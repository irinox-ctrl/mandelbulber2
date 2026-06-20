/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Gegenbauer-polynoom Julia.
 * Math: z = C_n^(lambda)(z) + c
 */

#include "all_fractal_definitions.h"

cFractalThreex3GegenbauerPolynomialJulia::cFractalThreex3GegenbauerPolynomialJulia() : cAbstractFractal()
{
	nameInComboBox = "3x3 V15 Gegenbauer Polynomial Julia";
	internalName = "threex3_gegenbauer_polynomial_julia";
	internalID = fractal::threex3GegenbauerPolynomialJulia;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3GegenbauerPolynomialJulia::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Gegenbauer Polynomial Julia: z = C_n^(lambda)(z) + c
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	double th0 = acos(z.z / r);
	double ph0 = atan2(z.y, z.x);
	double power = fractal->bulb.power;
	if (power < 2.0) power = 3.0;
	// Special function modulation
	double mod = sin(power * th0) * cos(power * ph0);
	double rp = pow(r, power - 1.0);
	double th = th0 * power + fractal->transformCommon.offset0 * mod;
	double ph = ph0 * power + fractal->transformCommon.offsetA0 * mod;
	double sth = sin(th);
	aux.DE = rp * aux.DE * power + 1.0;
	rp *= r;
	z.x = sth * cos(ph) * rp;
	z.y = sth * sin(ph) * rp;
	z.z = cos(th) * rp;
}
