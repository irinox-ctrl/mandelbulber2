/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2017-23 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * opencl dynamic data for transferring to the worker device
 */

#include "opencl_dynamic_data.hpp"

#include <map>
#include <vector>

#include "color_gradient.h"
#include "fractparams.hpp"
#include "light.h"
#include "lights.hpp"
#include "material.h"
#include "opencl_textures_data.h"
#include "primitives.h"
#include "render_worker.hpp"

// custom includes
#ifdef USE_OPENCL
#include "opencl/material_cl.h"
#include "opencl/input_data_structures.h"
#include "opencl/primitives_cl.h"
#include "opencl/light_cl.h"
#endif

#ifdef USE_OPENCL
cOpenClDynamicData::cOpenClDynamicData(int numberOfItems)
		: cOpenClAbstractDynamicData(numberOfItems) // this container has 5
																								// items
{
}

cOpenClDynamicData::~cOpenClDynamicData() = default;

int cOpenClDynamicData::BuildMaterialsData(
	const std::map<int, cMaterial> &materials, const QMap<QString, int> &textureIndexes)
{
	/* material dynamic data structure

	header:
	cl_int numberOfMaterials

	materials offsets:
	cl_int material[0] offset
	cl_int material[1] offset
	...
	cl_int material[numberOfMaterials] offset

	---- material 0 ---
	+0	cl_int materialClOffset (offset for material data)
	+4	cl_int paletteItemsOffset
	+8	cl_int palette_offset_surface
	+12	cl_int paletteLengthSurface (number of surface color palette items)
	+16 cl_int palette offset specular
	+20 cl_int paletteLengthSpecular (number of specular color palette items)

	+24	sMaterialCl material

		palette items:
			cl_float3 color[0]
			cl_float3 color[1]
			...
			cl_float3 color[paletteLength]
	-------------------

	*/

	totalDataOffset += PutDummyToAlign(totalDataOffset, 16, &data);
	itemOffsets[materialsItemIndex].itemOffset = totalDataOffset;

	// number of materials is a maximum material index
	// Empty material indexes will be filled with zero data
	QList<int> keys;
	for (auto const &element : materials)
	{
		keys.push_back(element.first);
	}

	std::sort(keys.begin(), keys.end());
	cl_int numberOfMaterials = keys.last() + 1;

	// numberOfMaterials
	data.append(reinterpret_cast<char *>(&numberOfMaterials), sizeof(numberOfMaterials));
	int headerSize = sizeof(numberOfMaterials);
	totalDataOffset += headerSize;

	// reserve bytes for material offsets
	std::vector<cl_int> materialOffsets(numberOfMaterials);
	int materialOffsetsSize = sizeof(cl_int) * numberOfMaterials;
	std::fill(materialOffsets.begin(), materialOffsets.end(), 0);

	int materialOffsetsAddress = totalDataOffset;
	data.append(reinterpret_cast<char *>(materialOffsets.data()), materialOffsetsSize);
	totalDataOffset += materialOffsetsSize;

	// add dummy bytes for alignment to 16
	totalDataOffset += PutDummyToAlign(totalDataOffset, 16, &data);

	for (int materialIndex = 0; materialIndex < numberOfMaterials; materialIndex++)
	{
		sMaterialCl materialCl;
		std::vector<cl_float4> paletteCl;

		int totalSizeOfGradients = 0;
		cl_int paletteOffsetSurface;
		cl_int paletteSizeSurface;
		cl_int paletteOffsetSpecular;
		cl_int paletteSizeSpecular;
		cl_int paletteOffsetDiffuse;
		cl_int paletteSizeDiffuse;
		cl_int paletteOffsetLuminosity;
		cl_int paletteSizeLuminosity;
		cl_int paletteOffsetRoughness;
		cl_int paletteSizeRoughness;
		cl_int paletteOffsetReflectance;
		cl_int paletteSizeReflectance;
		cl_int paletteOffsetTransparency;
		cl_int paletteSizeTransparency;
		// Dummy opacity offsets (not yet implemented)
		cl_int opacityOffsetSurface = -1, opacitySizeSurface = 0;
		cl_int opacityOffsetSpecular = -1, opacitySizeSpecular = 0;
		cl_int opacityOffsetDiffuse = -1, opacitySizeDiffuse = 0;
		cl_int opacityOffsetLuminosity = -1, opacitySizeLuminosity = 0;
		cl_int opacityOffsetRoughness = -1, opacitySizeRoughness = 0;
		cl_int opacityOffsetReflectance = -1, opacitySizeReflectance = 0;
		cl_int opacityOffsetTransparency = -1, opacitySizeTransparency = 0;
		// Midpoint offsets
		cl_int midpointOffsetSurface;
		cl_int midpointSizeSurface;
		cl_int midpointOffsetSpecular;
		cl_int midpointSizeSpecular;
		cl_int midpointOffsetDiffuse;
		cl_int midpointSizeDiffuse;
		cl_int midpointOffsetLuminosity;
		cl_int midpointSizeLuminosity;
		cl_int midpointOffsetRoughness;
		cl_int midpointSizeRoughness;
		cl_int midpointOffsetReflectance;
		cl_int midpointSizeReflectance;
		cl_int midpointOffsetTransparency;
		cl_int midpointSizeTransparency;

		if (materials.find(materialIndex) != materials.end())
		{
			const cMaterial &material = materials.at(materialIndex);
			materialCl = clCopySMaterialCl(material);
			materialCl.surfaceGradientInterpolationMode = static_cast<cl_int>(material.gradientSurface.GetInterpolationMode());
			materialCl.surfaceGradientBlendMode = material.surfaceGradientBlendMode;

			QString textureName;

			textureName = material.colorTexture.GetFileName();
			materialCl.colorTextureIndex =
				textureIndexes.contains(textureName) ? textureIndexes[textureName] : -1;

			textureName = material.diffusionTexture.GetFileName();
			materialCl.diffusionTextureIndex =
				textureIndexes.contains(textureName) ? textureIndexes[textureName] : -1;

			textureName = material.luminosityTexture.GetFileName();
			materialCl.luminosityTextureIndex =
				textureIndexes.contains(textureName) ? textureIndexes[textureName] : -1;

			textureName = material.displacementTexture.GetFileName() + "grey16bit";
			materialCl.displacementTextureIndex =
				textureIndexes.contains(textureName) ? textureIndexes[textureName] : -1;

			textureName = material.normalMapTexture.GetFileName();
			materialCl.normalMapTextureIndex =
				textureIndexes.contains(textureName) ? textureIndexes[textureName] : -1;

			textureName = material.reflectanceTexture.GetFileName();
			materialCl.reflectanceTextureIndex =
				textureIndexes.contains(textureName) ? textureIndexes[textureName] : -1;

			textureName = material.transparencyTexture.GetFileName();
			materialCl.transparencyTextureIndex =
				textureIndexes.contains(textureName) ? textureIndexes[textureName] : -1;

			textureName = material.transparencyAlphaTexture.GetFileName();
			materialCl.transparencyAlphaTextureIndex =
				textureIndexes.contains(textureName) ? textureIndexes[textureName] : -1;

			textureName = material.roughnessTexture.GetFileName();
			materialCl.roughnessTextureIndex =
				textureIndexes.contains(textureName) ? textureIndexes[textureName] : -1;

			// gradients
			QList<cColorGradient::sColor> gradientSurface =
				material.gradientSurface.GetListOfSortedColors();
			QList<cColorGradient::sColor> gradientSpecular =
				material.gradientSpecular.GetListOfSortedColors();
			QList<cColorGradient::sColor> gradientDiffuse =
				material.gradientDiffuse.GetListOfSortedColors();
			QList<cColorGradient::sColor> gradientLuminosity =
				material.gradientLuminosity.GetListOfSortedColors();
			QList<cColorGradient::sColor> gradientRoughness =
				material.gradientRoughness.GetListOfSortedColors();
			QList<cColorGradient::sColor> gradientReflectance =
				material.gradientReflectance.GetListOfSortedColors();
			QList<cColorGradient::sColor> gradientTransparency =
				material.gradientTransparency.GetListOfSortedColors();

			paletteOffsetSurface = 0;
			paletteSizeSurface = gradientSurface.size();
			totalSizeOfGradients += paletteSizeSurface;

			paletteOffsetSpecular = paletteOffsetSurface + paletteSizeSurface;
			paletteSizeSpecular = gradientSpecular.size();
			totalSizeOfGradients += paletteSizeSpecular;

			paletteOffsetDiffuse = paletteOffsetSpecular + paletteSizeSpecular;
			paletteSizeDiffuse = gradientDiffuse.size();
			totalSizeOfGradients += paletteSizeDiffuse;

			paletteOffsetLuminosity = paletteOffsetDiffuse + paletteSizeDiffuse;
			paletteSizeLuminosity = gradientLuminosity.size();
			totalSizeOfGradients += paletteSizeLuminosity;

			paletteOffsetRoughness = paletteOffsetLuminosity + paletteSizeLuminosity;
			paletteSizeRoughness = gradientRoughness.size();
			totalSizeOfGradients += paletteSizeRoughness;

			paletteOffsetReflectance = paletteOffsetRoughness + paletteSizeRoughness;
			paletteSizeReflectance = gradientReflectance.size();
			totalSizeOfGradients += paletteSizeReflectance;

			paletteOffsetTransparency = paletteOffsetReflectance + paletteSizeReflectance;
			paletteSizeTransparency = gradientTransparency.size();
			totalSizeOfGradients += paletteSizeTransparency;

			paletteCl.resize(totalSizeOfGradients);

			for (int i = 0; i < paletteSizeSurface; i++)
			{
				paletteCl[i + paletteOffsetSurface] = toClFloat4(
					CVector4(gradientSurface[i].color.R / 256.0, gradientSurface[i].color.G / 256.0,
						gradientSurface[i].color.B / 256.0, gradientSurface[i].position));
			}

			for (int i = 0; i < paletteSizeSpecular; i++)
			{
				paletteCl[i + paletteOffsetSpecular] = toClFloat4(
					CVector4(gradientSpecular[i].color.R / 256.0, gradientSpecular[i].color.G / 256.0,
						gradientSpecular[i].color.B / 256.0, gradientSpecular[i].position));
			}

			for (int i = 0; i < paletteSizeDiffuse; i++)
			{
				paletteCl[i + paletteOffsetDiffuse] = toClFloat4(
					CVector4(gradientDiffuse[i].color.R / 256.0, gradientDiffuse[i].color.G / 256.0,
						gradientDiffuse[i].color.B / 256.0, gradientDiffuse[i].position));
			}

			for (int i = 0; i < paletteSizeLuminosity; i++)
			{
				paletteCl[i + paletteOffsetLuminosity] = toClFloat4(
					CVector4(gradientLuminosity[i].color.R / 256.0, gradientLuminosity[i].color.G / 256.0,
						gradientLuminosity[i].color.B / 256.0, gradientLuminosity[i].position));
			}

			for (int i = 0; i < paletteSizeRoughness; i++)
			{
				paletteCl[i + paletteOffsetRoughness] = toClFloat4(
					CVector4(gradientRoughness[i].color.R / 256.0, gradientRoughness[i].color.G / 256.0,
						gradientRoughness[i].color.B / 256.0, gradientRoughness[i].position));
			}

			for (int i = 0; i < paletteSizeReflectance; i++)
			{
				paletteCl[i + paletteOffsetReflectance] = toClFloat4(
					CVector4(gradientReflectance[i].color.R / 256.0, gradientReflectance[i].color.G / 256.0,
						gradientReflectance[i].color.B / 256.0, gradientReflectance[i].position));
			}

			for (int i = 0; i < paletteSizeTransparency; i++)
			{
				paletteCl[i + paletteOffsetTransparency] = toClFloat4(
					CVector4(gradientTransparency[i].color.R / 256.0, gradientTransparency[i].color.G / 256.0,
						gradientTransparency[i].color.B / 256.0, gradientTransparency[i].position));
			}

			// Midpoint data (one per segment)
			midpointOffsetSurface = totalSizeOfGradients;
			midpointSizeSurface = qMax(0, gradientSurface.size() - 1);
			totalSizeOfGradients += midpointSizeSurface;

			midpointOffsetSpecular = totalSizeOfGradients;
			midpointSizeSpecular = qMax(0, gradientSpecular.size() - 1);
			totalSizeOfGradients += midpointSizeSpecular;

			midpointOffsetDiffuse = totalSizeOfGradients;
			midpointSizeDiffuse = qMax(0, gradientDiffuse.size() - 1);
			totalSizeOfGradients += midpointSizeDiffuse;

			midpointOffsetLuminosity = totalSizeOfGradients;
			midpointSizeLuminosity = qMax(0, gradientLuminosity.size() - 1);
			totalSizeOfGradients += midpointSizeLuminosity;

			midpointOffsetRoughness = totalSizeOfGradients;
			midpointSizeRoughness = qMax(0, gradientRoughness.size() - 1);
			totalSizeOfGradients += midpointSizeRoughness;

			midpointOffsetReflectance = totalSizeOfGradients;
			midpointSizeReflectance = qMax(0, gradientReflectance.size() - 1);
			totalSizeOfGradients += midpointSizeReflectance;

			midpointOffsetTransparency = totalSizeOfGradients;
			midpointSizeTransparency = qMax(0, gradientTransparency.size() - 1);
			totalSizeOfGradients += midpointSizeTransparency;

			paletteCl.resize(totalSizeOfGradients);

			// Write midpoint values (x=midpoint, y=segmentMode, z=intensity, w=0)
			for (int i = 0; i < midpointSizeSurface; i++)
				paletteCl[midpointOffsetSurface + i] = toClFloat4(
					CVector4(material.gradientSurface.GetMidpoint(i),
						static_cast<float>(material.gradientSurface.GetSegmentMode(i)),
						material.gradientSurface.GetSegmentIntensity(i), material.gradientSurface.GetSegmentBias(i)));
			for (int i = 0; i < midpointSizeSpecular; i++)
				paletteCl[midpointOffsetSpecular + i] = toClFloat4(
					CVector4(material.gradientSpecular.GetMidpoint(i),
						static_cast<float>(material.gradientSpecular.GetSegmentMode(i)),
						material.gradientSpecular.GetSegmentIntensity(i), material.gradientSpecular.GetSegmentBias(i)));
			for (int i = 0; i < midpointSizeDiffuse; i++)
				paletteCl[midpointOffsetDiffuse + i] = toClFloat4(
					CVector4(material.gradientDiffuse.GetMidpoint(i),
						static_cast<float>(material.gradientDiffuse.GetSegmentMode(i)),
						material.gradientDiffuse.GetSegmentIntensity(i), material.gradientDiffuse.GetSegmentBias(i)));
			for (int i = 0; i < midpointSizeLuminosity; i++)
				paletteCl[midpointOffsetLuminosity + i] = toClFloat4(
					CVector4(material.gradientLuminosity.GetMidpoint(i),
						static_cast<float>(material.gradientLuminosity.GetSegmentMode(i)),
						material.gradientLuminosity.GetSegmentIntensity(i), material.gradientLuminosity.GetSegmentBias(i)));
			for (int i = 0; i < midpointSizeRoughness; i++)
				paletteCl[midpointOffsetRoughness + i] = toClFloat4(
					CVector4(material.gradientRoughness.GetMidpoint(i),
						static_cast<float>(material.gradientRoughness.GetSegmentMode(i)),
						material.gradientRoughness.GetSegmentIntensity(i), material.gradientRoughness.GetSegmentBias(i)));
			for (int i = 0; i < midpointSizeReflectance; i++)
				paletteCl[midpointOffsetReflectance + i] = toClFloat4(
					CVector4(material.gradientReflectance.GetMidpoint(i),
						static_cast<float>(material.gradientReflectance.GetSegmentMode(i)),
						material.gradientReflectance.GetSegmentIntensity(i), material.gradientReflectance.GetSegmentBias(i)));
			for (int i = 0; i < midpointSizeTransparency; i++)
				paletteCl[midpointOffsetTransparency + i] = toClFloat4(
					CVector4(material.gradientTransparency.GetMidpoint(i),
						static_cast<float>(material.gradientTransparency.GetSegmentMode(i)),
						material.gradientTransparency.GetSegmentIntensity(i), material.gradientTransparency.GetSegmentBias(i)));

			// Pack opacity data for ALL gradient types
			// Helper lambda: packs opacity stops + midpoints for a gradient
			auto packGradientOpacity = [&](const cColorGradient &grad,
				const QList<cColorGradient::sColor> &colorList,
				cl_int &opacityOffset, cl_int &opacitySize)
			{
				opacityOffset = totalSizeOfGradients;
				if (grad.HasSeparateOpacityStops())
				{
					auto opacityStops = grad.GetListOfSortedOpacityStops();
					opacitySize = opacityStops.size();
					totalSizeOfGradients += opacitySize;
					paletteCl.resize(totalSizeOfGradients);
					for (int i = 0; i < opacitySize; i++)
					{
						paletteCl[opacityOffset + i] = toClFloat4(
							CVector4(opacityStops[i].opacity, opacityStops[i].opacity,
								opacityStops[i].opacity, opacityStops[i].position));
					}
				}
				else
				{
					opacitySize = colorList.size();
					totalSizeOfGradients += opacitySize;
					paletteCl.resize(totalSizeOfGradients);
					for (int i = 0; i < opacitySize; i++)
					{
						paletteCl[opacityOffset + i] = toClFloat4(
							CVector4(colorList[i].opacity, colorList[i].opacity,
								colorList[i].opacity, colorList[i].position));
					}
				}
				// Midpoint data follows opacity stops
				int midpointCount = qMax(0, opacitySize - 1);
				if (midpointCount > 0)
				{
					totalSizeOfGradients += midpointCount;
					paletteCl.resize(totalSizeOfGradients);
					for (int i = 0; i < midpointCount; i++)
					{
						float mp;
						int modeVal;
						if (grad.HasSeparateOpacityStops())
						{
							mp = grad.GetOpacityMidpoint(i);
							modeVal = static_cast<int>(grad.GetOpacitySegmentMode(i));
						}
						else
						{
							mp = grad.GetMidpoint(i);
							modeVal = static_cast<int>(grad.GetSegmentMode(i));
						}
						paletteCl[opacityOffset + opacitySize + i] = toClFloat4(
							CVector4(mp, static_cast<float>(modeVal),
								grad.GetSegmentIntensity(i), grad.GetSegmentBias(i)));
					}
				}
			};

			packGradientOpacity(material.gradientSurface, gradientSurface,
				opacityOffsetSurface, opacitySizeSurface);
			packGradientOpacity(material.gradientSpecular, gradientSpecular,
				opacityOffsetSpecular, opacitySizeSpecular);
			packGradientOpacity(material.gradientDiffuse, gradientDiffuse,
				opacityOffsetDiffuse, opacitySizeDiffuse);
			packGradientOpacity(material.gradientLuminosity, gradientLuminosity,
				opacityOffsetLuminosity, opacitySizeLuminosity);
			packGradientOpacity(material.gradientRoughness, gradientRoughness,
				opacityOffsetRoughness, opacitySizeRoughness);
			packGradientOpacity(material.gradientReflectance, gradientReflectance,
				opacityOffsetReflectance, opacitySizeReflectance);
			packGradientOpacity(material.gradientTransparency, gradientTransparency,
				opacityOffsetTransparency, opacitySizeTransparency);
		}
		else
		{
			// fill not used material with dummy
			memset(&materialCl, 0, sizeof(materialCl));
			paletteOffsetSurface = 0;
			paletteSizeSurface = 2;
			paletteOffsetSpecular = 2;
			paletteSizeSpecular = 2;
			paletteOffsetDiffuse = 4;
			paletteSizeDiffuse = 2;
			paletteOffsetLuminosity = 6;
			paletteSizeLuminosity = 2;
			paletteOffsetRoughness = 8;
			paletteSizeRoughness = 2;
			paletteOffsetReflectance = 10;
			paletteSizeReflectance = 2;
			paletteOffsetTransparency = 12;
			paletteSizeTransparency = 2;
			// Initialize opacity and midpoint dummies for unused material
			opacityOffsetSurface = -1; opacitySizeSurface = 0;
			opacityOffsetSpecular = -1; opacitySizeSpecular = 0;
			opacityOffsetDiffuse = -1; opacitySizeDiffuse = 0;
			opacityOffsetLuminosity = -1; opacitySizeLuminosity = 0;
			opacityOffsetRoughness = -1; opacitySizeRoughness = 0;
			opacityOffsetReflectance = -1; opacitySizeReflectance = 0;
			opacityOffsetTransparency = -1; opacitySizeTransparency = 0;
			midpointOffsetSurface = -1; midpointSizeSurface = 0;
			midpointOffsetSpecular = -1; midpointSizeSpecular = 0;
			midpointOffsetDiffuse = -1; midpointSizeDiffuse = 0;
			midpointOffsetLuminosity = -1; midpointSizeLuminosity = 0;
			midpointOffsetRoughness = -1; midpointSizeRoughness = 0;
			midpointOffsetReflectance = -1; midpointSizeReflectance = 0;
			midpointOffsetTransparency = -1; midpointSizeTransparency = 0;
			paletteCl.resize(14);
			for (int i = 0; i < 14; i++)
			{
				paletteCl[i] = toClFloat4(CVector4());
			}
		}

		materialOffsets[materialIndex] = totalDataOffset;

		cl_int materialClOffset = 0;
		cl_int paletteItemsOffset = 0;

		// reserve bytes for cl_int materialClOffset
		int materialClOffsetAddress = totalDataOffset;
		data.append(reinterpret_cast<char *>(&materialClOffset), sizeof(materialClOffset));
		totalDataOffset += sizeof(materialClOffset);

		// reserve bytes cl_int paletteItemsOffset
		int paletteItemsOffsetAddress = totalDataOffset;
		data.append(reinterpret_cast<char *>(&paletteItemsOffset), sizeof(paletteItemsOffset));
		totalDataOffset += sizeof(paletteItemsOffset);

		// cl_int paletteOffsetSurface
		data.append(reinterpret_cast<char *>(&paletteOffsetSurface), sizeof(paletteOffsetSurface));
		totalDataOffset += sizeof(paletteOffsetSurface);

		// cl_int paletteSizeSurface
		data.append(reinterpret_cast<char *>(&paletteSizeSurface), sizeof(paletteSizeSurface));
		totalDataOffset += sizeof(paletteSizeSurface);

		// cl_int paletteOffsetSpecular
		data.append(reinterpret_cast<char *>(&paletteOffsetSpecular), sizeof(paletteOffsetSpecular));
		totalDataOffset += sizeof(paletteOffsetSpecular);

		// cl_int paletteSizeSpecular
		data.append(reinterpret_cast<char *>(&paletteSizeSpecular), sizeof(paletteSizeSpecular));
		totalDataOffset += sizeof(paletteSizeSpecular);

		// cl_int paletteOffsetDiffuse
		data.append(reinterpret_cast<char *>(&paletteOffsetDiffuse), sizeof(paletteOffsetDiffuse));
		totalDataOffset += sizeof(paletteOffsetDiffuse);

		// cl_int paletteSizeDiffuse
		data.append(reinterpret_cast<char *>(&paletteSizeDiffuse), sizeof(paletteSizeDiffuse));
		totalDataOffset += sizeof(paletteSizeDiffuse);

		// cl_int paletteOffsetLuminosity
		data.append(
			reinterpret_cast<char *>(&paletteOffsetLuminosity), sizeof(paletteOffsetLuminosity));
		totalDataOffset += sizeof(paletteOffsetLuminosity);

		// cl_int paletteSizeLuminosity
		data.append(reinterpret_cast<char *>(&paletteSizeLuminosity), sizeof(paletteSizeLuminosity));
		totalDataOffset += sizeof(paletteSizeLuminosity);

		// cl_int paletteOffsetRoughness
		data.append(reinterpret_cast<char *>(&paletteOffsetRoughness), sizeof(paletteOffsetRoughness));
		totalDataOffset += sizeof(paletteOffsetRoughness);

		// cl_int paletteSizeRoughness
		data.append(reinterpret_cast<char *>(&paletteSizeRoughness), sizeof(paletteSizeRoughness));
		totalDataOffset += sizeof(paletteSizeRoughness);

		// cl_int paletteOffsetReflectance
		data.append(
			reinterpret_cast<char *>(&paletteOffsetReflectance), sizeof(paletteOffsetReflectance));
		totalDataOffset += sizeof(paletteOffsetReflectance);

		// cl_int paletteSizeReflectance
		data.append(reinterpret_cast<char *>(&paletteSizeReflectance), sizeof(paletteSizeReflectance));
		totalDataOffset += sizeof(paletteSizeReflectance);

		// cl_int paletteOffsetTransparency
		data.append(
			reinterpret_cast<char *>(&paletteOffsetTransparency), sizeof(paletteOffsetTransparency));
		totalDataOffset += sizeof(paletteOffsetTransparency);

		// cl_int paletteSizeTransparency
		data.append(
			reinterpret_cast<char *>(&paletteSizeTransparency), sizeof(paletteSizeTransparency));
		totalDataOffset += sizeof(paletteSizeTransparency);

		// Dummy opacity offsets (for engine compatibility)
		data.append(reinterpret_cast<char *>(&opacityOffsetSurface), sizeof(opacityOffsetSurface));
		totalDataOffset += sizeof(opacityOffsetSurface);
		data.append(reinterpret_cast<char *>(&opacitySizeSurface), sizeof(opacitySizeSurface));
		totalDataOffset += sizeof(opacitySizeSurface);
		data.append(reinterpret_cast<char *>(&opacityOffsetSpecular), sizeof(opacityOffsetSpecular));
		totalDataOffset += sizeof(opacityOffsetSpecular);
		data.append(reinterpret_cast<char *>(&opacitySizeSpecular), sizeof(opacitySizeSpecular));
		totalDataOffset += sizeof(opacitySizeSpecular);
		data.append(reinterpret_cast<char *>(&opacityOffsetDiffuse), sizeof(opacityOffsetDiffuse));
		totalDataOffset += sizeof(opacityOffsetDiffuse);
		data.append(reinterpret_cast<char *>(&opacitySizeDiffuse), sizeof(opacitySizeDiffuse));
		totalDataOffset += sizeof(opacitySizeDiffuse);
		data.append(reinterpret_cast<char *>(&opacityOffsetLuminosity), sizeof(opacityOffsetLuminosity));
		totalDataOffset += sizeof(opacityOffsetLuminosity);
		data.append(reinterpret_cast<char *>(&opacitySizeLuminosity), sizeof(opacitySizeLuminosity));
		totalDataOffset += sizeof(opacitySizeLuminosity);
		data.append(reinterpret_cast<char *>(&opacityOffsetRoughness), sizeof(opacityOffsetRoughness));
		totalDataOffset += sizeof(opacityOffsetRoughness);
		data.append(reinterpret_cast<char *>(&opacitySizeRoughness), sizeof(opacitySizeRoughness));
		totalDataOffset += sizeof(opacitySizeRoughness);
		data.append(reinterpret_cast<char *>(&opacityOffsetReflectance), sizeof(opacityOffsetReflectance));
		totalDataOffset += sizeof(opacityOffsetReflectance);
		data.append(reinterpret_cast<char *>(&opacitySizeReflectance), sizeof(opacitySizeReflectance));
		totalDataOffset += sizeof(opacitySizeReflectance);
		data.append(reinterpret_cast<char *>(&opacityOffsetTransparency), sizeof(opacityOffsetTransparency));
		totalDataOffset += sizeof(opacityOffsetTransparency);
		data.append(reinterpret_cast<char *>(&opacitySizeTransparency), sizeof(opacitySizeTransparency));
		totalDataOffset += sizeof(opacitySizeTransparency);

		// Midpoint offsets
		data.append(reinterpret_cast<char *>(&midpointOffsetSurface), sizeof(midpointOffsetSurface));
		totalDataOffset += sizeof(midpointOffsetSurface);
		data.append(reinterpret_cast<char *>(&midpointSizeSurface), sizeof(midpointSizeSurface));
		totalDataOffset += sizeof(midpointSizeSurface);
		data.append(reinterpret_cast<char *>(&midpointOffsetSpecular), sizeof(midpointOffsetSpecular));
		totalDataOffset += sizeof(midpointOffsetSpecular);
		data.append(reinterpret_cast<char *>(&midpointSizeSpecular), sizeof(midpointSizeSpecular));
		totalDataOffset += sizeof(midpointSizeSpecular);
		data.append(reinterpret_cast<char *>(&midpointOffsetDiffuse), sizeof(midpointOffsetDiffuse));
		totalDataOffset += sizeof(midpointOffsetDiffuse);
		data.append(reinterpret_cast<char *>(&midpointSizeDiffuse), sizeof(midpointSizeDiffuse));
		totalDataOffset += sizeof(midpointSizeDiffuse);
		data.append(reinterpret_cast<char *>(&midpointOffsetLuminosity), sizeof(midpointOffsetLuminosity));
		totalDataOffset += sizeof(midpointOffsetLuminosity);
		data.append(reinterpret_cast<char *>(&midpointSizeLuminosity), sizeof(midpointSizeLuminosity));
		totalDataOffset += sizeof(midpointSizeLuminosity);
		data.append(reinterpret_cast<char *>(&midpointOffsetRoughness), sizeof(midpointOffsetRoughness));
		totalDataOffset += sizeof(midpointOffsetRoughness);
		data.append(reinterpret_cast<char *>(&midpointSizeRoughness), sizeof(midpointSizeRoughness));
		totalDataOffset += sizeof(midpointSizeRoughness);
		data.append(reinterpret_cast<char *>(&midpointOffsetReflectance), sizeof(midpointOffsetReflectance));
		totalDataOffset += sizeof(midpointOffsetReflectance);
		data.append(reinterpret_cast<char *>(&midpointSizeReflectance), sizeof(midpointSizeReflectance));
		totalDataOffset += sizeof(midpointSizeReflectance);
		data.append(reinterpret_cast<char *>(&midpointOffsetTransparency), sizeof(midpointOffsetTransparency));
		totalDataOffset += sizeof(midpointOffsetTransparency);
		data.append(reinterpret_cast<char *>(&midpointSizeTransparency), sizeof(midpointSizeTransparency));
		totalDataOffset += sizeof(midpointSizeTransparency);

		// add dummy bytes for alignment to 16
		totalDataOffset += PutDummyToAlign(totalDataOffset, 16, &data);

		// sMaterialCl material
		materialClOffset = totalDataOffset;
		data.append(reinterpret_cast<char *>(&materialCl), sizeof(materialCl));
		totalDataOffset += sizeof(materialCl);

		// fill materialClOffset value
		data.replace(materialClOffsetAddress, sizeof(materialClOffset),
			reinterpret_cast<char *>(&materialClOffset), sizeof(materialClOffset));

		// add dummy bytes for alignment to 16
		totalDataOffset += PutDummyToAlign(totalDataOffset, 16, &data);

		// palette data
		paletteItemsOffset = totalDataOffset;
		int paletteSizeBytes = totalSizeOfGradients * sizeof(cl_float4);
		data.append(reinterpret_cast<char *>(paletteCl.data()), paletteSizeBytes);
		totalDataOffset += paletteSizeBytes;

		// fill paletteItemsOffset value
		data.replace(paletteItemsOffsetAddress, sizeof(paletteItemsOffset),
			reinterpret_cast<char *>(&paletteItemsOffset), sizeof(paletteItemsOffset));
	}

	// fill materials offsets:
	data.replace(materialOffsetsAddress, materialOffsetsSize,
		reinterpret_cast<char *>(materialOffsets.data()), materialOffsetsSize);

	return numberOfMaterials;
}

void cOpenClDynamicData::BuildAOVectorsData(const sVectorsAround *AOVectors, cl_int vectorsCount)
{
	/* use __attribute__((aligned(16))) in kernel code for array
	 *
	 * header:
	 * cl_int vectorsCount
	 * cl_int arrayOffset;
	 *
	 * array (aligned to 16):
	 * 	sVectorsAroundCl item1
	 * 	sVectorsAroundCl item2
	 * 	...
	 *	sVectorsAroundCl itemN
	 */

	totalDataOffset += PutDummyToAlign(totalDataOffset, 16, &data);
	itemOffsets[AOVectorsItemIndex].itemOffset = totalDataOffset;

	data.append(reinterpret_cast<char *>(&vectorsCount), sizeof(vectorsCount));
	totalDataOffset += sizeof(vectorsCount);

	// reserve bytes for array offset
	cl_int arrayOffset = 0;
	int arrayOffsetAddress = totalDataOffset;
	data.append(reinterpret_cast<char *>(&arrayOffset), sizeof(arrayOffset));
	totalDataOffset += sizeof(arrayOffset);

	// copy AO vectors aligned to 16
	for (int i = 0; i < vectorsCount; i++)
	{
		totalDataOffset += PutDummyToAlign(totalDataOffset, 16, &data);
		if (i == 0) arrayOffset = totalDataOffset;

		sVectorsAroundCl vector;
		vector.v = toClFloat3(AOVectors[i].v);
		vector.color = toClFloat3(AOVectors[i].color);

		data.append(reinterpret_cast<char *>(&vector), sizeof(vector));
		totalDataOffset += sizeof(vector);
	}

	// replace arrayOffset:
	data.replace(arrayOffsetAddress, sizeof(arrayOffset), reinterpret_cast<char *>(&arrayOffset),
		sizeof(arrayOffset));
}

void cOpenClDynamicData::BuildLightsData(
	const cLights *lights, const QMap<QString, int> &textureIndexes)
{
	/* use __attribute__((aligned(16))) in kernel code for array
	 *
	 * header:
	 * cl_int numberOfLights
	 * cl_int arrayOffset;
	 *
	 * array (aligned to 16):
	 * 	sLightCl light1
	 * 	sLightCl light1
	 *  ...
	 * 	sLightCl lightN
	 */

	totalDataOffset += PutDummyToAlign(totalDataOffset, 16, &data);
	itemOffsets[lightsItemIndex].itemOffset = totalDataOffset;

	cl_int numberOfLights = lights->GetNumberOfLights();
	data.append(reinterpret_cast<char *>(&numberOfLights), sizeof(numberOfLights));
	totalDataOffset += sizeof(numberOfLights);

	// reserve bytes for array offset
	cl_int arrayOffset = 0;
	int arrayOffsetAddress = totalDataOffset;
	data.append(reinterpret_cast<char *>(&arrayOffset), sizeof(arrayOffset));
	totalDataOffset += sizeof(arrayOffset);

	// copy lights aligned to 16
	for (int i = 0; i < numberOfLights; i++)
	{
		// align struct to 16
		totalDataOffset += PutDummyToAlign(totalDataOffset, 16, &data);
		if (i == 0) arrayOffset = totalDataOffset;

		sLightCl lightCl;
		const cLight *light = lights->GetLight(i);

		lightCl.enabled = light->enabled;
		lightCl.castShadows = light->castShadows;
		lightCl.penetrating = light->penetrating;
		lightCl.relativePosition = light->relativePosition;
		lightCl.repeatTexture = light->repeatTexture;
		lightCl.volumetric = light->volumetric;

		lightCl.coneAngle = light->coneAngle;
		lightCl.coneSoftAngle = light->coneSoftAngle;
		lightCl.intensity = light->intensity;
		lightCl.visibility = light->visibility;
		lightCl.volumetricVisibility = light->volumetricVisibility;
		lightCl.size = light->size;
		lightCl.softShadowCone = light->softShadowCone;
		lightCl.contourSharpness = light->contourSharpness;
		lightCl.beamRadius = light->beamRadius;
		lightCl.beamSoftEdge = light->beamSoftEdge;
		lightCl.beamFadeIn = light->beamFadeIn;
		lightCl.beamFadeOut = light->beamFadeOut;
		lightCl.coneRatio = light->coneRatio;
		lightCl.coneSoftRatio = light->coneSoftRatio;
		lightCl.projectionHorizontalRatio = light->projectionHorizontalRatio;
		lightCl.projectionVerticalRatio = light->projectionVerticalRatio;
		lightCl.projectionSoftEdge = light->projectionSoftEdge;
		lightCl.projectionIntensity = light->projectionIntensity;
		lightCl.projectionUseAsMask = light->projectionUseAsMask;
		lightCl.projectionInvertAlphaMask = light->projectionInvertAlphaMask;
		lightCl.projectionBlendMode = light->projectionBlendMode;

		lightCl.position = toClFloat3(light->position);
		lightCl.rotation = toClFloat3(light->rotation);
		lightCl.target = toClFloat3(light->target);
		lightCl.lightDirection = toClFloat3(light->lightDirection);
		lightCl.lightTopVector = toClFloat3(light->lightTopVector);
		lightCl.lightRightVector = toClFloat3(light->lightRightVector);

		lightCl.color = toClFloat3(light->color);

		lightCl.rotMatrix = toClMatrix33(light->rotMatrix);

		lightCl.projectionParams1 = {{
			cl_float(light->projectionTextureOffsetX),
			cl_float(light->projectionTextureOffsetY),
			cl_float(light->projectionTextureScaleX),
			cl_float(light->projectionTextureScaleY)}};
		lightCl.projectionParams2 = {{
			cl_float(light->projectionTextureRotationZ),
			cl_float(light->projectionRepeatMode),
			cl_float(light->projectionUseAlphaAsMask ? 1.0f : 0.0f),
			cl_float(light->projectionUseTextureAlphaAsMask ? 1.0f : 0.0f)}};
		lightCl.projectionParams3 = {{
			cl_float(light->projectionTextureOffsetZ),
			cl_float(light->projectionTextureScaleZ),
			cl_float(light->projectionTextureRotationX),
			cl_float(light->projectionTextureRotationY)}};

		lightCl.alphaTextureParams1 = {{
			cl_float(light->alphaTextureOffsetX),
			cl_float(light->alphaTextureOffsetY),
			cl_float(light->alphaTextureScaleX),
			cl_float(light->alphaTextureScaleY)}};
		lightCl.alphaTextureParams2 = {{
			cl_float(light->alphaTextureRotationZ),
			cl_float(light->alphaTextureRepeatMode),
			cl_float(light->alphaTextureSoftEdge),
			0.0f}};

		lightCl.type = static_cast<enumLightTypeCl>(light->type);
		lightCl.decayFunction = static_cast<enumLightDecayFunctionCl>(light->decayFunction);

		QString textureName = light->colorTexture.GetFileName();
		lightCl.colorTextureIndex =
			textureIndexes.contains(textureName) ? textureIndexes[textureName] : -1;

		textureName = light->alphaTexture.GetFileName();
		lightCl.alphaTextureIndex =
			textureIndexes.contains(textureName) ? textureIndexes[textureName] : -1;

		textureName = light->sphericalTexture.GetFileName();
		lightCl.sphericalTextureIndex =
			textureIndexes.contains(textureName) ? textureIndexes[textureName] : -1;
		lightCl.sphericalTextureIntensity = light->sphericalTextureIntensity;

		data.append(reinterpret_cast<char *>(&lightCl), sizeof(lightCl));
		totalDataOffset += sizeof(lightCl);
	}

	// replace arrayOffset:
	data.replace(arrayOffsetAddress, sizeof(arrayOffset), reinterpret_cast<char *>(&arrayOffset),
		sizeof(arrayOffset));
}

QString cOpenClDynamicData::BuildPrimitivesData(const cPrimitives *primitivesContainer)
{
	/* use __attribute__((aligned(16))) in kernel code for array
	 *
	 * header:
	 * cl_int numberOfPrimitives
	 * cl_int globalPositionOffset
	 * cl_int arrayOffset;
	 *
	 * sPrimitiveGlobalPositionCl (aligned to 16)
	 *
	 * array (aligned to 16):
	 * 	sPrimitiveCl primitive1
	 * 	sPrimitiveCl primitive2
	 *  ...
	 * 	sPrimitiveCl primitiveN
	 */

	totalDataOffset += PutDummyToAlign(totalDataOffset, 16, &data);
	itemOffsets[primitivesItemIndex].itemOffset = totalDataOffset;

	cl_int numberOfPrimitives = primitivesContainer->GetNumberOfPrimivives();
	data.append(reinterpret_cast<char *>(&numberOfPrimitives), sizeof(numberOfPrimitives));
	totalDataOffset += sizeof(numberOfPrimitives);

	// reserve bytes for sPrimitiveGlobalPosition offset
	cl_int globalPositionOffset = 0;
	int globalPositionOffsetAddress = totalDataOffset;
	data.append(reinterpret_cast<char *>(&globalPositionOffset), sizeof(globalPositionOffset));
	totalDataOffset += sizeof(globalPositionOffset);

	// reserve bytes for array offset
	cl_int arrayOffset = 0;
	int arrayOffsetAddress = totalDataOffset;
	data.append(reinterpret_cast<char *>(&arrayOffset), sizeof(arrayOffset));
	totalDataOffset += sizeof(arrayOffset);

	totalDataOffset += PutDummyToAlign(totalDataOffset, 16, &data);
	globalPositionOffset = totalDataOffset;
	sPrimitiveGlobalDataCl globalData;
	globalData.allPrimitivesPosition = toClFloat3(primitivesContainer->allPrimitivesPosition);
	globalData.allPrimitivesRotation = toClFloat3(primitivesContainer->allPrimitivesRotation);
	globalData.mRotAllPrimitivesRotation =
		toClMatrix33(primitivesContainer->mRotAllPrimitivesRotation);
	globalData.primitiveIndexForBasicFog = primitivesContainer->primitiveIndexForBasicFog;
	globalData.primitiveIndexForDistFog = primitivesContainer->primitiveIndexForDistFog;
	globalData.primitiveIndexForIterFog = primitivesContainer->primitiveIndexForIterFog;
	globalData.primitiveIndexForClouds = primitivesContainer->primitiveIndexForClouds;
	data.append(reinterpret_cast<char *>(&globalData), sizeof(globalData));
	totalDataOffset += sizeof(globalData);
	data.replace(globalPositionOffsetAddress, sizeof(globalPositionOffset),
		reinterpret_cast<char *>(&globalPositionOffset), sizeof(globalPositionOffset));

	bool usePrimitivePlane = false;
	bool usePrimitiveBox = false;
	bool usePrimitiveSphere = false;
	bool usePrimitiveRectangle = false;
	bool usePrimitiveCylinder = false;
	bool usePrimitiveCircle = false;
	bool usePrimitiveCone = false;
	bool usePrimitiveWater = false;
	bool usePrimitiveTorus = false;
	bool usePrimitivePrism = false;
	bool usePrimitiveEllipsoid = false;
	bool usePrimitiveCapsule = false;
	bool usePrimitiveHexPrism = false;
	bool usePrimitiveLavaPlane = false;
	bool usePrimitiveOctahedron = false;
	bool usePrimitivePyramid = false;
	bool usePrimitiveTerrainPlane = false;

	// copy primitives data aligned to 16
	for (int i = 0; i < numberOfPrimitives; i++)
	{
		// align struct to 16
		totalDataOffset += PutDummyToAlign(totalDataOffset, 16, &data);

		if (i == 0) arrayOffset = totalDataOffset;

		sPrimitiveCl primitiveCl;
			memset(&primitiveCl, 0, sizeof(primitiveCl));
		const std::shared_ptr<sPrimitiveBasic> primitive = primitivesContainer->GetPrimitive(i);

		primitiveCl.object.enable = primitive->enable;
		primitiveCl.object.materialId = primitive->materialId;
		primitiveCl.object.objectId = primitive->objectId;
		primitiveCl.object.objectType = static_cast<enumObjectTypeCl>(primitive->objectType);
		primitiveCl.object.position = toClFloat3(primitive->position);
		primitiveCl.object.rotationMatrix = toClMatrix33(primitive->rotationMatrix);
		primitiveCl.object.size = toClFloat3(primitive->size);
		primitiveCl.object.primitiveScale = toClFloat3(primitive->primitiveScale);
		primitiveCl.object.repeat = toClFloat3(primitive->repeat);
		primitiveCl.object.smoothDeCombineEnable = primitive->smoothDeCombineEnable;
		primitiveCl.object.smoothDeCombineDistance = primitive->smoothDeCombineDistance;
		primitiveCl.booleanOperator =
			static_cast<enumClPrimitiveBooleanOperator>(primitive->booleanOperator);
		primitiveCl.object.usedForVolumetric = primitive->usedForVolumetric;
		primitiveCl.object.wallThickness = primitive->wallThickness;

		// Pivot
		primitiveCl.object.pivot = toClFloat3(primitive->pivot);
		primitiveCl.object.useWorldSpacePivot = primitive->useWorldSpacePivot;

		// Cloner
		primitiveCl.object.clonerEnabled = primitive->cloner.enabled;
		primitiveCl.object.clonerMode = static_cast<cl_int>(primitive->cloner.mode);
		primitiveCl.object.clonerCount = primitive->cloner.count;
		primitiveCl.object.clonerOffset = toClFloat3(primitive->cloner.offset);
		primitiveCl.object.clonerRadius = primitive->cloner.radius;
		primitiveCl.object.clonerStartAngle = primitive->cloner.startAngle;
		primitiveCl.object.clonerEndAngle = primitive->cloner.endAngle;
		primitiveCl.object.clonerPlane = primitive->cloner.plane;
		primitiveCl.object.clonerGridCount = toClFloat3(primitive->cloner.gridCount);
		primitiveCl.object.clonerGridSize = toClFloat3(primitive->cloner.gridSize);
		primitiveCl.object.clonerSpiralHeight = primitive->cloner.spiralHeight;
		primitiveCl.object.clonerSpiralTurns = primitive->cloner.spiralTurns;
		primitiveCl.object.clonerRandomSeed = primitive->cloner.randomSeed;
		primitiveCl.object.clonerRandomBounds = toClFloat3(primitive->cloner.randomBounds);
		primitiveCl.object.clonerHoneycombSpacing = primitive->cloner.honeycombSpacing;

		// Advanced Repeat
		primitiveCl.object.repeatMode = primitive->repeatMode;
		primitiveCl.object.repeatRotationStep = primitive->repeatRotationStep;
		primitiveCl.object.repeatFibonacciCount = primitive->repeatFibonacciCount;
		primitiveCl.object.repeatFibonacciSpread = primitive->repeatFibonacciSpread;
		primitiveCl.object.repeatSpiralStep = toClFloat3(primitive->repeatSpiralStep);
		primitiveCl.object.repeatSpiralAngle = toClFloat3(primitive->repeatSpiralAngle);
		primitiveCl.object.repeatSpiralRadius = toClFloat3(primitive->repeatSpiralRadius);
		primitiveCl.object.repeatWaveAmplitude = toClFloat3(primitive->repeatWaveAmplitude);
		primitiveCl.object.repeatWaveFrequency = toClFloat3(primitive->repeatWaveFrequency);
		primitiveCl.object.repeatWavePhase = toClFloat3(primitive->repeatWavePhase);
		primitiveCl.object.repeatWaveAxis = primitive->repeatWaveAxis;

		// Mirror
		primitiveCl.object.mirrorX = primitive->mirrorX;
		primitiveCl.object.mirrorY = primitive->mirrorY;
		primitiveCl.object.mirrorZ = primitive->mirrorZ;

		// Groups & Boolean targeting
		primitiveCl.object.groupId = primitive->groupId;
		primitiveCl.object.groupEnabled = primitive->groupEnabled;
		primitiveCl.object.groupBooleanOperator = primitive->groupBooleanOperator;
		primitiveCl.object.groupSmoothRadius = primitive->groupSmoothRadius;
		primitiveCl.object.groupPriority = primitive->groupPriority;
		primitiveCl.object.booleanTargetGroupId = primitive->booleanTargetGroupId;

		// Deformers
		primitiveCl.object.deformBendEnable = primitive->deformBendEnable;
		primitiveCl.object.deformBendAngle = primitive->deformBendAngle;
		primitiveCl.object.deformBendAxis = primitive->deformBendAxis;
		primitiveCl.object.deformTwistEnable = primitive->deformTwistEnable;
		primitiveCl.object.deformTwistAngle = primitive->deformTwistAngle;
		primitiveCl.object.deformTwistAxis = primitive->deformTwistAxis;
		primitiveCl.object.deformTaperEnable = primitive->deformTaperEnable;
		primitiveCl.object.deformTaperRate = primitive->deformTaperRate;
		primitiveCl.object.deformTaperAxis = primitive->deformTaperAxis;

		// Effectors (MoGraph)
		for (int ei = 0; ei < 4; ei++)
		{
			if (primitive->effectors[ei] && primitive->effectors[ei]->enabled)
			{
				auto *eff = primitive->effectors[ei].get();
				primitiveCl.effectors[ei].mode = static_cast<cl_int>(eff->mode);
				primitiveCl.effectors[ei].strength = eff->strength;

				auto *re = dynamic_cast<sPrimitiveBasic::RandomEffector *>(eff);
				auto *se = dynamic_cast<sPrimitiveBasic::StepEffector *>(eff);
				auto *fe = dynamic_cast<sPrimitiveBasic::FormulaEffector *>(eff);
				auto *te = dynamic_cast<sPrimitiveBasic::TimeEffector *>(eff);

				if (re)
				{
					primitiveCl.effectors[ei].type = 1;
					primitiveCl.effectors[ei].seed = re->seed;
					primitiveCl.effectors[ei].posAmp = toClFloat3(re->positionAmp);
					primitiveCl.effectors[ei].rotAmp = toClFloat3(re->rotationAmp);
					primitiveCl.effectors[ei].scaleAmp = toClFloat3(re->scaleAmp);
				}
				else if (se)
				{
					primitiveCl.effectors[ei].type = 2;
					primitiveCl.effectors[ei].posAmp = toClFloat3(se->positionStep);
					primitiveCl.effectors[ei].rotAmp = toClFloat3(se->rotationStep);
					primitiveCl.effectors[ei].scaleAmp = toClFloat3(se->scaleStep);
				}
				else if (fe)
				{
					primitiveCl.effectors[ei].type = 3;
					primitiveCl.effectors[ei].formulaPreset = fe->formulaPreset;
				}
				else if (te)
				{
					primitiveCl.effectors[ei].type = 4;
					primitiveCl.effectors[ei].timeOffset = te->timeOffset;
					primitiveCl.effectors[ei].timeScale = te->timeScale;
				}
			}
		}

		try
		{
			switch (primitive->objectType)
			{
				case fractal::objPlane:
				{
					const sPrimitivePlane *plane = dynamic_cast<const sPrimitivePlane *>(primitive.get());
					if (plane)
					{
						primitiveCl.data.plane.empty = plane->empty;
						usePrimitivePlane = true;
					}
					else
						throw QString("sPrimitivePlane");
					break;
				}

				case fractal::objBox:
				{
					const sPrimitiveBox *box = dynamic_cast<const sPrimitiveBox *>(primitive.get());
					if (box)
					{
						primitiveCl.data.box.empty = box->empty;
						primitiveCl.data.box.rounding = box->rounding;
						primitiveCl.data.box.repeat = toClFloat3(box->repeat);
						primitiveCl.data.box.limitsEnable = box->limitsEnable;
						primitiveCl.data.box.limitsMax = toClFloat3(box->limitsMax);
						primitiveCl.data.box.limitsMin = toClFloat3(box->limitsMin);
						usePrimitiveBox = true;
					}
					else
						throw QString("sPrimitivePlane");
					break;
				}

				case fractal::objSphere:
				{
					const sPrimitiveSphere *sphere = dynamic_cast<const sPrimitiveSphere *>(primitive.get());
					if (sphere)
					{
						primitiveCl.data.sphere.empty = sphere->empty;
						primitiveCl.data.sphere.radius = sphere->radius;
						primitiveCl.data.sphere.repeat = toClFloat3(sphere->repeat);
						primitiveCl.data.sphere.limitsEnable = sphere->limitsEnable;
						primitiveCl.data.sphere.limitsMax = toClFloat3(sphere->limitsMax);
						primitiveCl.data.sphere.limitsMin = toClFloat3(sphere->limitsMin);
						usePrimitiveSphere = true;
					}
					else
						throw QString("sPrimitiveSphere");
					break;
				}

				case fractal::objWater:
				{
					const sPrimitiveWater *water = dynamic_cast<const sPrimitiveWater *>(primitive.get());
					if (water)
					{
						primitiveCl.data.water.empty = water->empty;
						primitiveCl.data.water.waveFromObjectsEnable = water->waveFromObjectsEnable;
						primitiveCl.data.water.relativeAmplitude = water->relativeAmplitude;
						primitiveCl.data.water.animSpeed = water->animSpeed;
						primitiveCl.data.water.animProgressionSpeed = water->animProgressionSpeed;
						primitiveCl.data.water.length = water->length;
						primitiveCl.data.water.waveFromObjectsRelativeAmplitude =
							water->waveFromObjectsRelativeAmplitude;
						primitiveCl.data.water.iterations = water->iterations;
						primitiveCl.data.water.animFrame = water->animFrame;
						primitiveCl.data.water.limitsEnable = water->limitsEnable;
						primitiveCl.data.water.limitsMax = toClFloat3(water->limitsMax);
						primitiveCl.data.water.limitsMin = toClFloat3(water->limitsMin);
						usePrimitiveWater = true;
					}
					else
						throw QString("sPrimitiveWater");
					break;
				}

				case fractal::objCone:
				{
					const sPrimitiveCone *cone = dynamic_cast<const sPrimitiveCone *>(primitive.get());
					if (cone)
					{
						primitiveCl.data.cone.empty = cone->empty;
						primitiveCl.data.cone.caps = cone->caps;
						primitiveCl.data.cone.radius = cone->radius;
						primitiveCl.data.cone.height = cone->height;
						primitiveCl.data.cone.wallNormal = toClFloat2(cone->wallNormal);
						primitiveCl.data.cone.repeat = toClFloat3(cone->repeat);
						primitiveCl.data.cone.limitsEnable = cone->limitsEnable;
						primitiveCl.data.cone.limitsMax = toClFloat3(cone->limitsMax);
						primitiveCl.data.cone.limitsMin = toClFloat3(cone->limitsMin);
						usePrimitiveCone = true;
					}
					else
						throw QString("sPrimitiveCone");
					break;
				}

				case fractal::objCylinder:
				{
					const sPrimitiveCylinder *cylinder =
						dynamic_cast<const sPrimitiveCylinder *>(primitive.get());
					if (cylinder)
					{
						primitiveCl.data.cylinder.empty = cylinder->empty;
						primitiveCl.data.cylinder.caps = cylinder->caps;
						primitiveCl.data.cylinder.radius = cylinder->radius;
						primitiveCl.data.cylinder.height = cylinder->height;
						primitiveCl.data.cylinder.repeat = toClFloat3(cylinder->repeat);
						primitiveCl.data.cylinder.limitsEnable = cylinder->limitsEnable;
						primitiveCl.data.cylinder.limitsMax = toClFloat3(cylinder->limitsMax);
						primitiveCl.data.cylinder.limitsMin = toClFloat3(cylinder->limitsMin);
						usePrimitiveCylinder = true;
					}
					else
						throw QString("sPrimitiveCylinder");
					break;
				}

				case fractal::objTorus:
				{
					const sPrimitiveTorus *torus = dynamic_cast<const sPrimitiveTorus *>(primitive.get());
					if (torus)
					{
						primitiveCl.data.torus.empty = torus->empty;
						primitiveCl.data.torus.radius = torus->radius;
						primitiveCl.data.torus.radiusLPow = torus->radiusLPow;
						primitiveCl.data.torus.tubeRadius = torus->tubeRadius;
						primitiveCl.data.torus.tubeRadiusLPow = torus->tubeRadiusLPow;
						primitiveCl.data.torus.repeat = toClFloat3(torus->repeat);
						primitiveCl.data.torus.limitsEnable = torus->limitsEnable;
						primitiveCl.data.torus.limitsMax = toClFloat3(torus->limitsMax);
						primitiveCl.data.torus.limitsMin = toClFloat3(torus->limitsMin);
						usePrimitiveTorus = true;
					}
					else
						throw QString("sPrimitiveTorus");
					break;
				}

				case fractal::objCircle:
				{
					const sPrimitiveCircle *circle = dynamic_cast<const sPrimitiveCircle *>(primitive.get());
					if (circle)
					{
						primitiveCl.data.circle.radius = circle->radius;
						usePrimitiveCircle = true;
					}
					else
						throw QString("sPrimitiveCircle");
					break;
				}

				case fractal::objRectangle:
				{
					const sPrimitiveRectangle *rectangle =
						dynamic_cast<const sPrimitiveRectangle *>(primitive.get());
					if (rectangle)
					{
						primitiveCl.data.rectangle.height = rectangle->height;
						primitiveCl.data.rectangle.width = rectangle->width;
						usePrimitiveRectangle = true;
					}
					else
						throw QString("sPrimitiveRectangle");
					break;
				}

				case fractal::objPrism:
				{
					const sPrimitivePrism *prism = dynamic_cast<const sPrimitivePrism *>(primitive.get());
					if (prism)
					{
						primitiveCl.data.prism.empty = prism->empty;
						primitiveCl.data.prism.triangleHeight = prism->triangleHeight;
						primitiveCl.data.prism.height = prism->height;
						primitiveCl.data.prism.prismAngle = prism->prismAngle;
						primitiveCl.data.prism.normals = toClFloat3(prism->normals);
						primitiveCl.data.prism.repeat = toClFloat3(prism->repeat);

						usePrimitivePrism = true;
					}
					else
						throw QString("sPrimitivePrism");
					break;
				}

				case fractal::objEllipsoid:
				{
					const sPrimitiveEllipsoid *ellipsoid =
						dynamic_cast<const sPrimitiveEllipsoid *>(primitive.get());
					if (ellipsoid)
					{
						primitiveCl.data.ellipsoid.empty = ellipsoid->empty;
						primitiveCl.data.ellipsoid.repeat = toClFloat3(ellipsoid->repeat);
						primitiveCl.data.ellipsoid.limitsEnable = ellipsoid->limitsEnable;
						primitiveCl.data.ellipsoid.limitsMax = toClFloat3(ellipsoid->limitsMax);
						primitiveCl.data.ellipsoid.limitsMin = toClFloat3(ellipsoid->limitsMin);
						usePrimitiveEllipsoid = true;
					}
					else
						throw QString("sPrimitiveEllipsoid");
					break;
				}

				case fractal::objCapsule:
				{
					const sPrimitiveCapsule *capsule =
						dynamic_cast<const sPrimitiveCapsule *>(primitive.get());
					if (capsule)
					{
						primitiveCl.data.capsule.empty = capsule->empty;
						primitiveCl.data.capsule.radius = capsule->radius;
						primitiveCl.data.capsule.height = capsule->height;
						primitiveCl.data.capsule.repeat = toClFloat3(capsule->repeat);
						primitiveCl.data.capsule.limitsEnable = capsule->limitsEnable;
						primitiveCl.data.capsule.limitsMax = toClFloat3(capsule->limitsMax);
						primitiveCl.data.capsule.limitsMin = toClFloat3(capsule->limitsMin);
						usePrimitiveCapsule = true;
					}
					else
						throw QString("sPrimitiveCapsule");
					break;
				}

				case fractal::objHexPrism:
				{
					const sPrimitiveHexPrism *hexprism =
						dynamic_cast<const sPrimitiveHexPrism *>(primitive.get());
					if (hexprism)
					{
						primitiveCl.data.hexprism.empty = hexprism->empty;
						primitiveCl.data.hexprism.height = hexprism->height;
						primitiveCl.data.hexprism.repeat = toClFloat3(hexprism->repeat);
						primitiveCl.data.hexprism.limitsEnable = hexprism->limitsEnable;
						primitiveCl.data.hexprism.limitsMax = toClFloat3(hexprism->limitsMax);
						primitiveCl.data.hexprism.limitsMin = toClFloat3(hexprism->limitsMin);
						usePrimitiveHexPrism = true;
					}
					else
						throw QString("sPrimitiveHexPrism");
					break;
				}

				case fractal::objLavaPlane:
				{
					const sPrimitiveLavaPlane *lava =
						dynamic_cast<const sPrimitiveLavaPlane *>(primitive.get());
					if (lava)
					{
						primitiveCl.data.lavaplane.empty = lava->empty;
						primitiveCl.data.lavaplane.waveHeight = lava->waveHeight;
						primitiveCl.data.lavaplane.waveScale = lava->waveScale;
						primitiveCl.data.lavaplane.waveOctaves = lava->waveOctaves;
						usePrimitiveLavaPlane = true;
					}
					else
						throw QString("sPrimitiveLavaPlane");
					break;
				}

				case fractal::objOctahedron:
				{
					const sPrimitiveOctahedron *octa =
						dynamic_cast<const sPrimitiveOctahedron *>(primitive.get());
					if (octa)
					{
						primitiveCl.data.octahedron.empty = octa->empty;
						primitiveCl.data.octahedron.repeat = toClFloat3(octa->repeat);
						primitiveCl.data.octahedron.limitsEnable = octa->limitsEnable;
						primitiveCl.data.octahedron.limitsMax = toClFloat3(octa->limitsMax);
						primitiveCl.data.octahedron.limitsMin = toClFloat3(octa->limitsMin);
						usePrimitiveOctahedron = true;
					}
					else
						throw QString("sPrimitiveOctahedron");
					break;
				}

				case fractal::objPyramid:
				{
					const sPrimitivePyramid *pyramid =
						dynamic_cast<const sPrimitivePyramid *>(primitive.get());
					if (pyramid)
					{
						primitiveCl.data.pyramid.empty = pyramid->empty;
						primitiveCl.data.pyramid.height = pyramid->height;
						primitiveCl.data.pyramid.baseSize = pyramid->baseSize;
						primitiveCl.data.pyramid.repeat = toClFloat3(pyramid->repeat);
						primitiveCl.data.pyramid.limitsEnable = pyramid->limitsEnable;
						primitiveCl.data.pyramid.limitsMax = toClFloat3(pyramid->limitsMax);
						primitiveCl.data.pyramid.limitsMin = toClFloat3(pyramid->limitsMin);
						usePrimitivePyramid = true;
					}
					else
						throw QString("sPrimitivePyramid");
					break;
				}

				case fractal::objTerrainPlane:
				{
					const sPrimitiveTerrainPlane *terrain =
						dynamic_cast<const sPrimitiveTerrainPlane *>(primitive.get());
					if (terrain)
					{
						primitiveCl.data.terrainplane.empty = terrain->empty;
						primitiveCl.data.terrainplane.terrainType = terrain->terrainType;
						primitiveCl.data.terrainplane.amplitude = terrain->amplitude;
						primitiveCl.data.terrainplane.frequency = terrain->frequency;
						primitiveCl.data.terrainplane.octaves = terrain->octaves;
						primitiveCl.data.terrainplane.roughness = terrain->roughness;
						primitiveCl.data.terrainplane.lacunarity = terrain->lacunarity;
						primitiveCl.data.terrainplane.erosion = terrain->erosion;
						primitiveCl.data.terrainplane.detailScale = terrain->detailScale;
						usePrimitiveTerrainPlane = true;
					}
					else
						throw QString("sPrimitiveTerrainPlane");
					break;
				}

				default:
				{
					qCritical() << "cOpenClDynamicData::BuildPrimitivesData - invalid object type";
					break;
				}
			}
		}
		catch (const QString &ex)
		{
			qCritical() << QString(
				"cOpenClDynamicData::BuildPrimitivesData - invalid dynamic cast to %1 "
				"object - error: ")
									<< ex;
		}

		data.append(reinterpret_cast<char *>(&primitiveCl), sizeof(primitiveCl));
		totalDataOffset += sizeof(primitiveCl);
	}

	// replace arrayOffset:
	data.replace(arrayOffsetAddress, sizeof(arrayOffset), reinterpret_cast<char *>(&arrayOffset),
		sizeof(arrayOffset));

	QString definesCollector;
	if (usePrimitiveBox) definesCollector += " -DUSE_PRIMITIVE_BOX";
	if (usePrimitiveCircle) definesCollector += " -DUSE_PRIMITIVE_CIRCLE";
	if (usePrimitiveCone) definesCollector += " -DUSE_PRIMITIVE_CONE";
	if (usePrimitiveCylinder) definesCollector += " -DUSE_PRIMITIVE_CYLINDER";
	if (usePrimitivePlane) definesCollector += " -DUSE_PRIMITIVE_PLANE";
	if (usePrimitivePrism) definesCollector += " -DUSE_PRIMITIVE_PRISM";
	if (usePrimitiveRectangle) definesCollector += " -DUSE_PRIMITIVE_RECTANGLE";
	if (usePrimitiveSphere) definesCollector += " -DUSE_PRIMITIVE_SPHERE";
	if (usePrimitiveTorus) definesCollector += " -DUSE_PRIMITIVE_TORUS";
	if (usePrimitiveWater) definesCollector += " -DUSE_PRIMITIVE_WATER";
	if (usePrimitiveEllipsoid) definesCollector += " -DUSE_PRIMITIVE_ELLIPSOID";
	if (usePrimitiveCapsule) definesCollector += " -DUSE_PRIMITIVE_CAPSULE";
	if (usePrimitiveHexPrism) definesCollector += " -DUSE_PRIMITIVE_HEXPRISM";
	if (usePrimitiveLavaPlane) definesCollector += " -DUSE_PRIMITIVE_LAVAPLANE";
	if (usePrimitiveOctahedron) definesCollector += " -DUSE_PRIMITIVE_OCTAHEDRON";
	if (usePrimitivePyramid) definesCollector += " -DUSE_PRIMITIVE_PYRAMID";
	if (usePrimitiveTerrainPlane) definesCollector += " -DUSE_PRIMITIVE_TERRAINPLANE";

	if (primitivesContainer->primitiveIndexForBasicFog >= 0)
		definesCollector += " -DBASIC_FOG_SHAPE_FROM_PRIMITIVE";
	if (primitivesContainer->primitiveIndexForDistFog >= 0)
		definesCollector += " -DDIST_FOG_SHAPE_FROM_PRIMITIVE";
	if (primitivesContainer->primitiveIndexForIterFog >= 0)
		definesCollector += " -DITER_FOG_SHAPE_FROM_PRIMITIVE";
	if (primitivesContainer->primitiveIndexForClouds >= 0)
		definesCollector += " -DCLOUDS_SHAPE_FROM_PRIMITIVE";

	return definesCollector;
}

void cOpenClDynamicData::BuildObjectsData(const std::vector<cObjectData> *objectData)
{
	/* use __attribute__((aligned(16))) in kernel code for array
	 *
	 * header:
	 * cl_int numberOfObjects
	 * cl_int arrayOffset;
	 *
	 * array (aligned to 16):
	 * 	objectDataCl object1
	 * 	objectDataCl object2
	 *  ...
	 * 	objectDataCl objectN
	 */

	totalDataOffset += PutDummyToAlign(totalDataOffset, 16, &data);
	itemOffsets[objectsItemIndex].itemOffset = totalDataOffset;

	cl_int numberOfObjects = objectData->size();
	data.append(reinterpret_cast<char *>(&numberOfObjects), sizeof(numberOfObjects));
	totalDataOffset += sizeof(numberOfObjects);

	// reserve bytes for array offset
	cl_int arrayOffset = 0;
	int arrayOffsetAddress = totalDataOffset;
	data.append(reinterpret_cast<char *>(&arrayOffset), sizeof(arrayOffset));
	totalDataOffset += sizeof(arrayOffset);

	// copy objects aligned to 16
	for (int i = 0; i < numberOfObjects; i++)
	{
		// align struct to 16
		totalDataOffset += PutDummyToAlign(totalDataOffset, 16, &data);
		if (i == 0) arrayOffset = totalDataOffset;

		sObjectDataCl objectCl;
		const cObjectData *object = &objectData->at(i);
		objectCl.enable = true; // dummy - only used for primitives data
		objectCl.objectId = i;
		objectCl.position = toClFloat3(object->position);
		objectCl.size = toClFloat3(object->size);
		objectCl.repeat = toClFloat3(object->repeat);
		objectCl.materialId = object->materialId;
		objectCl.objectType = static_cast<enumObjectTypeCl>(object->objectType);
		objectCl.rotationMatrix = toClMatrix33(object->rotationMatrix);

		data.append(reinterpret_cast<char *>(&objectCl), sizeof(objectCl));
		totalDataOffset += sizeof(objectCl);
	}

	// replace arrayOffset:
	data.replace(arrayOffsetAddress, sizeof(arrayOffset), reinterpret_cast<char *>(&arrayOffset),
		sizeof(arrayOffset));
}

void cOpenClDynamicData::BuildNebulaGradientsData(const sParamRender *params)
{
	/* use __attribute__((aligned(16))) in kernel code for array
	 *
	 * header:
	 * cl_int paletteItemsOffset
	 * cl_int paletteOffsetXAxis
	 * cl_int paletteSizeXAxis
	 * cl_int paletteOffsetYAxis
	 * cl_int paletteSizeYAxis
	 * cl_int paletteOffsetZAxis
	 * cl_int paletteSizeZAxis
	 * cl_int paletteOffsetIterations
	 * cl_int paletteSizeIterations
	 *
	 * array (aligned to 16):
	 * 	cl_float4 gradientXAxis1
	 * 	cl_float4 gradientXAxis2
	 *  ...
	 * 	cl_float4 gradientXAxisN
	 *
	 * 	cl_float4 gradientYAxis1
	 * 	cl_float4 gradientYAxis2
	 *  ...
	 * 	cl_float4 gradientYAxisN
	 *
	 * 	cl_float4 gradientZAxis1
	 * 	cl_float4 gradientZAxis2
	 *  ...
	 * 	cl_float4 gradientZAxisN
	 */

	totalDataOffset += PutDummyToAlign(totalDataOffset, 16, &data);
	itemOffsets[nebulaGradientsItemIndex].itemOffset = totalDataOffset;

	std::vector<cl_float4> paletteCl;

	QList<cColorGradient::sColor> gradientXAxis = params->nebulaXAxisColors.GetListOfSortedColors();
	QList<cColorGradient::sColor> gradientYAxis = params->nebulaYAxisColors.GetListOfSortedColors();
	QList<cColorGradient::sColor> gradientZAxis = params->nebulaZAxisColors.GetListOfSortedColors();
	QList<cColorGradient::sColor> gradientIterations =
		params->nebulaIterationsColors.GetListOfSortedColors();

	int paletteOffsetXAxis = 0;
	int paletteSizeXAxis = gradientXAxis.size();

	int paletteOffsetYAxis = paletteOffsetXAxis + paletteSizeXAxis;
	int paletteSizeYAxis = gradientYAxis.size();

	int paletteOffsetZAxis = paletteOffsetYAxis + paletteSizeYAxis;
	int paletteSizeZAxis = gradientZAxis.size();

	int paletteOffsetIterations = paletteOffsetZAxis + paletteSizeZAxis;
	int paletteSizeIterations = gradientIterations.size();

	int totalSizeOfGradients =
		paletteSizeXAxis + paletteSizeYAxis + paletteSizeZAxis + paletteSizeIterations;

	paletteCl.resize(totalSizeOfGradients);

	for (int i = 0; i < paletteSizeXAxis; i++)
	{
		paletteCl[i + paletteOffsetXAxis] =
			toClFloat4(CVector4(gradientXAxis[i].color.R / 256.0, gradientXAxis[i].color.G / 256.0,
				gradientXAxis[i].color.B / 256.0, gradientXAxis[i].position));
	}

	for (int i = 0; i < paletteSizeYAxis; i++)
	{
		paletteCl[i + paletteOffsetYAxis] =
			toClFloat4(CVector4(gradientYAxis[i].color.R / 256.0, gradientYAxis[i].color.G / 256.0,
				gradientYAxis[i].color.B / 256.0, gradientYAxis[i].position));
	}

	for (int i = 0; i < paletteSizeZAxis; i++)
	{
		paletteCl[i + paletteOffsetZAxis] =
			toClFloat4(CVector4(gradientZAxis[i].color.R / 256.0, gradientZAxis[i].color.G / 256.0,
				gradientZAxis[i].color.B / 256.0, gradientZAxis[i].position));
	}

	for (int i = 0; i < paletteSizeIterations; i++)
	{
		paletteCl[i + paletteOffsetIterations] = toClFloat4(
			CVector4(gradientIterations[i].color.R / 256.0, gradientIterations[i].color.G / 256.0,
				gradientIterations[i].color.B / 256.0, gradientIterations[i].position));
	}

	cl_int paletteItemsOffset = 0;
	// reserve bytes cl_int paletteItemsOffset
	int paletteItemsOffsetAddress = totalDataOffset;
	data.append(reinterpret_cast<char *>(&paletteItemsOffset), sizeof(paletteItemsOffset));
	totalDataOffset += sizeof(paletteItemsOffset);

	// cl_int paletteOffsetXAxis
	data.append(reinterpret_cast<char *>(&paletteOffsetXAxis), sizeof(paletteOffsetXAxis));
	totalDataOffset += sizeof(paletteOffsetXAxis);
	// cl_int paletteSizeXAxis
	data.append(reinterpret_cast<char *>(&paletteSizeXAxis), sizeof(paletteSizeXAxis));
	totalDataOffset += sizeof(paletteSizeXAxis);

	// cl_int paletteOffsetYAxis
	data.append(reinterpret_cast<char *>(&paletteOffsetYAxis), sizeof(paletteOffsetYAxis));
	totalDataOffset += sizeof(paletteOffsetYAxis);
	// cl_int paletteSizeYAxis
	data.append(reinterpret_cast<char *>(&paletteSizeYAxis), sizeof(paletteSizeYAxis));
	totalDataOffset += sizeof(paletteSizeYAxis);

	// cl_int paletteOffsetZAxis
	data.append(reinterpret_cast<char *>(&paletteOffsetZAxis), sizeof(paletteOffsetZAxis));
	totalDataOffset += sizeof(paletteOffsetZAxis);
	// cl_int paletteSizeZAxis
	data.append(reinterpret_cast<char *>(&paletteSizeZAxis), sizeof(paletteSizeZAxis));
	totalDataOffset += sizeof(paletteSizeZAxis);

	// cl_int paletteOffsetIterations
	data.append(reinterpret_cast<char *>(&paletteOffsetIterations), sizeof(paletteOffsetIterations));
	totalDataOffset += sizeof(paletteOffsetIterations);
	// cl_int paletteSizeIterations
	data.append(reinterpret_cast<char *>(&paletteSizeIterations), sizeof(paletteSizeIterations));
	totalDataOffset += sizeof(paletteSizeIterations);

	// add dummy bytes for alignment to 16
	totalDataOffset += PutDummyToAlign(totalDataOffset, 16, &data);

	// palette data
	paletteItemsOffset = totalDataOffset;
	int paletteSizeBytes = totalSizeOfGradients * sizeof(cl_float4);
	data.append(reinterpret_cast<char *>(paletteCl.data()), paletteSizeBytes);
	totalDataOffset += paletteSizeBytes;

	// fill paletteItemsOffset value
	data.replace(paletteItemsOffsetAddress, sizeof(paletteItemsOffset),
		reinterpret_cast<char *>(&paletteItemsOffset), sizeof(paletteItemsOffset));
}

void cOpenClDynamicData::BuildDeepZoomData(const float *orbitData, int orbitLength,
	float power, float bailout, float rebaseThreshold,
	float centerX, float centerY, float centerZ,
	const float *saMatrix, int saSkipIters, bool saValid)
{
	/* Deep Zoom perturbation data for GPU
	 *
	 * header:
	 * cl_int orbitLength
	 * cl_float power
	 * cl_float bailout
	 * cl_float rebaseThreshold
	 * cl_float centerX, centerY, centerZ
	 * cl_float saMatrix[9]
	 * cl_int saSkipIters
	 * cl_int saValid
	 * cl_int orbitDataOffset
	 *
	 * array (aligned to 16):
	 *   float[8] orbitPoint0 (Z.x, Z.y, Z.z, DE, r, theta, phi, escaped)
	 *   float[8] orbitPoint1
	 *   ...
	 */

	totalDataOffset += PutDummyToAlign(totalDataOffset, 16, &data);
	itemOffsets[deepZoomItemIndex].itemOffset = totalDataOffset;

	cl_int clOrbitLength = orbitLength;
	data.append(reinterpret_cast<char *>(&clOrbitLength), sizeof(clOrbitLength));
	totalDataOffset += sizeof(clOrbitLength);

	cl_float clPower = power;
	data.append(reinterpret_cast<char *>(&clPower), sizeof(clPower));
	totalDataOffset += sizeof(clPower);

	cl_float clBailout = bailout;
	data.append(reinterpret_cast<char *>(&clBailout), sizeof(clBailout));
	totalDataOffset += sizeof(clBailout);

	cl_float clRebase = rebaseThreshold;
	data.append(reinterpret_cast<char *>(&clRebase), sizeof(clRebase));
	totalDataOffset += sizeof(clRebase);

	cl_float clCx = centerX;
	data.append(reinterpret_cast<char *>(&clCx), sizeof(clCx));
	totalDataOffset += sizeof(clCx);
	cl_float clCy = centerY;
	data.append(reinterpret_cast<char *>(&clCy), sizeof(clCy));
	totalDataOffset += sizeof(clCy);
	cl_float clCz = centerZ;
	data.append(reinterpret_cast<char *>(&clCz), sizeof(clCz));
	totalDataOffset += sizeof(clCz);

	// SA matrix (9 floats)
	for (int i = 0; i < 9; i++)
	{
		cl_float val = saMatrix[i];
		data.append(reinterpret_cast<char *>(&val), sizeof(val));
		totalDataOffset += sizeof(val);
	}

	cl_int clSASkip = saSkipIters;
	data.append(reinterpret_cast<char *>(&clSASkip), sizeof(clSASkip));
	totalDataOffset += sizeof(clSASkip);

	cl_int clSAValid = saValid ? 1 : 0;
	data.append(reinterpret_cast<char *>(&clSAValid), sizeof(clSAValid));
	totalDataOffset += sizeof(clSAValid);

	// reserve bytes for orbit data offset
	cl_int orbitDataOffset = 0;
	int orbitDataOffsetAddress = totalDataOffset;
	data.append(reinterpret_cast<char *>(&orbitDataOffset), sizeof(orbitDataOffset));
	totalDataOffset += sizeof(orbitDataOffset);

	// align to 16 before orbit array
	totalDataOffset += PutDummyToAlign(totalDataOffset, 16, &data);
	orbitDataOffset = totalDataOffset;

	// orbit data: orbitLength * 8 floats per point
	int orbitBytes = orbitLength * 8 * sizeof(cl_float);
	data.append(reinterpret_cast<const char *>(orbitData), orbitBytes);
	totalDataOffset += orbitBytes;

	// fill orbitDataOffset value
	data.replace(orbitDataOffsetAddress, sizeof(orbitDataOffset),
		reinterpret_cast<char *>(&orbitDataOffset), sizeof(orbitDataOffset));
}

#endif // USE_OPENCL
