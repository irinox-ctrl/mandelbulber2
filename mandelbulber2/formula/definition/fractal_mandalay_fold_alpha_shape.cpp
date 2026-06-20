/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Mandalay Fold: Alpha-vorm in Mandalay Fold.
 * Math: z = z + Edelsbrunner * union_of_disks * homotopy_type * filtration * persistent_homology
 */

#include "all_fractal_definitions.h"

cFractalMandalayFoldAlphaShape::cFractalMandalayFoldAlphaShape() : cAbstractFractal()
{
	nameInComboBox = "Mandalay Fold V40 Alpha Shape";
	internalName = "mandalay_fold_alpha_shape";
	internalID = fractal::mandalayFoldAlphaShape;
	DEType = analyticDEType;
	DEFunctionType = linearDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionLinear;
	coloringFunction = coloringFunctionDefault;
}

void cFractalMandalayFoldAlphaShape::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Mandalay base: abs fold
	z = fabs(z);

	// Sort for Mandalay clip
	if (z.z > z.y) swap(z.y, z.z);
	if (z.y > z.x) swap(z.x, z.y);
	if (z.z > z.y) swap(z.y, z.z);

	// Alpha Shape fold: filtration
	double s = fractal->transformCommon.scale08;
	double alpha = 1.0;
	double r2 = z.x*z.x + z.y*z.y + z.z*z.z;
	double inside = (r2 < alpha*alpha) ? 1.0 : 0.0;
	z.x = z.x * (1.0 - s) + z.x * inside * s;
	z.y = z.y * (1.0 - s) + z.y * inside * s;
	z.z = z.z * (1.0 - s) + z.z * inside * s;

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
