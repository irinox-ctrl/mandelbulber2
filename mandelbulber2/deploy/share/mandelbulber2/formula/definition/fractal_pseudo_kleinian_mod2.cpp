/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * Pseudo Kleinian Mod2, Knighty - Theli-at's Pseudo Kleinian (Scale 1 JuliaBox + Something
 * @reference https://github.com/Syntopia/Fragmentarium/blob/master/
 * Fragmentarium-Source/Examples/Knighty%20Collection/PseudoKleinian.frag
 */

#include "all_fractal_definitions.h"

cFractalPseudoKleinianMod2::cFractalPseudoKleinianMod2() : cAbstractFractal()
{
	nameInComboBox = "Pseudo Kleinian - Mod 2";
	internalName = "pseudo_kleinian_mod2";
	internalID = fractal::pseudoKleinianMod2;
	DEType = analyticDEType;
	DEFunctionType = pseudoKleinianDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionPseudoKleinian;
	coloringFunction = coloringFunctionDefault;
}

void cFractalPseudoKleinianMod2::FormulaCode(
	CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	CVector4 oldZ = z;
	CVector4 zCol = z;
	double rrCol = 0.0;
	double colorAdd = 0.0;
	// spherical fold
	if (fractal->transformCommon.functionEnabledSFalse
			&& aux.i >= fractal->transformCommon.startIterationsS
			&& aux.i < fractal->transformCommon.stopIterationsS)
	{
		double para = 0.0;
		double paraAddP0 = 0.0;
		if (fractal->transformCommon.functionEnabledyFalse)
		{
			if (fractal->Cpara.enabledLinear)
			{
				para = fractal->Cpara.para00; // parameter value at iter 0
				double temp0 = para;
				double tempA = fractal->Cpara.paraA;
				double tempB = fractal->Cpara.paraB;
				double tempC = fractal->Cpara.paraC;
				double lengthAB = fractal->Cpara.iterB - fractal->Cpara.iterA;
				double lengthBC = fractal->Cpara.iterC - fractal->Cpara.iterB;
				double grade1 = (tempA - temp0) / fractal->Cpara.iterA;
				double grade2 = (tempB - tempA) / lengthAB;
				double grade3 = (tempC - tempB) / lengthBC;

				// slopes
				if (aux.i < fractal->Cpara.iterA)
				{
					para = temp0 + (aux.i * grade1);
				}
				if (aux.i < fractal->Cpara.iterB && aux.i >= fractal->Cpara.iterA)
				{
					para = tempA + (aux.i - fractal->Cpara.iterA) * grade2;
				}
				if (aux.i >= fractal->Cpara.iterB)
				{
					para = tempB + (aux.i - fractal->Cpara.iterB) * grade3;
				}

				// Curvi part on "true"
				if (fractal->Cpara.enabledCurves)
				{
					double paraAdd = 0.0;
					double paraIt;
					if (lengthAB > 2.0 * fractal->Cpara.iterA) // stop  error, todo fix.
					{
						double curve1 = (grade2 - grade1) / (4.0 * fractal->Cpara.iterA);
						double tempL = lengthAB - fractal->Cpara.iterA;
						double curve2 = (grade3 - grade2) / (4.0 * tempL);
						if (aux.i < 2 * fractal->Cpara.iterA)
						{
							paraIt = tempA - fabs(tempA - aux.i);
							paraAdd = paraIt * paraIt * curve1;
						}
						if (aux.i >= 2 * fractal->Cpara.iterA && aux.i < fractal->Cpara.iterB + tempL)
						{
							paraIt = tempB - fabs(tempB * aux.i);
							paraAdd = paraIt * paraIt * curve2;
						}
						para += paraAdd;
					}
				}
			}
			paraAddP0 = 0.0;
			if (fractal->Cpara.enabledParabFalse)
			{ // parabolic = paraOffset + iter *slope + (iter *iter *scale)
				paraAddP0 = fractal->Cpara.parabOffset0 + (aux.i * fractal->Cpara.parabSlope)
										+ (aux.i * aux.i * 0.001 * fractal->Cpara.parabScale);
			}
		}
		para += paraAddP0 + fractal->transformCommon.minR2p25;

		// spherical fold
		double rr = z.Dot(z);
		rrCol = rr;
		z += fractal->mandelbox.offset;

		// if (rr < 1e-21) rr = 1e-21;
		if (rr < para)
		{
			double tglad_factor1 = fractal->transformCommon.maxR2d1 / para;
			z *= tglad_factor1;
			aux.DE *= tglad_factor1;
		}
		else if (rr < fractal->transformCommon.maxR2d1) // fractal->mandelbox.fR2
		{
			double tglad_factor2 = fractal->transformCommon.maxR2d1 / rr;
			z *= tglad_factor2;
			aux.DE *= tglad_factor2;
		}
		z -= fractal->mandelbox.offset;
		z *= fractal->transformCommon.scale1;
		aux.DE = aux.DE * fabs(fractal->transformCommon.scale1) + fractal->analyticDE.offset0;
	}

	if (fractal->transformCommon.functionEnabledPFalse
			&& aux.i >= fractal->transformCommon.startIterationsP
			&& aux.i < fractal->transformCommon.stopIterationsP1)
	{
		CVector4 gap = fractal->transformCommon.constantMultiplier000;
		z.y = fabs(z.y);
		z.z = fabs(z.z);
		double dot1 = (z.x * -SQRT_3_4 + z.y * 0.5) * fractal->transformCommon.scale;
		double t = max(0.0, dot1);
		z.x -= t * -SQRT_3;
		z.y = fabs(z.y - t);

		if (z.y > z.z) swap(z.y, z.z);
		z -= gap * CVector4(SQRT_3_4, 1.5, 1.5, 0.0);
		// z was pos, now some points neg (ie neg shift)
		if (z.z > z.x) swap(z.z, z.x);
		if (z.x > 0.0)
		{
			z.y = max(0.0, z.y);
			z.z = max(0.0, z.z);
		}
	}

	if (fractal->transformCommon.functionEnabledRFalse
			&& aux.i >= fractal->transformCommon.startIterationsR
			&& aux.i < fractal->transformCommon.stopIterationsR)
		z = fractal->transformCommon.rotationMatrix.RotateVector(z);

	if (fractal->transformCommon.benesiT1EnabledFalse
			&& aux.i >= fractal->transformCommon.startIterationsT
			&& aux.i < fractal->transformCommon.stopIterationsT1)
	{
		double tempXZ = z.x * SQRT_2_3 - z.z * SQRT_1_3;
		z = CVector4(
			(tempXZ - z.y) * SQRT_1_2, (tempXZ + z.y) * SQRT_1_2, z.x * SQRT_1_3 + z.z * SQRT_2_3, 0.0);

		CVector4 tempZ = z;
		double tempL = tempZ.Length();
		z = fabs(z) * fractal->transformCommon.scale3D222;
		// if (tempL < 1e-21) tempL = 1e-21;
		double avgScale = z.Length() / tempL;
		aux.DE = aux.DE * avgScale + 1.0;

		tempXZ = (z.y + z.x) * SQRT_1_2;

		z = CVector4(z.z * SQRT_1_3 + tempXZ * SQRT_2_3, (z.y - z.x) * SQRT_1_2,
			z.z * SQRT_2_3 - tempXZ * SQRT_1_3, 0.0);
		z = z - fractal->transformCommon.offset200;
	}

	if (fractal->transformCommon.functionEnabledxFalse
			&& aux.i >= fractal->transformCommon.startIterationsD
			&& aux.i < fractal->transformCommon.stopIterationsTM1)
	{
		double tempXZ = z.x * SQRT_2_3 - z.z * SQRT_1_3;
		z = CVector4(
			(tempXZ - z.y) * SQRT_1_2, (tempXZ + z.y) * SQRT_1_2, z.x * SQRT_1_3 + z.z * SQRT_2_3, 0.0);

		CVector4 temp = z;
		double tempL = temp.Length();
		z = fabs(z) * fractal->transformCommon.scale3D333;
		// if (tempL < 1e-21) tempL = 1e-21;
		double avgScale = z.Length() / tempL;
		aux.DE = aux.DE * avgScale + 1.0;

		oldZ = z;
		z = (fabs(z + fractal->transformCommon.additionConstant111)
				 - fabs(z - fractal->transformCommon.additionConstant111) - z);
		zCol = z;
		/*if (fractal->foldColor.auxColorEnabledFalse)
		{
			if (z.x != oldZ.x) colorAdd += fractal->mandelbox.color.factor.x;
			if (z.y != oldZ.y) colorAdd += fractal->mandelbox.color.factor.y;
			if (z.z != oldZ.z) colorAdd += fractal->mandelbox.color.factor.z;
		}*/
		tempXZ = (z.y + z.x) * SQRT_1_2;

		z = CVector4(z.z * SQRT_1_3 + tempXZ * SQRT_2_3, (z.y - z.x) * SQRT_1_2,
			z.z * SQRT_2_3 - tempXZ * SQRT_1_3, 0.0);
	}

	double k = 1.0;
	// Pseudo kleinian
	CVector4 cSize = fractal->transformCommon.additionConstant0777;
	if (fractal->transformCommon.functionEnabledAy
			&& aux.i >= fractal->transformCommon.startIterationsC
			&& aux.i < fractal->transformCommon.stopIterationsC)
	{
		CVector4 tempZ = z; //  correct c++ version. non conditional mult 2.0

		if (z.x > cSize.x) tempZ.x = cSize.x;
		if (z.x < -cSize.x) tempZ.x = -cSize.x;
		if (z.y > cSize.y) tempZ.y = cSize.y;
		if (z.y < -cSize.y) tempZ.y = -cSize.y;
		if (z.z > cSize.z) tempZ.z = cSize.z;
		if (z.z < -cSize.z) tempZ.z = -cSize.z;

		z = tempZ * 2.0 - z;
		k = max(fractal->transformCommon.minR05 / z.Dot(z), 1.0);
		z *= k;
		aux.DE *= k + fractal->analyticDE.tweak005;
			aux.pseudoKleinianDE = fractal->analyticDE.scale1; // pK DE
	}

	if (fractal->transformCommon.functionEnabledAyFalse
			&& aux.i >= fractal->transformCommon.startIterationsB
			&& aux.i < fractal->transformCommon.stopIterationsB)
	{
		//  variation from openCL conditional mult 2.0
		if (z.x > cSize.x) z.x = cSize.x * 2.0 - z.x;
		if (z.x < -cSize.x) z.x = -cSize.x * 2.0 - z.x;
		if (z.y > cSize.y) z.y = cSize.y * 2.0 - z.y;
		if (z.y < -cSize.y) z.y = -cSize.y * 2.0 - z.y;
		if (z.z > cSize.z) z.z = cSize.z * 2.0 - z.z;
		if (z.z < -cSize.z) z.z = -cSize.z * 2.0 - z.z;

		k = max(fractal->transformCommon.minR05 / z.Dot(z), 1.0);
		z *= k;
		aux.DE *= k + fractal->analyticDE.tweak005;
			aux.pseudoKleinianDE = fractal->analyticDE.scale1; // pK DE
	}

	z += fractal->transformCommon.additionConstant000;

	if (fractal->transformCommon.functionEnabledFFalse
			&& aux.i >= fractal->transformCommon.startIterationsF
			&& aux.i < fractal->transformCommon.stopIterationsF)
	{
		oldZ = z;
		z = fabs(z + fractal->transformCommon.offsetA000)
				- fabs(z - fractal->transformCommon.offsetA000) - z;
		zCol = z;

		if (fractal->transformCommon.functionEnabledFalse
				&& aux.i >= fractal->transformCommon.startIterationsA
				&& aux.i < fractal->transformCommon.stopIterationsA)
		{
			CVector4 limit = fractal->transformCommon.offsetA000;
			CVector4 length = 2.0 * limit;
			CVector4 tgladS = 1.0 / length;
			CVector4 Add = CVector4(0.0, 0.0, 0.0, 0.0);

			if (fabs(z.x) < limit.x) Add.x = z.x * z.x * tgladS.x;
			if (fabs(z.y) < limit.y) Add.y = z.y * z.y * tgladS.y;
			if (fabs(z.z) < limit.z) Add.z = z.z * z.z * tgladS.z;
			if (fabs(z.x) > limit.x && fabs(z.x) < length.x)
				Add.x = (length.x - fabs(z.x)) * (length.x - fabs(z.x)) * tgladS.x;
			if (fabs(z.y) > limit.y && fabs(z.y) < length.y)
				Add.y = (length.y - fabs(z.y)) * (length.y - fabs(z.y)) * tgladS.y;
			if (fabs(z.z) > limit.z && fabs(z.z) < length.z)
				Add.z = (length.z - fabs(z.z)) * (length.z - fabs(z.z)) * tgladS.z;
			Add *= fractal->transformCommon.scale3D000;
			z.x = (z.x - (sign(z.x) * (Add.x)));
			z.y = (z.y - (sign(z.y) * (Add.y)));
			z.z = (z.z - (sign(z.z) * (Add.z)));
		}
	}
	if (fractal->transformCommon.addCpixelEnabledFalse) // symmetrical addCpixel
	{
		CVector4 tempFAB = aux.const_c;
		if (fractal->transformCommon.functionEnabledx) tempFAB.x = fabs(tempFAB.x);
		if (fractal->transformCommon.functionEnabledy) tempFAB.y = fabs(tempFAB.y);
		if (fractal->transformCommon.functionEnabledz) tempFAB.z = fabs(tempFAB.z);

		tempFAB *= fractal->transformCommon.offsetF000;
		z.x += sign(z.x) * tempFAB.x;
		z.y += sign(z.y) * tempFAB.y;
		z.z += sign(z.z) * tempFAB.z;
	}

	// aux.pseudoKleinianZZ = fractal->transformCommon.scale0; // pK z.z * z.z * scale0

	// color updated v2.13 & mode2 v2.14
	if (fractal->foldColor.auxColorEnabledFalse
			&& aux.i >= fractal->foldColor.startIterationsA
			&& aux.i < fractal->foldColor.stopIterationsA)
	{
		colorAdd += k * fractal->foldColor.difs0000.x;
		if (fractal->transformCommon.functionEnabledCxFalse)
		{
			if (zCol.x != oldZ.x)
				colorAdd += fractal->mandelbox.color.factor.x
										* (fabs(zCol.x) - fractal->transformCommon.additionConstant111.x);
			if (zCol.y != oldZ.y)
				colorAdd += fractal->mandelbox.color.factor.y
										* (fabs(zCol.y) - fractal->transformCommon.additionConstant111.y);
			if (zCol.z != oldZ.z)
				colorAdd += fractal->mandelbox.color.factor.z
										* (fabs(zCol.z) - fractal->transformCommon.additionConstant111.z);

			if (rrCol < fractal->transformCommon.maxR2d1)
			{
				if (rrCol < fractal->transformCommon.minR2p25)
					colorAdd +=
						fractal->mandelbox.color.factorSp1 * (fractal->transformCommon.minR2p25 - rrCol)
						+ fractal->mandelbox.color.factorSp2
								* (fractal->transformCommon.maxR2d1 - fractal->transformCommon.minR2p25);
				else
					colorAdd +=
						fractal->mandelbox.color.factorSp2 * (fractal->transformCommon.maxR2d1 - rrCol);
			}
		}
		else
		{
			if (zCol.x != oldZ.x) colorAdd += fractal->mandelbox.color.factor.x;
			if (zCol.y != oldZ.y) colorAdd += fractal->mandelbox.color.factor.y;
			if (zCol.z != oldZ.z) colorAdd += fractal->mandelbox.color.factor.z;

			if (rrCol < fractal->transformCommon.minR2p25)
				colorAdd += fractal->mandelbox.color.factorSp1;
			else if (rrCol < fractal->transformCommon.maxR2d1)
				colorAdd += fractal->mandelbox.color.factorSp2;
		}
		aux.color += colorAdd;
	}
	// =============================================
	// === PSEUDO KLEINIAN EXTENSIONS (#1-#15) ===
	// =============================================

	// === PK #1-2: CSize Oscillation ===
	if (fractal->transformCommon.pkCsizeOscAmp != 0.0)
	{
		double csOsc = fractal->transformCommon.pkCsizeOscAmp * sin((double)aux.i * fractal->transformCommon.pkCsizeOscFreq);
		z.x += csOsc * z.x;
		z.y += csOsc * z.y;
		z.z += csOsc * z.z;
	}

	// === PK #3-4: MinR Oscillation ===
	if (fractal->transformCommon.pkMinROscAmp != 0.0)
	{
		double mrOsc = fractal->transformCommon.pkMinROscAmp * sin((double)aux.i * fractal->transformCommon.pkMinROscFreq);
		double rLocal = z.Length();
		double factor = 1.0 + mrOsc / (rLocal + 1e-21);
		z *= factor;
		aux.DE *= fabs(factor);
	}

	// === PK #5: K Power (sphere fold exponent) ===
	if (fractal->transformCommon.pkKPower != 1.0 && fractal->transformCommon.pkKPower != 0.0)
	{
		double rr = z.Dot(z);
		if (rr > 1e-21)
		{
			double kk = max(1.0 / rr, 1.0);
			kk = pow(kk, fractal->transformCommon.pkKPower);
			z *= kk;
			aux.DE *= fabs(kk);
		}
	}

	// === PK #6: Pre-Twist ===
	if (fractal->transformCommon.pkPreTwist != 0.0)
	{
		double angle = fractal->transformCommon.pkPreTwist * M_PI / 180.0 * (double)aux.i;
		double cosA = cos(angle);
		double sinA = sin(angle);
		double xn = z.x * cosA - z.y * sinA;
		double yn = z.x * sinA + z.y * cosA;
		z.x = xn;
		z.y = yn;
	}

	// === PK #7: Post-Twist ===
	if (fractal->transformCommon.pkPostTwist != 0.0)
	{
		double angle = fractal->transformCommon.pkPostTwist * M_PI / 180.0;
		double cosA = cos(angle);
		double sinA = sin(angle);
		double xn = z.x * cosA - z.z * sinA;
		double zn = z.x * sinA + z.z * cosA;
		z.x = xn;
		z.z = zn;
	}

	// === PK #8: Z-Shift (height-dependent displacement) ===
	if (fractal->transformCommon.pkZShift != 0.0)
	{
		z.x += fractal->transformCommon.pkZShift * z.z;
		z.y += fractal->transformCommon.pkZShift * z.z * 0.5;
	}

	// === PK #9: Radial Distortion ===
	if (fractal->transformCommon.pkRadialDistort != 0.0)
	{
		double r = sqrt(z.x * z.x + z.y * z.y + 1e-21);
		double distort = 1.0 + fractal->transformCommon.pkRadialDistort * sin(r * 3.0);
		z.x *= distort;
		z.y *= distort;
		aux.DE *= fabs(distort);
	}

	// === PK #10: Turbulence Injection ===
	if (fractal->transformCommon.pkTurbulence != 0.0)
	{
		double turb = fractal->transformCommon.pkTurbulence;
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

	// === PK #11: Gradient Color (k-value based) ===
	if (fractal->transformCommon.pkGradientColor != 0.0)
	{
		double rr = z.Dot(z);
		double kCol = max(1.0 / (rr + 1e-21), 1.0);
		aux.color += fabs(kCol - 1.0) * fractal->transformCommon.pkGradientColor;
	}

	// === PK #12: DE Tweak (additive per iteration) ===
	if (fractal->transformCommon.pkDETweak != 0.0)
	{
		aux.DE += fractal->transformCommon.pkDETweak;
	}

	// === PK #13: C-Pixel Inject ===
	if (fractal->transformCommon.pkCpixelInject != 0.0)
	{
		z += aux.const_c * fractal->transformCommon.pkCpixelInject;
	}

	// === PK #14: Sphere Softness ===
	if (fractal->transformCommon.pkSphereSoftness > 0.0)
	{
		double rr2 = z.Dot(z);
		double s = fractal->transformCommon.pkSphereSoftness;
		double t = fmax(0.0, fmin(1.0, (rr2 - 0.25) / (s + 1e-21)));
		t = t * t * (3.0 - 2.0 * t);
		double softScale = 1.0 + (1.0 - t) * s * 0.1;
		z *= softScale;
		aux.DE *= fabs(softScale);
	}

	// === PK #15: Anisotropic K (non-uniform Z-axis scaling) ===
	if (fractal->transformCommon.pkAnisotropicK != 0.0)
	{
		z.z *= 1.0 + fractal->transformCommon.pkAnisotropicK;
		aux.DE *= fabs(1.0 + fractal->transformCommon.pkAnisotropicK * 0.5);
	}

	// GPU bypass: skip if all multipliers disabled
	if (fractal->transformCommon.multiplierEnabled1 || fractal->transformCommon.multiplierEnabled2 || fractal->transformCommon.multiplierEnabled3 || fractal->transformCommon.multiplierEnabled4 || fractal->transformCommon.multiplierEnabled5)
	{
		double prevMultVal = 1.0;
		// === General Purpose Multiplier 1 ===
		if (fractal->transformCommon.multiplierEnabled1
				&& aux.i >= fractal->transformCommon.multiplierStartIter1
				&& aux.i < fractal->transformCommon.multiplierStopIter1)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode1;
			double threshR = z.Length();
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold1)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold1))
			{
				double val = fractal->transformCommon.multiplierScale1;

				if (fractal->transformCommon.multiplierInverse1) val = (fabs(val) > 1e-15) ? (1.0 / val) : 1e15;

				int vmode = fractal->transformCommon.multiplierValueMode1;
				double range = (double)(fractal->transformCommon.multiplierStopIter1 - fractal->transformCommon.multiplierStartIter1);
				double ph = fractal->transformCommon.multiplierPhase1;
				if (range > 0 && vmode > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.multiplierStartIter1) / range;
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
					case 1: z.x *= val; aux.DE *= fabs(val); break;
					case 2: z.y *= val; aux.DE *= fabs(val); break;
					case 3: z.z *= val; aux.DE *= fabs(val); break;
					case 4: aux.DE *= val; break;
					case 5: aux.color *= val; break;
					case 6: z.w *= val; aux.DE *= fabs(val); break;
					case 7: z.x *= val; z.y *= val; aux.DE *= fabs(val); break;
					case 8: z.x *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 9: z.y *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 10: aux.color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 2 ===
		if (fractal->transformCommon.multiplierEnabled2
				&& aux.i >= fractal->transformCommon.multiplierStartIter2
				&& aux.i < fractal->transformCommon.multiplierStopIter2)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode2;
			double threshR = z.Length();
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold2)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold2))
			{
				double val = fractal->transformCommon.multiplierScale2;

				if (fractal->transformCommon.multiplierInverse2) val = (fabs(val) > 1e-15) ? (1.0 / val) : 1e15;

				int vmode = fractal->transformCommon.multiplierValueMode2;
				double range = (double)(fractal->transformCommon.multiplierStopIter2 - fractal->transformCommon.multiplierStartIter2);
				double ph = fractal->transformCommon.multiplierPhase2;
				if (range > 0 && vmode > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.multiplierStartIter2) / range;
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
					case 1: z.x *= val; aux.DE *= fabs(val); break;
					case 2: z.y *= val; aux.DE *= fabs(val); break;
					case 3: z.z *= val; aux.DE *= fabs(val); break;
					case 4: aux.DE *= val; break;
					case 5: aux.color *= val; break;
					case 6: z.w *= val; aux.DE *= fabs(val); break;
					case 7: z.x *= val; z.y *= val; aux.DE *= fabs(val); break;
					case 8: z.x *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 9: z.y *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 10: aux.color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 3 ===
		if (fractal->transformCommon.multiplierEnabled3
				&& aux.i >= fractal->transformCommon.multiplierStartIter3
				&& aux.i < fractal->transformCommon.multiplierStopIter3)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode3;
			double threshR = z.Length();
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold3)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold3))
			{
				double val = fractal->transformCommon.multiplierScale3;

				if (fractal->transformCommon.multiplierInverse3) val = (fabs(val) > 1e-15) ? (1.0 / val) : 1e15;

				int vmode = fractal->transformCommon.multiplierValueMode3;
				double range = (double)(fractal->transformCommon.multiplierStopIter3 - fractal->transformCommon.multiplierStartIter3);
				double ph = fractal->transformCommon.multiplierPhase3;
				if (range > 0 && vmode > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.multiplierStartIter3) / range;
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
					case 1: z.x *= val; aux.DE *= fabs(val); break;
					case 2: z.y *= val; aux.DE *= fabs(val); break;
					case 3: z.z *= val; aux.DE *= fabs(val); break;
					case 4: aux.DE *= val; break;
					case 5: aux.color *= val; break;
					case 6: z.w *= val; aux.DE *= fabs(val); break;
					case 7: z.x *= val; z.y *= val; aux.DE *= fabs(val); break;
					case 8: z.x *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 9: z.y *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 10: aux.color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 4 ===
		if (fractal->transformCommon.multiplierEnabled4
				&& aux.i >= fractal->transformCommon.multiplierStartIter4
				&& aux.i < fractal->transformCommon.multiplierStopIter4)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode4;
			double threshR = z.Length();
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold4)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold4))
			{
				double val = fractal->transformCommon.multiplierScale4;

				if (fractal->transformCommon.multiplierInverse4) val = (fabs(val) > 1e-15) ? (1.0 / val) : 1e15;

				int vmode = fractal->transformCommon.multiplierValueMode4;
				double range = (double)(fractal->transformCommon.multiplierStopIter4 - fractal->transformCommon.multiplierStartIter4);
				double ph = fractal->transformCommon.multiplierPhase4;
				if (range > 0 && vmode > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.multiplierStartIter4) / range;
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
					case 1: z.x *= val; aux.DE *= fabs(val); break;
					case 2: z.y *= val; aux.DE *= fabs(val); break;
					case 3: z.z *= val; aux.DE *= fabs(val); break;
					case 4: aux.DE *= val; break;
					case 5: aux.color *= val; break;
					case 6: z.w *= val; aux.DE *= fabs(val); break;
					case 7: z.x *= val; z.y *= val; aux.DE *= fabs(val); break;
					case 8: z.x *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 9: z.y *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 10: aux.color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 5 ===
		if (fractal->transformCommon.multiplierEnabled5
				&& aux.i >= fractal->transformCommon.multiplierStartIter5
				&& aux.i < fractal->transformCommon.multiplierStopIter5)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode5;
			double threshR = z.Length();
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold5)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold5))
			{
				double val = fractal->transformCommon.multiplierScale5;

				if (fractal->transformCommon.multiplierInverse5) val = (fabs(val) > 1e-15) ? (1.0 / val) : 1e15;

				int vmode = fractal->transformCommon.multiplierValueMode5;
				double range = (double)(fractal->transformCommon.multiplierStopIter5 - fractal->transformCommon.multiplierStartIter5);
				double ph = fractal->transformCommon.multiplierPhase5;
				if (range > 0 && vmode > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.multiplierStartIter5) / range;
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
					case 1: z.x *= val; aux.DE *= fabs(val); break;
					case 2: z.y *= val; aux.DE *= fabs(val); break;
					case 3: z.z *= val; aux.DE *= fabs(val); break;
					case 4: aux.DE *= val; break;
					case 5: aux.color *= val; break;
					case 6: z.w *= val; aux.DE *= fabs(val); break;
					case 7: z.x *= val; z.y *= val; aux.DE *= fabs(val); break;
					case 8: z.x *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 9: z.y *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 10: aux.color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}
	}

}
