#!/usr/bin/env python3
"""
Wrap mutation switch cases in OpenCL engine .cl files with compile-time pruning guards.

When MUTATION_PRUNE is defined, only cases with matching MUT_NEED_<TYPE>_<N>
defines are compiled. Pair with opencl_mutation_defines.cpp.

Usage:
    python3 apply_mutation_prune_cl.py
    python3 apply_mutation_prune_cl.py opencl/engines/compute_fractal.cl
"""

import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]

# switch(var) -> MUT_NEED_* prefix (must match opencl_mutation_defines.cpp)
SWITCH_PREFIX = {
    "mut->inversionType": "MUT_NEED_INVERSIONTYPE",
    "mut->foldType": "MUT_NEED_FOLDTYPE",
    "mut->swizzle": "MUT_NEED_SWIZZLE",
    "mut->mathType": "MUT_NEED_MATHTYPE",
    "mut->clipType": "MUT_NEED_CLIPTYPE",
    "mut->clampType": "MUT_NEED_CLAMPTYPE",
    "mut->jbType": "MUT_NEED_JBTYPE",
    "mut->mdType": "MUT_NEED_MDTYPE",
    "mut->josLeysDeType": "MUT_NEED_JOSLEYSDETYPE",
    "mut->pseudoKleinianDeType": "MUT_NEED_PKDETYPE",
    "mut->mbMathType": "MUT_NEED_MBMATHTYPE",
    "mut->warpDistType": "MUT_NEED_WARPDISTTYPE",
    "mut->symKalType": "MUT_NEED_SYMKALTYPE",
    "mut->aboxType": "MUT_NEED_ABOXTYPE",
    "mut->noiseType": "MUT_NEED_NOISETYPE",
    "mut->orbitTrapType": "MUT_NEED_ORBITTRAPTYPE",
    "mut->torusType": "MUT_NEED_TORUSTYPE",
    "mut->asType": "MUT_NEED_ASTYPE",
    "mut->smType": "MUT_NEED_SMTYPE",
    "mut->blockifyType": "MUT_NEED_BLOCKIFYTYPE",
    "mut->tileType": "MUT_NEED_TILETYPE",
}

DEFAULT_FILES = [
    ROOT / "opencl/engines/nebula.cl",
    ROOT / "opencl/engines/compute_fractal.cl",
]

CASE_RE = re.compile(r"^(\s*)case\s+(-?\d+)\s*:")
IF_GUARD_RE = re.compile(r"^#if\s+!defined\(MUTATION_PRUNE\)")
ENDIF_RE = re.compile(r"^#endif\s*$")


def dedupe_prune_guards(text: str) -> str:
    """Remove duplicate consecutive MUTATION_PRUNE guard pairs from a previous run."""
    lines = text.splitlines(keepends=True)
    out = []
    i = 0
    while i < len(lines):
        line = lines[i]
        if IF_GUARD_RE.match(line.strip()) and i + 1 < len(lines) and IF_GUARD_RE.match(
            lines[i + 1].strip()
        ):
            out.append(line)
            i += 2
            continue
        if ENDIF_RE.match(line.strip()) and i + 1 < len(lines) and ENDIF_RE.match(lines[i + 1].strip()):
            out.append(line)
            i += 2
            continue
        out.append(line)
        i += 1
    return "".join(out)


def find_switch_end(lines, start_idx):
    brace_i = start_idx
    while brace_i < len(lines):
        if "{" in lines[brace_i]:
            break
        brace_i += 1
    if brace_i >= len(lines):
        return start_idx

    depth = 0
    for j in range(brace_i, len(lines)):
        for ch in lines[j]:
            if ch == "{":
                depth += 1
            elif ch == "}":
                depth -= 1
        if depth == 0 and j >= brace_i:
            return j
    return len(lines) - 1


def consume_case(lines, case_line_idx, end_idx):
    depth = 0
    case_line = lines[case_line_idx]
    depth += case_line.count("{") - case_line.count("}")

    body = [case_line]
    i = case_line_idx + 1
    while i <= end_idx:
        line = lines[i]
        body.append(line)
        depth += line.count("{") - line.count("}")
        if "break" in line and depth <= 0:
            return body, i + 1
        if "break" in line and depth == 1:
            j = i + 1
            while j <= end_idx and lines[j].strip() == "":
                body.append(lines[j])
                j += 1
            if j <= end_idx and lines[j].strip() == "}":
                body.append(lines[j])
                return body, j + 1
            return body, i + 1
        i += 1
    return body, i


def wrap_switch(lines, start_idx, end_idx, prefix):
    out = []
    i = start_idx
    while i <= end_idx:
        line = lines[i]
        if IF_GUARD_RE.match(line.strip()):
            out.append(line)
            i += 1
            continue

        m = CASE_RE.match(line)
        if m:
            if out and IF_GUARD_RE.match(out[-1].strip()):
                out.append(line)
                i += 1
                continue
            case_num = m.group(2)
            body, next_i = consume_case(lines, i, end_idx)
            out.append(f"#if !defined(MUTATION_PRUNE) || defined({prefix}_{case_num})\n")
            out.extend(body)
            out.append("#endif\n")
            i = next_i
            continue

        out.append(line)
        i += 1
    return out


def process(text):
    lines = text.splitlines(keepends=True)
    switch_re = re.compile(r"\bswitch\s*\(\s*(mut->\w+)\s*\)")

    i = 0
    result = []
    while i < len(lines):
        m = switch_re.search(lines[i])
        if m:
            var = m.group(1)
            prefix = SWITCH_PREFIX.get(var)
            if prefix:
                end = find_switch_end(lines, i)
                block = lines[i : end + 1]
                wrapped = wrap_switch(block, 0, len(block) - 1, prefix)
                result.extend(wrapped)
                i = end + 1
                continue
        result.append(lines[i])
        i += 1
    return "".join(result)


def process_file(path: Path) -> bool:
    text = dedupe_prune_guards(path.read_text(errors="replace"))
    new_text = dedupe_prune_guards(process(text))
    if new_text == text:
        print(f"No changes needed: {path}")
        return False
    path.write_text(new_text)
    print(f"Updated {path} with mutation prune guards")
    return True


def sync_copies(src: Path):
    for rel in (
        "share/mandelbulber2/opencl/engines",
        "deploy/share/mandelbulber2/opencl/engines",
    ):
        dst_dir = ROOT / rel
        dst_dir.mkdir(parents=True, exist_ok=True)
        dst = dst_dir / src.name
        dst.write_text(src.read_text(errors="replace"))
        print(f"Synced -> {dst}")


def main():
    paths = [Path(p) for p in sys.argv[1:]] if len(sys.argv) > 1 else DEFAULT_FILES
    changed = False
    for path in paths:
        if not path.is_absolute():
            path = ROOT / path
        if not path.exists():
            print(f"SKIP missing: {path}")
            continue
        if process_file(path):
            changed = True
            sync_copies(path)
    return 0 if changed or not paths else 0


if __name__ == "__main__":
    raise SystemExit(main())
