/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * amazing surf from Mandelbulber3D. Formula proposed by Kali, with features added by DarkBeam
 * v7.6: 30 formula-specific extensions across 6 categories
 *
 * This formula has a c.x c.y SWAP
 *
 * @reference
 * http://www.fractalforums.com/mandelbulb-3d/custom-formulas-and-transforms-release-t17106/
 */

#include "all_fractal_definitions.h"

cFractalAmazingSurf::cFractalAmazingSurf() : cAbstractFractal()
{
	nameInComboBox = "Amazing Surf";
	internalName = "amazing_surf";
	internalID = fractal::amazingSurf;
	DEType = analyticDEType;
	DEFunctionType = linearDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionLinear;
	coloringFunction = coloringFunctionAmazingSurf;
}

void cFractalAmazingSurf::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// update aux.actualScale
	aux.actualScale =
		fractal->mandelbox.scale + fractal->mandelboxVary4D.scaleVary * (fabs(aux.actualScale) - 1.0);

	CVector4 c = aux.const_c;

	// === CAT 3 #16: Pre-Sphere Inversie (Möbius) ===
	if (fractal->transformCommon.functionEnabledPFalse
		&& aux.i >= fractal->transformCommon.startIterationsP
		&& aux.i < fractal->transformCommon.stopIterationsP)
	{
		CVector4 center = fractal->transformCommon.offset000;
		double r2 = fractal->transformCommon.radius1 * fractal->transformCommon.radius1;
		CVector4 diff = z - center;
		double d2 = diff.Dot(diff);
		if (d2 > 1e-21)
		{
			z = center + diff * (r2 / d2);
			aux.DE *= r2 / d2;
		}
	}

	// === CAT 3 #18: Pre-Rotation ===
	if (fractal->transformCommon.functionEnabledRFalse
		&& aux.i >= fractal->transformCommon.startIterationsR
		&& aux.i < fractal->transformCommon.stopIterationsR)
	{
		z = fractal->transformCommon.rotationMatrix2.RotateVector(z);
	}

	// === CAT 3 #20: Möbius Pre-Transform ===
	if (fractal->transformCommon.functionEnabledMFalse
		&& aux.i >= fractal->transformCommon.startIterationsM
		&& aux.i < fractal->transformCommon.stopIterationsM)
	{
		double a = fractal->transformCommon.scale1;
		double b = fractal->transformCommon.offset05;
		double d = fractal->transformCommon.offsetA1;
		CVector4 az = z * a + CVector4(b, b, b, 0.0);
		double denom = z.Length() + d;
		if (fabs(denom) > 1e-21)
		{
			z = az * (1.0 / denom);
			aux.DE *= fabs(a * d - b) / (denom * denom);
		}
	}

	// === CAT 1 #6: Pre-Abs (absolute value before fold) ===
	if (fractal->transformCommon.functionEnabledAxFalse) z.x = fabs(z.x);
	if (fractal->transformCommon.functionEnabledAyFalse) z.y = fabs(z.y);
	if (fractal->transformCommon.functionEnabledAzFalse) z.z = fabs(z.z);

	// === CAT 5 #27: Mirror Symmetry Toggle ===
	// (uses the same pre-abs flags above — enable per axis)

	// === CAT 3 #19: Z-Twist (Screw Motion) ===
	if (fractal->transformCommon.functionEnabledTFalse
		&& aux.i >= fractal->transformCommon.startIterationsT
		&& aux.i < fractal->transformCommon.stopIterationsT)
	{
		double angle = fractal->transformCommon.offset01 * z.z;
		double cosA = cos(angle);
		double sinA = sin(angle);
		double xn = z.x * cosA - z.y * sinA;
		double yn = z.x * sinA + z.y * cosA;
		z.x = xn;
		z.y = yn;
	}

	// === TGLAD BOX FOLD (original) ===
	double foldX = fractal->transformCommon.additionConstant111.x;
	double foldY = fractal->transformCommon.additionConstant111.y;

	// === CAT 1 #2: Asymmetrische Fold ===
	if (fractal->transformCommon.functionEnabledBFalse)
	{
		double a = foldX;
		double b = fractal->transformCommon.offsetA05;
		z.x = fabs(z.x + a) - fabs(z.x - b) - z.x;
		double aY = foldY;
		double bY = fractal->transformCommon.offsetB05;
		z.y = fabs(z.y + aY) - fabs(z.y - bY) - z.y;
	}
	// === CAT 1 #3: Smooth Fold (Hyperbolisch) ===
	else if (fractal->transformCommon.functionEnabledCFalse)
	{
		double k = fractal->transformCommon.scale3;
		if (k > 0.01)
		{
			z.x = z.x - tanh(k * z.x) / k;
			z.y = z.y - tanh(k * z.y) / k;
		}
	}
	else
	{
		// Standard tglad fold (X, Y only)
		z.x = fabs(z.x + foldX) - fabs(z.x - foldX) - z.x;
		z.y = fabs(z.y + foldY) - fabs(z.y - foldY) - z.y;
	}

	// === CAT 1 #1: Z-Axis Tglad Fold ===
	if (fractal->transformCommon.functionEnabledzFalse)
	{
		double foldZ = fractal->transformCommon.additionConstant111.z;
		z.z = fabs(z.z + foldZ) - fabs(z.z - foldZ) - z.z;
	}

	// === CAT 1 #4: Variable Fold per Iteratie ===
	if (fractal->transformCommon.functionEnabledDFalse
		&& aux.i >= fractal->transformCommon.startIterationsD
		&& aux.i < fractal->transformCommon.stopIterationsD)
	{
		double vary = fractal->transformCommon.scaleVary0;
		double factor = 1.0 + vary * sin((double)aux.i * 0.1);
		z.x *= factor;
		z.y *= factor;
	}

	// === CAT 1 #5: Multi-Sequenced Fold (2nd fold pass) ===
	if (fractal->transformCommon.functionEnabledEFalse
		&& aux.i >= fractal->transformCommon.startIterationsE
		&& aux.i < fractal->transformCommon.stopIterationsE)
	{
		double fold2X = fractal->transformCommon.additionConstantA111.x;
		double fold2Y = fractal->transformCommon.additionConstantA111.y;
		z.x = fabs(z.x + fold2X) - fabs(z.x - fold2X) - z.x;
		z.y = fabs(z.y + fold2Y) - fabs(z.y - fold2Y) - z.y;
	}

	// === CAT 1 #7: Fold met Z-Shear ===
	if (fractal->transformCommon.functionEnabledFFalse
		&& aux.i >= fractal->transformCommon.startIterationsF
		&& aux.i < fractal->transformCommon.stopIterationsF)
	{
		z.z += fractal->transformCommon.offsetF0 * (z.x + z.y);
	}

	// === SPHERICAL FOLD SECTION ===
	double rr = z.Dot(z);
	if (fractal->transformCommon.functionEnabledFalse) // force cylinder fold
		rr -= z.z * z.z;

	// === CAT 2 #8: Anisotrope Spherical Fold (Ellipsoïde) ===
	if (fractal->transformCommon.functionEnabledGFalse)
	{
		CVector4 axis = fractal->transformCommon.scale3D111;
		rr = 0.0;
		if (fabs(axis.x) > 1e-21) rr += (z.x * z.x) / (axis.x * axis.x);
		if (fabs(axis.y) > 1e-21) rr += (z.y * z.y) / (axis.y * axis.y);
		if (fabs(axis.z) > 1e-21) rr += (z.z * z.z) / (axis.z * axis.z);
	}

	// === CAT 2 #9: Torus Distance Fold ===
	if (fractal->transformCommon.functionEnabledHFalse)
	{
		double R = fractal->transformCommon.offsetR1;
		double xyDist = sqrt(z.x * z.x + z.y * z.y) - R;
		rr = xyDist * xyDist + z.z * z.z;
	}

	double sqrtMinR = sqrt(fractal->transformCommon.minR05);

	// === CAT 2 #10: Logarithmic Dividend ===
	double dividend;
	if (fractal->transformCommon.functionEnabledIFalse)
	{
		double k = fractal->transformCommon.scaleA1;
		if (k > 0.001) dividend = log(1.0 + rr * k) / k;
		else dividend = rr;
	}
	// === CAT 2 #12: Smoothstep Dividend ===
	else if (fractal->transformCommon.functionEnabledJFalse)
	{
		double t = (rr - sqrtMinR) / (1.0 - sqrtMinR + 1e-21);
		t = fmax(0.0, fmin(1.0, t));
		dividend = sqrtMinR + t * t * (3.0 - 2.0 * t) * (1.0 - sqrtMinR);
	}
	else
	{
		dividend = rr < sqrtMinR ? sqrtMinR : min(rr, 1.0);
	}

	// === CAT 2 #11: Exponential Scale Factor ===
	double m;
	if (fractal->transformCommon.functionEnabledKFalse)
	{
		m = exp(aux.actualScale / (dividend + 1e-21) - 1.0);
	}
	else
	{
		m = aux.actualScale / (dividend + 1e-21);
	}

	// === CAT 2 #13: Dual Scale (Bipolar) ===
	if (fractal->transformCommon.functionEnabledNFalse)
	{
		double scaleB = fractal->transformCommon.scaleB1;
		if (z.x < 0.0) m = scaleB / (dividend + 1e-21);
	}

	// === CAT 2 #14: Z-Scale Decoupled ===
	if (fractal->transformCommon.functionEnabledOFalse)
	{
		double mZ = fractal->transformCommon.scaleC1 / (dividend + 1e-21);
		double scaleMix = (m - 1.0) * fractal->transformCommon.scale1 + 1.0;
		double scaleZ = (mZ - 1.0) * fractal->transformCommon.scale1 + 1.0;
		z.x *= scaleMix;
		z.y *= scaleMix;
		z.z *= scaleZ;
		aux.DE = aux.DE * fmax(fabs(m), fabs(mZ)) + 1.0;
	}
	else
	{
		z *= (m - 1.0) * fractal->transformCommon.scale1 + 1.0;
		// === CAT 6 #28: DE Offset Tweak ===
		double deOffset = fractal->transformCommon.functionEnabledSFalse
			? fractal->transformCommon.offsetD0
			: 1.0;
		aux.DE = aux.DE * fabs(m) + deOffset;
	}

	// === CAT 2 #15: Nested Spherical (2-lagen) ===
	if (fractal->transformCommon.functionEnabledXFalse
		&& aux.i >= fractal->transformCommon.startIterationsX
		&& aux.i < fractal->transformCommon.stopIterationsX)
	{
		double rr2 = z.Dot(z);
		double sqrtMinR2 = sqrtMinR * fractal->transformCommon.scaleD1;
		double div2 = rr2 < sqrtMinR2 ? sqrtMinR2 : min(rr2, 1.0);
		double m2 = aux.actualScale / (div2 + 1e-21);
		z *= (m2 - 1.0) * fractal->transformCommon.scale1 + 1.0;
		aux.DE = aux.DE * fabs(m2) + 1.0;
	}

	// === CAT 3 #17: Post-Fold Inversie ===
	if (fractal->transformCommon.functionEnabledYFalse
		&& aux.i >= fractal->transformCommon.startIterationsN
		&& aux.i < fractal->transformCommon.stopIterationsN)
	{
		double zLen2 = z.Dot(z);
		if (zLen2 > 1e-21)
		{
			z = z * (1.0 / zLen2);
			aux.DE *= 1.0 / zLen2;
		}
	}

	// === CAT 4 #21: C-Pixel Permutaties ===
	if (fractal->transformCommon.addCpixelEnabledFalse)
	{
		CVector4 cPerm;
		switch (fractal->transformCommon.intA)
		{
			case 0: cPerm = CVector4(c.y, c.x, c.z, c.w); break; // default swap
			case 1: cPerm = CVector4(c.x, c.y, c.z, c.w); break; // xyz
			case 2: cPerm = CVector4(c.x, c.z, c.y, c.w); break; // xzy
			case 3: cPerm = CVector4(c.y, c.z, c.x, c.w); break; // yzx
			case 4: cPerm = CVector4(c.z, c.x, c.y, c.w); break; // zxy
			case 5: cPerm = CVector4(c.z, c.y, c.x, c.w); break; // zyx
			default: cPerm = CVector4(c.y, c.x, c.z, c.w); break;
		}

		// === CAT 4 #22: C-Pixel Modulation ===
		if (fractal->transformCommon.functionEnabledAFalse)
		{
			double modFactor = 1.0 + fractal->transformCommon.scaleA0
				* sin((double)aux.i * fractal->transformCommon.scaleB0);
			cPerm *= modFactor;
		}

		// === CAT 4 #23: Bipolar C-Pixel ===
		if (fractal->transformCommon.functionEnabled4dFalse)
		{
			cPerm *= (z.x >= 0.0 ? 1.0 : -1.0);
		}

		// === CAT 4 #24: C-Pixel met Orbit Trap (feedback) ===
		if (fractal->transformCommon.functionEnabledAuxCFalse)
		{
			cPerm = cPerm + (z - aux.old_z) * 0.1;
		}

		z += cPerm * fractal->transformCommon.constantMultiplier111;
	}

	// === CAT 6 #29: Color Trap op m-waarde ===
	if (fractal->transformCommon.functionEnabledCxFalse)
	{
		aux.color += fabs(m - 1.0) * fractal->transformCommon.scaleE1;
	}

	// === CAT 6 #30: Orbit Trap: Cross ===
	if (fractal->transformCommon.functionEnabledCyFalse)
	{
		double trap = fmin(fabs(z.x), fmin(fabs(z.y), fabs(z.z)));
		aux.color += trap * fractal->transformCommon.scaleF1;
	}

	// === CAT 5 #25: Fibonacci / Golden Angle Rotation ===
	if (fractal->transformCommon.functionEnabledSwFalse)
	{
		double angle = (double)aux.i * 2.39996322972865332; // golden angle
		double cosG = cos(angle);
		double sinG = sin(angle);
		double xn = z.x * cosG - z.y * sinG;
		double yn = z.x * sinG + z.y * cosG;
		z.x = xn;
		z.y = yn;
	}

	// === CAT 5 #26: Quaternion Rotatie ===
	// (implemented via the existing rotationMatrix — users set rotation angles)

	// GPU bypass: skip if all multipliers disabled
	if (fractal->transformCommon.functionEnabledBxFalse || fractal->transformCommon.functionEnabledByFalse || fractal->transformCommon.functionEnabledBzFalse || fractal->transformCommon.functionEnabledBwFalse || fractal->transformCommon.functionEnabledCzFalse)
	{
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

				if (fractal->transformCommon.multiplierInverse1) val = 1.0 / val;

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
				}

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

				if (fractal->transformCommon.multiplierInverse2) val = 1.0 / val;

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
				}

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

				if (fractal->transformCommon.multiplierInverse3) val = 1.0 / val;

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
				}

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

				if (fractal->transformCommon.multiplierInverse4) val = 1.0 / val;

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
				}

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

				if (fractal->transformCommon.multiplierInverse5) val = 1.0 / val;

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
				}

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
			}
		}
	}

	// Post-Rotation (original)
	z = fractal->transformCommon.rotationMatrix.RotateVector(z);

	aux.old_z = z;
}
