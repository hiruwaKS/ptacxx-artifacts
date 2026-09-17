#!/usr/bin/env python3
"""Instrument LLVM IR and generate dynamic points-to dumps.

Per .ll input, the pipeline is:
    <ll>            --instrument-->  <out>.inst.bc
    <out>.inst.bc   --clang+++hook--> <out>.inst
    <out>.inst      --run-->         <ll>.pts

Usage:
    instrument.py LLVM_PATH --instrument PATH --hook PATH
                  [--src DIR] [--blob DIR] [--list FILE]...
                  [-j N] [--timeout SEC]

LLVM_PATH is either an LLVM prefix (e.g. /usr/lib/llvm-14) or a clang++
executable. --src is a tree of .ll files (default: the matching
d260917-suite/blob/<version>). Outputs mirror the input tree under
--blob/<version>, e.g. cpp/foo.cpp.ll -> blob/llvm14/cpp/foo.cpp.ll.inst.

--list restricts processing to the files named in it (repeatable). Each
line may be an absolute path, a path relative to --src, or a basename.
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


MODE_BITS = {"-mode-ptr": 1, "-mode-bb": 2, "-mode-cg": 4}


def mode_mask(mode_str: str) -> int:
    m = 0
    for flag in mode_str.split():
        m |= MODE_BITS.get(flag, 0)
    return m


def resolve_cxx(llvm_path: pathlib.Path) -> str:
    if llvm_path.is_dir():
        cxx = llvm_path / "bin" / "clang++"
        if not cxx.exists():
            sys.exit(f"clang++ not found under: {llvm_path}")
        return str(cxx)
    return str(llvm_path)


def detect_version(cxx: str) -> str:
    try:
        out = subprocess.run([cxx, "--version"], capture_output=True, text=True,
                             errors="replace").stdout
    except OSError:
        return "unknown"
    m = re.search(r"clang version (\d+)", out)
    return f"llvm{m.group(1)}" if m else "unknown"


def load_list(paths, src_root: pathlib.Path):
    wanted = set()
    for path in paths:
        f = pathlib.Path(path)
        if not f.is_file():
            sys.exit(f"list file not found: {f}")
        for line in f.read_text(encoding="utf-8").splitlines():
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            q = pathlib.Path(line)
            wanted.add(line)
            wanted.add(q.name)
            try:
                wanted.add(str(q.resolve().relative_to(src_root.resolve())))
            except ValueError:
                pass
    return wanted


def collect_sources(src_root: pathlib.Path, wanted):
    if not src_root.is_dir():
        sys.exit(f"source dir not found: {src_root}")
    jobs = []
    for src in sorted(p for p in src_root.rglob("*.ll") if p.is_file()):
        if wanted:
            rel = src.relative_to(src_root)
            if (str(src.resolve()) not in wanted
                    and str(rel) not in wanted
                    and rel.as_posix() not in wanted
                    and src.name not in wanted):
                continue
        jobs.append(src)
    return jobs


def main():
    here = pathlib.Path(__file__).resolve().parent
    ap = argparse.ArgumentParser(description="Instrument IR and dump points-to.")
    ap.add_argument("llvm_path", help="LLVM prefix or clang++ path")
    ap.add_argument("--instrument", required=True, metavar="PATH",
                    help="path to the instrument binary")
    ap.add_argument("--hook", required=True, metavar="PATH",
                    help="path to libhook.so")
    ap.add_argument("--src", type=pathlib.Path, default=None,
                    help="tree of .ll inputs (default: d260917-suite/blob/<ver>)")
    ap.add_argument("--blob", type=pathlib.Path, default=here / "blob",
                    help="output root (default: d260917-pts/blob)")
    ap.add_argument("--label", default=None,
                    help="output version subdir (default: llvm<major>)")
    ap.add_argument("--list", action="append", default=[], metavar="FILE",
                    help="file listing .ll files to process (repeatable)")
    ap.add_argument("--libcxx-lib", action="append", default=[], metavar="DIR",
                    help="libc++ library dir for stl-libcxx inputs (repeatable)")
    ap.add_argument("--mode", default="-mode-ptr", help="instrument mode flag")
    ap.add_argument("--k", type=int, default=0, help="PTACXX_K (default: 0)")
    ap.add_argument("-j", "--jobs", type=int, default=0,
                    help="parallel jobs (default: CPU count)")
    ap.add_argument("--timeout", type=float, default=30.0,
                    help="per-executable run timeout in seconds")
    args = ap.parse_args()

    cxx = resolve_cxx(pathlib.Path(args.llvm_path))
    llvm_prefix = pathlib.Path(cxx).resolve().parent.parent
    llvm_config = llvm_prefix / "bin" / "llvm-config"
    hook = pathlib.Path(args.hook).resolve()
    instrument = pathlib.Path(args.instrument).resolve()

    label = args.label or detect_version(cxx)
    src_root = args.src or (here.parent / "d260917-suite" / "blob" / label)
    blob_root = args.blob / label

    wanted = load_list(args.list, src_root)
    sources = collect_sources(src_root, wanted)

    print(f"cxx:        {cxx}")
    print(f"llvm:       {llvm_prefix}")
    print(f"instrument: {instrument}")
    print(f"hook:       {hook}")
    print(f"src:        {src_root}")
    print(f"blob:       {blob_root}")
    print(f"jobs:       {len(sources)}\n")
    if not sources:
        print("nothing to do")
        return 0

    try:
        llvm_ldflags = subprocess.run(
            [str(llvm_config), "--libs", "--system-libs", "--ldflags"],
            capture_output=True, text=True, check=True).stdout.split()
    except (OSError, subprocess.CalledProcessError) as e:
        sys.exit(f"failed to query llvm-config: {e}")

    lock = threading.Lock()
    done = 0
    failed = []
    results = []
    total = len(sources)

    results_csv = blob_root / "results.csv"
    results_csv.parent.mkdir(parents=True, exist_ok=True)
    rf = results_csv.open("w", encoding="utf-8")
    rf.write("file\tstatus\tstage\tseconds\n")
    rf.flush()

    instrument_log = blob_root / "instrument.log"
    log_lock = threading.Lock()

    def run_pipeline(src):
        t0 = time.monotonic()
        try:
            rel = src.relative_to(src_root)
        except ValueError:
            rel = pathlib.Path(src.name)
        base = blob_root / rel
        bc = str(base) + ".inst.bc"
        exe = str(base) + ".inst"
        dump = str(base)
        base.parent.mkdir(parents=True, exist_ok=True)

        libcxx_flags = []
        if args.libcxx_lib and "stl-libcxx" in rel.parts:
            libcxx_flags = ["-stdlib=libc++"]
            for d in args.libcxx_lib:
                libcxx_flags += ["-L", d, f"-Wl,-rpath,{d}"]

        env = os.environ.copy()
        env["LD_LIBRARY_PATH"] = str(llvm_prefix / "lib") + (
            ":" + env["LD_LIBRARY_PATH"] if env.get("LD_LIBRARY_PATH") else "")
        p = subprocess.run([str(instrument), str(src), "-o", bc, args.mode],
                           capture_output=True, text=True, errors="replace",
                           env=env)
        with log_lock:
            with instrument_log.open("a", encoding="utf-8") as lf:
                lf.write(f"=== {rel} rc={p.returncode} ===\n")
                if p.stdout:
                    lf.write("[stdout]\n")
                    lf.write(p.stdout)
                if p.stderr:
                    lf.write("[stderr]\n")
                    lf.write(p.stderr)
                lf.write("\n")
        if p.returncode != 0:
            return src, "instrument", p.stderr, time.monotonic() - t0

        link = [cxx] + libcxx_flags + [bc, "-o", exe] + llvm_ldflags + \
            ["-lpthread", "-lm", str(hook)]
        p = subprocess.run(link, capture_output=True, text=True, errors="replace")
        if p.returncode != 0:
            return src, "link", p.stderr, time.monotonic() - t0

        run_env = os.environ.copy()
        run_env["PTACXX_MODE"] = str(mode_mask(args.mode))
        run_env["PTACXX_K"] = str(args.k)
        run_env["PTACXX_DUMP_PATH"] = dump
        run_env["LD_LIBRARY_PATH"] = ":".join(filter(None, [
            str(llvm_prefix / "lib"), str(hook.parent)] + args.libcxx_lib +
            [run_env.get("LD_LIBRARY_PATH")]))
        try:
            p = subprocess.run([exe], capture_output=True, text=True,
                               errors="replace", env=run_env,
                               timeout=args.timeout)
        except subprocess.TimeoutExpired:
            return src, "timeout", "", time.monotonic() - t0
        except OSError as e:
            return src, "run", str(e), time.monotonic() - t0
        if p.returncode != 0:
            return src, f"rc={p.returncode}", p.stderr, time.monotonic() - t0
        return src, None, "", time.monotonic() - t0

    t_start = time.monotonic()
    workers = args.jobs if args.jobs > 0 else (os.cpu_count() or 1)
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as ex:
        futs = [ex.submit(run_pipeline, s) for s in sources]
        for fut in concurrent.futures.as_completed(futs):
            src, err, detail, dt = fut.result()
            with lock:
                done += 1
                pct = done * 100 // total
                rel = src.relative_to(src_root)
                status = "ok" if err is None else "fail"
                results.append((str(rel), status, err or "", dt))
                rf.write(f"{rel}\t{status}\t{err or ''}\t{dt:.3f}\n")
                rf.flush()
                if err is None:
                    print(f"[{pct:3d}%] OK   {rel} ({dt:.2f}s)")
                else:
                    failed.append((src, err, detail))
                    print(f"[{pct:3d}%] FAIL {rel} ({err}) ({dt:.2f}s)")
    elapsed = time.monotonic() - t_start

    if failed:
        logs = blob_root / "logs"
        logs.mkdir(parents=True, exist_ok=True)
        for src, err, detail in failed:
            rel = src.relative_to(src_root)
            log = logs / (str(rel) + ".log")
            log.parent.mkdir(parents=True, exist_ok=True)
            log.write_text(f"stage: {err}\n\n{detail}", encoding="utf-8")

    rf.close()
    with results_csv.open("w", encoding="utf-8") as f:
        f.write(f"# total\t{elapsed:.3f}\n")
        f.write("file\tstatus\tstage\tseconds\n")
        for rel, status, stage, dt in sorted(results):
            f.write(f"{rel}\t{status}\t{stage}\t{dt:.3f}\n")

    print(f"\ninstrumented ok={total - len(failed)} fail={len(failed)} "
          f"in {elapsed:.1f}s")
    print(f"results: {results_csv}")
    if failed:
        print(f"failure logs: {blob_root / 'logs'}")
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
