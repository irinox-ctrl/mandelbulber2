/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Knoop-complement Julia.
 * Math: z = z² + c op S³ \ K knoop-complement
 */

#include "all_fractal_definitions.h"

cFractalThreex3KnotComplementJulia::cFractalThreex3KnotComplementJulia() : cAbstractFractal()
{
	nameInComboBox = "3x3 V151 Knot Complement Julia";
	internalName = "threex3_knot_complement_julia";
	internalID = fractal::threex3KnotComplementJulia;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3KnotComplementJulia::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Knot Complement Julia: z = z² + c op S³ \ K knoop-complement
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	// Knot/manifold twist: toroidal mapping
	double R = fractal->transformCommon.scale1;
	if (R < 0.1) R = 2.0;
	double theta = atan2(z.y, z.x);
	double rxy = sqrt(z.x * z.x + z.y * z.y);
	double phi = atan2(z.z, rxy - R);
	double rTube = sqrt((rxy - R) * (rxy - R) + z.z * z.z);
	// Power map on torus
	theta *= power;
	phi *= power;
	rTube = pow(rTube, power);
	double newRxy = R + rTube * cos(phi);
	z.x = newRxy * cos(theta);
	z.y = newRxy * sin(theta);
	z.z = rTube * sin(phi);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
}
