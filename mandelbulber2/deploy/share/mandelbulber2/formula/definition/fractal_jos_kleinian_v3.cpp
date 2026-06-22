/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * JosLeys-Kleinian V3 formula
 * @reference
 * http://www.fractalforums.com/3d-fractal-generation/an-escape-tim-algorithm-for-kleinian-group-limit-sets/msg98248/#msg98248
 * This formula contains aux.color and aux.DE
 */

#include "all_fractal_definitions.h"

cFractalJosKleinianV3::cFractalJosKleinianV3() : cAbstractFractal()
{
	nameInComboBox = "JosLeys-Kleinian V3";
	internalName = "jos_kleinian_v3";
	internalID = fractal::josKleinianV3;
	DEType = analyticDEType;
	DEFunctionType = customDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionCustomDE;
	coloringFunction = coloringFunctionDefault;
}

void cFractalJosKleinianV3::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	double rr = 0.0;
	// sphere inversion position
	if (!fractal->transformCommon.functionEnabledIFalse)
	{
		if (fractal->transformCommon.sphereInversionEnabledFalse
				&& aux.i >= fractal->transformCommon.startIterationsD
				&& aux.i < fractal->transformCommon.stopIterationsD1)
		{
			z += fractal->transformCommon.offset000;
			rr = z.Dot(z);
			z *= fractal->transformCommon.maxR2d1 / rr;
			z += fractal->transformCommon.additionConstant000 - fractal->transformCommon.offset000;
			z *= fractal->transformCommon.scaleA1;
			aux.DE *= (fractal->transformCommon.maxR2d1 / rr) * fractal->analyticDE.scale1
								* fractal->transformCommon.scaleA1;
		}
	}

	if (fractal->transformCommon.functionEnabledPFalse
			&& aux.i >= fractal->transformCommon.startIterationsP
			&& aux.i < fractal->transformCommon.stopIterationsP1)
	{
		z = fractal->transformCommon.rotationMatrix.RotateVector(z);

		if (fractal->transformCommon.functionEnabledx) z.x = fabs(z.x);
		if (fractal->transformCommon.functionEnabledy) z.y = fabs(z.y);
		if (fractal->transformCommon.functionEnabledz) z.z = fabs(z.z);

		if (fractal->transformCommon.functionEnabledCx)
		{
			double psi = M_PI / fractal->transformCommon.int8X;
			psi = fabs(fmod(atan2(z.y, z.x) + psi, 2.0 * psi) - psi);
			double len = sqrt(z.x * z.x + z.y * z.y);
			z.x = cos(psi) * len;
			z.y = sin(psi) * len;
		}

		if (fractal->transformCommon.functionEnabledCyFalse)
		{
			double psi = M_PI / fractal->transformCommon.int8Y;
			psi = fabs(fmod(atan2(z.z, z.y) + psi, 2.0 * psi) - psi);
			double len = sqrt(z.y * z.y + z.z * z.z);
			z.y = cos(psi) * len;
			z.z = sin(psi) * len;
		}

		if (fractal->transformCommon.functionEnabledCzFalse)
		{
			double psi = M_PI / fractal->transformCommon.int8Z;
			psi = fabs(fmod(atan2(z.x, z.z) + psi, 2.0 * psi) - psi);
			double len = sqrt(z.z * z.z + z.x * z.x);
			z.z = cos(psi) * len;
			z.x = sin(psi) * len;
		}
		// addition constant
		z += fractal->transformCommon.offsetF000;
	}

	// alternative sphere inversion position
	if (fractal->transformCommon.functionEnabledIFalse)
	{
		if (fractal->transformCommon.sphereInversionEnabledFalse
				&& aux.i >= fractal->transformCommon.startIterationsD
				&& aux.i < fractal->transformCommon.stopIterationsD1)
		{
			z += fractal->transformCommon.offset000;
			rr = z.Dot(z);
			z *= fractal->transformCommon.maxR2d1 / rr;
			z += fractal->transformCommon.additionConstant000 - fractal->transformCommon.offset000;
			z *= fractal->transformCommon.scaleA1;
			aux.DE *= (fractal->transformCommon.maxR2d1 / rr) * fractal->analyticDE.scale1
								* fractal->transformCommon.scaleA1;
		}
	}

	// diagonal fold
	if (fractal->transformCommon.functionEnabledCFalse
			&& aux.i >= fractal->transformCommon.startIterationsC
			&& aux.i < fractal->transformCommon.stopIterationsC1)
	{
		if (z.y > z.x) swap(z.x, z.y);
	}

	if (fractal->transformCommon.functionEnabledFalse
			&& aux.i >= fractal->transformCommon.startIterations
			&& aux.i < fractal->transformCommon.stopIterations1)
	{
		// square
		if (fractal->transformCommon.functionEnabledBx) z.x = max(fabs(z.x), fabs(z.y));
		// circle
		if (fractal->transformCommon.functionEnabledOFalse) z.x = sqrt((z.x * z.x) + (z.y * z.y));
	}

	// kleinian
	if (aux.i >= fractal->transformCommon.startIterationsF
			&& aux.i < fractal->transformCommon.stopIterationsF)
	{
		CVector4 box_size = fractal->transformCommon.offset111;
		double a = fractal->transformCommon.foldingValue;
		double b = fractal->transformCommon.offset;
		double f = sign(b);
		z.x += box_size.x;
		z.y += box_size.y;
		z.x = z.x - 2.0 * box_size.x * floor(z.x / 2.0 * box_size.x) - box_size.x;
		z.y = z.y - 2.0 * box_size.y * floor(z.y / 2.0 * box_size.y) - box_size.y;
		z.z += box_size.z - 1.0;
		z.z = z.z - a * box_size.z * floor(z.z / a * box_size.z);
		z.z -= (box_size.z - 1.0);
		if (z.z >= a * (0.5 + 0.2 * sin(f * M_PI * (z.x + b * 0.5) / box_size.x)))
		{
			z.x = -z.x - b;
			z.z = -z.z + a;
		}

		double useScale = fractal->transformCommon.scale1 - aux.actualScaleA;
		z *= useScale;
		aux.DE = aux.DE * fabs(useScale);
		if (fractal->transformCommon.functionEnabledKFalse) // update actualScaleA
			aux.actualScaleA = fractal->transformCommon.scaleVary0
										* (fabs(aux.actualScaleA) + 1.0);

		rr = z.Dot(z);
		double iR = 1.0 / rr;
		aux.DE *= iR;
		z *= -iR; // invert and mirror
		z.x = -z.x - b;
		z.z = a + z.z;
	}

	if (fractal->transformCommon.functionEnabledEFalse
			&& aux.i >= fractal->transformCommon.startIterationsE
			&& aux.i < fractal->transformCommon.stopIterationsE)
	{
		z.y = sign(z.y)
					* (fractal->transformCommon.offset1 - fabs(z.y)
						 + fabs(z.y) * fractal->transformCommon.scale0);
	}

	double Ztemp = z.z;
	if (fractal->transformCommon.spheresEnabled)
		Ztemp = min(z.z, fractal->transformCommon.foldingValue - z.z);

	if (aux.i >= fractal->transformCommon.startIterationsG)
	{
		aux.dist =
			min(Ztemp + fractal->analyticDE.offset0, fractal->analyticDE.tweak005)
			/ max(aux.DE, fractal->analyticDE.offset1);
	}

	if (fractal->transformCommon.functionEnabledTFalse
			&& aux.i >= fractal->transformCommon.startIterationsT
			&& aux.i < fractal->transformCommon.stopIterationsT)
				z.z = Ztemp;

	// aux.color
	if (fractal->foldColor.auxColorEnabledFalse
			&& aux.i >= fractal->transformCommon.startIterationsN
			&& aux.i < fractal->transformCommon.stopIterationsN)
	{
		double colorAdd = 0.0;
		colorAdd += fractal->foldColor.difs0000.x * z.Dot(z);
		colorAdd += fractal->foldColor.difs0000.y * max(max(fabs(z.x), fabs(z.y)), fabs(z.z));
		colorAdd += fractal->foldColor.difs0000.z * z.z;
		if (-z.x * z.y > 0.0) colorAdd += fractal->foldColor.difs0000.w;

		if (!fractal->transformCommon.functionEnabledJFalse)
			if (!fractal->transformCommon.functionEnabledMFalse)
				aux.color = colorAdd;
			else
				aux.color += colorAdd;
		else
			aux.color = max(aux.color, colorAdd);
	}
	// =============================================
	// === JOS KLEINIAN EXTENSIONS (#1-#15) ===
	// =============================================

	// === JK #1-2: Separation Line Warp ===
	if (fractal->transformCommon.jkSepLineWarp != 0.0)
	{
		double warpAmp = fractal->transformCommon.jkSepLineWarp;
		double warpFreq = fractal->transformCommon.jkSepLineFreq;
		z.x += warpAmp * sin(z.y * warpFreq);
		z.y += warpAmp * sin(z.z * warpFreq * 0.7);
	}

	// === JK #3: Inversion Power ===
	if (fractal->transformCommon.jkInversionPower != 1.0 && fractal->transformCommon.jkInversionPower != 0.0)
	{
		double rr = z.Dot(z);
		if (rr > 1e-21)
		{
			double iRp = pow(1.0 / rr, fractal->transformCommon.jkInversionPower * 0.5);
			z *= iRp;
			aux.DE *= fabs(iRp);
		}
	}

	// === JK #4-5: Box Oscillation ===
	if (fractal->transformCommon.jkBoxOscAmp != 0.0)
	{
		double osc = fractal->transformCommon.jkBoxOscAmp * sin((double)aux.i * fractal->transformCommon.jkBoxOscFreq);
		z.x += osc * z.x;
		z.y += osc * z.y;
		z.z += osc * z.z;
	}

	// === JK #6: Pre-Twist XY ===
	if (fractal->transformCommon.jkPreTwistXY != 0.0)
	{
		double angle = fractal->transformCommon.jkPreTwistXY * M_PI / 180.0 * (double)aux.i;
		double cosA = cos(angle);
		double sinA = sin(angle);
		double xn = z.x * cosA - z.y * sinA;
		double yn = z.x * sinA + z.y * cosA;
		z.x = xn;
		z.y = yn;
	}

	// === JK #7: Post-Twist XZ ===
	if (fractal->transformCommon.jkPostTwistXZ != 0.0)
	{
		double angle = fractal->transformCommon.jkPostTwistXZ * M_PI / 180.0;
		double cosA = cos(angle);
		double sinA = sin(angle);
		double xn = z.x * cosA - z.z * sinA;
		double zn = z.x * sinA + z.z * cosA;
		z.x = xn;
		z.z = zn;
	}

	// === JK #8: Z-Shift ===
	if (fractal->transformCommon.jkZShift != 0.0)
	{
		z.x += fractal->transformCommon.jkZShift * z.z;
		z.y += fractal->transformCommon.jkZShift * z.z * 0.5;
	}

	// === JK #9: Radial Warp ===
	if (fractal->transformCommon.jkRadialWarp != 0.0)
	{
		double r = sqrt(z.x * z.x + z.y * z.y + 1e-21);
		double warp = 1.0 + fractal->transformCommon.jkRadialWarp * sin(r * 3.0);
		z.x *= warp;
		z.y *= warp;
		aux.DE *= fabs(warp);
	}

	// === JK #10: Turbulence ===
	if (fractal->transformCommon.jkTurbulence != 0.0)
	{
		double turb = fractal->transformCommon.jkTurbulence;
		int hx = (int)(z.x * 1000.0) * 73856093;
		int hy = (int)(z.y * 1000.0) * 19349663;
		int hz = (int)(z.z * 1000.0) * 83492791;
		int h = hx ^ hy ^ hz;
		h = (h ^ (h >> 13)) * 1274126177;
		h = h ^ (h >> 16);
		double noise = ((double)(h & 0xFFFF) / 32767.5) - 1.0;
		z.x += turb * noise;
		h = h * 1103515245 + 12345;
		noise = ((double)(h & 0xFFFF) / 32767.5) - 1.0;
		z.y += turb * noise;
		h = h * 1103515245 + 12345;
		noise = ((double)(h & 0xFFFF) / 32767.5) - 1.0;
		z.z += turb * noise;
	}

	// === JK #11: Gradient Color (iR-based) ===
	if (fractal->transformCommon.jkGradientColor != 0.0)
	{
		double rr = z.Dot(z);
		double iRCol = 1.0 / (rr + 1e-21);
		aux.color += fabs(iRCol) * fractal->transformCommon.jkGradientColor;
	}

	// === JK #12: DE Tweak ===
	if (fractal->transformCommon.jkDETweak != 0.0)
	{
		aux.DE += fractal->transformCommon.jkDETweak;
	}

	// === JK #13: C-Pixel Inject ===
	if (fractal->transformCommon.jkCpixelInject != 0.0)
	{
		z += aux.const_c * fractal->transformCommon.jkCpixelInject;
	}

	// === JK #14: Wrap Softness ===
	if (fractal->transformCommon.jkWrapSoftness > 0.0)
	{
		double rr2 = z.Dot(z);
		double s = fractal->transformCommon.jkWrapSoftness;
		double t = fmax(0.0, fmin(1.0, (rr2 - 0.25) / (s + 1e-21)));
		t = t * t * (3.0 - 2.0 * t);
		double softScale = 1.0 + (1.0 - t) * s * 0.1;
		z *= softScale;
		aux.DE *= fabs(softScale);
	}

	// === JK #15: Anisotropic Inversion ===
	if (fractal->transformCommon.jkAnisotropicInv != 0.0)
	{
		z.z *= 1.0 + fractal->transformCommon.jkAnisotropicInv;
		aux.DE *= fabs(1.0 + fractal->transformCommon.jkAnisotropicInv * 0.5);
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
