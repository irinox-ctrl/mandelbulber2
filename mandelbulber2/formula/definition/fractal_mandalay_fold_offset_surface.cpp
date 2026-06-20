/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Mandalay Fold: Offset-oppervlak in Mandalay Fold.
 * Math: z = z + parallel * constant_distance * self_intersection * trimming * medial_axis
 */

#include "all_fractal_definitions.h"

cFractalMandalayFoldOffsetSurface::cFractalMandalayFoldOffsetSurface() : cAbstractFractal()
{
	nameInComboBox = "Mandalay Fold V31 Offset Surface";
	internalName = "mandalay_fold_offset_surface";
	internalID = fractal::mandalayFoldOffsetSurface;
	DEType = analyticDEType;
	DEFunctionType = linearDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionLinear;
	coloringFunction = coloringFunctionDefault;
}

void cFractalMandalayFoldOffsetSurface::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Mandalay base: abs fold
	z = fabs(z);

	// Sort for Mandalay clip
	if (z.z > z.y) swap(z.y, z.z);
	if (z.y > z.x) swap(z.x, z.y);
	if (z.z > z.y) swap(z.y, z.z);

	// Offset Surface fold: parallel surface
	double s = fractal->transformCommon.scale08;
	double r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
	double offset = 0.3;
	if (r > 1e-21) {
		z.x += z.x / r * offset * s;
		z.y += z.y / r * offset * s;
		z.z += z.z / r * offset * s;
	}

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
