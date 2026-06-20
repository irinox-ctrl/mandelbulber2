#!/usr/bin/env python3
"""
mutation_wizard.py — Batch mutation creation and management tool.

Creates new mutation systems, generates .mut files from templates,
validates existing mutations, and triggers code generation.

Usage:
    python3 mutation_wizard.py --new-system
    python3 mutation_wizard.py --batch-add 50 --system custom_clip --template smooth_fold
    python3 mutation_wizard.py --validate
    python3 mutation_wizard.py --list-templates
    python3 mutation_wizard.py --full-rebuild
"""

import os
import sys
import json
import math
import argparse
import logging
import re
from pathlib import Path
from datetime import datetime

# ─── Paths ──────────────────────────────────────────────────────────────────

BASE_DIR = Path(__file__).resolve().parent.parent  # mandelbulber2/mutations/
SYSTEMS_DIR = BASE_DIR / "systems"
GENERATED_DIR = BASE_DIR / "generated"
CONFIG_DIR = BASE_DIR / "config"
LOGS_DIR = BASE_DIR / "logs"
AUDIT_DIR = BASE_DIR / "audit"
REGISTRY_FILE = CONFIG_DIR / "mutation_registry.json"

# ─── Logging ────────────────────────────────────────────────────────────────

LOGS_DIR.mkdir(parents=True, exist_ok=True)
logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s | %(levelname)-8s | %(name)s | %(message)s",
    handlers=[
        logging.StreamHandler(),
        logging.FileHandler(LOGS_DIR / f"mutation_manager_{datetime.now():%Y%m%d_%H%M%S}.log"),
    ],
)
logger = logging.getLogger("MutationWizard")

# ─── Variation Templates ────────────────────────────────────────────────────

VARIATION_TEMPLATES = {
    "smooth_fold": {
        "base": (
            "if (zz.x > {pa}) zz.x = {pa} - zz.x;\n"
            "else if (zz.x < -{pa}) zz.x = -{pa} - zz.x;\n"
            "if (zz.y > {pb}) zz.y = {pb} - zz.y;\n"
            "else if (zz.y < -{pb}) zz.y = -{pb} - zz.y;\n"
            "if (zz.z > {pc}) zz.z = {pc} - zz.z;\n"
            "else if (zz.z < -{pc}) zz.z = -{pc} - zz.z;\n"
            "mde = {pb};"
        ),
        "params": ["PA", "PB", "PC"],
        "description": "Smooth axis-aligned folding with configurable thresholds",
    },
    "exponential_fold": {
        "base": (
            "FLOAT_T r = LENGTH3(zz.x, zz.y, zz.z);\n"
            "FLOAT_T decay = SAFE_EXP(-{pa} * r);\n"
            "zz.x *= (1.0 + {pb} * decay);\n"
            "zz.y *= (1.0 + {pb} * decay);\n"
            "zz.z *= (1.0 + {pb} * decay);\n"
            "mde = 1.0 + {pb} * decay;"
        ),
        "params": ["PA", "PB"],
        "description": "Exponential decay scaling",
    },
    "spiral_inversion": {
        "base": (
            "FLOAT_T r = LENGTH3(zz.x, zz.y, zz.z);\n"
            "FLOAT_T theta = atan2(zz.y, zz.x);\n"
            "FLOAT_T phi = atan2(LENGTH3(zz.x, zz.y, 0.0), zz.z);\n"
            "r = SAFE_LOG(r + 1.0) * {pa};\n"
            "theta += {pb} * SAFE_LOG(r + 1.0);\n"
            "zz.x = r * sin(phi) * cos(theta);\n"
            "zz.y = r * sin(phi) * sin(theta);\n"
            "zz.z = r * cos(phi);\n"
            "mde = {pa};"
        ),
        "params": ["PA", "PB"],
        "description": "Logarithmic spiral transformation",
    },
    "gaussian_clip": {
        "base": (
            "FLOAT_T r2 = zz.x*zz.x + zz.y*zz.y + zz.z*zz.z;\n"
            "FLOAT_T gauss = SAFE_EXP(-r2 / ({pa} * {pa}));\n"
            "zz.x *= gauss;\n"
            "zz.y *= gauss;\n"
            "zz.z *= gauss;\n"
            "mde = gauss;"
        ),
        "params": ["PA"],
        "description": "Gaussian bell curve attenuation",
    },
    "wave_modulation": {
        "base": (
            "zz.x += {pa} * sin({pb} * zz.y);\n"
            "zz.y += {pa} * sin({pb} * zz.z);\n"
            "zz.z += {pa} * sin({pb} * zz.x);\n"
            "mde = 1.0;"
        ),
        "params": ["PA", "PB"],
        "description": "Sinusoidal wave deformation",
    },
    "distance_field": {
        "base": (
            "FLOAT_T dx = fabs(zz.x) - {pa};\n"
            "FLOAT_T dy = fabs(zz.y) - {pb};\n"
            "FLOAT_T dz = fabs(zz.z) - {pc};\n"
            "FLOAT_T dBox = LENGTH3(fmax(dx, 0.0), fmax(dy, 0.0), fmax(dz, 0.0))\n"
            "    + fmin(fmax(dx, fmax(dy, dz)), 0.0);\n"
            "if (dBox < 0.0) { zz.x *= 0.0; zz.y *= 0.0; zz.z *= 0.0; }\n"
            "mde = 1.0;"
        ),
        "params": ["PA", "PB", "PC"],
        "description": "Box/sphere distance field clipping",
    },
    "newton_method": {
        "base": (
            "FLOAT_T r2 = zz.x*zz.x + zz.y*zz.y + zz.z*zz.z;\n"
            "FLOAT_T rn = SAFE_POW(r2, {pa} * 0.5);\n"
            "FLOAT_T dr = {pa} * rn;\n"
            "FLOAT_T denom = GUARD_ZERO_VAL(dr);\n"
            "zz.x -= zz.x * (rn - 1.0) / denom * {pb};\n"
            "zz.y -= zz.y * (rn - 1.0) / denom * {pb};\n"
            "zz.z -= zz.z * (rn - 1.0) / denom * {pb};\n"
            "mde = fabs(1.0 - {pb} * (rn - 1.0) / denom);"
        ),
        "params": ["PA", "PB"],
        "description": "Newton-Raphson root-finding iteration",
    },
    "julia_hybrid": {
        "base": (
            "FLOAT_T cx = {pa}, cy = {pb}, cz = {pc};\n"
            "FLOAT_T nx = zz.x*zz.x - zz.y*zz.y + cx;\n"
            "FLOAT_T ny = 2.0 * zz.x * zz.y + cy;\n"
            "FLOAT_T nz = zz.z + cz;\n"
            "zz.x = nx; zz.y = ny; zz.z = nz;\n"
            "mde = 2.0 * LENGTH3(zz.x, zz.y, zz.z);"
        ),
        "params": ["PA", "PB", "PC"],
        "description": "Julia set modification hybrid",
    },
}

# ─── Parameter Strategies ───────────────────────────────────────────────────

PARAM_STRATEGIES = {
    "linear": lambda i, n: 0.5 + (i / max(n - 1, 1)) * 1.5,
    "exponential": lambda i, n: 0.1 * math.exp(2.0 * i / max(n - 1, 1)),
    "logarithmic": lambda i, n: 0.5 + math.log1p(i) / math.log1p(max(n - 1, 1)) * 1.5,
    "sinusoidal": lambda i, n: 1.0 + 0.5 * math.sin(2.0 * math.pi * i / max(n - 1, 1)),
    "power": lambda i, n: (i / max(n - 1, 1)) ** 2 * 2.0,
    "harmonic": lambda i, n: 1.0 / (1.0 + i * 0.1),
    "sawtooth": lambda i, n: (i % 10) / 10.0 * 2.0,
    "random_cluster": lambda i, n: 0.5 + ((i * 7 + 3) % 11) / 11.0 * 1.5,
}

STRATEGY_NAMES = list(PARAM_STRATEGIES.keys())


def get_strategy_name(index, total):
    return STRATEGY_NAMES[index % len(STRATEGY_NAMES)]


def get_param_value(strategy_name, index, total):
    return PARAM_STRATEGIES[strategy_name](index, total)


# ─── Registry ───────────────────────────────────────────────────────────────

def load_registry():
    CONFIG_DIR.mkdir(parents=True, exist_ok=True)
    if REGISTRY_FILE.exists():
        with open(REGISTRY_FILE) as f:
            return json.load(f)
    return {"systems": {}}


def save_registry(registry):
    CONFIG_DIR.mkdir(parents=True, exist_ok=True)
    with open(REGISTRY_FILE, "w") as f:
        json.dump(registry, f, indent=2)


def audit_log(action, system, details, status="success"):
    AUDIT_DIR.mkdir(parents=True, exist_ok=True)
    entry = {
        "timestamp": datetime.now().isoformat(),
        "action": action,
        "system": system,
        "details": details,
        "status": status,
    }
    audit_file = AUDIT_DIR / f"audit_{datetime.now():%Y%m%d}.jsonl"
    with open(audit_file, "a") as f:
        f.write(json.dumps(entry) + "\n")


# ─── System Creation ────────────────────────────────────────────────────────

def create_system_interactive():
    """Interactive system creation wizard."""
    print("\n=== New Mutation System ===\n")
    name = input("System name (e.g. custom_clip): ").strip()
    display_name = input("Display name: ").strip() or name.replace("_", " ").title()
    prefix = input(f"Struct prefix [{name.replace('_', '').title()}]: ").strip()
    if not prefix:
        prefix = "".join(w.capitalize() for w in name.split("_"))
        prefix = prefix[0].lower() + prefix[1:]
    params_str = input("Parameter aliases (comma-separated, e.g. PA,PB,PC): ").strip()
    params = [p.strip().upper() for p in params_str.split(",") if p.strip()]
    if not params:
        params = ["PA", "PB", "PC"]

    registry = load_registry()
    registry["systems"][name] = {
        "name": name,
        "display_name": display_name,
        "struct_prefix": prefix,
        "params": params,
        "base_type_id": 1,
        "created_at": datetime.now().isoformat(),
        "updated_at": datetime.now().isoformat(),
    }
    save_registry(registry)

    sys_dir = SYSTEMS_DIR / name
    sys_dir.mkdir(parents=True, exist_ok=True)

    logger.info(f"Created system: {name} at {sys_dir}")
    audit_log("create_system", name, {"display_name": display_name, "params": params})

    gen = input("\nGenerate mutations now? (y/n): ").strip().lower()
    if gen == "y":
        count = int(input("Number of variations: ").strip() or "50")
        print("\nAvailable templates:")
        for i, t in enumerate(VARIATION_TEMPLATES):
            print(f"  {i+1}. {t} — {VARIATION_TEMPLATES[t]['description']}")
        tmpl_idx = int(input("Select template (number): ").strip() or "1") - 1
        tmpl_name = list(VARIATION_TEMPLATES.keys())[tmpl_idx]
        generate_mutations(name, count, tmpl_name, optimize=True)


def create_system_batch(name, display_name=None, prefix=None, params=None):
    """Non-interactive system creation."""
    if not display_name:
        display_name = name.replace("_", " ").title()
    if not prefix:
        prefix = "".join(w.capitalize() for w in name.split("_"))
        prefix = prefix[0].lower() + prefix[1:]
    if not params:
        params = ["PA", "PB", "PC"]

    registry = load_registry()
    registry["systems"][name] = {
        "name": name,
        "display_name": display_name,
        "struct_prefix": prefix,
        "params": params,
        "base_type_id": 1,
        "created_at": datetime.now().isoformat(),
        "updated_at": datetime.now().isoformat(),
    }
    save_registry(registry)
    sys_dir = SYSTEMS_DIR / name
    sys_dir.mkdir(parents=True, exist_ok=True)
    logger.info(f"Created system: {name}")


# ─── Mutation Generation ────────────────────────────────────────────────────

def generate_mutations(system_name, count, template_name, optimize=False):
    """Generate batch of .mut files from a template."""
    if template_name not in VARIATION_TEMPLATES:
        logger.error(f"Unknown template: {template_name}")
        return False

    template = VARIATION_TEMPLATES[template_name]
    sys_dir = SYSTEMS_DIR / system_name
    sys_dir.mkdir(parents=True, exist_ok=True)

    registry = load_registry()
    sys_config = registry.get("systems", {}).get(system_name, {})
    params = sys_config.get("params", template["params"])
    base_id = sys_config.get("base_type_id", 1)

    # Find max existing type_id
    existing_ids = set()
    for f in sys_dir.glob("*.mut"):
        with open(f) as fh:
            for line in fh:
                m = re.match(r'^//\s*TYPE_ID:\s*(\d+)', line)
                if m:
                    existing_ids.add(int(m.group(1)))
                    break
    start_id = max(existing_ids) + 1 if existing_ids else base_id

    generated = 0
    for i in range(count):
        type_id = start_id + i
        strategy = get_strategy_name(i, count)

        # Generate parameter values
        param_values = {}
        for p in params:
            param_values[p.lower()] = round(get_param_value(strategy, i, count), 4)

        # Substitute template
        body = template["base"]
        for k, v in param_values.items():
            body = body.replace(f"{{{k}}}", str(v))

        # File content
        name = f"{strategy.replace('_', ' ').title()} Variant {i + 1}"
        filename = f"{system_name}_{type_id:03d}_{strategy}_variant_{i + 1}.mut"

        content = (
            f"// SYSTEM: {system_name}\n"
            f"// TYPE_ID: {type_id}\n"
            f"// NAME: {name}\n"
            f"// PARAMS: {', '.join(params)}\n"
            f"// TAGS: {strategy}, auto-generated, {system_name}\n"
            f"// NOTES: Auto-generated variant {i + 1}/{count} using {strategy} strategy\n"
            f"\n"
            f"// {template['description']}\n"
            f"\n"
            f"{body}\n"
        )

        filepath = sys_dir / filename
        with open(filepath, "w") as f:
            f.write(content)
        generated += 1

    logger.info(f"Generated {generated}/{count} mutation files in {sys_dir}")
    audit_log("generate_mutations", system_name, {
        "count": count, "template": template_name, "optimize": optimize
    })
    return True


# ─── Validation ─────────────────────────────────────────────────────────────

def validate_system(system_name=None):
    """Validate .mut files for correctness."""
    if system_name:
        dirs = [SYSTEMS_DIR / system_name]
    else:
        dirs = [d for d in SYSTEMS_DIR.iterdir() if d.is_dir()] if SYSTEMS_DIR.exists() else []

    total_valid = 0
    total_warnings = 0
    total_errors = 0

    for sys_dir in dirs:
        sname = sys_dir.name
        mut_files = sorted(sys_dir.glob("*.mut"))
        if not mut_files:
            continue

        print(f"\nValidating {sname}: {len(mut_files)} files")
        seen_ids = set()

        for mf in mut_files:
            with open(mf) as f:
                content = f.read()

            # Check TYPE_ID
            m = re.search(r'^//\s*TYPE_ID:\s*(\d+)', content, re.MULTILINE)
            if not m:
                print(f"  ERROR: {mf.name} — missing TYPE_ID")
                total_errors += 1
                continue

            tid = int(m.group(1))
            if tid == 0:
                print(f"  ERROR: {mf.name} — TYPE_ID 0 is reserved")
                total_errors += 1
                continue
            if tid in seen_ids:
                print(f"  ERROR: {mf.name} — duplicate TYPE_ID {tid}")
                total_errors += 1
                continue
            seen_ids.add(tid)

            # Check NAME
            if not re.search(r'^//\s*NAME:', content, re.MULTILINE):
                print(f"  WARNING: {mf.name} — missing NAME header")
                total_warnings += 1

            # Check for body content
            body_lines = [l for l in content.split("\n")
                          if l.strip() and not l.strip().startswith("//")]
            if not body_lines:
                print(f"  ERROR: {mf.name} — empty body")
                total_errors += 1
                continue

            # Check for unsafe patterns
            if "1/0" in content or "/0.0" in content:
                print(f"  WARNING: {mf.name} — potential division by zero")
                total_warnings += 1

            total_valid += 1
            name_match = re.search(r'^//\s*NAME:\s*(.+)$', content, re.MULTILINE)
            name = name_match.group(1).strip() if name_match else "?"
            print(f"  [{tid:3d}] {name:40s} <- {mf.name}")

    print(f"\nValid: {total_valid}")
    print(f"Warnings: {total_warnings}")
    print(f"Errors: {total_errors}")
    print(f"\nVALIDATION {'COMPLETE' if total_errors == 0 else 'FAILED'}")
    return total_errors == 0


# ─── Full Rebuild ───────────────────────────────────────────────────────────

def full_rebuild():
    """Validate all systems and regenerate code."""
    print("=== Full Rebuild ===\n")

    # Step 1: Validate
    print("Step 1: Validating all systems...")
    if not validate_system():
        print("\nValidation failed — aborting rebuild.")
        return False

    # Step 2: Generate
    print("\nStep 2: Generating switch blocks...")
    import importlib.util
    gen_path = Path(__file__).parent / "generate_switch.py"
    if gen_path.exists():
        spec = importlib.util.spec_from_file_location("generate_switch", gen_path)
        gen = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(gen)
        gen.load_config()
        if SYSTEMS_DIR.exists():
            for sys_dir in sorted(SYSTEMS_DIR.iterdir()):
                if sys_dir.is_dir():
                    gen.generate_system(sys_dir.name)
    else:
        print("Warning: generate_switch.py not found, skipping code generation")

    print("\n=== Rebuild Complete ===")
    return True


# ─── CLI ────────────────────────────────────────────────────────────────────

def main():
    parser = argparse.ArgumentParser(
        description="Mutation Wizard — batch mutation creation and management"
    )
    parser.add_argument("--new-system", action="store_true",
                        help="Create a new system interactively")
    parser.add_argument("--batch-add", type=int, metavar="N",
                        help="Generate N mutations")
    parser.add_argument("--system", help="Target system name")
    parser.add_argument("--template", default="smooth_fold",
                        help="Template name (default: smooth_fold)")
    parser.add_argument("--optimize", action="store_true",
                        help="Enable parameter optimization")
    parser.add_argument("--validate", action="store_true",
                        help="Validate all .mut files")
    parser.add_argument("--list-templates", action="store_true",
                        help="List available templates")
    parser.add_argument("--full-rebuild", action="store_true",
                        help="Validate + regenerate all")
    args = parser.parse_args()

    if args.list_templates:
        print("\nAvailable Templates:\n")
        for name, tmpl in VARIATION_TEMPLATES.items():
            print(f"  {name:20s} — {tmpl['description']}")
            print(f"  {'':20s}   Params: {', '.join(tmpl['params'])}")
        return

    if args.new_system:
        create_system_interactive()
        return

    if args.batch_add:
        if not args.system:
            print("Error: --system required with --batch-add")
            sys.exit(1)
        # Auto-create system if it doesn't exist
        sys_dir = SYSTEMS_DIR / args.system
        if not sys_dir.exists():
            create_system_batch(args.system)
        generate_mutations(args.system, args.batch_add, args.template, args.optimize)
        return

    if args.validate:
        ok = validate_system(args.system)
        sys.exit(0 if ok else 1)

    if args.full_rebuild:
        ok = full_rebuild()
        sys.exit(0 if ok else 1)

    parser.print_help()


if __name__ == "__main__":
    main()
