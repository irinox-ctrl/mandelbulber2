/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Kiesswetter-kromme fractaal.
 * Math: z = kiesswetter_transform(z) + c
 */

#include "all_fractal_definitions.h"

cFractalThreex3KiesswetterCurveFractal::cFractalThreex3KiesswetterCurveFractal() : cAbstractFractal()
{
	nameInComboBox = "3x3 V389 Kiesswetter Curve Fractal";
	internalName = "threex3_kiesswetter_curve_fractal";
	internalID = fractal::threex3KiesswetterCurveFractal;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3KiesswetterCurveFractal::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Kiesswetter Curve Fractal: z = kiesswetter_transform(z) + c
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	// Tiling: periodic fold pattern
	double period = fractal->transformCommon.scale1;
	if (period < 0.01) period = 1.0;
	z.x = fmod(z.x + period * 0.5, period) - period * 0.5;
	z.y = fmod(z.y + period * 0.5, period) - period * 0.5;
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
}
