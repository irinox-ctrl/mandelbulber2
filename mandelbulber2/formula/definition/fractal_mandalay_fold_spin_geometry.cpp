/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Mandalay Fold: Spin-meetkunde in Mandalay Fold.
 * Math: z = z + spin_structure * spinor_bundle * Clifford_algebra * Dirac_operator * twistor
 */

#include "all_fractal_definitions.h"

cFractalMandalayFoldSpinGeometry::cFractalMandalayFoldSpinGeometry() : cAbstractFractal()
{
	nameInComboBox = "Mandalay Fold V48 Spin Geometry";
	internalName = "mandalay_fold_spin_geometry";
	internalID = fractal::mandalayFoldSpinGeometry;
	DEType = analyticDEType;
	DEFunctionType = linearDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionLinear;
	coloringFunction = coloringFunctionDefault;
}

void cFractalMandalayFoldSpinGeometry::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Mandalay base: abs fold
	z = fabs(z);

	// Sort for Mandalay clip
	if (z.z > z.y) swap(z.y, z.z);
	if (z.y > z.x) swap(z.x, z.y);
	if (z.z > z.y) swap(z.y, z.z);

	// Spin Geometry fold: spinor bundle
	double s = fractal->transformCommon.scale08;
	double r = sqrt(z.x*z.x + z.y*z.y + z.z*z.z);
	double theta = atan2(z.y, z.x);
	z.x += s * 0.1 * cos(theta * 0.5) * r;
	z.y += s * 0.1 * sin(theta * 0.5) * r;
	z.z *= (1.0 + s * 0.05);

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
