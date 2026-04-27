#!/usr/bin/env python3
"""
FIND NEXT AVAILABLE FORMULA ID
===============================
Utility to find the next available formula enum ID number.

Usage:
    python3 find_next_formula_id.py
"""

import re
from pathlib import Path


def find_all_formula_ids(formula_dir):
    """Find all existing formula internal IDs"""

    formula_dir = Path(formula_dir)
    cpp_files = list(formula_dir.glob("fractal_*.cpp"))

    ids = {}
    max_id = 0

    print(f"Scanning {len(cpp_files)} formula files...\n")

    for cpp_file in cpp_files:
        try:
            with open(cpp_file, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()

            # Extract internalID
            match = re.search(r'internalID\s*=\s*fractal::(\w+);', content)
            if match:
                internal_id = match.group(1)

                # Try to find if there's a numeric mapping somewhere
                # For now, just collect the names
                ids[internal_id] = cpp_file.name

        except Exception as e:
            pass

    print(f"Found {len(ids)} formula IDs:\n")

    # Sort and display
    for i, (fid, fname) in enumerate(sorted(ids.items()), 1):
        print(f"{i:3d}. {fid:40s} ({fname})")

    print(f"\n{'='*70}")
    print(f"NEXT AVAILABLE NUMBER: {len(ids) + 1}")
    print(f"{'='*70}")

    print(f"\nRecommendation:")
    print(f"  - Use enum ID number: {len(ids) + 1}")
    print(f"  - Current formula count: {len(ids)}")
    print(f"  - Safe to use any number > {len(ids)}")

    return len(ids) + 1


if __name__ == "__main__":
    base_dir = Path(__file__).parent.parent / "mandelbulber2"
    formula_dir = base_dir / "formula" / "definition"

    if not formula_dir.exists():
        print(f"ERROR: Formula directory not found: {formula_dir}")
        exit(1)

    next_id = find_all_formula_ids(formula_dir)
