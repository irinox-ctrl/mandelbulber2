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

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include "color_gradient.h"

#include <algorithm>
#include <cmath>

#include <QChar>
#include <QDebug>
#include <QList>
#include <QMutex>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QtGlobal>

// ===================================================================
// CONSTRUCTOR / DESTRUCTOR
// ===================================================================

cColorGradient::cColorGradient()
{
	// First two color stops at 0.0 and 1.0 (white, fully opaque)
	sColorStop stop0;
	stop0.color = sRGBAFloat(1.0f, 1.0f, 1.0f, 1.0f);
	stop0.position = 0.0f;
	colorStops.append(stop0);

	sColorStop stop1;
	stop1.color = sRGBAFloat(1.0f, 1.0f, 1.0f, 1.0f);
	stop1.position = 1.0f;
	colorStops.append(stop1);

	// Default opacity stops (fully opaque)
	sOpacityStop op0;
	op0.alpha = 1.0f;
	op0.position = 0.0f;
	opacityStops.append(op0);

	sOpacityStop op1;
	op1.alpha = 1.0f;
	op1.position = 1.0f;
	opacityStops.append(op1);

	// Default midpoints (centered)
	midpoints.resize(1);
	midpoints[0].position = 0.5f;

	grayscale = false;
	sorted = false;
	maskEnabled = false;
	interpolationMode = InterpolationMode::Linear;

	Sort();
}

cColorGradient::~cColorGradient() = default;

// ===================================================================
// INTERNAL: SORTING
// ===================================================================

void cColorGradient::Sort()
{
	if (!sorted)
	{
		QMutex mutex;
		mutex.lock();

		// Sync legacy lists
		colors.clear();
		sortedColors.clear();
		for (const auto &stop : colorStops)
		{
			sRGB rgb;
			rgb.R = qint32(stop.color.R * 255.0f);
			rgb.G = qint32(stop.color.G * 255.0f);
			rgb.B = qint32(stop.color.B * 255.0f);
			sColor legacyColor = {rgb, stop.position};
			colors.append(legacyColor);
		}

		sortedColorStops = colorStops;
		std::sort(sortedColorStops.begin(), sortedColorStops.end(), sColorStop::lessCompare);

		sortedOpacityStops = opacityStops;
		std::sort(sortedOpacityStops.begin(), sortedOpacityStops.end(), sOpacityStop::lessCompare);

		// Resize midpoints to match segments
		int numSegments = qMax(0, sortedColorStops.size() - 1);
		if (midpoints.size() != numSegments)
		{
			midpoints.resize(numSegments);
			for (int i = 0; i < numSegments; i++)
			{
				if (midpoints[i].position <= 0.0f || midpoints[i].position >= 1.0f)
					midpoints[i].position = 0.5f;
			}
		}

		sortedColors = colors;
		std::sort(sortedColors.begin(), sortedColors.end(), sColor::lessCompare);

		sorted = true;
		mutex.unlock();
	}
}

// ===================================================================
// INTERNAL: SEGMENT FINDING
// ===================================================================

int cColorGradient::FindColorSegment(float position) const
{
	if (sortedColorStops.size() < 2)
		return 0;
	int index = 0;
	int maxIndex = int(sortedColorStops.size()) - 2;
	while (index <= maxIndex && position > sortedColorStops[index + 1].position)
	{
		index++;
	}
	return qMin(index, maxIndex);
}

int cColorGradient::FindOpacitySegment(float position) const
{
	if (sortedOpacityStops.size() < 2)
		return 0;
	int index = 0;
	int maxIndex = int(sortedOpacityStops.size()) - 2;
	while (index <= maxIndex && position > sortedOpacityStops[index + 1].position)
	{
		index++;
	}
	return qMin(index, maxIndex);
}

// ===================================================================
// INTERNAL: MIDPOINT MATH
// ===================================================================

float cColorGradient::ApplyMidpoint(float t, float midpoint) const
{
	midpoint = qBound(0.01f, midpoint, 0.99f);
	if (t < midpoint)
	{
		return 0.5f * t / midpoint;
	}
	else
	{
		return 0.5f + 0.5f * (t - midpoint) / (1.0f - midpoint);
	}
}

// ===================================================================
// INTERNAL: INTERPOLATION
// ===================================================================

sRGBFloat cColorGradient::InterpolateRGBSegment(int seg, float localT) const
{
	if (seg < 0 || seg >= sortedColorStops.size() - 1)
	{
		return sRGBFloat(1.0f, 1.0f, 1.0f);
	}

	const sColorStop &stop1 = sortedColorStops[seg];
	const sColorStop &stop2 = sortedColorStops[seg + 1];

	sRGBFloat color1(stop1.color.R, stop1.color.G, stop1.color.B);
	sRGBFloat color2(stop2.color.R, stop2.color.G, stop2.color.B);

	float nT = 1.0f - localT;
	sRGBFloat result;
	result.R = color1.R * nT + color2.R * localT;
	result.G = color1.G * nT + color2.G * localT;
	result.B = color1.B * nT + color2.B * localT;

	return result;
}

float cColorGradient::InterpolateAlphaSegment(int seg, float localT) const
{
	if (seg < 0 || seg >= sortedOpacityStops.size() - 1)
	{
		return 1.0f;
	}

	const sOpacityStop &stop1 = sortedOpacityStops[seg];
	const sOpacityStop &stop2 = sortedOpacityStops[seg + 1];

	return stop1.alpha * (1.0f - localT) + stop2.alpha * localT;
}

sRGBAFloat cColorGradient::InterpolateColorSegment(int seg, float localT) const
{
	sRGBFloat rgb = InterpolateRGBSegment(seg, localT);
	float alpha = InterpolateAlphaSegment(seg, localT);
	return sRGBAFloat(rgb.R, rgb.G, rgb.B, alpha);
}

// ===================================================================
// SPLINE INTERPOLATION (Catmull-Rom)
// ===================================================================

sRGBFloat cColorGradient::SplineInterpolateRGB(int seg, float localT) const
{
	int n = sortedColorStops.size();
	if (n < 2) return sRGBFloat(1.0f, 1.0f, 1.0f);

	// Get control points
	int i0 = qMax(0, seg - 1);
	int i1 = seg;
	int i2 = qMin(n - 1, seg + 1);
	int i3 = qMin(n - 1, seg + 2);

	sRGBFloat p0(sortedColorStops[i0].color.R, sortedColorStops[i0].color.G, sortedColorStops[i0].color.B);
	sRGBFloat p1(sortedColorStops[i1].color.R, sortedColorStops[i1].color.G, sortedColorStops[i1].color.B);
	sRGBFloat p2(sortedColorStops[i2].color.R, sortedColorStops[i2].color.G, sortedColorStops[i2].color.B);
	sRGBFloat p3(sortedColorStops[i3].color.R, sortedColorStops[i3].color.G, sortedColorStops[i3].color.B);

	float t = localT;
	float t2 = t * t;
	float t3 = t2 * t;

	// Catmull-Rom basis functions
	sRGBFloat result;
	result.R = 0.5f * ((2.0f * p1.R) + (-p0.R + p2.R) * t
					+ (2.0f * p0.R - 5.0f * p1.R + 4.0f * p2.R - p3.R) * t2
					+ (-p0.R + 3.0f * p1.R - 3.0f * p2.R + p3.R) * t3);
	result.G = 0.5f * ((2.0f * p1.G) + (-p0.G + p2.G) * t
					+ (2.0f * p0.G - 5.0f * p1.G + 4.0f * p2.G - p3.G) * t2
					+ (-p0.G + 3.0f * p1.G - 3.0f * p2.G + p3.G) * t3);
	result.B = 0.5f * ((2.0f * p1.B) + (-p0.B + p2.B) * t
					+ (2.0f * p0.B - 5.0f * p1.B + 4.0f * p2.B - p3.B) * t2
					+ (-p0.B + 3.0f * p1.B - 3.0f * p2.B + p3.B) * t3);

	return result;
}

// ===================================================================
// NEW API: CORE SAMPLING
// ===================================================================

sRGBAFloat cColorGradient::GetColorRGBA(float position)
{
	Sort();

	if (sortedColorStops.size() < 2)
		return sRGBAFloat(1.0f, 1.0f, 1.0f, 1.0f);

	// Clamp position
	position = qBound(0.0f, position, 1.0f);

	// Find segment
	int seg = FindColorSegment(position);

	// Calculate local t
	float pos1 = sortedColorStops[seg].position;
	float pos2 = sortedColorStops[seg + 1].position;
	float t = (position - pos1) / (pos2 - pos1);

	// Apply midpoint
	if (seg < midpoints.size())
	{
		t = ApplyMidpoint(t, midpoints[seg].position);
	}

	// Apply interpolation mode
	InterpolationMode mode = interpolationMode;
	sRGBFloat rgb;

	if (mode == InterpolationMode::Smooth)
	{
		t = 0.5f * (1.0f - cosf(t * float(M_PI)));
		rgb = InterpolateRGBSegment(seg, t);
	}
	else if (mode == InterpolationMode::Spline)
	{
		rgb = SplineInterpolateRGB(seg, t);
	}
	else // Linear
	{
		rgb = InterpolateRGBSegment(seg, t);
	}

	// Interpolate alpha (using separate opacity stops with their own segments)
	float alpha = 1.0f;
	if (sortedOpacityStops.size() >= 2)
	{
		int alphaSeg = FindOpacitySegment(position);
		if (alphaSeg >= 0 && alphaSeg < sortedOpacityStops.size() - 1)
		{
			float alphaPos1 = sortedOpacityStops[alphaSeg].position;
			float alphaPos2 = sortedOpacityStops[alphaSeg + 1].position;
			float alphaT = (position - alphaPos1) / (alphaPos2 - alphaPos1);
			alpha = InterpolateAlphaSegment(alphaSeg, alphaT);
		}
	}

	return sRGBAFloat(rgb.R, rgb.G, rgb.B, alpha);
}

sRGBFloat cColorGradient::GetColorFloat(float position)
{
	Sort();
	sRGBAFloat rgba = GetColorRGBA(position);
	return sRGBFloat(rgba.R, rgba.G, rgba.B);
}

float cColorGradient::GetAlpha(float position)
{
	Sort();

	if (sortedOpacityStops.size() < 2)
		return 1.0f;

	position = qBound(0.0f, position, 1.0f);
	int seg = FindOpacitySegment(position);
	if (seg < 0 || seg >= sortedOpacityStops.size() - 1)
		return 1.0f;
	float pos1 = sortedOpacityStops[seg].position;
	float pos2 = sortedOpacityStops[seg + 1].position;
	float t = (position - pos1) / (pos2 - pos1);
	return InterpolateAlphaSegment(seg, t);
}

// ===================================================================
// LEGACY API: GetColorFloat with smooth parameter
// ===================================================================

sRGBFloat cColorGradient::GetColorFloat(float position, bool smooth)
{
	// If smooth explicitly requested, use cosine interpolation regardless of mode
	// Otherwise use the configured interpolation mode
	if (smooth)
	{
		if (sortedColorStops.isEmpty())
			return sRGBFloat(1.0f, 1.0f, 1.0f);

		position = qBound(0.0f, position, 1.0f);
		int seg = FindColorSegment(position);
		float pos1 = sortedColorStops[seg].position;
		float pos2 = sortedColorStops[seg + 1].position;
		float t = (position - pos1) / (pos2 - pos1);

		if (seg < midpoints.size())
			t = ApplyMidpoint(t, midpoints[seg].position);

		t = 0.5f * (1.0f - cosf(t * float(M_PI)));
		return InterpolateRGBSegment(seg, t);
	}
	else
	{
		return GetColorFloat(position);
	}
}

// ===================================================================
// NEW API: COLOR STOP MANAGEMENT
// ===================================================================

int cColorGradient::AddColorStop(const sRGBAFloat &color, float position)
{
	sorted = false;
	position = qBound(0.0f, position, 1.0f);

	sColorStop stop;
	stop.color = color;
	stop.position = position;
	colorStops.append(stop);
	Sort();
	return colorStops.size();
}

void cColorGradient::ModifyColorStop(int index, const sRGBAFloat &color)
{
	if (index >= 0 && index < colorStops.size())
	{
		sorted = false;
		colorStops[index].color = color;
	}
}

void cColorGradient::ModifyColorStopPosition(int index, float position)
{
	if (index >= 0 && index < colorStops.size())
	{
		sorted = false;
		colorStops[index].position = qBound(0.0f, position, 1.0f);
	}
}

void cColorGradient::RemoveColorStop(int index)
{
	if (colorStops.size() > 2 && index >= 0 && index < colorStops.size())
	{
		sorted = false;
		colorStops.removeAt(index);
		Sort();
	}
}

// ===================================================================
// NEW API: OPACITY STOP MANAGEMENT
// ===================================================================

int cColorGradient::AddOpacityStop(float alpha, float position)
{
	sorted = false;
	position = qBound(0.0f, position, 1.0f);
	alpha = qBound(0.0f, alpha, 1.0f);

	sOpacityStop stop;
	stop.alpha = alpha;
	stop.position = position;
	opacityStops.append(stop);
	Sort();
	return opacityStops.size();
}

void cColorGradient::ModifyOpacityStop(int index, float alpha)
{
	if (index >= 0 && index < opacityStops.size())
	{
		sorted = false;
		opacityStops[index].alpha = qBound(0.0f, alpha, 1.0f);
	}
}

void cColorGradient::ModifyOpacityStopPosition(int index, float position)
{
	if (index >= 0 && index < opacityStops.size())
	{
		sorted = false;
		opacityStops[index].position = qBound(0.0f, position, 1.0f);
	}
}

void cColorGradient::RemoveOpacityStop(int index)
{
	if (opacityStops.size() > 2 && index >= 0 && index < opacityStops.size())
	{
		sorted = false;
		opacityStops.removeAt(index);
		Sort();
	}
}

// ===================================================================
// NEW API: MIDPOINT MANAGEMENT
// ===================================================================

void cColorGradient::SetMidpoint(int segmentIndex, float midpoint)
{
	if (segmentIndex >= 0 && segmentIndex < midpoints.size())
	{
		midpoints[segmentIndex].position = qBound(0.01f, midpoint, 0.99f);
	}
}

float cColorGradient::GetMidpoint(int segmentIndex) const
{
	if (segmentIndex >= 0 && segmentIndex < midpoints.size())
	{
		return midpoints[segmentIndex].position;
	}
	return 0.5f;
}

void cColorGradient::ResetMidpoints()
{
	for (int i = 0; i < midpoints.size(); i++)
	{
		midpoints[i].position = 0.5f;
	}
}

// ===================================================================
// NEW API: INTERPOLATION MODE
// ===================================================================

void cColorGradient::SetInterpolationMode(InterpolationMode mode)
{
	interpolationMode = mode;
}

// ===================================================================
// NEW API: SERIALIZATION (v2 format)
// ===================================================================

QString cColorGradient::Serialize()
{
	Sort();

	QStringList parts;
	parts.append("v2");
	parts.append(QString::number(int(interpolationMode)));
	parts.append(QString::number(sortedColorStops.size()));
	parts.append(QString::number(sortedOpacityStops.size()));

	// Color stops: position*10000 RRGGBBAA (hex)
	for (const auto &stop : sortedColorStops)
	{
		int r = qBound(0, int(stop.color.R * 255.0f), 255);
		int g = qBound(0, int(stop.color.G * 255.0f), 255);
		int b = qBound(0, int(stop.color.B * 255.0f), 255);
		int a = qBound(0, int(stop.color.A * 255.0f), 255);
		int hexColor = (r << 24) | (g << 16) | (b << 8) | a;

		parts.append(QString::number(int(stop.position * 10000.0f)));
		parts.append(QString("%1").arg(hexColor, 8, 16, QChar('0')));
	}

	// Opacity stops: position*10000 AA (hex)
	for (const auto &stop : sortedOpacityStops)
	{
		int a = qBound(0, int(stop.alpha * 255.0f), 255);
		parts.append(QString::number(int(stop.position * 10000.0f)));
		parts.append(QString("%1").arg(a, 2, 16, QChar('0')));
	}

	// Midpoints: position*10000 (only if not default 0.5)
	bool hasNonDefaultMidpoints = false;
	for (const auto &mp : midpoints)
	{
		if (fabsf(mp.position - 0.5f) > 0.001f)
		{
			hasNonDefaultMidpoints = true;
			break;
		}
	}

	if (hasNonDefaultMidpoints)
	{
		for (const auto &mp : midpoints)
		{
			parts.append(QString::number(int(mp.position * 10000.0f)));
		}
	}

	return parts.join(" ");
}

void cColorGradient::Deserialize(const QString &string)
{
	if (string.startsWith("v2 ") || string.startsWith("v2"))
	{
		DeserializeV2(string);
	}
	else
	{
		DeserializeLegacy(string);
	}
}

void cColorGradient::DeserializeV2(const QString &string)
{
	QStringList split = string.split(" ");
	colorStops.clear();
	opacityStops.clear();
	midpoints.clear();
	sorted = false;

	if (split.size() < 5)
	{
		// Fallback to default
		cColorGradient defaultGrad;
		*this = defaultGrad;
		return;
	}

	int idx = 0;
	if (split[idx] == "v2")
		idx++;

	int mode = split[idx++].toInt();
	interpolationMode = InterpolationMode(qBound(0, mode, 2));

	int colorCount = split[idx++].toInt();
	int opacityCount = split[idx++].toInt();

	// Parse color stops
	for (int i = 0; i < colorCount && idx + 1 < split.size(); i++)
	{
		float position = split[idx++].toFloat() / 10000.0f;
		int hexColor = split[idx++].toInt(nullptr, 16);

		int r = (hexColor >> 24) & 0xFF;
		int g = (hexColor >> 16) & 0xFF;
		int b = (hexColor >> 8) & 0xFF;
		int a = hexColor & 0xFF;

		sColorStop stop;
		stop.color.R = r / 255.0f;
		stop.color.G = g / 255.0f;
		stop.color.B = b / 255.0f;
		stop.color.A = a / 255.0f;
		stop.position = qBound(0.0f, position, 1.0f);
		colorStops.append(stop);
	}

	// Parse opacity stops
	for (int i = 0; i < opacityCount && idx + 1 < split.size(); i++)
	{
		float position = split[idx++].toFloat() / 10000.0f;
		int alpha = split[idx++].toInt(nullptr, 16);

		sOpacityStop stop;
		stop.alpha = qBound(0.0f, alpha / 255.0f, 1.0f);
		stop.position = qBound(0.0f, position, 1.0f);
		opacityStops.append(stop);
	}

	// Parse midpoints (remaining values)
	int numSegments = qMax(0, colorStops.size() - 1);
	midpoints.resize(numSegments);
	for (int i = 0; i < numSegments; i++)
	{
		midpoints[i].position = 0.5f;
	}

	int mpIdx = 0;
	while (idx < split.size() && mpIdx < numSegments)
	{
		float mp = split[idx++].toFloat() / 10000.0f;
		midpoints[mpIdx++].position = qBound(0.01f, mp, 0.99f);
	}

	Sort();
}

// ===================================================================
// LEGACY DESERIALIZATION (backwards compatibility)
// ===================================================================

void cColorGradient::DeserializeLegacy(const QString &string)
{
	QStringList split = string.split(" ");
	colorStops.clear();
	opacityStops.clear();
	midpoints.clear();
	sorted = false;

	if (split.size() < 2)
	{
		// Default white gradient
		sColorStop stop0;
		stop0.color = sRGBAFloat(1.0f, 1.0f, 1.0f, 1.0f);
		stop0.position = 0.0f;
		colorStops.append(stop0);

		sColorStop stop1;
		stop1.color = sRGBAFloat(1.0f, 1.0f, 1.0f, 1.0f);
		stop1.position = 1.0f;
		colorStops.append(stop1);
	}
	else
	{
		float position = 0.0f;
		sRGB color;

		for (int i = 0; i < split.size(); i++)
		{
			if (split[i].size() > 0)
			{
				if (i % 2 == 0)
				{
					position = split[i].toInt() / 10000.0f;
				}
				else
				{
					int colorHex = split[i].toInt(nullptr, 16);
					color.R = colorHex / 65536;
					color.G = (colorHex / 256) % 256;
					color.B = colorHex % 256;
					color = MakeGrayscaleIfNeeded(color);

					sColorStop stop;
					stop.color.R = color.R / 255.0f;
					stop.color.G = color.G / 255.0f;
					stop.color.B = color.B / 255.0f;
					stop.color.A = 1.0f; // Legacy: fully opaque
					stop.position = qBound(0.0f, position, 1.0f);
					colorStops.append(stop);

					// Photoshop behavior: first color duplicated at position 1.0
					if (i == 1)
					{
						sColorStop lastStop = colorStops.first();
						lastStop.position = 1.0f;
						colorStops.append(lastStop);
					}
				}
			}
		}
	}

	// Default opacity stops (fully opaque for legacy)
	sOpacityStop op0;
	op0.alpha = 1.0f;
	op0.position = 0.0f;
	opacityStops.append(op0);

	sOpacityStop op1;
	op1.alpha = 1.0f;
	op1.position = 1.0f;
	opacityStops.append(op1);

	// Default midpoints (centered)
	int numSegments = qMax(0, colorStops.size() - 1);
	midpoints.resize(numSegments);
	for (int i = 0; i < numSegments; i++)
	{
		midpoints[i].position = 0.5f;
	}

	// Default to Smooth mode for legacy (matches old behavior)
	interpolationMode = InterpolationMode::Smooth;

	Sort();
}

// ===================================================================
// NEW API: UI HELPERS
// ===================================================================

QVector<sRGBAFloat> cColorGradient::GetGradientRGBA(int length)
{
	QVector<sRGBAFloat> gradient;
	if (length >= 2)
	{
		gradient.reserve(length);
		float step = 1.0f / (length - 1);
		for (int i = 0; i < length; i++)
		{
			float pos = i * step;
			gradient.append(GetColorRGBA(pos));
		}
	}
	return gradient;
}

QList<cColorGradient::sColorStop> cColorGradient::GetListOfColorStops() const
{
	return colorStops;
}

QList<cColorGradient::sColorStop> cColorGradient::GetListOfSortedColorStops() const
{
	if (!sorted)
	{
		qCritical() << "Colors were not sorted!";
	}
	return sortedColorStops;
}

QList<cColorGradient::sOpacityStop> cColorGradient::GetListOfSortedOpacityStops() const
{
	if (!sorted)
	{
		qCritical() << "Opacity stops were not sorted!";
	}
	return sortedOpacityStops;
}

QList<cColorGradient::sOpacityStop> cColorGradient::GetListOfOpacityStops() const
{
	return opacityStops;
}

// ===================================================================
// LEGACY API IMPLEMENTATIONS (delegated to new system)
// ===================================================================

int cColorGradient::AddColor(sRGB color, float position)
{
	sRGBAFloat rgba;
	rgba.R = color.R / 255.0f;
	rgba.G = color.G / 255.0f;
	rgba.B = color.B / 255.0f;
	rgba.A = 1.0f;
	return AddColorStop(rgba, position);
}

void cColorGradient::ModifyColor(int index, sRGB color)
{
	if (index >= 0 && index < colorStops.size())
	{
		sorted = false;
		color = MakeGrayscaleIfNeeded(color);
		colorStops[index].color.R = color.R / 255.0f;
		colorStops[index].color.G = color.G / 255.0f;
		colorStops[index].color.B = color.B / 255.0f;
	}
}

void cColorGradient::ModifyPosition(int index, float position)
{
	ModifyColorStopPosition(index, position);
}

void cColorGradient::RemoveColor(int index)
{
	RemoveColorStop(index);
}

sRGB cColorGradient::GetColor(float position, bool smooth)
{
	sRGBFloat floatColor = GetColorFloat(position, smooth);
	sRGB result;
	result.R = qint32(qBound(0.0f, floatColor.R * 255.0f, 255.0f));
	result.G = qint32(qBound(0.0f, floatColor.G * 255.0f, 255.0f));
	result.B = qint32(qBound(0.0f, floatColor.B * 255.0f, 255.0f));
	return result;
}

sRGB cColorGradient::GetColorByIndex(int index)
{
	if (index > colorStops.size() - 1)
		index = 1;
	sRGB result;
	result.R = qint32(colorStops.at(index).color.R * 255.0f);
	result.G = qint32(colorStops.at(index).color.G * 255.0f);
	result.B = qint32(colorStops.at(index).color.B * 255.0f);
	return result;
}

float cColorGradient::GetPositionByIndex(int index)
{
	if (index > colorStops.size() - 1)
		index = 1;
	return colorStops.at(index).position;
}

QList<cColorGradient::sColor> cColorGradient::GetListOfColors() const
{
	return colors;
}

QList<cColorGradient::sColor> cColorGradient::GetListOfSortedColors() const
{
	if (!sorted)
		qCritical() << "Colors were not sorted!";
	return sortedColors;
}

QVector<sRGB> cColorGradient::GetGradient(int length, bool smooth)
{
	QVector<sRGB> gradient;
	if (length >= 2)
	{
		Sort();
		gradient.reserve(length);
		float step = 1.0f / (length - 1);
		for (int i = 0; i < length; i++)
		{
			float pos = i * step;
			sRGBFloat floatColor = GetColorFloat(pos, smooth);
			sRGB color;
			color.R = qint32(qBound(0.0f, floatColor.R * 255.0f, 255.0f));
			color.G = qint32(qBound(0.0f, floatColor.G * 255.0f, 255.0f));
			color.B = qint32(qBound(0.0f, floatColor.B * 255.0f, 255.0f));
			gradient.append(color);
		}
	}
	else
	{
		qCritical() << "Wrong length of gradient";
	}
	return gradient;
}

QString cColorGradient::GetColorsAsString()
{
	return Serialize();
}

void cColorGradient::SetColorsFromString(const QString &string)
{
	Deserialize(string);
}

void cColorGradient::SortGradient()
{
	Sort();
}

void cColorGradient::DeleteAll()
{
	colorStops.clear();
	opacityStops.clear();
	midpoints.clear();
	colors.clear();
	sortedColors.clear();
	sortedColorStops.clear();
	sortedOpacityStops.clear();
	sorted = false;
}

void cColorGradient::DeleteAndKeepTwo()
{
	sorted = false;
	while (colorStops.size() > 2)
	{
		colorStops.removeLast();
	}
	while (opacityStops.size() > 2)
	{
		opacityStops.removeLast();
	}
	midpoints.resize(1);
	midpoints[0].position = 0.5f;
	Sort();
}

// ===================================================================
// LEGACY INTERNAL METHODS
// ===================================================================

int cColorGradient::PaletteIterator(int paletteIndex, float colorPosition) const
{
	int newIndex = paletteIndex;
	while (newIndex < sortedColors.size() - 1 && colorPosition > sortedColors[newIndex + 1].position)
	{
		newIndex++;
	}
	return newIndex;
}

sRGB cColorGradient::Interpolate(int paletteIndex, float pos, bool smooth) const
{
	sRGB color;
	if (paletteIndex == sortedColors.size() - 1)
	{
		color = sortedColors[paletteIndex - 1].color;
	}
	else
	{
		sRGB color1 = sortedColors[paletteIndex].color;
		sRGB color2 = sortedColors[paletteIndex + 1].color;
		float pos1 = sortedColors[paletteIndex].position;
		float pos2 = sortedColors[paletteIndex + 1].position;
		if (pos2 - pos1 > 0.0f)
		{
			float delta = (pos - pos1) / (pos2 - pos1);
			if (smooth)
				delta = 0.5f * (1.0f - cosf(delta * float(M_PI)));
			float nDelta = 1.0f - delta;
			color.R = int(color1.R * nDelta + color2.R * delta);
			color.G = int(color1.G * nDelta + color2.G * delta);
			color.B = int(color1.B * nDelta + color2.B * delta);
		}
		else
		{
			qCritical() << "Wrong sequence of colors";
			color = color1;
		}
	}
	return color;
}

sRGBFloat cColorGradient::InterpolateFloat(int paletteIndex, float pos, bool smooth) const
{
	sRGBFloat color;
	if (paletteIndex == sortedColors.size() - 1)
	{
		color.R = sortedColors[paletteIndex - 1].color.R;
		color.G = sortedColors[paletteIndex - 1].color.G;
		color.B = sortedColors[paletteIndex - 1].color.B;
	}
	else
	{
		sRGBFloat color1, color2;
		color1.R = sortedColors[paletteIndex].color.R;
		color1.G = sortedColors[paletteIndex].color.G;
		color1.B = sortedColors[paletteIndex].color.B;
		color2.R = sortedColors[paletteIndex + 1].color.R;
		color2.G = sortedColors[paletteIndex + 1].color.G;
		color2.B = sortedColors[paletteIndex + 1].color.B;
		float pos1 = sortedColors[paletteIndex].position;
		float pos2 = sortedColors[paletteIndex + 1].position;
		if (pos2 - pos1 > 0.0f)
		{
			float delta = (pos - pos1) / (pos2 - pos1);
			if (smooth)
				delta = 0.5f * (1.0f - cosf(delta * float(M_PI)));
			float nDelta = 1.0f - delta;
			color.R = float((color1.R * nDelta + color2.R * delta) / 256.0f);
			color.G = (color1.G * nDelta + color2.G * delta) / 256.0f;
			color.B = (color1.B * nDelta + color2.B * delta) / 256.0f;
		}
		else
		{
			qCritical() << "Wrong sequence of colors";
			color = color1;
		}
	}
	return color;
}

float cColorGradient::CorrectPosition(float position, int ignoreIndex)
{
	position = qBound(0.0f, position, 1.0f);
	bool positionIncorrect = false;
	bool rightDirection = (position < 0.5f);

	do
	{
		for (int i = 0; i < colorStops.size(); i++)
		{
			if (i == ignoreIndex)
				continue;
			if (fabsf(position - colorStops[i].position) < 0.0001f)
			{
				positionIncorrect = true;
				if (rightDirection)
					position += 0.0001f;
				else
					position -= 0.0001f;
			}
			else
			{
				positionIncorrect = false;
			}
		}
	} while (positionIncorrect);

	return position;
}

sRGB cColorGradient::MakeGrayscaleIfNeeded(sRGB color)
{
	if (grayscale)
	{
		int avg = (color.R + color.G + color.B) / 3;
		color.R = color.G = color.B = avg;
	}
	return color;
}
