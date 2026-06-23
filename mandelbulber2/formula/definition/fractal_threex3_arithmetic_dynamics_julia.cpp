/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Rekenkundige dynamica Julia.
 * Math: z = phi(z) + c met phi morfisme over getallenlichaam
 */

#include "all_fractal_definitions.h"

cFractalThreex3ArithmeticDynamicsJulia::cFractalThreex3ArithmeticDynamicsJulia() : cAbstractFractal()
{
	nameInComboBox = "3x3 V34 Arithmetic Dynamics Julia";
	internalName = "threex3_arithmetic_dynamics_julia";
	internalID = fractal::threex3ArithmeticDynamicsJulia;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3ArithmeticDynamicsJulia::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Arithmetic Dynamics Julia: z = phi(z) + c met phi morfisme over getallenlichaam
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	// Arithmetic dynamics: discrete floor modulation
	double gridScale = fractal->transformCommon.scale1;
	if (gridScale < 0.01) gridScale = 1.0;
	double fx = floor(z.x * gridScale + 0.5) / gridScale;
	double fy = floor(z.y * gridScale + 0.5) / gridScale;
	double discreteShift = fractal->transformCommon.offset0 * (fx * fx + fy * fy);
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp + discreteShift * 0.01;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;

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
						double denom = exp(freq) - 1.0;
															val = 1.0 + (val - 1.0) * (fabs(denom) > 1e-12
																? (exp(t * freq) - 1.0) / denom
																: t);
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
						int seed = aux.i * 73856093 + (fractal->transformCommon.multiplierNoiseSeed1 > 0 ? fractal->transformCommon.multiplierNoiseSeed1 : 1) * 19349663;
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

							// Decay
							if (fractal->transformCommon.multiplierDecay1 > 0.0)
							{
								double dcy = fractal->transformCommon.multiplierDecay1;
								double rng = (double)(fractal->transformCommon.multiplierStopIter1 - fractal->transformCommon.multiplierStartIter1);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter1) / rng : 0.0;
								val = 1.0 + (val - 1.0) * exp(-dcy * td * 5.0);
							}
							// Exponent
							if (fractal->transformCommon.multiplierExponent1 != 1.0)
							{
								double ep = fractal->transformCommon.multiplierExponent1;
								double sgn = (val >= 1.0) ? 1.0 : -1.0;
								val = 1.0 + sgn * pow(fabs(val - 1.0) + 1e-30, ep);
							}
							// Offset
							val += fractal->transformCommon.multiplierOffset1;

							// Delay
							if (fractal->transformCommon.multiplierDelay1 > 0
								&& aux.i < fractal->transformCommon.multiplierStartIter1 + fractal->transformCommon.multiplierDelay1)
								val = 1.0;
							// Iteration Modulo
							if (fractal->transformCommon.multiplierIterModulo1 > 1
								&& ((aux.i - fractal->transformCommon.multiplierStartIter1) % fractal->transformCommon.multiplierIterModulo1) != 0)
								val = 1.0;
							// Attack envelope
							if (fractal->transformCommon.multiplierAttack1 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter1 - fractal->transformCommon.multiplierStartIter1);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter1) / rng : 1.0;
								double att = fractal->transformCommon.multiplierAttack1;
								if (td < att) val = 1.0 + (val - 1.0) * (td / att);
							}
							// Release envelope
							if (fractal->transformCommon.multiplierRelease1 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter1 - fractal->transformCommon.multiplierStartIter1);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter1) / rng : 1.0;
								double rel = fractal->transformCommon.multiplierRelease1;
								if (td > (1.0 - rel)) val = 1.0 + (val - 1.0) * ((1.0 - td) / rel);
							}
							// Feedback
							if (fractal->transformCommon.multiplierFeedback1 > 0.0)
							{
								double fb = fractal->transformCommon.multiplierFeedback1;
								val = 1.0 + (val - 1.0) * (1.0 - fb) + (prevMultVal - 1.0) * fb;
							}
							// Harmonics
							if (fractal->transformCommon.multiplierHarmonics1 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter1 - fractal->transformCommon.multiplierStartIter1);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter1) / rng : 0.0;
								double hrm = fractal->transformCommon.multiplierHarmonics1;
								double frq = fractal->transformCommon.multiplierFrequency1;
								val += hrm * sin(4.0 * M_PI * frq * td) * fabs(val - 1.0);
							}
							// Pulse Width
							if (fractal->transformCommon.multiplierPulseWidth1 != 0.5)
							{
								double pw = fractal->transformCommon.multiplierPulseWidth1;
								double diff = val - 1.0;
								double sgn = (diff >= 0.0) ? 1.0 : -1.0;
								double mg = fabs(diff) + 1e-30;
								val = 1.0 + sgn * pow(mg, 1.0 / (2.0 * fmax(pw, 0.01)));
							}
							// Mirror
							if (fractal->transformCommon.multiplierMirror1 && val < 1.0)
								val = 2.0 - val;
							// Quantize
							if (fractal->transformCommon.multiplierQuantize1 > 0)
							{
								double step = 1.0 / (double)fractal->transformCommon.multiplierQuantize1;
								val = 1.0 + floor((val - 1.0) / step + 0.5) * step;
							}
							// Symmetry Break
							if (fractal->transformCommon.multiplierSymmetryBreak1 != 0.0)
							{
								double sb = fractal->transformCommon.multiplierSymmetryBreak1;
								double diff = val - 1.0;
								val = (diff > 0.0) ? 1.0 + diff * (1.0 + sb) : 1.0 + diff * (1.0 - sb);
							}
							// Clamp
							if (val < fractal->transformCommon.multiplierClampMin1) val = fractal->transformCommon.multiplierClampMin1;
							if (val > fractal->transformCommon.multiplierClampMax1) val = fractal->transformCommon.multiplierClampMax1;
							// Soft Clip
							if (fractal->transformCommon.multiplierSoftClip1 > 0.0)
							{
								double sc = fractal->transformCommon.multiplierSoftClip1;
								double diff = val - 1.0;
								val = 1.0 + diff / (1.0 + sc * fabs(diff));
							}
							// Radial Falloff
							if (fractal->transformCommon.multiplierRadialFalloff1 > 0.0)
							{
								double rf = fractal->transformCommon.multiplierRadialFalloff1;
								double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0 + (val - 1.0) * exp(-rf * r);
							}
							// Angular Bias
							if (fractal->transformCommon.multiplierAngularBias1 != 0.0)
							{
								double ab = fractal->transformCommon.multiplierAngularBias1;
								double angle = atan2(z.y, z.x);
								double bias = 0.5 + 0.5 * cos(angle - ab * M_PI / 180.0);
								val = 1.0 + (val - 1.0) * bias;
							}
							// Polar Mode
							if (fractal->transformCommon.multiplierPolarMode1)
							{
								double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0 + (val - 1.0) * (1.0 + 0.5 * sin(r));
							}
							// Cross-axis Coupling
							if (fractal->transformCommon.multiplierCrossCoupling1 > 0.0)
							{
								double cc = fractal->transformCommon.multiplierCrossCoupling1;
								double leak = (val - 1.0) * cc * 0.1;
								z.x += leak * z.y;
								z.y += leak * z.z;
								z.z += leak * z.x;
							}
							// Noise addition
							if (fractal->transformCommon.multiplierNoiseSeed1 > 0)
							{
								int seed = fractal->transformCommon.multiplierNoiseSeed1;
								int oct = fractal->transformCommon.multiplierNoiseOctaves1;
								double nv = 0.0;
								double amp = 1.0;
								for (int o = 0; o < oct; o++)
								{
									double ph = (double)(aux.i * 1237 + seed * 7919 + o * 4621);
									nv += amp * sin(ph * 0.0031415);
									amp *= 0.5;
								}
								val += nv * fabs(val - 1.0) * 0.3;
							}
							// Blend Mode: 0=normal, 1=shrink-only, 2=grow-only, 3=abs, 4=smooth
							{
								int bm = fractal->transformCommon.multiplierBlendMode1;
								if (bm == 1 && val > 1.0) val = 1.0;
								else if (bm == 2 && val < 1.0) val = 1.0;
								else if (bm == 3) val = 1.0 + fabs(val - 1.0);
								else if (bm == 4) { double sv = fmin(fmax((val - 0.5) * 1.0, 0.0), 1.0); val = 0.5 + sv * sv * (3.0 - 2.0 * sv); }
							}

							// Clip Drive (pre-gain)
							if (fractal->transformCommon.multiplierClipDrive1 != 1.0)
							{
								double drv = fractal->transformCommon.multiplierClipDrive1;
								val = 1.0 + (val - 1.0) * drv;
							}
							// Clip Rectify: 0=off, 1=half(clamp neg to 0), 2=full(abs)
							{
								int cr = fractal->transformCommon.multiplierClipRectify1;
								if (cr == 1 && val < 1.0) val = 1.0;
								else if (cr == 2) val = 1.0 + fabs(val - 1.0);
							}
							// Clip Fold (wavefolder)
							if (fractal->transformCommon.multiplierClipFold1)
							{
								int folds = fractal->transformCommon.multiplierClipFoldCount1;
								if (folds < 1) folds = 1;
								double ceil = fractal->transformCommon.multiplierClipCeiling1;
								double flr = fractal->transformCommon.multiplierClipFloor1;
								for (int fi = 0; fi < folds; fi++)
								{
									if (val > ceil) val = 2.0 * ceil - val;
									if (val < flr) val = 2.0 * flr - val;
								}
							}
							// Clip Ceiling / Floor (hard clamp with asymmetry)
							if (!fractal->transformCommon.multiplierClipFold1)
							{
								double ceil = fractal->transformCommon.multiplierClipCeiling1;
								double flr = fractal->transformCommon.multiplierClipFloor1;
								double asym = fractal->transformCommon.multiplierClipAsymmetry1;
								ceil += asym;
								flr -= asym;
								// Clip Curve (soft knee)
								double curve = fractal->transformCommon.multiplierClipCurve1;
								double knee = fractal->transformCommon.multiplierClipKnee1;
								if (curve > 0.0 || knee > 0.0)
								{
									double k = fmax(knee, 0.001);
									if (val > ceil - k)
									{
										double x = (val - (ceil - k)) / (2.0 * k);
										x = fmin(fmax(x, 0.0), 1.0);
										double sm = x * x * (3.0 - 2.0 * x);
										val = (ceil - k) + k * sm * (1.0 + curve);
										if (val > ceil) val = ceil;
									}
									if (val < flr + k)
									{
										double x = ((flr + k) - val) / (2.0 * k);
										x = fmin(fmax(x, 0.0), 1.0);
										double sm = x * x * (3.0 - 2.0 * x);
										val = (flr + k) - k * sm * (1.0 + curve);
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
							if (fractal->transformCommon.multiplierClipMix1 < 1.0)
							{
								double mx = fractal->transformCommon.multiplierClipMix1;
								// val is already clipped; recover original from drive
								// approximate: mix toward 1.0 (neutral)
								val = 1.0 + mx * (val - 1.0);
							}

							// === Inverse Processing ===
							// Inv Oscillate: alternate normal/inverse per iteration
							{
								bool doInverse = fractal->transformCommon.multiplierInverse1;
								if (fractal->transformCommon.multiplierInvOscillate1)
									doInverse = (aux.i % 2 == 0) ? doInverse : !doInverse;
								if (doInverse)
								{
									double origVal = val;
									double diff = val - 1.0;
									double absDiff = fabs(diff);
									// Inv Range: only invert within range
									double rMin = fractal->transformCommon.multiplierInvRangeMin1;
									double rMax = fractal->transformCommon.multiplierInvRangeMax1;
									if (absDiff >= rMin && absDiff <= rMax)
									{
										// Inv Threshold: only invert if above threshold
										double thr = fractal->transformCommon.multiplierInvThreshold1;
										if (absDiff >= thr)
										{
											double bias = fractal->transformCommon.multiplierInvBias1;
											double center = 1.0 + bias;
											int imode = fractal->transformCommon.multiplierInvMode1;
											if (imode == 0) // Reciprocal
												val = center + (fabs(val - center) > 1e-15 ? (1.0 / (val - center)) : 1e15);
											else if (imode == 1) // Negate
												val = center - (val - center);
											else if (imode == 2) // Complement
												val = center + (1.0 - fabs(val - center));
											else if (imode == 3) // Flip sign
												val = center - fabs(val - center) * ((val > center) ? 1.0 : -1.0);
											// Inv Smooth
											double sm = fractal->transformCommon.multiplierInvSmooth1;
											if (sm > 0.0)
											{
												double blend = fmin(absDiff / (thr + sm + 1e-15), 1.0);
												blend = blend * blend * (3.0 - 2.0 * blend);
												val = origVal + blend * (val - origVal);
											}
											// Inv Decay
											double idcy = fractal->transformCommon.multiplierInvDecay1;
											if (idcy > 0.0)
											{
												double rng = (double)(fractal->transformCommon.multiplierStopIter1 - fractal->transformCommon.multiplierStartIter1);
												double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter1) / rng : 0.0;
												double fade = exp(-idcy * td * 5.0);
												val = origVal + fade * (val - origVal);
											}
											// Inv Strength
											double str = fractal->transformCommon.multiplierInvStrength1;
											if (str < 1.0)
												val = origVal + str * (val - origVal);
										}
									}
									// Inv Axis: 0=all(done), 1/2/3=restore non-target axes later
								}
							}

				
							// Burst / Falloff / Wrap / Conditional for slot 1
							int burstLen1 = fractal->transformCommon.multiplierBurstLength1;
							int burstGap1 = fractal->transformCommon.multiplierBurstGap1;
							if (burstLen1 > 0 && burstGap1 > 0)
							{
								int cycle1 = burstLen1 + burstGap1;
								int phase1 = (aux.i - fractal->transformCommon.multiplierStartIter1) % cycle1;
								if (phase1 >= burstLen1) val = 1.0;
							}
							double sphFall1 = fractal->transformCommon.multiplierSphericalFalloff1;
							if (sphFall1 > 0.0)
							{
								double dist1 = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								double falloff1 = exp(-sphFall1 * dist1);
								val = 1.0 + (val - 1.0) * falloff1;
							}
							double wrapR1 = fractal->transformCommon.multiplierWrapRange1;
							if (wrapR1 > 0.0)
							{
								double shifted1 = val - 1.0;
								shifted1 = fmod(shifted1, wrapR1);
								if (shifted1 < 0.0) shifted1 += wrapR1;
								val = 1.0 + shifted1;
							}
							int condMode1 = fractal->transformCommon.multiplierConditionalMode1;
							if (condMode1 == 1 && z.x < 0.0) val = 1.0;
							else if (condMode1 == 2 && z.x >= 0.0) val = 1.0;
							else if (condMode1 == 3)
							{
								double condDist1 = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								if (condDist1 < fractal->transformCommon.multiplierConditionalThreshold1) val = 1.0;
							}

														// Accumulate for slot 1
							if (fractal->transformCommon.multiplierAccumulate1 && prevMultVal != 1.0)
								val = 1.0 + (val - 1.0) + (prevMultVal - 1.0);

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
						double denom = exp(freq) - 1.0;
															val = 1.0 + (val - 1.0) * (fabs(denom) > 1e-12
																? (exp(t * freq) - 1.0) / denom
																: t);
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
						int seed = aux.i * 73856093 + (fractal->transformCommon.multiplierNoiseSeed2 > 0 ? fractal->transformCommon.multiplierNoiseSeed2 : 2) * 19349663;
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

							// Decay
							if (fractal->transformCommon.multiplierDecay2 > 0.0)
							{
								double dcy = fractal->transformCommon.multiplierDecay2;
								double rng = (double)(fractal->transformCommon.multiplierStopIter2 - fractal->transformCommon.multiplierStartIter2);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter2) / rng : 0.0;
								val = 1.0 + (val - 1.0) * exp(-dcy * td * 5.0);
							}
							// Exponent
							if (fractal->transformCommon.multiplierExponent2 != 1.0)
							{
								double ep = fractal->transformCommon.multiplierExponent2;
								double sgn = (val >= 1.0) ? 1.0 : -1.0;
								val = 1.0 + sgn * pow(fabs(val - 1.0) + 1e-30, ep);
							}
							// Offset
							val += fractal->transformCommon.multiplierOffset2;

							// Delay
							if (fractal->transformCommon.multiplierDelay2 > 0
								&& aux.i < fractal->transformCommon.multiplierStartIter2 + fractal->transformCommon.multiplierDelay2)
								val = 1.0;
							// Iteration Modulo
							if (fractal->transformCommon.multiplierIterModulo2 > 1
								&& ((aux.i - fractal->transformCommon.multiplierStartIter2) % fractal->transformCommon.multiplierIterModulo2) != 0)
								val = 1.0;
							// Attack envelope
							if (fractal->transformCommon.multiplierAttack2 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter2 - fractal->transformCommon.multiplierStartIter2);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter2) / rng : 1.0;
								double att = fractal->transformCommon.multiplierAttack2;
								if (td < att) val = 1.0 + (val - 1.0) * (td / att);
							}
							// Release envelope
							if (fractal->transformCommon.multiplierRelease2 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter2 - fractal->transformCommon.multiplierStartIter2);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter2) / rng : 1.0;
								double rel = fractal->transformCommon.multiplierRelease2;
								if (td > (1.0 - rel)) val = 1.0 + (val - 1.0) * ((1.0 - td) / rel);
							}
							// Feedback
							if (fractal->transformCommon.multiplierFeedback2 > 0.0)
							{
								double fb = fractal->transformCommon.multiplierFeedback2;
								val = 1.0 + (val - 1.0) * (1.0 - fb) + (prevMultVal - 1.0) * fb;
							}
							// Harmonics
							if (fractal->transformCommon.multiplierHarmonics2 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter2 - fractal->transformCommon.multiplierStartIter2);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter2) / rng : 0.0;
								double hrm = fractal->transformCommon.multiplierHarmonics2;
								double frq = fractal->transformCommon.multiplierFrequency2;
								val += hrm * sin(4.0 * M_PI * frq * td) * fabs(val - 1.0);
							}
							// Pulse Width
							if (fractal->transformCommon.multiplierPulseWidth2 != 0.5)
							{
								double pw = fractal->transformCommon.multiplierPulseWidth2;
								double diff = val - 1.0;
								double sgn = (diff >= 0.0) ? 1.0 : -1.0;
								double mg = fabs(diff) + 1e-30;
								val = 1.0 + sgn * pow(mg, 1.0 / (2.0 * fmax(pw, 0.01)));
							}
							// Mirror
							if (fractal->transformCommon.multiplierMirror2 && val < 1.0)
								val = 2.0 - val;
							// Quantize
							if (fractal->transformCommon.multiplierQuantize2 > 0)
							{
								double step = 1.0 / (double)fractal->transformCommon.multiplierQuantize2;
								val = 1.0 + floor((val - 1.0) / step + 0.5) * step;
							}
							// Symmetry Break
							if (fractal->transformCommon.multiplierSymmetryBreak2 != 0.0)
							{
								double sb = fractal->transformCommon.multiplierSymmetryBreak2;
								double diff = val - 1.0;
								val = (diff > 0.0) ? 1.0 + diff * (1.0 + sb) : 1.0 + diff * (1.0 - sb);
							}
							// Clamp
							if (val < fractal->transformCommon.multiplierClampMin2) val = fractal->transformCommon.multiplierClampMin2;
							if (val > fractal->transformCommon.multiplierClampMax2) val = fractal->transformCommon.multiplierClampMax2;
							// Soft Clip
							if (fractal->transformCommon.multiplierSoftClip2 > 0.0)
							{
								double sc = fractal->transformCommon.multiplierSoftClip2;
								double diff = val - 1.0;
								val = 1.0 + diff / (1.0 + sc * fabs(diff));
							}
							// Radial Falloff
							if (fractal->transformCommon.multiplierRadialFalloff2 > 0.0)
							{
								double rf = fractal->transformCommon.multiplierRadialFalloff2;
								double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0 + (val - 1.0) * exp(-rf * r);
							}
							// Angular Bias
							if (fractal->transformCommon.multiplierAngularBias2 != 0.0)
							{
								double ab = fractal->transformCommon.multiplierAngularBias2;
								double angle = atan2(z.y, z.x);
								double bias = 0.5 + 0.5 * cos(angle - ab * M_PI / 180.0);
								val = 1.0 + (val - 1.0) * bias;
							}
							// Polar Mode
							if (fractal->transformCommon.multiplierPolarMode2)
							{
								double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0 + (val - 1.0) * (1.0 + 0.5 * sin(r));
							}
							// Cross-axis Coupling
							if (fractal->transformCommon.multiplierCrossCoupling2 > 0.0)
							{
								double cc = fractal->transformCommon.multiplierCrossCoupling2;
								double leak = (val - 1.0) * cc * 0.1;
								z.x += leak * z.y;
								z.y += leak * z.z;
								z.z += leak * z.x;
							}
							// Noise addition
							if (fractal->transformCommon.multiplierNoiseSeed2 > 0)
							{
								int seed = fractal->transformCommon.multiplierNoiseSeed2;
								int oct = fractal->transformCommon.multiplierNoiseOctaves2;
								double nv = 0.0;
								double amp = 1.0;
								for (int o = 0; o < oct; o++)
								{
									double ph = (double)(aux.i * 1237 + seed * 7919 + o * 4621);
									nv += amp * sin(ph * 0.0031415);
									amp *= 0.5;
								}
								val += nv * fabs(val - 1.0) * 0.3;
							}
							// Blend Mode: 0=normal, 1=shrink-only, 2=grow-only, 3=abs, 4=smooth
							{
								int bm = fractal->transformCommon.multiplierBlendMode2;
								if (bm == 1 && val > 1.0) val = 1.0;
								else if (bm == 2 && val < 1.0) val = 1.0;
								else if (bm == 3) val = 1.0 + fabs(val - 1.0);
								else if (bm == 4) { double sv = fmin(fmax((val - 0.5) * 1.0, 0.0), 1.0); val = 0.5 + sv * sv * (3.0 - 2.0 * sv); }
							}

							// Clip Drive (pre-gain)
							if (fractal->transformCommon.multiplierClipDrive2 != 1.0)
							{
								double drv = fractal->transformCommon.multiplierClipDrive2;
								val = 1.0 + (val - 1.0) * drv;
							}
							// Clip Rectify: 0=off, 1=half(clamp neg to 0), 2=full(abs)
							{
								int cr = fractal->transformCommon.multiplierClipRectify2;
								if (cr == 1 && val < 1.0) val = 1.0;
								else if (cr == 2) val = 1.0 + fabs(val - 1.0);
							}
							// Clip Fold (wavefolder)
							if (fractal->transformCommon.multiplierClipFold2)
							{
								int folds = fractal->transformCommon.multiplierClipFoldCount2;
								if (folds < 1) folds = 1;
								double ceil = fractal->transformCommon.multiplierClipCeiling2;
								double flr = fractal->transformCommon.multiplierClipFloor2;
								for (int fi = 0; fi < folds; fi++)
								{
									if (val > ceil) val = 2.0 * ceil - val;
									if (val < flr) val = 2.0 * flr - val;
								}
							}
							// Clip Ceiling / Floor (hard clamp with asymmetry)
							if (!fractal->transformCommon.multiplierClipFold2)
							{
								double ceil = fractal->transformCommon.multiplierClipCeiling2;
								double flr = fractal->transformCommon.multiplierClipFloor2;
								double asym = fractal->transformCommon.multiplierClipAsymmetry2;
								ceil += asym;
								flr -= asym;
								// Clip Curve (soft knee)
								double curve = fractal->transformCommon.multiplierClipCurve2;
								double knee = fractal->transformCommon.multiplierClipKnee2;
								if (curve > 0.0 || knee > 0.0)
								{
									double k = fmax(knee, 0.001);
									if (val > ceil - k)
									{
										double x = (val - (ceil - k)) / (2.0 * k);
										x = fmin(fmax(x, 0.0), 1.0);
										double sm = x * x * (3.0 - 2.0 * x);
										val = (ceil - k) + k * sm * (1.0 + curve);
										if (val > ceil) val = ceil;
									}
									if (val < flr + k)
									{
										double x = ((flr + k) - val) / (2.0 * k);
										x = fmin(fmax(x, 0.0), 1.0);
										double sm = x * x * (3.0 - 2.0 * x);
										val = (flr + k) - k * sm * (1.0 + curve);
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
							if (fractal->transformCommon.multiplierClipMix2 < 1.0)
							{
								double mx = fractal->transformCommon.multiplierClipMix2;
								// val is already clipped; recover original from drive
								// approximate: mix toward 1.0 (neutral)
								val = 1.0 + mx * (val - 1.0);
							}

							// === Inverse Processing ===
							// Inv Oscillate: alternate normal/inverse per iteration
							{
								bool doInverse = fractal->transformCommon.multiplierInverse2;
								if (fractal->transformCommon.multiplierInvOscillate2)
									doInverse = (aux.i % 2 == 0) ? doInverse : !doInverse;
								if (doInverse)
								{
									double origVal = val;
									double diff = val - 1.0;
									double absDiff = fabs(diff);
									// Inv Range: only invert within range
									double rMin = fractal->transformCommon.multiplierInvRangeMin2;
									double rMax = fractal->transformCommon.multiplierInvRangeMax2;
									if (absDiff >= rMin && absDiff <= rMax)
									{
										// Inv Threshold: only invert if above threshold
										double thr = fractal->transformCommon.multiplierInvThreshold2;
										if (absDiff >= thr)
										{
											double bias = fractal->transformCommon.multiplierInvBias2;
											double center = 1.0 + bias;
											int imode = fractal->transformCommon.multiplierInvMode2;
											if (imode == 0) // Reciprocal
												val = center + (fabs(val - center) > 1e-15 ? (1.0 / (val - center)) : 1e15);
											else if (imode == 1) // Negate
												val = center - (val - center);
											else if (imode == 2) // Complement
												val = center + (1.0 - fabs(val - center));
											else if (imode == 3) // Flip sign
												val = center - fabs(val - center) * ((val > center) ? 1.0 : -1.0);
											// Inv Smooth
											double sm = fractal->transformCommon.multiplierInvSmooth2;
											if (sm > 0.0)
											{
												double blend = fmin(absDiff / (thr + sm + 1e-15), 1.0);
												blend = blend * blend * (3.0 - 2.0 * blend);
												val = origVal + blend * (val - origVal);
											}
											// Inv Decay
											double idcy = fractal->transformCommon.multiplierInvDecay2;
											if (idcy > 0.0)
											{
												double rng = (double)(fractal->transformCommon.multiplierStopIter2 - fractal->transformCommon.multiplierStartIter2);
												double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter2) / rng : 0.0;
												double fade = exp(-idcy * td * 5.0);
												val = origVal + fade * (val - origVal);
											}
											// Inv Strength
											double str = fractal->transformCommon.multiplierInvStrength2;
											if (str < 1.0)
												val = origVal + str * (val - origVal);
										}
									}
									// Inv Axis: 0=all(done), 1/2/3=restore non-target axes later
								}
							}

				
							// Burst / Falloff / Wrap / Conditional for slot 2
							int burstLen2 = fractal->transformCommon.multiplierBurstLength2;
							int burstGap2 = fractal->transformCommon.multiplierBurstGap2;
							if (burstLen2 > 0 && burstGap2 > 0)
							{
								int cycle2 = burstLen2 + burstGap2;
								int phase2 = (aux.i - fractal->transformCommon.multiplierStartIter2) % cycle2;
								if (phase2 >= burstLen2) val = 1.0;
							}
							double sphFall2 = fractal->transformCommon.multiplierSphericalFalloff2;
							if (sphFall2 > 0.0)
							{
								double dist2 = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								double falloff2 = exp(-sphFall2 * dist2);
								val = 1.0 + (val - 1.0) * falloff2;
							}
							double wrapR2 = fractal->transformCommon.multiplierWrapRange2;
							if (wrapR2 > 0.0)
							{
								double shifted2 = val - 1.0;
								shifted2 = fmod(shifted2, wrapR2);
								if (shifted2 < 0.0) shifted2 += wrapR2;
								val = 1.0 + shifted2;
							}
							int condMode2 = fractal->transformCommon.multiplierConditionalMode2;
							if (condMode2 == 1 && z.x < 0.0) val = 1.0;
							else if (condMode2 == 2 && z.x >= 0.0) val = 1.0;
							else if (condMode2 == 3)
							{
								double condDist2 = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								if (condDist2 < fractal->transformCommon.multiplierConditionalThreshold2) val = 1.0;
							}

														// Accumulate for slot 2
							if (fractal->transformCommon.multiplierAccumulate2 && prevMultVal != 1.0)
								val = 1.0 + (val - 1.0) + (prevMultVal - 1.0);

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
						double denom = exp(freq) - 1.0;
															val = 1.0 + (val - 1.0) * (fabs(denom) > 1e-12
																? (exp(t * freq) - 1.0) / denom
																: t);
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
						int seed = aux.i * 73856093 + (fractal->transformCommon.multiplierNoiseSeed3 > 0 ? fractal->transformCommon.multiplierNoiseSeed3 : 3) * 19349663;
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

							// Decay
							if (fractal->transformCommon.multiplierDecay3 > 0.0)
							{
								double dcy = fractal->transformCommon.multiplierDecay3;
								double rng = (double)(fractal->transformCommon.multiplierStopIter3 - fractal->transformCommon.multiplierStartIter3);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter3) / rng : 0.0;
								val = 1.0 + (val - 1.0) * exp(-dcy * td * 5.0);
							}
							// Exponent
							if (fractal->transformCommon.multiplierExponent3 != 1.0)
							{
								double ep = fractal->transformCommon.multiplierExponent3;
								double sgn = (val >= 1.0) ? 1.0 : -1.0;
								val = 1.0 + sgn * pow(fabs(val - 1.0) + 1e-30, ep);
							}
							// Offset
							val += fractal->transformCommon.multiplierOffset3;

							// Delay
							if (fractal->transformCommon.multiplierDelay3 > 0
								&& aux.i < fractal->transformCommon.multiplierStartIter3 + fractal->transformCommon.multiplierDelay3)
								val = 1.0;
							// Iteration Modulo
							if (fractal->transformCommon.multiplierIterModulo3 > 1
								&& ((aux.i - fractal->transformCommon.multiplierStartIter3) % fractal->transformCommon.multiplierIterModulo3) != 0)
								val = 1.0;
							// Attack envelope
							if (fractal->transformCommon.multiplierAttack3 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter3 - fractal->transformCommon.multiplierStartIter3);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter3) / rng : 1.0;
								double att = fractal->transformCommon.multiplierAttack3;
								if (td < att) val = 1.0 + (val - 1.0) * (td / att);
							}
							// Release envelope
							if (fractal->transformCommon.multiplierRelease3 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter3 - fractal->transformCommon.multiplierStartIter3);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter3) / rng : 1.0;
								double rel = fractal->transformCommon.multiplierRelease3;
								if (td > (1.0 - rel)) val = 1.0 + (val - 1.0) * ((1.0 - td) / rel);
							}
							// Feedback
							if (fractal->transformCommon.multiplierFeedback3 > 0.0)
							{
								double fb = fractal->transformCommon.multiplierFeedback3;
								val = 1.0 + (val - 1.0) * (1.0 - fb) + (prevMultVal - 1.0) * fb;
							}
							// Harmonics
							if (fractal->transformCommon.multiplierHarmonics3 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter3 - fractal->transformCommon.multiplierStartIter3);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter3) / rng : 0.0;
								double hrm = fractal->transformCommon.multiplierHarmonics3;
								double frq = fractal->transformCommon.multiplierFrequency3;
								val += hrm * sin(4.0 * M_PI * frq * td) * fabs(val - 1.0);
							}
							// Pulse Width
							if (fractal->transformCommon.multiplierPulseWidth3 != 0.5)
							{
								double pw = fractal->transformCommon.multiplierPulseWidth3;
								double diff = val - 1.0;
								double sgn = (diff >= 0.0) ? 1.0 : -1.0;
								double mg = fabs(diff) + 1e-30;
								val = 1.0 + sgn * pow(mg, 1.0 / (2.0 * fmax(pw, 0.01)));
							}
							// Mirror
							if (fractal->transformCommon.multiplierMirror3 && val < 1.0)
								val = 2.0 - val;
							// Quantize
							if (fractal->transformCommon.multiplierQuantize3 > 0)
							{
								double step = 1.0 / (double)fractal->transformCommon.multiplierQuantize3;
								val = 1.0 + floor((val - 1.0) / step + 0.5) * step;
							}
							// Symmetry Break
							if (fractal->transformCommon.multiplierSymmetryBreak3 != 0.0)
							{
								double sb = fractal->transformCommon.multiplierSymmetryBreak3;
								double diff = val - 1.0;
								val = (diff > 0.0) ? 1.0 + diff * (1.0 + sb) : 1.0 + diff * (1.0 - sb);
							}
							// Clamp
							if (val < fractal->transformCommon.multiplierClampMin3) val = fractal->transformCommon.multiplierClampMin3;
							if (val > fractal->transformCommon.multiplierClampMax3) val = fractal->transformCommon.multiplierClampMax3;
							// Soft Clip
							if (fractal->transformCommon.multiplierSoftClip3 > 0.0)
							{
								double sc = fractal->transformCommon.multiplierSoftClip3;
								double diff = val - 1.0;
								val = 1.0 + diff / (1.0 + sc * fabs(diff));
							}
							// Radial Falloff
							if (fractal->transformCommon.multiplierRadialFalloff3 > 0.0)
							{
								double rf = fractal->transformCommon.multiplierRadialFalloff3;
								double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0 + (val - 1.0) * exp(-rf * r);
							}
							// Angular Bias
							if (fractal->transformCommon.multiplierAngularBias3 != 0.0)
							{
								double ab = fractal->transformCommon.multiplierAngularBias3;
								double angle = atan2(z.y, z.x);
								double bias = 0.5 + 0.5 * cos(angle - ab * M_PI / 180.0);
								val = 1.0 + (val - 1.0) * bias;
							}
							// Polar Mode
							if (fractal->transformCommon.multiplierPolarMode3)
							{
								double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0 + (val - 1.0) * (1.0 + 0.5 * sin(r));
							}
							// Cross-axis Coupling
							if (fractal->transformCommon.multiplierCrossCoupling3 > 0.0)
							{
								double cc = fractal->transformCommon.multiplierCrossCoupling3;
								double leak = (val - 1.0) * cc * 0.1;
								z.x += leak * z.y;
								z.y += leak * z.z;
								z.z += leak * z.x;
							}
							// Noise addition
							if (fractal->transformCommon.multiplierNoiseSeed3 > 0)
							{
								int seed = fractal->transformCommon.multiplierNoiseSeed3;
								int oct = fractal->transformCommon.multiplierNoiseOctaves3;
								double nv = 0.0;
								double amp = 1.0;
								for (int o = 0; o < oct; o++)
								{
									double ph = (double)(aux.i * 1237 + seed * 7919 + o * 4621);
									nv += amp * sin(ph * 0.0031415);
									amp *= 0.5;
								}
								val += nv * fabs(val - 1.0) * 0.3;
							}
							// Blend Mode: 0=normal, 1=shrink-only, 2=grow-only, 3=abs, 4=smooth
							{
								int bm = fractal->transformCommon.multiplierBlendMode3;
								if (bm == 1 && val > 1.0) val = 1.0;
								else if (bm == 2 && val < 1.0) val = 1.0;
								else if (bm == 3) val = 1.0 + fabs(val - 1.0);
								else if (bm == 4) { double sv = fmin(fmax((val - 0.5) * 1.0, 0.0), 1.0); val = 0.5 + sv * sv * (3.0 - 2.0 * sv); }
							}

							// Clip Drive (pre-gain)
							if (fractal->transformCommon.multiplierClipDrive3 != 1.0)
							{
								double drv = fractal->transformCommon.multiplierClipDrive3;
								val = 1.0 + (val - 1.0) * drv;
							}
							// Clip Rectify: 0=off, 1=half(clamp neg to 0), 2=full(abs)
							{
								int cr = fractal->transformCommon.multiplierClipRectify3;
								if (cr == 1 && val < 1.0) val = 1.0;
								else if (cr == 2) val = 1.0 + fabs(val - 1.0);
							}
							// Clip Fold (wavefolder)
							if (fractal->transformCommon.multiplierClipFold3)
							{
								int folds = fractal->transformCommon.multiplierClipFoldCount3;
								if (folds < 1) folds = 1;
								double ceil = fractal->transformCommon.multiplierClipCeiling3;
								double flr = fractal->transformCommon.multiplierClipFloor3;
								for (int fi = 0; fi < folds; fi++)
								{
									if (val > ceil) val = 2.0 * ceil - val;
									if (val < flr) val = 2.0 * flr - val;
								}
							}
							// Clip Ceiling / Floor (hard clamp with asymmetry)
							if (!fractal->transformCommon.multiplierClipFold3)
							{
								double ceil = fractal->transformCommon.multiplierClipCeiling3;
								double flr = fractal->transformCommon.multiplierClipFloor3;
								double asym = fractal->transformCommon.multiplierClipAsymmetry3;
								ceil += asym;
								flr -= asym;
								// Clip Curve (soft knee)
								double curve = fractal->transformCommon.multiplierClipCurve3;
								double knee = fractal->transformCommon.multiplierClipKnee3;
								if (curve > 0.0 || knee > 0.0)
								{
									double k = fmax(knee, 0.001);
									if (val > ceil - k)
									{
										double x = (val - (ceil - k)) / (2.0 * k);
										x = fmin(fmax(x, 0.0), 1.0);
										double sm = x * x * (3.0 - 2.0 * x);
										val = (ceil - k) + k * sm * (1.0 + curve);
										if (val > ceil) val = ceil;
									}
									if (val < flr + k)
									{
										double x = ((flr + k) - val) / (2.0 * k);
										x = fmin(fmax(x, 0.0), 1.0);
										double sm = x * x * (3.0 - 2.0 * x);
										val = (flr + k) - k * sm * (1.0 + curve);
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
							if (fractal->transformCommon.multiplierClipMix3 < 1.0)
							{
								double mx = fractal->transformCommon.multiplierClipMix3;
								// val is already clipped; recover original from drive
								// approximate: mix toward 1.0 (neutral)
								val = 1.0 + mx * (val - 1.0);
							}

							// === Inverse Processing ===
							// Inv Oscillate: alternate normal/inverse per iteration
							{
								bool doInverse = fractal->transformCommon.multiplierInverse3;
								if (fractal->transformCommon.multiplierInvOscillate3)
									doInverse = (aux.i % 2 == 0) ? doInverse : !doInverse;
								if (doInverse)
								{
									double origVal = val;
									double diff = val - 1.0;
									double absDiff = fabs(diff);
									// Inv Range: only invert within range
									double rMin = fractal->transformCommon.multiplierInvRangeMin3;
									double rMax = fractal->transformCommon.multiplierInvRangeMax3;
									if (absDiff >= rMin && absDiff <= rMax)
									{
										// Inv Threshold: only invert if above threshold
										double thr = fractal->transformCommon.multiplierInvThreshold3;
										if (absDiff >= thr)
										{
											double bias = fractal->transformCommon.multiplierInvBias3;
											double center = 1.0 + bias;
											int imode = fractal->transformCommon.multiplierInvMode3;
											if (imode == 0) // Reciprocal
												val = center + (fabs(val - center) > 1e-15 ? (1.0 / (val - center)) : 1e15);
											else if (imode == 1) // Negate
												val = center - (val - center);
											else if (imode == 2) // Complement
												val = center + (1.0 - fabs(val - center));
											else if (imode == 3) // Flip sign
												val = center - fabs(val - center) * ((val > center) ? 1.0 : -1.0);
											// Inv Smooth
											double sm = fractal->transformCommon.multiplierInvSmooth3;
											if (sm > 0.0)
											{
												double blend = fmin(absDiff / (thr + sm + 1e-15), 1.0);
												blend = blend * blend * (3.0 - 2.0 * blend);
												val = origVal + blend * (val - origVal);
											}
											// Inv Decay
											double idcy = fractal->transformCommon.multiplierInvDecay3;
											if (idcy > 0.0)
											{
												double rng = (double)(fractal->transformCommon.multiplierStopIter3 - fractal->transformCommon.multiplierStartIter3);
												double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter3) / rng : 0.0;
												double fade = exp(-idcy * td * 5.0);
												val = origVal + fade * (val - origVal);
											}
											// Inv Strength
											double str = fractal->transformCommon.multiplierInvStrength3;
											if (str < 1.0)
												val = origVal + str * (val - origVal);
										}
									}
									// Inv Axis: 0=all(done), 1/2/3=restore non-target axes later
								}
							}

				
							// Burst / Falloff / Wrap / Conditional for slot 3
							int burstLen3 = fractal->transformCommon.multiplierBurstLength3;
							int burstGap3 = fractal->transformCommon.multiplierBurstGap3;
							if (burstLen3 > 0 && burstGap3 > 0)
							{
								int cycle3 = burstLen3 + burstGap3;
								int phase3 = (aux.i - fractal->transformCommon.multiplierStartIter3) % cycle3;
								if (phase3 >= burstLen3) val = 1.0;
							}
							double sphFall3 = fractal->transformCommon.multiplierSphericalFalloff3;
							if (sphFall3 > 0.0)
							{
								double dist3 = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								double falloff3 = exp(-sphFall3 * dist3);
								val = 1.0 + (val - 1.0) * falloff3;
							}
							double wrapR3 = fractal->transformCommon.multiplierWrapRange3;
							if (wrapR3 > 0.0)
							{
								double shifted3 = val - 1.0;
								shifted3 = fmod(shifted3, wrapR3);
								if (shifted3 < 0.0) shifted3 += wrapR3;
								val = 1.0 + shifted3;
							}
							int condMode3 = fractal->transformCommon.multiplierConditionalMode3;
							if (condMode3 == 1 && z.x < 0.0) val = 1.0;
							else if (condMode3 == 2 && z.x >= 0.0) val = 1.0;
							else if (condMode3 == 3)
							{
								double condDist3 = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								if (condDist3 < fractal->transformCommon.multiplierConditionalThreshold3) val = 1.0;
							}

														// Accumulate for slot 3
							if (fractal->transformCommon.multiplierAccumulate3 && prevMultVal != 1.0)
								val = 1.0 + (val - 1.0) + (prevMultVal - 1.0);

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
						double denom = exp(freq) - 1.0;
															val = 1.0 + (val - 1.0) * (fabs(denom) > 1e-12
																? (exp(t * freq) - 1.0) / denom
																: t);
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
						int seed = aux.i * 73856093 + (fractal->transformCommon.multiplierNoiseSeed4 > 0 ? fractal->transformCommon.multiplierNoiseSeed4 : 4) * 19349663;
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

							// Decay
							if (fractal->transformCommon.multiplierDecay4 > 0.0)
							{
								double dcy = fractal->transformCommon.multiplierDecay4;
								double rng = (double)(fractal->transformCommon.multiplierStopIter4 - fractal->transformCommon.multiplierStartIter4);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter4) / rng : 0.0;
								val = 1.0 + (val - 1.0) * exp(-dcy * td * 5.0);
							}
							// Exponent
							if (fractal->transformCommon.multiplierExponent4 != 1.0)
							{
								double ep = fractal->transformCommon.multiplierExponent4;
								double sgn = (val >= 1.0) ? 1.0 : -1.0;
								val = 1.0 + sgn * pow(fabs(val - 1.0) + 1e-30, ep);
							}
							// Offset
							val += fractal->transformCommon.multiplierOffset4;

							// Delay
							if (fractal->transformCommon.multiplierDelay4 > 0
								&& aux.i < fractal->transformCommon.multiplierStartIter4 + fractal->transformCommon.multiplierDelay4)
								val = 1.0;
							// Iteration Modulo
							if (fractal->transformCommon.multiplierIterModulo4 > 1
								&& ((aux.i - fractal->transformCommon.multiplierStartIter4) % fractal->transformCommon.multiplierIterModulo4) != 0)
								val = 1.0;
							// Attack envelope
							if (fractal->transformCommon.multiplierAttack4 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter4 - fractal->transformCommon.multiplierStartIter4);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter4) / rng : 1.0;
								double att = fractal->transformCommon.multiplierAttack4;
								if (td < att) val = 1.0 + (val - 1.0) * (td / att);
							}
							// Release envelope
							if (fractal->transformCommon.multiplierRelease4 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter4 - fractal->transformCommon.multiplierStartIter4);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter4) / rng : 1.0;
								double rel = fractal->transformCommon.multiplierRelease4;
								if (td > (1.0 - rel)) val = 1.0 + (val - 1.0) * ((1.0 - td) / rel);
							}
							// Feedback
							if (fractal->transformCommon.multiplierFeedback4 > 0.0)
							{
								double fb = fractal->transformCommon.multiplierFeedback4;
								val = 1.0 + (val - 1.0) * (1.0 - fb) + (prevMultVal - 1.0) * fb;
							}
							// Harmonics
							if (fractal->transformCommon.multiplierHarmonics4 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter4 - fractal->transformCommon.multiplierStartIter4);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter4) / rng : 0.0;
								double hrm = fractal->transformCommon.multiplierHarmonics4;
								double frq = fractal->transformCommon.multiplierFrequency4;
								val += hrm * sin(4.0 * M_PI * frq * td) * fabs(val - 1.0);
							}
							// Pulse Width
							if (fractal->transformCommon.multiplierPulseWidth4 != 0.5)
							{
								double pw = fractal->transformCommon.multiplierPulseWidth4;
								double diff = val - 1.0;
								double sgn = (diff >= 0.0) ? 1.0 : -1.0;
								double mg = fabs(diff) + 1e-30;
								val = 1.0 + sgn * pow(mg, 1.0 / (2.0 * fmax(pw, 0.01)));
							}
							// Mirror
							if (fractal->transformCommon.multiplierMirror4 && val < 1.0)
								val = 2.0 - val;
							// Quantize
							if (fractal->transformCommon.multiplierQuantize4 > 0)
							{
								double step = 1.0 / (double)fractal->transformCommon.multiplierQuantize4;
								val = 1.0 + floor((val - 1.0) / step + 0.5) * step;
							}
							// Symmetry Break
							if (fractal->transformCommon.multiplierSymmetryBreak4 != 0.0)
							{
								double sb = fractal->transformCommon.multiplierSymmetryBreak4;
								double diff = val - 1.0;
								val = (diff > 0.0) ? 1.0 + diff * (1.0 + sb) : 1.0 + diff * (1.0 - sb);
							}
							// Clamp
							if (val < fractal->transformCommon.multiplierClampMin4) val = fractal->transformCommon.multiplierClampMin4;
							if (val > fractal->transformCommon.multiplierClampMax4) val = fractal->transformCommon.multiplierClampMax4;
							// Soft Clip
							if (fractal->transformCommon.multiplierSoftClip4 > 0.0)
							{
								double sc = fractal->transformCommon.multiplierSoftClip4;
								double diff = val - 1.0;
								val = 1.0 + diff / (1.0 + sc * fabs(diff));
							}
							// Radial Falloff
							if (fractal->transformCommon.multiplierRadialFalloff4 > 0.0)
							{
								double rf = fractal->transformCommon.multiplierRadialFalloff4;
								double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0 + (val - 1.0) * exp(-rf * r);
							}
							// Angular Bias
							if (fractal->transformCommon.multiplierAngularBias4 != 0.0)
							{
								double ab = fractal->transformCommon.multiplierAngularBias4;
								double angle = atan2(z.y, z.x);
								double bias = 0.5 + 0.5 * cos(angle - ab * M_PI / 180.0);
								val = 1.0 + (val - 1.0) * bias;
							}
							// Polar Mode
							if (fractal->transformCommon.multiplierPolarMode4)
							{
								double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0 + (val - 1.0) * (1.0 + 0.5 * sin(r));
							}
							// Cross-axis Coupling
							if (fractal->transformCommon.multiplierCrossCoupling4 > 0.0)
							{
								double cc = fractal->transformCommon.multiplierCrossCoupling4;
								double leak = (val - 1.0) * cc * 0.1;
								z.x += leak * z.y;
								z.y += leak * z.z;
								z.z += leak * z.x;
							}
							// Noise addition
							if (fractal->transformCommon.multiplierNoiseSeed4 > 0)
							{
								int seed = fractal->transformCommon.multiplierNoiseSeed4;
								int oct = fractal->transformCommon.multiplierNoiseOctaves4;
								double nv = 0.0;
								double amp = 1.0;
								for (int o = 0; o < oct; o++)
								{
									double ph = (double)(aux.i * 1237 + seed * 7919 + o * 4621);
									nv += amp * sin(ph * 0.0031415);
									amp *= 0.5;
								}
								val += nv * fabs(val - 1.0) * 0.3;
							}
							// Blend Mode: 0=normal, 1=shrink-only, 2=grow-only, 3=abs, 4=smooth
							{
								int bm = fractal->transformCommon.multiplierBlendMode4;
								if (bm == 1 && val > 1.0) val = 1.0;
								else if (bm == 2 && val < 1.0) val = 1.0;
								else if (bm == 3) val = 1.0 + fabs(val - 1.0);
								else if (bm == 4) { double sv = fmin(fmax((val - 0.5) * 1.0, 0.0), 1.0); val = 0.5 + sv * sv * (3.0 - 2.0 * sv); }
							}

							// Clip Drive (pre-gain)
							if (fractal->transformCommon.multiplierClipDrive4 != 1.0)
							{
								double drv = fractal->transformCommon.multiplierClipDrive4;
								val = 1.0 + (val - 1.0) * drv;
							}
							// Clip Rectify: 0=off, 1=half(clamp neg to 0), 2=full(abs)
							{
								int cr = fractal->transformCommon.multiplierClipRectify4;
								if (cr == 1 && val < 1.0) val = 1.0;
								else if (cr == 2) val = 1.0 + fabs(val - 1.0);
							}
							// Clip Fold (wavefolder)
							if (fractal->transformCommon.multiplierClipFold4)
							{
								int folds = fractal->transformCommon.multiplierClipFoldCount4;
								if (folds < 1) folds = 1;
								double ceil = fractal->transformCommon.multiplierClipCeiling4;
								double flr = fractal->transformCommon.multiplierClipFloor4;
								for (int fi = 0; fi < folds; fi++)
								{
									if (val > ceil) val = 2.0 * ceil - val;
									if (val < flr) val = 2.0 * flr - val;
								}
							}
							// Clip Ceiling / Floor (hard clamp with asymmetry)
							if (!fractal->transformCommon.multiplierClipFold4)
							{
								double ceil = fractal->transformCommon.multiplierClipCeiling4;
								double flr = fractal->transformCommon.multiplierClipFloor4;
								double asym = fractal->transformCommon.multiplierClipAsymmetry4;
								ceil += asym;
								flr -= asym;
								// Clip Curve (soft knee)
								double curve = fractal->transformCommon.multiplierClipCurve4;
								double knee = fractal->transformCommon.multiplierClipKnee4;
								if (curve > 0.0 || knee > 0.0)
								{
									double k = fmax(knee, 0.001);
									if (val > ceil - k)
									{
										double x = (val - (ceil - k)) / (2.0 * k);
										x = fmin(fmax(x, 0.0), 1.0);
										double sm = x * x * (3.0 - 2.0 * x);
										val = (ceil - k) + k * sm * (1.0 + curve);
										if (val > ceil) val = ceil;
									}
									if (val < flr + k)
									{
										double x = ((flr + k) - val) / (2.0 * k);
										x = fmin(fmax(x, 0.0), 1.0);
										double sm = x * x * (3.0 - 2.0 * x);
										val = (flr + k) - k * sm * (1.0 + curve);
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
							if (fractal->transformCommon.multiplierClipMix4 < 1.0)
							{
								double mx = fractal->transformCommon.multiplierClipMix4;
								// val is already clipped; recover original from drive
								// approximate: mix toward 1.0 (neutral)
								val = 1.0 + mx * (val - 1.0);
							}

							// === Inverse Processing ===
							// Inv Oscillate: alternate normal/inverse per iteration
							{
								bool doInverse = fractal->transformCommon.multiplierInverse4;
								if (fractal->transformCommon.multiplierInvOscillate4)
									doInverse = (aux.i % 2 == 0) ? doInverse : !doInverse;
								if (doInverse)
								{
									double origVal = val;
									double diff = val - 1.0;
									double absDiff = fabs(diff);
									// Inv Range: only invert within range
									double rMin = fractal->transformCommon.multiplierInvRangeMin4;
									double rMax = fractal->transformCommon.multiplierInvRangeMax4;
									if (absDiff >= rMin && absDiff <= rMax)
									{
										// Inv Threshold: only invert if above threshold
										double thr = fractal->transformCommon.multiplierInvThreshold4;
										if (absDiff >= thr)
										{
											double bias = fractal->transformCommon.multiplierInvBias4;
											double center = 1.0 + bias;
											int imode = fractal->transformCommon.multiplierInvMode4;
											if (imode == 0) // Reciprocal
												val = center + (fabs(val - center) > 1e-15 ? (1.0 / (val - center)) : 1e15);
											else if (imode == 1) // Negate
												val = center - (val - center);
											else if (imode == 2) // Complement
												val = center + (1.0 - fabs(val - center));
											else if (imode == 3) // Flip sign
												val = center - fabs(val - center) * ((val > center) ? 1.0 : -1.0);
											// Inv Smooth
											double sm = fractal->transformCommon.multiplierInvSmooth4;
											if (sm > 0.0)
											{
												double blend = fmin(absDiff / (thr + sm + 1e-15), 1.0);
												blend = blend * blend * (3.0 - 2.0 * blend);
												val = origVal + blend * (val - origVal);
											}
											// Inv Decay
											double idcy = fractal->transformCommon.multiplierInvDecay4;
											if (idcy > 0.0)
											{
												double rng = (double)(fractal->transformCommon.multiplierStopIter4 - fractal->transformCommon.multiplierStartIter4);
												double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter4) / rng : 0.0;
												double fade = exp(-idcy * td * 5.0);
												val = origVal + fade * (val - origVal);
											}
											// Inv Strength
											double str = fractal->transformCommon.multiplierInvStrength4;
											if (str < 1.0)
												val = origVal + str * (val - origVal);
										}
									}
									// Inv Axis: 0=all(done), 1/2/3=restore non-target axes later
								}
							}

				
							// Burst / Falloff / Wrap / Conditional for slot 4
							int burstLen4 = fractal->transformCommon.multiplierBurstLength4;
							int burstGap4 = fractal->transformCommon.multiplierBurstGap4;
							if (burstLen4 > 0 && burstGap4 > 0)
							{
								int cycle4 = burstLen4 + burstGap4;
								int phase4 = (aux.i - fractal->transformCommon.multiplierStartIter4) % cycle4;
								if (phase4 >= burstLen4) val = 1.0;
							}
							double sphFall4 = fractal->transformCommon.multiplierSphericalFalloff4;
							if (sphFall4 > 0.0)
							{
								double dist4 = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								double falloff4 = exp(-sphFall4 * dist4);
								val = 1.0 + (val - 1.0) * falloff4;
							}
							double wrapR4 = fractal->transformCommon.multiplierWrapRange4;
							if (wrapR4 > 0.0)
							{
								double shifted4 = val - 1.0;
								shifted4 = fmod(shifted4, wrapR4);
								if (shifted4 < 0.0) shifted4 += wrapR4;
								val = 1.0 + shifted4;
							}
							int condMode4 = fractal->transformCommon.multiplierConditionalMode4;
							if (condMode4 == 1 && z.x < 0.0) val = 1.0;
							else if (condMode4 == 2 && z.x >= 0.0) val = 1.0;
							else if (condMode4 == 3)
							{
								double condDist4 = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								if (condDist4 < fractal->transformCommon.multiplierConditionalThreshold4) val = 1.0;
							}

														// Accumulate for slot 4
							if (fractal->transformCommon.multiplierAccumulate4 && prevMultVal != 1.0)
								val = 1.0 + (val - 1.0) + (prevMultVal - 1.0);

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
						double denom = exp(freq) - 1.0;
															val = 1.0 + (val - 1.0) * (fabs(denom) > 1e-12
																? (exp(t * freq) - 1.0) / denom
																: t);
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
						int seed = aux.i * 73856093 + (fractal->transformCommon.multiplierNoiseSeed5 > 0 ? fractal->transformCommon.multiplierNoiseSeed5 : 5) * 19349663;
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

							// Decay
							if (fractal->transformCommon.multiplierDecay5 > 0.0)
							{
								double dcy = fractal->transformCommon.multiplierDecay5;
								double rng = (double)(fractal->transformCommon.multiplierStopIter5 - fractal->transformCommon.multiplierStartIter5);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter5) / rng : 0.0;
								val = 1.0 + (val - 1.0) * exp(-dcy * td * 5.0);
							}
							// Exponent
							if (fractal->transformCommon.multiplierExponent5 != 1.0)
							{
								double ep = fractal->transformCommon.multiplierExponent5;
								double sgn = (val >= 1.0) ? 1.0 : -1.0;
								val = 1.0 + sgn * pow(fabs(val - 1.0) + 1e-30, ep);
							}
							// Offset
							val += fractal->transformCommon.multiplierOffset5;

							// Delay
							if (fractal->transformCommon.multiplierDelay5 > 0
								&& aux.i < fractal->transformCommon.multiplierStartIter5 + fractal->transformCommon.multiplierDelay5)
								val = 1.0;
							// Iteration Modulo
							if (fractal->transformCommon.multiplierIterModulo5 > 1
								&& ((aux.i - fractal->transformCommon.multiplierStartIter5) % fractal->transformCommon.multiplierIterModulo5) != 0)
								val = 1.0;
							// Attack envelope
							if (fractal->transformCommon.multiplierAttack5 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter5 - fractal->transformCommon.multiplierStartIter5);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter5) / rng : 1.0;
								double att = fractal->transformCommon.multiplierAttack5;
								if (td < att) val = 1.0 + (val - 1.0) * (td / att);
							}
							// Release envelope
							if (fractal->transformCommon.multiplierRelease5 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter5 - fractal->transformCommon.multiplierStartIter5);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter5) / rng : 1.0;
								double rel = fractal->transformCommon.multiplierRelease5;
								if (td > (1.0 - rel)) val = 1.0 + (val - 1.0) * ((1.0 - td) / rel);
							}
							// Feedback
							if (fractal->transformCommon.multiplierFeedback5 > 0.0)
							{
								double fb = fractal->transformCommon.multiplierFeedback5;
								val = 1.0 + (val - 1.0) * (1.0 - fb) + (prevMultVal - 1.0) * fb;
							}
							// Harmonics
							if (fractal->transformCommon.multiplierHarmonics5 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter5 - fractal->transformCommon.multiplierStartIter5);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter5) / rng : 0.0;
								double hrm = fractal->transformCommon.multiplierHarmonics5;
								double frq = fractal->transformCommon.multiplierFrequency5;
								val += hrm * sin(4.0 * M_PI * frq * td) * fabs(val - 1.0);
							}
							// Pulse Width
							if (fractal->transformCommon.multiplierPulseWidth5 != 0.5)
							{
								double pw = fractal->transformCommon.multiplierPulseWidth5;
								double diff = val - 1.0;
								double sgn = (diff >= 0.0) ? 1.0 : -1.0;
								double mg = fabs(diff) + 1e-30;
								val = 1.0 + sgn * pow(mg, 1.0 / (2.0 * fmax(pw, 0.01)));
							}
							// Mirror
							if (fractal->transformCommon.multiplierMirror5 && val < 1.0)
								val = 2.0 - val;
							// Quantize
							if (fractal->transformCommon.multiplierQuantize5 > 0)
							{
								double step = 1.0 / (double)fractal->transformCommon.multiplierQuantize5;
								val = 1.0 + floor((val - 1.0) / step + 0.5) * step;
							}
							// Symmetry Break
							if (fractal->transformCommon.multiplierSymmetryBreak5 != 0.0)
							{
								double sb = fractal->transformCommon.multiplierSymmetryBreak5;
								double diff = val - 1.0;
								val = (diff > 0.0) ? 1.0 + diff * (1.0 + sb) : 1.0 + diff * (1.0 - sb);
							}
							// Clamp
							if (val < fractal->transformCommon.multiplierClampMin5) val = fractal->transformCommon.multiplierClampMin5;
							if (val > fractal->transformCommon.multiplierClampMax5) val = fractal->transformCommon.multiplierClampMax5;
							// Soft Clip
							if (fractal->transformCommon.multiplierSoftClip5 > 0.0)
							{
								double sc = fractal->transformCommon.multiplierSoftClip5;
								double diff = val - 1.0;
								val = 1.0 + diff / (1.0 + sc * fabs(diff));
							}
							// Radial Falloff
							if (fractal->transformCommon.multiplierRadialFalloff5 > 0.0)
							{
								double rf = fractal->transformCommon.multiplierRadialFalloff5;
								double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0 + (val - 1.0) * exp(-rf * r);
							}
							// Angular Bias
							if (fractal->transformCommon.multiplierAngularBias5 != 0.0)
							{
								double ab = fractal->transformCommon.multiplierAngularBias5;
								double angle = atan2(z.y, z.x);
								double bias = 0.5 + 0.5 * cos(angle - ab * M_PI / 180.0);
								val = 1.0 + (val - 1.0) * bias;
							}
							// Polar Mode
							if (fractal->transformCommon.multiplierPolarMode5)
							{
								double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0 + (val - 1.0) * (1.0 + 0.5 * sin(r));
							}
							// Cross-axis Coupling
							if (fractal->transformCommon.multiplierCrossCoupling5 > 0.0)
							{
								double cc = fractal->transformCommon.multiplierCrossCoupling5;
								double leak = (val - 1.0) * cc * 0.1;
								z.x += leak * z.y;
								z.y += leak * z.z;
								z.z += leak * z.x;
							}
							// Noise addition
							if (fractal->transformCommon.multiplierNoiseSeed5 > 0)
							{
								int seed = fractal->transformCommon.multiplierNoiseSeed5;
								int oct = fractal->transformCommon.multiplierNoiseOctaves5;
								double nv = 0.0;
								double amp = 1.0;
								for (int o = 0; o < oct; o++)
								{
									double ph = (double)(aux.i * 1237 + seed * 7919 + o * 4621);
									nv += amp * sin(ph * 0.0031415);
									amp *= 0.5;
								}
								val += nv * fabs(val - 1.0) * 0.3;
							}
							// Blend Mode: 0=normal, 1=shrink-only, 2=grow-only, 3=abs, 4=smooth
							{
								int bm = fractal->transformCommon.multiplierBlendMode5;
								if (bm == 1 && val > 1.0) val = 1.0;
								else if (bm == 2 && val < 1.0) val = 1.0;
								else if (bm == 3) val = 1.0 + fabs(val - 1.0);
								else if (bm == 4) { double sv = fmin(fmax((val - 0.5) * 1.0, 0.0), 1.0); val = 0.5 + sv * sv * (3.0 - 2.0 * sv); }
							}

							// Clip Drive (pre-gain)
							if (fractal->transformCommon.multiplierClipDrive5 != 1.0)
							{
								double drv = fractal->transformCommon.multiplierClipDrive5;
								val = 1.0 + (val - 1.0) * drv;
							}
							// Clip Rectify: 0=off, 1=half(clamp neg to 0), 2=full(abs)
							{
								int cr = fractal->transformCommon.multiplierClipRectify5;
								if (cr == 1 && val < 1.0) val = 1.0;
								else if (cr == 2) val = 1.0 + fabs(val - 1.0);
							}
							// Clip Fold (wavefolder)
							if (fractal->transformCommon.multiplierClipFold5)
							{
								int folds = fractal->transformCommon.multiplierClipFoldCount5;
								if (folds < 1) folds = 1;
								double ceil = fractal->transformCommon.multiplierClipCeiling5;
								double flr = fractal->transformCommon.multiplierClipFloor5;
								for (int fi = 0; fi < folds; fi++)
								{
									if (val > ceil) val = 2.0 * ceil - val;
									if (val < flr) val = 2.0 * flr - val;
								}
							}
							// Clip Ceiling / Floor (hard clamp with asymmetry)
							if (!fractal->transformCommon.multiplierClipFold5)
							{
								double ceil = fractal->transformCommon.multiplierClipCeiling5;
								double flr = fractal->transformCommon.multiplierClipFloor5;
								double asym = fractal->transformCommon.multiplierClipAsymmetry5;
								ceil += asym;
								flr -= asym;
								// Clip Curve (soft knee)
								double curve = fractal->transformCommon.multiplierClipCurve5;
								double knee = fractal->transformCommon.multiplierClipKnee5;
								if (curve > 0.0 || knee > 0.0)
								{
									double k = fmax(knee, 0.001);
									if (val > ceil - k)
									{
										double x = (val - (ceil - k)) / (2.0 * k);
										x = fmin(fmax(x, 0.0), 1.0);
										double sm = x * x * (3.0 - 2.0 * x);
										val = (ceil - k) + k * sm * (1.0 + curve);
										if (val > ceil) val = ceil;
									}
									if (val < flr + k)
									{
										double x = ((flr + k) - val) / (2.0 * k);
										x = fmin(fmax(x, 0.0), 1.0);
										double sm = x * x * (3.0 - 2.0 * x);
										val = (flr + k) - k * sm * (1.0 + curve);
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
							if (fractal->transformCommon.multiplierClipMix5 < 1.0)
							{
								double mx = fractal->transformCommon.multiplierClipMix5;
								// val is already clipped; recover original from drive
								// approximate: mix toward 1.0 (neutral)
								val = 1.0 + mx * (val - 1.0);
							}

							// === Inverse Processing ===
							// Inv Oscillate: alternate normal/inverse per iteration
							{
								bool doInverse = fractal->transformCommon.multiplierInverse5;
								if (fractal->transformCommon.multiplierInvOscillate5)
									doInverse = (aux.i % 2 == 0) ? doInverse : !doInverse;
								if (doInverse)
								{
									double origVal = val;
									double diff = val - 1.0;
									double absDiff = fabs(diff);
									// Inv Range: only invert within range
									double rMin = fractal->transformCommon.multiplierInvRangeMin5;
									double rMax = fractal->transformCommon.multiplierInvRangeMax5;
									if (absDiff >= rMin && absDiff <= rMax)
									{
										// Inv Threshold: only invert if above threshold
										double thr = fractal->transformCommon.multiplierInvThreshold5;
										if (absDiff >= thr)
										{
											double bias = fractal->transformCommon.multiplierInvBias5;
											double center = 1.0 + bias;
											int imode = fractal->transformCommon.multiplierInvMode5;
											if (imode == 0) // Reciprocal
												val = center + (fabs(val - center) > 1e-15 ? (1.0 / (val - center)) : 1e15);
											else if (imode == 1) // Negate
												val = center - (val - center);
											else if (imode == 2) // Complement
												val = center + (1.0 - fabs(val - center));
											else if (imode == 3) // Flip sign
												val = center - fabs(val - center) * ((val > center) ? 1.0 : -1.0);
											// Inv Smooth
											double sm = fractal->transformCommon.multiplierInvSmooth5;
											if (sm > 0.0)
											{
												double blend = fmin(absDiff / (thr + sm + 1e-15), 1.0);
												blend = blend * blend * (3.0 - 2.0 * blend);
												val = origVal + blend * (val - origVal);
											}
											// Inv Decay
											double idcy = fractal->transformCommon.multiplierInvDecay5;
											if (idcy > 0.0)
											{
												double rng = (double)(fractal->transformCommon.multiplierStopIter5 - fractal->transformCommon.multiplierStartIter5);
												double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter5) / rng : 0.0;
												double fade = exp(-idcy * td * 5.0);
												val = origVal + fade * (val - origVal);
											}
											// Inv Strength
											double str = fractal->transformCommon.multiplierInvStrength5;
											if (str < 1.0)
												val = origVal + str * (val - origVal);
										}
									}
									// Inv Axis: 0=all(done), 1/2/3=restore non-target axes later
								}
							}

				
							// Burst / Falloff / Wrap / Conditional for slot 5
							int burstLen5 = fractal->transformCommon.multiplierBurstLength5;
							int burstGap5 = fractal->transformCommon.multiplierBurstGap5;
							if (burstLen5 > 0 && burstGap5 > 0)
							{
								int cycle5 = burstLen5 + burstGap5;
								int phase5 = (aux.i - fractal->transformCommon.multiplierStartIter5) % cycle5;
								if (phase5 >= burstLen5) val = 1.0;
							}
							double sphFall5 = fractal->transformCommon.multiplierSphericalFalloff5;
							if (sphFall5 > 0.0)
							{
								double dist5 = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								double falloff5 = exp(-sphFall5 * dist5);
								val = 1.0 + (val - 1.0) * falloff5;
							}
							double wrapR5 = fractal->transformCommon.multiplierWrapRange5;
							if (wrapR5 > 0.0)
							{
								double shifted5 = val - 1.0;
								shifted5 = fmod(shifted5, wrapR5);
								if (shifted5 < 0.0) shifted5 += wrapR5;
								val = 1.0 + shifted5;
							}
							int condMode5 = fractal->transformCommon.multiplierConditionalMode5;
							if (condMode5 == 1 && z.x < 0.0) val = 1.0;
							else if (condMode5 == 2 && z.x >= 0.0) val = 1.0;
							else if (condMode5 == 3)
							{
								double condDist5 = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								if (condDist5 < fractal->transformCommon.multiplierConditionalThreshold5) val = 1.0;
							}

														// Accumulate for slot 5
							if (fractal->transformCommon.multiplierAccumulate5 && prevMultVal != 1.0)
								val = 1.0 + (val - 1.0) + (prevMultVal - 1.0);

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
