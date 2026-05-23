/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Stirling-getal fractaal.
 */

REAL4 Threex3StirlingNumberFractalIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Stirling Number Fractal: z = S(z,k) + c of s(z,k) + c
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	// Number theory: Collatz-inspired branching
	REAL th = asin(z.z / r) * power;
	REAL ph = atan2(z.y, z.x) * power;
	REAL rp = pow(r, power);
	// Parity-based perturbation
	int parity = ((int)floor(fabs(z.x * 100.0))) % 2;
	REAL shift = parity ? fractal->transformCommon.scale1 * 0.01 : -fractal->transformCommon.scale1 * 0.01;
	aux->DE = power * pow(r, power - 1.0) * aux->DE + 1.0;
	z.x = cos(th) * cos(ph) * rp + shift;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
	return z;
}
