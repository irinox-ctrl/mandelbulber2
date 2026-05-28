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

#include "ui_tab_fractal.h"

#include "custom_formula_editor.h"
#include "dock_fractal.h"
#include "navigator_window.h"

#include "src/automated_widgets.hpp"
#include "src/error_message.hpp"
#include "src/fractal_container.hpp"
#include "src/initparameters.hpp"
#include "src/interface.hpp"
#include "src/my_ui_loader.h"
#include "src/render_window.hpp"
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

	// Direct parameter update for mutation type comboboxes
	// (plain QComboBox does not auto-update parameters on interaction)
	auto connectMutationCombo = [&](QComboBox *combo, const QString &paramBase) {
		if (!combo || !params) return;
		QString paramName = paramBase + "_" + QString::number(tabIndex + 1);
		connect(combo, QOverload<int>::of(&QComboBox::currentIndexChanged),
			[=](int index) {
				if (params) params->Set(paramName, index);
			});
	};

	connectMutationCombo(ui->comboBox_mutation_inv_type, "mutation_inv_type");
	connectMutationCombo(ui->comboBox_mutation_clip_type, "mutation_clip_type");
	connectMutationCombo(ui->comboBox_mutation_jos_de_type, "mutation_jos_de_type");
	connectMutationCombo(ui->comboBox_mutation_pk_de_type, "mutation_pk_de_type");
	connectMutationCombo(ui->comboBox_mutation_mb_math_type, "mutation_mb_math_type");
	connectMutationCombo(ui->comboBox_mutation_warp_dist_type, "mutation_warp_dist_type");
	connectMutationCombo(ui->comboBox_mutation_sym_kal_type, "mutation_sym_kal_type");
	connectMutationCombo(ui->comboBox_mutation_abox_type, "mutation_abox_type");
	connectMutationCombo(ui->comboBox_mutation_noise_type, "mutation_noise_type");
	connectMutationCombo(ui->comboBox_mutation_orbit_trap_type, "mutation_orbit_trap_type");
	connectMutationCombo(ui->comboBox_mutation_torus_type, "mutation_torus_type");

	// v7.6 — Gray out mutation parameters that have no effect
	QList<QComboBox *> mutationTypeCombos = {
		ui->comboBox_mutation_inv_type,
		ui->comboBox_mutation_clip_type,
		ui->comboBox_mutation_jos_de_type,
		ui->comboBox_mutation_pk_de_type,
		ui->comboBox_mutation_mb_math_type,
		ui->comboBox_mutation_warp_dist_type,
		ui->comboBox_mutation_sym_kal_type,
		ui->comboBox_mutation_abox_type,
		ui->comboBox_mutation_noise_type,
		ui->comboBox_mutation_orbit_trap_type,
		ui->comboBox_mutation_torus_type,
		ui->comboBox_mutation_fold_type,
		ui->comboBox_mutation_warp_type,
		ui->comboBox_mutation_math_type,
	};
	for (QComboBox *combo : mutationTypeCombos)
	{
		if (combo) connect(combo, QOverload<int>::of(&QComboBox::currentIndexChanged),
			this, &cTabFractal::UpdateMutationGrayOut);
	}

	QList<QGroupBox *> mutationGroups = {
		ui->groupCheck_mutation_enabled,
		ui->groupCheck_mutation_inversion_enabled,
		ui->groupCheck_mutation_clip_enabled,
		ui->groupCheck_mutation_jos_leys_enabled,
		ui->groupCheck_mutation_pk_enabled,
		ui->groupCheck_mutation_mb_math_enabled,
		ui->groupCheck_mutation_warp_dist_enabled,
		ui->groupCheck_mutation_symmetry_enabled,
		ui->groupCheck_mutation_abox_enabled,
		ui->groupCheck_mutation_noise_enabled,
		ui->groupCheck_mutation_orbit_trap_enabled,
		ui->groupCheck_mutation_torus_enabled,
	};
	for (QGroupBox *group : mutationGroups)
	{
		if (group) connect(group, &QGroupBox::toggled, this, &cTabFractal::UpdateMutationGrayOut);
	}

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

	connect(ui->comboBox_formula, SIGNAL(currentIndexChanged(int)), this,
		SLOT(slotChangedComboFractal(int)));
	connect(
		ui->pushButton_reset_formula, SIGNAL(clicked()), this, SLOT(slotPressedButtonResetFormula()));

	FrameIterationFormulaSetWidgetsVisibility(false);

	ui->checkBox_dont_add_c_constant->setText(QObject::tr("Don't add global C constant"));

	if (!firstTab)
	{
		ui->frame_iterations_formula->setEnabled(false);
	}

	ui->groupBox_formula_transform->setVisible(false);
	ui->groupBox_c_constant_addition->setVisible(false);
	ui->groupBox_material_fractal->setVisible(false);
}

void cTabFractal::slotChangedComboFractal(int indexInComboBox)
{
	QString comboName = sender()->objectName();
	int index = qobject_cast<QComboBox *>(sender())->itemData(indexInComboBox).toInt();

	QString fullFormulaName = newFractalList[index]->getNameInComboBox();
	if (newFractalList[index]->getInternalId() > 0)
	{
		QString formulaName = newFractalList[index]->getInternalName();
		QString uiFilename = newFractalList[index]->getUiFilename();

		bool widgetLoaded = false;

		if (formulaName == "custom")
		{
			fractalWidget.reset(new cCustomFormulaEditor());
			dynamic_cast<cCustomFormulaEditor *>(fractalWidget.get())->AssignSlot(tabIndex);
			widgetLoaded = true;
		}
		else
		{
			MyUiLoader loader;
			QFile uiFile(uiFilename);

			if (uiFile.exists())
			{
				uiFile.open(QFile::ReadOnly);
				fractalWidget.reset(loader.load(&uiFile));

				uiFile.close();
				widgetLoaded = true;
			}
		}

		if (widgetLoaded)
		{
			QVBoxLayout *layout = ui->verticalLayout_fractal;
			
			// Remove any existing widget from the layout before adding the new one
			while (layout->count() > 0)
			{
				QLayoutItem *item = layout->takeAt(0);
				if (item->widget())
				{
					item->widget()->setParent(nullptr);
				}
				delete item;
			}
			
			layout->addWidget(fractalWidget.get());

			if (params->Get<bool>("ui_colorize"))
				cInterface::ColorizeGroupBoxes(
					fractalWidget.get(), params->Get<int>("ui_colorize_random_seed"));
			cInterface::AdjustLayoutSpacing(fractalWidget.get(), gPar->Get<int>("ui_layout_spacing"));

			fractalWidget->show();
			automatedWidgets->ConnectSignalsForSlidersInWindow(fractalWidget.get());
			SynchronizeInterfaceWindow(
				fractalWidget.get(), fractalParams->at(tabIndex), qInterface::write);

			switch (newFractalList[index]->getCpixelAddition())
			{
				case fractal::cpixelEnabledByDefault:
					ui->checkBox_dont_add_c_constant->setText(QObject::tr("Don't add global C constant"));
					ui->checkBox_dont_add_c_constant->setEnabled(true);
					break;

				case fractal::cpixelDisabledByDefault:
				{
					ui->checkBox_dont_add_c_constant->setText(QObject::tr("Add global C constant"));
					ui->checkBox_dont_add_c_constant->setEnabled(true);
					break;
				}

				case fractal::cpixelAlreadyHas:
				{
					ui->checkBox_dont_add_c_constant->setText(QObject::tr("Don't add global C constant"));
					ui->checkBox_dont_add_c_constant->setEnabled(false);
					break;
				}

				case fractal::cpixelUndefined:
				{
					ui->checkBox_dont_add_c_constant->setText(QObject::tr("Don't add global C constant"));
					ui->checkBox_dont_add_c_constant->setEnabled(false);
					break;
				}
			};

			fractal::enumCPixelAddition cPixelAddition = newFractalList[index]->getCpixelAddition();

			if (cPixelAddition == fractal::cpixelAlreadyHas)
				CConstantAdditionSetVisible(false);
			else
			{
				if (parentDockFractal)
				{
					bool booleanState = parentDockFractal->AreBooleanFractalsEnabled();
					CConstantAdditionSetVisible(booleanState);
				}
			}

			if (newFractalList[index]->getInternalId() == fractal::kaleidoscopicIfs)
			{
				QWidget *pushButton_preset_dodecahedron =
					fractalWidget->findChild<QWidget *>("pushButton_preset_dodecahedron");
				QApplication::connect(pushButton_preset_dodecahedron, SIGNAL(clicked()), this,
					SLOT(slotPressedButtonIFSDefaultsDodecahedron()));
				QWidget *pushButton_preset_icosahedron =
					fractalWidget->findChild<QWidget *>("pushButton_preset_icosahedron");
				QApplication::connect(pushButton_preset_icosahedron, SIGNAL(clicked()), this,
					SLOT(slotPressedButtonIFSDefaultsIcosahedron()));
				QWidget *pushButton_preset_octahedron =
					fractalWidget->findChild<QWidget *>("pushButton_preset_octahedron");
				QApplication::connect(pushButton_preset_octahedron, SIGNAL(clicked()), this,
					SLOT(slotPressedButtonIFSDefaultsOctahedron()));
				QWidget *pushButton_preset_menger_sponge =
					fractalWidget->findChild<QWidget *>("pushButton_preset_menger_sponge");
				QApplication::connect(pushButton_preset_menger_sponge, SIGNAL(clicked()), this,
					SLOT(slotPressedButtonIFSDefaultsMengerSponge()));
				QWidget *pushButton_preset_reset =
					fractalWidget->findChild<QWidget *>("pushButton_preset_reset");
				QApplication::connect(pushButton_preset_reset, SIGNAL(clicked()), this,
					SLOT(slotPressedButtonIFSDefaultsReset()));
			}
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
		fractalWidget.reset();
	}

	if (parentDockFractal)
	{
		parentDockFractal->SetTabText(
			tabIndex, QString("#%1: %2").arg(tabIndex + 1).arg(fullFormulaName));
	}

	UpdateMutationFieldVisibility(index);
	UpdateMutationGrayOut();
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

	WriteLog("cTabFractal::SynchronizeInterface: groupCheck_mutation_enabled", 3);
	// groupCheck's own checked state must be synced explicitly:
	// SynchronizeInterfaceWindow processes CHILDREN only, not the widget itself.
	{
		QString paramName = "mutation_enabled_" + QString::number(tabIndex + 1);

		if (mode == qInterface::read)
			par->Set(paramName, ui->groupCheck_mutation_enabled->isChecked());
		else
			ui->groupCheck_mutation_enabled->setChecked(par->Get<bool>(paramName));
	}
	SynchronizeInterfaceWindow(ui->groupCheck_mutation_enabled, par, mode);

	// Sync individual mutation system groupboxes
	auto syncMutationGroupbox = [&](const QString &paramBase, QGroupBox *groupbox) {
		QString paramName = paramBase + "_" + QString::number(tabIndex + 1);
		if (mode == qInterface::read)
			par->Set(paramName, groupbox->isChecked());
		else
			groupbox->setChecked(par->Get<bool>(paramName));
		SynchronizeInterfaceWindow(groupbox, par, mode);
	};

	WriteLog("cTabFractal::SynchronizeInterface: groupCheck_mutation_clip_enabled", 3);
	syncMutationGroupbox("mutation_clip_enabled", ui->groupCheck_mutation_clip_enabled);
	// Force clip groupbox to be visible
	ui->groupCheck_mutation_clip_enabled->setVisible(true);

	WriteLog("cTabFractal::SynchronizeInterface: groupCheck_mutation_inversion_enabled", 3);
	syncMutationGroupbox("mutation_inversion_enabled", ui->groupCheck_mutation_inversion_enabled);
	ui->groupCheck_mutation_inversion_enabled->setVisible(true);

	WriteLog("cTabFractal::SynchronizeInterface: groupCheck_mutation_jos_leys_enabled", 3);
	syncMutationGroupbox("mutation_jos_leys_enabled", ui->groupCheck_mutation_jos_leys_enabled);

	WriteLog("cTabFractal::SynchronizeInterface: groupCheck_mutation_pk_enabled", 3);
	syncMutationGroupbox("mutation_pk_enabled", ui->groupCheck_mutation_pk_enabled);

	WriteLog("cTabFractal::SynchronizeInterface: groupCheck_mutation_mb_math_enabled", 3);
	syncMutationGroupbox("mutation_mb_math_enabled", ui->groupCheck_mutation_mb_math_enabled);

	WriteLog("cTabFractal::SynchronizeInterface: groupCheck_mutation_warp_dist_enabled", 3);
	syncMutationGroupbox("mutation_warp_dist_enabled", ui->groupCheck_mutation_warp_dist_enabled);

	WriteLog("cTabFractal::SynchronizeInterface: groupCheck_mutation_symmetry_enabled", 3);
	syncMutationGroupbox("mutation_symmetry_enabled", ui->groupCheck_mutation_symmetry_enabled);

	WriteLog("cTabFractal::SynchronizeInterface: groupCheck_mutation_abox_enabled", 3);
	syncMutationGroupbox("mutation_abox_enabled", ui->groupCheck_mutation_abox_enabled);

	WriteLog("cTabFractal::SynchronizeInterface: groupCheck_mutation_noise_enabled", 3);
	syncMutationGroupbox("mutation_noise_enabled", ui->groupCheck_mutation_noise_enabled);

	WriteLog("cTabFractal::SynchronizeInterface: groupCheck_mutation_orbit_trap_enabled", 3);
	syncMutationGroupbox("mutation_orbit_trap_enabled", ui->groupCheck_mutation_orbit_trap_enabled);

	WriteLog("cTabFractal::SynchronizeInterface: groupCheck_mutation_torus_enabled", 3);
	syncMutationGroupbox("mutation_torus_enabled", ui->groupCheck_mutation_torus_enabled);

	// v7.6 — Update gray-out state for all mutation parameters
	UpdateMutationGrayOut();
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
	connect(ui->comboBox_weight_mode, SIGNAL(currentIndexChanged(int)), this,
		SLOT(slotChangedWeightMode(int)));
	connect(ui->checkBox_weight_separate_components, SIGNAL(stateChanged(int)), this,
		SLOT(slotChangedSeparateComponents(int)));

	// Mutation reset button
	connect(ui->pushButton_mutation_reset, &QPushButton::clicked, this,
		&cTabFractal::slotPressedButtonMutationReset);

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

void cTabFractal::SetMutationWidgetsEnabled(const QStringList &names, bool enabled) const
{
	for (const QString &name : names)
	{
		QWidget *w = ui->groupCheck_mutation_enabled->findChild<QWidget *>(name);
		if (w) w->setEnabled(enabled);
	}
}

void cTabFractal::UpdateMutationFieldVisibility(int formulaIndex) const
{
	if (formulaIndex <= 0 || formulaIndex >= newFractalList.size()) return;

	fractal::enumDEType deType = newFractalList[formulaIndex]->getDeType();
	fractal::enumCPixelAddition cPixel = newFractalList[formulaIndex]->getCpixelAddition();
	QString internalName = newFractalList[formulaIndex]->getInternalName();
	bool isTransform = internalName.startsWith("transf_");

	// DE tweak: only useful for analytic DE formulas
	bool hasDeTweak = (deType == fractal::analyticDEType);
	QString idx = "_" + QString::number(tabIndex + 1);
	QStringList deTweakWidgets = {
		"comboBox_mutation_de_tweak" + idx,
		"spinbox_mutation_de_scale" + idx,
		"spinbox_mutation_de_tweak_p1" + idx,
		"spinbox_mutation_de_tweak_p2" + idx,
		"label_mutation_de_tweak" + idx,
		"label_mutation_de_scale" + idx,
		"label_mutation_de_tweak_p1" + idx,
		"label_mutation_de_tweak_p2" + idx
	};
	SetMutationWidgetsEnabled(deTweakWidgets, hasDeTweak);

	// Julia injection: less useful for transforms and formulas that already handle c-pixel
	bool juliaUseful = !isTransform && (cPixel != fractal::cpixelAlreadyHas);
	QStringList juliaWidgets = {
		"comboBox_mutation_julia_injection" + idx,
		"comboBox_mutation_julia_start" + idx,
		"comboBox_mutation_julia_c_transform" + idx,
		"comboBox_mutation_julia_dynamic" + idx,
		"comboBox_mutation_julia_multi" + idx,
		"spinbox_mutation_julia_c_mul" + idx,
		"spinbox_mutation_julia_c_power" + idx,
		"spinbox_mutation_julia_c_radius" + idx,
		"spinbox_mutation_julia_pulse_freq" + idx,
		"spinbox_mutation_julia_absorb" + idx,
		"label_mutation_julia_injection" + idx,
		"label_mutation_julia_start" + idx,
		"label_mutation_julia_c_transform" + idx,
		"label_mutation_julia_dynamic" + idx,
		"label_mutation_julia_multi" + idx,
		"label_mutation_julia_c_mul" + idx,
		"label_mutation_julia_c_power" + idx,
		"label_mutation_julia_c_radius" + idx,
		"label_mutation_julia_pulse_freq" + idx,
		"label_mutation_julia_absorb" + idx
	};
	SetMutationWidgetsEnabled(juliaWidgets, juliaUseful);

	// Orbit trap: less useful for transforms
	QStringList orbitWidgets = {
		"comboBox_mutation_orbit_trap" + idx,
		"label_mutation_orbit_trap" + idx
	};
	SetMutationWidgetsEnabled(orbitWidgets, !isTransform);
}

void cTabFractal::UpdateMutationGrayOut() const
{
	// Helper: set enabled state AND orange color for active parameters
	auto styleWidget = [&](QWidget *w, bool enabled) {
		if (!w) return;
		w->setEnabled(enabled);
		if (enabled) {
			w->setStyleSheet("color: #FFA500;");
		} else {
			w->setStyleSheet("");
		}
	};

	// Helper for systems with their own GroupBox (simple on/off based on type==0)
	auto grayOutGroupSystem = [&](QComboBox *combo, QGroupBox *group) {
		if (!combo || !group) return;
		bool systemActive = group->isChecked() && combo->currentIndex() != 0;
		QList<QWidget *> children = group->findChildren<QWidget *>();
		for (QWidget *w : children)
		{
			if (w == combo || w == group) continue;
			styleWidget(w, systemActive);
		}
	};

	// Systems with their own GroupBox (simple on/off)
	// Note: Inversion and Clip are handled separately below with per-type gray-out
	grayOutGroupSystem(ui->comboBox_mutation_jos_de_type, ui->groupCheck_mutation_jos_leys_enabled);
	grayOutGroupSystem(ui->comboBox_mutation_pk_de_type, ui->groupCheck_mutation_pk_enabled);
	grayOutGroupSystem(ui->comboBox_mutation_mb_math_type, ui->groupCheck_mutation_mb_math_enabled);
	grayOutGroupSystem(ui->comboBox_mutation_warp_dist_type, ui->groupCheck_mutation_warp_dist_enabled);
	grayOutGroupSystem(ui->comboBox_mutation_sym_kal_type, ui->groupCheck_mutation_symmetry_enabled);
	grayOutGroupSystem(ui->comboBox_mutation_abox_type, ui->groupCheck_mutation_abox_enabled);
	grayOutGroupSystem(ui->comboBox_mutation_noise_type, ui->groupCheck_mutation_noise_enabled);
	grayOutGroupSystem(ui->comboBox_mutation_orbit_trap_type, ui->groupCheck_mutation_orbit_trap_enabled);
	grayOutGroupSystem(ui->comboBox_mutation_torus_type, ui->groupCheck_mutation_torus_enabled);

	// --- Clip System: per-type gray-out ---
	{
		QGroupBox *clipGroup = ui->groupCheck_mutation_clip_enabled;
		QComboBox *clipCombo = ui->comboBox_mutation_clip_type;
		if (clipGroup && clipCombo)
		{
			bool clipActive = clipGroup->isChecked() && clipCombo->currentIndex() != 0;
			int clipType = clipCombo->currentIndex();

			auto setClipWidget = [&](const QString &baseName, bool enabled) {
				QString suffix = "_" + QString::number(tabIndex + 1);
				QWidget *w = clipGroup->findChild<QWidget *>(baseName + suffix);
				styleWidget(w, clipActive && enabled);
			};

			// Always relevant for any active clip type
			setClipWidget("label_clip_center", true);
			setClipWidget("spinbox_mutation_clip_center_ax", true);
			setClipWidget("spinbox_mutation_clip_center_ay", true);
			setClipWidget("spinbox_mutation_clip_center_az", true);
			setClipWidget("label_clip_bool", true);
			setClipWidget("spinboxInt_mutation_clip_boolean_op", true);
			setClipWidget("label_clip_iter_start", true);
			setClipWidget("spinboxInt_mutation_clip_iter_start", true);
			setClipWidget("label_clip_iter_stop", true);
			setClipWidget("spinboxInt_mutation_clip_iter_stop", true);
			setClipWidget("label_clip_prerot_x", true);
			setClipWidget("label_clip_prerot_y", true);
			setClipWidget("label_clip_prerot_z", true);
			setClipWidget("spinbox_mutation_clip_pre_rot_ax", true);
			setClipWidget("spinbox_mutation_clip_pre_rot_ay", true);
			setClipWidget("spinbox_mutation_clip_pre_rot_az", true);

			// Per-type relevance
			bool needSize = (clipType == 1 || clipType == 5 || clipType == 7 || clipType == 11
							 || clipType == 12 || clipType == 13 || clipType == 14 || clipType == 15
							 || clipType == 16 || clipType == 17 || clipType == 18 || clipType == 19
							 || clipType == 22);
			setClipWidget("label_clip_size", needSize);
			setClipWidget("spinbox_mutation_clip_size_ax", needSize);
			setClipWidget("spinbox_mutation_clip_size_ay", needSize);
			setClipWidget("spinbox_mutation_clip_size_az", needSize);

			bool needRadius = (clipType == 2 || clipType == 3 || clipType == 11 || clipType == 12
							 || clipType == 13 || clipType == 14 || clipType == 15 || clipType == 16
							 || clipType == 17 || clipType == 18 || clipType == 19 || clipType == 20
							 || clipType == 21 || clipType == 25 || clipType == 26 || clipType == 27
							 || clipType == 28 || clipType == 29 || clipType == 30);
			setClipWidget("label_clip_radius", needRadius);
			setClipWidget("spinbox_mutation_clip_radius", needRadius);

			bool needMajorR = (clipType == 2);
			setClipWidget("label_clip_major_r", needMajorR);
			setClipWidget("spinbox_mutation_clip_major_radius", needMajorR);

			bool needAngle = (clipType == 4);
			setClipWidget("label_clip_angle", needAngle);
			setClipWidget("spinbox_mutation_clip_angle", needAngle);

			bool needFreq = (clipType == 9 || clipType == 26);
			setClipWidget("label_clip_freq", needFreq);
			setClipWidget("spinbox_mutation_clip_frequency", needFreq);

			bool needAmp = (clipType == 9 || clipType == 10 || clipType == 23 || clipType == 28
							|| clipType == 30);
			setClipWidget("label_clip_amp", needAmp);
			setClipWidget("spinbox_mutation_clip_amplitude", needAmp);

			bool needSmoothK = (clipType == 14 || clipType == 15);
			setClipWidget("label_clip_smooth", needSmoothK);
			setClipWidget("spinbox_mutation_clip_smooth_k", needSmoothK);

			bool needNPoints = (clipType == 31 || clipType == 33 || clipType == 34 || clipType == 35);
			setClipWidget("label_clip_npoints", needNPoints);
			setClipWidget("spinboxInt_mutation_clip_n_points", needNPoints);

			bool needParamA = (clipType == 6 || clipType == 8 || clipType == 20 || clipType == 24
							 || clipType == 27);
			setClipWidget("label_clip_param", needParamA);
			setClipWidget("spinbox_mutation_clip_param_a", needParamA);

			bool needParamB = (clipType == 8);
			setClipWidget("label_clip_param_b", needParamB);
			setClipWidget("spinbox_mutation_clip_param_b", needParamB);

			bool needParamC = false; // not used by any current type
			setClipWidget("label_clip_param_c", needParamC);
			setClipWidget("spinbox_mutation_clip_param_c", needParamC);

			bool needThreshold = false; // not used by any current type
			setClipWidget("label_clip_threshold", needThreshold);
			setClipWidget("spinbox_mutation_clip_threshold", needThreshold);
		}
	}

	// --- Inversion System: per-type gray-out ---
	{
		QGroupBox *invGroup = ui->groupCheck_mutation_inversion_enabled;
		QComboBox *invCombo = ui->comboBox_mutation_inv_type;
		if (invGroup && invCombo)
		{
			bool invActive = invGroup->isChecked() && invCombo->currentIndex() != 0;
			int invType = invCombo->currentIndex();

			auto setInvWidget = [&](const QString &baseName, bool enabled) {
				QString suffix = "_" + QString::number(tabIndex + 1);
				QWidget *w = invGroup->findChild<QWidget *>(baseName + suffix);
				styleWidget(w, invActive && enabled);
			};

			// Always relevant for any active inversion type
			setInvWidget("label_inv_center", true);
			setInvWidget("spinbox_mutation_inv_center_ax", true);
			setInvWidget("spinbox_mutation_inv_center_ay", true);
			setInvWidget("spinbox_mutation_inv_center_az", true);
			setInvWidget("label_inv_iter_start", true);
			setInvWidget("spinboxInt_mutation_inv_iter_start", true);
			setInvWidget("label_inv_iter_stop", true);
			setInvWidget("spinboxInt_mutation_inv_iter_stop", true);
			setInvWidget("label_inv_prerot_x", true);
			setInvWidget("label_inv_prerot_y", true);
			setInvWidget("label_inv_prerot_z", true);
			setInvWidget("spinbox_mutation_inv_pre_rot_ax", true);
			setInvWidget("spinbox_mutation_inv_pre_rot_ay", true);
			setInvWidget("spinbox_mutation_inv_pre_rot_az", true);

			// Per-type relevance
			bool needRadius = (invType >= 2 && invType <= 30);
			setInvWidget("label_inv_radius", needRadius);
			setInvWidget("spinbox_mutation_inv_radius", needRadius);

			bool needParamA = (invType == 1 || invType == 3 || invType == 4 || invType == 5
							 || invType == 7 || invType == 9 || invType == 10 || invType == 15
							 || invType == 16 || invType == 17 || invType == 18 || invType == 20
							 || invType == 23);
			setInvWidget("label_inv_param_a", needParamA);
			setInvWidget("spinbox_mutation_inv_param_a", needParamA);

			bool needParamB = (invType == 1 || invType == 4 || invType == 7 || invType == 18);
			setInvWidget("label_inv_param_b", needParamB);
			setInvWidget("spinbox_mutation_inv_param_b", needParamB);

			bool needParamC = (invType == 1 || invType == 4 || invType == 11 || invType == 18);
			setInvWidget("label_inv_param_c", needParamC);
			setInvWidget("spinbox_mutation_inv_param_c", needParamC);

			bool needAngle = (invType == 6);
			setInvWidget("label_inv_angle", needAngle);
			setInvWidget("spinbox_mutation_inv_angle", needAngle);

			bool needFreq = (invType == 8 || invType == 25 || invType == 26);
			setInvWidget("label_inv_freq", needFreq);
			setInvWidget("spinbox_mutation_inv_frequency", needFreq);

			bool needAmp = (invType == 22 || invType == 25 || invType == 26);
			setInvWidget("label_inv_amp", needAmp);
			setInvWidget("spinbox_mutation_inv_amplitude", needAmp);

			bool needScale = (invType == 25);
			setInvWidget("label_inv_scale", needScale);
			setInvWidget("spinbox_mutation_inv_scale", needScale);

			bool needMinR = false; // not used in kernel
			setInvWidget("label_inv_minr", needMinR);
			setInvWidget("spinbox_mutation_inv_min_r", needMinR);

			bool needMaxR = false; // not used in kernel
			setInvWidget("label_inv_maxr", needMaxR);
			setInvWidget("spinbox_mutation_inv_max_r", needMaxR);

			bool needWeight = (invType == 12);
			setInvWidget("label_inv_weight", needWeight);
			setInvWidget("spinbox_mutation_inv_weight", needWeight);

			bool needNSteps = (invType == 14);
			setInvWidget("label_inv_nsteps", needNSteps);
			setInvWidget("spinboxInt_mutation_inv_n_steps", needNSteps);

			bool needThreshold = (invType == 28);
			setInvWidget("label_inv_threshold", needThreshold);
			setInvWidget("spinbox_mutation_inv_threshold", needThreshold);

			bool needColorFactor = (invType == 29);
			setInvWidget("label_inv_colorfactor", needColorFactor);
			setInvWidget("spinbox_mutation_inv_color_factor", needColorFactor);

			bool needCenter2 = (invType == 11 || invType == 12 || invType == 13 || invType == 14);
			setInvWidget("label_inv_center2", needCenter2);
			setInvWidget("spinbox_mutation_inv_center2_ax", needCenter2);
			setInvWidget("spinbox_mutation_inv_center2_ay", needCenter2);
			setInvWidget("spinbox_mutation_inv_center2_az", needCenter2);

			bool needRadius2 = (invType == 11 || invType == 12 || invType == 13);
			setInvWidget("label_inv_radius2", needRadius2);
			setInvWidget("spinbox_mutation_inv_radius2", needRadius2);
		}
	}

	// Systems inside the main mutation group (no own GroupBox)
	bool mutationEnabled = ui->groupCheck_mutation_enabled->isChecked();

	// Fold system
	bool foldActive = mutationEnabled && ui->comboBox_mutation_fold_type->currentIndex() != 0;
	QList<QWidget *> allMutationChildren = ui->groupCheck_mutation_enabled->findChildren<QWidget *>();
	for (QWidget *w : allMutationChildren)
	{
		QString name = w->objectName();
		if (name.contains("fold") && !name.contains("position"))
		{
			styleWidget(w, foldActive);
		}
	}

	// Warp system (basic warp, not warp_dist)
	bool warpActive = mutationEnabled && ui->comboBox_mutation_warp_type->currentIndex() != 0;
	for (QWidget *w : allMutationChildren)
	{
		QString name = w->objectName();
		if (name.contains("warp") && !name.contains("warp_dist") && !name.contains("wd_"))
		{
			styleWidget(w, warpActive);
		}
	}

	// Math system
	bool mathActive = mutationEnabled && ui->comboBox_mutation_math_type->currentIndex() != 0;
	for (QWidget *w : allMutationChildren)
	{
		QString name = w->objectName();
		if (name.contains("math") && !name.contains("mb_math"))
		{
			styleWidget(w, mathActive);
		}
	}

	// --- Jos Leys DE per-type ---
	{
		QGroupBox *josGroup = ui->groupCheck_mutation_jos_leys_enabled;
		int josType = ui->comboBox_mutation_jos_de_type->currentIndex();
		bool josActive = josGroup->isChecked() && josType != 0;
		QString suffix = "_" + QString::number(tabIndex + 1);
		QList<QWidget *> josChildren = josGroup->findChildren<QWidget *>();
		auto setJosWidget = [&](const QString &baseName, bool enabled) {
			QString fullName = baseName + suffix;
			for (QWidget *w : josChildren)
			{
				if (w->objectName() == fullName)
				{
					styleWidget(w, josActive && enabled);
					break;
				}
			}
		};

		// Factor is used by all types
		setJosWidget("label_jos_factor", true);
		setJosWidget("spinbox_mutation_jos_factor", true);

		bool needParamA = (josType == 1 || josType == 2 || josType == 3 || josType == 4
						|| josType == 5 || josType == 6 || josType == 7 || josType == 8
						|| josType == 10 || josType == 11 || josType == 12 || josType == 13
						|| josType == 15 || josType == 17);
		setJosWidget("label_jos_param_a", needParamA);
		setJosWidget("spinbox_mutation_jos_param_a", needParamA);

		bool needParamB = (josType == 1 || josType == 2 || josType == 5 || josType == 6
						|| josType == 10 || josType == 11 || josType == 12 || josType == 13
						|| josType == 17);
		setJosWidget("label_jos_param_b", needParamB);
		setJosWidget("spinbox_mutation_jos_param_b", needParamB);

		bool needParamC = (josType == 3 || josType == 4 || josType == 7 || josType == 8
						|| josType == 11 || josType == 12);
		setJosWidget("label_jos_param_c", needParamC);
		setJosWidget("spinbox_mutation_jos_param_c", needParamC);

		bool needParamD = false; // never used in kernel
		setJosWidget("label_jos_param_d", needParamD);
		setJosWidget("spinbox_mutation_jos_param_d", needParamD);

		bool needPhase = (josType == 2 || josType == 4 || josType == 6 || josType == 8);
		setJosWidget("label_jos_phase", needPhase);
		setJosWidget("spinbox_mutation_jos_phase", needPhase);

		bool needFreq = (josType == 2 || josType == 4 || josType == 6 || josType == 8);
		setJosWidget("label_jos_freq", needFreq);
		setJosWidget("spinbox_mutation_jos_freq", needFreq);

		bool needAmp = false; // never used in kernel
		setJosWidget("label_jos_amp", needAmp);
		setJosWidget("spinbox_mutation_jos_amp", needAmp);

		bool needScale = false; // never used in kernel
		setJosWidget("label_jos_scale", needScale);
		setJosWidget("spinbox_mutation_jos_scale", needScale);
	}

	// --- Pseudokleinian DE per-type ---
	{
		QGroupBox *pkGroup = ui->groupCheck_mutation_pk_enabled;
		int pkType = ui->comboBox_mutation_pk_de_type->currentIndex();
		bool pkActive = pkGroup->isChecked() && pkType != 0;
		QString suffix = "_" + QString::number(tabIndex + 1);
		QList<QWidget *> pkChildren = pkGroup->findChildren<QWidget *>();
		auto setPkWidget = [&](const QString &baseName, bool enabled) {
			QString fullName = baseName + suffix;
			for (QWidget *w : pkChildren)
			{
				if (w->objectName() == fullName)
				{
					styleWidget(w, pkActive && enabled);
					break;
				}
			}
		};

		// Factor is used by all types
		setPkWidget("label_pk_factor", true);
		setPkWidget("spinbox_mutation_pk_factor", true);

		bool needParamA = (pkType >= 7 && pkType <= 29);
		setPkWidget("label_pk_param_a", needParamA);
		setPkWidget("spinbox_mutation_pk_param_a", needParamA);

		bool needParamB = (pkType == 13 || pkType == 14 || pkType == 20 || pkType == 21
						|| pkType == 22 || pkType == 29);
		setPkWidget("label_pk_param_b", needParamB);
		setPkWidget("spinbox_mutation_pk_param_b", needParamB);

		bool needParamC = (pkType == 21 || pkType == 22 || pkType == 29);
		setPkWidget("label_pk_param_c", needParamC);
		setPkWidget("spinbox_mutation_pk_param_c", needParamC);

		bool needParamD = false; // never used in kernel
		setPkWidget("label_pk_param_d", needParamD);
		setPkWidget("spinbox_mutation_pk_param_d", needParamD);

		bool needPhase = (pkType == 10 || pkType == 20 || pkType == 21 || pkType == 22);
		setPkWidget("label_pk_phase", needPhase);
		setPkWidget("spinbox_mutation_pk_phase", needPhase);

		bool needFreq = (pkType == 10 || pkType == 20 || pkType == 21 || pkType == 22);
		setPkWidget("label_pk_freq", needFreq);
		setPkWidget("spinbox_mutation_pk_freq", needFreq);

		bool needAmp = false; // never used in kernel
		setPkWidget("label_pk_amp", needAmp);
		setPkWidget("spinbox_mutation_pk_amp", needAmp);

		bool needScale = false; // never used in kernel
		setPkWidget("label_pk_scale", needScale);
		setPkWidget("spinbox_mutation_pk_scale", needScale);
	}
}

void cTabFractal::FrameIterationFormulaSetEnabled(bool enabled) const
{
	ui->frame_iterations_formula->setEnabled(enabled);
}

void cTabFractal::SynchronizeFractal(
	std::shared_ptr<cParameterContainer> fractal, qInterface::enumReadWrite mode) const
{
	if (fractalWidget)
	{
		SynchronizeInterfaceWindow(fractalWidget.get(), fractal, mode);
	}
}

void cTabFractal::slotPressedButtonIFSDefaultsDodecahedron() const
{
	SynchronizeInterfaceWindow(fractalWidget.get(), fractalParams->at(tabIndex), qInterface::read);
	gMainInterface->IFSDefaultsDodecahedron(fractalParams->at(tabIndex));
	SynchronizeInterfaceWindow(fractalWidget.get(), fractalParams->at(tabIndex), qInterface::write);
}

void cTabFractal::slotPressedButtonIFSDefaultsIcosahedron() const
{
	SynchronizeInterfaceWindow(fractalWidget.get(), fractalParams->at(tabIndex), qInterface::read);
	gMainInterface->IFSDefaultsIcosahedron(fractalParams->at(tabIndex));
	SynchronizeInterfaceWindow(fractalWidget.get(), fractalParams->at(tabIndex), qInterface::write);
}

void cTabFractal::slotPressedButtonIFSDefaultsOctahedron() const
{
	SynchronizeInterfaceWindow(fractalWidget.get(), fractalParams->at(tabIndex), qInterface::read);
	gMainInterface->IFSDefaultsOctahedron(fractalParams->at(tabIndex));
	SynchronizeInterfaceWindow(fractalWidget.get(), fractalParams->at(tabIndex), qInterface::write);
}

void cTabFractal::slotPressedButtonIFSDefaultsMengerSponge() const
{
	SynchronizeInterfaceWindow(fractalWidget.get(), fractalParams->at(tabIndex), qInterface::read);
	gMainInterface->IFSDefaultsMengerSponge(fractalParams->at(tabIndex));
	SynchronizeInterfaceWindow(fractalWidget.get(), fractalParams->at(tabIndex), qInterface::write);
}

void cTabFractal::slotPressedButtonIFSDefaultsReset() const
{
	SynchronizeInterfaceWindow(fractalWidget.get(), fractalParams->at(tabIndex), qInterface::read);
	gMainInterface->IFSDefaultsReset(fractalParams->at(tabIndex));
	SynchronizeInterfaceWindow(fractalWidget.get(), fractalParams->at(tabIndex), qInterface::write);
}

void cTabFractal::slotPressedButtonResetFormula() const
{
	gMainInterface->ResetFormula(tabIndex);
}

void cTabFractal::slotPressedButtonMutationReset()
{
	int idx = tabIndex + 1;
	// Reset all mutation params to defaults (keep enabled state unchanged)

	auto setD = [&](const QString &name, double val) {
		params->Set(name + "_" + QString::number(idx), val);
	};
	auto setI = [&](const QString &name, int val) {
		params->Set(name + "_" + QString::number(idx), val);
	};
	auto setB = [&](const QString &name, bool val) {
		params->Set(name + "_" + QString::number(idx), val);
	};

	// Pre-transform
	setD("mutation_pre_rotation_ax", 0.0);
	setD("mutation_pre_rotation_ay", 0.0);
	setD("mutation_pre_rotation_az", 0.0);
	setD("mutation_pre_scale", 1.0);
	setD("mutation_pre_offset_ax", 0.0);
	setD("mutation_pre_offset_ay", 0.0);
	setD("mutation_pre_offset_az", 0.0);
	setB("mutation_pre_abs_ax", false);
	setB("mutation_pre_abs_ay", false);
	setB("mutation_pre_abs_az", false);
	// Post-transform
	setD("mutation_post_rotation_ax", 0.0);
	setD("mutation_post_rotation_ay", 0.0);
	setD("mutation_post_rotation_az", 0.0);
	setD("mutation_post_scale", 1.0);
	setD("mutation_post_offset_ax", 0.0);
	setD("mutation_post_offset_ay", 0.0);
	setD("mutation_post_offset_az", 0.0);
	// Types
	setI("mutation_swizzle", 0);
	setI("mutation_fold_type", 0);
	setI("mutation_fold_position", 0);
	setD("mutation_fold_limit", 1.0);
	setD("mutation_fold_value", 2.0);
	setI("mutation_kaleidoscope_sides", 6);
	setI("mutation_warp_type", 0);
	setD("mutation_warp_frequency", 1.0);
	setD("mutation_warp_amplitude", 0.0);
	setI("mutation_math_type", 0);
	setD("mutation_math_p1", 2.0);
	setD("mutation_math_p2", 0.0);
	setD("mutation_math_p3", 0.0);
	setD("mutation_math_p4", 0.0);
	setD("mutation_math_p5", 0.0);
	setD("mutation_math_p6", 0.0);
	setD("mutation_math_p7", 0.0);
	setD("mutation_math_p8", 0.0);
	setD("mutation_math_mix", 1.0);
	// Output
	setD("mutation_z_mix", 1.0);
	setD("mutation_de_scale", 1.0);
	setI("mutation_de_tweak", 0);
	setI("mutation_orbit_trap", 0);
	// Iterations (global + per-section)
	setI("mutation_iteration_start", 0);
	setI("mutation_iteration_stop", 250);
	setI("mutation_pre_iter_start", 0);
	setI("mutation_pre_iter_stop", 10000);
	setI("mutation_fold_iter_start", 0);
	setI("mutation_fold_iter_stop", 10000);
	setI("mutation_warp_iter_start", 0);
	setI("mutation_warp_iter_stop", 10000);
	setI("mutation_math_iter_start", 0);
	setI("mutation_math_iter_stop", 10000);
	setI("mutation_post_iter_start", 0);
	setI("mutation_post_iter_stop", 10000);
	setI("mutation_julia_iter_start", 0);
	setI("mutation_julia_iter_stop", 10000);
	setI("mutation_de_iter_start", 0);
	setI("mutation_de_iter_stop", 10000);
	// Julia
	setI("mutation_julia_injection", 0);
	setI("mutation_julia_start", 0);
	setI("mutation_julia_c_transform", 0);
	setI("mutation_julia_dynamic", 0);
	setI("mutation_julia_multi", 0);
	setD("mutation_julia_c_mul", 1.0);
	setD("mutation_julia_c_power", 1.0);
	setD("mutation_julia_c_radius", 1.0);
	// Inversion
	setI("mutation_inv_type", 0);
	setD("mutation_inv_center_ax", 0.0);
	setD("mutation_inv_center_ay", 0.0);
	setD("mutation_inv_center_az", 0.0);
	setD("mutation_inv_radius", 1.0);
	setD("mutation_inv_param_a", 1.0);
	setD("mutation_inv_param_b", 1.0);
	setD("mutation_inv_param_c", 1.0);
	setD("mutation_inv_scale", 1.0);
	setD("mutation_inv_angle", 0.0);
	setD("mutation_inv_frequency", 1.0);
	setD("mutation_inv_amplitude", 0.1);
	setD("mutation_inv_min_r", 0.5);
	setD("mutation_inv_max_r", 1.0);
	setD("mutation_inv_pre_rot_ax", 0.0);
	setD("mutation_inv_pre_rot_ay", 0.0);
	setD("mutation_inv_pre_rot_az", 0.0);
	setD("mutation_inv_center2_ax", 0.0);
	setD("mutation_inv_center2_ay", 0.0);
	setD("mutation_inv_center2_az", 0.0);
	setD("mutation_inv_radius2", 1.0);
	setD("mutation_inv_weight", 0.5);
	setI("mutation_inv_n_steps", 4);
	setD("mutation_inv_threshold", 1.0);
	setD("mutation_inv_color_factor", 1.0);
	setI("mutation_inv_iter_start", 0);
	setI("mutation_inv_iter_stop", 10000);
	// Clip
	setI("mutation_clip_type", 0);
	setD("mutation_clip_center_ax", 0.0);
	setD("mutation_clip_center_ay", 0.0);
	setD("mutation_clip_center_az", 0.0);
	setD("mutation_clip_size_ax", 1.0);
	setD("mutation_clip_size_ay", 1.0);
	setD("mutation_clip_size_az", 1.0);
	setD("mutation_clip_radius", 1.0);
	setD("mutation_clip_major_radius", 2.0);
	setD("mutation_clip_angle", 0.0);
	setD("mutation_clip_amplitude", 0.1);
	setD("mutation_clip_frequency", 1.0);
	setD("mutation_clip_smooth_k", 0.1);
	setI("mutation_clip_boolean_op", 0);
	setD("mutation_clip_pre_rot_ax", 0.0);
	setD("mutation_clip_pre_rot_ay", 0.0);
	setD("mutation_clip_pre_rot_az", 0.0);
	setI("mutation_clip_n_points", 5);
	setD("mutation_clip_param_a", 1.0);
	setD("mutation_clip_param_b", 1.0);
	setD("mutation_clip_param_c", 1.0);
	setD("mutation_clip_threshold", 1.0);
	setI("mutation_clip_iter_start", 0);
	setI("mutation_clip_iter_stop", 10000);

	// Jos Leys DE reset
	setI("mutation_jos_de_type", 0);
	setD("mutation_jos_factor", 1.0);
	setD("mutation_jos_param_a", 1.0);
	setD("mutation_jos_param_b", 1.0);
	setD("mutation_jos_param_c", 1.0);
	setD("mutation_jos_param_d", 1.0);
	setD("mutation_jos_freq", 1.0);
	setD("mutation_jos_amp", 0.5);
	setD("mutation_jos_scale", 1.0);
	setD("mutation_jos_phase", 0.0);
	setI("mutation_jos_iter_start", 0);
	setI("mutation_jos_iter_stop", 10000);

	// Pseudokleinian DE reset
	setI("mutation_pk_de_type", 0);
	setD("mutation_pk_factor", 1.0);
	setD("mutation_pk_param_a", 1.0);
	setD("mutation_pk_param_b", 1.0);
	setD("mutation_pk_param_c", 1.0);
	setD("mutation_pk_param_d", 1.0);
	setD("mutation_pk_freq", 1.0);
	setD("mutation_pk_amp", 0.5);
	setD("mutation_pk_scale", 1.0);
	setD("mutation_pk_phase", 0.0);
	setI("mutation_pk_iter_start", 0);
	setI("mutation_pk_iter_stop", 10000);

	// Mandelbox Math reset
	setI("mutation_mb_math_type", 0);
	setD("mutation_mb_factor", 1.0);
	setD("mutation_mb_param_a", 1.0);
	setD("mutation_mb_param_b", 1.0);
	setD("mutation_mb_param_c", 1.0);
	setD("mutation_mb_param_d", 1.0);
	setD("mutation_mb_param_e", 1.0);
	setD("mutation_mb_param_f", 1.0);
	setD("mutation_mb_param_g", 1.0);
	setD("mutation_mb_param_h", 0.0);
	setI("mutation_mb_iter_start", 0);
	setI("mutation_mb_iter_stop", 10000);

	// Warp Distortion reset
	setI("mutation_warp_dist_type", 0);
	setD("mutation_wd_factor", 1.0);
	setD("mutation_wd_param_a", 1.0);
	setD("mutation_wd_param_b", 1.0);
	setD("mutation_wd_param_c", 1.0);
	setD("mutation_wd_param_d", 1.0);
	setD("mutation_wd_freq", 1.0);
	setD("mutation_wd_amp", 0.5);
	setD("mutation_wd_scale", 1.0);
	setD("mutation_wd_phase", 0.0);
	setI("mutation_wd_iter_start", 0);
	setI("mutation_wd_iter_stop", 10000);

	// Symmetry/Kaleidoscope reset
	setI("mutation_sym_kal_type", 0);
	setD("mutation_sk_factor", 1.0);
	setD("mutation_sk_param_a", 1.0);
	setD("mutation_sk_param_b", 1.0);
	setD("mutation_sk_param_c", 1.0);
	setD("mutation_sk_param_d", 1.0);
	setD("mutation_sk_freq", 1.0);
	setD("mutation_sk_amp", 0.5);
	setD("mutation_sk_angle", 60.0);
	setD("mutation_sk_offset", 0.0);
	setI("mutation_sk_iter_start", 0);
	setI("mutation_sk_iter_stop", 10000);

	// Abox DE reset
	setI("mutation_abox_type", 0);
	setD("mutation_ab_factor", 1.0);
	setD("mutation_ab_param_a", 1.0);
	setD("mutation_ab_param_b", 1.0);
	setD("mutation_ab_param_c", 1.0);
	setD("mutation_ab_param_d", 1.0);
	setD("mutation_ab_param_e", 1.0);
	setD("mutation_ab_param_f", 1.0);
	setD("mutation_ab_param_g", 1.0);
	setD("mutation_ab_param_h", 0.0);
	setI("mutation_ab_iter_start", 0);
	setI("mutation_ab_iter_stop", 10000);

	// Noise & Procedural DE reset
	setI("mutation_noise_type", 0);
	setD("mutation_noise_factor", 1.0);
	setD("mutation_noise_param_a", 1.0);
	setD("mutation_noise_param_b", 1.0);
	setD("mutation_noise_param_c", 1.0);
	setD("mutation_noise_param_d", 1.0);
	setD("mutation_noise_freq", 1.0);
	setD("mutation_noise_amp", 0.5);
	setI("mutation_noise_iter_start", 0);
	setI("mutation_noise_iter_stop", 10000);

	// Orbit Trap DE reset
	setI("mutation_orbit_trap_type", 0);
	setD("mutation_orbit_factor", 1.0);
	setD("mutation_orbit_param_a", 1.0);
	setD("mutation_orbit_param_b", 1.0);
	setD("mutation_orbit_param_c", 1.0);
	setD("mutation_orbit_param_d", 1.0);
	setI("mutation_orbit_iter_start", 0);
	setI("mutation_orbit_iter_stop", 10000);

	// MandelTorus DE reset
	setI("mutation_torus_type", 0);
	setD("mutation_torus_factor", 1.0);
	setD("mutation_torus_param_a", 1.0);
	setD("mutation_torus_param_b", 1.0);
	setD("mutation_torus_param_c", 1.0);
	setD("mutation_torus_param_d", 1.0);
	setI("mutation_torus_iter_start", 0);
	setI("mutation_torus_iter_stop", 10000);

	// Write defaults back to UI widgets
	SynchronizeInterface(params, qInterface::write);
	UpdateMutationGrayOut();
}

void cTabFractal::slotPressedButtonNavi()
{
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
