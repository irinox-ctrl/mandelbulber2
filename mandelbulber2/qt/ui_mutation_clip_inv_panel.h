/********************************************************************************
** Form generated from reading UI file 'mutation_clip_inv_panel.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUTATION_CLIP_INV_PANEL_H
#define UI_MUTATION_CLIP_INV_PANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "my_check_box.h"
#include "my_double_spin_box.h"
#include "my_group_box.h"
#include "my_spin_box.h"

QT_BEGIN_NAMESPACE

class Ui_cMutationClipInvPanel
{
public:
    QVBoxLayout *verticalLayout_mutation_clip_inv;
    MyGroupBox *groupCheck_mutation_inversion_enabled;
    QGridLayout *gridLayout_mutation_inversion;
    QLabel *label_mutation_inv_type;
    QLabel *label;
    MyDoubleSpinBox *spinbox_mutation_inversion_section_weight;
    QPushButton *pushButton_mutation_inversion_reset_weights;
    QComboBox *comboBox_mutation_inv_type;
    QLabel *label_inv_center;
    MyDoubleSpinBox *spinbox_mutation_inv_center_ax;
    QLabel *label_inv_center_y;
    MyDoubleSpinBox *spinbox_mutation_inv_center_ay;
    QLabel *label_inv_center_z;
    MyDoubleSpinBox *spinbox_mutation_inv_center_az;
    QLabel *label_inv_radius;
    MyDoubleSpinBox *spinbox_mutation_inv_radius;
    QLabel *label_inv_param_a;
    MyDoubleSpinBox *spinbox_mutation_inv_param_a;
    QLabel *label_inv_param_b;
    MyDoubleSpinBox *spinbox_mutation_inv_param_b;
    QLabel *label_inv_param_c;
    MyDoubleSpinBox *spinbox_mutation_inv_param_c;
    QLabel *label_inv_scale;
    MyDoubleSpinBox *spinbox_mutation_inv_scale;
    QLabel *label_inv_angle;
    MyDoubleSpinBox *spinbox_mutation_inv_angle;
    QLabel *label_inv_freq;
    MyDoubleSpinBox *spinbox_mutation_inv_frequency;
    QLabel *label_inv_amp;
    MyDoubleSpinBox *spinbox_mutation_inv_amplitude;
    QLabel *label_inv_minr;
    MyDoubleSpinBox *spinbox_mutation_inv_min_r;
    QLabel *label_inv_maxr;
    MyDoubleSpinBox *spinbox_mutation_inv_max_r;
    QLabel *label_inv_prerot_x;
    MyDoubleSpinBox *spinbox_mutation_inv_pre_rot_ax;
    QLabel *label_inv_prerot_y;
    MyDoubleSpinBox *spinbox_mutation_inv_pre_rot_ay;
    QLabel *label_inv_prerot_z;
    MyDoubleSpinBox *spinbox_mutation_inv_pre_rot_az;
    QLabel *label_inv_center2;
    MyDoubleSpinBox *spinbox_mutation_inv_center2_ax;
    QLabel *label_inv_center2_y;
    MyDoubleSpinBox *spinbox_mutation_inv_center2_ay;
    QLabel *label_inv_center2_z;
    MyDoubleSpinBox *spinbox_mutation_inv_center2_az;
    QLabel *label_inv_radius2;
    MyDoubleSpinBox *spinbox_mutation_inv_radius2;
    QLabel *label_inv_weight;
    MyDoubleSpinBox *spinbox_mutation_inv_weight;
    QLabel *label_inv_nsteps;
    MySpinBox *spinboxInt_mutation_inv_n_steps;
    QLabel *label_inv_threshold;
    MyDoubleSpinBox *spinbox_mutation_inv_threshold;
    QLabel *label_inv_colorfactor;
    MyDoubleSpinBox *spinbox_mutation_inv_color_factor;
    QLabel *label_inv_iter;
    MySpinBox *spinboxInt_mutation_inv_iter_start;
    QLabel *label_inv_iter_stop;
    MySpinBox *spinboxInt_mutation_inv_iter_stop;
    MyGroupBox *groupCheck_mutation_clip_enabled;
    QGridLayout *gridLayout_mutation_clip;
    QLabel *label_mutation_clip_type;
    QLabel *label1;
    MyDoubleSpinBox *spinbox_mutation_clip_section_weight;
    QPushButton *pushButton_mutation_clip_reset_weights;
    QComboBox *comboBox_mutation_clip_type;
    QLabel *label_clip_center;
    MyDoubleSpinBox *spinbox_mutation_clip_center_ax;
    QLabel *label_clip_center_y;
    MyDoubleSpinBox *spinbox_mutation_clip_center_ay;
    QLabel *label_clip_center_z;
    MyDoubleSpinBox *spinbox_mutation_clip_center_az;
    QLabel *label_clip_size;
    MyDoubleSpinBox *spinbox_mutation_clip_size_ax;
    QLabel *label_clip_size_y;
    MyDoubleSpinBox *spinbox_mutation_clip_size_ay;
    QLabel *label_clip_size_z;
    MyDoubleSpinBox *spinbox_mutation_clip_size_az;
    QLabel *label_clip_radius;
    MyDoubleSpinBox *spinbox_mutation_clip_radius;
    QLabel *label_clip_major_r;
    MyDoubleSpinBox *spinbox_mutation_clip_major_radius;
    QLabel *label_clip_angle;
    MyDoubleSpinBox *spinbox_mutation_clip_angle;
    QLabel *label_clip_freq;
    MyDoubleSpinBox *spinbox_mutation_clip_frequency;
    QLabel *label_clip_amp;
    MyDoubleSpinBox *spinbox_mutation_clip_amplitude;
    QLabel *label_clip_smooth;
    MyDoubleSpinBox *spinbox_mutation_clip_smooth_k;
    QLabel *label_clip_bool;
    MySpinBox *spinboxInt_mutation_clip_boolean_op;
    QLabel *label_clip_npoints;
    MySpinBox *spinboxInt_mutation_clip_n_points;
    QLabel *label_clip_param;
    MyDoubleSpinBox *spinbox_mutation_clip_param_a;
    QLabel *label_clip_param_b;
    MyDoubleSpinBox *spinbox_mutation_clip_param_b;
    QLabel *label_clip_param_c;
    MyDoubleSpinBox *spinbox_mutation_clip_param_c;
    QLabel *label_clip_threshold;
    MyDoubleSpinBox *spinbox_mutation_clip_threshold;
    QLabel *label_clip_prerot_x;
    MyDoubleSpinBox *spinbox_mutation_clip_pre_rot_ax;
    QLabel *label_clip_prerot_y;
    MyDoubleSpinBox *spinbox_mutation_clip_pre_rot_ay;
    QLabel *label_clip_prerot_z;
    MyDoubleSpinBox *spinbox_mutation_clip_pre_rot_az;
    QLabel *label_clip_iter_start;
    MySpinBox *spinboxInt_mutation_clip_iter_start;
    QLabel *label_clip_iter_stop;
    MySpinBox *spinboxInt_mutation_clip_iter_stop;

    void setupUi(QWidget *cMutationClipInvPanel)
    {
        if (cMutationClipInvPanel->objectName().isEmpty())
            cMutationClipInvPanel->setObjectName(QString::fromUtf8("cMutationClipInvPanel"));
        verticalLayout_mutation_clip_inv = new QVBoxLayout(cMutationClipInvPanel);
        verticalLayout_mutation_clip_inv->setSpacing(2);
        verticalLayout_mutation_clip_inv->setObjectName(QString::fromUtf8("verticalLayout_mutation_clip_inv"));
        verticalLayout_mutation_clip_inv->setContentsMargins(0, 0, 0, 0);
        groupCheck_mutation_inversion_enabled = new MyGroupBox(cMutationClipInvPanel);
        groupCheck_mutation_inversion_enabled->setObjectName(QString::fromUtf8("groupCheck_mutation_inversion_enabled"));
        groupCheck_mutation_inversion_enabled->setCheckable(true);
        groupCheck_mutation_inversion_enabled->setChecked(false);
        gridLayout_mutation_inversion = new QGridLayout(groupCheck_mutation_inversion_enabled);
        gridLayout_mutation_inversion->setObjectName(QString::fromUtf8("gridLayout_mutation_inversion"));
        label_mutation_inv_type = new QLabel(groupCheck_mutation_inversion_enabled);
        label_mutation_inv_type->setObjectName(QString::fromUtf8("label_mutation_inv_type"));

        gridLayout_mutation_inversion->addWidget(label_mutation_inv_type, 0, 0, 1, 2);

        label = new QLabel(groupCheck_mutation_inversion_enabled);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout_mutation_inversion->addWidget(label, 0, 6, 1, 1);

        spinbox_mutation_inversion_section_weight = new MyDoubleSpinBox(groupCheck_mutation_inversion_enabled);
        spinbox_mutation_inversion_section_weight->setObjectName(QString::fromUtf8("spinbox_mutation_inversion_section_weight"));
        spinbox_mutation_inversion_section_weight->setMinimum(0.000000000000000);
        spinbox_mutation_inversion_section_weight->setMaximum(1.000000000000000);
        spinbox_mutation_inversion_section_weight->setSingleStep(0.050000000000000);
        spinbox_mutation_inversion_section_weight->setValue(1.000000000000000);
        spinbox_mutation_inversion_section_weight->setDecimals(2);
        spinbox_mutation_inversion_section_weight->setMinimumSize(QSize(60, 0));

        gridLayout_mutation_inversion->addWidget(spinbox_mutation_inversion_section_weight, 1, 6, 1, 1);

        pushButton_mutation_inversion_reset_weights = new QPushButton(groupCheck_mutation_inversion_enabled);
        pushButton_mutation_inversion_reset_weights->setObjectName(QString::fromUtf8("pushButton_mutation_inversion_reset_weights"));
        pushButton_mutation_inversion_reset_weights->setMaximumSize(QSize(60, 16777215));

        gridLayout_mutation_inversion->addWidget(pushButton_mutation_inversion_reset_weights, 2, 6, 1, 1);

        comboBox_mutation_inv_type = new QComboBox(groupCheck_mutation_inversion_enabled);
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->addItem(QString());
        comboBox_mutation_inv_type->setObjectName(QString::fromUtf8("comboBox_mutation_inv_type"));

        gridLayout_mutation_inversion->addWidget(comboBox_mutation_inv_type, 0, 2, 1, 4);

        label_inv_center = new QLabel(groupCheck_mutation_inversion_enabled);
        label_inv_center->setObjectName(QString::fromUtf8("label_inv_center"));

        gridLayout_mutation_inversion->addWidget(label_inv_center, 1, 0, 1, 1);

        spinbox_mutation_inv_center_ax = new MyDoubleSpinBox(groupCheck_mutation_inversion_enabled);
        spinbox_mutation_inv_center_ax->setObjectName(QString::fromUtf8("spinbox_mutation_inv_center_ax"));
        spinbox_mutation_inv_center_ax->setMinimum(-100.000000000000000);
        spinbox_mutation_inv_center_ax->setMaximum(100.000000000000000);
        spinbox_mutation_inv_center_ax->setSingleStep(0.100000000000000);

        gridLayout_mutation_inversion->addWidget(spinbox_mutation_inv_center_ax, 1, 1, 1, 1);

        label_inv_center_y = new QLabel(groupCheck_mutation_inversion_enabled);
        label_inv_center_y->setObjectName(QString::fromUtf8("label_inv_center_y"));

        gridLayout_mutation_inversion->addWidget(label_inv_center_y, 1, 2, 1, 1);

        spinbox_mutation_inv_center_ay = new MyDoubleSpinBox(groupCheck_mutation_inversion_enabled);
        spinbox_mutation_inv_center_ay->setObjectName(QString::fromUtf8("spinbox_mutation_inv_center_ay"));
        spinbox_mutation_inv_center_ay->setMinimum(-100.000000000000000);
        spinbox_mutation_inv_center_ay->setMaximum(100.000000000000000);
        spinbox_mutation_inv_center_ay->setSingleStep(0.100000000000000);

        gridLayout_mutation_inversion->addWidget(spinbox_mutation_inv_center_ay, 1, 3, 1, 1);

        label_inv_center_z = new QLabel(groupCheck_mutation_inversion_enabled);
        label_inv_center_z->setObjectName(QString::fromUtf8("label_inv_center_z"));

        gridLayout_mutation_inversion->addWidget(label_inv_center_z, 1, 4, 1, 1);

        spinbox_mutation_inv_center_az = new MyDoubleSpinBox(groupCheck_mutation_inversion_enabled);
        spinbox_mutation_inv_center_az->setObjectName(QString::fromUtf8("spinbox_mutation_inv_center_az"));
        spinbox_mutation_inv_center_az->setMinimum(-100.000000000000000);
        spinbox_mutation_inv_center_az->setMaximum(100.000000000000000);
        spinbox_mutation_inv_center_az->setSingleStep(0.100000000000000);

        gridLayout_mutation_inversion->addWidget(spinbox_mutation_inv_center_az, 1, 5, 1, 1);

        label_inv_radius = new QLabel(groupCheck_mutation_inversion_enabled);
        label_inv_radius->setObjectName(QString::fromUtf8("label_inv_radius"));

        gridLayout_mutation_inversion->addWidget(label_inv_radius, 2, 0, 1, 1);

        spinbox_mutation_inv_radius = new MyDoubleSpinBox(groupCheck_mutation_inversion_enabled);
        spinbox_mutation_inv_radius->setObjectName(QString::fromUtf8("spinbox_mutation_inv_radius"));
        spinbox_mutation_inv_radius->setMinimum(0.001000000000000);
        spinbox_mutation_inv_radius->setMaximum(100.000000000000000);
        spinbox_mutation_inv_radius->setValue(1.000000000000000);
        spinbox_mutation_inv_radius->setSingleStep(0.100000000000000);

        gridLayout_mutation_inversion->addWidget(spinbox_mutation_inv_radius, 2, 1, 1, 1);

        label_inv_param_a = new QLabel(groupCheck_mutation_inversion_enabled);
        label_inv_param_a->setObjectName(QString::fromUtf8("label_inv_param_a"));

        gridLayout_mutation_inversion->addWidget(label_inv_param_a, 2, 2, 1, 1);

        spinbox_mutation_inv_param_a = new MyDoubleSpinBox(groupCheck_mutation_inversion_enabled);
        spinbox_mutation_inv_param_a->setObjectName(QString::fromUtf8("spinbox_mutation_inv_param_a"));
        spinbox_mutation_inv_param_a->setMinimum(0.001000000000000);
        spinbox_mutation_inv_param_a->setMaximum(100.000000000000000);
        spinbox_mutation_inv_param_a->setValue(1.000000000000000);
        spinbox_mutation_inv_param_a->setSingleStep(0.100000000000000);

        gridLayout_mutation_inversion->addWidget(spinbox_mutation_inv_param_a, 2, 3, 1, 1);

        label_inv_param_b = new QLabel(groupCheck_mutation_inversion_enabled);
        label_inv_param_b->setObjectName(QString::fromUtf8("label_inv_param_b"));

        gridLayout_mutation_inversion->addWidget(label_inv_param_b, 2, 4, 1, 1);

        spinbox_mutation_inv_param_b = new MyDoubleSpinBox(groupCheck_mutation_inversion_enabled);
        spinbox_mutation_inv_param_b->setObjectName(QString::fromUtf8("spinbox_mutation_inv_param_b"));
        spinbox_mutation_inv_param_b->setMinimum(0.001000000000000);
        spinbox_mutation_inv_param_b->setMaximum(100.000000000000000);
        spinbox_mutation_inv_param_b->setValue(1.000000000000000);
        spinbox_mutation_inv_param_b->setSingleStep(0.100000000000000);

        gridLayout_mutation_inversion->addWidget(spinbox_mutation_inv_param_b, 2, 5, 1, 1);

        label_inv_param_c = new QLabel(groupCheck_mutation_inversion_enabled);
        label_inv_param_c->setObjectName(QString::fromUtf8("label_inv_param_c"));

        gridLayout_mutation_inversion->addWidget(label_inv_param_c, 3, 0, 1, 1);

        spinbox_mutation_inv_param_c = new MyDoubleSpinBox(groupCheck_mutation_inversion_enabled);
        spinbox_mutation_inv_param_c->setObjectName(QString::fromUtf8("spinbox_mutation_inv_param_c"));
        spinbox_mutation_inv_param_c->setMinimum(0.001000000000000);
        spinbox_mutation_inv_param_c->setMaximum(100.000000000000000);
        spinbox_mutation_inv_param_c->setValue(1.000000000000000);
        spinbox_mutation_inv_param_c->setSingleStep(0.100000000000000);

        gridLayout_mutation_inversion->addWidget(spinbox_mutation_inv_param_c, 3, 1, 1, 1);

        label_inv_scale = new QLabel(groupCheck_mutation_inversion_enabled);
        label_inv_scale->setObjectName(QString::fromUtf8("label_inv_scale"));

        gridLayout_mutation_inversion->addWidget(label_inv_scale, 3, 2, 1, 1);

        spinbox_mutation_inv_scale = new MyDoubleSpinBox(groupCheck_mutation_inversion_enabled);
        spinbox_mutation_inv_scale->setObjectName(QString::fromUtf8("spinbox_mutation_inv_scale"));
        spinbox_mutation_inv_scale->setMinimum(0.001000000000000);
        spinbox_mutation_inv_scale->setMaximum(100.000000000000000);
        spinbox_mutation_inv_scale->setValue(1.000000000000000);
        spinbox_mutation_inv_scale->setSingleStep(0.100000000000000);

        gridLayout_mutation_inversion->addWidget(spinbox_mutation_inv_scale, 3, 3, 1, 1);

        label_inv_angle = new QLabel(groupCheck_mutation_inversion_enabled);
        label_inv_angle->setObjectName(QString::fromUtf8("label_inv_angle"));

        gridLayout_mutation_inversion->addWidget(label_inv_angle, 3, 4, 1, 1);

        spinbox_mutation_inv_angle = new MyDoubleSpinBox(groupCheck_mutation_inversion_enabled);
        spinbox_mutation_inv_angle->setObjectName(QString::fromUtf8("spinbox_mutation_inv_angle"));
        spinbox_mutation_inv_angle->setMinimum(-360.000000000000000);
        spinbox_mutation_inv_angle->setMaximum(360.000000000000000);
        spinbox_mutation_inv_angle->setSingleStep(1.000000000000000);

        gridLayout_mutation_inversion->addWidget(spinbox_mutation_inv_angle, 3, 5, 1, 1);

        label_inv_freq = new QLabel(groupCheck_mutation_inversion_enabled);
        label_inv_freq->setObjectName(QString::fromUtf8("label_inv_freq"));

        gridLayout_mutation_inversion->addWidget(label_inv_freq, 4, 0, 1, 1);

        spinbox_mutation_inv_frequency = new MyDoubleSpinBox(groupCheck_mutation_inversion_enabled);
        spinbox_mutation_inv_frequency->setObjectName(QString::fromUtf8("spinbox_mutation_inv_frequency"));
        spinbox_mutation_inv_frequency->setMinimum(0.000000000000000);
        spinbox_mutation_inv_frequency->setMaximum(100.000000000000000);
        spinbox_mutation_inv_frequency->setValue(1.000000000000000);
        spinbox_mutation_inv_frequency->setSingleStep(0.100000000000000);

        gridLayout_mutation_inversion->addWidget(spinbox_mutation_inv_frequency, 4, 1, 1, 1);

        label_inv_amp = new QLabel(groupCheck_mutation_inversion_enabled);
        label_inv_amp->setObjectName(QString::fromUtf8("label_inv_amp"));

        gridLayout_mutation_inversion->addWidget(label_inv_amp, 4, 2, 1, 1);

        spinbox_mutation_inv_amplitude = new MyDoubleSpinBox(groupCheck_mutation_inversion_enabled);
        spinbox_mutation_inv_amplitude->setObjectName(QString::fromUtf8("spinbox_mutation_inv_amplitude"));
        spinbox_mutation_inv_amplitude->setMinimum(0.000000000000000);
        spinbox_mutation_inv_amplitude->setMaximum(100.000000000000000);
        spinbox_mutation_inv_amplitude->setValue(0.100000000000000);
        spinbox_mutation_inv_amplitude->setSingleStep(0.010000000000000);

        gridLayout_mutation_inversion->addWidget(spinbox_mutation_inv_amplitude, 4, 3, 1, 1);

        label_inv_minr = new QLabel(groupCheck_mutation_inversion_enabled);
        label_inv_minr->setObjectName(QString::fromUtf8("label_inv_minr"));

        gridLayout_mutation_inversion->addWidget(label_inv_minr, 4, 4, 1, 1);

        spinbox_mutation_inv_min_r = new MyDoubleSpinBox(groupCheck_mutation_inversion_enabled);
        spinbox_mutation_inv_min_r->setObjectName(QString::fromUtf8("spinbox_mutation_inv_min_r"));
        spinbox_mutation_inv_min_r->setMinimum(0.000000000000000);
        spinbox_mutation_inv_min_r->setMaximum(100.000000000000000);
        spinbox_mutation_inv_min_r->setValue(0.500000000000000);
        spinbox_mutation_inv_min_r->setSingleStep(0.100000000000000);

        gridLayout_mutation_inversion->addWidget(spinbox_mutation_inv_min_r, 4, 5, 1, 1);

        label_inv_maxr = new QLabel(groupCheck_mutation_inversion_enabled);
        label_inv_maxr->setObjectName(QString::fromUtf8("label_inv_maxr"));

        gridLayout_mutation_inversion->addWidget(label_inv_maxr, 5, 0, 1, 1);

        spinbox_mutation_inv_max_r = new MyDoubleSpinBox(groupCheck_mutation_inversion_enabled);
        spinbox_mutation_inv_max_r->setObjectName(QString::fromUtf8("spinbox_mutation_inv_max_r"));
        spinbox_mutation_inv_max_r->setMinimum(0.000000000000000);
        spinbox_mutation_inv_max_r->setMaximum(100.000000000000000);
        spinbox_mutation_inv_max_r->setValue(1.000000000000000);
        spinbox_mutation_inv_max_r->setSingleStep(0.100000000000000);

        gridLayout_mutation_inversion->addWidget(spinbox_mutation_inv_max_r, 5, 1, 1, 1);

        label_inv_prerot_x = new QLabel(groupCheck_mutation_inversion_enabled);
        label_inv_prerot_x->setObjectName(QString::fromUtf8("label_inv_prerot_x"));

        gridLayout_mutation_inversion->addWidget(label_inv_prerot_x, 5, 2, 1, 1);

        spinbox_mutation_inv_pre_rot_ax = new MyDoubleSpinBox(groupCheck_mutation_inversion_enabled);
        spinbox_mutation_inv_pre_rot_ax->setObjectName(QString::fromUtf8("spinbox_mutation_inv_pre_rot_ax"));
        spinbox_mutation_inv_pre_rot_ax->setMinimum(-360.000000000000000);
        spinbox_mutation_inv_pre_rot_ax->setMaximum(360.000000000000000);
        spinbox_mutation_inv_pre_rot_ax->setSingleStep(1.000000000000000);

        gridLayout_mutation_inversion->addWidget(spinbox_mutation_inv_pre_rot_ax, 5, 3, 1, 1);

        label_inv_prerot_y = new QLabel(groupCheck_mutation_inversion_enabled);
        label_inv_prerot_y->setObjectName(QString::fromUtf8("label_inv_prerot_y"));

        gridLayout_mutation_inversion->addWidget(label_inv_prerot_y, 5, 4, 1, 1);

        spinbox_mutation_inv_pre_rot_ay = new MyDoubleSpinBox(groupCheck_mutation_inversion_enabled);
        spinbox_mutation_inv_pre_rot_ay->setObjectName(QString::fromUtf8("spinbox_mutation_inv_pre_rot_ay"));
        spinbox_mutation_inv_pre_rot_ay->setMinimum(-360.000000000000000);
        spinbox_mutation_inv_pre_rot_ay->setMaximum(360.000000000000000);
        spinbox_mutation_inv_pre_rot_ay->setSingleStep(1.000000000000000);

        gridLayout_mutation_inversion->addWidget(spinbox_mutation_inv_pre_rot_ay, 5, 5, 1, 1);

        label_inv_prerot_z = new QLabel(groupCheck_mutation_inversion_enabled);
        label_inv_prerot_z->setObjectName(QString::fromUtf8("label_inv_prerot_z"));

        gridLayout_mutation_inversion->addWidget(label_inv_prerot_z, 6, 0, 1, 1);

        spinbox_mutation_inv_pre_rot_az = new MyDoubleSpinBox(groupCheck_mutation_inversion_enabled);
        spinbox_mutation_inv_pre_rot_az->setObjectName(QString::fromUtf8("spinbox_mutation_inv_pre_rot_az"));
        spinbox_mutation_inv_pre_rot_az->setMinimum(-360.000000000000000);
        spinbox_mutation_inv_pre_rot_az->setMaximum(360.000000000000000);
        spinbox_mutation_inv_pre_rot_az->setSingleStep(1.000000000000000);

        gridLayout_mutation_inversion->addWidget(spinbox_mutation_inv_pre_rot_az, 6, 1, 1, 1);

        label_inv_center2 = new QLabel(groupCheck_mutation_inversion_enabled);
        label_inv_center2->setObjectName(QString::fromUtf8("label_inv_center2"));

        gridLayout_mutation_inversion->addWidget(label_inv_center2, 6, 2, 1, 1);

        spinbox_mutation_inv_center2_ax = new MyDoubleSpinBox(groupCheck_mutation_inversion_enabled);
        spinbox_mutation_inv_center2_ax->setObjectName(QString::fromUtf8("spinbox_mutation_inv_center2_ax"));
        spinbox_mutation_inv_center2_ax->setMinimum(-100.000000000000000);
        spinbox_mutation_inv_center2_ax->setMaximum(100.000000000000000);
        spinbox_mutation_inv_center2_ax->setSingleStep(0.100000000000000);

        gridLayout_mutation_inversion->addWidget(spinbox_mutation_inv_center2_ax, 6, 3, 1, 1);

        label_inv_center2_y = new QLabel(groupCheck_mutation_inversion_enabled);
        label_inv_center2_y->setObjectName(QString::fromUtf8("label_inv_center2_y"));

        gridLayout_mutation_inversion->addWidget(label_inv_center2_y, 6, 4, 1, 1);

        spinbox_mutation_inv_center2_ay = new MyDoubleSpinBox(groupCheck_mutation_inversion_enabled);
        spinbox_mutation_inv_center2_ay->setObjectName(QString::fromUtf8("spinbox_mutation_inv_center2_ay"));
        spinbox_mutation_inv_center2_ay->setMinimum(-100.000000000000000);
        spinbox_mutation_inv_center2_ay->setMaximum(100.000000000000000);
        spinbox_mutation_inv_center2_ay->setSingleStep(0.100000000000000);

        gridLayout_mutation_inversion->addWidget(spinbox_mutation_inv_center2_ay, 6, 5, 1, 1);

        label_inv_center2_z = new QLabel(groupCheck_mutation_inversion_enabled);
        label_inv_center2_z->setObjectName(QString::fromUtf8("label_inv_center2_z"));

        gridLayout_mutation_inversion->addWidget(label_inv_center2_z, 7, 0, 1, 1);

        spinbox_mutation_inv_center2_az = new MyDoubleSpinBox(groupCheck_mutation_inversion_enabled);
        spinbox_mutation_inv_center2_az->setObjectName(QString::fromUtf8("spinbox_mutation_inv_center2_az"));
        spinbox_mutation_inv_center2_az->setMinimum(-100.000000000000000);
        spinbox_mutation_inv_center2_az->setMaximum(100.000000000000000);
        spinbox_mutation_inv_center2_az->setSingleStep(0.100000000000000);

        gridLayout_mutation_inversion->addWidget(spinbox_mutation_inv_center2_az, 7, 1, 1, 1);

        label_inv_radius2 = new QLabel(groupCheck_mutation_inversion_enabled);
        label_inv_radius2->setObjectName(QString::fromUtf8("label_inv_radius2"));

        gridLayout_mutation_inversion->addWidget(label_inv_radius2, 7, 2, 1, 1);

        spinbox_mutation_inv_radius2 = new MyDoubleSpinBox(groupCheck_mutation_inversion_enabled);
        spinbox_mutation_inv_radius2->setObjectName(QString::fromUtf8("spinbox_mutation_inv_radius2"));
        spinbox_mutation_inv_radius2->setMinimum(0.001000000000000);
        spinbox_mutation_inv_radius2->setMaximum(100.000000000000000);
        spinbox_mutation_inv_radius2->setValue(1.000000000000000);
        spinbox_mutation_inv_radius2->setSingleStep(0.100000000000000);

        gridLayout_mutation_inversion->addWidget(spinbox_mutation_inv_radius2, 7, 3, 1, 1);

        label_inv_weight = new QLabel(groupCheck_mutation_inversion_enabled);
        label_inv_weight->setObjectName(QString::fromUtf8("label_inv_weight"));

        gridLayout_mutation_inversion->addWidget(label_inv_weight, 7, 4, 1, 1);

        spinbox_mutation_inv_weight = new MyDoubleSpinBox(groupCheck_mutation_inversion_enabled);
        spinbox_mutation_inv_weight->setObjectName(QString::fromUtf8("spinbox_mutation_inv_weight"));
        spinbox_mutation_inv_weight->setMinimum(0.000000000000000);
        spinbox_mutation_inv_weight->setMaximum(1.000000000000000);
        spinbox_mutation_inv_weight->setValue(0.500000000000000);
        spinbox_mutation_inv_weight->setSingleStep(0.100000000000000);

        gridLayout_mutation_inversion->addWidget(spinbox_mutation_inv_weight, 7, 5, 1, 1);

        label_inv_nsteps = new QLabel(groupCheck_mutation_inversion_enabled);
        label_inv_nsteps->setObjectName(QString::fromUtf8("label_inv_nsteps"));

        gridLayout_mutation_inversion->addWidget(label_inv_nsteps, 8, 0, 1, 1);

        spinboxInt_mutation_inv_n_steps = new MySpinBox(groupCheck_mutation_inversion_enabled);
        spinboxInt_mutation_inv_n_steps->setObjectName(QString::fromUtf8("spinboxInt_mutation_inv_n_steps"));
        spinboxInt_mutation_inv_n_steps->setMinimum(1);
        spinboxInt_mutation_inv_n_steps->setMaximum(16);
        spinboxInt_mutation_inv_n_steps->setValue(4);

        gridLayout_mutation_inversion->addWidget(spinboxInt_mutation_inv_n_steps, 8, 1, 1, 1);

        label_inv_threshold = new QLabel(groupCheck_mutation_inversion_enabled);
        label_inv_threshold->setObjectName(QString::fromUtf8("label_inv_threshold"));

        gridLayout_mutation_inversion->addWidget(label_inv_threshold, 8, 2, 1, 1);

        spinbox_mutation_inv_threshold = new MyDoubleSpinBox(groupCheck_mutation_inversion_enabled);
        spinbox_mutation_inv_threshold->setObjectName(QString::fromUtf8("spinbox_mutation_inv_threshold"));
        spinbox_mutation_inv_threshold->setMinimum(0.000000000000000);
        spinbox_mutation_inv_threshold->setMaximum(100.000000000000000);
        spinbox_mutation_inv_threshold->setValue(1.000000000000000);
        spinbox_mutation_inv_threshold->setSingleStep(0.100000000000000);

        gridLayout_mutation_inversion->addWidget(spinbox_mutation_inv_threshold, 8, 3, 1, 1);

        label_inv_colorfactor = new QLabel(groupCheck_mutation_inversion_enabled);
        label_inv_colorfactor->setObjectName(QString::fromUtf8("label_inv_colorfactor"));

        gridLayout_mutation_inversion->addWidget(label_inv_colorfactor, 8, 4, 1, 1);

        spinbox_mutation_inv_color_factor = new MyDoubleSpinBox(groupCheck_mutation_inversion_enabled);
        spinbox_mutation_inv_color_factor->setObjectName(QString::fromUtf8("spinbox_mutation_inv_color_factor"));
        spinbox_mutation_inv_color_factor->setMinimum(-100.000000000000000);
        spinbox_mutation_inv_color_factor->setMaximum(100.000000000000000);
        spinbox_mutation_inv_color_factor->setValue(1.000000000000000);
        spinbox_mutation_inv_color_factor->setSingleStep(0.100000000000000);

        gridLayout_mutation_inversion->addWidget(spinbox_mutation_inv_color_factor, 8, 5, 1, 1);

        label_inv_iter = new QLabel(groupCheck_mutation_inversion_enabled);
        label_inv_iter->setObjectName(QString::fromUtf8("label_inv_iter"));

        gridLayout_mutation_inversion->addWidget(label_inv_iter, 9, 0, 1, 1);

        spinboxInt_mutation_inv_iter_start = new MySpinBox(groupCheck_mutation_inversion_enabled);
        spinboxInt_mutation_inv_iter_start->setObjectName(QString::fromUtf8("spinboxInt_mutation_inv_iter_start"));
        spinboxInt_mutation_inv_iter_start->setMinimum(0);
        spinboxInt_mutation_inv_iter_start->setMaximum(10000);
        spinboxInt_mutation_inv_iter_start->setValue(0);

        gridLayout_mutation_inversion->addWidget(spinboxInt_mutation_inv_iter_start, 9, 1, 1, 2);

        label_inv_iter_stop = new QLabel(groupCheck_mutation_inversion_enabled);
        label_inv_iter_stop->setObjectName(QString::fromUtf8("label_inv_iter_stop"));

        gridLayout_mutation_inversion->addWidget(label_inv_iter_stop, 9, 3, 1, 1);

        spinboxInt_mutation_inv_iter_stop = new MySpinBox(groupCheck_mutation_inversion_enabled);
        spinboxInt_mutation_inv_iter_stop->setObjectName(QString::fromUtf8("spinboxInt_mutation_inv_iter_stop"));
        spinboxInt_mutation_inv_iter_stop->setMinimum(0);
        spinboxInt_mutation_inv_iter_stop->setMaximum(10000);
        spinboxInt_mutation_inv_iter_stop->setValue(10000);

        gridLayout_mutation_inversion->addWidget(spinboxInt_mutation_inv_iter_stop, 9, 4, 1, 2);


        verticalLayout_mutation_clip_inv->addWidget(groupCheck_mutation_inversion_enabled);

        groupCheck_mutation_clip_enabled = new MyGroupBox(cMutationClipInvPanel);
        groupCheck_mutation_clip_enabled->setObjectName(QString::fromUtf8("groupCheck_mutation_clip_enabled"));
        groupCheck_mutation_clip_enabled->setCheckable(true);
        groupCheck_mutation_clip_enabled->setChecked(false);
        gridLayout_mutation_clip = new QGridLayout(groupCheck_mutation_clip_enabled);
        gridLayout_mutation_clip->setObjectName(QString::fromUtf8("gridLayout_mutation_clip"));
        label_mutation_clip_type = new QLabel(groupCheck_mutation_clip_enabled);
        label_mutation_clip_type->setObjectName(QString::fromUtf8("label_mutation_clip_type"));

        gridLayout_mutation_clip->addWidget(label_mutation_clip_type, 0, 0, 1, 2);

        label1 = new QLabel(groupCheck_mutation_clip_enabled);
        label1->setObjectName(QString::fromUtf8("label1"));
        label1->setAlignment(Qt::AlignCenter);

        gridLayout_mutation_clip->addWidget(label1, 0, 6, 1, 1);

        spinbox_mutation_clip_section_weight = new MyDoubleSpinBox(groupCheck_mutation_clip_enabled);
        spinbox_mutation_clip_section_weight->setObjectName(QString::fromUtf8("spinbox_mutation_clip_section_weight"));
        spinbox_mutation_clip_section_weight->setMinimum(0.000000000000000);
        spinbox_mutation_clip_section_weight->setMaximum(1.000000000000000);
        spinbox_mutation_clip_section_weight->setSingleStep(0.050000000000000);
        spinbox_mutation_clip_section_weight->setValue(1.000000000000000);
        spinbox_mutation_clip_section_weight->setDecimals(2);
        spinbox_mutation_clip_section_weight->setMinimumSize(QSize(60, 0));

        gridLayout_mutation_clip->addWidget(spinbox_mutation_clip_section_weight, 1, 6, 1, 1);

        pushButton_mutation_clip_reset_weights = new QPushButton(groupCheck_mutation_clip_enabled);
        pushButton_mutation_clip_reset_weights->setObjectName(QString::fromUtf8("pushButton_mutation_clip_reset_weights"));
        pushButton_mutation_clip_reset_weights->setMaximumSize(QSize(60, 16777215));

        gridLayout_mutation_clip->addWidget(pushButton_mutation_clip_reset_weights, 2, 6, 1, 1);

        comboBox_mutation_clip_type = new QComboBox(groupCheck_mutation_clip_enabled);
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->addItem(QString());
        comboBox_mutation_clip_type->setObjectName(QString::fromUtf8("comboBox_mutation_clip_type"));

        gridLayout_mutation_clip->addWidget(comboBox_mutation_clip_type, 0, 2, 1, 4);

        label_clip_center = new QLabel(groupCheck_mutation_clip_enabled);
        label_clip_center->setObjectName(QString::fromUtf8("label_clip_center"));

        gridLayout_mutation_clip->addWidget(label_clip_center, 1, 0, 1, 1);

        spinbox_mutation_clip_center_ax = new MyDoubleSpinBox(groupCheck_mutation_clip_enabled);
        spinbox_mutation_clip_center_ax->setObjectName(QString::fromUtf8("spinbox_mutation_clip_center_ax"));
        spinbox_mutation_clip_center_ax->setMinimum(-100.000000000000000);
        spinbox_mutation_clip_center_ax->setMaximum(100.000000000000000);
        spinbox_mutation_clip_center_ax->setSingleStep(0.100000000000000);

        gridLayout_mutation_clip->addWidget(spinbox_mutation_clip_center_ax, 1, 1, 1, 1);

        label_clip_center_y = new QLabel(groupCheck_mutation_clip_enabled);
        label_clip_center_y->setObjectName(QString::fromUtf8("label_clip_center_y"));

        gridLayout_mutation_clip->addWidget(label_clip_center_y, 1, 2, 1, 1);

        spinbox_mutation_clip_center_ay = new MyDoubleSpinBox(groupCheck_mutation_clip_enabled);
        spinbox_mutation_clip_center_ay->setObjectName(QString::fromUtf8("spinbox_mutation_clip_center_ay"));
        spinbox_mutation_clip_center_ay->setMinimum(-100.000000000000000);
        spinbox_mutation_clip_center_ay->setMaximum(100.000000000000000);
        spinbox_mutation_clip_center_ay->setSingleStep(0.100000000000000);

        gridLayout_mutation_clip->addWidget(spinbox_mutation_clip_center_ay, 1, 3, 1, 1);

        label_clip_center_z = new QLabel(groupCheck_mutation_clip_enabled);
        label_clip_center_z->setObjectName(QString::fromUtf8("label_clip_center_z"));

        gridLayout_mutation_clip->addWidget(label_clip_center_z, 1, 4, 1, 1);

        spinbox_mutation_clip_center_az = new MyDoubleSpinBox(groupCheck_mutation_clip_enabled);
        spinbox_mutation_clip_center_az->setObjectName(QString::fromUtf8("spinbox_mutation_clip_center_az"));
        spinbox_mutation_clip_center_az->setMinimum(-100.000000000000000);
        spinbox_mutation_clip_center_az->setMaximum(100.000000000000000);
        spinbox_mutation_clip_center_az->setSingleStep(0.100000000000000);

        gridLayout_mutation_clip->addWidget(spinbox_mutation_clip_center_az, 1, 5, 1, 1);

        label_clip_size = new QLabel(groupCheck_mutation_clip_enabled);
        label_clip_size->setObjectName(QString::fromUtf8("label_clip_size"));

        gridLayout_mutation_clip->addWidget(label_clip_size, 2, 0, 1, 1);

        spinbox_mutation_clip_size_ax = new MyDoubleSpinBox(groupCheck_mutation_clip_enabled);
        spinbox_mutation_clip_size_ax->setObjectName(QString::fromUtf8("spinbox_mutation_clip_size_ax"));
        spinbox_mutation_clip_size_ax->setMinimum(0.001000000000000);
        spinbox_mutation_clip_size_ax->setMaximum(100.000000000000000);
        spinbox_mutation_clip_size_ax->setValue(1.000000000000000);
        spinbox_mutation_clip_size_ax->setSingleStep(0.100000000000000);

        gridLayout_mutation_clip->addWidget(spinbox_mutation_clip_size_ax, 2, 1, 1, 1);

        label_clip_size_y = new QLabel(groupCheck_mutation_clip_enabled);
        label_clip_size_y->setObjectName(QString::fromUtf8("label_clip_size_y"));

        gridLayout_mutation_clip->addWidget(label_clip_size_y, 2, 2, 1, 1);

        spinbox_mutation_clip_size_ay = new MyDoubleSpinBox(groupCheck_mutation_clip_enabled);
        spinbox_mutation_clip_size_ay->setObjectName(QString::fromUtf8("spinbox_mutation_clip_size_ay"));
        spinbox_mutation_clip_size_ay->setMinimum(0.001000000000000);
        spinbox_mutation_clip_size_ay->setMaximum(100.000000000000000);
        spinbox_mutation_clip_size_ay->setValue(1.000000000000000);
        spinbox_mutation_clip_size_ay->setSingleStep(0.100000000000000);

        gridLayout_mutation_clip->addWidget(spinbox_mutation_clip_size_ay, 2, 3, 1, 1);

        label_clip_size_z = new QLabel(groupCheck_mutation_clip_enabled);
        label_clip_size_z->setObjectName(QString::fromUtf8("label_clip_size_z"));

        gridLayout_mutation_clip->addWidget(label_clip_size_z, 2, 4, 1, 1);

        spinbox_mutation_clip_size_az = new MyDoubleSpinBox(groupCheck_mutation_clip_enabled);
        spinbox_mutation_clip_size_az->setObjectName(QString::fromUtf8("spinbox_mutation_clip_size_az"));
        spinbox_mutation_clip_size_az->setMinimum(0.001000000000000);
        spinbox_mutation_clip_size_az->setMaximum(100.000000000000000);
        spinbox_mutation_clip_size_az->setValue(1.000000000000000);
        spinbox_mutation_clip_size_az->setSingleStep(0.100000000000000);

        gridLayout_mutation_clip->addWidget(spinbox_mutation_clip_size_az, 2, 5, 1, 1);

        label_clip_radius = new QLabel(groupCheck_mutation_clip_enabled);
        label_clip_radius->setObjectName(QString::fromUtf8("label_clip_radius"));

        gridLayout_mutation_clip->addWidget(label_clip_radius, 3, 0, 1, 1);

        spinbox_mutation_clip_radius = new MyDoubleSpinBox(groupCheck_mutation_clip_enabled);
        spinbox_mutation_clip_radius->setObjectName(QString::fromUtf8("spinbox_mutation_clip_radius"));
        spinbox_mutation_clip_radius->setMinimum(0.001000000000000);
        spinbox_mutation_clip_radius->setMaximum(100.000000000000000);
        spinbox_mutation_clip_radius->setValue(1.000000000000000);
        spinbox_mutation_clip_radius->setSingleStep(0.100000000000000);

        gridLayout_mutation_clip->addWidget(spinbox_mutation_clip_radius, 3, 1, 1, 1);

        label_clip_major_r = new QLabel(groupCheck_mutation_clip_enabled);
        label_clip_major_r->setObjectName(QString::fromUtf8("label_clip_major_r"));

        gridLayout_mutation_clip->addWidget(label_clip_major_r, 3, 2, 1, 1);

        spinbox_mutation_clip_major_radius = new MyDoubleSpinBox(groupCheck_mutation_clip_enabled);
        spinbox_mutation_clip_major_radius->setObjectName(QString::fromUtf8("spinbox_mutation_clip_major_radius"));
        spinbox_mutation_clip_major_radius->setMinimum(0.001000000000000);
        spinbox_mutation_clip_major_radius->setMaximum(100.000000000000000);
        spinbox_mutation_clip_major_radius->setValue(2.000000000000000);
        spinbox_mutation_clip_major_radius->setSingleStep(0.100000000000000);

        gridLayout_mutation_clip->addWidget(spinbox_mutation_clip_major_radius, 3, 3, 1, 1);

        label_clip_angle = new QLabel(groupCheck_mutation_clip_enabled);
        label_clip_angle->setObjectName(QString::fromUtf8("label_clip_angle"));

        gridLayout_mutation_clip->addWidget(label_clip_angle, 3, 4, 1, 1);

        spinbox_mutation_clip_angle = new MyDoubleSpinBox(groupCheck_mutation_clip_enabled);
        spinbox_mutation_clip_angle->setObjectName(QString::fromUtf8("spinbox_mutation_clip_angle"));
        spinbox_mutation_clip_angle->setMinimum(-360.000000000000000);
        spinbox_mutation_clip_angle->setMaximum(360.000000000000000);
        spinbox_mutation_clip_angle->setSingleStep(1.000000000000000);

        gridLayout_mutation_clip->addWidget(spinbox_mutation_clip_angle, 3, 5, 1, 1);

        label_clip_freq = new QLabel(groupCheck_mutation_clip_enabled);
        label_clip_freq->setObjectName(QString::fromUtf8("label_clip_freq"));

        gridLayout_mutation_clip->addWidget(label_clip_freq, 4, 0, 1, 1);

        spinbox_mutation_clip_frequency = new MyDoubleSpinBox(groupCheck_mutation_clip_enabled);
        spinbox_mutation_clip_frequency->setObjectName(QString::fromUtf8("spinbox_mutation_clip_frequency"));
        spinbox_mutation_clip_frequency->setMinimum(0.000000000000000);
        spinbox_mutation_clip_frequency->setMaximum(100.000000000000000);
        spinbox_mutation_clip_frequency->setValue(1.000000000000000);
        spinbox_mutation_clip_frequency->setSingleStep(0.100000000000000);

        gridLayout_mutation_clip->addWidget(spinbox_mutation_clip_frequency, 4, 1, 1, 1);

        label_clip_amp = new QLabel(groupCheck_mutation_clip_enabled);
        label_clip_amp->setObjectName(QString::fromUtf8("label_clip_amp"));

        gridLayout_mutation_clip->addWidget(label_clip_amp, 4, 2, 1, 1);

        spinbox_mutation_clip_amplitude = new MyDoubleSpinBox(groupCheck_mutation_clip_enabled);
        spinbox_mutation_clip_amplitude->setObjectName(QString::fromUtf8("spinbox_mutation_clip_amplitude"));
        spinbox_mutation_clip_amplitude->setMinimum(0.000000000000000);
        spinbox_mutation_clip_amplitude->setMaximum(100.000000000000000);
        spinbox_mutation_clip_amplitude->setValue(0.100000000000000);
        spinbox_mutation_clip_amplitude->setSingleStep(0.010000000000000);

        gridLayout_mutation_clip->addWidget(spinbox_mutation_clip_amplitude, 4, 3, 1, 1);

        label_clip_smooth = new QLabel(groupCheck_mutation_clip_enabled);
        label_clip_smooth->setObjectName(QString::fromUtf8("label_clip_smooth"));

        gridLayout_mutation_clip->addWidget(label_clip_smooth, 4, 4, 1, 1);

        spinbox_mutation_clip_smooth_k = new MyDoubleSpinBox(groupCheck_mutation_clip_enabled);
        spinbox_mutation_clip_smooth_k->setObjectName(QString::fromUtf8("spinbox_mutation_clip_smooth_k"));
        spinbox_mutation_clip_smooth_k->setMinimum(0.001000000000000);
        spinbox_mutation_clip_smooth_k->setMaximum(10.000000000000000);
        spinbox_mutation_clip_smooth_k->setValue(0.100000000000000);
        spinbox_mutation_clip_smooth_k->setSingleStep(0.010000000000000);

        gridLayout_mutation_clip->addWidget(spinbox_mutation_clip_smooth_k, 4, 5, 1, 1);

        label_clip_bool = new QLabel(groupCheck_mutation_clip_enabled);
        label_clip_bool->setObjectName(QString::fromUtf8("label_clip_bool"));

        gridLayout_mutation_clip->addWidget(label_clip_bool, 5, 0, 1, 1);

        spinboxInt_mutation_clip_boolean_op = new MySpinBox(groupCheck_mutation_clip_enabled);
        spinboxInt_mutation_clip_boolean_op->setObjectName(QString::fromUtf8("spinboxInt_mutation_clip_boolean_op"));
        spinboxInt_mutation_clip_boolean_op->setMinimum(0);
        spinboxInt_mutation_clip_boolean_op->setMaximum(5);
        spinboxInt_mutation_clip_boolean_op->setValue(0);

        gridLayout_mutation_clip->addWidget(spinboxInt_mutation_clip_boolean_op, 5, 1, 1, 2);

        label_clip_npoints = new QLabel(groupCheck_mutation_clip_enabled);
        label_clip_npoints->setObjectName(QString::fromUtf8("label_clip_npoints"));

        gridLayout_mutation_clip->addWidget(label_clip_npoints, 5, 3, 1, 1);

        spinboxInt_mutation_clip_n_points = new MySpinBox(groupCheck_mutation_clip_enabled);
        spinboxInt_mutation_clip_n_points->setObjectName(QString::fromUtf8("spinboxInt_mutation_clip_n_points"));
        spinboxInt_mutation_clip_n_points->setMinimum(2);
        spinboxInt_mutation_clip_n_points->setMaximum(32);
        spinboxInt_mutation_clip_n_points->setValue(5);

        gridLayout_mutation_clip->addWidget(spinboxInt_mutation_clip_n_points, 5, 4, 1, 2);

        label_clip_param = new QLabel(groupCheck_mutation_clip_enabled);
        label_clip_param->setObjectName(QString::fromUtf8("label_clip_param"));

        gridLayout_mutation_clip->addWidget(label_clip_param, 6, 0, 1, 1);

        spinbox_mutation_clip_param_a = new MyDoubleSpinBox(groupCheck_mutation_clip_enabled);
        spinbox_mutation_clip_param_a->setObjectName(QString::fromUtf8("spinbox_mutation_clip_param_a"));
        spinbox_mutation_clip_param_a->setMinimum(-100.000000000000000);
        spinbox_mutation_clip_param_a->setMaximum(100.000000000000000);
        spinbox_mutation_clip_param_a->setValue(1.000000000000000);
        spinbox_mutation_clip_param_a->setSingleStep(0.100000000000000);

        gridLayout_mutation_clip->addWidget(spinbox_mutation_clip_param_a, 6, 1, 1, 1);

        label_clip_param_b = new QLabel(groupCheck_mutation_clip_enabled);
        label_clip_param_b->setObjectName(QString::fromUtf8("label_clip_param_b"));

        gridLayout_mutation_clip->addWidget(label_clip_param_b, 6, 2, 1, 1);

        spinbox_mutation_clip_param_b = new MyDoubleSpinBox(groupCheck_mutation_clip_enabled);
        spinbox_mutation_clip_param_b->setObjectName(QString::fromUtf8("spinbox_mutation_clip_param_b"));
        spinbox_mutation_clip_param_b->setMinimum(-100.000000000000000);
        spinbox_mutation_clip_param_b->setMaximum(100.000000000000000);
        spinbox_mutation_clip_param_b->setValue(1.000000000000000);
        spinbox_mutation_clip_param_b->setSingleStep(0.100000000000000);

        gridLayout_mutation_clip->addWidget(spinbox_mutation_clip_param_b, 6, 3, 1, 1);

        label_clip_param_c = new QLabel(groupCheck_mutation_clip_enabled);
        label_clip_param_c->setObjectName(QString::fromUtf8("label_clip_param_c"));

        gridLayout_mutation_clip->addWidget(label_clip_param_c, 6, 4, 1, 1);

        spinbox_mutation_clip_param_c = new MyDoubleSpinBox(groupCheck_mutation_clip_enabled);
        spinbox_mutation_clip_param_c->setObjectName(QString::fromUtf8("spinbox_mutation_clip_param_c"));
        spinbox_mutation_clip_param_c->setMinimum(-100.000000000000000);
        spinbox_mutation_clip_param_c->setMaximum(100.000000000000000);
        spinbox_mutation_clip_param_c->setValue(1.000000000000000);
        spinbox_mutation_clip_param_c->setSingleStep(0.100000000000000);

        gridLayout_mutation_clip->addWidget(spinbox_mutation_clip_param_c, 6, 5, 1, 1);

        label_clip_threshold = new QLabel(groupCheck_mutation_clip_enabled);
        label_clip_threshold->setObjectName(QString::fromUtf8("label_clip_threshold"));

        gridLayout_mutation_clip->addWidget(label_clip_threshold, 7, 0, 1, 1);

        spinbox_mutation_clip_threshold = new MyDoubleSpinBox(groupCheck_mutation_clip_enabled);
        spinbox_mutation_clip_threshold->setObjectName(QString::fromUtf8("spinbox_mutation_clip_threshold"));
        spinbox_mutation_clip_threshold->setMinimum(0.000000000000000);
        spinbox_mutation_clip_threshold->setMaximum(100.000000000000000);
        spinbox_mutation_clip_threshold->setValue(1.000000000000000);
        spinbox_mutation_clip_threshold->setSingleStep(0.100000000000000);

        gridLayout_mutation_clip->addWidget(spinbox_mutation_clip_threshold, 7, 1, 1, 1);

        label_clip_prerot_x = new QLabel(groupCheck_mutation_clip_enabled);
        label_clip_prerot_x->setObjectName(QString::fromUtf8("label_clip_prerot_x"));

        gridLayout_mutation_clip->addWidget(label_clip_prerot_x, 7, 2, 1, 1);

        spinbox_mutation_clip_pre_rot_ax = new MyDoubleSpinBox(groupCheck_mutation_clip_enabled);
        spinbox_mutation_clip_pre_rot_ax->setObjectName(QString::fromUtf8("spinbox_mutation_clip_pre_rot_ax"));
        spinbox_mutation_clip_pre_rot_ax->setMinimum(-360.000000000000000);
        spinbox_mutation_clip_pre_rot_ax->setMaximum(360.000000000000000);
        spinbox_mutation_clip_pre_rot_ax->setSingleStep(1.000000000000000);

        gridLayout_mutation_clip->addWidget(spinbox_mutation_clip_pre_rot_ax, 7, 3, 1, 1);

        label_clip_prerot_y = new QLabel(groupCheck_mutation_clip_enabled);
        label_clip_prerot_y->setObjectName(QString::fromUtf8("label_clip_prerot_y"));

        gridLayout_mutation_clip->addWidget(label_clip_prerot_y, 7, 4, 1, 1);

        spinbox_mutation_clip_pre_rot_ay = new MyDoubleSpinBox(groupCheck_mutation_clip_enabled);
        spinbox_mutation_clip_pre_rot_ay->setObjectName(QString::fromUtf8("spinbox_mutation_clip_pre_rot_ay"));
        spinbox_mutation_clip_pre_rot_ay->setMinimum(-360.000000000000000);
        spinbox_mutation_clip_pre_rot_ay->setMaximum(360.000000000000000);
        spinbox_mutation_clip_pre_rot_ay->setSingleStep(1.000000000000000);

        gridLayout_mutation_clip->addWidget(spinbox_mutation_clip_pre_rot_ay, 7, 5, 1, 1);

        label_clip_prerot_z = new QLabel(groupCheck_mutation_clip_enabled);
        label_clip_prerot_z->setObjectName(QString::fromUtf8("label_clip_prerot_z"));

        gridLayout_mutation_clip->addWidget(label_clip_prerot_z, 8, 0, 1, 1);

        spinbox_mutation_clip_pre_rot_az = new MyDoubleSpinBox(groupCheck_mutation_clip_enabled);
        spinbox_mutation_clip_pre_rot_az->setObjectName(QString::fromUtf8("spinbox_mutation_clip_pre_rot_az"));
        spinbox_mutation_clip_pre_rot_az->setMinimum(-360.000000000000000);
        spinbox_mutation_clip_pre_rot_az->setMaximum(360.000000000000000);
        spinbox_mutation_clip_pre_rot_az->setSingleStep(1.000000000000000);

        gridLayout_mutation_clip->addWidget(spinbox_mutation_clip_pre_rot_az, 8, 1, 1, 1);

        label_clip_iter_start = new QLabel(groupCheck_mutation_clip_enabled);
        label_clip_iter_start->setObjectName(QString::fromUtf8("label_clip_iter_start"));

        gridLayout_mutation_clip->addWidget(label_clip_iter_start, 8, 2, 1, 1);

        spinboxInt_mutation_clip_iter_start = new MySpinBox(groupCheck_mutation_clip_enabled);
        spinboxInt_mutation_clip_iter_start->setObjectName(QString::fromUtf8("spinboxInt_mutation_clip_iter_start"));
        spinboxInt_mutation_clip_iter_start->setMinimum(0);
        spinboxInt_mutation_clip_iter_start->setMaximum(10000);
        spinboxInt_mutation_clip_iter_start->setValue(0);

        gridLayout_mutation_clip->addWidget(spinboxInt_mutation_clip_iter_start, 8, 3, 1, 1);

        label_clip_iter_stop = new QLabel(groupCheck_mutation_clip_enabled);
        label_clip_iter_stop->setObjectName(QString::fromUtf8("label_clip_iter_stop"));

        gridLayout_mutation_clip->addWidget(label_clip_iter_stop, 8, 4, 1, 1);

        spinboxInt_mutation_clip_iter_stop = new MySpinBox(groupCheck_mutation_clip_enabled);
        spinboxInt_mutation_clip_iter_stop->setObjectName(QString::fromUtf8("spinboxInt_mutation_clip_iter_stop"));
        spinboxInt_mutation_clip_iter_stop->setMinimum(0);
        spinboxInt_mutation_clip_iter_stop->setMaximum(10000);
        spinboxInt_mutation_clip_iter_stop->setValue(10000);

        gridLayout_mutation_clip->addWidget(spinboxInt_mutation_clip_iter_stop, 8, 5, 1, 1);


        verticalLayout_mutation_clip_inv->addWidget(groupCheck_mutation_clip_enabled);


        retranslateUi(cMutationClipInvPanel);

        QMetaObject::connectSlotsByName(cMutationClipInvPanel);
    } // setupUi

    void retranslateUi(QWidget *cMutationClipInvPanel)
    {
        groupCheck_mutation_inversion_enabled->setTitle(QCoreApplication::translate("cMutationClipInvPanel", "Inversion System", nullptr));
        label_mutation_inv_type->setText(QCoreApplication::translate("cMutationClipInvPanel", "Inversion Type:", nullptr));
        label->setText(QCoreApplication::translate("cMutationClipInvPanel", "Weight", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_mutation_inversion_section_weight->setToolTip(QCoreApplication::translate("cMutationClipInvPanel", "Section weight: 1=full effect, 0=off", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_mutation_inversion_reset_weights->setText(QCoreApplication::translate("cMutationClipInvPanel", "Reset", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_mutation_inversion_reset_weights->setToolTip(QCoreApplication::translate("cMutationClipInvPanel", "Reset this section's weights to 1.0", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_mutation_inv_type->setItemText(0, QCoreApplication::translate("cMutationClipInvPanel", "None", nullptr));
        comboBox_mutation_inv_type->setItemText(1, QCoreApplication::translate("cMutationClipInvPanel", "Ellipsoid", nullptr));
        comboBox_mutation_inv_type->setItemText(2, QCoreApplication::translate("cMutationClipInvPanel", "Cylinder", nullptr));
        comboBox_mutation_inv_type->setItemText(3, QCoreApplication::translate("cMutationClipInvPanel", "Torus", nullptr));
        comboBox_mutation_inv_type->setItemText(4, QCoreApplication::translate("cMutationClipInvPanel", "Hyperboloid", nullptr));
        comboBox_mutation_inv_type->setItemText(5, QCoreApplication::translate("cMutationClipInvPanel", "Paraboloid", nullptr));
        comboBox_mutation_inv_type->setItemText(6, QCoreApplication::translate("cMutationClipInvPanel", "Cone", nullptr));
        comboBox_mutation_inv_type->setItemText(7, QCoreApplication::translate("cMutationClipInvPanel", "Saddle", nullptr));
        comboBox_mutation_inv_type->setItemText(8, QCoreApplication::translate("cMutationClipInvPanel", "Spiral", nullptr));
        comboBox_mutation_inv_type->setItemText(9, QCoreApplication::translate("cMutationClipInvPanel", "Lemniscate", nullptr));
        comboBox_mutation_inv_type->setItemText(10, QCoreApplication::translate("cMutationClipInvPanel", "Cassini", nullptr));
        comboBox_mutation_inv_type->setItemText(11, QCoreApplication::translate("cMutationClipInvPanel", "Dipole", nullptr));
        comboBox_mutation_inv_type->setItemText(12, QCoreApplication::translate("cMutationClipInvPanel", "Multipoint", nullptr));
        comboBox_mutation_inv_type->setItemText(13, QCoreApplication::translate("cMutationClipInvPanel", "Chain (2-step)", nullptr));
        comboBox_mutation_inv_type->setItemText(14, QCoreApplication::translate("cMutationClipInvPanel", "Nest (K-step)", nullptr));
        comboBox_mutation_inv_type->setItemText(15, QCoreApplication::translate("cMutationClipInvPanel", "Apollonian", nullptr));
        comboBox_mutation_inv_type->setItemText(16, QCoreApplication::translate("cMutationClipInvPanel", "Ford Circle", nullptr));
        comboBox_mutation_inv_type->setItemText(17, QCoreApplication::translate("cMutationClipInvPanel", "Schottky Group", nullptr));
        comboBox_mutation_inv_type->setItemText(18, QCoreApplication::translate("cMutationClipInvPanel", "Fuchsian", nullptr));
        comboBox_mutation_inv_type->setItemText(19, QCoreApplication::translate("cMutationClipInvPanel", "Modular (SL2Z)", nullptr));
        comboBox_mutation_inv_type->setItemText(20, QCoreApplication::translate("cMutationClipInvPanel", "Hecke", nullptr));
        comboBox_mutation_inv_type->setItemText(21, QCoreApplication::translate("cMutationClipInvPanel", "Pre-Rotation", nullptr));
        comboBox_mutation_inv_type->setItemText(22, QCoreApplication::translate("cMutationClipInvPanel", "Pre-Shear", nullptr));
        comboBox_mutation_inv_type->setItemText(23, QCoreApplication::translate("cMutationClipInvPanel", "Pre-Fold", nullptr));
        comboBox_mutation_inv_type->setItemText(24, QCoreApplication::translate("cMutationClipInvPanel", "Pre-Abs", nullptr));
        comboBox_mutation_inv_type->setItemText(25, QCoreApplication::translate("cMutationClipInvPanel", "Post-Scale Pulse", nullptr));
        comboBox_mutation_inv_type->setItemText(26, QCoreApplication::translate("cMutationClipInvPanel", "Post-Offset Wave", nullptr));
        comboBox_mutation_inv_type->setItemText(27, QCoreApplication::translate("cMutationClipInvPanel", "Iterative Angle", nullptr));
        comboBox_mutation_inv_type->setItemText(28, QCoreApplication::translate("cMutationClipInvPanel", "DE-Aware", nullptr));
        comboBox_mutation_inv_type->setItemText(29, QCoreApplication::translate("cMutationClipInvPanel", "Color-Trigger", nullptr));
        comboBox_mutation_inv_type->setItemText(30, QCoreApplication::translate("cMutationClipInvPanel", "Orbit-Trap", nullptr));
        comboBox_mutation_inv_type->setItemText(31, QCoreApplication::translate("cMutationClipInvPanel", "Quaternion", nullptr));
        comboBox_mutation_inv_type->setItemText(32, QCoreApplication::translate("cMutationClipInvPanel", "Dual Complex", nullptr));
        comboBox_mutation_inv_type->setItemText(33, QCoreApplication::translate("cMutationClipInvPanel", "Split Complex", nullptr));
        comboBox_mutation_inv_type->setItemText(34, QCoreApplication::translate("cMutationClipInvPanel", "Dual Number", nullptr));
        comboBox_mutation_inv_type->setItemText(35, QCoreApplication::translate("cMutationClipInvPanel", "Octonion", nullptr));
        comboBox_mutation_inv_type->setItemText(36, QCoreApplication::translate("cMutationClipInvPanel", "Sedenion", nullptr));
        comboBox_mutation_inv_type->setItemText(37, QCoreApplication::translate("cMutationClipInvPanel", "Clifford", nullptr));
        comboBox_mutation_inv_type->setItemText(38, QCoreApplication::translate("cMutationClipInvPanel", "Grassmann", nullptr));
        comboBox_mutation_inv_type->setItemText(39, QCoreApplication::translate("cMutationClipInvPanel", "Non-Commutative", nullptr));
        comboBox_mutation_inv_type->setItemText(40, QCoreApplication::translate("cMutationClipInvPanel", "Probabilistic", nullptr));
        comboBox_mutation_inv_type->setItemText(41, QCoreApplication::translate("cMutationClipInvPanel", "x Spherical Fold", nullptr));
        comboBox_mutation_inv_type->setItemText(42, QCoreApplication::translate("cMutationClipInvPanel", "x Box Fold", nullptr));
        comboBox_mutation_inv_type->setItemText(43, QCoreApplication::translate("cMutationClipInvPanel", "x Mobius", nullptr));
        comboBox_mutation_inv_type->setItemText(44, QCoreApplication::translate("cMutationClipInvPanel", "x Kleinian", nullptr));
        comboBox_mutation_inv_type->setItemText(45, QCoreApplication::translate("cMutationClipInvPanel", "x Julia", nullptr));
        comboBox_mutation_inv_type->setItemText(46, QCoreApplication::translate("cMutationClipInvPanel", "x IFS", nullptr));
        comboBox_mutation_inv_type->setItemText(47, QCoreApplication::translate("cMutationClipInvPanel", "x Loxodromic", nullptr));
        comboBox_mutation_inv_type->setItemText(48, QCoreApplication::translate("cMutationClipInvPanel", "x Parabolic", nullptr));
        comboBox_mutation_inv_type->setItemText(49, QCoreApplication::translate("cMutationClipInvPanel", "x Elliptic", nullptr));
        comboBox_mutation_inv_type->setItemText(50, QCoreApplication::translate("cMutationClipInvPanel", "x Hyperbolic Translation", nullptr));

        label_inv_center->setText(QCoreApplication::translate("cMutationClipInvPanel", "Center X:", nullptr));
        label_inv_center_y->setText(QCoreApplication::translate("cMutationClipInvPanel", "Y:", nullptr));
        label_inv_center_z->setText(QCoreApplication::translate("cMutationClipInvPanel", "Z:", nullptr));
        label_inv_radius->setText(QCoreApplication::translate("cMutationClipInvPanel", "Radius:", nullptr));
        label_inv_param_a->setText(QCoreApplication::translate("cMutationClipInvPanel", "A:", nullptr));
        label_inv_param_b->setText(QCoreApplication::translate("cMutationClipInvPanel", "B:", nullptr));
        label_inv_param_c->setText(QCoreApplication::translate("cMutationClipInvPanel", "C:", nullptr));
        label_inv_scale->setText(QCoreApplication::translate("cMutationClipInvPanel", "Scale:", nullptr));
        label_inv_angle->setText(QCoreApplication::translate("cMutationClipInvPanel", "Angle:", nullptr));
        label_inv_freq->setText(QCoreApplication::translate("cMutationClipInvPanel", "Frequency:", nullptr));
        label_inv_amp->setText(QCoreApplication::translate("cMutationClipInvPanel", "Amplitude:", nullptr));
        label_inv_minr->setText(QCoreApplication::translate("cMutationClipInvPanel", "MinR:", nullptr));
        label_inv_maxr->setText(QCoreApplication::translate("cMutationClipInvPanel", "MaxR:", nullptr));
        label_inv_prerot_x->setText(QCoreApplication::translate("cMutationClipInvPanel", "PreRotX:", nullptr));
        label_inv_prerot_y->setText(QCoreApplication::translate("cMutationClipInvPanel", "Y:", nullptr));
        label_inv_prerot_z->setText(QCoreApplication::translate("cMutationClipInvPanel", "PreRotZ:", nullptr));
        label_inv_center2->setText(QCoreApplication::translate("cMutationClipInvPanel", "Center2 X:", nullptr));
        label_inv_center2_y->setText(QCoreApplication::translate("cMutationClipInvPanel", "Y:", nullptr));
        label_inv_center2_z->setText(QCoreApplication::translate("cMutationClipInvPanel", "Center2 Z:", nullptr));
        label_inv_radius2->setText(QCoreApplication::translate("cMutationClipInvPanel", "Radius2:", nullptr));
        label_inv_weight->setText(QCoreApplication::translate("cMutationClipInvPanel", "Weight:", nullptr));
        label_inv_nsteps->setText(QCoreApplication::translate("cMutationClipInvPanel", "N Steps:", nullptr));
        label_inv_threshold->setText(QCoreApplication::translate("cMutationClipInvPanel", "Threshold:", nullptr));
        label_inv_colorfactor->setText(QCoreApplication::translate("cMutationClipInvPanel", "Color:", nullptr));
        label_inv_iter->setText(QCoreApplication::translate("cMutationClipInvPanel", "Inv Iter:", nullptr));
        label_inv_iter_stop->setText(QCoreApplication::translate("cMutationClipInvPanel", "Stop:", nullptr));
        groupCheck_mutation_clip_enabled->setTitle(QCoreApplication::translate("cMutationClipInvPanel", "Clip System", nullptr));
        label_mutation_clip_type->setText(QCoreApplication::translate("cMutationClipInvPanel", "Clip Type:", nullptr));
        label1->setText(QCoreApplication::translate("cMutationClipInvPanel", "Weight", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_mutation_clip_section_weight->setToolTip(QCoreApplication::translate("cMutationClipInvPanel", "Section weight: 1=full effect, 0=off", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_mutation_clip_reset_weights->setText(QCoreApplication::translate("cMutationClipInvPanel", "Reset", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_mutation_clip_reset_weights->setToolTip(QCoreApplication::translate("cMutationClipInvPanel", "Reset this section's weights to 1.0", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_mutation_clip_type->setItemText(0, QCoreApplication::translate("cMutationClipInvPanel", "None", nullptr));
        comboBox_mutation_clip_type->setItemText(1, QCoreApplication::translate("cMutationClipInvPanel", "Ellipsoid", nullptr));
        comboBox_mutation_clip_type->setItemText(2, QCoreApplication::translate("cMutationClipInvPanel", "Torus", nullptr));
        comboBox_mutation_clip_type->setItemText(3, QCoreApplication::translate("cMutationClipInvPanel", "Cylinder (infinite)", nullptr));
        comboBox_mutation_clip_type->setItemText(4, QCoreApplication::translate("cMutationClipInvPanel", "Cone", nullptr));
        comboBox_mutation_clip_type->setItemText(5, QCoreApplication::translate("cMutationClipInvPanel", "Hyperboloid", nullptr));
        comboBox_mutation_clip_type->setItemText(6, QCoreApplication::translate("cMutationClipInvPanel", "Paraboloid", nullptr));
        comboBox_mutation_clip_type->setItemText(7, QCoreApplication::translate("cMutationClipInvPanel", "Saddle", nullptr));
        comboBox_mutation_clip_type->setItemText(8, QCoreApplication::translate("cMutationClipInvPanel", "Spiral", nullptr));
        comboBox_mutation_clip_type->setItemText(9, QCoreApplication::translate("cMutationClipInvPanel", "Wave", nullptr));
        comboBox_mutation_clip_type->setItemText(10, QCoreApplication::translate("cMutationClipInvPanel", "Noise", nullptr));
        comboBox_mutation_clip_type->setItemText(11, QCoreApplication::translate("cMutationClipInvPanel", "Union (OR)", nullptr));
        comboBox_mutation_clip_type->setItemText(12, QCoreApplication::translate("cMutationClipInvPanel", "Difference (A-B)", nullptr));
        comboBox_mutation_clip_type->setItemText(13, QCoreApplication::translate("cMutationClipInvPanel", "XOR", nullptr));
        comboBox_mutation_clip_type->setItemText(14, QCoreApplication::translate("cMutationClipInvPanel", "Smooth Union", nullptr));
        comboBox_mutation_clip_type->setItemText(15, QCoreApplication::translate("cMutationClipInvPanel", "Smooth Difference", nullptr));
        comboBox_mutation_clip_type->setItemText(16, QCoreApplication::translate("cMutationClipInvPanel", "Chain (3-stage)", nullptr));
        comboBox_mutation_clip_type->setItemText(17, QCoreApplication::translate("cMutationClipInvPanel", "Array (Grid)", nullptr));
        comboBox_mutation_clip_type->setItemText(18, QCoreApplication::translate("cMutationClipInvPanel", "Random Array", nullptr));
        comboBox_mutation_clip_type->setItemText(19, QCoreApplication::translate("cMutationClipInvPanel", "Hierarchical", nullptr));
        comboBox_mutation_clip_type->setItemText(20, QCoreApplication::translate("cMutationClipInvPanel", "Fractal", nullptr));
        comboBox_mutation_clip_type->setItemText(21, QCoreApplication::translate("cMutationClipInvPanel", "Pre-Rotation", nullptr));
        comboBox_mutation_clip_type->setItemText(22, QCoreApplication::translate("cMutationClipInvPanel", "Pre-Scale", nullptr));
        comboBox_mutation_clip_type->setItemText(23, QCoreApplication::translate("cMutationClipInvPanel", "Pre-Shear", nullptr));
        comboBox_mutation_clip_type->setItemText(24, QCoreApplication::translate("cMutationClipInvPanel", "Pre-Fold", nullptr));
        comboBox_mutation_clip_type->setItemText(25, QCoreApplication::translate("cMutationClipInvPanel", "Pre-Abs", nullptr));
        comboBox_mutation_clip_type->setItemText(26, QCoreApplication::translate("cMutationClipInvPanel", "Post-Offset", nullptr));
        comboBox_mutation_clip_type->setItemText(27, QCoreApplication::translate("cMutationClipInvPanel", "Post-Scale", nullptr));
        comboBox_mutation_clip_type->setItemText(28, QCoreApplication::translate("cMutationClipInvPanel", "Color-Depth", nullptr));
        comboBox_mutation_clip_type->setItemText(29, QCoreApplication::translate("cMutationClipInvPanel", "Orbit-Trap", nullptr));
        comboBox_mutation_clip_type->setItemText(30, QCoreApplication::translate("cMutationClipInvPanel", "DE-Visualization", nullptr));
        comboBox_mutation_clip_type->setItemText(31, QCoreApplication::translate("cMutationClipInvPanel", "Star (n-point)", nullptr));
        comboBox_mutation_clip_type->setItemText(32, QCoreApplication::translate("cMutationClipInvPanel", "Heart", nullptr));
        comboBox_mutation_clip_type->setItemText(33, QCoreApplication::translate("cMutationClipInvPanel", "Superformula", nullptr));
        comboBox_mutation_clip_type->setItemText(34, QCoreApplication::translate("cMutationClipInvPanel", "Gear", nullptr));
        comboBox_mutation_clip_type->setItemText(35, QCoreApplication::translate("cMutationClipInvPanel", "Spiral Galaxy", nullptr));
        comboBox_mutation_clip_type->setItemText(36, QCoreApplication::translate("cMutationClipInvPanel", "Voronoi", nullptr));
        comboBox_mutation_clip_type->setItemText(37, QCoreApplication::translate("cMutationClipInvPanel", "Delaunay", nullptr));
        comboBox_mutation_clip_type->setItemText(38, QCoreApplication::translate("cMutationClipInvPanel", "L-System", nullptr));
        comboBox_mutation_clip_type->setItemText(39, QCoreApplication::translate("cMutationClipInvPanel", "Julia Set", nullptr));
        comboBox_mutation_clip_type->setItemText(40, QCoreApplication::translate("cMutationClipInvPanel", "Mandelbrot Set", nullptr));
        comboBox_mutation_clip_type->setItemText(41, QCoreApplication::translate("cMutationClipInvPanel", "4D Hypercube", nullptr));
        comboBox_mutation_clip_type->setItemText(42, QCoreApplication::translate("cMutationClipInvPanel", "4D Hypersphere", nullptr));
        comboBox_mutation_clip_type->setItemText(43, QCoreApplication::translate("cMutationClipInvPanel", "Time-Dependent", nullptr));
        comboBox_mutation_clip_type->setItemText(44, QCoreApplication::translate("cMutationClipInvPanel", "Orbit-Dependent", nullptr));
        comboBox_mutation_clip_type->setItemText(45, QCoreApplication::translate("cMutationClipInvPanel", "DE-Dependent", nullptr));
        comboBox_mutation_clip_type->setItemText(46, QCoreApplication::translate("cMutationClipInvPanel", "Color-Dependent", nullptr));
        comboBox_mutation_clip_type->setItemText(47, QCoreApplication::translate("cMutationClipInvPanel", "Iteration-Dependent", nullptr));
        comboBox_mutation_clip_type->setItemText(48, QCoreApplication::translate("cMutationClipInvPanel", "Random-Dependent", nullptr));
        comboBox_mutation_clip_type->setItemText(49, QCoreApplication::translate("cMutationClipInvPanel", "Neural-Dependent", nullptr));
        comboBox_mutation_clip_type->setItemText(50, QCoreApplication::translate("cMutationClipInvPanel", "Fractal Recursion", nullptr));

        label_clip_center->setText(QCoreApplication::translate("cMutationClipInvPanel", "Center X:", nullptr));
        label_clip_center_y->setText(QCoreApplication::translate("cMutationClipInvPanel", "Y:", nullptr));
        label_clip_center_z->setText(QCoreApplication::translate("cMutationClipInvPanel", "Z:", nullptr));
        label_clip_size->setText(QCoreApplication::translate("cMutationClipInvPanel", "Size X:", nullptr));
        label_clip_size_y->setText(QCoreApplication::translate("cMutationClipInvPanel", "Y:", nullptr));
        label_clip_size_z->setText(QCoreApplication::translate("cMutationClipInvPanel", "Z:", nullptr));
        label_clip_radius->setText(QCoreApplication::translate("cMutationClipInvPanel", "Radius:", nullptr));
        label_clip_major_r->setText(QCoreApplication::translate("cMutationClipInvPanel", "MajorR:", nullptr));
        label_clip_angle->setText(QCoreApplication::translate("cMutationClipInvPanel", "Angle:", nullptr));
        label_clip_freq->setText(QCoreApplication::translate("cMutationClipInvPanel", "Frequency:", nullptr));
        label_clip_amp->setText(QCoreApplication::translate("cMutationClipInvPanel", "Amplitude:", nullptr));
        label_clip_smooth->setText(QCoreApplication::translate("cMutationClipInvPanel", "Smooth K:", nullptr));
        label_clip_bool->setText(QCoreApplication::translate("cMutationClipInvPanel", "Boolean Op:", nullptr));
        label_clip_npoints->setText(QCoreApplication::translate("cMutationClipInvPanel", "N Points:", nullptr));
        label_clip_param->setText(QCoreApplication::translate("cMutationClipInvPanel", "A:", nullptr));
        label_clip_param_b->setText(QCoreApplication::translate("cMutationClipInvPanel", "B:", nullptr));
        label_clip_param_c->setText(QCoreApplication::translate("cMutationClipInvPanel", "C:", nullptr));
        label_clip_threshold->setText(QCoreApplication::translate("cMutationClipInvPanel", "Threshold:", nullptr));
        label_clip_prerot_x->setText(QCoreApplication::translate("cMutationClipInvPanel", "PreRotX:", nullptr));
        label_clip_prerot_y->setText(QCoreApplication::translate("cMutationClipInvPanel", "Y:", nullptr));
        label_clip_prerot_z->setText(QCoreApplication::translate("cMutationClipInvPanel", "PreRotZ:", nullptr));
        label_clip_iter_start->setText(QCoreApplication::translate("cMutationClipInvPanel", "Clip Iter:", nullptr));
        label_clip_iter_stop->setText(QCoreApplication::translate("cMutationClipInvPanel", "Stop:", nullptr));
        (void)cMutationClipInvPanel;
    } // retranslateUi

};

namespace Ui {
    class cMutationClipInvPanel: public Ui_cMutationClipInvPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUTATION_CLIP_INV_PANEL_H
