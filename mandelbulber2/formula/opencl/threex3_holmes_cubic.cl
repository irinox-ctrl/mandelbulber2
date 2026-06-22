/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Holmes' kubische.
 */

REAL4 Threex3HolmesCubicIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Holmes Cubic: x_{n+1} = y_n, y_{n+1} = -b*x_n + a*y_n - y_n³
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	// Dynamic system: coupled oscillator map
	REAL a = fractal->transformCommon.scale1;
	if (a == 0.0) a = 1.4;
	REAL b = fractal->transformCommon.offset0;
	if (b == 0.0) b = 0.3;
	REAL newX = 1.0 - a * z.x * z.x + z.y;
	REAL newY = b * z.x + z.z * fractal->transformCommon.offsetA0;
	REAL newZ = sin(z.z * power) + z.x * fractal->transformCommon.offsetB0;
	aux->DE = aux->DE * fabs(2.0 * a * z.x) + 1.0;
	z.x = newX;
	z.y = newY;
	z.z = newZ;

	// GPU bypass: skip if all multipliers disabled
	if (fractal->transformCommon.multiplierEnabled1 || fractal->transformCommon.multiplierEnabled2 || fractal->transformCommon.multiplierEnabled3 || fractal->transformCommon.multiplierEnabled4 || fractal->transformCommon.multiplierEnabled5)
	{
		REAL prevMultVal = 1.0;
		// === General Purpose Multiplier 1 ===
		if (fractal->transformCommon.multiplierEnabled1
				&& aux->i >= fractal->transformCommon.multiplierStartIter1
				&& aux->i < fractal->transformCommon.multiplierStopIter1)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode1;
			REAL threshR = length(z);
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold1)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold1))
			{
				REAL val = fractal->transformCommon.multiplierScale1;

				if (fractal->transformCommon.multiplierInverse1) val = (fabs(val) > 1e-15f) ? (1.0f / val) : 1e15f;

				int vmode = fractal->transformCommon.multiplierValueMode1;
				REAL range = (REAL)(fractal->transformCommon.multiplierStopIter1 - fractal->transformCommon.multiplierStartIter1);
				REAL ph = fractal->transformCommon.multiplierPhase1;
				if (range > 0 && vmode > 0)
				{
					REAL t = (REAL)(aux->i - fractal->transformCommon.multiplierStartIter1) / range;
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

							// Decay
							if (fractal->transformCommon.multiplierDecay1 > 0.0f)
							{
								REAL dcy = fractal->transformCommon.multiplierDecay1;
								REAL rng = (REAL)(fractal->transformCommon.multiplierStopIter1 - fractal->transformCommon.multiplierStartIter1);
								REAL td = (rng > 0.0f) ? (REAL)(aux->i - fractal->transformCommon.multiplierStartIter1) / rng : 0.0f;
								val = 1.0f + (val - 1.0f) * native_exp(-dcy * td * 5.0f);
							}
							// Exponent
							if (fractal->transformCommon.multiplierExponent1 != 1.0f)
							{
								REAL ep = fractal->transformCommon.multiplierExponent1;
								REAL sgn = (val >= 1.0f) ? 1.0f : -1.0f;
								val = 1.0f + sgn * native_powr(fabs(val - 1.0f) + 1e-30f, ep);
							}
							// Offset
							val += fractal->transformCommon.multiplierOffset1;

							// Delay
							if (fractal->transformCommon.multiplierDelay1 > 0
								&& aux->i < fractal->transformCommon.multiplierStartIter1 + fractal->transformCommon.multiplierDelay1)
								val = 1.0f;
							// Iteration Modulo
							if (fractal->transformCommon.multiplierIterModulo1 > 1
								&& ((aux->i - fractal->transformCommon.multiplierStartIter1) % fractal->transformCommon.multiplierIterModulo1) != 0)
								val = 1.0f;
							// Attack envelope
							if (fractal->transformCommon.multiplierAttack1 > 0.0f)
							{
								REAL rng = (REAL)(fractal->transformCommon.multiplierStopIter1 - fractal->transformCommon.multiplierStartIter1);
								REAL td = (rng > 0.0f) ? (REAL)(aux->i - fractal->transformCommon.multiplierStartIter1) / rng : 1.0f;
								REAL att = fractal->transformCommon.multiplierAttack1;
								if (td < att) val = 1.0f + (val - 1.0f) * (td / att);
							}
							// Release envelope
							if (fractal->transformCommon.multiplierRelease1 > 0.0f)
							{
								REAL rng = (REAL)(fractal->transformCommon.multiplierStopIter1 - fractal->transformCommon.multiplierStartIter1);
								REAL td = (rng > 0.0f) ? (REAL)(aux->i - fractal->transformCommon.multiplierStartIter1) / rng : 1.0f;
								REAL rel = fractal->transformCommon.multiplierRelease1;
								if (td > (1.0f - rel)) val = 1.0f + (val - 1.0f) * ((1.0f - td) / rel);
							}
							// Feedback
							if (fractal->transformCommon.multiplierFeedback1 > 0.0f)
							{
								REAL fb = fractal->transformCommon.multiplierFeedback1;
								val = 1.0f + (val - 1.0f) * (1.0f - fb) + (prevMultVal - 1.0f) * fb;
							}
							// Harmonics
							if (fractal->transformCommon.multiplierHarmonics1 > 0.0f)
							{
								REAL rng = (REAL)(fractal->transformCommon.multiplierStopIter1 - fractal->transformCommon.multiplierStartIter1);
								REAL td = (rng > 0.0f) ? (REAL)(aux->i - fractal->transformCommon.multiplierStartIter1) / rng : 0.0f;
								REAL hrm = fractal->transformCommon.multiplierHarmonics1;
								REAL frq = fractal->transformCommon.multiplierFrequency1;
								val += hrm * native_sin(4.0f * M_PI_F * frq * td) * fabs(val - 1.0f);
							}
							// Pulse Width
							if (fractal->transformCommon.multiplierPulseWidth1 != 0.5f)
							{
								REAL pw = fractal->transformCommon.multiplierPulseWidth1;
								REAL diff = val - 1.0f;
								REAL sgn = (diff >= 0.0f) ? 1.0f : -1.0f;
								REAL mg = fabs(diff) + 1e-30f;
								val = 1.0f + sgn * native_powr(mg, 1.0f / (2.0f * fmax(pw, 0.01f)));
							}
							// Mirror
							if (fractal->transformCommon.multiplierMirror1 && val < 1.0f)
								val = 2.0f - val;
							// Quantize
							if (fractal->transformCommon.multiplierQuantize1 > 0)
							{
								REAL step = 1.0f / (REAL)fractal->transformCommon.multiplierQuantize1;
								val = 1.0f + floor((val - 1.0f) / step + 0.5f) * step;
							}
							// Symmetry Break
							if (fractal->transformCommon.multiplierSymmetryBreak1 != 0.0f)
							{
								REAL sb = fractal->transformCommon.multiplierSymmetryBreak1;
								REAL diff = val - 1.0f;
								val = (diff > 0.0f) ? 1.0f + diff * (1.0f + sb) : 1.0f + diff * (1.0f - sb);
							}
							// Clamp
							if (val < fractal->transformCommon.multiplierClampMin1) val = fractal->transformCommon.multiplierClampMin1;
							if (val > fractal->transformCommon.multiplierClampMax1) val = fractal->transformCommon.multiplierClampMax1;
							// Soft Clip
							if (fractal->transformCommon.multiplierSoftClip1 > 0.0f)
							{
								REAL sc = fractal->transformCommon.multiplierSoftClip1;
								REAL diff = val - 1.0f;
								val = 1.0f + diff / (1.0f + sc * fabs(diff));
							}
							// Radial Falloff
							if (fractal->transformCommon.multiplierRadialFalloff1 > 0.0f)
							{
								REAL rf = fractal->transformCommon.multiplierRadialFalloff1;
								REAL r = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0f + (val - 1.0f) * native_exp(-rf * r);
							}
							// Angular Bias
							if (fractal->transformCommon.multiplierAngularBias1 != 0.0f)
							{
								REAL ab = fractal->transformCommon.multiplierAngularBias1;
								REAL angle = atan2(z.y, z.x);
								REAL bias = 0.5f + 0.5f * native_cos(angle - ab * M_PI_F / 180.0f);
								val = 1.0f + (val - 1.0f) * bias;
							}
							// Polar Mode
							if (fractal->transformCommon.multiplierPolarMode1)
							{
								REAL r = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0f + (val - 1.0f) * (1.0f + 0.5f * native_sin(r));
							}
							// Cross-axis Coupling
							if (fractal->transformCommon.multiplierCrossCoupling1 > 0.0f)
							{
								REAL ccc = fractal->transformCommon.multiplierCrossCoupling1;
								REAL leak = (val - 1.0f) * ccc * 0.1f;
								z.x += leak * z.y;
								z.y += leak * z.z;
								z.z += leak * z.x;
							}
							// Noise addition
							if (fractal->transformCommon.multiplierNoiseSeed1 > 0)
							{
								int seed = fractal->transformCommon.multiplierNoiseSeed1;
								int oct = fractal->transformCommon.multiplierNoiseOctaves1;
								REAL nv = 0.0f;
								REAL amp = 1.0f;
								for (int o = 0; o < oct; o++)
								{
									REAL ph = (REAL)(aux->i * 1237 + seed * 7919 + o * 4621);
									nv += amp * native_sin(ph * 0.0031415f);
									amp *= 0.5f;
								}
								val += nv * fabs(val - 1.0f) * 0.3f;
							}
							// Blend Mode: 0=normal, 1=shrink-only, 2=grow-only, 3=abs, 4=smooth
							{
								int bm = fractal->transformCommon.multiplierBlendMode1;
								if (bm == 1 && val > 1.0f) val = 1.0f;
								else if (bm == 2 && val < 1.0f) val = 1.0f;
								else if (bm == 3) val = 1.0f + fabs(val - 1.0f);
								else if (bm == 4) { REAL sv = fmin(fmax((val - 0.5f), 0.0f), 1.0f); val = 0.5f + sv * sv * (3.0f - 2.0f * sv); }
							}

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
					case 1: z.x *= val; aux->DE *= fabs(val); break;
					case 2: z.y *= val; aux->DE *= fabs(val); break;
					case 3: z.z *= val; aux->DE *= fabs(val); break;
					case 4: aux->DE *= val; break;
					case 5: aux->color *= val; break;
					case 6: z.w *= val; aux->DE *= fabs(val); break;
					case 7: z.x *= val; z.y *= val; aux->DE *= fabs(val); break;
					case 8: z.x *= val; z.z *= val; aux->DE *= fabs(val); break;
					case 9: z.y *= val; z.z *= val; aux->DE *= fabs(val); break;
					case 10: aux->color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 2 ===
		if (fractal->transformCommon.multiplierEnabled2
				&& aux->i >= fractal->transformCommon.multiplierStartIter2
				&& aux->i < fractal->transformCommon.multiplierStopIter2)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode2;
			REAL threshR = length(z);
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold2)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold2))
			{
				REAL val = fractal->transformCommon.multiplierScale2;

				if (fractal->transformCommon.multiplierInverse2) val = (fabs(val) > 1e-15f) ? (1.0f / val) : 1e15f;

				int vmode = fractal->transformCommon.multiplierValueMode2;
				REAL range = (REAL)(fractal->transformCommon.multiplierStopIter2 - fractal->transformCommon.multiplierStartIter2);
				REAL ph = fractal->transformCommon.multiplierPhase2;
				if (range > 0 && vmode > 0)
				{
					REAL t = (REAL)(aux->i - fractal->transformCommon.multiplierStartIter2) / range;
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

							// Decay
							if (fractal->transformCommon.multiplierDecay2 > 0.0f)
							{
								REAL dcy = fractal->transformCommon.multiplierDecay2;
								REAL rng = (REAL)(fractal->transformCommon.multiplierStopIter2 - fractal->transformCommon.multiplierStartIter2);
								REAL td = (rng > 0.0f) ? (REAL)(aux->i - fractal->transformCommon.multiplierStartIter2) / rng : 0.0f;
								val = 1.0f + (val - 1.0f) * native_exp(-dcy * td * 5.0f);
							}
							// Exponent
							if (fractal->transformCommon.multiplierExponent2 != 1.0f)
							{
								REAL ep = fractal->transformCommon.multiplierExponent2;
								REAL sgn = (val >= 1.0f) ? 1.0f : -1.0f;
								val = 1.0f + sgn * native_powr(fabs(val - 1.0f) + 1e-30f, ep);
							}
							// Offset
							val += fractal->transformCommon.multiplierOffset2;

							// Delay
							if (fractal->transformCommon.multiplierDelay2 > 0
								&& aux->i < fractal->transformCommon.multiplierStartIter2 + fractal->transformCommon.multiplierDelay2)
								val = 1.0f;
							// Iteration Modulo
							if (fractal->transformCommon.multiplierIterModulo2 > 1
								&& ((aux->i - fractal->transformCommon.multiplierStartIter2) % fractal->transformCommon.multiplierIterModulo2) != 0)
								val = 1.0f;
							// Attack envelope
							if (fractal->transformCommon.multiplierAttack2 > 0.0f)
							{
								REAL rng = (REAL)(fractal->transformCommon.multiplierStopIter2 - fractal->transformCommon.multiplierStartIter2);
								REAL td = (rng > 0.0f) ? (REAL)(aux->i - fractal->transformCommon.multiplierStartIter2) / rng : 1.0f;
								REAL att = fractal->transformCommon.multiplierAttack2;
								if (td < att) val = 1.0f + (val - 1.0f) * (td / att);
							}
							// Release envelope
							if (fractal->transformCommon.multiplierRelease2 > 0.0f)
							{
								REAL rng = (REAL)(fractal->transformCommon.multiplierStopIter2 - fractal->transformCommon.multiplierStartIter2);
								REAL td = (rng > 0.0f) ? (REAL)(aux->i - fractal->transformCommon.multiplierStartIter2) / rng : 1.0f;
								REAL rel = fractal->transformCommon.multiplierRelease2;
								if (td > (1.0f - rel)) val = 1.0f + (val - 1.0f) * ((1.0f - td) / rel);
							}
							// Feedback
							if (fractal->transformCommon.multiplierFeedback2 > 0.0f)
							{
								REAL fb = fractal->transformCommon.multiplierFeedback2;
								val = 1.0f + (val - 1.0f) * (1.0f - fb) + (prevMultVal - 1.0f) * fb;
							}
							// Harmonics
							if (fractal->transformCommon.multiplierHarmonics2 > 0.0f)
							{
								REAL rng = (REAL)(fractal->transformCommon.multiplierStopIter2 - fractal->transformCommon.multiplierStartIter2);
								REAL td = (rng > 0.0f) ? (REAL)(aux->i - fractal->transformCommon.multiplierStartIter2) / rng : 0.0f;
								REAL hrm = fractal->transformCommon.multiplierHarmonics2;
								REAL frq = fractal->transformCommon.multiplierFrequency2;
								val += hrm * native_sin(4.0f * M_PI_F * frq * td) * fabs(val - 1.0f);
							}
							// Pulse Width
							if (fractal->transformCommon.multiplierPulseWidth2 != 0.5f)
							{
								REAL pw = fractal->transformCommon.multiplierPulseWidth2;
								REAL diff = val - 1.0f;
								REAL sgn = (diff >= 0.0f) ? 1.0f : -1.0f;
								REAL mg = fabs(diff) + 1e-30f;
								val = 1.0f + sgn * native_powr(mg, 1.0f / (2.0f * fmax(pw, 0.01f)));
							}
							// Mirror
							if (fractal->transformCommon.multiplierMirror2 && val < 1.0f)
								val = 2.0f - val;
							// Quantize
							if (fractal->transformCommon.multiplierQuantize2 > 0)
							{
								REAL step = 1.0f / (REAL)fractal->transformCommon.multiplierQuantize2;
								val = 1.0f + floor((val - 1.0f) / step + 0.5f) * step;
							}
							// Symmetry Break
							if (fractal->transformCommon.multiplierSymmetryBreak2 != 0.0f)
							{
								REAL sb = fractal->transformCommon.multiplierSymmetryBreak2;
								REAL diff = val - 1.0f;
								val = (diff > 0.0f) ? 1.0f + diff * (1.0f + sb) : 1.0f + diff * (1.0f - sb);
							}
							// Clamp
							if (val < fractal->transformCommon.multiplierClampMin2) val = fractal->transformCommon.multiplierClampMin2;
							if (val > fractal->transformCommon.multiplierClampMax2) val = fractal->transformCommon.multiplierClampMax2;
							// Soft Clip
							if (fractal->transformCommon.multiplierSoftClip2 > 0.0f)
							{
								REAL sc = fractal->transformCommon.multiplierSoftClip2;
								REAL diff = val - 1.0f;
								val = 1.0f + diff / (1.0f + sc * fabs(diff));
							}
							// Radial Falloff
							if (fractal->transformCommon.multiplierRadialFalloff2 > 0.0f)
							{
								REAL rf = fractal->transformCommon.multiplierRadialFalloff2;
								REAL r = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0f + (val - 1.0f) * native_exp(-rf * r);
							}
							// Angular Bias
							if (fractal->transformCommon.multiplierAngularBias2 != 0.0f)
							{
								REAL ab = fractal->transformCommon.multiplierAngularBias2;
								REAL angle = atan2(z.y, z.x);
								REAL bias = 0.5f + 0.5f * native_cos(angle - ab * M_PI_F / 180.0f);
								val = 1.0f + (val - 1.0f) * bias;
							}
							// Polar Mode
							if (fractal->transformCommon.multiplierPolarMode2)
							{
								REAL r = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0f + (val - 1.0f) * (1.0f + 0.5f * native_sin(r));
							}
							// Cross-axis Coupling
							if (fractal->transformCommon.multiplierCrossCoupling2 > 0.0f)
							{
								REAL ccc = fractal->transformCommon.multiplierCrossCoupling2;
								REAL leak = (val - 1.0f) * ccc * 0.1f;
								z.x += leak * z.y;
								z.y += leak * z.z;
								z.z += leak * z.x;
							}
							// Noise addition
							if (fractal->transformCommon.multiplierNoiseSeed2 > 0)
							{
								int seed = fractal->transformCommon.multiplierNoiseSeed2;
								int oct = fractal->transformCommon.multiplierNoiseOctaves2;
								REAL nv = 0.0f;
								REAL amp = 1.0f;
								for (int o = 0; o < oct; o++)
								{
									REAL ph = (REAL)(aux->i * 1237 + seed * 7919 + o * 4621);
									nv += amp * native_sin(ph * 0.0031415f);
									amp *= 0.5f;
								}
								val += nv * fabs(val - 1.0f) * 0.3f;
							}
							// Blend Mode: 0=normal, 1=shrink-only, 2=grow-only, 3=abs, 4=smooth
							{
								int bm = fractal->transformCommon.multiplierBlendMode2;
								if (bm == 1 && val > 1.0f) val = 1.0f;
								else if (bm == 2 && val < 1.0f) val = 1.0f;
								else if (bm == 3) val = 1.0f + fabs(val - 1.0f);
								else if (bm == 4) { REAL sv = fmin(fmax((val - 0.5f), 0.0f), 1.0f); val = 0.5f + sv * sv * (3.0f - 2.0f * sv); }
							}

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
					case 1: z.x *= val; aux->DE *= fabs(val); break;
					case 2: z.y *= val; aux->DE *= fabs(val); break;
					case 3: z.z *= val; aux->DE *= fabs(val); break;
					case 4: aux->DE *= val; break;
					case 5: aux->color *= val; break;
					case 6: z.w *= val; aux->DE *= fabs(val); break;
					case 7: z.x *= val; z.y *= val; aux->DE *= fabs(val); break;
					case 8: z.x *= val; z.z *= val; aux->DE *= fabs(val); break;
					case 9: z.y *= val; z.z *= val; aux->DE *= fabs(val); break;
					case 10: aux->color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 3 ===
		if (fractal->transformCommon.multiplierEnabled3
				&& aux->i >= fractal->transformCommon.multiplierStartIter3
				&& aux->i < fractal->transformCommon.multiplierStopIter3)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode3;
			REAL threshR = length(z);
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold3)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold3))
			{
				REAL val = fractal->transformCommon.multiplierScale3;

				if (fractal->transformCommon.multiplierInverse3) val = (fabs(val) > 1e-15f) ? (1.0f / val) : 1e15f;

				int vmode = fractal->transformCommon.multiplierValueMode3;
				REAL range = (REAL)(fractal->transformCommon.multiplierStopIter3 - fractal->transformCommon.multiplierStartIter3);
				REAL ph = fractal->transformCommon.multiplierPhase3;
				if (range > 0 && vmode > 0)
				{
					REAL t = (REAL)(aux->i - fractal->transformCommon.multiplierStartIter3) / range;
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

							// Decay
							if (fractal->transformCommon.multiplierDecay3 > 0.0f)
							{
								REAL dcy = fractal->transformCommon.multiplierDecay3;
								REAL rng = (REAL)(fractal->transformCommon.multiplierStopIter3 - fractal->transformCommon.multiplierStartIter3);
								REAL td = (rng > 0.0f) ? (REAL)(aux->i - fractal->transformCommon.multiplierStartIter3) / rng : 0.0f;
								val = 1.0f + (val - 1.0f) * native_exp(-dcy * td * 5.0f);
							}
							// Exponent
							if (fractal->transformCommon.multiplierExponent3 != 1.0f)
							{
								REAL ep = fractal->transformCommon.multiplierExponent3;
								REAL sgn = (val >= 1.0f) ? 1.0f : -1.0f;
								val = 1.0f + sgn * native_powr(fabs(val - 1.0f) + 1e-30f, ep);
							}
							// Offset
							val += fractal->transformCommon.multiplierOffset3;

							// Delay
							if (fractal->transformCommon.multiplierDelay3 > 0
								&& aux->i < fractal->transformCommon.multiplierStartIter3 + fractal->transformCommon.multiplierDelay3)
								val = 1.0f;
							// Iteration Modulo
							if (fractal->transformCommon.multiplierIterModulo3 > 1
								&& ((aux->i - fractal->transformCommon.multiplierStartIter3) % fractal->transformCommon.multiplierIterModulo3) != 0)
								val = 1.0f;
							// Attack envelope
							if (fractal->transformCommon.multiplierAttack3 > 0.0f)
							{
								REAL rng = (REAL)(fractal->transformCommon.multiplierStopIter3 - fractal->transformCommon.multiplierStartIter3);
								REAL td = (rng > 0.0f) ? (REAL)(aux->i - fractal->transformCommon.multiplierStartIter3) / rng : 1.0f;
								REAL att = fractal->transformCommon.multiplierAttack3;
								if (td < att) val = 1.0f + (val - 1.0f) * (td / att);
							}
							// Release envelope
							if (fractal->transformCommon.multiplierRelease3 > 0.0f)
							{
								REAL rng = (REAL)(fractal->transformCommon.multiplierStopIter3 - fractal->transformCommon.multiplierStartIter3);
								REAL td = (rng > 0.0f) ? (REAL)(aux->i - fractal->transformCommon.multiplierStartIter3) / rng : 1.0f;
								REAL rel = fractal->transformCommon.multiplierRelease3;
								if (td > (1.0f - rel)) val = 1.0f + (val - 1.0f) * ((1.0f - td) / rel);
							}
							// Feedback
							if (fractal->transformCommon.multiplierFeedback3 > 0.0f)
							{
								REAL fb = fractal->transformCommon.multiplierFeedback3;
								val = 1.0f + (val - 1.0f) * (1.0f - fb) + (prevMultVal - 1.0f) * fb;
							}
							// Harmonics
							if (fractal->transformCommon.multiplierHarmonics3 > 0.0f)
							{
								REAL rng = (REAL)(fractal->transformCommon.multiplierStopIter3 - fractal->transformCommon.multiplierStartIter3);
								REAL td = (rng > 0.0f) ? (REAL)(aux->i - fractal->transformCommon.multiplierStartIter3) / rng : 0.0f;
								REAL hrm = fractal->transformCommon.multiplierHarmonics3;
								REAL frq = fractal->transformCommon.multiplierFrequency3;
								val += hrm * native_sin(4.0f * M_PI_F * frq * td) * fabs(val - 1.0f);
							}
							// Pulse Width
							if (fractal->transformCommon.multiplierPulseWidth3 != 0.5f)
							{
								REAL pw = fractal->transformCommon.multiplierPulseWidth3;
								REAL diff = val - 1.0f;
								REAL sgn = (diff >= 0.0f) ? 1.0f : -1.0f;
								REAL mg = fabs(diff) + 1e-30f;
								val = 1.0f + sgn * native_powr(mg, 1.0f / (2.0f * fmax(pw, 0.01f)));
							}
							// Mirror
							if (fractal->transformCommon.multiplierMirror3 && val < 1.0f)
								val = 2.0f - val;
							// Quantize
							if (fractal->transformCommon.multiplierQuantize3 > 0)
							{
								REAL step = 1.0f / (REAL)fractal->transformCommon.multiplierQuantize3;
								val = 1.0f + floor((val - 1.0f) / step + 0.5f) * step;
							}
							// Symmetry Break
							if (fractal->transformCommon.multiplierSymmetryBreak3 != 0.0f)
							{
								REAL sb = fractal->transformCommon.multiplierSymmetryBreak3;
								REAL diff = val - 1.0f;
								val = (diff > 0.0f) ? 1.0f + diff * (1.0f + sb) : 1.0f + diff * (1.0f - sb);
							}
							// Clamp
							if (val < fractal->transformCommon.multiplierClampMin3) val = fractal->transformCommon.multiplierClampMin3;
							if (val > fractal->transformCommon.multiplierClampMax3) val = fractal->transformCommon.multiplierClampMax3;
							// Soft Clip
							if (fractal->transformCommon.multiplierSoftClip3 > 0.0f)
							{
								REAL sc = fractal->transformCommon.multiplierSoftClip3;
								REAL diff = val - 1.0f;
								val = 1.0f + diff / (1.0f + sc * fabs(diff));
							}
							// Radial Falloff
							if (fractal->transformCommon.multiplierRadialFalloff3 > 0.0f)
							{
								REAL rf = fractal->transformCommon.multiplierRadialFalloff3;
								REAL r = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0f + (val - 1.0f) * native_exp(-rf * r);
							}
							// Angular Bias
							if (fractal->transformCommon.multiplierAngularBias3 != 0.0f)
							{
								REAL ab = fractal->transformCommon.multiplierAngularBias3;
								REAL angle = atan2(z.y, z.x);
								REAL bias = 0.5f + 0.5f * native_cos(angle - ab * M_PI_F / 180.0f);
								val = 1.0f + (val - 1.0f) * bias;
							}
							// Polar Mode
							if (fractal->transformCommon.multiplierPolarMode3)
							{
								REAL r = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0f + (val - 1.0f) * (1.0f + 0.5f * native_sin(r));
							}
							// Cross-axis Coupling
							if (fractal->transformCommon.multiplierCrossCoupling3 > 0.0f)
							{
								REAL ccc = fractal->transformCommon.multiplierCrossCoupling3;
								REAL leak = (val - 1.0f) * ccc * 0.1f;
								z.x += leak * z.y;
								z.y += leak * z.z;
								z.z += leak * z.x;
							}
							// Noise addition
							if (fractal->transformCommon.multiplierNoiseSeed3 > 0)
							{
								int seed = fractal->transformCommon.multiplierNoiseSeed3;
								int oct = fractal->transformCommon.multiplierNoiseOctaves3;
								REAL nv = 0.0f;
								REAL amp = 1.0f;
								for (int o = 0; o < oct; o++)
								{
									REAL ph = (REAL)(aux->i * 1237 + seed * 7919 + o * 4621);
									nv += amp * native_sin(ph * 0.0031415f);
									amp *= 0.5f;
								}
								val += nv * fabs(val - 1.0f) * 0.3f;
							}
							// Blend Mode: 0=normal, 1=shrink-only, 2=grow-only, 3=abs, 4=smooth
							{
								int bm = fractal->transformCommon.multiplierBlendMode3;
								if (bm == 1 && val > 1.0f) val = 1.0f;
								else if (bm == 2 && val < 1.0f) val = 1.0f;
								else if (bm == 3) val = 1.0f + fabs(val - 1.0f);
								else if (bm == 4) { REAL sv = fmin(fmax((val - 0.5f), 0.0f), 1.0f); val = 0.5f + sv * sv * (3.0f - 2.0f * sv); }
							}

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
					case 1: z.x *= val; aux->DE *= fabs(val); break;
					case 2: z.y *= val; aux->DE *= fabs(val); break;
					case 3: z.z *= val; aux->DE *= fabs(val); break;
					case 4: aux->DE *= val; break;
					case 5: aux->color *= val; break;
					case 6: z.w *= val; aux->DE *= fabs(val); break;
					case 7: z.x *= val; z.y *= val; aux->DE *= fabs(val); break;
					case 8: z.x *= val; z.z *= val; aux->DE *= fabs(val); break;
					case 9: z.y *= val; z.z *= val; aux->DE *= fabs(val); break;
					case 10: aux->color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 4 ===
		if (fractal->transformCommon.multiplierEnabled4
				&& aux->i >= fractal->transformCommon.multiplierStartIter4
				&& aux->i < fractal->transformCommon.multiplierStopIter4)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode4;
			REAL threshR = length(z);
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold4)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold4))
			{
				REAL val = fractal->transformCommon.multiplierScale4;

				if (fractal->transformCommon.multiplierInverse4) val = (fabs(val) > 1e-15f) ? (1.0f / val) : 1e15f;

				int vmode = fractal->transformCommon.multiplierValueMode4;
				REAL range = (REAL)(fractal->transformCommon.multiplierStopIter4 - fractal->transformCommon.multiplierStartIter4);
				REAL ph = fractal->transformCommon.multiplierPhase4;
				if (range > 0 && vmode > 0)
				{
					REAL t = (REAL)(aux->i - fractal->transformCommon.multiplierStartIter4) / range;
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

							// Decay
							if (fractal->transformCommon.multiplierDecay4 > 0.0f)
							{
								REAL dcy = fractal->transformCommon.multiplierDecay4;
								REAL rng = (REAL)(fractal->transformCommon.multiplierStopIter4 - fractal->transformCommon.multiplierStartIter4);
								REAL td = (rng > 0.0f) ? (REAL)(aux->i - fractal->transformCommon.multiplierStartIter4) / rng : 0.0f;
								val = 1.0f + (val - 1.0f) * native_exp(-dcy * td * 5.0f);
							}
							// Exponent
							if (fractal->transformCommon.multiplierExponent4 != 1.0f)
							{
								REAL ep = fractal->transformCommon.multiplierExponent4;
								REAL sgn = (val >= 1.0f) ? 1.0f : -1.0f;
								val = 1.0f + sgn * native_powr(fabs(val - 1.0f) + 1e-30f, ep);
							}
							// Offset
							val += fractal->transformCommon.multiplierOffset4;

							// Delay
							if (fractal->transformCommon.multiplierDelay4 > 0
								&& aux->i < fractal->transformCommon.multiplierStartIter4 + fractal->transformCommon.multiplierDelay4)
								val = 1.0f;
							// Iteration Modulo
							if (fractal->transformCommon.multiplierIterModulo4 > 1
								&& ((aux->i - fractal->transformCommon.multiplierStartIter4) % fractal->transformCommon.multiplierIterModulo4) != 0)
								val = 1.0f;
							// Attack envelope
							if (fractal->transformCommon.multiplierAttack4 > 0.0f)
							{
								REAL rng = (REAL)(fractal->transformCommon.multiplierStopIter4 - fractal->transformCommon.multiplierStartIter4);
								REAL td = (rng > 0.0f) ? (REAL)(aux->i - fractal->transformCommon.multiplierStartIter4) / rng : 1.0f;
								REAL att = fractal->transformCommon.multiplierAttack4;
								if (td < att) val = 1.0f + (val - 1.0f) * (td / att);
							}
							// Release envelope
							if (fractal->transformCommon.multiplierRelease4 > 0.0f)
							{
								REAL rng = (REAL)(fractal->transformCommon.multiplierStopIter4 - fractal->transformCommon.multiplierStartIter4);
								REAL td = (rng > 0.0f) ? (REAL)(aux->i - fractal->transformCommon.multiplierStartIter4) / rng : 1.0f;
								REAL rel = fractal->transformCommon.multiplierRelease4;
								if (td > (1.0f - rel)) val = 1.0f + (val - 1.0f) * ((1.0f - td) / rel);
							}
							// Feedback
							if (fractal->transformCommon.multiplierFeedback4 > 0.0f)
							{
								REAL fb = fractal->transformCommon.multiplierFeedback4;
								val = 1.0f + (val - 1.0f) * (1.0f - fb) + (prevMultVal - 1.0f) * fb;
							}
							// Harmonics
							if (fractal->transformCommon.multiplierHarmonics4 > 0.0f)
							{
								REAL rng = (REAL)(fractal->transformCommon.multiplierStopIter4 - fractal->transformCommon.multiplierStartIter4);
								REAL td = (rng > 0.0f) ? (REAL)(aux->i - fractal->transformCommon.multiplierStartIter4) / rng : 0.0f;
								REAL hrm = fractal->transformCommon.multiplierHarmonics4;
								REAL frq = fractal->transformCommon.multiplierFrequency4;
								val += hrm * native_sin(4.0f * M_PI_F * frq * td) * fabs(val - 1.0f);
							}
							// Pulse Width
							if (fractal->transformCommon.multiplierPulseWidth4 != 0.5f)
							{
								REAL pw = fractal->transformCommon.multiplierPulseWidth4;
								REAL diff = val - 1.0f;
								REAL sgn = (diff >= 0.0f) ? 1.0f : -1.0f;
								REAL mg = fabs(diff) + 1e-30f;
								val = 1.0f + sgn * native_powr(mg, 1.0f / (2.0f * fmax(pw, 0.01f)));
							}
							// Mirror
							if (fractal->transformCommon.multiplierMirror4 && val < 1.0f)
								val = 2.0f - val;
							// Quantize
							if (fractal->transformCommon.multiplierQuantize4 > 0)
							{
								REAL step = 1.0f / (REAL)fractal->transformCommon.multiplierQuantize4;
								val = 1.0f + floor((val - 1.0f) / step + 0.5f) * step;
							}
							// Symmetry Break
							if (fractal->transformCommon.multiplierSymmetryBreak4 != 0.0f)
							{
								REAL sb = fractal->transformCommon.multiplierSymmetryBreak4;
								REAL diff = val - 1.0f;
								val = (diff > 0.0f) ? 1.0f + diff * (1.0f + sb) : 1.0f + diff * (1.0f - sb);
							}
							// Clamp
							if (val < fractal->transformCommon.multiplierClampMin4) val = fractal->transformCommon.multiplierClampMin4;
							if (val > fractal->transformCommon.multiplierClampMax4) val = fractal->transformCommon.multiplierClampMax4;
							// Soft Clip
							if (fractal->transformCommon.multiplierSoftClip4 > 0.0f)
							{
								REAL sc = fractal->transformCommon.multiplierSoftClip4;
								REAL diff = val - 1.0f;
								val = 1.0f + diff / (1.0f + sc * fabs(diff));
							}
							// Radial Falloff
							if (fractal->transformCommon.multiplierRadialFalloff4 > 0.0f)
							{
								REAL rf = fractal->transformCommon.multiplierRadialFalloff4;
								REAL r = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0f + (val - 1.0f) * native_exp(-rf * r);
							}
							// Angular Bias
							if (fractal->transformCommon.multiplierAngularBias4 != 0.0f)
							{
								REAL ab = fractal->transformCommon.multiplierAngularBias4;
								REAL angle = atan2(z.y, z.x);
								REAL bias = 0.5f + 0.5f * native_cos(angle - ab * M_PI_F / 180.0f);
								val = 1.0f + (val - 1.0f) * bias;
							}
							// Polar Mode
							if (fractal->transformCommon.multiplierPolarMode4)
							{
								REAL r = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0f + (val - 1.0f) * (1.0f + 0.5f * native_sin(r));
							}
							// Cross-axis Coupling
							if (fractal->transformCommon.multiplierCrossCoupling4 > 0.0f)
							{
								REAL ccc = fractal->transformCommon.multiplierCrossCoupling4;
								REAL leak = (val - 1.0f) * ccc * 0.1f;
								z.x += leak * z.y;
								z.y += leak * z.z;
								z.z += leak * z.x;
							}
							// Noise addition
							if (fractal->transformCommon.multiplierNoiseSeed4 > 0)
							{
								int seed = fractal->transformCommon.multiplierNoiseSeed4;
								int oct = fractal->transformCommon.multiplierNoiseOctaves4;
								REAL nv = 0.0f;
								REAL amp = 1.0f;
								for (int o = 0; o < oct; o++)
								{
									REAL ph = (REAL)(aux->i * 1237 + seed * 7919 + o * 4621);
									nv += amp * native_sin(ph * 0.0031415f);
									amp *= 0.5f;
								}
								val += nv * fabs(val - 1.0f) * 0.3f;
							}
							// Blend Mode: 0=normal, 1=shrink-only, 2=grow-only, 3=abs, 4=smooth
							{
								int bm = fractal->transformCommon.multiplierBlendMode4;
								if (bm == 1 && val > 1.0f) val = 1.0f;
								else if (bm == 2 && val < 1.0f) val = 1.0f;
								else if (bm == 3) val = 1.0f + fabs(val - 1.0f);
								else if (bm == 4) { REAL sv = fmin(fmax((val - 0.5f), 0.0f), 1.0f); val = 0.5f + sv * sv * (3.0f - 2.0f * sv); }
							}

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
					case 1: z.x *= val; aux->DE *= fabs(val); break;
					case 2: z.y *= val; aux->DE *= fabs(val); break;
					case 3: z.z *= val; aux->DE *= fabs(val); break;
					case 4: aux->DE *= val; break;
					case 5: aux->color *= val; break;
					case 6: z.w *= val; aux->DE *= fabs(val); break;
					case 7: z.x *= val; z.y *= val; aux->DE *= fabs(val); break;
					case 8: z.x *= val; z.z *= val; aux->DE *= fabs(val); break;
					case 9: z.y *= val; z.z *= val; aux->DE *= fabs(val); break;
					case 10: aux->color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 5 ===
		if (fractal->transformCommon.multiplierEnabled5
				&& aux->i >= fractal->transformCommon.multiplierStartIter5
				&& aux->i < fractal->transformCommon.multiplierStopIter5)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode5;
			REAL threshR = length(z);
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold5)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold5))
			{
				REAL val = fractal->transformCommon.multiplierScale5;

				if (fractal->transformCommon.multiplierInverse5) val = (fabs(val) > 1e-15f) ? (1.0f / val) : 1e15f;

				int vmode = fractal->transformCommon.multiplierValueMode5;
				REAL range = (REAL)(fractal->transformCommon.multiplierStopIter5 - fractal->transformCommon.multiplierStartIter5);
				REAL ph = fractal->transformCommon.multiplierPhase5;
				if (range > 0 && vmode > 0)
				{
					REAL t = (REAL)(aux->i - fractal->transformCommon.multiplierStartIter5) / range;
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

							// Decay
							if (fractal->transformCommon.multiplierDecay5 > 0.0f)
							{
								REAL dcy = fractal->transformCommon.multiplierDecay5;
								REAL rng = (REAL)(fractal->transformCommon.multiplierStopIter5 - fractal->transformCommon.multiplierStartIter5);
								REAL td = (rng > 0.0f) ? (REAL)(aux->i - fractal->transformCommon.multiplierStartIter5) / rng : 0.0f;
								val = 1.0f + (val - 1.0f) * native_exp(-dcy * td * 5.0f);
							}
							// Exponent
							if (fractal->transformCommon.multiplierExponent5 != 1.0f)
							{
								REAL ep = fractal->transformCommon.multiplierExponent5;
								REAL sgn = (val >= 1.0f) ? 1.0f : -1.0f;
								val = 1.0f + sgn * native_powr(fabs(val - 1.0f) + 1e-30f, ep);
							}
							// Offset
							val += fractal->transformCommon.multiplierOffset5;

							// Delay
							if (fractal->transformCommon.multiplierDelay5 > 0
								&& aux->i < fractal->transformCommon.multiplierStartIter5 + fractal->transformCommon.multiplierDelay5)
								val = 1.0f;
							// Iteration Modulo
							if (fractal->transformCommon.multiplierIterModulo5 > 1
								&& ((aux->i - fractal->transformCommon.multiplierStartIter5) % fractal->transformCommon.multiplierIterModulo5) != 0)
								val = 1.0f;
							// Attack envelope
							if (fractal->transformCommon.multiplierAttack5 > 0.0f)
							{
								REAL rng = (REAL)(fractal->transformCommon.multiplierStopIter5 - fractal->transformCommon.multiplierStartIter5);
								REAL td = (rng > 0.0f) ? (REAL)(aux->i - fractal->transformCommon.multiplierStartIter5) / rng : 1.0f;
								REAL att = fractal->transformCommon.multiplierAttack5;
								if (td < att) val = 1.0f + (val - 1.0f) * (td / att);
							}
							// Release envelope
							if (fractal->transformCommon.multiplierRelease5 > 0.0f)
							{
								REAL rng = (REAL)(fractal->transformCommon.multiplierStopIter5 - fractal->transformCommon.multiplierStartIter5);
								REAL td = (rng > 0.0f) ? (REAL)(aux->i - fractal->transformCommon.multiplierStartIter5) / rng : 1.0f;
								REAL rel = fractal->transformCommon.multiplierRelease5;
								if (td > (1.0f - rel)) val = 1.0f + (val - 1.0f) * ((1.0f - td) / rel);
							}
							// Feedback
							if (fractal->transformCommon.multiplierFeedback5 > 0.0f)
							{
								REAL fb = fractal->transformCommon.multiplierFeedback5;
								val = 1.0f + (val - 1.0f) * (1.0f - fb) + (prevMultVal - 1.0f) * fb;
							}
							// Harmonics
							if (fractal->transformCommon.multiplierHarmonics5 > 0.0f)
							{
								REAL rng = (REAL)(fractal->transformCommon.multiplierStopIter5 - fractal->transformCommon.multiplierStartIter5);
								REAL td = (rng > 0.0f) ? (REAL)(aux->i - fractal->transformCommon.multiplierStartIter5) / rng : 0.0f;
								REAL hrm = fractal->transformCommon.multiplierHarmonics5;
								REAL frq = fractal->transformCommon.multiplierFrequency5;
								val += hrm * native_sin(4.0f * M_PI_F * frq * td) * fabs(val - 1.0f);
							}
							// Pulse Width
							if (fractal->transformCommon.multiplierPulseWidth5 != 0.5f)
							{
								REAL pw = fractal->transformCommon.multiplierPulseWidth5;
								REAL diff = val - 1.0f;
								REAL sgn = (diff >= 0.0f) ? 1.0f : -1.0f;
								REAL mg = fabs(diff) + 1e-30f;
								val = 1.0f + sgn * native_powr(mg, 1.0f / (2.0f * fmax(pw, 0.01f)));
							}
							// Mirror
							if (fractal->transformCommon.multiplierMirror5 && val < 1.0f)
								val = 2.0f - val;
							// Quantize
							if (fractal->transformCommon.multiplierQuantize5 > 0)
							{
								REAL step = 1.0f / (REAL)fractal->transformCommon.multiplierQuantize5;
								val = 1.0f + floor((val - 1.0f) / step + 0.5f) * step;
							}
							// Symmetry Break
							if (fractal->transformCommon.multiplierSymmetryBreak5 != 0.0f)
							{
								REAL sb = fractal->transformCommon.multiplierSymmetryBreak5;
								REAL diff = val - 1.0f;
								val = (diff > 0.0f) ? 1.0f + diff * (1.0f + sb) : 1.0f + diff * (1.0f - sb);
							}
							// Clamp
							if (val < fractal->transformCommon.multiplierClampMin5) val = fractal->transformCommon.multiplierClampMin5;
							if (val > fractal->transformCommon.multiplierClampMax5) val = fractal->transformCommon.multiplierClampMax5;
							// Soft Clip
							if (fractal->transformCommon.multiplierSoftClip5 > 0.0f)
							{
								REAL sc = fractal->transformCommon.multiplierSoftClip5;
								REAL diff = val - 1.0f;
								val = 1.0f + diff / (1.0f + sc * fabs(diff));
							}
							// Radial Falloff
							if (fractal->transformCommon.multiplierRadialFalloff5 > 0.0f)
							{
								REAL rf = fractal->transformCommon.multiplierRadialFalloff5;
								REAL r = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0f + (val - 1.0f) * native_exp(-rf * r);
							}
							// Angular Bias
							if (fractal->transformCommon.multiplierAngularBias5 != 0.0f)
							{
								REAL ab = fractal->transformCommon.multiplierAngularBias5;
								REAL angle = atan2(z.y, z.x);
								REAL bias = 0.5f + 0.5f * native_cos(angle - ab * M_PI_F / 180.0f);
								val = 1.0f + (val - 1.0f) * bias;
							}
							// Polar Mode
							if (fractal->transformCommon.multiplierPolarMode5)
							{
								REAL r = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0f + (val - 1.0f) * (1.0f + 0.5f * native_sin(r));
							}
							// Cross-axis Coupling
							if (fractal->transformCommon.multiplierCrossCoupling5 > 0.0f)
							{
								REAL ccc = fractal->transformCommon.multiplierCrossCoupling5;
								REAL leak = (val - 1.0f) * ccc * 0.1f;
								z.x += leak * z.y;
								z.y += leak * z.z;
								z.z += leak * z.x;
							}
							// Noise addition
							if (fractal->transformCommon.multiplierNoiseSeed5 > 0)
							{
								int seed = fractal->transformCommon.multiplierNoiseSeed5;
								int oct = fractal->transformCommon.multiplierNoiseOctaves5;
								REAL nv = 0.0f;
								REAL amp = 1.0f;
								for (int o = 0; o < oct; o++)
								{
									REAL ph = (REAL)(aux->i * 1237 + seed * 7919 + o * 4621);
									nv += amp * native_sin(ph * 0.0031415f);
									amp *= 0.5f;
								}
								val += nv * fabs(val - 1.0f) * 0.3f;
							}
							// Blend Mode: 0=normal, 1=shrink-only, 2=grow-only, 3=abs, 4=smooth
							{
								int bm = fractal->transformCommon.multiplierBlendMode5;
								if (bm == 1 && val > 1.0f) val = 1.0f;
								else if (bm == 2 && val < 1.0f) val = 1.0f;
								else if (bm == 3) val = 1.0f + fabs(val - 1.0f);
								else if (bm == 4) { REAL sv = fmin(fmax((val - 0.5f), 0.0f), 1.0f); val = 0.5f + sv * sv * (3.0f - 2.0f * sv); }
							}

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
					case 1: z.x *= val; aux->DE *= fabs(val); break;
					case 2: z.y *= val; aux->DE *= fabs(val); break;
					case 3: z.z *= val; aux->DE *= fabs(val); break;
					case 4: aux->DE *= val; break;
					case 5: aux->color *= val; break;
					case 6: z.w *= val; aux->DE *= fabs(val); break;
					case 7: z.x *= val; z.y *= val; aux->DE *= fabs(val); break;
					case 8: z.x *= val; z.z *= val; aux->DE *= fabs(val); break;
					case 9: z.y *= val; z.z *= val; aux->DE *= fabs(val); break;
					case 10: aux->color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}
	}

	return z;
}
