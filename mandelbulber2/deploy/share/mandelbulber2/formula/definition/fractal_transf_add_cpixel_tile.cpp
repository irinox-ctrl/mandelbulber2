/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * Based on M3D _julia sets
 * @reference A pretransform to show juliasets from formulas.
 * http://www.fractalforums.com/mandelbulb-3d/custom-formulas-and-transforms-release-t17106/
 * This formula contains aux.color
 */

#include "all_fractal_definitions.h"

cFractalTransfAddCpixelTile::cFractalTransfAddCpixelTile() : cAbstractFractal()
{
	nameInComboBox = "T>Add Cpixel Tile";
	internalName = "transf_add_cpixel_tile";
	internalID = fractal::transfAddCpixelTile;
	DEType = analyticDEType;
	DEFunctionType = withoutDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionNone;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfAddCpixelTile::FormulaCode(
	CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	CVector4 cv = aux.const_c;
	if (aux.i == fractal->transformCommon.startIterations) // tiling iteration
	{
		CVector4 p = aux.const_c;
		if (fractal->transformCommon.functionEnabledAx)
		{
			cv.x = round(p.x / fractal->transformCommon.scale3D444.x);
			z.x = p.x - cv.x * fractal->transformCommon.scale3D444.x;
		}

		if (fractal->transformCommon.functionEnabledAy)
		{
			cv.y = round(p.y / fractal->transformCommon.scale3D444.y);
			z.y = p.y - cv.y * fractal->transformCommon.scale3D444.y;
		}

		if (fractal->transformCommon.functionEnabledAz)
		{
			cv.z = round(p.z / fractal->transformCommon.scale3D444.z);
			z.z = p.z - cv.z * fractal->transformCommon.scale3D444.z;
		}

			//z = p - cv * fractal->transformCommon.scale3D444;

		if (fractal->transformCommon.functionEnabledCxFalse) z.x = fabs(z.x);
		if (fractal->transformCommon.functionEnabledCyFalse) z.y = fabs(z.y);

		if (fractal->transformCommon.functionEnabledAxFalse) cv = z;

		cv = cv * fractal->transformCommon.constantMultiplier111
				+ fractal->transformCommon.offset000;

		if (fractal->transformCommon.functionEnabledBFalse)
		{
			cv.x *= sign(aux.const_c.x);
			cv.y *= sign(aux.const_c.y);
			cv.z *= sign(aux.const_c.z);
		}
		aux.c = cv;
	}

	if (aux.i >= fractal->transformCommon.startIterationsA)
	{
		cv = aux.c;
		if (fractal->transformCommon.functionEnabledCFalse)
		{
			cv.x *= sign(z.x);
			cv.y *= sign(z.y);
			cv.z *= sign(z.z);
		}
		z += cv;
		// aux.c = cv;
	}

	// Analytic DE tweak
	if (fractal->analyticDE.enabledFalse)
			aux.DE = aux.DE * fractal->analyticDE.scale1
								+ fractal->analyticDE.offset0;

	// aux->color
	if (fractal->foldColor.auxColorEnabledFalse)
	{
		aux.color += fabs(cv.x * cv.y) * fractal->foldColor.difs0000.x;
		aux.color += (cv.x * cv.x + cv.y * cv.y) * fractal->foldColor.difs0000.y;
	}
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
