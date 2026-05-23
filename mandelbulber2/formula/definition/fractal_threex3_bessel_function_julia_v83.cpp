/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Bessel-functie Julia.
 * Math: z = J_nu(z) + c — Bessel van eerste soort
 */

#include "all_fractal_definitions.h"

cFractalThreex3BesselFunctionJuliaV83::cFractalThreex3BesselFunctionJuliaV83() : cAbstractFractal()
{
	nameInComboBox = "3x3 V83 Bessel Function Julia";
	internalName = "threex3_bessel_function_julia_v83";
	internalID = fractal::threex3BesselFunctionJuliaV83;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3BesselFunctionJuliaV83::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Bessel Function Julia: z = J_nu(z) + c — Bessel van eerste soort
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	// Series summation: harmonic perturbation
	double harm = 0.0;
	int terms = max(1, (int)(fractal->transformCommon.scale1));
	for (int n = 1; n <= terms && n <= 8; n++)
		harm += sin(n * th) / (double)n;
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th + harm * 0.1) * cos(ph) * rp;
	z.y = cos(th + harm * 0.1) * sin(ph) * rp;
	z.z = sin(th + harm * 0.1) * rp;
}
