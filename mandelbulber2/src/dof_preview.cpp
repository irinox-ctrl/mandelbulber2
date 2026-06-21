/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2024 Mandelbulber Team        §R-==%w["'~5]m%=L.=~5N
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
 * Authors: Krzysztof Marczak (buddhi1980@gmail.com), AI Assistant
 *
 * cDOFPreview - Fast real-time DOF preview implementation
 */

#include "dof_preview.hpp"

#include <algorithm>
#include <cmath>

#include "color_structures.hpp"

cDOFPreview::cDOFPreview(QObject *parent) : QObject(parent), previewEnabled(false)
{
}

cDOFPreview::~cDOFPreview() = default;

void cDOFPreview::RenderFastPreview(
	std::shared_ptr<cImage> sourceImage, float focusDistance, float blurRadius, bool *stopRequest)
{
	if (!previewEnabled || !sourceImage) return;

	emit previewProgress(0);

	// Apply fast blur directly to the image
	ApplyFastBlur(sourceImage, focusDistance, blurRadius, stopRequest);

	emit previewProgress(100);
	emit previewUpdated();
}

void cDOFPreview::ApplyFastBlur(
	std::shared_ptr<cImage> image, float focusDistance, float maxBlurRadius, bool *stopRequest)
{
	const quint64 width = image->GetWidth();
	const quint64 height = image->GetHeight();

	// FAST PREVIEW MODE: Process at 1/2 resolution for speed
	// Verified against NIVEAU_2_ALGORITMEN.md: Simplified Phase I blur
	const int step = 2; // Sample every 2nd pixel

	// Create temporary buffer for blurred image
	std::vector<sRGBFloat> tempBuffer(width * height);

	// Phase I: Forward blur (simplified version)
	for (quint64 y = 0; y < height; y += step)
	{
		if (stopRequest && *stopRequest) return;

		for (quint64 x = 0; x < width; x += step)
		{
			float zBuffer = image->GetPixelZBuffer(x, y);
			float blurRad = CalculateBlurRadius(zBuffer, focusDistance, maxBlurRadius);

			// For preview, limit blur radius to keep it fast
			blurRad = (std::min)(blurRad, 20.0f);

			if (blurRad < 0.5f)
			{
				// No blur needed - copy original pixel
				tempBuffer[y * width + x] = image->GetPixelPostImage(x, y);
			}
			else
			{
				// Simple box blur for speed (instead of Gaussian)
				// Accumulate colors in blur radius
				float totalR = 0.0f, totalG = 0.0f, totalB = 0.0f;
				int sampleCount = 0;

				int iRadius = int(blurRad + 0.5f);
				for (int dy = -iRadius; dy <= iRadius; dy += step)
				{
					for (int dx = -iRadius; dx <= iRadius; dx += step)
					{
						qint64 sx = qint64(x) + dx;
						qint64 sy = qint64(y) + dy;

						// Bounds check (NIVEAU_5 Edge Case 6: image boundaries)
						if (sx >= 0 && sx < qint64(width) && sy >= 0 && sy < qint64(height))
						{
							sRGBFloat sample = image->GetPixelPostImage(quint64(sx), quint64(sy));
							totalR += sample.R;
							totalG += sample.G;
							totalB += sample.B;
							sampleCount++;
						}
					}
				}

				// Average and store
				if (sampleCount > 0)
				{
					sRGBFloat blurred;
					blurred.R = totalR / float(sampleCount);
					blurred.G = totalG / float(sampleCount);
					blurred.B = totalB / float(sampleCount);
					tempBuffer[y * width + x] = blurred;
				}
				else
				{
					tempBuffer[y * width + x] = image->GetPixelPostImage(x, y);
				}
			}
		}

		// Progress update every 10 rows
		if (y % 10 == 0)
		{
			int progress = int((y * 100) / height);
			emit previewProgress(progress);
		}
	}

	// Copy blurred result back to image (only sampled pixels)
	for (quint64 y = 0; y < height; y += step)
	{
		for (quint64 x = 0; x < width; x += step)
		{
			image->PutPixelPostImage(x, y, tempBuffer[y * width + x]);
		}
	}

	// Fill in gaps with simple interpolation for smoother preview
	for (quint64 y = 0; y < height; ++y)
	{
		for (quint64 x = 0; x < width; ++x)
		{
			if (x % step != 0 || y % step != 0)
			{
				// Interpolate from nearest sampled pixels
				quint64 x0 = (x / step) * step;
				quint64 x1 = (std::min)(x0 + step, width - 1);
				quint64 y0 = (y / step) * step;
				quint64 y1 = (std::min)(y0 + step, height - 1);

				// Simple bilinear interpolation
				sRGBFloat p00 = tempBuffer[y0 * width + x0];
				sRGBFloat p10 = tempBuffer[y0 * width + x1];
				sRGBFloat p01 = tempBuffer[y1 * width + x0];
				sRGBFloat p11 = tempBuffer[y1 * width + x1];

				float fx = float(x - x0) / float(step);
				float fy = float(y - y0) / float(step);

				sRGBFloat result;
				result.R = p00.R * (1 - fx) * (1 - fy) + p10.R * fx * (1 - fy) + p01.R * (1 - fx) * fy
									 + p11.R * fx * fy;
				result.G = p00.G * (1 - fx) * (1 - fy) + p10.G * fx * (1 - fy) + p01.G * (1 - fx) * fy
									 + p11.G * fx * fy;
				result.B = p00.B * (1 - fx) * (1 - fy) + p10.B * fx * (1 - fy) + p01.B * (1 - fx) * fy
									 + p11.B * fx * fy;

				image->PutPixelPostImage(x, y, result);
			}
		}
	}
}
