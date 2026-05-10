/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2019-24 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * cGradientEditWidget class - widget for editing gradients of colors
 */

#include "gradient_edit_widget.h"

#include <QColorDialog>
#include <QInputDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>
#include <QtWidgets>

#include "preview_file_dialog.h"

#include "src/common_math.h"
#include "src/error_message.hpp"
#include "src/parameters.hpp"
#include "src/random.hpp"
#include "src/system_data.hpp"
#include "src/system_directories.hpp"

cGradientEditWidget::cGradientEditWidget(QWidget *parent)
		: QWidget(parent), CommonMyWidgetWrapper(this)
{
	viewMode = false;
	mouseDragStarted = false;
	isDraggingMidpoint = false;
	isDraggingOpacityStop = false;
	pressedColorIndex = 0;
	pressedMidpointIndex = -1;
	pressedOpacityIndex = -1;
	dragStartX = 0;
	grayscale = false;
	undoIndex = -1;

	fixHeight = int(systemData.GetPreferredThumbnailSize() / 1.4);
	setFixedHeight(fixHeight);

	buttonWidth = fixHeight / 8;
	if (buttonWidth % 2 == 0) buttonWidth += 1; // to always have odd width

	margins = buttonWidth / 2 + 2;
	toolbarHeight = int(fixHeight / 3.5);

	buttonRandomColors = new QToolButton(this);
	AddToolButton(buttonRandomColors, margins, ":gradient/icons/dice_colors.svg");
	buttonRandomColorsAndPositions = new QToolButton(this);
	AddToolButton(buttonRandomColorsAndPositions, margins + (toolbarHeight + 2) * 1,
		":gradient/icons/dice_colors_and_pos.svg");
	buttonBrightnessInc = new QToolButton(this);
	AddToolButton(buttonBrightnessInc, margins + (toolbarHeight + 2) * 2,
		":gradient/icons/gradient-brighter.svg");
	buttonBrightnessDec = new QToolButton(this);
	AddToolButton(
		buttonBrightnessDec, margins + (toolbarHeight + 2) * 3, ":gradient/icons/gradient-darker.svg");
	buttonPaletteInvert = new QToolButton(this);
	AddToolButton(
		buttonPaletteInvert, margins + (toolbarHeight + 2) * 4, ":gradient/icons/gradient-invert.svg");
	buttonSaturationInc = new QToolButton(this);
	AddToolButton(buttonSaturationInc, margins + (toolbarHeight + 2) * 5,
		":gradient/icons/gradient-high-saturation.svg");
	buttonSaturationDec = new QToolButton(this);
	AddToolButton(buttonSaturationDec, margins + (toolbarHeight + 2) * 6,
		":gradient/icons/gradient-low-saturation.svg");

	// Interpolation mode dropdown
	comboInterpolationMode = new QComboBox(this);
	comboInterpolationMode->addItem("Linear");
	comboInterpolationMode->addItem("Smooth");
	comboInterpolationMode->addItem("HSL Short");
	comboInterpolationMode->addItem("HSL Long");
	comboInterpolationMode->addItem("Cubic");
	comboInterpolationMode->addItem("Constant");
	comboInterpolationMode->addItem("Quadratic Bezier");
	comboInterpolationMode->setFixedHeight(toolbarHeight);
	comboInterpolationMode->move(margins + (toolbarHeight + 2) * 7 + 10, 0);
	comboInterpolationMode->show();
	connect(comboInterpolationMode, SIGNAL(currentIndexChanged(int)), this,
		SLOT(interpolationModeChanged(int)));

	// Initialize undo stack with default gradient
	PushUndoState();

	connect(buttonRandomColors, SIGNAL(clicked()), this, SLOT(pressedButtonRandomColors()));
	connect(buttonRandomColorsAndPositions, SIGNAL(clicked()), this,
		SLOT(pressedButtonRandomColorsAndPositions()));
	connect(buttonBrightnessInc, SIGNAL(clicked()), this, SLOT(pressedButtonBrightnessInc()));
	connect(buttonBrightnessDec, SIGNAL(clicked()), this, SLOT(pressedButtonBrightnessDec()));
	connect(buttonPaletteInvert, SIGNAL(clicked()), this, SLOT(pressedButtonInvert()));
	connect(buttonSaturationInc, SIGNAL(clicked()), this, SLOT(pressedButtonSaturationInc()));
	connect(buttonSaturationDec, SIGNAL(clicked()), this, SLOT(pressedButtonSaturationDec()));

	buttonRandomColors->setToolTip(
		tr("Randomize all colors in gradient without changing positions and number of colors"));
	buttonRandomColorsAndPositions->setToolTip(
		tr("Randomize all colors, positions, and number of colors in gradient"));
	buttonBrightnessInc->setToolTip(tr("Increase brightness of gradient"));
	buttonBrightnessDec->setToolTip(tr("Decrease brightness of gradient"));
	buttonPaletteInvert->setToolTip(tr("Invert palette"));
	buttonSaturationInc->setToolTip(tr("Increase saturation of colors in gradient"));
	buttonSaturationDec->setToolTip(tr("Decrease saturation of colors in gradient"));
}

cGradientEditWidget::~cGradientEditWidget()
{
	// nothing to destroy
}

void cGradientEditWidget::SetGrayscale()
{
	delete buttonSaturationInc;
	delete buttonSaturationDec;
	grayscale = true;
	gradient.SetGrayscale();
}

void cGradientEditWidget::AddToolButton(QToolButton *toolbutton, int position, QString iconName)
{
	toolbutton->setObjectName("button");
	toolbutton->setFixedSize(toolbarHeight, toolbarHeight);
	QIcon iconRandomColors = QIcon(iconName);
	toolbutton->setIcon(iconRandomColors);
	toolbutton->setIconSize(QSize(toolbarHeight - 4, toolbarHeight - 4));
	toolbutton->move(position, 0);
	toolbutton->show();
}

void cGradientEditWidget::SetViewModeOnly()
{
	viewMode = true;
	setFixedHeight(systemData.GetPreferredThumbnailSize() / 4);
	margins = 0;
}

void cGradientEditWidget::paintEvent(QPaintEvent *event)
{
	GetDefault();

	QWidget::paintEvent(event);

	int gradientWidth = width() - 2 * margins;
	if (gradientWidth < 2) gradientWidth = 2;
	int gradientHeight = (viewMode) ? height() : (height() - toolbarHeight) / 2;

	QPainter painter(this);
	QVector<sRGBA8> grad = gradient.GetGradient(gradientWidth, false);

	// Draw checkerboard background for opacity visualization
	int checkSize = 4;
	for (int y = toolbarHeight; y < toolbarHeight + gradientHeight; y += checkSize)
	{
		for (int x = 0; x < gradientWidth; x += checkSize)
		{
			bool white = ((x / checkSize) + (y / checkSize)) % 2 == 0;
			painter.fillRect(x + margins, y, checkSize, checkSize, white ? QColor(220, 220, 220) : QColor(180, 180, 180));
		}
	}

	for (int x = 0; x < grad.size(); x++)
	{
		QColor color(grad[x].R, grad[x].G, grad[x].B, grad[x].A);
		painter.setPen(color);
		painter.drawLine(x + margins, toolbarHeight, x + margins, toolbarHeight + gradientHeight);
	}

	if (!viewMode)
	{
		// Paint opacity curve at the top
		PaintOpacityCurve(painter);

		// Paint opacity stop handles
		QList<cColorGradient::sOpacityStop> opacityStops = gradient.GetListOfOpacityStops();
		for (int i = 0; i < opacityStops.size(); i++)
		{
			PaintOpacityStop(opacityStops[i], i, painter);
		}

		QList<cColorGradient::sColor> listOfColors = gradient.GetListOfColors();
		for (cColorGradient::sColor posColor : listOfColors)
		{
			PaintButton(posColor, painter);
		}
		// Draw midpoint handles
		QList<cColorGradient::sColor> sortedColors = gradient.GetListOfSortedColors();
		for (int i = 0; i < sortedColors.size() - 1; i++)
		{
			PaintMidpointHandle(i, painter);
		}
	}
}

int cGradientEditWidget::CalcButtonPosition(float position)
{
	return int(margins + position * (width() - 2 * margins - 1));
}

int cGradientEditWidget::CalcMidpointPosition(int segmentIndex)
{
	QList<cColorGradient::sColor> sortedColors = gradient.GetListOfSortedColors();
	if (segmentIndex < 0 || segmentIndex >= sortedColors.size() - 1) return 0;
	float p1 = sortedColors[segmentIndex].position;
	float p2 = sortedColors[segmentIndex + 1].position;
	float mp = gradient.GetMidpoint(segmentIndex);
	float pos = p1 + mp * (p2 - p1);
	return int(margins + pos * (width() - 2 * margins - 1));
}

void cGradientEditWidget::PaintButton(const cColorGradient::sColor &posColor, QPainter &painter)
{
	int buttonPosition = CalcButtonPosition(posColor.position);

	int buttonTop = (height() - toolbarHeight) / 2 + toolbarHeight + buttonWidth / 2;

	QRect rect(QPoint(buttonPosition - buttonWidth / 2, buttonTop),
		QPoint(buttonPosition + buttonWidth / 2, height() - 2));

	QColor color(posColor.color.R, posColor.color.G, posColor.color.B);

	QBrush brush(color, Qt::SolidPattern);
	painter.fillRect(rect, brush);

	QVector<QPoint> triangle = {QPoint(buttonPosition, buttonTop - buttonWidth / 2),
		QPoint(buttonPosition - buttonWidth / 2, buttonTop),
		QPoint(buttonPosition + buttonWidth / 2, buttonTop)};
	QPolygon pTriangle(triangle);
	QPainterPath pathTriangle;
	pathTriangle.addPolygon(pTriangle);
	painter.fillPath(pathTriangle, brush);

	// Opacity indicator: small square inside the triangle
	int opacityIndicatorSize = buttonWidth / 3;
	if (opacityIndicatorSize < 3) opacityIndicatorSize = 3;
	int opacityGray = int(posColor.opacity * 255);
	QRect opacityRect(buttonPosition - opacityIndicatorSize / 2,
		buttonTop - buttonWidth / 2 + (buttonWidth / 2 - opacityIndicatorSize) / 2,
		opacityIndicatorSize, opacityIndicatorSize);
	painter.fillRect(opacityRect, QColor(opacityGray, opacityGray, opacityGray));

	int avgColor = (posColor.color.R + posColor.color.G + posColor.color.B) / 3;
	if (avgColor > 100)
		painter.setPen(Qt::black);
	else
		painter.setPen(Qt::white);

	painter.drawRect(rect);
}

void cGradientEditWidget::PaintMidpointHandle(int segmentIndex, QPainter &painter)
{
	int midpointPosition = CalcMidpointPosition(segmentIndex);
	int handleTop = toolbarHeight + buttonWidth / 2;
	int handleSize = buttonWidth / 2;
	if (handleSize < 3) handleSize = 3;

	QVector<QPoint> diamond = {
		QPoint(midpointPosition, handleTop - handleSize),
		QPoint(midpointPosition - handleSize, handleTop),
		QPoint(midpointPosition, handleTop + handleSize),
		QPoint(midpointPosition + handleSize, handleTop)};
	QPolygon pDiamond(diamond);
	QPainterPath pathDiamond;
	pathDiamond.addPolygon(pDiamond);

	QColor handleColor(200, 200, 200);
	if (pressedMidpointIndex == segmentIndex)
		handleColor = QColor(255, 255, 0);
	QBrush brush(handleColor, Qt::SolidPattern);
	painter.fillPath(pathDiamond, brush);
	painter.setPen(Qt::black);
	painter.drawPolygon(pDiamond);
}

void cGradientEditWidget::PaintOpacityStop(const cColorGradient::sOpacityStop &stop, int index, QPainter &painter)
{
	int stopPosition = CalcButtonPosition(stop.position);
	int handleTop = toolbarHeight + 2;
	int handleSize = buttonWidth / 2;
	if (handleSize < 4) handleSize = 4;

	// Grayscale color based on opacity
	int gray = int(stop.opacity * 255);
	QColor handleColor(gray, gray, gray);
	if (pressedOpacityIndex == index)
		handleColor = QColor(255, 255, 0); // yellow when selected

	QRect rect(stopPosition - handleSize, handleTop, handleSize * 2, handleSize * 2);
	painter.fillRect(rect, handleColor);
	painter.setPen(Qt::black);
	painter.drawRect(rect);
}

void cGradientEditWidget::PaintOpacityCurve(QPainter &painter)
{
	int gradientWidth = width() - 2 * margins;
	if (gradientWidth < 2) return;

	int curveY = toolbarHeight + buttonWidth / 2 + 2;
	int prevX = margins;
	float prevOpacity = gradient.GetOpacity(0.0f, false);
	int prevY = curveY + int((1.0f - prevOpacity) * buttonWidth);

	painter.setPen(QPen(QColor(255, 255, 255, 180), 1));
	for (int x = 1; x < gradientWidth; x++)
	{
		float pos = float(x) / gradientWidth;
		float opacity = gradient.GetOpacity(pos, false);
		int y = curveY + int((1.0f - opacity) * buttonWidth);
		painter.drawLine(prevX, prevY, margins + x, y);
		prevX = margins + x;
		prevY = y;
	}
}

int cGradientEditWidget::FindOpacityStopAtPosition(int x)
{
	QList<cColorGradient::sOpacityStop> opacityStops = gradient.GetListOfOpacityStops();
	int handleSize = buttonWidth / 2 + 2;
	if (handleSize < 5) handleSize = 5;

	for (int i = 0; i < opacityStops.size(); i++)
	{
		int xStop = CalcButtonPosition(opacityStops[i].position);
		if ((x > xStop - handleSize) && (x <= xStop + handleSize))
		{
			return i;
		}
	}
	return -1;
}

int cGradientEditWidget::FindButtonAtPosition(int x)
{
	QList<cColorGradient::sColor> listOfColors = gradient.GetListOfColors();

	for (int i = listOfColors.size() - 1; i >= 0; i--)
	{
		int xButton = CalcButtonPosition(listOfColors[i].position);
		if ((x > xButton - buttonWidth / 2) && (x <= xButton + buttonWidth / 2))
		{
			return i;
		}
	}
	return -1; //-1 means nothing found
}

int cGradientEditWidget::FindMidpointAtPosition(int x)
{
	QList<cColorGradient::sColor> sortedColors = gradient.GetListOfSortedColors();
	int handleSize = buttonWidth / 2 + 2;
	if (handleSize < 5) handleSize = 5;

	for (int i = 0; i < sortedColors.size() - 1; i++)
	{
		int xMid = CalcMidpointPosition(i);
		if ((x > xMid - handleSize) && (x <= xMid + handleSize))
		{
			return i;
		}
	}
	return -1;
}

void cGradientEditWidget::mouseMoveEvent(QMouseEvent *event)
{
	if (pressedOpacityIndex >= 0)
	{
		if (event->x() != dragStartX)
		{
			isDraggingOpacityStop = true;
		}
		if (isDraggingOpacityStop)
		{
			float pos = float(event->x() - margins) / (width() - 2 * margins - 1);
			pos = qBound(0.0f, pos, 1.0f);
			gradient.ModifyOpacityStopPosition(pressedOpacityIndex, pos);
			emit update();
		}
	}
	else if (isDraggingMidpoint && pressedMidpointIndex >= 0)
	{
		float pos = float(event->x() - margins) / (width() - 2 * margins - 1);
		QList<cColorGradient::sColor> sortedColors = gradient.GetListOfSortedColors();
		float p1 = sortedColors[pressedMidpointIndex].position;
		float p2 = sortedColors[pressedMidpointIndex + 1].position;
		float mp = (pos - p1) / (p2 - p1);
		mp = qBound(0.01f, mp, 0.99f);
		gradient.SetMidpoint(pressedMidpointIndex, mp);
		emit update();
	}
	else if (pressedColorIndex >= 2)
	{
		if (event->x() != dragStartX)
		{
			mouseDragStarted = true;
		}

		if (mouseDragStarted)
		{
			float pos = float(event->x() - margins) / (width() - 2 * margins - 1);
			gradient.ModifyPosition(pressedColorIndex, pos);
			emit update();
		}
	}
}

void cGradientEditWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		if (viewMode)
		{
			emit openEditor();
		}
		else
		{
			int mouseX = event->x();
			int mouseY = event->y();

			if (mouseY > height() / 2)
			{
				int index = FindButtonAtPosition(mouseX);
				dragStartX = mouseX;
				pressedColorIndex = index;
			}
			else if (mouseY > toolbarHeight + buttonWidth)
			{
				// Midpoint area
				int mpIndex = FindMidpointAtPosition(mouseX);
				if (mpIndex >= 0)
				{
					isDraggingMidpoint = true;
					pressedMidpointIndex = mpIndex;
					dragStartX = mouseX;
				}
			}
			else
			{
				// Opacity stop area (top of gradient bar)
				int opIndex = FindOpacityStopAtPosition(mouseX);
				if (opIndex >= 0)
				{
					pressedOpacityIndex = opIndex;
					dragStartX = mouseX;
				}
			}
		}
	}
}

void cGradientEditWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		if (!viewMode)
		{
			if (!isDraggingOpacityStop && pressedOpacityIndex < 0 && pressedColorIndex < 0 && pressedMidpointIndex < 0 && !mouseDragStarted)
			{
				// Click on empty area in opacity region — add new opacity stop
				int mouseY = event->y();
				if (mouseY < toolbarHeight + buttonWidth && mouseY > toolbarHeight)
				{
					AddOpacityStopAt(event->x());
				}
			}
			else if (pressedColorIndex >= 0 && !mouseDragStarted)
			{
				QList<cColorGradient::sColor> listOfColors = gradient.GetListOfColors();

				QColorDialog colorDialog(this);
				colorDialog.setOption(QColorDialog::DontUseNativeDialog);
				sRGB colorRGB = listOfColors[pressedColorIndex].color;
				QColor color(colorRGB.R, colorRGB.G, colorRGB.B);
				colorDialog.setCurrentColor(color);
				colorDialog.setWindowTitle(
					tr("Edit color #%1").arg(QString::number(pressedColorIndex + 1)));
				if (colorDialog.exec() == QDialog::Accepted)
				{
					color = colorDialog.currentColor();
					colorRGB = sRGB(color.red(), color.green(), color.blue());
					gradient.ModifyColor(pressedColorIndex, colorRGB);

					if (pressedColorIndex == 0) gradient.ModifyColor(1, colorRGB);

					if (pressedColorIndex == 1) gradient.ModifyColor(0, colorRGB);

					PushUndoState();
					emit update();
				}
			}

			// Push undo for drag operations
			if (isDraggingMidpoint || isDraggingOpacityStop || mouseDragStarted)
			{
				PushUndoState();
			}

			pressedColorIndex = -1;
				pressedMidpointIndex = -1;
				isDraggingMidpoint = false;
				pressedOpacityIndex = -1;
				isDraggingOpacityStop = false;
			mouseDragStarted = false;
		}
	}
}

void cGradientEditWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	if (viewMode) return;

	int mouseX = event->x();
	int mouseY = event->y();

	// Check opacity stop area first
	if (mouseY <= toolbarHeight + buttonWidth && mouseY > toolbarHeight)
	{
		int opIndex = FindOpacityStopAtPosition(mouseX);
		if (opIndex >= 0)
		{
			float currentOpacity = gradient.GetOpacityStopOpacityByIndex(opIndex);
			bool ok;
			int opacityPercent = QInputDialog::getInt(this, tr("Set opacity"),
				tr("Opacity (0-100%):"), int(currentOpacity * 100), 0, 100, 1, &ok);
			if (ok)
			{
				gradient.ModifyOpacityStopOpacity(opIndex, opacityPercent / 100.0f);
				PushUndoState();
				emit update();
			}
			return;
		}
	}
}

void cGradientEditWidget::SetColors(const QString &colorsString)
{
	gradient.SetColorsFromString(colorsString);
	if (comboInterpolationMode)
	{
		comboInterpolationMode->setCurrentIndex(static_cast<int>(gradient.GetInterpolationMode()));
	}
	emit update();
}

void cGradientEditWidget::PushUndoState()
{
	// Truncate redo history if we're not at the top of the stack
	while (undoStack.size() > undoIndex + 1)
	{
		undoStack.removeLast();
	}
	
	undoStack.append(gradient.GetColorsAsString());
	undoIndex++;
	
	// Limit stack size to 30
	if (undoStack.size() > 30)
	{
		undoStack.removeFirst();
		undoIndex--;
	}
}

void cGradientEditWidget::Undo()
{
	if (undoIndex > 0)
	{
		undoIndex--;
		gradient.SetColorsFromString(undoStack[undoIndex]);
		if (comboInterpolationMode)
		{
			comboInterpolationMode->setCurrentIndex(static_cast<int>(gradient.GetInterpolationMode()));
		}
		emit update();
	}
}

void cGradientEditWidget::Redo()
{
	if (undoIndex < undoStack.size() - 1)
	{
		undoIndex++;
		gradient.SetColorsFromString(undoStack[undoIndex]);
		if (comboInterpolationMode)
		{
			comboInterpolationMode->setCurrentIndex(static_cast<int>(gradient.GetInterpolationMode()));
		}
		emit update();
	}
}

void cGradientEditWidget::keyPressEvent(QKeyEvent *event)
{
	if (event->modifiers() & Qt::ControlModifier)
	{
		if (event->key() == Qt::Key_Z)
		{
			if (event->modifiers() & Qt::ShiftModifier)
			{
				Redo();
			}
			else
			{
				Undo();
			}
			return;
		}
		else if (event->key() == Qt::Key_Y)
		{
			Redo();
			return;
		}
	}
	QWidget::keyPressEvent(event);
}

void cGradientEditWidget::AddColor(QContextMenuEvent *event)
{
	int xClick = event->x();
	int gradientWidth = width() - 2 * margins;
	float pos = float(xClick - margins) / gradientWidth;
	gradient.SortGradient();
	sRGB color = gradient.GetColor(pos, false);
	gradient.AddColor(color, pos);
	PushUndoState();
	emit update();
}

void cGradientEditWidget::RemoveColor(QContextMenuEvent *event)
{
	int xClick = event->x();
	int index = FindButtonAtPosition(xClick);
	if (index >= 2)
	{
		gradient.RemoveColor(index);
	}
	PushUndoState();
	emit update();
}

void cGradientEditWidget::SetOpacity(QContextMenuEvent *event)
{
	int xClick = event->x();

	// First check if clicking on an opacity stop
	int opIndex = FindOpacityStopAtPosition(xClick);
	if (opIndex >= 0)
	{
		float currentOpacity = gradient.GetOpacityStopOpacityByIndex(opIndex);
		bool ok;
		int opacityPercent = QInputDialog::getInt(this, tr("Set opacity"), tr("Opacity (0-100%):"),
			int(currentOpacity * 100), 0, 100, 1, &ok);
		if (ok)
		{
			gradient.ModifyOpacityStopOpacity(opIndex, opacityPercent / 100.0f);
			emit update();
		}
		return;
	}

	// Fallback: color stop opacity (legacy)
	int index = FindButtonAtPosition(xClick);
	if (index >= 0)
	{
		float currentOpacity = gradient.GetOpacityByIndex(index);
		bool ok;
		int opacityPercent = QInputDialog::getInt(this, tr("Set opacity"), tr("Opacity (0-100%):"),
			int(currentOpacity * 100), 0, 100, 1, &ok);
		if (ok)
		{
			gradient.ModifyOpacity(index, opacityPercent / 100.0f);
			emit update();
		}
	}
}

void cGradientEditWidget::AddOpacityStopAt(int x)
{
	float pos = float(x - margins) / (width() - 2 * margins - 1);
	pos = qBound(0.0f, pos, 1.0f);
	float currentOpacity = gradient.GetOpacity(pos, false);
	gradient.AddOpacityStop(pos, currentOpacity);
	PushUndoState();
	emit update();
}

void cGradientEditWidget::RemoveOpacityStop(int index)
{
	if (index >= 0)
	{
		gradient.RemoveOpacityStop(index);
		PushUndoState();
		emit update();
	}
}

void cGradientEditWidget::Clear()
{
	gradient.DeleteAndKeepTwo();
	PushUndoState();
	emit update();
}

void cGradientEditWidget::ChangeNumberOfColors()
{
	bool ok;
	int newNumber = QInputDialog::getInt(this, tr("Change number of colors"),
		tr("New number of colors:"), gradient.GetNumberOfColors() - 1, 1, 100, 1, &ok);
	if (ok && newNumber != gradient.GetNumberOfColors() - 1)
	{
		gradient.SortGradient();
		cColorGradient newGradient;
		if (grayscale) newGradient.SetGrayscale();
		newGradient.DeleteAll();
		float step = 1.0f / newNumber;
		for (int i = 0; i < newNumber; i++)
		{
			if (i == 0)
			{
				sRGB color = gradient.GetColor(0.0f, false);
				newGradient.AddColor(color, 0.0f);
				newGradient.AddColor(color, 1.0f);
			}
			else
			{
				float pos = step * i;
				sRGB color = gradient.GetColor(pos, false);
				newGradient.AddColor(color, pos);
			}
		}
		gradient = newGradient;
		PushUndoState();
	}
	emit update();
}

void cGradientEditWidget::GrabColors()
{
	PreviewFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::ExistingFile);
	dialog.setNameFilter(tr("Images (*.jpg *.jpeg *.png *.bmp)"));
	dialog.setDirectory(
		QDir::toNativeSeparators(systemDirectories.GetImagesFolder() + QDir::separator()));
	dialog.selectFile(QDir::toNativeSeparators(systemData.lastImagePaletteFile));
	dialog.setAcceptMode(QFileDialog::AcceptOpen);
	dialog.setWindowTitle(tr("Select image to grab colors..."));
	QStringList filenames;
	if (dialog.exec())
	{
		filenames = dialog.selectedFiles();
		QString filename = QDir::toNativeSeparators(filenames.first());

		QImage imagePalette(filename);

		if (!imagePalette.isNull())
		{
			int width = imagePalette.width();
			int height = imagePalette.height();
			int numberOfColors = gradient.GetNumberOfColors();
			gradient.DeleteAll();

			float step = 1.0f / numberOfColors;

			for (int i = 0; i < numberOfColors; i++)
			{
				double angle = double(i) / numberOfColors * M_PI * 2.0;
				double x = width / 2 + cos(angle) * width * 0.4;
				double y = height / 2 + sin(angle) * height * 0.4;
				QRgb pixel = imagePalette.pixel(int(x), int(y));
				sRGB pixelRGB(qRed(pixel), qGreen(pixel), qBlue(pixel));

				if (i == 0)
				{
					gradient.AddColor(pixelRGB, 0.0);
					gradient.AddColor(pixelRGB, 1.0);
				}
				else
				{
					float pos = step * i;
					gradient.AddColor(pixelRGB, pos);
				}
			}
		}

		systemData.lastImagePaletteFile = filename;
		PushUndoState();
	}

	emit update();
}

void cGradientEditWidget::LoadColors()
{
	QFileDialog dialog(this);
	dialog.setOption(QFileDialog::DontUseNativeDialog);
	dialog.setFileMode(QFileDialog::AnyFile);
	dialog.setNameFilter(tr("Gradients (*.gradient *.txt)"));
	dialog.setDirectory(
		QDir::toNativeSeparators(QFileInfo(systemData.lastGradientFile).absolutePath()));
	dialog.selectFile(
		QDir::toNativeSeparators(QFileInfo(systemData.lastGradientFile).completeBaseName()));
	dialog.setAcceptMode(QFileDialog::AcceptOpen);
	dialog.setWindowTitle(tr("Load gradient..."));
	dialog.setDefaultSuffix("gradient");
	QStringList filenames;
	if (dialog.exec())
	{
		filenames = dialog.selectedFiles();
		QString filename = QDir::toNativeSeparators(filenames.first());
		systemData.lastGradientFile = filename;

		QFile file(filename);
		if (file.open(QIODevice::ReadOnly))
		{
			QString stringLoaded;
			QTextStream stream(&file);
			stringLoaded = stream.readLine();

			bool result = DecodeGradientFromFile(stringLoaded);
			if (!result)
			{
				cErrorMessage::showMessage(
					QObject::tr("Selected file doesn't contain valid gradient of colors"),
					cErrorMessage::errorMessage);
				return;
			}

			file.close();
			PushUndoState();
		}
	}
}

bool cGradientEditWidget::DecodeGradientFromFile(QString string)
{
	QString header = "[gradient]";
	if (string.left(header.length()) == header)
	{
		QString gradientText = string.mid(header.length() + 1);
		gradient.SetColorsFromString(gradientText);
		return true;
	}
	else if (string.contains("https://coolors.co/"))
	{
		int lastSlashPosition = string.lastIndexOf('/');
		QString colorsString = string.mid(lastSlashPosition + 1);
		QStringList splited = colorsString.split('-');
		if (splited.size() > 1)
		{
			gradient.DeleteAll();

			for (int i = 0; i < splited.size(); i++)
			{
				int colorHex = splited[i].toInt(nullptr, 16);
				sRGB color;
				color.R = colorHex / 65536;
				color.G = (colorHex / 256) % 256;
				color.B = colorHex % 256;
				float position = float(i) / splited.size();

				if (i == 0)
				{
					gradient.AddColor(color, 0.0f);
					gradient.AddColor(color, 1.0f);
				}
				else
				{
					gradient.AddColor(color, position);
				}
			}
		}
		else
		{
			return false;
		}
		return true;
	}
	return false;
}

void cGradientEditWidget::SaveColors()
{
	QFileDialog dialog(this);
	dialog.setOption(QFileDialog::DontUseNativeDialog);
	dialog.setFileMode(QFileDialog::AnyFile);
	dialog.setNameFilter(tr("Gradients (*.gradient *.txt)"));
	dialog.setDirectory(
		QDir::toNativeSeparators(QFileInfo(systemData.lastGradientFile).absolutePath()));
	dialog.selectFile(
		QDir::toNativeSeparators(QFileInfo(systemData.lastGradientFile).completeBaseName()));
	dialog.setAcceptMode(QFileDialog::AcceptSave);
	dialog.setWindowTitle(tr("Save gradient..."));
	dialog.setDefaultSuffix("gradient");
	QStringList filenames;
	if (dialog.exec())
	{
		filenames = dialog.selectedFiles();
		QString filename = QDir::toNativeSeparators(filenames.first());
		systemData.lastGradientFile = filename;

		QFile file(filename);
		if (file.open(QIODevice::ReadWrite))
		{
			QString string = gradient.GetColorsAsString();
			QTextStream stream(&file);
			stream << "[gradient] " << string << "\n";
			file.close();
		}
	}
}

void cGradientEditWidget::LoadFromClipboard()
{
	QClipboard *clipboard = QApplication::clipboard();
	QString stringLoaded = clipboard->text();

	bool result = DecodeGradientFromFile(stringLoaded);
	if (!result)
	{
		cErrorMessage::showMessage(QObject::tr("Clipboard doesn't contain valid gradient of colors"),
			cErrorMessage::errorMessage);
		return;
	}
	PushUndoState();
}

void cGradientEditWidget::SaveToClipboard()
{
	QClipboard *clipboard = QApplication::clipboard();
	QString string = QString("[gradient] ") + gradient.GetColorsAsString();
	clipboard->setText(string);
}

void cGradientEditWidget::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu *menu = new QMenu(); // menu is deleted in contextMenuEvent()

	// Check if right-clicking on an opacity stop
	int opacityIndexUnderCursor = FindOpacityStopAtPosition(event->x());

	QAction *actionAddColor = nullptr;
	QAction *actionRemoveColor = nullptr;
	QAction *actionSetOpacity = nullptr;
	QAction *actionAddOpacityStop = nullptr;
	QAction *actionRemoveOpacityStop = nullptr;

	if (opacityIndexUnderCursor >= 0)
	{
		// Context menu for opacity stop
		actionRemoveOpacityStop = menu->addAction(tr("Remove opacity stop"));
	}
	else
	{
		// Context menu for color area
		actionAddColor = menu->addAction(tr("Add color"));
		actionRemoveColor = menu->addAction(tr("Remove color"));
		actionSetOpacity = menu->addAction(tr("Set color stop opacity ..."));
		actionAddOpacityStop = menu->addAction(tr("Add opacity stop"));
	}
	
	// Per-segment interpolation mode submenu
	QMenu *segmentModeMenu = nullptr;
	int segmentIndexUnderCursor = -1;
	QList<QAction *> segmentModeActions;
	{
		float pos = float(event->x() - margins) / (width() - 2 * margins);
		gradient.SortGradient();
		QList<cColorGradient::sColor> sorted = gradient.GetListOfSortedColors();
		for (int i = 0; i < sorted.size() - 1; i++)
		{
			if (pos >= sorted[i].position && pos <= sorted[i + 1].position)
			{
				segmentIndexUnderCursor = i;
				break;
			}
		}
		if (segmentIndexUnderCursor >= 0)
		{
			segmentModeMenu = menu->addMenu(tr("Segment interpolation mode"));
			QStringList modeNames = {"Linear", "Smooth", "HSL Short", "HSL Long", "Cubic", "Constant", "Quadratic Bezier"};
			for (int m = 0; m < modeNames.size(); m++)
			{
				QAction *modeAction = segmentModeMenu->addAction(modeNames[m]);
				modeAction->setData(m);
				segmentModeActions.append(modeAction);
				if (gradient.GetSegmentMode(segmentIndexUnderCursor) == static_cast<cColorGradient::InterpolationMode>(m))
				{
					modeAction->setCheckable(true);
					modeAction->setChecked(true);
				}
			}
		}
	}
	
	menu->addSeparator();
	QAction *actionClear = menu->addAction(tr("Delete all colors"));
	QAction *actionChangeNumberOfColors = menu->addAction(tr("Change number of colors ..."));
	QAction *actionGrabColors = menu->addAction(tr("Grab colors from image ..."));
	QAction *actionLoad = menu->addAction(tr("Load colors from file ..."));
	QAction *actionSave = menu->addAction(tr("Save colors to file ..."));
	QAction *actionCopy = menu->addAction(tr("Copy"));
	QAction *actionPaste = menu->addAction(tr("Paste"));
	menu->addSeparator();
	LoadPresetsMenu(menu);

	const QAction *selectedItem = CommonMyWidgetWrapper::contextMenuEvent(event, menu);

	if (selectedItem)
	{
		if (selectedItem == actionAddColor) AddColor(event);
		if (selectedItem == actionRemoveColor) RemoveColor(event);
		if (selectedItem == actionSetOpacity) SetOpacity(event);
		if (selectedItem == actionAddOpacityStop) AddOpacityStopAt(event->x());
		if (selectedItem == actionRemoveOpacityStop) RemoveOpacityStop(opacityIndexUnderCursor);
		if (selectedItem == actionClear) Clear();
		if (selectedItem == actionChangeNumberOfColors) ChangeNumberOfColors();
		if (selectedItem == actionGrabColors) GrabColors();
		if (selectedItem == actionLoad) LoadColors();
		if (selectedItem == actionSave) SaveColors();
		if (selectedItem == actionCopy) SaveToClipboard();
		if (selectedItem == actionPaste) LoadFromClipboard();
		if (selectedItem && segmentModeActions.contains(const_cast<QAction *>(selectedItem)))
		{
			int mode = selectedItem->data().toInt();
			if (segmentIndexUnderCursor >= 0)
			{
				gradient.SetSegmentMode(segmentIndexUnderCursor, static_cast<cColorGradient::InterpolationMode>(mode));
				PushUndoState();
				emit update();
			}
		}
	}
}

void cGradientEditWidget::LoadPreset(QString presetGradient)
{
	if (!presetGradient.isEmpty())
	{
		gradient.SetColorsFromString(presetGradient);
		// Update the interpolation mode dropdown
		comboInterpolationMode->blockSignals(true);
		comboInterpolationMode->setCurrentIndex(static_cast<int>(gradient.GetInterpolationMode()));
		comboInterpolationMode->blockSignals(false);
		PushUndoState();
		emit update();
	}
}

void cGradientEditWidget::LoadPresetsMenu(QMenu *menu)
{
	QString presetsPath = QDir::toNativeSeparators(
		systemDirectories.GetDataDirectoryPublic() + QDir::separator() + "gradients" + QDir::separator() + "presets.json");
	
	QFile file(presetsPath);
	if (!file.open(QIODevice::ReadOnly))
	{
		// Try alternative location in user's home
		presetsPath = QDir::homePath() + QDir::separator() + ".mandelbulber" + QDir::separator() 
			+ "gradients" + QDir::separator() + "presets.json";
		file.setFileName(presetsPath);
		if (!file.open(QIODevice::ReadOnly))
		{
			QAction *actionNoPresets = menu->addAction(tr("No presets found"));
			actionNoPresets->setEnabled(false);
			return;
		}
	}
	
	QByteArray data = file.readAll();
	file.close();
	
	QJsonDocument doc = QJsonDocument::fromJson(data);
	if (doc.isNull() || !doc.isObject())
	{
		QAction *actionInvalid = menu->addAction(tr("Invalid presets file"));
		actionInvalid->setEnabled(false);
		return;
	}
	
	QJsonObject root = doc.object();
	QJsonArray presets = root.value("presets").toArray();
	
	if (presets.isEmpty())
	{
		QAction *actionEmpty = menu->addAction(tr("No presets available"));
		actionEmpty->setEnabled(false);
		return;
	}
	
	QMenu *presetsMenu = menu->addMenu(tr("Load preset"));
	for (int i = 0; i < presets.size(); i++)
	{
		QJsonObject preset = presets.at(i).toObject();
		QString name = preset.value("name").toString();
		QString description = preset.value("description").toString();
		QString gradientStr = preset.value("gradient").toString();
		
		if (!name.isEmpty() && !gradientStr.isEmpty())
		{
			QAction *action = presetsMenu->addAction(name);
			if (!description.isEmpty()) action->setToolTip(description);
			connect(action, &QAction::triggered, this, [this, gradientStr]() {
				LoadPreset(gradientStr);
			});
		}
	}
}

void cGradientEditWidget::pressedButtonRandomColors()
{
	for (int i = 1; i < gradient.GetNumberOfColors(); i++)
	{
		sRGB color(Random(255), Random(255), Random(255));
		gradient.ModifyColor(i, color);
		if (i == 1) gradient.ModifyColor(0, color);
	}
	PushUndoState();
	update();
}

void cGradientEditWidget::pressedButtonRandomColorsAndPositions()
{
	cRandom random;
	random.Initialize(QTime::currentTime().msec());

	int numberOfColors = random.Random(18) + 2;
	gradient.DeleteAll();
	for (int i = 0; i < numberOfColors; i++)
	{
		sRGB color(random.Random(255), random.Random(255), random.Random(255));
		float position = Random(10000) / 10000.0f;
		if (i == 0)
		{
			gradient.AddColor(color, 0.0f);
			gradient.AddColor(color, 1.0f);
		}
		else
		{
			gradient.AddColor(color, position);
		}
	}
	PushUndoState();
	update();
}

void cGradientEditWidget::pressedButtonBrightnessInc()
{
	for (int i = 1; i < gradient.GetNumberOfColors(); i++)
	{
		sRGB color = gradient.GetColorByIndex(i);
		color.R = qBound(0, int(color.R * 1.2), 255);
		color.G = qBound(0, int(color.G * 1.2), 255);
		color.B = qBound(0, int(color.B * 1.2), 255);
		gradient.ModifyColor(i, color);
		if (i == 1) gradient.ModifyColor(0, color);
	}
	PushUndoState();
	update();
}

void cGradientEditWidget::pressedButtonBrightnessDec()
{

	for (int i = 1; i < gradient.GetNumberOfColors(); i++)
	{
		sRGB color = gradient.GetColorByIndex(i);
		color.R = qBound(0, int(color.R * 0.8), 255);
		color.G = qBound(0, int(color.G * 0.8), 255);
		color.B = qBound(0, int(color.B * 0.8), 255);
		gradient.ModifyColor(i, color);
		if (i == 1) gradient.ModifyColor(0, color);
	}
	PushUndoState();
	update();
}

void cGradientEditWidget::pressedButtonSaturationInc()
{
	for (int i = 1; i < gradient.GetNumberOfColors(); i++)
	{
		sRGB color = gradient.GetColorByIndex(i);
		int average = (color.R + color.G + color.B) / 3;
		color.R = qBound(0, int((color.R - average) * 0.2 + color.R), 255);
		color.G = qBound(0, int((color.G - average) * 0.2 + color.G), 255);
		color.B = qBound(0, int((color.B - average) * 0.2 + color.B), 255);

		gradient.ModifyColor(i, color);
		if (i == 1) gradient.ModifyColor(0, color);
	}
	PushUndoState();
	update();
}

void cGradientEditWidget::pressedButtonSaturationDec()
{
	for (int i = 1; i < gradient.GetNumberOfColors(); i++)
	{
		sRGB color = gradient.GetColorByIndex(i);
		int average = (color.R + color.G + color.B) / 3;
		color.R = qBound(0, int((color.R - average) * -0.2 + color.R), 255);
		color.G = qBound(0, int((color.G - average) * -0.2 + color.G), 255);
		color.B = qBound(0, int((color.B - average) * -0.2 + color.B), 255);

		gradient.ModifyColor(i, color);
		if (i == 1) gradient.ModifyColor(0, color);
	}
	PushUndoState();
	update();
}

void cGradientEditWidget::pressedButtonInvert()
{
	for (int i = 1; i < gradient.GetNumberOfColors(); i++)
	{
		sRGB color = gradient.GetColorByIndex(i);
		color.R = qBound(0, 255 - color.R, 255);
		color.G = qBound(0, 255 - color.G, 255);
		color.B = qBound(0, 255 - color.B, 255);

		gradient.ModifyColor(i, color);
		if (i == 1) gradient.ModifyColor(0, color);
	}
	PushUndoState();
	update();
}

void cGradientEditWidget::resetToDefault()
{
	SetColors(defaultValue);
	update();
}

QString cGradientEditWidget::GetDefault()
{
	if (parameterContainer && !gotDefault)
	{
		defaultValue = parameterContainer->GetDefault<QString>(parameterName);
		setToolTipText();
		gotDefault = true;
	}
	return defaultValue;
}

QString cGradientEditWidget::getDefaultAsString()
{
	return GetColors();
}

QString cGradientEditWidget::getFullParameterName()
{
	return parameterName;
}

void cGradientEditWidget::interpolationModeChanged(int index)
{
	gradient.SetInterpolationMode(static_cast<cColorGradient::InterpolationMode>(index));
	PushUndoState();
	emit update();
}

void cGradientEditWidget::UpdateScriptAppearance(bool hasScript) {}
