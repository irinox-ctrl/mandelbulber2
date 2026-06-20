/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Drinfeld-module Julia.
 * Math: z = phi_T(z) + c met phi Drinfeld-module over functieveld
 */

#include "all_fractal_definitions.h"

cFractalThreex3DrinfeldModuleJulia::cFractalThreex3DrinfeldModuleJulia() : cAbstractFractal()
{
	nameInComboBox = "3x3 V40 Drinfeld Module Julia";
	internalName = "threex3_drinfeld_module_julia";
	internalID = fractal::threex3DrinfeldModuleJulia;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3DrinfeldModuleJulia::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Drinfeld Module Julia: z = phi_T(z) + c met phi Drinfeld-module over functieveld
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	// Arithmetic dynamics: discrete floor modulation
	double gridScale = fractal->transformCommon.scale1;
	if (gridScale < 0.01) gridScale = 1.0;
	double fx = floor(z.x * gridScale + 0.5) / gridScale;
	double fy = floor(z.y * gridScale + 0.5) / gridScale;
	double discreteShift = fractal->transformCommon.offset0 * (fx * fx + fy * fy);
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp + discreteShift * 0.01;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
}
