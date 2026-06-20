/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Model-set fractaal.
 * Math: Lambda = {pi_parallel(x) : x in L, pi_perp(x) in W}
 */

#include "all_fractal_definitions.h"

cFractalThreex3ModelSetFractal::cFractalThreex3ModelSetFractal() : cAbstractFractal()
{
	nameInComboBox = "3x3 V419 Model Set Fractal";
	internalName = "threex3_model_set_fractal";
	internalID = fractal::threex3ModelSetFractal;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3ModelSetFractal::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Model Set Fractal: Lambda = {pi_parallel(x) : x in L, pi_perp(x) in W}
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	// Spin model: nearest-neighbor coupling
	double J = fractal->transformCommon.scale1;
	if (J == 0.0) J = 1.0;
	double coupling = J * (sin(z.x) * sin(z.y) + sin(z.y) * sin(z.z) + sin(z.z) * sin(z.x));
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp + fractal->transformCommon.offset0 * coupling * 0.001;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
}
