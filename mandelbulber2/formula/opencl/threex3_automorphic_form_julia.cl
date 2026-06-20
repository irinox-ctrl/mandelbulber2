/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Automorfe vorm Julia.
 */

REAL4 Threex3AutomorphicFormJuliaIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Automorphic Form Julia: z = f(gamma*z) = j(gamma,z)^k * f(z) + c
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	REAL th = asin(z.z / r) * power;
	REAL ph = atan2(z.y, z.x) * power;
	// Modular form twist: periodic perturbation
	REAL tau = fractal->transformCommon.scale1;
	REAL q = exp(-2.0 * M_PI_F * tau);
	REAL modTwist = 1.0 + 2.0 * q * cos(2.0 * M_PI_F * ph / (2.0 * M_PI_F));
	REAL rp = pow(r, power);
	aux->DE = power * pow(r, power - 1.0) * aux->DE + 1.0;
	z.x = cos(th) * cos(ph) * rp * modTwist;
	z.y = cos(th) * sin(ph) * rp * modTwist;
	z.z = sin(th) * rp;
	return z;
}
