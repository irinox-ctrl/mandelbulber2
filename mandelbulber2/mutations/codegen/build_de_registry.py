#!/usr/bin/env python3
"""
Build mutation_registry.json entries for DE subsystems.

Scrapes initparameters.cpp and nine_fractals.cpp to pair param names with struct fields.

Usage:
    python3 build_de_registry.py --merge
    python3 build_de_registry.py --merge --dry-run
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path
from typing import Dict, List, Tuple

ROOT = Path(__file__).resolve().parent.parent.parent
REGISTRY = ROOT / "mutations" / "config" / "mutation_registry.json"
INITPARAMS = ROOT / "src" / "initparameters.cpp"
NINE_CPP = ROOT / "src" / "nine_fractals.cpp"

DE_META: Dict[str, dict] = {
    "jos_leys": {
        "type_field": "josLeysDeType",
        "enabled_field": "josLeysEnabled",
        "iter_start": "josIterStart",
        "iter_stop": "josIterStop",
        "weight_field": "josLeysWeight",
        "prefixes": ["mutation_jos_"],
    },
    "pk": {
        "type_field": "pseudoKleinianDeType",
        "enabled_field": "pkEnabled",
        "iter_start": "pkIterStart",
        "iter_stop": "pkIterStop",
        "weight_field": "pkWeight",
        "prefixes": ["mutation_pk_"],
    },
    "mb_math": {
        "type_field": "mbMathType",
        "enabled_field": "mbMathEnabled",
        "iter_start": "mbIterStart",
        "iter_stop": "mbIterStop",
        "weight_field": "mbMathWeight",
        "prefixes": ["mutation_mb_"],
    },
    "warp_dist": {
        "type_field": "warpDistType",
        "enabled_field": "warpDistEnabled",
        "iter_start": "warpIterStart",
        "iter_stop": "warpIterStop",
        "weight_field": "warpDistWeight",
        "prefixes": ["mutation_warp_"],
    },
    "sym_kal": {
        "type_field": "symKalType",
        "enabled_field": "symmetryEnabled",
        "iter_start": "skIterStart",
        "iter_stop": "skIterStop",
        "weight_field": "symmetryWeight",
        "prefixes": ["mutation_sym_", "mutation_sk_"],
    },
    "abox": {
        "type_field": "aboxType",
        "enabled_field": "aboxEnabled",
        "iter_start": "abIterStart",
        "iter_stop": "abIterStop",
        "weight_field": "aboxWeight",
        "prefixes": ["mutation_ab_", "mutation_abox_"],
    },
    "noise": {
        "type_field": "noiseType",
        "enabled_field": "noiseEnabled",
        "iter_start": "noiseIterStart",
        "iter_stop": "noiseIterStop",
        "weight_field": "noiseWeight",
        "prefixes": ["mutation_noise_"],
    },
    "orbit_trap": {
        "type_field": "orbitTrapType",
        "enabled_field": "orbitTrapEnabled",
        "iter_start": "orbitIterStart",
        "iter_stop": "orbitIterStop",
        "weight_field": "orbitTrapWeight",
        "prefixes": ["mutation_orbit_"],
    },
    "torus": {
        "type_field": "torusType",
        "enabled_field": "torusEnabled",
        "iter_start": "torusIterStart",
        "iter_stop": "torusIterStop",
        "weight_field": "torusWeight",
        "prefixes": ["mutation_torus_"],
    },
    "as": {
        "type_field": "asType",
        "enabled_field": "asEnabled",
        "iter_start": "asIterStart",
        "iter_stop": "asIterStop",
        "weight_field": "asWeight",
        "prefixes": ["mutation_as_"],
    },
    "sm": {
        "type_field": "smType",
        "enabled_field": "smEnabled",
        "iter_start": "smIterStart",
        "iter_stop": "smIterStop",
        "weight_field": "smWeight",
        "prefixes": ["mutation_sm_"],
    },
}


def scrape_initparams(text: str) -> List[str]:
    return re.findall(r'addParam\("([^"]+)"', text)


def scrape_reads(text: str) -> Dict[str, Tuple[str, str]]:
    """Map init param name -> (struct field, type)."""
    mapping: Dict[str, Tuple[str, str]] = {}
    for m in re.finditer(
        r'mutationParams\[i\]\.(\w+)\s*=\s*(?:\n\s*)?generalPar->Get<(\w+)>\("([^"]+)"',
        text,
    ):
        mapping[m.group(3)] = (m.group(1), m.group(2).lower())

    for m in re.finditer(
        r'mutationParams\[i\]\.(\w+)\s*=\s*enum\w+\(generalPar->Get<(\w+)>\("([^"]+)"',
        text,
    ):
        mapping[m.group(3)] = (m.group(1), "int")

    for m in re.finditer(
        r'mutationParams\[i\]\.(\w+)\s*=\s*LoadMutationEnabled\(\s*generalPar,\s*i,\s*"([^"]+)"',
        text,
    ):
        mapping[m.group(2)] = (m.group(1), "bool")

    return mapping


def matches_prefix(name: str, prefixes: List[str]) -> bool:
    return any(name.startswith(p) for p in prefixes)


def build_system_entry(name: str, meta: dict, init_names: List[str], reads: Dict[str, Tuple[str, str]]) -> dict:
    seen_fields: set[str] = set()
    initparams: List[dict] = []
    for pname in sorted(init_names):
        if not matches_prefix(pname, meta["prefixes"]):
            continue
        if pname not in reads:
            continue
        field, typ = reads[pname]
        if field in seen_fields:
            continue
        seen_fields.add(field)
        entry: dict = {"name": pname, "field": field, "type": typ}
        if typ == "bool":
            entry["default"] = True
        elif typ == "int":
            entry["default"] = 0
        else:
            entry["default"] = 1.0
        initparams.append(entry)

    return {
        "type_field": meta["type_field"],
        "enabled_field": meta["enabled_field"],
        "iter_start": meta["iter_start"],
        "iter_stop": meta["iter_stop"],
        "weight_field": meta["weight_field"],
        "initparams": initparams,
    }


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--merge", action="store_true", help="Merge DE entries into mutation_registry.json")
    parser.add_argument("--dry-run", action="store_true")
    args = parser.parse_args()

    init_text = INITPARAMS.read_text(encoding="utf-8")
    nine_text = NINE_CPP.read_text(encoding="utf-8")
    init_names = scrape_initparams(init_text)
    reads = scrape_reads(nine_text)

    built = {}
    for name, meta in DE_META.items():
        entry = build_system_entry(name, meta, init_names, reads)
        built[name] = entry
        print(f"{name}: {len(entry['initparams'])} initparams")

    if not args.merge:
        print(json.dumps(built, indent=2))
        return 0

    registry = json.loads(REGISTRY.read_text(encoding="utf-8"))
    systems = registry.setdefault("systems", {})
    for name, entry in built.items():
        systems[name] = entry

    out = json.dumps(registry, indent=2) + "\n"
    if args.dry_run:
        print(out[:2000], "...")
        return 0

    REGISTRY.write_text(out, encoding="utf-8")
    print(f"Updated {REGISTRY} ({len(built)} DE systems)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
