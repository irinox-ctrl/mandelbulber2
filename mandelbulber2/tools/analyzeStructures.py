#!/usr/bin/env python3
"""
Mandelbulber2 Structure Analyzer
==================================
Comprehensive analysis tool for sCommonParams, CalcParams, and Morph systems.

Based on comprehensive studies:
- SCOMMONPARAMS_COMPREHENSIVE_STUDY.md
- CALCPARAMS_COMPREHENSIVE_STUDY.md
- MORPH_SYSTEM_COMPREHENSIVE_STUDY.md

Usage:
    ./analyzeStructures.py --check-commonparams
    ./analyzeStructures.py --check-calcparams
    ./analyzeStructures.py --check-morph
    ./analyzeStructures.py --check-alignment
    ./analyzeStructures.py --find-unused-params
    ./analyzeStructures.py --validate-all
    ./analyzeStructures.py --report
"""

import os
import re
import sys
import argparse
from pathlib import Path
from typing import Dict, List, Tuple, Set

# ============================================================================
# CONFIGURATION
# ============================================================================

MANDELBULBER_ROOT = Path(__file__).parent.parent
SRC_DIR = MANDELBULBER_ROOT / "src"
OPENCL_DIR = MANDELBULBER_ROOT / "opencl"

# Known structure definitions
STRUCTURES = {
    'sCommonParams': {
        'cpu_file': SRC_DIR / 'common_params.hpp',
        'cpu_start': 191,
        'cpu_end': 266,
        'opencl_file': OPENCL_DIR / 'common_params_cl.hpp',
        'opencl_start': 214,
        'opencl_end': 291,
        'member_count': 70,
    },
    'sClCalcParams': {
        'opencl_file': OPENCL_DIR / 'input_data_structures.h',
        'opencl_start': 72,
        'opencl_end': 83,
        'member_count': 9,
    },
    'enumMorphType': {
        'cpu_file': SRC_DIR / 'one_parameter.hpp',
        'cpu_start': 53,
        'cpu_end': 66,
        'type_count': 11,
    }
}

# ============================================================================
# ANALYSIS FUNCTIONS
# ============================================================================

def read_file_lines(filepath: Path, start: int, end: int) -> List[str]:
    """Read specific lines from a file."""
    if not filepath.exists():
        print(f"❌ File not found: {filepath}")
        return []

    with open(filepath, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    return lines[start-1:end]


def extract_struct_members(lines: List[str]) -> List[Dict[str, str]]:
    """Extract struct member definitions."""
    members = []

    for line in lines:
        line = line.strip()
        if not line or line.startswith('//') or line.startswith('/*'):
            continue
        if line.startswith('struct') or line.startswith('{') or line.startswith('}'):
            continue

        # Parse member: type name; or type name = value;
        match = re.match(r'(\w+(?:\s*\*)?)\s+(\w+)(?:\s*=\s*[^;]+)?;', line)
        if match:
            members.append({
                'type': match.group(1).strip(),
                'name': match.group(2).strip(),
                'line': line
            })

    return members


def check_commonparams_alignment():
    """Check sCommonParams CPU/OpenCL alignment."""
    print("\n" + "="*80)
    print("CHECKING sCommonParams ALIGNMENT")
    print("="*80)

    config = STRUCTURES['sCommonParams']

    # Read CPU struct
    cpu_lines = read_file_lines(config['cpu_file'], config['cpu_start'], config['cpu_end'])
    cpu_members = extract_struct_members(cpu_lines)

    # Read OpenCL struct
    opencl_lines = read_file_lines(config['opencl_file'], config['opencl_start'], config['opencl_end'])
    opencl_members = extract_struct_members(opencl_lines)

    print(f"\n📊 CPU members: {len(cpu_members)}")
    print(f"📊 OpenCL members: {len(opencl_members)}")

    # Check for missing members
    cpu_names = {m['name'] for m in cpu_members}
    opencl_names = {m['name'] for m in opencl_members if not m['name'].startswith('pad')}

    missing_in_opencl = cpu_names - opencl_names
    extra_in_opencl = opencl_names - cpu_names

    if missing_in_opencl:
        print(f"\n⚠️  Members in CPU but NOT in OpenCL:")
        for name in sorted(missing_in_opencl):
            print(f"   - {name}")

    if extra_in_opencl:
        print(f"\n⚠️  Members in OpenCL but NOT in CPU:")
        for name in sorted(extra_in_opencl):
            print(f"   - {name}")

    if not missing_in_opencl and not extra_in_opencl:
        print("\n✅ All members present in both CPU and OpenCL")

    # Check for padding fields
    padding_count = sum(1 for m in opencl_members if m['name'].startswith('pad'))
    if padding_count > 0:
        print(f"\n📝 Padding fields found: {padding_count}")
        for m in opencl_members:
            if m['name'].startswith('pad'):
                print(f"   - {m['line']}")

    return len(cpu_members), len(opencl_members), padding_count


def check_calcparams_structure():
    """Check sClCalcParams structure definition."""
    print("\n" + "="*80)
    print("CHECKING sClCalcParams STRUCTURE")
    print("="*80)

    config = STRUCTURES['sClCalcParams']

    # Read OpenCL struct
    opencl_lines = read_file_lines(config['opencl_file'], config['opencl_start'], config['opencl_end'])
    opencl_members = extract_struct_members(opencl_lines)

    print(f"\n📊 OpenCL members: {len(opencl_members)}")
    print(f"📊 Expected members: {config['member_count']}")

    if len(opencl_members) != config['member_count']:
        print(f"\n⚠️  Member count mismatch!")
        print(f"   Expected: {config['member_count']}")
        print(f"   Found: {len(opencl_members)}")
    else:
        print("\n✅ Member count matches expected")

    # List all members
    print("\n📝 Members:")
    for m in opencl_members:
        print(f"   {m['type']:20s} {m['name']}")

    # Check for required members (based on comprehensive study)
    required = ['N', 'deltaDEMaxN', 'randomSeed', 'iterThreshMode',
                'normalCalculationMode', 'orbitTrapIndex', 'orbitTrap',
                'distThresh', 'detailSize']

    found_names = {m['name'] for m in opencl_members}
    missing = set(required) - found_names

    if missing:
        print(f"\n⚠️  Missing required members:")
        for name in sorted(missing):
            print(f"   - {name}")
    else:
        print("\n✅ All required members present")

    return len(opencl_members)


def check_morph_types():
    """Check morph type enumeration."""
    print("\n" + "="*80)
    print("CHECKING MORPH TYPE ENUMERATION")
    print("="*80)

    config = STRUCTURES['enumMorphType']

    # Read enum
    enum_lines = read_file_lines(config['cpu_file'], config['cpu_start'], config['cpu_end'])

    # Extract enum values
    morph_types = []
    for line in enum_lines:
        line = line.strip()
        if not line or line.startswith('//') or line.startswith('enum') or line == '{' or line == '};':
            continue

        match = re.match(r'(\w+)\s*(?:=\s*(\d+))?,?', line)
        if match:
            name = match.group(1)
            value = match.group(2) if match.group(2) else None
            morph_types.append({'name': name, 'value': value, 'line': line})

    print(f"\n📊 Morph types found: {len(morph_types)}")
    print(f"📊 Expected types: {config['type_count']}")

    if len(morph_types) != config['type_count']:
        print(f"\n⚠️  Type count mismatch!")
    else:
        print("\n✅ Type count matches expected")

    # List all types
    print("\n📝 Morph Types:")
    for idx, mt in enumerate(morph_types):
        value = mt['value'] if mt['value'] else str(idx)
        print(f"   {value:3s} - {mt['name']}")

    # Check for expected types
    expected = ['morphNone', 'morphLinear', 'morphLinearAngle', 'morphCatMullRom',
                'morphCatMullRomAngle', 'morphAkima', 'morphAkimaAngle', 'morphCubic',
                'morphCubicAngle', 'morphSteffen', 'morphSteffenAngle']

    found_names = {mt['name'] for mt in morph_types}
    missing = set(expected) - found_names
    extra = found_names - set(expected)

    if missing:
        print(f"\n⚠️  Missing expected types:")
        for name in sorted(missing):
            print(f"   - {name}")

    if extra:
        print(f"\n✅ New types added:")
        for name in sorted(extra):
            print(f"   + {name}")

    if not missing and not extra:
        print("\n✅ All expected types present")

    return len(morph_types)


def find_unused_commonparams():
    """Find potentially unused sCommonParams members."""
    print("\n" + "="*80)
    print("FINDING UNUSED sCommonParams MEMBERS")
    print("="*80)

    config = STRUCTURES['sCommonParams']

    # Read CPU struct
    cpu_lines = read_file_lines(config['cpu_file'], config['cpu_start'], config['cpu_end'])
    cpu_members = extract_struct_members(cpu_lines)

    print(f"\n🔍 Searching for usage of {len(cpu_members)} members...")

    # Search for usage in src and opencl directories
    unused = []

    for member in cpu_members:
        name = member['name']

        # Search in src files
        src_matches = 0
        for src_file in SRC_DIR.rglob("*.cpp"):
            with open(src_file, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
                if name in content:
                    src_matches += 1

        # Search in opencl files
        opencl_matches = 0
        for opencl_file in OPENCL_DIR.rglob("*.cl"):
            with open(opencl_file, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
                if name in content:
                    opencl_matches += 1

        if src_matches == 0 and opencl_matches == 0:
            unused.append(member)
            print(f"   ⚠️  {member['type']:30s} {name:40s} - NOT FOUND")

    if unused:
        print(f"\n⚠️  Potentially unused members: {len(unused)}")
    else:
        print(f"\n✅ All members appear to be in use")

    return unused


def validate_calcparams_initialization():
    """Validate calcParams initialization patterns in OpenCL."""
    print("\n" + "="*80)
    print("VALIDATING calcParams INITIALIZATION")
    print("="*80)

    # Expected initialization pattern
    expected_pattern = [
        'calcParam.N',
        'calcParam.normalCalculationMode',
        'calcParam.iterThreshMode',
        'calcParam.distThresh',
        'calcParam.detailSize',
    ]

    # Search in OpenCL engines
    engines = list((OPENCL_DIR / 'engines').glob('*.cl'))

    print(f"\n🔍 Checking {len(engines)} OpenCL engine files...")

    issues = []

    for engine_file in engines:
        with open(engine_file, 'r', encoding='utf-8') as f:
            content = f.read()

        # Check if file uses calcParam
        if 'sClCalcParams calcParam' not in content:
            continue

        print(f"\n📄 {engine_file.name}:")

        # Check for each expected initialization
        missing = []
        for pattern in expected_pattern:
            if pattern not in content:
                missing.append(pattern)

        if missing:
            print(f"   ⚠️  Missing initialization:")
            for m in missing:
                print(f"      - {m}")
            issues.append({'file': engine_file.name, 'missing': missing})
        else:
            print(f"   ✅ Complete initialization")

    if issues:
        print(f"\n⚠️  Files with incomplete initialization: {len(issues)}")
    else:
        print(f"\n✅ All files have complete calcParam initialization")

    return issues


def generate_report():
    """Generate comprehensive analysis report."""
    print("\n" + "="*80)
    print("COMPREHENSIVE STRUCTURE ANALYSIS REPORT")
    print("="*80)
    print(f"\nMandelbulber2 Root: {MANDELBULBER_ROOT}")
    print(f"Analysis Date: {__import__('datetime').datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")

    # Run all checks
    cpu_count, opencl_count, padding = check_commonparams_alignment()
    calcparams_count = check_calcparams_structure()
    morph_count = check_morph_types()
    unused = find_unused_commonparams()
    init_issues = validate_calcparams_initialization()

    # Summary
    print("\n" + "="*80)
    print("SUMMARY")
    print("="*80)
    print(f"\n✅ sCommonParams:")
    print(f"   - CPU members: {cpu_count}")
    print(f"   - OpenCL members: {opencl_count}")
    print(f"   - Padding fields: {padding}")
    print(f"   - Unused members: {len(unused)}")

    print(f"\n✅ sClCalcParams:")
    print(f"   - Members: {calcparams_count}")
    print(f"   - Initialization issues: {len(init_issues)}")

    print(f"\n✅ Morph System:")
    print(f"   - Morph types: {morph_count}")

    print("\n" + "="*80)
    print("RECOMMENDATIONS")
    print("="*80)

    if unused:
        print("\n⚠️  Consider removing or documenting unused sCommonParams members")

    if init_issues:
        print("\n⚠️  Fix incomplete calcParams initialization in OpenCL engines")

    if cpu_count != opencl_count - padding:
        print("\n⚠️  Investigate CPU/OpenCL member count discrepancy")

    if not unused and not init_issues and cpu_count == opencl_count - padding:
        print("\n✅ No issues found - all structures are well-formed!")

    print("\n")


# ============================================================================
# MAIN
# ============================================================================

def main():
    parser = argparse.ArgumentParser(
        description='Mandelbulber2 Structure Analyzer',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__
    )

    parser.add_argument('--check-commonparams', action='store_true',
                        help='Check sCommonParams alignment')
    parser.add_argument('--check-calcparams', action='store_true',
                        help='Check sClCalcParams structure')
    parser.add_argument('--check-morph', action='store_true',
                        help='Check morph type enumeration')
    parser.add_argument('--check-alignment', action='store_true',
                        help='Check structure alignment')
    parser.add_argument('--find-unused-params', action='store_true',
                        help='Find unused parameters')
    parser.add_argument('--validate-init', action='store_true',
                        help='Validate calcParams initialization')
    parser.add_argument('--validate-all', action='store_true',
                        help='Run all validation checks')
    parser.add_argument('--report', action='store_true',
                        help='Generate comprehensive report')

    args = parser.parse_args()

    # If no arguments, show help
    if len(sys.argv) == 1:
        parser.print_help()
        sys.exit(0)

    # Run requested checks
    if args.check_commonparams or args.validate_all:
        check_commonparams_alignment()

    if args.check_calcparams or args.validate_all:
        check_calcparams_structure()

    if args.check_morph or args.validate_all:
        check_morph_types()

    if args.check_alignment or args.validate_all:
        check_commonparams_alignment()

    if args.find_unused_params or args.validate_all:
        find_unused_commonparams()

    if args.validate_init or args.validate_all:
        validate_calcparams_initialization()

    if args.report or args.validate_all:
        generate_report()


if __name__ == '__main__':
    main()
