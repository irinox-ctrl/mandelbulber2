#!/usr/bin/env python3
"""
FEATURE PRESENCE CHECKER
=========================
Check welke features WEL/NIET in current repo zitten!

Specifiek checken:
- Cloner system
- Epic repeat modes
- Deformation system
- Pivot point / world space system
- Emission system

Author: Claude + Joeri
Date: 2026-04-19
"""

from pathlib import Path
import re

def check_feature_in_file(file_path: Path, keywords: list) -> dict:
    """Check if keywords present in file"""
    results = {kw: [] for kw in keywords}

    try:
        with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
            for line_num, line in enumerate(f, 1):
                for kw in keywords:
                    if kw.lower() in line.lower():
                        results[kw].append((line_num, line.strip()[:80]))
    except:
        pass

    return results

def main():
    print("=" * 70)
    print("🔍 FEATURE PRESENCE CHECKER")
    print("=" * 70)
    print()

    # Check if we're in dev_tools or root
    if Path.cwd().name == "dev_tools":
        repo_dir = Path.cwd().parent / "mandelbulber2"
    else:
        repo_dir = Path.cwd() / "mandelbulber2"

    # Features te checken
    features = {
        'Epic Repeat System': {
            'keywords': ['epic_repeat', 'repeatMode', 'repeat_mode', 'MODE_GRID', 'MODE_BRICK', 'MODE_HONEYCOMB'],
            'files': ['src/initparameters.cpp', 'src/compute_fractal.cpp', 'src/common_params.hpp']
        },
        'Cloner System': {
            'keywords': ['cloner', 'clone_count', 'clone_offset', 'cloning'],
            'files': ['src/initparameters.cpp', 'src/compute_fractal.cpp']
        },
        'Deformation System': {
            'keywords': ['deformation', 'deform_bend', 'deform_twist', 'deform_taper'],
            'files': ['src/initparameters.cpp', 'src/compute_fractal.cpp']
        },
        'Pivot/World Space': {
            'keywords': ['pivot', 'world_space', 'world_coord', 'rotation_center', 'worldCoord'],
            'files': ['src/initparameters.cpp', 'src/compute_fractal.cpp', 'src/common_params.hpp']
        },
        'Emission System': {
            'keywords': ['emission', 'emitter', 'primitive_emission'],
            'files': ['src/initparameters.cpp', 'src/primitive.cpp']
        },
        'Fake Lights V2': {
            'keywords': ['fakeLightsPositionMode', 'fakeLightsMode', 'pathSpiral', 'pathCircle'],
            'files': ['src/common_params.hpp', 'src/shader_fake_lights.cpp']
        }
    }

    # Check each feature
    for feature_name, feature_data in features.items():
        print(f"{'─'*70}")
        print(f"🔧 {feature_name}")
        print(f"{'─'*70}")

        found_any = False

        for file_rel in feature_data['files']:
            file_path = repo_dir / file_rel

            if not file_path.exists():
                print(f"  ⚠️  File not found: {file_rel}")
                continue

            results = check_feature_in_file(file_path, feature_data['keywords'])

            # Count matches
            total_matches = sum(len(v) for v in results.values())

            if total_matches > 0:
                found_any = True
                print(f"  ✅ {file_rel}: {total_matches} matches")

                # Show enkele matches
                for kw, matches in results.items():
                    if matches:
                        print(f"     - {kw}: {len(matches)} occurrences")
                        # Show first match
                        if matches:
                            line_num, line = matches[0]
                            print(f"       Line {line_num}: {line}")
            else:
                print(f"  ❌ {file_rel}: NO matches")

        if found_any:
            print(f"\n  🎯 STATUS: ✅ PRESENT in repo")
        else:
            print(f"\n  🎯 STATUS: ❌ MISSING from repo")

        print()

    # Summary
    print("=" * 70)
    print("📊 FEATURE SUMMARY")
    print("=" * 70)
    print()

    for feature_name, feature_data in features.items():
        # Quick check
        found = False
        for file_rel in feature_data['files']:
            file_path = repo_dir / file_rel
            if file_path.exists():
                results = check_feature_in_file(file_path, feature_data['keywords'])
                if any(len(v) > 0 for v in results.values()):
                    found = True
                    break

        status = "✅ PRESENT" if found else "❌ MISSING"
        print(f"  {status}  {feature_name}")

    print()

if __name__ == "__main__":
    main()
