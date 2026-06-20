/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Hénon-afbeelding.
 * Math: x_{n+1} = 1 - a*x_n² + y_n, y_{n+1} = b*x_n
 */

#include "all_fractal_definitions.h"

cFractalThreex3HenonMap::cFractalThreex3HenonMap() : cAbstractFractal()
{
	nameInComboBox = "3x3 V201 Henon Map";
	internalName = "threex3_henon_map";
	internalID = fractal::threex3HenonMap;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3HenonMap::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Henon Map: x_{n+1} = 1 - a*x_n² + y_n, y_{n+1} = b*x_n
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	// Dynamic system: coupled oscillator map
	double a = fractal->transformCommon.scale1;
	if (a == 0.0) a = 1.4;
	double b = fractal->transformCommon.offset0;
	if (b == 0.0) b = 0.3;
	double newX = 1.0 - a * z.x * z.x + z.y;
	double newY = b * z.x + z.z * fractal->transformCommon.offsetA0;
	double newZ = sin(z.z * power) + z.x * fractal->transformCommon.offsetB0;
	aux.DE = aux.DE * fabs(2.0 * a * z.x) + 1.0;
	z.x = newX;
	z.y = newY;
	z.z = newZ;
}
