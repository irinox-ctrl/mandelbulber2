#!/usr/bin/env python3
"""
Upgrade script: Add 50 T Custom Clip power transform parameters + 25 inverse transform parameters.
"""
import glob
import os
import xml.etree.ElementTree as ET

BASE = "/home/ubuntu/repos/mandelbulber2-private/mandelbulber2"
CPP_DIR = os.path.join(BASE, "formula", "definition")
CL_DIR = os.path.join(BASE, "formula", "opencl")
UI_DIR = os.path.join(BASE, "formula", "ui")

MARKER = "// GPU bypass: skip if all multipliers disabled"


def find_clip_files(directory, ext):
    if ext == "cpp":
        return sorted(glob.glob(os.path.join(directory, "fractal_transf_difs_clip_custom.cpp")))
    elif ext == "cl":
        return sorted(glob.glob(os.path.join(directory, "transf_difs_clip_custom.cl")))
    elif ext == "ui":
        return sorted(glob.glob(os.path.join(directory, "transf_difs_clip_custom.ui")))
    return []


def find_inverse_files(directory, ext):
    files = set()
    if ext == "cpp":
        files.update(glob.glob(os.path.join(directory, "fractal_*inverse*.cpp")))
        files.update(glob.glob(os.path.join(directory, "fractal_transf*inv*.cpp")))
    elif ext == "cl":
        files.update(glob.glob(os.path.join(directory, "*inverse*.cl")))
        files.update(glob.glob(os.path.join(directory, "transf*inv*.cl")))
    elif ext == "ui":
        files.update(glob.glob(os.path.join(directory, "*inverse*.ui")))
        files.update(glob.glob(os.path.join(directory, "transf*inv*.ui")))
    return sorted(files)


def make_cp_block_cpp():
    """Generate C++ Custom Clip Power Transform block (50 params)."""
    return """\t// --- Custom Clip Power Transform Extensions (50 parameters) ---
\t{
\t\tdouble cpPwX = fractal->transformCommon.cpPowerX;
\t\tdouble cpPwY = fractal->transformCommon.cpPowerY;
\t\tdouble cpPwZ = fractal->transformCommon.cpPowerZ;
\t\tdouble cpPreXY = fractal->transformCommon.cpPreRotXY;
\t\tdouble cpPreXZ = fractal->transformCommon.cpPreRotXZ;
\t\tdouble cpPreYZ = fractal->transformCommon.cpPreRotYZ;
\t\tdouble cpPostXY = fractal->transformCommon.cpPostRotXY;
\t\tdouble cpPostXZ = fractal->transformCommon.cpPostRotXZ;
\t\tdouble cpPostYZ = fractal->transformCommon.cpPostRotYZ;
\t\tdouble cpScX = fractal->transformCommon.cpScaleX;
\t\tdouble cpScY = fractal->transformCommon.cpScaleY;
\t\tdouble cpScZ = fractal->transformCommon.cpScaleZ;
\t\tdouble cpOfX = fractal->transformCommon.cpOffsetX;
\t\tdouble cpOfY = fractal->transformCommon.cpOffsetY;
\t\tdouble cpOfZ = fractal->transformCommon.cpOffsetZ;
\t\tdouble cpTwX = fractal->transformCommon.cpTwistX;
\t\tdouble cpTwY = fractal->transformCommon.cpTwistY;
\t\tdouble cpTwZ = fractal->transformCommon.cpTwistZ;
\t\tdouble cpBnX = fractal->transformCommon.cpBendX;
\t\tdouble cpBnY = fractal->transformCommon.cpBendY;
\t\tdouble cpBnZ = fractal->transformCommon.cpBendZ;
\t\tdouble cpTpX = fractal->transformCommon.cpTaperX;
\t\tdouble cpTpY = fractal->transformCommon.cpTaperY;
\t\tdouble cpTpZ = fractal->transformCommon.cpTaperZ;
\t\tdouble cpSFR = fractal->transformCommon.cpSphereFoldR;
\t\tdouble cpSFMR = fractal->transformCommon.cpSphereFoldMinR;
\t\tdouble cpBFX = fractal->transformCommon.cpBoxFoldX;
\t\tdouble cpBFY = fractal->transformCommon.cpBoxFoldY;
\t\tdouble cpBFZ = fractal->transformCommon.cpBoxFoldZ;
\t\tdouble cpSwA = fractal->transformCommon.cpSinWarpAmp;
\t\tdouble cpSwFX = fractal->transformCommon.cpSinWarpFreqX;
\t\tdouble cpSwFY = fractal->transformCommon.cpSinWarpFreqY;
\t\tdouble cpSwFZ = fractal->transformCommon.cpSinWarpFreqZ;
\t\tdouble cpRdW = fractal->transformCommon.cpRadialWarp;
\t\tdouble cpRdF = fractal->transformCommon.cpRadialFreq;
\t\tdouble cpNsA = fractal->transformCommon.cpNoiseAmp;
\t\tdouble cpNsF = fractal->transformCommon.cpNoiseFreq;
\t\tdouble cpItS = fractal->transformCommon.cpIterScale;
\t\tdouble cpItF = fractal->transformCommon.cpIterScaleFreq;
\t\tdouble cpMrX = fractal->transformCommon.cpMirrorX;
\t\tdouble cpMrY = fractal->transformCommon.cpMirrorY;
\t\tdouble cpMrZ = fractal->transformCommon.cpMirrorZ;
\t\tdouble cpInvR = fractal->transformCommon.cpInversionR;
\t\tdouble cpCpW = fractal->transformCommon.cpCpixelWeight;
\t\tdouble cpClD = fractal->transformCommon.cpColorDist;
\t\tdouble cpClA = fractal->transformCommon.cpColorAngle;
\t\tdouble cpClR = fractal->transformCommon.cpColorRadius;
\t\tdouble cpDET = fractal->transformCommon.cpDETweak;
\t\tdouble cpDES = fractal->transformCommon.cpDEScale;
\t\tdouble cpSCD = fractal->transformCommon.cpSoftClipDist;
\t\tdouble cpSCS = fractal->transformCommon.cpSoftClipSmooth;

\t\t// 1-3. Power transform per axis
\t\tif (cpPwX != 1.0 || cpPwY != 1.0 || cpPwZ != 1.0)
\t\t{
\t\t\tz.x = sign(z.x) * pow(fabs(z.x) + 1e-15, cpPwX);
\t\t\tz.y = sign(z.y) * pow(fabs(z.y) + 1e-15, cpPwY);
\t\t\tz.z = sign(z.z) * pow(fabs(z.z) + 1e-15, cpPwZ);
\t\t}

\t\t// 4-6. Pre-rotations
\t\tif (cpPreXY != 0.0)
\t\t{
\t\t\tdouble a = cpPreXY * M_PI / 180.0 * aux.i;
\t\t\tdouble ca = cos(a); double sa = sin(a);
\t\t\tdouble px = z.x * ca - z.y * sa;
\t\t\tdouble py = z.x * sa + z.y * ca;
\t\t\tz.x = px; z.y = py;
\t\t}
\t\tif (cpPreXZ != 0.0)
\t\t{
\t\t\tdouble a = cpPreXZ * M_PI / 180.0 * aux.i;
\t\t\tdouble ca = cos(a); double sa = sin(a);
\t\t\tdouble px = z.x * ca - z.z * sa;
\t\t\tdouble pz = z.x * sa + z.z * ca;
\t\t\tz.x = px; z.z = pz;
\t\t}
\t\tif (cpPreYZ != 0.0)
\t\t{
\t\t\tdouble a = cpPreYZ * M_PI / 180.0 * aux.i;
\t\t\tdouble ca = cos(a); double sa = sin(a);
\t\t\tdouble py = z.y * ca - z.z * sa;
\t\t\tdouble pz = z.y * sa + z.z * ca;
\t\t\tz.y = py; z.z = pz;
\t\t}

\t\t// 7-9. Post-rotations
\t\tif (cpPostXY != 0.0)
\t\t{
\t\t\tdouble a = cpPostXY * M_PI / 180.0;
\t\t\tdouble ca = cos(a); double sa = sin(a);
\t\t\tdouble px = z.x * ca - z.y * sa;
\t\t\tdouble py = z.x * sa + z.y * ca;
\t\t\tz.x = px; z.y = py;
\t\t}
\t\tif (cpPostXZ != 0.0)
\t\t{
\t\t\tdouble a = cpPostXZ * M_PI / 180.0;
\t\t\tdouble ca = cos(a); double sa = sin(a);
\t\t\tdouble px = z.x * ca - z.z * sa;
\t\t\tdouble pz = z.x * sa + z.z * ca;
\t\t\tz.x = px; z.z = pz;
\t\t}
\t\tif (cpPostYZ != 0.0)
\t\t{
\t\t\tdouble a = cpPostYZ * M_PI / 180.0;
\t\t\tdouble ca = cos(a); double sa = sin(a);
\t\t\tdouble py = z.y * ca - z.z * sa;
\t\t\tdouble pz = z.y * sa + z.z * ca;
\t\t\tz.y = py; z.z = pz;
\t\t}

\t\t// 10-12. Per-axis scale
\t\tif (cpScX != 1.0 || cpScY != 1.0 || cpScZ != 1.0)
\t\t{
\t\t\tz.x *= cpScX; z.y *= cpScY; z.z *= cpScZ;
\t\t\taux.DE *= fabs(max(cpScX, max(cpScY, cpScZ)));
\t\t}

\t\t// 13-15. Offset
\t\tif (cpOfX != 0.0 || cpOfY != 0.0 || cpOfZ != 0.0)
\t\t{
\t\t\tz.x += cpOfX; z.y += cpOfY; z.z += cpOfZ;
\t\t}

\t\t// 16-18. Twist per axis
\t\tif (cpTwX != 0.0)
\t\t{
\t\t\tdouble tw = cpTwX * M_PI / 180.0 * z.x;
\t\t\tdouble ct = cos(tw); double st = sin(tw);
\t\t\tdouble ty = z.y * ct - z.z * st;
\t\t\tdouble tz = z.y * st + z.z * ct;
\t\t\tz.y = ty; z.z = tz;
\t\t}
\t\tif (cpTwY != 0.0)
\t\t{
\t\t\tdouble tw = cpTwY * M_PI / 180.0 * z.y;
\t\t\tdouble ct = cos(tw); double st = sin(tw);
\t\t\tdouble tx = z.x * ct - z.z * st;
\t\t\tdouble tz = z.x * st + z.z * ct;
\t\t\tz.x = tx; z.z = tz;
\t\t}
\t\tif (cpTwZ != 0.0)
\t\t{
\t\t\tdouble tw = cpTwZ * M_PI / 180.0 * z.z;
\t\t\tdouble ct = cos(tw); double st = sin(tw);
\t\t\tdouble tx = z.x * ct - z.y * st;
\t\t\tdouble ty = z.x * st + z.y * ct;
\t\t\tz.x = tx; z.y = ty;
\t\t}

\t\t// 19-21. Bend per axis
\t\tif (cpBnX != 0.0) { z.y += cpBnX * z.x * z.x; }
\t\tif (cpBnY != 0.0) { z.z += cpBnY * z.y * z.y; }
\t\tif (cpBnZ != 0.0) { z.x += cpBnZ * z.z * z.z; }

\t\t// 22-24. Taper per axis
\t\tif (cpTpX != 0.0) { z.y *= 1.0 + cpTpX * z.x; z.z *= 1.0 + cpTpX * z.x; }
\t\tif (cpTpY != 0.0) { z.x *= 1.0 + cpTpY * z.y; z.z *= 1.0 + cpTpY * z.y; }
\t\tif (cpTpZ != 0.0) { z.x *= 1.0 + cpTpZ * z.z; z.y *= 1.0 + cpTpZ * z.z; }

\t\t// 25-26. Sphere fold
\t\tif (cpSFR != 0.0)
\t\t{
\t\t\tdouble r2 = z.Dot(z);
\t\t\tdouble minR2 = cpSFMR * cpSFMR;
\t\t\tdouble fixedR2 = cpSFR * cpSFR;
\t\t\tif (r2 < minR2)
\t\t\t{
\t\t\t\tdouble t = fixedR2 / minR2;
\t\t\t\tz *= t; aux.DE *= t;
\t\t\t}
\t\t\telse if (r2 < fixedR2)
\t\t\t{
\t\t\t\tdouble t = fixedR2 / r2;
\t\t\t\tz *= t; aux.DE *= t;
\t\t\t}
\t\t}

\t\t// 27-29. Box fold per axis
\t\tif (cpBFX != 0.0)
\t\t{
\t\t\tif (z.x > cpBFX) z.x = 2.0 * cpBFX - z.x;
\t\t\telse if (z.x < -cpBFX) z.x = -2.0 * cpBFX - z.x;
\t\t}
\t\tif (cpBFY != 0.0)
\t\t{
\t\t\tif (z.y > cpBFY) z.y = 2.0 * cpBFY - z.y;
\t\t\telse if (z.y < -cpBFY) z.y = -2.0 * cpBFY - z.y;
\t\t}
\t\tif (cpBFZ != 0.0)
\t\t{
\t\t\tif (z.z > cpBFZ) z.z = 2.0 * cpBFZ - z.z;
\t\t\telse if (z.z < -cpBFZ) z.z = -2.0 * cpBFZ - z.z;
\t\t}

\t\t// 30-33. Sin warp
\t\tif (cpSwA != 0.0)
\t\t{
\t\t\tz.x += cpSwA * sin(z.y * cpSwFX);
\t\t\tz.y += cpSwA * sin(z.z * cpSwFY);
\t\t\tz.z += cpSwA * sin(z.x * cpSwFZ);
\t\t}

\t\t// 34-35. Radial warp
\t\tif (cpRdW != 0.0)
\t\t{
\t\t\tdouble r = z.Length();
\t\t\tif (r > 1e-15)
\t\t\t{
\t\t\t\tdouble w = 1.0 + cpRdW * sin(r * cpRdF);
\t\t\t\tz *= w; aux.DE *= fabs(w);
\t\t\t}
\t\t}

\t\t// 36-37. Noise
\t\tif (cpNsA != 0.0)
\t\t{
\t\t\tdouble hx = sin(z.x * cpNsF * 12.9898 + z.y * 78.233) * 43758.5453;
\t\t\thx = hx - floor(hx);
\t\t\tdouble hy = sin(z.y * cpNsF * 12.9898 + z.z * 78.233) * 43758.5453;
\t\t\thy = hy - floor(hy);
\t\t\tdouble hz = sin(z.z * cpNsF * 12.9898 + z.x * 78.233) * 43758.5453;
\t\t\thz = hz - floor(hz);
\t\t\tz.x += (hx - 0.5) * cpNsA;
\t\t\tz.y += (hy - 0.5) * cpNsA;
\t\t\tz.z += (hz - 0.5) * cpNsA;
\t\t}

\t\t// 38-39. Iteration-dependent scale
\t\tif (cpItS != 0.0)
\t\t{
\t\t\tdouble s = 1.0 + cpItS * sin(aux.i * cpItF * 0.5);
\t\t\tz *= s; aux.DE *= fabs(s);
\t\t}

\t\t// 40-42. Mirror planes
\t\tif (cpMrX != 0.0) { if (z.x < 0.0) z.x = -z.x + cpMrX; }
\t\tif (cpMrY != 0.0) { if (z.y < 0.0) z.y = -z.y + cpMrY; }
\t\tif (cpMrZ != 0.0) { if (z.z < 0.0) z.z = -z.z + cpMrZ; }

\t\t// 43. Spherical inversion
\t\tif (cpInvR != 0.0)
\t\t{
\t\t\tdouble r2 = z.Dot(z);
\t\t\tif (r2 > 1e-15)
\t\t\t{
\t\t\t\tdouble invR2 = cpInvR * cpInvR / r2;
\t\t\t\tz *= invR2; aux.DE *= invR2;
\t\t\t}
\t\t}

\t\t// 44. C-pixel weight
\t\tif (cpCpW != 0.0)
\t\t{
\t\t\tz += aux.const_c * cpCpW;
\t\t}

\t\t// 45-47. Coloring
\t\tif (cpClD != 0.0) { aux.color += cpClD * z.Length(); }
\t\tif (cpClA != 0.0) { aux.color += cpClA * fabs(atan2(z.y, z.x)); }
\t\tif (cpClR != 0.0) { aux.color += cpClR * sqrt(z.x * z.x + z.y * z.y); }

\t\t// 48-49. DE adjustment
\t\tif (cpDET != 0.0) { aux.DE += cpDET; }
\t\tif (cpDES != 1.0) { aux.DE *= cpDES; }

\t\t// 50. Soft clip
\t\tif (cpSCD != 0.0)
\t\t{
\t\t\tdouble r = z.Length();
\t\t\tif (r > cpSCD)
\t\t\t{
\t\t\t\tdouble smooth = (cpSCS > 0.0) ? cpSCS : 0.1;
\t\t\t\tdouble t = 1.0 - (r - cpSCD) / (r - cpSCD + smooth);
\t\t\t\tz *= t; aux.DE *= t;
\t\t\t}
\t\t}
\t}

"""


def make_cp_block_cl():
    """Generate OpenCL Custom Clip Power Transform block."""
    cpp = make_cp_block_cpp()
    cl = cpp.replace("double ", "REAL ")
    cl = cl.replace("z.Dot(z)", "dot(z, z)")
    cl = cl.replace("z.Length()", "length(z)")
    cl = cl.replace("M_PI", "M_PI_F")
    cl = cl.replace("sin(", "native_sin(")
    cl = cl.replace("cos(", "native_cos(")
    cl = cl.replace("aux.i", "aux->i")
    cl = cl.replace("aux.DE", "aux->DE")
    cl = cl.replace("aux.color", "aux->color")
    cl = cl.replace("aux.const_c", "aux->const_c")
    # Fix double-native replacements
    cl = cl.replace("anative_cos", "acos")
    cl = cl.replace("fnative_cos", "fcos")
    return cl


def make_iv_block_cpp():
    """Generate C++ Inverse Transform block (25 params)."""
    return """\t// --- Inverse Transform Extensions (25 parameters) ---
\t{
\t\tdouble ivPreXY = fractal->transformCommon.ivPreRotXY;
\t\tdouble ivPreXZ = fractal->transformCommon.ivPreRotXZ;
\t\tdouble ivPostYZ = fractal->transformCommon.ivPostRotYZ;
\t\tdouble ivScOsc = fractal->transformCommon.ivScaleOsc;
\t\tdouble ivScFreq = fractal->transformCommon.ivScaleOscFreq;
\t\tdouble ivPwWarp = fractal->transformCommon.ivPowerWarp;
\t\tdouble ivRadSc = fractal->transformCommon.ivRadiusScale;
\t\tdouble ivTwZ = fractal->transformCommon.ivTwistZ;
\t\tdouble ivBnX = fractal->transformCommon.ivBendX;
\t\tdouble ivBnY = fractal->transformCommon.ivBendY;
\t\tdouble ivOffOsc = fractal->transformCommon.ivOffsetOsc;
\t\tdouble ivOffFreq = fractal->transformCommon.ivOffsetOscFreq;
\t\tdouble ivSwA = fractal->transformCommon.ivSinWarpAmp;
\t\tdouble ivSwF = fractal->transformCommon.ivSinWarpFreq;
\t\tdouble ivRadDist = fractal->transformCommon.ivRadialDistort;
\t\tdouble ivTurb = fractal->transformCommon.ivTurbulence;
\t\tdouble ivSphere = fractal->transformCommon.ivSphereFold;
\t\tdouble ivBox = fractal->transformCommon.ivBoxFold;
\t\tdouble ivMrX = fractal->transformCommon.ivMirrorX;
\t\tdouble ivMrY = fractal->transformCommon.ivMirrorY;
\t\tdouble ivMrZ = fractal->transformCommon.ivMirrorZ;
\t\tdouble ivGradCol = fractal->transformCommon.ivGradientColor;
\t\tdouble ivDETw = fractal->transformCommon.ivDETweak;
\t\tdouble ivCpix = fractal->transformCommon.ivCpixelScale;
\t\tdouble ivEdgeSoft = fractal->transformCommon.ivEdgeSoftness;

\t\t// 1-2. Pre-rotations
\t\tif (ivPreXY != 0.0)
\t\t{
\t\t\tdouble a = ivPreXY * M_PI / 180.0 * aux.i;
\t\t\tdouble ca = cos(a); double sa = sin(a);
\t\t\tdouble px = z.x * ca - z.y * sa;
\t\t\tdouble py = z.x * sa + z.y * ca;
\t\t\tz.x = px; z.y = py;
\t\t}
\t\tif (ivPreXZ != 0.0)
\t\t{
\t\t\tdouble a = ivPreXZ * M_PI / 180.0 * aux.i;
\t\t\tdouble ca = cos(a); double sa = sin(a);
\t\t\tdouble px = z.x * ca - z.z * sa;
\t\t\tdouble pz = z.x * sa + z.z * ca;
\t\t\tz.x = px; z.z = pz;
\t\t}

\t\t// 3. Post-rotation YZ
\t\tif (ivPostYZ != 0.0)
\t\t{
\t\t\tdouble a = ivPostYZ * M_PI / 180.0;
\t\t\tdouble ca = cos(a); double sa = sin(a);
\t\t\tdouble py = z.y * ca - z.z * sa;
\t\t\tdouble pz = z.y * sa + z.z * ca;
\t\t\tz.y = py; z.z = pz;
\t\t}

\t\t// 4-5. Scale oscillation
\t\tif (ivScOsc != 0.0)
\t\t{
\t\t\tdouble s = 1.0 + ivScOsc * sin(aux.i * ivScFreq * 0.5);
\t\t\tz *= s; aux.DE *= fabs(s);
\t\t}

\t\t// 6. Power warp
\t\tif (ivPwWarp != 0.0)
\t\t{
\t\t\tdouble pw = 1.0 + ivPwWarp;
\t\t\tz.x = sign(z.x) * pow(fabs(z.x) + 1e-15, pw);
\t\t\tz.y = sign(z.y) * pow(fabs(z.y) + 1e-15, pw);
\t\t\tz.z = sign(z.z) * pow(fabs(z.z) + 1e-15, pw);
\t\t}

\t\t// 7. Radius scale
\t\tif (ivRadSc != 0.0)
\t\t{
\t\t\tdouble r = z.Length();
\t\t\tif (r > 1e-15)
\t\t\t{
\t\t\t\tdouble s = 1.0 + ivRadSc * (r - 1.0);
\t\t\t\tz *= s; aux.DE *= fabs(s);
\t\t\t}
\t\t}

\t\t// 8. Twist Z
\t\tif (ivTwZ != 0.0)
\t\t{
\t\t\tdouble tw = ivTwZ * M_PI / 180.0 * z.z;
\t\t\tdouble ct = cos(tw); double st = sin(tw);
\t\t\tdouble tx = z.x * ct - z.y * st;
\t\t\tdouble ty = z.x * st + z.y * ct;
\t\t\tz.x = tx; z.y = ty;
\t\t}

\t\t// 9-10. Bend
\t\tif (ivBnX != 0.0) { z.y += ivBnX * z.x * z.x; }
\t\tif (ivBnY != 0.0) { z.z += ivBnY * z.y * z.y; }

\t\t// 11-12. Offset oscillation
\t\tif (ivOffOsc != 0.0)
\t\t{
\t\t\tdouble oOsc = ivOffOsc * sin(aux.i * ivOffFreq * 0.5);
\t\t\tz.x += oOsc; z.y += oOsc * 0.7; z.z += oOsc * 0.5;
\t\t}

\t\t// 13-14. Sin warp
\t\tif (ivSwA != 0.0)
\t\t{
\t\t\tz.x += ivSwA * sin(z.y * ivSwF);
\t\t\tz.y += ivSwA * sin(z.z * ivSwF);
\t\t\tz.z += ivSwA * sin(z.x * ivSwF);
\t\t}

\t\t// 15. Radial distortion
\t\tif (ivRadDist != 0.0)
\t\t{
\t\t\tdouble r = z.Length();
\t\t\tif (r > 1e-15)
\t\t\t{
\t\t\t\tdouble d = 1.0 + ivRadDist * sin(r * 4.0);
\t\t\t\tz *= d; aux.DE *= fabs(d);
\t\t\t}
\t\t}

\t\t// 16. Turbulence
\t\tif (ivTurb != 0.0)
\t\t{
\t\t\tdouble hx = sin(z.x * 12.9898 + z.y * 78.233) * 43758.5453;
\t\t\thx = hx - floor(hx);
\t\t\tdouble hy = sin(z.y * 12.9898 + z.z * 78.233) * 43758.5453;
\t\t\thy = hy - floor(hy);
\t\t\tdouble hz = sin(z.z * 12.9898 + z.x * 78.233) * 43758.5453;
\t\t\thz = hz - floor(hz);
\t\t\tz.x += (hx - 0.5) * ivTurb;
\t\t\tz.y += (hy - 0.5) * ivTurb;
\t\t\tz.z += (hz - 0.5) * ivTurb;
\t\t}

\t\t// 17. Sphere fold
\t\tif (ivSphere != 0.0)
\t\t{
\t\t\tdouble r2 = z.Dot(z);
\t\t\tdouble minR2 = 0.25;
\t\t\tdouble fixedR2 = ivSphere * ivSphere;
\t\t\tif (r2 < minR2) { double t = fixedR2 / minR2; z *= t; aux.DE *= t; }
\t\t\telse if (r2 < fixedR2) { double t = fixedR2 / r2; z *= t; aux.DE *= t; }
\t\t}

\t\t// 18. Box fold
\t\tif (ivBox != 0.0)
\t\t{
\t\t\tif (z.x > ivBox) z.x = 2.0 * ivBox - z.x;
\t\t\telse if (z.x < -ivBox) z.x = -2.0 * ivBox - z.x;
\t\t\tif (z.y > ivBox) z.y = 2.0 * ivBox - z.y;
\t\t\telse if (z.y < -ivBox) z.y = -2.0 * ivBox - z.y;
\t\t\tif (z.z > ivBox) z.z = 2.0 * ivBox - z.z;
\t\t\telse if (z.z < -ivBox) z.z = -2.0 * ivBox - z.z;
\t\t}

\t\t// 19-21. Mirror planes
\t\tif (ivMrX != 0.0) { if (z.x < 0.0) z.x = -z.x + ivMrX; }
\t\tif (ivMrY != 0.0) { if (z.y < 0.0) z.y = -z.y + ivMrY; }
\t\tif (ivMrZ != 0.0) { if (z.z < 0.0) z.z = -z.z + ivMrZ; }

\t\t// 22. Gradient color
\t\tif (ivGradCol != 0.0) { aux.color += ivGradCol * z.Length(); }

\t\t// 23. DE tweak
\t\tif (ivDETw != 0.0) { aux.DE += ivDETw; }

\t\t// 24. C-pixel scale
\t\tif (ivCpix != 0.0) { z += aux.const_c * ivCpix; }

\t\t// 25. Edge softness
\t\tif (ivEdgeSoft != 0.0)
\t\t{
\t\t\tdouble r = z.Length();
\t\t\tif (r > 1e-15) { double soft = r / (r + ivEdgeSoft); z *= soft; aux.DE *= soft; }
\t\t}
\t}

"""


def make_iv_block_cl():
    """Generate OpenCL Inverse Transform block."""
    cpp = make_iv_block_cpp()
    cl = cpp.replace("double ", "REAL ")
    cl = cl.replace("z.Dot(z)", "dot(z, z)")
    cl = cl.replace("z.Length()", "length(z)")
    cl = cl.replace("M_PI", "M_PI_F")
    cl = cl.replace("sin(", "native_sin(")
    cl = cl.replace("cos(", "native_cos(")
    cl = cl.replace("aux.i", "aux->i")
    cl = cl.replace("aux.DE", "aux->DE")
    cl = cl.replace("aux.color", "aux->color")
    cl = cl.replace("aux.const_c", "aux->const_c")
    cl = cl.replace("anative_cos", "acos")
    cl = cl.replace("fnative_cos", "fcos")
    return cl


def update_formula_file(filepath, block, tag):
    """Insert block before the GPU bypass marker."""
    with open(filepath, "r") as f:
        content = f.read()

    if tag in content:
        return False

    if MARKER not in content:
        print(f"  WARN (no marker): {os.path.basename(filepath)}")
        return False

    content = content.replace(MARKER, block + "\t" + MARKER)
    with open(filepath, "w") as f:
        f.write(content)
    return True


def make_cp_ui_groupbox():
    """Generate UI XML for Custom Clip power transform (50 params)."""
    lines = []
    lines.append('   <widget class="QGroupBox" name="groupCheck_clip_power_transform">')
    lines.append('    <property name="title">')
    lines.append('     <string>Custom Clip Power Transform</string>')
    lines.append('    </property>')
    lines.append('    <property name="checkable"><bool>true</bool></property>')
    lines.append('    <property name="checked"><bool>false</bool></property>')
    lines.append('    <layout class="QGridLayout">')

    params = [
        ("transf_cp_power_x", "Power X:"), ("transf_cp_power_y", "Power Y:"), ("transf_cp_power_z", "Power Z:"),
        ("transf_cp_pre_rot_xy", "Pre-Rot XY:"), ("transf_cp_pre_rot_xz", "Pre-Rot XZ:"), ("transf_cp_pre_rot_yz", "Pre-Rot YZ:"),
        ("transf_cp_post_rot_xy", "Post-Rot XY:"), ("transf_cp_post_rot_xz", "Post-Rot XZ:"), ("transf_cp_post_rot_yz", "Post-Rot YZ:"),
        ("transf_cp_scale_x", "Scale X:"), ("transf_cp_scale_y", "Scale Y:"), ("transf_cp_scale_z", "Scale Z:"),
        ("transf_cp_offset_x", "Offset X:"), ("transf_cp_offset_y", "Offset Y:"), ("transf_cp_offset_z", "Offset Z:"),
        ("transf_cp_twist_x", "Twist X:"), ("transf_cp_twist_y", "Twist Y:"), ("transf_cp_twist_z", "Twist Z:"),
        ("transf_cp_bend_x", "Bend X:"), ("transf_cp_bend_y", "Bend Y:"), ("transf_cp_bend_z", "Bend Z:"),
        ("transf_cp_taper_x", "Taper X:"), ("transf_cp_taper_y", "Taper Y:"), ("transf_cp_taper_z", "Taper Z:"),
        ("transf_cp_sphere_fold_r", "Sphere Fold R:"), ("transf_cp_sphere_fold_min_r", "Sphere Fold MinR:"),
        ("transf_cp_box_fold_x", "Box Fold X:"), ("transf_cp_box_fold_y", "Box Fold Y:"), ("transf_cp_box_fold_z", "Box Fold Z:"),
        ("transf_cp_sin_warp_amp", "Sin Warp Amp:"), ("transf_cp_sin_warp_freq_x", "Sin Warp Freq X:"),
        ("transf_cp_sin_warp_freq_y", "Sin Warp Freq Y:"), ("transf_cp_sin_warp_freq_z", "Sin Warp Freq Z:"),
        ("transf_cp_radial_warp", "Radial Warp:"), ("transf_cp_radial_freq", "Radial Freq:"),
        ("transf_cp_noise_amp", "Noise Amp:"), ("transf_cp_noise_freq", "Noise Freq:"),
        ("transf_cp_iter_scale", "Iter Scale:"), ("transf_cp_iter_scale_freq", "Iter Scale Freq:"),
        ("transf_cp_mirror_x", "Mirror X:"), ("transf_cp_mirror_y", "Mirror Y:"), ("transf_cp_mirror_z", "Mirror Z:"),
        ("transf_cp_inversion_r", "Inversion R:"), ("transf_cp_cpixel_weight", "C-Pixel Weight:"),
        ("transf_cp_color_dist", "Color Dist:"), ("transf_cp_color_angle", "Color Angle:"), ("transf_cp_color_radius", "Color Radius:"),
        ("transf_cp_de_tweak", "DE Tweak:"), ("transf_cp_de_scale", "DE Scale:"),
        ("transf_cp_soft_clip_dist", "Soft Clip Dist:"), ("transf_cp_soft_clip_smooth", "Soft Clip Smooth:"),
    ]

    for row, (param, label) in enumerate(params):
        lines.append(f'     <item row="{row}" column="0">')
        lines.append(f'      <widget class="QLabel"><property name="text"><string>{label}</string></property></widget>')
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


def make_iv_ui_groupbox():
    """Generate UI XML for Inverse Transform (25 params)."""
    lines = []
    lines.append('   <widget class="QGroupBox" name="groupCheck_inverse_extensions">')
    lines.append('    <property name="title"><string>Inverse Transform Extensions</string></property>')
    lines.append('    <property name="checkable"><bool>true</bool></property>')
    lines.append('    <property name="checked"><bool>false</bool></property>')
    lines.append('    <layout class="QGridLayout">')

    params = [
        ("transf_iv_pre_rot_xy", "Pre-Rot XY:"), ("transf_iv_pre_rot_xz", "Pre-Rot XZ:"),
        ("transf_iv_post_rot_yz", "Post-Rot YZ:"),
        ("transf_iv_scale_osc", "Scale Osc:"), ("transf_iv_scale_osc_freq", "Scale Osc Freq:"),
        ("transf_iv_power_warp", "Power Warp:"), ("transf_iv_radius_scale", "Radius Scale:"),
        ("transf_iv_twist_z", "Twist Z:"), ("transf_iv_bend_x", "Bend X:"), ("transf_iv_bend_y", "Bend Y:"),
        ("transf_iv_offset_osc", "Offset Osc:"), ("transf_iv_offset_osc_freq", "Offset Osc Freq:"),
        ("transf_iv_sin_warp_amp", "Sin Warp Amp:"), ("transf_iv_sin_warp_freq", "Sin Warp Freq:"),
        ("transf_iv_radial_distort", "Radial Distort:"), ("transf_iv_turbulence", "Turbulence:"),
        ("transf_iv_sphere_fold", "Sphere Fold:"), ("transf_iv_box_fold", "Box Fold:"),
        ("transf_iv_mirror_x", "Mirror X:"), ("transf_iv_mirror_y", "Mirror Y:"), ("transf_iv_mirror_z", "Mirror Z:"),
        ("transf_iv_gradient_color", "Gradient Color:"), ("transf_iv_de_tweak", "DE Tweak:"),
        ("transf_iv_cpixel_scale", "C-Pixel Scale:"), ("transf_iv_edge_softness", "Edge Softness:"),
    ]

    for row, (param, label) in enumerate(params):
        lines.append(f'     <item row="{row}" column="0">')
        lines.append(f'      <widget class="QLabel"><property name="text"><string>{label}</string></property></widget>')
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


def update_ui_file(filepath, groupbox_xml, tag):
    """Insert groupbox into UI file."""
    with open(filepath, "r") as f:
        content = f.read()

    if tag in content:
        return False

    insert_marker = " </widget>\n <customwidgets>"
    if insert_marker not in content:
        insert_marker = " </widget>\n</ui>"
        if insert_marker not in content:
            print(f"  WARN UI (no insert point): {os.path.basename(filepath)}")
            return False

    content = content.replace(insert_marker, groupbox_xml + "\n" + insert_marker, 1)
    with open(filepath, "w") as f:
        f.write(content)
    return True


def validate_xml(filepath):
    try:
        ET.parse(filepath)
        return True
    except ET.ParseError as e:
        print(f"  XML ERROR in {os.path.basename(filepath)}: {e}")
        return False


def main():
    print("=== Custom Clip + Inverse Transform Upgrade Script ===")
    print()

    # Custom Clip
    cp_cpp = find_clip_files(CPP_DIR, "cpp")
    cp_cl = find_clip_files(CL_DIR, "cl")
    cp_ui = find_clip_files(UI_DIR, "ui")
    print(f"Custom Clip: {len(cp_cpp)} CPP, {len(cp_cl)} CL, {len(cp_ui)} UI")

    # Inverse
    iv_cpp = find_inverse_files(CPP_DIR, "cpp")
    iv_cl = find_inverse_files(CL_DIR, "cl")
    iv_ui = find_inverse_files(UI_DIR, "ui")
    print(f"Inverse: {len(iv_cpp)} CPP, {len(iv_cl)} CL, {len(iv_ui)} UI")
    print()

    cp_block_cpp = make_cp_block_cpp()
    cp_block_cl = make_cp_block_cl()
    iv_block_cpp = make_iv_block_cpp()
    iv_block_cl = make_iv_block_cl()

    # Update Custom Clip formulas
    print("--- Custom Clip CPP ---")
    ok = 0
    for f in cp_cpp:
        if update_formula_file(f, cp_block_cpp, "Custom Clip Power Transform"):
            ok += 1
    print(f"  Updated {ok}/{len(cp_cpp)}")

    print("--- Custom Clip CL ---")
    ok = 0
    for f in cp_cl:
        if update_formula_file(f, cp_block_cl, "Custom Clip Power Transform"):
            ok += 1
    print(f"  Updated {ok}/{len(cp_cl)}")

    print("--- Custom Clip UI ---")
    ok = 0
    for f in cp_ui:
        if update_ui_file(f, make_cp_ui_groupbox(), "clip_power_transform"):
            ok += 1
    print(f"  Updated {ok}/{len(cp_ui)}")
    print()

    # Update Inverse formulas
    print("--- Inverse CPP ---")
    ok = 0
    for f in iv_cpp:
        if update_formula_file(f, iv_block_cpp, "Inverse Transform Extensions"):
            ok += 1
    print(f"  Updated {ok}/{len(iv_cpp)}")

    print("--- Inverse CL ---")
    ok = 0
    for f in iv_cl:
        if update_formula_file(f, iv_block_cl, "Inverse Transform Extensions"):
            ok += 1
    print(f"  Updated {ok}/{len(iv_cl)}")

    print("--- Inverse UI ---")
    ok = 0
    for f in iv_ui:
        if update_ui_file(f, make_iv_ui_groupbox(), "inverse_extensions"):
            ok += 1
    print(f"  Updated {ok}/{len(iv_ui)}")
    print()

    # Validate XML
    print("--- Validating XML ---")
    xml_errors = 0
    for f in cp_ui + iv_ui:
        if not validate_xml(f):
            xml_errors += 1
    total = len(cp_ui) + len(iv_ui)
    if xml_errors == 0:
        print(f"  All {total} UI files valid XML")
    else:
        print(f"  WARNING: {xml_errors}/{total} files have XML errors!")
    print()

    print("=== Done ===")


if __name__ == "__main__":
    main()
