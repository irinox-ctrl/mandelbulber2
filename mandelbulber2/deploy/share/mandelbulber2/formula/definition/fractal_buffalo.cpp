/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * Buffalo fractal
 * @reference /http://www.fractalforums.com/gallery-b177/buffalo-fractals
 */

#include "all_fractal_definitions.h"

cFractalBuffalo::cFractalBuffalo() : cAbstractFractal()
{
	nameInComboBox = "Buffalo";
	internalName = "buffalo";
	internalID = fractal::buffalo;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalBuffalo::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	aux.DE = aux.DE * 2.0 * aux.r;

	if (fractal->buffalo.preabsx) z.x = fabs(z.x);
	if (fractal->buffalo.preabsy) z.y = fabs(z.y);
	if (fractal->buffalo.preabsz) z.z = fabs(z.z);

	double x2 = z.x * z.x;
	double y2 = z.y * z.y;
	double z2 = z.z * z.z;
	double temp = 1.0 - z2 / (x2 + y2);
	double newx = (x2 - y2) * temp;
	double newy = 2.0 * z.x * z.y * temp;
	double newz = (fractal->buffalo.posz ? 2.0 : -2.0) * z.z * sqrt(x2 + y2);

	z.x = fractal->buffalo.absx ? fabs(newx) : newx;
	z.y = fractal->buffalo.absy ? fabs(newy) : newy;
	z.z = fractal->buffalo.absz ? fabs(newz) : newz;
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
