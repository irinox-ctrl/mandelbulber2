/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * TransfSincosHelixIteration
 */

#include "all_fractal_definitions.h"

cFractalTransfSincosHelix::cFractalTransfSincosHelix() : cAbstractFractal()
{
	nameInComboBox = "T>SinCos Helix";
	internalName = "transf_sincos_helix";
	internalID = fractal::transfSincosHelix;
	DEType = analyticDEType;
	DEFunctionType = withoutDEFunction;
	cpixelAddition = cpixelDisabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionNone;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTransfSincosHelix::FormulaCode(CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	double temp;
	double ang;
	if (fractal->transformCommon.functionEnabledPFalse)
	{
		if (aux.i >= fractal->transformCommon.startIterationsP
				&& aux.i < fractal->transformCommon.stopIterationsP1)
		{
			// pre abs
			if (fractal->transformCommon.functionEnabledxFalse)
			{
				if (!fractal->transformCommon.functionEnabledBxFalse) z.x = fabs(z.x);
				else z.x = -fabs(z.x);
			}
			if (fractal->transformCommon.functionEnabledyFalse)
			{
				if (!fractal->transformCommon.functionEnabledByFalse) z.y = fabs(z.y);
				else z.y = -fabs(z.y);
			}
			if (fractal->transformCommon.functionEnabledzFalse)
			{
				if (!fractal->transformCommon.functionEnabledBzFalse) z.z = fabs(z.z);
				else z.z = -fabs(z.z);
			}
			// addition constant
			z += fractal->transformCommon.additionConstantA000;
		}

		if (aux.i >= fractal->transformCommon.startIterationsC
				&& aux.i < fractal->transformCommon.stopIterationsC1)
		{
			if (fractal->transformCommon.functionEnabledCxFalse)
			{
				ang = M_PI / fractal->transformCommon.int8X;
				ang = fabs(fmod(atan2(z.y, z.x) + ang, 2.0 * ang) - ang);
				temp = sqrt(z.x * z.x + z.y * z.y);
				z.x = cos(ang) * temp;
				z.y = sin(ang) * temp;
			}
			if (fractal->transformCommon.functionEnabledCyFalse)
			{
				ang = M_PI / fractal->transformCommon.int8Y;
				ang = fabs(fmod(atan2(z.z, z.y) + ang, 2.0 * ang) - ang);
				temp = sqrt(z.y * z.y + z.z * z.z);
				z.y = cos(ang) * temp;
				z.z = sin(ang) * temp;
			}
			if (fractal->transformCommon.functionEnabledCzFalse)
			{
				ang = M_PI / fractal->transformCommon.int8Z;
				ang = fabs(fmod(atan2(z.x, z.z) + ang, 2.0 * ang) - ang);
				temp = sqrt(z.z * z.z + z.x * z.x);
				z.z = cos(ang) * temp;
				z.x = sin(ang) * temp;
			}
			// addition constant
			z += fractal->transformCommon.additionConstant000;
		}

		// rotation
		if (aux.i >= fractal->transformCommon.startIterationsR
				&& aux.i < fractal->transformCommon.stopIterationsR1)
		{
			z = fractal->transformCommon.rotationMatrix.RotateVector(z);
		}
	}

	// swap axis
	if (fractal->transformCommon.functionEnabledSwFalse)
	{
		temp = z.x;
		z.x = z.y;
		z.y = temp;
	}

	// swap axis
	if (fractal->transformCommon.functionEnabledSFalse)
	{
		temp = z.x;
		z.x = z.z;
		z.z = temp;
	}

	z *= fractal->transformCommon.scale1;
	aux.DE = fabs(aux.DE * fractal->transformCommon.scale1);

	if (!fractal->transformCommon.functionEnabledOFalse)
		ang = atan2(z.x, z.y);
	else
		ang = atan2(z.y, z.x);
	ang *= M_PI_2x_INV * fractal->transformCommon.scaleA1;

	if (fractal->transformCommon.functionEnabled)
		z.y = sqrt(z.x * z.x + z.y * z.y) - fractal->transformCommon.scale015;

	if (fractal->transformCommon.functionEnabledAFalse)
	{
		z.x += z.z * fractal->transformCommon.scaleB0;
		z.y += z.z * fractal->transformCommon.scaleC0;
	}

	// vert helix
	if (fractal->transformCommon.functionEnabledAx)
	{
		double Voff = fractal->transformCommon.offset4;
		temp = z.z - Voff * ang * fractal->transformCommon.int1 + Voff * 0.5;
		z.z = temp - Voff * floor(temp / (Voff)) - Voff * 0.5;
	}

	// stretch
	if (fractal->transformCommon.functionEnabledAw)
	{
		if (!fractal->transformCommon.functionEnabledAy)
			z.x = fractal->transformCommon.offsetR1;
		else
		{
			temp = fractal->transformCommon.scale16 * ang
					+ fractal->transformCommon.offsetR1;
			z.x = temp - 2.0 * floor(temp * 0.5) - 1.0;
		}
	}
	if (fractal->transformCommon.functionEnabledAzFalse)
	{
		if (fractal->transformCommon.functionEnabledAwFalse)
		{
			double Phi = z.z;
			double Rho = sqrt(z.x * z.x + z.y * z.y);

			ang = Rho * fractal->transformCommon.offsetA0
					+ Phi * fractal->transformCommon.offsetB0;
		}
		double cosA = cos(ang);
		double sinB = sin(ang);
		if (!fractal->transformCommon.functionEnabledNFalse)
		{
			temp = z.x;
			z.x = z.y * cosA + z.x * sinB;
		}
		else
		{
			temp = z.z;
			z.z = z.y * cosA + z.z * sinB;
		}
		z.y = temp * cosA - z.y * sinB;
	}

	// repeat
	if (fractal->transformCommon.functionEnabledMFalse
			&& aux.i >= fractal->transformCommon.startIterationsTM
			&& aux.i < fractal->transformCommon.stopIterationsTM1)
	{
		if ((z.z < (fractal->transformCommon.scaleA1 + 0.5) * fractal->transformCommon.offset2)
			&& (z.z > (fractal->transformCommon.offsetT1 + 0.5) * -fractal->transformCommon.offset2))
		{
			z.z -= round(z.z / fractal->transformCommon.offset2) * fractal->transformCommon.offset2;
			z.z = clamp(fabs(z.z), -fractal->transformCommon.offset1, fractal->transformCommon.offset1);
		}
	}

	// clip
	if (fractal->transformCommon.functionEnabledJFalse
			&& aux.i >= fractal->transformCommon.startIterationsT
			&& aux.i < fractal->transformCommon.stopIterationsT1)
	{
		if (fractal->transformCommon.functionEnabledEFalse)
			z.z = max(aux.const_c.z - fractal->transformCommon.offsetE0, z.z);

		if (fractal->transformCommon.functionEnabledFFalse)
			z.z = min(aux.const_c.z + fractal->transformCommon.offsetF0, -z.z);
	}

	// Analytic DE tweak
	if (fractal->analyticDE.enabledFalse)
		aux.DE = aux.DE * fractal->analyticDE.scale1 + fractal->analyticDE.offset0;

	// aux.color
	if (fractal->foldColor.auxColorEnabled)
	{
		if (!fractal->transformCommon.functionEnabledGFalse)
		{
			double ang = (M_PI - 2.0 * fabs(atan(fractal->foldColor.difs1 * z.y / z.z)))
					* 4.0 * M_PI_2x_INV;
			if (fmod(ang, 2.0) < 1.0) aux.color += fractal->foldColor.difs0000.z;
			else aux.color += fractal->foldColor.difs0000.y;
		}
		else
		{
			aux.color += fractal->foldColor.difs0000.x * (z.x * z.x);
			aux.color += fractal->foldColor.difs0000.z * (z.z * z.z);
			aux.color += fractal->foldColor.difs0000.y * (z.y * z.y);
		}
	}
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
