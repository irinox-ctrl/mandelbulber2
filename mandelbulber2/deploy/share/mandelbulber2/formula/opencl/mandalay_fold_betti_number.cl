/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Mandalay Fold: Betti-getal in Mandalay Fold.
 */

REAL4 MandalayFoldBettiNumberIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Mandalay base: abs fold
	z = fabs(z);

	// Sort for Mandalay clip
	REAL tmp;
	if (z.z > z.y) { tmp = z.y; z.y = z.z; z.z = tmp; }
	if (z.y > z.x) { tmp = z.x; z.x = z.y; z.y = tmp; }
	if (z.z > z.y) { tmp = z.y; z.y = z.z; z.z = tmp; }

	// Betti Number fold: topological holes
	REAL s = fractal->transformCommon.scale08;
	REAL b0 = 1.0;
	REAL r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
	REAL b1 = (r > 0.5 && r < 1.5) ? 1.0 : 0.0;
	z.x *= (1.0 + (b0 + b1) * s * 0.1);
	z.y *= (1.0 + (b0 + b1) * s * 0.1);

	// Spherical fold
	REAL rr = dot(z, z);
	if (rr < fractal->transformCommon.minR2p25)
	{
		REAL tglad_factor1 = fractal->transformCommon.maxR2d1 / fractal->transformCommon.minR2p25;
		z *= tglad_factor1;
		aux->DE *= tglad_factor1;
	}
	else if (rr < fractal->transformCommon.maxR2d1)
	{
		REAL tglad_factor2 = fractal->transformCommon.maxR2d1 / rr;
		z *= tglad_factor2;
		aux->DE *= tglad_factor2;
	}

	// Scale
	REAL useScale = fractal->transformCommon.scale2;
	z *= useScale;
	aux->DE = aux->DE * fabs(useScale) + 1.0f;


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

				if (fractal->transformCommon.multiplierInverse1) val = (fabs(val) > 1e-15f) ? (1.0f / val) : 1e15f;

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

				if (fractal->transformCommon.multiplierInverse2) val = (fabs(val) > 1e-15f) ? (1.0f / val) : 1e15f;

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

				if (fractal->transformCommon.multiplierInverse3) val = (fabs(val) > 1e-15f) ? (1.0f / val) : 1e15f;

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

				if (fractal->transformCommon.multiplierInverse4) val = (fabs(val) > 1e-15f) ? (1.0f / val) : 1e15f;

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

				if (fractal->transformCommon.multiplierInverse5) val = (fabs(val) > 1e-15f) ? (1.0f / val) : 1e15f;

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

	return z;
}
