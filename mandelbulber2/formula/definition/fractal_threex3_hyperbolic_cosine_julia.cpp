/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Hyperbolische cosinus Julia.
 * Math: z = cosh(z) + c
 */

#include "all_fractal_definitions.h"

cFractalThreex3HyperbolicCosineJulia::cFractalThreex3HyperbolicCosineJulia() : cAbstractFractal()
{
	nameInComboBox = "3x3 V60 Hyperbolic Cosine Julia";
	internalName = "threex3_hyperbolic_cosine_julia";
	internalID = fractal::threex3HyperbolicCosineJulia;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3HyperbolicCosineJulia::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Hyperbolic Cosine Julia: z = cosh(z) + c
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	// Transcendental: exp-sin-cos iteration
	double ex = exp(z.x * fractal->transformCommon.scale1);
	double newX = ex * cos(z.y) - z.z * fractal->transformCommon.offset0;
	double newY = ex * sin(z.y) + z.z * fractal->transformCommon.offsetA0;
	double newZ = z.z * cos(z.x * 0.5) + sin(z.y * 0.5) * fractal->transformCommon.scaleC1;
	aux.DE = aux.DE * power * r + 1.0;
	z.x = newX;
	z.y = newY;
	z.z = newZ;
}
