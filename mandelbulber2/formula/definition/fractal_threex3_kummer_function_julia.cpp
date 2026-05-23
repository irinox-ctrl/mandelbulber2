/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Kummer-functie Julia.
 * Math: z = 1F1(a;b;z) + c — confluente hypergeometrisch
 */

#include "all_fractal_definitions.h"

cFractalThreex3KummerFunctionJulia::cFractalThreex3KummerFunctionJulia() : cAbstractFractal()
{
	nameInComboBox = "3x3 V79 Kummer Function Julia";
	internalName = "threex3_kummer_function_julia";
	internalID = fractal::threex3KummerFunctionJulia;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3KummerFunctionJulia::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Kummer Function Julia: z = 1F1(a;b;z) + c — confluente hypergeometrisch
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	// Elliptic function modulation
	double k = fractal->transformCommon.scale1;
	double sn = sin(th) / (1.0 + k * k * sin(th) * sin(th));
	double cn = cos(th) * sqrt(1.0 - k * k * sin(th) * sin(th) * 0.25);
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cn * cos(ph) * rp;
	z.y = cn * sin(ph) * rp;
	z.z = sn * rp;
}
