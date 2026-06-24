/********************************************************************************
** Form generated from reading UI file 'mutation_jos_pk_panel.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUTATION_JOS_PK_PANEL_H
#define UI_MUTATION_JOS_PK_PANEL_H

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

class Ui_cMutationJosPkPanel
{
public:
    QVBoxLayout *verticalLayout_mutation_jos_pk;
    MyGroupBox *groupCheck_mutation_jos_leys_enabled;
    QGridLayout *gridLayout_mutation_jos_leys;
    QLabel *label_jos_type;
    QLabel *label;
    MyDoubleSpinBox *spinbox_mutation_jos_leys_section_weight;
    QPushButton *pushButton_mutation_jos_leys_reset_weights;
    QComboBox *comboBox_mutation_jos_de_type;
    QLabel *label_jos_factor;
    MyDoubleSpinBox *spinbox_mutation_jos_factor;
    QLabel *label_jos_scale;
    MyDoubleSpinBox *spinbox_mutation_jos_scale;
    QLabel *label_jos_phase;
    MyDoubleSpinBox *spinbox_mutation_jos_phase;
    QLabel *label_jos_param_a;
    MyDoubleSpinBox *spinbox_mutation_jos_param_a;
    QLabel *label_jos_param_b;
    MyDoubleSpinBox *spinbox_mutation_jos_param_b;
    QLabel *label_jos_param_c;
    MyDoubleSpinBox *spinbox_mutation_jos_param_c;
    QLabel *label_jos_param_d;
    MyDoubleSpinBox *spinbox_mutation_jos_param_d;
    QLabel *label_jos_freq;
    MyDoubleSpinBox *spinbox_mutation_jos_freq;
    QLabel *label_jos_amp;
    MyDoubleSpinBox *spinbox_mutation_jos_amp;
    QLabel *label_jos_iter;
    MySpinBox *spinboxInt_mutation_jos_iter_start;
    QLabel *label_jos_iter_stop;
    MySpinBox *spinboxInt_mutation_jos_iter_stop;
    MyGroupBox *groupCheck_mutation_pk_enabled;
    QGridLayout *gridLayout_mutation_pk;
    QLabel *label_pk_type;
    QLabel *label1;
    MyDoubleSpinBox *spinbox_mutation_pk_section_weight;
    QPushButton *pushButton_mutation_pk_reset_weights;
    QComboBox *comboBox_mutation_pk_de_type;
    QLabel *label_pk_factor;
    MyDoubleSpinBox *spinbox_mutation_pk_factor;
    QLabel *label_pk_scale;
    MyDoubleSpinBox *spinbox_mutation_pk_scale;
    QLabel *label_pk_phase;
    MyDoubleSpinBox *spinbox_mutation_pk_phase;
    QLabel *label_pk_param_a;
    MyDoubleSpinBox *spinbox_mutation_pk_param_a;
    QLabel *label_pk_param_b;
    MyDoubleSpinBox *spinbox_mutation_pk_param_b;
    QLabel *label_pk_param_c;
    MyDoubleSpinBox *spinbox_mutation_pk_param_c;
    QLabel *label_pk_param_d;
    MyDoubleSpinBox *spinbox_mutation_pk_param_d;
    QLabel *label_pk_freq;
    MyDoubleSpinBox *spinbox_mutation_pk_freq;
    QLabel *label_pk_amp;
    MyDoubleSpinBox *spinbox_mutation_pk_amp;
    QLabel *label_pk_iter;
    MySpinBox *spinboxInt_mutation_pk_iter_start;
    QLabel *label_pk_iter_stop;
    MySpinBox *spinboxInt_mutation_pk_iter_stop;

    void setupUi(QWidget *cMutationJosPkPanel)
    {
        if (cMutationJosPkPanel->objectName().isEmpty())
            cMutationJosPkPanel->setObjectName(QString::fromUtf8("cMutationJosPkPanel"));
        verticalLayout_mutation_jos_pk = new QVBoxLayout(cMutationJosPkPanel);
        verticalLayout_mutation_jos_pk->setSpacing(2);
        verticalLayout_mutation_jos_pk->setObjectName(QString::fromUtf8("verticalLayout_mutation_jos_pk"));
        verticalLayout_mutation_jos_pk->setContentsMargins(0, 0, 0, 0);
        groupCheck_mutation_jos_leys_enabled = new MyGroupBox(cMutationJosPkPanel);
        groupCheck_mutation_jos_leys_enabled->setObjectName(QString::fromUtf8("groupCheck_mutation_jos_leys_enabled"));
        groupCheck_mutation_jos_leys_enabled->setCheckable(true);
        groupCheck_mutation_jos_leys_enabled->setChecked(false);
        gridLayout_mutation_jos_leys = new QGridLayout(groupCheck_mutation_jos_leys_enabled);
        gridLayout_mutation_jos_leys->setObjectName(QString::fromUtf8("gridLayout_mutation_jos_leys"));
        label_jos_type = new QLabel(groupCheck_mutation_jos_leys_enabled);
        label_jos_type->setObjectName(QString::fromUtf8("label_jos_type"));

        gridLayout_mutation_jos_leys->addWidget(label_jos_type, 0, 0, 1, 1);

        label = new QLabel(groupCheck_mutation_jos_leys_enabled);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout_mutation_jos_leys->addWidget(label, 0, 6, 1, 1);

        spinbox_mutation_jos_leys_section_weight = new MyDoubleSpinBox(groupCheck_mutation_jos_leys_enabled);
        spinbox_mutation_jos_leys_section_weight->setObjectName(QString::fromUtf8("spinbox_mutation_jos_leys_section_weight"));
        spinbox_mutation_jos_leys_section_weight->setMinimum(0.000000000000000);
        spinbox_mutation_jos_leys_section_weight->setMaximum(1.000000000000000);
        spinbox_mutation_jos_leys_section_weight->setSingleStep(0.050000000000000);
        spinbox_mutation_jos_leys_section_weight->setValue(1.000000000000000);
        spinbox_mutation_jos_leys_section_weight->setDecimals(2);
        spinbox_mutation_jos_leys_section_weight->setMinimumSize(QSize(60, 0));

        gridLayout_mutation_jos_leys->addWidget(spinbox_mutation_jos_leys_section_weight, 1, 6, 1, 1);

        pushButton_mutation_jos_leys_reset_weights = new QPushButton(groupCheck_mutation_jos_leys_enabled);
        pushButton_mutation_jos_leys_reset_weights->setObjectName(QString::fromUtf8("pushButton_mutation_jos_leys_reset_weights"));
        pushButton_mutation_jos_leys_reset_weights->setMaximumSize(QSize(60, 16777215));

        gridLayout_mutation_jos_leys->addWidget(pushButton_mutation_jos_leys_reset_weights, 2, 6, 1, 1);

        comboBox_mutation_jos_de_type = new QComboBox(groupCheck_mutation_jos_leys_enabled);
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->addItem(QString());
        comboBox_mutation_jos_de_type->setObjectName(QString::fromUtf8("comboBox_mutation_jos_de_type"));

        gridLayout_mutation_jos_leys->addWidget(comboBox_mutation_jos_de_type, 0, 1, 1, 5);

        label_jos_factor = new QLabel(groupCheck_mutation_jos_leys_enabled);
        label_jos_factor->setObjectName(QString::fromUtf8("label_jos_factor"));

        gridLayout_mutation_jos_leys->addWidget(label_jos_factor, 1, 0, 1, 1);

        spinbox_mutation_jos_factor = new MyDoubleSpinBox(groupCheck_mutation_jos_leys_enabled);
        spinbox_mutation_jos_factor->setObjectName(QString::fromUtf8("spinbox_mutation_jos_factor"));
        spinbox_mutation_jos_factor->setMinimum(-100.000000000000000);
        spinbox_mutation_jos_factor->setMaximum(100.000000000000000);
        spinbox_mutation_jos_factor->setSingleStep(0.100000000000000);
        spinbox_mutation_jos_factor->setValue(1.000000000000000);
        spinbox_mutation_jos_factor->setDecimals(6);

        gridLayout_mutation_jos_leys->addWidget(spinbox_mutation_jos_factor, 1, 1, 1, 1);

        label_jos_scale = new QLabel(groupCheck_mutation_jos_leys_enabled);
        label_jos_scale->setObjectName(QString::fromUtf8("label_jos_scale"));

        gridLayout_mutation_jos_leys->addWidget(label_jos_scale, 1, 2, 1, 1);

        spinbox_mutation_jos_scale = new MyDoubleSpinBox(groupCheck_mutation_jos_leys_enabled);
        spinbox_mutation_jos_scale->setObjectName(QString::fromUtf8("spinbox_mutation_jos_scale"));
        spinbox_mutation_jos_scale->setMinimum(-100.000000000000000);
        spinbox_mutation_jos_scale->setMaximum(100.000000000000000);
        spinbox_mutation_jos_scale->setSingleStep(0.100000000000000);
        spinbox_mutation_jos_scale->setValue(1.000000000000000);
        spinbox_mutation_jos_scale->setDecimals(6);

        gridLayout_mutation_jos_leys->addWidget(spinbox_mutation_jos_scale, 1, 3, 1, 1);

        label_jos_phase = new QLabel(groupCheck_mutation_jos_leys_enabled);
        label_jos_phase->setObjectName(QString::fromUtf8("label_jos_phase"));

        gridLayout_mutation_jos_leys->addWidget(label_jos_phase, 1, 4, 1, 1);

        spinbox_mutation_jos_phase = new MyDoubleSpinBox(groupCheck_mutation_jos_leys_enabled);
        spinbox_mutation_jos_phase->setObjectName(QString::fromUtf8("spinbox_mutation_jos_phase"));
        spinbox_mutation_jos_phase->setMinimum(-360.000000000000000);
        spinbox_mutation_jos_phase->setMaximum(360.000000000000000);
        spinbox_mutation_jos_phase->setSingleStep(1.000000000000000);
        spinbox_mutation_jos_phase->setValue(0.000000000000000);
        spinbox_mutation_jos_phase->setDecimals(3);

        gridLayout_mutation_jos_leys->addWidget(spinbox_mutation_jos_phase, 1, 5, 1, 1);

        label_jos_param_a = new QLabel(groupCheck_mutation_jos_leys_enabled);
        label_jos_param_a->setObjectName(QString::fromUtf8("label_jos_param_a"));

        gridLayout_mutation_jos_leys->addWidget(label_jos_param_a, 2, 0, 1, 1);

        spinbox_mutation_jos_param_a = new MyDoubleSpinBox(groupCheck_mutation_jos_leys_enabled);
        spinbox_mutation_jos_param_a->setObjectName(QString::fromUtf8("spinbox_mutation_jos_param_a"));
        spinbox_mutation_jos_param_a->setMinimum(-100.000000000000000);
        spinbox_mutation_jos_param_a->setMaximum(100.000000000000000);
        spinbox_mutation_jos_param_a->setSingleStep(0.100000000000000);
        spinbox_mutation_jos_param_a->setValue(1.000000000000000);
        spinbox_mutation_jos_param_a->setDecimals(6);

        gridLayout_mutation_jos_leys->addWidget(spinbox_mutation_jos_param_a, 2, 1, 1, 1);

        label_jos_param_b = new QLabel(groupCheck_mutation_jos_leys_enabled);
        label_jos_param_b->setObjectName(QString::fromUtf8("label_jos_param_b"));

        gridLayout_mutation_jos_leys->addWidget(label_jos_param_b, 2, 2, 1, 1);

        spinbox_mutation_jos_param_b = new MyDoubleSpinBox(groupCheck_mutation_jos_leys_enabled);
        spinbox_mutation_jos_param_b->setObjectName(QString::fromUtf8("spinbox_mutation_jos_param_b"));
        spinbox_mutation_jos_param_b->setMinimum(-100.000000000000000);
        spinbox_mutation_jos_param_b->setMaximum(100.000000000000000);
        spinbox_mutation_jos_param_b->setSingleStep(0.100000000000000);
        spinbox_mutation_jos_param_b->setValue(1.000000000000000);
        spinbox_mutation_jos_param_b->setDecimals(6);

        gridLayout_mutation_jos_leys->addWidget(spinbox_mutation_jos_param_b, 2, 3, 1, 1);

        label_jos_param_c = new QLabel(groupCheck_mutation_jos_leys_enabled);
        label_jos_param_c->setObjectName(QString::fromUtf8("label_jos_param_c"));

        gridLayout_mutation_jos_leys->addWidget(label_jos_param_c, 2, 4, 1, 1);

        spinbox_mutation_jos_param_c = new MyDoubleSpinBox(groupCheck_mutation_jos_leys_enabled);
        spinbox_mutation_jos_param_c->setObjectName(QString::fromUtf8("spinbox_mutation_jos_param_c"));
        spinbox_mutation_jos_param_c->setMinimum(-100.000000000000000);
        spinbox_mutation_jos_param_c->setMaximum(100.000000000000000);
        spinbox_mutation_jos_param_c->setSingleStep(0.100000000000000);
        spinbox_mutation_jos_param_c->setValue(1.000000000000000);
        spinbox_mutation_jos_param_c->setDecimals(6);

        gridLayout_mutation_jos_leys->addWidget(spinbox_mutation_jos_param_c, 2, 5, 1, 1);

        label_jos_param_d = new QLabel(groupCheck_mutation_jos_leys_enabled);
        label_jos_param_d->setObjectName(QString::fromUtf8("label_jos_param_d"));

        gridLayout_mutation_jos_leys->addWidget(label_jos_param_d, 3, 0, 1, 1);

        spinbox_mutation_jos_param_d = new MyDoubleSpinBox(groupCheck_mutation_jos_leys_enabled);
        spinbox_mutation_jos_param_d->setObjectName(QString::fromUtf8("spinbox_mutation_jos_param_d"));
        spinbox_mutation_jos_param_d->setMinimum(-100.000000000000000);
        spinbox_mutation_jos_param_d->setMaximum(100.000000000000000);
        spinbox_mutation_jos_param_d->setSingleStep(0.100000000000000);
        spinbox_mutation_jos_param_d->setValue(1.000000000000000);
        spinbox_mutation_jos_param_d->setDecimals(6);

        gridLayout_mutation_jos_leys->addWidget(spinbox_mutation_jos_param_d, 3, 1, 1, 1);

        label_jos_freq = new QLabel(groupCheck_mutation_jos_leys_enabled);
        label_jos_freq->setObjectName(QString::fromUtf8("label_jos_freq"));

        gridLayout_mutation_jos_leys->addWidget(label_jos_freq, 3, 2, 1, 1);

        spinbox_mutation_jos_freq = new MyDoubleSpinBox(groupCheck_mutation_jos_leys_enabled);
        spinbox_mutation_jos_freq->setObjectName(QString::fromUtf8("spinbox_mutation_jos_freq"));
        spinbox_mutation_jos_freq->setMinimum(0.010000000000000);
        spinbox_mutation_jos_freq->setMaximum(100.000000000000000);
        spinbox_mutation_jos_freq->setSingleStep(0.100000000000000);
        spinbox_mutation_jos_freq->setValue(1.000000000000000);
        spinbox_mutation_jos_freq->setDecimals(6);

        gridLayout_mutation_jos_leys->addWidget(spinbox_mutation_jos_freq, 3, 3, 1, 1);

        label_jos_amp = new QLabel(groupCheck_mutation_jos_leys_enabled);
        label_jos_amp->setObjectName(QString::fromUtf8("label_jos_amp"));

        gridLayout_mutation_jos_leys->addWidget(label_jos_amp, 3, 4, 1, 1);

        spinbox_mutation_jos_amp = new MyDoubleSpinBox(groupCheck_mutation_jos_leys_enabled);
        spinbox_mutation_jos_amp->setObjectName(QString::fromUtf8("spinbox_mutation_jos_amp"));
        spinbox_mutation_jos_amp->setMinimum(-10.000000000000000);
        spinbox_mutation_jos_amp->setMaximum(10.000000000000000);
        spinbox_mutation_jos_amp->setSingleStep(0.100000000000000);
        spinbox_mutation_jos_amp->setValue(0.500000000000000);
        spinbox_mutation_jos_amp->setDecimals(6);

        gridLayout_mutation_jos_leys->addWidget(spinbox_mutation_jos_amp, 3, 5, 1, 1);

        label_jos_iter = new QLabel(groupCheck_mutation_jos_leys_enabled);
        label_jos_iter->setObjectName(QString::fromUtf8("label_jos_iter"));

        gridLayout_mutation_jos_leys->addWidget(label_jos_iter, 4, 0, 1, 1);

        spinboxInt_mutation_jos_iter_start = new MySpinBox(groupCheck_mutation_jos_leys_enabled);
        spinboxInt_mutation_jos_iter_start->setObjectName(QString::fromUtf8("spinboxInt_mutation_jos_iter_start"));
        spinboxInt_mutation_jos_iter_start->setMinimum(0);
        spinboxInt_mutation_jos_iter_start->setMaximum(10000);
        spinboxInt_mutation_jos_iter_start->setValue(0);

        gridLayout_mutation_jos_leys->addWidget(spinboxInt_mutation_jos_iter_start, 4, 1, 1, 1);

        label_jos_iter_stop = new QLabel(groupCheck_mutation_jos_leys_enabled);
        label_jos_iter_stop->setObjectName(QString::fromUtf8("label_jos_iter_stop"));

        gridLayout_mutation_jos_leys->addWidget(label_jos_iter_stop, 4, 2, 1, 1);

        spinboxInt_mutation_jos_iter_stop = new MySpinBox(groupCheck_mutation_jos_leys_enabled);
        spinboxInt_mutation_jos_iter_stop->setObjectName(QString::fromUtf8("spinboxInt_mutation_jos_iter_stop"));
        spinboxInt_mutation_jos_iter_stop->setMinimum(0);
        spinboxInt_mutation_jos_iter_stop->setMaximum(10000);
        spinboxInt_mutation_jos_iter_stop->setValue(10000);

        gridLayout_mutation_jos_leys->addWidget(spinboxInt_mutation_jos_iter_stop, 4, 3, 1, 1);


        verticalLayout_mutation_jos_pk->addWidget(groupCheck_mutation_jos_leys_enabled);

        groupCheck_mutation_pk_enabled = new MyGroupBox(cMutationJosPkPanel);
        groupCheck_mutation_pk_enabled->setObjectName(QString::fromUtf8("groupCheck_mutation_pk_enabled"));
        groupCheck_mutation_pk_enabled->setCheckable(true);
        groupCheck_mutation_pk_enabled->setChecked(false);
        gridLayout_mutation_pk = new QGridLayout(groupCheck_mutation_pk_enabled);
        gridLayout_mutation_pk->setObjectName(QString::fromUtf8("gridLayout_mutation_pk"));
        label_pk_type = new QLabel(groupCheck_mutation_pk_enabled);
        label_pk_type->setObjectName(QString::fromUtf8("label_pk_type"));

        gridLayout_mutation_pk->addWidget(label_pk_type, 0, 0, 1, 1);

        label1 = new QLabel(groupCheck_mutation_pk_enabled);
        label1->setObjectName(QString::fromUtf8("label1"));
        label1->setAlignment(Qt::AlignCenter);

        gridLayout_mutation_pk->addWidget(label1, 0, 6, 1, 1);

        spinbox_mutation_pk_section_weight = new MyDoubleSpinBox(groupCheck_mutation_pk_enabled);
        spinbox_mutation_pk_section_weight->setObjectName(QString::fromUtf8("spinbox_mutation_pk_section_weight"));
        spinbox_mutation_pk_section_weight->setMinimum(0.000000000000000);
        spinbox_mutation_pk_section_weight->setMaximum(1.000000000000000);
        spinbox_mutation_pk_section_weight->setSingleStep(0.050000000000000);
        spinbox_mutation_pk_section_weight->setValue(1.000000000000000);
        spinbox_mutation_pk_section_weight->setDecimals(2);
        spinbox_mutation_pk_section_weight->setMinimumSize(QSize(60, 0));

        gridLayout_mutation_pk->addWidget(spinbox_mutation_pk_section_weight, 1, 6, 1, 1);

        pushButton_mutation_pk_reset_weights = new QPushButton(groupCheck_mutation_pk_enabled);
        pushButton_mutation_pk_reset_weights->setObjectName(QString::fromUtf8("pushButton_mutation_pk_reset_weights"));
        pushButton_mutation_pk_reset_weights->setMaximumSize(QSize(60, 16777215));

        gridLayout_mutation_pk->addWidget(pushButton_mutation_pk_reset_weights, 2, 6, 1, 1);

        comboBox_mutation_pk_de_type = new QComboBox(groupCheck_mutation_pk_enabled);
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->addItem(QString());
        comboBox_mutation_pk_de_type->setObjectName(QString::fromUtf8("comboBox_mutation_pk_de_type"));

        gridLayout_mutation_pk->addWidget(comboBox_mutation_pk_de_type, 0, 1, 1, 5);

        label_pk_factor = new QLabel(groupCheck_mutation_pk_enabled);
        label_pk_factor->setObjectName(QString::fromUtf8("label_pk_factor"));

        gridLayout_mutation_pk->addWidget(label_pk_factor, 1, 0, 1, 1);

        spinbox_mutation_pk_factor = new MyDoubleSpinBox(groupCheck_mutation_pk_enabled);
        spinbox_mutation_pk_factor->setObjectName(QString::fromUtf8("spinbox_mutation_pk_factor"));
        spinbox_mutation_pk_factor->setMinimum(-100.000000000000000);
        spinbox_mutation_pk_factor->setMaximum(100.000000000000000);
        spinbox_mutation_pk_factor->setSingleStep(0.100000000000000);
        spinbox_mutation_pk_factor->setValue(1.000000000000000);
        spinbox_mutation_pk_factor->setDecimals(6);

        gridLayout_mutation_pk->addWidget(spinbox_mutation_pk_factor, 1, 1, 1, 1);

        label_pk_scale = new QLabel(groupCheck_mutation_pk_enabled);
        label_pk_scale->setObjectName(QString::fromUtf8("label_pk_scale"));

        gridLayout_mutation_pk->addWidget(label_pk_scale, 1, 2, 1, 1);

        spinbox_mutation_pk_scale = new MyDoubleSpinBox(groupCheck_mutation_pk_enabled);
        spinbox_mutation_pk_scale->setObjectName(QString::fromUtf8("spinbox_mutation_pk_scale"));
        spinbox_mutation_pk_scale->setMinimum(-100.000000000000000);
        spinbox_mutation_pk_scale->setMaximum(100.000000000000000);
        spinbox_mutation_pk_scale->setSingleStep(0.100000000000000);
        spinbox_mutation_pk_scale->setValue(1.000000000000000);
        spinbox_mutation_pk_scale->setDecimals(6);

        gridLayout_mutation_pk->addWidget(spinbox_mutation_pk_scale, 1, 3, 1, 1);

        label_pk_phase = new QLabel(groupCheck_mutation_pk_enabled);
        label_pk_phase->setObjectName(QString::fromUtf8("label_pk_phase"));

        gridLayout_mutation_pk->addWidget(label_pk_phase, 1, 4, 1, 1);

        spinbox_mutation_pk_phase = new MyDoubleSpinBox(groupCheck_mutation_pk_enabled);
        spinbox_mutation_pk_phase->setObjectName(QString::fromUtf8("spinbox_mutation_pk_phase"));
        spinbox_mutation_pk_phase->setMinimum(-360.000000000000000);
        spinbox_mutation_pk_phase->setMaximum(360.000000000000000);
        spinbox_mutation_pk_phase->setSingleStep(1.000000000000000);
        spinbox_mutation_pk_phase->setValue(0.000000000000000);
        spinbox_mutation_pk_phase->setDecimals(3);

        gridLayout_mutation_pk->addWidget(spinbox_mutation_pk_phase, 1, 5, 1, 1);

        label_pk_param_a = new QLabel(groupCheck_mutation_pk_enabled);
        label_pk_param_a->setObjectName(QString::fromUtf8("label_pk_param_a"));

        gridLayout_mutation_pk->addWidget(label_pk_param_a, 2, 0, 1, 1);

        spinbox_mutation_pk_param_a = new MyDoubleSpinBox(groupCheck_mutation_pk_enabled);
        spinbox_mutation_pk_param_a->setObjectName(QString::fromUtf8("spinbox_mutation_pk_param_a"));
        spinbox_mutation_pk_param_a->setMinimum(-100.000000000000000);
        spinbox_mutation_pk_param_a->setMaximum(100.000000000000000);
        spinbox_mutation_pk_param_a->setSingleStep(0.100000000000000);
        spinbox_mutation_pk_param_a->setValue(1.000000000000000);
        spinbox_mutation_pk_param_a->setDecimals(6);

        gridLayout_mutation_pk->addWidget(spinbox_mutation_pk_param_a, 2, 1, 1, 1);

        label_pk_param_b = new QLabel(groupCheck_mutation_pk_enabled);
        label_pk_param_b->setObjectName(QString::fromUtf8("label_pk_param_b"));

        gridLayout_mutation_pk->addWidget(label_pk_param_b, 2, 2, 1, 1);

        spinbox_mutation_pk_param_b = new MyDoubleSpinBox(groupCheck_mutation_pk_enabled);
        spinbox_mutation_pk_param_b->setObjectName(QString::fromUtf8("spinbox_mutation_pk_param_b"));
        spinbox_mutation_pk_param_b->setMinimum(-100.000000000000000);
        spinbox_mutation_pk_param_b->setMaximum(100.000000000000000);
        spinbox_mutation_pk_param_b->setSingleStep(0.100000000000000);
        spinbox_mutation_pk_param_b->setValue(1.000000000000000);
        spinbox_mutation_pk_param_b->setDecimals(6);

        gridLayout_mutation_pk->addWidget(spinbox_mutation_pk_param_b, 2, 3, 1, 1);

        label_pk_param_c = new QLabel(groupCheck_mutation_pk_enabled);
        label_pk_param_c->setObjectName(QString::fromUtf8("label_pk_param_c"));

        gridLayout_mutation_pk->addWidget(label_pk_param_c, 2, 4, 1, 1);

        spinbox_mutation_pk_param_c = new MyDoubleSpinBox(groupCheck_mutation_pk_enabled);
        spinbox_mutation_pk_param_c->setObjectName(QString::fromUtf8("spinbox_mutation_pk_param_c"));
        spinbox_mutation_pk_param_c->setMinimum(-100.000000000000000);
        spinbox_mutation_pk_param_c->setMaximum(100.000000000000000);
        spinbox_mutation_pk_param_c->setSingleStep(0.100000000000000);
        spinbox_mutation_pk_param_c->setValue(1.000000000000000);
        spinbox_mutation_pk_param_c->setDecimals(6);

        gridLayout_mutation_pk->addWidget(spinbox_mutation_pk_param_c, 2, 5, 1, 1);

        label_pk_param_d = new QLabel(groupCheck_mutation_pk_enabled);
        label_pk_param_d->setObjectName(QString::fromUtf8("label_pk_param_d"));

        gridLayout_mutation_pk->addWidget(label_pk_param_d, 3, 0, 1, 1);

        spinbox_mutation_pk_param_d = new MyDoubleSpinBox(groupCheck_mutation_pk_enabled);
        spinbox_mutation_pk_param_d->setObjectName(QString::fromUtf8("spinbox_mutation_pk_param_d"));
        spinbox_mutation_pk_param_d->setMinimum(-100.000000000000000);
        spinbox_mutation_pk_param_d->setMaximum(100.000000000000000);
        spinbox_mutation_pk_param_d->setSingleStep(0.100000000000000);
        spinbox_mutation_pk_param_d->setValue(1.000000000000000);
        spinbox_mutation_pk_param_d->setDecimals(6);

        gridLayout_mutation_pk->addWidget(spinbox_mutation_pk_param_d, 3, 1, 1, 1);

        label_pk_freq = new QLabel(groupCheck_mutation_pk_enabled);
        label_pk_freq->setObjectName(QString::fromUtf8("label_pk_freq"));

        gridLayout_mutation_pk->addWidget(label_pk_freq, 3, 2, 1, 1);

        spinbox_mutation_pk_freq = new MyDoubleSpinBox(groupCheck_mutation_pk_enabled);
        spinbox_mutation_pk_freq->setObjectName(QString::fromUtf8("spinbox_mutation_pk_freq"));
        spinbox_mutation_pk_freq->setMinimum(0.010000000000000);
        spinbox_mutation_pk_freq->setMaximum(100.000000000000000);
        spinbox_mutation_pk_freq->setSingleStep(0.100000000000000);
        spinbox_mutation_pk_freq->setValue(1.000000000000000);
        spinbox_mutation_pk_freq->setDecimals(6);

        gridLayout_mutation_pk->addWidget(spinbox_mutation_pk_freq, 3, 3, 1, 1);

        label_pk_amp = new QLabel(groupCheck_mutation_pk_enabled);
        label_pk_amp->setObjectName(QString::fromUtf8("label_pk_amp"));

        gridLayout_mutation_pk->addWidget(label_pk_amp, 3, 4, 1, 1);

        spinbox_mutation_pk_amp = new MyDoubleSpinBox(groupCheck_mutation_pk_enabled);
        spinbox_mutation_pk_amp->setObjectName(QString::fromUtf8("spinbox_mutation_pk_amp"));
        spinbox_mutation_pk_amp->setMinimum(-10.000000000000000);
        spinbox_mutation_pk_amp->setMaximum(10.000000000000000);
        spinbox_mutation_pk_amp->setSingleStep(0.100000000000000);
        spinbox_mutation_pk_amp->setValue(0.500000000000000);
        spinbox_mutation_pk_amp->setDecimals(6);

        gridLayout_mutation_pk->addWidget(spinbox_mutation_pk_amp, 3, 5, 1, 1);

        label_pk_iter = new QLabel(groupCheck_mutation_pk_enabled);
        label_pk_iter->setObjectName(QString::fromUtf8("label_pk_iter"));

        gridLayout_mutation_pk->addWidget(label_pk_iter, 4, 0, 1, 1);

        spinboxInt_mutation_pk_iter_start = new MySpinBox(groupCheck_mutation_pk_enabled);
        spinboxInt_mutation_pk_iter_start->setObjectName(QString::fromUtf8("spinboxInt_mutation_pk_iter_start"));
        spinboxInt_mutation_pk_iter_start->setMinimum(0);
        spinboxInt_mutation_pk_iter_start->setMaximum(10000);
        spinboxInt_mutation_pk_iter_start->setValue(0);

        gridLayout_mutation_pk->addWidget(spinboxInt_mutation_pk_iter_start, 4, 1, 1, 1);

        label_pk_iter_stop = new QLabel(groupCheck_mutation_pk_enabled);
        label_pk_iter_stop->setObjectName(QString::fromUtf8("label_pk_iter_stop"));

        gridLayout_mutation_pk->addWidget(label_pk_iter_stop, 4, 2, 1, 1);

        spinboxInt_mutation_pk_iter_stop = new MySpinBox(groupCheck_mutation_pk_enabled);
        spinboxInt_mutation_pk_iter_stop->setObjectName(QString::fromUtf8("spinboxInt_mutation_pk_iter_stop"));
        spinboxInt_mutation_pk_iter_stop->setMinimum(0);
        spinboxInt_mutation_pk_iter_stop->setMaximum(10000);
        spinboxInt_mutation_pk_iter_stop->setValue(10000);

        gridLayout_mutation_pk->addWidget(spinboxInt_mutation_pk_iter_stop, 4, 3, 1, 1);


        verticalLayout_mutation_jos_pk->addWidget(groupCheck_mutation_pk_enabled);


        retranslateUi(cMutationJosPkPanel);

        QMetaObject::connectSlotsByName(cMutationJosPkPanel);
    } // setupUi

    void retranslateUi(QWidget *cMutationJosPkPanel)
    {
        groupCheck_mutation_jos_leys_enabled->setTitle(QCoreApplication::translate("cMutationJosPkPanel", "Jos Leys DE System", nullptr));
        label_jos_type->setText(QCoreApplication::translate("cMutationJosPkPanel", "Jos Leys DE Type:", nullptr));
        label->setText(QCoreApplication::translate("cMutationJosPkPanel", "Weight", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_mutation_jos_leys_section_weight->setToolTip(QCoreApplication::translate("cMutationJosPkPanel", "Section weight: 1=full effect, 0=off", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_mutation_jos_leys_reset_weights->setText(QCoreApplication::translate("cMutationJosPkPanel", "Reset", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_mutation_jos_leys_reset_weights->setToolTip(QCoreApplication::translate("cMutationJosPkPanel", "Reset this section's weights to 1.0", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_mutation_jos_de_type->setItemText(0, QCoreApplication::translate("cMutationJosPkPanel", "None", nullptr));
        comboBox_mutation_jos_de_type->setItemText(1, QCoreApplication::translate("cMutationJosPkPanel", "Curvature Feedback", nullptr));
        comboBox_mutation_jos_de_type->setItemText(2, QCoreApplication::translate("cMutationJosPkPanel", "Log-Derivative Scaling", nullptr));
        comboBox_mutation_jos_de_type->setItemText(3, QCoreApplication::translate("cMutationJosPkPanel", "Spherical Cap DE", nullptr));
        comboBox_mutation_jos_de_type->setItemText(4, QCoreApplication::translate("cMutationJosPkPanel", "Radial-Twist DE", nullptr));
        comboBox_mutation_jos_de_type->setItemText(5, QCoreApplication::translate("cMutationJosPkPanel", "Harmonic Decay DE", nullptr));
        comboBox_mutation_jos_de_type->setItemText(6, QCoreApplication::translate("cMutationJosPkPanel", "Orbit Length DE", nullptr));
        comboBox_mutation_jos_de_type->setItemText(7, QCoreApplication::translate("cMutationJosPkPanel", "Torsion Feedback", nullptr));
        comboBox_mutation_jos_de_type->setItemText(8, QCoreApplication::translate("cMutationJosPkPanel", "Angular Momentum DE", nullptr));
        comboBox_mutation_jos_de_type->setItemText(9, QCoreApplication::translate("cMutationJosPkPanel", "Conformal Stretch", nullptr));
        comboBox_mutation_jos_de_type->setItemText(10, QCoreApplication::translate("cMutationJosPkPanel", "Lyapunov DE", nullptr));
        comboBox_mutation_jos_de_type->setItemText(11, QCoreApplication::translate("cMutationJosPkPanel", "Gradient Descent DE", nullptr));
        comboBox_mutation_jos_de_type->setItemText(12, QCoreApplication::translate("cMutationJosPkPanel", "Newton Step DE", nullptr));
        comboBox_mutation_jos_de_type->setItemText(13, QCoreApplication::translate("cMutationJosPkPanel", "Min-Max Axis DE", nullptr));
        comboBox_mutation_jos_de_type->setItemText(14, QCoreApplication::translate("cMutationJosPkPanel", "Distance Ratio DE", nullptr));
        comboBox_mutation_jos_de_type->setItemText(15, QCoreApplication::translate("cMutationJosPkPanel", "Sectional Curvature", nullptr));
        comboBox_mutation_jos_de_type->setItemText(16, QCoreApplication::translate("cMutationJosPkPanel", "Geodesic DE", nullptr));
        comboBox_mutation_jos_de_type->setItemText(17, QCoreApplication::translate("cMutationJosPkPanel", "Laplacian DE", nullptr));
        comboBox_mutation_jos_de_type->setItemText(18, QCoreApplication::translate("cMutationJosPkPanel", "Divergence DE", nullptr));
        comboBox_mutation_jos_de_type->setItemText(19, QCoreApplication::translate("cMutationJosPkPanel", "Curl DE", nullptr));
        comboBox_mutation_jos_de_type->setItemText(20, QCoreApplication::translate("cMutationJosPkPanel", "Vorticity DE", nullptr));
        comboBox_mutation_jos_de_type->setItemText(21, QCoreApplication::translate("cMutationJosPkPanel", "Strain-Rate DE", nullptr));
        comboBox_mutation_jos_de_type->setItemText(22, QCoreApplication::translate("cMutationJosPkPanel", "Potential Field DE", nullptr));
        comboBox_mutation_jos_de_type->setItemText(23, QCoreApplication::translate("cMutationJosPkPanel", "Green Function DE", nullptr));
        comboBox_mutation_jos_de_type->setItemText(24, QCoreApplication::translate("cMutationJosPkPanel", "Poisson DE", nullptr));
        comboBox_mutation_jos_de_type->setItemText(25, QCoreApplication::translate("cMutationJosPkPanel", "Helmholtz DE", nullptr));
        comboBox_mutation_jos_de_type->setItemText(26, QCoreApplication::translate("cMutationJosPkPanel", "Wave Equation DE", nullptr));
        comboBox_mutation_jos_de_type->setItemText(27, QCoreApplication::translate("cMutationJosPkPanel", "Diffusion DE", nullptr));
        comboBox_mutation_jos_de_type->setItemText(28, QCoreApplication::translate("cMutationJosPkPanel", "Heat Kernel DE", nullptr));
        comboBox_mutation_jos_de_type->setItemText(29, QCoreApplication::translate("cMutationJosPkPanel", "Spectral DE", nullptr));
        comboBox_mutation_jos_de_type->setItemText(30, QCoreApplication::translate("cMutationJosPkPanel", "Fractal Dim DE", nullptr));

        label_jos_factor->setText(QCoreApplication::translate("cMutationJosPkPanel", "Factor:", nullptr));
        label_jos_scale->setText(QCoreApplication::translate("cMutationJosPkPanel", "Scale:", nullptr));
        label_jos_phase->setText(QCoreApplication::translate("cMutationJosPkPanel", "Phase:", nullptr));
        label_jos_param_a->setText(QCoreApplication::translate("cMutationJosPkPanel", "ParamA:", nullptr));
        label_jos_param_b->setText(QCoreApplication::translate("cMutationJosPkPanel", "ParamB:", nullptr));
        label_jos_param_c->setText(QCoreApplication::translate("cMutationJosPkPanel", "ParamC:", nullptr));
        label_jos_param_d->setText(QCoreApplication::translate("cMutationJosPkPanel", "ParamD:", nullptr));
        label_jos_freq->setText(QCoreApplication::translate("cMutationJosPkPanel", "Freq:", nullptr));
        label_jos_amp->setText(QCoreApplication::translate("cMutationJosPkPanel", "Amp:", nullptr));
        label_jos_iter->setText(QCoreApplication::translate("cMutationJosPkPanel", "Jos Iter:", nullptr));
        label_jos_iter_stop->setText(QCoreApplication::translate("cMutationJosPkPanel", "Stop:", nullptr));
        groupCheck_mutation_pk_enabled->setTitle(QCoreApplication::translate("cMutationJosPkPanel", "Pseudokleinian DE System", nullptr));
        label_pk_type->setText(QCoreApplication::translate("cMutationJosPkPanel", "Nylander DE Type:", nullptr));
        label1->setText(QCoreApplication::translate("cMutationJosPkPanel", "Weight", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_mutation_pk_section_weight->setToolTip(QCoreApplication::translate("cMutationJosPkPanel", "Section weight: 1=full effect, 0=off", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_mutation_pk_reset_weights->setText(QCoreApplication::translate("cMutationJosPkPanel", "Reset", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_mutation_pk_reset_weights->setToolTip(QCoreApplication::translate("cMutationJosPkPanel", "Reset this section's weights to 1.0", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_mutation_pk_de_type->setItemText(0, QCoreApplication::translate("cMutationJosPkPanel", "None", nullptr));
        comboBox_mutation_pk_de_type->setItemText(1, QCoreApplication::translate("cMutationJosPkPanel", "Conformal DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(2, QCoreApplication::translate("cMutationJosPkPanel", "Poincar\303\251 Metric", nullptr));
        comboBox_mutation_pk_de_type->setItemText(3, QCoreApplication::translate("cMutationJosPkPanel", "Ford Circle DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(4, QCoreApplication::translate("cMutationJosPkPanel", "Apollonian DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(5, QCoreApplication::translate("cMutationJosPkPanel", "Schottky DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(6, QCoreApplication::translate("cMutationJosPkPanel", "Fuchsian DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(7, QCoreApplication::translate("cMutationJosPkPanel", "Modular DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(8, QCoreApplication::translate("cMutationJosPkPanel", "Hecke DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(9, QCoreApplication::translate("cMutationJosPkPanel", "Eisenstein DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(10, QCoreApplication::translate("cMutationJosPkPanel", "Theta Function DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(11, QCoreApplication::translate("cMutationJosPkPanel", "Weierstrass DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(12, QCoreApplication::translate("cMutationJosPkPanel", "Klein J DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(13, QCoreApplication::translate("cMutationJosPkPanel", "Riemann Surface DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(14, QCoreApplication::translate("cMutationJosPkPanel", "Uniformization DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(15, QCoreApplication::translate("cMutationJosPkPanel", "Selberg Zeta DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(16, QCoreApplication::translate("cMutationJosPkPanel", "L-Function DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(17, QCoreApplication::translate("cMutationJosPkPanel", "Dirichlet DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(18, QCoreApplication::translate("cMutationJosPkPanel", "Ramanujan DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(19, QCoreApplication::translate("cMutationJosPkPanel", "Dedekind DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(20, QCoreApplication::translate("cMutationJosPkPanel", "Eta Function DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(21, QCoreApplication::translate("cMutationJosPkPanel", "Jacobi Form DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(22, QCoreApplication::translate("cMutationJosPkPanel", "Siegel Modular DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(23, QCoreApplication::translate("cMutationJosPkPanel", "Hilbert Modular DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(24, QCoreApplication::translate("cMutationJosPkPanel", "Picard DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(25, QCoreApplication::translate("cMutationJosPkPanel", "Bianchi DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(26, QCoreApplication::translate("cMutationJosPkPanel", "Arithmetic DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(27, QCoreApplication::translate("cMutationJosPkPanel", "Quaternionic DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(28, QCoreApplication::translate("cMutationJosPkPanel", "Octonionic DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(29, QCoreApplication::translate("cMutationJosPkPanel", "Algebraic DE", nullptr));
        comboBox_mutation_pk_de_type->setItemText(30, QCoreApplication::translate("cMutationJosPkPanel", "Transcendental DE", nullptr));

        label_pk_factor->setText(QCoreApplication::translate("cMutationJosPkPanel", "Factor:", nullptr));
        label_pk_scale->setText(QCoreApplication::translate("cMutationJosPkPanel", "Scale:", nullptr));
        label_pk_phase->setText(QCoreApplication::translate("cMutationJosPkPanel", "Phase:", nullptr));
        label_pk_param_a->setText(QCoreApplication::translate("cMutationJosPkPanel", "ParamA:", nullptr));
        label_pk_param_b->setText(QCoreApplication::translate("cMutationJosPkPanel", "ParamB:", nullptr));
        label_pk_param_c->setText(QCoreApplication::translate("cMutationJosPkPanel", "ParamC:", nullptr));
        label_pk_param_d->setText(QCoreApplication::translate("cMutationJosPkPanel", "ParamD:", nullptr));
        label_pk_freq->setText(QCoreApplication::translate("cMutationJosPkPanel", "Freq:", nullptr));
        label_pk_amp->setText(QCoreApplication::translate("cMutationJosPkPanel", "Amp:", nullptr));
        label_pk_iter->setText(QCoreApplication::translate("cMutationJosPkPanel", "PK Iter:", nullptr));
        label_pk_iter_stop->setText(QCoreApplication::translate("cMutationJosPkPanel", "Stop:", nullptr));
        (void)cMutationJosPkPanel;
    } // retranslateUi

};

namespace Ui {
    class cMutationJosPkPanel: public Ui_cMutationJosPkPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUTATION_JOS_PK_PANEL_H
