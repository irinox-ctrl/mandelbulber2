/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * box fold 4D
 * This formula contains aux.color
 */

#include "all_fractal_definitions.h"

cFractalTransfBoxFold4d::cFractalTransfBoxFold4d() : cAbstractFractal()
{
	nameInComboBox = "T>Box Fold 4D";
	internalName = "transf_box_fold4d";
	internalID = fractal::transfBoxFold4d;
	DEType = analyticDEType;
	DEFunctionType = withoutDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionNone;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfBoxFold4d::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	CVector4 oldZ = z;
	if (z.x > fractal->mandelbox.foldingLimit)
	{
		z.x = fractal->mandelbox.foldingValue - z.x;
	}
	else if (z.x < -fractal->mandelbox.foldingLimit)
	{
		z.x = -fractal->mandelbox.foldingValue - z.x;
	}
	if (z.y > fractal->mandelbox.foldingLimit)
	{
		z.y = fractal->mandelbox.foldingValue - z.y;
	}
	else if (z.y < -fractal->mandelbox.foldingLimit)
	{
		z.y = -fractal->mandelbox.foldingValue - z.y;
	}
	if (z.z > fractal->mandelbox.foldingLimit)
	{
		z.z = fractal->mandelbox.foldingValue - z.z;
	}
	else if (z.z < -fractal->mandelbox.foldingLimit)
	{
		z.z = -fractal->mandelbox.foldingValue - z.z;
	}
	if (z.w > fractal->mandelbox.foldingLimit)
	{
		z.w = fractal->mandelbox.foldingValue - z.w;
	}
	else if (z.w < -fractal->mandelbox.foldingLimit)
	{
		z.w = -fractal->mandelbox.foldingValue - z.w;
	}
	if (fractal->foldColor.auxColorEnabledFalse)
	{
		if (z.x != oldZ.x) aux.color += fractal->mandelbox.color.factor4D.x;
		if (z.y != oldZ.y) aux.color += fractal->mandelbox.color.factor4D.y;
		if (z.z != oldZ.z) aux.color += fractal->mandelbox.color.factor4D.z;
		if (z.w != oldZ.w) aux.color += fractal->mandelbox.color.factor4D.w;
	}
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
