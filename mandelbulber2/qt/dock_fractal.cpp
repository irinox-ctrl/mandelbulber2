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

#include "fractal_formulas_tab.h"
#include "fractal_common_tab.h"
#include "fractal_hybrid_tab.h"
#include "fractal_primitives_tab.h"
#include "fractal_description_tab.h"

#define FORMULAS_UI (static_cast<cFractalFormulasTab*>(ui->tabWidget_fractal_formulas)->formulasUi())
#define COMMON_UI (static_cast<cFractalCommonTab*>(ui->tabWidget_fractal_common)->commonUi())
#define HYBRID_UI (static_cast<cFractalHybridTab*>(ui->tabWidget_fractal_hybrid)->hybridUi())
#define PRIM_UI (static_cast<cFractalPrimitivesTab*>(ui->tab_primitives)->primitivesUi())
#define DESC_UI (static_cast<cFractalDescriptionTab*>(ui->tab_description)->descriptionUi())
#include "dock_mutation.h"
#include "dock_rendering_engine.h"
#include "my_tab_bar.h"

#include "src/ao_modes.h"
#include "src/automated_widgets.hpp"
#include "src/error_message.hpp"
#include "src/fractal_enums.h"
#include "src/global_data.hpp"
#include "src/initparameters.hpp"
#include "src/interface.hpp"
#include "qt_utils.h"
#include "src/render_window.hpp"
#include "src/rendered_image_widget.hpp"
#include "src/write_log.hpp"

#include <QClipboard>
#include <QLineEdit>
#include <QProgressBar>
#include <QRandomGenerator>
#include <QSignalBlocker>
#include <QDateTime>
#include <QSlider>
#include <QtConcurrent/QtConcurrent>

#include "formula/definition/all_fractal_list.hpp"
#include "julia_heatmap_widget.h"
#include "navigator_window.h"
#include "src/deep_zoom_integration.h"
#include "src/calculate_distance.hpp"
#include "src/fractal_container.hpp"
#include "src/fractparams.hpp"
#include "src/nine_fractals.hpp"
#include "src/render_data.hpp"

cDockFractal::cDockFractal(QWidget *parent)
		: QWidget(parent), cMyWidgetWithParams(), ui(new Ui::cDockFractal)
{
	ui->setupUi(this);

	fractalTabs.resize(NUMBER_OF_FRACTALS);
	for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
	{
		fractalTabs[i] =
			FORMULAS_UI->tabWidget_fractals->findChild<cTabFractal *>(QString("widgetTabFractal_%1").arg(i + 1));
	}

	automatedWidgets = new cAutomatedWidgets(this);
	automatedWidgets->ConnectSignalsForSlidersInWindow(this);

	HYBRID_UI->label_repeat_from->setEnabled(false);
	HYBRID_UI->spinboxInt_repeat_from->setEnabled(false);
	FORMULAS_UI->label_fractals_remark_julia->setVisible(false);

	COMMON_UI->previewwidget_julia->SetSize(256, 256, 2);

	FORMULAS_UI->tabWidget_fractals->setUsesScrollButtons(true);
	FORMULAS_UI->tabWidget_fractals->setDocumentMode(true);
	FORMULAS_UI->tabWidget_fractals->setElideMode(Qt::ElideNone);

	ConnectSignals();
	SetupJuliaExplorer();
	SetupJuliaHeatmap();
	SetupDroneExplorer();

	// Beauty Finder — connect buttons directly
	if (COMMON_UI->pushButton_beauty_find)
		connect(COMMON_UI->pushButton_beauty_find, &QPushButton::clicked, this, &cDockFractal::slotBeautyFindBest);
	if (COMMON_UI->pushButton_beauty_next)
		connect(COMMON_UI->pushButton_beauty_next, &QPushButton::clicked, this, &cDockFractal::slotBeautyApplyNext);

	// Auto beauty debounce timer (500ms after last Julia change)
	beautyAutoTimer = new QTimer(this);
	beautyAutoTimer->setSingleShot(true);
	beautyAutoTimer->setInterval(500);
	connect(beautyAutoTimer, &QTimer::timeout, this, &cDockFractal::slotBeautyFindBest);

	// Async beauty scan watcher
	beautyScanWatcher = new QFutureWatcher<QVector<sBeautyResult>>(this);
	connect(beautyScanWatcher, &QFutureWatcher<QVector<sBeautyResult>>::finished,
		this, &cDockFractal::slotBeautyScanFinished);

	heatmapScanCancelled = std::make_shared<std::atomic<bool>>(false);
	heatmapScanProgress = std::make_shared<std::atomic<int>>(0);
	heatmapScanWatcher = new QFutureWatcher<QVector<double>>(this);
	connect(heatmapScanWatcher, &QFutureWatcher<QVector<double>>::finished,
		this, &cDockFractal::slotHeatmapScanFinished);
	heatmapProgressTimer = new QTimer(this);
	heatmapProgressTimer->setInterval(100);
	connect(heatmapProgressTimer, &QTimer::timeout, this, [this]() {
		if (!heatmapScanRunning || !heatmapScanProgress) return;
		slotHeatmapScanProgress(heatmapScanProgress->load());
	});
}

cDockFractal::~cDockFractal()
{
	if (sweepTimer)
	{
		sweepTimer->stop();
		delete sweepTimer;
	}
	if (beautyScanWatcher)
	{
		if (beautyScanWatcher->isRunning())
			beautyScanWatcher->waitForFinished();
		delete beautyScanWatcher;
	}
	if (heatmapProgressTimer)
		heatmapProgressTimer->stop();
	if (heatmapScanWatcher)
	{
		if (heatmapScanCancelled)
			heatmapScanCancelled->store(true);
		if (heatmapScanWatcher->isRunning())
			heatmapScanWatcher->waitForFinished();
		delete heatmapScanWatcher;
	}
	delete ui;
}

bool cDockFractal::AreHybridFractalsEnabled() const
{
	return HYBRID_UI->checkBox_hybrid_fractal_enable->isChecked();
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
	SynchronizeInterfaceWindow(FORMULAS_UI->tabWidget_fractals->tabBar(), par, mode);

	for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
	{
		WriteLog("cInterface::SynchronizeInterface: fractalWidgets[i]", 3);
		fractalTabs[i]->SynchronizeInterface(par, mode);
	}

	if (mode == qInterface::write)
	{
		for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
			fractalTabs[i]->EnsureFormulaWidgetMatchesParams(false);
	}

	for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
	{
		WriteLog("cInterface::SynchronizeInterface: fractalWidgets[i] fractal params", 3);
		fractalTabs[i]->SynchronizeFractal(parFractal->at(i), mode);
	}
}

void cDockFractal::slotSynchronizeInterfaceJulia(std::shared_ptr<cParameterContainer> par) const
{
	SynchronizeInterfaceWindow(COMMON_UI->groupCheck_julia_mode, par, qInterface::write);
}

void cDockFractal::slotSynchronizeInterfacePrimitives(
	std::shared_ptr<cParameterContainer> par) const
{
	SynchronizeInterfaceWindow(PRIM_UI->scrollArea_primitives, par, qInterface::write);
}

void cDockFractal::slotEnableJuliaMode() const
{
	COMMON_UI->groupCheck_julia_mode->setChecked(true);
}

QWidget *cDockFractal::GetContainerWithPrimitives() const
{
	return PRIM_UI->scrollAreaWidgetContents_primitives;
}

QVBoxLayout *cDockFractal::GetLayoutWithPrimitives() const
{
	return PRIM_UI->verticalLayout_primitives;
}

bool cDockFractal::AreBooleanFractalsEnabled() const
{
	return HYBRID_UI->groupCheck_boolean_operators->isChecked();
}

void cDockFractal::SetTabText(int tabIndex, QString text) const
{
	FORMULAS_UI->tabWidget_fractals->setTabText(tabIndex, text);
}

void cDockFractal::ConnectSignals()
{
	connect(COMMON_UI->vect3_julia_c_x, &QLineEdit::textChanged, this, &cDockFractal::slotChangedJuliaPoint);
	connect(COMMON_UI->vect3_julia_c_y, &QLineEdit::textChanged, this, &cDockFractal::slotChangedJuliaPoint);
	connect(COMMON_UI->vect3_julia_c_z, &QLineEdit::textChanged, this, &cDockFractal::slotChangedJuliaPoint);
	connect(COMMON_UI->logedit_julia_preview_distance, &QLineEdit::textChanged, this,
		&cDockFractal::slotChangedJuliaPoint);

	connect(COMMON_UI->pushButton_get_julia_constant, &QPushButton::clicked, this,
		&cDockFractal::slotPressedButtonGetJuliaConstant);

	connect(COMMON_UI->groupCheck_julia_mode, &QGroupBox::toggled, this,
		&cDockFractal::slotGroupCheckJuliaModeToggled);
	connect(HYBRID_UI->checkBox_hybrid_fractal_enable, &QCheckBox::stateChanged, this,
		&cDockFractal::slotChangedCheckBoxHybridFractal);
	connect(HYBRID_UI->groupCheck_boolean_operators, &QGroupBox::toggled, this,
		&cDockFractal::slotChangedCheckBoxBooleanOperators);
	connect(COMMON_UI->groupCheck_julia_mode, &QGroupBox::toggled, this,
		&cDockFractal::slotChangedCheckBoxJuliaMode);
	auto *fractalTabBar = qobject_cast<MyTabBar *>(FORMULAS_UI->tabWidget_fractals->tabBar());
	if (fractalTabBar)
		connect(fractalTabBar, &MyTabBar::toggledEnable, this, &cDockFractal::slotToggledFractalEnable);
	connect(FORMULAS_UI->tabWidget_fractals->tabBar(), &QTabBar::currentChanged, this,
		&cDockFractal::slotChangedFractalTab);
	connect(FORMULAS_UI->pushButton_local_navi, &QPushButton::clicked, this, &cDockFractal::slotPressedButtonNavi);
	connect(FORMULAS_UI->tabWidget_fractals, &MyTabWidget::swapTabs, this, &cDockFractal::slotFractalSwap);

	connect(PRIM_UI->widgetPrimitivesManager, &cPrimitivesManager::signalUpdatePrimitivesCombos, this,
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

	cDockMutation *dockMutation = nullptr;
	if (gMainInterface && gMainInterface->mainWindow)
	{
		dockMutation = gMainInterface->mainWindow->GetWidgetDockMutation();
	}

	for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
	{
		if (i == 0)
			FORMULAS_UI->tabWidget_fractals->setTabText(i, QString("#1: Mandelbulb"));
		else
		{
			FORMULAS_UI->tabWidget_fractals->setTabText(i, QString("#%1: None").arg(i + 1));
			FORMULAS_UI->tabWidget_fractals
				->findChild<QScrollArea *>("scrollArea_fractal_" + QString::number(i + 1))
				->setEnabled(false);
		}
		fractalTabs[i]->AssignParameterContainers(params, fractalParams);
		fractalTabs[i]->Init(i == 0, i);
		fractalTabs[i]->AssignParentDockFractal(this);

		// Connect fractal formula change to mutation dock
		if (dockMutation)
		{
			// Set initial tab title with formula name
			int formulaIndex = fractalTabs[i]->GetCurrentFractalIndexOnList();
			if (formulaIndex >= 0 && formulaIndex < newFractalList.size())
			{
				dockMutation->UpdateTabTitle(i, QString("#%1: %2")
					.arg(i + 1).arg(newFractalList[formulaIndex]->getNameInComboBox()));
			}

			connect(fractalTabs[i], &cTabFractal::signalFormulaChanged,
				[=](int formulaIndex) {
					dockMutation->UpdateMutationFieldVisibility(i, formulaIndex);
					dockMutation->UpdateMutationGrayOut(i);
					if (formulaIndex >= 0 && formulaIndex < newFractalList.size())
					{
						dockMutation->UpdateTabTitle(i, QString("#%1: %2")
							.arg(i + 1).arg(newFractalList[formulaIndex]->getNameInComboBox()));
					}
				});
		}
	}

	static_cast<MyTabBar *>(FORMULAS_UI->tabWidget_fractals->tabBar())->setupMoveButtons();

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
	CHECK_MAIN_INTERFACE();
	if (state)
	{
		QSignalBlocker blocker(HYBRID_UI->checkBox_hybrid_fractal_enable);
		HYBRID_UI->checkBox_hybrid_fractal_enable->setChecked(false);
	}

	for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
	{
		if (i > 0)
		{
			fractalTabs[i]->FrameIterationFormulaSetEnabled(state);
			FORMULAS_UI->tabWidget_fractals
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
	COMMON_UI->groupBox_material_fractal->setVisible(!state);
}

void cDockFractal::slotChangedCheckBoxHybridFractal(int state) const
{
	if (state)
	{
		QSignalBlocker blocker(HYBRID_UI->groupCheck_boolean_operators);
		HYBRID_UI->groupCheck_boolean_operators->setChecked(false);
	}

	for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
	{
		fractalTabs[i]->FrameIterationFormulaSetWidgetsVisibility(state);
		fractalTabs[i]->FormulaTransformSetVisible(state);

		const fractal::enumCPixelAddition cPixelAddition =
			newFractalList[fractalTabs[i]->GetCurrentFractalIndexOnList()]->getCpixelAddition();

		if (cPixelAddition == fractal::cpixelAlreadyHas)
			fractalTabs[i]->CConstantAdditionSetVisible(false);
		else
			fractalTabs[i]->CConstantAdditionSetVisible(state);

		fractalTabs[i]->MaterialSetVisible(state);
		fractalTabs[i]->CalculationParametersSetVisible(state);

		if (i > 0)
		{
			fractalTabs[i]->FrameIterationFormulaSetEnabled(state);
			FORMULAS_UI->tabWidget_fractals
				->findChild<QScrollArea *>("scrollArea_fractal_" + QString::number(i + 1))
				->setEnabled(state);
		}
	}

	FORMULAS_UI->label_fractals_remark_hybrid->setVisible(!state);
	HYBRID_UI->label_repeat_from->setEnabled(state);
	HYBRID_UI->spinboxInt_repeat_from->setEnabled(state);
}

void cDockFractal::slotChangedCheckBoxJuliaMode(bool state) const
{
	FORMULAS_UI->label_fractals_remark_julia->setVisible(state);
}

void cDockFractal::slotToggledFractalEnable(int fractalIndex, bool enabled) const
{
	FORMULAS_UI->tabWidget_fractals->widget(fractalIndex - 1)->setEnabled(enabled);
}

void cDockFractal::slotGroupCheckJuliaModeToggled(bool state)
{
	CHECK_MAIN_INTERFACE();
	if (state)
	{
		gMainInterface->DisablePeriodicRefresh();
	}
}

void cDockFractal::slotChangedJuliaPoint()
{
	// Auto beauty triggers ONLY on slider release (slotJuliaSliderReleased)
	// NOT here — this fires on every keystroke/spinbox change and blocks UI

	if (COMMON_UI->groupBox_julia_preview && COMMON_UI->groupCheck_julia_mode->isChecked()
			&& params->Get<bool>("julia_preview") && gInterfaceReadyForSynchronization)
	{
		std::shared_ptr<cParameterContainer> params(new cParameterContainer());
		InitParams(params);
		InitMaterialParams(1, params);
		SynchronizeInterfaceWindow(COMMON_UI->groupCheck_julia_mode, params, qInterface::read);
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

		COMMON_UI->previewwidget_julia->AssignParameters(params, fractalParams);
		COMMON_UI->previewwidget_julia->update();
	}
}

void cDockFractal::slotPressedButtonGetJuliaConstant()
{
	CHECK_MAIN_INTERFACE();
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
		if (!HYBRID_UI->checkBox_hybrid_fractal_enable->isChecked()
				&& !HYBRID_UI->groupCheck_boolean_operators->isChecked())
		{
			auto *message = new QMessageBox(this);
			message->setAttribute(Qt::WA_DeleteOnClose);

			QPushButton *buttonHybrid =
				message->addButton(tr("Enable hybrid fractals"), QMessageBox::AcceptRole);
			QPushButton *buttonBoolean =
				message->addButton(tr("Enable boolean mode"), QMessageBox::AcceptRole);
			const QPushButton *buttonCancel = message->addButton(QMessageBox::Cancel);

			message->setText(tr(
				"You have selected next fractal formula.\nDo you want to enable hybrid fractals or boolean "
				"mode?"));
			message->setWindowTitle(tr("More fractals..."));
			message->setIcon(QMessageBox::Question);
			connect(message, &QMessageBox::finished, this,
				[this, message, buttonHybrid, buttonBoolean, buttonCancel]() {
					if (message->clickedButton() == buttonCancel) return;
					if (message->clickedButton() == buttonHybrid)
						HYBRID_UI->checkBox_hybrid_fractal_enable->setChecked(true);
					else if (message->clickedButton() == buttonBoolean)
						HYBRID_UI->groupCheck_boolean_operators->setChecked(true);
				});
			message->open();
		}
	}
}

void cDockFractal::AssignParameterContainers(
	std::shared_ptr<cParameterContainer> _params, std::shared_ptr<cFractalContainer> _fractalParams)
{
	cMyWidgetWithParams::AssignParameterContainers(_params, _fractalParams);
	PRIM_UI->widgetPrimitivesManager->AssignParameterContainers(_params, _fractalParams);
	PRIM_UI->widgetPrimitivesManager->Init();
}

void cDockFractal::AssignSpecialWidgets(
	RenderedImage *_renderedImage, QComboBox *_mouseFunctionCombo)
{
	cMyWidgetWithParams::AssignSpecialWidgets(_renderedImage, _mouseFunctionCombo);
	PRIM_UI->widgetPrimitivesManager->AssignSpecialWidgets(_renderedImage, _mouseFunctionCombo);
}

void cDockFractal::RegeneratePrimitives()
{
	PRIM_UI->widgetPrimitivesManager->Regenerate();
}

void cDockFractal::slotPressedButtonNavi()
{
	CHECK_MAIN_INTERFACE();
	CHECK_PARAMS();
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
	if (COMMON_UI->pushButton_get_julia_constant)
	{
		COMMON_UI->pushButton_get_julia_constant->setVisible(false);
		COMMON_UI->pushButton_get_julia_constant->setEnabled(false);
	}
	if (COMMON_UI->groupBox_julia_preview)
	{
		COMMON_UI->groupBox_julia_preview->setVisible(false);
		COMMON_UI->groupBox_julia_preview->setEnabled(false);
	}
}

// ===== 3x3lion Julia Explorer =====

void cDockFractal::SetupJuliaExplorer()
{
	// Default range: ±2.0 (index 2)
	if (COMMON_UI->comboBox_julia_range) COMMON_UI->comboBox_julia_range->setCurrentIndex(2);

	sweepTimer = new QTimer(this);
	sweepTimer->setInterval(100);

	ConnectJuliaExplorerSignals();

	if (COMMON_UI->pushButton_beauty_find)
		COMMON_UI->pushButton_beauty_find->setToolTip(
			tr("Scan the Julia parameter space for high-detail regions"));
	if (COMMON_UI->pushButton_julia_sweep_start)
		COMMON_UI->pushButton_julia_sweep_start->setToolTip(
			tr("Animate Julia c along the selected axis"));
	if (COMMON_UI->widget_julia_heatmap)
		COMMON_UI->widget_julia_heatmap->setToolTip(
			tr("Click cells to jump to Julia c values; run scan to fill the heatmap"));
}

void cDockFractal::ConnectJuliaExplorerSignals()
{
	// Sliders
	if (COMMON_UI->jslider_julia_cx)
	{
		connect(COMMON_UI->jslider_julia_cx, &QSlider::valueChanged, this, &cDockFractal::slotJuliaSliderCxChanged);
		connect(COMMON_UI->jslider_julia_cx, &QSlider::sliderReleased, this, &cDockFractal::slotJuliaSliderReleased);
	}
	if (COMMON_UI->jslider_julia_cy)
	{
		connect(COMMON_UI->jslider_julia_cy, &QSlider::valueChanged, this, &cDockFractal::slotJuliaSliderCyChanged);
		connect(COMMON_UI->jslider_julia_cy, &QSlider::sliderReleased, this, &cDockFractal::slotJuliaSliderReleased);
	}
	if (COMMON_UI->jslider_julia_cz)
	{
		connect(COMMON_UI->jslider_julia_cz, &QSlider::valueChanged, this, &cDockFractal::slotJuliaSliderCzChanged);
		connect(COMMON_UI->jslider_julia_cz, &QSlider::sliderReleased, this, &cDockFractal::slotJuliaSliderReleased);
	}

	if (COMMON_UI->comboBox_julia_range)
		connect(COMMON_UI->comboBox_julia_range, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
			&cDockFractal::slotJuliaRangeChanged);

	if (COMMON_UI->pushButton_julia_copy)
		connect(COMMON_UI->pushButton_julia_copy, &QPushButton::clicked, this, &cDockFractal::slotJuliaCopy);
	if (COMMON_UI->pushButton_julia_paste)
		connect(COMMON_UI->pushButton_julia_paste, &QPushButton::clicked, this, &cDockFractal::slotJuliaPaste);
	if (COMMON_UI->pushButton_julia_random)
		connect(COMMON_UI->pushButton_julia_random, &QPushButton::clicked, this, &cDockFractal::slotJuliaRandom);
	if (COMMON_UI->pushButton_julia_zero)
		connect(COMMON_UI->pushButton_julia_zero, &QPushButton::clicked, this, &cDockFractal::slotJuliaZero);

	// Presets (use lambda to pass index)
	QPushButton *presetButtons[] = {
		COMMON_UI->pushButton_julia_preset_1, COMMON_UI->pushButton_julia_preset_2, COMMON_UI->pushButton_julia_preset_3,
		COMMON_UI->pushButton_julia_preset_4, COMMON_UI->pushButton_julia_preset_5, COMMON_UI->pushButton_julia_preset_6,
		COMMON_UI->pushButton_julia_preset_7, COMMON_UI->pushButton_julia_preset_8, COMMON_UI->pushButton_julia_preset_9
	};
	for (int i = 0; i < 9; i++)
	{
		if (presetButtons[i])
		{
			connect(presetButtons[i], &QPushButton::clicked, this, [this, i]() { slotJuliaPreset(i); });
		}
	}

	// Sweep
	if (COMMON_UI->pushButton_julia_sweep_start)
		connect(COMMON_UI->pushButton_julia_sweep_start, &QPushButton::clicked, this,
			&cDockFractal::slotJuliaSweepStart);
	if (COMMON_UI->pushButton_julia_sweep_stop)
		connect(COMMON_UI->pushButton_julia_sweep_stop, &QPushButton::clicked, this,
			&cDockFractal::slotJuliaSweepStop);
	if (sweepTimer)
		connect(sweepTimer, &QTimer::timeout, this, &cDockFractal::slotJuliaSweepStep);

	if (COMMON_UI->listWidget_julia_history)
		connect(COMMON_UI->listWidget_julia_history, &QListWidget::itemDoubleClicked, this,
			&cDockFractal::slotJuliaHistoryItemDoubleClicked);
	if (COMMON_UI->pushButton_julia_history_save)
		connect(COMMON_UI->pushButton_julia_history_save, &QPushButton::clicked, this,
			&cDockFractal::slotJuliaHistorySave);
	if (COMMON_UI->pushButton_julia_history_clear)
		connect(COMMON_UI->pushButton_julia_history_clear, &QPushButton::clicked, this,
			&cDockFractal::slotJuliaHistoryClear);
}

double cDockFractal::JuliaSliderRange() const
{
	if (!COMMON_UI->comboBox_julia_range) return 2.0;
	switch (COMMON_UI->comboBox_julia_range->currentIndex())
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
	if (COMMON_UI->jslider_julia_cx && COMMON_UI->label_julia_cx_value)
	{
		double val = COMMON_UI->jslider_julia_cx->value() / 1000.0 * range;
		COMMON_UI->label_julia_cx_value->setText(QString::number(val, 'f', 3));
	}
	if (COMMON_UI->jslider_julia_cy && COMMON_UI->label_julia_cy_value)
	{
		double val = COMMON_UI->jslider_julia_cy->value() / 1000.0 * range;
		COMMON_UI->label_julia_cy_value->setText(QString::number(val, 'f', 3));
	}
	if (COMMON_UI->jslider_julia_cz && COMMON_UI->label_julia_cz_value)
	{
		double val = COMMON_UI->jslider_julia_cz->value() / 1000.0 * range;
		COMMON_UI->label_julia_cz_value->setText(QString::number(val, 'f', 3));
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
	if (COMMON_UI->listWidget_julia_history)
	{
		COMMON_UI->listWidget_julia_history->clear();
		for (int i = juliaHistory.size() - 1; i >= 0; i--)
		{
			const auto &e = juliaHistory[i];
			QString text = QString("[%1] c = (%2, %3, %4)")
				.arg(e.timestamp)
				.arg(e.cx, 0, 'f', 4)
				.arg(e.cy, 0, 'f', 4)
				.arg(e.cz, 0, 'f', 4);
			COMMON_UI->listWidget_julia_history->addItem(text);
		}
	}
}

void cDockFractal::SetJuliaC(double cx, double cy, double cz)
{
	params->Set("julia_c", CVector3(cx, cy, cz));
	slotSynchronizeInterfaceJulia(params);
}

void cDockFractal::slotJuliaSliderCxChanged(int value)
{
	double range = JuliaSliderRange();
	double cx = value / 1000.0 * range;
	CVector3 current = params->Get<CVector3>("julia_c");
	current.x = cx;
	params->Set("julia_c", current);
	slotSynchronizeInterfaceJulia(params);
	UpdateJuliaSliderLabels();
}

void cDockFractal::slotJuliaSliderCyChanged(int value)
{
	double range = JuliaSliderRange();
	double cy = value / 1000.0 * range;
	CVector3 current = params->Get<CVector3>("julia_c");
	current.y = cy;
	params->Set("julia_c", current);
	slotSynchronizeInterfaceJulia(params);
	UpdateJuliaSliderLabels();
}

void cDockFractal::slotJuliaSliderCzChanged(int value)
{
	double range = JuliaSliderRange();
	double cz = value / 1000.0 * range;
	CVector3 current = params->Get<CVector3>("julia_c");
	current.z = cz;
	params->Set("julia_c", current);
	slotSynchronizeInterfaceJulia(params);
	UpdateJuliaSliderLabels();
}

void cDockFractal::TriggerAutoBeauty()
{
	if (!beautyAutoTimer) return;
	if (beautyApplying) return; // prevent infinite loop when applying beauty result
	if (beautyScanRunning) return;
	bool hasCheckbox = (COMMON_UI->checkBox_beauty_auto != nullptr);
	bool isChecked = hasCheckbox && COMMON_UI->checkBox_beauty_auto->isChecked();
	if (isChecked)
	{
		beautyAutoTimer->start(); // singleShot — restarts on every call (debounce)
	}
}

void cDockFractal::slotJuliaSliderReleased()
{
	CHECK_MAIN_INTERFACE();
	gMainInterface->RequestRender(QStringLiteral("julia slider"), 80);
	TriggerAutoBeauty();
}

void cDockFractal::slotJuliaRangeChanged(int /*index*/)
{
	UpdateJuliaSliderLabels();
}

void cDockFractal::slotJuliaCopy()
{
	CVector3 c = params->Get<CVector3>("julia_c");
	QString text = QString("%1, %2, %3")
		.arg(c.x, 0, 'f', 6).arg(c.y, 0, 'f', 6).arg(c.z, 0, 'f', 6);
	QApplication::clipboard()->setText(text);
}

void cDockFractal::slotJuliaPaste()
{
	CHECK_MAIN_INTERFACE();
	CHECK_PARAMS();
	QString text = QApplication::clipboard()->text();
	QStringList parts = text.split(',');
	if (parts.size() >= 3)
	{
		double cx = parts[0].trimmed().toDouble();
		double cy = parts[1].trimmed().toDouble();
		double cz = parts[2].trimmed().toDouble();
		SetJuliaC(cx, cy, cz);
		AddToJuliaHistory(cx, cy, cz);
		gMainInterface->RequestRender(QStringLiteral("julia slider"), 80);
	}
}

void cDockFractal::slotJuliaRandom()
{
	CHECK_MAIN_INTERFACE();
	CHECK_PARAMS();
	double range = JuliaSliderRange();
	double cx = (QRandomGenerator::global()->generateDouble() * 2.0 - 1.0) * range;
	double cy = (QRandomGenerator::global()->generateDouble() * 2.0 - 1.0) * range;
	double cz = (QRandomGenerator::global()->generateDouble() * 2.0 - 1.0) * range;
	SetJuliaC(cx, cy, cz);
	AddToJuliaHistory(cx, cy, cz);
	gMainInterface->RequestRender(QStringLiteral("julia slider"), 80);
}

void cDockFractal::slotJuliaZero()
{
	CHECK_MAIN_INTERFACE();
	CHECK_PARAMS();
	SetJuliaC(0.0, 0.0, 0.0);
	gMainInterface->RequestRender(QStringLiteral("julia slider"), 80);
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

	// Use params→interface sync (same as clickGetJuliaConstant)
	params->Set("julia_c", CVector3(p.cx, p.cy, p.cz));
	params->Set("julia_mode", true);
	slotEnableJuliaMode();
	slotSynchronizeInterfaceJulia(params);

	AddToJuliaHistory(p.cx, p.cy, p.cz);
	gMainInterface->RequestRender(QStringLiteral("julia slider"), 80);
}

void cDockFractal::slotJuliaSweepStart()
{
	if (sweepRunning) return;

	sweepAxis = COMMON_UI->comboBox_julia_sweep_axis ? COMMON_UI->comboBox_julia_sweep_axis->currentIndex() : 0;
	sweepFrom = COMMON_UI->spinBox_julia_sweep_from ? COMMON_UI->spinBox_julia_sweep_from->value() : -2.0;
	sweepTo = COMMON_UI->spinBox_julia_sweep_to ? COMMON_UI->spinBox_julia_sweep_to->value() : 2.0;
	sweepTotalSteps = COMMON_UI->spinBox_julia_sweep_steps ? COMMON_UI->spinBox_julia_sweep_steps->value() : 50;
	sweepCurrentStep = 0;
	sweepRunning = true;

	// Auto-enable Julia mode
	if (COMMON_UI->groupCheck_julia_mode && !COMMON_UI->groupCheck_julia_mode->isChecked())
		COMMON_UI->groupCheck_julia_mode->setChecked(true);

	if (COMMON_UI->progressBar_julia_sweep) COMMON_UI->progressBar_julia_sweep->setValue(0);

	if (sweepTimer) sweepTimer->start();
}

void cDockFractal::slotJuliaSweepStop()
{
	sweepRunning = false;
	if (sweepTimer) sweepTimer->stop();
	if (COMMON_UI->progressBar_julia_sweep)
		COMMON_UI->progressBar_julia_sweep->setValue(0);
}

void cDockFractal::slotJuliaSweepStep()
{
	CHECK_MAIN_INTERFACE();
	if (!sweepRunning || sweepCurrentStep >= sweepTotalSteps)
	{
		slotJuliaSweepStop();
		return;
	}

	double t = static_cast<double>(sweepCurrentStep) / static_cast<double>(sweepTotalSteps - 1);
	double val = sweepFrom + t * (sweepTo - sweepFrom);

	// Get current c values from params
	CVector3 cVec = params->Get<CVector3>("julia_c");
	double cx = cVec.x;
	double cy = cVec.y;
	double cz = cVec.z;

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

	SetJuliaC(cx, cy, cz);

	// Update progress
	int progress = static_cast<int>((sweepCurrentStep + 1) * 100.0 / sweepTotalSteps);
	if (COMMON_UI->progressBar_julia_sweep) COMMON_UI->progressBar_julia_sweep->setValue(progress);

	sweepCurrentStep++;
	gMainInterface->RequestRender(QStringLiteral("julia sweep"), 0);
}

void cDockFractal::slotJuliaHistoryItemDoubleClicked(QListWidgetItem *item)
{
	CHECK_MAIN_INTERFACE();
	if (!item) return;
	int row = COMMON_UI->listWidget_julia_history->row(item);
	int historyIndex = juliaHistory.size() - 1 - row;
	if (historyIndex < 0 || historyIndex >= juliaHistory.size()) return;

	const auto &entry = juliaHistory[historyIndex];
	SetJuliaC(entry.cx, entry.cy, entry.cz);
	gMainInterface->RequestRender(QStringLiteral("julia history"), 80);
}

void cDockFractal::slotJuliaHistorySave()
{
	if (!COMMON_UI->listWidget_julia_history) return;
	QListWidgetItem *item = COMMON_UI->listWidget_julia_history->currentItem();
	if (!item) return;

	int row = COMMON_UI->listWidget_julia_history->row(item);
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
	if (COMMON_UI->listWidget_julia_history) COMMON_UI->listWidget_julia_history->clear();
}

// ========================================================================
// 3x3lion Julia Heatmap — maps interest scores across Julia c-space
// ========================================================================

void cDockFractal::SetupJuliaHeatmap()
{
	if (COMMON_UI->comboBox_heatmap_resolution)
		COMMON_UI->comboBox_heatmap_resolution->setCurrentIndex(1); // 32x32 default

	ConnectJuliaHeatmapSignals();
}

void cDockFractal::ConnectJuliaHeatmapSignals()
{
	if (COMMON_UI->pushButton_heatmap_scan)
		connect(COMMON_UI->pushButton_heatmap_scan, &QPushButton::clicked, this,
			&cDockFractal::slotHeatmapScan);

	if (COMMON_UI->pushButton_heatmap_stop)
		connect(COMMON_UI->pushButton_heatmap_stop, &QPushButton::clicked, this,
			&cDockFractal::slotHeatmapStop);

	if (COMMON_UI->pushButton_heatmap_clear)
		connect(COMMON_UI->pushButton_heatmap_clear, &QPushButton::clicked, this,
			&cDockFractal::slotHeatmapClear);

	if (COMMON_UI->comboBox_heatmap_axis_h)
		connect(COMMON_UI->comboBox_heatmap_axis_h, QOverload<int>::of(&QComboBox::currentIndexChanged),
			this, &cDockFractal::slotHeatmapAxisHChanged);

	if (COMMON_UI->comboBox_heatmap_axis_v)
		connect(COMMON_UI->comboBox_heatmap_axis_v, QOverload<int>::of(&QComboBox::currentIndexChanged),
			this, &cDockFractal::slotHeatmapAxisVChanged);

	if (COMMON_UI->comboBox_heatmap_resolution)
		connect(COMMON_UI->comboBox_heatmap_resolution,
			QOverload<int>::of(&QComboBox::currentIndexChanged), this,
			&cDockFractal::slotHeatmapResolutionChanged);

	if (COMMON_UI->comboBox_heatmap_scheme)
		connect(COMMON_UI->comboBox_heatmap_scheme, QOverload<int>::of(&QComboBox::currentIndexChanged),
			this, &cDockFractal::slotHeatmapSchemeChanged);

	if (COMMON_UI->widget_julia_heatmap)
	{
		connect(COMMON_UI->widget_julia_heatmap, &cJuliaHeatmapWidget::signalCellClicked, this,
			&cDockFractal::slotHeatmapCellClicked);
		connect(COMMON_UI->widget_julia_heatmap, &cJuliaHeatmapWidget::signalHoverInfo, this,
			&cDockFractal::slotHeatmapHoverInfo);
	}
}

void cDockFractal::UpdateHeatmapMarker()
{
	if (!COMMON_UI->widget_julia_heatmap) return;

	CVector3 cCur = params->Get<CVector3>("julia_c");
	double cx = cCur.x, cy = cCur.y, cz = cCur.z;

	int axisH = COMMON_UI->widget_julia_heatmap->GetAxisH();
	int axisV = COMMON_UI->widget_julia_heatmap->GetAxisV();

	double cArr[3] = {cx, cy, cz};
	COMMON_UI->widget_julia_heatmap->SetMarker(cArr[axisH], cArr[axisV]);
}

void cDockFractal::BuildScanEngine()
{
	if (!params || !gPar || !gParFractal) return;
	SynchronizeInterfaceWindow(COMMON_UI->groupCheck_julia_mode, params, qInterface::read);
	scanRenderData.reset(new sRenderData);
	scanRenderData->objectData.resize(NUMBER_OF_FRACTALS);
	scanFractals.reset(new cNineFractals(gParFractal, gPar));
	scanParamRender.reset(new sParamRender(gPar, &scanRenderData->objectData));

	// Use beauty-specific iteration range
	beautyIterStart = COMMON_UI->spinBox_beauty_iter_start ? COMMON_UI->spinBox_beauty_iter_start->value() : 0;
	int beautyIterStop = COMMON_UI->spinBox_beauty_iter_stop ? COMMON_UI->spinBox_beauty_iter_stop->value() : 64;
	scanParamRender->N = beautyIterStop;

	for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
		scanFractals->SetJuliaEnabled(i, true);
}

double cDockFractal::ComputeQuickScore(double cx, double cy, double cz)
{
	if (!scanParamRender || !scanFractals) return 0.0;
	return ComputeQuickScoreReal(cx, cy, cz, *scanParamRender, *scanFractals);
}

double cDockFractal::ComputeQuickScoreReal(double cx, double cy, double cz,
	sParamRender &pr, cNineFractals &nf)
{
	// Set julia constant for all formula slots
	CVector3 juliaC(cx, cy, cz);
	for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
	{
		nf.SetJuliaConstant(i, juliaC);
		nf.SetJuliaEnabled(i, true);
	}

	// Sample a 4³ grid of z-starting points using the REAL fractal engine
	const int gridN = 4;
	const double zRange = 1.5;
	const double zStep = 2.0 * zRange / (gridN - 1);
	const int maxIter = std::min(60, pr.N);

	int inside = 0;   // maxiter reached
	int surface = 0;  // near surface (small distance)
	int outside = 0;  // far from surface
	double iterSum = 0.0;
	double iterSqSum = 0.0;
	int total = gridN * gridN * gridN;

	for (int iz = 0; iz < gridN; iz++)
	{
		double z0z = -zRange + iz * zStep;
		for (int iy = 0; iy < gridN; iy++)
		{
			double z0y = -zRange + iy * zStep;
			for (int ix = 0; ix < gridN; ix++)
			{
				double z0x = -zRange + ix * zStep;

				sDistanceIn distIn(CVector3(z0x, z0y, z0z), 0.001, false);
				sDistanceOut distOut;
				distOut.distance = 0;
				distOut.iters = 0;
				distOut.totalIters = 0;
				distOut.colorIndex = 0;
				distOut.objectId = 0;
				distOut.maxiter = false;

				CalculateDistanceSimple(pr, nf, distIn, &distOut, -1, nullptr);

				double iters = static_cast<double>(distOut.iters);
				iterSum += iters;
				iterSqSum += iters * iters;

				if (distOut.maxiter)
					inside++;
				else if (distOut.distance < 0.01)
					surface++;
				else
					outside++;
			}
		}
	}

	// Reject trivial: all inside or all outside
	double insideFrac = static_cast<double>(inside) / total;
	double surfaceFrac = static_cast<double>(surface) / total;
	if (insideFrac > 0.9 || (inside + surface) == 0) return 0.0;
	if (insideFrac < 0.05 && surfaceFrac < 0.05) return 0.0;

	// Balance: best when ~30-60% inside (complex boundary region)
	double balanceScore = 1.0 - 2.0 * std::abs(insideFrac - 0.4);
	balanceScore = std::max(0.0, balanceScore);

	// Surface richness: many points near the fractal surface
	double surfaceScore = surfaceFrac * 3.0;
	surfaceScore = std::min(1.0, surfaceScore);

	// Iteration variance: complex boundary structure
	double varianceScore = 0.0;
	if (total > 1)
	{
		double mean = iterSum / total;
		double var = (iterSqSum / total) - (mean * mean);
		double stddev = std::sqrt(std::max(0.0, var));
		varianceScore = std::min(1.0, stddev / (maxIter * 0.15));
	}

	return qBound(0.0, 0.25 * balanceScore + 0.35 * varianceScore + 0.4 * surfaceScore, 1.0);
}

static QVector<double> RunHeatmapScanAsync(const int resolution, const double range,
	const int axisH, const int axisV, const double fixedVal, sParamRender &pr, cNineFractals &nf,
	const std::shared_ptr<std::atomic<bool>> &cancelled,
	const std::shared_ptr<std::atomic<int>> &progress)
{
	QVector<double> scores(resolution * resolution, 0.0);
	const int total = resolution * resolution;
	const double stepSize = 2.0 * range / resolution;
	int done = 0;

	for (int gy = 0; gy < resolution; ++gy)
	{
		const double cV = range - (gy + 0.5) * stepSize;
		for (int gx = 0; gx < resolution; ++gx)
		{
			if (cancelled && cancelled->load())
				return scores;

			const double cH = -range + (gx + 0.5) * stepSize;
			double cArr[3] = {0.0, 0.0, 0.0};
			cArr[axisH] = cH;
			cArr[axisV] = cV;
			const int fixedAxis = 3 - axisH - axisV;
			if (fixedAxis >= 0 && fixedAxis <= 2)
				cArr[fixedAxis] = fixedVal;

			scores[gy * resolution + gx] =
				cDockFractal::ComputeQuickScoreReal(cArr[0], cArr[1], cArr[2], pr, nf);

			++done;
			if (progress && (done % 4 == 0 || done == total))
			{
				const int percent = total > 0 ? (done * 100) / total : 100;
				progress->store(percent);
			}
		}
	}

	if (progress)
		progress->store(100);
	return scores;
}

void cDockFractal::slotHeatmapScan()
{
	if (!COMMON_UI->widget_julia_heatmap) return;
	if (heatmapScanRunning)
		return;

	static const int resolutions[] = {16, 32, 48, 64};
	int resIdx = COMMON_UI->comboBox_heatmap_resolution ? COMMON_UI->comboBox_heatmap_resolution->currentIndex() : 1;
	if (resIdx < 0 || resIdx > 3) resIdx = 1;
	const int resolution = resolutions[resIdx];
	const double range = JuliaSliderRange();

	const int axisH = COMMON_UI->comboBox_heatmap_axis_h ? COMMON_UI->comboBox_heatmap_axis_h->currentIndex() : 0;
	const int axisV = COMMON_UI->comboBox_heatmap_axis_v ? COMMON_UI->comboBox_heatmap_axis_v->currentIndex() : 1;
	COMMON_UI->widget_julia_heatmap->SetResolution(resolution);
	COMMON_UI->widget_julia_heatmap->SetRange(range);
	COMMON_UI->widget_julia_heatmap->SetAxes(axisH, axisV);

	int fixedAxis = 3 - axisH - axisV;
	if (fixedAxis < 0 || fixedAxis > 2) fixedAxis = 2;
	const CVector3 cFixed = params->Get<CVector3>("julia_c");
	const double cArr[3] = {cFixed.x, cFixed.y, cFixed.z};
	COMMON_UI->widget_julia_heatmap->SetFixedAxisValue(cArr[fixedAxis]);

	COMMON_UI->widget_julia_heatmap->ClearScores();
	COMMON_UI->widget_julia_heatmap->SetExternalScanActive(true);

	heatmapScanRunning = true;
	if (heatmapScanCancelled)
		heatmapScanCancelled->store(false);
	if (heatmapScanProgress)
		heatmapScanProgress->store(0);

	if (COMMON_UI->progressBar_heatmap)
		COMMON_UI->progressBar_heatmap->setValue(0);
	if (COMMON_UI->pushButton_heatmap_scan)
		COMMON_UI->pushButton_heatmap_scan->setEnabled(false);
	if (COMMON_UI->label_heatmap_info)
		COMMON_UI->label_heatmap_info->setText("Scanning c-space in background...");
	if (heatmapProgressTimer)
		heatmapProgressTimer->start();

	SynchronizeInterfaceWindow(COMMON_UI->groupCheck_julia_mode, params, qInterface::read);
	const int beautyIterStop =
		COMMON_UI->spinBox_beauty_iter_stop ? COMMON_UI->spinBox_beauty_iter_stop->value() : 64;
	const double fixedVal = cArr[fixedAxis];

	auto parCopy = std::make_shared<cParameterContainer>(*params);
	auto fractalCopy = std::make_shared<cFractalContainer>(*fractalParams);
	auto cancelled = heatmapScanCancelled;
	auto progress = heatmapScanProgress;

	QFuture<QVector<double>> future = QtConcurrent::run(
		[resolution, range, axisH, axisV, fixedVal, beautyIterStop, parCopy, fractalCopy, cancelled,
			progress]() {
			sRenderData renderData;
			renderData.objectData.resize(NUMBER_OF_FRACTALS);
			cNineFractals nf(fractalCopy, parCopy);
			sParamRender pr(parCopy, &renderData.objectData);
			pr.N = beautyIterStop;
			for (int i = 0; i < NUMBER_OF_FRACTALS; ++i)
				nf.SetJuliaEnabled(i, true);
			return RunHeatmapScanAsync(resolution, range, axisH, axisV, fixedVal, pr, nf, cancelled,
				progress);
		});
	heatmapScanWatcher->setFuture(future);
}

void cDockFractal::slotHeatmapScanFinished()
{
	heatmapScanRunning = false;
	if (heatmapProgressTimer)
		heatmapProgressTimer->stop();

	if (COMMON_UI->widget_julia_heatmap)
		COMMON_UI->widget_julia_heatmap->SetExternalScanActive(false);
	if (COMMON_UI->pushButton_heatmap_scan)
		COMMON_UI->pushButton_heatmap_scan->setEnabled(true);

	if (!heatmapScanWatcher)
	{
		heatmapScanForDrone = false;
		return;
	}

	const QVector<double> scores = heatmapScanWatcher->result();
	if (COMMON_UI->widget_julia_heatmap && scores.size() == COMMON_UI->widget_julia_heatmap->GetResolution()
			* COMMON_UI->widget_julia_heatmap->GetResolution())
	{
		COMMON_UI->widget_julia_heatmap->SetScoreGrid(scores);
	}

	slotHeatmapScanProgress(100);

	if (heatmapScanCancelled && heatmapScanCancelled->load())
	{
		if (COMMON_UI->label_heatmap_info)
			COMMON_UI->label_heatmap_info->setText("Scan stopped");
		heatmapScanForDrone = false;
		return;
	}

	slotHeatmapScanComplete();

	if (heatmapScanForDrone)
	{
		heatmapScanForDrone = false;
		LaunchDroneFleetAfterHeatmap();
	}
}

void cDockFractal::slotHeatmapStop()
{
	if (heatmapScanCancelled)
		heatmapScanCancelled->store(true);
	if (COMMON_UI->widget_julia_heatmap)
		COMMON_UI->widget_julia_heatmap->SetExternalScanActive(false);
	if (COMMON_UI->label_heatmap_info)
		COMMON_UI->label_heatmap_info->setText("Stopping scan...");
}

void cDockFractal::slotHeatmapClear()
{
	if (COMMON_UI->widget_julia_heatmap) COMMON_UI->widget_julia_heatmap->ClearScores();
	if (COMMON_UI->progressBar_heatmap) COMMON_UI->progressBar_heatmap->setValue(0);
	if (COMMON_UI->label_heatmap_info)
		COMMON_UI->label_heatmap_info->setText("Hover over heatmap for details");
}

void cDockFractal::slotHeatmapAxisHChanged(int index)
{
	if (!COMMON_UI->widget_julia_heatmap) return;

	int axisV = COMMON_UI->comboBox_heatmap_axis_v ? COMMON_UI->comboBox_heatmap_axis_v->currentIndex() : 1;
	if (index == axisV)
	{
		// Swap to avoid same axis on both
		int newV = (index + 1) % 3;
		if (COMMON_UI->comboBox_heatmap_axis_v)
			COMMON_UI->comboBox_heatmap_axis_v->setCurrentIndex(newV);
		axisV = newV;
	}
	COMMON_UI->widget_julia_heatmap->SetAxes(index, axisV);
	COMMON_UI->widget_julia_heatmap->ClearScores();
}

void cDockFractal::slotHeatmapAxisVChanged(int index)
{
	if (!COMMON_UI->widget_julia_heatmap) return;

	int axisH = COMMON_UI->comboBox_heatmap_axis_h ? COMMON_UI->comboBox_heatmap_axis_h->currentIndex() : 0;
	if (index == axisH)
	{
		int newH = (index + 1) % 3;
		if (COMMON_UI->comboBox_heatmap_axis_h)
			COMMON_UI->comboBox_heatmap_axis_h->setCurrentIndex(newH);
		axisH = newH;
	}
	COMMON_UI->widget_julia_heatmap->SetAxes(axisH, index);
	COMMON_UI->widget_julia_heatmap->ClearScores();
}

void cDockFractal::slotHeatmapResolutionChanged(int index)
{
	if (!COMMON_UI->widget_julia_heatmap) return;
	static const int resolutions[] = {16, 32, 48, 64};
	if (index >= 0 && index <= 3)
		COMMON_UI->widget_julia_heatmap->SetResolution(resolutions[index]);
}

void cDockFractal::slotHeatmapSchemeChanged(int index)
{
	if (!COMMON_UI->widget_julia_heatmap) return;
	COMMON_UI->widget_julia_heatmap->SetColorScheme(
		static_cast<cJuliaHeatmapWidget::eColorScheme>(index));
}

void cDockFractal::slotHeatmapCellClicked(double cH, double cV)
{
	CHECK_MAIN_INTERFACE();
	CHECK_PARAMS();
	// When user clicks a cell, jump to that Julia c-value
	int axisH = COMMON_UI->widget_julia_heatmap ? COMMON_UI->widget_julia_heatmap->GetAxisH() : 0;
	int axisV = COMMON_UI->widget_julia_heatmap ? COMMON_UI->widget_julia_heatmap->GetAxisV() : 1;

	CVector3 cCur = params->Get<CVector3>("julia_c");
	double cArr[3] = {cCur.x, cCur.y, cCur.z};
	cArr[axisH] = cH;
	cArr[axisV] = cV;

	SetJuliaC(cArr[0], cArr[1], cArr[2]);
	AddToJuliaHistory(cArr[0], cArr[1], cArr[2]);
	UpdateHeatmapMarker();
	gMainInterface->RequestRender(QStringLiteral("julia heatmap"), 0);
}

void cDockFractal::slotHeatmapScanProgress(int percent)
{
	if (COMMON_UI->progressBar_heatmap) COMMON_UI->progressBar_heatmap->setValue(percent);
}

void cDockFractal::slotHeatmapScanComplete()
{
	if (COMMON_UI->progressBar_heatmap) COMMON_UI->progressBar_heatmap->setValue(100);
	if (COMMON_UI->label_heatmap_info)
		COMMON_UI->label_heatmap_info->setText("Scan complete — click hotspots to explore");
	UpdateHeatmapMarker();
}

void cDockFractal::slotHeatmapHoverInfo(double cH, double cV, double score)
{
	if (!COMMON_UI->label_heatmap_info) return;
	int axisH = COMMON_UI->widget_julia_heatmap ? COMMON_UI->widget_julia_heatmap->GetAxisH() : 0;
	int axisV = COMMON_UI->widget_julia_heatmap ? COMMON_UI->widget_julia_heatmap->GetAxisV() : 1;

	static const char *names[] = {"c.x", "c.y", "c.z"};
	COMMON_UI->label_heatmap_info->setText(
		QString("%1=%2  %3=%4  score=%5")
			.arg(names[axisH])
			.arg(QString::number(cH, 'f', 3))
			.arg(names[axisV])
			.arg(QString::number(cV, 'f', 3))
			.arg(QString::number(score, 'f', 4)));
}

// ========================================================================
// ===== 3x3lion Drone Explorer =====
// ========================================================================

void cDockFractal::SetupDroneExplorer()
{
	ConnectDroneExplorerSignals();
}

void cDockFractal::ConnectDroneExplorerSignals()
{
	if (COMMON_UI->pushButton_drone_launch)
		connect(COMMON_UI->pushButton_drone_launch, &QPushButton::clicked, this,
			&cDockFractal::slotDroneLaunch);

	if (COMMON_UI->pushButton_drone_stop)
		connect(COMMON_UI->pushButton_drone_stop, &QPushButton::clicked, this,
			&cDockFractal::slotDroneStop);

	if (COMMON_UI->pushButton_drone_reset)
		connect(COMMON_UI->pushButton_drone_reset, &QPushButton::clicked, this,
			&cDockFractal::slotDroneReset);

	if (COMMON_UI->comboBox_drone_strategy)
		connect(COMMON_UI->comboBox_drone_strategy, QOverload<int>::of(&QComboBox::currentIndexChanged),
			this, &cDockFractal::slotDroneStrategyChanged);

	if (COMMON_UI->jslider_drone_speed)
		connect(COMMON_UI->jslider_drone_speed, &QSlider::valueChanged, this,
			&cDockFractal::slotDroneSpeedChanged);

	if (COMMON_UI->widget_drone_explorer)
	{
		connect(COMMON_UI->widget_drone_explorer, &cDroneExplorerWidget::signalFleetStatus, this,
			&cDockFractal::slotDroneFleetStatus);
		connect(COMMON_UI->widget_drone_explorer, &cDroneExplorerWidget::signalDroneClicked, this,
			&cDockFractal::slotDroneClicked);
	}
}

bool cDockFractal::FeedHeatmapToDronesFromCache()
{
	if (!COMMON_UI->widget_drone_explorer || !COMMON_UI->widget_julia_heatmap) return false;
	if (!COMMON_UI->widget_julia_heatmap->HasScoreData()) return false;

	cJuliaHeatmapWidget *heatmap = COMMON_UI->widget_julia_heatmap;
	COMMON_UI->widget_drone_explorer->SetRange(heatmap->GetRange());
	COMMON_UI->widget_drone_explorer->SetScoreGrid(heatmap->GetScores(), heatmap->GetResolution());
	return true;
}

void cDockFractal::LaunchDroneFleetAfterHeatmap()
{
	if (!COMMON_UI->widget_drone_explorer) return;
	FeedHeatmapToDronesFromCache();
	COMMON_UI->widget_drone_explorer->StartFleet();
	if (COMMON_UI->label_drone_status)
		COMMON_UI->label_drone_status->setText("Fleet launched — drones exploring c-space...");
}

void cDockFractal::slotDroneLaunch()
{
	if (!COMMON_UI->widget_drone_explorer) return;

	if (FeedHeatmapToDronesFromCache())
	{
		LaunchDroneFleetAfterHeatmap();
		return;
	}

	heatmapScanForDrone = true;
	if (!heatmapScanRunning)
		slotHeatmapScan();
	else if (COMMON_UI->label_drone_status)
		COMMON_UI->label_drone_status->setText("Waiting for heatmap scan to finish...");
}

void cDockFractal::slotDroneStop()
{
	if (!COMMON_UI->widget_drone_explorer) return;
	COMMON_UI->widget_drone_explorer->StopFleet();

	if (COMMON_UI->label_drone_status)
		COMMON_UI->label_drone_status->setText("Fleet recalled — drones holding position");
}

void cDockFractal::slotDroneReset()
{
	if (!COMMON_UI->widget_drone_explorer) return;
	COMMON_UI->widget_drone_explorer->ResetFleet();

	if (COMMON_UI->label_drone_status)
		COMMON_UI->label_drone_status->setText("Fleet reset — ready to launch");
}

void cDockFractal::slotDroneStrategyChanged(int index)
{
	if (COMMON_UI->widget_drone_explorer)
		COMMON_UI->widget_drone_explorer->SetStrategy(index);
}

void cDockFractal::slotDroneSpeedChanged(int value)
{
	if (COMMON_UI->widget_drone_explorer)
		COMMON_UI->widget_drone_explorer->SetSpeed(value / 10.0);
}

void cDockFractal::slotDroneFleetStatus(int discoveries, double bestScore, double coverage)
{
	if (!COMMON_UI->label_drone_status) return;
	COMMON_UI->label_drone_status->setText(
		QString("Discoveries: %1 | Best: %2 | Coverage: %3%")
			.arg(discoveries)
			.arg(QString::number(bestScore, 'f', 3))
			.arg(QString::number(coverage * 100.0, 'f', 1)));
}

void cDockFractal::slotDroneClicked(double cH, double cV)
{
	if (!COMMON_UI->widget_julia_heatmap) return;

	int axisH = COMMON_UI->widget_julia_heatmap->GetAxisH();
	int axisV = COMMON_UI->widget_julia_heatmap->GetAxisV();

	CVector3 cDrone = params->Get<CVector3>("julia_c");
	double cArr[3] = {cDrone.x, cDrone.y, cDrone.z};
	cArr[axisH] = cH;
	cArr[axisV] = cV;

	SetJuliaC(cArr[0], cArr[1], cArr[2]);
	AddToJuliaHistory(cArr[0], cArr[1], cArr[2]);
	UpdateHeatmapMarker();
	gMainInterface->RequestRender(QStringLiteral("julia drone"), 0);
}
// =====================================================================

// Free function for async beauty scanning - thread-safe, no Qt UI access
static QVector<sBeautyResult> RunBeautyScanAsync(
	double centerX, double centerY, double centerZ,
	double range, double wx, double wy, double wz,
	sParamRender &pr, cNineFractals &nf)
{
	QVector<sBeautyResult> results;
	double rangeX = range * wx;
	double rangeY = range * wy;
	double rangeZ = range * wz;

	// Pass 1: coarse grid 8³ = 512 centered on current Julia c
	int perAxis = 8;
	double stepX = (rangeX > 0) ? 2.0 * rangeX / (perAxis - 1) : 0;
	double stepY = (rangeY > 0) ? 2.0 * rangeY / (perAxis - 1) : 0;
	double stepZ = (rangeZ > 0) ? 2.0 * rangeZ / (perAxis - 1) : 0;

	for (int iz = 0; iz < perAxis; iz++)
	{
		for (int iy = 0; iy < perAxis; iy++)
			for (int ix = 0; ix < perAxis; ix++)
			{
				double cx = (rangeX > 0) ? centerX - rangeX + ix * stepX : centerX;
				double cy = (rangeY > 0) ? centerY - rangeY + iy * stepY : centerY;
				double cz = (rangeZ > 0) ? centerZ - rangeZ + iz * stepZ : centerZ;
				
				// Set julia constant for all formula slots
				CVector3 juliaC(cx, cy, cz);
				for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
				{
					nf.SetJuliaConstant(i, juliaC);
					nf.SetJuliaEnabled(i, true);
				}
				
				double s = cDockFractal::ComputeQuickScoreReal(cx, cy, cz, pr, nf);
				if (s > 0.001) results.append({cx, cy, cz, s});
			}
	}

	// Sort and keep top 16
	std::sort(results.begin(), results.end());
	if (results.size() > 16) results.resize(16);

	// Pass 2: refine around top 16 with 4³ grid each
	QVector<sBeautyResult> refined;
	double refRangeX = rangeX * 0.12;
	double refRangeY = rangeY * 0.12;
	double refRangeZ = rangeZ * 0.12;
	int perAxis2 = 4;
	double step2X = (refRangeX > 0) ? 2.0 * refRangeX / (perAxis2 - 1) : 0;
	double step2Y = (refRangeY > 0) ? 2.0 * refRangeY / (perAxis2 - 1) : 0;
	double step2Z = (refRangeZ > 0) ? 2.0 * refRangeZ / (perAxis2 - 1) : 0;

	for (int t = 0; t < results.size(); t++)
	{
		const auto &top = results[t];
		for (int iz = 0; iz < perAxis2; iz++)
			for (int iy = 0; iy < perAxis2; iy++)
				for (int ix = 0; ix < perAxis2; ix++)
				{
					double cx = (refRangeX > 0) ? top.cx - refRangeX + ix * step2X : top.cx;
					double cy = (refRangeY > 0) ? top.cy - refRangeY + iy * step2Y : top.cy;
					double cz = (refRangeZ > 0) ? top.cz - refRangeZ + iz * step2Z : top.cz;
					
					// Set julia constant for all formula slots
					CVector3 juliaC2(cx, cy, cz);
					for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
					{
						nf.SetJuliaConstant(i, juliaC2);
						nf.SetJuliaEnabled(i, true);
					}
					
					double s = cDockFractal::ComputeQuickScoreReal(cx, cy, cz, pr, nf);
					if (s > 0.001) refined.append({cx, cy, cz, s});
				}
	}

	// Sort and keep top 10
	std::sort(refined.begin(), refined.end());
	results.clear();
	for (int i = 0; i < qMin(10, refined.size()); i++)
		results.append(refined[i]);

	return results;
}

void cDockFractal::slotBeautyFindBest()
{
	if (beautyScanRunning)
	{
		// Scan already in progress — retry after it finishes
		if (beautyAutoTimer) beautyAutoTimer->start();
		return;
	}
	beautyScanRunning = true;
	beautyScanTimer.start();

	double range = COMMON_UI->spinBox_beauty_range ? COMMON_UI->spinBox_beauty_range->value() : 2.0;

	// Sync UI → params so we read current slider values
	SynchronizeInterfaceWindow(COMMON_UI->groupCheck_julia_mode, params, qInterface::read);

	// Use current Julia c as center of search
	CVector3 center = params->Get<CVector3>("julia_c");

	if (COMMON_UI->label_beauty_result)
		COMMON_UI->label_beauty_result->setText(
			QString("Scanning around (%1, %2, %3)...")
				.arg(center.x, 0, 'f', 3).arg(center.y, 0, 'f', 3).arg(center.z, 0, 'f', 3));
	if (COMMON_UI->progressBar_beauty)
		COMMON_UI->progressBar_beauty->setValue(0);
	if (COMMON_UI->pushButton_beauty_find) COMMON_UI->pushButton_beauty_find->setEnabled(false);

	double wx = COMMON_UI->spinBox_beauty_weight_x ? COMMON_UI->spinBox_beauty_weight_x->value() : 1.0;
	double wy = COMMON_UI->spinBox_beauty_weight_y ? COMMON_UI->spinBox_beauty_weight_y->value() : 1.0;
	double wz = COMMON_UI->spinBox_beauty_weight_z ? COMMON_UI->spinBox_beauty_weight_z->value() : 1.0;
	int beautyIterStop = COMMON_UI->spinBox_beauty_iter_stop ? COMMON_UI->spinBox_beauty_iter_stop->value() : 64;

	auto parCopy = std::make_shared<cParameterContainer>(*params);
	auto fractalCopy = std::make_shared<cFractalContainer>(*fractalParams);

	// Launch async scan — build fractal engine on worker thread (cNineFractals is not copyable)
	QFuture<QVector<sBeautyResult>> future = QtConcurrent::run(
		[center, range, wx, wy, wz, parCopy, fractalCopy, beautyIterStop]() {
			sRenderData renderData;
			renderData.objectData.resize(NUMBER_OF_FRACTALS);
			cNineFractals nf(fractalCopy, parCopy);
			sParamRender pr(parCopy, &renderData.objectData);
			pr.N = beautyIterStop;
			for (int i = 0; i < NUMBER_OF_FRACTALS; i++)
				nf.SetJuliaEnabled(i, true);
			return RunBeautyScanAsync(center.x, center.y, center.z, range, wx, wy, wz, pr, nf);
		});
	beautyScanWatcher->setFuture(future);
}

void cDockFractal::slotBeautyApplyNext()
{
	if (beautyResults.isEmpty()) return;

	beautyResultIndex++;
	if (beautyResultIndex >= beautyResults.size()) beautyResultIndex = 0;

	ApplyBeautyResult(beautyResults[beautyResultIndex]);
}

void cDockFractal::slotBeautyScanFinished()
{
	QVector<sBeautyResult> results = beautyScanWatcher->result();
	beautyScanRunning = false;

	// Sort results by score descending (using the operator< we defined)
	std::sort(results.begin(), results.end());

	if (!results.isEmpty())
	{
		beautyResults = results;
		beautyResultIndex = 0;
		ApplyBeautyResult(beautyResults[0]);
		if (COMMON_UI->pushButton_beauty_next) COMMON_UI->pushButton_beauty_next->setEnabled(true);

		if (COMMON_UI->label_beauty_result)
			COMMON_UI->label_beauty_result->setText(
				tr("Scan complete: %1 results in %2 ms — (%3, %4, %5) score=%6")
					.arg(beautyResults.size())
					.arg(beautyScanTimer.elapsed())
					.arg(results[0].cx, 0, 'f', 4).arg(results[0].cy, 0, 'f', 4)
					.arg(results[0].cz, 0, 'f', 4).arg(results[0].score, 0, 'f', 3));
	}
	else
	{
		beautyResults.clear();
		if (COMMON_UI->label_beauty_result)
			COMMON_UI->label_beauty_result->setText(tr("No interesting Julia sets found"));
		if (COMMON_UI->pushButton_beauty_next) COMMON_UI->pushButton_beauty_next->setEnabled(false);
	}

	if (COMMON_UI->progressBar_beauty) COMMON_UI->progressBar_beauty->setValue(100);

	// Re-enable UI controls
	if (COMMON_UI->pushButton_beauty_find) COMMON_UI->pushButton_beauty_find->setEnabled(true);
}

void cDockFractal::ApplyBeautyResult(const sBeautyResult &r)
{
	CHECK_MAIN_INTERFACE();
	CHECK_PARAMS();
	// Guard: prevent TriggerAutoBeauty from re-firing when we set julia_c
	beautyApplying = true;

	// Use the SAME mechanism as clickGetJuliaConstant (the working method):
	// 1. Write to parameter container
	// 2. Enable Julia mode
	// 3. SynchronizeInterfaceWindow to push params → UI widgets
	params->Set("julia_c", CVector3(r.cx, r.cy, r.cz));
	params->Set("julia_mode", true);

	slotEnableJuliaMode();
	slotSynchronizeInterfaceJulia(params);

	beautyApplying = false;

	if (COMMON_UI->label_beauty_result)
		COMMON_UI->label_beauty_result->setText(
			QString("%1/%2: (%3, %4, %5) score=%6")
				.arg(beautyResultIndex + 1).arg(beautyResults.size())
				.arg(r.cx, 0, 'f', 4).arg(r.cy, 0, 'f', 4)
				.arg(r.cz, 0, 'f', 4).arg(r.score, 0, 'f', 3));

	AddToJuliaHistory(r.cx, r.cy, r.cz);
	gMainInterface->RequestRender(QStringLiteral("julia beauty"), 80);
}
