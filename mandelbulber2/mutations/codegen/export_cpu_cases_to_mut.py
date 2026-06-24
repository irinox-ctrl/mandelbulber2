#!/usr/bin/env python3
"""
Export CPU mutation switch cases to .mut pilot files.

Reads compute_fractal.cpp switches and writes mutations/systems/<system>/type_NNN_<slug>.mut.

Usage:
    python3 export_cpu_cases_to_mut.py --system clip
    python3 export_cpu_cases_to_mut.py --all              # clip + inversion
    python3 export_cpu_cases_to_mut.py --all-de           # 11 DE subsystems
    python3 export_cpu_cases_to_mut.py --all --all-de --force
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
CODEGEN = Path(__file__).resolve().parent
sys.path.insert(0, str(CODEGEN))
import port_cpu_de_cases as PORT  # noqa: E402

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
    return PORT.extract_cases(switch_body)


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
    return slug.strip("_")[:48] or "type"


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
        f"// PARAMS: {', '.join(params) if params else 'locals'}",
        f"// SYSTEM: {system}",
        body.strip(),
        "",
    ]
    path.write_text("\n".join(lines), encoding="utf-8")


def write_cases(system: str, switch_body: str, cases: Dict[int, str], aliases: List[Tuple[str, str]], force: bool) -> int:
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
        path = out_dir / f"type_{num:03d}_{slug}.mut"
        if not force and path.exists():
            continue
        if force:
            for old in existing_by_id.get(num, []):
                if old != path and old.exists():
                    old.unlink()
        body = apply_aliases(cases[num], aliases) if aliases else cases[num]
        write_mut(path, num, name, system, body)
        written += 1
    print(f"{system}: exported {written} .mut files ({len(cases)} CPU cases total)")
    return written


def export_transform_system(system: str, force: bool) -> int:
    cfg = SYSTEM_CONFIG[system]
    cpu_text = CPU_FILE.read_text(encoding="utf-8")
    switch_body = find_switch_body(cpu_text, cfg["switch"])
    cases = extract_cases(switch_body)
    if not cases:
        print(f"{system}: no cases found")
        return 0
    return write_cases(system, switch_body, cases, cfg["aliases"], force)


def export_de_system(section, cpu_text: str, force: bool) -> int:
    start = PORT.find_marker_pos(cpu_text, section.marker)
    _, _, switch_body = PORT.find_switch_body(cpu_text, section.cpu_switch, start)
    cases = extract_cases(switch_body)
    if not cases:
        print(f"{section.section_id}: no cases found")
        return 0
    return write_cases(section.section_id, switch_body, cases, [], force)


def main() -> int:
    parser = argparse.ArgumentParser(description="Export CPU switch cases to .mut files")
    parser.add_argument("--system", choices=sorted(SYSTEM_CONFIG))
    parser.add_argument("--de-system", choices=[s.section_id for s in PORT.SECTIONS])
    parser.add_argument("--all", action="store_true", help="clip + inversion")
    parser.add_argument("--all-de", action="store_true", help="All 11 DE subsystems")
    parser.add_argument("--force", action="store_true")
    args = parser.parse_args()

    if not CPU_FILE.is_file():
        print(f"CPU file not found: {CPU_FILE}")
        return 1

    total = 0
    cpu_text = CPU_FILE.read_text(encoding="utf-8")

    if args.all:
        for system in SYSTEM_CONFIG:
            total += export_transform_system(system, args.force)
    elif args.system:
        total += export_transform_system(args.system, args.force)

    if args.all_de:
        for section in PORT.SECTIONS:
            total += export_de_system(section, cpu_text, args.force)
    elif args.de_system:
        section = next(s for s in PORT.SECTIONS if s.section_id == args.de_system)
        total += export_de_system(section, cpu_text, args.force)

    if total == 0 and not (args.all or args.system or args.all_de or args.de_system):
        parser.print_help()
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
