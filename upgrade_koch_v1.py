#!/usr/bin/env python3
"""
Upgrade script: Add 20 Koch-specific parameters to all Koch formula variants.
Inserts code blocks BEFORE '// GPU bypass: skip if all multipliers disabled' marker.
"""
import glob
import os
import xml.etree.ElementTree as ET

BASE = "/home/ubuntu/repos/mandelbulber2-private/mandelbulber2"
CPP_DIR = os.path.join(BASE, "formula", "definition")
CL_DIR = os.path.join(BASE, "formula", "opencl")
UI_DIR = os.path.join(BASE, "formula", "ui")

MARKER = "// GPU bypass: skip if all multipliers disabled"

PARAMS = [
    ("kochFoldAngle", "transf_koch_fold_angle"),
    ("kochFoldAngleFreq", "transf_koch_fold_angle_freq"),
    ("kochScaleOsc", "transf_koch_scale_osc"),
    ("kochScaleOscFreq", "transf_koch_scale_osc_freq"),
    ("kochOffsetOscX", "transf_koch_offset_osc_x"),
    ("kochOffsetOscY", "transf_koch_offset_osc_y"),
    ("kochOffsetOscZ", "transf_koch_offset_osc_z"),
    ("kochOffsetOscFreq", "transf_koch_offset_osc_freq"),
    ("kochPreRotAngle", "transf_koch_pre_rot_angle"),
    ("kochPostRotAngle", "transf_koch_post_rot_angle"),
    ("kochYOffWarp", "transf_koch_yoff_warp"),
    ("kochTwistZ", "transf_koch_twist_z"),
    ("kochRadialDistort", "transf_koch_radial_distort"),
    ("kochTurbulence", "transf_koch_turbulence"),
    ("kochGradientColor", "transf_koch_gradient_color"),
    ("kochDETweak", "transf_koch_de_tweak"),
    ("kochCpixelInject", "transf_koch_cpixel_inject"),
    ("kochAnisotropic", "transf_koch_anisotropic"),
    ("kochSphereFold", "transf_koch_sphere_fold"),
    ("kochEdgeSoftness", "transf_koch_edge_softness"),
]


def make_koch_block_cpp():
    """Generate the C++ Koch extensions block."""
    lines = []
    lines.append("\t// --- Koch Extensions (20 parameters) ---")
    lines.append("\t{")
    lines.append("\t\tdouble kFoldAngle = fractal->transformCommon.kochFoldAngle;")
    lines.append("\t\tdouble kFoldAngleFreq = fractal->transformCommon.kochFoldAngleFreq;")
    lines.append("\t\tdouble kScaleOsc = fractal->transformCommon.kochScaleOsc;")
    lines.append("\t\tdouble kScaleOscFreq = fractal->transformCommon.kochScaleOscFreq;")
    lines.append("\t\tdouble kOffOscX = fractal->transformCommon.kochOffsetOscX;")
    lines.append("\t\tdouble kOffOscY = fractal->transformCommon.kochOffsetOscY;")
    lines.append("\t\tdouble kOffOscZ = fractal->transformCommon.kochOffsetOscZ;")
    lines.append("\t\tdouble kOffOscFreq = fractal->transformCommon.kochOffsetOscFreq;")
    lines.append("\t\tdouble kPreRot = fractal->transformCommon.kochPreRotAngle;")
    lines.append("\t\tdouble kPostRot = fractal->transformCommon.kochPostRotAngle;")
    lines.append("\t\tdouble kYOffWarp = fractal->transformCommon.kochYOffWarp;")
    lines.append("\t\tdouble kTwistZ = fractal->transformCommon.kochTwistZ;")
    lines.append("\t\tdouble kRadDist = fractal->transformCommon.kochRadialDistort;")
    lines.append("\t\tdouble kTurb = fractal->transformCommon.kochTurbulence;")
    lines.append("\t\tdouble kGradColor = fractal->transformCommon.kochGradientColor;")
    lines.append("\t\tdouble kDETweak = fractal->transformCommon.kochDETweak;")
    lines.append("\t\tdouble kCpixel = fractal->transformCommon.kochCpixelInject;")
    lines.append("\t\tdouble kAniso = fractal->transformCommon.kochAnisotropic;")
    lines.append("\t\tdouble kSphere = fractal->transformCommon.kochSphereFold;")
    lines.append("\t\tdouble kEdgeSoft = fractal->transformCommon.kochEdgeSoftness;")
    lines.append("")
    lines.append("\t\t// 1. Fold angle oscillation")
    lines.append("\t\tif (kFoldAngle != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble angle = kFoldAngle * sin(aux.i * kFoldAngleFreq * 0.5);")
    lines.append("\t\t\tdouble cosA = cos(angle);")
    lines.append("\t\t\tdouble sinA = sin(angle);")
    lines.append("\t\t\tdouble nx = z.x * cosA - z.y * sinA;")
    lines.append("\t\t\tdouble ny = z.x * sinA + z.y * cosA;")
    lines.append("\t\t\tz.x = nx;")
    lines.append("\t\t\tz.y = ny;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 2-3. Scale oscillation")
    lines.append("\t\tif (kScaleOsc != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble sOsc = 1.0 + kScaleOsc * sin(aux.i * kScaleOscFreq * 0.5);")
    lines.append("\t\t\tz *= sOsc;")
    lines.append("\t\t\taux.DE *= fabs(sOsc);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 4-7. Offset oscillation (per axis)")
    lines.append("\t\tif (kOffOscX != 0.0 || kOffOscY != 0.0 || kOffOscZ != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble oPhase = aux.i * kOffOscFreq * 0.5;")
    lines.append("\t\t\tz.x += kOffOscX * sin(oPhase);")
    lines.append("\t\t\tz.y += kOffOscY * sin(oPhase * 1.3);")
    lines.append("\t\t\tz.z += kOffOscZ * sin(oPhase * 0.7);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 8. Pre-rotation")
    lines.append("\t\tif (kPreRot != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble a = kPreRot * M_PI / 180.0 * aux.i;")
    lines.append("\t\t\tdouble ca = cos(a); double sa = sin(a);")
    lines.append("\t\t\tdouble px = z.x * ca - z.z * sa;")
    lines.append("\t\t\tdouble pz = z.x * sa + z.z * ca;")
    lines.append("\t\t\tz.x = px; z.z = pz;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 9. Post-rotation")
    lines.append("\t\tif (kPostRot != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble a = kPostRot * M_PI / 180.0;")
    lines.append("\t\t\tdouble ca = cos(a); double sa = sin(a);")
    lines.append("\t\t\tdouble py = z.y * ca - z.z * sa;")
    lines.append("\t\t\tdouble pzz = z.y * sa + z.z * ca;")
    lines.append("\t\t\tz.y = py; z.z = pzz;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 10. YOff warp")
    lines.append("\t\tif (kYOffWarp != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tz.y += kYOffWarp * sin(z.x * 3.0 + aux.i);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 11. Twist Z")
    lines.append("\t\tif (kTwistZ != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble tw = kTwistZ * M_PI / 180.0 * z.z;")
    lines.append("\t\t\tdouble ct = cos(tw); double st = sin(tw);")
    lines.append("\t\t\tdouble tx = z.x * ct - z.y * st;")
    lines.append("\t\t\tdouble ty = z.x * st + z.y * ct;")
    lines.append("\t\t\tz.x = tx; z.y = ty;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 12. Radial distortion")
    lines.append("\t\tif (kRadDist != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble r = z.Length();")
    lines.append("\t\t\tif (r > 1e-15)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tdouble distort = 1.0 + kRadDist * sin(r * 5.0);")
    lines.append("\t\t\t\tz *= distort;")
    lines.append("\t\t\t\taux.DE *= fabs(distort);")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 13. Turbulence")
    lines.append("\t\tif (kTurb != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble hx = sin(z.x * 12.9898 + z.y * 78.233) * 43758.5453;")
    lines.append("\t\t\thx = hx - floor(hx);")
    lines.append("\t\t\tdouble hy = sin(z.y * 12.9898 + z.z * 78.233) * 43758.5453;")
    lines.append("\t\t\thy = hy - floor(hy);")
    lines.append("\t\t\tdouble hz = sin(z.z * 12.9898 + z.x * 78.233) * 43758.5453;")
    lines.append("\t\t\thz = hz - floor(hz);")
    lines.append("\t\t\tz.x += (hx - 0.5) * kTurb;")
    lines.append("\t\t\tz.y += (hy - 0.5) * kTurb;")
    lines.append("\t\t\tz.z += (hz - 0.5) * kTurb;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 14. Gradient color")
    lines.append("\t\tif (kGradColor != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\taux.color += kGradColor * z.Length();")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 15. DE tweak")
    lines.append("\t\tif (kDETweak != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\taux.DE += kDETweak;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 16. C-pixel injection")
    lines.append("\t\tif (kCpixel != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tz += aux.const_c * kCpixel;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 17. Anisotropic scaling")
    lines.append("\t\tif (kAniso != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tz.z *= (1.0 + kAniso);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 18. Sphere fold")
    lines.append("\t\tif (kSphere != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble r2 = z.Dot(z);")
    lines.append("\t\t\tdouble minR2 = 0.25;")
    lines.append("\t\t\tdouble fixedR2 = 1.0;")
    lines.append("\t\t\tif (r2 < minR2)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tdouble t = fixedR2 / minR2;")
    lines.append("\t\t\t\tz *= t * kSphere;")
    lines.append("\t\t\t\taux.DE *= fabs(t * kSphere);")
    lines.append("\t\t\t}")
    lines.append("\t\t\telse if (r2 < fixedR2)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tdouble t = fixedR2 / r2;")
    lines.append("\t\t\t\tz *= t * kSphere;")
    lines.append("\t\t\t\taux.DE *= fabs(t * kSphere);")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 19. Edge softness")
    lines.append("\t\tif (kEdgeSoft != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble r = z.Length();")
    lines.append("\t\t\tif (r > 1e-15)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tdouble soft = r / (r + kEdgeSoft);")
    lines.append("\t\t\t\tz *= soft;")
    lines.append("\t\t\t\taux.DE *= soft;")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("\t}")
    lines.append("")
    return "\n".join(lines) + "\n"


def make_koch_block_cl():
    """Generate the OpenCL Koch extensions block."""
    lines = []
    lines.append("\t// --- Koch Extensions (20 parameters) ---")
    lines.append("\t{")
    lines.append("\t\tREAL kFoldAngle = fractal->transformCommon.kochFoldAngle;")
    lines.append("\t\tREAL kFoldAngleFreq = fractal->transformCommon.kochFoldAngleFreq;")
    lines.append("\t\tREAL kScaleOsc = fractal->transformCommon.kochScaleOsc;")
    lines.append("\t\tREAL kScaleOscFreq = fractal->transformCommon.kochScaleOscFreq;")
    lines.append("\t\tREAL kOffOscX = fractal->transformCommon.kochOffsetOscX;")
    lines.append("\t\tREAL kOffOscY = fractal->transformCommon.kochOffsetOscY;")
    lines.append("\t\tREAL kOffOscZ = fractal->transformCommon.kochOffsetOscZ;")
    lines.append("\t\tREAL kOffOscFreq = fractal->transformCommon.kochOffsetOscFreq;")
    lines.append("\t\tREAL kPreRot = fractal->transformCommon.kochPreRotAngle;")
    lines.append("\t\tREAL kPostRot = fractal->transformCommon.kochPostRotAngle;")
    lines.append("\t\tREAL kYOffWarp = fractal->transformCommon.kochYOffWarp;")
    lines.append("\t\tREAL kTwistZ = fractal->transformCommon.kochTwistZ;")
    lines.append("\t\tREAL kRadDist = fractal->transformCommon.kochRadialDistort;")
    lines.append("\t\tREAL kTurb = fractal->transformCommon.kochTurbulence;")
    lines.append("\t\tREAL kGradColor = fractal->transformCommon.kochGradientColor;")
    lines.append("\t\tREAL kDETweak = fractal->transformCommon.kochDETweak;")
    lines.append("\t\tREAL kCpixel = fractal->transformCommon.kochCpixelInject;")
    lines.append("\t\tREAL kAniso = fractal->transformCommon.kochAnisotropic;")
    lines.append("\t\tREAL kSphere = fractal->transformCommon.kochSphereFold;")
    lines.append("\t\tREAL kEdgeSoft = fractal->transformCommon.kochEdgeSoftness;")
    lines.append("")
    lines.append("\t\t// 1. Fold angle oscillation")
    lines.append("\t\tif (kFoldAngle != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL angle = kFoldAngle * native_sin(aux->i * kFoldAngleFreq * 0.5f);")
    lines.append("\t\t\tREAL cosA = native_cos(angle);")
    lines.append("\t\t\tREAL sinA = native_sin(angle);")
    lines.append("\t\t\tREAL nx = z.x * cosA - z.y * sinA;")
    lines.append("\t\t\tREAL ny = z.x * sinA + z.y * cosA;")
    lines.append("\t\t\tz.x = nx;")
    lines.append("\t\t\tz.y = ny;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 2-3. Scale oscillation")
    lines.append("\t\tif (kScaleOsc != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL sOsc = 1.0f + kScaleOsc * native_sin(aux->i * kScaleOscFreq * 0.5f);")
    lines.append("\t\t\tz *= sOsc;")
    lines.append("\t\t\taux->DE *= fabs(sOsc);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 4-7. Offset oscillation (per axis)")
    lines.append("\t\tif (kOffOscX != 0.0f || kOffOscY != 0.0f || kOffOscZ != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL oPhase = aux->i * kOffOscFreq * 0.5f;")
    lines.append("\t\t\tz.x += kOffOscX * native_sin(oPhase);")
    lines.append("\t\t\tz.y += kOffOscY * native_sin(oPhase * 1.3f);")
    lines.append("\t\t\tz.z += kOffOscZ * native_sin(oPhase * 0.7f);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 8. Pre-rotation")
    lines.append("\t\tif (kPreRot != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL a = kPreRot * M_PI_F / 180.0f * aux->i;")
    lines.append("\t\t\tREAL ca = native_cos(a); REAL sa = native_sin(a);")
    lines.append("\t\t\tREAL px = z.x * ca - z.z * sa;")
    lines.append("\t\t\tREAL pz = z.x * sa + z.z * ca;")
    lines.append("\t\t\tz.x = px; z.z = pz;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 9. Post-rotation")
    lines.append("\t\tif (kPostRot != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL a = kPostRot * M_PI_F / 180.0f;")
    lines.append("\t\t\tREAL ca = native_cos(a); REAL sa = native_sin(a);")
    lines.append("\t\t\tREAL py = z.y * ca - z.z * sa;")
    lines.append("\t\t\tREAL pzz = z.y * sa + z.z * ca;")
    lines.append("\t\t\tz.y = py; z.z = pzz;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 10. YOff warp")
    lines.append("\t\tif (kYOffWarp != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tz.y += kYOffWarp * native_sin(z.x * 3.0f + aux->i);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 11. Twist Z")
    lines.append("\t\tif (kTwistZ != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL tw = kTwistZ * M_PI_F / 180.0f * z.z;")
    lines.append("\t\t\tREAL ct = native_cos(tw); REAL st = native_sin(tw);")
    lines.append("\t\t\tREAL tx = z.x * ct - z.y * st;")
    lines.append("\t\t\tREAL ty = z.x * st + z.y * ct;")
    lines.append("\t\t\tz.x = tx; z.y = ty;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 12. Radial distortion")
    lines.append("\t\tif (kRadDist != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL r = length(z);")
    lines.append("\t\t\tif (r > 1e-15f)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tREAL distort = 1.0f + kRadDist * native_sin(r * 5.0f);")
    lines.append("\t\t\t\tz *= distort;")
    lines.append("\t\t\t\taux->DE *= fabs(distort);")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 13. Turbulence")
    lines.append("\t\tif (kTurb != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL hx = native_sin(z.x * 12.9898f + z.y * 78.233f) * 43758.5453f;")
    lines.append("\t\t\thx = hx - floor(hx);")
    lines.append("\t\t\tREAL hy = native_sin(z.y * 12.9898f + z.z * 78.233f) * 43758.5453f;")
    lines.append("\t\t\thy = hy - floor(hy);")
    lines.append("\t\t\tREAL hz = native_sin(z.z * 12.9898f + z.x * 78.233f) * 43758.5453f;")
    lines.append("\t\t\thz = hz - floor(hz);")
    lines.append("\t\t\tz.x += (hx - 0.5f) * kTurb;")
    lines.append("\t\t\tz.y += (hy - 0.5f) * kTurb;")
    lines.append("\t\t\tz.z += (hz - 0.5f) * kTurb;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 14. Gradient color")
    lines.append("\t\tif (kGradColor != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\taux->color += kGradColor * length(z);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 15. DE tweak")
    lines.append("\t\tif (kDETweak != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\taux->DE += kDETweak;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 16. C-pixel injection")
    lines.append("\t\tif (kCpixel != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tz += aux->const_c * kCpixel;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 17. Anisotropic scaling")
    lines.append("\t\tif (kAniso != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tz.z *= (1.0f + kAniso);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 18. Sphere fold")
    lines.append("\t\tif (kSphere != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL r2 = dot(z, z);")
    lines.append("\t\t\tREAL minR2 = 0.25f;")
    lines.append("\t\t\tREAL fixedR2 = 1.0f;")
    lines.append("\t\t\tif (r2 < minR2)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tREAL t = fixedR2 / minR2;")
    lines.append("\t\t\t\tz *= t * kSphere;")
    lines.append("\t\t\t\taux->DE *= fabs(t * kSphere);")
    lines.append("\t\t\t}")
    lines.append("\t\t\telse if (r2 < fixedR2)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tREAL t = fixedR2 / r2;")
    lines.append("\t\t\t\tz *= t * kSphere;")
    lines.append("\t\t\t\taux->DE *= fabs(t * kSphere);")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 19. Edge softness")
    lines.append("\t\tif (kEdgeSoft != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL r = length(z);")
    lines.append("\t\t\tif (r > 1e-15f)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tREAL soft = r / (r + kEdgeSoft);")
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

    if "Koch Extensions" in content:
        print(f"  SKIP (already has Koch Extensions): {filepath}")
        return False

    if MARKER not in content:
        print(f"  WARN (no marker): {filepath}")
        return False

    content = content.replace(MARKER, block + "\t" + MARKER)
    with open(filepath, "w") as f:
        f.write(content)
    return True


def make_ui_groupbox():
    """Generate the UI XML groupbox for Koch extensions."""
    lines = []
    lines.append('   <widget class="QGroupBox" name="groupCheck_koch_extensions">')
    lines.append('    <property name="title">')
    lines.append('     <string>Koch Extensions</string>')
    lines.append('    </property>')
    lines.append('    <property name="checkable">')
    lines.append('     <bool>true</bool>')
    lines.append('    </property>')
    lines.append('    <property name="checked">')
    lines.append('     <bool>false</bool>')
    lines.append('    </property>')
    lines.append('    <layout class="QGridLayout">')

    param_labels = [
        ("transf_koch_fold_angle", "Fold Angle:"),
        ("transf_koch_fold_angle_freq", "Fold Angle Freq:"),
        ("transf_koch_scale_osc", "Scale Osc Amp:"),
        ("transf_koch_scale_osc_freq", "Scale Osc Freq:"),
        ("transf_koch_offset_osc_x", "Offset Osc X:"),
        ("transf_koch_offset_osc_y", "Offset Osc Y:"),
        ("transf_koch_offset_osc_z", "Offset Osc Z:"),
        ("transf_koch_offset_osc_freq", "Offset Osc Freq:"),
        ("transf_koch_pre_rot_angle", "Pre-Rotation:"),
        ("transf_koch_post_rot_angle", "Post-Rotation:"),
        ("transf_koch_yoff_warp", "YOff Warp:"),
        ("transf_koch_twist_z", "Twist Z:"),
        ("transf_koch_radial_distort", "Radial Distort:"),
        ("transf_koch_turbulence", "Turbulence:"),
        ("transf_koch_gradient_color", "Gradient Color:"),
        ("transf_koch_de_tweak", "DE Tweak:"),
        ("transf_koch_cpixel_inject", "C-Pixel Inject:"),
        ("transf_koch_anisotropic", "Anisotropic:"),
        ("transf_koch_sphere_fold", "Sphere Fold:"),
        ("transf_koch_edge_softness", "Edge Softness:"),
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
    """Insert Koch extensions groupbox into UI file."""
    with open(filepath, "r") as f:
        content = f.read()

    if "koch_extensions" in content:
        print(f"  SKIP UI (already has Koch extensions): {filepath}")
        return False

    # Insert before " </widget>\n <customwidgets>" or before " </widget>\n</ui>"
    insert_marker = " </widget>\n <customwidgets>"
    if insert_marker not in content:
        insert_marker = " </widget>\n</ui>"
        if insert_marker not in content:
            print(f"  WARN UI (no insert point): {filepath}")
            return False

    groupbox = make_ui_groupbox()
    # Insert groupbox inside the main widget, before closing
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
        print(f"  XML ERROR in {filepath}: {e}")
        return False


def main():
    print("=== Koch Extensions Upgrade Script ===")
    print()

    # Find Koch formula files
    cpp_files = sorted(glob.glob(os.path.join(CPP_DIR, "fractal_koch*.cpp")))
    cl_files = sorted(glob.glob(os.path.join(CL_DIR, "koch*.cl")))
    ui_files = sorted(glob.glob(os.path.join(UI_DIR, "koch*.ui")))

    print(f"Found {len(cpp_files)} CPP, {len(cl_files)} CL, {len(ui_files)} UI files")
    print()

    # Generate blocks
    cpp_block = make_koch_block_cpp()
    cl_block = make_koch_block_cl()

    # Update CPP files
    print("--- Updating CPP files ---")
    cpp_ok = 0
    for f in cpp_files:
        if update_formula_file(f, cpp_block):
            cpp_ok += 1
            print(f"  OK: {os.path.basename(f)}")
    print(f"  Updated {cpp_ok}/{len(cpp_files)} CPP files")
    print()

    # Update CL files
    print("--- Updating CL files ---")
    cl_ok = 0
    for f in cl_files:
        if update_formula_file(f, cl_block):
            cl_ok += 1
            print(f"  OK: {os.path.basename(f)}")
    print(f"  Updated {cl_ok}/{len(cl_files)} CL files")
    print()

    # Update UI files
    print("--- Updating UI files ---")
    ui_ok = 0
    for f in ui_files:
        if update_ui_file(f):
            ui_ok += 1
            print(f"  OK: {os.path.basename(f)}")
    print(f"  Updated {ui_ok}/{len(ui_files)} UI files")
    print()

    # Validate XML
    print("--- Validating XML ---")
    xml_errors = 0
    for f in ui_files:
        if not validate_xml(f):
            xml_errors += 1
    print(f"  {len(ui_files) - xml_errors}/{len(ui_files)} UI files valid XML")
    if xml_errors > 0:
        print(f"  WARNING: {xml_errors} files have XML errors!")
    print()

    print("=== Done ===")
    print(f"Total: {cpp_ok} CPP + {cl_ok} CL + {ui_ok} UI files updated")


if __name__ == "__main__":
    main()
