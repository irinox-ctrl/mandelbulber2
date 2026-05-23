/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Cerf-theorie Julia.
 */

REAL4 Threex3CerfTheoryJuliaIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Cerf Theory Julia: z = z² + c met generieke 1-parameter familie
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	// Symplectic twist map
	REAL q1 = z.x; REAL p1 = z.y; REAL q2 = z.z;
	REAL K = fractal->transformCommon.scale1;
	REAL newP = p1 + K * sin(2.0 * M_PI_F * q1);
	REAL newQ = q1 + newP;
	REAL th = asin(q2 / r) * power;
	REAL ph = atan2(newP, newQ) * power;
	REAL rp = pow(r, power);
	aux->DE = power * pow(r, power - 1.0) * aux->DE + 1.0;
	z.x = cos(th) * cos(ph) * rp;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
	return z;
}
