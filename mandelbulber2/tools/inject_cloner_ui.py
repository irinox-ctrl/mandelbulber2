#!/usr/bin/env python3
"""
Inject cloner UI section into older primitive .ui files.
Extracts the cloner widgets from a reference UI (primitive_capsule.ui)
and inserts them into target files before the closing </layout> of gridLayout.
"""

import os
import sys
import shutil

DEPLOY_UI_DIR = os.path.join(
    os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
    "deploy", "share", "mandelbulber2", "formula", "ui"
)

REFERENCE_UI = os.path.join(DEPLOY_UI_DIR, "primitive_capsule.ui")

TARGET_PRIMITIVES = [
    "box", "sphere", "plane", "cylinder", "cone",
    "torus", "circle", "rectangle", "prism", "ellipsoid", "water"
]


def extract_cloner_xml(ref_path):
    """Extract cloner section from reference UI (rows 77-93 in capsule)."""
    with open(ref_path, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    # Find start: the <item> containing label_cloner (look ahead for label_cloner within 3 lines)
    start_idx = None
    for i, line in enumerate(lines):
        if '<item ' in line:
            # Check next few lines for label_cloner widget
            for j in range(i, min(i + 5, len(lines))):
                if 'name="label_cloner"' in lines[j]:
                    start_idx = i
                    break
            if start_idx is not None:
                break

    if start_idx is None:
        raise RuntimeError("Could not find start of cloner section in reference UI")

    # Find end: the </item> after comboBox_cloner_plane
    end_idx = None
    for i in range(start_idx + 1, len(lines)):
        if 'comboBox_cloner_plane' in lines[i]:
            # Find the closing </item> for this widget
            depth = 0
            for j in range(i, len(lines)):
                if '<item>' in lines[j] or '<item ' in lines[j]:
                    depth += 1
                if '</item>' in lines[j]:
                    if depth > 0:
                        depth -= 1
                    else:
                        end_idx = j
                        break
            break

    if end_idx is None:
        raise RuntimeError("Could not find end of cloner section in reference UI")

    return lines[start_idx:end_idx + 1]


def inject_cloner(target_path, cloner_lines):
    """Inject cloner XML before the gridLayout closing tag."""
    with open(target_path, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    # Find the </layout> that closes gridLayout, which is followed by
    #   </item>
    #   <item>
    #    <spacer name="verticalSpacer">
    inject_idx = None
    for i in range(len(lines) - 4):
        if lines[i].strip() == '</layout>':
            # Check next few lines for the spacer pattern
            next_lines = ''.join(lines[i:i+8])
            if 'verticalSpacer' in next_lines and '<spacer' in next_lines:
                inject_idx = i
                break

    if inject_idx is None:
        raise RuntimeError(f"Could not find injection point in {target_path}")

    # Build output: everything before inject_idx + cloner lines + everything from inject_idx
    output = lines[:inject_idx] + cloner_lines + lines[inject_idx:]

    with open(target_path, 'w', encoding='utf-8') as f:
        f.writelines(output)


def main():
    print(f"Reference UI: {REFERENCE_UI}")
    if not os.path.exists(REFERENCE_UI):
        print("ERROR: Reference UI not found")
        sys.exit(1)

    cloner_lines = extract_cloner_xml(REFERENCE_UI)
    print(f"Extracted {len(cloner_lines)} lines of cloner XML")

    for name in TARGET_PRIMITIVES:
        target_path = os.path.join(DEPLOY_UI_DIR, f"primitive_{name}.ui")
        if not os.path.exists(target_path):
            print(f"SKIP: {target_path} not found")
            continue

        # Backup
        backup_path = target_path + '.backup'
        shutil.copy2(target_path, backup_path)

        try:
            inject_cloner(target_path, cloner_lines)
            print(f"OK:    Injected cloner into primitive_{name}.ui")
        except RuntimeError as e:
            print(f"ERROR: {e}")
            # Restore backup
            shutil.copy2(backup_path, target_path)


if __name__ == '__main__':
    main()
