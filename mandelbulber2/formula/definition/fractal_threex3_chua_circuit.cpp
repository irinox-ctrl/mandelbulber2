/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Chua-circuit.
 * Math: dx/dt = alpha*(y - x - f(x)), dy/dt = x - y + z, dz/dt = -beta*y met f(x) = m1*x + 0.5*(m0-m1)*(|x+1| - |x-1|)
 */

#include "all_fractal_definitions.h"

cFractalThreex3ChuaCircuit::cFractalThreex3ChuaCircuit() : cAbstractFractal()
{
	nameInComboBox = "3x3 V223 Chua Circuit";
	internalName = "threex3_chua_circuit";
	internalID = fractal::threex3ChuaCircuit;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3ChuaCircuit::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Chua Circuit: dx/dt = alpha*(y - x - f(x)), dy/dt = x - y + z, dz/dt = -beta*y met f(x) = m1*x + 0.5*(m0-m1)*(|x+1| - |x-1|)
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	// Flow: Rössler-type 3D attractor
	double a = fractal->transformCommon.scale1;
	if (a == 0.0) a = 0.2;
	double b = fractal->transformCommon.offset0;
	if (b == 0.0) b = 0.2;
	double c = fractal->transformCommon.offsetA0;
	if (c == 0.0) c = 5.7;
	double dt = 0.01 * power;
	double dx = -(z.y + z.z);
	double dy = z.x + a * z.y;
	double dz = b + z.z * (z.x - c);
	z.x += dx * dt;
	z.y += dy * dt;
	z.z += dz * dt;
	aux.DE = aux.DE * (1.0 + fabs(dt * (z.x - c))) + 0.01;
}
