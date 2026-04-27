#!/usr/bin/env python3
import xml.etree.ElementTree as ET
import os
from collections import defaultdict

UI_DIR = os.path.expanduser("~/mandelbulber2/mandelbulber2/mandelbulber2/formula/ui")

# ═══════════════════════════════════════════════════════════════
# STAP 1: ANALYSEER BOX.UI ALS REFERENTIE
# ═══════════════════════════════════════════════════════════════

def analyze_box():
    """Analyseer box.ui volledig"""
    path = os.path.join(UI_DIR, "primitive_box.ui")
    tree = ET.parse(path)
    root = tree.getroot()

    headers = {}
    sections = defaultdict(list)

    for layout in root.iter("layout"):
        if layout.get("class") == "QGridLayout":
            for item in layout:
                row_str = item.get("row")
                if not row_str:
                    continue

                row = int(row_str)
                widget = item.find("widget")
                if not widget:
                    continue

                name = widget.get("name", "")

                # Check if it's a header
                if name.startswith("label_section_") or name.endswith("_header"):
                    # Get stylesheet if exists
                    stylesheet = ""
                    for prop in widget.findall(".//property[@name='styleSheet']"):
                        string_elem = prop.find("string")
                        if string_elem is not None:
                            stylesheet = string_elem.text or ""

                    header_type = "STYLED" if name.startswith("label_section_") else "SIMPLE"

                    headers[name] = {
                        "row": row,
                        "type": header_type,
                        "stylesheet": stylesheet,
                        "text": widget.find(".//property[@name='text']/string").text if widget.find(".//property[@name='text']/string") is not None else ""
                    }

                # Categorize widgets by section
                if "boolean" in name.lower() and not name.endswith("_header"):
                    sections["boolean"].append(name)
                elif "material" in name.lower() and not name.endswith("_header"):
                    sections["material"].append(name)
                elif "position" in name.lower() or "rotation" in name.lower() or "size" in name.lower():
                    sections["transform"].append(name)
                elif "repeat" in name.lower() and not name.endswith("_header") and not name.startswith("label_section_"):
                    sections["repeat"].append(name)
                elif "cloner" in name.lower() and not name.endswith("_header"):
                    sections["cloner"].append(name)
                elif "group" in name.lower() and not name.endswith("_header"):
                    sections["groups"].append(name)
                elif "deform" in name.lower() and not name.endswith("_header"):
                    sections["deform"].append(name)
                elif "instance" in name.lower() and not name.endswith("_header"):
                    sections["instance"].append(name)
                elif "boolean_edge" in name.lower() or "chamfer" in name.lower():
                    sections["boolean_edge"].append(name)
                elif "emission" in name.lower() or "luminosity" in name.lower():
                    sections["emission"].append(name)

    return headers, sections

def analyze_primitive(filename):
    """Analyseer een primitive UI bestand"""
    path = os.path.join(UI_DIR, filename)
    tree = ET.parse(path)
    root = tree.getroot()

    found_headers = []
    has_repeat_params = False
    repeat_param_count = 0

    for layout in root.iter("layout"):
        if layout.get("class") == "QGridLayout":
            for item in layout:
                widget = item.find("widget")
                if not widget:
                    continue

                name = widget.get("name", "")

                if name.startswith("label_section_") or name.endswith("_header"):
                    found_headers.append(name)

                if "repeat" in name.lower() and not name.startswith("label_section_") and not name.endswith("_header"):
                    has_repeat_params = True
                    repeat_param_count += 1

    return found_headers, has_repeat_params, repeat_param_count

# ═══════════════════════════════════════════════════════════════
# MAIN ANALYSIS
# ═══════════════════════════════════════════════════════════════

print("═" * 80)
print("STAP 1: VOLLEDIGE ANALYSE — BOX ALS REFERENTIE")
print("═" * 80)
print()

# Analyze box
box_headers, box_sections = analyze_box()

print("BOX.UI — REFERENTIE STRUCTUUR")
print("=" * 80)
print()

print("HEADERS IN BOX:")
print("-" * 80)
for header_name in sorted(box_headers.keys()):
    info = box_headers[header_name]
    print(f"  {info['type']:7s}  {header_name:40s}  row {info['row']:3d}  '{info['text']}'")

print()
print(f"Totaal: {len(box_headers)} headers")
print()

print("SECTIES IN BOX:")
print("-" * 80)
for section_name in ["boolean", "transform", "repeat", "material", "groups",
                      "cloner", "deform", "instance", "boolean_edge", "emission"]:
    count = len(box_sections[section_name])
    if count > 0:
        print(f"  {section_name:20s}: {count:3d} widgets")

print()
print("=" * 80)
print()

# Analyze all other primitives
primitives = []
for filename in sorted(os.listdir(UI_DIR)):
    if filename.startswith("primitive_") and filename.endswith(".ui") and filename != "primitive_box.ui":
        primitives.append(filename)

# Determine 2D vs 3D
primitives_2d = ["primitive_plane.ui", "primitive_water.ui", "primitive_lava_plane.ui",
                 "primitive_circle.ui", "primitive_rectangle.ui"]
primitives_3d = [p for p in primitives if p not in primitives_2d]

print("PRIMITIVES VERGELIJKING")
print("=" * 80)
print()

# Create comparison table
all_results = {}
for primitive_file in primitives:
    found_headers, has_repeat_params, repeat_count = analyze_primitive(primitive_file)
    all_results[primitive_file] = {
        "headers": found_headers,
        "has_repeat": has_repeat_params,
        "repeat_count": repeat_count
    }

# Print detailed comparison
print("HEADER AANWEZIGHEID:")
print("-" * 80)

header_list = [
    "label_section_boolean",
    "label_section_transform",
    "label_section_repeat",
    "label_section_material",
    "label_section_groups",
    "label_section_cloner",
    "label_section_emission",
    "label_deform_header",
    "label_instance_header",
    "label_boolean_edge_header"
]

# Header per primitive
print()
for primitive_file in primitives:
    primitive_name = primitive_file.replace("primitive_", "").replace(".ui", "")
    is_2d = primitive_file in primitives_2d
    dimension = "2D" if is_2d else "3D"

    print(f"{primitive_name:20s} [{dimension}]:")

    result = all_results[primitive_file]

    for header in header_list:
        # Skip repeat voor 2D primitives in de check
        if header == "label_section_repeat" and is_2d:
            status = "  (2D - niet nodig)"
        elif header in result["headers"]:
            status = "✓ JA"
        else:
            status = "✗ MIST"

        print(f"  {header:40s} {status}")

    if result["has_repeat"]:
        print(f"  → Repeat parameters: {result['repeat_count']}")

    print()

print("=" * 80)
print()

# Summary table
print("SAMENVATTING — WAT MIST ER?")
print("=" * 80)
print()

for primitive_file in primitives:
    primitive_name = primitive_file.replace("primitive_", "").replace(".ui", "")
    is_2d = primitive_file in primitives_2d
    dimension = "2D" if is_2d else "3D"

    result = all_results[primitive_file]
    missing = []

    for header in header_list:
        # Skip repeat check voor 2D primitives
        if header == "label_section_repeat" and is_2d:
            continue
        if header not in result["headers"]:
            missing.append(header)

    if missing:
        print(f"{primitive_name:20s} [{dimension}] mist {len(missing)} headers:")
        for m in missing:
            print(f"  - {m}")
        print()
    else:
        print(f"{primitive_name:20s} [{dimension}] ✓ COMPLEET")

print()
print("=" * 80)
print("KLAAR MET ANALYSE — WACHT OP GOEDKEURING VOOR STAP 2")
print("=" * 80)
