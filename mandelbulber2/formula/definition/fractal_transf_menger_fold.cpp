/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * Transform Menger Fold
 * Menger Sponge formula created by Knighty
 * @reference
 * http://www.fractalforums.com/ifs-iterated-function-systems/kaleidoscopic-(escape-time-ifs)/
 * analytic aux.DE
 */

#include "all_fractal_definitions.h"

cFractalTransfMengerFold::cFractalTransfMengerFold() : cAbstractFractal()
{
	nameInComboBox = "T>Menger Fold";
	internalName = "transf_menger_fold";
	internalID = fractal::transfMengerFold;
	DEType = analyticDEType;
	DEFunctionType = withoutDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionNone;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfMengerFold::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	if (fractal->transformCommon.functionEnabledx)
	{
		double col = 0.0;
		double temp = 0.0;
		z = fabs(z + fractal->transformCommon.additionConstantA000);
		if (z.x < z.y)
		{
			temp = z.y;
			z.y = z.x;
			z.x = temp;
			col += fractal->foldColor.difs0000.x;
		}
		if (z.x < z.z)
		{
			temp = z.z;
			z.z = z.x;
			z.x = temp;
			col += fractal->foldColor.difs0000.y;
		}
		if (z.y < z.z)
		{
			temp = z.z;
			z.z = z.y;
			z.y = temp;
			col += fractal->foldColor.difs0000.z;
		}
		if (fractal->foldColor.auxColorEnabledFalse
				&& aux.i >= fractal->foldColor.startIterationsA
						&& aux.i < fractal->foldColor.stopIterationsA)
		{
			aux.color += col;
		}
	}

	if (fractal->transformCommon.functionEnabledy)
	{ // menger scales and offsets
		z *= fractal->transformCommon.scale3;
		z.x -= 2.0 * fractal->transformCommon.constantMultiplier111.x;
		z.y -= 2.0 * fractal->transformCommon.constantMultiplier111.y;
		if (fractal->transformCommon.functionEnabled)
		{
			if (z.z > 1.0) z.z -= 2.0 * fractal->transformCommon.constantMultiplier111.z;
		}
		else
		{
			z.z -= 2.0 * fractal->transformCommon.constantMultiplier111.z;
		}

		if (fractal->analyticDE.enabled)
		{
			if (!fractal->analyticDE.enabledFalse)
				aux.DE *= fractal->transformCommon.scale3;
			else
				aux.DE = aux.DE * fractal->transformCommon.scale3 * fractal->analyticDE.scale1
								 + fractal->analyticDE.offset0;
		}
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
