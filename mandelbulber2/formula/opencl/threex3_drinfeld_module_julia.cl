/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Drinfeld-module Julia.
 */

REAL4 Threex3DrinfeldModuleJuliaIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Drinfeld Module Julia: z = phi_T(z) + c met phi Drinfeld-module over functieveld
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	REAL th = asin(z.z / r) * power;
	REAL ph = atan2(z.y, z.x) * power;
	// Arithmetic dynamics: discrete floor modulation
	REAL gridScale = fractal->transformCommon.scale1;
	if (gridScale < 0.01) gridScale = 1.0;
	REAL fx = floor(z.x * gridScale + 0.5) / gridScale;
	REAL fy = floor(z.y * gridScale + 0.5) / gridScale;
	REAL discreteShift = fractal->transformCommon.offset0 * (fx * fx + fy * fy);
	REAL rp = pow(r, power);
	aux->DE = power * pow(r, power - 1.0) * aux->DE + 1.0;
	z.x = cos(th) * cos(ph) * rp + discreteShift * 0.01;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
	return z;
}
