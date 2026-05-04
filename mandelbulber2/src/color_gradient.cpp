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

	sColor positionedColor = {sRGB(255, 255, 255), 0.0, 1.0f};
	colors.append(positionedColor);

	sColor positionedColor2 = {sRGB(255, 255, 255), 1.0, 1.0f};
	colors.append(positionedColor2);

	midpoints.append(0.5f);

	grayscale = false;
	sorted = false;
}

cColorGradient::~cColorGradient() = default;

int cColorGradient::AddColor(sRGB color, float position, float opacity)
{
	sorted = false;
	position = CorrectPosition(position, -1);
	color = MakeGrayscaleIfNeeded(color);
	sColor positionedColor = {color, position, opacity};
	colors.append(positionedColor);
	midpoints.append(0.5f);
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
			if (index > 0)
				midpoints.removeAt(index - 1);
			else if (!midpoints.isEmpty())
				midpoints.removeFirst();
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
	// if last element then just copy color value (no interpolation)
	if (paletteIndex == sortedColors.size() - 1)
	{
		color = sortedColors[paletteIndex - 1].color;
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

			if (smooth) delta = 0.5f * (1.0f - cosf(delta * float(M_PI)));

			if (paletteIndex < midpoints.size())
				delta = ApplyMidpoint(delta, midpoints[paletteIndex]);

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

sRGBFloat cColorGradient::GetColorFloat(float position, bool smooth) const
{
	int paletteIndex = PaletteIterator(0, position);
	return InterpolateFloat(paletteIndex, position, smooth);
}

sRGBFloat cColorGradient::InterpolateFloat(int paletteIndex, float pos, bool smooth) const
{
	sRGBFloat color;
	// if last element then just copy color value (no interpolation)
	if (paletteIndex == sortedColors.size() - 1)
	{
		color.R = sortedColors[paletteIndex - 1].color.R;
		color.G = sortedColors[paletteIndex - 1].color.G;
		color.B = sortedColors[paletteIndex - 1].color.B;
	}
	else
	{
		// interpolation
		sRGBFloat color1, color2;

		color1.R = sortedColors[paletteIndex].color.R;
		color1.G = sortedColors[paletteIndex].color.G;
		color1.B = sortedColors[paletteIndex].color.B;

		color2.R = sortedColors[paletteIndex + 1].color.R;
		color2.G = sortedColors[paletteIndex + 1].color.G;
		color2.B = sortedColors[paletteIndex + 1].color.B;

		float pos1 = sortedColors[paletteIndex].position;
		float pos2 = sortedColors[paletteIndex + 1].position;
		// relative delta
		if (pos2 - pos1 > 0.0f)
		{
			float delta = (pos - pos1) / (pos2 - pos1);

			if (smooth) delta = 0.5f * (1.0f - cosf(delta * float(M_PI)));

			if (paletteIndex < midpoints.size())
				delta = ApplyMidpoint(delta, midpoints[paletteIndex]);

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

float cColorGradient::GetOpacity(float position, bool smooth) const
{
	int paletteIndex = PaletteIterator(0, position);
	return InterpolateOpacity(paletteIndex, position, smooth);
}

float cColorGradient::InterpolateOpacity(int paletteIndex, float pos, bool smooth) const
{
	// if last element then just copy opacity value (no interpolation)
	if (paletteIndex == sortedColors.size() - 1)
	{
		return sortedColors[paletteIndex - 1].opacity;
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

			if (paletteIndex < midpoints.size())
				delta = ApplyMidpoint(delta, midpoints[paletteIndex]);

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
			float opacity = InterpolateOpacity(paletteIndex, pos, smooth);
			gradient.append(sRGBA8(color.R / 256, color.G / 256, color.B / 256, int(opacity * 255)));
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
		sortedColors = colors;
		std::sort(sortedColors.begin(), sortedColors.end(), sColor::lessCompare);
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
	for (int i = 0; i < sortedColors.size() - 1; i++)
	{
		if (sortedColors[i].opacity < 0.999f)
		{
			hasNonDefaultOpacity = true;
			break;
		}
	}

	// Use v2 format if opacity or midpoints are customized
	bool hasNonDefaultMidpoints = false;
	for (float mp : midpoints)
	{
		if (fabsf(mp - 0.5f) > 0.001f)
		{
			hasNonDefaultMidpoints = true;
			break;
		}
	}

	if (hasNonDefaultOpacity)
	{
		string = "v2:";
		// last color is not converted because is the same like first
		for (int i = 0; i < sortedColors.size() - 1; i++)
		{
			QString oneColor = QString("%1 %2%3%4 %5")
													 .arg(int(sortedColors[i].position * 10000))
													 .arg(sortedColors[i].color.R, 2, 16, QChar('0'))
													 .arg(sortedColors[i].color.G, 2, 16, QChar('0'))
													 .arg(sortedColors[i].color.B, 2, 16, QChar('0'))
													 .arg(int(sortedColors[i].opacity * 10000));
			if (i > 0) string += " ";
			string += oneColor;
		}
	}
	else
	{
		// Legacy format (no v2: prefix, 2 tokens per stop)
		for (int i = 0; i < sortedColors.size() - 1; i++)
		{
			QString oneColor = QString("%1 %2%3%4")
													 .arg(int(sortedColors[i].position * 10000))
													 .arg(sortedColors[i].color.R, 2, 16, QChar('0'))
													 .arg(sortedColors[i].color.G, 2, 16, QChar('0'))
													 .arg(sortedColors[i].color.B, 2, 16, QChar('0'));
			if (i > 0) string += " ";
			string += oneColor;
		}
	}

	// Append midpoints if any are non-default (not 0.5)
	if (hasNonDefaultMidpoints)
	{
		for (float mp : midpoints)
		{
			string += " " + QString::number(int(mp * 10000.0f));
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
	int tokenStart = 0;
	if (split.size() > 0 && split[0] == "v2:")
	{
		isV2Format = true;
		tokenStart = 1; // skip the "v2:" marker
	}

	if (split.size() - tokenStart < 2)
	{
		sColor positionedColor = {sRGB(255, 255, 255), 0.0, 1.0f};
		colors.append(positionedColor);

		sColor positionedColor2 = {sRGB(255, 255, 255), 1.0, 1.0f};
		colors.append(positionedColor2);

		qCritical() << "Error! In gradient string shoud be at least one color";
	}
	else
	{
		float position = 0.0f;
		sRGB color;
		float opacity = 1.0f;

		int tokensPerStop = isV2Format ? 3 : 2;

		for (int i = tokenStart; i < split.size(); i++)
		{
			if (split[i].size() > 0)
			{
				int tokenInStop = (i - tokenStart) % tokensPerStop;
				if (tokenInStop == 0)
				{
					position = split[i].toInt() / 10000.0f;
				}
				else if (tokenInStop == 1)
				{
					int colorHex = split[i].toInt(nullptr, 16);
					color.R = colorHex / 65536;
					color.G = (colorHex / 256) % 256;
					color.B = colorHex % 256;
					color = MakeGrayscaleIfNeeded(color);
					if (isV2Format)
					{
						// In v2, opacity comes next; wait for third token
					}
					else
					{
						// Legacy: no opacity, default to 1.0
						sColor colorPos = {color, position, 1.0f};
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
				else if (tokenInStop == 2 && isV2Format)
				{
					opacity = split[i].toInt() / 10000.0f;
					sColor colorPos = {color, position, opacity};
					position = CorrectPosition(position, -1);
					colors.append(colorPos);

					if (i == tokenStart + 2)
					{
						sColor lastColor = colors.first();
						lastColor.position = 1.0;
						colors.append(lastColor);
					}
				}
			}
		}
	}
	
	// Parse remaining values as midpoints (backwards compatibility: none = 0.5)
	int numSegments = qMax(0, colors.size() - 1);
	midpoints.resize(numSegments);
	for (int j = 0; j < numSegments; j++)
		 midpoints[j] = 0.5f;
	
	int tokensPerStop = isV2Format ? 3 : 2;
	int colorPairCount = (colors.size() - 1) * tokensPerStop;
	int mpIdx = 0;
	for (int j = colorPairCount + tokenStart; j < split.size() && mpIdx < numSegments; j++)
	{
		if (split[j].size() > 0)
		{
			float mp = split[j].toInt() / 10000.0f;
			midpoints[mpIdx] = qBound(0.01f, mp, 0.99f);
			mpIdx++;
		}
	}
	SortGradient();
}

void cColorGradient::DeleteAll()
{
	colors.clear();
	sortedColors.clear();
	midpoints.clear();
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
	midpoints.resize(1);
	midpoints[0] = 0.5f;
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
	if (segmentIndex >= 0 && segmentIndex < midpoints.size())
	{
		midpoints[segmentIndex] = qBound(0.01f, midpoint, 0.99f);
	}
}

float cColorGradient::GetMidpoint(int segmentIndex) const
{
	if (segmentIndex >= 0 && segmentIndex < midpoints.size())
	{
		return midpoints[segmentIndex];
	}
	return 0.5f;
}

void cColorGradient::ResetMidpoints()
{
	for (int i = 0; i < midpoints.size(); i++)
	{
		midpoints[i] = 0.5f;
	}
}

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
