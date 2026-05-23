/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Voevodsky-motief Julia.
 * Math: M = M² + C in DM(k) trianguleerde motive categorie
 */

#include "all_fractal_definitions.h"

cFractalThreex3VoevodskyMotiveJulia::cFractalThreex3VoevodskyMotiveJulia() : cAbstractFractal()
{
	nameInComboBox = "3x3 V137 Voevodsky Motive Julia";
	internalName = "threex3_voevodsky_motive_julia";
	internalID = fractal::threex3VoevodskyMotiveJulia;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3VoevodskyMotiveJulia::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Voevodsky Motive Julia: M = M² + C in DM(k) trianguleerde motive categorie
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	// Categorical functor: apply morphism
	double twist = fractal->transformCommon.scale1;
	double functor = sin(twist * r) * cos(twist * th);
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph + functor * 0.1) * rp;
	z.y = cos(th) * sin(ph + functor * 0.1) * rp;
	z.z = sin(th) * rp;
}
