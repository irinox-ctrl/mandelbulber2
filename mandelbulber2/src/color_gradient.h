/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2019-20 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * TODO: description
 */

#ifndef MANDELBULBER2_SRC_COLOR_GRADIENT_H_
#define MANDELBULBER2_SRC_COLOR_GRADIENT_H_
#include <QList>
#include <QVector>

#include "color_structures.hpp"

class cColorGradient
{
public:
	cColorGradient();
	~cColorGradient();

public:
	struct sColor
	{
		sRGB color;
		float position; // from 0 to 1.0
		float opacity;  // from 0.0 to 1.0, default 1.0

		static bool lessCompare(sColor a, sColor b) { return a.position < b.position; }
	};
	void SetGrayscale() { grayscale = true; }
	bool isGrayscale() { return grayscale; }
	int AddColor(sRGB color, float position, float opacity = 1.0f); // returns new color index
	void ModifyColor(int index, sRGB color);
	void ModifyOpacity(int index, float opacity);
	void ModifyPosition(int index, float position);
	void RemoveColor(int index);
	sRGB GetColor(float position, bool smooth) const;
	sRGBFloat GetColorFloat(float position, bool smooth) const;
	float GetOpacity(float position, bool smooth) const;
	sRGB GetColorByIndex(int index);
	float GetOpacityByIndex(int index);
	float GetPositionByIndex(int index);
	QList<sColor> GetListOfColors() const;
	QList<sColor> GetListOfSortedColors() const;
	QVector<sRGBA8> GetGradient(int length, bool smooth);
	QString GetColorsAsString();
	void SetColorsFromString(const QString &string);
	void SortGradient();
	int GetNumberOfColors() { return colors.size(); }
	int GetNumberOfSegments() { return qMax(0, colors.size() - 1); }
	void DeleteAll();

	// Interpolation modes (Photoshop-style)
	enum class InterpolationMode
	{
		Linear,   // Standard RGB linear
		Smooth,   // Cosine ease-in-out
		HSLShort, // Hue via shortest path (<=180 deg)
		HSLLong,  // Hue via longest path (>180 deg)
		Cubic,    // Catmull-Rom spline
		Constant  // Hard transition, no blend
	};
	void SetInterpolationMode(InterpolationMode mode) { interpolationMode = mode; }
	InterpolationMode GetInterpolationMode() const { return interpolationMode; }
	void DeleteAndKeepTwo();

	// Midpoint control (Photoshop-style curve per segment)
	void SetMidpoint(int segmentIndex, float midpoint);
	float GetMidpoint(int segmentIndex) const;
	void ResetMidpoints();

private:
	int PaletteIterator(int paletteIndex, float position) const;
	sRGB Interpolate(int paletteIndex, float pos, bool smooth) const;
	sRGBFloat InterpolateFloat(int paletteIndex, float pos, bool smooth) const;
	float InterpolateOpacity(int paletteIndex, float pos, bool smooth) const;
	float CorrectPosition(float position, int ignoreIndex);
	sRGB MakeGrayscaleIfNeeded(sRGB color);

	// HSL color space helpers
	static void RGBtoHSL(float r, float g, float b, float &h, float &s, float &l);
	static sRGBFloat HSLtoRGB(float h, float s, float l);
	static float InterpolateHue(float h1, float h2, float delta, bool shortestPath);
	static float CubicInterpolate(float y0, float y1, float y2, float y3, float mu);

	// Mode-aware interpolation helpers
	sRGB InterpolateMode(int paletteIndex, float pos, bool smooth) const;
	sRGBFloat InterpolateFloatMode(int paletteIndex, float pos, bool smooth) const;

	QList<sColor> colors;
	QList<sColor> sortedColors;
	QVector<float> midpoints; // one per segment, default 0.5
	bool grayscale;
	bool sorted;
	InterpolationMode interpolationMode;

	float ApplyMidpoint(float t, float midpoint) const;
};

#endif /* MANDELBULBER2_SRC_COLOR_GRADIENT_H_ */
