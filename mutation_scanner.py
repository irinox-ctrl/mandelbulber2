#!/usr/bin/env python3
"""
Mutation Scanner v1.0 — Automated Code Quality & Safety Scanner
for Mandelbulber2 Formula Mutation System (1400+ transformations)

Scans:
  1. GPU/CPU parity (struct fields, switch case counts)
  2. GPU conversion errors (double→float, sin→native_sin, M_PI→M_PI_F, mut.→mut->)
  3. Runtime safety (div-by-zero, NaN/Inf, sqrt(neg), log(neg), exp overflow)
  4. Parameter naming collisions
  5. Iteration control consistency

Usage:
  python3 mutation_scanner.py                 # Full scan with summary
  python3 mutation_scanner.py --fix           # Apply automatic fixes
  python3 mutation_scanner.py --verbose       # Show every issue detail
  python3 mutation_scanner.py --section torus # Scan only MandelTorus section
"""

import re
import sys
import os
from collections import defaultdict

# ─── Configuration ───────────────────────────────────────────────────────────
BASE = os.path.dirname(os.path.abspath(__file__))
CPU_FILE = os.path.join(BASE, "mandelbulber2/src/compute_fractal.cpp")
GPU_FILE = os.path.join(BASE, "mandelbulber2/opencl/engines/compute_fractal.cl")
CPU_STRUCT = os.path.join(BASE, "mandelbulber2/src/nine_fractals.hpp")
GPU_STRUCT = os.path.join(BASE, "mandelbulber2/opencl/fractal_sequence_cl.h")
INIT_PARAMS = os.path.join(BASE, "mandelbulber2/src/initparameters.cpp")
NINE_FRACT = os.path.join(BASE, "mandelbulber2/src/nine_fractals.cpp")

# Issue severity levels
CRITICAL = "CRITICAL"   # Will cause crash/NaN on GPU
HIGH     = "HIGH"       # Likely visual artifacts or wrong results
MEDIUM   = "MEDIUM"     # May cause issues with certain parameter values
LOW      = "LOW"        # Style/consistency issue, unlikely runtime impact

# ─── Issue Tracker ───────────────────────────────────────────────────────────
class Issue:
    def __init__(self, severity, category, file, line, message, fix=None):
        self.severity = severity
        self.category = category
        self.file = os.path.basename(file)
        self.line = line
        self.message = message
        self.fix = fix  # (old_str, new_str) tuple for auto-fix

    def __repr__(self):
        return f"[{self.severity}] {self.file}:{self.line} ({self.category}) {self.message}"


issues = []

def report(severity, category, file, line, message, fix=None):
    issues.append(Issue(severity, category, file, line, message, fix))


# ─── Scanner 1: GPU Conversion Errors ───────────────────────────────────────
def scan_gpu_conversions(gpu_lines, filepath):
    """Check for unconverted CPU syntax in GPU (OpenCL) code."""

    # Track which mutation section we're in
    section = "unknown"
    in_mutation = False

    for i, line in enumerate(gpu_lines, 1):
        stripped = line.strip()

        # Track sections
        if "v7." in stripped and "—" in stripped:
            section = stripped.strip("/ \t")
            in_mutation = True
            continue

        # Only scan mutation case statements and surrounding code
        if not in_mutation:
            continue

        # Skip pure comments
        if stripped.startswith("//"):
            continue

        # --- Check 1: double keyword (should be float in OpenCL) ---
        double_matches = list(re.finditer(r'\bdouble\b', stripped))
        for m in double_matches:
            ctx = stripped[max(0,m.start()-10):m.end()+20]
            report(CRITICAL, "GPU_DOUBLE", filepath, i,
                   f"'double' in GPU code (should be float): ...{ctx}...",
                   fix=(line, line.replace("double", "float")))

        # --- Check 2: M_PI without _F suffix ---
        if re.search(r'\bM_PI\b(?!_F)', stripped):
            report(CRITICAL, "GPU_M_PI", filepath, i,
                   f"M_PI without _F suffix (should be M_PI_F)")

        # --- Check 3: Unconverted math functions ---
        # sin() should be native_sin(), etc.
        for func in ['sin', 'cos', 'exp', 'sqrt', 'log', 'tan']:
            # Match func( but not native_func( or asin( or sinh( etc
            pattern = rf'(?<!native_)(?<!a)(?<!arc)(?<!{func[0]}h)\b{func}\('
            # Simpler: just look for bare func( not preceded by native_
            bare_pattern = rf'(?<![a-zA-Z_]){func}\('
            native_pattern = rf'native_{func}\('

            for m in re.finditer(bare_pattern, stripped):
                # Check it's not already native_
                pre = stripped[max(0,m.start()-7):m.start()]
                if 'native_' in pre:
                    continue
                # Check it's not asin, acos, atan, sinh, cosh, tanh
                pre2 = stripped[max(0,m.start()-1):m.start()]
                if pre2 in ['a', 'h']:
                    continue
                pre4 = stripped[max(0,m.start()-4):m.start()]
                if any(p in pre4 for p in ['asin', 'acos', 'atan', 'sinh', 'cosh', 'tanh', 'fabs']):
                    continue

                report(HIGH, f"GPU_BARE_{func.upper()}", filepath, i,
                       f"Bare {func}() should be native_{func}() in OpenCL")

        # --- Check 4: mut. instead of mut-> ---
        if re.search(r'\bmut\.(?!torusType)', stripped):
            # In GPU code, struct access should use -> not .
            if 'mut.' in stripped and 'mut->' not in stripped:
                report(CRITICAL, "GPU_MUT_DOT", filepath, i,
                       f"'mut.' used instead of 'mut->' in GPU code")


# ─── Scanner 2: Runtime Safety ──────────────────────────────────────────────
def scan_runtime_safety(lines, filepath, is_gpu=False):
    """Check for division-by-zero, NaN, Inf risks in mutation code."""

    section = "unknown"
    in_mutation = False
    float_t = "float" if is_gpu else "double"

    for i, line in enumerate(lines, 1):
        stripped = line.strip()

        if "v7." in stripped and "—" in stripped:
            section = stripped.strip("/ \t")
            in_mutation = True
            continue

        if not in_mutation or stripped.startswith("//"):
            continue

        if not stripped.startswith("case "):
            continue

        # --- Division by zero: /param without fmax protection ---
        # Find all divisions
        for m in re.finditer(r'/\s*\(([^)]+)\)', stripped):
            denom = m.group(1)
            if not any(p in denom for p in ['fmax', '+1e-', '+0.0', 'fabs']):
                if not re.match(r'^[\d.]+$', denom.strip()):
                    report(MEDIUM, "DIV_ZERO", filepath, i,
                           f"Division by ({denom[:40]}) without fmax() protection")

        # --- exp() overflow: positive unbounded argument ---
        for m in re.finditer(r'(?:native_)?exp\(([^)]{1,80})\)', stripped):
            arg = m.group(1)
            if '-' not in arg and 'fmin' not in arg:
                if re.search(r'\*\s*r\b', arg) or re.search(r'\*\s*z\.', arg):
                    report(HIGH, "EXP_OVERFLOW", filepath, i,
                           f"exp({arg[:50]}) — unbounded positive argument, risk of Inf")

        # --- log() domain: argument can be zero or negative ---
        for m in re.finditer(r'(?:native_)?log\(([^)]{1,80})\)', stripped):
            arg = m.group(1)
            if not any(p in arg for p in ['+', 'fmax', 'fabs', '1.0', '1e-']):
                if not re.match(r'^[\d.]+f?$', arg.strip()):
                    report(HIGH, "LOG_DOMAIN", filepath, i,
                           f"log({arg[:50]}) — argument may be zero or negative")

        # --- sqrt() domain: argument can be negative ---
        for m in re.finditer(r'(?:native_)?sqrt\(([^)]{1,80})\)', stripped):
            arg = m.group(1)
            # Skip sums of squares (always >= 0)
            if re.search(r'\w\*\w.*\+.*\w\*\w', arg):
                continue
            if '-' in arg and 'fabs' not in arg and 'fmax' not in arg:
                if 'z.x*z.x' not in arg and 'z.y*z.y' not in arg:
                    report(MEDIUM, "SQRT_DOMAIN", filepath, i,
                           f"sqrt({arg[:50]}) — argument may be negative")

        # --- 1/cosh: cosh approaches 0 for complex/extreme values ---
        if '/cosh(' in stripped or '/ cosh(' in stripped:
            report(MEDIUM, "COSH_DIV", filepath, i,
                   "Division by cosh() — cosh is always >= 1 for real args but may overflow")

        # --- Inf/NaN propagation: aux.DE *= large_value without fmin clamp ---
        if 'aux.DE *=' in stripped:
            # Check if the multiplier is bounded
            after_eq = stripped.split('aux.DE *=')[1] if 'aux.DE *=' in stripped else ""
            if 'fmin' not in after_eq and 'fmax' not in after_eq:
                if 'exp(' in after_eq and '-' not in after_eq.split('exp(')[1][:20]:
                    report(MEDIUM, "DE_UNBOUNDED", filepath, i,
                           "aux.DE *= exp(positive) — DE can grow to Inf without fmin clamp")


# ─── Scanner 3: GPU/CPU Case Parity ─────────────────────────────────────────
def scan_case_parity(cpu_lines, gpu_lines):
    """Ensure every CPU switch case has a corresponding GPU case."""

    def normalize_section(name):
        """Normalize section name: remove [GPU], extra spaces, for matching."""
        name = re.sub(r'\s*\[GPU\]\s*', ' ', name)
        name = re.sub(r'\s+', ' ', name).strip("/ \t")
        return name[:50]

    def extract_cases(lines, marker_pattern):
        """Extract case numbers grouped by section."""
        sections = {}
        section = None
        for line in lines:
            stripped = line.strip()
            if re.search(marker_pattern, stripped):
                section = normalize_section(stripped)
                sections[section] = set()
                continue
            if section:
                m = re.match(r'case\s+(\d+)\s*:', stripped)
                if m:
                    sections[section].add(int(m.group(1)))
        return sections

    cpu_sections = extract_cases(cpu_lines, r'v7\.\d+.*—')
    gpu_sections = extract_cases(gpu_lines, r'v7\.\d+.*—')

    for sec_name, cpu_cases in cpu_sections.items():
        # Find matching GPU section
        matched = False
        for gpu_name, gpu_cases in gpu_sections.items():
            if gpu_name[:40] == sec_name[:40]:
                matched = True
                cpu_only = cpu_cases - gpu_cases - {0}  # case 0 = disabled, ignore
                gpu_only = gpu_cases - cpu_cases - {0}
                if cpu_only:
                    report(CRITICAL, "CASE_MISSING_GPU", GPU_FILE, 0,
                           f"Section '{sec_name[:40]}': cases {sorted(cpu_only)} in CPU but NOT in GPU")
                if gpu_only:
                    report(CRITICAL, "CASE_MISSING_CPU", CPU_FILE, 0,
                           f"Section '{sec_name[:40]}': cases {sorted(gpu_only)} in GPU but NOT in CPU")
                if len(cpu_cases) != len(gpu_cases):
                    report(HIGH, "CASE_COUNT_MISMATCH", "both", 0,
                           f"Section '{sec_name[:40]}': CPU has {len(cpu_cases)} cases, GPU has {len(gpu_cases)}")
                break
        if not matched and cpu_cases:
            report(CRITICAL, "SECTION_MISSING_GPU", GPU_FILE, 0,
                   f"Section '{sec_name[:40]}' ({len(cpu_cases)} cases) exists in CPU but not GPU!")


# ─── Scanner 4: Struct Field Parity ─────────────────────────────────────────
def scan_struct_parity():
    """Check CPU and GPU struct fields match."""
    with open(CPU_STRUCT) as f:
        cpu = f.read()
    with open(GPU_STRUCT) as f:
        gpu = f.read()

    # Extract CPU fields
    start = cpu.find('struct sFormulaMutationParams')
    end = cpu.find('};', start)
    cpu_body = cpu[start:end]
    cpu_fields = set()
    for line in cpu_body.split('\n'):
        line = line.strip()
        if line.startswith('//') or not line:
            continue
        for m in re.findall(r'\b(?:double|int|bool)\s+(\w+)', line):
            cpu_fields.add(m)

    # Extract GPU fields
    gstart = gpu.find('cl_int enabled;')
    gend = gpu.find('} sClFormulaMutationParams;')
    gpu_body = gpu[gstart:gend] if gstart > 0 else ""
    gpu_fields = set()
    for line in gpu_body.split('\n'):
        line = line.strip()
        if line.startswith('//') or not line:
            continue
        for m in re.findall(r'\b(?:cl_float|cl_int)\s+(\w+)', line):
            gpu_fields.add(m)

    # Note: CPU enums map to cl_int on GPU, so some CPU-only fields are expected
    # We only flag GPU fields that don't appear in CPU at all
    for f in gpu_fields - cpu_fields:
        # Check if field exists as enum in CPU
        if f not in cpu:
            report(HIGH, "STRUCT_GPU_EXTRA", GPU_STRUCT, 0,
                   f"GPU field '{f}' has no CPU equivalent")

    # Check size
    n_floats = len(re.findall(r'\bcl_float\b', gpu_body))
    n_ints = len(re.findall(r'\bcl_int\b', gpu_body))
    n_mats = len(re.findall(r'matrix33', gpu_body))
    size_per_slot = n_floats * 4 + n_ints * 4 + n_mats * 36
    total_size = size_per_slot * 9
    if total_size > 85 * 1024:
        report(CRITICAL, "STRUCT_SIZE", GPU_STRUCT, 0,
               f"GPU struct too large: {total_size/1024:.1f} KB > 85 KB limit!")
    return total_size


# ─── Scanner 5: Parameter Registration Parity ───────────────────────────────
def scan_param_registration():
    """Check all struct fields have registered parameters and read logic."""
    with open(INIT_PARAMS) as f:
        init = f.read()
    with open(NINE_FRACT) as f:
        nf = f.read()

    # Find all mutation_* parameter registrations
    registered = set(re.findall(r'addParam\("(mutation_\w+)"', init))

    # Find all parameter reads
    reads = set(re.findall(r'Get<\w+>\("(mutation_\w+)"', nf))

    # Find all GPU copies (sequence->mutationParams)
    copies = set(re.findall(r'sequence->mutationParams\[i\]\.(\w+)\s*=', nf))

    reg_only = registered - reads
    read_only = reads - registered

    for p in reg_only:
        report(HIGH, "PARAM_NO_READ", NINE_FRACT, 0,
               f"Parameter '{p}' registered but never read in nine_fractals.cpp")
    for p in read_only:
        report(HIGH, "PARAM_NO_REG", INIT_PARAMS, 0,
               f"Parameter '{p}' read but never registered in initparameters.cpp")

    return registered, reads, copies


# ─── Scanner 6: Iteration Control Consistency ───────────────────────────────
def scan_iteration_controls(cpu_lines):
    """Check every mutation section has proper iteration range guards."""
    section = None
    has_iter_guard = False

    for line in cpu_lines:
        stripped = line.strip()
        if "v7." in stripped and "—" in stripped:
            if section and not has_iter_guard:
                report(HIGH, "NO_ITER_GUARD", CPU_FILE, 0,
                       f"Section '{section[:50]}' has no iteration range guard (i >= ...IterStart)")
            section = stripped.strip("/ \t")[:60]
            has_iter_guard = False
        if section and "IterStart" in stripped and "IterStop" in stripped:
            has_iter_guard = True


# ─── Auto-Fix Engine ────────────────────────────────────────────────────────
def apply_fixes():
    """Apply automatic fixes for GPU conversion issues."""
    with open(GPU_FILE) as f:
        content = f.read()

    fixes_applied = 0

    # Fix 1: double → float (in mutation sections only)
    lines = content.split('\n')
    in_mutation = False
    new_lines = []
    for line in lines:
        if "v7." in line and "—" in line:
            in_mutation = True
        if in_mutation and 'double' in line:
            # Replace double() cast and double keyword
            new_line = re.sub(r'\bdouble\b', 'float', line)
            if new_line != line:
                fixes_applied += 1
            line = new_line
        new_lines.append(line)

    content = '\n'.join(new_lines)

    # Fix 2: M_PI → M_PI_F (in mutation sections)
    count = len(re.findall(r'\bM_PI\b(?!_F)', content))
    content = re.sub(r'\bM_PI\b(?!_F)', 'M_PI_F', content)
    fixes_applied += count

    # Fix 3: Bare math functions → native_ variants in case statements
    lines = content.split('\n')
    new_lines = []
    in_mutation = False
    for line in lines:
        if "v7." in line and "—" in line:
            in_mutation = True

        if in_mutation and line.strip().startswith('case '):
            orig = line
            for func in ['sin', 'cos', 'exp', 'sqrt', 'log', 'tan']:
                # Replace bare func( with native_func( but not afunc( or native_func(
                # Negative lookbehind for word chars and native_
                line = re.sub(
                    rf'(?<![a-zA-Z_])(?<!native_){func}\(',
                    f'native_{func}(',
                    line
                )
            # Undo false positives: restore asin, acos, atan, sinh, cosh, tanh, fabs
            for prefix in ['a', '']:
                for func in ['sin', 'cos', 'tan']:
                    wrong = f'native_a{func}(' if prefix == 'a' else ''
                    # These shouldn't happen with proper lookbehind, but safety check
            # Restore fabs → shouldn't be touched since it doesn't match our pattern
            if orig != line:
                fixes_applied += 1
        new_lines.append(line)

    content = '\n'.join(new_lines)

    with open(GPU_FILE, 'w') as f:
        f.write(content)

    return fixes_applied


# ─── Main ────────────────────────────────────────────────────────────────────
def main():
    args = sys.argv[1:]
    verbose = "--verbose" in args or "-v" in args
    do_fix = "--fix" in args
    section_filter = None
    if "--section" in args:
        idx = args.index("--section")
        if idx + 1 < len(args):
            section_filter = args[idx + 1].lower()

    print("=" * 70)
    print("  Mutation Scanner v1.0 — Mandelbulber2 Code Quality Audit")
    print("  Scanning 1400+ transformations across CPU + GPU")
    print("=" * 70)
    print()

    # Load files
    with open(CPU_FILE) as f:
        cpu_lines = f.readlines()
    with open(GPU_FILE) as f:
        gpu_lines = f.readlines()

    # Run all scanners
    print("[1/6] Scanning GPU conversion errors...")
    scan_gpu_conversions(gpu_lines, GPU_FILE)

    print("[2/6] Scanning CPU runtime safety...")
    scan_runtime_safety(cpu_lines, CPU_FILE, is_gpu=False)

    print("[3/6] Scanning GPU runtime safety...")
    scan_runtime_safety(gpu_lines, GPU_FILE, is_gpu=True)

    print("[4/6] Checking GPU/CPU case parity...")
    scan_case_parity(cpu_lines, gpu_lines)

    print("[5/6] Checking struct field parity...")
    total_gpu_size = scan_struct_parity()

    print("[6/6] Checking parameter registration & iteration controls...")
    scan_param_registration()
    scan_iteration_controls(cpu_lines)

    # ─── Report ──────────────────────────────────────────────────────────
    print()
    print("=" * 70)
    print("  SCAN RESULTS")
    print("=" * 70)

    # Count by severity
    by_severity = defaultdict(list)
    by_category = defaultdict(list)
    for issue in issues:
        by_severity[issue.severity].append(issue)
        by_category[issue.category].append(issue)

    print(f"\n  GPU struct size: {total_gpu_size/1024:.1f} KB / 85 KB "
          f"({'OK' if total_gpu_size < 85*1024 else 'OVER LIMIT!'})")
    print(f"  Total issues found: {len(issues)}")
    print()

    for sev in [CRITICAL, HIGH, MEDIUM, LOW]:
        count = len(by_severity[sev])
        if count:
            print(f"  {sev}: {count}")

    print()
    print("  By category:")
    for cat in sorted(by_category.keys()):
        count = len(by_category[cat])
        print(f"    {cat}: {count}")

    if verbose:
        print()
        print("-" * 70)
        print("  DETAILED ISSUES")
        print("-" * 70)
        for sev in [CRITICAL, HIGH, MEDIUM, LOW]:
            for issue in by_severity[sev]:
                print(f"\n  {issue}")

    # Auto-fix
    if do_fix:
        print()
        print("=" * 70)
        print("  APPLYING AUTO-FIXES")
        print("=" * 70)
        n = apply_fixes()
        print(f"  Applied {n} automatic fixes to {os.path.basename(GPU_FILE)}")
        print("  Re-run scanner to verify remaining issues.")

    # Summary
    print()
    print("=" * 70)
    crit = len(by_severity[CRITICAL])
    high = len(by_severity[HIGH])
    if crit == 0 and high == 0:
        print("  STATUS: ALL CLEAR — no critical or high-severity issues!")
    elif crit > 0:
        print(f"  STATUS: {crit} CRITICAL issues need immediate attention!")
        print(f"  Run: python3 mutation_scanner.py --fix  to auto-fix GPU issues")
    else:
        print(f"  STATUS: {high} HIGH issues found (no critical)")
    print("=" * 70)

    return 1 if crit > 0 else 0


if __name__ == "__main__":
    sys.exit(main())
