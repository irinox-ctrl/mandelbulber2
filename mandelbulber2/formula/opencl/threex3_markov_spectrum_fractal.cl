/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Markov-spectrum fractaal.
 */

REAL4 Threex3MarkovSpectrumFractalIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Markov Spectrum Fractal: m(x) = inf(q*||qx||) voor irrationaal x
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	// Quasicrystal: 5-fold symmetry superposition
	REAL th = asin(z.z / r) * power;
	REAL ph = atan2(z.y, z.x) * power;
	REAL quasi = 0.0;
	int folds = max(3, (int)(fractal->transformCommon.scale1));
	if (folds > 12) folds = 12;
	for (int k = 0; k < folds; k++)
		quasi += cos(z.x * cos(k * M_PI_F / folds) + z.y * sin(k * M_PI_F / folds));
	REAL rp = pow(r, power) * (1.0 + fractal->transformCommon.offset0 * quasi * 0.001);
	aux->DE = power * pow(r, power - 1.0) * aux->DE + 1.0;
	z.x = cos(th) * cos(ph) * rp;
	z.y = cos(th) * sin(ph) * rp;
	z.z = sin(th) * rp;
	return z;
}
