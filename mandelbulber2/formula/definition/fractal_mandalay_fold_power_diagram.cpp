/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Mandalay Fold: Vermogendiagram in Mandalay Fold.
 * Math: z = z + weighted_Voronoi * radical_axis * sphere_packing * Laguerre * additively_weighted
 */

#include "all_fractal_definitions.h"

cFractalMandalayFoldPowerDiagram::cFractalMandalayFoldPowerDiagram() : cAbstractFractal()
{
	nameInComboBox = "Mandalay Fold V38 Power Diagram";
	internalName = "mandalay_fold_power_diagram";
	internalID = fractal::mandalayFoldPowerDiagram;
	DEType = analyticDEType;
	DEFunctionType = linearDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionLinear;
	coloringFunction = coloringFunctionDefault;
}

void cFractalMandalayFoldPowerDiagram::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Mandalay base: abs fold
	z = fabs(z);

	// Sort for Mandalay clip
	if (z.z > z.y) swap(z.y, z.z);
	if (z.y > z.x) swap(z.x, z.y);
	if (z.z > z.y) swap(z.y, z.z);

	// Power Diagram fold: weighted Voronoi
	double s = fractal->transformCommon.scale08;
	double w1 = 1.0; double w2 = 0.7;
	double d1 = z.x*z.x + z.y*z.y + z.z*z.z - w1;
	double d2 = (z.x-1.0)*(z.x-1.0) + z.y*z.y + z.z*z.z - w2;
	double blend = 1.0 / (1.0 + exp(-(d1 - d2) * 5.0));
	z.x = z.x * (1.0 - blend * s) + (z.x - 0.5) * blend * s;

	// Spherical fold
	double rr = z.Dot(z);
	if (rr < fractal->transformCommon.minR2p25)
	{
		double tglad_factor1 = fractal->transformCommon.maxR2d1 / fractal->transformCommon.minR2p25;
		z *= tglad_factor1;
		aux.DE *= tglad_factor1;
	}
	else if (rr < fractal->transformCommon.maxR2d1)
	{
		double tglad_factor2 = fractal->transformCommon.maxR2d1 / rr;
		z *= tglad_factor2;
		aux.DE *= tglad_factor2;
	}

	// Scale
	double useScale = fractal->transformCommon.scale2;
	z *= useScale;
	aux.DE = aux.DE * fabs(useScale) + 1.0;

	// Rotation
	if (fractal->transformCommon.rotationEnabled)
	{
		z = fractal->transformCommon.rotationMatrix.RotateVector(z);
	}
}
