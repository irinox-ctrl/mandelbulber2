/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Spectrale Julia.
 */

REAL4 Threex3SpectralJuliaIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Spectral Julia: E = E² + C met spectraal schema
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	// Clifford algebra rotation
	REAL angle = fractal->transformCommon.scale1 * M_PI_F;
	REAL ca = cos(angle); REAL sa = sin(angle);
	REAL rx = z.x * ca - z.y * sa;
	REAL ry = z.x * sa + z.y * ca;
	REAL th = asin(z.z / r) * power;
	REAL ph = atan2(ry, rx) * power;
	REAL rp = pow(r, power);
	aux->DE = power * pow(r, power - 1.0) * aux->DE + 1.0;
	z.x = cos(th) * cos(ph) * rp;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
	return z;
}
