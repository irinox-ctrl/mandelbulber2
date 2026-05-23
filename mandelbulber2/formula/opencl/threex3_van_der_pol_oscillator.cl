/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Van der Pol-oscillator.
 */

REAL4 Threex3VanDerPolOscillatorIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Van der Pol Oscillator: d²x/dt² - mu*(1-x²)*dx/dt + x = 0
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	// Flow: Rössler-type 3D attractor
	REAL a = fractal->transformCommon.scale1;
	if (a == 0.0) a = 0.2;
	REAL b = fractal->transformCommon.offset0;
	if (b == 0.0) b = 0.2;
	REAL c = fractal->transformCommon.offsetA0;
	if (c == 0.0) c = 5.7;
	REAL dt = 0.01 * power;
	REAL dx = -(z.y + z.z);
	REAL dy = z.x + a * z.y;
	REAL dz = b + z.z * (z.x - c);
	z.x += dx * dt;
	z.y += dy * dt;
	z.z += dz * dt;
	aux->DE = aux->DE * (1.0 + fabs(dt * (z.x - c))) + 0.01;
	return z;
}
