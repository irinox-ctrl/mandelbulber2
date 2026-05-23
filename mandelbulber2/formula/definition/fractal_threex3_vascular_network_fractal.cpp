/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Vasculair netwerk fractaal.
 * Math: Murray's law: r_parent^3 = sum(r_daughter^3)
 */

#include "all_fractal_definitions.h"

cFractalThreex3VascularNetworkFractal::cFractalThreex3VascularNetworkFractal() : cAbstractFractal()
{
	nameInComboBox = "3x3 V453 Vascular Network Fractal";
	internalName = "threex3_vascular_network_fractal";
	internalID = fractal::threex3VascularNetworkFractal;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3VascularNetworkFractal::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Vascular Network Fractal: Murray's law: r_parent^3 = sum(r_daughter^3)
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	// Biological: branching tree pattern
	double branchAngle = fractal->transformCommon.scale1;
	if (branchAngle < 0.01) branchAngle = 0.5;
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	// Branch perturbation based on radius
	double branch = branchAngle * sin(3.0 * th) * cos(5.0 * ph) * exp(-r * 0.1);
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th + branch) * cos(ph) * rp;
	z.y = cos(th + branch) * sin(ph) * rp;
	z.z = sin(th + branch) * rp;
}
