/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * asurf mod3  beta
 * amazing surf from Mandelbulber3D. Formula proposed by Kali, with features added by DarkBeam
 *
 * Note for the original version apply a c.x c.y SWAP
 *
 * @reference
 * http://www.fractalforums.com/mandelbulb-3d/custom-formulas-and-transforms-release-t17106/
 */

#include "all_fractal_definitions.h"

cFractalAmazingSurfMod3::cFractalAmazingSurfMod3() : cAbstractFractal()
{
	nameInComboBox = "Amazing Surf - Mod 3";
	internalName = "amazing_surf_mod3";
	internalID = fractal::amazingSurfMod3;
	DEType = analyticDEType;
	DEFunctionType = linearDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionLinear;
	coloringFunction = coloringFunctionDefault;
}

void cFractalAmazingSurfMod3::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	double colorAdd = 0.0;
	double rrCol = 0.0;
	CVector4 zCol = z;
	CVector4 oldZ = z;
	CVector4 c = aux.const_c;

	oldZ = z;

	bool functionEnabledN[3] = {fractal->transformCommon.functionEnabledAx,
		fractal->transformCommon.functionEnabledAyFalse,
		fractal->transformCommon.functionEnabledAzFalse};
	int startIterationN[3] = {fractal->transformCommon.startIterationsA,
		fractal->transformCommon.startIterationsB, fractal->transformCommon.startIterationsC};
	int stopIterationN[3] = {fractal->transformCommon.stopIterationsA,
		fractal->transformCommon.stopIterationsB, fractal->transformCommon.stopIterationsC};
	enumMulti_orderOf3Folds foldN[3] = {fractal->aSurf3Folds.orderOf3Folds1,
		fractal->aSurf3Folds.orderOf3Folds2, fractal->aSurf3Folds.orderOf3Folds3};

	for (int f = 0; f < 3; f++)
	{
		if (functionEnabledN[f] && aux.i >= startIterationN[f] && aux.i < stopIterationN[f])
		{
			switch (foldN[f])
			{
				case multi_orderOf3Folds_type1: // tglad fold
				default:
					if (fractal->transformCommon.functionEnabledCx)
					{
						z.x = fabs(z.x + fractal->transformCommon.additionConstant111.x)
									- fabs(z.x - fractal->transformCommon.additionConstant111.x) - z.x;
						z.y = fabs(z.y + fractal->transformCommon.additionConstant111.y)
									- fabs(z.y - fractal->transformCommon.additionConstant111.y) - z.y;
						zCol = z;
					}
					break;
				case multi_orderOf3Folds_type2:
					if (fractal->transformCommon.functionEnabledDFalse)
					{
						// tglad fold
						CVector4 foldMod = fractal->transformCommon.offsetA222;
						CVector4 fold = fractal->transformCommon.offset111;
						CVector4 sg = z;
						sg.x = sign(z.x);
						sg.y = sign(z.y);

						CVector4 folder = z;
						CVector4 Tglad = z;

						Tglad.x = fabs(z.x + fold.x) - fabs(z.x - fold.x) - z.x;
						Tglad.y = fabs(z.y + fold.y) - fabs(z.y - fold.y) - z.y;

						folder.x = sg.x * (z.x - Tglad.x);
						folder.y = sg.y * (z.y - Tglad.y);
						folder.x = fabs(folder.x);
						folder.y = fabs(folder.y);
						folder.x = min(folder.x, foldMod.x);
						folder.y = min(folder.y, foldMod.y);
						z.x -= sg.x * folder.x;
						z.y -= sg.y * folder.y;
						zCol = z;
					}
					break;
				case multi_orderOf3Folds_type3:
					if (fractal->transformCommon.functionEnabledEFalse)
					{
						// z = fold2 - fabs( fabs(z + fold) - fold2) - fabs(fold), darkbeam's
						z.x = fractal->transformCommon.offset222.x
									- fabs(fabs(z.x + fractal->transformCommon.offsetA111.x)
												 - fractal->transformCommon.offset222.x)
									- fractal->transformCommon.offsetA111.x;
						z.y = fractal->transformCommon.offset222.y
									- fabs(fabs(z.y + fractal->transformCommon.offsetA111.y)
												 - fractal->transformCommon.offset222.y)
									- fractal->transformCommon.offsetA111.y;
						zCol = z;
					}
					break;
			}
		}
	}

	// enable z axis
	if (fractal->transformCommon.functionEnabledAxFalse
			&& aux.i >= fractal->transformCommon.startIterationsZ
			&& aux.i < fractal->transformCommon.stopIterationsZ)
	{
		z.z = fabs(z.z + fractal->transformCommon.additionConstant111.z)
					- fabs(z.z - fractal->transformCommon.additionConstant111.z) - z.z;
		zCol.z = z.z;
	}

	// swizzle, swap xy alternating
	if (fractal->transformCommon.functionEnabledSwFalse
			&& aux.i >= fractal->transformCommon.startIterationsI
			&& aux.i < fractal->transformCommon.stopIterationsI)
	{
		z = CVector4(z.y, z.x, z.z, z.w);
	}
	// change y sign if iter is even
	if (fractal->transformCommon.functionEnabledJFalse
			&& aux.i >= fractal->transformCommon.startIterationsJ
			&& aux.i < fractal->transformCommon.stopIterationsJ)
	{
		if (aux.i % 2 < 1) z.y = -z.y;
	}

	// change z sign if iter is even
	if (fractal->transformCommon.functionEnabledKFalse
			&& aux.i >= fractal->transformCommon.startIterationsK
			&& aux.i < fractal->transformCommon.stopIterationsK)
	{
		if (aux.i % 2 < 1) z.z = -z.z;
	}

	// offset
	if (fractal->transformCommon.functionEnabledBzFalse
			&& aux.i >= fractal->transformCommon.startIterationsX
			&& aux.i < fractal->transformCommon.stopIterationsX)
	{
		if (fractal->transformCommon.functionEnabledBxFalse)
		{
			CVector4 temp = fractal->transformCommon.additionConstant000;
			CVector4 temp2 = temp * temp;

			z.x -= ((temp.x * temp2.x) / ((z.x * z.x) + (temp2.x)) - 2.0 * temp.x)
						 * fractal->transformCommon.scale1;
			z.y -= ((temp.y * temp2.y) / ((z.y * z.y) + (temp2.y)) - 2.0 * temp.y)
						 * fractal->transformCommon.scale1;
			z.z -= ((temp.z * temp2.z) / ((z.z * z.z) + (temp2.z)) - 2.0 * temp.z)
						 * fractal->transformCommon.scale1;
		}
		if (fractal->transformCommon.functionEnabledByFalse)
		{
			CVector4 temp = fractal->transformCommon.additionConstant000;
			CVector4 temp2 = temp * temp;

			z.x -= ((temp2.x) / ((z.x * z.x) + (temp2.x)) - 2.0 * temp.x)
						 * fractal->transformCommon.scale1; // * sign(z.x);
			z.y -= ((temp2.y) / ((z.y * z.y) + (temp2.y)) - 2.0 * temp.y)
						 * fractal->transformCommon.scale1; // * sign(z.y);
			z.z -= ((temp2.z) / ((z.z * z.z) + (temp2.z)) - 2.0 * temp.z)
						 * fractal->transformCommon.scale1; // * sign(z.z);
		}
	}
	else if (aux.i >= fractal->transformCommon.startIterationsO
					 && aux.i < fractal->transformCommon.stopIterationsO)
		z += fractal->transformCommon.additionConstant000;

	// standard functions
	if (fractal->transformCommon.functionEnabledAy)
	{
		double rr = z.Dot(z);
		rrCol = rr;
		if (fractal->transformCommon.functionEnabledFalse
				&& aux.i >= fractal->transformCommon.startIterationsD
				&& aux.i < fractal->transformCommon.stopIterationsD) // force cylinder fold
			rr -= z.z * z.z * fractal->transformCommon.scaleB1;		 // fold weight

		// Mandelbox Spherical fold
		if (aux.i >= fractal->transformCommon.startIterationsM
				&& aux.i < fractal->transformCommon.stopIterationsM)
		{
			z += fractal->mandelbox.offset;

			// if (r2 < 1e-21) r2 = 1e-21;
			if (rr < fractal->transformCommon.minR0)
			{
				// double tglad_factor1 = fractal->transformCommon.maxR2d1 / fractal->transformCommon.minR0;
				z *= fractal->transformCommon.maxMinR0factor;
				aux.DE *= fractal->transformCommon.maxMinR0factor;
			}
			else if (rr < fractal->transformCommon.maxR2d1)
			{
				double tglad_factor2 = fractal->transformCommon.maxR2d1 / rr;
				z *= tglad_factor2;
				aux.DE *= tglad_factor2;
			}
			z -= fractal->mandelbox.offset;
		}

		// scale
		double useScale = 1.0;
		if (aux.i >= fractal->transformCommon.startIterationsS
				&& aux.i < fractal->transformCommon.stopIterationsS)
		{
			useScale = aux.actualScaleA + fractal->mandelbox.scale;

			z *= useScale;

			if (!fractal->analyticDE.enabledFalse)
				aux.DE = aux.DE * fabs(useScale) + 1.0;
			else
				aux.DE = aux.DE * fabs(useScale) * fractal->analyticDE.scale1 + fractal->analyticDE.offset1;

			if (fractal->transformCommon.functionEnabledFFalse
					&& aux.i >= fractal->transformCommon.startIterationsY
					&& aux.i < fractal->transformCommon.stopIterationsY)
			{
				// update actualScaleA for next iteration
				double vary = fractal->transformCommon.scaleVary0
											* (fabs(aux.actualScaleA) - fractal->transformCommon.scaleC1);
				if (fractal->transformCommon.functionEnabledMFalse)
					aux.actualScaleA = -vary;
				else
					aux.actualScaleA = aux.actualScaleA - vary;
			}
		}
	}

	if (fractal->mandelbox.mainRotationEnabled && aux.i >= fractal->transformCommon.startIterationsR
			&& aux.i < fractal->transformCommon.stopIterationsR)
		z = fractal->mandelbox.mainRot.RotateVector(z);

	if (fractal->foldColor.auxColorEnabledFalse)
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
			colorAdd += fractal->mandelbox.color.factorSp2 * (fractal->transformCommon.maxR2d1 - rrCol);
			if (rrCol < fractal->transformCommon.minR2p25)
				colorAdd += fractal->mandelbox.color.factorSp1 * (fractal->transformCommon.minR2p25 - rrCol)
										+ fractal->mandelbox.color.factorSp2
												* (fractal->transformCommon.maxR2d1 - fractal->transformCommon.minR2p25);
		}
		aux.color += colorAdd;
	}
	if (fractal->transformCommon.addCpixelEnabledFalse
			&& aux.i >= fractal->transformCommon.startIterationsH
			&& aux.i < fractal->transformCommon.stopIterationsH)
	{
		CVector4 tempC = aux.const_c;
		if (fractal->transformCommon.alternateEnabledFalse) // alternate
		{
			tempC = aux.c;
			switch (fractal->mandelbulbMulti.orderOfXYZ)
			{
				case multi_OrderOfXYZ_xyz:
				default: tempC = CVector4(tempC.x, tempC.y, tempC.z, tempC.w); break;
				case multi_OrderOfXYZ_xzy: tempC = CVector4(tempC.x, tempC.z, tempC.y, tempC.w); break;
				case multi_OrderOfXYZ_yxz: tempC = CVector4(tempC.y, tempC.x, tempC.z, tempC.w); break;
				case multi_OrderOfXYZ_yzx: tempC = CVector4(tempC.y, tempC.z, tempC.x, tempC.w); break;
				case multi_OrderOfXYZ_zxy: tempC = CVector4(tempC.z, tempC.x, tempC.y, tempC.w); break;
				case multi_OrderOfXYZ_zyx: tempC = CVector4(tempC.z, tempC.y, tempC.x, tempC.w); break;
			}
			aux.c = tempC;
		}
		else
		{
			switch (fractal->mandelbulbMulti.orderOfXYZ)
			{
				case multi_OrderOfXYZ_xyz:
				default: tempC = CVector4(c.x, c.y, c.z, c.w); break;
				case multi_OrderOfXYZ_xzy: tempC = CVector4(c.x, c.z, c.y, c.w); break;
				case multi_OrderOfXYZ_yxz: tempC = CVector4(c.y, c.x, c.z, c.w); break;
				case multi_OrderOfXYZ_yzx: tempC = CVector4(c.y, c.z, c.x, c.w); break;
				case multi_OrderOfXYZ_zxy: tempC = CVector4(c.z, c.x, c.y, c.w); break;
				case multi_OrderOfXYZ_zyx: tempC = CVector4(c.z, c.y, c.x, c.w); break;
			}
		}
		if (fractal->transformCommon.rotationEnabled
				&& aux.i >= fractal->transformCommon.startIterationsG
				&& aux.i < fractal->transformCommon.stopIterationsG)
		{
			tempC = fractal->transformCommon.rotationMatrix.RotateVector(tempC);
		}
		z += tempC * fractal->transformCommon.constantMultiplier111;
	}

	// invert c
	if (fractal->transformCommon.functionEnabledCxFalse
			&& aux.i >= fractal->transformCommon.startIterationsF
			&& aux.i < fractal->transformCommon.stopIterationsF)
	{
		if (fractal->transformCommon.functionEnabledCyFalse)
		{
			aux.c *= fractal->transformCommon.scale3D111;
			double rSqrL = aux.c.Dot(aux.c);
			rSqrL = 1.0 / rSqrL;
			aux.c *= rSqrL;
			z += aux.c;
		}
		else
		{
			c *= fractal->transformCommon.scale3D111;
			double rSqrL = c.Dot(c);
			rSqrL = 1.0 / rSqrL;
			z += c * rSqrL;
		}
	}
	// =============================================
	// === AMAZING SURF EXTENSIONS (#31-#40) ===
	// =============================================

	// === SURF #31: Fold Power ===
	if (fractal->transformCommon.surfFoldPower != 1.0)
	{
		double p = fractal->transformCommon.surfFoldPower;
		z.x = sign(z.x) * pow(fabs(z.x) + 1e-30, p);
		z.y = sign(z.y) * pow(fabs(z.y) + 1e-30, p);
		z.z = sign(z.z) * pow(fabs(z.z) + 1e-30, p);
	}

	// === SURF #32-33: Scale Oscillation ===
	if (fractal->transformCommon.surfScaleOscAmp != 0.0)
	{
		aux.actualScale += fractal->transformCommon.surfScaleOscAmp
			* sin((double)aux.i * fractal->transformCommon.surfScaleOscFreq);
	}

	// === SURF #34: Fold Warp ===
	if (fractal->transformCommon.surfFoldWarp != 0.0)
	{
		double warp = fractal->transformCommon.surfFoldWarp * sin((double)aux.i * 0.5);
		double oldX = z.x;
		z.x += warp * z.y;
		z.y += warp * oldX;
	}

	// === SURF #35: Post-Scale Z-Rotation ===
	if (fractal->transformCommon.surfPostRotZ != 0.0)
	{
		double angle = fractal->transformCommon.surfPostRotZ * M_PI / 180.0;
		double cosA = cos(angle);
		double sinA = sin(angle);
		double xn = z.x * cosA - z.y * sinA;
		double yn = z.x * sinA + z.y * cosA;
		z.x = xn;
		z.y = yn;
	}

	// === SURF #36: Gradient Coloring (fold boundary proximity) ===
	if (fractal->transformCommon.surfGradientColor != 0.0)
	{
		double foldDist = fmin(fabs(fabs(z.x) - 1.0), fabs(fabs(z.y) - 1.0));
		aux.color += foldDist * fractal->transformCommon.surfGradientColor;
	}

	// === SURF #37: Turbulence Injection ===
	if (fractal->transformCommon.surfTurbulence != 0.0)
	{
		double turb = fractal->transformCommon.surfTurbulence;
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

	// === SURF #38: MinR Oscillation ===
	if (fractal->transformCommon.surfMinROsc != 0.0)
	{
		double rLocal = z.Length();
		double minROsc = fractal->transformCommon.surfMinROsc * sin((double)aux.i * 0.3);
		double factor = 1.0 + minROsc / (rLocal + 1e-21);
		z *= factor;
		aux.DE *= fabs(factor);
	}

	// === SURF #39: C-Pixel Decay ===
	if (fractal->transformCommon.surfCpixelDecay != 0.0 && aux.i > 0)
	{
		double decay = exp(-fractal->transformCommon.surfCpixelDecay * (double)aux.i);
		z -= aux.const_c * (1.0 - decay);
	}

	// === SURF #40: Sphere Softness ===
	if (fractal->transformCommon.surfSphereSoftness > 0.0)
	{
		double rr2 = z.Dot(z);
		double s = fractal->transformCommon.surfSphereSoftness;
		double t = fmax(0.0, fmin(1.0, (rr2 - 0.25) / (s + 1e-21)));
		t = t * t * (3.0 - 2.0 * t);
		double softScale = 1.0 + (1.0 - t) * s;
		z *= softScale;
		aux.DE *= fabs(softScale);
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
