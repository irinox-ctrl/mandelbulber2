/**
 * Mandelbulber v2, a 3D fractal generator  _%}}i*<.         ______
 * Copyright (C) 2020 Mandelbulber Team   _>]|=||i=i<,      / ____/ __    __
 *                                        \><||i|=>>%)     / /   __/ /___/ /_
 * This file is part of Mandelbulber.     )<=i=]=|=i<>    / /__ /_  __/_  __/
 * The project is licensed under GPLv3,   -<>>=|><|||`    \____/ /_/   /_/
 * see also COPYING file in this folder.    ~+{i%+++
 *
 * GeneralizedFoldBoxIteration - Prototype Tinker Towers
 * @reference http://www.fractalforums.com/new-theories-and-research/tinker-towers/
 * This formula contains aux.color
 */

#include "all_fractal_definitions.h"

cFractalTinkerTowers::cFractalTinkerTowers() : cAbstractFractal()
{
	nameInComboBox = "Tinker Towers";
	internalName = "tinker_towers";
	internalID = fractal::tinkerTowers;
	DEType = analyticDEType;
	DEFunctionType = logarithmicDEFunction;
	cpixelAddition = cpixelEnabledByDefault;
	defaultBailout = 100.0;
	DEAnalyticFunction = analyticFunctionLogarithmic;
	coloringFunction = coloringFunctionDefault;
}

void cFractalTinkerTowers::FormulaCode(
	CVector4 &z, const sFractal *fractal, sExtendedAux &aux)
{
	double t = 0.0;
	CVector3 tv = CVector3(0.0, 0.0, 0.0);
	CVector3 zXYZ = z.GetXYZ();

	CVector3 u_zXYZ = CVector3(0.0, 0.0, 1.0); // angle does matter if mag_zXYZ==0
	double mag_zXYZ = 0.0;

	t = zXYZ.Dot(zXYZ);
	if(t > 0.0)
	{
		t = sqrt(t);
		u_zXYZ = zXYZ / t;
		mag_zXYZ = t;
	}


	double flat = 0.0;
	int sides;
	int i;


	// By defination u_Fv are unit vectors (rays) that define the orentation of the facets that cut a unit sphere.
	// The Nv vectors need to be scaled by a number between 0 and 1, mag_Fv, in order to cut the unit sphere.
	// They don't have to be scaled by the same amount, but every facit must contain its definining u_Fv vector.

	const CVector3 *u_Fv;

	switch (fractal->genFoldBox.type)
	{
		default:
		case generalizedFoldBoxType_foldTet:
			u_Fv = fractal->genFoldBox.Nv_tet;
			sides = fractal->genFoldBox.sides_tet;
			break;
		case generalizedFoldBoxType_foldCube:
			u_Fv = fractal->genFoldBox.Nv_cube;
			sides = fractal->genFoldBox.sides_cube;
			break;
		case generalizedFoldBoxType_foldOct:
			u_Fv = fractal->genFoldBox.Nv_oct;
			sides = fractal->genFoldBox.sides_oct;
			break;
		case generalizedFoldBoxType_foldDodeca:
			u_Fv = fractal->genFoldBox.Nv_dodeca;
			sides = fractal->genFoldBox.sides_dodeca;
			break;
		case generalizedFoldBoxType_foldOctCube:
			u_Fv = fractal->genFoldBox.Nv_oct_cube;
			sides = fractal->genFoldBox.sides_oct_cube;
			break;
		case generalizedFoldBoxType_foldIcosa:
			u_Fv = fractal->genFoldBox.Nv_icosa;
			sides = fractal->genFoldBox.sides_icosa;
			break;
		case generalizedFoldBoxType_foldBox6:
			u_Fv = fractal->genFoldBox.Nv_box6;
			sides = fractal->genFoldBox.sides_box6;
			break;
		case generalizedFoldBoxType_foldBox5:
			u_Fv = fractal->genFoldBox.Nv_box5;
			sides = fractal->genFoldBox.sides_box5;
			break;
	}

	// melt is going to be used to control the u_Fv vector height.
	// The height must be between 0 and 1 to cut the unit sphere
	// The magnetude does not need to be equal, but u_Fv must not be cut from the face.
	double melt = fractal->transformCommon.offset05;
	double mag_Fv[64];
	for (i = 0; i < sides; i++)
	{
		mag_Fv[i] = melt;
	}

	//
	// Scale is used as the power.
	double power = fractal->transformCommon.pwr4;
	// fractal->transformCommon.functionEnabledAFalse is used for selecting fractal(disabled) or target map(enabled).
//	double solid = fractal->mandelbox.solid;


	// Find the lowest cutting plane that cuts the ray from the origin through zXYZ.
	// The parameterized equation for this ray is L_Z(h) = h * u_zXYX.
	// The plane equation is X dot u_Fv = mag_Fv;
	// The value of h at the intersection point is h = mag_Fv/(u_zXYZ dot u_Fv)

	int side = -1; // Assume no facet found before unit sphere.
	double h = 1.0; // so h=1.
	double my_h;
	for (i = 0; i < sides; i++)
	{
		my_h = 2.0; // just needs to be >1
		double u_zXYZ_dot_u_Fvi = u_zXYZ.Dot(u_Fv[i]);
		if(u_zXYZ_dot_u_Fvi > 0.0)
		{
			my_h = mag_Fv[i] / u_zXYZ_dot_u_Fvi;
		}
		if(my_h < h)
		{
			h = my_h;
			side = i;
		}
	}
	// Did we hit a cutting plane in the unit sphere.
	// If so calculate the ratio of the distance from u_Fv through the point
	// of intersection of ray (Zc) to either another cutting plane or
	// the unit sphere if there are none.
	// Zc = h * zXYZ
	double w, my_w;
	int edge = -1;
	CVector3 Zc;
	// The intersection point is Zc.
	Zc = h * u_zXYZ;

	if (side != -1)
	{
		// The parameterized formula for the line from u_Fv through Zi is
		// L_u_Fv_Zc(w) = w * unit_vector(Zc - mag_Fv * u_Fv).

		// Using dot product to estimate ratio of u_Fv[side] to Zc to NV[side] to edge of facit
		// u_Fv[side] dot u_Fv[side] = 1;
		// u_Fv[side] dot Zc = h;
		// u_Fv[side] dot unclipped circle = mag_Fv.

		tv = (Zc - mag_Fv[side] * u_Fv[side]);
		t = tv.Dot(Zc - mag_Fv[side] * u_Fv[side]); // mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
		double D_u_Fv_to_Zc = sqrt(t);
		// double D_u_Fv_to_Zc = sqrt((Zc - mag_Fv[side] * u_Fv[side]).Dot(Zc - mag_Fv[side] * u_Fv[side]));

		CVector3 u_Fv_to_Zc = (Zc - mag_Fv[side] * u_Fv[side]);
		//CVector3 u_Fv_to_Zc;
		if (D_u_Fv_to_Zc > 0.0)
		{
			u_Fv_to_Zc = u_Fv_to_Zc / D_u_Fv_to_Zc;
		}

		// Assume no cutting plane before the unit sphere.
		// Find the distancd from u_Fv to edge of sphere.
		w = sqrt(1.0 - mag_Fv[side] * mag_Fv[side]);

		for (i = 0; i < sides; i++)
		{
			// Don't check side found in step 1.
			if(side != i)
			{
			// avoid dividing by zero.
				if( (u_Fv_to_Zc.Dot(u_Fv[i])) > 0.0)
				{
				// Distance from mag_Fv * u_Fv to cutting plane i.
					my_w = (mag_Fv[i] - mag_Fv[side] * (u_Fv[side].Dot(u_Fv[i]))) / (u_Fv_to_Zc.Dot(u_Fv[i]));

					if(my_w < w)
					{
						w = my_w;
						edge = i;
					}
				}
			}
		}
		// w is the distance between u_Fv[side] and either an edge (cutting plane mag_Fv * u_Fv[edge])
		// The ratio of the distance (|mag_nv * u_Fv - Zc|)/w is the radial parameter for the patch map.

		double D = 0.0;
		CVector3  Axis = CVector3(0.0, 0.0, 1.0); // angle does not matter if D=0;
		//D = sqrt((Zc - mag_Fv * u_Fv[side]).Dot(Zc - mag_Fv * u_Fv[side]))/w;
		if (w > 0.0)
		{
			D = D_u_Fv_to_Zc / w;
			Axis = u_Fv[side].Cross(zXYZ);
			Axis = Axis / sqrt(Axis.Dot(Axis));
		}
		flat = Zc.Dot(u_zXYZ);
		if (!fractal->transformCommon.functionEnabledAFalse)
		{
			//if(D>1.0){printf("HERE");}
			// double rot_angle = 3.14159*(1-D*D)*(1-D*D);  // force detail away from edges and center.
			//double rot_angle = 3.14159*(1-D)*(1-D); // Move detail toward center.
			//double rot_angle = 3.14159*(1-D*D); // Move detail tword edge.
			//double rot_angle = 3.14159*(1-.3 * D*D - .7*D);  // Mixing
			double rot_angle = M_PI * (1.0 - D); // Linear

			//Sign of rot_angel determines the patch includes self
			//rot_angle = rot_angle * ((side & 2)-1); // mix it up

			if (!fractal->transformCommon.functionEnabledBFalse) {rot_angle = -rot_angle;}
			//rot_angle = rot_angle;  // Exclude self
			//rot_angle = -rot_angle; // Include self

			//zXYZ = zXYZ *(1.0 - .0*flat);  // Does not play well with power DE
			//zXYZ =  zXYZ.RotateAroundVectorByAngle(u_Fv[side], 3.14159/3.0); // Taffy

            CVector4 v4 = CVector4(zXYZ.x, zXYZ.y, zXYZ.z, 0.0);
            v4 = v4.RotateAroundVectorByAngle(Axis, rot_angle);  // php angel4 ?? mmmmmmmmmmmfix
            zXYZ = CVector3(v4.x, v4.y, v4.z);

		}
		else
		{
			zXYZ = zXYZ / flat;
			double ramp = 5.0 * D - (int)(5.0 * D); // (int)
			double saw = -1.0 + 2.0 * fabs(ramp - 0.5); // fabs
			saw = (saw + 0.6) + fabs(saw + 0.6); // fabs
			saw = 0.02 * saw * saw;
			double rings = 1.0 - (saw * (1.0 - 0.1 * ramp));
			if (D < 0.02) rings = rings * 0.98;
			zXYZ = zXYZ * rings;
		}

	}

	// zXYZ ray hits unit sphere first.

	double rp = pow(mag_zXYZ, power - 1.0); // what about julia bulb or proper bulb

	aux.DE = rp * aux.DE * power + 1.0;

	zXYZ = zXYZ * rp;


	aux.DE = aux.DE * fractal->analyticDE.scale1 + fractal->analyticDE.offset0;
	z = CVector4(zXYZ, z.w);
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

							// Decay
							if (fractal->transformCommon.multiplierDecay1 > 0.0)
							{
								double dcy = fractal->transformCommon.multiplierDecay1;
								double rng = (double)(fractal->transformCommon.multiplierStopIter1 - fractal->transformCommon.multiplierStartIter1);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter1) / rng : 0.0;
								val = 1.0 + (val - 1.0) * exp(-dcy * td * 5.0);
							}
							// Exponent
							if (fractal->transformCommon.multiplierExponent1 != 1.0)
							{
								double ep = fractal->transformCommon.multiplierExponent1;
								double sgn = (val >= 1.0) ? 1.0 : -1.0;
								val = 1.0 + sgn * pow(fabs(val - 1.0) + 1e-30, ep);
							}
							// Offset
							val += fractal->transformCommon.multiplierOffset1;

							// Delay
							if (fractal->transformCommon.multiplierDelay1 > 0
								&& aux.i < fractal->transformCommon.multiplierStartIter1 + fractal->transformCommon.multiplierDelay1)
								val = 1.0;
							// Iteration Modulo
							if (fractal->transformCommon.multiplierIterModulo1 > 1
								&& ((aux.i - fractal->transformCommon.multiplierStartIter1) % fractal->transformCommon.multiplierIterModulo1) != 0)
								val = 1.0;
							// Attack envelope
							if (fractal->transformCommon.multiplierAttack1 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter1 - fractal->transformCommon.multiplierStartIter1);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter1) / rng : 1.0;
								double att = fractal->transformCommon.multiplierAttack1;
								if (td < att) val = 1.0 + (val - 1.0) * (td / att);
							}
							// Release envelope
							if (fractal->transformCommon.multiplierRelease1 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter1 - fractal->transformCommon.multiplierStartIter1);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter1) / rng : 1.0;
								double rel = fractal->transformCommon.multiplierRelease1;
								if (td > (1.0 - rel)) val = 1.0 + (val - 1.0) * ((1.0 - td) / rel);
							}
							// Feedback
							if (fractal->transformCommon.multiplierFeedback1 > 0.0)
							{
								double fb = fractal->transformCommon.multiplierFeedback1;
								val = 1.0 + (val - 1.0) * (1.0 - fb) + (prevMultVal - 1.0) * fb;
							}
							// Harmonics
							if (fractal->transformCommon.multiplierHarmonics1 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter1 - fractal->transformCommon.multiplierStartIter1);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter1) / rng : 0.0;
								double hrm = fractal->transformCommon.multiplierHarmonics1;
								double frq = fractal->transformCommon.multiplierFrequency1;
								val += hrm * sin(4.0 * M_PI * frq * td) * fabs(val - 1.0);
							}
							// Pulse Width
							if (fractal->transformCommon.multiplierPulseWidth1 != 0.5)
							{
								double pw = fractal->transformCommon.multiplierPulseWidth1;
								double diff = val - 1.0;
								double sgn = (diff >= 0.0) ? 1.0 : -1.0;
								double mg = fabs(diff) + 1e-30;
								val = 1.0 + sgn * pow(mg, 1.0 / (2.0 * fmax(pw, 0.01)));
							}
							// Mirror
							if (fractal->transformCommon.multiplierMirror1 && val < 1.0)
								val = 2.0 - val;
							// Quantize
							if (fractal->transformCommon.multiplierQuantize1 > 0)
							{
								double step = 1.0 / (double)fractal->transformCommon.multiplierQuantize1;
								val = 1.0 + floor((val - 1.0) / step + 0.5) * step;
							}
							// Symmetry Break
							if (fractal->transformCommon.multiplierSymmetryBreak1 != 0.0)
							{
								double sb = fractal->transformCommon.multiplierSymmetryBreak1;
								double diff = val - 1.0;
								val = (diff > 0.0) ? 1.0 + diff * (1.0 + sb) : 1.0 + diff * (1.0 - sb);
							}
							// Clamp
							if (val < fractal->transformCommon.multiplierClampMin1) val = fractal->transformCommon.multiplierClampMin1;
							if (val > fractal->transformCommon.multiplierClampMax1) val = fractal->transformCommon.multiplierClampMax1;
							// Soft Clip
							if (fractal->transformCommon.multiplierSoftClip1 > 0.0)
							{
								double sc = fractal->transformCommon.multiplierSoftClip1;
								double diff = val - 1.0;
								val = 1.0 + diff / (1.0 + sc * fabs(diff));
							}
							// Radial Falloff
							if (fractal->transformCommon.multiplierRadialFalloff1 > 0.0)
							{
								double rf = fractal->transformCommon.multiplierRadialFalloff1;
								double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0 + (val - 1.0) * exp(-rf * r);
							}
							// Angular Bias
							if (fractal->transformCommon.multiplierAngularBias1 != 0.0)
							{
								double ab = fractal->transformCommon.multiplierAngularBias1;
								double angle = atan2(z.y, z.x);
								double bias = 0.5 + 0.5 * cos(angle - ab * M_PI / 180.0);
								val = 1.0 + (val - 1.0) * bias;
							}
							// Polar Mode
							if (fractal->transformCommon.multiplierPolarMode1)
							{
								double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0 + (val - 1.0) * (1.0 + 0.5 * sin(r));
							}
							// Cross-axis Coupling
							if (fractal->transformCommon.multiplierCrossCoupling1 > 0.0)
							{
								double cc = fractal->transformCommon.multiplierCrossCoupling1;
								double leak = (val - 1.0) * cc * 0.1;
								z.x += leak * z.y;
								z.y += leak * z.z;
								z.z += leak * z.x;
							}
							// Noise addition
							if (fractal->transformCommon.multiplierNoiseSeed1 > 0)
							{
								int seed = fractal->transformCommon.multiplierNoiseSeed1;
								int oct = fractal->transformCommon.multiplierNoiseOctaves1;
								double nv = 0.0;
								double amp = 1.0;
								for (int o = 0; o < oct; o++)
								{
									double ph = (double)(aux.i * 1237 + seed * 7919 + o * 4621);
									nv += amp * sin(ph * 0.0031415);
									amp *= 0.5;
								}
								val += nv * fabs(val - 1.0) * 0.3;
							}
							// Blend Mode: 0=normal, 1=shrink-only, 2=grow-only, 3=abs, 4=smooth
							{
								int bm = fractal->transformCommon.multiplierBlendMode1;
								if (bm == 1 && val > 1.0) val = 1.0;
								else if (bm == 2 && val < 1.0) val = 1.0;
								else if (bm == 3) val = 1.0 + fabs(val - 1.0);
								else if (bm == 4) { double sv = fmin(fmax((val - 0.5) * 1.0, 0.0), 1.0); val = 0.5 + sv * sv * (3.0 - 2.0 * sv); }
							}

							// Clip Drive (pre-gain)
							if (fractal->transformCommon.multiplierClipDrive1 != 1.0)
							{
								double drv = fractal->transformCommon.multiplierClipDrive1;
								val = 1.0 + (val - 1.0) * drv;
							}
							// Clip Rectify: 0=off, 1=half(clamp neg to 0), 2=full(abs)
							{
								int cr = fractal->transformCommon.multiplierClipRectify1;
								if (cr == 1 && val < 1.0) val = 1.0;
								else if (cr == 2) val = 1.0 + fabs(val - 1.0);
							}
							// Clip Fold (wavefolder)
							if (fractal->transformCommon.multiplierClipFold1)
							{
								int folds = fractal->transformCommon.multiplierClipFoldCount1;
								if (folds < 1) folds = 1;
								double ceil = fractal->transformCommon.multiplierClipCeiling1;
								double flr = fractal->transformCommon.multiplierClipFloor1;
								for (int fi = 0; fi < folds; fi++)
								{
									if (val > ceil) val = 2.0 * ceil - val;
									if (val < flr) val = 2.0 * flr - val;
								}
							}
							// Clip Ceiling / Floor (hard clamp with asymmetry)
							if (!fractal->transformCommon.multiplierClipFold1)
							{
								double ceil = fractal->transformCommon.multiplierClipCeiling1;
								double flr = fractal->transformCommon.multiplierClipFloor1;
								double asym = fractal->transformCommon.multiplierClipAsymmetry1;
								ceil += asym;
								flr -= asym;
								// Clip Curve (soft knee)
								double curve = fractal->transformCommon.multiplierClipCurve1;
								double knee = fractal->transformCommon.multiplierClipKnee1;
								if (curve > 0.0 || knee > 0.0)
								{
									double k = fmax(knee, 0.001);
									if (val > ceil - k)
									{
										double x = (val - (ceil - k)) / (2.0 * k);
										x = fmin(fmax(x, 0.0), 1.0);
										double sm = x * x * (3.0 - 2.0 * x);
										val = (ceil - k) + k * sm * (1.0 + curve);
										if (val > ceil) val = ceil;
									}
									if (val < flr + k)
									{
										double x = ((flr + k) - val) / (2.0 * k);
										x = fmin(fmax(x, 0.0), 1.0);
										double sm = x * x * (3.0 - 2.0 * x);
										val = (flr + k) - k * sm * (1.0 + curve);
										if (val < flr) val = flr;
									}
								}
								else
								{
									if (val > ceil) val = ceil;
									if (val < flr) val = flr;
								}
							}
							// Clip Mix (blend clipped/unclipped)
							if (fractal->transformCommon.multiplierClipMix1 < 1.0)
							{
								double mx = fractal->transformCommon.multiplierClipMix1;
								// val is already clipped; recover original from drive
								// approximate: mix toward 1.0 (neutral)
								val = 1.0 + mx * (val - 1.0);
							}

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

							// Decay
							if (fractal->transformCommon.multiplierDecay2 > 0.0)
							{
								double dcy = fractal->transformCommon.multiplierDecay2;
								double rng = (double)(fractal->transformCommon.multiplierStopIter2 - fractal->transformCommon.multiplierStartIter2);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter2) / rng : 0.0;
								val = 1.0 + (val - 1.0) * exp(-dcy * td * 5.0);
							}
							// Exponent
							if (fractal->transformCommon.multiplierExponent2 != 1.0)
							{
								double ep = fractal->transformCommon.multiplierExponent2;
								double sgn = (val >= 1.0) ? 1.0 : -1.0;
								val = 1.0 + sgn * pow(fabs(val - 1.0) + 1e-30, ep);
							}
							// Offset
							val += fractal->transformCommon.multiplierOffset2;

							// Delay
							if (fractal->transformCommon.multiplierDelay2 > 0
								&& aux.i < fractal->transformCommon.multiplierStartIter2 + fractal->transformCommon.multiplierDelay2)
								val = 1.0;
							// Iteration Modulo
							if (fractal->transformCommon.multiplierIterModulo2 > 1
								&& ((aux.i - fractal->transformCommon.multiplierStartIter2) % fractal->transformCommon.multiplierIterModulo2) != 0)
								val = 1.0;
							// Attack envelope
							if (fractal->transformCommon.multiplierAttack2 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter2 - fractal->transformCommon.multiplierStartIter2);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter2) / rng : 1.0;
								double att = fractal->transformCommon.multiplierAttack2;
								if (td < att) val = 1.0 + (val - 1.0) * (td / att);
							}
							// Release envelope
							if (fractal->transformCommon.multiplierRelease2 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter2 - fractal->transformCommon.multiplierStartIter2);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter2) / rng : 1.0;
								double rel = fractal->transformCommon.multiplierRelease2;
								if (td > (1.0 - rel)) val = 1.0 + (val - 1.0) * ((1.0 - td) / rel);
							}
							// Feedback
							if (fractal->transformCommon.multiplierFeedback2 > 0.0)
							{
								double fb = fractal->transformCommon.multiplierFeedback2;
								val = 1.0 + (val - 1.0) * (1.0 - fb) + (prevMultVal - 1.0) * fb;
							}
							// Harmonics
							if (fractal->transformCommon.multiplierHarmonics2 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter2 - fractal->transformCommon.multiplierStartIter2);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter2) / rng : 0.0;
								double hrm = fractal->transformCommon.multiplierHarmonics2;
								double frq = fractal->transformCommon.multiplierFrequency2;
								val += hrm * sin(4.0 * M_PI * frq * td) * fabs(val - 1.0);
							}
							// Pulse Width
							if (fractal->transformCommon.multiplierPulseWidth2 != 0.5)
							{
								double pw = fractal->transformCommon.multiplierPulseWidth2;
								double diff = val - 1.0;
								double sgn = (diff >= 0.0) ? 1.0 : -1.0;
								double mg = fabs(diff) + 1e-30;
								val = 1.0 + sgn * pow(mg, 1.0 / (2.0 * fmax(pw, 0.01)));
							}
							// Mirror
							if (fractal->transformCommon.multiplierMirror2 && val < 1.0)
								val = 2.0 - val;
							// Quantize
							if (fractal->transformCommon.multiplierQuantize2 > 0)
							{
								double step = 1.0 / (double)fractal->transformCommon.multiplierQuantize2;
								val = 1.0 + floor((val - 1.0) / step + 0.5) * step;
							}
							// Symmetry Break
							if (fractal->transformCommon.multiplierSymmetryBreak2 != 0.0)
							{
								double sb = fractal->transformCommon.multiplierSymmetryBreak2;
								double diff = val - 1.0;
								val = (diff > 0.0) ? 1.0 + diff * (1.0 + sb) : 1.0 + diff * (1.0 - sb);
							}
							// Clamp
							if (val < fractal->transformCommon.multiplierClampMin2) val = fractal->transformCommon.multiplierClampMin2;
							if (val > fractal->transformCommon.multiplierClampMax2) val = fractal->transformCommon.multiplierClampMax2;
							// Soft Clip
							if (fractal->transformCommon.multiplierSoftClip2 > 0.0)
							{
								double sc = fractal->transformCommon.multiplierSoftClip2;
								double diff = val - 1.0;
								val = 1.0 + diff / (1.0 + sc * fabs(diff));
							}
							// Radial Falloff
							if (fractal->transformCommon.multiplierRadialFalloff2 > 0.0)
							{
								double rf = fractal->transformCommon.multiplierRadialFalloff2;
								double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0 + (val - 1.0) * exp(-rf * r);
							}
							// Angular Bias
							if (fractal->transformCommon.multiplierAngularBias2 != 0.0)
							{
								double ab = fractal->transformCommon.multiplierAngularBias2;
								double angle = atan2(z.y, z.x);
								double bias = 0.5 + 0.5 * cos(angle - ab * M_PI / 180.0);
								val = 1.0 + (val - 1.0) * bias;
							}
							// Polar Mode
							if (fractal->transformCommon.multiplierPolarMode2)
							{
								double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0 + (val - 1.0) * (1.0 + 0.5 * sin(r));
							}
							// Cross-axis Coupling
							if (fractal->transformCommon.multiplierCrossCoupling2 > 0.0)
							{
								double cc = fractal->transformCommon.multiplierCrossCoupling2;
								double leak = (val - 1.0) * cc * 0.1;
								z.x += leak * z.y;
								z.y += leak * z.z;
								z.z += leak * z.x;
							}
							// Noise addition
							if (fractal->transformCommon.multiplierNoiseSeed2 > 0)
							{
								int seed = fractal->transformCommon.multiplierNoiseSeed2;
								int oct = fractal->transformCommon.multiplierNoiseOctaves2;
								double nv = 0.0;
								double amp = 1.0;
								for (int o = 0; o < oct; o++)
								{
									double ph = (double)(aux.i * 1237 + seed * 7919 + o * 4621);
									nv += amp * sin(ph * 0.0031415);
									amp *= 0.5;
								}
								val += nv * fabs(val - 1.0) * 0.3;
							}
							// Blend Mode: 0=normal, 1=shrink-only, 2=grow-only, 3=abs, 4=smooth
							{
								int bm = fractal->transformCommon.multiplierBlendMode2;
								if (bm == 1 && val > 1.0) val = 1.0;
								else if (bm == 2 && val < 1.0) val = 1.0;
								else if (bm == 3) val = 1.0 + fabs(val - 1.0);
								else if (bm == 4) { double sv = fmin(fmax((val - 0.5) * 1.0, 0.0), 1.0); val = 0.5 + sv * sv * (3.0 - 2.0 * sv); }
							}

							// Clip Drive (pre-gain)
							if (fractal->transformCommon.multiplierClipDrive2 != 1.0)
							{
								double drv = fractal->transformCommon.multiplierClipDrive2;
								val = 1.0 + (val - 1.0) * drv;
							}
							// Clip Rectify: 0=off, 1=half(clamp neg to 0), 2=full(abs)
							{
								int cr = fractal->transformCommon.multiplierClipRectify2;
								if (cr == 1 && val < 1.0) val = 1.0;
								else if (cr == 2) val = 1.0 + fabs(val - 1.0);
							}
							// Clip Fold (wavefolder)
							if (fractal->transformCommon.multiplierClipFold2)
							{
								int folds = fractal->transformCommon.multiplierClipFoldCount2;
								if (folds < 1) folds = 1;
								double ceil = fractal->transformCommon.multiplierClipCeiling2;
								double flr = fractal->transformCommon.multiplierClipFloor2;
								for (int fi = 0; fi < folds; fi++)
								{
									if (val > ceil) val = 2.0 * ceil - val;
									if (val < flr) val = 2.0 * flr - val;
								}
							}
							// Clip Ceiling / Floor (hard clamp with asymmetry)
							if (!fractal->transformCommon.multiplierClipFold2)
							{
								double ceil = fractal->transformCommon.multiplierClipCeiling2;
								double flr = fractal->transformCommon.multiplierClipFloor2;
								double asym = fractal->transformCommon.multiplierClipAsymmetry2;
								ceil += asym;
								flr -= asym;
								// Clip Curve (soft knee)
								double curve = fractal->transformCommon.multiplierClipCurve2;
								double knee = fractal->transformCommon.multiplierClipKnee2;
								if (curve > 0.0 || knee > 0.0)
								{
									double k = fmax(knee, 0.001);
									if (val > ceil - k)
									{
										double x = (val - (ceil - k)) / (2.0 * k);
										x = fmin(fmax(x, 0.0), 1.0);
										double sm = x * x * (3.0 - 2.0 * x);
										val = (ceil - k) + k * sm * (1.0 + curve);
										if (val > ceil) val = ceil;
									}
									if (val < flr + k)
									{
										double x = ((flr + k) - val) / (2.0 * k);
										x = fmin(fmax(x, 0.0), 1.0);
										double sm = x * x * (3.0 - 2.0 * x);
										val = (flr + k) - k * sm * (1.0 + curve);
										if (val < flr) val = flr;
									}
								}
								else
								{
									if (val > ceil) val = ceil;
									if (val < flr) val = flr;
								}
							}
							// Clip Mix (blend clipped/unclipped)
							if (fractal->transformCommon.multiplierClipMix2 < 1.0)
							{
								double mx = fractal->transformCommon.multiplierClipMix2;
								// val is already clipped; recover original from drive
								// approximate: mix toward 1.0 (neutral)
								val = 1.0 + mx * (val - 1.0);
							}

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

							// Decay
							if (fractal->transformCommon.multiplierDecay3 > 0.0)
							{
								double dcy = fractal->transformCommon.multiplierDecay3;
								double rng = (double)(fractal->transformCommon.multiplierStopIter3 - fractal->transformCommon.multiplierStartIter3);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter3) / rng : 0.0;
								val = 1.0 + (val - 1.0) * exp(-dcy * td * 5.0);
							}
							// Exponent
							if (fractal->transformCommon.multiplierExponent3 != 1.0)
							{
								double ep = fractal->transformCommon.multiplierExponent3;
								double sgn = (val >= 1.0) ? 1.0 : -1.0;
								val = 1.0 + sgn * pow(fabs(val - 1.0) + 1e-30, ep);
							}
							// Offset
							val += fractal->transformCommon.multiplierOffset3;

							// Delay
							if (fractal->transformCommon.multiplierDelay3 > 0
								&& aux.i < fractal->transformCommon.multiplierStartIter3 + fractal->transformCommon.multiplierDelay3)
								val = 1.0;
							// Iteration Modulo
							if (fractal->transformCommon.multiplierIterModulo3 > 1
								&& ((aux.i - fractal->transformCommon.multiplierStartIter3) % fractal->transformCommon.multiplierIterModulo3) != 0)
								val = 1.0;
							// Attack envelope
							if (fractal->transformCommon.multiplierAttack3 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter3 - fractal->transformCommon.multiplierStartIter3);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter3) / rng : 1.0;
								double att = fractal->transformCommon.multiplierAttack3;
								if (td < att) val = 1.0 + (val - 1.0) * (td / att);
							}
							// Release envelope
							if (fractal->transformCommon.multiplierRelease3 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter3 - fractal->transformCommon.multiplierStartIter3);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter3) / rng : 1.0;
								double rel = fractal->transformCommon.multiplierRelease3;
								if (td > (1.0 - rel)) val = 1.0 + (val - 1.0) * ((1.0 - td) / rel);
							}
							// Feedback
							if (fractal->transformCommon.multiplierFeedback3 > 0.0)
							{
								double fb = fractal->transformCommon.multiplierFeedback3;
								val = 1.0 + (val - 1.0) * (1.0 - fb) + (prevMultVal - 1.0) * fb;
							}
							// Harmonics
							if (fractal->transformCommon.multiplierHarmonics3 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter3 - fractal->transformCommon.multiplierStartIter3);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter3) / rng : 0.0;
								double hrm = fractal->transformCommon.multiplierHarmonics3;
								double frq = fractal->transformCommon.multiplierFrequency3;
								val += hrm * sin(4.0 * M_PI * frq * td) * fabs(val - 1.0);
							}
							// Pulse Width
							if (fractal->transformCommon.multiplierPulseWidth3 != 0.5)
							{
								double pw = fractal->transformCommon.multiplierPulseWidth3;
								double diff = val - 1.0;
								double sgn = (diff >= 0.0) ? 1.0 : -1.0;
								double mg = fabs(diff) + 1e-30;
								val = 1.0 + sgn * pow(mg, 1.0 / (2.0 * fmax(pw, 0.01)));
							}
							// Mirror
							if (fractal->transformCommon.multiplierMirror3 && val < 1.0)
								val = 2.0 - val;
							// Quantize
							if (fractal->transformCommon.multiplierQuantize3 > 0)
							{
								double step = 1.0 / (double)fractal->transformCommon.multiplierQuantize3;
								val = 1.0 + floor((val - 1.0) / step + 0.5) * step;
							}
							// Symmetry Break
							if (fractal->transformCommon.multiplierSymmetryBreak3 != 0.0)
							{
								double sb = fractal->transformCommon.multiplierSymmetryBreak3;
								double diff = val - 1.0;
								val = (diff > 0.0) ? 1.0 + diff * (1.0 + sb) : 1.0 + diff * (1.0 - sb);
							}
							// Clamp
							if (val < fractal->transformCommon.multiplierClampMin3) val = fractal->transformCommon.multiplierClampMin3;
							if (val > fractal->transformCommon.multiplierClampMax3) val = fractal->transformCommon.multiplierClampMax3;
							// Soft Clip
							if (fractal->transformCommon.multiplierSoftClip3 > 0.0)
							{
								double sc = fractal->transformCommon.multiplierSoftClip3;
								double diff = val - 1.0;
								val = 1.0 + diff / (1.0 + sc * fabs(diff));
							}
							// Radial Falloff
							if (fractal->transformCommon.multiplierRadialFalloff3 > 0.0)
							{
								double rf = fractal->transformCommon.multiplierRadialFalloff3;
								double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0 + (val - 1.0) * exp(-rf * r);
							}
							// Angular Bias
							if (fractal->transformCommon.multiplierAngularBias3 != 0.0)
							{
								double ab = fractal->transformCommon.multiplierAngularBias3;
								double angle = atan2(z.y, z.x);
								double bias = 0.5 + 0.5 * cos(angle - ab * M_PI / 180.0);
								val = 1.0 + (val - 1.0) * bias;
							}
							// Polar Mode
							if (fractal->transformCommon.multiplierPolarMode3)
							{
								double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0 + (val - 1.0) * (1.0 + 0.5 * sin(r));
							}
							// Cross-axis Coupling
							if (fractal->transformCommon.multiplierCrossCoupling3 > 0.0)
							{
								double cc = fractal->transformCommon.multiplierCrossCoupling3;
								double leak = (val - 1.0) * cc * 0.1;
								z.x += leak * z.y;
								z.y += leak * z.z;
								z.z += leak * z.x;
							}
							// Noise addition
							if (fractal->transformCommon.multiplierNoiseSeed3 > 0)
							{
								int seed = fractal->transformCommon.multiplierNoiseSeed3;
								int oct = fractal->transformCommon.multiplierNoiseOctaves3;
								double nv = 0.0;
								double amp = 1.0;
								for (int o = 0; o < oct; o++)
								{
									double ph = (double)(aux.i * 1237 + seed * 7919 + o * 4621);
									nv += amp * sin(ph * 0.0031415);
									amp *= 0.5;
								}
								val += nv * fabs(val - 1.0) * 0.3;
							}
							// Blend Mode: 0=normal, 1=shrink-only, 2=grow-only, 3=abs, 4=smooth
							{
								int bm = fractal->transformCommon.multiplierBlendMode3;
								if (bm == 1 && val > 1.0) val = 1.0;
								else if (bm == 2 && val < 1.0) val = 1.0;
								else if (bm == 3) val = 1.0 + fabs(val - 1.0);
								else if (bm == 4) { double sv = fmin(fmax((val - 0.5) * 1.0, 0.0), 1.0); val = 0.5 + sv * sv * (3.0 - 2.0 * sv); }
							}

							// Clip Drive (pre-gain)
							if (fractal->transformCommon.multiplierClipDrive3 != 1.0)
							{
								double drv = fractal->transformCommon.multiplierClipDrive3;
								val = 1.0 + (val - 1.0) * drv;
							}
							// Clip Rectify: 0=off, 1=half(clamp neg to 0), 2=full(abs)
							{
								int cr = fractal->transformCommon.multiplierClipRectify3;
								if (cr == 1 && val < 1.0) val = 1.0;
								else if (cr == 2) val = 1.0 + fabs(val - 1.0);
							}
							// Clip Fold (wavefolder)
							if (fractal->transformCommon.multiplierClipFold3)
							{
								int folds = fractal->transformCommon.multiplierClipFoldCount3;
								if (folds < 1) folds = 1;
								double ceil = fractal->transformCommon.multiplierClipCeiling3;
								double flr = fractal->transformCommon.multiplierClipFloor3;
								for (int fi = 0; fi < folds; fi++)
								{
									if (val > ceil) val = 2.0 * ceil - val;
									if (val < flr) val = 2.0 * flr - val;
								}
							}
							// Clip Ceiling / Floor (hard clamp with asymmetry)
							if (!fractal->transformCommon.multiplierClipFold3)
							{
								double ceil = fractal->transformCommon.multiplierClipCeiling3;
								double flr = fractal->transformCommon.multiplierClipFloor3;
								double asym = fractal->transformCommon.multiplierClipAsymmetry3;
								ceil += asym;
								flr -= asym;
								// Clip Curve (soft knee)
								double curve = fractal->transformCommon.multiplierClipCurve3;
								double knee = fractal->transformCommon.multiplierClipKnee3;
								if (curve > 0.0 || knee > 0.0)
								{
									double k = fmax(knee, 0.001);
									if (val > ceil - k)
									{
										double x = (val - (ceil - k)) / (2.0 * k);
										x = fmin(fmax(x, 0.0), 1.0);
										double sm = x * x * (3.0 - 2.0 * x);
										val = (ceil - k) + k * sm * (1.0 + curve);
										if (val > ceil) val = ceil;
									}
									if (val < flr + k)
									{
										double x = ((flr + k) - val) / (2.0 * k);
										x = fmin(fmax(x, 0.0), 1.0);
										double sm = x * x * (3.0 - 2.0 * x);
										val = (flr + k) - k * sm * (1.0 + curve);
										if (val < flr) val = flr;
									}
								}
								else
								{
									if (val > ceil) val = ceil;
									if (val < flr) val = flr;
								}
							}
							// Clip Mix (blend clipped/unclipped)
							if (fractal->transformCommon.multiplierClipMix3 < 1.0)
							{
								double mx = fractal->transformCommon.multiplierClipMix3;
								// val is already clipped; recover original from drive
								// approximate: mix toward 1.0 (neutral)
								val = 1.0 + mx * (val - 1.0);
							}

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

							// Decay
							if (fractal->transformCommon.multiplierDecay4 > 0.0)
							{
								double dcy = fractal->transformCommon.multiplierDecay4;
								double rng = (double)(fractal->transformCommon.multiplierStopIter4 - fractal->transformCommon.multiplierStartIter4);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter4) / rng : 0.0;
								val = 1.0 + (val - 1.0) * exp(-dcy * td * 5.0);
							}
							// Exponent
							if (fractal->transformCommon.multiplierExponent4 != 1.0)
							{
								double ep = fractal->transformCommon.multiplierExponent4;
								double sgn = (val >= 1.0) ? 1.0 : -1.0;
								val = 1.0 + sgn * pow(fabs(val - 1.0) + 1e-30, ep);
							}
							// Offset
							val += fractal->transformCommon.multiplierOffset4;

							// Delay
							if (fractal->transformCommon.multiplierDelay4 > 0
								&& aux.i < fractal->transformCommon.multiplierStartIter4 + fractal->transformCommon.multiplierDelay4)
								val = 1.0;
							// Iteration Modulo
							if (fractal->transformCommon.multiplierIterModulo4 > 1
								&& ((aux.i - fractal->transformCommon.multiplierStartIter4) % fractal->transformCommon.multiplierIterModulo4) != 0)
								val = 1.0;
							// Attack envelope
							if (fractal->transformCommon.multiplierAttack4 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter4 - fractal->transformCommon.multiplierStartIter4);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter4) / rng : 1.0;
								double att = fractal->transformCommon.multiplierAttack4;
								if (td < att) val = 1.0 + (val - 1.0) * (td / att);
							}
							// Release envelope
							if (fractal->transformCommon.multiplierRelease4 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter4 - fractal->transformCommon.multiplierStartIter4);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter4) / rng : 1.0;
								double rel = fractal->transformCommon.multiplierRelease4;
								if (td > (1.0 - rel)) val = 1.0 + (val - 1.0) * ((1.0 - td) / rel);
							}
							// Feedback
							if (fractal->transformCommon.multiplierFeedback4 > 0.0)
							{
								double fb = fractal->transformCommon.multiplierFeedback4;
								val = 1.0 + (val - 1.0) * (1.0 - fb) + (prevMultVal - 1.0) * fb;
							}
							// Harmonics
							if (fractal->transformCommon.multiplierHarmonics4 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter4 - fractal->transformCommon.multiplierStartIter4);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter4) / rng : 0.0;
								double hrm = fractal->transformCommon.multiplierHarmonics4;
								double frq = fractal->transformCommon.multiplierFrequency4;
								val += hrm * sin(4.0 * M_PI * frq * td) * fabs(val - 1.0);
							}
							// Pulse Width
							if (fractal->transformCommon.multiplierPulseWidth4 != 0.5)
							{
								double pw = fractal->transformCommon.multiplierPulseWidth4;
								double diff = val - 1.0;
								double sgn = (diff >= 0.0) ? 1.0 : -1.0;
								double mg = fabs(diff) + 1e-30;
								val = 1.0 + sgn * pow(mg, 1.0 / (2.0 * fmax(pw, 0.01)));
							}
							// Mirror
							if (fractal->transformCommon.multiplierMirror4 && val < 1.0)
								val = 2.0 - val;
							// Quantize
							if (fractal->transformCommon.multiplierQuantize4 > 0)
							{
								double step = 1.0 / (double)fractal->transformCommon.multiplierQuantize4;
								val = 1.0 + floor((val - 1.0) / step + 0.5) * step;
							}
							// Symmetry Break
							if (fractal->transformCommon.multiplierSymmetryBreak4 != 0.0)
							{
								double sb = fractal->transformCommon.multiplierSymmetryBreak4;
								double diff = val - 1.0;
								val = (diff > 0.0) ? 1.0 + diff * (1.0 + sb) : 1.0 + diff * (1.0 - sb);
							}
							// Clamp
							if (val < fractal->transformCommon.multiplierClampMin4) val = fractal->transformCommon.multiplierClampMin4;
							if (val > fractal->transformCommon.multiplierClampMax4) val = fractal->transformCommon.multiplierClampMax4;
							// Soft Clip
							if (fractal->transformCommon.multiplierSoftClip4 > 0.0)
							{
								double sc = fractal->transformCommon.multiplierSoftClip4;
								double diff = val - 1.0;
								val = 1.0 + diff / (1.0 + sc * fabs(diff));
							}
							// Radial Falloff
							if (fractal->transformCommon.multiplierRadialFalloff4 > 0.0)
							{
								double rf = fractal->transformCommon.multiplierRadialFalloff4;
								double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0 + (val - 1.0) * exp(-rf * r);
							}
							// Angular Bias
							if (fractal->transformCommon.multiplierAngularBias4 != 0.0)
							{
								double ab = fractal->transformCommon.multiplierAngularBias4;
								double angle = atan2(z.y, z.x);
								double bias = 0.5 + 0.5 * cos(angle - ab * M_PI / 180.0);
								val = 1.0 + (val - 1.0) * bias;
							}
							// Polar Mode
							if (fractal->transformCommon.multiplierPolarMode4)
							{
								double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0 + (val - 1.0) * (1.0 + 0.5 * sin(r));
							}
							// Cross-axis Coupling
							if (fractal->transformCommon.multiplierCrossCoupling4 > 0.0)
							{
								double cc = fractal->transformCommon.multiplierCrossCoupling4;
								double leak = (val - 1.0) * cc * 0.1;
								z.x += leak * z.y;
								z.y += leak * z.z;
								z.z += leak * z.x;
							}
							// Noise addition
							if (fractal->transformCommon.multiplierNoiseSeed4 > 0)
							{
								int seed = fractal->transformCommon.multiplierNoiseSeed4;
								int oct = fractal->transformCommon.multiplierNoiseOctaves4;
								double nv = 0.0;
								double amp = 1.0;
								for (int o = 0; o < oct; o++)
								{
									double ph = (double)(aux.i * 1237 + seed * 7919 + o * 4621);
									nv += amp * sin(ph * 0.0031415);
									amp *= 0.5;
								}
								val += nv * fabs(val - 1.0) * 0.3;
							}
							// Blend Mode: 0=normal, 1=shrink-only, 2=grow-only, 3=abs, 4=smooth
							{
								int bm = fractal->transformCommon.multiplierBlendMode4;
								if (bm == 1 && val > 1.0) val = 1.0;
								else if (bm == 2 && val < 1.0) val = 1.0;
								else if (bm == 3) val = 1.0 + fabs(val - 1.0);
								else if (bm == 4) { double sv = fmin(fmax((val - 0.5) * 1.0, 0.0), 1.0); val = 0.5 + sv * sv * (3.0 - 2.0 * sv); }
							}

							// Clip Drive (pre-gain)
							if (fractal->transformCommon.multiplierClipDrive4 != 1.0)
							{
								double drv = fractal->transformCommon.multiplierClipDrive4;
								val = 1.0 + (val - 1.0) * drv;
							}
							// Clip Rectify: 0=off, 1=half(clamp neg to 0), 2=full(abs)
							{
								int cr = fractal->transformCommon.multiplierClipRectify4;
								if (cr == 1 && val < 1.0) val = 1.0;
								else if (cr == 2) val = 1.0 + fabs(val - 1.0);
							}
							// Clip Fold (wavefolder)
							if (fractal->transformCommon.multiplierClipFold4)
							{
								int folds = fractal->transformCommon.multiplierClipFoldCount4;
								if (folds < 1) folds = 1;
								double ceil = fractal->transformCommon.multiplierClipCeiling4;
								double flr = fractal->transformCommon.multiplierClipFloor4;
								for (int fi = 0; fi < folds; fi++)
								{
									if (val > ceil) val = 2.0 * ceil - val;
									if (val < flr) val = 2.0 * flr - val;
								}
							}
							// Clip Ceiling / Floor (hard clamp with asymmetry)
							if (!fractal->transformCommon.multiplierClipFold4)
							{
								double ceil = fractal->transformCommon.multiplierClipCeiling4;
								double flr = fractal->transformCommon.multiplierClipFloor4;
								double asym = fractal->transformCommon.multiplierClipAsymmetry4;
								ceil += asym;
								flr -= asym;
								// Clip Curve (soft knee)
								double curve = fractal->transformCommon.multiplierClipCurve4;
								double knee = fractal->transformCommon.multiplierClipKnee4;
								if (curve > 0.0 || knee > 0.0)
								{
									double k = fmax(knee, 0.001);
									if (val > ceil - k)
									{
										double x = (val - (ceil - k)) / (2.0 * k);
										x = fmin(fmax(x, 0.0), 1.0);
										double sm = x * x * (3.0 - 2.0 * x);
										val = (ceil - k) + k * sm * (1.0 + curve);
										if (val > ceil) val = ceil;
									}
									if (val < flr + k)
									{
										double x = ((flr + k) - val) / (2.0 * k);
										x = fmin(fmax(x, 0.0), 1.0);
										double sm = x * x * (3.0 - 2.0 * x);
										val = (flr + k) - k * sm * (1.0 + curve);
										if (val < flr) val = flr;
									}
								}
								else
								{
									if (val > ceil) val = ceil;
									if (val < flr) val = flr;
								}
							}
							// Clip Mix (blend clipped/unclipped)
							if (fractal->transformCommon.multiplierClipMix4 < 1.0)
							{
								double mx = fractal->transformCommon.multiplierClipMix4;
								// val is already clipped; recover original from drive
								// approximate: mix toward 1.0 (neutral)
								val = 1.0 + mx * (val - 1.0);
							}

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

							// Decay
							if (fractal->transformCommon.multiplierDecay5 > 0.0)
							{
								double dcy = fractal->transformCommon.multiplierDecay5;
								double rng = (double)(fractal->transformCommon.multiplierStopIter5 - fractal->transformCommon.multiplierStartIter5);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter5) / rng : 0.0;
								val = 1.0 + (val - 1.0) * exp(-dcy * td * 5.0);
							}
							// Exponent
							if (fractal->transformCommon.multiplierExponent5 != 1.0)
							{
								double ep = fractal->transformCommon.multiplierExponent5;
								double sgn = (val >= 1.0) ? 1.0 : -1.0;
								val = 1.0 + sgn * pow(fabs(val - 1.0) + 1e-30, ep);
							}
							// Offset
							val += fractal->transformCommon.multiplierOffset5;

							// Delay
							if (fractal->transformCommon.multiplierDelay5 > 0
								&& aux.i < fractal->transformCommon.multiplierStartIter5 + fractal->transformCommon.multiplierDelay5)
								val = 1.0;
							// Iteration Modulo
							if (fractal->transformCommon.multiplierIterModulo5 > 1
								&& ((aux.i - fractal->transformCommon.multiplierStartIter5) % fractal->transformCommon.multiplierIterModulo5) != 0)
								val = 1.0;
							// Attack envelope
							if (fractal->transformCommon.multiplierAttack5 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter5 - fractal->transformCommon.multiplierStartIter5);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter5) / rng : 1.0;
								double att = fractal->transformCommon.multiplierAttack5;
								if (td < att) val = 1.0 + (val - 1.0) * (td / att);
							}
							// Release envelope
							if (fractal->transformCommon.multiplierRelease5 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter5 - fractal->transformCommon.multiplierStartIter5);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter5) / rng : 1.0;
								double rel = fractal->transformCommon.multiplierRelease5;
								if (td > (1.0 - rel)) val = 1.0 + (val - 1.0) * ((1.0 - td) / rel);
							}
							// Feedback
							if (fractal->transformCommon.multiplierFeedback5 > 0.0)
							{
								double fb = fractal->transformCommon.multiplierFeedback5;
								val = 1.0 + (val - 1.0) * (1.0 - fb) + (prevMultVal - 1.0) * fb;
							}
							// Harmonics
							if (fractal->transformCommon.multiplierHarmonics5 > 0.0)
							{
								double rng = (double)(fractal->transformCommon.multiplierStopIter5 - fractal->transformCommon.multiplierStartIter5);
								double td = (rng > 0.0) ? (double)(aux.i - fractal->transformCommon.multiplierStartIter5) / rng : 0.0;
								double hrm = fractal->transformCommon.multiplierHarmonics5;
								double frq = fractal->transformCommon.multiplierFrequency5;
								val += hrm * sin(4.0 * M_PI * frq * td) * fabs(val - 1.0);
							}
							// Pulse Width
							if (fractal->transformCommon.multiplierPulseWidth5 != 0.5)
							{
								double pw = fractal->transformCommon.multiplierPulseWidth5;
								double diff = val - 1.0;
								double sgn = (diff >= 0.0) ? 1.0 : -1.0;
								double mg = fabs(diff) + 1e-30;
								val = 1.0 + sgn * pow(mg, 1.0 / (2.0 * fmax(pw, 0.01)));
							}
							// Mirror
							if (fractal->transformCommon.multiplierMirror5 && val < 1.0)
								val = 2.0 - val;
							// Quantize
							if (fractal->transformCommon.multiplierQuantize5 > 0)
							{
								double step = 1.0 / (double)fractal->transformCommon.multiplierQuantize5;
								val = 1.0 + floor((val - 1.0) / step + 0.5) * step;
							}
							// Symmetry Break
							if (fractal->transformCommon.multiplierSymmetryBreak5 != 0.0)
							{
								double sb = fractal->transformCommon.multiplierSymmetryBreak5;
								double diff = val - 1.0;
								val = (diff > 0.0) ? 1.0 + diff * (1.0 + sb) : 1.0 + diff * (1.0 - sb);
							}
							// Clamp
							if (val < fractal->transformCommon.multiplierClampMin5) val = fractal->transformCommon.multiplierClampMin5;
							if (val > fractal->transformCommon.multiplierClampMax5) val = fractal->transformCommon.multiplierClampMax5;
							// Soft Clip
							if (fractal->transformCommon.multiplierSoftClip5 > 0.0)
							{
								double sc = fractal->transformCommon.multiplierSoftClip5;
								double diff = val - 1.0;
								val = 1.0 + diff / (1.0 + sc * fabs(diff));
							}
							// Radial Falloff
							if (fractal->transformCommon.multiplierRadialFalloff5 > 0.0)
							{
								double rf = fractal->transformCommon.multiplierRadialFalloff5;
								double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0 + (val - 1.0) * exp(-rf * r);
							}
							// Angular Bias
							if (fractal->transformCommon.multiplierAngularBias5 != 0.0)
							{
								double ab = fractal->transformCommon.multiplierAngularBias5;
								double angle = atan2(z.y, z.x);
								double bias = 0.5 + 0.5 * cos(angle - ab * M_PI / 180.0);
								val = 1.0 + (val - 1.0) * bias;
							}
							// Polar Mode
							if (fractal->transformCommon.multiplierPolarMode5)
							{
								double r = sqrt(z.x * z.x + z.y * z.y + z.z * z.z);
								val = 1.0 + (val - 1.0) * (1.0 + 0.5 * sin(r));
							}
							// Cross-axis Coupling
							if (fractal->transformCommon.multiplierCrossCoupling5 > 0.0)
							{
								double cc = fractal->transformCommon.multiplierCrossCoupling5;
								double leak = (val - 1.0) * cc * 0.1;
								z.x += leak * z.y;
								z.y += leak * z.z;
								z.z += leak * z.x;
							}
							// Noise addition
							if (fractal->transformCommon.multiplierNoiseSeed5 > 0)
							{
								int seed = fractal->transformCommon.multiplierNoiseSeed5;
								int oct = fractal->transformCommon.multiplierNoiseOctaves5;
								double nv = 0.0;
								double amp = 1.0;
								for (int o = 0; o < oct; o++)
								{
									double ph = (double)(aux.i * 1237 + seed * 7919 + o * 4621);
									nv += amp * sin(ph * 0.0031415);
									amp *= 0.5;
								}
								val += nv * fabs(val - 1.0) * 0.3;
							}
							// Blend Mode: 0=normal, 1=shrink-only, 2=grow-only, 3=abs, 4=smooth
							{
								int bm = fractal->transformCommon.multiplierBlendMode5;
								if (bm == 1 && val > 1.0) val = 1.0;
								else if (bm == 2 && val < 1.0) val = 1.0;
								else if (bm == 3) val = 1.0 + fabs(val - 1.0);
								else if (bm == 4) { double sv = fmin(fmax((val - 0.5) * 1.0, 0.0), 1.0); val = 0.5 + sv * sv * (3.0 - 2.0 * sv); }
							}

							// Clip Drive (pre-gain)
							if (fractal->transformCommon.multiplierClipDrive5 != 1.0)
							{
								double drv = fractal->transformCommon.multiplierClipDrive5;
								val = 1.0 + (val - 1.0) * drv;
							}
							// Clip Rectify: 0=off, 1=half(clamp neg to 0), 2=full(abs)
							{
								int cr = fractal->transformCommon.multiplierClipRectify5;
								if (cr == 1 && val < 1.0) val = 1.0;
								else if (cr == 2) val = 1.0 + fabs(val - 1.0);
							}
							// Clip Fold (wavefolder)
							if (fractal->transformCommon.multiplierClipFold5)
							{
								int folds = fractal->transformCommon.multiplierClipFoldCount5;
								if (folds < 1) folds = 1;
								double ceil = fractal->transformCommon.multiplierClipCeiling5;
								double flr = fractal->transformCommon.multiplierClipFloor5;
								for (int fi = 0; fi < folds; fi++)
								{
									if (val > ceil) val = 2.0 * ceil - val;
									if (val < flr) val = 2.0 * flr - val;
								}
							}
							// Clip Ceiling / Floor (hard clamp with asymmetry)
							if (!fractal->transformCommon.multiplierClipFold5)
							{
								double ceil = fractal->transformCommon.multiplierClipCeiling5;
								double flr = fractal->transformCommon.multiplierClipFloor5;
								double asym = fractal->transformCommon.multiplierClipAsymmetry5;
								ceil += asym;
								flr -= asym;
								// Clip Curve (soft knee)
								double curve = fractal->transformCommon.multiplierClipCurve5;
								double knee = fractal->transformCommon.multiplierClipKnee5;
								if (curve > 0.0 || knee > 0.0)
								{
									double k = fmax(knee, 0.001);
									if (val > ceil - k)
									{
										double x = (val - (ceil - k)) / (2.0 * k);
										x = fmin(fmax(x, 0.0), 1.0);
										double sm = x * x * (3.0 - 2.0 * x);
										val = (ceil - k) + k * sm * (1.0 + curve);
										if (val > ceil) val = ceil;
									}
									if (val < flr + k)
									{
										double x = ((flr + k) - val) / (2.0 * k);
										x = fmin(fmax(x, 0.0), 1.0);
										double sm = x * x * (3.0 - 2.0 * x);
										val = (flr + k) - k * sm * (1.0 + curve);
										if (val < flr) val = flr;
									}
								}
								else
								{
									if (val > ceil) val = ceil;
									if (val < flr) val = flr;
								}
							}
							// Clip Mix (blend clipped/unclipped)
							if (fractal->transformCommon.multiplierClipMix5 < 1.0)
							{
								double mx = fractal->transformCommon.multiplierClipMix5;
								// val is already clipped; recover original from drive
								// approximate: mix toward 1.0 (neutral)
								val = 1.0 + mx * (val - 1.0);
							}

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
