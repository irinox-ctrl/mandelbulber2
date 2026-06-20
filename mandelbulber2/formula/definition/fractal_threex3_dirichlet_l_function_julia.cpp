/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Dirichlet L-functie Julia.
 * Math: z = L(s, chi) + c met karakter chi
 */

#include "all_fractal_definitions.h"

cFractalThreex3DirichletLFunctionJulia::cFractalThreex3DirichletLFunctionJulia() : cAbstractFractal()
{
	nameInComboBox = "3x3 V22 Dirichlet L-Function Julia";
	internalName = "threex3_dirichlet_l_function_julia";
	internalID = fractal::threex3DirichletLFunctionJulia;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3DirichletLFunctionJulia::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Dirichlet L-Function Julia: z = L(s, chi) + c met karakter chi
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	// Modular form twist: periodic perturbation
	double tau = fractal->transformCommon.scale1;
	double q = exp(-2.0 * M_PI * tau);
	double modTwist = 1.0 + 2.0 * q * cos(2.0 * M_PI * ph / (2.0 * M_PI));
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp * modTwist;
	z.y = cos(th) * sin(ph) * rp * modTwist;
	z.z = sin(th) * rp;
}
