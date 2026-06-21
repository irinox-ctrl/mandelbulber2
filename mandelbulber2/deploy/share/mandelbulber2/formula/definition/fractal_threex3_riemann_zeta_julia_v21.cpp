/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Riemann-zeta Julia.
 * Math: z = zeta(s) + c met s = 0.5 + i*z
 */

#include "all_fractal_definitions.h"

cFractalThreex3RiemannZetaJuliaV21::cFractalThreex3RiemannZetaJuliaV21() : cAbstractFractal()
{
	nameInComboBox = "3x3 V21 Riemann Zeta Julia";
	internalName = "threex3_riemann_zeta_julia_v21";
	internalID = fractal::threex3RiemannZetaJuliaV21;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3RiemannZetaJuliaV21::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Riemann Zeta Julia: z = zeta(s) + c met s = 0.5 + i*z
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	// Modular form twist: periodic perturbation
	double tau = fractal->transformCommon.scale1;
	double q = exp(-2.0 * M_PI * tau);
	double modTwist = 1.0 + 2.0 * q * cos(2.0 * M_PI * ph / (2.0 * M_PI));
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp * modTwist;
	z.y = cos(th) * sin(ph) * rp * modTwist;
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
