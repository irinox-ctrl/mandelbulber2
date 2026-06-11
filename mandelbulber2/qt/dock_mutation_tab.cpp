#include "dock_mutation_tab.h"
#include "ui_dock_mutation_tab.h"

#include "src/automated_widgets.hpp"
#include "src/fractal_container.hpp"
#include "src/initparameters.hpp"
#include "src/interface.hpp"
#include "src/write_log.hpp"

#include "formula/definition/all_fractal_list.hpp"

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
		ui->comboBox_mutation_julia_injection,
		ui->comboBox_mutation_julia_start,
		ui->comboBox_mutation_julia_c_transform,
		ui->comboBox_mutation_julia_dynamic,
		ui->comboBox_mutation_julia_multi,
	};
	for (QComboBox *combo : mutationTypeCombos)
	{
		if (combo) connect(combo, QOverload<int>::of(&QComboBox::currentIndexChanged),
			this, &cDockMutationTab::UpdateMutationGrayOut);
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
		if (!group) continue;

		// Accordion: als 1 sectie open gaat, sluiten alle andere
		connect(group, &QGroupBox::toggled, this, [this, group, mutationGroups](bool checked) {
			// Als deze group wordt GEOPEND, sluit alle ANDERE groups
			if (checked) {
				for (QGroupBox *other : mutationGroups) {
					if (other != group && other->isChecked()) {
						other->setChecked(false);
					}
				}
			}

			// Pas de hoogte aan
			int height = checked ? 16777215 : 28; // 28px voor titelbar
			group->setMaximumHeight(height);
			group->setSizePolicy(QSizePolicy::Expanding, 
			                    checked ? QSizePolicy::Preferred : QSizePolicy::Fixed);
		});

		// Initieel instellen
		group->setMaximumHeight(group->isChecked() ? 16777215 : 28);
		group->setSizePolicy(QSizePolicy::Expanding, 
		                    group->isChecked() ? QSizePolicy::Preferred : QSizePolicy::Fixed);
	}

	connect(ui->pushButton_mutation_reset, &QPushButton::clicked, this,
		&cDockMutationTab::slotPressedButtonMutationReset);

	// Zorg dat alle spinboxen breed genoeg zijn om cijfers te tonen
	const int minSpinWidth = 72;
	for (QAbstractSpinBox *sb : findChildren<QAbstractSpinBox *>())
	{
		sb->setMinimumWidth(minSpinWidth);
		sb->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
	}
}

void cDockMutationTab::SynchronizeInterface(
	std::shared_ptr<cParameterContainer> par, qInterface::enumReadWrite mode)
{
	SynchronizeInterfaceWindow(this, par, mode);
}

void cDockMutationTab::SetMutationWidgetsEnabled(const QStringList &names, bool enabled) const
{
	for (const QString &name : names)
	{
		QWidget *w = ui->groupCheck_mutation_enabled->findChild<QWidget *>(name);
		if (w) w->setEnabled(enabled);
	}
}

void cDockMutationTab::UpdateMutationFieldVisibility(int formulaIndex) const
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
		"label_bipolar_cr" + idx
	};
	SetMutationWidgetsEnabled(juliaWidgets, juliaUseful);

	// Orbit trap: less useful for transforms
	QStringList orbitWidgets = {
		"comboBox_mutation_orbit_trap" + idx,
		"label_mutation_orbit_trap" + idx
	};
	SetMutationWidgetsEnabled(orbitWidgets, !isTransform);
}

void cDockMutationTab::UpdateMutationGrayOut() const
{
	// Helper: set enabled state AND orange color for active parameters
	auto styleWidget = [&](QWidget *w, bool enabled) {
		if (!w) return;
		w->setEnabled(enabled);
		if (enabled) {
			w->setStyleSheet("color: #FFA500; font-weight: bold;");
		} else {
			w->setStyleSheet("color: #AAAAAA;");
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
			// Sla nested groupboxen over: die hebben eigen checked-state
			if (qobject_cast<QGroupBox *>(w)) continue;
			// Sla QFrame/QAbstractScrollArea over: dit zijn popup containers van QComboBox
			if (qobject_cast<QFrame *>(w) && w->windowFlags() & Qt::Popup) continue;
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

	// --- Julia system per-parameter gray-out ---
	{
		QString suffix = "_" + QString::number(tabIndex + 1);
		int juliaInjection = ui->comboBox_mutation_julia_injection->currentIndex();
		int juliaCTransform = ui->comboBox_mutation_julia_c_transform->currentIndex();
		int juliaDynamic = ui->comboBox_mutation_julia_dynamic->currentIndex();
		int juliaMulti = ui->comboBox_mutation_julia_multi->currentIndex();

		bool injectionActive = juliaInjection != 0;

		auto setJuliaWidget = [&](const QString &baseName, bool enabled) {
			QString fullName = baseName + suffix;
			for (QWidget *w : allMutationChildren)
			{
				if (w->objectName() == fullName)
				{
					styleWidget(w, enabled);
					break;
				}
			}
		};

		// Start mode, injection, iter range: always relevant
		setJuliaWidget("comboBox_mutation_julia_start", true);
		setJuliaWidget("label_mutation_julia_start", true);
		setJuliaWidget("comboBox_mutation_julia_injection", true);
		setJuliaWidget("label_mutation_julia_injection", true);
		setJuliaWidget("spinboxInt_mutation_julia_iter_start", true);
		setJuliaWidget("label_mutation_julia_iter_s", true);
		setJuliaWidget("spinboxInt_mutation_julia_iter_stop", true);
		setJuliaWidget("label_mutation_julia_iter_e", true);
		setJuliaWidget("label_mutation_julia_iter", true);

		// C-transform and base params
		setJuliaWidget("comboBox_mutation_julia_c_transform", injectionActive);
		setJuliaWidget("label_mutation_julia_c_transform", injectionActive);
		setJuliaWidget("spinbox_mutation_julia_c_mul", injectionActive);
		setJuliaWidget("label_mutation_julia_c_mul", injectionActive);

		// C-transform specific params
		setJuliaWidget("spinboxd3_mutation_julia_c_rot_x", injectionActive && juliaCTransform == 3);
		setJuliaWidget("spinboxd3_mutation_julia_c_rot_y", injectionActive && juliaCTransform == 3);
		setJuliaWidget("spinboxd3_mutation_julia_c_rot_z", injectionActive && juliaCTransform == 3);
		setJuliaWidget("label_c_rotation", injectionActive && juliaCTransform == 3);

		setJuliaWidget("spinbox_mutation_julia_c_radius", injectionActive && juliaCTransform == 1);
		setJuliaWidget("label_mutation_julia_c_radius", injectionActive && juliaCTransform == 1);

		setJuliaWidget("spinboxd_mutation_julia_c_mobius_a", injectionActive && juliaCTransform == 2);
		setJuliaWidget("spinboxd_mutation_julia_c_mobius_b", injectionActive && juliaCTransform == 2);
		setJuliaWidget("spinboxd_mutation_julia_c_mobius_d", injectionActive && juliaCTransform == 2);
		setJuliaWidget("label_m_bius_a", injectionActive && juliaCTransform == 2);
		setJuliaWidget("label_m_bius_b", injectionActive && juliaCTransform == 2);
		setJuliaWidget("label_m_bius_d", injectionActive && juliaCTransform == 2);

		setJuliaWidget("spinbox_mutation_julia_c_power", injectionActive && juliaCTransform == 4);
		setJuliaWidget("label_mutation_julia_c_power", injectionActive && juliaCTransform == 4);

		// Dynamic and its params
		setJuliaWidget("comboBox_mutation_julia_dynamic", injectionActive);
		setJuliaWidget("label_mutation_julia_dynamic", injectionActive);

		setJuliaWidget("spinbox_mutation_julia_pulse_freq", injectionActive && juliaDynamic == 2);
		setJuliaWidget("label_mutation_julia_pulse_freq", injectionActive && juliaDynamic == 2);
		setJuliaWidget("spinboxd_mutation_julia_pulse_amp", injectionActive && juliaDynamic == 2);
		setJuliaWidget("label_pulse_amp", injectionActive && juliaDynamic == 2);

		setJuliaWidget("spinbox_mutation_julia_absorb", injectionActive && juliaDynamic == 4);
		setJuliaWidget("label_mutation_julia_absorb", injectionActive && juliaDynamic == 4);

		// Multi and its params
		setJuliaWidget("comboBox_mutation_julia_multi", injectionActive);
		setJuliaWidget("label_mutation_julia_multi", injectionActive);

		setJuliaWidget("spinboxd_mutation_julia_noise_freq", injectionActive && juliaMulti == 4);
		setJuliaWidget("label_julia_noise_freq", injectionActive && juliaMulti == 4);
		setJuliaWidget("spinboxd_mutation_julia_noise_amp", injectionActive && juliaMulti == 4);
		setJuliaWidget("label_julia_noise_amp", injectionActive && juliaMulti == 4);

		setJuliaWidget("spinboxd3_mutation_julia_fourier_c2_x", injectionActive && juliaMulti == 3);
		setJuliaWidget("spinboxd3_mutation_julia_fourier_c2_y", injectionActive && juliaMulti == 3);
		setJuliaWidget("spinboxd3_mutation_julia_fourier_c2_z", injectionActive && juliaMulti == 3);
		setJuliaWidget("label_fourier_c2", injectionActive && juliaMulti == 3);

		setJuliaWidget("spinboxd3_mutation_julia_fourier_c3_x", injectionActive && juliaMulti == 3);
		setJuliaWidget("spinboxd3_mutation_julia_fourier_c3_y", injectionActive && juliaMulti == 3);
		setJuliaWidget("spinboxd3_mutation_julia_fourier_c3_z", injectionActive && juliaMulti == 3);
		setJuliaWidget("label_fourier_c3", injectionActive && juliaMulti == 3);

		setJuliaWidget("spinboxd3_mutation_julia_bipolar_cr_x", injectionActive && juliaMulti == 1);
		setJuliaWidget("spinboxd3_mutation_julia_bipolar_cr_y", injectionActive && juliaMulti == 1);
		setJuliaWidget("spinboxd3_mutation_julia_bipolar_cr_z", injectionActive && juliaMulti == 1);
		setJuliaWidget("label_bipolar_cr", injectionActive && juliaMulti == 1);
	}
}

void cDockMutationTab::slotPressedButtonMutationReset()
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
	setD("mutation_julia_c_rot_x", 0.0);
	setD("mutation_julia_c_rot_y", 0.0);
	setD("mutation_julia_c_rot_z", 0.0);
	setD("mutation_julia_c_mobius_a", 1.0);
	setD("mutation_julia_c_mobius_b", 0.0);
	setD("mutation_julia_c_mobius_d", 1.0);
	setD("mutation_julia_pulse_amp", 1.0);
	setD("mutation_julia_noise_freq", 1.0);
	setD("mutation_julia_noise_amp", 0.1);
	params->Set("mutation_julia_fourier_c2_" + QString::number(idx), CVector3(0.0, 0.0, 0.0));
	params->Set("mutation_julia_fourier_c3_" + QString::number(idx), CVector3(0.0, 0.0, 0.0));
	params->Set("mutation_julia_bipolar_cr_" + QString::number(idx), CVector3(0.0, 0.0, 0.0));
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
