/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Sinus Julia.
 */

REAL4 Threex3SineJuliaIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Sine Julia: z = sin(z) + c
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	// Transcendental: exp-sin-cos iteration
	REAL ex = exp(z.x * fractal->transformCommon.scale1);
	REAL newX = ex * cos(z.y) - z.z * fractal->transformCommon.offset0;
	REAL newY = ex * sin(z.y) + z.z * fractal->transformCommon.offsetA0;
	REAL newZ = z.z * cos(z.x * 0.5) + sin(z.y * 0.5) * fractal->transformCommon.scaleC1;
	aux->DE = aux->DE * power * r + 1.0;
	z.x = newX;
	z.y = newY;
	z.z = newZ;
	return z;
}
