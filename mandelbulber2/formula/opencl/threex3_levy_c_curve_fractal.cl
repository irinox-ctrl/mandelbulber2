/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Lévy C-kromme fractaal.
 */

REAL4 Threex3LevyCCurveFractalIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Levy C Curve Fractal: z = levy_replace(z, angle) + c
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	// L-system: branch-and-rotate
	REAL angle = fractal->transformCommon.scale1 * M_PI_F / 6.0;
	if (angle == 0.0) angle = M_PI_F / 6.0;
	REAL ca = cos(angle); REAL sa = sin(angle);
	// Apply rotation based on iteration parity
	if (aux->i % 2 == 0) {
		REAL tmp = z.x * ca - z.y * sa;
		z.y = z.x * sa + z.y * ca;
		z.x = tmp;
	} else {
		REAL tmp = z.y * ca - z.z * sa;
		z.z = z.y * sa + z.z * ca;
		z.y = tmp;
	}
	REAL th = asin(z.z / r) * power;
	REAL ph = atan2(z.y, z.x) * power;
	REAL rp = pow(r, power);
	aux->DE = power * pow(r, power - 1.0) * aux->DE + 1.0;
	z.x = cos(th) * cos(ph) * rp;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
	return z;
}
