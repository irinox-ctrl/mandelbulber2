/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * Adds rotated Cpixel constant to z vector. Possible to swap Cpixel vector axes.
 */

#include "all_fractal_definitions.h"

cFractalTransfAddCpixelRotated::cFractalTransfAddCpixelRotated() : cAbstractFractal()
{
	nameInComboBox = "T>Add Cpixel - Rotated";
	internalName = "transf_add_cpixel_rotated";
	internalID = fractal::transfAddCpixelRotated;
	DEType = analyticDEType;
	DEFunctionType = withoutDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionNone;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfAddCpixelRotated::FormulaCode(
	CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	CVector4 c = aux.const_c;

	CVector4 tempC = c;
	if (fractal->transformCommon.alternateEnabledFalse) // alternate
	{
		tempC = aux.c;
		switch (fractal->mandelbulbMulti.orderOfXYZ)
		{
			case multi_OrderOfXYZ_xyz:
			default: tempC = CVector4(tempC.x, tempC.y, tempC.z, tempC.w); break;
			case multi_OrderOfXYZ_xzy: tempC = CVector4(tempC.x, tempC.z, tempC.y, tempC.w); break;
			case multi_OrderOfXYZ_yxz: tempC = CVector4(tempC.y, tempC.x, tempC.z, tempC.w); break;
			case multi_OrderOfXYZ_yzx: tempC = CVector4(tempC.y, tempC.z, tempC.x, tempC.w); break;
			case multi_OrderOfXYZ_zxy: tempC = CVector4(tempC.z, tempC.x, tempC.y, tempC.w); break;
			case multi_OrderOfXYZ_zyx: tempC = CVector4(tempC.z, tempC.y, tempC.x, tempC.w); break;
		}
		aux.c = tempC;
	}
	else
	{
		switch (fractal->mandelbulbMulti.orderOfXYZ)
		{
			case multi_OrderOfXYZ_xyz:
			default: tempC = CVector4(c.x, c.y, c.z, c.w); break;
			case multi_OrderOfXYZ_xzy: tempC = CVector4(c.x, c.z, c.y, c.w); break;
			case multi_OrderOfXYZ_yxz: tempC = CVector4(c.y, c.x, c.z, c.w); break;
			case multi_OrderOfXYZ_yzx: tempC = CVector4(c.y, c.z, c.x, c.w); break;
			case multi_OrderOfXYZ_zxy: tempC = CVector4(c.z, c.x, c.y, c.w); break;
			case multi_OrderOfXYZ_zyx: tempC = CVector4(c.z, c.y, c.x, c.w); break;
		}
	}
	if (aux.i >= fractal->transformCommon.startIterationsG
			&& aux.i < fractal->transformCommon.stopIterationsG)
	{
		tempC = fractal->transformCommon.rotationMatrix.RotateVector(tempC);
	}
	z += tempC * fractal->transformCommon.constantMultiplier111;
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
