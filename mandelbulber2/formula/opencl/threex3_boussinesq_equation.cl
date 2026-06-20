/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Boussinesq-vergelijking.
 */

REAL4 Threex3BoussinesqEquationIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Boussinesq Equation: u_tt - u_xx - (u²)_xx - u_xxxx = 0
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	// Neural: sigmoid activation with coupling
	REAL w1 = fractal->transformCommon.scale1;
	REAL w2 = fractal->transformCommon.offset0;
	REAL sigmoid_x = 1.0 / (1.0 + exp(-w1 * z.x));
	REAL sigmoid_y = 1.0 / (1.0 + exp(-w1 * z.y));
	REAL sigmoid_z = 1.0 / (1.0 + exp(-w1 * z.z));
	REAL th = asin(z.z / r) * power;
	REAL ph = atan2(z.y, z.x) * power;
	REAL rp = pow(r, power);
	aux->DE = power * pow(r, power - 1.0) * aux->DE + 1.0;
	z.x = cos(th) * cos(ph) * rp + w2 * (sigmoid_x - 0.5);
	z.y = cos(th) * sin(ph) * rp + w2 * (sigmoid_y - 0.5);
	z.z = sin(th) * rp + w2 * (sigmoid_z - 0.5);
	return z;
}
