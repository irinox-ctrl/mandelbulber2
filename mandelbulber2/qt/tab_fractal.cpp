#include <QDebug>
/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2016-22 Mandelbulber Team     §R-==%w["'~5]m%=L.=~5N
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
 * cTabFractal - contains ui logic for the fractal and transform tabs
 * tab_fractal.ui is the layout ui for the outer ui.
 * The formula specific ui is loaded dynamically in slotChangedComboFractal()
 * and reads the corresponding ui from formula/ui/fractal_<FORMULA_NAME>.ui
 */

#include "tab_fractal.h"

#include <QFile>
#include <QVBoxLayout>

#include "ui_tab_fractal.h"

#include "custom_formula_editor.h"
#include "dock_fractal.h"
#include "navigator_window.h"

#include "src/automated_widgets.hpp"
#include "src/error_message.hpp"
#include "src/fractal_container.hpp"
#include "src/initparameters.hpp"
#include "src/ui_transaction.hpp"
#include "src/interface.hpp"
#include "qt_utils.h"
#include "src/my_ui_loader.h"
#include "src/render_window.hpp"
#include "src/global_data.hpp"
#include "src/perf_scope.hpp"
#include "src/write_log.hpp"

#include "formula/definition/all_fractal_list.hpp"

cTabFractal::cTabFractal(QWidget *parent)
		: QWidget(parent), cMyWidgetWithParams(), ui(new Ui::cTabFractal)
{
	ui->setupUi(this);
	automatedWidgets = new cAutomatedWidgets(this);
	// Don't connect signals here yet - widget names need to be updated first
	ConnectSignals();

	tabIndex = 0;

	// v7.6 — Larger fonts and widgets for mutation section
	QString mutationStyleSheet = QString(
		"QLabel, QComboBox, QCheckBox, MyDoubleSpinBox, MySpinBox, QGroupBox, QRadioButton { "
		"  font-size: 14px; "
		"} "
		"MyDoubleSpinBox, QDoubleSpinBox, QSpinBox, QComboBox { "
		"  min-height: 28px; "
		"  min-width: 120px; "
		"  padding: 2px 6px; "
		"} "
		"QGroupBox::title { "
		"  font-size: 15px; "
		"  font-weight: bold; "
		"} "
		"QLabel { "
		"  min-height: 22px; "
		"}");

	QList<QWidget *> allWidgets = findChildren<QWidget *>();
	for (QWidget *widget : allWidgets)
	{
		if (widget->objectName().contains("mutation"))
		{
			widget->setStyleSheet(mutationStyleSheet);
		}
	}
}

cTabFractal::~cTabFractal()
{
	delete ui;
}

void cTabFractal::InitWidgetNames() const
{
	QList<QWidget *> widgetList = findChildren<QWidget *>();

	for (auto widget : widgetList)
	{
		QString oldName = widget->objectName();
		if (oldName.size() > 0)
		{
			QString lastTwoLetters = oldName.right(2);
			QString newName;
			if (lastTwoLetters == "_x" || lastTwoLetters == "_y" || lastTwoLetters == "_z"
					|| lastTwoLetters == "_w")
			{
				newName =
					oldName.left(oldName.size() - 2) + "_" + QString::number(tabIndex + 1) + lastTwoLetters;
			}
			else
			{
				newName = oldName + "_" + QString::number(tabIndex + 1);
			}
			widget->setObjectName(newName);
		}
	}
}

void cTabFractal::Init(bool firstTab, int _tabIndex)
{
	tabIndex = _tabIndex;

	InitWidgetNames();
	
	// Connect signals after widget names have been updated with correct tab index
	automatedWidgets->ConnectSignalsForSlidersInWindow(this);

	// set headings and separator of formulas and transforms
	QFont fontHeading;
	fontHeading.setBold(true);
	QList<QPair<int, QString> /* */> insertHeader;
	insertHeader << QPair<int, QString>(
		fractal::aexion, QObject::tr("*** Formulas with analytic DE ***"));
	insertHeader << QPair<int, QString>(fractal::aexion, QObject::tr("Logarithmic DE"));
	insertHeader << QPair<int, QString>(fractal::aboxMod1, QObject::tr("Linear DE"));
	insertHeader << QPair<int, QString>(fractal::josKleinian, QObject::tr("JosLeys-Kleinian DE"));
	insertHeader << QPair<int, QString>(fractal::pseudoKleinian, QObject::tr("Pseudo Kleinian DE"));
	insertHeader << QPair<int, QString>(
		fractal::dIFSAmazingIfs, QObject::tr("Custom DE - dIFS Formulas"));
	insertHeader << QPair<int, QString>(
		fractal::transfDIFSAmazingIfs, QObject::tr("Custom DE - dIFS Transforms"));
	insertHeader << QPair<int, QString>(
		fractal::foldCutCube, QObject::tr("Custom DE - non-dIFS formulas"));

	insertHeader << QPair<int, QString>(
		fractal::aexionOctopusMod, QObject::tr("*** Formulas with delta-DE ***"));
	insertHeader << QPair<int, QString>(
		fractal::aexionOctopusMod, QObject::tr("Logarithmic delta-DE"));
	insertHeader << QPair<int, QString>(fractal::boxFoldBulbPow2, QObject::tr("Linear delta-DE"));

	insertHeader << QPair<int, QString>(
		fractal::transfAbsAddConditional, QObject::tr("*** Transforms ***"));

	insertHeader << QPair<int, QString>(
		fractal::transfHybridColor, QObject::tr("*** Hybrid coloring ***"));
	insertHeader << QPair<int, QString>(
		fractal::testing, QObject::tr("*** Experimental Do Not Use***"));

	ui->comboBox_formula->populateItemsFromFractalList(
		newFractalList, insertHeader, params->Get<int>("ui_colorize_random_seed"));

	connect(ui->comboBox_formula, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
		&cTabFractal::slotChangedComboFractal);
	connect(ui->pushButton_reset_formula, &QPushButton::clicked, this,
		&cTabFractal::slotPressedButtonResetFormula);

	FrameIterationFormulaSetWidgetsVisibility(false);

	ui->checkBox_dont_add_c_constant->setText(QObject::tr("Don't add global C constant"));

	if (!firstTab)
	{
		ui->frame_iterations_formula->setEnabled(false);
	}

	EnsureFormulaWidgetMatchesParams(false);

	ui->groupBox_formula_transform->setVisible(false);
	ui->groupBox_c_constant_addition->setVisible(false);
	ui->groupBox_material_fractal->setVisible(false);
}

void cTabFractal::ClearFormulaLayout()
{
	QVBoxLayout *layout = ui->verticalLayout_fractal;
	while (layout->count() > 0)
	{
		QLayoutItem *item = layout->takeAt(0);
		if (item->widget()) item->widget()->hide();
		delete item;
	}
	activeFractalWidget = nullptr;
	activeFormulaListIndex = -1;
}

QWidget *cTabFractal::GetOrCreateFormulaWidget(const QString &cacheKey, const QString &formulaName,
	const QString &uiFilename, const int fractalListIndex, bool *created)
{
	if (formulaWidgetCache.contains(cacheKey))
	{
		*created = false;
		return formulaWidgetCache.value(cacheKey);
	}

	QWidget *widgetPtr = nullptr;
	if (formulaName == "custom")
	{
		auto *editor = new cCustomFormulaEditor(this);
		editor->AssignSlot(tabIndex);
		widgetPtr = editor;
	}
	else
	{
		MyUiLoader loader;
		QFile uiFile(uiFilename);
		if (!uiFile.exists()) return nullptr;

		uiFile.open(QFile::ReadOnly);
		widgetPtr = loader.load(&uiFile, this);
		uiFile.close();
	}

	if (!widgetPtr) return nullptr;

	widgetPtr->hide();
	formulaWidgetCache.insert(cacheKey, widgetPtr);
	ConnectFormulaWidgetSignals(widgetPtr, fractalListIndex);
	*created = true;
	return widgetPtr;
}

void cTabFractal::ConnectFormulaWidgetSignals(QWidget *widget, const int fractalListIndex)
{
	if (!widget) return;

	const QString cacheKey = newFractalList[fractalListIndex]->getInternalName();
	if (formulaWidgetsConnected.contains(cacheKey)) return;

	automatedWidgets->ConnectSignalsForSlidersInWindow(widget);

	if (newFractalList[fractalListIndex]->getInternalId() == fractal::kaleidoscopicIfs)
	{
		if (QPushButton *pushButton = widget->findChild<QPushButton *>("pushButton_preset_dodecahedron"))
			QApplication::connect(pushButton, &QPushButton::clicked, this,
				&cTabFractal::slotPressedButtonIFSDefaultsDodecahedron);
		if (QPushButton *pushButton = widget->findChild<QPushButton *>("pushButton_preset_icosahedron"))
			QApplication::connect(pushButton, &QPushButton::clicked, this,
				&cTabFractal::slotPressedButtonIFSDefaultsIcosahedron);
		if (QPushButton *pushButton = widget->findChild<QPushButton *>("pushButton_preset_octahedron"))
			QApplication::connect(pushButton, &QPushButton::clicked, this,
				&cTabFractal::slotPressedButtonIFSDefaultsOctahedron);
		if (QPushButton *pushButton = widget->findChild<QPushButton *>("pushButton_preset_menger_sponge"))
			QApplication::connect(pushButton, &QPushButton::clicked, this,
				&cTabFractal::slotPressedButtonIFSDefaultsMengerSponge);
		if (QPushButton *pushButton = widget->findChild<QPushButton *>("pushButton_preset_reset"))
			QApplication::connect(pushButton, &QPushButton::clicked, this,
				&cTabFractal::slotPressedButtonIFSDefaultsReset);
	}

	formulaWidgetsConnected.insert(cacheKey);
}

void cTabFractal::ShowFormulaWidget(QWidget *widget, const int fractalListIndex)
{
	if (!widget) return;

	setUpdatesEnabled(false);
	ClearFormulaLayout();

	ui->verticalLayout_fractal->addWidget(widget);

	if (params->Get<bool>("ui_colorize"))
		cInterface::ColorizeGroupBoxes(widget, params->Get<int>("ui_colorize_random_seed"));
	cInterface::AdjustLayoutSpacing(widget, gPar->Get<int>("ui_layout_spacing"));

	widget->show();
	SynchronizeInterfaceWindow(widget, fractalParams->at(tabIndex), qInterface::write);
	activeFractalWidget = widget;
	activeFormulaListIndex = fractalListIndex;
	setUpdatesEnabled(true);
	update();

	switch (newFractalList[fractalListIndex]->getCpixelAddition())
	{
		case fractal::cpixelEnabledByDefault:
			ui->checkBox_dont_add_c_constant->setText(QObject::tr("Don't add global C constant"));
			ui->checkBox_dont_add_c_constant->setEnabled(true);
			break;

		case fractal::cpixelDisabledByDefault:
			ui->checkBox_dont_add_c_constant->setText(QObject::tr("Add global C constant"));
			ui->checkBox_dont_add_c_constant->setEnabled(true);
			break;

		case fractal::cpixelAlreadyHas:
			ui->checkBox_dont_add_c_constant->setText(QObject::tr("Don't add global C constant"));
			ui->checkBox_dont_add_c_constant->setEnabled(false);
			break;

		case fractal::cpixelUndefined:
			ui->checkBox_dont_add_c_constant->setText(QObject::tr("Don't add global C constant"));
			ui->checkBox_dont_add_c_constant->setEnabled(false);
			break;
	}

	const fractal::enumCPixelAddition cPixelAddition = newFractalList[fractalListIndex]->getCpixelAddition();
	if (cPixelAddition == fractal::cpixelAlreadyHas)
		CConstantAdditionSetVisible(false);
	else if (parentDockFractal)
		CConstantAdditionSetVisible(parentDockFractal->AreBooleanFractalsEnabled());
}

void cTabFractal::ApplyFormulaListIndex(const int fractalListIndex, const bool requestRender)
{
	PERF_SCOPE("Formula.Switch.UiRebuild");

	if (fractalListIndex < 0 || fractalListIndex >= newFractalList.size()) return;

	if (params)
	{
		params->Set(QString("formula_%1").arg(tabIndex + 1),
			int(newFractalList[fractalListIndex]->getInternalId()));
	}

	cUiTransaction tx(QObject::tr("formula changed"));
	const QString fullFormulaName = newFractalList[fractalListIndex]->getNameInComboBox();

	if (newFractalList[fractalListIndex]->getInternalId() > 0)
	{
		const QString formulaName = newFractalList[fractalListIndex]->getInternalName();
		const QString uiFilename = newFractalList[fractalListIndex]->getUiFilename();

		bool created = false;
		QWidget *widget =
			GetOrCreateFormulaWidget(formulaName, formulaName, uiFilename, fractalListIndex, &created);
		if (widget)
		{
			ShowFormulaWidget(widget, fractalListIndex);
		}
		else
		{
			cErrorMessage::showMessage(
				QString("Can't open file ") + uiFilename + QString("\nFractal ui file can't be loaded"),
				cErrorMessage::errorMessage, gMainInterface->mainWindow);
		}
	}
	else
	{
		setUpdatesEnabled(false);
		ClearFormulaLayout();
		activeFractalWidget = nullptr;
		activeFormulaListIndex = -1;
		setUpdatesEnabled(true);
		update();
	}

	if (parentDockFractal)
	{
		parentDockFractal->SetTabText(
			tabIndex, QString("#%1: %2").arg(tabIndex + 1).arg(fullFormulaName));
	}

	emit signalFormulaChanged(fractalListIndex);

	if (requestRender && gMainInterface && newFractalList[fractalListIndex]->getInternalId() > 0)
	{
		tx.MarkParamsDirty();
		tx.RequestRender(0);
	}
}

void cTabFractal::EnsureFormulaWidgetMatchesParams(const bool requestRender)
{
	if (!params) return;

	const int comboListIndex = GetCurrentFractalIndexOnList();
	int wantedInternalId = params->Get<int>(QString("formula_%1").arg(tabIndex + 1));

	// Combo may already reflect a user change while params are still stale (read sync is deferred).
	if (comboListIndex >= 0 && comboListIndex < newFractalList.size()
			&& newFractalList[comboListIndex]->getInternalId() != wantedInternalId
			&& activeFormulaListIndex == comboListIndex)
	{
		wantedInternalId = int(newFractalList[comboListIndex]->getInternalId());
		params->Set(QString("formula_%1").arg(tabIndex + 1), wantedInternalId);
	}

	int wantedListIndex = -1;
	for (int i = 0; i < newFractalList.size(); i++)
	{
		if (newFractalList[i]->getInternalId() == wantedInternalId)
		{
			wantedListIndex = i;
			break;
		}
	}

	if (wantedListIndex < 0 || newFractalList[wantedListIndex]->getInternalId() <= 0)
	{
		if (activeFractalWidget)
		{
			setUpdatesEnabled(false);
			ClearFormulaLayout();
			activeFractalWidget = nullptr;
			activeFormulaListIndex = -1;
			setUpdatesEnabled(true);
			update();
		}
		if (parentDockFractal)
			parentDockFractal->SetTabText(tabIndex, QString("#%1: None").arg(tabIndex + 1));
		return;
	}

	const int comboIndex = ui->comboBox_formula->findData(wantedListIndex);
	if (comboIndex < 0) return;

	if (ui->comboBox_formula->currentIndex() != comboIndex)
	{
		QSignalBlocker blocker(ui->comboBox_formula);
		ui->comboBox_formula->setCurrentIndex(comboIndex);
	}

	if (activeFormulaListIndex == wantedListIndex && activeFractalWidget)
	{
		if (parentDockFractal)
		{
			parentDockFractal->SetTabText(tabIndex,
				QString("#%1: %2").arg(tabIndex + 1)
					.arg(newFractalList[wantedListIndex]->getNameInComboBox()));
		}
		if (fractalParams)
		{
			SynchronizeInterfaceWindow(
				activeFractalWidget, fractalParams->at(tabIndex), qInterface::write);
		}
		return;
	}

	ApplyFormulaListIndex(wantedListIndex, requestRender);
}

void cTabFractal::slotChangedComboFractal(int indexInComboBox)
{
	const QComboBox *combo = qobject_cast<QComboBox *>(sender());
	if (!combo) return;

	const int index = combo->itemData(indexInComboBox).toInt();
	ApplyFormulaListIndex(index, true);
}

void cTabFractal::FormulaTransformSetVisible(bool visible) const
{
	ui->groupBox_formula_transform->setVisible(visible);
}

int cTabFractal::GetCurrentFractalIndexOnList() const
{
	return ui->comboBox_formula->itemData(ui->comboBox_formula->currentIndex()).toInt();
}

void cTabFractal::CConstantAdditionSetVisible(bool visible) const
{
	ui->groupBox_c_constant_addition->setVisible(visible);
}

void cTabFractal::CalculationParametersSetVisible(bool visible) const
{
	ui->groupBox_calculation_parameters->setVisible(visible);
}

void cTabFractal::SynchronizeInterface(
	std::shared_ptr<cParameterContainer> par, qInterface::enumReadWrite mode) const
{
	WriteLog("cTabFractal::SynchronizeInterface: frame_iterations_formula", 3);
	SynchronizeInterfaceWindow(ui->frame_iterations_formula, par, mode);

	WriteLog("cTabFractal::SynchronizeInterface: groupBox_formula_transform", 3);
	SynchronizeInterfaceWindow(ui->groupBox_formula_transform, par, mode);

	WriteLog("cTabFractal::SynchronizeInterface: groupBox_c_constant_addition", 3);
	SynchronizeInterfaceWindow(ui->groupBox_c_constant_addition, par, mode);

	WriteLog("cTabFractal::SynchronizeInterface: groupBox_material_fractal", 3);
	SynchronizeInterfaceWindow(ui->groupBox_material_fractal, par, mode);

	WriteLog("cTabFractal::SynchronizeInterface: groupBox_material_fractal", 3);
	SynchronizeInterfaceWindow(ui->groupBox_calculation_parameters, par, mode);

	WriteLog("cTabFractal::SynchronizeInterface: groupBox_advanced_weight", 3);
	SynchronizeInterfaceWindow(ui->groupBox_advanced_weight, par, mode);


}

void cTabFractal::FrameIterationFormulaSetWidgetsVisibility(bool visible) const
{
	ui->label_formula_iterations->setVisible(visible);
	ui->spinboxInt_formula_iterations->setVisible(visible);
	ui->label_formula_weight->setVisible(visible);
	ui->spinbox_formula_weight->setVisible(visible);
	ui->label_formula_start_iteration->setVisible(visible);
	ui->label_formula_stop_iteration->setVisible(visible);
	ui->spinboxInt_formula_start_iteration->setVisible(visible);
	ui->spinboxInt_formula_stop_iteration->setVisible(visible);
	ui->checkBox_check_for_bailout->setVisible(visible);
	ui->groupBox_advanced_weight->setVisible(visible);
	// Formula Mutation is always visible (works in single formula mode too)
}

void cTabFractal::ConnectSignals()
{
	connect(
		ui->pushButton_local_navi, &QPushButton::clicked, this, &cTabFractal::slotPressedButtonNavi);

	// Connect weight mode combo box to dynamic visibility
	connect(ui->comboBox_weight_mode, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
		&cTabFractal::slotChangedWeightMode);
	connect(ui->checkBox_weight_separate_components, &QCheckBox::stateChanged, this,
		&cTabFractal::slotChangedSeparateComponents);


	// Set initial visibility (mode 0 = Static)
	UpdateWeightWidgetsVisibility(0, false);
}

void cTabFractal::slotChangedWeightMode(int mode)
{
	bool separateComponents = ui->checkBox_weight_separate_components->isChecked();
	UpdateWeightWidgetsVisibility(mode, separateComponents);
}

void cTabFractal::slotChangedSeparateComponents(int state)
{
	int mode = ui->comboBox_weight_mode->currentIndex();
	UpdateWeightWidgetsVisibility(mode, state != 0);
}

void cTabFractal::UpdateWeightWidgetsVisibility(int mode, bool separateComponents) const
{
	// Static params (mode 0)
	bool showStatic = (mode == 0);
	ui->label_weight_static->setVisible(showStatic);
	ui->spinbox_weight_static->setVisible(showStatic);

	// Iteration params (mode 1)
	bool showIter = (mode == 1);
	ui->label_weight_iter_start->setVisible(showIter);
	ui->spinboxInt_weight_iter_start->setVisible(showIter);
	ui->label_weight_iter_end->setVisible(showIter);
	ui->spinboxInt_weight_iter_end->setVisible(showIter);
	ui->label_weight_start->setVisible(showIter);
	ui->spinbox_weight_start->setVisible(showIter);
	ui->label_weight_end->setVisible(showIter);
	ui->spinbox_weight_end->setVisible(showIter);
	ui->label_weight_blend_mode->setVisible(showIter);
	ui->comboBox_weight_blend_mode->setVisible(showIter);

	// DE params (mode 2)
	bool showDE = (mode == 2);
	ui->label_weight_de_base->setVisible(showDE);
	ui->spinbox_weight_de_base->setVisible(showDE);
	ui->label_weight_de_sensitivity->setVisible(showDE);
	ui->spinbox_weight_de_sensitivity->setVisible(showDE);
	ui->label_weight_de_threshold->setVisible(showDE);
	ui->spinbox_weight_de_threshold->setVisible(showDE);
	ui->label_weight_de_mod_type->setVisible(showDE);
	ui->comboBox_weight_de_mod_type->setVisible(showDE);

	// ZLength params (mode 3)
	bool showZLen = (mode == 3);
	ui->label_weight_zlength_base->setVisible(showZLen);
	ui->spinbox_weight_zlength_base->setVisible(showZLen);
	ui->label_weight_zlength_sens->setVisible(showZLen);
	ui->spinbox_weight_zlength_sens->setVisible(showZLen);
	ui->label_weight_zlength_threshold->setVisible(showZLen);
	ui->spinbox_weight_zlength_threshold->setVisible(showZLen);
	ui->label_weight_zlength_mod_type->setVisible(showZLen);
	ui->comboBox_weight_zlength_mod_type->setVisible(showZLen);

	// Conditional params (mode 4)
	bool showCond = (mode == 4);
	ui->label_weight_condition_type->setVisible(showCond);
	ui->comboBox_weight_condition_type->setVisible(showCond);
	ui->label_weight_condition_threshold->setVisible(showCond);
	ui->spinbox_weight_condition_threshold->setVisible(showCond);
	ui->label_weight_true->setVisible(showCond);
	ui->spinbox_weight_true->setVisible(showCond);
	ui->label_weight_false->setVisible(showCond);
	ui->spinbox_weight_false->setVisible(showCond);
	ui->label_weight_condition_blend->setVisible(showCond);
	ui->comboBox_weight_condition_blend->setVisible(showCond);

	// OrbitTrap params (mode 5)
	bool showOrbit = (mode == 5);
	ui->label_weight_orbit_trap_base->setVisible(showOrbit);
	ui->spinbox_weight_orbit_trap_base->setVisible(showOrbit);
	ui->label_weight_orbit_trap_sensitivity->setVisible(showOrbit);
	ui->spinbox_weight_orbit_trap_sensitivity->setVisible(showOrbit);
	ui->label_weight_orbit_trap_threshold->setVisible(showOrbit);
	ui->spinbox_weight_orbit_trap_threshold->setVisible(showOrbit);
	ui->label_weight_orbit_trap_mod_type->setVisible(showOrbit);
	ui->comboBox_weight_orbit_trap_mod_type->setVisible(showOrbit);

	// Curve params (mode 6)
	bool showCurve = (mode == 6);
	ui->label_weight_curve_base->setVisible(showCurve);
	ui->spinbox_weight_curve_base->setVisible(showCurve);
	ui->label_weight_curve_sensitivity->setVisible(showCurve);
	ui->spinbox_weight_curve_sensitivity->setVisible(showCurve);
	ui->label_weight_curve_power->setVisible(showCurve);
	ui->spinbox_weight_curve_power->setVisible(showCurve);
	ui->label_weight_curve_mod_type->setVisible(showCurve);
	ui->comboBox_weight_curve_mod_type->setVisible(showCurve);

	// DE Ratio params (mode 8)
	bool showDERatio = (mode == 8);
	ui->label_weight_de_ratio_scale->setVisible(showDERatio);
	ui->spinbox_weight_de_ratio_scale->setVisible(showDERatio);
	ui->label_weight_de_ratio_offset->setVisible(showDERatio);
	ui->spinbox_weight_de_ratio_offset->setVisible(showDERatio);
	ui->label_weight_de_ratio_mod_type->setVisible(showDERatio);
	ui->comboBox_weight_de_ratio_mod_type->setVisible(showDERatio);

	// Adaptive params (mode 9)
	bool showAdaptive = (mode == 9);
	ui->label_weight_adaptive_strength->setVisible(showAdaptive);
	ui->spinbox_weight_adaptive_strength->setVisible(showAdaptive);

	// Fine-tuning params — always visible when advanced weight is active (mode > 0)
	bool showFineTuning = (mode > 0);
	ui->label_weight_floor->setVisible(showFineTuning);
	ui->spinbox_weight_floor->setVisible(showFineTuning);
	ui->label_weight_ceiling->setVisible(showFineTuning);
	ui->spinbox_weight_ceiling->setVisible(showFineTuning);
	ui->label_weight_gamma->setVisible(showFineTuning);
	ui->spinbox_weight_gamma->setVisible(showFineTuning);
	ui->checkBox_weight_invert->setVisible(showFineTuning);
	ui->label_weight_fade_in->setVisible(showFineTuning);
	ui->spinboxInt_weight_fade_in->setVisible(showFineTuning);
	ui->label_weight_fade_out->setVisible(showFineTuning);
	ui->spinboxInt_weight_fade_out->setVisible(showFineTuning);
	// DE Smooth Radius: only visible in DE-based modes (2, 5, 6, 8)
	bool showDESmooth = (mode == 2 || mode == 5 || mode == 6 || mode == 8);
	ui->label_weight_de_smooth_radius->setVisible(showDESmooth);
	ui->spinbox_weight_de_smooth_radius->setVisible(showDESmooth);
	// Blend curve: always visible when weight active
	ui->label_weight_component_blend_curve->setVisible(showFineTuning);
	ui->spinbox_weight_component_blend_curve->setVisible(showFineTuning);

	// Separate components — always visible
	// Sub-params only visible when checkbox is checked
	ui->label_weight_z_vector->setVisible(separateComponents);
	ui->spinbox_weight_z_vector->setVisible(separateComponents);
	ui->label_weight_de_component->setVisible(separateComponents);
	ui->spinbox_weight_de_component->setVisible(separateComponents);
	ui->label_weight_dist_component->setVisible(separateComponents);
	ui->spinbox_weight_dist_component->setVisible(separateComponents);
	ui->label_weight_color_component->setVisible(separateComponents);
	ui->spinbox_weight_color_component->setVisible(separateComponents);
}

void cTabFractal::MaterialSetVisible(bool visible) const
{
	ui->groupBox_material_fractal->setVisible(visible);
}




void cTabFractal::FrameIterationFormulaSetEnabled(bool enabled) const
{
	ui->frame_iterations_formula->setEnabled(enabled);
}

void cTabFractal::SynchronizeFractal(
	std::shared_ptr<cParameterContainer> fractal, qInterface::enumReadWrite mode) const
{
	if (activeFractalWidget)
	{
		SynchronizeInterfaceWindow(activeFractalWidget, fractal, mode);
	}
}

void cTabFractal::slotPressedButtonIFSDefaultsDodecahedron() const
{
	CHECK_MAIN_INTERFACE();
	SynchronizeInterfaceWindow(activeFractalWidget, fractalParams->at(tabIndex), qInterface::read);
	gMainInterface->IFSDefaultsDodecahedron(fractalParams->at(tabIndex));
	SynchronizeInterfaceWindow(activeFractalWidget, fractalParams->at(tabIndex), qInterface::write);
}

void cTabFractal::slotPressedButtonIFSDefaultsIcosahedron() const
{
	CHECK_MAIN_INTERFACE();
	SynchronizeInterfaceWindow(activeFractalWidget, fractalParams->at(tabIndex), qInterface::read);
	gMainInterface->IFSDefaultsIcosahedron(fractalParams->at(tabIndex));
	SynchronizeInterfaceWindow(activeFractalWidget, fractalParams->at(tabIndex), qInterface::write);
}

void cTabFractal::slotPressedButtonIFSDefaultsOctahedron() const
{
	CHECK_MAIN_INTERFACE();
	SynchronizeInterfaceWindow(activeFractalWidget, fractalParams->at(tabIndex), qInterface::read);
	gMainInterface->IFSDefaultsOctahedron(fractalParams->at(tabIndex));
	SynchronizeInterfaceWindow(activeFractalWidget, fractalParams->at(tabIndex), qInterface::write);
}

void cTabFractal::slotPressedButtonIFSDefaultsMengerSponge() const
{
	CHECK_MAIN_INTERFACE();
	SynchronizeInterfaceWindow(activeFractalWidget, fractalParams->at(tabIndex), qInterface::read);
	gMainInterface->IFSDefaultsMengerSponge(fractalParams->at(tabIndex));
	SynchronizeInterfaceWindow(activeFractalWidget, fractalParams->at(tabIndex), qInterface::write);
}

void cTabFractal::slotPressedButtonIFSDefaultsReset() const
{
	CHECK_MAIN_INTERFACE();
	SynchronizeInterfaceWindow(activeFractalWidget, fractalParams->at(tabIndex), qInterface::read);
	gMainInterface->IFSDefaultsReset(fractalParams->at(tabIndex));
	SynchronizeInterfaceWindow(activeFractalWidget, fractalParams->at(tabIndex), qInterface::write);
}

void cTabFractal::slotPressedButtonResetFormula() const
{
	CHECK_MAIN_INTERFACE();
	gMainInterface->ResetFormula(tabIndex);
}


void cTabFractal::slotPressedButtonNavi()
{
	CHECK_MAIN_INTERFACE();
	gMainInterface->SynchronizeInterface(params, fractalParams, qInterface::read);
	cNavigatorWindow *navigator = new cNavigatorWindow();
	cTabFractal *leftWidget = new cTabFractal();
	navigator->AddLeftWidget(leftWidget);
	navigator->setAttribute(Qt::WA_DeleteOnClose);
	navigator->SetInitialParameters(params, fractalParams);
	leftWidget->Init(true, tabIndex);
	navigator->SynchronizeInterface(qInterface::write);
	navigator->SetMouseClickFunction(gMainInterface->GetMouseClickFunction());
	navigator->show();
	navigator->AllPrepared();
}
