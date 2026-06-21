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
 * cDOFPreview - Fast real-time DOF preview for parameter adjustments
 *
 * VERIFIED AGAINST DOF NUCLEAR ANALYSIS:
 * - NIVEAU_2: Uses same blur algorithm principles as full DOF
 * - NIVEAU_3: Integrates with same parameter flow (DOF_focus, DOF_radius)
 * - NIVEAU_4: CPU-only implementation (no GPU overhead for preview)
 * - NIVEAU_5: Handles edge cases (infinity z-values, zero radius)
 */

#ifndef MANDELBULBER2_SRC_DOF_PREVIEW_HPP_
#define MANDELBULBER2_SRC_DOF_PREVIEW_HPP_

#include <QObject>
#include <cmath>
#include <memory>

#include "cimage.hpp"

class cDOFPreview : public QObject
{
	Q_OBJECT

public:
	cDOFPreview(QObject *parent = nullptr);
	~cDOFPreview() override;

	// Fast preview rendering (< 100ms target)
	// Uses 1/4 resolution and simplified single-pass blur
	void RenderFastPreview(std::shared_ptr<cImage> sourceImage, float focusDistance,
		float blurRadius, bool *stopRequest = nullptr);

	// Enable/disable preview mode
	void SetPreviewEnabled(bool enabled) { previewEnabled = enabled; }
	bool IsPreviewEnabled() const { return previewEnabled; }

signals:
	void previewUpdated();
	void previewProgress(int percent);

private:
	bool previewEnabled;

	// Fast Gaussian blur approximation
	// Verified against NIVEAU_2_ALGORITMEN.md - simplified version of Phase I
	void ApplyFastBlur(std::shared_ptr<cImage> image, float focusDistance, float blurRadius,
		bool *stopRequest);

	// Calculate blur radius for a pixel based on z-buffer depth
	// Same formula as full DOF (NIVEAU_2 section 2.1)
	inline float CalculateBlurRadius(float zBuffer, float focusDistance, float maxBlurRadius) const
	{
		if (zBuffer >= 1e10) return 0.0f; // Edge Case 4: infinity handling
		float delta = fabs(zBuffer - focusDistance);
		float radius = delta * maxBlurRadius;
		return radius;
	}
};

#endif /* MANDELBULBER2_SRC_DOF_PREVIEW_HPP_ */
