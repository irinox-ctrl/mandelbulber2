/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Erdős-Borwein-constante fractaal.
 * Math: E = sum(1/(2^n - 1)) — irrationaal
 */

#include "all_fractal_definitions.h"

cFractalThreex3ErdosBorweinConstantFractal::cFractalThreex3ErdosBorweinConstantFractal() : cAbstractFractal()
{
	nameInComboBox = "3x3 V446 Erdos-Borwein Constant Fractal";
	internalName = "threex3_erdos_borwein_constant_fractal";
	internalID = fractal::threex3ErdosBorweinConstantFractal;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3ErdosBorweinConstantFractal::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Erdos-Borwein Constant Fractal: E = sum(1/(2^n - 1)) — irrationaal
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	// Wave equation: standing wave modulation
	double k_wave = fractal->transformCommon.scale1;
	if (k_wave < 0.1) k_wave = 2.0;
	double standing = sin(k_wave * r) * cos(k_wave * th);
	double rp = pow(r, power) * (1.0 + fractal->transformCommon.offset0 * standing * 0.01);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
}
