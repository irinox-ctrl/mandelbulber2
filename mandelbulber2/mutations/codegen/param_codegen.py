#!/usr/bin/env python3
"""
param_codegen.py — Validate and generate C++/OpenCL snippets from mutation_registry.json.

CI mode checks that registry initparams match initparameters.cpp and nine_fractals field reads.
Generation mode writes reference .inc snippets under mutations/generated/ (not auto-included).

Usage:
    python3 param_codegen.py --ci
    python3 param_codegen.py --all --out mutations/generated/
    python3 param_codegen.py --system inversion --target cpu
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent.parent
MUTATIONS = ROOT / "mutations"
REGISTRY = MUTATIONS / "config" / "mutation_registry.json"
INITPARAMS = ROOT / "src" / "initparameters.cpp"
NINE_CPP = ROOT / "src" / "nine_fractals.cpp"
NINE_HPP = ROOT / "src" / "nine_fractals.hpp"


def load_registry() -> dict:
    if not REGISTRY.exists():
        raise FileNotFoundError(f"Registry not found: {REGISTRY}")
    with open(REGISTRY, encoding="utf-8") as f:
        return json.load(f)


def validate_system(system: str, cfg: dict) -> list[str]:
    errors: list[str] = []
    init_text = INITPARAMS.read_text(encoding="utf-8")
    nine_cpp = NINE_CPP.read_text(encoding="utf-8")
    nine_hpp = NINE_HPP.read_text(encoding="utf-8")

    for entry in cfg.get("initparams", []):
        name = entry["name"]
        field = entry["field"]
        if f'"{name}"' not in init_text:
            errors.append(f"{system}: init param '{name}' missing in initparameters.cpp")
        if field not in nine_hpp:
            errors.append(f"{system}: struct field '{field}' missing in nine_fractals.hpp")
        read_pat = rf'mutationParams\[i\]\.{re.escape(field)}\s*='
        if field.endswith("Enabled"):
            read_pat = rf'\.{re.escape(field)}\s*='
        if not re.search(read_pat, nine_cpp):
            errors.append(f"{system}: field '{field}' not read in nine_fractals.cpp")

    for key in ("type_field", "enabled_field", "iter_start", "iter_stop"):
        field = cfg.get(key)
        if field and field not in nine_hpp:
            errors.append(f"{system}: {key} '{field}' missing in nine_fractals.hpp")

    aliases = cfg.get("param_aliases", {})
    prefix = cfg.get("struct_prefix", system)
    for alias, suffix in aliases.items():
        full = f"{prefix}{suffix}"
        if full not in nine_hpp and suffix not in ("ParamA", "ParamB", "ParamC"):
            if full not in nine_hpp:
                errors.append(f"{system}: alias {alias} -> {full} not in struct")

    return errors


def cpp_type(entry: dict) -> str:
    t = entry.get("type", "double")
    return {"bool": "bool", "int": "int", "double": "double"}.get(t, "double")


def generate_initparams_snippet(system: str, cfg: dict) -> str:
    lines = [f"// Auto-generated initparameters snippet for {system}", ""]
    for entry in cfg.get("initparams", []):
        name = entry["name"]
        t = cpp_type(entry)
        default = entry.get("default", 0)
        if t == "bool":
            lines.append(f'\t\tpar->addParam("{name}", i, {str(default).lower()}, morphLinear, paramStandard);')
        elif t == "int":
            lo = entry.get("min", 0)
            hi = entry.get("max", 10000)
            lines.append(f'\t\tpar->addParam("{name}", i, {default}, {lo}, {hi}, morphAkima, paramStandard);')
        else:
            lo = entry.get("min", -100.0)
            hi = entry.get("max", 100.0)
            lines.append(f'\t\tpar->addParam("{name}", i, {default}, {lo}, {hi}, morphAkima, paramStandard);')
    return "\n".join(lines) + "\n"


def generate_reads_snippet(system: str, cfg: dict) -> str:
    lines = [f"// Auto-generated nine_fractals.cpp reads for {system}", ""]
    for entry in cfg.get("initparams", []):
        name = entry["name"]
        field = entry["field"]
        t = cpp_type(entry)
        getter = "Get<bool>" if t == "bool" else ("Get<int>" if t == "int" else "Get<double>")
        lines.append(
            f'\t\tmutationParams[i].{field} = generalPar->{getter}("{name}", i + 1);'
        )
    return "\n".join(lines) + "\n"


def generate_struct_snippet(system: str, cfg: dict) -> str:
    lines = [f"// Auto-generated struct fields for {system} (reference)", ""]
    seen: set[str] = set()
    for entry in cfg.get("initparams", []):
        field = entry["field"]
        if field in seen:
            continue
        seen.add(field)
        t = cpp_type(entry)
        lines.append(f"\t{t} {field};")
    for key in ("type_field", "enabled_field", "iter_start", "iter_stop", "weight_field"):
        field = cfg.get(key)
        if field and field not in seen:
            seen.add(field)
            if "Enabled" in field:
                lines.append(f"\tbool {field};")
            elif field.endswith("Type") or field.endswith("Start") or field.endswith("Stop") or field.endswith("Steps"):
                lines.append(f"\tint {field};")
            else:
                lines.append(f"\tdouble {field};")
    return "\n".join(lines) + "\n"


def generate_copy_snippet(system: str, cfg: dict) -> str:
    lines = [f"// Auto-generated copyFields snippet for {system}", ""]
    for entry in cfg.get("initparams", []):
        field = entry["field"]
        lines.append(f"\t\tsequence->mutationParams[i].{field} = mutationParams[i].{field};")
    return "\n".join(lines) + "\n"


def write_snippets(system: str, cfg: dict, out_dir: Path) -> None:
    out_dir.mkdir(parents=True, exist_ok=True)
    snippets = {
        f"{system}_initparams.cpp.inc": generate_initparams_snippet(system, cfg),
        f"{system}_reads.cpp.inc": generate_reads_snippet(system, cfg),
        f"{system}_struct.hpp.inc": generate_struct_snippet(system, cfg),
        f"{system}_copy.cpp.inc": generate_copy_snippet(system, cfg),
    }
    for fname, content in snippets.items():
        path = out_dir / fname
        path.write_text(content, encoding="utf-8")
        print(f"Generated: {path}")


def main() -> int:
    parser = argparse.ArgumentParser(description="Mutation param registry codegen")
    parser.add_argument("--ci", action="store_true", help="Validate registry against runtime sources")
    parser.add_argument("--all", action="store_true", help="Process all systems in registry")
    parser.add_argument("--system", help="Single system name")
    parser.add_argument("--out", type=Path, default=MUTATIONS / "generated")
    parser.add_argument("--target", choices=["cpu", "gpu", "all"], default="all")
    args = parser.parse_args()

    registry = load_registry()
    systems = registry.get("systems", {})
    if not systems:
        print("Registry has no systems")
        return 1

    selected = list(systems.keys()) if args.all or args.ci else []
    if args.system:
        if args.system not in systems:
            print(f"Unknown system: {args.system}")
            return 1
        selected = [args.system]

    if args.ci:
        errors: list[str] = []
        for name, cfg in systems.items():
            errors.extend(validate_system(name, cfg))
        if errors:
            for err in errors:
                print(f"ERROR: {err}")
            print(f"param_codegen --ci: FAIL ({len(errors)} issues)")
            return 1
        print(f"param_codegen --ci: OK ({len(systems)} systems validated)")
        return 0

    if not selected:
        parser.print_help()
        return 1

    for name in selected:
        write_snippets(name, systems[name], args.out)
    return 0


if __name__ == "__main__":
    sys.exit(main())
