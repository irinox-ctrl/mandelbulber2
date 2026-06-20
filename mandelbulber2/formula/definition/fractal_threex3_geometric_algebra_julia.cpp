/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Geometrische algebra Julia.
 * Math: x = x² + c in GA(n)
 */

#include "all_fractal_definitions.h"

cFractalThreex3GeometricAlgebraJulia::cFractalThreex3GeometricAlgebraJulia() : cAbstractFractal()
{
	nameInComboBox = "3x3 V110 Geometric Algebra Julia";
	internalName = "threex3_geometric_algebra_julia";
	internalID = fractal::threex3GeometricAlgebraJulia;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3GeometricAlgebraJulia::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Geometric Algebra Julia: x = x² + c in GA(n)
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
