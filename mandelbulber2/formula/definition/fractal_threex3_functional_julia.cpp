/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Functionele Julia.
 * Math: f = f² + g met functie-compositie
 */

#include "all_fractal_definitions.h"

cFractalThreex3FunctionalJulia::cFractalThreex3FunctionalJulia() : cAbstractFractal()
{
	nameInComboBox = "3x3 V117 Functional Julia";
	internalName = "threex3_functional_julia";
	internalID = fractal::threex3FunctionalJulia;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3FunctionalJulia::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Functional Julia: f = f² + g met functie-compositie
	// Quaternion-style multiplication with twist
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	// Higher-dim: quaternion square + perturbation
	double newX = z.x * z.x - z.y * z.y - z.z * z.z + fractal->transformCommon.offset0;
	double newY = 2.0 * z.x * z.y + fractal->transformCommon.offsetA0;
	double newZ = 2.0 * z.x * z.z + fractal->transformCommon.offsetB0;
	// Apply power scaling
	double scale = pow(r, power - 2.0);
	z.x = newX * scale;
	z.y = newY * scale;
	z.z = newZ * scale;
	aux.DE = aux.DE * power * pow(r, power - 1.0) + 1.0;
}
