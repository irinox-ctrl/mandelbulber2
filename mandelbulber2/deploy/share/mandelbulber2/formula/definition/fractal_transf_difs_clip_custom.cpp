/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * TransfDIFSClipCustom
 */

#include "all_fractal_definitions.h"

cFractalTransfDIFSClipCustom::cFractalTransfDIFSClipCustom() : cAbstractFractal()
{
	nameInComboBox = "T>DIFS Clip Custom";
	internalName = "transf_difs_clip_custom";
	internalID = fractal::transfDIFSClipCustom;
	DEType = analyticDEType;
	DEFunctionType = customDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 1000.0;
	DEAnalyticFunction = analyticFunctionCustomDE;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfDIFSClipCustom::FormulaCode(
	CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	if (fractal->transformCommon.functionEnabledwFalse) aux.dist = z.Length() / aux.DE;

	// pre-box option
	if (fractal->transformCommon.functionEnabledAFalse)
	{
		CVector4 zc = z;
		zc += fractal->transformCommon.offsetA000;
		zc = fabs(zc) - fractal->transformCommon.additionConstant111;
		zc.x = max(zc.x, 0.0);
		zc.y = max(zc.y, 0.0);
		zc.z = max(zc.z, 0.0);
		double zcd = zc.Length() * fractal->transformCommon.scale1 - fractal->transformCommon.offsetB0;
		if (!fractal->transformCommon.functionEnabledNFalse)
		{
			aux.dist = zcd;
		}
		else
		{
			aux.dist = min(aux.dist, zcd);
		}
	}

	// transform c
	CVector4 c = aux.const_c;
	if (fractal->transformCommon.functionEnabledFalse) c = z;

			// polyfold
	if (fractal->transformCommon.functionEnabledPFalse)
	{
		c.y = fabs(c.y);
		double psi = M_PI / fractal->transformCommon.int6;
		psi = fabs(fmod(atan2(c.y, c.x) + psi, 2.0 * psi) - psi);
		double len = sqrt(c.x * c.x + c.y * c.y);
		c.x = cos(psi) * len;
		c.y = sin(psi) * len;
	}

	if (fractal->transformCommon.functionEnabledAxFalse) c.x = fabs(c.x);
	if (fractal->transformCommon.functionEnabledAyFalse) c.y = fabs(c.y);
	if (fractal->transformCommon.functionEnabledAzFalse) c.z = fabs(c.z);

	c *= fractal->transformCommon.scale3D111;
	c += fractal->transformCommon.offset000;
	c = fractal->transformCommon.rotationMatrix.RotateVector(c);

	double dst = 0.0;
	if (fractal->transformCommon.functionEnabledBx)
	{
		CVector4 g = fabs(c) - fractal->transformCommon.offsetC111;
		if (!fractal->transformCommon.functionEnabledCFalse)
		{
			dst = max(max(g.x, g.y), g.z);
		}
		else
		{
			dst = c.Length() - g.Length();
		}
		if (fractal->transformCommon.functionEnabledOFalse)
		{
			dst = fabs(dst) - fractal->transformCommon.offsetC0;
		}
	}

	double dst1 = 0.0;
	if (fractal->transformCommon.functionEnabledBFalse) // sphere
	{

		if (!fractal->transformCommon.functionEnabledIFalse)
		{
			dst1 = c.Length() - fractal->transformCommon.offsetR1; // sphere
		}
		else // cyl or cone
		{
			if (!fractal->transformCommon.functionEnabledEFalse) // cyl
			{
				dst1 = sqrt(c.x * c.x + c.y * c.y) - fractal->transformCommon.offsetR1;
			}
			else // cones
			{
				double CZ = -c.z;
				if (fractal->transformCommon.functionEnabledFFalse) CZ = fabs(c.z);
				if (fractal->transformCommon.functionEnabledGFalse) CZ = c.z * c.z;
				dst1 = sqrt(c.x * c.x + c.y * c.y) - fractal->transformCommon.offsetR1 * CZ;
			}
		}

		if (!fractal->transformCommon.functionEnabledJFalse) // z clip
		{
			dst1 = max(fabs(c.z) - fractal->transformCommon.offset1, dst1);
		}
		if (fractal->transformCommon.functionEnabledMFalse)
		{
			dst1 = fabs(dst1) - fractal->transformCommon.offsetA0;
		}

		if (!fractal->transformCommon.functionEnabledDFalse) dst = dst1;
		else dst = max(dst, dst1);
	}

	// aux->color
	if (fractal->foldColor.auxColorEnabledFalse)
	{
		double addColor = 0.0;
		if (dst > aux.dist) addColor += fractal->foldColor.difs0000.x;
		if (dst1 > aux.dist) addColor += fractal->foldColor.difs0000.y;

		if (!fractal->transformCommon.functionEnabledyFalse)
			aux.color = addColor;
		else
			aux.color += addColor;
	}

	if (!fractal->transformCommon.functionEnabledxFalse)
	{
		dst *= fractal->analyticDE.scale1;
	}
	else
	{
		dst *= fractal->analyticDE.scale1 / aux.DE;
	}

	dst = max(aux.dist, dst);

	if (!fractal->analyticDE.enabledFalse)
		aux.dist = dst;
	else
		aux.dist = min(dst, aux.dist);
		// --- IFS/DIFS Extensions (15 parameters) ---
	{
		double ifsFoldOsc = fractal->transformCommon.ifsFoldOscAmp;
		double ifsFoldFreq = fractal->transformCommon.ifsFoldOscFreq;
		double ifsScaleOsc = fractal->transformCommon.ifsScaleOsc;
		double ifsScaleFreq = fractal->transformCommon.ifsScaleOscFreq;
		double ifsPreRot = fractal->transformCommon.ifsPreRotAngle;
		double ifsPostRot = fractal->transformCommon.ifsPostRotAngle;
		double ifsTwZ = fractal->transformCommon.ifsTwistZ;
		double ifsOffWarp = fractal->transformCommon.ifsOffsetWarp;
		double ifsRadDist = fractal->transformCommon.ifsRadialDistort;
		double ifsTurb = fractal->transformCommon.ifsTurbulence;
		double ifsGradCol = fractal->transformCommon.ifsGradientColor;
		double ifsDETw = fractal->transformCommon.ifsDETweak;
		double ifsCpix = fractal->transformCommon.ifsCpixelInject;
		double ifsSphere = fractal->transformCommon.ifsSphereFold;
		double ifsEdgeSoft = fractal->transformCommon.ifsEdgeSoftness;

		// 1-2. Fold oscillation
		if (ifsFoldOsc != 0.0)
		{
			double fOsc = ifsFoldOsc * sin(aux.i * ifsFoldFreq * 0.5);
			z.x += fOsc * sin(z.y * 3.0);
			z.y += fOsc * sin(z.z * 3.0);
			z.z += fOsc * sin(z.x * 3.0);
		}

		// 3-4. Scale oscillation
		if (ifsScaleOsc != 0.0)
		{
			double sOsc = 1.0 + ifsScaleOsc * sin(aux.i * ifsScaleFreq * 0.5);
			z *= sOsc;
			aux.DE *= fabs(sOsc);
		}

		// 5. Pre-rotation
		if (ifsPreRot != 0.0)
		{
			double a = ifsPreRot * M_PI / 180.0 * aux.i;
			double ca = cos(a); double sa = sin(a);
			double px = z.x * ca - z.y * sa;
			double py = z.x * sa + z.y * ca;
			z.x = px; z.y = py;
		}

		// 6. Post-rotation
		if (ifsPostRot != 0.0)
		{
			double a = ifsPostRot * M_PI / 180.0;
			double ca = cos(a); double sa = sin(a);
			double py = z.y * ca - z.z * sa;
			double pz = z.y * sa + z.z * ca;
			z.y = py; z.z = pz;
		}

		// 7. Twist Z
		if (ifsTwZ != 0.0)
		{
			double tw = ifsTwZ * M_PI / 180.0 * z.z;
			double ct = cos(tw); double st = sin(tw);
			double tx = z.x * ct - z.y * st;
			double ty = z.x * st + z.y * ct;
			z.x = tx; z.y = ty;
		}

		// 8. Offset warp
		if (ifsOffWarp != 0.0)
		{
			z.x += ifsOffWarp * sin(z.y * 2.0 + aux.i * 0.5);
			z.y += ifsOffWarp * sin(z.z * 2.0 + aux.i * 0.7);
			z.z += ifsOffWarp * sin(z.x * 2.0 + aux.i * 0.3);
		}

		// 9. Radial distortion
		if (ifsRadDist != 0.0)
		{
			double r = z.Length();
			if (r > 1e-15)
			{
				double distort = 1.0 + ifsRadDist * sin(r * 4.0);
				z *= distort;
				aux.DE *= fabs(distort);
			}
		}

		// 10. Turbulence
		if (ifsTurb != 0.0)
		{
			double hx = sin(z.x * 12.9898 + z.y * 78.233) * 43758.5453;
			hx = hx - floor(hx);
			double hy = sin(z.y * 12.9898 + z.z * 78.233) * 43758.5453;
			hy = hy - floor(hy);
			double hz = sin(z.z * 12.9898 + z.x * 78.233) * 43758.5453;
			hz = hz - floor(hz);
			z.x += (hx - 0.5) * ifsTurb;
			z.y += (hy - 0.5) * ifsTurb;
			z.z += (hz - 0.5) * ifsTurb;
		}

		// 11. Gradient color
		if (ifsGradCol != 0.0)
		{
			aux.color += ifsGradCol * z.Length();
		}

		// 12. DE tweak
		if (ifsDETw != 0.0)
		{
			aux.DE += ifsDETw;
		}

		// 13. C-pixel injection
		if (ifsCpix != 0.0)
		{
			z += aux.const_c * ifsCpix;
		}

		// 14. Sphere fold
		if (ifsSphere != 0.0)
		{
			double r2 = z.Dot(z);
			double minR2 = 0.25;
			double fixedR2 = 1.0;
			if (r2 < minR2)
			{
				double t = fixedR2 / minR2;
				z *= t * ifsSphere;
				aux.DE *= fabs(t * ifsSphere);
			}
			else if (r2 < fixedR2)
			{
				double t = fixedR2 / r2;
				z *= t * ifsSphere;
				aux.DE *= fabs(t * ifsSphere);
			}
		}

		// 15. Edge softness
		if (ifsEdgeSoft != 0.0)
		{
			double r = z.Length();
			if (r > 1e-15)
			{
				double soft = r / (r + ifsEdgeSoft);
				z *= soft;
				aux.DE *= soft;
			}
		}
	}

		// --- Custom Clip Power Transform Extensions (50 parameters) ---
	{
		double cpPwX = fractal->transformCommon.cpPowerX;
		double cpPwY = fractal->transformCommon.cpPowerY;
		double cpPwZ = fractal->transformCommon.cpPowerZ;
		double cpPreXY = fractal->transformCommon.cpPreRotXY;
		double cpPreXZ = fractal->transformCommon.cpPreRotXZ;
		double cpPreYZ = fractal->transformCommon.cpPreRotYZ;
		double cpPostXY = fractal->transformCommon.cpPostRotXY;
		double cpPostXZ = fractal->transformCommon.cpPostRotXZ;
		double cpPostYZ = fractal->transformCommon.cpPostRotYZ;
		double cpScX = fractal->transformCommon.cpScaleX;
		double cpScY = fractal->transformCommon.cpScaleY;
		double cpScZ = fractal->transformCommon.cpScaleZ;
		double cpOfX = fractal->transformCommon.cpOffsetX;
		double cpOfY = fractal->transformCommon.cpOffsetY;
		double cpOfZ = fractal->transformCommon.cpOffsetZ;
		double cpTwX = fractal->transformCommon.cpTwistX;
		double cpTwY = fractal->transformCommon.cpTwistY;
		double cpTwZ = fractal->transformCommon.cpTwistZ;
		double cpBnX = fractal->transformCommon.cpBendX;
		double cpBnY = fractal->transformCommon.cpBendY;
		double cpBnZ = fractal->transformCommon.cpBendZ;
		double cpTpX = fractal->transformCommon.cpTaperX;
		double cpTpY = fractal->transformCommon.cpTaperY;
		double cpTpZ = fractal->transformCommon.cpTaperZ;
		double cpSFR = fractal->transformCommon.cpSphereFoldR;
		double cpSFMR = fractal->transformCommon.cpSphereFoldMinR;
		double cpBFX = fractal->transformCommon.cpBoxFoldX;
		double cpBFY = fractal->transformCommon.cpBoxFoldY;
		double cpBFZ = fractal->transformCommon.cpBoxFoldZ;
		double cpSwA = fractal->transformCommon.cpSinWarpAmp;
		double cpSwFX = fractal->transformCommon.cpSinWarpFreqX;
		double cpSwFY = fractal->transformCommon.cpSinWarpFreqY;
		double cpSwFZ = fractal->transformCommon.cpSinWarpFreqZ;
		double cpRdW = fractal->transformCommon.cpRadialWarp;
		double cpRdF = fractal->transformCommon.cpRadialFreq;
		double cpNsA = fractal->transformCommon.cpNoiseAmp;
		double cpNsF = fractal->transformCommon.cpNoiseFreq;
		double cpItS = fractal->transformCommon.cpIterScale;
		double cpItF = fractal->transformCommon.cpIterScaleFreq;
		double cpMrX = fractal->transformCommon.cpMirrorX;
		double cpMrY = fractal->transformCommon.cpMirrorY;
		double cpMrZ = fractal->transformCommon.cpMirrorZ;
		double cpInvR = fractal->transformCommon.cpInversionR;
		double cpCpW = fractal->transformCommon.cpCpixelWeight;
		double cpClD = fractal->transformCommon.cpColorDist;
		double cpClA = fractal->transformCommon.cpColorAngle;
		double cpClR = fractal->transformCommon.cpColorRadius;
		double cpDET = fractal->transformCommon.cpDETweak;
		double cpDES = fractal->transformCommon.cpDEScale;
		double cpSCD = fractal->transformCommon.cpSoftClipDist;
		double cpSCS = fractal->transformCommon.cpSoftClipSmooth;

		// 1-3. Power transform per axis
		if (cpPwX != 1.0 || cpPwY != 1.0 || cpPwZ != 1.0)
		{
			z.x = sign(z.x) * pow(fabs(z.x) + 1e-15, cpPwX);
			z.y = sign(z.y) * pow(fabs(z.y) + 1e-15, cpPwY);
			z.z = sign(z.z) * pow(fabs(z.z) + 1e-15, cpPwZ);
		}

		// 4-6. Pre-rotations
		if (cpPreXY != 0.0)
		{
			double a = cpPreXY * M_PI / 180.0 * aux.i;
			double ca = cos(a); double sa = sin(a);
			double px = z.x * ca - z.y * sa;
			double py = z.x * sa + z.y * ca;
			z.x = px; z.y = py;
		}
		if (cpPreXZ != 0.0)
		{
			double a = cpPreXZ * M_PI / 180.0 * aux.i;
			double ca = cos(a); double sa = sin(a);
			double px = z.x * ca - z.z * sa;
			double pz = z.x * sa + z.z * ca;
			z.x = px; z.z = pz;
		}
		if (cpPreYZ != 0.0)
		{
			double a = cpPreYZ * M_PI / 180.0 * aux.i;
			double ca = cos(a); double sa = sin(a);
			double py = z.y * ca - z.z * sa;
			double pz = z.y * sa + z.z * ca;
			z.y = py; z.z = pz;
		}

		// 7-9. Post-rotations
		if (cpPostXY != 0.0)
		{
			double a = cpPostXY * M_PI / 180.0;
			double ca = cos(a); double sa = sin(a);
			double px = z.x * ca - z.y * sa;
			double py = z.x * sa + z.y * ca;
			z.x = px; z.y = py;
		}
		if (cpPostXZ != 0.0)
		{
			double a = cpPostXZ * M_PI / 180.0;
			double ca = cos(a); double sa = sin(a);
			double px = z.x * ca - z.z * sa;
			double pz = z.x * sa + z.z * ca;
			z.x = px; z.z = pz;
		}
		if (cpPostYZ != 0.0)
		{
			double a = cpPostYZ * M_PI / 180.0;
			double ca = cos(a); double sa = sin(a);
			double py = z.y * ca - z.z * sa;
			double pz = z.y * sa + z.z * ca;
			z.y = py; z.z = pz;
		}

		// 10-12. Per-axis scale
		if (cpScX != 1.0 || cpScY != 1.0 || cpScZ != 1.0)
		{
			z.x *= cpScX; z.y *= cpScY; z.z *= cpScZ;
			aux.DE *= fabs(max(cpScX, max(cpScY, cpScZ)));
		}

		// 13-15. Offset
		if (cpOfX != 0.0 || cpOfY != 0.0 || cpOfZ != 0.0)
		{
			z.x += cpOfX; z.y += cpOfY; z.z += cpOfZ;
		}

		// 16-18. Twist per axis
		if (cpTwX != 0.0)
		{
			double tw = cpTwX * M_PI / 180.0 * z.x;
			double ct = cos(tw); double st = sin(tw);
			double ty = z.y * ct - z.z * st;
			double tz = z.y * st + z.z * ct;
			z.y = ty; z.z = tz;
		}
		if (cpTwY != 0.0)
		{
			double tw = cpTwY * M_PI / 180.0 * z.y;
			double ct = cos(tw); double st = sin(tw);
			double tx = z.x * ct - z.z * st;
			double tz = z.x * st + z.z * ct;
			z.x = tx; z.z = tz;
		}
		if (cpTwZ != 0.0)
		{
			double tw = cpTwZ * M_PI / 180.0 * z.z;
			double ct = cos(tw); double st = sin(tw);
			double tx = z.x * ct - z.y * st;
			double ty = z.x * st + z.y * ct;
			z.x = tx; z.y = ty;
		}

		// 19-21. Bend per axis
		if (cpBnX != 0.0) { z.y += cpBnX * z.x * z.x; }
		if (cpBnY != 0.0) { z.z += cpBnY * z.y * z.y; }
		if (cpBnZ != 0.0) { z.x += cpBnZ * z.z * z.z; }

		// 22-24. Taper per axis
		if (cpTpX != 0.0) { z.y *= 1.0 + cpTpX * z.x; z.z *= 1.0 + cpTpX * z.x; }
		if (cpTpY != 0.0) { z.x *= 1.0 + cpTpY * z.y; z.z *= 1.0 + cpTpY * z.y; }
		if (cpTpZ != 0.0) { z.x *= 1.0 + cpTpZ * z.z; z.y *= 1.0 + cpTpZ * z.z; }

		// 25-26. Sphere fold
		if (cpSFR != 0.0)
		{
			double r2 = z.Dot(z);
			double minR2 = cpSFMR * cpSFMR;
			double fixedR2 = cpSFR * cpSFR;
			if (r2 < minR2)
			{
				double t = fixedR2 / minR2;
				z *= t; aux.DE *= t;
			}
			else if (r2 < fixedR2)
			{
				double t = fixedR2 / r2;
				z *= t; aux.DE *= t;
			}
		}

		// 27-29. Box fold per axis
		if (cpBFX != 0.0)
		{
			if (z.x > cpBFX) z.x = 2.0 * cpBFX - z.x;
			else if (z.x < -cpBFX) z.x = -2.0 * cpBFX - z.x;
		}
		if (cpBFY != 0.0)
		{
			if (z.y > cpBFY) z.y = 2.0 * cpBFY - z.y;
			else if (z.y < -cpBFY) z.y = -2.0 * cpBFY - z.y;
		}
		if (cpBFZ != 0.0)
		{
			if (z.z > cpBFZ) z.z = 2.0 * cpBFZ - z.z;
			else if (z.z < -cpBFZ) z.z = -2.0 * cpBFZ - z.z;
		}

		// 30-33. Sin warp
		if (cpSwA != 0.0)
		{
			z.x += cpSwA * sin(z.y * cpSwFX);
			z.y += cpSwA * sin(z.z * cpSwFY);
			z.z += cpSwA * sin(z.x * cpSwFZ);
		}

		// 34-35. Radial warp
		if (cpRdW != 0.0)
		{
			double r = z.Length();
			if (r > 1e-15)
			{
				double w = 1.0 + cpRdW * sin(r * cpRdF);
				z *= w; aux.DE *= fabs(w);
			}
		}

		// 36-37. Noise
		if (cpNsA != 0.0)
		{
			double hx = sin(z.x * cpNsF * 12.9898 + z.y * 78.233) * 43758.5453;
			hx = hx - floor(hx);
			double hy = sin(z.y * cpNsF * 12.9898 + z.z * 78.233) * 43758.5453;
			hy = hy - floor(hy);
			double hz = sin(z.z * cpNsF * 12.9898 + z.x * 78.233) * 43758.5453;
			hz = hz - floor(hz);
			z.x += (hx - 0.5) * cpNsA;
			z.y += (hy - 0.5) * cpNsA;
			z.z += (hz - 0.5) * cpNsA;
		}

		// 38-39. Iteration-dependent scale
		if (cpItS != 0.0)
		{
			double s = 1.0 + cpItS * sin(aux.i * cpItF * 0.5);
			z *= s; aux.DE *= fabs(s);
		}

		// 40-42. Mirror planes
		if (cpMrX != 0.0) { if (z.x < 0.0) z.x = -z.x + cpMrX; }
		if (cpMrY != 0.0) { if (z.y < 0.0) z.y = -z.y + cpMrY; }
		if (cpMrZ != 0.0) { if (z.z < 0.0) z.z = -z.z + cpMrZ; }

		// 43. Spherical inversion
		if (cpInvR != 0.0)
		{
			double r2 = z.Dot(z);
			if (r2 > 1e-15)
			{
				double invR2 = cpInvR * cpInvR / r2;
				z *= invR2; aux.DE *= invR2;
			}
		}

		// 44. C-pixel weight
		if (cpCpW != 0.0)
		{
			z += aux.const_c * cpCpW;
		}

		// 45-47. Coloring
		if (cpClD != 0.0) { aux.color += cpClD * z.Length(); }
		if (cpClA != 0.0) { aux.color += cpClA * fabs(atan2(z.y, z.x)); }
		if (cpClR != 0.0) { aux.color += cpClR * sqrt(z.x * z.x + z.y * z.y); }

		// 48-49. DE adjustment
		if (cpDET != 0.0) { aux.DE += cpDET; }
		if (cpDES != 1.0) { aux.DE *= cpDES; }

		// 50. Soft clip
		if (cpSCD != 0.0)
		{
			double r = z.Length();
			if (r > cpSCD)
			{
				double smooth = (cpSCS > 0.0) ? cpSCS : 0.1;
				double t = 1.0 - (r - cpSCD) / (r - cpSCD + smooth);
				z *= t; aux.DE *= t;
			}
		}
	}

	// GPU bypass: skip if all multipliers disabled
	if (fractal->transformCommon.functionEnabledBxFalse || fractal->transformCommon.functionEnabledByFalse || fractal->transformCommon.functionEnabledBzFalse || fractal->transformCommon.functionEnabledBwFalse || fractal->transformCommon.functionEnabledCzFalse)
	{
		double prevMultVal = 1.0;
		// === General Purpose Multiplier 1 ===
		if (fractal->transformCommon.functionEnabledBxFalse
				&& aux.i >= fractal->transformCommon.startIterationsB
				&& aux.i < fractal->transformCommon.stopIterationsB)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode1;
			double threshR = z.Length();
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold1)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold1))
			{
				double val = fractal->transformCommon.scale4;

				if (fractal->transformCommon.multiplierInverse1) val = (fabs(val) > 1e-15) ? (1.0 / val) : 1e15;

				int vmode = fractal->transformCommon.multiplierValueMode1;
				double range = (double)(fractal->transformCommon.stopIterationsB - fractal->transformCommon.startIterationsB);
				double ph = fractal->transformCommon.multiplierPhase1;
				if (range > 0 && vmode > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.startIterationsB) / range;
					double freq = fractal->transformCommon.multiplierFrequency1;
					if (vmode == 1) // Sine
					{
						val = 1.0 + (val - 1.0) * sin((t * freq + ph) * 2.0 * M_PI);
					}
					else if (vmode == 2) // Ramp
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 3) // Exponential
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + (val - 1.0) * (exp(t * freq) - 1.0) / (exp(freq) - 1.0);
					}
					else if (vmode == 4) // Triangle
					{
						double tri = 1.0 - 2.0 * fabs(fmod(t * freq + ph, 1.0) - 0.5);
						val = 1.0 + (val - 1.0) * tri;
					}
					else if (vmode == 5) // Square
					{
						val = (fmod(t * freq + ph, 1.0) < 0.5) ? val : 1.0;
					}
					else if (vmode == 6) // Smoothstep
					{
						t = qBound(0.0, t, 1.0);
						t = t * t * (3.0 - 2.0 * t);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 7) // Noise
					{
						int seed = aux.i * 73856093 + 1 * 19349663;
						seed = (seed ^ (seed >> 13)) * 1274126177;
						seed = seed ^ (seed >> 16);
						double noise = (double)(seed & 0xFFFF) / 65535.0;
						val = 1.0 + (val - 1.0) * noise;
					}
					else if (vmode == 8) // Ping-pong
					{
						double pp = fmod(t * freq + ph, 2.0);
						if (pp > 1.0) pp = 2.0 - pp;
						val = 1.0 + (val - 1.0) * pp;
					}
					else if (vmode == 9) // Stepped
					{
						double steps = freq;
						if (steps < 1.0) steps = 1.0;
						double st = floor(t * steps) / steps;
						val = 1.0 + (val - 1.0) * st;
					}
				}

				double w = fractal->transformCommon.multiplierWeight1;
				val = 1.0 + w * (val - 1.0);

				switch (fractal->transformCommon.multiplierMode1)
				{
					default:
					case 0:
					{
						double valY = fractal->transformCommon.multiplierScaleY1;
						double valZ = fractal->transformCommon.multiplierScaleZ1;
						if (valY == 0.0) valY = val;
						if (valZ == 0.0) valZ = val;
						z.x *= val; z.y *= valY; z.z *= valZ;
						aux.DE *= fabs(val);
						break;
					}
					case 1: z.x *= val; break;
					case 2: z.y *= val; break;
					case 3: z.z *= val; break;
					case 4: aux.DE *= val; break;
					case 5: aux.color *= val; break;
					case 6: z.w *= val; break;
					case 7: z.x *= val; z.y *= val; break;
					case 8: z.x *= val; z.z *= val; break;
					case 9: z.y *= val; z.z *= val; break;
					case 10: aux.color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 2 ===
		if (fractal->transformCommon.functionEnabledByFalse
				&& aux.i >= fractal->transformCommon.startIterationsC
				&& aux.i < fractal->transformCommon.stopIterationsC)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode2;
			double threshR = z.Length();
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold2)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold2))
			{
				double val = fractal->transformCommon.scale5;

				if (fractal->transformCommon.multiplierInverse2) val = (fabs(val) > 1e-15) ? (1.0 / val) : 1e15;

				int vmode = fractal->transformCommon.multiplierValueMode2;
				double range = (double)(fractal->transformCommon.stopIterationsC - fractal->transformCommon.startIterationsC);
				double ph = fractal->transformCommon.multiplierPhase2;
				if (range > 0 && vmode > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.startIterationsC) / range;
					double freq = fractal->transformCommon.multiplierFrequency2;
					if (vmode == 1) // Sine
					{
						val = 1.0 + (val - 1.0) * sin((t * freq + ph) * 2.0 * M_PI);
					}
					else if (vmode == 2) // Ramp
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 3) // Exponential
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + (val - 1.0) * (exp(t * freq) - 1.0) / (exp(freq) - 1.0);
					}
					else if (vmode == 4) // Triangle
					{
						double tri = 1.0 - 2.0 * fabs(fmod(t * freq + ph, 1.0) - 0.5);
						val = 1.0 + (val - 1.0) * tri;
					}
					else if (vmode == 5) // Square
					{
						val = (fmod(t * freq + ph, 1.0) < 0.5) ? val : 1.0;
					}
					else if (vmode == 6) // Smoothstep
					{
						t = qBound(0.0, t, 1.0);
						t = t * t * (3.0 - 2.0 * t);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 7) // Noise
					{
						int seed = aux.i * 73856093 + 2 * 19349663;
						seed = (seed ^ (seed >> 13)) * 1274126177;
						seed = seed ^ (seed >> 16);
						double noise = (double)(seed & 0xFFFF) / 65535.0;
						val = 1.0 + (val - 1.0) * noise;
					}
					else if (vmode == 8) // Ping-pong
					{
						double pp = fmod(t * freq + ph, 2.0);
						if (pp > 1.0) pp = 2.0 - pp;
						val = 1.0 + (val - 1.0) * pp;
					}
					else if (vmode == 9) // Stepped
					{
						double steps = freq;
						if (steps < 1.0) steps = 1.0;
						double st = floor(t * steps) / steps;
						val = 1.0 + (val - 1.0) * st;
					}
				}

				if (fractal->transformCommon.multiplierChain2) val *= prevMultVal;

				double w = fractal->transformCommon.multiplierWeight2;
				val = 1.0 + w * (val - 1.0);

				switch (fractal->transformCommon.multiplierMode2)
				{
					default:
					case 0:
					{
						double valY = fractal->transformCommon.multiplierScaleY2;
						double valZ = fractal->transformCommon.multiplierScaleZ2;
						if (valY == 0.0) valY = val;
						if (valZ == 0.0) valZ = val;
						z.x *= val; z.y *= valY; z.z *= valZ;
						aux.DE *= fabs(val);
						break;
					}
					case 1: z.x *= val; break;
					case 2: z.y *= val; break;
					case 3: z.z *= val; break;
					case 4: aux.DE *= val; break;
					case 5: aux.color *= val; break;
					case 6: z.w *= val; break;
					case 7: z.x *= val; z.y *= val; break;
					case 8: z.x *= val; z.z *= val; break;
					case 9: z.y *= val; z.z *= val; break;
					case 10: aux.color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 3 ===
		if (fractal->transformCommon.functionEnabledBzFalse
				&& aux.i >= fractal->transformCommon.startIterationsD
				&& aux.i < fractal->transformCommon.stopIterationsD)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode3;
			double threshR = z.Length();
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold3)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold3))
			{
				double val = fractal->transformCommon.scale6;

				if (fractal->transformCommon.multiplierInverse3) val = (fabs(val) > 1e-15) ? (1.0 / val) : 1e15;

				int vmode = fractal->transformCommon.multiplierValueMode3;
				double range = (double)(fractal->transformCommon.stopIterationsD - fractal->transformCommon.startIterationsD);
				double ph = fractal->transformCommon.multiplierPhase3;
				if (range > 0 && vmode > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.startIterationsD) / range;
					double freq = fractal->transformCommon.multiplierFrequency3;
					if (vmode == 1) // Sine
					{
						val = 1.0 + (val - 1.0) * sin((t * freq + ph) * 2.0 * M_PI);
					}
					else if (vmode == 2) // Ramp
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 3) // Exponential
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + (val - 1.0) * (exp(t * freq) - 1.0) / (exp(freq) - 1.0);
					}
					else if (vmode == 4) // Triangle
					{
						double tri = 1.0 - 2.0 * fabs(fmod(t * freq + ph, 1.0) - 0.5);
						val = 1.0 + (val - 1.0) * tri;
					}
					else if (vmode == 5) // Square
					{
						val = (fmod(t * freq + ph, 1.0) < 0.5) ? val : 1.0;
					}
					else if (vmode == 6) // Smoothstep
					{
						t = qBound(0.0, t, 1.0);
						t = t * t * (3.0 - 2.0 * t);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 7) // Noise
					{
						int seed = aux.i * 73856093 + 3 * 19349663;
						seed = (seed ^ (seed >> 13)) * 1274126177;
						seed = seed ^ (seed >> 16);
						double noise = (double)(seed & 0xFFFF) / 65535.0;
						val = 1.0 + (val - 1.0) * noise;
					}
					else if (vmode == 8) // Ping-pong
					{
						double pp = fmod(t * freq + ph, 2.0);
						if (pp > 1.0) pp = 2.0 - pp;
						val = 1.0 + (val - 1.0) * pp;
					}
					else if (vmode == 9) // Stepped
					{
						double steps = freq;
						if (steps < 1.0) steps = 1.0;
						double st = floor(t * steps) / steps;
						val = 1.0 + (val - 1.0) * st;
					}
				}

				if (fractal->transformCommon.multiplierChain3) val *= prevMultVal;

				double w = fractal->transformCommon.multiplierWeight3;
				val = 1.0 + w * (val - 1.0);

				switch (fractal->transformCommon.multiplierMode3)
				{
					default:
					case 0:
					{
						double valY = fractal->transformCommon.multiplierScaleY3;
						double valZ = fractal->transformCommon.multiplierScaleZ3;
						if (valY == 0.0) valY = val;
						if (valZ == 0.0) valZ = val;
						z.x *= val; z.y *= valY; z.z *= valZ;
						aux.DE *= fabs(val);
						break;
					}
					case 1: z.x *= val; break;
					case 2: z.y *= val; break;
					case 3: z.z *= val; break;
					case 4: aux.DE *= val; break;
					case 5: aux.color *= val; break;
					case 6: z.w *= val; break;
					case 7: z.x *= val; z.y *= val; break;
					case 8: z.x *= val; z.z *= val; break;
					case 9: z.y *= val; z.z *= val; break;
					case 10: aux.color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 4 ===
		if (fractal->transformCommon.functionEnabledBwFalse
				&& aux.i >= fractal->transformCommon.startIterationsE
				&& aux.i < fractal->transformCommon.stopIterationsE)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode4;
			double threshR = z.Length();
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold4)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold4))
			{
				double val = fractal->transformCommon.scale8;

				if (fractal->transformCommon.multiplierInverse4) val = (fabs(val) > 1e-15) ? (1.0 / val) : 1e15;

				int vmode = fractal->transformCommon.multiplierValueMode4;
				double range = (double)(fractal->transformCommon.stopIterationsE - fractal->transformCommon.startIterationsE);
				double ph = fractal->transformCommon.multiplierPhase4;
				if (range > 0 && vmode > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.startIterationsE) / range;
					double freq = fractal->transformCommon.multiplierFrequency4;
					if (vmode == 1) // Sine
					{
						val = 1.0 + (val - 1.0) * sin((t * freq + ph) * 2.0 * M_PI);
					}
					else if (vmode == 2) // Ramp
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 3) // Exponential
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + (val - 1.0) * (exp(t * freq) - 1.0) / (exp(freq) - 1.0);
					}
					else if (vmode == 4) // Triangle
					{
						double tri = 1.0 - 2.0 * fabs(fmod(t * freq + ph, 1.0) - 0.5);
						val = 1.0 + (val - 1.0) * tri;
					}
					else if (vmode == 5) // Square
					{
						val = (fmod(t * freq + ph, 1.0) < 0.5) ? val : 1.0;
					}
					else if (vmode == 6) // Smoothstep
					{
						t = qBound(0.0, t, 1.0);
						t = t * t * (3.0 - 2.0 * t);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 7) // Noise
					{
						int seed = aux.i * 73856093 + 4 * 19349663;
						seed = (seed ^ (seed >> 13)) * 1274126177;
						seed = seed ^ (seed >> 16);
						double noise = (double)(seed & 0xFFFF) / 65535.0;
						val = 1.0 + (val - 1.0) * noise;
					}
					else if (vmode == 8) // Ping-pong
					{
						double pp = fmod(t * freq + ph, 2.0);
						if (pp > 1.0) pp = 2.0 - pp;
						val = 1.0 + (val - 1.0) * pp;
					}
					else if (vmode == 9) // Stepped
					{
						double steps = freq;
						if (steps < 1.0) steps = 1.0;
						double st = floor(t * steps) / steps;
						val = 1.0 + (val - 1.0) * st;
					}
				}

				if (fractal->transformCommon.multiplierChain4) val *= prevMultVal;

				double w = fractal->transformCommon.multiplierWeight4;
				val = 1.0 + w * (val - 1.0);

				switch (fractal->transformCommon.multiplierMode4)
				{
					default:
					case 0:
					{
						double valY = fractal->transformCommon.multiplierScaleY4;
						double valZ = fractal->transformCommon.multiplierScaleZ4;
						if (valY == 0.0) valY = val;
						if (valZ == 0.0) valZ = val;
						z.x *= val; z.y *= valY; z.z *= valZ;
						aux.DE *= fabs(val);
						break;
					}
					case 1: z.x *= val; break;
					case 2: z.y *= val; break;
					case 3: z.z *= val; break;
					case 4: aux.DE *= val; break;
					case 5: aux.color *= val; break;
					case 6: z.w *= val; break;
					case 7: z.x *= val; z.y *= val; break;
					case 8: z.x *= val; z.z *= val; break;
					case 9: z.y *= val; z.z *= val; break;
					case 10: aux.color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 5 ===
		if (fractal->transformCommon.functionEnabledCzFalse
				&& aux.i >= fractal->transformCommon.startIterationsF
				&& aux.i < fractal->transformCommon.stopIterationsF)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode5;
			double threshR = z.Length();
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold5)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold5))
			{
				double val = fractal->transformCommon.scale16;

				if (fractal->transformCommon.multiplierInverse5) val = (fabs(val) > 1e-15) ? (1.0 / val) : 1e15;

				int vmode = fractal->transformCommon.multiplierValueMode5;
				double range = (double)(fractal->transformCommon.stopIterationsF - fractal->transformCommon.startIterationsF);
				double ph = fractal->transformCommon.multiplierPhase5;
				if (range > 0 && vmode > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.startIterationsF) / range;
					double freq = fractal->transformCommon.multiplierFrequency5;
					if (vmode == 1) // Sine
					{
						val = 1.0 + (val - 1.0) * sin((t * freq + ph) * 2.0 * M_PI);
					}
					else if (vmode == 2) // Ramp
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 3) // Exponential
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + (val - 1.0) * (exp(t * freq) - 1.0) / (exp(freq) - 1.0);
					}
					else if (vmode == 4) // Triangle
					{
						double tri = 1.0 - 2.0 * fabs(fmod(t * freq + ph, 1.0) - 0.5);
						val = 1.0 + (val - 1.0) * tri;
					}
					else if (vmode == 5) // Square
					{
						val = (fmod(t * freq + ph, 1.0) < 0.5) ? val : 1.0;
					}
					else if (vmode == 6) // Smoothstep
					{
						t = qBound(0.0, t, 1.0);
						t = t * t * (3.0 - 2.0 * t);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 7) // Noise
					{
						int seed = aux.i * 73856093 + 5 * 19349663;
						seed = (seed ^ (seed >> 13)) * 1274126177;
						seed = seed ^ (seed >> 16);
						double noise = (double)(seed & 0xFFFF) / 65535.0;
						val = 1.0 + (val - 1.0) * noise;
					}
					else if (vmode == 8) // Ping-pong
					{
						double pp = fmod(t * freq + ph, 2.0);
						if (pp > 1.0) pp = 2.0 - pp;
						val = 1.0 + (val - 1.0) * pp;
					}
					else if (vmode == 9) // Stepped
					{
						double steps = freq;
						if (steps < 1.0) steps = 1.0;
						double st = floor(t * steps) / steps;
						val = 1.0 + (val - 1.0) * st;
					}
				}

				if (fractal->transformCommon.multiplierChain5) val *= prevMultVal;

				double w = fractal->transformCommon.multiplierWeight5;
				val = 1.0 + w * (val - 1.0);

				switch (fractal->transformCommon.multiplierMode5)
				{
					default:
					case 0:
					{
						double valY = fractal->transformCommon.multiplierScaleY5;
						double valZ = fractal->transformCommon.multiplierScaleZ5;
						if (valY == 0.0) valY = val;
						if (valZ == 0.0) valZ = val;
						z.x *= val; z.y *= valY; z.z *= valZ;
						aux.DE *= fabs(val);
						break;
					}
					case 1: z.x *= val; break;
					case 2: z.y *= val; break;
					case 3: z.z *= val; break;
					case 4: aux.DE *= val; break;
					case 5: aux.color *= val; break;
					case 6: z.w *= val; break;
					case 7: z.x *= val; z.y *= val; break;
					case 8: z.x *= val; z.z *= val; break;
					case 9: z.y *= val; z.z *= val; break;
					case 10: aux.color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}
	}

}
