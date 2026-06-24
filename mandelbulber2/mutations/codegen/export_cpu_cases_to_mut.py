#!/usr/bin/env python3
"""
Export CPU mutation switch cases to .mut pilot files.

Reads compute_fractal.cpp clip / inversion switches and writes
mutations/systems/<system>/type_NNN_<slug>.mut with parameter aliases.

Usage:
    python3 export_cpu_cases_to_mut.py --system clip
    python3 export_cpu_cases_to_mut.py --system inversion
    python3 export_cpu_cases_to_mut.py --all
    python3 export_cpu_cases_to_mut.py --all --force   # overwrite existing
"""

from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path
from typing import Dict, List, Tuple

ROOT = Path(__file__).resolve().parent.parent.parent
CPU_FILE = ROOT / "src" / "compute_fractal.cpp"
SYSTEMS_DIR = ROOT / "mutations" / "systems"

SYSTEM_CONFIG = {
    "clip": {
        "switch": r"switch\s*\(\s*mut\.clipType\s*\)",
        "system_name": "clip",
        "aliases": [
            (r"\bmut\.clipSizeX\b", "Sx"),
            (r"\bmut\.clipSizeY\b", "Sy"),
            (r"\bmut\.clipSizeZ\b", "Sz"),
            (r"\bmut\.clipRadius\b", "CR"),
            (r"\bmut\.clipMajorRadius\b", "MR"),
            (r"\bmut\.clipParamA\b", "PA"),
            (r"\bmut\.clipParamB\b", "PB"),
            (r"\bmut\.clipParamC\b", "PC"),
            (r"\bmut\.clipAngle\b", "ANG"),
            (r"\bmut\.clipAmplitude\b", "AMP"),
            (r"\bmut\.clipFrequency\b", "FREQ"),
            (r"\bmut\.clipSmoothK\b", "K"),
            (r"\bmut\.clipNPoints\b", "NPTS"),
            (r"\bsx\b", "Sx"),
            (r"\bsy\b", "Sy"),
            (r"\bsz\b", "Sz"),
            (r"\bcr\b", "CR"),
            (r"\bcR\b", "MR"),
            (r"\bca\b", "PA"),
            (r"\bcb\b", "PB"),
            (r"\bcc\b", "PC"),
        ],
    },
    "inversion": {
        "switch": r"switch\s*\(\s*mut\.inversionType\s*\)",
        "system_name": "inversion",
        "aliases": [
            (r"\bmut\.invParamA\b", "PA"),
            (r"\bmut\.invParamB\b", "PB"),
            (r"\bmut\.invParamC\b", "PC"),
            (r"\bmut\.invRadius\b", "iR"),
            (r"\bmut\.invScale\b", "isc"),
            (r"\bmut\.invAngle\b", "ANG"),
            (r"\bmut\.invFrequency\b", "FREQ"),
            (r"\bmut\.invAmplitude\b", "AMP"),
            (r"\bmut\.invMinR\b", "MINR"),
            (r"\bmut\.invMaxR\b", "MAXR"),
            (r"\bmut\.invWeight\b", "WGT"),
            (r"\bmut\.invThreshold\b", "THR"),
            (r"\bmut\.invColorFactor\b", "COLF"),
            (r"\bmut\.invNSteps\b", "NSTP"),
            (r"\bia\b", "PA"),
            (r"\bib\b", "PB"),
            (r"\bic\b", "PC"),
            (r"\biR\b", "iR"),
            (r"\bisc\b", "isc"),
        ],
    },
}


def find_switch_body(text: str, switch_pattern: str) -> str:
    m = re.search(switch_pattern, text)
    if not m:
        raise ValueError(f"Switch not found: {switch_pattern}")
    brace = text.find("{", m.start())
    if brace < 0:
        raise ValueError("Switch opening brace not found")
    depth = 0
    for i in range(brace, len(text)):
        if text[i] == "{":
            depth += 1
        elif text[i] == "}":
            depth -= 1
            if depth == 0:
                return text[brace + 1 : i]
    raise ValueError("Switch closing brace not found")


def extract_cases(switch_body: str) -> Dict[int, str]:
    cases: Dict[int, str] = {}
    pattern = re.compile(r"case\s+(\d+)\s*:\s*(.*?)\sbreak\s*;", re.DOTALL)
    for m in pattern.finditer(switch_body):
        case_body = m.group(2).strip()
        if case_body.startswith("{"):
            case_body = case_body[1:].lstrip()
        if case_body.endswith("}"):
            case_body = case_body[:-1].rstrip()
        cases[int(m.group(1))] = case_body
    return cases


def extract_case_name(switch_body: str, case_num: int) -> str:
    m = re.search(rf"case\s+{case_num}\s*:", switch_body)
    if not m:
        return f"Type {case_num}"
    tail = switch_body[m.end() :]
    nxt = re.search(rf"\bcase\s+{case_num + 1}\s*:\s*|\bdefault\s*:", tail)
    chunk = tail[: nxt.start()] if nxt else tail[:8000]
    comments = re.findall(r"//\s*(.+?)\s*(?:\n|$)", chunk)
    if comments:
        name = comments[-1].strip()
        name = re.sub(r"^FIXED:\s*", "", name)
        return name.split("—")[0].strip()
    return f"Type {case_num}"


def slugify(name: str) -> str:
    slug = name.lower()
    slug = re.sub(r"[^a-z0-9]+", "_", slug)
    slug = slug.strip("_")
    return slug[:48] or "type"


def apply_aliases(body: str, aliases: List[Tuple[str, str]]) -> str:
    out = body
    for pattern, repl in aliases:
        out = re.sub(pattern, repl, out)
    return out


def detect_params(body: str) -> List[str]:
    tokens = set(re.findall(r"\b[A-Z][A-Z0-9]{1,4}\b", body))
    tokens.discard("DE")
    return sorted(tokens)


def write_mut(path: Path, type_id: int, name: str, system: str, body: str) -> None:
    params = detect_params(body)
    lines = [
        f"// TYPE_ID: {type_id}",
        f"// NAME: {name}",
        f"// PARAMS: {', '.join(params) if params else 'none'}",
        f"// SYSTEM: {system}",
        body.strip(),
        "",
    ]
    path.write_text("\n".join(lines), encoding="utf-8")


def export_system(system: str, force: bool) -> int:
    cfg = SYSTEM_CONFIG[system]
    cpu_text = CPU_FILE.read_text(encoding="utf-8")
    switch_body = find_switch_body(cpu_text, cfg["switch"])
    cases = extract_cases(switch_body)
    if not cases:
        print(f"{system}: no cases found")
        return 0

    out_dir = SYSTEMS_DIR / system
    out_dir.mkdir(parents=True, exist_ok=True)

    existing_by_id: Dict[int, List[Path]] = {}
    for path in out_dir.glob("*.mut"):
        text = path.read_text(encoding="utf-8")
        m = re.search(r"^//\s*TYPE_ID:\s*(\d+)", text, re.MULTILINE)
        if m:
            existing_by_id.setdefault(int(m.group(1)), []).append(path)

    written = 0
    for num in sorted(cases):
        if num == 0:
            continue
        name = extract_case_name(switch_body, num)
        slug = slugify(name)
        fname = f"type_{num:03d}_{slug}.mut"
        path = out_dir / fname
        if not force and path.exists():
            continue
        if force:
            for old in existing_by_id.get(num, []):
                if old != path and old.exists():
                    old.unlink()
        body = apply_aliases(cases[num], cfg["aliases"])
        write_mut(path, num, name, cfg["system_name"], body)
        written += 1
    print(f"{system}: exported {written} .mut files ({len(cases)} CPU cases total)")
    return written


def main() -> int:
    parser = argparse.ArgumentParser(description="Export CPU switch cases to .mut files")
    parser.add_argument("--system", choices=sorted(SYSTEM_CONFIG))
    parser.add_argument("--all", action="store_true")
    parser.add_argument("--force", action="store_true", help="Overwrite existing .mut files")
    args = parser.parse_args()

    if not CPU_FILE.is_file():
        print(f"CPU file not found: {CPU_FILE}")
        return 1

    targets = list(SYSTEM_CONFIG) if args.all else ([args.system] if args.system else [])
    if not targets:
        parser.print_help()
        return 1

    total = 0
    for system in targets:
        total += export_system(system, args.force)
    return 0 if total >= 0 else 1


if __name__ == "__main__":
    sys.exit(main())
