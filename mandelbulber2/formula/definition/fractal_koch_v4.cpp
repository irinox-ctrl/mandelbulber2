/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * KochV2Iteration
 * Based on Knighty's Kaleidoscopic IFS 3D Fractals, described here:
 * http://www.fractalforums.com/3d-fractal-generation/kaleidoscopic-%28escape-time-ifs%29/
 */

#include "all_fractal_definitions.h"

cFractalKochV4::cFractalKochV4() : cAbstractFractal()
{
	nameInComboBox = "Koch V4";
	internalName = "koch_v4";
	internalID = fractal::kochV4;
	DEType = analyticDEType;
	DEFunctionType = customDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionCustomDE;
	coloringFunction = coloringFunctionDefault;
}

void cFractalKochV4::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	CVector4 zc = z;

	if (fractal->transformCommon.functionEnabledAx) zc.x = fabs(zc.x);
	if (fractal->transformCommon.functionEnabledAy) zc.y = fabs(zc.y);
	if (fractal->transformCommon.functionEnabledAzFalse) zc.z = fabs(zc.z);
	if (fractal->transformCommon.functionEnabledCx)
		if (zc.y > zc.x) swap(zc.x, zc.y);

	// folds
	if (fractal->transformCommon.functionEnabledFalse)
	{
		// diagonal2
		if (fractal->transformCommon.functionEnabledCxFalse)
			if (zc.x > zc.y) swap(zc.x, zc.y);
		// polyfold
		if (fractal->transformCommon.functionEnabledPFalse)
		{
			zc.x = fabs(zc.x);
			double psi = M_PI / fractal->transformCommon.int6;
			psi = fabs(fmod(atan2(zc.y, zc.x) + psi, 2.0 * psi) - psi);
			double len = sqrt(zc.x * zc.x + zc.y * zc.y);
			zc.x = cos(psi) * len;
			zc.y = sin(psi) * len;
		}
		// abs offsets
		if (fractal->transformCommon.functionEnabledCFalse)
		{
			double xOffset = fractal->transformCommon.offsetC0;
			if (zc.x < xOffset) zc.x = fabs(zc.x - xOffset) + xOffset;
		}
		if (fractal->transformCommon.functionEnabledDFalse)
		{
			double yOffset = fractal->transformCommon.offsetD0;
			if (zc.y < yOffset) zc.y = fabs(zc.y - yOffset) + yOffset;
		}
	}

	double YOff = FRAC_1_3 * fractal->transformCommon.scale1;
	zc.y = YOff - fabs(zc.y - YOff);

	zc.x += FRAC_1_3;
	if (zc.z > zc.x) swap(zc.x, zc.z);
	zc.x -= FRAC_1_3;

	zc.x -= FRAC_1_3;
	if (zc.z > zc.x) swap(zc.x, zc.z);
	zc.x += FRAC_1_3;

	CVector4 Offset = fractal->transformCommon.offset100;
	double useScale = 1.0;
	useScale = (aux.actualScaleA + fractal->transformCommon.scale3);
	if (fractal->transformCommon.functionEnabledKFalse)
	{
		// update actualScaleA for next iteration
		double vary = fractal->transformCommon.scaleVary0
									* (fabs(aux.actualScaleA) - fractal->transformCommon.scaleC1);
		aux.actualScaleA = -vary;
	}
	zc = useScale * (zc - Offset) + Offset;
	aux.DE = aux.DE * fabs(useScale) + fractal->analyticDE.offset0;

	// rotation
	if (fractal->transformCommon.functionEnabledRFalse
			&& aux.i >= fractal->transformCommon.startIterationsR
			&& aux.i < fractal->transformCommon.stopIterationsR)
	{
		zc = fractal->transformCommon.rotationMatrix.RotateVector(zc);
	}
	zc += fractal->transformCommon.offset000;

	//aux.dist
	CVector4 c = aux.const_c;
	double d;

	double a = fractal->transformCommon.offsetA0;
	if (!fractal->transformCommon.functionEnabledFFalse)
	{
		CVector4 b = fabs(zc) - CVector4(a, a, a, 0.0);
		d = max(b.x, max(b.y, b.z));
	}
	else
	{
		d = fabs(zc.Length() - a);
	}

	if (fractal->transformCommon.functionEnabledBFalse)
		d -= Offset.Length();

	// plane
	double g = fabs(zc.z - fractal->transformCommon.offsetR0) - fractal->transformCommon.offsetF0;

	g = min(g, d);

	// clip
	double e = fractal->transformCommon.offset2;
	if (!fractal->transformCommon.functionEnabledEFalse)
	{
		CVector4 f = fabs(c) - CVector4(e, e, e, 0.0);
		if (!fractal->transformCommon.functionEnabledIFalse)
			e = max(f.x, f.y); // sq
		else
			e = max(f.x, max(f.y, f.z)); // box
	}
	else
	{
		if (!fractal->transformCommon.functionEnabledIFalse)
			e = clamp(sqrt(c.x * c.x + c.y * c.y) - e, 0.0, 100.0); // circle
		else
			e = clamp(c.Length() - e, 0.0, 100.0); // sphere
	}

	d = max(g, e) / aux.DE;

	//aux.dist = d;
	aux.dist = min(d, aux.dist);

	// aux->color
	if (fractal->foldColor.auxColorEnabledFalse
			&& aux.i >= fractal->foldColor.startIterationsA
			&& aux.i < fractal->foldColor.stopIterationsA)
	{
		double addColor = 0.0;
		if (aux.dist == d)
			aux.color = fractal->foldColor.difs0000.x;

		else
		{
			addColor = fractal->foldColor.difs0000.y * fabs(zc.x)
					+ fractal->foldColor.difs0000.z * fabs(zc.z)
					+ fractal->foldColor.difs0000.w * g;

			if (!fractal->transformCommon.functionEnabledJFalse)
				aux.color = addColor;
			else
				aux.color += addColor;
		}
	}
	z = zc;

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
