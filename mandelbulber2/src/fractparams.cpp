/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2014-24 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * sParamRender struct - container for scene parameters
 */

#include "fractparams.hpp"

#include "object_data.hpp"
#include "objects_tree.h"
#include "parameters.hpp"

sParamRender::sParamRender(const std::shared_ptr<cParameterContainer> container,
	std::vector<cObjectData> *objectData,
	std::vector<cObjectsTree::sNodeDataForRendering> *objectTreeNodes)
		: primitives(container, objectData, objectTreeNodes)
{
	advancedQuality = container->Get<bool>("advanced_quality");
	absMaxMarchingStep = container->Get<double>("abs_max_marching_step");
	absMinMarchingStep = container->Get<double>("abs_min_marching_step");
	allPrimitivesInvisibleAlpha = container->Get<bool>("all_primitives_invisible_alpha");
	antialiasingAdaptive = container->Get<bool>("antialiasing_adaptive");
	antialiasingEnabled = container->Get<bool>("antialiasing_enabled");
	antialiasingOclDepth = container->Get<int>("antialiasing_ocl_depth");
	antialiasingSize = container->Get<int>("antialiasing_size");
	ambientOcclusion = container->Get<float>("ambient_occlusion");
	ambientOcclusionEnabled = container->Get<bool>("ambient_occlusion_enabled");
	ambientOcclusionColor = toRGBFloat(container->Get<sRGB>("ambient_occlusion_color"));
	ambientOcclusionFastTune = container->Get<double>("ambient_occlusion_fast_tune");
	ambientOcclusionMode = params::enumAOMode(container->Get<int>("ambient_occlusion_mode"));
	ambientOcclusionQuality = container->Get<int>("ambient_occlusion_quality");
	ambientOcclusionLightMapRotation =
		container->Get<CVector3>("ao_light_map_rotation") / 180.0 * M_PI;
	mRotAmbientOcclusionLightMapRotation.SetRotation(ambientOcclusionLightMapRotation);
	background3ColorsEnable = container->Get<bool>("background_3_colors_enable");
	background_color1 = toRGBFloat(container->Get<sRGB>("background_color", 1));
	background_color2 = toRGBFloat(container->Get<sRGB>("background_color", 2));
	background_color3 = toRGBFloat(container->Get<sRGB>("background_color", 3));
	background_brightness = container->Get<double>("background_brightness");
	background_gamma = container->Get<double>("background_gamma");
	background_saturation = container->Get<double>("background_saturation");
	backgroundHScale = container->Get<double>("background_h_scale");
	backgroundVScale = container->Get<double>("background_v_scale");
	backgroundTextureOffsetX = container->Get<double>("background_texture_offset_x");
	backgroundTextureOffsetY = container->Get<double>("background_texture_offset_y");
	backgroundRotation = container->Get<CVector3>("background_rotation");
	booleanOperatorsEnabled = container->Get<bool>("boolean_operators");
	camera = container->Get<CVector3>("camera");
	cameraDistanceToTarget = container->Get<double>("camera_distance_to_target");
	cloudsAmbientLight = container->Get<double>("clouds_ambient_light");
	cloudsCastShadows = container->Get<bool>("clouds_cast_shadows");
	cloudsCenter = container->Get<CVector3>("clouds_center");
	cloudsColor = toRGBFloat(container->Get<sRGB>("clouds_color"));
	cloudsDEMultiplier = container->Get<double>("clouds_DE_multiplier");
	cloudsDensity = container->Get<double>("clouds_density");
	cloudsDEApproaching = container->Get<double>("clouds_DE_approaching");
	cloudsDetailAccuracy = container->Get<double>("clouds_detail_accuracy");
	cloudsDistance = container->Get<double>("clouds_distance");
	cloudsDistanceLayer = container->Get<double>("clouds_distance_layer");
	cloudsDistanceMode = container->Get<bool>("clouds_distance_mode");
	cloudsEnable = container->Get<bool>("clouds_enable");
	cloudsLightsBoost = container->Get<double>("clouds_lights_boost");
	cloudsPeriod = container->Get<double>("clouds_period");
	cloudsPlaneShape = container->Get<bool>("clouds_plane_shape");
	cloudsHeight = container->Get<double>("clouds_height");
	cloudsIterations = container->Get<int>("clouds_noise_iterations");
	cloudsOpacity = container->Get<double>("clouds_opacity");
	cloudsRandomSeed = container->Get<int>("clouds_random_seed");
	cloudsRotation = container->Get<CVector3>("clouds_rotation");
	cloudsSpeed = container->Get<CVector3>("clouds_speed");
	cloudsSharpEdges = container->Get<bool>("clouds_sharp_edges");
	cloudsSharpness = container->Get<double>("clouds_sharpness");
	constantDEThreshold = container->Get<bool>("constant_DE_threshold");
	constantFactor = container->Get<double>("fractal_constant_factor");
	DEFactor = container->Get<double>("DE_factor");
	delta_DE_function = fractal::enumDEFunctionType(container->Get<int>("delta_DE_function"));
	delta_DE_method = fractal::enumDEMethod(container->Get<int>("delta_DE_method"));
	deltaDERelativeDelta = container->Get<double>("deltade_relative_delta");
	detailLevel = container->Get<double>("detail_level");
	detailSizeMax = container->Get<double>("detail_size_max");
	detailSizeMin = container->Get<double>("detail_size_min");
	DEThresh = container->Get<double>("DE_thresh");
	distanceFogShadows = container->Get<bool>("distance_fog_shadows");
	DOFEnabled = container->Get<bool>("DOF_enabled");
	DOFFocus = container->Get<double>("DOF_focus");
	DOFRadius = container->Get<double>("DOF_radius");
	DOFMaxRadius = container->Get<double>("DOF_max_radius");
	DOFHDRMode = container->Get<bool>("DOF_HDR");
	DOFMonteCarlo = container->Get<bool>("DOF_monte_carlo");
	DOFMonteCarloGlobalIllumination = container->Get<bool>("DOF_MC_global_illumination");
	DOFNumberOfPasses = container->Get<int>("DOF_number_of_passes");
	DOFSamples = container->Get<int>("DOF_samples");
	DOFMinSamples = container->Get<int>("DOF_min_samples");
	DOFBlurOpacity = container->Get<double>("DOF_blur_opacity");
	DOFMaxNoise = container->Get<double>("DOF_max_noise");
	DOFMonteCarloChromaticAberration = container->Get<bool>("DOF_MC_CA_enable");
	DOFMonteCarloCADispersionGain = container->Get<float>("DOF_MC_CA_dispersion_gain");
	DOFMonteCarloCACameraDispersion = container->Get<float>("DOF_MC_CA_camera_dispersion");
	envMappingEnable = container->Get<bool>("env_mapping_enable");
	backgroundAsEnvmap = container->Get<bool>("background_as_envmap");
	backgroundAsLightmap = container->Get<bool>("background_as_lightmap");
	fakeLightsColor = toRGBFloat(container->Get<sRGB>("fake_lights_color"));
	fakeLightsColor2 = toRGBFloat(container->Get<sRGB>("fake_lights_color_2"));
	fakeLightsColor3 = toRGBFloat(container->Get<sRGB>("fake_lights_color_3"));
	for (int mc = 0; mc < 24; mc++)
	{
		fakeLightsMultiCenterColor[mc] =
			toRGBFloat(container->Get<sRGB>(QString("fake_lights_multi_center_color_%1").arg(mc + 1)));
	}
	fakeLightsEnabled = container->Get<bool>("fake_lights_enabled");
	fakeLightsIntensity = container->Get<double>("fake_lights_intensity");
	fakeLightsVisibility = container->Get<double>("fake_lights_visibility");
	fakeLightsVisibilitySize = container->Get<double>("fake_lights_visibility_size");
	fakeLightsMaskEnabled = container->Get<bool>("fake_lights_mask_enabled");
	fakeLightsMaskThreshold = container->Get<double>("fake_lights_mask_threshold");
	fakeLightsMaskSharpness = container->Get<double>("fake_lights_mask_sharpness");
	fillLightColor = toRGBFloat(container->Get<sRGB>("fill_light_color"));
	fogColor = toRGBFloat(container->Get<sRGB>("basic_fog_color"));
	fogEnabled = container->Get<bool>("basic_fog_enabled");
	fogVisibility = container->Get<double>("basic_fog_visibility");
	fogCastShadows = container->Get<bool>("basic_fog_cast_shadows");
	perspectiveType = params::enumPerspectiveType(container->Get<int>("perspective_type"));
	fov = CalcFOV(container->Get<double>("fov"), perspectiveType);
	frameNo = container->Get<int>("frame_no");
	glowColor1 = toRGBFloat(container->Get<sRGB>("glow_color", 1));
	glowColor2 = toRGBFloat(container->Get<sRGB>("glow_color", 2));
	glowEnabled = container->Get<bool>("glow_enabled");
	glowIntensity = container->Get<float>("glow_intensity");
	hdrBlurEnabled = container->Get<bool>("hdr_blur_enabled");
	hdrBlurRadius = container->Get<double>("hdr_blur_radius");
	hdrBlurIntensity = container->Get<double>("hdr_blur_intensity");
	hybridFractalEnable = container->Get<bool>("hybrid_fractal_enable");
	imageAdjustments.brightness = container->Get<float>("brightness");
	imageAdjustments.contrast = container->Get<float>("contrast");
	imageAdjustments.hdrEnabled = container->Get<bool>("hdr");
	imageAdjustments.toneMappingMode = container->Get<int>("tone_mapping_mode");
	imageAdjustments.toneExposure = container->Get<float>("tone_exposure");
	imageAdjustments.imageGamma = container->Get<float>("gamma");
	imageAdjustments.saturation = container->Get<float>("saturation");
	imageAdjustments.colorTemperature = container->Get<float>("color_temperature");
	imageAdjustments.blackPoint = container->Get<float>("image_black_point");
	imageAdjustments.whitePoint = container->Get<float>("image_white_point");
	imageAdjustments.vignetteIntensity = container->Get<float>("vignette_intensity");
	imageAdjustments.vignetteRadius = container->Get<float>("vignette_radius");
	imageAdjustments.sharpenIntensity = container->Get<float>("sharpen_intensity");
	imageHeight = container->Get<int>("image_height");
	imageWidth = container->Get<int>("image_width");
	interiorMode = container->Get<bool>("interior_mode");
	iterFogBrightnessBoost = container->Get<float>("iteration_fog_brightness_boost");
	iterFogColor1Maxiter = container->Get<float>("iteration_fog_color_1_maxiter");
	iterFogColor2Maxiter = container->Get<float>("iteration_fog_color_2_maxiter");
	iterFogColour1 = toRGBFloat(container->Get<sRGB>("iteration_fog_color", 1));
	iterFogColour2 = toRGBFloat(container->Get<sRGB>("iteration_fog_color", 2));
	iterFogColour3 = toRGBFloat(container->Get<sRGB>("iteration_fog_color", 3));
	iterFogEnabled = container->Get<bool>("iteration_fog_enable");
	iterFogOpacity = container->Get<double>("iteration_fog_opacity");
	iterFogOpacityTrim = container->Get<float>("iteration_fog_opacity_trim");
	iterFogOpacityTrimHigh = container->Get<float>("iteration_fog_opacity_trim_high");
	iterFogShadows = container->Get<bool>("iteration_fog_shadows");
	legacyCoordinateSystem = container->Get<bool>("legacy_coordinate_system");
	limitMax = container->Get<CVector3>("limit_max");
	limitMin = container->Get<CVector3>("limit_min");
	limitsEnabled = container->Get<bool>("limits_enabled");
	maxRaymarchingSteps = container->Get<int>("max_raymarching_steps");
	minN = container->Get<int>("minN");
	monteCarloSoftShadows = container->Get<bool>("MC_soft_shadows_enable");
	monteCarloGIRadianceLimit = container->Get<float>("MC_GI_radiance_limit");
	monteCarloGIUseReflectance = container->Get<bool>("MC_GI_use_reflectance");
	monteCarloGIVolumetric = container->Get<bool>("MC_global_illumination_volumetric");
	monteCarloGIOfVolumetric = container->Get<bool>("MC_fog_illumination");
	monteCarloDenoiserEnable = container->Get<bool>("MC_denoiser_enable");
	monteCarloDenoiserStrength = container->Get<int>("MC_denoiser_strength");
	monteCarloDenoiserPreserveGeometry = container->Get<bool>("MC_denoiser_preserve_geometry");
	monteCarloPixelLevelOptimization = container->Get<bool>("MC_pixel_level_optimization");
	N = container->Get<int>("N");
	nebulaBrighness = container->Get<float>("nebula_brightness");
	nebulaConstantBrighness = container->Get<bool>("nebula_constant_brightness");
	nebulaColorMixing = container->Get<int>("nebula_color_mixing");
	nebulaNumberOfSamplesPerPixel = container->Get<int>("nebula_samples_per_pixel");
	nebulaMinIteration = container->Get<int>("nebula_min_iteration");
	nebulaInnerEnabled = container->Get<bool>("nebula_inner_enabled");
	nebulaOuterEnabled = container->Get<bool>("nebula_outer_enabled");
	nebulaXAxisColorsEnabled = container->Get<bool>("nebula_x_axis_colors_enabled");
	nebulaYAxisColorsEnabled = container->Get<bool>("nebula_y_axis_colors_enabled");
	nebulaZAxisColorsEnabled = container->Get<bool>("nebula_z_axis_colors_enabled");
	nebulaIterationsColorsEnabled = container->Get<bool>("nebula_iterations_colors_enabled");
	nebulaGridDomainEnabled = container->Get<bool>("nebula_grid_domain_enabled");
	nebulaXGridSize = container->Get<float>("nebula_x_grid_size");
	nebulaYGridSize = container->Get<float>("nebula_y_grid_size");
	nebulaZGridSize = container->Get<float>("nebula_z_grid_size");
	objectsTreeEnable = container->Get<bool>("objects_tree_enable");
	postChromaticAberrationEnabled = container->Get<bool>("post_chromatic_aberration_enabled");
	postChromaticAberrationRadius = container->Get<float>("post_chromatic_aberration_radius");
	postChromaticAberrationIntensity = container->Get<float>("post_chromatic_aberration_intensity");
	postChromaticAberrationReverse = container->Get<bool>("post_chromatic_aberration_reverse");
	rayleighScatteringBlue = container->Get<float>("rayleigh_scattering_blue");
	rayleighScatteringRed = container->Get<float>("rayleigh_scattering_red");
	raytracedReflections = container->Get<bool>("raytraced_reflections");
	reflectionsMax = container->Get<int>("reflections_max");
	relMaxMarchingStep = container->Get<double>("rel_max_marching_step");
	relMinMarchingStep = container->Get<double>("rel_min_marching_step");
	repeatFrom = container->Get<int>("repeat_from");
	resolution = 0.0;
	slowShading = container->Get<bool>("slow_shading");
	smoothness = container->Get<double>("smoothness");
	SSAO_random_mode = container->Get<bool>("SSAO_random_mode");
	stereoEyeDistance = container->Get<double>("stereo_eye_distance");
	stereoInfiniteCorrection = container->Get<double>("stereo_infinite_correction");
	stereoSwapEyes = container->Get<bool>("stereo_swap_eyes");
	sweetSpotHAngle = container->Get<double>("sweet_spot_horizontal_angle") / 180.0 * M_PI;
	sweetSpotVAngle = container->Get<double>("sweet_spot_vertical_angle") / 180.0 * M_PI;
	target = container->Get<CVector3>("target");
	target = container->Get<CVector3>("target");
	texturedBackground = container->Get<bool>("textured_background");
	texturedBackgroundMapType =
		params::enumTextureMapType(container->Get<int>("textured_background_map_type"));
	topVector = container->Get<CVector3>("camera_top");
	useDefaultBailout = container->Get<bool>("use_default_bailout");
	viewAngle = container->Get<CVector3>("camera_rotation");
	viewDistanceMax = container->Get<double>("view_distance_max");
	viewDistanceMin = container->Get<double>("view_distance_min");
	volFogColour1 = toRGBFloat(container->Get<sRGB>("fog_color", 1));
	volFogColour1Distance = container->Get<double>("volumetric_fog_colour_1_distance");
	volFogColour2 = toRGBFloat(container->Get<sRGB>("fog_color", 2));
	volFogColour2Distance = container->Get<double>("volumetric_fog_colour_2_distance");
	volFogColour3 = toRGBFloat(container->Get<sRGB>("fog_color", 3));
	volFogDensity = container->Get<float>("volumetric_fog_density");
	volFogDistanceFactor = container->Get<double>("volumetric_fog_distance_factor");
	volFogDistanceFromSurface = container->Get<double>("volumetric_fog_distance_from_surface");
	volFogEnabled = container->Get<bool>("volumetric_fog_enabled");
	volumetricLightDEFactor = container->Get<double>("volumetric_light_DE_Factor");

	mRotBackgroundRotation.SetRotation(backgroundRotation * M_PI / 180.0);
	mRotCloudsRotation.SetRotation2(cloudsRotation * M_PI / 180.0);

	nebulaXAxisColors.SetColorsFromString(container->Get<QString>("nebula_x_axis_colors"));
	nebulaYAxisColors.SetColorsFromString(container->Get<QString>("nebula_y_axis_colors"));
	nebulaZAxisColors.SetColorsFromString(container->Get<QString>("nebula_z_axis_colors"));
	nebulaIterationsColors.SetColorsFromString(container->Get<QString>("nebula_iterations_colors"));

	for (int i = 0; i < NUMBER_OF_FRACTALS - 1; i++)
	{
		booleanOperator[i] =
			params::enumBooleanOperator(container->Get<int>("boolean_operator", i + 1));
	}

	for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
	{
		formulaPosition[i] = container->Get<CVector3>("formula_position", i + 1);
		formulaRotation[i] = container->Get<CVector3>("formula_rotation", i + 1);
		formulaRepeat[i] = container->Get<CVector3>("formula_repeat", i + 1);
		formulaScale[i] = 1.0 / container->Get<double>("formula_scale", i + 1);
		mRotFormulaRotation[i].SetRotation2(formulaRotation[i] * (M_PI / 180.0));
		formulaMaterialId[i] = container->Get<int>("formula_material_id", i + 1);
		smoothDeCombineEnable[i] = container->Get<bool>("smooth_de_combine_enable", i + 1);
		smoothDeCombineDistance[i] = container->Get<double>("smooth_de_combine_distance", i + 1);

		if (objectData)
		{
			cObjectData oneObjectData;
			oneObjectData.position = formulaPosition[i];
			oneObjectData.size = CVector3(1.0, 1.0, 1.0) / formulaScale[i];
			oneObjectData.repeat = formulaRepeat[i];
			oneObjectData.SetRotation(formulaRotation[i]);
			oneObjectData.materialId = formulaMaterialId[i];
			oneObjectData.objectType = fractal::objFractal;
			(*objectData)[i] = oneObjectData;
		}

		if (objectTreeNodes)
		{
			cObjectsTree::WriteInternalNodeID(i, i, -1, objectTreeNodes);
		}
	}

	if (!booleanOperatorsEnabled && objectData)
	{
		formulaMaterialId[0] = container->Get<int>("formula_material_id");
		(*objectData)[0].materialId = formulaMaterialId[0];
		(*objectData)[0].position = container->Get<CVector3>("fractal_position");
		(*objectData)[0].repeat = container->Get<CVector3>("repeat");
		(*objectData)[0].size = CVector3(1.0, 1.0, 1.0);
		(*objectData)[0].SetRotation(container->Get<CVector3>("fractal_rotation"));
		(*objectData)[0].objectType = fractal::objFractal;

		if (objectTreeNodes)
		{
			cObjectsTree::WriteInternalNodeID(0, 0, -1, objectTreeNodes);
		}
	}

	common.fakeLightsColor2Enabled = container->Get<bool>("fake_lights_color_2_enabled");
	common.fakeLightsColor3Enabled = container->Get<bool>("fake_lights_color_3_enabled");
	common.fakeLightsMaxIter = container->Get<int>("fake_lights_max_iter");
	common.fakeLightsMinIter = container->Get<int>("fake_lights_min_iter");
	common.fakeLightsCenterIteration = container->Get<int>("fake_lights_center_iteration");
	common.fakeLightsOrbitTrap = container->Get<CVector3>("fake_lights_orbit_trap");
	common.fakeLightsMultiCenterEnabled = container->Get<bool>("fake_lights_multi_center_enabled");
	for (int mc = 0; mc < 24; mc++)
	{
		common.fakeLightsMultiCenter[mc] =
			container->Get<CVector3>(QString("fake_lights_multi_center_%1").arg(mc + 1));
		common.fakeLightsMultiCenterWeight[mc] =
			container->Get<double>(QString("fake_lights_multi_center_weight_%1").arg(mc + 1));
	}
	common.fakeLightsOrbitTrapShape =
		params::enumFakeLightsShape(container->Get<int>("fake_lights_orbit_trap_shape"));
	common.fakeLightsOrbitTrapSize = container->Get<double>("fake_lights_orbit_trap_size");
	common.fakeLightsThickness = container->Get<double>("fake_lights_thickness");
	common.fakeLightsDecayFunction =
		params::enumFakeLightsDecay(container->Get<int>("fake_lights_decay_function"));
	common.fakeLightsRelativeCenter = container->Get<bool>("fake_lights_relative_center");
	common.fakeLightsRotation = container->Get<CVector3>("fake_lights_orbit_rotation");
	common.foldings.boxEnable = container->Get<bool>("box_folding");
	common.foldings.boxLimit = container->Get<double>("box_folding_limit");
	common.foldings.boxValue = container->Get<double>("box_folding_value");
	common.foldings.sphericalEnable = container->Get<bool>("spherical_folding");
	common.foldings.sphericalInner = container->Get<double>("spherical_folding_inner");
	common.foldings.sphericalOuter = container->Get<double>("spherical_folding_outer");
	common.fractalPosition = container->Get<CVector3>("fractal_position");
	common.fractalRotation = container->Get<CVector3>("fractal_rotation");
	common.mRotFractalRotation.SetRotation2(common.fractalRotation / 180.0 * M_PI);
	common.repeat = container->Get<CVector3>("repeat");
	common.iterThreshMode = iterThreshMode = container->Get<bool>("iteration_threshold_mode");
	common.linearDEOffset = container->Get<double>("linear_DE_offset");

	common.mRotFakeLightsRotation.SetRotation2(common.fakeLightsRotation * M_PI / 180.0);

	// V2: Position mode and per-mode parameters
	common.fakeLightsPositionMode =
		params::enumFakeLightsPositionMode(container->Get<int>("fake_lights_position_mode"));

	// Mode 0: World
	common.fakeLightsModes[0].offset = container->Get<CVector3>("fake_lights_world_offset");
	common.fakeLightsModes[0].scale = container->Get<double>("fake_lights_world_scale");
	common.fakeLightsModes[0].rotation = container->Get<CVector3>("fake_lights_world_rotation");

	// Mode 1: Camera
	common.fakeLightsModes[1].offset = container->Get<CVector3>("fake_lights_camera_offset");
	common.fakeLightsModes[1].scale = container->Get<double>("fake_lights_camera_scale");
	common.fakeLightsModes[1].rotation = container->Get<CVector3>("fake_lights_camera_rotation");

	// Mode 2: Target
	common.fakeLightsModes[2].offset = container->Get<CVector3>("fake_lights_target_offset");
	common.fakeLightsModes[2].scale = container->Get<double>("fake_lights_target_scale");
	common.fakeLightsModes[2].rotation = container->Get<CVector3>("fake_lights_target_rotation");

	// Mode 3: FractalCenter
	common.fakeLightsModes[3].offset = container->Get<CVector3>("fake_lights_fractal_center_offset");
	common.fakeLightsModes[3].scale = container->Get<double>("fake_lights_fractal_center_scale");
	common.fakeLightsModes[3].rotation = container->Get<CVector3>("fake_lights_fractal_center_rotation");

	// Mode 4: Path Circle
	common.fakeLightsModes[4].offset = container->Get<CVector3>("fake_lights_path_circle_offset");
	common.fakeLightsModes[4].scale = container->Get<double>("fake_lights_path_circle_scale");
	common.fakeLightsModes[4].rotation = container->Get<CVector3>("fake_lights_path_circle_rotation");
	common.fakeLightsModes[4].pathRadius = container->Get<double>("fake_lights_path_circle_path_radius");

	// Mode 5: Path Spiral
	common.fakeLightsModes[5].offset = container->Get<CVector3>("fake_lights_path_spiral_offset");
	common.fakeLightsModes[5].scale = container->Get<double>("fake_lights_path_spiral_scale");
	common.fakeLightsModes[5].rotation = container->Get<CVector3>("fake_lights_path_spiral_rotation");
	common.fakeLightsModes[5].pathRadius = container->Get<double>("fake_lights_path_spiral_path_radius");

	// Mode 6: Orbit Around Target
	common.fakeLightsModes[6].offset = container->Get<CVector3>("fake_lights_orbit_target_offset");
	common.fakeLightsModes[6].scale = container->Get<double>("fake_lights_orbit_target_scale");
	common.fakeLightsModes[6].rotation = container->Get<CVector3>("fake_lights_orbit_target_rotation");
	common.fakeLightsModes[6].pathRadius = container->Get<double>("fake_lights_orbit_target_path_radius");

	// V2: Shape modifiers
	common.fakeLightsShapeTwist = container->Get<double>("fake_lights_shape_twist");
	common.fakeLightsShapeBend = container->Get<double>("fake_lights_shape_bend");
	common.fakeLightsShapeTaper = container->Get<double>("fake_lights_shape_taper");
	common.fakeLightsShapeFoldSymmetry = container->Get<int>("fake_lights_shape_fold_symmetry");
	common.fakeLightsShapeRepeatX = container->Get<double>("fake_lights_shape_repeat_x");
	common.fakeLightsShapeRepeatY = container->Get<double>("fake_lights_shape_repeat_y");
	common.fakeLightsShapeRepeatZ = container->Get<double>("fake_lights_shape_repeat_z");
	common.fakeLightsShapeWobbleAmplitude = container->Get<double>("fake_lights_shape_wobble_amplitude");
	common.fakeLightsShapeWobbleFrequency = container->Get<double>("fake_lights_shape_wobble_frequency");
	common.fakeLightsShapeChamfer = container->Get<double>("fake_lights_shape_chamfer");
	common.fakeLightsShapeScaleX = container->Get<double>("fake_lights_shape_scale_x");
	common.fakeLightsShapeScaleY = container->Get<double>("fake_lights_shape_scale_y");
	common.fakeLightsShapeScaleZ = container->Get<double>("fake_lights_shape_scale_z");
	common.fakeLightsShapeMirrorX = container->Get<bool>("fake_lights_shape_mirror_x");
	common.fakeLightsShapeMirrorY = container->Get<bool>("fake_lights_shape_mirror_y");
	common.fakeLightsShapeMirrorZ = container->Get<bool>("fake_lights_shape_mirror_z");
	common.fakeLightsShapeInflate = container->Get<double>("fake_lights_shape_inflate");
	common.fakeLightsShapeLineLength = container->Get<double>("fake_lights_shape_line_length");
	common.fakeLightsShapeTubeRadius = container->Get<double>("fake_lights_shape_tube_radius");
	common.fakeLightsShapeLineThickness = container->Get<double>("fake_lights_shape_line_thickness");
	common.fakeLightsShapeFalloff = container->Get<double>("fake_lights_shape_falloff");
	common.fakeLightsShapeMaskRadius = container->Get<double>("fake_lights_shape_mask_radius");
	common.fakeLightsShapeMaskSoftness = container->Get<double>("fake_lights_shape_mask_softness");
	common.fakeLightsShapeSpiral = container->Get<double>("fake_lights_shape_spiral");
	common.fakeLightsShapeWaveX = container->Get<double>("fake_lights_shape_wave_x");
	common.fakeLightsShapeWaveY = container->Get<double>("fake_lights_shape_wave_y");
	common.fakeLightsShapeWaveZ = container->Get<double>("fake_lights_shape_wave_z");
	common.fakeLightsShapeWaveFrequency = container->Get<double>("fake_lights_shape_wave_frequency");
	common.fakeLightsTransitionSpeed = container->Get<double>("fake_lights_transition_speed");
	common.fakeLightsTransitionSourceMode =
		params::enumFakeLightsPositionMode(container->Get<int>("fake_lights_transition_source_mode"));
	common.fakeLightsTransitionBlend = container->Get<double>("fake_lights_transition_blend");

	// V2: Transition interpolation - update blend factor and compute blended orbit trap
	if (common.fakeLightsTransitionSpeed > 0.0)
	{
		auto calculateModePosition = [&](int modeIdx) -> CVector3 {
			const sFakeLightsModeParams &m = common.fakeLightsModes[modeIdx];
			CRotationMatrix mRot;
			mRot.SetRotation2(m.rotation * M_PI / 180.0);
			CVector3 trap = m.offset + mRot.RotateVector(common.fakeLightsOrbitTrap * m.scale);
			switch (modeIdx)
			{
				case params::fakeLightsPositionCamera:
					return camera + trap;
				case params::fakeLightsPositionTarget:
					return target + trap;
				case params::fakeLightsPositionPathCircle:
				{
					double angle = m.rotation.y * M_PI / 180.0;
					CVector3 pathOffset(cos(angle) * m.pathRadius, 0.0, sin(angle) * m.pathRadius);
					return trap + pathOffset;
				}
				case params::fakeLightsPositionPathSpiral:
				{
					double angle = m.rotation.y * M_PI / 180.0;
					double yOffset = angle * m.pathRadius * 0.1;
					CVector3 pathOffset(cos(angle) * m.pathRadius, yOffset, sin(angle) * m.pathRadius);
					return trap + pathOffset;
				}
				case params::fakeLightsPositionOrbitTarget:
				{
					double angle = m.rotation.y * M_PI / 180.0;
					CVector3 pathOffset(cos(angle) * m.pathRadius, 0.0, sin(angle) * m.pathRadius);
					return target + trap + pathOffset;
				}
				default: // World and FractalCenter
					return trap;
			}
		};

		int currentMode = common.fakeLightsPositionMode;
		int sourceMode = common.fakeLightsTransitionSourceMode;

		if (sourceMode < 0 || sourceMode > 6) sourceMode = currentMode;

		if (sourceMode != currentMode)
		{
			// Transition in progress or just started
			if (common.fakeLightsTransitionBlend >= 1.0)
				common.fakeLightsTransitionBlend = 0.0;

			common.fakeLightsTransitionBlend += common.fakeLightsTransitionSpeed * 0.05;
			if (common.fakeLightsTransitionBlend >= 1.0)
			{
				common.fakeLightsTransitionBlend = 1.0;
				common.fakeLightsTransitionSourceMode = params::enumFakeLightsPositionMode(currentMode);
			}
		}
		else
		{
			common.fakeLightsTransitionBlend = 1.0;
		}

		CVector3 sourcePos = calculateModePosition(sourceMode);
		CVector3 targetPos = calculateModePosition(currentMode);
		double blend = common.fakeLightsTransitionBlend;
		common.fakeLightsOrbitTrap = sourcePos * (1.0 - blend) + targetPos * blend;
		common.fakeLightsOrbitTrapPreTransformed = true;

		// Write back to container so next frame continues the transition
		container->Set("fake_lights_transition_source_mode", int(common.fakeLightsTransitionSourceMode));
		container->Set("fake_lights_transition_blend", common.fakeLightsTransitionBlend);
	}
	else
	{
		// Instant transition
		common.fakeLightsTransitionBlend = 1.0;
		common.fakeLightsTransitionSourceMode = common.fakeLightsPositionMode;
		common.fakeLightsOrbitTrapPreTransformed = false;
		container->Set("fake_lights_transition_source_mode", int(common.fakeLightsPositionMode));
		container->Set("fake_lights_transition_blend", 1.0);
	}

	// Glow Sphere
	glowSphere1.enabled = container->Get<bool>("glow_sphere_1_enabled");
	glowSphere1.position = container->Get<CVector3>("glow_sphere_1_position");
	glowSphere1.rotation = container->Get<CVector3>("glow_sphere_1_rotation");
	glowSphere1.radius = container->Get<double>("glow_sphere_1_radius");
	glowSphere1.color = container->Get<sRGB>("glow_sphere_1_color");
	glowSphere1.intensity = container->Get<double>("glow_sphere_1_intensity");
	glowSphere1.falloffRadius = container->Get<double>("glow_sphere_1_falloff_radius");
	glowSphere1.outerColor = container->Get<sRGB>("glow_sphere_1_outer_color");
	glowSphere1.pulseSpeed = container->Get<double>("glow_sphere_1_pulse_speed");
	glowSphere1.pulseAmount = container->Get<double>("glow_sphere_1_pulse_amount");

	// Glow Sphere 2
	glowSphere2.enabled = container->Get<bool>("glow_sphere_2_enabled");
	glowSphere2.position = container->Get<CVector3>("glow_sphere_2_position");
	glowSphere2.rotation = container->Get<CVector3>("glow_sphere_2_rotation");
	glowSphere2.radius = container->Get<double>("glow_sphere_2_radius");
	glowSphere2.color = container->Get<sRGB>("glow_sphere_2_color");
	glowSphere2.intensity = container->Get<double>("glow_sphere_2_intensity");
	glowSphere2.falloffRadius = container->Get<double>("glow_sphere_2_falloff_radius");
	glowSphere2.outerColor = container->Get<sRGB>("glow_sphere_2_outer_color");
	glowSphere2.pulseSpeed = container->Get<double>("glow_sphere_2_pulse_speed");
	glowSphere2.pulseAmount = container->Get<double>("glow_sphere_2_pulse_amount");

	// Glow Sphere 3
	glowSphere3.enabled = container->Get<bool>("glow_sphere_3_enabled");
	glowSphere3.position = container->Get<CVector3>("glow_sphere_3_position");
	glowSphere3.rotation = container->Get<CVector3>("glow_sphere_3_rotation");
	glowSphere3.radius = container->Get<double>("glow_sphere_3_radius");
	glowSphere3.color = container->Get<sRGB>("glow_sphere_3_color");
	glowSphere3.intensity = container->Get<double>("glow_sphere_3_intensity");
	glowSphere3.falloffRadius = container->Get<double>("glow_sphere_3_falloff_radius");
	glowSphere3.outerColor = container->Get<sRGB>("glow_sphere_3_outer_color");
	glowSphere3.pulseSpeed = container->Get<double>("glow_sphere_3_pulse_speed");
	glowSphere3.pulseAmount = container->Get<double>("glow_sphere_3_pulse_amount");

	// Glow Sphere 4
	glowSphere4.enabled = container->Get<bool>("glow_sphere_4_enabled");
	glowSphere4.position = container->Get<CVector3>("glow_sphere_4_position");
	glowSphere4.rotation = container->Get<CVector3>("glow_sphere_4_rotation");
	glowSphere4.radius = container->Get<double>("glow_sphere_4_radius");
	glowSphere4.color = container->Get<sRGB>("glow_sphere_4_color");
	glowSphere4.intensity = container->Get<double>("glow_sphere_4_intensity");
	glowSphere4.falloffRadius = container->Get<double>("glow_sphere_4_falloff_radius");
	glowSphere4.outerColor = container->Get<sRGB>("glow_sphere_4_outer_color");
	glowSphere4.pulseSpeed = container->Get<double>("glow_sphere_4_pulse_speed");
	glowSphere4.pulseAmount = container->Get<double>("glow_sphere_4_pulse_amount");

	// Single Trap Lights
	singleTrapLights.enabled = container->Get<bool>("single_trap_lights_enabled");
	int storedActiveCount = container->Get<int>("single_trap_lights_active_count");
	if (storedActiveCount < 0) storedActiveCount = 0;
	if (storedActiveCount > MAX_SINGLE_TRAP_LIGHT_LAYERS) storedActiveCount = MAX_SINGLE_TRAP_LIGHT_LAYERS;
	// Automatically derive active count from highest enabled layer so the UI
	// spinbox cannot hide layers that are enabled.
	int highestEnabled = 0;
	for (int i = 1; i <= MAX_SINGLE_TRAP_LIGHT_LAYERS; i++)
	{
		if (container->Get<bool>(QString("single_trap_light_%1_enabled").arg(i))) highestEnabled = i;
	}
	singleTrapLights.activeLayerCount = std::max(storedActiveCount, highestEnabled);
	singleTrapLights.soloLayerIndex = container->Get<int>("single_trap_lights_solo_layer");
	if (singleTrapLights.soloLayerIndex < 0) singleTrapLights.soloLayerIndex = 0;
	if (singleTrapLights.soloLayerIndex > MAX_SINGLE_TRAP_LIGHT_LAYERS)
		singleTrapLights.soloLayerIndex = MAX_SINGLE_TRAP_LIGHT_LAYERS;
	{
		int cm = container->Get<int>("single_trap_lights_combine_mode");
		if (cm < 0) cm = 0;
		if (cm > 4) cm = 4;
		singleTrapLights.combineMode = params::enumSingleTrapLightsCombineMode(cm);
	}
	for (int i = 0; i < MAX_SINGLE_TRAP_LIGHT_LAYERS; i++)
	{
		QString prefix = QString("single_trap_light_%1").arg(i + 1);
		singleTrapLights.layers[i].enabled = container->Get<bool>(prefix + "_enabled");
		singleTrapLights.layers[i].shape = params::enumSingleTrapLightShape(
			container->Get<int>(prefix + "_shape"));
		singleTrapLights.layers[i].position = container->Get<CVector3>(prefix + "_position");
		singleTrapLights.layers[i].size = container->Get<double>(prefix + "_size");
		singleTrapLights.layers[i].size2 = container->Get<double>(prefix + "_size2");
		singleTrapLights.layers[i].thickness = container->Get<double>(prefix + "_thickness");
		singleTrapLights.layers[i].rotation = container->Get<CVector3>(prefix + "_rotation");
		singleTrapLights.layers[i].UpdateRotationMatrix();
		singleTrapLights.layers[i].intensity = container->Get<double>(prefix + "_intensity");
		singleTrapLights.layers[i].color = toRGBFloat(container->Get<sRGB>(prefix + "_color"));
		singleTrapLights.layers[i].gradientColor = toRGBFloat(container->Get<sRGB>(prefix + "_gradient_color"));
		singleTrapLights.layers[i].visibility = container->Get<double>(prefix + "_visibility");
		singleTrapLights.layers[i].maxDistance = container->Get<double>(prefix + "_max_distance");
		singleTrapLights.layers[i].sharpening = container->Get<double>(prefix + "_sharpening");
		singleTrapLights.layers[i].blur = container->Get<double>(prefix + "_blur");
		singleTrapLights.layers[i].solidIntensity = container->Get<double>(prefix + "_solid_intensity");
		singleTrapLights.layers[i].softness = container->Get<double>(prefix + "_softness");
		singleTrapLights.layers[i].relativeSize = container->Get<double>(prefix + "_relative_size");
		singleTrapLights.layers[i].preTransformed = container->Get<bool>(prefix + "_pre_transformed");
		singleTrapLights.layers[i].positionMode = container->Get<int>(prefix + "_position_mode");
		singleTrapLights.layers[i].coloringMode = params::enumSingleTrapLightColoringMode(
			container->Get<int>(prefix + "_coloring_mode"));
		singleTrapLights.layers[i].falloffType = params::enumSingleTrapLightFalloffType(
			container->Get<int>(prefix + "_falloff_type"));
		singleTrapLights.layers[i].edgeSoftness = container->Get<double>(prefix + "_edge_softness");
		singleTrapLights.layers[i].animOrbitRadius = container->Get<double>(prefix + "_anim_orbit_radius");
		singleTrapLights.layers[i].animOrbitSpeed = container->Get<double>(prefix + "_anim_orbit_speed");
		singleTrapLights.layers[i].animPulsateSpeed = container->Get<double>(prefix + "_anim_pulsate_speed");
		singleTrapLights.layers[i].animPulsateAmount = container->Get<double>(prefix + "_anim_pulsate_amount");
	}

	// Pattern line traps (world-space lines, explicit control)
	patternLineTraps.enabled = container->Get<bool>("pattern_line_traps_enabled");
	patternLineTraps.soloLayerIndex = container->Get<int>("pattern_line_trap_solo_layer");
	int cm = container->Get<int>("pattern_line_traps_combine_mode");
	if (cm < 0) cm = 0;
	if (cm > 1) cm = 1;
	patternLineTraps.combineMode = cm;
	int colm = container->Get<int>("pattern_line_traps_coloring_mode");
	if (colm < 0) colm = 0;
	if (colm > 2) colm = 2;
	patternLineTraps.coloringMode = colm;
	patternLineTraps.coloringSpeed = container->Get<double>("pattern_line_traps_coloring_speed");
	patternLineTraps.paletteOffset = container->Get<double>("pattern_line_traps_palette_offset");
	patternLineTraps.globalIntensity = container->Get<double>("pattern_line_traps_global_intensity");
	patternLineTraps.globalMaxDistance = container->Get<double>("pattern_line_traps_global_max_distance");
	patternLineTraps.globalScale = container->Get<double>("pattern_line_traps_global_scale");
	patternLineTraps.globalRelativeThickness = container->Get<double>("pattern_line_traps_global_relative_thickness");
	if (patternLineTraps.soloLayerIndex < 0) patternLineTraps.soloLayerIndex = 0;
	if (patternLineTraps.soloLayerIndex > PATTERN_LINE_TRAP_COUNT)
		patternLineTraps.soloLayerIndex = PATTERN_LINE_TRAP_COUNT;
	for (int i = 0; i < PATTERN_LINE_TRAP_COUNT; i++)
	{
		const QString p = QString("pattern_line_trap_%1").arg(i + 1);
		patternLineTraps.layers[i].enabled = container->Get<bool>(p + "_enabled");
		patternLineTraps.layers[i].position = container->Get<CVector3>(p + "_position");
		patternLineTraps.layers[i].rotation = container->Get<CVector3>(p + "_rotation");
		patternLineTraps.layers[i].UpdateRotationMatrix();
		patternLineTraps.layers[i].radius = container->Get<double>(p + "_radius");
		patternLineTraps.layers[i].thickness = container->Get<double>(p + "_thickness");
		patternLineTraps.layers[i].scale = container->Get<double>(p + "_scale");
		patternLineTraps.layers[i].relativeThickness = container->Get<double>(p + "_relative_thickness");
		patternLineTraps.layers[i].edgeSoftness = container->Get<double>(p + "_edge_softness");
		patternLineTraps.layers[i].intensity = container->Get<double>(p + "_intensity");
		patternLineTraps.layers[i].maxDistance = container->Get<double>(p + "_max_distance");
		patternLineTraps.layers[i].falloffSharpness = container->Get<double>(p + "_falloff_sharpness");
		patternLineTraps.layers[i].glowSpread = container->Get<double>(p + "_glow_spread");
		int fp = container->Get<int>(p + "_falloff_profile");
		if (fp < 0) fp = 0;
		if (fp > 3) fp = 3;
		patternLineTraps.layers[i].falloffProfile = fp;
		int esd = container->Get<int>(p + "_edge_side");
		if (esd < 0) esd = 0;
		if (esd > 2) esd = 2;
		patternLineTraps.layers[i].edgeSide = esd;
		patternLineTraps.layers[i].segmentHalfLength = container->Get<double>(p + "_segment_half_length");
		int sh = container->Get<int>(p + "_shape");
		if (sh < 0) sh = 0;
		if (sh > 49) sh = 49;
		patternLineTraps.layers[i].shape = sh;
		patternLineTraps.layers[i].shapeAux = container->Get<double>(p + "_shape_aux");
		patternLineTraps.layers[i].relativeSize = container->Get<double>(p + "_relative_size");
		patternLineTraps.layers[i].color = toRGBFloat(container->Get<sRGB>(p + "_color"));
		patternLineTraps.layers[i].color2 = toRGBFloat(container->Get<sRGB>(p + "_color_2"));
		patternLineTraps.layers[i].color3 = toRGBFloat(container->Get<sRGB>(p + "_color_3"));
	}

	// formula = Get<int>("tile_number");
}
