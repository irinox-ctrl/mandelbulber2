/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Aardbevingsbreuk fractaal.
 */

REAL4 Threex3EarthquakeFaultFractalIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Earthquake Fault Fractal: self-organized_criticality + Gutenberg-Richter
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	// Reaction-diffusion: Turing pattern
	REAL Da = fractal->transformCommon.scale1;
	if (Da < 0.01) Da = 1.0;
	REAL f_rate = fractal->transformCommon.offset0;
	if (f_rate == 0.0) f_rate = 0.04;
	REAL k_rate = fractal->transformCommon.offsetA0;
	if (k_rate == 0.0) k_rate = 0.06;
	// Gray-Scott inspired perturbation
	REAL u = 0.5 + 0.5 * sin(z.x * 3.0);
	REAL v = 0.5 + 0.5 * cos(z.y * 3.0);
	REAL reaction = -u * v * v + f_rate * (1.0 - u);
	REAL th = asin(z.z / r) * power;
	REAL ph = atan2(z.y, z.x) * power;
	REAL rp = pow(r, power);
	aux->DE = power * pow(r, power - 1.0) * aux->DE + 1.0;
	z.x = cos(th) * cos(ph) * rp + Da * reaction * 0.001;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
	return z;
}
