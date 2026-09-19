#!/usr/bin/env python3
"""Run all (or selected) analyzer indices from report.md Appendix B against the
unified 921-case pts set, writing blob/<label>/<index>/pts-test-{normal,abnormal}.csv.

The Python replacement for runIndexes.sh: runPtsTest.py takes over the
escalating-timeout logic (--timeout 1 4 16). A case is re-run at the next,
larger timeout only if it timed out at the previous tier, and is recorded as a
timeout only if it times out at every tier; cases that pass or crash at a
smaller timeout are never re-run.

Usage:
  ./runIndexes.py <label>            # all 25 indices
  ./runIndexes.py baseline 1 3 9     # only the listed indices

Env:
  AN_DIR=<dir>          REQUIRED: dir with lotus-{aa,tpa,...} binaries
  LOTUS_CONFIG_DIR=<dir> REQUIRED: dir containing ptr.spec / modref.spec
  JOBS=4 VERSION=llvm14 TIMEOUTS="1 4 16"
"""

import csv
import fcntl
import os
import pathlib
import sys

import runPtsTest

HERE = pathlib.Path(__file__).resolve().parent
ART = HERE.parent

AN_DIR = os.environ.get("AN_DIR")
if not AN_DIR:
    sys.exit("AN_DIR is not set (dir containing lotus-aa, lotus-tpa, ...)")
LOTUS_CONFIG_DIR = os.environ.get("LOTUS_CONFIG_DIR")
if not LOTUS_CONFIG_DIR:
    sys.exit("LOTUS_CONFIG_DIR is not set (dir containing ptr.spec / modref.spec)")

JOBS = int(os.environ.get("JOBS", "4"))
VERSION = os.environ.get("VERSION", "llvm14")
TIMEOUTS = [float(t.strip()) for t in os.environ.get("TIMEOUTS", "1 4 16").split()]

PTS_ROOT = pathlib.Path(os.environ.get("PTS_ROOT", ART / "d260917-pts" / "blob" / VERSION))
SUITE_ROOT = pathlib.Path(os.environ.get("SUITE_ROOT", ART / "d260917-suite" / "blob" / VERSION))

if len(sys.argv) < 2:
    sys.exit("usage: runIndexes.py <label> [index ...]")
LABEL = sys.argv[1]
selected = sys.argv[2:]

SPECS = [
    (1, "lotus-aa", []),
    (2, "lotus-tpa", ["--k-limit=0"]),
    (3, "lotus-sparrow-aa", ["--andersen-k-cs=0"]),
    (4, "lotus-sparrow-aa", ["--andersen-k-cs=0", "--andersen-use-bdd-pts"]),
    (5, "lotus-sparrow-aa", ["--andersen-k-cs=0", "--enable-hcd"]),
    (6, "lotus-sparrow-aa", ["--andersen-k-cs=0", "--enable-hu"]),
    (7, "lotus-sparrow-aa", ["--andersen-k-cs=0", "--enable-hvn"]),
    (8, "lotus-sparrow-aa", ["--andersen-k-cs=0", "--enable-lcd"]),
    (9, "lotus-aser-aa", ["--analysis-mode=ci"]),
    (10, "lotus-aser-aa", ["--analysis-mode=ci", "--solver=basic"]),
    (11, "lotus-aser-aa", ["--analysis-mode=ci", "--solver=deep"]),
    (12, "lotus-aser-aa", ["--analysis-mode=ci", "--field-sensitive=false"]),
    (13, "lotus-aser-aa", ["--analysis-mode=ci", "--pta-use-bdd-pts"]),
    (14, "lotus-un-dyckaa", []),
    (15, "lotus-un-dyckaa", ["--dyckaa-inter-iteration=10"]),
    (16, "lotus-un-dyckaa", ["--function-type-check-level=0"]),
    (17, "lotus-un-dyckaa", ["--with-function-cast-comb"]),
    (18, "lotus-un-dyckaa", ["--nworkers=4"]),
]

lock_path = HERE / ".runIndexes.lock"
lock_fd = lock_path.open("a+")
try:
    fcntl.flock(lock_fd, fcntl.LOCK_EX | fcntl.LOCK_NB)
except OSError:
    sys.exit(f"another runIndexes.py is already running (lock: {lock_path}); aborting")

fmt_timeouts = " ".join(str(t) for t in TIMEOUTS)
print(f"label={LABEL} version={VERSION} jobs={JOBS} timeouts={fmt_timeouts}")

for idx, bin, extra in SPECS:
    if selected and str(idx) not in selected:
        continue
    analyzer = pathlib.Path(AN_DIR) / bin
    if not analyzer.is_file() or not os.access(analyzer, os.X_OK):
        print(f"!! [{idx}] missing analyzer: {analyzer}", file=sys.stderr)
        sys.exit(1)
    out = HERE / "blob" / LABEL / str(idx)
    print(f"===== [{idx}] {bin} {' '.join(extra)} -> {out}")
    rc = runPtsTest.run_batch(
        str(analyzer),
        pts_root=PTS_ROOT, suite_root=SUITE_ROOT,
        out_dir=out, config_dir=LOTUS_CONFIG_DIR,
        jobs=JOBS, timeouts=TIMEOUTS[:],
        analyzer_args=extra,
    )
    if rc != 0:
        print(f"!! [{idx}] run_batch returned {rc}", file=sys.stderr)
        sys.exit(rc)