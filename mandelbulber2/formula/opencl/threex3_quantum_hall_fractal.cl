/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Kwantum Hall fractaal.
 */

REAL4 Threex3QuantumHallFractalIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Quantum Hall Fractal: sigma_xy = n*e²/h met Landau-niveaus
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	// Spin model: nearest-neighbor coupling
	REAL J = fractal->transformCommon.scale1;
	if (J == 0.0) J = 1.0;
	REAL coupling = J * (sin(z.x) * sin(z.y) + sin(z.y) * sin(z.z) + sin(z.z) * sin(z.x));
	REAL th = asin(z.z / r) * power;
	REAL ph = atan2(z.y, z.x) * power;
	REAL rp = pow(r, power);
	aux->DE = power * pow(r, power - 1.0) * aux->DE + 1.0;
	z.x = cos(th) * cos(ph) * rp + fractal->transformCommon.offset0 * coupling * 0.001;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
	return z;
}
