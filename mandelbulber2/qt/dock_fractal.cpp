/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2016-23 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * Widget which contains UI for fractals
 */

#include "dock_fractal.h"

#include "ui_dock_fractal.h"

#include "dock_rendering_engine.h"
#include "my_tab_bar.h"

#include "src/ao_modes.h"
#include "src/automated_widgets.hpp"
#include "src/error_message.hpp"
#include "src/fractal_enums.h"
#include "src/global_data.hpp"
#include "src/initparameters.hpp"
#include "src/interface.hpp"
#include "src/render_window.hpp"
#include "src/rendered_image_widget.hpp"
#include "src/write_log.hpp"

#include <QClipboard>
#include <QRandomGenerator>
#include <QDateTime>

#include "formula/definition/all_fractal_list.hpp"
#include "julia_heatmap_widget.h"
#include "navigator_window.h"

cDockFractal::cDockFractal(QWidget *parent)
		: QWidget(parent), cMyWidgetWithParams(), ui(new Ui::cDockFractal)
{
	ui->setupUi(this);

	fractalTabs.resize(NUMBER_OF_FRACTALS);
	for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
	{
		fractalTabs[i] =
			ui->tabWidget_fractals->findChild<cTabFractal *>(QString("widgetTabFractal_%1").arg(i + 1));
	}

	automatedWidgets = new cAutomatedWidgets(this);
	automatedWidgets->ConnectSignalsForSlidersInWindow(this);

	ui->label_repeat_from->setEnabled(false);
	ui->spinboxInt_repeat_from->setEnabled(false);
	ui->label_fractals_remark_julia->setVisible(false);

	ui->previewwidget_julia->SetSize(256, 256, 2);

	ui->tabWidget_fractals->setUsesScrollButtons(true);
	ui->tabWidget_fractals->setDocumentMode(true);
	ui->tabWidget_fractals->setElideMode(Qt::ElideNone);

	ConnectSignals();
	SetupJuliaExplorer();
	SetupJuliaHeatmap();
}

cDockFractal::~cDockFractal()
{
	if (sweepTimer)
	{
		sweepTimer->stop();
		delete sweepTimer;
	}
	delete ui;
}

bool cDockFractal::AreHybridFractalsEnabled() const
{
	return ui->checkBox_hybrid_fractal_enable->isChecked();
}

void cDockFractal::SynchronizeInterfaceFractals(std::shared_ptr<cParameterContainer> par,
	std::shared_ptr<cFractalContainer> parFractal, qInterface::enumReadWrite mode) const
{
	WriteLog("cInterface::SynchronizeInterface: tabWidget_fractal_common", 3);
	SynchronizeInterfaceWindow(ui->tabWidget_fractal_common, par, mode);
	WriteLog("cInterface::SynchronizeInterface: tabWidget_fractal_hybrid", 3);
	SynchronizeInterfaceWindow(ui->tabWidget_fractal_hybrid, par, mode);
	WriteLog("cInterface::SynchronizeInterface: tab_primitives", 3);
	SynchronizeInterfaceWindow(ui->tab_primitives, par, mode);
	// Directly synchronize widgetPrimitivesManager to ensure primitive widgets are found
	cPrimitivesManager *pm = ui->tab_primitives->findChild<cPrimitivesManager *>("widgetPrimitivesManager");
	if (pm) {
		SynchronizeInterfaceWindow(pm, par, mode);
	}

	WriteLog("cInterface::SynchronizeInterface: tab_description", 3);
	SynchronizeInterfaceWindow(ui->tab_description, par, mode);

	WriteLog("cInterface::SynchronizeInterface: tabWidget_fractals", 3);
	SynchronizeInterfaceWindow(ui->tabWidget_fractals->tabBar(), par, mode);

	for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
	{
		WriteLog("cInterface::SynchronizeInterface: fractalWidgets[i]", 3);
		fractalTabs[i]->SynchronizeFractal(parFractal->at(i), mode);
		fractalTabs[i]->SynchronizeInterface(par, mode);
	}
}

void cDockFractal::slotSynchronizeInterfaceJulia(std::shared_ptr<cParameterContainer> par) const
{
	SynchronizeInterfaceWindow(ui->groupCheck_julia_mode, par, qInterface::write);
}

void cDockFractal::slotSynchronizeInterfacePrimitives(
	std::shared_ptr<cParameterContainer> par) const
{
	SynchronizeInterfaceWindow(ui->scrollArea_primitives, par, qInterface::write);
}

void cDockFractal::slotEnableJuliaMode() const
{
	ui->groupCheck_julia_mode->setChecked(true);
}

QWidget *cDockFractal::GetContainerWithPrimitives() const
{
	return ui->scrollAreaWidgetContents_primitives;
}

QVBoxLayout *cDockFractal::GetLayoutWithPrimitives() const
{
	return ui->verticalLayout_primitives;
}

bool cDockFractal::AreBooleanFractalsEnabled() const
{
	return ui->groupCheck_boolean_operators->isChecked();
}

void cDockFractal::SetTabText(int tabIndex, QString text) const
{
	ui->tabWidget_fractals->setTabText(tabIndex, text);
}

void cDockFractal::ConnectSignals() const
{
	connect(
		ui->vect3_julia_c_x, SIGNAL(textChanged(const QString &)), this, SLOT(slotChangedJuliaPoint()));
	connect(
		ui->vect3_julia_c_y, SIGNAL(textChanged(const QString &)), this, SLOT(slotChangedJuliaPoint()));
	connect(
		ui->vect3_julia_c_z, SIGNAL(textChanged(const QString &)), this, SLOT(slotChangedJuliaPoint()));
	connect(ui->logedit_julia_preview_distance, SIGNAL(textChanged(const QString &)), this,
		SLOT(slotChangedJuliaPoint()));

	connect(ui->pushButton_get_julia_constant, SIGNAL(clicked()), this,
		SLOT(slotPressedButtonGetJuliaConstant()));

	connect(ui->groupCheck_julia_mode, SIGNAL(toggled(bool)), this,
		SLOT(slotGroupCheckJuliaModeToggled(bool)));

	connect(ui->checkBox_hybrid_fractal_enable, SIGNAL(stateChanged(int)), this,
		SLOT(slotChangedCheckBoxHybridFractal(int)));
	connect(ui->groupCheck_boolean_operators, SIGNAL(toggled(bool)), this,
		SLOT(slotChangedCheckBoxBooleanOperators(bool)));
	connect(ui->groupCheck_julia_mode, SIGNAL(toggled(bool)), this,
		SLOT(slotChangedCheckBoxJuliaMode(bool)));
	connect(ui->tabWidget_fractals->tabBar(), SIGNAL(toggledEnable(int, bool)), this,
		SLOT(slotToggledFractalEnable(int, bool)));
	connect(ui->tabWidget_fractals->tabBar(), SIGNAL(currentChanged(int)), this,
		SLOT(slotChangedFractalTab(int)));
	connect(
		ui->pushButton_local_navi, &QPushButton::clicked, this, &cDockFractal::slotPressedButtonNavi);

	connect(
		ui->tabWidget_fractals, SIGNAL(swapTabs(int, int)), this, SLOT(slotFractalSwap(int, int)));

	connect(ui->widgetPrimitivesManager, &cPrimitivesManager::signalUpdatePrimitivesCombos, this,
		&cDockFractal::signalUpdatePrimitivesCombos);
}

// initialize ui for hybrid fractal components
void cDockFractal::InitializeFractalUi() const
{
	WriteLog("cInterface::InitializeFractalUi(QString &uiFileName) started", 2);
	// MyUiLoader loader;

	// QFile uiFile(uiFileName);

	// if (uiFile.exists())
	//{
	//		uiFile.open(QFile::ReadOnly);
	//		fractalWidgets[0] = loader.load(&uiFile);
	//		ui->verticalLayout_fractal_1->addWidget(fractalWidgets[0]);
	//		fractalWidgets[0]->show();

	for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
	{
		if (i == 0)
			ui->tabWidget_fractals->setTabText(i, QString("#1: Mandelbulb"));
		else
		{
			ui->tabWidget_fractals->setTabText(i, QString("#%1: None").arg(i + 1));
			ui->tabWidget_fractals
				->findChild<QScrollArea *>("scrollArea_fractal_" + QString::number(i + 1))
				->setEnabled(false);
		}
		fractalTabs[i]->AssignParameterContainers(params, fractalParams);
		fractalTabs[i]->Init(i == 0, i);
		fractalTabs[i]->AssignParentDockFractal(this);
	}

	static_cast<MyTabBar *>(ui->tabWidget_fractals->tabBar())->setupMoveButtons();

	//}
	WriteLog("cInterface::InitializeFractalUi(QString &uiFileName) finished", 2);
}

void cDockFractal::slotFractalSwap(int swapA, int swapB) const
{
	// qDebug() << "swapping " << swapA << " with " << swapB;

	// read all data from ui
	SynchronizeInterfaceFractals(params, fractalParams, qInterface::read);

	// swap formula specific fields in gPar
	QStringList gParFormulaSpecificFields({"formula", "formula_iterations", "formula_weight",
		"formula_start_iteration", "formula_stop_iteration", "julia_mode", "julia_c",
		"fractal_constant_factor", "formula_position", "formula_rotation", "formula_repeat",
		"formula_scale", "dont_add_c_constant", "check_for_bailout", "formula_maxiter",
		"smooth_de_combine_enable", "smooth_de_combine_distance"});

	for (int i = 0; i < gParFormulaSpecificFields.size(); i++)
	{
		// to keep original properties of parameters
		cOneParameter formulaA =
			params->GetAsOneParameter(gParFormulaSpecificFields.at(i) + "_" + QString::number(swapA + 1));
		cOneParameter formulaB =
			params->GetAsOneParameter(gParFormulaSpecificFields.at(i) + "_" + QString::number(swapB + 1));

		// get only actual values and swap between slots
		cMultiVal multiA = formulaB.GetMultiVal(parameterContainer::valueActual);
		cMultiVal multiB = formulaA.GetMultiVal(parameterContainer::valueActual);

		// write values to OneParameters
		formulaA.SetMultiVal(multiA, parameterContainer::valueActual);
		formulaB.SetMultiVal(multiB, parameterContainer::valueActual);

		// writing parameters to original containers
		params->SetFromOneParameter(
			gParFormulaSpecificFields.at(i) + "_" + QString::number(swapA + 1), formulaA);
		params->SetFromOneParameter(
			gParFormulaSpecificFields.at(i) + "_" + QString::number(swapB + 1), formulaB);
	}

	// swap formula specific fields in fractalParams by swapping whole container
	fractalTabs[swapA]->SynchronizeFractal(fractalParams->at(swapB), qInterface::read);
	fractalTabs[swapB]->SynchronizeFractal(fractalParams->at(swapA), qInterface::read);

	// write swapped changes to ui
	SynchronizeInterfaceFractals(params, fractalParams, qInterface::write);
}

void cDockFractal::slotChangedCheckBoxBooleanOperators(bool state) const
{
	if (state) ui->checkBox_hybrid_fractal_enable->setChecked(false);
	gApplication->processEvents();

	for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
	{
		if (i > 0)
		{
			fractalTabs[i]->FrameIterationFormulaSetEnabled(state);
			ui->tabWidget_fractals
				->findChild<QScrollArea *>("scrollArea_fractal_" + QString::number(i + 1))
				->setEnabled(state);
		}

		fractalTabs[i]->FormulaTransformSetVisible(state);

		const fractal::enumCPixelAddition cPixelAddition =
			newFractalList[fractalTabs[i]->GetCurrentFractalIndexOnList()]->getCpixelAddition();

		if (cPixelAddition == fractal::cpixelAlreadyHas)
			fractalTabs[i]->CConstantAdditionSetVisible(false);
		else
			fractalTabs[i]->CConstantAdditionSetVisible(state);

		fractalTabs[i]->MaterialSetVisible(state);
		fractalTabs[i]->CalculationParametersSetVisible(state);
	}

	gMainInterface->mainWindow->GetWidgetDockRenderingEngine()->ComboDeltaDEFunctionSetEnabled(
		!state);
	ui->groupBox_material_fractal->setVisible(!state);
}

void cDockFractal::slotChangedCheckBoxHybridFractal(int state) const
{
	if (state) ui->groupCheck_boolean_operators->setChecked(false);
	gApplication->processEvents();

	for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
	{
		fractalTabs[i]->FrameIterationFormulaSetWidgetsVisibility(state);
		if (i > 0)
		{
			fractalTabs[i]->FrameIterationFormulaSetEnabled(state);
			ui->tabWidget_fractals
				->findChild<QScrollArea *>("scrollArea_fractal_" + QString::number(i + 1))
				->setEnabled(state);
		}
	}

	ui->label_fractals_remark_hybrid->setVisible(!state);
	ui->label_repeat_from->setEnabled(state);
	ui->spinboxInt_repeat_from->setEnabled(state);
}

void cDockFractal::slotChangedCheckBoxJuliaMode(bool state) const
{
	ui->label_fractals_remark_julia->setVisible(state);
}

void cDockFractal::slotToggledFractalEnable(int fractalIndex, bool enabled) const
{
	ui->tabWidget_fractals->widget(fractalIndex - 1)->setEnabled(enabled);
}

void cDockFractal::slotGroupCheckJuliaModeToggled(bool state)
{
	if (state)
	{
		gMainInterface->DisablePeriodicRefresh();
	}
}

void cDockFractal::slotChangedJuliaPoint() const
{
	if (ui->groupBox_julia_preview && ui->groupCheck_julia_mode->isChecked()
			&& params->Get<bool>("julia_preview") && gInterfaceReadyForSynchronization)
	{
		std::shared_ptr<cParameterContainer> params(new cParameterContainer());
		InitParams(params);
		InitMaterialParams(1, params);
		SynchronizeInterfaceWindow(ui->groupCheck_julia_mode, params, qInterface::read);
		params->SetContainerName("juliaPreview");

		const double cameraDistance = params->Get<double>("julia_preview_distance");
		CVector3 target(0.0, 0.0, 0.0);
		CVector3 direction = params->Get<CVector3>("camera") - params->Get<CVector3>("target");
		direction.Normalize();
		CVector3 camera = target + direction * cameraDistance;

		params->Set("camera", camera);
		params->Set("target", target);
		params->Set("julia_mode", true);
		params->Set("ambient_occlusion_enabled", true);
		params->Set("ambient_occlusion_mode", int(params::AOModeFast));
		params->Copy("camera_top", params);
		for (int i = 1; i <= NUMBER_OF_FRACTALS; i++)
		{
			params->Copy(QString("formula_%1").arg(i), params);
			params->Copy(QString("formula_iterations_%1").arg(i), params);
			params->Copy(QString("fractal_enable_%1").arg(i), params);
			params->Copy(QString("formula_weight_%1").arg(i), params);
			params->Copy(QString("formula_start_iteration_%1").arg(i), params);
			params->Copy(QString("formula_stop_iteration_%1").arg(i), params);
			params->Copy(QString("dont_add_c_constant_%1").arg(i), params);
			params->Copy(QString("check_for_bailout_%1").arg(i), params);
		}
		params->Copy("hybrid_fractal_enable", params);
		params->Copy("fractal_constant_factor", params);
		params->Copy("opencl_mode", params);
		params->Copy("opencl_enabled", params);

		ui->previewwidget_julia->AssignParameters(params, fractalParams);
		ui->previewwidget_julia->update();
	}
}

void cDockFractal::slotPressedButtonGetJuliaConstant()
{
	QList<QVariant> item;
	item.append(int(RenderedImage::clickGetJuliaConstant));
	int index = gMainInterface->mainWindow->GetComboBoxMouseClickFunction()->findData(item);
	gMainInterface->mainWindow->GetComboBoxMouseClickFunction()->setCurrentIndex(index);
	gMainInterface->renderedImage->setClickMode(item);
}

void cDockFractal::slotChangedFractalTab(int index)
{
	if (index > 0)
	{
		if (!ui->checkBox_hybrid_fractal_enable->isChecked()
				&& !ui->groupCheck_boolean_operators->isChecked())
		{
			QMessageBox message;
			;

			QPushButton *buttonHybrid =
				message.addButton(tr("Enable hybrid fractals"), QMessageBox::AcceptRole);
			QPushButton *buttonBoolean =
				message.addButton(tr("Enable boolean mode"), QMessageBox::AcceptRole);
			const QPushButton *buttonCancel = message.addButton(QMessageBox::Cancel);

			message.setText(tr(
				"You have selected next fractal formula.\nDo you want to enable hybrid fractals or boolean "
				"mode?"));
			message.setWindowTitle(tr("More fractals..."));
			message.setIcon(QMessageBox::Question);
			const int result = message.exec();
			Q_UNUSED(result);

			if (message.clickedButton() != buttonCancel)
			{
				if (message.clickedButton() == buttonHybrid)
				{
					ui->checkBox_hybrid_fractal_enable->setChecked(true);
				}
				else if (message.clickedButton() == buttonBoolean)
				{
					ui->groupCheck_boolean_operators->setChecked(true);
				}
			}
		}
	}
}

void cDockFractal::AssignParameterContainers(
	std::shared_ptr<cParameterContainer> _params, std::shared_ptr<cFractalContainer> _fractalParams)
{
	cMyWidgetWithParams::AssignParameterContainers(_params, _fractalParams);
	ui->widgetPrimitivesManager->AssignParameterContainers(_params, _fractalParams);
	ui->widgetPrimitivesManager->Init();
}

void cDockFractal::AssignSpecialWidgets(
	RenderedImage *_renderedImage, QComboBox *_mouseFunctionCombo)
{
	cMyWidgetWithParams::AssignSpecialWidgets(_renderedImage, _mouseFunctionCombo);
	ui->widgetPrimitivesManager->AssignSpecialWidgets(_renderedImage, _mouseFunctionCombo);
}

void cDockFractal::RegeneratePrimitives()
{
	ui->widgetPrimitivesManager->Regenerate();
}

void cDockFractal::slotPressedButtonNavi()
{
	gMainInterface->SynchronizeInterface(params, fractalParams, qInterface::read);
	cNavigatorWindow *navigator = new cNavigatorWindow();
	cDockFractal *leftWidget = new cDockFractal();
	navigator->AddLeftWidget(leftWidget);
	navigator->setAttribute(Qt::WA_DeleteOnClose);
	navigator->SetInitialParameters(params, fractalParams);
	navigator->SetMouseClickFunction(gMainInterface->GetMouseClickFunction());
	leftWidget->HideSomeWidgetsForNavi();
	leftWidget->InitializeFractalUi();
	navigator->SynchronizeInterface(qInterface::write);

	connect(navigator, &cNavigatorWindow::signalChangesAccepted, this,
		&cDockFractal::slotNewParametersFromNavi);

	navigator->show();
	navigator->AllPrepared();
}

void cDockFractal::slotNewParametersFromNavi()
{
	RegeneratePrimitives();
}

void cDockFractal::HideSomeWidgetsForNavi()
{
	delete ui->pushButton_get_julia_constant;
	ui->pushButton_get_julia_constant = nullptr;
	delete ui->groupBox_julia_preview;
	ui->groupBox_julia_preview = nullptr;
}

// ===== 3x3lion Julia Explorer =====

void cDockFractal::SetupJuliaExplorer()
{
	// Default range: ±2.0 (index 2)
	if (ui->comboBox_julia_range) ui->comboBox_julia_range->setCurrentIndex(2);

	sweepTimer = new QTimer(this);
	sweepTimer->setInterval(100);

	ConnectJuliaExplorerSignals();
}

void cDockFractal::ConnectJuliaExplorerSignals()
{
	// Sliders
	if (ui->slider_julia_cx)
		connect(ui->slider_julia_cx, SIGNAL(valueChanged(int)), this, SLOT(slotJuliaSliderCxChanged(int)));
	if (ui->slider_julia_cy)
		connect(ui->slider_julia_cy, SIGNAL(valueChanged(int)), this, SLOT(slotJuliaSliderCyChanged(int)));
	if (ui->slider_julia_cz)
		connect(ui->slider_julia_cz, SIGNAL(valueChanged(int)), this, SLOT(slotJuliaSliderCzChanged(int)));

	// Range combo
	if (ui->comboBox_julia_range)
		connect(ui->comboBox_julia_range, SIGNAL(currentIndexChanged(int)), this, SLOT(slotJuliaRangeChanged(int)));

	// Action buttons
	if (ui->pushButton_julia_copy)
		connect(ui->pushButton_julia_copy, SIGNAL(clicked()), this, SLOT(slotJuliaCopy()));
	if (ui->pushButton_julia_paste)
		connect(ui->pushButton_julia_paste, SIGNAL(clicked()), this, SLOT(slotJuliaPaste()));
	if (ui->pushButton_julia_random)
		connect(ui->pushButton_julia_random, SIGNAL(clicked()), this, SLOT(slotJuliaRandom()));
	if (ui->pushButton_julia_zero)
		connect(ui->pushButton_julia_zero, SIGNAL(clicked()), this, SLOT(slotJuliaZero()));

	// Presets (use lambda to pass index)
	QPushButton *presetButtons[] = {
		ui->pushButton_julia_preset_1, ui->pushButton_julia_preset_2, ui->pushButton_julia_preset_3,
		ui->pushButton_julia_preset_4, ui->pushButton_julia_preset_5, ui->pushButton_julia_preset_6,
		ui->pushButton_julia_preset_7, ui->pushButton_julia_preset_8, ui->pushButton_julia_preset_9
	};
	for (int i = 0; i < 9; i++)
	{
		if (presetButtons[i])
		{
			connect(presetButtons[i], &QPushButton::clicked, this, [this, i]() { slotJuliaPreset(i); });
		}
	}

	// Sweep
	if (ui->pushButton_julia_sweep_start)
		connect(ui->pushButton_julia_sweep_start, SIGNAL(clicked()), this, SLOT(slotJuliaSweepStart()));
	if (ui->pushButton_julia_sweep_stop)
		connect(ui->pushButton_julia_sweep_stop, SIGNAL(clicked()), this, SLOT(slotJuliaSweepStop()));
	if (sweepTimer)
		connect(sweepTimer, SIGNAL(timeout()), this, SLOT(slotJuliaSweepStep()));

	// History
	if (ui->listWidget_julia_history)
		connect(ui->listWidget_julia_history, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
			this, SLOT(slotJuliaHistoryItemDoubleClicked(QListWidgetItem *)));
	if (ui->pushButton_julia_history_save)
		connect(ui->pushButton_julia_history_save, SIGNAL(clicked()), this, SLOT(slotJuliaHistorySave()));
	if (ui->pushButton_julia_history_clear)
		connect(ui->pushButton_julia_history_clear, SIGNAL(clicked()), this, SLOT(slotJuliaHistoryClear()));
}

double cDockFractal::JuliaSliderRange() const
{
	if (!ui->comboBox_julia_range) return 2.0;
	switch (ui->comboBox_julia_range->currentIndex())
	{
		case 0: return 0.5;
		case 1: return 1.0;
		case 2: return 2.0;
		case 3: return 5.0;
		case 4: return 10.0;
		default: return 2.0;
	}
}

void cDockFractal::UpdateJuliaSliderLabels()
{
	double range = JuliaSliderRange();
	if (ui->slider_julia_cx && ui->label_julia_cx_value)
	{
		double val = ui->slider_julia_cx->value() / 1000.0 * range;
		ui->label_julia_cx_value->setText(QString::number(val, 'f', 3));
	}
	if (ui->slider_julia_cy && ui->label_julia_cy_value)
	{
		double val = ui->slider_julia_cy->value() / 1000.0 * range;
		ui->label_julia_cy_value->setText(QString::number(val, 'f', 3));
	}
	if (ui->slider_julia_cz && ui->label_julia_cz_value)
	{
		double val = ui->slider_julia_cz->value() / 1000.0 * range;
		ui->label_julia_cz_value->setText(QString::number(val, 'f', 3));
	}
}

void cDockFractal::AddToJuliaHistory(double cx, double cy, double cz)
{
	sJuliaHistoryEntry entry;
	entry.cx = cx;
	entry.cy = cy;
	entry.cz = cz;
	entry.timestamp = QDateTime::currentDateTime().toString("HH:mm:ss");

	// Avoid duplicates at the top
	if (!juliaHistory.isEmpty())
	{
		const auto &last = juliaHistory.last();
		if (qFuzzyCompare(last.cx, cx) && qFuzzyCompare(last.cy, cy) && qFuzzyCompare(last.cz, cz))
			return;
	}

	juliaHistory.append(entry);

	// Keep max 50 entries
	while (juliaHistory.size() > 50) juliaHistory.removeFirst();

	// Update list widget
	if (ui->listWidget_julia_history)
	{
		ui->listWidget_julia_history->clear();
		for (int i = juliaHistory.size() - 1; i >= 0; i--)
		{
			const auto &e = juliaHistory[i];
			QString text = QString("[%1] c = (%2, %3, %4)")
				.arg(e.timestamp)
				.arg(e.cx, 0, 'f', 4)
				.arg(e.cy, 0, 'f', 4)
				.arg(e.cz, 0, 'f', 4);
			ui->listWidget_julia_history->addItem(text);
		}
	}
}

void cDockFractal::slotJuliaSliderCxChanged(int value)
{
	double range = JuliaSliderRange();
	double cx = value / 1000.0 * range;
	if (ui->vect3_julia_c_x) ui->vect3_julia_c_x->setText(QString::number(cx, 'f', 6));
	UpdateJuliaSliderLabels();
}

void cDockFractal::slotJuliaSliderCyChanged(int value)
{
	double range = JuliaSliderRange();
	double cy = value / 1000.0 * range;
	if (ui->vect3_julia_c_y) ui->vect3_julia_c_y->setText(QString::number(cy, 'f', 6));
	UpdateJuliaSliderLabels();
}

void cDockFractal::slotJuliaSliderCzChanged(int value)
{
	double range = JuliaSliderRange();
	double cz = value / 1000.0 * range;
	if (ui->vect3_julia_c_z) ui->vect3_julia_c_z->setText(QString::number(cz, 'f', 6));
	UpdateJuliaSliderLabels();
}

void cDockFractal::slotJuliaRangeChanged(int /*index*/)
{
	UpdateJuliaSliderLabels();
}

void cDockFractal::slotJuliaCopy()
{
	if (!ui->vect3_julia_c_x || !ui->vect3_julia_c_y || !ui->vect3_julia_c_z) return;
	QString text = QString("%1, %2, %3")
		.arg(ui->vect3_julia_c_x->text())
		.arg(ui->vect3_julia_c_y->text())
		.arg(ui->vect3_julia_c_z->text());
	QApplication::clipboard()->setText(text);
}

void cDockFractal::slotJuliaPaste()
{
	QString text = QApplication::clipboard()->text();
	QStringList parts = text.split(',');
	if (parts.size() >= 3)
	{
		if (ui->vect3_julia_c_x) ui->vect3_julia_c_x->setText(parts[0].trimmed());
		if (ui->vect3_julia_c_y) ui->vect3_julia_c_y->setText(parts[1].trimmed());
		if (ui->vect3_julia_c_z) ui->vect3_julia_c_z->setText(parts[2].trimmed());
		double cx = parts[0].trimmed().toDouble();
		double cy = parts[1].trimmed().toDouble();
		double cz = parts[2].trimmed().toDouble();
		AddToJuliaHistory(cx, cy, cz);
	}
}

void cDockFractal::slotJuliaRandom()
{
	double range = JuliaSliderRange();
	double cx = (QRandomGenerator::global()->generateDouble() * 2.0 - 1.0) * range;
	double cy = (QRandomGenerator::global()->generateDouble() * 2.0 - 1.0) * range;
	double cz = (QRandomGenerator::global()->generateDouble() * 2.0 - 1.0) * range;
	if (ui->vect3_julia_c_x) ui->vect3_julia_c_x->setText(QString::number(cx, 'f', 6));
	if (ui->vect3_julia_c_y) ui->vect3_julia_c_y->setText(QString::number(cy, 'f', 6));
	if (ui->vect3_julia_c_z) ui->vect3_julia_c_z->setText(QString::number(cz, 'f', 6));

	// Update sliders
	if (ui->slider_julia_cx) ui->slider_julia_cx->setValue(static_cast<int>(cx / range * 1000.0));
	if (ui->slider_julia_cy) ui->slider_julia_cy->setValue(static_cast<int>(cy / range * 1000.0));
	if (ui->slider_julia_cz) ui->slider_julia_cz->setValue(static_cast<int>(cz / range * 1000.0));

	AddToJuliaHistory(cx, cy, cz);
}

void cDockFractal::slotJuliaZero()
{
	if (ui->vect3_julia_c_x) ui->vect3_julia_c_x->setText("0.0");
	if (ui->vect3_julia_c_y) ui->vect3_julia_c_y->setText("0.0");
	if (ui->vect3_julia_c_z) ui->vect3_julia_c_z->setText("0.0");
	if (ui->slider_julia_cx) ui->slider_julia_cx->setValue(0);
	if (ui->slider_julia_cy) ui->slider_julia_cy->setValue(0);
	if (ui->slider_julia_cz) ui->slider_julia_cz->setValue(0);
}

void cDockFractal::slotJuliaPreset(int presetIndex)
{
	struct sPreset { double cx, cy, cz; };
	static const sPreset presets[] = {
		{0.285, 0.01, 0.0},       // Classic
		{0.0, 1.0, 0.0},          // Dendrite
		{-0.4, 0.6, 0.0},         // Spiral
		{-0.391, -0.587, 0.0},    // Siegel
		{-0.123, 0.745, 0.0},     // Rabbit
		{-0.75, 0.15, 0.2},       // Starfish
		{0.355, 0.355, 0.355},    // Galaxy
		{0.36, 0.1, -0.3},        // Dragon
		{-0.5, 0.0, 0.5}          // Flower
	};

	if (presetIndex < 0 || presetIndex >= 9) return;
	const sPreset &p = presets[presetIndex];

	if (ui->vect3_julia_c_x) ui->vect3_julia_c_x->setText(QString::number(p.cx, 'f', 6));
	if (ui->vect3_julia_c_y) ui->vect3_julia_c_y->setText(QString::number(p.cy, 'f', 6));
	if (ui->vect3_julia_c_z) ui->vect3_julia_c_z->setText(QString::number(p.cz, 'f', 6));

	// Update sliders
	double range = JuliaSliderRange();
	if (range > 0.0)
	{
		if (ui->slider_julia_cx) ui->slider_julia_cx->setValue(static_cast<int>(p.cx / range * 1000.0));
		if (ui->slider_julia_cy) ui->slider_julia_cy->setValue(static_cast<int>(p.cy / range * 1000.0));
		if (ui->slider_julia_cz) ui->slider_julia_cz->setValue(static_cast<int>(p.cz / range * 1000.0));
	}

	// Auto-enable Julia mode
	if (ui->groupCheck_julia_mode && !ui->groupCheck_julia_mode->isChecked())
		ui->groupCheck_julia_mode->setChecked(true);

	AddToJuliaHistory(p.cx, p.cy, p.cz);
}

void cDockFractal::slotJuliaSweepStart()
{
	if (sweepRunning) return;

	sweepAxis = ui->comboBox_julia_sweep_axis ? ui->comboBox_julia_sweep_axis->currentIndex() : 0;
	sweepFrom = ui->spinBox_julia_sweep_from ? ui->spinBox_julia_sweep_from->value() : -2.0;
	sweepTo = ui->spinBox_julia_sweep_to ? ui->spinBox_julia_sweep_to->value() : 2.0;
	sweepTotalSteps = ui->spinBox_julia_sweep_steps ? ui->spinBox_julia_sweep_steps->value() : 50;
	sweepCurrentStep = 0;
	sweepRunning = true;

	// Auto-enable Julia mode
	if (ui->groupCheck_julia_mode && !ui->groupCheck_julia_mode->isChecked())
		ui->groupCheck_julia_mode->setChecked(true);

	if (ui->progressBar_julia_sweep) ui->progressBar_julia_sweep->setValue(0);

	if (sweepTimer) sweepTimer->start();
}

void cDockFractal::slotJuliaSweepStop()
{
	sweepRunning = false;
	if (sweepTimer) sweepTimer->stop();
	if (ui->progressBar_julia_sweep)
		ui->progressBar_julia_sweep->setValue(0);
}

void cDockFractal::slotJuliaSweepStep()
{
	if (!sweepRunning || sweepCurrentStep >= sweepTotalSteps)
	{
		slotJuliaSweepStop();
		return;
	}

	double t = static_cast<double>(sweepCurrentStep) / static_cast<double>(sweepTotalSteps - 1);
	double val = sweepFrom + t * (sweepTo - sweepFrom);

	// Get current c values
	double cx = ui->vect3_julia_c_x ? ui->vect3_julia_c_x->text().toDouble() : 0.0;
	double cy = ui->vect3_julia_c_y ? ui->vect3_julia_c_y->text().toDouble() : 0.0;
	double cz = ui->vect3_julia_c_z ? ui->vect3_julia_c_z->text().toDouble() : 0.0;

	switch (sweepAxis)
	{
		case 0: // c.x
			cx = val;
			break;
		case 1: // c.y
			cy = val;
			break;
		case 2: // c.z
			cz = val;
			break;
		case 3: // All (spiral)
		{
			double angle = t * 4.0 * M_PI;
			double radius = val;
			cx = radius * cos(angle);
			cy = radius * sin(angle);
			cz = val * 0.5;
			break;
		}
	}

	if (ui->vect3_julia_c_x) ui->vect3_julia_c_x->setText(QString::number(cx, 'f', 6));
	if (ui->vect3_julia_c_y) ui->vect3_julia_c_y->setText(QString::number(cy, 'f', 6));
	if (ui->vect3_julia_c_z) ui->vect3_julia_c_z->setText(QString::number(cz, 'f', 6));

	// Update progress
	int progress = static_cast<int>((sweepCurrentStep + 1) * 100.0 / sweepTotalSteps);
	if (ui->progressBar_julia_sweep) ui->progressBar_julia_sweep->setValue(progress);

	sweepCurrentStep++;
}

void cDockFractal::slotJuliaHistoryItemDoubleClicked(QListWidgetItem *item)
{
	if (!item) return;
	int row = ui->listWidget_julia_history->row(item);
	int historyIndex = juliaHistory.size() - 1 - row;
	if (historyIndex < 0 || historyIndex >= juliaHistory.size()) return;

	const auto &entry = juliaHistory[historyIndex];
	if (ui->vect3_julia_c_x) ui->vect3_julia_c_x->setText(QString::number(entry.cx, 'f', 6));
	if (ui->vect3_julia_c_y) ui->vect3_julia_c_y->setText(QString::number(entry.cy, 'f', 6));
	if (ui->vect3_julia_c_z) ui->vect3_julia_c_z->setText(QString::number(entry.cz, 'f', 6));

	double range = JuliaSliderRange();
	if (range > 0.0)
	{
		if (ui->slider_julia_cx)
			ui->slider_julia_cx->setValue(static_cast<int>(entry.cx / range * 1000.0));
		if (ui->slider_julia_cy)
			ui->slider_julia_cy->setValue(static_cast<int>(entry.cy / range * 1000.0));
		if (ui->slider_julia_cz)
			ui->slider_julia_cz->setValue(static_cast<int>(entry.cz / range * 1000.0));
	}
}

void cDockFractal::slotJuliaHistorySave()
{
	if (!ui->listWidget_julia_history) return;
	QListWidgetItem *item = ui->listWidget_julia_history->currentItem();
	if (!item) return;

	int row = ui->listWidget_julia_history->row(item);
	int historyIndex = juliaHistory.size() - 1 - row;
	if (historyIndex < 0 || historyIndex >= juliaHistory.size()) return;

	const auto &entry = juliaHistory[historyIndex];
	QString msg = QString("Julia c = (%1, %2, %3) saved to clipboard as bookmark format")
		.arg(entry.cx, 0, 'f', 4).arg(entry.cy, 0, 'f', 4).arg(entry.cz, 0, 'f', 4);
	QApplication::clipboard()->setText(
		QString("%1, %2, %3").arg(entry.cx, 0, 'f', 6).arg(entry.cy, 0, 'f', 6).arg(entry.cz, 0, 'f', 6));
}

void cDockFractal::slotJuliaHistoryClear()
{
	juliaHistory.clear();
	if (ui->listWidget_julia_history) ui->listWidget_julia_history->clear();
}

// ========================================================================
// 3x3lion Julia Heatmap — maps interest scores across Julia c-space
// ========================================================================

void cDockFractal::SetupJuliaHeatmap()
{
	if (ui->comboBox_heatmap_resolution)
		ui->comboBox_heatmap_resolution->setCurrentIndex(1); // 32x32 default

	ConnectJuliaHeatmapSignals();
}

void cDockFractal::ConnectJuliaHeatmapSignals()
{
	if (ui->pushButton_heatmap_scan)
		connect(ui->pushButton_heatmap_scan, &QPushButton::clicked, this,
			&cDockFractal::slotHeatmapScan);

	if (ui->pushButton_heatmap_stop)
		connect(ui->pushButton_heatmap_stop, &QPushButton::clicked, this,
			&cDockFractal::slotHeatmapStop);

	if (ui->pushButton_heatmap_clear)
		connect(ui->pushButton_heatmap_clear, &QPushButton::clicked, this,
			&cDockFractal::slotHeatmapClear);

	if (ui->comboBox_heatmap_axis_h)
		connect(ui->comboBox_heatmap_axis_h, QOverload<int>::of(&QComboBox::currentIndexChanged),
			this, &cDockFractal::slotHeatmapAxisHChanged);

	if (ui->comboBox_heatmap_axis_v)
		connect(ui->comboBox_heatmap_axis_v, QOverload<int>::of(&QComboBox::currentIndexChanged),
			this, &cDockFractal::slotHeatmapAxisVChanged);

	if (ui->comboBox_heatmap_resolution)
		connect(ui->comboBox_heatmap_resolution,
			QOverload<int>::of(&QComboBox::currentIndexChanged), this,
			&cDockFractal::slotHeatmapResolutionChanged);

	if (ui->comboBox_heatmap_scheme)
		connect(ui->comboBox_heatmap_scheme, QOverload<int>::of(&QComboBox::currentIndexChanged),
			this, &cDockFractal::slotHeatmapSchemeChanged);

	if (ui->widget_julia_heatmap)
	{
		connect(ui->widget_julia_heatmap, &cJuliaHeatmapWidget::signalCellClicked, this,
			&cDockFractal::slotHeatmapCellClicked);
		connect(ui->widget_julia_heatmap, &cJuliaHeatmapWidget::signalScanRequested, this,
			&cDockFractal::slotHeatmapScanRequested);
		connect(ui->widget_julia_heatmap, &cJuliaHeatmapWidget::signalScanProgress, this,
			&cDockFractal::slotHeatmapScanProgress);
		connect(ui->widget_julia_heatmap, &cJuliaHeatmapWidget::signalScanComplete, this,
			&cDockFractal::slotHeatmapScanComplete);
		connect(ui->widget_julia_heatmap, &cJuliaHeatmapWidget::signalHoverInfo, this,
			&cDockFractal::slotHeatmapHoverInfo);
	}
}

void cDockFractal::UpdateHeatmapMarker()
{
	if (!ui->widget_julia_heatmap) return;

	double cx = ui->vect3_julia_c_x ? ui->vect3_julia_c_x->text().toDouble() : 0.0;
	double cy = ui->vect3_julia_c_y ? ui->vect3_julia_c_y->text().toDouble() : 0.0;
	double cz = ui->vect3_julia_c_z ? ui->vect3_julia_c_z->text().toDouble() : 0.0;

	int axisH = ui->widget_julia_heatmap->GetAxisH();
	int axisV = ui->widget_julia_heatmap->GetAxisV();

	double cArr[3] = {cx, cy, cz};
	ui->widget_julia_heatmap->SetMarker(cArr[axisH], cArr[axisV]);
}

double cDockFractal::ComputeQuickScore(double cx, double cy, double cz)
{
	// Quick heuristic score based on Julia c-value properties.
	// Uses the Mandelbrot-set membership test as a proxy for interesting Julia sets:
	// c-values near the boundary of the Mandelbrot set produce the most interesting Julia sets.
	// For 3D, we extend this to test orbit divergence speed.

	double zx = 0.0, zy = 0.0, zz = 0.0;
	int maxIter = 64;
	int escapeIter = maxIter;

	for (int i = 0; i < maxIter; i++)
	{
		// Simplified 3D orbit: z = z^2 + c (using a Mandelbulb-like power-2 approximation)
		double r = std::sqrt(zx * zx + zy * zy + zz * zz);
		if (r > 4.0)
		{
			escapeIter = i;
			break;
		}

		double theta = std::atan2(std::sqrt(zx * zx + zy * zy), zz);
		double phi = std::atan2(zy, zx);
		double r2 = r * r;

		zx = r2 * std::sin(2.0 * theta) * std::cos(2.0 * phi) + cx;
		zy = r2 * std::sin(2.0 * theta) * std::sin(2.0 * phi) + cy;
		zz = r2 * std::cos(2.0 * theta) + cz;
	}

	if (escapeIter == maxIter)
	{
		// Inside the set — moderately interesting (connected Julia set)
		return 0.4;
	}

	// Boundary region is most interesting — score based on how close to boundary
	// Points that escape quickly (low iter) are boring (dust Julia sets)
	// Points that escape slowly (high iter) are near the boundary (most interesting)
	double normalizedIter = static_cast<double>(escapeIter) / maxIter;

	// Smooth scoring: peak interest at boundary
	double score = 4.0 * normalizedIter * (1.0 - normalizedIter);

	// Boost near-boundary points
	if (normalizedIter > 0.3 && normalizedIter < 0.8) score *= 1.5;

	return qBound(0.0, score, 1.0);
}

void cDockFractal::slotHeatmapScan()
{
	if (!ui->widget_julia_heatmap) return;

	// Set resolution based on combo
	static const int resolutions[] = {16, 32, 48, 64};
	int resIdx = ui->comboBox_heatmap_resolution ? ui->comboBox_heatmap_resolution->currentIndex() : 1;
	if (resIdx < 0 || resIdx > 3) resIdx = 1;
	ui->widget_julia_heatmap->SetResolution(resolutions[resIdx]);

	// Set range from Julia Explorer range combo
	double range = JuliaSliderRange();
	ui->widget_julia_heatmap->SetRange(range);

	// Set the fixed axis value (third axis not shown in heatmap)
	int axisH = ui->comboBox_heatmap_axis_h ? ui->comboBox_heatmap_axis_h->currentIndex() : 0;
	int axisV = ui->comboBox_heatmap_axis_v ? ui->comboBox_heatmap_axis_v->currentIndex() : 1;
	ui->widget_julia_heatmap->SetAxes(axisH, axisV);

	// The fixed axis is whichever is not H or V
	int fixedAxis = 3 - axisH - axisV;
	if (fixedAxis < 0 || fixedAxis > 2) fixedAxis = 2;
	double cArr[3] = {
		ui->vect3_julia_c_x ? ui->vect3_julia_c_x->text().toDouble() : 0.0,
		ui->vect3_julia_c_y ? ui->vect3_julia_c_y->text().toDouble() : 0.0,
		ui->vect3_julia_c_z ? ui->vect3_julia_c_z->text().toDouble() : 0.0};
	ui->widget_julia_heatmap->SetFixedAxisValue(cArr[fixedAxis]);

	// Start the scan
	ui->widget_julia_heatmap->StartScan();
}

void cDockFractal::slotHeatmapStop()
{
	if (ui->widget_julia_heatmap) ui->widget_julia_heatmap->StopScan();
}

void cDockFractal::slotHeatmapClear()
{
	if (ui->widget_julia_heatmap) ui->widget_julia_heatmap->ClearScores();
	if (ui->progressBar_heatmap) ui->progressBar_heatmap->setValue(0);
	if (ui->label_heatmap_info)
		ui->label_heatmap_info->setText("Hover over heatmap for details");
}

void cDockFractal::slotHeatmapAxisHChanged(int index)
{
	if (!ui->widget_julia_heatmap) return;

	int axisV = ui->comboBox_heatmap_axis_v ? ui->comboBox_heatmap_axis_v->currentIndex() : 1;
	if (index == axisV)
	{
		// Swap to avoid same axis on both
		int newV = (index + 1) % 3;
		if (ui->comboBox_heatmap_axis_v)
			ui->comboBox_heatmap_axis_v->setCurrentIndex(newV);
		axisV = newV;
	}
	ui->widget_julia_heatmap->SetAxes(index, axisV);
	ui->widget_julia_heatmap->ClearScores();
}

void cDockFractal::slotHeatmapAxisVChanged(int index)
{
	if (!ui->widget_julia_heatmap) return;

	int axisH = ui->comboBox_heatmap_axis_h ? ui->comboBox_heatmap_axis_h->currentIndex() : 0;
	if (index == axisH)
	{
		int newH = (index + 1) % 3;
		if (ui->comboBox_heatmap_axis_h)
			ui->comboBox_heatmap_axis_h->setCurrentIndex(newH);
		axisH = newH;
	}
	ui->widget_julia_heatmap->SetAxes(axisH, index);
	ui->widget_julia_heatmap->ClearScores();
}

void cDockFractal::slotHeatmapResolutionChanged(int index)
{
	if (!ui->widget_julia_heatmap) return;
	static const int resolutions[] = {16, 32, 48, 64};
	if (index >= 0 && index <= 3)
		ui->widget_julia_heatmap->SetResolution(resolutions[index]);
}

void cDockFractal::slotHeatmapSchemeChanged(int index)
{
	if (!ui->widget_julia_heatmap) return;
	ui->widget_julia_heatmap->SetColorScheme(
		static_cast<cJuliaHeatmapWidget::eColorScheme>(index));
}

void cDockFractal::slotHeatmapCellClicked(double cH, double cV)
{
	// When user clicks a cell, jump to that Julia c-value
	int axisH = ui->widget_julia_heatmap ? ui->widget_julia_heatmap->GetAxisH() : 0;
	int axisV = ui->widget_julia_heatmap ? ui->widget_julia_heatmap->GetAxisV() : 1;

	double cx = ui->vect3_julia_c_x ? ui->vect3_julia_c_x->text().toDouble() : 0.0;
	double cy = ui->vect3_julia_c_y ? ui->vect3_julia_c_y->text().toDouble() : 0.0;
	double cz = ui->vect3_julia_c_z ? ui->vect3_julia_c_z->text().toDouble() : 0.0;

	double cArr[3] = {cx, cy, cz};
	cArr[axisH] = cH;
	cArr[axisV] = cV;

	if (ui->vect3_julia_c_x) ui->vect3_julia_c_x->setText(QString::number(cArr[0], 'f', 6));
	if (ui->vect3_julia_c_y) ui->vect3_julia_c_y->setText(QString::number(cArr[1], 'f', 6));
	if (ui->vect3_julia_c_z) ui->vect3_julia_c_z->setText(QString::number(cArr[2], 'f', 6));

	UpdateJuliaSliderLabels();
	AddToJuliaHistory(cArr[0], cArr[1], cArr[2]);
	UpdateHeatmapMarker();
}

void cDockFractal::slotHeatmapScanRequested(int gx, int gy, double cH, double cV)
{
	if (!ui->widget_julia_heatmap) return;

	int axisH = ui->widget_julia_heatmap->GetAxisH();
	int axisV = ui->widget_julia_heatmap->GetAxisV();
	double fixedVal = ui->widget_julia_heatmap->GetFixedAxisValue();

	double cArr[3] = {0.0, 0.0, 0.0};
	cArr[axisH] = cH;
	cArr[axisV] = cV;

	// Set the fixed axis
	int fixedAxis = 3 - axisH - axisV;
	if (fixedAxis >= 0 && fixedAxis <= 2) cArr[fixedAxis] = fixedVal;

	double score = ComputeQuickScore(cArr[0], cArr[1], cArr[2]);
	ui->widget_julia_heatmap->SetScore(gx, gy, score);
}

void cDockFractal::slotHeatmapScanProgress(int percent)
{
	if (ui->progressBar_heatmap) ui->progressBar_heatmap->setValue(percent);
}

void cDockFractal::slotHeatmapScanComplete()
{
	if (ui->progressBar_heatmap) ui->progressBar_heatmap->setValue(100);
	if (ui->label_heatmap_info)
		ui->label_heatmap_info->setText("Scan complete — click hotspots to explore");
	UpdateHeatmapMarker();
}

void cDockFractal::slotHeatmapHoverInfo(double cH, double cV, double score)
{
	if (!ui->label_heatmap_info) return;
	int axisH = ui->widget_julia_heatmap ? ui->widget_julia_heatmap->GetAxisH() : 0;
	int axisV = ui->widget_julia_heatmap ? ui->widget_julia_heatmap->GetAxisV() : 1;

	static const char *names[] = {"c.x", "c.y", "c.z"};
	ui->label_heatmap_info->setText(
		QString("%1=%2  %3=%4  score=%5")
			.arg(names[axisH])
			.arg(QString::number(cH, 'f', 3))
			.arg(names[axisV])
			.arg(QString::number(cV, 'f', 3))
			.arg(QString::number(score, 'f', 4)));
}
