#!/usr/bin/env python3
"""
Upgrade script: Add 20 Julia-specific parameters to all 199 Julia formula variants.
"""
import glob
import os
import xml.etree.ElementTree as ET

BASE = "/home/ubuntu/repos/mandelbulber2-private/mandelbulber2"
CPP_DIR = os.path.join(BASE, "formula", "definition")
CL_DIR = os.path.join(BASE, "formula", "opencl")
UI_DIR = os.path.join(BASE, "formula", "ui")

MARKER = "// GPU bypass: skip if all multipliers disabled"


def find_julia_files(directory, ext):
    """Find all Julia files in directory."""
    if ext == "cpp":
        pattern = os.path.join(directory, "fractal_*julia*.cpp")
    elif ext == "cl":
        pattern = os.path.join(directory, "*julia*.cl")
    elif ext == "ui":
        pattern = os.path.join(directory, "*julia*.ui")
    return sorted(glob.glob(pattern))


def make_jl_block_cpp():
    """Generate the C++ Julia extensions block."""
    lines = []
    lines.append("\t// --- Julia Extensions (20 parameters) ---")
    lines.append("\t{")
    lines.append("\t\tdouble jlPwOsc = fractal->transformCommon.jlPowerOsc;")
    lines.append("\t\tdouble jlPwFreq = fractal->transformCommon.jlPowerOscFreq;")
    lines.append("\t\tdouble jlThWarp = fractal->transformCommon.jlThetaWarp;")
    lines.append("\t\tdouble jlPhWarp = fractal->transformCommon.jlPhiWarp;")
    lines.append("\t\tdouble jlRadStr = fractal->transformCommon.jlRadialStretch;")
    lines.append("\t\tdouble jlPreXY = fractal->transformCommon.jlPreRotXY;")
    lines.append("\t\tdouble jlPreXZ = fractal->transformCommon.jlPreRotXZ;")
    lines.append("\t\tdouble jlPostYZ = fractal->transformCommon.jlPostRotYZ;")
    lines.append("\t\tdouble jlTwZ = fractal->transformCommon.jlTwistZ;")
    lines.append("\t\tdouble jlScOsc = fractal->transformCommon.jlScaleOsc;")
    lines.append("\t\tdouble jlScFreq = fractal->transformCommon.jlScaleOscFreq;")
    lines.append("\t\tdouble jlOffOsc = fractal->transformCommon.jlOffsetOsc;")
    lines.append("\t\tdouble jlOffFreq = fractal->transformCommon.jlOffsetOscFreq;")
    lines.append("\t\tdouble jlRadDist = fractal->transformCommon.jlRadialDistort;")
    lines.append("\t\tdouble jlTurb = fractal->transformCommon.jlTurbulence;")
    lines.append("\t\tdouble jlGradCol = fractal->transformCommon.jlGradientColor;")
    lines.append("\t\tdouble jlDETw = fractal->transformCommon.jlDETweak;")
    lines.append("\t\tdouble jlCpix = fractal->transformCommon.jlCpixelScale;")
    lines.append("\t\tdouble jlSphere = fractal->transformCommon.jlSphereFold;")
    lines.append("\t\tdouble jlEdgeSoft = fractal->transformCommon.jlEdgeSoftness;")
    lines.append("")
    lines.append("\t\t// 1-2. Power oscillation")
    lines.append("\t\tif (jlPwOsc != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble pOsc = 1.0 + jlPwOsc * sin(aux.i * jlPwFreq * 0.5);")
    lines.append("\t\t\tz *= pOsc;")
    lines.append("\t\t\taux.DE *= fabs(pOsc);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 3. Theta warp")
    lines.append("\t\tif (jlThWarp != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble r = z.Length();")
    lines.append("\t\t\tif (r > 1e-15)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tdouble th = acos(z.z / r);")
    lines.append("\t\t\t\tth += jlThWarp * sin(aux.i * 1.5);")
    lines.append("\t\t\t\tdouble ph = atan2(z.y, z.x);")
    lines.append("\t\t\t\tz.x = r * sin(th) * cos(ph);")
    lines.append("\t\t\t\tz.y = r * sin(th) * sin(ph);")
    lines.append("\t\t\t\tz.z = r * cos(th);")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 4. Phi warp")
    lines.append("\t\tif (jlPhWarp != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble r = z.Length();")
    lines.append("\t\t\tif (r > 1e-15)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tdouble th = acos(z.z / r);")
    lines.append("\t\t\t\tdouble ph = atan2(z.y, z.x);")
    lines.append("\t\t\t\tph += jlPhWarp * sin(aux.i * 1.3);")
    lines.append("\t\t\t\tz.x = r * sin(th) * cos(ph);")
    lines.append("\t\t\t\tz.y = r * sin(th) * sin(ph);")
    lines.append("\t\t\t\tz.z = r * cos(th);")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 5. Radial stretch")
    lines.append("\t\tif (jlRadStr != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble r = z.Length();")
    lines.append("\t\t\tif (r > 1e-15)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tdouble stretch = 1.0 + jlRadStr * (r - 1.0);")
    lines.append("\t\t\t\tz *= stretch / r * r;")
    lines.append("\t\t\t\taux.DE *= fabs(stretch);")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 6. Pre-rotation XY")
    lines.append("\t\tif (jlPreXY != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble a = jlPreXY * M_PI / 180.0 * aux.i;")
    lines.append("\t\t\tdouble ca = cos(a); double sa = sin(a);")
    lines.append("\t\t\tdouble px = z.x * ca - z.y * sa;")
    lines.append("\t\t\tdouble py = z.x * sa + z.y * ca;")
    lines.append("\t\t\tz.x = px; z.y = py;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 7. Pre-rotation XZ")
    lines.append("\t\tif (jlPreXZ != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble a = jlPreXZ * M_PI / 180.0 * aux.i;")
    lines.append("\t\t\tdouble ca = cos(a); double sa = sin(a);")
    lines.append("\t\t\tdouble px = z.x * ca - z.z * sa;")
    lines.append("\t\t\tdouble pz = z.x * sa + z.z * ca;")
    lines.append("\t\t\tz.x = px; z.z = pz;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 8. Post-rotation YZ")
    lines.append("\t\tif (jlPostYZ != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble a = jlPostYZ * M_PI / 180.0;")
    lines.append("\t\t\tdouble ca = cos(a); double sa = sin(a);")
    lines.append("\t\t\tdouble py = z.y * ca - z.z * sa;")
    lines.append("\t\t\tdouble pz = z.y * sa + z.z * ca;")
    lines.append("\t\t\tz.y = py; z.z = pz;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 9. Twist Z")
    lines.append("\t\tif (jlTwZ != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble tw = jlTwZ * M_PI / 180.0 * z.z;")
    lines.append("\t\t\tdouble ct = cos(tw); double st = sin(tw);")
    lines.append("\t\t\tdouble tx = z.x * ct - z.y * st;")
    lines.append("\t\t\tdouble ty = z.x * st + z.y * ct;")
    lines.append("\t\t\tz.x = tx; z.y = ty;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 10-11. Scale oscillation")
    lines.append("\t\tif (jlScOsc != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble sOsc = 1.0 + jlScOsc * sin(aux.i * jlScFreq * 0.5);")
    lines.append("\t\t\tz *= sOsc;")
    lines.append("\t\t\taux.DE *= fabs(sOsc);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 12-13. Offset oscillation")
    lines.append("\t\tif (jlOffOsc != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble oOsc = jlOffOsc * sin(aux.i * jlOffFreq * 0.5);")
    lines.append("\t\t\tz.x += oOsc;")
    lines.append("\t\t\tz.y += oOsc * 0.7;")
    lines.append("\t\t\tz.z += oOsc * 0.5;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 14. Radial distortion")
    lines.append("\t\tif (jlRadDist != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble r = z.Length();")
    lines.append("\t\t\tif (r > 1e-15)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tdouble distort = 1.0 + jlRadDist * sin(r * 4.0);")
    lines.append("\t\t\t\tz *= distort;")
    lines.append("\t\t\t\taux.DE *= fabs(distort);")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 15. Turbulence")
    lines.append("\t\tif (jlTurb != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble hx = sin(z.x * 12.9898 + z.y * 78.233) * 43758.5453;")
    lines.append("\t\t\thx = hx - floor(hx);")
    lines.append("\t\t\tdouble hy = sin(z.y * 12.9898 + z.z * 78.233) * 43758.5453;")
    lines.append("\t\t\thy = hy - floor(hy);")
    lines.append("\t\t\tdouble hz = sin(z.z * 12.9898 + z.x * 78.233) * 43758.5453;")
    lines.append("\t\t\thz = hz - floor(hz);")
    lines.append("\t\t\tz.x += (hx - 0.5) * jlTurb;")
    lines.append("\t\t\tz.y += (hy - 0.5) * jlTurb;")
    lines.append("\t\t\tz.z += (hz - 0.5) * jlTurb;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 16. Gradient color")
    lines.append("\t\tif (jlGradCol != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\taux.color += jlGradCol * z.Length();")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 17. DE tweak")
    lines.append("\t\tif (jlDETw != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\taux.DE += jlDETw;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 18. C-pixel scale")
    lines.append("\t\tif (jlCpix != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tz += aux.const_c * jlCpix;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 19. Sphere fold")
    lines.append("\t\tif (jlSphere != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble r2 = z.Dot(z);")
    lines.append("\t\t\tdouble minR2 = 0.25;")
    lines.append("\t\t\tdouble fixedR2 = 1.0;")
    lines.append("\t\t\tif (r2 < minR2)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tdouble t = fixedR2 / minR2;")
    lines.append("\t\t\t\tz *= t * jlSphere;")
    lines.append("\t\t\t\taux.DE *= fabs(t * jlSphere);")
    lines.append("\t\t\t}")
    lines.append("\t\t\telse if (r2 < fixedR2)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tdouble t = fixedR2 / r2;")
    lines.append("\t\t\t\tz *= t * jlSphere;")
    lines.append("\t\t\t\taux.DE *= fabs(t * jlSphere);")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 20. Edge softness")
    lines.append("\t\tif (jlEdgeSoft != 0.0)")
    lines.append("\t\t{")
    lines.append("\t\t\tdouble r = z.Length();")
    lines.append("\t\t\tif (r > 1e-15)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tdouble soft = r / (r + jlEdgeSoft);")
    lines.append("\t\t\t\tz *= soft;")
    lines.append("\t\t\t\taux.DE *= soft;")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("\t}")
    lines.append("")
    return "\n".join(lines) + "\n"


def make_jl_block_cl():
    """Generate the OpenCL Julia extensions block."""
    lines = []
    lines.append("\t// --- Julia Extensions (20 parameters) ---")
    lines.append("\t{")
    lines.append("\t\tREAL jlPwOsc = fractal->transformCommon.jlPowerOsc;")
    lines.append("\t\tREAL jlPwFreq = fractal->transformCommon.jlPowerOscFreq;")
    lines.append("\t\tREAL jlThWarp = fractal->transformCommon.jlThetaWarp;")
    lines.append("\t\tREAL jlPhWarp = fractal->transformCommon.jlPhiWarp;")
    lines.append("\t\tREAL jlRadStr = fractal->transformCommon.jlRadialStretch;")
    lines.append("\t\tREAL jlPreXY = fractal->transformCommon.jlPreRotXY;")
    lines.append("\t\tREAL jlPreXZ = fractal->transformCommon.jlPreRotXZ;")
    lines.append("\t\tREAL jlPostYZ = fractal->transformCommon.jlPostRotYZ;")
    lines.append("\t\tREAL jlTwZ = fractal->transformCommon.jlTwistZ;")
    lines.append("\t\tREAL jlScOsc = fractal->transformCommon.jlScaleOsc;")
    lines.append("\t\tREAL jlScFreq = fractal->transformCommon.jlScaleOscFreq;")
    lines.append("\t\tREAL jlOffOsc = fractal->transformCommon.jlOffsetOsc;")
    lines.append("\t\tREAL jlOffFreq = fractal->transformCommon.jlOffsetOscFreq;")
    lines.append("\t\tREAL jlRadDist = fractal->transformCommon.jlRadialDistort;")
    lines.append("\t\tREAL jlTurb = fractal->transformCommon.jlTurbulence;")
    lines.append("\t\tREAL jlGradCol = fractal->transformCommon.jlGradientColor;")
    lines.append("\t\tREAL jlDETw = fractal->transformCommon.jlDETweak;")
    lines.append("\t\tREAL jlCpix = fractal->transformCommon.jlCpixelScale;")
    lines.append("\t\tREAL jlSphere = fractal->transformCommon.jlSphereFold;")
    lines.append("\t\tREAL jlEdgeSoft = fractal->transformCommon.jlEdgeSoftness;")
    lines.append("")
    lines.append("\t\t// 1-2. Power oscillation")
    lines.append("\t\tif (jlPwOsc != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL pOsc = 1.0f + jlPwOsc * native_sin(aux->i * jlPwFreq * 0.5f);")
    lines.append("\t\t\tz *= pOsc;")
    lines.append("\t\t\taux->DE *= fabs(pOsc);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 3. Theta warp")
    lines.append("\t\tif (jlThWarp != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL r = length(z);")
    lines.append("\t\t\tif (r > 1e-15f)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tREAL th = acos(z.z / r);")
    lines.append("\t\t\t\tth += jlThWarp * native_sin(aux->i * 1.5f);")
    lines.append("\t\t\t\tREAL ph = atan2(z.y, z.x);")
    lines.append("\t\t\t\tz.x = r * native_sin(th) * native_cos(ph);")
    lines.append("\t\t\t\tz.y = r * native_sin(th) * native_sin(ph);")
    lines.append("\t\t\t\tz.z = r * native_cos(th);")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 4. Phi warp")
    lines.append("\t\tif (jlPhWarp != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL r = length(z);")
    lines.append("\t\t\tif (r > 1e-15f)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tREAL th = acos(z.z / r);")
    lines.append("\t\t\t\tREAL ph = atan2(z.y, z.x);")
    lines.append("\t\t\t\tph += jlPhWarp * native_sin(aux->i * 1.3f);")
    lines.append("\t\t\t\tz.x = r * native_sin(th) * native_cos(ph);")
    lines.append("\t\t\t\tz.y = r * native_sin(th) * native_sin(ph);")
    lines.append("\t\t\t\tz.z = r * native_cos(th);")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 5. Radial stretch")
    lines.append("\t\tif (jlRadStr != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL r = length(z);")
    lines.append("\t\t\tif (r > 1e-15f)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tREAL stretch = 1.0f + jlRadStr * (r - 1.0f);")
    lines.append("\t\t\t\tz *= stretch / r * r;")
    lines.append("\t\t\t\taux->DE *= fabs(stretch);")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 6. Pre-rotation XY")
    lines.append("\t\tif (jlPreXY != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL a = jlPreXY * M_PI_F / 180.0f * aux->i;")
    lines.append("\t\t\tREAL ca = native_cos(a); REAL sa = native_sin(a);")
    lines.append("\t\t\tREAL px = z.x * ca - z.y * sa;")
    lines.append("\t\t\tREAL py = z.x * sa + z.y * ca;")
    lines.append("\t\t\tz.x = px; z.y = py;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 7. Pre-rotation XZ")
    lines.append("\t\tif (jlPreXZ != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL a = jlPreXZ * M_PI_F / 180.0f * aux->i;")
    lines.append("\t\t\tREAL ca = native_cos(a); REAL sa = native_sin(a);")
    lines.append("\t\t\tREAL px = z.x * ca - z.z * sa;")
    lines.append("\t\t\tREAL pz = z.x * sa + z.z * ca;")
    lines.append("\t\t\tz.x = px; z.z = pz;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 8. Post-rotation YZ")
    lines.append("\t\tif (jlPostYZ != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL a = jlPostYZ * M_PI_F / 180.0f;")
    lines.append("\t\t\tREAL ca = native_cos(a); REAL sa = native_sin(a);")
    lines.append("\t\t\tREAL py = z.y * ca - z.z * sa;")
    lines.append("\t\t\tREAL pz = z.y * sa + z.z * ca;")
    lines.append("\t\t\tz.y = py; z.z = pz;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 9. Twist Z")
    lines.append("\t\tif (jlTwZ != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL tw = jlTwZ * M_PI_F / 180.0f * z.z;")
    lines.append("\t\t\tREAL ct = native_cos(tw); REAL st = native_sin(tw);")
    lines.append("\t\t\tREAL tx = z.x * ct - z.y * st;")
    lines.append("\t\t\tREAL ty = z.x * st + z.y * ct;")
    lines.append("\t\t\tz.x = tx; z.y = ty;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 10-11. Scale oscillation")
    lines.append("\t\tif (jlScOsc != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL sOsc = 1.0f + jlScOsc * native_sin(aux->i * jlScFreq * 0.5f);")
    lines.append("\t\t\tz *= sOsc;")
    lines.append("\t\t\taux->DE *= fabs(sOsc);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 12-13. Offset oscillation")
    lines.append("\t\tif (jlOffOsc != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL oOsc = jlOffOsc * native_sin(aux->i * jlOffFreq * 0.5f);")
    lines.append("\t\t\tz.x += oOsc;")
    lines.append("\t\t\tz.y += oOsc * 0.7f;")
    lines.append("\t\t\tz.z += oOsc * 0.5f;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 14. Radial distortion")
    lines.append("\t\tif (jlRadDist != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL r = length(z);")
    lines.append("\t\t\tif (r > 1e-15f)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tREAL distort = 1.0f + jlRadDist * native_sin(r * 4.0f);")
    lines.append("\t\t\t\tz *= distort;")
    lines.append("\t\t\t\taux->DE *= fabs(distort);")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 15. Turbulence")
    lines.append("\t\tif (jlTurb != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL hx = native_sin(z.x * 12.9898f + z.y * 78.233f) * 43758.5453f;")
    lines.append("\t\t\thx = hx - floor(hx);")
    lines.append("\t\t\tREAL hy = native_sin(z.y * 12.9898f + z.z * 78.233f) * 43758.5453f;")
    lines.append("\t\t\thy = hy - floor(hy);")
    lines.append("\t\t\tREAL hz = native_sin(z.z * 12.9898f + z.x * 78.233f) * 43758.5453f;")
    lines.append("\t\t\thz = hz - floor(hz);")
    lines.append("\t\t\tz.x += (hx - 0.5f) * jlTurb;")
    lines.append("\t\t\tz.y += (hy - 0.5f) * jlTurb;")
    lines.append("\t\t\tz.z += (hz - 0.5f) * jlTurb;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 16. Gradient color")
    lines.append("\t\tif (jlGradCol != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\taux->color += jlGradCol * length(z);")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 17. DE tweak")
    lines.append("\t\tif (jlDETw != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\taux->DE += jlDETw;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 18. C-pixel scale")
    lines.append("\t\tif (jlCpix != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tz += aux->const_c * jlCpix;")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 19. Sphere fold")
    lines.append("\t\tif (jlSphere != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL r2 = dot(z, z);")
    lines.append("\t\t\tREAL minR2 = 0.25f;")
    lines.append("\t\t\tREAL fixedR2 = 1.0f;")
    lines.append("\t\t\tif (r2 < minR2)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tREAL t = fixedR2 / minR2;")
    lines.append("\t\t\t\tz *= t * jlSphere;")
    lines.append("\t\t\t\taux->DE *= fabs(t * jlSphere);")
    lines.append("\t\t\t}")
    lines.append("\t\t\telse if (r2 < fixedR2)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tREAL t = fixedR2 / r2;")
    lines.append("\t\t\t\tz *= t * jlSphere;")
    lines.append("\t\t\t\taux->DE *= fabs(t * jlSphere);")
    lines.append("\t\t\t}")
    lines.append("\t\t}")
    lines.append("")
    lines.append("\t\t// 20. Edge softness")
    lines.append("\t\tif (jlEdgeSoft != 0.0f)")
    lines.append("\t\t{")
    lines.append("\t\t\tREAL r = length(z);")
    lines.append("\t\t\tif (r > 1e-15f)")
    lines.append("\t\t\t{")
    lines.append("\t\t\t\tREAL soft = r / (r + jlEdgeSoft);")
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

    if "Julia Extensions" in content:
        return False

    if MARKER not in content:
        print(f"  WARN (no marker): {os.path.basename(filepath)}")
        return False

    content = content.replace(MARKER, block + "\t" + MARKER)
    with open(filepath, "w") as f:
        f.write(content)
    return True


def make_ui_groupbox():
    """Generate the UI XML groupbox for Julia extensions."""
    lines = []
    lines.append('   <widget class="QGroupBox" name="groupCheck_julia_extensions">')
    lines.append('    <property name="title">')
    lines.append('     <string>Julia Extensions</string>')
    lines.append('    </property>')
    lines.append('    <property name="checkable">')
    lines.append('     <bool>true</bool>')
    lines.append('    </property>')
    lines.append('    <property name="checked">')
    lines.append('     <bool>false</bool>')
    lines.append('    </property>')
    lines.append('    <layout class="QGridLayout">')

    param_labels = [
        ("transf_jl_power_osc", "Power Osc:"),
        ("transf_jl_power_osc_freq", "Power Osc Freq:"),
        ("transf_jl_theta_warp", "Theta Warp:"),
        ("transf_jl_phi_warp", "Phi Warp:"),
        ("transf_jl_radial_stretch", "Radial Stretch:"),
        ("transf_jl_pre_rot_xy", "Pre-Rot XY:"),
        ("transf_jl_pre_rot_xz", "Pre-Rot XZ:"),
        ("transf_jl_post_rot_yz", "Post-Rot YZ:"),
        ("transf_jl_twist_z", "Twist Z:"),
        ("transf_jl_scale_osc", "Scale Osc:"),
        ("transf_jl_scale_osc_freq", "Scale Osc Freq:"),
        ("transf_jl_offset_osc", "Offset Osc:"),
        ("transf_jl_offset_osc_freq", "Offset Osc Freq:"),
        ("transf_jl_radial_distort", "Radial Distort:"),
        ("transf_jl_turbulence", "Turbulence:"),
        ("transf_jl_gradient_color", "Gradient Color:"),
        ("transf_jl_de_tweak", "DE Tweak:"),
        ("transf_jl_cpixel_scale", "C-Pixel Scale:"),
        ("transf_jl_sphere_fold", "Sphere Fold:"),
        ("transf_jl_edge_softness", "Edge Softness:"),
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
    """Insert Julia extensions groupbox into UI file."""
    with open(filepath, "r") as f:
        content = f.read()

    if "julia_extensions" in content:
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
    print("=== Julia Extensions Upgrade Script ===")
    print()

    cpp_files = find_julia_files(CPP_DIR, "cpp")
    cl_files = find_julia_files(CL_DIR, "cl")
    ui_files = find_julia_files(UI_DIR, "ui")

    print(f"Found {len(cpp_files)} CPP, {len(cl_files)} CL, {len(ui_files)} UI files")
    print()

    cpp_block = make_jl_block_cpp()
    cl_block = make_jl_block_cl()

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
