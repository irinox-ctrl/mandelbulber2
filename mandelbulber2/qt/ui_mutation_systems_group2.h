/********************************************************************************
** Form generated from reading UI file 'mutation_systems_group2.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUTATION_SYSTEMS_GROUP2_H
#define UI_MUTATION_SYSTEMS_GROUP2_H

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

class Ui_cMutationSystemsGroup2
{
public:
    QVBoxLayout *verticalLayout_cMutationSystemsGroup2;
    MyGroupBox *groupCheck_mutation_abox_enabled;
    QGridLayout *gridLayout_mutation_abox;
    QLabel *label_ab_type;
    QLabel *label;
    MyDoubleSpinBox *spinbox_mutation_abox_section_weight;
    QPushButton *pushButton_mutation_abox_reset_weights;
    QComboBox *comboBox_mutation_abox_type;
    QLabel *label_ab_factor;
    MyDoubleSpinBox *spinbox_mutation_ab_factor;
    QLabel *label_ab_param_a;
    MyDoubleSpinBox *spinbox_mutation_ab_param_a;
    QLabel *label_ab_param_b;
    MyDoubleSpinBox *spinbox_mutation_ab_param_b;
    QLabel *label_ab_param_c;
    MyDoubleSpinBox *spinbox_mutation_ab_param_c;
    QLabel *label_ab_param_d;
    MyDoubleSpinBox *spinbox_mutation_ab_param_d;
    QLabel *label_ab_param_e;
    MyDoubleSpinBox *spinbox_mutation_ab_param_e;
    QLabel *label_ab_param_f;
    MyDoubleSpinBox *spinbox_mutation_ab_param_f;
    QLabel *label_ab_param_g;
    MyDoubleSpinBox *spinbox_mutation_ab_param_g;
    QLabel *label_ab_param_h;
    MyDoubleSpinBox *spinbox_mutation_ab_param_h;
    QLabel *label_ab_iter;
    MySpinBox *spinboxInt_mutation_ab_iter_start;
    QLabel *label_ab_iter_stop;
    MySpinBox *spinboxInt_mutation_ab_iter_stop;
    MyGroupBox *groupCheck_mutation_noise_enabled;
    QGridLayout *gridLayout_mutation_noise;
    QLabel *label_noise_type;
    QLabel *label1;
    MyDoubleSpinBox *spinbox_mutation_noise_section_weight;
    QPushButton *pushButton_mutation_noise_reset_weights;
    QComboBox *comboBox_mutation_noise_type;
    QLabel *label_noise_factor;
    MyDoubleSpinBox *spinbox_mutation_noise_factor;
    QLabel *label_noise_param_a;
    MyDoubleSpinBox *spinbox_mutation_noise_param_a;
    QLabel *label_noise_param_b;
    MyDoubleSpinBox *spinbox_mutation_noise_param_b;
    QLabel *label_noise_param_c;
    MyDoubleSpinBox *spinbox_mutation_noise_param_c;
    QLabel *label_noise_param_d;
    MyDoubleSpinBox *spinbox_mutation_noise_param_d;
    QLabel *label_julia_noise_freq;
    MyDoubleSpinBox *spinbox_mutation_noise_freq;
    QLabel *label_julia_noise_amp;
    MyDoubleSpinBox *spinbox_mutation_noise_amp;
    QLabel *label_noise_iter;
    MySpinBox *spinboxInt_mutation_noise_iter_start;
    QLabel *label_noise_iter_stop;
    MySpinBox *spinboxInt_mutation_noise_iter_stop;
    MyGroupBox *groupCheck_mutation_orbit_trap_enabled;
    QGridLayout *gridLayout_mutation_orbit_trap;
    QLabel *label_orbit_type;
    QLabel *label2;
    MyDoubleSpinBox *spinbox_mutation_orbit_trap_section_weight;
    QPushButton *pushButton_mutation_orbit_trap_reset_weights;
    QComboBox *comboBox_mutation_orbit_trap_type;
    QLabel *label_orbit_factor;
    MyDoubleSpinBox *spinbox_mutation_orbit_factor;
    QLabel *label_orbit_param_a;
    MyDoubleSpinBox *spinbox_mutation_orbit_param_a;
    QLabel *label_orbit_param_b;
    MyDoubleSpinBox *spinbox_mutation_orbit_param_b;
    QLabel *label_orbit_param_c;
    MyDoubleSpinBox *spinbox_mutation_orbit_param_c;
    QLabel *label_orbit_param_d;
    MyDoubleSpinBox *spinbox_mutation_orbit_param_d;
    QLabel *label_orbit_iter;
    MySpinBox *spinboxInt_mutation_orbit_iter_start;
    QLabel *label_orbit_iter_stop2;
    MySpinBox *spinboxInt_mutation_orbit_iter_stop;

    void setupUi(QWidget *cMutationSystemsGroup2)
    {
        if (cMutationSystemsGroup2->objectName().isEmpty())
            cMutationSystemsGroup2->setObjectName(QString::fromUtf8("cMutationSystemsGroup2"));
        verticalLayout_cMutationSystemsGroup2 = new QVBoxLayout(cMutationSystemsGroup2);
        verticalLayout_cMutationSystemsGroup2->setSpacing(2);
        verticalLayout_cMutationSystemsGroup2->setObjectName(QString::fromUtf8("verticalLayout_cMutationSystemsGroup2"));
        verticalLayout_cMutationSystemsGroup2->setContentsMargins(0, 0, 0, 0);
        groupCheck_mutation_abox_enabled = new MyGroupBox(cMutationSystemsGroup2);
        groupCheck_mutation_abox_enabled->setObjectName(QString::fromUtf8("groupCheck_mutation_abox_enabled"));
        groupCheck_mutation_abox_enabled->setCheckable(true);
        groupCheck_mutation_abox_enabled->setChecked(false);
        gridLayout_mutation_abox = new QGridLayout(groupCheck_mutation_abox_enabled);
        gridLayout_mutation_abox->setObjectName(QString::fromUtf8("gridLayout_mutation_abox"));
        label_ab_type = new QLabel(groupCheck_mutation_abox_enabled);
        label_ab_type->setObjectName(QString::fromUtf8("label_ab_type"));

        gridLayout_mutation_abox->addWidget(label_ab_type, 0, 0, 1, 1);

        label = new QLabel(groupCheck_mutation_abox_enabled);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout_mutation_abox->addWidget(label, 0, 6, 1, 1);

        spinbox_mutation_abox_section_weight = new MyDoubleSpinBox(groupCheck_mutation_abox_enabled);
        spinbox_mutation_abox_section_weight->setObjectName(QString::fromUtf8("spinbox_mutation_abox_section_weight"));
        spinbox_mutation_abox_section_weight->setMinimum(0.000000000000000);
        spinbox_mutation_abox_section_weight->setMaximum(1.000000000000000);
        spinbox_mutation_abox_section_weight->setSingleStep(0.050000000000000);
        spinbox_mutation_abox_section_weight->setValue(1.000000000000000);
        spinbox_mutation_abox_section_weight->setDecimals(2);
        spinbox_mutation_abox_section_weight->setMinimumSize(QSize(60, 0));

        gridLayout_mutation_abox->addWidget(spinbox_mutation_abox_section_weight, 1, 6, 1, 1);

        pushButton_mutation_abox_reset_weights = new QPushButton(groupCheck_mutation_abox_enabled);
        pushButton_mutation_abox_reset_weights->setObjectName(QString::fromUtf8("pushButton_mutation_abox_reset_weights"));
        pushButton_mutation_abox_reset_weights->setMaximumSize(QSize(60, 16777215));

        gridLayout_mutation_abox->addWidget(pushButton_mutation_abox_reset_weights, 2, 6, 1, 1);

        comboBox_mutation_abox_type = new QComboBox(groupCheck_mutation_abox_enabled);
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->addItem(QString());
        comboBox_mutation_abox_type->setObjectName(QString::fromUtf8("comboBox_mutation_abox_type"));

        gridLayout_mutation_abox->addWidget(comboBox_mutation_abox_type, 0, 1, 1, 5);

        label_ab_factor = new QLabel(groupCheck_mutation_abox_enabled);
        label_ab_factor->setObjectName(QString::fromUtf8("label_ab_factor"));

        gridLayout_mutation_abox->addWidget(label_ab_factor, 1, 0, 1, 1);

        spinbox_mutation_ab_factor = new MyDoubleSpinBox(groupCheck_mutation_abox_enabled);
        spinbox_mutation_ab_factor->setObjectName(QString::fromUtf8("spinbox_mutation_ab_factor"));
        spinbox_mutation_ab_factor->setMinimum(-100.000000000000000);
        spinbox_mutation_ab_factor->setMaximum(100.000000000000000);
        spinbox_mutation_ab_factor->setSingleStep(0.100000000000000);
        spinbox_mutation_ab_factor->setValue(1.000000000000000);
        spinbox_mutation_ab_factor->setDecimals(6);

        gridLayout_mutation_abox->addWidget(spinbox_mutation_ab_factor, 1, 1, 1, 1);

        label_ab_param_a = new QLabel(groupCheck_mutation_abox_enabled);
        label_ab_param_a->setObjectName(QString::fromUtf8("label_ab_param_a"));

        gridLayout_mutation_abox->addWidget(label_ab_param_a, 1, 2, 1, 1);

        spinbox_mutation_ab_param_a = new MyDoubleSpinBox(groupCheck_mutation_abox_enabled);
        spinbox_mutation_ab_param_a->setObjectName(QString::fromUtf8("spinbox_mutation_ab_param_a"));
        spinbox_mutation_ab_param_a->setMinimum(-100.000000000000000);
        spinbox_mutation_ab_param_a->setMaximum(100.000000000000000);
        spinbox_mutation_ab_param_a->setSingleStep(0.100000000000000);
        spinbox_mutation_ab_param_a->setValue(1.000000000000000);
        spinbox_mutation_ab_param_a->setDecimals(6);

        gridLayout_mutation_abox->addWidget(spinbox_mutation_ab_param_a, 1, 3, 1, 1);

        label_ab_param_b = new QLabel(groupCheck_mutation_abox_enabled);
        label_ab_param_b->setObjectName(QString::fromUtf8("label_ab_param_b"));

        gridLayout_mutation_abox->addWidget(label_ab_param_b, 1, 4, 1, 1);

        spinbox_mutation_ab_param_b = new MyDoubleSpinBox(groupCheck_mutation_abox_enabled);
        spinbox_mutation_ab_param_b->setObjectName(QString::fromUtf8("spinbox_mutation_ab_param_b"));
        spinbox_mutation_ab_param_b->setMinimum(-100.000000000000000);
        spinbox_mutation_ab_param_b->setMaximum(100.000000000000000);
        spinbox_mutation_ab_param_b->setSingleStep(0.100000000000000);
        spinbox_mutation_ab_param_b->setValue(1.000000000000000);
        spinbox_mutation_ab_param_b->setDecimals(6);

        gridLayout_mutation_abox->addWidget(spinbox_mutation_ab_param_b, 1, 5, 1, 1);

        label_ab_param_c = new QLabel(groupCheck_mutation_abox_enabled);
        label_ab_param_c->setObjectName(QString::fromUtf8("label_ab_param_c"));

        gridLayout_mutation_abox->addWidget(label_ab_param_c, 2, 0, 1, 1);

        spinbox_mutation_ab_param_c = new MyDoubleSpinBox(groupCheck_mutation_abox_enabled);
        spinbox_mutation_ab_param_c->setObjectName(QString::fromUtf8("spinbox_mutation_ab_param_c"));
        spinbox_mutation_ab_param_c->setMinimum(-100.000000000000000);
        spinbox_mutation_ab_param_c->setMaximum(100.000000000000000);
        spinbox_mutation_ab_param_c->setSingleStep(0.100000000000000);
        spinbox_mutation_ab_param_c->setValue(1.000000000000000);
        spinbox_mutation_ab_param_c->setDecimals(6);

        gridLayout_mutation_abox->addWidget(spinbox_mutation_ab_param_c, 2, 1, 1, 1);

        label_ab_param_d = new QLabel(groupCheck_mutation_abox_enabled);
        label_ab_param_d->setObjectName(QString::fromUtf8("label_ab_param_d"));

        gridLayout_mutation_abox->addWidget(label_ab_param_d, 2, 2, 1, 1);

        spinbox_mutation_ab_param_d = new MyDoubleSpinBox(groupCheck_mutation_abox_enabled);
        spinbox_mutation_ab_param_d->setObjectName(QString::fromUtf8("spinbox_mutation_ab_param_d"));
        spinbox_mutation_ab_param_d->setMinimum(-100.000000000000000);
        spinbox_mutation_ab_param_d->setMaximum(100.000000000000000);
        spinbox_mutation_ab_param_d->setSingleStep(0.100000000000000);
        spinbox_mutation_ab_param_d->setValue(1.000000000000000);
        spinbox_mutation_ab_param_d->setDecimals(6);

        gridLayout_mutation_abox->addWidget(spinbox_mutation_ab_param_d, 2, 3, 1, 1);

        label_ab_param_e = new QLabel(groupCheck_mutation_abox_enabled);
        label_ab_param_e->setObjectName(QString::fromUtf8("label_ab_param_e"));

        gridLayout_mutation_abox->addWidget(label_ab_param_e, 2, 4, 1, 1);

        spinbox_mutation_ab_param_e = new MyDoubleSpinBox(groupCheck_mutation_abox_enabled);
        spinbox_mutation_ab_param_e->setObjectName(QString::fromUtf8("spinbox_mutation_ab_param_e"));
        spinbox_mutation_ab_param_e->setMinimum(-100.000000000000000);
        spinbox_mutation_ab_param_e->setMaximum(100.000000000000000);
        spinbox_mutation_ab_param_e->setSingleStep(0.100000000000000);
        spinbox_mutation_ab_param_e->setValue(1.000000000000000);
        spinbox_mutation_ab_param_e->setDecimals(6);

        gridLayout_mutation_abox->addWidget(spinbox_mutation_ab_param_e, 2, 5, 1, 1);

        label_ab_param_f = new QLabel(groupCheck_mutation_abox_enabled);
        label_ab_param_f->setObjectName(QString::fromUtf8("label_ab_param_f"));

        gridLayout_mutation_abox->addWidget(label_ab_param_f, 3, 0, 1, 1);

        spinbox_mutation_ab_param_f = new MyDoubleSpinBox(groupCheck_mutation_abox_enabled);
        spinbox_mutation_ab_param_f->setObjectName(QString::fromUtf8("spinbox_mutation_ab_param_f"));
        spinbox_mutation_ab_param_f->setMinimum(-100.000000000000000);
        spinbox_mutation_ab_param_f->setMaximum(100.000000000000000);
        spinbox_mutation_ab_param_f->setSingleStep(0.100000000000000);
        spinbox_mutation_ab_param_f->setValue(1.000000000000000);
        spinbox_mutation_ab_param_f->setDecimals(6);

        gridLayout_mutation_abox->addWidget(spinbox_mutation_ab_param_f, 3, 1, 1, 1);

        label_ab_param_g = new QLabel(groupCheck_mutation_abox_enabled);
        label_ab_param_g->setObjectName(QString::fromUtf8("label_ab_param_g"));

        gridLayout_mutation_abox->addWidget(label_ab_param_g, 3, 2, 1, 1);

        spinbox_mutation_ab_param_g = new MyDoubleSpinBox(groupCheck_mutation_abox_enabled);
        spinbox_mutation_ab_param_g->setObjectName(QString::fromUtf8("spinbox_mutation_ab_param_g"));
        spinbox_mutation_ab_param_g->setMinimum(-100.000000000000000);
        spinbox_mutation_ab_param_g->setMaximum(100.000000000000000);
        spinbox_mutation_ab_param_g->setSingleStep(0.100000000000000);
        spinbox_mutation_ab_param_g->setValue(1.000000000000000);
        spinbox_mutation_ab_param_g->setDecimals(6);

        gridLayout_mutation_abox->addWidget(spinbox_mutation_ab_param_g, 3, 3, 1, 1);

        label_ab_param_h = new QLabel(groupCheck_mutation_abox_enabled);
        label_ab_param_h->setObjectName(QString::fromUtf8("label_ab_param_h"));

        gridLayout_mutation_abox->addWidget(label_ab_param_h, 3, 4, 1, 1);

        spinbox_mutation_ab_param_h = new MyDoubleSpinBox(groupCheck_mutation_abox_enabled);
        spinbox_mutation_ab_param_h->setObjectName(QString::fromUtf8("spinbox_mutation_ab_param_h"));
        spinbox_mutation_ab_param_h->setMinimum(-100.000000000000000);
        spinbox_mutation_ab_param_h->setMaximum(100.000000000000000);
        spinbox_mutation_ab_param_h->setSingleStep(0.100000000000000);
        spinbox_mutation_ab_param_h->setValue(0.000000000000000);
        spinbox_mutation_ab_param_h->setDecimals(6);

        gridLayout_mutation_abox->addWidget(spinbox_mutation_ab_param_h, 3, 5, 1, 1);

        label_ab_iter = new QLabel(groupCheck_mutation_abox_enabled);
        label_ab_iter->setObjectName(QString::fromUtf8("label_ab_iter"));

        gridLayout_mutation_abox->addWidget(label_ab_iter, 4, 0, 1, 1);

        spinboxInt_mutation_ab_iter_start = new MySpinBox(groupCheck_mutation_abox_enabled);
        spinboxInt_mutation_ab_iter_start->setObjectName(QString::fromUtf8("spinboxInt_mutation_ab_iter_start"));
        spinboxInt_mutation_ab_iter_start->setMinimum(0);
        spinboxInt_mutation_ab_iter_start->setMaximum(10000);
        spinboxInt_mutation_ab_iter_start->setValue(0);

        gridLayout_mutation_abox->addWidget(spinboxInt_mutation_ab_iter_start, 4, 1, 1, 1);

        label_ab_iter_stop = new QLabel(groupCheck_mutation_abox_enabled);
        label_ab_iter_stop->setObjectName(QString::fromUtf8("label_ab_iter_stop"));

        gridLayout_mutation_abox->addWidget(label_ab_iter_stop, 4, 2, 1, 1);

        spinboxInt_mutation_ab_iter_stop = new MySpinBox(groupCheck_mutation_abox_enabled);
        spinboxInt_mutation_ab_iter_stop->setObjectName(QString::fromUtf8("spinboxInt_mutation_ab_iter_stop"));
        spinboxInt_mutation_ab_iter_stop->setMinimum(0);
        spinboxInt_mutation_ab_iter_stop->setMaximum(10000);
        spinboxInt_mutation_ab_iter_stop->setValue(10000);

        gridLayout_mutation_abox->addWidget(spinboxInt_mutation_ab_iter_stop, 4, 3, 1, 1);


        verticalLayout_cMutationSystemsGroup2->addWidget(groupCheck_mutation_abox_enabled);

        groupCheck_mutation_noise_enabled = new MyGroupBox(cMutationSystemsGroup2);
        groupCheck_mutation_noise_enabled->setObjectName(QString::fromUtf8("groupCheck_mutation_noise_enabled"));
        groupCheck_mutation_noise_enabled->setCheckable(true);
        groupCheck_mutation_noise_enabled->setChecked(false);
        gridLayout_mutation_noise = new QGridLayout(groupCheck_mutation_noise_enabled);
        gridLayout_mutation_noise->setObjectName(QString::fromUtf8("gridLayout_mutation_noise"));
        label_noise_type = new QLabel(groupCheck_mutation_noise_enabled);
        label_noise_type->setObjectName(QString::fromUtf8("label_noise_type"));

        gridLayout_mutation_noise->addWidget(label_noise_type, 0, 0, 1, 1);

        label1 = new QLabel(groupCheck_mutation_noise_enabled);
        label1->setObjectName(QString::fromUtf8("label1"));
        label1->setAlignment(Qt::AlignCenter);

        gridLayout_mutation_noise->addWidget(label1, 0, 6, 1, 1);

        spinbox_mutation_noise_section_weight = new MyDoubleSpinBox(groupCheck_mutation_noise_enabled);
        spinbox_mutation_noise_section_weight->setObjectName(QString::fromUtf8("spinbox_mutation_noise_section_weight"));
        spinbox_mutation_noise_section_weight->setMinimum(0.000000000000000);
        spinbox_mutation_noise_section_weight->setMaximum(1.000000000000000);
        spinbox_mutation_noise_section_weight->setSingleStep(0.050000000000000);
        spinbox_mutation_noise_section_weight->setValue(1.000000000000000);
        spinbox_mutation_noise_section_weight->setDecimals(2);
        spinbox_mutation_noise_section_weight->setMinimumSize(QSize(60, 0));

        gridLayout_mutation_noise->addWidget(spinbox_mutation_noise_section_weight, 1, 6, 1, 1);

        pushButton_mutation_noise_reset_weights = new QPushButton(groupCheck_mutation_noise_enabled);
        pushButton_mutation_noise_reset_weights->setObjectName(QString::fromUtf8("pushButton_mutation_noise_reset_weights"));
        pushButton_mutation_noise_reset_weights->setMaximumSize(QSize(60, 16777215));

        gridLayout_mutation_noise->addWidget(pushButton_mutation_noise_reset_weights, 2, 6, 1, 1);

        comboBox_mutation_noise_type = new QComboBox(groupCheck_mutation_noise_enabled);
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->addItem(QString());
        comboBox_mutation_noise_type->setObjectName(QString::fromUtf8("comboBox_mutation_noise_type"));

        gridLayout_mutation_noise->addWidget(comboBox_mutation_noise_type, 0, 1, 1, 5);

        label_noise_factor = new QLabel(groupCheck_mutation_noise_enabled);
        label_noise_factor->setObjectName(QString::fromUtf8("label_noise_factor"));

        gridLayout_mutation_noise->addWidget(label_noise_factor, 1, 0, 1, 1);

        spinbox_mutation_noise_factor = new MyDoubleSpinBox(groupCheck_mutation_noise_enabled);
        spinbox_mutation_noise_factor->setObjectName(QString::fromUtf8("spinbox_mutation_noise_factor"));
        spinbox_mutation_noise_factor->setMinimum(-100.000000000000000);
        spinbox_mutation_noise_factor->setMaximum(100.000000000000000);
        spinbox_mutation_noise_factor->setSingleStep(0.100000000000000);
        spinbox_mutation_noise_factor->setValue(1.000000000000000);
        spinbox_mutation_noise_factor->setDecimals(6);

        gridLayout_mutation_noise->addWidget(spinbox_mutation_noise_factor, 1, 1, 1, 1);

        label_noise_param_a = new QLabel(groupCheck_mutation_noise_enabled);
        label_noise_param_a->setObjectName(QString::fromUtf8("label_noise_param_a"));

        gridLayout_mutation_noise->addWidget(label_noise_param_a, 1, 2, 1, 1);

        spinbox_mutation_noise_param_a = new MyDoubleSpinBox(groupCheck_mutation_noise_enabled);
        spinbox_mutation_noise_param_a->setObjectName(QString::fromUtf8("spinbox_mutation_noise_param_a"));
        spinbox_mutation_noise_param_a->setMinimum(-100.000000000000000);
        spinbox_mutation_noise_param_a->setMaximum(100.000000000000000);
        spinbox_mutation_noise_param_a->setSingleStep(0.100000000000000);
        spinbox_mutation_noise_param_a->setValue(1.000000000000000);
        spinbox_mutation_noise_param_a->setDecimals(6);

        gridLayout_mutation_noise->addWidget(spinbox_mutation_noise_param_a, 1, 3, 1, 1);

        label_noise_param_b = new QLabel(groupCheck_mutation_noise_enabled);
        label_noise_param_b->setObjectName(QString::fromUtf8("label_noise_param_b"));

        gridLayout_mutation_noise->addWidget(label_noise_param_b, 1, 4, 1, 1);

        spinbox_mutation_noise_param_b = new MyDoubleSpinBox(groupCheck_mutation_noise_enabled);
        spinbox_mutation_noise_param_b->setObjectName(QString::fromUtf8("spinbox_mutation_noise_param_b"));
        spinbox_mutation_noise_param_b->setMinimum(-100.000000000000000);
        spinbox_mutation_noise_param_b->setMaximum(100.000000000000000);
        spinbox_mutation_noise_param_b->setSingleStep(0.100000000000000);
        spinbox_mutation_noise_param_b->setValue(1.000000000000000);
        spinbox_mutation_noise_param_b->setDecimals(6);

        gridLayout_mutation_noise->addWidget(spinbox_mutation_noise_param_b, 1, 5, 1, 1);

        label_noise_param_c = new QLabel(groupCheck_mutation_noise_enabled);
        label_noise_param_c->setObjectName(QString::fromUtf8("label_noise_param_c"));

        gridLayout_mutation_noise->addWidget(label_noise_param_c, 2, 0, 1, 1);

        spinbox_mutation_noise_param_c = new MyDoubleSpinBox(groupCheck_mutation_noise_enabled);
        spinbox_mutation_noise_param_c->setObjectName(QString::fromUtf8("spinbox_mutation_noise_param_c"));
        spinbox_mutation_noise_param_c->setMinimum(-100.000000000000000);
        spinbox_mutation_noise_param_c->setMaximum(100.000000000000000);
        spinbox_mutation_noise_param_c->setSingleStep(0.100000000000000);
        spinbox_mutation_noise_param_c->setValue(1.000000000000000);
        spinbox_mutation_noise_param_c->setDecimals(6);

        gridLayout_mutation_noise->addWidget(spinbox_mutation_noise_param_c, 2, 1, 1, 1);

        label_noise_param_d = new QLabel(groupCheck_mutation_noise_enabled);
        label_noise_param_d->setObjectName(QString::fromUtf8("label_noise_param_d"));

        gridLayout_mutation_noise->addWidget(label_noise_param_d, 2, 2, 1, 1);

        spinbox_mutation_noise_param_d = new MyDoubleSpinBox(groupCheck_mutation_noise_enabled);
        spinbox_mutation_noise_param_d->setObjectName(QString::fromUtf8("spinbox_mutation_noise_param_d"));
        spinbox_mutation_noise_param_d->setMinimum(-100.000000000000000);
        spinbox_mutation_noise_param_d->setMaximum(100.000000000000000);
        spinbox_mutation_noise_param_d->setSingleStep(0.100000000000000);
        spinbox_mutation_noise_param_d->setValue(1.000000000000000);
        spinbox_mutation_noise_param_d->setDecimals(6);

        gridLayout_mutation_noise->addWidget(spinbox_mutation_noise_param_d, 2, 3, 1, 1);

        label_julia_noise_freq = new QLabel(groupCheck_mutation_noise_enabled);
        label_julia_noise_freq->setObjectName(QString::fromUtf8("label_julia_noise_freq"));

        gridLayout_mutation_noise->addWidget(label_julia_noise_freq, 2, 4, 1, 1);

        spinbox_mutation_noise_freq = new MyDoubleSpinBox(groupCheck_mutation_noise_enabled);
        spinbox_mutation_noise_freq->setObjectName(QString::fromUtf8("spinbox_mutation_noise_freq"));
        spinbox_mutation_noise_freq->setMinimum(0.001000000000000);
        spinbox_mutation_noise_freq->setMaximum(100.000000000000000);
        spinbox_mutation_noise_freq->setSingleStep(0.100000000000000);
        spinbox_mutation_noise_freq->setValue(1.000000000000000);
        spinbox_mutation_noise_freq->setDecimals(6);

        gridLayout_mutation_noise->addWidget(spinbox_mutation_noise_freq, 2, 5, 1, 1);

        label_julia_noise_amp = new QLabel(groupCheck_mutation_noise_enabled);
        label_julia_noise_amp->setObjectName(QString::fromUtf8("label_julia_noise_amp"));

        gridLayout_mutation_noise->addWidget(label_julia_noise_amp, 3, 0, 1, 1);

        spinbox_mutation_noise_amp = new MyDoubleSpinBox(groupCheck_mutation_noise_enabled);
        spinbox_mutation_noise_amp->setObjectName(QString::fromUtf8("spinbox_mutation_noise_amp"));
        spinbox_mutation_noise_amp->setMinimum(-10.000000000000000);
        spinbox_mutation_noise_amp->setMaximum(10.000000000000000);
        spinbox_mutation_noise_amp->setSingleStep(0.010000000000000);
        spinbox_mutation_noise_amp->setValue(0.500000000000000);
        spinbox_mutation_noise_amp->setDecimals(6);

        gridLayout_mutation_noise->addWidget(spinbox_mutation_noise_amp, 3, 1, 1, 1);

        label_noise_iter = new QLabel(groupCheck_mutation_noise_enabled);
        label_noise_iter->setObjectName(QString::fromUtf8("label_noise_iter"));

        gridLayout_mutation_noise->addWidget(label_noise_iter, 3, 2, 1, 1);

        spinboxInt_mutation_noise_iter_start = new MySpinBox(groupCheck_mutation_noise_enabled);
        spinboxInt_mutation_noise_iter_start->setObjectName(QString::fromUtf8("spinboxInt_mutation_noise_iter_start"));
        spinboxInt_mutation_noise_iter_start->setMinimum(0);
        spinboxInt_mutation_noise_iter_start->setMaximum(10000);
        spinboxInt_mutation_noise_iter_start->setValue(0);

        gridLayout_mutation_noise->addWidget(spinboxInt_mutation_noise_iter_start, 3, 3, 1, 1);

        label_noise_iter_stop = new QLabel(groupCheck_mutation_noise_enabled);
        label_noise_iter_stop->setObjectName(QString::fromUtf8("label_noise_iter_stop"));

        gridLayout_mutation_noise->addWidget(label_noise_iter_stop, 3, 4, 1, 1);

        spinboxInt_mutation_noise_iter_stop = new MySpinBox(groupCheck_mutation_noise_enabled);
        spinboxInt_mutation_noise_iter_stop->setObjectName(QString::fromUtf8("spinboxInt_mutation_noise_iter_stop"));
        spinboxInt_mutation_noise_iter_stop->setMinimum(0);
        spinboxInt_mutation_noise_iter_stop->setMaximum(10000);
        spinboxInt_mutation_noise_iter_stop->setValue(10000);

        gridLayout_mutation_noise->addWidget(spinboxInt_mutation_noise_iter_stop, 3, 5, 1, 1);


        verticalLayout_cMutationSystemsGroup2->addWidget(groupCheck_mutation_noise_enabled);

        groupCheck_mutation_orbit_trap_enabled = new MyGroupBox(cMutationSystemsGroup2);
        groupCheck_mutation_orbit_trap_enabled->setObjectName(QString::fromUtf8("groupCheck_mutation_orbit_trap_enabled"));
        groupCheck_mutation_orbit_trap_enabled->setCheckable(true);
        groupCheck_mutation_orbit_trap_enabled->setChecked(false);
        gridLayout_mutation_orbit_trap = new QGridLayout(groupCheck_mutation_orbit_trap_enabled);
        gridLayout_mutation_orbit_trap->setObjectName(QString::fromUtf8("gridLayout_mutation_orbit_trap"));
        label_orbit_type = new QLabel(groupCheck_mutation_orbit_trap_enabled);
        label_orbit_type->setObjectName(QString::fromUtf8("label_orbit_type"));

        gridLayout_mutation_orbit_trap->addWidget(label_orbit_type, 0, 0, 1, 1);

        label2 = new QLabel(groupCheck_mutation_orbit_trap_enabled);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setAlignment(Qt::AlignCenter);

        gridLayout_mutation_orbit_trap->addWidget(label2, 0, 6, 1, 1);

        spinbox_mutation_orbit_trap_section_weight = new MyDoubleSpinBox(groupCheck_mutation_orbit_trap_enabled);
        spinbox_mutation_orbit_trap_section_weight->setObjectName(QString::fromUtf8("spinbox_mutation_orbit_trap_section_weight"));
        spinbox_mutation_orbit_trap_section_weight->setMinimum(0.000000000000000);
        spinbox_mutation_orbit_trap_section_weight->setMaximum(1.000000000000000);
        spinbox_mutation_orbit_trap_section_weight->setSingleStep(0.050000000000000);
        spinbox_mutation_orbit_trap_section_weight->setValue(1.000000000000000);
        spinbox_mutation_orbit_trap_section_weight->setDecimals(2);
        spinbox_mutation_orbit_trap_section_weight->setMinimumSize(QSize(60, 0));

        gridLayout_mutation_orbit_trap->addWidget(spinbox_mutation_orbit_trap_section_weight, 1, 6, 1, 1);

        pushButton_mutation_orbit_trap_reset_weights = new QPushButton(groupCheck_mutation_orbit_trap_enabled);
        pushButton_mutation_orbit_trap_reset_weights->setObjectName(QString::fromUtf8("pushButton_mutation_orbit_trap_reset_weights"));
        pushButton_mutation_orbit_trap_reset_weights->setMaximumSize(QSize(60, 16777215));

        gridLayout_mutation_orbit_trap->addWidget(pushButton_mutation_orbit_trap_reset_weights, 2, 6, 1, 1);

        comboBox_mutation_orbit_trap_type = new QComboBox(groupCheck_mutation_orbit_trap_enabled);
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->addItem(QString());
        comboBox_mutation_orbit_trap_type->setObjectName(QString::fromUtf8("comboBox_mutation_orbit_trap_type"));

        gridLayout_mutation_orbit_trap->addWidget(comboBox_mutation_orbit_trap_type, 0, 1, 1, 5);

        label_orbit_factor = new QLabel(groupCheck_mutation_orbit_trap_enabled);
        label_orbit_factor->setObjectName(QString::fromUtf8("label_orbit_factor"));

        gridLayout_mutation_orbit_trap->addWidget(label_orbit_factor, 1, 0, 1, 1);

        spinbox_mutation_orbit_factor = new MyDoubleSpinBox(groupCheck_mutation_orbit_trap_enabled);
        spinbox_mutation_orbit_factor->setObjectName(QString::fromUtf8("spinbox_mutation_orbit_factor"));
        spinbox_mutation_orbit_factor->setMinimum(-100.000000000000000);
        spinbox_mutation_orbit_factor->setMaximum(100.000000000000000);
        spinbox_mutation_orbit_factor->setSingleStep(0.100000000000000);
        spinbox_mutation_orbit_factor->setValue(1.000000000000000);
        spinbox_mutation_orbit_factor->setDecimals(6);

        gridLayout_mutation_orbit_trap->addWidget(spinbox_mutation_orbit_factor, 1, 1, 1, 1);

        label_orbit_param_a = new QLabel(groupCheck_mutation_orbit_trap_enabled);
        label_orbit_param_a->setObjectName(QString::fromUtf8("label_orbit_param_a"));

        gridLayout_mutation_orbit_trap->addWidget(label_orbit_param_a, 1, 2, 1, 1);

        spinbox_mutation_orbit_param_a = new MyDoubleSpinBox(groupCheck_mutation_orbit_trap_enabled);
        spinbox_mutation_orbit_param_a->setObjectName(QString::fromUtf8("spinbox_mutation_orbit_param_a"));
        spinbox_mutation_orbit_param_a->setMinimum(-100.000000000000000);
        spinbox_mutation_orbit_param_a->setMaximum(100.000000000000000);
        spinbox_mutation_orbit_param_a->setSingleStep(0.100000000000000);
        spinbox_mutation_orbit_param_a->setValue(1.000000000000000);
        spinbox_mutation_orbit_param_a->setDecimals(6);

        gridLayout_mutation_orbit_trap->addWidget(spinbox_mutation_orbit_param_a, 1, 3, 1, 1);

        label_orbit_param_b = new QLabel(groupCheck_mutation_orbit_trap_enabled);
        label_orbit_param_b->setObjectName(QString::fromUtf8("label_orbit_param_b"));

        gridLayout_mutation_orbit_trap->addWidget(label_orbit_param_b, 1, 4, 1, 1);

        spinbox_mutation_orbit_param_b = new MyDoubleSpinBox(groupCheck_mutation_orbit_trap_enabled);
        spinbox_mutation_orbit_param_b->setObjectName(QString::fromUtf8("spinbox_mutation_orbit_param_b"));
        spinbox_mutation_orbit_param_b->setMinimum(-100.000000000000000);
        spinbox_mutation_orbit_param_b->setMaximum(100.000000000000000);
        spinbox_mutation_orbit_param_b->setSingleStep(0.100000000000000);
        spinbox_mutation_orbit_param_b->setValue(1.000000000000000);
        spinbox_mutation_orbit_param_b->setDecimals(6);

        gridLayout_mutation_orbit_trap->addWidget(spinbox_mutation_orbit_param_b, 1, 5, 1, 1);

        label_orbit_param_c = new QLabel(groupCheck_mutation_orbit_trap_enabled);
        label_orbit_param_c->setObjectName(QString::fromUtf8("label_orbit_param_c"));

        gridLayout_mutation_orbit_trap->addWidget(label_orbit_param_c, 2, 0, 1, 1);

        spinbox_mutation_orbit_param_c = new MyDoubleSpinBox(groupCheck_mutation_orbit_trap_enabled);
        spinbox_mutation_orbit_param_c->setObjectName(QString::fromUtf8("spinbox_mutation_orbit_param_c"));
        spinbox_mutation_orbit_param_c->setMinimum(-100.000000000000000);
        spinbox_mutation_orbit_param_c->setMaximum(100.000000000000000);
        spinbox_mutation_orbit_param_c->setSingleStep(0.100000000000000);
        spinbox_mutation_orbit_param_c->setValue(1.000000000000000);
        spinbox_mutation_orbit_param_c->setDecimals(6);

        gridLayout_mutation_orbit_trap->addWidget(spinbox_mutation_orbit_param_c, 2, 1, 1, 1);

        label_orbit_param_d = new QLabel(groupCheck_mutation_orbit_trap_enabled);
        label_orbit_param_d->setObjectName(QString::fromUtf8("label_orbit_param_d"));

        gridLayout_mutation_orbit_trap->addWidget(label_orbit_param_d, 2, 2, 1, 1);

        spinbox_mutation_orbit_param_d = new MyDoubleSpinBox(groupCheck_mutation_orbit_trap_enabled);
        spinbox_mutation_orbit_param_d->setObjectName(QString::fromUtf8("spinbox_mutation_orbit_param_d"));
        spinbox_mutation_orbit_param_d->setMinimum(-100.000000000000000);
        spinbox_mutation_orbit_param_d->setMaximum(100.000000000000000);
        spinbox_mutation_orbit_param_d->setSingleStep(0.100000000000000);
        spinbox_mutation_orbit_param_d->setValue(1.000000000000000);
        spinbox_mutation_orbit_param_d->setDecimals(6);

        gridLayout_mutation_orbit_trap->addWidget(spinbox_mutation_orbit_param_d, 2, 3, 1, 1);

        label_orbit_iter = new QLabel(groupCheck_mutation_orbit_trap_enabled);
        label_orbit_iter->setObjectName(QString::fromUtf8("label_orbit_iter"));

        gridLayout_mutation_orbit_trap->addWidget(label_orbit_iter, 2, 4, 1, 1);

        spinboxInt_mutation_orbit_iter_start = new MySpinBox(groupCheck_mutation_orbit_trap_enabled);
        spinboxInt_mutation_orbit_iter_start->setObjectName(QString::fromUtf8("spinboxInt_mutation_orbit_iter_start"));
        spinboxInt_mutation_orbit_iter_start->setMinimum(0);
        spinboxInt_mutation_orbit_iter_start->setMaximum(10000);
        spinboxInt_mutation_orbit_iter_start->setValue(0);

        gridLayout_mutation_orbit_trap->addWidget(spinboxInt_mutation_orbit_iter_start, 2, 5, 1, 1);

        label_orbit_iter_stop2 = new QLabel(groupCheck_mutation_orbit_trap_enabled);
        label_orbit_iter_stop2->setObjectName(QString::fromUtf8("label_orbit_iter_stop2"));

        gridLayout_mutation_orbit_trap->addWidget(label_orbit_iter_stop2, 3, 0, 1, 1);

        spinboxInt_mutation_orbit_iter_stop = new MySpinBox(groupCheck_mutation_orbit_trap_enabled);
        spinboxInt_mutation_orbit_iter_stop->setObjectName(QString::fromUtf8("spinboxInt_mutation_orbit_iter_stop"));
        spinboxInt_mutation_orbit_iter_stop->setMinimum(0);
        spinboxInt_mutation_orbit_iter_stop->setMaximum(10000);
        spinboxInt_mutation_orbit_iter_stop->setValue(10000);

        gridLayout_mutation_orbit_trap->addWidget(spinboxInt_mutation_orbit_iter_stop, 3, 1, 1, 1);


        verticalLayout_cMutationSystemsGroup2->addWidget(groupCheck_mutation_orbit_trap_enabled);


        retranslateUi(cMutationSystemsGroup2);

        QMetaObject::connectSlotsByName(cMutationSystemsGroup2);
    } // setupUi

    void retranslateUi(QWidget *cMutationSystemsGroup2)
    {
        groupCheck_mutation_abox_enabled->setTitle(QCoreApplication::translate("cMutationSystemsGroup2", "Abox DE System", nullptr));
        label_ab_type->setText(QCoreApplication::translate("cMutationSystemsGroup2", "AB Type:", nullptr));
        label->setText(QCoreApplication::translate("cMutationSystemsGroup2", "Wt", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_mutation_abox_section_weight->setToolTip(QCoreApplication::translate("cMutationSystemsGroup2", "Section weight: 1=full effect, 0=off", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_mutation_abox_reset_weights->setText(QCoreApplication::translate("cMutationSystemsGroup2", "Reset", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_mutation_abox_reset_weights->setToolTip(QCoreApplication::translate("cMutationSystemsGroup2", "Reset this section's weights to 1.0", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_mutation_abox_type->setItemText(0, QCoreApplication::translate("cMutationSystemsGroup2", "None", nullptr));
        comboBox_mutation_abox_type->setItemText(1, QCoreApplication::translate("cMutationSystemsGroup2", "Linear Scale", nullptr));
        comboBox_mutation_abox_type->setItemText(2, QCoreApplication::translate("cMutationSystemsGroup2", "Quadratic Scale", nullptr));
        comboBox_mutation_abox_type->setItemText(3, QCoreApplication::translate("cMutationSystemsGroup2", "Exponential Decay", nullptr));
        comboBox_mutation_abox_type->setItemText(4, QCoreApplication::translate("cMutationSystemsGroup2", "Harmonic Scale", nullptr));
        comboBox_mutation_abox_type->setItemText(5, QCoreApplication::translate("cMutationSystemsGroup2", "Sigmoid Scale", nullptr));
        comboBox_mutation_abox_type->setItemText(6, QCoreApplication::translate("cMutationSystemsGroup2", "Log Scale", nullptr));
        comboBox_mutation_abox_type->setItemText(7, QCoreApplication::translate("cMutationSystemsGroup2", "Sqrt Scale", nullptr));
        comboBox_mutation_abox_type->setItemText(8, QCoreApplication::translate("cMutationSystemsGroup2", "Power Scale", nullptr));
        comboBox_mutation_abox_type->setItemText(9, QCoreApplication::translate("cMutationSystemsGroup2", "Atan Scale", nullptr));
        comboBox_mutation_abox_type->setItemText(10, QCoreApplication::translate("cMutationSystemsGroup2", "Tanh Scale", nullptr));
        comboBox_mutation_abox_type->setItemText(11, QCoreApplication::translate("cMutationSystemsGroup2", "Softplus", nullptr));
        comboBox_mutation_abox_type->setItemText(12, QCoreApplication::translate("cMutationSystemsGroup2", "ReLU", nullptr));
        comboBox_mutation_abox_type->setItemText(13, QCoreApplication::translate("cMutationSystemsGroup2", "Gaussian", nullptr));
        comboBox_mutation_abox_type->setItemText(14, QCoreApplication::translate("cMutationSystemsGroup2", "Laplacian", nullptr));
        comboBox_mutation_abox_type->setItemText(15, QCoreApplication::translate("cMutationSystemsGroup2", "Cauchy", nullptr));
        comboBox_mutation_abox_type->setItemText(16, QCoreApplication::translate("cMutationSystemsGroup2", "Logistic", nullptr));
        comboBox_mutation_abox_type->setItemText(17, QCoreApplication::translate("cMutationSystemsGroup2", "Reciprocal", nullptr));
        comboBox_mutation_abox_type->setItemText(18, QCoreApplication::translate("cMutationSystemsGroup2", "Step", nullptr));
        comboBox_mutation_abox_type->setItemText(19, QCoreApplication::translate("cMutationSystemsGroup2", "Sawtooth", nullptr));
        comboBox_mutation_abox_type->setItemText(20, QCoreApplication::translate("cMutationSystemsGroup2", "Triangle Wave", nullptr));
        comboBox_mutation_abox_type->setItemText(21, QCoreApplication::translate("cMutationSystemsGroup2", "Square Wave", nullptr));
        comboBox_mutation_abox_type->setItemText(22, QCoreApplication::translate("cMutationSystemsGroup2", "Smooth Step", nullptr));
        comboBox_mutation_abox_type->setItemText(23, QCoreApplication::translate("cMutationSystemsGroup2", "Hermite", nullptr));
        comboBox_mutation_abox_type->setItemText(24, QCoreApplication::translate("cMutationSystemsGroup2", "Catmull-Rom", nullptr));
        comboBox_mutation_abox_type->setItemText(25, QCoreApplication::translate("cMutationSystemsGroup2", "B-Spline", nullptr));
        comboBox_mutation_abox_type->setItemText(26, QCoreApplication::translate("cMutationSystemsGroup2", "Bezier", nullptr));
        comboBox_mutation_abox_type->setItemText(27, QCoreApplication::translate("cMutationSystemsGroup2", "Polynomial 3", nullptr));
        comboBox_mutation_abox_type->setItemText(28, QCoreApplication::translate("cMutationSystemsGroup2", "Polynomial 4", nullptr));
        comboBox_mutation_abox_type->setItemText(29, QCoreApplication::translate("cMutationSystemsGroup2", "Rational", nullptr));
        comboBox_mutation_abox_type->setItemText(30, QCoreApplication::translate("cMutationSystemsGroup2", "Chebyshev", nullptr));

        label_ab_factor->setText(QCoreApplication::translate("cMutationSystemsGroup2", "Factor:", nullptr));
        label_ab_param_a->setText(QCoreApplication::translate("cMutationSystemsGroup2", "A:", nullptr));
        label_ab_param_b->setText(QCoreApplication::translate("cMutationSystemsGroup2", "B:", nullptr));
        label_ab_param_c->setText(QCoreApplication::translate("cMutationSystemsGroup2", "C:", nullptr));
        label_ab_param_d->setText(QCoreApplication::translate("cMutationSystemsGroup2", "D:", nullptr));
        label_ab_param_e->setText(QCoreApplication::translate("cMutationSystemsGroup2", "E:", nullptr));
        label_ab_param_f->setText(QCoreApplication::translate("cMutationSystemsGroup2", "F:", nullptr));
        label_ab_param_g->setText(QCoreApplication::translate("cMutationSystemsGroup2", "G:", nullptr));
        label_ab_param_h->setText(QCoreApplication::translate("cMutationSystemsGroup2", "H:", nullptr));
        label_ab_iter->setText(QCoreApplication::translate("cMutationSystemsGroup2", "AB Iter:", nullptr));
        label_ab_iter_stop->setText(QCoreApplication::translate("cMutationSystemsGroup2", "Stop:", nullptr));
        groupCheck_mutation_noise_enabled->setTitle(QCoreApplication::translate("cMutationSystemsGroup2", "Noise & Procedural DE", nullptr));
        label_noise_type->setText(QCoreApplication::translate("cMutationSystemsGroup2", "Noise Type:", nullptr));
        label1->setText(QCoreApplication::translate("cMutationSystemsGroup2", "Wt", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_mutation_noise_section_weight->setToolTip(QCoreApplication::translate("cMutationSystemsGroup2", "Section weight: 1=full effect, 0=off", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_mutation_noise_reset_weights->setText(QCoreApplication::translate("cMutationSystemsGroup2", "Reset", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_mutation_noise_reset_weights->setToolTip(QCoreApplication::translate("cMutationSystemsGroup2", "Reset this section's weights to 1.0", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_mutation_noise_type->setItemText(0, QCoreApplication::translate("cMutationSystemsGroup2", "None", nullptr));
        comboBox_mutation_noise_type->setItemText(1, QCoreApplication::translate("cMutationSystemsGroup2", "Hash Noise 3D", nullptr));
        comboBox_mutation_noise_type->setItemText(2, QCoreApplication::translate("cMutationSystemsGroup2", "Hash Noise Avg", nullptr));
        comboBox_mutation_noise_type->setItemText(3, QCoreApplication::translate("cMutationSystemsGroup2", "Sine Noise", nullptr));
        comboBox_mutation_noise_type->setItemText(4, QCoreApplication::translate("cMutationSystemsGroup2", "Lattice Noise", nullptr));
        comboBox_mutation_noise_type->setItemText(5, QCoreApplication::translate("cMutationSystemsGroup2", "Gradient Noise", nullptr));
        comboBox_mutation_noise_type->setItemText(6, QCoreApplication::translate("cMutationSystemsGroup2", "Value Noise", nullptr));
        comboBox_mutation_noise_type->setItemText(7, QCoreApplication::translate("cMutationSystemsGroup2", "Perlin 3D", nullptr));
        comboBox_mutation_noise_type->setItemText(8, QCoreApplication::translate("cMutationSystemsGroup2", "Simplex 3D", nullptr));
        comboBox_mutation_noise_type->setItemText(9, QCoreApplication::translate("cMutationSystemsGroup2", "Worley (Cell)", nullptr));
        comboBox_mutation_noise_type->setItemText(10, QCoreApplication::translate("cMutationSystemsGroup2", "Voronoi", nullptr));
        comboBox_mutation_noise_type->setItemText(11, QCoreApplication::translate("cMutationSystemsGroup2", "FBM (4-octave)", nullptr));
        comboBox_mutation_noise_type->setItemText(12, QCoreApplication::translate("cMutationSystemsGroup2", "Turbulence", nullptr));
        comboBox_mutation_noise_type->setItemText(13, QCoreApplication::translate("cMutationSystemsGroup2", "Ridged Multi", nullptr));
        comboBox_mutation_noise_type->setItemText(14, QCoreApplication::translate("cMutationSystemsGroup2", "Billowed", nullptr));
        comboBox_mutation_noise_type->setItemText(15, QCoreApplication::translate("cMutationSystemsGroup2", "Marble", nullptr));
        comboBox_mutation_noise_type->setItemText(16, QCoreApplication::translate("cMutationSystemsGroup2", "Wood Grain", nullptr));
        comboBox_mutation_noise_type->setItemText(17, QCoreApplication::translate("cMutationSystemsGroup2", "Caustics", nullptr));
        comboBox_mutation_noise_type->setItemText(18, QCoreApplication::translate("cMutationSystemsGroup2", "Erosion", nullptr));
        comboBox_mutation_noise_type->setItemText(19, QCoreApplication::translate("cMutationSystemsGroup2", "River Network", nullptr));
        comboBox_mutation_noise_type->setItemText(20, QCoreApplication::translate("cMutationSystemsGroup2", "Cloud", nullptr));
        comboBox_mutation_noise_type->setItemText(21, QCoreApplication::translate("cMutationSystemsGroup2", "Lava", nullptr));
        comboBox_mutation_noise_type->setItemText(22, QCoreApplication::translate("cMutationSystemsGroup2", "Crystal", nullptr));
        comboBox_mutation_noise_type->setItemText(23, QCoreApplication::translate("cMutationSystemsGroup2", "Foam", nullptr));
        comboBox_mutation_noise_type->setItemText(24, QCoreApplication::translate("cMutationSystemsGroup2", "Bark", nullptr));
        comboBox_mutation_noise_type->setItemText(25, QCoreApplication::translate("cMutationSystemsGroup2", "Scales", nullptr));
        comboBox_mutation_noise_type->setItemText(26, QCoreApplication::translate("cMutationSystemsGroup2", "Weave", nullptr));
        comboBox_mutation_noise_type->setItemText(27, QCoreApplication::translate("cMutationSystemsGroup2", "Spots", nullptr));
        comboBox_mutation_noise_type->setItemText(28, QCoreApplication::translate("cMutationSystemsGroup2", "Speckle", nullptr));
        comboBox_mutation_noise_type->setItemText(29, QCoreApplication::translate("cMutationSystemsGroup2", "Dunes", nullptr));
        comboBox_mutation_noise_type->setItemText(30, QCoreApplication::translate("cMutationSystemsGroup2", "Crackle", nullptr));

        label_noise_factor->setText(QCoreApplication::translate("cMutationSystemsGroup2", "Factor:", nullptr));
        label_noise_param_a->setText(QCoreApplication::translate("cMutationSystemsGroup2", "A:", nullptr));
        label_noise_param_b->setText(QCoreApplication::translate("cMutationSystemsGroup2", "B:", nullptr));
        label_noise_param_c->setText(QCoreApplication::translate("cMutationSystemsGroup2", "C:", nullptr));
        label_noise_param_d->setText(QCoreApplication::translate("cMutationSystemsGroup2", "D:", nullptr));
        label_julia_noise_freq->setText(QCoreApplication::translate("cMutationSystemsGroup2", "Freq:", nullptr));
        label_julia_noise_amp->setText(QCoreApplication::translate("cMutationSystemsGroup2", "Amp:", nullptr));
        label_noise_iter->setText(QCoreApplication::translate("cMutationSystemsGroup2", "Iter:", nullptr));
        label_noise_iter_stop->setText(QCoreApplication::translate("cMutationSystemsGroup2", "Stop:", nullptr));
        groupCheck_mutation_orbit_trap_enabled->setTitle(QCoreApplication::translate("cMutationSystemsGroup2", "Orbit Trap DE", nullptr));
        label_orbit_type->setText(QCoreApplication::translate("cMutationSystemsGroup2", "Orbit Type:", nullptr));
        label2->setText(QCoreApplication::translate("cMutationSystemsGroup2", "Wt", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_mutation_orbit_trap_section_weight->setToolTip(QCoreApplication::translate("cMutationSystemsGroup2", "Section weight: 1=full effect, 0=off", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_mutation_orbit_trap_reset_weights->setText(QCoreApplication::translate("cMutationSystemsGroup2", "Reset", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_mutation_orbit_trap_reset_weights->setToolTip(QCoreApplication::translate("cMutationSystemsGroup2", "Reset this section's weights to 1.0", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_mutation_orbit_trap_type->setItemText(0, QCoreApplication::translate("cMutationSystemsGroup2", "None", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(1, QCoreApplication::translate("cMutationSystemsGroup2", "Sphere Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(2, QCoreApplication::translate("cMutationSystemsGroup2", "Manhattan Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(3, QCoreApplication::translate("cMutationSystemsGroup2", "Chebyshev Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(4, QCoreApplication::translate("cMutationSystemsGroup2", "Cylinder Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(5, QCoreApplication::translate("cMutationSystemsGroup2", "Plane Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(6, QCoreApplication::translate("cMutationSystemsGroup2", "Torus Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(7, QCoreApplication::translate("cMutationSystemsGroup2", "Cross Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(8, QCoreApplication::translate("cMutationSystemsGroup2", "Line Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(9, QCoreApplication::translate("cMutationSystemsGroup2", "Point Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(10, QCoreApplication::translate("cMutationSystemsGroup2", "Box Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(11, QCoreApplication::translate("cMutationSystemsGroup2", "Ellipsoid Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(12, QCoreApplication::translate("cMutationSystemsGroup2", "Cone Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(13, QCoreApplication::translate("cMutationSystemsGroup2", "Hyperboloid Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(14, QCoreApplication::translate("cMutationSystemsGroup2", "Paraboloid Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(15, QCoreApplication::translate("cMutationSystemsGroup2", "Spiral Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(16, QCoreApplication::translate("cMutationSystemsGroup2", "Helix Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(17, QCoreApplication::translate("cMutationSystemsGroup2", "Knot Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(18, QCoreApplication::translate("cMutationSystemsGroup2", "M\303\266bius Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(19, QCoreApplication::translate("cMutationSystemsGroup2", "Gyroid Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(20, QCoreApplication::translate("cMutationSystemsGroup2", "Schwarz-P Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(21, QCoreApplication::translate("cMutationSystemsGroup2", "Schwarz-D Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(22, QCoreApplication::translate("cMutationSystemsGroup2", "Neovius Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(23, QCoreApplication::translate("cMutationSystemsGroup2", "Lidinoid Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(24, QCoreApplication::translate("cMutationSystemsGroup2", "Split-P Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(25, QCoreApplication::translate("cMutationSystemsGroup2", "IWP Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(26, QCoreApplication::translate("cMutationSystemsGroup2", "FRD Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(27, QCoreApplication::translate("cMutationSystemsGroup2", "Tubular-G Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(28, QCoreApplication::translate("cMutationSystemsGroup2", "Tubular-P Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(29, QCoreApplication::translate("cMutationSystemsGroup2", "Custom TPMS Trap", nullptr));
        comboBox_mutation_orbit_trap_type->setItemText(30, QCoreApplication::translate("cMutationSystemsGroup2", "Multi-Trap", nullptr));

        label_orbit_factor->setText(QCoreApplication::translate("cMutationSystemsGroup2", "Factor:", nullptr));
        label_orbit_param_a->setText(QCoreApplication::translate("cMutationSystemsGroup2", "A:", nullptr));
        label_orbit_param_b->setText(QCoreApplication::translate("cMutationSystemsGroup2", "B:", nullptr));
        label_orbit_param_c->setText(QCoreApplication::translate("cMutationSystemsGroup2", "C:", nullptr));
        label_orbit_param_d->setText(QCoreApplication::translate("cMutationSystemsGroup2", "D:", nullptr));
        label_orbit_iter->setText(QCoreApplication::translate("cMutationSystemsGroup2", "Iter:", nullptr));
        label_orbit_iter_stop2->setText(QCoreApplication::translate("cMutationSystemsGroup2", "Stop:", nullptr));
        (void)cMutationSystemsGroup2;
    } // retranslateUi

};

namespace Ui {
    class cMutationSystemsGroup2: public Ui_cMutationSystemsGroup2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUTATION_SYSTEMS_GROUP2_H
