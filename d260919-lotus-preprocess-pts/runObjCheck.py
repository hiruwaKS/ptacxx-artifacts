#!/usr/bin/env python3
"""Run an analyzer, dump the preprocessed IR, then object -> link -> run.

--name selects the analyzer (aser / tpa / seadsa).

Per case:
    lotus-<analyzer> --output-ir <m1>.ll <orig>.ll
    llc-14 -filetype=obj <ll> -o <obj>          (both orig and m1)
    clang++-14 <obj> stub.o -no-pie -o <exe>    (both)
    run <exe>; rc==0 means OK                   (both)

Return codes are recorded per stage and are never faked: a timeout is a
separate flag, not a made-up negative code, so it cannot be confused with a
signal. The final executable's rc/signal is kept distinct from every
intermediate (analyzer / llc / link) rc.

Outputs under --out-dir:
    <name>-objectcheck.csv
    <name>-objectcheck.md
"""

import argparse
import csv
import os
import pathlib
import re
import shutil
import subprocess
import threading
import time
from collections import Counter
from concurrent.futures import ThreadPoolExecutor, as_completed

HERE = pathlib.Path(__file__).resolve().parent
ART = HERE.parent
SUBDIRS = ("c", "cpp", "stl-libcxx", "stl-libstdcxx")
AN_BINS = {"aser": "lotus-aser-aa", "tpa": "lotus-tpa",
           "seadsa": "lotus-un-seadsa-aa"}
TOTAL_RE = re.compile(r"^total\s+(\d+)\s+us", re.M)

STUB_SRC = r"""
#include <stdio.h>
void SAFE_LOAD(void *p) { printf("SAFE_LOAD(%p)\n", p); }
void UNSAFE_LOAD(void *p) { printf("UNSAFE_LOAD(%p)\n", p); }
int nd_int(void) { return 0; }
void svf_print(int v, char *name) { printf("%s: %d\n", name ? name : "?", v); }
void set_value(int v, int lo, int hi) { (void)lo; (void)hi; printf("set_value(%d)\n", v); }
"""


def load_caseids(path):
    idmap = {}
    with open(path, newline="") as f:
        for row in csv.reader(f):
            if not row or row[0] == "id":
                continue
            idmap[row[1]] = int(row[0])
    return idmap


def first_line(text):
    return next((l.strip() for l in (text or "").splitlines() if l.strip()), "")


def _run(cmd, timeout, **kw):
    """Return (rc, timed_out, elapsed, stderr). rc is None on timeout."""
    t0 = time.monotonic()
    try:
        p = subprocess.run(cmd, capture_output=True, text=True,
                           errors="replace", timeout=timeout, **kw)
        return p.returncode, False, time.monotonic() - t0, p.stderr
    except subprocess.TimeoutExpired:
        return None, True, time.monotonic() - t0, ""


def run_llc(llc, src, obj, timeout):
    if obj.exists():
        obj.unlink()
    rc, to, dt, se = _run([llc, "-filetype=obj", str(src), "-o", str(obj)], timeout)
    size = obj.stat().st_size if obj.exists() else 0
    err = "llc timeout" if to else (first_line(se) if rc else "")
    return rc, to, dt, size, err


def run_link(cxx, obj, stub, exe, extra, timeout):
    rc, to, dt, se = _run([cxx, str(obj), str(stub), "-no-pie", "-o", str(exe)] + extra,
                          timeout)
    err = "link timeout" if to else (first_line(se) if rc else "")
    return rc, to, dt, err


def run_exe(exe, timeout):
    rc, to, dt, se = _run([str(exe)], timeout)
    if to:
        return None, 0, True, dt, "run timeout"
    if rc < 0:                       # killed by signal (returncode == -signum)
        return rc, -rc, False, dt, first_line(se) or f"signal {-rc}"
    return rc, 0, False, dt, first_line(se) if rc else ""


def run_aser(an, orig, dump, config_dir, timeout):
    env = os.environ.copy()
    if config_dir:
        env["LOTUS_CONFIG_DIR"] = str(config_dir)
    t0 = time.monotonic()
    try:
        p = subprocess.run([an, "--output-ir", str(dump), str(orig)],
                           input="", capture_output=True, text=True,
                           errors="replace", env=env, timeout=timeout)
        rc, to, out, err = p.returncode, False, p.stdout or "", p.stderr or ""
    except subprocess.TimeoutExpired:
        rc, to, out, err = None, True, "", ""
    dt = time.monotonic() - t0
    m = TOTAL_RE.search(out)
    total_s = int(m.group(1)) / 1e6 if m else dt
    return rc, to, total_s, dt, ("aser timeout" if to else first_line(err))


def build_stub(cxx, stub):
    p = subprocess.run([cxx, "-x", "c", "-c", "-", "-o", str(stub)],
                       input=STUB_SRC, capture_output=True, text=True, errors="replace")
    if p.returncode != 0:
        raise SystemExit("failed to build stub:\n" + p.stderr)


def rcstr(v):
    return "" if v is None else str(v)


def main():
    here = pathlib.Path(__file__).resolve().parent
    ap = argparse.ArgumentParser()
    ap.add_argument("--name", default="aser", choices=sorted(AN_BINS),
                    help="analyzer: aser / tpa / seadsa")
    ap.add_argument("--artifact-root", type=pathlib.Path, default=ART,
                    help="artifact repo root (default: script's parent dir)")
    ap.add_argument("--ptacxx-root", type=pathlib.Path,
                    default=os.environ.get("PTACXX_ROOT"),
                    help="ptacxx checkout root (or $PTACXX_ROOT); used to "
                         "derive --an-dir / --config-dir")
    ap.add_argument("--an", default=None)
    ap.add_argument("--an-dir", type=pathlib.Path, default=None,
                    help="default: <ptacxx-root>/build/build_debug/lotus/"
                         "src/drivers/lotus-alias")
    ap.add_argument("--llc", default="/usr/bin/llc-14")
    ap.add_argument("--cxx", default="/usr/bin/clang++-14")
    ap.add_argument("--config-dir", type=pathlib.Path, default=None,
                    help="default: <ptacxx-root>/config")
    ap.add_argument("--libcxx-lib", action="append", default=None,
                    help="repeatable -L dir for the libc++ runtime")
    ap.add_argument("--suite", type=pathlib.Path, default=None,
                    help="default: <artifact-root>/d260917-suite/blob/llvm14")
    ap.add_argument("--caseid", type=pathlib.Path, default=None,
                    help="default: <artifact-root>/d260917-suite/caseId.csv")
    ap.add_argument("--m1-root", type=pathlib.Path, default=None)
    ap.add_argument("--out-dir", type=pathlib.Path, default=None)
    ap.add_argument("--tmp", type=pathlib.Path, default=None)
    ap.add_argument("--branch", default="tmp-fix")
    ap.add_argument("--jobs", type=int, default=4,
                    help="parallel cases (default 4; use 1 for serial)")
    ap.add_argument("--timeout", type=float, default=120.0)
    ap.add_argument("--llc-timeout", type=float, default=60.0)
    ap.add_argument("--run-timeout", type=float, default=10.0)
    args = ap.parse_args()

    art = args.artifact_root.resolve()
    if args.suite is None:
        args.suite = art / "d260917-suite/blob/llvm14"
    if args.caseid is None:
        args.caseid = art / "d260917-suite/caseId.csv"
    if args.an_dir is None:
        if args.ptacxx_root is None:
            raise SystemExit("pass --an-dir or --ptacxx-root (or $PTACXX_ROOT)")
        args.an_dir = (args.ptacxx_root / "build/build_debug/lotus"
                       / "src/drivers/lotus-alias")
    if args.an is None:
        args.an = str(args.an_dir / AN_BINS[args.name])
    if args.config_dir is None and args.ptacxx_root is not None:
        args.config_dir = args.ptacxx_root / "config"
    if args.libcxx_lib is None:
        args.libcxx_lib = []
    if args.m1_root is None:
        args.m1_root = here / "blob" / "work" / args.name / "m1"
    if args.out_dir is None:
        args.out_dir = here / "blob" / f"llvm14-{args.name}-objectcheck"
    if args.tmp is None:
        args.tmp = pathlib.Path(f"/tmp/{args.name}_objcheck")


    idmap = load_caseids(args.caseid)
    if args.tmp.exists():
        shutil.rmtree(args.tmp)
    args.tmp.mkdir(parents=True)
    args.m1_root.mkdir(parents=True, exist_ok=True)
    args.out_dir.mkdir(parents=True, exist_ok=True)
    stub = args.tmp / "stub.o"
    build_stub(args.cxx, stub)

    libcxx = ["-stdlib=libc++"]
    for d in args.libcxx_lib:
        libcxx += ["-L", d, f"-Wl,-rpath,{d}"]

    cases = []
    for sub in SUBDIRS:
        d = args.suite / sub
        if d.is_dir():
            cases += [f"{sub}/{p.name}" for p in sorted(d.glob("*.ll"))]

    def stage(case_tmp, prefix, ll, sub, r):
        obj = case_tmp / f"{prefix}.o"
        exe = case_tmp / f"{prefix}.exe"
        rc, to, dt, size, err = run_llc(args.llc, ll, obj, args.llc_timeout)
        r[f"{prefix}_llc_rc"], r[f"{prefix}_llc_t"], r[f"{prefix}_llc_time_s"] = rc, to, dt
        if prefix == "m1":
            r["obj_bytes"] = size
        if rc != 0 or to:
            r.update({f"{prefix}_link_rc": None, f"{prefix}_link_t": False,
                      f"{prefix}_run_rc": None, f"{prefix}_run_sig": 0,
                      f"{prefix}_run_t": False, f"{prefix}_run_time_s": 0.0,
                      f"{prefix}_err": err})
            return
        lrc, lto, _, lerr = run_link(args.cxx, obj, stub, exe,
                                     libcxx if sub == "stl-libcxx" else [],
                                     args.llc_timeout)
        r[f"{prefix}_link_rc"], r[f"{prefix}_link_t"] = lrc, lto
        if lrc != 0 or lto:
            r.update({f"{prefix}_run_rc": None, f"{prefix}_run_sig": 0,
                      f"{prefix}_run_t": False, f"{prefix}_run_time_s": 0.0,
                      f"{prefix}_err": lerr})
            return
        rrc, sig, rto, rdt, rerr = run_exe(exe, args.run_timeout)
        r[f"{prefix}_run_rc"], r[f"{prefix}_run_sig"] = rrc, sig
        r[f"{prefix}_run_t"], r[f"{prefix}_run_time_s"] = rto, rdt
        r[f"{prefix}_err"] = rerr

    def process(index, case):
        sub = case.split("/")[0]
        orig = args.suite / case
        m1 = args.m1_root / case
        m1.parent.mkdir(parents=True, exist_ok=True)
        case_tmp = args.tmp / f"{index:04d}"
        case_tmp.mkdir(parents=True, exist_ok=True)
        arc, ato, at, aw, aerr = run_aser(args.an, orig, m1, args.config_dir, args.timeout)
        r = dict(caseId=idmap.get(case, -1), case=case, branch=args.branch, round=1,
                 aser_rc=arc, aser_t=ato, aser_time_s=at, aser_wall_s=aw)
        if arc == 0 and not ato and m1.is_file():
            stage(case_tmp, "orig", orig, sub, r)
            stage(case_tmp, "m1", m1, sub, r)
            if r["m1_llc_t"]:
                st, err = "llc_timeout", r["m1_err"]
            elif r["m1_llc_rc"] != 0:
                st = "llc_fail_new" if r["orig_llc_rc"] == 0 else "llc_fail_both"
                err = r["m1_err"]
            elif r["m1_link_t"]:
                st, err = "link_timeout", r["m1_err"]
            elif r["m1_link_rc"] != 0:
                st = "link_fail_new" if r["orig_link_rc"] == 0 else "link_fail_both"
                err = r["m1_err"]
            elif r["m1_run_t"]:
                st, err = "run_timeout", r["m1_err"]
            elif r["m1_run_rc"] != 0:
                st = "run_fail_new" if r["orig_run_rc"] == 0 else "run_fail_both"
                err = r["m1_err"]
            else:
                st, err = "ok", ""
            r["status"], r["err"] = st, err
        else:
            for p in ("orig", "m1"):
                r.update({f"{p}_llc_rc": None, f"{p}_llc_t": False, f"{p}_llc_time_s": 0.0,
                          f"{p}_link_rc": None, f"{p}_link_t": False,
                          f"{p}_run_rc": None, f"{p}_run_sig": 0, f"{p}_run_t": False,
                          f"{p}_run_time_s": 0.0, f"{p}_err": ""})
            r["obj_bytes"] = 0
            r["status"] = "aser_timeout" if ato else "an_fail"
            r["err"] = aerr or "no dump"
        return index, r

    rows = [None] * len(cases)
    done = 0
    lock = threading.Lock()

    def report():
        nok = sum(1 for x in rows if x and x["status"] == "ok")
        print(f"{done}/{len(cases)} ok={nok}", flush=True)

    if args.jobs <= 1:
        for i, case in enumerate(cases, 1):
            _, rows[i - 1] = process(i, case)
            done += 1
            if done % 20 == 0:
                report()
    else:
        with ThreadPoolExecutor(max_workers=args.jobs) as ex:
            futs = [ex.submit(process, i, c) for i, c in enumerate(cases, 1)]
            for fut in as_completed(futs):
                idx, r = fut.result()
                rows[idx - 1] = r
                with lock:
                    done += 1
                    if done % 20 == 0:
                        report()

    cols = ["caseId", "case", "branch", "round",
            "an_rc", "an_t", "an_time_s", "an_wall_s",
            "orig_llc_rc", "orig_llc_t", "orig_link_rc", "orig_link_t",
            "orig_run_rc", "orig_run_sig", "orig_run_t", "orig_run_time_s",
            "m1_llc_rc", "m1_llc_t", "m1_link_rc", "m1_link_t",
            "m1_run_rc", "m1_run_sig", "m1_run_t", "m1_run_time_s",
            "obj_bytes", "status", "err"]
    with open(args.out_dir / f"{args.name}-objectcheck.csv", "w", newline="") as f:
        w = csv.writer(f)
        w.writerow(cols)
        for r in rows:
            w.writerow([
                r["caseId"], r["case"], r["branch"], r["round"],
                rcstr(r["aser_rc"]), int(r["aser_t"]), f"{r['aser_time_s']:.4f}",
                f"{r['aser_wall_s']:.4f}",
                rcstr(r["orig_llc_rc"]), int(r["orig_llc_t"]),
                rcstr(r["orig_link_rc"]), int(r["orig_link_t"]),
                rcstr(r["orig_run_rc"]), r["orig_run_sig"], int(r["orig_run_t"]),
                f"{r['orig_run_time_s']:.4f}",
                rcstr(r["m1_llc_rc"]), int(r["m1_llc_t"]),
                rcstr(r["m1_link_rc"]), int(r["m1_link_t"]),
                rcstr(r["m1_run_rc"]), r["m1_run_sig"], int(r["m1_run_t"]),
                f"{r['m1_run_time_s']:.4f}",
                int(r["obj_bytes"]), r["status"], r["err"]])

    cnt = Counter(r["status"] for r in rows)

    def stats(vals):
        xs = sorted(vals)
        n = len(xs)
        return (sum(xs) / n, xs[0], xs[min(n - 1, int(n * 0.95))], xs[-1]) if n else (0,) * 4

    am = stats([r["aser_time_s"] for r in rows])
    om = stats([r["orig_run_time_s"] for r in rows if r["orig_run_rc"] == 0])
    mm = stats([r["m1_run_time_s"] for r in rows if r["m1_run_rc"] == 0])
    fails = [r for r in rows if r["status"] != "ok"]
    L = [f"# {args.name} IR -> object -> link -> run check", "",
         f"- analyzer: `{args.an}` (branch `{args.branch}`)",
         f"- dump: `--output-ir` -> `{args.m1_root}`",
         f"- chain: `{args.llc} -filetype=obj` -> `{args.cxx}` link -> run",
         f"- total cases: {len(rows)}", "", "## status", "",
         "| status | count |", "|---|---|"]
    for k in ("ok", "run_fail_new", "run_fail_both", "run_timeout", "link_fail_new",
              "link_fail_both", "link_timeout", "llc_fail_new", "llc_fail_both",
              "llc_timeout", "an_fail", "aser_timeout", "no_dump"):
        if cnt.get(k):
            L.append(f"| {k} | {cnt.get(k)} |")
    L += ["", "## time (s)", "", "| arm | mean | min | p95 | max |",
          "|---|---|---|---|---|",
          f"| {args.name} preprocess | {am[0]:.4f} | {am[1]:.4f} | {am[2]:.4f} | {am[3]:.4f} |",
          f"| orig exe | {om[0]:.4f} | {om[1]:.4f} | {om[2]:.4f} | {om[3]:.4f} |",
          f"| m1 exe | {mm[0]:.4f} | {mm[1]:.4f} | {mm[2]:.4f} | {mm[3]:.4f} |", ""]
    if fails:
        L += ["## failures", "",
              "| caseId | case | orig_run_rc | m1_run_rc | m1_sig | status | err |",
              "|---|---|---|---|---|---|---|"]
        for r in fails:
            L.append(f"| {r['caseId']} | {r['case']} | {rcstr(r['orig_run_rc'])} | "
                     f"{rcstr(r['m1_run_rc'])} | {r['m1_run_sig']} | {r['status']} | "
                     f"{r['err'][:160]} |")
    else:
        L += ["## failures", "", "none"]
    (args.out_dir / f"{args.name}-objectcheck.md").write_text("\n".join(L) + "\n")

    print("status:", dict(cnt))
    print("out:", args.out_dir / f"{args.name}-objectcheck.csv")


if __name__ == "__main__":
    main()
