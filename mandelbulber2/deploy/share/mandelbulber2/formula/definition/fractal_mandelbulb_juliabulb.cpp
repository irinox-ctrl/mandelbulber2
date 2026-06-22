/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * mandelbulb juliabulb hybrid 3D
 * constructed from Mandelbulb, Msltoe - Julia Bulb Eiffie & Msltoe - Sym4 Mod formulas.
 * note: an Offset Radius of 0.1 can sometimes improve the DE statistic
 */

#include "all_fractal_definitions.h"

cFractalMandelbulbJuliabulb::cFractalMandelbulbJuliabulb() : cAbstractFractal()
{
	nameInComboBox = "Mandelbulb - Juliabulb";
	internalName = "mandelbulb_juliabulb";
	internalID = fractal::mandelbulbJuliabulb;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 10.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalMandelbulbJuliabulb::FormulaCode(
	CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	// mandelbulb multi
	if (aux.i >= fractal->transformCommon.startIterationsM
			&& aux.i < fractal->transformCommon.stopIterationsM)
	{
		aux.r = z.Length();
		if (fractal->transformCommon.functionEnabledFalse)
		{
			if (fractal->transformCommon.functionEnabledAxFalse
					&& aux.i >= fractal->transformCommon.startIterationsX
					&& aux.i < fractal->transformCommon.stopIterationsX)
				z.x = fabs(z.x);
			if (fractal->transformCommon.functionEnabledAyFalse
					&& aux.i >= fractal->transformCommon.startIterationsY
					&& aux.i < fractal->transformCommon.stopIterationsY)
				z.y = fabs(z.y);
			if (fractal->transformCommon.functionEnabledAzFalse
					&& aux.i >= fractal->transformCommon.startIterationsZ
					&& aux.i < fractal->transformCommon.stopIterationsZ)
				z.z = fabs(z.z);
		}

		double th0 = fractal->bulb.betaAngleOffset;
		double ph0 = fractal->bulb.alphaAngleOffset;

		CVector3 v;
		switch (fractal->sinTan2Trig.orderOfZYX)
		{
			case multi_OrderOfZYX_zyx:
			default: v = CVector3(z.z, z.y, z.x); break;
			case multi_OrderOfZYX_zxy: v = CVector3(z.z, z.x, z.y); break;
			case multi_OrderOfZYX_yzx: v = CVector3(z.y, z.z, z.x); break;
			case multi_OrderOfZYX_yxz: v = CVector3(z.y, z.x, z.z); break;
			case multi_OrderOfZYX_xzy: v = CVector3(z.x, z.z, z.y); break;
			case multi_OrderOfZYX_xyz: v = CVector3(z.x, z.y, z.z); break;
		}

		if (fractal->sinTan2Trig.asinOrAcos == multi_asinOrAcos_asin)
			th0 += asin(v.x / aux.r);
		else
			th0 += acos(v.x / aux.r);

		if (fractal->sinTan2Trig.atan2OrAtan == multi_atan2OrAtan_atan2)
			ph0 += atan2(v.y, v.z);
		else
			ph0 += atan(v.y / v.z);

		double rp = pow(aux.r, fractal->bulb.power - 1.0);
		double th = th0 * fractal->bulb.power * fractal->transformCommon.scaleA1;
		double ph = ph0 * fractal->bulb.power * fractal->transformCommon.scaleB1;

		aux.DE = rp * aux.DE * fractal->bulb.power + 1.0;
		rp *= aux.r;

		if (fractal->transformCommon.functionEnabledxFalse)
		{ // cosine mode
			double sinth = th;
			if (fractal->transformCommon.functionEnabledyFalse) sinth = th0;
			sinth = sin(sinth);
			z = rp * CVector4(sinth * sin(ph), cos(ph) * sinth, cos(th), 0.0);
		}
		else
		{ // sine mode
			double costh = th;
			if (fractal->transformCommon.functionEnabledzFalse) costh = th0;
			costh = cos(costh);
			z = rp * CVector4(costh * cos(ph), sin(ph) * costh, sin(th), 0.0);
		}
	}

	// sym4
	if (fractal->transformCommon.functionEnabled && aux.i >= fractal->transformCommon.startIterationsD
			&& aux.i < fractal->transformCommon.stopIterationsD)
	{
		aux.r = z.Length();
		aux.DE = aux.DE * 2.0 * aux.r;
		CVector4 temp = z;
		double tempL = temp.Length();
		// if (tempL < 1e-21)
		//	tempL = 1e-21;
		z *= fractal->transformCommon.scale3D111;

		aux.DE *= z.Length() / tempL;

		if (fabs(z.x) < fabs(z.z)) swap(z.x, z.z);
		if (fabs(z.x) < fabs(z.y)) swap(z.x, z.y);
		if (fabs(z.y) < fabs(z.z)) swap(z.y, z.z);

		if (z.x * z.z < 0.0) z.z = -z.z;
		if (z.x * z.y < 0.0) z.y = -z.y;

		temp.x = z.x * z.x - z.y * z.y - z.z * z.z;
		temp.y = 2.0 * z.x * z.y;
		temp.z = 2.0 * z.x * z.z;

		z = temp + fractal->transformCommon.offsetF000;
	}

	// sym3 msltoe eiffie
	if (fractal->transformCommon.functionEnabledEFalse
			&& aux.i >= fractal->transformCommon.startIterationsE
			&& aux.i < fractal->transformCommon.stopIterationsE)
	{
		aux.r = z.Length();
		double psi = fabs(fmod(atan2(z.z, z.y) + M_PI + M_PI_8, M_PI_4) - M_PI_8);
		double lengthYZ = sqrt(z.y * z.y + z.z * z.z);

		z.y = cos(psi) * lengthYZ;
		z.z = sin(psi) * lengthYZ;
		aux.DE = aux.DE * 2.0 * aux.r;

		CVector4 z2 = z * z;
		double rr = z2.x + z2.y + z2.z;
		double m = 1.0 - z2.z / rr;
		CVector4 temp;
		temp.x = (z2.x - z2.y) * m;
		temp.y = 2.0 * z.x * z.y * m * fractal->transformCommon.scale; // scaling y;;
		temp.z = 2.0 * z.z * sqrt(z2.x + z2.y);
		temp.w = z.w;
		z = temp + fractal->transformCommon.additionConstant000;
	}

	if (fractal->transformCommon.addCpixelEnabledFalse)
	{
		CVector4 c = aux.const_c;
		CVector4 tempC = c;
		if (fractal->transformCommon.alternateEnabledFalse) // alternate
		{
			tempC = aux.c;
			switch (fractal->mandelbulbMulti.orderOfXYZC)
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
			switch (fractal->mandelbulbMulti.orderOfXYZC)
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
		z += tempC * fractal->transformCommon.constantMultiplierC111;
	}
	// radial offset
	double lengthTempZ = -z.Length();
	// if (lengthTempZ > -1e-21)
	//	lengthTempZ = -1e-21;   //  z is neg.)
	z *= 1.0 + fractal->transformCommon.offset / lengthTempZ;
	// scale
	z *= fractal->transformCommon.scale1;
	aux.DE *= fabs(fractal->transformCommon.scale1);
	// =============================================
	// === MANDELBULB EXTENSIONS (#1-#10) ===
	// =============================================

	// === MB #1-2: Power Oscillation ===
	if (fractal->transformCommon.mbPowerOsc != 0.0)
	{
		double powerOsc = fractal->transformCommon.mbPowerOsc * sin((double)aux.i * fractal->transformCommon.mbPowerOscFreq);
		double rr = z.Dot(z);
		if (rr > 1e-21)
		{
			double factor = pow(sqrt(rr), powerOsc);
			z *= factor;
			aux.DE *= fabs(factor);
		}
	}

	// === MB #3: Theta Warp ===
	if (fractal->transformCommon.mbThetaWarp != 0.0)
	{
		double r2 = z.x * z.x + z.y * z.y + z.z * z.z;
		if (r2 > 1e-21)
		{
			double r = sqrt(r2);
			double theta = asin(z.z / r);
			double phi = atan2(z.y, z.x);
			theta += fractal->transformCommon.mbThetaWarp * sin(theta * 3.0);
			z.x = r * cos(theta) * cos(phi);
			z.y = r * cos(theta) * sin(phi);
			z.z = r * sin(theta);
		}
	}

	// === MB #4: Phi Warp ===
	if (fractal->transformCommon.mbPhiWarp != 0.0)
	{
		double r2 = z.x * z.x + z.y * z.y + z.z * z.z;
		if (r2 > 1e-21)
		{
			double r = sqrt(r2);
			double theta = asin(z.z / r);
			double phi = atan2(z.y, z.x);
			phi += fractal->transformCommon.mbPhiWarp * sin(phi * 2.0);
			z.x = r * cos(theta) * cos(phi);
			z.y = r * cos(theta) * sin(phi);
			z.z = r * sin(theta);
		}
	}

	// === MB #5: Radial Stretch ===
	if (fractal->transformCommon.mbRadialStretch != 0.0)
	{
		double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z + 1e-21);
		double stretch = 1.0 + fractal->transformCommon.mbRadialStretch * sin(r * 2.0);
		z *= stretch;
		aux.DE *= fabs(stretch);
	}

	// === MB #6: Pre-Twist Z ===
	if (fractal->transformCommon.mbPreTwistZ != 0.0)
	{
		double angle = fractal->transformCommon.mbPreTwistZ * M_PI / 180.0 * (double)aux.i;
		double cosA = cos(angle);
		double sinA = sin(angle);
		double xn = z.x * cosA - z.y * sinA;
		double yn = z.x * sinA + z.y * cosA;
		z.x = xn;
		z.y = yn;
	}

	// === MB #7: Turbulence ===
	if (fractal->transformCommon.mbTurbulence != 0.0)
	{
		double turb = fractal->transformCommon.mbTurbulence;
		int hx = (int)(z.x * 1000.0) * 73856093;
		int hy = (int)(z.y * 1000.0) * 19349663;
		int hz = (int)(z.z * 1000.0) * 83492791;
		int h = hx ^ hy ^ hz;
		h = (h ^ (h >> 13)) * 1274126177;
		h = h ^ (h >> 16);
		double noise = ((double)(h & 0xFFFF) / 32767.5) - 1.0;
		z.x += turb * noise;
		h = h * 1103515245 + 12345;
		noise = ((double)(h & 0xFFFF) / 32767.5) - 1.0;
		z.y += turb * noise;
		h = h * 1103515245 + 12345;
		noise = ((double)(h & 0xFFFF) / 32767.5) - 1.0;
		z.z += turb * noise;
	}

	// === MB #8: Gradient Color ===
	if (fractal->transformCommon.mbGradientColor != 0.0)
	{
		double rCol = sqrt(z.x * z.x + z.y * z.y + z.z * z.z + 1e-21);
		aux.color += rCol * fractal->transformCommon.mbGradientColor;
	}

	// === MB #9: DE Tweak ===
	if (fractal->transformCommon.mbDETweak != 0.0)
	{
		aux.DE += fractal->transformCommon.mbDETweak;
	}

	// === MB #10: C-Pixel Scale ===
	if (fractal->transformCommon.mbCpixelScale != 0.0)
	{
		z += aux.const_c * fractal->transformCommon.mbCpixelScale;
	}

		// --- Julia Extensions (20 parameters) ---
	{
		double jlPwOsc = fractal->transformCommon.jlPowerOsc;
		double jlPwFreq = fractal->transformCommon.jlPowerOscFreq;
		double jlThWarp = fractal->transformCommon.jlThetaWarp;
		double jlPhWarp = fractal->transformCommon.jlPhiWarp;
		double jlRadStr = fractal->transformCommon.jlRadialStretch;
		double jlPreXY = fractal->transformCommon.jlPreRotXY;
		double jlPreXZ = fractal->transformCommon.jlPreRotXZ;
		double jlPostYZ = fractal->transformCommon.jlPostRotYZ;
		double jlTwZ = fractal->transformCommon.jlTwistZ;
		double jlScOsc = fractal->transformCommon.jlScaleOsc;
		double jlScFreq = fractal->transformCommon.jlScaleOscFreq;
		double jlOffOsc = fractal->transformCommon.jlOffsetOsc;
		double jlOffFreq = fractal->transformCommon.jlOffsetOscFreq;
		double jlRadDist = fractal->transformCommon.jlRadialDistort;
		double jlTurb = fractal->transformCommon.jlTurbulence;
		double jlGradCol = fractal->transformCommon.jlGradientColor;
		double jlDETw = fractal->transformCommon.jlDETweak;
		double jlCpix = fractal->transformCommon.jlCpixelScale;
		double jlSphere = fractal->transformCommon.jlSphereFold;
		double jlEdgeSoft = fractal->transformCommon.jlEdgeSoftness;

		// 1-2. Power oscillation
		if (jlPwOsc != 0.0)
		{
			double pOsc = 1.0 + jlPwOsc * sin(aux.i * jlPwFreq * 0.5);
			z *= pOsc;
			aux.DE *= fabs(pOsc);
		}

		// 3. Theta warp
		if (jlThWarp != 0.0)
		{
			double r = z.Length();
			if (r > 1e-15)
			{
				double th = acos(z.z / r);
				th += jlThWarp * sin(aux.i * 1.5);
				double ph = atan2(z.y, z.x);
				z.x = r * sin(th) * cos(ph);
				z.y = r * sin(th) * sin(ph);
				z.z = r * cos(th);
			}
		}

		// 4. Phi warp
		if (jlPhWarp != 0.0)
		{
			double r = z.Length();
			if (r > 1e-15)
			{
				double th = acos(z.z / r);
				double ph = atan2(z.y, z.x);
				ph += jlPhWarp * sin(aux.i * 1.3);
				z.x = r * sin(th) * cos(ph);
				z.y = r * sin(th) * sin(ph);
				z.z = r * cos(th);
			}
		}

		// 5. Radial stretch
		if (jlRadStr != 0.0)
		{
			double r = z.Length();
			if (r > 1e-15)
			{
				double stretch = 1.0 + jlRadStr * (r - 1.0);
				z *= stretch / r * r;
				aux.DE *= fabs(stretch);
			}
		}

		// 6. Pre-rotation XY
		if (jlPreXY != 0.0)
		{
			double a = jlPreXY * M_PI / 180.0 * aux.i;
			double ca = cos(a); double sa = sin(a);
			double px = z.x * ca - z.y * sa;
			double py = z.x * sa + z.y * ca;
			z.x = px; z.y = py;
		}

		// 7. Pre-rotation XZ
		if (jlPreXZ != 0.0)
		{
			double a = jlPreXZ * M_PI / 180.0 * aux.i;
			double ca = cos(a); double sa = sin(a);
			double px = z.x * ca - z.z * sa;
			double pz = z.x * sa + z.z * ca;
			z.x = px; z.z = pz;
		}

		// 8. Post-rotation YZ
		if (jlPostYZ != 0.0)
		{
			double a = jlPostYZ * M_PI / 180.0;
			double ca = cos(a); double sa = sin(a);
			double py = z.y * ca - z.z * sa;
			double pz = z.y * sa + z.z * ca;
			z.y = py; z.z = pz;
		}

		// 9. Twist Z
		if (jlTwZ != 0.0)
		{
			double tw = jlTwZ * M_PI / 180.0 * z.z;
			double ct = cos(tw); double st = sin(tw);
			double tx = z.x * ct - z.y * st;
			double ty = z.x * st + z.y * ct;
			z.x = tx; z.y = ty;
		}

		// 10-11. Scale oscillation
		if (jlScOsc != 0.0)
		{
			double sOsc = 1.0 + jlScOsc * sin(aux.i * jlScFreq * 0.5);
			z *= sOsc;
			aux.DE *= fabs(sOsc);
		}

		// 12-13. Offset oscillation
		if (jlOffOsc != 0.0)
		{
			double oOsc = jlOffOsc * sin(aux.i * jlOffFreq * 0.5);
			z.x += oOsc;
			z.y += oOsc * 0.7;
			z.z += oOsc * 0.5;
		}

		// 14. Radial distortion
		if (jlRadDist != 0.0)
		{
			double r = z.Length();
			if (r > 1e-15)
			{
				double distort = 1.0 + jlRadDist * sin(r * 4.0);
				z *= distort;
				aux.DE *= fabs(distort);
			}
		}

		// 15. Turbulence
		if (jlTurb != 0.0)
		{
			double hx = sin(z.x * 12.9898 + z.y * 78.233) * 43758.5453;
			hx = hx - floor(hx);
			double hy = sin(z.y * 12.9898 + z.z * 78.233) * 43758.5453;
			hy = hy - floor(hy);
			double hz = sin(z.z * 12.9898 + z.x * 78.233) * 43758.5453;
			hz = hz - floor(hz);
			z.x += (hx - 0.5) * jlTurb;
			z.y += (hy - 0.5) * jlTurb;
			z.z += (hz - 0.5) * jlTurb;
		}

		// 16. Gradient color
		if (jlGradCol != 0.0)
		{
			aux.color += jlGradCol * z.Length();
		}

		// 17. DE tweak
		if (jlDETw != 0.0)
		{
			aux.DE += jlDETw;
		}

		// 18. C-pixel scale
		if (jlCpix != 0.0)
		{
			z += aux.const_c * jlCpix;
		}

		// 19. Sphere fold
		if (jlSphere != 0.0)
		{
			double r2 = z.Dot(z);
			double minR2 = 0.25;
			double fixedR2 = 1.0;
			if (r2 < minR2)
			{
				double t = fixedR2 / minR2;
				z *= t * jlSphere;
				aux.DE *= fabs(t * jlSphere);
			}
			else if (r2 < fixedR2)
			{
				double t = fixedR2 / r2;
				z *= t * jlSphere;
				aux.DE *= fabs(t * jlSphere);
			}
		}

		// 20. Edge softness
		if (jlEdgeSoft != 0.0)
		{
			double r = z.Length();
			if (r > 1e-15)
			{
				double soft = r / (r + jlEdgeSoft);
				z *= soft;
				aux.DE *= soft;
			}
		}
	}

	// GPU bypass: skip if all multipliers disabled
	if (fractal->transformCommon.multiplierEnabled1 || fractal->transformCommon.multiplierEnabled2 || fractal->transformCommon.multiplierEnabled3 || fractal->transformCommon.multiplierEnabled4 || fractal->transformCommon.multiplierEnabled5)
	{
		double prevMultVal = 1.0;
		// === General Purpose Multiplier 1 ===
		if (fractal->transformCommon.multiplierEnabled1
				&& aux.i >= fractal->transformCommon.multiplierStartIter1
				&& aux.i < fractal->transformCommon.multiplierStopIter1)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode1;
			double threshR = z.Length();
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold1)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold1))
			{
				double val = fractal->transformCommon.multiplierScale1;

				if (fractal->transformCommon.multiplierInverse1) val = (fabs(val) > 1e-15) ? (1.0 / val) : 1e15;

				int vmode = fractal->transformCommon.multiplierValueMode1;
				double range = (double)(fractal->transformCommon.multiplierStopIter1 - fractal->transformCommon.multiplierStartIter1);
				double ph = fractal->transformCommon.multiplierPhase1;
				if (range > 0 && vmode > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.multiplierStartIter1) / range;
					double freq = fractal->transformCommon.multiplierFrequency1;
					if (vmode == 1) // Sine
					{
						val = 1.0 + (val - 1.0) * sin((t * freq + ph) * 2.0 * M_PI);
					}
					else if (vmode == 2) // Ramp
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 3) // Exponential
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + (val - 1.0) * (exp(t * freq) - 1.0) / (exp(freq) - 1.0);
					}
					else if (vmode == 4) // Triangle
					{
						double tri = 1.0 - 2.0 * fabs(fmod(t * freq + ph, 1.0) - 0.5);
						val = 1.0 + (val - 1.0) * tri;
					}
					else if (vmode == 5) // Square
					{
						val = (fmod(t * freq + ph, 1.0) < 0.5) ? val : 1.0;
					}
					else if (vmode == 6) // Smoothstep
					{
						t = qBound(0.0, t, 1.0);
						t = t * t * (3.0 - 2.0 * t);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 7) // Noise
					{
						int seed = aux.i * 73856093 + 1 * 19349663;
						seed = (seed ^ (seed >> 13)) * 1274126177;
						seed = seed ^ (seed >> 16);
						double noise = (double)(seed & 0xFFFF) / 65535.0;
						val = 1.0 + (val - 1.0) * noise;
					}
					else if (vmode == 8) // Ping-pong
					{
						double pp = fmod(t * freq + ph, 2.0);
						if (pp > 1.0) pp = 2.0 - pp;
						val = 1.0 + (val - 1.0) * pp;
					}
					else if (vmode == 9) // Stepped
					{
						double steps = freq;
						if (steps < 1.0) steps = 1.0;
						double st = floor(t * steps) / steps;
						val = 1.0 + (val - 1.0) * st;
					}
				}

				double w = fractal->transformCommon.multiplierWeight1;
				val = 1.0 + w * (val - 1.0);

				switch (fractal->transformCommon.multiplierMode1)
				{
					default:
					case 0:
					{
						double valY = fractal->transformCommon.multiplierScaleY1;
						double valZ = fractal->transformCommon.multiplierScaleZ1;
						if (valY == 0.0) valY = val;
						if (valZ == 0.0) valZ = val;
						z.x *= val; z.y *= valY; z.z *= valZ;
						aux.DE *= fabs(val);
						break;
					}
					case 1: z.x *= val; aux.DE *= fabs(val); break;
					case 2: z.y *= val; aux.DE *= fabs(val); break;
					case 3: z.z *= val; aux.DE *= fabs(val); break;
					case 4: aux.DE *= val; break;
					case 5: aux.color *= val; break;
					case 6: z.w *= val; aux.DE *= fabs(val); break;
					case 7: z.x *= val; z.y *= val; aux.DE *= fabs(val); break;
					case 8: z.x *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 9: z.y *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 10: aux.color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 2 ===
		if (fractal->transformCommon.multiplierEnabled2
				&& aux.i >= fractal->transformCommon.multiplierStartIter2
				&& aux.i < fractal->transformCommon.multiplierStopIter2)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode2;
			double threshR = z.Length();
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold2)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold2))
			{
				double val = fractal->transformCommon.multiplierScale2;

				if (fractal->transformCommon.multiplierInverse2) val = (fabs(val) > 1e-15) ? (1.0 / val) : 1e15;

				int vmode = fractal->transformCommon.multiplierValueMode2;
				double range = (double)(fractal->transformCommon.multiplierStopIter2 - fractal->transformCommon.multiplierStartIter2);
				double ph = fractal->transformCommon.multiplierPhase2;
				if (range > 0 && vmode > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.multiplierStartIter2) / range;
					double freq = fractal->transformCommon.multiplierFrequency2;
					if (vmode == 1) // Sine
					{
						val = 1.0 + (val - 1.0) * sin((t * freq + ph) * 2.0 * M_PI);
					}
					else if (vmode == 2) // Ramp
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 3) // Exponential
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + (val - 1.0) * (exp(t * freq) - 1.0) / (exp(freq) - 1.0);
					}
					else if (vmode == 4) // Triangle
					{
						double tri = 1.0 - 2.0 * fabs(fmod(t * freq + ph, 1.0) - 0.5);
						val = 1.0 + (val - 1.0) * tri;
					}
					else if (vmode == 5) // Square
					{
						val = (fmod(t * freq + ph, 1.0) < 0.5) ? val : 1.0;
					}
					else if (vmode == 6) // Smoothstep
					{
						t = qBound(0.0, t, 1.0);
						t = t * t * (3.0 - 2.0 * t);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 7) // Noise
					{
						int seed = aux.i * 73856093 + 2 * 19349663;
						seed = (seed ^ (seed >> 13)) * 1274126177;
						seed = seed ^ (seed >> 16);
						double noise = (double)(seed & 0xFFFF) / 65535.0;
						val = 1.0 + (val - 1.0) * noise;
					}
					else if (vmode == 8) // Ping-pong
					{
						double pp = fmod(t * freq + ph, 2.0);
						if (pp > 1.0) pp = 2.0 - pp;
						val = 1.0 + (val - 1.0) * pp;
					}
					else if (vmode == 9) // Stepped
					{
						double steps = freq;
						if (steps < 1.0) steps = 1.0;
						double st = floor(t * steps) / steps;
						val = 1.0 + (val - 1.0) * st;
					}
				}

				if (fractal->transformCommon.multiplierChain2) val *= prevMultVal;

				double w = fractal->transformCommon.multiplierWeight2;
				val = 1.0 + w * (val - 1.0);

				switch (fractal->transformCommon.multiplierMode2)
				{
					default:
					case 0:
					{
						double valY = fractal->transformCommon.multiplierScaleY2;
						double valZ = fractal->transformCommon.multiplierScaleZ2;
						if (valY == 0.0) valY = val;
						if (valZ == 0.0) valZ = val;
						z.x *= val; z.y *= valY; z.z *= valZ;
						aux.DE *= fabs(val);
						break;
					}
					case 1: z.x *= val; aux.DE *= fabs(val); break;
					case 2: z.y *= val; aux.DE *= fabs(val); break;
					case 3: z.z *= val; aux.DE *= fabs(val); break;
					case 4: aux.DE *= val; break;
					case 5: aux.color *= val; break;
					case 6: z.w *= val; aux.DE *= fabs(val); break;
					case 7: z.x *= val; z.y *= val; aux.DE *= fabs(val); break;
					case 8: z.x *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 9: z.y *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 10: aux.color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 3 ===
		if (fractal->transformCommon.multiplierEnabled3
				&& aux.i >= fractal->transformCommon.multiplierStartIter3
				&& aux.i < fractal->transformCommon.multiplierStopIter3)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode3;
			double threshR = z.Length();
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold3)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold3))
			{
				double val = fractal->transformCommon.multiplierScale3;

				if (fractal->transformCommon.multiplierInverse3) val = (fabs(val) > 1e-15) ? (1.0 / val) : 1e15;

				int vmode = fractal->transformCommon.multiplierValueMode3;
				double range = (double)(fractal->transformCommon.multiplierStopIter3 - fractal->transformCommon.multiplierStartIter3);
				double ph = fractal->transformCommon.multiplierPhase3;
				if (range > 0 && vmode > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.multiplierStartIter3) / range;
					double freq = fractal->transformCommon.multiplierFrequency3;
					if (vmode == 1) // Sine
					{
						val = 1.0 + (val - 1.0) * sin((t * freq + ph) * 2.0 * M_PI);
					}
					else if (vmode == 2) // Ramp
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 3) // Exponential
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + (val - 1.0) * (exp(t * freq) - 1.0) / (exp(freq) - 1.0);
					}
					else if (vmode == 4) // Triangle
					{
						double tri = 1.0 - 2.0 * fabs(fmod(t * freq + ph, 1.0) - 0.5);
						val = 1.0 + (val - 1.0) * tri;
					}
					else if (vmode == 5) // Square
					{
						val = (fmod(t * freq + ph, 1.0) < 0.5) ? val : 1.0;
					}
					else if (vmode == 6) // Smoothstep
					{
						t = qBound(0.0, t, 1.0);
						t = t * t * (3.0 - 2.0 * t);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 7) // Noise
					{
						int seed = aux.i * 73856093 + 3 * 19349663;
						seed = (seed ^ (seed >> 13)) * 1274126177;
						seed = seed ^ (seed >> 16);
						double noise = (double)(seed & 0xFFFF) / 65535.0;
						val = 1.0 + (val - 1.0) * noise;
					}
					else if (vmode == 8) // Ping-pong
					{
						double pp = fmod(t * freq + ph, 2.0);
						if (pp > 1.0) pp = 2.0 - pp;
						val = 1.0 + (val - 1.0) * pp;
					}
					else if (vmode == 9) // Stepped
					{
						double steps = freq;
						if (steps < 1.0) steps = 1.0;
						double st = floor(t * steps) / steps;
						val = 1.0 + (val - 1.0) * st;
					}
				}

				if (fractal->transformCommon.multiplierChain3) val *= prevMultVal;

				double w = fractal->transformCommon.multiplierWeight3;
				val = 1.0 + w * (val - 1.0);

				switch (fractal->transformCommon.multiplierMode3)
				{
					default:
					case 0:
					{
						double valY = fractal->transformCommon.multiplierScaleY3;
						double valZ = fractal->transformCommon.multiplierScaleZ3;
						if (valY == 0.0) valY = val;
						if (valZ == 0.0) valZ = val;
						z.x *= val; z.y *= valY; z.z *= valZ;
						aux.DE *= fabs(val);
						break;
					}
					case 1: z.x *= val; aux.DE *= fabs(val); break;
					case 2: z.y *= val; aux.DE *= fabs(val); break;
					case 3: z.z *= val; aux.DE *= fabs(val); break;
					case 4: aux.DE *= val; break;
					case 5: aux.color *= val; break;
					case 6: z.w *= val; aux.DE *= fabs(val); break;
					case 7: z.x *= val; z.y *= val; aux.DE *= fabs(val); break;
					case 8: z.x *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 9: z.y *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 10: aux.color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 4 ===
		if (fractal->transformCommon.multiplierEnabled4
				&& aux.i >= fractal->transformCommon.multiplierStartIter4
				&& aux.i < fractal->transformCommon.multiplierStopIter4)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode4;
			double threshR = z.Length();
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold4)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold4))
			{
				double val = fractal->transformCommon.multiplierScale4;

				if (fractal->transformCommon.multiplierInverse4) val = (fabs(val) > 1e-15) ? (1.0 / val) : 1e15;

				int vmode = fractal->transformCommon.multiplierValueMode4;
				double range = (double)(fractal->transformCommon.multiplierStopIter4 - fractal->transformCommon.multiplierStartIter4);
				double ph = fractal->transformCommon.multiplierPhase4;
				if (range > 0 && vmode > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.multiplierStartIter4) / range;
					double freq = fractal->transformCommon.multiplierFrequency4;
					if (vmode == 1) // Sine
					{
						val = 1.0 + (val - 1.0) * sin((t * freq + ph) * 2.0 * M_PI);
					}
					else if (vmode == 2) // Ramp
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 3) // Exponential
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + (val - 1.0) * (exp(t * freq) - 1.0) / (exp(freq) - 1.0);
					}
					else if (vmode == 4) // Triangle
					{
						double tri = 1.0 - 2.0 * fabs(fmod(t * freq + ph, 1.0) - 0.5);
						val = 1.0 + (val - 1.0) * tri;
					}
					else if (vmode == 5) // Square
					{
						val = (fmod(t * freq + ph, 1.0) < 0.5) ? val : 1.0;
					}
					else if (vmode == 6) // Smoothstep
					{
						t = qBound(0.0, t, 1.0);
						t = t * t * (3.0 - 2.0 * t);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 7) // Noise
					{
						int seed = aux.i * 73856093 + 4 * 19349663;
						seed = (seed ^ (seed >> 13)) * 1274126177;
						seed = seed ^ (seed >> 16);
						double noise = (double)(seed & 0xFFFF) / 65535.0;
						val = 1.0 + (val - 1.0) * noise;
					}
					else if (vmode == 8) // Ping-pong
					{
						double pp = fmod(t * freq + ph, 2.0);
						if (pp > 1.0) pp = 2.0 - pp;
						val = 1.0 + (val - 1.0) * pp;
					}
					else if (vmode == 9) // Stepped
					{
						double steps = freq;
						if (steps < 1.0) steps = 1.0;
						double st = floor(t * steps) / steps;
						val = 1.0 + (val - 1.0) * st;
					}
				}

				if (fractal->transformCommon.multiplierChain4) val *= prevMultVal;

				double w = fractal->transformCommon.multiplierWeight4;
				val = 1.0 + w * (val - 1.0);

				switch (fractal->transformCommon.multiplierMode4)
				{
					default:
					case 0:
					{
						double valY = fractal->transformCommon.multiplierScaleY4;
						double valZ = fractal->transformCommon.multiplierScaleZ4;
						if (valY == 0.0) valY = val;
						if (valZ == 0.0) valZ = val;
						z.x *= val; z.y *= valY; z.z *= valZ;
						aux.DE *= fabs(val);
						break;
					}
					case 1: z.x *= val; aux.DE *= fabs(val); break;
					case 2: z.y *= val; aux.DE *= fabs(val); break;
					case 3: z.z *= val; aux.DE *= fabs(val); break;
					case 4: aux.DE *= val; break;
					case 5: aux.color *= val; break;
					case 6: z.w *= val; aux.DE *= fabs(val); break;
					case 7: z.x *= val; z.y *= val; aux.DE *= fabs(val); break;
					case 8: z.x *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 9: z.y *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 10: aux.color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 5 ===
		if (fractal->transformCommon.multiplierEnabled5
				&& aux.i >= fractal->transformCommon.multiplierStartIter5
				&& aux.i < fractal->transformCommon.multiplierStopIter5)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode5;
			double threshR = z.Length();
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold5)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold5))
			{
				double val = fractal->transformCommon.multiplierScale5;

				if (fractal->transformCommon.multiplierInverse5) val = (fabs(val) > 1e-15) ? (1.0 / val) : 1e15;

				int vmode = fractal->transformCommon.multiplierValueMode5;
				double range = (double)(fractal->transformCommon.multiplierStopIter5 - fractal->transformCommon.multiplierStartIter5);
				double ph = fractal->transformCommon.multiplierPhase5;
				if (range > 0 && vmode > 0)
				{
					double t = (double)(aux.i - fractal->transformCommon.multiplierStartIter5) / range;
					double freq = fractal->transformCommon.multiplierFrequency5;
					if (vmode == 1) // Sine
					{
						val = 1.0 + (val - 1.0) * sin((t * freq + ph) * 2.0 * M_PI);
					}
					else if (vmode == 2) // Ramp
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 3) // Exponential
					{
						t = qBound(0.0, t, 1.0);
						val = 1.0 + (val - 1.0) * (exp(t * freq) - 1.0) / (exp(freq) - 1.0);
					}
					else if (vmode == 4) // Triangle
					{
						double tri = 1.0 - 2.0 * fabs(fmod(t * freq + ph, 1.0) - 0.5);
						val = 1.0 + (val - 1.0) * tri;
					}
					else if (vmode == 5) // Square
					{
						val = (fmod(t * freq + ph, 1.0) < 0.5) ? val : 1.0;
					}
					else if (vmode == 6) // Smoothstep
					{
						t = qBound(0.0, t, 1.0);
						t = t * t * (3.0 - 2.0 * t);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 7) // Noise
					{
						int seed = aux.i * 73856093 + 5 * 19349663;
						seed = (seed ^ (seed >> 13)) * 1274126177;
						seed = seed ^ (seed >> 16);
						double noise = (double)(seed & 0xFFFF) / 65535.0;
						val = 1.0 + (val - 1.0) * noise;
					}
					else if (vmode == 8) // Ping-pong
					{
						double pp = fmod(t * freq + ph, 2.0);
						if (pp > 1.0) pp = 2.0 - pp;
						val = 1.0 + (val - 1.0) * pp;
					}
					else if (vmode == 9) // Stepped
					{
						double steps = freq;
						if (steps < 1.0) steps = 1.0;
						double st = floor(t * steps) / steps;
						val = 1.0 + (val - 1.0) * st;
					}
				}

				if (fractal->transformCommon.multiplierChain5) val *= prevMultVal;

				double w = fractal->transformCommon.multiplierWeight5;
				val = 1.0 + w * (val - 1.0);

				switch (fractal->transformCommon.multiplierMode5)
				{
					default:
					case 0:
					{
						double valY = fractal->transformCommon.multiplierScaleY5;
						double valZ = fractal->transformCommon.multiplierScaleZ5;
						if (valY == 0.0) valY = val;
						if (valZ == 0.0) valZ = val;
						z.x *= val; z.y *= valY; z.z *= valZ;
						aux.DE *= fabs(val);
						break;
					}
					case 1: z.x *= val; aux.DE *= fabs(val); break;
					case 2: z.y *= val; aux.DE *= fabs(val); break;
					case 3: z.z *= val; aux.DE *= fabs(val); break;
					case 4: aux.DE *= val; break;
					case 5: aux.color *= val; break;
					case 6: z.w *= val; aux.DE *= fabs(val); break;
					case 7: z.x *= val; z.y *= val; aux.DE *= fabs(val); break;
					case 8: z.x *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 9: z.y *= val; z.z *= val; aux.DE *= fabs(val); break;
					case 10: aux.color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}
	}

}
