/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * T-graaf fractaal.
 * Math: z = T_contract(z) + c
 */

#include "all_fractal_definitions.h"

cFractalThreex3TGraphFractal::cFractalThreex3TGraphFractal() : cAbstractFractal()
{
	nameInComboBox = "3x3 V359 T-Graph Fractal";
	internalName = "threex3_t_graph_fractal";
	internalID = fractal::threex3TGraphFractal;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3TGraphFractal::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// T-Graph Fractal: z = T_contract(z) + c
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	// Cellular automaton: rule-based folding
	double rule = fractal->transformCommon.scale1;
	if (rule < 1.0) rule = 30.0;
	double threshold = fractal->transformCommon.offset0;
	if (threshold == 0.0) threshold = 0.5;
	// Fold based on threshold
	if (z.x > threshold) z.x = 2.0 * threshold - z.x;
	if (z.x < -threshold) z.x = -2.0 * threshold - z.x;
	if (z.y > threshold) z.y = 2.0 * threshold - z.y;
	if (z.y < -threshold) z.y = -2.0 * threshold - z.y;
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
}
