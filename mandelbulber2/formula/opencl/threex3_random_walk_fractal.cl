/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Willekeurige wandeling fractaal.
 */

REAL4 Threex3RandomWalkFractalIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Random Walk Fractal: z_{n+1} = z_n + random_step() met random_step() uniform of Gaussisch
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	// Stochastic: deterministic chaos via tent map coupling
	REAL s = fractal->transformCommon.scale1;
	if (s < 0.01) s = 1.5;
	REAL tent_x = s * (1.0 - 2.0 * fabs(fmod(z.x, 1.0) - 0.5));
	REAL tent_y = s * (1.0 - 2.0 * fabs(fmod(z.y, 1.0) - 0.5));
	REAL th = asin(z.z / r) * power;
	REAL ph = atan2(z.y + tent_y * 0.01, z.x + tent_x * 0.01) * power;
	REAL rp = pow(r, power);
	aux->DE = power * pow(r, power - 1.0) * aux->DE + 1.0;
	z.x = cos(th) * cos(ph) * rp;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;

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
						REAL denom = native_powr(2.718281828f, freq) - 1.0f;
															val = 1.0f + (val - 1.0f) * (fabs(denom) > 1e-12f
																? (native_powr(2.718281828f, t * freq) - 1.0f) / denom
																: t);
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
						int seed = aux->i * 73856093 + (fractal->transformCommon.multiplierNoiseSeed1 > 0 ? fractal->transformCommon.multiplierNoiseSeed1 : 1) * 19349663;
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
								else if (vmode == 10)
								{
									REAL k1ls = fmax(fractal->transformCommon.multiplierExponent1, 0.1f) * 10.0f;
									REAL sv1 = 1.0f / (1.0f + native_exp(-k1ls * (t - 0.5f)));
									val = 1.0f + (sv1 - 0.5f) * 2.0f * (val - 1.0f);
								}
								else if (vmode == 11)
								{
									REAL chirpR1 = freq * 0.1f;
									val = 1.0f + native_sin(2.0f * M_PI_F * (freq + chirpR1 * t) * t + ph) * (val - 1.0f);
								}
								else if (vmode == 12)
								{
									REAL rt1v = fmod(t * freq + ph, 1.0f);
									if (rt1v < 0.0f) rt1v += 1.0f;
									val = 1.0f + (1.0f - rt1v) * (val - 1.0f);
								}
								else if (vmode == 13)
								{
									REAL lx1v = 1.0f, ly1v = 1.0f, lz1v = 1.0f;
									lx1v += (REAL)((fractal->transformCommon.multiplierNoiseSeed1 + 1) % 100) * 0.01f;
									for (int li1 = 0; li1 < (int)(t * 100.0f) + 1; li1++)
									{
										REAL dx1v = 10.0f * (ly1v - lx1v) * 0.01f;
										REAL dy1v = (lx1v * (28.0f - lz1v) - ly1v) * 0.01f;
										REAL dz1v = (lx1v * ly1v - 2.6667f * lz1v) * 0.01f;
										lx1v += dx1v; ly1v += dy1v; lz1v += dz1v;
									}
									val = 1.0f + fmod(fabs(lx1v), 1.0f) * (val - 1.0f);
								}
								else if (vmode == 14)
								{
									REAL bt1v = fmod(t * freq + ph, 1.0f);
									if (bt1v < 0.0f) bt1v += 1.0f;
									REAL tri1v = fabs(2.0f * bt1v - 1.0f);
									val = 1.0f + (1.0f - tri1v * tri1v) * (val - 1.0f);
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

							// Clip Drive (pre-gain)
							if (fractal->transformCommon.multiplierClipDrive1 != 1.0f)
							{
								REAL drv = fractal->transformCommon.multiplierClipDrive1;
								val = 1.0f + (val - 1.0f) * drv;
							}
							// Clip Rectify: 0=off, 1=half(clamp neg to 0), 2=full(abs)
							{
								int cr = fractal->transformCommon.multiplierClipRectify1;
								if (cr == 1 && val < 1.0f) val = 1.0f;
								else if (cr == 2) val = 1.0f + fabs(val - 1.0f);
							}
							// Clip Fold (wavefolder)
							if (fractal->transformCommon.multiplierClipFold1)
							{
								int folds = fractal->transformCommon.multiplierClipFoldCount1;
								if (folds < 1) folds = 1;
								REAL ceil = fractal->transformCommon.multiplierClipCeiling1;
								REAL flr = fractal->transformCommon.multiplierClipFloor1;
								for (int fi = 0; fi < folds; fi++)
								{
									if (val > ceil) val = 2.0f * ceil - val;
									if (val < flr) val = 2.0f * flr - val;
								}
							}
							// Clip Ceiling / Floor (hard clamp with asymmetry)
							if (!fractal->transformCommon.multiplierClipFold1)
							{
								REAL ceil = fractal->transformCommon.multiplierClipCeiling1;
								REAL flr = fractal->transformCommon.multiplierClipFloor1;
								REAL asym = fractal->transformCommon.multiplierClipAsymmetry1;
								ceil += asym;
								flr -= asym;
								REAL curve = fractal->transformCommon.multiplierClipCurve1;
								REAL knee = fractal->transformCommon.multiplierClipKnee1;
								if (curve > 0.0f || knee > 0.0f)
								{
									REAL k = fmax(knee, 0.001f);
									if (val > ceil - k)
									{
										REAL x = (val - (ceil - k)) / (2.0f * k);
										x = fmin(fmax(x, 0.0f), 1.0f);
										REAL sm = x * x * (3.0f - 2.0f * x);
										val = (ceil - k) + k * sm * (1.0f + curve);
										if (val > ceil) val = ceil;
									}
									if (val < flr + k)
									{
										REAL x = ((flr + k) - val) / (2.0f * k);
										x = fmin(fmax(x, 0.0f), 1.0f);
										REAL sm = x * x * (3.0f - 2.0f * x);
										val = (flr + k) - k * sm * (1.0f + curve);
										if (val < flr) val = flr;
									}
								}
								else
								{
									if (val > ceil) val = ceil;
									if (val < flr) val = flr;
								}
							}
							// Clip Mix (blend clipped/unclipped)
							if (fractal->transformCommon.multiplierClipMix1 < 1.0f)
							{
								REAL mx = fractal->transformCommon.multiplierClipMix1;
								val = 1.0f + mx * (val - 1.0f);
							}

							// === Inverse Processing ===
							{
								int doInverse = fractal->transformCommon.multiplierInverse1;
								if (fractal->transformCommon.multiplierInvOscillate1)
									doInverse = (aux->i % 2 == 0) ? doInverse : !doInverse;
								if (doInverse)
								{
									REAL origVal = val;
									REAL diff = val - 1.0f;
									REAL absDiff = fabs(diff);
									REAL rMin = fractal->transformCommon.multiplierInvRangeMin1;
									REAL rMax = fractal->transformCommon.multiplierInvRangeMax1;
									if (absDiff >= rMin && absDiff <= rMax)
									{
										REAL thr = fractal->transformCommon.multiplierInvThreshold1;
										if (absDiff >= thr)
										{
											REAL bias = fractal->transformCommon.multiplierInvBias1;
											REAL center = 1.0f + bias;
											int imode = fractal->transformCommon.multiplierInvMode1;
											if (imode == 0)
												val = center + (fabs(val - center) > 1e-15f ? (1.0f / (val - center)) : 1e15f);
											else if (imode == 1)
												val = center - (val - center);
											else if (imode == 2)
												val = center + (1.0f - fabs(val - center));
											else if (imode == 3)
												val = center - fabs(val - center) * ((val > center) ? 1.0f : -1.0f);
											REAL sm = fractal->transformCommon.multiplierInvSmooth1;
											if (sm > 0.0f)
											{
												REAL blend = fmin(absDiff / (thr + sm + 1e-15f), 1.0f);
												blend = blend * blend * (3.0f - 2.0f * blend);
												val = origVal + blend * (val - origVal);
											}
											REAL idcy = fractal->transformCommon.multiplierInvDecay1;
											if (idcy > 0.0f)
											{
												REAL rng = (REAL)(fractal->transformCommon.multiplierStopIter1 - fractal->transformCommon.multiplierStartIter1);
												REAL td = (rng > 0.0f) ? (REAL)(aux->i - fractal->transformCommon.multiplierStartIter1) / rng : 0.0f;
												REAL fade = native_exp(-idcy * td * 5.0f);
												val = origVal + fade * (val - origVal);
											}
											REAL str = fractal->transformCommon.multiplierInvStrength1;
											if (str < 1.0f)
												val = origVal + str * (val - origVal);
										}
									}
								}
							}

				
							// Burst / Falloff / Wrap / Conditional for slot 1
							int burstLen1 = fractal->transformCommon.multiplierBurstLength1;
							int burstGap1 = fractal->transformCommon.multiplierBurstGap1;
							if (burstLen1 > 0 && burstGap1 > 0)
							{
								int cycle1 = burstLen1 + burstGap1;
								int phase1 = (aux->i - fractal->transformCommon.multiplierStartIter1) % cycle1;
								if (phase1 >= burstLen1) val = 1.0f;
							}
							REAL sphFall1 = fractal->transformCommon.multiplierSphericalFalloff1;
							if (sphFall1 > 0.0f)
							{
								REAL dist1 = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								REAL falloff1 = native_exp(-sphFall1 * dist1);
								val = 1.0f + (val - 1.0f) * falloff1;
							}
							REAL wrapR1 = fractal->transformCommon.multiplierWrapRange1;
							if (wrapR1 > 0.0f)
							{
								REAL shifted1 = val - 1.0f;
								shifted1 = fmod(shifted1, wrapR1);
								if (shifted1 < 0.0f) shifted1 += wrapR1;
								val = 1.0f + shifted1;
							}
							int condMode1 = fractal->transformCommon.multiplierConditionalMode1;
							if (condMode1 == 1 && z.x < 0.0f) val = 1.0f;
							else if (condMode1 == 2 && z.x >= 0.0f) val = 1.0f;
							else if (condMode1 == 3)
							{
								REAL condDist1 = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								if (condDist1 < fractal->transformCommon.multiplierConditionalThreshold1) val = 1.0f;
							}

														// Accumulate for slot 1
							if (fractal->transformCommon.multiplierAccumulate1 && prevMultVal != 1.0f)
								val = 1.0f + (val - 1.0f) + (prevMultVal - 1.0f);

							
							// === Top-10 params for slot 1 ===
							if (fractal->transformCommon.multiplierSlotDisable1) { val = 1.0f; }
							else {
							REAL cullDist1 = fractal->transformCommon.multiplierDistCull1;
							if (cullDist1 > 0.0f && (z.x * z.x + z.y * z.y + z.z * z.z) > cullDist1 * cullDist1)
								val = 1.0f;
							else {

							int rampIn1 = fractal->transformCommon.multiplierRampIn1;
							if (rampIn1 > 0)
							{
								int elapsed1 = aux->i - fractal->transformCommon.multiplierStartIter1;
								if (elapsed1 < rampIn1)
								{
									REAL t1 = (REAL)elapsed1 / (REAL)rampIn1;
									t1 = t1 * t1 * (3.0f - 2.0f * t1);
									val = 1.0f + (val - 1.0f) * t1;
								}
							}
							int rampOut1 = fractal->transformCommon.multiplierRampOut1;
							if (rampOut1 > 0)
							{
								int remaining1 = fractal->transformCommon.multiplierStopIter1 - aux->i;
								if (remaining1 < rampOut1 && remaining1 >= 0)
								{
									REAL t1 = (REAL)remaining1 / (REAL)rampOut1;
									t1 = t1 * t1 * (3.0f - 2.0f * t1);
									val = 1.0f + (val - 1.0f) * t1;
								}
							}
							REAL cylBias1 = fractal->transformCommon.multiplierCylindricalBias1;
							if (cylBias1 > 0.0f)
							{
								REAL cylDist1 = native_sqrt(z.x * z.x + z.y * z.y);
								REAL cylFade1 = native_exp(-cylBias1 * cylDist1);
								val = 1.0f + (val - 1.0f) * cylFade1;
							}
							REAL softExp1 = fractal->transformCommon.multiplierSoftExp1;
							if (softExp1 > 0.0f && val < 1.0f)
							{
								REAL v1 = val - 1.0f;
								val = 1.0f + softExp1 * (native_exp(v1 / fmax(softExp1, 1e-12f)) - 1.0f);
							}
							REAL slewRate1 = fractal->transformCommon.multiplierSlewRate1;
							if (slewRate1 > 0.0f && prevMultVal != 1.0f)
							{
								REAL delta1 = val - prevMultVal;
								if (fabs(delta1) > slewRate1)
									val = prevMultVal + (delta1 > 0.0f ? slewRate1 : -slewRate1);
							}
							REAL hyst1 = fractal->transformCommon.multiplierHysteresis1;
							if (hyst1 > 0.0f)
							{
								REAL hystDist1 = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								REAL hystThresh1 = fractal->transformCommon.multiplierThreshold1;
								if (hystDist1 > hystThresh1 - hyst1 * 0.5f && hystDist1 < hystThresh1 + hyst1 * 0.5f)
								{
									REAL blend1 = (hystDist1 - (hystThresh1 - hyst1 * 0.5f)) / hyst1;
									val = 1.0f + (val - 1.0f) * blend1;
								}
							}
							REAL aaStep1 = fractal->transformCommon.multiplierAntiAlias1;
							if (aaStep1 > 0.0f)
							{
								REAL aaDist1 = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								REAL aaThresh1 = fractal->transformCommon.multiplierThreshold1;
								REAL aaT1 = (aaDist1 - (aaThresh1 - aaStep1)) / (2.0f * aaStep1);
								aaT1 = fmax(0.0f, fmin(1.0f, aaT1));
								aaT1 = aaT1 * aaT1 * (3.0f - 2.0f * aaT1);
								val = 1.0f + (val - 1.0f) * aaT1;
							}
							REAL neutralEps1 = fractal->transformCommon.multiplierNeutralEps1;
							if (neutralEps1 > 0.0f && fabs(val - 1.0f) < neutralEps1)
								val = 1.0f;

							} // end else distCull
							} // end else slotDisable

							
							REAL gradDir1 = fractal->transformCommon.multiplierGradientDir1;
							if (gradDir1 != 0.0f)
							{
								REAL r1g = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								if (r1g > 1e-12f)
								{
									REAL cosW1 = (z.x * native_cos(gradDir1) + z.y * native_sin(gradDir1)) / r1g;
									REAL blend1 = (cosW1 + 1.0f) * 0.5f;
									val = 1.0f + (val - 1.0f) * blend1;
								}
							}
							REAL voroScale1 = fractal->transformCommon.multiplierVoronoiScale1;
							if (voroScale1 > 0.0f)
							{
								REAL vx1 = z.x * voroScale1;
								REAL vy1 = z.y * voroScale1;
								REAL vz1 = z.z * voroScale1;
								REAL fx1 = vx1 - floor(vx1) - 0.5f;
								REAL fy1 = vy1 - floor(vy1) - 0.5f;
								REAL fz1 = vz1 - floor(vz1) - 0.5f;
								REAL vDist1 = native_sqrt(fx1 * fx1 + fy1 * fy1 + fz1 * fz1);
								val = 1.0f + (val - 1.0f) * fmin(vDist1 * 2.0f, 1.0f);
							}
							REAL torusR1 = fractal->transformCommon.multiplierToroidalR1;
							if (torusR1 > 0.0f)
							{
								REAL xyR1 = native_sqrt(z.x * z.x + z.y * z.y);
								REAL tDist1 = native_sqrt((xyR1 - torusR1) * (xyR1 - torusR1) + z.z * z.z);
								REAL tFade1 = native_exp(-tDist1);
								val = 1.0f + (val - 1.0f) * tFade1;
							}
							int angStripes1 = fractal->transformCommon.multiplierAngularStripes1;
							if (angStripes1 > 0)
							{
								REAL angle1 = atan2(z.y, z.x);
								int sector1 = (int)floor((angle1 + M_PI_F) / (2.0f * M_PI_F) * (REAL)angStripes1);
								if (sector1 % 2 != 0) val = 1.0f;
							}
							REAL geoP1 = fractal->transformCommon.multiplierGeoProgression1;
							if (geoP1 != 1.0f)
							{
								int elapsed1g = aux->i - fractal->transformCommon.multiplierStartIter1;
								if (elapsed1g > 0)
									val = 1.0f + (val - 1.0f) * native_powr(geoP1, (REAL)elapsed1g);
							}
							int parity1 = fractal->transformCommon.multiplierParityGate1;
							if (parity1 == 1 && aux->i % 2 == 0) val = 1.0f;
							if (parity1 == 2 && aux->i % 2 != 0) val = 1.0f;
							if (fractal->transformCommon.multiplierFibonacciStep1)
							{
								bool isFib1 = false;
								int fa1 = 0, fb1 = 1;
								while (fb1 <= aux->i) { int fc1 = fa1 + fb1; fa1 = fb1; fb1 = fc1; if (fb1 == aux->i) isFib1 = true; }
								if (aux->i == 0 || aux->i == 1) isFib1 = true;
								if (!isFib1) val = 1.0f;
							}

							
							int icurve1 = fractal->transformCommon.multiplierInterpCurve1;
							if (icurve1 > 0 && val != 1.0f)
							{
								REAL dev1 = val - 1.0f;
								REAL tn1 = fabs(dev1);
								if (tn1 > 1.0f) tn1 = 1.0f;
								if (icurve1 == 1) tn1 = tn1 * tn1 * tn1;
								else if (icurve1 == 2) tn1 = tn1 * tn1 * (3.0f - 2.0f * tn1);
								else if (icurve1 == 3) tn1 = (1.0f - native_cos(tn1 * M_PI_F)) * 0.5f;
								val = 1.0f + (dev1 > 0 ? tn1 : -tn1);
							}
							REAL dq1 = fractal->transformCommon.multiplierDitherQuantize1;
							if (dq1 > 0.0f)
							{
								int dqseed1 = aux->i * 48271 + 1 * 16807;
								dqseed1 = (dqseed1 ^ (dqseed1 >> 15)) * 1103515245;
								REAL dither1 = ((REAL)(dqseed1 & 0xFFFF) / 65535.0f - 0.5f) * dq1;
								val = floor((val + dither1) / dq1 + 0.5f) * dq1;
							}
							if (fractal->transformCommon.multiplierComplexMag1)
							{
								REAL cmag1 = native_sqrt(z.x * z.x + z.y * z.y);
								if (cmag1 > 1e-12f) val = 1.0f + (val - 1.0f) * cmag1;
							}
							REAL pidx1 = fractal->transformCommon.multiplierPaletteIdxDrive1;
							if (pidx1 > 0.0f)
							{
								aux->color += (val - 1.0f) * pidx1 * 256.0f;
							}
							int tLayers1 = fractal->transformCommon.multiplierTurbulenceLayers1;
							if (tLayers1 > 1 && val != 1.0f)
							{
								REAL turbSum1 = val - 1.0f;
								REAL amp1 = 0.5f;
								for (int tl1 = 1; tl1 < tLayers1; tl1++)
								{
									int tseed1 = aux->i * 73856093 + tl1 * 19349663 + 1 * 83492791;
									tseed1 = (tseed1 ^ (tseed1 >> 13)) * 1274126177;
									tseed1 = tseed1 ^ (tseed1 >> 16);
									REAL tnoise1 = (REAL)(tseed1 & 0xFFFF) / 65535.0f - 0.5f;
									turbSum1 += tnoise1 * amp1 * (val - 1.0f);
									amp1 *= 0.5f;
								}
								val = 1.0f + turbSum1;
							}
							REAL kalAngle1 = fractal->transformCommon.multiplierKaleidoscopeBias1;
							if (kalAngle1 > 0.0f)
							{
								val = 1.0f + (val - 1.0f) * native_cos(kalAngle1 * val);
							}
							REAL phRand1 = fractal->transformCommon.multiplierPhaseRandomise1;
							if (phRand1 > 0.0f)
							{
								int phseed1 = (int)(z.x * 73856.0f + z.y * 19349.0f + z.z * 83492.0f) + 1;
								phseed1 = (phseed1 ^ (phseed1 >> 13)) * 1274126177;
								phseed1 = phseed1 ^ (phseed1 >> 16);
								REAL phJitter1 = ((REAL)(phseed1 & 0xFFFF) / 65535.0f - 0.5f) * phRand1;
								val = 1.0f + (val - 1.0f) * native_cos(phJitter1 * 2.0f * M_PI_F);
							}
							REAL plOff1 = fractal->transformCommon.multiplierPhaseLockOffset1;
							if (plOff1 != 0.0f)
							{
								val = 1.0f + (val - 1.0f) * native_cos(plOff1 * M_PI_F);
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
						REAL denom = native_powr(2.718281828f, freq) - 1.0f;
															val = 1.0f + (val - 1.0f) * (fabs(denom) > 1e-12f
																? (native_powr(2.718281828f, t * freq) - 1.0f) / denom
																: t);
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
						int seed = aux->i * 73856093 + (fractal->transformCommon.multiplierNoiseSeed2 > 0 ? fractal->transformCommon.multiplierNoiseSeed2 : 2) * 19349663;
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

							// Clip Drive (pre-gain)
							if (fractal->transformCommon.multiplierClipDrive2 != 1.0f)
							{
								REAL drv = fractal->transformCommon.multiplierClipDrive2;
								val = 1.0f + (val - 1.0f) * drv;
							}
							// Clip Rectify: 0=off, 1=half(clamp neg to 0), 2=full(abs)
							{
								int cr = fractal->transformCommon.multiplierClipRectify2;
								if (cr == 1 && val < 1.0f) val = 1.0f;
								else if (cr == 2) val = 1.0f + fabs(val - 1.0f);
							}
							// Clip Fold (wavefolder)
							if (fractal->transformCommon.multiplierClipFold2)
							{
								int folds = fractal->transformCommon.multiplierClipFoldCount2;
								if (folds < 1) folds = 1;
								REAL ceil = fractal->transformCommon.multiplierClipCeiling2;
								REAL flr = fractal->transformCommon.multiplierClipFloor2;
								for (int fi = 0; fi < folds; fi++)
								{
									if (val > ceil) val = 2.0f * ceil - val;
									if (val < flr) val = 2.0f * flr - val;
								}
							}
							// Clip Ceiling / Floor (hard clamp with asymmetry)
							if (!fractal->transformCommon.multiplierClipFold2)
							{
								REAL ceil = fractal->transformCommon.multiplierClipCeiling2;
								REAL flr = fractal->transformCommon.multiplierClipFloor2;
								REAL asym = fractal->transformCommon.multiplierClipAsymmetry2;
								ceil += asym;
								flr -= asym;
								REAL curve = fractal->transformCommon.multiplierClipCurve2;
								REAL knee = fractal->transformCommon.multiplierClipKnee2;
								if (curve > 0.0f || knee > 0.0f)
								{
									REAL k = fmax(knee, 0.001f);
									if (val > ceil - k)
									{
										REAL x = (val - (ceil - k)) / (2.0f * k);
										x = fmin(fmax(x, 0.0f), 1.0f);
										REAL sm = x * x * (3.0f - 2.0f * x);
										val = (ceil - k) + k * sm * (1.0f + curve);
										if (val > ceil) val = ceil;
									}
									if (val < flr + k)
									{
										REAL x = ((flr + k) - val) / (2.0f * k);
										x = fmin(fmax(x, 0.0f), 1.0f);
										REAL sm = x * x * (3.0f - 2.0f * x);
										val = (flr + k) - k * sm * (1.0f + curve);
										if (val < flr) val = flr;
									}
								}
								else
								{
									if (val > ceil) val = ceil;
									if (val < flr) val = flr;
								}
							}
							// Clip Mix (blend clipped/unclipped)
							if (fractal->transformCommon.multiplierClipMix2 < 1.0f)
							{
								REAL mx = fractal->transformCommon.multiplierClipMix2;
								val = 1.0f + mx * (val - 1.0f);
							}

							// === Inverse Processing ===
							{
								int doInverse = fractal->transformCommon.multiplierInverse2;
								if (fractal->transformCommon.multiplierInvOscillate2)
									doInverse = (aux->i % 2 == 0) ? doInverse : !doInverse;
								if (doInverse)
								{
									REAL origVal = val;
									REAL diff = val - 1.0f;
									REAL absDiff = fabs(diff);
									REAL rMin = fractal->transformCommon.multiplierInvRangeMin2;
									REAL rMax = fractal->transformCommon.multiplierInvRangeMax2;
									if (absDiff >= rMin && absDiff <= rMax)
									{
										REAL thr = fractal->transformCommon.multiplierInvThreshold2;
										if (absDiff >= thr)
										{
											REAL bias = fractal->transformCommon.multiplierInvBias2;
											REAL center = 1.0f + bias;
											int imode = fractal->transformCommon.multiplierInvMode2;
											if (imode == 0)
												val = center + (fabs(val - center) > 1e-15f ? (1.0f / (val - center)) : 1e15f);
											else if (imode == 1)
												val = center - (val - center);
											else if (imode == 2)
												val = center + (1.0f - fabs(val - center));
											else if (imode == 3)
												val = center - fabs(val - center) * ((val > center) ? 1.0f : -1.0f);
											REAL sm = fractal->transformCommon.multiplierInvSmooth2;
											if (sm > 0.0f)
											{
												REAL blend = fmin(absDiff / (thr + sm + 1e-15f), 1.0f);
												blend = blend * blend * (3.0f - 2.0f * blend);
												val = origVal + blend * (val - origVal);
											}
											REAL idcy = fractal->transformCommon.multiplierInvDecay2;
											if (idcy > 0.0f)
											{
												REAL rng = (REAL)(fractal->transformCommon.multiplierStopIter2 - fractal->transformCommon.multiplierStartIter2);
												REAL td = (rng > 0.0f) ? (REAL)(aux->i - fractal->transformCommon.multiplierStartIter2) / rng : 0.0f;
												REAL fade = native_exp(-idcy * td * 5.0f);
												val = origVal + fade * (val - origVal);
											}
											REAL str = fractal->transformCommon.multiplierInvStrength2;
											if (str < 1.0f)
												val = origVal + str * (val - origVal);
										}
									}
								}
							}

				
							// Burst / Falloff / Wrap / Conditional for slot 2
							int burstLen2 = fractal->transformCommon.multiplierBurstLength2;
							int burstGap2 = fractal->transformCommon.multiplierBurstGap2;
							if (burstLen2 > 0 && burstGap2 > 0)
							{
								int cycle2 = burstLen2 + burstGap2;
								int phase2 = (aux->i - fractal->transformCommon.multiplierStartIter2) % cycle2;
								if (phase2 >= burstLen2) val = 1.0f;
							}
							REAL sphFall2 = fractal->transformCommon.multiplierSphericalFalloff2;
							if (sphFall2 > 0.0f)
							{
								REAL dist2 = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								REAL falloff2 = native_exp(-sphFall2 * dist2);
								val = 1.0f + (val - 1.0f) * falloff2;
							}
							REAL wrapR2 = fractal->transformCommon.multiplierWrapRange2;
							if (wrapR2 > 0.0f)
							{
								REAL shifted2 = val - 1.0f;
								shifted2 = fmod(shifted2, wrapR2);
								if (shifted2 < 0.0f) shifted2 += wrapR2;
								val = 1.0f + shifted2;
							}
							int condMode2 = fractal->transformCommon.multiplierConditionalMode2;
							if (condMode2 == 1 && z.x < 0.0f) val = 1.0f;
							else if (condMode2 == 2 && z.x >= 0.0f) val = 1.0f;
							else if (condMode2 == 3)
							{
								REAL condDist2 = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								if (condDist2 < fractal->transformCommon.multiplierConditionalThreshold2) val = 1.0f;
							}

														// Accumulate for slot 2
							if (fractal->transformCommon.multiplierAccumulate2 && prevMultVal != 1.0f)
								val = 1.0f + (val - 1.0f) + (prevMultVal - 1.0f);

							
							// === Top-10 params for slot 2 ===
							if (fractal->transformCommon.multiplierSlotDisable2) { val = 1.0f; }
							else {
							REAL cullDist2 = fractal->transformCommon.multiplierDistCull2;
							if (cullDist2 > 0.0f && (z.x * z.x + z.y * z.y + z.z * z.z) > cullDist2 * cullDist2)
								val = 1.0f;
							else {

							int rampIn2 = fractal->transformCommon.multiplierRampIn2;
							if (rampIn2 > 0)
							{
								int elapsed2 = aux->i - fractal->transformCommon.multiplierStartIter2;
								if (elapsed2 < rampIn2)
								{
									REAL t2 = (REAL)elapsed2 / (REAL)rampIn2;
									t2 = t2 * t2 * (3.0f - 2.0f * t2);
									val = 1.0f + (val - 1.0f) * t2;
								}
							}
							int rampOut2 = fractal->transformCommon.multiplierRampOut2;
							if (rampOut2 > 0)
							{
								int remaining2 = fractal->transformCommon.multiplierStopIter2 - aux->i;
								if (remaining2 < rampOut2 && remaining2 >= 0)
								{
									REAL t2 = (REAL)remaining2 / (REAL)rampOut2;
									t2 = t2 * t2 * (3.0f - 2.0f * t2);
									val = 1.0f + (val - 1.0f) * t2;
								}
							}
							REAL cylBias2 = fractal->transformCommon.multiplierCylindricalBias2;
							if (cylBias2 > 0.0f)
							{
								REAL cylDist2 = native_sqrt(z.x * z.x + z.y * z.y);
								REAL cylFade2 = native_exp(-cylBias2 * cylDist2);
								val = 1.0f + (val - 1.0f) * cylFade2;
							}
							REAL softExp2 = fractal->transformCommon.multiplierSoftExp2;
							if (softExp2 > 0.0f && val < 1.0f)
							{
								REAL v2 = val - 1.0f;
								val = 1.0f + softExp2 * (native_exp(v2 / fmax(softExp2, 1e-12f)) - 1.0f);
							}
							REAL slewRate2 = fractal->transformCommon.multiplierSlewRate2;
							if (slewRate2 > 0.0f && prevMultVal != 1.0f)
							{
								REAL delta2 = val - prevMultVal;
								if (fabs(delta2) > slewRate2)
									val = prevMultVal + (delta2 > 0.0f ? slewRate2 : -slewRate2);
							}
							REAL hyst2 = fractal->transformCommon.multiplierHysteresis2;
							if (hyst2 > 0.0f)
							{
								REAL hystDist2 = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								REAL hystThresh2 = fractal->transformCommon.multiplierThreshold2;
								if (hystDist2 > hystThresh2 - hyst2 * 0.5f && hystDist2 < hystThresh2 + hyst2 * 0.5f)
								{
									REAL blend2 = (hystDist2 - (hystThresh2 - hyst2 * 0.5f)) / hyst2;
									val = 1.0f + (val - 1.0f) * blend2;
								}
							}
							REAL aaStep2 = fractal->transformCommon.multiplierAntiAlias2;
							if (aaStep2 > 0.0f)
							{
								REAL aaDist2 = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								REAL aaThresh2 = fractal->transformCommon.multiplierThreshold2;
								REAL aaT2 = (aaDist2 - (aaThresh2 - aaStep2)) / (2.0f * aaStep2);
								aaT2 = fmax(0.0f, fmin(1.0f, aaT2));
								aaT2 = aaT2 * aaT2 * (3.0f - 2.0f * aaT2);
								val = 1.0f + (val - 1.0f) * aaT2;
							}
							REAL neutralEps2 = fractal->transformCommon.multiplierNeutralEps2;
							if (neutralEps2 > 0.0f && fabs(val - 1.0f) < neutralEps2)
								val = 1.0f;

							} // end else distCull
							} // end else slotDisable

							
							REAL gradDir2 = fractal->transformCommon.multiplierGradientDir2;
							if (gradDir2 != 0.0f)
							{
								REAL r2g = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								if (r2g > 1e-12f)
								{
									REAL cosW2 = (z.x * native_cos(gradDir2) + z.y * native_sin(gradDir2)) / r2g;
									REAL blend2 = (cosW2 + 1.0f) * 0.5f;
									val = 1.0f + (val - 1.0f) * blend2;
								}
							}
							REAL voroScale2 = fractal->transformCommon.multiplierVoronoiScale2;
							if (voroScale2 > 0.0f)
							{
								REAL vx2 = z.x * voroScale2;
								REAL vy2 = z.y * voroScale2;
								REAL vz2 = z.z * voroScale2;
								REAL fx2 = vx2 - floor(vx2) - 0.5f;
								REAL fy2 = vy2 - floor(vy2) - 0.5f;
								REAL fz2 = vz2 - floor(vz2) - 0.5f;
								REAL vDist2 = native_sqrt(fx2 * fx2 + fy2 * fy2 + fz2 * fz2);
								val = 1.0f + (val - 1.0f) * fmin(vDist2 * 2.0f, 1.0f);
							}
							REAL torusR2 = fractal->transformCommon.multiplierToroidalR2;
							if (torusR2 > 0.0f)
							{
								REAL xyR2 = native_sqrt(z.x * z.x + z.y * z.y);
								REAL tDist2 = native_sqrt((xyR2 - torusR2) * (xyR2 - torusR2) + z.z * z.z);
								REAL tFade2 = native_exp(-tDist2);
								val = 1.0f + (val - 1.0f) * tFade2;
							}
							int angStripes2 = fractal->transformCommon.multiplierAngularStripes2;
							if (angStripes2 > 0)
							{
								REAL angle2 = atan2(z.y, z.x);
								int sector2 = (int)floor((angle2 + M_PI_F) / (2.0f * M_PI_F) * (REAL)angStripes2);
								if (sector2 % 2 != 0) val = 1.0f;
							}
							REAL geoP2 = fractal->transformCommon.multiplierGeoProgression2;
							if (geoP2 != 1.0f)
							{
								int elapsed2g = aux->i - fractal->transformCommon.multiplierStartIter2;
								if (elapsed2g > 0)
									val = 1.0f + (val - 1.0f) * native_powr(geoP2, (REAL)elapsed2g);
							}
							int parity2 = fractal->transformCommon.multiplierParityGate2;
							if (parity2 == 1 && aux->i % 2 == 0) val = 1.0f;
							if (parity2 == 2 && aux->i % 2 != 0) val = 1.0f;
							if (fractal->transformCommon.multiplierFibonacciStep2)
							{
								bool isFib2 = false;
								int fa2 = 0, fb2 = 1;
								while (fb2 <= aux->i) { int fc2 = fa2 + fb2; fa2 = fb2; fb2 = fc2; if (fb2 == aux->i) isFib2 = true; }
								if (aux->i == 0 || aux->i == 1) isFib2 = true;
								if (!isFib2) val = 1.0f;
							}

							
							int icurve2 = fractal->transformCommon.multiplierInterpCurve2;
							if (icurve2 > 0 && val != 1.0f)
							{
								REAL dev2 = val - 1.0f;
								REAL tn2 = fabs(dev2);
								if (tn2 > 1.0f) tn2 = 1.0f;
								if (icurve2 == 1) tn2 = tn2 * tn2 * tn2;
								else if (icurve2 == 2) tn2 = tn2 * tn2 * (3.0f - 2.0f * tn2);
								else if (icurve2 == 3) tn2 = (1.0f - native_cos(tn2 * M_PI_F)) * 0.5f;
								val = 1.0f + (dev2 > 0 ? tn2 : -tn2);
							}
							REAL dq2 = fractal->transformCommon.multiplierDitherQuantize2;
							if (dq2 > 0.0f)
							{
								int dqseed2 = aux->i * 48271 + 2 * 16807;
								dqseed2 = (dqseed2 ^ (dqseed2 >> 15)) * 1103515245;
								REAL dither2 = ((REAL)(dqseed2 & 0xFFFF) / 65535.0f - 0.5f) * dq2;
								val = floor((val + dither2) / dq2 + 0.5f) * dq2;
							}
							if (fractal->transformCommon.multiplierComplexMag2)
							{
								REAL cmag2 = native_sqrt(z.x * z.x + z.y * z.y);
								if (cmag2 > 1e-12f) val = 1.0f + (val - 1.0f) * cmag2;
							}
							REAL pidx2 = fractal->transformCommon.multiplierPaletteIdxDrive2;
							if (pidx2 > 0.0f)
							{
								aux->color += (val - 1.0f) * pidx2 * 256.0f;
							}
							int tLayers2 = fractal->transformCommon.multiplierTurbulenceLayers2;
							if (tLayers2 > 1 && val != 1.0f)
							{
								REAL turbSum2 = val - 1.0f;
								REAL amp2 = 0.5f;
								for (int tl2 = 1; tl2 < tLayers2; tl2++)
								{
									int tseed2 = aux->i * 73856093 + tl2 * 19349663 + 2 * 83492791;
									tseed2 = (tseed2 ^ (tseed2 >> 13)) * 1274126177;
									tseed2 = tseed2 ^ (tseed2 >> 16);
									REAL tnoise2 = (REAL)(tseed2 & 0xFFFF) / 65535.0f - 0.5f;
									turbSum2 += tnoise2 * amp2 * (val - 1.0f);
									amp2 *= 0.5f;
								}
								val = 1.0f + turbSum2;
							}
							REAL kalAngle2 = fractal->transformCommon.multiplierKaleidoscopeBias2;
							if (kalAngle2 > 0.0f)
							{
								val = 1.0f + (val - 1.0f) * native_cos(kalAngle2 * val);
							}
							REAL phRand2 = fractal->transformCommon.multiplierPhaseRandomise2;
							if (phRand2 > 0.0f)
							{
								int phseed2 = (int)(z.x * 73856.0f + z.y * 19349.0f + z.z * 83492.0f) + 2;
								phseed2 = (phseed2 ^ (phseed2 >> 13)) * 1274126177;
								phseed2 = phseed2 ^ (phseed2 >> 16);
								REAL phJitter2 = ((REAL)(phseed2 & 0xFFFF) / 65535.0f - 0.5f) * phRand2;
								val = 1.0f + (val - 1.0f) * native_cos(phJitter2 * 2.0f * M_PI_F);
							}
							REAL plOff2 = fractal->transformCommon.multiplierPhaseLockOffset2;
							if (plOff2 != 0.0f)
							{
								val = 1.0f + (val - 1.0f) * native_cos(plOff2 * M_PI_F);
							}

							switch (fractal->transformCommon.multiplierMode2)
				{
					
case 11:
								{
									REAL chirpRate1 = freq * 0.1f;
									val = native_sin(2.0f * M_PI_F * (freq1 + chirpRate1 * t) * t + phase1);
									val = 1.0f + val * (val - 1.0f);
									break;
								}
case 13:
								{
									REAL sigma1 = 10.0f, rho1 = 28.0f, beta1 = 8.0f / 3.0f;
									REAL dt1 = 0.01f;
									REAL lx1 = 1.0f, ly1 = 1.0f, lz1 = 1.0f;
									int seed1 = fractal->transformCommon.multiplierNoiseSeed1 + 1;
									lx1 += (REAL)(seed1 % 100) * 0.01f;
									for (int li = 0; li < (int)(t * 100.0f) + 1; li++)
									{
										REAL dx1 = sigma1 * (ly1 - lx1) * dt1;
										REAL dy1 = (lx1 * (rho1 - lz1) - ly1) * dt1;
										REAL dz1 = (lx1 * ly1 - beta1 * lz1) * dt1;
										lx1 += dx1; ly1 += dy1; lz1 += dz1;
									}
									val = 1.0f + fmod(fabs(lx1), 1.0f) * (val - 1.0f);
									break;
								}
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
						REAL denom = native_powr(2.718281828f, freq) - 1.0f;
															val = 1.0f + (val - 1.0f) * (fabs(denom) > 1e-12f
																? (native_powr(2.718281828f, t * freq) - 1.0f) / denom
																: t);
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
						int seed = aux->i * 73856093 + (fractal->transformCommon.multiplierNoiseSeed3 > 0 ? fractal->transformCommon.multiplierNoiseSeed3 : 3) * 19349663;
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

							// Clip Drive (pre-gain)
							if (fractal->transformCommon.multiplierClipDrive3 != 1.0f)
							{
								REAL drv = fractal->transformCommon.multiplierClipDrive3;
								val = 1.0f + (val - 1.0f) * drv;
							}
							// Clip Rectify: 0=off, 1=half(clamp neg to 0), 2=full(abs)
							{
								int cr = fractal->transformCommon.multiplierClipRectify3;
								if (cr == 1 && val < 1.0f) val = 1.0f;
								else if (cr == 2) val = 1.0f + fabs(val - 1.0f);
							}
							// Clip Fold (wavefolder)
							if (fractal->transformCommon.multiplierClipFold3)
							{
								int folds = fractal->transformCommon.multiplierClipFoldCount3;
								if (folds < 1) folds = 1;
								REAL ceil = fractal->transformCommon.multiplierClipCeiling3;
								REAL flr = fractal->transformCommon.multiplierClipFloor3;
								for (int fi = 0; fi < folds; fi++)
								{
									if (val > ceil) val = 2.0f * ceil - val;
									if (val < flr) val = 2.0f * flr - val;
								}
							}
							// Clip Ceiling / Floor (hard clamp with asymmetry)
							if (!fractal->transformCommon.multiplierClipFold3)
							{
								REAL ceil = fractal->transformCommon.multiplierClipCeiling3;
								REAL flr = fractal->transformCommon.multiplierClipFloor3;
								REAL asym = fractal->transformCommon.multiplierClipAsymmetry3;
								ceil += asym;
								flr -= asym;
								REAL curve = fractal->transformCommon.multiplierClipCurve3;
								REAL knee = fractal->transformCommon.multiplierClipKnee3;
								if (curve > 0.0f || knee > 0.0f)
								{
									REAL k = fmax(knee, 0.001f);
									if (val > ceil - k)
									{
										REAL x = (val - (ceil - k)) / (2.0f * k);
										x = fmin(fmax(x, 0.0f), 1.0f);
										REAL sm = x * x * (3.0f - 2.0f * x);
										val = (ceil - k) + k * sm * (1.0f + curve);
										if (val > ceil) val = ceil;
									}
									if (val < flr + k)
									{
										REAL x = ((flr + k) - val) / (2.0f * k);
										x = fmin(fmax(x, 0.0f), 1.0f);
										REAL sm = x * x * (3.0f - 2.0f * x);
										val = (flr + k) - k * sm * (1.0f + curve);
										if (val < flr) val = flr;
									}
								}
								else
								{
									if (val > ceil) val = ceil;
									if (val < flr) val = flr;
								}
							}
							// Clip Mix (blend clipped/unclipped)
							if (fractal->transformCommon.multiplierClipMix3 < 1.0f)
							{
								REAL mx = fractal->transformCommon.multiplierClipMix3;
								val = 1.0f + mx * (val - 1.0f);
							}

							// === Inverse Processing ===
							{
								int doInverse = fractal->transformCommon.multiplierInverse3;
								if (fractal->transformCommon.multiplierInvOscillate3)
									doInverse = (aux->i % 2 == 0) ? doInverse : !doInverse;
								if (doInverse)
								{
									REAL origVal = val;
									REAL diff = val - 1.0f;
									REAL absDiff = fabs(diff);
									REAL rMin = fractal->transformCommon.multiplierInvRangeMin3;
									REAL rMax = fractal->transformCommon.multiplierInvRangeMax3;
									if (absDiff >= rMin && absDiff <= rMax)
									{
										REAL thr = fractal->transformCommon.multiplierInvThreshold3;
										if (absDiff >= thr)
										{
											REAL bias = fractal->transformCommon.multiplierInvBias3;
											REAL center = 1.0f + bias;
											int imode = fractal->transformCommon.multiplierInvMode3;
											if (imode == 0)
												val = center + (fabs(val - center) > 1e-15f ? (1.0f / (val - center)) : 1e15f);
											else if (imode == 1)
												val = center - (val - center);
											else if (imode == 2)
												val = center + (1.0f - fabs(val - center));
											else if (imode == 3)
												val = center - fabs(val - center) * ((val > center) ? 1.0f : -1.0f);
											REAL sm = fractal->transformCommon.multiplierInvSmooth3;
											if (sm > 0.0f)
											{
												REAL blend = fmin(absDiff / (thr + sm + 1e-15f), 1.0f);
												blend = blend * blend * (3.0f - 2.0f * blend);
												val = origVal + blend * (val - origVal);
											}
											REAL idcy = fractal->transformCommon.multiplierInvDecay3;
											if (idcy > 0.0f)
											{
												REAL rng = (REAL)(fractal->transformCommon.multiplierStopIter3 - fractal->transformCommon.multiplierStartIter3);
												REAL td = (rng > 0.0f) ? (REAL)(aux->i - fractal->transformCommon.multiplierStartIter3) / rng : 0.0f;
												REAL fade = native_exp(-idcy * td * 5.0f);
												val = origVal + fade * (val - origVal);
											}
											REAL str = fractal->transformCommon.multiplierInvStrength3;
											if (str < 1.0f)
												val = origVal + str * (val - origVal);
										}
									}
								}
							}

				
							// Burst / Falloff / Wrap / Conditional for slot 3
							int burstLen3 = fractal->transformCommon.multiplierBurstLength3;
							int burstGap3 = fractal->transformCommon.multiplierBurstGap3;
							if (burstLen3 > 0 && burstGap3 > 0)
							{
								int cycle3 = burstLen3 + burstGap3;
								int phase3 = (aux->i - fractal->transformCommon.multiplierStartIter3) % cycle3;
								if (phase3 >= burstLen3) val = 1.0f;
							}
							REAL sphFall3 = fractal->transformCommon.multiplierSphericalFalloff3;
							if (sphFall3 > 0.0f)
							{
								REAL dist3 = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								REAL falloff3 = native_exp(-sphFall3 * dist3);
								val = 1.0f + (val - 1.0f) * falloff3;
							}
							REAL wrapR3 = fractal->transformCommon.multiplierWrapRange3;
							if (wrapR3 > 0.0f)
							{
								REAL shifted3 = val - 1.0f;
								shifted3 = fmod(shifted3, wrapR3);
								if (shifted3 < 0.0f) shifted3 += wrapR3;
								val = 1.0f + shifted3;
							}
							int condMode3 = fractal->transformCommon.multiplierConditionalMode3;
							if (condMode3 == 1 && z.x < 0.0f) val = 1.0f;
							else if (condMode3 == 2 && z.x >= 0.0f) val = 1.0f;
							else if (condMode3 == 3)
							{
								REAL condDist3 = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								if (condDist3 < fractal->transformCommon.multiplierConditionalThreshold3) val = 1.0f;
							}

														// Accumulate for slot 3
							if (fractal->transformCommon.multiplierAccumulate3 && prevMultVal != 1.0f)
								val = 1.0f + (val - 1.0f) + (prevMultVal - 1.0f);

							
							// === Top-10 params for slot 3 ===
							if (fractal->transformCommon.multiplierSlotDisable3) { val = 1.0f; }
							else {
							REAL cullDist3 = fractal->transformCommon.multiplierDistCull3;
							if (cullDist3 > 0.0f && (z.x * z.x + z.y * z.y + z.z * z.z) > cullDist3 * cullDist3)
								val = 1.0f;
							else {

							int rampIn3 = fractal->transformCommon.multiplierRampIn3;
							if (rampIn3 > 0)
							{
								int elapsed3 = aux->i - fractal->transformCommon.multiplierStartIter3;
								if (elapsed3 < rampIn3)
								{
									REAL t3 = (REAL)elapsed3 / (REAL)rampIn3;
									t3 = t3 * t3 * (3.0f - 2.0f * t3);
									val = 1.0f + (val - 1.0f) * t3;
								}
							}
							int rampOut3 = fractal->transformCommon.multiplierRampOut3;
							if (rampOut3 > 0)
							{
								int remaining3 = fractal->transformCommon.multiplierStopIter3 - aux->i;
								if (remaining3 < rampOut3 && remaining3 >= 0)
								{
									REAL t3 = (REAL)remaining3 / (REAL)rampOut3;
									t3 = t3 * t3 * (3.0f - 2.0f * t3);
									val = 1.0f + (val - 1.0f) * t3;
								}
							}
							REAL cylBias3 = fractal->transformCommon.multiplierCylindricalBias3;
							if (cylBias3 > 0.0f)
							{
								REAL cylDist3 = native_sqrt(z.x * z.x + z.y * z.y);
								REAL cylFade3 = native_exp(-cylBias3 * cylDist3);
								val = 1.0f + (val - 1.0f) * cylFade3;
							}
							REAL softExp3 = fractal->transformCommon.multiplierSoftExp3;
							if (softExp3 > 0.0f && val < 1.0f)
							{
								REAL v3 = val - 1.0f;
								val = 1.0f + softExp3 * (native_exp(v3 / fmax(softExp3, 1e-12f)) - 1.0f);
							}
							REAL slewRate3 = fractal->transformCommon.multiplierSlewRate3;
							if (slewRate3 > 0.0f && prevMultVal != 1.0f)
							{
								REAL delta3 = val - prevMultVal;
								if (fabs(delta3) > slewRate3)
									val = prevMultVal + (delta3 > 0.0f ? slewRate3 : -slewRate3);
							}
							REAL hyst3 = fractal->transformCommon.multiplierHysteresis3;
							if (hyst3 > 0.0f)
							{
								REAL hystDist3 = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								REAL hystThresh3 = fractal->transformCommon.multiplierThreshold3;
								if (hystDist3 > hystThresh3 - hyst3 * 0.5f && hystDist3 < hystThresh3 + hyst3 * 0.5f)
								{
									REAL blend3 = (hystDist3 - (hystThresh3 - hyst3 * 0.5f)) / hyst3;
									val = 1.0f + (val - 1.0f) * blend3;
								}
							}
							REAL aaStep3 = fractal->transformCommon.multiplierAntiAlias3;
							if (aaStep3 > 0.0f)
							{
								REAL aaDist3 = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								REAL aaThresh3 = fractal->transformCommon.multiplierThreshold3;
								REAL aaT3 = (aaDist3 - (aaThresh3 - aaStep3)) / (2.0f * aaStep3);
								aaT3 = fmax(0.0f, fmin(1.0f, aaT3));
								aaT3 = aaT3 * aaT3 * (3.0f - 2.0f * aaT3);
								val = 1.0f + (val - 1.0f) * aaT3;
							}
							REAL neutralEps3 = fractal->transformCommon.multiplierNeutralEps3;
							if (neutralEps3 > 0.0f && fabs(val - 1.0f) < neutralEps3)
								val = 1.0f;

							} // end else distCull
							} // end else slotDisable

							
							REAL gradDir3 = fractal->transformCommon.multiplierGradientDir3;
							if (gradDir3 != 0.0f)
							{
								REAL r3g = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								if (r3g > 1e-12f)
								{
									REAL cosW3 = (z.x * native_cos(gradDir3) + z.y * native_sin(gradDir3)) / r3g;
									REAL blend3 = (cosW3 + 1.0f) * 0.5f;
									val = 1.0f + (val - 1.0f) * blend3;
								}
							}
							REAL voroScale3 = fractal->transformCommon.multiplierVoronoiScale3;
							if (voroScale3 > 0.0f)
							{
								REAL vx3 = z.x * voroScale3;
								REAL vy3 = z.y * voroScale3;
								REAL vz3 = z.z * voroScale3;
								REAL fx3 = vx3 - floor(vx3) - 0.5f;
								REAL fy3 = vy3 - floor(vy3) - 0.5f;
								REAL fz3 = vz3 - floor(vz3) - 0.5f;
								REAL vDist3 = native_sqrt(fx3 * fx3 + fy3 * fy3 + fz3 * fz3);
								val = 1.0f + (val - 1.0f) * fmin(vDist3 * 2.0f, 1.0f);
							}
							REAL torusR3 = fractal->transformCommon.multiplierToroidalR3;
							if (torusR3 > 0.0f)
							{
								REAL xyR3 = native_sqrt(z.x * z.x + z.y * z.y);
								REAL tDist3 = native_sqrt((xyR3 - torusR3) * (xyR3 - torusR3) + z.z * z.z);
								REAL tFade3 = native_exp(-tDist3);
								val = 1.0f + (val - 1.0f) * tFade3;
							}
							int angStripes3 = fractal->transformCommon.multiplierAngularStripes3;
							if (angStripes3 > 0)
							{
								REAL angle3 = atan2(z.y, z.x);
								int sector3 = (int)floor((angle3 + M_PI_F) / (2.0f * M_PI_F) * (REAL)angStripes3);
								if (sector3 % 2 != 0) val = 1.0f;
							}
							REAL geoP3 = fractal->transformCommon.multiplierGeoProgression3;
							if (geoP3 != 1.0f)
							{
								int elapsed3g = aux->i - fractal->transformCommon.multiplierStartIter3;
								if (elapsed3g > 0)
									val = 1.0f + (val - 1.0f) * native_powr(geoP3, (REAL)elapsed3g);
							}
							int parity3 = fractal->transformCommon.multiplierParityGate3;
							if (parity3 == 1 && aux->i % 2 == 0) val = 1.0f;
							if (parity3 == 2 && aux->i % 2 != 0) val = 1.0f;
							if (fractal->transformCommon.multiplierFibonacciStep3)
							{
								bool isFib3 = false;
								int fa3 = 0, fb3 = 1;
								while (fb3 <= aux->i) { int fc3 = fa3 + fb3; fa3 = fb3; fb3 = fc3; if (fb3 == aux->i) isFib3 = true; }
								if (aux->i == 0 || aux->i == 1) isFib3 = true;
								if (!isFib3) val = 1.0f;
							}

							
							int icurve3 = fractal->transformCommon.multiplierInterpCurve3;
							if (icurve3 > 0 && val != 1.0f)
							{
								REAL dev3 = val - 1.0f;
								REAL tn3 = fabs(dev3);
								if (tn3 > 1.0f) tn3 = 1.0f;
								if (icurve3 == 1) tn3 = tn3 * tn3 * tn3;
								else if (icurve3 == 2) tn3 = tn3 * tn3 * (3.0f - 2.0f * tn3);
								else if (icurve3 == 3) tn3 = (1.0f - native_cos(tn3 * M_PI_F)) * 0.5f;
								val = 1.0f + (dev3 > 0 ? tn3 : -tn3);
							}
							REAL dq3 = fractal->transformCommon.multiplierDitherQuantize3;
							if (dq3 > 0.0f)
							{
								int dqseed3 = aux->i * 48271 + 3 * 16807;
								dqseed3 = (dqseed3 ^ (dqseed3 >> 15)) * 1103515245;
								REAL dither3 = ((REAL)(dqseed3 & 0xFFFF) / 65535.0f - 0.5f) * dq3;
								val = floor((val + dither3) / dq3 + 0.5f) * dq3;
							}
							if (fractal->transformCommon.multiplierComplexMag3)
							{
								REAL cmag3 = native_sqrt(z.x * z.x + z.y * z.y);
								if (cmag3 > 1e-12f) val = 1.0f + (val - 1.0f) * cmag3;
							}
							REAL pidx3 = fractal->transformCommon.multiplierPaletteIdxDrive3;
							if (pidx3 > 0.0f)
							{
								aux->color += (val - 1.0f) * pidx3 * 256.0f;
							}
							int tLayers3 = fractal->transformCommon.multiplierTurbulenceLayers3;
							if (tLayers3 > 1 && val != 1.0f)
							{
								REAL turbSum3 = val - 1.0f;
								REAL amp3 = 0.5f;
								for (int tl3 = 1; tl3 < tLayers3; tl3++)
								{
									int tseed3 = aux->i * 73856093 + tl3 * 19349663 + 3 * 83492791;
									tseed3 = (tseed3 ^ (tseed3 >> 13)) * 1274126177;
									tseed3 = tseed3 ^ (tseed3 >> 16);
									REAL tnoise3 = (REAL)(tseed3 & 0xFFFF) / 65535.0f - 0.5f;
									turbSum3 += tnoise3 * amp3 * (val - 1.0f);
									amp3 *= 0.5f;
								}
								val = 1.0f + turbSum3;
							}
							REAL kalAngle3 = fractal->transformCommon.multiplierKaleidoscopeBias3;
							if (kalAngle3 > 0.0f)
							{
								val = 1.0f + (val - 1.0f) * native_cos(kalAngle3 * val);
							}
							REAL phRand3 = fractal->transformCommon.multiplierPhaseRandomise3;
							if (phRand3 > 0.0f)
							{
								int phseed3 = (int)(z.x * 73856.0f + z.y * 19349.0f + z.z * 83492.0f) + 3;
								phseed3 = (phseed3 ^ (phseed3 >> 13)) * 1274126177;
								phseed3 = phseed3 ^ (phseed3 >> 16);
								REAL phJitter3 = ((REAL)(phseed3 & 0xFFFF) / 65535.0f - 0.5f) * phRand3;
								val = 1.0f + (val - 1.0f) * native_cos(phJitter3 * 2.0f * M_PI_F);
							}
							REAL plOff3 = fractal->transformCommon.multiplierPhaseLockOffset3;
							if (plOff3 != 0.0f)
							{
								val = 1.0f + (val - 1.0f) * native_cos(plOff3 * M_PI_F);
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
						REAL denom = native_powr(2.718281828f, freq) - 1.0f;
															val = 1.0f + (val - 1.0f) * (fabs(denom) > 1e-12f
																? (native_powr(2.718281828f, t * freq) - 1.0f) / denom
																: t);
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
						int seed = aux->i * 73856093 + (fractal->transformCommon.multiplierNoiseSeed4 > 0 ? fractal->transformCommon.multiplierNoiseSeed4 : 4) * 19349663;
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

							// Clip Drive (pre-gain)
							if (fractal->transformCommon.multiplierClipDrive4 != 1.0f)
							{
								REAL drv = fractal->transformCommon.multiplierClipDrive4;
								val = 1.0f + (val - 1.0f) * drv;
							}
							// Clip Rectify: 0=off, 1=half(clamp neg to 0), 2=full(abs)
							{
								int cr = fractal->transformCommon.multiplierClipRectify4;
								if (cr == 1 && val < 1.0f) val = 1.0f;
								else if (cr == 2) val = 1.0f + fabs(val - 1.0f);
							}
							// Clip Fold (wavefolder)
							if (fractal->transformCommon.multiplierClipFold4)
							{
								int folds = fractal->transformCommon.multiplierClipFoldCount4;
								if (folds < 1) folds = 1;
								REAL ceil = fractal->transformCommon.multiplierClipCeiling4;
								REAL flr = fractal->transformCommon.multiplierClipFloor4;
								for (int fi = 0; fi < folds; fi++)
								{
									if (val > ceil) val = 2.0f * ceil - val;
									if (val < flr) val = 2.0f * flr - val;
								}
							}
							// Clip Ceiling / Floor (hard clamp with asymmetry)
							if (!fractal->transformCommon.multiplierClipFold4)
							{
								REAL ceil = fractal->transformCommon.multiplierClipCeiling4;
								REAL flr = fractal->transformCommon.multiplierClipFloor4;
								REAL asym = fractal->transformCommon.multiplierClipAsymmetry4;
								ceil += asym;
								flr -= asym;
								REAL curve = fractal->transformCommon.multiplierClipCurve4;
								REAL knee = fractal->transformCommon.multiplierClipKnee4;
								if (curve > 0.0f || knee > 0.0f)
								{
									REAL k = fmax(knee, 0.001f);
									if (val > ceil - k)
									{
										REAL x = (val - (ceil - k)) / (2.0f * k);
										x = fmin(fmax(x, 0.0f), 1.0f);
										REAL sm = x * x * (3.0f - 2.0f * x);
										val = (ceil - k) + k * sm * (1.0f + curve);
										if (val > ceil) val = ceil;
									}
									if (val < flr + k)
									{
										REAL x = ((flr + k) - val) / (2.0f * k);
										x = fmin(fmax(x, 0.0f), 1.0f);
										REAL sm = x * x * (3.0f - 2.0f * x);
										val = (flr + k) - k * sm * (1.0f + curve);
										if (val < flr) val = flr;
									}
								}
								else
								{
									if (val > ceil) val = ceil;
									if (val < flr) val = flr;
								}
							}
							// Clip Mix (blend clipped/unclipped)
							if (fractal->transformCommon.multiplierClipMix4 < 1.0f)
							{
								REAL mx = fractal->transformCommon.multiplierClipMix4;
								val = 1.0f + mx * (val - 1.0f);
							}

							// === Inverse Processing ===
							{
								int doInverse = fractal->transformCommon.multiplierInverse4;
								if (fractal->transformCommon.multiplierInvOscillate4)
									doInverse = (aux->i % 2 == 0) ? doInverse : !doInverse;
								if (doInverse)
								{
									REAL origVal = val;
									REAL diff = val - 1.0f;
									REAL absDiff = fabs(diff);
									REAL rMin = fractal->transformCommon.multiplierInvRangeMin4;
									REAL rMax = fractal->transformCommon.multiplierInvRangeMax4;
									if (absDiff >= rMin && absDiff <= rMax)
									{
										REAL thr = fractal->transformCommon.multiplierInvThreshold4;
										if (absDiff >= thr)
										{
											REAL bias = fractal->transformCommon.multiplierInvBias4;
											REAL center = 1.0f + bias;
											int imode = fractal->transformCommon.multiplierInvMode4;
											if (imode == 0)
												val = center + (fabs(val - center) > 1e-15f ? (1.0f / (val - center)) : 1e15f);
											else if (imode == 1)
												val = center - (val - center);
											else if (imode == 2)
												val = center + (1.0f - fabs(val - center));
											else if (imode == 3)
												val = center - fabs(val - center) * ((val > center) ? 1.0f : -1.0f);
											REAL sm = fractal->transformCommon.multiplierInvSmooth4;
											if (sm > 0.0f)
											{
												REAL blend = fmin(absDiff / (thr + sm + 1e-15f), 1.0f);
												blend = blend * blend * (3.0f - 2.0f * blend);
												val = origVal + blend * (val - origVal);
											}
											REAL idcy = fractal->transformCommon.multiplierInvDecay4;
											if (idcy > 0.0f)
											{
												REAL rng = (REAL)(fractal->transformCommon.multiplierStopIter4 - fractal->transformCommon.multiplierStartIter4);
												REAL td = (rng > 0.0f) ? (REAL)(aux->i - fractal->transformCommon.multiplierStartIter4) / rng : 0.0f;
												REAL fade = native_exp(-idcy * td * 5.0f);
												val = origVal + fade * (val - origVal);
											}
											REAL str = fractal->transformCommon.multiplierInvStrength4;
											if (str < 1.0f)
												val = origVal + str * (val - origVal);
										}
									}
								}
							}

				
							// Burst / Falloff / Wrap / Conditional for slot 4
							int burstLen4 = fractal->transformCommon.multiplierBurstLength4;
							int burstGap4 = fractal->transformCommon.multiplierBurstGap4;
							if (burstLen4 > 0 && burstGap4 > 0)
							{
								int cycle4 = burstLen4 + burstGap4;
								int phase4 = (aux->i - fractal->transformCommon.multiplierStartIter4) % cycle4;
								if (phase4 >= burstLen4) val = 1.0f;
							}
							REAL sphFall4 = fractal->transformCommon.multiplierSphericalFalloff4;
							if (sphFall4 > 0.0f)
							{
								REAL dist4 = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								REAL falloff4 = native_exp(-sphFall4 * dist4);
								val = 1.0f + (val - 1.0f) * falloff4;
							}
							REAL wrapR4 = fractal->transformCommon.multiplierWrapRange4;
							if (wrapR4 > 0.0f)
							{
								REAL shifted4 = val - 1.0f;
								shifted4 = fmod(shifted4, wrapR4);
								if (shifted4 < 0.0f) shifted4 += wrapR4;
								val = 1.0f + shifted4;
							}
							int condMode4 = fractal->transformCommon.multiplierConditionalMode4;
							if (condMode4 == 1 && z.x < 0.0f) val = 1.0f;
							else if (condMode4 == 2 && z.x >= 0.0f) val = 1.0f;
							else if (condMode4 == 3)
							{
								REAL condDist4 = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								if (condDist4 < fractal->transformCommon.multiplierConditionalThreshold4) val = 1.0f;
							}

														// Accumulate for slot 4
							if (fractal->transformCommon.multiplierAccumulate4 && prevMultVal != 1.0f)
								val = 1.0f + (val - 1.0f) + (prevMultVal - 1.0f);

							
							// === Top-10 params for slot 4 ===
							if (fractal->transformCommon.multiplierSlotDisable4) { val = 1.0f; }
							else {
							REAL cullDist4 = fractal->transformCommon.multiplierDistCull4;
							if (cullDist4 > 0.0f && (z.x * z.x + z.y * z.y + z.z * z.z) > cullDist4 * cullDist4)
								val = 1.0f;
							else {

							int rampIn4 = fractal->transformCommon.multiplierRampIn4;
							if (rampIn4 > 0)
							{
								int elapsed4 = aux->i - fractal->transformCommon.multiplierStartIter4;
								if (elapsed4 < rampIn4)
								{
									REAL t4 = (REAL)elapsed4 / (REAL)rampIn4;
									t4 = t4 * t4 * (3.0f - 2.0f * t4);
									val = 1.0f + (val - 1.0f) * t4;
								}
							}
							int rampOut4 = fractal->transformCommon.multiplierRampOut4;
							if (rampOut4 > 0)
							{
								int remaining4 = fractal->transformCommon.multiplierStopIter4 - aux->i;
								if (remaining4 < rampOut4 && remaining4 >= 0)
								{
									REAL t4 = (REAL)remaining4 / (REAL)rampOut4;
									t4 = t4 * t4 * (3.0f - 2.0f * t4);
									val = 1.0f + (val - 1.0f) * t4;
								}
							}
							REAL cylBias4 = fractal->transformCommon.multiplierCylindricalBias4;
							if (cylBias4 > 0.0f)
							{
								REAL cylDist4 = native_sqrt(z.x * z.x + z.y * z.y);
								REAL cylFade4 = native_exp(-cylBias4 * cylDist4);
								val = 1.0f + (val - 1.0f) * cylFade4;
							}
							REAL softExp4 = fractal->transformCommon.multiplierSoftExp4;
							if (softExp4 > 0.0f && val < 1.0f)
							{
								REAL v4 = val - 1.0f;
								val = 1.0f + softExp4 * (native_exp(v4 / fmax(softExp4, 1e-12f)) - 1.0f);
							}
							REAL slewRate4 = fractal->transformCommon.multiplierSlewRate4;
							if (slewRate4 > 0.0f && prevMultVal != 1.0f)
							{
								REAL delta4 = val - prevMultVal;
								if (fabs(delta4) > slewRate4)
									val = prevMultVal + (delta4 > 0.0f ? slewRate4 : -slewRate4);
							}
							REAL hyst4 = fractal->transformCommon.multiplierHysteresis4;
							if (hyst4 > 0.0f)
							{
								REAL hystDist4 = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								REAL hystThresh4 = fractal->transformCommon.multiplierThreshold4;
								if (hystDist4 > hystThresh4 - hyst4 * 0.5f && hystDist4 < hystThresh4 + hyst4 * 0.5f)
								{
									REAL blend4 = (hystDist4 - (hystThresh4 - hyst4 * 0.5f)) / hyst4;
									val = 1.0f + (val - 1.0f) * blend4;
								}
							}
							REAL aaStep4 = fractal->transformCommon.multiplierAntiAlias4;
							if (aaStep4 > 0.0f)
							{
								REAL aaDist4 = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								REAL aaThresh4 = fractal->transformCommon.multiplierThreshold4;
								REAL aaT4 = (aaDist4 - (aaThresh4 - aaStep4)) / (2.0f * aaStep4);
								aaT4 = fmax(0.0f, fmin(1.0f, aaT4));
								aaT4 = aaT4 * aaT4 * (3.0f - 2.0f * aaT4);
								val = 1.0f + (val - 1.0f) * aaT4;
							}
							REAL neutralEps4 = fractal->transformCommon.multiplierNeutralEps4;
							if (neutralEps4 > 0.0f && fabs(val - 1.0f) < neutralEps4)
								val = 1.0f;

							} // end else distCull
							} // end else slotDisable

							
							REAL gradDir4 = fractal->transformCommon.multiplierGradientDir4;
							if (gradDir4 != 0.0f)
							{
								REAL r4g = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								if (r4g > 1e-12f)
								{
									REAL cosW4 = (z.x * native_cos(gradDir4) + z.y * native_sin(gradDir4)) / r4g;
									REAL blend4 = (cosW4 + 1.0f) * 0.5f;
									val = 1.0f + (val - 1.0f) * blend4;
								}
							}
							REAL voroScale4 = fractal->transformCommon.multiplierVoronoiScale4;
							if (voroScale4 > 0.0f)
							{
								REAL vx4 = z.x * voroScale4;
								REAL vy4 = z.y * voroScale4;
								REAL vz4 = z.z * voroScale4;
								REAL fx4 = vx4 - floor(vx4) - 0.5f;
								REAL fy4 = vy4 - floor(vy4) - 0.5f;
								REAL fz4 = vz4 - floor(vz4) - 0.5f;
								REAL vDist4 = native_sqrt(fx4 * fx4 + fy4 * fy4 + fz4 * fz4);
								val = 1.0f + (val - 1.0f) * fmin(vDist4 * 2.0f, 1.0f);
							}
							REAL torusR4 = fractal->transformCommon.multiplierToroidalR4;
							if (torusR4 > 0.0f)
							{
								REAL xyR4 = native_sqrt(z.x * z.x + z.y * z.y);
								REAL tDist4 = native_sqrt((xyR4 - torusR4) * (xyR4 - torusR4) + z.z * z.z);
								REAL tFade4 = native_exp(-tDist4);
								val = 1.0f + (val - 1.0f) * tFade4;
							}
							int angStripes4 = fractal->transformCommon.multiplierAngularStripes4;
							if (angStripes4 > 0)
							{
								REAL angle4 = atan2(z.y, z.x);
								int sector4 = (int)floor((angle4 + M_PI_F) / (2.0f * M_PI_F) * (REAL)angStripes4);
								if (sector4 % 2 != 0) val = 1.0f;
							}
							REAL geoP4 = fractal->transformCommon.multiplierGeoProgression4;
							if (geoP4 != 1.0f)
							{
								int elapsed4g = aux->i - fractal->transformCommon.multiplierStartIter4;
								if (elapsed4g > 0)
									val = 1.0f + (val - 1.0f) * native_powr(geoP4, (REAL)elapsed4g);
							}
							int parity4 = fractal->transformCommon.multiplierParityGate4;
							if (parity4 == 1 && aux->i % 2 == 0) val = 1.0f;
							if (parity4 == 2 && aux->i % 2 != 0) val = 1.0f;
							if (fractal->transformCommon.multiplierFibonacciStep4)
							{
								bool isFib4 = false;
								int fa4 = 0, fb4 = 1;
								while (fb4 <= aux->i) { int fc4 = fa4 + fb4; fa4 = fb4; fb4 = fc4; if (fb4 == aux->i) isFib4 = true; }
								if (aux->i == 0 || aux->i == 1) isFib4 = true;
								if (!isFib4) val = 1.0f;
							}

							
							int icurve4 = fractal->transformCommon.multiplierInterpCurve4;
							if (icurve4 > 0 && val != 1.0f)
							{
								REAL dev4 = val - 1.0f;
								REAL tn4 = fabs(dev4);
								if (tn4 > 1.0f) tn4 = 1.0f;
								if (icurve4 == 1) tn4 = tn4 * tn4 * tn4;
								else if (icurve4 == 2) tn4 = tn4 * tn4 * (3.0f - 2.0f * tn4);
								else if (icurve4 == 3) tn4 = (1.0f - native_cos(tn4 * M_PI_F)) * 0.5f;
								val = 1.0f + (dev4 > 0 ? tn4 : -tn4);
							}
							REAL dq4 = fractal->transformCommon.multiplierDitherQuantize4;
							if (dq4 > 0.0f)
							{
								int dqseed4 = aux->i * 48271 + 4 * 16807;
								dqseed4 = (dqseed4 ^ (dqseed4 >> 15)) * 1103515245;
								REAL dither4 = ((REAL)(dqseed4 & 0xFFFF) / 65535.0f - 0.5f) * dq4;
								val = floor((val + dither4) / dq4 + 0.5f) * dq4;
							}
							if (fractal->transformCommon.multiplierComplexMag4)
							{
								REAL cmag4 = native_sqrt(z.x * z.x + z.y * z.y);
								if (cmag4 > 1e-12f) val = 1.0f + (val - 1.0f) * cmag4;
							}
							REAL pidx4 = fractal->transformCommon.multiplierPaletteIdxDrive4;
							if (pidx4 > 0.0f)
							{
								aux->color += (val - 1.0f) * pidx4 * 256.0f;
							}
							int tLayers4 = fractal->transformCommon.multiplierTurbulenceLayers4;
							if (tLayers4 > 1 && val != 1.0f)
							{
								REAL turbSum4 = val - 1.0f;
								REAL amp4 = 0.5f;
								for (int tl4 = 1; tl4 < tLayers4; tl4++)
								{
									int tseed4 = aux->i * 73856093 + tl4 * 19349663 + 4 * 83492791;
									tseed4 = (tseed4 ^ (tseed4 >> 13)) * 1274126177;
									tseed4 = tseed4 ^ (tseed4 >> 16);
									REAL tnoise4 = (REAL)(tseed4 & 0xFFFF) / 65535.0f - 0.5f;
									turbSum4 += tnoise4 * amp4 * (val - 1.0f);
									amp4 *= 0.5f;
								}
								val = 1.0f + turbSum4;
							}
							REAL kalAngle4 = fractal->transformCommon.multiplierKaleidoscopeBias4;
							if (kalAngle4 > 0.0f)
							{
								val = 1.0f + (val - 1.0f) * native_cos(kalAngle4 * val);
							}
							REAL phRand4 = fractal->transformCommon.multiplierPhaseRandomise4;
							if (phRand4 > 0.0f)
							{
								int phseed4 = (int)(z.x * 73856.0f + z.y * 19349.0f + z.z * 83492.0f) + 4;
								phseed4 = (phseed4 ^ (phseed4 >> 13)) * 1274126177;
								phseed4 = phseed4 ^ (phseed4 >> 16);
								REAL phJitter4 = ((REAL)(phseed4 & 0xFFFF) / 65535.0f - 0.5f) * phRand4;
								val = 1.0f + (val - 1.0f) * native_cos(phJitter4 * 2.0f * M_PI_F);
							}
							REAL plOff4 = fractal->transformCommon.multiplierPhaseLockOffset4;
							if (plOff4 != 0.0f)
							{
								val = 1.0f + (val - 1.0f) * native_cos(plOff4 * M_PI_F);
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
						REAL denom = native_powr(2.718281828f, freq) - 1.0f;
															val = 1.0f + (val - 1.0f) * (fabs(denom) > 1e-12f
																? (native_powr(2.718281828f, t * freq) - 1.0f) / denom
																: t);
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
						int seed = aux->i * 73856093 + (fractal->transformCommon.multiplierNoiseSeed5 > 0 ? fractal->transformCommon.multiplierNoiseSeed5 : 5) * 19349663;
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

							// Clip Drive (pre-gain)
							if (fractal->transformCommon.multiplierClipDrive5 != 1.0f)
							{
								REAL drv = fractal->transformCommon.multiplierClipDrive5;
								val = 1.0f + (val - 1.0f) * drv;
							}
							// Clip Rectify: 0=off, 1=half(clamp neg to 0), 2=full(abs)
							{
								int cr = fractal->transformCommon.multiplierClipRectify5;
								if (cr == 1 && val < 1.0f) val = 1.0f;
								else if (cr == 2) val = 1.0f + fabs(val - 1.0f);
							}
							// Clip Fold (wavefolder)
							if (fractal->transformCommon.multiplierClipFold5)
							{
								int folds = fractal->transformCommon.multiplierClipFoldCount5;
								if (folds < 1) folds = 1;
								REAL ceil = fractal->transformCommon.multiplierClipCeiling5;
								REAL flr = fractal->transformCommon.multiplierClipFloor5;
								for (int fi = 0; fi < folds; fi++)
								{
									if (val > ceil) val = 2.0f * ceil - val;
									if (val < flr) val = 2.0f * flr - val;
								}
							}
							// Clip Ceiling / Floor (hard clamp with asymmetry)
							if (!fractal->transformCommon.multiplierClipFold5)
							{
								REAL ceil = fractal->transformCommon.multiplierClipCeiling5;
								REAL flr = fractal->transformCommon.multiplierClipFloor5;
								REAL asym = fractal->transformCommon.multiplierClipAsymmetry5;
								ceil += asym;
								flr -= asym;
								REAL curve = fractal->transformCommon.multiplierClipCurve5;
								REAL knee = fractal->transformCommon.multiplierClipKnee5;
								if (curve > 0.0f || knee > 0.0f)
								{
									REAL k = fmax(knee, 0.001f);
									if (val > ceil - k)
									{
										REAL x = (val - (ceil - k)) / (2.0f * k);
										x = fmin(fmax(x, 0.0f), 1.0f);
										REAL sm = x * x * (3.0f - 2.0f * x);
										val = (ceil - k) + k * sm * (1.0f + curve);
										if (val > ceil) val = ceil;
									}
									if (val < flr + k)
									{
										REAL x = ((flr + k) - val) / (2.0f * k);
										x = fmin(fmax(x, 0.0f), 1.0f);
										REAL sm = x * x * (3.0f - 2.0f * x);
										val = (flr + k) - k * sm * (1.0f + curve);
										if (val < flr) val = flr;
									}
								}
								else
								{
									if (val > ceil) val = ceil;
									if (val < flr) val = flr;
								}
							}
							// Clip Mix (blend clipped/unclipped)
							if (fractal->transformCommon.multiplierClipMix5 < 1.0f)
							{
								REAL mx = fractal->transformCommon.multiplierClipMix5;
								val = 1.0f + mx * (val - 1.0f);
							}

							// === Inverse Processing ===
							{
								int doInverse = fractal->transformCommon.multiplierInverse5;
								if (fractal->transformCommon.multiplierInvOscillate5)
									doInverse = (aux->i % 2 == 0) ? doInverse : !doInverse;
								if (doInverse)
								{
									REAL origVal = val;
									REAL diff = val - 1.0f;
									REAL absDiff = fabs(diff);
									REAL rMin = fractal->transformCommon.multiplierInvRangeMin5;
									REAL rMax = fractal->transformCommon.multiplierInvRangeMax5;
									if (absDiff >= rMin && absDiff <= rMax)
									{
										REAL thr = fractal->transformCommon.multiplierInvThreshold5;
										if (absDiff >= thr)
										{
											REAL bias = fractal->transformCommon.multiplierInvBias5;
											REAL center = 1.0f + bias;
											int imode = fractal->transformCommon.multiplierInvMode5;
											if (imode == 0)
												val = center + (fabs(val - center) > 1e-15f ? (1.0f / (val - center)) : 1e15f);
											else if (imode == 1)
												val = center - (val - center);
											else if (imode == 2)
												val = center + (1.0f - fabs(val - center));
											else if (imode == 3)
												val = center - fabs(val - center) * ((val > center) ? 1.0f : -1.0f);
											REAL sm = fractal->transformCommon.multiplierInvSmooth5;
											if (sm > 0.0f)
											{
												REAL blend = fmin(absDiff / (thr + sm + 1e-15f), 1.0f);
												blend = blend * blend * (3.0f - 2.0f * blend);
												val = origVal + blend * (val - origVal);
											}
											REAL idcy = fractal->transformCommon.multiplierInvDecay5;
											if (idcy > 0.0f)
											{
												REAL rng = (REAL)(fractal->transformCommon.multiplierStopIter5 - fractal->transformCommon.multiplierStartIter5);
												REAL td = (rng > 0.0f) ? (REAL)(aux->i - fractal->transformCommon.multiplierStartIter5) / rng : 0.0f;
												REAL fade = native_exp(-idcy * td * 5.0f);
												val = origVal + fade * (val - origVal);
											}
											REAL str = fractal->transformCommon.multiplierInvStrength5;
											if (str < 1.0f)
												val = origVal + str * (val - origVal);
										}
									}
								}
							}

				
							// Burst / Falloff / Wrap / Conditional for slot 5
							int burstLen5 = fractal->transformCommon.multiplierBurstLength5;
							int burstGap5 = fractal->transformCommon.multiplierBurstGap5;
							if (burstLen5 > 0 && burstGap5 > 0)
							{
								int cycle5 = burstLen5 + burstGap5;
								int phase5 = (aux->i - fractal->transformCommon.multiplierStartIter5) % cycle5;
								if (phase5 >= burstLen5) val = 1.0f;
							}
							REAL sphFall5 = fractal->transformCommon.multiplierSphericalFalloff5;
							if (sphFall5 > 0.0f)
							{
								REAL dist5 = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								REAL falloff5 = native_exp(-sphFall5 * dist5);
								val = 1.0f + (val - 1.0f) * falloff5;
							}
							REAL wrapR5 = fractal->transformCommon.multiplierWrapRange5;
							if (wrapR5 > 0.0f)
							{
								REAL shifted5 = val - 1.0f;
								shifted5 = fmod(shifted5, wrapR5);
								if (shifted5 < 0.0f) shifted5 += wrapR5;
								val = 1.0f + shifted5;
							}
							int condMode5 = fractal->transformCommon.multiplierConditionalMode5;
							if (condMode5 == 1 && z.x < 0.0f) val = 1.0f;
							else if (condMode5 == 2 && z.x >= 0.0f) val = 1.0f;
							else if (condMode5 == 3)
							{
								REAL condDist5 = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								if (condDist5 < fractal->transformCommon.multiplierConditionalThreshold5) val = 1.0f;
							}

														// Accumulate for slot 5
							if (fractal->transformCommon.multiplierAccumulate5 && prevMultVal != 1.0f)
								val = 1.0f + (val - 1.0f) + (prevMultVal - 1.0f);

							
							// === Top-10 params for slot 5 ===
							if (fractal->transformCommon.multiplierSlotDisable5) { val = 1.0f; }
							else {
							REAL cullDist5 = fractal->transformCommon.multiplierDistCull5;
							if (cullDist5 > 0.0f && (z.x * z.x + z.y * z.y + z.z * z.z) > cullDist5 * cullDist5)
								val = 1.0f;
							else {

							int rampIn5 = fractal->transformCommon.multiplierRampIn5;
							if (rampIn5 > 0)
							{
								int elapsed5 = aux->i - fractal->transformCommon.multiplierStartIter5;
								if (elapsed5 < rampIn5)
								{
									REAL t5 = (REAL)elapsed5 / (REAL)rampIn5;
									t5 = t5 * t5 * (3.0f - 2.0f * t5);
									val = 1.0f + (val - 1.0f) * t5;
								}
							}
							int rampOut5 = fractal->transformCommon.multiplierRampOut5;
							if (rampOut5 > 0)
							{
								int remaining5 = fractal->transformCommon.multiplierStopIter5 - aux->i;
								if (remaining5 < rampOut5 && remaining5 >= 0)
								{
									REAL t5 = (REAL)remaining5 / (REAL)rampOut5;
									t5 = t5 * t5 * (3.0f - 2.0f * t5);
									val = 1.0f + (val - 1.0f) * t5;
								}
							}
							REAL cylBias5 = fractal->transformCommon.multiplierCylindricalBias5;
							if (cylBias5 > 0.0f)
							{
								REAL cylDist5 = native_sqrt(z.x * z.x + z.y * z.y);
								REAL cylFade5 = native_exp(-cylBias5 * cylDist5);
								val = 1.0f + (val - 1.0f) * cylFade5;
							}
							REAL softExp5 = fractal->transformCommon.multiplierSoftExp5;
							if (softExp5 > 0.0f && val < 1.0f)
							{
								REAL v5 = val - 1.0f;
								val = 1.0f + softExp5 * (native_exp(v5 / fmax(softExp5, 1e-12f)) - 1.0f);
							}
							REAL slewRate5 = fractal->transformCommon.multiplierSlewRate5;
							if (slewRate5 > 0.0f && prevMultVal != 1.0f)
							{
								REAL delta5 = val - prevMultVal;
								if (fabs(delta5) > slewRate5)
									val = prevMultVal + (delta5 > 0.0f ? slewRate5 : -slewRate5);
							}
							REAL hyst5 = fractal->transformCommon.multiplierHysteresis5;
							if (hyst5 > 0.0f)
							{
								REAL hystDist5 = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								REAL hystThresh5 = fractal->transformCommon.multiplierThreshold5;
								if (hystDist5 > hystThresh5 - hyst5 * 0.5f && hystDist5 < hystThresh5 + hyst5 * 0.5f)
								{
									REAL blend5 = (hystDist5 - (hystThresh5 - hyst5 * 0.5f)) / hyst5;
									val = 1.0f + (val - 1.0f) * blend5;
								}
							}
							REAL aaStep5 = fractal->transformCommon.multiplierAntiAlias5;
							if (aaStep5 > 0.0f)
							{
								REAL aaDist5 = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								REAL aaThresh5 = fractal->transformCommon.multiplierThreshold5;
								REAL aaT5 = (aaDist5 - (aaThresh5 - aaStep5)) / (2.0f * aaStep5);
								aaT5 = fmax(0.0f, fmin(1.0f, aaT5));
								aaT5 = aaT5 * aaT5 * (3.0f - 2.0f * aaT5);
								val = 1.0f + (val - 1.0f) * aaT5;
							}
							REAL neutralEps5 = fractal->transformCommon.multiplierNeutralEps5;
							if (neutralEps5 > 0.0f && fabs(val - 1.0f) < neutralEps5)
								val = 1.0f;

							} // end else distCull
							} // end else slotDisable

							
							REAL gradDir5 = fractal->transformCommon.multiplierGradientDir5;
							if (gradDir5 != 0.0f)
							{
								REAL r5g = native_sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								if (r5g > 1e-12f)
								{
									REAL cosW5 = (z.x * native_cos(gradDir5) + z.y * native_sin(gradDir5)) / r5g;
									REAL blend5 = (cosW5 + 1.0f) * 0.5f;
									val = 1.0f + (val - 1.0f) * blend5;
								}
							}
							REAL voroScale5 = fractal->transformCommon.multiplierVoronoiScale5;
							if (voroScale5 > 0.0f)
							{
								REAL vx5 = z.x * voroScale5;
								REAL vy5 = z.y * voroScale5;
								REAL vz5 = z.z * voroScale5;
								REAL fx5 = vx5 - floor(vx5) - 0.5f;
								REAL fy5 = vy5 - floor(vy5) - 0.5f;
								REAL fz5 = vz5 - floor(vz5) - 0.5f;
								REAL vDist5 = native_sqrt(fx5 * fx5 + fy5 * fy5 + fz5 * fz5);
								val = 1.0f + (val - 1.0f) * fmin(vDist5 * 2.0f, 1.0f);
							}
							REAL torusR5 = fractal->transformCommon.multiplierToroidalR5;
							if (torusR5 > 0.0f)
							{
								REAL xyR5 = native_sqrt(z.x * z.x + z.y * z.y);
								REAL tDist5 = native_sqrt((xyR5 - torusR5) * (xyR5 - torusR5) + z.z * z.z);
								REAL tFade5 = native_exp(-tDist5);
								val = 1.0f + (val - 1.0f) * tFade5;
							}
							int angStripes5 = fractal->transformCommon.multiplierAngularStripes5;
							if (angStripes5 > 0)
							{
								REAL angle5 = atan2(z.y, z.x);
								int sector5 = (int)floor((angle5 + M_PI_F) / (2.0f * M_PI_F) * (REAL)angStripes5);
								if (sector5 % 2 != 0) val = 1.0f;
							}
							REAL geoP5 = fractal->transformCommon.multiplierGeoProgression5;
							if (geoP5 != 1.0f)
							{
								int elapsed5g = aux->i - fractal->transformCommon.multiplierStartIter5;
								if (elapsed5g > 0)
									val = 1.0f + (val - 1.0f) * native_powr(geoP5, (REAL)elapsed5g);
							}
							int parity5 = fractal->transformCommon.multiplierParityGate5;
							if (parity5 == 1 && aux->i % 2 == 0) val = 1.0f;
							if (parity5 == 2 && aux->i % 2 != 0) val = 1.0f;
							if (fractal->transformCommon.multiplierFibonacciStep5)
							{
								bool isFib5 = false;
								int fa5 = 0, fb5 = 1;
								while (fb5 <= aux->i) { int fc5 = fa5 + fb5; fa5 = fb5; fb5 = fc5; if (fb5 == aux->i) isFib5 = true; }
								if (aux->i == 0 || aux->i == 1) isFib5 = true;
								if (!isFib5) val = 1.0f;
							}

							
							int icurve5 = fractal->transformCommon.multiplierInterpCurve5;
							if (icurve5 > 0 && val != 1.0f)
							{
								REAL dev5 = val - 1.0f;
								REAL tn5 = fabs(dev5);
								if (tn5 > 1.0f) tn5 = 1.0f;
								if (icurve5 == 1) tn5 = tn5 * tn5 * tn5;
								else if (icurve5 == 2) tn5 = tn5 * tn5 * (3.0f - 2.0f * tn5);
								else if (icurve5 == 3) tn5 = (1.0f - native_cos(tn5 * M_PI_F)) * 0.5f;
								val = 1.0f + (dev5 > 0 ? tn5 : -tn5);
							}
							REAL dq5 = fractal->transformCommon.multiplierDitherQuantize5;
							if (dq5 > 0.0f)
							{
								int dqseed5 = aux->i * 48271 + 5 * 16807;
								dqseed5 = (dqseed5 ^ (dqseed5 >> 15)) * 1103515245;
								REAL dither5 = ((REAL)(dqseed5 & 0xFFFF) / 65535.0f - 0.5f) * dq5;
								val = floor((val + dither5) / dq5 + 0.5f) * dq5;
							}
							if (fractal->transformCommon.multiplierComplexMag5)
							{
								REAL cmag5 = native_sqrt(z.x * z.x + z.y * z.y);
								if (cmag5 > 1e-12f) val = 1.0f + (val - 1.0f) * cmag5;
							}
							REAL pidx5 = fractal->transformCommon.multiplierPaletteIdxDrive5;
							if (pidx5 > 0.0f)
							{
								aux->color += (val - 1.0f) * pidx5 * 256.0f;
							}
							int tLayers5 = fractal->transformCommon.multiplierTurbulenceLayers5;
							if (tLayers5 > 1 && val != 1.0f)
							{
								REAL turbSum5 = val - 1.0f;
								REAL amp5 = 0.5f;
								for (int tl5 = 1; tl5 < tLayers5; tl5++)
								{
									int tseed5 = aux->i * 73856093 + tl5 * 19349663 + 5 * 83492791;
									tseed5 = (tseed5 ^ (tseed5 >> 13)) * 1274126177;
									tseed5 = tseed5 ^ (tseed5 >> 16);
									REAL tnoise5 = (REAL)(tseed5 & 0xFFFF) / 65535.0f - 0.5f;
									turbSum5 += tnoise5 * amp5 * (val - 1.0f);
									amp5 *= 0.5f;
								}
								val = 1.0f + turbSum5;
							}
							REAL kalAngle5 = fractal->transformCommon.multiplierKaleidoscopeBias5;
							if (kalAngle5 > 0.0f)
							{
								val = 1.0f + (val - 1.0f) * native_cos(kalAngle5 * val);
							}
							REAL phRand5 = fractal->transformCommon.multiplierPhaseRandomise5;
							if (phRand5 > 0.0f)
							{
								int phseed5 = (int)(z.x * 73856.0f + z.y * 19349.0f + z.z * 83492.0f) + 5;
								phseed5 = (phseed5 ^ (phseed5 >> 13)) * 1274126177;
								phseed5 = phseed5 ^ (phseed5 >> 16);
								REAL phJitter5 = ((REAL)(phseed5 & 0xFFFF) / 65535.0f - 0.5f) * phRand5;
								val = 1.0f + (val - 1.0f) * native_cos(phJitter5 * 2.0f * M_PI_F);
							}
							REAL plOff5 = fractal->transformCommon.multiplierPhaseLockOffset5;
							if (plOff5 != 0.0f)
							{
								val = 1.0f + (val - 1.0f) * native_cos(plOff5 * M_PI_F);
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
