/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Aliquot-reeks fractaal.
 */

REAL4 Threex3AliquotSequenceFractalIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Aliquot Sequence Fractal: s(n) = sigma(n) - n, z = s(z) + c
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	REAL th = asin(z.z / r) * power;
	REAL ph = atan2(z.y, z.x) * power;
	// Arithmetic: prime-like sieve modulation
	REAL freq = max(1.0, fractal->transformCommon.scale1);
	REAL sieve = 0.0;
	for (int p = 2; p <= 7; p++)
		sieve += sin(freq * p * th) / (double)p;
	REAL rp = pow(r, power);
	aux->DE = power * pow(r, power - 1.0) * aux->DE + 1.0;
	z.x = cos(th + sieve * 0.02) * cos(ph) * rp;
	z.y = cos(th + sieve * 0.02) * sin(ph) * rp;
	z.z = sin(th + sieve * 0.02) * rp;
	return z;
}
