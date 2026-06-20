/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Householder-methode fractaal.
 * Math: z = z + (d+1)*(1/f)^(d)/(d+1)!
 */

#include "all_fractal_definitions.h"

cFractalThreex3HouseholderMethodFractal::cFractalThreex3HouseholderMethodFractal() : cAbstractFractal()
{
	nameInComboBox = "3x3 V9 Householder Method Fractal";
	internalName = "threex3_householder_method_fractal";
	internalID = fractal::threex3HouseholderMethodFractal;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3HouseholderMethodFractal::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Householder Method Fractal: z = z + (d+1)*(1/f)^(d)/(d+1)!
	double r = aux.r;
	double th0 = asin(z.z / r) + fractal->bulb.betaAngleOffset;
	double ph0 = atan2(z.y, z.x) + fractal->bulb.alphaAngleOffset;
	double power = fractal->bulb.power;
	if (power < 2.0) power = 6.0;
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
