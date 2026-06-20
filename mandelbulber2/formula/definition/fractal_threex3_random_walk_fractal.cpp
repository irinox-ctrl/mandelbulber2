/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Willekeurige wandeling fractaal.
 * Math: z_{n+1} = z_n + random_step() met random_step() uniform of Gaussisch
 */

#include "all_fractal_definitions.h"

cFractalThreex3RandomWalkFractal::cFractalThreex3RandomWalkFractal() : cAbstractFractal()
{
	nameInComboBox = "3x3 V251 Random Walk Fractal";
	internalName = "threex3_random_walk_fractal";
	internalID = fractal::threex3RandomWalkFractal;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3RandomWalkFractal::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Random Walk Fractal: z_{n+1} = z_n + random_step() met random_step() uniform of Gaussisch
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
}
