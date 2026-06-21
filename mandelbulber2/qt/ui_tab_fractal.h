/********************************************************************************
** Form generated from reading UI file 'tab_fractal.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAB_FRACTAL_H
#define UI_TAB_FRACTAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "buton_load_settings_from_widget.h"
#include "buton_random_settings_from_widget.h"
#include "buton_reset_settings_from_widget.h"
#include "buton_save_settings_from_widget.h"
#include "formula_combo_box.h"
#include "material_selector.h"
#include "my_check_box.h"
#include "my_double_spin_box.h"
#include "my_group_box.h"
#include "my_line_edit.h"
#include "my_spin_box.h"

QT_BEGIN_NAMESPACE

class Ui_cTabFractal
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    cButtonRandomSettingsFromWidget *pushButton_local_randomize_2;
    cButtonLoadSettingsFromWidget *pushButton_local_load;
    cButtonSaveSettingsFromWidget *pushButton_local_save;
    cButtonResetSettingsFromWidget *pushButton_local_reset;
    QPushButton *pushButton_local_navi;
    QSpacerItem *horizontalSpacer_2;
    QFrame *frame_iterations_formula;
    QVBoxLayout *verticalLayout_56;
    QGridLayout *gridLayout_27;
    QPushButton *pushButton_reset_formula;
    MySpinBox *spinboxInt_formula_start_iteration;
    QLabel *label_formula_start_iteration;
    QLabel *label_formula_weight;
    cFormulaComboBox *comboBox_formula;
    MyDoubleSpinBox *spinbox_formula_weight;
    MySpinBox *spinboxInt_formula_iterations;
    QLabel *label_formula_iterations;
    MyCheckBox *checkBox_check_for_bailout;
    QLabel *label_formula_stop_iteration;
    MySpinBox *spinboxInt_formula_stop_iteration;
    MyCheckBox *checkBox_dont_add_c_constant;
    QGroupBox *groupBox_advanced_weight;
    QGridLayout *gridLayout_advanced_weight;
    QLabel *label_weight_mode;
    QComboBox *comboBox_weight_mode;
    QLabel *label_weight_static;
    MyDoubleSpinBox *spinbox_weight_static;
    QLabel *label_weight_iter_start;
    MySpinBox *spinboxInt_weight_iter_start;
    QLabel *label_weight_iter_end;
    MySpinBox *spinboxInt_weight_iter_end;
    QLabel *label_weight_start;
    MyDoubleSpinBox *spinbox_weight_start;
    QLabel *label_weight_end;
    MyDoubleSpinBox *spinbox_weight_end;
    QLabel *label_weight_blend_mode;
    QComboBox *comboBox_weight_blend_mode;
    QLabel *label_weight_de_base;
    MyDoubleSpinBox *spinbox_weight_de_base;
    QLabel *label_weight_de_sensitivity;
    MyDoubleSpinBox *spinbox_weight_de_sensitivity;
    QLabel *label_weight_de_threshold;
    MyDoubleSpinBox *spinbox_weight_de_threshold;
    QLabel *label_weight_de_mod_type;
    QComboBox *comboBox_weight_de_mod_type;
    QLabel *label_weight_zlength_base;
    MyDoubleSpinBox *spinbox_weight_zlength_base;
    QLabel *label_weight_zlength_sens;
    MyDoubleSpinBox *spinbox_weight_zlength_sens;
    QLabel *label_weight_zlength_threshold;
    MyDoubleSpinBox *spinbox_weight_zlength_threshold;
    QLabel *label_weight_zlength_mod_type;
    QComboBox *comboBox_weight_zlength_mod_type;
    QLabel *label_weight_condition_type;
    QComboBox *comboBox_weight_condition_type;
    QLabel *label_weight_condition_threshold;
    MyDoubleSpinBox *spinbox_weight_condition_threshold;
    QLabel *label_weight_true;
    MyDoubleSpinBox *spinbox_weight_true;
    QLabel *label_weight_false;
    MyDoubleSpinBox *spinbox_weight_false;
    QLabel *label_weight_condition_blend;
    QComboBox *comboBox_weight_condition_blend;
    QLabel *label_weight_orbit_trap_base;
    MyDoubleSpinBox *spinbox_weight_orbit_trap_base;
    QLabel *label_weight_orbit_trap_sensitivity;
    MyDoubleSpinBox *spinbox_weight_orbit_trap_sensitivity;
    QLabel *label_weight_orbit_trap_threshold;
    MyDoubleSpinBox *spinbox_weight_orbit_trap_threshold;
    QLabel *label_weight_orbit_trap_mod_type;
    QComboBox *comboBox_weight_orbit_trap_mod_type;
    QLabel *label_weight_curve_base;
    MyDoubleSpinBox *spinbox_weight_curve_base;
    QLabel *label_weight_curve_sensitivity;
    MyDoubleSpinBox *spinbox_weight_curve_sensitivity;
    QLabel *label_weight_curve_power;
    MyDoubleSpinBox *spinbox_weight_curve_power;
    QLabel *label_weight_curve_mod_type;
    QComboBox *comboBox_weight_curve_mod_type;
    QLabel *label_weight_de_ratio_scale;
    MyDoubleSpinBox *spinbox_weight_de_ratio_scale;
    QLabel *label_weight_de_ratio_offset;
    MyDoubleSpinBox *spinbox_weight_de_ratio_offset;
    QLabel *label_weight_de_ratio_mod_type;
    QComboBox *comboBox_weight_de_ratio_mod_type;
    QLabel *label_weight_adaptive_strength;
    MyDoubleSpinBox *spinbox_weight_adaptive_strength;
    QLabel *label_weight_floor;
    MyDoubleSpinBox *spinbox_weight_floor;
    QLabel *label_weight_ceiling;
    MyDoubleSpinBox *spinbox_weight_ceiling;
    QLabel *label_weight_gamma;
    MyDoubleSpinBox *spinbox_weight_gamma;
    MyCheckBox *checkBox_weight_invert;
    QLabel *label_weight_fade_in;
    MySpinBox *spinboxInt_weight_fade_in;
    QLabel *label_weight_fade_out;
    MySpinBox *spinboxInt_weight_fade_out;
    QLabel *label_weight_de_smooth_radius;
    MyDoubleSpinBox *spinbox_weight_de_smooth_radius;
    QLabel *label_weight_component_blend_curve;
    MyDoubleSpinBox *spinbox_weight_component_blend_curve;
    MyCheckBox *checkBox_weight_separate_components;
    QLabel *label_weight_z_vector;
    MyDoubleSpinBox *spinbox_weight_z_vector;
    QLabel *label_weight_de_component;
    MyDoubleSpinBox *spinbox_weight_de_component;
    QLabel *label_weight_dist_component;
    MyDoubleSpinBox *spinbox_weight_dist_component;
    QLabel *label_weight_color_component;
    MyDoubleSpinBox *spinbox_weight_color_component;
    QGroupBox *groupBox_formula_parameters;
    QVBoxLayout *verticalLayout_77;
    cButtonRandomSettingsFromWidget *pushButton_local_randomize;
    QVBoxLayout *verticalLayout_fractal;
    QGroupBox *groupBox_calculation_parameters;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    MySpinBox *spinboxInt_formula_maxiter;
    QLabel *label_305;
    MyGroupBox *groupCheck_smooth_de_combine_enable;
    QGridLayout *gridLayout_4;
    QLabel *label_306;
    MyLineEdit *logedit_smooth_de_combine_distance;
    QGroupBox *groupBox_c_constant_addition;
    QVBoxLayout *verticalLayout_120;
    MyGroupBox *groupCheck_julia_mode;
    QVBoxLayout *verticalLayout_121;
    QGridLayout *gridLayout_75;
    QLabel *label_300;
    QLabel *label_301;
    MyLineEdit *vect3_julia_c_y;
    MyLineEdit *vect3_julia_c_x;
    QLabel *label_302;
    QLabel *label_303;
    MyLineEdit *vect3_julia_c_z;
    QGridLayout *gridLayout_76;
    QLabel *label_352;
    MyDoubleSpinBox *spinbox3_fractal_constant_factor_x;
    MyDoubleSpinBox *spinbox3_fractal_constant_factor_y;
    MyDoubleSpinBox *spinbox3_fractal_constant_factor_z;
    QLabel *label_304;
    QLabel *label_351;
    QLabel *label_353;
    QLabel *label_295;
    MyDoubleSpinBox *spinbox_initial_waxis;
    QGroupBox *groupBox_material_fractal;
    QVBoxLayout *verticalLayout_63;
    cMaterialSelector *materialselector_formula_material_id;
    QGroupBox *groupBox_formula_transform;
    QVBoxLayout *verticalLayout_22;
    QGridLayout *gridLayout_41;
    QLabel *label_158;
    MyLineEdit *vect3_formula_position_z;
    QLabel *label_163;
    QLabel *label_157;
    QLabel *label_159;
    MyLineEdit *vect3_formula_position_y;
    MyDoubleSpinBox *spinboxd3_formula_rotation_z;
    MyDoubleSpinBox *spinboxd3_formula_rotation_y;
    QLabel *label_167;
    MyDoubleSpinBox *spinboxd3_formula_rotation_x;
    MyLineEdit *vect3_formula_position_x;
    MyLineEdit *vect3_formula_repeat_x;
    QLabel *label_160;
    QLabel *label_162;
    QLabel *label_161;
    MyLineEdit *vect3_formula_repeat_y;
    QLabel *label_165;
    MyLineEdit *vect3_formula_repeat_z;
    QLabel *label_166;
    QLabel *label_164;
    QLabel *label_168;
    MyLineEdit *logedit_formula_scale;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *cTabFractal)
    {
        if (cTabFractal->objectName().isEmpty())
            cTabFractal->setObjectName(QString::fromUtf8("cTabFractal"));
        cTabFractal->resize(440, 1045);
        verticalLayout = new QVBoxLayout(cTabFractal);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_local_randomize_2 = new cButtonRandomSettingsFromWidget(cTabFractal);
        pushButton_local_randomize_2->setObjectName(QString::fromUtf8("pushButton_local_randomize_2"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_local_randomize_2->sizePolicy().hasHeightForWidth());
        pushButton_local_randomize_2->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(pushButton_local_randomize_2);

        pushButton_local_load = new cButtonLoadSettingsFromWidget(cTabFractal);
        pushButton_local_load->setObjectName(QString::fromUtf8("pushButton_local_load"));

        horizontalLayout_2->addWidget(pushButton_local_load);

        pushButton_local_save = new cButtonSaveSettingsFromWidget(cTabFractal);
        pushButton_local_save->setObjectName(QString::fromUtf8("pushButton_local_save"));

        horizontalLayout_2->addWidget(pushButton_local_save);

        pushButton_local_reset = new cButtonResetSettingsFromWidget(cTabFractal);
        pushButton_local_reset->setObjectName(QString::fromUtf8("pushButton_local_reset"));

        horizontalLayout_2->addWidget(pushButton_local_reset);

        pushButton_local_navi = new QPushButton(cTabFractal);
        pushButton_local_navi->setObjectName(QString::fromUtf8("pushButton_local_navi"));
        sizePolicy.setHeightForWidth(pushButton_local_navi->sizePolicy().hasHeightForWidth());
        pushButton_local_navi->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(pushButton_local_navi);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        frame_iterations_formula = new QFrame(cTabFractal);
        frame_iterations_formula->setObjectName(QString::fromUtf8("frame_iterations_formula"));
        frame_iterations_formula->setFrameShape(QFrame::StyledPanel);
        frame_iterations_formula->setFrameShadow(QFrame::Raised);
        verticalLayout_56 = new QVBoxLayout(frame_iterations_formula);
        verticalLayout_56->setSpacing(2);
        verticalLayout_56->setObjectName(QString::fromUtf8("verticalLayout_56"));
        verticalLayout_56->setContentsMargins(2, 2, 2, 2);
        gridLayout_27 = new QGridLayout();
        gridLayout_27->setSpacing(2);
        gridLayout_27->setObjectName(QString::fromUtf8("gridLayout_27"));
        gridLayout_27->setContentsMargins(-1, 0, -1, -1);
        pushButton_reset_formula = new QPushButton(frame_iterations_formula);
        pushButton_reset_formula->setObjectName(QString::fromUtf8("pushButton_reset_formula"));

        gridLayout_27->addWidget(pushButton_reset_formula, 1, 0, 1, 2);

        spinboxInt_formula_start_iteration = new MySpinBox(frame_iterations_formula);
        spinboxInt_formula_start_iteration->setObjectName(QString::fromUtf8("spinboxInt_formula_start_iteration"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(spinboxInt_formula_start_iteration->sizePolicy().hasHeightForWidth());
        spinboxInt_formula_start_iteration->setSizePolicy(sizePolicy1);
        spinboxInt_formula_start_iteration->setMinimum(0);
        spinboxInt_formula_start_iteration->setMaximum(99999);
        spinboxInt_formula_start_iteration->setValue(0);

        gridLayout_27->addWidget(spinboxInt_formula_start_iteration, 6, 1, 1, 1);

        label_formula_start_iteration = new QLabel(frame_iterations_formula);
        label_formula_start_iteration->setObjectName(QString::fromUtf8("label_formula_start_iteration"));

        gridLayout_27->addWidget(label_formula_start_iteration, 6, 0, 1, 1);

        label_formula_weight = new QLabel(frame_iterations_formula);
        label_formula_weight->setObjectName(QString::fromUtf8("label_formula_weight"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_formula_weight->sizePolicy().hasHeightForWidth());
        label_formula_weight->setSizePolicy(sizePolicy2);

        gridLayout_27->addWidget(label_formula_weight, 3, 0, 1, 1);

        comboBox_formula = new cFormulaComboBox(frame_iterations_formula);
        comboBox_formula->setObjectName(QString::fromUtf8("comboBox_formula"));
        sizePolicy2.setHeightForWidth(comboBox_formula->sizePolicy().hasHeightForWidth());
        comboBox_formula->setSizePolicy(sizePolicy2);
        comboBox_formula->setMaxVisibleItems(50);

        gridLayout_27->addWidget(comboBox_formula, 0, 0, 1, 2);

        spinbox_formula_weight = new MyDoubleSpinBox(frame_iterations_formula);
        spinbox_formula_weight->setObjectName(QString::fromUtf8("spinbox_formula_weight"));
        sizePolicy1.setHeightForWidth(spinbox_formula_weight->sizePolicy().hasHeightForWidth());
        spinbox_formula_weight->setSizePolicy(sizePolicy1);
        spinbox_formula_weight->setDecimals(5);
        spinbox_formula_weight->setMaximum(1.000000000000000);
        spinbox_formula_weight->setSingleStep(0.010000000000000);

        gridLayout_27->addWidget(spinbox_formula_weight, 3, 1, 1, 1);

        spinboxInt_formula_iterations = new MySpinBox(frame_iterations_formula);
        spinboxInt_formula_iterations->setObjectName(QString::fromUtf8("spinboxInt_formula_iterations"));
        sizePolicy1.setHeightForWidth(spinboxInt_formula_iterations->sizePolicy().hasHeightForWidth());
        spinboxInt_formula_iterations->setSizePolicy(sizePolicy1);
        spinboxInt_formula_iterations->setMinimum(1);
        spinboxInt_formula_iterations->setMaximum(500);

        gridLayout_27->addWidget(spinboxInt_formula_iterations, 2, 1, 1, 1);

        label_formula_iterations = new QLabel(frame_iterations_formula);
        label_formula_iterations->setObjectName(QString::fromUtf8("label_formula_iterations"));
        sizePolicy2.setHeightForWidth(label_formula_iterations->sizePolicy().hasHeightForWidth());
        label_formula_iterations->setSizePolicy(sizePolicy2);

        gridLayout_27->addWidget(label_formula_iterations, 2, 0, 1, 1);

        checkBox_check_for_bailout = new MyCheckBox(frame_iterations_formula);
        checkBox_check_for_bailout->setObjectName(QString::fromUtf8("checkBox_check_for_bailout"));
        sizePolicy1.setHeightForWidth(checkBox_check_for_bailout->sizePolicy().hasHeightForWidth());
        checkBox_check_for_bailout->setSizePolicy(sizePolicy1);

        gridLayout_27->addWidget(checkBox_check_for_bailout, 5, 0, 1, 2);

        label_formula_stop_iteration = new QLabel(frame_iterations_formula);
        label_formula_stop_iteration->setObjectName(QString::fromUtf8("label_formula_stop_iteration"));

        gridLayout_27->addWidget(label_formula_stop_iteration, 7, 0, 1, 1);

        spinboxInt_formula_stop_iteration = new MySpinBox(frame_iterations_formula);
        spinboxInt_formula_stop_iteration->setObjectName(QString::fromUtf8("spinboxInt_formula_stop_iteration"));
        sizePolicy1.setHeightForWidth(spinboxInt_formula_stop_iteration->sizePolicy().hasHeightForWidth());
        spinboxInt_formula_stop_iteration->setSizePolicy(sizePolicy1);
        spinboxInt_formula_stop_iteration->setMaximum(99999);

        gridLayout_27->addWidget(spinboxInt_formula_stop_iteration, 7, 1, 1, 1);

        checkBox_dont_add_c_constant = new MyCheckBox(frame_iterations_formula);
        checkBox_dont_add_c_constant->setObjectName(QString::fromUtf8("checkBox_dont_add_c_constant"));
        sizePolicy1.setHeightForWidth(checkBox_dont_add_c_constant->sizePolicy().hasHeightForWidth());
        checkBox_dont_add_c_constant->setSizePolicy(sizePolicy1);

        gridLayout_27->addWidget(checkBox_dont_add_c_constant, 4, 0, 1, 2);

        gridLayout_27->setColumnStretch(1, 1);

        verticalLayout_56->addLayout(gridLayout_27);


        verticalLayout->addWidget(frame_iterations_formula);

        groupBox_advanced_weight = new QGroupBox(cTabFractal);
        groupBox_advanced_weight->setObjectName(QString::fromUtf8("groupBox_advanced_weight"));
        groupBox_advanced_weight->setCheckable(false);
        gridLayout_advanced_weight = new QGridLayout(groupBox_advanced_weight);
        gridLayout_advanced_weight->setSpacing(3);
        gridLayout_advanced_weight->setObjectName(QString::fromUtf8("gridLayout_advanced_weight"));
        label_weight_mode = new QLabel(groupBox_advanced_weight);
        label_weight_mode->setObjectName(QString::fromUtf8("label_weight_mode"));

        gridLayout_advanced_weight->addWidget(label_weight_mode, 0, 0, 1, 1);

        comboBox_weight_mode = new QComboBox(groupBox_advanced_weight);
        comboBox_weight_mode->addItem(QString());
        comboBox_weight_mode->addItem(QString());
        comboBox_weight_mode->addItem(QString());
        comboBox_weight_mode->addItem(QString());
        comboBox_weight_mode->addItem(QString());
        comboBox_weight_mode->addItem(QString());
        comboBox_weight_mode->addItem(QString());
        comboBox_weight_mode->addItem(QString());
        comboBox_weight_mode->addItem(QString());
        comboBox_weight_mode->addItem(QString());
        comboBox_weight_mode->setObjectName(QString::fromUtf8("comboBox_weight_mode"));

        gridLayout_advanced_weight->addWidget(comboBox_weight_mode, 0, 1, 1, 1);

        label_weight_static = new QLabel(groupBox_advanced_weight);
        label_weight_static->setObjectName(QString::fromUtf8("label_weight_static"));

        gridLayout_advanced_weight->addWidget(label_weight_static, 1, 0, 1, 1);

        spinbox_weight_static = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_static->setObjectName(QString::fromUtf8("spinbox_weight_static"));
        spinbox_weight_static->setDecimals(4);
        spinbox_weight_static->setMaximum(1.000000000000000);
        spinbox_weight_static->setSingleStep(0.010000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_static, 1, 1, 1, 1);

        label_weight_iter_start = new QLabel(groupBox_advanced_weight);
        label_weight_iter_start->setObjectName(QString::fromUtf8("label_weight_iter_start"));

        gridLayout_advanced_weight->addWidget(label_weight_iter_start, 2, 0, 1, 1);

        spinboxInt_weight_iter_start = new MySpinBox(groupBox_advanced_weight);
        spinboxInt_weight_iter_start->setObjectName(QString::fromUtf8("spinboxInt_weight_iter_start"));
        spinboxInt_weight_iter_start->setMaximum(65536);

        gridLayout_advanced_weight->addWidget(spinboxInt_weight_iter_start, 2, 1, 1, 1);

        label_weight_iter_end = new QLabel(groupBox_advanced_weight);
        label_weight_iter_end->setObjectName(QString::fromUtf8("label_weight_iter_end"));

        gridLayout_advanced_weight->addWidget(label_weight_iter_end, 3, 0, 1, 1);

        spinboxInt_weight_iter_end = new MySpinBox(groupBox_advanced_weight);
        spinboxInt_weight_iter_end->setObjectName(QString::fromUtf8("spinboxInt_weight_iter_end"));
        spinboxInt_weight_iter_end->setMaximum(65536);

        gridLayout_advanced_weight->addWidget(spinboxInt_weight_iter_end, 3, 1, 1, 1);

        label_weight_start = new QLabel(groupBox_advanced_weight);
        label_weight_start->setObjectName(QString::fromUtf8("label_weight_start"));

        gridLayout_advanced_weight->addWidget(label_weight_start, 4, 0, 1, 1);

        spinbox_weight_start = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_start->setObjectName(QString::fromUtf8("spinbox_weight_start"));
        spinbox_weight_start->setDecimals(4);
        spinbox_weight_start->setMaximum(1.000000000000000);
        spinbox_weight_start->setSingleStep(0.010000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_start, 4, 1, 1, 1);

        label_weight_end = new QLabel(groupBox_advanced_weight);
        label_weight_end->setObjectName(QString::fromUtf8("label_weight_end"));

        gridLayout_advanced_weight->addWidget(label_weight_end, 5, 0, 1, 1);

        spinbox_weight_end = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_end->setObjectName(QString::fromUtf8("spinbox_weight_end"));
        spinbox_weight_end->setDecimals(4);
        spinbox_weight_end->setMaximum(1.000000000000000);
        spinbox_weight_end->setSingleStep(0.010000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_end, 5, 1, 1, 1);

        label_weight_blend_mode = new QLabel(groupBox_advanced_weight);
        label_weight_blend_mode->setObjectName(QString::fromUtf8("label_weight_blend_mode"));

        gridLayout_advanced_weight->addWidget(label_weight_blend_mode, 6, 0, 1, 1);

        comboBox_weight_blend_mode = new QComboBox(groupBox_advanced_weight);
        comboBox_weight_blend_mode->addItem(QString());
        comboBox_weight_blend_mode->addItem(QString());
        comboBox_weight_blend_mode->addItem(QString());
        comboBox_weight_blend_mode->addItem(QString());
        comboBox_weight_blend_mode->addItem(QString());
        comboBox_weight_blend_mode->addItem(QString());
        comboBox_weight_blend_mode->addItem(QString());
        comboBox_weight_blend_mode->setObjectName(QString::fromUtf8("comboBox_weight_blend_mode"));

        gridLayout_advanced_weight->addWidget(comboBox_weight_blend_mode, 6, 1, 1, 1);

        label_weight_de_base = new QLabel(groupBox_advanced_weight);
        label_weight_de_base->setObjectName(QString::fromUtf8("label_weight_de_base"));

        gridLayout_advanced_weight->addWidget(label_weight_de_base, 7, 0, 1, 1);

        spinbox_weight_de_base = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_de_base->setObjectName(QString::fromUtf8("spinbox_weight_de_base"));
        spinbox_weight_de_base->setDecimals(4);
        spinbox_weight_de_base->setMaximum(1.000000000000000);
        spinbox_weight_de_base->setSingleStep(0.010000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_de_base, 7, 1, 1, 1);

        label_weight_de_sensitivity = new QLabel(groupBox_advanced_weight);
        label_weight_de_sensitivity->setObjectName(QString::fromUtf8("label_weight_de_sensitivity"));

        gridLayout_advanced_weight->addWidget(label_weight_de_sensitivity, 8, 0, 1, 1);

        spinbox_weight_de_sensitivity = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_de_sensitivity->setObjectName(QString::fromUtf8("spinbox_weight_de_sensitivity"));
        spinbox_weight_de_sensitivity->setDecimals(4);
        spinbox_weight_de_sensitivity->setMaximum(100.000000000000000);
        spinbox_weight_de_sensitivity->setSingleStep(0.100000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_de_sensitivity, 8, 1, 1, 1);

        label_weight_de_threshold = new QLabel(groupBox_advanced_weight);
        label_weight_de_threshold->setObjectName(QString::fromUtf8("label_weight_de_threshold"));

        gridLayout_advanced_weight->addWidget(label_weight_de_threshold, 9, 0, 1, 1);

        spinbox_weight_de_threshold = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_de_threshold->setObjectName(QString::fromUtf8("spinbox_weight_de_threshold"));
        spinbox_weight_de_threshold->setDecimals(4);
        spinbox_weight_de_threshold->setMaximum(1000.000000000000000);
        spinbox_weight_de_threshold->setSingleStep(0.010000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_de_threshold, 9, 1, 1, 1);

        label_weight_de_mod_type = new QLabel(groupBox_advanced_weight);
        label_weight_de_mod_type->setObjectName(QString::fromUtf8("label_weight_de_mod_type"));

        gridLayout_advanced_weight->addWidget(label_weight_de_mod_type, 10, 0, 1, 1);

        comboBox_weight_de_mod_type = new QComboBox(groupBox_advanced_weight);
        comboBox_weight_de_mod_type->addItem(QString());
        comboBox_weight_de_mod_type->addItem(QString());
        comboBox_weight_de_mod_type->addItem(QString());
        comboBox_weight_de_mod_type->addItem(QString());
        comboBox_weight_de_mod_type->addItem(QString());
        comboBox_weight_de_mod_type->setObjectName(QString::fromUtf8("comboBox_weight_de_mod_type"));

        gridLayout_advanced_weight->addWidget(comboBox_weight_de_mod_type, 10, 1, 1, 1);

        label_weight_zlength_base = new QLabel(groupBox_advanced_weight);
        label_weight_zlength_base->setObjectName(QString::fromUtf8("label_weight_zlength_base"));

        gridLayout_advanced_weight->addWidget(label_weight_zlength_base, 11, 0, 1, 1);

        spinbox_weight_zlength_base = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_zlength_base->setObjectName(QString::fromUtf8("spinbox_weight_zlength_base"));
        spinbox_weight_zlength_base->setDecimals(4);
        spinbox_weight_zlength_base->setMaximum(1.000000000000000);
        spinbox_weight_zlength_base->setSingleStep(0.010000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_zlength_base, 11, 1, 1, 1);

        label_weight_zlength_sens = new QLabel(groupBox_advanced_weight);
        label_weight_zlength_sens->setObjectName(QString::fromUtf8("label_weight_zlength_sens"));

        gridLayout_advanced_weight->addWidget(label_weight_zlength_sens, 12, 0, 1, 1);

        spinbox_weight_zlength_sens = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_zlength_sens->setObjectName(QString::fromUtf8("spinbox_weight_zlength_sens"));
        spinbox_weight_zlength_sens->setDecimals(4);
        spinbox_weight_zlength_sens->setMaximum(100.000000000000000);
        spinbox_weight_zlength_sens->setSingleStep(0.100000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_zlength_sens, 12, 1, 1, 1);

        label_weight_zlength_threshold = new QLabel(groupBox_advanced_weight);
        label_weight_zlength_threshold->setObjectName(QString::fromUtf8("label_weight_zlength_threshold"));

        gridLayout_advanced_weight->addWidget(label_weight_zlength_threshold, 13, 0, 1, 1);

        spinbox_weight_zlength_threshold = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_zlength_threshold->setObjectName(QString::fromUtf8("spinbox_weight_zlength_threshold"));
        spinbox_weight_zlength_threshold->setDecimals(4);
        spinbox_weight_zlength_threshold->setMaximum(1000.000000000000000);
        spinbox_weight_zlength_threshold->setSingleStep(0.100000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_zlength_threshold, 13, 1, 1, 1);

        label_weight_zlength_mod_type = new QLabel(groupBox_advanced_weight);
        label_weight_zlength_mod_type->setObjectName(QString::fromUtf8("label_weight_zlength_mod_type"));

        gridLayout_advanced_weight->addWidget(label_weight_zlength_mod_type, 14, 0, 1, 1);

        comboBox_weight_zlength_mod_type = new QComboBox(groupBox_advanced_weight);
        comboBox_weight_zlength_mod_type->addItem(QString());
        comboBox_weight_zlength_mod_type->addItem(QString());
        comboBox_weight_zlength_mod_type->addItem(QString());
        comboBox_weight_zlength_mod_type->addItem(QString());
        comboBox_weight_zlength_mod_type->addItem(QString());
        comboBox_weight_zlength_mod_type->setObjectName(QString::fromUtf8("comboBox_weight_zlength_mod_type"));

        gridLayout_advanced_weight->addWidget(comboBox_weight_zlength_mod_type, 14, 1, 1, 1);

        label_weight_condition_type = new QLabel(groupBox_advanced_weight);
        label_weight_condition_type->setObjectName(QString::fromUtf8("label_weight_condition_type"));

        gridLayout_advanced_weight->addWidget(label_weight_condition_type, 15, 0, 1, 1);

        comboBox_weight_condition_type = new QComboBox(groupBox_advanced_weight);
        comboBox_weight_condition_type->addItem(QString());
        comboBox_weight_condition_type->addItem(QString());
        comboBox_weight_condition_type->addItem(QString());
        comboBox_weight_condition_type->addItem(QString());
        comboBox_weight_condition_type->setObjectName(QString::fromUtf8("comboBox_weight_condition_type"));

        gridLayout_advanced_weight->addWidget(comboBox_weight_condition_type, 15, 1, 1, 1);

        label_weight_condition_threshold = new QLabel(groupBox_advanced_weight);
        label_weight_condition_threshold->setObjectName(QString::fromUtf8("label_weight_condition_threshold"));

        gridLayout_advanced_weight->addWidget(label_weight_condition_threshold, 16, 0, 1, 1);

        spinbox_weight_condition_threshold = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_condition_threshold->setObjectName(QString::fromUtf8("spinbox_weight_condition_threshold"));
        spinbox_weight_condition_threshold->setDecimals(4);
        spinbox_weight_condition_threshold->setMaximum(1000.000000000000000);
        spinbox_weight_condition_threshold->setSingleStep(0.010000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_condition_threshold, 16, 1, 1, 1);

        label_weight_true = new QLabel(groupBox_advanced_weight);
        label_weight_true->setObjectName(QString::fromUtf8("label_weight_true"));

        gridLayout_advanced_weight->addWidget(label_weight_true, 17, 0, 1, 1);

        spinbox_weight_true = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_true->setObjectName(QString::fromUtf8("spinbox_weight_true"));
        spinbox_weight_true->setDecimals(4);
        spinbox_weight_true->setMaximum(1.000000000000000);
        spinbox_weight_true->setSingleStep(0.010000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_true, 17, 1, 1, 1);

        label_weight_false = new QLabel(groupBox_advanced_weight);
        label_weight_false->setObjectName(QString::fromUtf8("label_weight_false"));

        gridLayout_advanced_weight->addWidget(label_weight_false, 18, 0, 1, 1);

        spinbox_weight_false = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_false->setObjectName(QString::fromUtf8("spinbox_weight_false"));
        spinbox_weight_false->setDecimals(4);
        spinbox_weight_false->setMaximum(1.000000000000000);
        spinbox_weight_false->setSingleStep(0.010000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_false, 18, 1, 1, 1);

        label_weight_condition_blend = new QLabel(groupBox_advanced_weight);
        label_weight_condition_blend->setObjectName(QString::fromUtf8("label_weight_condition_blend"));

        gridLayout_advanced_weight->addWidget(label_weight_condition_blend, 19, 0, 1, 1);

        comboBox_weight_condition_blend = new QComboBox(groupBox_advanced_weight);
        comboBox_weight_condition_blend->addItem(QString());
        comboBox_weight_condition_blend->addItem(QString());
        comboBox_weight_condition_blend->addItem(QString());
        comboBox_weight_condition_blend->setObjectName(QString::fromUtf8("comboBox_weight_condition_blend"));

        gridLayout_advanced_weight->addWidget(comboBox_weight_condition_blend, 19, 1, 1, 1);

        label_weight_orbit_trap_base = new QLabel(groupBox_advanced_weight);
        label_weight_orbit_trap_base->setObjectName(QString::fromUtf8("label_weight_orbit_trap_base"));

        gridLayout_advanced_weight->addWidget(label_weight_orbit_trap_base, 20, 0, 1, 1);

        spinbox_weight_orbit_trap_base = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_orbit_trap_base->setObjectName(QString::fromUtf8("spinbox_weight_orbit_trap_base"));
        spinbox_weight_orbit_trap_base->setDecimals(4);
        spinbox_weight_orbit_trap_base->setMaximum(1.000000000000000);
        spinbox_weight_orbit_trap_base->setSingleStep(0.010000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_orbit_trap_base, 20, 1, 1, 1);

        label_weight_orbit_trap_sensitivity = new QLabel(groupBox_advanced_weight);
        label_weight_orbit_trap_sensitivity->setObjectName(QString::fromUtf8("label_weight_orbit_trap_sensitivity"));

        gridLayout_advanced_weight->addWidget(label_weight_orbit_trap_sensitivity, 21, 0, 1, 1);

        spinbox_weight_orbit_trap_sensitivity = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_orbit_trap_sensitivity->setObjectName(QString::fromUtf8("spinbox_weight_orbit_trap_sensitivity"));
        spinbox_weight_orbit_trap_sensitivity->setDecimals(4);
        spinbox_weight_orbit_trap_sensitivity->setMaximum(100.000000000000000);
        spinbox_weight_orbit_trap_sensitivity->setSingleStep(0.100000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_orbit_trap_sensitivity, 21, 1, 1, 1);

        label_weight_orbit_trap_threshold = new QLabel(groupBox_advanced_weight);
        label_weight_orbit_trap_threshold->setObjectName(QString::fromUtf8("label_weight_orbit_trap_threshold"));

        gridLayout_advanced_weight->addWidget(label_weight_orbit_trap_threshold, 22, 0, 1, 1);

        spinbox_weight_orbit_trap_threshold = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_orbit_trap_threshold->setObjectName(QString::fromUtf8("spinbox_weight_orbit_trap_threshold"));
        spinbox_weight_orbit_trap_threshold->setDecimals(4);
        spinbox_weight_orbit_trap_threshold->setMaximum(1000.000000000000000);
        spinbox_weight_orbit_trap_threshold->setSingleStep(0.100000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_orbit_trap_threshold, 22, 1, 1, 1);

        label_weight_orbit_trap_mod_type = new QLabel(groupBox_advanced_weight);
        label_weight_orbit_trap_mod_type->setObjectName(QString::fromUtf8("label_weight_orbit_trap_mod_type"));

        gridLayout_advanced_weight->addWidget(label_weight_orbit_trap_mod_type, 23, 0, 1, 1);

        comboBox_weight_orbit_trap_mod_type = new QComboBox(groupBox_advanced_weight);
        comboBox_weight_orbit_trap_mod_type->addItem(QString());
        comboBox_weight_orbit_trap_mod_type->addItem(QString());
        comboBox_weight_orbit_trap_mod_type->addItem(QString());
        comboBox_weight_orbit_trap_mod_type->addItem(QString());
        comboBox_weight_orbit_trap_mod_type->addItem(QString());
        comboBox_weight_orbit_trap_mod_type->setObjectName(QString::fromUtf8("comboBox_weight_orbit_trap_mod_type"));

        gridLayout_advanced_weight->addWidget(comboBox_weight_orbit_trap_mod_type, 23, 1, 1, 1);

        label_weight_curve_base = new QLabel(groupBox_advanced_weight);
        label_weight_curve_base->setObjectName(QString::fromUtf8("label_weight_curve_base"));

        gridLayout_advanced_weight->addWidget(label_weight_curve_base, 24, 0, 1, 1);

        spinbox_weight_curve_base = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_curve_base->setObjectName(QString::fromUtf8("spinbox_weight_curve_base"));
        spinbox_weight_curve_base->setDecimals(4);
        spinbox_weight_curve_base->setMaximum(1.000000000000000);
        spinbox_weight_curve_base->setSingleStep(0.010000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_curve_base, 24, 1, 1, 1);

        label_weight_curve_sensitivity = new QLabel(groupBox_advanced_weight);
        label_weight_curve_sensitivity->setObjectName(QString::fromUtf8("label_weight_curve_sensitivity"));

        gridLayout_advanced_weight->addWidget(label_weight_curve_sensitivity, 25, 0, 1, 1);

        spinbox_weight_curve_sensitivity = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_curve_sensitivity->setObjectName(QString::fromUtf8("spinbox_weight_curve_sensitivity"));
        spinbox_weight_curve_sensitivity->setDecimals(4);
        spinbox_weight_curve_sensitivity->setMaximum(100.000000000000000);
        spinbox_weight_curve_sensitivity->setSingleStep(0.100000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_curve_sensitivity, 25, 1, 1, 1);

        label_weight_curve_power = new QLabel(groupBox_advanced_weight);
        label_weight_curve_power->setObjectName(QString::fromUtf8("label_weight_curve_power"));

        gridLayout_advanced_weight->addWidget(label_weight_curve_power, 26, 0, 1, 1);

        spinbox_weight_curve_power = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_curve_power->setObjectName(QString::fromUtf8("spinbox_weight_curve_power"));
        spinbox_weight_curve_power->setDecimals(4);
        spinbox_weight_curve_power->setMinimum(0.010000000000000);
        spinbox_weight_curve_power->setMaximum(10.000000000000000);
        spinbox_weight_curve_power->setSingleStep(0.100000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_curve_power, 26, 1, 1, 1);

        label_weight_curve_mod_type = new QLabel(groupBox_advanced_weight);
        label_weight_curve_mod_type->setObjectName(QString::fromUtf8("label_weight_curve_mod_type"));

        gridLayout_advanced_weight->addWidget(label_weight_curve_mod_type, 27, 0, 1, 1);

        comboBox_weight_curve_mod_type = new QComboBox(groupBox_advanced_weight);
        comboBox_weight_curve_mod_type->addItem(QString());
        comboBox_weight_curve_mod_type->addItem(QString());
        comboBox_weight_curve_mod_type->addItem(QString());
        comboBox_weight_curve_mod_type->addItem(QString());
        comboBox_weight_curve_mod_type->addItem(QString());
        comboBox_weight_curve_mod_type->setObjectName(QString::fromUtf8("comboBox_weight_curve_mod_type"));

        gridLayout_advanced_weight->addWidget(comboBox_weight_curve_mod_type, 27, 1, 1, 1);

        label_weight_de_ratio_scale = new QLabel(groupBox_advanced_weight);
        label_weight_de_ratio_scale->setObjectName(QString::fromUtf8("label_weight_de_ratio_scale"));

        gridLayout_advanced_weight->addWidget(label_weight_de_ratio_scale, 28, 0, 1, 1);

        spinbox_weight_de_ratio_scale = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_de_ratio_scale->setObjectName(QString::fromUtf8("spinbox_weight_de_ratio_scale"));
        spinbox_weight_de_ratio_scale->setDecimals(4);
        spinbox_weight_de_ratio_scale->setMinimum(0.010000000000000);
        spinbox_weight_de_ratio_scale->setMaximum(100.000000000000000);
        spinbox_weight_de_ratio_scale->setSingleStep(0.100000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_de_ratio_scale, 28, 1, 1, 1);

        label_weight_de_ratio_offset = new QLabel(groupBox_advanced_weight);
        label_weight_de_ratio_offset->setObjectName(QString::fromUtf8("label_weight_de_ratio_offset"));

        gridLayout_advanced_weight->addWidget(label_weight_de_ratio_offset, 29, 0, 1, 1);

        spinbox_weight_de_ratio_offset = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_de_ratio_offset->setObjectName(QString::fromUtf8("spinbox_weight_de_ratio_offset"));
        spinbox_weight_de_ratio_offset->setDecimals(6);
        spinbox_weight_de_ratio_offset->setMinimum(0.000000000001000);
        spinbox_weight_de_ratio_offset->setMaximum(1000.000000000000000);
        spinbox_weight_de_ratio_offset->setSingleStep(0.100000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_de_ratio_offset, 29, 1, 1, 1);

        label_weight_de_ratio_mod_type = new QLabel(groupBox_advanced_weight);
        label_weight_de_ratio_mod_type->setObjectName(QString::fromUtf8("label_weight_de_ratio_mod_type"));

        gridLayout_advanced_weight->addWidget(label_weight_de_ratio_mod_type, 30, 0, 1, 1);

        comboBox_weight_de_ratio_mod_type = new QComboBox(groupBox_advanced_weight);
        comboBox_weight_de_ratio_mod_type->addItem(QString());
        comboBox_weight_de_ratio_mod_type->addItem(QString());
        comboBox_weight_de_ratio_mod_type->addItem(QString());
        comboBox_weight_de_ratio_mod_type->addItem(QString());
        comboBox_weight_de_ratio_mod_type->addItem(QString());
        comboBox_weight_de_ratio_mod_type->setObjectName(QString::fromUtf8("comboBox_weight_de_ratio_mod_type"));

        gridLayout_advanced_weight->addWidget(comboBox_weight_de_ratio_mod_type, 30, 1, 1, 1);

        label_weight_adaptive_strength = new QLabel(groupBox_advanced_weight);
        label_weight_adaptive_strength->setObjectName(QString::fromUtf8("label_weight_adaptive_strength"));

        gridLayout_advanced_weight->addWidget(label_weight_adaptive_strength, 31, 0, 1, 1);

        spinbox_weight_adaptive_strength = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_adaptive_strength->setObjectName(QString::fromUtf8("spinbox_weight_adaptive_strength"));
        spinbox_weight_adaptive_strength->setDecimals(4);
        spinbox_weight_adaptive_strength->setMinimum(0.010000000000000);
        spinbox_weight_adaptive_strength->setMaximum(10.000000000000000);
        spinbox_weight_adaptive_strength->setSingleStep(0.100000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_adaptive_strength, 31, 1, 1, 1);

        label_weight_floor = new QLabel(groupBox_advanced_weight);
        label_weight_floor->setObjectName(QString::fromUtf8("label_weight_floor"));

        gridLayout_advanced_weight->addWidget(label_weight_floor, 32, 0, 1, 1);

        spinbox_weight_floor = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_floor->setObjectName(QString::fromUtf8("spinbox_weight_floor"));
        spinbox_weight_floor->setDecimals(4);
        spinbox_weight_floor->setMaximum(1.000000000000000);
        spinbox_weight_floor->setSingleStep(0.010000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_floor, 32, 1, 1, 1);

        label_weight_ceiling = new QLabel(groupBox_advanced_weight);
        label_weight_ceiling->setObjectName(QString::fromUtf8("label_weight_ceiling"));

        gridLayout_advanced_weight->addWidget(label_weight_ceiling, 33, 0, 1, 1);

        spinbox_weight_ceiling = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_ceiling->setObjectName(QString::fromUtf8("spinbox_weight_ceiling"));
        spinbox_weight_ceiling->setDecimals(4);
        spinbox_weight_ceiling->setMaximum(1.000000000000000);
        spinbox_weight_ceiling->setSingleStep(0.010000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_ceiling, 33, 1, 1, 1);

        label_weight_gamma = new QLabel(groupBox_advanced_weight);
        label_weight_gamma->setObjectName(QString::fromUtf8("label_weight_gamma"));

        gridLayout_advanced_weight->addWidget(label_weight_gamma, 34, 0, 1, 1);

        spinbox_weight_gamma = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_gamma->setObjectName(QString::fromUtf8("spinbox_weight_gamma"));
        spinbox_weight_gamma->setDecimals(4);
        spinbox_weight_gamma->setMinimum(0.010000000000000);
        spinbox_weight_gamma->setMaximum(10.000000000000000);
        spinbox_weight_gamma->setSingleStep(0.100000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_gamma, 34, 1, 1, 1);

        checkBox_weight_invert = new MyCheckBox(groupBox_advanced_weight);
        checkBox_weight_invert->setObjectName(QString::fromUtf8("checkBox_weight_invert"));

        gridLayout_advanced_weight->addWidget(checkBox_weight_invert, 35, 0, 1, 2);

        label_weight_fade_in = new QLabel(groupBox_advanced_weight);
        label_weight_fade_in->setObjectName(QString::fromUtf8("label_weight_fade_in"));

        gridLayout_advanced_weight->addWidget(label_weight_fade_in, 36, 0, 1, 1);

        spinboxInt_weight_fade_in = new MySpinBox(groupBox_advanced_weight);
        spinboxInt_weight_fade_in->setObjectName(QString::fromUtf8("spinboxInt_weight_fade_in"));
        spinboxInt_weight_fade_in->setMaximum(1000);

        gridLayout_advanced_weight->addWidget(spinboxInt_weight_fade_in, 36, 1, 1, 1);

        label_weight_fade_out = new QLabel(groupBox_advanced_weight);
        label_weight_fade_out->setObjectName(QString::fromUtf8("label_weight_fade_out"));

        gridLayout_advanced_weight->addWidget(label_weight_fade_out, 37, 0, 1, 1);

        spinboxInt_weight_fade_out = new MySpinBox(groupBox_advanced_weight);
        spinboxInt_weight_fade_out->setObjectName(QString::fromUtf8("spinboxInt_weight_fade_out"));
        spinboxInt_weight_fade_out->setMaximum(1000);

        gridLayout_advanced_weight->addWidget(spinboxInt_weight_fade_out, 37, 1, 1, 1);

        label_weight_de_smooth_radius = new QLabel(groupBox_advanced_weight);
        label_weight_de_smooth_radius->setObjectName(QString::fromUtf8("label_weight_de_smooth_radius"));

        gridLayout_advanced_weight->addWidget(label_weight_de_smooth_radius, 38, 0, 1, 1);

        spinbox_weight_de_smooth_radius = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_de_smooth_radius->setObjectName(QString::fromUtf8("spinbox_weight_de_smooth_radius"));
        spinbox_weight_de_smooth_radius->setDecimals(6);
        spinbox_weight_de_smooth_radius->setMaximum(100.000000000000000);
        spinbox_weight_de_smooth_radius->setSingleStep(0.010000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_de_smooth_radius, 38, 1, 1, 1);

        label_weight_component_blend_curve = new QLabel(groupBox_advanced_weight);
        label_weight_component_blend_curve->setObjectName(QString::fromUtf8("label_weight_component_blend_curve"));

        gridLayout_advanced_weight->addWidget(label_weight_component_blend_curve, 39, 0, 1, 1);

        spinbox_weight_component_blend_curve = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_component_blend_curve->setObjectName(QString::fromUtf8("spinbox_weight_component_blend_curve"));
        spinbox_weight_component_blend_curve->setDecimals(4);
        spinbox_weight_component_blend_curve->setMinimum(0.100000000000000);
        spinbox_weight_component_blend_curve->setMaximum(10.000000000000000);
        spinbox_weight_component_blend_curve->setSingleStep(0.100000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_component_blend_curve, 39, 1, 1, 1);

        checkBox_weight_separate_components = new MyCheckBox(groupBox_advanced_weight);
        checkBox_weight_separate_components->setObjectName(QString::fromUtf8("checkBox_weight_separate_components"));

        gridLayout_advanced_weight->addWidget(checkBox_weight_separate_components, 40, 0, 1, 2);

        label_weight_z_vector = new QLabel(groupBox_advanced_weight);
        label_weight_z_vector->setObjectName(QString::fromUtf8("label_weight_z_vector"));

        gridLayout_advanced_weight->addWidget(label_weight_z_vector, 41, 0, 1, 1);

        spinbox_weight_z_vector = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_z_vector->setObjectName(QString::fromUtf8("spinbox_weight_z_vector"));
        spinbox_weight_z_vector->setDecimals(4);
        spinbox_weight_z_vector->setMaximum(1.000000000000000);
        spinbox_weight_z_vector->setSingleStep(0.010000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_z_vector, 41, 1, 1, 1);

        label_weight_de_component = new QLabel(groupBox_advanced_weight);
        label_weight_de_component->setObjectName(QString::fromUtf8("label_weight_de_component"));

        gridLayout_advanced_weight->addWidget(label_weight_de_component, 42, 0, 1, 1);

        spinbox_weight_de_component = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_de_component->setObjectName(QString::fromUtf8("spinbox_weight_de_component"));
        spinbox_weight_de_component->setDecimals(4);
        spinbox_weight_de_component->setMaximum(1.000000000000000);
        spinbox_weight_de_component->setSingleStep(0.010000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_de_component, 42, 1, 1, 1);

        label_weight_dist_component = new QLabel(groupBox_advanced_weight);
        label_weight_dist_component->setObjectName(QString::fromUtf8("label_weight_dist_component"));

        gridLayout_advanced_weight->addWidget(label_weight_dist_component, 43, 0, 1, 1);

        spinbox_weight_dist_component = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_dist_component->setObjectName(QString::fromUtf8("spinbox_weight_dist_component"));
        spinbox_weight_dist_component->setDecimals(4);
        spinbox_weight_dist_component->setMaximum(1.000000000000000);
        spinbox_weight_dist_component->setSingleStep(0.010000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_dist_component, 43, 1, 1, 1);

        label_weight_color_component = new QLabel(groupBox_advanced_weight);
        label_weight_color_component->setObjectName(QString::fromUtf8("label_weight_color_component"));

        gridLayout_advanced_weight->addWidget(label_weight_color_component, 44, 0, 1, 1);

        spinbox_weight_color_component = new MyDoubleSpinBox(groupBox_advanced_weight);
        spinbox_weight_color_component->setObjectName(QString::fromUtf8("spinbox_weight_color_component"));
        spinbox_weight_color_component->setDecimals(4);
        spinbox_weight_color_component->setMaximum(1.000000000000000);
        spinbox_weight_color_component->setSingleStep(0.010000000000000);

        gridLayout_advanced_weight->addWidget(spinbox_weight_color_component, 44, 1, 1, 1);


        verticalLayout->addWidget(groupBox_advanced_weight);

        groupBox_formula_parameters = new QGroupBox(cTabFractal);
        groupBox_formula_parameters->setObjectName(QString::fromUtf8("groupBox_formula_parameters"));
        verticalLayout_77 = new QVBoxLayout(groupBox_formula_parameters);
        verticalLayout_77->setSpacing(2);
        verticalLayout_77->setObjectName(QString::fromUtf8("verticalLayout_77"));
        verticalLayout_77->setContentsMargins(2, 2, 2, 2);
        pushButton_local_randomize = new cButtonRandomSettingsFromWidget(groupBox_formula_parameters);
        pushButton_local_randomize->setObjectName(QString::fromUtf8("pushButton_local_randomize"));
        sizePolicy.setHeightForWidth(pushButton_local_randomize->sizePolicy().hasHeightForWidth());
        pushButton_local_randomize->setSizePolicy(sizePolicy);

        verticalLayout_77->addWidget(pushButton_local_randomize);

        verticalLayout_fractal = new QVBoxLayout();
        verticalLayout_fractal->setSpacing(2);
        verticalLayout_fractal->setObjectName(QString::fromUtf8("verticalLayout_fractal"));

        verticalLayout_77->addLayout(verticalLayout_fractal);


        verticalLayout->addWidget(groupBox_formula_parameters);

        groupBox_calculation_parameters = new QGroupBox(cTabFractal);
        groupBox_calculation_parameters->setObjectName(QString::fromUtf8("groupBox_calculation_parameters"));
        verticalLayout_2 = new QVBoxLayout(groupBox_calculation_parameters);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(2, 2, 2, 2);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        spinboxInt_formula_maxiter = new MySpinBox(groupBox_calculation_parameters);
        spinboxInt_formula_maxiter->setObjectName(QString::fromUtf8("spinboxInt_formula_maxiter"));
        sizePolicy1.setHeightForWidth(spinboxInt_formula_maxiter->sizePolicy().hasHeightForWidth());
        spinboxInt_formula_maxiter->setSizePolicy(sizePolicy1);
        spinboxInt_formula_maxiter->setMinimum(1);
        spinboxInt_formula_maxiter->setMaximum(500);

        gridLayout->addWidget(spinboxInt_formula_maxiter, 0, 1, 1, 1);

        label_305 = new QLabel(groupBox_calculation_parameters);
        label_305->setObjectName(QString::fromUtf8("label_305"));
        label_305->setWordWrap(true);

        gridLayout->addWidget(label_305, 0, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        groupCheck_smooth_de_combine_enable = new MyGroupBox(groupBox_calculation_parameters);
        groupCheck_smooth_de_combine_enable->setObjectName(QString::fromUtf8("groupCheck_smooth_de_combine_enable"));
        groupCheck_smooth_de_combine_enable->setCheckable(true);
        gridLayout_4 = new QGridLayout(groupCheck_smooth_de_combine_enable);
        gridLayout_4->setSpacing(2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(2, 2, 2, 2);
        label_306 = new QLabel(groupCheck_smooth_de_combine_enable);
        label_306->setObjectName(QString::fromUtf8("label_306"));
        label_306->setWordWrap(true);

        gridLayout_4->addWidget(label_306, 0, 0, 1, 1);

        logedit_smooth_de_combine_distance = new MyLineEdit(groupCheck_smooth_de_combine_enable);
        logedit_smooth_de_combine_distance->setObjectName(QString::fromUtf8("logedit_smooth_de_combine_distance"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(logedit_smooth_de_combine_distance->sizePolicy().hasHeightForWidth());
        logedit_smooth_de_combine_distance->setSizePolicy(sizePolicy3);

        gridLayout_4->addWidget(logedit_smooth_de_combine_distance, 0, 1, 1, 1);


        verticalLayout_2->addWidget(groupCheck_smooth_de_combine_enable);


        verticalLayout->addWidget(groupBox_calculation_parameters);

        groupBox_c_constant_addition = new QGroupBox(cTabFractal);
        groupBox_c_constant_addition->setObjectName(QString::fromUtf8("groupBox_c_constant_addition"));
        verticalLayout_120 = new QVBoxLayout(groupBox_c_constant_addition);
        verticalLayout_120->setObjectName(QString::fromUtf8("verticalLayout_120"));
        verticalLayout_120->setContentsMargins(2, 2, 2, 2);
        groupCheck_julia_mode = new MyGroupBox(groupBox_c_constant_addition);
        groupCheck_julia_mode->setObjectName(QString::fromUtf8("groupCheck_julia_mode"));
        groupCheck_julia_mode->setCheckable(true);
        verticalLayout_121 = new QVBoxLayout(groupCheck_julia_mode);
        verticalLayout_121->setSpacing(2);
        verticalLayout_121->setObjectName(QString::fromUtf8("verticalLayout_121"));
        verticalLayout_121->setContentsMargins(2, 2, 2, 2);
        gridLayout_75 = new QGridLayout();
        gridLayout_75->setSpacing(2);
        gridLayout_75->setObjectName(QString::fromUtf8("gridLayout_75"));
        label_300 = new QLabel(groupCheck_julia_mode);
        label_300->setObjectName(QString::fromUtf8("label_300"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_300->sizePolicy().hasHeightForWidth());
        label_300->setSizePolicy(sizePolicy4);
        label_300->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_75->addWidget(label_300, 1, 1, 1, 1);

        label_301 = new QLabel(groupCheck_julia_mode);
        label_301->setObjectName(QString::fromUtf8("label_301"));

        gridLayout_75->addWidget(label_301, 0, 0, 1, 1);

        vect3_julia_c_y = new MyLineEdit(groupCheck_julia_mode);
        vect3_julia_c_y->setObjectName(QString::fromUtf8("vect3_julia_c_y"));
        sizePolicy3.setHeightForWidth(vect3_julia_c_y->sizePolicy().hasHeightForWidth());
        vect3_julia_c_y->setSizePolicy(sizePolicy3);

        gridLayout_75->addWidget(vect3_julia_c_y, 1, 2, 1, 1);

        vect3_julia_c_x = new MyLineEdit(groupCheck_julia_mode);
        vect3_julia_c_x->setObjectName(QString::fromUtf8("vect3_julia_c_x"));
        sizePolicy3.setHeightForWidth(vect3_julia_c_x->sizePolicy().hasHeightForWidth());
        vect3_julia_c_x->setSizePolicy(sizePolicy3);

        gridLayout_75->addWidget(vect3_julia_c_x, 0, 2, 1, 1);

        label_302 = new QLabel(groupCheck_julia_mode);
        label_302->setObjectName(QString::fromUtf8("label_302"));
        sizePolicy4.setHeightForWidth(label_302->sizePolicy().hasHeightForWidth());
        label_302->setSizePolicy(sizePolicy4);
        label_302->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_75->addWidget(label_302, 2, 1, 1, 1);

        label_303 = new QLabel(groupCheck_julia_mode);
        label_303->setObjectName(QString::fromUtf8("label_303"));
        sizePolicy4.setHeightForWidth(label_303->sizePolicy().hasHeightForWidth());
        label_303->setSizePolicy(sizePolicy4);
        label_303->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_75->addWidget(label_303, 0, 1, 1, 1);

        vect3_julia_c_z = new MyLineEdit(groupCheck_julia_mode);
        vect3_julia_c_z->setObjectName(QString::fromUtf8("vect3_julia_c_z"));
        sizePolicy3.setHeightForWidth(vect3_julia_c_z->sizePolicy().hasHeightForWidth());
        vect3_julia_c_z->setSizePolicy(sizePolicy3);

        gridLayout_75->addWidget(vect3_julia_c_z, 2, 2, 1, 1);


        verticalLayout_121->addLayout(gridLayout_75);


        verticalLayout_120->addWidget(groupCheck_julia_mode);

        gridLayout_76 = new QGridLayout();
        gridLayout_76->setSpacing(2);
        gridLayout_76->setObjectName(QString::fromUtf8("gridLayout_76"));
        gridLayout_76->setContentsMargins(0, 0, -1, -1);
        label_352 = new QLabel(groupBox_c_constant_addition);
        label_352->setObjectName(QString::fromUtf8("label_352"));
        sizePolicy4.setHeightForWidth(label_352->sizePolicy().hasHeightForWidth());
        label_352->setSizePolicy(sizePolicy4);
        label_352->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_76->addWidget(label_352, 2, 1, 1, 1);

        spinbox3_fractal_constant_factor_x = new MyDoubleSpinBox(groupBox_c_constant_addition);
        spinbox3_fractal_constant_factor_x->setObjectName(QString::fromUtf8("spinbox3_fractal_constant_factor_x"));
        sizePolicy1.setHeightForWidth(spinbox3_fractal_constant_factor_x->sizePolicy().hasHeightForWidth());
        spinbox3_fractal_constant_factor_x->setSizePolicy(sizePolicy1);
        spinbox3_fractal_constant_factor_x->setDecimals(6);
        spinbox3_fractal_constant_factor_x->setMinimum(-1000.000000000000000);
        spinbox3_fractal_constant_factor_x->setMaximum(1000.000000000000000);
        spinbox3_fractal_constant_factor_x->setSingleStep(0.100000000000000);

        gridLayout_76->addWidget(spinbox3_fractal_constant_factor_x, 1, 2, 1, 1);

        spinbox3_fractal_constant_factor_y = new MyDoubleSpinBox(groupBox_c_constant_addition);
        spinbox3_fractal_constant_factor_y->setObjectName(QString::fromUtf8("spinbox3_fractal_constant_factor_y"));
        sizePolicy1.setHeightForWidth(spinbox3_fractal_constant_factor_y->sizePolicy().hasHeightForWidth());
        spinbox3_fractal_constant_factor_y->setSizePolicy(sizePolicy1);
        spinbox3_fractal_constant_factor_y->setDecimals(6);
        spinbox3_fractal_constant_factor_y->setMinimum(-1000.000000000000000);
        spinbox3_fractal_constant_factor_y->setMaximum(1000.000000000000000);
        spinbox3_fractal_constant_factor_y->setSingleStep(0.100000000000000);

        gridLayout_76->addWidget(spinbox3_fractal_constant_factor_y, 2, 2, 1, 1);

        spinbox3_fractal_constant_factor_z = new MyDoubleSpinBox(groupBox_c_constant_addition);
        spinbox3_fractal_constant_factor_z->setObjectName(QString::fromUtf8("spinbox3_fractal_constant_factor_z"));
        sizePolicy1.setHeightForWidth(spinbox3_fractal_constant_factor_z->sizePolicy().hasHeightForWidth());
        spinbox3_fractal_constant_factor_z->setSizePolicy(sizePolicy1);
        spinbox3_fractal_constant_factor_z->setDecimals(6);
        spinbox3_fractal_constant_factor_z->setMinimum(-1000.000000000000000);
        spinbox3_fractal_constant_factor_z->setMaximum(1000.000000000000000);
        spinbox3_fractal_constant_factor_z->setSingleStep(0.100000000000000);

        gridLayout_76->addWidget(spinbox3_fractal_constant_factor_z, 3, 2, 1, 1);

        label_304 = new QLabel(groupBox_c_constant_addition);
        label_304->setObjectName(QString::fromUtf8("label_304"));

        gridLayout_76->addWidget(label_304, 1, 0, 3, 1);

        label_351 = new QLabel(groupBox_c_constant_addition);
        label_351->setObjectName(QString::fromUtf8("label_351"));
        sizePolicy4.setHeightForWidth(label_351->sizePolicy().hasHeightForWidth());
        label_351->setSizePolicy(sizePolicy4);
        label_351->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_76->addWidget(label_351, 1, 1, 1, 1);

        label_353 = new QLabel(groupBox_c_constant_addition);
        label_353->setObjectName(QString::fromUtf8("label_353"));
        sizePolicy4.setHeightForWidth(label_353->sizePolicy().hasHeightForWidth());
        label_353->setSizePolicy(sizePolicy4);
        label_353->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_76->addWidget(label_353, 3, 1, 1, 1);

        label_295 = new QLabel(groupBox_c_constant_addition);
        label_295->setObjectName(QString::fromUtf8("label_295"));

        gridLayout_76->addWidget(label_295, 0, 0, 1, 1);

        spinbox_initial_waxis = new MyDoubleSpinBox(groupBox_c_constant_addition);
        spinbox_initial_waxis->setObjectName(QString::fromUtf8("spinbox_initial_waxis"));
        sizePolicy1.setHeightForWidth(spinbox_initial_waxis->sizePolicy().hasHeightForWidth());
        spinbox_initial_waxis->setSizePolicy(sizePolicy1);
        spinbox_initial_waxis->setDecimals(6);
        spinbox_initial_waxis->setMinimum(-1000.000000000000000);
        spinbox_initial_waxis->setMaximum(1000.000000000000000);
        spinbox_initial_waxis->setSingleStep(0.100000000000000);

        gridLayout_76->addWidget(spinbox_initial_waxis, 0, 2, 1, 1);

        gridLayout_76->setColumnStretch(2, 1);

        verticalLayout_120->addLayout(gridLayout_76);


        verticalLayout->addWidget(groupBox_c_constant_addition);

        groupBox_material_fractal = new QGroupBox(cTabFractal);
        groupBox_material_fractal->setObjectName(QString::fromUtf8("groupBox_material_fractal"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(groupBox_material_fractal->sizePolicy().hasHeightForWidth());
        groupBox_material_fractal->setSizePolicy(sizePolicy5);
        verticalLayout_63 = new QVBoxLayout(groupBox_material_fractal);
        verticalLayout_63->setSpacing(2);
        verticalLayout_63->setObjectName(QString::fromUtf8("verticalLayout_63"));
        verticalLayout_63->setContentsMargins(2, 2, 2, 2);
        materialselector_formula_material_id = new cMaterialSelector(groupBox_material_fractal);
        materialselector_formula_material_id->setObjectName(QString::fromUtf8("materialselector_formula_material_id"));
        sizePolicy5.setHeightForWidth(materialselector_formula_material_id->sizePolicy().hasHeightForWidth());
        materialselector_formula_material_id->setSizePolicy(sizePolicy5);

        verticalLayout_63->addWidget(materialselector_formula_material_id);


        verticalLayout->addWidget(groupBox_material_fractal);

        groupBox_formula_transform = new QGroupBox(cTabFractal);
        groupBox_formula_transform->setObjectName(QString::fromUtf8("groupBox_formula_transform"));
        verticalLayout_22 = new QVBoxLayout(groupBox_formula_transform);
        verticalLayout_22->setSpacing(2);
        verticalLayout_22->setObjectName(QString::fromUtf8("verticalLayout_22"));
        verticalLayout_22->setContentsMargins(2, 2, 2, 2);
        gridLayout_41 = new QGridLayout();
        gridLayout_41->setSpacing(2);
        gridLayout_41->setObjectName(QString::fromUtf8("gridLayout_41"));
        label_158 = new QLabel(groupBox_formula_transform);
        label_158->setObjectName(QString::fromUtf8("label_158"));
        sizePolicy4.setHeightForWidth(label_158->sizePolicy().hasHeightForWidth());
        label_158->setSizePolicy(sizePolicy4);
        label_158->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_41->addWidget(label_158, 2, 1, 1, 1);

        vect3_formula_position_z = new MyLineEdit(groupBox_formula_transform);
        vect3_formula_position_z->setObjectName(QString::fromUtf8("vect3_formula_position_z"));
        sizePolicy3.setHeightForWidth(vect3_formula_position_z->sizePolicy().hasHeightForWidth());
        vect3_formula_position_z->setSizePolicy(sizePolicy3);

        gridLayout_41->addWidget(vect3_formula_position_z, 2, 2, 1, 1);

        label_163 = new QLabel(groupBox_formula_transform);
        label_163->setObjectName(QString::fromUtf8("label_163"));

        gridLayout_41->addWidget(label_163, 0, 0, 3, 1);

        label_157 = new QLabel(groupBox_formula_transform);
        label_157->setObjectName(QString::fromUtf8("label_157"));

        gridLayout_41->addWidget(label_157, 5, 0, 1, 1);

        label_159 = new QLabel(groupBox_formula_transform);
        label_159->setObjectName(QString::fromUtf8("label_159"));
        sizePolicy4.setHeightForWidth(label_159->sizePolicy().hasHeightForWidth());
        label_159->setSizePolicy(sizePolicy4);
        label_159->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_41->addWidget(label_159, 0, 1, 1, 1);

        vect3_formula_position_y = new MyLineEdit(groupBox_formula_transform);
        vect3_formula_position_y->setObjectName(QString::fromUtf8("vect3_formula_position_y"));
        sizePolicy3.setHeightForWidth(vect3_formula_position_y->sizePolicy().hasHeightForWidth());
        vect3_formula_position_y->setSizePolicy(sizePolicy3);

        gridLayout_41->addWidget(vect3_formula_position_y, 1, 2, 1, 1);

        spinboxd3_formula_rotation_z = new MyDoubleSpinBox(groupBox_formula_transform);
        spinboxd3_formula_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_formula_rotation_z"));
        sizePolicy1.setHeightForWidth(spinboxd3_formula_rotation_z->sizePolicy().hasHeightForWidth());
        spinboxd3_formula_rotation_z->setSizePolicy(sizePolicy1);
        spinboxd3_formula_rotation_z->setDecimals(2);
        spinboxd3_formula_rotation_z->setMinimum(-36000.000000000000000);
        spinboxd3_formula_rotation_z->setMaximum(36000.000000000000000);
        spinboxd3_formula_rotation_z->setSingleStep(0.100000000000000);

        gridLayout_41->addWidget(spinboxd3_formula_rotation_z, 6, 2, 1, 1);

        spinboxd3_formula_rotation_y = new MyDoubleSpinBox(groupBox_formula_transform);
        spinboxd3_formula_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_formula_rotation_y"));
        sizePolicy1.setHeightForWidth(spinboxd3_formula_rotation_y->sizePolicy().hasHeightForWidth());
        spinboxd3_formula_rotation_y->setSizePolicy(sizePolicy1);
        spinboxd3_formula_rotation_y->setDecimals(2);
        spinboxd3_formula_rotation_y->setMinimum(-36000.000000000000000);
        spinboxd3_formula_rotation_y->setMaximum(36000.000000000000000);
        spinboxd3_formula_rotation_y->setSingleStep(0.100000000000000);

        gridLayout_41->addWidget(spinboxd3_formula_rotation_y, 5, 2, 1, 1);

        label_167 = new QLabel(groupBox_formula_transform);
        label_167->setObjectName(QString::fromUtf8("label_167"));
        sizePolicy4.setHeightForWidth(label_167->sizePolicy().hasHeightForWidth());
        label_167->setSizePolicy(sizePolicy4);
        label_167->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_41->addWidget(label_167, 8, 1, 1, 1);

        spinboxd3_formula_rotation_x = new MyDoubleSpinBox(groupBox_formula_transform);
        spinboxd3_formula_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_formula_rotation_x"));
        sizePolicy1.setHeightForWidth(spinboxd3_formula_rotation_x->sizePolicy().hasHeightForWidth());
        spinboxd3_formula_rotation_x->setSizePolicy(sizePolicy1);
        spinboxd3_formula_rotation_x->setDecimals(2);
        spinboxd3_formula_rotation_x->setMinimum(-36000.000000000000000);
        spinboxd3_formula_rotation_x->setMaximum(36000.000000000000000);
        spinboxd3_formula_rotation_x->setSingleStep(0.100000000000000);

        gridLayout_41->addWidget(spinboxd3_formula_rotation_x, 4, 2, 1, 1);

        vect3_formula_position_x = new MyLineEdit(groupBox_formula_transform);
        vect3_formula_position_x->setObjectName(QString::fromUtf8("vect3_formula_position_x"));
        sizePolicy3.setHeightForWidth(vect3_formula_position_x->sizePolicy().hasHeightForWidth());
        vect3_formula_position_x->setSizePolicy(sizePolicy3);

        gridLayout_41->addWidget(vect3_formula_position_x, 0, 2, 1, 1);

        vect3_formula_repeat_x = new MyLineEdit(groupBox_formula_transform);
        vect3_formula_repeat_x->setObjectName(QString::fromUtf8("vect3_formula_repeat_x"));
        sizePolicy3.setHeightForWidth(vect3_formula_repeat_x->sizePolicy().hasHeightForWidth());
        vect3_formula_repeat_x->setSizePolicy(sizePolicy3);

        gridLayout_41->addWidget(vect3_formula_repeat_x, 7, 2, 1, 1);

        label_160 = new QLabel(groupBox_formula_transform);
        label_160->setObjectName(QString::fromUtf8("label_160"));

        gridLayout_41->addWidget(label_160, 4, 0, 1, 1);

        label_162 = new QLabel(groupBox_formula_transform);
        label_162->setObjectName(QString::fromUtf8("label_162"));

        gridLayout_41->addWidget(label_162, 6, 0, 1, 1);

        label_161 = new QLabel(groupBox_formula_transform);
        label_161->setObjectName(QString::fromUtf8("label_161"));
        sizePolicy4.setHeightForWidth(label_161->sizePolicy().hasHeightForWidth());
        label_161->setSizePolicy(sizePolicy4);
        label_161->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_41->addWidget(label_161, 1, 1, 1, 1);

        vect3_formula_repeat_y = new MyLineEdit(groupBox_formula_transform);
        vect3_formula_repeat_y->setObjectName(QString::fromUtf8("vect3_formula_repeat_y"));
        sizePolicy3.setHeightForWidth(vect3_formula_repeat_y->sizePolicy().hasHeightForWidth());
        vect3_formula_repeat_y->setSizePolicy(sizePolicy3);

        gridLayout_41->addWidget(vect3_formula_repeat_y, 8, 2, 1, 1);

        label_165 = new QLabel(groupBox_formula_transform);
        label_165->setObjectName(QString::fromUtf8("label_165"));
        sizePolicy4.setHeightForWidth(label_165->sizePolicy().hasHeightForWidth());
        label_165->setSizePolicy(sizePolicy4);
        label_165->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_41->addWidget(label_165, 7, 1, 1, 1);

        vect3_formula_repeat_z = new MyLineEdit(groupBox_formula_transform);
        vect3_formula_repeat_z->setObjectName(QString::fromUtf8("vect3_formula_repeat_z"));
        sizePolicy3.setHeightForWidth(vect3_formula_repeat_z->sizePolicy().hasHeightForWidth());
        vect3_formula_repeat_z->setSizePolicy(sizePolicy3);

        gridLayout_41->addWidget(vect3_formula_repeat_z, 9, 2, 1, 1);

        label_166 = new QLabel(groupBox_formula_transform);
        label_166->setObjectName(QString::fromUtf8("label_166"));
        sizePolicy4.setHeightForWidth(label_166->sizePolicy().hasHeightForWidth());
        label_166->setSizePolicy(sizePolicy4);
        label_166->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_41->addWidget(label_166, 9, 1, 1, 1);

        label_164 = new QLabel(groupBox_formula_transform);
        label_164->setObjectName(QString::fromUtf8("label_164"));

        gridLayout_41->addWidget(label_164, 7, 0, 3, 1);

        label_168 = new QLabel(groupBox_formula_transform);
        label_168->setObjectName(QString::fromUtf8("label_168"));

        gridLayout_41->addWidget(label_168, 3, 0, 1, 1);

        logedit_formula_scale = new MyLineEdit(groupBox_formula_transform);
        logedit_formula_scale->setObjectName(QString::fromUtf8("logedit_formula_scale"));
        sizePolicy3.setHeightForWidth(logedit_formula_scale->sizePolicy().hasHeightForWidth());
        logedit_formula_scale->setSizePolicy(sizePolicy3);

        gridLayout_41->addWidget(logedit_formula_scale, 3, 2, 1, 1);


        verticalLayout_22->addLayout(gridLayout_41);


        verticalLayout->addWidget(groupBox_formula_transform);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        QWidget::setTabOrder(comboBox_formula, spinboxInt_formula_iterations);
        QWidget::setTabOrder(spinboxInt_formula_iterations, spinbox_formula_weight);
        QWidget::setTabOrder(spinbox_formula_weight, checkBox_dont_add_c_constant);
        QWidget::setTabOrder(checkBox_dont_add_c_constant, checkBox_check_for_bailout);
        QWidget::setTabOrder(checkBox_check_for_bailout, groupCheck_julia_mode);
        QWidget::setTabOrder(groupCheck_julia_mode, vect3_julia_c_x);
        QWidget::setTabOrder(vect3_julia_c_x, vect3_julia_c_y);
        QWidget::setTabOrder(vect3_julia_c_y, vect3_julia_c_z);
        QWidget::setTabOrder(vect3_julia_c_z, spinbox_initial_waxis);
        QWidget::setTabOrder(spinbox_initial_waxis, spinbox3_fractal_constant_factor_x);
        QWidget::setTabOrder(spinbox3_fractal_constant_factor_x, spinbox3_fractal_constant_factor_y);
        QWidget::setTabOrder(spinbox3_fractal_constant_factor_y, spinbox3_fractal_constant_factor_z);
        QWidget::setTabOrder(spinbox3_fractal_constant_factor_z, vect3_formula_position_x);
        QWidget::setTabOrder(vect3_formula_position_x, vect3_formula_position_y);
        QWidget::setTabOrder(vect3_formula_position_y, vect3_formula_position_z);
        QWidget::setTabOrder(vect3_formula_position_z, logedit_formula_scale);
        QWidget::setTabOrder(logedit_formula_scale, spinboxd3_formula_rotation_x);
        QWidget::setTabOrder(spinboxd3_formula_rotation_x, spinboxd3_formula_rotation_y);
        QWidget::setTabOrder(spinboxd3_formula_rotation_y, spinboxd3_formula_rotation_z);
        QWidget::setTabOrder(spinboxd3_formula_rotation_z, vect3_formula_repeat_x);
        QWidget::setTabOrder(vect3_formula_repeat_x, vect3_formula_repeat_y);
        QWidget::setTabOrder(vect3_formula_repeat_y, vect3_formula_repeat_z);

        retranslateUi(cTabFractal);

        QMetaObject::connectSlotsByName(cTabFractal);
    } // setupUi

    void retranslateUi(QWidget *cTabFractal)
    {
        cTabFractal->setWindowTitle(QCoreApplication::translate("cTabFractal", "Form", nullptr));
        pushButton_local_randomize_2->setText(QCoreApplication::translate("cTabFractal", "Randomize", nullptr));
        pushButton_local_load->setText(QCoreApplication::translate("cTabFractal", "Load", nullptr));
        pushButton_local_save->setText(QCoreApplication::translate("cTabFractal", "Save", nullptr));
        pushButton_local_reset->setText(QCoreApplication::translate("cTabFractal", "Reset", nullptr));
        pushButton_local_navi->setText(QCoreApplication::translate("cTabFractal", "Navi", nullptr));
        pushButton_reset_formula->setText(QCoreApplication::translate("cTabFractal", "Reset formula parameters", nullptr));
#if QT_CONFIG(tooltip)
        spinboxInt_formula_start_iteration->setToolTip(QCoreApplication::translate("cTabFractal", "<html><head/><body><p>This fractal formula will be used when iteration number will be not less than 'Start at iteration'</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_formula_start_iteration->setText(QCoreApplication::translate("cTabFractal", "Start at iteration :", nullptr));
        label_formula_weight->setText(QCoreApplication::translate("cTabFractal", "Weight:", nullptr));
#if QT_CONFIG(tooltip)
        comboBox_formula->setToolTip(QCoreApplication::translate("cTabFractal", "<html><head/><body><p>Selection for fractal formula. Fractal formula defines shape of fractal.</p><p>Algorithm (code) for selected formula is visible in Information box.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinbox_formula_weight->setToolTip(QCoreApplication::translate("cTabFractal", "<html><head/><body><p>Weight of result of fractal formula. If weight is zero then result is ignored. If result is 1 then is fully taken.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_formula_weight->setPrefix(QString());
        spinbox_formula_weight->setSuffix(QString());
#if QT_CONFIG(tooltip)
        spinboxInt_formula_iterations->setToolTip(QCoreApplication::translate("cTabFractal", "<html><head/><body><p>Number of iterations to calculate for this formula</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_formula_iterations->setText(QCoreApplication::translate("cTabFractal", "Iterations:", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_check_for_bailout->setToolTip(QCoreApplication::translate("cTabFractal", "<html><head/><body><p>Enables checking of bailout condition for this fractal formula. </p><p>Bailout condition is checked at the end of each iteration. If the length of the iteration vector is longer than the value defined by 'bailout' parameter,  then the  iterating  stops.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_check_for_bailout->setText(QCoreApplication::translate("cTabFractal", "Check for bailout condition", nullptr));
        label_formula_stop_iteration->setText(QCoreApplication::translate("cTabFractal", "Stop at Iteration:", nullptr));
#if QT_CONFIG(tooltip)
        spinboxInt_formula_stop_iteration->setToolTip(QCoreApplication::translate("cTabFractal", "<html><head/><body><p>This fractal formula will be used when iteration number will be not higher than 'Stop at iteration'</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBox_dont_add_c_constant->setToolTip(QCoreApplication::translate("cTabFractal", "<html><head/><body><p>Disables adding Cpixel  constant to the result of fractal iteration (e.g. z<span style=\" vertical-align:sub;\">n+1</span> = z<span style=\" vertical-align:sub;\">n</span><span style=\" vertical-align:super;\">2</span> + C)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_dont_add_c_constant->setText(QCoreApplication::translate("cTabFractal", "Don't add C constant", nullptr));
        groupBox_advanced_weight->setTitle(QCoreApplication::translate("cTabFractal", "Advanced Weight System", nullptr));
        label_weight_mode->setText(QCoreApplication::translate("cTabFractal", "Weight Mode:", nullptr));
        comboBox_weight_mode->setItemText(0, QCoreApplication::translate("cTabFractal", "Static", nullptr));
        comboBox_weight_mode->setItemText(1, QCoreApplication::translate("cTabFractal", "Iteration", nullptr));
        comboBox_weight_mode->setItemText(2, QCoreApplication::translate("cTabFractal", "DE", nullptr));
        comboBox_weight_mode->setItemText(3, QCoreApplication::translate("cTabFractal", "ZLength", nullptr));
        comboBox_weight_mode->setItemText(4, QCoreApplication::translate("cTabFractal", "Conditional", nullptr));
        comboBox_weight_mode->setItemText(5, QCoreApplication::translate("cTabFractal", "OrbitTrap", nullptr));
        comboBox_weight_mode->setItemText(6, QCoreApplication::translate("cTabFractal", "Curve", nullptr));
        comboBox_weight_mode->setItemText(7, QCoreApplication::translate("cTabFractal", "Transform Passthrough", nullptr));
        comboBox_weight_mode->setItemText(8, QCoreApplication::translate("cTabFractal", "DE Ratio", nullptr));
        comboBox_weight_mode->setItemText(9, QCoreApplication::translate("cTabFractal", "Adaptive", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_weight_mode->setToolTip(QCoreApplication::translate("cTabFractal", "Weight calculation mode for this formula in hybrid rendering.\n"
"                                                                                       Static: Fixed weight (simple). Iteration: Weight changes over iterations (morphing). DE: Weight modulated by distance estimation (detail-aware). ZLength: Weight modulated by orbit magnitude (spatial). Conditional: Binary weight based on threshold (sharp transitions). OrbitTrap: Weight based on orbit trap distance (artistic). Curve: Custom power curve for weight (non-linear).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_weight_static->setText(QCoreApplication::translate("cTabFractal", "Static Weight:", nullptr));
        label_weight_iter_start->setText(QCoreApplication::translate("cTabFractal", "Iter Start:", nullptr));
        label_weight_iter_end->setText(QCoreApplication::translate("cTabFractal", "Iter End:", nullptr));
        label_weight_start->setText(QCoreApplication::translate("cTabFractal", "Start Weight:", nullptr));
        label_weight_end->setText(QCoreApplication::translate("cTabFractal", "End Weight:", nullptr));
        label_weight_blend_mode->setText(QCoreApplication::translate("cTabFractal", "Blend Mode:", nullptr));
        comboBox_weight_blend_mode->setItemText(0, QCoreApplication::translate("cTabFractal", "Linear", nullptr));
        comboBox_weight_blend_mode->setItemText(1, QCoreApplication::translate("cTabFractal", "Smooth", nullptr));
        comboBox_weight_blend_mode->setItemText(2, QCoreApplication::translate("cTabFractal", "Step", nullptr));
        comboBox_weight_blend_mode->setItemText(3, QCoreApplication::translate("cTabFractal", "Multiply", nullptr));
        comboBox_weight_blend_mode->setItemText(4, QCoreApplication::translate("cTabFractal", "Power", nullptr));
        comboBox_weight_blend_mode->setItemText(5, QCoreApplication::translate("cTabFractal", "Min", nullptr));
        comboBox_weight_blend_mode->setItemText(6, QCoreApplication::translate("cTabFractal", "Max", nullptr));

        label_weight_de_base->setText(QCoreApplication::translate("cTabFractal", "DE Base Weight:", nullptr));
        label_weight_de_sensitivity->setText(QCoreApplication::translate("cTabFractal", "DE Sensitivity:", nullptr));
        label_weight_de_threshold->setText(QCoreApplication::translate("cTabFractal", "DE Threshold:", nullptr));
        label_weight_de_mod_type->setText(QCoreApplication::translate("cTabFractal", "DE Mod Type:", nullptr));
        comboBox_weight_de_mod_type->setItemText(0, QCoreApplication::translate("cTabFractal", "Linear", nullptr));
        comboBox_weight_de_mod_type->setItemText(1, QCoreApplication::translate("cTabFractal", "Smooth", nullptr));
        comboBox_weight_de_mod_type->setItemText(2, QCoreApplication::translate("cTabFractal", "Exponential", nullptr));
        comboBox_weight_de_mod_type->setItemText(3, QCoreApplication::translate("cTabFractal", "Inverse", nullptr));
        comboBox_weight_de_mod_type->setItemText(4, QCoreApplication::translate("cTabFractal", "Sigmoid", nullptr));

        label_weight_zlength_base->setText(QCoreApplication::translate("cTabFractal", "Z-Length Base:", nullptr));
        label_weight_zlength_sens->setText(QCoreApplication::translate("cTabFractal", "Z-Length Sens:", nullptr));
        label_weight_zlength_threshold->setText(QCoreApplication::translate("cTabFractal", "Z-Length Threshold:", nullptr));
        label_weight_zlength_mod_type->setText(QCoreApplication::translate("cTabFractal", "Z-Length Mod Type:", nullptr));
        comboBox_weight_zlength_mod_type->setItemText(0, QCoreApplication::translate("cTabFractal", "Linear", nullptr));
        comboBox_weight_zlength_mod_type->setItemText(1, QCoreApplication::translate("cTabFractal", "Smooth", nullptr));
        comboBox_weight_zlength_mod_type->setItemText(2, QCoreApplication::translate("cTabFractal", "Exponential", nullptr));
        comboBox_weight_zlength_mod_type->setItemText(3, QCoreApplication::translate("cTabFractal", "Inverse", nullptr));
        comboBox_weight_zlength_mod_type->setItemText(4, QCoreApplication::translate("cTabFractal", "Sigmoid", nullptr));

        label_weight_condition_type->setText(QCoreApplication::translate("cTabFractal", "Condition Type:", nullptr));
        comboBox_weight_condition_type->setItemText(0, QCoreApplication::translate("cTabFractal", "DE Threshold", nullptr));
        comboBox_weight_condition_type->setItemText(1, QCoreApplication::translate("cTabFractal", "ZLength", nullptr));
        comboBox_weight_condition_type->setItemText(2, QCoreApplication::translate("cTabFractal", "Dist (DIFS)", nullptr));
        comboBox_weight_condition_type->setItemText(3, QCoreApplication::translate("cTabFractal", "Iteration", nullptr));

        label_weight_condition_threshold->setText(QCoreApplication::translate("cTabFractal", "Condition Threshold:", nullptr));
        label_weight_true->setText(QCoreApplication::translate("cTabFractal", "True Weight:", nullptr));
        label_weight_false->setText(QCoreApplication::translate("cTabFractal", "False Weight:", nullptr));
        label_weight_condition_blend->setText(QCoreApplication::translate("cTabFractal", "Condition Blend:", nullptr));
        comboBox_weight_condition_blend->setItemText(0, QCoreApplication::translate("cTabFractal", "Step", nullptr));
        comboBox_weight_condition_blend->setItemText(1, QCoreApplication::translate("cTabFractal", "Linear", nullptr));
        comboBox_weight_condition_blend->setItemText(2, QCoreApplication::translate("cTabFractal", "Smooth", nullptr));

        label_weight_orbit_trap_base->setText(QCoreApplication::translate("cTabFractal", "Orbit Trap Base:", nullptr));
        label_weight_orbit_trap_sensitivity->setText(QCoreApplication::translate("cTabFractal", "Orbit Trap Sens:", nullptr));
        label_weight_orbit_trap_threshold->setText(QCoreApplication::translate("cTabFractal", "Orbit Trap Threshold:", nullptr));
        label_weight_orbit_trap_mod_type->setText(QCoreApplication::translate("cTabFractal", "Orbit Trap Mod Type:", nullptr));
        comboBox_weight_orbit_trap_mod_type->setItemText(0, QCoreApplication::translate("cTabFractal", "Linear", nullptr));
        comboBox_weight_orbit_trap_mod_type->setItemText(1, QCoreApplication::translate("cTabFractal", "Smooth", nullptr));
        comboBox_weight_orbit_trap_mod_type->setItemText(2, QCoreApplication::translate("cTabFractal", "Exponential", nullptr));
        comboBox_weight_orbit_trap_mod_type->setItemText(3, QCoreApplication::translate("cTabFractal", "Inverse", nullptr));
        comboBox_weight_orbit_trap_mod_type->setItemText(4, QCoreApplication::translate("cTabFractal", "Sigmoid", nullptr));

        label_weight_curve_base->setText(QCoreApplication::translate("cTabFractal", "Curve Base:", nullptr));
        label_weight_curve_sensitivity->setText(QCoreApplication::translate("cTabFractal", "Curve Sensitivity:", nullptr));
        label_weight_curve_power->setText(QCoreApplication::translate("cTabFractal", "Curve Power:", nullptr));
        label_weight_curve_mod_type->setText(QCoreApplication::translate("cTabFractal", "Curve Mod Type:", nullptr));
        comboBox_weight_curve_mod_type->setItemText(0, QCoreApplication::translate("cTabFractal", "Linear", nullptr));
        comboBox_weight_curve_mod_type->setItemText(1, QCoreApplication::translate("cTabFractal", "Smooth", nullptr));
        comboBox_weight_curve_mod_type->setItemText(2, QCoreApplication::translate("cTabFractal", "Exponential", nullptr));
        comboBox_weight_curve_mod_type->setItemText(3, QCoreApplication::translate("cTabFractal", "Inverse", nullptr));
        comboBox_weight_curve_mod_type->setItemText(4, QCoreApplication::translate("cTabFractal", "Sigmoid", nullptr));

        label_weight_de_ratio_scale->setText(QCoreApplication::translate("cTabFractal", "DE Ratio Scale:", nullptr));
        label_weight_de_ratio_offset->setText(QCoreApplication::translate("cTabFractal", "DE Ratio Offset:", nullptr));
        label_weight_de_ratio_mod_type->setText(QCoreApplication::translate("cTabFractal", "DE Ratio Mod:", nullptr));
        comboBox_weight_de_ratio_mod_type->setItemText(0, QCoreApplication::translate("cTabFractal", "Linear", nullptr));
        comboBox_weight_de_ratio_mod_type->setItemText(1, QCoreApplication::translate("cTabFractal", "Smooth", nullptr));
        comboBox_weight_de_ratio_mod_type->setItemText(2, QCoreApplication::translate("cTabFractal", "Exponential", nullptr));
        comboBox_weight_de_ratio_mod_type->setItemText(3, QCoreApplication::translate("cTabFractal", "Inverse", nullptr));
        comboBox_weight_de_ratio_mod_type->setItemText(4, QCoreApplication::translate("cTabFractal", "Sigmoid", nullptr));

        label_weight_adaptive_strength->setText(QCoreApplication::translate("cTabFractal", "Adaptive Strength:", nullptr));
        label_weight_floor->setText(QCoreApplication::translate("cTabFractal", "Weight Floor:", nullptr));
        label_weight_ceiling->setText(QCoreApplication::translate("cTabFractal", "Weight Ceiling:", nullptr));
        label_weight_gamma->setText(QCoreApplication::translate("cTabFractal", "Weight Gamma:", nullptr));
        checkBox_weight_invert->setText(QCoreApplication::translate("cTabFractal", "Invert Weight", nullptr));
        label_weight_fade_in->setText(QCoreApplication::translate("cTabFractal", "Fade-In Iterations:", nullptr));
        label_weight_fade_out->setText(QCoreApplication::translate("cTabFractal", "Fade-Out Iterations:", nullptr));
        label_weight_de_smooth_radius->setText(QCoreApplication::translate("cTabFractal", "DE Smooth Radius:", nullptr));
        label_weight_component_blend_curve->setText(QCoreApplication::translate("cTabFractal", "Blend Curve:", nullptr));
        checkBox_weight_separate_components->setText(QCoreApplication::translate("cTabFractal", "Separate Components", nullptr));
        label_weight_z_vector->setText(QCoreApplication::translate("cTabFractal", "Z-Vector Weight:", nullptr));
        label_weight_de_component->setText(QCoreApplication::translate("cTabFractal", "DE Weight:", nullptr));
        label_weight_dist_component->setText(QCoreApplication::translate("cTabFractal", "Dist Weight (DIFS):", nullptr));
        label_weight_color_component->setText(QCoreApplication::translate("cTabFractal", "Color Weight:", nullptr));
        groupBox_formula_parameters->setTitle(QCoreApplication::translate("cTabFractal", "Formula specific parameters", nullptr));
        pushButton_local_randomize->setText(QCoreApplication::translate("cTabFractal", "Randomize", nullptr));
        groupBox_calculation_parameters->setTitle(QCoreApplication::translate("cTabFractal", "Calculation parameters", nullptr));
#if QT_CONFIG(tooltip)
        spinboxInt_formula_maxiter->setToolTip(QCoreApplication::translate("cTabFractal", "<html><head/><body><p>Number of iterations to calculate for this formula</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_305->setText(QCoreApplication::translate("cTabFractal", "Maximum number of fractal iterations:", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_smooth_de_combine_enable->setToolTip(QCoreApplication::translate("cTabFractal", "<html><head/><body> <p>Enable smooth combination of distance fields when this element is combined with others (Boolean operations).</p> <p>Effect: - Softens/rounds edges at unions, intersections, and subtractions instead of sharp seams. - \342\200\234Smooth distance\342\200\235 sets the blend radius (scene units): smaller values keep crisper edges; larger values produce wider, more rounded transitions.</p> <p>Notes: - Visible mainly where this object/formula meets another one. - The appropriate value depends on scale; start small (e.g., 0.05\342\200\2230.2) and adjust. - Very large values may overly blur details or introduce artifacts.</p> </body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_smooth_de_combine_enable->setTitle(QCoreApplication::translate("cTabFractal", "Smooth DE combine", nullptr));
        label_306->setText(QCoreApplication::translate("cTabFractal", "Smooth distance:", nullptr));
        groupBox_c_constant_addition->setTitle(QCoreApplication::translate("cTabFractal", "C constant addition for this fractal formula", nullptr));
        groupCheck_julia_mode->setTitle(QCoreApplication::translate("cTabFractal", "&Julia mode", nullptr));
        label_300->setText(QCoreApplication::translate("cTabFractal", "y:", nullptr));
        label_301->setText(QCoreApplication::translate("cTabFractal", "Julia constant (c):", nullptr));
        label_302->setText(QCoreApplication::translate("cTabFractal", "z:", nullptr));
        label_303->setText(QCoreApplication::translate("cTabFractal", "x:", nullptr));
        label_352->setText(QCoreApplication::translate("cTabFractal", "y:", nullptr));
        spinbox3_fractal_constant_factor_x->setPrefix(QString());
        spinbox3_fractal_constant_factor_x->setSuffix(QString());
        spinbox3_fractal_constant_factor_y->setPrefix(QString());
        spinbox3_fractal_constant_factor_y->setSuffix(QString());
        spinbox3_fractal_constant_factor_z->setPrefix(QString());
        spinbox3_fractal_constant_factor_z->setSuffix(QString());
        label_304->setText(QCoreApplication::translate("cTabFractal", "Constant multiplier:", nullptr));
        label_351->setText(QCoreApplication::translate("cTabFractal", "x:", nullptr));
        label_353->setText(QCoreApplication::translate("cTabFractal", "z:", nullptr));
        label_295->setText(QCoreApplication::translate("cTabFractal", "Initial w-axis value\n"
"                                                                                                                                                                                                                                                                                                                                                                                                for 4D fractals", nullptr));
        spinbox_initial_waxis->setPrefix(QString());
        spinbox_initial_waxis->setSuffix(QString());
        groupBox_material_fractal->setTitle(QCoreApplication::translate("cTabFractal", "Material for fractal", nullptr));
        groupBox_formula_transform->setTitle(QCoreApplication::translate("cTabFractal", "Transform (fractal positioning)", nullptr));
        label_158->setText(QCoreApplication::translate("cTabFractal", "z:", nullptr));
        label_163->setText(QCoreApplication::translate("cTabFractal", "shift:", nullptr));
        label_157->setText(QCoreApplication::translate("cTabFractal", "Y-axis rotation:", nullptr));
        label_159->setText(QCoreApplication::translate("cTabFractal", "x:", nullptr));
        spinboxd3_formula_rotation_z->setPrefix(QString());
        spinboxd3_formula_rotation_z->setSuffix(QString());
        spinboxd3_formula_rotation_y->setPrefix(QString());
        spinboxd3_formula_rotation_y->setSuffix(QString());
        label_167->setText(QCoreApplication::translate("cTabFractal", "y:", nullptr));
        spinboxd3_formula_rotation_x->setPrefix(QString());
        spinboxd3_formula_rotation_x->setSuffix(QString());
        label_160->setText(QCoreApplication::translate("cTabFractal", "X-axis rotation:", nullptr));
        label_162->setText(QCoreApplication::translate("cTabFractal", "Z-axis rotation:", nullptr));
        label_161->setText(QCoreApplication::translate("cTabFractal", "y:", nullptr));
        label_165->setText(QCoreApplication::translate("cTabFractal", "x:", nullptr));
        label_166->setText(QCoreApplication::translate("cTabFractal", "z:", nullptr));
        label_164->setText(QCoreApplication::translate("cTabFractal", "Repeat", nullptr));
        label_168->setText(QCoreApplication::translate("cTabFractal", "scale:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cTabFractal: public Ui_cTabFractal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAB_FRACTAL_H
