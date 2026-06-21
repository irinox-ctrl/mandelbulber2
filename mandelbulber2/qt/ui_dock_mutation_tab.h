/********************************************************************************
** Form generated from reading UI file 'dock_mutation_tab.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCK_MUTATION_TAB_H
#define UI_DOCK_MUTATION_TAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <mutation_clip_inv_panel.h>
#include <mutation_jos_pk_panel.h>
#include <mutation_systems_panel.h>
#include <mutation_tail_panel.h>
#include "my_check_box.h"
#include "my_double_spin_box.h"
#include "my_group_box.h"
#include "my_spin_box.h"

QT_BEGIN_NAMESPACE

class Ui_cDockMutationTab
{
public:
    QVBoxLayout *verticalLayout_mutation_dock;
    QHBoxLayout *horizontalLayout_mutation_top;
    QPushButton *pushButton_mutation_randomize_weights;
    QPushButton *pushButton_mutation_reset_weights;
    QPushButton *pushButton_mutation_reset_all_top;
    QLabel *label_mutation_master_weight;
    MyDoubleSpinBox *spinbox_mutation_master_weight;
    QSpacerItem *horizontalSpacer_mutation_top;
    MyGroupBox *groupCheck_mutation_enabled;
    QGridLayout *gridLayout_mutation;
    QLabel *label_mutation_pre_rotation;
    QLabel *label_mutation_pre_rot_ax;
    MyDoubleSpinBox *spinbox_mutation_pre_rotation_ax;
    QLabel *label_mutation_pre_rot_ay;
    MyDoubleSpinBox *spinbox_mutation_pre_rotation_ay;
    QLabel *label_mutation_pre_rot_az;
    MyDoubleSpinBox *spinbox_mutation_pre_rotation_az;
    QLabel *label_mutation_pre_scale;
    MyDoubleSpinBox *spinbox_mutation_pre_scale;
    QLabel *label_mutation_pre_offset;
    QLabel *label_mutation_preoff_ax;
    MyDoubleSpinBox *spinbox_mutation_pre_offset_ax;
    QLabel *label_mutation_preoff_ay;
    MyDoubleSpinBox *spinbox_mutation_pre_offset_ay;
    QLabel *label_mutation_preoff_az;
    MyDoubleSpinBox *spinbox_mutation_pre_offset_az;
    QLabel *label_mutation_pre_abs;
    MyCheckBox *checkBox_mutation_pre_abs_ax;
    MyCheckBox *checkBox_mutation_pre_abs_ay;
    MyCheckBox *checkBox_mutation_pre_abs_az;
    QLabel *label_mutation_post_rotation;
    QLabel *label_mutation_post_rot_ax;
    MyDoubleSpinBox *spinbox_mutation_post_rotation_ax;
    QLabel *label_mutation_post_rot_ay;
    MyDoubleSpinBox *spinbox_mutation_post_rotation_ay;
    QLabel *label_mutation_post_rot_az;
    MyDoubleSpinBox *spinbox_mutation_post_rotation_az;
    QLabel *label_mutation_post_scale;
    MyDoubleSpinBox *spinbox_mutation_post_scale;
    QLabel *label_mutation_post_offset;
    QLabel *label_mutation_postoff_ax;
    MyDoubleSpinBox *spinbox_mutation_post_offset_ax;
    QLabel *label_mutation_postoff_ay;
    MyDoubleSpinBox *spinbox_mutation_post_offset_ay;
    QLabel *label_mutation_postoff_az;
    MyDoubleSpinBox *spinbox_mutation_post_offset_az;
    QLabel *label_mutation_swizzle;
    QComboBox *comboBox_mutation_swizzle;
    QLabel *label_mutation_fold_type;
    QComboBox *comboBox_mutation_fold_type;
    QLabel *label_mutation_fold_limit;
    MyDoubleSpinBox *spinbox_mutation_fold_limit;
    QLabel *label_mutation_fold_value;
    MyDoubleSpinBox *spinbox_mutation_fold_value;
    QLabel *label_mutation_warp_type;
    QComboBox *comboBox_mutation_warp_type;
    QLabel *label_mutation_warp_freq;
    MyDoubleSpinBox *spinbox_mutation_warp_frequency;
    QLabel *label_mutation_warp_amp;
    MyDoubleSpinBox *spinbox_mutation_warp_amplitude;
    QLabel *label_mutation_fold_position;
    QComboBox *comboBox_mutation_fold_position;
    QLabel *label_mutation_kaleidoscope_sides;
    MySpinBox *spinboxInt_mutation_kaleidoscope_sides;
    QLabel *label_mutation_iter_range;
    QLabel *label_mutation_iter_start;
    MySpinBox *spinboxInt_mutation_iteration_start;
    QLabel *label_mutation_iter_stop;
    MySpinBox *spinboxInt_mutation_iteration_stop;
    QLabel *label_mutation_math_type;
    QComboBox *comboBox_mutation_math_type;
    QLabel *label_mutation_math_mix;
    MyDoubleSpinBox *spinbox_mutation_math_mix;
    QLabel *label_mutation_math_p1;
    MyDoubleSpinBox *spinbox_mutation_math_p1;
    QLabel *label_mutation_math_p2;
    MyDoubleSpinBox *spinbox_mutation_math_p2;
    QLabel *label_mutation_math_p3;
    MyDoubleSpinBox *spinbox_mutation_math_p3;
    MyDoubleSpinBox *spinbox_mutation_math_p4;
    QLabel *label_mutation_math_p5;
    MyDoubleSpinBox *spinbox_mutation_math_p5;
    QLabel *label_mutation_math_p6;
    MyDoubleSpinBox *spinbox_mutation_math_p6;
    QLabel *label_mutation_math_p7;
    MyDoubleSpinBox *spinbox_mutation_math_p7;
    MyDoubleSpinBox *spinbox_mutation_math_p8;
    QLabel *label_mutation_z_mix;
    MyDoubleSpinBox *spinbox_mutation_z_mix;
    QLabel *label_mutation_de_scale;
    MyDoubleSpinBox *spinbox_mutation_de_scale;
    QLabel *label_mutation_de_tweak;
    QComboBox *comboBox_mutation_de_tweak;
    QLabel *label_mutation_de_tweak_p1;
    MyDoubleSpinBox *spinbox_mutation_de_tweak_p1;
    QLabel *label_mutation_de_tweak_p2;
    MyDoubleSpinBox *spinbox_mutation_de_tweak_p2;
    QLabel *label_mutation_orbit_trap;
    QComboBox *comboBox_mutation_orbit_trap;
    QLabel *label_mutation_trap_radius;
    MyDoubleSpinBox *spinbox_mutation_trap_radius;
    QCheckBox *checkBox_mutation_curvature_coloring;
    QLabel *label_mutation_julia_injection;
    QComboBox *comboBox_mutation_julia_injection;
    QLabel *label_mutation_julia_start;
    QComboBox *comboBox_mutation_julia_start;
    QLabel *label_mutation_julia_c_transform;
    QComboBox *comboBox_mutation_julia_c_transform;
    QLabel *label_mutation_julia_dynamic;
    QComboBox *comboBox_mutation_julia_dynamic;
    QLabel *label_mutation_julia_multi;
    QComboBox *comboBox_mutation_julia_multi;
    QLabel *label_mutation_julia_c_mul;
    MyDoubleSpinBox *spinbox_mutation_julia_c_mul;
    QLabel *label_mutation_julia_pulse_freq;
    MyDoubleSpinBox *spinbox_mutation_julia_pulse_freq;
    QLabel *label_mutation_julia_absorb;
    MyDoubleSpinBox *spinbox_mutation_julia_absorb;
    QLabel *label_mutation_julia_c_power;
    MyDoubleSpinBox *spinbox_mutation_julia_c_power;
    QLabel *label_mutation_julia_c_radius;
    MyDoubleSpinBox *spinbox_mutation_julia_c_radius;
    QLabel *label_mutation_section_iter_header;
    QLabel *label_mutation_pre_iter;
    QLabel *label_mutation_pre_iter_s;
    MySpinBox *spinboxInt_mutation_pre_iter_start;
    QLabel *label_mutation_pre_iter_e;
    MySpinBox *spinboxInt_mutation_pre_iter_stop;
    QLabel *label_mutation_fold_iter;
    QLabel *label_mutation_fold_iter_s;
    MySpinBox *spinboxInt_mutation_fold_iter_start;
    QLabel *label_mutation_fold_iter_e;
    MySpinBox *spinboxInt_mutation_fold_iter_stop;
    QLabel *label_mutation_warp_iter;
    QLabel *label_mutation_warp_iter_s;
    MySpinBox *spinboxInt_mutation_warp_iter_start;
    QLabel *label_mutation_warp_iter_e;
    MySpinBox *spinboxInt_mutation_warp_iter_stop;
    QLabel *label_mutation_math_iter;
    QLabel *label_mutation_math_iter_s;
    MySpinBox *spinboxInt_mutation_math_iter_start;
    QLabel *label_mutation_math_iter_e;
    MySpinBox *spinboxInt_mutation_math_iter_stop;
    QLabel *label_mutation_post_iter;
    QLabel *label_mutation_post_iter_s;
    MySpinBox *spinboxInt_mutation_post_iter_start;
    QLabel *label_mutation_post_iter_e;
    MySpinBox *spinboxInt_mutation_post_iter_stop;
    QLabel *label_mutation_julia_iter;
    QLabel *label_mutation_julia_iter_s;
    MySpinBox *spinboxInt_mutation_julia_iter_start;
    QLabel *label_mutation_julia_iter_e;
    MySpinBox *spinboxInt_mutation_julia_iter_stop;
    QLabel *label_mutation_julia_ext_header;
    QLabel *label_mutation_julia_decay_rate_l;
    MyDoubleSpinBox *spinbox_mutation_julia_decay_rate;
    QLabel *label_mutation_julia_spiral_angle_l;
    MyDoubleSpinBox *spinbox_mutation_julia_spiral_angle;
    QLabel *label_mutation_julia_chaos_r_l;
    MyDoubleSpinBox *spinbox_mutation_julia_chaos_r;
    QLabel *label_mutation_julia_threshold_l;
    MyDoubleSpinBox *spinbox_mutation_julia_threshold;
    QLabel *label_mutation_julia_gradient_end_l;
    MyDoubleSpinBox *spinbox_mutation_julia_gradient_end;
    QLabel *label_mutation_julia_box_fold_limit_l;
    MyDoubleSpinBox *spinbox_mutation_julia_box_fold_limit;
    QLabel *label_mutation_julia_start_epsilon_l;
    MyDoubleSpinBox *spinbox_mutation_julia_start_epsilon;
    QLabel *label_mutation_julia_layer_c2_l;
    MyDoubleSpinBox *spinboxd3_mutation_julia_layer_c2_x;
    QLabel *label_mutation_julia_layer_c2_yz_l;
    MyDoubleSpinBox *spinboxd3_mutation_julia_layer_c2_y;
    MyDoubleSpinBox *spinboxd3_mutation_julia_layer_c2_z;
    QLabel *label_mutation_julia_dist_band_l;
    MyDoubleSpinBox *spinbox_mutation_julia_dist_band_mid;
    QLabel *label_mutation_julia_dist_band_far_l;
    MyDoubleSpinBox *spinbox_mutation_julia_dist_band_far;
    QLabel *label_julia_finetune_header;
    QLabel *label_mutation_julia_ctransform_iter_start_l;
    MySpinBox *spinboxInt_mutation_julia_ctransform_iter_start;
    QLabel *label_mutation_julia_ctransform_iter_stop_l;
    MySpinBox *spinboxInt_mutation_julia_ctransform_iter_stop;
    QLabel *label_mutation_julia_dynamic_iter_start_l;
    MySpinBox *spinboxInt_mutation_julia_dynamic_iter_start;
    QLabel *label_mutation_julia_dynamic_iter_stop_l;
    MySpinBox *spinboxInt_mutation_julia_dynamic_iter_stop;
    QLabel *label_mutation_julia_multi_iter_start_l;
    MySpinBox *spinboxInt_mutation_julia_multi_iter_start;
    QLabel *label_mutation_julia_multi_iter_stop_l;
    MySpinBox *spinboxInt_mutation_julia_multi_iter_stop;
    QLabel *label_mutation_julia_ctransform_strength_l;
    MyDoubleSpinBox *spinbox_mutation_julia_ctransform_strength;
    QLabel *label_mutation_julia_dynamic_strength_l;
    MyDoubleSpinBox *spinbox_mutation_julia_dynamic_strength;
    QLabel *label_mutation_julia_multi_strength_l;
    MyDoubleSpinBox *spinbox_mutation_julia_multi_strength;
    QLabel *label_mutation_julia_injection_strength_l;
    MyDoubleSpinBox *spinbox_mutation_julia_injection_strength;
    QLabel *label_mutation_julia_de_factor_l;
    MyDoubleSpinBox *spinbox_mutation_julia_de_factor;
    QLabel *label_mutation_de_iter;
    QLabel *label_mutation_de_iter_s;
    MySpinBox *spinboxInt_mutation_de_iter_start;
    QLabel *label_mutation_de_iter_e;
    MySpinBox *spinboxInt_mutation_de_iter_stop;
    QLabel *label_c_rotation;
    MyDoubleSpinBox *spinboxd3_mutation_julia_c_rot_x;
    MyDoubleSpinBox *spinboxd3_mutation_julia_c_rot_y;
    MyDoubleSpinBox *spinboxd3_mutation_julia_c_rot_z;
    QLabel *label_m_bius_a;
    MyDoubleSpinBox *spinboxd_mutation_julia_c_mobius_a;
    QLabel *label_m_bius_b;
    MyDoubleSpinBox *spinboxd_mutation_julia_c_mobius_b;
    QLabel *label_m_bius_d;
    MyDoubleSpinBox *spinboxd_mutation_julia_c_mobius_d;
    QLabel *label_pulse_amp;
    MyDoubleSpinBox *spinboxd_mutation_julia_pulse_amp;
    QLabel *label_noise_freq;
    MyDoubleSpinBox *spinboxd_mutation_julia_noise_freq;
    QLabel *label_noise_amp;
    MyDoubleSpinBox *spinboxd_mutation_julia_noise_amp;
    QLabel *label_fourier_c2;
    MyDoubleSpinBox *spinboxd3_mutation_julia_fourier_c2_x;
    MyDoubleSpinBox *spinboxd3_mutation_julia_fourier_c2_y;
    MyDoubleSpinBox *spinboxd3_mutation_julia_fourier_c2_z;
    QLabel *label_fourier_c3;
    MyDoubleSpinBox *spinboxd3_mutation_julia_fourier_c3_x;
    MyDoubleSpinBox *spinboxd3_mutation_julia_fourier_c3_y;
    MyDoubleSpinBox *spinboxd3_mutation_julia_fourier_c3_z;
    QLabel *label_bipolar_cr;
    MyDoubleSpinBox *spinboxd3_mutation_julia_bipolar_cr_x;
    MyDoubleSpinBox *spinboxd3_mutation_julia_bipolar_cr_y;
    MyDoubleSpinBox *spinboxd3_mutation_julia_bipolar_cr_z;
    QWidget *widget_mutation_sections;
    QVBoxLayout *vboxLayout_mutation_sections;
    QHBoxLayout *horizontalLayout_mutation_sections_top;
    QPushButton *pushButton_mutation_randomize_weights_2;
    QPushButton *pushButton_mutation_reset_all;
    QLabel *label;
    MyDoubleSpinBox *footerMasterWeightSpin;
    QSpacerItem *spacerItem;
    cMutationClipInvPanel *widget_mutation_clip_inv_panel;
    cMutationJosPkPanel *widget_mutation_jos_pk_panel;
    cMutationSystemsPanel *widget_mutation_systems_panel;
    cMutationTailPanel *widget_mutation_tail_panel;

    void setupUi(QWidget *cDockMutationTab)
    {
        if (cDockMutationTab->objectName().isEmpty())
            cDockMutationTab->setObjectName(QString::fromUtf8("cDockMutationTab"));
        cDockMutationTab->resize(460, 3000);
        verticalLayout_mutation_dock = new QVBoxLayout(cDockMutationTab);
        verticalLayout_mutation_dock->setSpacing(2);
        verticalLayout_mutation_dock->setObjectName(QString::fromUtf8("verticalLayout_mutation_dock"));
        verticalLayout_mutation_dock->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_mutation_top = new QHBoxLayout();
        horizontalLayout_mutation_top->setObjectName(QString::fromUtf8("horizontalLayout_mutation_top"));
        pushButton_mutation_randomize_weights = new QPushButton(cDockMutationTab);
        pushButton_mutation_randomize_weights->setObjectName(QString::fromUtf8("pushButton_mutation_randomize_weights"));

        horizontalLayout_mutation_top->addWidget(pushButton_mutation_randomize_weights);

        pushButton_mutation_reset_weights = new QPushButton(cDockMutationTab);
        pushButton_mutation_reset_weights->setObjectName(QString::fromUtf8("pushButton_mutation_reset_weights"));

        horizontalLayout_mutation_top->addWidget(pushButton_mutation_reset_weights);

        pushButton_mutation_reset_all_top = new QPushButton(cDockMutationTab);
        pushButton_mutation_reset_all_top->setObjectName(QString::fromUtf8("pushButton_mutation_reset_all_top"));

        horizontalLayout_mutation_top->addWidget(pushButton_mutation_reset_all_top);

        label_mutation_master_weight = new QLabel(cDockMutationTab);
        label_mutation_master_weight->setObjectName(QString::fromUtf8("label_mutation_master_weight"));

        horizontalLayout_mutation_top->addWidget(label_mutation_master_weight);

        spinbox_mutation_master_weight = new MyDoubleSpinBox(cDockMutationTab);
        spinbox_mutation_master_weight->setObjectName(QString::fromUtf8("spinbox_mutation_master_weight"));
        spinbox_mutation_master_weight->setMinimum(0.000000000000000);
        spinbox_mutation_master_weight->setMaximum(1.000000000000000);
        spinbox_mutation_master_weight->setSingleStep(0.050000000000000);
        spinbox_mutation_master_weight->setValue(1.000000000000000);
        spinbox_mutation_master_weight->setDecimals(4);

        horizontalLayout_mutation_top->addWidget(spinbox_mutation_master_weight);

        horizontalSpacer_mutation_top = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_mutation_top->addItem(horizontalSpacer_mutation_top);


        verticalLayout_mutation_dock->addLayout(horizontalLayout_mutation_top);

        groupCheck_mutation_enabled = new MyGroupBox(cDockMutationTab);
        groupCheck_mutation_enabled->setObjectName(QString::fromUtf8("groupCheck_mutation_enabled"));
        groupCheck_mutation_enabled->setCheckable(true);
        groupCheck_mutation_enabled->setChecked(false);
        gridLayout_mutation = new QGridLayout(groupCheck_mutation_enabled);
        gridLayout_mutation->setSpacing(2);
        gridLayout_mutation->setObjectName(QString::fromUtf8("gridLayout_mutation"));
        label_mutation_pre_rotation = new QLabel(groupCheck_mutation_enabled);
        label_mutation_pre_rotation->setObjectName(QString::fromUtf8("label_mutation_pre_rotation"));

        gridLayout_mutation->addWidget(label_mutation_pre_rotation, 0, 0, 1, 1);

        label_mutation_pre_rot_ax = new QLabel(groupCheck_mutation_enabled);
        label_mutation_pre_rot_ax->setObjectName(QString::fromUtf8("label_mutation_pre_rot_ax"));
        label_mutation_pre_rot_ax->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_pre_rot_ax, 0, 1, 1, 1);

        spinbox_mutation_pre_rotation_ax = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_pre_rotation_ax->setObjectName(QString::fromUtf8("spinbox_mutation_pre_rotation_ax"));
        spinbox_mutation_pre_rotation_ax->setDecimals(2);
        spinbox_mutation_pre_rotation_ax->setMinimum(-360.000000000000000);
        spinbox_mutation_pre_rotation_ax->setMaximum(360.000000000000000);
        spinbox_mutation_pre_rotation_ax->setSingleStep(5.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_pre_rotation_ax, 0, 2, 1, 1);

        label_mutation_pre_rot_ay = new QLabel(groupCheck_mutation_enabled);
        label_mutation_pre_rot_ay->setObjectName(QString::fromUtf8("label_mutation_pre_rot_ay"));
        label_mutation_pre_rot_ay->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_pre_rot_ay, 0, 3, 1, 1);

        spinbox_mutation_pre_rotation_ay = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_pre_rotation_ay->setObjectName(QString::fromUtf8("spinbox_mutation_pre_rotation_ay"));
        spinbox_mutation_pre_rotation_ay->setDecimals(2);
        spinbox_mutation_pre_rotation_ay->setMinimum(-360.000000000000000);
        spinbox_mutation_pre_rotation_ay->setMaximum(360.000000000000000);
        spinbox_mutation_pre_rotation_ay->setSingleStep(5.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_pre_rotation_ay, 0, 4, 1, 1);

        label_mutation_pre_rot_az = new QLabel(groupCheck_mutation_enabled);
        label_mutation_pre_rot_az->setObjectName(QString::fromUtf8("label_mutation_pre_rot_az"));
        label_mutation_pre_rot_az->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_pre_rot_az, 0, 5, 1, 1);

        spinbox_mutation_pre_rotation_az = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_pre_rotation_az->setObjectName(QString::fromUtf8("spinbox_mutation_pre_rotation_az"));
        spinbox_mutation_pre_rotation_az->setDecimals(2);
        spinbox_mutation_pre_rotation_az->setMinimum(-360.000000000000000);
        spinbox_mutation_pre_rotation_az->setMaximum(360.000000000000000);
        spinbox_mutation_pre_rotation_az->setSingleStep(5.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_pre_rotation_az, 0, 6, 1, 1);

        label_mutation_pre_scale = new QLabel(groupCheck_mutation_enabled);
        label_mutation_pre_scale->setObjectName(QString::fromUtf8("label_mutation_pre_scale"));

        gridLayout_mutation->addWidget(label_mutation_pre_scale, 1, 0, 1, 1);

        spinbox_mutation_pre_scale = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_pre_scale->setObjectName(QString::fromUtf8("spinbox_mutation_pre_scale"));
        spinbox_mutation_pre_scale->setDecimals(4);
        spinbox_mutation_pre_scale->setMinimum(0.001000000000000);
        spinbox_mutation_pre_scale->setMaximum(100.000000000000000);
        spinbox_mutation_pre_scale->setSingleStep(0.100000000000000);
        spinbox_mutation_pre_scale->setValue(1.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_pre_scale, 1, 1, 1, 5);

        label_mutation_pre_offset = new QLabel(groupCheck_mutation_enabled);
        label_mutation_pre_offset->setObjectName(QString::fromUtf8("label_mutation_pre_offset"));

        gridLayout_mutation->addWidget(label_mutation_pre_offset, 2, 0, 1, 1);

        label_mutation_preoff_ax = new QLabel(groupCheck_mutation_enabled);
        label_mutation_preoff_ax->setObjectName(QString::fromUtf8("label_mutation_preoff_ax"));
        label_mutation_preoff_ax->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_preoff_ax, 2, 1, 1, 1);

        spinbox_mutation_pre_offset_ax = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_pre_offset_ax->setObjectName(QString::fromUtf8("spinbox_mutation_pre_offset_ax"));
        spinbox_mutation_pre_offset_ax->setDecimals(4);
        spinbox_mutation_pre_offset_ax->setMinimum(-100.000000000000000);
        spinbox_mutation_pre_offset_ax->setMaximum(100.000000000000000);
        spinbox_mutation_pre_offset_ax->setSingleStep(0.010000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_pre_offset_ax, 2, 2, 1, 1);

        label_mutation_preoff_ay = new QLabel(groupCheck_mutation_enabled);
        label_mutation_preoff_ay->setObjectName(QString::fromUtf8("label_mutation_preoff_ay"));
        label_mutation_preoff_ay->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_preoff_ay, 2, 3, 1, 1);

        spinbox_mutation_pre_offset_ay = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_pre_offset_ay->setObjectName(QString::fromUtf8("spinbox_mutation_pre_offset_ay"));
        spinbox_mutation_pre_offset_ay->setDecimals(4);
        spinbox_mutation_pre_offset_ay->setMinimum(-100.000000000000000);
        spinbox_mutation_pre_offset_ay->setMaximum(100.000000000000000);
        spinbox_mutation_pre_offset_ay->setSingleStep(0.010000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_pre_offset_ay, 2, 4, 1, 1);

        label_mutation_preoff_az = new QLabel(groupCheck_mutation_enabled);
        label_mutation_preoff_az->setObjectName(QString::fromUtf8("label_mutation_preoff_az"));
        label_mutation_preoff_az->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_preoff_az, 2, 5, 1, 1);

        spinbox_mutation_pre_offset_az = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_pre_offset_az->setObjectName(QString::fromUtf8("spinbox_mutation_pre_offset_az"));
        spinbox_mutation_pre_offset_az->setDecimals(4);
        spinbox_mutation_pre_offset_az->setMinimum(-100.000000000000000);
        spinbox_mutation_pre_offset_az->setMaximum(100.000000000000000);
        spinbox_mutation_pre_offset_az->setSingleStep(0.010000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_pre_offset_az, 2, 6, 1, 1);

        label_mutation_pre_abs = new QLabel(groupCheck_mutation_enabled);
        label_mutation_pre_abs->setObjectName(QString::fromUtf8("label_mutation_pre_abs"));

        gridLayout_mutation->addWidget(label_mutation_pre_abs, 3, 0, 1, 1);

        checkBox_mutation_pre_abs_ax = new MyCheckBox(groupCheck_mutation_enabled);
        checkBox_mutation_pre_abs_ax->setObjectName(QString::fromUtf8("checkBox_mutation_pre_abs_ax"));

        gridLayout_mutation->addWidget(checkBox_mutation_pre_abs_ax, 3, 1, 1, 2);

        checkBox_mutation_pre_abs_ay = new MyCheckBox(groupCheck_mutation_enabled);
        checkBox_mutation_pre_abs_ay->setObjectName(QString::fromUtf8("checkBox_mutation_pre_abs_ay"));

        gridLayout_mutation->addWidget(checkBox_mutation_pre_abs_ay, 3, 3, 1, 2);

        checkBox_mutation_pre_abs_az = new MyCheckBox(groupCheck_mutation_enabled);
        checkBox_mutation_pre_abs_az->setObjectName(QString::fromUtf8("checkBox_mutation_pre_abs_az"));

        gridLayout_mutation->addWidget(checkBox_mutation_pre_abs_az, 3, 5, 1, 1);

        label_mutation_post_rotation = new QLabel(groupCheck_mutation_enabled);
        label_mutation_post_rotation->setObjectName(QString::fromUtf8("label_mutation_post_rotation"));

        gridLayout_mutation->addWidget(label_mutation_post_rotation, 4, 0, 1, 1);

        label_mutation_post_rot_ax = new QLabel(groupCheck_mutation_enabled);
        label_mutation_post_rot_ax->setObjectName(QString::fromUtf8("label_mutation_post_rot_ax"));
        label_mutation_post_rot_ax->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_post_rot_ax, 4, 1, 1, 1);

        spinbox_mutation_post_rotation_ax = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_post_rotation_ax->setObjectName(QString::fromUtf8("spinbox_mutation_post_rotation_ax"));
        spinbox_mutation_post_rotation_ax->setDecimals(2);
        spinbox_mutation_post_rotation_ax->setMinimum(-360.000000000000000);
        spinbox_mutation_post_rotation_ax->setMaximum(360.000000000000000);
        spinbox_mutation_post_rotation_ax->setSingleStep(5.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_post_rotation_ax, 4, 2, 1, 1);

        label_mutation_post_rot_ay = new QLabel(groupCheck_mutation_enabled);
        label_mutation_post_rot_ay->setObjectName(QString::fromUtf8("label_mutation_post_rot_ay"));
        label_mutation_post_rot_ay->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_post_rot_ay, 4, 3, 1, 1);

        spinbox_mutation_post_rotation_ay = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_post_rotation_ay->setObjectName(QString::fromUtf8("spinbox_mutation_post_rotation_ay"));
        spinbox_mutation_post_rotation_ay->setDecimals(2);
        spinbox_mutation_post_rotation_ay->setMinimum(-360.000000000000000);
        spinbox_mutation_post_rotation_ay->setMaximum(360.000000000000000);
        spinbox_mutation_post_rotation_ay->setSingleStep(5.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_post_rotation_ay, 4, 4, 1, 1);

        label_mutation_post_rot_az = new QLabel(groupCheck_mutation_enabled);
        label_mutation_post_rot_az->setObjectName(QString::fromUtf8("label_mutation_post_rot_az"));
        label_mutation_post_rot_az->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_post_rot_az, 4, 5, 1, 1);

        spinbox_mutation_post_rotation_az = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_post_rotation_az->setObjectName(QString::fromUtf8("spinbox_mutation_post_rotation_az"));
        spinbox_mutation_post_rotation_az->setDecimals(2);
        spinbox_mutation_post_rotation_az->setMinimum(-360.000000000000000);
        spinbox_mutation_post_rotation_az->setMaximum(360.000000000000000);
        spinbox_mutation_post_rotation_az->setSingleStep(5.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_post_rotation_az, 4, 6, 1, 1);

        label_mutation_post_scale = new QLabel(groupCheck_mutation_enabled);
        label_mutation_post_scale->setObjectName(QString::fromUtf8("label_mutation_post_scale"));

        gridLayout_mutation->addWidget(label_mutation_post_scale, 5, 0, 1, 1);

        spinbox_mutation_post_scale = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_post_scale->setObjectName(QString::fromUtf8("spinbox_mutation_post_scale"));
        spinbox_mutation_post_scale->setDecimals(4);
        spinbox_mutation_post_scale->setMinimum(0.001000000000000);
        spinbox_mutation_post_scale->setMaximum(100.000000000000000);
        spinbox_mutation_post_scale->setSingleStep(0.100000000000000);
        spinbox_mutation_post_scale->setValue(1.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_post_scale, 5, 1, 1, 5);

        label_mutation_post_offset = new QLabel(groupCheck_mutation_enabled);
        label_mutation_post_offset->setObjectName(QString::fromUtf8("label_mutation_post_offset"));

        gridLayout_mutation->addWidget(label_mutation_post_offset, 6, 0, 1, 1);

        label_mutation_postoff_ax = new QLabel(groupCheck_mutation_enabled);
        label_mutation_postoff_ax->setObjectName(QString::fromUtf8("label_mutation_postoff_ax"));
        label_mutation_postoff_ax->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_postoff_ax, 6, 1, 1, 1);

        spinbox_mutation_post_offset_ax = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_post_offset_ax->setObjectName(QString::fromUtf8("spinbox_mutation_post_offset_ax"));
        spinbox_mutation_post_offset_ax->setDecimals(4);
        spinbox_mutation_post_offset_ax->setMinimum(-100.000000000000000);
        spinbox_mutation_post_offset_ax->setMaximum(100.000000000000000);
        spinbox_mutation_post_offset_ax->setSingleStep(0.010000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_post_offset_ax, 6, 2, 1, 1);

        label_mutation_postoff_ay = new QLabel(groupCheck_mutation_enabled);
        label_mutation_postoff_ay->setObjectName(QString::fromUtf8("label_mutation_postoff_ay"));
        label_mutation_postoff_ay->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_postoff_ay, 6, 3, 1, 1);

        spinbox_mutation_post_offset_ay = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_post_offset_ay->setObjectName(QString::fromUtf8("spinbox_mutation_post_offset_ay"));
        spinbox_mutation_post_offset_ay->setDecimals(4);
        spinbox_mutation_post_offset_ay->setMinimum(-100.000000000000000);
        spinbox_mutation_post_offset_ay->setMaximum(100.000000000000000);
        spinbox_mutation_post_offset_ay->setSingleStep(0.010000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_post_offset_ay, 6, 4, 1, 1);

        label_mutation_postoff_az = new QLabel(groupCheck_mutation_enabled);
        label_mutation_postoff_az->setObjectName(QString::fromUtf8("label_mutation_postoff_az"));
        label_mutation_postoff_az->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_postoff_az, 6, 5, 1, 1);

        spinbox_mutation_post_offset_az = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_post_offset_az->setObjectName(QString::fromUtf8("spinbox_mutation_post_offset_az"));
        spinbox_mutation_post_offset_az->setDecimals(4);
        spinbox_mutation_post_offset_az->setMinimum(-100.000000000000000);
        spinbox_mutation_post_offset_az->setMaximum(100.000000000000000);
        spinbox_mutation_post_offset_az->setSingleStep(0.010000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_post_offset_az, 6, 6, 1, 1);

        label_mutation_swizzle = new QLabel(groupCheck_mutation_enabled);
        label_mutation_swizzle->setObjectName(QString::fromUtf8("label_mutation_swizzle"));

        gridLayout_mutation->addWidget(label_mutation_swizzle, 7, 0, 1, 1);

        comboBox_mutation_swizzle = new QComboBox(groupCheck_mutation_enabled);
        comboBox_mutation_swizzle->addItem(QString());
        comboBox_mutation_swizzle->addItem(QString());
        comboBox_mutation_swizzle->addItem(QString());
        comboBox_mutation_swizzle->addItem(QString());
        comboBox_mutation_swizzle->addItem(QString());
        comboBox_mutation_swizzle->addItem(QString());
        comboBox_mutation_swizzle->setObjectName(QString::fromUtf8("comboBox_mutation_swizzle"));

        gridLayout_mutation->addWidget(comboBox_mutation_swizzle, 7, 1, 1, 5);

        label_mutation_fold_type = new QLabel(groupCheck_mutation_enabled);
        label_mutation_fold_type->setObjectName(QString::fromUtf8("label_mutation_fold_type"));

        gridLayout_mutation->addWidget(label_mutation_fold_type, 8, 0, 1, 1);

        comboBox_mutation_fold_type = new QComboBox(groupCheck_mutation_enabled);
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->addItem(QString());
        comboBox_mutation_fold_type->setObjectName(QString::fromUtf8("comboBox_mutation_fold_type"));

        gridLayout_mutation->addWidget(comboBox_mutation_fold_type, 8, 1, 1, 2);

        label_mutation_fold_limit = new QLabel(groupCheck_mutation_enabled);
        label_mutation_fold_limit->setObjectName(QString::fromUtf8("label_mutation_fold_limit"));
        label_mutation_fold_limit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_fold_limit, 8, 3, 1, 1);

        spinbox_mutation_fold_limit = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_fold_limit->setObjectName(QString::fromUtf8("spinbox_mutation_fold_limit"));
        spinbox_mutation_fold_limit->setDecimals(4);
        spinbox_mutation_fold_limit->setMinimum(0.001000000000000);
        spinbox_mutation_fold_limit->setMaximum(100.000000000000000);
        spinbox_mutation_fold_limit->setSingleStep(0.100000000000000);
        spinbox_mutation_fold_limit->setValue(1.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_fold_limit, 8, 4, 1, 1);

        label_mutation_fold_value = new QLabel(groupCheck_mutation_enabled);
        label_mutation_fold_value->setObjectName(QString::fromUtf8("label_mutation_fold_value"));
        label_mutation_fold_value->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_fold_value, 8, 5, 1, 1);

        spinbox_mutation_fold_value = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_fold_value->setObjectName(QString::fromUtf8("spinbox_mutation_fold_value"));
        spinbox_mutation_fold_value->setDecimals(4);
        spinbox_mutation_fold_value->setMinimum(0.001000000000000);
        spinbox_mutation_fold_value->setMaximum(200.000000000000000);
        spinbox_mutation_fold_value->setSingleStep(0.100000000000000);
        spinbox_mutation_fold_value->setValue(2.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_fold_value, 8, 6, 1, 1);

        label_mutation_warp_type = new QLabel(groupCheck_mutation_enabled);
        label_mutation_warp_type->setObjectName(QString::fromUtf8("label_mutation_warp_type"));

        gridLayout_mutation->addWidget(label_mutation_warp_type, 9, 0, 1, 1);

        comboBox_mutation_warp_type = new QComboBox(groupCheck_mutation_enabled);
        comboBox_mutation_warp_type->addItem(QString());
        comboBox_mutation_warp_type->addItem(QString());
        comboBox_mutation_warp_type->addItem(QString());
        comboBox_mutation_warp_type->addItem(QString());
        comboBox_mutation_warp_type->addItem(QString());
        comboBox_mutation_warp_type->addItem(QString());
        comboBox_mutation_warp_type->addItem(QString());
        comboBox_mutation_warp_type->addItem(QString());
        comboBox_mutation_warp_type->addItem(QString());
        comboBox_mutation_warp_type->addItem(QString());
        comboBox_mutation_warp_type->addItem(QString());
        comboBox_mutation_warp_type->addItem(QString());
        comboBox_mutation_warp_type->setObjectName(QString::fromUtf8("comboBox_mutation_warp_type"));

        gridLayout_mutation->addWidget(comboBox_mutation_warp_type, 9, 1, 1, 2);

        label_mutation_warp_freq = new QLabel(groupCheck_mutation_enabled);
        label_mutation_warp_freq->setObjectName(QString::fromUtf8("label_mutation_warp_freq"));
        label_mutation_warp_freq->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_warp_freq, 9, 3, 1, 1);

        spinbox_mutation_warp_frequency = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_warp_frequency->setObjectName(QString::fromUtf8("spinbox_mutation_warp_frequency"));
        spinbox_mutation_warp_frequency->setDecimals(4);
        spinbox_mutation_warp_frequency->setMinimum(0.001000000000000);
        spinbox_mutation_warp_frequency->setMaximum(100.000000000000000);
        spinbox_mutation_warp_frequency->setSingleStep(0.100000000000000);
        spinbox_mutation_warp_frequency->setValue(1.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_warp_frequency, 9, 4, 1, 1);

        label_mutation_warp_amp = new QLabel(groupCheck_mutation_enabled);
        label_mutation_warp_amp->setObjectName(QString::fromUtf8("label_mutation_warp_amp"));
        label_mutation_warp_amp->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_warp_amp, 9, 5, 1, 1);

        spinbox_mutation_warp_amplitude = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_warp_amplitude->setObjectName(QString::fromUtf8("spinbox_mutation_warp_amplitude"));
        spinbox_mutation_warp_amplitude->setDecimals(4);
        spinbox_mutation_warp_amplitude->setMinimum(0.000000000000000);
        spinbox_mutation_warp_amplitude->setMaximum(100.000000000000000);
        spinbox_mutation_warp_amplitude->setSingleStep(0.010000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_warp_amplitude, 9, 6, 1, 1);

        label_mutation_fold_position = new QLabel(groupCheck_mutation_enabled);
        label_mutation_fold_position->setObjectName(QString::fromUtf8("label_mutation_fold_position"));

        gridLayout_mutation->addWidget(label_mutation_fold_position, 10, 0, 1, 1);

        comboBox_mutation_fold_position = new QComboBox(groupCheck_mutation_enabled);
        comboBox_mutation_fold_position->addItem(QString());
        comboBox_mutation_fold_position->addItem(QString());
        comboBox_mutation_fold_position->addItem(QString());
        comboBox_mutation_fold_position->setObjectName(QString::fromUtf8("comboBox_mutation_fold_position"));

        gridLayout_mutation->addWidget(comboBox_mutation_fold_position, 10, 1, 1, 2);

        label_mutation_kaleidoscope_sides = new QLabel(groupCheck_mutation_enabled);
        label_mutation_kaleidoscope_sides->setObjectName(QString::fromUtf8("label_mutation_kaleidoscope_sides"));
        label_mutation_kaleidoscope_sides->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_kaleidoscope_sides, 10, 3, 1, 1);

        spinboxInt_mutation_kaleidoscope_sides = new MySpinBox(groupCheck_mutation_enabled);
        spinboxInt_mutation_kaleidoscope_sides->setObjectName(QString::fromUtf8("spinboxInt_mutation_kaleidoscope_sides"));
        spinboxInt_mutation_kaleidoscope_sides->setMinimum(3);
        spinboxInt_mutation_kaleidoscope_sides->setMaximum(24);
        spinboxInt_mutation_kaleidoscope_sides->setValue(6);

        gridLayout_mutation->addWidget(spinboxInt_mutation_kaleidoscope_sides, 10, 4, 1, 2);

        label_mutation_iter_range = new QLabel(groupCheck_mutation_enabled);
        label_mutation_iter_range->setObjectName(QString::fromUtf8("label_mutation_iter_range"));

        gridLayout_mutation->addWidget(label_mutation_iter_range, 11, 0, 1, 1);

        label_mutation_iter_start = new QLabel(groupCheck_mutation_enabled);
        label_mutation_iter_start->setObjectName(QString::fromUtf8("label_mutation_iter_start"));
        label_mutation_iter_start->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_iter_start, 11, 1, 1, 1);

        spinboxInt_mutation_iteration_start = new MySpinBox(groupCheck_mutation_enabled);
        spinboxInt_mutation_iteration_start->setObjectName(QString::fromUtf8("spinboxInt_mutation_iteration_start"));
        spinboxInt_mutation_iteration_start->setMinimum(0);
        spinboxInt_mutation_iteration_start->setMaximum(10000);
        spinboxInt_mutation_iteration_start->setValue(0);

        gridLayout_mutation->addWidget(spinboxInt_mutation_iteration_start, 11, 2, 1, 1);

        label_mutation_iter_stop = new QLabel(groupCheck_mutation_enabled);
        label_mutation_iter_stop->setObjectName(QString::fromUtf8("label_mutation_iter_stop"));
        label_mutation_iter_stop->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_iter_stop, 11, 3, 1, 1);

        spinboxInt_mutation_iteration_stop = new MySpinBox(groupCheck_mutation_enabled);
        spinboxInt_mutation_iteration_stop->setObjectName(QString::fromUtf8("spinboxInt_mutation_iteration_stop"));
        spinboxInt_mutation_iteration_stop->setMinimum(0);
        spinboxInt_mutation_iteration_stop->setMaximum(10000);
        spinboxInt_mutation_iteration_stop->setValue(250);

        gridLayout_mutation->addWidget(spinboxInt_mutation_iteration_stop, 11, 4, 1, 2);

        label_mutation_math_type = new QLabel(groupCheck_mutation_enabled);
        label_mutation_math_type->setObjectName(QString::fromUtf8("label_mutation_math_type"));

        gridLayout_mutation->addWidget(label_mutation_math_type, 12, 0, 1, 1);

        comboBox_mutation_math_type = new QComboBox(groupCheck_mutation_enabled);
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->addItem(QString());
        comboBox_mutation_math_type->setObjectName(QString::fromUtf8("comboBox_mutation_math_type"));

        gridLayout_mutation->addWidget(comboBox_mutation_math_type, 12, 1, 1, 2);

        label_mutation_math_mix = new QLabel(groupCheck_mutation_enabled);
        label_mutation_math_mix->setObjectName(QString::fromUtf8("label_mutation_math_mix"));
        label_mutation_math_mix->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_math_mix, 12, 3, 1, 1);

        spinbox_mutation_math_mix = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_math_mix->setObjectName(QString::fromUtf8("spinbox_mutation_math_mix"));
        spinbox_mutation_math_mix->setDecimals(4);
        spinbox_mutation_math_mix->setMinimum(0.000000000000000);
        spinbox_mutation_math_mix->setMaximum(1.000000000000000);
        spinbox_mutation_math_mix->setSingleStep(0.010000000000000);
        spinbox_mutation_math_mix->setValue(1.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_math_mix, 12, 4, 1, 2);

        label_mutation_math_p1 = new QLabel(groupCheck_mutation_enabled);
        label_mutation_math_p1->setObjectName(QString::fromUtf8("label_mutation_math_p1"));

        gridLayout_mutation->addWidget(label_mutation_math_p1, 13, 0, 1, 1);

        spinbox_mutation_math_p1 = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_math_p1->setObjectName(QString::fromUtf8("spinbox_mutation_math_p1"));
        spinbox_mutation_math_p1->setDecimals(4);
        spinbox_mutation_math_p1->setMinimum(-100.000000000000000);
        spinbox_mutation_math_p1->setMaximum(100.000000000000000);
        spinbox_mutation_math_p1->setSingleStep(0.100000000000000);
        spinbox_mutation_math_p1->setValue(2.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_math_p1, 13, 1, 1, 1);

        label_mutation_math_p2 = new QLabel(groupCheck_mutation_enabled);
        label_mutation_math_p2->setObjectName(QString::fromUtf8("label_mutation_math_p2"));
        label_mutation_math_p2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_math_p2, 13, 2, 1, 1);

        spinbox_mutation_math_p2 = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_math_p2->setObjectName(QString::fromUtf8("spinbox_mutation_math_p2"));
        spinbox_mutation_math_p2->setDecimals(4);
        spinbox_mutation_math_p2->setMinimum(-100.000000000000000);
        spinbox_mutation_math_p2->setMaximum(100.000000000000000);
        spinbox_mutation_math_p2->setSingleStep(0.100000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_math_p2, 13, 3, 1, 1);

        label_mutation_math_p3 = new QLabel(groupCheck_mutation_enabled);
        label_mutation_math_p3->setObjectName(QString::fromUtf8("label_mutation_math_p3"));
        label_mutation_math_p3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_math_p3, 13, 4, 1, 1);

        spinbox_mutation_math_p3 = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_math_p3->setObjectName(QString::fromUtf8("spinbox_mutation_math_p3"));
        spinbox_mutation_math_p3->setDecimals(4);
        spinbox_mutation_math_p3->setMinimum(-100.000000000000000);
        spinbox_mutation_math_p3->setMaximum(100.000000000000000);
        spinbox_mutation_math_p3->setSingleStep(0.100000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_math_p3, 13, 5, 1, 1);

        spinbox_mutation_math_p4 = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_math_p4->setObjectName(QString::fromUtf8("spinbox_mutation_math_p4"));
        spinbox_mutation_math_p4->setDecimals(4);
        spinbox_mutation_math_p4->setMinimum(-100.000000000000000);
        spinbox_mutation_math_p4->setMaximum(100.000000000000000);
        spinbox_mutation_math_p4->setSingleStep(0.100000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_math_p4, 13, 6, 1, 1);

        label_mutation_math_p5 = new QLabel(groupCheck_mutation_enabled);
        label_mutation_math_p5->setObjectName(QString::fromUtf8("label_mutation_math_p5"));
        label_mutation_math_p5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_math_p5, 14, 0, 1, 1);

        spinbox_mutation_math_p5 = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_math_p5->setObjectName(QString::fromUtf8("spinbox_mutation_math_p5"));
        spinbox_mutation_math_p5->setDecimals(4);
        spinbox_mutation_math_p5->setMinimum(-100.000000000000000);
        spinbox_mutation_math_p5->setMaximum(100.000000000000000);
        spinbox_mutation_math_p5->setSingleStep(0.100000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_math_p5, 14, 1, 1, 1);

        label_mutation_math_p6 = new QLabel(groupCheck_mutation_enabled);
        label_mutation_math_p6->setObjectName(QString::fromUtf8("label_mutation_math_p6"));
        label_mutation_math_p6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_math_p6, 14, 2, 1, 1);

        spinbox_mutation_math_p6 = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_math_p6->setObjectName(QString::fromUtf8("spinbox_mutation_math_p6"));
        spinbox_mutation_math_p6->setDecimals(4);
        spinbox_mutation_math_p6->setMinimum(-100.000000000000000);
        spinbox_mutation_math_p6->setMaximum(100.000000000000000);
        spinbox_mutation_math_p6->setSingleStep(0.100000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_math_p6, 14, 3, 1, 1);

        label_mutation_math_p7 = new QLabel(groupCheck_mutation_enabled);
        label_mutation_math_p7->setObjectName(QString::fromUtf8("label_mutation_math_p7"));
        label_mutation_math_p7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_math_p7, 14, 4, 1, 1);

        spinbox_mutation_math_p7 = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_math_p7->setObjectName(QString::fromUtf8("spinbox_mutation_math_p7"));
        spinbox_mutation_math_p7->setDecimals(4);
        spinbox_mutation_math_p7->setMinimum(-100.000000000000000);
        spinbox_mutation_math_p7->setMaximum(100.000000000000000);
        spinbox_mutation_math_p7->setSingleStep(0.100000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_math_p7, 14, 5, 1, 1);

        spinbox_mutation_math_p8 = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_math_p8->setObjectName(QString::fromUtf8("spinbox_mutation_math_p8"));
        spinbox_mutation_math_p8->setDecimals(4);
        spinbox_mutation_math_p8->setMinimum(-100.000000000000000);
        spinbox_mutation_math_p8->setMaximum(100.000000000000000);
        spinbox_mutation_math_p8->setSingleStep(0.100000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_math_p8, 14, 6, 1, 1);

        label_mutation_z_mix = new QLabel(groupCheck_mutation_enabled);
        label_mutation_z_mix->setObjectName(QString::fromUtf8("label_mutation_z_mix"));

        gridLayout_mutation->addWidget(label_mutation_z_mix, 15, 0, 1, 1);

        spinbox_mutation_z_mix = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_z_mix->setObjectName(QString::fromUtf8("spinbox_mutation_z_mix"));
        spinbox_mutation_z_mix->setDecimals(4);
        spinbox_mutation_z_mix->setMinimum(0.000000000000000);
        spinbox_mutation_z_mix->setMaximum(1.000000000000000);
        spinbox_mutation_z_mix->setSingleStep(0.050000000000000);
        spinbox_mutation_z_mix->setValue(1.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_z_mix, 15, 1, 1, 2);

        label_mutation_de_scale = new QLabel(groupCheck_mutation_enabled);
        label_mutation_de_scale->setObjectName(QString::fromUtf8("label_mutation_de_scale"));
        label_mutation_de_scale->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_de_scale, 15, 3, 1, 1);

        spinbox_mutation_de_scale = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_de_scale->setObjectName(QString::fromUtf8("spinbox_mutation_de_scale"));
        spinbox_mutation_de_scale->setDecimals(4);
        spinbox_mutation_de_scale->setMinimum(0.001000000000000);
        spinbox_mutation_de_scale->setMaximum(100.000000000000000);
        spinbox_mutation_de_scale->setSingleStep(0.100000000000000);
        spinbox_mutation_de_scale->setValue(1.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_de_scale, 15, 4, 1, 2);

        label_mutation_de_tweak = new QLabel(groupCheck_mutation_enabled);
        label_mutation_de_tweak->setObjectName(QString::fromUtf8("label_mutation_de_tweak"));

        gridLayout_mutation->addWidget(label_mutation_de_tweak, 16, 0, 1, 1);

        comboBox_mutation_de_tweak = new QComboBox(groupCheck_mutation_enabled);
        comboBox_mutation_de_tweak->addItem(QString());
        comboBox_mutation_de_tweak->addItem(QString());
        comboBox_mutation_de_tweak->addItem(QString());
        comboBox_mutation_de_tweak->addItem(QString());
        comboBox_mutation_de_tweak->addItem(QString());
        comboBox_mutation_de_tweak->addItem(QString());
        comboBox_mutation_de_tweak->addItem(QString());
        comboBox_mutation_de_tweak->setObjectName(QString::fromUtf8("comboBox_mutation_de_tweak"));

        gridLayout_mutation->addWidget(comboBox_mutation_de_tweak, 16, 1, 1, 2);

        label_mutation_de_tweak_p1 = new QLabel(groupCheck_mutation_enabled);
        label_mutation_de_tweak_p1->setObjectName(QString::fromUtf8("label_mutation_de_tweak_p1"));
        label_mutation_de_tweak_p1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_de_tweak_p1, 16, 3, 1, 1);

        spinbox_mutation_de_tweak_p1 = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_de_tweak_p1->setObjectName(QString::fromUtf8("spinbox_mutation_de_tweak_p1"));
        spinbox_mutation_de_tweak_p1->setDecimals(4);
        spinbox_mutation_de_tweak_p1->setMinimum(0.000000000000000);
        spinbox_mutation_de_tweak_p1->setMaximum(10.000000000000000);
        spinbox_mutation_de_tweak_p1->setSingleStep(0.010000000000000);
        spinbox_mutation_de_tweak_p1->setValue(0.100000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_de_tweak_p1, 16, 4, 1, 1);

        label_mutation_de_tweak_p2 = new QLabel(groupCheck_mutation_enabled);
        label_mutation_de_tweak_p2->setObjectName(QString::fromUtf8("label_mutation_de_tweak_p2"));
        label_mutation_de_tweak_p2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_de_tweak_p2, 16, 5, 1, 1);

        spinbox_mutation_de_tweak_p2 = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_de_tweak_p2->setObjectName(QString::fromUtf8("spinbox_mutation_de_tweak_p2"));
        spinbox_mutation_de_tweak_p2->setDecimals(4);
        spinbox_mutation_de_tweak_p2->setMinimum(0.000000000000000);
        spinbox_mutation_de_tweak_p2->setMaximum(1000.000000000000000);
        spinbox_mutation_de_tweak_p2->setSingleStep(1.000000000000000);
        spinbox_mutation_de_tweak_p2->setValue(10.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_de_tweak_p2, 16, 6, 1, 1);

        label_mutation_orbit_trap = new QLabel(groupCheck_mutation_enabled);
        label_mutation_orbit_trap->setObjectName(QString::fromUtf8("label_mutation_orbit_trap"));

        gridLayout_mutation->addWidget(label_mutation_orbit_trap, 17, 0, 1, 1);

        comboBox_mutation_orbit_trap = new QComboBox(groupCheck_mutation_enabled);
        comboBox_mutation_orbit_trap->addItem(QString());
        comboBox_mutation_orbit_trap->addItem(QString());
        comboBox_mutation_orbit_trap->addItem(QString());
        comboBox_mutation_orbit_trap->addItem(QString());
        comboBox_mutation_orbit_trap->addItem(QString());
        comboBox_mutation_orbit_trap->addItem(QString());
        comboBox_mutation_orbit_trap->setObjectName(QString::fromUtf8("comboBox_mutation_orbit_trap"));

        gridLayout_mutation->addWidget(comboBox_mutation_orbit_trap, 17, 1, 1, 2);

        label_mutation_trap_radius = new QLabel(groupCheck_mutation_enabled);
        label_mutation_trap_radius->setObjectName(QString::fromUtf8("label_mutation_trap_radius"));
        label_mutation_trap_radius->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_trap_radius, 17, 3, 1, 1);

        spinbox_mutation_trap_radius = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_trap_radius->setObjectName(QString::fromUtf8("spinbox_mutation_trap_radius"));
        spinbox_mutation_trap_radius->setDecimals(4);
        spinbox_mutation_trap_radius->setMinimum(0.001000000000000);
        spinbox_mutation_trap_radius->setMaximum(100.000000000000000);
        spinbox_mutation_trap_radius->setSingleStep(0.100000000000000);
        spinbox_mutation_trap_radius->setValue(1.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_trap_radius, 17, 4, 1, 2);

        checkBox_mutation_curvature_coloring = new QCheckBox(groupCheck_mutation_enabled);
        checkBox_mutation_curvature_coloring->setObjectName(QString::fromUtf8("checkBox_mutation_curvature_coloring"));

        gridLayout_mutation->addWidget(checkBox_mutation_curvature_coloring, 18, 0, 1, 1);

        label_mutation_julia_injection = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_injection->setObjectName(QString::fromUtf8("label_mutation_julia_injection"));

        gridLayout_mutation->addWidget(label_mutation_julia_injection, 19, 0, 1, 1);

        comboBox_mutation_julia_injection = new QComboBox(groupCheck_mutation_enabled);
        comboBox_mutation_julia_injection->addItem(QString());
        comboBox_mutation_julia_injection->addItem(QString());
        comboBox_mutation_julia_injection->addItem(QString());
        comboBox_mutation_julia_injection->addItem(QString());
        comboBox_mutation_julia_injection->addItem(QString());
        comboBox_mutation_julia_injection->addItem(QString());
        comboBox_mutation_julia_injection->addItem(QString());
        comboBox_mutation_julia_injection->addItem(QString());
        comboBox_mutation_julia_injection->addItem(QString());
        comboBox_mutation_julia_injection->addItem(QString());
        comboBox_mutation_julia_injection->addItem(QString());
        comboBox_mutation_julia_injection->addItem(QString());
        comboBox_mutation_julia_injection->setObjectName(QString::fromUtf8("comboBox_mutation_julia_injection"));

        gridLayout_mutation->addWidget(comboBox_mutation_julia_injection, 19, 1, 1, 1);

        label_mutation_julia_start = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_start->setObjectName(QString::fromUtf8("label_mutation_julia_start"));

        gridLayout_mutation->addWidget(label_mutation_julia_start, 20, 0, 1, 1);

        comboBox_mutation_julia_start = new QComboBox(groupCheck_mutation_enabled);
        comboBox_mutation_julia_start->addItem(QString());
        comboBox_mutation_julia_start->addItem(QString());
        comboBox_mutation_julia_start->addItem(QString());
        comboBox_mutation_julia_start->addItem(QString());
        comboBox_mutation_julia_start->addItem(QString());
        comboBox_mutation_julia_start->addItem(QString());
        comboBox_mutation_julia_start->addItem(QString());
        comboBox_mutation_julia_start->addItem(QString());
        comboBox_mutation_julia_start->addItem(QString());
        comboBox_mutation_julia_start->addItem(QString());
        comboBox_mutation_julia_start->setObjectName(QString::fromUtf8("comboBox_mutation_julia_start"));

        gridLayout_mutation->addWidget(comboBox_mutation_julia_start, 20, 1, 1, 1);

        label_mutation_julia_c_transform = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_c_transform->setObjectName(QString::fromUtf8("label_mutation_julia_c_transform"));

        gridLayout_mutation->addWidget(label_mutation_julia_c_transform, 21, 0, 1, 1);

        comboBox_mutation_julia_c_transform = new QComboBox(groupCheck_mutation_enabled);
        comboBox_mutation_julia_c_transform->addItem(QString());
        comboBox_mutation_julia_c_transform->addItem(QString());
        comboBox_mutation_julia_c_transform->addItem(QString());
        comboBox_mutation_julia_c_transform->addItem(QString());
        comboBox_mutation_julia_c_transform->addItem(QString());
        comboBox_mutation_julia_c_transform->addItem(QString());
        comboBox_mutation_julia_c_transform->addItem(QString());
        comboBox_mutation_julia_c_transform->addItem(QString());
        comboBox_mutation_julia_c_transform->addItem(QString());
        comboBox_mutation_julia_c_transform->addItem(QString());
        comboBox_mutation_julia_c_transform->addItem(QString());
        comboBox_mutation_julia_c_transform->addItem(QString());
        comboBox_mutation_julia_c_transform->setObjectName(QString::fromUtf8("comboBox_mutation_julia_c_transform"));

        gridLayout_mutation->addWidget(comboBox_mutation_julia_c_transform, 21, 1, 1, 1);

        label_mutation_julia_dynamic = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_dynamic->setObjectName(QString::fromUtf8("label_mutation_julia_dynamic"));

        gridLayout_mutation->addWidget(label_mutation_julia_dynamic, 22, 0, 1, 1);

        comboBox_mutation_julia_dynamic = new QComboBox(groupCheck_mutation_enabled);
        comboBox_mutation_julia_dynamic->addItem(QString());
        comboBox_mutation_julia_dynamic->addItem(QString());
        comboBox_mutation_julia_dynamic->addItem(QString());
        comboBox_mutation_julia_dynamic->addItem(QString());
        comboBox_mutation_julia_dynamic->addItem(QString());
        comboBox_mutation_julia_dynamic->addItem(QString());
        comboBox_mutation_julia_dynamic->addItem(QString());
        comboBox_mutation_julia_dynamic->addItem(QString());
        comboBox_mutation_julia_dynamic->addItem(QString());
        comboBox_mutation_julia_dynamic->addItem(QString());
        comboBox_mutation_julia_dynamic->addItem(QString());
        comboBox_mutation_julia_dynamic->addItem(QString());
        comboBox_mutation_julia_dynamic->setObjectName(QString::fromUtf8("comboBox_mutation_julia_dynamic"));

        gridLayout_mutation->addWidget(comboBox_mutation_julia_dynamic, 22, 1, 1, 1);

        label_mutation_julia_multi = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_multi->setObjectName(QString::fromUtf8("label_mutation_julia_multi"));

        gridLayout_mutation->addWidget(label_mutation_julia_multi, 23, 0, 1, 1);

        comboBox_mutation_julia_multi = new QComboBox(groupCheck_mutation_enabled);
        comboBox_mutation_julia_multi->addItem(QString());
        comboBox_mutation_julia_multi->addItem(QString());
        comboBox_mutation_julia_multi->addItem(QString());
        comboBox_mutation_julia_multi->addItem(QString());
        comboBox_mutation_julia_multi->addItem(QString());
        comboBox_mutation_julia_multi->addItem(QString());
        comboBox_mutation_julia_multi->addItem(QString());
        comboBox_mutation_julia_multi->addItem(QString());
        comboBox_mutation_julia_multi->addItem(QString());
        comboBox_mutation_julia_multi->addItem(QString());
        comboBox_mutation_julia_multi->addItem(QString());
        comboBox_mutation_julia_multi->addItem(QString());
        comboBox_mutation_julia_multi->setObjectName(QString::fromUtf8("comboBox_mutation_julia_multi"));

        gridLayout_mutation->addWidget(comboBox_mutation_julia_multi, 23, 1, 1, 1);

        label_mutation_julia_c_mul = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_c_mul->setObjectName(QString::fromUtf8("label_mutation_julia_c_mul"));

        gridLayout_mutation->addWidget(label_mutation_julia_c_mul, 24, 0, 1, 1);

        spinbox_mutation_julia_c_mul = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_julia_c_mul->setObjectName(QString::fromUtf8("spinbox_mutation_julia_c_mul"));
        spinbox_mutation_julia_c_mul->setMinimum(-10.000000000000000);
        spinbox_mutation_julia_c_mul->setMaximum(10.000000000000000);
        spinbox_mutation_julia_c_mul->setSingleStep(0.100000000000000);
        spinbox_mutation_julia_c_mul->setValue(1.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_julia_c_mul, 24, 1, 1, 1);

        label_mutation_julia_pulse_freq = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_pulse_freq->setObjectName(QString::fromUtf8("label_mutation_julia_pulse_freq"));

        gridLayout_mutation->addWidget(label_mutation_julia_pulse_freq, 25, 0, 1, 1);

        spinbox_mutation_julia_pulse_freq = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_julia_pulse_freq->setObjectName(QString::fromUtf8("spinbox_mutation_julia_pulse_freq"));
        spinbox_mutation_julia_pulse_freq->setMinimum(0.010000000000000);
        spinbox_mutation_julia_pulse_freq->setMaximum(100.000000000000000);
        spinbox_mutation_julia_pulse_freq->setSingleStep(0.100000000000000);
        spinbox_mutation_julia_pulse_freq->setValue(1.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_julia_pulse_freq, 25, 1, 1, 1);

        label_mutation_julia_absorb = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_absorb->setObjectName(QString::fromUtf8("label_mutation_julia_absorb"));

        gridLayout_mutation->addWidget(label_mutation_julia_absorb, 26, 0, 1, 1);

        spinbox_mutation_julia_absorb = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_julia_absorb->setObjectName(QString::fromUtf8("spinbox_mutation_julia_absorb"));
        spinbox_mutation_julia_absorb->setMinimum(0.000000000000000);
        spinbox_mutation_julia_absorb->setMaximum(1.000000000000000);
        spinbox_mutation_julia_absorb->setSingleStep(0.010000000000000);
        spinbox_mutation_julia_absorb->setValue(0.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_julia_absorb, 26, 1, 1, 1);

        label_mutation_julia_c_power = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_c_power->setObjectName(QString::fromUtf8("label_mutation_julia_c_power"));

        gridLayout_mutation->addWidget(label_mutation_julia_c_power, 27, 0, 1, 1);

        spinbox_mutation_julia_c_power = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_julia_c_power->setObjectName(QString::fromUtf8("spinbox_mutation_julia_c_power"));
        spinbox_mutation_julia_c_power->setMinimum(0.100000000000000);
        spinbox_mutation_julia_c_power->setMaximum(10.000000000000000);
        spinbox_mutation_julia_c_power->setSingleStep(0.100000000000000);
        spinbox_mutation_julia_c_power->setValue(2.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_julia_c_power, 27, 1, 1, 1);

        label_mutation_julia_c_radius = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_c_radius->setObjectName(QString::fromUtf8("label_mutation_julia_c_radius"));

        gridLayout_mutation->addWidget(label_mutation_julia_c_radius, 28, 0, 1, 1);

        spinbox_mutation_julia_c_radius = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_julia_c_radius->setObjectName(QString::fromUtf8("spinbox_mutation_julia_c_radius"));
        spinbox_mutation_julia_c_radius->setMinimum(0.010000000000000);
        spinbox_mutation_julia_c_radius->setMaximum(100.000000000000000);
        spinbox_mutation_julia_c_radius->setSingleStep(0.100000000000000);
        spinbox_mutation_julia_c_radius->setValue(1.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_julia_c_radius, 28, 1, 1, 1);

        label_mutation_section_iter_header = new QLabel(groupCheck_mutation_enabled);
        label_mutation_section_iter_header->setObjectName(QString::fromUtf8("label_mutation_section_iter_header"));
        label_mutation_section_iter_header->setAlignment(Qt::AlignCenter);

        gridLayout_mutation->addWidget(label_mutation_section_iter_header, 50, 0, 1, 7);

        label_mutation_pre_iter = new QLabel(groupCheck_mutation_enabled);
        label_mutation_pre_iter->setObjectName(QString::fromUtf8("label_mutation_pre_iter"));

        gridLayout_mutation->addWidget(label_mutation_pre_iter, 51, 0, 1, 1);

        label_mutation_pre_iter_s = new QLabel(groupCheck_mutation_enabled);
        label_mutation_pre_iter_s->setObjectName(QString::fromUtf8("label_mutation_pre_iter_s"));
        label_mutation_pre_iter_s->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_pre_iter_s, 51, 1, 1, 1);

        spinboxInt_mutation_pre_iter_start = new MySpinBox(groupCheck_mutation_enabled);
        spinboxInt_mutation_pre_iter_start->setObjectName(QString::fromUtf8("spinboxInt_mutation_pre_iter_start"));
        spinboxInt_mutation_pre_iter_start->setMinimum(0);
        spinboxInt_mutation_pre_iter_start->setMaximum(10000);
        spinboxInt_mutation_pre_iter_start->setValue(0);

        gridLayout_mutation->addWidget(spinboxInt_mutation_pre_iter_start, 51, 2, 1, 1);

        label_mutation_pre_iter_e = new QLabel(groupCheck_mutation_enabled);
        label_mutation_pre_iter_e->setObjectName(QString::fromUtf8("label_mutation_pre_iter_e"));
        label_mutation_pre_iter_e->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_pre_iter_e, 51, 3, 1, 1);

        spinboxInt_mutation_pre_iter_stop = new MySpinBox(groupCheck_mutation_enabled);
        spinboxInt_mutation_pre_iter_stop->setObjectName(QString::fromUtf8("spinboxInt_mutation_pre_iter_stop"));
        spinboxInt_mutation_pre_iter_stop->setMinimum(0);
        spinboxInt_mutation_pre_iter_stop->setMaximum(10000);
        spinboxInt_mutation_pre_iter_stop->setValue(10000);

        gridLayout_mutation->addWidget(spinboxInt_mutation_pre_iter_stop, 51, 4, 1, 2);

        label_mutation_fold_iter = new QLabel(groupCheck_mutation_enabled);
        label_mutation_fold_iter->setObjectName(QString::fromUtf8("label_mutation_fold_iter"));

        gridLayout_mutation->addWidget(label_mutation_fold_iter, 52, 0, 1, 1);

        label_mutation_fold_iter_s = new QLabel(groupCheck_mutation_enabled);
        label_mutation_fold_iter_s->setObjectName(QString::fromUtf8("label_mutation_fold_iter_s"));
        label_mutation_fold_iter_s->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_fold_iter_s, 52, 1, 1, 1);

        spinboxInt_mutation_fold_iter_start = new MySpinBox(groupCheck_mutation_enabled);
        spinboxInt_mutation_fold_iter_start->setObjectName(QString::fromUtf8("spinboxInt_mutation_fold_iter_start"));
        spinboxInt_mutation_fold_iter_start->setMinimum(0);
        spinboxInt_mutation_fold_iter_start->setMaximum(10000);
        spinboxInt_mutation_fold_iter_start->setValue(0);

        gridLayout_mutation->addWidget(spinboxInt_mutation_fold_iter_start, 52, 2, 1, 1);

        label_mutation_fold_iter_e = new QLabel(groupCheck_mutation_enabled);
        label_mutation_fold_iter_e->setObjectName(QString::fromUtf8("label_mutation_fold_iter_e"));
        label_mutation_fold_iter_e->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_fold_iter_e, 52, 3, 1, 1);

        spinboxInt_mutation_fold_iter_stop = new MySpinBox(groupCheck_mutation_enabled);
        spinboxInt_mutation_fold_iter_stop->setObjectName(QString::fromUtf8("spinboxInt_mutation_fold_iter_stop"));
        spinboxInt_mutation_fold_iter_stop->setMinimum(0);
        spinboxInt_mutation_fold_iter_stop->setMaximum(10000);
        spinboxInt_mutation_fold_iter_stop->setValue(10000);

        gridLayout_mutation->addWidget(spinboxInt_mutation_fold_iter_stop, 52, 4, 1, 2);

        label_mutation_warp_iter = new QLabel(groupCheck_mutation_enabled);
        label_mutation_warp_iter->setObjectName(QString::fromUtf8("label_mutation_warp_iter"));

        gridLayout_mutation->addWidget(label_mutation_warp_iter, 53, 0, 1, 1);

        label_mutation_warp_iter_s = new QLabel(groupCheck_mutation_enabled);
        label_mutation_warp_iter_s->setObjectName(QString::fromUtf8("label_mutation_warp_iter_s"));
        label_mutation_warp_iter_s->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_warp_iter_s, 53, 1, 1, 1);

        spinboxInt_mutation_warp_iter_start = new MySpinBox(groupCheck_mutation_enabled);
        spinboxInt_mutation_warp_iter_start->setObjectName(QString::fromUtf8("spinboxInt_mutation_warp_iter_start"));
        spinboxInt_mutation_warp_iter_start->setMinimum(0);
        spinboxInt_mutation_warp_iter_start->setMaximum(10000);
        spinboxInt_mutation_warp_iter_start->setValue(0);

        gridLayout_mutation->addWidget(spinboxInt_mutation_warp_iter_start, 53, 2, 1, 1);

        label_mutation_warp_iter_e = new QLabel(groupCheck_mutation_enabled);
        label_mutation_warp_iter_e->setObjectName(QString::fromUtf8("label_mutation_warp_iter_e"));
        label_mutation_warp_iter_e->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_warp_iter_e, 53, 3, 1, 1);

        spinboxInt_mutation_warp_iter_stop = new MySpinBox(groupCheck_mutation_enabled);
        spinboxInt_mutation_warp_iter_stop->setObjectName(QString::fromUtf8("spinboxInt_mutation_warp_iter_stop"));
        spinboxInt_mutation_warp_iter_stop->setMinimum(0);
        spinboxInt_mutation_warp_iter_stop->setMaximum(10000);
        spinboxInt_mutation_warp_iter_stop->setValue(10000);

        gridLayout_mutation->addWidget(spinboxInt_mutation_warp_iter_stop, 53, 4, 1, 2);

        label_mutation_math_iter = new QLabel(groupCheck_mutation_enabled);
        label_mutation_math_iter->setObjectName(QString::fromUtf8("label_mutation_math_iter"));

        gridLayout_mutation->addWidget(label_mutation_math_iter, 54, 0, 1, 1);

        label_mutation_math_iter_s = new QLabel(groupCheck_mutation_enabled);
        label_mutation_math_iter_s->setObjectName(QString::fromUtf8("label_mutation_math_iter_s"));
        label_mutation_math_iter_s->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_math_iter_s, 54, 1, 1, 1);

        spinboxInt_mutation_math_iter_start = new MySpinBox(groupCheck_mutation_enabled);
        spinboxInt_mutation_math_iter_start->setObjectName(QString::fromUtf8("spinboxInt_mutation_math_iter_start"));
        spinboxInt_mutation_math_iter_start->setMinimum(0);
        spinboxInt_mutation_math_iter_start->setMaximum(10000);
        spinboxInt_mutation_math_iter_start->setValue(0);

        gridLayout_mutation->addWidget(spinboxInt_mutation_math_iter_start, 54, 2, 1, 1);

        label_mutation_math_iter_e = new QLabel(groupCheck_mutation_enabled);
        label_mutation_math_iter_e->setObjectName(QString::fromUtf8("label_mutation_math_iter_e"));
        label_mutation_math_iter_e->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_math_iter_e, 54, 3, 1, 1);

        spinboxInt_mutation_math_iter_stop = new MySpinBox(groupCheck_mutation_enabled);
        spinboxInt_mutation_math_iter_stop->setObjectName(QString::fromUtf8("spinboxInt_mutation_math_iter_stop"));
        spinboxInt_mutation_math_iter_stop->setMinimum(0);
        spinboxInt_mutation_math_iter_stop->setMaximum(10000);
        spinboxInt_mutation_math_iter_stop->setValue(10000);

        gridLayout_mutation->addWidget(spinboxInt_mutation_math_iter_stop, 54, 4, 1, 2);

        label_mutation_post_iter = new QLabel(groupCheck_mutation_enabled);
        label_mutation_post_iter->setObjectName(QString::fromUtf8("label_mutation_post_iter"));

        gridLayout_mutation->addWidget(label_mutation_post_iter, 55, 0, 1, 1);

        label_mutation_post_iter_s = new QLabel(groupCheck_mutation_enabled);
        label_mutation_post_iter_s->setObjectName(QString::fromUtf8("label_mutation_post_iter_s"));
        label_mutation_post_iter_s->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_post_iter_s, 55, 1, 1, 1);

        spinboxInt_mutation_post_iter_start = new MySpinBox(groupCheck_mutation_enabled);
        spinboxInt_mutation_post_iter_start->setObjectName(QString::fromUtf8("spinboxInt_mutation_post_iter_start"));
        spinboxInt_mutation_post_iter_start->setMinimum(0);
        spinboxInt_mutation_post_iter_start->setMaximum(10000);
        spinboxInt_mutation_post_iter_start->setValue(0);

        gridLayout_mutation->addWidget(spinboxInt_mutation_post_iter_start, 55, 2, 1, 1);

        label_mutation_post_iter_e = new QLabel(groupCheck_mutation_enabled);
        label_mutation_post_iter_e->setObjectName(QString::fromUtf8("label_mutation_post_iter_e"));
        label_mutation_post_iter_e->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_post_iter_e, 55, 3, 1, 1);

        spinboxInt_mutation_post_iter_stop = new MySpinBox(groupCheck_mutation_enabled);
        spinboxInt_mutation_post_iter_stop->setObjectName(QString::fromUtf8("spinboxInt_mutation_post_iter_stop"));
        spinboxInt_mutation_post_iter_stop->setMinimum(0);
        spinboxInt_mutation_post_iter_stop->setMaximum(10000);
        spinboxInt_mutation_post_iter_stop->setValue(10000);

        gridLayout_mutation->addWidget(spinboxInt_mutation_post_iter_stop, 55, 4, 1, 2);

        label_mutation_julia_iter = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_iter->setObjectName(QString::fromUtf8("label_mutation_julia_iter"));

        gridLayout_mutation->addWidget(label_mutation_julia_iter, 56, 0, 1, 1);

        label_mutation_julia_iter_s = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_iter_s->setObjectName(QString::fromUtf8("label_mutation_julia_iter_s"));
        label_mutation_julia_iter_s->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_julia_iter_s, 56, 1, 1, 1);

        spinboxInt_mutation_julia_iter_start = new MySpinBox(groupCheck_mutation_enabled);
        spinboxInt_mutation_julia_iter_start->setObjectName(QString::fromUtf8("spinboxInt_mutation_julia_iter_start"));
        spinboxInt_mutation_julia_iter_start->setMinimum(0);
        spinboxInt_mutation_julia_iter_start->setMaximum(10000);
        spinboxInt_mutation_julia_iter_start->setValue(0);

        gridLayout_mutation->addWidget(spinboxInt_mutation_julia_iter_start, 56, 2, 1, 1);

        label_mutation_julia_iter_e = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_iter_e->setObjectName(QString::fromUtf8("label_mutation_julia_iter_e"));
        label_mutation_julia_iter_e->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_julia_iter_e, 56, 3, 1, 1);

        spinboxInt_mutation_julia_iter_stop = new MySpinBox(groupCheck_mutation_enabled);
        spinboxInt_mutation_julia_iter_stop->setObjectName(QString::fromUtf8("spinboxInt_mutation_julia_iter_stop"));
        spinboxInt_mutation_julia_iter_stop->setMinimum(0);
        spinboxInt_mutation_julia_iter_stop->setMaximum(10000);
        spinboxInt_mutation_julia_iter_stop->setValue(10000);

        gridLayout_mutation->addWidget(spinboxInt_mutation_julia_iter_stop, 56, 4, 1, 2);

        label_mutation_julia_ext_header = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_ext_header->setObjectName(QString::fromUtf8("label_mutation_julia_ext_header"));
        QFont font;
        font.setBold(true);
        label_mutation_julia_ext_header->setFont(font);

        gridLayout_mutation->addWidget(label_mutation_julia_ext_header, 57, 0, 1, 1);

        label_mutation_julia_decay_rate_l = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_decay_rate_l->setObjectName(QString::fromUtf8("label_mutation_julia_decay_rate_l"));
        label_mutation_julia_decay_rate_l->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_julia_decay_rate_l, 58, 0, 1, 1);

        spinbox_mutation_julia_decay_rate = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_julia_decay_rate->setObjectName(QString::fromUtf8("spinbox_mutation_julia_decay_rate"));
        spinbox_mutation_julia_decay_rate->setDecimals(4);
        spinbox_mutation_julia_decay_rate->setMinimum(0.001000000000000);
        spinbox_mutation_julia_decay_rate->setMaximum(10.000000000000000);
        spinbox_mutation_julia_decay_rate->setSingleStep(0.010000000000000);
        spinbox_mutation_julia_decay_rate->setValue(0.100000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_julia_decay_rate, 58, 1, 1, 2);

        label_mutation_julia_spiral_angle_l = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_spiral_angle_l->setObjectName(QString::fromUtf8("label_mutation_julia_spiral_angle_l"));
        label_mutation_julia_spiral_angle_l->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_julia_spiral_angle_l, 58, 3, 1, 1);

        spinbox_mutation_julia_spiral_angle = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_julia_spiral_angle->setObjectName(QString::fromUtf8("spinbox_mutation_julia_spiral_angle"));
        spinbox_mutation_julia_spiral_angle->setDecimals(2);
        spinbox_mutation_julia_spiral_angle->setMinimum(-360.000000000000000);
        spinbox_mutation_julia_spiral_angle->setMaximum(360.000000000000000);
        spinbox_mutation_julia_spiral_angle->setSingleStep(1.000000000000000);
        spinbox_mutation_julia_spiral_angle->setValue(15.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_julia_spiral_angle, 58, 4, 1, 2);

        label_mutation_julia_chaos_r_l = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_chaos_r_l->setObjectName(QString::fromUtf8("label_mutation_julia_chaos_r_l"));
        label_mutation_julia_chaos_r_l->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_julia_chaos_r_l, 59, 0, 1, 1);

        spinbox_mutation_julia_chaos_r = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_julia_chaos_r->setObjectName(QString::fromUtf8("spinbox_mutation_julia_chaos_r"));
        spinbox_mutation_julia_chaos_r->setDecimals(3);
        spinbox_mutation_julia_chaos_r->setMinimum(2.500000000000000);
        spinbox_mutation_julia_chaos_r->setMaximum(4.000000000000000);
        spinbox_mutation_julia_chaos_r->setSingleStep(0.010000000000000);
        spinbox_mutation_julia_chaos_r->setValue(3.800000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_julia_chaos_r, 59, 1, 1, 2);

        label_mutation_julia_threshold_l = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_threshold_l->setObjectName(QString::fromUtf8("label_mutation_julia_threshold_l"));
        label_mutation_julia_threshold_l->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_julia_threshold_l, 59, 3, 1, 1);

        spinbox_mutation_julia_threshold = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_julia_threshold->setObjectName(QString::fromUtf8("spinbox_mutation_julia_threshold"));
        spinbox_mutation_julia_threshold->setDecimals(3);
        spinbox_mutation_julia_threshold->setMinimum(0.000000000000000);
        spinbox_mutation_julia_threshold->setMaximum(100.000000000000000);
        spinbox_mutation_julia_threshold->setSingleStep(0.100000000000000);
        spinbox_mutation_julia_threshold->setValue(1.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_julia_threshold, 59, 4, 1, 2);

        label_mutation_julia_gradient_end_l = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_gradient_end_l->setObjectName(QString::fromUtf8("label_mutation_julia_gradient_end_l"));
        label_mutation_julia_gradient_end_l->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_julia_gradient_end_l, 60, 0, 1, 1);

        spinbox_mutation_julia_gradient_end = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_julia_gradient_end->setObjectName(QString::fromUtf8("spinbox_mutation_julia_gradient_end"));
        spinbox_mutation_julia_gradient_end->setDecimals(3);
        spinbox_mutation_julia_gradient_end->setMinimum(-10.000000000000000);
        spinbox_mutation_julia_gradient_end->setMaximum(10.000000000000000);
        spinbox_mutation_julia_gradient_end->setSingleStep(0.100000000000000);
        spinbox_mutation_julia_gradient_end->setValue(0.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_julia_gradient_end, 60, 1, 1, 2);

        label_mutation_julia_box_fold_limit_l = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_box_fold_limit_l->setObjectName(QString::fromUtf8("label_mutation_julia_box_fold_limit_l"));
        label_mutation_julia_box_fold_limit_l->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_julia_box_fold_limit_l, 60, 3, 1, 1);

        spinbox_mutation_julia_box_fold_limit = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_julia_box_fold_limit->setObjectName(QString::fromUtf8("spinbox_mutation_julia_box_fold_limit"));
        spinbox_mutation_julia_box_fold_limit->setDecimals(3);
        spinbox_mutation_julia_box_fold_limit->setMinimum(0.010000000000000);
        spinbox_mutation_julia_box_fold_limit->setMaximum(100.000000000000000);
        spinbox_mutation_julia_box_fold_limit->setSingleStep(0.100000000000000);
        spinbox_mutation_julia_box_fold_limit->setValue(1.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_julia_box_fold_limit, 60, 4, 1, 2);

        label_mutation_julia_start_epsilon_l = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_start_epsilon_l->setObjectName(QString::fromUtf8("label_mutation_julia_start_epsilon_l"));
        label_mutation_julia_start_epsilon_l->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_julia_start_epsilon_l, 61, 0, 1, 1);

        spinbox_mutation_julia_start_epsilon = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_julia_start_epsilon->setObjectName(QString::fromUtf8("spinbox_mutation_julia_start_epsilon"));
        spinbox_mutation_julia_start_epsilon->setDecimals(5);
        spinbox_mutation_julia_start_epsilon->setMinimum(0.000100000000000);
        spinbox_mutation_julia_start_epsilon->setMaximum(1.000000000000000);
        spinbox_mutation_julia_start_epsilon->setSingleStep(0.001000000000000);
        spinbox_mutation_julia_start_epsilon->setValue(0.001000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_julia_start_epsilon, 61, 1, 1, 2);

        label_mutation_julia_layer_c2_l = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_layer_c2_l->setObjectName(QString::fromUtf8("label_mutation_julia_layer_c2_l"));
        label_mutation_julia_layer_c2_l->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_julia_layer_c2_l, 61, 3, 1, 1);

        spinboxd3_mutation_julia_layer_c2_x = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinboxd3_mutation_julia_layer_c2_x->setObjectName(QString::fromUtf8("spinboxd3_mutation_julia_layer_c2_x"));
        spinboxd3_mutation_julia_layer_c2_x->setDecimals(4);
        spinboxd3_mutation_julia_layer_c2_x->setMinimum(-10.000000000000000);
        spinboxd3_mutation_julia_layer_c2_x->setMaximum(10.000000000000000);
        spinboxd3_mutation_julia_layer_c2_x->setSingleStep(0.100000000000000);

        gridLayout_mutation->addWidget(spinboxd3_mutation_julia_layer_c2_x, 61, 4, 1, 2);

        label_mutation_julia_layer_c2_yz_l = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_layer_c2_yz_l->setObjectName(QString::fromUtf8("label_mutation_julia_layer_c2_yz_l"));
        label_mutation_julia_layer_c2_yz_l->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_julia_layer_c2_yz_l, 62, 0, 1, 1);

        spinboxd3_mutation_julia_layer_c2_y = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinboxd3_mutation_julia_layer_c2_y->setObjectName(QString::fromUtf8("spinboxd3_mutation_julia_layer_c2_y"));
        spinboxd3_mutation_julia_layer_c2_y->setDecimals(4);
        spinboxd3_mutation_julia_layer_c2_y->setMinimum(-10.000000000000000);
        spinboxd3_mutation_julia_layer_c2_y->setMaximum(10.000000000000000);
        spinboxd3_mutation_julia_layer_c2_y->setSingleStep(0.100000000000000);

        gridLayout_mutation->addWidget(spinboxd3_mutation_julia_layer_c2_y, 62, 1, 1, 2);

        spinboxd3_mutation_julia_layer_c2_z = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinboxd3_mutation_julia_layer_c2_z->setObjectName(QString::fromUtf8("spinboxd3_mutation_julia_layer_c2_z"));
        spinboxd3_mutation_julia_layer_c2_z->setDecimals(4);
        spinboxd3_mutation_julia_layer_c2_z->setMinimum(-10.000000000000000);
        spinboxd3_mutation_julia_layer_c2_z->setMaximum(10.000000000000000);
        spinboxd3_mutation_julia_layer_c2_z->setSingleStep(0.100000000000000);

        gridLayout_mutation->addWidget(spinboxd3_mutation_julia_layer_c2_z, 62, 3, 1, 3);

        label_mutation_julia_dist_band_l = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_dist_band_l->setObjectName(QString::fromUtf8("label_mutation_julia_dist_band_l"));
        label_mutation_julia_dist_band_l->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_julia_dist_band_l, 63, 0, 1, 1);

        spinbox_mutation_julia_dist_band_mid = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_julia_dist_band_mid->setObjectName(QString::fromUtf8("spinbox_mutation_julia_dist_band_mid"));
        spinbox_mutation_julia_dist_band_mid->setDecimals(3);
        spinbox_mutation_julia_dist_band_mid->setMinimum(0.000000000000000);
        spinbox_mutation_julia_dist_band_mid->setMaximum(100.000000000000000);
        spinbox_mutation_julia_dist_band_mid->setSingleStep(0.100000000000000);
        spinbox_mutation_julia_dist_band_mid->setValue(1.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_julia_dist_band_mid, 63, 1, 1, 2);

        label_mutation_julia_dist_band_far_l = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_dist_band_far_l->setObjectName(QString::fromUtf8("label_mutation_julia_dist_band_far_l"));
        label_mutation_julia_dist_band_far_l->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_julia_dist_band_far_l, 63, 3, 1, 1);

        spinbox_mutation_julia_dist_band_far = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_julia_dist_band_far->setObjectName(QString::fromUtf8("spinbox_mutation_julia_dist_band_far"));
        spinbox_mutation_julia_dist_band_far->setDecimals(3);
        spinbox_mutation_julia_dist_band_far->setMinimum(0.000000000000000);
        spinbox_mutation_julia_dist_band_far->setMaximum(100.000000000000000);
        spinbox_mutation_julia_dist_band_far->setSingleStep(0.100000000000000);
        spinbox_mutation_julia_dist_band_far->setValue(2.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_julia_dist_band_far, 63, 4, 1, 2);

        label_julia_finetune_header = new QLabel(groupCheck_mutation_enabled);
        label_julia_finetune_header->setObjectName(QString::fromUtf8("label_julia_finetune_header"));
        label_julia_finetune_header->setFont(font);

        gridLayout_mutation->addWidget(label_julia_finetune_header, 64, 0, 1, 1);

        label_mutation_julia_ctransform_iter_start_l = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_ctransform_iter_start_l->setObjectName(QString::fromUtf8("label_mutation_julia_ctransform_iter_start_l"));

        gridLayout_mutation->addWidget(label_mutation_julia_ctransform_iter_start_l, 65, 0, 1, 1);

        spinboxInt_mutation_julia_ctransform_iter_start = new MySpinBox(groupCheck_mutation_enabled);
        spinboxInt_mutation_julia_ctransform_iter_start->setObjectName(QString::fromUtf8("spinboxInt_mutation_julia_ctransform_iter_start"));
        spinboxInt_mutation_julia_ctransform_iter_start->setMinimum(0);
        spinboxInt_mutation_julia_ctransform_iter_start->setMaximum(10000);
        spinboxInt_mutation_julia_ctransform_iter_start->setValue(0);

        gridLayout_mutation->addWidget(spinboxInt_mutation_julia_ctransform_iter_start, 65, 1, 1, 1);

        label_mutation_julia_ctransform_iter_stop_l = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_ctransform_iter_stop_l->setObjectName(QString::fromUtf8("label_mutation_julia_ctransform_iter_stop_l"));

        gridLayout_mutation->addWidget(label_mutation_julia_ctransform_iter_stop_l, 66, 0, 1, 1);

        spinboxInt_mutation_julia_ctransform_iter_stop = new MySpinBox(groupCheck_mutation_enabled);
        spinboxInt_mutation_julia_ctransform_iter_stop->setObjectName(QString::fromUtf8("spinboxInt_mutation_julia_ctransform_iter_stop"));
        spinboxInt_mutation_julia_ctransform_iter_stop->setMinimum(0);
        spinboxInt_mutation_julia_ctransform_iter_stop->setMaximum(10000);
        spinboxInt_mutation_julia_ctransform_iter_stop->setValue(10000);

        gridLayout_mutation->addWidget(spinboxInt_mutation_julia_ctransform_iter_stop, 66, 1, 1, 1);

        label_mutation_julia_dynamic_iter_start_l = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_dynamic_iter_start_l->setObjectName(QString::fromUtf8("label_mutation_julia_dynamic_iter_start_l"));

        gridLayout_mutation->addWidget(label_mutation_julia_dynamic_iter_start_l, 67, 0, 1, 1);

        spinboxInt_mutation_julia_dynamic_iter_start = new MySpinBox(groupCheck_mutation_enabled);
        spinboxInt_mutation_julia_dynamic_iter_start->setObjectName(QString::fromUtf8("spinboxInt_mutation_julia_dynamic_iter_start"));
        spinboxInt_mutation_julia_dynamic_iter_start->setMinimum(0);
        spinboxInt_mutation_julia_dynamic_iter_start->setMaximum(10000);
        spinboxInt_mutation_julia_dynamic_iter_start->setValue(0);

        gridLayout_mutation->addWidget(spinboxInt_mutation_julia_dynamic_iter_start, 67, 1, 1, 1);

        label_mutation_julia_dynamic_iter_stop_l = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_dynamic_iter_stop_l->setObjectName(QString::fromUtf8("label_mutation_julia_dynamic_iter_stop_l"));

        gridLayout_mutation->addWidget(label_mutation_julia_dynamic_iter_stop_l, 68, 0, 1, 1);

        spinboxInt_mutation_julia_dynamic_iter_stop = new MySpinBox(groupCheck_mutation_enabled);
        spinboxInt_mutation_julia_dynamic_iter_stop->setObjectName(QString::fromUtf8("spinboxInt_mutation_julia_dynamic_iter_stop"));
        spinboxInt_mutation_julia_dynamic_iter_stop->setMinimum(0);
        spinboxInt_mutation_julia_dynamic_iter_stop->setMaximum(10000);
        spinboxInt_mutation_julia_dynamic_iter_stop->setValue(10000);

        gridLayout_mutation->addWidget(spinboxInt_mutation_julia_dynamic_iter_stop, 68, 1, 1, 1);

        label_mutation_julia_multi_iter_start_l = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_multi_iter_start_l->setObjectName(QString::fromUtf8("label_mutation_julia_multi_iter_start_l"));

        gridLayout_mutation->addWidget(label_mutation_julia_multi_iter_start_l, 69, 0, 1, 1);

        spinboxInt_mutation_julia_multi_iter_start = new MySpinBox(groupCheck_mutation_enabled);
        spinboxInt_mutation_julia_multi_iter_start->setObjectName(QString::fromUtf8("spinboxInt_mutation_julia_multi_iter_start"));
        spinboxInt_mutation_julia_multi_iter_start->setMinimum(0);
        spinboxInt_mutation_julia_multi_iter_start->setMaximum(10000);
        spinboxInt_mutation_julia_multi_iter_start->setValue(0);

        gridLayout_mutation->addWidget(spinboxInt_mutation_julia_multi_iter_start, 69, 1, 1, 1);

        label_mutation_julia_multi_iter_stop_l = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_multi_iter_stop_l->setObjectName(QString::fromUtf8("label_mutation_julia_multi_iter_stop_l"));

        gridLayout_mutation->addWidget(label_mutation_julia_multi_iter_stop_l, 70, 0, 1, 1);

        spinboxInt_mutation_julia_multi_iter_stop = new MySpinBox(groupCheck_mutation_enabled);
        spinboxInt_mutation_julia_multi_iter_stop->setObjectName(QString::fromUtf8("spinboxInt_mutation_julia_multi_iter_stop"));
        spinboxInt_mutation_julia_multi_iter_stop->setMinimum(0);
        spinboxInt_mutation_julia_multi_iter_stop->setMaximum(10000);
        spinboxInt_mutation_julia_multi_iter_stop->setValue(10000);

        gridLayout_mutation->addWidget(spinboxInt_mutation_julia_multi_iter_stop, 70, 1, 1, 1);

        label_mutation_julia_ctransform_strength_l = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_ctransform_strength_l->setObjectName(QString::fromUtf8("label_mutation_julia_ctransform_strength_l"));

        gridLayout_mutation->addWidget(label_mutation_julia_ctransform_strength_l, 71, 0, 1, 1);

        spinbox_mutation_julia_ctransform_strength = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_julia_ctransform_strength->setObjectName(QString::fromUtf8("spinbox_mutation_julia_ctransform_strength"));
        spinbox_mutation_julia_ctransform_strength->setDecimals(3);
        spinbox_mutation_julia_ctransform_strength->setMinimum(0.000000000000000);
        spinbox_mutation_julia_ctransform_strength->setMaximum(2.000000000000000);
        spinbox_mutation_julia_ctransform_strength->setSingleStep(0.050000000000000);
        spinbox_mutation_julia_ctransform_strength->setValue(1.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_julia_ctransform_strength, 71, 1, 1, 1);

        label_mutation_julia_dynamic_strength_l = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_dynamic_strength_l->setObjectName(QString::fromUtf8("label_mutation_julia_dynamic_strength_l"));

        gridLayout_mutation->addWidget(label_mutation_julia_dynamic_strength_l, 72, 0, 1, 1);

        spinbox_mutation_julia_dynamic_strength = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_julia_dynamic_strength->setObjectName(QString::fromUtf8("spinbox_mutation_julia_dynamic_strength"));
        spinbox_mutation_julia_dynamic_strength->setDecimals(3);
        spinbox_mutation_julia_dynamic_strength->setMinimum(0.000000000000000);
        spinbox_mutation_julia_dynamic_strength->setMaximum(5.000000000000000);
        spinbox_mutation_julia_dynamic_strength->setSingleStep(0.050000000000000);
        spinbox_mutation_julia_dynamic_strength->setValue(1.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_julia_dynamic_strength, 72, 1, 1, 1);

        label_mutation_julia_multi_strength_l = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_multi_strength_l->setObjectName(QString::fromUtf8("label_mutation_julia_multi_strength_l"));

        gridLayout_mutation->addWidget(label_mutation_julia_multi_strength_l, 73, 0, 1, 1);

        spinbox_mutation_julia_multi_strength = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_julia_multi_strength->setObjectName(QString::fromUtf8("spinbox_mutation_julia_multi_strength"));
        spinbox_mutation_julia_multi_strength->setDecimals(3);
        spinbox_mutation_julia_multi_strength->setMinimum(0.000000000000000);
        spinbox_mutation_julia_multi_strength->setMaximum(2.000000000000000);
        spinbox_mutation_julia_multi_strength->setSingleStep(0.050000000000000);
        spinbox_mutation_julia_multi_strength->setValue(1.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_julia_multi_strength, 73, 1, 1, 1);

        label_mutation_julia_injection_strength_l = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_injection_strength_l->setObjectName(QString::fromUtf8("label_mutation_julia_injection_strength_l"));

        gridLayout_mutation->addWidget(label_mutation_julia_injection_strength_l, 74, 0, 1, 1);

        spinbox_mutation_julia_injection_strength = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_julia_injection_strength->setObjectName(QString::fromUtf8("spinbox_mutation_julia_injection_strength"));
        spinbox_mutation_julia_injection_strength->setDecimals(3);
        spinbox_mutation_julia_injection_strength->setMinimum(0.000000000000000);
        spinbox_mutation_julia_injection_strength->setMaximum(10.000000000000000);
        spinbox_mutation_julia_injection_strength->setSingleStep(0.100000000000000);
        spinbox_mutation_julia_injection_strength->setValue(1.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_julia_injection_strength, 74, 1, 1, 1);

        label_mutation_julia_de_factor_l = new QLabel(groupCheck_mutation_enabled);
        label_mutation_julia_de_factor_l->setObjectName(QString::fromUtf8("label_mutation_julia_de_factor_l"));

        gridLayout_mutation->addWidget(label_mutation_julia_de_factor_l, 75, 0, 1, 1);

        spinbox_mutation_julia_de_factor = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinbox_mutation_julia_de_factor->setObjectName(QString::fromUtf8("spinbox_mutation_julia_de_factor"));
        spinbox_mutation_julia_de_factor->setDecimals(3);
        spinbox_mutation_julia_de_factor->setMinimum(0.100000000000000);
        spinbox_mutation_julia_de_factor->setMaximum(2.000000000000000);
        spinbox_mutation_julia_de_factor->setSingleStep(0.050000000000000);
        spinbox_mutation_julia_de_factor->setValue(1.000000000000000);

        gridLayout_mutation->addWidget(spinbox_mutation_julia_de_factor, 75, 1, 1, 1);

        label_mutation_de_iter = new QLabel(groupCheck_mutation_enabled);
        label_mutation_de_iter->setObjectName(QString::fromUtf8("label_mutation_de_iter"));

        gridLayout_mutation->addWidget(label_mutation_de_iter, 76, 0, 1, 1);

        label_mutation_de_iter_s = new QLabel(groupCheck_mutation_enabled);
        label_mutation_de_iter_s->setObjectName(QString::fromUtf8("label_mutation_de_iter_s"));
        label_mutation_de_iter_s->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_de_iter_s, 57, 1, 1, 1);

        spinboxInt_mutation_de_iter_start = new MySpinBox(groupCheck_mutation_enabled);
        spinboxInt_mutation_de_iter_start->setObjectName(QString::fromUtf8("spinboxInt_mutation_de_iter_start"));
        spinboxInt_mutation_de_iter_start->setMinimum(0);
        spinboxInt_mutation_de_iter_start->setMaximum(10000);
        spinboxInt_mutation_de_iter_start->setValue(0);

        gridLayout_mutation->addWidget(spinboxInt_mutation_de_iter_start, 57, 2, 1, 1);

        label_mutation_de_iter_e = new QLabel(groupCheck_mutation_enabled);
        label_mutation_de_iter_e->setObjectName(QString::fromUtf8("label_mutation_de_iter_e"));
        label_mutation_de_iter_e->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_mutation->addWidget(label_mutation_de_iter_e, 57, 3, 1, 1);

        spinboxInt_mutation_de_iter_stop = new MySpinBox(groupCheck_mutation_enabled);
        spinboxInt_mutation_de_iter_stop->setObjectName(QString::fromUtf8("spinboxInt_mutation_de_iter_stop"));
        spinboxInt_mutation_de_iter_stop->setMinimum(0);
        spinboxInt_mutation_de_iter_stop->setMaximum(10000);
        spinboxInt_mutation_de_iter_stop->setValue(10000);

        gridLayout_mutation->addWidget(spinboxInt_mutation_de_iter_stop, 57, 4, 1, 2);

        label_c_rotation = new QLabel(groupCheck_mutation_enabled);
        label_c_rotation->setObjectName(QString::fromUtf8("label_c_rotation"));

        gridLayout_mutation->addWidget(label_c_rotation, 29, 0, 1, 1);

        spinboxd3_mutation_julia_c_rot_x = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinboxd3_mutation_julia_c_rot_x->setObjectName(QString::fromUtf8("spinboxd3_mutation_julia_c_rot_x"));
        spinboxd3_mutation_julia_c_rot_x->setDecimals(2);
        spinboxd3_mutation_julia_c_rot_x->setMinimum(-360.000000000000000);
        spinboxd3_mutation_julia_c_rot_x->setMaximum(360.000000000000000);
        spinboxd3_mutation_julia_c_rot_x->setSingleStep(1.000000000000000);

        gridLayout_mutation->addWidget(spinboxd3_mutation_julia_c_rot_x, 29, 1, 1, 1);

        spinboxd3_mutation_julia_c_rot_y = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinboxd3_mutation_julia_c_rot_y->setObjectName(QString::fromUtf8("spinboxd3_mutation_julia_c_rot_y"));
        spinboxd3_mutation_julia_c_rot_y->setDecimals(2);
        spinboxd3_mutation_julia_c_rot_y->setMinimum(-360.000000000000000);
        spinboxd3_mutation_julia_c_rot_y->setMaximum(360.000000000000000);
        spinboxd3_mutation_julia_c_rot_y->setSingleStep(1.000000000000000);

        gridLayout_mutation->addWidget(spinboxd3_mutation_julia_c_rot_y, 29, 2, 1, 1);

        spinboxd3_mutation_julia_c_rot_z = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinboxd3_mutation_julia_c_rot_z->setObjectName(QString::fromUtf8("spinboxd3_mutation_julia_c_rot_z"));
        spinboxd3_mutation_julia_c_rot_z->setDecimals(2);
        spinboxd3_mutation_julia_c_rot_z->setMinimum(-360.000000000000000);
        spinboxd3_mutation_julia_c_rot_z->setMaximum(360.000000000000000);
        spinboxd3_mutation_julia_c_rot_z->setSingleStep(1.000000000000000);

        gridLayout_mutation->addWidget(spinboxd3_mutation_julia_c_rot_z, 29, 3, 1, 1);

        label_m_bius_a = new QLabel(groupCheck_mutation_enabled);
        label_m_bius_a->setObjectName(QString::fromUtf8("label_m_bius_a"));

        gridLayout_mutation->addWidget(label_m_bius_a, 30, 0, 1, 1);

        spinboxd_mutation_julia_c_mobius_a = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinboxd_mutation_julia_c_mobius_a->setObjectName(QString::fromUtf8("spinboxd_mutation_julia_c_mobius_a"));

        gridLayout_mutation->addWidget(spinboxd_mutation_julia_c_mobius_a, 30, 1, 1, 2);

        label_m_bius_b = new QLabel(groupCheck_mutation_enabled);
        label_m_bius_b->setObjectName(QString::fromUtf8("label_m_bius_b"));

        gridLayout_mutation->addWidget(label_m_bius_b, 31, 0, 1, 1);

        spinboxd_mutation_julia_c_mobius_b = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinboxd_mutation_julia_c_mobius_b->setObjectName(QString::fromUtf8("spinboxd_mutation_julia_c_mobius_b"));

        gridLayout_mutation->addWidget(spinboxd_mutation_julia_c_mobius_b, 31, 1, 1, 2);

        label_m_bius_d = new QLabel(groupCheck_mutation_enabled);
        label_m_bius_d->setObjectName(QString::fromUtf8("label_m_bius_d"));

        gridLayout_mutation->addWidget(label_m_bius_d, 32, 0, 1, 1);

        spinboxd_mutation_julia_c_mobius_d = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinboxd_mutation_julia_c_mobius_d->setObjectName(QString::fromUtf8("spinboxd_mutation_julia_c_mobius_d"));

        gridLayout_mutation->addWidget(spinboxd_mutation_julia_c_mobius_d, 32, 1, 1, 2);

        label_pulse_amp = new QLabel(groupCheck_mutation_enabled);
        label_pulse_amp->setObjectName(QString::fromUtf8("label_pulse_amp"));

        gridLayout_mutation->addWidget(label_pulse_amp, 33, 0, 1, 1);

        spinboxd_mutation_julia_pulse_amp = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinboxd_mutation_julia_pulse_amp->setObjectName(QString::fromUtf8("spinboxd_mutation_julia_pulse_amp"));

        gridLayout_mutation->addWidget(spinboxd_mutation_julia_pulse_amp, 33, 1, 1, 2);

        label_noise_freq = new QLabel(groupCheck_mutation_enabled);
        label_noise_freq->setObjectName(QString::fromUtf8("label_noise_freq"));

        gridLayout_mutation->addWidget(label_noise_freq, 34, 0, 1, 1);

        spinboxd_mutation_julia_noise_freq = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinboxd_mutation_julia_noise_freq->setObjectName(QString::fromUtf8("spinboxd_mutation_julia_noise_freq"));

        gridLayout_mutation->addWidget(spinboxd_mutation_julia_noise_freq, 34, 1, 1, 2);

        label_noise_amp = new QLabel(groupCheck_mutation_enabled);
        label_noise_amp->setObjectName(QString::fromUtf8("label_noise_amp"));

        gridLayout_mutation->addWidget(label_noise_amp, 35, 0, 1, 1);

        spinboxd_mutation_julia_noise_amp = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinboxd_mutation_julia_noise_amp->setObjectName(QString::fromUtf8("spinboxd_mutation_julia_noise_amp"));

        gridLayout_mutation->addWidget(spinboxd_mutation_julia_noise_amp, 35, 1, 1, 2);

        label_fourier_c2 = new QLabel(groupCheck_mutation_enabled);
        label_fourier_c2->setObjectName(QString::fromUtf8("label_fourier_c2"));

        gridLayout_mutation->addWidget(label_fourier_c2, 36, 0, 1, 1);

        spinboxd3_mutation_julia_fourier_c2_x = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinboxd3_mutation_julia_fourier_c2_x->setObjectName(QString::fromUtf8("spinboxd3_mutation_julia_fourier_c2_x"));
        spinboxd3_mutation_julia_fourier_c2_x->setDecimals(3);
        spinboxd3_mutation_julia_fourier_c2_x->setMinimum(-10.000000000000000);
        spinboxd3_mutation_julia_fourier_c2_x->setMaximum(10.000000000000000);
        spinboxd3_mutation_julia_fourier_c2_x->setSingleStep(0.100000000000000);

        gridLayout_mutation->addWidget(spinboxd3_mutation_julia_fourier_c2_x, 36, 1, 1, 1);

        spinboxd3_mutation_julia_fourier_c2_y = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinboxd3_mutation_julia_fourier_c2_y->setObjectName(QString::fromUtf8("spinboxd3_mutation_julia_fourier_c2_y"));
        spinboxd3_mutation_julia_fourier_c2_y->setDecimals(3);
        spinboxd3_mutation_julia_fourier_c2_y->setMinimum(-10.000000000000000);
        spinboxd3_mutation_julia_fourier_c2_y->setMaximum(10.000000000000000);
        spinboxd3_mutation_julia_fourier_c2_y->setSingleStep(0.100000000000000);

        gridLayout_mutation->addWidget(spinboxd3_mutation_julia_fourier_c2_y, 36, 2, 1, 1);

        spinboxd3_mutation_julia_fourier_c2_z = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinboxd3_mutation_julia_fourier_c2_z->setObjectName(QString::fromUtf8("spinboxd3_mutation_julia_fourier_c2_z"));
        spinboxd3_mutation_julia_fourier_c2_z->setDecimals(3);
        spinboxd3_mutation_julia_fourier_c2_z->setMinimum(-10.000000000000000);
        spinboxd3_mutation_julia_fourier_c2_z->setMaximum(10.000000000000000);
        spinboxd3_mutation_julia_fourier_c2_z->setSingleStep(0.100000000000000);

        gridLayout_mutation->addWidget(spinboxd3_mutation_julia_fourier_c2_z, 36, 3, 1, 1);

        label_fourier_c3 = new QLabel(groupCheck_mutation_enabled);
        label_fourier_c3->setObjectName(QString::fromUtf8("label_fourier_c3"));

        gridLayout_mutation->addWidget(label_fourier_c3, 37, 0, 1, 1);

        spinboxd3_mutation_julia_fourier_c3_x = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinboxd3_mutation_julia_fourier_c3_x->setObjectName(QString::fromUtf8("spinboxd3_mutation_julia_fourier_c3_x"));
        spinboxd3_mutation_julia_fourier_c3_x->setDecimals(3);
        spinboxd3_mutation_julia_fourier_c3_x->setMinimum(-10.000000000000000);
        spinboxd3_mutation_julia_fourier_c3_x->setMaximum(10.000000000000000);
        spinboxd3_mutation_julia_fourier_c3_x->setSingleStep(0.100000000000000);

        gridLayout_mutation->addWidget(spinboxd3_mutation_julia_fourier_c3_x, 37, 1, 1, 1);

        spinboxd3_mutation_julia_fourier_c3_y = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinboxd3_mutation_julia_fourier_c3_y->setObjectName(QString::fromUtf8("spinboxd3_mutation_julia_fourier_c3_y"));
        spinboxd3_mutation_julia_fourier_c3_y->setDecimals(3);
        spinboxd3_mutation_julia_fourier_c3_y->setMinimum(-10.000000000000000);
        spinboxd3_mutation_julia_fourier_c3_y->setMaximum(10.000000000000000);
        spinboxd3_mutation_julia_fourier_c3_y->setSingleStep(0.100000000000000);

        gridLayout_mutation->addWidget(spinboxd3_mutation_julia_fourier_c3_y, 37, 2, 1, 1);

        spinboxd3_mutation_julia_fourier_c3_z = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinboxd3_mutation_julia_fourier_c3_z->setObjectName(QString::fromUtf8("spinboxd3_mutation_julia_fourier_c3_z"));
        spinboxd3_mutation_julia_fourier_c3_z->setDecimals(3);
        spinboxd3_mutation_julia_fourier_c3_z->setMinimum(-10.000000000000000);
        spinboxd3_mutation_julia_fourier_c3_z->setMaximum(10.000000000000000);
        spinboxd3_mutation_julia_fourier_c3_z->setSingleStep(0.100000000000000);

        gridLayout_mutation->addWidget(spinboxd3_mutation_julia_fourier_c3_z, 37, 3, 1, 1);

        label_bipolar_cr = new QLabel(groupCheck_mutation_enabled);
        label_bipolar_cr->setObjectName(QString::fromUtf8("label_bipolar_cr"));

        gridLayout_mutation->addWidget(label_bipolar_cr, 38, 0, 1, 1);

        spinboxd3_mutation_julia_bipolar_cr_x = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinboxd3_mutation_julia_bipolar_cr_x->setObjectName(QString::fromUtf8("spinboxd3_mutation_julia_bipolar_cr_x"));
        spinboxd3_mutation_julia_bipolar_cr_x->setDecimals(3);
        spinboxd3_mutation_julia_bipolar_cr_x->setMinimum(-10.000000000000000);
        spinboxd3_mutation_julia_bipolar_cr_x->setMaximum(10.000000000000000);
        spinboxd3_mutation_julia_bipolar_cr_x->setSingleStep(0.100000000000000);

        gridLayout_mutation->addWidget(spinboxd3_mutation_julia_bipolar_cr_x, 38, 1, 1, 1);

        spinboxd3_mutation_julia_bipolar_cr_y = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinboxd3_mutation_julia_bipolar_cr_y->setObjectName(QString::fromUtf8("spinboxd3_mutation_julia_bipolar_cr_y"));
        spinboxd3_mutation_julia_bipolar_cr_y->setDecimals(3);
        spinboxd3_mutation_julia_bipolar_cr_y->setMinimum(-10.000000000000000);
        spinboxd3_mutation_julia_bipolar_cr_y->setMaximum(10.000000000000000);
        spinboxd3_mutation_julia_bipolar_cr_y->setSingleStep(0.100000000000000);

        gridLayout_mutation->addWidget(spinboxd3_mutation_julia_bipolar_cr_y, 38, 2, 1, 1);

        spinboxd3_mutation_julia_bipolar_cr_z = new MyDoubleSpinBox(groupCheck_mutation_enabled);
        spinboxd3_mutation_julia_bipolar_cr_z->setObjectName(QString::fromUtf8("spinboxd3_mutation_julia_bipolar_cr_z"));
        spinboxd3_mutation_julia_bipolar_cr_z->setDecimals(3);
        spinboxd3_mutation_julia_bipolar_cr_z->setMinimum(-10.000000000000000);
        spinboxd3_mutation_julia_bipolar_cr_z->setMaximum(10.000000000000000);
        spinboxd3_mutation_julia_bipolar_cr_z->setSingleStep(0.100000000000000);

        gridLayout_mutation->addWidget(spinboxd3_mutation_julia_bipolar_cr_z, 38, 3, 1, 1);

        widget_mutation_sections = new QWidget(groupCheck_mutation_enabled);
        widget_mutation_sections->setObjectName(QString::fromUtf8("widget_mutation_sections"));
        vboxLayout_mutation_sections = new QVBoxLayout(widget_mutation_sections);
        vboxLayout_mutation_sections->setSpacing(2);
        vboxLayout_mutation_sections->setObjectName(QString::fromUtf8("vboxLayout_mutation_sections"));
        vboxLayout_mutation_sections->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_mutation_sections_top = new QHBoxLayout();
        horizontalLayout_mutation_sections_top->setObjectName(QString::fromUtf8("horizontalLayout_mutation_sections_top"));
        pushButton_mutation_randomize_weights_2 = new QPushButton(widget_mutation_sections);
        pushButton_mutation_randomize_weights_2->setObjectName(QString::fromUtf8("pushButton_mutation_randomize_weights_2"));

        horizontalLayout_mutation_sections_top->addWidget(pushButton_mutation_randomize_weights_2);

        pushButton_mutation_reset_all = new QPushButton(widget_mutation_sections);
        pushButton_mutation_reset_all->setObjectName(QString::fromUtf8("pushButton_mutation_reset_all"));

        horizontalLayout_mutation_sections_top->addWidget(pushButton_mutation_reset_all);

        label = new QLabel(widget_mutation_sections);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_mutation_sections_top->addWidget(label);

        footerMasterWeightSpin = new MyDoubleSpinBox(widget_mutation_sections);
        footerMasterWeightSpin->setObjectName(QString::fromUtf8("footerMasterWeightSpin"));
        footerMasterWeightSpin->setMinimum(0.000000000000000);
        footerMasterWeightSpin->setMaximum(1.000000000000000);
        footerMasterWeightSpin->setSingleStep(0.050000000000000);
        footerMasterWeightSpin->setValue(1.000000000000000);
        footerMasterWeightSpin->setDecimals(2);

        horizontalLayout_mutation_sections_top->addWidget(footerMasterWeightSpin);

        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_mutation_sections_top->addItem(spacerItem);


        vboxLayout_mutation_sections->addLayout(horizontalLayout_mutation_sections_top);

        widget_mutation_clip_inv_panel = new cMutationClipInvPanel(widget_mutation_sections);
        widget_mutation_clip_inv_panel->setObjectName(QString::fromUtf8("widget_mutation_clip_inv_panel"));

        vboxLayout_mutation_sections->addWidget(widget_mutation_clip_inv_panel);

        widget_mutation_jos_pk_panel = new cMutationJosPkPanel(widget_mutation_sections);
        widget_mutation_jos_pk_panel->setObjectName(QString::fromUtf8("widget_mutation_jos_pk_panel"));

        vboxLayout_mutation_sections->addWidget(widget_mutation_jos_pk_panel);

        widget_mutation_systems_panel = new cMutationSystemsPanel(widget_mutation_sections);
        widget_mutation_systems_panel->setObjectName(QString::fromUtf8("widget_mutation_systems_panel"));

        vboxLayout_mutation_sections->addWidget(widget_mutation_systems_panel);


        gridLayout_mutation->addWidget(widget_mutation_sections, 58, 0, 1, 6);


        verticalLayout_mutation_dock->addWidget(groupCheck_mutation_enabled);

        widget_mutation_tail_panel = new cMutationTailPanel(cDockMutationTab);
        widget_mutation_tail_panel->setObjectName(QString::fromUtf8("widget_mutation_tail_panel"));

        verticalLayout_mutation_dock->addWidget(widget_mutation_tail_panel);


        retranslateUi(cDockMutationTab);

        QMetaObject::connectSlotsByName(cDockMutationTab);
    } // setupUi

    void retranslateUi(QWidget *cDockMutationTab)
    {
        cDockMutationTab->setWindowTitle(QCoreApplication::translate("cDockMutationTab", "Mutation", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_mutation_randomize_weights->setToolTip(QCoreApplication::translate("cDockMutationTab", "Randomize every section and per-parameter weight", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_mutation_randomize_weights->setText(QCoreApplication::translate("cDockMutationTab", "Randomize Weights", nullptr));
        pushButton_mutation_randomize_weights->setStyleSheet(QCoreApplication::translate("cDockMutationTab", "font-weight: bold; color: #FF8C00;", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_mutation_reset_weights->setToolTip(QCoreApplication::translate("cDockMutationTab", "Reset all mutation weights back to 1.0", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_mutation_reset_weights->setText(QCoreApplication::translate("cDockMutationTab", "Reset Weights", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_mutation_reset_all_top->setToolTip(QCoreApplication::translate("cDockMutationTab", "Reset ALL mutation parameters to defaults (types, factors, weights, everything)", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_mutation_reset_all_top->setText(QCoreApplication::translate("cDockMutationTab", "Reset All Parameters", nullptr));
        pushButton_mutation_reset_all_top->setStyleSheet(QCoreApplication::translate("cDockMutationTab", "font-weight: bold; color: #FF4444;", nullptr));
        label_mutation_master_weight->setText(QCoreApplication::translate("cDockMutationTab", "Master Weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_mutation_master_weight->setToolTip(QCoreApplication::translate("cDockMutationTab", "Global master weight multiplied into every section weight (1=full, 0=all off)", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_mutation_enabled->setTitle(QCoreApplication::translate("cDockMutationTab", "Formula Mutation", nullptr));
        label_mutation_pre_rotation->setText(QCoreApplication::translate("cDockMutationTab", "Pre-Rotation:", nullptr));
        label_mutation_pre_rot_ax->setText(QCoreApplication::translate("cDockMutationTab", "X:", nullptr));
        label_mutation_pre_rot_ay->setText(QCoreApplication::translate("cDockMutationTab", "Y:", nullptr));
        label_mutation_pre_rot_az->setText(QCoreApplication::translate("cDockMutationTab", "Z:", nullptr));
        label_mutation_pre_scale->setText(QCoreApplication::translate("cDockMutationTab", "Pre-Scale:", nullptr));
        label_mutation_pre_offset->setText(QCoreApplication::translate("cDockMutationTab", "Pre-Offset:", nullptr));
        label_mutation_preoff_ax->setText(QCoreApplication::translate("cDockMutationTab", "X:", nullptr));
        label_mutation_preoff_ay->setText(QCoreApplication::translate("cDockMutationTab", "Y:", nullptr));
        label_mutation_preoff_az->setText(QCoreApplication::translate("cDockMutationTab", "Z:", nullptr));
        label_mutation_pre_abs->setText(QCoreApplication::translate("cDockMutationTab", "Pre-Abs:", nullptr));
        checkBox_mutation_pre_abs_ax->setText(QCoreApplication::translate("cDockMutationTab", "X", nullptr));
        checkBox_mutation_pre_abs_ay->setText(QCoreApplication::translate("cDockMutationTab", "Y", nullptr));
        checkBox_mutation_pre_abs_az->setText(QCoreApplication::translate("cDockMutationTab", "Z", nullptr));
        label_mutation_post_rotation->setText(QCoreApplication::translate("cDockMutationTab", "Post-Rotation:", nullptr));
        label_mutation_post_rot_ax->setText(QCoreApplication::translate("cDockMutationTab", "X:", nullptr));
        label_mutation_post_rot_ay->setText(QCoreApplication::translate("cDockMutationTab", "Y:", nullptr));
        label_mutation_post_rot_az->setText(QCoreApplication::translate("cDockMutationTab", "Z:", nullptr));
        label_mutation_post_scale->setText(QCoreApplication::translate("cDockMutationTab", "Post-Scale:", nullptr));
        label_mutation_post_offset->setText(QCoreApplication::translate("cDockMutationTab", "Post-Offset:", nullptr));
        label_mutation_postoff_ax->setText(QCoreApplication::translate("cDockMutationTab", "X:", nullptr));
        label_mutation_postoff_ay->setText(QCoreApplication::translate("cDockMutationTab", "Y:", nullptr));
        label_mutation_postoff_az->setText(QCoreApplication::translate("cDockMutationTab", "Z:", nullptr));
        label_mutation_swizzle->setText(QCoreApplication::translate("cDockMutationTab", "Swizzle:", nullptr));
        comboBox_mutation_swizzle->setItemText(0, QCoreApplication::translate("cDockMutationTab", "XYZ (default)", nullptr));
        comboBox_mutation_swizzle->setItemText(1, QCoreApplication::translate("cDockMutationTab", "XZY", nullptr));
        comboBox_mutation_swizzle->setItemText(2, QCoreApplication::translate("cDockMutationTab", "YXZ", nullptr));
        comboBox_mutation_swizzle->setItemText(3, QCoreApplication::translate("cDockMutationTab", "YZX", nullptr));
        comboBox_mutation_swizzle->setItemText(4, QCoreApplication::translate("cDockMutationTab", "ZXY", nullptr));
        comboBox_mutation_swizzle->setItemText(5, QCoreApplication::translate("cDockMutationTab", "ZYX", nullptr));

        label_mutation_fold_type->setText(QCoreApplication::translate("cDockMutationTab", "Fold Inject:", nullptr));
        comboBox_mutation_fold_type->setItemText(0, QCoreApplication::translate("cDockMutationTab", "None", nullptr));
        comboBox_mutation_fold_type->setItemText(1, QCoreApplication::translate("cDockMutationTab", "Box Fold", nullptr));
        comboBox_mutation_fold_type->setItemText(2, QCoreApplication::translate("cDockMutationTab", "Sphere Fold", nullptr));
        comboBox_mutation_fold_type->setItemText(3, QCoreApplication::translate("cDockMutationTab", "Menger Fold", nullptr));
        comboBox_mutation_fold_type->setItemText(4, QCoreApplication::translate("cDockMutationTab", "Sierpinski Fold", nullptr));
        comboBox_mutation_fold_type->setItemText(5, QCoreApplication::translate("cDockMutationTab", "Abs Fold (tglad)", nullptr));
        comboBox_mutation_fold_type->setItemText(6, QCoreApplication::translate("cDockMutationTab", "Kaleidoscope", nullptr));
        comboBox_mutation_fold_type->setItemText(7, QCoreApplication::translate("cDockMutationTab", "Octahedral", nullptr));
        comboBox_mutation_fold_type->setItemText(8, QCoreApplication::translate("cDockMutationTab", "Smooth (tanh)", nullptr));
        comboBox_mutation_fold_type->setItemText(9, QCoreApplication::translate("cDockMutationTab", "Polynomial (Chebyshev)", nullptr));
        comboBox_mutation_fold_type->setItemText(10, QCoreApplication::translate("cDockMutationTab", "Circular", nullptr));
        comboBox_mutation_fold_type->setItemText(11, QCoreApplication::translate("cDockMutationTab", "Spiral", nullptr));
        comboBox_mutation_fold_type->setItemText(12, QCoreApplication::translate("cDockMutationTab", "Sinusoidal", nullptr));
        comboBox_mutation_fold_type->setItemText(13, QCoreApplication::translate("cDockMutationTab", "Exponential (Gaussian)", nullptr));
        comboBox_mutation_fold_type->setItemText(14, QCoreApplication::translate("cDockMutationTab", "Logarithmic", nullptr));
        comboBox_mutation_fold_type->setItemText(15, QCoreApplication::translate("cDockMutationTab", "Power", nullptr));
        comboBox_mutation_fold_type->setItemText(16, QCoreApplication::translate("cDockMutationTab", "Smooth Abs (tanh)", nullptr));
        comboBox_mutation_fold_type->setItemText(17, QCoreApplication::translate("cDockMutationTab", "Modulo Wrap (tiling)", nullptr));
        comboBox_mutation_fold_type->setItemText(18, QCoreApplication::translate("cDockMutationTab", "Nested Abs", nullptr));
        comboBox_mutation_fold_type->setItemText(19, QCoreApplication::translate("cDockMutationTab", "Sawtooth", nullptr));
        comboBox_mutation_fold_type->setItemText(20, QCoreApplication::translate("cDockMutationTab", "Bipolar", nullptr));
        comboBox_mutation_fold_type->setItemText(21, QCoreApplication::translate("cDockMutationTab", "Radial Box", nullptr));
        comboBox_mutation_fold_type->setItemText(22, QCoreApplication::translate("cDockMutationTab", "Fold+Shear", nullptr));
        comboBox_mutation_fold_type->setItemText(23, QCoreApplication::translate("cDockMutationTab", "3D Cross", nullptr));
        comboBox_mutation_fold_type->setItemText(24, QCoreApplication::translate("cDockMutationTab", "Conformal", nullptr));
        comboBox_mutation_fold_type->setItemText(25, QCoreApplication::translate("cDockMutationTab", "Fold+Rotation", nullptr));
        comboBox_mutation_fold_type->setItemText(26, QCoreApplication::translate("cDockMutationTab", "Scale Pulse", nullptr));
        comboBox_mutation_fold_type->setItemText(27, QCoreApplication::translate("cDockMutationTab", "Triangle Wave", nullptr));

        label_mutation_fold_limit->setText(QCoreApplication::translate("cDockMutationTab", "Limit:", nullptr));
        label_mutation_fold_value->setText(QCoreApplication::translate("cDockMutationTab", "Value:", nullptr));
        label_mutation_warp_type->setText(QCoreApplication::translate("cDockMutationTab", "Warp:", nullptr));
        comboBox_mutation_warp_type->setItemText(0, QCoreApplication::translate("cDockMutationTab", "None", nullptr));
        comboBox_mutation_warp_type->setItemText(1, QCoreApplication::translate("cDockMutationTab", "Sine", nullptr));
        comboBox_mutation_warp_type->setItemText(2, QCoreApplication::translate("cDockMutationTab", "Twist", nullptr));
        comboBox_mutation_warp_type->setItemText(3, QCoreApplication::translate("cDockMutationTab", "Spiral", nullptr));
        comboBox_mutation_warp_type->setItemText(4, QCoreApplication::translate("cDockMutationTab", "Radial", nullptr));
        comboBox_mutation_warp_type->setItemText(5, QCoreApplication::translate("cDockMutationTab", "Cylindrical", nullptr));
        comboBox_mutation_warp_type->setItemText(6, QCoreApplication::translate("cDockMutationTab", "Spherical Inversion", nullptr));
        comboBox_mutation_warp_type->setItemText(7, QCoreApplication::translate("cDockMutationTab", "M\303\266bius", nullptr));
        comboBox_mutation_warp_type->setItemText(8, QCoreApplication::translate("cDockMutationTab", "IFS Contraction", nullptr));
        comboBox_mutation_warp_type->setItemText(9, QCoreApplication::translate("cDockMutationTab", "IFS Rotation (Golden)", nullptr));
        comboBox_mutation_warp_type->setItemText(10, QCoreApplication::translate("cDockMutationTab", "Polar IFS", nullptr));
        comboBox_mutation_warp_type->setItemText(11, QCoreApplication::translate("cDockMutationTab", "Shear IFS", nullptr));

        label_mutation_warp_freq->setText(QCoreApplication::translate("cDockMutationTab", "Freq:", nullptr));
        label_mutation_warp_amp->setText(QCoreApplication::translate("cDockMutationTab", "Amp:", nullptr));
        label_mutation_fold_position->setText(QCoreApplication::translate("cDockMutationTab", "Fold Position:", nullptr));
        comboBox_mutation_fold_position->setItemText(0, QCoreApplication::translate("cDockMutationTab", "Pre-formula", nullptr));
        comboBox_mutation_fold_position->setItemText(1, QCoreApplication::translate("cDockMutationTab", "Post-formula", nullptr));
        comboBox_mutation_fold_position->setItemText(2, QCoreApplication::translate("cDockMutationTab", "Both", nullptr));

        label_mutation_kaleidoscope_sides->setText(QCoreApplication::translate("cDockMutationTab", "Kal. Sides:", nullptr));
        label_mutation_iter_range->setText(QCoreApplication::translate("cDockMutationTab", "Iter Range:", nullptr));
        label_mutation_iter_start->setText(QCoreApplication::translate("cDockMutationTab", "Start:", nullptr));
        label_mutation_iter_stop->setText(QCoreApplication::translate("cDockMutationTab", "Stop:", nullptr));
        label_mutation_math_type->setText(QCoreApplication::translate("cDockMutationTab", "Math:", nullptr));
        comboBox_mutation_math_type->setItemText(0, QCoreApplication::translate("cDockMutationTab", "None", nullptr));
        comboBox_mutation_math_type->setItemText(1, QCoreApplication::translate("cDockMutationTab", "Sin Power", nullptr));
        comboBox_mutation_math_type->setItemText(2, QCoreApplication::translate("cDockMutationTab", "Cosh Field", nullptr));
        comboBox_mutation_math_type->setItemText(3, QCoreApplication::translate("cDockMutationTab", "Exp Map", nullptr));
        comboBox_mutation_math_type->setItemText(4, QCoreApplication::translate("cDockMutationTab", "Log Spiral", nullptr));
        comboBox_mutation_math_type->setItemText(5, QCoreApplication::translate("cDockMutationTab", "Power N", nullptr));
        comboBox_mutation_math_type->setItemText(6, QCoreApplication::translate("cDockMutationTab", "Complex Mul", nullptr));
        comboBox_mutation_math_type->setItemText(7, QCoreApplication::translate("cDockMutationTab", "Quaternion Mul", nullptr));
        comboBox_mutation_math_type->setItemText(8, QCoreApplication::translate("cDockMutationTab", "Bilinear (M\303\266bius)", nullptr));
        comboBox_mutation_math_type->setItemText(9, QCoreApplication::translate("cDockMutationTab", "Inv Cylindrical", nullptr));
        comboBox_mutation_math_type->setItemText(10, QCoreApplication::translate("cDockMutationTab", "Spiral Power", nullptr));
        comboBox_mutation_math_type->setItemText(11, QCoreApplication::translate("cDockMutationTab", "Hyperbolic Rot", nullptr));
        comboBox_mutation_math_type->setItemText(12, QCoreApplication::translate("cDockMutationTab", "Sphere Inversion 3D", nullptr));
        comboBox_mutation_math_type->setItemText(13, QCoreApplication::translate("cDockMutationTab", "Loxodromic", nullptr));
        comboBox_mutation_math_type->setItemText(14, QCoreApplication::translate("cDockMutationTab", "Parabolic (Horocycle)", nullptr));
        comboBox_mutation_math_type->setItemText(15, QCoreApplication::translate("cDockMutationTab", "Schottky Dual", nullptr));
        comboBox_mutation_math_type->setItemText(16, QCoreApplication::translate("cDockMutationTab", "Fibonacci Word", nullptr));
        comboBox_mutation_math_type->setItemText(17, QCoreApplication::translate("cDockMutationTab", "Maskit Bend", nullptr));
        comboBox_mutation_math_type->setItemText(18, QCoreApplication::translate("cDockMutationTab", "Ellipsoid Inversion", nullptr));
        comboBox_mutation_math_type->setItemText(19, QCoreApplication::translate("cDockMutationTab", "Torus Inversion", nullptr));
        comboBox_mutation_math_type->setItemText(20, QCoreApplication::translate("cDockMutationTab", "Quat Julia-Kleinian", nullptr));
        comboBox_mutation_math_type->setItemText(21, QCoreApplication::translate("cDockMutationTab", "Poincar\303\251 Ball (H\302\263)", nullptr));
        comboBox_mutation_math_type->setItemText(22, QCoreApplication::translate("cDockMutationTab", "Lorentz Boost", nullptr));
        comboBox_mutation_math_type->setItemText(23, QCoreApplication::translate("cDockMutationTab", "Conformal Flow", nullptr));
        comboBox_mutation_math_type->setItemText(24, QCoreApplication::translate("cDockMutationTab", "Fractional Power", nullptr));
        comboBox_mutation_math_type->setItemText(25, QCoreApplication::translate("cDockMutationTab", "Anisotrope Power", nullptr));
        comboBox_mutation_math_type->setItemText(26, QCoreApplication::translate("cDockMutationTab", "Hyperbolic Trig Power", nullptr));
        comboBox_mutation_math_type->setItemText(27, QCoreApplication::translate("cDockMutationTab", "Logarithmic Radius", nullptr));
        comboBox_mutation_math_type->setItemText(28, QCoreApplication::translate("cDockMutationTab", "Polar Swap (\316\270\342\206\224\317\206)", nullptr));
        comboBox_mutation_math_type->setItemText(29, QCoreApplication::translate("cDockMutationTab", "Radial Modulation", nullptr));
        comboBox_mutation_math_type->setItemText(30, QCoreApplication::translate("cDockMutationTab", "Dual Quaternion", nullptr));
        comboBox_mutation_math_type->setItemText(31, QCoreApplication::translate("cDockMutationTab", "Octonion Power", nullptr));
        comboBox_mutation_math_type->setItemText(32, QCoreApplication::translate("cDockMutationTab", "Quaternion M\303\266bius", nullptr));
        comboBox_mutation_math_type->setItemText(33, QCoreApplication::translate("cDockMutationTab", "Split Quaternion", nullptr));
        comboBox_mutation_math_type->setItemText(34, QCoreApplication::translate("cDockMutationTab", "Ford Circles", nullptr));
        comboBox_mutation_math_type->setItemText(35, QCoreApplication::translate("cDockMutationTab", "Apollonian Net", nullptr));
        comboBox_mutation_math_type->setItemText(36, QCoreApplication::translate("cDockMutationTab", "Conformal Wedge", nullptr));
        comboBox_mutation_math_type->setItemText(37, QCoreApplication::translate("cDockMutationTab", "Circle Inv Chain", nullptr));
        comboBox_mutation_math_type->setItemText(38, QCoreApplication::translate("cDockMutationTab", "Hyperbolic Sine", nullptr));
        comboBox_mutation_math_type->setItemText(39, QCoreApplication::translate("cDockMutationTab", "Bessel Approx", nullptr));
        comboBox_mutation_math_type->setItemText(40, QCoreApplication::translate("cDockMutationTab", "Lambert W", nullptr));
        comboBox_mutation_math_type->setItemText(41, QCoreApplication::translate("cDockMutationTab", "Error Function", nullptr));

        label_mutation_math_mix->setText(QCoreApplication::translate("cDockMutationTab", "Math Mix:", nullptr));
        label_mutation_math_p1->setText(QCoreApplication::translate("cDockMutationTab", "P1:", nullptr));
        label_mutation_math_p2->setText(QCoreApplication::translate("cDockMutationTab", "P2:", nullptr));
        label_mutation_math_p3->setText(QCoreApplication::translate("cDockMutationTab", "P3:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_mutation_math_p4->setToolTip(QCoreApplication::translate("cDockMutationTab", "P4 (quaternion w, bilinear d)", nullptr));
#endif // QT_CONFIG(tooltip)
        label_mutation_math_p5->setText(QCoreApplication::translate("cDockMutationTab", "P5:", nullptr));
        label_mutation_math_p6->setText(QCoreApplication::translate("cDockMutationTab", "P6:", nullptr));
        label_mutation_math_p7->setText(QCoreApplication::translate("cDockMutationTab", "P7:", nullptr));
        label_mutation_z_mix->setText(QCoreApplication::translate("cDockMutationTab", "Z-Mix:", nullptr));
        label_mutation_de_scale->setText(QCoreApplication::translate("cDockMutationTab", "DE Scale:", nullptr));
        label_mutation_de_tweak->setText(QCoreApplication::translate("cDockMutationTab", "DE Tweak:", nullptr));
        comboBox_mutation_de_tweak->setItemText(0, QCoreApplication::translate("cDockMutationTab", "None", nullptr));
        comboBox_mutation_de_tweak->setItemText(1, QCoreApplication::translate("cDockMutationTab", "Logarithmic (soft/misty)", nullptr));
        comboBox_mutation_de_tweak->setItemText(2, QCoreApplication::translate("cDockMutationTab", "Exponential (hard)", nullptr));
        comboBox_mutation_de_tweak->setItemText(3, QCoreApplication::translate("cDockMutationTab", "Noise (eroded)", nullptr));
        comboBox_mutation_de_tweak->setItemText(4, QCoreApplication::translate("cDockMutationTab", "Modulation (ripple)", nullptr));
        comboBox_mutation_de_tweak->setItemText(5, QCoreApplication::translate("cDockMutationTab", "Slack (0.9x understep)", nullptr));
        comboBox_mutation_de_tweak->setItemText(6, QCoreApplication::translate("cDockMutationTab", "Aggressive (1.1x overstep)", nullptr));

        label_mutation_de_tweak_p1->setText(QCoreApplication::translate("cDockMutationTab", "Amp:", nullptr));
        label_mutation_de_tweak_p2->setText(QCoreApplication::translate("cDockMutationTab", "Freq:", nullptr));
        label_mutation_orbit_trap->setText(QCoreApplication::translate("cDockMutationTab", "Orbit Trap:", nullptr));
        comboBox_mutation_orbit_trap->setItemText(0, QCoreApplication::translate("cDockMutationTab", "None", nullptr));
        comboBox_mutation_orbit_trap->setItemText(1, QCoreApplication::translate("cDockMutationTab", "Sphere", nullptr));
        comboBox_mutation_orbit_trap->setItemText(2, QCoreApplication::translate("cDockMutationTab", "Cross (axes)", nullptr));
        comboBox_mutation_orbit_trap->setItemText(3, QCoreApplication::translate("cDockMutationTab", "Line (Y-axis)", nullptr));
        comboBox_mutation_orbit_trap->setItemText(4, QCoreApplication::translate("cDockMutationTab", "Torus", nullptr));
        comboBox_mutation_orbit_trap->setItemText(5, QCoreApplication::translate("cDockMutationTab", "Angle", nullptr));

        label_mutation_trap_radius->setText(QCoreApplication::translate("cDockMutationTab", "Radius:", nullptr));
        checkBox_mutation_curvature_coloring->setText(QCoreApplication::translate("cDockMutationTab", "Curvature Coloring", nullptr));
        label_mutation_julia_injection->setText(QCoreApplication::translate("cDockMutationTab", "Julia Injection Point", nullptr));
        comboBox_mutation_julia_injection->setItemText(0, QCoreApplication::translate("cDockMutationTab", "None", nullptr));
        comboBox_mutation_julia_injection->setItemText(1, QCoreApplication::translate("cDockMutationTab", "Pre-Fold", nullptr));
        comboBox_mutation_julia_injection->setItemText(2, QCoreApplication::translate("cDockMutationTab", "Mid-Fold", nullptr));
        comboBox_mutation_julia_injection->setItemText(3, QCoreApplication::translate("cDockMutationTab", "Post-Scale", nullptr));
        comboBox_mutation_julia_injection->setItemText(4, QCoreApplication::translate("cDockMutationTab", "Dual (Pre+Post)", nullptr));
        comboBox_mutation_julia_injection->setItemText(5, QCoreApplication::translate("cDockMutationTab", "Pre-Scale Damped", nullptr));
        comboBox_mutation_julia_injection->setItemText(6, QCoreApplication::translate("cDockMutationTab", "Post-Fold", nullptr));
        comboBox_mutation_julia_injection->setItemText(7, QCoreApplication::translate("cDockMutationTab", "Alternating", nullptr));
        comboBox_mutation_julia_injection->setItemText(8, QCoreApplication::translate("cDockMutationTab", "Radial", nullptr));
        comboBox_mutation_julia_injection->setItemText(9, QCoreApplication::translate("cDockMutationTab", "Conditional", nullptr));
        comboBox_mutation_julia_injection->setItemText(10, QCoreApplication::translate("cDockMutationTab", "Gradient", nullptr));
        comboBox_mutation_julia_injection->setItemText(11, QCoreApplication::translate("cDockMutationTab", "Layered", nullptr));

        label_mutation_julia_start->setText(QCoreApplication::translate("cDockMutationTab", "Julia Start Mode", nullptr));
        comboBox_mutation_julia_start->setItemText(0, QCoreApplication::translate("cDockMutationTab", "Ray (default)", nullptr));
        comboBox_mutation_julia_start->setItemText(1, QCoreApplication::translate("cDockMutationTab", "z\342\202\200 = c (Classic Julia)", nullptr));
        comboBox_mutation_julia_start->setItemText(2, QCoreApplication::translate("cDockMutationTab", "z\342\202\200 = ray + c", nullptr));
        comboBox_mutation_julia_start->setItemText(3, QCoreApplication::translate("cDockMutationTab", "z\342\202\200 = 0, c = ray (Pure Julia)", nullptr));
        comboBox_mutation_julia_start->setItemText(4, QCoreApplication::translate("cDockMutationTab", "z\342\202\200 = 4D (c.x,c.y,c.z,c.w)", nullptr));
        comboBox_mutation_julia_start->setItemText(5, QCoreApplication::translate("cDockMutationTab", "Inversion (z\342\202\200 = c/|c|\302\262)", nullptr));
        comboBox_mutation_julia_start->setItemText(6, QCoreApplication::translate("cDockMutationTab", "Spherical (z\342\202\200 = c/|c|)", nullptr));
        comboBox_mutation_julia_start->setItemText(7, QCoreApplication::translate("cDockMutationTab", "Bipolar", nullptr));
        comboBox_mutation_julia_start->setItemText(8, QCoreApplication::translate("cDockMutationTab", "Lattice", nullptr));
        comboBox_mutation_julia_start->setItemText(9, QCoreApplication::translate("cDockMutationTab", "Perturb (z\342\202\200 = ray + \316\265\302\267rand)", nullptr));

        label_mutation_julia_c_transform->setText(QCoreApplication::translate("cDockMutationTab", "C-Pixel Transform", nullptr));
        comboBox_mutation_julia_c_transform->setItemText(0, QCoreApplication::translate("cDockMutationTab", "None", nullptr));
        comboBox_mutation_julia_c_transform->setItemText(1, QCoreApplication::translate("cDockMutationTab", "Spherical Projection", nullptr));
        comboBox_mutation_julia_c_transform->setItemText(2, QCoreApplication::translate("cDockMutationTab", "M\303\266bius", nullptr));
        comboBox_mutation_julia_c_transform->setItemText(3, QCoreApplication::translate("cDockMutationTab", "Rotation", nullptr));
        comboBox_mutation_julia_c_transform->setItemText(4, QCoreApplication::translate("cDockMutationTab", "Power (c^p)", nullptr));
        comboBox_mutation_julia_c_transform->setItemText(5, QCoreApplication::translate("cDockMutationTab", "Quaternion", nullptr));
        comboBox_mutation_julia_c_transform->setItemText(6, QCoreApplication::translate("cDockMutationTab", "Logarithmic", nullptr));
        comboBox_mutation_julia_c_transform->setItemText(7, QCoreApplication::translate("cDockMutationTab", "Exponential", nullptr));
        comboBox_mutation_julia_c_transform->setItemText(8, QCoreApplication::translate("cDockMutationTab", "Inversion (c/|c|\302\262)", nullptr));
        comboBox_mutation_julia_c_transform->setItemText(9, QCoreApplication::translate("cDockMutationTab", "BoxFold", nullptr));
        comboBox_mutation_julia_c_transform->setItemText(10, QCoreApplication::translate("cDockMutationTab", "Spiral (XY rotation)", nullptr));
        comboBox_mutation_julia_c_transform->setItemText(11, QCoreApplication::translate("cDockMutationTab", "Mandelbrot (c\302\262+c\342\202\200)", nullptr));

        label_mutation_julia_dynamic->setText(QCoreApplication::translate("cDockMutationTab", "Dynamic Julia", nullptr));
        comboBox_mutation_julia_dynamic->setItemText(0, QCoreApplication::translate("cDockMutationTab", "None", nullptr));
        comboBox_mutation_julia_dynamic->setItemText(1, QCoreApplication::translate("cDockMutationTab", "Orbit-Modulated", nullptr));
        comboBox_mutation_julia_dynamic->setItemText(2, QCoreApplication::translate("cDockMutationTab", "Pulse (sin iter)", nullptr));
        comboBox_mutation_julia_dynamic->setItemText(3, QCoreApplication::translate("cDockMutationTab", "Fold-Triggered Boost", nullptr));
        comboBox_mutation_julia_dynamic->setItemText(4, QCoreApplication::translate("cDockMutationTab", "Absorption", nullptr));
        comboBox_mutation_julia_dynamic->setItemText(5, QCoreApplication::translate("cDockMutationTab", "Orbit Memory", nullptr));
        comboBox_mutation_julia_dynamic->setItemText(6, QCoreApplication::translate("cDockMutationTab", "Exp Decay", nullptr));
        comboBox_mutation_julia_dynamic->setItemText(7, QCoreApplication::translate("cDockMutationTab", "Sawtooth", nullptr));
        comboBox_mutation_julia_dynamic->setItemText(8, QCoreApplication::translate("cDockMutationTab", "SmoothStep", nullptr));
        comboBox_mutation_julia_dynamic->setItemText(9, QCoreApplication::translate("cDockMutationTab", "Chaos (Logistic)", nullptr));
        comboBox_mutation_julia_dynamic->setItemText(10, QCoreApplication::translate("cDockMutationTab", "Spiral", nullptr));
        comboBox_mutation_julia_dynamic->setItemText(11, QCoreApplication::translate("cDockMutationTab", "Bounce (|sin|)", nullptr));

        label_mutation_julia_multi->setText(QCoreApplication::translate("cDockMutationTab", "Multi-C Mode", nullptr));
        comboBox_mutation_julia_multi->setItemText(0, QCoreApplication::translate("cDockMutationTab", "None", nullptr));
        comboBox_mutation_julia_multi->setItemText(1, QCoreApplication::translate("cDockMutationTab", "Bipolar (L/R seeds)", nullptr));
        comboBox_mutation_julia_multi->setItemText(2, QCoreApplication::translate("cDockMutationTab", "4D Component Swap", nullptr));
        comboBox_mutation_julia_multi->setItemText(3, QCoreApplication::translate("cDockMutationTab", "Fourier Harmonics", nullptr));
        comboBox_mutation_julia_multi->setItemText(4, QCoreApplication::translate("cDockMutationTab", "Noise", nullptr));
        comboBox_mutation_julia_multi->setItemText(5, QCoreApplication::translate("cDockMutationTab", "Recursive", nullptr));
        comboBox_mutation_julia_multi->setItemText(6, QCoreApplication::translate("cDockMutationTab", "Octave (layered noise)", nullptr));
        comboBox_mutation_julia_multi->setItemText(7, QCoreApplication::translate("cDockMutationTab", "Phase Shift", nullptr));
        comboBox_mutation_julia_multi->setItemText(8, QCoreApplication::translate("cDockMutationTab", "Orbit Split (quadrant)", nullptr));
        comboBox_mutation_julia_multi->setItemText(9, QCoreApplication::translate("cDockMutationTab", "Iter Modulo (3-phase)", nullptr));
        comboBox_mutation_julia_multi->setItemText(10, QCoreApplication::translate("cDockMutationTab", "Distance Band", nullptr));
        comboBox_mutation_julia_multi->setItemText(11, QCoreApplication::translate("cDockMutationTab", "Random", nullptr));

        label_mutation_julia_c_mul->setText(QCoreApplication::translate("cDockMutationTab", "C Multiplier", nullptr));
        label_mutation_julia_pulse_freq->setText(QCoreApplication::translate("cDockMutationTab", "Pulse Frequency", nullptr));
        label_mutation_julia_absorb->setText(QCoreApplication::translate("cDockMutationTab", "Julia Absorb Rate", nullptr));
        label_mutation_julia_c_power->setText(QCoreApplication::translate("cDockMutationTab", "C Power (for c^p)", nullptr));
        label_mutation_julia_c_radius->setText(QCoreApplication::translate("cDockMutationTab", "C Sphere Radius", nullptr));
        label_mutation_section_iter_header->setText(QCoreApplication::translate("cDockMutationTab", "\342\200\224 Per-Section Iteration Ranges \342\200\224", nullptr));
        label_mutation_pre_iter->setText(QCoreApplication::translate("cDockMutationTab", "Pre-Transform:", nullptr));
        label_mutation_pre_iter_s->setText(QCoreApplication::translate("cDockMutationTab", "Start:", nullptr));
        label_mutation_pre_iter_e->setText(QCoreApplication::translate("cDockMutationTab", "Stop:", nullptr));
        label_mutation_fold_iter->setText(QCoreApplication::translate("cDockMutationTab", "Fold:", nullptr));
        label_mutation_fold_iter_s->setText(QCoreApplication::translate("cDockMutationTab", "Start:", nullptr));
        label_mutation_fold_iter_e->setText(QCoreApplication::translate("cDockMutationTab", "Stop:", nullptr));
        label_mutation_warp_iter->setText(QCoreApplication::translate("cDockMutationTab", "Warp:", nullptr));
        label_mutation_warp_iter_s->setText(QCoreApplication::translate("cDockMutationTab", "Start:", nullptr));
        label_mutation_warp_iter_e->setText(QCoreApplication::translate("cDockMutationTab", "Stop:", nullptr));
        label_mutation_math_iter->setText(QCoreApplication::translate("cDockMutationTab", "Math:", nullptr));
        label_mutation_math_iter_s->setText(QCoreApplication::translate("cDockMutationTab", "Start:", nullptr));
        label_mutation_math_iter_e->setText(QCoreApplication::translate("cDockMutationTab", "Stop:", nullptr));
        label_mutation_post_iter->setText(QCoreApplication::translate("cDockMutationTab", "Post-Transform:", nullptr));
        label_mutation_post_iter_s->setText(QCoreApplication::translate("cDockMutationTab", "Start:", nullptr));
        label_mutation_post_iter_e->setText(QCoreApplication::translate("cDockMutationTab", "Stop:", nullptr));
        label_mutation_julia_iter->setText(QCoreApplication::translate("cDockMutationTab", "Julia:", nullptr));
        label_mutation_julia_iter_s->setText(QCoreApplication::translate("cDockMutationTab", "Start:", nullptr));
        label_mutation_julia_iter_e->setText(QCoreApplication::translate("cDockMutationTab", "Stop:", nullptr));
        label_mutation_julia_ext_header->setText(QCoreApplication::translate("cDockMutationTab", "Julia Extended:", nullptr));
        label_mutation_julia_decay_rate_l->setText(QCoreApplication::translate("cDockMutationTab", "Decay Rate:", nullptr));
        label_mutation_julia_spiral_angle_l->setText(QCoreApplication::translate("cDockMutationTab", "Spiral Angle:", nullptr));
        label_mutation_julia_chaos_r_l->setText(QCoreApplication::translate("cDockMutationTab", "Chaos R:", nullptr));
        label_mutation_julia_threshold_l->setText(QCoreApplication::translate("cDockMutationTab", "Threshold:", nullptr));
        label_mutation_julia_gradient_end_l->setText(QCoreApplication::translate("cDockMutationTab", "Gradient End:", nullptr));
        label_mutation_julia_box_fold_limit_l->setText(QCoreApplication::translate("cDockMutationTab", "BoxFold Limit:", nullptr));
        label_mutation_julia_start_epsilon_l->setText(QCoreApplication::translate("cDockMutationTab", "Start Epsilon:", nullptr));
        label_mutation_julia_layer_c2_l->setText(QCoreApplication::translate("cDockMutationTab", "Layer C2:", nullptr));
        label_mutation_julia_layer_c2_yz_l->setText(QCoreApplication::translate("cDockMutationTab", "Layer C2 Y/Z:", nullptr));
        label_mutation_julia_dist_band_l->setText(QCoreApplication::translate("cDockMutationTab", "Dist Band Mid:", nullptr));
        label_mutation_julia_dist_band_far_l->setText(QCoreApplication::translate("cDockMutationTab", "Dist Band Far:", nullptr));
        label_julia_finetune_header->setText(QCoreApplication::translate("cDockMutationTab", "Julia Fine-Tune:", nullptr));
        label_mutation_julia_ctransform_iter_start_l->setText(QCoreApplication::translate("cDockMutationTab", "C-Transf Iter Start:", nullptr));
        label_mutation_julia_ctransform_iter_stop_l->setText(QCoreApplication::translate("cDockMutationTab", "C-Transf Iter Stop:", nullptr));
        label_mutation_julia_dynamic_iter_start_l->setText(QCoreApplication::translate("cDockMutationTab", "Dynamic Iter Start:", nullptr));
        label_mutation_julia_dynamic_iter_stop_l->setText(QCoreApplication::translate("cDockMutationTab", "Dynamic Iter Stop:", nullptr));
        label_mutation_julia_multi_iter_start_l->setText(QCoreApplication::translate("cDockMutationTab", "Multi-C Iter Start:", nullptr));
        label_mutation_julia_multi_iter_stop_l->setText(QCoreApplication::translate("cDockMutationTab", "Multi-C Iter Stop:", nullptr));
        label_mutation_julia_ctransform_strength_l->setText(QCoreApplication::translate("cDockMutationTab", "C-Transform Strength:", nullptr));
        label_mutation_julia_dynamic_strength_l->setText(QCoreApplication::translate("cDockMutationTab", "Dynamic Strength:", nullptr));
        label_mutation_julia_multi_strength_l->setText(QCoreApplication::translate("cDockMutationTab", "Multi-C Strength:", nullptr));
        label_mutation_julia_injection_strength_l->setText(QCoreApplication::translate("cDockMutationTab", "Injection Strength:", nullptr));
        label_mutation_julia_de_factor_l->setText(QCoreApplication::translate("cDockMutationTab", "DE Factor:", nullptr));
        label_mutation_de_iter->setText(QCoreApplication::translate("cDockMutationTab", "DE/Output:", nullptr));
        label_mutation_de_iter_s->setText(QCoreApplication::translate("cDockMutationTab", "Start:", nullptr));
        label_mutation_de_iter_e->setText(QCoreApplication::translate("cDockMutationTab", "Stop:", nullptr));
        label_c_rotation->setText(QCoreApplication::translate("cDockMutationTab", "C-Rotation", nullptr));
        label_m_bius_a->setText(QCoreApplication::translate("cDockMutationTab", "M\303\266bius A", nullptr));
        label_m_bius_b->setText(QCoreApplication::translate("cDockMutationTab", "M\303\266bius B", nullptr));
        label_m_bius_d->setText(QCoreApplication::translate("cDockMutationTab", "M\303\266bius D", nullptr));
        label_pulse_amp->setText(QCoreApplication::translate("cDockMutationTab", "Pulse Amp", nullptr));
        label_noise_freq->setText(QCoreApplication::translate("cDockMutationTab", "Noise Freq", nullptr));
        label_noise_amp->setText(QCoreApplication::translate("cDockMutationTab", "Noise Amp", nullptr));
        label_fourier_c2->setText(QCoreApplication::translate("cDockMutationTab", "Fourier C2", nullptr));
        label_fourier_c3->setText(QCoreApplication::translate("cDockMutationTab", "Fourier C3", nullptr));
        label_bipolar_cr->setText(QCoreApplication::translate("cDockMutationTab", "Bipolar CR", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_mutation_randomize_weights_2->setToolTip(QCoreApplication::translate("cDockMutationTab", "Randomize all weights", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_mutation_randomize_weights_2->setText(QCoreApplication::translate("cDockMutationTab", "Randomize", nullptr));
        pushButton_mutation_randomize_weights_2->setStyleSheet(QCoreApplication::translate("cDockMutationTab", "font-weight: bold; color: #FF8C00;", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_mutation_reset_all->setToolTip(QCoreApplication::translate("cDockMutationTab", "Reset all mutation parameters to defaults", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_mutation_reset_all->setText(QCoreApplication::translate("cDockMutationTab", "Reset All", nullptr));
        label->setText(QCoreApplication::translate("cDockMutationTab", "Master:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cDockMutationTab: public Ui_cDockMutationTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCK_MUTATION_TAB_H
