#!/usr/bin/env python3
"""Compare pts-test index result directories: one baseline A vs one or more fixes B.

Usage:
  ./evalIndex.py <A_dir> <B_dir> [B_dir ...] [-o out.csv]

The first directory is the baseline; every following directory is compared
against it (one 18-statistic block per pair). Each dir must contain
pts-test-normal.csv and pts-test-abnormal.csv.

The normal CSV is parsed by column POSITION (some baseline files have a wrong
header `name,class,detail` while the data is the 9-column normal format):
  name, arg_parse, ir_load, index, analysis, total, Pass, Fail, Unresolved

Direction: "up" = B - A > 0 (fix higher than baseline).

Reported statistics (18 per pair):
  - analysis / Pass / Fail / Unresolved, each over the COMMON-NORMAL set
    (names present in both normal tables), split into up/down by the sign of
    B-A. Each side reports mean and POPULATION variance of the ABSOLUTE
    magnitude (up: B-A>0; down: A-B>0). => 4 metrics x 2 dirs x 2 stats = 16
  - abnormal: set difference of abnormal case names:
      up   = newly abnormal (A normal -> B abnormal) = |B_abn - A_abn|
      down = eliminated   (A abnormal -> B normal)  = |A_abn - B_abn|
    => 2
"""

import argparse
import csv
import os
import sys

METRICS = ["analysis", "Pass", "Fail", "Unresolved"]
NORMAL_COLS = ["name", "arg_parse", "ir_load", "index", "analysis", "total",
               "Pass", "Fail", "Unresolved"]


def load_normal(path):
    """name -> {arg_parse, ir_load, index, analysis, total, Pass, Fail, Unresolved}."""
    out = {}
    with open(path, newline="") as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            parts = line.split(",")
            if parts[0] == "name":          # header (may be malformed)
                continue
            if len(parts) < len(NORMAL_COLS):
                continue
            out[parts[0]] = {
                "arg_parse": float(parts[1]),
                "ir_load": float(parts[2]),
                "index": float(parts[3]),
                "analysis": float(parts[4]),
                "total": float(parts[5]),
                "Pass": float(parts[6]),
                "Fail": float(parts[7]),
                "Unresolved": float(parts[8]),
            }
    return out


def load_abnormal(path):
    """name -> class."""
    out = {}
    with open(path, newline="") as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            parts = line.split(",", 2)
            if parts[0] == "name":
                continue
            out[parts[0]] = parts[1] if len(parts) > 1 else ""
    return out


def mean_var(xs):
    """mean and population variance (divide by n)."""
    if not xs:
        return None, None
    n = len(xs)
    m = sum(xs) / n
    v = sum((x - m) ** 2 for x in xs) / n
    return m, v


def updown(diffs):
    """split signed diffs into (up magnitudes, down magnitudes)."""
    up = [d for d in diffs if d > 0]
    down = [-d for d in diffs if d < 0]
    return up, down


def require(d):
    an = os.path.join(d, "pts-test-normal.csv")
    aa = os.path.join(d, "pts-test-abnormal.csv")
    for p in (an, aa):
        if not os.path.isfile(p):
            sys.exit(f"missing file: {p}")
    return an, aa


def compare(a_dir, b_dir):
    """Return (info, rows) for baseline a_dir vs fix b_dir."""
    an, aa = require(a_dir)
    bn, ba = require(b_dir)
    A, B = load_normal(an), load_normal(bn)
    A_abn, B_abn = load_abnormal(aa), load_abnormal(ba)
    common = sorted(set(A) & set(B))

    rows = []  # (metric, direction, mean, variance, n)
    for metric in METRICS:
        diffs = [B[n][metric] - A[n][metric] for n in common]
        up, down = updown(diffs)
        for direction, xs in (("up", up), ("down", down)):
            m, v = mean_var(xs)
            rows.append((metric, direction, m, v, len(xs)))

    rows.append(("abnormal", "up", float(len(set(B_abn) - set(A_abn))), None, None))
    rows.append(("abnormal", "down", float(len(set(A_abn) - set(B_abn))), None, None))

    info = dict(a_dir=a_dir, b_dir=b_dir,
                a_normal=len(A), a_abnormal=len(A_abn),
                b_normal=len(B), b_abnormal=len(B_abn),
                common=len(common))
    return info, rows


def print_block(info, rows):
    print(f"A (baseline): {info['a_dir']}  normal={info['a_normal']} abnormal={info['a_abnormal']}")
    print(f"B (fix):      {info['b_dir']}  normal={info['b_normal']} abnormal={info['b_abnormal']}")
    print(f"common normal: {info['common']}")
    hdr = f"{'metric':<12}{'dir':<6}{'mean':>16}{'variance':>18}{'n':>8}"
    print(hdr)
    print("-" * len(hdr))
    for metric, direction, m, v, n in rows:
        ms = f"{m:.4f}" if m is not None else "-"
        vs = f"{v:.4f}" if v is not None else "-"
        ns = f"{n}" if n is not None else "-"
        print(f"{metric:<12}{direction:<6}{ms:>16}{vs:>18}{ns:>8}")
    print()


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("dirs", nargs="+", metavar="DIR",
                    help="first = baseline, rest = fixes (each compared to baseline)")
    ap.add_argument("-o", "--out", default="eval_index.csv",
                    help="CSV output path (default: eval_index.csv)")
    args = ap.parse_args()
    if len(args.dirs) < 2:
        sys.exit("need at least one baseline dir and one fix dir")

    a_dir, b_dirs = args.dirs[0], args.dirs[1:]

    csv_rows = []
    for b_dir in b_dirs:
        info, rows = compare(a_dir, b_dir)
        print_block(info, rows)
        for metric, direction, m, v, n in rows:
            csv_rows.append([a_dir, b_dir, metric, direction,
                             "" if m is None else f"{m:.6f}",
                             "" if v is None else f"{v:.6f}",
                             "" if n is None else n])

    with open(args.out, "w", newline="") as f:
        w = csv.writer(f)
        w.writerow(["baseline", "fix", "metric", "direction", "mean", "variance", "n"])
        w.writerows(csv_rows)
    print(f"wrote {args.out}  ({len(b_dirs)} pair(s))")


if __name__ == "__main__":
    main()

