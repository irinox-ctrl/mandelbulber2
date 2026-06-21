/********************************************************************************
** Form generated from reading UI file 'fractal_hybrid_tab.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRACTAL_HYBRID_TAB_H
#define UI_FRACTAL_HYBRID_TAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "buton_load_settings_from_widget.h"
#include "buton_random_settings_from_widget.h"
#include "buton_reset_settings_from_widget.h"
#include "buton_save_settings_from_widget.h"
#include "my_check_box.h"
#include "my_combo_box.h"
#include "my_double_spin_box.h"
#include "my_group_box.h"
#include "my_spin_box.h"
#include "objects_tree_widget.h"

QT_BEGIN_NAMESPACE

class Ui_cFractalHybridTab
{
public:
    QVBoxLayout *verticalLayout_53;
    QHBoxLayout *horizontalLayout_6;
    cButtonLoadSettingsFromWidget *pushButton_local_load_6;
    cButtonSaveSettingsFromWidget *pushButton_local_save_6;
    cButtonResetSettingsFromWidget *pushButton_local_reset_6;
    cButtonRandomSettingsFromWidget *pushButton_local_randomize_3;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout_28;
    MyDoubleSpinBox *spinbox_linear_DE_offset;
    MySpinBox *spinboxInt_repeat_from;
    QLabel *label_repeat_from;
    QLabel *label_131;
    MyCheckBox *checkBox_hybrid_fractal_enable;
    MyGroupBox *groupCheck_boolean_operators;
    QVBoxLayout *verticalLayout_76;
    QGridLayout *gridLayout_40;
    MyComboBox *comboBox_boolean_operator_1;
    QLabel *label_154;
    MyComboBox *comboBox_boolean_operator_2;
    MyComboBox *comboBox_boolean_operator_3;
    QLabel *label_155;
    QLabel *label_156;
    QLabel *label_286;
    QLabel *label_287;
    QLabel *label_288;
    QLabel *label_285;
    QLabel *label_289;
    MyComboBox *comboBox_boolean_operator_4;
    MyComboBox *comboBox_boolean_operator_5;
    MyComboBox *comboBox_boolean_operator_6;
    MyComboBox *comboBox_boolean_operator_7;
    MyComboBox *comboBox_boolean_operator_8;
    MyGroupBox *groupCheck_box_folding;
    QVBoxLayout *verticalLayout_80;
    QGridLayout *gridLayout_42;
    MyDoubleSpinBox *spinbox_box_folding_limit;
    QLabel *label_129;
    QLabel *label_128;
    MyDoubleSpinBox *spinbox_box_folding_value;
    MyGroupBox *groupCheck_spherical_folding;
    QVBoxLayout *verticalLayout_81;
    QGridLayout *gridLayout_43;
    QLabel *label_169;
    MyDoubleSpinBox *spinbox_spherical_folding_outer;
    QLabel *label_130;
    MyDoubleSpinBox *spinbox_spherical_folding_inner;
    MyGroupBox *groupCheck_objects_tree_enable;
    QVBoxLayout *verticalLayout_7;
    cObjectsTreeWidget *widget_objectsTree;
    QSpacerItem *verticalSpacer_10;

    void setupUi(QWidget *cFractalHybridTab)
    {
        if (cFractalHybridTab->objectName().isEmpty())
            cFractalHybridTab->setObjectName(QString::fromUtf8("cFractalHybridTab"));
        verticalLayout_53 = new QVBoxLayout(cFractalHybridTab);
        verticalLayout_53->setSpacing(2);
        verticalLayout_53->setObjectName(QString::fromUtf8("verticalLayout_53"));
        verticalLayout_53->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        pushButton_local_load_6 = new cButtonLoadSettingsFromWidget(cFractalHybridTab);
        pushButton_local_load_6->setObjectName(QString::fromUtf8("pushButton_local_load_6"));

        horizontalLayout_6->addWidget(pushButton_local_load_6);

        pushButton_local_save_6 = new cButtonSaveSettingsFromWidget(cFractalHybridTab);
        pushButton_local_save_6->setObjectName(QString::fromUtf8("pushButton_local_save_6"));

        horizontalLayout_6->addWidget(pushButton_local_save_6);

        pushButton_local_reset_6 = new cButtonResetSettingsFromWidget(cFractalHybridTab);
        pushButton_local_reset_6->setObjectName(QString::fromUtf8("pushButton_local_reset_6"));

        horizontalLayout_6->addWidget(pushButton_local_reset_6);

        pushButton_local_randomize_3 = new cButtonRandomSettingsFromWidget(cFractalHybridTab);
        pushButton_local_randomize_3->setObjectName(QString::fromUtf8("pushButton_local_randomize_3"));

        horizontalLayout_6->addWidget(pushButton_local_randomize_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_4);


        verticalLayout_53->addLayout(horizontalLayout_6);

        groupBox_3 = new QGroupBox(cFractalHybridTab);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_4 = new QVBoxLayout(groupBox_3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(2, 2, 2, 2);
        gridLayout_28 = new QGridLayout();
        gridLayout_28->setSpacing(2);
        gridLayout_28->setObjectName(QString::fromUtf8("gridLayout_28"));
        spinbox_linear_DE_offset = new MyDoubleSpinBox(groupBox_3);
        spinbox_linear_DE_offset->setObjectName(QString::fromUtf8("spinbox_linear_DE_offset"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(spinbox_linear_DE_offset->sizePolicy().hasHeightForWidth());
        spinbox_linear_DE_offset->setSizePolicy(sizePolicy);
        spinbox_linear_DE_offset->setDecimals(3);
        spinbox_linear_DE_offset->setMinimum(-1000.000000000000000);
        spinbox_linear_DE_offset->setMaximum(1000.000000000000000);
        spinbox_linear_DE_offset->setSingleStep(0.100000000000000);

        gridLayout_28->addWidget(spinbox_linear_DE_offset, 2, 1, 1, 1);

        spinboxInt_repeat_from = new MySpinBox(groupBox_3);
        spinboxInt_repeat_from->setObjectName(QString::fromUtf8("spinboxInt_repeat_from"));
        sizePolicy.setHeightForWidth(spinboxInt_repeat_from->sizePolicy().hasHeightForWidth());
        spinboxInt_repeat_from->setSizePolicy(sizePolicy);
        spinboxInt_repeat_from->setMinimum(1);
        spinboxInt_repeat_from->setMaximum(9);

        gridLayout_28->addWidget(spinboxInt_repeat_from, 1, 1, 1, 1);

        label_repeat_from = new QLabel(groupBox_3);
        label_repeat_from->setObjectName(QString::fromUtf8("label_repeat_from"));

        gridLayout_28->addWidget(label_repeat_from, 1, 0, 1, 1);

        label_131 = new QLabel(groupBox_3);
        label_131->setObjectName(QString::fromUtf8("label_131"));

        gridLayout_28->addWidget(label_131, 2, 0, 1, 1);

        checkBox_hybrid_fractal_enable = new MyCheckBox(groupBox_3);
        checkBox_hybrid_fractal_enable->setObjectName(QString::fromUtf8("checkBox_hybrid_fractal_enable"));
        sizePolicy.setHeightForWidth(checkBox_hybrid_fractal_enable->sizePolicy().hasHeightForWidth());
        checkBox_hybrid_fractal_enable->setSizePolicy(sizePolicy);

        gridLayout_28->addWidget(checkBox_hybrid_fractal_enable, 0, 0, 1, 2);


        verticalLayout_4->addLayout(gridLayout_28);


        verticalLayout_53->addWidget(groupBox_3);

        groupCheck_boolean_operators = new MyGroupBox(cFractalHybridTab);
        groupCheck_boolean_operators->setObjectName(QString::fromUtf8("groupCheck_boolean_operators"));
        groupCheck_boolean_operators->setEnabled(true);
        groupCheck_boolean_operators->setCheckable(true);
        groupCheck_boolean_operators->setChecked(true);
        verticalLayout_76 = new QVBoxLayout(groupCheck_boolean_operators);
        verticalLayout_76->setSpacing(2);
        verticalLayout_76->setObjectName(QString::fromUtf8("verticalLayout_76"));
        verticalLayout_76->setContentsMargins(2, 2, 2, 2);
        gridLayout_40 = new QGridLayout();
        gridLayout_40->setSpacing(2);
        gridLayout_40->setObjectName(QString::fromUtf8("gridLayout_40"));
        comboBox_boolean_operator_1 = new MyComboBox(groupCheck_boolean_operators);
        comboBox_boolean_operator_1->addItem(QString());
        comboBox_boolean_operator_1->addItem(QString());
        comboBox_boolean_operator_1->addItem(QString());
        comboBox_boolean_operator_1->setObjectName(QString::fromUtf8("comboBox_boolean_operator_1"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox_boolean_operator_1->sizePolicy().hasHeightForWidth());
        comboBox_boolean_operator_1->setSizePolicy(sizePolicy1);

        gridLayout_40->addWidget(comboBox_boolean_operator_1, 1, 1, 1, 1);

        label_154 = new QLabel(groupCheck_boolean_operators);
        label_154->setObjectName(QString::fromUtf8("label_154"));

        gridLayout_40->addWidget(label_154, 1, 0, 1, 1);

        comboBox_boolean_operator_2 = new MyComboBox(groupCheck_boolean_operators);
        comboBox_boolean_operator_2->addItem(QString());
        comboBox_boolean_operator_2->addItem(QString());
        comboBox_boolean_operator_2->addItem(QString());
        comboBox_boolean_operator_2->setObjectName(QString::fromUtf8("comboBox_boolean_operator_2"));
        sizePolicy1.setHeightForWidth(comboBox_boolean_operator_2->sizePolicy().hasHeightForWidth());
        comboBox_boolean_operator_2->setSizePolicy(sizePolicy1);

        gridLayout_40->addWidget(comboBox_boolean_operator_2, 2, 1, 1, 1);

        comboBox_boolean_operator_3 = new MyComboBox(groupCheck_boolean_operators);
        comboBox_boolean_operator_3->addItem(QString());
        comboBox_boolean_operator_3->addItem(QString());
        comboBox_boolean_operator_3->addItem(QString());
        comboBox_boolean_operator_3->setObjectName(QString::fromUtf8("comboBox_boolean_operator_3"));
        sizePolicy1.setHeightForWidth(comboBox_boolean_operator_3->sizePolicy().hasHeightForWidth());
        comboBox_boolean_operator_3->setSizePolicy(sizePolicy1);

        gridLayout_40->addWidget(comboBox_boolean_operator_3, 3, 1, 1, 1);

        label_155 = new QLabel(groupCheck_boolean_operators);
        label_155->setObjectName(QString::fromUtf8("label_155"));

        gridLayout_40->addWidget(label_155, 2, 0, 1, 1);

        label_156 = new QLabel(groupCheck_boolean_operators);
        label_156->setObjectName(QString::fromUtf8("label_156"));

        gridLayout_40->addWidget(label_156, 3, 0, 1, 1);

        label_286 = new QLabel(groupCheck_boolean_operators);
        label_286->setObjectName(QString::fromUtf8("label_286"));

        gridLayout_40->addWidget(label_286, 5, 0, 1, 1);

        label_287 = new QLabel(groupCheck_boolean_operators);
        label_287->setObjectName(QString::fromUtf8("label_287"));

        gridLayout_40->addWidget(label_287, 6, 0, 1, 1);

        label_288 = new QLabel(groupCheck_boolean_operators);
        label_288->setObjectName(QString::fromUtf8("label_288"));

        gridLayout_40->addWidget(label_288, 7, 0, 1, 1);

        label_285 = new QLabel(groupCheck_boolean_operators);
        label_285->setObjectName(QString::fromUtf8("label_285"));

        gridLayout_40->addWidget(label_285, 4, 0, 1, 1);

        label_289 = new QLabel(groupCheck_boolean_operators);
        label_289->setObjectName(QString::fromUtf8("label_289"));

        gridLayout_40->addWidget(label_289, 8, 0, 1, 1);

        comboBox_boolean_operator_4 = new MyComboBox(groupCheck_boolean_operators);
        comboBox_boolean_operator_4->addItem(QString());
        comboBox_boolean_operator_4->addItem(QString());
        comboBox_boolean_operator_4->addItem(QString());
        comboBox_boolean_operator_4->setObjectName(QString::fromUtf8("comboBox_boolean_operator_4"));
        sizePolicy1.setHeightForWidth(comboBox_boolean_operator_4->sizePolicy().hasHeightForWidth());
        comboBox_boolean_operator_4->setSizePolicy(sizePolicy1);

        gridLayout_40->addWidget(comboBox_boolean_operator_4, 4, 1, 1, 1);

        comboBox_boolean_operator_5 = new MyComboBox(groupCheck_boolean_operators);
        comboBox_boolean_operator_5->addItem(QString());
        comboBox_boolean_operator_5->addItem(QString());
        comboBox_boolean_operator_5->addItem(QString());
        comboBox_boolean_operator_5->setObjectName(QString::fromUtf8("comboBox_boolean_operator_5"));
        sizePolicy1.setHeightForWidth(comboBox_boolean_operator_5->sizePolicy().hasHeightForWidth());
        comboBox_boolean_operator_5->setSizePolicy(sizePolicy1);

        gridLayout_40->addWidget(comboBox_boolean_operator_5, 5, 1, 1, 1);

        comboBox_boolean_operator_6 = new MyComboBox(groupCheck_boolean_operators);
        comboBox_boolean_operator_6->addItem(QString());
        comboBox_boolean_operator_6->addItem(QString());
        comboBox_boolean_operator_6->addItem(QString());
        comboBox_boolean_operator_6->setObjectName(QString::fromUtf8("comboBox_boolean_operator_6"));
        sizePolicy1.setHeightForWidth(comboBox_boolean_operator_6->sizePolicy().hasHeightForWidth());
        comboBox_boolean_operator_6->setSizePolicy(sizePolicy1);

        gridLayout_40->addWidget(comboBox_boolean_operator_6, 6, 1, 1, 1);

        comboBox_boolean_operator_7 = new MyComboBox(groupCheck_boolean_operators);
        comboBox_boolean_operator_7->addItem(QString());
        comboBox_boolean_operator_7->addItem(QString());
        comboBox_boolean_operator_7->addItem(QString());
        comboBox_boolean_operator_7->setObjectName(QString::fromUtf8("comboBox_boolean_operator_7"));
        sizePolicy1.setHeightForWidth(comboBox_boolean_operator_7->sizePolicy().hasHeightForWidth());
        comboBox_boolean_operator_7->setSizePolicy(sizePolicy1);

        gridLayout_40->addWidget(comboBox_boolean_operator_7, 7, 1, 1, 1);

        comboBox_boolean_operator_8 = new MyComboBox(groupCheck_boolean_operators);
        comboBox_boolean_operator_8->addItem(QString());
        comboBox_boolean_operator_8->addItem(QString());
        comboBox_boolean_operator_8->addItem(QString());
        comboBox_boolean_operator_8->setObjectName(QString::fromUtf8("comboBox_boolean_operator_8"));
        sizePolicy1.setHeightForWidth(comboBox_boolean_operator_8->sizePolicy().hasHeightForWidth());
        comboBox_boolean_operator_8->setSizePolicy(sizePolicy1);

        gridLayout_40->addWidget(comboBox_boolean_operator_8, 8, 1, 1, 1);


        verticalLayout_76->addLayout(gridLayout_40);


        verticalLayout_53->addWidget(groupCheck_boolean_operators);

        groupCheck_box_folding = new MyGroupBox(cFractalHybridTab);
        groupCheck_box_folding->setObjectName(QString::fromUtf8("groupCheck_box_folding"));
        groupCheck_box_folding->setEnabled(true);
        groupCheck_box_folding->setCheckable(true);
        groupCheck_box_folding->setChecked(true);
        verticalLayout_80 = new QVBoxLayout(groupCheck_box_folding);
        verticalLayout_80->setSpacing(2);
        verticalLayout_80->setObjectName(QString::fromUtf8("verticalLayout_80"));
        verticalLayout_80->setContentsMargins(2, 2, 2, 2);
        gridLayout_42 = new QGridLayout();
        gridLayout_42->setSpacing(2);
        gridLayout_42->setObjectName(QString::fromUtf8("gridLayout_42"));
        spinbox_box_folding_limit = new MyDoubleSpinBox(groupCheck_box_folding);
        spinbox_box_folding_limit->setObjectName(QString::fromUtf8("spinbox_box_folding_limit"));
        sizePolicy.setHeightForWidth(spinbox_box_folding_limit->sizePolicy().hasHeightForWidth());
        spinbox_box_folding_limit->setSizePolicy(sizePolicy);
        spinbox_box_folding_limit->setDecimals(6);
        spinbox_box_folding_limit->setMaximum(1000.000000000000000);
        spinbox_box_folding_limit->setSingleStep(0.100000000000000);

        gridLayout_42->addWidget(spinbox_box_folding_limit, 0, 1, 1, 1);

        label_129 = new QLabel(groupCheck_box_folding);
        label_129->setObjectName(QString::fromUtf8("label_129"));

        gridLayout_42->addWidget(label_129, 1, 0, 1, 1);

        label_128 = new QLabel(groupCheck_box_folding);
        label_128->setObjectName(QString::fromUtf8("label_128"));

        gridLayout_42->addWidget(label_128, 0, 0, 1, 1);

        spinbox_box_folding_value = new MyDoubleSpinBox(groupCheck_box_folding);
        spinbox_box_folding_value->setObjectName(QString::fromUtf8("spinbox_box_folding_value"));
        sizePolicy.setHeightForWidth(spinbox_box_folding_value->sizePolicy().hasHeightForWidth());
        spinbox_box_folding_value->setSizePolicy(sizePolicy);
        spinbox_box_folding_value->setDecimals(6);
        spinbox_box_folding_value->setMaximum(1000.000000000000000);
        spinbox_box_folding_value->setSingleStep(0.100000000000000);

        gridLayout_42->addWidget(spinbox_box_folding_value, 1, 1, 1, 1);


        verticalLayout_80->addLayout(gridLayout_42);


        verticalLayout_53->addWidget(groupCheck_box_folding);

        groupCheck_spherical_folding = new MyGroupBox(cFractalHybridTab);
        groupCheck_spherical_folding->setObjectName(QString::fromUtf8("groupCheck_spherical_folding"));
        groupCheck_spherical_folding->setEnabled(true);
        groupCheck_spherical_folding->setCheckable(true);
        groupCheck_spherical_folding->setChecked(true);
        verticalLayout_81 = new QVBoxLayout(groupCheck_spherical_folding);
        verticalLayout_81->setSpacing(2);
        verticalLayout_81->setObjectName(QString::fromUtf8("verticalLayout_81"));
        verticalLayout_81->setContentsMargins(2, 2, 2, 2);
        gridLayout_43 = new QGridLayout();
        gridLayout_43->setSpacing(2);
        gridLayout_43->setObjectName(QString::fromUtf8("gridLayout_43"));
        label_169 = new QLabel(groupCheck_spherical_folding);
        label_169->setObjectName(QString::fromUtf8("label_169"));

        gridLayout_43->addWidget(label_169, 1, 0, 1, 1);

        spinbox_spherical_folding_outer = new MyDoubleSpinBox(groupCheck_spherical_folding);
        spinbox_spherical_folding_outer->setObjectName(QString::fromUtf8("spinbox_spherical_folding_outer"));
        sizePolicy.setHeightForWidth(spinbox_spherical_folding_outer->sizePolicy().hasHeightForWidth());
        spinbox_spherical_folding_outer->setSizePolicy(sizePolicy);
        spinbox_spherical_folding_outer->setDecimals(6);
        spinbox_spherical_folding_outer->setMaximum(1000.000000000000000);
        spinbox_spherical_folding_outer->setSingleStep(0.100000000000000);

        gridLayout_43->addWidget(spinbox_spherical_folding_outer, 0, 1, 1, 1);

        label_130 = new QLabel(groupCheck_spherical_folding);
        label_130->setObjectName(QString::fromUtf8("label_130"));

        gridLayout_43->addWidget(label_130, 0, 0, 1, 1);

        spinbox_spherical_folding_inner = new MyDoubleSpinBox(groupCheck_spherical_folding);
        spinbox_spherical_folding_inner->setObjectName(QString::fromUtf8("spinbox_spherical_folding_inner"));
        sizePolicy.setHeightForWidth(spinbox_spherical_folding_inner->sizePolicy().hasHeightForWidth());
        spinbox_spherical_folding_inner->setSizePolicy(sizePolicy);
        spinbox_spherical_folding_inner->setDecimals(6);
        spinbox_spherical_folding_inner->setMaximum(1000.000000000000000);
        spinbox_spherical_folding_inner->setSingleStep(0.100000000000000);

        gridLayout_43->addWidget(spinbox_spherical_folding_inner, 1, 1, 1, 1);


        verticalLayout_81->addLayout(gridLayout_43);


        verticalLayout_53->addWidget(groupCheck_spherical_folding);

        groupCheck_objects_tree_enable = new MyGroupBox(cFractalHybridTab);
        groupCheck_objects_tree_enable->setObjectName(QString::fromUtf8("groupCheck_objects_tree_enable"));
        groupCheck_objects_tree_enable->setCheckable(true);
        verticalLayout_7 = new QVBoxLayout(groupCheck_objects_tree_enable);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        widget_objectsTree = new cObjectsTreeWidget(groupCheck_objects_tree_enable);
        widget_objectsTree->setObjectName(QString::fromUtf8("widget_objectsTree"));
        widget_objectsTree->setMinimumSize(QSize(0, 32));

        verticalLayout_7->addWidget(widget_objectsTree);


        verticalLayout_53->addWidget(groupCheck_objects_tree_enable);

        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_53->addItem(verticalSpacer_10);


        retranslateUi(cFractalHybridTab);

        QMetaObject::connectSlotsByName(cFractalHybridTab);
    } // setupUi

    void retranslateUi(QWidget *cFractalHybridTab)
    {
        pushButton_local_load_6->setText(QCoreApplication::translate("cFractalHybridTab", "Load", nullptr));
        pushButton_local_save_6->setText(QCoreApplication::translate("cFractalHybridTab", "Save", nullptr));
        pushButton_local_reset_6->setText(QCoreApplication::translate("cFractalHybridTab", "Reset", nullptr));
        pushButton_local_randomize_3->setText(QCoreApplication::translate("cFractalHybridTab", "Randomize", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("cFractalHybridTab", "Hybrid", nullptr));
        spinbox_linear_DE_offset->setPrefix(QString());
        spinbox_linear_DE_offset->setSuffix(QString());
#if QT_CONFIG(tooltip)
        spinboxInt_repeat_from->setToolTip(QCoreApplication::translate("cFractalHybridTab", "<html><head/><body><p>Controls from which fractal component will be repeated hybrid formula sequence</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_repeat_from->setText(QCoreApplication::translate("cFractalHybridTab", "Repeat sequence\n"
"from fractal #:", nullptr));
        label_131->setText(QCoreApplication::translate("cFractalHybridTab", "Linear DE offset\n"
"(fine tuning of IFS\n"
"distance estimation)", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_hybrid_fractal_enable->setToolTip(QCoreApplication::translate("cFractalHybridTab", "<html><head/><body><p>Enables hybrid fractals.</p><p>Hybrid fractals are calculated by multiplexing between different fractal formulas. In 9 fractal tabs (slots) you can define a set of fractal formulas each with their own parameters.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_hybrid_fractal_enable->setText(QCoreApplication::translate("cFractalHybridTab", "Enable hybrid fractals", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_boolean_operators->setToolTip(QCoreApplication::translate("cFractalHybridTab", "<html><head/><body><p>Boolean operators between fractal shapes.<br/>Additional controls will appear at the bottom of each formula UI.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_boolean_operators->setTitle(QCoreApplication::translate("cFractalHybridTab", "Boo&lean operators", nullptr));
        comboBox_boolean_operator_1->setItemText(0, QCoreApplication::translate("cFractalHybridTab", "Intersection (AND)", nullptr));
        comboBox_boolean_operator_1->setItemText(1, QCoreApplication::translate("cFractalHybridTab", "Union (OR)", nullptr));
        comboBox_boolean_operator_1->setItemText(2, QCoreApplication::translate("cFractalHybridTab", "Complement (1st minus 2nd)", nullptr));

        label_154->setText(QCoreApplication::translate("cFractalHybridTab", "1st <-> 2nd formula:", nullptr));
        comboBox_boolean_operator_2->setItemText(0, QCoreApplication::translate("cFractalHybridTab", "Intersection (AND)", nullptr));
        comboBox_boolean_operator_2->setItemText(1, QCoreApplication::translate("cFractalHybridTab", "Union (OR)", nullptr));
        comboBox_boolean_operator_2->setItemText(2, QCoreApplication::translate("cFractalHybridTab", "Complement (2nd minus 3rd)", nullptr));

        comboBox_boolean_operator_3->setItemText(0, QCoreApplication::translate("cFractalHybridTab", "Intersection (AND)", nullptr));
        comboBox_boolean_operator_3->setItemText(1, QCoreApplication::translate("cFractalHybridTab", "Union (OR)", nullptr));
        comboBox_boolean_operator_3->setItemText(2, QCoreApplication::translate("cFractalHybridTab", "Complement (3rd minus 4th)", nullptr));

        label_155->setText(QCoreApplication::translate("cFractalHybridTab", "2st <-> 3rd formula:", nullptr));
        label_156->setText(QCoreApplication::translate("cFractalHybridTab", "3rd <-> 4th formula:", nullptr));
        label_286->setText(QCoreApplication::translate("cFractalHybridTab", "5rd <-> 6th formula:", nullptr));
        label_287->setText(QCoreApplication::translate("cFractalHybridTab", "6rd <-> 7th formula:", nullptr));
        label_288->setText(QCoreApplication::translate("cFractalHybridTab", "7rd <-> 8th formula:", nullptr));
        label_285->setText(QCoreApplication::translate("cFractalHybridTab", "4rd <-> 5th formula:", nullptr));
        label_289->setText(QCoreApplication::translate("cFractalHybridTab", "8rd <-> 9th formula:", nullptr));
        comboBox_boolean_operator_4->setItemText(0, QCoreApplication::translate("cFractalHybridTab", "Intersection (AND)", nullptr));
        comboBox_boolean_operator_4->setItemText(1, QCoreApplication::translate("cFractalHybridTab", "Union (OR)", nullptr));
        comboBox_boolean_operator_4->setItemText(2, QCoreApplication::translate("cFractalHybridTab", "Complement (4th minus 5th)", nullptr));

        comboBox_boolean_operator_5->setItemText(0, QCoreApplication::translate("cFractalHybridTab", "Intersection (AND)", nullptr));
        comboBox_boolean_operator_5->setItemText(1, QCoreApplication::translate("cFractalHybridTab", "Union (OR)", nullptr));
        comboBox_boolean_operator_5->setItemText(2, QCoreApplication::translate("cFractalHybridTab", "Complement (5th minus 6th)", nullptr));

        comboBox_boolean_operator_6->setItemText(0, QCoreApplication::translate("cFractalHybridTab", "Intersection (AND)", nullptr));
        comboBox_boolean_operator_6->setItemText(1, QCoreApplication::translate("cFractalHybridTab", "Union (OR)", nullptr));
        comboBox_boolean_operator_6->setItemText(2, QCoreApplication::translate("cFractalHybridTab", "Complement (6th minus 7th)", nullptr));

        comboBox_boolean_operator_7->setItemText(0, QCoreApplication::translate("cFractalHybridTab", "Intersection (AND)", nullptr));
        comboBox_boolean_operator_7->setItemText(1, QCoreApplication::translate("cFractalHybridTab", "Union (OR)", nullptr));
        comboBox_boolean_operator_7->setItemText(2, QCoreApplication::translate("cFractalHybridTab", "Complement (7th minus 8th)", nullptr));

        comboBox_boolean_operator_8->setItemText(0, QCoreApplication::translate("cFractalHybridTab", "Intersection (AND)", nullptr));
        comboBox_boolean_operator_8->setItemText(1, QCoreApplication::translate("cFractalHybridTab", "Union (OR)", nullptr));
        comboBox_boolean_operator_8->setItemText(2, QCoreApplication::translate("cFractalHybridTab", "Complement (8th minus 9th)", nullptr));

#if QT_CONFIG(tooltip)
        groupCheck_box_folding->setToolTip(QCoreApplication::translate("cFractalHybridTab", "<html><head/><body><p>Enables box folding like is used in Mandelbox formula.</p><p>(It's to keep compatibility with Mandelbulber 1.21)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_box_folding->setTitle(QCoreApplication::translate("cFractalHybridTab", "Bo&x Folding", nullptr));
        spinbox_box_folding_limit->setPrefix(QString());
        spinbox_box_folding_limit->setSuffix(QString());
        label_129->setText(QCoreApplication::translate("cFractalHybridTab", "Folding value:", nullptr));
        label_128->setText(QCoreApplication::translate("cFractalHybridTab", "Folding limit:", nullptr));
        spinbox_box_folding_value->setPrefix(QString());
        spinbox_box_folding_value->setSuffix(QString());
#if QT_CONFIG(tooltip)
        groupCheck_spherical_folding->setToolTip(QCoreApplication::translate("cFractalHybridTab", "<html><head/><body><p>Enables spherical folding like is used in Mandelbox formula.</p><p>(It's to keep compatibility with Mandelbulber 1.21)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_spherical_folding->setTitle(QCoreApplication::translate("cFractalHybridTab", "Spherical Folding", nullptr));
        label_169->setText(QCoreApplication::translate("cFractalHybridTab", "Inner radius:", nullptr));
        spinbox_spherical_folding_outer->setPrefix(QString());
        spinbox_spherical_folding_outer->setSuffix(QString());
        label_130->setText(QCoreApplication::translate("cFractalHybridTab", "Outer radius:", nullptr));
        spinbox_spherical_folding_inner->setPrefix(QString());
        spinbox_spherical_folding_inner->setSuffix(QString());
        groupCheck_objects_tree_enable->setTitle(QCoreApplication::translate("cFractalHybridTab", "GroupBox", nullptr));
        (void)cFractalHybridTab;
    } // retranslateUi

};

namespace Ui {
    class cFractalHybridTab: public Ui_cFractalHybridTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRACTAL_HYBRID_TAB_H
