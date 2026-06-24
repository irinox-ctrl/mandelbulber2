#include "dock_mutation_tab.h"
#include "ui_dock_mutation_tab.h"

#include "src/automated_widgets.hpp"
#include "src/fractal_container.hpp"
#include "src/initparameters.hpp"
#include "src/interface.hpp"
#include "src/mutation_ui_registry.hpp"
#include "src/write_log.hpp"
#include "qt_utils.h"

#include "formula/definition/all_fractal_list.hpp"

#include <QSet>
#include <functional>

#define MUT_CLIP_INV (ui->widget_mutation_clip_inv_panel->clipInvUi())
#define MUT_JOS_PK (ui->widget_mutation_jos_pk_panel->josPkUi())
#define MUT_SYS1 (ui->widget_mutation_systems_panel->group1Ui())
#define MUT_SYS2 (ui->widget_mutation_systems_panel->group2Ui())
#define MUT_SYS3 (ui->widget_mutation_systems_panel->group3Ui())
#define MUT_TAIL (ui->widget_mutation_tail_panel->tailUi())

cDockMutationTab::cDockMutationTab(QWidget *parent)
		: QWidget(parent), cMyWidgetWithParams(), ui(new Ui::cDockMutationTab)
{
	ui->setupUi(this);
	automatedWidgets = new cAutomatedWidgets(this);
	tabIndex = 0;
}

cDockMutationTab::~cDockMutationTab()
{
	delete ui;
}

void cDockMutationTab::InitWidgetNames() const
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
				newName = oldName.left(oldName.size() - 2) + "_" + QString::number(tabIndex + 1) + lastTwoLetters;
			}
			else
			{
				newName = oldName + "_" + QString::number(tabIndex + 1);
			}
			widget->setObjectName(newName);
		}
	}
}

void cDockMutationTab::Init(int _tabIndex)
{
	tabIndex = _tabIndex;

	InitWidgetNames();

	automatedWidgets->ConnectSignalsForSlidersInWindow(this);

	auto connectMutationCombo = [this](QComboBox *combo, const QString &paramBase) {
		if (!combo || !params) return;
		const QString paramName = paramBase + "_" + QString::number(tabIndex + 1);
		connect(combo, QOverload<int>::of(&QComboBox::currentIndexChanged),
			this, [this, paramName, paramBase](int index) {
				if (!params) return;
				params->Set(paramName, index);
				// Warp amplitude defaults to 0 — auto-enable a visible strength when type is picked
				if (paramBase == "mutation_warp_type" && index != 0)
				{
					const QString ampName =
						"mutation_warp_amplitude_" + QString::number(tabIndex + 1);
					if (params->Get<double>(ampName) < 1e-6)
						params->Set(ampName, 0.5);
				}
			});
	};

	connectMutationCombo(MUT_CLIP_INV->comboBox_mutation_inv_type, "mutation_inv_type");
	connectMutationCombo(MUT_CLIP_INV->comboBox_mutation_clip_type, "mutation_clip_type");
	connectMutationCombo(MUT_JOS_PK->comboBox_mutation_jos_de_type, "mutation_jos_de_type");
	connectMutationCombo(MUT_JOS_PK->comboBox_mutation_pk_de_type, "mutation_pk_de_type");
	connectMutationCombo(MUT_SYS1->comboBox_mutation_mb_math_type, "mutation_mb_math_type");
	connectMutationCombo(MUT_SYS1->comboBox_mutation_warp_dist_type, "mutation_warp_dist_type");
	connectMutationCombo(MUT_SYS1->comboBox_mutation_sym_kal_type, "mutation_sym_kal_type");
	connectMutationCombo(MUT_SYS2->comboBox_mutation_abox_type, "mutation_abox_type");
	connectMutationCombo(MUT_SYS2->comboBox_mutation_noise_type, "mutation_noise_type");
	connectMutationCombo(MUT_SYS2->comboBox_mutation_orbit_trap_type, "mutation_orbit_trap_type");
	connectMutationCombo(MUT_SYS3->comboBox_mutation_torus_type, "mutation_torus_type");
	connectMutationCombo(MUT_SYS3->comboBox_mutation_clamp_type, "mutation_clamp_type");
	connectMutationCombo(MUT_SYS3->comboBox_mutation_jb_type, "mutation_jb_type");
	connectMutationCombo(MUT_TAIL->comboBox_mutation_md_type, "mutation_md_type");
	connectMutationCombo(MUT_TAIL->comboBox_mutation_as_type, "mutation_as_type");
	connectMutationCombo(MUT_TAIL->comboBox_mutation_sm_type, "mutation_sm_type");
	connectMutationCombo(MUT_TAIL->comboBox_mutation_blockify_type, "mutation_blockify_type");
	connectMutationCombo(MUT_TAIL->comboBox_mutation_tile_type, "mutation_tile_type");
	connectMutationCombo(ui->comboBox_mutation_julia_injection, "mutation_julia_injection");
	connectMutationCombo(ui->comboBox_mutation_julia_start, "mutation_julia_start");
	connectMutationCombo(ui->comboBox_mutation_julia_c_transform, "mutation_julia_c_transform");
	connectMutationCombo(ui->comboBox_mutation_julia_dynamic, "mutation_julia_dynamic");
	connectMutationCombo(ui->comboBox_mutation_julia_multi, "mutation_julia_multi");
	connectMutationCombo(ui->comboBox_mutation_de_tweak, "mutation_de_tweak");
	connectMutationCombo(ui->comboBox_mutation_fold_type, "mutation_fold_type");
	connectMutationCombo(ui->comboBox_mutation_fold_position, "mutation_fold_position");
	connectMutationCombo(ui->comboBox_mutation_math_type, "mutation_math_type");
	connectMutationCombo(ui->comboBox_mutation_orbit_trap, "mutation_orbit_trap");
	connectMutationCombo(ui->comboBox_mutation_swizzle, "mutation_swizzle");
	connectMutationCombo(ui->comboBox_mutation_warp_type, "mutation_warp_type");

	// Weight spinboxes sync via SynchronizeInterfaceWindow (standard Mandelbulber mechanism)
	// No manual connectWeight needed — widget name matches param key after InitWidgetNames

	QList<QComboBox *> mutationTypeCombos = {
		MUT_CLIP_INV->comboBox_mutation_inv_type,
		MUT_CLIP_INV->comboBox_mutation_clip_type,
		MUT_JOS_PK->comboBox_mutation_jos_de_type,
		MUT_JOS_PK->comboBox_mutation_pk_de_type,
		MUT_SYS1->comboBox_mutation_mb_math_type,
		MUT_SYS1->comboBox_mutation_warp_dist_type,
		MUT_SYS1->comboBox_mutation_sym_kal_type,
		MUT_SYS2->comboBox_mutation_abox_type,
		MUT_SYS2->comboBox_mutation_noise_type,
		MUT_SYS2->comboBox_mutation_orbit_trap_type,
		MUT_SYS3->comboBox_mutation_torus_type,
		ui->comboBox_mutation_fold_type,
		ui->comboBox_mutation_warp_type,
		ui->comboBox_mutation_math_type,
		ui->comboBox_mutation_julia_injection,
		ui->comboBox_mutation_julia_start,
		ui->comboBox_mutation_julia_c_transform,
		ui->comboBox_mutation_julia_dynamic,
		ui->comboBox_mutation_julia_multi,
		MUT_SYS3->comboBox_mutation_clamp_type,
		MUT_SYS3->comboBox_mutation_jb_type,
		MUT_TAIL->comboBox_mutation_md_type,
		MUT_TAIL->comboBox_mutation_as_type,
		MUT_TAIL->comboBox_mutation_sm_type,
		MUT_TAIL->comboBox_mutation_blockify_type,
		MUT_TAIL->comboBox_mutation_tile_type,
		ui->comboBox_mutation_de_tweak,
		ui->comboBox_mutation_swizzle,
		ui->comboBox_mutation_orbit_trap,
		ui->comboBox_mutation_fold_position,
	};
	for (QComboBox *combo : mutationTypeCombos)
	{
		if (combo) connect(combo, QOverload<int>::of(&QComboBox::currentIndexChanged),
			this, &cDockMutationTab::UpdateMutationGrayOut);
	}

	// Verbind combos voor grayOut
	QList<QGroupBox *> mutationGroups = {
		ui->groupCheck_mutation_enabled,
		MUT_CLIP_INV->groupCheck_mutation_inversion_enabled,
		MUT_CLIP_INV->groupCheck_mutation_clip_enabled,
		MUT_JOS_PK->groupCheck_mutation_jos_leys_enabled,
		MUT_JOS_PK->groupCheck_mutation_pk_enabled,
		MUT_SYS1->groupCheck_mutation_mb_math_enabled,
		MUT_SYS1->groupCheck_mutation_warp_dist_enabled,
		MUT_SYS1->groupCheck_mutation_symmetry_enabled,
		MUT_SYS2->groupCheck_mutation_abox_enabled,
		MUT_SYS2->groupCheck_mutation_noise_enabled,
		MUT_SYS2->groupCheck_mutation_orbit_trap_enabled,
		MUT_SYS3->groupCheck_mutation_torus_enabled,
		MUT_SYS3->groupCheck_mutation_clamp_enabled,
		MUT_SYS3->groupCheck_mutation_jb_enabled,
		MUT_TAIL->groupCheck_mutation_md_enabled,
		MUT_TAIL->groupCheck_mutation_as_enabled,
		MUT_TAIL->groupCheck_mutation_sm_enabled,
		MUT_TAIL->groupCheck_mutation_blockify_enabled,
		MUT_TAIL->groupCheck_mutation_tile_enabled,
	};
	for (QGroupBox *group : mutationGroups)
	{
		if (group) connect(group, &QGroupBox::toggled, this, &cDockMutationTab::UpdateMutationGrayOut);
	}

	// === Accordion: één sectie open, geen scroll ===
	// setMaximumHeight(22) = alleen titelbar zichtbaar (ingeklapt)
	// setMaximumHeight(QWIDGETSIZE_MAX) = volledig open
	const int TITLE_H = 22;

	QList<QGroupBox *> sections = {
		MUT_CLIP_INV->groupCheck_mutation_inversion_enabled,
		MUT_CLIP_INV->groupCheck_mutation_clip_enabled,
		MUT_JOS_PK->groupCheck_mutation_jos_leys_enabled,
		MUT_JOS_PK->groupCheck_mutation_pk_enabled,
		MUT_SYS1->groupCheck_mutation_mb_math_enabled,
		MUT_SYS1->groupCheck_mutation_warp_dist_enabled,
		MUT_SYS1->groupCheck_mutation_symmetry_enabled,
		MUT_SYS2->groupCheck_mutation_abox_enabled,
		MUT_SYS2->groupCheck_mutation_noise_enabled,
		MUT_SYS2->groupCheck_mutation_orbit_trap_enabled,
		MUT_SYS3->groupCheck_mutation_torus_enabled,
		MUT_SYS3->groupCheck_mutation_clamp_enabled,
		MUT_SYS3->groupCheck_mutation_jb_enabled,
		MUT_TAIL->groupCheck_mutation_md_enabled,
		MUT_TAIL->groupCheck_mutation_as_enabled,
		MUT_TAIL->groupCheck_mutation_sm_enabled,
		MUT_TAIL->groupCheck_mutation_blockify_enabled,
		MUT_TAIL->groupCheck_mutation_tile_enabled,
	};

	// Sluit alle secties bij opstarten
	for (QGroupBox *sec : sections)
	{
		if (!sec) continue;
		sec->blockSignals(true);
		sec->setChecked(false);
		sec->blockSignals(false);
		sec->setMaximumHeight(TITLE_H);
	}

	// Verbind accordion: open deze, sluit alle andere
	for (QGroupBox *sec : sections)
	{
		if (!sec) continue;
		connect(sec, &QGroupBox::toggled, this,
			[this, sec, sections, TITLE_H](bool open) {
				if (open)
				{
					for (QGroupBox *other : sections)
					{
						if (!other || other == sec) continue;
						other->blockSignals(true);
						other->setChecked(false);
						other->blockSignals(false);
						toggleSection(other, false, TITLE_H);
					}
					toggleSection(sec, true, TITLE_H);
				}
				else
				{
					toggleSection(sec, false, TITLE_H);
				}
			});
	}

	connect(MUT_SYS3->pushButton_mutation_reset, &QPushButton::clicked, this,
		&cDockMutationTab::slotPressedButtonMutationReset);

	if (ui->pushButton_mutation_randomize_weights)
		connect(ui->pushButton_mutation_randomize_weights, &QPushButton::clicked, this,
			&cDockMutationTab::slotPressedButtonRandomizeWeights);
	if (ui->pushButton_mutation_reset_weights)
		connect(ui->pushButton_mutation_reset_weights, &QPushButton::clicked, this,
			&cDockMutationTab::slotPressedButtonResetWeights);
	if (ui->pushButton_mutation_randomize_weights_2)
		connect(ui->pushButton_mutation_randomize_weights_2, &QPushButton::clicked, this,
			&cDockMutationTab::slotPressedButtonRandomizeWeights);
	if (ui->pushButton_mutation_reset_all)
		connect(ui->pushButton_mutation_reset_all, &QPushButton::clicked, this,
			&cDockMutationTab::slotPressedButtonMutationReset);
	if (ui->pushButton_mutation_reset_all_top)
		connect(ui->pushButton_mutation_reset_all_top, &QPushButton::clicked, this,
			&cDockMutationTab::slotPressedButtonMutationReset);

	// Connect per-section reset weight buttons
	for (QPushButton *btn : findChildren<QPushButton *>())
	{
		if (btn->objectName().contains("_reset_weights"))
			connect(btn, &QPushButton::clicked, this,
				&cDockMutationTab::slotPressedButtonResetSectionWeights);
	}

	// Zorg dat alle spinboxen breed genoeg zijn om cijfers te tonen
	for (QAbstractSpinBox *sb : findChildren<QAbstractSpinBox *>())
	{
		sb->setMinimumWidth(72);
		sb->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
	}

	SetupTooltips();
}

void cDockMutationTab::toggleSection(QGroupBox *sec, bool open, int titleHeight) const
{
	if (!sec) return;
	const int target = open ? sec->sizeHint().height() : titleHeight;
	auto *anim = new QPropertyAnimation(sec, "maximumHeight", sec);
	anim->setDuration(150);
	anim->setStartValue(sec->maximumHeight());
	anim->setEndValue(target);
	anim->setEasingCurve(QEasingCurve::InOutQuad);
	anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void cDockMutationTab::SetupTooltips() const
{
	if (MUT_SYS3->pushButton_mutation_reset)
		MUT_SYS3->pushButton_mutation_reset->setToolTip(
			tr("Reset all mutation parameters to defaults for this fractal"));
	if (ui->pushButton_mutation_randomize_weights)
		ui->pushButton_mutation_randomize_weights->setToolTip(
			tr("Randomize mutation section weights"));
	if (ui->pushButton_mutation_reset_weights)
		ui->pushButton_mutation_reset_weights->setToolTip(tr("Reset all mutation weights to 1.0"));
	if (ui->groupCheck_mutation_enabled)
		ui->groupCheck_mutation_enabled->setToolTip(tr("Enable or disable the mutation stack"));
	for (QComboBox *combo : findChildren<QComboBox *>())
	{
		if (!combo->toolTip().isEmpty()) continue;
		combo->setToolTip(tr("Mutation type selector — orange fields are active for this type"));
	}
}

void cDockMutationTab::SynchronizeInterface(
	std::shared_ptr<cParameterContainer> par, qInterface::enumReadWrite mode)
{
	SynchronizeInterfaceWindow(this, par, mode);
}

void cDockMutationTab::MarkFormulaHiddenWidgets(const QStringList &names, bool hidden) const
{
	if (!hidden) return;
	for (const QString &name : names)
		m_formulaHiddenWidgets.insert(name);
}

void cDockMutationTab::UpdateMutationFieldVisibility(int formulaIndex) const
{
	m_formulaHiddenWidgets.clear();

	if (formulaIndex <= 0 || formulaIndex >= newFractalList.size())
	{
		UpdateMutationGrayOut();
		return;
	}

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
		"spinboxInt_mutation_de_iter_start" + idx,
		"spinboxInt_mutation_de_iter_stop" + idx,
		"label_mutation_de_tweak" + idx,
		"label_mutation_de_scale" + idx,
		"label_mutation_de_tweak_p1" + idx,
		"label_mutation_de_tweak_p2" + idx,
		"label_mutation_de_iter" + idx,
		"label_mutation_de_iter_s" + idx,
		"label_mutation_de_iter_e" + idx
	};
	MarkFormulaHiddenWidgets(deTweakWidgets, !hasDeTweak);

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
		"spinboxd3_mutation_julia_c_rot_x" + idx,
		"spinboxd3_mutation_julia_c_rot_y" + idx,
		"spinboxd3_mutation_julia_c_rot_z" + idx,
		"spinboxd_mutation_julia_c_mobius_a" + idx,
		"spinboxd_mutation_julia_c_mobius_b" + idx,
		"spinboxd_mutation_julia_c_mobius_d" + idx,
		"spinboxd_mutation_julia_pulse_amp" + idx,
		"spinboxd_mutation_julia_noise_freq" + idx,
		"spinboxd_mutation_julia_noise_amp" + idx,
		"spinboxd3_mutation_julia_fourier_c2_x" + idx,
		"spinboxd3_mutation_julia_fourier_c2_y" + idx,
		"spinboxd3_mutation_julia_fourier_c2_z" + idx,
		"spinboxd3_mutation_julia_fourier_c3_x" + idx,
		"spinboxd3_mutation_julia_fourier_c3_y" + idx,
		"spinboxd3_mutation_julia_fourier_c3_z" + idx,
		"spinboxd3_mutation_julia_bipolar_cr_x" + idx,
		"spinboxd3_mutation_julia_bipolar_cr_y" + idx,
		"spinboxd3_mutation_julia_bipolar_cr_z" + idx,
		// Fine-tune: per-subsystem iter ranges
		"spinboxInt_mutation_julia_ctransform_iter_start" + idx,
		"spinboxInt_mutation_julia_ctransform_iter_stop" + idx,
		"spinboxInt_mutation_julia_dynamic_iter_start" + idx,
		"spinboxInt_mutation_julia_dynamic_iter_stop" + idx,
		"spinboxInt_mutation_julia_multi_iter_start" + idx,
		"spinboxInt_mutation_julia_multi_iter_stop" + idx,
		// Fine-tune: strengths
		"spinbox_mutation_julia_ctransform_strength" + idx,
		"spinbox_mutation_julia_dynamic_strength" + idx,
		"spinbox_mutation_julia_multi_strength" + idx,
		"spinbox_mutation_julia_injection_strength" + idx,
		"spinbox_mutation_julia_de_factor" + idx,
		// Fine-tune: expansion params
		"spinbox_mutation_julia_decay_rate" + idx,
		"spinbox_mutation_julia_spiral_angle" + idx,
		"spinbox_mutation_julia_chaos_r" + idx,
		"spinbox_mutation_julia_threshold" + idx,
		"spinbox_mutation_julia_gradient_end" + idx,
		"spinbox_mutation_julia_box_fold_limit" + idx,
		"spinbox_mutation_julia_start_epsilon" + idx,
		"spinboxd3_mutation_julia_layer_c2_x" + idx,
		"spinboxd3_mutation_julia_layer_c2_y" + idx,
		"spinboxd3_mutation_julia_layer_c2_z" + idx,
		"spinbox_mutation_julia_dist_band_mid" + idx,
		"spinbox_mutation_julia_dist_band_far" + idx,
		// Labels
		"label_mutation_julia_injection" + idx,
		"label_mutation_julia_start" + idx,
		"label_mutation_julia_c_transform" + idx,
		"label_mutation_julia_dynamic" + idx,
		"label_mutation_julia_multi" + idx,
		"label_mutation_julia_c_mul" + idx,
		"label_mutation_julia_c_power" + idx,
		"label_mutation_julia_c_radius" + idx,
		"label_mutation_julia_pulse_freq" + idx,
		"label_mutation_julia_absorb" + idx,
		"label_c_rotation" + idx,
		"label_m_bius_a" + idx,
		"label_m_bius_b" + idx,
		"label_m_bius_d" + idx,
		"label_pulse_amp" + idx,
		"label_julia_noise_freq" + idx,
		"label_julia_noise_amp" + idx,
		"label_fourier_c2" + idx,
		"label_fourier_c3" + idx,
		"label_bipolar_cr" + idx,
		// Fine-tune labels
		"label_mutation_julia_ctransform_iter_start_l" + idx,
		"label_mutation_julia_ctransform_iter_stop_l" + idx,
		"label_mutation_julia_ctransform_strength_l" + idx,
		"label_mutation_julia_dynamic_iter_start_l" + idx,
		"label_mutation_julia_dynamic_iter_stop_l" + idx,
		"label_mutation_julia_dynamic_strength_l" + idx,
		"label_mutation_julia_multi_iter_start_l" + idx,
		"label_mutation_julia_multi_iter_stop_l" + idx,
		"label_mutation_julia_multi_strength_l" + idx,
		"label_mutation_julia_injection_strength_l" + idx,
		"label_mutation_julia_de_factor_l" + idx,
		"label_mutation_julia_ext_header" + idx,
		"label_mutation_julia_decay_rate_l" + idx,
		"label_mutation_julia_spiral_angle_l" + idx,
		"label_mutation_julia_chaos_r_l" + idx,
		"label_mutation_julia_threshold_l" + idx,
		"label_mutation_julia_gradient_end_l" + idx,
		"label_mutation_julia_box_fold_limit_l" + idx,
		"label_mutation_julia_start_epsilon_l" + idx,
		"label_mutation_julia_layer_c2_l" + idx,
		"label_mutation_julia_layer_c2_yz_l" + idx,
		"label_mutation_julia_dist_band_l" + idx,
		"label_mutation_julia_dist_band_far_l" + idx
	};
	MarkFormulaHiddenWidgets(juliaWidgets, !juliaUseful);

	// Orbit trap: less useful for transforms
	QStringList orbitWidgets = {
		"comboBox_mutation_orbit_trap" + idx,
		"label_mutation_orbit_trap" + idx
	};
	MarkFormulaHiddenWidgets(orbitWidgets, isTransform);

	UpdateMutationGrayOut();
}

void cDockMutationTab::UpdateMutationGrayOut() const
{
	if (!ui->groupCheck_mutation_enabled) return;

	// Helper: set enabled state AND orange color for active parameters
	auto styleWidget = [this](QWidget *w, bool enabled) {
		if (!w) return;
		if (m_formulaHiddenWidgets.contains(w->objectName()))
			enabled = false;
		w->setEnabled(enabled);
		if (enabled) {
			w->setStyleSheet("color: #FFA500; font-weight: bold;");
		} else {
			w->setStyleSheet("color: #AAAAAA;");
		}
	};

	// Helper: default group children to gray; registry enables per-type active params
	auto grayOutGroupSystem = [this, styleWidget](QComboBox *combo, QGroupBox *group) {
		if (!combo || !group) return;
		const bool groupOn = ui->groupCheck_mutation_enabled->isChecked() && group->isChecked();
		styleWidget(combo, groupOn);
		QList<QWidget *> children = group->findChildren<QWidget *>();
		for (QWidget *w : children)
		{
			if (w == combo || w == group) continue;
			// Sla nested groupboxen over: die hebben eigen checked-state
			if (qobject_cast<QGroupBox *>(w)) continue;
			QString name = w->objectName();
			if (name.contains("section_weight") || name.contains("reset_weights"))
			{
				styleWidget(w, groupOn);
				continue;
			}
			if (qobject_cast<QLabel *>(w) && name.contains("_type"))
			{
				styleWidget(w, groupOn);
				continue;
			}
			styleWidget(w, false);
		}
	};

	// Systems with their own GroupBox (simple on/off)
	grayOutGroupSystem(MUT_CLIP_INV->comboBox_mutation_inv_type, MUT_CLIP_INV->groupCheck_mutation_inversion_enabled);
	grayOutGroupSystem(MUT_CLIP_INV->comboBox_mutation_clip_type, MUT_CLIP_INV->groupCheck_mutation_clip_enabled);
	grayOutGroupSystem(MUT_JOS_PK->comboBox_mutation_jos_de_type, MUT_JOS_PK->groupCheck_mutation_jos_leys_enabled);
	grayOutGroupSystem(MUT_JOS_PK->comboBox_mutation_pk_de_type, MUT_JOS_PK->groupCheck_mutation_pk_enabled);
	grayOutGroupSystem(MUT_SYS1->comboBox_mutation_mb_math_type, MUT_SYS1->groupCheck_mutation_mb_math_enabled);
	grayOutGroupSystem(MUT_SYS1->comboBox_mutation_warp_dist_type, MUT_SYS1->groupCheck_mutation_warp_dist_enabled);
	grayOutGroupSystem(MUT_SYS1->comboBox_mutation_sym_kal_type, MUT_SYS1->groupCheck_mutation_symmetry_enabled);
	grayOutGroupSystem(MUT_SYS2->comboBox_mutation_abox_type, MUT_SYS2->groupCheck_mutation_abox_enabled);
	grayOutGroupSystem(MUT_SYS2->comboBox_mutation_noise_type, MUT_SYS2->groupCheck_mutation_noise_enabled);
	grayOutGroupSystem(MUT_SYS2->comboBox_mutation_orbit_trap_type, MUT_SYS2->groupCheck_mutation_orbit_trap_enabled);
	grayOutGroupSystem(MUT_SYS3->comboBox_mutation_torus_type, MUT_SYS3->groupCheck_mutation_torus_enabled);
	grayOutGroupSystem(MUT_SYS3->comboBox_mutation_clamp_type, MUT_SYS3->groupCheck_mutation_clamp_enabled);
	grayOutGroupSystem(MUT_SYS3->comboBox_mutation_jb_type, MUT_SYS3->groupCheck_mutation_jb_enabled);
	grayOutGroupSystem(MUT_TAIL->comboBox_mutation_md_type, MUT_TAIL->groupCheck_mutation_md_enabled);
	grayOutGroupSystem(MUT_TAIL->comboBox_mutation_as_type, MUT_TAIL->groupCheck_mutation_as_enabled);
	grayOutGroupSystem(MUT_TAIL->comboBox_mutation_sm_type, MUT_TAIL->groupCheck_mutation_sm_enabled);
	grayOutGroupSystem(MUT_TAIL->comboBox_mutation_blockify_type, MUT_TAIL->groupCheck_mutation_blockify_enabled);
	grayOutGroupSystem(MUT_TAIL->comboBox_mutation_tile_type, MUT_TAIL->groupCheck_mutation_tile_enabled);

	// --- Per-type parameter gray-out (registry-driven) ---
	{
		QHash<QString, QPair<QGroupBox *, QComboBox *>> registrySystems;
		registrySystems.insert("jos", {MUT_JOS_PK->groupCheck_mutation_jos_leys_enabled, MUT_JOS_PK->comboBox_mutation_jos_de_type});
		registrySystems.insert("pk", {MUT_JOS_PK->groupCheck_mutation_pk_enabled, MUT_JOS_PK->comboBox_mutation_pk_de_type});
		registrySystems.insert("mb", {MUT_SYS1->groupCheck_mutation_mb_math_enabled, MUT_SYS1->comboBox_mutation_mb_math_type});
		registrySystems.insert("wd", {MUT_SYS1->groupCheck_mutation_warp_dist_enabled, MUT_SYS1->comboBox_mutation_warp_dist_type});
		registrySystems.insert("sk", {MUT_SYS1->groupCheck_mutation_symmetry_enabled, MUT_SYS1->comboBox_mutation_sym_kal_type});
		registrySystems.insert("noise", {MUT_SYS2->groupCheck_mutation_noise_enabled, MUT_SYS2->comboBox_mutation_noise_type});
		registrySystems.insert("orbit", {MUT_SYS2->groupCheck_mutation_orbit_trap_enabled, MUT_SYS2->comboBox_mutation_orbit_trap_type});
		registrySystems.insert("torus", {MUT_SYS3->groupCheck_mutation_torus_enabled, MUT_SYS3->comboBox_mutation_torus_type});
		registrySystems.insert("ab", {MUT_SYS2->groupCheck_mutation_abox_enabled, MUT_SYS2->comboBox_mutation_abox_type});
		registrySystems.insert("as", {MUT_TAIL->groupCheck_mutation_as_enabled, MUT_TAIL->comboBox_mutation_as_type});
		registrySystems.insert("sm", {MUT_TAIL->groupCheck_mutation_sm_enabled, MUT_TAIL->comboBox_mutation_sm_type});
		registrySystems.insert("blockify", {MUT_TAIL->groupCheck_mutation_blockify_enabled, MUT_TAIL->comboBox_mutation_blockify_type});
		registrySystems.insert("tile", {MUT_TAIL->groupCheck_mutation_tile_enabled, MUT_TAIL->comboBox_mutation_tile_type});
		registrySystems.insert("clamp", {MUT_SYS3->groupCheck_mutation_clamp_enabled, MUT_SYS3->comboBox_mutation_clamp_type});
		registrySystems.insert("jb", {MUT_SYS3->groupCheck_mutation_jb_enabled, MUT_SYS3->comboBox_mutation_jb_type});
		registrySystems.insert("md", {MUT_TAIL->groupCheck_mutation_md_enabled, MUT_TAIL->comboBox_mutation_md_type});
		registrySystems.insert("clip", {MUT_CLIP_INV->groupCheck_mutation_clip_enabled, MUT_CLIP_INV->comboBox_mutation_clip_type});
		registrySystems.insert("inv", {MUT_CLIP_INV->groupCheck_mutation_inversion_enabled, MUT_CLIP_INV->comboBox_mutation_inv_type});
		cMutationUiRegistry::ApplyPerTypeParamGrayOut(tabIndex, registrySystems, styleWidget);
	}

	// Systems inside the main mutation group (no own GroupBox)
	bool mutationEnabled = ui->groupCheck_mutation_enabled->isChecked();
	QString suffix = "_" + QString::number(tabIndex + 1);

	QList<QWidget *> allMutationChildren = ui->groupCheck_mutation_enabled->findChildren<QWidget *>();

	auto applyInlineSubsystemGrayOut = [&](const char *systemId, QComboBox *typeCombo,
		const QString &typeLabelBase, bool systemActive,
		const std::function<bool(const QString &)> &matches) {
		if (!typeCombo) return;
		const QString comboName = typeCombo->objectName();
		const QString typeLabelName = typeLabelBase + suffix;
		for (QWidget *w : allMutationChildren)
		{
			QString name = w->objectName();
			if (!matches(name)) continue;
			if (name == comboName || name == typeLabelName)
				styleWidget(w, mutationEnabled);
			else
				styleWidget(w, false);
		}
		cMutationUiRegistry::ApplyInlinePerTypeParamGrayOut(tabIndex, systemId,
			ui->groupCheck_mutation_enabled, typeCombo, systemActive, styleWidget);
	};

	// Fold system (per-type parameter gray-out via registry)
	{
		const bool foldActive = mutationEnabled && ui->comboBox_mutation_fold_type->currentIndex() != 0;
		applyInlineSubsystemGrayOut("fold", ui->comboBox_mutation_fold_type, "label_mutation_fold_type",
			foldActive, [](const QString &name) {
				return name.contains("fold") && !name.contains("box_fold");
			});
		if (ui->comboBox_mutation_fold_position)
			styleWidget(ui->comboBox_mutation_fold_position, foldActive);
	}

	// Warp system (basic warp, not warp_dist)
	{
		const bool warpActive = mutationEnabled && ui->comboBox_mutation_warp_type->currentIndex() != 0;
		applyInlineSubsystemGrayOut("warp", ui->comboBox_mutation_warp_type, "label_mutation_warp_type",
			warpActive, [](const QString &name) {
				return name.contains("warp") && !name.contains("warp_dist") && !name.contains("wd_");
			});
	}

	// Math system (inline, not mb_math DE panel)
	{
		const bool mathActive = mutationEnabled && ui->comboBox_mutation_math_type->currentIndex() != 0;
		applyInlineSubsystemGrayOut("math", ui->comboBox_mutation_math_type, "label_mutation_math_type",
			mathActive, [](const QString &name) {
				return name.contains("math") && !name.contains("mb_math");
			});
	}

	// Swizzle: combo + label always active when mutation enabled
	{
		for (QWidget *w : allMutationChildren)
		{
			QString name = w->objectName();
			if (name == "comboBox_mutation_swizzle" + suffix
				|| name == "label_mutation_swizzle" + suffix)
				styleWidget(w, mutationEnabled);
		}
	}

	// Orbit trap (in main group): per-type gray-out via registry
	{
		const bool orbitActive = mutationEnabled && ui->comboBox_mutation_orbit_trap->currentIndex() != 0;
		applyInlineSubsystemGrayOut("trap", ui->comboBox_mutation_orbit_trap, "label_mutation_orbit_trap",
			orbitActive, [](const QString &name) {
				return name.contains("orbit_trap") || name.contains("trap_radius");
			});
	}

	// --- Julia system per-parameter gray-out (registry-driven) ---
	if (mutationEnabled)
	{
		sMutationJuliaUiContext juliaCtx;
		juliaCtx.injection = ui->comboBox_mutation_julia_injection->currentIndex();
		juliaCtx.cTransform = ui->comboBox_mutation_julia_c_transform->currentIndex();
		juliaCtx.dynamic = ui->comboBox_mutation_julia_dynamic->currentIndex();
		juliaCtx.multi = ui->comboBox_mutation_julia_multi->currentIndex();
		juliaCtx.start = ui->comboBox_mutation_julia_start->currentIndex();
		cMutationUiRegistry::ApplyJuliaGrayOut(
			tabIndex, ui->groupCheck_mutation_enabled, juliaCtx, styleWidget);
	}
	else
	{
		for (QWidget *w : allMutationChildren)
		{
			QString name = w->objectName();
			if (name.contains("julia"))
				styleWidget(w, false);
		}
	}

	// DE tweak combo + gray inactive params before registry pass
	{
		const bool deActive = mutationEnabled && ui->comboBox_mutation_de_tweak->currentIndex() != 0;
		for (QWidget *w : allMutationChildren)
		{
			QString name = w->objectName();
			if (name == "comboBox_mutation_de_tweak" + suffix)
				styleWidget(w, mutationEnabled);
			else if (name == "label_mutation_de_tweak" + suffix)
				styleWidget(w, deActive);
			else if (name.contains("de_tweak") || name.contains("de_scale")
				|| name.contains("de_iter") || name == "label_mutation_de_iter" + suffix
				|| name == "label_mutation_de_iter_s" + suffix
				|| name == "label_mutation_de_iter_e" + suffix)
				styleWidget(w, false);
		}
		cMutationUiRegistry::ApplyInlinePerTypeParamGrayOut(tabIndex, "de",
			ui->groupCheck_mutation_enabled, ui->comboBox_mutation_de_tweak, deActive, styleWidget);
	}

	// Pre/post transform, global iteration, z-mix, curvature (always active when mutation on)
	auto isGlobalAlwaysActiveWidget = [](const QString &name) {
		if (name.contains("mutation_pre_")) return true;
		if (name.contains("mutation_post_")) return true;
		if (name.contains("mutation_iteration_")) return true;
		if (name.startsWith("label_mutation_iter")) return true;
		if (name.contains("mutation_z_mix")) return true;
		if (name.contains("curvature_coloring")) return true;
		return false;
	};
	for (QWidget *w : allMutationChildren)
	{
		if (isGlobalAlwaysActiveWidget(w->objectName()))
			styleWidget(w, mutationEnabled);
	}

	// Top bar: master weight + weight buttons
	styleWidget(ui->spinbox_mutation_master_weight, mutationEnabled);
	styleWidget(ui->label_mutation_master_weight, mutationEnabled);

	auto styleTopButton = [&](QPushButton *btn, bool orangeWhenActive) {
		if (!btn) return;
		btn->setEnabled(mutationEnabled);
		if (!mutationEnabled)
			btn->setStyleSheet("color: #AAAAAA;");
		else if (orangeWhenActive)
			btn->setStyleSheet("color: #FFA500; font-weight: bold;");
		else
			btn->setStyleSheet("font-weight: bold; color: #FF4444;");
	};
	styleTopButton(ui->pushButton_mutation_randomize_weights, true);
	styleTopButton(ui->pushButton_mutation_reset_weights, true);
	styleTopButton(ui->pushButton_mutation_reset_all_top, false);
	if (ui->pushButton_mutation_randomize_weights_2)
		styleTopButton(ui->pushButton_mutation_randomize_weights_2, true);
	if (ui->pushButton_mutation_reset_all)
		styleTopButton(ui->pushButton_mutation_reset_all, false);
}

void cDockMutationTab::slotPressedButtonMutationReset()
{
	CHECK_PARAMS();
	const int idx = tabIndex + 1;
	// Reset all mutation params to defaults (keep enabled state unchanged)

	auto setD = [this, idx](const QString &name, double val) {
		params->Set(name + "_" + QString::number(idx), val);
	};
	auto setI = [this, idx](const QString &name, int val) {
		params->Set(name + "_" + QString::number(idx), val);
	};
	auto setB = [this, idx](const QString &name, bool val) {
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
	setD("mutation_warp_amplitude", 0.5);
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
	setD("mutation_de_tweak_p1", 0.1);
	setD("mutation_de_tweak_p2", 10.0);
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
	params->Set("mutation_julia_c_rot_" + QString::number(idx), CVector3(0.0, 0.0, 0.0));
	setD("mutation_julia_c_mobius_a", 1.0);
	setD("mutation_julia_c_mobius_b", 0.0);
	setD("mutation_julia_c_mobius_d", 1.0);
	setD("mutation_julia_pulse_freq", 1.0);
	setD("mutation_julia_pulse_amp", 1.0);
	setD("mutation_julia_absorb", 0.0);
	setD("mutation_julia_noise_freq", 1.0);
	setD("mutation_julia_noise_amp", 0.1);
	params->Set("mutation_julia_fourier_c2_" + QString::number(idx), CVector3(0.0, 0.0, 0.0));
	params->Set("mutation_julia_fourier_c3_" + QString::number(idx), CVector3(0.0, 0.0, 0.0));
	params->Set("mutation_julia_bipolar_cr_" + QString::number(idx), CVector3(0.0, 0.0, 0.0));
	// Julia fine-tune
	setI("mutation_julia_ctransform_iter_start", 0);
	setI("mutation_julia_ctransform_iter_stop", 10000);
	setI("mutation_julia_dynamic_iter_start", 0);
	setI("mutation_julia_dynamic_iter_stop", 10000);
	setI("mutation_julia_multi_iter_start", 0);
	setI("mutation_julia_multi_iter_stop", 10000);
	setD("mutation_julia_ctransform_strength", 1.0);
	setD("mutation_julia_dynamic_strength", 1.0);
	setD("mutation_julia_multi_strength", 1.0);
	setD("mutation_julia_injection_strength", 1.0);
	setD("mutation_julia_de_factor", 1.0);
	setD("mutation_julia_decay_rate", 0.1);
	setD("mutation_julia_spiral_angle", 15.0);
	setD("mutation_julia_chaos_r", 3.8);
	setD("mutation_julia_threshold", 1.0);
	setD("mutation_julia_gradient_end", 0.0);
	setD("mutation_julia_box_fold_limit", 1.0);
	setD("mutation_julia_start_epsilon", 0.001);
	params->Set("mutation_julia_layer_c2_" + QString::number(idx), CVector3(0.0, 0.0, 0.0));
	setD("mutation_julia_dist_band_mid", 1.0);
	setD("mutation_julia_dist_band_far", 2.0);
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


void cDockMutationTab::slotPressedButtonRandomizeWeights()
{
	// Randomiseer alle weight spinboxen in deze tab
	QList<QDoubleSpinBox *> spinboxes = findChildren<QDoubleSpinBox *>();
	for (QDoubleSpinBox *sb : spinboxes)
	{
		if (sb->objectName().contains("weight", Qt::CaseInsensitive))
		{
			double range = sb->maximum() - sb->minimum();
			sb->setValue(sb->minimum() + (double)rand() / RAND_MAX * range);
		}
	}
}

void cDockMutationTab::slotPressedButtonResetWeights()
{
	// Reset alle weight spinboxen naar 1.0
	QList<QDoubleSpinBox *> spinboxes = findChildren<QDoubleSpinBox *>();
	for (QDoubleSpinBox *sb : spinboxes)
	{
		if (sb->objectName().contains("weight", Qt::CaseInsensitive))
		{
			sb->setValue(1.0);
		}
	}
}

void cDockMutationTab::slotPressedButtonResetSectionWeights()
{
	// Reset weight spinboxen in de actieve sectie naar 1.0
	// Zoek de parent groupbox van de knop die het signaal stuurde
	QPushButton *btn = qobject_cast<QPushButton *>(sender());
	if (!btn) return;
	QGroupBox *parentGroup = nullptr;
	QWidget *p = btn->parentWidget();
	while (p)
	{
		parentGroup = qobject_cast<QGroupBox *>(p);
		if (parentGroup) break;
		p = p->parentWidget();
	}
	if (!parentGroup) return;
	QList<QDoubleSpinBox *> spinboxes = parentGroup->findChildren<QDoubleSpinBox *>();
	for (QDoubleSpinBox *sb : spinboxes)
	{
		if (sb->objectName().contains("weight", Qt::CaseInsensitive))
		{
			sb->setValue(1.0);
		}
	}
}
