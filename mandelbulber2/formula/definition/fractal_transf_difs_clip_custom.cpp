/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * TransfDIFSClipCustom
 */

#include "all_fractal_definitions.h"

cFractalTransfDIFSClipCustom::cFractalTransfDIFSClipCustom() : cAbstractFractal()
{
	nameInComboBox = "T>DIFS Clip Custom";
	internalName = "transf_difs_clip_custom";
	internalID = fractal::transfDIFSClipCustom;
	DEType = analyticDEType;
	DEFunctionType = customDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 1000.0;
	DEAnalyticFunction = analyticFunctionCustomDE;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfDIFSClipCustom::FormulaCode(
	CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	if (fractal->transformCommon.functionEnabledwFalse) aux.dist = z.Length() / aux.DE;

	// pre-box option
	if (fractal->transformCommon.functionEnabledAFalse)
	{
		CVector4 zc = z;
		zc += fractal->transformCommon.offsetA000;
		zc = fabs(zc) - fractal->transformCommon.additionConstant111;
		zc.x = max(zc.x, 0.0);
		zc.y = max(zc.y, 0.0);
		zc.z = max(zc.z, 0.0);
		double zcd = zc.Length() * fractal->transformCommon.scale1 - fractal->transformCommon.offsetB0;
		if (!fractal->transformCommon.functionEnabledNFalse)
		{
			aux.dist = zcd;
		}
		else
		{
			aux.dist = min(aux.dist, zcd);
		}
	}

	// transform c
	CVector4 c = aux.const_c;
	if (fractal->transformCommon.functionEnabledFalse) c = z;

			// polyfold
	if (fractal->transformCommon.functionEnabledPFalse)
	{
		c.y = fabs(c.y);
		double psi = M_PI / fractal->transformCommon.int6;
		psi = fabs(fmod(atan2(c.y, c.x) + psi, 2.0 * psi) - psi);
		double len = sqrt(c.x * c.x + c.y * c.y);
		c.x = cos(psi) * len;
		c.y = sin(psi) * len;
	}

	if (fractal->transformCommon.functionEnabledAxFalse) c.x = fabs(c.x);
	if (fractal->transformCommon.functionEnabledAyFalse) c.y = fabs(c.y);
	if (fractal->transformCommon.functionEnabledAzFalse) c.z = fabs(c.z);

	c *= fractal->transformCommon.scale3D111;
	c += fractal->transformCommon.offset000;
	c = fractal->transformCommon.rotationMatrix.RotateVector(c);

	double dst = 0.0;
	if (fractal->transformCommon.functionEnabledBx)
	{
		CVector4 g = fabs(c) - fractal->transformCommon.offsetC111;
		if (!fractal->transformCommon.functionEnabledCFalse)
		{
			dst = max(max(g.x, g.y), g.z);
		}
		else
		{
			dst = c.Length() - g.Length();
		}
		if (fractal->transformCommon.functionEnabledOFalse)
		{
			dst = fabs(dst) - fractal->transformCommon.offsetC0;
		}
	}

	double dst1 = 0.0;
	if (fractal->transformCommon.functionEnabledBFalse) // sphere
	{

		if (!fractal->transformCommon.functionEnabledIFalse)
		{
			dst1 = c.Length() - fractal->transformCommon.offsetR1; // sphere
		}
		else // cyl or cone
		{
			if (!fractal->transformCommon.functionEnabledEFalse) // cyl
			{
				dst1 = sqrt(c.x * c.x + c.y * c.y) - fractal->transformCommon.offsetR1;
			}
			else // cones
			{
				double CZ = -c.z;
				if (fractal->transformCommon.functionEnabledFFalse) CZ = fabs(c.z);
				if (fractal->transformCommon.functionEnabledGFalse) CZ = c.z * c.z;
				dst1 = sqrt(c.x * c.x + c.y * c.y) - fractal->transformCommon.offsetR1 * CZ;
			}
		}

		if (!fractal->transformCommon.functionEnabledJFalse) // z clip
		{
			dst1 = max(fabs(c.z) - fractal->transformCommon.offset1, dst1);
		}
		if (fractal->transformCommon.functionEnabledMFalse)
		{
			dst1 = fabs(dst1) - fractal->transformCommon.offsetA0;
		}

		if (!fractal->transformCommon.functionEnabledDFalse) dst = dst1;
		else dst = max(dst, dst1);
	}

	// aux->color
	if (fractal->foldColor.auxColorEnabledFalse)
	{
		double addColor = 0.0;
		if (dst > aux.dist) addColor += fractal->foldColor.difs0000.x;
		if (dst1 > aux.dist) addColor += fractal->foldColor.difs0000.y;

		if (!fractal->transformCommon.functionEnabledyFalse)
			aux.color = addColor;
		else
			aux.color += addColor;
	}

	if (!fractal->transformCommon.functionEnabledxFalse)
	{
		dst *= fractal->analyticDE.scale1;
	}
	else
	{
		dst *= fractal->analyticDE.scale1 / aux.DE;
	}

	dst = max(aux.dist, dst);

	if (!fractal->analyticDE.enabledFalse)
		aux.dist = dst;
	else
		aux.dist = min(dst, aux.dist);
	// GPU bypass: skip if all multipliers disabled
	if (fractal->transformCommon.functionEnabledBxFalse || fractal->transformCommon.functionEnabledByFalse || fractal->transformCommon.functionEnabledBzFalse || fractal->transformCommon.functionEnabledBwFalse || fractal->transformCommon.functionEnabledCzFalse)
	{
		// === General Purpose Multiplier 1 ===
		if (fractal->transformCommon.functionEnabledBxFalse
				&& aux.i >= fractal->transformCommon.startIterationsB
				&& aux.i < fractal->transformCommon.stopIterationsB)
		{
			double val = fractal->transformCommon.scale4;

			if (fractal->transformCommon.multiplierInverse1) val = 1.0 / val;

			int vmode = fractal->transformCommon.multiplierValueMode1;
			if (vmode == 1)
			{
				double range = (double)(fractal->transformCommon.stopIterationsB - fractal->transformCommon.startIterationsB);
				if (range > 0)
				{
					double phase = (double)(aux.i - fractal->transformCommon.startIterationsB) / range;
					val = 1.0 + (val - 1.0) * sin(phase * fractal->transformCommon.multiplierFrequency1 * 2.0 * M_PI);
				}
			}
			else if (vmode == 2)
			{
				double range = (double)(fractal->transformCommon.stopIterationsB - fractal->transformCommon.startIterationsB);
				if (range > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.startIterationsB) / range;
					t = qBound(0.0, t, 1.0);
					val = 1.0 + t * (val - 1.0);
				}
			}

			switch (fractal->transformCommon.multiplierMode1)
			{
				default:
				case 0: z *= val; aux.DE *= fabs(val); break;
				case 1: z.x *= val; break;
				case 2: z.y *= val; break;
				case 3: z.z *= val; break;
				case 4: aux.DE *= val; break;
				case 5: aux.color *= val; break;
				case 6: z.w *= val; break;
				case 7: z.x *= val; z.y *= val; break;
				case 8: z.x *= val; z.z *= val; break;
				case 9: z.y *= val; z.z *= val; break;
			}
		}

		// === General Purpose Multiplier 2 ===
		if (fractal->transformCommon.functionEnabledByFalse
				&& aux.i >= fractal->transformCommon.startIterationsC
				&& aux.i < fractal->transformCommon.stopIterationsC)
		{
			double val = fractal->transformCommon.scale5;

			if (fractal->transformCommon.multiplierInverse2) val = 1.0 / val;

			int vmode = fractal->transformCommon.multiplierValueMode2;
			if (vmode == 1)
			{
				double range = (double)(fractal->transformCommon.stopIterationsC - fractal->transformCommon.startIterationsC);
				if (range > 0)
				{
					double phase = (double)(aux.i - fractal->transformCommon.startIterationsC) / range;
					val = 1.0 + (val - 1.0) * sin(phase * fractal->transformCommon.multiplierFrequency2 * 2.0 * M_PI);
				}
			}
			else if (vmode == 2)
			{
				double range = (double)(fractal->transformCommon.stopIterationsC - fractal->transformCommon.startIterationsC);
				if (range > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.startIterationsC) / range;
					t = qBound(0.0, t, 1.0);
					val = 1.0 + t * (val - 1.0);
				}
			}

			switch (fractal->transformCommon.multiplierMode2)
			{
				default:
				case 0: z *= val; aux.DE *= fabs(val); break;
				case 1: z.x *= val; break;
				case 2: z.y *= val; break;
				case 3: z.z *= val; break;
				case 4: aux.DE *= val; break;
				case 5: aux.color *= val; break;
				case 6: z.w *= val; break;
				case 7: z.x *= val; z.y *= val; break;
				case 8: z.x *= val; z.z *= val; break;
				case 9: z.y *= val; z.z *= val; break;
			}
		}

		// === General Purpose Multiplier 3 ===
		if (fractal->transformCommon.functionEnabledBzFalse
				&& aux.i >= fractal->transformCommon.startIterationsD
				&& aux.i < fractal->transformCommon.stopIterationsD)
		{
			double val = fractal->transformCommon.scale6;

			if (fractal->transformCommon.multiplierInverse3) val = 1.0 / val;

			int vmode = fractal->transformCommon.multiplierValueMode3;
			if (vmode == 1)
			{
				double range = (double)(fractal->transformCommon.stopIterationsD - fractal->transformCommon.startIterationsD);
				if (range > 0)
				{
					double phase = (double)(aux.i - fractal->transformCommon.startIterationsD) / range;
					val = 1.0 + (val - 1.0) * sin(phase * fractal->transformCommon.multiplierFrequency3 * 2.0 * M_PI);
				}
			}
			else if (vmode == 2)
			{
				double range = (double)(fractal->transformCommon.stopIterationsD - fractal->transformCommon.startIterationsD);
				if (range > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.startIterationsD) / range;
					t = qBound(0.0, t, 1.0);
					val = 1.0 + t * (val - 1.0);
				}
			}

			switch (fractal->transformCommon.multiplierMode3)
			{
				default:
				case 0: z *= val; aux.DE *= fabs(val); break;
				case 1: z.x *= val; break;
				case 2: z.y *= val; break;
				case 3: z.z *= val; break;
				case 4: aux.DE *= val; break;
				case 5: aux.color *= val; break;
				case 6: z.w *= val; break;
				case 7: z.x *= val; z.y *= val; break;
				case 8: z.x *= val; z.z *= val; break;
				case 9: z.y *= val; z.z *= val; break;
			}
		}

		// === General Purpose Multiplier 4 ===
		if (fractal->transformCommon.functionEnabledBwFalse
				&& aux.i >= fractal->transformCommon.startIterationsE
				&& aux.i < fractal->transformCommon.stopIterationsE)
		{
			double val = fractal->transformCommon.scale8;

			if (fractal->transformCommon.multiplierInverse4) val = 1.0 / val;

			int vmode = fractal->transformCommon.multiplierValueMode4;
			if (vmode == 1)
			{
				double range = (double)(fractal->transformCommon.stopIterationsE - fractal->transformCommon.startIterationsE);
				if (range > 0)
				{
					double phase = (double)(aux.i - fractal->transformCommon.startIterationsE) / range;
					val = 1.0 + (val - 1.0) * sin(phase * fractal->transformCommon.multiplierFrequency4 * 2.0 * M_PI);
				}
			}
			else if (vmode == 2)
			{
				double range = (double)(fractal->transformCommon.stopIterationsE - fractal->transformCommon.startIterationsE);
				if (range > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.startIterationsE) / range;
					t = qBound(0.0, t, 1.0);
					val = 1.0 + t * (val - 1.0);
				}
			}

			switch (fractal->transformCommon.multiplierMode4)
			{
				default:
				case 0: z *= val; aux.DE *= fabs(val); break;
				case 1: z.x *= val; break;
				case 2: z.y *= val; break;
				case 3: z.z *= val; break;
				case 4: aux.DE *= val; break;
				case 5: aux.color *= val; break;
				case 6: z.w *= val; break;
				case 7: z.x *= val; z.y *= val; break;
				case 8: z.x *= val; z.z *= val; break;
				case 9: z.y *= val; z.z *= val; break;
			}
		}

		// === General Purpose Multiplier 5 ===
		if (fractal->transformCommon.functionEnabledCzFalse
				&& aux.i >= fractal->transformCommon.startIterationsF
				&& aux.i < fractal->transformCommon.stopIterationsF)
		{
			double val = fractal->transformCommon.scale16;

			if (fractal->transformCommon.multiplierInverse5) val = 1.0 / val;

			int vmode = fractal->transformCommon.multiplierValueMode5;
			if (vmode == 1)
			{
				double range = (double)(fractal->transformCommon.stopIterationsF - fractal->transformCommon.startIterationsF);
				if (range > 0)
				{
					double phase = (double)(aux.i - fractal->transformCommon.startIterationsF) / range;
					val = 1.0 + (val - 1.0) * sin(phase * fractal->transformCommon.multiplierFrequency5 * 2.0 * M_PI);
				}
			}
			else if (vmode == 2)
			{
				double range = (double)(fractal->transformCommon.stopIterationsF - fractal->transformCommon.startIterationsF);
				if (range > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.startIterationsF) / range;
					t = qBound(0.0, t, 1.0);
					val = 1.0 + t * (val - 1.0);
				}
			}

			switch (fractal->transformCommon.multiplierMode5)
			{
				default:
				case 0: z *= val; aux.DE *= fabs(val); break;
				case 1: z.x *= val; break;
				case 2: z.y *= val; break;
				case 3: z.z *= val; break;
				case 4: aux.DE *= val; break;
				case 5: aux.color *= val; break;
				case 6: z.w *= val; break;
				case 7: z.x *= val; z.y *= val; break;
				case 8: z.x *= val; z.z *= val; break;
				case 9: z.y *= val; z.z *= val; break;
			}
		}
	}

}
