/********************************************************************************
** Form generated from reading UI file 'fractal_common_tab.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRACTAL_COMMON_TAB_H
#define UI_FRACTAL_COMMON_TAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "buton_load_settings_from_widget.h"
#include "buton_random_settings_from_widget.h"
#include "buton_reset_settings_from_widget.h"
#include "buton_save_settings_from_widget.h"
#include "drone_explorer_widget.h"
#include "julia_heatmap_widget.h"
#include "material_selector.h"
#include "my_double_spin_box.h"
#include "my_group_box.h"
#include "my_line_edit.h"
#include "thumbnail_widget.h"

QT_BEGIN_NAMESPACE

class Ui_cFractalCommonTab
{
public:
    QVBoxLayout *verticalLayout_47;
    QHBoxLayout *horizontalLayout_5;
    cButtonLoadSettingsFromWidget *pushButton_local_load_5;
    cButtonSaveSettingsFromWidget *pushButton_local_save_5;
    cButtonResetSettingsFromWidget *pushButton_local_reset_5;
    cButtonRandomSettingsFromWidget *pushButton_local_randomize_2;
    QSpacerItem *horizontalSpacer_3;
    QScrollArea *scrollArea_11;
    QWidget *scrollAreaWidgetContents_12;
    QVBoxLayout *verticalLayout_68;
    QGroupBox *groupBox_material_fractal;
    QVBoxLayout *verticalLayout_29;
    cMaterialSelector *materialselector_formula_material_id;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_36;
    MyLineEdit *vect3_fractal_position_z;
    QLabel *label_139;
    QLabel *label_140;
    MyLineEdit *vect3_fractal_position_y;
    QLabel *label_46;
    MyLineEdit *vect3_fractal_position_x;
    QLabel *label_138;
    QLabel *label_137;
    MyDoubleSpinBox *spinboxd3_fractal_rotation_x;
    MyDoubleSpinBox *spinboxd3_fractal_rotation_y;
    MyDoubleSpinBox *spinboxd3_fractal_rotation_z;
    QLabel *label_48;
    QLabel *label_47;
    MyLineEdit *vect3_repeat_x;
    MyLineEdit *vect3_repeat_y;
    MyLineEdit *vect3_repeat_z;
    QLabel *label_repeat_x_2;
    QLabel *label_repeat_y_2;
    QLabel *label_repeat_z_2;
    QLabel *label_145;
    QGroupBox *groupBox_iter_ranges;
    QGridLayout *gridLayout_iter_ranges;
    QLabel *label;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    QLabel *label5;
    MyDoubleSpinBox *spinboxd3_formula_position_iter_start_x;
    MyDoubleSpinBox *spinboxd3_formula_position_iter_stop_x;
    QLabel *label6;
    MyDoubleSpinBox *spinboxd3_formula_position_iter_start_y;
    MyDoubleSpinBox *spinboxd3_formula_position_iter_stop_y;
    QLabel *label7;
    MyDoubleSpinBox *spinboxd3_formula_position_iter_start_z;
    MyDoubleSpinBox *spinboxd3_formula_position_iter_stop_z;
    QLabel *label8;
    QLabel *label9;
    MyDoubleSpinBox *spinboxd3_formula_rotation_iter_start_x;
    MyDoubleSpinBox *spinboxd3_formula_rotation_iter_stop_x;
    QLabel *label10;
    MyDoubleSpinBox *spinboxd3_formula_rotation_iter_start_y;
    MyDoubleSpinBox *spinboxd3_formula_rotation_iter_stop_y;
    QLabel *label11;
    MyDoubleSpinBox *spinboxd3_formula_rotation_iter_start_z;
    MyDoubleSpinBox *spinboxd3_formula_rotation_iter_stop_z;
    QLabel *label12;
    QLabel *label13;
    MyDoubleSpinBox *spinboxd3_formula_repeat_iter_start_x;
    MyDoubleSpinBox *spinboxd3_formula_repeat_iter_stop_x;
    QLabel *label14;
    MyDoubleSpinBox *spinboxd3_formula_repeat_iter_start_y;
    MyDoubleSpinBox *spinboxd3_formula_repeat_iter_stop_y;
    QLabel *label15;
    MyDoubleSpinBox *spinboxd3_formula_repeat_iter_start_z;
    MyDoubleSpinBox *spinboxd3_formula_repeat_iter_stop_z;
    MyGroupBox *groupCheck_julia_mode;
    QVBoxLayout *verticalLayout_48;
    QGridLayout *gridLayout_22;
    QLabel *label_116;
    QLabel *label_113;
    MyLineEdit *vect3_julia_c_y;
    MyLineEdit *vect3_julia_c_x;
    QLabel *label_120;
    QLabel *label_115;
    MyLineEdit *vect3_julia_c_z;
    QPushButton *pushButton_get_julia_constant;
    QGroupBox *groupBox_julia_fine_tune;
    QGridLayout *gridLayout_julia_fine_tune;
    QLabel *label16;
    QLabel *label17;
    QLabel *label18;
    QLabel *label19;
    MyDoubleSpinBox *spinbox3_julia_c_iter_start_x;
    MyDoubleSpinBox *spinbox3_julia_c_iter_stop_x;
    MyDoubleSpinBox *spinbox3_julia_c_weight_x;
    QLabel *label20;
    MyDoubleSpinBox *spinbox3_julia_c_iter_start_y;
    MyDoubleSpinBox *spinbox3_julia_c_iter_stop_y;
    MyDoubleSpinBox *spinbox3_julia_c_weight_y;
    QLabel *label21;
    MyDoubleSpinBox *spinbox3_julia_c_iter_start_z;
    MyDoubleSpinBox *spinbox3_julia_c_iter_stop_z;
    MyDoubleSpinBox *spinbox3_julia_c_weight_z;
    QFrame *line;
    QLabel *label22;
    MyDoubleSpinBox *spinbox3_const_c_iter_start_x;
    MyDoubleSpinBox *spinbox3_const_c_iter_stop_x;
    MyDoubleSpinBox *spinbox3_const_c_weight_x;
    QLabel *label23;
    MyDoubleSpinBox *spinbox3_const_c_iter_start_y;
    MyDoubleSpinBox *spinbox3_const_c_iter_stop_y;
    MyDoubleSpinBox *spinbox3_const_c_weight_y;
    QLabel *label24;
    MyDoubleSpinBox *spinbox3_const_c_iter_start_z;
    MyDoubleSpinBox *spinbox3_const_c_iter_stop_z;
    MyDoubleSpinBox *spinbox3_const_c_weight_z;
    QGroupBox *groupBox_julia_explorer;
    QVBoxLayout *layout_julia_explorer;
    QGridLayout *gridLayout_julia_sliders;
    QLabel *label_julia_slider_cx;
    QSlider *jslider_julia_cx;
    QLabel *label_julia_cx_value;
    QLabel *label_julia_slider_cy;
    QSlider *jslider_julia_cy;
    QLabel *label_julia_cy_value;
    QLabel *label_julia_slider_cz;
    QSlider *jslider_julia_cz;
    QLabel *label_julia_cz_value;
    QLabel *label_julia_range;
    QComboBox *comboBox_julia_range;
    QHBoxLayout *layout_julia_actions;
    QPushButton *pushButton_julia_copy;
    QPushButton *pushButton_julia_paste;
    QPushButton *pushButton_julia_random;
    QPushButton *pushButton_julia_zero;
    QGroupBox *groupBox_julia_presets;
    QGridLayout *gridLayout_julia_presets;
    QPushButton *pushButton_julia_preset_1;
    QPushButton *pushButton_julia_preset_2;
    QPushButton *pushButton_julia_preset_3;
    QPushButton *pushButton_julia_preset_4;
    QPushButton *pushButton_julia_preset_5;
    QPushButton *pushButton_julia_preset_6;
    QPushButton *pushButton_julia_preset_7;
    QPushButton *pushButton_julia_preset_8;
    QPushButton *pushButton_julia_preset_9;
    QGroupBox *groupBox_julia_sweep;
    QVBoxLayout *layout_julia_sweep;
    QHBoxLayout *layout_sweep_axis;
    QLabel *label_sweep_axis;
    QComboBox *comboBox_julia_sweep_axis;
    QHBoxLayout *layout_sweep_range;
    QLabel *label_sweep_from;
    QDoubleSpinBox *spinBox_julia_sweep_from;
    QLabel *label_sweep_to;
    QDoubleSpinBox *spinBox_julia_sweep_to;
    QHBoxLayout *layout_sweep_controls;
    QPushButton *pushButton_julia_sweep_start;
    QPushButton *pushButton_julia_sweep_stop;
    QSpinBox *spinBox_julia_sweep_steps;
    QProgressBar *progressBar_julia_sweep;
    QGroupBox *groupBox_julia_history;
    QVBoxLayout *layout_julia_history;
    QListWidget *listWidget_julia_history;
    QHBoxLayout *layout_julia_history_buttons;
    QPushButton *pushButton_julia_history_save;
    QPushButton *pushButton_julia_history_clear;
    QGroupBox *groupBox_julia_heatmap;
    QVBoxLayout *layout_julia_heatmap;
    QHBoxLayout *layout_heatmap_controls;
    QLabel *label_heatmap_h;
    QComboBox *comboBox_heatmap_axis_h;
    QLabel *label_heatmap_v;
    QComboBox *comboBox_heatmap_axis_v;
    QLabel *label_heatmap_res;
    QComboBox *comboBox_heatmap_resolution;
    QHBoxLayout *layout_heatmap_scheme;
    QLabel *label_heatmap_scheme;
    QComboBox *comboBox_heatmap_scheme;
    QSpacerItem *heatmap_spacer_1;
    cJuliaHeatmapWidget *widget_julia_heatmap;
    QHBoxLayout *layout_heatmap_scan;
    QPushButton *pushButton_heatmap_scan;
    QPushButton *pushButton_heatmap_stop;
    QPushButton *pushButton_heatmap_clear;
    QProgressBar *progressBar_heatmap;
    QLabel *label_heatmap_info;
    QGroupBox *groupBox_drone_explorer;
    QVBoxLayout *layout_drone_explorer;
    QHBoxLayout *layout_drone_controls;
    QLabel *label_drone_strategy;
    QComboBox *comboBox_drone_strategy;
    QLabel *label_drone_speed;
    QSlider *jslider_drone_speed;
    cDroneExplorerWidget *widget_drone_explorer;
    QHBoxLayout *layout_drone_fleet;
    QPushButton *pushButton_drone_launch;
    QPushButton *pushButton_drone_stop;
    QPushButton *pushButton_drone_reset;
    QLabel *label_drone_status;
    MyGroupBox *groupBox_julia_preview;
    QVBoxLayout *verticalLayout_6;
    QGridLayout *gridLayout_7;
    MyLineEdit *logedit_julia_preview_distance;
    QLabel *label_133;
    cThumbnailWidget *previewwidget_julia;
    QGroupBox *groupBox_beauty_finder;
    QVBoxLayout *layout_beauty_finder;
    QHBoxLayout *layout_beauty_range;
    QLabel *label_beauty_range;
    QDoubleSpinBox *spinBox_beauty_range;
    QPushButton *pushButton_beauty_find;
    QPushButton *pushButton_beauty_next;
    QHBoxLayout *layout_beauty_iter;
    QLabel *label25;
    QSpinBox *spinBox_beauty_iter_start;
    QLabel *label26;
    QSpinBox *spinBox_beauty_iter_stop;
    QCheckBox *checkBox_beauty_auto;
    QHBoxLayout *layout_beauty_weight;
    QLabel *label27;
    QLabel *label28;
    QDoubleSpinBox *spinBox_beauty_weight_x;
    QLabel *label29;
    QDoubleSpinBox *spinBox_beauty_weight_y;
    QLabel *label30;
    QDoubleSpinBox *spinBox_beauty_weight_z;
    QProgressBar *progressBar_beauty;
    QLabel *label_beauty_result;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout_3;
    MyDoubleSpinBox *spinbox3_fractal_constant_factor_y;
    QLabel *label_347;
    QLabel *label_346;
    QLabel *label_172;
    QLabel *label_135;
    MyDoubleSpinBox *spinbox3_fractal_constant_factor_x;
    QLabel *label_348;
    MyDoubleSpinBox *spinbox3_fractal_constant_factor_z;
    MyDoubleSpinBox *spinbox_initial_waxis;
    QSpacerItem *verticalSpacer_7;

    void setupUi(QWidget *cFractalCommonTab)
    {
        if (cFractalCommonTab->objectName().isEmpty())
            cFractalCommonTab->setObjectName(QString::fromUtf8("cFractalCommonTab"));
        verticalLayout_47 = new QVBoxLayout(cFractalCommonTab);
        verticalLayout_47->setSpacing(2);
        verticalLayout_47->setObjectName(QString::fromUtf8("verticalLayout_47"));
        verticalLayout_47->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        pushButton_local_load_5 = new cButtonLoadSettingsFromWidget(cFractalCommonTab);
        pushButton_local_load_5->setObjectName(QString::fromUtf8("pushButton_local_load_5"));

        horizontalLayout_5->addWidget(pushButton_local_load_5);

        pushButton_local_save_5 = new cButtonSaveSettingsFromWidget(cFractalCommonTab);
        pushButton_local_save_5->setObjectName(QString::fromUtf8("pushButton_local_save_5"));

        horizontalLayout_5->addWidget(pushButton_local_save_5);

        pushButton_local_reset_5 = new cButtonResetSettingsFromWidget(cFractalCommonTab);
        pushButton_local_reset_5->setObjectName(QString::fromUtf8("pushButton_local_reset_5"));

        horizontalLayout_5->addWidget(pushButton_local_reset_5);

        pushButton_local_randomize_2 = new cButtonRandomSettingsFromWidget(cFractalCommonTab);
        pushButton_local_randomize_2->setObjectName(QString::fromUtf8("pushButton_local_randomize_2"));

        horizontalLayout_5->addWidget(pushButton_local_randomize_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        verticalLayout_47->addLayout(horizontalLayout_5);

        scrollArea_11 = new QScrollArea(cFractalCommonTab);
        scrollArea_11->setObjectName(QString::fromUtf8("scrollArea_11"));
        scrollArea_11->setWidgetResizable(true);
        scrollAreaWidgetContents_12 = new QWidget();
        scrollAreaWidgetContents_12->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_12"));
        scrollAreaWidgetContents_12->setGeometry(QRect(0, 0, 438, 1076));
        verticalLayout_68 = new QVBoxLayout(scrollAreaWidgetContents_12);
        verticalLayout_68->setSpacing(2);
        verticalLayout_68->setObjectName(QString::fromUtf8("verticalLayout_68"));
        verticalLayout_68->setContentsMargins(2, 2, 2, 2);
        groupBox_material_fractal = new QGroupBox(scrollAreaWidgetContents_12);
        groupBox_material_fractal->setObjectName(QString::fromUtf8("groupBox_material_fractal"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_material_fractal->sizePolicy().hasHeightForWidth());
        groupBox_material_fractal->setSizePolicy(sizePolicy);
        verticalLayout_29 = new QVBoxLayout(groupBox_material_fractal);
        verticalLayout_29->setSpacing(2);
        verticalLayout_29->setObjectName(QString::fromUtf8("verticalLayout_29"));
        verticalLayout_29->setContentsMargins(2, 2, 2, 2);
        materialselector_formula_material_id = new cMaterialSelector(groupBox_material_fractal);
        materialselector_formula_material_id->setObjectName(QString::fromUtf8("materialselector_formula_material_id"));
        sizePolicy.setHeightForWidth(materialselector_formula_material_id->sizePolicy().hasHeightForWidth());
        materialselector_formula_material_id->setSizePolicy(sizePolicy);

        verticalLayout_29->addWidget(materialselector_formula_material_id);


        verticalLayout_68->addWidget(groupBox_material_fractal);

        groupBox = new QGroupBox(scrollAreaWidgetContents_12);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(2, 2, 2, 2);
        gridLayout_36 = new QGridLayout();
        gridLayout_36->setSpacing(2);
        gridLayout_36->setObjectName(QString::fromUtf8("gridLayout_36"));
        vect3_fractal_position_z = new MyLineEdit(groupBox);
        vect3_fractal_position_z->setObjectName(QString::fromUtf8("vect3_fractal_position_z"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(vect3_fractal_position_z->sizePolicy().hasHeightForWidth());
        vect3_fractal_position_z->setSizePolicy(sizePolicy1);

        gridLayout_36->addWidget(vect3_fractal_position_z, 2, 2, 1, 1);

        label_139 = new QLabel(groupBox);
        label_139->setObjectName(QString::fromUtf8("label_139"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_139->sizePolicy().hasHeightForWidth());
        label_139->setSizePolicy(sizePolicy2);
        label_139->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_36->addWidget(label_139, 2, 1, 1, 1);

        label_140 = new QLabel(groupBox);
        label_140->setObjectName(QString::fromUtf8("label_140"));
        sizePolicy2.setHeightForWidth(label_140->sizePolicy().hasHeightForWidth());
        label_140->setSizePolicy(sizePolicy2);
        label_140->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_36->addWidget(label_140, 0, 1, 1, 1);

        vect3_fractal_position_y = new MyLineEdit(groupBox);
        vect3_fractal_position_y->setObjectName(QString::fromUtf8("vect3_fractal_position_y"));
        sizePolicy1.setHeightForWidth(vect3_fractal_position_y->sizePolicy().hasHeightForWidth());
        vect3_fractal_position_y->setSizePolicy(sizePolicy1);

        gridLayout_36->addWidget(vect3_fractal_position_y, 1, 2, 1, 1);

        label_46 = new QLabel(groupBox);
        label_46->setObjectName(QString::fromUtf8("label_46"));

        gridLayout_36->addWidget(label_46, 3, 0, 1, 1);

        vect3_fractal_position_x = new MyLineEdit(groupBox);
        vect3_fractal_position_x->setObjectName(QString::fromUtf8("vect3_fractal_position_x"));
        sizePolicy1.setHeightForWidth(vect3_fractal_position_x->sizePolicy().hasHeightForWidth());
        vect3_fractal_position_x->setSizePolicy(sizePolicy1);

        gridLayout_36->addWidget(vect3_fractal_position_x, 0, 2, 1, 1);

        label_138 = new QLabel(groupBox);
        label_138->setObjectName(QString::fromUtf8("label_138"));

        gridLayout_36->addWidget(label_138, 0, 0, 1, 1);

        label_137 = new QLabel(groupBox);
        label_137->setObjectName(QString::fromUtf8("label_137"));
        sizePolicy2.setHeightForWidth(label_137->sizePolicy().hasHeightForWidth());
        label_137->setSizePolicy(sizePolicy2);
        label_137->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_36->addWidget(label_137, 1, 1, 1, 1);

        spinboxd3_fractal_rotation_x = new MyDoubleSpinBox(groupBox);
        spinboxd3_fractal_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_fractal_rotation_x"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(spinboxd3_fractal_rotation_x->sizePolicy().hasHeightForWidth());
        spinboxd3_fractal_rotation_x->setSizePolicy(sizePolicy3);
        spinboxd3_fractal_rotation_x->setDecimals(2);
        spinboxd3_fractal_rotation_x->setMinimum(-36000.000000000000000);
        spinboxd3_fractal_rotation_x->setMaximum(36000.000000000000000);
        spinboxd3_fractal_rotation_x->setSingleStep(0.100000000000000);

        gridLayout_36->addWidget(spinboxd3_fractal_rotation_x, 3, 2, 1, 1);

        spinboxd3_fractal_rotation_y = new MyDoubleSpinBox(groupBox);
        spinboxd3_fractal_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_fractal_rotation_y"));
        sizePolicy3.setHeightForWidth(spinboxd3_fractal_rotation_y->sizePolicy().hasHeightForWidth());
        spinboxd3_fractal_rotation_y->setSizePolicy(sizePolicy3);
        spinboxd3_fractal_rotation_y->setDecimals(2);
        spinboxd3_fractal_rotation_y->setMinimum(-36000.000000000000000);
        spinboxd3_fractal_rotation_y->setMaximum(36000.000000000000000);
        spinboxd3_fractal_rotation_y->setSingleStep(0.100000000000000);

        gridLayout_36->addWidget(spinboxd3_fractal_rotation_y, 4, 2, 1, 1);

        spinboxd3_fractal_rotation_z = new MyDoubleSpinBox(groupBox);
        spinboxd3_fractal_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_fractal_rotation_z"));
        sizePolicy3.setHeightForWidth(spinboxd3_fractal_rotation_z->sizePolicy().hasHeightForWidth());
        spinboxd3_fractal_rotation_z->setSizePolicy(sizePolicy3);
        spinboxd3_fractal_rotation_z->setDecimals(2);
        spinboxd3_fractal_rotation_z->setMinimum(-36000.000000000000000);
        spinboxd3_fractal_rotation_z->setMaximum(36000.000000000000000);
        spinboxd3_fractal_rotation_z->setSingleStep(0.100000000000000);

        gridLayout_36->addWidget(spinboxd3_fractal_rotation_z, 5, 2, 1, 1);

        label_48 = new QLabel(groupBox);
        label_48->setObjectName(QString::fromUtf8("label_48"));

        gridLayout_36->addWidget(label_48, 5, 0, 1, 1);

        label_47 = new QLabel(groupBox);
        label_47->setObjectName(QString::fromUtf8("label_47"));

        gridLayout_36->addWidget(label_47, 4, 0, 1, 1);

        vect3_repeat_x = new MyLineEdit(groupBox);
        vect3_repeat_x->setObjectName(QString::fromUtf8("vect3_repeat_x"));
        sizePolicy1.setHeightForWidth(vect3_repeat_x->sizePolicy().hasHeightForWidth());
        vect3_repeat_x->setSizePolicy(sizePolicy1);

        gridLayout_36->addWidget(vect3_repeat_x, 6, 2, 1, 1);

        vect3_repeat_y = new MyLineEdit(groupBox);
        vect3_repeat_y->setObjectName(QString::fromUtf8("vect3_repeat_y"));
        sizePolicy1.setHeightForWidth(vect3_repeat_y->sizePolicy().hasHeightForWidth());
        vect3_repeat_y->setSizePolicy(sizePolicy1);

        gridLayout_36->addWidget(vect3_repeat_y, 7, 2, 1, 1);

        vect3_repeat_z = new MyLineEdit(groupBox);
        vect3_repeat_z->setObjectName(QString::fromUtf8("vect3_repeat_z"));
        sizePolicy1.setHeightForWidth(vect3_repeat_z->sizePolicy().hasHeightForWidth());
        vect3_repeat_z->setSizePolicy(sizePolicy1);

        gridLayout_36->addWidget(vect3_repeat_z, 8, 2, 1, 1);

        label_repeat_x_2 = new QLabel(groupBox);
        label_repeat_x_2->setObjectName(QString::fromUtf8("label_repeat_x_2"));
        label_repeat_x_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_36->addWidget(label_repeat_x_2, 6, 1, 1, 1);

        label_repeat_y_2 = new QLabel(groupBox);
        label_repeat_y_2->setObjectName(QString::fromUtf8("label_repeat_y_2"));
        label_repeat_y_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_36->addWidget(label_repeat_y_2, 7, 1, 1, 1);

        label_repeat_z_2 = new QLabel(groupBox);
        label_repeat_z_2->setObjectName(QString::fromUtf8("label_repeat_z_2"));
        label_repeat_z_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_36->addWidget(label_repeat_z_2, 8, 1, 1, 1);

        label_145 = new QLabel(groupBox);
        label_145->setObjectName(QString::fromUtf8("label_145"));

        gridLayout_36->addWidget(label_145, 6, 0, 1, 1);

        groupBox_iter_ranges = new QGroupBox(groupBox);
        groupBox_iter_ranges->setObjectName(QString::fromUtf8("groupBox_iter_ranges"));
        gridLayout_iter_ranges = new QGridLayout(groupBox_iter_ranges);
        gridLayout_iter_ranges->setSpacing(2);
        gridLayout_iter_ranges->setObjectName(QString::fromUtf8("gridLayout_iter_ranges"));
        label = new QLabel(groupBox_iter_ranges);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_iter_ranges->addWidget(label, 0, 0, 1, 1);

        label1 = new QLabel(groupBox_iter_ranges);
        label1->setObjectName(QString::fromUtf8("label1"));

        gridLayout_iter_ranges->addWidget(label1, 0, 1, 1, 1);

        label2 = new QLabel(groupBox_iter_ranges);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setAlignment(Qt::AlignCenter);

        gridLayout_iter_ranges->addWidget(label2, 0, 2, 1, 1);

        label3 = new QLabel(groupBox_iter_ranges);
        label3->setObjectName(QString::fromUtf8("label3"));
        label3->setAlignment(Qt::AlignCenter);

        gridLayout_iter_ranges->addWidget(label3, 0, 3, 1, 1);

        label4 = new QLabel(groupBox_iter_ranges);
        label4->setObjectName(QString::fromUtf8("label4"));

        gridLayout_iter_ranges->addWidget(label4, 1, 0, 1, 1);

        label5 = new QLabel(groupBox_iter_ranges);
        label5->setObjectName(QString::fromUtf8("label5"));
        label5->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_iter_ranges->addWidget(label5, 1, 1, 1, 1);

        spinboxd3_formula_position_iter_start_x = new MyDoubleSpinBox(groupBox_iter_ranges);
        spinboxd3_formula_position_iter_start_x->setObjectName(QString::fromUtf8("spinboxd3_formula_position_iter_start_x"));
        spinboxd3_formula_position_iter_start_x->setMinimum(0.000000000000000);
        spinboxd3_formula_position_iter_start_x->setMaximum(99999.000000000000000);
        spinboxd3_formula_position_iter_start_x->setValue(0.000000000000000);
        spinboxd3_formula_position_iter_start_x->setDecimals(0);

        gridLayout_iter_ranges->addWidget(spinboxd3_formula_position_iter_start_x, 1, 2, 1, 1);

        spinboxd3_formula_position_iter_stop_x = new MyDoubleSpinBox(groupBox_iter_ranges);
        spinboxd3_formula_position_iter_stop_x->setObjectName(QString::fromUtf8("spinboxd3_formula_position_iter_stop_x"));
        spinboxd3_formula_position_iter_stop_x->setMinimum(0.000000000000000);
        spinboxd3_formula_position_iter_stop_x->setMaximum(99999.000000000000000);
        spinboxd3_formula_position_iter_stop_x->setValue(250.000000000000000);
        spinboxd3_formula_position_iter_stop_x->setDecimals(0);

        gridLayout_iter_ranges->addWidget(spinboxd3_formula_position_iter_stop_x, 1, 3, 1, 1);

        label6 = new QLabel(groupBox_iter_ranges);
        label6->setObjectName(QString::fromUtf8("label6"));
        label6->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_iter_ranges->addWidget(label6, 2, 1, 1, 1);

        spinboxd3_formula_position_iter_start_y = new MyDoubleSpinBox(groupBox_iter_ranges);
        spinboxd3_formula_position_iter_start_y->setObjectName(QString::fromUtf8("spinboxd3_formula_position_iter_start_y"));
        spinboxd3_formula_position_iter_start_y->setMinimum(0.000000000000000);
        spinboxd3_formula_position_iter_start_y->setMaximum(99999.000000000000000);
        spinboxd3_formula_position_iter_start_y->setValue(0.000000000000000);
        spinboxd3_formula_position_iter_start_y->setDecimals(0);

        gridLayout_iter_ranges->addWidget(spinboxd3_formula_position_iter_start_y, 2, 2, 1, 1);

        spinboxd3_formula_position_iter_stop_y = new MyDoubleSpinBox(groupBox_iter_ranges);
        spinboxd3_formula_position_iter_stop_y->setObjectName(QString::fromUtf8("spinboxd3_formula_position_iter_stop_y"));
        spinboxd3_formula_position_iter_stop_y->setMinimum(0.000000000000000);
        spinboxd3_formula_position_iter_stop_y->setMaximum(99999.000000000000000);
        spinboxd3_formula_position_iter_stop_y->setValue(250.000000000000000);
        spinboxd3_formula_position_iter_stop_y->setDecimals(0);

        gridLayout_iter_ranges->addWidget(spinboxd3_formula_position_iter_stop_y, 2, 3, 1, 1);

        label7 = new QLabel(groupBox_iter_ranges);
        label7->setObjectName(QString::fromUtf8("label7"));
        label7->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_iter_ranges->addWidget(label7, 3, 1, 1, 1);

        spinboxd3_formula_position_iter_start_z = new MyDoubleSpinBox(groupBox_iter_ranges);
        spinboxd3_formula_position_iter_start_z->setObjectName(QString::fromUtf8("spinboxd3_formula_position_iter_start_z"));
        spinboxd3_formula_position_iter_start_z->setMinimum(0.000000000000000);
        spinboxd3_formula_position_iter_start_z->setMaximum(99999.000000000000000);
        spinboxd3_formula_position_iter_start_z->setValue(0.000000000000000);
        spinboxd3_formula_position_iter_start_z->setDecimals(0);

        gridLayout_iter_ranges->addWidget(spinboxd3_formula_position_iter_start_z, 3, 2, 1, 1);

        spinboxd3_formula_position_iter_stop_z = new MyDoubleSpinBox(groupBox_iter_ranges);
        spinboxd3_formula_position_iter_stop_z->setObjectName(QString::fromUtf8("spinboxd3_formula_position_iter_stop_z"));
        spinboxd3_formula_position_iter_stop_z->setMinimum(0.000000000000000);
        spinboxd3_formula_position_iter_stop_z->setMaximum(99999.000000000000000);
        spinboxd3_formula_position_iter_stop_z->setValue(250.000000000000000);
        spinboxd3_formula_position_iter_stop_z->setDecimals(0);

        gridLayout_iter_ranges->addWidget(spinboxd3_formula_position_iter_stop_z, 3, 3, 1, 1);

        label8 = new QLabel(groupBox_iter_ranges);
        label8->setObjectName(QString::fromUtf8("label8"));

        gridLayout_iter_ranges->addWidget(label8, 4, 0, 1, 1);

        label9 = new QLabel(groupBox_iter_ranges);
        label9->setObjectName(QString::fromUtf8("label9"));
        label9->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_iter_ranges->addWidget(label9, 4, 1, 1, 1);

        spinboxd3_formula_rotation_iter_start_x = new MyDoubleSpinBox(groupBox_iter_ranges);
        spinboxd3_formula_rotation_iter_start_x->setObjectName(QString::fromUtf8("spinboxd3_formula_rotation_iter_start_x"));
        spinboxd3_formula_rotation_iter_start_x->setMinimum(0.000000000000000);
        spinboxd3_formula_rotation_iter_start_x->setMaximum(99999.000000000000000);
        spinboxd3_formula_rotation_iter_start_x->setValue(0.000000000000000);
        spinboxd3_formula_rotation_iter_start_x->setDecimals(0);

        gridLayout_iter_ranges->addWidget(spinboxd3_formula_rotation_iter_start_x, 4, 2, 1, 1);

        spinboxd3_formula_rotation_iter_stop_x = new MyDoubleSpinBox(groupBox_iter_ranges);
        spinboxd3_formula_rotation_iter_stop_x->setObjectName(QString::fromUtf8("spinboxd3_formula_rotation_iter_stop_x"));
        spinboxd3_formula_rotation_iter_stop_x->setMinimum(0.000000000000000);
        spinboxd3_formula_rotation_iter_stop_x->setMaximum(99999.000000000000000);
        spinboxd3_formula_rotation_iter_stop_x->setValue(250.000000000000000);
        spinboxd3_formula_rotation_iter_stop_x->setDecimals(0);

        gridLayout_iter_ranges->addWidget(spinboxd3_formula_rotation_iter_stop_x, 4, 3, 1, 1);

        label10 = new QLabel(groupBox_iter_ranges);
        label10->setObjectName(QString::fromUtf8("label10"));
        label10->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_iter_ranges->addWidget(label10, 5, 1, 1, 1);

        spinboxd3_formula_rotation_iter_start_y = new MyDoubleSpinBox(groupBox_iter_ranges);
        spinboxd3_formula_rotation_iter_start_y->setObjectName(QString::fromUtf8("spinboxd3_formula_rotation_iter_start_y"));
        spinboxd3_formula_rotation_iter_start_y->setMinimum(0.000000000000000);
        spinboxd3_formula_rotation_iter_start_y->setMaximum(99999.000000000000000);
        spinboxd3_formula_rotation_iter_start_y->setValue(0.000000000000000);
        spinboxd3_formula_rotation_iter_start_y->setDecimals(0);

        gridLayout_iter_ranges->addWidget(spinboxd3_formula_rotation_iter_start_y, 5, 2, 1, 1);

        spinboxd3_formula_rotation_iter_stop_y = new MyDoubleSpinBox(groupBox_iter_ranges);
        spinboxd3_formula_rotation_iter_stop_y->setObjectName(QString::fromUtf8("spinboxd3_formula_rotation_iter_stop_y"));
        spinboxd3_formula_rotation_iter_stop_y->setMinimum(0.000000000000000);
        spinboxd3_formula_rotation_iter_stop_y->setMaximum(99999.000000000000000);
        spinboxd3_formula_rotation_iter_stop_y->setValue(250.000000000000000);
        spinboxd3_formula_rotation_iter_stop_y->setDecimals(0);

        gridLayout_iter_ranges->addWidget(spinboxd3_formula_rotation_iter_stop_y, 5, 3, 1, 1);

        label11 = new QLabel(groupBox_iter_ranges);
        label11->setObjectName(QString::fromUtf8("label11"));
        label11->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_iter_ranges->addWidget(label11, 6, 1, 1, 1);

        spinboxd3_formula_rotation_iter_start_z = new MyDoubleSpinBox(groupBox_iter_ranges);
        spinboxd3_formula_rotation_iter_start_z->setObjectName(QString::fromUtf8("spinboxd3_formula_rotation_iter_start_z"));
        spinboxd3_formula_rotation_iter_start_z->setMinimum(0.000000000000000);
        spinboxd3_formula_rotation_iter_start_z->setMaximum(99999.000000000000000);
        spinboxd3_formula_rotation_iter_start_z->setValue(0.000000000000000);
        spinboxd3_formula_rotation_iter_start_z->setDecimals(0);

        gridLayout_iter_ranges->addWidget(spinboxd3_formula_rotation_iter_start_z, 6, 2, 1, 1);

        spinboxd3_formula_rotation_iter_stop_z = new MyDoubleSpinBox(groupBox_iter_ranges);
        spinboxd3_formula_rotation_iter_stop_z->setObjectName(QString::fromUtf8("spinboxd3_formula_rotation_iter_stop_z"));
        spinboxd3_formula_rotation_iter_stop_z->setMinimum(0.000000000000000);
        spinboxd3_formula_rotation_iter_stop_z->setMaximum(99999.000000000000000);
        spinboxd3_formula_rotation_iter_stop_z->setValue(250.000000000000000);
        spinboxd3_formula_rotation_iter_stop_z->setDecimals(0);

        gridLayout_iter_ranges->addWidget(spinboxd3_formula_rotation_iter_stop_z, 6, 3, 1, 1);

        label12 = new QLabel(groupBox_iter_ranges);
        label12->setObjectName(QString::fromUtf8("label12"));

        gridLayout_iter_ranges->addWidget(label12, 7, 0, 1, 1);

        label13 = new QLabel(groupBox_iter_ranges);
        label13->setObjectName(QString::fromUtf8("label13"));
        label13->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_iter_ranges->addWidget(label13, 7, 1, 1, 1);

        spinboxd3_formula_repeat_iter_start_x = new MyDoubleSpinBox(groupBox_iter_ranges);
        spinboxd3_formula_repeat_iter_start_x->setObjectName(QString::fromUtf8("spinboxd3_formula_repeat_iter_start_x"));
        spinboxd3_formula_repeat_iter_start_x->setMinimum(0.000000000000000);
        spinboxd3_formula_repeat_iter_start_x->setMaximum(99999.000000000000000);
        spinboxd3_formula_repeat_iter_start_x->setValue(0.000000000000000);
        spinboxd3_formula_repeat_iter_start_x->setDecimals(0);

        gridLayout_iter_ranges->addWidget(spinboxd3_formula_repeat_iter_start_x, 7, 2, 1, 1);

        spinboxd3_formula_repeat_iter_stop_x = new MyDoubleSpinBox(groupBox_iter_ranges);
        spinboxd3_formula_repeat_iter_stop_x->setObjectName(QString::fromUtf8("spinboxd3_formula_repeat_iter_stop_x"));
        spinboxd3_formula_repeat_iter_stop_x->setMinimum(0.000000000000000);
        spinboxd3_formula_repeat_iter_stop_x->setMaximum(99999.000000000000000);
        spinboxd3_formula_repeat_iter_stop_x->setValue(250.000000000000000);
        spinboxd3_formula_repeat_iter_stop_x->setDecimals(0);

        gridLayout_iter_ranges->addWidget(spinboxd3_formula_repeat_iter_stop_x, 7, 3, 1, 1);

        label14 = new QLabel(groupBox_iter_ranges);
        label14->setObjectName(QString::fromUtf8("label14"));
        label14->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_iter_ranges->addWidget(label14, 8, 1, 1, 1);

        spinboxd3_formula_repeat_iter_start_y = new MyDoubleSpinBox(groupBox_iter_ranges);
        spinboxd3_formula_repeat_iter_start_y->setObjectName(QString::fromUtf8("spinboxd3_formula_repeat_iter_start_y"));
        spinboxd3_formula_repeat_iter_start_y->setMinimum(0.000000000000000);
        spinboxd3_formula_repeat_iter_start_y->setMaximum(99999.000000000000000);
        spinboxd3_formula_repeat_iter_start_y->setValue(0.000000000000000);
        spinboxd3_formula_repeat_iter_start_y->setDecimals(0);

        gridLayout_iter_ranges->addWidget(spinboxd3_formula_repeat_iter_start_y, 8, 2, 1, 1);

        spinboxd3_formula_repeat_iter_stop_y = new MyDoubleSpinBox(groupBox_iter_ranges);
        spinboxd3_formula_repeat_iter_stop_y->setObjectName(QString::fromUtf8("spinboxd3_formula_repeat_iter_stop_y"));
        spinboxd3_formula_repeat_iter_stop_y->setMinimum(0.000000000000000);
        spinboxd3_formula_repeat_iter_stop_y->setMaximum(99999.000000000000000);
        spinboxd3_formula_repeat_iter_stop_y->setValue(250.000000000000000);
        spinboxd3_formula_repeat_iter_stop_y->setDecimals(0);

        gridLayout_iter_ranges->addWidget(spinboxd3_formula_repeat_iter_stop_y, 8, 3, 1, 1);

        label15 = new QLabel(groupBox_iter_ranges);
        label15->setObjectName(QString::fromUtf8("label15"));
        label15->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_iter_ranges->addWidget(label15, 9, 1, 1, 1);

        spinboxd3_formula_repeat_iter_start_z = new MyDoubleSpinBox(groupBox_iter_ranges);
        spinboxd3_formula_repeat_iter_start_z->setObjectName(QString::fromUtf8("spinboxd3_formula_repeat_iter_start_z"));
        spinboxd3_formula_repeat_iter_start_z->setMinimum(0.000000000000000);
        spinboxd3_formula_repeat_iter_start_z->setMaximum(99999.000000000000000);
        spinboxd3_formula_repeat_iter_start_z->setValue(0.000000000000000);
        spinboxd3_formula_repeat_iter_start_z->setDecimals(0);

        gridLayout_iter_ranges->addWidget(spinboxd3_formula_repeat_iter_start_z, 9, 2, 1, 1);

        spinboxd3_formula_repeat_iter_stop_z = new MyDoubleSpinBox(groupBox_iter_ranges);
        spinboxd3_formula_repeat_iter_stop_z->setObjectName(QString::fromUtf8("spinboxd3_formula_repeat_iter_stop_z"));
        spinboxd3_formula_repeat_iter_stop_z->setMinimum(0.000000000000000);
        spinboxd3_formula_repeat_iter_stop_z->setMaximum(99999.000000000000000);
        spinboxd3_formula_repeat_iter_stop_z->setValue(250.000000000000000);
        spinboxd3_formula_repeat_iter_stop_z->setDecimals(0);

        gridLayout_iter_ranges->addWidget(spinboxd3_formula_repeat_iter_stop_z, 9, 3, 1, 1);


        gridLayout_36->addWidget(groupBox_iter_ranges, 9, 0, 1, 3);


        verticalLayout_3->addLayout(gridLayout_36);


        verticalLayout_68->addWidget(groupBox);

        groupCheck_julia_mode = new MyGroupBox(scrollAreaWidgetContents_12);
        groupCheck_julia_mode->setObjectName(QString::fromUtf8("groupCheck_julia_mode"));
        groupCheck_julia_mode->setCheckable(true);
        verticalLayout_48 = new QVBoxLayout(groupCheck_julia_mode);
        verticalLayout_48->setSpacing(2);
        verticalLayout_48->setObjectName(QString::fromUtf8("verticalLayout_48"));
        verticalLayout_48->setContentsMargins(2, 2, 2, 2);
        gridLayout_22 = new QGridLayout();
        gridLayout_22->setSpacing(2);
        gridLayout_22->setObjectName(QString::fromUtf8("gridLayout_22"));
        label_116 = new QLabel(groupCheck_julia_mode);
        label_116->setObjectName(QString::fromUtf8("label_116"));
        sizePolicy2.setHeightForWidth(label_116->sizePolicy().hasHeightForWidth());
        label_116->setSizePolicy(sizePolicy2);
        label_116->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_22->addWidget(label_116, 1, 1, 1, 1);

        label_113 = new QLabel(groupCheck_julia_mode);
        label_113->setObjectName(QString::fromUtf8("label_113"));

        gridLayout_22->addWidget(label_113, 0, 0, 1, 1);

        vect3_julia_c_y = new MyLineEdit(groupCheck_julia_mode);
        vect3_julia_c_y->setObjectName(QString::fromUtf8("vect3_julia_c_y"));
        sizePolicy1.setHeightForWidth(vect3_julia_c_y->sizePolicy().hasHeightForWidth());
        vect3_julia_c_y->setSizePolicy(sizePolicy1);

        gridLayout_22->addWidget(vect3_julia_c_y, 1, 2, 1, 1);

        vect3_julia_c_x = new MyLineEdit(groupCheck_julia_mode);
        vect3_julia_c_x->setObjectName(QString::fromUtf8("vect3_julia_c_x"));
        sizePolicy1.setHeightForWidth(vect3_julia_c_x->sizePolicy().hasHeightForWidth());
        vect3_julia_c_x->setSizePolicy(sizePolicy1);

        gridLayout_22->addWidget(vect3_julia_c_x, 0, 2, 1, 1);

        label_120 = new QLabel(groupCheck_julia_mode);
        label_120->setObjectName(QString::fromUtf8("label_120"));
        sizePolicy2.setHeightForWidth(label_120->sizePolicy().hasHeightForWidth());
        label_120->setSizePolicy(sizePolicy2);
        label_120->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_22->addWidget(label_120, 2, 1, 1, 1);

        label_115 = new QLabel(groupCheck_julia_mode);
        label_115->setObjectName(QString::fromUtf8("label_115"));
        sizePolicy2.setHeightForWidth(label_115->sizePolicy().hasHeightForWidth());
        label_115->setSizePolicy(sizePolicy2);
        label_115->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_22->addWidget(label_115, 0, 1, 1, 1);

        vect3_julia_c_z = new MyLineEdit(groupCheck_julia_mode);
        vect3_julia_c_z->setObjectName(QString::fromUtf8("vect3_julia_c_z"));
        sizePolicy1.setHeightForWidth(vect3_julia_c_z->sizePolicy().hasHeightForWidth());
        vect3_julia_c_z->setSizePolicy(sizePolicy1);

        gridLayout_22->addWidget(vect3_julia_c_z, 2, 2, 1, 1);


        verticalLayout_48->addLayout(gridLayout_22);

        pushButton_get_julia_constant = new QPushButton(groupCheck_julia_mode);
        pushButton_get_julia_constant->setObjectName(QString::fromUtf8("pushButton_get_julia_constant"));
        sizePolicy3.setHeightForWidth(pushButton_get_julia_constant->sizePolicy().hasHeightForWidth());
        pushButton_get_julia_constant->setSizePolicy(sizePolicy3);

        verticalLayout_48->addWidget(pushButton_get_julia_constant);

        groupBox_julia_fine_tune = new QGroupBox(groupCheck_julia_mode);
        groupBox_julia_fine_tune->setObjectName(QString::fromUtf8("groupBox_julia_fine_tune"));
        gridLayout_julia_fine_tune = new QGridLayout(groupBox_julia_fine_tune);
        gridLayout_julia_fine_tune->setSpacing(3);
        gridLayout_julia_fine_tune->setObjectName(QString::fromUtf8("gridLayout_julia_fine_tune"));
        label16 = new QLabel(groupBox_julia_fine_tune);
        label16->setObjectName(QString::fromUtf8("label16"));
        label16->setAlignment(Qt::AlignCenter);

        gridLayout_julia_fine_tune->addWidget(label16, 0, 1, 1, 1);

        label17 = new QLabel(groupBox_julia_fine_tune);
        label17->setObjectName(QString::fromUtf8("label17"));
        label17->setAlignment(Qt::AlignCenter);

        gridLayout_julia_fine_tune->addWidget(label17, 0, 2, 1, 1);

        label18 = new QLabel(groupBox_julia_fine_tune);
        label18->setObjectName(QString::fromUtf8("label18"));
        label18->setAlignment(Qt::AlignCenter);

        gridLayout_julia_fine_tune->addWidget(label18, 0, 3, 1, 1);

        label19 = new QLabel(groupBox_julia_fine_tune);
        label19->setObjectName(QString::fromUtf8("label19"));

        gridLayout_julia_fine_tune->addWidget(label19, 1, 0, 1, 1);

        spinbox3_julia_c_iter_start_x = new MyDoubleSpinBox(groupBox_julia_fine_tune);
        spinbox3_julia_c_iter_start_x->setObjectName(QString::fromUtf8("spinbox3_julia_c_iter_start_x"));
        spinbox3_julia_c_iter_start_x->setDecimals(0);
        spinbox3_julia_c_iter_start_x->setMinimum(0.000000000000000);
        spinbox3_julia_c_iter_start_x->setMaximum(99999.000000000000000);

        gridLayout_julia_fine_tune->addWidget(spinbox3_julia_c_iter_start_x, 1, 1, 1, 1);

        spinbox3_julia_c_iter_stop_x = new MyDoubleSpinBox(groupBox_julia_fine_tune);
        spinbox3_julia_c_iter_stop_x->setObjectName(QString::fromUtf8("spinbox3_julia_c_iter_stop_x"));
        spinbox3_julia_c_iter_stop_x->setDecimals(0);
        spinbox3_julia_c_iter_stop_x->setMinimum(0.000000000000000);
        spinbox3_julia_c_iter_stop_x->setMaximum(99999.000000000000000);

        gridLayout_julia_fine_tune->addWidget(spinbox3_julia_c_iter_stop_x, 1, 2, 1, 1);

        spinbox3_julia_c_weight_x = new MyDoubleSpinBox(groupBox_julia_fine_tune);
        spinbox3_julia_c_weight_x->setObjectName(QString::fromUtf8("spinbox3_julia_c_weight_x"));
        spinbox3_julia_c_weight_x->setDecimals(3);
        spinbox3_julia_c_weight_x->setMinimum(-10.000000000000000);
        spinbox3_julia_c_weight_x->setMaximum(10.000000000000000);
        spinbox3_julia_c_weight_x->setSingleStep(0.100000000000000);

        gridLayout_julia_fine_tune->addWidget(spinbox3_julia_c_weight_x, 1, 3, 1, 1);

        label20 = new QLabel(groupBox_julia_fine_tune);
        label20->setObjectName(QString::fromUtf8("label20"));

        gridLayout_julia_fine_tune->addWidget(label20, 2, 0, 1, 1);

        spinbox3_julia_c_iter_start_y = new MyDoubleSpinBox(groupBox_julia_fine_tune);
        spinbox3_julia_c_iter_start_y->setObjectName(QString::fromUtf8("spinbox3_julia_c_iter_start_y"));
        spinbox3_julia_c_iter_start_y->setDecimals(0);
        spinbox3_julia_c_iter_start_y->setMinimum(0.000000000000000);
        spinbox3_julia_c_iter_start_y->setMaximum(99999.000000000000000);

        gridLayout_julia_fine_tune->addWidget(spinbox3_julia_c_iter_start_y, 2, 1, 1, 1);

        spinbox3_julia_c_iter_stop_y = new MyDoubleSpinBox(groupBox_julia_fine_tune);
        spinbox3_julia_c_iter_stop_y->setObjectName(QString::fromUtf8("spinbox3_julia_c_iter_stop_y"));
        spinbox3_julia_c_iter_stop_y->setDecimals(0);
        spinbox3_julia_c_iter_stop_y->setMinimum(0.000000000000000);
        spinbox3_julia_c_iter_stop_y->setMaximum(99999.000000000000000);

        gridLayout_julia_fine_tune->addWidget(spinbox3_julia_c_iter_stop_y, 2, 2, 1, 1);

        spinbox3_julia_c_weight_y = new MyDoubleSpinBox(groupBox_julia_fine_tune);
        spinbox3_julia_c_weight_y->setObjectName(QString::fromUtf8("spinbox3_julia_c_weight_y"));
        spinbox3_julia_c_weight_y->setDecimals(3);
        spinbox3_julia_c_weight_y->setMinimum(-10.000000000000000);
        spinbox3_julia_c_weight_y->setMaximum(10.000000000000000);
        spinbox3_julia_c_weight_y->setSingleStep(0.100000000000000);

        gridLayout_julia_fine_tune->addWidget(spinbox3_julia_c_weight_y, 2, 3, 1, 1);

        label21 = new QLabel(groupBox_julia_fine_tune);
        label21->setObjectName(QString::fromUtf8("label21"));

        gridLayout_julia_fine_tune->addWidget(label21, 3, 0, 1, 1);

        spinbox3_julia_c_iter_start_z = new MyDoubleSpinBox(groupBox_julia_fine_tune);
        spinbox3_julia_c_iter_start_z->setObjectName(QString::fromUtf8("spinbox3_julia_c_iter_start_z"));
        spinbox3_julia_c_iter_start_z->setDecimals(0);
        spinbox3_julia_c_iter_start_z->setMinimum(0.000000000000000);
        spinbox3_julia_c_iter_start_z->setMaximum(99999.000000000000000);

        gridLayout_julia_fine_tune->addWidget(spinbox3_julia_c_iter_start_z, 3, 1, 1, 1);

        spinbox3_julia_c_iter_stop_z = new MyDoubleSpinBox(groupBox_julia_fine_tune);
        spinbox3_julia_c_iter_stop_z->setObjectName(QString::fromUtf8("spinbox3_julia_c_iter_stop_z"));
        spinbox3_julia_c_iter_stop_z->setDecimals(0);
        spinbox3_julia_c_iter_stop_z->setMinimum(0.000000000000000);
        spinbox3_julia_c_iter_stop_z->setMaximum(99999.000000000000000);

        gridLayout_julia_fine_tune->addWidget(spinbox3_julia_c_iter_stop_z, 3, 2, 1, 1);

        spinbox3_julia_c_weight_z = new MyDoubleSpinBox(groupBox_julia_fine_tune);
        spinbox3_julia_c_weight_z->setObjectName(QString::fromUtf8("spinbox3_julia_c_weight_z"));
        spinbox3_julia_c_weight_z->setDecimals(3);
        spinbox3_julia_c_weight_z->setMinimum(-10.000000000000000);
        spinbox3_julia_c_weight_z->setMaximum(10.000000000000000);
        spinbox3_julia_c_weight_z->setSingleStep(0.100000000000000);

        gridLayout_julia_fine_tune->addWidget(spinbox3_julia_c_weight_z, 3, 3, 1, 1);

        line = new QFrame(groupBox_julia_fine_tune);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_julia_fine_tune->addWidget(line, 4, 0, 1, 4);

        label22 = new QLabel(groupBox_julia_fine_tune);
        label22->setObjectName(QString::fromUtf8("label22"));

        gridLayout_julia_fine_tune->addWidget(label22, 5, 0, 1, 1);

        spinbox3_const_c_iter_start_x = new MyDoubleSpinBox(groupBox_julia_fine_tune);
        spinbox3_const_c_iter_start_x->setObjectName(QString::fromUtf8("spinbox3_const_c_iter_start_x"));
        spinbox3_const_c_iter_start_x->setDecimals(0);
        spinbox3_const_c_iter_start_x->setMinimum(0.000000000000000);
        spinbox3_const_c_iter_start_x->setMaximum(99999.000000000000000);

        gridLayout_julia_fine_tune->addWidget(spinbox3_const_c_iter_start_x, 5, 1, 1, 1);

        spinbox3_const_c_iter_stop_x = new MyDoubleSpinBox(groupBox_julia_fine_tune);
        spinbox3_const_c_iter_stop_x->setObjectName(QString::fromUtf8("spinbox3_const_c_iter_stop_x"));
        spinbox3_const_c_iter_stop_x->setDecimals(0);
        spinbox3_const_c_iter_stop_x->setMinimum(0.000000000000000);
        spinbox3_const_c_iter_stop_x->setMaximum(99999.000000000000000);

        gridLayout_julia_fine_tune->addWidget(spinbox3_const_c_iter_stop_x, 5, 2, 1, 1);

        spinbox3_const_c_weight_x = new MyDoubleSpinBox(groupBox_julia_fine_tune);
        spinbox3_const_c_weight_x->setObjectName(QString::fromUtf8("spinbox3_const_c_weight_x"));
        spinbox3_const_c_weight_x->setDecimals(3);
        spinbox3_const_c_weight_x->setMinimum(-10.000000000000000);
        spinbox3_const_c_weight_x->setMaximum(10.000000000000000);
        spinbox3_const_c_weight_x->setSingleStep(0.100000000000000);

        gridLayout_julia_fine_tune->addWidget(spinbox3_const_c_weight_x, 5, 3, 1, 1);

        label23 = new QLabel(groupBox_julia_fine_tune);
        label23->setObjectName(QString::fromUtf8("label23"));

        gridLayout_julia_fine_tune->addWidget(label23, 6, 0, 1, 1);

        spinbox3_const_c_iter_start_y = new MyDoubleSpinBox(groupBox_julia_fine_tune);
        spinbox3_const_c_iter_start_y->setObjectName(QString::fromUtf8("spinbox3_const_c_iter_start_y"));
        spinbox3_const_c_iter_start_y->setDecimals(0);
        spinbox3_const_c_iter_start_y->setMinimum(0.000000000000000);
        spinbox3_const_c_iter_start_y->setMaximum(99999.000000000000000);

        gridLayout_julia_fine_tune->addWidget(spinbox3_const_c_iter_start_y, 6, 1, 1, 1);

        spinbox3_const_c_iter_stop_y = new MyDoubleSpinBox(groupBox_julia_fine_tune);
        spinbox3_const_c_iter_stop_y->setObjectName(QString::fromUtf8("spinbox3_const_c_iter_stop_y"));
        spinbox3_const_c_iter_stop_y->setDecimals(0);
        spinbox3_const_c_iter_stop_y->setMinimum(0.000000000000000);
        spinbox3_const_c_iter_stop_y->setMaximum(99999.000000000000000);

        gridLayout_julia_fine_tune->addWidget(spinbox3_const_c_iter_stop_y, 6, 2, 1, 1);

        spinbox3_const_c_weight_y = new MyDoubleSpinBox(groupBox_julia_fine_tune);
        spinbox3_const_c_weight_y->setObjectName(QString::fromUtf8("spinbox3_const_c_weight_y"));
        spinbox3_const_c_weight_y->setDecimals(3);
        spinbox3_const_c_weight_y->setMinimum(-10.000000000000000);
        spinbox3_const_c_weight_y->setMaximum(10.000000000000000);
        spinbox3_const_c_weight_y->setSingleStep(0.100000000000000);

        gridLayout_julia_fine_tune->addWidget(spinbox3_const_c_weight_y, 6, 3, 1, 1);

        label24 = new QLabel(groupBox_julia_fine_tune);
        label24->setObjectName(QString::fromUtf8("label24"));

        gridLayout_julia_fine_tune->addWidget(label24, 7, 0, 1, 1);

        spinbox3_const_c_iter_start_z = new MyDoubleSpinBox(groupBox_julia_fine_tune);
        spinbox3_const_c_iter_start_z->setObjectName(QString::fromUtf8("spinbox3_const_c_iter_start_z"));
        spinbox3_const_c_iter_start_z->setDecimals(0);
        spinbox3_const_c_iter_start_z->setMinimum(0.000000000000000);
        spinbox3_const_c_iter_start_z->setMaximum(99999.000000000000000);

        gridLayout_julia_fine_tune->addWidget(spinbox3_const_c_iter_start_z, 7, 1, 1, 1);

        spinbox3_const_c_iter_stop_z = new MyDoubleSpinBox(groupBox_julia_fine_tune);
        spinbox3_const_c_iter_stop_z->setObjectName(QString::fromUtf8("spinbox3_const_c_iter_stop_z"));
        spinbox3_const_c_iter_stop_z->setDecimals(0);
        spinbox3_const_c_iter_stop_z->setMinimum(0.000000000000000);
        spinbox3_const_c_iter_stop_z->setMaximum(99999.000000000000000);

        gridLayout_julia_fine_tune->addWidget(spinbox3_const_c_iter_stop_z, 7, 2, 1, 1);

        spinbox3_const_c_weight_z = new MyDoubleSpinBox(groupBox_julia_fine_tune);
        spinbox3_const_c_weight_z->setObjectName(QString::fromUtf8("spinbox3_const_c_weight_z"));
        spinbox3_const_c_weight_z->setDecimals(3);
        spinbox3_const_c_weight_z->setMinimum(-10.000000000000000);
        spinbox3_const_c_weight_z->setMaximum(10.000000000000000);
        spinbox3_const_c_weight_z->setSingleStep(0.100000000000000);

        gridLayout_julia_fine_tune->addWidget(spinbox3_const_c_weight_z, 7, 3, 1, 1);


        verticalLayout_48->addWidget(groupBox_julia_fine_tune);

        groupBox_julia_explorer = new QGroupBox(groupCheck_julia_mode);
        groupBox_julia_explorer->setObjectName(QString::fromUtf8("groupBox_julia_explorer"));
        layout_julia_explorer = new QVBoxLayout(groupBox_julia_explorer);
        layout_julia_explorer->setSpacing(3);
        layout_julia_explorer->setObjectName(QString::fromUtf8("layout_julia_explorer"));
        layout_julia_explorer->setContentsMargins(3, 3, 3, 3);
        gridLayout_julia_sliders = new QGridLayout();
        gridLayout_julia_sliders->setSpacing(2);
        gridLayout_julia_sliders->setObjectName(QString::fromUtf8("gridLayout_julia_sliders"));
        label_julia_slider_cx = new QLabel(groupBox_julia_explorer);
        label_julia_slider_cx->setObjectName(QString::fromUtf8("label_julia_slider_cx"));
        label_julia_slider_cx->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_julia_sliders->addWidget(label_julia_slider_cx, 0, 0, 1, 1);

        jslider_julia_cx = new QSlider(groupBox_julia_explorer);
        jslider_julia_cx->setObjectName(QString::fromUtf8("jslider_julia_cx"));
        jslider_julia_cx->setMinimum(-2000);
        jslider_julia_cx->setMaximum(2000);
        jslider_julia_cx->setOrientation(Qt::Horizontal);

        gridLayout_julia_sliders->addWidget(jslider_julia_cx, 0, 1, 1, 1);

        label_julia_cx_value = new QLabel(groupBox_julia_explorer);
        label_julia_cx_value->setObjectName(QString::fromUtf8("label_julia_cx_value"));
        label_julia_cx_value->setMinimumSize(QSize(48, 0));
        label_julia_cx_value->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_julia_sliders->addWidget(label_julia_cx_value, 0, 2, 1, 1);

        label_julia_slider_cy = new QLabel(groupBox_julia_explorer);
        label_julia_slider_cy->setObjectName(QString::fromUtf8("label_julia_slider_cy"));
        label_julia_slider_cy->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_julia_sliders->addWidget(label_julia_slider_cy, 1, 0, 1, 1);

        jslider_julia_cy = new QSlider(groupBox_julia_explorer);
        jslider_julia_cy->setObjectName(QString::fromUtf8("jslider_julia_cy"));
        jslider_julia_cy->setMinimum(-2000);
        jslider_julia_cy->setMaximum(2000);
        jslider_julia_cy->setOrientation(Qt::Horizontal);

        gridLayout_julia_sliders->addWidget(jslider_julia_cy, 1, 1, 1, 1);

        label_julia_cy_value = new QLabel(groupBox_julia_explorer);
        label_julia_cy_value->setObjectName(QString::fromUtf8("label_julia_cy_value"));
        label_julia_cy_value->setMinimumSize(QSize(48, 0));
        label_julia_cy_value->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_julia_sliders->addWidget(label_julia_cy_value, 1, 2, 1, 1);

        label_julia_slider_cz = new QLabel(groupBox_julia_explorer);
        label_julia_slider_cz->setObjectName(QString::fromUtf8("label_julia_slider_cz"));
        label_julia_slider_cz->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_julia_sliders->addWidget(label_julia_slider_cz, 2, 0, 1, 1);

        jslider_julia_cz = new QSlider(groupBox_julia_explorer);
        jslider_julia_cz->setObjectName(QString::fromUtf8("jslider_julia_cz"));
        jslider_julia_cz->setMinimum(-2000);
        jslider_julia_cz->setMaximum(2000);
        jslider_julia_cz->setOrientation(Qt::Horizontal);

        gridLayout_julia_sliders->addWidget(jslider_julia_cz, 2, 1, 1, 1);

        label_julia_cz_value = new QLabel(groupBox_julia_explorer);
        label_julia_cz_value->setObjectName(QString::fromUtf8("label_julia_cz_value"));
        label_julia_cz_value->setMinimumSize(QSize(48, 0));
        label_julia_cz_value->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_julia_sliders->addWidget(label_julia_cz_value, 2, 2, 1, 1);

        label_julia_range = new QLabel(groupBox_julia_explorer);
        label_julia_range->setObjectName(QString::fromUtf8("label_julia_range"));
        label_julia_range->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        gridLayout_julia_sliders->addWidget(label_julia_range, 3, 0, 1, 1);

        comboBox_julia_range = new QComboBox(groupBox_julia_explorer);
        comboBox_julia_range->addItem(QString());
        comboBox_julia_range->addItem(QString());
        comboBox_julia_range->addItem(QString());
        comboBox_julia_range->addItem(QString());
        comboBox_julia_range->addItem(QString());
        comboBox_julia_range->setObjectName(QString::fromUtf8("comboBox_julia_range"));

        gridLayout_julia_sliders->addWidget(comboBox_julia_range, 3, 1, 1, 1);


        layout_julia_explorer->addLayout(gridLayout_julia_sliders);

        layout_julia_actions = new QHBoxLayout();
        layout_julia_actions->setSpacing(2);
        layout_julia_actions->setObjectName(QString::fromUtf8("layout_julia_actions"));
        pushButton_julia_copy = new QPushButton(groupBox_julia_explorer);
        pushButton_julia_copy->setObjectName(QString::fromUtf8("pushButton_julia_copy"));
        pushButton_julia_copy->setMaximumSize(QSize(16777215, 24));

        layout_julia_actions->addWidget(pushButton_julia_copy);

        pushButton_julia_paste = new QPushButton(groupBox_julia_explorer);
        pushButton_julia_paste->setObjectName(QString::fromUtf8("pushButton_julia_paste"));
        pushButton_julia_paste->setMaximumSize(QSize(16777215, 24));

        layout_julia_actions->addWidget(pushButton_julia_paste);

        pushButton_julia_random = new QPushButton(groupBox_julia_explorer);
        pushButton_julia_random->setObjectName(QString::fromUtf8("pushButton_julia_random"));
        pushButton_julia_random->setMaximumSize(QSize(16777215, 24));

        layout_julia_actions->addWidget(pushButton_julia_random);

        pushButton_julia_zero = new QPushButton(groupBox_julia_explorer);
        pushButton_julia_zero->setObjectName(QString::fromUtf8("pushButton_julia_zero"));
        pushButton_julia_zero->setMaximumSize(QSize(16777215, 24));

        layout_julia_actions->addWidget(pushButton_julia_zero);


        layout_julia_explorer->addLayout(layout_julia_actions);

        groupBox_julia_presets = new QGroupBox(groupBox_julia_explorer);
        groupBox_julia_presets->setObjectName(QString::fromUtf8("groupBox_julia_presets"));
        gridLayout_julia_presets = new QGridLayout(groupBox_julia_presets);
        gridLayout_julia_presets->setSpacing(2);
        gridLayout_julia_presets->setObjectName(QString::fromUtf8("gridLayout_julia_presets"));
        gridLayout_julia_presets->setContentsMargins(2, 2, 2, 2);
        pushButton_julia_preset_1 = new QPushButton(groupBox_julia_presets);
        pushButton_julia_preset_1->setObjectName(QString::fromUtf8("pushButton_julia_preset_1"));
        pushButton_julia_preset_1->setMaximumSize(QSize(16777215, 22));

        gridLayout_julia_presets->addWidget(pushButton_julia_preset_1, 0, 0, 1, 1);

        pushButton_julia_preset_2 = new QPushButton(groupBox_julia_presets);
        pushButton_julia_preset_2->setObjectName(QString::fromUtf8("pushButton_julia_preset_2"));
        pushButton_julia_preset_2->setMaximumSize(QSize(16777215, 22));

        gridLayout_julia_presets->addWidget(pushButton_julia_preset_2, 0, 1, 1, 1);

        pushButton_julia_preset_3 = new QPushButton(groupBox_julia_presets);
        pushButton_julia_preset_3->setObjectName(QString::fromUtf8("pushButton_julia_preset_3"));
        pushButton_julia_preset_3->setMaximumSize(QSize(16777215, 22));

        gridLayout_julia_presets->addWidget(pushButton_julia_preset_3, 0, 2, 1, 1);

        pushButton_julia_preset_4 = new QPushButton(groupBox_julia_presets);
        pushButton_julia_preset_4->setObjectName(QString::fromUtf8("pushButton_julia_preset_4"));
        pushButton_julia_preset_4->setMaximumSize(QSize(16777215, 22));

        gridLayout_julia_presets->addWidget(pushButton_julia_preset_4, 1, 0, 1, 1);

        pushButton_julia_preset_5 = new QPushButton(groupBox_julia_presets);
        pushButton_julia_preset_5->setObjectName(QString::fromUtf8("pushButton_julia_preset_5"));
        pushButton_julia_preset_5->setMaximumSize(QSize(16777215, 22));

        gridLayout_julia_presets->addWidget(pushButton_julia_preset_5, 1, 1, 1, 1);

        pushButton_julia_preset_6 = new QPushButton(groupBox_julia_presets);
        pushButton_julia_preset_6->setObjectName(QString::fromUtf8("pushButton_julia_preset_6"));
        pushButton_julia_preset_6->setMaximumSize(QSize(16777215, 22));

        gridLayout_julia_presets->addWidget(pushButton_julia_preset_6, 1, 2, 1, 1);

        pushButton_julia_preset_7 = new QPushButton(groupBox_julia_presets);
        pushButton_julia_preset_7->setObjectName(QString::fromUtf8("pushButton_julia_preset_7"));
        pushButton_julia_preset_7->setMaximumSize(QSize(16777215, 22));

        gridLayout_julia_presets->addWidget(pushButton_julia_preset_7, 2, 0, 1, 1);

        pushButton_julia_preset_8 = new QPushButton(groupBox_julia_presets);
        pushButton_julia_preset_8->setObjectName(QString::fromUtf8("pushButton_julia_preset_8"));
        pushButton_julia_preset_8->setMaximumSize(QSize(16777215, 22));

        gridLayout_julia_presets->addWidget(pushButton_julia_preset_8, 2, 1, 1, 1);

        pushButton_julia_preset_9 = new QPushButton(groupBox_julia_presets);
        pushButton_julia_preset_9->setObjectName(QString::fromUtf8("pushButton_julia_preset_9"));
        pushButton_julia_preset_9->setMaximumSize(QSize(16777215, 22));

        gridLayout_julia_presets->addWidget(pushButton_julia_preset_9, 2, 2, 1, 1);


        layout_julia_explorer->addWidget(groupBox_julia_presets);

        groupBox_julia_sweep = new QGroupBox(groupBox_julia_explorer);
        groupBox_julia_sweep->setObjectName(QString::fromUtf8("groupBox_julia_sweep"));
        layout_julia_sweep = new QVBoxLayout(groupBox_julia_sweep);
        layout_julia_sweep->setSpacing(2);
        layout_julia_sweep->setObjectName(QString::fromUtf8("layout_julia_sweep"));
        layout_julia_sweep->setContentsMargins(2, 2, 2, 2);
        layout_sweep_axis = new QHBoxLayout();
        layout_sweep_axis->setObjectName(QString::fromUtf8("layout_sweep_axis"));
        label_sweep_axis = new QLabel(groupBox_julia_sweep);
        label_sweep_axis->setObjectName(QString::fromUtf8("label_sweep_axis"));

        layout_sweep_axis->addWidget(label_sweep_axis);

        comboBox_julia_sweep_axis = new QComboBox(groupBox_julia_sweep);
        comboBox_julia_sweep_axis->addItem(QString());
        comboBox_julia_sweep_axis->addItem(QString());
        comboBox_julia_sweep_axis->addItem(QString());
        comboBox_julia_sweep_axis->addItem(QString());
        comboBox_julia_sweep_axis->setObjectName(QString::fromUtf8("comboBox_julia_sweep_axis"));

        layout_sweep_axis->addWidget(comboBox_julia_sweep_axis);


        layout_julia_sweep->addLayout(layout_sweep_axis);

        layout_sweep_range = new QHBoxLayout();
        layout_sweep_range->setObjectName(QString::fromUtf8("layout_sweep_range"));
        label_sweep_from = new QLabel(groupBox_julia_sweep);
        label_sweep_from->setObjectName(QString::fromUtf8("label_sweep_from"));

        layout_sweep_range->addWidget(label_sweep_from);

        spinBox_julia_sweep_from = new QDoubleSpinBox(groupBox_julia_sweep);
        spinBox_julia_sweep_from->setObjectName(QString::fromUtf8("spinBox_julia_sweep_from"));
        spinBox_julia_sweep_from->setMinimum(-10.000000000000000);
        spinBox_julia_sweep_from->setMaximum(10.000000000000000);
        spinBox_julia_sweep_from->setValue(-2.000000000000000);
        spinBox_julia_sweep_from->setDecimals(3);
        spinBox_julia_sweep_from->setSingleStep(0.100000000000000);

        layout_sweep_range->addWidget(spinBox_julia_sweep_from);

        label_sweep_to = new QLabel(groupBox_julia_sweep);
        label_sweep_to->setObjectName(QString::fromUtf8("label_sweep_to"));

        layout_sweep_range->addWidget(label_sweep_to);

        spinBox_julia_sweep_to = new QDoubleSpinBox(groupBox_julia_sweep);
        spinBox_julia_sweep_to->setObjectName(QString::fromUtf8("spinBox_julia_sweep_to"));
        spinBox_julia_sweep_to->setMinimum(-10.000000000000000);
        spinBox_julia_sweep_to->setMaximum(10.000000000000000);
        spinBox_julia_sweep_to->setValue(2.000000000000000);
        spinBox_julia_sweep_to->setDecimals(3);
        spinBox_julia_sweep_to->setSingleStep(0.100000000000000);

        layout_sweep_range->addWidget(spinBox_julia_sweep_to);


        layout_julia_sweep->addLayout(layout_sweep_range);

        layout_sweep_controls = new QHBoxLayout();
        layout_sweep_controls->setSpacing(2);
        layout_sweep_controls->setObjectName(QString::fromUtf8("layout_sweep_controls"));
        pushButton_julia_sweep_start = new QPushButton(groupBox_julia_sweep);
        pushButton_julia_sweep_start->setObjectName(QString::fromUtf8("pushButton_julia_sweep_start"));
        pushButton_julia_sweep_start->setMaximumSize(QSize(16777215, 24));

        layout_sweep_controls->addWidget(pushButton_julia_sweep_start);

        pushButton_julia_sweep_stop = new QPushButton(groupBox_julia_sweep);
        pushButton_julia_sweep_stop->setObjectName(QString::fromUtf8("pushButton_julia_sweep_stop"));
        pushButton_julia_sweep_stop->setMaximumSize(QSize(16777215, 24));

        layout_sweep_controls->addWidget(pushButton_julia_sweep_stop);

        spinBox_julia_sweep_steps = new QSpinBox(groupBox_julia_sweep);
        spinBox_julia_sweep_steps->setObjectName(QString::fromUtf8("spinBox_julia_sweep_steps"));
        spinBox_julia_sweep_steps->setMinimum(5);
        spinBox_julia_sweep_steps->setMaximum(1000);
        spinBox_julia_sweep_steps->setValue(50);

        layout_sweep_controls->addWidget(spinBox_julia_sweep_steps);


        layout_julia_sweep->addLayout(layout_sweep_controls);

        progressBar_julia_sweep = new QProgressBar(groupBox_julia_sweep);
        progressBar_julia_sweep->setObjectName(QString::fromUtf8("progressBar_julia_sweep"));
        progressBar_julia_sweep->setValue(0);
        progressBar_julia_sweep->setMaximumSize(QSize(16777215, 12));

        layout_julia_sweep->addWidget(progressBar_julia_sweep);


        layout_julia_explorer->addWidget(groupBox_julia_sweep);

        groupBox_julia_history = new QGroupBox(groupBox_julia_explorer);
        groupBox_julia_history->setObjectName(QString::fromUtf8("groupBox_julia_history"));
        layout_julia_history = new QVBoxLayout(groupBox_julia_history);
        layout_julia_history->setSpacing(2);
        layout_julia_history->setObjectName(QString::fromUtf8("layout_julia_history"));
        layout_julia_history->setContentsMargins(2, 2, 2, 2);
        listWidget_julia_history = new QListWidget(groupBox_julia_history);
        listWidget_julia_history->setObjectName(QString::fromUtf8("listWidget_julia_history"));
        listWidget_julia_history->setMaximumSize(QSize(16777215, 90));

        layout_julia_history->addWidget(listWidget_julia_history);

        layout_julia_history_buttons = new QHBoxLayout();
        layout_julia_history_buttons->setSpacing(2);
        layout_julia_history_buttons->setObjectName(QString::fromUtf8("layout_julia_history_buttons"));
        pushButton_julia_history_save = new QPushButton(groupBox_julia_history);
        pushButton_julia_history_save->setObjectName(QString::fromUtf8("pushButton_julia_history_save"));
        pushButton_julia_history_save->setMaximumSize(QSize(16777215, 24));

        layout_julia_history_buttons->addWidget(pushButton_julia_history_save);

        pushButton_julia_history_clear = new QPushButton(groupBox_julia_history);
        pushButton_julia_history_clear->setObjectName(QString::fromUtf8("pushButton_julia_history_clear"));
        pushButton_julia_history_clear->setMaximumSize(QSize(16777215, 24));

        layout_julia_history_buttons->addWidget(pushButton_julia_history_clear);


        layout_julia_history->addLayout(layout_julia_history_buttons);


        layout_julia_explorer->addWidget(groupBox_julia_history);


        verticalLayout_48->addWidget(groupBox_julia_explorer);

        groupBox_julia_heatmap = new QGroupBox(groupCheck_julia_mode);
        groupBox_julia_heatmap->setObjectName(QString::fromUtf8("groupBox_julia_heatmap"));
        layout_julia_heatmap = new QVBoxLayout(groupBox_julia_heatmap);
        layout_julia_heatmap->setSpacing(3);
        layout_julia_heatmap->setObjectName(QString::fromUtf8("layout_julia_heatmap"));
        layout_julia_heatmap->setContentsMargins(3, 3, 3, 3);
        layout_heatmap_controls = new QHBoxLayout();
        layout_heatmap_controls->setSpacing(3);
        layout_heatmap_controls->setObjectName(QString::fromUtf8("layout_heatmap_controls"));
        label_heatmap_h = new QLabel(groupBox_julia_heatmap);
        label_heatmap_h->setObjectName(QString::fromUtf8("label_heatmap_h"));

        layout_heatmap_controls->addWidget(label_heatmap_h);

        comboBox_heatmap_axis_h = new QComboBox(groupBox_julia_heatmap);
        comboBox_heatmap_axis_h->addItem(QString());
        comboBox_heatmap_axis_h->addItem(QString());
        comboBox_heatmap_axis_h->addItem(QString());
        comboBox_heatmap_axis_h->setObjectName(QString::fromUtf8("comboBox_heatmap_axis_h"));

        layout_heatmap_controls->addWidget(comboBox_heatmap_axis_h);

        label_heatmap_v = new QLabel(groupBox_julia_heatmap);
        label_heatmap_v->setObjectName(QString::fromUtf8("label_heatmap_v"));

        layout_heatmap_controls->addWidget(label_heatmap_v);

        comboBox_heatmap_axis_v = new QComboBox(groupBox_julia_heatmap);
        comboBox_heatmap_axis_v->addItem(QString());
        comboBox_heatmap_axis_v->addItem(QString());
        comboBox_heatmap_axis_v->addItem(QString());
        comboBox_heatmap_axis_v->setObjectName(QString::fromUtf8("comboBox_heatmap_axis_v"));

        layout_heatmap_controls->addWidget(comboBox_heatmap_axis_v);

        label_heatmap_res = new QLabel(groupBox_julia_heatmap);
        label_heatmap_res->setObjectName(QString::fromUtf8("label_heatmap_res"));

        layout_heatmap_controls->addWidget(label_heatmap_res);

        comboBox_heatmap_resolution = new QComboBox(groupBox_julia_heatmap);
        comboBox_heatmap_resolution->addItem(QString());
        comboBox_heatmap_resolution->addItem(QString());
        comboBox_heatmap_resolution->addItem(QString());
        comboBox_heatmap_resolution->addItem(QString());
        comboBox_heatmap_resolution->setObjectName(QString::fromUtf8("comboBox_heatmap_resolution"));

        layout_heatmap_controls->addWidget(comboBox_heatmap_resolution);


        layout_julia_heatmap->addLayout(layout_heatmap_controls);

        layout_heatmap_scheme = new QHBoxLayout();
        layout_heatmap_scheme->setSpacing(3);
        layout_heatmap_scheme->setObjectName(QString::fromUtf8("layout_heatmap_scheme"));
        label_heatmap_scheme = new QLabel(groupBox_julia_heatmap);
        label_heatmap_scheme->setObjectName(QString::fromUtf8("label_heatmap_scheme"));

        layout_heatmap_scheme->addWidget(label_heatmap_scheme);

        comboBox_heatmap_scheme = new QComboBox(groupBox_julia_heatmap);
        comboBox_heatmap_scheme->addItem(QString());
        comboBox_heatmap_scheme->addItem(QString());
        comboBox_heatmap_scheme->addItem(QString());
        comboBox_heatmap_scheme->addItem(QString());
        comboBox_heatmap_scheme->addItem(QString());
        comboBox_heatmap_scheme->setObjectName(QString::fromUtf8("comboBox_heatmap_scheme"));

        layout_heatmap_scheme->addWidget(comboBox_heatmap_scheme);

        heatmap_spacer_1 = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        layout_heatmap_scheme->addItem(heatmap_spacer_1);


        layout_julia_heatmap->addLayout(layout_heatmap_scheme);

        widget_julia_heatmap = new cJuliaHeatmapWidget(groupBox_julia_heatmap);
        widget_julia_heatmap->setObjectName(QString::fromUtf8("widget_julia_heatmap"));
        widget_julia_heatmap->setMinimumSize(QSize(200, 200));

        layout_julia_heatmap->addWidget(widget_julia_heatmap);

        layout_heatmap_scan = new QHBoxLayout();
        layout_heatmap_scan->setSpacing(3);
        layout_heatmap_scan->setObjectName(QString::fromUtf8("layout_heatmap_scan"));
        pushButton_heatmap_scan = new QPushButton(groupBox_julia_heatmap);
        pushButton_heatmap_scan->setObjectName(QString::fromUtf8("pushButton_heatmap_scan"));

        layout_heatmap_scan->addWidget(pushButton_heatmap_scan);

        pushButton_heatmap_stop = new QPushButton(groupBox_julia_heatmap);
        pushButton_heatmap_stop->setObjectName(QString::fromUtf8("pushButton_heatmap_stop"));

        layout_heatmap_scan->addWidget(pushButton_heatmap_stop);

        pushButton_heatmap_clear = new QPushButton(groupBox_julia_heatmap);
        pushButton_heatmap_clear->setObjectName(QString::fromUtf8("pushButton_heatmap_clear"));

        layout_heatmap_scan->addWidget(pushButton_heatmap_clear);

        progressBar_heatmap = new QProgressBar(groupBox_julia_heatmap);
        progressBar_heatmap->setObjectName(QString::fromUtf8("progressBar_heatmap"));
        progressBar_heatmap->setValue(0);
        progressBar_heatmap->setTextVisible(true);

        layout_heatmap_scan->addWidget(progressBar_heatmap);


        layout_julia_heatmap->addLayout(layout_heatmap_scan);

        label_heatmap_info = new QLabel(groupBox_julia_heatmap);
        label_heatmap_info->setObjectName(QString::fromUtf8("label_heatmap_info"));
        label_heatmap_info->setAlignment(Qt::AlignCenter);

        layout_julia_heatmap->addWidget(label_heatmap_info);


        verticalLayout_48->addWidget(groupBox_julia_heatmap);

        groupBox_drone_explorer = new QGroupBox(groupCheck_julia_mode);
        groupBox_drone_explorer->setObjectName(QString::fromUtf8("groupBox_drone_explorer"));
        layout_drone_explorer = new QVBoxLayout(groupBox_drone_explorer);
        layout_drone_explorer->setSpacing(3);
        layout_drone_explorer->setObjectName(QString::fromUtf8("layout_drone_explorer"));
        layout_drone_explorer->setContentsMargins(3, 3, 3, 3);
        layout_drone_controls = new QHBoxLayout();
        layout_drone_controls->setSpacing(3);
        layout_drone_controls->setObjectName(QString::fromUtf8("layout_drone_controls"));
        label_drone_strategy = new QLabel(groupBox_drone_explorer);
        label_drone_strategy->setObjectName(QString::fromUtf8("label_drone_strategy"));

        layout_drone_controls->addWidget(label_drone_strategy);

        comboBox_drone_strategy = new QComboBox(groupBox_drone_explorer);
        comboBox_drone_strategy->addItem(QString());
        comboBox_drone_strategy->addItem(QString());
        comboBox_drone_strategy->addItem(QString());
        comboBox_drone_strategy->setObjectName(QString::fromUtf8("comboBox_drone_strategy"));

        layout_drone_controls->addWidget(comboBox_drone_strategy);

        label_drone_speed = new QLabel(groupBox_drone_explorer);
        label_drone_speed->setObjectName(QString::fromUtf8("label_drone_speed"));

        layout_drone_controls->addWidget(label_drone_speed);

        jslider_drone_speed = new QSlider(groupBox_drone_explorer);
        jslider_drone_speed->setObjectName(QString::fromUtf8("jslider_drone_speed"));
        jslider_drone_speed->setOrientation(Qt::Horizontal);
        jslider_drone_speed->setMinimum(1);
        jslider_drone_speed->setMaximum(50);
        jslider_drone_speed->setValue(10);

        layout_drone_controls->addWidget(jslider_drone_speed);


        layout_drone_explorer->addLayout(layout_drone_controls);

        widget_drone_explorer = new cDroneExplorerWidget(groupBox_drone_explorer);
        widget_drone_explorer->setObjectName(QString::fromUtf8("widget_drone_explorer"));
        widget_drone_explorer->setMinimumSize(QSize(280, 220));

        layout_drone_explorer->addWidget(widget_drone_explorer);

        layout_drone_fleet = new QHBoxLayout();
        layout_drone_fleet->setSpacing(3);
        layout_drone_fleet->setObjectName(QString::fromUtf8("layout_drone_fleet"));
        pushButton_drone_launch = new QPushButton(groupBox_drone_explorer);
        pushButton_drone_launch->setObjectName(QString::fromUtf8("pushButton_drone_launch"));

        layout_drone_fleet->addWidget(pushButton_drone_launch);

        pushButton_drone_stop = new QPushButton(groupBox_drone_explorer);
        pushButton_drone_stop->setObjectName(QString::fromUtf8("pushButton_drone_stop"));

        layout_drone_fleet->addWidget(pushButton_drone_stop);

        pushButton_drone_reset = new QPushButton(groupBox_drone_explorer);
        pushButton_drone_reset->setObjectName(QString::fromUtf8("pushButton_drone_reset"));

        layout_drone_fleet->addWidget(pushButton_drone_reset);


        layout_drone_explorer->addLayout(layout_drone_fleet);

        label_drone_status = new QLabel(groupBox_drone_explorer);
        label_drone_status->setObjectName(QString::fromUtf8("label_drone_status"));
        label_drone_status->setAlignment(Qt::AlignCenter);

        layout_drone_explorer->addWidget(label_drone_status);


        verticalLayout_48->addWidget(groupBox_drone_explorer);

        groupBox_julia_preview = new MyGroupBox(groupCheck_julia_mode);
        groupBox_julia_preview->setObjectName(QString::fromUtf8("groupBox_julia_preview"));
        groupBox_julia_preview->setCheckable(true);
        verticalLayout_6 = new QVBoxLayout(groupBox_julia_preview);
        verticalLayout_6->setSpacing(2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(2, 2, 2, 2);
        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(2);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setContentsMargins(-1, 0, -1, -1);
        logedit_julia_preview_distance = new MyLineEdit(groupBox_julia_preview);
        logedit_julia_preview_distance->setObjectName(QString::fromUtf8("logedit_julia_preview_distance"));

        gridLayout_7->addWidget(logedit_julia_preview_distance, 0, 1, 1, 1);

        label_133 = new QLabel(groupBox_julia_preview);
        label_133->setObjectName(QString::fromUtf8("label_133"));

        gridLayout_7->addWidget(label_133, 0, 0, 1, 1);


        verticalLayout_6->addLayout(gridLayout_7);

        previewwidget_julia = new cThumbnailWidget(groupBox_julia_preview);
        previewwidget_julia->setObjectName(QString::fromUtf8("previewwidget_julia"));
        previewwidget_julia->setMinimumSize(QSize(256, 256));

        verticalLayout_6->addWidget(previewwidget_julia);


        verticalLayout_48->addWidget(groupBox_julia_preview);


        verticalLayout_68->addWidget(groupCheck_julia_mode);

        groupBox_beauty_finder = new QGroupBox(scrollAreaWidgetContents_12);
        groupBox_beauty_finder->setObjectName(QString::fromUtf8("groupBox_beauty_finder"));
        layout_beauty_finder = new QVBoxLayout(groupBox_beauty_finder);
        layout_beauty_finder->setSpacing(3);
        layout_beauty_finder->setObjectName(QString::fromUtf8("layout_beauty_finder"));
        layout_beauty_finder->setContentsMargins(3, 3, 3, 3);
        layout_beauty_range = new QHBoxLayout();
        layout_beauty_range->setSpacing(3);
        layout_beauty_range->setObjectName(QString::fromUtf8("layout_beauty_range"));
        label_beauty_range = new QLabel(groupBox_beauty_finder);
        label_beauty_range->setObjectName(QString::fromUtf8("label_beauty_range"));

        layout_beauty_range->addWidget(label_beauty_range);

        spinBox_beauty_range = new QDoubleSpinBox(groupBox_beauty_finder);
        spinBox_beauty_range->setObjectName(QString::fromUtf8("spinBox_beauty_range"));
        spinBox_beauty_range->setMinimum(0.001000000000000);
        spinBox_beauty_range->setMaximum(10.000000000000000);
        spinBox_beauty_range->setValue(2.000000000000000);
        spinBox_beauty_range->setDecimals(3);
        spinBox_beauty_range->setSingleStep(0.010000000000000);

        layout_beauty_range->addWidget(spinBox_beauty_range);

        pushButton_beauty_find = new QPushButton(groupBox_beauty_finder);
        pushButton_beauty_find->setObjectName(QString::fromUtf8("pushButton_beauty_find"));

        layout_beauty_range->addWidget(pushButton_beauty_find);

        pushButton_beauty_next = new QPushButton(groupBox_beauty_finder);
        pushButton_beauty_next->setObjectName(QString::fromUtf8("pushButton_beauty_next"));
        pushButton_beauty_next->setEnabled(false);

        layout_beauty_range->addWidget(pushButton_beauty_next);


        layout_beauty_finder->addLayout(layout_beauty_range);

        layout_beauty_iter = new QHBoxLayout();
        layout_beauty_iter->setSpacing(3);
        layout_beauty_iter->setObjectName(QString::fromUtf8("layout_beauty_iter"));
        label25 = new QLabel(groupBox_beauty_finder);
        label25->setObjectName(QString::fromUtf8("label25"));

        layout_beauty_iter->addWidget(label25);

        spinBox_beauty_iter_start = new QSpinBox(groupBox_beauty_finder);
        spinBox_beauty_iter_start->setObjectName(QString::fromUtf8("spinBox_beauty_iter_start"));
        spinBox_beauty_iter_start->setMinimum(0);
        spinBox_beauty_iter_start->setMaximum(9999);
        spinBox_beauty_iter_start->setValue(0);

        layout_beauty_iter->addWidget(spinBox_beauty_iter_start);

        label26 = new QLabel(groupBox_beauty_finder);
        label26->setObjectName(QString::fromUtf8("label26"));
        label26->setAlignment(Qt::AlignCenter);

        layout_beauty_iter->addWidget(label26);

        spinBox_beauty_iter_stop = new QSpinBox(groupBox_beauty_finder);
        spinBox_beauty_iter_stop->setObjectName(QString::fromUtf8("spinBox_beauty_iter_stop"));
        spinBox_beauty_iter_stop->setMinimum(1);
        spinBox_beauty_iter_stop->setMaximum(9999);
        spinBox_beauty_iter_stop->setValue(64);

        layout_beauty_iter->addWidget(spinBox_beauty_iter_stop);

        checkBox_beauty_auto = new QCheckBox(groupBox_beauty_finder);
        checkBox_beauty_auto->setObjectName(QString::fromUtf8("checkBox_beauty_auto"));
        checkBox_beauty_auto->setChecked(false);

        layout_beauty_iter->addWidget(checkBox_beauty_auto);


        layout_beauty_finder->addLayout(layout_beauty_iter);

        layout_beauty_weight = new QHBoxLayout();
        layout_beauty_weight->setSpacing(3);
        layout_beauty_weight->setObjectName(QString::fromUtf8("layout_beauty_weight"));
        label27 = new QLabel(groupBox_beauty_finder);
        label27->setObjectName(QString::fromUtf8("label27"));

        layout_beauty_weight->addWidget(label27);

        label28 = new QLabel(groupBox_beauty_finder);
        label28->setObjectName(QString::fromUtf8("label28"));
        label28->setAlignment(Qt::AlignCenter);

        layout_beauty_weight->addWidget(label28);

        spinBox_beauty_weight_x = new QDoubleSpinBox(groupBox_beauty_finder);
        spinBox_beauty_weight_x->setObjectName(QString::fromUtf8("spinBox_beauty_weight_x"));
        spinBox_beauty_weight_x->setMinimum(-10.000000000000000);
        spinBox_beauty_weight_x->setMaximum(10.000000000000000);
        spinBox_beauty_weight_x->setValue(1.000000000000000);
        spinBox_beauty_weight_x->setDecimals(3);
        spinBox_beauty_weight_x->setSingleStep(0.100000000000000);

        layout_beauty_weight->addWidget(spinBox_beauty_weight_x);

        label29 = new QLabel(groupBox_beauty_finder);
        label29->setObjectName(QString::fromUtf8("label29"));
        label29->setAlignment(Qt::AlignCenter);

        layout_beauty_weight->addWidget(label29);

        spinBox_beauty_weight_y = new QDoubleSpinBox(groupBox_beauty_finder);
        spinBox_beauty_weight_y->setObjectName(QString::fromUtf8("spinBox_beauty_weight_y"));
        spinBox_beauty_weight_y->setMinimum(-10.000000000000000);
        spinBox_beauty_weight_y->setMaximum(10.000000000000000);
        spinBox_beauty_weight_y->setValue(1.000000000000000);
        spinBox_beauty_weight_y->setDecimals(3);
        spinBox_beauty_weight_y->setSingleStep(0.100000000000000);

        layout_beauty_weight->addWidget(spinBox_beauty_weight_y);

        label30 = new QLabel(groupBox_beauty_finder);
        label30->setObjectName(QString::fromUtf8("label30"));
        label30->setAlignment(Qt::AlignCenter);

        layout_beauty_weight->addWidget(label30);

        spinBox_beauty_weight_z = new QDoubleSpinBox(groupBox_beauty_finder);
        spinBox_beauty_weight_z->setObjectName(QString::fromUtf8("spinBox_beauty_weight_z"));
        spinBox_beauty_weight_z->setMinimum(-10.000000000000000);
        spinBox_beauty_weight_z->setMaximum(10.000000000000000);
        spinBox_beauty_weight_z->setValue(1.000000000000000);
        spinBox_beauty_weight_z->setDecimals(3);
        spinBox_beauty_weight_z->setSingleStep(0.100000000000000);

        layout_beauty_weight->addWidget(spinBox_beauty_weight_z);


        layout_beauty_finder->addLayout(layout_beauty_weight);

        progressBar_beauty = new QProgressBar(groupBox_beauty_finder);
        progressBar_beauty->setObjectName(QString::fromUtf8("progressBar_beauty"));
        progressBar_beauty->setValue(0);
        progressBar_beauty->setTextVisible(true);

        layout_beauty_finder->addWidget(progressBar_beauty);

        label_beauty_result = new QLabel(groupBox_beauty_finder);
        label_beauty_result->setObjectName(QString::fromUtf8("label_beauty_result"));
        label_beauty_result->setAlignment(Qt::AlignCenter);
        label_beauty_result->setWordWrap(true);

        layout_beauty_finder->addWidget(label_beauty_result);


        verticalLayout_68->addWidget(groupBox_beauty_finder);

        groupBox_2 = new QGroupBox(scrollAreaWidgetContents_12);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(2, 2, 2, 2);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, -1, -1);
        spinbox3_fractal_constant_factor_y = new MyDoubleSpinBox(groupBox_2);
        spinbox3_fractal_constant_factor_y->setObjectName(QString::fromUtf8("spinbox3_fractal_constant_factor_y"));
        sizePolicy3.setHeightForWidth(spinbox3_fractal_constant_factor_y->sizePolicy().hasHeightForWidth());
        spinbox3_fractal_constant_factor_y->setSizePolicy(sizePolicy3);
        spinbox3_fractal_constant_factor_y->setDecimals(6);
        spinbox3_fractal_constant_factor_y->setMinimum(-1000.000000000000000);
        spinbox3_fractal_constant_factor_y->setMaximum(1000.000000000000000);
        spinbox3_fractal_constant_factor_y->setSingleStep(0.100000000000000);

        gridLayout_3->addWidget(spinbox3_fractal_constant_factor_y, 2, 2, 1, 1);

        label_347 = new QLabel(groupBox_2);
        label_347->setObjectName(QString::fromUtf8("label_347"));
        QSizePolicy sizePolicy4(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_347->sizePolicy().hasHeightForWidth());
        label_347->setSizePolicy(sizePolicy4);
        label_347->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_347, 2, 1, 1, 1);

        label_346 = new QLabel(groupBox_2);
        label_346->setObjectName(QString::fromUtf8("label_346"));
        sizePolicy4.setHeightForWidth(label_346->sizePolicy().hasHeightForWidth());
        label_346->setSizePolicy(sizePolicy4);
        label_346->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_346, 1, 1, 1, 1);

        label_172 = new QLabel(groupBox_2);
        label_172->setObjectName(QString::fromUtf8("label_172"));

        gridLayout_3->addWidget(label_172, 0, 0, 1, 1);

        label_135 = new QLabel(groupBox_2);
        label_135->setObjectName(QString::fromUtf8("label_135"));

        gridLayout_3->addWidget(label_135, 1, 0, 3, 1);

        spinbox3_fractal_constant_factor_x = new MyDoubleSpinBox(groupBox_2);
        spinbox3_fractal_constant_factor_x->setObjectName(QString::fromUtf8("spinbox3_fractal_constant_factor_x"));
        sizePolicy3.setHeightForWidth(spinbox3_fractal_constant_factor_x->sizePolicy().hasHeightForWidth());
        spinbox3_fractal_constant_factor_x->setSizePolicy(sizePolicy3);
        spinbox3_fractal_constant_factor_x->setDecimals(6);
        spinbox3_fractal_constant_factor_x->setMinimum(-1000.000000000000000);
        spinbox3_fractal_constant_factor_x->setMaximum(1000.000000000000000);
        spinbox3_fractal_constant_factor_x->setSingleStep(0.100000000000000);

        gridLayout_3->addWidget(spinbox3_fractal_constant_factor_x, 1, 2, 1, 1);

        label_348 = new QLabel(groupBox_2);
        label_348->setObjectName(QString::fromUtf8("label_348"));
        sizePolicy4.setHeightForWidth(label_348->sizePolicy().hasHeightForWidth());
        label_348->setSizePolicy(sizePolicy4);
        label_348->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_348, 3, 1, 1, 1);

        spinbox3_fractal_constant_factor_z = new MyDoubleSpinBox(groupBox_2);
        spinbox3_fractal_constant_factor_z->setObjectName(QString::fromUtf8("spinbox3_fractal_constant_factor_z"));
        sizePolicy3.setHeightForWidth(spinbox3_fractal_constant_factor_z->sizePolicy().hasHeightForWidth());
        spinbox3_fractal_constant_factor_z->setSizePolicy(sizePolicy3);
        spinbox3_fractal_constant_factor_z->setDecimals(6);
        spinbox3_fractal_constant_factor_z->setMinimum(-1000.000000000000000);
        spinbox3_fractal_constant_factor_z->setMaximum(1000.000000000000000);
        spinbox3_fractal_constant_factor_z->setSingleStep(0.100000000000000);

        gridLayout_3->addWidget(spinbox3_fractal_constant_factor_z, 3, 2, 1, 1);

        spinbox_initial_waxis = new MyDoubleSpinBox(groupBox_2);
        spinbox_initial_waxis->setObjectName(QString::fromUtf8("spinbox_initial_waxis"));
        sizePolicy3.setHeightForWidth(spinbox_initial_waxis->sizePolicy().hasHeightForWidth());
        spinbox_initial_waxis->setSizePolicy(sizePolicy3);
        spinbox_initial_waxis->setDecimals(6);
        spinbox_initial_waxis->setMinimum(-1000.000000000000000);
        spinbox_initial_waxis->setMaximum(1000.000000000000000);
        spinbox_initial_waxis->setSingleStep(0.100000000000000);

        gridLayout_3->addWidget(spinbox_initial_waxis, 0, 2, 1, 1);


        verticalLayout_2->addLayout(gridLayout_3);


        verticalLayout_68->addWidget(groupBox_2);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_68->addItem(verticalSpacer_7);

        scrollArea_11->setWidget(scrollAreaWidgetContents_12);

        verticalLayout_47->addWidget(scrollArea_11);


        retranslateUi(cFractalCommonTab);

        comboBox_heatmap_axis_v->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(cFractalCommonTab);
    } // setupUi

    void retranslateUi(QWidget *cFractalCommonTab)
    {
        pushButton_local_load_5->setText(QCoreApplication::translate("cFractalCommonTab", "Load", nullptr));
        pushButton_local_save_5->setText(QCoreApplication::translate("cFractalCommonTab", "Save", nullptr));
        pushButton_local_reset_5->setText(QCoreApplication::translate("cFractalCommonTab", "Reset", nullptr));
        pushButton_local_randomize_2->setText(QCoreApplication::translate("cFractalCommonTab", "Randomize", nullptr));
        groupBox_material_fractal->setTitle(QCoreApplication::translate("cFractalCommonTab", "Material for fractal", nullptr));
#if QT_CONFIG(tooltip)
        materialselector_formula_material_id->setToolTip(QCoreApplication::translate("cFractalCommonTab", "<html><head/><body> <p>Assign a material to the current fractal/formula.</p> <p>The material defines the surface appearance during rendering (color, shading, reflectance, roughness, transparency, textures, emission, etc.).</p> <p>How to use: - Click the material thumbnail/name to open the Material manager. - Choose an existing material or edit it; the label shows the material name and ID [matN].</p> <p>Scope: - Applies to this fractal only; in hybrid/boolean setups each fractal can have its own material and the final look depends on how they are combined.</p> </body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox->setTitle(QCoreApplication::translate("cFractalCommonTab", "Fractal positioning", nullptr));
        label_139->setText(QCoreApplication::translate("cFractalCommonTab", "z:", nullptr));
        label_140->setText(QCoreApplication::translate("cFractalCommonTab", "x:", nullptr));
        label_46->setText(QCoreApplication::translate("cFractalCommonTab", "X-axis rotation:", nullptr));
        label_138->setText(QCoreApplication::translate("cFractalCommonTab", "Fractal position:", nullptr));
        label_137->setText(QCoreApplication::translate("cFractalCommonTab", "y:", nullptr));
        spinboxd3_fractal_rotation_x->setPrefix(QString());
        spinboxd3_fractal_rotation_x->setSuffix(QString());
        spinboxd3_fractal_rotation_y->setPrefix(QString());
        spinboxd3_fractal_rotation_y->setSuffix(QString());
        spinboxd3_fractal_rotation_z->setPrefix(QString());
        spinboxd3_fractal_rotation_z->setSuffix(QString());
        label_48->setText(QCoreApplication::translate("cFractalCommonTab", "Z-axis rotation:", nullptr));
        label_47->setText(QCoreApplication::translate("cFractalCommonTab", "Y-axis rotation:", nullptr));
        label_repeat_x_2->setText(QCoreApplication::translate("cFractalCommonTab", "x:", nullptr));
        label_repeat_y_2->setText(QCoreApplication::translate("cFractalCommonTab", "y:", nullptr));
        label_repeat_z_2->setText(QCoreApplication::translate("cFractalCommonTab", "z:", nullptr));
        label_145->setText(QCoreApplication::translate("cFractalCommonTab", "Repeat", nullptr));
        groupBox_iter_ranges->setTitle(QCoreApplication::translate("cFractalCommonTab", "Per-axis iteration ranges", nullptr));
        label->setText(QString());
        label1->setText(QString());
        label2->setText(QCoreApplication::translate("cFractalCommonTab", "Start", nullptr));
        label3->setText(QCoreApplication::translate("cFractalCommonTab", "Stop", nullptr));
        label4->setText(QCoreApplication::translate("cFractalCommonTab", "Position", nullptr));
        label4->setStyleSheet(QCoreApplication::translate("cFractalCommonTab", "font-weight:bold;", nullptr));
        label5->setText(QCoreApplication::translate("cFractalCommonTab", "x:", nullptr));
        label6->setText(QCoreApplication::translate("cFractalCommonTab", "y:", nullptr));
        label7->setText(QCoreApplication::translate("cFractalCommonTab", "z:", nullptr));
        label8->setText(QCoreApplication::translate("cFractalCommonTab", "Rotation", nullptr));
        label8->setStyleSheet(QCoreApplication::translate("cFractalCommonTab", "font-weight:bold;", nullptr));
        label9->setText(QCoreApplication::translate("cFractalCommonTab", "x:", nullptr));
        label10->setText(QCoreApplication::translate("cFractalCommonTab", "y:", nullptr));
        label11->setText(QCoreApplication::translate("cFractalCommonTab", "z:", nullptr));
        label12->setText(QCoreApplication::translate("cFractalCommonTab", "Repeat", nullptr));
        label12->setStyleSheet(QCoreApplication::translate("cFractalCommonTab", "font-weight:bold;", nullptr));
        label13->setText(QCoreApplication::translate("cFractalCommonTab", "x:", nullptr));
        label14->setText(QCoreApplication::translate("cFractalCommonTab", "y:", nullptr));
        label15->setText(QCoreApplication::translate("cFractalCommonTab", "z:", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_julia_mode->setToolTip(QCoreApplication::translate("cFractalCommonTab", "<html><head/><body><p>Enables calculation of fractal in the same way as Julia Set.</p><p>When it's enabled then:<br/>z<span style=\" vertical-align:sub;\">0</span> = p<br/>z<span style=\" vertical-align:sub;\">n+1</span> = f(z<span style=\" vertical-align:sub;\">n</span>) + c</p><p>where:<br/>p - coordinates of point<br/>c - Julia constant</p><p>to compare, regular fractals are calculated in following way:<br/>z<span style=\" vertical-align:sub;\">0</span> = p<br/>z<span style=\" vertical-align:sub;\">n+1</span> = f(z<span style=\" vertical-align:sub;\">n</span>) + p</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_julia_mode->setTitle(QCoreApplication::translate("cFractalCommonTab", "J&ulia mode", nullptr));
        label_116->setText(QCoreApplication::translate("cFractalCommonTab", "y:", nullptr));
        label_113->setText(QCoreApplication::translate("cFractalCommonTab", "Julia constant (c):", nullptr));
        label_120->setText(QCoreApplication::translate("cFractalCommonTab", "z:", nullptr));
        label_115->setText(QCoreApplication::translate("cFractalCommonTab", "x:", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_get_julia_constant->setToolTip(QCoreApplication::translate("cFractalCommonTab", "<html><head/><body><p>Pick Julia constant (C) from the rendered image.</p><p>When Julia mode is disabled, select point of fractal which has interesting features. It assigns its coordinates to the Julia constant fields (C.x, C.y, C.z).</p><p>After enabling Julia mode, entire fractal will have shapes similar to previously selected place.</p><p>Notes: - Works with formulas that support Julia mode; enable Julia mode to see the effect immediately. - The mouse function switches to \342\200\234Get Julia constant\342\200\235; change the mouse function to exit picking.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_get_julia_constant->setText(QCoreApplication::translate("cFractalCommonTab", "Get Julia constant by mouse pointer", nullptr));
        groupBox_julia_fine_tune->setTitle(QCoreApplication::translate("cFractalCommonTab", "Julia C Fine Tune (per-component)", nullptr));
        label16->setText(QCoreApplication::translate("cFractalCommonTab", "Start iter", nullptr));
        label17->setText(QCoreApplication::translate("cFractalCommonTab", "Stop iter", nullptr));
        label18->setText(QCoreApplication::translate("cFractalCommonTab", "Weight", nullptr));
        label19->setText(QCoreApplication::translate("cFractalCommonTab", "Julia C X", nullptr));
        label20->setText(QCoreApplication::translate("cFractalCommonTab", "Julia C Y", nullptr));
        label21->setText(QCoreApplication::translate("cFractalCommonTab", "Julia C Z", nullptr));
        label22->setText(QCoreApplication::translate("cFractalCommonTab", "Const C X", nullptr));
        label23->setText(QCoreApplication::translate("cFractalCommonTab", "Const C Y", nullptr));
        label24->setText(QCoreApplication::translate("cFractalCommonTab", "Const C Z", nullptr));
        groupBox_julia_explorer->setTitle(QCoreApplication::translate("cFractalCommonTab", "Julia Explorer", nullptr));
        label_julia_slider_cx->setText(QCoreApplication::translate("cFractalCommonTab", "c.x", nullptr));
#if QT_CONFIG(tooltip)
        jslider_julia_cx->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Drag to adjust Julia c.x", nullptr));
#endif // QT_CONFIG(tooltip)
        label_julia_cx_value->setText(QCoreApplication::translate("cFractalCommonTab", "0.000", nullptr));
        label_julia_slider_cy->setText(QCoreApplication::translate("cFractalCommonTab", "c.y", nullptr));
#if QT_CONFIG(tooltip)
        jslider_julia_cy->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Drag to adjust Julia c.y", nullptr));
#endif // QT_CONFIG(tooltip)
        label_julia_cy_value->setText(QCoreApplication::translate("cFractalCommonTab", "0.000", nullptr));
        label_julia_slider_cz->setText(QCoreApplication::translate("cFractalCommonTab", "c.z", nullptr));
#if QT_CONFIG(tooltip)
        jslider_julia_cz->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Drag to adjust Julia c.z", nullptr));
#endif // QT_CONFIG(tooltip)
        label_julia_cz_value->setText(QCoreApplication::translate("cFractalCommonTab", "0.000", nullptr));
        label_julia_range->setText(QCoreApplication::translate("cFractalCommonTab", "Range", nullptr));
        comboBox_julia_range->setItemText(0, QCoreApplication::translate("cFractalCommonTab", "\302\2610.5", nullptr));
        comboBox_julia_range->setItemText(1, QCoreApplication::translate("cFractalCommonTab", "\302\2611.0", nullptr));
        comboBox_julia_range->setItemText(2, QCoreApplication::translate("cFractalCommonTab", "\302\2612.0", nullptr));
        comboBox_julia_range->setItemText(3, QCoreApplication::translate("cFractalCommonTab", "\302\2615.0", nullptr));
        comboBox_julia_range->setItemText(4, QCoreApplication::translate("cFractalCommonTab", "\302\26110.0", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_julia_range->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Range of Julia c sliders", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_julia_copy->setText(QCoreApplication::translate("cFractalCommonTab", "Copy c", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_julia_copy->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Copy Julia constant to clipboard", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_julia_paste->setText(QCoreApplication::translate("cFractalCommonTab", "Paste c", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_julia_paste->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Paste Julia constant from clipboard", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_julia_random->setText(QCoreApplication::translate("cFractalCommonTab", "Random", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_julia_random->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Generate random Julia constant", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_julia_zero->setText(QCoreApplication::translate("cFractalCommonTab", "Zero", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_julia_zero->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Reset Julia constant to (0, 0, 0)", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_julia_presets->setTitle(QCoreApplication::translate("cFractalCommonTab", "Presets", nullptr));
        pushButton_julia_preset_1->setText(QCoreApplication::translate("cFractalCommonTab", "Classic", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_julia_preset_1->setToolTip(QCoreApplication::translate("cFractalCommonTab", "c = (0.285, 0.01, 0.0)", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_julia_preset_2->setText(QCoreApplication::translate("cFractalCommonTab", "Dendrite", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_julia_preset_2->setToolTip(QCoreApplication::translate("cFractalCommonTab", "c = (0.0, 1.0, 0.0)", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_julia_preset_3->setText(QCoreApplication::translate("cFractalCommonTab", "Spiral", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_julia_preset_3->setToolTip(QCoreApplication::translate("cFractalCommonTab", "c = (-0.4, 0.6, 0.0)", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_julia_preset_4->setText(QCoreApplication::translate("cFractalCommonTab", "Siegel", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_julia_preset_4->setToolTip(QCoreApplication::translate("cFractalCommonTab", "c = (-0.391, -0.587, 0.0)", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_julia_preset_5->setText(QCoreApplication::translate("cFractalCommonTab", "Rabbit", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_julia_preset_5->setToolTip(QCoreApplication::translate("cFractalCommonTab", "c = (-0.123, 0.745, 0.0)", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_julia_preset_6->setText(QCoreApplication::translate("cFractalCommonTab", "Starfish", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_julia_preset_6->setToolTip(QCoreApplication::translate("cFractalCommonTab", "c = (-0.75, 0.15, 0.2)", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_julia_preset_7->setText(QCoreApplication::translate("cFractalCommonTab", "Galaxy", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_julia_preset_7->setToolTip(QCoreApplication::translate("cFractalCommonTab", "c = (0.355, 0.355, 0.355)", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_julia_preset_8->setText(QCoreApplication::translate("cFractalCommonTab", "Dragon", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_julia_preset_8->setToolTip(QCoreApplication::translate("cFractalCommonTab", "c = (0.36, 0.1, -0.3)", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_julia_preset_9->setText(QCoreApplication::translate("cFractalCommonTab", "Flower", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_julia_preset_9->setToolTip(QCoreApplication::translate("cFractalCommonTab", "c = (-0.5, 0.0, 0.5)", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_julia_sweep->setTitle(QCoreApplication::translate("cFractalCommonTab", "Animated Sweep", nullptr));
        label_sweep_axis->setText(QCoreApplication::translate("cFractalCommonTab", "Sweep axis:", nullptr));
        comboBox_julia_sweep_axis->setItemText(0, QCoreApplication::translate("cFractalCommonTab", "c.x", nullptr));
        comboBox_julia_sweep_axis->setItemText(1, QCoreApplication::translate("cFractalCommonTab", "c.y", nullptr));
        comboBox_julia_sweep_axis->setItemText(2, QCoreApplication::translate("cFractalCommonTab", "c.z", nullptr));
        comboBox_julia_sweep_axis->setItemText(3, QCoreApplication::translate("cFractalCommonTab", "All (spiral)", nullptr));

        label_sweep_from->setText(QCoreApplication::translate("cFractalCommonTab", "From:", nullptr));
        label_sweep_to->setText(QCoreApplication::translate("cFractalCommonTab", "To:", nullptr));
        pushButton_julia_sweep_start->setText(QCoreApplication::translate("cFractalCommonTab", "Sweep", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_julia_sweep_start->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Animate through Julia c-space", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_julia_sweep_stop->setText(QCoreApplication::translate("cFractalCommonTab", "Stop", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_julia_sweep_stop->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Stop the current sweep", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinBox_julia_sweep_steps->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Number of steps in sweep", nullptr));
#endif // QT_CONFIG(tooltip)
        spinBox_julia_sweep_steps->setSuffix(QCoreApplication::translate("cFractalCommonTab", " steps", nullptr));
        groupBox_julia_history->setTitle(QCoreApplication::translate("cFractalCommonTab", "History", nullptr));
#if QT_CONFIG(tooltip)
        listWidget_julia_history->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Recent Julia constants \342\200\224 double-click to apply", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_julia_history_save->setText(QCoreApplication::translate("cFractalCommonTab", "Save to Bookmarks", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_julia_history_save->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Save selected Julia constant as bookmark", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_julia_history_clear->setText(QCoreApplication::translate("cFractalCommonTab", "Clear", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_julia_history_clear->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Clear Julia history", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_julia_heatmap->setTitle(QCoreApplication::translate("cFractalCommonTab", "Julia Heatmap", nullptr));
        label_heatmap_h->setText(QCoreApplication::translate("cFractalCommonTab", "H:", nullptr));
        comboBox_heatmap_axis_h->setItemText(0, QCoreApplication::translate("cFractalCommonTab", "c.x", nullptr));
        comboBox_heatmap_axis_h->setItemText(1, QCoreApplication::translate("cFractalCommonTab", "c.y", nullptr));
        comboBox_heatmap_axis_h->setItemText(2, QCoreApplication::translate("cFractalCommonTab", "c.z", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_heatmap_axis_h->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Horizontal axis", nullptr));
#endif // QT_CONFIG(tooltip)
        label_heatmap_v->setText(QCoreApplication::translate("cFractalCommonTab", "V:", nullptr));
        comboBox_heatmap_axis_v->setItemText(0, QCoreApplication::translate("cFractalCommonTab", "c.x", nullptr));
        comboBox_heatmap_axis_v->setItemText(1, QCoreApplication::translate("cFractalCommonTab", "c.y", nullptr));
        comboBox_heatmap_axis_v->setItemText(2, QCoreApplication::translate("cFractalCommonTab", "c.z", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_heatmap_axis_v->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Vertical axis", nullptr));
#endif // QT_CONFIG(tooltip)
        label_heatmap_res->setText(QCoreApplication::translate("cFractalCommonTab", "Res:", nullptr));
        comboBox_heatmap_resolution->setItemText(0, QCoreApplication::translate("cFractalCommonTab", "16\303\22716", nullptr));
        comboBox_heatmap_resolution->setItemText(1, QCoreApplication::translate("cFractalCommonTab", "32\303\22732", nullptr));
        comboBox_heatmap_resolution->setItemText(2, QCoreApplication::translate("cFractalCommonTab", "48\303\22748", nullptr));
        comboBox_heatmap_resolution->setItemText(3, QCoreApplication::translate("cFractalCommonTab", "64\303\22764", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_heatmap_resolution->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Grid resolution (cells per axis)", nullptr));
#endif // QT_CONFIG(tooltip)
        label_heatmap_scheme->setText(QCoreApplication::translate("cFractalCommonTab", "Colors:", nullptr));
        comboBox_heatmap_scheme->setItemText(0, QCoreApplication::translate("cFractalCommonTab", "Catppuccin", nullptr));
        comboBox_heatmap_scheme->setItemText(1, QCoreApplication::translate("cFractalCommonTab", "Inferno", nullptr));
        comboBox_heatmap_scheme->setItemText(2, QCoreApplication::translate("cFractalCommonTab", "Plasma", nullptr));
        comboBox_heatmap_scheme->setItemText(3, QCoreApplication::translate("cFractalCommonTab", "Viridis", nullptr));
        comboBox_heatmap_scheme->setItemText(4, QCoreApplication::translate("cFractalCommonTab", "Magma", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_heatmap_scheme->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Heatmap color scheme", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        widget_julia_heatmap->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Julia c-space interest heatmap. Click to jump to that c value. Brighter = more interesting.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_heatmap_scan->setText(QCoreApplication::translate("cFractalCommonTab", "Scan", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_heatmap_scan->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Scan Julia c-space to build the interest heatmap", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_heatmap_stop->setText(QCoreApplication::translate("cFractalCommonTab", "Stop", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_heatmap_stop->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Stop the current scan", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_heatmap_clear->setText(QCoreApplication::translate("cFractalCommonTab", "Clear", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_heatmap_clear->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Clear the heatmap data", nullptr));
#endif // QT_CONFIG(tooltip)
        label_heatmap_info->setText(QCoreApplication::translate("cFractalCommonTab", "Hover over heatmap for details", nullptr));
        groupBox_drone_explorer->setTitle(QCoreApplication::translate("cFractalCommonTab", "Drone Explorer", nullptr));
        label_drone_strategy->setText(QCoreApplication::translate("cFractalCommonTab", "Strategy:", nullptr));
        comboBox_drone_strategy->setItemText(0, QCoreApplication::translate("cFractalCommonTab", "Explore", nullptr));
        comboBox_drone_strategy->setItemText(1, QCoreApplication::translate("cFractalCommonTab", "Exploit", nullptr));
        comboBox_drone_strategy->setItemText(2, QCoreApplication::translate("cFractalCommonTab", "Swarm", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_drone_strategy->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Fleet exploration strategy", nullptr));
#endif // QT_CONFIG(tooltip)
        label_drone_speed->setText(QCoreApplication::translate("cFractalCommonTab", "Speed:", nullptr));
#if QT_CONFIG(tooltip)
        jslider_drone_speed->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Drone fleet speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        widget_drone_explorer->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Autonomous drone fleet exploring Julia c-space. Click to set a target point.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_drone_launch->setText(QCoreApplication::translate("cFractalCommonTab", "Launch Fleet", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_drone_launch->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Launch the drone fleet to explore Julia c-space", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_drone_stop->setText(QCoreApplication::translate("cFractalCommonTab", "Recall", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_drone_stop->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Recall all drones", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_drone_reset->setText(QCoreApplication::translate("cFractalCommonTab", "Reset", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_drone_reset->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Reset drone fleet to initial positions", nullptr));
#endif // QT_CONFIG(tooltip)
        label_drone_status->setText(QCoreApplication::translate("cFractalCommonTab", "Fleet standby \342\200\224 Scan heatmap first, then launch drones", nullptr));
        groupBox_julia_preview->setTitle(QCoreApplication::translate("cFractalCommonTab", "Preview", nullptr));
        label_133->setText(QCoreApplication::translate("cFractalCommonTab", "Julia mode\n"
"preview distance:", nullptr));
        groupBox_beauty_finder->setTitle(QCoreApplication::translate("cFractalCommonTab", "Beauty Finder", nullptr));
        label_beauty_range->setText(QCoreApplication::translate("cFractalCommonTab", "Range:", nullptr));
#if QT_CONFIG(tooltip)
        spinBox_beauty_range->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Search range in c-space (fine: 0.001)", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_beauty_find->setText(QCoreApplication::translate("cFractalCommonTab", "Find Best Julia", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_beauty_find->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Scan c-space to find the best Julia set for the current fractal", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_beauty_find->setStyleSheet(QCoreApplication::translate("cFractalCommonTab", "font-weight: bold;", nullptr));
        pushButton_beauty_next->setText(QCoreApplication::translate("cFractalCommonTab", "Next Best", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_beauty_next->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Apply the next-best result", nullptr));
#endif // QT_CONFIG(tooltip)
        label25->setText(QCoreApplication::translate("cFractalCommonTab", "Scan iter:", nullptr));
#if QT_CONFIG(tooltip)
        spinBox_beauty_iter_start->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Start iteration for beauty scoring", nullptr));
#endif // QT_CONFIG(tooltip)
        label26->setText(QCoreApplication::translate("cFractalCommonTab", "to", nullptr));
#if QT_CONFIG(tooltip)
        spinBox_beauty_iter_stop->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Stop iteration for beauty scoring", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_beauty_auto->setText(QCoreApplication::translate("cFractalCommonTab", "Auto", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_beauty_auto->setToolTip(QCoreApplication::translate("cFractalCommonTab", "Auto-update on Julia slider change", nullptr));
#endif // QT_CONFIG(tooltip)
        label27->setText(QCoreApplication::translate("cFractalCommonTab", "Weight:", nullptr));
        label28->setText(QCoreApplication::translate("cFractalCommonTab", "X", nullptr));
        label29->setText(QCoreApplication::translate("cFractalCommonTab", "Y", nullptr));
        label30->setText(QCoreApplication::translate("cFractalCommonTab", "Z", nullptr));
        label_beauty_result->setText(QCoreApplication::translate("cFractalCommonTab", "Click \"Find Best Julia\" to search", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("cFractalCommonTab", "C constant", nullptr));
#if QT_CONFIG(tooltip)
        spinbox3_fractal_constant_factor_y->setToolTip(QCoreApplication::translate("cFractalCommonTab", "<html><head/><body><p>Multiplies fractal c constant by this value.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox3_fractal_constant_factor_y->setPrefix(QString());
        spinbox3_fractal_constant_factor_y->setSuffix(QString());
        label_347->setText(QCoreApplication::translate("cFractalCommonTab", "y:", nullptr));
        label_346->setText(QCoreApplication::translate("cFractalCommonTab", "x:", nullptr));
        label_172->setText(QCoreApplication::translate("cFractalCommonTab", "Initial w-axis value\n"
"for 4D fractals", nullptr));
        label_135->setText(QCoreApplication::translate("cFractalCommonTab", "Constant multiplier:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox3_fractal_constant_factor_x->setToolTip(QCoreApplication::translate("cFractalCommonTab", "<html><head/><body><p>Multiplies fractal c constant by this value.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox3_fractal_constant_factor_x->setPrefix(QString());
        spinbox3_fractal_constant_factor_x->setSuffix(QString());
        label_348->setText(QCoreApplication::translate("cFractalCommonTab", "z:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox3_fractal_constant_factor_z->setToolTip(QCoreApplication::translate("cFractalCommonTab", "<html><head/><body><p>Multiplies fractal c constant by this value.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox3_fractal_constant_factor_z->setPrefix(QString());
        spinbox3_fractal_constant_factor_z->setSuffix(QString());
#if QT_CONFIG(tooltip)
        spinbox_initial_waxis->setToolTip(QCoreApplication::translate("cFractalCommonTab", "<html><head/><body><p>Multiplies fractal c constant by this value.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_initial_waxis->setPrefix(QString());
        spinbox_initial_waxis->setSuffix(QString());
        (void)cFractalCommonTab;
    } // retranslateUi

};

namespace Ui {
    class cFractalCommonTab: public Ui_cFractalCommonTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRACTAL_COMMON_TAB_H
