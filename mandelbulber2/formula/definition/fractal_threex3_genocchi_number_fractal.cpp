/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Genocchi-getal fractaal.
 * Math: z = G_z + c met Genocchi-getallen
 */

#include "all_fractal_definitions.h"

cFractalThreex3GenocchiNumberFractal::cFractalThreex3GenocchiNumberFractal() : cAbstractFractal()
{
	nameInComboBox = "3x3 V345 Genocchi Number Fractal";
	internalName = "threex3_genocchi_number_fractal";
	internalID = fractal::threex3GenocchiNumberFractal;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3GenocchiNumberFractal::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Genocchi Number Fractal: z = G_z + c met Genocchi-getallen
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	// Continued fraction: golden ratio modulation
	double golden = 1.6180339887;
	double cfrac = fractal->transformCommon.scale1 * sin(golden * th) * cos(golden * ph);
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp + cfrac * 0.01;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
}
