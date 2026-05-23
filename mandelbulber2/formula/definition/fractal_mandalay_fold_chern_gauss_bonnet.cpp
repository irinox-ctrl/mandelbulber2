/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Mandalay Fold: Chern-Gauss-Bonnet in Mandalay Fold.
 * Math: z = z + integral(Pfaffian) = chi * Chern * characteristic_form * even_dimensional
 */

#include "all_fractal_definitions.h"

cFractalMandalayFoldChernGaussBonnet::cFractalMandalayFoldChernGaussBonnet() : cAbstractFractal()
{
	nameInComboBox = "Mandalay Fold V45 Chern-Gauss-Bonnet";
	internalName = "mandalay_fold_chern_gauss_bonnet";
	internalID = fractal::mandalayFoldChernGaussBonnet;
	DEType = analyticDEType;
	DEFunctionType = linearDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionLinear;
	coloringFunction = coloringFunctionDefault;
}

void cFractalMandalayFoldChernGaussBonnet::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Mandalay base: abs fold
	z = fabs(z);

	// Sort for Mandalay clip
	if (z.z > z.y) swap(z.y, z.z);
	if (z.y > z.x) swap(z.x, z.y);
	if (z.z > z.y) swap(z.y, z.z);

	// Chern-Gauss-Bonnet fold: Pfaffian integral
	double s = fractal->transformCommon.scale08;
	double r2 = z.x*z.x + z.y*z.y + z.z*z.z;
	double pf = (z.x*z.y - z.y*z.x) + (z.y*z.z - z.z*z.y);
	double cgb = 1.0 / (r2 + 1.0);
	z.x *= (1.0 + cgb * s);
	z.y *= (1.0 + cgb * s);
	z.z *= (1.0 - cgb * s);

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
