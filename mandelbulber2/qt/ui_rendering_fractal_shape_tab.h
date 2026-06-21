/********************************************************************************
** Form generated from reading UI file 'rendering_fractal_shape_tab.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RENDERING_FRACTAL_SHAPE_TAB_H
#define UI_RENDERING_FRACTAL_SHAPE_TAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "my_check_box.h"
#include "my_combo_box.h"
#include "my_double_spin_box.h"
#include "my_group_box.h"
#include "my_line_edit.h"
#include "my_spin_box.h"

QT_BEGIN_NAMESPACE

class Ui_cRenderingFractalShapeTab
{
public:
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_114;
    QGridLayout *gridLayout_69;
    QLabel *label_284;
    MyLineEdit *logedit_bailout;
    MyCheckBox *checkBox_use_default_bailout;
    MySpinBox *spinboxInt_N;
    QLabel *label_222;
    QHBoxLayout *horizontalLayout_auto_iter;
    QPushButton *pushButton_auto_iter_bailout;
    QPushButton *pushButton_auto_slot_iter;
    QLabel *label_auto_iter_result;
    QGroupBox *groupBox_distanceEstimation;
    QVBoxLayout *verticalLayout_115;
    QGridLayout *gridLayout_70;
    QPushButton *pushButton_optimization_MQ;
    MyComboBox *comboBox_delta_DE_method;
    QLabel *label_291;
    MyLineEdit *logedit_DE_factor;
    QLabel *label_wrong_DE_percentage;
    QLabel *label_used_distance_estimation;
    QLabel *label_292;
    QLabel *label_105;
    QLabel *label_290;
    QPushButton *pushButton_optimization_LQ;
    MyComboBox *comboBox_delta_DE_function;
    QPushButton *pushButton_optimization_HQ;
    QGroupBox *groupBox_detailLevel;
    QVBoxLayout *verticalLayout_7;
    QGridLayout *gridLayout;
    MyLineEdit *logedit_detail_level;
    QLabel *label_104;
    MyCheckBox *checkBox_connect_detail_level_2;
    MyGroupBox *groupCheck_constant_DE_threshold;
    QVBoxLayout *verticalLayout_44;
    QGridLayout *gridLayout_20;
    MyLineEdit *logedit_DE_thresh;
    QLabel *label_99;
    QPushButton *pushButton_calculate_dist_thresh;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_15;
    MyCheckBox *checkBox_iteration_threshold_mode;
    MyCheckBox *checkBox_interior_mode;
    QGroupBox *groupBox_10;
    QVBoxLayout *verticalLayout_116;
    QGridLayout *gridLayout_71;
    QLabel *label_106;
    MyCheckBox *checkBox_slow_shading;
    MyLineEdit *logedit_smoothness;
    MyGroupBox *groupCheck_advanced_quality;
    QVBoxLayout *verticalLayout_14;
    QGridLayout *gridLayout_2;
    MyLineEdit *logedit_rel_max_marching_step;
    QLabel *label_122;
    QLabel *label_115;
    QLabel *label_120;
    QLabel *label_116;
    MyLineEdit *logedit_detail_size_min;
    MyLineEdit *logedit_rel_min_marching_step;
    MyLineEdit *logedit_deltade_relative_delta;
    QLabel *label_113;
    MyLineEdit *logedit_abs_max_marching_step;
    QLabel *label_123;
    MyLineEdit *logedit_detail_size_max;
    QLabel *label_124;
    MyLineEdit *logedit_abs_min_marching_step;
    QLabel *label_125;
    MySpinBox *spinboxInt_max_raymarching_steps;
    QLabel *label_marching_omega;
    QWidget *widget_marching_omega;
    QHBoxLayout *horizontalLayout_marching_omega;
    QSlider *slider_marching_omega;
    MyDoubleSpinBox *spinbox_marching_omega;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *cRenderingFractalShapeTab)
    {
        if (cRenderingFractalShapeTab->objectName().isEmpty())
            cRenderingFractalShapeTab->setObjectName(QString::fromUtf8("cRenderingFractalShapeTab"));
        verticalLayout_2 = new QVBoxLayout(cRenderingFractalShapeTab);
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(2, 2, 2, 2);
        scrollArea = new QScrollArea(cRenderingFractalShapeTab);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 417, 1082));
        verticalLayout_6 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_6->setSpacing(2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(2, 2, 2, 2);
        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_114 = new QVBoxLayout(groupBox);
        verticalLayout_114->setSpacing(2);
        verticalLayout_114->setObjectName(QString::fromUtf8("verticalLayout_114"));
        verticalLayout_114->setContentsMargins(2, 2, 2, 2);
        gridLayout_69 = new QGridLayout();
        gridLayout_69->setSpacing(2);
        gridLayout_69->setObjectName(QString::fromUtf8("gridLayout_69"));
        gridLayout_69->setContentsMargins(-1, 0, -1, -1);
        label_284 = new QLabel(groupBox);
        label_284->setObjectName(QString::fromUtf8("label_284"));

        gridLayout_69->addWidget(label_284, 0, 0, 1, 1);

        logedit_bailout = new MyLineEdit(groupBox);
        logedit_bailout->setObjectName(QString::fromUtf8("logedit_bailout"));

        gridLayout_69->addWidget(logedit_bailout, 1, 1, 1, 1);

        checkBox_use_default_bailout = new MyCheckBox(groupBox);
        checkBox_use_default_bailout->setObjectName(QString::fromUtf8("checkBox_use_default_bailout"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(checkBox_use_default_bailout->sizePolicy().hasHeightForWidth());
        checkBox_use_default_bailout->setSizePolicy(sizePolicy);

        gridLayout_69->addWidget(checkBox_use_default_bailout, 2, 0, 1, 2);

        spinboxInt_N = new MySpinBox(groupBox);
        spinboxInt_N->setObjectName(QString::fromUtf8("spinboxInt_N"));
        sizePolicy.setHeightForWidth(spinboxInt_N->sizePolicy().hasHeightForWidth());
        spinboxInt_N->setSizePolicy(sizePolicy);
        spinboxInt_N->setMinimum(1);
        spinboxInt_N->setMaximum(9999);

        gridLayout_69->addWidget(spinboxInt_N, 0, 1, 1, 1);

        label_222 = new QLabel(groupBox);
        label_222->setObjectName(QString::fromUtf8("label_222"));

        gridLayout_69->addWidget(label_222, 1, 0, 1, 1);


        verticalLayout_114->addLayout(gridLayout_69);

        horizontalLayout_auto_iter = new QHBoxLayout();
        horizontalLayout_auto_iter->setSpacing(4);
        horizontalLayout_auto_iter->setObjectName(QString::fromUtf8("horizontalLayout_auto_iter"));
        pushButton_auto_iter_bailout = new QPushButton(groupBox);
        pushButton_auto_iter_bailout->setObjectName(QString::fromUtf8("pushButton_auto_iter_bailout"));

        horizontalLayout_auto_iter->addWidget(pushButton_auto_iter_bailout);

        pushButton_auto_slot_iter = new QPushButton(groupBox);
        pushButton_auto_slot_iter->setObjectName(QString::fromUtf8("pushButton_auto_slot_iter"));

        horizontalLayout_auto_iter->addWidget(pushButton_auto_slot_iter);


        verticalLayout_114->addLayout(horizontalLayout_auto_iter);

        label_auto_iter_result = new QLabel(groupBox);
        label_auto_iter_result->setObjectName(QString::fromUtf8("label_auto_iter_result"));
        label_auto_iter_result->setWordWrap(true);

        verticalLayout_114->addWidget(label_auto_iter_result);


        verticalLayout_6->addWidget(groupBox);

        groupBox_distanceEstimation = new QGroupBox(scrollAreaWidgetContents);
        groupBox_distanceEstimation->setObjectName(QString::fromUtf8("groupBox_distanceEstimation"));
        verticalLayout_115 = new QVBoxLayout(groupBox_distanceEstimation);
        verticalLayout_115->setSpacing(2);
        verticalLayout_115->setObjectName(QString::fromUtf8("verticalLayout_115"));
        verticalLayout_115->setContentsMargins(2, 2, 2, 2);
        gridLayout_70 = new QGridLayout();
        gridLayout_70->setSpacing(2);
        gridLayout_70->setObjectName(QString::fromUtf8("gridLayout_70"));
        gridLayout_70->setContentsMargins(-1, 0, -1, -1);
        pushButton_optimization_MQ = new QPushButton(groupBox_distanceEstimation);
        pushButton_optimization_MQ->setObjectName(QString::fromUtf8("pushButton_optimization_MQ"));

        gridLayout_70->addWidget(pushButton_optimization_MQ, 2, 1, 1, 2);

        comboBox_delta_DE_method = new MyComboBox(groupBox_distanceEstimation);
        comboBox_delta_DE_method->addItem(QString());
        comboBox_delta_DE_method->addItem(QString());
        comboBox_delta_DE_method->addItem(QString());
        comboBox_delta_DE_method->setObjectName(QString::fromUtf8("comboBox_delta_DE_method"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox_delta_DE_method->sizePolicy().hasHeightForWidth());
        comboBox_delta_DE_method->setSizePolicy(sizePolicy1);

        gridLayout_70->addWidget(comboBox_delta_DE_method, 5, 1, 1, 2);

        label_291 = new QLabel(groupBox_distanceEstimation);
        label_291->setObjectName(QString::fromUtf8("label_291"));

        gridLayout_70->addWidget(label_291, 5, 0, 1, 1);

        logedit_DE_factor = new MyLineEdit(groupBox_distanceEstimation);
        logedit_DE_factor->setObjectName(QString::fromUtf8("logedit_DE_factor"));

        gridLayout_70->addWidget(logedit_DE_factor, 0, 2, 1, 1);

        label_wrong_DE_percentage = new QLabel(groupBox_distanceEstimation);
        label_wrong_DE_percentage->setObjectName(QString::fromUtf8("label_wrong_DE_percentage"));

        gridLayout_70->addWidget(label_wrong_DE_percentage, 4, 0, 1, 3);

        label_used_distance_estimation = new QLabel(groupBox_distanceEstimation);
        label_used_distance_estimation->setObjectName(QString::fromUtf8("label_used_distance_estimation"));

        gridLayout_70->addWidget(label_used_distance_estimation, 7, 0, 1, 3);

        label_292 = new QLabel(groupBox_distanceEstimation);
        label_292->setObjectName(QString::fromUtf8("label_292"));

        gridLayout_70->addWidget(label_292, 1, 0, 3, 1);

        label_105 = new QLabel(groupBox_distanceEstimation);
        label_105->setObjectName(QString::fromUtf8("label_105"));

        gridLayout_70->addWidget(label_105, 0, 0, 1, 1);

        label_290 = new QLabel(groupBox_distanceEstimation);
        label_290->setObjectName(QString::fromUtf8("label_290"));

        gridLayout_70->addWidget(label_290, 6, 0, 1, 1);

        pushButton_optimization_LQ = new QPushButton(groupBox_distanceEstimation);
        pushButton_optimization_LQ->setObjectName(QString::fromUtf8("pushButton_optimization_LQ"));

        gridLayout_70->addWidget(pushButton_optimization_LQ, 1, 1, 1, 2);

        comboBox_delta_DE_function = new MyComboBox(groupBox_distanceEstimation);
        comboBox_delta_DE_function->addItem(QString());
        comboBox_delta_DE_function->addItem(QString());
        comboBox_delta_DE_function->addItem(QString());
        comboBox_delta_DE_function->addItem(QString());
        comboBox_delta_DE_function->addItem(QString());
        comboBox_delta_DE_function->addItem(QString());
        comboBox_delta_DE_function->addItem(QString());
        comboBox_delta_DE_function->setObjectName(QString::fromUtf8("comboBox_delta_DE_function"));
        comboBox_delta_DE_function->setEnabled(true);
        sizePolicy1.setHeightForWidth(comboBox_delta_DE_function->sizePolicy().hasHeightForWidth());
        comboBox_delta_DE_function->setSizePolicy(sizePolicy1);

        gridLayout_70->addWidget(comboBox_delta_DE_function, 6, 1, 1, 2);

        pushButton_optimization_HQ = new QPushButton(groupBox_distanceEstimation);
        pushButton_optimization_HQ->setObjectName(QString::fromUtf8("pushButton_optimization_HQ"));

        gridLayout_70->addWidget(pushButton_optimization_HQ, 3, 1, 1, 2);


        verticalLayout_115->addLayout(gridLayout_70);


        verticalLayout_6->addWidget(groupBox_distanceEstimation);

        groupBox_detailLevel = new QGroupBox(scrollAreaWidgetContents);
        groupBox_detailLevel->setObjectName(QString::fromUtf8("groupBox_detailLevel"));
        verticalLayout_7 = new QVBoxLayout(groupBox_detailLevel);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(2, 2, 2, 2);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        logedit_detail_level = new MyLineEdit(groupBox_detailLevel);
        logedit_detail_level->setObjectName(QString::fromUtf8("logedit_detail_level"));

        gridLayout->addWidget(logedit_detail_level, 0, 1, 1, 1);

        label_104 = new QLabel(groupBox_detailLevel);
        label_104->setObjectName(QString::fromUtf8("label_104"));

        gridLayout->addWidget(label_104, 0, 0, 1, 1);


        verticalLayout_7->addLayout(gridLayout);

        checkBox_connect_detail_level_2 = new MyCheckBox(groupBox_detailLevel);
        checkBox_connect_detail_level_2->setObjectName(QString::fromUtf8("checkBox_connect_detail_level_2"));

        verticalLayout_7->addWidget(checkBox_connect_detail_level_2);

        groupCheck_constant_DE_threshold = new MyGroupBox(groupBox_detailLevel);
        groupCheck_constant_DE_threshold->setObjectName(QString::fromUtf8("groupCheck_constant_DE_threshold"));
        groupCheck_constant_DE_threshold->setCheckable(true);
        groupCheck_constant_DE_threshold->setChecked(true);
        verticalLayout_44 = new QVBoxLayout(groupCheck_constant_DE_threshold);
        verticalLayout_44->setSpacing(2);
        verticalLayout_44->setObjectName(QString::fromUtf8("verticalLayout_44"));
        verticalLayout_44->setContentsMargins(2, 2, 2, 2);
        gridLayout_20 = new QGridLayout();
        gridLayout_20->setSpacing(2);
        gridLayout_20->setObjectName(QString::fromUtf8("gridLayout_20"));
        logedit_DE_thresh = new MyLineEdit(groupCheck_constant_DE_threshold);
        logedit_DE_thresh->setObjectName(QString::fromUtf8("logedit_DE_thresh"));

        gridLayout_20->addWidget(logedit_DE_thresh, 0, 1, 1, 1);

        label_99 = new QLabel(groupCheck_constant_DE_threshold);
        label_99->setObjectName(QString::fromUtf8("label_99"));

        gridLayout_20->addWidget(label_99, 0, 0, 1, 1);


        verticalLayout_44->addLayout(gridLayout_20);

        pushButton_calculate_dist_thresh = new QPushButton(groupCheck_constant_DE_threshold);
        pushButton_calculate_dist_thresh->setObjectName(QString::fromUtf8("pushButton_calculate_dist_thresh"));

        verticalLayout_44->addWidget(pushButton_calculate_dist_thresh);


        verticalLayout_7->addWidget(groupCheck_constant_DE_threshold);


        verticalLayout_6->addWidget(groupBox_detailLevel);

        groupBox_3 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_15 = new QVBoxLayout(groupBox_3);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        verticalLayout_15->setContentsMargins(2, 2, 2, 2);
        checkBox_iteration_threshold_mode = new MyCheckBox(groupBox_3);
        checkBox_iteration_threshold_mode->setObjectName(QString::fromUtf8("checkBox_iteration_threshold_mode"));
        sizePolicy.setHeightForWidth(checkBox_iteration_threshold_mode->sizePolicy().hasHeightForWidth());
        checkBox_iteration_threshold_mode->setSizePolicy(sizePolicy);

        verticalLayout_15->addWidget(checkBox_iteration_threshold_mode);

        checkBox_interior_mode = new MyCheckBox(groupBox_3);
        checkBox_interior_mode->setObjectName(QString::fromUtf8("checkBox_interior_mode"));
        sizePolicy.setHeightForWidth(checkBox_interior_mode->sizePolicy().hasHeightForWidth());
        checkBox_interior_mode->setSizePolicy(sizePolicy);

        verticalLayout_15->addWidget(checkBox_interior_mode);


        verticalLayout_6->addWidget(groupBox_3);

        groupBox_10 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        verticalLayout_116 = new QVBoxLayout(groupBox_10);
        verticalLayout_116->setSpacing(2);
        verticalLayout_116->setObjectName(QString::fromUtf8("verticalLayout_116"));
        verticalLayout_116->setContentsMargins(2, 2, 2, 2);
        gridLayout_71 = new QGridLayout();
        gridLayout_71->setObjectName(QString::fromUtf8("gridLayout_71"));
        gridLayout_71->setContentsMargins(-1, 0, -1, -1);
        label_106 = new QLabel(groupBox_10);
        label_106->setObjectName(QString::fromUtf8("label_106"));

        gridLayout_71->addWidget(label_106, 0, 0, 1, 1);

        checkBox_slow_shading = new MyCheckBox(groupBox_10);
        checkBox_slow_shading->setObjectName(QString::fromUtf8("checkBox_slow_shading"));
        sizePolicy.setHeightForWidth(checkBox_slow_shading->sizePolicy().hasHeightForWidth());
        checkBox_slow_shading->setSizePolicy(sizePolicy);

        gridLayout_71->addWidget(checkBox_slow_shading, 1, 0, 1, 2);

        logedit_smoothness = new MyLineEdit(groupBox_10);
        logedit_smoothness->setObjectName(QString::fromUtf8("logedit_smoothness"));

        gridLayout_71->addWidget(logedit_smoothness, 0, 1, 1, 1);


        verticalLayout_116->addLayout(gridLayout_71);


        verticalLayout_6->addWidget(groupBox_10);

        groupCheck_advanced_quality = new MyGroupBox(scrollAreaWidgetContents);
        groupCheck_advanced_quality->setObjectName(QString::fromUtf8("groupCheck_advanced_quality"));
        groupCheck_advanced_quality->setCheckable(true);
        verticalLayout_14 = new QVBoxLayout(groupCheck_advanced_quality);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(2, 2, 2, 2);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(-1, 0, -1, -1);
        logedit_rel_max_marching_step = new MyLineEdit(groupCheck_advanced_quality);
        logedit_rel_max_marching_step->setObjectName(QString::fromUtf8("logedit_rel_max_marching_step"));

        gridLayout_2->addWidget(logedit_rel_max_marching_step, 2, 1, 1, 1);

        label_122 = new QLabel(groupCheck_advanced_quality);
        label_122->setObjectName(QString::fromUtf8("label_122"));
        label_122->setWordWrap(true);

        gridLayout_2->addWidget(label_122, 5, 0, 1, 1);

        label_115 = new QLabel(groupCheck_advanced_quality);
        label_115->setObjectName(QString::fromUtf8("label_115"));
        label_115->setWordWrap(true);

        gridLayout_2->addWidget(label_115, 2, 0, 1, 1);

        label_120 = new QLabel(groupCheck_advanced_quality);
        label_120->setObjectName(QString::fromUtf8("label_120"));
        label_120->setWordWrap(true);

        gridLayout_2->addWidget(label_120, 1, 0, 1, 1);

        label_116 = new QLabel(groupCheck_advanced_quality);
        label_116->setObjectName(QString::fromUtf8("label_116"));
        label_116->setWordWrap(true);

        gridLayout_2->addWidget(label_116, 3, 0, 1, 1);

        logedit_detail_size_min = new MyLineEdit(groupCheck_advanced_quality);
        logedit_detail_size_min->setObjectName(QString::fromUtf8("logedit_detail_size_min"));

        gridLayout_2->addWidget(logedit_detail_size_min, 5, 1, 1, 1);

        logedit_rel_min_marching_step = new MyLineEdit(groupCheck_advanced_quality);
        logedit_rel_min_marching_step->setObjectName(QString::fromUtf8("logedit_rel_min_marching_step"));

        gridLayout_2->addWidget(logedit_rel_min_marching_step, 3, 1, 1, 1);

        logedit_deltade_relative_delta = new MyLineEdit(groupCheck_advanced_quality);
        logedit_deltade_relative_delta->setObjectName(QString::fromUtf8("logedit_deltade_relative_delta"));

        gridLayout_2->addWidget(logedit_deltade_relative_delta, 6, 1, 1, 1);

        label_113 = new QLabel(groupCheck_advanced_quality);
        label_113->setObjectName(QString::fromUtf8("label_113"));
        label_113->setWordWrap(true);

        gridLayout_2->addWidget(label_113, 0, 0, 1, 1);

        logedit_abs_max_marching_step = new MyLineEdit(groupCheck_advanced_quality);
        logedit_abs_max_marching_step->setObjectName(QString::fromUtf8("logedit_abs_max_marching_step"));

        gridLayout_2->addWidget(logedit_abs_max_marching_step, 0, 1, 1, 1);

        label_123 = new QLabel(groupCheck_advanced_quality);
        label_123->setObjectName(QString::fromUtf8("label_123"));
        label_123->setWordWrap(true);

        gridLayout_2->addWidget(label_123, 4, 0, 1, 1);

        logedit_detail_size_max = new MyLineEdit(groupCheck_advanced_quality);
        logedit_detail_size_max->setObjectName(QString::fromUtf8("logedit_detail_size_max"));

        gridLayout_2->addWidget(logedit_detail_size_max, 4, 1, 1, 1);

        label_124 = new QLabel(groupCheck_advanced_quality);
        label_124->setObjectName(QString::fromUtf8("label_124"));
        label_124->setWordWrap(true);

        gridLayout_2->addWidget(label_124, 6, 0, 1, 1);

        logedit_abs_min_marching_step = new MyLineEdit(groupCheck_advanced_quality);
        logedit_abs_min_marching_step->setObjectName(QString::fromUtf8("logedit_abs_min_marching_step"));

        gridLayout_2->addWidget(logedit_abs_min_marching_step, 1, 1, 1, 1);

        label_125 = new QLabel(groupCheck_advanced_quality);
        label_125->setObjectName(QString::fromUtf8("label_125"));
        label_125->setWordWrap(true);

        gridLayout_2->addWidget(label_125, 7, 0, 1, 1);

        spinboxInt_max_raymarching_steps = new MySpinBox(groupCheck_advanced_quality);
        spinboxInt_max_raymarching_steps->setObjectName(QString::fromUtf8("spinboxInt_max_raymarching_steps"));
        sizePolicy.setHeightForWidth(spinboxInt_max_raymarching_steps->sizePolicy().hasHeightForWidth());
        spinboxInt_max_raymarching_steps->setSizePolicy(sizePolicy);
        spinboxInt_max_raymarching_steps->setMinimum(1);
        spinboxInt_max_raymarching_steps->setMaximum(10000000);
        spinboxInt_max_raymarching_steps->setValue(10000);

        gridLayout_2->addWidget(spinboxInt_max_raymarching_steps, 7, 1, 1, 1);

        label_marching_omega = new QLabel(groupCheck_advanced_quality);
        label_marching_omega->setObjectName(QString::fromUtf8("label_marching_omega"));
        label_marching_omega->setWordWrap(true);

        gridLayout_2->addWidget(label_marching_omega, 8, 0, 1, 1);

        widget_marching_omega = new QWidget(groupCheck_advanced_quality);
        widget_marching_omega->setObjectName(QString::fromUtf8("widget_marching_omega"));
        horizontalLayout_marching_omega = new QHBoxLayout(widget_marching_omega);
        horizontalLayout_marching_omega->setSpacing(4);
        horizontalLayout_marching_omega->setObjectName(QString::fromUtf8("horizontalLayout_marching_omega"));
        horizontalLayout_marching_omega->setContentsMargins(0, 0, 0, 0);
        slider_marching_omega = new QSlider(widget_marching_omega);
        slider_marching_omega->setObjectName(QString::fromUtf8("slider_marching_omega"));
        slider_marching_omega->setMinimum(100);
        slider_marching_omega->setMaximum(200);
        slider_marching_omega->setValue(120);
        slider_marching_omega->setOrientation(Qt::Horizontal);

        horizontalLayout_marching_omega->addWidget(slider_marching_omega);

        spinbox_marching_omega = new MyDoubleSpinBox(widget_marching_omega);
        spinbox_marching_omega->setObjectName(QString::fromUtf8("spinbox_marching_omega"));
        spinbox_marching_omega->setDecimals(2);
        spinbox_marching_omega->setMinimum(1.000000000000000);
        spinbox_marching_omega->setMaximum(2.000000000000000);
        spinbox_marching_omega->setSingleStep(0.050000000000000);
        spinbox_marching_omega->setValue(1.200000000000000);

        horizontalLayout_marching_omega->addWidget(spinbox_marching_omega);


        gridLayout_2->addWidget(widget_marching_omega, 8, 1, 1, 1);


        verticalLayout_14->addLayout(gridLayout_2);


        verticalLayout_6->addWidget(groupCheck_advanced_quality);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);


        retranslateUi(cRenderingFractalShapeTab);

        QMetaObject::connectSlotsByName(cRenderingFractalShapeTab);
    } // setupUi

    void retranslateUi(QWidget *cRenderingFractalShapeTab)
    {
        groupBox->setTitle(QCoreApplication::translate("cRenderingFractalShapeTab", "Fractal formula iterations", nullptr));
        label_284->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Maximum number\n"
"of fractal iterations\n"
"(maxiter):", nullptr));
#if QT_CONFIG(tooltip)
        logedit_bailout->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "<html><head/><body><p>The vector values are checked during each iteration of fractal formula to see if they have reached a critical 'escape' condition or 'bailout'. If that condition is reached, the calculation is stopped. Condition is: if length of vector is greater than bailout, then break iteration loop.</p><p>In some cases higher value can increase image quality, but it will increase rendering time.</p><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBox_use_default_bailout->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "<html><head/><body><p>Enables using default (recommended) bailout value. Each fractal formula has different optimal bailout value.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_use_default_bailout->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Use default bailout for\n"
"each fractal formula", nullptr));
#if QT_CONFIG(tooltip)
        spinboxInt_N->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "<html><head/><body><p>The higher the maximum number of iterations (&quot;maxiter&quot;) is, the more detail and subtlety emerge in the final image, but also the longer time it will take to calculate the fractal image. </p><p>In normal operation this should be set as high as possible because &quot;Distance estimation&quot; algorithm limits number of iteration (almost no influence on rendering speed)</p><p>When <span style=\" font-style:italic;\">Stop at maximum iteration</span> is selected, then this parameter controls detail level.<br/></p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>maxiter = 10</p></td><td><p>maxiter = 15</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/image - maxiter - 10.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - maxiter - 15.jpg\"/></p></td></tr></table></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_222->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Bailout\n"
"(escape condition):", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_auto_iter_bailout->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "Automatically estimates optimal maxiter (N) and bailout for the current fractal and camera position.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_auto_iter_bailout->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Auto N + Bailout", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_auto_slot_iter->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "Estimates formula_maxiter for each enabled hybrid formula slot.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_auto_slot_iter->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Auto slot maxiter", nullptr));
        label_auto_iter_result->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "-", nullptr));
        groupBox_distanceEstimation->setTitle(QCoreApplication::translate("cRenderingFractalShapeTab", "Distance estimation (quality control)", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_optimization_MQ->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "<html><head/><body><p>Optimize 'Raymarching step multiplier' for medium image quality.</p><p>It gives 0.1% of wrong distance estimations (pixels with potential noise)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_optimization_MQ->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Medium quality", nullptr));
        comboBox_delta_DE_method->setItemText(0, QCoreApplication::translate("cRenderingFractalShapeTab", "Automatic (analytic if possible)", nullptr));
        comboBox_delta_DE_method->setItemText(1, QCoreApplication::translate("cRenderingFractalShapeTab", "Force \"Delta DE\" method", nullptr));
        comboBox_delta_DE_method->setItemText(2, QCoreApplication::translate("cRenderingFractalShapeTab", "Force \"Analytic DE\" method", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_delta_DE_method->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "<html><head/><body><p>Distance estimation is a method which calculates approximate distance to fractal surface from any point in space.</p><p>- Automatic mode uses distance estimation method defined for selected fractal</p><p>- Force &quot;Delta DE&quot; method uses  Delta DE algorithm which is slower but works also with untypical fractal configurations<br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_291->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Distance estimation\n"
"method:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_DE_factor->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "<html><head/><body><p>This parameter has the biggest influence on overall quality of image and rendering speed.</p><p>Higher value gives faster rendering but more noise on image.</p><p>When rays are traced, for each step there are estimated distances to the fractal surface. Optimally , the jump distance for every ray-marching step would be equal to the estimated distance. This would produce a small number of steps and good quality. However the distance can be only estimated, so it's not always accurate. It can produce oversteppings which will be visible on the image as random noise.</p><p>In some cases you need to adjust  this parameter to find a balance between acceptable image quality and a reasonable rendering time.</p><p><br/></p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>step multiplier = 1.0 (optimal - good quality and fast)</p></td><td><p>step multiplier = 5 (visible strong noise on image)</p></td></"
                        "tr><tr><td><p><img src=\":/tooltips/tooltips_images/image - DE step factor 1.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - DE step factor 4.jpg\"/></p></td></tr></table><p>As a quality indicator, the<span style=\" font-style:italic;\">Percentage of wrong distance estimations</span> ( visible in <span style=\" font-style:italic;\">Statistics</span> dock ) can be used . </p><p>To optimize this parameter the histograms of iteration count and ray-marching step count,  can be used .</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        label_wrong_DE_percentage->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "<html><head/><body><p>Percentage of points on image which are probably calculated wrong.</p><p>Higher value usually means more visible noise or artifacts on image.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_wrong_DE_percentage->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Percentage of wrong distance estimations:", nullptr));
        label_used_distance_estimation->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Used distance estimation algorithm:", nullptr));
        label_292->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Optimization:", nullptr));
        label_105->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Raymarching step mult.\n"
"(controls quality):", nullptr));
        label_290->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Distance estimation\n"
"function:", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_optimization_LQ->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "<html><head/><body><p>Optimize 'Raymarching step multiplier' for low image quality and fast rendering</p><p>It gives 1% of wrong distance estimations (pixels with potential noise)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_optimization_LQ->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Low quality", nullptr));
        comboBox_delta_DE_function->setItemText(0, QCoreApplication::translate("cRenderingFractalShapeTab", "Automatic", nullptr));
        comboBox_delta_DE_function->setItemText(1, QCoreApplication::translate("cRenderingFractalShapeTab", "Linear", nullptr));
        comboBox_delta_DE_function->setItemText(2, QCoreApplication::translate("cRenderingFractalShapeTab", "Logarithmic", nullptr));
        comboBox_delta_DE_function->setItemText(3, QCoreApplication::translate("cRenderingFractalShapeTab", "Pseudo Kleinian", nullptr));
        comboBox_delta_DE_function->setItemText(4, QCoreApplication::translate("cRenderingFractalShapeTab", "JosKleinian", nullptr));
        comboBox_delta_DE_function->setItemText(5, QCoreApplication::translate("cRenderingFractalShapeTab", "Custom", nullptr));
        comboBox_delta_DE_function->setItemText(6, QCoreApplication::translate("cRenderingFractalShapeTab", "MaxAxis", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_delta_DE_function->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "<html><head/><body><p>Distance estimation function is specific to the fractal formula calculations.</p><p>In some fractal fomulas the length of the iteration vector increases exponentially and some in a linear manner.</p><p>- Automatic mode - finds the probable best function based on the fractal formulas used.</p><p>- Logarithmic - the best for fractals with exponential growth of iteration vector (e.g. Mandelbulb)</p><p>- Linear - the best for fractals with linear growth of iteration vector (e.g. Mandelbox, IFS)</p><p>- Pseudo Kleinian - linear growth distance estimation function for working with Pseudo Kleinian formulas</p><p>- JosKleinian - linear growth distance estimation function for working with JosKleinian formulas</p><p>- Custom - distance estimation function where the distance estimation out.distance is calculated entirely in the formula. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        pushButton_optimization_HQ->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "<html><head/><body><p>Optimize 'Raymarching step multiplier' for high image quality and slow rendering</p><p>It gives 0.01% of wrong distance estimations (pixels with potential noise)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_optimization_HQ->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "High quality", nullptr));
        groupBox_detailLevel->setTitle(QCoreApplication::translate("cRenderingFractalShapeTab", "Detail level", nullptr));
#if QT_CONFIG(tooltip)
        logedit_detail_level->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "<html><head/><body><p>Controls how much detail will be visible on fractal surface. When it is set to 1.0, then minimum visible detail has size of 2 pixels.</p><p>Higher value gives more detailed image, but slows down rendering.</p><p><br/></p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>detail level 0.2</p></td><td><p>detail level 0.5</p></td><td><p>detail level 1.0</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/image - resolution 0.2.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - resolution 0.5.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - resolution 1.jpg\"/></p></td></tr></table></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_104->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Detail level:", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_connect_detail_level_2->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "<html><head/><body><p>When this option is enabled, the fractal appearance is maintained at all resolutions. </p><p>The fractal detail level will be automatically adjusted to match any change of image resolution. </p><p>For instance, if the resolution is doubled then the detail level will be reduced by half.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_connect_detail_level_2->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Connect fractal detail level\n"
"with image resolution", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_constant_DE_threshold->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "<html><head/><body><p>When not enabled, the program automatically reduces the level of detail for the farthest regions of the fractal. If you go closer to the fractal surface, the program increases the level of detail.</p><p>If enabled, then in every region of the fractal,  the detail level (size) will be the same.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_constant_DE_threshold->setTitle(QCoreApplication::translate("cRenderingFractalShapeTab", "Constant detai&l size", nullptr));
#if QT_CONFIG(tooltip)
        logedit_DE_thresh->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "<html><head/><body><p>Distance threshold which defines detail size.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_99->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "distance threshold:", nullptr));
        pushButton_calculate_dist_thresh->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Calculate threshold", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("cRenderingFractalShapeTab", "Shape control", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_iteration_threshold_mode->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "<html><head/><body><p>Switches off stopping of ray-marching at distance threshold. When it's checked detail level is controlled with <span style=\" font-style:italic;\">Max. fractal iterations</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_iteration_threshold_mode->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Stop at maximum iteration (at maxiter)", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_interior_mode->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "<html><head/><body><p>Makes fractals hollow inside. It gives interesting results when a  cross section of the fractal is rendered using <span style=\" font-style:italic;\">Limits (box)</span> feature. </p><p>This effect is very slow to render because of the high number of iterations required to render the inside of the fractal. To speed up rendering try  reducing Max. fractal iterations .</p><p><br/></p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>interior mode enabled</p></td><td><p>interior mode disabled</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/image - interior enabled.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - interior disabled.jpg\"/></p></td></tr></table></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_interior_mode->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Interior mode", nullptr));
        groupBox_10->setTitle(QCoreApplication::translate("cRenderingFractalShapeTab", "Surface (normal vector) calculation:", nullptr));
        label_106->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Smoothness:", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_slow_shading->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "<html><head/><body><p>Enables mode dedicated for fractals where it is difficult to calculate surface normal vectors. Rendering is much slower, but fractal surface is much smoother.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_slow_shading->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Non-DE shading mode (slow)", nullptr));
#if QT_CONFIG(tooltip)
        logedit_smoothness->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "<html><head/><body><p>Smoothness parameter defines averaging area for normal vector calculation.</p><p>Higher value gives smoother fractal surface.</p><p><br/></p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>smoothness = 0.1</p></td><td><p>smoothness = 1.0</p></td><td><p>smoothness = 5.0</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/image - smoothness 0.1.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - smoothness 1.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - smoothness 5.jpg\"/></p></td></tr></table></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        groupCheck_advanced_quality->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "Access advanced quality settings for fine-tuning raymarching steps, detail size, and rendering precision.", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_advanced_quality->setTitle(QCoreApplication::translate("cRenderingFractalShapeTab", "Advanced &quality settings", nullptr));
#if QT_CONFIG(tooltip)
        logedit_rel_max_marching_step->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "<html><head/><body><p>Maximum relative step for raymarching. It is related to local detail size. Close to the camera, the limit is lower (visible details are smaller).</p><p>Lower value can improve calculation accuracy far from the fractal surface.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_122->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Minimum detail size:", nullptr));
        label_115->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Relative maximum step:", nullptr));
        label_120->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Absolute minimum step:", nullptr));
        label_116->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Relative minimum step:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_detail_size_min->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "<html><head/><body><p>Higher value can produce less detail in areas close to the camera.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_rel_min_marching_step->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "<html><head/><body><p>Minimum relative step for raymarching. It is related to local detail size. Close to the camera, the limit is lower (visible details are smaller).</p><p>Higher value can speed up calculation of raymarching in areas close to the fractal surface.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_deltade_relative_delta->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "<html><head/><body><p>Controls delta used in DeltaDE distance algorithm. Tuning of this parameter can improve quality when there is noise caused by inaccurate distance estimation.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_113->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Absolute maximum step:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_abs_max_marching_step->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "<html><head/><body><p>Maximum step for raymarching. Lower value can improve calculation accuracy in areas far from the fractal surface.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_123->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Maximum detail size:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_detail_size_max->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "<html><head/><body><p>Lower value can produce more detail in areas far from the camera.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_124->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "deltaDE relative delta:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_abs_min_marching_step->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "<html><head/><body><p>Minimum step for raymarching. Higher value can speed up rendering. It will reduce the number of raymarching steps close to the fractal surface.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_125->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "maximum number\n"
"of raymarching steps", nullptr));
#if QT_CONFIG(tooltip)
        spinboxInt_max_raymarching_steps->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "Maximum number of raymarching steps per pixel. Limits how many steps are taken when rendering each pixel.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        label_marching_omega->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "Sphere tracing over-relaxation factor. Values above 1.0 allow larger steps when the distance field is reliable, reducing march iterations. Too high may cause surface overshoot.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_marching_omega->setText(QCoreApplication::translate("cRenderingFractalShapeTab", "Marching omega\n"
"(over-relaxation):", nullptr));
#if QT_CONFIG(tooltip)
        slider_marching_omega->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "Sphere tracing over-relaxation (1.0 = disabled, ~1.2 = faster).", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinbox_marching_omega->setToolTip(QCoreApplication::translate("cRenderingFractalShapeTab", "Sphere tracing over-relaxation factor (1.0\342\200\2232.0). Used by Fast and Limited OpenCL engines.", nullptr));
#endif // QT_CONFIG(tooltip)
        (void)cRenderingFractalShapeTab;
    } // retranslateUi

};

namespace Ui {
    class cRenderingFractalShapeTab: public Ui_cRenderingFractalShapeTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RENDERING_FRACTAL_SHAPE_TAB_H
