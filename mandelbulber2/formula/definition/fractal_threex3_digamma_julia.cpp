/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Digamma Julia.
 * Math: z = psi(z) + c = d/dz ln(gamma(z)) + c
 */

#include "all_fractal_definitions.h"

cFractalThreex3DigammaJulia::cFractalThreex3DigammaJulia() : cAbstractFractal()
{
	nameInComboBox = "3x3 V70 Digamma Julia";
	internalName = "threex3_digamma_julia";
	internalID = fractal::threex3DigammaJulia;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3DigammaJulia::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Digamma Julia: z = psi(z) + c = d/dz ln(gamma(z)) + c
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	// Hyperbolic: sinh/cosh iteration
	double sh = sinh(z.x * fractal->transformCommon.scale1);
	double ch = cosh(z.y * fractal->transformCommon.scale1);
	double newX = sh * ch + z.x;
	double newY = sin(z.y) * cosh(z.x * 0.5) + z.y;
	double newZ = z.z * power + tanh(z.z) * fractal->transformCommon.offset0;
	aux.DE = aux.DE * fabs(power * ch) + 1.0;
	z.x = newX;
	z.y = newY;
	z.z = newZ;
}
