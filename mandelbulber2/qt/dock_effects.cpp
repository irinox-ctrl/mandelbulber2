/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2016-24 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * Widget which contains UI for effects
 */

#include "dock_effects.h"

#include "ui_dock_effects.h"

#include <algorithm>

#include <QtGlobal>

#include <QApplication>
#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QRegularExpression>

#include "dock_image_adjustments.h"
#include "navigator_window.h"

#include "src/ao_modes.h"
#include "src/automated_widgets.hpp"
#include "src/fractal_container.hpp"
#include "src/initparameters.hpp"
#include "src/interface.hpp"
#include "src/primitives.h"
#include "src/random.hpp"
#include "src/render_window.hpp"
#include "src/rendered_image_widget.hpp"
#include "src/synchronize_interface.hpp"
#include "src/system_data.hpp"

cDockEffects::cDockEffects(QWidget *parent)
		: QWidget(parent), cMyWidgetWithParams(), ui(new Ui::cDockEffects)
{
	ui->setupUi(this);

	automatedWidgets = new cAutomatedWidgets(this);
	automatedWidgets->ConnectSignalsForSlidersInWindow(this);
	ConnectSignals();
	InstallSingleTrapPlacementHelp();

	// Initialize size2 visibility based on current shape selection
	for (int i = 1; i <= 20; i++)
	{
		QComboBox *shapeCombo = findChild<QComboBox *>(
			QString("comboBox_single_trap_light_%1_shape").arg(i));
		if (shapeCombo)
		{
			int shape = shapeCombo->currentIndex();
			bool usesSize2 = SingleTrapShapeUsesSecondSize(shape);
			QLabel *label = findChild<QLabel *>(
				QString("label_single_trap_light_%1_size2").arg(i));
			QWidget *edit = findChild<QWidget *>(
				QString("logedit_single_trap_light_%1_size2").arg(i));
			if (label) label->setVisible(usesSize2);
			if (edit) edit->setVisible(usesSize2);
		}
	}
}

bool cDockEffects::SingleTrapShapeUsesSecondSize(int shapeIndex)
{
	// Plane (12) only uses primary size; torus–disc need thickness / secondary radius.
	return shapeIndex >= 6 && shapeIndex != 12;
}

void cDockEffects::EnsureSingleTrapEngineOnAndActiveThrough(int layerIndex)
{
	if (layerIndex < 1 || layerIndex > 20) return;
	gPar->Set("fake_lights_enabled", false);
	gPar->Set("single_trap_lights_enabled", true);
	int cur = gPar->Get<int>("single_trap_lights_active_count");
	int n = std::max(cur, layerIndex);
	n = std::min(n, 20);
	gPar->Set("single_trap_lights_active_count", n);
	if (ui->groupCheck_single_trap_lights_enabled)
		ui->groupCheck_single_trap_lights_enabled->setChecked(true);
	if (ui->spinboxInt_single_trap_lights_active_count)
		ui->spinboxInt_single_trap_lights_active_count->setValue(n);
}

void cDockEffects::SyncSingleTrapActiveCountToHighestEnabledLayer()
{
	int maxOn = 0;
	for (int i = 1; i <= 20; i++)
	{
		if (gPar->Get<bool>(QString("single_trap_light_%1_enabled").arg(i))) maxOn = i;
	}
	if (maxOn < 1) return;
	gPar->Set("single_trap_lights_active_count", maxOn);
	if (ui->spinboxInt_single_trap_lights_active_count)
		ui->spinboxInt_single_trap_lights_active_count->setValue(maxOn);
}

double cDockEffects::SingleTrapForwardAlongView(double camTargetDist)
{
	return std::max(camTargetDist * 0.48, 1.8);
}

double cDockEffects::SingleTrapRadialClearance(const QString &prefix) const
{
	const double rs = std::max(1e-8, fabs(gPar->Get<double>(prefix + "_relative_size")));
	const double sz1 = fabs(gPar->Get<double>(prefix + "_size"));
	const double sz2 = fabs(gPar->Get<double>(prefix + "_size2"));
	const double es = fabs(gPar->Get<double>(prefix + "_edge_softness"));
	const double th = std::max(gPar->Get<double>(prefix + "_thickness"), 1e-6);
	const int shape = gPar->Get<int>(prefix + "_shape");
	const double orbitR = fabs(gPar->Get<double>(prefix + "_anim_orbit_radius"));

	const double geomExtent = std::max(std::max(sz1, sz2), 1e-6) + es;
	const double bodyRadius = geomExtent * rs;

	double clearance = bodyRadius * 2.9 + orbitR + 0.55 * th;
	if (shape == 12)
		clearance = std::max(clearance, (sz1 + es) * rs * 2.2);
	else if (shape == 1)
		clearance = std::max(clearance, sz1 * rs * 3.2);
	else if (shape == 13)
		clearance = std::max(clearance, (std::max(sz1, sz2) + es) * rs * 2.6);

	return clearance;
}

double cDockEffects::SingleTrapPlacementBumpFromView(const QString &prefix, double camTargetLen) const
{
	double bump = SingleTrapRadialClearance(prefix);
	const int shape = gPar->Get<int>(prefix + "_shape");
	const double sz1 = fabs(gPar->Get<double>(prefix + "_size"));
	const double es = fabs(gPar->Get<double>(prefix + "_edge_softness"));
	const double rs = std::max(1e-8, fabs(gPar->Get<double>(prefix + "_relative_size")));
	if (shape == 12)
		bump = std::max(bump, camTargetLen * 0.22 + (sz1 + es) * rs * 1.8);
	else if (shape == 1)
		bump = std::max(bump, sz1 * rs * 2.8 + camTargetLen * 0.12);
	else if (shape == 13)
	{
		const double sz2 = fabs(gPar->Get<double>(prefix + "_size2"));
		bump = std::max(bump, (std::max(sz1, sz2) + es) * rs * 2.2);
	}
	return std::max(bump, 0.12);
}

bool cDockEffects::SingleTrapRaymarchFirstSurface(
	const CVector3 &origin, const CVector3 &dirUnit, CVector3 *hitPoint) const
{
	CVector3 point = origin;
	double totalDist = 0.0;
	const double maxDist = 100.0;
	for (int i = 0; i < 1000; i++)
	{
		double dist = cInterface::GetDistanceForPoint(point, gPar, gParFractal);
		if (dist < 1e-6)
		{
			*hitPoint = point;
			return true;
		}
		if (totalDist > maxDist) break;
		point += dirUnit * dist;
		totalDist += dist;
	}
	*hitPoint = point;
	return false;
}

void cDockEffects::InstallSingleTrapPlacementHelp()
{
	const QString posTip = QStringLiteral(
		"Middelpunt van de vorm in wereldruimte (positiemodus «absolute»). "
		"Elke lamp heeft eigen X,Y,Z — ze staan niet aan elkaar gekoppeld.");
	const QString rsTip = QStringLiteral(
		"1,0 aanbevolen voor voorspelbare plaatsing: dit veld is het echte midden in de scene. "
		"Andere waarden schalen alleen de vorm rond dat punt.");
	const QString shapeTip = QStringLiteral(
		"Bol: grootte = straal; randzachtheid hieronder maakt de rand zachter. "
		"Lijn: na rotatie ligt de lijn langs de lokale X-as; grootte = half de dikte van de buis (Y/Z).");
	const QString edgeTip = QStringLiteral(
		"Zachtere overgang aan de rand van de lichtvorm (geen koppeling met andere lampen).");
	const QString modeTip = QStringLiteral(
		"Voor vaste coördinaten: «absolute». Andere opties verschuiven t.o.v. camera, fractal center of doel.");

	for (int i = 1; i <= 20; i++)
	{
		if (QLabel *l = findChild<QLabel *>(QStringLiteral("label_single_trap_light_%1_position").arg(i)))
			l->setToolTip(posTip);
		if (QWidget *w = findChild<QWidget *>(QStringLiteral("logedit_single_trap_light_%1_relative_size").arg(i)))
			w->setToolTip(rsTip);
		if (QLabel *l = findChild<QLabel *>(QStringLiteral("label_single_trap_light_%1_shape").arg(i)))
			l->setToolTip(shapeTip);
		if (QComboBox *c = findChild<QComboBox *>(QStringLiteral("comboBox_single_trap_light_%1_shape").arg(i)))
			c->setToolTip(shapeTip);
		if (QLabel *l = findChild<QLabel *>(QStringLiteral("label_single_trap_light_%1_edge_softness").arg(i)))
			l->setToolTip(edgeTip);
		if (QComboBox *c = findChild<QComboBox *>(QStringLiteral("comboBox_single_trap_light_%1_position_mode").arg(i)))
			c->setToolTip(modeTip);
	}
}

cDockEffects::~cDockEffects()
{
	delete ui;
}

void cDockEffects::ConnectSignals() const
{
	connect(ui->comboBox_fake_lights_position_mode, SIGNAL(currentIndexChanged(int)),
		ui->stackedWidget_fake_lights_mode, SLOT(setCurrentIndex(int)));

	connect(ui->pushButton_reset_world, SIGNAL(clicked()), this, SLOT(slotPressedButtonResetWorld()));
	connect(ui->pushButton_reset_camera, SIGNAL(clicked()), this, SLOT(slotPressedButtonResetCamera()));
	connect(ui->pushButton_reset_target, SIGNAL(clicked()), this, SLOT(slotPressedButtonResetTarget()));
	connect(ui->pushButton_reset_fractal_center, SIGNAL(clicked()), this, SLOT(slotPressedButtonResetFractalCenter()));
	connect(ui->pushButton_reset_path_circle, SIGNAL(clicked()), this, SLOT(slotPressedButtonResetPathCircle()));
	connect(ui->pushButton_reset_path_spiral, SIGNAL(clicked()), this, SLOT(slotPressedButtonResetPathSpiral()));
	connect(ui->pushButton_reset_orbit_target, SIGNAL(clicked()), this, SLOT(slotPressedButtonResetOrbitTarget()));
	connect(ui->pushButton_reset_multi_center, SIGNAL(clicked()), this, SLOT(slotPressedButtonResetMultiCenter()));

	connect(ui->button_calculateFog, SIGNAL(clicked()), this, SLOT(slotPressedButtonAutoFog()));

	connect(ui->comboBox_ambient_occlusion_mode, SIGNAL(currentIndexChanged(int)), this,
		SLOT(slotChangedComboAmbientOcclusionMode(int)));

	connect(ui->logedit_aux_light_manual_placement_dist, SIGNAL(textChanged(const QString &)), this,
		SLOT(slotEditedLineEditManualLightPlacementDistance(const QString &)));

	connect(
		ui->pushButton_DOF_set_focus, SIGNAL(clicked()), this, SLOT(slotPressedButtonSetDOFByMouse()));
	connect(
		ui->pushButton_DOF_update, SIGNAL(clicked()), this, SLOT(slotPressedButtonUpdatePostEffects()));
	connect(ui->pushButton_post_effects_update, SIGNAL(clicked()), this,
		SLOT(slotPressedButtonUpdatePostEffects()));

	connect(ui->pushButton_set_fog_by_mouse, SIGNAL(clicked()), this,
		SLOT(slotPressedButtonSetFogByMouse()));
	connect(ui->pushButton_place_random_lights_by_mouse, SIGNAL(clicked()), this,
		SLOT(slotPressedButtonPlaceRandomLightsByMouse()));

	connect(ui->toolButton_fog_distance_double, &QToolButton::clicked, this,
		&cDockEffects::slotPressedButtonFogDistDouble);

	connect(ui->toolButton_fog_distance_half, &QToolButton::clicked, this,
		&cDockEffects::slotPressedButtonFogDistHalf);

	connect(ui->checkBox_aux_light_place_behind, SIGNAL(stateChanged(int)), this,
		SLOT(slotChangedPlaceLightBehindObjects(int)));

	connect(ui->groupCheck_DOF_monte_carlo, SIGNAL(toggled(bool)), this,
		SLOT(slotChangedEnableMCDOF(bool)));
	connect(ui->checkBox_DOF_MC_global_illumination, SIGNAL(stateChanged(int)), this,
		SLOT(slotChangedEnableGI(int)));
	connect(ui->checkBox_MC_global_illumination_volumetric, SIGNAL(stateChanged(int)), this,
		SLOT(slotChangedEnableGIVolumetric(int)));
	connect(ui->checkBox_MC_fog_illumination, SIGNAL(stateChanged(int)), this,
		SLOT(slotChangedEnableGIFog(int)));

	connect(ui->comboBox_random_lights_coloring_type, SIGNAL(currentIndexChanged(int)), this,
		SLOT(slotRandomLightColoringTypeChanged(int)));

	connect(ui->pushButton_clouds_randomize, &QPushButton::clicked, this,
		&cDockEffects::slotPressedButtonCloudsRandomize);

	connect(ui->widget_light_sources_manager,
		&cLightSourcesManager::signalChangeLightPlacementDistance, this,
		&cDockEffects::slotSetAuxLightManualPlacementDistance);

	connect(ui->groupCheck_env_mapping_enable, &QGroupBox::toggled, this,
		&cDockEffects::slotEnvMappingToggled);

	for (int i = 1; i <= 20; i++)
	{
		QPushButton *button = findChild<QPushButton *>(
			QString("pushButton_single_trap_light_%1_place_camera").arg(i));
		if (button)
		{
			connect(button, &QPushButton::clicked, this, &cDockEffects::slotPressedButtonPlaceLightAtCamera);
		}

		QPushButton *surfaceButton = findChild<QPushButton *>(
			QString("pushButton_single_trap_light_%1_place_surface").arg(i));
		if (surfaceButton)
		{
			connect(surfaceButton, &QPushButton::clicked, this,
				&cDockEffects::slotPressedButtonPlaceSingleTrapLightAtSurface);
		}

		QPushButton *targetButton = findChild<QPushButton *>(
			QString("pushButton_single_trap_light_%1_place_target").arg(i));
		if (targetButton)
		{
			connect(targetButton, &QPushButton::clicked, this,
				&cDockEffects::slotPressedButtonPlaceSingleTrapLightAtTarget);
		}

		QComboBox *shapeCombo = findChild<QComboBox *>(
			QString("comboBox_single_trap_light_%1_shape").arg(i));
		if (shapeCombo)
		{
			connect(shapeCombo, SIGNAL(currentIndexChanged(int)), this,
				SLOT(slotChangedSingleTrapLightShape(int)));
		}
	}

	connect(ui->pushButton_single_trap_copy, &QPushButton::clicked, this,
		&cDockEffects::slotPressedButtonCopySingleTrapLight);

	connect(ui->pushButton_single_trap_randomize, &QPushButton::clicked, this,
		&cDockEffects::slotPressedButtonRandomizeSingleTrapLight);

	connect(ui->pushButton_single_trap_world_anchor, &QPushButton::clicked, this,
		&cDockEffects::slotPressedButtonSingleTrapWorldAnchor);

	connect(ui->pushButton_single_trap_randomize_all, &QPushButton::clicked, this,
		&cDockEffects::slotPressedButtonRandomizeAllSingleTrapLights);

	connect(ui->pushButton_single_trap_preset_apply, &QPushButton::clicked, this,
		&cDockEffects::slotPressedButtonSingleTrapPresetApply);

	connect(ui->pushButton_single_trap_reset_all, &QPushButton::clicked, this,
		&cDockEffects::slotPressedButtonSingleTrapResetAll);

	connect(
		ui->pushButton_local_navi, &QPushButton::clicked, this, &cDockEffects::slotPressedButtonNavi);

	connect(ui->checkB_MCShowNoiseLevels, &QCheckBox::toggled, this,
		&cDockEffects::changedMCNoiseVisibility);
}

void cDockEffects::slotSynchronizeInterfaceBasicFog(std::shared_ptr<cParameterContainer> par) const
{
	SynchronizeInterfaceWindow(ui->groupCheck_basic_fog_enabled, par, qInterface::write);
}

void cDockEffects::slotSynchronizeInterfaceDOF(std::shared_ptr<cParameterContainer> par) const
{
	SynchronizeInterfaceWindow(ui->groupCheck_DOF_enabled, par, qInterface::write);
}

void cDockEffects::slotSynchronizeInterfaceLights(std::shared_ptr<cParameterContainer> par) const
{
	SynchronizeInterfaceWindow(ui->widget_light_sources_manager, par, qInterface::write);
}

void cDockEffects::slotSynchronizeInterfaceRandomLights(
	std::shared_ptr<cParameterContainer> par) const
{
	SynchronizeInterfaceWindow(ui->groupCheck_random_lights_group, par, qInterface::write);
}

double cDockEffects::GetAuxLightManualPlacementDistance() const
{
	return systemData.locale.toDouble(ui->logedit_aux_light_manual_placement_dist->text());
}

void cDockEffects::slotSetAuxLightManualPlacementDistance(double dist) const
{
	ui->logedit_aux_light_manual_placement_dist->setText(QString("%L1").arg(dist));
}

void cDockEffects::slotEditedLineEditManualLightPlacementDistance(const QString &text)
{
	renderedImageWidget->SetFrontDist(systemData.locale.toDouble(text));
}

void cDockEffects::slotChangedPlaceLightBehindObjects(int state)
{
	renderedImageWidget->SetPlaceBehindObjects(state);
}

void cDockEffects::slotChangedComboAmbientOcclusionMode(int index) const
{
	bool enabled = index == params::AOModeMultipleRays ? true : false;
	ui->frame_lightmap_texture->setEnabled(enabled);
	enabled = index == params::AOModeFast ? true : false;
	ui->spinbox_ambient_occlusion_fast_tune->setEnabled(enabled);
}

void cDockEffects::slotPressedButtonAutoFog()
{
	SynchronizeInterfaceWindow(this, params, qInterface::read);
	gMainInterface->AutoFog(params, fractalParams);
	SynchronizeInterfaceWindow(this, params, qInterface::write);
}

void cDockEffects::slotPressedButtonUpdatePostEffects()
{
	emit signalRefreshPostEffects();
}

void cDockEffects::slotPressedButtonSetDOFByMouse()
{
	QList<QVariant> item;
	item.append(int(RenderedImage::clickDOFFocus));
	int index = mouseFunctionComboWidget->findData(item);
	mouseFunctionComboWidget->setCurrentIndex(index);
	renderedImageWidget->setClickMode(item);
}

void cDockEffects::slotPressedButtonSetFogByMouse()
{
	QList<QVariant> item;
	item.append(int(RenderedImage::clickFogVisibility));
	int index = mouseFunctionComboWidget->findData(item);
	mouseFunctionComboWidget->setCurrentIndex(index);
	renderedImageWidget->setClickMode(item);
}

void cDockEffects::slotPressedButtonPlaceRandomLightsByMouse()
{
	QList<QVariant> item;
	item.append(int(RenderedImage::clickPlaceRandomLightCenter));
	int index = mouseFunctionComboWidget->findData(item);
	mouseFunctionComboWidget->setCurrentIndex(index);
	renderedImageWidget->setClickMode(item);
}

void cDockEffects::UpdateLabelAverageDOFSamples(const QString &avg)
{
	ui->label_average_DOF_samples->setText(avg);
}

void cDockEffects::UpdateLabelAverageDOFNoise(const QString &avg)
{
	ui->label_average_DOF_noise->setText(avg);
}

void cDockEffects::UpdateLabelMaskedPixels(const QString &avg)
{
	ui->label_masked_pixels->setText(avg);
}

void cDockEffects::UpdateLabelTilesDone(const QString &avg)
{
	ui->label_tiles_done->setText(avg);
}

void cDockEffects::slotChangedEnableMCDOF(bool state)
{
	if (state)
	{
		params::enumAOMode AOMode =
			params::enumAOMode(ui->comboBox_ambient_occlusion_mode->currentIndex());
		if (AOMode == params::AOModeScreenSpace)
		{
			ui->groupCheck_ambient_occlusion_enabled->setChecked(false);
		}
	}
}

void cDockEffects::slotChangedEnableGI(int state)
{
	ui->checkBox_MC_global_illumination_volumetric->setEnabled(state);
	ui->checkBox_MC_fog_illumination->setEnabled(state);
}

void cDockEffects::slotChangedEnableGIVolumetric(int state)
{
	if (state == Qt::Checked) ui->checkBox_MC_fog_illumination->setChecked(false);
}

void cDockEffects::slotChangedEnableGIFog(int state)
{
	if (state == Qt::Checked) ui->checkBox_MC_global_illumination_volumetric->setChecked(false);
}

void cDockEffects::slotPressedButtonCloudsRandomize()
{
	cRandom random;
	random.Initialize(QTime::currentTime().msec());
	int rnd = random.Random(100000);
	ui->spinboxInt_clouds_random_seed->setValue(rnd);
}

void cDockEffects::RegenerateLights()
{
	ui->widget_light_sources_manager->Regenerate();
}

void cDockEffects::slotPressedButtonNavi()
{
	gMainInterface->SynchronizeInterface(params, fractalParams, qInterface::read);
	cNavigatorWindow *navigator = new cNavigatorWindow();
	cDockEffects *leftWidget = new cDockEffects();
	navigator->AddLeftWidget(leftWidget);
	navigator->setAttribute(Qt::WA_DeleteOnClose);
	navigator->SetInitialParameters(params, fractalParams);
	navigator->SynchronizeInterface(qInterface::write);
	navigator->SetMouseClickFunction(gMainInterface->GetMouseClickFunction());

	connect(navigator, &cNavigatorWindow::signalChangesAccepted, this,
		&cDockEffects::slotNewParametersFromNavi);

	navigator->show();
	navigator->AllPrepared();
}

void cDockEffects::AssignParameterContainers(
	std::shared_ptr<cParameterContainer> _params, std::shared_ptr<cFractalContainer> _fractalParams)
{
	cMyWidgetWithParams::AssignParameterContainers(_params, _fractalParams);
	ui->widget_light_sources_manager->AssignParameterContainers(_params, _fractalParams);

	ui->widget_light_sources_manager->Init();
}

void cDockEffects::AssignSpecialWidgets(
	RenderedImage *_renderedImage, QComboBox *_mouseFunctionCombo)
{
	cMyWidgetWithParams::AssignSpecialWidgets(_renderedImage, _mouseFunctionCombo);
	ui->widget_light_sources_manager->AssignSpecialWidgets(
		renderedImageWidget, mouseFunctionComboWidget);
}

void cDockEffects::slotNewParametersFromNavi()
{
	RegenerateLights();
}

void cDockEffects::slotPressedButtonFogDistDouble()
{
	SynchronizeInterfaceWindow(this, params, qInterface::read);

	params->Set("volumetric_fog_colour_1_distance",
		params->Get<double>("volumetric_fog_colour_1_distance") * 2.0);

	params->Set("volumetric_fog_colour_2_distance",
		params->Get<double>("volumetric_fog_colour_2_distance") * 2.0);

	params->Set(
		"volumetric_fog_distance_factor", params->Get<double>("volumetric_fog_distance_factor") * 2.0);

	params->Set("volumetric_fog_distance_from_surface",
		params->Get<double>("volumetric_fog_distance_from_surface") * 2.0);

	SynchronizeInterfaceWindow(this, params, qInterface::write);
}

void cDockEffects::slotPressedButtonFogDistHalf()
{
	SynchronizeInterfaceWindow(this, params, qInterface::read);

	params->Set("volumetric_fog_colour_1_distance",
		params->Get<double>("volumetric_fog_colour_1_distance") / 2.0);

	params->Set("volumetric_fog_colour_2_distance",
		params->Get<double>("volumetric_fog_colour_2_distance") / 2.0);

	params->Set(
		"volumetric_fog_distance_factor", params->Get<double>("volumetric_fog_distance_factor") / 2.0);

	params->Set("volumetric_fog_distance_from_surface",
		params->Get<double>("volumetric_fog_distance_from_surface") / 2.0);

	SynchronizeInterfaceWindow(this, params, qInterface::write);
}

void cDockEffects::slotRandomLightColoringTypeChanged(int index)
{
	ui->label_random_lights_first_color->setVisible(index > 0);
	ui->colorButton_random_lights_color->setVisible(index > 0);
	ui->label_random_lights_second_color->setVisible(index >= 2);
	ui->colorButton_random_lights_color_2->setVisible(index >= 2);
}

void cDockEffects::slotUpdatePrimitivesCombos()
{
	cPrimitives::PrepareComboBox(ui->comboBox_basic_fog_primitive, params);
	cPrimitives::PrepareComboBox(ui->comboBox_distance_fog_primitive, params);
	cPrimitives::PrepareComboBox(ui->comboBox_iteration_fog_primitive, params);
	cPrimitives::PrepareComboBox(ui->comboBox_clouds_primitive, params);
}

void cDockEffects::slotEnvMappingToggled(bool state)
{
	if (state)
	{
		ui->groupCheck_raytraced_reflections->setChecked(false);
	}
}

void cDockEffects::slotPressedButtonResetWorld()
{
	gPar->Set("fake_lights_world_offset", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_world_scale", 1.0);
	gPar->Set("fake_lights_world_rotation", CVector3(0.0, 0.0, 0.0));
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}

void cDockEffects::slotPressedButtonResetCamera()
{
	gPar->Set("fake_lights_camera_offset", CVector3(2.0, 0.0, 0.0));
	gPar->Set("fake_lights_camera_scale", 1.0);
	gPar->Set("fake_lights_camera_rotation", CVector3(0.0, 0.0, 0.0));
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}

void cDockEffects::slotPressedButtonResetTarget()
{
	gPar->Set("fake_lights_target_offset", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_target_scale", 1.0);
	gPar->Set("fake_lights_target_rotation", CVector3(0.0, 0.0, 0.0));
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}

void cDockEffects::slotPressedButtonResetFractalCenter()
{
	gPar->Set("fake_lights_fractal_center_offset", CVector3(0.0, 0.0, 1.0));
	gPar->Set("fake_lights_fractal_center_scale", 1.0);
	gPar->Set("fake_lights_fractal_center_rotation", CVector3(0.0, 0.0, 0.0));
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}

void cDockEffects::slotPressedButtonResetPathCircle()
{
	gPar->Set("fake_lights_path_circle_offset", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_path_circle_scale", 1.0);
	gPar->Set("fake_lights_path_circle_rotation", CVector3(0.0, 45.0, 0.0));
	gPar->Set("fake_lights_path_circle_path_radius", 2.0);
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}

void cDockEffects::slotPressedButtonResetPathSpiral()
{
	gPar->Set("fake_lights_path_spiral_offset", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_path_spiral_scale", 1.0);
	gPar->Set("fake_lights_path_spiral_rotation", CVector3(0.0, 90.0, 0.0));
	gPar->Set("fake_lights_path_spiral_path_radius", 2.0);
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}

void cDockEffects::slotPressedButtonResetOrbitTarget()
{
	gPar->Set("fake_lights_orbit_target_offset", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_orbit_target_scale", 1.0);
	gPar->Set("fake_lights_orbit_target_rotation", CVector3(0.0, 0.0, 0.0));
	gPar->Set("fake_lights_orbit_target_path_radius", 2.0);
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}

void cDockEffects::slotPressedButtonPlaceLightAtCamera()
{
	QPushButton *button = qobject_cast<QPushButton *>(sender());
	if (!button) return;

	QString name = button->objectName();
	QRegularExpression re("single_trap_light_(\\d+)_place_camera");
	QRegularExpressionMatch match = re.match(name);
	if (!match.hasMatch()) return;

	int layerNum = match.captured(1).toInt();
	QString prefix = QString("single_trap_light_%1").arg(layerNum);

	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::read);
	EnsureSingleTrapEngineOnAndActiveThrough(layerNum);

	const CVector3 camera = gPar->Get<CVector3>("camera");
	const CVector3 target = gPar->Get<CVector3>("target");
	CVector3 viewDir = target - camera;
	const double camTargetDist = viewDir.Length();
	if (camTargetDist < 1e-20)
		viewDir = CVector3(0.0, 0.0, 1.0);
	else
		viewDir.Normalize();

	CVector3 hitPoint;
	const bool hit = SingleTrapRaymarchFirstSurface(camera, viewDir, &hitPoint);

	CVector3 placedWorld;
	if (hit)
	{
		// Past the first surface along the view → inside the solid (not in empty space in front).
		const double bump = SingleTrapPlacementBumpFromView(prefix, camTargetDist);
		const double rayFromCam = (hitPoint - camera).Length();
		const double inset =
			std::min(bump * 0.45, std::max(0.0, rayFromCam - 0.02) * 0.42);
		const double insetUse = std::max(inset, 0.06);
		placedWorld = hitPoint + viewDir * insetUse;
	}
	else
	{
		// No surface along the ray (empty view): fall back to forward offset from camera.
		double clearance = SingleTrapRadialClearance(prefix);
		const int shape = gPar->Get<int>(prefix + "_shape");
		const double sz1 = fabs(gPar->Get<double>(prefix + "_size"));
		const double es = fabs(gPar->Get<double>(prefix + "_edge_softness"));
		const double rs = std::max(1e-8, fabs(gPar->Get<double>(prefix + "_relative_size")));
		if (shape == 12)
			clearance = std::max(clearance, camTargetDist * 0.38 + (sz1 + es) * rs * 2.2);
		else if (shape == 1)
			clearance = std::max(clearance, sz1 * rs * 3.2 + camTargetDist * 0.18);
		else if (shape == 13)
		{
			const double sz2 = fabs(gPar->Get<double>(prefix + "_size2"));
			clearance = std::max(clearance, (std::max(sz1, sz2) + es) * rs * 2.6);
		}
		const double alongView = SingleTrapForwardAlongView(camTargetDist);
		const double forward = std::max(alongView, clearance);
		placedWorld = camera + viewDir * forward;
	}

	// Single world-space placement; relative / pre_transformed modes were easy to misuse here.
	gPar->Set(prefix + "_pre_transformed", false);
	gPar->Set(prefix + "_position_mode", 0);
	gPar->Set(prefix + "_position", placedWorld);

	gPar->Set("single_trap_lights_solo_layer", layerNum);
	if (ui->spinboxInt_single_trap_lights_solo_layer)
		ui->spinboxInt_single_trap_lights_solo_layer->setValue(layerNum);

	if (QWidget *fw = QApplication::focusWidget()) fw->clearFocus();
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
	gMainInterface->StartRender(true);
}

void cDockEffects::slotPressedButtonPlaceSingleTrapLightAtSurface()
{
	QPushButton *button = qobject_cast<QPushButton *>(sender());
	if (!button) return;

	QString name = button->objectName();
	QRegularExpression re("single_trap_light_(\\d+)_place_surface");
	QRegularExpressionMatch match = re.match(name);
	if (!match.hasMatch()) return;

	int layerNum = match.captured(1).toInt();
	QString prefix = QString("single_trap_light_%1").arg(layerNum);

	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::read);
	EnsureSingleTrapEngineOnAndActiveThrough(layerNum);

	// Raymarch from camera in view direction to find fractal surface
	const CVector3 camera = gPar->Get<CVector3>("camera");
	const CVector3 target = gPar->Get<CVector3>("target");
	CVector3 direction = target - camera;
	const double camTargetLen = direction.Length();
	if (camTargetLen < 1e-20)
		direction = CVector3(0.0, 0.0, 1.0);
	else
		direction.Normalize();

	CVector3 point;
	SingleTrapRaymarchFirstSurface(camera, direction, &point);

	// Exact hit sits in/on the fractal; centering the light there puts the surface inside the
	// light SDF → white blow-up. Nudge back toward the camera by the same radial clearance.
	const double bump = SingleTrapPlacementBumpFromView(prefix, camTargetLen);

	const double rayFromCam = (point - camera).Length();
	const double back = std::min(bump, std::max(0.0, rayFromCam - 0.02) * 0.92);
	const CVector3 placedWorld = point - direction * back;

	gPar->Set(prefix + "_pre_transformed", false);
	gPar->Set(prefix + "_position_mode", 0);
	gPar->Set(prefix + "_position", placedWorld);

	// Solo this lamp so you can judge placement without other lights stacking (set to 0 for all).
	gPar->Set("single_trap_lights_solo_layer", layerNum);
	if (ui->spinboxInt_single_trap_lights_solo_layer)
		ui->spinboxInt_single_trap_lights_solo_layer->setValue(layerNum);

	if (QWidget *fw = QApplication::focusWidget()) fw->clearFocus();
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
	gMainInterface->StartRender(true);
}

void cDockEffects::slotPressedButtonPlaceSingleTrapLightAtTarget()
{
	QPushButton *button = qobject_cast<QPushButton *>(sender());
	if (!button) return;

	QString name = button->objectName();
	QRegularExpression re("single_trap_light_(\\d+)_place_target");
	QRegularExpressionMatch match = re.match(name);
	if (!match.hasMatch()) return;

	int layerNum = match.captured(1).toInt();
	QString prefix = QString("single_trap_light_%1").arg(layerNum);

	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::read);
	EnsureSingleTrapEngineOnAndActiveThrough(layerNum);

	const CVector3 camera = gPar->Get<CVector3>("camera");
	const CVector3 target = gPar->Get<CVector3>("target");
	CVector3 toCam = camera - target;
	const double len = toCam.Length();
	const double camTargetLen = (target - camera).Length();
	const double bump = SingleTrapPlacementBumpFromView(prefix, camTargetLen);

	CVector3 placedWorld = target;
	if (len > 1e-20)
	{
		toCam.Normalize();
		const double move = std::min(bump, len * 0.42);
		placedWorld = target + toCam * move;
	}

	gPar->Set(prefix + "_pre_transformed", false);
	gPar->Set(prefix + "_position_mode", 0);
	gPar->Set(prefix + "_position", placedWorld);

	gPar->Set("single_trap_lights_solo_layer", layerNum);
	if (ui->spinboxInt_single_trap_lights_solo_layer)
		ui->spinboxInt_single_trap_lights_solo_layer->setValue(layerNum);

	if (QWidget *fw = QApplication::focusWidget()) fw->clearFocus();
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
	gMainInterface->StartRender(true);
}

void cDockEffects::slotPressedButtonCopySingleTrapLight()
{
	int from = ui->spinboxInt_single_trap_copy_from->value();
	int to = ui->spinboxInt_single_trap_copy_to->value();

	if (from == to) return;
	if (from < 1 || from > 20 || to < 1 || to > 20) return;

	EnsureSingleTrapEngineOnAndActiveThrough(to);

	QString fromPrefix = QString("single_trap_light_%1").arg(from);
	QString toPrefix = QString("single_trap_light_%1").arg(to);

	// Copy all parameters
	gPar->Set(toPrefix + "_enabled", gPar->Get<bool>(fromPrefix + "_enabled"));
	gPar->Set(toPrefix + "_shape", gPar->Get<int>(fromPrefix + "_shape"));
	gPar->Set(toPrefix + "_position", gPar->Get<CVector3>(fromPrefix + "_position"));
	gPar->Set(toPrefix + "_size", gPar->Get<double>(fromPrefix + "_size"));
	gPar->Set(toPrefix + "_size2", gPar->Get<double>(fromPrefix + "_size2"));
	gPar->Set(toPrefix + "_thickness", gPar->Get<double>(fromPrefix + "_thickness"));
	gPar->Set(toPrefix + "_rotation", gPar->Get<CVector3>(fromPrefix + "_rotation"));
	gPar->Set(toPrefix + "_intensity", gPar->Get<double>(fromPrefix + "_intensity"));
	gPar->Set(toPrefix + "_color", gPar->Get<sRGB>(fromPrefix + "_color"));
	gPar->Set(toPrefix + "_gradient_color", gPar->Get<sRGB>(fromPrefix + "_gradient_color"));
	gPar->Set(toPrefix + "_visibility", gPar->Get<double>(fromPrefix + "_visibility"));
	gPar->Set(toPrefix + "_max_distance", gPar->Get<double>(fromPrefix + "_max_distance"));
	gPar->Set(toPrefix + "_sharpening", gPar->Get<double>(fromPrefix + "_sharpening"));
	gPar->Set(toPrefix + "_blur", gPar->Get<double>(fromPrefix + "_blur"));
	gPar->Set(toPrefix + "_solid_intensity", gPar->Get<double>(fromPrefix + "_solid_intensity"));
	gPar->Set(toPrefix + "_softness", gPar->Get<double>(fromPrefix + "_softness"));
	gPar->Set(toPrefix + "_relative_size", gPar->Get<double>(fromPrefix + "_relative_size"));
	gPar->Set(toPrefix + "_pre_transformed", gPar->Get<bool>(fromPrefix + "_pre_transformed"));
	gPar->Set(toPrefix + "_position_mode", gPar->Get<int>(fromPrefix + "_position_mode"));
	gPar->Set(toPrefix + "_coloring_mode", gPar->Get<int>(fromPrefix + "_coloring_mode"));
	gPar->Set(toPrefix + "_falloff_type", gPar->Get<int>(fromPrefix + "_falloff_type"));
	gPar->Set(toPrefix + "_edge_softness", gPar->Get<double>(fromPrefix + "_edge_softness"));
	gPar->Set(toPrefix + "_anim_orbit_radius", gPar->Get<double>(fromPrefix + "_anim_orbit_radius"));
	gPar->Set(toPrefix + "_anim_orbit_speed", gPar->Get<double>(fromPrefix + "_anim_orbit_speed"));
	gPar->Set(toPrefix + "_anim_pulsate_speed", gPar->Get<double>(fromPrefix + "_anim_pulsate_speed"));
	gPar->Set(toPrefix + "_anim_pulsate_amount", gPar->Get<double>(fromPrefix + "_anim_pulsate_amount"));

	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
	gMainInterface->StartRender(true);
}

void cDockEffects::slotPressedButtonRandomizeSingleTrapLight()
{
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::read);
	int layer = gPar->Get<int>("single_trap_randomize_layer");
	if (layer < 1 || layer > 20) return;
	RandomizeSingleTrapLightLayer(layer);
}

void cDockEffects::slotPressedButtonSingleTrapWorldAnchor()
{
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::read);
	int layer = gPar->Get<int>("single_trap_randomize_layer");
	if (layer < 1 || layer > 20) return;
	const QString p = QStringLiteral("single_trap_light_%1").arg(layer);
	gPar->Set(p + "_position_mode", 0);
	gPar->Set(p + "_pre_transformed", false);
	gPar->Set(p + "_relative_size", 1.0);
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
	gMainInterface->StartRender(true);
}

void cDockEffects::slotPressedButtonRandomizeAllSingleTrapLights()
{
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::read);
	gPar->Set("fake_lights_enabled", false);
	gPar->Set("single_trap_lights_enabled", true);
	if (ui->groupCheck_single_trap_lights_enabled)
		ui->groupCheck_single_trap_lights_enabled->setChecked(true);
	for (int layer = 1; layer <= 20; layer++)
	{
		RandomizeSingleTrapLightLayer(layer, false);
	}
	SyncSingleTrapActiveCountToHighestEnabledLayer();
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
	gMainInterface->StartRender(true);
}

void cDockEffects::RandomizeSingleTrapLightLayer(int layer, bool syncAndRender)
{
	cRandom random;
	random.Initialize(QTime::currentTime().msec() + layer * 137);

	QString prefix = QString("single_trap_light_%1").arg(layer);

	EnsureSingleTrapEngineOnAndActiveThrough(layer);

	gPar->Set(prefix + "_enabled", true);

	// Shapes 0..13 (Random(n) yields 0..n inclusive in this codebase)
	gPar->Set(prefix + "_shape", int(random.Random(13)));

	// Random position around current camera/target area (scale with scene extent)
	CVector3 camera = gPar->Get<CVector3>("camera");
	CVector3 target = gPar->Get<CVector3>("target");
	const double camTargetLen = (target - camera).Length();
	const double sceneScale = std::max(camTargetLen, 0.5);
	CVector3 center = camera + (target - camera) * random.DoubleRandom(0.2, 0.45);
	const double spread = sceneScale * random.DoubleRandom(0.35, 0.75);
	CVector3 pos(
		center.x + random.DoubleRandom(-spread, spread),
		center.y + random.DoubleRandom(-spread, spread),
		center.z + random.DoubleRandom(-spread, spread));
	gPar->Set(prefix + "_position", pos);

	// Random size parameters
	gPar->Set(prefix + "_size", random.DoubleRandom(0.25, sceneScale * 0.45));
	gPar->Set(prefix + "_size2", random.DoubleRandom(0.08, std::max(0.35, sceneScale * 0.12)));
	gPar->Set(prefix + "_thickness", random.DoubleRandom(0.35, 1.85));

	// Random rotation
	gPar->Set(prefix + "_rotation",
		CVector3(
			random.DoubleRandom(0.0, 360.0),
			random.DoubleRandom(0.0, 360.0),
			random.DoubleRandom(0.0, 360.0)));

	// Random intensity and visibility (stronger, usually full visibility)
	gPar->Set(prefix + "_intensity", random.DoubleRandom(0.85, 4.2));
	gPar->Set(prefix + "_visibility", random.DoubleRandom(0.75, 1.0));

	// Random bright color (HSV-like: high saturation, varied hue)
	double hue = random.DoubleRandom(0.0, 1.0);
	double sat = random.DoubleRandom(0.6, 1.0);
	double val = random.DoubleRandom(0.8, 1.0);
	// HSV to RGB conversion
	int hi = int(hue * 6.0) % 6;
	double f = hue * 6.0 - hi;
	double p = val * (1.0 - sat);
	double q = val * (1.0 - f * sat);
	double t = val * (1.0 - (1.0 - f) * sat);
	double r, g, b;
	switch (hi)
	{
		case 0: r = val; g = t; b = p; break;
		case 1: r = q; g = val; b = p; break;
		case 2: r = p; g = val; b = t; break;
		case 3: r = p; g = q; b = val; break;
		case 4: r = t; g = p; b = val; break;
		default: r = val; g = p; b = q; break;
	}
	gPar->Set(prefix + "_color", sRGB(int(r * 65535), int(g * 65535), int(b * 65535)));

	// Gradient color: complementary or analogous
	double hue2 = fmod(hue + 0.5, 1.0);
	hi = int(hue2 * 6.0) % 6;
	f = hue2 * 6.0 - hi;
	p = val * (1.0 - sat);
	q = val * (1.0 - f * sat);
	t = val * (1.0 - (1.0 - f) * sat);
	switch (hi)
	{
		case 0: r = val; g = t; b = p; break;
		case 1: r = q; g = val; b = p; break;
		case 2: r = p; g = val; b = t; break;
		case 3: r = p; g = q; b = val; break;
		case 4: r = t; g = p; b = val; break;
		default: r = val; g = p; b = q; break;
	}
	gPar->Set(prefix + "_gradient_color", sRGB(int(r * 65535), int(g * 65535), int(b * 65535)));

	// Random falloff and distance — max_distance in a visible band (too low reads as “off”)
	gPar->Set(prefix + "_max_distance", random.DoubleRandom(0.22, 0.72));
	gPar->Set(prefix + "_sharpening", random.DoubleRandom(0.35, 3.8));
	gPar->Set(prefix + "_blur", random.DoubleRandom(0.0, 2.0));
	gPar->Set(prefix + "_solid_intensity", random.DoubleRandom(0.6, 2.2));
	gPar->Set(prefix + "_softness", random.DoubleRandom(0.0, 1.8));
	gPar->Set(prefix + "_relative_size", random.DoubleRandom(0.55, 2.2));
	gPar->Set(prefix + "_edge_softness", random.DoubleRandom(0.0, 0.85));
	// Falloff enum 0..4 inclusive → Random(4)
	gPar->Set(prefix + "_falloff_type", int(random.Random(4)));
	gPar->Set(prefix + "_coloring_mode", int(random.Random(2)));
	gPar->Set(prefix + "_pre_transformed", false);
	gPar->Set(prefix + "_position_mode", 0);
	gPar->Set(prefix + "_anim_orbit_radius", random.DoubleRandom(0.0, 5.0));
	gPar->Set(prefix + "_anim_orbit_speed", random.DoubleRandom(-2.0, 2.0));
	gPar->Set(prefix + "_anim_pulsate_speed", random.DoubleRandom(0.0, 3.0));
	gPar->Set(prefix + "_anim_pulsate_amount", random.DoubleRandom(0.0, 0.5));

	if (syncAndRender)
	{
		gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
		gMainInterface->StartRender(true);
	}
}

void cDockEffects::slotPressedButtonSingleTrapPresetApply()
{
	int preset = ui->comboBox_single_trap_preset->currentIndex();
	ApplySingleTrapPreset(preset);
}

void cDockEffects::slotPressedButtonSingleTrapResetAll()
{
	gPar->Set("single_trap_lights_solo_layer", 0);
	gPar->Set("single_trap_lights_combine_mode", 0);
	if (ui->spinboxInt_single_trap_lights_solo_layer)
		ui->spinboxInt_single_trap_lights_solo_layer->setValue(0);
	if (ui->comboBox_single_trap_lights_combine_mode)
		ui->comboBox_single_trap_lights_combine_mode->setCurrentIndex(0);

	for (int layer = 1; layer <= 20; layer++)
	{
		ResetSingleTrapLightLayer(layer);
	}
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
	gMainInterface->StartRender(true);
}

void cDockEffects::ResetSingleTrapLightLayer(int layer)
{
	QString prefix = QString("single_trap_light_%1").arg(layer);
	gPar->Set(prefix + "_enabled", false);
	gPar->Set(prefix + "_shape", 0);
	gPar->Set(prefix + "_position", CVector3(0.0, 0.0, 0.0));
	gPar->Set(prefix + "_size", 1.0);
	gPar->Set(prefix + "_size2", 0.25);
	gPar->Set(prefix + "_thickness", 1.0);
	gPar->Set(prefix + "_rotation", CVector3(0.0, 0.0, 0.0));
	gPar->Set(prefix + "_intensity", 1.0);
	gPar->Set(prefix + "_color", sRGB(65535, 65535, 65535));
	gPar->Set(prefix + "_gradient_color", sRGB(65535, 65535, 65535));
	gPar->Set(prefix + "_visibility", 1.0);
	gPar->Set(prefix + "_max_distance", 0.5);
	gPar->Set(prefix + "_sharpening", 1.0);
	gPar->Set(prefix + "_blur", 0.0);
	gPar->Set(prefix + "_solid_intensity", 1.0);
	gPar->Set(prefix + "_softness", 0.0);
	gPar->Set(prefix + "_relative_size", 1.0);
	gPar->Set(prefix + "_edge_softness", 0.0);
	gPar->Set(prefix + "_falloff_type", 0);
	gPar->Set(prefix + "_coloring_mode", 0);
	gPar->Set(prefix + "_pre_transformed", false);
	gPar->Set(prefix + "_position_mode", 0);
	gPar->Set(prefix + "_anim_orbit_radius", 0.0);
	gPar->Set(prefix + "_anim_orbit_speed", 0.0);
	gPar->Set(prefix + "_anim_pulsate_speed", 0.0);
	gPar->Set(prefix + "_anim_pulsate_amount", 0.0);
}

void cDockEffects::ApplySingleTrapPreset(int preset)
{
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::read);
	gPar->Set("fake_lights_enabled", false);
	gPar->Set("single_trap_lights_enabled", true);
	if (ui->groupCheck_single_trap_lights_enabled)
		ui->groupCheck_single_trap_lights_enabled->setChecked(true);

	// Reset all first
	for (int layer = 1; layer <= 20; layer++)
	{
		ResetSingleTrapLightLayer(layer);
	}

	gPar->Set("single_trap_lights_solo_layer", 0);
	if (ui->spinboxInt_single_trap_lights_solo_layer)
		ui->spinboxInt_single_trap_lights_solo_layer->setValue(0);

	const CVector3 camera = gPar->Get<CVector3>("camera");
	const CVector3 target = gPar->Get<CVector3>("target");
	CVector3 viewDir = target - camera;
	const double camTgtLen = viewDir.Length();
	if (camTgtLen < 1e-20)
		viewDir = CVector3(0.0, 0.0, 1.0);
	else
		viewDir.Normalize();
	// Robust orthonormal basis
	CVector3 worldUp(0.0, 0.0, 1.0);
	if (fabs(viewDir.z) > 0.99) worldUp = CVector3(0.0, 1.0, 0.0);
	CVector3 right = worldUp.Cross(viewDir);
	right.Normalize();
	CVector3 up = viewDir.Cross(right);
	up.Normalize();
	// Scale rigs with camera–target distance so presets stay readable on any zoom.
	const double fwd = std::max(0.48 * camTgtLen, 1.5);
	const double lat = std::max(0.32 * camTgtLen, 1.05);
	const double vert = std::max(0.26 * camTgtLen, 0.9);
	const double szSphere = std::max(0.35 * fwd, 1.15);

	switch (preset)
	{
		case 0: // Zon — high-key + rim (add)
		{
			gPar->Set("single_trap_lights_combine_mode", 0);
			if (ui->comboBox_single_trap_lights_combine_mode)
				ui->comboBox_single_trap_lights_combine_mode->setCurrentIndex(0);

			gPar->Set("single_trap_light_1_enabled", true);
			gPar->Set("single_trap_light_1_shape", 4);
			gPar->Set("single_trap_light_1_position", camera + viewDir * fwd * 1.25 + up * vert * 2.0);
			gPar->Set("single_trap_light_1_size", szSphere * 2.0);
			gPar->Set("single_trap_light_1_intensity", 3.4);
			gPar->Set("single_trap_light_1_solid_intensity", 1.35);
			gPar->Set("single_trap_light_1_visibility", 1.0);
			gPar->Set("single_trap_light_1_color", sRGB(65535, 58000, 42000));
			gPar->Set("single_trap_light_1_gradient_color", sRGB(65535, 42000, 18000));
			gPar->Set("single_trap_light_1_max_distance", 0.82);
			gPar->Set("single_trap_light_1_sharpening", 0.55);
			gPar->Set("single_trap_light_1_falloff_type", 1);
			gPar->Set("single_trap_light_1_softness", 0.25);
			gPar->Set("single_trap_light_1_blur", 0.08);

			gPar->Set("single_trap_light_2_enabled", true);
			gPar->Set("single_trap_light_2_shape", 4);
			gPar->Set("single_trap_light_2_position", camera + viewDir * fwd * 0.72 - right * lat * 1.35 + up * vert * 0.6);
			gPar->Set("single_trap_light_2_size", szSphere * 1.15);
			gPar->Set("single_trap_light_2_intensity", 1.85);
			gPar->Set("single_trap_light_2_visibility", 1.0);
			gPar->Set("single_trap_light_2_color", sRGB(35000, 48000, 65535));
			gPar->Set("single_trap_light_2_gradient_color", sRGB(25000, 38000, 65535));
			gPar->Set("single_trap_light_2_max_distance", 0.62);
			gPar->Set("single_trap_light_2_sharpening", 0.5);
			gPar->Set("single_trap_light_2_falloff_type", 3);
			gPar->Set("single_trap_light_2_softness", 0.2);

			gPar->Set("single_trap_light_3_enabled", true);
			gPar->Set("single_trap_light_3_shape", 4);
			gPar->Set("single_trap_light_3_position", camera + viewDir * fwd * 0.35 + up * vert * 2.4 + right * lat * 0.45);
			gPar->Set("single_trap_light_3_size", szSphere * 0.75);
			gPar->Set("single_trap_light_3_intensity", 2.5);
			gPar->Set("single_trap_light_3_visibility", 1.0);
			gPar->Set("single_trap_light_3_color", sRGB(65535, 52000, 38000));
			gPar->Set("single_trap_light_3_gradient_color", sRGB(65535, 40000, 22000));
			gPar->Set("single_trap_light_3_max_distance", 0.48);
			gPar->Set("single_trap_light_3_sharpening", 0.95);
			gPar->Set("single_trap_light_3_falloff_type", 2);
			break;
		}
		case 1: // Neon — max combine, saturated tubes
		{
			gPar->Set("single_trap_lights_combine_mode", 1);
			if (ui->comboBox_single_trap_lights_combine_mode)
				ui->comboBox_single_trap_lights_combine_mode->setCurrentIndex(1);

			sRGB colors[6] = {
				sRGB(65535, 0, 65535), sRGB(0, 65535, 65535), sRGB(65535, 65535, 0),
				sRGB(65535, 0, 30000), sRGB(0, 65535, 20000), sRGB(65535, 40000, 0),
			};
			for (int i = 0; i < 6; i++)
			{
				QString p = QString("single_trap_light_%1").arg(i + 1);
				gPar->Set(p + "_enabled", true);
				gPar->Set(p + "_shape", 1);
				double angle = i * M_PI / 3.0;
				CVector3 pos = camera + viewDir * fwd * 1.05 + right * cos(angle) * lat * 1.55 + up * sin(angle) * lat * 1.55;
				gPar->Set(p + "_position", pos);
				gPar->Set(p + "_rotation", CVector3(0.0, angle * 180.0 / M_PI, 20.0 + i * 12.0));
				gPar->Set(p + "_size", std::max(0.55, lat * 0.22));
				gPar->Set(p + "_intensity", 2.85);
				gPar->Set(p + "_solid_intensity", 1.25);
				gPar->Set(p + "_visibility", 1.0);
				gPar->Set(p + "_color", colors[i]);
				gPar->Set(p + "_gradient_color", colors[(i + 1) % 6]);
				gPar->Set(p + "_max_distance", 0.45);
				gPar->Set(p + "_sharpening", 0.85);
				gPar->Set(p + "_blur", 0.18);
				gPar->Set(p + "_falloff_type", i % 2);
				gPar->Set(p + "_coloring_mode", 1);
			}
			break;
		}
		case 2: // Vuur — clustered embers + soft halo torus
		{
			gPar->Set("single_trap_lights_combine_mode", 0);
			if (ui->comboBox_single_trap_lights_combine_mode)
				ui->comboBox_single_trap_lights_combine_mode->setCurrentIndex(0);

			sRGB fireColors[5] = {
				sRGB(65535, 50000, 0), sRGB(65535, 30000, 0), sRGB(65535, 15000, 0),
				sRGB(65535, 60000, 20000), sRGB(65535, 20000, 0),
			};
			for (int i = 0; i < 5; i++)
			{
				QString p = QString("single_trap_light_%1").arg(i + 1);
				gPar->Set(p + "_enabled", true);
				gPar->Set(p + "_shape", 4);
				double t = double(i) / 4.0;
				CVector3 pos = camera + viewDir * fwd * (0.65 + t * 0.55) + right * (double(i) - 2.0) * lat * 0.42
											 + up * (vert * 0.55 + t * vert * 1.1);
				gPar->Set(p + "_position", pos);
				gPar->Set(p + "_size", szSphere * (0.85 + t * 0.35));
				gPar->Set(p + "_intensity", 2.0 + t * 1.1);
				gPar->Set(p + "_solid_intensity", 1.5 + t * 0.4);
				gPar->Set(p + "_visibility", 1.0);
				gPar->Set(p + "_color", fireColors[i]);
				gPar->Set(p + "_gradient_color", fireColors[(i + 1) % 5]);
				gPar->Set(p + "_max_distance", 0.68);
				gPar->Set(p + "_softness", 0.35 + t * 0.45);
				gPar->Set(p + "_sharpening", 0.45);
				gPar->Set(p + "_falloff_type", t > 0.5 ? 3 : 0);
				gPar->Set(p + "_anim_pulsate_speed", 0.8 + t * 0.6);
				gPar->Set(p + "_anim_pulsate_amount", 0.12 + t * 0.08);
			}
			gPar->Set("single_trap_light_6_enabled", true);
			gPar->Set("single_trap_light_6_shape", 6);
			gPar->Set("single_trap_light_6_position", camera + viewDir * fwd * 0.55);
			gPar->Set("single_trap_light_6_rotation", CVector3(90.0, 0.0, 0.0));
			gPar->Set("single_trap_light_6_size", std::max(0.9, lat * 0.5));
			gPar->Set("single_trap_light_6_size2", std::max(0.12, lat * 0.07));
			gPar->Set("single_trap_light_6_intensity", 1.1);
			gPar->Set("single_trap_light_6_max_distance", 0.88);
			gPar->Set("single_trap_light_6_sharpening", 0.35);
			gPar->Set("single_trap_light_6_softness", 0.55);
			gPar->Set("single_trap_light_6_blur", 0.35);
			gPar->Set("single_trap_light_6_color", sRGB(65535, 35000, 4000));
			gPar->Set("single_trap_light_6_gradient_color", sRGB(65535, 20000, 0));
			gPar->Set("single_trap_light_6_falloff_type", 4);
			break;
		}
		case 3: // IJs — cool key + fill + wide disc bounce
		{
			gPar->Set("single_trap_lights_combine_mode", 0);
			if (ui->comboBox_single_trap_lights_combine_mode)
				ui->comboBox_single_trap_lights_combine_mode->setCurrentIndex(0);

			gPar->Set("single_trap_light_1_enabled", true);
			gPar->Set("single_trap_light_1_shape", 4);
			gPar->Set("single_trap_light_1_position", camera + viewDir * fwd * 1.1 + up * vert * 1.85);
			gPar->Set("single_trap_light_1_size", szSphere * 1.9);
			gPar->Set("single_trap_light_1_intensity", 2.6);
			gPar->Set("single_trap_light_1_visibility", 1.0);
			gPar->Set("single_trap_light_1_color", sRGB(48000, 62000, 65535));
			gPar->Set("single_trap_light_1_gradient_color", sRGB(38000, 52000, 65535));
			gPar->Set("single_trap_light_1_max_distance", 0.78);
			gPar->Set("single_trap_light_1_sharpening", 0.55);
			gPar->Set("single_trap_light_1_edge_softness", 0.35);
			gPar->Set("single_trap_light_1_falloff_type", 3);
			gPar->Set("single_trap_light_1_blur", 0.12);

			gPar->Set("single_trap_light_2_enabled", true);
			gPar->Set("single_trap_light_2_shape", 4);
			gPar->Set("single_trap_light_2_position", camera + viewDir * fwd * 0.68 - right * lat * 1.1);
			gPar->Set("single_trap_light_2_size", szSphere * 1.25);
			gPar->Set("single_trap_light_2_intensity", 1.55);
			gPar->Set("single_trap_light_2_visibility", 1.0);
			gPar->Set("single_trap_light_2_color", sRGB(58000, 65535, 65535));
			gPar->Set("single_trap_light_2_gradient_color", sRGB(48000, 60000, 65535));
			gPar->Set("single_trap_light_2_max_distance", 0.58);
			gPar->Set("single_trap_light_2_sharpening", 0.48);
			gPar->Set("single_trap_light_2_falloff_type", 0);

			gPar->Set("single_trap_light_3_enabled", true);
			gPar->Set("single_trap_light_3_shape", 13);
			gPar->Set("single_trap_light_3_position", camera + viewDir * fwd * 0.45 - up * vert * 0.35);
			gPar->Set("single_trap_light_3_rotation", CVector3(0.0, 0.0, 0.0));
			gPar->Set("single_trap_light_3_size", std::max(1.4, lat * 0.85));
			gPar->Set("single_trap_light_3_size2", std::max(0.08, fwd * 0.04));
			gPar->Set("single_trap_light_3_intensity", 1.25);
			gPar->Set("single_trap_light_3_max_distance", 0.92);
			gPar->Set("single_trap_light_3_sharpening", 0.32);
			gPar->Set("single_trap_light_3_softness", 0.4);
			gPar->Set("single_trap_light_3_blur", 0.28);
			gPar->Set("single_trap_light_3_color", sRGB(55000, 65535, 65535));
			gPar->Set("single_trap_light_3_gradient_color", sRGB(40000, 52000, 65535));
			gPar->Set("single_trap_light_3_falloff_type", 4);
			break;
		}
		case 4: // Onderwater — murky beams, mixed falloff
		{
			gPar->Set("single_trap_lights_combine_mode", 0);
			if (ui->comboBox_single_trap_lights_combine_mode)
				ui->comboBox_single_trap_lights_combine_mode->setCurrentIndex(0);

			for (int i = 0; i < 5; i++)
			{
				QString p = QString("single_trap_light_%1").arg(i + 1);
				gPar->Set(p + "_enabled", true);
				gPar->Set(p + "_shape", 4);
				double t = double(i) / 4.0;
				CVector3 pos = camera + viewDir * fwd * (0.85 + t * 0.45) + right * cos(t * M_PI * 2.0) * lat * 1.25
											 + up * sin(t * M_PI * 2.0) * vert * 0.95;
				gPar->Set(p + "_position", pos);
				gPar->Set(p + "_size", szSphere * (1.0 + 0.2 * t));
				gPar->Set(p + "_intensity", 1.65 + t * 0.55);
				gPar->Set(p + "_visibility", 1.0);
				int green = 38000 + int(t * 22000);
				gPar->Set(p + "_color", sRGB(8000, green, 65535));
				gPar->Set(p + "_gradient_color", sRGB(4000, green + 6000, 62000));
				gPar->Set(p + "_max_distance", 0.62 + t * 0.18);
				gPar->Set(p + "_blur", 0.55 + t * 0.45);
				gPar->Set(p + "_softness", 0.4 + t * 0.25);
				gPar->Set(p + "_sharpening", 0.42);
				gPar->Set(p + "_falloff_type", i % 3);
				gPar->Set(p + "_coloring_mode", (i & 1) ? 1 : 0);
			}
			break;
		}
		case 5: // Disco — max combine, hard sparkle points
		{
			gPar->Set("single_trap_lights_combine_mode", 1);
			if (ui->comboBox_single_trap_lights_combine_mode)
				ui->comboBox_single_trap_lights_combine_mode->setCurrentIndex(1);

			for (int i = 0; i < 8; i++)
			{
				QString p = QString("single_trap_light_%1").arg(i + 1);
				gPar->Set(p + "_enabled", true);
				gPar->Set(p + "_shape", 0);
				double angle = i * M_PI / 4.0;
				double rad = lat * (1.05 + 0.12 * (i % 3));
				CVector3 pos = camera + viewDir * fwd * 0.95 + right * cos(angle) * rad + up * sin(angle) * vert * 1.05;
				gPar->Set(p + "_position", pos);
				gPar->Set(p + "_size", std::max(0.42, lat * 0.14));
				gPar->Set(p + "_intensity", 1.85 + (i % 3) * 0.35);
				gPar->Set(p + "_solid_intensity", 1.4);
				gPar->Set(p + "_visibility", 1.0);
				int hue = (i * 65535) / 8;
				int r = (hue < 21845) ? 65535 - hue * 3 : (hue < 43690) ? 0 : (hue - 43690) * 3;
				int g = (hue < 21845) ? hue * 3 : (hue < 43690) ? 65535 : 65535 - (hue - 43690) * 3;
				int b = (hue < 21845) ? 0 : (hue < 43690) ? (hue - 21845) * 3 : 65535 - (hue - 43690) * 3;
				gPar->Set(p + "_color", sRGB(qBound(0, r, 65535), qBound(0, g, 65535), qBound(0, b, 65535)));
				gPar->Set(p + "_gradient_color", sRGB(65535, 65535, 65535));
				gPar->Set(p + "_max_distance", 0.34);
				gPar->Set(p + "_sharpening", 1.05);
				gPar->Set(p + "_blur", 0.06);
				gPar->Set(p + "_falloff_type", (i % 2) ? 2 : 0);
			}
			break;
		}
		case 6: // Film Noir — hard key + weak cool fill
		{
			gPar->Set("single_trap_lights_combine_mode", 0);
			if (ui->comboBox_single_trap_lights_combine_mode)
				ui->comboBox_single_trap_lights_combine_mode->setCurrentIndex(0);

			gPar->Set("single_trap_light_1_enabled", true);
			gPar->Set("single_trap_light_1_shape", 4);
			gPar->Set("single_trap_light_1_position", camera + viewDir * fwd * 1.05 + right * lat * 1.45 + up * vert * 1.9);
			gPar->Set("single_trap_light_1_size", szSphere * 1.1);
			gPar->Set("single_trap_light_1_intensity", 3.8);
			gPar->Set("single_trap_light_1_visibility", 1.0);
			gPar->Set("single_trap_light_1_color", sRGB(65535, 56000, 44000));
			gPar->Set("single_trap_light_1_gradient_color", sRGB(65535, 48000, 32000));
			gPar->Set("single_trap_light_1_max_distance", 0.58);
			gPar->Set("single_trap_light_1_sharpening", 1.05);
			gPar->Set("single_trap_light_1_falloff_type", 1);
			gPar->Set("single_trap_light_1_softness", 0.08);

			gPar->Set("single_trap_light_2_enabled", true);
			gPar->Set("single_trap_light_2_shape", 4);
			gPar->Set("single_trap_light_2_position", camera + viewDir * fwd * 0.42 - right * lat * 1.55 + up * vert * 0.35);
			gPar->Set("single_trap_light_2_size", szSphere * 1.35);
			gPar->Set("single_trap_light_2_intensity", 0.72);
			gPar->Set("single_trap_light_2_visibility", 1.0);
			gPar->Set("single_trap_light_2_color", sRGB(38000, 42000, 52000));
			gPar->Set("single_trap_light_2_gradient_color", sRGB(28000, 32000, 45000));
			gPar->Set("single_trap_light_2_max_distance", 0.88);
			gPar->Set("single_trap_light_2_sharpening", 0.38);
			gPar->Set("single_trap_light_2_falloff_type", 2);
			gPar->Set("single_trap_light_2_blur", 0.22);
			break;
		}
		case 7: // Magisch — max combine, orbit + sparks
		{
			gPar->Set("single_trap_lights_combine_mode", 1);
			if (ui->comboBox_single_trap_lights_combine_mode)
				ui->comboBox_single_trap_lights_combine_mode->setCurrentIndex(1);

			gPar->Set("single_trap_light_1_enabled", true);
			gPar->Set("single_trap_light_1_shape", 6);
			gPar->Set("single_trap_light_1_position", camera + viewDir * fwd * 0.92 + up * vert * 1.1);
			gPar->Set("single_trap_light_1_rotation", CVector3(35.0, 15.0, 0.0));
			gPar->Set("single_trap_light_1_size", std::max(1.0, lat * 0.55));
			gPar->Set("single_trap_light_1_size2", std::max(0.14, lat * 0.09));
			gPar->Set("single_trap_light_1_intensity", 2.35);
			gPar->Set("single_trap_light_1_solid_intensity", 1.45);
			gPar->Set("single_trap_light_1_visibility", 1.0);
			gPar->Set("single_trap_light_1_color", sRGB(52000, 28000, 65535));
			gPar->Set("single_trap_light_1_gradient_color", sRGB(65535, 45000, 18000));
			gPar->Set("single_trap_light_1_max_distance", 0.72);
			gPar->Set("single_trap_light_1_softness", 0.55);
			gPar->Set("single_trap_light_1_sharpening", 0.62);
			gPar->Set("single_trap_light_1_falloff_type", 4);
			gPar->Set("single_trap_light_1_anim_orbit_radius", std::max(0.25, lat * 0.12));
			gPar->Set("single_trap_light_1_anim_orbit_speed", 0.65);

			for (int i = 0; i < 5; i++)
			{
				QString p = QString("single_trap_light_%1").arg(i + 2);
				gPar->Set(p + "_enabled", true);
				gPar->Set(p + "_shape", 0);
				double angle = i * (2.0 * M_PI / 5.0);
				CVector3 pos = camera + viewDir * fwd * 0.72 + right * cos(angle) * lat * 1.05 + up * sin(angle) * vert * 0.88;
				gPar->Set(p + "_position", pos);
				gPar->Set(p + "_size", std::max(0.35, lat * 0.11));
				gPar->Set(p + "_intensity", 1.55 + 0.2 * i);
				gPar->Set(p + "_solid_intensity", 1.65);
				gPar->Set(p + "_visibility", 1.0);
				gPar->Set(p + "_color", sRGB(65535, 52000 + i * 2500, 35000));
				gPar->Set(p + "_gradient_color", sRGB(50000, 28000, 65535));
				gPar->Set(p + "_max_distance", 0.28);
				gPar->Set(p + "_sharpening", 0.95);
				gPar->Set(p + "_blur", 0.05);
				gPar->Set(p + "_falloff_type", i % 3);
				gPar->Set(p + "_coloring_mode", 2);
			}
			break;
		}
	}

	SyncSingleTrapActiveCountToHighestEnabledLayer();

	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
	gMainInterface->StartRender(true);
}

void cDockEffects::slotChangedSingleTrapLightShape(int index) const
{
	QComboBox *combo = qobject_cast<QComboBox *>(sender());
	if (!combo) return;

	QString name = combo->objectName();
	QRegularExpression re("single_trap_light_(\\d+)_shape");
	QRegularExpressionMatch match = re.match(name);
	if (!match.hasMatch()) return;

	int layerNum = match.captured(1).toInt();
	bool usesSize2 = SingleTrapShapeUsesSecondSize(index);

	QLabel *label = findChild<QLabel *>(
		QString("label_single_trap_light_%1_size2").arg(layerNum));
	QWidget *edit = findChild<QWidget *>(
		QString("logedit_single_trap_light_%1_size2").arg(layerNum));

	if (label) label->setVisible(usesSize2);
	if (edit) edit->setVisible(usesSize2);
}

void cDockEffects::slotPressedButtonResetMultiCenter()
{
	gPar->Set("fake_lights_multi_center_enabled", false);
	gPar->Set("fake_lights_multi_center_1", CVector3(1.0, 0.0, 0.0));
	gPar->Set("fake_lights_multi_center_2", CVector3(0.0, 1.0, 0.0));
	gPar->Set("fake_lights_multi_center_3", CVector3(0.0, 0.0, 1.0));
	gPar->Set("fake_lights_multi_center_4", CVector3(-1.0, 0.0, 0.0));
	gPar->Set("fake_lights_multi_center_weight_1", 1.0);
	gPar->Set("fake_lights_multi_center_weight_2", 1.0);
	gPar->Set("fake_lights_multi_center_weight_3", 1.0);
	gPar->Set("fake_lights_multi_center_weight_4", 1.0);
	gPar->Set("fake_lights_multi_center_color_1", sRGB(65535, 0, 0));
	gPar->Set("fake_lights_multi_center_color_2", sRGB(0, 65535, 0));
	gPar->Set("fake_lights_multi_center_color_3", sRGB(0, 0, 65535));
	gPar->Set("fake_lights_multi_center_color_4", sRGB(65535, 65535, 0));
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}
