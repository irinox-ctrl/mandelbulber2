/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Mandalay Fold: Monge-Ampère-vergelijking in Mandalay Fold.
 * Math: z = z + det(D²u) = f * Caffarelli * Nirenberg * Krylov
 */

#include "all_fractal_definitions.h"

cFractalMandalayFoldMongeAmpre::cFractalMandalayFoldMongeAmpre() : cAbstractFractal()
{
	nameInComboBox = "Mandalay Fold V7 Monge-Ampère";
	internalName = "mandalay_fold_monge_amp_re";
	internalID = fractal::mandalayFoldMongeAmpre;
	DEType = analyticDEType;
	DEFunctionType = linearDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionLinear;
	coloringFunction = coloringFunctionDefault;
}

void cFractalMandalayFoldMongeAmpre::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Mandalay base: abs fold
	z = fabs(z);

	// Sort for Mandalay clip
	if (z.z > z.y) swap(z.y, z.z);
	if (z.y > z.x) swap(z.x, z.y);
	if (z.z > z.y) swap(z.y, z.z);

	// Monge-Ampere fold: nonlinear elliptic PDE
	double hxx = 2.0; double hyy = 2.0; double hzz = 2.0;
	double hxy = z.x * z.y; double hxz = z.x * z.z; double hyz = z.y * z.z;
	double det = hxx*(hyy*hzz - hyz*hyz) - hxy*(hxy*hzz - hyz*hxz) + hxz*(hxy*hyz - hyy*hxz);
	double s = fractal->transformCommon.scale08;
	z.x += det * z.x * s * 0.01;
	z.y += det * z.y * s * 0.01;
	z.z += det * z.z * s * 0.01;

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
