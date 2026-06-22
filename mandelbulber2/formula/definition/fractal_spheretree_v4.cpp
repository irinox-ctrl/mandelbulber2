/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * formula by TGlad,
 * https://https://fractalforums.org/fractal-mathematics-and-new-theories/28/sphere-inversion-trees/5113
 */

#include "all_fractal_definitions.h"

cFractalSpheretreeV4::cFractalSpheretreeV4() : cAbstractFractal()
{
	nameInComboBox = "Spheretree V4";
	internalName = "spheretree_v4";
	internalID = fractal::spheretreeV4;
	DEType = analyticDEType;
	DEFunctionType = linearDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionLinear;
	coloringFunction = coloringFunctionDefault;
}

void cFractalSpheretreeV4::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	double t = 0.0; // temp
	CVector4 tv = CVector4(0.0, 0.0, 0.0, 0.0); // temp vector
	CVector4 oldZ = z;
	double col = 0.0;
	CVector4 ColV = tv;
	if (fractal->transformCommon.functionEnabledJFalse)
	{
		aux.DE = 1.0;
		z = aux.const_c;
	}

	z *= fractal->transformCommon.scaleG1; // master scale
	aux.DE *= fractal->transformCommon.scaleG1;

	int NumChildren = fractal->transformCommon.int8X;
	int n = NumChildren;
	double ang1 = M_PI / n;

	double o1 = 3.0;
	if (NumChildren <= 4)
		o1 = 5.0;
	else if (NumChildren <= 6)
		o1 = 4.0;
	double sec = 1.0 / cos(M_PI / o1);
	double csc = 1.0 / sin(M_PI / n);
	double r = sec / sqrt(csc * csc - sec * sec);
	double l = sqrt(1.0 + r * r);

	double o2 = fractal->transformCommon.offset3;
	t = sin(M_PI - M_PI / o2);
	double theta = asin(r * t / l);
	double L4 = l * sin(M_PI / o2 - theta) / t;
	double minr = L4 * L4 * fractal->transformCommon.scaleD1;
	double bend = fractal->transformCommon.scale08;
	double omega = 0.0;
	double bigR = 0.0;
	double d = 0.0;

	if (!fractal->transformCommon.functionEnabledzFalse)
	{
		omega = M_PI_2 - bend;
		bigR = 1.0 / cos(omega);
		d = tan(omega);
	}
	// iteration loop
	bool recurse = true;
	if (fractal->transformCommon.functionEnabledFalse) recurse = false;
	for (int c = 0; c < fractal->transformCommon.int16; c++)
	{
		if (fractal->transformCommon.functionEnabledzFalse)
		{
			omega = M_PI_2 - bend;
			bigR = 1.0 / cos(omega);
			d = tan(omega);
		}

		if (recurse == true && c >= fractal->transformCommon.startIterationsC
				&& c < fractal->transformCommon.stopIterationsC)
		{
			z.z += d + bigR;
			double inv = 1.0 / z.Dot(z);
			double sc = 4.0 * bigR * bigR * inv;
			z *= sc;
			aux.DE *= sc;
			z.z += -2.0 * bigR;
			z.z = -z.z;
			double invSize = (bigR + d) / (2.0 * bigR);
			aux.DE *= invSize;
			z *= invSize;
			recurse = false;
		}

		double angle = atan2(z.y, z.x);
		if (angle < 0.0) angle += M_PI_2x;
		angle = fmod(angle, M_PI_2x / n);
		double mag = sqrt(z.x * z.x + z.y * z.y);
		z.x = mag * cos(angle);
		z.y = mag * sin(angle);

		CVector4 circle_centre = l * CVector4(cos(ang1), sin(ang1), 0.0, 0.0);
		tv = z - circle_centre;
		double len = tv.Length();
		if (len < r)
		{
			ColV.x += 1.0;
			double sc = r * r / (len * len);
			tv *= sc;
			aux.DE *= sc;
		}
		z = tv + circle_centre;

		o2 = bend / 2.0;
		double R2 = minr / cos(o2);
		tv = z;
		tv.z -= minr * tan(o2) * fractal->transformCommon.scaleA1;
		double amp = tv.Length();
		// double mag4 = sqrt(z.x * z.x + z.y * z.y};
		if (amp <= R2 - fractal->transformCommon.offsetA0
				&& c >= fractal->transformCommon.startIterationsB
				&& c < fractal->transformCommon.stopIterationsB) // || mag4 <= minr)
		{
			ColV.z += 1.0;
			t = 1.0 / minr;
			z *= t;
			aux.DE *= t;
			recurse = true;
		}
		else if (z.Length() < L4)
		{
			double inv = 1.0 / z.Dot(z);
			double sc =  L4 * L4  * inv;
			z *= sc;
			aux.DE *= sc;
		}

		if (c >= fractal->transformCommon.startIterationsA
				&& c < fractal->transformCommon.stopIterationsA)
		{
			bend *= fractal->transformCommon.scaleB1;
			bend += fractal->transformCommon.offsetB0;
		}

		// post scale
		z *= fractal->transformCommon.scaleC1;
		aux.DE *= fabs(fractal->transformCommon.scaleC1);

		// DE tweaks
		aux.DE = aux.DE * fractal->analyticDE.scale1 + fractal->analyticDE.offset0;

		if (fractal->foldColor.auxColorEnabled && c >= fractal->foldColor.startIterationsA
				&& c < fractal->foldColor.stopIterationsA)
		{
			t = z.Length();

			aux.temp1000 = min(aux.temp1000, t);
			ColV.y = aux.temp1000;
			ColV.w  = t;

			col += ColV.x * fractal->foldColor.difs0000.x + ColV.y * fractal->foldColor.difs0000.y
					+ ColV.z * fractal->foldColor.difs0000.z + ColV.w * fractal->foldColor.difs0000.w;
		}
	}

	aux.DE = aux.DE + fractal->transformCommon.offsetF0;
	if (fractal->transformCommon.offset0 != 0.0)
	{
		t = z.Length();
		aux.DE *= t / (t - fractal->transformCommon.offset0);
		aux.dist = t / aux.DE;
	}

	if (fractal->analyticDE.enabledFalse) z = oldZ;

	if (!fractal->transformCommon.functionEnabledCFalse)
		aux.color += col;
	else
		aux.color = col;
	// GPU bypass: skip if all multipliers disabled
	if (fractal->transformCommon.functionEnabledBxFalse || fractal->transformCommon.functionEnabledByFalse || fractal->transformCommon.functionEnabledBzFalse || fractal->transformCommon.functionEnabledBwFalse || fractal->transformCommon.functionEnabledCzFalse)
	{
		// === General Purpose Multiplier 1 ===
		if (fractal->transformCommon.functionEnabledBxFalse
				&& aux.i >= fractal->transformCommon.startIterationsB
				&& aux.i < fractal->transformCommon.stopIterationsB)
		{
			double val = fractal->transformCommon.scale4;

			if (fractal->transformCommon.multiplierInverse1) val = 1.0 / val;

			int vmode = fractal->transformCommon.multiplierValueMode1;
			if (vmode == 1)
			{
				double range = (double)(fractal->transformCommon.stopIterationsB - fractal->transformCommon.startIterationsB);
				if (range > 0)
				{
					double phase = (double)(aux.i - fractal->transformCommon.startIterationsB) / range;
					val = 1.0 + (val - 1.0) * sin(phase * fractal->transformCommon.multiplierFrequency1 * 2.0 * M_PI);
				}
			}
			else if (vmode == 2)
			{
				double range = (double)(fractal->transformCommon.stopIterationsB - fractal->transformCommon.startIterationsB);
				if (range > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.startIterationsB) / range;
					t = qBound(0.0, t, 1.0);
					val = 1.0 + t * (val - 1.0);
				}
			}

			switch (fractal->transformCommon.multiplierMode1)
			{
				default:
				case 0: z *= val; aux.DE *= fabs(val); break;
				case 1: z.x *= val; break;
				case 2: z.y *= val; break;
				case 3: z.z *= val; break;
				case 4: aux.DE *= val; break;
				case 5: aux.color *= val; break;
				case 6: z.w *= val; break;
				case 7: z.x *= val; z.y *= val; break;
				case 8: z.x *= val; z.z *= val; break;
				case 9: z.y *= val; z.z *= val; break;
			}
		}

		// === General Purpose Multiplier 2 ===
		if (fractal->transformCommon.functionEnabledByFalse
				&& aux.i >= fractal->transformCommon.startIterationsC
				&& aux.i < fractal->transformCommon.stopIterationsC)
		{
			double val = fractal->transformCommon.scale5;

			if (fractal->transformCommon.multiplierInverse2) val = 1.0 / val;

			int vmode = fractal->transformCommon.multiplierValueMode2;
			if (vmode == 1)
			{
				double range = (double)(fractal->transformCommon.stopIterationsC - fractal->transformCommon.startIterationsC);
				if (range > 0)
				{
					double phase = (double)(aux.i - fractal->transformCommon.startIterationsC) / range;
					val = 1.0 + (val - 1.0) * sin(phase * fractal->transformCommon.multiplierFrequency2 * 2.0 * M_PI);
				}
			}
			else if (vmode == 2)
			{
				double range = (double)(fractal->transformCommon.stopIterationsC - fractal->transformCommon.startIterationsC);
				if (range > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.startIterationsC) / range;
					t = qBound(0.0, t, 1.0);
					val = 1.0 + t * (val - 1.0);
				}
			}

			switch (fractal->transformCommon.multiplierMode2)
			{
				default:
				case 0: z *= val; aux.DE *= fabs(val); break;
				case 1: z.x *= val; break;
				case 2: z.y *= val; break;
				case 3: z.z *= val; break;
				case 4: aux.DE *= val; break;
				case 5: aux.color *= val; break;
				case 6: z.w *= val; break;
				case 7: z.x *= val; z.y *= val; break;
				case 8: z.x *= val; z.z *= val; break;
				case 9: z.y *= val; z.z *= val; break;
			}
		}

		// === General Purpose Multiplier 3 ===
		if (fractal->transformCommon.functionEnabledBzFalse
				&& aux.i >= fractal->transformCommon.startIterationsD
				&& aux.i < fractal->transformCommon.stopIterationsD)
		{
			double val = fractal->transformCommon.scale6;

			if (fractal->transformCommon.multiplierInverse3) val = 1.0 / val;

			int vmode = fractal->transformCommon.multiplierValueMode3;
			if (vmode == 1)
			{
				double range = (double)(fractal->transformCommon.stopIterationsD - fractal->transformCommon.startIterationsD);
				if (range > 0)
				{
					double phase = (double)(aux.i - fractal->transformCommon.startIterationsD) / range;
					val = 1.0 + (val - 1.0) * sin(phase * fractal->transformCommon.multiplierFrequency3 * 2.0 * M_PI);
				}
			}
			else if (vmode == 2)
			{
				double range = (double)(fractal->transformCommon.stopIterationsD - fractal->transformCommon.startIterationsD);
				if (range > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.startIterationsD) / range;
					t = qBound(0.0, t, 1.0);
					val = 1.0 + t * (val - 1.0);
				}
			}

			switch (fractal->transformCommon.multiplierMode3)
			{
				default:
				case 0: z *= val; aux.DE *= fabs(val); break;
				case 1: z.x *= val; break;
				case 2: z.y *= val; break;
				case 3: z.z *= val; break;
				case 4: aux.DE *= val; break;
				case 5: aux.color *= val; break;
				case 6: z.w *= val; break;
				case 7: z.x *= val; z.y *= val; break;
				case 8: z.x *= val; z.z *= val; break;
				case 9: z.y *= val; z.z *= val; break;
			}
		}

		// === General Purpose Multiplier 4 ===
		if (fractal->transformCommon.functionEnabledBwFalse
				&& aux.i >= fractal->transformCommon.startIterationsE
				&& aux.i < fractal->transformCommon.stopIterationsE)
		{
			double val = fractal->transformCommon.scale8;

			if (fractal->transformCommon.multiplierInverse4) val = 1.0 / val;

			int vmode = fractal->transformCommon.multiplierValueMode4;
			if (vmode == 1)
			{
				double range = (double)(fractal->transformCommon.stopIterationsE - fractal->transformCommon.startIterationsE);
				if (range > 0)
				{
					double phase = (double)(aux.i - fractal->transformCommon.startIterationsE) / range;
					val = 1.0 + (val - 1.0) * sin(phase * fractal->transformCommon.multiplierFrequency4 * 2.0 * M_PI);
				}
			}
			else if (vmode == 2)
			{
				double range = (double)(fractal->transformCommon.stopIterationsE - fractal->transformCommon.startIterationsE);
				if (range > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.startIterationsE) / range;
					t = qBound(0.0, t, 1.0);
					val = 1.0 + t * (val - 1.0);
				}
			}

			switch (fractal->transformCommon.multiplierMode4)
			{
				default:
				case 0: z *= val; aux.DE *= fabs(val); break;
				case 1: z.x *= val; break;
				case 2: z.y *= val; break;
				case 3: z.z *= val; break;
				case 4: aux.DE *= val; break;
				case 5: aux.color *= val; break;
				case 6: z.w *= val; break;
				case 7: z.x *= val; z.y *= val; break;
				case 8: z.x *= val; z.z *= val; break;
				case 9: z.y *= val; z.z *= val; break;
			}
		}

		// === General Purpose Multiplier 5 ===
		if (fractal->transformCommon.functionEnabledCzFalse
				&& aux.i >= fractal->transformCommon.startIterationsF
				&& aux.i < fractal->transformCommon.stopIterationsF)
		{
			double val = fractal->transformCommon.scale16;

			if (fractal->transformCommon.multiplierInverse5) val = 1.0 / val;

			int vmode = fractal->transformCommon.multiplierValueMode5;
			if (vmode == 1)
			{
				double range = (double)(fractal->transformCommon.stopIterationsF - fractal->transformCommon.startIterationsF);
				if (range > 0)
				{
					double phase = (double)(aux.i - fractal->transformCommon.startIterationsF) / range;
					val = 1.0 + (val - 1.0) * sin(phase * fractal->transformCommon.multiplierFrequency5 * 2.0 * M_PI);
				}
			}
			else if (vmode == 2)
			{
				double range = (double)(fractal->transformCommon.stopIterationsF - fractal->transformCommon.startIterationsF);
				if (range > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.startIterationsF) / range;
					t = qBound(0.0, t, 1.0);
					val = 1.0 + t * (val - 1.0);
				}
			}

			switch (fractal->transformCommon.multiplierMode5)
			{
				default:
				case 0: z *= val; aux.DE *= fabs(val); break;
				case 1: z.x *= val; break;
				case 2: z.y *= val; break;
				case 3: z.z *= val; break;
				case 4: aux.DE *= val; break;
				case 5: aux.color *= val; break;
				case 6: z.w *= val; break;
				case 7: z.x *= val; z.y *= val; break;
				case 8: z.x *= val; z.z *= val; break;
				case 9: z.y *= val; z.z *= val; break;
			}
		}
	}

}
