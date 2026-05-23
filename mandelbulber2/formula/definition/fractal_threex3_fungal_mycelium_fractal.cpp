/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Schimmel-mycelium fractaal.
 * Math: hyphal_tip_growth + branching + anastomosis
 */

#include "all_fractal_definitions.h"

cFractalThreex3FungalMyceliumFractal::cFractalThreex3FungalMyceliumFractal() : cAbstractFractal()
{
	nameInComboBox = "3x3 V495 Fungal Mycelium Fractal";
	internalName = "threex3_fungal_mycelium_fractal";
	internalID = fractal::threex3FungalMyceliumFractal;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3FungalMyceliumFractal::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Fungal Mycelium Fractal: hyphal_tip_growth + branching + anastomosis
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	// Crystal: faceted growth
	double symmetry = fractal->transformCommon.scale1;
	if (symmetry < 2.0) symmetry = 6.0;
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	// Faceting via angular quantization
	double phQ = round(ph * symmetry / (2.0 * M_PI)) * 2.0 * M_PI / symmetry;
	double blend = fractal->transformCommon.offset0;
	if (blend == 0.0) blend = 0.1;
	ph = ph * (1.0 - blend) + phQ * blend;
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
}
