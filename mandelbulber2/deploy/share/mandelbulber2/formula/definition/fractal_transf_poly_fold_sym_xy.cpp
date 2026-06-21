/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * poly fold sym DarkBeam's version
 * @reference
 * DarkBeam (luca) http://www.fractalforums.com/mandelbulber/
 * _polyfold_sym-and-polyfoldsymifs-in-mandelbulber-2/msg98162/#msg98162
 */

#include "all_fractal_definitions.h"

cFractalTransfPolyFoldSymXY::cFractalTransfPolyFoldSymXY() : cAbstractFractal()
{
	nameInComboBox = "T>Poly Fold Sym XY";
	internalName = "transf_poly_fold_sym_xy";
	internalID = fractal::transfPolyFoldSymXY;
	DEType = analyticDEType;
	DEFunctionType = withoutDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionNone;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfPolyFoldSymXY::FormulaCode(
	CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	CVector4 oldZ = z;
	// pre abs
	if (fractal->transformCommon.functionEnabledxFalse) z.x = fabs(z.x);
	if (fractal->transformCommon.functionEnabledyFalse) z.y = fabs(z.y);

	int order = fractal->transformCommon.int6;
	double div2PI = (double)order * M_PI_2x_INV;

	bool cy = false;
	int sector;
	if (!fractal->transformCommon.functionEnabledFalse)
		sector = (int)(-div2PI * atan(z.x / z.y));
	else
		sector = (int)(-div2PI * atan2(z.x, z.y));

	if (sector & 1) cy = true; // parity   if (sector & 1) is a "bit check", true = odd
	double angle = (double)(sector / div2PI);
	// z.xy = rotate(z.xy,angle); // sin
	double tempZx = z.x;
	double sAng = sin(angle);
	double cAng = cos(angle);
	z.x = z.x * cAng - z.y * sAng;
	z.y = tempZx * sAng + z.y * cAng;
	if (cy) z.y = -z.y;
	// if ((order&1) && (sector == 0)) z.y = fabs(z.y); // more continuous?

	// addition constant
	z.x += fractal->transformCommon.offset0;
	z.y += fractal->transformCommon.offsetA0;

	if (fractal->analyticDE.enabled)
	{
		if (!fractal->analyticDE.enabledFalse)
			aux.DE = aux.DE * fractal->analyticDE.scale1 + fractal->analyticDE.offset0;
		else
		{
			double avgScale = z.Length() / oldZ.Length();
			aux.DE = aux.DE * avgScale * fractal->analyticDE.scale1 + fractal->analyticDE.offset0;
		}
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
