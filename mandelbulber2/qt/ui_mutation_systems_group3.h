/********************************************************************************
** Form generated from reading UI file 'mutation_systems_group3.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUTATION_SYSTEMS_GROUP3_H
#define UI_MUTATION_SYSTEMS_GROUP3_H

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

class Ui_cMutationSystemsGroup3
{
public:
    QVBoxLayout *verticalLayout_cMutationSystemsGroup3;
    MyGroupBox *groupCheck_mutation_torus_enabled;
    QGridLayout *gridLayout_mutation_torus;
    QLabel *label_torus_type;
    QLabel *label;
    MyDoubleSpinBox *spinbox_mutation_torus_section_weight;
    QPushButton *pushButton_mutation_torus_reset_weights;
    QComboBox *comboBox_mutation_torus_type;
    QLabel *label_torus_factor;
    MyDoubleSpinBox *spinbox_mutation_torus_factor;
    QLabel *label_torus_param_a;
    MyDoubleSpinBox *spinbox_mutation_torus_param_a;
    QLabel *label_torus_param_b;
    MyDoubleSpinBox *spinbox_mutation_torus_param_b;
    QLabel *label_torus_param_c;
    MyDoubleSpinBox *spinbox_mutation_torus_param_c;
    QLabel *label_torus_param_d;
    MyDoubleSpinBox *spinbox_mutation_torus_param_d;
    QLabel *label_torus_iter;
    MySpinBox *spinboxInt_mutation_torus_iter_start;
    QLabel *label_torus_iter_stop2;
    MySpinBox *spinboxInt_mutation_torus_iter_stop;
    QPushButton *pushButton_mutation_reset;
    MyGroupBox *groupCheck_mutation_clamp_enabled;
    QGridLayout *gridLayout_clamp;
    QLabel *label_clamp_type;
    QLabel *label1;
    MyDoubleSpinBox *spinbox_mutation_clamp_section_weight;
    QPushButton *pushButton_mutation_clamp_reset_weights;
    QLabel *label_mutation_clamp_factor;
    MyDoubleSpinBox *spinbox_mutation_clamp_factor;
    QLabel *label_mutation_clamp_clamp_param_a;
    MyDoubleSpinBox *spinbox_mutation_clamp_param_a;
    QLabel *label_mutation_clamp_clamp_param_b;
    MyDoubleSpinBox *spinbox_mutation_clamp_param_b;
    QLabel *label_mutation_clamp_clamp_param_c;
    MyDoubleSpinBox *spinbox_mutation_clamp_param_c;
    QLabel *label_mutation_clamp_clamp_param_d;
    MyDoubleSpinBox *spinbox_mutation_clamp_param_d;
    QLabel *label_mutation_clamp_iter_start;
    MySpinBox *spinboxInt_mutation_clamp_iter_start;
    QLabel *label_mutation_clamp_iter_stop;
    MySpinBox *spinboxInt_mutation_clamp_iter_stop;
    QComboBox *comboBox_mutation_clamp_type;
    MyGroupBox *groupCheck_mutation_jb_enabled;
    QGridLayout *gridLayout_jb;
    QLabel *label_jb_type;
    QLabel *label2;
    MyDoubleSpinBox *spinbox_mutation_jb_section_weight;
    QPushButton *pushButton_mutation_jb_reset_weights;
    QLabel *label_mutation_jb_factor;
    MyDoubleSpinBox *spinbox_mutation_jb_factor;
    QLabel *label_mutation_jb_jb_param_a;
    MyDoubleSpinBox *spinbox_mutation_jb_param_a;
    QLabel *label_mutation_jb_jb_param_b;
    MyDoubleSpinBox *spinbox_mutation_jb_param_b;
    QLabel *label_mutation_jb_jb_param_c;
    MyDoubleSpinBox *spinbox_mutation_jb_param_c;
    QLabel *label_mutation_jb_jb_param_d;
    MyDoubleSpinBox *spinbox_mutation_jb_param_d;
    QLabel *label_mutation_jb_iter_start;
    MySpinBox *spinboxInt_mutation_jb_iter_start;
    QLabel *label_mutation_jb_iter_stop;
    MySpinBox *spinboxInt_mutation_jb_iter_stop;
    QComboBox *comboBox_mutation_jb_type;

    void setupUi(QWidget *cMutationSystemsGroup3)
    {
        if (cMutationSystemsGroup3->objectName().isEmpty())
            cMutationSystemsGroup3->setObjectName(QString::fromUtf8("cMutationSystemsGroup3"));
        verticalLayout_cMutationSystemsGroup3 = new QVBoxLayout(cMutationSystemsGroup3);
        verticalLayout_cMutationSystemsGroup3->setSpacing(2);
        verticalLayout_cMutationSystemsGroup3->setObjectName(QString::fromUtf8("verticalLayout_cMutationSystemsGroup3"));
        verticalLayout_cMutationSystemsGroup3->setContentsMargins(0, 0, 0, 0);
        groupCheck_mutation_torus_enabled = new MyGroupBox(cMutationSystemsGroup3);
        groupCheck_mutation_torus_enabled->setObjectName(QString::fromUtf8("groupCheck_mutation_torus_enabled"));
        groupCheck_mutation_torus_enabled->setCheckable(true);
        groupCheck_mutation_torus_enabled->setChecked(false);
        gridLayout_mutation_torus = new QGridLayout(groupCheck_mutation_torus_enabled);
        gridLayout_mutation_torus->setObjectName(QString::fromUtf8("gridLayout_mutation_torus"));
        label_torus_type = new QLabel(groupCheck_mutation_torus_enabled);
        label_torus_type->setObjectName(QString::fromUtf8("label_torus_type"));

        gridLayout_mutation_torus->addWidget(label_torus_type, 0, 0, 1, 1);

        label = new QLabel(groupCheck_mutation_torus_enabled);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout_mutation_torus->addWidget(label, 0, 6, 1, 1);

        spinbox_mutation_torus_section_weight = new MyDoubleSpinBox(groupCheck_mutation_torus_enabled);
        spinbox_mutation_torus_section_weight->setObjectName(QString::fromUtf8("spinbox_mutation_torus_section_weight"));
        spinbox_mutation_torus_section_weight->setMinimum(0.000000000000000);
        spinbox_mutation_torus_section_weight->setMaximum(1.000000000000000);
        spinbox_mutation_torus_section_weight->setSingleStep(0.050000000000000);
        spinbox_mutation_torus_section_weight->setValue(1.000000000000000);
        spinbox_mutation_torus_section_weight->setDecimals(2);
        spinbox_mutation_torus_section_weight->setMinimumSize(QSize(60, 0));

        gridLayout_mutation_torus->addWidget(spinbox_mutation_torus_section_weight, 1, 6, 1, 1);

        pushButton_mutation_torus_reset_weights = new QPushButton(groupCheck_mutation_torus_enabled);
        pushButton_mutation_torus_reset_weights->setObjectName(QString::fromUtf8("pushButton_mutation_torus_reset_weights"));
        pushButton_mutation_torus_reset_weights->setMaximumSize(QSize(60, 16777215));

        gridLayout_mutation_torus->addWidget(pushButton_mutation_torus_reset_weights, 2, 6, 1, 1);

        comboBox_mutation_torus_type = new QComboBox(groupCheck_mutation_torus_enabled);
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->addItem(QString());
        comboBox_mutation_torus_type->setObjectName(QString::fromUtf8("comboBox_mutation_torus_type"));

        gridLayout_mutation_torus->addWidget(comboBox_mutation_torus_type, 0, 1, 1, 5);

        label_torus_factor = new QLabel(groupCheck_mutation_torus_enabled);
        label_torus_factor->setObjectName(QString::fromUtf8("label_torus_factor"));

        gridLayout_mutation_torus->addWidget(label_torus_factor, 1, 0, 1, 1);

        spinbox_mutation_torus_factor = new MyDoubleSpinBox(groupCheck_mutation_torus_enabled);
        spinbox_mutation_torus_factor->setObjectName(QString::fromUtf8("spinbox_mutation_torus_factor"));
        spinbox_mutation_torus_factor->setMinimum(-100.000000000000000);
        spinbox_mutation_torus_factor->setMaximum(100.000000000000000);
        spinbox_mutation_torus_factor->setSingleStep(0.100000000000000);
        spinbox_mutation_torus_factor->setValue(1.000000000000000);
        spinbox_mutation_torus_factor->setDecimals(6);

        gridLayout_mutation_torus->addWidget(spinbox_mutation_torus_factor, 1, 1, 1, 1);

        label_torus_param_a = new QLabel(groupCheck_mutation_torus_enabled);
        label_torus_param_a->setObjectName(QString::fromUtf8("label_torus_param_a"));

        gridLayout_mutation_torus->addWidget(label_torus_param_a, 1, 2, 1, 1);

        spinbox_mutation_torus_param_a = new MyDoubleSpinBox(groupCheck_mutation_torus_enabled);
        spinbox_mutation_torus_param_a->setObjectName(QString::fromUtf8("spinbox_mutation_torus_param_a"));
        spinbox_mutation_torus_param_a->setMinimum(-100.000000000000000);
        spinbox_mutation_torus_param_a->setMaximum(100.000000000000000);
        spinbox_mutation_torus_param_a->setSingleStep(0.100000000000000);
        spinbox_mutation_torus_param_a->setValue(1.000000000000000);
        spinbox_mutation_torus_param_a->setDecimals(6);

        gridLayout_mutation_torus->addWidget(spinbox_mutation_torus_param_a, 1, 3, 1, 1);

        label_torus_param_b = new QLabel(groupCheck_mutation_torus_enabled);
        label_torus_param_b->setObjectName(QString::fromUtf8("label_torus_param_b"));

        gridLayout_mutation_torus->addWidget(label_torus_param_b, 1, 4, 1, 1);

        spinbox_mutation_torus_param_b = new MyDoubleSpinBox(groupCheck_mutation_torus_enabled);
        spinbox_mutation_torus_param_b->setObjectName(QString::fromUtf8("spinbox_mutation_torus_param_b"));
        spinbox_mutation_torus_param_b->setMinimum(-100.000000000000000);
        spinbox_mutation_torus_param_b->setMaximum(100.000000000000000);
        spinbox_mutation_torus_param_b->setSingleStep(0.100000000000000);
        spinbox_mutation_torus_param_b->setValue(1.000000000000000);
        spinbox_mutation_torus_param_b->setDecimals(6);

        gridLayout_mutation_torus->addWidget(spinbox_mutation_torus_param_b, 1, 5, 1, 1);

        label_torus_param_c = new QLabel(groupCheck_mutation_torus_enabled);
        label_torus_param_c->setObjectName(QString::fromUtf8("label_torus_param_c"));

        gridLayout_mutation_torus->addWidget(label_torus_param_c, 2, 0, 1, 1);

        spinbox_mutation_torus_param_c = new MyDoubleSpinBox(groupCheck_mutation_torus_enabled);
        spinbox_mutation_torus_param_c->setObjectName(QString::fromUtf8("spinbox_mutation_torus_param_c"));
        spinbox_mutation_torus_param_c->setMinimum(-100.000000000000000);
        spinbox_mutation_torus_param_c->setMaximum(100.000000000000000);
        spinbox_mutation_torus_param_c->setSingleStep(0.100000000000000);
        spinbox_mutation_torus_param_c->setValue(1.000000000000000);
        spinbox_mutation_torus_param_c->setDecimals(6);

        gridLayout_mutation_torus->addWidget(spinbox_mutation_torus_param_c, 2, 1, 1, 1);

        label_torus_param_d = new QLabel(groupCheck_mutation_torus_enabled);
        label_torus_param_d->setObjectName(QString::fromUtf8("label_torus_param_d"));

        gridLayout_mutation_torus->addWidget(label_torus_param_d, 2, 2, 1, 1);

        spinbox_mutation_torus_param_d = new MyDoubleSpinBox(groupCheck_mutation_torus_enabled);
        spinbox_mutation_torus_param_d->setObjectName(QString::fromUtf8("spinbox_mutation_torus_param_d"));
        spinbox_mutation_torus_param_d->setMinimum(-100.000000000000000);
        spinbox_mutation_torus_param_d->setMaximum(100.000000000000000);
        spinbox_mutation_torus_param_d->setSingleStep(0.100000000000000);
        spinbox_mutation_torus_param_d->setValue(1.000000000000000);
        spinbox_mutation_torus_param_d->setDecimals(6);

        gridLayout_mutation_torus->addWidget(spinbox_mutation_torus_param_d, 2, 3, 1, 1);

        label_torus_iter = new QLabel(groupCheck_mutation_torus_enabled);
        label_torus_iter->setObjectName(QString::fromUtf8("label_torus_iter"));

        gridLayout_mutation_torus->addWidget(label_torus_iter, 2, 4, 1, 1);

        spinboxInt_mutation_torus_iter_start = new MySpinBox(groupCheck_mutation_torus_enabled);
        spinboxInt_mutation_torus_iter_start->setObjectName(QString::fromUtf8("spinboxInt_mutation_torus_iter_start"));
        spinboxInt_mutation_torus_iter_start->setMinimum(0);
        spinboxInt_mutation_torus_iter_start->setMaximum(10000);
        spinboxInt_mutation_torus_iter_start->setValue(0);

        gridLayout_mutation_torus->addWidget(spinboxInt_mutation_torus_iter_start, 2, 5, 1, 1);

        label_torus_iter_stop2 = new QLabel(groupCheck_mutation_torus_enabled);
        label_torus_iter_stop2->setObjectName(QString::fromUtf8("label_torus_iter_stop2"));

        gridLayout_mutation_torus->addWidget(label_torus_iter_stop2, 3, 0, 1, 1);

        spinboxInt_mutation_torus_iter_stop = new MySpinBox(groupCheck_mutation_torus_enabled);
        spinboxInt_mutation_torus_iter_stop->setObjectName(QString::fromUtf8("spinboxInt_mutation_torus_iter_stop"));
        spinboxInt_mutation_torus_iter_stop->setMinimum(0);
        spinboxInt_mutation_torus_iter_stop->setMaximum(10000);
        spinboxInt_mutation_torus_iter_stop->setValue(10000);

        gridLayout_mutation_torus->addWidget(spinboxInt_mutation_torus_iter_stop, 3, 1, 1, 1);

        pushButton_mutation_reset = new QPushButton(groupCheck_mutation_torus_enabled);
        pushButton_mutation_reset->setObjectName(QString::fromUtf8("pushButton_mutation_reset"));

        gridLayout_mutation_torus->addWidget(pushButton_mutation_reset, 4, 0, 1, 7);


        verticalLayout_cMutationSystemsGroup3->addWidget(groupCheck_mutation_torus_enabled);

        groupCheck_mutation_clamp_enabled = new MyGroupBox(cMutationSystemsGroup3);
        groupCheck_mutation_clamp_enabled->setObjectName(QString::fromUtf8("groupCheck_mutation_clamp_enabled"));
        groupCheck_mutation_clamp_enabled->setCheckable(true);
        groupCheck_mutation_clamp_enabled->setChecked(false);
        gridLayout_clamp = new QGridLayout(groupCheck_mutation_clamp_enabled);
        gridLayout_clamp->setObjectName(QString::fromUtf8("gridLayout_clamp"));
        label_clamp_type = new QLabel(groupCheck_mutation_clamp_enabled);
        label_clamp_type->setObjectName(QString::fromUtf8("label_clamp_type"));

        gridLayout_clamp->addWidget(label_clamp_type, 0, 0, 1, 1);

        label1 = new QLabel(groupCheck_mutation_clamp_enabled);
        label1->setObjectName(QString::fromUtf8("label1"));
        label1->setAlignment(Qt::AlignCenter);

        gridLayout_clamp->addWidget(label1, 0, 6, 1, 1);

        spinbox_mutation_clamp_section_weight = new MyDoubleSpinBox(groupCheck_mutation_clamp_enabled);
        spinbox_mutation_clamp_section_weight->setObjectName(QString::fromUtf8("spinbox_mutation_clamp_section_weight"));
        spinbox_mutation_clamp_section_weight->setMinimum(0.000000000000000);
        spinbox_mutation_clamp_section_weight->setMaximum(1.000000000000000);
        spinbox_mutation_clamp_section_weight->setSingleStep(0.050000000000000);
        spinbox_mutation_clamp_section_weight->setValue(1.000000000000000);
        spinbox_mutation_clamp_section_weight->setDecimals(2);
        spinbox_mutation_clamp_section_weight->setMinimumSize(QSize(60, 0));

        gridLayout_clamp->addWidget(spinbox_mutation_clamp_section_weight, 1, 6, 1, 1);

        pushButton_mutation_clamp_reset_weights = new QPushButton(groupCheck_mutation_clamp_enabled);
        pushButton_mutation_clamp_reset_weights->setObjectName(QString::fromUtf8("pushButton_mutation_clamp_reset_weights"));
        pushButton_mutation_clamp_reset_weights->setMaximumSize(QSize(60, 16777215));

        gridLayout_clamp->addWidget(pushButton_mutation_clamp_reset_weights, 2, 6, 1, 1);

        label_mutation_clamp_factor = new QLabel(groupCheck_mutation_clamp_enabled);
        label_mutation_clamp_factor->setObjectName(QString::fromUtf8("label_mutation_clamp_factor"));

        gridLayout_clamp->addWidget(label_mutation_clamp_factor, 1, 0, 1, 1);

        spinbox_mutation_clamp_factor = new MyDoubleSpinBox(groupCheck_mutation_clamp_enabled);
        spinbox_mutation_clamp_factor->setObjectName(QString::fromUtf8("spinbox_mutation_clamp_factor"));
        spinbox_mutation_clamp_factor->setMinimum(-100.000000000000000);
        spinbox_mutation_clamp_factor->setMaximum(100.000000000000000);
        spinbox_mutation_clamp_factor->setSingleStep(0.100000000000000);
        spinbox_mutation_clamp_factor->setValue(1.000000000000000);
        spinbox_mutation_clamp_factor->setDecimals(6);

        gridLayout_clamp->addWidget(spinbox_mutation_clamp_factor, 1, 1, 1, 1);

        label_mutation_clamp_clamp_param_a = new QLabel(groupCheck_mutation_clamp_enabled);
        label_mutation_clamp_clamp_param_a->setObjectName(QString::fromUtf8("label_mutation_clamp_clamp_param_a"));

        gridLayout_clamp->addWidget(label_mutation_clamp_clamp_param_a, 1, 2, 1, 1);

        spinbox_mutation_clamp_param_a = new MyDoubleSpinBox(groupCheck_mutation_clamp_enabled);
        spinbox_mutation_clamp_param_a->setObjectName(QString::fromUtf8("spinbox_mutation_clamp_param_a"));
        spinbox_mutation_clamp_param_a->setMinimum(-100.000000000000000);
        spinbox_mutation_clamp_param_a->setMaximum(100.000000000000000);
        spinbox_mutation_clamp_param_a->setSingleStep(0.100000000000000);
        spinbox_mutation_clamp_param_a->setValue(1.000000000000000);
        spinbox_mutation_clamp_param_a->setDecimals(6);

        gridLayout_clamp->addWidget(spinbox_mutation_clamp_param_a, 1, 3, 1, 1);

        label_mutation_clamp_clamp_param_b = new QLabel(groupCheck_mutation_clamp_enabled);
        label_mutation_clamp_clamp_param_b->setObjectName(QString::fromUtf8("label_mutation_clamp_clamp_param_b"));

        gridLayout_clamp->addWidget(label_mutation_clamp_clamp_param_b, 1, 4, 1, 1);

        spinbox_mutation_clamp_param_b = new MyDoubleSpinBox(groupCheck_mutation_clamp_enabled);
        spinbox_mutation_clamp_param_b->setObjectName(QString::fromUtf8("spinbox_mutation_clamp_param_b"));
        spinbox_mutation_clamp_param_b->setMinimum(-100.000000000000000);
        spinbox_mutation_clamp_param_b->setMaximum(100.000000000000000);
        spinbox_mutation_clamp_param_b->setSingleStep(0.100000000000000);
        spinbox_mutation_clamp_param_b->setValue(1.000000000000000);
        spinbox_mutation_clamp_param_b->setDecimals(6);

        gridLayout_clamp->addWidget(spinbox_mutation_clamp_param_b, 1, 5, 1, 1);

        label_mutation_clamp_clamp_param_c = new QLabel(groupCheck_mutation_clamp_enabled);
        label_mutation_clamp_clamp_param_c->setObjectName(QString::fromUtf8("label_mutation_clamp_clamp_param_c"));

        gridLayout_clamp->addWidget(label_mutation_clamp_clamp_param_c, 2, 0, 1, 1);

        spinbox_mutation_clamp_param_c = new MyDoubleSpinBox(groupCheck_mutation_clamp_enabled);
        spinbox_mutation_clamp_param_c->setObjectName(QString::fromUtf8("spinbox_mutation_clamp_param_c"));
        spinbox_mutation_clamp_param_c->setMinimum(-100.000000000000000);
        spinbox_mutation_clamp_param_c->setMaximum(100.000000000000000);
        spinbox_mutation_clamp_param_c->setSingleStep(0.100000000000000);
        spinbox_mutation_clamp_param_c->setValue(1.000000000000000);
        spinbox_mutation_clamp_param_c->setDecimals(6);

        gridLayout_clamp->addWidget(spinbox_mutation_clamp_param_c, 2, 1, 1, 1);

        label_mutation_clamp_clamp_param_d = new QLabel(groupCheck_mutation_clamp_enabled);
        label_mutation_clamp_clamp_param_d->setObjectName(QString::fromUtf8("label_mutation_clamp_clamp_param_d"));

        gridLayout_clamp->addWidget(label_mutation_clamp_clamp_param_d, 2, 2, 1, 1);

        spinbox_mutation_clamp_param_d = new MyDoubleSpinBox(groupCheck_mutation_clamp_enabled);
        spinbox_mutation_clamp_param_d->setObjectName(QString::fromUtf8("spinbox_mutation_clamp_param_d"));
        spinbox_mutation_clamp_param_d->setMinimum(-100.000000000000000);
        spinbox_mutation_clamp_param_d->setMaximum(100.000000000000000);
        spinbox_mutation_clamp_param_d->setSingleStep(0.100000000000000);
        spinbox_mutation_clamp_param_d->setValue(1.000000000000000);
        spinbox_mutation_clamp_param_d->setDecimals(6);

        gridLayout_clamp->addWidget(spinbox_mutation_clamp_param_d, 2, 3, 1, 1);

        label_mutation_clamp_iter_start = new QLabel(groupCheck_mutation_clamp_enabled);
        label_mutation_clamp_iter_start->setObjectName(QString::fromUtf8("label_mutation_clamp_iter_start"));

        gridLayout_clamp->addWidget(label_mutation_clamp_iter_start, 2, 4, 1, 1);

        spinboxInt_mutation_clamp_iter_start = new MySpinBox(groupCheck_mutation_clamp_enabled);
        spinboxInt_mutation_clamp_iter_start->setObjectName(QString::fromUtf8("spinboxInt_mutation_clamp_iter_start"));
        spinboxInt_mutation_clamp_iter_start->setMinimum(0);
        spinboxInt_mutation_clamp_iter_start->setMaximum(10000);
        spinboxInt_mutation_clamp_iter_start->setValue(0);

        gridLayout_clamp->addWidget(spinboxInt_mutation_clamp_iter_start, 2, 5, 1, 1);

        label_mutation_clamp_iter_stop = new QLabel(groupCheck_mutation_clamp_enabled);
        label_mutation_clamp_iter_stop->setObjectName(QString::fromUtf8("label_mutation_clamp_iter_stop"));

        gridLayout_clamp->addWidget(label_mutation_clamp_iter_stop, 3, 0, 1, 1);

        spinboxInt_mutation_clamp_iter_stop = new MySpinBox(groupCheck_mutation_clamp_enabled);
        spinboxInt_mutation_clamp_iter_stop->setObjectName(QString::fromUtf8("spinboxInt_mutation_clamp_iter_stop"));
        spinboxInt_mutation_clamp_iter_stop->setMinimum(0);
        spinboxInt_mutation_clamp_iter_stop->setMaximum(10000);
        spinboxInt_mutation_clamp_iter_stop->setValue(10000);

        gridLayout_clamp->addWidget(spinboxInt_mutation_clamp_iter_stop, 3, 1, 1, 1);

        comboBox_mutation_clamp_type = new QComboBox(groupCheck_mutation_clamp_enabled);
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->addItem(QString());
        comboBox_mutation_clamp_type->setObjectName(QString::fromUtf8("comboBox_mutation_clamp_type"));

        gridLayout_clamp->addWidget(comboBox_mutation_clamp_type, 0, 1, 1, 5);


        verticalLayout_cMutationSystemsGroup3->addWidget(groupCheck_mutation_clamp_enabled);

        groupCheck_mutation_jb_enabled = new MyGroupBox(cMutationSystemsGroup3);
        groupCheck_mutation_jb_enabled->setObjectName(QString::fromUtf8("groupCheck_mutation_jb_enabled"));
        groupCheck_mutation_jb_enabled->setCheckable(true);
        groupCheck_mutation_jb_enabled->setChecked(false);
        gridLayout_jb = new QGridLayout(groupCheck_mutation_jb_enabled);
        gridLayout_jb->setObjectName(QString::fromUtf8("gridLayout_jb"));
        label_jb_type = new QLabel(groupCheck_mutation_jb_enabled);
        label_jb_type->setObjectName(QString::fromUtf8("label_jb_type"));

        gridLayout_jb->addWidget(label_jb_type, 0, 0, 1, 1);

        label2 = new QLabel(groupCheck_mutation_jb_enabled);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setAlignment(Qt::AlignCenter);

        gridLayout_jb->addWidget(label2, 0, 6, 1, 1);

        spinbox_mutation_jb_section_weight = new MyDoubleSpinBox(groupCheck_mutation_jb_enabled);
        spinbox_mutation_jb_section_weight->setObjectName(QString::fromUtf8("spinbox_mutation_jb_section_weight"));
        spinbox_mutation_jb_section_weight->setMinimum(0.000000000000000);
        spinbox_mutation_jb_section_weight->setMaximum(1.000000000000000);
        spinbox_mutation_jb_section_weight->setSingleStep(0.050000000000000);
        spinbox_mutation_jb_section_weight->setValue(1.000000000000000);
        spinbox_mutation_jb_section_weight->setDecimals(2);
        spinbox_mutation_jb_section_weight->setMinimumSize(QSize(60, 0));

        gridLayout_jb->addWidget(spinbox_mutation_jb_section_weight, 1, 6, 1, 1);

        pushButton_mutation_jb_reset_weights = new QPushButton(groupCheck_mutation_jb_enabled);
        pushButton_mutation_jb_reset_weights->setObjectName(QString::fromUtf8("pushButton_mutation_jb_reset_weights"));
        pushButton_mutation_jb_reset_weights->setMaximumSize(QSize(60, 16777215));

        gridLayout_jb->addWidget(pushButton_mutation_jb_reset_weights, 2, 6, 1, 1);

        label_mutation_jb_factor = new QLabel(groupCheck_mutation_jb_enabled);
        label_mutation_jb_factor->setObjectName(QString::fromUtf8("label_mutation_jb_factor"));

        gridLayout_jb->addWidget(label_mutation_jb_factor, 1, 0, 1, 1);

        spinbox_mutation_jb_factor = new MyDoubleSpinBox(groupCheck_mutation_jb_enabled);
        spinbox_mutation_jb_factor->setObjectName(QString::fromUtf8("spinbox_mutation_jb_factor"));
        spinbox_mutation_jb_factor->setMinimum(-100.000000000000000);
        spinbox_mutation_jb_factor->setMaximum(100.000000000000000);
        spinbox_mutation_jb_factor->setSingleStep(0.100000000000000);
        spinbox_mutation_jb_factor->setValue(1.000000000000000);
        spinbox_mutation_jb_factor->setDecimals(6);

        gridLayout_jb->addWidget(spinbox_mutation_jb_factor, 1, 1, 1, 1);

        label_mutation_jb_jb_param_a = new QLabel(groupCheck_mutation_jb_enabled);
        label_mutation_jb_jb_param_a->setObjectName(QString::fromUtf8("label_mutation_jb_jb_param_a"));

        gridLayout_jb->addWidget(label_mutation_jb_jb_param_a, 1, 2, 1, 1);

        spinbox_mutation_jb_param_a = new MyDoubleSpinBox(groupCheck_mutation_jb_enabled);
        spinbox_mutation_jb_param_a->setObjectName(QString::fromUtf8("spinbox_mutation_jb_param_a"));
        spinbox_mutation_jb_param_a->setMinimum(-100.000000000000000);
        spinbox_mutation_jb_param_a->setMaximum(100.000000000000000);
        spinbox_mutation_jb_param_a->setSingleStep(0.100000000000000);
        spinbox_mutation_jb_param_a->setValue(1.000000000000000);
        spinbox_mutation_jb_param_a->setDecimals(6);

        gridLayout_jb->addWidget(spinbox_mutation_jb_param_a, 1, 3, 1, 1);

        label_mutation_jb_jb_param_b = new QLabel(groupCheck_mutation_jb_enabled);
        label_mutation_jb_jb_param_b->setObjectName(QString::fromUtf8("label_mutation_jb_jb_param_b"));

        gridLayout_jb->addWidget(label_mutation_jb_jb_param_b, 1, 4, 1, 1);

        spinbox_mutation_jb_param_b = new MyDoubleSpinBox(groupCheck_mutation_jb_enabled);
        spinbox_mutation_jb_param_b->setObjectName(QString::fromUtf8("spinbox_mutation_jb_param_b"));
        spinbox_mutation_jb_param_b->setMinimum(-100.000000000000000);
        spinbox_mutation_jb_param_b->setMaximum(100.000000000000000);
        spinbox_mutation_jb_param_b->setSingleStep(0.100000000000000);
        spinbox_mutation_jb_param_b->setValue(1.000000000000000);
        spinbox_mutation_jb_param_b->setDecimals(6);

        gridLayout_jb->addWidget(spinbox_mutation_jb_param_b, 1, 5, 1, 1);

        label_mutation_jb_jb_param_c = new QLabel(groupCheck_mutation_jb_enabled);
        label_mutation_jb_jb_param_c->setObjectName(QString::fromUtf8("label_mutation_jb_jb_param_c"));

        gridLayout_jb->addWidget(label_mutation_jb_jb_param_c, 2, 0, 1, 1);

        spinbox_mutation_jb_param_c = new MyDoubleSpinBox(groupCheck_mutation_jb_enabled);
        spinbox_mutation_jb_param_c->setObjectName(QString::fromUtf8("spinbox_mutation_jb_param_c"));
        spinbox_mutation_jb_param_c->setMinimum(-100.000000000000000);
        spinbox_mutation_jb_param_c->setMaximum(100.000000000000000);
        spinbox_mutation_jb_param_c->setSingleStep(0.100000000000000);
        spinbox_mutation_jb_param_c->setValue(1.000000000000000);
        spinbox_mutation_jb_param_c->setDecimals(6);

        gridLayout_jb->addWidget(spinbox_mutation_jb_param_c, 2, 1, 1, 1);

        label_mutation_jb_jb_param_d = new QLabel(groupCheck_mutation_jb_enabled);
        label_mutation_jb_jb_param_d->setObjectName(QString::fromUtf8("label_mutation_jb_jb_param_d"));

        gridLayout_jb->addWidget(label_mutation_jb_jb_param_d, 2, 2, 1, 1);

        spinbox_mutation_jb_param_d = new MyDoubleSpinBox(groupCheck_mutation_jb_enabled);
        spinbox_mutation_jb_param_d->setObjectName(QString::fromUtf8("spinbox_mutation_jb_param_d"));
        spinbox_mutation_jb_param_d->setMinimum(-100.000000000000000);
        spinbox_mutation_jb_param_d->setMaximum(100.000000000000000);
        spinbox_mutation_jb_param_d->setSingleStep(0.100000000000000);
        spinbox_mutation_jb_param_d->setValue(1.000000000000000);
        spinbox_mutation_jb_param_d->setDecimals(6);

        gridLayout_jb->addWidget(spinbox_mutation_jb_param_d, 2, 3, 1, 1);

        label_mutation_jb_iter_start = new QLabel(groupCheck_mutation_jb_enabled);
        label_mutation_jb_iter_start->setObjectName(QString::fromUtf8("label_mutation_jb_iter_start"));

        gridLayout_jb->addWidget(label_mutation_jb_iter_start, 2, 4, 1, 1);

        spinboxInt_mutation_jb_iter_start = new MySpinBox(groupCheck_mutation_jb_enabled);
        spinboxInt_mutation_jb_iter_start->setObjectName(QString::fromUtf8("spinboxInt_mutation_jb_iter_start"));
        spinboxInt_mutation_jb_iter_start->setMinimum(0);
        spinboxInt_mutation_jb_iter_start->setMaximum(10000);
        spinboxInt_mutation_jb_iter_start->setValue(0);

        gridLayout_jb->addWidget(spinboxInt_mutation_jb_iter_start, 2, 5, 1, 1);

        label_mutation_jb_iter_stop = new QLabel(groupCheck_mutation_jb_enabled);
        label_mutation_jb_iter_stop->setObjectName(QString::fromUtf8("label_mutation_jb_iter_stop"));

        gridLayout_jb->addWidget(label_mutation_jb_iter_stop, 3, 0, 1, 1);

        spinboxInt_mutation_jb_iter_stop = new MySpinBox(groupCheck_mutation_jb_enabled);
        spinboxInt_mutation_jb_iter_stop->setObjectName(QString::fromUtf8("spinboxInt_mutation_jb_iter_stop"));
        spinboxInt_mutation_jb_iter_stop->setMinimum(0);
        spinboxInt_mutation_jb_iter_stop->setMaximum(10000);
        spinboxInt_mutation_jb_iter_stop->setValue(10000);

        gridLayout_jb->addWidget(spinboxInt_mutation_jb_iter_stop, 3, 1, 1, 1);

        comboBox_mutation_jb_type = new QComboBox(groupCheck_mutation_jb_enabled);
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->addItem(QString());
        comboBox_mutation_jb_type->setObjectName(QString::fromUtf8("comboBox_mutation_jb_type"));

        gridLayout_jb->addWidget(comboBox_mutation_jb_type, 0, 1, 1, 5);


        verticalLayout_cMutationSystemsGroup3->addWidget(groupCheck_mutation_jb_enabled);


        retranslateUi(cMutationSystemsGroup3);

        QMetaObject::connectSlotsByName(cMutationSystemsGroup3);
    } // setupUi

    void retranslateUi(QWidget *cMutationSystemsGroup3)
    {
        groupCheck_mutation_torus_enabled->setTitle(QCoreApplication::translate("cMutationSystemsGroup3", "MandelTorus DE", nullptr));
        label_torus_type->setText(QCoreApplication::translate("cMutationSystemsGroup3", "Torus Type:", nullptr));
        label->setText(QCoreApplication::translate("cMutationSystemsGroup3", "Wt", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_mutation_torus_section_weight->setToolTip(QCoreApplication::translate("cMutationSystemsGroup3", "Section weight: 1=full effect, 0=off", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_mutation_torus_reset_weights->setText(QCoreApplication::translate("cMutationSystemsGroup3", "Reset", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_mutation_torus_reset_weights->setToolTip(QCoreApplication::translate("cMutationSystemsGroup3", "Reset this section's weights to 1.0", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_mutation_torus_type->setItemText(0, QCoreApplication::translate("cMutationSystemsGroup3", "None", nullptr));
        comboBox_mutation_torus_type->setItemText(1, QCoreApplication::translate("cMutationSystemsGroup3", "Sigmoid DE", nullptr));
        comboBox_mutation_torus_type->setItemText(2, QCoreApplication::translate("cMutationSystemsGroup3", "Gaussian DE", nullptr));
        comboBox_mutation_torus_type->setItemText(3, QCoreApplication::translate("cMutationSystemsGroup3", "Double-Well DE", nullptr));
        comboBox_mutation_torus_type->setItemText(4, QCoreApplication::translate("cMutationSystemsGroup3", "Plateau DE", nullptr));
        comboBox_mutation_torus_type->setItemText(5, QCoreApplication::translate("cMutationSystemsGroup3", "Asymmetric DE", nullptr));
        comboBox_mutation_torus_type->setItemText(6, QCoreApplication::translate("cMutationSystemsGroup3", "Oscillating DE", nullptr));
        comboBox_mutation_torus_type->setItemText(7, QCoreApplication::translate("cMutationSystemsGroup3", "Step DE", nullptr));
        comboBox_mutation_torus_type->setItemText(8, QCoreApplication::translate("cMutationSystemsGroup3", "Smooth Clamp DE", nullptr));
        comboBox_mutation_torus_type->setItemText(9, QCoreApplication::translate("cMutationSystemsGroup3", "Exponential Plateau", nullptr));
        comboBox_mutation_torus_type->setItemText(10, QCoreApplication::translate("cMutationSystemsGroup3", "Log Barrier DE", nullptr));
        comboBox_mutation_torus_type->setItemText(11, QCoreApplication::translate("cMutationSystemsGroup3", "Inverse Barrier DE", nullptr));
        comboBox_mutation_torus_type->setItemText(12, QCoreApplication::translate("cMutationSystemsGroup3", "Softmin DE", nullptr));
        comboBox_mutation_torus_type->setItemText(13, QCoreApplication::translate("cMutationSystemsGroup3", "Softmax DE", nullptr));
        comboBox_mutation_torus_type->setItemText(14, QCoreApplication::translate("cMutationSystemsGroup3", "Boltzmann DE", nullptr));
        comboBox_mutation_torus_type->setItemText(15, QCoreApplication::translate("cMutationSystemsGroup3", "Fermi-Dirac DE", nullptr));
        comboBox_mutation_torus_type->setItemText(16, QCoreApplication::translate("cMutationSystemsGroup3", "Power Sigmoid DE", nullptr));
        comboBox_mutation_torus_type->setItemText(17, QCoreApplication::translate("cMutationSystemsGroup3", "Tanh Plateau", nullptr));
        comboBox_mutation_torus_type->setItemText(18, QCoreApplication::translate("cMutationSystemsGroup3", "Arctan Plateau", nullptr));
        comboBox_mutation_torus_type->setItemText(19, QCoreApplication::translate("cMutationSystemsGroup3", "Erf Plateau", nullptr));
        comboBox_mutation_torus_type->setItemText(20, QCoreApplication::translate("cMutationSystemsGroup3", "Sech Squared DE", nullptr));
        comboBox_mutation_torus_type->setItemText(21, QCoreApplication::translate("cMutationSystemsGroup3", "Lorentzian DE", nullptr));
        comboBox_mutation_torus_type->setItemText(22, QCoreApplication::translate("cMutationSystemsGroup3", "Voigt Profile DE", nullptr));
        comboBox_mutation_torus_type->setItemText(23, QCoreApplication::translate("cMutationSystemsGroup3", "Pseudo-Voigt DE", nullptr));
        comboBox_mutation_torus_type->setItemText(24, QCoreApplication::translate("cMutationSystemsGroup3", "Asymmetric Gaussian", nullptr));
        comboBox_mutation_torus_type->setItemText(25, QCoreApplication::translate("cMutationSystemsGroup3", "Bifurcation DE", nullptr));
        comboBox_mutation_torus_type->setItemText(26, QCoreApplication::translate("cMutationSystemsGroup3", "Logistic Map DE", nullptr));
        comboBox_mutation_torus_type->setItemText(27, QCoreApplication::translate("cMutationSystemsGroup3", "Henon Map DE", nullptr));
        comboBox_mutation_torus_type->setItemText(28, QCoreApplication::translate("cMutationSystemsGroup3", "Lorenz Attractor DE", nullptr));
        comboBox_mutation_torus_type->setItemText(29, QCoreApplication::translate("cMutationSystemsGroup3", "R\303\266ssler DE", nullptr));
        comboBox_mutation_torus_type->setItemText(30, QCoreApplication::translate("cMutationSystemsGroup3", "Strange Attractor DE", nullptr));

        label_torus_factor->setText(QCoreApplication::translate("cMutationSystemsGroup3", "Factor:", nullptr));
        label_torus_param_a->setText(QCoreApplication::translate("cMutationSystemsGroup3", "A:", nullptr));
        label_torus_param_b->setText(QCoreApplication::translate("cMutationSystemsGroup3", "B:", nullptr));
        label_torus_param_c->setText(QCoreApplication::translate("cMutationSystemsGroup3", "C:", nullptr));
        label_torus_param_d->setText(QCoreApplication::translate("cMutationSystemsGroup3", "D:", nullptr));
        label_torus_iter->setText(QCoreApplication::translate("cMutationSystemsGroup3", "Iter:", nullptr));
        label_torus_iter_stop2->setText(QCoreApplication::translate("cMutationSystemsGroup3", "Stop:", nullptr));
        pushButton_mutation_reset->setText(QCoreApplication::translate("cMutationSystemsGroup3", "Reset Mutation to Defaults", nullptr));
        groupCheck_mutation_clamp_enabled->setTitle(QCoreApplication::translate("cMutationSystemsGroup3", "T Clamp", nullptr));
        label_clamp_type->setText(QCoreApplication::translate("cMutationSystemsGroup3", "Clamp Type:", nullptr));
        label1->setText(QCoreApplication::translate("cMutationSystemsGroup3", "Wt", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_mutation_clamp_section_weight->setToolTip(QCoreApplication::translate("cMutationSystemsGroup3", "Section weight: 1=full effect, 0=off", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_mutation_clamp_reset_weights->setText(QCoreApplication::translate("cMutationSystemsGroup3", "Reset", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_mutation_clamp_reset_weights->setToolTip(QCoreApplication::translate("cMutationSystemsGroup3", "Reset this section's weights to 1.0", nullptr));
#endif // QT_CONFIG(tooltip)
        label_mutation_clamp_factor->setText(QCoreApplication::translate("cMutationSystemsGroup3", "Factor:", nullptr));
        label_mutation_clamp_clamp_param_a->setText(QCoreApplication::translate("cMutationSystemsGroup3", "A:", nullptr));
        label_mutation_clamp_clamp_param_b->setText(QCoreApplication::translate("cMutationSystemsGroup3", "B:", nullptr));
        label_mutation_clamp_clamp_param_c->setText(QCoreApplication::translate("cMutationSystemsGroup3", "C:", nullptr));
        label_mutation_clamp_clamp_param_d->setText(QCoreApplication::translate("cMutationSystemsGroup3", "D:", nullptr));
        label_mutation_clamp_iter_start->setText(QCoreApplication::translate("cMutationSystemsGroup3", "Iter:", nullptr));
        label_mutation_clamp_iter_stop->setText(QCoreApplication::translate("cMutationSystemsGroup3", "Stop:", nullptr));
        comboBox_mutation_clamp_type->setItemText(0, QCoreApplication::translate("cMutationSystemsGroup3", "None", nullptr));
        comboBox_mutation_clamp_type->setItemText(1, QCoreApplication::translate("cMutationSystemsGroup3", "Hard Box Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(2, QCoreApplication::translate("cMutationSystemsGroup3", "Soft Tanh Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(3, QCoreApplication::translate("cMutationSystemsGroup3", "Radial Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(4, QCoreApplication::translate("cMutationSystemsGroup3", "Sphere Inversion Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(5, QCoreApplication::translate("cMutationSystemsGroup3", "Box Fold Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(6, QCoreApplication::translate("cMutationSystemsGroup3", "Cylinder Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(7, QCoreApplication::translate("cMutationSystemsGroup3", "Cone Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(8, QCoreApplication::translate("cMutationSystemsGroup3", "Progressive Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(9, QCoreApplication::translate("cMutationSystemsGroup3", "Sine Oscillating Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(10, QCoreApplication::translate("cMutationSystemsGroup3", "Exponential Decay Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(11, QCoreApplication::translate("cMutationSystemsGroup3", "Orbit-Reactive Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(12, QCoreApplication::translate("cMutationSystemsGroup3", "DE-Reactive Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(13, QCoreApplication::translate("cMutationSystemsGroup3", "Cylinder XY Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(14, QCoreApplication::translate("cMutationSystemsGroup3", "Cylinder + Cone Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(15, QCoreApplication::translate("cMutationSystemsGroup3", "Ellipsoid Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(16, QCoreApplication::translate("cMutationSystemsGroup3", "Torus Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(17, QCoreApplication::translate("cMutationSystemsGroup3", "Sigmoid Smooth Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(18, QCoreApplication::translate("cMutationSystemsGroup3", "Atan Smooth Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(19, QCoreApplication::translate("cMutationSystemsGroup3", "Erf Smooth Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(20, QCoreApplication::translate("cMutationSystemsGroup3", "Log Smooth Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(21, QCoreApplication::translate("cMutationSystemsGroup3", "Hyperbolic Smooth Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(22, QCoreApplication::translate("cMutationSystemsGroup3", "Modular Fold", nullptr));
        comboBox_mutation_clamp_type->setItemText(23, QCoreApplication::translate("cMutationSystemsGroup3", "Sawtooth Fold", nullptr));
        comboBox_mutation_clamp_type->setItemText(24, QCoreApplication::translate("cMutationSystemsGroup3", "Mirror Fold", nullptr));
        comboBox_mutation_clamp_type->setItemText(25, QCoreApplication::translate("cMutationSystemsGroup3", "Bounce Fold", nullptr));
        comboBox_mutation_clamp_type->setItemText(26, QCoreApplication::translate("cMutationSystemsGroup3", "DE-Reactive Clamp v2", nullptr));
        comboBox_mutation_clamp_type->setItemText(27, QCoreApplication::translate("cMutationSystemsGroup3", "Spiral Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(28, QCoreApplication::translate("cMutationSystemsGroup3", "Wave Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(29, QCoreApplication::translate("cMutationSystemsGroup3", "Octahedral Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(30, QCoreApplication::translate("cMutationSystemsGroup3", "Diamond Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(31, QCoreApplication::translate("cMutationSystemsGroup3", "Inverse Radial Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(32, QCoreApplication::translate("cMutationSystemsGroup3", "Power Smooth Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(33, QCoreApplication::translate("cMutationSystemsGroup3", "Iteration Fade Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(34, QCoreApplication::translate("cMutationSystemsGroup3", "Axis-Selective Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(35, QCoreApplication::translate("cMutationSystemsGroup3", "Min-Axis Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(36, QCoreApplication::translate("cMutationSystemsGroup3", "Gradient Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(37, QCoreApplication::translate("cMutationSystemsGroup3", "DE-Scaled Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(38, QCoreApplication::translate("cMutationSystemsGroup3", "Orbit-Orbit Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(39, QCoreApplication::translate("cMutationSystemsGroup3", "Modulo Wrap", nullptr));
        comboBox_mutation_clamp_type->setItemText(40, QCoreApplication::translate("cMutationSystemsGroup3", "Triangle Fold", nullptr));
        comboBox_mutation_clamp_type->setItemText(41, QCoreApplication::translate("cMutationSystemsGroup3", "Smooth Step Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(42, QCoreApplication::translate("cMutationSystemsGroup3", "Double Sided Box", nullptr));
        comboBox_mutation_clamp_type->setItemText(43, QCoreApplication::translate("cMutationSystemsGroup3", "Capsule Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(44, QCoreApplication::translate("cMutationSystemsGroup3", "Superellipsoid Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(45, QCoreApplication::translate("cMutationSystemsGroup3", "Abs Fold Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(46, QCoreApplication::translate("cMutationSystemsGroup3", "Cross Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(47, QCoreApplication::translate("cMutationSystemsGroup3", "Hex Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(48, QCoreApplication::translate("cMutationSystemsGroup3", "Twist Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(49, QCoreApplication::translate("cMutationSystemsGroup3", "Fractal Clamp", nullptr));
        comboBox_mutation_clamp_type->setItemText(50, QCoreApplication::translate("cMutationSystemsGroup3", "Ultra Smooth Clamp", nullptr));

        groupCheck_mutation_jb_enabled->setTitle(QCoreApplication::translate("cMutationSystemsGroup3", "T Julia Box", nullptr));
        label_jb_type->setText(QCoreApplication::translate("cMutationSystemsGroup3", "Julia Box Type:", nullptr));
        label2->setText(QCoreApplication::translate("cMutationSystemsGroup3", "Wt", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_mutation_jb_section_weight->setToolTip(QCoreApplication::translate("cMutationSystemsGroup3", "Section weight: 1=full effect, 0=off", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_mutation_jb_reset_weights->setText(QCoreApplication::translate("cMutationSystemsGroup3", "Reset", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_mutation_jb_reset_weights->setToolTip(QCoreApplication::translate("cMutationSystemsGroup3", "Reset this section's weights to 1.0", nullptr));
#endif // QT_CONFIG(tooltip)
        label_mutation_jb_factor->setText(QCoreApplication::translate("cMutationSystemsGroup3", "Factor:", nullptr));
        label_mutation_jb_jb_param_a->setText(QCoreApplication::translate("cMutationSystemsGroup3", "A:", nullptr));
        label_mutation_jb_jb_param_b->setText(QCoreApplication::translate("cMutationSystemsGroup3", "B:", nullptr));
        label_mutation_jb_jb_param_c->setText(QCoreApplication::translate("cMutationSystemsGroup3", "C:", nullptr));
        label_mutation_jb_jb_param_d->setText(QCoreApplication::translate("cMutationSystemsGroup3", "D:", nullptr));
        label_mutation_jb_iter_start->setText(QCoreApplication::translate("cMutationSystemsGroup3", "Iter:", nullptr));
        label_mutation_jb_iter_stop->setText(QCoreApplication::translate("cMutationSystemsGroup3", "Stop:", nullptr));
        comboBox_mutation_jb_type->setItemText(0, QCoreApplication::translate("cMutationSystemsGroup3", "None", nullptr));
        comboBox_mutation_jb_type->setItemText(1, QCoreApplication::translate("cMutationSystemsGroup3", "Standard Julia Box", nullptr));
        comboBox_mutation_jb_type->setItemText(2, QCoreApplication::translate("cMutationSystemsGroup3", "Rotated Julia Box", nullptr));
        comboBox_mutation_jb_type->setItemText(3, QCoreApplication::translate("cMutationSystemsGroup3", "Mandelbox Classic", nullptr));
        comboBox_mutation_jb_type->setItemText(4, QCoreApplication::translate("cMutationSystemsGroup3", "Amazing Box", nullptr));
        comboBox_mutation_jb_type->setItemText(5, QCoreApplication::translate("cMutationSystemsGroup3", "Sierpinski Fold", nullptr));
        comboBox_mutation_jb_type->setItemText(6, QCoreApplication::translate("cMutationSystemsGroup3", "Menger Fold", nullptr));
        comboBox_mutation_jb_type->setItemText(7, QCoreApplication::translate("cMutationSystemsGroup3", "Kaleidoscopic IFS", nullptr));
        comboBox_mutation_jb_type->setItemText(8, QCoreApplication::translate("cMutationSystemsGroup3", "Twist Box", nullptr));
        comboBox_mutation_jb_type->setItemText(9, QCoreApplication::translate("cMutationSystemsGroup3", "Polar Box", nullptr));
        comboBox_mutation_jb_type->setItemText(10, QCoreApplication::translate("cMutationSystemsGroup3", "Gyroid Fold", nullptr));
        comboBox_mutation_jb_type->setItemText(11, QCoreApplication::translate("cMutationSystemsGroup3", "Quaternion Fold", nullptr));
        comboBox_mutation_jb_type->setItemText(12, QCoreApplication::translate("cMutationSystemsGroup3", "Smooth Fold", nullptr));
        comboBox_mutation_jb_type->setItemText(13, QCoreApplication::translate("cMutationSystemsGroup3", "Cubic Fold", nullptr));
        comboBox_mutation_jb_type->setItemText(14, QCoreApplication::translate("cMutationSystemsGroup3", "Cascade Fold", nullptr));
        comboBox_mutation_jb_type->setItemText(15, QCoreApplication::translate("cMutationSystemsGroup3", "Anti-Fold", nullptr));
        comboBox_mutation_jb_type->setItemText(16, QCoreApplication::translate("cMutationSystemsGroup3", "DE-Reactive Box", nullptr));
        comboBox_mutation_jb_type->setItemText(17, QCoreApplication::translate("cMutationSystemsGroup3", "Animated Julia Box", nullptr));
        comboBox_mutation_jb_type->setItemText(18, QCoreApplication::translate("cMutationSystemsGroup3", "Color-Reactive Fold", nullptr));
        comboBox_mutation_jb_type->setItemText(19, QCoreApplication::translate("cMutationSystemsGroup3", "Noise Fold", nullptr));
        comboBox_mutation_jb_type->setItemText(20, QCoreApplication::translate("cMutationSystemsGroup3", "Hexagonal Fold", nullptr));
        comboBox_mutation_jb_type->setItemText(21, QCoreApplication::translate("cMutationSystemsGroup3", "Orbit-Reactive Box", nullptr));
        comboBox_mutation_jb_type->setItemText(22, QCoreApplication::translate("cMutationSystemsGroup3", "Scale Pulse Box", nullptr));
        comboBox_mutation_jb_type->setItemText(23, QCoreApplication::translate("cMutationSystemsGroup3", "Mirror Julia", nullptr));
        comboBox_mutation_jb_type->setItemText(24, QCoreApplication::translate("cMutationSystemsGroup3", "Hyperbolic Box", nullptr));
        comboBox_mutation_jb_type->setItemText(25, QCoreApplication::translate("cMutationSystemsGroup3", "Spherical Fold Box", nullptr));
        comboBox_mutation_jb_type->setItemText(26, QCoreApplication::translate("cMutationSystemsGroup3", "Exp Julia Box", nullptr));
        comboBox_mutation_jb_type->setItemText(27, QCoreApplication::translate("cMutationSystemsGroup3", "Logarithmic Fold", nullptr));
        comboBox_mutation_jb_type->setItemText(28, QCoreApplication::translate("cMutationSystemsGroup3", "Sin Fold Box", nullptr));
        comboBox_mutation_jb_type->setItemText(29, QCoreApplication::translate("cMutationSystemsGroup3", "Tan Fold Box", nullptr));
        comboBox_mutation_jb_type->setItemText(30, QCoreApplication::translate("cMutationSystemsGroup3", "Abs Julia Box", nullptr));
        comboBox_mutation_jb_type->setItemText(31, QCoreApplication::translate("cMutationSystemsGroup3", "Power Fold", nullptr));
        comboBox_mutation_jb_type->setItemText(32, QCoreApplication::translate("cMutationSystemsGroup3", "Iteration-Fade Box", nullptr));
        comboBox_mutation_jb_type->setItemText(33, QCoreApplication::translate("cMutationSystemsGroup3", "Progressive Box", nullptr));
        comboBox_mutation_jb_type->setItemText(34, QCoreApplication::translate("cMutationSystemsGroup3", "Loxodromic Fold", nullptr));
        comboBox_mutation_jb_type->setItemText(35, QCoreApplication::translate("cMutationSystemsGroup3", "Kleinian Fold", nullptr));
        comboBox_mutation_jb_type->setItemText(36, QCoreApplication::translate("cMutationSystemsGroup3", "Cross Fold", nullptr));
        comboBox_mutation_jb_type->setItemText(37, QCoreApplication::translate("cMutationSystemsGroup3", "Star Fold", nullptr));
        comboBox_mutation_jb_type->setItemText(38, QCoreApplication::translate("cMutationSystemsGroup3", "Spiral Fold", nullptr));
        comboBox_mutation_jb_type->setItemText(39, QCoreApplication::translate("cMutationSystemsGroup3", "Vortex Box", nullptr));
        comboBox_mutation_jb_type->setItemText(40, QCoreApplication::translate("cMutationSystemsGroup3", "Turbulence Box", nullptr));
        comboBox_mutation_jb_type->setItemText(41, QCoreApplication::translate("cMutationSystemsGroup3", "Ripple Fold", nullptr));
        comboBox_mutation_jb_type->setItemText(42, QCoreApplication::translate("cMutationSystemsGroup3", "Mandala Fold", nullptr));
        comboBox_mutation_jb_type->setItemText(43, QCoreApplication::translate("cMutationSystemsGroup3", "Diamond Fold", nullptr));
        comboBox_mutation_jb_type->setItemText(44, QCoreApplication::translate("cMutationSystemsGroup3", "Multi-Scale Box", nullptr));
        comboBox_mutation_jb_type->setItemText(45, QCoreApplication::translate("cMutationSystemsGroup3", "Phase-Shift Box", nullptr));
        comboBox_mutation_jb_type->setItemText(46, QCoreApplication::translate("cMutationSystemsGroup3", "Frequency Box", nullptr));
        comboBox_mutation_jb_type->setItemText(47, QCoreApplication::translate("cMutationSystemsGroup3", "Damped Box", nullptr));
        comboBox_mutation_jb_type->setItemText(48, QCoreApplication::translate("cMutationSystemsGroup3", "Resonance Box", nullptr));
        comboBox_mutation_jb_type->setItemText(49, QCoreApplication::translate("cMutationSystemsGroup3", "Chaos Box", nullptr));
        comboBox_mutation_jb_type->setItemText(50, QCoreApplication::translate("cMutationSystemsGroup3", "Ultra Julia Box", nullptr));

        (void)cMutationSystemsGroup3;
    } // retranslateUi

};

namespace Ui {
    class cMutationSystemsGroup3: public Ui_cMutationSystemsGroup3 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUTATION_SYSTEMS_GROUP3_H
