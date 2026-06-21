/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Chebyshev-polynoom Julia.
 * Math: z = T_n(z) + c
 */

#include "all_fractal_definitions.h"

cFractalThreex3ChebyshevPolynomialJulia::cFractalThreex3ChebyshevPolynomialJulia() : cAbstractFractal()
{
	nameInComboBox = "3x3 V11 Chebyshev Polynomial Julia";
	internalName = "threex3_chebyshev_polynomial_julia";
	internalID = fractal::threex3ChebyshevPolynomialJulia;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3ChebyshevPolynomialJulia::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Chebyshev Polynomial Julia: z = T_n(z) + c
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
	// === General Purpose Multiplier 1 ===
	if (fractal->transformCommon.functionEnabledBxFalse
		&& aux.i >= fractal->transformCommon.startIterationsB
		&& aux.i < fractal->transformCommon.stopIterationsB)
	{
		z *= fractal->transformCommon.scale4;
		aux.DE *= fabs(fractal->transformCommon.scale4);
	}

	// === General Purpose Multiplier 2 ===
	if (fractal->transformCommon.functionEnabledByFalse
		&& aux.i >= fractal->transformCommon.startIterationsC
		&& aux.i < fractal->transformCommon.stopIterationsC)
	{
		z *= fractal->transformCommon.scale5;
		aux.DE *= fabs(fractal->transformCommon.scale5);
	}

	// === General Purpose Multiplier 3 ===
	if (fractal->transformCommon.functionEnabledBzFalse
		&& aux.i >= fractal->transformCommon.startIterationsD
		&& aux.i < fractal->transformCommon.stopIterationsD)
	{
		z *= fractal->transformCommon.scale6;
		aux.DE *= fabs(fractal->transformCommon.scale6);
	}

	// === General Purpose Multiplier 4 ===
	if (fractal->transformCommon.functionEnabledBwFalse
		&& aux.i >= fractal->transformCommon.startIterationsE
		&& aux.i < fractal->transformCommon.stopIterationsE)
	{
		z *= fractal->transformCommon.scale8;
		aux.DE *= fabs(fractal->transformCommon.scale8);
	}

	// === General Purpose Multiplier 5 ===
	if (fractal->transformCommon.functionEnabledCzFalse
		&& aux.i >= fractal->transformCommon.startIterationsF
		&& aux.i < fractal->transformCommon.stopIterationsF)
	{
		z *= fractal->transformCommon.scale16;
		aux.DE *= fabs(fractal->transformCommon.scale16);
	}

}
