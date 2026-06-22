#!/usr/bin/env python3
"""
Upgrade script: Add 15 IFS/DIFS-specific parameters to all IFS and DIFS formula variants.
Inserts code blocks BEFORE '// GPU bypass: skip if all multipliers disabled' marker.
Targets: 68 formulas (IFS + DIFS families, excluding koch_ifs which already has Koch extensions).
"""
import glob
import os
import xml.etree.ElementTree as ET

BASE = "/home/ubuntu/repos/mandelbulber2-private/mandelbulber2"
CPP_DIR = os.path.join(BASE, "formula", "definition")
CL_DIR = os.path.join(BASE, "formula", "opencl")
UI_DIR = os.path.join(BASE, "formula", "ui")

MARKER = "// GPU bypass: skip if all multipliers disabled"


def find_ifs_difs_files(directory, ext):
    """Find all IFS/DIFS files in directory, excluding koch_ifs."""
    patterns = []
    if ext == "cpp":
        patterns = [
            os.path.join(directory, "fractal_*ifs*.cpp"),
            os.path.join(directory, "fractal_*difs*.cpp"),
        ]
    elif ext == "cl":
        patterns = [
            os.path.join(directory, "*ifs*.cl"),
            os.path.join(directory, "*difs*.cl"),
        ]
    elif ext == "ui":
        patterns = [
            os.path.join(directory, "*ifs*.ui"),
            os.path.join(directory, "*difs*.ui"),
        ]

    files = set()
    for p in patterns:
        files.update(glob.glob(p))

    # Exclude koch_ifs (already has Koch extensions)
    files = {f for f in files if "koch_ifs" not in os.path.basename(f)}
    return sorted(files)


def make_ifs_block_cpp():
    """Generate the C++ IFS/DIFS extensions block."""
    lines = []
    lines.append("\t// --- IFS/DIFS Extensions (15 parameters) ---")
    lines.append("\t{")
    lines.append("\t\tdouble ifsFoldOsc = fractal->transformCommon.ifsFoldOscAmp;")
    lines.append("\t\tdouble ifsFoldFreq = fractal->transformCommon.ifsFoldOscFreq;")
    lines.append("\t\tdouble ifsScaleOsc = fractal->transformCommon.ifsScaleOsc;")
    lines.append("\t\tdouble ifsScaleFreq = fractal->transformCommon.ifsScaleOscFreq;")
    lines.append("\t\tdouble ifsPreRot = fractal->transformCommon.ifsPreRotAngle;")
    lines.append("\t\tdouble ifsPostRot = fractal->transformCommon.ifsPostRotAngle;")
    lines.append("\t\tdouble ifsTwZ = fractal->transformCommon.ifsTwistZ;")
    lines.append("\t\tdouble ifsOffWarp = fractal->transformCommon.ifsOffsetWarp;")
    lines.append("\t\tdouble ifsRadDist = fractal->transformCommon.ifsRadialDistort;")
    lines.append("\t\tdouble ifsTurb = fractal->transformCommon.ifsTurbulence;")
    lines.append("\t\tdouble ifsGradCol = fractal->transformCommon.ifsGradientColor;")
    lines.append("\t\tdouble ifsDETw = fractal->transformCommon.ifsDETweak;")
    lines.append("\t\tdouble ifsCpix = fractal->transformCommon.ifsCpixelInject;")
    lines.append("\t\tdouble ifsSphere = fractal->transformCommon.ifsSphereFold;")
    lines.append("\t\tdouble ifsEdgeSoft = fractal->transformCommon.ifsEdgeSoftness;")
    lines.append("")
    lines.append("\t\t// 1-2. Fold oscillation")
    lines.append("\t\tif (ifsFoldOsc != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble fOsc = ifsFoldOsc * sin(aux.i * ifsFoldFreq * 0.5);")
    lines.append("\t\t\tz.x += fOsc * sin(z.y * 3.0);")
    lines.append("\t\t\tz.y += fOsc * sin(z.z * 3.0);")
    lines.append("\t\t\tz.z += fOsc * sin(z.x * 3.0);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 3-4. Scale oscillation")
    lines.append("\t\tif (ifsScaleOsc != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble sOsc = 1.0 + ifsScaleOsc * sin(aux.i * ifsScaleFreq * 0.5);")
    lines.append("\t\t\tz *= sOsc;")
    lines.append("\t\t\taux.DE *= fabs(sOsc);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 5. Pre-rotation")
    lines.append("\t\tif (ifsPreRot != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble a = ifsPreRot * M_PI / 180.0 * aux.i;")
    lines.append("\t\t\tdouble ca = cos(a); double sa = sin(a);")
    lines.append("\t\t\tdouble px = z.x * ca - z.y * sa;")
    lines.append("\t\t\tdouble py = z.x * sa + z.y * ca;")
    lines.append("\t\t\tz.x = px; z.y = py;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 6. Post-rotation")
    lines.append("\t\tif (ifsPostRot != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble a = ifsPostRot * M_PI / 180.0;")
    lines.append("\t\t\tdouble ca = cos(a); double sa = sin(a);")
    lines.append("\t\t\tdouble py = z.y * ca - z.z * sa;")
    lines.append("\t\t\tdouble pz = z.y * sa + z.z * ca;")
    lines.append("\t\t\tz.y = py; z.z = pz;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 7. Twist Z")
    lines.append("\t\tif (ifsTwZ != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble tw = ifsTwZ * M_PI / 180.0 * z.z;")
    lines.append("\t\t\tdouble ct = cos(tw); double st = sin(tw);")
    lines.append("\t\t\tdouble tx = z.x * ct - z.y * st;")
    lines.append("\t\t\tdouble ty = z.x * st + z.y * ct;")
    lines.append("\t\t\tz.x = tx; z.y = ty;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 8. Offset warp")
    lines.append("\t\tif (ifsOffWarp != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tz.x += ifsOffWarp * sin(z.y * 2.0 + aux.i * 0.5);")
    lines.append("\t\t\tz.y += ifsOffWarp * sin(z.z * 2.0 + aux.i * 0.7);")
    lines.append("\t\t\tz.z += ifsOffWarp * sin(z.x * 2.0 + aux.i * 0.3);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 9. Radial distortion")
    lines.append("\t\tif (ifsRadDist != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble r = z.Length();")
    lines.append("\t\t\tif (r > 1e-15)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tdouble distort = 1.0 + ifsRadDist * sin(r * 4.0);")
    lines.append("\t\t\t\tz *= distort;")
    lines.append("\t\t\t\taux.DE *= fabs(distort);")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 10. Turbulence")
    lines.append("\t\tif (ifsTurb != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble hx = sin(z.x * 12.9898 + z.y * 78.233) * 43758.5453;")
    lines.append("\t\t\thx = hx - floor(hx);")
    lines.append("\t\t\tdouble hy = sin(z.y * 12.9898 + z.z * 78.233) * 43758.5453;")
    lines.append("\t\t\thy = hy - floor(hy);")
    lines.append("\t\t\tdouble hz = sin(z.z * 12.9898 + z.x * 78.233) * 43758.5453;")
    lines.append("\t\t\thz = hz - floor(hz);")
    lines.append("\t\t\tz.x += (hx - 0.5) * ifsTurb;")
    lines.append("\t\t\tz.y += (hy - 0.5) * ifsTurb;")
    lines.append("\t\t\tz.z += (hz - 0.5) * ifsTurb;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 11. Gradient color")
    lines.append("\t\tif (ifsGradCol != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\taux.color += ifsGradCol * z.Length();")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 12. DE tweak")
    lines.append("\t\tif (ifsDETw != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\taux.DE += ifsDETw;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 13. C-pixel injection")
    lines.append("\t\tif (ifsCpix != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tz += aux.const_c * ifsCpix;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 14. Sphere fold")
    lines.append("\t\tif (ifsSphere != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble r2 = z.Dot(z);")
    lines.append("\t\t\tdouble minR2 = 0.25;")
    lines.append("\t\t\tdouble fixedR2 = 1.0;")
    lines.append("\t\t\tif (r2 < minR2)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tdouble t = fixedR2 / minR2;")
    lines.append("\t\t\t\tz *= t * ifsSphere;")
    lines.append("\t\t\t\taux.DE *= fabs(t * ifsSphere);")
    lines.append("\t\t\t}")
    lines.append("\t\t\telse if (r2 < fixedR2)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tdouble t = fixedR2 / r2;")
    lines.append("\t\t\t\tz *= t * ifsSphere;")
    lines.append("\t\t\t\taux.DE *= fabs(t * ifsSphere);")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 15. Edge softness")
    lines.append("\t\tif (ifsEdgeSoft != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble r = z.Length();")
    lines.append("\t\t\tif (r > 1e-15)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tdouble soft = r / (r + ifsEdgeSoft);")
    lines.append("\t\t\t\tz *= soft;")
    lines.append("\t\t\t\taux.DE *= soft;")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("\t}")
    lines.append("")
    return "\n".join(lines) + "\n"


def make_ifs_block_cl():
    """Generate the OpenCL IFS/DIFS extensions block."""
    lines = []
    lines.append("\t// --- IFS/DIFS Extensions (15 parameters) ---")
    lines.append("\t{")
    lines.append("\t\tREAL ifsFoldOsc = fractal->transformCommon.ifsFoldOscAmp;")
    lines.append("\t\tREAL ifsFoldFreq = fractal->transformCommon.ifsFoldOscFreq;")
    lines.append("\t\tREAL ifsScaleOsc = fractal->transformCommon.ifsScaleOsc;")
    lines.append("\t\tREAL ifsScaleFreq = fractal->transformCommon.ifsScaleOscFreq;")
    lines.append("\t\tREAL ifsPreRot = fractal->transformCommon.ifsPreRotAngle;")
    lines.append("\t\tREAL ifsPostRot = fractal->transformCommon.ifsPostRotAngle;")
    lines.append("\t\tREAL ifsTwZ = fractal->transformCommon.ifsTwistZ;")
    lines.append("\t\tREAL ifsOffWarp = fractal->transformCommon.ifsOffsetWarp;")
    lines.append("\t\tREAL ifsRadDist = fractal->transformCommon.ifsRadialDistort;")
    lines.append("\t\tREAL ifsTurb = fractal->transformCommon.ifsTurbulence;")
    lines.append("\t\tREAL ifsGradCol = fractal->transformCommon.ifsGradientColor;")
    lines.append("\t\tREAL ifsDETw = fractal->transformCommon.ifsDETweak;")
    lines.append("\t\tREAL ifsCpix = fractal->transformCommon.ifsCpixelInject;")
    lines.append("\t\tREAL ifsSphere = fractal->transformCommon.ifsSphereFold;")
    lines.append("\t\tREAL ifsEdgeSoft = fractal->transformCommon.ifsEdgeSoftness;")
    lines.append("")
    lines.append("\t\t// 1-2. Fold oscillation")
    lines.append("\t\tif (ifsFoldOsc != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL fOsc = ifsFoldOsc * native_sin(aux->i * ifsFoldFreq * 0.5f);")
    lines.append("\t\t\tz.x += fOsc * native_sin(z.y * 3.0f);")
    lines.append("\t\t\tz.y += fOsc * native_sin(z.z * 3.0f);")
    lines.append("\t\t\tz.z += fOsc * native_sin(z.x * 3.0f);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 3-4. Scale oscillation")
    lines.append("\t\tif (ifsScaleOsc != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL sOsc = 1.0f + ifsScaleOsc * native_sin(aux->i * ifsScaleFreq * 0.5f);")
    lines.append("\t\t\tz *= sOsc;")
    lines.append("\t\t\taux->DE *= fabs(sOsc);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 5. Pre-rotation")
    lines.append("\t\tif (ifsPreRot != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL a = ifsPreRot * M_PI_F / 180.0f * aux->i;")
    lines.append("\t\t\tREAL ca = native_cos(a); REAL sa = native_sin(a);")
    lines.append("\t\t\tREAL px = z.x * ca - z.y * sa;")
    lines.append("\t\t\tREAL py = z.x * sa + z.y * ca;")
    lines.append("\t\t\tz.x = px; z.y = py;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 6. Post-rotation")
    lines.append("\t\tif (ifsPostRot != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL a = ifsPostRot * M_PI_F / 180.0f;")
    lines.append("\t\t\tREAL ca = native_cos(a); REAL sa = native_sin(a);")
    lines.append("\t\t\tREAL py = z.y * ca - z.z * sa;")
    lines.append("\t\t\tREAL pz = z.y * sa + z.z * ca;")
    lines.append("\t\t\tz.y = py; z.z = pz;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 7. Twist Z")
    lines.append("\t\tif (ifsTwZ != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL tw = ifsTwZ * M_PI_F / 180.0f * z.z;")
    lines.append("\t\t\tREAL ct = native_cos(tw); REAL st = native_sin(tw);")
    lines.append("\t\t\tREAL tx = z.x * ct - z.y * st;")
    lines.append("\t\t\tREAL ty = z.x * st + z.y * ct;")
    lines.append("\t\t\tz.x = tx; z.y = ty;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 8. Offset warp")
    lines.append("\t\tif (ifsOffWarp != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tz.x += ifsOffWarp * native_sin(z.y * 2.0f + aux->i * 0.5f);")
    lines.append("\t\t\tz.y += ifsOffWarp * native_sin(z.z * 2.0f + aux->i * 0.7f);")
    lines.append("\t\t\tz.z += ifsOffWarp * native_sin(z.x * 2.0f + aux->i * 0.3f);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 9. Radial distortion")
    lines.append("\t\tif (ifsRadDist != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL r = length(z);")
    lines.append("\t\t\tif (r > 1e-15f)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tREAL distort = 1.0f + ifsRadDist * native_sin(r * 4.0f);")
    lines.append("\t\t\t\tz *= distort;")
    lines.append("\t\t\t\taux->DE *= fabs(distort);")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 10. Turbulence")
    lines.append("\t\tif (ifsTurb != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL hx = native_sin(z.x * 12.9898f + z.y * 78.233f) * 43758.5453f;")
    lines.append("\t\t\thx = hx - floor(hx);")
    lines.append("\t\t\tREAL hy = native_sin(z.y * 12.9898f + z.z * 78.233f) * 43758.5453f;")
    lines.append("\t\t\thy = hy - floor(hy);")
    lines.append("\t\t\tREAL hz = native_sin(z.z * 12.9898f + z.x * 78.233f) * 43758.5453f;")
    lines.append("\t\t\thz = hz - floor(hz);")
    lines.append("\t\t\tz.x += (hx - 0.5f) * ifsTurb;")
    lines.append("\t\t\tz.y += (hy - 0.5f) * ifsTurb;")
    lines.append("\t\t\tz.z += (hz - 0.5f) * ifsTurb;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 11. Gradient color")
    lines.append("\t\tif (ifsGradCol != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\taux->color += ifsGradCol * length(z);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 12. DE tweak")
    lines.append("\t\tif (ifsDETw != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\taux->DE += ifsDETw;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 13. C-pixel injection")
    lines.append("\t\tif (ifsCpix != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tz += aux->const_c * ifsCpix;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 14. Sphere fold")
    lines.append("\t\tif (ifsSphere != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL r2 = dot(z, z);")
    lines.append("\t\t\tREAL minR2 = 0.25f;")
    lines.append("\t\t\tREAL fixedR2 = 1.0f;")
    lines.append("\t\t\tif (r2 < minR2)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tREAL t = fixedR2 / minR2;")
    lines.append("\t\t\t\tz *= t * ifsSphere;")
    lines.append("\t\t\t\taux->DE *= fabs(t * ifsSphere);")
    lines.append("\t\t\t}")
    lines.append("\t\t\telse if (r2 < fixedR2)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tREAL t = fixedR2 / r2;")
    lines.append("\t\t\t\tz *= t * ifsSphere;")
    lines.append("\t\t\t\taux->DE *= fabs(t * ifsSphere);")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 15. Edge softness")
    lines.append("\t\tif (ifsEdgeSoft != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL r = length(z);")
    lines.append("\t\t\tif (r > 1e-15f)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tREAL soft = r / (r + ifsEdgeSoft);")
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

    if "IFS/DIFS Extensions" in content:
        print(f"  SKIP (already has IFS/DIFS Extensions): {os.path.basename(filepath)}")
        return False

    if MARKER not in content:
        print(f"  WARN (no marker): {os.path.basename(filepath)}")
        return False

    content = content.replace(MARKER, block + "\t" + MARKER)
    with open(filepath, "w") as f:
        f.write(content)
    return True


def make_ui_groupbox():
    """Generate the UI XML groupbox for IFS/DIFS extensions."""
    lines = []
    lines.append('   <widget class="QGroupBox" name="groupCheck_ifs_difs_extensions">')
    lines.append('    <property name="title">')
    lines.append('     <string>IFS/DIFS Extensions</string>')
    lines.append('    </property>')
    lines.append('    <property name="checkable">')
    lines.append('     <bool>true</bool>')
    lines.append('    </property>')
    lines.append('    <property name="checked">')
    lines.append('     <bool>false</bool>')
    lines.append('    </property>')
    lines.append('    <layout class="QGridLayout">')

    param_labels = [
        ("transf_ifs_fold_osc_amp", "Fold Osc Amp:"),
        ("transf_ifs_fold_osc_freq", "Fold Osc Freq:"),
        ("transf_ifs_scale_osc", "Scale Osc:"),
        ("transf_ifs_scale_osc_freq", "Scale Osc Freq:"),
        ("transf_ifs_pre_rot_angle", "Pre-Rotation:"),
        ("transf_ifs_post_rot_angle", "Post-Rotation:"),
        ("transf_ifs_twist_z", "Twist Z:"),
        ("transf_ifs_offset_warp", "Offset Warp:"),
        ("transf_ifs_radial_distort", "Radial Distort:"),
        ("transf_ifs_turbulence", "Turbulence:"),
        ("transf_ifs_gradient_color", "Gradient Color:"),
        ("transf_ifs_de_tweak", "DE Tweak:"),
        ("transf_ifs_cpixel_inject", "C-Pixel Inject:"),
        ("transf_ifs_sphere_fold", "Sphere Fold:"),
        ("transf_ifs_edge_softness", "Edge Softness:"),
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
    """Insert IFS/DIFS extensions groupbox into UI file."""
    with open(filepath, "r") as f:
        content = f.read()

    if "ifs_difs_extensions" in content:
        print(f"  SKIP UI (already has IFS/DIFS extensions): {os.path.basename(filepath)}")
        return False

    # Insert before " </widget>\n <customwidgets>" or before " </widget>\n</ui>"
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
    print("=== IFS/DIFS Extensions Upgrade Script ===")
    print()

    cpp_files = find_ifs_difs_files(CPP_DIR, "cpp")
    cl_files = find_ifs_difs_files(CL_DIR, "cl")
    ui_files = find_ifs_difs_files(UI_DIR, "ui")

    print(f"Found {len(cpp_files)} CPP, {len(cl_files)} CL, {len(ui_files)} UI files")
    print()

    cpp_block = make_ifs_block_cpp()
    cl_block = make_ifs_block_cl()

    # Update CPP files
    print("--- Updating CPP files ---")
    cpp_ok = 0
    for f in cpp_files:
        if update_formula_file(f, cpp_block):
            cpp_ok += 1
    print(f"  Updated {cpp_ok}/{len(cpp_files)} CPP files")
    print()

    # Update CL files
    print("--- Updating CL files ---")
    cl_ok = 0
    for f in cl_files:
        if update_formula_file(f, cl_block):
            cl_ok += 1
    print(f"  Updated {cl_ok}/{len(cl_files)} CL files")
    print()

    # Update UI files
    print("--- Updating UI files ---")
    ui_ok = 0
    for f in ui_files:
        if update_ui_file(f):
            ui_ok += 1
    print(f"  Updated {ui_ok}/{len(ui_files)} UI files")
    print()

    # Validate XML
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
