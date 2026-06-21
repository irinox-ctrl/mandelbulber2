/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * rotate angles with iteration start/stop controls
 */

#include "all_fractal_definitions.h"

cFractalTransfRotationIterControls::cFractalTransfRotationIterControls() : cAbstractFractal()
{
	nameInComboBox = "T>Rotation Iter Controls";
	internalName = "transf_rotation_iter_controls";
	internalID = fractal::transfRotationIterControls;
	DEType = analyticDEType;
	DEFunctionType = withoutDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionNone;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfRotationIterControls::FormulaCode(
	CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	Q_UNUSED(aux);
	CVector4 tp;
	if (fractal->transformCommon.rotation44a.y != 0
			&& aux.i >= fractal->transformCommon.startIterationsA
			&& aux.i < fractal->transformCommon.stopIterationsA)
	{
		tp = z;
		double alpha = fractal->transformCommon.rotation44a.y * -M_PI_180;
		z.y = tp.y * cos(alpha) + tp.z * sin(alpha);
		z.z = tp.y * -sin(alpha) + tp.z * cos(alpha);
	}

	if (fractal->transformCommon.rotation44a.z != 0
			&& aux.i >= fractal->transformCommon.startIterationsB
			&& aux.i < fractal->transformCommon.stopIterationsB)
	{
		tp = z;
		double beta = fractal->transformCommon.rotation44a.z * M_PI_180;
		z.x = tp.x * cos(beta) + tp.z * sin(beta);
		z.z = tp.x * -sin(beta) + tp.z * cos(beta);
	}

	if (fractal->transformCommon.rotation44a.x != 0
			&& aux.i >= fractal->transformCommon.startIterationsC
			&& aux.i < fractal->transformCommon.stopIterationsC)
	{
		tp = z;
		double gamma = fractal->transformCommon.rotation44a.x * -M_PI_180;
		z.x = tp.x * cos(gamma) + tp.y * sin(gamma);
		z.y = tp.x * -sin(gamma) + tp.y * cos(gamma);
	}
	// === General Purpose Multiplier 1 ===
	if (fractal->transformCommon.functionEnabledBxFalse
		&& aux.i >= fractal->transformCommon.startIterationsB
		&& aux.i < fractal->transformCommon.stopIterationsB)
	{
		z *= fractal->transformCommon.scale4;
		aux.DE *= fabs(fractal->transformCommon.scale4);
	}

	// === General Purpose Multiplier 2 ===
	if (fractal->transformCommon.functionEnabledByFalse
		&& aux.i >= fractal->transformCommon.startIterationsC
		&& aux.i < fractal->transformCommon.stopIterationsC)
	{
		z *= fractal->transformCommon.scale5;
		aux.DE *= fabs(fractal->transformCommon.scale5);
	}

	// === General Purpose Multiplier 3 ===
	if (fractal->transformCommon.functionEnabledBzFalse
		&& aux.i >= fractal->transformCommon.startIterationsD
		&& aux.i < fractal->transformCommon.stopIterationsD)
	{
		z *= fractal->transformCommon.scale6;
		aux.DE *= fabs(fractal->transformCommon.scale6);
	}

	// === General Purpose Multiplier 4 ===
	if (fractal->transformCommon.functionEnabledBwFalse
		&& aux.i >= fractal->transformCommon.startIterationsE
		&& aux.i < fractal->transformCommon.stopIterationsE)
	{
		z *= fractal->transformCommon.scale8;
		aux.DE *= fabs(fractal->transformCommon.scale8);
	}

	// === General Purpose Multiplier 5 ===
	if (fractal->transformCommon.functionEnabledCzFalse
		&& aux.i >= fractal->transformCommon.startIterationsF
		&& aux.i < fractal->transformCommon.stopIterationsF)
	{
		z *= fractal->transformCommon.scale16;
		aux.DE *= fabs(fractal->transformCommon.scale16);
	}

}
