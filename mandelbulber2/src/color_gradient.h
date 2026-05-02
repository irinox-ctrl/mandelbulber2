/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%,,,§;, "K
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
 * Advanced gradient system with Photoshop-style features:
 * - Opacity stops (per-stop alpha)
 * - Midpoints (curve control between stops)
 * - Interpolation modes (linear, smooth, spline)
 * - Masking support (alpha output)
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

	// ===================================================================
	// DATA STRUCTURES
	// ===================================================================

	// Legacy color stop (RGB only) — kept for backwards compatibility
	struct sColor
	{
		sRGB color;
		float position; // from 0 to 1.0
		static bool lessCompare(sColor a, sColor b) { return a.position < b.position; }
	};

	// New: RGBA color stop with alpha
	struct sColorStop
	{
		sRGBAFloat color; // R, G, B, A in 0.0..1.0
		float position;   // 0.0 .. 1.0
		static bool lessCompare(const sColorStop &a, const sColorStop &b)
		{
			return a.position < b.position;
		}
	};

	// New: opacity stop (separate alpha control, like Photoshop top row)
	struct sOpacityStop
	{
		float alpha;    // 0.0 .. 1.0
		float position; // 0.0 .. 1.0
		static bool lessCompare(const sOpacityStop &a, const sOpacityStop &b)
		{
			return a.position < b.position;
		}
	};

	// New: midpoint controls curve between two stops (Photoshop diamond)
	struct sMidpoint
	{
		float position; // 0.0 .. 1.0 (0.5 = center, default)
	};

	// New: interpolation modes
	enum class InterpolationMode
	{
		Linear = 0, // Direct linear interpolation
		Smooth = 1, // Cosine ease-in-out (legacy "smooth" behavior)
		Spline = 2  // Catmull-Rom spline
	};

	// ===================================================================
	// GRAYSCALE
	// ===================================================================
	void SetGrayscale() { grayscale = true; }
	bool isGrayscale() { return grayscale; }

	// ===================================================================
	// LEGACY API (backwards compatible)
	// ===================================================================
	int AddColor(sRGB color, float position); // returns new color index
	void ModifyColor(int index, sRGB color);
	void ModifyPosition(int index, float position);
	void RemoveColor(int index);
	sRGB GetColor(float position, bool smooth);
	sRGBFloat GetColorFloat(float position, bool smooth);
	sRGB GetColorByIndex(int index);
	float GetPositionByIndex(int index);
	QList<sColor> GetListOfColors() const;
	QList<sColor> GetListOfSortedColors() const;
	QVector<sRGB> GetGradient(int length, bool smooth);
	QString GetColorsAsString();
	void SetColorsFromString(const QString &string);
	void SortGradient();
	int GetNumberOfColors() { return colorStops.size(); }
	void DeleteAll();
	void DeleteAndKeepTwo();

	// ===================================================================
	// NEW: ADVANCED GRADIENT API
	// ===================================================================

	// --- Core sampling ---
	sRGBAFloat GetColorRGBA(float position); // Full RGBA with all features
	sRGBFloat GetColorFloat(float position); // RGB only, ignores alpha
	float GetAlpha(float position);          // Alpha only

	// --- Color stop management ---
	int AddColorStop(const sRGBAFloat &color, float position);
	void ModifyColorStop(int index, const sRGBAFloat &color);
	void ModifyColorStopPosition(int index, float position);
	void RemoveColorStop(int index);

	// --- Opacity stop management ---
	int AddOpacityStop(float alpha, float position);
	void ModifyOpacityStop(int index, float alpha);
	void ModifyOpacityStopPosition(int index, float position);
	void RemoveOpacityStop(int index);

	// --- Midpoint management ---
	void SetMidpoint(int segmentIndex, float midpoint); // 0.0..1.0
	float GetMidpoint(int segmentIndex) const;
	void ResetMidpoints(); // Set all midpoints to 0.5

	// --- Interpolation mode ---
	void SetInterpolationMode(InterpolationMode mode);
	InterpolationMode GetInterpolationMode() const { return interpolationMode; }

	// --- Serialization (new v2 format + legacy fallback) ---
	QString Serialize();
	void Deserialize(const QString &string);

	// --- UI helpers ---
	QVector<sRGBAFloat> GetGradientRGBA(int length);
	QList<sColorStop> GetListOfColorStops() const;
	QList<sColorStop> GetListOfSortedColorStops() const;
	QList<sOpacityStop> GetListOfOpacityStops() const;
	QList<sOpacityStop> GetListOfSortedOpacityStops() const;

	// --- Mask support ---
	void SetMaskEnable(bool enable) { maskEnabled = enable; }
	bool IsMaskEnabled() const { return maskEnabled; }

private:
	// ===================================================================
	// INTERNAL
	// ===================================================================

	// Legacy data (kept for smooth migration)
	QList<sColor> colors;
	QList<sColor> sortedColors;

	// New advanced data
	QList<sColorStop> colorStops;
	QList<sColorStop> sortedColorStops;
	QList<sOpacityStop> opacityStops;
	QList<sOpacityStop> sortedOpacityStops;
	QVector<sMidpoint> midpoints; // size = max(0, sortedColorStops.size() - 1)

	InterpolationMode interpolationMode = InterpolationMode::Linear;
	bool grayscale = false;
	bool sorted = false;
	bool maskEnabled = false;

	// Internal methods
	void Sort();
	int FindColorSegment(float position) const;
	int FindOpacitySegment(float position) const;
	float ApplyMidpoint(float t, float midpoint) const;
	sRGBAFloat InterpolateColorSegment(int seg, float localT) const;
	sRGBFloat InterpolateRGBSegment(int seg, float localT) const;
	float InterpolateAlphaSegment(int seg, float localT) const;
	sRGBFloat SplineInterpolateRGB(int seg, float localT) const;

	// Legacy helpers
	int PaletteIterator(int paletteIndex, float colorPosition) const;
	sRGB Interpolate(int paletteIndex, float pos, bool smooth) const;
	sRGBFloat InterpolateFloat(int paletteIndex, float pos, bool smooth) const;
	float CorrectPosition(float position, int ignoreIndex);
	sRGB MakeGrayscaleIfNeeded(sRGB color);

	// Serialization
	void DeserializeLegacy(const QString &string);
	void DeserializeV2(const QString &string);
};

#endif /* MANDELBULBER2_SRC_COLOR_GRADIENT_H_ */
