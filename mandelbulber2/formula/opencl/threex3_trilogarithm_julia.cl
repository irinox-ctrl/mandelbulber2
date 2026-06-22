/**
 * Mandelbulber v2, a 3D fractal generator — OpenCL kernel
 * Copyright (C) 2025 3x3lion Team
 * Licensed under GPLv3.
 *
 * Trilogaritme Julia.
 */

REAL4 Threex3TrilogarithmJuliaIteration(REAL4 z, __constant sFractalCl *fractal, sExtendedAuxCl *aux)
{
	// Trilogarithm Julia: z = Li_3(z) + c
	REAL r = aux->r;
	if (r < 1e-21) r = 1e-21;
	REAL power = fractal->bulb.power;
	if (power < 2.0) power = 2.0;
	REAL th = asin(z.z / r) * power;
	REAL ph = atan2(z.y, z.x) * power;
	// Elliptic function modulation
	REAL k = fractal->transformCommon.scale1;
	REAL sn = sin(th) / (1.0 + k * k * sin(th) * sin(th));
	REAL cn = cos(th) * sqrt(1.0 - k * k * sin(th) * sin(th) * 0.25);
	REAL rp = pow(r, power);
	aux->DE = power * pow(r, power - 1.0) * aux->DE + 1.0;
	z.x = cn * cos(ph) * rp;
	z.y = cn * sin(ph) * rp;
	z.z = sn * rp;

		// --- Julia Extensions (20 parameters) ---
	{
		REAL jlPwOsc = fractal->transformCommon.jlPowerOsc;
		REAL jlPwFreq = fractal->transformCommon.jlPowerOscFreq;
		REAL jlThWarp = fractal->transformCommon.jlThetaWarp;
		REAL jlPhWarp = fractal->transformCommon.jlPhiWarp;
		REAL jlRadStr = fractal->transformCommon.jlRadialStretch;
		REAL jlPreXY = fractal->transformCommon.jlPreRotXY;
		REAL jlPreXZ = fractal->transformCommon.jlPreRotXZ;
		REAL jlPostYZ = fractal->transformCommon.jlPostRotYZ;
		REAL jlTwZ = fractal->transformCommon.jlTwistZ;
		REAL jlScOsc = fractal->transformCommon.jlScaleOsc;
		REAL jlScFreq = fractal->transformCommon.jlScaleOscFreq;
		REAL jlOffOsc = fractal->transformCommon.jlOffsetOsc;
		REAL jlOffFreq = fractal->transformCommon.jlOffsetOscFreq;
		REAL jlRadDist = fractal->transformCommon.jlRadialDistort;
		REAL jlTurb = fractal->transformCommon.jlTurbulence;
		REAL jlGradCol = fractal->transformCommon.jlGradientColor;
		REAL jlDETw = fractal->transformCommon.jlDETweak;
		REAL jlCpix = fractal->transformCommon.jlCpixelScale;
		REAL jlSphere = fractal->transformCommon.jlSphereFold;
		REAL jlEdgeSoft = fractal->transformCommon.jlEdgeSoftness;

		// 1-2. Power oscillation
		if (jlPwOsc != 0.0f)
		{
			REAL pOsc = 1.0f + jlPwOsc * native_sin(aux->i * jlPwFreq * 0.5f);
			z *= pOsc;
			aux->DE *= fabs(pOsc);
		}

		// 3. Theta warp
		if (jlThWarp != 0.0f)
		{
			REAL r = length(z);
			if (r > 1e-15f)
			{
				REAL th = acos(z.z / r);
				th += jlThWarp * native_sin(aux->i * 1.5f);
				REAL ph = atan2(z.y, z.x);
				z.x = r * native_sin(th) * native_cos(ph);
				z.y = r * native_sin(th) * native_sin(ph);
				z.z = r * native_cos(th);
			}
		}

		// 4. Phi warp
		if (jlPhWarp != 0.0f)
		{
			REAL r = length(z);
			if (r > 1e-15f)
			{
				REAL th = acos(z.z / r);
				REAL ph = atan2(z.y, z.x);
				ph += jlPhWarp * native_sin(aux->i * 1.3f);
				z.x = r * native_sin(th) * native_cos(ph);
				z.y = r * native_sin(th) * native_sin(ph);
				z.z = r * native_cos(th);
			}
		}

		// 5. Radial stretch
		if (jlRadStr != 0.0f)
		{
			REAL r = length(z);
			if (r > 1e-15f)
			{
				REAL stretch = 1.0f + jlRadStr * (r - 1.0f);
				z *= stretch / r * r;
				aux->DE *= fabs(stretch);
			}
		}

		// 6. Pre-rotation XY
		if (jlPreXY != 0.0f)
		{
			REAL a = jlPreXY * M_PI_F / 180.0f * aux->i;
			REAL ca = native_cos(a); REAL sa = native_sin(a);
			REAL px = z.x * ca - z.y * sa;
			REAL py = z.x * sa + z.y * ca;
			z.x = px; z.y = py;
		}

		// 7. Pre-rotation XZ
		if (jlPreXZ != 0.0f)
		{
			REAL a = jlPreXZ * M_PI_F / 180.0f * aux->i;
			REAL ca = native_cos(a); REAL sa = native_sin(a);
			REAL px = z.x * ca - z.z * sa;
			REAL pz = z.x * sa + z.z * ca;
			z.x = px; z.z = pz;
		}

		// 8. Post-rotation YZ
		if (jlPostYZ != 0.0f)
		{
			REAL a = jlPostYZ * M_PI_F / 180.0f;
			REAL ca = native_cos(a); REAL sa = native_sin(a);
			REAL py = z.y * ca - z.z * sa;
			REAL pz = z.y * sa + z.z * ca;
			z.y = py; z.z = pz;
		}

		// 9. Twist Z
		if (jlTwZ != 0.0f)
		{
			REAL tw = jlTwZ * M_PI_F / 180.0f * z.z;
			REAL ct = native_cos(tw); REAL st = native_sin(tw);
			REAL tx = z.x * ct - z.y * st;
			REAL ty = z.x * st + z.y * ct;
			z.x = tx; z.y = ty;
		}

		// 10-11. Scale oscillation
		if (jlScOsc != 0.0f)
		{
			REAL sOsc = 1.0f + jlScOsc * native_sin(aux->i * jlScFreq * 0.5f);
			z *= sOsc;
			aux->DE *= fabs(sOsc);
		}

		// 12-13. Offset oscillation
		if (jlOffOsc != 0.0f)
		{
			REAL oOsc = jlOffOsc * native_sin(aux->i * jlOffFreq * 0.5f);
			z.x += oOsc;
			z.y += oOsc * 0.7f;
			z.z += oOsc * 0.5f;
		}

		// 14. Radial distortion
		if (jlRadDist != 0.0f)
		{
			REAL r = length(z);
			if (r > 1e-15f)
			{
				REAL distort = 1.0f + jlRadDist * native_sin(r * 4.0f);
				z *= distort;
				aux->DE *= fabs(distort);
			}
		}

		// 15. Turbulence
		if (jlTurb != 0.0f)
		{
			REAL hx = native_sin(z.x * 12.9898f + z.y * 78.233f) * 43758.5453f;
			hx = hx - floor(hx);
			REAL hy = native_sin(z.y * 12.9898f + z.z * 78.233f) * 43758.5453f;
			hy = hy - floor(hy);
			REAL hz = native_sin(z.z * 12.9898f + z.x * 78.233f) * 43758.5453f;
			hz = hz - floor(hz);
			z.x += (hx - 0.5f) * jlTurb;
			z.y += (hy - 0.5f) * jlTurb;
			z.z += (hz - 0.5f) * jlTurb;
		}

		// 16. Gradient color
		if (jlGradCol != 0.0f)
		{
			aux->color += jlGradCol * length(z);
		}

		// 17. DE tweak
		if (jlDETw != 0.0f)
		{
			aux->DE += jlDETw;
		}

		// 18. C-pixel scale
		if (jlCpix != 0.0f)
		{
			z += aux->const_c * jlCpix;
		}

		// 19. Sphere fold
		if (jlSphere != 0.0f)
		{
			REAL r2 = dot(z, z);
			REAL minR2 = 0.25f;
			REAL fixedR2 = 1.0f;
			if (r2 < minR2)
			{
				REAL t = fixedR2 / minR2;
				z *= t * jlSphere;
				aux->DE *= fabs(t * jlSphere);
			}
			else if (r2 < fixedR2)
			{
				REAL t = fixedR2 / r2;
				z *= t * jlSphere;
				aux->DE *= fabs(t * jlSphere);
			}
		}

		// 20. Edge softness
		if (jlEdgeSoft != 0.0f)
		{
			REAL r = length(z);
			if (r > 1e-15f)
			{
				REAL soft = r / (r + jlEdgeSoft);
				z *= soft;
				aux->DE *= soft;
			}
		}
	}

	// GPU bypass: skip if all multipliers disabled
	if (fractal->transformCommon.multiplierEnabled1 || fractal->transformCommon.multiplierEnabled2 || fractal->transformCommon.multiplierEnabled3 || fractal->transformCommon.multiplierEnabled4 || fractal->transformCommon.multiplierEnabled5)
	{
		REAL prevMultVal = 1.0;
		// === General Purpose Multiplier 1 ===
		if (fractal->transformCommon.multiplierEnabled1
				&& aux->i >= fractal->transformCommon.multiplierStartIter1
				&& aux->i < fractal->transformCommon.multiplierStopIter1)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode1;
			REAL threshR = length(z);
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold1)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold1))
			{
				REAL val = fractal->transformCommon.multiplierScale1;

				if (fractal->transformCommon.multiplierInverse1) val = (fabs(val) > 1e-15f) ? (1.0f / val) : 1e15f;

				int vmode = fractal->transformCommon.multiplierValueMode1;
				REAL range = (REAL)(fractal->transformCommon.multiplierStopIter1 - fractal->transformCommon.multiplierStartIter1);
				REAL ph = fractal->transformCommon.multiplierPhase1;
				if (range > 0 && vmode > 0)
				{
					REAL t = (REAL)(aux->i - fractal->transformCommon.multiplierStartIter1) / range;
					REAL freq = fractal->transformCommon.multiplierFrequency1;
					if (vmode == 1) // Sine
					{
						val = 1.0 + (val - 1.0) * native_sin((t * freq + ph) * 2.0 * M_PI_F);
					}
					else if (vmode == 2) // Ramp
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 3) // Exponential
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						val = 1.0 + (val - 1.0) * (native_powr(2.718281828f, t * freq) - 1.0) / (native_powr(2.718281828f, freq) - 1.0);
					}
					else if (vmode == 4) // Triangle
					{
						REAL tri = 1.0 - 2.0 * fabs(fmod(t * freq + ph, 1.0) - 0.5);
						val = 1.0 + (val - 1.0) * tri;
					}
					else if (vmode == 5) // Square
					{
						val = (fmod(t * freq + ph, 1.0) < 0.5) ? val : 1.0;
					}
					else if (vmode == 6) // Smoothstep
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						t = t * t * (3.0 - 2.0 * t);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 7) // Noise
					{
						int seed = aux->i * 73856093 + 1 * 19349663;
						seed = (seed ^ (seed >> 13)) * 1274126177;
						seed = seed ^ (seed >> 16);
						REAL noise = (REAL)(seed & 0xFFFF) / 65535.0;
						val = 1.0 + (val - 1.0) * noise;
					}
					else if (vmode == 8) // Ping-pong
					{
						REAL pp = fmod(t * freq + ph, 2.0);
						if (pp > 1.0) pp = 2.0 - pp;
						val = 1.0 + (val - 1.0) * pp;
					}
					else if (vmode == 9) // Stepped
					{
						REAL steps = freq;
						if (steps < 1.0) steps = 1.0;
						REAL st = floor(t * steps) / steps;
						val = 1.0 + (val - 1.0) * st;
					}
				}

				REAL w = fractal->transformCommon.multiplierWeight1;
				val = 1.0 + w * (val - 1.0);

				switch (fractal->transformCommon.multiplierMode1)
				{
					default:
					case 0:
					{
						REAL valY = fractal->transformCommon.multiplierScaleY1;
						REAL valZ = fractal->transformCommon.multiplierScaleZ1;
						if (valY == 0.0) valY = val;
						if (valZ == 0.0) valZ = val;
						z.x *= val; z.y *= valY; z.z *= valZ;
						aux->DE *= fabs(val);
						break;
					}
					case 1: z.x *= val; aux->DE *= fabs(val); break;
					case 2: z.y *= val; aux->DE *= fabs(val); break;
					case 3: z.z *= val; aux->DE *= fabs(val); break;
					case 4: aux->DE *= val; break;
					case 5: aux->color *= val; break;
					case 6: z.w *= val; aux->DE *= fabs(val); break;
					case 7: z.x *= val; z.y *= val; aux->DE *= fabs(val); break;
					case 8: z.x *= val; z.z *= val; aux->DE *= fabs(val); break;
					case 9: z.y *= val; z.z *= val; aux->DE *= fabs(val); break;
					case 10: aux->color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 2 ===
		if (fractal->transformCommon.multiplierEnabled2
				&& aux->i >= fractal->transformCommon.multiplierStartIter2
				&& aux->i < fractal->transformCommon.multiplierStopIter2)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode2;
			REAL threshR = length(z);
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold2)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold2))
			{
				REAL val = fractal->transformCommon.multiplierScale2;

				if (fractal->transformCommon.multiplierInverse2) val = (fabs(val) > 1e-15f) ? (1.0f / val) : 1e15f;

				int vmode = fractal->transformCommon.multiplierValueMode2;
				REAL range = (REAL)(fractal->transformCommon.multiplierStopIter2 - fractal->transformCommon.multiplierStartIter2);
				REAL ph = fractal->transformCommon.multiplierPhase2;
				if (range > 0 && vmode > 0)
				{
					REAL t = (REAL)(aux->i - fractal->transformCommon.multiplierStartIter2) / range;
					REAL freq = fractal->transformCommon.multiplierFrequency2;
					if (vmode == 1) // Sine
					{
						val = 1.0 + (val - 1.0) * native_sin((t * freq + ph) * 2.0 * M_PI_F);
					}
					else if (vmode == 2) // Ramp
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 3) // Exponential
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						val = 1.0 + (val - 1.0) * (native_powr(2.718281828f, t * freq) - 1.0) / (native_powr(2.718281828f, freq) - 1.0);
					}
					else if (vmode == 4) // Triangle
					{
						REAL tri = 1.0 - 2.0 * fabs(fmod(t * freq + ph, 1.0) - 0.5);
						val = 1.0 + (val - 1.0) * tri;
					}
					else if (vmode == 5) // Square
					{
						val = (fmod(t * freq + ph, 1.0) < 0.5) ? val : 1.0;
					}
					else if (vmode == 6) // Smoothstep
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						t = t * t * (3.0 - 2.0 * t);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 7) // Noise
					{
						int seed = aux->i * 73856093 + 2 * 19349663;
						seed = (seed ^ (seed >> 13)) * 1274126177;
						seed = seed ^ (seed >> 16);
						REAL noise = (REAL)(seed & 0xFFFF) / 65535.0;
						val = 1.0 + (val - 1.0) * noise;
					}
					else if (vmode == 8) // Ping-pong
					{
						REAL pp = fmod(t * freq + ph, 2.0);
						if (pp > 1.0) pp = 2.0 - pp;
						val = 1.0 + (val - 1.0) * pp;
					}
					else if (vmode == 9) // Stepped
					{
						REAL steps = freq;
						if (steps < 1.0) steps = 1.0;
						REAL st = floor(t * steps) / steps;
						val = 1.0 + (val - 1.0) * st;
					}
				}

				if (fractal->transformCommon.multiplierChain2) val *= prevMultVal;

				REAL w = fractal->transformCommon.multiplierWeight2;
				val = 1.0 + w * (val - 1.0);

				switch (fractal->transformCommon.multiplierMode2)
				{
					default:
					case 0:
					{
						REAL valY = fractal->transformCommon.multiplierScaleY2;
						REAL valZ = fractal->transformCommon.multiplierScaleZ2;
						if (valY == 0.0) valY = val;
						if (valZ == 0.0) valZ = val;
						z.x *= val; z.y *= valY; z.z *= valZ;
						aux->DE *= fabs(val);
						break;
					}
					case 1: z.x *= val; aux->DE *= fabs(val); break;
					case 2: z.y *= val; aux->DE *= fabs(val); break;
					case 3: z.z *= val; aux->DE *= fabs(val); break;
					case 4: aux->DE *= val; break;
					case 5: aux->color *= val; break;
					case 6: z.w *= val; aux->DE *= fabs(val); break;
					case 7: z.x *= val; z.y *= val; aux->DE *= fabs(val); break;
					case 8: z.x *= val; z.z *= val; aux->DE *= fabs(val); break;
					case 9: z.y *= val; z.z *= val; aux->DE *= fabs(val); break;
					case 10: aux->color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 3 ===
		if (fractal->transformCommon.multiplierEnabled3
				&& aux->i >= fractal->transformCommon.multiplierStartIter3
				&& aux->i < fractal->transformCommon.multiplierStopIter3)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode3;
			REAL threshR = length(z);
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold3)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold3))
			{
				REAL val = fractal->transformCommon.multiplierScale3;

				if (fractal->transformCommon.multiplierInverse3) val = (fabs(val) > 1e-15f) ? (1.0f / val) : 1e15f;

				int vmode = fractal->transformCommon.multiplierValueMode3;
				REAL range = (REAL)(fractal->transformCommon.multiplierStopIter3 - fractal->transformCommon.multiplierStartIter3);
				REAL ph = fractal->transformCommon.multiplierPhase3;
				if (range > 0 && vmode > 0)
				{
					REAL t = (REAL)(aux->i - fractal->transformCommon.multiplierStartIter3) / range;
					REAL freq = fractal->transformCommon.multiplierFrequency3;
					if (vmode == 1) // Sine
					{
						val = 1.0 + (val - 1.0) * native_sin((t * freq + ph) * 2.0 * M_PI_F);
					}
					else if (vmode == 2) // Ramp
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 3) // Exponential
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						val = 1.0 + (val - 1.0) * (native_powr(2.718281828f, t * freq) - 1.0) / (native_powr(2.718281828f, freq) - 1.0);
					}
					else if (vmode == 4) // Triangle
					{
						REAL tri = 1.0 - 2.0 * fabs(fmod(t * freq + ph, 1.0) - 0.5);
						val = 1.0 + (val - 1.0) * tri;
					}
					else if (vmode == 5) // Square
					{
						val = (fmod(t * freq + ph, 1.0) < 0.5) ? val : 1.0;
					}
					else if (vmode == 6) // Smoothstep
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						t = t * t * (3.0 - 2.0 * t);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 7) // Noise
					{
						int seed = aux->i * 73856093 + 3 * 19349663;
						seed = (seed ^ (seed >> 13)) * 1274126177;
						seed = seed ^ (seed >> 16);
						REAL noise = (REAL)(seed & 0xFFFF) / 65535.0;
						val = 1.0 + (val - 1.0) * noise;
					}
					else if (vmode == 8) // Ping-pong
					{
						REAL pp = fmod(t * freq + ph, 2.0);
						if (pp > 1.0) pp = 2.0 - pp;
						val = 1.0 + (val - 1.0) * pp;
					}
					else if (vmode == 9) // Stepped
					{
						REAL steps = freq;
						if (steps < 1.0) steps = 1.0;
						REAL st = floor(t * steps) / steps;
						val = 1.0 + (val - 1.0) * st;
					}
				}

				if (fractal->transformCommon.multiplierChain3) val *= prevMultVal;

				REAL w = fractal->transformCommon.multiplierWeight3;
				val = 1.0 + w * (val - 1.0);

				switch (fractal->transformCommon.multiplierMode3)
				{
					default:
					case 0:
					{
						REAL valY = fractal->transformCommon.multiplierScaleY3;
						REAL valZ = fractal->transformCommon.multiplierScaleZ3;
						if (valY == 0.0) valY = val;
						if (valZ == 0.0) valZ = val;
						z.x *= val; z.y *= valY; z.z *= valZ;
						aux->DE *= fabs(val);
						break;
					}
					case 1: z.x *= val; aux->DE *= fabs(val); break;
					case 2: z.y *= val; aux->DE *= fabs(val); break;
					case 3: z.z *= val; aux->DE *= fabs(val); break;
					case 4: aux->DE *= val; break;
					case 5: aux->color *= val; break;
					case 6: z.w *= val; aux->DE *= fabs(val); break;
					case 7: z.x *= val; z.y *= val; aux->DE *= fabs(val); break;
					case 8: z.x *= val; z.z *= val; aux->DE *= fabs(val); break;
					case 9: z.y *= val; z.z *= val; aux->DE *= fabs(val); break;
					case 10: aux->color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 4 ===
		if (fractal->transformCommon.multiplierEnabled4
				&& aux->i >= fractal->transformCommon.multiplierStartIter4
				&& aux->i < fractal->transformCommon.multiplierStopIter4)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode4;
			REAL threshR = length(z);
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold4)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold4))
			{
				REAL val = fractal->transformCommon.multiplierScale4;

				if (fractal->transformCommon.multiplierInverse4) val = (fabs(val) > 1e-15f) ? (1.0f / val) : 1e15f;

				int vmode = fractal->transformCommon.multiplierValueMode4;
				REAL range = (REAL)(fractal->transformCommon.multiplierStopIter4 - fractal->transformCommon.multiplierStartIter4);
				REAL ph = fractal->transformCommon.multiplierPhase4;
				if (range > 0 && vmode > 0)
				{
					REAL t = (REAL)(aux->i - fractal->transformCommon.multiplierStartIter4) / range;
					REAL freq = fractal->transformCommon.multiplierFrequency4;
					if (vmode == 1) // Sine
					{
						val = 1.0 + (val - 1.0) * native_sin((t * freq + ph) * 2.0 * M_PI_F);
					}
					else if (vmode == 2) // Ramp
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 3) // Exponential
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						val = 1.0 + (val - 1.0) * (native_powr(2.718281828f, t * freq) - 1.0) / (native_powr(2.718281828f, freq) - 1.0);
					}
					else if (vmode == 4) // Triangle
					{
						REAL tri = 1.0 - 2.0 * fabs(fmod(t * freq + ph, 1.0) - 0.5);
						val = 1.0 + (val - 1.0) * tri;
					}
					else if (vmode == 5) // Square
					{
						val = (fmod(t * freq + ph, 1.0) < 0.5) ? val : 1.0;
					}
					else if (vmode == 6) // Smoothstep
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						t = t * t * (3.0 - 2.0 * t);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 7) // Noise
					{
						int seed = aux->i * 73856093 + 4 * 19349663;
						seed = (seed ^ (seed >> 13)) * 1274126177;
						seed = seed ^ (seed >> 16);
						REAL noise = (REAL)(seed & 0xFFFF) / 65535.0;
						val = 1.0 + (val - 1.0) * noise;
					}
					else if (vmode == 8) // Ping-pong
					{
						REAL pp = fmod(t * freq + ph, 2.0);
						if (pp > 1.0) pp = 2.0 - pp;
						val = 1.0 + (val - 1.0) * pp;
					}
					else if (vmode == 9) // Stepped
					{
						REAL steps = freq;
						if (steps < 1.0) steps = 1.0;
						REAL st = floor(t * steps) / steps;
						val = 1.0 + (val - 1.0) * st;
					}
				}

				if (fractal->transformCommon.multiplierChain4) val *= prevMultVal;

				REAL w = fractal->transformCommon.multiplierWeight4;
				val = 1.0 + w * (val - 1.0);

				switch (fractal->transformCommon.multiplierMode4)
				{
					default:
					case 0:
					{
						REAL valY = fractal->transformCommon.multiplierScaleY4;
						REAL valZ = fractal->transformCommon.multiplierScaleZ4;
						if (valY == 0.0) valY = val;
						if (valZ == 0.0) valZ = val;
						z.x *= val; z.y *= valY; z.z *= valZ;
						aux->DE *= fabs(val);
						break;
					}
					case 1: z.x *= val; aux->DE *= fabs(val); break;
					case 2: z.y *= val; aux->DE *= fabs(val); break;
					case 3: z.z *= val; aux->DE *= fabs(val); break;
					case 4: aux->DE *= val; break;
					case 5: aux->color *= val; break;
					case 6: z.w *= val; aux->DE *= fabs(val); break;
					case 7: z.x *= val; z.y *= val; aux->DE *= fabs(val); break;
					case 8: z.x *= val; z.z *= val; aux->DE *= fabs(val); break;
					case 9: z.y *= val; z.z *= val; aux->DE *= fabs(val); break;
					case 10: aux->color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}

		// === General Purpose Multiplier 5 ===
		if (fractal->transformCommon.multiplierEnabled5
				&& aux->i >= fractal->transformCommon.multiplierStartIter5
				&& aux->i < fractal->transformCommon.multiplierStopIter5)
		{
			int tmode = fractal->transformCommon.multiplierThresholdMode5;
			REAL threshR = length(z);
			if (tmode == 0 || (tmode == 1 && threshR > fractal->transformCommon.multiplierThreshold5)
				|| (tmode == 2 && threshR < fractal->transformCommon.multiplierThreshold5))
			{
				REAL val = fractal->transformCommon.multiplierScale5;

				if (fractal->transformCommon.multiplierInverse5) val = (fabs(val) > 1e-15f) ? (1.0f / val) : 1e15f;

				int vmode = fractal->transformCommon.multiplierValueMode5;
				REAL range = (REAL)(fractal->transformCommon.multiplierStopIter5 - fractal->transformCommon.multiplierStartIter5);
				REAL ph = fractal->transformCommon.multiplierPhase5;
				if (range > 0 && vmode > 0)
				{
					REAL t = (REAL)(aux->i - fractal->transformCommon.multiplierStartIter5) / range;
					REAL freq = fractal->transformCommon.multiplierFrequency5;
					if (vmode == 1) // Sine
					{
						val = 1.0 + (val - 1.0) * native_sin((t * freq + ph) * 2.0 * M_PI_F);
					}
					else if (vmode == 2) // Ramp
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 3) // Exponential
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						val = 1.0 + (val - 1.0) * (native_powr(2.718281828f, t * freq) - 1.0) / (native_powr(2.718281828f, freq) - 1.0);
					}
					else if (vmode == 4) // Triangle
					{
						REAL tri = 1.0 - 2.0 * fabs(fmod(t * freq + ph, 1.0) - 0.5);
						val = 1.0 + (val - 1.0) * tri;
					}
					else if (vmode == 5) // Square
					{
						val = (fmod(t * freq + ph, 1.0) < 0.5) ? val : 1.0;
					}
					else if (vmode == 6) // Smoothstep
					{
						t = clamp(t, (REAL)0.0, (REAL)1.0);
						t = t * t * (3.0 - 2.0 * t);
						val = 1.0 + t * (val - 1.0);
					}
					else if (vmode == 7) // Noise
					{
						int seed = aux->i * 73856093 + 5 * 19349663;
						seed = (seed ^ (seed >> 13)) * 1274126177;
						seed = seed ^ (seed >> 16);
						REAL noise = (REAL)(seed & 0xFFFF) / 65535.0;
						val = 1.0 + (val - 1.0) * noise;
					}
					else if (vmode == 8) // Ping-pong
					{
						REAL pp = fmod(t * freq + ph, 2.0);
						if (pp > 1.0) pp = 2.0 - pp;
						val = 1.0 + (val - 1.0) * pp;
					}
					else if (vmode == 9) // Stepped
					{
						REAL steps = freq;
						if (steps < 1.0) steps = 1.0;
						REAL st = floor(t * steps) / steps;
						val = 1.0 + (val - 1.0) * st;
					}
				}

				if (fractal->transformCommon.multiplierChain5) val *= prevMultVal;

				REAL w = fractal->transformCommon.multiplierWeight5;
				val = 1.0 + w * (val - 1.0);

				switch (fractal->transformCommon.multiplierMode5)
				{
					default:
					case 0:
					{
						REAL valY = fractal->transformCommon.multiplierScaleY5;
						REAL valZ = fractal->transformCommon.multiplierScaleZ5;
						if (valY == 0.0) valY = val;
						if (valZ == 0.0) valZ = val;
						z.x *= val; z.y *= valY; z.z *= valZ;
						aux->DE *= fabs(val);
						break;
					}
					case 1: z.x *= val; aux->DE *= fabs(val); break;
					case 2: z.y *= val; aux->DE *= fabs(val); break;
					case 3: z.z *= val; aux->DE *= fabs(val); break;
					case 4: aux->DE *= val; break;
					case 5: aux->color *= val; break;
					case 6: z.w *= val; aux->DE *= fabs(val); break;
					case 7: z.x *= val; z.y *= val; aux->DE *= fabs(val); break;
					case 8: z.x *= val; z.z *= val; aux->DE *= fabs(val); break;
					case 9: z.y *= val; z.z *= val; aux->DE *= fabs(val); break;
					case 10: aux->color += fabs(val - 1.0) * 100.0; break;
				}
				prevMultVal = val;
			}
		}
	}

	return z;
}
