#!/usr/bin/env python3
"""
add_primitive_widgets.py — Mandelbulber Primitive UI Widget Inserter
====================================================================
Veilig widgets toevoegen aan primitive_*.ui bestanden.

PROBLEEM: Claude Code maakt steeds dezelfde fouten:
  1. Rijnummers als "10a" i.p.v. integers
  2. Widgets in geneste layout i.p.v. hoofd-gridLayout
  3. Rijen die al bezet zijn (overlap → widgets onzichtbaar)
  4. Widgets BUITEN de layout plaatsen

DIT SCRIPT: Parsed de XML correct en vindt:
  - De HOOFD-gridLayout (waar position/size/rotation al in zitten)
  - Alle bezette rijnummers
  - De eerstvolgende vrije rij
  - De exacte insert-positie (BINNEN de juiste layout)

GEBRUIK:
  python3 add_primitive_widgets.py --show primitive_box.ui
      → Toont structuur: layouts, bezette rijen, vrije rijen

  python3 add_primitive_widgets.py --add-vec3 prim_scale --label "Scale:" primitive_box.ui
      → Voegt 3 MyLineEdit velden toe (x/y/z) op de eerste vrije rij

  python3 add_primitive_widgets.py --add-combo coordinate_space --label "Coord:" --items "Local,World" primitive_box.ui
      → Voegt een combobox toe op de eerste vrije rij

  python3 add_primitive_widgets.py --add-vec3 pivot --label "Pivot:" --start-row 28 primitive_box.ui
      → Voegt vec3 toe op specifieke startrij

  python3 add_primitive_widgets.py --batch --add-vec3 prim_scale --label "Scale:" formula/ui/primitive_*.ui
      → Doet ALLE bestanden in één keer

VERIFICATIE: Na elke wijziging toont het script:
  - Welke rijen zijn gebruikt
  - Of de widgets in de hoofd-layout zitten (JA/NEE)
  - Diff van de wijziging
"""

import xml.etree.ElementTree as ET
import sys
import os
import argparse
import glob
import copy
import re
from pathlib import Path


# ============================================================================
# ANALYSE: Vind de hoofd-gridLayout en bezette rijen
# ============================================================================

def find_main_grid_layout(root):
    """
    Vindt de HOOFD-gridLayout in een Mandelbulber primitive .ui bestand.
    
    De hoofd-layout is de gridLayout die de bekende primitive widgets bevat:
    vect3_position_x, vect3_size_x, spinboxd3_rotation_x, etc.
    
    Returns: (layout_element, depth) of (None, -1)
    """
    known_widgets = [
        'vect3_position_x', 'vect3_position_y', 'vect3_position_z',
        'spinboxd3_rotation_x', 'spinboxd3_rotation_y', 'spinboxd3_rotation_z',
    ]
    
    def search_layout(element, depth=0):
        """Recursief zoeken naar de layout die bekende widgets bevat."""
        if element.tag == 'layout' and element.get('class') == 'QGridLayout':
            # Zoek of deze layout bekende widgets bevat (direct of in items)
            widget_names = set()
            for item in element.findall('item'):
                for widget in item.findall('widget'):
                    name = widget.get('name', '')
                    widget_names.add(name)
            
            # Als deze layout bekende primitive widgets bevat, is het de hoofd-layout
            matches = widget_names.intersection(known_widgets)
            if len(matches) >= 2:
                return (element, depth)
        
        # Recursief zoeken in kinderen
        for child in element:
            result = search_layout(child, depth + 1)
            if result[0] is not None:
                return result
        
        return (None, -1)
    
    return search_layout(root)


def get_used_rows(layout):
    """
    Geeft een dict van alle gebruikte rijnummers → widget namen.
    """
    rows = {}
    for item in layout.findall('item'):
        row_str = item.get('row', '')
        if row_str.isdigit():
            row = int(row_str)
            # Verzamel widget namen op deze rij
            widgets = []
            for widget in item.findall('widget'):
                widgets.append(widget.get('name', '?'))
            if row not in rows:
                rows[row] = []
            rows[row].extend(widgets)
    return rows


def get_next_free_row(used_rows, start_from=None):
    """
    Vindt de eerste vrije rij na de hoogste bezette rij.
    """
    if not used_rows:
        return 0
    max_row = max(used_rows.keys())
    if start_from is not None:
        return max(start_from, max_row + 1)
    return max_row + 1


def find_insert_position_in_source(source_lines, layout, root):
    """
    Vindt het regelnummer waar nieuwe items ingevoegd moeten worden
    BINNEN de hoofd-gridLayout (voor de sluitende </layout> tag).
    
    Dit werkt op de brontekst, niet op de ET-boom, omdat ET
    regelnummers niet bijhoudt.
    """
    # Strategie: vind het LAATSTE </item> dat bij de hoofd-layout hoort,
    # of de </layout> die de hoofd-layout sluit.
    
    # Stap 1: Verzamel alle widget namen in de hoofd-layout
    layout_widgets = set()
    for item in layout.findall('item'):
        for widget in item.findall('widget'):
            layout_widgets.add(widget.get('name', ''))
    
    if not layout_widgets:
        return None
    
    # Stap 2: Zoek in de brontekst het laatste voorkomen van een bekend widget
    last_widget_line = -1
    last_widget_name = ''
    for i, line in enumerate(source_lines):
        for wname in layout_widgets:
            if f'name="{wname}"' in line:
                last_widget_line = i
                last_widget_name = wname
    
    if last_widget_line < 0:
        return None
    
    # Stap 3: Zoek de </item> die dit widget afsluit
    depth = 0
    for i in range(last_widget_line, len(source_lines)):
        line = source_lines[i]
        # Tel <item> en </item> tags
        depth += line.count('<item')
        depth -= line.count('</item>')
        if '</item>' in line and depth <= 0:
            # Dit is de afsluitende </item> tag
            # Insert positie is de regel ERNA
            return i + 1
    
    # Fallback: zoek de </layout> na het laatste widget
    for i in range(last_widget_line, len(source_lines)):
        if '</layout>' in source_lines[i]:
            return i
    
    return None


def find_insert_position_robust(source_lines):
    """
    Alternatieve methode: zoek de hoofd-gridLayout door patronen in de brontekst.
    
    De hoofd-layout bevat items met 'vect3_position_x'. We zoeken de </layout>
    die bij DEZELFDE nesting-diepte hoort.
    """
    # Vind de gridLayout die vect3_position_x bevat
    in_main_layout = False
    layout_start_line = -1
    layout_depth = 0
    
    for i, line in enumerate(source_lines):
        if 'vect3_position_x' in line:
            # Zoek TERUG naar de <layout> die deze widget bevat
            depth = 0
            for j in range(i, -1, -1):
                if '</layout>' in source_lines[j]:
                    depth += 1
                if '<layout' in source_lines[j] and 'QGridLayout' in source_lines[j]:
                    if depth == 0:
                        layout_start_line = j
                        break
                    depth -= 1
            break
    
    if layout_start_line < 0:
        return None
    
    # Nu zoeken we de bijbehorende </layout>
    depth = 0
    last_item_end = layout_start_line
    for i in range(layout_start_line, len(source_lines)):
        line = source_lines[i]
        
        # Track het laatste </item> op diepte 1 (direct in de hoofd-layout)
        if '</item>' in line:
            last_item_end = i
        
        # Tel layout nesting
        if '<layout' in line:
            depth += 1
        if '</layout>' in line:
            depth -= 1
            if depth == 0:
                # Dit is de sluitende </layout> van de hoofd-layout
                # Insert positie is VOOR deze </layout>, na het laatste </item>
                return i
    
    return None


# ============================================================================
# WIDGET GENERATIE: XML blokken voor verschillende widget types
# ============================================================================

def make_vec3_xml(param_name, label, start_row, indent="     "):
    """
    Genereert XML voor een CVector3 widget (3 rijen: x, y, z).
    Exact hetzelfde patroon als vect3_size_x/y/z in Mandelbulber.
    
    Returns: (xml_string, num_rows_used)
    """
    axes = ['x', 'y', 'z']
    lines = []
    
    # Label spanning 3 rijen
    lines.append(f'{indent}<item row="{start_row}" column="0" rowspan="3">')
    lines.append(f'{indent} <widget class="QLabel" name="label_{param_name}">')
    lines.append(f'{indent}  <property name="text">')
    lines.append(f'{indent}   <string>{label}</string>')
    lines.append(f'{indent}  </property>')
    lines.append(f'{indent}  <property name="alignment">')
    lines.append(f'{indent}   <set>Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter</set>')
    lines.append(f'{indent}  </property>')
    lines.append(f'{indent} </widget>')
    lines.append(f'{indent}</item>')
    
    # Per as: label + MyLineEdit
    for idx, axis in enumerate(axes):
        row = start_row + idx
        
        # As-label (x/y/z)
        lines.append(f'{indent}<item row="{row}" column="1">')
        lines.append(f'{indent} <widget class="QLabel" name="label_{param_name}_{axis}">')
        lines.append(f'{indent}  <property name="text">')
        lines.append(f'{indent}   <string>{axis}</string>')
        lines.append(f'{indent}  </property>')
        lines.append(f'{indent}  <property name="alignment">')
        lines.append(f'{indent}   <set>Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter</set>')
        lines.append(f'{indent}  </property>')
        lines.append(f'{indent} </widget>')
        lines.append(f'{indent}</item>')
        
        # Invoerveld
        lines.append(f'{indent}<item row="{row}" column="2">')
        lines.append(f'{indent} <widget class="MyLineEdit" name="vect3_{param_name}_{axis}">')
        lines.append(f'{indent}  <property name="sizePolicy">')
        lines.append(f'{indent}   <sizepolicy hsizetype="Expanding" vsizetype="Maximum">')
        lines.append(f'{indent}    <horstretch>0</horstretch>')
        lines.append(f'{indent}    <verstretch>0</verstretch>')
        lines.append(f'{indent}   </sizepolicy>')
        lines.append(f'{indent}  </property>')
        lines.append(f'{indent} </widget>')
        lines.append(f'{indent}</item>')
    
    return ('\n'.join(lines), 3)


def make_combo_xml(param_name, label, items, start_row, indent="     "):
    """
    Genereert XML voor een combobox widget (1 rij).
    
    Returns: (xml_string, num_rows_used)
    """
    lines = []
    
    # Label
    lines.append(f'{indent}<item row="{start_row}" column="0">')
    lines.append(f'{indent} <widget class="QLabel" name="label_{param_name}">')
    lines.append(f'{indent}  <property name="text">')
    lines.append(f'{indent}   <string>{label}</string>')
    lines.append(f'{indent}  </property>')
    lines.append(f'{indent}  <property name="alignment">')
    lines.append(f'{indent}   <set>Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter</set>')
    lines.append(f'{indent}  </property>')
    lines.append(f'{indent} </widget>')
    lines.append(f'{indent}</item>')
    
    # ComboBox
    lines.append(f'{indent}<item row="{start_row}" column="1" colspan="2">')
    lines.append(f'{indent} <widget class="QComboBox" name="comboBox_{param_name}">')
    for item_text in items:
        lines.append(f'{indent}  <item>')
        lines.append(f'{indent}   <property name="text">')
        lines.append(f'{indent}    <string>{item_text}</string>')
        lines.append(f'{indent}   </property>')
        lines.append(f'{indent}  </item>')
    lines.append(f'{indent} </widget>')
    lines.append(f'{indent}</item>')
    
    return ('\n'.join(lines), 1)


def make_checkbox_xml(param_name, label, start_row, indent="     "):
    """
    Genereert XML voor een checkbox widget (1 rij, spanning kolom 0-2).
    
    Returns: (xml_string, num_rows_used)
    """
    lines = []
    lines.append(f'{indent}<item row="{start_row}" column="0" colspan="3">')
    lines.append(f'{indent} <widget class="MyCheckBox" name="checkBox_{param_name}">')
    lines.append(f'{indent}  <property name="text">')
    lines.append(f'{indent}   <string>{label}</string>')
    lines.append(f'{indent}  </property>')
    lines.append(f'{indent} </widget>')
    lines.append(f'{indent}</item>')
    
    return ('\n'.join(lines), 1)


def make_spinbox_xml(param_name, label, start_row, indent="     "):
    """
    Genereert XML voor een enkele MyLineEdit (double spinbox, 1 rij).
    
    Returns: (xml_string, num_rows_used)
    """
    lines = []
    
    # Label
    lines.append(f'{indent}<item row="{start_row}" column="0">')
    lines.append(f'{indent} <widget class="QLabel" name="label_{param_name}">')
    lines.append(f'{indent}  <property name="text">')
    lines.append(f'{indent}   <string>{label}</string>')
    lines.append(f'{indent}  </property>')
    lines.append(f'{indent}  <property name="alignment">')
    lines.append(f'{indent}   <set>Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter</set>')
    lines.append(f'{indent}  </property>')
    lines.append(f'{indent} </widget>')
    lines.append(f'{indent}</item>')
    
    # Spinbox
    lines.append(f'{indent}<item row="{start_row}" column="1" colspan="2">')
    lines.append(f'{indent} <widget class="MyLineEdit" name="logedit_{param_name}">')
    lines.append(f'{indent}  <property name="sizePolicy">')
    lines.append(f'{indent}   <sizepolicy hsizetype="Expanding" vsizetype="Maximum">')
    lines.append(f'{indent}    <horstretch>0</horstretch>')
    lines.append(f'{indent}    <verstretch>0</verstretch>')
    lines.append(f'{indent}   </sizepolicy>')
    lines.append(f'{indent}  </property>')
    lines.append(f'{indent} </widget>')
    lines.append(f'{indent}</item>')
    
    return ('\n'.join(lines), 1)


# ============================================================================
# SHOW: Toon structuur van een UI bestand
# ============================================================================

def show_structure(filepath):
    """Toont de layout structuur, bezette rijen en vrije rijen."""
    print(f"\n{'='*60}")
    print(f"  ANALYSE: {os.path.basename(filepath)}")
    print(f"{'='*60}")
    
    with open(filepath, 'r') as f:
        source = f.read()
    source_lines = source.split('\n')
    
    # Parse XML
    try:
        root = ET.fromstring(source)
    except ET.ParseError as e:
        print(f"  ❌ XML PARSE ERROR: {e}")
        return False
    
    # Vind hoofd-layout
    layout, depth = find_main_grid_layout(root)
    if layout is None:
        print(f"  ❌ Geen hoofd-gridLayout gevonden!")
        print(f"     (Geen layout met vect3_position_x/y/z)")
        return False
    
    layout_name = layout.get('name', '(naamloos)')
    print(f"\n  ✓ Hoofd-gridLayout: {layout_name} (diepte {depth})")
    
    # Bezette rijen
    used = get_used_rows(layout)
    print(f"\n  Bezette rijen ({len(used)}):")
    for row in sorted(used.keys()):
        widgets = ', '.join(used[row])
        print(f"    rij {row:3d}: {widgets}")
    
    # Vrije rijen
    next_free = get_next_free_row(used)
    print(f"\n  ✓ Volgende vrije rij: {next_free}")
    
    # Insert positie
    insert_line = find_insert_position_robust(source_lines)
    if insert_line:
        print(f"  ✓ Insert positie: regel {insert_line + 1} (voor </layout>)")
        # Toon context
        start = max(0, insert_line - 2)
        end = min(len(source_lines), insert_line + 2)
        print(f"\n  Context rond insert-punt:")
        for i in range(start, end):
            marker = " >>>" if i == insert_line else "    "
            print(f"  {marker} {i+1:4d}: {source_lines[i]}")
    else:
        print(f"  ❌ Kan insert positie niet bepalen!")
    
    # Zoek bestaande custom widgets
    print(f"\n  Bestaande custom widgets:")
    for name in ['prim_scale', 'pivot', 'coordinate_space']:
        count = source.count(name)
        if count > 0:
            print(f"    ✓ {name}: {count} voorkomens")
    
    print()
    return True


# ============================================================================
# ADD: Voeg widgets toe aan een UI bestand
# ============================================================================

def add_widgets(filepath, widget_type, param_name, label, items=None, 
                start_row=None, dry_run=False, force=False):
    """
    Voegt widgets toe aan een primitive .ui bestand.
    
    Args:
        filepath: Pad naar .ui bestand
        widget_type: 'vec3', 'combo', 'checkbox', 'spinbox'
        param_name: Parameter naam (bijv. 'prim_scale', 'coordinate_space')
        label: Label tekst (bijv. 'Scale:', 'Coord:')
        items: Combobox items (alleen voor type 'combo')
        start_row: Optionele startrij (anders automatisch)
        dry_run: Alleen tonen, niet schrijven
        force: Overschrijf bestaande widgets met dezelfde naam
    
    Returns: True als succesvol
    """
    basename = os.path.basename(filepath)
    
    with open(filepath, 'r') as f:
        source = f.read()
    source_lines = source.split('\n')
    
    # Check of widget al bestaat
    if param_name in source and not force:
        print(f"  ⏭  {basename}: '{param_name}' bestaat al (gebruik --force om te overschrijven)")
        return True
    
    # Verwijder bestaande widgets als force
    if param_name in source and force:
        source_lines = remove_widget_block(source_lines, param_name)
        source = '\n'.join(source_lines)
    
    # Parse XML
    try:
        root = ET.fromstring(source)
    except ET.ParseError as e:
        print(f"  ❌ {basename}: XML parse error: {e}")
        return False
    
    # Vind hoofd-layout
    layout, depth = find_main_grid_layout(root)
    if layout is None:
        print(f"  ❌ {basename}: Geen hoofd-gridLayout gevonden!")
        return False
    
    # Bezette rijen
    used = get_used_rows(layout)
    
    # Bepaal startrij
    if start_row is None:
        start_row = get_next_free_row(used)
    
    # Check of gevraagde rijen vrij zijn
    generators = {
        'vec3': (make_vec3_xml, 3),
        'combo': (make_combo_xml, 1),
        'checkbox': (make_checkbox_xml, 1),
        'spinbox': (make_spinbox_xml, 1),
    }
    
    gen_func, num_rows = generators[widget_type]
    needed_rows = range(start_row, start_row + num_rows)
    conflicts = [r for r in needed_rows if r in used]
    if conflicts:
        print(f"  ⚠  {basename}: Rijen {conflicts} zijn al bezet!")
        start_row = get_next_free_row(used)
        print(f"     → Verschoven naar rij {start_row}")
    
    # Genereer XML
    if widget_type == 'combo':
        xml_block, _ = gen_func(param_name, label, items or [], start_row)
    elif widget_type in ('checkbox', 'spinbox'):
        xml_block, _ = gen_func(param_name, label, start_row)
    else:
        xml_block, _ = gen_func(param_name, label, start_row)
    
    # Vind insert positie
    insert_line = find_insert_position_robust(source_lines)
    if insert_line is None:
        print(f"  ❌ {basename}: Kan insert positie niet bepalen!")
        return False
    
    # Insert
    new_lines = source_lines[:insert_line] + [xml_block] + source_lines[insert_line:]
    new_source = '\n'.join(new_lines)
    
    if dry_run:
        print(f"  🔍 {basename}: DRY RUN — zou {widget_type} '{param_name}' toevoegen op rij {start_row}")
        print(f"     Insert op regel {insert_line + 1}")
        return True
    
    # Schrijf
    with open(filepath, 'w') as f:
        f.write(new_source)
    
    # Verificatie
    verify_ok = verify_widget_placement(filepath, param_name)
    status = "✓" if verify_ok else "⚠"
    print(f"  {status} {basename}: {widget_type} '{param_name}' toegevoegd op rij {start_row}-{start_row + num_rows - 1}")
    
    return True


def remove_widget_block(source_lines, param_name):
    """
    Verwijdert alle <item>...</item> blokken die param_name bevatten.
    """
    result = []
    skip_until_close = False
    item_depth = 0
    
    i = 0
    while i < len(source_lines):
        line = source_lines[i]
        
        if skip_until_close:
            if '<item' in line:
                item_depth += 1
            if '</item>' in line:
                if item_depth == 0:
                    skip_until_close = False
                    i += 1
                    continue
                item_depth -= 1
            i += 1
            continue
        
        # Check of deze regel een <item> start die param_name bevat
        if '<item' in line:
            # Kijk vooruit of param_name in dit blok zit
            block_end = i
            depth = 0
            found = False
            for j in range(i, min(i + 30, len(source_lines))):
                if param_name in source_lines[j]:
                    found = True
                if '<item' in source_lines[j]:
                    depth += 1
                if '</item>' in source_lines[j]:
                    depth -= 1
                    if depth == 0:
                        block_end = j
                        break
            
            if found:
                # Skip dit hele blok
                i = block_end + 1
                continue
        
        result.append(line)
        i += 1
    
    return result


def verify_widget_placement(filepath, param_name):
    """
    Verifieert dat de widget in de hoofd-gridLayout staat.
    Returns True als correct geplaatst.
    """
    with open(filepath, 'r') as f:
        source = f.read()
    
    try:
        root = ET.fromstring(source)
    except ET.ParseError:
        return False
    
    layout, _ = find_main_grid_layout(root)
    if layout is None:
        return False
    
    # Check of param_name in een widget in deze layout zit
    for item in layout.findall('item'):
        for widget in item.findall('widget'):
            if param_name in widget.get('name', ''):
                return True
    
    return False


# ============================================================================
# BATCH: Verwerk alle primitive UI bestanden
# ============================================================================

def get_all_primitive_ui_files(base_dir):
    """Vindt alle primitive_*.ui bestanden."""
    pattern = os.path.join(base_dir, 'formula', 'ui', 'primitive_*.ui')
    files = sorted(glob.glob(pattern))
    if not files:
        # Probeer alternatieve locaties
        for alt in ['~/mandelbulber2/mandelbulber2', '/usr/share/mandelbulber2']:
            alt = os.path.expanduser(alt)
            pattern = os.path.join(alt, 'formula', 'ui', 'primitive_*.ui')
            files = sorted(glob.glob(pattern))
            if files:
                break
    return files


# ============================================================================
# MAIN
# ============================================================================

def main():
    parser = argparse.ArgumentParser(
        description='Mandelbulber Primitive UI Widget Manager',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Voorbeelden:
  %(prog)s --show primitive_box.ui
  %(prog)s --add-vec3 prim_scale --label "Scale:" primitive_box.ui
  %(prog)s --add-combo coordinate_space --label "Coord:" --items "Local,World" *.ui
  %(prog)s --add-checkbox prim_enabled --label "Enabled" --batch
  %(prog)s --remove prim_scale primitive_box.ui
        """
    )
    
    # Acties
    action = parser.add_mutually_exclusive_group(required=True)
    action.add_argument('--show', action='store_true',
                       help='Toon structuur van UI bestand(en)')
    action.add_argument('--add-vec3', metavar='NAME',
                       help='Voeg CVector3 widget toe (3 rijen x/y/z)')
    action.add_argument('--add-combo', metavar='NAME',
                       help='Voeg combobox widget toe (1 rij)')
    action.add_argument('--add-checkbox', metavar='NAME',
                       help='Voeg checkbox widget toe (1 rij)')
    action.add_argument('--add-spinbox', metavar='NAME',
                       help='Voeg enkele spinbox widget toe (1 rij)')
    action.add_argument('--remove', metavar='NAME',
                       help='Verwijder widget blokken met deze naam')
    
    # Opties
    parser.add_argument('--label', default='',
                       help='Label tekst voor de widget')
    parser.add_argument('--items', default='',
                       help='Combobox items, komma-gescheiden (bijv. "Local,World")')
    parser.add_argument('--start-row', type=int, default=None,
                       help='Startrij (anders automatisch na hoogste bezette rij)')
    parser.add_argument('--force', action='store_true',
                       help='Overschrijf bestaande widgets met dezelfde naam')
    parser.add_argument('--dry-run', action='store_true',
                       help='Alleen tonen, niet wijzigen')
    parser.add_argument('--batch', action='store_true',
                       help='Verwerk ALLE primitive_*.ui bestanden')
    parser.add_argument('--copy-to-system', action='store_true',
                       help='Kopieer resultaat naar /usr/share/mandelbulber2/')
    
    # Bestanden
    parser.add_argument('files', nargs='*',
                       help='UI bestand(en) om te verwerken')
    
    args = parser.parse_args()
    
    # Verzamel bestanden
    files = []
    if args.batch:
        files = get_all_primitive_ui_files('.')
        if not files:
            files = get_all_primitive_ui_files(os.path.expanduser('~/mandelbulber2/mandelbulber2'))
        if not files:
            print("❌ Geen primitive_*.ui bestanden gevonden!")
            print("   Gebruik --batch vanuit de mandelbulber2 directory,")
            print("   of geef bestanden op als argumenten.")
            sys.exit(1)
    elif args.files:
        for pattern in args.files:
            files.extend(glob.glob(pattern))
    
    if not files:
        print("❌ Geen bestanden opgegeven! Gebruik --batch of geef bestanden op.")
        sys.exit(1)
    
    files = sorted(set(files))  # Dedup
    print(f"\n📁 {len(files)} bestand(en) te verwerken\n")
    
    # Uitvoeren
    success = 0
    failed = 0
    
    if args.show:
        for f in files:
            if show_structure(f):
                success += 1
            else:
                failed += 1
    
    elif args.remove:
        for f in files:
            basename = os.path.basename(f)
            with open(f, 'r') as fh:
                lines = fh.read().split('\n')
            
            if args.remove not in '\n'.join(lines):
                print(f"  ⏭  {basename}: '{args.remove}' niet gevonden")
                success += 1
                continue
            
            new_lines = remove_widget_block(lines, args.remove)
            
            if args.dry_run:
                removed = len(lines) - len(new_lines)
                print(f"  🔍 {basename}: DRY RUN — zou {removed} regels verwijderen")
            else:
                with open(f, 'w') as fh:
                    fh.write('\n'.join(new_lines))
                removed = len(lines) - len(new_lines)
                print(f"  ✓ {basename}: {removed} regels verwijderd")
            success += 1
    
    else:
        # Add widget
        if args.add_vec3:
            wtype, name = 'vec3', args.add_vec3
        elif args.add_combo:
            wtype, name = 'combo', args.add_combo
        elif args.add_checkbox:
            wtype, name = 'checkbox', args.add_checkbox
        elif args.add_spinbox:
            wtype, name = 'spinbox', args.add_spinbox
        
        items = [i.strip() for i in args.items.split(',') if i.strip()] if args.items else None
        
        for f in files:
            if add_widgets(f, wtype, name, args.label, items=items,
                          start_row=args.start_row, dry_run=args.dry_run,
                          force=args.force):
                success += 1
            else:
                failed += 1
    
    # Kopieer naar systeem
    if args.copy_to_system and not args.dry_run and not args.show:
        print(f"\n📋 Kopiëren naar /usr/share/mandelbulber2/formula/ui/...")
        for f in files:
            dest = os.path.join('/usr/share/mandelbulber2/formula/ui/', os.path.basename(f))
            try:
                import shutil
                shutil.copy2(f, dest)
                print(f"  ✓ {os.path.basename(f)}")
            except Exception as e:
                print(f"  ❌ {os.path.basename(f)}: {e}")
    
    # Samenvatting
    print(f"\n{'='*60}")
    print(f"  Klaar: {success} ✓  {failed} ❌")
    print(f"{'='*60}\n")
    
    return 0 if failed == 0 else 1


if __name__ == '__main__':
    sys.exit(main())
