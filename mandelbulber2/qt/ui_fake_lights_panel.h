/********************************************************************************
** Form generated from reading UI file 'fake_lights_panel.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FAKE_LIGHTS_PANEL_H
#define UI_FAKE_LIGHTS_PANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "my_check_box.h"
#include "my_color_button.h"
#include "my_combo_box.h"
#include "my_double_spin_box.h"
#include "my_group_box.h"
#include "my_line_edit.h"
#include "my_spin_box.h"

QT_BEGIN_NAMESPACE

class Ui_cFakeLightsPanel
{
public:
    QVBoxLayout *verticalLayout_fake_lights_panel_root;
    MyGroupBox *groupCheck_fake_lights_enabled;
    QVBoxLayout *verticalLayout_39;
    QGridLayout *gridLayout_17;
    MyCheckBox *checkBox_fake_lights_relative_center;
    QLabel *label_60;
    MyLineEdit *logedit_fake_lights_orbit_trap_size;
    QLabel *label_91;
    MyLineEdit *vect3_fake_lights_orbit_trap_y;
    MyLineEdit *vect3_fake_lights_orbit_trap_z;
    MySpinBox *spinboxInt_fake_lights_min_iter;
    QLabel *label_106;
    QLabel *label_105;
    MyLineEdit *logedit_fake_lights_thickness;
    MyComboBox *comboBox_fake_lights_orbit_trap_shape;
    QLabel *label_92;
    QLabel *label_93;
    QLabel *label_108;
    MyLineEdit *logedit_fake_lights_visibility;
    QLabel *label_98;
    MyColorButton *colorButton_fake_lights_color;
    QLabel *label_97;
    MyDoubleSpinBox *spinboxd3_fake_lights_orbit_rotation_z;
    MyDoubleSpinBox *spinboxd3_fake_lights_orbit_rotation_x;
    QLabel *label_104;
    QLabel *label_96;
    QLabel *label_102;
    QLabel *label_107;
    QLabel *label_94;
    QLabel *label_45;
    MyDoubleSpinBox *spinboxd3_fake_lights_orbit_rotation_y;
    MyGroupBox *groupCheck_fake_lights_color_2_enabled;
    QGridLayout *gridLayout_25;
    QLabel *label_48;
    MyColorButton *colorButton_fake_lights_color_2;
    MyGroupBox *groupCheck_fake_lights_color_3_enabled;
    QGridLayout *gridLayout_28;
    QLabel *label_51;
    MyColorButton *colorButton_fake_lights_color_3;
    MyLineEdit *logedit_fake_lights_intensity;
    MySpinBox *spinboxInt_fake_lights_max_iter;
    MyDoubleSpinBox *spinbox_fake_lights_visibility_size;
    QLabel *label_95;
    QLabel *label_109;
    MyLineEdit *vect3_fake_lights_orbit_trap_x;
    QLabel *label_position_mode_;
    MyComboBox *comboBox_fake_lights_position_mode;
    QLabel *label_transition_speed_;
    MyDoubleSpinBox *spinbox_fake_lights_transition_speed;
    QStackedWidget *stackedWidget_fake_lights_mode;
    QWidget *page_fake_lights_world;
    QVBoxLayout *verticalLayout_world;
    QGroupBox *groupBox_fake_lights_world;
    QGridLayout *gridLayout_world;
    QLabel *label_world_offset;
    QLabel *label_world_offset_x;
    MyLineEdit *vect3_fake_lights_world_offset_x;
    QLabel *label_world_offset_y;
    MyLineEdit *vect3_fake_lights_world_offset_y;
    QLabel *label_world_offset_z;
    MyLineEdit *vect3_fake_lights_world_offset_z;
    QLabel *label_world_scale;
    MyLineEdit *logedit_fake_lights_world_scale;
    QLabel *label_world_rotation;
    QLabel *label_world_rotation_x;
    MyDoubleSpinBox *spinboxd3_fake_lights_world_rotation_x;
    QLabel *label_world_rotation_y;
    MyDoubleSpinBox *spinboxd3_fake_lights_world_rotation_y;
    QLabel *label_world_rotation_z;
    MyDoubleSpinBox *spinboxd3_fake_lights_world_rotation_z;
    QPushButton *pushButton_reset_world;
    QWidget *page_fake_lights_camera;
    QVBoxLayout *verticalLayout_camera;
    QGroupBox *groupBox_fake_lights_camera;
    QGridLayout *gridLayout_camera;
    QLabel *label_camera_offset;
    QLabel *label_camera_offset_x;
    MyLineEdit *vect3_fake_lights_camera_offset_x;
    QLabel *label_camera_offset_y;
    MyLineEdit *vect3_fake_lights_camera_offset_y;
    QLabel *label_camera_offset_z;
    MyLineEdit *vect3_fake_lights_camera_offset_z;
    QLabel *label_camera_scale;
    MyLineEdit *logedit_fake_lights_camera_scale;
    QLabel *label_camera_rotation;
    QLabel *label_camera_rotation_x;
    MyDoubleSpinBox *spinboxd3_fake_lights_camera_rotation_x;
    QLabel *label_camera_rotation_y;
    MyDoubleSpinBox *spinboxd3_fake_lights_camera_rotation_y;
    QLabel *label_camera_rotation_z;
    MyDoubleSpinBox *spinboxd3_fake_lights_camera_rotation_z;
    QPushButton *pushButton_reset_camera;
    QWidget *page_fake_lights_target;
    QVBoxLayout *verticalLayout_target;
    QGroupBox *groupBox_fake_lights_target;
    QGridLayout *gridLayout_target;
    QLabel *label_target_offset;
    QLabel *label_target_offset_x;
    MyLineEdit *vect3_fake_lights_target_offset_x;
    QLabel *label_target_offset_y;
    MyLineEdit *vect3_fake_lights_target_offset_y;
    QLabel *label_target_offset_z;
    MyLineEdit *vect3_fake_lights_target_offset_z;
    QLabel *label_target_scale;
    MyLineEdit *logedit_fake_lights_target_scale;
    QLabel *label_target_rotation;
    QLabel *label_target_rotation_x;
    MyDoubleSpinBox *spinboxd3_fake_lights_target_rotation_x;
    QLabel *label_target_rotation_y;
    MyDoubleSpinBox *spinboxd3_fake_lights_target_rotation_y;
    QLabel *label_target_rotation_z;
    MyDoubleSpinBox *spinboxd3_fake_lights_target_rotation_z;
    QPushButton *pushButton_reset_target;
    QWidget *page_fake_lights_fractal_center;
    QVBoxLayout *verticalLayout_fractal_center;
    QGroupBox *groupBox_fake_lights_fractal_center;
    QGridLayout *gridLayout_fractal_center;
    QLabel *label_fractal_center_offset;
    QLabel *label_fractal_center_offset_x;
    MyLineEdit *vect3_fake_lights_fractal_center_offset_x;
    QLabel *label_fractal_center_offset_y;
    MyLineEdit *vect3_fake_lights_fractal_center_offset_y;
    QLabel *label_fractal_center_offset_z;
    MyLineEdit *vect3_fake_lights_fractal_center_offset_z;
    QLabel *label_fractal_center_scale;
    MyLineEdit *logedit_fake_lights_fractal_center_scale;
    QLabel *label_fractal_center_rotation;
    QLabel *label_fractal_center_rotation_x;
    MyDoubleSpinBox *spinboxd3_fake_lights_fractal_center_rotation_x;
    QLabel *label_fractal_center_rotation_y;
    MyDoubleSpinBox *spinboxd3_fake_lights_fractal_center_rotation_y;
    QLabel *label_fractal_center_rotation_z;
    MyDoubleSpinBox *spinboxd3_fake_lights_fractal_center_rotation_z;
    QPushButton *pushButton_reset_fractal_center;
    QWidget *page_fake_lights_path_circle;
    QVBoxLayout *verticalLayout_path_circle;
    QGroupBox *groupBox_fake_lights_path_circle;
    QGridLayout *gridLayout_path_circle;
    QLabel *label_path_circle_offset;
    QLabel *label_path_circle_offset_x;
    MyLineEdit *vect3_fake_lights_path_circle_offset_x;
    QLabel *label_path_circle_offset_y;
    MyLineEdit *vect3_fake_lights_path_circle_offset_y;
    QLabel *label_path_circle_offset_z;
    MyLineEdit *vect3_fake_lights_path_circle_offset_z;
    QLabel *label_path_circle_scale;
    MyLineEdit *logedit_fake_lights_path_circle_scale;
    QLabel *label_path_circle_rotation;
    QLabel *label_path_circle_rotation_x;
    MyDoubleSpinBox *spinboxd3_fake_lights_path_circle_rotation_x;
    QLabel *label_path_circle_rotation_y;
    MyDoubleSpinBox *spinboxd3_fake_lights_path_circle_rotation_y;
    QLabel *label_path_circle_rotation_z;
    MyDoubleSpinBox *spinboxd3_fake_lights_path_circle_rotation_z;
    QLabel *label_path_circle_radius;
    MyDoubleSpinBox *spinbox_fake_lights_path_circle_path_radius;
    QPushButton *pushButton_reset_path_circle;
    QWidget *page_fake_lights_path_spiral;
    QVBoxLayout *verticalLayout_path_spiral;
    QGroupBox *groupBox_fake_lights_path_spiral;
    QGridLayout *gridLayout_path_spiral;
    QLabel *label_path_spiral_offset;
    QLabel *label_path_spiral_offset_x;
    MyLineEdit *vect3_fake_lights_path_spiral_offset_x;
    QLabel *label_path_spiral_offset_y;
    MyLineEdit *vect3_fake_lights_path_spiral_offset_y;
    QLabel *label_path_spiral_offset_z;
    MyLineEdit *vect3_fake_lights_path_spiral_offset_z;
    QLabel *label_path_spiral_scale;
    MyLineEdit *logedit_fake_lights_path_spiral_scale;
    QLabel *label_path_spiral_rotation;
    QLabel *label_path_spiral_rotation_x;
    MyDoubleSpinBox *spinboxd3_fake_lights_path_spiral_rotation_x;
    QLabel *label_path_spiral_rotation_y;
    MyDoubleSpinBox *spinboxd3_fake_lights_path_spiral_rotation_y;
    QLabel *label_path_spiral_rotation_z;
    MyDoubleSpinBox *spinboxd3_fake_lights_path_spiral_rotation_z;
    QLabel *label_path_spiral_radius;
    MyDoubleSpinBox *spinbox_fake_lights_path_spiral_path_radius;
    QPushButton *pushButton_reset_path_spiral;
    QWidget *page_fake_lights_orbit_target;
    QVBoxLayout *verticalLayout_orbit_target;
    QGroupBox *groupBox_fake_lights_orbit_target;
    QGridLayout *gridLayout_orbit_target;
    QLabel *label_orbit_target_offset;
    QLabel *label_orbit_target_offset_x;
    MyLineEdit *vect3_fake_lights_orbit_target_offset_x;
    QLabel *label_orbit_target_offset_y;
    MyLineEdit *vect3_fake_lights_orbit_target_offset_y;
    QLabel *label_orbit_target_offset_z;
    MyLineEdit *vect3_fake_lights_orbit_target_offset_z;
    QLabel *label_orbit_target_scale;
    MyLineEdit *logedit_fake_lights_orbit_target_scale;
    QLabel *label_orbit_target_rotation;
    QLabel *label_orbit_target_rotation_x;
    MyDoubleSpinBox *spinboxd3_fake_lights_orbit_target_rotation_x;
    QLabel *label_orbit_target_rotation_y;
    MyDoubleSpinBox *spinboxd3_fake_lights_orbit_target_rotation_y;
    QLabel *label_orbit_target_rotation_z;
    MyDoubleSpinBox *spinboxd3_fake_lights_orbit_target_rotation_z;
    QLabel *label_orbit_target_radius;
    MyDoubleSpinBox *spinbox_fake_lights_orbit_target_path_radius;
    QPushButton *pushButton_reset_orbit_target;
    QGroupBox *groupBox_fake_lights_multi_center;
    QGridLayout *gridLayout_multi_center;
    MyCheckBox *checkBox_fake_lights_multi_center_enabled;
    QLabel *label_multi_center_1;
    QLabel *label_multi_center_1_x;
    MyLineEdit *vect3_fake_lights_multi_center_1_x;
    QLabel *label_multi_center_1_y;
    MyLineEdit *vect3_fake_lights_multi_center_1_y;
    QLabel *label_multi_center_1_z;
    MyLineEdit *vect3_fake_lights_multi_center_1_z;
    QLabel *label_multi_center_weight_1;
    MyDoubleSpinBox *spinbox_fake_lights_multi_center_weight_1;
    QLabel *label_multi_center_color_1;
    MyColorButton *colorButton_fake_lights_multi_center_color_1;
    QFrame *line_multi_center_sep_4;
    QLabel *label_multi_center_2;
    QLabel *label_multi_center_2_x;
    MyLineEdit *vect3_fake_lights_multi_center_2_x;
    QLabel *label_multi_center_2_y;
    MyLineEdit *vect3_fake_lights_multi_center_2_y;
    QLabel *label_multi_center_2_z;
    MyLineEdit *vect3_fake_lights_multi_center_2_z;
    QLabel *label_multi_center_weight_2;
    MyDoubleSpinBox *spinbox_fake_lights_multi_center_weight_2;
    QLabel *label_multi_center_color_2;
    MyColorButton *colorButton_fake_lights_multi_center_color_2;
    QFrame *line_multi_center_sep_8;
    QLabel *label_multi_center_3;
    QLabel *label_multi_center_3_x;
    MyLineEdit *vect3_fake_lights_multi_center_3_x;
    QLabel *label_multi_center_3_y;
    MyLineEdit *vect3_fake_lights_multi_center_3_y;
    QLabel *label_multi_center_3_z;
    MyLineEdit *vect3_fake_lights_multi_center_3_z;
    QLabel *label_multi_center_weight_3;
    MyDoubleSpinBox *spinbox_fake_lights_multi_center_weight_3;
    QLabel *label_multi_center_color_3;
    MyColorButton *colorButton_fake_lights_multi_center_color_3;
    QFrame *line_multi_center_sep_12;
    QLabel *label_multi_center_4;
    QLabel *label_multi_center_4_x;
    MyLineEdit *vect3_fake_lights_multi_center_4_x;
    QLabel *label_multi_center_4_y;
    MyLineEdit *vect3_fake_lights_multi_center_4_y;
    QLabel *label_multi_center_4_z;
    MyLineEdit *vect3_fake_lights_multi_center_4_z;
    QLabel *label_multi_center_weight_4;
    MyDoubleSpinBox *spinbox_fake_lights_multi_center_weight_4;
    QLabel *label_multi_center_color_4;
    MyColorButton *colorButton_fake_lights_multi_center_color_4;
    QFrame *line_multi_center_sep_16;
    QLabel *label_multi_center_5;
    QLabel *label_multi_center_5_x;
    MyLineEdit *vect3_fake_lights_multi_center_5_x;
    QLabel *label_multi_center_5_y;
    MyLineEdit *vect3_fake_lights_multi_center_5_y;
    QLabel *label_multi_center_5_z;
    MyLineEdit *vect3_fake_lights_multi_center_5_z;
    QLabel *label_multi_center_weight_5;
    MyDoubleSpinBox *spinbox_fake_lights_multi_center_weight_5;
    QLabel *label_multi_center_color_5;
    MyColorButton *colorButton_fake_lights_multi_center_color_5;
    QFrame *line_multi_center_sep_20;
    QLabel *label_multi_center_6;
    QLabel *label_multi_center_6_x;
    MyLineEdit *vect3_fake_lights_multi_center_6_x;
    QLabel *label_multi_center_6_y;
    MyLineEdit *vect3_fake_lights_multi_center_6_y;
    QLabel *label_multi_center_6_z;
    MyLineEdit *vect3_fake_lights_multi_center_6_z;
    QLabel *label_multi_center_weight_6;
    MyDoubleSpinBox *spinbox_fake_lights_multi_center_weight_6;
    QLabel *label_multi_center_color_6;
    MyColorButton *colorButton_fake_lights_multi_center_color_6;
    QFrame *line_multi_center_sep_24;
    QLabel *label_multi_center_7;
    QLabel *label_multi_center_7_x;
    MyLineEdit *vect3_fake_lights_multi_center_7_x;
    QLabel *label_multi_center_7_y;
    MyLineEdit *vect3_fake_lights_multi_center_7_y;
    QLabel *label_multi_center_7_z;
    MyLineEdit *vect3_fake_lights_multi_center_7_z;
    QLabel *label_multi_center_weight_7;
    MyDoubleSpinBox *spinbox_fake_lights_multi_center_weight_7;
    QLabel *label_multi_center_color_7;
    MyColorButton *colorButton_fake_lights_multi_center_color_7;
    QFrame *line_multi_center_sep_28;
    QLabel *label_multi_center_8;
    QLabel *label_multi_center_8_x;
    MyLineEdit *vect3_fake_lights_multi_center_8_x;
    QLabel *label_multi_center_8_y;
    MyLineEdit *vect3_fake_lights_multi_center_8_y;
    QLabel *label_multi_center_8_z;
    MyLineEdit *vect3_fake_lights_multi_center_8_z;
    QLabel *label_multi_center_weight_8;
    MyDoubleSpinBox *spinbox_fake_lights_multi_center_weight_8;
    QLabel *label_multi_center_color_8;
    MyColorButton *colorButton_fake_lights_multi_center_color_8;
    QFrame *line_multi_center_sep_32;
    QLabel *label_multi_center_9;
    QLabel *label_multi_center_9_x;
    MyLineEdit *vect3_fake_lights_multi_center_9_x;
    QLabel *label_multi_center_9_y;
    MyLineEdit *vect3_fake_lights_multi_center_9_y;
    QLabel *label_multi_center_9_z;
    MyLineEdit *vect3_fake_lights_multi_center_9_z;
    QLabel *label_multi_center_weight_9;
    MyDoubleSpinBox *spinbox_fake_lights_multi_center_weight_9;
    QLabel *label_multi_center_color_9;
    MyColorButton *colorButton_fake_lights_multi_center_color_9;
    QFrame *line_multi_center_sep_36;
    QLabel *label_multi_center_10;
    QLabel *label_multi_center_10_x;
    MyLineEdit *vect3_fake_lights_multi_center_10_x;
    QLabel *label_multi_center_10_y;
    MyLineEdit *vect3_fake_lights_multi_center_10_y;
    QLabel *label_multi_center_10_z;
    MyLineEdit *vect3_fake_lights_multi_center_10_z;
    QLabel *label_multi_center_weight_10;
    MyDoubleSpinBox *spinbox_fake_lights_multi_center_weight_10;
    QLabel *label_multi_center_color_10;
    MyColorButton *colorButton_fake_lights_multi_center_color_10;
    QFrame *line_multi_center_sep_40;
    QLabel *label_multi_center_11;
    QLabel *label_multi_center_11_x;
    MyLineEdit *vect3_fake_lights_multi_center_11_x;
    QLabel *label_multi_center_11_y;
    MyLineEdit *vect3_fake_lights_multi_center_11_y;
    QLabel *label_multi_center_11_z;
    MyLineEdit *vect3_fake_lights_multi_center_11_z;
    QLabel *label_multi_center_weight_11;
    MyDoubleSpinBox *spinbox_fake_lights_multi_center_weight_11;
    QLabel *label_multi_center_color_11;
    MyColorButton *colorButton_fake_lights_multi_center_color_11;
    QFrame *line_multi_center_sep_44;
    QLabel *label_multi_center_12;
    QLabel *label_multi_center_12_x;
    MyLineEdit *vect3_fake_lights_multi_center_12_x;
    QLabel *label_multi_center_12_y;
    MyLineEdit *vect3_fake_lights_multi_center_12_y;
    QLabel *label_multi_center_12_z;
    MyLineEdit *vect3_fake_lights_multi_center_12_z;
    QLabel *label_multi_center_weight_12;
    MyDoubleSpinBox *spinbox_fake_lights_multi_center_weight_12;
    QLabel *label_multi_center_color_12;
    MyColorButton *colorButton_fake_lights_multi_center_color_12;
    QFrame *line_multi_center_sep_48;
    QLabel *label_multi_center_13;
    QLabel *label_multi_center_13_x;
    MyLineEdit *vect3_fake_lights_multi_center_13_x;
    QLabel *label_multi_center_13_y;
    MyLineEdit *vect3_fake_lights_multi_center_13_y;
    QLabel *label_multi_center_13_z;
    MyLineEdit *vect3_fake_lights_multi_center_13_z;
    QLabel *label_multi_center_weight_13;
    MyDoubleSpinBox *spinbox_fake_lights_multi_center_weight_13;
    QLabel *label_multi_center_color_13;
    MyColorButton *colorButton_fake_lights_multi_center_color_13;
    QFrame *line_multi_center_sep_52;
    QLabel *label_multi_center_14;
    QLabel *label_multi_center_14_x;
    MyLineEdit *vect3_fake_lights_multi_center_14_x;
    QLabel *label_multi_center_14_y;
    MyLineEdit *vect3_fake_lights_multi_center_14_y;
    QLabel *label_multi_center_14_z;
    MyLineEdit *vect3_fake_lights_multi_center_14_z;
    QLabel *label_multi_center_weight_14;
    MyDoubleSpinBox *spinbox_fake_lights_multi_center_weight_14;
    QLabel *label_multi_center_color_14;
    MyColorButton *colorButton_fake_lights_multi_center_color_14;
    QFrame *line_multi_center_sep_56;
    QLabel *label_multi_center_15;
    QLabel *label_multi_center_15_x;
    MyLineEdit *vect3_fake_lights_multi_center_15_x;
    QLabel *label_multi_center_15_y;
    MyLineEdit *vect3_fake_lights_multi_center_15_y;
    QLabel *label_multi_center_15_z;
    MyLineEdit *vect3_fake_lights_multi_center_15_z;
    QLabel *label_multi_center_weight_15;
    MyDoubleSpinBox *spinbox_fake_lights_multi_center_weight_15;
    QLabel *label_multi_center_color_15;
    MyColorButton *colorButton_fake_lights_multi_center_color_15;
    QFrame *line_multi_center_sep_60;
    QLabel *label_multi_center_16;
    QLabel *label_multi_center_16_x;
    MyLineEdit *vect3_fake_lights_multi_center_16_x;
    QLabel *label_multi_center_16_y;
    MyLineEdit *vect3_fake_lights_multi_center_16_y;
    QLabel *label_multi_center_16_z;
    MyLineEdit *vect3_fake_lights_multi_center_16_z;
    QLabel *label_multi_center_weight_16;
    MyDoubleSpinBox *spinbox_fake_lights_multi_center_weight_16;
    QLabel *label_multi_center_color_16;
    MyColorButton *colorButton_fake_lights_multi_center_color_16;
    QFrame *line_multi_center_sep_64;
    QLabel *label_multi_center_17;
    QLabel *label_multi_center_17_x;
    MyLineEdit *vect3_fake_lights_multi_center_17_x;
    QLabel *label_multi_center_17_y;
    MyLineEdit *vect3_fake_lights_multi_center_17_y;
    QLabel *label_multi_center_17_z;
    MyLineEdit *vect3_fake_lights_multi_center_17_z;
    QLabel *label_multi_center_weight_17;
    MyDoubleSpinBox *spinbox_fake_lights_multi_center_weight_17;
    QLabel *label_multi_center_color_17;
    MyColorButton *colorButton_fake_lights_multi_center_color_17;
    QFrame *line_multi_center_sep_68;
    QLabel *label_multi_center_18;
    QLabel *label_multi_center_18_x;
    MyLineEdit *vect3_fake_lights_multi_center_18_x;
    QLabel *label_multi_center_18_y;
    MyLineEdit *vect3_fake_lights_multi_center_18_y;
    QLabel *label_multi_center_18_z;
    MyLineEdit *vect3_fake_lights_multi_center_18_z;
    QLabel *label_multi_center_weight_18;
    MyDoubleSpinBox *spinbox_fake_lights_multi_center_weight_18;
    QLabel *label_multi_center_color_18;
    MyColorButton *colorButton_fake_lights_multi_center_color_18;
    QFrame *line_multi_center_sep_72;
    QLabel *label_multi_center_19;
    QLabel *label_multi_center_19_x;
    MyLineEdit *vect3_fake_lights_multi_center_19_x;
    QLabel *label_multi_center_19_y;
    MyLineEdit *vect3_fake_lights_multi_center_19_y;
    QLabel *label_multi_center_19_z;
    MyLineEdit *vect3_fake_lights_multi_center_19_z;
    QLabel *label_multi_center_weight_19;
    MyDoubleSpinBox *spinbox_fake_lights_multi_center_weight_19;
    QLabel *label_multi_center_color_19;
    MyColorButton *colorButton_fake_lights_multi_center_color_19;
    QFrame *line_multi_center_sep_76;
    QLabel *label_multi_center_20;
    QLabel *label_multi_center_20_x;
    MyLineEdit *vect3_fake_lights_multi_center_20_x;
    QLabel *label_multi_center_20_y;
    MyLineEdit *vect3_fake_lights_multi_center_20_y;
    QLabel *label_multi_center_20_z;
    MyLineEdit *vect3_fake_lights_multi_center_20_z;
    QLabel *label_multi_center_weight_20;
    MyDoubleSpinBox *spinbox_fake_lights_multi_center_weight_20;
    QLabel *label_multi_center_color_20;
    MyColorButton *colorButton_fake_lights_multi_center_color_20;
    QFrame *line_multi_center_sep_80;
    QLabel *label_multi_center_21;
    QLabel *label_multi_center_21_x;
    MyLineEdit *vect3_fake_lights_multi_center_21_x;
    QLabel *label_multi_center_21_y;
    MyLineEdit *vect3_fake_lights_multi_center_21_y;
    QLabel *label_multi_center_21_z;
    MyLineEdit *vect3_fake_lights_multi_center_21_z;
    QLabel *label_multi_center_weight_21;
    MyDoubleSpinBox *spinbox_fake_lights_multi_center_weight_21;
    QLabel *label_multi_center_color_21;
    MyColorButton *colorButton_fake_lights_multi_center_color_21;
    QFrame *line_multi_center_sep_84;
    QLabel *label_multi_center_22;
    QLabel *label_multi_center_22_x;
    MyLineEdit *vect3_fake_lights_multi_center_22_x;
    QLabel *label_multi_center_22_y;
    MyLineEdit *vect3_fake_lights_multi_center_22_y;
    QLabel *label_multi_center_22_z;
    MyLineEdit *vect3_fake_lights_multi_center_22_z;
    QLabel *label_multi_center_weight_22;
    MyDoubleSpinBox *spinbox_fake_lights_multi_center_weight_22;
    QLabel *label_multi_center_color_22;
    MyColorButton *colorButton_fake_lights_multi_center_color_22;
    QFrame *line_multi_center_sep_88;
    QLabel *label_multi_center_23;
    QLabel *label_multi_center_23_x;
    MyLineEdit *vect3_fake_lights_multi_center_23_x;
    QLabel *label_multi_center_23_y;
    MyLineEdit *vect3_fake_lights_multi_center_23_y;
    QLabel *label_multi_center_23_z;
    MyLineEdit *vect3_fake_lights_multi_center_23_z;
    QLabel *label_multi_center_weight_23;
    MyDoubleSpinBox *spinbox_fake_lights_multi_center_weight_23;
    QLabel *label_multi_center_color_23;
    MyColorButton *colorButton_fake_lights_multi_center_color_23;
    QFrame *line_multi_center_sep_92;
    QLabel *label_multi_center_24;
    QLabel *label_multi_center_24_x;
    MyLineEdit *vect3_fake_lights_multi_center_24_x;
    QLabel *label_multi_center_24_y;
    MyLineEdit *vect3_fake_lights_multi_center_24_y;
    QLabel *label_multi_center_24_z;
    MyLineEdit *vect3_fake_lights_multi_center_24_z;
    QLabel *label_multi_center_weight_24;
    MyDoubleSpinBox *spinbox_fake_lights_multi_center_weight_24;
    QLabel *label_multi_center_color_24;
    MyColorButton *colorButton_fake_lights_multi_center_color_24;
    QPushButton *pushButton_reset_multi_center;
    QGroupBox *groupBox_fake_lights_shape_modifiers;
    QGridLayout *gridLayout_shape_modifiers;
    QLabel *label_shape_twist;
    MyDoubleSpinBox *spinbox_fake_lights_shape_twist;
    QLabel *label_shape_bend;
    MyDoubleSpinBox *spinbox_fake_lights_shape_bend;
    QLabel *label_shape_taper;
    MyDoubleSpinBox *spinbox_fake_lights_shape_taper;
    QLabel *label_shape_fold_symmetry;
    MySpinBox *spinboxInt_fake_lights_shape_fold_symmetry;
    QLabel *label_shape_repeat_x;
    MyDoubleSpinBox *spinbox_fake_lights_shape_repeat_x;
    QLabel *label_shape_repeat_y;
    MyDoubleSpinBox *spinbox_fake_lights_shape_repeat_y;
    QLabel *label_shape_repeat_z;
    MyDoubleSpinBox *spinbox_fake_lights_shape_repeat_z;
    QLabel *label_shape_wobble_amp;
    MyDoubleSpinBox *spinbox_fake_lights_shape_wobble_amplitude;
    QLabel *label_shape_wobble_freq;
    MyDoubleSpinBox *spinbox_fake_lights_shape_wobble_frequency;
    QLabel *label_shape_chamfer;
    MyDoubleSpinBox *spinbox_fake_lights_shape_chamfer;
    QLabel *label_shape_scale_x;
    MyDoubleSpinBox *spinbox_fake_lights_shape_scale_x;
    QLabel *label_shape_scale_y;
    MyDoubleSpinBox *spinbox_fake_lights_shape_scale_y;
    QLabel *label_shape_scale_z;
    MyDoubleSpinBox *spinbox_fake_lights_shape_scale_z;
    QLabel *label_shape_mirror_x;
    MyCheckBox *checkBox_fake_lights_shape_mirror_x;
    QLabel *label_shape_mirror_y;
    MyCheckBox *checkBox_fake_lights_shape_mirror_y;
    QLabel *label_shape_mirror_z;
    MyCheckBox *checkBox_fake_lights_shape_mirror_z;
    QLabel *label_shape_inflate;
    MyDoubleSpinBox *spinbox_fake_lights_shape_inflate;
    QLabel *label_shape_line_length;
    MyDoubleSpinBox *spinbox_fake_lights_shape_line_length;
    QLabel *label_shape_tube_radius;
    MyDoubleSpinBox *spinbox_fake_lights_shape_tube_radius;
    QLabel *label_shape_line_thickness;
    MyDoubleSpinBox *spinbox_fake_lights_shape_line_thickness;
    QLabel *label_shape_falloff;
    MyDoubleSpinBox *spinbox_fake_lights_shape_falloff;
    QLabel *label_shape_mask_radius;
    MyDoubleSpinBox *spinbox_fake_lights_shape_mask_radius;
    QLabel *label_shape_mask_softness;
    MyDoubleSpinBox *spinbox_fake_lights_shape_mask_softness;
    QLabel *label_shape_spiral;
    MyDoubleSpinBox *spinbox_fake_lights_shape_spiral;
    QLabel *label_shape_wave_x;
    MyDoubleSpinBox *spinbox_fake_lights_shape_wave_x;
    QLabel *label_shape_wave_y;
    MyDoubleSpinBox *spinbox_fake_lights_shape_wave_y;
    QLabel *label_shape_wave_z;
    MyDoubleSpinBox *spinbox_fake_lights_shape_wave_z;
    QLabel *label_shape_wave_frequency;
    MyDoubleSpinBox *spinbox_fake_lights_shape_wave_frequency;
    QGroupBox *groupBox_fake_lights_distance_mask;
    QGridLayout *gridLayout_distance_mask;
    MyCheckBox *checkBox_fake_lights_mask_enabled;
    QLabel *label_mask_threshold;
    MyDoubleSpinBox *spinbox_fake_lights_mask_threshold;
    QLabel *label_mask_sharpness;
    MyDoubleSpinBox *spinbox_fake_lights_mask_sharpness;

    void setupUi(QWidget *cFakeLightsPanel)
    {
        if (cFakeLightsPanel->objectName().isEmpty())
            cFakeLightsPanel->setObjectName(QString::fromUtf8("cFakeLightsPanel"));
        verticalLayout_fake_lights_panel_root = new QVBoxLayout(cFakeLightsPanel);
        verticalLayout_fake_lights_panel_root->setObjectName(QString::fromUtf8("verticalLayout_fake_lights_panel_root"));
        verticalLayout_fake_lights_panel_root->setContentsMargins(0, 0, 0, 0);
        groupCheck_fake_lights_enabled = new MyGroupBox(cFakeLightsPanel);
        groupCheck_fake_lights_enabled->setObjectName(QString::fromUtf8("groupCheck_fake_lights_enabled"));
        groupCheck_fake_lights_enabled->setCheckable(true);
        verticalLayout_39 = new QVBoxLayout(groupCheck_fake_lights_enabled);
        verticalLayout_39->setSpacing(2);
        verticalLayout_39->setObjectName(QString::fromUtf8("verticalLayout_39"));
        verticalLayout_39->setContentsMargins(2, 2, 2, 2);
        gridLayout_17 = new QGridLayout();
        gridLayout_17->setSpacing(2);
        gridLayout_17->setObjectName(QString::fromUtf8("gridLayout_17"));
        checkBox_fake_lights_relative_center = new MyCheckBox(groupCheck_fake_lights_enabled);
        checkBox_fake_lights_relative_center->setObjectName(QString::fromUtf8("checkBox_fake_lights_relative_center"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(checkBox_fake_lights_relative_center->sizePolicy().hasHeightForWidth());
        checkBox_fake_lights_relative_center->setSizePolicy(sizePolicy);

        gridLayout_17->addWidget(checkBox_fake_lights_relative_center, 7, 0, 1, 3);

        label_60 = new QLabel(groupCheck_fake_lights_enabled);
        label_60->setObjectName(QString::fromUtf8("label_60"));

        gridLayout_17->addWidget(label_60, 0, 0, 1, 1);

        logedit_fake_lights_orbit_trap_size = new MyLineEdit(groupCheck_fake_lights_enabled);
        logedit_fake_lights_orbit_trap_size->setObjectName(QString::fromUtf8("logedit_fake_lights_orbit_trap_size"));

        gridLayout_17->addWidget(logedit_fake_lights_orbit_trap_size, 11, 2, 1, 1);

        label_91 = new QLabel(groupCheck_fake_lights_enabled);
        label_91->setObjectName(QString::fromUtf8("label_91"));

        gridLayout_17->addWidget(label_91, 1, 0, 1, 1);

        vect3_fake_lights_orbit_trap_y = new MyLineEdit(groupCheck_fake_lights_enabled);
        vect3_fake_lights_orbit_trap_y->setObjectName(QString::fromUtf8("vect3_fake_lights_orbit_trap_y"));

        gridLayout_17->addWidget(vect3_fake_lights_orbit_trap_y, 9, 2, 1, 1);

        vect3_fake_lights_orbit_trap_z = new MyLineEdit(groupCheck_fake_lights_enabled);
        vect3_fake_lights_orbit_trap_z->setObjectName(QString::fromUtf8("vect3_fake_lights_orbit_trap_z"));

        gridLayout_17->addWidget(vect3_fake_lights_orbit_trap_z, 10, 2, 1, 1);

        spinboxInt_fake_lights_min_iter = new MySpinBox(groupCheck_fake_lights_enabled);
        spinboxInt_fake_lights_min_iter->setObjectName(QString::fromUtf8("spinboxInt_fake_lights_min_iter"));
        sizePolicy.setHeightForWidth(spinboxInt_fake_lights_min_iter->sizePolicy().hasHeightForWidth());
        spinboxInt_fake_lights_min_iter->setSizePolicy(sizePolicy);
        spinboxInt_fake_lights_min_iter->setMaximum(500);

        gridLayout_17->addWidget(spinboxInt_fake_lights_min_iter, 0, 2, 1, 1);

        label_106 = new QLabel(groupCheck_fake_lights_enabled);
        label_106->setObjectName(QString::fromUtf8("label_106"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_106->sizePolicy().hasHeightForWidth());
        label_106->setSizePolicy(sizePolicy1);
        label_106->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_17->addWidget(label_106, 12, 1, 1, 1);

        label_105 = new QLabel(groupCheck_fake_lights_enabled);
        label_105->setObjectName(QString::fromUtf8("label_105"));

        gridLayout_17->addWidget(label_105, 11, 0, 1, 1);

        logedit_fake_lights_thickness = new MyLineEdit(groupCheck_fake_lights_enabled);
        logedit_fake_lights_thickness->setObjectName(QString::fromUtf8("logedit_fake_lights_thickness"));

        gridLayout_17->addWidget(logedit_fake_lights_thickness, 5, 2, 1, 1);

        comboBox_fake_lights_orbit_trap_shape = new MyComboBox(groupCheck_fake_lights_enabled);
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->addItem(QString());
        comboBox_fake_lights_orbit_trap_shape->setObjectName(QString::fromUtf8("comboBox_fake_lights_orbit_trap_shape"));

        gridLayout_17->addWidget(comboBox_fake_lights_orbit_trap_shape, 6, 2, 1, 1);

        label_92 = new QLabel(groupCheck_fake_lights_enabled);
        label_92->setObjectName(QString::fromUtf8("label_92"));

        gridLayout_17->addWidget(label_92, 2, 0, 1, 1);

        label_93 = new QLabel(groupCheck_fake_lights_enabled);
        label_93->setObjectName(QString::fromUtf8("label_93"));
        label_93->setWordWrap(true);

        gridLayout_17->addWidget(label_93, 3, 0, 1, 1);

        label_108 = new QLabel(groupCheck_fake_lights_enabled);
        label_108->setObjectName(QString::fromUtf8("label_108"));
        sizePolicy1.setHeightForWidth(label_108->sizePolicy().hasHeightForWidth());
        label_108->setSizePolicy(sizePolicy1);
        label_108->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_17->addWidget(label_108, 14, 1, 1, 1);

        logedit_fake_lights_visibility = new MyLineEdit(groupCheck_fake_lights_enabled);
        logedit_fake_lights_visibility->setObjectName(QString::fromUtf8("logedit_fake_lights_visibility"));

        gridLayout_17->addWidget(logedit_fake_lights_visibility, 3, 2, 1, 1);

        label_98 = new QLabel(groupCheck_fake_lights_enabled);
        label_98->setObjectName(QString::fromUtf8("label_98"));
        sizePolicy1.setHeightForWidth(label_98->sizePolicy().hasHeightForWidth());
        label_98->setSizePolicy(sizePolicy1);
        label_98->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_17->addWidget(label_98, 10, 1, 1, 1);

        colorButton_fake_lights_color = new MyColorButton(groupCheck_fake_lights_enabled);
        colorButton_fake_lights_color->setObjectName(QString::fromUtf8("colorButton_fake_lights_color"));

        gridLayout_17->addWidget(colorButton_fake_lights_color, 15, 2, 1, 1);

        label_97 = new QLabel(groupCheck_fake_lights_enabled);
        label_97->setObjectName(QString::fromUtf8("label_97"));
        sizePolicy1.setHeightForWidth(label_97->sizePolicy().hasHeightForWidth());
        label_97->setSizePolicy(sizePolicy1);
        label_97->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_17->addWidget(label_97, 9, 1, 1, 1);

        spinboxd3_fake_lights_orbit_rotation_z = new MyDoubleSpinBox(groupCheck_fake_lights_enabled);
        spinboxd3_fake_lights_orbit_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_fake_lights_orbit_rotation_z"));
        sizePolicy.setHeightForWidth(spinboxd3_fake_lights_orbit_rotation_z->sizePolicy().hasHeightForWidth());
        spinboxd3_fake_lights_orbit_rotation_z->setSizePolicy(sizePolicy);
        spinboxd3_fake_lights_orbit_rotation_z->setDecimals(2);
        spinboxd3_fake_lights_orbit_rotation_z->setMinimum(-36000.000000000000000);
        spinboxd3_fake_lights_orbit_rotation_z->setMaximum(36000.000000000000000);
        spinboxd3_fake_lights_orbit_rotation_z->setSingleStep(0.100000000000000);

        gridLayout_17->addWidget(spinboxd3_fake_lights_orbit_rotation_z, 14, 2, 1, 1);

        spinboxd3_fake_lights_orbit_rotation_x = new MyDoubleSpinBox(groupCheck_fake_lights_enabled);
        spinboxd3_fake_lights_orbit_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_fake_lights_orbit_rotation_x"));
        sizePolicy.setHeightForWidth(spinboxd3_fake_lights_orbit_rotation_x->sizePolicy().hasHeightForWidth());
        spinboxd3_fake_lights_orbit_rotation_x->setSizePolicy(sizePolicy);
        spinboxd3_fake_lights_orbit_rotation_x->setDecimals(2);
        spinboxd3_fake_lights_orbit_rotation_x->setMinimum(-36000.000000000000000);
        spinboxd3_fake_lights_orbit_rotation_x->setMaximum(36000.000000000000000);
        spinboxd3_fake_lights_orbit_rotation_x->setSingleStep(0.100000000000000);

        gridLayout_17->addWidget(spinboxd3_fake_lights_orbit_rotation_x, 12, 2, 1, 1);

        label_104 = new QLabel(groupCheck_fake_lights_enabled);
        label_104->setObjectName(QString::fromUtf8("label_104"));

        gridLayout_17->addWidget(label_104, 6, 0, 1, 1);

        label_96 = new QLabel(groupCheck_fake_lights_enabled);
        label_96->setObjectName(QString::fromUtf8("label_96"));
        sizePolicy1.setHeightForWidth(label_96->sizePolicy().hasHeightForWidth());
        label_96->setSizePolicy(sizePolicy1);
        label_96->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_17->addWidget(label_96, 8, 1, 1, 1);

        label_102 = new QLabel(groupCheck_fake_lights_enabled);
        label_102->setObjectName(QString::fromUtf8("label_102"));

        gridLayout_17->addWidget(label_102, 12, 0, 3, 1);

        label_107 = new QLabel(groupCheck_fake_lights_enabled);
        label_107->setObjectName(QString::fromUtf8("label_107"));
        sizePolicy1.setHeightForWidth(label_107->sizePolicy().hasHeightForWidth());
        label_107->setSizePolicy(sizePolicy1);
        label_107->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_17->addWidget(label_107, 13, 1, 1, 1);

        label_94 = new QLabel(groupCheck_fake_lights_enabled);
        label_94->setObjectName(QString::fromUtf8("label_94"));

        gridLayout_17->addWidget(label_94, 4, 0, 1, 1);

        label_45 = new QLabel(groupCheck_fake_lights_enabled);
        label_45->setObjectName(QString::fromUtf8("label_45"));

        gridLayout_17->addWidget(label_45, 15, 0, 1, 1);

        spinboxd3_fake_lights_orbit_rotation_y = new MyDoubleSpinBox(groupCheck_fake_lights_enabled);
        spinboxd3_fake_lights_orbit_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_fake_lights_orbit_rotation_y"));
        sizePolicy.setHeightForWidth(spinboxd3_fake_lights_orbit_rotation_y->sizePolicy().hasHeightForWidth());
        spinboxd3_fake_lights_orbit_rotation_y->setSizePolicy(sizePolicy);
        spinboxd3_fake_lights_orbit_rotation_y->setDecimals(2);
        spinboxd3_fake_lights_orbit_rotation_y->setMinimum(-36000.000000000000000);
        spinboxd3_fake_lights_orbit_rotation_y->setMaximum(36000.000000000000000);
        spinboxd3_fake_lights_orbit_rotation_y->setSingleStep(0.100000000000000);

        gridLayout_17->addWidget(spinboxd3_fake_lights_orbit_rotation_y, 13, 2, 1, 1);

        groupCheck_fake_lights_color_2_enabled = new MyGroupBox(groupCheck_fake_lights_enabled);
        groupCheck_fake_lights_color_2_enabled->setObjectName(QString::fromUtf8("groupCheck_fake_lights_color_2_enabled"));
        groupCheck_fake_lights_color_2_enabled->setCheckable(true);
        gridLayout_25 = new QGridLayout(groupCheck_fake_lights_color_2_enabled);
        gridLayout_25->setSpacing(2);
        gridLayout_25->setObjectName(QString::fromUtf8("gridLayout_25"));
        gridLayout_25->setContentsMargins(2, 2, 2, 2);
        label_48 = new QLabel(groupCheck_fake_lights_color_2_enabled);
        label_48->setObjectName(QString::fromUtf8("label_48"));

        gridLayout_25->addWidget(label_48, 0, 0, 1, 1);

        colorButton_fake_lights_color_2 = new MyColorButton(groupCheck_fake_lights_color_2_enabled);
        colorButton_fake_lights_color_2->setObjectName(QString::fromUtf8("colorButton_fake_lights_color_2"));

        gridLayout_25->addWidget(colorButton_fake_lights_color_2, 0, 1, 1, 1);

        groupCheck_fake_lights_color_3_enabled = new MyGroupBox(groupCheck_fake_lights_color_2_enabled);
        groupCheck_fake_lights_color_3_enabled->setObjectName(QString::fromUtf8("groupCheck_fake_lights_color_3_enabled"));
        groupCheck_fake_lights_color_3_enabled->setCheckable(true);
        gridLayout_28 = new QGridLayout(groupCheck_fake_lights_color_3_enabled);
        gridLayout_28->setSpacing(2);
        gridLayout_28->setObjectName(QString::fromUtf8("gridLayout_28"));
        gridLayout_28->setContentsMargins(2, 2, 2, 2);
        label_51 = new QLabel(groupCheck_fake_lights_color_3_enabled);
        label_51->setObjectName(QString::fromUtf8("label_51"));

        gridLayout_28->addWidget(label_51, 0, 0, 1, 1);

        colorButton_fake_lights_color_3 = new MyColorButton(groupCheck_fake_lights_color_3_enabled);
        colorButton_fake_lights_color_3->setObjectName(QString::fromUtf8("colorButton_fake_lights_color_3"));

        gridLayout_28->addWidget(colorButton_fake_lights_color_3, 0, 1, 1, 1);


        gridLayout_25->addWidget(groupCheck_fake_lights_color_3_enabled, 1, 0, 1, 2);


        gridLayout_17->addWidget(groupCheck_fake_lights_color_2_enabled, 16, 0, 1, 3);

        logedit_fake_lights_intensity = new MyLineEdit(groupCheck_fake_lights_enabled);
        logedit_fake_lights_intensity->setObjectName(QString::fromUtf8("logedit_fake_lights_intensity"));

        gridLayout_17->addWidget(logedit_fake_lights_intensity, 2, 2, 1, 1);

        spinboxInt_fake_lights_max_iter = new MySpinBox(groupCheck_fake_lights_enabled);
        spinboxInt_fake_lights_max_iter->setObjectName(QString::fromUtf8("spinboxInt_fake_lights_max_iter"));
        sizePolicy.setHeightForWidth(spinboxInt_fake_lights_max_iter->sizePolicy().hasHeightForWidth());
        spinboxInt_fake_lights_max_iter->setSizePolicy(sizePolicy);
        spinboxInt_fake_lights_max_iter->setMaximum(500);

        gridLayout_17->addWidget(spinboxInt_fake_lights_max_iter, 1, 2, 1, 1);

        spinbox_fake_lights_visibility_size = new MyDoubleSpinBox(groupCheck_fake_lights_enabled);
        spinbox_fake_lights_visibility_size->setObjectName(QString::fromUtf8("spinbox_fake_lights_visibility_size"));
        sizePolicy.setHeightForWidth(spinbox_fake_lights_visibility_size->sizePolicy().hasHeightForWidth());
        spinbox_fake_lights_visibility_size->setSizePolicy(sizePolicy);
        spinbox_fake_lights_visibility_size->setDecimals(2);
        spinbox_fake_lights_visibility_size->setMinimum(0.100000000000000);
        spinbox_fake_lights_visibility_size->setMaximum(10.000000000000000);
        spinbox_fake_lights_visibility_size->setSingleStep(0.100000000000000);

        gridLayout_17->addWidget(spinbox_fake_lights_visibility_size, 4, 2, 1, 1);

        label_95 = new QLabel(groupCheck_fake_lights_enabled);
        label_95->setObjectName(QString::fromUtf8("label_95"));

        gridLayout_17->addWidget(label_95, 8, 0, 3, 1);

        label_109 = new QLabel(groupCheck_fake_lights_enabled);
        label_109->setObjectName(QString::fromUtf8("label_109"));

        gridLayout_17->addWidget(label_109, 5, 0, 1, 1);

        vect3_fake_lights_orbit_trap_x = new MyLineEdit(groupCheck_fake_lights_enabled);
        vect3_fake_lights_orbit_trap_x->setObjectName(QString::fromUtf8("vect3_fake_lights_orbit_trap_x"));

        gridLayout_17->addWidget(vect3_fake_lights_orbit_trap_x, 8, 2, 1, 1);

        label_position_mode_ = new QLabel(groupCheck_fake_lights_enabled);
        label_position_mode_->setObjectName(QString::fromUtf8("label_position_mode_"));

        gridLayout_17->addWidget(label_position_mode_, 17, 0, 1, 1);

        comboBox_fake_lights_position_mode = new MyComboBox(groupCheck_fake_lights_enabled);
        comboBox_fake_lights_position_mode->addItem(QString());
        comboBox_fake_lights_position_mode->addItem(QString());
        comboBox_fake_lights_position_mode->addItem(QString());
        comboBox_fake_lights_position_mode->addItem(QString());
        comboBox_fake_lights_position_mode->addItem(QString());
        comboBox_fake_lights_position_mode->addItem(QString());
        comboBox_fake_lights_position_mode->addItem(QString());
        comboBox_fake_lights_position_mode->setObjectName(QString::fromUtf8("comboBox_fake_lights_position_mode"));

        gridLayout_17->addWidget(comboBox_fake_lights_position_mode, 17, 1, 1, 2);

        label_transition_speed_ = new QLabel(groupCheck_fake_lights_enabled);
        label_transition_speed_->setObjectName(QString::fromUtf8("label_transition_speed_"));

        gridLayout_17->addWidget(label_transition_speed_, 18, 0, 1, 1);

        spinbox_fake_lights_transition_speed = new MyDoubleSpinBox(groupCheck_fake_lights_enabled);
        spinbox_fake_lights_transition_speed->setObjectName(QString::fromUtf8("spinbox_fake_lights_transition_speed"));
        spinbox_fake_lights_transition_speed->setDecimals(2);
        spinbox_fake_lights_transition_speed->setMinimum(0.000000000000000);
        spinbox_fake_lights_transition_speed->setMaximum(10.000000000000000);
        spinbox_fake_lights_transition_speed->setSingleStep(0.100000000000000);

        gridLayout_17->addWidget(spinbox_fake_lights_transition_speed, 18, 1, 1, 2);


        verticalLayout_39->addLayout(gridLayout_17);

        stackedWidget_fake_lights_mode = new QStackedWidget(groupCheck_fake_lights_enabled);
        stackedWidget_fake_lights_mode->setObjectName(QString::fromUtf8("stackedWidget_fake_lights_mode"));
        page_fake_lights_world = new QWidget();
        page_fake_lights_world->setObjectName(QString::fromUtf8("page_fake_lights_world"));
        verticalLayout_world = new QVBoxLayout(page_fake_lights_world);
        verticalLayout_world->setSpacing(2);
        verticalLayout_world->setObjectName(QString::fromUtf8("verticalLayout_world"));
        verticalLayout_world->setContentsMargins(0, 0, 0, 0);
        groupBox_fake_lights_world = new QGroupBox(page_fake_lights_world);
        groupBox_fake_lights_world->setObjectName(QString::fromUtf8("groupBox_fake_lights_world"));
        gridLayout_world = new QGridLayout(groupBox_fake_lights_world);
        gridLayout_world->setSpacing(2);
        gridLayout_world->setObjectName(QString::fromUtf8("gridLayout_world"));
        label_world_offset = new QLabel(groupBox_fake_lights_world);
        label_world_offset->setObjectName(QString::fromUtf8("label_world_offset"));

        gridLayout_world->addWidget(label_world_offset, 0, 0, 3, 1);

        label_world_offset_x = new QLabel(groupBox_fake_lights_world);
        label_world_offset_x->setObjectName(QString::fromUtf8("label_world_offset_x"));
        label_world_offset_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_world->addWidget(label_world_offset_x, 0, 1, 1, 1);

        vect3_fake_lights_world_offset_x = new MyLineEdit(groupBox_fake_lights_world);
        vect3_fake_lights_world_offset_x->setObjectName(QString::fromUtf8("vect3_fake_lights_world_offset_x"));

        gridLayout_world->addWidget(vect3_fake_lights_world_offset_x, 0, 2, 1, 1);

        label_world_offset_y = new QLabel(groupBox_fake_lights_world);
        label_world_offset_y->setObjectName(QString::fromUtf8("label_world_offset_y"));
        label_world_offset_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_world->addWidget(label_world_offset_y, 1, 1, 1, 1);

        vect3_fake_lights_world_offset_y = new MyLineEdit(groupBox_fake_lights_world);
        vect3_fake_lights_world_offset_y->setObjectName(QString::fromUtf8("vect3_fake_lights_world_offset_y"));

        gridLayout_world->addWidget(vect3_fake_lights_world_offset_y, 1, 2, 1, 1);

        label_world_offset_z = new QLabel(groupBox_fake_lights_world);
        label_world_offset_z->setObjectName(QString::fromUtf8("label_world_offset_z"));
        label_world_offset_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_world->addWidget(label_world_offset_z, 2, 1, 1, 1);

        vect3_fake_lights_world_offset_z = new MyLineEdit(groupBox_fake_lights_world);
        vect3_fake_lights_world_offset_z->setObjectName(QString::fromUtf8("vect3_fake_lights_world_offset_z"));

        gridLayout_world->addWidget(vect3_fake_lights_world_offset_z, 2, 2, 1, 1);

        label_world_scale = new QLabel(groupBox_fake_lights_world);
        label_world_scale->setObjectName(QString::fromUtf8("label_world_scale"));

        gridLayout_world->addWidget(label_world_scale, 3, 0, 1, 1);

        logedit_fake_lights_world_scale = new MyLineEdit(groupBox_fake_lights_world);
        logedit_fake_lights_world_scale->setObjectName(QString::fromUtf8("logedit_fake_lights_world_scale"));

        gridLayout_world->addWidget(logedit_fake_lights_world_scale, 3, 1, 1, 2);

        label_world_rotation = new QLabel(groupBox_fake_lights_world);
        label_world_rotation->setObjectName(QString::fromUtf8("label_world_rotation"));

        gridLayout_world->addWidget(label_world_rotation, 4, 0, 3, 1);

        label_world_rotation_x = new QLabel(groupBox_fake_lights_world);
        label_world_rotation_x->setObjectName(QString::fromUtf8("label_world_rotation_x"));
        label_world_rotation_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_world->addWidget(label_world_rotation_x, 4, 1, 1, 1);

        spinboxd3_fake_lights_world_rotation_x = new MyDoubleSpinBox(groupBox_fake_lights_world);
        spinboxd3_fake_lights_world_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_fake_lights_world_rotation_x"));
        spinboxd3_fake_lights_world_rotation_x->setDecimals(2);
        spinboxd3_fake_lights_world_rotation_x->setMinimum(-36000.000000000000000);
        spinboxd3_fake_lights_world_rotation_x->setMaximum(36000.000000000000000);
        spinboxd3_fake_lights_world_rotation_x->setSingleStep(0.100000000000000);

        gridLayout_world->addWidget(spinboxd3_fake_lights_world_rotation_x, 4, 2, 1, 1);

        label_world_rotation_y = new QLabel(groupBox_fake_lights_world);
        label_world_rotation_y->setObjectName(QString::fromUtf8("label_world_rotation_y"));
        label_world_rotation_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_world->addWidget(label_world_rotation_y, 5, 1, 1, 1);

        spinboxd3_fake_lights_world_rotation_y = new MyDoubleSpinBox(groupBox_fake_lights_world);
        spinboxd3_fake_lights_world_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_fake_lights_world_rotation_y"));
        spinboxd3_fake_lights_world_rotation_y->setDecimals(2);
        spinboxd3_fake_lights_world_rotation_y->setMinimum(-36000.000000000000000);
        spinboxd3_fake_lights_world_rotation_y->setMaximum(36000.000000000000000);
        spinboxd3_fake_lights_world_rotation_y->setSingleStep(0.100000000000000);

        gridLayout_world->addWidget(spinboxd3_fake_lights_world_rotation_y, 5, 2, 1, 1);

        label_world_rotation_z = new QLabel(groupBox_fake_lights_world);
        label_world_rotation_z->setObjectName(QString::fromUtf8("label_world_rotation_z"));
        label_world_rotation_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_world->addWidget(label_world_rotation_z, 6, 1, 1, 1);

        spinboxd3_fake_lights_world_rotation_z = new MyDoubleSpinBox(groupBox_fake_lights_world);
        spinboxd3_fake_lights_world_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_fake_lights_world_rotation_z"));
        spinboxd3_fake_lights_world_rotation_z->setDecimals(2);
        spinboxd3_fake_lights_world_rotation_z->setMinimum(-36000.000000000000000);
        spinboxd3_fake_lights_world_rotation_z->setMaximum(36000.000000000000000);
        spinboxd3_fake_lights_world_rotation_z->setSingleStep(0.100000000000000);

        gridLayout_world->addWidget(spinboxd3_fake_lights_world_rotation_z, 6, 2, 1, 1);


        verticalLayout_world->addWidget(groupBox_fake_lights_world);

        pushButton_reset_world = new QPushButton(page_fake_lights_world);
        pushButton_reset_world->setObjectName(QString::fromUtf8("pushButton_reset_world"));

        verticalLayout_world->addWidget(pushButton_reset_world);

        stackedWidget_fake_lights_mode->addWidget(page_fake_lights_world);
        page_fake_lights_camera = new QWidget();
        page_fake_lights_camera->setObjectName(QString::fromUtf8("page_fake_lights_camera"));
        verticalLayout_camera = new QVBoxLayout(page_fake_lights_camera);
        verticalLayout_camera->setSpacing(2);
        verticalLayout_camera->setObjectName(QString::fromUtf8("verticalLayout_camera"));
        verticalLayout_camera->setContentsMargins(0, 0, 0, 0);
        groupBox_fake_lights_camera = new QGroupBox(page_fake_lights_camera);
        groupBox_fake_lights_camera->setObjectName(QString::fromUtf8("groupBox_fake_lights_camera"));
        gridLayout_camera = new QGridLayout(groupBox_fake_lights_camera);
        gridLayout_camera->setSpacing(2);
        gridLayout_camera->setObjectName(QString::fromUtf8("gridLayout_camera"));
        label_camera_offset = new QLabel(groupBox_fake_lights_camera);
        label_camera_offset->setObjectName(QString::fromUtf8("label_camera_offset"));

        gridLayout_camera->addWidget(label_camera_offset, 0, 0, 3, 1);

        label_camera_offset_x = new QLabel(groupBox_fake_lights_camera);
        label_camera_offset_x->setObjectName(QString::fromUtf8("label_camera_offset_x"));
        label_camera_offset_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_camera->addWidget(label_camera_offset_x, 0, 1, 1, 1);

        vect3_fake_lights_camera_offset_x = new MyLineEdit(groupBox_fake_lights_camera);
        vect3_fake_lights_camera_offset_x->setObjectName(QString::fromUtf8("vect3_fake_lights_camera_offset_x"));

        gridLayout_camera->addWidget(vect3_fake_lights_camera_offset_x, 0, 2, 1, 1);

        label_camera_offset_y = new QLabel(groupBox_fake_lights_camera);
        label_camera_offset_y->setObjectName(QString::fromUtf8("label_camera_offset_y"));
        label_camera_offset_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_camera->addWidget(label_camera_offset_y, 1, 1, 1, 1);

        vect3_fake_lights_camera_offset_y = new MyLineEdit(groupBox_fake_lights_camera);
        vect3_fake_lights_camera_offset_y->setObjectName(QString::fromUtf8("vect3_fake_lights_camera_offset_y"));

        gridLayout_camera->addWidget(vect3_fake_lights_camera_offset_y, 1, 2, 1, 1);

        label_camera_offset_z = new QLabel(groupBox_fake_lights_camera);
        label_camera_offset_z->setObjectName(QString::fromUtf8("label_camera_offset_z"));
        label_camera_offset_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_camera->addWidget(label_camera_offset_z, 2, 1, 1, 1);

        vect3_fake_lights_camera_offset_z = new MyLineEdit(groupBox_fake_lights_camera);
        vect3_fake_lights_camera_offset_z->setObjectName(QString::fromUtf8("vect3_fake_lights_camera_offset_z"));

        gridLayout_camera->addWidget(vect3_fake_lights_camera_offset_z, 2, 2, 1, 1);

        label_camera_scale = new QLabel(groupBox_fake_lights_camera);
        label_camera_scale->setObjectName(QString::fromUtf8("label_camera_scale"));

        gridLayout_camera->addWidget(label_camera_scale, 3, 0, 1, 1);

        logedit_fake_lights_camera_scale = new MyLineEdit(groupBox_fake_lights_camera);
        logedit_fake_lights_camera_scale->setObjectName(QString::fromUtf8("logedit_fake_lights_camera_scale"));

        gridLayout_camera->addWidget(logedit_fake_lights_camera_scale, 3, 1, 1, 2);

        label_camera_rotation = new QLabel(groupBox_fake_lights_camera);
        label_camera_rotation->setObjectName(QString::fromUtf8("label_camera_rotation"));

        gridLayout_camera->addWidget(label_camera_rotation, 4, 0, 3, 1);

        label_camera_rotation_x = new QLabel(groupBox_fake_lights_camera);
        label_camera_rotation_x->setObjectName(QString::fromUtf8("label_camera_rotation_x"));
        label_camera_rotation_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_camera->addWidget(label_camera_rotation_x, 4, 1, 1, 1);

        spinboxd3_fake_lights_camera_rotation_x = new MyDoubleSpinBox(groupBox_fake_lights_camera);
        spinboxd3_fake_lights_camera_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_fake_lights_camera_rotation_x"));
        spinboxd3_fake_lights_camera_rotation_x->setDecimals(2);
        spinboxd3_fake_lights_camera_rotation_x->setMinimum(-36000.000000000000000);
        spinboxd3_fake_lights_camera_rotation_x->setMaximum(36000.000000000000000);
        spinboxd3_fake_lights_camera_rotation_x->setSingleStep(0.100000000000000);

        gridLayout_camera->addWidget(spinboxd3_fake_lights_camera_rotation_x, 4, 2, 1, 1);

        label_camera_rotation_y = new QLabel(groupBox_fake_lights_camera);
        label_camera_rotation_y->setObjectName(QString::fromUtf8("label_camera_rotation_y"));
        label_camera_rotation_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_camera->addWidget(label_camera_rotation_y, 5, 1, 1, 1);

        spinboxd3_fake_lights_camera_rotation_y = new MyDoubleSpinBox(groupBox_fake_lights_camera);
        spinboxd3_fake_lights_camera_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_fake_lights_camera_rotation_y"));
        spinboxd3_fake_lights_camera_rotation_y->setDecimals(2);
        spinboxd3_fake_lights_camera_rotation_y->setMinimum(-36000.000000000000000);
        spinboxd3_fake_lights_camera_rotation_y->setMaximum(36000.000000000000000);
        spinboxd3_fake_lights_camera_rotation_y->setSingleStep(0.100000000000000);

        gridLayout_camera->addWidget(spinboxd3_fake_lights_camera_rotation_y, 5, 2, 1, 1);

        label_camera_rotation_z = new QLabel(groupBox_fake_lights_camera);
        label_camera_rotation_z->setObjectName(QString::fromUtf8("label_camera_rotation_z"));
        label_camera_rotation_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_camera->addWidget(label_camera_rotation_z, 6, 1, 1, 1);

        spinboxd3_fake_lights_camera_rotation_z = new MyDoubleSpinBox(groupBox_fake_lights_camera);
        spinboxd3_fake_lights_camera_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_fake_lights_camera_rotation_z"));
        spinboxd3_fake_lights_camera_rotation_z->setDecimals(2);
        spinboxd3_fake_lights_camera_rotation_z->setMinimum(-36000.000000000000000);
        spinboxd3_fake_lights_camera_rotation_z->setMaximum(36000.000000000000000);
        spinboxd3_fake_lights_camera_rotation_z->setSingleStep(0.100000000000000);

        gridLayout_camera->addWidget(spinboxd3_fake_lights_camera_rotation_z, 6, 2, 1, 1);


        verticalLayout_camera->addWidget(groupBox_fake_lights_camera);

        pushButton_reset_camera = new QPushButton(page_fake_lights_camera);
        pushButton_reset_camera->setObjectName(QString::fromUtf8("pushButton_reset_camera"));

        verticalLayout_camera->addWidget(pushButton_reset_camera);

        stackedWidget_fake_lights_mode->addWidget(page_fake_lights_camera);
        page_fake_lights_target = new QWidget();
        page_fake_lights_target->setObjectName(QString::fromUtf8("page_fake_lights_target"));
        verticalLayout_target = new QVBoxLayout(page_fake_lights_target);
        verticalLayout_target->setSpacing(2);
        verticalLayout_target->setObjectName(QString::fromUtf8("verticalLayout_target"));
        verticalLayout_target->setContentsMargins(0, 0, 0, 0);
        groupBox_fake_lights_target = new QGroupBox(page_fake_lights_target);
        groupBox_fake_lights_target->setObjectName(QString::fromUtf8("groupBox_fake_lights_target"));
        gridLayout_target = new QGridLayout(groupBox_fake_lights_target);
        gridLayout_target->setSpacing(2);
        gridLayout_target->setObjectName(QString::fromUtf8("gridLayout_target"));
        label_target_offset = new QLabel(groupBox_fake_lights_target);
        label_target_offset->setObjectName(QString::fromUtf8("label_target_offset"));

        gridLayout_target->addWidget(label_target_offset, 0, 0, 3, 1);

        label_target_offset_x = new QLabel(groupBox_fake_lights_target);
        label_target_offset_x->setObjectName(QString::fromUtf8("label_target_offset_x"));
        label_target_offset_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_target->addWidget(label_target_offset_x, 0, 1, 1, 1);

        vect3_fake_lights_target_offset_x = new MyLineEdit(groupBox_fake_lights_target);
        vect3_fake_lights_target_offset_x->setObjectName(QString::fromUtf8("vect3_fake_lights_target_offset_x"));

        gridLayout_target->addWidget(vect3_fake_lights_target_offset_x, 0, 2, 1, 1);

        label_target_offset_y = new QLabel(groupBox_fake_lights_target);
        label_target_offset_y->setObjectName(QString::fromUtf8("label_target_offset_y"));
        label_target_offset_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_target->addWidget(label_target_offset_y, 1, 1, 1, 1);

        vect3_fake_lights_target_offset_y = new MyLineEdit(groupBox_fake_lights_target);
        vect3_fake_lights_target_offset_y->setObjectName(QString::fromUtf8("vect3_fake_lights_target_offset_y"));

        gridLayout_target->addWidget(vect3_fake_lights_target_offset_y, 1, 2, 1, 1);

        label_target_offset_z = new QLabel(groupBox_fake_lights_target);
        label_target_offset_z->setObjectName(QString::fromUtf8("label_target_offset_z"));
        label_target_offset_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_target->addWidget(label_target_offset_z, 2, 1, 1, 1);

        vect3_fake_lights_target_offset_z = new MyLineEdit(groupBox_fake_lights_target);
        vect3_fake_lights_target_offset_z->setObjectName(QString::fromUtf8("vect3_fake_lights_target_offset_z"));

        gridLayout_target->addWidget(vect3_fake_lights_target_offset_z, 2, 2, 1, 1);

        label_target_scale = new QLabel(groupBox_fake_lights_target);
        label_target_scale->setObjectName(QString::fromUtf8("label_target_scale"));

        gridLayout_target->addWidget(label_target_scale, 3, 0, 1, 1);

        logedit_fake_lights_target_scale = new MyLineEdit(groupBox_fake_lights_target);
        logedit_fake_lights_target_scale->setObjectName(QString::fromUtf8("logedit_fake_lights_target_scale"));

        gridLayout_target->addWidget(logedit_fake_lights_target_scale, 3, 1, 1, 2);

        label_target_rotation = new QLabel(groupBox_fake_lights_target);
        label_target_rotation->setObjectName(QString::fromUtf8("label_target_rotation"));

        gridLayout_target->addWidget(label_target_rotation, 4, 0, 3, 1);

        label_target_rotation_x = new QLabel(groupBox_fake_lights_target);
        label_target_rotation_x->setObjectName(QString::fromUtf8("label_target_rotation_x"));
        label_target_rotation_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_target->addWidget(label_target_rotation_x, 4, 1, 1, 1);

        spinboxd3_fake_lights_target_rotation_x = new MyDoubleSpinBox(groupBox_fake_lights_target);
        spinboxd3_fake_lights_target_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_fake_lights_target_rotation_x"));
        spinboxd3_fake_lights_target_rotation_x->setDecimals(2);
        spinboxd3_fake_lights_target_rotation_x->setMinimum(-36000.000000000000000);
        spinboxd3_fake_lights_target_rotation_x->setMaximum(36000.000000000000000);
        spinboxd3_fake_lights_target_rotation_x->setSingleStep(0.100000000000000);

        gridLayout_target->addWidget(spinboxd3_fake_lights_target_rotation_x, 4, 2, 1, 1);

        label_target_rotation_y = new QLabel(groupBox_fake_lights_target);
        label_target_rotation_y->setObjectName(QString::fromUtf8("label_target_rotation_y"));
        label_target_rotation_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_target->addWidget(label_target_rotation_y, 5, 1, 1, 1);

        spinboxd3_fake_lights_target_rotation_y = new MyDoubleSpinBox(groupBox_fake_lights_target);
        spinboxd3_fake_lights_target_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_fake_lights_target_rotation_y"));
        spinboxd3_fake_lights_target_rotation_y->setDecimals(2);
        spinboxd3_fake_lights_target_rotation_y->setMinimum(-36000.000000000000000);
        spinboxd3_fake_lights_target_rotation_y->setMaximum(36000.000000000000000);
        spinboxd3_fake_lights_target_rotation_y->setSingleStep(0.100000000000000);

        gridLayout_target->addWidget(spinboxd3_fake_lights_target_rotation_y, 5, 2, 1, 1);

        label_target_rotation_z = new QLabel(groupBox_fake_lights_target);
        label_target_rotation_z->setObjectName(QString::fromUtf8("label_target_rotation_z"));
        label_target_rotation_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_target->addWidget(label_target_rotation_z, 6, 1, 1, 1);

        spinboxd3_fake_lights_target_rotation_z = new MyDoubleSpinBox(groupBox_fake_lights_target);
        spinboxd3_fake_lights_target_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_fake_lights_target_rotation_z"));
        spinboxd3_fake_lights_target_rotation_z->setDecimals(2);
        spinboxd3_fake_lights_target_rotation_z->setMinimum(-36000.000000000000000);
        spinboxd3_fake_lights_target_rotation_z->setMaximum(36000.000000000000000);
        spinboxd3_fake_lights_target_rotation_z->setSingleStep(0.100000000000000);

        gridLayout_target->addWidget(spinboxd3_fake_lights_target_rotation_z, 6, 2, 1, 1);


        verticalLayout_target->addWidget(groupBox_fake_lights_target);

        pushButton_reset_target = new QPushButton(page_fake_lights_target);
        pushButton_reset_target->setObjectName(QString::fromUtf8("pushButton_reset_target"));

        verticalLayout_target->addWidget(pushButton_reset_target);

        stackedWidget_fake_lights_mode->addWidget(page_fake_lights_target);
        page_fake_lights_fractal_center = new QWidget();
        page_fake_lights_fractal_center->setObjectName(QString::fromUtf8("page_fake_lights_fractal_center"));
        verticalLayout_fractal_center = new QVBoxLayout(page_fake_lights_fractal_center);
        verticalLayout_fractal_center->setSpacing(2);
        verticalLayout_fractal_center->setObjectName(QString::fromUtf8("verticalLayout_fractal_center"));
        verticalLayout_fractal_center->setContentsMargins(0, 0, 0, 0);
        groupBox_fake_lights_fractal_center = new QGroupBox(page_fake_lights_fractal_center);
        groupBox_fake_lights_fractal_center->setObjectName(QString::fromUtf8("groupBox_fake_lights_fractal_center"));
        gridLayout_fractal_center = new QGridLayout(groupBox_fake_lights_fractal_center);
        gridLayout_fractal_center->setSpacing(2);
        gridLayout_fractal_center->setObjectName(QString::fromUtf8("gridLayout_fractal_center"));
        label_fractal_center_offset = new QLabel(groupBox_fake_lights_fractal_center);
        label_fractal_center_offset->setObjectName(QString::fromUtf8("label_fractal_center_offset"));

        gridLayout_fractal_center->addWidget(label_fractal_center_offset, 0, 0, 3, 1);

        label_fractal_center_offset_x = new QLabel(groupBox_fake_lights_fractal_center);
        label_fractal_center_offset_x->setObjectName(QString::fromUtf8("label_fractal_center_offset_x"));
        label_fractal_center_offset_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_fractal_center->addWidget(label_fractal_center_offset_x, 0, 1, 1, 1);

        vect3_fake_lights_fractal_center_offset_x = new MyLineEdit(groupBox_fake_lights_fractal_center);
        vect3_fake_lights_fractal_center_offset_x->setObjectName(QString::fromUtf8("vect3_fake_lights_fractal_center_offset_x"));

        gridLayout_fractal_center->addWidget(vect3_fake_lights_fractal_center_offset_x, 0, 2, 1, 1);

        label_fractal_center_offset_y = new QLabel(groupBox_fake_lights_fractal_center);
        label_fractal_center_offset_y->setObjectName(QString::fromUtf8("label_fractal_center_offset_y"));
        label_fractal_center_offset_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_fractal_center->addWidget(label_fractal_center_offset_y, 1, 1, 1, 1);

        vect3_fake_lights_fractal_center_offset_y = new MyLineEdit(groupBox_fake_lights_fractal_center);
        vect3_fake_lights_fractal_center_offset_y->setObjectName(QString::fromUtf8("vect3_fake_lights_fractal_center_offset_y"));

        gridLayout_fractal_center->addWidget(vect3_fake_lights_fractal_center_offset_y, 1, 2, 1, 1);

        label_fractal_center_offset_z = new QLabel(groupBox_fake_lights_fractal_center);
        label_fractal_center_offset_z->setObjectName(QString::fromUtf8("label_fractal_center_offset_z"));
        label_fractal_center_offset_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_fractal_center->addWidget(label_fractal_center_offset_z, 2, 1, 1, 1);

        vect3_fake_lights_fractal_center_offset_z = new MyLineEdit(groupBox_fake_lights_fractal_center);
        vect3_fake_lights_fractal_center_offset_z->setObjectName(QString::fromUtf8("vect3_fake_lights_fractal_center_offset_z"));

        gridLayout_fractal_center->addWidget(vect3_fake_lights_fractal_center_offset_z, 2, 2, 1, 1);

        label_fractal_center_scale = new QLabel(groupBox_fake_lights_fractal_center);
        label_fractal_center_scale->setObjectName(QString::fromUtf8("label_fractal_center_scale"));

        gridLayout_fractal_center->addWidget(label_fractal_center_scale, 3, 0, 1, 1);

        logedit_fake_lights_fractal_center_scale = new MyLineEdit(groupBox_fake_lights_fractal_center);
        logedit_fake_lights_fractal_center_scale->setObjectName(QString::fromUtf8("logedit_fake_lights_fractal_center_scale"));

        gridLayout_fractal_center->addWidget(logedit_fake_lights_fractal_center_scale, 3, 1, 1, 2);

        label_fractal_center_rotation = new QLabel(groupBox_fake_lights_fractal_center);
        label_fractal_center_rotation->setObjectName(QString::fromUtf8("label_fractal_center_rotation"));

        gridLayout_fractal_center->addWidget(label_fractal_center_rotation, 4, 0, 3, 1);

        label_fractal_center_rotation_x = new QLabel(groupBox_fake_lights_fractal_center);
        label_fractal_center_rotation_x->setObjectName(QString::fromUtf8("label_fractal_center_rotation_x"));
        label_fractal_center_rotation_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_fractal_center->addWidget(label_fractal_center_rotation_x, 4, 1, 1, 1);

        spinboxd3_fake_lights_fractal_center_rotation_x = new MyDoubleSpinBox(groupBox_fake_lights_fractal_center);
        spinboxd3_fake_lights_fractal_center_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_fake_lights_fractal_center_rotation_x"));
        spinboxd3_fake_lights_fractal_center_rotation_x->setDecimals(2);
        spinboxd3_fake_lights_fractal_center_rotation_x->setMinimum(-36000.000000000000000);
        spinboxd3_fake_lights_fractal_center_rotation_x->setMaximum(36000.000000000000000);
        spinboxd3_fake_lights_fractal_center_rotation_x->setSingleStep(0.100000000000000);

        gridLayout_fractal_center->addWidget(spinboxd3_fake_lights_fractal_center_rotation_x, 4, 2, 1, 1);

        label_fractal_center_rotation_y = new QLabel(groupBox_fake_lights_fractal_center);
        label_fractal_center_rotation_y->setObjectName(QString::fromUtf8("label_fractal_center_rotation_y"));
        label_fractal_center_rotation_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_fractal_center->addWidget(label_fractal_center_rotation_y, 5, 1, 1, 1);

        spinboxd3_fake_lights_fractal_center_rotation_y = new MyDoubleSpinBox(groupBox_fake_lights_fractal_center);
        spinboxd3_fake_lights_fractal_center_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_fake_lights_fractal_center_rotation_y"));
        spinboxd3_fake_lights_fractal_center_rotation_y->setDecimals(2);
        spinboxd3_fake_lights_fractal_center_rotation_y->setMinimum(-36000.000000000000000);
        spinboxd3_fake_lights_fractal_center_rotation_y->setMaximum(36000.000000000000000);
        spinboxd3_fake_lights_fractal_center_rotation_y->setSingleStep(0.100000000000000);

        gridLayout_fractal_center->addWidget(spinboxd3_fake_lights_fractal_center_rotation_y, 5, 2, 1, 1);

        label_fractal_center_rotation_z = new QLabel(groupBox_fake_lights_fractal_center);
        label_fractal_center_rotation_z->setObjectName(QString::fromUtf8("label_fractal_center_rotation_z"));
        label_fractal_center_rotation_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_fractal_center->addWidget(label_fractal_center_rotation_z, 6, 1, 1, 1);

        spinboxd3_fake_lights_fractal_center_rotation_z = new MyDoubleSpinBox(groupBox_fake_lights_fractal_center);
        spinboxd3_fake_lights_fractal_center_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_fake_lights_fractal_center_rotation_z"));
        spinboxd3_fake_lights_fractal_center_rotation_z->setDecimals(2);
        spinboxd3_fake_lights_fractal_center_rotation_z->setMinimum(-36000.000000000000000);
        spinboxd3_fake_lights_fractal_center_rotation_z->setMaximum(36000.000000000000000);
        spinboxd3_fake_lights_fractal_center_rotation_z->setSingleStep(0.100000000000000);

        gridLayout_fractal_center->addWidget(spinboxd3_fake_lights_fractal_center_rotation_z, 6, 2, 1, 1);


        verticalLayout_fractal_center->addWidget(groupBox_fake_lights_fractal_center);

        pushButton_reset_fractal_center = new QPushButton(page_fake_lights_fractal_center);
        pushButton_reset_fractal_center->setObjectName(QString::fromUtf8("pushButton_reset_fractal_center"));

        verticalLayout_fractal_center->addWidget(pushButton_reset_fractal_center);

        stackedWidget_fake_lights_mode->addWidget(page_fake_lights_fractal_center);
        page_fake_lights_path_circle = new QWidget();
        page_fake_lights_path_circle->setObjectName(QString::fromUtf8("page_fake_lights_path_circle"));
        verticalLayout_path_circle = new QVBoxLayout(page_fake_lights_path_circle);
        verticalLayout_path_circle->setSpacing(2);
        verticalLayout_path_circle->setObjectName(QString::fromUtf8("verticalLayout_path_circle"));
        verticalLayout_path_circle->setContentsMargins(0, 0, 0, 0);
        groupBox_fake_lights_path_circle = new QGroupBox(page_fake_lights_path_circle);
        groupBox_fake_lights_path_circle->setObjectName(QString::fromUtf8("groupBox_fake_lights_path_circle"));
        gridLayout_path_circle = new QGridLayout(groupBox_fake_lights_path_circle);
        gridLayout_path_circle->setSpacing(2);
        gridLayout_path_circle->setObjectName(QString::fromUtf8("gridLayout_path_circle"));
        label_path_circle_offset = new QLabel(groupBox_fake_lights_path_circle);
        label_path_circle_offset->setObjectName(QString::fromUtf8("label_path_circle_offset"));

        gridLayout_path_circle->addWidget(label_path_circle_offset, 0, 0, 3, 1);

        label_path_circle_offset_x = new QLabel(groupBox_fake_lights_path_circle);
        label_path_circle_offset_x->setObjectName(QString::fromUtf8("label_path_circle_offset_x"));
        label_path_circle_offset_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_path_circle->addWidget(label_path_circle_offset_x, 0, 1, 1, 1);

        vect3_fake_lights_path_circle_offset_x = new MyLineEdit(groupBox_fake_lights_path_circle);
        vect3_fake_lights_path_circle_offset_x->setObjectName(QString::fromUtf8("vect3_fake_lights_path_circle_offset_x"));

        gridLayout_path_circle->addWidget(vect3_fake_lights_path_circle_offset_x, 0, 2, 1, 1);

        label_path_circle_offset_y = new QLabel(groupBox_fake_lights_path_circle);
        label_path_circle_offset_y->setObjectName(QString::fromUtf8("label_path_circle_offset_y"));
        label_path_circle_offset_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_path_circle->addWidget(label_path_circle_offset_y, 1, 1, 1, 1);

        vect3_fake_lights_path_circle_offset_y = new MyLineEdit(groupBox_fake_lights_path_circle);
        vect3_fake_lights_path_circle_offset_y->setObjectName(QString::fromUtf8("vect3_fake_lights_path_circle_offset_y"));

        gridLayout_path_circle->addWidget(vect3_fake_lights_path_circle_offset_y, 1, 2, 1, 1);

        label_path_circle_offset_z = new QLabel(groupBox_fake_lights_path_circle);
        label_path_circle_offset_z->setObjectName(QString::fromUtf8("label_path_circle_offset_z"));
        label_path_circle_offset_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_path_circle->addWidget(label_path_circle_offset_z, 2, 1, 1, 1);

        vect3_fake_lights_path_circle_offset_z = new MyLineEdit(groupBox_fake_lights_path_circle);
        vect3_fake_lights_path_circle_offset_z->setObjectName(QString::fromUtf8("vect3_fake_lights_path_circle_offset_z"));

        gridLayout_path_circle->addWidget(vect3_fake_lights_path_circle_offset_z, 2, 2, 1, 1);

        label_path_circle_scale = new QLabel(groupBox_fake_lights_path_circle);
        label_path_circle_scale->setObjectName(QString::fromUtf8("label_path_circle_scale"));

        gridLayout_path_circle->addWidget(label_path_circle_scale, 3, 0, 1, 1);

        logedit_fake_lights_path_circle_scale = new MyLineEdit(groupBox_fake_lights_path_circle);
        logedit_fake_lights_path_circle_scale->setObjectName(QString::fromUtf8("logedit_fake_lights_path_circle_scale"));

        gridLayout_path_circle->addWidget(logedit_fake_lights_path_circle_scale, 3, 1, 1, 2);

        label_path_circle_rotation = new QLabel(groupBox_fake_lights_path_circle);
        label_path_circle_rotation->setObjectName(QString::fromUtf8("label_path_circle_rotation"));

        gridLayout_path_circle->addWidget(label_path_circle_rotation, 4, 0, 3, 1);

        label_path_circle_rotation_x = new QLabel(groupBox_fake_lights_path_circle);
        label_path_circle_rotation_x->setObjectName(QString::fromUtf8("label_path_circle_rotation_x"));
        label_path_circle_rotation_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_path_circle->addWidget(label_path_circle_rotation_x, 4, 1, 1, 1);

        spinboxd3_fake_lights_path_circle_rotation_x = new MyDoubleSpinBox(groupBox_fake_lights_path_circle);
        spinboxd3_fake_lights_path_circle_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_fake_lights_path_circle_rotation_x"));
        spinboxd3_fake_lights_path_circle_rotation_x->setDecimals(2);
        spinboxd3_fake_lights_path_circle_rotation_x->setMinimum(-36000.000000000000000);
        spinboxd3_fake_lights_path_circle_rotation_x->setMaximum(36000.000000000000000);
        spinboxd3_fake_lights_path_circle_rotation_x->setSingleStep(0.100000000000000);

        gridLayout_path_circle->addWidget(spinboxd3_fake_lights_path_circle_rotation_x, 4, 2, 1, 1);

        label_path_circle_rotation_y = new QLabel(groupBox_fake_lights_path_circle);
        label_path_circle_rotation_y->setObjectName(QString::fromUtf8("label_path_circle_rotation_y"));
        label_path_circle_rotation_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_path_circle->addWidget(label_path_circle_rotation_y, 5, 1, 1, 1);

        spinboxd3_fake_lights_path_circle_rotation_y = new MyDoubleSpinBox(groupBox_fake_lights_path_circle);
        spinboxd3_fake_lights_path_circle_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_fake_lights_path_circle_rotation_y"));
        spinboxd3_fake_lights_path_circle_rotation_y->setDecimals(2);
        spinboxd3_fake_lights_path_circle_rotation_y->setMinimum(-36000.000000000000000);
        spinboxd3_fake_lights_path_circle_rotation_y->setMaximum(36000.000000000000000);
        spinboxd3_fake_lights_path_circle_rotation_y->setSingleStep(0.100000000000000);

        gridLayout_path_circle->addWidget(spinboxd3_fake_lights_path_circle_rotation_y, 5, 2, 1, 1);

        label_path_circle_rotation_z = new QLabel(groupBox_fake_lights_path_circle);
        label_path_circle_rotation_z->setObjectName(QString::fromUtf8("label_path_circle_rotation_z"));
        label_path_circle_rotation_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_path_circle->addWidget(label_path_circle_rotation_z, 6, 1, 1, 1);

        spinboxd3_fake_lights_path_circle_rotation_z = new MyDoubleSpinBox(groupBox_fake_lights_path_circle);
        spinboxd3_fake_lights_path_circle_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_fake_lights_path_circle_rotation_z"));
        spinboxd3_fake_lights_path_circle_rotation_z->setDecimals(2);
        spinboxd3_fake_lights_path_circle_rotation_z->setMinimum(-36000.000000000000000);
        spinboxd3_fake_lights_path_circle_rotation_z->setMaximum(36000.000000000000000);
        spinboxd3_fake_lights_path_circle_rotation_z->setSingleStep(0.100000000000000);

        gridLayout_path_circle->addWidget(spinboxd3_fake_lights_path_circle_rotation_z, 6, 2, 1, 1);

        label_path_circle_radius = new QLabel(groupBox_fake_lights_path_circle);
        label_path_circle_radius->setObjectName(QString::fromUtf8("label_path_circle_radius"));

        gridLayout_path_circle->addWidget(label_path_circle_radius, 7, 0, 1, 1);

        spinbox_fake_lights_path_circle_path_radius = new MyDoubleSpinBox(groupBox_fake_lights_path_circle);
        spinbox_fake_lights_path_circle_path_radius->setObjectName(QString::fromUtf8("spinbox_fake_lights_path_circle_path_radius"));
        spinbox_fake_lights_path_circle_path_radius->setDecimals(3);
        spinbox_fake_lights_path_circle_path_radius->setMinimum(0.000000000000000);
        spinbox_fake_lights_path_circle_path_radius->setMaximum(10000.000000000000000);
        spinbox_fake_lights_path_circle_path_radius->setSingleStep(0.100000000000000);

        gridLayout_path_circle->addWidget(spinbox_fake_lights_path_circle_path_radius, 7, 1, 1, 2);


        verticalLayout_path_circle->addWidget(groupBox_fake_lights_path_circle);

        pushButton_reset_path_circle = new QPushButton(page_fake_lights_path_circle);
        pushButton_reset_path_circle->setObjectName(QString::fromUtf8("pushButton_reset_path_circle"));

        verticalLayout_path_circle->addWidget(pushButton_reset_path_circle);

        stackedWidget_fake_lights_mode->addWidget(page_fake_lights_path_circle);
        page_fake_lights_path_spiral = new QWidget();
        page_fake_lights_path_spiral->setObjectName(QString::fromUtf8("page_fake_lights_path_spiral"));
        verticalLayout_path_spiral = new QVBoxLayout(page_fake_lights_path_spiral);
        verticalLayout_path_spiral->setSpacing(2);
        verticalLayout_path_spiral->setObjectName(QString::fromUtf8("verticalLayout_path_spiral"));
        verticalLayout_path_spiral->setContentsMargins(0, 0, 0, 0);
        groupBox_fake_lights_path_spiral = new QGroupBox(page_fake_lights_path_spiral);
        groupBox_fake_lights_path_spiral->setObjectName(QString::fromUtf8("groupBox_fake_lights_path_spiral"));
        gridLayout_path_spiral = new QGridLayout(groupBox_fake_lights_path_spiral);
        gridLayout_path_spiral->setSpacing(2);
        gridLayout_path_spiral->setObjectName(QString::fromUtf8("gridLayout_path_spiral"));
        label_path_spiral_offset = new QLabel(groupBox_fake_lights_path_spiral);
        label_path_spiral_offset->setObjectName(QString::fromUtf8("label_path_spiral_offset"));

        gridLayout_path_spiral->addWidget(label_path_spiral_offset, 0, 0, 3, 1);

        label_path_spiral_offset_x = new QLabel(groupBox_fake_lights_path_spiral);
        label_path_spiral_offset_x->setObjectName(QString::fromUtf8("label_path_spiral_offset_x"));
        label_path_spiral_offset_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_path_spiral->addWidget(label_path_spiral_offset_x, 0, 1, 1, 1);

        vect3_fake_lights_path_spiral_offset_x = new MyLineEdit(groupBox_fake_lights_path_spiral);
        vect3_fake_lights_path_spiral_offset_x->setObjectName(QString::fromUtf8("vect3_fake_lights_path_spiral_offset_x"));

        gridLayout_path_spiral->addWidget(vect3_fake_lights_path_spiral_offset_x, 0, 2, 1, 1);

        label_path_spiral_offset_y = new QLabel(groupBox_fake_lights_path_spiral);
        label_path_spiral_offset_y->setObjectName(QString::fromUtf8("label_path_spiral_offset_y"));
        label_path_spiral_offset_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_path_spiral->addWidget(label_path_spiral_offset_y, 1, 1, 1, 1);

        vect3_fake_lights_path_spiral_offset_y = new MyLineEdit(groupBox_fake_lights_path_spiral);
        vect3_fake_lights_path_spiral_offset_y->setObjectName(QString::fromUtf8("vect3_fake_lights_path_spiral_offset_y"));

        gridLayout_path_spiral->addWidget(vect3_fake_lights_path_spiral_offset_y, 1, 2, 1, 1);

        label_path_spiral_offset_z = new QLabel(groupBox_fake_lights_path_spiral);
        label_path_spiral_offset_z->setObjectName(QString::fromUtf8("label_path_spiral_offset_z"));
        label_path_spiral_offset_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_path_spiral->addWidget(label_path_spiral_offset_z, 2, 1, 1, 1);

        vect3_fake_lights_path_spiral_offset_z = new MyLineEdit(groupBox_fake_lights_path_spiral);
        vect3_fake_lights_path_spiral_offset_z->setObjectName(QString::fromUtf8("vect3_fake_lights_path_spiral_offset_z"));

        gridLayout_path_spiral->addWidget(vect3_fake_lights_path_spiral_offset_z, 2, 2, 1, 1);

        label_path_spiral_scale = new QLabel(groupBox_fake_lights_path_spiral);
        label_path_spiral_scale->setObjectName(QString::fromUtf8("label_path_spiral_scale"));

        gridLayout_path_spiral->addWidget(label_path_spiral_scale, 3, 0, 1, 1);

        logedit_fake_lights_path_spiral_scale = new MyLineEdit(groupBox_fake_lights_path_spiral);
        logedit_fake_lights_path_spiral_scale->setObjectName(QString::fromUtf8("logedit_fake_lights_path_spiral_scale"));

        gridLayout_path_spiral->addWidget(logedit_fake_lights_path_spiral_scale, 3, 1, 1, 2);

        label_path_spiral_rotation = new QLabel(groupBox_fake_lights_path_spiral);
        label_path_spiral_rotation->setObjectName(QString::fromUtf8("label_path_spiral_rotation"));

        gridLayout_path_spiral->addWidget(label_path_spiral_rotation, 4, 0, 3, 1);

        label_path_spiral_rotation_x = new QLabel(groupBox_fake_lights_path_spiral);
        label_path_spiral_rotation_x->setObjectName(QString::fromUtf8("label_path_spiral_rotation_x"));
        label_path_spiral_rotation_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_path_spiral->addWidget(label_path_spiral_rotation_x, 4, 1, 1, 1);

        spinboxd3_fake_lights_path_spiral_rotation_x = new MyDoubleSpinBox(groupBox_fake_lights_path_spiral);
        spinboxd3_fake_lights_path_spiral_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_fake_lights_path_spiral_rotation_x"));
        spinboxd3_fake_lights_path_spiral_rotation_x->setDecimals(2);
        spinboxd3_fake_lights_path_spiral_rotation_x->setMinimum(-36000.000000000000000);
        spinboxd3_fake_lights_path_spiral_rotation_x->setMaximum(36000.000000000000000);
        spinboxd3_fake_lights_path_spiral_rotation_x->setSingleStep(0.100000000000000);

        gridLayout_path_spiral->addWidget(spinboxd3_fake_lights_path_spiral_rotation_x, 4, 2, 1, 1);

        label_path_spiral_rotation_y = new QLabel(groupBox_fake_lights_path_spiral);
        label_path_spiral_rotation_y->setObjectName(QString::fromUtf8("label_path_spiral_rotation_y"));
        label_path_spiral_rotation_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_path_spiral->addWidget(label_path_spiral_rotation_y, 5, 1, 1, 1);

        spinboxd3_fake_lights_path_spiral_rotation_y = new MyDoubleSpinBox(groupBox_fake_lights_path_spiral);
        spinboxd3_fake_lights_path_spiral_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_fake_lights_path_spiral_rotation_y"));
        spinboxd3_fake_lights_path_spiral_rotation_y->setDecimals(2);
        spinboxd3_fake_lights_path_spiral_rotation_y->setMinimum(-36000.000000000000000);
        spinboxd3_fake_lights_path_spiral_rotation_y->setMaximum(36000.000000000000000);
        spinboxd3_fake_lights_path_spiral_rotation_y->setSingleStep(0.100000000000000);

        gridLayout_path_spiral->addWidget(spinboxd3_fake_lights_path_spiral_rotation_y, 5, 2, 1, 1);

        label_path_spiral_rotation_z = new QLabel(groupBox_fake_lights_path_spiral);
        label_path_spiral_rotation_z->setObjectName(QString::fromUtf8("label_path_spiral_rotation_z"));
        label_path_spiral_rotation_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_path_spiral->addWidget(label_path_spiral_rotation_z, 6, 1, 1, 1);

        spinboxd3_fake_lights_path_spiral_rotation_z = new MyDoubleSpinBox(groupBox_fake_lights_path_spiral);
        spinboxd3_fake_lights_path_spiral_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_fake_lights_path_spiral_rotation_z"));
        spinboxd3_fake_lights_path_spiral_rotation_z->setDecimals(2);
        spinboxd3_fake_lights_path_spiral_rotation_z->setMinimum(-36000.000000000000000);
        spinboxd3_fake_lights_path_spiral_rotation_z->setMaximum(36000.000000000000000);
        spinboxd3_fake_lights_path_spiral_rotation_z->setSingleStep(0.100000000000000);

        gridLayout_path_spiral->addWidget(spinboxd3_fake_lights_path_spiral_rotation_z, 6, 2, 1, 1);

        label_path_spiral_radius = new QLabel(groupBox_fake_lights_path_spiral);
        label_path_spiral_radius->setObjectName(QString::fromUtf8("label_path_spiral_radius"));

        gridLayout_path_spiral->addWidget(label_path_spiral_radius, 7, 0, 1, 1);

        spinbox_fake_lights_path_spiral_path_radius = new MyDoubleSpinBox(groupBox_fake_lights_path_spiral);
        spinbox_fake_lights_path_spiral_path_radius->setObjectName(QString::fromUtf8("spinbox_fake_lights_path_spiral_path_radius"));
        spinbox_fake_lights_path_spiral_path_radius->setDecimals(3);
        spinbox_fake_lights_path_spiral_path_radius->setMinimum(0.000000000000000);
        spinbox_fake_lights_path_spiral_path_radius->setMaximum(10000.000000000000000);
        spinbox_fake_lights_path_spiral_path_radius->setSingleStep(0.100000000000000);

        gridLayout_path_spiral->addWidget(spinbox_fake_lights_path_spiral_path_radius, 7, 1, 1, 2);


        verticalLayout_path_spiral->addWidget(groupBox_fake_lights_path_spiral);

        pushButton_reset_path_spiral = new QPushButton(page_fake_lights_path_spiral);
        pushButton_reset_path_spiral->setObjectName(QString::fromUtf8("pushButton_reset_path_spiral"));

        verticalLayout_path_spiral->addWidget(pushButton_reset_path_spiral);

        stackedWidget_fake_lights_mode->addWidget(page_fake_lights_path_spiral);
        page_fake_lights_orbit_target = new QWidget();
        page_fake_lights_orbit_target->setObjectName(QString::fromUtf8("page_fake_lights_orbit_target"));
        verticalLayout_orbit_target = new QVBoxLayout(page_fake_lights_orbit_target);
        verticalLayout_orbit_target->setSpacing(2);
        verticalLayout_orbit_target->setObjectName(QString::fromUtf8("verticalLayout_orbit_target"));
        verticalLayout_orbit_target->setContentsMargins(0, 0, 0, 0);
        groupBox_fake_lights_orbit_target = new QGroupBox(page_fake_lights_orbit_target);
        groupBox_fake_lights_orbit_target->setObjectName(QString::fromUtf8("groupBox_fake_lights_orbit_target"));
        gridLayout_orbit_target = new QGridLayout(groupBox_fake_lights_orbit_target);
        gridLayout_orbit_target->setSpacing(2);
        gridLayout_orbit_target->setObjectName(QString::fromUtf8("gridLayout_orbit_target"));
        label_orbit_target_offset = new QLabel(groupBox_fake_lights_orbit_target);
        label_orbit_target_offset->setObjectName(QString::fromUtf8("label_orbit_target_offset"));

        gridLayout_orbit_target->addWidget(label_orbit_target_offset, 0, 0, 3, 1);

        label_orbit_target_offset_x = new QLabel(groupBox_fake_lights_orbit_target);
        label_orbit_target_offset_x->setObjectName(QString::fromUtf8("label_orbit_target_offset_x"));
        label_orbit_target_offset_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_orbit_target->addWidget(label_orbit_target_offset_x, 0, 1, 1, 1);

        vect3_fake_lights_orbit_target_offset_x = new MyLineEdit(groupBox_fake_lights_orbit_target);
        vect3_fake_lights_orbit_target_offset_x->setObjectName(QString::fromUtf8("vect3_fake_lights_orbit_target_offset_x"));

        gridLayout_orbit_target->addWidget(vect3_fake_lights_orbit_target_offset_x, 0, 2, 1, 1);

        label_orbit_target_offset_y = new QLabel(groupBox_fake_lights_orbit_target);
        label_orbit_target_offset_y->setObjectName(QString::fromUtf8("label_orbit_target_offset_y"));
        label_orbit_target_offset_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_orbit_target->addWidget(label_orbit_target_offset_y, 1, 1, 1, 1);

        vect3_fake_lights_orbit_target_offset_y = new MyLineEdit(groupBox_fake_lights_orbit_target);
        vect3_fake_lights_orbit_target_offset_y->setObjectName(QString::fromUtf8("vect3_fake_lights_orbit_target_offset_y"));

        gridLayout_orbit_target->addWidget(vect3_fake_lights_orbit_target_offset_y, 1, 2, 1, 1);

        label_orbit_target_offset_z = new QLabel(groupBox_fake_lights_orbit_target);
        label_orbit_target_offset_z->setObjectName(QString::fromUtf8("label_orbit_target_offset_z"));
        label_orbit_target_offset_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_orbit_target->addWidget(label_orbit_target_offset_z, 2, 1, 1, 1);

        vect3_fake_lights_orbit_target_offset_z = new MyLineEdit(groupBox_fake_lights_orbit_target);
        vect3_fake_lights_orbit_target_offset_z->setObjectName(QString::fromUtf8("vect3_fake_lights_orbit_target_offset_z"));

        gridLayout_orbit_target->addWidget(vect3_fake_lights_orbit_target_offset_z, 2, 2, 1, 1);

        label_orbit_target_scale = new QLabel(groupBox_fake_lights_orbit_target);
        label_orbit_target_scale->setObjectName(QString::fromUtf8("label_orbit_target_scale"));

        gridLayout_orbit_target->addWidget(label_orbit_target_scale, 3, 0, 1, 1);

        logedit_fake_lights_orbit_target_scale = new MyLineEdit(groupBox_fake_lights_orbit_target);
        logedit_fake_lights_orbit_target_scale->setObjectName(QString::fromUtf8("logedit_fake_lights_orbit_target_scale"));

        gridLayout_orbit_target->addWidget(logedit_fake_lights_orbit_target_scale, 3, 1, 1, 2);

        label_orbit_target_rotation = new QLabel(groupBox_fake_lights_orbit_target);
        label_orbit_target_rotation->setObjectName(QString::fromUtf8("label_orbit_target_rotation"));

        gridLayout_orbit_target->addWidget(label_orbit_target_rotation, 4, 0, 3, 1);

        label_orbit_target_rotation_x = new QLabel(groupBox_fake_lights_orbit_target);
        label_orbit_target_rotation_x->setObjectName(QString::fromUtf8("label_orbit_target_rotation_x"));
        label_orbit_target_rotation_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_orbit_target->addWidget(label_orbit_target_rotation_x, 4, 1, 1, 1);

        spinboxd3_fake_lights_orbit_target_rotation_x = new MyDoubleSpinBox(groupBox_fake_lights_orbit_target);
        spinboxd3_fake_lights_orbit_target_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_fake_lights_orbit_target_rotation_x"));
        spinboxd3_fake_lights_orbit_target_rotation_x->setDecimals(2);
        spinboxd3_fake_lights_orbit_target_rotation_x->setMinimum(-36000.000000000000000);
        spinboxd3_fake_lights_orbit_target_rotation_x->setMaximum(36000.000000000000000);
        spinboxd3_fake_lights_orbit_target_rotation_x->setSingleStep(0.100000000000000);

        gridLayout_orbit_target->addWidget(spinboxd3_fake_lights_orbit_target_rotation_x, 4, 2, 1, 1);

        label_orbit_target_rotation_y = new QLabel(groupBox_fake_lights_orbit_target);
        label_orbit_target_rotation_y->setObjectName(QString::fromUtf8("label_orbit_target_rotation_y"));
        label_orbit_target_rotation_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_orbit_target->addWidget(label_orbit_target_rotation_y, 5, 1, 1, 1);

        spinboxd3_fake_lights_orbit_target_rotation_y = new MyDoubleSpinBox(groupBox_fake_lights_orbit_target);
        spinboxd3_fake_lights_orbit_target_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_fake_lights_orbit_target_rotation_y"));
        spinboxd3_fake_lights_orbit_target_rotation_y->setDecimals(2);
        spinboxd3_fake_lights_orbit_target_rotation_y->setMinimum(-36000.000000000000000);
        spinboxd3_fake_lights_orbit_target_rotation_y->setMaximum(36000.000000000000000);
        spinboxd3_fake_lights_orbit_target_rotation_y->setSingleStep(0.100000000000000);

        gridLayout_orbit_target->addWidget(spinboxd3_fake_lights_orbit_target_rotation_y, 5, 2, 1, 1);

        label_orbit_target_rotation_z = new QLabel(groupBox_fake_lights_orbit_target);
        label_orbit_target_rotation_z->setObjectName(QString::fromUtf8("label_orbit_target_rotation_z"));
        label_orbit_target_rotation_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_orbit_target->addWidget(label_orbit_target_rotation_z, 6, 1, 1, 1);

        spinboxd3_fake_lights_orbit_target_rotation_z = new MyDoubleSpinBox(groupBox_fake_lights_orbit_target);
        spinboxd3_fake_lights_orbit_target_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_fake_lights_orbit_target_rotation_z"));
        spinboxd3_fake_lights_orbit_target_rotation_z->setDecimals(2);
        spinboxd3_fake_lights_orbit_target_rotation_z->setMinimum(-36000.000000000000000);
        spinboxd3_fake_lights_orbit_target_rotation_z->setMaximum(36000.000000000000000);
        spinboxd3_fake_lights_orbit_target_rotation_z->setSingleStep(0.100000000000000);

        gridLayout_orbit_target->addWidget(spinboxd3_fake_lights_orbit_target_rotation_z, 6, 2, 1, 1);

        label_orbit_target_radius = new QLabel(groupBox_fake_lights_orbit_target);
        label_orbit_target_radius->setObjectName(QString::fromUtf8("label_orbit_target_radius"));

        gridLayout_orbit_target->addWidget(label_orbit_target_radius, 7, 0, 1, 1);

        spinbox_fake_lights_orbit_target_path_radius = new MyDoubleSpinBox(groupBox_fake_lights_orbit_target);
        spinbox_fake_lights_orbit_target_path_radius->setObjectName(QString::fromUtf8("spinbox_fake_lights_orbit_target_path_radius"));
        spinbox_fake_lights_orbit_target_path_radius->setDecimals(3);
        spinbox_fake_lights_orbit_target_path_radius->setMinimum(0.000000000000000);
        spinbox_fake_lights_orbit_target_path_radius->setMaximum(10000.000000000000000);
        spinbox_fake_lights_orbit_target_path_radius->setSingleStep(0.100000000000000);

        gridLayout_orbit_target->addWidget(spinbox_fake_lights_orbit_target_path_radius, 7, 1, 1, 2);


        verticalLayout_orbit_target->addWidget(groupBox_fake_lights_orbit_target);

        pushButton_reset_orbit_target = new QPushButton(page_fake_lights_orbit_target);
        pushButton_reset_orbit_target->setObjectName(QString::fromUtf8("pushButton_reset_orbit_target"));

        verticalLayout_orbit_target->addWidget(pushButton_reset_orbit_target);

        stackedWidget_fake_lights_mode->addWidget(page_fake_lights_orbit_target);

        verticalLayout_39->addWidget(stackedWidget_fake_lights_mode);

        groupBox_fake_lights_multi_center = new QGroupBox(groupCheck_fake_lights_enabled);
        groupBox_fake_lights_multi_center->setObjectName(QString::fromUtf8("groupBox_fake_lights_multi_center"));
        gridLayout_multi_center = new QGridLayout(groupBox_fake_lights_multi_center);
        gridLayout_multi_center->setSpacing(2);
        gridLayout_multi_center->setObjectName(QString::fromUtf8("gridLayout_multi_center"));
        checkBox_fake_lights_multi_center_enabled = new MyCheckBox(groupBox_fake_lights_multi_center);
        checkBox_fake_lights_multi_center_enabled->setObjectName(QString::fromUtf8("checkBox_fake_lights_multi_center_enabled"));

        gridLayout_multi_center->addWidget(checkBox_fake_lights_multi_center_enabled, 0, 0, 1, 7);

        label_multi_center_1 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_1->setObjectName(QString::fromUtf8("label_multi_center_1"));

        gridLayout_multi_center->addWidget(label_multi_center_1, 1, 0, 3, 1);

        label_multi_center_1_x = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_1_x->setObjectName(QString::fromUtf8("label_multi_center_1_x"));
        label_multi_center_1_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_1_x, 1, 1, 1, 1);

        vect3_fake_lights_multi_center_1_x = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_1_x->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_1_x"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_1_x, 1, 2, 1, 1);

        label_multi_center_1_y = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_1_y->setObjectName(QString::fromUtf8("label_multi_center_1_y"));
        label_multi_center_1_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_1_y, 2, 1, 1, 1);

        vect3_fake_lights_multi_center_1_y = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_1_y->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_1_y"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_1_y, 2, 2, 1, 1);

        label_multi_center_1_z = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_1_z->setObjectName(QString::fromUtf8("label_multi_center_1_z"));
        label_multi_center_1_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_1_z, 3, 1, 1, 1);

        vect3_fake_lights_multi_center_1_z = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_1_z->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_1_z"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_1_z, 3, 2, 1, 1);

        label_multi_center_weight_1 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_weight_1->setObjectName(QString::fromUtf8("label_multi_center_weight_1"));

        gridLayout_multi_center->addWidget(label_multi_center_weight_1, 1, 3, 1, 1);

        spinbox_fake_lights_multi_center_weight_1 = new MyDoubleSpinBox(groupBox_fake_lights_multi_center);
        spinbox_fake_lights_multi_center_weight_1->setObjectName(QString::fromUtf8("spinbox_fake_lights_multi_center_weight_1"));
        spinbox_fake_lights_multi_center_weight_1->setDecimals(3);
        spinbox_fake_lights_multi_center_weight_1->setMinimum(0.000000000000000);
        spinbox_fake_lights_multi_center_weight_1->setMaximum(100.000000000000000);
        spinbox_fake_lights_multi_center_weight_1->setSingleStep(0.100000000000000);

        gridLayout_multi_center->addWidget(spinbox_fake_lights_multi_center_weight_1, 1, 4, 1, 1);

        label_multi_center_color_1 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_color_1->setObjectName(QString::fromUtf8("label_multi_center_color_1"));

        gridLayout_multi_center->addWidget(label_multi_center_color_1, 1, 5, 1, 1);

        colorButton_fake_lights_multi_center_color_1 = new MyColorButton(groupBox_fake_lights_multi_center);
        colorButton_fake_lights_multi_center_color_1->setObjectName(QString::fromUtf8("colorButton_fake_lights_multi_center_color_1"));

        gridLayout_multi_center->addWidget(colorButton_fake_lights_multi_center_color_1, 1, 6, 1, 1);

        line_multi_center_sep_4 = new QFrame(groupBox_fake_lights_multi_center);
        line_multi_center_sep_4->setObjectName(QString::fromUtf8("line_multi_center_sep_4"));
        line_multi_center_sep_4->setFrameShape(QFrame::HLine);
        line_multi_center_sep_4->setFrameShadow(QFrame::Sunken);

        gridLayout_multi_center->addWidget(line_multi_center_sep_4, 4, 0, 1, 7);

        label_multi_center_2 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_2->setObjectName(QString::fromUtf8("label_multi_center_2"));

        gridLayout_multi_center->addWidget(label_multi_center_2, 5, 0, 3, 1);

        label_multi_center_2_x = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_2_x->setObjectName(QString::fromUtf8("label_multi_center_2_x"));
        label_multi_center_2_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_2_x, 5, 1, 1, 1);

        vect3_fake_lights_multi_center_2_x = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_2_x->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_2_x"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_2_x, 5, 2, 1, 1);

        label_multi_center_2_y = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_2_y->setObjectName(QString::fromUtf8("label_multi_center_2_y"));
        label_multi_center_2_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_2_y, 6, 1, 1, 1);

        vect3_fake_lights_multi_center_2_y = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_2_y->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_2_y"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_2_y, 6, 2, 1, 1);

        label_multi_center_2_z = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_2_z->setObjectName(QString::fromUtf8("label_multi_center_2_z"));
        label_multi_center_2_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_2_z, 7, 1, 1, 1);

        vect3_fake_lights_multi_center_2_z = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_2_z->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_2_z"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_2_z, 7, 2, 1, 1);

        label_multi_center_weight_2 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_weight_2->setObjectName(QString::fromUtf8("label_multi_center_weight_2"));

        gridLayout_multi_center->addWidget(label_multi_center_weight_2, 5, 3, 1, 1);

        spinbox_fake_lights_multi_center_weight_2 = new MyDoubleSpinBox(groupBox_fake_lights_multi_center);
        spinbox_fake_lights_multi_center_weight_2->setObjectName(QString::fromUtf8("spinbox_fake_lights_multi_center_weight_2"));
        spinbox_fake_lights_multi_center_weight_2->setDecimals(3);
        spinbox_fake_lights_multi_center_weight_2->setMinimum(0.000000000000000);
        spinbox_fake_lights_multi_center_weight_2->setMaximum(100.000000000000000);
        spinbox_fake_lights_multi_center_weight_2->setSingleStep(0.100000000000000);

        gridLayout_multi_center->addWidget(spinbox_fake_lights_multi_center_weight_2, 5, 4, 1, 1);

        label_multi_center_color_2 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_color_2->setObjectName(QString::fromUtf8("label_multi_center_color_2"));

        gridLayout_multi_center->addWidget(label_multi_center_color_2, 5, 5, 1, 1);

        colorButton_fake_lights_multi_center_color_2 = new MyColorButton(groupBox_fake_lights_multi_center);
        colorButton_fake_lights_multi_center_color_2->setObjectName(QString::fromUtf8("colorButton_fake_lights_multi_center_color_2"));

        gridLayout_multi_center->addWidget(colorButton_fake_lights_multi_center_color_2, 5, 6, 1, 1);

        line_multi_center_sep_8 = new QFrame(groupBox_fake_lights_multi_center);
        line_multi_center_sep_8->setObjectName(QString::fromUtf8("line_multi_center_sep_8"));
        line_multi_center_sep_8->setFrameShape(QFrame::HLine);
        line_multi_center_sep_8->setFrameShadow(QFrame::Sunken);

        gridLayout_multi_center->addWidget(line_multi_center_sep_8, 8, 0, 1, 7);

        label_multi_center_3 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_3->setObjectName(QString::fromUtf8("label_multi_center_3"));

        gridLayout_multi_center->addWidget(label_multi_center_3, 9, 0, 3, 1);

        label_multi_center_3_x = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_3_x->setObjectName(QString::fromUtf8("label_multi_center_3_x"));
        label_multi_center_3_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_3_x, 9, 1, 1, 1);

        vect3_fake_lights_multi_center_3_x = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_3_x->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_3_x"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_3_x, 9, 2, 1, 1);

        label_multi_center_3_y = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_3_y->setObjectName(QString::fromUtf8("label_multi_center_3_y"));
        label_multi_center_3_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_3_y, 10, 1, 1, 1);

        vect3_fake_lights_multi_center_3_y = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_3_y->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_3_y"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_3_y, 10, 2, 1, 1);

        label_multi_center_3_z = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_3_z->setObjectName(QString::fromUtf8("label_multi_center_3_z"));
        label_multi_center_3_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_3_z, 11, 1, 1, 1);

        vect3_fake_lights_multi_center_3_z = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_3_z->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_3_z"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_3_z, 11, 2, 1, 1);

        label_multi_center_weight_3 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_weight_3->setObjectName(QString::fromUtf8("label_multi_center_weight_3"));

        gridLayout_multi_center->addWidget(label_multi_center_weight_3, 9, 3, 1, 1);

        spinbox_fake_lights_multi_center_weight_3 = new MyDoubleSpinBox(groupBox_fake_lights_multi_center);
        spinbox_fake_lights_multi_center_weight_3->setObjectName(QString::fromUtf8("spinbox_fake_lights_multi_center_weight_3"));
        spinbox_fake_lights_multi_center_weight_3->setDecimals(3);
        spinbox_fake_lights_multi_center_weight_3->setMinimum(0.000000000000000);
        spinbox_fake_lights_multi_center_weight_3->setMaximum(100.000000000000000);
        spinbox_fake_lights_multi_center_weight_3->setSingleStep(0.100000000000000);

        gridLayout_multi_center->addWidget(spinbox_fake_lights_multi_center_weight_3, 9, 4, 1, 1);

        label_multi_center_color_3 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_color_3->setObjectName(QString::fromUtf8("label_multi_center_color_3"));

        gridLayout_multi_center->addWidget(label_multi_center_color_3, 9, 5, 1, 1);

        colorButton_fake_lights_multi_center_color_3 = new MyColorButton(groupBox_fake_lights_multi_center);
        colorButton_fake_lights_multi_center_color_3->setObjectName(QString::fromUtf8("colorButton_fake_lights_multi_center_color_3"));

        gridLayout_multi_center->addWidget(colorButton_fake_lights_multi_center_color_3, 9, 6, 1, 1);

        line_multi_center_sep_12 = new QFrame(groupBox_fake_lights_multi_center);
        line_multi_center_sep_12->setObjectName(QString::fromUtf8("line_multi_center_sep_12"));
        line_multi_center_sep_12->setFrameShape(QFrame::HLine);
        line_multi_center_sep_12->setFrameShadow(QFrame::Sunken);

        gridLayout_multi_center->addWidget(line_multi_center_sep_12, 12, 0, 1, 7);

        label_multi_center_4 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_4->setObjectName(QString::fromUtf8("label_multi_center_4"));

        gridLayout_multi_center->addWidget(label_multi_center_4, 13, 0, 3, 1);

        label_multi_center_4_x = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_4_x->setObjectName(QString::fromUtf8("label_multi_center_4_x"));
        label_multi_center_4_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_4_x, 13, 1, 1, 1);

        vect3_fake_lights_multi_center_4_x = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_4_x->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_4_x"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_4_x, 13, 2, 1, 1);

        label_multi_center_4_y = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_4_y->setObjectName(QString::fromUtf8("label_multi_center_4_y"));
        label_multi_center_4_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_4_y, 14, 1, 1, 1);

        vect3_fake_lights_multi_center_4_y = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_4_y->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_4_y"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_4_y, 14, 2, 1, 1);

        label_multi_center_4_z = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_4_z->setObjectName(QString::fromUtf8("label_multi_center_4_z"));
        label_multi_center_4_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_4_z, 15, 1, 1, 1);

        vect3_fake_lights_multi_center_4_z = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_4_z->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_4_z"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_4_z, 15, 2, 1, 1);

        label_multi_center_weight_4 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_weight_4->setObjectName(QString::fromUtf8("label_multi_center_weight_4"));

        gridLayout_multi_center->addWidget(label_multi_center_weight_4, 13, 3, 1, 1);

        spinbox_fake_lights_multi_center_weight_4 = new MyDoubleSpinBox(groupBox_fake_lights_multi_center);
        spinbox_fake_lights_multi_center_weight_4->setObjectName(QString::fromUtf8("spinbox_fake_lights_multi_center_weight_4"));
        spinbox_fake_lights_multi_center_weight_4->setDecimals(3);
        spinbox_fake_lights_multi_center_weight_4->setMinimum(0.000000000000000);
        spinbox_fake_lights_multi_center_weight_4->setMaximum(100.000000000000000);
        spinbox_fake_lights_multi_center_weight_4->setSingleStep(0.100000000000000);

        gridLayout_multi_center->addWidget(spinbox_fake_lights_multi_center_weight_4, 13, 4, 1, 1);

        label_multi_center_color_4 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_color_4->setObjectName(QString::fromUtf8("label_multi_center_color_4"));

        gridLayout_multi_center->addWidget(label_multi_center_color_4, 13, 5, 1, 1);

        colorButton_fake_lights_multi_center_color_4 = new MyColorButton(groupBox_fake_lights_multi_center);
        colorButton_fake_lights_multi_center_color_4->setObjectName(QString::fromUtf8("colorButton_fake_lights_multi_center_color_4"));

        gridLayout_multi_center->addWidget(colorButton_fake_lights_multi_center_color_4, 13, 6, 1, 1);

        line_multi_center_sep_16 = new QFrame(groupBox_fake_lights_multi_center);
        line_multi_center_sep_16->setObjectName(QString::fromUtf8("line_multi_center_sep_16"));
        line_multi_center_sep_16->setFrameShape(QFrame::HLine);
        line_multi_center_sep_16->setFrameShadow(QFrame::Sunken);

        gridLayout_multi_center->addWidget(line_multi_center_sep_16, 16, 0, 1, 7);

        label_multi_center_5 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_5->setObjectName(QString::fromUtf8("label_multi_center_5"));

        gridLayout_multi_center->addWidget(label_multi_center_5, 17, 0, 3, 1);

        label_multi_center_5_x = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_5_x->setObjectName(QString::fromUtf8("label_multi_center_5_x"));
        label_multi_center_5_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_5_x, 17, 1, 1, 1);

        vect3_fake_lights_multi_center_5_x = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_5_x->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_5_x"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_5_x, 17, 2, 1, 1);

        label_multi_center_5_y = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_5_y->setObjectName(QString::fromUtf8("label_multi_center_5_y"));
        label_multi_center_5_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_5_y, 18, 1, 1, 1);

        vect3_fake_lights_multi_center_5_y = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_5_y->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_5_y"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_5_y, 18, 2, 1, 1);

        label_multi_center_5_z = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_5_z->setObjectName(QString::fromUtf8("label_multi_center_5_z"));
        label_multi_center_5_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_5_z, 19, 1, 1, 1);

        vect3_fake_lights_multi_center_5_z = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_5_z->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_5_z"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_5_z, 19, 2, 1, 1);

        label_multi_center_weight_5 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_weight_5->setObjectName(QString::fromUtf8("label_multi_center_weight_5"));

        gridLayout_multi_center->addWidget(label_multi_center_weight_5, 17, 3, 1, 1);

        spinbox_fake_lights_multi_center_weight_5 = new MyDoubleSpinBox(groupBox_fake_lights_multi_center);
        spinbox_fake_lights_multi_center_weight_5->setObjectName(QString::fromUtf8("spinbox_fake_lights_multi_center_weight_5"));
        spinbox_fake_lights_multi_center_weight_5->setDecimals(3);
        spinbox_fake_lights_multi_center_weight_5->setMinimum(0.000000000000000);
        spinbox_fake_lights_multi_center_weight_5->setMaximum(100.000000000000000);
        spinbox_fake_lights_multi_center_weight_5->setSingleStep(0.100000000000000);

        gridLayout_multi_center->addWidget(spinbox_fake_lights_multi_center_weight_5, 17, 4, 1, 1);

        label_multi_center_color_5 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_color_5->setObjectName(QString::fromUtf8("label_multi_center_color_5"));

        gridLayout_multi_center->addWidget(label_multi_center_color_5, 17, 5, 1, 1);

        colorButton_fake_lights_multi_center_color_5 = new MyColorButton(groupBox_fake_lights_multi_center);
        colorButton_fake_lights_multi_center_color_5->setObjectName(QString::fromUtf8("colorButton_fake_lights_multi_center_color_5"));

        gridLayout_multi_center->addWidget(colorButton_fake_lights_multi_center_color_5, 17, 6, 1, 1);

        line_multi_center_sep_20 = new QFrame(groupBox_fake_lights_multi_center);
        line_multi_center_sep_20->setObjectName(QString::fromUtf8("line_multi_center_sep_20"));
        line_multi_center_sep_20->setFrameShape(QFrame::HLine);
        line_multi_center_sep_20->setFrameShadow(QFrame::Sunken);

        gridLayout_multi_center->addWidget(line_multi_center_sep_20, 20, 0, 1, 7);

        label_multi_center_6 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_6->setObjectName(QString::fromUtf8("label_multi_center_6"));

        gridLayout_multi_center->addWidget(label_multi_center_6, 21, 0, 3, 1);

        label_multi_center_6_x = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_6_x->setObjectName(QString::fromUtf8("label_multi_center_6_x"));
        label_multi_center_6_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_6_x, 21, 1, 1, 1);

        vect3_fake_lights_multi_center_6_x = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_6_x->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_6_x"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_6_x, 21, 2, 1, 1);

        label_multi_center_6_y = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_6_y->setObjectName(QString::fromUtf8("label_multi_center_6_y"));
        label_multi_center_6_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_6_y, 22, 1, 1, 1);

        vect3_fake_lights_multi_center_6_y = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_6_y->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_6_y"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_6_y, 22, 2, 1, 1);

        label_multi_center_6_z = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_6_z->setObjectName(QString::fromUtf8("label_multi_center_6_z"));
        label_multi_center_6_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_6_z, 23, 1, 1, 1);

        vect3_fake_lights_multi_center_6_z = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_6_z->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_6_z"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_6_z, 23, 2, 1, 1);

        label_multi_center_weight_6 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_weight_6->setObjectName(QString::fromUtf8("label_multi_center_weight_6"));

        gridLayout_multi_center->addWidget(label_multi_center_weight_6, 21, 3, 1, 1);

        spinbox_fake_lights_multi_center_weight_6 = new MyDoubleSpinBox(groupBox_fake_lights_multi_center);
        spinbox_fake_lights_multi_center_weight_6->setObjectName(QString::fromUtf8("spinbox_fake_lights_multi_center_weight_6"));
        spinbox_fake_lights_multi_center_weight_6->setDecimals(3);
        spinbox_fake_lights_multi_center_weight_6->setMinimum(0.000000000000000);
        spinbox_fake_lights_multi_center_weight_6->setMaximum(100.000000000000000);
        spinbox_fake_lights_multi_center_weight_6->setSingleStep(0.100000000000000);

        gridLayout_multi_center->addWidget(spinbox_fake_lights_multi_center_weight_6, 21, 4, 1, 1);

        label_multi_center_color_6 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_color_6->setObjectName(QString::fromUtf8("label_multi_center_color_6"));

        gridLayout_multi_center->addWidget(label_multi_center_color_6, 21, 5, 1, 1);

        colorButton_fake_lights_multi_center_color_6 = new MyColorButton(groupBox_fake_lights_multi_center);
        colorButton_fake_lights_multi_center_color_6->setObjectName(QString::fromUtf8("colorButton_fake_lights_multi_center_color_6"));

        gridLayout_multi_center->addWidget(colorButton_fake_lights_multi_center_color_6, 21, 6, 1, 1);

        line_multi_center_sep_24 = new QFrame(groupBox_fake_lights_multi_center);
        line_multi_center_sep_24->setObjectName(QString::fromUtf8("line_multi_center_sep_24"));
        line_multi_center_sep_24->setFrameShape(QFrame::HLine);
        line_multi_center_sep_24->setFrameShadow(QFrame::Sunken);

        gridLayout_multi_center->addWidget(line_multi_center_sep_24, 24, 0, 1, 7);

        label_multi_center_7 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_7->setObjectName(QString::fromUtf8("label_multi_center_7"));

        gridLayout_multi_center->addWidget(label_multi_center_7, 25, 0, 3, 1);

        label_multi_center_7_x = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_7_x->setObjectName(QString::fromUtf8("label_multi_center_7_x"));
        label_multi_center_7_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_7_x, 25, 1, 1, 1);

        vect3_fake_lights_multi_center_7_x = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_7_x->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_7_x"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_7_x, 25, 2, 1, 1);

        label_multi_center_7_y = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_7_y->setObjectName(QString::fromUtf8("label_multi_center_7_y"));
        label_multi_center_7_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_7_y, 26, 1, 1, 1);

        vect3_fake_lights_multi_center_7_y = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_7_y->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_7_y"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_7_y, 26, 2, 1, 1);

        label_multi_center_7_z = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_7_z->setObjectName(QString::fromUtf8("label_multi_center_7_z"));
        label_multi_center_7_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_7_z, 27, 1, 1, 1);

        vect3_fake_lights_multi_center_7_z = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_7_z->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_7_z"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_7_z, 27, 2, 1, 1);

        label_multi_center_weight_7 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_weight_7->setObjectName(QString::fromUtf8("label_multi_center_weight_7"));

        gridLayout_multi_center->addWidget(label_multi_center_weight_7, 25, 3, 1, 1);

        spinbox_fake_lights_multi_center_weight_7 = new MyDoubleSpinBox(groupBox_fake_lights_multi_center);
        spinbox_fake_lights_multi_center_weight_7->setObjectName(QString::fromUtf8("spinbox_fake_lights_multi_center_weight_7"));
        spinbox_fake_lights_multi_center_weight_7->setDecimals(3);
        spinbox_fake_lights_multi_center_weight_7->setMinimum(0.000000000000000);
        spinbox_fake_lights_multi_center_weight_7->setMaximum(100.000000000000000);
        spinbox_fake_lights_multi_center_weight_7->setSingleStep(0.100000000000000);

        gridLayout_multi_center->addWidget(spinbox_fake_lights_multi_center_weight_7, 25, 4, 1, 1);

        label_multi_center_color_7 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_color_7->setObjectName(QString::fromUtf8("label_multi_center_color_7"));

        gridLayout_multi_center->addWidget(label_multi_center_color_7, 25, 5, 1, 1);

        colorButton_fake_lights_multi_center_color_7 = new MyColorButton(groupBox_fake_lights_multi_center);
        colorButton_fake_lights_multi_center_color_7->setObjectName(QString::fromUtf8("colorButton_fake_lights_multi_center_color_7"));

        gridLayout_multi_center->addWidget(colorButton_fake_lights_multi_center_color_7, 25, 6, 1, 1);

        line_multi_center_sep_28 = new QFrame(groupBox_fake_lights_multi_center);
        line_multi_center_sep_28->setObjectName(QString::fromUtf8("line_multi_center_sep_28"));
        line_multi_center_sep_28->setFrameShape(QFrame::HLine);
        line_multi_center_sep_28->setFrameShadow(QFrame::Sunken);

        gridLayout_multi_center->addWidget(line_multi_center_sep_28, 28, 0, 1, 7);

        label_multi_center_8 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_8->setObjectName(QString::fromUtf8("label_multi_center_8"));

        gridLayout_multi_center->addWidget(label_multi_center_8, 29, 0, 3, 1);

        label_multi_center_8_x = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_8_x->setObjectName(QString::fromUtf8("label_multi_center_8_x"));
        label_multi_center_8_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_8_x, 29, 1, 1, 1);

        vect3_fake_lights_multi_center_8_x = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_8_x->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_8_x"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_8_x, 29, 2, 1, 1);

        label_multi_center_8_y = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_8_y->setObjectName(QString::fromUtf8("label_multi_center_8_y"));
        label_multi_center_8_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_8_y, 30, 1, 1, 1);

        vect3_fake_lights_multi_center_8_y = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_8_y->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_8_y"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_8_y, 30, 2, 1, 1);

        label_multi_center_8_z = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_8_z->setObjectName(QString::fromUtf8("label_multi_center_8_z"));
        label_multi_center_8_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_8_z, 31, 1, 1, 1);

        vect3_fake_lights_multi_center_8_z = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_8_z->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_8_z"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_8_z, 31, 2, 1, 1);

        label_multi_center_weight_8 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_weight_8->setObjectName(QString::fromUtf8("label_multi_center_weight_8"));

        gridLayout_multi_center->addWidget(label_multi_center_weight_8, 29, 3, 1, 1);

        spinbox_fake_lights_multi_center_weight_8 = new MyDoubleSpinBox(groupBox_fake_lights_multi_center);
        spinbox_fake_lights_multi_center_weight_8->setObjectName(QString::fromUtf8("spinbox_fake_lights_multi_center_weight_8"));
        spinbox_fake_lights_multi_center_weight_8->setDecimals(3);
        spinbox_fake_lights_multi_center_weight_8->setMinimum(0.000000000000000);
        spinbox_fake_lights_multi_center_weight_8->setMaximum(100.000000000000000);
        spinbox_fake_lights_multi_center_weight_8->setSingleStep(0.100000000000000);

        gridLayout_multi_center->addWidget(spinbox_fake_lights_multi_center_weight_8, 29, 4, 1, 1);

        label_multi_center_color_8 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_color_8->setObjectName(QString::fromUtf8("label_multi_center_color_8"));

        gridLayout_multi_center->addWidget(label_multi_center_color_8, 29, 5, 1, 1);

        colorButton_fake_lights_multi_center_color_8 = new MyColorButton(groupBox_fake_lights_multi_center);
        colorButton_fake_lights_multi_center_color_8->setObjectName(QString::fromUtf8("colorButton_fake_lights_multi_center_color_8"));

        gridLayout_multi_center->addWidget(colorButton_fake_lights_multi_center_color_8, 29, 6, 1, 1);

        line_multi_center_sep_32 = new QFrame(groupBox_fake_lights_multi_center);
        line_multi_center_sep_32->setObjectName(QString::fromUtf8("line_multi_center_sep_32"));
        line_multi_center_sep_32->setFrameShape(QFrame::HLine);
        line_multi_center_sep_32->setFrameShadow(QFrame::Sunken);

        gridLayout_multi_center->addWidget(line_multi_center_sep_32, 32, 0, 1, 7);

        label_multi_center_9 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_9->setObjectName(QString::fromUtf8("label_multi_center_9"));

        gridLayout_multi_center->addWidget(label_multi_center_9, 33, 0, 3, 1);

        label_multi_center_9_x = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_9_x->setObjectName(QString::fromUtf8("label_multi_center_9_x"));
        label_multi_center_9_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_9_x, 33, 1, 1, 1);

        vect3_fake_lights_multi_center_9_x = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_9_x->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_9_x"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_9_x, 33, 2, 1, 1);

        label_multi_center_9_y = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_9_y->setObjectName(QString::fromUtf8("label_multi_center_9_y"));
        label_multi_center_9_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_9_y, 34, 1, 1, 1);

        vect3_fake_lights_multi_center_9_y = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_9_y->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_9_y"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_9_y, 34, 2, 1, 1);

        label_multi_center_9_z = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_9_z->setObjectName(QString::fromUtf8("label_multi_center_9_z"));
        label_multi_center_9_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_9_z, 35, 1, 1, 1);

        vect3_fake_lights_multi_center_9_z = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_9_z->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_9_z"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_9_z, 35, 2, 1, 1);

        label_multi_center_weight_9 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_weight_9->setObjectName(QString::fromUtf8("label_multi_center_weight_9"));

        gridLayout_multi_center->addWidget(label_multi_center_weight_9, 33, 3, 1, 1);

        spinbox_fake_lights_multi_center_weight_9 = new MyDoubleSpinBox(groupBox_fake_lights_multi_center);
        spinbox_fake_lights_multi_center_weight_9->setObjectName(QString::fromUtf8("spinbox_fake_lights_multi_center_weight_9"));
        spinbox_fake_lights_multi_center_weight_9->setDecimals(3);
        spinbox_fake_lights_multi_center_weight_9->setMinimum(0.000000000000000);
        spinbox_fake_lights_multi_center_weight_9->setMaximum(100.000000000000000);
        spinbox_fake_lights_multi_center_weight_9->setSingleStep(0.100000000000000);

        gridLayout_multi_center->addWidget(spinbox_fake_lights_multi_center_weight_9, 33, 4, 1, 1);

        label_multi_center_color_9 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_color_9->setObjectName(QString::fromUtf8("label_multi_center_color_9"));

        gridLayout_multi_center->addWidget(label_multi_center_color_9, 33, 5, 1, 1);

        colorButton_fake_lights_multi_center_color_9 = new MyColorButton(groupBox_fake_lights_multi_center);
        colorButton_fake_lights_multi_center_color_9->setObjectName(QString::fromUtf8("colorButton_fake_lights_multi_center_color_9"));

        gridLayout_multi_center->addWidget(colorButton_fake_lights_multi_center_color_9, 33, 6, 1, 1);

        line_multi_center_sep_36 = new QFrame(groupBox_fake_lights_multi_center);
        line_multi_center_sep_36->setObjectName(QString::fromUtf8("line_multi_center_sep_36"));
        line_multi_center_sep_36->setFrameShape(QFrame::HLine);
        line_multi_center_sep_36->setFrameShadow(QFrame::Sunken);

        gridLayout_multi_center->addWidget(line_multi_center_sep_36, 36, 0, 1, 7);

        label_multi_center_10 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_10->setObjectName(QString::fromUtf8("label_multi_center_10"));

        gridLayout_multi_center->addWidget(label_multi_center_10, 37, 0, 3, 1);

        label_multi_center_10_x = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_10_x->setObjectName(QString::fromUtf8("label_multi_center_10_x"));
        label_multi_center_10_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_10_x, 37, 1, 1, 1);

        vect3_fake_lights_multi_center_10_x = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_10_x->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_10_x"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_10_x, 37, 2, 1, 1);

        label_multi_center_10_y = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_10_y->setObjectName(QString::fromUtf8("label_multi_center_10_y"));
        label_multi_center_10_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_10_y, 38, 1, 1, 1);

        vect3_fake_lights_multi_center_10_y = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_10_y->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_10_y"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_10_y, 38, 2, 1, 1);

        label_multi_center_10_z = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_10_z->setObjectName(QString::fromUtf8("label_multi_center_10_z"));
        label_multi_center_10_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_10_z, 39, 1, 1, 1);

        vect3_fake_lights_multi_center_10_z = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_10_z->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_10_z"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_10_z, 39, 2, 1, 1);

        label_multi_center_weight_10 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_weight_10->setObjectName(QString::fromUtf8("label_multi_center_weight_10"));

        gridLayout_multi_center->addWidget(label_multi_center_weight_10, 37, 3, 1, 1);

        spinbox_fake_lights_multi_center_weight_10 = new MyDoubleSpinBox(groupBox_fake_lights_multi_center);
        spinbox_fake_lights_multi_center_weight_10->setObjectName(QString::fromUtf8("spinbox_fake_lights_multi_center_weight_10"));
        spinbox_fake_lights_multi_center_weight_10->setDecimals(3);
        spinbox_fake_lights_multi_center_weight_10->setMinimum(0.000000000000000);
        spinbox_fake_lights_multi_center_weight_10->setMaximum(100.000000000000000);
        spinbox_fake_lights_multi_center_weight_10->setSingleStep(0.100000000000000);

        gridLayout_multi_center->addWidget(spinbox_fake_lights_multi_center_weight_10, 37, 4, 1, 1);

        label_multi_center_color_10 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_color_10->setObjectName(QString::fromUtf8("label_multi_center_color_10"));

        gridLayout_multi_center->addWidget(label_multi_center_color_10, 37, 5, 1, 1);

        colorButton_fake_lights_multi_center_color_10 = new MyColorButton(groupBox_fake_lights_multi_center);
        colorButton_fake_lights_multi_center_color_10->setObjectName(QString::fromUtf8("colorButton_fake_lights_multi_center_color_10"));

        gridLayout_multi_center->addWidget(colorButton_fake_lights_multi_center_color_10, 37, 6, 1, 1);

        line_multi_center_sep_40 = new QFrame(groupBox_fake_lights_multi_center);
        line_multi_center_sep_40->setObjectName(QString::fromUtf8("line_multi_center_sep_40"));
        line_multi_center_sep_40->setFrameShape(QFrame::HLine);
        line_multi_center_sep_40->setFrameShadow(QFrame::Sunken);

        gridLayout_multi_center->addWidget(line_multi_center_sep_40, 40, 0, 1, 7);

        label_multi_center_11 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_11->setObjectName(QString::fromUtf8("label_multi_center_11"));

        gridLayout_multi_center->addWidget(label_multi_center_11, 41, 0, 3, 1);

        label_multi_center_11_x = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_11_x->setObjectName(QString::fromUtf8("label_multi_center_11_x"));
        label_multi_center_11_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_11_x, 41, 1, 1, 1);

        vect3_fake_lights_multi_center_11_x = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_11_x->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_11_x"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_11_x, 41, 2, 1, 1);

        label_multi_center_11_y = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_11_y->setObjectName(QString::fromUtf8("label_multi_center_11_y"));
        label_multi_center_11_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_11_y, 42, 1, 1, 1);

        vect3_fake_lights_multi_center_11_y = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_11_y->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_11_y"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_11_y, 42, 2, 1, 1);

        label_multi_center_11_z = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_11_z->setObjectName(QString::fromUtf8("label_multi_center_11_z"));
        label_multi_center_11_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_11_z, 43, 1, 1, 1);

        vect3_fake_lights_multi_center_11_z = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_11_z->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_11_z"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_11_z, 43, 2, 1, 1);

        label_multi_center_weight_11 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_weight_11->setObjectName(QString::fromUtf8("label_multi_center_weight_11"));

        gridLayout_multi_center->addWidget(label_multi_center_weight_11, 41, 3, 1, 1);

        spinbox_fake_lights_multi_center_weight_11 = new MyDoubleSpinBox(groupBox_fake_lights_multi_center);
        spinbox_fake_lights_multi_center_weight_11->setObjectName(QString::fromUtf8("spinbox_fake_lights_multi_center_weight_11"));
        spinbox_fake_lights_multi_center_weight_11->setDecimals(3);
        spinbox_fake_lights_multi_center_weight_11->setMinimum(0.000000000000000);
        spinbox_fake_lights_multi_center_weight_11->setMaximum(100.000000000000000);
        spinbox_fake_lights_multi_center_weight_11->setSingleStep(0.100000000000000);

        gridLayout_multi_center->addWidget(spinbox_fake_lights_multi_center_weight_11, 41, 4, 1, 1);

        label_multi_center_color_11 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_color_11->setObjectName(QString::fromUtf8("label_multi_center_color_11"));

        gridLayout_multi_center->addWidget(label_multi_center_color_11, 41, 5, 1, 1);

        colorButton_fake_lights_multi_center_color_11 = new MyColorButton(groupBox_fake_lights_multi_center);
        colorButton_fake_lights_multi_center_color_11->setObjectName(QString::fromUtf8("colorButton_fake_lights_multi_center_color_11"));

        gridLayout_multi_center->addWidget(colorButton_fake_lights_multi_center_color_11, 41, 6, 1, 1);

        line_multi_center_sep_44 = new QFrame(groupBox_fake_lights_multi_center);
        line_multi_center_sep_44->setObjectName(QString::fromUtf8("line_multi_center_sep_44"));
        line_multi_center_sep_44->setFrameShape(QFrame::HLine);
        line_multi_center_sep_44->setFrameShadow(QFrame::Sunken);

        gridLayout_multi_center->addWidget(line_multi_center_sep_44, 44, 0, 1, 7);

        label_multi_center_12 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_12->setObjectName(QString::fromUtf8("label_multi_center_12"));

        gridLayout_multi_center->addWidget(label_multi_center_12, 45, 0, 3, 1);

        label_multi_center_12_x = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_12_x->setObjectName(QString::fromUtf8("label_multi_center_12_x"));
        label_multi_center_12_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_12_x, 45, 1, 1, 1);

        vect3_fake_lights_multi_center_12_x = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_12_x->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_12_x"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_12_x, 45, 2, 1, 1);

        label_multi_center_12_y = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_12_y->setObjectName(QString::fromUtf8("label_multi_center_12_y"));
        label_multi_center_12_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_12_y, 46, 1, 1, 1);

        vect3_fake_lights_multi_center_12_y = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_12_y->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_12_y"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_12_y, 46, 2, 1, 1);

        label_multi_center_12_z = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_12_z->setObjectName(QString::fromUtf8("label_multi_center_12_z"));
        label_multi_center_12_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_12_z, 47, 1, 1, 1);

        vect3_fake_lights_multi_center_12_z = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_12_z->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_12_z"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_12_z, 47, 2, 1, 1);

        label_multi_center_weight_12 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_weight_12->setObjectName(QString::fromUtf8("label_multi_center_weight_12"));

        gridLayout_multi_center->addWidget(label_multi_center_weight_12, 45, 3, 1, 1);

        spinbox_fake_lights_multi_center_weight_12 = new MyDoubleSpinBox(groupBox_fake_lights_multi_center);
        spinbox_fake_lights_multi_center_weight_12->setObjectName(QString::fromUtf8("spinbox_fake_lights_multi_center_weight_12"));
        spinbox_fake_lights_multi_center_weight_12->setDecimals(3);
        spinbox_fake_lights_multi_center_weight_12->setMinimum(0.000000000000000);
        spinbox_fake_lights_multi_center_weight_12->setMaximum(100.000000000000000);
        spinbox_fake_lights_multi_center_weight_12->setSingleStep(0.100000000000000);

        gridLayout_multi_center->addWidget(spinbox_fake_lights_multi_center_weight_12, 45, 4, 1, 1);

        label_multi_center_color_12 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_color_12->setObjectName(QString::fromUtf8("label_multi_center_color_12"));

        gridLayout_multi_center->addWidget(label_multi_center_color_12, 45, 5, 1, 1);

        colorButton_fake_lights_multi_center_color_12 = new MyColorButton(groupBox_fake_lights_multi_center);
        colorButton_fake_lights_multi_center_color_12->setObjectName(QString::fromUtf8("colorButton_fake_lights_multi_center_color_12"));

        gridLayout_multi_center->addWidget(colorButton_fake_lights_multi_center_color_12, 45, 6, 1, 1);

        line_multi_center_sep_48 = new QFrame(groupBox_fake_lights_multi_center);
        line_multi_center_sep_48->setObjectName(QString::fromUtf8("line_multi_center_sep_48"));
        line_multi_center_sep_48->setFrameShape(QFrame::HLine);
        line_multi_center_sep_48->setFrameShadow(QFrame::Sunken);

        gridLayout_multi_center->addWidget(line_multi_center_sep_48, 48, 0, 1, 7);

        label_multi_center_13 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_13->setObjectName(QString::fromUtf8("label_multi_center_13"));

        gridLayout_multi_center->addWidget(label_multi_center_13, 49, 0, 3, 1);

        label_multi_center_13_x = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_13_x->setObjectName(QString::fromUtf8("label_multi_center_13_x"));
        label_multi_center_13_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_13_x, 49, 1, 1, 1);

        vect3_fake_lights_multi_center_13_x = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_13_x->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_13_x"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_13_x, 49, 2, 1, 1);

        label_multi_center_13_y = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_13_y->setObjectName(QString::fromUtf8("label_multi_center_13_y"));
        label_multi_center_13_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_13_y, 50, 1, 1, 1);

        vect3_fake_lights_multi_center_13_y = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_13_y->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_13_y"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_13_y, 50, 2, 1, 1);

        label_multi_center_13_z = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_13_z->setObjectName(QString::fromUtf8("label_multi_center_13_z"));
        label_multi_center_13_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_13_z, 51, 1, 1, 1);

        vect3_fake_lights_multi_center_13_z = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_13_z->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_13_z"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_13_z, 51, 2, 1, 1);

        label_multi_center_weight_13 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_weight_13->setObjectName(QString::fromUtf8("label_multi_center_weight_13"));

        gridLayout_multi_center->addWidget(label_multi_center_weight_13, 49, 3, 1, 1);

        spinbox_fake_lights_multi_center_weight_13 = new MyDoubleSpinBox(groupBox_fake_lights_multi_center);
        spinbox_fake_lights_multi_center_weight_13->setObjectName(QString::fromUtf8("spinbox_fake_lights_multi_center_weight_13"));
        spinbox_fake_lights_multi_center_weight_13->setDecimals(3);
        spinbox_fake_lights_multi_center_weight_13->setMinimum(0.000000000000000);
        spinbox_fake_lights_multi_center_weight_13->setMaximum(100.000000000000000);
        spinbox_fake_lights_multi_center_weight_13->setSingleStep(0.100000000000000);

        gridLayout_multi_center->addWidget(spinbox_fake_lights_multi_center_weight_13, 49, 4, 1, 1);

        label_multi_center_color_13 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_color_13->setObjectName(QString::fromUtf8("label_multi_center_color_13"));

        gridLayout_multi_center->addWidget(label_multi_center_color_13, 49, 5, 1, 1);

        colorButton_fake_lights_multi_center_color_13 = new MyColorButton(groupBox_fake_lights_multi_center);
        colorButton_fake_lights_multi_center_color_13->setObjectName(QString::fromUtf8("colorButton_fake_lights_multi_center_color_13"));

        gridLayout_multi_center->addWidget(colorButton_fake_lights_multi_center_color_13, 49, 6, 1, 1);

        line_multi_center_sep_52 = new QFrame(groupBox_fake_lights_multi_center);
        line_multi_center_sep_52->setObjectName(QString::fromUtf8("line_multi_center_sep_52"));
        line_multi_center_sep_52->setFrameShape(QFrame::HLine);
        line_multi_center_sep_52->setFrameShadow(QFrame::Sunken);

        gridLayout_multi_center->addWidget(line_multi_center_sep_52, 52, 0, 1, 7);

        label_multi_center_14 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_14->setObjectName(QString::fromUtf8("label_multi_center_14"));

        gridLayout_multi_center->addWidget(label_multi_center_14, 53, 0, 3, 1);

        label_multi_center_14_x = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_14_x->setObjectName(QString::fromUtf8("label_multi_center_14_x"));
        label_multi_center_14_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_14_x, 53, 1, 1, 1);

        vect3_fake_lights_multi_center_14_x = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_14_x->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_14_x"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_14_x, 53, 2, 1, 1);

        label_multi_center_14_y = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_14_y->setObjectName(QString::fromUtf8("label_multi_center_14_y"));
        label_multi_center_14_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_14_y, 54, 1, 1, 1);

        vect3_fake_lights_multi_center_14_y = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_14_y->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_14_y"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_14_y, 54, 2, 1, 1);

        label_multi_center_14_z = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_14_z->setObjectName(QString::fromUtf8("label_multi_center_14_z"));
        label_multi_center_14_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_14_z, 55, 1, 1, 1);

        vect3_fake_lights_multi_center_14_z = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_14_z->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_14_z"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_14_z, 55, 2, 1, 1);

        label_multi_center_weight_14 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_weight_14->setObjectName(QString::fromUtf8("label_multi_center_weight_14"));

        gridLayout_multi_center->addWidget(label_multi_center_weight_14, 53, 3, 1, 1);

        spinbox_fake_lights_multi_center_weight_14 = new MyDoubleSpinBox(groupBox_fake_lights_multi_center);
        spinbox_fake_lights_multi_center_weight_14->setObjectName(QString::fromUtf8("spinbox_fake_lights_multi_center_weight_14"));
        spinbox_fake_lights_multi_center_weight_14->setDecimals(3);
        spinbox_fake_lights_multi_center_weight_14->setMinimum(0.000000000000000);
        spinbox_fake_lights_multi_center_weight_14->setMaximum(100.000000000000000);
        spinbox_fake_lights_multi_center_weight_14->setSingleStep(0.100000000000000);

        gridLayout_multi_center->addWidget(spinbox_fake_lights_multi_center_weight_14, 53, 4, 1, 1);

        label_multi_center_color_14 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_color_14->setObjectName(QString::fromUtf8("label_multi_center_color_14"));

        gridLayout_multi_center->addWidget(label_multi_center_color_14, 53, 5, 1, 1);

        colorButton_fake_lights_multi_center_color_14 = new MyColorButton(groupBox_fake_lights_multi_center);
        colorButton_fake_lights_multi_center_color_14->setObjectName(QString::fromUtf8("colorButton_fake_lights_multi_center_color_14"));

        gridLayout_multi_center->addWidget(colorButton_fake_lights_multi_center_color_14, 53, 6, 1, 1);

        line_multi_center_sep_56 = new QFrame(groupBox_fake_lights_multi_center);
        line_multi_center_sep_56->setObjectName(QString::fromUtf8("line_multi_center_sep_56"));
        line_multi_center_sep_56->setFrameShape(QFrame::HLine);
        line_multi_center_sep_56->setFrameShadow(QFrame::Sunken);

        gridLayout_multi_center->addWidget(line_multi_center_sep_56, 56, 0, 1, 7);

        label_multi_center_15 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_15->setObjectName(QString::fromUtf8("label_multi_center_15"));

        gridLayout_multi_center->addWidget(label_multi_center_15, 57, 0, 3, 1);

        label_multi_center_15_x = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_15_x->setObjectName(QString::fromUtf8("label_multi_center_15_x"));
        label_multi_center_15_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_15_x, 57, 1, 1, 1);

        vect3_fake_lights_multi_center_15_x = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_15_x->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_15_x"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_15_x, 57, 2, 1, 1);

        label_multi_center_15_y = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_15_y->setObjectName(QString::fromUtf8("label_multi_center_15_y"));
        label_multi_center_15_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_15_y, 58, 1, 1, 1);

        vect3_fake_lights_multi_center_15_y = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_15_y->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_15_y"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_15_y, 58, 2, 1, 1);

        label_multi_center_15_z = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_15_z->setObjectName(QString::fromUtf8("label_multi_center_15_z"));
        label_multi_center_15_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_15_z, 59, 1, 1, 1);

        vect3_fake_lights_multi_center_15_z = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_15_z->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_15_z"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_15_z, 59, 2, 1, 1);

        label_multi_center_weight_15 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_weight_15->setObjectName(QString::fromUtf8("label_multi_center_weight_15"));

        gridLayout_multi_center->addWidget(label_multi_center_weight_15, 57, 3, 1, 1);

        spinbox_fake_lights_multi_center_weight_15 = new MyDoubleSpinBox(groupBox_fake_lights_multi_center);
        spinbox_fake_lights_multi_center_weight_15->setObjectName(QString::fromUtf8("spinbox_fake_lights_multi_center_weight_15"));
        spinbox_fake_lights_multi_center_weight_15->setDecimals(3);
        spinbox_fake_lights_multi_center_weight_15->setMinimum(0.000000000000000);
        spinbox_fake_lights_multi_center_weight_15->setMaximum(100.000000000000000);
        spinbox_fake_lights_multi_center_weight_15->setSingleStep(0.100000000000000);

        gridLayout_multi_center->addWidget(spinbox_fake_lights_multi_center_weight_15, 57, 4, 1, 1);

        label_multi_center_color_15 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_color_15->setObjectName(QString::fromUtf8("label_multi_center_color_15"));

        gridLayout_multi_center->addWidget(label_multi_center_color_15, 57, 5, 1, 1);

        colorButton_fake_lights_multi_center_color_15 = new MyColorButton(groupBox_fake_lights_multi_center);
        colorButton_fake_lights_multi_center_color_15->setObjectName(QString::fromUtf8("colorButton_fake_lights_multi_center_color_15"));

        gridLayout_multi_center->addWidget(colorButton_fake_lights_multi_center_color_15, 57, 6, 1, 1);

        line_multi_center_sep_60 = new QFrame(groupBox_fake_lights_multi_center);
        line_multi_center_sep_60->setObjectName(QString::fromUtf8("line_multi_center_sep_60"));
        line_multi_center_sep_60->setFrameShape(QFrame::HLine);
        line_multi_center_sep_60->setFrameShadow(QFrame::Sunken);

        gridLayout_multi_center->addWidget(line_multi_center_sep_60, 60, 0, 1, 7);

        label_multi_center_16 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_16->setObjectName(QString::fromUtf8("label_multi_center_16"));

        gridLayout_multi_center->addWidget(label_multi_center_16, 61, 0, 3, 1);

        label_multi_center_16_x = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_16_x->setObjectName(QString::fromUtf8("label_multi_center_16_x"));
        label_multi_center_16_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_16_x, 61, 1, 1, 1);

        vect3_fake_lights_multi_center_16_x = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_16_x->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_16_x"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_16_x, 61, 2, 1, 1);

        label_multi_center_16_y = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_16_y->setObjectName(QString::fromUtf8("label_multi_center_16_y"));
        label_multi_center_16_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_16_y, 62, 1, 1, 1);

        vect3_fake_lights_multi_center_16_y = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_16_y->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_16_y"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_16_y, 62, 2, 1, 1);

        label_multi_center_16_z = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_16_z->setObjectName(QString::fromUtf8("label_multi_center_16_z"));
        label_multi_center_16_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_16_z, 63, 1, 1, 1);

        vect3_fake_lights_multi_center_16_z = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_16_z->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_16_z"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_16_z, 63, 2, 1, 1);

        label_multi_center_weight_16 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_weight_16->setObjectName(QString::fromUtf8("label_multi_center_weight_16"));

        gridLayout_multi_center->addWidget(label_multi_center_weight_16, 61, 3, 1, 1);

        spinbox_fake_lights_multi_center_weight_16 = new MyDoubleSpinBox(groupBox_fake_lights_multi_center);
        spinbox_fake_lights_multi_center_weight_16->setObjectName(QString::fromUtf8("spinbox_fake_lights_multi_center_weight_16"));
        spinbox_fake_lights_multi_center_weight_16->setDecimals(3);
        spinbox_fake_lights_multi_center_weight_16->setMinimum(0.000000000000000);
        spinbox_fake_lights_multi_center_weight_16->setMaximum(100.000000000000000);
        spinbox_fake_lights_multi_center_weight_16->setSingleStep(0.100000000000000);

        gridLayout_multi_center->addWidget(spinbox_fake_lights_multi_center_weight_16, 61, 4, 1, 1);

        label_multi_center_color_16 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_color_16->setObjectName(QString::fromUtf8("label_multi_center_color_16"));

        gridLayout_multi_center->addWidget(label_multi_center_color_16, 61, 5, 1, 1);

        colorButton_fake_lights_multi_center_color_16 = new MyColorButton(groupBox_fake_lights_multi_center);
        colorButton_fake_lights_multi_center_color_16->setObjectName(QString::fromUtf8("colorButton_fake_lights_multi_center_color_16"));

        gridLayout_multi_center->addWidget(colorButton_fake_lights_multi_center_color_16, 61, 6, 1, 1);

        line_multi_center_sep_64 = new QFrame(groupBox_fake_lights_multi_center);
        line_multi_center_sep_64->setObjectName(QString::fromUtf8("line_multi_center_sep_64"));
        line_multi_center_sep_64->setFrameShape(QFrame::HLine);
        line_multi_center_sep_64->setFrameShadow(QFrame::Sunken);

        gridLayout_multi_center->addWidget(line_multi_center_sep_64, 64, 0, 1, 7);

        label_multi_center_17 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_17->setObjectName(QString::fromUtf8("label_multi_center_17"));

        gridLayout_multi_center->addWidget(label_multi_center_17, 65, 0, 3, 1);

        label_multi_center_17_x = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_17_x->setObjectName(QString::fromUtf8("label_multi_center_17_x"));
        label_multi_center_17_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_17_x, 65, 1, 1, 1);

        vect3_fake_lights_multi_center_17_x = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_17_x->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_17_x"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_17_x, 65, 2, 1, 1);

        label_multi_center_17_y = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_17_y->setObjectName(QString::fromUtf8("label_multi_center_17_y"));
        label_multi_center_17_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_17_y, 66, 1, 1, 1);

        vect3_fake_lights_multi_center_17_y = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_17_y->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_17_y"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_17_y, 66, 2, 1, 1);

        label_multi_center_17_z = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_17_z->setObjectName(QString::fromUtf8("label_multi_center_17_z"));
        label_multi_center_17_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_17_z, 67, 1, 1, 1);

        vect3_fake_lights_multi_center_17_z = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_17_z->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_17_z"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_17_z, 67, 2, 1, 1);

        label_multi_center_weight_17 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_weight_17->setObjectName(QString::fromUtf8("label_multi_center_weight_17"));

        gridLayout_multi_center->addWidget(label_multi_center_weight_17, 65, 3, 1, 1);

        spinbox_fake_lights_multi_center_weight_17 = new MyDoubleSpinBox(groupBox_fake_lights_multi_center);
        spinbox_fake_lights_multi_center_weight_17->setObjectName(QString::fromUtf8("spinbox_fake_lights_multi_center_weight_17"));
        spinbox_fake_lights_multi_center_weight_17->setDecimals(3);
        spinbox_fake_lights_multi_center_weight_17->setMinimum(0.000000000000000);
        spinbox_fake_lights_multi_center_weight_17->setMaximum(100.000000000000000);
        spinbox_fake_lights_multi_center_weight_17->setSingleStep(0.100000000000000);

        gridLayout_multi_center->addWidget(spinbox_fake_lights_multi_center_weight_17, 65, 4, 1, 1);

        label_multi_center_color_17 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_color_17->setObjectName(QString::fromUtf8("label_multi_center_color_17"));

        gridLayout_multi_center->addWidget(label_multi_center_color_17, 65, 5, 1, 1);

        colorButton_fake_lights_multi_center_color_17 = new MyColorButton(groupBox_fake_lights_multi_center);
        colorButton_fake_lights_multi_center_color_17->setObjectName(QString::fromUtf8("colorButton_fake_lights_multi_center_color_17"));

        gridLayout_multi_center->addWidget(colorButton_fake_lights_multi_center_color_17, 65, 6, 1, 1);

        line_multi_center_sep_68 = new QFrame(groupBox_fake_lights_multi_center);
        line_multi_center_sep_68->setObjectName(QString::fromUtf8("line_multi_center_sep_68"));
        line_multi_center_sep_68->setFrameShape(QFrame::HLine);
        line_multi_center_sep_68->setFrameShadow(QFrame::Sunken);

        gridLayout_multi_center->addWidget(line_multi_center_sep_68, 68, 0, 1, 7);

        label_multi_center_18 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_18->setObjectName(QString::fromUtf8("label_multi_center_18"));

        gridLayout_multi_center->addWidget(label_multi_center_18, 69, 0, 3, 1);

        label_multi_center_18_x = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_18_x->setObjectName(QString::fromUtf8("label_multi_center_18_x"));
        label_multi_center_18_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_18_x, 69, 1, 1, 1);

        vect3_fake_lights_multi_center_18_x = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_18_x->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_18_x"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_18_x, 69, 2, 1, 1);

        label_multi_center_18_y = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_18_y->setObjectName(QString::fromUtf8("label_multi_center_18_y"));
        label_multi_center_18_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_18_y, 70, 1, 1, 1);

        vect3_fake_lights_multi_center_18_y = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_18_y->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_18_y"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_18_y, 70, 2, 1, 1);

        label_multi_center_18_z = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_18_z->setObjectName(QString::fromUtf8("label_multi_center_18_z"));
        label_multi_center_18_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_18_z, 71, 1, 1, 1);

        vect3_fake_lights_multi_center_18_z = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_18_z->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_18_z"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_18_z, 71, 2, 1, 1);

        label_multi_center_weight_18 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_weight_18->setObjectName(QString::fromUtf8("label_multi_center_weight_18"));

        gridLayout_multi_center->addWidget(label_multi_center_weight_18, 69, 3, 1, 1);

        spinbox_fake_lights_multi_center_weight_18 = new MyDoubleSpinBox(groupBox_fake_lights_multi_center);
        spinbox_fake_lights_multi_center_weight_18->setObjectName(QString::fromUtf8("spinbox_fake_lights_multi_center_weight_18"));
        spinbox_fake_lights_multi_center_weight_18->setDecimals(3);
        spinbox_fake_lights_multi_center_weight_18->setMinimum(0.000000000000000);
        spinbox_fake_lights_multi_center_weight_18->setMaximum(100.000000000000000);
        spinbox_fake_lights_multi_center_weight_18->setSingleStep(0.100000000000000);

        gridLayout_multi_center->addWidget(spinbox_fake_lights_multi_center_weight_18, 69, 4, 1, 1);

        label_multi_center_color_18 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_color_18->setObjectName(QString::fromUtf8("label_multi_center_color_18"));

        gridLayout_multi_center->addWidget(label_multi_center_color_18, 69, 5, 1, 1);

        colorButton_fake_lights_multi_center_color_18 = new MyColorButton(groupBox_fake_lights_multi_center);
        colorButton_fake_lights_multi_center_color_18->setObjectName(QString::fromUtf8("colorButton_fake_lights_multi_center_color_18"));

        gridLayout_multi_center->addWidget(colorButton_fake_lights_multi_center_color_18, 69, 6, 1, 1);

        line_multi_center_sep_72 = new QFrame(groupBox_fake_lights_multi_center);
        line_multi_center_sep_72->setObjectName(QString::fromUtf8("line_multi_center_sep_72"));
        line_multi_center_sep_72->setFrameShape(QFrame::HLine);
        line_multi_center_sep_72->setFrameShadow(QFrame::Sunken);

        gridLayout_multi_center->addWidget(line_multi_center_sep_72, 72, 0, 1, 7);

        label_multi_center_19 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_19->setObjectName(QString::fromUtf8("label_multi_center_19"));

        gridLayout_multi_center->addWidget(label_multi_center_19, 73, 0, 3, 1);

        label_multi_center_19_x = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_19_x->setObjectName(QString::fromUtf8("label_multi_center_19_x"));
        label_multi_center_19_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_19_x, 73, 1, 1, 1);

        vect3_fake_lights_multi_center_19_x = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_19_x->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_19_x"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_19_x, 73, 2, 1, 1);

        label_multi_center_19_y = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_19_y->setObjectName(QString::fromUtf8("label_multi_center_19_y"));
        label_multi_center_19_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_19_y, 74, 1, 1, 1);

        vect3_fake_lights_multi_center_19_y = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_19_y->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_19_y"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_19_y, 74, 2, 1, 1);

        label_multi_center_19_z = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_19_z->setObjectName(QString::fromUtf8("label_multi_center_19_z"));
        label_multi_center_19_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_19_z, 75, 1, 1, 1);

        vect3_fake_lights_multi_center_19_z = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_19_z->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_19_z"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_19_z, 75, 2, 1, 1);

        label_multi_center_weight_19 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_weight_19->setObjectName(QString::fromUtf8("label_multi_center_weight_19"));

        gridLayout_multi_center->addWidget(label_multi_center_weight_19, 73, 3, 1, 1);

        spinbox_fake_lights_multi_center_weight_19 = new MyDoubleSpinBox(groupBox_fake_lights_multi_center);
        spinbox_fake_lights_multi_center_weight_19->setObjectName(QString::fromUtf8("spinbox_fake_lights_multi_center_weight_19"));
        spinbox_fake_lights_multi_center_weight_19->setDecimals(3);
        spinbox_fake_lights_multi_center_weight_19->setMinimum(0.000000000000000);
        spinbox_fake_lights_multi_center_weight_19->setMaximum(100.000000000000000);
        spinbox_fake_lights_multi_center_weight_19->setSingleStep(0.100000000000000);

        gridLayout_multi_center->addWidget(spinbox_fake_lights_multi_center_weight_19, 73, 4, 1, 1);

        label_multi_center_color_19 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_color_19->setObjectName(QString::fromUtf8("label_multi_center_color_19"));

        gridLayout_multi_center->addWidget(label_multi_center_color_19, 73, 5, 1, 1);

        colorButton_fake_lights_multi_center_color_19 = new MyColorButton(groupBox_fake_lights_multi_center);
        colorButton_fake_lights_multi_center_color_19->setObjectName(QString::fromUtf8("colorButton_fake_lights_multi_center_color_19"));

        gridLayout_multi_center->addWidget(colorButton_fake_lights_multi_center_color_19, 73, 6, 1, 1);

        line_multi_center_sep_76 = new QFrame(groupBox_fake_lights_multi_center);
        line_multi_center_sep_76->setObjectName(QString::fromUtf8("line_multi_center_sep_76"));
        line_multi_center_sep_76->setFrameShape(QFrame::HLine);
        line_multi_center_sep_76->setFrameShadow(QFrame::Sunken);

        gridLayout_multi_center->addWidget(line_multi_center_sep_76, 76, 0, 1, 7);

        label_multi_center_20 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_20->setObjectName(QString::fromUtf8("label_multi_center_20"));

        gridLayout_multi_center->addWidget(label_multi_center_20, 77, 0, 3, 1);

        label_multi_center_20_x = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_20_x->setObjectName(QString::fromUtf8("label_multi_center_20_x"));
        label_multi_center_20_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_20_x, 77, 1, 1, 1);

        vect3_fake_lights_multi_center_20_x = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_20_x->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_20_x"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_20_x, 77, 2, 1, 1);

        label_multi_center_20_y = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_20_y->setObjectName(QString::fromUtf8("label_multi_center_20_y"));
        label_multi_center_20_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_20_y, 78, 1, 1, 1);

        vect3_fake_lights_multi_center_20_y = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_20_y->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_20_y"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_20_y, 78, 2, 1, 1);

        label_multi_center_20_z = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_20_z->setObjectName(QString::fromUtf8("label_multi_center_20_z"));
        label_multi_center_20_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_20_z, 79, 1, 1, 1);

        vect3_fake_lights_multi_center_20_z = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_20_z->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_20_z"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_20_z, 79, 2, 1, 1);

        label_multi_center_weight_20 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_weight_20->setObjectName(QString::fromUtf8("label_multi_center_weight_20"));

        gridLayout_multi_center->addWidget(label_multi_center_weight_20, 77, 3, 1, 1);

        spinbox_fake_lights_multi_center_weight_20 = new MyDoubleSpinBox(groupBox_fake_lights_multi_center);
        spinbox_fake_lights_multi_center_weight_20->setObjectName(QString::fromUtf8("spinbox_fake_lights_multi_center_weight_20"));
        spinbox_fake_lights_multi_center_weight_20->setDecimals(3);
        spinbox_fake_lights_multi_center_weight_20->setMinimum(0.000000000000000);
        spinbox_fake_lights_multi_center_weight_20->setMaximum(100.000000000000000);
        spinbox_fake_lights_multi_center_weight_20->setSingleStep(0.100000000000000);

        gridLayout_multi_center->addWidget(spinbox_fake_lights_multi_center_weight_20, 77, 4, 1, 1);

        label_multi_center_color_20 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_color_20->setObjectName(QString::fromUtf8("label_multi_center_color_20"));

        gridLayout_multi_center->addWidget(label_multi_center_color_20, 77, 5, 1, 1);

        colorButton_fake_lights_multi_center_color_20 = new MyColorButton(groupBox_fake_lights_multi_center);
        colorButton_fake_lights_multi_center_color_20->setObjectName(QString::fromUtf8("colorButton_fake_lights_multi_center_color_20"));

        gridLayout_multi_center->addWidget(colorButton_fake_lights_multi_center_color_20, 77, 6, 1, 1);

        line_multi_center_sep_80 = new QFrame(groupBox_fake_lights_multi_center);
        line_multi_center_sep_80->setObjectName(QString::fromUtf8("line_multi_center_sep_80"));
        line_multi_center_sep_80->setFrameShape(QFrame::HLine);
        line_multi_center_sep_80->setFrameShadow(QFrame::Sunken);

        gridLayout_multi_center->addWidget(line_multi_center_sep_80, 80, 0, 1, 7);

        label_multi_center_21 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_21->setObjectName(QString::fromUtf8("label_multi_center_21"));

        gridLayout_multi_center->addWidget(label_multi_center_21, 81, 0, 3, 1);

        label_multi_center_21_x = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_21_x->setObjectName(QString::fromUtf8("label_multi_center_21_x"));
        label_multi_center_21_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_21_x, 81, 1, 1, 1);

        vect3_fake_lights_multi_center_21_x = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_21_x->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_21_x"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_21_x, 81, 2, 1, 1);

        label_multi_center_21_y = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_21_y->setObjectName(QString::fromUtf8("label_multi_center_21_y"));
        label_multi_center_21_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_21_y, 82, 1, 1, 1);

        vect3_fake_lights_multi_center_21_y = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_21_y->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_21_y"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_21_y, 82, 2, 1, 1);

        label_multi_center_21_z = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_21_z->setObjectName(QString::fromUtf8("label_multi_center_21_z"));
        label_multi_center_21_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_21_z, 83, 1, 1, 1);

        vect3_fake_lights_multi_center_21_z = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_21_z->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_21_z"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_21_z, 83, 2, 1, 1);

        label_multi_center_weight_21 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_weight_21->setObjectName(QString::fromUtf8("label_multi_center_weight_21"));

        gridLayout_multi_center->addWidget(label_multi_center_weight_21, 81, 3, 1, 1);

        spinbox_fake_lights_multi_center_weight_21 = new MyDoubleSpinBox(groupBox_fake_lights_multi_center);
        spinbox_fake_lights_multi_center_weight_21->setObjectName(QString::fromUtf8("spinbox_fake_lights_multi_center_weight_21"));
        spinbox_fake_lights_multi_center_weight_21->setDecimals(3);
        spinbox_fake_lights_multi_center_weight_21->setMinimum(0.000000000000000);
        spinbox_fake_lights_multi_center_weight_21->setMaximum(100.000000000000000);
        spinbox_fake_lights_multi_center_weight_21->setSingleStep(0.100000000000000);

        gridLayout_multi_center->addWidget(spinbox_fake_lights_multi_center_weight_21, 81, 4, 1, 1);

        label_multi_center_color_21 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_color_21->setObjectName(QString::fromUtf8("label_multi_center_color_21"));

        gridLayout_multi_center->addWidget(label_multi_center_color_21, 81, 5, 1, 1);

        colorButton_fake_lights_multi_center_color_21 = new MyColorButton(groupBox_fake_lights_multi_center);
        colorButton_fake_lights_multi_center_color_21->setObjectName(QString::fromUtf8("colorButton_fake_lights_multi_center_color_21"));

        gridLayout_multi_center->addWidget(colorButton_fake_lights_multi_center_color_21, 81, 6, 1, 1);

        line_multi_center_sep_84 = new QFrame(groupBox_fake_lights_multi_center);
        line_multi_center_sep_84->setObjectName(QString::fromUtf8("line_multi_center_sep_84"));
        line_multi_center_sep_84->setFrameShape(QFrame::HLine);
        line_multi_center_sep_84->setFrameShadow(QFrame::Sunken);

        gridLayout_multi_center->addWidget(line_multi_center_sep_84, 84, 0, 1, 7);

        label_multi_center_22 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_22->setObjectName(QString::fromUtf8("label_multi_center_22"));

        gridLayout_multi_center->addWidget(label_multi_center_22, 85, 0, 3, 1);

        label_multi_center_22_x = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_22_x->setObjectName(QString::fromUtf8("label_multi_center_22_x"));
        label_multi_center_22_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_22_x, 85, 1, 1, 1);

        vect3_fake_lights_multi_center_22_x = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_22_x->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_22_x"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_22_x, 85, 2, 1, 1);

        label_multi_center_22_y = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_22_y->setObjectName(QString::fromUtf8("label_multi_center_22_y"));
        label_multi_center_22_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_22_y, 86, 1, 1, 1);

        vect3_fake_lights_multi_center_22_y = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_22_y->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_22_y"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_22_y, 86, 2, 1, 1);

        label_multi_center_22_z = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_22_z->setObjectName(QString::fromUtf8("label_multi_center_22_z"));
        label_multi_center_22_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_22_z, 87, 1, 1, 1);

        vect3_fake_lights_multi_center_22_z = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_22_z->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_22_z"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_22_z, 87, 2, 1, 1);

        label_multi_center_weight_22 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_weight_22->setObjectName(QString::fromUtf8("label_multi_center_weight_22"));

        gridLayout_multi_center->addWidget(label_multi_center_weight_22, 85, 3, 1, 1);

        spinbox_fake_lights_multi_center_weight_22 = new MyDoubleSpinBox(groupBox_fake_lights_multi_center);
        spinbox_fake_lights_multi_center_weight_22->setObjectName(QString::fromUtf8("spinbox_fake_lights_multi_center_weight_22"));
        spinbox_fake_lights_multi_center_weight_22->setDecimals(3);
        spinbox_fake_lights_multi_center_weight_22->setMinimum(0.000000000000000);
        spinbox_fake_lights_multi_center_weight_22->setMaximum(100.000000000000000);
        spinbox_fake_lights_multi_center_weight_22->setSingleStep(0.100000000000000);

        gridLayout_multi_center->addWidget(spinbox_fake_lights_multi_center_weight_22, 85, 4, 1, 1);

        label_multi_center_color_22 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_color_22->setObjectName(QString::fromUtf8("label_multi_center_color_22"));

        gridLayout_multi_center->addWidget(label_multi_center_color_22, 85, 5, 1, 1);

        colorButton_fake_lights_multi_center_color_22 = new MyColorButton(groupBox_fake_lights_multi_center);
        colorButton_fake_lights_multi_center_color_22->setObjectName(QString::fromUtf8("colorButton_fake_lights_multi_center_color_22"));

        gridLayout_multi_center->addWidget(colorButton_fake_lights_multi_center_color_22, 85, 6, 1, 1);

        line_multi_center_sep_88 = new QFrame(groupBox_fake_lights_multi_center);
        line_multi_center_sep_88->setObjectName(QString::fromUtf8("line_multi_center_sep_88"));
        line_multi_center_sep_88->setFrameShape(QFrame::HLine);
        line_multi_center_sep_88->setFrameShadow(QFrame::Sunken);

        gridLayout_multi_center->addWidget(line_multi_center_sep_88, 88, 0, 1, 7);

        label_multi_center_23 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_23->setObjectName(QString::fromUtf8("label_multi_center_23"));

        gridLayout_multi_center->addWidget(label_multi_center_23, 89, 0, 3, 1);

        label_multi_center_23_x = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_23_x->setObjectName(QString::fromUtf8("label_multi_center_23_x"));
        label_multi_center_23_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_23_x, 89, 1, 1, 1);

        vect3_fake_lights_multi_center_23_x = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_23_x->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_23_x"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_23_x, 89, 2, 1, 1);

        label_multi_center_23_y = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_23_y->setObjectName(QString::fromUtf8("label_multi_center_23_y"));
        label_multi_center_23_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_23_y, 90, 1, 1, 1);

        vect3_fake_lights_multi_center_23_y = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_23_y->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_23_y"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_23_y, 90, 2, 1, 1);

        label_multi_center_23_z = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_23_z->setObjectName(QString::fromUtf8("label_multi_center_23_z"));
        label_multi_center_23_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_23_z, 91, 1, 1, 1);

        vect3_fake_lights_multi_center_23_z = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_23_z->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_23_z"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_23_z, 91, 2, 1, 1);

        label_multi_center_weight_23 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_weight_23->setObjectName(QString::fromUtf8("label_multi_center_weight_23"));

        gridLayout_multi_center->addWidget(label_multi_center_weight_23, 89, 3, 1, 1);

        spinbox_fake_lights_multi_center_weight_23 = new MyDoubleSpinBox(groupBox_fake_lights_multi_center);
        spinbox_fake_lights_multi_center_weight_23->setObjectName(QString::fromUtf8("spinbox_fake_lights_multi_center_weight_23"));
        spinbox_fake_lights_multi_center_weight_23->setDecimals(3);
        spinbox_fake_lights_multi_center_weight_23->setMinimum(0.000000000000000);
        spinbox_fake_lights_multi_center_weight_23->setMaximum(100.000000000000000);
        spinbox_fake_lights_multi_center_weight_23->setSingleStep(0.100000000000000);

        gridLayout_multi_center->addWidget(spinbox_fake_lights_multi_center_weight_23, 89, 4, 1, 1);

        label_multi_center_color_23 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_color_23->setObjectName(QString::fromUtf8("label_multi_center_color_23"));

        gridLayout_multi_center->addWidget(label_multi_center_color_23, 89, 5, 1, 1);

        colorButton_fake_lights_multi_center_color_23 = new MyColorButton(groupBox_fake_lights_multi_center);
        colorButton_fake_lights_multi_center_color_23->setObjectName(QString::fromUtf8("colorButton_fake_lights_multi_center_color_23"));

        gridLayout_multi_center->addWidget(colorButton_fake_lights_multi_center_color_23, 89, 6, 1, 1);

        line_multi_center_sep_92 = new QFrame(groupBox_fake_lights_multi_center);
        line_multi_center_sep_92->setObjectName(QString::fromUtf8("line_multi_center_sep_92"));
        line_multi_center_sep_92->setFrameShape(QFrame::HLine);
        line_multi_center_sep_92->setFrameShadow(QFrame::Sunken);

        gridLayout_multi_center->addWidget(line_multi_center_sep_92, 92, 0, 1, 7);

        label_multi_center_24 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_24->setObjectName(QString::fromUtf8("label_multi_center_24"));

        gridLayout_multi_center->addWidget(label_multi_center_24, 93, 0, 3, 1);

        label_multi_center_24_x = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_24_x->setObjectName(QString::fromUtf8("label_multi_center_24_x"));
        label_multi_center_24_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_24_x, 93, 1, 1, 1);

        vect3_fake_lights_multi_center_24_x = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_24_x->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_24_x"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_24_x, 93, 2, 1, 1);

        label_multi_center_24_y = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_24_y->setObjectName(QString::fromUtf8("label_multi_center_24_y"));
        label_multi_center_24_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_24_y, 94, 1, 1, 1);

        vect3_fake_lights_multi_center_24_y = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_24_y->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_24_y"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_24_y, 94, 2, 1, 1);

        label_multi_center_24_z = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_24_z->setObjectName(QString::fromUtf8("label_multi_center_24_z"));
        label_multi_center_24_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_multi_center->addWidget(label_multi_center_24_z, 95, 1, 1, 1);

        vect3_fake_lights_multi_center_24_z = new MyLineEdit(groupBox_fake_lights_multi_center);
        vect3_fake_lights_multi_center_24_z->setObjectName(QString::fromUtf8("vect3_fake_lights_multi_center_24_z"));

        gridLayout_multi_center->addWidget(vect3_fake_lights_multi_center_24_z, 95, 2, 1, 1);

        label_multi_center_weight_24 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_weight_24->setObjectName(QString::fromUtf8("label_multi_center_weight_24"));

        gridLayout_multi_center->addWidget(label_multi_center_weight_24, 93, 3, 1, 1);

        spinbox_fake_lights_multi_center_weight_24 = new MyDoubleSpinBox(groupBox_fake_lights_multi_center);
        spinbox_fake_lights_multi_center_weight_24->setObjectName(QString::fromUtf8("spinbox_fake_lights_multi_center_weight_24"));
        spinbox_fake_lights_multi_center_weight_24->setDecimals(3);
        spinbox_fake_lights_multi_center_weight_24->setMinimum(0.000000000000000);
        spinbox_fake_lights_multi_center_weight_24->setMaximum(100.000000000000000);
        spinbox_fake_lights_multi_center_weight_24->setSingleStep(0.100000000000000);

        gridLayout_multi_center->addWidget(spinbox_fake_lights_multi_center_weight_24, 93, 4, 1, 1);

        label_multi_center_color_24 = new QLabel(groupBox_fake_lights_multi_center);
        label_multi_center_color_24->setObjectName(QString::fromUtf8("label_multi_center_color_24"));

        gridLayout_multi_center->addWidget(label_multi_center_color_24, 93, 5, 1, 1);

        colorButton_fake_lights_multi_center_color_24 = new MyColorButton(groupBox_fake_lights_multi_center);
        colorButton_fake_lights_multi_center_color_24->setObjectName(QString::fromUtf8("colorButton_fake_lights_multi_center_color_24"));

        gridLayout_multi_center->addWidget(colorButton_fake_lights_multi_center_color_24, 93, 6, 1, 1);

        pushButton_reset_multi_center = new QPushButton(groupBox_fake_lights_multi_center);
        pushButton_reset_multi_center->setObjectName(QString::fromUtf8("pushButton_reset_multi_center"));

        gridLayout_multi_center->addWidget(pushButton_reset_multi_center, 96, 0, 1, 7);


        verticalLayout_39->addWidget(groupBox_fake_lights_multi_center);

        groupBox_fake_lights_shape_modifiers = new QGroupBox(groupCheck_fake_lights_enabled);
        groupBox_fake_lights_shape_modifiers->setObjectName(QString::fromUtf8("groupBox_fake_lights_shape_modifiers"));
        gridLayout_shape_modifiers = new QGridLayout(groupBox_fake_lights_shape_modifiers);
        gridLayout_shape_modifiers->setSpacing(2);
        gridLayout_shape_modifiers->setObjectName(QString::fromUtf8("gridLayout_shape_modifiers"));
        label_shape_twist = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_twist->setObjectName(QString::fromUtf8("label_shape_twist"));

        gridLayout_shape_modifiers->addWidget(label_shape_twist, 0, 0, 1, 1);

        spinbox_fake_lights_shape_twist = new MyDoubleSpinBox(groupBox_fake_lights_shape_modifiers);
        spinbox_fake_lights_shape_twist->setObjectName(QString::fromUtf8("spinbox_fake_lights_shape_twist"));
        spinbox_fake_lights_shape_twist->setDecimals(3);
        spinbox_fake_lights_shape_twist->setMinimum(-1000.000000000000000);
        spinbox_fake_lights_shape_twist->setMaximum(1000.000000000000000);
        spinbox_fake_lights_shape_twist->setSingleStep(0.010000000000000);

        gridLayout_shape_modifiers->addWidget(spinbox_fake_lights_shape_twist, 0, 1, 1, 1);

        label_shape_bend = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_bend->setObjectName(QString::fromUtf8("label_shape_bend"));

        gridLayout_shape_modifiers->addWidget(label_shape_bend, 1, 0, 1, 1);

        spinbox_fake_lights_shape_bend = new MyDoubleSpinBox(groupBox_fake_lights_shape_modifiers);
        spinbox_fake_lights_shape_bend->setObjectName(QString::fromUtf8("spinbox_fake_lights_shape_bend"));
        spinbox_fake_lights_shape_bend->setDecimals(3);
        spinbox_fake_lights_shape_bend->setMinimum(-1000.000000000000000);
        spinbox_fake_lights_shape_bend->setMaximum(1000.000000000000000);
        spinbox_fake_lights_shape_bend->setSingleStep(0.010000000000000);

        gridLayout_shape_modifiers->addWidget(spinbox_fake_lights_shape_bend, 1, 1, 1, 1);

        label_shape_taper = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_taper->setObjectName(QString::fromUtf8("label_shape_taper"));

        gridLayout_shape_modifiers->addWidget(label_shape_taper, 2, 0, 1, 1);

        spinbox_fake_lights_shape_taper = new MyDoubleSpinBox(groupBox_fake_lights_shape_modifiers);
        spinbox_fake_lights_shape_taper->setObjectName(QString::fromUtf8("spinbox_fake_lights_shape_taper"));
        spinbox_fake_lights_shape_taper->setDecimals(3);
        spinbox_fake_lights_shape_taper->setMinimum(-1000.000000000000000);
        spinbox_fake_lights_shape_taper->setMaximum(1000.000000000000000);
        spinbox_fake_lights_shape_taper->setSingleStep(0.010000000000000);

        gridLayout_shape_modifiers->addWidget(spinbox_fake_lights_shape_taper, 2, 1, 1, 1);

        label_shape_fold_symmetry = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_fold_symmetry->setObjectName(QString::fromUtf8("label_shape_fold_symmetry"));

        gridLayout_shape_modifiers->addWidget(label_shape_fold_symmetry, 3, 0, 1, 1);

        spinboxInt_fake_lights_shape_fold_symmetry = new MySpinBox(groupBox_fake_lights_shape_modifiers);
        spinboxInt_fake_lights_shape_fold_symmetry->setObjectName(QString::fromUtf8("spinboxInt_fake_lights_shape_fold_symmetry"));
        spinboxInt_fake_lights_shape_fold_symmetry->setMinimum(0);
        spinboxInt_fake_lights_shape_fold_symmetry->setMaximum(16);

        gridLayout_shape_modifiers->addWidget(spinboxInt_fake_lights_shape_fold_symmetry, 3, 1, 1, 1);

        label_shape_repeat_x = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_repeat_x->setObjectName(QString::fromUtf8("label_shape_repeat_x"));

        gridLayout_shape_modifiers->addWidget(label_shape_repeat_x, 4, 0, 1, 1);

        spinbox_fake_lights_shape_repeat_x = new MyDoubleSpinBox(groupBox_fake_lights_shape_modifiers);
        spinbox_fake_lights_shape_repeat_x->setObjectName(QString::fromUtf8("spinbox_fake_lights_shape_repeat_x"));
        spinbox_fake_lights_shape_repeat_x->setDecimals(3);
        spinbox_fake_lights_shape_repeat_x->setMinimum(0.000000000000000);
        spinbox_fake_lights_shape_repeat_x->setMaximum(1000.000000000000000);
        spinbox_fake_lights_shape_repeat_x->setSingleStep(0.010000000000000);

        gridLayout_shape_modifiers->addWidget(spinbox_fake_lights_shape_repeat_x, 4, 1, 1, 1);

        label_shape_repeat_y = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_repeat_y->setObjectName(QString::fromUtf8("label_shape_repeat_y"));

        gridLayout_shape_modifiers->addWidget(label_shape_repeat_y, 5, 0, 1, 1);

        spinbox_fake_lights_shape_repeat_y = new MyDoubleSpinBox(groupBox_fake_lights_shape_modifiers);
        spinbox_fake_lights_shape_repeat_y->setObjectName(QString::fromUtf8("spinbox_fake_lights_shape_repeat_y"));
        spinbox_fake_lights_shape_repeat_y->setDecimals(3);
        spinbox_fake_lights_shape_repeat_y->setMinimum(0.000000000000000);
        spinbox_fake_lights_shape_repeat_y->setMaximum(1000.000000000000000);
        spinbox_fake_lights_shape_repeat_y->setSingleStep(0.010000000000000);

        gridLayout_shape_modifiers->addWidget(spinbox_fake_lights_shape_repeat_y, 5, 1, 1, 1);

        label_shape_repeat_z = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_repeat_z->setObjectName(QString::fromUtf8("label_shape_repeat_z"));

        gridLayout_shape_modifiers->addWidget(label_shape_repeat_z, 6, 0, 1, 1);

        spinbox_fake_lights_shape_repeat_z = new MyDoubleSpinBox(groupBox_fake_lights_shape_modifiers);
        spinbox_fake_lights_shape_repeat_z->setObjectName(QString::fromUtf8("spinbox_fake_lights_shape_repeat_z"));
        spinbox_fake_lights_shape_repeat_z->setDecimals(3);
        spinbox_fake_lights_shape_repeat_z->setMinimum(0.000000000000000);
        spinbox_fake_lights_shape_repeat_z->setMaximum(1000.000000000000000);
        spinbox_fake_lights_shape_repeat_z->setSingleStep(0.010000000000000);

        gridLayout_shape_modifiers->addWidget(spinbox_fake_lights_shape_repeat_z, 6, 1, 1, 1);

        label_shape_wobble_amp = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_wobble_amp->setObjectName(QString::fromUtf8("label_shape_wobble_amp"));

        gridLayout_shape_modifiers->addWidget(label_shape_wobble_amp, 7, 0, 1, 1);

        spinbox_fake_lights_shape_wobble_amplitude = new MyDoubleSpinBox(groupBox_fake_lights_shape_modifiers);
        spinbox_fake_lights_shape_wobble_amplitude->setObjectName(QString::fromUtf8("spinbox_fake_lights_shape_wobble_amplitude"));
        spinbox_fake_lights_shape_wobble_amplitude->setDecimals(3);
        spinbox_fake_lights_shape_wobble_amplitude->setMinimum(-1000.000000000000000);
        spinbox_fake_lights_shape_wobble_amplitude->setMaximum(1000.000000000000000);
        spinbox_fake_lights_shape_wobble_amplitude->setSingleStep(0.010000000000000);

        gridLayout_shape_modifiers->addWidget(spinbox_fake_lights_shape_wobble_amplitude, 7, 1, 1, 1);

        label_shape_wobble_freq = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_wobble_freq->setObjectName(QString::fromUtf8("label_shape_wobble_freq"));

        gridLayout_shape_modifiers->addWidget(label_shape_wobble_freq, 8, 0, 1, 1);

        spinbox_fake_lights_shape_wobble_frequency = new MyDoubleSpinBox(groupBox_fake_lights_shape_modifiers);
        spinbox_fake_lights_shape_wobble_frequency->setObjectName(QString::fromUtf8("spinbox_fake_lights_shape_wobble_frequency"));
        spinbox_fake_lights_shape_wobble_frequency->setDecimals(3);
        spinbox_fake_lights_shape_wobble_frequency->setMinimum(0.000000000000000);
        spinbox_fake_lights_shape_wobble_frequency->setMaximum(1000.000000000000000);
        spinbox_fake_lights_shape_wobble_frequency->setSingleStep(0.010000000000000);

        gridLayout_shape_modifiers->addWidget(spinbox_fake_lights_shape_wobble_frequency, 8, 1, 1, 1);

        label_shape_chamfer = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_chamfer->setObjectName(QString::fromUtf8("label_shape_chamfer"));

        gridLayout_shape_modifiers->addWidget(label_shape_chamfer, 9, 0, 1, 1);

        spinbox_fake_lights_shape_chamfer = new MyDoubleSpinBox(groupBox_fake_lights_shape_modifiers);
        spinbox_fake_lights_shape_chamfer->setObjectName(QString::fromUtf8("spinbox_fake_lights_shape_chamfer"));
        spinbox_fake_lights_shape_chamfer->setDecimals(3);
        spinbox_fake_lights_shape_chamfer->setMinimum(0.000000000000000);
        spinbox_fake_lights_shape_chamfer->setMaximum(1000.000000000000000);
        spinbox_fake_lights_shape_chamfer->setSingleStep(0.010000000000000);

        gridLayout_shape_modifiers->addWidget(spinbox_fake_lights_shape_chamfer, 9, 1, 1, 1);

        label_shape_scale_x = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_scale_x->setObjectName(QString::fromUtf8("label_shape_scale_x"));

        gridLayout_shape_modifiers->addWidget(label_shape_scale_x, 10, 0, 1, 1);

        spinbox_fake_lights_shape_scale_x = new MyDoubleSpinBox(groupBox_fake_lights_shape_modifiers);
        spinbox_fake_lights_shape_scale_x->setObjectName(QString::fromUtf8("spinbox_fake_lights_shape_scale_x"));
        spinbox_fake_lights_shape_scale_x->setDecimals(3);
        spinbox_fake_lights_shape_scale_x->setMinimum(-1000.000000000000000);
        spinbox_fake_lights_shape_scale_x->setMaximum(1000.000000000000000);
        spinbox_fake_lights_shape_scale_x->setSingleStep(0.010000000000000);
        spinbox_fake_lights_shape_scale_x->setValue(1.000000000000000);

        gridLayout_shape_modifiers->addWidget(spinbox_fake_lights_shape_scale_x, 10, 1, 1, 1);

        label_shape_scale_y = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_scale_y->setObjectName(QString::fromUtf8("label_shape_scale_y"));

        gridLayout_shape_modifiers->addWidget(label_shape_scale_y, 11, 0, 1, 1);

        spinbox_fake_lights_shape_scale_y = new MyDoubleSpinBox(groupBox_fake_lights_shape_modifiers);
        spinbox_fake_lights_shape_scale_y->setObjectName(QString::fromUtf8("spinbox_fake_lights_shape_scale_y"));
        spinbox_fake_lights_shape_scale_y->setDecimals(3);
        spinbox_fake_lights_shape_scale_y->setMinimum(-1000.000000000000000);
        spinbox_fake_lights_shape_scale_y->setMaximum(1000.000000000000000);
        spinbox_fake_lights_shape_scale_y->setSingleStep(0.010000000000000);
        spinbox_fake_lights_shape_scale_y->setValue(1.000000000000000);

        gridLayout_shape_modifiers->addWidget(spinbox_fake_lights_shape_scale_y, 11, 1, 1, 1);

        label_shape_scale_z = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_scale_z->setObjectName(QString::fromUtf8("label_shape_scale_z"));

        gridLayout_shape_modifiers->addWidget(label_shape_scale_z, 12, 0, 1, 1);

        spinbox_fake_lights_shape_scale_z = new MyDoubleSpinBox(groupBox_fake_lights_shape_modifiers);
        spinbox_fake_lights_shape_scale_z->setObjectName(QString::fromUtf8("spinbox_fake_lights_shape_scale_z"));
        spinbox_fake_lights_shape_scale_z->setDecimals(3);
        spinbox_fake_lights_shape_scale_z->setMinimum(-1000.000000000000000);
        spinbox_fake_lights_shape_scale_z->setMaximum(1000.000000000000000);
        spinbox_fake_lights_shape_scale_z->setSingleStep(0.010000000000000);
        spinbox_fake_lights_shape_scale_z->setValue(1.000000000000000);

        gridLayout_shape_modifiers->addWidget(spinbox_fake_lights_shape_scale_z, 12, 1, 1, 1);

        label_shape_mirror_x = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_mirror_x->setObjectName(QString::fromUtf8("label_shape_mirror_x"));

        gridLayout_shape_modifiers->addWidget(label_shape_mirror_x, 13, 0, 1, 1);

        checkBox_fake_lights_shape_mirror_x = new MyCheckBox(groupBox_fake_lights_shape_modifiers);
        checkBox_fake_lights_shape_mirror_x->setObjectName(QString::fromUtf8("checkBox_fake_lights_shape_mirror_x"));

        gridLayout_shape_modifiers->addWidget(checkBox_fake_lights_shape_mirror_x, 13, 1, 1, 1);

        label_shape_mirror_y = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_mirror_y->setObjectName(QString::fromUtf8("label_shape_mirror_y"));

        gridLayout_shape_modifiers->addWidget(label_shape_mirror_y, 14, 0, 1, 1);

        checkBox_fake_lights_shape_mirror_y = new MyCheckBox(groupBox_fake_lights_shape_modifiers);
        checkBox_fake_lights_shape_mirror_y->setObjectName(QString::fromUtf8("checkBox_fake_lights_shape_mirror_y"));

        gridLayout_shape_modifiers->addWidget(checkBox_fake_lights_shape_mirror_y, 14, 1, 1, 1);

        label_shape_mirror_z = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_mirror_z->setObjectName(QString::fromUtf8("label_shape_mirror_z"));

        gridLayout_shape_modifiers->addWidget(label_shape_mirror_z, 15, 0, 1, 1);

        checkBox_fake_lights_shape_mirror_z = new MyCheckBox(groupBox_fake_lights_shape_modifiers);
        checkBox_fake_lights_shape_mirror_z->setObjectName(QString::fromUtf8("checkBox_fake_lights_shape_mirror_z"));

        gridLayout_shape_modifiers->addWidget(checkBox_fake_lights_shape_mirror_z, 15, 1, 1, 1);

        label_shape_inflate = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_inflate->setObjectName(QString::fromUtf8("label_shape_inflate"));

        gridLayout_shape_modifiers->addWidget(label_shape_inflate, 16, 0, 1, 1);

        spinbox_fake_lights_shape_inflate = new MyDoubleSpinBox(groupBox_fake_lights_shape_modifiers);
        spinbox_fake_lights_shape_inflate->setObjectName(QString::fromUtf8("spinbox_fake_lights_shape_inflate"));
        spinbox_fake_lights_shape_inflate->setDecimals(3);
        spinbox_fake_lights_shape_inflate->setMinimum(-1000.000000000000000);
        spinbox_fake_lights_shape_inflate->setMaximum(1000.000000000000000);
        spinbox_fake_lights_shape_inflate->setSingleStep(0.010000000000000);

        gridLayout_shape_modifiers->addWidget(spinbox_fake_lights_shape_inflate, 16, 1, 1, 1);

        label_shape_line_length = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_line_length->setObjectName(QString::fromUtf8("label_shape_line_length"));

        gridLayout_shape_modifiers->addWidget(label_shape_line_length, 17, 0, 1, 1);

        spinbox_fake_lights_shape_line_length = new MyDoubleSpinBox(groupBox_fake_lights_shape_modifiers);
        spinbox_fake_lights_shape_line_length->setObjectName(QString::fromUtf8("spinbox_fake_lights_shape_line_length"));
        spinbox_fake_lights_shape_line_length->setDecimals(3);
        spinbox_fake_lights_shape_line_length->setMinimum(0.000000000000000);
        spinbox_fake_lights_shape_line_length->setMaximum(1000.000000000000000);
        spinbox_fake_lights_shape_line_length->setSingleStep(0.010000000000000);

        gridLayout_shape_modifiers->addWidget(spinbox_fake_lights_shape_line_length, 17, 1, 1, 1);

        label_shape_tube_radius = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_tube_radius->setObjectName(QString::fromUtf8("label_shape_tube_radius"));

        gridLayout_shape_modifiers->addWidget(label_shape_tube_radius, 18, 0, 1, 1);

        spinbox_fake_lights_shape_tube_radius = new MyDoubleSpinBox(groupBox_fake_lights_shape_modifiers);
        spinbox_fake_lights_shape_tube_radius->setObjectName(QString::fromUtf8("spinbox_fake_lights_shape_tube_radius"));
        spinbox_fake_lights_shape_tube_radius->setDecimals(3);
        spinbox_fake_lights_shape_tube_radius->setMinimum(0.000000000000000);
        spinbox_fake_lights_shape_tube_radius->setMaximum(1000.000000000000000);
        spinbox_fake_lights_shape_tube_radius->setSingleStep(0.010000000000000);

        gridLayout_shape_modifiers->addWidget(spinbox_fake_lights_shape_tube_radius, 18, 1, 1, 1);

        label_shape_line_thickness = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_line_thickness->setObjectName(QString::fromUtf8("label_shape_line_thickness"));

        gridLayout_shape_modifiers->addWidget(label_shape_line_thickness, 19, 0, 1, 1);

        spinbox_fake_lights_shape_line_thickness = new MyDoubleSpinBox(groupBox_fake_lights_shape_modifiers);
        spinbox_fake_lights_shape_line_thickness->setObjectName(QString::fromUtf8("spinbox_fake_lights_shape_line_thickness"));
        spinbox_fake_lights_shape_line_thickness->setDecimals(3);
        spinbox_fake_lights_shape_line_thickness->setMinimum(0.000000000000000);
        spinbox_fake_lights_shape_line_thickness->setMaximum(1000.000000000000000);
        spinbox_fake_lights_shape_line_thickness->setSingleStep(0.010000000000000);

        gridLayout_shape_modifiers->addWidget(spinbox_fake_lights_shape_line_thickness, 19, 1, 1, 1);

        label_shape_falloff = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_falloff->setObjectName(QString::fromUtf8("label_shape_falloff"));

        gridLayout_shape_modifiers->addWidget(label_shape_falloff, 20, 0, 1, 1);

        spinbox_fake_lights_shape_falloff = new MyDoubleSpinBox(groupBox_fake_lights_shape_modifiers);
        spinbox_fake_lights_shape_falloff->setObjectName(QString::fromUtf8("spinbox_fake_lights_shape_falloff"));
        spinbox_fake_lights_shape_falloff->setDecimals(3);
        spinbox_fake_lights_shape_falloff->setMinimum(0.000000000000000);
        spinbox_fake_lights_shape_falloff->setMaximum(1000.000000000000000);
        spinbox_fake_lights_shape_falloff->setSingleStep(0.010000000000000);

        gridLayout_shape_modifiers->addWidget(spinbox_fake_lights_shape_falloff, 20, 1, 1, 1);

        label_shape_mask_radius = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_mask_radius->setObjectName(QString::fromUtf8("label_shape_mask_radius"));

        gridLayout_shape_modifiers->addWidget(label_shape_mask_radius, 21, 0, 1, 1);

        spinbox_fake_lights_shape_mask_radius = new MyDoubleSpinBox(groupBox_fake_lights_shape_modifiers);
        spinbox_fake_lights_shape_mask_radius->setObjectName(QString::fromUtf8("spinbox_fake_lights_shape_mask_radius"));
        spinbox_fake_lights_shape_mask_radius->setDecimals(3);
        spinbox_fake_lights_shape_mask_radius->setMinimum(0.000000000000000);
        spinbox_fake_lights_shape_mask_radius->setMaximum(1000.000000000000000);
        spinbox_fake_lights_shape_mask_radius->setSingleStep(0.010000000000000);

        gridLayout_shape_modifiers->addWidget(spinbox_fake_lights_shape_mask_radius, 21, 1, 1, 1);

        label_shape_mask_softness = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_mask_softness->setObjectName(QString::fromUtf8("label_shape_mask_softness"));

        gridLayout_shape_modifiers->addWidget(label_shape_mask_softness, 22, 0, 1, 1);

        spinbox_fake_lights_shape_mask_softness = new MyDoubleSpinBox(groupBox_fake_lights_shape_modifiers);
        spinbox_fake_lights_shape_mask_softness->setObjectName(QString::fromUtf8("spinbox_fake_lights_shape_mask_softness"));
        spinbox_fake_lights_shape_mask_softness->setDecimals(3);
        spinbox_fake_lights_shape_mask_softness->setMinimum(0.000000000000000);
        spinbox_fake_lights_shape_mask_softness->setMaximum(1000.000000000000000);
        spinbox_fake_lights_shape_mask_softness->setSingleStep(0.010000000000000);

        gridLayout_shape_modifiers->addWidget(spinbox_fake_lights_shape_mask_softness, 22, 1, 1, 1);

        label_shape_spiral = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_spiral->setObjectName(QString::fromUtf8("label_shape_spiral"));

        gridLayout_shape_modifiers->addWidget(label_shape_spiral, 24, 0, 1, 1);

        spinbox_fake_lights_shape_spiral = new MyDoubleSpinBox(groupBox_fake_lights_shape_modifiers);
        spinbox_fake_lights_shape_spiral->setObjectName(QString::fromUtf8("spinbox_fake_lights_shape_spiral"));
        spinbox_fake_lights_shape_spiral->setDecimals(3);
        spinbox_fake_lights_shape_spiral->setMinimum(-1000.000000000000000);
        spinbox_fake_lights_shape_spiral->setMaximum(1000.000000000000000);
        spinbox_fake_lights_shape_spiral->setSingleStep(0.010000000000000);

        gridLayout_shape_modifiers->addWidget(spinbox_fake_lights_shape_spiral, 24, 1, 1, 1);

        label_shape_wave_x = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_wave_x->setObjectName(QString::fromUtf8("label_shape_wave_x"));

        gridLayout_shape_modifiers->addWidget(label_shape_wave_x, 25, 0, 1, 1);

        spinbox_fake_lights_shape_wave_x = new MyDoubleSpinBox(groupBox_fake_lights_shape_modifiers);
        spinbox_fake_lights_shape_wave_x->setObjectName(QString::fromUtf8("spinbox_fake_lights_shape_wave_x"));
        spinbox_fake_lights_shape_wave_x->setDecimals(3);
        spinbox_fake_lights_shape_wave_x->setMinimum(-1000.000000000000000);
        spinbox_fake_lights_shape_wave_x->setMaximum(1000.000000000000000);
        spinbox_fake_lights_shape_wave_x->setSingleStep(0.010000000000000);

        gridLayout_shape_modifiers->addWidget(spinbox_fake_lights_shape_wave_x, 25, 1, 1, 1);

        label_shape_wave_y = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_wave_y->setObjectName(QString::fromUtf8("label_shape_wave_y"));

        gridLayout_shape_modifiers->addWidget(label_shape_wave_y, 26, 0, 1, 1);

        spinbox_fake_lights_shape_wave_y = new MyDoubleSpinBox(groupBox_fake_lights_shape_modifiers);
        spinbox_fake_lights_shape_wave_y->setObjectName(QString::fromUtf8("spinbox_fake_lights_shape_wave_y"));
        spinbox_fake_lights_shape_wave_y->setDecimals(3);
        spinbox_fake_lights_shape_wave_y->setMinimum(-1000.000000000000000);
        spinbox_fake_lights_shape_wave_y->setMaximum(1000.000000000000000);
        spinbox_fake_lights_shape_wave_y->setSingleStep(0.010000000000000);

        gridLayout_shape_modifiers->addWidget(spinbox_fake_lights_shape_wave_y, 26, 1, 1, 1);

        label_shape_wave_z = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_wave_z->setObjectName(QString::fromUtf8("label_shape_wave_z"));

        gridLayout_shape_modifiers->addWidget(label_shape_wave_z, 27, 0, 1, 1);

        spinbox_fake_lights_shape_wave_z = new MyDoubleSpinBox(groupBox_fake_lights_shape_modifiers);
        spinbox_fake_lights_shape_wave_z->setObjectName(QString::fromUtf8("spinbox_fake_lights_shape_wave_z"));
        spinbox_fake_lights_shape_wave_z->setDecimals(3);
        spinbox_fake_lights_shape_wave_z->setMinimum(-1000.000000000000000);
        spinbox_fake_lights_shape_wave_z->setMaximum(1000.000000000000000);
        spinbox_fake_lights_shape_wave_z->setSingleStep(0.010000000000000);

        gridLayout_shape_modifiers->addWidget(spinbox_fake_lights_shape_wave_z, 27, 1, 1, 1);

        label_shape_wave_frequency = new QLabel(groupBox_fake_lights_shape_modifiers);
        label_shape_wave_frequency->setObjectName(QString::fromUtf8("label_shape_wave_frequency"));

        gridLayout_shape_modifiers->addWidget(label_shape_wave_frequency, 28, 0, 1, 1);

        spinbox_fake_lights_shape_wave_frequency = new MyDoubleSpinBox(groupBox_fake_lights_shape_modifiers);
        spinbox_fake_lights_shape_wave_frequency->setObjectName(QString::fromUtf8("spinbox_fake_lights_shape_wave_frequency"));
        spinbox_fake_lights_shape_wave_frequency->setDecimals(3);
        spinbox_fake_lights_shape_wave_frequency->setMinimum(0.000000000000000);
        spinbox_fake_lights_shape_wave_frequency->setMaximum(1000.000000000000000);
        spinbox_fake_lights_shape_wave_frequency->setSingleStep(0.010000000000000);

        gridLayout_shape_modifiers->addWidget(spinbox_fake_lights_shape_wave_frequency, 28, 1, 1, 1);


        verticalLayout_39->addWidget(groupBox_fake_lights_shape_modifiers);


        verticalLayout_fake_lights_panel_root->addWidget(groupCheck_fake_lights_enabled);

        groupBox_fake_lights_distance_mask = new QGroupBox(cFakeLightsPanel);
        groupBox_fake_lights_distance_mask->setObjectName(QString::fromUtf8("groupBox_fake_lights_distance_mask"));
        gridLayout_distance_mask = new QGridLayout(groupBox_fake_lights_distance_mask);
        gridLayout_distance_mask->setSpacing(2);
        gridLayout_distance_mask->setObjectName(QString::fromUtf8("gridLayout_distance_mask"));
        checkBox_fake_lights_mask_enabled = new MyCheckBox(groupBox_fake_lights_distance_mask);
        checkBox_fake_lights_mask_enabled->setObjectName(QString::fromUtf8("checkBox_fake_lights_mask_enabled"));

        gridLayout_distance_mask->addWidget(checkBox_fake_lights_mask_enabled, 0, 0, 1, 2);

        label_mask_threshold = new QLabel(groupBox_fake_lights_distance_mask);
        label_mask_threshold->setObjectName(QString::fromUtf8("label_mask_threshold"));

        gridLayout_distance_mask->addWidget(label_mask_threshold, 1, 0, 1, 1);

        spinbox_fake_lights_mask_threshold = new MyDoubleSpinBox(groupBox_fake_lights_distance_mask);
        spinbox_fake_lights_mask_threshold->setObjectName(QString::fromUtf8("spinbox_fake_lights_mask_threshold"));
        spinbox_fake_lights_mask_threshold->setDecimals(3);
        spinbox_fake_lights_mask_threshold->setMinimum(0.000000000000000);
        spinbox_fake_lights_mask_threshold->setMaximum(100.000000000000000);
        spinbox_fake_lights_mask_threshold->setSingleStep(0.010000000000000);

        gridLayout_distance_mask->addWidget(spinbox_fake_lights_mask_threshold, 1, 1, 1, 1);

        label_mask_sharpness = new QLabel(groupBox_fake_lights_distance_mask);
        label_mask_sharpness->setObjectName(QString::fromUtf8("label_mask_sharpness"));

        gridLayout_distance_mask->addWidget(label_mask_sharpness, 2, 0, 1, 1);

        spinbox_fake_lights_mask_sharpness = new MyDoubleSpinBox(groupBox_fake_lights_distance_mask);
        spinbox_fake_lights_mask_sharpness->setObjectName(QString::fromUtf8("spinbox_fake_lights_mask_sharpness"));
        spinbox_fake_lights_mask_sharpness->setDecimals(3);
        spinbox_fake_lights_mask_sharpness->setMinimum(0.000000000000000);
        spinbox_fake_lights_mask_sharpness->setMaximum(100.000000000000000);
        spinbox_fake_lights_mask_sharpness->setSingleStep(0.010000000000000);

        gridLayout_distance_mask->addWidget(spinbox_fake_lights_mask_sharpness, 2, 1, 1, 1);


        verticalLayout_fake_lights_panel_root->addWidget(groupBox_fake_lights_distance_mask);


        retranslateUi(cFakeLightsPanel);

        QMetaObject::connectSlotsByName(cFakeLightsPanel);
    } // setupUi

    void retranslateUi(QWidget *cFakeLightsPanel)
    {
#if QT_CONFIG(tooltip)
        groupCheck_fake_lights_enabled->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Simulates a large amount of lights and is relatively fast to render.</p><p>An orbit trap is a point, a 2D, or 3D shape defined in 3D space. The brightness of the point is dependent on how close the point's orbit gets to the orbit trap shape during the chosen iterations.</p><p>This effect is difficult to setup and often you need to try many different orbit trap settings.</p><p>These light sources illuminate the fractal surface, but do not cast shadows.</p><p>Example:</p><p><img src=\":/tooltips/tooltips_images/image - shader - orbit trap lights.jpg\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_fake_lights_enabled->setTitle(QCoreApplication::translate("cFakeLightsPanel", "Orbit &trap lights", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_fake_lights_relative_center->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Interpret the Orbit trap center relative to the fractal\342\200\231s origin.</p><p>When enabled, the orbit\342\200\221trap distance is computed using coordinates relative to the fractal start/constant (z \342\210\222 C), effectively anchoring the trap to the fractal\342\200\231s local origin. When disabled, the distance uses absolute coordinates (z), so the trap center is in world space.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_fake_lights_relative_center->setText(QCoreApplication::translate("cFakeLightsPanel", "Orbit trap center relative to the origin", nullptr));
        label_60->setText(QCoreApplication::translate("cFakeLightsPanel", "Minimum iteration:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_fake_lights_orbit_trap_size->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Size of the Orbit trap shape used by Fake lights.</p><p>Meaning depends on Shape: - Point: sphere radius around the point - Line: cylinder radius around the line - Circle: ring radius - Square: half edge length - Sphere: shell radius - Cube: half edge length</p><p>Applied in the trap\342\200\231s local space around the Orbit trap center. Use \342\200\234Thickness\342\200\235 to control the shell\342\200\231s falloff width.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_91->setText(QCoreApplication::translate("cFakeLightsPanel", "Maximum iteration:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_orbit_trap_y->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of orbit trap point</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        vect3_fake_lights_orbit_trap_z->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of orbit trap point</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinboxInt_fake_lights_min_iter->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>First iteration taken for orbit trap calculation</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_106->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
        label_105->setText(QCoreApplication::translate("cFakeLightsPanel", "Shape size:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_fake_lights_thickness->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Brightness of visible lights</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_fake_lights_orbit_trap_shape->setItemText(0, QCoreApplication::translate("cFakeLightsPanel", "Point", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(1, QCoreApplication::translate("cFakeLightsPanel", "Line", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(2, QCoreApplication::translate("cFakeLightsPanel", "Cirkel", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(3, QCoreApplication::translate("cFakeLightsPanel", "Vierkant", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(4, QCoreApplication::translate("cFakeLightsPanel", "Bol", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(5, QCoreApplication::translate("cFakeLightsPanel", "Kubus", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(6, QCoreApplication::translate("cFakeLightsPanel", "Triangle", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(7, QCoreApplication::translate("cFakeLightsPanel", "Hexagon", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(8, QCoreApplication::translate("cFakeLightsPanel", "Torus", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(9, QCoreApplication::translate("cFakeLightsPanel", "Cylinder", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(10, QCoreApplication::translate("cFakeLightsPanel", "Cone", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(11, QCoreApplication::translate("cFakeLightsPanel", "Pyramid", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(12, QCoreApplication::translate("cFakeLightsPanel", "Octahedron", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(13, QCoreApplication::translate("cFakeLightsPanel", "Ellips", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(14, QCoreApplication::translate("cFakeLightsPanel", "Rectangle", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(15, QCoreApplication::translate("cFakeLightsPanel", "Kruis", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(16, QCoreApplication::translate("cFakeLightsPanel", "Star", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(17, QCoreApplication::translate("cFakeLightsPanel", "Diamond", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(18, QCoreApplication::translate("cFakeLightsPanel", "Ring", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(19, QCoreApplication::translate("cFakeLightsPanel", "Capsule", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(20, QCoreApplication::translate("cFakeLightsPanel", "Prism", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(21, QCoreApplication::translate("cFakeLightsPanel", "Torus Knot", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(22, QCoreApplication::translate("cFakeLightsPanel", "Box Frame", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(23, QCoreApplication::translate("cFakeLightsPanel", "Cone Infinite", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(24, QCoreApplication::translate("cFakeLightsPanel", "Cylinder Cap", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(25, QCoreApplication::translate("cFakeLightsPanel", "Superellipsoid", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(26, QCoreApplication::translate("cFakeLightsPanel", "Plane", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(27, QCoreApplication::translate("cFakeLightsPanel", "Disc", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(28, QCoreApplication::translate("cFakeLightsPanel", "Gear", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(29, QCoreApplication::translate("cFakeLightsPanel", "Spiral", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(30, QCoreApplication::translate("cFakeLightsPanel", "Heart", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(31, QCoreApplication::translate("cFakeLightsPanel", "Crescent", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(32, QCoreApplication::translate("cFakeLightsPanel", "Arrow", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(33, QCoreApplication::translate("cFakeLightsPanel", "Rounded Box", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(34, QCoreApplication::translate("cFakeLightsPanel", "Stadium", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(35, QCoreApplication::translate("cFakeLightsPanel", "Polygon 5", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(36, QCoreApplication::translate("cFakeLightsPanel", "Polygon 8", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(37, QCoreApplication::translate("cFakeLightsPanel", "Trefoil Knot", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(38, QCoreApplication::translate("cFakeLightsPanel", "Figure Eight", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(39, QCoreApplication::translate("cFakeLightsPanel", "Mobius Strip", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(40, QCoreApplication::translate("cFakeLightsPanel", "Torus Sector", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(41, QCoreApplication::translate("cFakeLightsPanel", "Helix", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(42, QCoreApplication::translate("cFakeLightsPanel", "Cone Rounded", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(43, QCoreApplication::translate("cFakeLightsPanel", "Cylinder Hollow", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(44, QCoreApplication::translate("cFakeLightsPanel", "Sphere Hollow", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(45, QCoreApplication::translate("cFakeLightsPanel", "Torus Twist", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(46, QCoreApplication::translate("cFakeLightsPanel", "Grid", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(47, QCoreApplication::translate("cFakeLightsPanel", "Lattice", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(48, QCoreApplication::translate("cFakeLightsPanel", "Sponge", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(49, QCoreApplication::translate("cFakeLightsPanel", "Tree", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(50, QCoreApplication::translate("cFakeLightsPanel", "Knot 34", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(51, QCoreApplication::translate("cFakeLightsPanel", "Spiral 3D", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(52, QCoreApplication::translate("cFakeLightsPanel", "Noise", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(53, QCoreApplication::translate("cFakeLightsPanel", "Voronoi", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(54, QCoreApplication::translate("cFakeLightsPanel", "Mandelbrot 2D", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(55, QCoreApplication::translate("cFakeLightsPanel", "Julia 2D", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(56, QCoreApplication::translate("cFakeLightsPanel", "Sierpinski", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(57, QCoreApplication::translate("cFakeLightsPanel", "Koch", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(58, QCoreApplication::translate("cFakeLightsPanel", "Dragon", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(59, QCoreApplication::translate("cFakeLightsPanel", "Hilbert", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(60, QCoreApplication::translate("cFakeLightsPanel", "Gyroid", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(61, QCoreApplication::translate("cFakeLightsPanel", "Schwarz P", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(62, QCoreApplication::translate("cFakeLightsPanel", "Schwarz D", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(63, QCoreApplication::translate("cFakeLightsPanel", "Neovius", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(64, QCoreApplication::translate("cFakeLightsPanel", "Labyrinth", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(65, QCoreApplication::translate("cFakeLightsPanel", "Fiber", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(66, QCoreApplication::translate("cFakeLightsPanel", "Astroid", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(67, QCoreApplication::translate("cFakeLightsPanel", "Deltoid", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(68, QCoreApplication::translate("cFakeLightsPanel", "Lemniscate", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(69, QCoreApplication::translate("cFakeLightsPanel", "Limacon", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(70, QCoreApplication::translate("cFakeLightsPanel", "Spherical Harmonics", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(71, QCoreApplication::translate("cFakeLightsPanel", "Superformula", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(72, QCoreApplication::translate("cFakeLightsPanel", "Fern", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(73, QCoreApplication::translate("cFakeLightsPanel", "Shell", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(74, QCoreApplication::translate("cFakeLightsPanel", "Coral", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(75, QCoreApplication::translate("cFakeLightsPanel", "Crystal", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(76, QCoreApplication::translate("cFakeLightsPanel", "Honeycomb", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(77, QCoreApplication::translate("cFakeLightsPanel", "Chain", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(78, QCoreApplication::translate("cFakeLightsPanel", "Woven", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(79, QCoreApplication::translate("cFakeLightsPanel", "Net", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(80, QCoreApplication::translate("cFakeLightsPanel", "Coil", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(81, QCoreApplication::translate("cFakeLightsPanel", "Vortex", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(82, QCoreApplication::translate("cFakeLightsPanel", "Ripple", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(83, QCoreApplication::translate("cFakeLightsPanel", "Shockwave", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(84, QCoreApplication::translate("cFakeLightsPanel", "Orbital", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(85, QCoreApplication::translate("cFakeLightsPanel", "Nebula", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(86, QCoreApplication::translate("cFakeLightsPanel", "Julia 3D", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(87, QCoreApplication::translate("cFakeLightsPanel", "Mandelbrot 3D", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(88, QCoreApplication::translate("cFakeLightsPanel", "Burning Ship", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(89, QCoreApplication::translate("cFakeLightsPanel", "Tricorn", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(90, QCoreApplication::translate("cFakeLightsPanel", "Multibrot", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(91, QCoreApplication::translate("cFakeLightsPanel", "Phoenix", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(92, QCoreApplication::translate("cFakeLightsPanel", "Newton", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(93, QCoreApplication::translate("cFakeLightsPanel", "Nova", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(94, QCoreApplication::translate("cFakeLightsPanel", "Spider", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(95, QCoreApplication::translate("cFakeLightsPanel", "Dendrite", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(96, QCoreApplication::translate("cFakeLightsPanel", "Lorenz", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(97, QCoreApplication::translate("cFakeLightsPanel", "Rossler", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(98, QCoreApplication::translate("cFakeLightsPanel", "Polyfold", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(99, QCoreApplication::translate("cFakeLightsPanel", "Apollonian", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(100, QCoreApplication::translate("cFakeLightsPanel", "Kleinian", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(101, QCoreApplication::translate("cFakeLightsPanel", "Fibonacci", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(102, QCoreApplication::translate("cFakeLightsPanel", "Celtic", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(103, QCoreApplication::translate("cFakeLightsPanel", "Crown", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(104, QCoreApplication::translate("cFakeLightsPanel", "Cactus", nullptr));
        comboBox_fake_lights_orbit_trap_shape->setItemText(105, QCoreApplication::translate("cFakeLightsPanel", "Siegel Disk", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_fake_lights_orbit_trap_shape->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body> <p>Select the orbit\342\200\221trap shape used by Fake lights (lighting is driven by the distance to this shape).</p> <p><i>Point</i> \342\200\224 a single point source near the trap center (default).</p> <p><i>Line</i> \342\200\224 an infinite line through the center; use Orbit rotation to set its direction.</p> <p><i>Circle</i> \342\200\224 a circular ring around a central axis; Size = ring radius; Rotation sets the axis.</p> <p><i>Square</i> \342\200\224 a square ring; Size = half edge; Rotation sets orientation.</p> <p><i>Sphere</i> \342\200\224 a spherical shell; Size = radius.</p> <p><i>Cube</i> \342\200\224 a cubic shell; Size = half edge length.</p> <p>Tip: Use Thickness to control falloff width, Visibility/Visibility size for reach, and set center/Relative center and Orbit rotation as needed. Effective when \342\200\234Fake lights\342\200\235 is enabled.</p> </body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_92->setText(QCoreApplication::translate("cFakeLightsPanel", "Intensity on surface:", nullptr));
        label_93->setText(QCoreApplication::translate("cFakeLightsPanel", "Visibility of glow (volumetric effect):", nullptr));
        label_108->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_fake_lights_visibility->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Brightness of visible lights. It is volumetric effect.</p><p>Quality of this effect can by controled by <span style=\" font-style:italic;\">Effects / Volumetric / Custom DE step multiplier for volumetric effects</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_98->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_color->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color of light source</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_color->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
        label_97->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        spinboxd3_fake_lights_orbit_rotation_z->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Rotate the Orbit trap shape around the selected axis (degrees).</p><p>Effects by shape: - Line: sets the line direction. - Circle: sets the ring\342\200\231s axis. - Square: sets the plane/orientation. - Cube: sets the cube orientation. - Sphere: usually no visible effect. - Point: no effect.</p><p>Notes: - Angles are in degrees; internal order is Z \342\206\222 Y \342\206\222 X. - Rotation is applied around the Orbit trap center (see \342\200\234Relative center\342\200\235).</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinboxd3_fake_lights_orbit_rotation_z->setPrefix(QString());
        spinboxd3_fake_lights_orbit_rotation_z->setSuffix(QString());
#if QT_CONFIG(tooltip)
        spinboxd3_fake_lights_orbit_rotation_x->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Rotate the Orbit trap shape around the selected axis (degrees).</p><p>Effects by shape: - Line: sets the line direction. - Circle: sets the ring\342\200\231s axis. - Square: sets the plane/orientation. - Cube: sets the cube orientation. - Sphere: usually no visible effect. - Point: no effect.</p><p>Notes: - Angles are in degrees; internal order is Z \342\206\222 Y \342\206\222 X. - Rotation is applied around the Orbit trap center (see \342\200\234Relative center\342\200\235).</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinboxd3_fake_lights_orbit_rotation_x->setPrefix(QString());
        spinboxd3_fake_lights_orbit_rotation_x->setSuffix(QString());
        label_104->setText(QCoreApplication::translate("cFakeLightsPanel", "Vorm:", nullptr));
        label_96->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
        label_102->setText(QCoreApplication::translate("cFakeLightsPanel", "Shape rotation:", nullptr));
        label_107->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
        label_94->setText(QCoreApplication::translate("cFakeLightsPanel", "Softness:", nullptr));
        label_45->setText(QCoreApplication::translate("cFakeLightsPanel", "Kleur:", nullptr));
#if QT_CONFIG(tooltip)
        spinboxd3_fake_lights_orbit_rotation_y->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Rotate the Orbit trap shape around the selected axis (degrees).</p><p>Effects by shape: - Line: sets the line direction. - Circle: sets the ring\342\200\231s axis. - Square: sets the plane/orientation. - Cube: sets the cube orientation. - Sphere: usually no visible effect. - Point: no effect.</p><p>Notes: - Angles are in degrees; internal order is Z \342\206\222 Y \342\206\222 X. - Rotation is applied around the Orbit trap center (see \342\200\234Relative center\342\200\235).</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinboxd3_fake_lights_orbit_rotation_y->setPrefix(QString());
        spinboxd3_fake_lights_orbit_rotation_y->setSuffix(QString());
        groupCheck_fake_lights_color_2_enabled->setTitle(QCoreApplication::translate("cFakeLightsPanel", "Enable color 2 (for second and further iterations)", nullptr));
        label_48->setText(QCoreApplication::translate("cFakeLightsPanel", "Color 2:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_color_2->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color of light source</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_color_2->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
        groupCheck_fake_lights_color_3_enabled->setTitle(QCoreApplication::translate("cFakeLightsPanel", "Enable color 3 (for third and further iterations)", nullptr));
        label_51->setText(QCoreApplication::translate("cFakeLightsPanel", "Color 3:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_color_3->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color of light source</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_color_3->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
#if QT_CONFIG(tooltip)
        logedit_fake_lights_intensity->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Intensity of illumination of fractal surface</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinboxInt_fake_lights_max_iter->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Last iteration taken for orbit trap calculation</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinbox_fake_lights_visibility_size->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Size of visible lights (scale is logarithmic)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_fake_lights_visibility_size->setPrefix(QString());
        spinbox_fake_lights_visibility_size->setSuffix(QString());
        label_95->setText(QCoreApplication::translate("cFakeLightsPanel", "Orbit trap center:", nullptr));
        label_109->setText(QCoreApplication::translate("cFakeLightsPanel", "Relative thickness:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_orbit_trap_x->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of orbit trap point</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_position_mode_->setText(QCoreApplication::translate("cFakeLightsPanel", "Position mode:", nullptr));
        comboBox_fake_lights_position_mode->setItemText(0, QCoreApplication::translate("cFakeLightsPanel", "World", nullptr));
        comboBox_fake_lights_position_mode->setItemText(1, QCoreApplication::translate("cFakeLightsPanel", "Camera Relative", nullptr));
        comboBox_fake_lights_position_mode->setItemText(2, QCoreApplication::translate("cFakeLightsPanel", "Target Point", nullptr));
        comboBox_fake_lights_position_mode->setItemText(3, QCoreApplication::translate("cFakeLightsPanel", "Fractal Center", nullptr));
        comboBox_fake_lights_position_mode->setItemText(4, QCoreApplication::translate("cFakeLightsPanel", "Path Circle", nullptr));
        comboBox_fake_lights_position_mode->setItemText(5, QCoreApplication::translate("cFakeLightsPanel", "Path Spiral", nullptr));
        comboBox_fake_lights_position_mode->setItemText(6, QCoreApplication::translate("cFakeLightsPanel", "Orbit Around Target", nullptr));

        label_transition_speed_->setText(QCoreApplication::translate("cFakeLightsPanel", "Transition speed:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fake_lights_transition_speed->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Speed of smooth transition between positioning modes. 0 = instant switch, higher values = gradual blend.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_fake_lights_world->setTitle(QCoreApplication::translate("cFakeLightsPanel", "World mode settings", nullptr));
        label_world_offset->setText(QCoreApplication::translate("cFakeLightsPanel", "Offset:", nullptr));
        label_world_offset_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
        label_world_offset_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
        label_world_offset_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
        label_world_scale->setText(QCoreApplication::translate("cFakeLightsPanel", "Scale:", nullptr));
        label_world_rotation->setText(QCoreApplication::translate("cFakeLightsPanel", "Rotatie:", nullptr));
        label_world_rotation_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
        label_world_rotation_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
        label_world_rotation_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
        pushButton_reset_world->setText(QCoreApplication::translate("cFakeLightsPanel", "Reset to Defaults", nullptr));
        groupBox_fake_lights_camera->setTitle(QCoreApplication::translate("cFakeLightsPanel", "Camera mode settings", nullptr));
        label_camera_offset->setText(QCoreApplication::translate("cFakeLightsPanel", "Offset:", nullptr));
        label_camera_offset_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
        label_camera_offset_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
        label_camera_offset_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
        label_camera_scale->setText(QCoreApplication::translate("cFakeLightsPanel", "Scale:", nullptr));
        label_camera_rotation->setText(QCoreApplication::translate("cFakeLightsPanel", "Rotatie:", nullptr));
        label_camera_rotation_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
        label_camera_rotation_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
        label_camera_rotation_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
        pushButton_reset_camera->setText(QCoreApplication::translate("cFakeLightsPanel", "Reset to Defaults", nullptr));
        groupBox_fake_lights_target->setTitle(QCoreApplication::translate("cFakeLightsPanel", "Target mode settings", nullptr));
        label_target_offset->setText(QCoreApplication::translate("cFakeLightsPanel", "Offset:", nullptr));
        label_target_offset_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
        label_target_offset_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
        label_target_offset_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
        label_target_scale->setText(QCoreApplication::translate("cFakeLightsPanel", "Scale:", nullptr));
        label_target_rotation->setText(QCoreApplication::translate("cFakeLightsPanel", "Rotatie:", nullptr));
        label_target_rotation_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
        label_target_rotation_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
        label_target_rotation_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
        pushButton_reset_target->setText(QCoreApplication::translate("cFakeLightsPanel", "Reset to Defaults", nullptr));
        groupBox_fake_lights_fractal_center->setTitle(QCoreApplication::translate("cFakeLightsPanel", "Fractal center mode settings", nullptr));
        label_fractal_center_offset->setText(QCoreApplication::translate("cFakeLightsPanel", "Offset:", nullptr));
        label_fractal_center_offset_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
        label_fractal_center_offset_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
        label_fractal_center_offset_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
        label_fractal_center_scale->setText(QCoreApplication::translate("cFakeLightsPanel", "Scale:", nullptr));
        label_fractal_center_rotation->setText(QCoreApplication::translate("cFakeLightsPanel", "Rotatie:", nullptr));
        label_fractal_center_rotation_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
        label_fractal_center_rotation_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
        label_fractal_center_rotation_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
        pushButton_reset_fractal_center->setText(QCoreApplication::translate("cFakeLightsPanel", "Reset to Defaults", nullptr));
        groupBox_fake_lights_path_circle->setTitle(QCoreApplication::translate("cFakeLightsPanel", "Path circle mode settings", nullptr));
        label_path_circle_offset->setText(QCoreApplication::translate("cFakeLightsPanel", "Offset:", nullptr));
        label_path_circle_offset_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
        label_path_circle_offset_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
        label_path_circle_offset_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
        label_path_circle_scale->setText(QCoreApplication::translate("cFakeLightsPanel", "Scale:", nullptr));
        label_path_circle_rotation->setText(QCoreApplication::translate("cFakeLightsPanel", "Rotatie:", nullptr));
        label_path_circle_rotation_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
        label_path_circle_rotation_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
        label_path_circle_rotation_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
        label_path_circle_radius->setText(QCoreApplication::translate("cFakeLightsPanel", "Path radius:", nullptr));
        pushButton_reset_path_circle->setText(QCoreApplication::translate("cFakeLightsPanel", "Reset to Defaults", nullptr));
        groupBox_fake_lights_path_spiral->setTitle(QCoreApplication::translate("cFakeLightsPanel", "Path spiral mode settings", nullptr));
        label_path_spiral_offset->setText(QCoreApplication::translate("cFakeLightsPanel", "Offset:", nullptr));
        label_path_spiral_offset_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
        label_path_spiral_offset_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
        label_path_spiral_offset_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
        label_path_spiral_scale->setText(QCoreApplication::translate("cFakeLightsPanel", "Scale:", nullptr));
        label_path_spiral_rotation->setText(QCoreApplication::translate("cFakeLightsPanel", "Rotatie:", nullptr));
        label_path_spiral_rotation_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
        label_path_spiral_rotation_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
        label_path_spiral_rotation_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
        label_path_spiral_radius->setText(QCoreApplication::translate("cFakeLightsPanel", "Path radius:", nullptr));
        pushButton_reset_path_spiral->setText(QCoreApplication::translate("cFakeLightsPanel", "Reset to Defaults", nullptr));
        groupBox_fake_lights_orbit_target->setTitle(QCoreApplication::translate("cFakeLightsPanel", "Orbit around target mode settings", nullptr));
        label_orbit_target_offset->setText(QCoreApplication::translate("cFakeLightsPanel", "Offset:", nullptr));
        label_orbit_target_offset_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
        label_orbit_target_offset_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
        label_orbit_target_offset_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
        label_orbit_target_scale->setText(QCoreApplication::translate("cFakeLightsPanel", "Scale:", nullptr));
        label_orbit_target_rotation->setText(QCoreApplication::translate("cFakeLightsPanel", "Rotatie:", nullptr));
        label_orbit_target_rotation_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
        label_orbit_target_rotation_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
        label_orbit_target_rotation_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
        label_orbit_target_radius->setText(QCoreApplication::translate("cFakeLightsPanel", "Path radius:", nullptr));
        pushButton_reset_orbit_target->setText(QCoreApplication::translate("cFakeLightsPanel", "Reset to Defaults", nullptr));
        groupBox_fake_lights_multi_center->setTitle(QCoreApplication::translate("cFakeLightsPanel", "Multi-Center Orbit Trap", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_fake_lights_multi_center_enabled->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Enable multiple orbit trap centers. When enabled, the orbit trap is evaluated at 24 additional positions and the weighted minimum distance is used.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_fake_lights_multi_center_enabled->setText(QCoreApplication::translate("cFakeLightsPanel", "Enable multi-center orbit trap", nullptr));
        label_multi_center_1->setText(QCoreApplication::translate("cFakeLightsPanel", "Center 1:", nullptr));
        label_multi_center_1_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_1_x->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 1</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_1_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_1_y->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 1</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_1_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_1_z->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 1</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_weight_1->setText(QCoreApplication::translate("cFakeLightsPanel", "Weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fake_lights_multi_center_weight_1->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Weight for multi-center point 1. Higher values make this center more influential.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_color_1->setText(QCoreApplication::translate("cFakeLightsPanel", "Kleur:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_1->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color for multi-center orbit trap point 1</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_1->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
        label_multi_center_2->setText(QCoreApplication::translate("cFakeLightsPanel", "Center 2:", nullptr));
        label_multi_center_2_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_2_x->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 2</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_2_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_2_y->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 2</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_2_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_2_z->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 2</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_weight_2->setText(QCoreApplication::translate("cFakeLightsPanel", "Weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fake_lights_multi_center_weight_2->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Weight for multi-center point 2. Higher values make this center more influential.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_color_2->setText(QCoreApplication::translate("cFakeLightsPanel", "Kleur:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_2->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color for multi-center orbit trap point 2</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_2->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
        label_multi_center_3->setText(QCoreApplication::translate("cFakeLightsPanel", "Center 3:", nullptr));
        label_multi_center_3_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_3_x->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 3</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_3_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_3_y->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 3</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_3_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_3_z->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 3</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_weight_3->setText(QCoreApplication::translate("cFakeLightsPanel", "Weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fake_lights_multi_center_weight_3->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Weight for multi-center point 3. Higher values make this center more influential.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_color_3->setText(QCoreApplication::translate("cFakeLightsPanel", "Kleur:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_3->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color for multi-center orbit trap point 3</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_3->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
        label_multi_center_4->setText(QCoreApplication::translate("cFakeLightsPanel", "Center 4:", nullptr));
        label_multi_center_4_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_4_x->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 4</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_4_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_4_y->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 4</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_4_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_4_z->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 4</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_weight_4->setText(QCoreApplication::translate("cFakeLightsPanel", "Weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fake_lights_multi_center_weight_4->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Weight for multi-center point 4. Higher values make this center more influential.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_color_4->setText(QCoreApplication::translate("cFakeLightsPanel", "Kleur:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_4->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color for multi-center orbit trap point 4</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_4->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
        label_multi_center_5->setText(QCoreApplication::translate("cFakeLightsPanel", "Center 5:", nullptr));
        label_multi_center_5_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_5_x->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 5</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_5_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_5_y->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 5</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_5_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_5_z->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 5</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_weight_5->setText(QCoreApplication::translate("cFakeLightsPanel", "Weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fake_lights_multi_center_weight_5->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Weight for multi-center point 5. Higher values make this center more influential.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_color_5->setText(QCoreApplication::translate("cFakeLightsPanel", "Kleur:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_5->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color for multi-center orbit trap point 5</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_5->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
        label_multi_center_6->setText(QCoreApplication::translate("cFakeLightsPanel", "Center 6:", nullptr));
        label_multi_center_6_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_6_x->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 6</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_6_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_6_y->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 6</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_6_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_6_z->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 6</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_weight_6->setText(QCoreApplication::translate("cFakeLightsPanel", "Weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fake_lights_multi_center_weight_6->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Weight for multi-center point 6. Higher values make this center more influential.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_color_6->setText(QCoreApplication::translate("cFakeLightsPanel", "Kleur:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_6->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color for multi-center orbit trap point 6</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_6->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
        label_multi_center_7->setText(QCoreApplication::translate("cFakeLightsPanel", "Center 7:", nullptr));
        label_multi_center_7_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_7_x->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 7</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_7_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_7_y->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 7</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_7_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_7_z->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 7</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_weight_7->setText(QCoreApplication::translate("cFakeLightsPanel", "Weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fake_lights_multi_center_weight_7->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Weight for multi-center point 7. Higher values make this center more influential.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_color_7->setText(QCoreApplication::translate("cFakeLightsPanel", "Kleur:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_7->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color for multi-center orbit trap point 7</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_7->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
        label_multi_center_8->setText(QCoreApplication::translate("cFakeLightsPanel", "Center 8:", nullptr));
        label_multi_center_8_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_8_x->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 8</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_8_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_8_y->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 8</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_8_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_8_z->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 8</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_weight_8->setText(QCoreApplication::translate("cFakeLightsPanel", "Weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fake_lights_multi_center_weight_8->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Weight for multi-center point 8. Higher values make this center more influential.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_color_8->setText(QCoreApplication::translate("cFakeLightsPanel", "Kleur:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_8->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color for multi-center orbit trap point 8</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_8->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
        label_multi_center_9->setText(QCoreApplication::translate("cFakeLightsPanel", "Center 9:", nullptr));
        label_multi_center_9_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_9_x->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 9</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_9_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_9_y->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 9</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_9_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_9_z->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 9</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_weight_9->setText(QCoreApplication::translate("cFakeLightsPanel", "Weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fake_lights_multi_center_weight_9->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Weight for multi-center point 9. Higher values make this center more influential.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_color_9->setText(QCoreApplication::translate("cFakeLightsPanel", "Kleur:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_9->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color for multi-center orbit trap point 9</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_9->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
        label_multi_center_10->setText(QCoreApplication::translate("cFakeLightsPanel", "Center 10:", nullptr));
        label_multi_center_10_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_10_x->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 10</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_10_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_10_y->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 10</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_10_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_10_z->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 10</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_weight_10->setText(QCoreApplication::translate("cFakeLightsPanel", "Weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fake_lights_multi_center_weight_10->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Weight for multi-center point 10. Higher values make this center more influential.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_color_10->setText(QCoreApplication::translate("cFakeLightsPanel", "Kleur:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_10->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color for multi-center orbit trap point 10</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_10->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
        label_multi_center_11->setText(QCoreApplication::translate("cFakeLightsPanel", "Center 11:", nullptr));
        label_multi_center_11_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_11_x->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 11</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_11_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_11_y->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 11</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_11_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_11_z->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 11</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_weight_11->setText(QCoreApplication::translate("cFakeLightsPanel", "Weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fake_lights_multi_center_weight_11->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Weight for multi-center point 11. Higher values make this center more influential.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_color_11->setText(QCoreApplication::translate("cFakeLightsPanel", "Kleur:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_11->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color for multi-center orbit trap point 11</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_11->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
        label_multi_center_12->setText(QCoreApplication::translate("cFakeLightsPanel", "Center 12:", nullptr));
        label_multi_center_12_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_12_x->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 12</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_12_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_12_y->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 12</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_12_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_12_z->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 12</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_weight_12->setText(QCoreApplication::translate("cFakeLightsPanel", "Weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fake_lights_multi_center_weight_12->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Weight for multi-center point 12. Higher values make this center more influential.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_color_12->setText(QCoreApplication::translate("cFakeLightsPanel", "Kleur:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_12->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color for multi-center orbit trap point 12</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_12->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
        label_multi_center_13->setText(QCoreApplication::translate("cFakeLightsPanel", "Center 13:", nullptr));
        label_multi_center_13_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_13_x->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 13</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_13_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_13_y->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 13</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_13_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_13_z->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 13</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_weight_13->setText(QCoreApplication::translate("cFakeLightsPanel", "Weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fake_lights_multi_center_weight_13->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Weight for multi-center point 13. Higher values make this center more influential.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_color_13->setText(QCoreApplication::translate("cFakeLightsPanel", "Kleur:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_13->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color for multi-center orbit trap point 13</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_13->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
        label_multi_center_14->setText(QCoreApplication::translate("cFakeLightsPanel", "Center 14:", nullptr));
        label_multi_center_14_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_14_x->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 14</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_14_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_14_y->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 14</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_14_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_14_z->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 14</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_weight_14->setText(QCoreApplication::translate("cFakeLightsPanel", "Weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fake_lights_multi_center_weight_14->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Weight for multi-center point 14. Higher values make this center more influential.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_color_14->setText(QCoreApplication::translate("cFakeLightsPanel", "Kleur:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_14->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color for multi-center orbit trap point 14</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_14->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
        label_multi_center_15->setText(QCoreApplication::translate("cFakeLightsPanel", "Center 15:", nullptr));
        label_multi_center_15_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_15_x->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 15</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_15_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_15_y->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 15</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_15_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_15_z->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 15</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_weight_15->setText(QCoreApplication::translate("cFakeLightsPanel", "Weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fake_lights_multi_center_weight_15->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Weight for multi-center point 15. Higher values make this center more influential.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_color_15->setText(QCoreApplication::translate("cFakeLightsPanel", "Kleur:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_15->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color for multi-center orbit trap point 15</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_15->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
        label_multi_center_16->setText(QCoreApplication::translate("cFakeLightsPanel", "Center 16:", nullptr));
        label_multi_center_16_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_16_x->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 16</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_16_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_16_y->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 16</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_16_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_16_z->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 16</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_weight_16->setText(QCoreApplication::translate("cFakeLightsPanel", "Weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fake_lights_multi_center_weight_16->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Weight for multi-center point 16. Higher values make this center more influential.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_color_16->setText(QCoreApplication::translate("cFakeLightsPanel", "Kleur:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_16->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color for multi-center orbit trap point 16</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_16->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
        label_multi_center_17->setText(QCoreApplication::translate("cFakeLightsPanel", "Center 17:", nullptr));
        label_multi_center_17_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_17_x->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 17</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_17_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_17_y->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 17</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_17_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_17_z->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 17</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_weight_17->setText(QCoreApplication::translate("cFakeLightsPanel", "Weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fake_lights_multi_center_weight_17->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Weight for multi-center point 17. Higher values make this center more influential.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_color_17->setText(QCoreApplication::translate("cFakeLightsPanel", "Kleur:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_17->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color for multi-center orbit trap point 17</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_17->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
        label_multi_center_18->setText(QCoreApplication::translate("cFakeLightsPanel", "Center 18:", nullptr));
        label_multi_center_18_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_18_x->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 18</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_18_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_18_y->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 18</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_18_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_18_z->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 18</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_weight_18->setText(QCoreApplication::translate("cFakeLightsPanel", "Weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fake_lights_multi_center_weight_18->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Weight for multi-center point 18. Higher values make this center more influential.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_color_18->setText(QCoreApplication::translate("cFakeLightsPanel", "Kleur:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_18->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color for multi-center orbit trap point 18</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_18->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
        label_multi_center_19->setText(QCoreApplication::translate("cFakeLightsPanel", "Center 19:", nullptr));
        label_multi_center_19_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_19_x->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 19</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_19_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_19_y->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 19</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_19_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_19_z->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 19</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_weight_19->setText(QCoreApplication::translate("cFakeLightsPanel", "Weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fake_lights_multi_center_weight_19->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Weight for multi-center point 19. Higher values make this center more influential.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_color_19->setText(QCoreApplication::translate("cFakeLightsPanel", "Kleur:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_19->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color for multi-center orbit trap point 19</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_19->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
        label_multi_center_20->setText(QCoreApplication::translate("cFakeLightsPanel", "Center 20:", nullptr));
        label_multi_center_20_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_20_x->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 20</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_20_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_20_y->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 20</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_20_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_20_z->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 20</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_weight_20->setText(QCoreApplication::translate("cFakeLightsPanel", "Weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fake_lights_multi_center_weight_20->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Weight for multi-center point 20. Higher values make this center more influential.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_color_20->setText(QCoreApplication::translate("cFakeLightsPanel", "Kleur:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_20->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color for multi-center orbit trap point 20</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_20->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
        label_multi_center_21->setText(QCoreApplication::translate("cFakeLightsPanel", "Center 21:", nullptr));
        label_multi_center_21_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_21_x->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 21</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_21_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_21_y->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 21</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_21_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_21_z->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 21</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_weight_21->setText(QCoreApplication::translate("cFakeLightsPanel", "Weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fake_lights_multi_center_weight_21->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Weight for multi-center point 21. Higher values make this center more influential.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_color_21->setText(QCoreApplication::translate("cFakeLightsPanel", "Kleur:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_21->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color for multi-center orbit trap point 21</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_21->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
        label_multi_center_22->setText(QCoreApplication::translate("cFakeLightsPanel", "Center 22:", nullptr));
        label_multi_center_22_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_22_x->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 22</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_22_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_22_y->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 22</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_22_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_22_z->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 22</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_weight_22->setText(QCoreApplication::translate("cFakeLightsPanel", "Weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fake_lights_multi_center_weight_22->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Weight for multi-center point 22. Higher values make this center more influential.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_color_22->setText(QCoreApplication::translate("cFakeLightsPanel", "Kleur:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_22->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color for multi-center orbit trap point 22</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_22->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
        label_multi_center_23->setText(QCoreApplication::translate("cFakeLightsPanel", "Center 23:", nullptr));
        label_multi_center_23_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_23_x->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 23</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_23_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_23_y->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 23</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_23_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_23_z->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 23</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_weight_23->setText(QCoreApplication::translate("cFakeLightsPanel", "Weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fake_lights_multi_center_weight_23->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Weight for multi-center point 23. Higher values make this center more influential.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_color_23->setText(QCoreApplication::translate("cFakeLightsPanel", "Kleur:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_23->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color for multi-center orbit trap point 23</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_23->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
        label_multi_center_24->setText(QCoreApplication::translate("cFakeLightsPanel", "Center 24:", nullptr));
        label_multi_center_24_x->setText(QCoreApplication::translate("cFakeLightsPanel", "x:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_24_x->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 24</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_24_y->setText(QCoreApplication::translate("cFakeLightsPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_24_y->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 24</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_24_z->setText(QCoreApplication::translate("cFakeLightsPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_fake_lights_multi_center_24_z->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Position of multi-center orbit trap point 24</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_weight_24->setText(QCoreApplication::translate("cFakeLightsPanel", "Weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fake_lights_multi_center_weight_24->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Weight for multi-center point 24. Higher values make this center more influential.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_multi_center_color_24->setText(QCoreApplication::translate("cFakeLightsPanel", "Kleur:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_24->setToolTip(QCoreApplication::translate("cFakeLightsPanel", "<html><head/><body><p>Color for multi-center orbit trap point 24</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fake_lights_multi_center_color_24->setProperty("text", QVariant(QCoreApplication::translate("cFakeLightsPanel", "PushButton", nullptr)));
        pushButton_reset_multi_center->setText(QCoreApplication::translate("cFakeLightsPanel", "Reset to Defaults", nullptr));
        groupBox_fake_lights_shape_modifiers->setTitle(QCoreApplication::translate("cFakeLightsPanel", "Shape Modifiers", nullptr));
        label_shape_twist->setText(QCoreApplication::translate("cFakeLightsPanel", "Twist:", nullptr));
        label_shape_bend->setText(QCoreApplication::translate("cFakeLightsPanel", "Bend:", nullptr));
        label_shape_taper->setText(QCoreApplication::translate("cFakeLightsPanel", "Taper:", nullptr));
        label_shape_fold_symmetry->setText(QCoreApplication::translate("cFakeLightsPanel", "Fold symmetry:", nullptr));
        label_shape_repeat_x->setText(QCoreApplication::translate("cFakeLightsPanel", "Repeat X:", nullptr));
        label_shape_repeat_y->setText(QCoreApplication::translate("cFakeLightsPanel", "Repeat Y:", nullptr));
        label_shape_repeat_z->setText(QCoreApplication::translate("cFakeLightsPanel", "Repeat Z:", nullptr));
        label_shape_wobble_amp->setText(QCoreApplication::translate("cFakeLightsPanel", "Wobble amp:", nullptr));
        label_shape_wobble_freq->setText(QCoreApplication::translate("cFakeLightsPanel", "Wobble freq:", nullptr));
        label_shape_chamfer->setText(QCoreApplication::translate("cFakeLightsPanel", "Chamfer:", nullptr));
        label_shape_scale_x->setText(QCoreApplication::translate("cFakeLightsPanel", "Scale X:", nullptr));
        label_shape_scale_y->setText(QCoreApplication::translate("cFakeLightsPanel", "Scale Y:", nullptr));
        label_shape_scale_z->setText(QCoreApplication::translate("cFakeLightsPanel", "Scale Z:", nullptr));
        label_shape_mirror_x->setText(QCoreApplication::translate("cFakeLightsPanel", "Mirror X:", nullptr));
        checkBox_fake_lights_shape_mirror_x->setText(QString());
        label_shape_mirror_y->setText(QCoreApplication::translate("cFakeLightsPanel", "Mirror Y:", nullptr));
        checkBox_fake_lights_shape_mirror_y->setText(QString());
        label_shape_mirror_z->setText(QCoreApplication::translate("cFakeLightsPanel", "Mirror Z:", nullptr));
        checkBox_fake_lights_shape_mirror_z->setText(QString());
        label_shape_inflate->setText(QCoreApplication::translate("cFakeLightsPanel", "Inflate:", nullptr));
        label_shape_line_length->setText(QCoreApplication::translate("cFakeLightsPanel", "Line length:", nullptr));
        label_shape_tube_radius->setText(QCoreApplication::translate("cFakeLightsPanel", "Tube radius:", nullptr));
        label_shape_line_thickness->setText(QCoreApplication::translate("cFakeLightsPanel", "Line thickness:", nullptr));
        label_shape_falloff->setText(QCoreApplication::translate("cFakeLightsPanel", "Falloff:", nullptr));
        label_shape_mask_radius->setText(QCoreApplication::translate("cFakeLightsPanel", "Mask radius:", nullptr));
        label_shape_mask_softness->setText(QCoreApplication::translate("cFakeLightsPanel", "Mask softness:", nullptr));
        label_shape_spiral->setText(QCoreApplication::translate("cFakeLightsPanel", "Spiral:", nullptr));
        label_shape_wave_x->setText(QCoreApplication::translate("cFakeLightsPanel", "Wave X:", nullptr));
        label_shape_wave_y->setText(QCoreApplication::translate("cFakeLightsPanel", "Wave Y:", nullptr));
        label_shape_wave_z->setText(QCoreApplication::translate("cFakeLightsPanel", "Wave Z:", nullptr));
        label_shape_wave_frequency->setText(QCoreApplication::translate("cFakeLightsPanel", "Wave freq:", nullptr));
        groupBox_fake_lights_distance_mask->setTitle(QCoreApplication::translate("cFakeLightsPanel", "Distance Masking", nullptr));
        checkBox_fake_lights_mask_enabled->setText(QCoreApplication::translate("cFakeLightsPanel", "Enabled", nullptr));
        label_mask_threshold->setText(QCoreApplication::translate("cFakeLightsPanel", "Threshold:", nullptr));
        label_mask_sharpness->setText(QCoreApplication::translate("cFakeLightsPanel", "Sharpness:", nullptr));
        (void)cFakeLightsPanel;
    } // retranslateUi

};

namespace Ui {
    class cFakeLightsPanel: public Ui_cFakeLightsPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FAKE_LIGHTS_PANEL_H
