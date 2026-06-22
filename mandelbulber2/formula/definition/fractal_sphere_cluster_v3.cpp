/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * formula by TGlad,
 * https://fractalforums.org/fractal-mathematics-and-new-theories/28/fractal-clusters/5107
 */

#include "all_fractal_definitions.h"

cFractalSphereClusterV3::cFractalSphereClusterV3() : cAbstractFractal()
{
	nameInComboBox = "Sphere Cluster V3";
	internalName = "sphere_cluster_v3";
	internalID = fractal::sphereClusterV3;
	DEType = analyticDEType;
	DEFunctionType = customDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionCustomDE;
	coloringFunction = coloringFunctionDefault;
}

void cFractalSphereClusterV3::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	double t = 0.0;
	CVector3 tv = CVector3(0.0, 0.0, 0.0);
	CVector4 oldZ = z;
	double col = 0.0;
	CVector4 ColV = CVector4(0.0, 0.0, 0.0, 0.0);
	CVector3 p = CVector3(z.x, z.y, z.z); // convert to vec3

	p *= fractal->transformCommon.scaleG1; // master scale
	aux.DE *= fractal->transformCommon.scaleG1;

	double phi = (1.0 + sqrt(5.0)) / fractal->transformCommon.scale2;

	// Isocahedral geometry
	CVector3 ta0 = CVector3(0.0, 1.0, phi);
	CVector3 ta1 = CVector3(0.0, -1.0, phi);
	CVector3 ta2 = CVector3(phi, 0.0, 1.0);
	CVector3 na0 = ta0.Cross(ta1 - ta0);
	na0 = na0 / na0.Length();
	CVector3 na1 = ta1.Cross(ta2 - ta1);
	na1 = na1 / na1.Length();
	CVector3 na2 = ta2.Cross(ta0 - ta2);
	na2 = na2 / na2.Length();
	double mid_to_edgea = atan(phi / (1.0 + 2.0 * phi));
	double xxa = 1.0 / sin(mid_to_edgea);
	double ra = 2.0 / sqrt(-4.0 + xxa * xxa);
	double la = sqrt(1.0 + ra * ra);
	CVector3 mida = (ta0 + ta1 + ta2);
	mida = mida/ mida.Length();
	double minra = (la - ra * fractal->transformCommon.scaleC1) * fractal->transformCommon.scaleA1;

	// Dodecahedral geometry
	CVector3 tb0 = CVector3(1.0 / phi, 0.0, phi);
	CVector3 tb1 = CVector3(1.0, -1.0, 1.0);
	CVector3 tb2 = CVector3(phi, -1.0 / phi, 0.0);
	CVector3 tb3 = CVector3(phi, 1.0 / phi, 0.0);
	CVector3 tb4 = CVector3(1.0, 1.0, 1.0);

	CVector3 nb0 = (tb0.Cross(tb1 - tb0));
	nb0 = nb0 / nb0.Length();
	CVector3 nb1 = (tb1.Cross(tb2 - tb1));
	nb1 = nb1 / nb1.Length();
	CVector3 nb2 = (tb2.Cross(tb3 - tb2));
	nb2 = nb2 / nb2.Length();
	CVector3 nb3 = (tb3.Cross(tb4 - tb3));
	nb3 = nb3 / nb3.Length();
	CVector3 nb4 = (tb4.Cross(tb0 - tb4));
	nb4 = nb4 / nb4.Length();
	CVector3 dirb = (tb0 + tb1 + tb2 + tb3 + tb4);
	dirb = dirb /dirb.Length();
	double mid_to_edgeb = atan(dirb.z / dirb.x);
	double xxb = 1.0 / sin(mid_to_edgeb);
	double rb =sqrt(2.0) / sqrt(-2.0 + xxb * xxb);
	double lb = sqrt(1.0 + rb * rb);
	CVector3 midb = dirb;
	double minrb = (lb - rb * fractal->transformCommon.scaleD1) * fractal->transformCommon.scaleB1;

	double k = fractal->transformCommon.scale08; // PackRatio;
	double excess = fractal->transformCommon.offset105; // adds a skin width

	double minr = 0.0;
	double l, r;
	CVector3 mid;

	int n;
	bool recurse = true;
	for (n = 0; n < fractal->transformCommon.int16; n++)
	{
		if (fractal->transformCommon.functionEnabledPFalse
				&& n >= fractal->transformCommon.startIterationsP
				&& n < fractal->transformCommon.stopIterationsP1)
		{
			if (fractal->transformCommon.functionEnabledCxFalse) p.x = fabs(p.x) + fractal->transformCommon.offsetA000.x;
			if (fractal->transformCommon.functionEnabledCyFalse) p.y = fabs(p.y) + fractal->transformCommon.offsetA000.y;
			if (fractal->transformCommon.functionEnabledCzFalse) p.z = fabs(p.z) + fractal->transformCommon.offsetA000.z;
		}

		bool is = true;
		if (n >= fractal->transformCommon.startIterationsA
				&& n < fractal->transformCommon.stopIterationsA) is = false; // Isocahedral

		bool on = true;
		if (n >= fractal->transformCommon.startIterationsB
			&& n < fractal->transformCommon.stopIterationsB) on = false;

		if (recurse && n >= fractal->transformCommon.startIterationsC
				&& n < fractal->transformCommon.stopIterationsC)
		{
			if (p.Length() > excess)
			{
				if (fractal->transformCommon.functionEnabledAFalse)
				{
					//tv = CVector3(0.0, 0.0, 0.0);
					tv = CVector3(z.x, z.y, z.z);
					p = fabs(tv);
				}
				if (!fractal->transformCommon.functionEnabledBFalse) break;
			}
			if (is == true)
			{
				minr = minrb; // Dodecahedral
			}
			else
			{
				minr = minra; // Isocahedral
			}
			if (on == false)
			{

				double sc = minr / p.Dot(p);
				p *= sc;
				aux.DE *= sc;
				ColV.z += 1.0;
				recurse = false;

			}
		}

		if (is == true) // Dodecahedral
		{
			l = lb;
			r = rb;
			mid = midb;
			minr = minrb;
			if (p.Dot(nb0) < 0.0)
				p -= 2.0 * nb0 * p.Dot(nb0);
			if (p.Dot(nb1) < 0.0)
				p -= 2.0 * nb1 * p.Dot(nb1);
			if (p.Dot(nb2) < 0.0)
				p -= 2.0 * nb2 * p.Dot(nb2);
			if (p.Dot(nb3) < 0.0)
				p -= 2.0 * nb3 * p.Dot(nb3);
			if (p.Dot(nb4) < 0.0)
				p -= 2.0 * nb4 * p.Dot(nb4);

			if (p.Dot(nb0) < 0.0)
				p -= 2.0 * nb0 * p.Dot(nb0);
			if (p.Dot(nb1) < 0.0)
				p -= 2.0 * nb1 * p.Dot(nb1);
			if (p.Dot(nb2) < 0.0)
				p -= 2.0 * nb2 * p.Dot(nb2);
			if (p.Dot(nb3) < 0.0)
				p -= 2.0 * nb3 * p.Dot(nb3);
			if (p.Dot(nb4) < 0.0)
				p -= 2.0 * nb4 * p.Dot(nb4);
		}
		else // Isocahedral
		{
			l = la;
			r = ra;
			mid = mida;
			minr = minra;
			if (p.Dot(na0) < 0.0)
				p -= 2.0 * na0 * p.Dot(na0);
			if (p.Dot(na1) < 0.0)
				p -= 2.0 * na1 * p.Dot(na1);
			if (p.Dot(na2) < 0.0)
				p -= 2.0 * na2 * p.Dot(na2);

			if (p.Dot(na0) < 0.0)
				p -= 2.0 * na0 * p.Dot(na0);
			if (p.Dot(na1) < 0.0)
				p -= 2.0 * na1 * p.Dot(na1);
			if (p.Dot(na2) < 0.0)
				p -= 2.0 * na2 * p.Dot(na2);

			if (p.Dot(na0) < 0.0)
				p -= 2.0 * na0 * p.Dot(na0);
			if (p.Dot(na1) < 0.0)
				p -= 2.0 * na1 * p.Dot(na1);
			if (p.Dot(na2) < 0.0)
				p -= 2.0 * na2 * p.Dot(na2);
		}

		double m = minr * k;
		t = 1.0 / m;
		CVector3 tv = p - mid * l;
		double dist = tv.Length();
		if (dist < r || n == fractal->transformCommon.int16 - 1)
		{
			p -= mid * l;

			double inv = 1.0 / p.Dot(p);


			double sc = r * r;
			if (!fractal->transformCommon.functionEnabledMFalse)
				sc = sc * inv;
			else
				sc = (sc + (minr - sc) * fractal->transformCommon.scale0) * inv;

			p *= sc;
			aux.DE *= sc;
			p += mid * l;

			if (fractal->transformCommon.functionEnabledTFalse) m = minr;
			if (p.Length() < m * fractal->transformCommon.radius1 && on == false)
			{
				ColV.y += 1.0;
				p *= t;
				aux.DE *= t;
				recurse = true;
			}
		}

		if (!fractal->transformCommon.functionEnabledIFalse)
		{
			if (on == true && n >= fractal->transformCommon.startIterationsD
					&& n < fractal->transformCommon.stopIterationsD)
			{
				p *= t;
				aux.DE *= t;
			}
		}
		else
		{
			if (recurse && n >= fractal->transformCommon.startIterationsD
					&& n < fractal->transformCommon.stopIterationsD)
			{
				p *= t;
				aux.DE *= t;
			}
		}

		k *= fractal->transformCommon.scale1; // PackRatioScale;
		// post scale
		p *= fractal->transformCommon.scaleF1;
		aux.DE *= fabs(fractal->transformCommon.scaleF1);
		// DE tweaks
		aux.DE = aux.DE * fractal->analyticDE.scale1 + fractal->analyticDE.offset0;

		if (fractal->foldColor.auxColorEnabled && n >= fractal->foldColor.startIterationsA
				&& n < fractal->foldColor.stopIterationsA)
		{
			t = z.Length();

			aux.temp1000 = min(aux.temp1000, t);
			ColV.x = aux.temp1000;

			col += ColV.x * fractal->foldColor.difs0000.x
					+ ColV.y * fractal->foldColor.difs0000.y
					+ ColV.z * fractal->foldColor.difs0000.z;
			if (fractal->foldColor.difs1 > dist) col += fractal->foldColor.difs0000.w;
		}
	}

	z = CVector4(p.x, p.y, p.z, z.w);

	CVector4 zc = z - fractal->transformCommon.offset000;
	if (!fractal->transformCommon.functionEnabledFFalse) zc = fabs(zc);
	double d = max(max(zc.x, zc.y), zc.z) - fractal->transformCommon.offset0;
	d = (d - minr * k) / aux.DE;
//if (d < 0.0) d = 0.0; // mmmmmmmmmmmmmmmmmmmmmmmmmm

	if (fractal->transformCommon.functionEnabledCFalse)
	{
		CVector4 cv = aux.const_c;
		cv.z += fractal->transformCommon.offsetF0;
		double dst1 = cv.Length() - fractal->transformCommon.offsetR1;
		d = max(d, dst1);
//		d = fabs(d); // mmmmmmmmmmmmmmmmmmmmmmmmmm
	}

	if (!fractal->transformCommon.functionEnabledXFalse)
		aux.dist = min(aux.dist, d);
	else
		aux.dist = d;

	if (fractal->analyticDE.enabledFalse) z = oldZ;

	if (!fractal->transformCommon.functionEnabledGFalse)
		aux.color += col;
	else
		aux.color = col;
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

				if (fractal->transformCommon.multiplierInverse1) val = 1.0 / val;

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

				if (fractal->transformCommon.multiplierInverse2) val = 1.0 / val;

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

				if (fractal->transformCommon.multiplierInverse3) val = 1.0 / val;

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

				if (fractal->transformCommon.multiplierInverse4) val = 1.0 / val;

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

				if (fractal->transformCommon.multiplierInverse5) val = 1.0 / val;

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
