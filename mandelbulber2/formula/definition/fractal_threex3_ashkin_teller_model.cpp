/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Ashkin-Teller-model.
 * Math: H = -J*sum(sigma_i*sigma_j) - K*sum(tau_i*tau_j) - L*sum(sigma_i*sigma_j*tau_i*tau_j)
 */

#include "all_fractal_definitions.h"

cFractalThreex3AshkinTellerModel::cFractalThreex3AshkinTellerModel() : cAbstractFractal()
{
	nameInComboBox = "3x3 V275 Ashkin-Teller Model";
	internalName = "threex3_ashkin_teller_model";
	internalID = fractal::threex3AshkinTellerModel;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3AshkinTellerModel::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Ashkin-Teller Model: H = -J*sum(sigma_i*sigma_j) - K*sum(tau_i*tau_j) - L*sum(sigma_i*sigma_j*tau_i*tau_j)
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	// Growth: aggregation-inspired radial modulation
	double growthRate = fractal->transformCommon.scale1;
	if (growthRate < 0.01) growthRate = 0.5;
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	// Radial fluctuation based on angle
	double fluct = 1.0 + growthRate * 0.1 * sin(5.0 * th) * cos(7.0 * ph);
	double rp = pow(r, power) * fluct;
	aux.DE = power * pow(r, power - 1.0) * fluct * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
}
