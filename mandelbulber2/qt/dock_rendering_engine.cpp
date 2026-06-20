/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2016-20 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * Widget which contains UI for rendering engine
 */

#include "dock_rendering_engine.h"

#include "ui_dock_rendering_engine.h"

#include "rendering_fractal_shape_tab.h"
#include "rendering_nebula_tab.h"
#include "rendering_limits_tab.h"
#include "rendering_netrender_tab.h"

#define SHAPE_UI (static_cast<cRenderingFractalShapeTab*>(ui->tabFractalShape)->fractalShapeUi())
#define NEBULA_UI (static_cast<cRenderingNebulaTab*>(ui->tabNebula)->nebulaUi())
#define LIMITS_UI (static_cast<cRenderingLimitsTab*>(ui->tabLimits)->limitsUi())
#define NET_UI (static_cast<cRenderingNetrenderTab*>(ui->tabNetRender)->netrenderUi())
#include "dock_fractal.h"
#include "dock_image_adjustments.h"
#include "dock_navigation.h"

#include "src/automated_widgets.hpp"
#include "src/auto_iter_bailout.hpp"
#include "src/auto_fog.hpp"
#include "src/cloud_presets.hpp"
#include "src/cimage.hpp"
#include "src/fractparams.hpp"
#include "src/fractal_container.hpp"
#include "src/initparameters.hpp"
#include "src/interface.hpp"
#include "qt_utils.h"
#include "src/netrender.hpp"
#include "src/nine_fractals.hpp"
#include "src/projection_3d.hpp"
#include "src/render_data.hpp"
#include "src/render_window.hpp"
#include "src/synchronize_interface.hpp"
#include "src/ui_parameter_validator.hpp"

#include <QMessageBox>
#include <algorithm>

namespace {
autoFog::eAutoFogQuality ReadAutoFogQuality(const std::shared_ptr<cParameterContainer> &par)
{
	const int qualityIndex = std::max(0, std::min(par->Get<int>("auto_fog_quality"), 2));
	return static_cast<autoFog::eAutoFogQuality>(qualityIndex);
}

bool RunAutoFogFromRenderSettings(cDockRenderingEngine *dock, autoFog::eAutoFogTuneMode mode,
	QString *statusOut)
{
	if (!gMainInterface || !gMainInterface->mainWindow) return false;

	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::read);

	sRenderData renderData;
	renderData.objectData.resize(NUMBER_OF_FRACTALS);
	std::shared_ptr<sParamRender> renderParams(new sParamRender(gPar, &renderData.objectData));
	std::shared_ptr<cNineFractals> fractals(new cNineFractals(gParFractal, gPar));
	renderParams->UpdateIterFogEffectiveN(fractals.get());

	const autoFog::eAutoFogQuality quality = ReadAutoFogQuality(gPar);

	const bool wasIterFogEnabled = renderParams->iterFogEnabled;
	const bool wasVolFogEnabled = renderParams->volFogEnabled;
	const bool wasFogEnabled = renderParams->fogEnabled;
	if (mode == autoFog::eAutoFogTuneMode::All || mode == autoFog::eAutoFogTuneMode::IterationOnly)
		renderParams->iterFogEnabled = true;
	if (mode == autoFog::eAutoFogTuneMode::All || mode == autoFog::eAutoFogTuneMode::DistanceOnly)
		renderParams->volFogEnabled = true;
	if (mode == autoFog::eAutoFogTuneMode::All || mode == autoFog::eAutoFogTuneMode::BasicOnly)
		renderParams->fogEnabled = true;

	autoFog::cAutoFog autoFog;
	const bool ok = autoFog.AutoTuneAll(renderParams.get(), fractals.get(), &renderData, quality, mode);

	renderParams->iterFogEnabled = wasIterFogEnabled;
	renderParams->volFogEnabled = wasVolFogEnabled;
	renderParams->fogEnabled = wasFogEnabled;

	if (ok)
	{
		autoFog::WriteAutoFogResults(gPar, *renderParams, mode, true);
		if (statusOut)
		{
			*statusOut = autoFog::FormatAutoFogResultLabel(
				autoFog.GetIterationProfile(), autoFog.GetLastFractalClassName());
		}
		gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
	}
	else if (statusOut)
	{
		*statusOut = dock->tr("Could not detect fractal surface from current camera position.");
	}

	return ok;
}
} // namespace

cDockRenderingEngine::cDockRenderingEngine(QWidget *parent)
		: QWidget(parent), ui(new Ui::cDockRenderingEngine)
{
	ui->setupUi(this);
	automatedWidgets = new cAutomatedWidgets(this);
	automatedWidgets->ConnectSignalsForSlidersInWindow(this);
	ConnectSignals();

	NET_UI->groupBox_netrender_client_config->setVisible(false);

#ifndef USE_OPENCL
	NEBULA_UI->groupCheck_nebula_mode->setVisible(false);
#endif
}

cDockRenderingEngine::~cDockRenderingEngine()
{
	delete ui;
}

void cDockRenderingEngine::ConnectSignals()
{
	connect(SHAPE_UI->checkBox_use_default_bailout, QOverload<int>::of(&QCheckBox::stateChanged), this,
		&cDockRenderingEngine::slotChangedCheckBoxUseDefaultBailout);
	connect(SHAPE_UI->pushButton_optimization_LQ, &QPushButton::clicked, this,
		&cDockRenderingEngine::slotPressedButtonOptimizeForLQ);
	connect(SHAPE_UI->pushButton_optimization_MQ, &QPushButton::clicked, this,
		&cDockRenderingEngine::slotPressedButtonOptimizeForMQ);
	connect(SHAPE_UI->pushButton_optimization_HQ, &QPushButton::clicked, this,
		&cDockRenderingEngine::slotPressedButtonOptimizeForHQ);
	connect(SHAPE_UI->logedit_detail_level, &QLineEdit::returnPressed, this,
		&cDockRenderingEngine::slotDetailLevelChanged);
	connect(SHAPE_UI->comboBox_delta_DE_method, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
		&cDockRenderingEngine::slotChangedComboDistanceEstimationMethod);

	connect(LIMITS_UI->bu_bounding_box_to_limit, &QPushButton::clicked, this,
		&cDockRenderingEngine::slotPressedButtonSetBoundingBoxAsLimits);
	connect(LIMITS_UI->bu_bounding_box_size_x_up, &QToolButton::clicked, this,
		&cDockRenderingEngine::slotPressedButtonBoundingBoxSizeXUp);
	connect(LIMITS_UI->bu_bounding_box_size_x_down, &QToolButton::clicked, this,
		&cDockRenderingEngine::slotPressedButtonBoundingBoxSizeXDown);
	connect(LIMITS_UI->bu_bounding_box_size_y_up, &QToolButton::clicked, this,
		&cDockRenderingEngine::slotPressedButtonBoundingBoxSizeYUp);
	connect(LIMITS_UI->bu_bounding_box_size_y_down, &QToolButton::clicked, this,
		&cDockRenderingEngine::slotPressedButtonBoundingBoxSizeYDown);
	connect(LIMITS_UI->bu_bounding_box_size_z_up, &QToolButton::clicked, this,
		&cDockRenderingEngine::slotPressedButtonBoundingBoxSizeZUp);
	connect(LIMITS_UI->bu_bounding_box_size_z_down, &QToolButton::clicked, this,
		&cDockRenderingEngine::slotPressedButtonBoundingBoxSizeZDown);
	connect(LIMITS_UI->bu_bounding_box_move_x_neg, &QToolButton::clicked, this,
		&cDockRenderingEngine::slotPressedButtonBoundingBoxMoveXNeg);
	connect(LIMITS_UI->bu_bounding_box_move_x_pos, &QToolButton::clicked, this,
		&cDockRenderingEngine::slotPressedButtonBoundingBoxMoveXPos);
	connect(LIMITS_UI->bu_bounding_box_move_y_neg, &QToolButton::clicked, this,
		&cDockRenderingEngine::slotPressedButtonBoundingBoxMoveYNeg);
	connect(LIMITS_UI->bu_bounding_box_move_y_pos, &QToolButton::clicked, this,
		&cDockRenderingEngine::slotPressedButtonBoundingBoxMoveYPos);
	connect(LIMITS_UI->bu_bounding_box_move_z_neg, &QToolButton::clicked, this,
		&cDockRenderingEngine::slotPressedButtonBoundingBoxMoveZNeg);
	connect(LIMITS_UI->bu_bounding_box_move_z_pos, &QToolButton::clicked, this,
		&cDockRenderingEngine::slotPressedButtonBoundingBoxMoveZPos);

	connect(NET_UI->bu_netrender_connect, &QPushButton::clicked, this,
		&cDockRenderingEngine::slotNetRenderClientConnect);
	connect(NET_UI->bu_netrender_disconnect, &QPushButton::clicked, this,
		&cDockRenderingEngine::slotNetRenderClientDisconnect);
	connect(NET_UI->bu_netrender_start_server, &QPushButton::clicked, this,
		&cDockRenderingEngine::slotNetRenderServerStart);
	connect(NET_UI->bu_netrender_stop_server, &QPushButton::clicked, this,
		&cDockRenderingEngine::slotNetRenderServerStop);
	connect(NET_UI->comboBox_netrender_mode, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
		&cDockRenderingEngine::slotNetRenderClientServerChange);
	connect(NET_UI->group_netrender, &QGroupBox::toggled, this,
		&cDockRenderingEngine::slotCheckBoxDisableNetRender);
	connect(gNetRender, &cNetRender::NewStatusClient, this,
		&cDockRenderingEngine::slotNetRenderStatusClientUpdate);
	connect(gNetRender, &cNetRender::NewStatusServer, this,
		&cDockRenderingEngine::slotNetRenderStatusServerUpdate);
	connect(gNetRender, &cNetRender::ClientsChanged, this,
		&cDockRenderingEngine::slotNetRenderClientListUpdate);
	connect(gNetRender, &cNetRender::ClientsChangedRow, this,
		&cDockRenderingEngine::slotNetRenderClientListUpdateRow);
	connect(gNetRender, &cNetRender::ClientsChangedCell, this,
		&cDockRenderingEngine::slotNetRenderClientListUpdateCell);

	connect(SHAPE_UI->checkBox_connect_detail_level_2, QOverload<int>::of(&QCheckBox::stateChanged), this,
		&cDockRenderingEngine::stateChangedConnectDetailLevel);

	connect(SHAPE_UI->pushButton_calculate_dist_thresh, &QPushButton::clicked, this,
		&cDockRenderingEngine::slotCalculateDistanceThreshold);
	connect(SHAPE_UI->pushButton_auto_iter_bailout, &QPushButton::clicked, this,
		&cDockRenderingEngine::slotPressedButtonAutoIterBailout);
	connect(SHAPE_UI->pushButton_auto_slot_iter, &QPushButton::clicked, this,
		&cDockRenderingEngine::slotPressedButtonAutoSlotIter);

	connect(SHAPE_UI->spinboxInt_N, QOverload<int>::of(&QSpinBox::valueChanged), this,
		&cDockRenderingEngine::slotChangedMaxIterations);

	connect(LIMITS_UI->pushButton_auto_iteration_fog, &QPushButton::clicked, this,
		&cDockRenderingEngine::slotPressedButtonAutoIterationFog);
	connect(LIMITS_UI->pushButton_auto_volumetric_fog, &QPushButton::clicked, this,
		&cDockRenderingEngine::slotPressedButtonAutoVolumetricFog);
	connect(LIMITS_UI->pushButton_auto_all_fog, &QPushButton::clicked, this,
		&cDockRenderingEngine::slotPressedButtonAutoAllFog);
	connect(LIMITS_UI->pushButton_auto_clouds, &QPushButton::clicked, this,
		&cDockRenderingEngine::slotPressedButtonAutoClouds);

	connect(NEBULA_UI->pushButton_nebula_auto_brightness_dark, &QPushButton::clicked, this,
		&cDockRenderingEngine::slotPressedButtonAutoBrighnessDark);
	connect(NEBULA_UI->pushButton_nebula_auto_brightness_medium, &QPushButton::clicked, this,
		&cDockRenderingEngine::slotPressedButtonAutoBrighnessMedium);
	connect(NEBULA_UI->pushButton_nebula_auto_brightness_bright, &QPushButton::clicked, this,
		&cDockRenderingEngine::slotPressedButtonAutoBrighnessBright);
}

void cDockRenderingEngine::slotNetRenderServerStart() const
{
	SynchronizeInterfaceWindow(NET_UI->group_netrender, gPar, qInterface::read);
	qint32 port = gPar->Get<int>("netrender_server_local_port");
	gNetRender->SetServer(port);
}

void cDockRenderingEngine::slotNetRenderServerStop()
{
	gNetRender->DeleteServer();
}

void cDockRenderingEngine::slotNetRenderClientConnect() const
{
	SynchronizeInterfaceWindow(NET_UI->group_netrender, gPar, qInterface::read);
	QString address = gPar->Get<QString>("netrender_client_remote_address");
	qint32 port = gPar->Get<int>("netrender_client_remote_port");
	gNetRender->SetClient(address, port);
}

void cDockRenderingEngine::slotNetRenderClientDisconnect()
{
	gNetRender->DeleteClient();
}

void cDockRenderingEngine::slotNetRenderClientServerChange(int index) const
{
	NET_UI->groupBox_netrender_client_config->setVisible(index == cNetRender::netRenderDeviceType_CLIENT);
	NET_UI->groupBox_netrender_server_config->setVisible(index == cNetRender::netRenderDeviceType_SERVER);
}

void cDockRenderingEngine::slotNetRenderClientListUpdate() const
{
	QTableWidget *table = NET_UI->tableWidget_netrender_connected_clients;

	// reset table
	if (gNetRender->GetClientCount() == 0)
	{
		table->clear();
		return;
	}

	// init table
	if (table->columnCount() == 0)
	{
		QStringList header;
		header << tr("Name") << tr("Host") << tr("CPUs") << tr("Status") << tr("Items done")
					 << tr("Actions");
		table->setColumnCount(header.size());
		table->setHorizontalHeaderLabels(header);
	}

	QHeaderView *headers = table->horizontalHeader();
	headers->setSectionResizeMode(QHeaderView::ResizeToContents);

	// change table
	if (table->rowCount() != gNetRender->GetClientCount())
	{
		table->setRowCount(gNetRender->GetClientCount());
	}

	// update table
	for (int i = 0; i < table->rowCount(); i++)
	{
		slotNetRenderClientListUpdateRow(i);
	}
}

void cDockRenderingEngine::slotNetRenderClientListUpdateRow(int i) const
{
	// update row i
	QTableWidget *table = NET_UI->tableWidget_netrender_connected_clients;
	for (int j = 0; j < table->columnCount(); j++)
	{
		slotNetRenderClientListUpdateCell(i, j);
	}
}

void cDockRenderingEngine::slotNetRenderClientListUpdateCell(int i, int j) const
{
	// update element in row i, column j
	QTableWidget *table = NET_UI->tableWidget_netrender_connected_clients;

	QTableWidgetItem *cell = table->item(i, j);
	if (!cell)
	{
		cell = new QTableWidgetItem;
		table->setItem(i, j, cell);
	}

	switch (j)
	{
		case 0: cell->setText(gNetRender->GetClient(i).name); break;
		case 1: cell->setText(gNetRender->GetClient(i).socket->peerAddress().toString()); break;
		case 2: cell->setText(QString::number(gNetRender->GetClient(i).clientWorkerCount)); break;
		case 3:
		{
			QString text = cNetRender::GetStatusText(gNetRender->GetClient(i).status);
			QString color = cNetRender::GetStatusColor(gNetRender->GetClient(i).status);

			cell->setText(text);
			cell->setForeground(QBrush(QColor(color)));
			cell->setBackground(QBrush(Qt::white));
			break;
		}
		case 4: cell->setText(QString::number(gNetRender->GetClient(i).itemsRendered)); break;
		case 5:
		{
			QFrame *frame = new QFrame;
			QGridLayout *gridLayout = new QGridLayout;
			QToolButton *actionKickAndKill = new QToolButton;
			actionKickAndKill->setIcon(actionKickAndKill->style()->standardIcon(QStyle::SP_TrashIcon));
			actionKickAndKill->setFixedSize(24, 24);
			actionKickAndKill->setObjectName(QString::number(i));
			gridLayout->setContentsMargins(2, 2, 2, 2);
			QObject::connect(actionKickAndKill, &QToolButton::clicked, this,
				&cDockRenderingEngine::slotNetRenderKickAndKill);
			gridLayout->addWidget(actionKickAndKill, 0, 0);
			gridLayout->setSpacing(0);
			frame->setLayout(gridLayout);
			table->setCellWidget(i, j, frame);
			break;
		}
		default: break;
	}
}

void cDockRenderingEngine::slotNetRenderStatusServerUpdate() const
{
	QString text = cNetRender::GetStatusText(gNetRender->GetStatus());
	QString color = cNetRender::GetStatusColor(gNetRender->GetStatus());
	NET_UI->label_netrender_server_status->setText(text);
	NET_UI->label_netrender_server_status->setStyleSheet(
				"QLabel { color: " + color + "; font-weight: bold; border: 2px solid darkgray; border-radius: 3px;"
						"background: white; text-align: center; qproperty-alignment: AlignCenter;}");

	NET_UI->bu_netrender_start_server->setEnabled(!gNetRender->IsServer());
	NET_UI->bu_netrender_stop_server->setEnabled(gNetRender->IsServer());
}

void cDockRenderingEngine::slotNetRenderStatusClientUpdate() const
{
	CHECK_MAIN_INTERFACE();
	QString text = cNetRender::GetStatusText(gNetRender->GetStatus());
	QString color = cNetRender::GetStatusColor(gNetRender->GetStatus());
	NET_UI->label_netrender_client_connected_server->setText(gNetRender->GetServerName());
	NET_UI->label_netrender_client_status->setText(text);
	NET_UI->label_netrender_client_status->setStyleSheet(
		"QLabel { color: " + color + "; font-weight: bold; border: 2px solid darkgray; border-radius: 3px;"
				"background: white; text-align: center; qproperty-alignment: AlignCenter;}");

	NET_UI->bu_netrender_connect->setEnabled(!gNetRender->IsClient());
	NET_UI->bu_netrender_disconnect->setEnabled(gNetRender->IsClient());
	gMainInterface->mainWindow->GetWidgetDockNavigation()->setEnabled(!gNetRender->IsClient());
}

void cDockRenderingEngine::slotCheckBoxDisableNetRender(bool on)
{
	if (!on)
	{
		gNetRender->DeleteClient();
		gNetRender->DeleteServer();
	}
}

void cDockRenderingEngine::slotNetRenderKickAndKill()
{
	QString buttonName = sender()->objectName();
	gNetRender->KickAndKillClient(buttonName.toInt());
}

void cDockRenderingEngine::SynchronizeInterfaceDistanceEstimation(
	std::shared_ptr<cParameterContainer> par) const
{
	SynchronizeInterfaceWindow(SHAPE_UI->groupBox_detailLevel, par, qInterface::write);
}

void cDockRenderingEngine::ComboDeltaDEFunctionSetEnabled(bool enabled) const
{
	SHAPE_UI->comboBox_delta_DE_function->setEnabled(enabled);
}

int cDockRenderingEngine::ComboDeltaDEMethodCurrentIndex() const
{
	return SHAPE_UI->comboBox_delta_DE_method->currentIndex();
}

void cDockRenderingEngine::slotChangedComboDistanceEstimationMethod(int index) const
{
	CHECK_MAIN_INTERFACE();
	Q_UNUSED(index);
	// SHAPE_UI->comboBox_delta_DE_function->setEnabled(
	//	gMainInterface->mainWindow->GetWidgetDockFractal()->AreHybridFractalsEnabled()
	//	|| index == int(fractal::forceDeltaDEMethod));
}

void cDockRenderingEngine::CheckboxConnectDetailLevelSetCheckState(Qt::CheckState state) const
{
	SHAPE_UI->checkBox_connect_detail_level_2->setCheckState(state);
}

void cDockRenderingEngine::UpdateLabelWrongDEPercentage(const QString &text) const
{
	SHAPE_UI->label_wrong_DE_percentage->setText(text);
}

void cDockRenderingEngine::UpdateLabelUsedDistanceEstimation(const QString &text) const
{
	SHAPE_UI->label_used_distance_estimation->setText(text);
}

void cDockRenderingEngine::slotChangedCheckBoxUseDefaultBailout(int state) const
{
	SHAPE_UI->logedit_bailout->setEnabled(!state);
}

void cDockRenderingEngine::slotDetailLevelChanged()
{
	CHECK_MAIN_INTERFACE();
	if (gMainInterface->mainWindow->GetWidgetDockImageAdjustments()->IsConnectDetailLevelEnabled())
	{
		gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::read);
		gMainInterface->lockedDetailLevel = gPar->Get<double>("detail_level");
		gMainInterface->lockedImageResolution =
			CVector2<int>(gPar->Get<int>("image_width"), gPar->Get<int>("image_height"));
	}
}

void cDockRenderingEngine::slotPressedButtonOptimizeForLQ()
{
	CHECK_MAIN_INTERFACE();
	gMainInterface->OptimizeStepFactor(1.0);
}

void cDockRenderingEngine::slotPressedButtonOptimizeForMQ()
{
	CHECK_MAIN_INTERFACE();
	gMainInterface->OptimizeStepFactor(0.1);
}
void cDockRenderingEngine::slotPressedButtonOptimizeForHQ()
{
	CHECK_MAIN_INTERFACE();
	gMainInterface->OptimizeStepFactor(0.01);
}
void cDockRenderingEngine::slotPressedButtonSetBoundingBoxAsLimits()
{
	CHECK_MAIN_INTERFACE();
	gMainInterface->SetBoundingBoxAsLimitsTotal();
}
void cDockRenderingEngine::slotPressedButtonBoundingBoxSizeXUp()
{
	CHECK_MAIN_INTERFACE();
	gMainInterface->BoundingBoxMove('x', 0.05, 0.05);
}
void cDockRenderingEngine::slotPressedButtonBoundingBoxSizeXDown()
{
	CHECK_MAIN_INTERFACE();
	gMainInterface->BoundingBoxMove('x', -0.05, -0.05);
}
void cDockRenderingEngine::slotPressedButtonBoundingBoxSizeYUp()
{
	CHECK_MAIN_INTERFACE();
	gMainInterface->BoundingBoxMove('y', 0.05, 0.05);
}
void cDockRenderingEngine::slotPressedButtonBoundingBoxSizeYDown()
{
	CHECK_MAIN_INTERFACE();
	gMainInterface->BoundingBoxMove('y', -0.05, -0.05);
}
void cDockRenderingEngine::slotPressedButtonBoundingBoxSizeZUp()
{
	CHECK_MAIN_INTERFACE();
	gMainInterface->BoundingBoxMove('z', 0.05, 0.05);
}
void cDockRenderingEngine::slotPressedButtonBoundingBoxSizeZDown()
{
	CHECK_MAIN_INTERFACE();
	gMainInterface->BoundingBoxMove('z', -0.05, -0.05);
}
void cDockRenderingEngine::slotPressedButtonBoundingBoxMoveXNeg()
{
	CHECK_MAIN_INTERFACE();
	gMainInterface->BoundingBoxMove('x', -0.05, 0.05);
}
void cDockRenderingEngine::slotPressedButtonBoundingBoxMoveXPos()
{
	CHECK_MAIN_INTERFACE();
	gMainInterface->BoundingBoxMove('x', 0.05, -0.05);
}
void cDockRenderingEngine::slotPressedButtonBoundingBoxMoveYNeg()
{
	CHECK_MAIN_INTERFACE();
	gMainInterface->BoundingBoxMove('y', -0.05, 0.05);
}
void cDockRenderingEngine::slotPressedButtonBoundingBoxMoveYPos()
{
	CHECK_MAIN_INTERFACE();
	gMainInterface->BoundingBoxMove('y', 0.05, -0.05);
}
void cDockRenderingEngine::slotPressedButtonBoundingBoxMoveZNeg()
{
	CHECK_MAIN_INTERFACE();
	gMainInterface->BoundingBoxMove('z', -0.05, 0.05);
}
void cDockRenderingEngine::slotPressedButtonBoundingBoxMoveZPos()
{
	CHECK_MAIN_INTERFACE();
	gMainInterface->BoundingBoxMove('z', 0.05, -0.05);
}

void cDockRenderingEngine::slotCalculateDistanceThreshold()
{
	CHECK_MAIN_INTERFACE();
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::read);
	double distance = gMainInterface->GetDistanceForPoint(gPar->Get<CVector3>("camera"));
	double detailLevel = gPar->Get<double>("detail_level");
	double imageWidth = gPar->Get<int>("image_width");
	params::enumPerspectiveType perspectiveType =
		params::enumPerspectiveType(gPar->Get<int>("perspective_type"));
	double fov = CalcFOV(gPar->Get<int>("fov"), perspectiveType);
	double distThresh = fov / detailLevel / imageWidth * distance * 10.0;
	gPar->Set("DE_thresh", distThresh);
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}

void cDockRenderingEngine::slotPressedButtonAutoIterBailout()
{
	CHECK_MAIN_INTERFACE();
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::read);

	sRenderData renderData;
	renderData.objectData.resize(NUMBER_OF_FRACTALS);
	cNineFractals fractals(gParFractal, gPar);
	sParamRender paramRender(gPar, &renderData.objectData);

	const autoIterBailout::sAutoIterBailoutResult result =
		autoIterBailout::EstimateGlobalIterBailout(paramRender, fractals, gPar);

	autoIterBailout::ApplyGlobalEstimates(gPar, result);
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);

	if (SHAPE_UI->label_auto_iter_result)
		SHAPE_UI->label_auto_iter_result->setText(autoIterBailout::FormatResultLabel(result));
}

void cDockRenderingEngine::slotPressedButtonAutoSlotIter()
{
	CHECK_MAIN_INTERFACE();
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::read);
	autoIterBailout::ApplyPerSlotEstimates(gPar, gParFractal);
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);

	if (SHAPE_UI->label_auto_iter_result)
		SHAPE_UI->label_auto_iter_result->setText(tr("Per-slot formula_maxiter values updated"));
}

void cDockRenderingEngine::slotChangedMaxIterations(int value)
{
	CHECK_MAIN_INTERFACE();
	gPar->Set("N", value);
	SyncFormulaMaxiterToN(gPar);
	gMainInterface->mainWindow->GetWidgetDockFractal()->SynchronizeInterfaceFractals(
		gPar, gParFractal, qInterface::write);
}

void cDockRenderingEngine::slotPressedButtonAutoIterationFog()
{
	QString status;
	const bool ok = RunAutoFogFromRenderSettings(
		this, autoFog::eAutoFogTuneMode::IterationOnly, &status);
	if (LIMITS_UI->label_auto_fog_result) LIMITS_UI->label_auto_fog_result->setText(status);
	if (!ok)
	{
		QMessageBox::warning(this, tr("Auto Iteration Fog"),
			tr("Could not detect fractal surface from current camera position.\n"
				"Try moving the camera closer to the fractal and try again."));
	}
}

void cDockRenderingEngine::slotPressedButtonAutoVolumetricFog()
{
	QString status;
	const bool ok = RunAutoFogFromRenderSettings(
		this, autoFog::eAutoFogTuneMode::DistanceOnly, &status);
	if (LIMITS_UI->label_auto_fog_result)
	{
		LIMITS_UI->label_auto_fog_result->setText(
			ok ? tr("Volumetric fog tuned from scene probe.") : status);
	}
	if (!ok)
	{
		QMessageBox::warning(this, tr("Auto Volumetric Fog"),
			tr("Could not detect fractal surface from current camera position.\n"
				"Try moving the camera closer to the fractal and try again."));
	}
}

void cDockRenderingEngine::slotPressedButtonAutoAllFog()
{
	QString status;
	const bool ok = RunAutoFogFromRenderSettings(this, autoFog::eAutoFogTuneMode::All, &status);
	if (LIMITS_UI->label_auto_fog_result) LIMITS_UI->label_auto_fog_result->setText(status);
	if (!ok)
	{
		QMessageBox::warning(this, tr("Auto Fog"),
			tr("Could not detect fractal surface from current camera position.\n"
				"Try moving the camera closer to the fractal and try again."));
	}
}

void cDockRenderingEngine::slotPressedButtonAutoClouds()
{
	if (!gMainInterface || !gMainInterface->mainWindow) return;

	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::read);
	cloudPresets::ApplyPreset(gPar, cloudPresets::ePreset::VolumetricClouds);
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);

	if (LIMITS_UI->label_auto_fog_result)
	{
		LIMITS_UI->label_auto_fog_result->setText(
			tr("Applied Volumetric Clouds preset and enabled clouds."));
	}
}

void cDockRenderingEngine::slotPressedButtonAutoBrighnessDark()
{
	CHECK_MAIN_INTERFACE();
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::read);
	double averageBrightness = gMainInterface->mainImage->GetAverageBrightness();
	//qDebug() << "Average brightness:" << averageBrightness;
	double oldBrighness = gPar->Get<double>("nebula_brightness");
	double newBrighness = oldBrighness * 0.05 / averageBrightness;
	gPar->Set("nebula_brightness", newBrighness);
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}

void cDockRenderingEngine::slotPressedButtonAutoBrighnessMedium()
{
	CHECK_MAIN_INTERFACE();
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::read);
	double averageBrightness = gMainInterface->mainImage->GetAverageBrightness();
	double oldBrighness = gPar->Get<double>("nebula_brightness");
	double newBrighness = oldBrighness * 0.15 / averageBrightness;
	gPar->Set("nebula_brightness", newBrighness);
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}

void cDockRenderingEngine::slotPressedButtonAutoBrighnessBright()
{
	CHECK_MAIN_INTERFACE();
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::read);
	double averageBrightness = gMainInterface->mainImage->GetAverageBrightness();
	double oldBrighness = gPar->Get<double>("nebula_brightness");
	double newBrighness = oldBrighness * 0.5 / averageBrightness;
	gPar->Set("nebula_brightness", newBrighness);
	gMainInterface->SynchronizeInterface(gPar, gParFractal, qInterface::write);
}
