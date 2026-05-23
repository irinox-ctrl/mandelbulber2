/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Krasny-filter.
 * Math: z = z + c met spectrale filter exp(-delta*|k|^p)
 */

#include "all_fractal_definitions.h"

cFractalThreex3KrasnyFilter::cFractalThreex3KrasnyFilter() : cAbstractFractal()
{
	nameInComboBox = "3x3 V248 Krasny Filter";
	internalName = "threex3_krasny_filter";
	internalID = fractal::threex3KrasnyFilter;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3KrasnyFilter::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Krasny Filter: z = z + c met spectrale filter exp(-delta*|k|^p)
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	// Neural: sigmoid activation with coupling
	double w1 = fractal->transformCommon.scale1;
	double w2 = fractal->transformCommon.offset0;
	double sigmoid_x = 1.0 / (1.0 + exp(-w1 * z.x));
	double sigmoid_y = 1.0 / (1.0 + exp(-w1 * z.y));
	double sigmoid_z = 1.0 / (1.0 + exp(-w1 * z.z));
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp + w2 * (sigmoid_x - 0.5);
	z.y = cos(th) * sin(ph) * rp + w2 * (sigmoid_y - 0.5);
	z.z = sin(th) * rp + w2 * (sigmoid_z - 0.5);
}
