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

#ifndef MANDELBULBER2_QT_GRADIENT_EDIT_WIDGET_H_
#define MANDELBULBER2_QT_GRADIENT_EDIT_WIDGET_H_

#include <QComboBox>
#include <QElapsedTimer>
#include <QSlider>
#include <QToolButton>
#include <QWidget>

#include "common_my_widget_wrapper.h"

#include "src/color_gradient.h"

class cGradientEditWidget : public QWidget, public CommonMyWidgetWrapper
{
	Q_OBJECT
public:
	enum class DisplayMode
	{
		BothPanels,
		OpacityOnly,
		ColorOnly
	};

	cGradientEditWidget(QWidget *parent = nullptr);
	~cGradientEditWidget() override;
	void SetGrayscale();
	void SetViewModeOnly();
	void SetDisplayMode(DisplayMode mode);
	QString GetColors() { return gradient.GetColorsAsString(); }
	void SetColors(const QString &colorsString);
	cColorGradient &GetGradient() { return gradient; }
	void NotifyGradientChanged();
	std::shared_ptr<cParameterContainer> GetParameterContainer() const { return parameterContainer; }
	QString GetParameterName() const { return parameterName; }

	// methods to define from CommonMyWidgetWrapper
	void resetToDefault() override;
	QString getDefaultAsString() override;
	QString getFullParameterName() override;
	void UpdateScriptAppearance(bool hasScript) override;

private:
	void paintEvent(QPaintEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseDoubleClickEvent(QMouseEvent *event) override;
	void contextMenuEvent(QContextMenuEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;
	void leaveEvent(QEvent *event) override;
	void resizeEvent(QResizeEvent *event) override;

	void PaintButton(const cColorGradient::sColor &posColor, QPainter &painter, int colorPanelTop);
	void PaintMidpointHandle(int segmentIndex, QPainter &painter, int colorPanelTop);
	void PaintOpacityStop(const cColorGradient::sOpacityStop &stop, int index, QPainter &painter, int opacityPanelTop, int opacityPanelHeight);
	void PaintOpacityCurve(QPainter &painter, int opacityPanelTop, int opacityPanelHeight);
	void PaintOpacityMidpointHandle(int segmentIndex, QPainter &painter, int opacityPanelTop);
	int CalcButtonPosition(float colorPosition);
	int CalcMidpointPosition(int segmentIndex);
	int CalcOpacityMidpointPosition(int segmentIndex);
	int FindButtonAtPosition(int x, int y);
	int FindMidpointAtPosition(int x, int y);
	int FindOpacityStopAtPosition(int x, int y);
	int FindOpacityMidpointAtPosition(int x, int y);
	void AddColor(QContextMenuEvent *event);
	void RemoveColor(QContextMenuEvent *event);
	void SetOpacity(QContextMenuEvent *event);
	void AddOpacityStopAt(int x, float opacity = -1.0f);
	void RemoveOpacityStop(int index);
	void Clear();
	void PushUndoState();
	void Undo();
	void Redo();
	void ChangeNumberOfColors();
	void GrabColors();
	void LoadColors();
	void SaveColors();
	void LoadPreset(QString presetGradient);
	void LoadPresetsMenu(QMenu *menu);
	bool DecodeGradientFromFile(QString string);
	void LoadFromClipboard();
	void SaveToClipboard();
	void AddToolButton(QToolButton *button, int position, QString iconName);
	QString GetDefault();
	QString GetInterpolationModeLabel(cColorGradient::InterpolationMode mode) const;

private slots:
	void pressedButtonRandomColors();
	void pressedButtonRandomColorsAndPositions();
	void pressedButtonBrightnessInc();
	void pressedButtonBrightnessDec();
	void pressedButtonSaturationInc();
	void pressedButtonSaturationDec();
	void pressedButtonInvert();
	void interpolationModeChanged(int index);
	void midpointIntensityChanged(int value);

private:
	cColorGradient gradient;
	int buttonWidth;
	int margins;
	bool mouseDragStarted;
	bool isDraggingMidpoint;
	bool isDraggingOpacityStop;
	bool isDraggingOpacityMidpoint;
	int pressedColorIndex;
	int pressedMidpointIndex;
	int pressedOpacityIndex;
	int pressedOpacityMidpointIndex;
	int hoveredMidpointIndex;
	int hoveredOpacityMidpointIndex;
	int dragStartX;
	int dragStartY;
	int toolbarHeight;
	bool viewMode;
	int fixHeight;
	bool grayscale;

	QString defaultValue;
	QVector<QString> undoStack;
	int undoIndex;

	QToolButton *buttonRandomColors;
	QToolButton *buttonRandomColorsAndPositions;
	QToolButton *buttonBrightnessInc;
	QToolButton *buttonBrightnessDec;
	QToolButton *buttonSaturationInc;
	QToolButton *buttonSaturationDec;
	QToolButton *buttonPaletteInvert;
	QComboBox *comboInterpolationMode;
	QSlider *sliderMidpointIntensity;

signals:
	void openEditor();
	void openEditorForMode(int mode);
	void gradientModified();

private:
	DisplayMode displayMode;
	bool popupMode;
	bool initialized;
	QElapsedTimer dragUpdateTimer;
};

#endif /* MANDELBULBER2_QT_GRADIENT_EDIT_WIDGET_H_ */
