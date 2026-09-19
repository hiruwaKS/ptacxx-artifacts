#!/usr/bin/env python3
"""Run a lotus analyzer against d260917-pts dumps and split results into two CSVs.

For each `.pts` dump, the matching module is the original `.ll` in the suite blob
(the dump's VIds are assigned on the pre-instrumentation module). The analyzer is
driven as a query server: `pts-test <dump>` on stdin, `<init>` / `<queryresult>` /
`<queryerror>` on stdout.

Outputs:
  normal.csv    one row per successful query:
                name, arg_parse, ir_load, index, analysis, total, Pass, Fail, Unresolved
  abnormal.csv  one row per failed query:
                name, class, detail
                class in {init_error, query_error, timeout,
                          init_abort, query_abort, init_segfault, query_segfault,
                          init_other, query_other}

Usage:
  runPtsTest.py <analyzer> [--pts-root DIR] [--suite-root DIR] [--out-dir DIR]
                [--jobs N] [--timeout S] [--limit N] [--dump-dir DIR] [args...]
"""

import argparse
import concurrent.futures
import csv
import os
import pathlib
import re
import signal
import subprocess
import sys
import threading
import time

HERE = pathlib.Path(__file__).resolve().parent
DEFAULT_PTS = HERE.parent / "d260917-pts" / "blob" / "llvm14"
DEFAULT_SUITE = HERE.parent / "d260917-suite" / "blob" / "llvm14"
DEFAULT_CONFIG = (pathlib.Path(os.environ["LOTUS_CONFIG_DIR"])
                  if os.environ.get("LOTUS_CONFIG_DIR") else None)
DEFAULT_TIMEOUT = 120.0
INIT_KEYS = ["arg_parse", "ir_load", "index", "analysis", "total"]

TAG_RE = re.compile(r"<([a-zA-Z]+)>\n(.*?)\n</\1>", re.S)


def extract(stdout, tag):
    m = re.search(rf"<{tag}>\n(.*?)\n</{tag}>", stdout, re.S)
    return m.group(1) if m else None


def one_line(text):
    return (text or "").replace("\r\n", "\n").replace("\r", "\n").replace("\n", "\\n")


def signal_name(rc):
    if rc is None or rc >= 0:
        return None
    try:
        return signal.Signals(-rc).name
    except ValueError:
        return None


def module_for(dump, pts_root, suite_root):
    rel = dump.relative_to(pts_root)
    return suite_root / str(rel)[: -len(".pts")]


def load_subset(paths):
    wanted = set()
    for path in paths:
        f = pathlib.Path(path)
        if not f.is_file():
            sys.exit(f"subset file not found: {f}")
        for line in f.read_text(encoding="utf-8").splitlines():
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            wanted.add(line)
            if "/" not in line:
                wanted.add(pathlib.Path(line).name)
    return wanted


def in_subset(dump, pts_root, wanted):
    rel = str(dump.relative_to(pts_root))
    rel_noext = rel[: -len(".pts")]
    name_noext = dump.name[: -len(".pts")]
    return (rel in wanted or rel_noext in wanted
            or dump.name in wanted or name_noext in wanted)


def parse_normal(stdout):
    qres = extract(stdout, "queryresult")
    if qres is None:
        return None
    def num(key):
        m = re.search(rf"\b{key}=(\d+)\b", qres)
        return int(m.group(1)) if m else None
    passes, fails, errors = num("Pass"), num("Fail"), num("Error")
    if passes is None or fails is None or errors is None:
        return None
    return passes, fails, errors


def parse_init(stdout):
    body = extract(stdout, "init")
    if body is None:
        return None
    out = {}
    for line in body.splitlines():
        parts = line.split()
        if len(parts) == 3 and parts[2] == "us":
            out[parts[0]] = parts[1]
    return out


def _crash_class(crash_text, phase):
    low = crash_text.lower()
    if "assert" in low or "llvm error" in low or "abort" in low or "trap" in low:
        return (f"{phase}_abort", one_line(crash_text))
    if "segmentation" in low or "segfault" in low or "sigbus" in low:
        return (f"{phase}_segfault", one_line(crash_text))
    return (f"{phase}_other", one_line(crash_text))


def run_once(dump, module, analyzer, analyzer_args, timeout, env, dump_dir, relname):
    """Run one case in this worker thread. A watchdog thread streams the child's
    stderr and kills the process group immediately when the analyzer crashes:
    LLVM's crash printer forks a helper and can hang there long past the timeout,
    which used to be misclassified as a plain timeout."""
    query = f"pts-test {dump.resolve()}"
    proc = subprocess.Popen(
        [str(analyzer), str(module), *analyzer_args],
        stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
        text=True, env=env, start_new_session=True,
    )

    crash_re = re.compile(
        r"Assertion `[^']*' failed\.?|Assertion .* failed|LLVM ERROR:"
        r"|PLEASE submit a bug report|[Ss]egmentation fault|Trace/breakpoint trap"
    )
    state = {
        "lock": threading.Lock(),
        "arrived": threading.Event(),
        "out_lines": [],
        "err_lines": [],
        "crash": None,
    }

    def pump(stream, target):
        try:
            for line in iter(stream.readline, ""):
                with state["lock"]:
                    target.append(line)
                state["arrived"].set()
        finally:
            stream.close()

    pumps = [
        threading.Thread(target=pump, args=(proc.stdout, state["out_lines"]), daemon=True),
        threading.Thread(target=pump, args=(proc.stderr, state["err_lines"]), daemon=True),
    ]
    for t in pumps:
        t.start()

    timed_out = threading.Event()

    def kill_tree():
        try:
            os.killpg(os.getpgid(proc.pid), signal.SIGKILL)
        except (ProcessLookupError, PermissionError):
            pass

    def watch():
        pos = 0
        deadline = time.monotonic() + timeout
        while time.monotonic() <= deadline:
            if state["crash"] is not None:
                kill_tree()
                return
            state["arrived"].wait(0.05)
            state["arrived"].clear()
            with state["lock"]:
                lines = state["err_lines"]
                while pos < len(lines):
                    line = lines[pos]
                    pos += 1
                    if crash_re.search(line):
                        state["crash"] = line.strip()
            if state["crash"] is not None:
                kill_tree()
                return
            if proc.poll() is not None:
                return
        timed_out.set()
        kill_tree()

    watchdog = threading.Thread(target=watch, daemon=True)
    watchdog.start()

    if proc.stdin is not None:
        try:
            proc.stdin.write(query)
        except BrokenPipeError:
            pass
        try:
            proc.stdin.close()
        except BrokenPipeError:
            pass

    for t in pumps:
        t.join()
    watchdog.join()

    with state["lock"]:
        stdout = "".join(state["out_lines"])
        stderr = "".join(state["err_lines"])
        crash = state["crash"]
    raw = stdout + "\n" + stderr
    if dump_dir:
        dump_path = dump_dir / (relname + ".txt")
        dump_path.parent.mkdir(parents=True, exist_ok=True)
        dump_path.write_text(raw, encoding="utf-8")

    if crash is not None:
        phase = "query" if parse_init(stdout) is not None else "init"
        cls, detail = _crash_class(crash, phase)
        return (cls, detail, raw, None)

    if timed_out.is_set():
        return ("timeout", f"timeout after {timeout:g}s", raw, None)

    init = parse_init(stdout)
    initerr = extract(stdout, "initerror")
    qerr = extract(stdout, "queryerror")
    rc = proc.returncode

    if initerr is not None:
        return ("init_error", one_line(initerr), raw, None)
    if qerr is not None:
        return ("query_error", one_line(qerr), raw, None)

    normal = parse_normal(stdout)
    if rc == 0 and normal is not None:
        passes, fails, errors = normal
        init = init or {}
        row = [init.get(k, "") for k in INIT_KEYS] + [passes, fails, errors]
        return ("ok", row, raw, None)

    phase = "query" if init is not None else "init"
    sig = signal_name(rc)
    if sig == "SIGSEGV":
        cls = f"{phase}_segfault"
    elif sig == "SIGABRT":
        cls = f"{phase}_abort"
    else:
        cls = f"{phase}_other"
    detail = f"rc={rc}" + (f" ({sig})" if sig else "")
    tail = (stderr or stdout).strip()
    if tail:
        detail += " " + one_line(tail[-1000:])
    return (cls, detail, raw, None)


def _run_pass(analyzer, pts_root, suite_root, out_dir, normal_csv, abnormal_csv,
              config_dir, dump_dir, jobs, timeout, limit, subset, analyzer_args,
              prefix=""):
    """Run one pass against the pts set, writing fresh CSVs into out_dir.
    Returns the set of case names that timed out, or 2 if no dumps matched."""
    if config_dir is None:
        sys.exit("config dir not set: pass --config-dir or set LOTUS_CONFIG_DIR")
    out_dir = out_dir if out_dir is not None else HERE / "blob"
    subset = subset or []
    analyzer_args = analyzer_args or []

    normal_csv = normal_csv or out_dir / "pts-test-normal.csv"
    abnormal_csv = abnormal_csv or out_dir / "pts-test-abnormal.csv"
    normal_csv.parent.mkdir(parents=True, exist_ok=True)
    if dump_dir:
        dump_dir.mkdir(parents=True, exist_ok=True)

    dumps = sorted(pts_root.rglob("*.pts"))
    if subset:
        wanted = load_subset(subset)
        dumps = [d for d in dumps if in_subset(d, pts_root, wanted)]
    if limit:
        dumps = dumps[: limit]
    if not dumps:
        print(f"no .pts dumps under {pts_root}", file=sys.stderr)
        return 2

    env = os.environ.copy()
    env["LOTUS_CONFIG_DIR"] = str(config_dir)

    analyzer = pathlib.Path(analyzer).resolve()

    nproc = jobs if jobs > 0 else (os.cpu_count() or 1)
    jobs = [(d, module_for(d, pts_root, suite_root)) for d in dumps]
    missing = [(d, m) for d, m in jobs if not m.is_file()]
    jobs = [(d, m) for d, m in jobs if m.is_file()]

    normal_fh = normal_csv.open("w", newline="", encoding="utf-8")
    abnormal_fh = abnormal_csv.open("w", newline="", encoding="utf-8")
    normal_w = csv.writer(normal_fh)
    abnormal_w = csv.writer(abnormal_fh)
    normal_w.writerow(["name", *INIT_KEYS, "Pass", "Fail", "Unresolved"])
    abnormal_w.writerow(["name", "class", "detail"])
    normal_fh.flush()
    abnormal_fh.flush()

    done = 0
    total = len(jobs) + len(missing)
    timeouts = set()

    def record(dump, status, payload):
        nonlocal done
        done += 1
        name = str(dump.relative_to(pts_root))[: -len(".pts")]
        if status == "ok":
            normal_w.writerow([name, *payload])
            normal_fh.flush()
            print(f"{prefix}[{done}/{total}] OK   {name}", flush=True)
        else:
            abnormal_w.writerow([name, status, payload])
            abnormal_fh.flush()
            print(f"{prefix}[{done}/{total}] {status.upper()} {name} {payload[:120]}", flush=True)
            if status == "timeout":
                timeouts.add(name)

    for d, m in missing:
        record(d, "missing_module", f"module not found: {m}")

    with concurrent.futures.ThreadPoolExecutor(max_workers=nproc) as ex:
        futs = {
            ex.submit(run_once, d, m, analyzer, analyzer_args, timeout,
                      env, dump_dir,
                      str(d.relative_to(pts_root))[: -len(".pts")]): d
            for d, m in jobs
        }
        for fut in concurrent.futures.as_completed(futs):
            dump = futs[fut]
            status, payload, _raw, _ = fut.result()
            record(dump, status, payload)

    normal_fh.close()
    abnormal_fh.close()
    print(f"{prefix}done {done}/{total} -> {normal_csv} , {abnormal_csv}")
    return timeouts


def _read_rows(csv_path):
    if not csv_path.is_file():
        return []
    with csv_path.open(newline="", encoding="utf-8") as f:
        return list(csv.reader(f))[1:]


def _write_rows(csv_path, rows):
    csv_path.parent.mkdir(parents=True, exist_ok=True)
    with csv_path.open("w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        if csv_path.name.endswith("-normal.csv"):
            w.writerow(["name", *INIT_KEYS, "Pass", "Fail", "Unresolved"])
        else:
            w.writerow(["name", "class", "detail"])
        w.writerows(rows)


def _run_escalating(analyzer, timeouts, pts_root, suite_root, out_dir,
                    normal_csv, abnormal_csv, config_dir, dump_dir, jobs,
                    limit, subset, analyzer_args):
    """Run timeouts in escalating order: a case is re-run at the next, larger
    timeout only if it timed out at the previous tier, and is recorded as a
    timeout only if it times out at every tier. Cases that pass or crash at a
    smaller timeout are never re-run."""
    out_dir = out_dir if out_dir is not None else HERE / "blob"
    normal_csv = normal_csv or out_dir / "pts-test-normal.csv"
    abnormal_csv = abnormal_csv or out_dir / "pts-test-abnormal.csv"
    if dump_dir:
        dump_dir.mkdir(parents=True, exist_ok=True)

    normal_rows, abnormal_rows = [], []
    pending = None
    for i, t in enumerate(timeouts):
        if pending is not None and not pending:
            break
        tier = out_dir / f"t{str(t).replace('.', '_')}"
        tier.mkdir(parents=True, exist_ok=True)
        prefix = f"[{t}s] "
        tier_subset = list(subset or [])
        if pending is not None:
            names_file = tier / "pending.txt"
            names_file.write_text("\n".join(sorted(pending)) + "\n", encoding="utf-8")
            tier_subset = [names_file]
        left = _run_pass(analyzer, pts_root, suite_root, tier,
                         tier / "pts-test-normal.csv", tier / "pts-test-abnormal.csv",
                         config_dir, dump_dir, jobs, t, limit, tier_subset,
                         analyzer_args, prefix=prefix)
        if left == 2:
            return 2
        normal_rows += _read_rows(tier / "pts-test-normal.csv")
        abnormal_rows += [r for r in _read_rows(tier / "pts-test-abnormal.csv")
                          if len(r) >= 2 and r[1] != "timeout"]
        pending = left

    for name in sorted(pending):
        abnormal_rows.append([name, "timeout", f"timeout after {timeouts[-1]:g}s"])

    _write_rows(normal_csv, normal_rows)
    _write_rows(abnormal_csv, abnormal_rows)
    print(f"\nmerged -> {normal_csv} , {abnormal_csv}")
    return 0


def run_batch(analyzer, pts_root=DEFAULT_PTS, suite_root=DEFAULT_SUITE,
              out_dir=None, normal_csv=None, abnormal_csv=None,
              config_dir=None, dump_dir=None, jobs=4, timeout=DEFAULT_TIMEOUT,
              timeouts=None, limit=0, subset=None, analyzer_args=None):
    """Run the analyzer against the pts set. With a single timeout this behaves
    like one pass; with several timeouts (e.g. [1, 4, 16]) timeouts escalate and
    a case is only recorded as a timeout if it times out at every tier."""
    if timeouts:
        return _run_escalating(analyzer, timeouts, pts_root, suite_root,
                               out_dir, normal_csv, abnormal_csv, config_dir,
                               dump_dir, jobs, limit, subset, analyzer_args)
    r = _run_pass(analyzer, pts_root, suite_root, out_dir, normal_csv,
                  abnormal_csv, config_dir, dump_dir, jobs, timeout, limit,
                  subset, analyzer_args)
    return 0 if r != 2 else 2


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("analyzer")
    ap.add_argument("--pts-root", type=pathlib.Path, default=DEFAULT_PTS)
    ap.add_argument("--suite-root", type=pathlib.Path, default=DEFAULT_SUITE)
    ap.add_argument("--out-dir", type=pathlib.Path, default=None)
    ap.add_argument("--normal-csv", type=pathlib.Path, default=None)
    ap.add_argument("--abnormal-csv", type=pathlib.Path, default=None)
    ap.add_argument("--config-dir", type=pathlib.Path, default=DEFAULT_CONFIG)
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--timeout", type=float, nargs="+", default=[DEFAULT_TIMEOUT],
                    help="timeout in seconds; several values escalate "
                         "(e.g. '1 4 16': a case is only recorded as timeout if "
                         "it times out at every tier, and a passing/crashing "
                         "case is never re-run)")
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--subset", action="append", default=[], metavar="FILE",
                    help="only run dumps named in FILE (repeatable)")
    ap.add_argument("--dump-dir", type=pathlib.Path, default=None)
    args, analyzer_args = ap.parse_known_args()
    analyzer_args = [a for a in analyzer_args if a != "--"]

    timeouts = args.timeout if len(args.timeout) > 1 else None
    return run_batch(
        args.analyzer,
        pts_root=args.pts_root, suite_root=args.suite_root,
        out_dir=args.out_dir, normal_csv=args.normal_csv,
        abnormal_csv=args.abnormal_csv, config_dir=args.config_dir,
        dump_dir=args.dump_dir, jobs=args.jobs, timeout=args.timeout[0],
        timeouts=timeouts, limit=args.limit, subset=args.subset,
        analyzer_args=analyzer_args,
    )


if __name__ == "__main__":
    sys.exit(main())
