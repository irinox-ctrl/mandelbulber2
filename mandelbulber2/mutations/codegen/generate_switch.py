#!/usr/bin/env python3
"""
generate_switch.py — Code generator for mutation switch blocks.

Generates CPU (.inc) and GPU (.inc) switch-case code from .mut definition files.
Handles parameter alias expansion with correct ordering (longest-first) to avoid
partial-match bugs.

Usage:
    python3 generate_switch.py --system custom_clip
    python3 generate_switch.py --system custom_clip --target cpu
    python3 generate_switch.py --all

Fixes included:
    - Fix #1: Parameter aliases sorted by length (longest first) to prevent
              partial replacement (e.g. PAD before PA)
    - Fix #8: Duplicate TYPE_ID validation — raises error on collisions
    - Fix #9: Improved float suffix regex for GPU (handles scientific notation)
"""

import re
import os
import sys
import json
import argparse
from pathlib import Path

# ─── Configuration ──────────────────────────────────────────────────────────

BASE_DIR = Path(__file__).resolve().parent.parent  # mandelbulber2/mutations/
SYSTEMS_DIR = BASE_DIR / "systems"
GENERATED_DIR = BASE_DIR / "generated"
CONFIG_FILE = BASE_DIR / "config" / "mutation_registry.json"

# Parameter alias → struct field mapping per system
# This is loaded from config or can be defined here as defaults
SYSTEM_PARAM_MAP = {
    "custom_clip": {
        "struct_prefix": "customClip",
        "type_field": "customClipType",
        "iter_start": "customClipIterStart",
        "iter_stop": "customClipIterStop",
        "enabled_field": "customClipEnabled",
        "PA": "ParamA",
        "PB": "ParamB",
        "PC": "ParamC",
        "PD": "ParamD",
        "PE": "ParamE",
        "PF": "ParamF",
        "PG": "ParamG",
        "PH": "ParamH",
    },
}

# Reserved (non-parameter) keys in param maps
RESERVED_KEYS = frozenset({
    "struct_prefix", "type_field", "iter_start", "iter_stop", "enabled_field"
})


def load_config():
    """Load system configuration from registry JSON if available."""
    if CONFIG_FILE.exists():
        with open(CONFIG_FILE) as f:
            registry = json.load(f)
        for name, sys_cfg in registry.get("systems", {}).items():
            if name not in SYSTEM_PARAM_MAP:
                SYSTEM_PARAM_MAP[name] = {}
            prefix = sys_cfg.get("struct_prefix", name)
            SYSTEM_PARAM_MAP[name]["struct_prefix"] = prefix
            SYSTEM_PARAM_MAP[name]["type_field"] = sys_cfg.get("type_field", f"{prefix}Type")
            SYSTEM_PARAM_MAP[name]["iter_start"] = sys_cfg.get("iter_start", f"{prefix}IterStart")
            SYSTEM_PARAM_MAP[name]["iter_stop"] = sys_cfg.get("iter_stop", f"{prefix}IterStop")
            SYSTEM_PARAM_MAP[name]["enabled_field"] = sys_cfg.get("enabled_field", f"{prefix}Enabled")
            aliases = sys_cfg.get("param_aliases", {})
            if aliases:
                for alias, field in aliases.items():
                    SYSTEM_PARAM_MAP[name][alias] = field
            else:
                for p in sys_cfg.get("params", []):
                    SYSTEM_PARAM_MAP[name][p] = f"Param{p[-1].upper()}" if len(p) == 2 else p


def parse_mut_file(filepath):
    """Parse a .mut file into metadata dict and code body string."""
    meta = {}
    body_lines = []
    in_body = False

    with open(filepath) as f:
        for line in f:
            line = line.rstrip("\n")
            if not in_body:
                # Parse header comments
                m = re.match(r'^//\s*(\w+):\s*(.+)$', line)
                if m:
                    key = m.group(1).lower()
                    val = m.group(2).strip()
                    if key == "type_id":
                        meta["type_id"] = int(val)
                    elif key == "name":
                        meta["name"] = val
                    elif key == "params":
                        meta["params"] = [p.strip() for p in val.split(",")]
                    elif key == "system":
                        meta["system"] = val
                    else:
                        meta[key] = val
                elif line.strip() and not line.strip().startswith("//"):
                    in_body = True
                    body_lines.append(line)
            else:
                body_lines.append(line)

    return meta, "\n".join(body_lines)


def expand_for_target(body, system, target):
    """
    Expand parameter aliases for target (cpu/gpu).

    Fix #1: Sort aliases by length DESCENDING to prevent partial matches.
    E.g., PAD is replaced before PA.
    """
    pmap = SYSTEM_PARAM_MAP.get(system, {})
    accessor = "." if target == "cpu" else "->"

    result = body

    # Sort REVERSED by length — longest alias first to prevent partial matches
    sorted_aliases = sorted(
        [k for k in pmap.keys() if k not in RESERVED_KEYS],
        key=len, reverse=True
    )
    prefix = pmap.get("struct_prefix", system)
    for alias in sorted_aliases:
        field = pmap[alias]
        result = re.sub(rf'\b{re.escape(alias)}\b', f'mut{accessor}{prefix}{field}', result)

    # Fix #9: GPU float suffix replacement (improved regex)
    if target == "gpu":
        # Match: 1.0, 0.5, 1.23, etc. (not already suffixed with f)
        result = re.sub(r'(?<![a-zA-Z_0-9])(\d+\.\d+)(?!f\b)', r'\1f', result)
        # Match: scientific notation 1.0e-10 → 1.0e-10f
        result = re.sub(r'(?<![a-zA-Z_])(\d+\.\d*[eE][+-]?\d+)(?!f\b)', r'\1f', result)

    return result


def generate_switch_block(system, mutations, target):
    """
    Generate a switch-case block from parsed mutations.

    Fix #8: Validates that no duplicate TYPE_IDs exist.
    """
    # Duplicate TYPE_ID check
    seen_ids = set()
    for mut_meta, _ in mutations:
        type_id = mut_meta.get("type_id", 0)
        if type_id in seen_ids:
            raise ValueError(
                f"Duplicate TYPE_ID {type_id} in system '{system}'. "
                f"Each mutation must have a unique TYPE_ID."
            )
        seen_ids.add(type_id)

    pmap = SYSTEM_PARAM_MAP.get(system, {})
    accessor = "." if target == "cpu" else "->"

    lines = []
    lines.append(f"// Auto-generated mutation switch for system: {system}")
    lines.append(f"// Target: {target.upper()}")
    lines.append(f"// Generated mutations: {len(mutations)}")
    lines.append(f"switch (mut{accessor}{pmap.get('type_field', system + 'Type')})")
    lines.append("{")

    for mut_meta, mut_body in sorted(mutations, key=lambda x: x[0].get("type_id", 0)):
        type_id = mut_meta.get("type_id", 0)
        name = mut_meta.get("name", f"Type {type_id}")
        expanded = expand_for_target(mut_body, system, target)

        lines.append(f"\tcase {type_id}: // {name}")
        lines.append("\t{")
        for code_line in expanded.strip().split("\n"):
            lines.append(f"\t\t{code_line}")
        lines.append("\t\tbreak;")
        lines.append("\t}")

    lines.append("\tdefault: break;")
    lines.append("}")

    return "\n".join(lines)


def generate_system(system_name, target=None):
    """Generate .inc files for a mutation system."""
    system_dir = SYSTEMS_DIR / system_name
    if not system_dir.exists():
        print(f"Error: System directory not found: {system_dir}")
        return False

    # Parse all .mut files
    mutations = []
    for mut_file in sorted(system_dir.glob("*.mut")):
        meta, body = parse_mut_file(mut_file)
        if meta.get("type_id") is not None and body.strip():
            mutations.append((meta, body))

    if not mutations:
        print(f"Warning: No valid .mut files found in {system_dir}")
        return False

    GENERATED_DIR.mkdir(parents=True, exist_ok=True)

    targets = [target] if target else ["cpu", "gpu"]
    for t in targets:
        try:
            switch_code = generate_switch_block(system_name, mutations, t)
            output_file = GENERATED_DIR / f"mutations_{system_name}_{t}.inc"
            with open(output_file, "w") as f:
                f.write(switch_code)
            print(f"Generated: {output_file} ({len(mutations)} mutations)")
        except ValueError as e:
            print(f"Error generating {t}: {e}")
            return False

    return True


def main():
    parser = argparse.ArgumentParser(description="Generate mutation switch blocks")
    parser.add_argument("--system", help="System name to generate")
    parser.add_argument("--target", choices=["cpu", "gpu"], help="Target platform")
    parser.add_argument("--all", action="store_true", help="Generate all systems")
    parser.add_argument("--validate-only", action="store_true", help="Only validate, don't generate")
    args = parser.parse_args()

    load_config()

    if args.all:
        if not SYSTEMS_DIR.exists():
            print(f"No systems directory found at {SYSTEMS_DIR}")
            sys.exit(1)
        success = True
        for system_dir in sorted(SYSTEMS_DIR.iterdir()):
            if not system_dir.is_dir():
                continue
            if args.validate_only:
                mutations = []
                for mut_file in sorted(system_dir.glob("*.mut")):
                    meta, body = parse_mut_file(mut_file)
                    if meta.get("type_id") is not None:
                        mutations.append((meta, body))
                seen = set()
                ok = True
                for m, _ in mutations:
                    tid = m.get("type_id", 0)
                    if tid in seen:
                        print(f"DUPLICATE TYPE_ID {tid} in {system_dir.name}")
                        ok = False
                    seen.add(tid)
                if ok and mutations:
                    print(f"Validation OK: {system_dir.name} ({len(mutations)} mutations)")
                elif not mutations:
                    print(f"Warning: no .mut files in {system_dir.name}")
                if not ok:
                    success = False
            else:
                if not generate_system(system_dir.name, args.target):
                    success = False
        sys.exit(0 if success else 1)
    elif args.system:
        if args.validate_only:
            system_dir = SYSTEMS_DIR / args.system
            if not system_dir.exists():
                print(f"System not found: {args.system}")
                sys.exit(1)
            mutations = []
            for mut_file in sorted(system_dir.glob("*.mut")):
                meta, body = parse_mut_file(mut_file)
                if meta.get("type_id") is not None:
                    mutations.append((meta, body))
            # Check duplicates
            seen = set()
            for m, _ in mutations:
                tid = m.get("type_id", 0)
                if tid in seen:
                    print(f"DUPLICATE TYPE_ID: {tid}")
                    sys.exit(1)
                seen.add(tid)
            print(f"Validation OK: {len(mutations)} mutations, no duplicates")
            sys.exit(0)
        if not generate_system(args.system, args.target):
            sys.exit(1)
    else:
        parser.print_help()
        sys.exit(1)


if __name__ == "__main__":
    main()
