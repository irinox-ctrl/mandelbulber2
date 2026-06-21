/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Fractionele Brownse beweging.
 * Math: B_H(t) met covariantie E[B_H(t)B_H(s)] = 0.5*(|t|^(2H) + |s|^(2H) - |t-s|^(2H))
 */

#include "all_fractal_definitions.h"

cFractalThreex3FractionalBrownianMotion::cFractalThreex3FractionalBrownianMotion() : cAbstractFractal()
{
	nameInComboBox = "3x3 V254 Fractional Brownian Motion";
	internalName = "threex3_fractional_brownian_motion";
	internalID = fractal::threex3FractionalBrownianMotion;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3FractionalBrownianMotion::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Fractional Brownian Motion: B_H(t) met covariantie E[B_H(t)B_H(s)] = 0.5*(|t|^(2H) + |s|^(2H) - |t-s|^(2H))
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	// Stochastic: deterministic chaos via tent map coupling
	double s = fractal->transformCommon.scale1;
	if (s < 0.01) s = 1.5;
	double tent_x = s * (1.0 - 2.0 * fabs(fmod(z.x, 1.0) - 0.5));
	double tent_y = s * (1.0 - 2.0 * fabs(fmod(z.y, 1.0) - 0.5));
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y + tent_y * 0.01, z.x + tent_x * 0.01) * power;
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
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
