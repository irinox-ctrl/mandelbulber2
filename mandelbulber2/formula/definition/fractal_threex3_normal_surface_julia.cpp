/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Normaal oppervlak Julia.
 * Math: z = z² + c met normale positie t.o.v. triangulatie
 */

#include "all_fractal_definitions.h"

cFractalThreex3NormalSurfaceJulia::cFractalThreex3NormalSurfaceJulia() : cAbstractFractal()
{
	nameInComboBox = "3x3 V189 Normal Surface Julia";
	internalName = "threex3_normal_surface_julia";
	internalID = fractal::threex3NormalSurfaceJulia;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3NormalSurfaceJulia::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Normal Surface Julia: z = z² + c met normale positie t.o.v. triangulatie
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	// Heegaard splitting: genus twist
	double genus = max(1.0, fractal->transformCommon.scale1);
	double split = sin(genus * th) * cos(genus * ph);
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp + split * fractal->transformCommon.offset0 * 0.01;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
}
