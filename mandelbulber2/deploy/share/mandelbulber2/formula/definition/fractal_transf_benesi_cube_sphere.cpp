/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * Benesi Cube to sphere transform
 * Warps a cube to a sphere; transform made by M.Benesi, optimized by Luca.
 * @reference http://www.fractalforums.com/mathematics/circle2square/
 */

#include "all_fractal_definitions.h"

cFractalTransfBenesiCubeSphere::cFractalTransfBenesiCubeSphere() : cAbstractFractal()
{
	nameInComboBox = "T>Benesi Cube>Sphere";
	internalName = "transf_benesi_cube_sphere";
	internalID = fractal::transfBenesiCubeSphere;
	DEType = analyticDEType;
	DEFunctionType = withoutDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionNone;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfBenesiCubeSphere::FormulaCode(
	CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	Q_UNUSED(fractal);
	// Q_UNUSED(aux);
	CVector4 oldZ = z;
	z *= z; // so all now positive

	// if (z.x == 0.0)
	//	z.x = 1e-21;
	// if (z.z == 0.0)
	//	z.z = 1e-21;

	double rCyz = z.y / z.z;

	double rCxyz = (z.y + z.z) / z.x;

	if (rCxyz == -1.0) z.z = 1.0; //+ 1e-21
	if (rCyz < 1.0)
		rCyz = sqrt(rCyz + 1.0);
	else
		rCyz = sqrt(1.0 / rCyz + 1.0);

	if (rCxyz < 1.0)
		rCxyz = sqrt(rCxyz + 1.0);
	else
		rCxyz = sqrt(1.0 / rCxyz + 1.0);

	z.y *= rCyz;
	z.z *= rCyz;

	z *= rCxyz / SQRT_3_2;
	// aux.DE *= z.Length() / oldZ.Length();
	if (fractal->analyticDE.enabled)
	{
		aux.DE = aux.DE * fractal->analyticDE.scale1 * z.Length() / oldZ.Length()
						 + fractal->analyticDE.offset1;
	}
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
