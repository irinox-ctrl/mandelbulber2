/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Hankel-functie Julia.
 * Math: z = H_nu^(1)(z) + c — Bessel van derde soort
 */

#include "all_fractal_definitions.h"

cFractalThreex3HankelFunctionJulia::cFractalThreex3HankelFunctionJulia() : cAbstractFractal()
{
	nameInComboBox = "3x3 V85 Hankel Function Julia";
	internalName = "threex3_hankel_function_julia";
	internalID = fractal::threex3HankelFunctionJulia;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3HankelFunctionJulia::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Hankel Function Julia: z = H_nu^(1)(z) + c — Bessel van derde soort
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
