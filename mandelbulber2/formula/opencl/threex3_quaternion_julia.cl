/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Quaternion Julia.
 */

REAL4 Threex3QuaternionJuliaIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Quaternion Julia: q = q² + c met q = a + bi + cj + dk
	// Quaternion-style multiplication with twist
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	// Higher-dim: quaternion square + perturbation
	REAL newX = z.x * z.x - z.y * z.y - z.z * z.z + fractal->transformCommon.offset0;
	REAL newY = 2.0 * z.x * z.y + fractal->transformCommon.offsetA0;
	REAL newZ = 2.0 * z.x * z.z + fractal->transformCommon.offsetB0;
	// Apply power scaling
	REAL scale = pow(r, power - 2.0);
	z.x = newX * scale;
	z.y = newY * scale;
	z.z = newZ * scale;
	aux->DE = aux->DE * power * pow(r, power - 1.0) + 1.0;
	return z;
}
