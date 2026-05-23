/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Golf-oppervlak Julia.
 * Math: z = z² + c op incompressible oppervlak
 */

#include "all_fractal_definitions.h"

cFractalThreex3WaveSurfaceJulia::cFractalThreex3WaveSurfaceJulia() : cAbstractFractal()
{
	nameInComboBox = "3x3 V187 Wave Surface Julia";
	internalName = "threex3_wave_surface_julia";
	internalID = fractal::threex3WaveSurfaceJulia;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3WaveSurfaceJulia::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Wave Surface Julia: z = z² + c op incompressible oppervlak
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
