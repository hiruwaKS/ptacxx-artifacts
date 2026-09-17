#!/usr/bin/env python3
"""Compile blob/<ver>/*.ll to objects, link with stub, run and verify rc.

Usage:
    irCompile.py [-j N] [--blob DIR] [--version LABEL]
                 [--libcxx-lib DIR]... [--timeout SEC] [--recompile FILE]...
                 LLVM_PATH

For every .ll under blob/<ver>/{c,cpp,stl-libstdcxx,stl-libcxx}:
    1. clang++ -c <ll> -o <obj>              (object file)
    2. clang++ <obj> <stub.o> -o <exe>       (+ libc++ flags for stl-libcxx)
    3. run <exe>, rc == 0 means OK

The stub provides the analysis-only extern symbols (SAFE_LOAD, UNSAFE_LOAD,
nd_int, svf_print, set_value) so the programs can actually run.
"""

import argparse
import concurrent.futures
import os
import pathlib
import re
import subprocess
import sys
import threading
import time

SUBDIRS = ("c", "cpp", "stl-libstdcxx", "stl-libcxx")

STUB_SRC = r"""
#include <stdio.h>
void SAFE_LOAD(void *p) { printf("SAFE_LOAD(%p)\n", p); }
void UNSAFE_LOAD(void *p) { printf("UNSAFE_LOAD(%p)\n", p); }
int nd_int(void) { return 0; }
void svf_print(int v, char *name) { printf("%s: %d\n", name ? name : "?", v); }
void set_value(int v, int lo, int hi) { (void)lo; (void)hi; printf("set_value(%d)\n", v); }
"""


def resolve_cxx(llvm_path: pathlib.Path) -> str:
    if llvm_path.is_dir():
        cxx = llvm_path / "bin" / "clang++"
        if not cxx.exists():
            sys.exit(f"clang++ not found under: {llvm_path}")
        return str(cxx)
    return str(llvm_path)


def detect_version(cxx: str) -> str:
    try:
        out = subprocess.run(
            [cxx, "--version"], capture_output=True, text=True, errors="replace"
        ).stdout
    except OSError:
        return "unknown"
    m = re.search(r"clang version (\d+)", out)
    return f"llvm{m.group(1)}" if m else "unknown"


def build_stub(cxx: str, out: pathlib.Path):
    out.parent.mkdir(parents=True, exist_ok=True)
    cmd = [cxx, "-x", "c", "-c", "-", "-o", str(out)]
    p = subprocess.run(cmd, input=STUB_SRC, capture_output=True, text=True, errors="replace")
    if p.returncode != 0:
        sys.exit(f"failed to build stub:\n{p.stderr}")


def load_recompile(paths):
    forced = set()
    for path in paths:
        f = pathlib.Path(path)
        if not f.is_file():
            sys.exit(f"recompile list not found: {f}")
        for line in f.read_text(encoding="utf-8").splitlines():
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            forced.add(line)
            forced.add(pathlib.Path(line).name)
    return forced


def main():
    here = pathlib.Path(__file__).resolve().parent
    ap = argparse.ArgumentParser(description="Compile+link+run blob IR.")
    ap.add_argument("llvm_path", help="LLVM prefix or clang++ path")
    ap.add_argument("-j", "--jobs", type=int, default=0,
                    help="parallel jobs (default: CPU count)")
    ap.add_argument("--blob", type=pathlib.Path,
                    default=here / "d260917-suite" / "blob")
    ap.add_argument("--version", dest="label", default=None,
                    help="blob subdirectory label (default: llvm<major>)")
    ap.add_argument("--libcxx-lib", action="append", default=[],
                    metavar="DIR", help="libc++ library dir for stl-libcxx")
    ap.add_argument("--timeout", type=float, default=10.0,
                    help="per-executable run timeout in seconds")
    ap.add_argument("--recompile", action="append", default=[],
                    metavar="FILE",
                    help="only verify sources listed in FILE (repeatable)")
    args = ap.parse_args()

    cxx = resolve_cxx(pathlib.Path(args.llvm_path))
    label = args.label or detect_version(cxx)
    blob_root = args.blob / label
    run_root = blob_root / ".run"
    obj_root = run_root / "obj"
    exe_root = run_root / "exe"

    stub_obj = run_root / "stub.o"
    build_stub(cxx, stub_obj)

    link_libcxx = ["-stdlib=libc++"]
    for d in args.libcxx_lib:
        link_libcxx += ["-L", d, f"-Wl,-rpath,{d}"]

    forced = load_recompile(args.recompile)

    jobs = []
    for sub in SUBDIRS:
        d = blob_root / sub
        if not d.is_dir():
            continue
        for ll in sorted(p for p in d.rglob("*.ll") if p.is_file()):
            rel = ll.relative_to(blob_root)
            src_rel = str(rel)[:-3]
            if forced and src_rel not in forced and pathlib.Path(src_rel).name not in forced:
                continue
            obj = obj_root / (str(rel) + ".o")
            exe = exe_root / str(rel)[:-3]
            extra = link_libcxx if sub == "stl-libcxx" else []
            jobs.append((ll, rel, obj, exe, extra))

    print(f"cxx:    {cxx}")
    print(f"blob:   {blob_root}")
    print("stub:   embedded")
    print(f"jobs:   {len(jobs)}\n")
    if not jobs:
        print("nothing to do")
        return 0

    lock = threading.Lock()
    done = 0
    failed = []
    total = len(jobs)

    def run(job):
        t0 = time.monotonic()
        ll, rel, obj, exe, extra = job
        obj.parent.mkdir(parents=True, exist_ok=True)
        exe.parent.mkdir(parents=True, exist_ok=True)
        p = subprocess.run([cxx, "-c", str(ll), "-o", str(obj)],
                           capture_output=True, text=True, errors="replace")
        if p.returncode != 0:
            return job, "compile", p.stderr, time.monotonic() - t0
        p = subprocess.run([cxx, str(obj), str(stub_obj), "-o", str(exe)] + extra,
                           capture_output=True, text=True, errors="replace")
        if p.returncode != 0:
            return job, "link", p.stderr, time.monotonic() - t0
        try:
            r = subprocess.run([str(exe)], capture_output=True, text=True, errors="replace",
                               timeout=args.timeout)
        except subprocess.TimeoutExpired:
            return job, "timeout", "", time.monotonic() - t0
        except OSError as e:
            return job, "run", str(e), time.monotonic() - t0
        if r.returncode != 0:
            return job, f"rc={r.returncode}", r.stderr, time.monotonic() - t0
        return job, None, "", time.monotonic() - t0

    t_start = time.monotonic()
    timings = []
    workers = args.jobs if args.jobs > 0 else (os.cpu_count() or 1)
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as ex:
        futs = [ex.submit(run, j) for j in jobs]
        for fut in concurrent.futures.as_completed(futs):
            (ll, rel, obj, exe, extra), err, detail, dt = fut.result()
            with lock:
                done += 1
                pct = done * 100 // total
                timings.append((dt, str(rel)))
                if err is None:
                    print(f"[{pct:3d}%] OK   {rel} ({dt:.2f}s)")
                else:
                    failed.append((ll, rel, err, detail))
                    print(f"[{pct:3d}%] FAIL {rel} ({err}) ({dt:.2f}s)")
    elapsed = time.monotonic() - t_start

    logs = run_root / "logs"
    if failed:
        logs.mkdir(parents=True, exist_ok=True)
        for ll, rel, err, detail in failed:
            log = logs / (str(rel) + ".log")
            log.parent.mkdir(parents=True, exist_ok=True)
            log.write_text(f"stage: {err}\n\n{detail}", encoding="utf-8")

    times_file = run_root / "times.csv"
    times_file.parent.mkdir(parents=True, exist_ok=True)
    with times_file.open("w", encoding="utf-8") as f:
        f.write(f"# total\t{elapsed:.3f}\n")
        f.write("seconds\tfile\n")
        for dt, rel in sorted(timings, reverse=True):
            f.write(f"{dt:.3f}\t{rel}\n")

    print(f"\nverified ok={total - len(failed)} fail={len(failed)} "
          f"in {elapsed:.1f}s")
    slowest = sorted(timings, reverse=True)[:5]
    if slowest:
        print("slowest:")
        for dt, rel in slowest:
            print(f"  {dt:7.2f}s {rel}")
    print(f"times: {times_file}")
    if failed:
        print(f"failure logs: {logs}")
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
