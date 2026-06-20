#!/usr/bin/env python3
"""
Inject pivot preset dropdown + pivot vector widgets into primitive .ui files.
"""

import os
import shutil

DEPLOY_UI_DIR = os.path.join(
    os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
    "deploy", "share", "mandelbulber2", "formula", "ui"
)

# Files that need BOTH preset dropdown + vect3_pivot (older primitives)
OLD_PRIMITIVES = [
    "box", "sphere", "plane", "cylinder", "cone",
    "torus", "circle", "rectangle", "prism", "ellipsoid", "water"
]

# Pivot preset XML (to be placed before the cloner / at end of grid layout)
PIVOT_PRESET_XML = """     <item row="200" column="0">
      <widget class="QLabel" name="label_pivot_preset">
       <property name="text">
        <string>Pivot preset:</string>
       </property>
       <property name="alignment">
        <set>Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter</set>
       </property>
      </widget>
     </item>
     <item row="200" column="2">
      <widget class="QComboBox" name="comboBox_pivot_preset">
       <item>
        <property name="text">
         <string>Custom</string>
        </property>
       </item>
       <item>
        <property name="text">
         <string>Center</string>
        </property>
       </item>
       <item>
        <property name="text">
         <string>Bottom</string>
        </property>
       </item>
       <item>
        <property name="text">
         <string>Top</string>
        </property>
       </item>
       <item>
        <property name="text">
         <string>Front</string>
        </property>
       </item>
       <item>
        <property name="text">
         <string>Back</string>
        </property>
       </item>
       <item>
        <property name="text">
         <string>Left</string>
        </property>
       </item>
       <item>
        <property name="text">
         <string>Right</string>
        </property>
       </item>
      </widget>
     </item>
"""

# Pivot vector XML
PIVOT_VECTOR_XML = """     <item row="201" column="0" rowspan="3">
      <widget class="QLabel" name="label_pivot">
       <property name="text">
        <string>Pivot:</string>
       </property>
       <property name="alignment">
        <set>Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter</set>
       </property>
      </widget>
     </item>
     <item row="201" column="1">
      <widget class="QLabel" name="label_pivot_x">
       <property name="text">
        <string>x</string>
       </property>
       <property name="alignment">
        <set>Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter</set>
       </property>
      </widget>
     </item>
     <item row="201" column="2">
      <widget class="MyLineEdit" name="vect3_pivot_x">
       <property name="sizePolicy">
        <sizepolicy hsizetype="Expanding" vsizetype="Maximum">
         <horstretch>0</horstretch>
         <verstretch>0</verstretch>
        </sizepolicy>
       </property>
      </widget>
     </item>
     <item row="202" column="1">
      <widget class="QLabel" name="label_pivot_y">
       <property name="text">
        <string>y</string>
       </property>
       <property name="alignment">
        <set>Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter</set>
       </property>
      </widget>
     </item>
     <item row="202" column="2">
      <widget class="MyLineEdit" name="vect3_pivot_y">
       <property name="sizePolicy">
        <sizepolicy hsizetype="Expanding" vsizetype="Maximum">
         <horstretch>0</horstretch>
         <verstretch>0</verstretch>
        </sizepolicy>
       </property>
      </widget>
     </item>
     <item row="203" column="1">
      <widget class="QLabel" name="label_pivot_z">
       <property name="text">
        <string>z</string>
       </property>
       <property name="alignment">
        <set>Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter</set>
       </property>
      </widget>
     </item>
     <item row="203" column="2">
      <widget class="MyLineEdit" name="vect3_pivot_z">
       <property name="sizePolicy">
        <sizepolicy hsizetype="Expanding" vsizetype="Maximum">
         <horstretch>0</horstretch>
         <verstretch>0</verstretch>
        </sizepolicy>
       </property>
      </widget>
     </item>
"""


def inject_pivot(target_path, add_preset=True):
    with open(target_path, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    # Check if already has pivot preset
    content = ''.join(lines)
    if 'comboBox_pivot_preset' in content:
        if add_preset:
            print(f"SKIP: {os.path.basename(target_path)} already has pivot preset")
            return
        # For newer files: only add vect3_pivot if missing
        if 'vect3_pivot_x' in content:
            print(f"SKIP: {os.path.basename(target_path)} already has pivot vector")
            return

    # Find injection point: the </layout> that closes gridLayout before verticalSpacer
    inject_idx = None
    for i in range(len(lines) - 4):
        if lines[i].strip() == '</layout>':
            next_lines = ''.join(lines[i:i+8])
            if 'verticalSpacer' in next_lines and '<spacer' in next_lines:
                inject_idx = i
                break

    if inject_idx is None:
        raise RuntimeError(f"Could not find injection point in {target_path}")

    xml_to_inject = ""
    if add_preset:
        xml_to_inject += PIVOT_PRESET_XML
    xml_to_inject += PIVOT_VECTOR_XML

    output = lines[:inject_idx] + [xml_to_inject] + lines[inject_idx:]

    with open(target_path, 'w', encoding='utf-8') as f:
        f.writelines(output)


def main():
    for name in OLD_PRIMITIVES:
        target_path = os.path.join(DEPLOY_UI_DIR, f"primitive_{name}.ui")
        if not os.path.exists(target_path):
            print(f"SKIP: {target_path} not found")
            continue

        backup_path = target_path + '.backup'
        shutil.copy2(target_path, backup_path)

        try:
            inject_pivot(target_path, add_preset=True)
            print(f"OK:    Injected pivot into primitive_{name}.ui")
        except RuntimeError as e:
            print(f"ERROR: {e}")
            shutil.copy2(backup_path, target_path)

    # Newer primitives: only add vect3_pivot if missing
    NEWER_PRIMITIVES = ["capsule", "hexprism", "lava_plane", "octahedron", "pyramid"]
    for name in NEWER_PRIMITIVES:
        target_path = os.path.join(DEPLOY_UI_DIR, f"primitive_{name}.ui")
        if not os.path.exists(target_path):
            continue
        if 'vect3_pivot_x' in open(target_path).read():
            continue  # lava_plane already has it

        backup_path = target_path + '.backup'
        shutil.copy2(target_path, backup_path)
        try:
            inject_pivot(target_path, add_preset=False)
            print(f"OK:    Injected pivot vector into primitive_{name}.ui")
        except RuntimeError as e:
            print(f"ERROR: {e}")
            shutil.copy2(backup_path, target_path)


if __name__ == '__main__':
    main()
