/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Froeschlé-afbeelding.
 * Math: I1' = I1 + k1*sin(theta1) + k2*sin(theta1+theta2), I2' = I2 + k3*sin(theta2) + k2*sin(theta1+theta2)
 */

#include "all_fractal_definitions.h"

cFractalThreex3FroeschleMap::cFractalThreex3FroeschleMap() : cAbstractFractal()
{
	nameInComboBox = "3x3 V213 Froeschle Map";
	internalName = "threex3_froeschle_map";
	internalID = fractal::threex3FroeschleMap;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3FroeschleMap::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Froeschle Map: I1' = I1 + k1*sin(theta1) + k2*sin(theta1+theta2), I2' = I2 + k3*sin(theta2) + k2*sin(theta1+theta2)
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
