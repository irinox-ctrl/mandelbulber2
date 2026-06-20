/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2017-24 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
 *                                        ,=mm=§M ]=4 yJKA"/-Nsaj  "Bw,==,,
 * This file is part of Mandelbulber.    §R.r= jw",M  Km .mM  FW ",§=ß., ,TN
 *                                     ,4R =%["w[N=7]J '"5=],""]]M,w,-; T=]M
 * Mandelbulber is free software:     §R.ß~-Q/M=,=5"v"]=Qf,'§"M= =,M.§ Rz]M"Kw
 * you can redistribute it and/or     §w "xDY.J ' -"m=====WeC=\ ""%""y=%"]"" §
 * modify it under the terms of the    "§M=M =D=4"N #"%==A%p M§ M6  R' #"=~.4M
 * GNU General Public License as        §W =, ][T"]C  §  § '§ e===~ U  !§[Z ]N
 * published by the                    4M",,Jm=,"=e~  §  §  j]]""N  BmM"py=ßM
 * Free Software Foundation,          ]§ T,M=& 'YmMMpM9MMM%=w=,,=MT]M m§;'§,
 * either version 3 of the License,    TWw [.j"5=~N[=§%=%W,T ]R,"=="Y[LFT ]N
 * or (at your option)                   TW=,-#"%=;[  =Q:["V""  ],,M.m == ]N
 * any later version.                      J§"mr"] ,=,," =="""J]= M"M"]==ß"
 *                                          §= "=C=4 §"eM "=B:m|4"]#F,§~
 * Mandelbulber is distributed in            "9w=,,]w em%wJ '"~" ,=,,ß"
 * the hope that it will be useful,                 . "K=  ,=RMMMßM"""
 * but WITHOUT ANY WARRANTY;                            .'''
 * without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with Mandelbulber. If not, see <http://www.gnu.org/licenses/>.
 *
 * ###########################################################################
 *
 * Authors: Krzysztof Marczak (buddhi1980@gmail.com)
 *
 * distance calculation function for opencl
 */

#ifndef MANDELBULBER2_OPENCL_ENGINES_CALCULATE_DISTANCE_CL_
#define MANDELBULBER2_OPENCL_ENGINES_CALCULATE_DISTANCE_CL_

// calculation of distance where ray-marching stops
float CalcDistThresh(float3 point, __constant sClInConstants *consts)
{
	float distThresh;
	if (consts->params.common.iterThreshMode)
	{
		distThresh =
			length(consts->params.camera - point) * consts->params.resolution * consts->params.fov;
	}
	else
	{
		if (consts->params.constantDEThreshold)
			distThresh = consts->params.DEThresh;
		else
			distThresh = length(consts->params.camera - point) * consts->params.resolution
									 * consts->params.fov / consts->params.detailLevel;
	}

#if defined(PERSP_EQUIRECTANGULAR)
	distThresh *= 0.5f;
#endif

#ifdef ADVANCED_QUALITY
	distThresh = clamp(distThresh, consts->params.detailSizeMin, consts->params.detailSizeMax);
#else
	distThresh = max(distThresh, 1e-6f);
#endif

	return distThresh;
}

// calculation of "voxel" size
float CalcDelta(float3 point, __constant sClInConstants *consts)
{
	float delta;
	delta = length(consts->params.camera - point) * consts->params.resolution * consts->params.fov;

#if defined(PERSP_EQUIRECTANGULAR)
	delta *= 0.5f;
#endif

	delta = max(delta, 1e-6f);
	return delta;
}

#ifdef BOOLEAN_OPERATORS
formulaOut CalculateDistanceSimple(__constant sClInConstants *consts, float3 point,
	sClCalcParams *calcParam, sRenderData *renderData, int forcedFormulaIndex)
#else
formulaOut CalculateDistance(__constant sClInConstants *consts, float3 point,
	sClCalcParams *calcParam, sRenderData *renderData)
#endif
{
	formulaOut out;
	out.z = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
	out.iters = 0;
	out.distance = 0.0f;
	out.colorIndex = 0.0f;
	out.orbitTrapR = 0.0f;
	out.pseudoKleinianDE = 1.0f;
	out.finalDE = 1.0f;
	out.orbitTrapCenterIndex = 0;
	out.maxiter = false;
	out.objectId = 0;

#ifdef DEEP_ZOOM_ENABLED
	// Deep Zoom perturbation path: use reference orbit + delta iteration (fp64)
	if (renderData->deepZoomOrbitLength > 0)
	{
		__global const double *orbit = renderData->deepZoomOrbit;
		int orbitLen = renderData->deepZoomOrbitLength;
		double power = (double)renderData->deepZoomPower;
		double bailout = (double)renderData->deepZoomBailout;

		double3 center = (double3)(
			renderData->deepZoomCenterX,
			renderData->deepZoomCenterY,
			renderData->deepZoomCenterZ);
		double3 deltaC = convert_double3(point) - center;
		double3 deltaZ = (double3)(0.0, 0.0, 0.0);
		double deltaDE = 0.0;

		int startIter = 0;
		// Apply Series Approximation skip if valid
		if (renderData->deepZoomSAValid && renderData->deepZoomSASkipIters > 0)
		{
			__global const double *sa = renderData->deepZoomSAMatrix;
			// δz₀ = A · δc (matrix-vector multiply)
			deltaZ.x = sa[0] * deltaC.x + sa[1] * deltaC.y + sa[2] * deltaC.z;
			deltaZ.y = sa[3] * deltaC.x + sa[4] * deltaC.y + sa[5] * deltaC.z;
			deltaZ.z = sa[6] * deltaC.x + sa[7] * deltaC.y + sa[8] * deltaC.z;
			startIter = renderData->deepZoomSASkipIters;
		}

		int iters = 0;
		bool escaped = false;
		double lastR = 0.0;
		for (int i = startIter; i < orbitLen && i < (int)calcParam->N; i++)
		{
			// Read reference orbit point: [Z.x, Z.y, Z.z, DE, r, theta, phi, escaped]
			int base = i * 8;
			double3 refZ = (double3)(orbit[base], orbit[base + 1], orbit[base + 2]);
			double refDE = orbit[base + 3];
			double refR = orbit[base + 4];
			double refTheta = orbit[base + 5];
			double refPhi = orbit[base + 6];

			// Full point: Z + δz
			double3 Zfull = refZ + deltaZ;
			double rFull = length(Zfull);

			if (rFull > bailout)
			{
				escaped = true;
				iters = i;
				lastR = rFull;
				break;
			}

			if (rFull < 1e-150)
			{
				deltaZ = deltaC;
				deltaDE = 1.0;
				iters = i + 1;
				continue;
			}

			// f(Z + δz) in spherical coordinates
			double clampVal = Zfull.z / rFull;
			clampVal = clampVal < -1.0 ? -1.0 : (clampVal > 1.0 ? 1.0 : clampVal);
			double thetaFull = asin(clampVal);
			double phiFull = atan2(Zfull.y, Zfull.x);
			double rpFull = pow(rFull, power);
			double rp1Full = pow(rFull, power - 1.0);

			double pTh = power * thetaFull;
			double pPh = power * phiFull;
			double3 fFull = (double3)(
				rpFull * cos(pTh) * cos(pPh),
				rpFull * cos(pTh) * sin(pPh),
				rpFull * sin(pTh));

			// f(Z) from reference
			double rpRef = pow(refR, power);
			double pThRef = power * refTheta;
			double pPhRef = power * refPhi;
			double3 fRef = (double3)(
				rpRef * cos(pThRef) * cos(pPhRef),
				rpRef * cos(pThRef) * sin(pPhRef),
				rpRef * sin(pThRef));

			// δz_{n+1} = f(Z + δz) - f(Z) + δc
			deltaZ = fFull - fRef + deltaC;

			// DE perturbation
			double deFull = refDE + deltaDE;
			double newDEFull = power * rp1Full * deFull + 1.0;
			double newDERef = power * pow(refR, power - 1.0) * refDE + 1.0;
			deltaDE = newDEFull - newDERef;

			iters = i + 1;
			lastR = rFull;

			// Rebasing: if |δz| grows too large relative to |Z|
			double dzLen = length(deltaZ);
			if (refR > 1e-30 && dzLen / refR > 1000.0)
			{
				break;
			}
		}

		// Compute distance estimate
		double3 lastRefZ = (double3)(
			orbit[(iters > 0 ? iters - 1 : 0) * 8],
			orbit[(iters > 0 ? iters - 1 : 0) * 8 + 1],
			orbit[(iters > 0 ? iters - 1 : 0) * 8 + 2]);
		double lastRefDE = orbit[(iters > 0 ? iters - 1 : 0) * 8 + 3];

		double3 finalZ = lastRefZ + deltaZ;
		double finalR = length(finalZ);
		double finalDE = fabs(lastRefDE + deltaDE);

		double distance;
		if (escaped && finalDE > 0.0)
		{
			distance = 0.5 * finalR * log(finalR) / finalDE;
		}
		else
		{
			distance = (double)calcParam->detailSize;
		}

		out.iters = iters;
		out.maxiter = (!escaped && iters >= (int)calcParam->N);
		out.colorIndex = (float)iters;
		out.z = (float4)((float)finalZ.x, (float)finalZ.y, (float)finalZ.z, 0.0f);

		if (isinf(distance)) distance = 0.0;
		if (distance < 0.0) distance = 0.0;
		if (distance > 5.0) distance = 5.0;
		out.distance = (float)distance;

		return out;
	}
#endif // DEEP_ZOOM_ENABLED

#ifndef BOOLEAN_OPERATORS
	float limitBoxDist = 0.0f;
	int forcedFormulaIndex = -1;

#ifdef LIMITS_ENABLED
	float3 boxDistance = max(point - consts->params.limitMax, -(point - consts->params.limitMin));
	limitBoxDist = max(max(boxDistance.x, boxDistance.y), boxDistance.z);

	if (limitBoxDist > calcParam->detailSize)
	{
		out.maxiter = false;
		out.distance = limitBoxDist;
		out.iters = 0;
		return out;
	}
#endif
#endif // BOOLEAN_OPERATORS

	int forcedFormulaIndexForSequence = max(0, forcedFormulaIndex);

#ifdef ANALYTIC_DE
#ifdef BOOLEAN_OPERATORS
	if (consts->sequence.DEType[forcedFormulaIndexForSequence] == analyticDEType)
#endif
	{
		out = Fractal(consts, point, calcParam, calcModeNormal, NULL, forcedFormulaIndex);
		bool maxiter = out.maxiter;

		// don't use maxiter when limits are disabled and iterThresh mode is not used
		if (!consts->params.iterThreshMode) maxiter = false;

		// never use maxiter if normal vectors are calculated
		if (calcParam->normalCalculationMode) maxiter = false;

		if (maxiter) out.distance = 0.0f;

		if (out.iters < consts->params.minN && out.distance < calcParam->detailSize)
			out.distance = calcParam->detailSize;

#ifdef INTERIOR_MODE
		if (!calcParam->normalCalculationMode)
		{
			if (out.distance < 0.5f * calcParam->detailSize || maxiter)
			{
				out.distance = calcParam->detailSize;
				out.maxiter = false;
			}
		}
		else
		{
			if (out.distance < 0.9f * calcParam->detailSize)
			{
				out.distance = calcParam->detailSize - out.distance;
				out.maxiter = false;
			}
		}
#endif

		if (consts->params.common.iterThreshMode && !calcParam->normalCalculationMode && !maxiter)
		{
			if (out.distance < calcParam->detailSize)
			{
				out.distance = calcParam->detailSize * 1.01f;
			}
		}

		if (isinf(out.distance)) out.distance = 0.0f;
		if (out.distance < 0.0f) out.distance = 0.0f;
		if (out.distance > 5.0f) out.distance = 5.0f;
	}
#endif // ANALYTIC_DE

#ifdef DELTA_DE
#ifdef BOOLEAN_OPERATORS
	if (consts->sequence.DEType[forcedFormulaIndexForSequence] == deltaDEType)
#endif
	{

#ifdef ADVANCED_QUALITY
		float delta =
			max(length(point) * 1.0e-6f, calcParam->detailSize * consts->params.deltaDERelativeDelta);
#else
		float delta = max(length(point) * 1.0e-6f, calcParam->detailSize * 0.1f);
#endif
		float3 dr = 0.0f;

		out = Fractal(consts, point, calcParam, calcModeDeltaDE1, NULL, forcedFormulaIndex);
		calcParam->deltaDEMaxN = out.iters - 1;
		float r = length(out.z);
		float4 zFromIters = out.z;

		bool maxiter = out.maxiter;

		// don't use maxiter when iterThresh mode is not used
		if (!consts->params.iterThreshMode) maxiter = false;

		// never use maxiter if normal vectors are calculated
		if (calcParam->normalCalculationMode) maxiter = false;

		float3 deltas[6];
		deltas[0] = (float3){delta, 0.0f, 0.0f};
		deltas[1] = (float3){-delta, 0.0f, 0.0f};
		deltas[2] = (float3){0.0f, delta, 0.0f};
		deltas[3] = (float3){0.0f, -delta, 0.0f};
		deltas[4] = (float3){0.0f, 0.0f, delta};
		deltas[5] = (float3){0.0f, 0.0f, -delta};

		float rDelta[6];
		for (int i = 0; i < 6; i++)
		{
			rDelta[i] = length(
				Fractal(consts, point + deltas[i], calcParam, calcModeDeltaDE2, NULL, forcedFormulaIndex)
					.z);
		}
		dr.x = min(fabs(rDelta[0] - r), fabs(rDelta[1] - r)) / delta;
		dr.y = min(fabs(rDelta[2] - r), fabs(rDelta[3] - r)) / delta;
		dr.z = min(fabs(rDelta[4] - r), fabs(rDelta[5] - r)) / delta;

		float d = length(dr);

		if (isinf(r) || isinf(d) || d == 0.0f)
		{
			out.distance = 0.0f;
		}
		else
		{
#ifdef DELTA_LINEAR_DE
			out.distance = 0.5f * r / d;
#elif DELTA_LOG_DE
			out.distance = 0.5f * r * native_log(r) / d;
#elif DELTA_PSEUDO_KLEINIAN_DE
			float rxy = native_sqrt(out.z.x * out.z.x + out.z.y * out.z.y);
			out.distance = max(rxy - out.pseudoKleinianDE, fabs(rxy * out.z.z) / r) / d;
#elif DELTA_JOS_KLEINIAN_DE
			float4 z = out.z;
			float rxy = native_sqrt(z.x * z.x + z.z * z.z);
			out.distance = (fabs(rxy * z.y) / r) / d;
			out.maxiter = false;
#elif DELTA_MAXAXIS_DE
			float4 absZ = fabs(zFromIters);
			float maxZ = max(max(absZ.x, absZ.y), absZ.z);
			float maxDr = max(max(fabs(dr.x), fabs(dr.y)), fabs(dr.z));
			out.distance = 0.5f * maxZ / maxDr;
#endif
		}

		// don't use maxiter when limits are disabled and iterThresh mode is not used
		if (!consts->params.iterThreshMode) maxiter = false;

		// never use maxiter if normal vectors are calculated
		if (calcParam->normalCalculationMode) maxiter = false;

		if (maxiter) out.distance = 0.0f;

		if (out.iters < consts->params.minN && out.distance < calcParam->detailSize)
			out.distance = calcParam->detailSize;

#ifdef INTERIOR_MODE
		if (!calcParam->normalCalculationMode)
		{
			if (out.distance < 0.5f * calcParam->detailSize || maxiter)
			{
				out.distance = calcParam->detailSize;
				out.maxiter = false;
			}
		}
		else
		{
			if (out.distance < 0.9f * calcParam->detailSize)
			{
				out.distance = calcParam->detailSize - out.distance;
				out.maxiter = false;
			}
		}
#endif

		if (consts->params.common.iterThreshMode && !calcParam->normalCalculationMode && !maxiter)
		{
			if (out.distance < calcParam->detailSize)
			{
				out.distance = calcParam->detailSize * 1.01f;
			}
		}

		if (out.distance < 0.0f) out.distance = 0.0f;
		if (out.distance > 5.0f) out.distance = 5.0f;
	}
#endif // DELTA_DE

	int closestObjectId = 0;

#ifndef BOOLEAN_OPERATORS

	float3 pointFractalized = point;
	float reduceDisplacement = 1.0f;

#ifdef FRACTALIZE_TEXTURE
	pointFractalized =
		FractalizeTexture(point, consts, calcParam, renderData, closestObjectId, &reduceDisplacement);
#endif // FRACTALIZE_TEXTURE

#ifdef USE_DISPLACEMENT_TEXTURE
	out.distance =
		DisplacementMap(out.distance, pointFractalized, out.objectId, renderData, reduceDisplacement);
#endif // USE_DISPLACEMENT_TEXTURE

#if defined(USE_PERLIN_NOISE) && defined(USE_PERLIN_NOISE_DISPLACEMENT)
	out.distance = PerlinNoiseDisplacement(out.distance, pointFractalized, renderData, out.objectId);
#endif // USE_PERLIN_NOISE

#ifdef USE_PRIMITIVES
	out.distance = TotalDistanceToPrimitives(consts, renderData, point, out.distance,
		calcParam->detailSize, calcParam->normalCalculationMode, &closestObjectId, -1);
	out.objectId = closestObjectId;
#endif

#ifdef LIMITS_ENABLED
	if (limitBoxDist < calcParam->detailSize)
	{
		out.distance = max(out.distance, limitBoxDist);
	}
#endif

	float distFromCamera = length(point - consts->params.camera);
	float distanceLimitMin = consts->params.viewDistanceMin - distFromCamera;
	out.distance = max(out.distance, distanceLimitMin);

	if (distanceLimitMin > calcParam->detailSize)
	{
		out.maxiter = false;
		out.iters = 0;
	}
#endif // BOOLEAN_OPERATORS

	return out;
}

//------------------------- Calculate distance for Booleans -------------------

#ifdef BOOLEAN_OPERATORS
formulaOut CalculateDistance(__constant sClInConstants *consts, float3 point,
	sClCalcParams *calcParam, sRenderData *renderData)
{
	formulaOut out;
	out.z = (float4)(0.0f, 0.0f, 0.0f, 0.0f);
	out.iters = 0;
	out.distance = 0.0f;
	out.colorIndex = 0.0f;
	out.orbitTrapR = 0.0f;
	out.orbitTrapCenterIndex = 0;
	out.maxiter = false;
	out.objectId = 0;

	float limitBoxDist = 0.0f;
	float dist = 0.0f;

#ifdef LIMITS_ENABLED
	float3 boxDistance = max(point - consts->params.limitMax, -(point - consts->params.limitMin));
	limitBoxDist = max(max(boxDistance.x, boxDistance.y), boxDistance.z);

	if (limitBoxDist > calcParam->detailSize)
	{
		out.maxiter = false;
		out.distance = limitBoxDist;
		out.iters = 0;
		return out;
	}
#endif

	{
		float3 pointTemp = point - consts->params.formulaPosition[0];
		pointTemp = Matrix33MulFloat3(consts->params.mRotFormulaRotation[0], pointTemp);
		pointTemp = modRepeat(pointTemp, consts->params.formulaRepeat[0]);
		pointTemp *= consts->params.formulaScale[0];

		out = CalculateDistanceSimple(consts, pointTemp, calcParam, renderData, 0);
		dist = out.distance / consts->params.formulaScale[0];
		out.objectId = 0;

		float3 pointFractalized = pointTemp;
		float reduceDisplacement = 1.0f;

#ifdef FRACTALIZE_TEXTURE
		pointFractalized =
			FractalizeTexture(pointTemp, consts, calcParam, renderData, 0, &reduceDisplacement);
#endif // FRACTALIZE_TEXTURE

#ifdef USE_DISPLACEMENT_TEXTURE
		dist = DisplacementMap(dist, pointFractalized, out.objectId, renderData, reduceDisplacement);
#endif // USE_DISPLACEMENT_TEXTURE

#if defined(USE_PERLIN_NOISE) && defined(USE_PERLIN_NOISE_DISPLACEMENT)
		dist = PerlinNoiseDisplacement(dist, pointFractalized, renderData, out.objectId);
#endif // USE_PERLIN_NOISE
	}

	for (int i = 0; i < NUMBER_OF_FRACTALS - 1; i++)
	{
		if (consts->fractal[i + 1].formula != 0) // != fractal::none
		{
			float3 pointTemp = point - consts->params.formulaPosition[i + 1];
			pointTemp = Matrix33MulFloat3(consts->params.mRotFormulaRotation[i + 1], pointTemp);
			pointTemp = modRepeat(pointTemp, consts->params.formulaRepeat[i + 1]);
			pointTemp *= consts->params.formulaScale[i + 1];

			formulaOut outTemp;

			outTemp = CalculateDistanceSimple(consts, pointTemp, calcParam, renderData, i + 1);
			float distTemp = outTemp.distance / consts->params.formulaScale[i + 1];

			float3 pointFractalized = pointTemp;
			float reduceDisplacement = 1.0f;

#ifdef FRACTALIZE_TEXTURE
			pointFractalized =
				FractalizeTexture(pointTemp, consts, calcParam, renderData, i + 1, &reduceDisplacement);
#endif // FRACTALIZE_TEXTURE

#ifdef USE_DISPLACEMENT_TEXTURE
			distTemp = DisplacementMap(distTemp, pointFractalized, i + 1, renderData, reduceDisplacement);
#endif

#if defined(USE_PERLIN_NOISE) && defined(USE_PERLIN_NOISE_DISPLACEMENT)
			distTemp = PerlinNoiseDisplacement(distTemp, pointFractalized, renderData, i + 1);
#endif // USE_PERLIN_NOISE

			enumBooleanOperatorCl boolOperator = consts->params.booleanOperator[i];

			switch (boolOperator)
			{
				case booleanOperatorOR:
					if (distTemp < dist)
					{
						outTemp.objectId = 1 + i;
						out.z = outTemp.z;
						out.iters = outTemp.iters;
						out.distance = outTemp.distance;
						out.colorIndex = outTemp.colorIndex;
						out.orbitTrapR = outTemp.orbitTrapR;
						out.maxiter = outTemp.maxiter;
						out.objectId = outTemp.objectId;
					}
					if (consts->params.smoothDeCombineEnable[i + 1])
					{
						dist = opSmoothUnion(distTemp, dist, consts->params.smoothDeCombineDistance[i + 1]);
					}
					else
					{
						dist = min(distTemp, dist);
					}

					break;
				case booleanOperatorAND:
					if (distTemp > dist)
					{
						outTemp.objectId = 1 + i;
						out.z = outTemp.z;
						out.iters = outTemp.iters;
						out.distance = outTemp.distance;
						out.colorIndex = outTemp.colorIndex;
						out.orbitTrapR = outTemp.orbitTrapR;
						out.maxiter = outTemp.maxiter;
						out.objectId = outTemp.objectId;
					}
					dist = max(distTemp, dist);
					break;
				case booleanOperatorSUB:
				{
					float limit = 1.5f;
					if (dist < calcParam->detailSize) // if inside 1st
					{
						if (distTemp < calcParam->detailSize * limit * 1.5)
						{
							outTemp.objectId = 1 + i;
							out.z = outTemp.z;
							out.iters = outTemp.iters;
							out.distance = outTemp.distance;
							out.colorIndex = outTemp.colorIndex;
							out.orbitTrapR = outTemp.orbitTrapR;
							out.maxiter = outTemp.maxiter;
							out.objectId = outTemp.objectId;
						}

						if (distTemp < calcParam->detailSize * limit) // if inside 2nd
						{
							if (calcParam->normalCalculationMode)
							{
								dist = max(calcParam->detailSize * limit - distTemp, dist);
							}
							else
							{
								dist = calcParam->detailSize * limit;
							}
						}
						else // if outside of 2nd
						{
							dist = max(calcParam->detailSize * limit - distTemp, dist);
							if (dist < 0) dist = 0;
						}
					}
					break;
				}
				default: break;
			}
		}
	}

	// out = CalculateDistanceSimple(consts, point, calcParam, renderData);

	int closestObjectId = out.objectId;

#ifdef USE_PRIMITIVES
	dist = TotalDistanceToPrimitives(consts, renderData, point, dist, calcParam->detailSize,
		calcParam->normalCalculationMode, &closestObjectId, -1);
	out.objectId = closestObjectId;
#endif

	// Glow Sphere - add as solid object to ray-marching
	float glowSphereDist = GlowSphereDistanceGPU(consts, point);
	if (glowSphereDist < dist)
	{
		dist = glowSphereDist;
		out.objectId = -2;  // special ID for glow sphere
	}

#ifdef LIMITS_ENABLED
	if (limitBoxDist < calcParam->detailSize)
	{
		dist = max(dist, limitBoxDist);
	}
#endif

	float distFromCamera = length(point - consts->params.camera);
	float distanceLimitMin = consts->params.viewDistanceMin - distFromCamera;
	dist = max(dist, distanceLimitMin);

	if (distanceLimitMin > calcParam->detailSize)
	{
		out.maxiter = false;
		out.iters = 0;
	}

	out.distance = dist;

	return out;
}
#endif

#endif // MANDELBULBER2_OPENCL_ENGINES_CALCULATE_DISTANCE_CL_
