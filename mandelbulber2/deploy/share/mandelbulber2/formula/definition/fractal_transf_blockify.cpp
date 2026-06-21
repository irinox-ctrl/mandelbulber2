/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * Blockify
 * based on a block of Fragmentarium code, from Adam Nixon
 * analytic aux.DE
 */

#include "all_fractal_definitions.h"

cFractalTransfBlockify::cFractalTransfBlockify() : cAbstractFractal()
{
	nameInComboBox = "T>Blockify";
	internalName = "transf_blockify";
	internalID = fractal::transfBlockify;
	DEType = analyticDEType;
	DEFunctionType = withoutDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionNone;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfBlockify::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	double master = fractal->transformCommon.scale / 100.0;
	CVector4 bSize = fractal->transformCommon.constantMultiplier111 * master;

	if (!fractal->transformCommon.functionEnabledFalse)
	{
		if (!fractal->transformCommon.functionEnabledDFalse)
		{
			if (fractal->transformCommon.functionEnabledCx) z.x = (floor(z.x / bSize.x) + 0.5) * bSize.x;
			if (fractal->transformCommon.functionEnabledCy) z.y = (floor(z.y / bSize.y) + 0.5) * bSize.y;
			if (fractal->transformCommon.functionEnabledCz) z.z = (floor(z.z / bSize.z) + 0.5) * bSize.z;
		}
		else // normalize
		{
			double rNorm = z.Length(); //z.Dot(z);
			z /= rNorm;
			if (fractal->transformCommon.functionEnabledCx) z.x = (floor(z.x / bSize.x) + 0.5) * bSize.x;
			if (fractal->transformCommon.functionEnabledCy) z.y = (floor(z.y / bSize.y) + 0.5) * bSize.y;
			if (fractal->transformCommon.functionEnabledCz) z.z = (floor(z.z / bSize.z) + 0.5) * bSize.z;
			z *= rNorm;
		}
	}
	else // radial
	{
		double rr = z.Dot(z);
		if (fractal->transformCommon.functionEnabledRFalse) rr = sqrt(rr); // z.Length();
		if (fractal->transformCommon.functionEnabledBxFalse) rr = z.x * z.x + z.y * z.y;
		if (fractal->transformCommon.functionEnabledByFalse) rr = z.y * z.y + z.z * z.z;
		if (fractal->transformCommon.functionEnabledBzFalse) rr = z.z * z.z + z.x * z.x;
		z /= rr;
		rr = floor(rr / master) * master;
		z *= rr;
	}

	// post scale
	z *= fractal->transformCommon.scale1;
	aux.DE = aux.DE * fractal->transformCommon.scale1 * fractal->analyticDE.scale1
							 + fractal->analyticDE.offset0;

	// === General Purpose Multiplier 1 ===
	if (fractal->transformCommon.functionEnabledBxFalse
		&& aux.i >= fractal->transformCommon.startIterationsB
		&& aux.i < fractal->transformCommon.stopIterationsB)
	{
		double val = fractal->transformCommon.scale4;
		switch (fractal->transformCommon.multiplierMode1)
		{
			default:
			case 0: z *= val; aux.DE *= fabs(val); break;
			case 1: z.x *= val; break;
			case 2: z.y *= val; break;
			case 3: z.z *= val; break;
			case 4: aux.DE *= val; break;
			case 5: aux.color *= val; break;
		}
	}

	// === General Purpose Multiplier 2 ===
	if (fractal->transformCommon.functionEnabledByFalse
		&& aux.i >= fractal->transformCommon.startIterationsC
		&& aux.i < fractal->transformCommon.stopIterationsC)
	{
		double val = fractal->transformCommon.scale5;
		switch (fractal->transformCommon.multiplierMode2)
		{
			default:
			case 0: z *= val; aux.DE *= fabs(val); break;
			case 1: z.x *= val; break;
			case 2: z.y *= val; break;
			case 3: z.z *= val; break;
			case 4: aux.DE *= val; break;
			case 5: aux.color *= val; break;
		}
	}

	// === General Purpose Multiplier 3 ===
	if (fractal->transformCommon.functionEnabledBzFalse
		&& aux.i >= fractal->transformCommon.startIterationsD
		&& aux.i < fractal->transformCommon.stopIterationsD)
	{
		double val = fractal->transformCommon.scale6;
		switch (fractal->transformCommon.multiplierMode3)
		{
			default:
			case 0: z *= val; aux.DE *= fabs(val); break;
			case 1: z.x *= val; break;
			case 2: z.y *= val; break;
			case 3: z.z *= val; break;
			case 4: aux.DE *= val; break;
			case 5: aux.color *= val; break;
		}
	}

	// === General Purpose Multiplier 4 ===
	if (fractal->transformCommon.functionEnabledBwFalse
		&& aux.i >= fractal->transformCommon.startIterationsE
		&& aux.i < fractal->transformCommon.stopIterationsE)
	{
		double val = fractal->transformCommon.scale8;
		switch (fractal->transformCommon.multiplierMode4)
		{
			default:
			case 0: z *= val; aux.DE *= fabs(val); break;
			case 1: z.x *= val; break;
			case 2: z.y *= val; break;
			case 3: z.z *= val; break;
			case 4: aux.DE *= val; break;
			case 5: aux.color *= val; break;
		}
	}

	// === General Purpose Multiplier 5 ===
	if (fractal->transformCommon.functionEnabledCzFalse
		&& aux.i >= fractal->transformCommon.startIterationsF
		&& aux.i < fractal->transformCommon.stopIterationsF)
	{
		double val = fractal->transformCommon.scale16;
		switch (fractal->transformCommon.multiplierMode5)
		{
			default:
			case 0: z *= val; aux.DE *= fabs(val); break;
			case 1: z.x *= val; break;
			case 2: z.y *= val; break;
			case 3: z.z *= val; break;
			case 4: aux.DE *= val; break;
			case 5: aux.color *= val; break;
		}
	}

}
