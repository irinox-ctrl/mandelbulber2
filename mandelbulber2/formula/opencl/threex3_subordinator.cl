/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Subordinator.
 */

REAL4 Threex3SubordinatorIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Subordinator: T(t) stijgend Lévy-proces met T(0) = 0
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	// Stochastic: deterministic chaos via tent map coupling
	REAL s = fractal->transformCommon.scale1;
	if (s < 0.01) s = 1.5;
	REAL tent_x = s * (1.0 - 2.0 * fabs(fmod(z.x, 1.0) - 0.5));
	REAL tent_y = s * (1.0 - 2.0 * fabs(fmod(z.y, 1.0) - 0.5));
	REAL th = asin(z.z / r) * power;
	REAL ph = atan2(z.y + tent_y * 0.01, z.x + tent_x * 0.01) * power;
	REAL rp = pow(r, power);
	aux->DE = power * pow(r, power - 1.0) * aux->DE + 1.0;
	z.x = cos(th) * cos(ph) * rp;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
	return z;
}
