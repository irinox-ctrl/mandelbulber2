#!/usr/bin/env python3
"""
Add cloner UI widgets to all primitive UI files
"""
import os
import re

# The cloner XML to insert
CLONER_XML = '''     <item row="28" column="0">
      <widget class="QLabel" name="label_cloner">
       <property name="text">
        <string>Cloner:</string>
       </property>
       <property name="alignment">
        <set>Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter</set>
       </property>
      </widget>
     </item>
     <item row="28" column="1" colspan="2">
      <widget class="MyCheckBox" name="checkBox_cloner_enabled">
       <property name="text">
        <string>Enabled</string>
       </property>
      </widget>
     </item>
     <item row="29" column="0">
      <widget class="QLabel" name="label_cloner_count">
       <property name="text">
        <string>Count:</string>
       </property>
       <property name="alignment">
        <set>Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter</set>
       </property>
      </widget>
     </item>
     <item row="29" column="1" colspan="2">
      <widget class="MySpinBox" name="spinboxInt_cloner_count">
       <property name="minimum">
        <number>1</number>
       </property>
       <property name="maximum">
        <number>1000</number>
       </property>
       <property name="value">
        <number>1</number>
       </property>
      </widget>
     </item>
     <item row="30" column="0" rowspan="3">
      <widget class="QLabel" name="label_cloner_offset">
       <property name="text">
        <string>Offset:</string>
       </property>
       <property name="alignment">
        <set>Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter</set>
       </property>
      </widget>
     </item>
     <item row="30" column="1">
      <widget class="QLabel" name="label_cloner_offset_x">
       <property name="text">
        <string>x</string>
       </property>
       <property name="alignment">
        <set>Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter</set>
       </property>
      </widget>
     </item>
     <item row="30" column="2">
      <widget class="MyLineEdit" name="vect3_cloner_offset_x">
       <property name="sizePolicy">
        <sizepolicy hsizetype="Expanding" vsizetype="Maximum">
         <horstretch>0</horstretch>
         <verstretch>0</verstretch>
        </sizepolicy>
       </property>
      </widget>
     </item>
     <item row="31" column="1">
      <widget class="QLabel" name="label_cloner_offset_y">
       <property name="text">
        <string>y</string>
       </property>
       <property name="alignment">
        <set>Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter</set>
       </property>
      </widget>
     </item>
     <item row="31" column="2">
      <widget class="MyLineEdit" name="vect3_cloner_offset_y">
       <property name="sizePolicy">
        <sizepolicy hsizetype="Expanding" vsizetype="Maximum">
         <horstretch>0</horstretch>
         <verstretch>0</verstretch>
        </sizepolicy>
       </property>
      </widget>
     </item>
     <item row="32" column="1">
      <widget class="QLabel" name="label_cloner_offset_z">
       <property name="text">
        <string>z</string>
       </property>
       <property name="alignment">
        <set>Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter</set>
       </property>
      </widget>
     </item>
     <item row="32" column="2">
      <widget class="MyLineEdit" name="vect3_cloner_offset_z">
       <property name="sizePolicy">
        <sizepolicy hsizetype="Expanding" vsizetype="Maximum">
         <horstretch>0</horstretch>
         <verstretch>0</verstretch>
        </sizepolicy>
       </property>
      </widget>
     </item>
'''

def add_cloner_to_ui_file(filepath):
    """Add cloner widgets to a primitive UI file"""
    with open(filepath, 'r') as f:
        content = f.read()

    # Check if already has cloner
    if 'label_cloner' in content:
        print(f"SKIP: {os.path.basename(filepath)} (already has cloner)")
        return False

    # Find the last vect3_pivot_z widget and add cloner after it
    # Pattern: find the closing </widget> after vect3_pivot_z, then find the closing </item>
    pattern = r'(<widget class="MyLineEdit" name="vect3_pivot_z">.*?</widget>\s*</item>)\s*(</layout>)'

    match = re.search(pattern, content, re.DOTALL)
    if not match:
        print(f"FAIL: {os.path.basename(filepath)} (no pivot_z found)")
        return False

    # Insert cloner XML between pivot_z </item> and </layout>
    new_content = content[:match.end(1)] + '\n' + CLONER_XML + match.group(2) + content[match.end():]

    # Write back
    with open(filepath, 'w') as f:
        f.write(new_content)

    print(f"OK:   {os.path.basename(filepath)}")
    return True

def main():
    ui_dir = '/home/joeri/mandelbulber2/mandelbulber2/formula/ui'
    files = [f for f in os.listdir(ui_dir) if f.startswith('primitive_') and f.endswith('.ui')]

    print(f"Found {len(files)} primitive UI files\n")

    success = 0
    for filename in sorted(files):
        filepath = os.path.join(ui_dir, filename)
        if add_cloner_to_ui_file(filepath):
            success += 1

    print(f"\n{success}/{len(files)} files updated successfully")

if __name__ == '__main__':
    main()
