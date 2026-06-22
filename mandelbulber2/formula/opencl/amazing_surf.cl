/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.        ____                _______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,     / __ \___  ___ ___  / ___/ /
 *                                        \><||i|=>>%)    / /_/ / _ \/ -_) _ \/ /__/ /__
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    \____/ .__/\__/_//_/\___/____/
 * The project is licensed under GPLv3,   -<>>=|><|||`        /_/
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

REAL4 AmazingSurfIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// update aux->actualScale
	aux->actualScale =
		fractal->mandelbox.scale + fractal->mandelboxVary4D.scaleVary * (fabs(aux->actualScale) - 1.0f);

	REAL4 c = aux->const_c;

	// === CAT 3 #16: Pre-Sphere Inversie (Möbius) ===
	if (fractal->transformCommon.functionEnabledPFalse
		&& aux->i >= fractal->transformCommon.startIterationsP
		&& aux->i < fractal->transformCommon.stopIterationsP)
	{
		REAL4 center = fractal->transformCommon.offset000;
		REAL r2 = fractal->transformCommon.radius1 * fractal->transformCommon.radius1;
		REAL4 diff = z - center;
		REAL d2 = dot(diff, diff);
		if (d2 > 1e-21f)
		{
			z = center + diff * (r2 / d2);
			aux->DE *= r2 / d2;
		}
	}

	// === CAT 3 #18: Pre-Rotation ===
	if (fractal->transformCommon.functionEnabledRFalse
		&& aux->i >= fractal->transformCommon.startIterationsR
		&& aux->i < fractal->transformCommon.stopIterationsR)
	{
		z = Matrix33MulFloat4(fractal->transformCommon.rotationMatrix2, z);
	}

	// === CAT 3 #20: Möbius Pre-Transform ===
	if (fractal->transformCommon.functionEnabledMFalse
		&& aux->i >= fractal->transformCommon.startIterationsM
		&& aux->i < fractal->transformCommon.stopIterationsM)
	{
		REAL a = fractal->transformCommon.scale1;
		REAL b = fractal->transformCommon.offset05;
		REAL d = fractal->transformCommon.offsetA1;
		REAL4 az = z * a + (REAL4){b, b, b, 0.0f};
		REAL denom = length(z) + d;
		if (fabs(denom) > 1e-21f)
		{
			z = az * (1.0f / denom);
			aux->DE *= fabs(a * d - b) / (denom * denom);
		}
	}

	// === CAT 1 #6: Pre-Abs ===
	if (fractal->transformCommon.functionEnabledAxFalse) z.x = fabs(z.x);
	if (fractal->transformCommon.functionEnabledAyFalse) z.y = fabs(z.y);
	if (fractal->transformCommon.functionEnabledAzFalse) z.z = fabs(z.z);

	// === CAT 3 #19: Z-Twist (Screw Motion) ===
	if (fractal->transformCommon.functionEnabledTFalse
		&& aux->i >= fractal->transformCommon.startIterationsT
		&& aux->i < fractal->transformCommon.stopIterationsT)
	{
		REAL angle = fractal->transformCommon.offset01 * z.z;
		REAL cosA = native_cos(angle);
		REAL sinA = native_sin(angle);
		REAL xn = z.x * cosA - z.y * sinA;
		REAL yn = z.x * sinA + z.y * cosA;
		z.x = xn;
		z.y = yn;
	}

	// === TGLAD BOX FOLD ===
	REAL foldX = fractal->transformCommon.additionConstant111.x;
	REAL foldY = fractal->transformCommon.additionConstant111.y;

	// === CAT 1 #2: Asymmetrische Fold ===
	if (fractal->transformCommon.functionEnabledBFalse)
	{
		REAL a = foldX;
		REAL b = fractal->transformCommon.offsetA05;
		z.x = fabs(z.x + a) - fabs(z.x - b) - z.x;
		REAL aY = foldY;
		REAL bY = fractal->transformCommon.offsetB05;
		z.y = fabs(z.y + aY) - fabs(z.y - bY) - z.y;
	}
	// === CAT 1 #3: Smooth Fold ===
	else if (fractal->transformCommon.functionEnabledCFalse)
	{
		REAL k = fractal->transformCommon.scale3;
		if (k > 0.01f)
		{
			z.x = z.x - tanh(k * z.x) / k;
			z.y = z.y - tanh(k * z.y) / k;
		}
	}
	else
	{
		z.x = fabs(z.x + foldX) - fabs(z.x - foldX) - z.x;
		z.y = fabs(z.y + foldY) - fabs(z.y - foldY) - z.y;
	}

	// === CAT 1 #1: Z-Axis Tglad Fold ===
	if (fractal->transformCommon.functionEnabledzFalse)
	{
		REAL foldZ = fractal->transformCommon.additionConstant111.z;
		z.z = fabs(z.z + foldZ) - fabs(z.z - foldZ) - z.z;
	}

	// === CAT 1 #4: Variable Fold per Iteratie ===
	if (fractal->transformCommon.functionEnabledDFalse
		&& aux->i >= fractal->transformCommon.startIterationsD
		&& aux->i < fractal->transformCommon.stopIterationsD)
	{
		REAL vary = fractal->transformCommon.scaleVary0;
		REAL factor = 1.0f + vary * native_sin((REAL)aux->i * 0.1f);
		z.x *= factor;
		z.y *= factor;
	}

	// === CAT 1 #5: Multi-Sequenced Fold (2nd pass) ===
	if (fractal->transformCommon.functionEnabledEFalse
		&& aux->i >= fractal->transformCommon.startIterationsE
		&& aux->i < fractal->transformCommon.stopIterationsE)
	{
		REAL fold2X = fractal->transformCommon.additionConstantA111.x;
		REAL fold2Y = fractal->transformCommon.additionConstantA111.y;
		z.x = fabs(z.x + fold2X) - fabs(z.x - fold2X) - z.x;
		z.y = fabs(z.y + fold2Y) - fabs(z.y - fold2Y) - z.y;
	}

	// === CAT 1 #7: Fold met Z-Shear ===
	if (fractal->transformCommon.functionEnabledFFalse
		&& aux->i >= fractal->transformCommon.startIterationsF
		&& aux->i < fractal->transformCommon.stopIterationsF)
	{
		z.z += fractal->transformCommon.offsetF0 * (z.x + z.y);
	}

	// === SPHERICAL FOLD SECTION ===
	REAL rr = dot(z, z);
	if (fractal->transformCommon.functionEnabledFalse) // force cylinder fold
		rr -= z.z * z.z;

	// === CAT 2 #8: Anisotrope Spherical Fold ===
	if (fractal->transformCommon.functionEnabledGFalse)
	{
		REAL4 axis = fractal->transformCommon.scale3D111;
		rr = 0.0f;
		if (fabs(axis.x) > 1e-21f) rr += (z.x * z.x) / (axis.x * axis.x);
		if (fabs(axis.y) > 1e-21f) rr += (z.y * z.y) / (axis.y * axis.y);
		if (fabs(axis.z) > 1e-21f) rr += (z.z * z.z) / (axis.z * axis.z);
	}

	// === CAT 2 #9: Torus Distance Fold ===
	if (fractal->transformCommon.functionEnabledHFalse)
	{
		REAL R = fractal->transformCommon.offsetR1;
		REAL xyDist = native_sqrt(z.x * z.x + z.y * z.y) - R;
		rr = xyDist * xyDist + z.z * z.z;
	}

	REAL sqrtMinR = native_sqrt(fractal->transformCommon.minR05);

	// === CAT 2 #10: Logarithmic Dividend ===
	REAL dividend;
	if (fractal->transformCommon.functionEnabledIFalse)
	{
		REAL k = fractal->transformCommon.scaleA1;
		if (k > 0.001f) dividend = native_log(1.0f + rr * k) / k;
		else dividend = rr;
	}
	// === CAT 2 #12: Smoothstep Dividend ===
	else if (fractal->transformCommon.functionEnabledJFalse)
	{
		REAL t = (rr - sqrtMinR) / (1.0f - sqrtMinR + 1e-21f);
		t = max(0.0f, min(1.0f, t));
		dividend = sqrtMinR + t * t * (3.0f - 2.0f * t) * (1.0f - sqrtMinR);
	}
	else
	{
		dividend = rr < sqrtMinR ? sqrtMinR : min(rr, 1.0f);
	}

	// === CAT 2 #11: Exponential Scale Factor ===
	REAL m;
	if (fractal->transformCommon.functionEnabledKFalse)
	{
		m = native_exp(aux->actualScale / (dividend + 1e-21f) - 1.0f);
	}
	else
	{
		m = aux->actualScale / (dividend + 1e-21f);
	}

	// === CAT 2 #13: Dual Scale (Bipolar) ===
	if (fractal->transformCommon.functionEnabledNFalse)
	{
		REAL scaleB = fractal->transformCommon.scaleB1;
		if (z.x < 0.0f) m = scaleB / (dividend + 1e-21f);
	}

	// === CAT 2 #14: Z-Scale Decoupled ===
	if (fractal->transformCommon.functionEnabledOFalse)
	{
		REAL mZ = fractal->transformCommon.scaleC1 / (dividend + 1e-21f);
		REAL scaleMix = (m - 1.0f) * fractal->transformCommon.scale1 + 1.0f;
		REAL scaleZ = (mZ - 1.0f) * fractal->transformCommon.scale1 + 1.0f;
		z.x *= scaleMix;
		z.y *= scaleMix;
		z.z *= scaleZ;
		aux->DE = aux->DE * max(fabs(m), fabs(mZ)) + 1.0f;
	}
	else
	{
		z *= (m - 1.0f) * fractal->transformCommon.scale1 + 1.0f;
		// === CAT 6 #28: DE Offset Tweak ===
		REAL deOffset = fractal->transformCommon.functionEnabledSFalse
			? fractal->transformCommon.offsetD0
			: 1.0f;
		aux->DE = aux->DE * fabs(m) + deOffset;
	}

	// === CAT 2 #15: Nested Spherical (2-lagen) ===
	if (fractal->transformCommon.functionEnabledXFalse
		&& aux->i >= fractal->transformCommon.startIterationsX
		&& aux->i < fractal->transformCommon.stopIterationsX)
	{
		REAL rr2 = dot(z, z);
		REAL sqrtMinR2 = sqrtMinR * fractal->transformCommon.scaleD1;
		REAL div2 = rr2 < sqrtMinR2 ? sqrtMinR2 : min(rr2, 1.0f);
		REAL m2 = aux->actualScale / (div2 + 1e-21f);
		z *= (m2 - 1.0f) * fractal->transformCommon.scale1 + 1.0f;
		aux->DE = aux->DE * fabs(m2) + 1.0f;
	}

	// === CAT 3 #17: Post-Fold Inversie ===
	if (fractal->transformCommon.functionEnabledYFalse
		&& aux->i >= fractal->transformCommon.startIterationsN
		&& aux->i < fractal->transformCommon.stopIterationsN)
	{
		REAL zLen2 = dot(z, z);
		if (zLen2 > 1e-21f)
		{
			z = z * (1.0f / zLen2);
			aux->DE *= 1.0f / zLen2;
		}
	}

	// === CAT 4 #21: C-Pixel Permutaties ===
	if (fractal->transformCommon.addCpixelEnabledFalse)
	{
		REAL4 cPerm;
		switch (fractal->transformCommon.intA)
		{
			case 0: cPerm = (REAL4){c.y, c.x, c.z, c.w}; break;
			case 1: cPerm = (REAL4){c.x, c.y, c.z, c.w}; break;
			case 2: cPerm = (REAL4){c.x, c.z, c.y, c.w}; break;
			case 3: cPerm = (REAL4){c.y, c.z, c.x, c.w}; break;
			case 4: cPerm = (REAL4){c.z, c.x, c.y, c.w}; break;
			case 5: cPerm = (REAL4){c.z, c.y, c.x, c.w}; break;
			default: cPerm = (REAL4){c.y, c.x, c.z, c.w}; break;
		}

		// === CAT 4 #22: C-Pixel Modulation ===
		if (fractal->transformCommon.functionEnabledAFalse)
		{
			REAL modFactor = 1.0f + fractal->transformCommon.scaleA0
				* native_sin((REAL)aux->i * fractal->transformCommon.scaleB0);
			cPerm *= modFactor;
		}

		// === CAT 4 #23: Bipolar C-Pixel ===
		if (fractal->transformCommon.functionEnabled4dFalse)
		{
			cPerm *= (z.x >= 0.0f ? 1.0f : -1.0f);
		}

		// === CAT 4 #24: C-Pixel met Orbit feedback ===
		if (fractal->transformCommon.functionEnabledAuxCFalse)
		{
			cPerm = cPerm + (z - aux->old_z) * 0.1f;
		}

		z += cPerm * fractal->transformCommon.constantMultiplier111;
	}

	// === CAT 6 #29: Color Trap op m-waarde ===
	if (fractal->transformCommon.functionEnabledCxFalse)
	{
		aux->color += fabs(m - 1.0f) * fractal->transformCommon.scaleE1;
	}

	// === CAT 6 #30: Orbit Trap: Cross ===
	if (fractal->transformCommon.functionEnabledCyFalse)
	{
		REAL trap = min(fabs(z.x), min(fabs(z.y), fabs(z.z)));
		aux->color += trap * fractal->transformCommon.scaleF1;
	}

	// === CAT 5 #25: Fibonacci / Golden Angle Rotation ===
	if (fractal->transformCommon.functionEnabledSwFalse)
	{
		REAL angle = (REAL)aux->i * 2.39996322972865332f;
		REAL cosG = native_cos(angle);
		REAL sinG = native_sin(angle);
		REAL xn = z.x * cosG - z.y * sinG;
		REAL yn = z.x * sinG + z.y * cosG;
		z.x = xn;
		z.y = yn;
	}

	// GPU bypass: skip if all multipliers disabled
	if (fractal->transformCommon.functionEnabledBxFalse || fractal->transformCommon.functionEnabledByFalse || fractal->transformCommon.functionEnabledBzFalse || fractal->transformCommon.functionEnabledBwFalse || fractal->transformCommon.functionEnabledCzFalse)
	{
		REAL prevMultVal = 1.0;
		// === General Purpose Multiplier 1 ===
		if (fractal->transformCommon.functionEnabledBxFalse
				&& aux->i >= fractal->transformCommon.startIterationsB
				&& aux->i < fractal->transformCommon.stopIterationsB)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode1;
			REAL threshR = length(z);
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold1)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold1))
			{
				REAL val = fractal->transformCommon.scale4;

				if (fractal->transformCommon.multiplierInverse1) val = 1.0 / val;

				int vmode = fractal->transformCommon.multiplierValueMode1;
				REAL range = (REAL)(fractal->transformCommon.stopIterationsB - fractal->transformCommon.startIterationsB);
				REAL ph = fractal->transformCommon.multiplierPhase1;
				if (range > 0 && vmode > 0)
				{
					REAL t = (REAL)(aux->i - fractal->transformCommon.startIterationsB) / range;
					REAL freq = fractal->transformCommon.multiplierFrequency1;
					if (vmode == 1) // Sine
					{
						val = 1.0 + (val - 1.0) * native_sin((t * freq + ph) * 2.0 * M_PI_F);
					}
					else if (vmode == 2) // Ramp
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 3) // Exponential
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						val = 1.0 + (val - 1.0) * (native_powr(2.718281828f, t * freq) - 1.0) / (native_powr(2.718281828f, freq) - 1.0);
					}
					else if (vmode == 4) // Triangle
					{
						REAL tri = 1.0 - 2.0 * fabs(fmod(t * freq + ph, 1.0) - 0.5);
						val = 1.0 + (val - 1.0) * tri;
					}
					else if (vmode == 5) // Square
					{
						val = (fmod(t * freq + ph, 1.0) < 0.5) ? val : 1.0;
					}
					else if (vmode == 6) // Smoothstep
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						t = t * t * (3.0 - 2.0 * t);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 7) // Noise
					{
						int seed = aux->i * 73856093 + 1 * 19349663;
						seed = (seed ^ (seed >> 13)) * 1274126177;
						seed = seed ^ (seed >> 16);
						REAL noise = (REAL)(seed & 0xFFFF) / 65535.0;
						val = 1.0 + (val - 1.0) * noise;
					}
					else if (vmode == 8) // Ping-pong
					{
						REAL pp = fmod(t * freq + ph, 2.0);
						if (pp > 1.0) pp = 2.0 - pp;
						val = 1.0 + (val - 1.0) * pp;
					}
					else if (vmode == 9) // Stepped
					{
						REAL steps = freq;
						if (steps < 1.0) steps = 1.0;
						REAL st = floor(t * steps) / steps;
						val = 1.0 + (val - 1.0) * st;
					}
				}

				REAL w = fractal->transformCommon.multiplierWeight1;
				val = 1.0 + w * (val - 1.0);

				switch (fractal->transformCommon.multiplierMode1)
				{
					default:
					case 0:
					{
						REAL valY = fractal->transformCommon.multiplierScaleY1;
						REAL valZ = fractal->transformCommon.multiplierScaleZ1;
						if (valY == 0.0) valY = val;
						if (valZ == 0.0) valZ = val;
						z.x *= val; z.y *= valY; z.z *= valZ;
						aux->DE *= fabs(val);
						break;
					}
					case 1: z.x *= val; break;
					case 2: z.y *= val; break;
					case 3: z.z *= val; break;
					case 4: aux->DE *= val; break;
					case 5: aux->color *= val; break;
					case 6: z.w *= val; break;
					case 7: z.x *= val; z.y *= val; break;
					case 8: z.x *= val; z.z *= val; break;
					case 9: z.y *= val; z.z *= val; break;
					case 10: aux->color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 2 ===
		if (fractal->transformCommon.functionEnabledByFalse
				&& aux->i >= fractal->transformCommon.startIterationsC
				&& aux->i < fractal->transformCommon.stopIterationsC)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode2;
			REAL threshR = length(z);
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold2)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold2))
			{
				REAL val = fractal->transformCommon.scale5;

				if (fractal->transformCommon.multiplierInverse2) val = 1.0 / val;

				int vmode = fractal->transformCommon.multiplierValueMode2;
				REAL range = (REAL)(fractal->transformCommon.stopIterationsC - fractal->transformCommon.startIterationsC);
				REAL ph = fractal->transformCommon.multiplierPhase2;
				if (range > 0 && vmode > 0)
				{
					REAL t = (REAL)(aux->i - fractal->transformCommon.startIterationsC) / range;
					REAL freq = fractal->transformCommon.multiplierFrequency2;
					if (vmode == 1) // Sine
					{
						val = 1.0 + (val - 1.0) * native_sin((t * freq + ph) * 2.0 * M_PI_F);
					}
					else if (vmode == 2) // Ramp
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 3) // Exponential
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						val = 1.0 + (val - 1.0) * (native_powr(2.718281828f, t * freq) - 1.0) / (native_powr(2.718281828f, freq) - 1.0);
					}
					else if (vmode == 4) // Triangle
					{
						REAL tri = 1.0 - 2.0 * fabs(fmod(t * freq + ph, 1.0) - 0.5);
						val = 1.0 + (val - 1.0) * tri;
					}
					else if (vmode == 5) // Square
					{
						val = (fmod(t * freq + ph, 1.0) < 0.5) ? val : 1.0;
					}
					else if (vmode == 6) // Smoothstep
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						t = t * t * (3.0 - 2.0 * t);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 7) // Noise
					{
						int seed = aux->i * 73856093 + 2 * 19349663;
						seed = (seed ^ (seed >> 13)) * 1274126177;
						seed = seed ^ (seed >> 16);
						REAL noise = (REAL)(seed & 0xFFFF) / 65535.0;
						val = 1.0 + (val - 1.0) * noise;
					}
					else if (vmode == 8) // Ping-pong
					{
						REAL pp = fmod(t * freq + ph, 2.0);
						if (pp > 1.0) pp = 2.0 - pp;
						val = 1.0 + (val - 1.0) * pp;
					}
					else if (vmode == 9) // Stepped
					{
						REAL steps = freq;
						if (steps < 1.0) steps = 1.0;
						REAL st = floor(t * steps) / steps;
						val = 1.0 + (val - 1.0) * st;
					}
				}

				if (fractal->transformCommon.multiplierChain2) val *= prevMultVal;

				REAL w = fractal->transformCommon.multiplierWeight2;
				val = 1.0 + w * (val - 1.0);

				switch (fractal->transformCommon.multiplierMode2)
				{
					default:
					case 0:
					{
						REAL valY = fractal->transformCommon.multiplierScaleY2;
						REAL valZ = fractal->transformCommon.multiplierScaleZ2;
						if (valY == 0.0) valY = val;
						if (valZ == 0.0) valZ = val;
						z.x *= val; z.y *= valY; z.z *= valZ;
						aux->DE *= fabs(val);
						break;
					}
					case 1: z.x *= val; break;
					case 2: z.y *= val; break;
					case 3: z.z *= val; break;
					case 4: aux->DE *= val; break;
					case 5: aux->color *= val; break;
					case 6: z.w *= val; break;
					case 7: z.x *= val; z.y *= val; break;
					case 8: z.x *= val; z.z *= val; break;
					case 9: z.y *= val; z.z *= val; break;
					case 10: aux->color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 3 ===
		if (fractal->transformCommon.functionEnabledBzFalse
				&& aux->i >= fractal->transformCommon.startIterationsD
				&& aux->i < fractal->transformCommon.stopIterationsD)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode3;
			REAL threshR = length(z);
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold3)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold3))
			{
				REAL val = fractal->transformCommon.scale6;

				if (fractal->transformCommon.multiplierInverse3) val = 1.0 / val;

				int vmode = fractal->transformCommon.multiplierValueMode3;
				REAL range = (REAL)(fractal->transformCommon.stopIterationsD - fractal->transformCommon.startIterationsD);
				REAL ph = fractal->transformCommon.multiplierPhase3;
				if (range > 0 && vmode > 0)
				{
					REAL t = (REAL)(aux->i - fractal->transformCommon.startIterationsD) / range;
					REAL freq = fractal->transformCommon.multiplierFrequency3;
					if (vmode == 1) // Sine
					{
						val = 1.0 + (val - 1.0) * native_sin((t * freq + ph) * 2.0 * M_PI_F);
					}
					else if (vmode == 2) // Ramp
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 3) // Exponential
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						val = 1.0 + (val - 1.0) * (native_powr(2.718281828f, t * freq) - 1.0) / (native_powr(2.718281828f, freq) - 1.0);
					}
					else if (vmode == 4) // Triangle
					{
						REAL tri = 1.0 - 2.0 * fabs(fmod(t * freq + ph, 1.0) - 0.5);
						val = 1.0 + (val - 1.0) * tri;
					}
					else if (vmode == 5) // Square
					{
						val = (fmod(t * freq + ph, 1.0) < 0.5) ? val : 1.0;
					}
					else if (vmode == 6) // Smoothstep
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						t = t * t * (3.0 - 2.0 * t);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 7) // Noise
					{
						int seed = aux->i * 73856093 + 3 * 19349663;
						seed = (seed ^ (seed >> 13)) * 1274126177;
						seed = seed ^ (seed >> 16);
						REAL noise = (REAL)(seed & 0xFFFF) / 65535.0;
						val = 1.0 + (val - 1.0) * noise;
					}
					else if (vmode == 8) // Ping-pong
					{
						REAL pp = fmod(t * freq + ph, 2.0);
						if (pp > 1.0) pp = 2.0 - pp;
						val = 1.0 + (val - 1.0) * pp;
					}
					else if (vmode == 9) // Stepped
					{
						REAL steps = freq;
						if (steps < 1.0) steps = 1.0;
						REAL st = floor(t * steps) / steps;
						val = 1.0 + (val - 1.0) * st;
					}
				}

				if (fractal->transformCommon.multiplierChain3) val *= prevMultVal;

				REAL w = fractal->transformCommon.multiplierWeight3;
				val = 1.0 + w * (val - 1.0);

				switch (fractal->transformCommon.multiplierMode3)
				{
					default:
					case 0:
					{
						REAL valY = fractal->transformCommon.multiplierScaleY3;
						REAL valZ = fractal->transformCommon.multiplierScaleZ3;
						if (valY == 0.0) valY = val;
						if (valZ == 0.0) valZ = val;
						z.x *= val; z.y *= valY; z.z *= valZ;
						aux->DE *= fabs(val);
						break;
					}
					case 1: z.x *= val; break;
					case 2: z.y *= val; break;
					case 3: z.z *= val; break;
					case 4: aux->DE *= val; break;
					case 5: aux->color *= val; break;
					case 6: z.w *= val; break;
					case 7: z.x *= val; z.y *= val; break;
					case 8: z.x *= val; z.z *= val; break;
					case 9: z.y *= val; z.z *= val; break;
					case 10: aux->color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 4 ===
		if (fractal->transformCommon.functionEnabledBwFalse
				&& aux->i >= fractal->transformCommon.startIterationsE
				&& aux->i < fractal->transformCommon.stopIterationsE)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode4;
			REAL threshR = length(z);
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold4)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold4))
			{
				REAL val = fractal->transformCommon.scale8;

				if (fractal->transformCommon.multiplierInverse4) val = 1.0 / val;

				int vmode = fractal->transformCommon.multiplierValueMode4;
				REAL range = (REAL)(fractal->transformCommon.stopIterationsE - fractal->transformCommon.startIterationsE);
				REAL ph = fractal->transformCommon.multiplierPhase4;
				if (range > 0 && vmode > 0)
				{
					REAL t = (REAL)(aux->i - fractal->transformCommon.startIterationsE) / range;
					REAL freq = fractal->transformCommon.multiplierFrequency4;
					if (vmode == 1) // Sine
					{
						val = 1.0 + (val - 1.0) * native_sin((t * freq + ph) * 2.0 * M_PI_F);
					}
					else if (vmode == 2) // Ramp
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 3) // Exponential
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						val = 1.0 + (val - 1.0) * (native_powr(2.718281828f, t * freq) - 1.0) / (native_powr(2.718281828f, freq) - 1.0);
					}
					else if (vmode == 4) // Triangle
					{
						REAL tri = 1.0 - 2.0 * fabs(fmod(t * freq + ph, 1.0) - 0.5);
						val = 1.0 + (val - 1.0) * tri;
					}
					else if (vmode == 5) // Square
					{
						val = (fmod(t * freq + ph, 1.0) < 0.5) ? val : 1.0;
					}
					else if (vmode == 6) // Smoothstep
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						t = t * t * (3.0 - 2.0 * t);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 7) // Noise
					{
						int seed = aux->i * 73856093 + 4 * 19349663;
						seed = (seed ^ (seed >> 13)) * 1274126177;
						seed = seed ^ (seed >> 16);
						REAL noise = (REAL)(seed & 0xFFFF) / 65535.0;
						val = 1.0 + (val - 1.0) * noise;
					}
					else if (vmode == 8) // Ping-pong
					{
						REAL pp = fmod(t * freq + ph, 2.0);
						if (pp > 1.0) pp = 2.0 - pp;
						val = 1.0 + (val - 1.0) * pp;
					}
					else if (vmode == 9) // Stepped
					{
						REAL steps = freq;
						if (steps < 1.0) steps = 1.0;
						REAL st = floor(t * steps) / steps;
						val = 1.0 + (val - 1.0) * st;
					}
				}

				if (fractal->transformCommon.multiplierChain4) val *= prevMultVal;

				REAL w = fractal->transformCommon.multiplierWeight4;
				val = 1.0 + w * (val - 1.0);

				switch (fractal->transformCommon.multiplierMode4)
				{
					default:
					case 0:
					{
						REAL valY = fractal->transformCommon.multiplierScaleY4;
						REAL valZ = fractal->transformCommon.multiplierScaleZ4;
						if (valY == 0.0) valY = val;
						if (valZ == 0.0) valZ = val;
						z.x *= val; z.y *= valY; z.z *= valZ;
						aux->DE *= fabs(val);
						break;
					}
					case 1: z.x *= val; break;
					case 2: z.y *= val; break;
					case 3: z.z *= val; break;
					case 4: aux->DE *= val; break;
					case 5: aux->color *= val; break;
					case 6: z.w *= val; break;
					case 7: z.x *= val; z.y *= val; break;
					case 8: z.x *= val; z.z *= val; break;
					case 9: z.y *= val; z.z *= val; break;
					case 10: aux->color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 5 ===
		if (fractal->transformCommon.functionEnabledCzFalse
				&& aux->i >= fractal->transformCommon.startIterationsF
				&& aux->i < fractal->transformCommon.stopIterationsF)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode5;
			REAL threshR = length(z);
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold5)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold5))
			{
				REAL val = fractal->transformCommon.scale16;

				if (fractal->transformCommon.multiplierInverse5) val = 1.0 / val;

				int vmode = fractal->transformCommon.multiplierValueMode5;
				REAL range = (REAL)(fractal->transformCommon.stopIterationsF - fractal->transformCommon.startIterationsF);
				REAL ph = fractal->transformCommon.multiplierPhase5;
				if (range > 0 && vmode > 0)
				{
					REAL t = (REAL)(aux->i - fractal->transformCommon.startIterationsF) / range;
					REAL freq = fractal->transformCommon.multiplierFrequency5;
					if (vmode == 1) // Sine
					{
						val = 1.0 + (val - 1.0) * native_sin((t * freq + ph) * 2.0 * M_PI_F);
					}
					else if (vmode == 2) // Ramp
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 3) // Exponential
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						val = 1.0 + (val - 1.0) * (native_powr(2.718281828f, t * freq) - 1.0) / (native_powr(2.718281828f, freq) - 1.0);
					}
					else if (vmode == 4) // Triangle
					{
						REAL tri = 1.0 - 2.0 * fabs(fmod(t * freq + ph, 1.0) - 0.5);
						val = 1.0 + (val - 1.0) * tri;
					}
					else if (vmode == 5) // Square
					{
						val = (fmod(t * freq + ph, 1.0) < 0.5) ? val : 1.0;
					}
					else if (vmode == 6) // Smoothstep
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						t = t * t * (3.0 - 2.0 * t);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 7) // Noise
					{
						int seed = aux->i * 73856093 + 5 * 19349663;
						seed = (seed ^ (seed >> 13)) * 1274126177;
						seed = seed ^ (seed >> 16);
						REAL noise = (REAL)(seed & 0xFFFF) / 65535.0;
						val = 1.0 + (val - 1.0) * noise;
					}
					else if (vmode == 8) // Ping-pong
					{
						REAL pp = fmod(t * freq + ph, 2.0);
						if (pp > 1.0) pp = 2.0 - pp;
						val = 1.0 + (val - 1.0) * pp;
					}
					else if (vmode == 9) // Stepped
					{
						REAL steps = freq;
						if (steps < 1.0) steps = 1.0;
						REAL st = floor(t * steps) / steps;
						val = 1.0 + (val - 1.0) * st;
					}
				}

				if (fractal->transformCommon.multiplierChain5) val *= prevMultVal;

				REAL w = fractal->transformCommon.multiplierWeight5;
				val = 1.0 + w * (val - 1.0);

				switch (fractal->transformCommon.multiplierMode5)
				{
					default:
					case 0:
					{
						REAL valY = fractal->transformCommon.multiplierScaleY5;
						REAL valZ = fractal->transformCommon.multiplierScaleZ5;
						if (valY == 0.0) valY = val;
						if (valZ == 0.0) valZ = val;
						z.x *= val; z.y *= valY; z.z *= valZ;
						aux->DE *= fabs(val);
						break;
					}
					case 1: z.x *= val; break;
					case 2: z.y *= val; break;
					case 3: z.z *= val; break;
					case 4: aux->DE *= val; break;
					case 5: aux->color *= val; break;
					case 6: z.w *= val; break;
					case 7: z.x *= val; z.y *= val; break;
					case 8: z.x *= val; z.z *= val; break;
					case 9: z.y *= val; z.z *= val; break;
					case 10: aux->color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}
	}

	// Post-Rotation (original)
	z = Matrix33MulFloat4(fractal->transformCommon.rotationMatrix, z);

	aux->old_z = z;
	return z;
}
