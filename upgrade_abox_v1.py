#!/usr/bin/env python3
"""
Upgrade script: Add 15 Amazing Box-specific parameters to all 21 ABox formula variants.
"""
import glob
import os
import xml.etree.ElementTree as ET

BASE = "/home/ubuntu/repos/mandelbulber2-private/mandelbulber2"
CPP_DIR = os.path.join(BASE, "formula", "definition")
CL_DIR = os.path.join(BASE, "formula", "opencl")
UI_DIR = os.path.join(BASE, "formula", "ui")

MARKER = "// GPU bypass: skip if all multipliers disabled"


def find_abox_files(directory, ext):
    """Find all ABox files in directory."""
    if ext == "cpp":
        pattern = os.path.join(directory, "fractal_abox*.cpp")
    elif ext == "cl":
        pattern = os.path.join(directory, "abox*.cl")
    elif ext == "ui":
        pattern = os.path.join(directory, "abox*.ui")
    return sorted(glob.glob(pattern))


def make_ab_block_cpp():
    """Generate the C++ Amazing Box extensions block."""
    lines = []
    lines.append("\t// --- Amazing Box Extensions (15 parameters) ---")
    lines.append("\t{")
    lines.append("\t\tdouble abBFOsc = fractal->transformCommon.abBoxFoldOsc;")
    lines.append("\t\tdouble abBFFreq = fractal->transformCommon.abBoxFoldOscFreq;")
    lines.append("\t\tdouble abScOsc = fractal->transformCommon.abScaleOsc;")
    lines.append("\t\tdouble abScFreq = fractal->transformCommon.abScaleOscFreq;")
    lines.append("\t\tdouble abMROsc = fractal->transformCommon.abMinROsc;")
    lines.append("\t\tdouble abMRFreq = fractal->transformCommon.abMinROscFreq;")
    lines.append("\t\tdouble abPreRot = fractal->transformCommon.abPreRotAngle;")
    lines.append("\t\tdouble abPostRot = fractal->transformCommon.abPostRotAngle;")
    lines.append("\t\tdouble abTwZ = fractal->transformCommon.abTwistZ;")
    lines.append("\t\tdouble abRadDist = fractal->transformCommon.abRadialDistort;")
    lines.append("\t\tdouble abTurb = fractal->transformCommon.abTurbulence;")
    lines.append("\t\tdouble abGradCol = fractal->transformCommon.abGradientColor;")
    lines.append("\t\tdouble abDETw = fractal->transformCommon.abDETweak;")
    lines.append("\t\tdouble abCpix = fractal->transformCommon.abCpixelScale;")
    lines.append("\t\tdouble abSphSoft = fractal->transformCommon.abSphereSoftness;")
    lines.append("")
    lines.append("\t\t// 1-2. Box fold oscillation")
    lines.append("\t\tif (abBFOsc != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble foldMod = abBFOsc * sin(aux.i * abBFFreq * 0.5);")
    lines.append("\t\t\tz.x += foldMod * sign(z.x);")
    lines.append("\t\t\tz.y += foldMod * sign(z.y);")
    lines.append("\t\t\tz.z += foldMod * sign(z.z);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 3-4. Scale oscillation")
    lines.append("\t\tif (abScOsc != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble sOsc = 1.0 + abScOsc * sin(aux.i * abScFreq * 0.5);")
    lines.append("\t\t\tz *= sOsc;")
    lines.append("\t\t\taux.DE *= fabs(sOsc);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 5-6. MinR oscillation")
    lines.append("\t\tif (abMROsc != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble r2 = z.Dot(z);")
    lines.append("\t\t\tdouble mrOsc = abMROsc * sin(aux.i * abMRFreq * 0.5);")
    lines.append("\t\t\tdouble minR2 = fmax(0.01, 0.25 + mrOsc);")
    lines.append("\t\t\tif (r2 < minR2)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tdouble t = 1.0 / minR2;")
    lines.append("\t\t\t\tz *= t;")
    lines.append("\t\t\t\taux.DE *= t;")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 7. Pre-rotation")
    lines.append("\t\tif (abPreRot != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble a = abPreRot * M_PI / 180.0 * aux.i;")
    lines.append("\t\t\tdouble ca = cos(a); double sa = sin(a);")
    lines.append("\t\t\tdouble px = z.x * ca - z.z * sa;")
    lines.append("\t\t\tdouble pz = z.x * sa + z.z * ca;")
    lines.append("\t\t\tz.x = px; z.z = pz;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 8. Post-rotation")
    lines.append("\t\tif (abPostRot != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble a = abPostRot * M_PI / 180.0;")
    lines.append("\t\t\tdouble ca = cos(a); double sa = sin(a);")
    lines.append("\t\t\tdouble py = z.y * ca - z.z * sa;")
    lines.append("\t\t\tdouble pz = z.y * sa + z.z * ca;")
    lines.append("\t\t\tz.y = py; z.z = pz;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 9. Twist Z")
    lines.append("\t\tif (abTwZ != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble tw = abTwZ * M_PI / 180.0 * z.z;")
    lines.append("\t\t\tdouble ct = cos(tw); double st = sin(tw);")
    lines.append("\t\t\tdouble tx = z.x * ct - z.y * st;")
    lines.append("\t\t\tdouble ty = z.x * st + z.y * ct;")
    lines.append("\t\t\tz.x = tx; z.y = ty;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 10. Radial distortion")
    lines.append("\t\tif (abRadDist != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble r = z.Length();")
    lines.append("\t\t\tif (r > 1e-15)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tdouble distort = 1.0 + abRadDist * sin(r * 4.0);")
    lines.append("\t\t\t\tz *= distort;")
    lines.append("\t\t\t\taux.DE *= fabs(distort);")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 11. Turbulence")
    lines.append("\t\tif (abTurb != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble hx = sin(z.x * 12.9898 + z.y * 78.233) * 43758.5453;")
    lines.append("\t\t\thx = hx - floor(hx);")
    lines.append("\t\t\tdouble hy = sin(z.y * 12.9898 + z.z * 78.233) * 43758.5453;")
    lines.append("\t\t\thy = hy - floor(hy);")
    lines.append("\t\t\tdouble hz = sin(z.z * 12.9898 + z.x * 78.233) * 43758.5453;")
    lines.append("\t\t\thz = hz - floor(hz);")
    lines.append("\t\t\tz.x += (hx - 0.5) * abTurb;")
    lines.append("\t\t\tz.y += (hy - 0.5) * abTurb;")
    lines.append("\t\t\tz.z += (hz - 0.5) * abTurb;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 12. Gradient color")
    lines.append("\t\tif (abGradCol != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\taux.color += abGradCol * z.Length();")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 13. DE tweak")
    lines.append("\t\tif (abDETw != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\taux.DE += abDETw;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 14. C-pixel scale")
    lines.append("\t\tif (abCpix != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tz += aux.const_c * abCpix;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 15. Sphere softness")
    lines.append("\t\tif (abSphSoft != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble r = z.Length();")
    lines.append("\t\t\tif (r > 1e-15)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tdouble soft = r / (r + abSphSoft);")
    lines.append("\t\t\t\tz *= soft;")
    lines.append("\t\t\t\taux.DE *= soft;")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("\t}")
    lines.append("")
    return "\n".join(lines) + "\n"


def make_ab_block_cl():
    """Generate the OpenCL Amazing Box extensions block."""
    lines = []
    lines.append("\t// --- Amazing Box Extensions (15 parameters) ---")
    lines.append("\t{")
    lines.append("\t\tREAL abBFOsc = fractal->transformCommon.abBoxFoldOsc;")
    lines.append("\t\tREAL abBFFreq = fractal->transformCommon.abBoxFoldOscFreq;")
    lines.append("\t\tREAL abScOsc = fractal->transformCommon.abScaleOsc;")
    lines.append("\t\tREAL abScFreq = fractal->transformCommon.abScaleOscFreq;")
    lines.append("\t\tREAL abMROsc = fractal->transformCommon.abMinROsc;")
    lines.append("\t\tREAL abMRFreq = fractal->transformCommon.abMinROscFreq;")
    lines.append("\t\tREAL abPreRot = fractal->transformCommon.abPreRotAngle;")
    lines.append("\t\tREAL abPostRot = fractal->transformCommon.abPostRotAngle;")
    lines.append("\t\tREAL abTwZ = fractal->transformCommon.abTwistZ;")
    lines.append("\t\tREAL abRadDist = fractal->transformCommon.abRadialDistort;")
    lines.append("\t\tREAL abTurb = fractal->transformCommon.abTurbulence;")
    lines.append("\t\tREAL abGradCol = fractal->transformCommon.abGradientColor;")
    lines.append("\t\tREAL abDETw = fractal->transformCommon.abDETweak;")
    lines.append("\t\tREAL abCpix = fractal->transformCommon.abCpixelScale;")
    lines.append("\t\tREAL abSphSoft = fractal->transformCommon.abSphereSoftness;")
    lines.append("")
    lines.append("\t\t// 1-2. Box fold oscillation")
    lines.append("\t\tif (abBFOsc != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL foldMod = abBFOsc * native_sin(aux->i * abBFFreq * 0.5f);")
    lines.append("\t\t\tz.x += foldMod * sign(z.x);")
    lines.append("\t\t\tz.y += foldMod * sign(z.y);")
    lines.append("\t\t\tz.z += foldMod * sign(z.z);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 3-4. Scale oscillation")
    lines.append("\t\tif (abScOsc != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL sOsc = 1.0f + abScOsc * native_sin(aux->i * abScFreq * 0.5f);")
    lines.append("\t\t\tz *= sOsc;")
    lines.append("\t\t\taux->DE *= fabs(sOsc);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 5-6. MinR oscillation")
    lines.append("\t\tif (abMROsc != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL r2 = dot(z, z);")
    lines.append("\t\t\tREAL mrOsc = abMROsc * native_sin(aux->i * abMRFreq * 0.5f);")
    lines.append("\t\t\tREAL minR2 = fmax(0.01f, 0.25f + mrOsc);")
    lines.append("\t\t\tif (r2 < minR2)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tREAL t = 1.0f / minR2;")
    lines.append("\t\t\t\tz *= t;")
    lines.append("\t\t\t\taux->DE *= t;")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 7. Pre-rotation")
    lines.append("\t\tif (abPreRot != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL a = abPreRot * M_PI_F / 180.0f * aux->i;")
    lines.append("\t\t\tREAL ca = native_cos(a); REAL sa = native_sin(a);")
    lines.append("\t\t\tREAL px = z.x * ca - z.z * sa;")
    lines.append("\t\t\tREAL pz = z.x * sa + z.z * ca;")
    lines.append("\t\t\tz.x = px; z.z = pz;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 8. Post-rotation")
    lines.append("\t\tif (abPostRot != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL a = abPostRot * M_PI_F / 180.0f;")
    lines.append("\t\t\tREAL ca = native_cos(a); REAL sa = native_sin(a);")
    lines.append("\t\t\tREAL py = z.y * ca - z.z * sa;")
    lines.append("\t\t\tREAL pz = z.y * sa + z.z * ca;")
    lines.append("\t\t\tz.y = py; z.z = pz;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 9. Twist Z")
    lines.append("\t\tif (abTwZ != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL tw = abTwZ * M_PI_F / 180.0f * z.z;")
    lines.append("\t\t\tREAL ct = native_cos(tw); REAL st = native_sin(tw);")
    lines.append("\t\t\tREAL tx = z.x * ct - z.y * st;")
    lines.append("\t\t\tREAL ty = z.x * st + z.y * ct;")
    lines.append("\t\t\tz.x = tx; z.y = ty;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 10. Radial distortion")
    lines.append("\t\tif (abRadDist != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL r = length(z);")
    lines.append("\t\t\tif (r > 1e-15f)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tREAL distort = 1.0f + abRadDist * native_sin(r * 4.0f);")
    lines.append("\t\t\t\tz *= distort;")
    lines.append("\t\t\t\taux->DE *= fabs(distort);")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 11. Turbulence")
    lines.append("\t\tif (abTurb != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL hx = native_sin(z.x * 12.9898f + z.y * 78.233f) * 43758.5453f;")
    lines.append("\t\t\thx = hx - floor(hx);")
    lines.append("\t\t\tREAL hy = native_sin(z.y * 12.9898f + z.z * 78.233f) * 43758.5453f;")
    lines.append("\t\t\thy = hy - floor(hy);")
    lines.append("\t\t\tREAL hz = native_sin(z.z * 12.9898f + z.x * 78.233f) * 43758.5453f;")
    lines.append("\t\t\thz = hz - floor(hz);")
    lines.append("\t\t\tz.x += (hx - 0.5f) * abTurb;")
    lines.append("\t\t\tz.y += (hy - 0.5f) * abTurb;")
    lines.append("\t\t\tz.z += (hz - 0.5f) * abTurb;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 12. Gradient color")
    lines.append("\t\tif (abGradCol != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\taux->color += abGradCol * length(z);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 13. DE tweak")
    lines.append("\t\tif (abDETw != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\taux->DE += abDETw;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 14. C-pixel scale")
    lines.append("\t\tif (abCpix != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tz += aux->const_c * abCpix;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 15. Sphere softness")
    lines.append("\t\tif (abSphSoft != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL r = length(z);")
    lines.append("\t\t\tif (r > 1e-15f)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tREAL soft = r / (r + abSphSoft);")
    lines.append("\t\t\t\tz *= soft;")
    lines.append("\t\t\t\taux->DE *= soft;")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("\t}")
    lines.append("")
    return "\n".join(lines) + "\n"


def update_formula_file(filepath, block):
    """Insert block before the GPU bypass marker."""
    with open(filepath, "r") as f:
        content = f.read()

    if "Amazing Box Extensions" in content:
        print(f"  SKIP (already has ABox Extensions): {os.path.basename(filepath)}")
        return False

    if MARKER not in content:
        print(f"  WARN (no marker): {os.path.basename(filepath)}")
        return False

    content = content.replace(MARKER, block + "\t" + MARKER)
    with open(filepath, "w") as f:
        f.write(content)
    return True


def make_ui_groupbox():
    """Generate the UI XML groupbox for Amazing Box extensions."""
    lines = []
    lines.append('   <widget class="QGroupBox" name="groupCheck_abox_extensions">')
    lines.append('    <property name="title">')
    lines.append('     <string>Amazing Box Extensions</string>')
    lines.append('    </property>')
    lines.append('    <property name="checkable">')
    lines.append('     <bool>true</bool>')
    lines.append('    </property>')
    lines.append('    <property name="checked">')
    lines.append('     <bool>false</bool>')
    lines.append('    </property>')
    lines.append('    <layout class="QGridLayout">')

    param_labels = [
        ("transf_ab_box_fold_osc", "Box Fold Osc:"),
        ("transf_ab_box_fold_osc_freq", "Box Fold Freq:"),
        ("transf_ab_scale_osc", "Scale Osc:"),
        ("transf_ab_scale_osc_freq", "Scale Osc Freq:"),
        ("transf_ab_min_r_osc", "MinR Osc:"),
        ("transf_ab_min_r_osc_freq", "MinR Osc Freq:"),
        ("transf_ab_pre_rot_angle", "Pre-Rotation:"),
        ("transf_ab_post_rot_angle", "Post-Rotation:"),
        ("transf_ab_twist_z", "Twist Z:"),
        ("transf_ab_radial_distort", "Radial Distort:"),
        ("transf_ab_turbulence", "Turbulence:"),
        ("transf_ab_gradient_color", "Gradient Color:"),
        ("transf_ab_de_tweak", "DE Tweak:"),
        ("transf_ab_cpixel_scale", "C-Pixel Scale:"),
        ("transf_ab_sphere_softness", "Sphere Softness:"),
    ]

    for row, (param, label) in enumerate(param_labels):
        lines.append(f'     <item row="{row}" column="0">')
        lines.append(f'      <widget class="QLabel">')
        lines.append(f'       <property name="text"><string>{label}</string></property>')
        lines.append(f'      </widget>')
        lines.append(f'     </item>')
        lines.append(f'     <item row="{row}" column="1">')
        lines.append(f'      <widget class="MyDoubleSpinBox" name="spinboxd_{param}">')
        lines.append(f'       <property name="decimals"><number>6</number></property>')
        lines.append(f'       <property name="minimum"><double>-1000.000000</double></property>')
        lines.append(f'       <property name="maximum"><double>1000.000000</double></property>')
        lines.append(f'       <property name="singleStep"><double>0.1</double></property>')
        lines.append(f'      </widget>')
        lines.append(f'     </item>')

    lines.append('    </layout>')
    lines.append('   </widget>')
    return "\n".join(lines)


def update_ui_file(filepath):
    """Insert Amazing Box extensions groupbox into UI file."""
    with open(filepath, "r") as f:
        content = f.read()

    if "abox_extensions" in content:
        print(f"  SKIP UI (already has ABox extensions): {os.path.basename(filepath)}")
        return False

    insert_marker = " </widget>\n <customwidgets>"
    if insert_marker not in content:
        insert_marker = " </widget>\n</ui>"
        if insert_marker not in content:
            print(f"  WARN UI (no insert point): {os.path.basename(filepath)}")
            return False

    groupbox = make_ui_groupbox()
    content = content.replace(insert_marker, groupbox + "\n" + insert_marker, 1)
    with open(filepath, "w") as f:
        f.write(content)
    return True


def validate_xml(filepath):
    """Validate UI file as XML."""
    try:
        ET.parse(filepath)
        return True
    except ET.ParseError as e:
        print(f"  XML ERROR in {os.path.basename(filepath)}: {e}")
        return False


def main():
    print("=== Amazing Box Extensions Upgrade Script ===")
    print()

    cpp_files = find_abox_files(CPP_DIR, "cpp")
    cl_files = find_abox_files(CL_DIR, "cl")
    ui_files = find_abox_files(UI_DIR, "ui")

    print(f"Found {len(cpp_files)} CPP, {len(cl_files)} CL, {len(ui_files)} UI files")
    print()

    cpp_block = make_ab_block_cpp()
    cl_block = make_ab_block_cl()

    print("--- Updating CPP files ---")
    cpp_ok = 0
    for f in cpp_files:
        if update_formula_file(f, cpp_block):
            cpp_ok += 1
    print(f"  Updated {cpp_ok}/{len(cpp_files)} CPP files")
    print()

    print("--- Updating CL files ---")
    cl_ok = 0
    for f in cl_files:
        if update_formula_file(f, cl_block):
            cl_ok += 1
    print(f"  Updated {cl_ok}/{len(cl_files)} CL files")
    print()

    print("--- Updating UI files ---")
    ui_ok = 0
    for f in ui_files:
        if update_ui_file(f):
            ui_ok += 1
    print(f"  Updated {ui_ok}/{len(ui_files)} UI files")
    print()

    print("--- Validating XML ---")
    xml_errors = 0
    for f in ui_files:
        if not validate_xml(f):
            xml_errors += 1
    if xml_errors == 0:
        print(f"  All {len(ui_files)} UI files valid XML")
    else:
        print(f"  WARNING: {xml_errors}/{len(ui_files)} files have XML errors!")
    print()

    print("=== Done ===")
    print(f"Total: {cpp_ok} CPP + {cl_ok} CL + {ui_ok} UI files updated")


if __name__ == "__main__":
    main()
