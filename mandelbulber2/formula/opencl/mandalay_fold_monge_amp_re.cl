/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Mandalay Fold: Monge-Ampère-vergelijking in Mandalay Fold.
 */

REAL4 MandalayFoldMongeAmpreIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Mandalay base: abs fold
	z = fabs(z);

	// Sort for Mandalay clip
	REAL tmp;
	if (z.z > z.y) { tmp = z.y; z.y = z.z; z.z = tmp; }
	if (z.y > z.x) { tmp = z.x; z.x = z.y; z.y = tmp; }
	if (z.z > z.y) { tmp = z.y; z.y = z.z; z.z = tmp; }

	// Monge-Ampere fold: nonlinear elliptic PDE
	REAL hxx = 2.0; REAL hyy = 2.0; REAL hzz = 2.0;
	REAL hxy = z.x * z.y; REAL hxz = z.x * z.z; REAL hyz = z.y * z.z;
	REAL det = hxx*(hyy*hzz - hyz*hyz) - hxy*(hxy*hzz - hyz*hxz) + hxz*(hxy*hyz - hyy*hxz);
	REAL s = fractal->transformCommon.scale08;
	z.x += det * z.x * s * 0.01;
	z.y += det * z.y * s * 0.01;
	z.z += det * z.z * s * 0.01;

	// Spherical fold
	REAL rr = dot(z, z);
	if (rr < fractal->transformCommon.minR2p25)
	{
		REAL tglad_factor1 = fractal->transformCommon.maxR2d1 / fractal->transformCommon.minR2p25;
		z *= tglad_factor1;
		aux->DE *= tglad_factor1;
	}
	else if (rr < fractal->transformCommon.maxR2d1)
	{
		REAL tglad_factor2 = fractal->transformCommon.maxR2d1 / rr;
		z *= tglad_factor2;
		aux->DE *= tglad_factor2;
	}

	// Scale
	REAL useScale = fractal->transformCommon.scale2;
	z *= useScale;
	aux->DE = aux->DE * fabs(useScale) + 1.0f;

	return z;
}
