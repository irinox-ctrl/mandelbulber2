/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Ikeda-afbeelding.
 */

REAL4 Threex3IkedaMapIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Ikeda Map: z = 1 + mu*z*exp(i*(0.4 - 6/(1 + |z|²)))
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	// Dynamic system: coupled oscillator map
	REAL a = fractal->transformCommon.scale1;
	if (a == 0.0) a = 1.4;
	REAL b = fractal->transformCommon.offset0;
	if (b == 0.0) b = 0.3;
	REAL newX = 1.0 - a * z.x * z.x + z.y;
	REAL newY = b * z.x + z.z * fractal->transformCommon.offsetA0;
	REAL newZ = sin(z.z * power) + z.x * fractal->transformCommon.offsetB0;
	aux->DE = aux->DE * fabs(2.0 * a * z.x) + 1.0;
	z.x = newX;
	z.y = newY;
	z.z = newZ;
	return z;
}
