/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Pauwenveer fractaal.
 * Math: eye_pattern + iridescence_structure
 */

#include "all_fractal_definitions.h"

cFractalThreex3PeacockFeatherFractal::cFractalThreex3PeacockFeatherFractal() : cAbstractFractal()
{
	nameInComboBox = "3x3 V463 Peacock Feather Fractal";
	internalName = "threex3_peacock_feather_fractal";
	internalID = fractal::threex3PeacockFeatherFractal;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3PeacockFeatherFractal::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Peacock Feather Fractal: eye_pattern + iridescence_structure
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
