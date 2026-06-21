/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * Adds c constant to z vector
 * This formula contains aux.pos_neg
 */

#include "all_fractal_definitions.h"

cFractalTransfAddConstantMod2::cFractalTransfAddConstantMod2() : cAbstractFractal()
{
	nameInComboBox = "T>Add Constant Mod2";
	internalName = "transf_add_constant_mod2";
	internalID = fractal::transfAddConstantMod2;
	DEType = analyticDEType;
	DEFunctionType = withoutDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionNone;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfAddConstantMod2::FormulaCode(
	CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// std offset
	z += fractal->transformCommon.additionConstantA000;

	// plus iter control and alternate offset
	if (fractal->transformCommon.functionEnabledAxFalse)
	{
		if (aux.i >= fractal->transformCommon.startIterationsA
				&& aux.i < fractal->transformCommon.stopIterationsA)
		{
			if (fractal->transformCommon.functionEnabledBxFalse)
			{
				z.x += aux.pos_neg * fractal->transformCommon.additionConstant000.x;
			}
			else
			{
				z.x += fractal->transformCommon.additionConstant000.x;
			}
		}
	}

	if (fractal->transformCommon.functionEnabledAyFalse)
	{
		if (aux.i >= fractal->transformCommon.startIterationsB
				&& aux.i < fractal->transformCommon.stopIterationsB)
		{
			if (fractal->transformCommon.functionEnabledByFalse)
			{
				z.y += aux.pos_neg * fractal->transformCommon.additionConstant000.y;
			}
			else
			{
				z.y += fractal->transformCommon.additionConstant000.y;
			}
		}
	}

	if (fractal->transformCommon.functionEnabledAzFalse)
	{
		if (aux.i >= fractal->transformCommon.startIterationsC
				&& aux.i < fractal->transformCommon.stopIterationsC)
		{
			if (fractal->transformCommon.functionEnabledBzFalse)
			{
				z.z += aux.pos_neg * fractal->transformCommon.additionConstant000.z;
			}
			else
			{
				z.z += fractal->transformCommon.additionConstant000.z;
			}
		}
	}
	aux.pos_neg *= fractal->transformCommon.scaleNeg1;
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
