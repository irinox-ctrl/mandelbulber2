/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * Kaleidoscopic Iterated Function Systems (IFS)
 * @reference
 * http://www.fractalforums.com/ifs-iterated-function-systems/kaleidoscopic-(escape-time-ifs)/
 */

#include "all_fractal_definitions.h"

cFractalKaleidoscopicIfs::cFractalKaleidoscopicIfs() : cAbstractFractal()
{
	nameInComboBox = "Kaleidoscopic IFS";
	internalName = "kaleidoscopic_ifs";
	internalID = fractal::kaleidoscopicIfs;
	DEType = analyticDEType;
	DEFunctionType = linearDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionIFS;
	coloringFunction = coloringFunctionIFS;
}

void cFractalKaleidoscopicIfs::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	if (fractal->IFS.absX) z.x = fabs(z.x);
	if (fractal->IFS.absY) z.y = fabs(z.y);
	if (fractal->IFS.absZ) z.z = fabs(z.z);

	for (int i = 0; i < IFS_VECTOR_COUNT; i++)
	{
		if (fractal->IFS.enabled[i])
		{
			z = fractal->IFS.rot[i].RotateVector(z);
			double length = z.Dot(fractal->IFS.direction[i]);

			if (length < fractal->IFS.distance[i])
			{
				z -= fractal->IFS.direction[i]
						 * (2.0 * (length - fractal->IFS.distance[i]) * fractal->IFS.intensity[i]);
			}
		}
	}

	if (fractal->IFS.rotationEnabled)
		z = fractal->IFS.mainRot.RotateVector(z - fractal->IFS.offset) + fractal->IFS.offset;

	if (fractal->IFS.edgeEnabled)
	{
		if (fractal->IFS.edge.x > 0.0) z.x = fractal->IFS.edge.x - fabs(fractal->IFS.edge.x - z.x);
		if (fractal->IFS.edge.y > 0.0) z.y = fractal->IFS.edge.y - fabs(fractal->IFS.edge.y - z.y);
		if (fractal->IFS.edge.z > 0.0) z.z = fractal->IFS.edge.z - fabs(fractal->IFS.edge.z - z.z);
	}

	z *= fractal->IFS.scale;
	if (fractal->IFS.mengerSpongeMode)
	{
		z.x -= fractal->IFS.offset.x * (fractal->IFS.scale - 1.0);
		z.y -= fractal->IFS.offset.y * (fractal->IFS.scale - 1.0);
		if (z.z > 0.5 * fractal->IFS.offset.z * (fractal->IFS.scale - 1.0))
			z.z -= fractal->IFS.offset.z * (fractal->IFS.scale - 1.0);
	}
	else
	{
		z -= fractal->IFS.offset * (fractal->IFS.scale - 1.0);
	}
	aux.DE *= fabs(fractal->IFS.scale);
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
