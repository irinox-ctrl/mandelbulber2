/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Moore-kromme fractaal.
 * Math: z = moore_transform(z) + c
 */

#include "all_fractal_definitions.h"

cFractalThreex3MooreCurveFractal::cFractalThreex3MooreCurveFractal() : cAbstractFractal()
{
	nameInComboBox = "3x3 V376 Moore Curve Fractal";
	internalName = "threex3_moore_curve_fractal";
	internalID = fractal::threex3MooreCurveFractal;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3MooreCurveFractal::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Moore Curve Fractal: z = moore_transform(z) + c
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	// L-system: branch-and-rotate
	double angle = fractal->transformCommon.scale1 * M_PI / 6.0;
	if (angle == 0.0) angle = M_PI / 6.0;
	double ca = cos(angle); double sa = sin(angle);
	// Apply rotation based on iteration parity
	if (aux.i % 2 == 0) {
		double tmp = z.x * ca - z.y * sa;
		z.y = z.x * sa + z.y * ca;
		z.x = tmp;
	} else {
		double tmp = z.y * ca - z.z * sa;
		z.z = z.y * sa + z.z * ca;
		z.y = tmp;
	}
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
}
