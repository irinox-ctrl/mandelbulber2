/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2020-22 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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

#include "light_editor.h"

#include <QDebug>

#include "ui_light_editor.h"

#include "my_combo_box.h"

#include "src/automated_widgets.hpp"
#include "src/camera_target.hpp"
#include "src/light.h"
#include "src/fractal_container.hpp"
#include "src/interface.hpp"
#include "src/parameters.hpp"

cLightEditor::cLightEditor(QWidget *parent) : QWidget(parent), ui(new Ui::cLightEditor)
{
	ui->setupUi(this);

	automatedWidgets = new cAutomatedWidgets(this);
	automatedWidgets->ConnectSignalsForSlidersInWindow(this);

	connect(ui->comboBox_type, qOverload<int>(&MyComboBox::currentIndexChanged), this,
		&cLightEditor::slotChangedLightType);
	connect(ui->spinboxd3_rotation_x, qOverload<double>(&QDoubleSpinBox::valueChanged), this,
		&cLightEditor::slotChangedLightAngleX);
	connect(ui->spinboxd3_rotation_y, qOverload<double>(&QDoubleSpinBox::valueChanged), this,
		&cLightEditor::slotChangedLightAngleY);
	connect(ui->colorButton_color, &MyColorButton::valueChanged, this,
		&cLightEditor::slotChangedLightColor);
	connect(ui->widget_angle_preview, &cLightWidget::angleChanged, this,
		&cLightEditor::slotChangedLightAngles);
	connect(ui->checkBox_relative_position, &MyCheckBox::stateChanged, this,
		&cLightEditor::slotChangedRelativeMode);
	connect(ui->checkBox_use_target_point, &MyCheckBox::stateChanged, this,
		&cLightEditor::slotChangedUseTarget);
	connect(ui->pushButton_applyOrbit, &QPushButton::clicked, this,
		&cLightEditor::slotButtonApplyOrbit);
	connect(ui->pushButton_applyAutoIntensity, &QPushButton::clicked, this,
		&cLightEditor::slotButtonApplyAutoIntensity);

	slotChangedUseTarget(false);
}

cLightEditor::~cLightEditor()
{
	delete ui;
}

void cLightEditor::AssignLight(std::shared_ptr<cParameterContainer> params, int index)
{
	if (isLightAssigned)
	{
		qCritical() << "Material is already assigned!";
	}
	else
	{
		lightIndex = index;
		parameterContainer = params;
		isLightAssigned = true;

		QList<QWidget *> lightWidgets = findChildren<QWidget *>();
		for (auto &lightWidget : lightWidgets)
		{
			if (!lightWidget->objectName().isEmpty())
			{
				QString objectName = lightWidget->objectName();
				int posOfDash = objectName.indexOf('_');
				if (posOfDash > 0)
				{
					QString newName = objectName.insert(posOfDash, QString("_light%1").arg(index));
					lightWidget->setObjectName(newName);
				}
			}
		}
	}
}

void cLightEditor::slotChangedLightType(int index)
{
	cLight::enumLightType lightType = static_cast<cLight::enumLightType>(index);

	bool useTarget = ui->checkBox_use_target_point->isChecked();

	ui->groupBox_cone_options->setEnabled(lightType == cLight::lightConical);
	ui->groupBox_projection_options->setEnabled(lightType == cLight::lightProjection);
	ui->widget_angle_preview->setEnabled(lightType == cLight::lightDirectional);

	bool visibleTarget = useTarget || (lightType == cLight::lightBeam);
	bool visibleAngle = !useTarget && (lightType != cLight::lightBeam);

	ui->checkBox_use_target_point->setVisible(lightType != cLight::lightBeam);

	ui->label_angle->setVisible(visibleAngle);
	ui->label_horizontal->setVisible(visibleAngle);
	ui->label_vertical->setVisible(visibleAngle);
	ui->label_roll->setVisible(visibleAngle);

	ui->spinboxd3_rotation_x->setVisible(visibleAngle);
	ui->spinboxd3_rotation_y->setVisible(visibleAngle);
	ui->spinboxd3_rotation_z->setVisible(visibleAngle);

	ui->label_target->setVisible(visibleTarget);
	ui->label_target_x->setVisible(visibleTarget);
	ui->label_target_y->setVisible(visibleTarget);
	ui->label_target_z->setVisible(visibleTarget);

	ui->vect3_target_x->setVisible(visibleTarget);
	ui->vect3_target_y->setVisible(visibleTarget);
	ui->vect3_target_z->setVisible(visibleTarget);
}

void cLightEditor::slotChangedLightAngleX(double angle)
{
	double newLightAngle = angle / 180.0 * M_PI;
	if (newLightAngle != lightAngleAlpha)
	{
		lightAngleAlpha = newLightAngle;
		CVector3 lightAngle(-lightAngleAlpha, lightAngleBeta, 0.0);
		ui->widget_angle_preview->SetLightAngle(lightAngle);
	}
}

void cLightEditor::slotChangedLightAngleY(double angle)
{
	double newLightAngle = angle / 180.0 * M_PI;
	if (newLightAngle != lightAngleBeta)
	{
		lightAngleBeta = newLightAngle;
		CVector3 lightAngle(-lightAngleAlpha, lightAngleBeta, 0.0);
		ui->widget_angle_preview->SetLightAngle(lightAngle);
	}
}

void cLightEditor::slotChangedLightColor()
{
	sRGB color = ui->colorButton_color->GetColor();
	sRGBFloat fColor(color.R / 65535.0, color.G / 65535.0, color.B / 65535.0);
	ui->widget_angle_preview->SetLightColor(fColor);
}

void cLightEditor::slotChangedLightAngles(double alpha, double beta)
{
	ui->spinboxd3_rotation_x->setValue(-alpha * 180.0 / M_PI);
	ui->spinboxd3_rotation_y->setValue(-beta * 180.0 / M_PI);
}

void cLightEditor::slotChangedRelativeMode(int state)
{
	ui->widget_angle_preview->SetRelativeMode(bool(state));
}

void cLightEditor::slotChangedUseTarget(int state)
{
	ui->label_angle->setVisible(!state);
	ui->label_horizontal->setVisible(!state);
	ui->label_vertical->setVisible(!state);
	ui->label_roll->setVisible(!state);

	ui->spinboxd3_rotation_x->setVisible(!state);
	ui->spinboxd3_rotation_y->setVisible(!state);
	ui->spinboxd3_rotation_z->setVisible(!state);

	ui->label_target->setVisible(state);
	ui->label_target_x->setVisible(state);
	ui->label_target_y->setVisible(state);
	ui->label_target_z->setVisible(state);

	ui->vect3_target_x->setVisible(state);
	ui->vect3_target_y->setVisible(state);
	ui->vect3_target_z->setVisible(state);
}

void cLightEditor::slotButtonApplyAutoIntensity()
{
	if (!parameterContainer || lightIndex < 0) return;

	CVector3 cam = parameterContainer->Get<CVector3>("camera");
	CVector3 target = parameterContainer->Get<CVector3>("target");
	CVector3 top = parameterContainer->Get<CVector3>("camera_top");
	CVector3 lightPosParam = parameterContainer->Get<CVector3>(cLight::Name("position", lightIndex));
	bool relativePosition = parameterContainer->Get<bool>(cLight::Name("relative_position", lightIndex));

	CVector3 lightPosWorld;
	if (relativePosition)
	{
		cCameraTarget cameraTarget(cam, target, top);
		CVector3 deltaRotated = cameraTarget.GetForwardVector() * lightPosParam.z
														+ cameraTarget.GetTopVector() * lightPosParam.y
														+ cameraTarget.GetRightVector() * lightPosParam.x;
		lightPosWorld = cam + deltaRotated;
	}
	else
	{
		lightPosWorld = lightPosParam;
	}

	double dist = cInterface::GetDistanceForPoint(lightPosWorld, parameterContainer, gParFractal);
	double factor = parameterContainer->Get<double>(cLight::Name("auto_intensity_factor", lightIndex));

	// Physical inverse-square law: intensity proportional to distance^2
	// At distance 1, intensity = 1. At distance 10, intensity = 100.
	double newIntensity = dist * dist * factor;

	parameterContainer->Set(cLight::Name("intensity", lightIndex), newIntensity);

	ui->logedit_intensity->blockSignals(true);
	ui->logedit_intensity->setText(QString("%L1").arg(newIntensity, 0, 'g', 15));
	ui->logedit_intensity->blockSignals(false);
}

void cLightEditor::slotButtonApplyOrbit()
{
	if (!parameterContainer || lightIndex < 0) return;

	double distance = parameterContainer->Get<double>(cLight::Name("orbit_distance", lightIndex));
	double yaw = parameterContainer->Get<double>(cLight::Name("orbit_yaw", lightIndex));
	double pitch = parameterContainer->Get<double>(cLight::Name("orbit_pitch", lightIndex));

	CVector3 target = parameterContainer->Get<CVector3>("target");

	// Spherical to cartesian (yaw = horizontal angle, pitch = vertical angle)
	double yawRad = yaw * M_PI / 180.0;
	double pitchRad = pitch * M_PI / 180.0;

	CVector3 offset;
	offset.x = distance * cos(pitchRad) * sin(yawRad);
	offset.y = distance * sin(pitchRad);
	offset.z = distance * cos(pitchRad) * cos(yawRad);

	CVector3 newPos = target + offset;

	bool relativePosition =
		parameterContainer->Get<bool>(cLight::Name("relative_position", lightIndex));

	if (relativePosition)
	{
		CVector3 cam = parameterContainer->Get<CVector3>("camera");
		CVector3 camTarget = parameterContainer->Get<CVector3>("target");
		CVector3 top = parameterContainer->Get<CVector3>("camera_top");
		cCameraTarget cameraTarget(cam, camTarget, top);
		CVector3 delta = newPos - cam;
		newPos.x = cameraTarget.GetRightVector().Dot(delta);
		newPos.y = cameraTarget.GetTopVector().Dot(delta);
		newPos.z = cameraTarget.GetForwardVector().Dot(delta);
	}

	parameterContainer->Set(cLight::Name("position", lightIndex), newPos);

	// Update position line edits directly
	ui->vect3_position_x->blockSignals(true);
	ui->vect3_position_y->blockSignals(true);
	ui->vect3_position_z->blockSignals(true);
	ui->vect3_position_x->setText(QString("%L1").arg(newPos.x, 0, 'g', 15));
	ui->vect3_position_y->setText(QString("%L1").arg(newPos.y, 0, 'g', 15));
	ui->vect3_position_z->setText(QString("%L1").arg(newPos.z, 0, 'g', 15));
	ui->vect3_position_x->blockSignals(false);
	ui->vect3_position_y->blockSignals(false);
	ui->vect3_position_z->blockSignals(false);
}
