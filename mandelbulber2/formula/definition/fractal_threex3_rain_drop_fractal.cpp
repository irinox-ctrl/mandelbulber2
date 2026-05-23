/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Regendruppel fractaal.
 * Math: surface_tension + air_resistance + oscillation
 */

#include "all_fractal_definitions.h"

cFractalThreex3RainDropFractal::cFractalThreex3RainDropFractal() : cAbstractFractal()
{
	nameInComboBox = "3x3 V477 Rain Drop Fractal";
	internalName = "threex3_rain_drop_fractal";
	internalID = fractal::threex3RainDropFractal;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3RainDropFractal::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Rain Drop Fractal: surface_tension + air_resistance + oscillation
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	// Reaction-diffusion: Turing pattern
	double Da = fractal->transformCommon.scale1;
	if (Da < 0.01) Da = 1.0;
	double f_rate = fractal->transformCommon.offset0;
	if (f_rate == 0.0) f_rate = 0.04;
	double k_rate = fractal->transformCommon.offsetA0;
	if (k_rate == 0.0) k_rate = 0.06;
	// Gray-Scott inspired perturbation
	double u = 0.5 + 0.5 * sin(z.x * 3.0);
	double v = 0.5 + 0.5 * cos(z.y * 3.0);
	double reaction = -u * v * v + f_rate * (1.0 - u);
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp + Da * reaction * 0.001;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
}
