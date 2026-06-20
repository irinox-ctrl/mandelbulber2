/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Mullins-vergelijking.
 */

REAL4 Threex3MullinsEquationIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Mullins Equation: h_t = -nu*h_xxxx + eta
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	// Statistical: Boltzmann-inspired energy landscape
	REAL beta = fractal->transformCommon.scale1;
	if (beta < 0.01) beta = 1.0;
	REAL energy = z.x * z.x + z.y * z.y + z.z * z.z;
	REAL boltz = exp(-beta * energy * 0.01);
	REAL th = asin(z.z / r) * power;
	REAL ph = atan2(z.y, z.x) * power;
	REAL rp = pow(r, power) * (1.0 + fractal->transformCommon.offset0 * boltz * 0.1);
	aux->DE = power * pow(r, power - 1.0) * aux->DE + 1.0;
	z.x = cos(th) * cos(ph) * rp;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
	return z;
}
