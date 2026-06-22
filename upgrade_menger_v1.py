#!/usr/bin/env python3
"""
Upgrade script: Add 15 Menger-specific parameters to all 34 Menger formula variants.
"""
import glob
import os
import xml.etree.ElementTree as ET

BASE = "/home/ubuntu/repos/mandelbulber2-private/mandelbulber2"
CPP_DIR = os.path.join(BASE, "formula", "definition")
CL_DIR = os.path.join(BASE, "formula", "opencl")
UI_DIR = os.path.join(BASE, "formula", "ui")

MARKER = "// GPU bypass: skip if all multipliers disabled"


def find_menger_files(directory, ext):
    """Find all Menger files in directory."""
    if ext == "cpp":
        pattern = os.path.join(directory, "fractal_*menger*.cpp")
    elif ext == "cl":
        pattern = os.path.join(directory, "*menger*.cl")
    elif ext == "ui":
        pattern = os.path.join(directory, "*menger*.ui")
    return sorted(glob.glob(pattern))


def make_mg_block_cpp():
    """Generate the C++ Menger extensions block."""
    lines = []
    lines.append("\t// --- Menger Extensions (15 parameters) ---")
    lines.append("\t{")
    lines.append("\t\tdouble mgScOsc = fractal->transformCommon.mgScaleOsc;")
    lines.append("\t\tdouble mgScFreq = fractal->transformCommon.mgScaleOscFreq;")
    lines.append("\t\tdouble mgFoldPow = fractal->transformCommon.mgFoldPower;")
    lines.append("\t\tdouble mgPreRot = fractal->transformCommon.mgPreRotAngle;")
    lines.append("\t\tdouble mgPostRot = fractal->transformCommon.mgPostRotAngle;")
    lines.append("\t\tdouble mgTwZ = fractal->transformCommon.mgTwistZ;")
    lines.append("\t\tdouble mgOffOsc = fractal->transformCommon.mgOffsetOsc;")
    lines.append("\t\tdouble mgOffFreq = fractal->transformCommon.mgOffsetOscFreq;")
    lines.append("\t\tdouble mgRadDist = fractal->transformCommon.mgRadialDistort;")
    lines.append("\t\tdouble mgTurb = fractal->transformCommon.mgTurbulence;")
    lines.append("\t\tdouble mgGradCol = fractal->transformCommon.mgGradientColor;")
    lines.append("\t\tdouble mgDETw = fractal->transformCommon.mgDETweak;")
    lines.append("\t\tdouble mgCpix = fractal->transformCommon.mgCpixelInject;")
    lines.append("\t\tdouble mgSphere = fractal->transformCommon.mgSphereFold;")
    lines.append("\t\tdouble mgEdgeSoft = fractal->transformCommon.mgEdgeSoftness;")
    lines.append("")
    lines.append("\t\t// 1-2. Scale oscillation")
    lines.append("\t\tif (mgScOsc != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble sOsc = 1.0 + mgScOsc * sin(aux.i * mgScFreq * 0.5);")
    lines.append("\t\t\tz *= sOsc;")
    lines.append("\t\t\taux.DE *= fabs(sOsc);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 3. Fold power")
    lines.append("\t\tif (mgFoldPow != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble p = 1.0 + mgFoldPow;")
    lines.append("\t\t\tz.x = sign(z.x) * pow(fabs(z.x) + 1e-20, p);")
    lines.append("\t\t\tz.y = sign(z.y) * pow(fabs(z.y) + 1e-20, p);")
    lines.append("\t\t\tz.z = sign(z.z) * pow(fabs(z.z) + 1e-20, p);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 4. Pre-rotation")
    lines.append("\t\tif (mgPreRot != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble a = mgPreRot * M_PI / 180.0 * aux.i;")
    lines.append("\t\t\tdouble ca = cos(a); double sa = sin(a);")
    lines.append("\t\t\tdouble px = z.x * ca - z.z * sa;")
    lines.append("\t\t\tdouble pz = z.x * sa + z.z * ca;")
    lines.append("\t\t\tz.x = px; z.z = pz;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 5. Post-rotation")
    lines.append("\t\tif (mgPostRot != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble a = mgPostRot * M_PI / 180.0;")
    lines.append("\t\t\tdouble ca = cos(a); double sa = sin(a);")
    lines.append("\t\t\tdouble py = z.y * ca - z.z * sa;")
    lines.append("\t\t\tdouble pz = z.y * sa + z.z * ca;")
    lines.append("\t\t\tz.y = py; z.z = pz;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 6. Twist Z")
    lines.append("\t\tif (mgTwZ != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble tw = mgTwZ * M_PI / 180.0 * z.z;")
    lines.append("\t\t\tdouble ct = cos(tw); double st = sin(tw);")
    lines.append("\t\t\tdouble tx = z.x * ct - z.y * st;")
    lines.append("\t\t\tdouble ty = z.x * st + z.y * ct;")
    lines.append("\t\t\tz.x = tx; z.y = ty;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 7-8. Offset oscillation")
    lines.append("\t\tif (mgOffOsc != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble oOsc = mgOffOsc * sin(aux.i * mgOffFreq * 0.5);")
    lines.append("\t\t\tz.x += oOsc;")
    lines.append("\t\t\tz.y += oOsc * 0.7;")
    lines.append("\t\t\tz.z += oOsc * 0.5;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 9. Radial distortion")
    lines.append("\t\tif (mgRadDist != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble r = z.Length();")
    lines.append("\t\t\tif (r > 1e-15)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tdouble distort = 1.0 + mgRadDist * sin(r * 4.0);")
    lines.append("\t\t\t\tz *= distort;")
    lines.append("\t\t\t\taux.DE *= fabs(distort);")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 10. Turbulence")
    lines.append("\t\tif (mgTurb != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble hx = sin(z.x * 12.9898 + z.y * 78.233) * 43758.5453;")
    lines.append("\t\t\thx = hx - floor(hx);")
    lines.append("\t\t\tdouble hy = sin(z.y * 12.9898 + z.z * 78.233) * 43758.5453;")
    lines.append("\t\t\thy = hy - floor(hy);")
    lines.append("\t\t\tdouble hz = sin(z.z * 12.9898 + z.x * 78.233) * 43758.5453;")
    lines.append("\t\t\thz = hz - floor(hz);")
    lines.append("\t\t\tz.x += (hx - 0.5) * mgTurb;")
    lines.append("\t\t\tz.y += (hy - 0.5) * mgTurb;")
    lines.append("\t\t\tz.z += (hz - 0.5) * mgTurb;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 11. Gradient color")
    lines.append("\t\tif (mgGradCol != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\taux.color += mgGradCol * z.Length();")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 12. DE tweak")
    lines.append("\t\tif (mgDETw != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\taux.DE += mgDETw;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 13. C-pixel injection")
    lines.append("\t\tif (mgCpix != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tz += aux.const_c * mgCpix;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 14. Sphere fold")
    lines.append("\t\tif (mgSphere != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble r2 = z.Dot(z);")
    lines.append("\t\t\tdouble minR2 = 0.25;")
    lines.append("\t\t\tdouble fixedR2 = 1.0;")
    lines.append("\t\t\tif (r2 < minR2)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tdouble t = fixedR2 / minR2;")
    lines.append("\t\t\t\tz *= t * mgSphere;")
    lines.append("\t\t\t\taux.DE *= fabs(t * mgSphere);")
    lines.append("\t\t\t}")
    lines.append("\t\t\telse if (r2 < fixedR2)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tdouble t = fixedR2 / r2;")
    lines.append("\t\t\t\tz *= t * mgSphere;")
    lines.append("\t\t\t\taux.DE *= fabs(t * mgSphere);")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 15. Edge softness")
    lines.append("\t\tif (mgEdgeSoft != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble r = z.Length();")
    lines.append("\t\t\tif (r > 1e-15)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tdouble soft = r / (r + mgEdgeSoft);")
    lines.append("\t\t\t\tz *= soft;")
    lines.append("\t\t\t\taux.DE *= soft;")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("\t}")
    lines.append("")
    return "\n".join(lines) + "\n"


def make_mg_block_cl():
    """Generate the OpenCL Menger extensions block."""
    lines = []
    lines.append("\t// --- Menger Extensions (15 parameters) ---")
    lines.append("\t{")
    lines.append("\t\tREAL mgScOsc = fractal->transformCommon.mgScaleOsc;")
    lines.append("\t\tREAL mgScFreq = fractal->transformCommon.mgScaleOscFreq;")
    lines.append("\t\tREAL mgFoldPow = fractal->transformCommon.mgFoldPower;")
    lines.append("\t\tREAL mgPreRot = fractal->transformCommon.mgPreRotAngle;")
    lines.append("\t\tREAL mgPostRot = fractal->transformCommon.mgPostRotAngle;")
    lines.append("\t\tREAL mgTwZ = fractal->transformCommon.mgTwistZ;")
    lines.append("\t\tREAL mgOffOsc = fractal->transformCommon.mgOffsetOsc;")
    lines.append("\t\tREAL mgOffFreq = fractal->transformCommon.mgOffsetOscFreq;")
    lines.append("\t\tREAL mgRadDist = fractal->transformCommon.mgRadialDistort;")
    lines.append("\t\tREAL mgTurb = fractal->transformCommon.mgTurbulence;")
    lines.append("\t\tREAL mgGradCol = fractal->transformCommon.mgGradientColor;")
    lines.append("\t\tREAL mgDETw = fractal->transformCommon.mgDETweak;")
    lines.append("\t\tREAL mgCpix = fractal->transformCommon.mgCpixelInject;")
    lines.append("\t\tREAL mgSphere = fractal->transformCommon.mgSphereFold;")
    lines.append("\t\tREAL mgEdgeSoft = fractal->transformCommon.mgEdgeSoftness;")
    lines.append("")
    lines.append("\t\t// 1-2. Scale oscillation")
    lines.append("\t\tif (mgScOsc != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL sOsc = 1.0f + mgScOsc * native_sin(aux->i * mgScFreq * 0.5f);")
    lines.append("\t\t\tz *= sOsc;")
    lines.append("\t\t\taux->DE *= fabs(sOsc);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 3. Fold power")
    lines.append("\t\tif (mgFoldPow != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL p = 1.0f + mgFoldPow;")
    lines.append("\t\t\tz.x = sign(z.x) * pow(fabs(z.x) + 1e-20f, p);")
    lines.append("\t\t\tz.y = sign(z.y) * pow(fabs(z.y) + 1e-20f, p);")
    lines.append("\t\t\tz.z = sign(z.z) * pow(fabs(z.z) + 1e-20f, p);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 4. Pre-rotation")
    lines.append("\t\tif (mgPreRot != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL a = mgPreRot * M_PI_F / 180.0f * aux->i;")
    lines.append("\t\t\tREAL ca = native_cos(a); REAL sa = native_sin(a);")
    lines.append("\t\t\tREAL px = z.x * ca - z.z * sa;")
    lines.append("\t\t\tREAL pz = z.x * sa + z.z * ca;")
    lines.append("\t\t\tz.x = px; z.z = pz;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 5. Post-rotation")
    lines.append("\t\tif (mgPostRot != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL a = mgPostRot * M_PI_F / 180.0f;")
    lines.append("\t\t\tREAL ca = native_cos(a); REAL sa = native_sin(a);")
    lines.append("\t\t\tREAL py = z.y * ca - z.z * sa;")
    lines.append("\t\t\tREAL pz = z.y * sa + z.z * ca;")
    lines.append("\t\t\tz.y = py; z.z = pz;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 6. Twist Z")
    lines.append("\t\tif (mgTwZ != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL tw = mgTwZ * M_PI_F / 180.0f * z.z;")
    lines.append("\t\t\tREAL ct = native_cos(tw); REAL st = native_sin(tw);")
    lines.append("\t\t\tREAL tx = z.x * ct - z.y * st;")
    lines.append("\t\t\tREAL ty = z.x * st + z.y * ct;")
    lines.append("\t\t\tz.x = tx; z.y = ty;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 7-8. Offset oscillation")
    lines.append("\t\tif (mgOffOsc != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL oOsc = mgOffOsc * native_sin(aux->i * mgOffFreq * 0.5f);")
    lines.append("\t\t\tz.x += oOsc;")
    lines.append("\t\t\tz.y += oOsc * 0.7f;")
    lines.append("\t\t\tz.z += oOsc * 0.5f;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 9. Radial distortion")
    lines.append("\t\tif (mgRadDist != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL r = length(z);")
    lines.append("\t\t\tif (r > 1e-15f)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tREAL distort = 1.0f + mgRadDist * native_sin(r * 4.0f);")
    lines.append("\t\t\t\tz *= distort;")
    lines.append("\t\t\t\taux->DE *= fabs(distort);")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 10. Turbulence")
    lines.append("\t\tif (mgTurb != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL hx = native_sin(z.x * 12.9898f + z.y * 78.233f) * 43758.5453f;")
    lines.append("\t\t\thx = hx - floor(hx);")
    lines.append("\t\t\tREAL hy = native_sin(z.y * 12.9898f + z.z * 78.233f) * 43758.5453f;")
    lines.append("\t\t\thy = hy - floor(hy);")
    lines.append("\t\t\tREAL hz = native_sin(z.z * 12.9898f + z.x * 78.233f) * 43758.5453f;")
    lines.append("\t\t\thz = hz - floor(hz);")
    lines.append("\t\t\tz.x += (hx - 0.5f) * mgTurb;")
    lines.append("\t\t\tz.y += (hy - 0.5f) * mgTurb;")
    lines.append("\t\t\tz.z += (hz - 0.5f) * mgTurb;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 11. Gradient color")
    lines.append("\t\tif (mgGradCol != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\taux->color += mgGradCol * length(z);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 12. DE tweak")
    lines.append("\t\tif (mgDETw != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\taux->DE += mgDETw;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 13. C-pixel injection")
    lines.append("\t\tif (mgCpix != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tz += aux->const_c * mgCpix;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 14. Sphere fold")
    lines.append("\t\tif (mgSphere != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL r2 = dot(z, z);")
    lines.append("\t\t\tREAL minR2 = 0.25f;")
    lines.append("\t\t\tREAL fixedR2 = 1.0f;")
    lines.append("\t\t\tif (r2 < minR2)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tREAL t = fixedR2 / minR2;")
    lines.append("\t\t\t\tz *= t * mgSphere;")
    lines.append("\t\t\t\taux->DE *= fabs(t * mgSphere);")
    lines.append("\t\t\t}")
    lines.append("\t\t\telse if (r2 < fixedR2)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tREAL t = fixedR2 / r2;")
    lines.append("\t\t\t\tz *= t * mgSphere;")
    lines.append("\t\t\t\taux->DE *= fabs(t * mgSphere);")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 15. Edge softness")
    lines.append("\t\tif (mgEdgeSoft != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL r = length(z);")
    lines.append("\t\t\tif (r > 1e-15f)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tREAL soft = r / (r + mgEdgeSoft);")
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

    if "Menger Extensions" in content:
        print(f"  SKIP (already has Menger Extensions): {os.path.basename(filepath)}")
        return False

    if MARKER not in content:
        print(f"  WARN (no marker): {os.path.basename(filepath)}")
        return False

    content = content.replace(MARKER, block + "\t" + MARKER)
    with open(filepath, "w") as f:
        f.write(content)
    return True


def make_ui_groupbox():
    """Generate the UI XML groupbox for Menger extensions."""
    lines = []
    lines.append('   <widget class="QGroupBox" name="groupCheck_menger_extensions">')
    lines.append('    <property name="title">')
    lines.append('     <string>Menger Extensions</string>')
    lines.append('    </property>')
    lines.append('    <property name="checkable">')
    lines.append('     <bool>true</bool>')
    lines.append('    </property>')
    lines.append('    <property name="checked">')
    lines.append('     <bool>false</bool>')
    lines.append('    </property>')
    lines.append('    <layout class="QGridLayout">')

    param_labels = [
        ("transf_mg_scale_osc", "Scale Osc:"),
        ("transf_mg_scale_osc_freq", "Scale Osc Freq:"),
        ("transf_mg_fold_power", "Fold Power:"),
        ("transf_mg_pre_rot_angle", "Pre-Rotation:"),
        ("transf_mg_post_rot_angle", "Post-Rotation:"),
        ("transf_mg_twist_z", "Twist Z:"),
        ("transf_mg_offset_osc", "Offset Osc:"),
        ("transf_mg_offset_osc_freq", "Offset Osc Freq:"),
        ("transf_mg_radial_distort", "Radial Distort:"),
        ("transf_mg_turbulence", "Turbulence:"),
        ("transf_mg_gradient_color", "Gradient Color:"),
        ("transf_mg_de_tweak", "DE Tweak:"),
        ("transf_mg_cpixel_inject", "C-Pixel Inject:"),
        ("transf_mg_sphere_fold", "Sphere Fold:"),
        ("transf_mg_edge_softness", "Edge Softness:"),
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
    """Insert Menger extensions groupbox into UI file."""
    with open(filepath, "r") as f:
        content = f.read()

    if "menger_extensions" in content:
        print(f"  SKIP UI (already has Menger extensions): {os.path.basename(filepath)}")
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
    print("=== Menger Extensions Upgrade Script ===")
    print()

    cpp_files = find_menger_files(CPP_DIR, "cpp")
    cl_files = find_menger_files(CL_DIR, "cl")
    ui_files = find_menger_files(UI_DIR, "ui")

    print(f"Found {len(cpp_files)} CPP, {len(cl_files)} CL, {len(ui_files)} UI files")
    print()

    cpp_block = make_mg_block_cpp()
    cl_block = make_mg_block_cl()

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
