/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * _sinY code from M3D,
 * @reference
 * http://www.fractalforums.com/mandelbulb-3d/custom-formulas-and-transforms-release-t17106/
 */

#include "all_fractal_definitions.h"

cFractalTransfSinYM3d::cFractalTransfSinYM3d() : cAbstractFractal()
{
	nameInComboBox = "T>SinY M3D";
	internalName = "transf_sin_y_m3d";
	internalID = fractal::transfSinYM3d;
	DEType = analyticDEType;
	DEFunctionType = withoutDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionNone;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfSinYM3d::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	if (fractal->transformCommon.functionEnabledAx)
		z.x = sin((z.x - fractal->transformCommon.offset000.x) * fractal->transformCommon.constantMultiplierA111.x)
				* fractal->transformCommon.constantMultiplierB111.x + fractal->transformCommon.offsetA000.x;
	if (fractal->transformCommon.functionEnabledAyFalse)
		z.y = sin((z.y - fractal->transformCommon.offset000.y) * fractal->transformCommon.constantMultiplierA111.y)
				* fractal->transformCommon.constantMultiplierB111.y + fractal->transformCommon.offsetA000.y;
	if (fractal->transformCommon.functionEnabledAzFalse)
		z.z = sin((z.z - fractal->transformCommon.offset000.z) * fractal->transformCommon.constantMultiplierA111.z)
				* fractal->transformCommon.constantMultiplierB111.z + fractal->transformCommon.offsetA000.z;

	// DE tweak
	if (fractal->analyticDE.enabledFalse)
		aux.DE = aux.DE * fractal->analyticDE.scale1 + fractal->analyticDE.offset0;
	// === General Purpose Multiplier 1 ===
	if (fractal->transformCommon.functionEnabledBxFalse
		&& aux.i >= fractal->transformCommon.startIterationsB
		&& aux.i < fractal->transformCommon.stopIterationsB)
	{
		z *= fractal->transformCommon.scale4;
		aux.DE *= fabs(fractal->transformCommon.scale4);
	}

	// === General Purpose Multiplier 2 ===
	if (fractal->transformCommon.functionEnabledByFalse
		&& aux.i >= fractal->transformCommon.startIterationsC
		&& aux.i < fractal->transformCommon.stopIterationsC)
	{
		z *= fractal->transformCommon.scale5;
		aux.DE *= fabs(fractal->transformCommon.scale5);
	}

	// === General Purpose Multiplier 3 ===
	if (fractal->transformCommon.functionEnabledBzFalse
		&& aux.i >= fractal->transformCommon.startIterationsD
		&& aux.i < fractal->transformCommon.stopIterationsD)
	{
		z *= fractal->transformCommon.scale6;
		aux.DE *= fabs(fractal->transformCommon.scale6);
	}

	// === General Purpose Multiplier 4 ===
	if (fractal->transformCommon.functionEnabledBwFalse
		&& aux.i >= fractal->transformCommon.startIterationsE
		&& aux.i < fractal->transformCommon.stopIterationsE)
	{
		z *= fractal->transformCommon.scale8;
		aux.DE *= fabs(fractal->transformCommon.scale8);
	}

	// === General Purpose Multiplier 5 ===
	if (fractal->transformCommon.functionEnabledCzFalse
		&& aux.i >= fractal->transformCommon.startIterationsF
		&& aux.i < fractal->transformCommon.stopIterationsF)
	{
		z *= fractal->transformCommon.scale16;
		aux.DE *= fabs(fractal->transformCommon.scale16);
	}

}
