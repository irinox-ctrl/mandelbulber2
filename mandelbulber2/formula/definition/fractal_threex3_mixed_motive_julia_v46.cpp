/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Gemengd motief Julia.
 * Math: z = z² + c met extensions of pure motives
 */

#include "all_fractal_definitions.h"

cFractalThreex3MixedMotiveJuliaV46::cFractalThreex3MixedMotiveJuliaV46() : cAbstractFractal()
{
	nameInComboBox = "3x3 V46 Mixed Motive Julia";
	internalName = "threex3_mixed_motive_julia_v46";
	internalID = fractal::threex3MixedMotiveJuliaV46;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3MixedMotiveJuliaV46::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Mixed Motive Julia: z = z² + c met extensions of pure motives
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double th0 = asin(z.z / r);
	double ph0 = atan2(z.y, z.x);
	// Cohomological twist: multiple frequency superposition
	double k = fractal->transformCommon.scale1;
	if (k < 1.0) k = 1.0;
	double th = th0 * power + fractal->transformCommon.offset0 * sin(k * th0);
	double ph = ph0 * power + fractal->transformCommon.offsetA0 * sin(k * ph0);
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
}
