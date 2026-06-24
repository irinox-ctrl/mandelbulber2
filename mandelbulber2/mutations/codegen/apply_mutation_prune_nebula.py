#!/usr/bin/env python3
"""
Wrap mutation switch cases in nebula.cl with compile-time pruning guards.

When MUTATION_PRUNE is defined, only cases with matching MUT_NEED_<TYPE>_<N>
defines are compiled. Pair with opencl_engine_render_fractal.cpp.

Idempotent: skips cases already wrapped.
"""

import re
import sys
from pathlib import Path

NEBULA = Path(__file__).resolve().parents[2] / "opencl" / "engines" / "nebula.cl"

SWITCH_PREFIX = {
    "mut->inversionType": "MUT_NEED_INVERSIONTYPE",
    "mut->foldType": "MUT_NEED_FOLDTYPE",
    "mut->swizzle": "MUT_NEED_SWIZZLE",
    "mut->mathType": "MUT_NEED_MATHTYPE",
    "mut->clipType": "MUT_NEED_CLIPTYPE",
    "mut->clampType": "MUT_NEED_CLAMPTYPE",
    "mut->jbType": "MUT_NEED_JBTYPE",
    "mut->mdType": "MUT_NEED_MDTYPE",
}

CASE_RE = re.compile(r"^(\s*)case\s+(-?\d+)\s*:")
IF_GUARD_RE = re.compile(r"^#if\s+!defined\(MUTATION_PRUNE\)")


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
    """Return (body_lines, next_index) for one case starting at case_line_idx."""
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


def main():
    path = NEBULA
    if len(sys.argv) > 1:
        path = Path(sys.argv[1])
    text = path.read_text(errors="replace")
    new_text = process(text)
    if new_text == text:
        print(f"No changes needed in {path}")
        return 0
    path.write_text(new_text)
    print(f"Updated {path} with mutation prune guards")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
