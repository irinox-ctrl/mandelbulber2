/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Chebyshev-functie fractaal.
 * Math: z = psi(z) + c = sum(log(p)) met p^k <= z
 */

#include "all_fractal_definitions.h"

cFractalThreex3ChebyshevFunctionFractal::cFractalThreex3ChebyshevFunctionFractal() : cAbstractFractal()
{
	nameInComboBox = "3x3 V312 Chebyshev Function Fractal";
	internalName = "threex3_chebyshev_function_fractal";
	internalID = fractal::threex3ChebyshevFunctionFractal;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3ChebyshevFunctionFractal::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Chebyshev Function Fractal: z = psi(z) + c = sum(log(p)) met p^k <= z
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	// Number theory: Collatz-inspired branching
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	double rp = pow(r, power);
	// Parity-based perturbation
	int parity = ((int)floor(fabs(z.x * 100.0))) % 2;
	double shift = parity ? fractal->transformCommon.scale1 * 0.01 : -fractal->transformCommon.scale1 * 0.01;
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp + shift;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
}
