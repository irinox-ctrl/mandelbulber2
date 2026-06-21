/**
 * Mandelbulber v2, a 3D fractal generator
 * Copyright (C) 2025 3x3lion Team
 * This file is part of Mandelbulber. Licensed under GPLv3.
 *
 * Hyperbolische cosinus-integraal Julia.
 * Math: z = Chi(z) + c = integral(cosh(t)/t) + c
 */

#include "all_fractal_definitions.h"

cFractalThreex3HyperbolicCosineIntegralJulia::cFractalThreex3HyperbolicCosineIntegralJulia() : cAbstractFractal()
{
	nameInComboBox = "3x3 V98 Hyperbolic Cosine Integral Julia";
	internalName = "threex3_hyperbolic_cosine_integral_julia";
	internalID = fractal::threex3HyperbolicCosineIntegralJulia;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalThreex3HyperbolicCosineIntegralJulia::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// Hyperbolic Cosine Integral Julia: z = Chi(z) + c = integral(cosh(t)/t) + c
	double r = aux.r;
	if (r < 1e-21) r = 1e-21;
	double power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	// PDE-inspired: diffusion-reaction
	double laplacian = (z.x * z.x + z.y * z.y + z.z * z.z) * fractal->transformCommon.scale1;
	double reaction = sin(z.x) * cos(z.y) * sin(z.z);
	double th = asin(z.z / r) * power;
	double ph = atan2(z.y, z.x) * power;
	double rp = pow(r, power);
	aux.DE = power * pow(r, power - 1.0) * aux.DE + 1.0;
	z.x = cos(th) * cos(ph) * rp + fractal->transformCommon.offset0 * reaction;
	z.y = cos(th) * sin(ph) * rp + fractal->transformCommon.offsetA0 * laplacian * 0.001;
	z.z = sin(th) * rp;
	// === General Purpose Multiplier 1 ===
	if (fractal->transformCommon.functionEnabledBxFalse
		&& aux.i >= fractal->transformCommon.startIterationsB
		&& aux.i < fractal->transformCommon.stopIterationsB)
	{
		double val = fractal->transformCommon.scale4;
		switch (fractal->transformCommon.multiplierMode1)
		{
			default:
			case 0: z *= val; aux.DE *= fabs(val); break;
			case 1: z.x *= val; break;
			case 2: z.y *= val; break;
			case 3: z.z *= val; break;
			case 4: aux.DE *= val; break;
			case 5: aux.color *= val; break;
		}
	}

	// === General Purpose Multiplier 2 ===
	if (fractal->transformCommon.functionEnabledByFalse
		&& aux.i >= fractal->transformCommon.startIterationsC
		&& aux.i < fractal->transformCommon.stopIterationsC)
	{
		double val = fractal->transformCommon.scale5;
		switch (fractal->transformCommon.multiplierMode2)
		{
			default:
			case 0: z *= val; aux.DE *= fabs(val); break;
			case 1: z.x *= val; break;
			case 2: z.y *= val; break;
			case 3: z.z *= val; break;
			case 4: aux.DE *= val; break;
			case 5: aux.color *= val; break;
		}
	}

	// === General Purpose Multiplier 3 ===
	if (fractal->transformCommon.functionEnabledBzFalse
		&& aux.i >= fractal->transformCommon.startIterationsD
		&& aux.i < fractal->transformCommon.stopIterationsD)
	{
		double val = fractal->transformCommon.scale6;
		switch (fractal->transformCommon.multiplierMode3)
		{
			default:
			case 0: z *= val; aux.DE *= fabs(val); break;
			case 1: z.x *= val; break;
			case 2: z.y *= val; break;
			case 3: z.z *= val; break;
			case 4: aux.DE *= val; break;
			case 5: aux.color *= val; break;
		}
	}

	// === General Purpose Multiplier 4 ===
	if (fractal->transformCommon.functionEnabledBwFalse
		&& aux.i >= fractal->transformCommon.startIterationsE
		&& aux.i < fractal->transformCommon.stopIterationsE)
	{
		double val = fractal->transformCommon.scale8;
		switch (fractal->transformCommon.multiplierMode4)
		{
			default:
			case 0: z *= val; aux.DE *= fabs(val); break;
			case 1: z.x *= val; break;
			case 2: z.y *= val; break;
			case 3: z.z *= val; break;
			case 4: aux.DE *= val; break;
			case 5: aux.color *= val; break;
		}
	}

	// === General Purpose Multiplier 5 ===
	if (fractal->transformCommon.functionEnabledCzFalse
		&& aux.i >= fractal->transformCommon.startIterationsF
		&& aux.i < fractal->transformCommon.stopIterationsF)
	{
		double val = fractal->transformCommon.scale16;
		switch (fractal->transformCommon.multiplierMode5)
		{
			default:
			case 0: z *= val; aux.DE *= fabs(val); break;
			case 1: z.x *= val; break;
			case 2: z.y *= val; break;
			case 3: z.z *= val; break;
			case 4: aux.DE *= val; break;
			case 5: aux.color *= val; break;
		}
	}

}
