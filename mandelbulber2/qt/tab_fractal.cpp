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
	// automatedWidgets->ConnectSignalsForSlidersInWindow(this);
	ConnectSignals();

	tabIndex = 0;
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
	// Iterations
	setI("mutation_iteration_start", 0);
	setI("mutation_iteration_stop", 250);
	// Julia
	setI("mutation_julia_injection", 0);
	setI("mutation_julia_start", 0);
	setI("mutation_julia_c_transform", 0);
	setI("mutation_julia_dynamic", 0);
	setI("mutation_julia_multi", 0);
	setD("mutation_julia_c_mul", 1.0);
	setD("mutation_julia_c_power", 1.0);
	setD("mutation_julia_c_radius", 1.0);

	// Write defaults back to UI widgets
	SynchronizeInterface(params, qInterface::write);
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
