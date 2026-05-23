/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Polynomiale Julia graad 4.
 * Math: z = z⁴ + a*z² + b*z + c
 */

#include "all_fractal_definitions.h"

cFractalThreex3PolynomialJuliaDegree4::cFractalThreex3PolynomialJuliaDegree4() : cAbstractFractal()
{
	nameInComboBox = "3x3 V3 Polynomial Julia Degree 4";
	internalName = "threex3_polynomial_julia_degree_4";
	internalID = fractal::threex3PolynomialJuliaDegree4;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3PolynomialJuliaDegree4::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Polynomial Julia Degree 4: z = z⁴ + a*z² + b*z + c
	double r = aux.r;
	double th0 = asin(z.z / r) + fractal->bulb.betaAngleOffset;
	double ph0 = atan2(z.y, z.x) + fractal->bulb.alphaAngleOffset;
	double power = fractal->bulb.power;
	if (power < 2.0) power = 5.0;
	double rp = pow(r, power - 1.0);
	double th = th0 * power;
	double ph = ph0 * power;
	double cth = cos(th);
	aux.DE = rp * aux.DE * power + 1.0;
	rp *= r;
	double newX = cth * cos(ph) * rp;
	double newY = cth * sin(ph) * rp;
	double newZ = sin(th) * rp;
	// Algebraic twist: add polynomial correction
	double corr = fractal->transformCommon.scale1 * sin(power * atan2(newY, newX));
	z.x = newX + corr * fractal->transformCommon.constantMultiplier111.x;
	z.y = newY + corr * fractal->transformCommon.constantMultiplier111.y;
	z.z = newZ + corr * fractal->transformCommon.constantMultiplier111.z;
}
