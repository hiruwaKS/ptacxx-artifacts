#!/usr/bin/env python3
"""Rebuild the TPA points-to (pts) dataset from preprocessed IR.

The d260917-pts oracle was generated from the raw `.ll`. TPA rewrites the
module during preprocessing (M -> M*), so the index / alias spec built from
the original module no longer matches the module the analysis actually runs
on.  Regenerate the oracle from M* so both sides use the same IR:

    orig.ll --lotus-tpa --output-ir--> M* --instrument--> link.inst --> run
    --> M*.ll.pts

Per case (llvm14, 921 cases, excluding the two UB cases of d260917-pts):
    1. lotus-tpa --output-ir <mstar> <orig.ll>      (preprocess)
    2. instrument <mstar> -o <base>.inst.bc -mode-ptr
    3. clang++-14 <base>.inst.bc ... -o <base>.inst
    4. PTACXX_DUMP_PATH=<base> <base>.inst          -> <base>.ll.pts

Outputs:
    <out-pts>/<sub>/<caseId>.ll.inst.bc / .inst / .ll.pts   (mirrors d260917-pts)
    <out-pts>/results.csv
    <out-pts>/results.md
    <mstar-root>/<sub>/<caseId>.ll            (staging tree, fed to instrument)
    <mstar-flat>/<caseId>.ll                  (canonical M*, by caseId)
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
AN_BINS = {
    "aa": "lotus-aa",
    "sparrow": "lotus-sparrow-aa",
    "aser": "lotus-aser-aa",
    "dyckaa": "lotus-un-dyckaa",
    "seadsa": "lotus-un-seadsa-aa",
    "tpa": "lotus-tpa",
}

# d260917-pts/blob/llvm14 excluded these as UB (behaviour flips under
# instrumentation).  Keeping the same exclusions yields 921 cases.
UB_CASES = {
    "c/c89-basic-address-dereference-test-recursiveglobal.c.ll",
    "c/c89-member-access-path13-struct-field-alias.c.ll",
}

# AserPTA does not model exception control flow; these 14 cases terminate
# after preprocessing (m1_run_rc=-6), so they are skipped -> 907 cases.
ASER_SKIP = {
    "cpp/cpp98-dynamic-cast-reference-bad-cast.cpp.ll",
    "cpp/cpp98-exception-basic-throw-catch-double-ptr.cpp.ll",
    "cpp/cpp98-exception-catch-base-derived-dispatch.cpp.ll",
    "cpp/cpp98-exception-throw-pointer-resource-cleanup.cpp.ll",
    "stl-libcxx/cpp98-stl-exception-catch-by-base-polymorphic.cpp.ll",
    "stl-libcxx/cpp98-stl-exception-logic-error-map.cpp.ll",
    "stl-libcxx/cpp98-stl-exception-out-of-range-vector.cpp.ll",
    "stl-libcxx/cpp98-stl-exception-resource-cleanup-container.cpp.ll",
    "stl-libcxx/cpp98-stl-exception-runtime-error-string.cpp.ll",
    "stl-libstdcxx/cpp98-stl-exception-catch-by-base-polymorphic.cpp.ll",
    "stl-libstdcxx/cpp98-stl-exception-logic-error-map.cpp.ll",
    "stl-libstdcxx/cpp98-stl-exception-out-of-range-vector.cpp.ll",
    "stl-libstdcxx/cpp98-stl-exception-resource-cleanup-container.cpp.ll",
    "stl-libstdcxx/cpp98-stl-exception-runtime-error-string.cpp.ll",
}

TYPE_RE = re.compile(
    r"^(i\d+|half|bfloat|float|double|x86_fp80|fp128|ppc_fp128|label|ptr|void)\b")


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


def count_instrs(path):
    """Approximate instruction count of a textual `.ll` file."""
    n = 0
    inside = False
    for line in path.read_text(errors="replace").splitlines():
        s = line.strip()
        if not inside:
            if s.startswith("define ") and s.endswith("{"):
                inside = True
            continue
        if s == "}":
            inside = False
            continue
        if not s or s.startswith(";") or s.startswith("!"):
            continue
        if s.endswith(":"):                      # basic-block label
            continue
        if "label %" in s and TYPE_RE.match(s):  # switch case lines
            continue
        n += 1
    return n


def _run(cmd, timeout, **kw):
    """Return (rc, timed_out, elapsed, stderr). rc is None on timeout."""
    t0 = time.monotonic()
    try:
        p = subprocess.run(cmd, capture_output=True, text=True,
                           errors="replace", timeout=timeout, **kw)
        return p.returncode, False, time.monotonic() - t0, p.stderr
    except subprocess.TimeoutExpired:
        return None, True, time.monotonic() - t0, ""


def main():
    here = pathlib.Path(__file__).resolve().parent
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--name", default="tpa", choices=sorted(AN_BINS),
                    help="analyzer: aa / sparrow / aser / dyckaa / seadsa / tpa")
    ap.add_argument("--artifact-root", type=pathlib.Path, default=ART,
                    help="artifact repo root (default: script's parent dir)")
    ap.add_argument("--ptacxx-root", type=pathlib.Path,
                    default=os.environ.get("PTACXX_ROOT"),
                    help="ptacxx checkout root (or $PTACXX_ROOT); used to "
                         "derive --an-dir / --instrument / --hook / --config-dir")
    ap.add_argument("--an", default=None,
                    help="analyzer binary (default: --an-dir/--name)")
    ap.add_argument("--an-dir", type=pathlib.Path, default=None,
                    help="default: <ptacxx-root>/build/build_debug/lotus/"
                         "src/drivers/lotus-alias")
    ap.add_argument("--instrument", default=None,
                    help="default: <ptacxx-root>/build/build_debug/lotus/"
                         "src/instrument/instrument")
    ap.add_argument("--hook", default=None,
                    help="default: <ptacxx-root>/build/build_debug/lotus/"
                         "src/hook/libhook.so")
    ap.add_argument("--llvm", default="/usr/lib/llvm-14")
    ap.add_argument("--cxx", default="/usr/bin/clang++-14")
    ap.add_argument("--config-dir", type=pathlib.Path, default=None,
                    help="default: <ptacxx-root>/config")
    ap.add_argument("--libcxx-lib", action="append", default=None,
                    help="repeatable -L dir for the libc++ runtime")
    ap.add_argument("--suite", type=pathlib.Path, default=None,
                    help="default: <artifact-root>/d260917-suite/blob/llvm14")
    ap.add_argument("--caseid", type=pathlib.Path, default=None,
                    help="default: <artifact-root>/d260917-suite/caseId.csv")
    ap.add_argument("--out-pts", type=pathlib.Path, default=None,
                    help="default: blob/llvm14-<name>-pts")
    ap.add_argument("--mstar-root", type=pathlib.Path, default=None,
                    help="default: blob/work/<name>/mstar")
    ap.add_argument("--mstar-flat", type=pathlib.Path, default=None,
                    help="default: blob/<name>")
    ap.add_argument("--mode", default="-mode-ptr")
    ap.add_argument("--k", type=int, default=0)
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--timeout", type=float, default=120.0)
    ap.add_argument("--run-timeout", type=float, default=30.0)
    ap.add_argument("--limit", type=int, default=0,
                    help="only process the first N cases (for a smoke test)")
    args = ap.parse_args()

    art = args.artifact_root.resolve()
    lotus_build = (args.ptacxx_root / "build/build_debug/lotus"
                   if args.ptacxx_root else None)
    if args.suite is None:
        args.suite = art / "d260917-suite/blob/llvm14"
    if args.caseid is None:
        args.caseid = art / "d260917-suite/caseId.csv"
    if args.an_dir is None:
        if lotus_build is None:
            raise SystemExit("pass --an-dir or --ptacxx-root (or $PTACXX_ROOT)")
        args.an_dir = lotus_build / "src/drivers/lotus-alias"
    if args.an is None:
        args.an = str(args.an_dir / AN_BINS[args.name])
    if args.instrument is None:
        if lotus_build is None:
            raise SystemExit("pass --instrument or --ptacxx-root")
        args.instrument = str(lotus_build / "src/instrument/instrument")
    if args.hook is None:
        if lotus_build is None:
            raise SystemExit("pass --hook or --ptacxx-root")
        args.hook = str(lotus_build / "src/hook/libhook.so")
    if args.config_dir is None and args.ptacxx_root is not None:
        args.config_dir = args.ptacxx_root / "config"
    if args.libcxx_lib is None:
        args.libcxx_lib = []
    if args.out_pts is None:
        args.out_pts = here / f"blob/llvm14-{args.name}-pts"
    if args.mstar_root is None:
        args.mstar_root = here / f"blob/work/{args.name}/mstar"
    if args.mstar_flat is None:
        args.mstar_flat = here / f"blob/{args.name}"

    skip = set(UB_CASES)
    if args.name == "aser":
        skip |= ASER_SKIP

    llvm_prefix = pathlib.Path(args.llvm)
    llvm_config = llvm_prefix / "bin" / "llvm-config"
    try:
        llvm_ldflags = subprocess.run(
            [str(llvm_config), "--libs", "--system-libs", "--ldflags"],
            capture_output=True, text=True, check=True).stdout.split()
    except (OSError, subprocess.CalledProcessError) as e:
        raise SystemExit(f"failed to query llvm-config: {e}")

    idmap = load_caseids(args.caseid)

    cases = []
    for sub in SUBDIRS:
        d = args.suite / sub
        if d.is_dir():
            for p in sorted(d.glob("*.ll")):
                rel = f"{sub}/{p.name}"
                if rel in skip:
                    continue
                cases.append(rel)
    if args.limit:
        cases = cases[:args.limit]

    args.out_pts.mkdir(parents=True, exist_ok=True)
    args.mstar_root.mkdir(parents=True, exist_ok=True)
    args.mstar_flat.mkdir(parents=True, exist_ok=True)

    libcxx_flags = []
    for d in args.libcxx_lib:
        libcxx_flags += ["-L", d, f"-Wl,-rpath,{d}"]

    env_base = os.environ.copy()
    if args.config_dir:
        env_base["LOTUS_CONFIG_DIR"] = str(args.config_dir)

    lock = threading.Lock()
    done = 0
    rows = [None] * len(cases)

    def process(index, rel):
        sub = rel.split("/")[0]
        case_id = idmap.get(rel, -1)
        orig = args.suite / rel
        mstar = args.mstar_root / sub / f"{case_id}.ll"
        mstar.parent.mkdir(parents=True, exist_ok=True)
        base = args.out_pts / sub / f"{case_id}.ll"
        base.parent.mkdir(parents=True, exist_ok=True)
        bc, exe, dump = f"{base}.inst.bc", f"{base}.inst", str(base)
        r = dict(caseId=case_id, case=rel)

        # 1. preprocess
        rc, to, dt, se = _run([args.an, "--output-ir", str(mstar), str(orig)],
                              args.timeout, input="", env=env_base)
        r["preprocess_s"] = dt
        if rc != 0 or to or not mstar.is_file():
            r.update(status="preprocess_timeout" if to else "preprocess_fail",
                     err=first_line(se) or ("timeout" if to else "no dump"))
            return index, r

        shutil.copy2(mstar, args.mstar_flat / f"{case_id}.ll")
        r["ir_instr_orig"] = count_instrs(orig)
        r["ir_instr_mstar"] = count_instrs(mstar)
        r["ir_size_ratio"] = (r["ir_instr_mstar"] / r["ir_instr_orig"]
                              if r["ir_instr_orig"] else 0.0)

        # 2. instrument
        env = os.environ.copy()
        env["LD_LIBRARY_PATH"] = str(llvm_prefix / "lib") + (
            ":" + env["LD_LIBRARY_PATH"] if env.get("LD_LIBRARY_PATH") else "")
        rc, to, inst_s, se = _run(
            [args.instrument, str(mstar), "-o", bc, args.mode], args.timeout,
            env=env)
        if rc != 0 or to:
            r.update(status="instrument_timeout" if to else "instrument_fail",
                     err=first_line(se))
            return index, r

        # 3. link
        lflags = ["-stdlib=libc++"] + libcxx_flags if sub == "stl-libcxx" else []
        rc, to, link_s, se = _run(
            [args.cxx] + lflags + [bc, "-o", exe] + llvm_ldflags +
            ["-lpthread", "-lm", str(args.hook)], args.timeout)
        if rc != 0 or to:
            r.update(status="link_timeout" if to else "link_fail",
                     err=first_line(se))
            return index, r

        r["instrument_s"] = inst_s + link_s

        # 4. run
        run_env = os.environ.copy()
        run_env["PTACXX_MODE"] = "1"
        run_env["PTACXX_K"] = str(args.k)
        run_env["PTACXX_DUMP_PATH"] = dump
        run_env["LD_LIBRARY_PATH"] = ":".join(filter(None, [
            str(llvm_prefix / "lib"), str(pathlib.Path(args.hook).parent)] +
            args.libcxx_lib + [run_env.get("LD_LIBRARY_PATH")]))
        rc, to, run_s, se = _run([exe], args.run_timeout, env=run_env)
        r["dynamic_run_s"] = run_s
        if to:
            r.update(status="run_timeout", err="timeout")
            return index, r
        if rc != 0:
            r.update(status=f"run_fail(rc={rc})",
                     err=first_line(se) or f"rc={rc}")
            return index, r

        pts = base.with_suffix(base.suffix + ".pts")
        r["pts_lines"] = (sum(1 for _ in pts.open(errors="replace"))
                          if pts.is_file() else 0)
        r.update(status="ok", err="")
        return index, r

    def report():
        nok = sum(1 for x in rows if x and x["status"] == "ok")
        print(f"{done}/{len(cases)} ok={nok}", flush=True)

    if args.jobs <= 1:
        for i, rel in enumerate(cases, 1):
            _, rows[i - 1] = process(i, rel)
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

    cols = ["caseId", "status", "err", "preprocess_s", "instrument_s",
            "dynamic_run_s", "ir_instr_orig", "ir_instr_mstar", "ir_size_ratio",
            "pts_lines"]
    def g(r, k, d=""):
        return r.get(k, d)
    with open(args.out_pts / "results.csv", "w", newline="") as f:
        w = csv.writer(f)
        w.writerow(cols)
        for r in sorted(rows, key=lambda x: x["caseId"]):
            w.writerow([
                r["caseId"], r["status"], r.get("err", ""),
                f"{r.get('preprocess_s', 0):.4f}",
                f"{r.get('instrument_s', 0):.4f}",
                f"{r.get('dynamic_run_s', 0):.4f}",
                g(r, "ir_instr_orig"), g(r, "ir_instr_mstar"),
                f"{r.get('ir_size_ratio', 0):.4f}", g(r, "pts_lines")])

    cnt = Counter(r["status"] for r in rows)
    oks = [r for r in rows if r["status"] == "ok"]

    def stats(key):
        xs = sorted(r[key] for r in oks if r.get(key) is not None)
        n = len(xs)
        return (sum(xs) / n, xs[0], xs[min(n - 1, int(n * 0.95))], xs[-1]) if n \
            else (0,) * 4

    pre, inst, run = stats("preprocess_s"), stats("instrument_s"), stats("dynamic_run_s")
    L = [f"# {args.name} pts dataset rebuilt from preprocessed IR (llvm14)", "",
         f"- analyzer: `{args.an}`", f"- cases: {len(rows)}",
         f"- pts root: `{args.out_pts}`", "", "## status", "",
         "| status | count |", "|---|---|"]
    for k, v in cnt.most_common():
        L.append(f"| {k} | {v} |")
    L += ["", "## time (s)", "", "| stage | mean | min | p95 | max |",
          "|---|---|---|---|---|",
          f"| preprocess | {pre[0]:.4f} | {pre[1]:.4f} | {pre[2]:.4f} | {pre[3]:.4f} |",
          f"| instrument | {inst[0]:.4f} | {inst[1]:.4f} | {inst[2]:.4f} | {inst[3]:.4f} |",
          f"| dynamic run | {run[0]:.4f} | {run[1]:.4f} | {run[2]:.4f} | {run[3]:.4f} |",
          "", f"- pts lines total: {sum(r.get('pts_lines', 0) for r in oks)}",
          f"- non-empty pts: {sum(1 for r in oks if r.get('pts_lines', 0))}",
          f"- ir size ratio (mstar/orig), mean: "
          f"{(sum(r.get('ir_size_ratio', 0) for r in oks) / len(oks)):.4f}"
          if oks else "", ""]
    (args.out_pts / "results.md").write_text("\n".join(L), encoding="utf-8")

    print("status:", dict(cnt))
    print("out:", args.out_pts / "results.csv")


if __name__ == "__main__":
    raise SystemExit(main())
