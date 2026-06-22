/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * benesiPwr2 mandelbulb
 * @reference
 * http://www.fractalforums.com/new-theories-and-research/
 * do-m3d-formula-have-to-be-distance-estimation-formulas/
 */

#include "all_fractal_definitions.h"

cFractalBenesiPwr2Mandelbulb::cFractalBenesiPwr2Mandelbulb() : cAbstractFractal()
{
	nameInComboBox = "Benesi - Pwr2 Mandelbulb";
	internalName = "benesi_pwr2_mandelbulb";
	internalID = fractal::benesiPwr2Mandelbulb;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalBenesiPwr2Mandelbulb::FormulaCode(
	CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	CVector4 c = aux.const_c;
	// Prism shape
	if (fractal->transformCommon.functionEnabledPFalse
			&& aux.i >= fractal->transformCommon.startIterationsP
			&& aux.i < fractal->transformCommon.stopIterationsP1)
	{
		CVector4 gap = fractal->transformCommon.constantMultiplier000;
		double t;
		double dot1;
		z.y = fabs(z.y);
		z.z = fabs(z.z);
		dot1 = (z.x * -SQRT_3_4 + z.y * 0.5) * fractal->transformCommon.scale;
		t = max(0.0, dot1);
		z.x -= t * -SQRT_3;
		z.y = fabs(z.y - t);

		if (z.y > z.z) swap(z.y, z.z);
		z -= gap * CVector4(SQRT_3_4, 1.5, 1.5, 0.0);

		if (z.z > z.x) swap(z.z, z.x);
		if (z.x > 0.0)
		{
			z.y = max(0.0, z.y);
			z.z = max(0.0, z.z);
		}
	}
	// Benesi mag transform T1
	if (fractal->transformCommon.benesiT1Enabled && aux.i >= fractal->transformCommon.startIterations
			&& aux.i < fractal->transformCommon.stopIterations)
	{
		double tempXZ = z.x * SQRT_2_3 - z.z * SQRT_1_3;
		z = CVector4(
			(tempXZ - z.y) * SQRT_1_2, (tempXZ + z.y) * SQRT_1_2, z.x * SQRT_1_3 + z.z * SQRT_2_3, z.w);

		double tempL = z.Length();
		z = fabs(z) * fractal->transformCommon.scale3D222;
		// if (tempL < 1e-21) tempL = 1e-21;
		double avgScale = z.Length() / tempL;
		aux.DE = aux.DE * avgScale + 1.0;

		if (fractal->transformCommon.rotationEnabled)
		{ // rotation inside T1
			z = fractal->transformCommon.rotationMatrix.RotateVector(z);
		}

		tempXZ = (z.y + z.x) * SQRT_1_2;

		z = CVector4(z.z * SQRT_1_3 + tempXZ * SQRT_2_3, (z.y - z.x) * SQRT_1_2,
			z.z * SQRT_2_3 - tempXZ * SQRT_1_3, z.w);
		z = z - fractal->transformCommon.offset200;
	}

	if (fractal->transformCommon.addCpixelEnabled
			&& aux.i >= fractal->transformCommon.startIterationsF
			&& aux.i < fractal->transformCommon.stopIterationsF)
	{ // Benesi original pwr2
		CVector4 zz = z * z;
		double rrYZ = zz.y + zz.z;
		double lenYZ = sqrt(rrYZ);
		double temp = zz.x + rrYZ;
		aux.r = sqrt(temp); // aux.r needed when alternating pwr2s
		aux.DE = aux.DE * 2.0 * aux.r;
		CVector4 newZ = z;
		temp = zz.x - rrYZ;
		newZ.x = -sign(c.x) * temp;
		if (z.x < lenYZ) newZ.x = temp;
		rrYZ = -1.0 / lenYZ * 2.0 * fabs(z.x);
		newZ.y = rrYZ * (zz.y - zz.z);
		newZ.z = rrYZ * 2.0 * z.y * z.z;
		z = newZ + (c * fractal->transformCommon.constantMultiplierA100);
	}
	//  Benesi pine tree pwr2
	if (fractal->transformCommon.addCpixelEnabledFalse
			&& aux.i >= fractal->transformCommon.startIterationsC
			&& aux.i < fractal->transformCommon.stopIterationsC)
	{
		CVector4 zz = z * z;
		aux.r = sqrt(zz.x + zz.y + zz.z); // needed when alternating pwr2s
		aux.DE = aux.r * aux.DE * 2.0 + 1.0;

		double t = 1.0;
		double temp = zz.y + zz.z;
		if (temp > 0.0) t = 2.0 * z.x / sqrt(temp);
		temp = z.z;
		z.x = (zz.x - zz.y - zz.z);
		z.y = (2.0 * t * z.y * temp);
		z.z = (t * (zz.y - zz.z));

		// swap c.yz then add cPixel
		CVector4 tempC = c;
		if (fractal->transformCommon.alternateEnabledFalse) // alternate
		{
			tempC = aux.c * fractal->transformCommon.constantMultiplier100;
			tempC = CVector4(tempC.x, tempC.z, tempC.y, tempC.w);
			aux.c = tempC;
		}
		else
		{
			tempC *= fractal->transformCommon.constantMultiplier100;
			tempC = CVector4(tempC.x, tempC.z, tempC.y, tempC.w);
		}
		z += tempC;
	}

	if (fractal->transformCommon.functionEnabledBxFalse
			&& aux.i >= fractal->transformCommon.startIterationsD
			&& aux.i < fractal->transformCommon.stopIterationsD)
	{
		z = CVector4(z.x * cos(z.y * fractal->transformCommon.scale1),
					z.x * sin(z.y * fractal->transformCommon.scale1), z.z * fractal->transformCommon.scaleC1,
					z.w)
				* fractal->transformCommon.scaleA1;
		aux.DE *= fabs(fractal->transformCommon.scaleA1);
	}

	if (fractal->transformCommon.juliaMode && aux.i >= fractal->transformCommon.startIterationsE
			&& aux.i < fractal->transformCommon.stopIterationsE)
		z += fractal->transformCommon.offset000;

	if (fractal->transformCommon.rotation2EnabledFalse)
		z = fractal->transformCommon.rotationMatrix2.RotateVector(z);

	// Analytic DE tweak
	if (fractal->analyticDE.enabledFalse)
		aux.DE = aux.DE * fractal->analyticDE.scale1 + fractal->analyticDE.offset0;
	// GPU bypass: skip if all multipliers disabled
	if (fractal->transformCommon.functionEnabledBxFalse || fractal->transformCommon.functionEnabledByFalse || fractal->transformCommon.functionEnabledBzFalse || fractal->transformCommon.functionEnabledBwFalse || fractal->transformCommon.functionEnabledCzFalse)
	{
		// === General Purpose Multiplier 1 ===
		if (fractal->transformCommon.functionEnabledBxFalse
				&& aux.i >= fractal->transformCommon.startIterationsB
				&& aux.i < fractal->transformCommon.stopIterationsB)
		{
			double val = fractal->transformCommon.scale4;

			if (fractal->transformCommon.multiplierInverse1) val = 1.0 / val;

			int vmode = fractal->transformCommon.multiplierValueMode1;
			if (vmode == 1)
			{
				double range = (double)(fractal->transformCommon.stopIterationsB - fractal->transformCommon.startIterationsB);
				if (range > 0)
				{
					double phase = (double)(aux.i - fractal->transformCommon.startIterationsB) / range;
					val = 1.0 + (val - 1.0) * sin(phase * fractal->transformCommon.multiplierFrequency1 * 2.0 * M_PI);
				}
			}
			else if (vmode == 2)
			{
				double range = (double)(fractal->transformCommon.stopIterationsB - fractal->transformCommon.startIterationsB);
				if (range > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.startIterationsB) / range;
					t = qBound(0.0, t, 1.0);
					val = 1.0 + t * (val - 1.0);
				}
			}

			switch (fractal->transformCommon.multiplierMode1)
			{
				default:
				case 0: z *= val; aux.DE *= fabs(val); break;
				case 1: z.x *= val; break;
				case 2: z.y *= val; break;
				case 3: z.z *= val; break;
				case 4: aux.DE *= val; break;
				case 5: aux.color *= val; break;
				case 6: z.w *= val; break;
				case 7: z.x *= val; z.y *= val; break;
				case 8: z.x *= val; z.z *= val; break;
				case 9: z.y *= val; z.z *= val; break;
			}
		}

		// === General Purpose Multiplier 2 ===
		if (fractal->transformCommon.functionEnabledByFalse
				&& aux.i >= fractal->transformCommon.startIterationsC
				&& aux.i < fractal->transformCommon.stopIterationsC)
		{
			double val = fractal->transformCommon.scale5;

			if (fractal->transformCommon.multiplierInverse2) val = 1.0 / val;

			int vmode = fractal->transformCommon.multiplierValueMode2;
			if (vmode == 1)
			{
				double range = (double)(fractal->transformCommon.stopIterationsC - fractal->transformCommon.startIterationsC);
				if (range > 0)
				{
					double phase = (double)(aux.i - fractal->transformCommon.startIterationsC) / range;
					val = 1.0 + (val - 1.0) * sin(phase * fractal->transformCommon.multiplierFrequency2 * 2.0 * M_PI);
				}
			}
			else if (vmode == 2)
			{
				double range = (double)(fractal->transformCommon.stopIterationsC - fractal->transformCommon.startIterationsC);
				if (range > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.startIterationsC) / range;
					t = qBound(0.0, t, 1.0);
					val = 1.0 + t * (val - 1.0);
				}
			}

			switch (fractal->transformCommon.multiplierMode2)
			{
				default:
				case 0: z *= val; aux.DE *= fabs(val); break;
				case 1: z.x *= val; break;
				case 2: z.y *= val; break;
				case 3: z.z *= val; break;
				case 4: aux.DE *= val; break;
				case 5: aux.color *= val; break;
				case 6: z.w *= val; break;
				case 7: z.x *= val; z.y *= val; break;
				case 8: z.x *= val; z.z *= val; break;
				case 9: z.y *= val; z.z *= val; break;
			}
		}

		// === General Purpose Multiplier 3 ===
		if (fractal->transformCommon.functionEnabledBzFalse
				&& aux.i >= fractal->transformCommon.startIterationsD
				&& aux.i < fractal->transformCommon.stopIterationsD)
		{
			double val = fractal->transformCommon.scale6;

			if (fractal->transformCommon.multiplierInverse3) val = 1.0 / val;

			int vmode = fractal->transformCommon.multiplierValueMode3;
			if (vmode == 1)
			{
				double range = (double)(fractal->transformCommon.stopIterationsD - fractal->transformCommon.startIterationsD);
				if (range > 0)
				{
					double phase = (double)(aux.i - fractal->transformCommon.startIterationsD) / range;
					val = 1.0 + (val - 1.0) * sin(phase * fractal->transformCommon.multiplierFrequency3 * 2.0 * M_PI);
				}
			}
			else if (vmode == 2)
			{
				double range = (double)(fractal->transformCommon.stopIterationsD - fractal->transformCommon.startIterationsD);
				if (range > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.startIterationsD) / range;
					t = qBound(0.0, t, 1.0);
					val = 1.0 + t * (val - 1.0);
				}
			}

			switch (fractal->transformCommon.multiplierMode3)
			{
				default:
				case 0: z *= val; aux.DE *= fabs(val); break;
				case 1: z.x *= val; break;
				case 2: z.y *= val; break;
				case 3: z.z *= val; break;
				case 4: aux.DE *= val; break;
				case 5: aux.color *= val; break;
				case 6: z.w *= val; break;
				case 7: z.x *= val; z.y *= val; break;
				case 8: z.x *= val; z.z *= val; break;
				case 9: z.y *= val; z.z *= val; break;
			}
		}

		// === General Purpose Multiplier 4 ===
		if (fractal->transformCommon.functionEnabledBwFalse
				&& aux.i >= fractal->transformCommon.startIterationsE
				&& aux.i < fractal->transformCommon.stopIterationsE)
		{
			double val = fractal->transformCommon.scale8;

			if (fractal->transformCommon.multiplierInverse4) val = 1.0 / val;

			int vmode = fractal->transformCommon.multiplierValueMode4;
			if (vmode == 1)
			{
				double range = (double)(fractal->transformCommon.stopIterationsE - fractal->transformCommon.startIterationsE);
				if (range > 0)
				{
					double phase = (double)(aux.i - fractal->transformCommon.startIterationsE) / range;
					val = 1.0 + (val - 1.0) * sin(phase * fractal->transformCommon.multiplierFrequency4 * 2.0 * M_PI);
				}
			}
			else if (vmode == 2)
			{
				double range = (double)(fractal->transformCommon.stopIterationsE - fractal->transformCommon.startIterationsE);
				if (range > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.startIterationsE) / range;
					t = qBound(0.0, t, 1.0);
					val = 1.0 + t * (val - 1.0);
				}
			}

			switch (fractal->transformCommon.multiplierMode4)
			{
				default:
				case 0: z *= val; aux.DE *= fabs(val); break;
				case 1: z.x *= val; break;
				case 2: z.y *= val; break;
				case 3: z.z *= val; break;
				case 4: aux.DE *= val; break;
				case 5: aux.color *= val; break;
				case 6: z.w *= val; break;
				case 7: z.x *= val; z.y *= val; break;
				case 8: z.x *= val; z.z *= val; break;
				case 9: z.y *= val; z.z *= val; break;
			}
		}

		// === General Purpose Multiplier 5 ===
		if (fractal->transformCommon.functionEnabledCzFalse
				&& aux.i >= fractal->transformCommon.startIterationsF
				&& aux.i < fractal->transformCommon.stopIterationsF)
		{
			double val = fractal->transformCommon.scale16;

			if (fractal->transformCommon.multiplierInverse5) val = 1.0 / val;

			int vmode = fractal->transformCommon.multiplierValueMode5;
			if (vmode == 1)
			{
				double range = (double)(fractal->transformCommon.stopIterationsF - fractal->transformCommon.startIterationsF);
				if (range > 0)
				{
					double phase = (double)(aux.i - fractal->transformCommon.startIterationsF) / range;
					val = 1.0 + (val - 1.0) * sin(phase * fractal->transformCommon.multiplierFrequency5 * 2.0 * M_PI);
				}
			}
			else if (vmode == 2)
			{
				double range = (double)(fractal->transformCommon.stopIterationsF - fractal->transformCommon.startIterationsF);
				if (range > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.startIterationsF) / range;
					t = qBound(0.0, t, 1.0);
					val = 1.0 + t * (val - 1.0);
				}
			}

			switch (fractal->transformCommon.multiplierMode5)
			{
				default:
				case 0: z *= val; aux.DE *= fabs(val); break;
				case 1: z.x *= val; break;
				case 2: z.y *= val; break;
				case 3: z.z *= val; break;
				case 4: aux.DE *= val; break;
				case 5: aux.color *= val; break;
				case 6: z.w *= val; break;
				case 7: z.x *= val; z.y *= val; break;
				case 8: z.x *= val; z.z *= val; break;
				case 9: z.y *= val; z.z *= val; break;
			}
		}
	}

}
