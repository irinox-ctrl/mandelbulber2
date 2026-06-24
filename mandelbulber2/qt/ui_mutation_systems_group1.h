/********************************************************************************
** Form generated from reading UI file 'mutation_systems_group1.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUTATION_SYSTEMS_GROUP1_H
#define UI_MUTATION_SYSTEMS_GROUP1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "my_double_spin_box.h"
#include "my_group_box.h"
#include "my_spin_box.h"

QT_BEGIN_NAMESPACE

class Ui_cMutationSystemsGroup1
{
public:
    QVBoxLayout *verticalLayout_cMutationSystemsGroup1;
    MyGroupBox *groupCheck_mutation_mb_math_enabled;
    QGridLayout *gridLayout_mutation_mb_math;
    QLabel *label_mb_math_type;
    QLabel *label;
    MyDoubleSpinBox *spinbox_mutation_mb_math_section_weight;
    QPushButton *pushButton_mutation_mb_math_reset_weights;
    QComboBox *comboBox_mutation_mb_math_type;
    QLabel *label_mb_factor;
    MyDoubleSpinBox *spinbox_mutation_mb_factor;
    QLabel *label_mb_param_a;
    MyDoubleSpinBox *spinbox_mutation_mb_param_a;
    QLabel *label_mb_param_b;
    MyDoubleSpinBox *spinbox_mutation_mb_param_b;
    QLabel *label_mb_param_c;
    MyDoubleSpinBox *spinbox_mutation_mb_param_c;
    QLabel *label_mb_param_d;
    MyDoubleSpinBox *spinbox_mutation_mb_param_d;
    QLabel *label_mb_param_e;
    MyDoubleSpinBox *spinbox_mutation_mb_param_e;
    QLabel *label_mb_param_f;
    MyDoubleSpinBox *spinbox_mutation_mb_param_f;
    QLabel *label_mb_param_g;
    MyDoubleSpinBox *spinbox_mutation_mb_param_g;
    QLabel *label_mb_param_h;
    MyDoubleSpinBox *spinbox_mutation_mb_param_h;
    QLabel *label_mb_iter;
    MySpinBox *spinboxInt_mutation_mb_iter_start;
    QLabel *label_mb_iter_stop;
    MySpinBox *spinboxInt_mutation_mb_iter_stop;
    MyGroupBox *groupCheck_mutation_warp_dist_enabled;
    QGridLayout *gridLayout_mutation_warp_dist;
    QLabel *label_wd_type;
    QLabel *label1;
    MyDoubleSpinBox *spinbox_mutation_warp_dist_section_weight;
    QPushButton *pushButton_mutation_warp_dist_reset_weights;
    QComboBox *comboBox_mutation_warp_dist_type;
    QLabel *label_wd_factor;
    MyDoubleSpinBox *spinbox_mutation_wd_factor;
    QLabel *label_wd_param_a;
    MyDoubleSpinBox *spinbox_mutation_wd_param_a;
    QLabel *label_wd_param_b;
    MyDoubleSpinBox *spinbox_mutation_wd_param_b;
    QLabel *label_wd_param_c;
    MyDoubleSpinBox *spinbox_mutation_wd_param_c;
    QLabel *label_wd_param_d;
    MyDoubleSpinBox *spinbox_mutation_wd_param_d;
    QLabel *label_wd_freq;
    MyDoubleSpinBox *spinbox_mutation_wd_freq;
    QLabel *label_wd_amp;
    MyDoubleSpinBox *spinbox_mutation_wd_amp;
    QLabel *label_wd_scale;
    MyDoubleSpinBox *spinbox_mutation_wd_scale;
    QLabel *label_wd_phase;
    MyDoubleSpinBox *spinbox_mutation_wd_phase;
    QLabel *label_wd_iter;
    MySpinBox *spinboxInt_mutation_wd_iter_start;
    QLabel *label_wd_iter_stop;
    MySpinBox *spinboxInt_mutation_wd_iter_stop;
    MyGroupBox *groupCheck_mutation_symmetry_enabled;
    QGridLayout *gridLayout_mutation_symmetry;
    QLabel *label_sk_type;
    QLabel *label2;
    MyDoubleSpinBox *spinbox_mutation_symmetry_section_weight;
    QPushButton *pushButton_mutation_symmetry_reset_weights;
    QComboBox *comboBox_mutation_sym_kal_type;
    QLabel *label_sk_factor;
    MyDoubleSpinBox *spinbox_mutation_sk_factor;
    QLabel *label_sk_param_a;
    MyDoubleSpinBox *spinbox_mutation_sk_param_a;
    QLabel *label_sk_param_b;
    MyDoubleSpinBox *spinbox_mutation_sk_param_b;
    QLabel *label_sk_param_c;
    MyDoubleSpinBox *spinbox_mutation_sk_param_c;
    QLabel *label_sk_param_d;
    MyDoubleSpinBox *spinbox_mutation_sk_param_d;
    QLabel *label_sk_freq;
    MyDoubleSpinBox *spinbox_mutation_sk_freq;
    QLabel *label_sk_amp;
    MyDoubleSpinBox *spinbox_mutation_sk_amp;
    QLabel *label_sk_angle;
    MyDoubleSpinBox *spinbox_mutation_sk_angle;
    QLabel *label_sk_offset;
    MyDoubleSpinBox *spinbox_mutation_sk_offset;
    QLabel *label_sk_iter;
    MySpinBox *spinboxInt_mutation_sk_iter_start;
    QLabel *label_sk_iter_stop;
    MySpinBox *spinboxInt_mutation_sk_iter_stop;

    void setupUi(QWidget *cMutationSystemsGroup1)
    {
        if (cMutationSystemsGroup1->objectName().isEmpty())
            cMutationSystemsGroup1->setObjectName(QString::fromUtf8("cMutationSystemsGroup1"));
        verticalLayout_cMutationSystemsGroup1 = new QVBoxLayout(cMutationSystemsGroup1);
        verticalLayout_cMutationSystemsGroup1->setSpacing(2);
        verticalLayout_cMutationSystemsGroup1->setObjectName(QString::fromUtf8("verticalLayout_cMutationSystemsGroup1"));
        verticalLayout_cMutationSystemsGroup1->setContentsMargins(0, 0, 0, 0);
        groupCheck_mutation_mb_math_enabled = new MyGroupBox(cMutationSystemsGroup1);
        groupCheck_mutation_mb_math_enabled->setObjectName(QString::fromUtf8("groupCheck_mutation_mb_math_enabled"));
        groupCheck_mutation_mb_math_enabled->setCheckable(true);
        groupCheck_mutation_mb_math_enabled->setChecked(false);
        gridLayout_mutation_mb_math = new QGridLayout(groupCheck_mutation_mb_math_enabled);
        gridLayout_mutation_mb_math->setObjectName(QString::fromUtf8("gridLayout_mutation_mb_math"));
        label_mb_math_type = new QLabel(groupCheck_mutation_mb_math_enabled);
        label_mb_math_type->setObjectName(QString::fromUtf8("label_mb_math_type"));

        gridLayout_mutation_mb_math->addWidget(label_mb_math_type, 0, 0, 1, 1);

        label = new QLabel(groupCheck_mutation_mb_math_enabled);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout_mutation_mb_math->addWidget(label, 0, 6, 1, 1);

        spinbox_mutation_mb_math_section_weight = new MyDoubleSpinBox(groupCheck_mutation_mb_math_enabled);
        spinbox_mutation_mb_math_section_weight->setObjectName(QString::fromUtf8("spinbox_mutation_mb_math_section_weight"));
        spinbox_mutation_mb_math_section_weight->setMinimum(0.000000000000000);
        spinbox_mutation_mb_math_section_weight->setMaximum(1.000000000000000);
        spinbox_mutation_mb_math_section_weight->setSingleStep(0.050000000000000);
        spinbox_mutation_mb_math_section_weight->setValue(1.000000000000000);
        spinbox_mutation_mb_math_section_weight->setDecimals(2);
        spinbox_mutation_mb_math_section_weight->setMinimumSize(QSize(60, 0));

        gridLayout_mutation_mb_math->addWidget(spinbox_mutation_mb_math_section_weight, 1, 6, 1, 1);

        pushButton_mutation_mb_math_reset_weights = new QPushButton(groupCheck_mutation_mb_math_enabled);
        pushButton_mutation_mb_math_reset_weights->setObjectName(QString::fromUtf8("pushButton_mutation_mb_math_reset_weights"));
        pushButton_mutation_mb_math_reset_weights->setMaximumSize(QSize(60, 16777215));

        gridLayout_mutation_mb_math->addWidget(pushButton_mutation_mb_math_reset_weights, 2, 6, 1, 1);

        comboBox_mutation_mb_math_type = new QComboBox(groupCheck_mutation_mb_math_enabled);
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->addItem(QString());
        comboBox_mutation_mb_math_type->setObjectName(QString::fromUtf8("comboBox_mutation_mb_math_type"));

        gridLayout_mutation_mb_math->addWidget(comboBox_mutation_mb_math_type, 0, 1, 1, 5);

        label_mb_factor = new QLabel(groupCheck_mutation_mb_math_enabled);
        label_mb_factor->setObjectName(QString::fromUtf8("label_mb_factor"));

        gridLayout_mutation_mb_math->addWidget(label_mb_factor, 1, 0, 1, 1);

        spinbox_mutation_mb_factor = new MyDoubleSpinBox(groupCheck_mutation_mb_math_enabled);
        spinbox_mutation_mb_factor->setObjectName(QString::fromUtf8("spinbox_mutation_mb_factor"));
        spinbox_mutation_mb_factor->setMinimum(-100.000000000000000);
        spinbox_mutation_mb_factor->setMaximum(100.000000000000000);
        spinbox_mutation_mb_factor->setSingleStep(0.100000000000000);
        spinbox_mutation_mb_factor->setValue(1.000000000000000);
        spinbox_mutation_mb_factor->setDecimals(6);

        gridLayout_mutation_mb_math->addWidget(spinbox_mutation_mb_factor, 1, 1, 1, 1);

        label_mb_param_a = new QLabel(groupCheck_mutation_mb_math_enabled);
        label_mb_param_a->setObjectName(QString::fromUtf8("label_mb_param_a"));

        gridLayout_mutation_mb_math->addWidget(label_mb_param_a, 1, 2, 1, 1);

        spinbox_mutation_mb_param_a = new MyDoubleSpinBox(groupCheck_mutation_mb_math_enabled);
        spinbox_mutation_mb_param_a->setObjectName(QString::fromUtf8("spinbox_mutation_mb_param_a"));
        spinbox_mutation_mb_param_a->setMinimum(-100.000000000000000);
        spinbox_mutation_mb_param_a->setMaximum(100.000000000000000);
        spinbox_mutation_mb_param_a->setSingleStep(0.100000000000000);
        spinbox_mutation_mb_param_a->setValue(1.000000000000000);
        spinbox_mutation_mb_param_a->setDecimals(6);

        gridLayout_mutation_mb_math->addWidget(spinbox_mutation_mb_param_a, 1, 3, 1, 1);

        label_mb_param_b = new QLabel(groupCheck_mutation_mb_math_enabled);
        label_mb_param_b->setObjectName(QString::fromUtf8("label_mb_param_b"));

        gridLayout_mutation_mb_math->addWidget(label_mb_param_b, 1, 4, 1, 1);

        spinbox_mutation_mb_param_b = new MyDoubleSpinBox(groupCheck_mutation_mb_math_enabled);
        spinbox_mutation_mb_param_b->setObjectName(QString::fromUtf8("spinbox_mutation_mb_param_b"));
        spinbox_mutation_mb_param_b->setMinimum(-100.000000000000000);
        spinbox_mutation_mb_param_b->setMaximum(100.000000000000000);
        spinbox_mutation_mb_param_b->setSingleStep(0.100000000000000);
        spinbox_mutation_mb_param_b->setValue(1.000000000000000);
        spinbox_mutation_mb_param_b->setDecimals(6);

        gridLayout_mutation_mb_math->addWidget(spinbox_mutation_mb_param_b, 1, 5, 1, 1);

        label_mb_param_c = new QLabel(groupCheck_mutation_mb_math_enabled);
        label_mb_param_c->setObjectName(QString::fromUtf8("label_mb_param_c"));

        gridLayout_mutation_mb_math->addWidget(label_mb_param_c, 2, 0, 1, 1);

        spinbox_mutation_mb_param_c = new MyDoubleSpinBox(groupCheck_mutation_mb_math_enabled);
        spinbox_mutation_mb_param_c->setObjectName(QString::fromUtf8("spinbox_mutation_mb_param_c"));
        spinbox_mutation_mb_param_c->setMinimum(-100.000000000000000);
        spinbox_mutation_mb_param_c->setMaximum(100.000000000000000);
        spinbox_mutation_mb_param_c->setSingleStep(0.100000000000000);
        spinbox_mutation_mb_param_c->setValue(1.000000000000000);
        spinbox_mutation_mb_param_c->setDecimals(6);

        gridLayout_mutation_mb_math->addWidget(spinbox_mutation_mb_param_c, 2, 1, 1, 1);

        label_mb_param_d = new QLabel(groupCheck_mutation_mb_math_enabled);
        label_mb_param_d->setObjectName(QString::fromUtf8("label_mb_param_d"));

        gridLayout_mutation_mb_math->addWidget(label_mb_param_d, 2, 2, 1, 1);

        spinbox_mutation_mb_param_d = new MyDoubleSpinBox(groupCheck_mutation_mb_math_enabled);
        spinbox_mutation_mb_param_d->setObjectName(QString::fromUtf8("spinbox_mutation_mb_param_d"));
        spinbox_mutation_mb_param_d->setMinimum(-100.000000000000000);
        spinbox_mutation_mb_param_d->setMaximum(100.000000000000000);
        spinbox_mutation_mb_param_d->setSingleStep(0.100000000000000);
        spinbox_mutation_mb_param_d->setValue(1.000000000000000);
        spinbox_mutation_mb_param_d->setDecimals(6);

        gridLayout_mutation_mb_math->addWidget(spinbox_mutation_mb_param_d, 2, 3, 1, 1);

        label_mb_param_e = new QLabel(groupCheck_mutation_mb_math_enabled);
        label_mb_param_e->setObjectName(QString::fromUtf8("label_mb_param_e"));

        gridLayout_mutation_mb_math->addWidget(label_mb_param_e, 2, 4, 1, 1);

        spinbox_mutation_mb_param_e = new MyDoubleSpinBox(groupCheck_mutation_mb_math_enabled);
        spinbox_mutation_mb_param_e->setObjectName(QString::fromUtf8("spinbox_mutation_mb_param_e"));
        spinbox_mutation_mb_param_e->setMinimum(-100.000000000000000);
        spinbox_mutation_mb_param_e->setMaximum(100.000000000000000);
        spinbox_mutation_mb_param_e->setSingleStep(0.100000000000000);
        spinbox_mutation_mb_param_e->setValue(1.000000000000000);
        spinbox_mutation_mb_param_e->setDecimals(6);

        gridLayout_mutation_mb_math->addWidget(spinbox_mutation_mb_param_e, 2, 5, 1, 1);

        label_mb_param_f = new QLabel(groupCheck_mutation_mb_math_enabled);
        label_mb_param_f->setObjectName(QString::fromUtf8("label_mb_param_f"));

        gridLayout_mutation_mb_math->addWidget(label_mb_param_f, 3, 0, 1, 1);

        spinbox_mutation_mb_param_f = new MyDoubleSpinBox(groupCheck_mutation_mb_math_enabled);
        spinbox_mutation_mb_param_f->setObjectName(QString::fromUtf8("spinbox_mutation_mb_param_f"));
        spinbox_mutation_mb_param_f->setMinimum(-100.000000000000000);
        spinbox_mutation_mb_param_f->setMaximum(100.000000000000000);
        spinbox_mutation_mb_param_f->setSingleStep(0.100000000000000);
        spinbox_mutation_mb_param_f->setValue(1.000000000000000);
        spinbox_mutation_mb_param_f->setDecimals(6);

        gridLayout_mutation_mb_math->addWidget(spinbox_mutation_mb_param_f, 3, 1, 1, 1);

        label_mb_param_g = new QLabel(groupCheck_mutation_mb_math_enabled);
        label_mb_param_g->setObjectName(QString::fromUtf8("label_mb_param_g"));

        gridLayout_mutation_mb_math->addWidget(label_mb_param_g, 3, 2, 1, 1);

        spinbox_mutation_mb_param_g = new MyDoubleSpinBox(groupCheck_mutation_mb_math_enabled);
        spinbox_mutation_mb_param_g->setObjectName(QString::fromUtf8("spinbox_mutation_mb_param_g"));
        spinbox_mutation_mb_param_g->setMinimum(-100.000000000000000);
        spinbox_mutation_mb_param_g->setMaximum(100.000000000000000);
        spinbox_mutation_mb_param_g->setSingleStep(0.100000000000000);
        spinbox_mutation_mb_param_g->setValue(1.000000000000000);
        spinbox_mutation_mb_param_g->setDecimals(6);

        gridLayout_mutation_mb_math->addWidget(spinbox_mutation_mb_param_g, 3, 3, 1, 1);

        label_mb_param_h = new QLabel(groupCheck_mutation_mb_math_enabled);
        label_mb_param_h->setObjectName(QString::fromUtf8("label_mb_param_h"));

        gridLayout_mutation_mb_math->addWidget(label_mb_param_h, 3, 4, 1, 1);

        spinbox_mutation_mb_param_h = new MyDoubleSpinBox(groupCheck_mutation_mb_math_enabled);
        spinbox_mutation_mb_param_h->setObjectName(QString::fromUtf8("spinbox_mutation_mb_param_h"));
        spinbox_mutation_mb_param_h->setMinimum(-100.000000000000000);
        spinbox_mutation_mb_param_h->setMaximum(100.000000000000000);
        spinbox_mutation_mb_param_h->setSingleStep(0.100000000000000);
        spinbox_mutation_mb_param_h->setValue(0.000000000000000);
        spinbox_mutation_mb_param_h->setDecimals(6);

        gridLayout_mutation_mb_math->addWidget(spinbox_mutation_mb_param_h, 3, 5, 1, 1);

        label_mb_iter = new QLabel(groupCheck_mutation_mb_math_enabled);
        label_mb_iter->setObjectName(QString::fromUtf8("label_mb_iter"));

        gridLayout_mutation_mb_math->addWidget(label_mb_iter, 4, 0, 1, 1);

        spinboxInt_mutation_mb_iter_start = new MySpinBox(groupCheck_mutation_mb_math_enabled);
        spinboxInt_mutation_mb_iter_start->setObjectName(QString::fromUtf8("spinboxInt_mutation_mb_iter_start"));
        spinboxInt_mutation_mb_iter_start->setMinimum(0);
        spinboxInt_mutation_mb_iter_start->setMaximum(10000);
        spinboxInt_mutation_mb_iter_start->setValue(0);

        gridLayout_mutation_mb_math->addWidget(spinboxInt_mutation_mb_iter_start, 4, 1, 1, 1);

        label_mb_iter_stop = new QLabel(groupCheck_mutation_mb_math_enabled);
        label_mb_iter_stop->setObjectName(QString::fromUtf8("label_mb_iter_stop"));

        gridLayout_mutation_mb_math->addWidget(label_mb_iter_stop, 4, 2, 1, 1);

        spinboxInt_mutation_mb_iter_stop = new MySpinBox(groupCheck_mutation_mb_math_enabled);
        spinboxInt_mutation_mb_iter_stop->setObjectName(QString::fromUtf8("spinboxInt_mutation_mb_iter_stop"));
        spinboxInt_mutation_mb_iter_stop->setMinimum(0);
        spinboxInt_mutation_mb_iter_stop->setMaximum(10000);
        spinboxInt_mutation_mb_iter_stop->setValue(10000);

        gridLayout_mutation_mb_math->addWidget(spinboxInt_mutation_mb_iter_stop, 4, 3, 1, 1);


        verticalLayout_cMutationSystemsGroup1->addWidget(groupCheck_mutation_mb_math_enabled);

        groupCheck_mutation_warp_dist_enabled = new MyGroupBox(cMutationSystemsGroup1);
        groupCheck_mutation_warp_dist_enabled->setObjectName(QString::fromUtf8("groupCheck_mutation_warp_dist_enabled"));
        groupCheck_mutation_warp_dist_enabled->setCheckable(true);
        groupCheck_mutation_warp_dist_enabled->setChecked(false);
        gridLayout_mutation_warp_dist = new QGridLayout(groupCheck_mutation_warp_dist_enabled);
        gridLayout_mutation_warp_dist->setObjectName(QString::fromUtf8("gridLayout_mutation_warp_dist"));
        label_wd_type = new QLabel(groupCheck_mutation_warp_dist_enabled);
        label_wd_type->setObjectName(QString::fromUtf8("label_wd_type"));

        gridLayout_mutation_warp_dist->addWidget(label_wd_type, 0, 0, 1, 1);

        label1 = new QLabel(groupCheck_mutation_warp_dist_enabled);
        label1->setObjectName(QString::fromUtf8("label1"));
        label1->setAlignment(Qt::AlignCenter);

        gridLayout_mutation_warp_dist->addWidget(label1, 0, 6, 1, 1);

        spinbox_mutation_warp_dist_section_weight = new MyDoubleSpinBox(groupCheck_mutation_warp_dist_enabled);
        spinbox_mutation_warp_dist_section_weight->setObjectName(QString::fromUtf8("spinbox_mutation_warp_dist_section_weight"));
        spinbox_mutation_warp_dist_section_weight->setMinimum(0.000000000000000);
        spinbox_mutation_warp_dist_section_weight->setMaximum(1.000000000000000);
        spinbox_mutation_warp_dist_section_weight->setSingleStep(0.050000000000000);
        spinbox_mutation_warp_dist_section_weight->setValue(1.000000000000000);
        spinbox_mutation_warp_dist_section_weight->setDecimals(2);
        spinbox_mutation_warp_dist_section_weight->setMinimumSize(QSize(60, 0));

        gridLayout_mutation_warp_dist->addWidget(spinbox_mutation_warp_dist_section_weight, 1, 6, 1, 1);

        pushButton_mutation_warp_dist_reset_weights = new QPushButton(groupCheck_mutation_warp_dist_enabled);
        pushButton_mutation_warp_dist_reset_weights->setObjectName(QString::fromUtf8("pushButton_mutation_warp_dist_reset_weights"));
        pushButton_mutation_warp_dist_reset_weights->setMaximumSize(QSize(60, 16777215));

        gridLayout_mutation_warp_dist->addWidget(pushButton_mutation_warp_dist_reset_weights, 2, 6, 1, 1);

        comboBox_mutation_warp_dist_type = new QComboBox(groupCheck_mutation_warp_dist_enabled);
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->addItem(QString());
        comboBox_mutation_warp_dist_type->setObjectName(QString::fromUtf8("comboBox_mutation_warp_dist_type"));

        gridLayout_mutation_warp_dist->addWidget(comboBox_mutation_warp_dist_type, 0, 1, 1, 5);

        label_wd_factor = new QLabel(groupCheck_mutation_warp_dist_enabled);
        label_wd_factor->setObjectName(QString::fromUtf8("label_wd_factor"));

        gridLayout_mutation_warp_dist->addWidget(label_wd_factor, 1, 0, 1, 1);

        spinbox_mutation_wd_factor = new MyDoubleSpinBox(groupCheck_mutation_warp_dist_enabled);
        spinbox_mutation_wd_factor->setObjectName(QString::fromUtf8("spinbox_mutation_wd_factor"));
        spinbox_mutation_wd_factor->setMinimum(-100.000000000000000);
        spinbox_mutation_wd_factor->setMaximum(100.000000000000000);
        spinbox_mutation_wd_factor->setSingleStep(0.100000000000000);
        spinbox_mutation_wd_factor->setValue(1.000000000000000);
        spinbox_mutation_wd_factor->setDecimals(6);

        gridLayout_mutation_warp_dist->addWidget(spinbox_mutation_wd_factor, 1, 1, 1, 1);

        label_wd_param_a = new QLabel(groupCheck_mutation_warp_dist_enabled);
        label_wd_param_a->setObjectName(QString::fromUtf8("label_wd_param_a"));

        gridLayout_mutation_warp_dist->addWidget(label_wd_param_a, 1, 2, 1, 1);

        spinbox_mutation_wd_param_a = new MyDoubleSpinBox(groupCheck_mutation_warp_dist_enabled);
        spinbox_mutation_wd_param_a->setObjectName(QString::fromUtf8("spinbox_mutation_wd_param_a"));
        spinbox_mutation_wd_param_a->setMinimum(-100.000000000000000);
        spinbox_mutation_wd_param_a->setMaximum(100.000000000000000);
        spinbox_mutation_wd_param_a->setSingleStep(0.100000000000000);
        spinbox_mutation_wd_param_a->setValue(1.000000000000000);
        spinbox_mutation_wd_param_a->setDecimals(6);

        gridLayout_mutation_warp_dist->addWidget(spinbox_mutation_wd_param_a, 1, 3, 1, 1);

        label_wd_param_b = new QLabel(groupCheck_mutation_warp_dist_enabled);
        label_wd_param_b->setObjectName(QString::fromUtf8("label_wd_param_b"));

        gridLayout_mutation_warp_dist->addWidget(label_wd_param_b, 1, 4, 1, 1);

        spinbox_mutation_wd_param_b = new MyDoubleSpinBox(groupCheck_mutation_warp_dist_enabled);
        spinbox_mutation_wd_param_b->setObjectName(QString::fromUtf8("spinbox_mutation_wd_param_b"));
        spinbox_mutation_wd_param_b->setMinimum(-100.000000000000000);
        spinbox_mutation_wd_param_b->setMaximum(100.000000000000000);
        spinbox_mutation_wd_param_b->setSingleStep(0.100000000000000);
        spinbox_mutation_wd_param_b->setValue(1.000000000000000);
        spinbox_mutation_wd_param_b->setDecimals(6);

        gridLayout_mutation_warp_dist->addWidget(spinbox_mutation_wd_param_b, 1, 5, 1, 1);

        label_wd_param_c = new QLabel(groupCheck_mutation_warp_dist_enabled);
        label_wd_param_c->setObjectName(QString::fromUtf8("label_wd_param_c"));

        gridLayout_mutation_warp_dist->addWidget(label_wd_param_c, 2, 0, 1, 1);

        spinbox_mutation_wd_param_c = new MyDoubleSpinBox(groupCheck_mutation_warp_dist_enabled);
        spinbox_mutation_wd_param_c->setObjectName(QString::fromUtf8("spinbox_mutation_wd_param_c"));
        spinbox_mutation_wd_param_c->setMinimum(-100.000000000000000);
        spinbox_mutation_wd_param_c->setMaximum(100.000000000000000);
        spinbox_mutation_wd_param_c->setSingleStep(0.100000000000000);
        spinbox_mutation_wd_param_c->setValue(1.000000000000000);
        spinbox_mutation_wd_param_c->setDecimals(6);

        gridLayout_mutation_warp_dist->addWidget(spinbox_mutation_wd_param_c, 2, 1, 1, 1);

        label_wd_param_d = new QLabel(groupCheck_mutation_warp_dist_enabled);
        label_wd_param_d->setObjectName(QString::fromUtf8("label_wd_param_d"));

        gridLayout_mutation_warp_dist->addWidget(label_wd_param_d, 2, 2, 1, 1);

        spinbox_mutation_wd_param_d = new MyDoubleSpinBox(groupCheck_mutation_warp_dist_enabled);
        spinbox_mutation_wd_param_d->setObjectName(QString::fromUtf8("spinbox_mutation_wd_param_d"));
        spinbox_mutation_wd_param_d->setMinimum(-100.000000000000000);
        spinbox_mutation_wd_param_d->setMaximum(100.000000000000000);
        spinbox_mutation_wd_param_d->setSingleStep(0.100000000000000);
        spinbox_mutation_wd_param_d->setValue(1.000000000000000);
        spinbox_mutation_wd_param_d->setDecimals(6);

        gridLayout_mutation_warp_dist->addWidget(spinbox_mutation_wd_param_d, 2, 3, 1, 1);

        label_wd_freq = new QLabel(groupCheck_mutation_warp_dist_enabled);
        label_wd_freq->setObjectName(QString::fromUtf8("label_wd_freq"));

        gridLayout_mutation_warp_dist->addWidget(label_wd_freq, 2, 4, 1, 1);

        spinbox_mutation_wd_freq = new MyDoubleSpinBox(groupCheck_mutation_warp_dist_enabled);
        spinbox_mutation_wd_freq->setObjectName(QString::fromUtf8("spinbox_mutation_wd_freq"));
        spinbox_mutation_wd_freq->setMinimum(0.001000000000000);
        spinbox_mutation_wd_freq->setMaximum(100.000000000000000);
        spinbox_mutation_wd_freq->setSingleStep(0.100000000000000);
        spinbox_mutation_wd_freq->setValue(1.000000000000000);
        spinbox_mutation_wd_freq->setDecimals(6);

        gridLayout_mutation_warp_dist->addWidget(spinbox_mutation_wd_freq, 2, 5, 1, 1);

        label_wd_amp = new QLabel(groupCheck_mutation_warp_dist_enabled);
        label_wd_amp->setObjectName(QString::fromUtf8("label_wd_amp"));

        gridLayout_mutation_warp_dist->addWidget(label_wd_amp, 3, 0, 1, 1);

        spinbox_mutation_wd_amp = new MyDoubleSpinBox(groupCheck_mutation_warp_dist_enabled);
        spinbox_mutation_wd_amp->setObjectName(QString::fromUtf8("spinbox_mutation_wd_amp"));
        spinbox_mutation_wd_amp->setMinimum(-10.000000000000000);
        spinbox_mutation_wd_amp->setMaximum(10.000000000000000);
        spinbox_mutation_wd_amp->setSingleStep(0.010000000000000);
        spinbox_mutation_wd_amp->setValue(0.500000000000000);
        spinbox_mutation_wd_amp->setDecimals(6);

        gridLayout_mutation_warp_dist->addWidget(spinbox_mutation_wd_amp, 3, 1, 1, 1);

        label_wd_scale = new QLabel(groupCheck_mutation_warp_dist_enabled);
        label_wd_scale->setObjectName(QString::fromUtf8("label_wd_scale"));

        gridLayout_mutation_warp_dist->addWidget(label_wd_scale, 3, 2, 1, 1);

        spinbox_mutation_wd_scale = new MyDoubleSpinBox(groupCheck_mutation_warp_dist_enabled);
        spinbox_mutation_wd_scale->setObjectName(QString::fromUtf8("spinbox_mutation_wd_scale"));
        spinbox_mutation_wd_scale->setMinimum(-100.000000000000000);
        spinbox_mutation_wd_scale->setMaximum(100.000000000000000);
        spinbox_mutation_wd_scale->setSingleStep(0.100000000000000);
        spinbox_mutation_wd_scale->setValue(1.000000000000000);
        spinbox_mutation_wd_scale->setDecimals(6);

        gridLayout_mutation_warp_dist->addWidget(spinbox_mutation_wd_scale, 3, 3, 1, 1);

        label_wd_phase = new QLabel(groupCheck_mutation_warp_dist_enabled);
        label_wd_phase->setObjectName(QString::fromUtf8("label_wd_phase"));

        gridLayout_mutation_warp_dist->addWidget(label_wd_phase, 3, 4, 1, 1);

        spinbox_mutation_wd_phase = new MyDoubleSpinBox(groupCheck_mutation_warp_dist_enabled);
        spinbox_mutation_wd_phase->setObjectName(QString::fromUtf8("spinbox_mutation_wd_phase"));
        spinbox_mutation_wd_phase->setMinimum(-360.000000000000000);
        spinbox_mutation_wd_phase->setMaximum(360.000000000000000);
        spinbox_mutation_wd_phase->setSingleStep(1.000000000000000);
        spinbox_mutation_wd_phase->setValue(0.000000000000000);
        spinbox_mutation_wd_phase->setDecimals(3);

        gridLayout_mutation_warp_dist->addWidget(spinbox_mutation_wd_phase, 3, 5, 1, 1);

        label_wd_iter = new QLabel(groupCheck_mutation_warp_dist_enabled);
        label_wd_iter->setObjectName(QString::fromUtf8("label_wd_iter"));

        gridLayout_mutation_warp_dist->addWidget(label_wd_iter, 4, 0, 1, 1);

        spinboxInt_mutation_wd_iter_start = new MySpinBox(groupCheck_mutation_warp_dist_enabled);
        spinboxInt_mutation_wd_iter_start->setObjectName(QString::fromUtf8("spinboxInt_mutation_wd_iter_start"));
        spinboxInt_mutation_wd_iter_start->setMinimum(0);
        spinboxInt_mutation_wd_iter_start->setMaximum(10000);
        spinboxInt_mutation_wd_iter_start->setValue(0);

        gridLayout_mutation_warp_dist->addWidget(spinboxInt_mutation_wd_iter_start, 4, 1, 1, 1);

        label_wd_iter_stop = new QLabel(groupCheck_mutation_warp_dist_enabled);
        label_wd_iter_stop->setObjectName(QString::fromUtf8("label_wd_iter_stop"));

        gridLayout_mutation_warp_dist->addWidget(label_wd_iter_stop, 4, 2, 1, 1);

        spinboxInt_mutation_wd_iter_stop = new MySpinBox(groupCheck_mutation_warp_dist_enabled);
        spinboxInt_mutation_wd_iter_stop->setObjectName(QString::fromUtf8("spinboxInt_mutation_wd_iter_stop"));
        spinboxInt_mutation_wd_iter_stop->setMinimum(0);
        spinboxInt_mutation_wd_iter_stop->setMaximum(10000);
        spinboxInt_mutation_wd_iter_stop->setValue(10000);

        gridLayout_mutation_warp_dist->addWidget(spinboxInt_mutation_wd_iter_stop, 4, 3, 1, 1);


        verticalLayout_cMutationSystemsGroup1->addWidget(groupCheck_mutation_warp_dist_enabled);

        groupCheck_mutation_symmetry_enabled = new MyGroupBox(cMutationSystemsGroup1);
        groupCheck_mutation_symmetry_enabled->setObjectName(QString::fromUtf8("groupCheck_mutation_symmetry_enabled"));
        groupCheck_mutation_symmetry_enabled->setCheckable(true);
        groupCheck_mutation_symmetry_enabled->setChecked(false);
        gridLayout_mutation_symmetry = new QGridLayout(groupCheck_mutation_symmetry_enabled);
        gridLayout_mutation_symmetry->setObjectName(QString::fromUtf8("gridLayout_mutation_symmetry"));
        label_sk_type = new QLabel(groupCheck_mutation_symmetry_enabled);
        label_sk_type->setObjectName(QString::fromUtf8("label_sk_type"));

        gridLayout_mutation_symmetry->addWidget(label_sk_type, 0, 0, 1, 1);

        label2 = new QLabel(groupCheck_mutation_symmetry_enabled);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setAlignment(Qt::AlignCenter);

        gridLayout_mutation_symmetry->addWidget(label2, 0, 6, 1, 1);

        spinbox_mutation_symmetry_section_weight = new MyDoubleSpinBox(groupCheck_mutation_symmetry_enabled);
        spinbox_mutation_symmetry_section_weight->setObjectName(QString::fromUtf8("spinbox_mutation_symmetry_section_weight"));
        spinbox_mutation_symmetry_section_weight->setMinimum(0.000000000000000);
        spinbox_mutation_symmetry_section_weight->setMaximum(1.000000000000000);
        spinbox_mutation_symmetry_section_weight->setSingleStep(0.050000000000000);
        spinbox_mutation_symmetry_section_weight->setValue(1.000000000000000);
        spinbox_mutation_symmetry_section_weight->setDecimals(2);
        spinbox_mutation_symmetry_section_weight->setMinimumSize(QSize(60, 0));

        gridLayout_mutation_symmetry->addWidget(spinbox_mutation_symmetry_section_weight, 1, 6, 1, 1);

        pushButton_mutation_symmetry_reset_weights = new QPushButton(groupCheck_mutation_symmetry_enabled);
        pushButton_mutation_symmetry_reset_weights->setObjectName(QString::fromUtf8("pushButton_mutation_symmetry_reset_weights"));
        pushButton_mutation_symmetry_reset_weights->setMaximumSize(QSize(60, 16777215));

        gridLayout_mutation_symmetry->addWidget(pushButton_mutation_symmetry_reset_weights, 2, 6, 1, 1);

        comboBox_mutation_sym_kal_type = new QComboBox(groupCheck_mutation_symmetry_enabled);
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->addItem(QString());
        comboBox_mutation_sym_kal_type->setObjectName(QString::fromUtf8("comboBox_mutation_sym_kal_type"));

        gridLayout_mutation_symmetry->addWidget(comboBox_mutation_sym_kal_type, 0, 1, 1, 5);

        label_sk_factor = new QLabel(groupCheck_mutation_symmetry_enabled);
        label_sk_factor->setObjectName(QString::fromUtf8("label_sk_factor"));

        gridLayout_mutation_symmetry->addWidget(label_sk_factor, 1, 0, 1, 1);

        spinbox_mutation_sk_factor = new MyDoubleSpinBox(groupCheck_mutation_symmetry_enabled);
        spinbox_mutation_sk_factor->setObjectName(QString::fromUtf8("spinbox_mutation_sk_factor"));
        spinbox_mutation_sk_factor->setMinimum(-100.000000000000000);
        spinbox_mutation_sk_factor->setMaximum(100.000000000000000);
        spinbox_mutation_sk_factor->setSingleStep(0.100000000000000);
        spinbox_mutation_sk_factor->setValue(1.000000000000000);
        spinbox_mutation_sk_factor->setDecimals(6);

        gridLayout_mutation_symmetry->addWidget(spinbox_mutation_sk_factor, 1, 1, 1, 1);

        label_sk_param_a = new QLabel(groupCheck_mutation_symmetry_enabled);
        label_sk_param_a->setObjectName(QString::fromUtf8("label_sk_param_a"));

        gridLayout_mutation_symmetry->addWidget(label_sk_param_a, 1, 2, 1, 1);

        spinbox_mutation_sk_param_a = new MyDoubleSpinBox(groupCheck_mutation_symmetry_enabled);
        spinbox_mutation_sk_param_a->setObjectName(QString::fromUtf8("spinbox_mutation_sk_param_a"));
        spinbox_mutation_sk_param_a->setMinimum(-100.000000000000000);
        spinbox_mutation_sk_param_a->setMaximum(100.000000000000000);
        spinbox_mutation_sk_param_a->setSingleStep(0.100000000000000);
        spinbox_mutation_sk_param_a->setValue(1.000000000000000);
        spinbox_mutation_sk_param_a->setDecimals(6);

        gridLayout_mutation_symmetry->addWidget(spinbox_mutation_sk_param_a, 1, 3, 1, 1);

        label_sk_param_b = new QLabel(groupCheck_mutation_symmetry_enabled);
        label_sk_param_b->setObjectName(QString::fromUtf8("label_sk_param_b"));

        gridLayout_mutation_symmetry->addWidget(label_sk_param_b, 1, 4, 1, 1);

        spinbox_mutation_sk_param_b = new MyDoubleSpinBox(groupCheck_mutation_symmetry_enabled);
        spinbox_mutation_sk_param_b->setObjectName(QString::fromUtf8("spinbox_mutation_sk_param_b"));
        spinbox_mutation_sk_param_b->setMinimum(-100.000000000000000);
        spinbox_mutation_sk_param_b->setMaximum(100.000000000000000);
        spinbox_mutation_sk_param_b->setSingleStep(0.100000000000000);
        spinbox_mutation_sk_param_b->setValue(1.000000000000000);
        spinbox_mutation_sk_param_b->setDecimals(6);

        gridLayout_mutation_symmetry->addWidget(spinbox_mutation_sk_param_b, 1, 5, 1, 1);

        label_sk_param_c = new QLabel(groupCheck_mutation_symmetry_enabled);
        label_sk_param_c->setObjectName(QString::fromUtf8("label_sk_param_c"));

        gridLayout_mutation_symmetry->addWidget(label_sk_param_c, 2, 0, 1, 1);

        spinbox_mutation_sk_param_c = new MyDoubleSpinBox(groupCheck_mutation_symmetry_enabled);
        spinbox_mutation_sk_param_c->setObjectName(QString::fromUtf8("spinbox_mutation_sk_param_c"));
        spinbox_mutation_sk_param_c->setMinimum(-100.000000000000000);
        spinbox_mutation_sk_param_c->setMaximum(100.000000000000000);
        spinbox_mutation_sk_param_c->setSingleStep(0.100000000000000);
        spinbox_mutation_sk_param_c->setValue(1.000000000000000);
        spinbox_mutation_sk_param_c->setDecimals(6);

        gridLayout_mutation_symmetry->addWidget(spinbox_mutation_sk_param_c, 2, 1, 1, 1);

        label_sk_param_d = new QLabel(groupCheck_mutation_symmetry_enabled);
        label_sk_param_d->setObjectName(QString::fromUtf8("label_sk_param_d"));

        gridLayout_mutation_symmetry->addWidget(label_sk_param_d, 2, 2, 1, 1);

        spinbox_mutation_sk_param_d = new MyDoubleSpinBox(groupCheck_mutation_symmetry_enabled);
        spinbox_mutation_sk_param_d->setObjectName(QString::fromUtf8("spinbox_mutation_sk_param_d"));
        spinbox_mutation_sk_param_d->setMinimum(-100.000000000000000);
        spinbox_mutation_sk_param_d->setMaximum(100.000000000000000);
        spinbox_mutation_sk_param_d->setSingleStep(0.100000000000000);
        spinbox_mutation_sk_param_d->setValue(1.000000000000000);
        spinbox_mutation_sk_param_d->setDecimals(6);

        gridLayout_mutation_symmetry->addWidget(spinbox_mutation_sk_param_d, 2, 3, 1, 1);

        label_sk_freq = new QLabel(groupCheck_mutation_symmetry_enabled);
        label_sk_freq->setObjectName(QString::fromUtf8("label_sk_freq"));

        gridLayout_mutation_symmetry->addWidget(label_sk_freq, 2, 4, 1, 1);

        spinbox_mutation_sk_freq = new MyDoubleSpinBox(groupCheck_mutation_symmetry_enabled);
        spinbox_mutation_sk_freq->setObjectName(QString::fromUtf8("spinbox_mutation_sk_freq"));
        spinbox_mutation_sk_freq->setMinimum(0.001000000000000);
        spinbox_mutation_sk_freq->setMaximum(100.000000000000000);
        spinbox_mutation_sk_freq->setSingleStep(0.100000000000000);
        spinbox_mutation_sk_freq->setValue(1.000000000000000);
        spinbox_mutation_sk_freq->setDecimals(6);

        gridLayout_mutation_symmetry->addWidget(spinbox_mutation_sk_freq, 2, 5, 1, 1);

        label_sk_amp = new QLabel(groupCheck_mutation_symmetry_enabled);
        label_sk_amp->setObjectName(QString::fromUtf8("label_sk_amp"));

        gridLayout_mutation_symmetry->addWidget(label_sk_amp, 3, 0, 1, 1);

        spinbox_mutation_sk_amp = new MyDoubleSpinBox(groupCheck_mutation_symmetry_enabled);
        spinbox_mutation_sk_amp->setObjectName(QString::fromUtf8("spinbox_mutation_sk_amp"));
        spinbox_mutation_sk_amp->setMinimum(-10.000000000000000);
        spinbox_mutation_sk_amp->setMaximum(10.000000000000000);
        spinbox_mutation_sk_amp->setSingleStep(0.010000000000000);
        spinbox_mutation_sk_amp->setValue(0.500000000000000);
        spinbox_mutation_sk_amp->setDecimals(6);

        gridLayout_mutation_symmetry->addWidget(spinbox_mutation_sk_amp, 3, 1, 1, 1);

        label_sk_angle = new QLabel(groupCheck_mutation_symmetry_enabled);
        label_sk_angle->setObjectName(QString::fromUtf8("label_sk_angle"));

        gridLayout_mutation_symmetry->addWidget(label_sk_angle, 3, 2, 1, 1);

        spinbox_mutation_sk_angle = new MyDoubleSpinBox(groupCheck_mutation_symmetry_enabled);
        spinbox_mutation_sk_angle->setObjectName(QString::fromUtf8("spinbox_mutation_sk_angle"));
        spinbox_mutation_sk_angle->setMinimum(0.000000000000000);
        spinbox_mutation_sk_angle->setMaximum(360.000000000000000);
        spinbox_mutation_sk_angle->setSingleStep(1.000000000000000);
        spinbox_mutation_sk_angle->setValue(60.000000000000000);
        spinbox_mutation_sk_angle->setDecimals(3);

        gridLayout_mutation_symmetry->addWidget(spinbox_mutation_sk_angle, 3, 3, 1, 1);

        label_sk_offset = new QLabel(groupCheck_mutation_symmetry_enabled);
        label_sk_offset->setObjectName(QString::fromUtf8("label_sk_offset"));

        gridLayout_mutation_symmetry->addWidget(label_sk_offset, 3, 4, 1, 1);

        spinbox_mutation_sk_offset = new MyDoubleSpinBox(groupCheck_mutation_symmetry_enabled);
        spinbox_mutation_sk_offset->setObjectName(QString::fromUtf8("spinbox_mutation_sk_offset"));
        spinbox_mutation_sk_offset->setMinimum(-100.000000000000000);
        spinbox_mutation_sk_offset->setMaximum(100.000000000000000);
        spinbox_mutation_sk_offset->setSingleStep(0.100000000000000);
        spinbox_mutation_sk_offset->setValue(0.000000000000000);
        spinbox_mutation_sk_offset->setDecimals(6);

        gridLayout_mutation_symmetry->addWidget(spinbox_mutation_sk_offset, 3, 5, 1, 1);

        label_sk_iter = new QLabel(groupCheck_mutation_symmetry_enabled);
        label_sk_iter->setObjectName(QString::fromUtf8("label_sk_iter"));

        gridLayout_mutation_symmetry->addWidget(label_sk_iter, 4, 0, 1, 1);

        spinboxInt_mutation_sk_iter_start = new MySpinBox(groupCheck_mutation_symmetry_enabled);
        spinboxInt_mutation_sk_iter_start->setObjectName(QString::fromUtf8("spinboxInt_mutation_sk_iter_start"));
        spinboxInt_mutation_sk_iter_start->setMinimum(0);
        spinboxInt_mutation_sk_iter_start->setMaximum(10000);
        spinboxInt_mutation_sk_iter_start->setValue(0);

        gridLayout_mutation_symmetry->addWidget(spinboxInt_mutation_sk_iter_start, 4, 1, 1, 1);

        label_sk_iter_stop = new QLabel(groupCheck_mutation_symmetry_enabled);
        label_sk_iter_stop->setObjectName(QString::fromUtf8("label_sk_iter_stop"));

        gridLayout_mutation_symmetry->addWidget(label_sk_iter_stop, 4, 2, 1, 1);

        spinboxInt_mutation_sk_iter_stop = new MySpinBox(groupCheck_mutation_symmetry_enabled);
        spinboxInt_mutation_sk_iter_stop->setObjectName(QString::fromUtf8("spinboxInt_mutation_sk_iter_stop"));
        spinboxInt_mutation_sk_iter_stop->setMinimum(0);
        spinboxInt_mutation_sk_iter_stop->setMaximum(10000);
        spinboxInt_mutation_sk_iter_stop->setValue(10000);

        gridLayout_mutation_symmetry->addWidget(spinboxInt_mutation_sk_iter_stop, 4, 3, 1, 1);


        verticalLayout_cMutationSystemsGroup1->addWidget(groupCheck_mutation_symmetry_enabled);


        retranslateUi(cMutationSystemsGroup1);

        QMetaObject::connectSlotsByName(cMutationSystemsGroup1);
    } // setupUi

    void retranslateUi(QWidget *cMutationSystemsGroup1)
    {
        groupCheck_mutation_mb_math_enabled->setTitle(QCoreApplication::translate("cMutationSystemsGroup1", "Mandelbox Math System", nullptr));
        label_mb_math_type->setText(QCoreApplication::translate("cMutationSystemsGroup1", "Mandelbox Math Type:", nullptr));
        label->setText(QCoreApplication::translate("cMutationSystemsGroup1", "Weight", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_mutation_mb_math_section_weight->setToolTip(QCoreApplication::translate("cMutationSystemsGroup1", "Section weight: 1=full effect, 0=off", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_mutation_mb_math_reset_weights->setText(QCoreApplication::translate("cMutationSystemsGroup1", "Reset", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_mutation_mb_math_reset_weights->setToolTip(QCoreApplication::translate("cMutationSystemsGroup1", "Reset this section's weights to 1.0", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_mutation_mb_math_type->setItemText(0, QCoreApplication::translate("cMutationSystemsGroup1", "None", nullptr));
        comboBox_mutation_mb_math_type->setItemText(1, QCoreApplication::translate("cMutationSystemsGroup1", "Box Fold (Custom Limits)", nullptr));
        comboBox_mutation_mb_math_type->setItemText(2, QCoreApplication::translate("cMutationSystemsGroup1", "Spherical Fold (Custom Radii)", nullptr));
        comboBox_mutation_mb_math_type->setItemText(3, QCoreApplication::translate("cMutationSystemsGroup1", "Rotational Fold", nullptr));
        comboBox_mutation_mb_math_type->setItemText(4, QCoreApplication::translate("cMutationSystemsGroup1", "Shear Fold", nullptr));
        comboBox_mutation_mb_math_type->setItemText(5, QCoreApplication::translate("cMutationSystemsGroup1", "Scaling Oscillation", nullptr));
        comboBox_mutation_mb_math_type->setItemText(6, QCoreApplication::translate("cMutationSystemsGroup1", "Adaptive Box Fold", nullptr));
        comboBox_mutation_mb_math_type->setItemText(7, QCoreApplication::translate("cMutationSystemsGroup1", "Conditional Abs Fold", nullptr));
        comboBox_mutation_mb_math_type->setItemText(8, QCoreApplication::translate("cMutationSystemsGroup1", "Smooth Box Fold", nullptr));
        comboBox_mutation_mb_math_type->setItemText(9, QCoreApplication::translate("cMutationSystemsGroup1", "Power Box Fold", nullptr));
        comboBox_mutation_mb_math_type->setItemText(10, QCoreApplication::translate("cMutationSystemsGroup1", "Exponential Fold", nullptr));
        comboBox_mutation_mb_math_type->setItemText(11, QCoreApplication::translate("cMutationSystemsGroup1", "Tanh Fold", nullptr));
        comboBox_mutation_mb_math_type->setItemText(12, QCoreApplication::translate("cMutationSystemsGroup1", "Sin-Cos Fold", nullptr));
        comboBox_mutation_mb_math_type->setItemText(13, QCoreApplication::translate("cMutationSystemsGroup1", "Spiral Fold", nullptr));
        comboBox_mutation_mb_math_type->setItemText(14, QCoreApplication::translate("cMutationSystemsGroup1", "Twist Fold", nullptr));
        comboBox_mutation_mb_math_type->setItemText(15, QCoreApplication::translate("cMutationSystemsGroup1", "Stretch Fold", nullptr));
        comboBox_mutation_mb_math_type->setItemText(16, QCoreApplication::translate("cMutationSystemsGroup1", "Compress Fold", nullptr));
        comboBox_mutation_mb_math_type->setItemText(17, QCoreApplication::translate("cMutationSystemsGroup1", "Mirror Fold", nullptr));
        comboBox_mutation_mb_math_type->setItemText(18, QCoreApplication::translate("cMutationSystemsGroup1", "Kaleidoscope Fold", nullptr));
        comboBox_mutation_mb_math_type->setItemText(19, QCoreApplication::translate("cMutationSystemsGroup1", "Menger Fold", nullptr));
        comboBox_mutation_mb_math_type->setItemText(20, QCoreApplication::translate("cMutationSystemsGroup1", "Sierpinski Fold", nullptr));
        comboBox_mutation_mb_math_type->setItemText(21, QCoreApplication::translate("cMutationSystemsGroup1", "Koch Fold", nullptr));
        comboBox_mutation_mb_math_type->setItemText(22, QCoreApplication::translate("cMutationSystemsGroup1", "Cantor Fold", nullptr));
        comboBox_mutation_mb_math_type->setItemText(23, QCoreApplication::translate("cMutationSystemsGroup1", "Julia Fold", nullptr));
        comboBox_mutation_mb_math_type->setItemText(24, QCoreApplication::translate("cMutationSystemsGroup1", "Newton Fold", nullptr));
        comboBox_mutation_mb_math_type->setItemText(25, QCoreApplication::translate("cMutationSystemsGroup1", "Halley Fold", nullptr));
        comboBox_mutation_mb_math_type->setItemText(26, QCoreApplication::translate("cMutationSystemsGroup1", "Laguerre Fold", nullptr));
        comboBox_mutation_mb_math_type->setItemText(27, QCoreApplication::translate("cMutationSystemsGroup1", "Durand-Kerner Fold", nullptr));
        comboBox_mutation_mb_math_type->setItemText(28, QCoreApplication::translate("cMutationSystemsGroup1", "Bairstow Fold", nullptr));
        comboBox_mutation_mb_math_type->setItemText(29, QCoreApplication::translate("cMutationSystemsGroup1", "Aberth Fold", nullptr));
        comboBox_mutation_mb_math_type->setItemText(30, QCoreApplication::translate("cMutationSystemsGroup1", "Jenkins-Traub Fold", nullptr));

        label_mb_factor->setText(QCoreApplication::translate("cMutationSystemsGroup1", "Factor:", nullptr));
        label_mb_param_a->setText(QCoreApplication::translate("cMutationSystemsGroup1", "A:", nullptr));
        label_mb_param_b->setText(QCoreApplication::translate("cMutationSystemsGroup1", "B:", nullptr));
        label_mb_param_c->setText(QCoreApplication::translate("cMutationSystemsGroup1", "C:", nullptr));
        label_mb_param_d->setText(QCoreApplication::translate("cMutationSystemsGroup1", "D:", nullptr));
        label_mb_param_e->setText(QCoreApplication::translate("cMutationSystemsGroup1", "E:", nullptr));
        label_mb_param_f->setText(QCoreApplication::translate("cMutationSystemsGroup1", "F:", nullptr));
        label_mb_param_g->setText(QCoreApplication::translate("cMutationSystemsGroup1", "G:", nullptr));
        label_mb_param_h->setText(QCoreApplication::translate("cMutationSystemsGroup1", "H:", nullptr));
        label_mb_iter->setText(QCoreApplication::translate("cMutationSystemsGroup1", "MB Iter:", nullptr));
        label_mb_iter_stop->setText(QCoreApplication::translate("cMutationSystemsGroup1", "Stop:", nullptr));
        groupCheck_mutation_warp_dist_enabled->setTitle(QCoreApplication::translate("cMutationSystemsGroup1", "Warp Distortion System", nullptr));
        label_wd_type->setText(QCoreApplication::translate("cMutationSystemsGroup1", "Warp Distortion Type:", nullptr));
        label1->setText(QCoreApplication::translate("cMutationSystemsGroup1", "Weight", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_mutation_warp_dist_section_weight->setToolTip(QCoreApplication::translate("cMutationSystemsGroup1", "Section weight: 1=full effect, 0=off", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_mutation_warp_dist_reset_weights->setText(QCoreApplication::translate("cMutationSystemsGroup1", "Reset", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_mutation_warp_dist_reset_weights->setToolTip(QCoreApplication::translate("cMutationSystemsGroup1", "Reset this section's weights to 1.0", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_mutation_warp_dist_type->setItemText(0, QCoreApplication::translate("cMutationSystemsGroup1", "None", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(1, QCoreApplication::translate("cMutationSystemsGroup1", "Sine X (Y-driven)", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(2, QCoreApplication::translate("cMutationSystemsGroup1", "Sine Y (Z-driven)", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(3, QCoreApplication::translate("cMutationSystemsGroup1", "Sine Z (X-driven)", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(4, QCoreApplication::translate("cMutationSystemsGroup1", "3D Sine (all axes)", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(5, QCoreApplication::translate("cMutationSystemsGroup1", "Cos-Sin Cross", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(6, QCoreApplication::translate("cMutationSystemsGroup1", "Polar Warp", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(7, QCoreApplication::translate("cMutationSystemsGroup1", "Spherical Warp", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(8, QCoreApplication::translate("cMutationSystemsGroup1", "Curl Warp (3D)", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(9, QCoreApplication::translate("cMutationSystemsGroup1", "Per-Axis Sine", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(10, QCoreApplication::translate("cMutationSystemsGroup1", "Radial Pulse", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(11, QCoreApplication::translate("cMutationSystemsGroup1", "Nested Sine", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(12, QCoreApplication::translate("cMutationSystemsGroup1", "Nested Cos-Sine", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(13, QCoreApplication::translate("cMutationSystemsGroup1", "Nested Sin-Cos", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(14, QCoreApplication::translate("cMutationSystemsGroup1", "Compound Double", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(15, QCoreApplication::translate("cMutationSystemsGroup1", "Cross-Product Sine", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(16, QCoreApplication::translate("cMutationSystemsGroup1", "Recursive Noise", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(17, QCoreApplication::translate("cMutationSystemsGroup1", "Cross-Trig 3D", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(18, QCoreApplication::translate("cMutationSystemsGroup1", "Ratio Sine", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(19, QCoreApplication::translate("cMutationSystemsGroup1", "Spherical Multi-Axis", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(20, QCoreApplication::translate("cMutationSystemsGroup1", "Feedback Sum", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(21, QCoreApplication::translate("cMutationSystemsGroup1", "Fractal Noise X (4-oct)", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(22, QCoreApplication::translate("cMutationSystemsGroup1", "Fractal Noise Y (4-oct)", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(23, QCoreApplication::translate("cMutationSystemsGroup1", "Fractal Noise Z (4-oct)", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(24, QCoreApplication::translate("cMutationSystemsGroup1", "Fractal Noise 3D", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(25, QCoreApplication::translate("cMutationSystemsGroup1", "Custom Octave 3D", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(26, QCoreApplication::translate("cMutationSystemsGroup1", "Turbulence X", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(27, QCoreApplication::translate("cMutationSystemsGroup1", "Turbulence Y", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(28, QCoreApplication::translate("cMutationSystemsGroup1", "Turbulence Z", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(29, QCoreApplication::translate("cMutationSystemsGroup1", "Turbulence 3D", nullptr));
        comboBox_mutation_warp_dist_type->setItemText(30, QCoreApplication::translate("cMutationSystemsGroup1", "Ridged Noise", nullptr));

        label_wd_factor->setText(QCoreApplication::translate("cMutationSystemsGroup1", "Factor:", nullptr));
        label_wd_param_a->setText(QCoreApplication::translate("cMutationSystemsGroup1", "A:", nullptr));
        label_wd_param_b->setText(QCoreApplication::translate("cMutationSystemsGroup1", "B:", nullptr));
        label_wd_param_c->setText(QCoreApplication::translate("cMutationSystemsGroup1", "C:", nullptr));
        label_wd_param_d->setText(QCoreApplication::translate("cMutationSystemsGroup1", "D:", nullptr));
        label_wd_freq->setText(QCoreApplication::translate("cMutationSystemsGroup1", "Freq:", nullptr));
        label_wd_amp->setText(QCoreApplication::translate("cMutationSystemsGroup1", "Amp:", nullptr));
        label_wd_scale->setText(QCoreApplication::translate("cMutationSystemsGroup1", "Scale:", nullptr));
        label_wd_phase->setText(QCoreApplication::translate("cMutationSystemsGroup1", "Phase:", nullptr));
        label_wd_iter->setText(QCoreApplication::translate("cMutationSystemsGroup1", "WD Iter:", nullptr));
        label_wd_iter_stop->setText(QCoreApplication::translate("cMutationSystemsGroup1", "Stop:", nullptr));
        groupCheck_mutation_symmetry_enabled->setTitle(QCoreApplication::translate("cMutationSystemsGroup1", "Symmetry / Kaleidoscope", nullptr));
        label_sk_type->setText(QCoreApplication::translate("cMutationSystemsGroup1", "Symmetry Type:", nullptr));
        label2->setText(QCoreApplication::translate("cMutationSystemsGroup1", "Weight", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_mutation_symmetry_section_weight->setToolTip(QCoreApplication::translate("cMutationSystemsGroup1", "Section weight: 1=full effect, 0=off", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_mutation_symmetry_reset_weights->setText(QCoreApplication::translate("cMutationSystemsGroup1", "Reset", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_mutation_symmetry_reset_weights->setToolTip(QCoreApplication::translate("cMutationSystemsGroup1", "Reset this section's weights to 1.0", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_mutation_sym_kal_type->setItemText(0, QCoreApplication::translate("cMutationSystemsGroup1", "None", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(1, QCoreApplication::translate("cMutationSystemsGroup1", "Abs X", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(2, QCoreApplication::translate("cMutationSystemsGroup1", "Abs Y", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(3, QCoreApplication::translate("cMutationSystemsGroup1", "Abs Z", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(4, QCoreApplication::translate("cMutationSystemsGroup1", "Abs XY", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(5, QCoreApplication::translate("cMutationSystemsGroup1", "Abs XZ", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(6, QCoreApplication::translate("cMutationSystemsGroup1", "Abs YZ", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(7, QCoreApplication::translate("cMutationSystemsGroup1", "Abs XYZ", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(8, QCoreApplication::translate("cMutationSystemsGroup1", "Min-Max Swap XY", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(9, QCoreApplication::translate("cMutationSystemsGroup1", "Min-Max Swap XZ", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(10, QCoreApplication::translate("cMutationSystemsGroup1", "Min-Max Swap YZ", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(11, QCoreApplication::translate("cMutationSystemsGroup1", "Cyclic Sort", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(12, QCoreApplication::translate("cMutationSystemsGroup1", "Reverse Sort", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(13, QCoreApplication::translate("cMutationSystemsGroup1", "Sign Flip X", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(14, QCoreApplication::translate("cMutationSystemsGroup1", "Sign Flip Y", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(15, QCoreApplication::translate("cMutationSystemsGroup1", "Sign Flip Z", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(16, QCoreApplication::translate("cMutationSystemsGroup1", "Rotation 90\302\260 XY", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(17, QCoreApplication::translate("cMutationSystemsGroup1", "Rotation 90\302\260 XZ", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(18, QCoreApplication::translate("cMutationSystemsGroup1", "Rotation 90\302\260 YZ", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(19, QCoreApplication::translate("cMutationSystemsGroup1", "Mirror X=Y", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(20, QCoreApplication::translate("cMutationSystemsGroup1", "Mirror X=Z", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(21, QCoreApplication::translate("cMutationSystemsGroup1", "Mirror Y=Z", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(22, QCoreApplication::translate("cMutationSystemsGroup1", "N-Fold (Z-axis)", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(23, QCoreApplication::translate("cMutationSystemsGroup1", "Tetrahedral", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(24, QCoreApplication::translate("cMutationSystemsGroup1", "Octahedral", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(25, QCoreApplication::translate("cMutationSystemsGroup1", "Icosahedral", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(26, QCoreApplication::translate("cMutationSystemsGroup1", "Cubic Mirror", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(27, QCoreApplication::translate("cMutationSystemsGroup1", "Hexagonal", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(28, QCoreApplication::translate("cMutationSystemsGroup1", "Pentagonal", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(29, QCoreApplication::translate("cMutationSystemsGroup1", "Triangular", nullptr));
        comboBox_mutation_sym_kal_type->setItemText(30, QCoreApplication::translate("cMutationSystemsGroup1", "Diamond", nullptr));

        label_sk_factor->setText(QCoreApplication::translate("cMutationSystemsGroup1", "Factor:", nullptr));
        label_sk_param_a->setText(QCoreApplication::translate("cMutationSystemsGroup1", "A:", nullptr));
        label_sk_param_b->setText(QCoreApplication::translate("cMutationSystemsGroup1", "B:", nullptr));
        label_sk_param_c->setText(QCoreApplication::translate("cMutationSystemsGroup1", "C:", nullptr));
        label_sk_param_d->setText(QCoreApplication::translate("cMutationSystemsGroup1", "D:", nullptr));
        label_sk_freq->setText(QCoreApplication::translate("cMutationSystemsGroup1", "Freq:", nullptr));
        label_sk_amp->setText(QCoreApplication::translate("cMutationSystemsGroup1", "Amp:", nullptr));
        label_sk_angle->setText(QCoreApplication::translate("cMutationSystemsGroup1", "Angle:", nullptr));
        label_sk_offset->setText(QCoreApplication::translate("cMutationSystemsGroup1", "Offset:", nullptr));
        label_sk_iter->setText(QCoreApplication::translate("cMutationSystemsGroup1", "SK Iter:", nullptr));
        label_sk_iter_stop->setText(QCoreApplication::translate("cMutationSystemsGroup1", "Stop:", nullptr));
        (void)cMutationSystemsGroup1;
    } // retranslateUi

};

namespace Ui {
    class cMutationSystemsGroup1: public Ui_cMutationSystemsGroup1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUTATION_SYSTEMS_GROUP1_H
