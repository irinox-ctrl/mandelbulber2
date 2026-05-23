/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Hyperbolische sinus-integraal Julia.
 * Math: z = Shi(z) + c = integral(sinh(t)/t) + c
 */

#include "all_fractal_definitions.h"

cFractalThreex3HyperbolicSineIntegralJulia::cFractalThreex3HyperbolicSineIntegralJulia() : cAbstractFractal()
{
	nameInComboBox = "3x3 V97 Hyperbolic Sine Integral Julia";
	internalName = "threex3_hyperbolic_sine_integral_julia";
	internalID = fractal::threex3HyperbolicSineIntegralJulia;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3HyperbolicSineIntegralJulia::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Hyperbolic Sine Integral Julia: z = Shi(z) + c = integral(sinh(t)/t) + c
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	// PDE-inspired: diffusion-reaction
	double laplacian = (z.x * z.x + z.y * z.y + z.z * z.z) * fractal->transformCommon.scale1;
	double reaction = sin(z.x) * cos(z.y) * sin(z.z);
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp + fractal->transformCommon.offset0 * reaction;
	z.y = cos(th) * sin(ph) * rp + fractal->transformCommon.offsetA0 * laplacian * 0.001;
	z.z = sin(th) * rp;
}
