/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Mandalay Fold: Kanaaloppervlak in Mandalay Fold.
 * Math: z = z + envelope_of_spheres * spine_curve * Dupin_cyclide * pipe_surface
 */

#include "all_fractal_definitions.h"

cFractalMandalayFoldChannelSurface::cFractalMandalayFoldChannelSurface() : cAbstractFractal()
{
	nameInComboBox = "Mandalay Fold V29 Channel Surface";
	internalName = "mandalay_fold_channel_surface";
	internalID = fractal::mandalayFoldChannelSurface;
	DEType = analyticDEType;
	DEFunctionType = linearDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionLinear;
	coloringFunction = coloringFunctionDefault;
}

void cFractalMandalayFoldChannelSurface::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Mandalay base: abs fold
	z = fabs(z);

	// Sort for Mandalay clip
	if (z.z > z.y) swap(z.y, z.z);
	if (z.y > z.x) swap(z.x, z.y);
	if (z.z > z.y) swap(z.y, z.z);

	// Channel Surface fold: envelope of spheres
	double s = fractal->transformCommon.scale08;
	double t = atan2(z.y, z.x);
	double spine_r = 1.0 + 0.3 * sin(t * 3.0);
	double rxy = sqrt(z.x*z.x + z.y*z.y);
	double diff = rxy - spine_r;
	z.x += diff * cos(t) * s * 0.5;
	z.y += diff * sin(t) * s * 0.5;

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
