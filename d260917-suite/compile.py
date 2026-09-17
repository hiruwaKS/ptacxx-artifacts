#!/usr/bin/env python3
"""Compile d260917-suite sources to LLVM IR (.ll) under blob/.

Usage:
    compile.py [-j N] [--src DIR] [--blob DIR] [--version LABEL]
               [--libcxx PREFIX] [--recompile FILE]... LLVM_PATH

LLVM_PATH is either an LLVM prefix (e.g. /usr/lib/llvm-14) or a clang++
executable. The version label defaults to llvm<major> parsed from clang.

Mapping:
    source/c                      -> blob/<ver>/c            (clang -x c, per-file std)
    source/cpp                    -> blob/<ver>/cpp          (clang++ -std=c++20)
    source/cpp-std-impl-sensitive -> blob/<ver>/stl-libstdcxx
                                     blob/<ver>/stl-libcxx    (--libcxx)

Every output has a command manifest under blob/<ver>/.cache/. A file is
recompiled when its output is missing, the source is newer, the command
changed (e.g. a flag was added), or it is named in --recompile FILE.
"""

import argparse
import concurrent.futures
import os
import pathlib
import re
import subprocess
import sys
import threading

SENSITIVE = "cpp-std-impl-sensitive"
CPP_STD = "c++20"
C_STD_PREFIXES = ("c89", "c90", "c99", "c11", "c17", "c23")
C_STD_DEFAULT = "c11"
SEP = "\x1f"


def c_std(name: str) -> str:
    for pref in C_STD_PREFIXES:
        if name.startswith(pref + "-"):
            return pref
    return C_STD_DEFAULT


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
            [cxx, "--version"], capture_output=True, text=True
        ).stdout
    except OSError:
        return "unknown"
    m = re.search(r"clang version (\d+)", out)
    return f"llvm{m.group(1)}" if m else "unknown"


def resolve_libcxx(paths):
    dirs = []
    for path in paths:
        root = pathlib.Path(path)
        found = [c for c in (root, root / "include" / "c++" / "v1")
                 if (c / "vector").is_file()]
        if not found:
            sys.exit(
                f"libc++ headers not found under: {root}\n"
                f"pass the libc++ include dir or an LLVM prefix via --libcxx"
            )
        for inc in found:
            if str(inc) not in dirs:
                dirs.append(str(inc))
            inc_root = inc.parent.parent
            if inc_root.is_dir():
                for sib in sorted(inc_root.glob("*/c++/v1")):
                    if sib != inc and (sib / "__config_site").is_file():
                        if str(sib) not in dirs:
                            dirs.append(str(sib))
    flags = ["-nostdinc++"]
    for d in dirs:
        flags += ["-isystem", d]
    return dirs, flags


def load_recompile(paths, src_root: pathlib.Path):
    forced = set()
    for path in paths:
        f = pathlib.Path(path)
        if not f.is_file():
            sys.exit(f"recompile list not found: {f}")
        for line in f.read_text(encoding="utf-8").splitlines():
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            q = pathlib.Path(line)
            forced.add(q.name)
            try:
                forced.add(str(q.resolve().relative_to(src_root.resolve())))
            except ValueError:
                pass
    return forced


def collect_jobs(src_root: pathlib.Path, blob_root: pathlib.Path, cxx: str,
                 libcxx_flags, forced):
    jobs = []

    def add(src: pathlib.Path, out_dir: pathlib.Path, lang, std, extra):
        out = out_dir / (src.name + ".ll")
        rel = str(out.relative_to(blob_root))
        is_forced = src.name in forced or str(src.relative_to(src_root)) in forced
        cmd = [cxx, "-x", lang, str(src), f"-std={std}", "-emit-llvm", "-S",
               "-g", "-O0"]
        cmd += extra + ["-o", str(out)]
        jobs.append((src, out, rel, is_forced, cmd))

    d = src_root / "c"
    if d.is_dir():
        for src in sorted(p for p in d.rglob("*") if p.is_file()):
            add(src, blob_root / "c", "c", c_std(src.name), [])

    d = src_root / "cpp"
    if d.is_dir():
        for src in sorted(p for p in d.rglob("*") if p.is_file()):
            add(src, blob_root / "cpp", "c++", CPP_STD, [])

    d = src_root / SENSITIVE
    if d.is_dir():
        for src in sorted(p for p in d.rglob("*") if p.is_file()):
            add(src, blob_root / "stl-libstdcxx", "c++", CPP_STD, [])
            add(src, blob_root / "stl-libcxx", "c++", CPP_STD, libcxx_flags)

    return jobs


def main():
    here = pathlib.Path(__file__).resolve().parent
    ap = argparse.ArgumentParser(description="Compile d260917-suite to LLVM IR.")
    ap.add_argument("llvm_path", help="LLVM prefix or clang++ path")
    ap.add_argument("-j", "--jobs", type=int, default=0,
                    help="parallel jobs (default: CPU count)")
    ap.add_argument("--src", type=pathlib.Path,
                    default=here / "d260917-suite" / "source")
    ap.add_argument("--blob", type=pathlib.Path,
                    default=here / "d260917-suite" / "blob")
    ap.add_argument("--version", dest="label", default=None,
                    help="blob subdirectory label (default: llvm<major>)")
    ap.add_argument("--libcxx", required=True, action="append",
                    metavar="DIR",
                    help="libc++ include dir or LLVM prefix for stl-libcxx "
                         "(repeatable)")
    ap.add_argument("--recompile", action="append", default=[],
                    metavar="FILE",
                    help="file listing sources to force recompile (repeatable)")
    args = ap.parse_args()

    cxx = resolve_cxx(pathlib.Path(args.llvm_path))
    label = args.label or detect_version(cxx)
    blob_root = args.blob / label
    cache_root = blob_root / ".cache"

    for sub in ("c", "cpp", "stl-libstdcxx", "stl-libcxx"):
        (blob_root / sub).mkdir(parents=True, exist_ok=True)

    forced = load_recompile(args.recompile, args.src)
    libcxx_dirs, libcxx_flags = resolve_libcxx(args.libcxx)

    print(f"cxx:    {cxx}")
    print(f"cpp std: {CPP_STD}")
    print(f"src:    {args.src}")
    print(f"blob:   {blob_root}")
    print(f"libcxx: {', '.join(libcxx_dirs)}")
    if args.recompile:
        print(f"recompile lists: {', '.join(args.recompile)}")

    jobs = collect_jobs(args.src, blob_root, cxx, libcxx_flags, forced)

    def cache_file(rel):
        return cache_root / (rel + ".cmd")

    pending = []
    skipped = 0
    for src, out, rel, is_forced, cmd in jobs:
        desired = SEP.join(cmd)
        cf = cache_file(rel)
        reason = None
        if is_forced:
            reason = "listed"
        elif not out.exists():
            reason = "missing"
        elif not cf.exists():
            reason = "no manifest"
        elif cf.read_text(encoding="utf-8") != desired:
            reason = "cmd changed"
        elif out.stat().st_mtime < src.stat().st_mtime:
            reason = "src newer"
        if reason is None:
            skipped += 1
        else:
            pending.append((src, out, rel, cmd, reason))

    print(f"jobs:   {len(jobs)} (compile: {len(pending)}, skip: {skipped})\n")
    if not pending:
        print("nothing to do")
        return 0

    lock = threading.Lock()
    done = 0
    failed = []
    total = len(pending)

    def run(item):
        src, out, rel, cmd, reason = item
        try:
            p = subprocess.run(cmd, capture_output=True, text=True)
        except OSError as e:
            return item, 1, str(e)
        return item, p.returncode, p.stderr

    workers = args.jobs if args.jobs > 0 else (os.cpu_count() or 1)
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as ex:
        futs = [ex.submit(run, j) for j in pending]
        for fut in concurrent.futures.as_completed(futs):
            (src, out, rel, cmd, reason), rc, err = fut.result()
            cf = cache_file(rel)
            if rc == 0:
                cf.parent.mkdir(parents=True, exist_ok=True)
                cf.write_text(SEP.join(cmd), encoding="utf-8")
            with lock:
                done += 1
                pct = done * 100 // total
                if rc == 0:
                    print(f"[{pct:3d}%] OK   {rel}")
                else:
                    failed.append((src, rel, err))
                    print(f"[{pct:3d}%] FAIL {rel}")

    recompile_txt = blob_root / "recompile.txt"
    if failed:
        lines = sorted({str(src.relative_to(args.src)) for src, _, _ in failed})
        recompile_txt.write_text("\n".join(lines) + "\n", encoding="utf-8")
        logs = blob_root / "logs"
        logs.mkdir(parents=True, exist_ok=True)
        for src, rel, err in failed:
            (logs / (pathlib.Path(rel).name + ".log")).write_text(
                f"source: {src}\n\n{err}", encoding="utf-8"
            )
    elif recompile_txt.exists():
        recompile_txt.unlink()

    print(f"\ncompiled ok={total - len(failed)} fail={len(failed)} "
          f"skip={skipped}")
    if failed:
        print(f"recompile list: {recompile_txt}")
        print(f"failure logs:   {blob_root / 'logs'}")
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
