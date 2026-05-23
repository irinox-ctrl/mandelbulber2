/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Inverse sinus Julia.
 */

REAL4 Threex3InverseSineJuliaIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Inverse Sine Julia: z = arcsin(z) + c
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	// Hyperbolic: sinh/cosh iteration
	REAL sh = sinh(z.x * fractal->transformCommon.scale1);
	REAL ch = cosh(z.y * fractal->transformCommon.scale1);
	REAL newX = sh * ch + z.x;
	REAL newY = sin(z.y) * cosh(z.x * 0.5) + z.y;
	REAL newZ = z.z * power + tanh(z.z) * fractal->transformCommon.offset0;
	aux->DE = aux->DE * fabs(power * ch) + 1.0;
	z.x = newX;
	z.y = newY;
	z.z = newZ;
	return z;
}
