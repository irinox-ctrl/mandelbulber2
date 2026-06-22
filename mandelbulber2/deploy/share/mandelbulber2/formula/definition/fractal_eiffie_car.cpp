/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * EiffieCar
 */

#include "all_fractal_definitions.h"

cFractalEiffieCar::cFractalEiffieCar() : cAbstractFractal()
{
	nameInComboBox = "Eiffie Car";
	internalName = "eiffie_car";
	internalID = fractal::eiffieCar;
	DEType = analyticDEType;
	DEFunctionType = customDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionCustomDE;
	coloringFunction = coloringFunctionDefault;
}

void cFractalEiffieCar::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	Q_UNUSED(&z);

	CVector4 p0 = aux.const_c;
	CVector4 p = p0;

	p.z = p0.z + fractal->transformCommon.scale015;

	double r = sqrt(p.z * p.z + p.x * p.x);

	CVector4 tp = p0;
	tp.y = max(fabs(p.y) - fractal->transformCommon.scale05, 0.0);
	tp.z = max(r - fractal->transformCommon.offset2, 0.0);
	tp.x = max(-p.z + fractal->transformCommon.offset105, 0.0);
	double d = tp.Length() - fractal->transformCommon.offset01; // round
	d = max(d, p.x - fractal->transformCommon.scale1p1); // boot
	if (fractal->transformCommon.functionEnabledDFalse) d = 100.0;


	p.z = p0.z - fractal->transformCommon.offsetD0; // locate z
	p.x = p0.x + fractal->transformCommon.minR2p25; //wheels and guards locate x
	p.y = fabs(fabs(p.y) - fractal->transformCommon.minR06); // locate y
	p.x = fabs(p.x) - fractal->transformCommon.offsetR1; //wheels and guards dist apart
	r = sqrt(p.z * p.z + p.x * p.x);
	tp.x = max(r - fractal->transformCommon.scale025, 0.0); // guard rad
	tp.y = max(p.y - fractal->transformCommon.offsetBp01 - 0.05, 0.0);
	tp.z = max(-p.z - 0.08, 0.0); // mmmmmmmmmmmmmmmmmmmmm

	// IQ's smooth minium function.
	if (!fractal->transformCommon.functionEnabledEFalse)
	{
		d = -log(exp(-fractal->transformCommon.scale8 * d)
				 + exp(-fractal->transformCommon.scale8 * (tp.Length() - 0.04)))
				/ fractal->transformCommon.scale8;
	}
	else
	{

	//	double b = tp.Length() - 0.04;
	//	double h = clamp( 0.5 + 0.5 * (b - d) / 0.2, 0. , 1.0);
	//	d = mix(b, d, h) - h * (1.0 - h) * 0.2;
	}

	d = max(d, -max(p.y - 0.165, r - 0.24)); // guard and car
double zcd = 0.0;
	if (!fractal->transformCommon.functionEnabledFFalse)
	{
		CVector4 q = fabs(p0) - fractal->transformCommon.offset100;
		CVector4 zc = q;

		zc.x = max(zc.x, 0.0);

		zc.y -=  fractal->transformCommon.minR06 + 2.0f * (fractal->transformCommon.offsetBp01 - 0.05f);
		zc.y = max(zc.y, 0.0);
		zc.z = max(zc.z, 0.0);
		zcd = zc.Length();

		zcd -= fractal->transformCommon.offsetB0;
		d = min(zcd, d);
	}

	//wheels
	CVector4 zc = p;
	double cylR = sqrt(zc.x * zc.x + zc.z * zc.z) - fractal->transformCommon.offset02; // tyre OD is offseto2
	cylR = max(fabs(cylR) - fractal->transformCommon.offsetp05, cylR); // tyre
	double cylH = fabs(zc.y) - fractal->transformCommon.offsetp1; //tyre width

	cylR = max(cylR, 0.0);
	cylH = max(cylH, 0.0);
	double cylD = sqrt(cylR * cylR + cylH * cylH);
	cylD = min(max(cylR, cylH), 0.0) + cylD;

	double d2 = cylD - 0.02; // round tyre
	if (fractal->transformCommon.functionEnabledCFalse)  d2 = 100.;
//	REAL d2 = sqrt(tp.y * tp.y + tp.z * tp.z) - .02;

	d = min(d, d2);
	aux.dist = d;

	// aux->color
	if (fractal->foldColor.auxColorEnabledFalse)
	{
		if (aux.dist == d2) aux.color = 3.0 + fractal->foldColor.difs0000.y;
		else aux.color = 5.0 + fractal->foldColor.difs0000.x;

		if (aux.dist == zcd)
			aux.color = 4.0 + fractal->foldColor.difs0000.z;

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
