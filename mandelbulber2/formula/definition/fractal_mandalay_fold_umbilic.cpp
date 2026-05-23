/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Mandalay Fold: Navel in Mandalay Fold.
 * Math: z = z + D4_singularity * elliptic_hyperbolic * parabolic * ridge * subparabolic
 */

#include "all_fractal_definitions.h"

cFractalMandalayFoldUmbilic::cFractalMandalayFoldUmbilic() : cAbstractFractal()
{
	nameInComboBox = "Mandalay Fold V22 Umbilic";
	internalName = "mandalay_fold_umbilic";
	internalID = fractal::mandalayFoldUmbilic;
	DEType = analyticDEType;
	DEFunctionType = linearDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionLinear;
	coloringFunction = coloringFunctionDefault;
}

void cFractalMandalayFoldUmbilic::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Mandalay base: abs fold
	z = fabs(z);

	// Sort for Mandalay clip
	if (z.z > z.y) swap(z.y, z.z);
	if (z.y > z.x) swap(z.x, z.y);
	if (z.z > z.y) swap(z.y, z.z);

	// Umbilic fold: D4 singularity
	double s = fractal->transformCommon.scale08;
	double K1 = 1.0 / (fabs(z.x) + 1e-21);
	double K2 = 1.0 / (fabs(z.y) + 1e-21);
	double umbilic = K1 - K2;
	z.z += umbilic * s * 0.01;

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
