/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Mandalay Fold: Morfologische dilatie in Mandalay Fold.
 * Math: z = z + Minkowski_sum * structuring_element * image_processing * opening * closing
 */

#include "all_fractal_definitions.h"

cFractalMandalayFoldMorphologicalDilation::cFractalMandalayFoldMorphologicalDilation() : cAbstractFractal()
{
	nameInComboBox = "Mandalay Fold V33 Morphological Dilation";
	internalName = "mandalay_fold_morphological_dilation";
	internalID = fractal::mandalayFoldMorphologicalDilation;
	DEType = analyticDEType;
	DEFunctionType = linearDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionLinear;
	coloringFunction = coloringFunctionDefault;
}

void cFractalMandalayFoldMorphologicalDilation::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Mandalay base: abs fold
	z = fabs(z);

	// Sort for Mandalay clip
	if (z.z > z.y) swap(z.y, z.z);
	if (z.y > z.x) swap(z.x, z.y);
	if (z.z > z.y) swap(z.y, z.z);

	// Morphological Dilation fold
	double s = fractal->transformCommon.scale08;
	double se = 0.3;
	z.x = max(z.x, se) * s + z.x * (1.0 - s);
	z.y = max(z.y, se) * s + z.y * (1.0 - s);
	z.z = max(z.z, se) * s + z.z * (1.0 - s);

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
