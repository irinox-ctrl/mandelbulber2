/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Bevriende paren fractaal.
 * Math: z = sigma(z) - z + c met iteratie naar bevriend getal
 */

#include "all_fractal_definitions.h"

cFractalThreex3AmicablePairFractal::cFractalThreex3AmicablePairFractal() : cAbstractFractal()
{
	nameInComboBox = "3x3 V332 Amicable Pair Fractal";
	internalName = "threex3_amicable_pair_fractal";
	internalID = fractal::threex3AmicablePairFractal;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3AmicablePairFractal::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Amicable Pair Fractal: z = sigma(z) - z + c met iteratie naar bevriend getal
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	// Arithmetic: prime-like sieve modulation
	double freq = max(1.0, fractal->transformCommon.scale1);
	double sieve = 0.0;
	for (int p = 2; p <= 7; p++)
		sieve += sin(freq * p * th) / (double)p;
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th + sieve * 0.02) * cos(ph) * rp;
	z.y = cos(th + sieve * 0.02) * sin(ph) * rp;
	z.z = sin(th + sieve * 0.02) * rp;
}
