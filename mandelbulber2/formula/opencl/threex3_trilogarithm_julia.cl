/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Trilogaritme Julia.
 */

REAL4 Threex3TrilogarithmJuliaIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Trilogarithm Julia: z = Li_3(z) + c
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	REAL th = asin(z.z / r) * power;
	REAL ph = atan2(z.y, z.x) * power;
	// Elliptic function modulation
	REAL k = fractal->transformCommon.scale1;
	REAL sn = sin(th) / (1.0 + k * k * sin(th) * sin(th));
	REAL cn = cos(th) * sqrt(1.0 - k * k * sin(th) * sin(th) * 0.25);
	REAL rp = pow(r, power);
	aux->DE = power * pow(r, power - 1.0) * aux->DE + 1.0;
	z.x = cn * cos(ph) * rp;
	z.y = cn * sin(ph) * rp;
	z.z = sn * rp;
	return z;
}
