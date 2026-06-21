/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * sin or cos z
 */

#include "all_fractal_definitions.h"

cFractalTransfSinOrCos::cFractalTransfSinOrCos() : cAbstractFractal()
{
	nameInComboBox = "T>Sin Or Cos";
	internalName = "transf_sin_or_cos";
	internalID = fractal::transfSinOrCos;
	DEType = analyticDEType;
	DEFunctionType = withoutDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionNone;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfSinOrCos::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	CVector4 oldZ = z;
	CVector4 trigZ = CVector4(0.0, 0.0, 0.0, 0.0);
	CVector4 scaleZ = z * fractal->transformCommon.constantMultiplierC111;

	if (fractal->transformCommon.functionEnabledAx)
	{
		if (!fractal->transformCommon.functionEnabledAxFalse)
			trigZ.x = sin(scaleZ.x);
		else
			trigZ.x = cos(scaleZ.x); // scale =0, cos = 1
	}
	if (fractal->transformCommon.functionEnabledAy)
	{
		if (!fractal->transformCommon.functionEnabledAyFalse)
			trigZ.y = sin(scaleZ.y);
		else
			trigZ.y = cos(scaleZ.y);
	}
	if (fractal->transformCommon.functionEnabledAz)
	{
		if (!fractal->transformCommon.functionEnabledAzFalse)
			trigZ.z = sin(scaleZ.z);
		else
			trigZ.z = cos(scaleZ.z);
	}

	z = trigZ * fractal->transformCommon.scale;
	if (fractal->transformCommon.functionEnabledFalse)
	{
		z.x = z.x * fractal->transformCommon.scale / (fabs(oldZ.x) + 1.0);
		z.y = z.y * fractal->transformCommon.scale / (fabs(oldZ.y) + 1.0);
		z.z = z.z * fractal->transformCommon.scale / (fabs(oldZ.z) + 1.0);
		// aux.DE = aux.DE * z.Length() / oldZ.Length();
	}
	//   if z == oldZ    z = oldZ * fractal->transformCommon.scale;
	if (!fractal->analyticDE.enabledFalse)
		aux.DE = aux.DE * fabs(fractal->transformCommon.scale) + 1.0;
	else
		aux.DE = aux.DE * fabs(fractal->transformCommon.scale) * fractal->analyticDE.scale1
						 + fractal->analyticDE.offset1;
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
