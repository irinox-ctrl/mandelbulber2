#!/usr/bin/env python3
"""Inject MoGraph-style Effector UI widgets into all primitive .ui files."""

import glob
import os
import re
import sys

UI_DIR = "deploy/share/mandelbulber2/formula/ui"
SHARE_UI_DIR = "share/mandelbulber2/formula/ui"


def generate_effector_ui(start_row: int) -> tuple[str, int]:
    """Generate XML snippet for 4 effectors, return (xml, next_row)."""
    lines = []
    row = start_row

    # Section header
    lines.append(f'     <item row="{row}" column="0" colspan="3">')
    lines.append('      <widget class="Line" name="line_effector">')
    lines.append('       <property name="orientation"><enum>Qt::Horizontal</enum></property>')
    lines.append('      </widget>')
    lines.append('     </item>')
    row += 1

    lines.append(f'     <item row="{row}" column="0" colspan="3">')
    lines.append('      <widget class="QLabel" name="label_effectors">')
    lines.append('       <property name="text"><string>Effectors (MoGraph)</string></property>')
    lines.append('       <property name="styleSheet"><string notr="true">font-weight: bold;</string></property>')
    lines.append('      </widget>')
    lines.append('     </item>')
    row += 1

    for i in range(1, 5):
        eff = f"effector_{i}"

        # Effector label
        lines.append(f'     <item row="{row}" column="0" colspan="3">')
        lines.append(f'      <widget class="QLabel" name="label_{eff}">')
        lines.append(f'       <property name="text"><string>Effector {i}</string></property>')
        lines.append('      </widget>')
        lines.append('     </item>')
        row += 1

        # Type
        lines.append(f'     <item row="{row}" column="0">')
        lines.append(f'      <widget class="QLabel" name="label_{eff}_type"><property name="text"><string>Type:</string></property></widget>')
        lines.append('     </item>')
        lines.append(f'     <item row="{row}" column="1" colspan="2">')
        lines.append(f'      <widget class="QComboBox" name="comboBox_{eff}_type">')
        lines.append('       <item><property name="text"><string>None</string></property></item>')
        lines.append('       <item><property name="text"><string>Random</string></property></item>')
        lines.append('       <item><property name="text"><string>Step</string></property></item>')
        lines.append('       <item><property name="text"><string>Formula</string></property></item>')
        lines.append('       <item><property name="text"><string>Time</string></property></item>')
        lines.append('      </widget>')
        lines.append('     </item>')
        row += 1

        # Enabled
        lines.append(f'     <item row="{row}" column="0">')
        lines.append(f'      <widget class="QLabel" name="label_{eff}_enabled"><property name="text"><string>Enabled:</string></property></widget>')
        lines.append('     </item>')
        lines.append(f'     <item row="{row}" column="1" colspan="2">')
        lines.append(f'      <widget class="MyCheckBox" name="checkBox_{eff}_enabled"><property name="text"><string>Enabled</string></property></widget>')
        lines.append('     </item>')
        row += 1

        # Mode
        lines.append(f'     <item row="{row}" column="0">')
        lines.append(f'      <widget class="QLabel" name="label_{eff}_mode"><property name="text"><string>Mode:</string></property></widget>')
        lines.append('     </item>')
        lines.append(f'     <item row="{row}" column="1" colspan="2">')
        lines.append(f'      <widget class="QComboBox" name="comboBox_{eff}_mode">')
        lines.append('       <item><property name="text"><string>Position</string></property></item>')
        lines.append('       <item><property name="text"><string>Rotation</string></property></item>')
        lines.append('       <item><property name="text"><string>Scale</string></property></item>')
        lines.append('       <item><property name="text"><string>All</string></property></item>')
        lines.append('      </widget>')
        lines.append('     </item>')
        row += 1

        # Strength
        lines.append(f'     <item row="{row}" column="0">')
        lines.append(f'      <widget class="QLabel" name="label_{eff}_strength"><property name="text"><string>Strength:</string></property></widget>')
        lines.append('     </item>')
        lines.append(f'     <item row="{row}" column="1" colspan="2">')
        lines.append(f'      <widget class="MyDoubleSpinBox" name="spinboxd_{eff}_strength"><property name="decimals"><number>2</number></property></widget>')
        lines.append('     </item>')
        row += 1

        # Random Seed
        lines.append(f'     <item row="{row}" column="0">')
        lines.append(f'      <widget class="QLabel" name="label_{eff}_random_seed"><property name="text"><string>Seed:</string></property></widget>')
        lines.append('     </item>')
        lines.append(f'     <item row="{row}" column="1" colspan="2">')
        lines.append(f'      <widget class="MySpinBox" name="spinboxInt_{eff}_random_seed"><property name="maximum"><number>999999</number></property></widget>')
        lines.append('     </item>')
        row += 1

        # Position Amp
        for axis, label in [('x', 'X'), ('y', 'Y'), ('z', 'Z')]:
            lines.append(f'     <item row="{row}" column="0">')
            lines.append(f'      <widget class="QLabel" name="label_{eff}_random_position_amp_{axis}"><property name="text"><string>Pos Amp {label}:</string></property></widget>')
            lines.append('     </item>')
            lines.append(f'     <item row="{row}" column="1" colspan="2">')
            lines.append(f'      <widget class="MyLineEdit" name="vect3_{eff}_random_position_amp_{axis}"/>')
            lines.append('     </item>')
            row += 1

        # Rotation Amp
        for axis, label in [('x', 'X'), ('y', 'Y'), ('z', 'Z')]:
            lines.append(f'     <item row="{row}" column="0">')
            lines.append(f'      <widget class="QLabel" name="label_{eff}_random_rotation_amp_{axis}"><property name="text"><string>Rot Amp {label}:</string></property></widget>')
            lines.append('     </item>')
            lines.append(f'     <item row="{row}" column="1" colspan="2">')
            lines.append(f'      <widget class="MyLineEdit" name="vect3_{eff}_random_rotation_amp_{axis}"/>')
            lines.append('     </item>')
            row += 1

        # Scale Amp
        for axis, label in [('x', 'X'), ('y', 'Y'), ('z', 'Z')]:
            lines.append(f'     <item row="{row}" column="0">')
            lines.append(f'      <widget class="QLabel" name="label_{eff}_random_scale_amp_{axis}"><property name="text"><string>Scale Amp {label}:</string></property></widget>')
            lines.append('     </item>')
            lines.append(f'     <item row="{row}" column="1" colspan="2">')
            lines.append(f'      <widget class="MyLineEdit" name="vect3_{eff}_random_scale_amp_{axis}"/>')
            lines.append('     </item>')
            row += 1

    return '\n'.join(lines), row


def inject_into_file(filepath: str) -> None:
    with open(filepath, 'r') as f:
        content = f.read()

    # Find last row number
    rows = [int(m) for m in re.findall(r'row="(\d+)"', content)]
    if not rows:
        print(f"Skipping {filepath}: no rows found")
        return
    last_row = max(rows)

    # Find the closing </layout> before </widget> for the main form
    # We look for the last </layout> that closes the main grid layout
    # Strategy: find the last major layout closing tag
    # In these files, the structure is: <layout class="QGridLayout" ...> ... </layout>
    # We insert before the closing </layout>

    # Find the spacer item before the closing </layout> of the vertical layout
    # Pattern: </layout>\n   </item>\n   <item>\n    <spacer name="verticalSpacer">
    match = re.search(r'(\s+</layout>\s+</item>\s+)(<item>\s+<spacer\s+name="verticalSpacer")', content, re.DOTALL)
    if not match:
        # Try with nested widget (some files have extra nesting)
        match = re.search(r'(\s+</widget>\s+</item>\s+)(<item>\s+<spacer\s+name="verticalSpacer")', content, re.DOTALL)
    if not match:
        print(f"Skipping {filepath}: could not find injection point")
        return

    snippet, _ = generate_effector_ui(last_row + 1)
    new_content = content[:match.start(2)] + snippet + '\n' + match.group(2) + content[match.end(2):]

    with open(filepath, 'w') as f:
        f.write(new_content)
    print(f"Injected effectors into {filepath}")


def main():
    files = sorted(glob.glob(os.path.join(UI_DIR, "primitive_*.ui")))
    if not files:
        print(f"No primitive UI files found in {UI_DIR}")
        sys.exit(1)

    for filepath in files:
        inject_into_file(filepath)

    # Sync to share dir
    share_files = sorted(glob.glob(os.path.join(SHARE_UI_DIR, "primitive_*.ui")))
    for src in files:
        dst = os.path.join(SHARE_UI_DIR, os.path.basename(src))
        if os.path.exists(dst):
            with open(src, 'r') as f:
                data = f.read()
            with open(dst, 'w') as f:
                f.write(data)
            print(f"Synced {os.path.basename(src)} to share/")

    print("Done!")


if __name__ == "__main__":
    main()
