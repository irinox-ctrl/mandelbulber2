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
 * Fast kernel for rendering opencl with missing effects
 */

// defined to force recompilation of kernels on NVidia cards with new releases
#define MANDELBULBER_VERSION 2.35

int GetInteger(int byte, __global char *array)
{
	__global int *intPointer = (__global int *)&array[byte];
	return *intPointer;
}

//------------------ MAIN RENDER FUNCTION --------------------
kernel void fractal3D(__global sClPixel *out, __global char *inBuff,
	__constant sClInConstants *consts, image2d_t image2dBackground, __global uchar *perlinNoiseSeeds,
	int initRandomSeed)
{
	// get actual pixel
	const int imageX = get_global_id(0);
	const int imageY = get_global_id(1);
	const int cl_offsetX = get_global_offset(0);
	const int cl_offsetY = get_global_offset(1);
	const int buffIndex = (imageX - cl_offsetX) + (imageY - cl_offsetY) * get_global_size(0);

	// randomizing random seed
	int randomSeed = imageX + imageY * consts->params.imageWidth + initRandomSeed;
	for (int i = 0; i < 3; i++)
	{
		randomSeed = RandomInt(&randomSeed);
	}

	float2 screenPoint = (float2){convert_float(imageX), convert_float(imageY)};
	float width = convert_float(consts->params.imageWidth);
	float height = convert_float(consts->params.imageHeight);
	float resolution = 1.0f / height;

	//-------- decode data file ----------------
	// main offset for materials
	int materialsMainOffset = GetInteger(0, inBuff);
	int AOVectorsMainOffset = GetInteger(1 * sizeof(int), inBuff);
	int lightsMainOffset = GetInteger(2 * sizeof(int), inBuff);
	int primitivesMainOffset = GetInteger(3 * sizeof(int), inBuff);
#ifdef DEEP_ZOOM_ENABLED
	int deepZoomMainOffset = GetInteger(5 * sizeof(int), inBuff);
#endif

	//--- main material

#ifdef USE_SURFACE_GRADIENT
	int paletteSurfaceOffset;
	int paletteSurfaceLength;
	int opacitySurfaceOffset;
	int opacitySurfaceLength;
	int midpointSurfaceOffset;
	int midpointSurfaceLength;
#endif
#ifdef USE_SPECULAR_GRADIENT
	int paletteSpecularOffset;
	int paletteSpecularLength;
	int opacitySpecularOffset;
	int opacitySpecularLength;
	int midpointSpecularOffset;
	int midpointSpecularLength;
#endif
#ifdef USE_DIFFUSE_GRADIENT
	int paletteDiffuseOffset;
	int paletteDiffuseLength;
	int opacityDiffuseOffset;
	int opacityDiffuseLength;
	int midpointDiffuseOffset;
	int midpointDiffuseLength;
#endif
#ifdef USE_LUMINOSITY_GRADIENT
	int paletteLuminosityOffset;
	int paletteLuminosityLength;
	int opacityLuminosityOffset;
	int opacityLuminosityLength;
	int midpointLuminosityOffset;
	int midpointLuminosityLength;
#endif
#ifdef USE_ROUGHNESS_GRADIENT
	int paletteRoughnessOffset;
	int paletteRoughnessLength;
	int opacityRoughnessOffset;
	int opacityRoughnessLength;
	int midpointRoughnessOffset;
	int midpointRoughnessLength;
#endif
#ifdef USE_REFLECTANCE_GRADIENT
	int paletteReflectanceOffset;
	int paletteReflectanceLength;
	int opacityReflectanceOffset;
	int opacityReflectanceLength;
	int midpointReflectanceOffset;
	int midpointReflectanceLength;
#endif
#ifdef USE_TRANSPARENCY_GRADIENT
	int paletteTransparencyOffset;
	int paletteTransparencyLength;
	int opacityTransparencyOffset;
	int opacityTransparencyLength;
	int midpointTransparencyOffset;
	int midpointTransparencyLength;
#endif

	// number of materials
	int numberOfMaterials = GetInteger(materialsMainOffset, inBuff);

	// materials 1 offset:
	const int materialAddressOffset = materialsMainOffset + 2 * sizeof(int);
	int material0Offset = GetInteger(materialAddressOffset, inBuff);

	// material header
	int materialClOffset = GetInteger(material0Offset, inBuff);
	int paletteItemsOffset = GetInteger(material0Offset + sizeof(int), inBuff);

#ifdef USE_SURFACE_GRADIENT
	paletteSurfaceOffset = GetInteger(material0Offset + sizeof(int) * 2, inBuff);
	paletteSurfaceLength = GetInteger(material0Offset + sizeof(int) * 3, inBuff);
	opacitySurfaceOffset = GetInteger(material0Offset + sizeof(int) * 16, inBuff);
	opacitySurfaceLength = GetInteger(material0Offset + sizeof(int) * 17, inBuff);
	midpointSurfaceOffset = GetInteger(material0Offset + sizeof(int) * 30, inBuff);
	midpointSurfaceLength = GetInteger(material0Offset + sizeof(int) * 31, inBuff);
#endif
#ifdef USE_SPECULAR_GRADIENT
	paletteSpecularOffset = GetInteger(material0Offset + sizeof(int) * 4, inBuff);
	paletteSpecularLength = GetInteger(material0Offset + sizeof(int) * 5, inBuff);
	opacitySpecularOffset = GetInteger(material0Offset + sizeof(int) * 18, inBuff);
	opacitySpecularLength = GetInteger(material0Offset + sizeof(int) * 19, inBuff);
	midpointSpecularOffset = GetInteger(material0Offset + sizeof(int) * 32, inBuff);
	midpointSpecularLength = GetInteger(material0Offset + sizeof(int) * 33, inBuff);
#endif
#ifdef USE_DIFFUSE_GRADIENT
	paletteDiffuseOffset = GetInteger(material0Offset + sizeof(int) * 6, inBuff);
	paletteDiffuseLength = GetInteger(material0Offset + sizeof(int) * 7, inBuff);
	opacityDiffuseOffset = GetInteger(material0Offset + sizeof(int) * 20, inBuff);
	opacityDiffuseLength = GetInteger(material0Offset + sizeof(int) * 21, inBuff);
	midpointDiffuseOffset = GetInteger(material0Offset + sizeof(int) * 34, inBuff);
	midpointDiffuseLength = GetInteger(material0Offset + sizeof(int) * 35, inBuff);
#endif
#ifdef USE_LUMINOSITY_GRADIENT
	paletteLuminosityOffset = GetInteger(material0Offset + sizeof(int) * 8, inBuff);
	paletteLuminosityLength = GetInteger(material0Offset + sizeof(int) * 9, inBuff);
	opacityLuminosityOffset = GetInteger(material0Offset + sizeof(int) * 22, inBuff);
	opacityLuminosityLength = GetInteger(material0Offset + sizeof(int) * 23, inBuff);
	midpointLuminosityOffset = GetInteger(material0Offset + sizeof(int) * 36, inBuff);
	midpointLuminosityLength = GetInteger(material0Offset + sizeof(int) * 37, inBuff);
#endif
#ifdef USE_ROUGHNESS_GRADIENT
	paletteRoughnessOffset = GetInteger(material0Offset + sizeof(int) * 10, inBuff);
	paletteRoughnessLength = GetInteger(material0Offset + sizeof(int) * 11, inBuff);
	opacityRoughnessOffset = GetInteger(material0Offset + sizeof(int) * 24, inBuff);
	opacityRoughnessLength = GetInteger(material0Offset + sizeof(int) * 25, inBuff);
	midpointRoughnessOffset = GetInteger(material0Offset + sizeof(int) * 38, inBuff);
	midpointRoughnessLength = GetInteger(material0Offset + sizeof(int) * 39, inBuff);
#endif
#ifdef USE_REFLECTANCE_GRADIENT
	paletteReflectanceOffset = GetInteger(material0Offset + sizeof(int) * 12, inBuff);
	paletteReflectanceLength = GetInteger(material0Offset + sizeof(int) * 13, inBuff);
	opacityReflectanceOffset = GetInteger(material0Offset + sizeof(int) * 26, inBuff);
	opacityReflectanceLength = GetInteger(material0Offset + sizeof(int) * 27, inBuff);
	midpointReflectanceOffset = GetInteger(material0Offset + sizeof(int) * 40, inBuff);
	midpointReflectanceLength = GetInteger(material0Offset + sizeof(int) * 41, inBuff);
#endif
#ifdef USE_TRANSPARENCY_GRADIENT
	paletteTransparencyOffset = GetInteger(material0Offset + sizeof(int) * 14, inBuff);
	paletteTransparencyLength = GetInteger(material0Offset + sizeof(int) * 15, inBuff);
	opacityTransparencyOffset = GetInteger(material0Offset + sizeof(int) * 28, inBuff);
	opacityTransparencyLength = GetInteger(material0Offset + sizeof(int) * 29, inBuff);
	midpointTransparencyOffset = GetInteger(material0Offset + sizeof(int) * 42, inBuff);
	midpointTransparencyLength = GetInteger(material0Offset + sizeof(int) * 43, inBuff);
#endif

	// material data
	__global sMaterialCl *material = (__global sMaterialCl *)&inBuff[materialClOffset];

	// palette data
	__global float4 *palette = (__global float4 *)&inBuff[paletteItemsOffset];

	//--- AO vectors

	// AO vectors count
	int AOVectorsCount = GetInteger(AOVectorsMainOffset, inBuff);
	int AOVectorsOffset = GetInteger(AOVectorsMainOffset + 1 * sizeof(int), inBuff);

	__global sVectorsAroundCl *__attribute__((aligned(16))) AOVectors =
		(__global sVectorsAroundCl *)&inBuff[AOVectorsOffset];

	//--- Lights

	// AO vectors count
	int numberOfLights = GetInteger(lightsMainOffset, inBuff);
	int lightssOffset = GetInteger(lightsMainOffset + 1 * sizeof(int), inBuff);

	__global sLightCl *__attribute__((aligned(16))) lights =
		(__global sLightCl *)&inBuff[lightssOffset];

	//--- Primitives

	// primitives count
	int numberOfPrimitives = GetInteger(primitivesMainOffset, inBuff);
	int primitivesGlobalDataOffset = GetInteger(primitivesMainOffset + 1 * sizeof(int), inBuff);
	int primitivesOffset = GetInteger(primitivesMainOffset + 2 * sizeof(int), inBuff);

	// global position of primitives
	__global sPrimitiveGlobalDataCl *primitivesGlobalData =
		(__global sPrimitiveGlobalDataCl *)&inBuff[primitivesGlobalDataOffset];

	// data for primitives
	__global sPrimitiveCl *__attribute__((aligned(16))) primitives =
		(__global sPrimitiveCl *)&inBuff[primitivesOffset];

	//--------- end of data file ----------------------------------

	sClPixel pixel;

#ifdef STEREO_REYCYAN
	float3 pixelLeftColor = 0.0f;
	float3 pixelRightColor = 0.0f;
	for (int eye = 0; eye < 2; eye++)
	{
#endif

		// auxiliary vectors
		const float3 one = (float3){1.0f, 0.0f, 0.0f};
		const float3 ones = 1.0f;

		// main rotation matrix
		matrix33 rot;
		rot.m1 = (float3){1.0f, 0.0f, 0.0f};
		rot.m2 = (float3){0.0f, 1.0f, 0.0f};
		rot.m3 = (float3){0.0f, 0.0f, 1.0f};

		rot = RotateZ(rot, consts->params.viewAngle.x);
		rot = RotateX(rot, consts->params.viewAngle.y);
		rot = RotateY(rot, consts->params.viewAngle.z);

		// sweet spot rotation
		rot = RotateZ(rot, -consts->params.sweetSpotHAngle);
		rot = RotateX(rot, consts->params.sweetSpotVAngle);

		matrix33 rotInv = TransposeMatrix(rot);

		// starting point for ray-marching
		float3 start = ds_deep_zoom_camera(consts->params.camera, consts->params.cameraHi,
			consts->params.cameraLo, consts->params.useDeepZoom);

// view vector
#ifdef PERSP_EQUIRECTANGULAR
		float aspectRatio = 2.0f;
#else
	float aspectRatio = width / height;
#endif

#ifdef STEREOSCOPIC
#ifndef STEREO_REYCYAN
#ifndef PERSP_EQUIRECTANGULAR
		aspectRatio = StereoModifyAspectRatio(aspectRatio);
#endif
#endif
#endif

		float2 normalizedScreenPoint;
		normalizedScreenPoint.x = (screenPoint.x / width - 0.5f);
		normalizedScreenPoint.y = -(screenPoint.y / height - 0.5f);
		if (consts->params.legacyCoordinateSystem) normalizedScreenPoint.y *= -1.0f;

#ifdef STEREOSCOPIC
#ifndef STEREO_REYCYAN
		int eye = StereoWhichEye(normalizedScreenPoint);
		normalizedScreenPoint = StereoModifyImagePoint(normalizedScreenPoint);
#endif
#endif

		normalizedScreenPoint.x *= aspectRatio;

#ifdef MONTE_CARLO_ANTI_ALIASING
		normalizedScreenPoint.x +=
			(Random(1000.0f, &randomSeed) / 1000.0f - 0.5f) / width * aspectRatio;
		normalizedScreenPoint.y += (Random(1000.0f, &randomSeed) / 1000.0f - 0.5f) / height;
#endif

		float3 viewVectorNotRotated = CalculateViewVector(normalizedScreenPoint, consts->params.fov);
		float3 viewVector = Matrix33MulFloat3(rot, viewVectorNotRotated);
		float invViewVectorLength = 1.0f / length(viewVector);

#ifdef MONTE_CARLO_DOF
		MonteCarloDOF(&start, &viewVector, consts, rot, &randomSeed);
#endif

#ifdef STEREOSCOPIC
#ifndef PERSP_FISH_EYE_CUT

#ifdef PERSP_EQUIRECTANGULAR // reduce of stereo effect on poles
		float stereoIntensity = 1.0f - pow(normalizedScreenPoint.y * 2.0f, 10.0f);
#else
		float stereoIntensity = 1.0f;
#endif

		start = StereoCalcEyePosition(start, viewVector, consts->params.topVector,
			consts->params.stereoEyeDistance * stereoIntensity, eye, consts->params.stereoSwapEyes);

		StereoViewVectorCorrection(consts->params.stereoInfiniteCorrection * stereoIntensity, &rot,
			&rotInv, eye, consts->params.stereoSwapEyes, &viewVector);
#else	 // PERSP_FISH_EYE_CUT
		float3 eyePosition = 0.0f;
		float3 sideVector = normalize(cross(viewVector, consts->params.topVector));
		float3 rightVector =
			normalize(cross(consts->params.target - consts->params.camera, consts->params.topVector));
		float eyeDistance = consts->params.stereoEyeDistance;
		if (consts->params.stereoSwapEyes) eyeDistance *= -1.0f;

		if (eye == 0)
		{
			eyePosition = start + 0.5f * (rightVector * eyeDistance + sideVector * eyeDistance);
		}
		else
		{
			eyePosition = start - 0.5f * (rightVector * eyeDistance + sideVector * eyeDistance);
		}
		start = eyePosition;
#endif // PERSP_FISH_EYE_CUT
#endif // STEREOSCOPIC

#ifdef PERSP_FISH_EYE_CUT
		bool hemisphereCut = false;
		if (length(normalizedScreenPoint) > M_PI_F * 0.5f / consts->params.fov) hemisphereCut = true;
#endif

		float4 color4 = 0.0f;
		float opacityOut = 0.0f;
		float3 surfaceColor = 0.0f;
		float3 iridescence = 0.0f;

		bool found = false;
		int count = 0;

		float3 point;
		float scan, distThresh, distance;

		scan = 1e-10f;

#ifdef PERSP_FISH_EYE_CUT
		if (!hemisphereCut)
		{
#endif // PERSP_FISH_EYE_CUT

			sClCalcParams calcParam;
			calcParam.N = consts->params.N;
			calcParam.normalCalculationMode = false;
			calcParam.iterThreshMode = consts->params.iterThreshMode;
			distThresh = 1e-6f;

			sRenderData renderData;
			renderData.viewVectorNotRotated = viewVectorNotRotated;
			renderData.material = material;
			renderData.palette = palette;
			renderData.AOVectors = AOVectors;
			renderData.lights = lights;
			renderData.numberOfLights = numberOfLights;

#ifdef USE_SURFACE_GRADIENT
			renderData.paletteSurfaceOffset = paletteSurfaceOffset;
			renderData.paletteSurfaceLength = paletteSurfaceLength;
			renderData.opacitySurfaceOffset = opacitySurfaceOffset;
			renderData.opacitySurfaceLength = opacitySurfaceLength;
			renderData.midpointSurfaceOffset = midpointSurfaceOffset;
			renderData.midpointSurfaceLength = midpointSurfaceLength;
#endif
#ifdef USE_SPECULAR_GRADIENT
			renderData.paletteSpecularOffset = paletteSpecularOffset;
			renderData.paletteSpecularLength = paletteSpecularLength;
			renderData.opacitySpecularOffset = opacitySpecularOffset;
			renderData.opacitySpecularLength = opacitySpecularLength;
			renderData.midpointSpecularOffset = midpointSpecularOffset;
			renderData.midpointSpecularLength = midpointSpecularLength;
#endif
#ifdef USE_DIFFUSE_GRADIENT
			renderData.paletteDiffuseOffset = paletteDiffuseOffset;
			renderData.paletteDiffuseLength = paletteDiffuseLength;
			renderData.opacityDiffuseOffset = opacityDiffuseOffset;
			renderData.opacityDiffuseLength = opacityDiffuseLength;
			renderData.midpointDiffuseOffset = midpointDiffuseOffset;
			renderData.midpointDiffuseLength = midpointDiffuseLength;
#endif
#ifdef USE_LUMINOSITY_GRADIENT
			renderData.paletteLuminosityOffset = paletteLuminosityOffset;
			renderData.paletteLuminosityLength = paletteLuminosityLength;
			renderData.opacityLuminosityOffset = opacityLuminosityOffset;
			renderData.opacityLuminosityLength = opacityLuminosityLength;
			renderData.midpointLuminosityOffset = midpointLuminosityOffset;
			renderData.midpointLuminosityLength = midpointLuminosityLength;
#endif
#ifdef USE_ROUGHNESS_GRADIENT
			renderData.paletteRoughnessOffset = paletteRoughnessOffset;
			renderData.paletteRoughnessLength = paletteRoughnessLength;
			renderData.opacityRoughnessOffset = opacityRoughnessOffset;
			renderData.opacityRoughnessLength = opacityRoughnessLength;
			renderData.midpointRoughnessOffset = midpointRoughnessOffset;
			renderData.midpointRoughnessLength = midpointRoughnessLength;
#endif
#ifdef USE_REFLECTANCE_GRADIENT
			renderData.paletteReflectanceOffset = paletteReflectanceOffset;
			renderData.paletteReflectanceLength = paletteReflectanceLength;
			renderData.opacityReflectanceOffset = opacityReflectanceOffset;
			renderData.opacityReflectanceLength = opacityReflectanceLength;
			renderData.midpointReflectanceOffset = midpointReflectanceOffset;
			renderData.midpointReflectanceLength = midpointReflectanceLength;
#endif
#ifdef USE_TRANSPARENCY_GRADIENT
			renderData.paletteTransparencyOffset = paletteTransparencyOffset;
			renderData.paletteTransparencyLength = paletteTransparencyLength;
			renderData.opacityTransparencyOffset = opacityTransparencyOffset;
			renderData.opacityTransparencyLength = opacityTransparencyLength;
			renderData.midpointTransparencyOffset = midpointTransparencyOffset;
			renderData.midpointTransparencyLength = midpointTransparencyLength;
#endif
			renderData.AOVectorsCount = AOVectorsCount;
			int reflectionsMax = consts->params.reflectionsMax;
			if (reflectionsMax > 1) reflectionsMax = 1;
			if (!consts->params.raytracedReflections) reflectionsMax = 0;
			renderData.reflectionsMax = reflectionsMax;
			renderData.primitives = primitives;
			renderData.numberOfPrimitives = numberOfPrimitives;
			renderData.primitivesGlobalData = primitivesGlobalData;
#ifdef DEEP_ZOOM_ENABLED
			{
				int dzOrbitLength = GetInteger(deepZoomMainOffset, inBuff);
				__global float *dzPowerPtr = (__global float *)&inBuff[deepZoomMainOffset + sizeof(int)];
				__global float *dzBailoutPtr = (__global float *)&inBuff[deepZoomMainOffset + sizeof(int) + sizeof(float)];
				__global double *dzCenterPtr = (__global double *)&inBuff[deepZoomMainOffset + 16];
				__global double *dzSAMat = (__global double *)&inBuff[deepZoomMainOffset + 16 + 3 * sizeof(double)];
				int dzSASkip = GetInteger(deepZoomMainOffset + 16 + 12 * sizeof(double), inBuff);
				int dzSAV = GetInteger(deepZoomMainOffset + 16 + 12 * sizeof(double) + sizeof(int), inBuff);
				int dzOrbOff = GetInteger(deepZoomMainOffset + 16 + 12 * sizeof(double) + 2 * sizeof(int), inBuff);
				renderData.deepZoomOrbit = (__global double *)&inBuff[dzOrbOff];
				renderData.deepZoomSAMatrix = dzSAMat;
				renderData.deepZoomOrbitLength = dzOrbitLength;
				renderData.deepZoomPower = *dzPowerPtr;
				renderData.deepZoomBailout = *dzBailoutPtr;
				renderData.deepZoomCenterX = dzCenterPtr[0];
				renderData.deepZoomCenterY = dzCenterPtr[1];
				renderData.deepZoomCenterZ = dzCenterPtr[2];
				renderData.deepZoomSASkipIters = dzSASkip;
				renderData.deepZoomSAValid = dzSAV;
			}
#endif
			renderData.mRot = rot;
			renderData.mRotInv = rotInv;

			formulaOut outF;
			float step = 0.0f;
			float prevStep = 0.0f;
			float omega = consts->params.marchingOmega;
			if (omega < 1.0f) omega = 1.0f;
			if (omega > 2.0f) omega = 2.0f;

			float searchAccuracy = 0.001f * consts->params.detailLevel;
			float searchLimit = 1.0f - searchAccuracy;

			if (reflectionsMax > 0)
			{
				sRayRecursionIn recursionIn;
				sRayMarchingIn rayMarchingIn;
				rayMarchingIn.binaryEnable = true;
				rayMarchingIn.direction = normalize(viewVector);
				rayMarchingIn.maxScan = consts->params.viewDistanceMax;
				rayMarchingIn.minScan = 0.0f;
				rayMarchingIn.start = start;
				rayMarchingIn.invertMode = false;
				recursionIn.rayMarchingIn = rayMarchingIn;
				recursionIn.calcInside = false;
				recursionIn.resultShader = 0.0f;
				recursionIn.objectColour = 0.0f;
				recursionIn.rayBranch = rayBranchReflection;

				sRayRecursionOut recursionOut =
					RayRecursion(recursionIn, &renderData, consts, image2dBackground, &randomSeed);
				color4 = recursionOut.resultShader;
				surfaceColor = recursionOut.objectColour;
				scan = recursionOut.found ? recursionOut.rayMarchingOut.depth : 1e20f;
				found = recursionOut.found;
			}
			else
			{
			// ray-marching
			for (count = 0; count < MAX_RAYMARCHING && scan < consts->params.viewDistanceMax; count++)
			{
				point = ds_deep_zoom_ray_point(consts->params.cameraHi, consts->params.cameraLo, start,
					viewVector, scan, count, consts->params.useDeepZoom);
				distThresh = CalcDistThresh(point, consts);
				calcParam.distThresh = distThresh;
				calcParam.detailSize = distThresh;
				outF = CalculateDistance(consts, point, &calcParam, &renderData);
				distance = outF.distance;

				if (distance < distThresh)
				{
					found = true;
					break;
				}

#ifdef INTERIOR_MODE
				float candidate = (distance - 0.8f * distThresh) * consts->params.DEFactor * omega;
#else
				float candidate = (distance - 0.5f * distThresh) * consts->params.DEFactor * omega;
#endif
				if (omega > 1.0f && candidate >= prevStep + distance)
					candidate = distance * consts->params.DEFactor;
				step = candidate;
				prevStep = step;

				step *= (1.0f - Random(200, &randomSeed) / 10000.0f);

#ifdef ADVANCED_QUALITY
				step = clamp(step, consts->params.absMinMarchingStep, consts->params.absMaxMarchingStep);

				if (distThresh > consts->params.absMinMarchingStep)
					step = clamp(step, consts->params.relMinMarchingStep * distThresh,
						consts->params.relMaxMarchingStep * distThresh);
#endif

				scan += step * invViewVectorLength;
			}

			point = ds_deep_zoom_ray_point(consts->params.cameraHi, consts->params.cameraLo, start,
				viewVector, scan, count, consts->params.useDeepZoom);

			// final binary searching
			if (found)
			{
				step *= 0.5f;
				for (int i = 0; i < 30; i++)
				{
					if (distance < distThresh && distance > distThresh * searchLimit)
					{
						break;
					}
					else
					{
						if (distance > distThresh)
						{
							scan += step;
							point = start + viewVector * scan;
						}
						else if (distance < distThresh * searchLimit)
						{
							scan -= step;
							point = start + viewVector * scan;
						}
					}
					outF = CalculateDistance(consts, point, &calcParam, &renderData);
					distance = outF.distance;
					step *= 0.5f;
				}
			}

			// shaders
			float3 color = 0.0f;
			float alpha = 0.0f;

			distThresh = CalcDistThresh(point, consts);

			sShaderInputDataCl shaderInputData;
			shaderInputData.point = point;
			shaderInputData.viewVector = viewVector;
			shaderInputData.viewVectorNotRotated = viewVectorNotRotated;
			shaderInputData.distThresh = distThresh;
			shaderInputData.lastDist = distance;
			shaderInputData.delta = calcParam.detailSize;
			shaderInputData.depth = scan;
			shaderInputData.invertMode = false;
			shaderInputData.material = material;
			shaderInputData.palette = palette;
#ifdef USE_SURFACE_GRADIENT
			shaderInputData.paletteSurfaceOffset = renderData.paletteSurfaceOffset;
			shaderInputData.paletteSurfaceLength = renderData.paletteSurfaceLength;
			shaderInputData.opacitySurfaceOffset = renderData.opacitySurfaceOffset;
			shaderInputData.opacitySurfaceLength = renderData.opacitySurfaceLength;
			shaderInputData.midpointSurfaceOffset = renderData.midpointSurfaceOffset;
			shaderInputData.midpointSurfaceLength = renderData.midpointSurfaceLength;
#endif
#ifdef USE_SPECULAR_GRADIENT
			shaderInputData.paletteSpecularOffset = renderData.paletteSpecularOffset;
			shaderInputData.paletteSpecularLength = renderData.paletteSpecularLength;
			shaderInputData.opacitySpecularOffset = renderData.opacitySpecularOffset;
			shaderInputData.opacitySpecularLength = renderData.opacitySpecularLength;
			shaderInputData.midpointSpecularOffset = renderData.midpointSpecularOffset;
			shaderInputData.midpointSpecularLength = renderData.midpointSpecularLength;
#endif
#ifdef USE_DIFFUSE_GRADIENT
			shaderInputData.paletteDiffuseOffset = renderData.paletteDiffuseOffset;
			shaderInputData.paletteDiffuseLength = renderData.paletteDiffuseLength;
			shaderInputData.opacityDiffuseOffset = renderData.opacityDiffuseOffset;
			shaderInputData.opacityDiffuseLength = renderData.opacityDiffuseLength;
			shaderInputData.midpointDiffuseOffset = renderData.midpointDiffuseOffset;
			shaderInputData.midpointDiffuseLength = renderData.midpointDiffuseLength;
#endif
#ifdef USE_LUMINOSITY_GRADIENT
			shaderInputData.paletteLuminosityOffset = renderData.paletteLuminosityOffset;
			shaderInputData.paletteLuminosityLength = renderData.paletteLuminosityLength;
			shaderInputData.opacityLuminosityOffset = renderData.opacityLuminosityOffset;
			shaderInputData.opacityLuminosityLength = renderData.opacityLuminosityLength;
			shaderInputData.midpointLuminosityOffset = renderData.midpointLuminosityOffset;
			shaderInputData.midpointLuminosityLength = renderData.midpointLuminosityLength;
#endif
#ifdef USE_ROUGHNESS_GRADIENT
			shaderInputData.paletteRoughnessOffset = renderData.paletteRoughnessOffset;
			shaderInputData.paletteRoughnessLength = renderData.paletteRoughnessLength;
			shaderInputData.opacityRoughnessOffset = renderData.opacityRoughnessOffset;
			shaderInputData.opacityRoughnessLength = renderData.opacityRoughnessLength;
			shaderInputData.midpointRoughnessOffset = renderData.midpointRoughnessOffset;
			shaderInputData.midpointRoughnessLength = renderData.midpointRoughnessLength;
#endif
#ifdef USE_REFLECTANCE_GRADIENT
			shaderInputData.paletteReflectanceOffset = renderData.paletteReflectanceOffset;
			shaderInputData.paletteReflectanceLength = renderData.paletteReflectanceLength;
			shaderInputData.opacityReflectanceOffset = renderData.opacityReflectanceOffset;
			shaderInputData.opacityReflectanceLength = renderData.opacityReflectanceLength;
			shaderInputData.midpointReflectanceOffset = renderData.midpointReflectanceOffset;
			shaderInputData.midpointReflectanceLength = renderData.midpointReflectanceLength;
#endif
#ifdef USE_TRANSPARENCY_GRADIENT
			shaderInputData.paletteTransparencyOffset = renderData.paletteTransparencyOffset;
			shaderInputData.paletteTransparencyLength = renderData.paletteTransparencyLength;
			shaderInputData.opacityTransparencyOffset = renderData.opacityTransparencyOffset;
			shaderInputData.opacityTransparencyLength = renderData.opacityTransparencyLength;
			shaderInputData.midpointTransparencyOffset = renderData.midpointTransparencyOffset;
			shaderInputData.midpointTransparencyLength = renderData.midpointTransparencyLength;
#endif
			shaderInputData.stepCount = count;
			shaderInputData.randomSeed = randomSeed;

			float3 normal = (float3)(0.0f, 1.0f, 0.0f);

			float3 specular = 0.0f;

			sClGradientsCollection gradients;

			if (found)
			{
				normal =
					NormalVector(consts, &renderData, point, distance, distThresh, false, &calcParam);
				shaderInputData.normal = normal;

				float3 shadowOutDummy;
				float3 outLuminosityEmissive;
				color = ObjectShader(consts, &renderData, &shaderInputData, &calcParam, &surfaceColor,
					&specular, &iridescence, &shadowOutDummy, &outLuminosityEmissive, &alpha, &gradients);
			}
			else
			{
				color = BackgroundShader(consts, &renderData, image2dBackground, &shaderInputData);
				scan = 1e20f;
				alpha = 0.0f;
			}

#ifdef VOLUMETRIC_FOG
			float fogDensity = consts->params.volFogDensity;
			if (fogDensity > 0.0f && found)
			{
				float fogFactor = exp(-fogDensity * scan);
				color = mix(consts->params.fogColor, color, fogFactor);
			}
#endif // VOLUMETRIC_FOG

#ifdef GLOW
			// glow init
			float glow = count * consts->params.glowIntensity / 512.0f * consts->params.DEFactor;
			float glowN = 1.0f - glow;
			if (glowN < 0.0f) glowN = 0.0f;

			float3 glowColor;

			glowColor = (glowN * consts->params.glowColor1 + consts->params.glowColor2 * glow);

			glow *= 0.7f;
			float glowOpacity = 1.0f * glow;
			if (glowOpacity > 1.0f) glowOpacity = 1.0f;
			color = glow * glowColor + (1.0f - glowOpacity) * color;
			alpha += glowOpacity;
#endif // GLOW

			color4 = (float4){color.s0, color.s1, color.s2, alpha};

			} // reflectionsMax == 0

#ifdef PERSP_FISH_EYE_CUT
		}
#endif // PERSP_FISH_EYE_CUT

#ifdef STEREO_REYCYAN
		if (eye == 0)
		{
			pixelLeftColor.s0 = color4.s0;
			pixelLeftColor.s1 = color4.s1;
			pixelLeftColor.s2 = color4.s2;
		}
		else
		{
			pixelRightColor.s0 = color4.s0;
			pixelRightColor.s1 = color4.s1;
			pixelRightColor.s2 = color4.s2;

			pixel.image.s0 = pixelRightColor.s0;
			pixel.image.s1 = pixelLeftColor.s1;
			pixel.image.s2 = pixelLeftColor.s2;
			pixel.zBuffer = scan;
			pixel.color = convert_uchar3(objectColour * 256.0f);
			pixel.opacity = opacityOut * 65535;
			pixel.alpha = color4.s3 * 65535;

			out[buffIndex] = pixel;
		}
	} // next exe

#else	 // no STEREO_REYCYAN

	pixel.image = color4.xyz;
	pixel.zBuffer = scan;
	pixel.color = convert_uchar3(surfaceColor * 256.0f);
	pixel.opacity = opacityOut * 65535;
	pixel.alpha = color4.s3 * 65535;

	out[buffIndex] = pixel;
#endif // STEREO_REYCYAN
}
