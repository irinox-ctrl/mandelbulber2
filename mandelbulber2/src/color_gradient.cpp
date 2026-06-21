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

cColorGradient::cColorGradient()
{
	// first two colors are always positioned at 0.0 and 1.0;

	sColor positionedColor = {sRGB(255, 255, 255), 0.0, 1.0f, 0.5f, InterpolationMode::Linear};
	colors.append(positionedColor);

	sColor positionedColor2 = {sRGB(255, 255, 255), 1.0, 1.0f, 0.5f, InterpolationMode::Linear};
	colors.append(positionedColor2);

	defaultInterpolationMode = InterpolationMode::Linear;

	grayscale = false;
	sorted = false;
	midpointIntensity = 1.0f;
}

cColorGradient::~cColorGradient() = default;

void cColorGradient::SetInterpolationMode(InterpolationMode mode)
{
	defaultInterpolationMode = mode;
	for (int i = 0; i < colors.size() - 1; i++)
	{
		colors[i].nextSegmentMode = mode;
	}
	for (int i = 0; i < opacitySegmentModes.size(); i++)
	{
		opacitySegmentModes[i] = mode;
	}
}

void cColorGradient::SetSegmentMode(int segmentIndex, InterpolationMode mode)
{
	SortGradient();
	if (segmentIndex >= 0 && segmentIndex < colors.size() - 1)
	{
		colors[segmentIndex].nextSegmentMode = mode;
	}
}

cColorGradient::InterpolationMode cColorGradient::GetSegmentMode(int segmentIndex) const
{
	if (segmentIndex >= 0 && segmentIndex < colors.size() - 1)
	{
		return colors.at(segmentIndex).nextSegmentMode;
	}
	return defaultInterpolationMode;
}

int cColorGradient::AddColor(sRGB color, float position, float opacity)
{
	sorted = false;
	position = CorrectPosition(position, -1);
	color = MakeGrayscaleIfNeeded(color);
	sColor positionedColor = {color, position, opacity, 0.5f, defaultInterpolationMode};
	colors.append(positionedColor);
	return colors.size();
}

void cColorGradient::ModifyColor(int index, sRGB color)
{
	if (index < colors.size())
	{
		sorted = false;
		color = MakeGrayscaleIfNeeded(color);
		colors[index].color = color;
	}
	else
	{
		qCritical() << "color index is too high";
	}
}

void cColorGradient::ModifyOpacity(int index, float opacity)
{
	if (index < colors.size())
	{
		colors[index].opacity = qBound(0.0f, opacity, 1.0f);
		sorted = false;
	}
	else
	{
		qCritical() << "color index is too high";
	}
}

void cColorGradient::ModifyPosition(int index, float position)
{
	position = CorrectPosition(position, index);

	if (index < colors.size())
	{
		sorted = false;
		colors[index].position = position;
	}
	else
	{
		qCritical() << "wrong color index";
	}
}

void cColorGradient::RemoveColor(int index)
{
	if (colors.size() > 2)
	{
		if (index < colors.size())
		{
			sorted = false;
			colors.removeAt(index);
		}
		else
		{
			qCritical() << "color index is too high";
		}
	}
	else
	{
		qCritical() << "there must be at least two colors";
	}
}

// ===================================================================
// OPACITY STOP METHODS
// ===================================================================

int cColorGradient::AddOpacityStop(float position, float opacity)
{
	sorted = false;
	position = qBound(0.0f, position, 1.0f);
	opacity = qBound(0.0f, opacity, 1.0f);
	sOpacityStop stop = {position, opacity, 0.5f};
	opacityStops.append(stop);
	opacityMidpoints.append(0.5f);
	opacitySegmentModes.append(defaultInterpolationMode);
	return opacityStops.size();
}

void cColorGradient::RemoveOpacityStop(int index)
{
	if (index >= 0 && index < opacityStops.size())
	{
		sorted = false;
		opacityStops.removeAt(index);
		if (index > 0 && index - 1 < opacityMidpoints.size())
		{
			opacityMidpoints.removeAt(index - 1);
			if (index - 1 < opacitySegmentModes.size())
				opacitySegmentModes.removeAt(index - 1);
		}
		else if (!opacityMidpoints.isEmpty())
		{
			opacityMidpoints.removeFirst();
			if (!opacitySegmentModes.isEmpty())
				opacitySegmentModes.removeFirst();
		}
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

void cColorGradient::ModifyOpacityStopOpacity(int index, float opacity)
{
	if (index >= 0 && index < opacityStops.size())
	{
		sorted = false;
		opacityStops[index].opacity = qBound(0.0f, opacity, 1.0f);
	}
}

QList<cColorGradient::sOpacityStop> cColorGradient::GetListOfOpacityStops() const
{
	return opacityStops;
}

QList<cColorGradient::sOpacityStop> cColorGradient::GetListOfSortedOpacityStops() const
{
	if (!sorted) qCritical() << "Opacity stops were not sorted!";
	return sortedOpacityStops;
}

bool cColorGradient::HasSeparateOpacityStops() const
{
	return !opacityStops.isEmpty();
}

float cColorGradient::GetOpacityStopOpacityByIndex(int index) const
{
	if (index >= 0 && index < opacityStops.size())
		return opacityStops.at(index).opacity;
	return 1.0f;
}

float cColorGradient::GetOpacityStopPositionByIndex(int index) const
{
	if (index >= 0 && index < opacityStops.size())
		return opacityStops.at(index).position;
	return 0.0f;
}

void cColorGradient::SetOpacityMidpoint(int segmentIndex, float midpoint)
{
	SortGradient();
	if (segmentIndex >= 0 && segmentIndex < opacityMidpoints.size())
	{
		opacityMidpoints[segmentIndex] = qBound(0.01f, midpoint, 0.99f);
	}
}

float cColorGradient::GetOpacityMidpoint(int segmentIndex) const
{
	if (segmentIndex >= 0 && segmentIndex < opacityMidpoints.size())
	{
		return opacityMidpoints[segmentIndex];
	}
	return 0.5f;
}

void cColorGradient::SetOpacitySegmentMode(int segmentIndex, InterpolationMode mode)
{
	SortGradient();
	if (segmentIndex >= 0 && segmentIndex < opacitySegmentModes.size())
	{
		opacitySegmentModes[segmentIndex] = mode;
	}
}

cColorGradient::InterpolationMode cColorGradient::GetOpacitySegmentMode(int segmentIndex) const
{
	if (segmentIndex >= 0 && segmentIndex < opacitySegmentModes.size())
	{
		return opacitySegmentModes[segmentIndex];
	}
	return defaultInterpolationMode;
}

int cColorGradient::PaletteIterator(int paletteIndex, float colorPosition) const
{
	int newIndex = paletteIndex;
	while (newIndex < sortedColors.size() - 1 && colorPosition > sortedColors[newIndex + 1].position)
	{
		newIndex++;
	}
	return newIndex;
}

sRGB cColorGradient::GetColor(float position, bool smooth) const
{
	int paletteIndex = PaletteIterator(0, position);
	return Interpolate(paletteIndex, position, smooth);
}

sRGB cColorGradient::Interpolate(int paletteIndex, float pos, bool smooth) const
{
	sRGB color;
	if (sortedColors.isEmpty()) return sRGB(255, 255, 255);
	// if last element then just copy color value (no interpolation)
	if (paletteIndex >= sortedColors.size() - 1)
	{
		color = sortedColors[sortedColors.size() - 1].color;
	}
	else
	{
		// interpolation
		sRGB color1 = sortedColors[paletteIndex].color;
		sRGB color2 = sortedColors[paletteIndex + 1].color;
		float pos1 = sortedColors[paletteIndex].position;
		float pos2 = sortedColors[paletteIndex + 1].position;
		// relative delta
		if (pos2 - pos1 > 0.0f)
		{
			float delta = (pos - pos1) / (pos2 - pos1);
			InterpolationMode mode = (paletteIndex < sortedColors.size() - 1)
				? sortedColors[paletteIndex].nextSegmentMode : defaultInterpolationMode;


			bool useSmooth = (mode == InterpolationMode::Smooth)
										 || (mode == InterpolationMode::Linear && smooth);
			if (useSmooth) delta = 0.5f * (1.0f - cosf(delta * float(M_PI)));

			if (paletteIndex < sortedColors.size() - 1)
				delta = ApplyMidpoint(delta, sortedColors[paletteIndex].nextMidpoint);

			// Quadratic Bezier uses midpoint as control point instead of ApplyMidpoint
			if (mode == InterpolationMode::QuadraticBezier)
			{
				float mp = (paletteIndex < sortedColors.size() - 1) ? sortedColors[paletteIndex].nextMidpoint : 0.5f;
				delta = 2.0f * (1.0f - delta) * delta * mp + delta * delta;
			}

			// PowerCurve uses midpoint as gamma exponent
			if (mode == InterpolationMode::PowerCurve)
			{
				float mp = (paletteIndex < colors.size() - 1) ? sortedColors[paletteIndex].nextMidpoint : 0.5f;
				mp = qBound(0.01f, mp, 0.99f);
				float gamma = logf(0.5f) / logf(mp);
				delta = powf(delta, gamma);
			}

			float nDelta = 1.0f - delta;

			switch (mode)
			{
				case InterpolationMode::Constant:
				{
					color = (delta < 0.5f) ? color1 : color2;
					break;
				}
				case InterpolationMode::HSLShort:
				case InterpolationMode::HSLLong:
				{
					float h1, s1, l1, h2, s2, l2;
					RGBtoHSL(color1.R / 255.0f, color1.G / 255.0f, color1.B / 255.0f, h1, s1, l1);
					RGBtoHSL(color2.R / 255.0f, color2.G / 255.0f, color2.B / 255.0f, h2, s2, l2);
					float h = InterpolateHue(h1, h2, delta, mode == InterpolationMode::HSLShort);
					float s = s1 * nDelta + s2 * delta;
					float l = l1 * nDelta + l2 * delta;
					sRGBFloat rgb = HSLtoRGB(h, s, l);
					color.R = qBound(0, int(rgb.R * 255.0f), 255);
					color.G = qBound(0, int(rgb.G * 255.0f), 255);
					color.B = qBound(0, int(rgb.B * 255.0f), 255);
					break;
				}
				case InterpolationMode::Cubic:
				{
					int n = colors.size();
					auto getCh = [n, this](int idx, int ch) -> float {
						if (idx < 0) idx = 0;
						if (idx >= n) idx = n - 1;
						if (ch == 0) return sortedColors[idx].color.R;
						if (ch == 1) return sortedColors[idx].color.G;
						return sortedColors[idx].color.B;
					};
					int i = paletteIndex;
					color.R = qBound(0, int(CubicInterpolate(getCh(i - 1, 0), getCh(i, 0), getCh(i + 1, 0), getCh(i + 2, 0), delta)), 255);
					color.G = qBound(0, int(CubicInterpolate(getCh(i - 1, 1), getCh(i, 1), getCh(i + 1, 1), getCh(i + 2, 1), delta)), 255);
					color.B = qBound(0, int(CubicInterpolate(getCh(i - 1, 2), getCh(i, 2), getCh(i + 1, 2), getCh(i + 2, 2), delta)), 255);
					break;
				}
				case InterpolationMode::Linear:
				case InterpolationMode::Smooth:
				case InterpolationMode::QuadraticBezier:
				case InterpolationMode::PowerCurve:
				default:
				{
					color.R = int(color1.R * nDelta + color2.R * delta);
					color.G = int(color1.G * nDelta + color2.G * delta);
					color.B = int(color1.B * nDelta + color2.B * delta);
					break;
				}
			}
		}
		else
		{
			qCritical() << "Wrong sequence of colors";
			color = color1;
		}
	}
	return color;
}

sRGBFloat cColorGradient::GetColorFloat(float position, bool smooth) const
{
	int paletteIndex = PaletteIterator(0, position);
	return InterpolateFloat(paletteIndex, position, smooth);
}

sRGBFloat cColorGradient::InterpolateFloat(int paletteIndex, float pos, bool smooth) const
{
	sRGBFloat color;
	if (sortedColors.isEmpty()) return sRGBFloat(1.0f, 1.0f, 1.0f);
	// if last element then just copy color value (no interpolation)
	if (paletteIndex >= sortedColors.size() - 1)
	{
		color.R = sortedColors[sortedColors.size() - 1].color.R / 255.0f;
		color.G = sortedColors[sortedColors.size() - 1].color.G / 255.0f;
		color.B = sortedColors[sortedColors.size() - 1].color.B / 255.0f;
	}
	else
	{
		// interpolation
		sRGBFloat color1, color2;

		color1.R = sortedColors[paletteIndex].color.R / 255.0f;
		color1.G = sortedColors[paletteIndex].color.G / 255.0f;
		color1.B = sortedColors[paletteIndex].color.B / 255.0f;

		color2.R = sortedColors[paletteIndex + 1].color.R / 255.0f;
		color2.G = sortedColors[paletteIndex + 1].color.G / 255.0f;
		color2.B = sortedColors[paletteIndex + 1].color.B / 255.0f;

		float pos1 = sortedColors[paletteIndex].position;
		float pos2 = sortedColors[paletteIndex + 1].position;
		// relative delta
		if (pos2 - pos1 > 0.0f)
		{
			float delta = (pos - pos1) / (pos2 - pos1);
			InterpolationMode mode = (paletteIndex < sortedColors.size() - 1)
				? sortedColors[paletteIndex].nextSegmentMode : defaultInterpolationMode;


			bool useSmooth = (mode == InterpolationMode::Smooth)
										 || (mode == InterpolationMode::Linear && smooth);
			if (useSmooth) delta = 0.5f * (1.0f - cosf(delta * float(M_PI)));

			if (paletteIndex < sortedColors.size() - 1)
				delta = ApplyMidpoint(delta, sortedColors[paletteIndex].nextMidpoint);

			// Quadratic Bezier uses midpoint as control point instead of ApplyMidpoint
			if (mode == InterpolationMode::QuadraticBezier)
			{
				float mp = (paletteIndex < sortedColors.size() - 1) ? sortedColors[paletteIndex].nextMidpoint : 0.5f;
				delta = 2.0f * (1.0f - delta) * delta * mp + delta * delta;
			}

			// PowerCurve uses midpoint as gamma exponent
			if (mode == InterpolationMode::PowerCurve)
			{
				float mp = (paletteIndex < sortedColors.size() - 1) ? sortedColors[paletteIndex].nextMidpoint : 0.5f;
				mp = qBound(0.01f, mp, 0.99f);
				float gamma = logf(0.5f) / logf(mp);
				delta = powf(delta, gamma);
			}

			float nDelta = 1.0f - delta;

			switch (mode)
			{
				case InterpolationMode::Constant:
				{
					color = (delta < 0.5f) ? color1 : color2;
					break;
				}
				case InterpolationMode::HSLShort:
				case InterpolationMode::HSLLong:
				{
					float h1, s1, l1, h2, s2, l2;
					RGBtoHSL(color1.R, color1.G, color1.B, h1, s1, l1);
					RGBtoHSL(color2.R, color2.G, color2.B, h2, s2, l2);
					float h = InterpolateHue(h1, h2, delta, mode == InterpolationMode::HSLShort);
					float s = s1 * nDelta + s2 * delta;
					float l = l1 * nDelta + l2 * delta;
					color = HSLtoRGB(h, s, l);
					break;
				}
				case InterpolationMode::Cubic:
				{
					int n = sortedColors.size();
					auto getCh = [n, this](int idx, int ch) -> float {
						if (idx < 0) idx = 0;
						if (idx >= n) idx = n - 1;
						if (ch == 0) return sortedColors[idx].color.R / 255.0f;
						if (ch == 1) return sortedColors[idx].color.G / 255.0f;
						return sortedColors[idx].color.B / 255.0f;
					};
					int i = paletteIndex;
					color.R = qBound(0.0f, CubicInterpolate(getCh(i - 1, 0), getCh(i, 0), getCh(i + 1, 0), getCh(i + 2, 0), delta), 1.0f);
					color.G = qBound(0.0f, CubicInterpolate(getCh(i - 1, 1), getCh(i, 1), getCh(i + 1, 1), getCh(i + 2, 1), delta), 1.0f);
					color.B = qBound(0.0f, CubicInterpolate(getCh(i - 1, 2), getCh(i, 2), getCh(i + 1, 2), getCh(i + 2, 2), delta), 1.0f);
					break;
				}
				case InterpolationMode::Linear:
				case InterpolationMode::Smooth:
				case InterpolationMode::QuadraticBezier:
				case InterpolationMode::PowerCurve:
				default:
				{
					color.R = color1.R * nDelta + color2.R * delta;
					color.G = color1.G * nDelta + color2.G * delta;
					color.B = color1.B * nDelta + color2.B * delta;
					break;
				}
			}
		}
		else
		{
			qCritical() << "Wrong sequence of colors";
			color = color1;
		}
	}
	return color;
}

float cColorGradient::GetOpacity(float position, bool smooth) const
{
	if (!sortedOpacityStops.isEmpty())
	{
		return InterpolateOpacityFromStops(position);
	}
	// Fallback: legacy per-color-stop opacity
	int paletteIndex = PaletteIterator(0, position);
	return InterpolateOpacityFromColors(paletteIndex, position, smooth);
}

float cColorGradient::InterpolateOpacityFromStops(float pos) const
{
	if (sortedOpacityStops.isEmpty()) return 1.0f;
	if (sortedOpacityStops.size() == 1) return sortedOpacityStops.first().opacity;

	// Find the segment containing pos
	int index = 0;
	while (index < sortedOpacityStops.size() - 1 && pos > sortedOpacityStops[index + 1].position)
	{
		index++;
	}

	float opacity1 = sortedOpacityStops[index].opacity;
	if (index >= sortedOpacityStops.size() - 1)
	{
		return opacity1;
	}

	float opacity2 = sortedOpacityStops[index + 1].opacity;
	float pos1 = sortedOpacityStops[index].position;
	float pos2 = sortedOpacityStops[index + 1].position;

	if (pos2 - pos1 > 0.0f)
	{
		float delta = (pos - pos1) / (pos2 - pos1);
		InterpolationMode mode = (index < opacitySegmentModes.size())
			? opacitySegmentModes[index] : defaultInterpolationMode;

		bool useSmooth = (mode == InterpolationMode::Smooth)
									 || (mode == InterpolationMode::Linear && false);
		if (useSmooth) delta = 0.5f * (1.0f - cosf(delta * float(M_PI)));

		if (index < opacityMidpoints.size())
			delta = ApplyMidpoint(delta, opacityMidpoints[index]);

		// Quadratic Bezier uses midpoint as control point
		if (mode == InterpolationMode::QuadraticBezier)
		{
			float mp = (index < opacityMidpoints.size()) ? opacityMidpoints[index] : 0.5f;
			delta = 2.0f * (1.0f - delta) * delta * mp + delta * delta;
		}

		// PowerCurve uses midpoint as gamma exponent
		if (mode == InterpolationMode::PowerCurve)
		{
			float mp = (index < opacityMidpoints.size()) ? opacityMidpoints[index] : 0.5f;
			mp = qBound(0.01f, mp, 0.99f);
			float gamma = logf(0.5f) / logf(mp);
			delta = powf(delta, gamma);
		}

		float nDelta = 1.0f - delta;

		switch (mode)
		{
			case InterpolationMode::Constant:
				return (delta < 0.5f) ? opacity1 : opacity2;
			case InterpolationMode::Cubic:
			{
				int n = sortedOpacityStops.size();
				auto getOp = [n, this](int idx) -> float {
					if (idx < 0) idx = 0;
					if (idx >= n) idx = n - 1;
					return sortedOpacityStops[idx].opacity;
				};
				return qBound(0.0f, CubicInterpolate(getOp(index - 1), getOp(index),
					getOp(index + 1), getOp(index + 2), delta), 1.0f);
			}
			case InterpolationMode::Linear:
			case InterpolationMode::Smooth:
			case InterpolationMode::QuadraticBezier:
			case InterpolationMode::PowerCurve:
			case InterpolationMode::HSLShort:
			case InterpolationMode::HSLLong:
			default:
				return opacity1 * nDelta + opacity2 * delta;
		}
	}
	return opacity1;
}

float cColorGradient::InterpolateOpacityFromColors(int paletteIndex, float pos, bool smooth) const
{
	// if last element then just copy opacity value (no interpolation)
	if (paletteIndex >= sortedColors.size() - 1)
	{
		return sortedColors[paletteIndex].opacity;
	}
	else
	{
		float opacity1 = sortedColors[paletteIndex].opacity;
		float opacity2 = sortedColors[paletteIndex + 1].opacity;

		float pos1 = sortedColors[paletteIndex].position;
		float pos2 = sortedColors[paletteIndex + 1].position;
		// relative delta
		if (pos2 - pos1 > 0.0f)
		{
			float delta = (pos - pos1) / (pos2 - pos1);

			if (smooth) delta = 0.5f * (1.0f - cosf(delta * float(M_PI)));

			if (paletteIndex < sortedColors.size() - 1)
				delta = ApplyMidpoint(delta, sortedColors[paletteIndex].nextMidpoint);

			float nDelta = 1.0f - delta;
			return opacity1 * nDelta + opacity2 * delta;
		}
		else
		{
			qCritical() << "Wrong sequence of colors";
			return opacity1;
		}
	}
}

QVector<sRGBA8> cColorGradient::GetGradient(int length, bool smooth)
{
	QVector<sRGBA8> gradient;
	if (length >= 2)
	{
		SortGradient();

		gradient.reserve(length);

		int paletteIndex = 0;

		float step = 1.0f / (length - 1);
		for (int i = 0; i < length; i++)
		{
			float pos = i * step;
			paletteIndex = PaletteIterator(paletteIndex, pos);
			sRGB color = Interpolate(paletteIndex, pos, smooth);
			float opacity = GetOpacity(pos, smooth);
			gradient.append(sRGBA8(color.R, color.G, color.B, int(opacity * 255)));
		}
	}
	else
	{
		qCritical() << "Wrong length of gradient";
	}

	return gradient;
}

QList<cColorGradient::sColor> cColorGradient::GetListOfColors() const
{
	return colors;
}

QList<cColorGradient::sColor> cColorGradient::GetListOfSortedColors() const
{
	if (!sorted) qCritical() << "Colors were not sorted!";
	return sortedColors;
}

void cColorGradient::SortGradient()
{
	if (!sorted)
	{
		QMutex mutex;
		mutex.lock();

		// Build index permutation that sorts colors by position
		QVector<int> indices(colors.size());
		for (int i = 0; i < colors.size(); i++) indices[i] = i;
		std::sort(indices.begin(), indices.end(), [this](int a, int b) {
			return colors[a].position < colors[b].position;
		});

		// Sort the colors in-place. Midpoints and segment modes are stored in sColor,
		// so they automatically move with their associated color.
		QList<sColor> colorsTemp;
		for (int idx : indices)
		{
			colorsTemp.append(colors[idx]);
		}
		colors = colorsTemp;
		sortedColors = colors; // cache for const readers

		// Sort opacity stops by position
		// Build index permutation for opacity stops
		int numOpacityStops = opacityStops.size();
		QVector<int> opIndices(numOpacityStops);
		for (int i = 0; i < numOpacityStops; i++) opIndices[i] = i;
		std::sort(opIndices.begin(), opIndices.end(), [this](int a, int b) {
			return opacityStops[a].position < opacityStops[b].position;
		});

		sortedOpacityStops.clear();
		for (int idx : opIndices)
		{
			sortedOpacityStops.append(opacityStops[idx]);
		}

		// Reorder opacity midpoints to match sorted opacity stop order
		int numOpacitySegments = qMax(0, numOpacityStops - 1);
		QVector<float> sortedOpacityMidpoints(numOpacitySegments);
		QVector<InterpolationMode> sortedOpacitySegmentModes(numOpacitySegments);
		for (int j = 0; j < numOpacitySegments; j++)
		{
			int oldIdx = opIndices[j];
			if (oldIdx < opacityMidpoints.size())
			{
				sortedOpacityMidpoints[j] = opacityMidpoints[oldIdx];
			}
			else
			{
				sortedOpacityMidpoints[j] = 0.5f;
			}
			if (oldIdx < opacitySegmentModes.size())
			{
				sortedOpacitySegmentModes[j] = opacitySegmentModes[oldIdx];
			}
			else
			{
				sortedOpacitySegmentModes[j] = defaultInterpolationMode;
			}
		}
		opacityMidpoints = sortedOpacityMidpoints;
		opacitySegmentModes = sortedOpacitySegmentModes;

		// Keep original list sorted too so indices always match between sorted and original
		opacityStops = sortedOpacityStops;

		sorted = true;
		mutex.unlock();
	}
}



QString cColorGradient::GetColorsAsString()
{
	SortGradient();
	QString string;

	// Check if any opacity is non-default (< 1.0)
	bool hasNonDefaultOpacity = false;
	for (int i = 0; i < colors.size(); i++)
	{
		if (colors[i].opacity < 0.999f)
		{
			hasNonDefaultOpacity = true;
			break;
		}
	}

	// Check if any midpoints are non-default
	bool hasNonDefaultMidpoints = false;
	for (int i = 0; i < colors.size() - 1; i++)
	{
		if (fabsf(colors[i].nextMidpoint - 0.5f) > 0.001f)
		{
			hasNonDefaultMidpoints = true;
			break;
		}
	}

	// Check if any segment modes differ from default
	bool hasNonDefaultSegmentModes = false;
	for (int i = 0; i < colors.size() - 1; i++)
	{
		if (colors[i].nextSegmentMode != defaultInterpolationMode)
		{
			hasNonDefaultSegmentModes = true;
			break;
		}
	}

	// Check if there are separate opacity stops
	bool hasSeparateOpacityStops = !opacityStops.isEmpty();

	// Determine if we need the new v2;mode; format (preserves interpolation mode + opacity + segment modes)
	bool useNewV2Format = (defaultInterpolationMode != InterpolationMode::Linear) || hasNonDefaultOpacity || hasNonDefaultSegmentModes || hasSeparateOpacityStops;

	if (useNewV2Format)
	{
		// New format: v2;mode; pos RRGGBBAA pos RRGGBBAA ... (all colors, no cyclic assumption)
		string = QString("v2;%1; ").arg(static_cast<int>(defaultInterpolationMode));
		for (int i = 0; i < colors.size(); i++)
		{
			int alpha = qBound(0, int(colors[i].opacity * 255.0f), 255);
			QString oneColor = QString("%1 %2%3%4%5")
												 .arg(int(colors[i].position * 10000))
												 .arg(colors[i].color.R, 2, 16, QChar('0'))
												 .arg(colors[i].color.G, 2, 16, QChar('0'))
												 .arg(colors[i].color.B, 2, 16, QChar('0'))
												 .arg(alpha, 2, 16, QChar('0'));
			if (i > 0) string += " ";
			string += oneColor;
		}
	}
	else
	{
		// Legacy format (no prefix, 2 tokens per stop, cyclic: last == first)
		for (int i = 0; i < colors.size() - 1; i++)
		{
			QString oneColor = QString("%1 %2%3%4")
												 .arg(int(colors[i].position * 10000))
												 .arg(colors[i].color.R, 2, 16, QChar('0'))
												 .arg(colors[i].color.G, 2, 16, QChar('0'))
												 .arg(colors[i].color.B, 2, 16, QChar('0'));
			if (i > 0) string += " ";
			string += oneColor;
		}
	}

	// Append midpoints if any are non-default (not 0.5)
	if (hasNonDefaultMidpoints)
	{
		string += " |";
		for (int i = 0; i < colors.size() - 1; i++)
		{
			string += " " + QString::number(int(colors[i].nextMidpoint * 10000.0f));
		}
	}

	// Append segment modes if any differ from default
	if (hasNonDefaultSegmentModes)
	{
		string += " |";
		for (int i = 0; i < colors.size() - 1; i++)
		{
			string += " " + QString::number(static_cast<int>(colors[i].nextSegmentMode));
		}
	}

	// Append separate opacity stops if present
	if (hasSeparateOpacityStops)
	{
		string += " |:";
		for (const sOpacityStop &stop : sortedOpacityStops)
		{
			string += " " + QString::number(int(stop.position * 10000.0f))
					+ ":" + QString::number(int(stop.opacity * 10000.0f));
		}
	}

	// Append opacity midpoints if any are non-default
	bool hasNonDefaultOpacityMidpoints = false;
	for (float mp : opacityMidpoints)
	{
		if (fabsf(mp - 0.5f) > 0.001f)
		{
			hasNonDefaultOpacityMidpoints = true;
			break;
		}
	}
	if (hasNonDefaultOpacityMidpoints)
	{
		string += " |m";
		for (float mp : opacityMidpoints)
		{
			string += " " + QString::number(int(mp * 10000.0f));
		}
	}

	// Append opacity segment modes if any differ from default
	bool hasNonDefaultOpacitySegmentModes = false;
	for (InterpolationMode sm : opacitySegmentModes)
	{
		if (sm != defaultInterpolationMode)
		{
			hasNonDefaultOpacitySegmentModes = true;
			break;
		}
	}
	if (hasNonDefaultOpacitySegmentModes)
	{
		string += " |mo";
		for (InterpolationMode sm : opacitySegmentModes)
		{
			string += " " + QString::number(static_cast<int>(sm));
		}
	}

	return string;
}

void cColorGradient::SetColorsFromString(const QString &string)
{
	QStringList split = string.split(" ");
	colors.clear();
	sorted = false;

	bool isV2Format = false;
	bool isNewV2Format = false;
	int tokenStart = 0;
	int modeInt = 0;

	if (split.size() > 0 && split[0].startsWith("v2"))
	{
		isV2Format = true;
		if (split[0].startsWith("v2;"))
		{
			// New format: v2;mode;
			isNewV2Format = true;
			QStringList parts = split[0].split(";");
			if (parts.size() >= 2) modeInt = parts[1].toInt();
			tokenStart = 1;
		}
		else
		{
			// Old format: v2:
			modeInt = 0;
			tokenStart = 1;
		}
	}

	defaultInterpolationMode = static_cast<InterpolationMode>(qBound(0, modeInt, 7));

	if (split.size() - tokenStart < 2)
	{
		sColor positionedColor = {sRGB(255, 255, 255), 0.0, 1.0f, 0.5f, InterpolationMode::Linear};
		colors.append(positionedColor);

		sColor positionedColor2 = {sRGB(255, 255, 255), 1.0, 1.0f, 0.5f, InterpolationMode::Linear};
		colors.append(positionedColor2);

		qCritical() << "Error! In gradient string shoud be at least one color";
	}
	else
	{
		float position = 0.0f;
		sRGB color;
		float opacity = 1.0f;

		int tokensPerStop = isNewV2Format ? 2 : (isV2Format ? 3 : 2);

		for (int i = tokenStart; i < split.size(); i++)
		{
			if (split[i] == "|" || split[i].startsWith("|i")) break; // midpoint separator or intensity section
			if (split[i].size() > 0)
			{
				int tokenInStop = (i - tokenStart) % tokensPerStop;
				if (tokenInStop == 0)
				{
					position = split[i].toInt() / 10000.0f;
				}
				else if (tokenInStop == 1)
				{
					if (isNewV2Format)
					{
						// New format: RRGGBBAA hex (all colors explicit, no cyclic auto-add)
						uint hex = split[i].toUInt(nullptr, 16);
						color.R = (hex >> 24) & 0xFF;
						color.G = (hex >> 16) & 0xFF;
						color.B = (hex >> 8) & 0xFF;
						opacity = (hex & 0xFF) / 255.0f;
						color = MakeGrayscaleIfNeeded(color);
						sColor colorPos = {color, position, opacity, 0.5f, defaultInterpolationMode};
						position = CorrectPosition(position, -1);
						colors.append(colorPos);
					}
					else
					{
						// Old v2: or legacy: RRGGBB hex
						uint colorHex = split[i].toUInt(nullptr, 16);
						color.R = colorHex / 65536;
						color.G = (colorHex / 256) % 256;
						color.B = colorHex % 256;
						color = MakeGrayscaleIfNeeded(color);
						if (isV2Format && !isNewV2Format)
						{
							// Old v2: wait for third token
						}
						else
						{
							// Legacy: add immediately
							sColor colorPos = {color, position, 1.0f, 0.5f, defaultInterpolationMode};
							position = CorrectPosition(position, -1);
							colors.append(colorPos);
							if (i == tokenStart + 1)
							{
								sColor lastColor = colors.first();
								lastColor.position = 1.0;
								colors.append(lastColor);
							}
						}
					}
				}
				else if (tokenInStop == 2 && isV2Format && !isNewV2Format)
				{
					// Old v2 format: opacity as integer
					opacity = split[i].toInt() / 10000.0f;
					sColor colorPos = {color, position, opacity, 0.5f, defaultInterpolationMode};
					position = CorrectPosition(position, -1);
					colors.append(colorPos);

					if (colors.size() == 2)
					{
						sColor lastColor = colors.first();
						lastColor.position = 1.0;
						colors.append(lastColor);
					}
				}
			}
		}
	}

	// Parse midpoints and segment modes
	int numSegments = qMax(0, colors.size() - 1);
	for (int j = 0; j < numSegments; j++)
	{
		colors[j].nextMidpoint = 0.5f;
		colors[j].nextSegmentMode = defaultInterpolationMode;
	}

	bool foundSep = false;
	int mpIdx = 0;
	int modeIdx = 0;
	bool parsingMidpoints = false;
	bool parsingModes = false;
	bool parsingOpacityStops = false;
	bool parsingOpacityMidpoints = false;
	bool parsingOpacityModes = false;
	opacityStops.clear();
	opacityMidpoints.clear();
	opacitySegmentModes.clear();
	for (int j = tokenStart; j < split.size(); j++)
	{
		if (split[j] == "|" || split[j] == "|:" || split[j] == "|m" || split[j] == "|mo" || split[j].startsWith("|i"))
		{
			if (split[j] == "|:")
			{
				// Opacity stops section marker
				foundSep = true;
				parsingMidpoints = false;
				parsingModes = false;
				parsingOpacityStops = true;
				parsingOpacityMidpoints = false;
				parsingOpacityModes = false;
			}
			else if (split[j] == "|m")
			{
				foundSep = true;
				parsingMidpoints = false;
				parsingModes = false;
				parsingOpacityStops = false;
				parsingOpacityMidpoints = true;
				parsingOpacityModes = false;
			}
			else if (split[j] == "|mo")
			{
				foundSep = true;
				parsingMidpoints = false;
				parsingModes = false;
				parsingOpacityStops = false;
				parsingOpacityMidpoints = false;
				parsingOpacityModes = true;
			}
			else if (split[j].startsWith("|i"))
			{
				// Intensity section (legacy, ignored by current parser)
				foundSep = true;
				parsingMidpoints = false;
				parsingModes = false;
				parsingOpacityStops = false;
				parsingOpacityMidpoints = false;
				parsingOpacityModes = false;
			}
			else if (!foundSep)
			{
				foundSep = true;
				parsingMidpoints = true;
			}
			else if (parsingMidpoints)
			{
				parsingMidpoints = false;
				parsingModes = true;
			}
			else if (parsingModes)
			{
				parsingModes = false;
				parsingOpacityStops = true;
			}
			continue;
		}
		if (foundSep && split[j].size() > 0)
		{
			if (parsingMidpoints && mpIdx < numSegments)
			{
				float mp = split[j].toInt() / 10000.0f;
				colors[mpIdx].nextMidpoint = qBound(0.01f, mp, 0.99f);
				mpIdx++;
			}
			else if (parsingModes && modeIdx < numSegments)
			{
				int sm = split[j].toInt();
				colors[modeIdx].nextSegmentMode = static_cast<InterpolationMode>(qBound(0, sm, 7));
				modeIdx++;
			}
			else if (parsingOpacityStops)
			{
				// Format: position:opacity, e.g. "5000:10000" (0.5 pos, 1.0 opacity)
				QStringList stopParts = split[j].split(":");
				if (stopParts.size() >= 2)
				{
					float stopPos = stopParts[0].toInt() / 10000.0f;
					float stopOpacity = stopParts[1].toInt() / 10000.0f;
					sOpacityStop stop = {stopPos, stopOpacity, 0.5f};
					opacityStops.append(stop);
				}
			}
			else if (parsingOpacityMidpoints)
			{
				float mp = split[j].toInt() / 10000.0f;
				opacityMidpoints.append(qBound(0.01f, mp, 0.99f));
			}
			else if (parsingOpacityModes)
			{
				int sm = split[j].toInt();
				opacitySegmentModes.append(static_cast<InterpolationMode>(qBound(0, sm, 7)));
			}
		}
	}
	SortGradient();
}

void cColorGradient::DeleteAll()
{
	colors.clear();
	colors.clear();
	opacityStops.clear();
	sortedOpacityStops.clear();
	opacityMidpoints.clear();
	opacitySegmentModes.clear();
	sorted = false;
}

void cColorGradient::DeleteAndKeepTwo()
{
	sorted = false;
	int numberOfColors = colors.size();
	for (int index = 2; index < numberOfColors; index++)
	{
		colors.removeLast();
	}
	opacityStops.clear();
	opacityMidpoints.clear();
	opacitySegmentModes.clear();
	colors[0].nextMidpoint = 0.5f;
	colors[0].nextSegmentMode = defaultInterpolationMode;
}

float cColorGradient::CorrectPosition(float position, int ignoreIndex)
{
	position = qBound(0.0f, position, 1.0f);
	bool positionIncorrect = false;

	bool rightDirection = (position < 0.5f) ? true : false;

	do
	{
		for (int i = 0; i < colors.size(); i++)
		{
			if (i == ignoreIndex) continue;
			if (fabsf(position - colors[i].position) < 0.0001f)
			{
				positionIncorrect = true;
				if (rightDirection)
				{
					position += 0.0001f;
				}
				else
				{
					position -= 0.0001f;
				}
			}
			else
			{
				positionIncorrect = false;
			}
		}
	} while (positionIncorrect);

	return position;
}

sRGB cColorGradient::GetColorByIndex(int index)
{
	if (index > colors.size() - 1) index = 1; // if index is too high then get most right color
	return colors.at(index).color;
}

float cColorGradient::GetOpacityByIndex(int index)
{
	if (index > colors.size() - 1) index = 1;
	return colors.at(index).opacity;
}

float cColorGradient::GetPositionByIndex(int index)
{
	if (index > colors.size() - 1) index = 1; // if index is too high then get most right color
	return colors.at(index).position;
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

// ===================================================================
// MIDPOINT METHODS
// ===================================================================

void cColorGradient::SetMidpoint(int segmentIndex, float midpoint)
{
	SortGradient();
	int numSegments = qMax(0, colors.size() - 1);
	if (segmentIndex >= 0 && segmentIndex < numSegments)
	{
		colors[segmentIndex].nextMidpoint = qBound(0.01f, midpoint, 0.99f);
	}
}

float cColorGradient::GetMidpoint(int segmentIndex) const
{
	if (segmentIndex >= 0 && segmentIndex < colors.size() - 1)
	{
		return colors.at(segmentIndex).nextMidpoint;
	}
	return 0.5f;
}

void cColorGradient::ResetMidpoints()
{
	for (int i = 0; i < colors.size() - 1; i++)
	{
		colors[i].nextMidpoint = 0.5f;
	}
}

float cColorGradient::ApplyMidpoint(float t, float midpoint) const
{
	// Power curve with intensity multiplier.
	// At midpoint=0.5 this gives linear (gamma=1). Midpoint<0.5 = ease-out,
	// midpoint>0.5 = ease-in. Intensity multiplies the deviation from linear.
	midpoint = qBound(0.01f, midpoint, 0.99f);
	float gamma = logf(0.5f) / logf(midpoint);
	// Apply intensity: deviation from 1.0 is multiplied
	float deviation = gamma - 1.0f;
	gamma = 1.0f + deviation * midpointIntensity;
	// Clamp to avoid numerical issues
	gamma = qBound(0.01f, gamma, 10.0f);
	return powf(t, gamma);
}

// ===================================================================
// HSL COLOR SPACE HELPERS
// ===================================================================

void cColorGradient::RGBtoHSL(float r, float g, float b, float &h, float &s, float &l)
{
	r = qBound(0.0f, r, 1.0f);
	g = qBound(0.0f, g, 1.0f);
	b = qBound(0.0f, b, 1.0f);

	float max = qMax(r, qMax(g, b));
	float min = qMin(r, qMin(g, b));
	l = (max + min) * 0.5f;

	if (max == min)
	{
		h = s = 0.0f;
	}
	else
	{
		float d = max - min;
		s = l > 0.5f ? d / (2.0f - max - min) : d / (max + min);
		if (max == r)
			h = (g - b) / d + (g < b ? 6.0f : 0.0f);
		else if (max == g)
			h = (b - r) / d + 2.0f;
		else
			h = (r - g) / d + 4.0f;
		h /= 6.0f;
	}
}

sRGBFloat cColorGradient::HSLtoRGB(float h, float s, float l)
{
	h = fmodf(h + 1.0f, 1.0f);
	s = qBound(0.0f, s, 1.0f);
	l = qBound(0.0f, l, 1.0f);

	auto hue2rgb = [](float p, float q, float t) -> float {
		if (t < 0.0f) t += 1.0f;
		if (t > 1.0f) t -= 1.0f;
		if (t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
		if (t < 1.0f / 2.0f) return q;
		if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
		return p;
	};

	sRGBFloat rgb;
	if (s == 0.0f)
	{
		rgb.R = rgb.G = rgb.B = l;
	}
	else
	{
		float q = l < 0.5f ? l * (1.0f + s) : l + s - l * s;
		float p = 2.0f * l - q;
		rgb.R = hue2rgb(p, q, h + 1.0f / 3.0f);
		rgb.G = hue2rgb(p, q, h);
		rgb.B = hue2rgb(p, q, h - 1.0f / 3.0f);
	}
	return rgb;
}

float cColorGradient::InterpolateHue(float h1, float h2, float delta, bool shortestPath)
{
	float diff = h2 - h1;
	if (shortestPath)
	{
		if (diff > 0.5f) diff -= 1.0f;
		if (diff < -0.5f) diff += 1.0f;
	}
	else
	{
		if (diff > 0.0f && diff < 0.5f) diff -= 1.0f;
		if (diff < 0.0f && diff > -0.5f) diff += 1.0f;
	}
	float h = h1 + diff * delta;
	return fmodf(h + 1.0f, 1.0f);
}

float cColorGradient::CubicInterpolate(float y0, float y1, float y2, float y3, float mu)
{
	float a0 = -0.5f * y0 + 1.5f * y1 - 1.5f * y2 + 0.5f * y3;
	float a1 = y0 - 2.5f * y1 + 2.0f * y2 - 0.5f * y3;
	float a2 = -0.5f * y0 + 0.5f * y2;
	float a3 = y1;
	float mu2 = mu * mu;
	return a0 * mu * mu2 + a1 * mu2 + a2 * mu + a3;
}
