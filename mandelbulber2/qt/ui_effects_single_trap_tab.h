/********************************************************************************
** Form generated from reading UI file 'effects_single_trap_tab.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EFFECTS_SINGLE_TRAP_TAB_H
#define UI_EFFECTS_SINGLE_TRAP_TAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "buton_load_settings_from_widget.h"
#include "buton_save_settings_from_widget.h"
#include "my_check_box.h"
#include "my_color_button.h"
#include "my_combo_box.h"
#include "my_double_spin_box.h"
#include "my_group_box.h"
#include "my_line_edit.h"
#include "my_spin_box.h"

QT_BEGIN_NAMESPACE

class Ui_cEffectsSingleTrapTab
{
public:
    QVBoxLayout *verticalLayout_single_trap_tab;
    QHBoxLayout *horizontalLayout_single_trap_header;
    cButtonLoadSettingsFromWidget *pushButton_single_trap_load;
    cButtonSaveSettingsFromWidget *pushButton_single_trap_save;
    QSpacerItem *horizontalSpacer_single_trap;
    MyGroupBox *groupCheck_single_trap_lights_enabled;
    QVBoxLayout *verticalLayout_single_trap_master;
    QHBoxLayout *horizontalLayout_active_count;
    QLabel *label_single_trap_active_count;
    MySpinBox *spinboxInt_single_trap_lights_active_count;
    QSpacerItem *horizontalSpacer_active_count;
    QLabel *label_single_trap_independent_hint;
    QGroupBox *groupBox_single_trap_tuning;
    QHBoxLayout *horizontalLayout_single_trap_tuning;
    QLabel *label_single_trap_solo_layer;
    MySpinBox *spinboxInt_single_trap_lights_solo_layer;
    QLabel *label_single_trap_combine_mode;
    MyComboBox *comboBox_single_trap_lights_combine_mode;
    QSpacerItem *horizontalSpacer_single_trap_tuning;
    QHBoxLayout *horizontalLayout_single_trap_copy;
    QLabel *label_single_trap_copy_from;
    MySpinBox *spinboxInt_single_trap_copy_from;
    QLabel *label_single_trap_copy_to;
    MySpinBox *spinboxInt_single_trap_copy_to;
    QPushButton *pushButton_single_trap_copy;
    QLabel *label_single_trap_randomize_layer;
    MySpinBox *spinboxInt_single_trap_randomize_layer;
    QPushButton *pushButton_single_trap_randomize;
    QPushButton *pushButton_single_trap_world_anchor;
    QPushButton *pushButton_single_trap_randomize_all;
    QHBoxLayout *horizontalLayout_single_trap_presets;
    QLabel *label_single_trap_preset;
    MyComboBox *comboBox_single_trap_presets;
    QPushButton *pushButton_single_trap_preset_refresh;
    QPushButton *pushButton_single_trap_preset_load;
    QPushButton *pushButton_single_trap_preset_save;
    QPushButton *pushButton_single_trap_reset_all;
    QScrollArea *scrollArea_single_trap_layers;
    QWidget *scrollAreaWidgetContents_single_trap;
    QVBoxLayout *verticalLayout_single_trap_layers;
    MyGroupBox *groupCheck_single_trap_light_1_enabled;
    QGridLayout *gridLayout_single_trap_light_1;
    QLabel *label_single_trap_light_1_shape;
    MyComboBox *comboBox_single_trap_light_1_shape;
    QLabel *label_single_trap_light_1_position;
    MyLineEdit *vect3_single_trap_light_1_position_x;
    MyLineEdit *vect3_single_trap_light_1_position_y;
    MyLineEdit *vect3_single_trap_light_1_position_z;
    QPushButton *pushButton_single_trap_light_1_place_camera;
    QLabel *label_single_trap_light_1_size;
    MyLineEdit *logedit_single_trap_light_1_size;
    QLabel *label_single_trap_light_1_size2;
    MyLineEdit *logedit_single_trap_light_1_size2;
    QLabel *label_single_trap_light_1_thickness;
    MyLineEdit *logedit_single_trap_light_1_thickness;
    QLabel *label_single_trap_light_1_rotation;
    MyDoubleSpinBox *spinboxd3_single_trap_light_1_rotation_x;
    MyDoubleSpinBox *spinboxd3_single_trap_light_1_rotation_y;
    MyDoubleSpinBox *spinboxd3_single_trap_light_1_rotation_z;
    QLabel *label_single_trap_light_1_intensity;
    MyLineEdit *logedit_single_trap_light_1_intensity;
    QLabel *label_single_trap_light_1_color;
    MyColorButton *colorButton_single_trap_light_1_color;
    QLabel *label_single_trap_light_1_gradient_color;
    MyColorButton *colorButton_single_trap_light_1_gradient_color;
    QLabel *label_single_trap_light_1_visibility;
    MyLineEdit *logedit_single_trap_light_1_visibility;
    QLabel *label_single_trap_light_1_max_distance;
    MyLineEdit *logedit_single_trap_light_1_max_distance;
    QLabel *label_single_trap_light_1_sharpening;
    MyLineEdit *logedit_single_trap_light_1_sharpening;
    QLabel *label_single_trap_light_1_blur;
    MyLineEdit *logedit_single_trap_light_1_blur;
    QLabel *label_single_trap_light_1_solid_intensity;
    MyLineEdit *logedit_single_trap_light_1_solid_intensity;
    QLabel *label_single_trap_light_1_softness;
    MyLineEdit *logedit_single_trap_light_1_softness;
    QLabel *label_single_trap_light_1_relative_size;
    MyLineEdit *logedit_single_trap_light_1_relative_size;
    MyCheckBox *checkBox_single_trap_light_1_pre_transformed;
    QLabel *label_single_trap_light_1_position_mode;
    MyComboBox *comboBox_single_trap_light_1_position_mode;
    QLabel *label_single_trap_light_1_coloring_mode;
    MyComboBox *comboBox_single_trap_light_1_coloring_mode;
    QLabel *label_single_trap_light_1_falloff_type;
    MyComboBox *comboBox_single_trap_light_1_falloff_type;
    QLabel *label_single_trap_light_1_edge_softness;
    MyLineEdit *logedit_single_trap_light_1_edge_softness;
    QLabel *label_single_trap_light_1_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_1_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_1_anim_orbit_speed;
    MyLineEdit *logedit_single_trap_light_1_anim_pulsate_speed;
    MyLineEdit *logedit_single_trap_light_1_anim_pulsate_amount;
    QPushButton *pushButton_single_trap_light_1_place_surface;
    QPushButton *pushButton_single_trap_light_1_place_target;
    MyGroupBox *groupCheck_single_trap_light_2_enabled;
    QGridLayout *gridLayout_single_trap_light_2;
    QLabel *label_single_trap_light_2_shape;
    MyComboBox *comboBox_single_trap_light_2_shape;
    QLabel *label_single_trap_light_2_position;
    MyLineEdit *vect3_single_trap_light_2_position_x;
    MyLineEdit *vect3_single_trap_light_2_position_y;
    MyLineEdit *vect3_single_trap_light_2_position_z;
    QPushButton *pushButton_single_trap_light_2_place_camera;
    QLabel *label_single_trap_light_2_size;
    MyLineEdit *logedit_single_trap_light_2_size;
    QLabel *label_single_trap_light_2_size2;
    MyLineEdit *logedit_single_trap_light_2_size2;
    QLabel *label_single_trap_light_2_thickness;
    MyLineEdit *logedit_single_trap_light_2_thickness;
    QLabel *label_single_trap_light_2_rotation;
    MyDoubleSpinBox *spinboxd3_single_trap_light_2_rotation_x;
    MyDoubleSpinBox *spinboxd3_single_trap_light_2_rotation_y;
    MyDoubleSpinBox *spinboxd3_single_trap_light_2_rotation_z;
    QLabel *label_single_trap_light_2_intensity;
    MyLineEdit *logedit_single_trap_light_2_intensity;
    QLabel *label_single_trap_light_2_color;
    MyColorButton *colorButton_single_trap_light_2_color;
    QLabel *label_single_trap_light_2_gradient_color;
    MyColorButton *colorButton_single_trap_light_2_gradient_color;
    QLabel *label_single_trap_light_2_visibility;
    MyLineEdit *logedit_single_trap_light_2_visibility;
    QLabel *label_single_trap_light_2_max_distance;
    MyLineEdit *logedit_single_trap_light_2_max_distance;
    QLabel *label_single_trap_light_2_sharpening;
    MyLineEdit *logedit_single_trap_light_2_sharpening;
    QLabel *label_single_trap_light_2_blur;
    MyLineEdit *logedit_single_trap_light_2_blur;
    QLabel *label_single_trap_light_2_solid_intensity;
    MyLineEdit *logedit_single_trap_light_2_solid_intensity;
    QLabel *label_single_trap_light_2_softness;
    MyLineEdit *logedit_single_trap_light_2_softness;
    QLabel *label_single_trap_light_2_relative_size;
    MyLineEdit *logedit_single_trap_light_2_relative_size;
    MyCheckBox *checkBox_single_trap_light_2_pre_transformed;
    QLabel *label_single_trap_light_2_position_mode;
    MyComboBox *comboBox_single_trap_light_2_position_mode;
    QLabel *label_single_trap_light_2_coloring_mode;
    MyComboBox *comboBox_single_trap_light_2_coloring_mode;
    QLabel *label_single_trap_light_2_falloff_type;
    MyComboBox *comboBox_single_trap_light_2_falloff_type;
    QLabel *label_single_trap_light_2_edge_softness;
    MyLineEdit *logedit_single_trap_light_2_edge_softness;
    QLabel *label_single_trap_light_2_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_2_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_2_anim_orbit_speed;
    MyLineEdit *logedit_single_trap_light_2_anim_pulsate_speed;
    MyLineEdit *logedit_single_trap_light_2_anim_pulsate_amount;
    QPushButton *pushButton_single_trap_light_2_place_surface;
    QPushButton *pushButton_single_trap_light_2_place_target;
    MyGroupBox *groupCheck_single_trap_light_3_enabled;
    QGridLayout *gridLayout_single_trap_light_3;
    QLabel *label_single_trap_light_3_shape;
    MyComboBox *comboBox_single_trap_light_3_shape;
    QLabel *label_single_trap_light_3_position;
    MyLineEdit *vect3_single_trap_light_3_position_x;
    MyLineEdit *vect3_single_trap_light_3_position_y;
    MyLineEdit *vect3_single_trap_light_3_position_z;
    QPushButton *pushButton_single_trap_light_3_place_camera;
    QLabel *label_single_trap_light_3_size;
    MyLineEdit *logedit_single_trap_light_3_size;
    QLabel *label_single_trap_light_3_size2;
    MyLineEdit *logedit_single_trap_light_3_size2;
    QLabel *label_single_trap_light_3_thickness;
    MyLineEdit *logedit_single_trap_light_3_thickness;
    QLabel *label_single_trap_light_3_rotation;
    MyDoubleSpinBox *spinboxd3_single_trap_light_3_rotation_x;
    MyDoubleSpinBox *spinboxd3_single_trap_light_3_rotation_y;
    MyDoubleSpinBox *spinboxd3_single_trap_light_3_rotation_z;
    QLabel *label_single_trap_light_3_intensity;
    MyLineEdit *logedit_single_trap_light_3_intensity;
    QLabel *label_single_trap_light_3_color;
    MyColorButton *colorButton_single_trap_light_3_color;
    QLabel *label_single_trap_light_3_gradient_color;
    MyColorButton *colorButton_single_trap_light_3_gradient_color;
    QLabel *label_single_trap_light_3_visibility;
    MyLineEdit *logedit_single_trap_light_3_visibility;
    QLabel *label_single_trap_light_3_max_distance;
    MyLineEdit *logedit_single_trap_light_3_max_distance;
    QLabel *label_single_trap_light_3_sharpening;
    MyLineEdit *logedit_single_trap_light_3_sharpening;
    QLabel *label_single_trap_light_3_blur;
    MyLineEdit *logedit_single_trap_light_3_blur;
    QLabel *label_single_trap_light_3_solid_intensity;
    MyLineEdit *logedit_single_trap_light_3_solid_intensity;
    QLabel *label_single_trap_light_3_softness;
    MyLineEdit *logedit_single_trap_light_3_softness;
    QLabel *label_single_trap_light_3_relative_size;
    MyLineEdit *logedit_single_trap_light_3_relative_size;
    MyCheckBox *checkBox_single_trap_light_3_pre_transformed;
    QLabel *label_single_trap_light_3_position_mode;
    MyComboBox *comboBox_single_trap_light_3_position_mode;
    QLabel *label_single_trap_light_3_coloring_mode;
    MyComboBox *comboBox_single_trap_light_3_coloring_mode;
    QLabel *label_single_trap_light_3_falloff_type;
    MyComboBox *comboBox_single_trap_light_3_falloff_type;
    QLabel *label_single_trap_light_3_edge_softness;
    MyLineEdit *logedit_single_trap_light_3_edge_softness;
    QLabel *label_single_trap_light_3_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_3_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_3_anim_orbit_speed;
    MyLineEdit *logedit_single_trap_light_3_anim_pulsate_speed;
    MyLineEdit *logedit_single_trap_light_3_anim_pulsate_amount;
    QPushButton *pushButton_single_trap_light_3_place_surface;
    QPushButton *pushButton_single_trap_light_3_place_target;
    MyGroupBox *groupCheck_single_trap_light_4_enabled;
    QGridLayout *gridLayout_single_trap_light_4;
    QLabel *label_single_trap_light_4_shape;
    MyComboBox *comboBox_single_trap_light_4_shape;
    QLabel *label_single_trap_light_4_position;
    MyLineEdit *vect3_single_trap_light_4_position_x;
    MyLineEdit *vect3_single_trap_light_4_position_y;
    MyLineEdit *vect3_single_trap_light_4_position_z;
    QPushButton *pushButton_single_trap_light_4_place_camera;
    QLabel *label_single_trap_light_4_size;
    MyLineEdit *logedit_single_trap_light_4_size;
    QLabel *label_single_trap_light_4_size2;
    MyLineEdit *logedit_single_trap_light_4_size2;
    QLabel *label_single_trap_light_4_thickness;
    MyLineEdit *logedit_single_trap_light_4_thickness;
    QLabel *label_single_trap_light_4_rotation;
    MyDoubleSpinBox *spinboxd3_single_trap_light_4_rotation_x;
    MyDoubleSpinBox *spinboxd3_single_trap_light_4_rotation_y;
    MyDoubleSpinBox *spinboxd3_single_trap_light_4_rotation_z;
    QLabel *label_single_trap_light_4_intensity;
    MyLineEdit *logedit_single_trap_light_4_intensity;
    QLabel *label_single_trap_light_4_color;
    MyColorButton *colorButton_single_trap_light_4_color;
    QLabel *label_single_trap_light_4_gradient_color;
    MyColorButton *colorButton_single_trap_light_4_gradient_color;
    QLabel *label_single_trap_light_4_visibility;
    MyLineEdit *logedit_single_trap_light_4_visibility;
    QLabel *label_single_trap_light_4_max_distance;
    MyLineEdit *logedit_single_trap_light_4_max_distance;
    QLabel *label_single_trap_light_4_sharpening;
    MyLineEdit *logedit_single_trap_light_4_sharpening;
    QLabel *label_single_trap_light_4_blur;
    MyLineEdit *logedit_single_trap_light_4_blur;
    QLabel *label_single_trap_light_4_solid_intensity;
    MyLineEdit *logedit_single_trap_light_4_solid_intensity;
    QLabel *label_single_trap_light_4_softness;
    MyLineEdit *logedit_single_trap_light_4_softness;
    QLabel *label_single_trap_light_4_relative_size;
    MyLineEdit *logedit_single_trap_light_4_relative_size;
    MyCheckBox *checkBox_single_trap_light_4_pre_transformed;
    QLabel *label_single_trap_light_4_position_mode;
    MyComboBox *comboBox_single_trap_light_4_position_mode;
    QLabel *label_single_trap_light_4_coloring_mode;
    MyComboBox *comboBox_single_trap_light_4_coloring_mode;
    QLabel *label_single_trap_light_4_falloff_type;
    MyComboBox *comboBox_single_trap_light_4_falloff_type;
    QLabel *label_single_trap_light_4_edge_softness;
    MyLineEdit *logedit_single_trap_light_4_edge_softness;
    QLabel *label_single_trap_light_4_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_4_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_4_anim_orbit_speed;
    MyLineEdit *logedit_single_trap_light_4_anim_pulsate_speed;
    MyLineEdit *logedit_single_trap_light_4_anim_pulsate_amount;
    QPushButton *pushButton_single_trap_light_4_place_surface;
    QPushButton *pushButton_single_trap_light_4_place_target;
    MyGroupBox *groupCheck_single_trap_light_5_enabled;
    QGridLayout *gridLayout_single_trap_light_5;
    QLabel *label_single_trap_light_5_shape;
    MyComboBox *comboBox_single_trap_light_5_shape;
    QLabel *label_single_trap_light_5_position;
    MyLineEdit *vect3_single_trap_light_5_position_x;
    MyLineEdit *vect3_single_trap_light_5_position_y;
    MyLineEdit *vect3_single_trap_light_5_position_z;
    QPushButton *pushButton_single_trap_light_5_place_camera;
    QLabel *label_single_trap_light_5_size;
    MyLineEdit *logedit_single_trap_light_5_size;
    QLabel *label_single_trap_light_5_size2;
    MyLineEdit *logedit_single_trap_light_5_size2;
    QLabel *label_single_trap_light_5_thickness;
    MyLineEdit *logedit_single_trap_light_5_thickness;
    QLabel *label_single_trap_light_5_rotation;
    MyDoubleSpinBox *spinboxd3_single_trap_light_5_rotation_x;
    MyDoubleSpinBox *spinboxd3_single_trap_light_5_rotation_y;
    MyDoubleSpinBox *spinboxd3_single_trap_light_5_rotation_z;
    QLabel *label_single_trap_light_5_intensity;
    MyLineEdit *logedit_single_trap_light_5_intensity;
    QLabel *label_single_trap_light_5_color;
    MyColorButton *colorButton_single_trap_light_5_color;
    QLabel *label_single_trap_light_5_gradient_color;
    MyColorButton *colorButton_single_trap_light_5_gradient_color;
    QLabel *label_single_trap_light_5_visibility;
    MyLineEdit *logedit_single_trap_light_5_visibility;
    QLabel *label_single_trap_light_5_max_distance;
    MyLineEdit *logedit_single_trap_light_5_max_distance;
    QLabel *label_single_trap_light_5_sharpening;
    MyLineEdit *logedit_single_trap_light_5_sharpening;
    QLabel *label_single_trap_light_5_blur;
    MyLineEdit *logedit_single_trap_light_5_blur;
    QLabel *label_single_trap_light_5_solid_intensity;
    MyLineEdit *logedit_single_trap_light_5_solid_intensity;
    QLabel *label_single_trap_light_5_softness;
    MyLineEdit *logedit_single_trap_light_5_softness;
    QLabel *label_single_trap_light_5_relative_size;
    MyLineEdit *logedit_single_trap_light_5_relative_size;
    MyCheckBox *checkBox_single_trap_light_5_pre_transformed;
    QLabel *label_single_trap_light_5_position_mode;
    MyComboBox *comboBox_single_trap_light_5_position_mode;
    QLabel *label_single_trap_light_5_coloring_mode;
    MyComboBox *comboBox_single_trap_light_5_coloring_mode;
    QLabel *label_single_trap_light_5_falloff_type;
    MyComboBox *comboBox_single_trap_light_5_falloff_type;
    QLabel *label_single_trap_light_5_edge_softness;
    MyLineEdit *logedit_single_trap_light_5_edge_softness;
    QLabel *label_single_trap_light_5_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_5_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_5_anim_orbit_speed;
    MyLineEdit *logedit_single_trap_light_5_anim_pulsate_speed;
    MyLineEdit *logedit_single_trap_light_5_anim_pulsate_amount;
    QPushButton *pushButton_single_trap_light_5_place_surface;
    QPushButton *pushButton_single_trap_light_5_place_target;
    MyGroupBox *groupCheck_single_trap_light_6_enabled;
    QGridLayout *gridLayout_single_trap_light_6;
    QLabel *label_single_trap_light_6_shape;
    MyComboBox *comboBox_single_trap_light_6_shape;
    QLabel *label_single_trap_light_6_position;
    MyLineEdit *vect3_single_trap_light_6_position_x;
    MyLineEdit *vect3_single_trap_light_6_position_y;
    MyLineEdit *vect3_single_trap_light_6_position_z;
    QPushButton *pushButton_single_trap_light_6_place_camera;
    QLabel *label_single_trap_light_6_size;
    MyLineEdit *logedit_single_trap_light_6_size;
    QLabel *label_single_trap_light_6_size2;
    MyLineEdit *logedit_single_trap_light_6_size2;
    QLabel *label_single_trap_light_6_thickness;
    MyLineEdit *logedit_single_trap_light_6_thickness;
    QLabel *label_single_trap_light_6_rotation;
    MyDoubleSpinBox *spinboxd3_single_trap_light_6_rotation_x;
    MyDoubleSpinBox *spinboxd3_single_trap_light_6_rotation_y;
    MyDoubleSpinBox *spinboxd3_single_trap_light_6_rotation_z;
    QLabel *label_single_trap_light_6_intensity;
    MyLineEdit *logedit_single_trap_light_6_intensity;
    QLabel *label_single_trap_light_6_color;
    MyColorButton *colorButton_single_trap_light_6_color;
    QLabel *label_single_trap_light_6_gradient_color;
    MyColorButton *colorButton_single_trap_light_6_gradient_color;
    QLabel *label_single_trap_light_6_visibility;
    MyLineEdit *logedit_single_trap_light_6_visibility;
    QLabel *label_single_trap_light_6_max_distance;
    MyLineEdit *logedit_single_trap_light_6_max_distance;
    QLabel *label_single_trap_light_6_sharpening;
    MyLineEdit *logedit_single_trap_light_6_sharpening;
    QLabel *label_single_trap_light_6_blur;
    MyLineEdit *logedit_single_trap_light_6_blur;
    QLabel *label_single_trap_light_6_solid_intensity;
    MyLineEdit *logedit_single_trap_light_6_solid_intensity;
    QLabel *label_single_trap_light_6_softness;
    MyLineEdit *logedit_single_trap_light_6_softness;
    QLabel *label_single_trap_light_6_relative_size;
    MyLineEdit *logedit_single_trap_light_6_relative_size;
    MyCheckBox *checkBox_single_trap_light_6_pre_transformed;
    QLabel *label_single_trap_light_6_position_mode;
    MyComboBox *comboBox_single_trap_light_6_position_mode;
    QLabel *label_single_trap_light_6_coloring_mode;
    MyComboBox *comboBox_single_trap_light_6_coloring_mode;
    QLabel *label_single_trap_light_6_falloff_type;
    MyComboBox *comboBox_single_trap_light_6_falloff_type;
    QLabel *label_single_trap_light_6_edge_softness;
    MyLineEdit *logedit_single_trap_light_6_edge_softness;
    QLabel *label_single_trap_light_6_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_6_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_6_anim_orbit_speed;
    MyLineEdit *logedit_single_trap_light_6_anim_pulsate_speed;
    MyLineEdit *logedit_single_trap_light_6_anim_pulsate_amount;
    QPushButton *pushButton_single_trap_light_6_place_surface;
    QPushButton *pushButton_single_trap_light_6_place_target;
    MyGroupBox *groupCheck_single_trap_light_7_enabled;
    QGridLayout *gridLayout_single_trap_light_7;
    QLabel *label_single_trap_light_7_shape;
    MyComboBox *comboBox_single_trap_light_7_shape;
    QLabel *label_single_trap_light_7_position;
    MyLineEdit *vect3_single_trap_light_7_position_x;
    MyLineEdit *vect3_single_trap_light_7_position_y;
    MyLineEdit *vect3_single_trap_light_7_position_z;
    QPushButton *pushButton_single_trap_light_7_place_camera;
    QLabel *label_single_trap_light_7_size;
    MyLineEdit *logedit_single_trap_light_7_size;
    QLabel *label_single_trap_light_7_size2;
    MyLineEdit *logedit_single_trap_light_7_size2;
    QLabel *label_single_trap_light_7_thickness;
    MyLineEdit *logedit_single_trap_light_7_thickness;
    QLabel *label_single_trap_light_7_rotation;
    MyDoubleSpinBox *spinboxd3_single_trap_light_7_rotation_x;
    MyDoubleSpinBox *spinboxd3_single_trap_light_7_rotation_y;
    MyDoubleSpinBox *spinboxd3_single_trap_light_7_rotation_z;
    QLabel *label_single_trap_light_7_intensity;
    MyLineEdit *logedit_single_trap_light_7_intensity;
    QLabel *label_single_trap_light_7_color;
    MyColorButton *colorButton_single_trap_light_7_color;
    QLabel *label_single_trap_light_7_gradient_color;
    MyColorButton *colorButton_single_trap_light_7_gradient_color;
    QLabel *label_single_trap_light_7_visibility;
    MyLineEdit *logedit_single_trap_light_7_visibility;
    QLabel *label_single_trap_light_7_max_distance;
    MyLineEdit *logedit_single_trap_light_7_max_distance;
    QLabel *label_single_trap_light_7_sharpening;
    MyLineEdit *logedit_single_trap_light_7_sharpening;
    QLabel *label_single_trap_light_7_blur;
    MyLineEdit *logedit_single_trap_light_7_blur;
    QLabel *label_single_trap_light_7_solid_intensity;
    MyLineEdit *logedit_single_trap_light_7_solid_intensity;
    QLabel *label_single_trap_light_7_softness;
    MyLineEdit *logedit_single_trap_light_7_softness;
    QLabel *label_single_trap_light_7_relative_size;
    MyLineEdit *logedit_single_trap_light_7_relative_size;
    MyCheckBox *checkBox_single_trap_light_7_pre_transformed;
    QLabel *label_single_trap_light_7_position_mode;
    MyComboBox *comboBox_single_trap_light_7_position_mode;
    QLabel *label_single_trap_light_7_coloring_mode;
    MyComboBox *comboBox_single_trap_light_7_coloring_mode;
    QLabel *label_single_trap_light_7_falloff_type;
    MyComboBox *comboBox_single_trap_light_7_falloff_type;
    QLabel *label_single_trap_light_7_edge_softness;
    MyLineEdit *logedit_single_trap_light_7_edge_softness;
    QLabel *label_single_trap_light_7_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_7_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_7_anim_orbit_speed;
    MyLineEdit *logedit_single_trap_light_7_anim_pulsate_speed;
    MyLineEdit *logedit_single_trap_light_7_anim_pulsate_amount;
    QPushButton *pushButton_single_trap_light_7_place_surface;
    QPushButton *pushButton_single_trap_light_7_place_target;
    MyGroupBox *groupCheck_single_trap_light_8_enabled;
    QGridLayout *gridLayout_single_trap_light_8;
    QLabel *label_single_trap_light_8_shape;
    MyComboBox *comboBox_single_trap_light_8_shape;
    QLabel *label_single_trap_light_8_position;
    MyLineEdit *vect3_single_trap_light_8_position_x;
    MyLineEdit *vect3_single_trap_light_8_position_y;
    MyLineEdit *vect3_single_trap_light_8_position_z;
    QPushButton *pushButton_single_trap_light_8_place_camera;
    QLabel *label_single_trap_light_8_size;
    MyLineEdit *logedit_single_trap_light_8_size;
    QLabel *label_single_trap_light_8_size2;
    MyLineEdit *logedit_single_trap_light_8_size2;
    QLabel *label_single_trap_light_8_thickness;
    MyLineEdit *logedit_single_trap_light_8_thickness;
    QLabel *label_single_trap_light_8_rotation;
    MyDoubleSpinBox *spinboxd3_single_trap_light_8_rotation_x;
    MyDoubleSpinBox *spinboxd3_single_trap_light_8_rotation_y;
    MyDoubleSpinBox *spinboxd3_single_trap_light_8_rotation_z;
    QLabel *label_single_trap_light_8_intensity;
    MyLineEdit *logedit_single_trap_light_8_intensity;
    QLabel *label_single_trap_light_8_color;
    MyColorButton *colorButton_single_trap_light_8_color;
    QLabel *label_single_trap_light_8_gradient_color;
    MyColorButton *colorButton_single_trap_light_8_gradient_color;
    QLabel *label_single_trap_light_8_visibility;
    MyLineEdit *logedit_single_trap_light_8_visibility;
    QLabel *label_single_trap_light_8_max_distance;
    MyLineEdit *logedit_single_trap_light_8_max_distance;
    QLabel *label_single_trap_light_8_sharpening;
    MyLineEdit *logedit_single_trap_light_8_sharpening;
    QLabel *label_single_trap_light_8_blur;
    MyLineEdit *logedit_single_trap_light_8_blur;
    QLabel *label_single_trap_light_8_solid_intensity;
    MyLineEdit *logedit_single_trap_light_8_solid_intensity;
    QLabel *label_single_trap_light_8_softness;
    MyLineEdit *logedit_single_trap_light_8_softness;
    QLabel *label_single_trap_light_8_relative_size;
    MyLineEdit *logedit_single_trap_light_8_relative_size;
    MyCheckBox *checkBox_single_trap_light_8_pre_transformed;
    QLabel *label_single_trap_light_8_position_mode;
    MyComboBox *comboBox_single_trap_light_8_position_mode;
    QLabel *label_single_trap_light_8_coloring_mode;
    MyComboBox *comboBox_single_trap_light_8_coloring_mode;
    QLabel *label_single_trap_light_8_falloff_type;
    MyComboBox *comboBox_single_trap_light_8_falloff_type;
    QLabel *label_single_trap_light_8_edge_softness;
    MyLineEdit *logedit_single_trap_light_8_edge_softness;
    QLabel *label_single_trap_light_8_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_8_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_8_anim_orbit_speed;
    MyLineEdit *logedit_single_trap_light_8_anim_pulsate_speed;
    MyLineEdit *logedit_single_trap_light_8_anim_pulsate_amount;
    QPushButton *pushButton_single_trap_light_8_place_surface;
    QPushButton *pushButton_single_trap_light_8_place_target;
    MyGroupBox *groupCheck_single_trap_light_9_enabled;
    QGridLayout *gridLayout_single_trap_light_9;
    QLabel *label_single_trap_light_9_shape;
    MyComboBox *comboBox_single_trap_light_9_shape;
    QLabel *label_single_trap_light_9_position;
    MyLineEdit *vect3_single_trap_light_9_position_x;
    MyLineEdit *vect3_single_trap_light_9_position_y;
    MyLineEdit *vect3_single_trap_light_9_position_z;
    QPushButton *pushButton_single_trap_light_9_place_camera;
    QLabel *label_single_trap_light_9_size;
    MyLineEdit *logedit_single_trap_light_9_size;
    QLabel *label_single_trap_light_9_size2;
    MyLineEdit *logedit_single_trap_light_9_size2;
    QLabel *label_single_trap_light_9_thickness;
    MyLineEdit *logedit_single_trap_light_9_thickness;
    QLabel *label_single_trap_light_9_rotation;
    MyDoubleSpinBox *spinboxd3_single_trap_light_9_rotation_x;
    MyDoubleSpinBox *spinboxd3_single_trap_light_9_rotation_y;
    MyDoubleSpinBox *spinboxd3_single_trap_light_9_rotation_z;
    QLabel *label_single_trap_light_9_intensity;
    MyLineEdit *logedit_single_trap_light_9_intensity;
    QLabel *label_single_trap_light_9_color;
    MyColorButton *colorButton_single_trap_light_9_color;
    QLabel *label_single_trap_light_9_gradient_color;
    MyColorButton *colorButton_single_trap_light_9_gradient_color;
    QLabel *label_single_trap_light_9_visibility;
    MyLineEdit *logedit_single_trap_light_9_visibility;
    QLabel *label_single_trap_light_9_max_distance;
    MyLineEdit *logedit_single_trap_light_9_max_distance;
    QLabel *label_single_trap_light_9_sharpening;
    MyLineEdit *logedit_single_trap_light_9_sharpening;
    QLabel *label_single_trap_light_9_blur;
    MyLineEdit *logedit_single_trap_light_9_blur;
    QLabel *label_single_trap_light_9_solid_intensity;
    MyLineEdit *logedit_single_trap_light_9_solid_intensity;
    QLabel *label_single_trap_light_9_softness;
    MyLineEdit *logedit_single_trap_light_9_softness;
    QLabel *label_single_trap_light_9_relative_size;
    MyLineEdit *logedit_single_trap_light_9_relative_size;
    MyCheckBox *checkBox_single_trap_light_9_pre_transformed;
    QLabel *label_single_trap_light_9_position_mode;
    MyComboBox *comboBox_single_trap_light_9_position_mode;
    QLabel *label_single_trap_light_9_coloring_mode;
    MyComboBox *comboBox_single_trap_light_9_coloring_mode;
    QLabel *label_single_trap_light_9_falloff_type;
    MyComboBox *comboBox_single_trap_light_9_falloff_type;
    QLabel *label_single_trap_light_9_edge_softness;
    MyLineEdit *logedit_single_trap_light_9_edge_softness;
    QLabel *label_single_trap_light_9_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_9_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_9_anim_orbit_speed;
    MyLineEdit *logedit_single_trap_light_9_anim_pulsate_speed;
    MyLineEdit *logedit_single_trap_light_9_anim_pulsate_amount;
    QPushButton *pushButton_single_trap_light_9_place_surface;
    QPushButton *pushButton_single_trap_light_9_place_target;
    MyGroupBox *groupCheck_single_trap_light_10_enabled;
    QGridLayout *gridLayout_single_trap_light_10;
    QLabel *label_single_trap_light_10_shape;
    MyComboBox *comboBox_single_trap_light_10_shape;
    QLabel *label_single_trap_light_10_position;
    MyLineEdit *vect3_single_trap_light_10_position_x;
    MyLineEdit *vect3_single_trap_light_10_position_y;
    MyLineEdit *vect3_single_trap_light_10_position_z;
    QPushButton *pushButton_single_trap_light_10_place_camera;
    QLabel *label_single_trap_light_10_size;
    MyLineEdit *logedit_single_trap_light_10_size;
    QLabel *label_single_trap_light_10_size2;
    MyLineEdit *logedit_single_trap_light_10_size2;
    QLabel *label_single_trap_light_10_thickness;
    MyLineEdit *logedit_single_trap_light_10_thickness;
    QLabel *label_single_trap_light_10_rotation;
    MyDoubleSpinBox *spinboxd3_single_trap_light_10_rotation_x;
    MyDoubleSpinBox *spinboxd3_single_trap_light_10_rotation_y;
    MyDoubleSpinBox *spinboxd3_single_trap_light_10_rotation_z;
    QLabel *label_single_trap_light_10_intensity;
    MyLineEdit *logedit_single_trap_light_10_intensity;
    QLabel *label_single_trap_light_10_color;
    MyColorButton *colorButton_single_trap_light_10_color;
    QLabel *label_single_trap_light_10_gradient_color;
    MyColorButton *colorButton_single_trap_light_10_gradient_color;
    QLabel *label_single_trap_light_10_visibility;
    MyLineEdit *logedit_single_trap_light_10_visibility;
    QLabel *label_single_trap_light_10_max_distance;
    MyLineEdit *logedit_single_trap_light_10_max_distance;
    QLabel *label_single_trap_light_10_sharpening;
    MyLineEdit *logedit_single_trap_light_10_sharpening;
    QLabel *label_single_trap_light_10_blur;
    MyLineEdit *logedit_single_trap_light_10_blur;
    QLabel *label_single_trap_light_10_solid_intensity;
    MyLineEdit *logedit_single_trap_light_10_solid_intensity;
    QLabel *label_single_trap_light_10_softness;
    MyLineEdit *logedit_single_trap_light_10_softness;
    QLabel *label_single_trap_light_10_relative_size;
    MyLineEdit *logedit_single_trap_light_10_relative_size;
    MyCheckBox *checkBox_single_trap_light_10_pre_transformed;
    QLabel *label_single_trap_light_10_position_mode;
    MyComboBox *comboBox_single_trap_light_10_position_mode;
    QLabel *label_single_trap_light_10_coloring_mode;
    MyComboBox *comboBox_single_trap_light_10_coloring_mode;
    QLabel *label_single_trap_light_10_falloff_type;
    MyComboBox *comboBox_single_trap_light_10_falloff_type;
    QLabel *label_single_trap_light_10_edge_softness;
    MyLineEdit *logedit_single_trap_light_10_edge_softness;
    QLabel *label_single_trap_light_10_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_10_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_10_anim_orbit_speed;
    MyLineEdit *logedit_single_trap_light_10_anim_pulsate_speed;
    MyLineEdit *logedit_single_trap_light_10_anim_pulsate_amount;
    QPushButton *pushButton_single_trap_light_10_place_surface;
    QPushButton *pushButton_single_trap_light_10_place_target;
    MyGroupBox *groupCheck_single_trap_light_11_enabled;
    QGridLayout *gridLayout_single_trap_light_11;
    QLabel *label_single_trap_light_11_shape;
    MyComboBox *comboBox_single_trap_light_11_shape;
    QLabel *label_single_trap_light_11_position;
    MyLineEdit *vect3_single_trap_light_11_position_x;
    MyLineEdit *vect3_single_trap_light_11_position_y;
    MyLineEdit *vect3_single_trap_light_11_position_z;
    QPushButton *pushButton_single_trap_light_11_place_camera;
    QLabel *label_single_trap_light_11_size;
    MyLineEdit *logedit_single_trap_light_11_size;
    QLabel *label_single_trap_light_11_size2;
    MyLineEdit *logedit_single_trap_light_11_size2;
    QLabel *label_single_trap_light_11_thickness;
    MyLineEdit *logedit_single_trap_light_11_thickness;
    QLabel *label_single_trap_light_11_rotation;
    MyDoubleSpinBox *spinboxd3_single_trap_light_11_rotation_x;
    MyDoubleSpinBox *spinboxd3_single_trap_light_11_rotation_y;
    MyDoubleSpinBox *spinboxd3_single_trap_light_11_rotation_z;
    QLabel *label_single_trap_light_11_intensity;
    MyLineEdit *logedit_single_trap_light_11_intensity;
    QLabel *label_single_trap_light_11_color;
    MyColorButton *colorButton_single_trap_light_11_color;
    QLabel *label_single_trap_light_11_gradient_color;
    MyColorButton *colorButton_single_trap_light_11_gradient_color;
    QLabel *label_single_trap_light_11_visibility;
    MyLineEdit *logedit_single_trap_light_11_visibility;
    QLabel *label_single_trap_light_11_max_distance;
    MyLineEdit *logedit_single_trap_light_11_max_distance;
    QLabel *label_single_trap_light_11_sharpening;
    MyLineEdit *logedit_single_trap_light_11_sharpening;
    QLabel *label_single_trap_light_11_blur;
    MyLineEdit *logedit_single_trap_light_11_blur;
    QLabel *label_single_trap_light_11_solid_intensity;
    MyLineEdit *logedit_single_trap_light_11_solid_intensity;
    QLabel *label_single_trap_light_11_softness;
    MyLineEdit *logedit_single_trap_light_11_softness;
    QLabel *label_single_trap_light_11_relative_size;
    MyLineEdit *logedit_single_trap_light_11_relative_size;
    MyCheckBox *checkBox_single_trap_light_11_pre_transformed;
    QLabel *label_single_trap_light_11_position_mode;
    MyComboBox *comboBox_single_trap_light_11_position_mode;
    QLabel *label_single_trap_light_11_coloring_mode;
    MyComboBox *comboBox_single_trap_light_11_coloring_mode;
    QLabel *label_single_trap_light_11_falloff_type;
    MyComboBox *comboBox_single_trap_light_11_falloff_type;
    QLabel *label_single_trap_light_11_edge_softness;
    MyLineEdit *logedit_single_trap_light_11_edge_softness;
    QLabel *label_single_trap_light_11_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_11_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_11_anim_orbit_speed;
    MyLineEdit *logedit_single_trap_light_11_anim_pulsate_speed;
    MyLineEdit *logedit_single_trap_light_11_anim_pulsate_amount;
    QPushButton *pushButton_single_trap_light_11_place_surface;
    QPushButton *pushButton_single_trap_light_11_place_target;
    MyGroupBox *groupCheck_single_trap_light_12_enabled;
    QGridLayout *gridLayout_single_trap_light_12;
    QLabel *label_single_trap_light_12_shape;
    MyComboBox *comboBox_single_trap_light_12_shape;
    QLabel *label_single_trap_light_12_position;
    MyLineEdit *vect3_single_trap_light_12_position_x;
    MyLineEdit *vect3_single_trap_light_12_position_y;
    MyLineEdit *vect3_single_trap_light_12_position_z;
    QPushButton *pushButton_single_trap_light_12_place_camera;
    QLabel *label_single_trap_light_12_size;
    MyLineEdit *logedit_single_trap_light_12_size;
    QLabel *label_single_trap_light_12_size2;
    MyLineEdit *logedit_single_trap_light_12_size2;
    QLabel *label_single_trap_light_12_thickness;
    MyLineEdit *logedit_single_trap_light_12_thickness;
    QLabel *label_single_trap_light_12_rotation;
    MyDoubleSpinBox *spinboxd3_single_trap_light_12_rotation_x;
    MyDoubleSpinBox *spinboxd3_single_trap_light_12_rotation_y;
    MyDoubleSpinBox *spinboxd3_single_trap_light_12_rotation_z;
    QLabel *label_single_trap_light_12_intensity;
    MyLineEdit *logedit_single_trap_light_12_intensity;
    QLabel *label_single_trap_light_12_color;
    MyColorButton *colorButton_single_trap_light_12_color;
    QLabel *label_single_trap_light_12_gradient_color;
    MyColorButton *colorButton_single_trap_light_12_gradient_color;
    QLabel *label_single_trap_light_12_visibility;
    MyLineEdit *logedit_single_trap_light_12_visibility;
    QLabel *label_single_trap_light_12_max_distance;
    MyLineEdit *logedit_single_trap_light_12_max_distance;
    QLabel *label_single_trap_light_12_sharpening;
    MyLineEdit *logedit_single_trap_light_12_sharpening;
    QLabel *label_single_trap_light_12_blur;
    MyLineEdit *logedit_single_trap_light_12_blur;
    QLabel *label_single_trap_light_12_solid_intensity;
    MyLineEdit *logedit_single_trap_light_12_solid_intensity;
    QLabel *label_single_trap_light_12_softness;
    MyLineEdit *logedit_single_trap_light_12_softness;
    QLabel *label_single_trap_light_12_relative_size;
    MyLineEdit *logedit_single_trap_light_12_relative_size;
    MyCheckBox *checkBox_single_trap_light_12_pre_transformed;
    QLabel *label_single_trap_light_12_position_mode;
    MyComboBox *comboBox_single_trap_light_12_position_mode;
    QLabel *label_single_trap_light_12_coloring_mode;
    MyComboBox *comboBox_single_trap_light_12_coloring_mode;
    QLabel *label_single_trap_light_12_falloff_type;
    MyComboBox *comboBox_single_trap_light_12_falloff_type;
    QLabel *label_single_trap_light_12_edge_softness;
    MyLineEdit *logedit_single_trap_light_12_edge_softness;
    QLabel *label_single_trap_light_12_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_12_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_12_anim_orbit_speed;
    MyLineEdit *logedit_single_trap_light_12_anim_pulsate_speed;
    MyLineEdit *logedit_single_trap_light_12_anim_pulsate_amount;
    QPushButton *pushButton_single_trap_light_12_place_surface;
    QPushButton *pushButton_single_trap_light_12_place_target;
    MyGroupBox *groupCheck_single_trap_light_13_enabled;
    QGridLayout *gridLayout_single_trap_light_13;
    QLabel *label_single_trap_light_13_shape;
    MyComboBox *comboBox_single_trap_light_13_shape;
    QLabel *label_single_trap_light_13_position;
    MyLineEdit *vect3_single_trap_light_13_position_x;
    MyLineEdit *vect3_single_trap_light_13_position_y;
    MyLineEdit *vect3_single_trap_light_13_position_z;
    QPushButton *pushButton_single_trap_light_13_place_camera;
    QLabel *label_single_trap_light_13_size;
    MyLineEdit *logedit_single_trap_light_13_size;
    QLabel *label_single_trap_light_13_size2;
    MyLineEdit *logedit_single_trap_light_13_size2;
    QLabel *label_single_trap_light_13_thickness;
    MyLineEdit *logedit_single_trap_light_13_thickness;
    QLabel *label_single_trap_light_13_rotation;
    MyDoubleSpinBox *spinboxd3_single_trap_light_13_rotation_x;
    MyDoubleSpinBox *spinboxd3_single_trap_light_13_rotation_y;
    MyDoubleSpinBox *spinboxd3_single_trap_light_13_rotation_z;
    QLabel *label_single_trap_light_13_intensity;
    MyLineEdit *logedit_single_trap_light_13_intensity;
    QLabel *label_single_trap_light_13_color;
    MyColorButton *colorButton_single_trap_light_13_color;
    QLabel *label_single_trap_light_13_gradient_color;
    MyColorButton *colorButton_single_trap_light_13_gradient_color;
    QLabel *label_single_trap_light_13_visibility;
    MyLineEdit *logedit_single_trap_light_13_visibility;
    QLabel *label_single_trap_light_13_max_distance;
    MyLineEdit *logedit_single_trap_light_13_max_distance;
    QLabel *label_single_trap_light_13_sharpening;
    MyLineEdit *logedit_single_trap_light_13_sharpening;
    QLabel *label_single_trap_light_13_blur;
    MyLineEdit *logedit_single_trap_light_13_blur;
    QLabel *label_single_trap_light_13_solid_intensity;
    MyLineEdit *logedit_single_trap_light_13_solid_intensity;
    QLabel *label_single_trap_light_13_softness;
    MyLineEdit *logedit_single_trap_light_13_softness;
    QLabel *label_single_trap_light_13_relative_size;
    MyLineEdit *logedit_single_trap_light_13_relative_size;
    MyCheckBox *checkBox_single_trap_light_13_pre_transformed;
    QLabel *label_single_trap_light_13_position_mode;
    MyComboBox *comboBox_single_trap_light_13_position_mode;
    QLabel *label_single_trap_light_13_coloring_mode;
    MyComboBox *comboBox_single_trap_light_13_coloring_mode;
    QLabel *label_single_trap_light_13_falloff_type;
    MyComboBox *comboBox_single_trap_light_13_falloff_type;
    QLabel *label_single_trap_light_13_edge_softness;
    MyLineEdit *logedit_single_trap_light_13_edge_softness;
    QLabel *label_single_trap_light_13_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_13_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_13_anim_orbit_speed;
    MyLineEdit *logedit_single_trap_light_13_anim_pulsate_speed;
    MyLineEdit *logedit_single_trap_light_13_anim_pulsate_amount;
    QPushButton *pushButton_single_trap_light_13_place_surface;
    QPushButton *pushButton_single_trap_light_13_place_target;
    MyGroupBox *groupCheck_single_trap_light_14_enabled;
    QGridLayout *gridLayout_single_trap_light_14;
    QLabel *label_single_trap_light_14_shape;
    MyComboBox *comboBox_single_trap_light_14_shape;
    QLabel *label_single_trap_light_14_position;
    MyLineEdit *vect3_single_trap_light_14_position_x;
    MyLineEdit *vect3_single_trap_light_14_position_y;
    MyLineEdit *vect3_single_trap_light_14_position_z;
    QPushButton *pushButton_single_trap_light_14_place_camera;
    QLabel *label_single_trap_light_14_size;
    MyLineEdit *logedit_single_trap_light_14_size;
    QLabel *label_single_trap_light_14_size2;
    MyLineEdit *logedit_single_trap_light_14_size2;
    QLabel *label_single_trap_light_14_thickness;
    MyLineEdit *logedit_single_trap_light_14_thickness;
    QLabel *label_single_trap_light_14_rotation;
    MyDoubleSpinBox *spinboxd3_single_trap_light_14_rotation_x;
    MyDoubleSpinBox *spinboxd3_single_trap_light_14_rotation_y;
    MyDoubleSpinBox *spinboxd3_single_trap_light_14_rotation_z;
    QLabel *label_single_trap_light_14_intensity;
    MyLineEdit *logedit_single_trap_light_14_intensity;
    QLabel *label_single_trap_light_14_color;
    MyColorButton *colorButton_single_trap_light_14_color;
    QLabel *label_single_trap_light_14_gradient_color;
    MyColorButton *colorButton_single_trap_light_14_gradient_color;
    QLabel *label_single_trap_light_14_visibility;
    MyLineEdit *logedit_single_trap_light_14_visibility;
    QLabel *label_single_trap_light_14_max_distance;
    MyLineEdit *logedit_single_trap_light_14_max_distance;
    QLabel *label_single_trap_light_14_sharpening;
    MyLineEdit *logedit_single_trap_light_14_sharpening;
    QLabel *label_single_trap_light_14_blur;
    MyLineEdit *logedit_single_trap_light_14_blur;
    QLabel *label_single_trap_light_14_solid_intensity;
    MyLineEdit *logedit_single_trap_light_14_solid_intensity;
    QLabel *label_single_trap_light_14_softness;
    MyLineEdit *logedit_single_trap_light_14_softness;
    QLabel *label_single_trap_light_14_relative_size;
    MyLineEdit *logedit_single_trap_light_14_relative_size;
    MyCheckBox *checkBox_single_trap_light_14_pre_transformed;
    QLabel *label_single_trap_light_14_position_mode;
    MyComboBox *comboBox_single_trap_light_14_position_mode;
    QLabel *label_single_trap_light_14_coloring_mode;
    MyComboBox *comboBox_single_trap_light_14_coloring_mode;
    QLabel *label_single_trap_light_14_falloff_type;
    MyComboBox *comboBox_single_trap_light_14_falloff_type;
    QLabel *label_single_trap_light_14_edge_softness;
    MyLineEdit *logedit_single_trap_light_14_edge_softness;
    QLabel *label_single_trap_light_14_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_14_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_14_anim_orbit_speed;
    MyLineEdit *logedit_single_trap_light_14_anim_pulsate_speed;
    MyLineEdit *logedit_single_trap_light_14_anim_pulsate_amount;
    QPushButton *pushButton_single_trap_light_14_place_surface;
    QPushButton *pushButton_single_trap_light_14_place_target;
    MyGroupBox *groupCheck_single_trap_light_15_enabled;
    QGridLayout *gridLayout_single_trap_light_15;
    QLabel *label_single_trap_light_15_shape;
    MyComboBox *comboBox_single_trap_light_15_shape;
    QLabel *label_single_trap_light_15_position;
    MyLineEdit *vect3_single_trap_light_15_position_x;
    MyLineEdit *vect3_single_trap_light_15_position_y;
    MyLineEdit *vect3_single_trap_light_15_position_z;
    QPushButton *pushButton_single_trap_light_15_place_camera;
    QLabel *label_single_trap_light_15_size;
    MyLineEdit *logedit_single_trap_light_15_size;
    QLabel *label_single_trap_light_15_size2;
    MyLineEdit *logedit_single_trap_light_15_size2;
    QLabel *label_single_trap_light_15_thickness;
    MyLineEdit *logedit_single_trap_light_15_thickness;
    QLabel *label_single_trap_light_15_rotation;
    MyDoubleSpinBox *spinboxd3_single_trap_light_15_rotation_x;
    MyDoubleSpinBox *spinboxd3_single_trap_light_15_rotation_y;
    MyDoubleSpinBox *spinboxd3_single_trap_light_15_rotation_z;
    QLabel *label_single_trap_light_15_intensity;
    MyLineEdit *logedit_single_trap_light_15_intensity;
    QLabel *label_single_trap_light_15_color;
    MyColorButton *colorButton_single_trap_light_15_color;
    QLabel *label_single_trap_light_15_gradient_color;
    MyColorButton *colorButton_single_trap_light_15_gradient_color;
    QLabel *label_single_trap_light_15_visibility;
    MyLineEdit *logedit_single_trap_light_15_visibility;
    QLabel *label_single_trap_light_15_max_distance;
    MyLineEdit *logedit_single_trap_light_15_max_distance;
    QLabel *label_single_trap_light_15_sharpening;
    MyLineEdit *logedit_single_trap_light_15_sharpening;
    QLabel *label_single_trap_light_15_blur;
    MyLineEdit *logedit_single_trap_light_15_blur;
    QLabel *label_single_trap_light_15_solid_intensity;
    MyLineEdit *logedit_single_trap_light_15_solid_intensity;
    QLabel *label_single_trap_light_15_softness;
    MyLineEdit *logedit_single_trap_light_15_softness;
    QLabel *label_single_trap_light_15_relative_size;
    MyLineEdit *logedit_single_trap_light_15_relative_size;
    MyCheckBox *checkBox_single_trap_light_15_pre_transformed;
    QLabel *label_single_trap_light_15_position_mode;
    MyComboBox *comboBox_single_trap_light_15_position_mode;
    QLabel *label_single_trap_light_15_coloring_mode;
    MyComboBox *comboBox_single_trap_light_15_coloring_mode;
    QLabel *label_single_trap_light_15_falloff_type;
    MyComboBox *comboBox_single_trap_light_15_falloff_type;
    QLabel *label_single_trap_light_15_edge_softness;
    MyLineEdit *logedit_single_trap_light_15_edge_softness;
    QLabel *label_single_trap_light_15_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_15_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_15_anim_orbit_speed;
    MyLineEdit *logedit_single_trap_light_15_anim_pulsate_speed;
    MyLineEdit *logedit_single_trap_light_15_anim_pulsate_amount;
    QPushButton *pushButton_single_trap_light_15_place_surface;
    QPushButton *pushButton_single_trap_light_15_place_target;
    MyGroupBox *groupCheck_single_trap_light_16_enabled;
    QGridLayout *gridLayout_single_trap_light_16;
    QLabel *label_single_trap_light_16_shape;
    MyComboBox *comboBox_single_trap_light_16_shape;
    QLabel *label_single_trap_light_16_position;
    MyLineEdit *vect3_single_trap_light_16_position_x;
    MyLineEdit *vect3_single_trap_light_16_position_y;
    MyLineEdit *vect3_single_trap_light_16_position_z;
    QPushButton *pushButton_single_trap_light_16_place_camera;
    QLabel *label_single_trap_light_16_size;
    MyLineEdit *logedit_single_trap_light_16_size;
    QLabel *label_single_trap_light_16_size2;
    MyLineEdit *logedit_single_trap_light_16_size2;
    QLabel *label_single_trap_light_16_thickness;
    MyLineEdit *logedit_single_trap_light_16_thickness;
    QLabel *label_single_trap_light_16_rotation;
    MyDoubleSpinBox *spinboxd3_single_trap_light_16_rotation_x;
    MyDoubleSpinBox *spinboxd3_single_trap_light_16_rotation_y;
    MyDoubleSpinBox *spinboxd3_single_trap_light_16_rotation_z;
    QLabel *label_single_trap_light_16_intensity;
    MyLineEdit *logedit_single_trap_light_16_intensity;
    QLabel *label_single_trap_light_16_color;
    MyColorButton *colorButton_single_trap_light_16_color;
    QLabel *label_single_trap_light_16_gradient_color;
    MyColorButton *colorButton_single_trap_light_16_gradient_color;
    QLabel *label_single_trap_light_16_visibility;
    MyLineEdit *logedit_single_trap_light_16_visibility;
    QLabel *label_single_trap_light_16_max_distance;
    MyLineEdit *logedit_single_trap_light_16_max_distance;
    QLabel *label_single_trap_light_16_sharpening;
    MyLineEdit *logedit_single_trap_light_16_sharpening;
    QLabel *label_single_trap_light_16_blur;
    MyLineEdit *logedit_single_trap_light_16_blur;
    QLabel *label_single_trap_light_16_solid_intensity;
    MyLineEdit *logedit_single_trap_light_16_solid_intensity;
    QLabel *label_single_trap_light_16_softness;
    MyLineEdit *logedit_single_trap_light_16_softness;
    QLabel *label_single_trap_light_16_relative_size;
    MyLineEdit *logedit_single_trap_light_16_relative_size;
    MyCheckBox *checkBox_single_trap_light_16_pre_transformed;
    QLabel *label_single_trap_light_16_position_mode;
    MyComboBox *comboBox_single_trap_light_16_position_mode;
    QLabel *label_single_trap_light_16_coloring_mode;
    MyComboBox *comboBox_single_trap_light_16_coloring_mode;
    QLabel *label_single_trap_light_16_falloff_type;
    MyComboBox *comboBox_single_trap_light_16_falloff_type;
    QLabel *label_single_trap_light_16_edge_softness;
    MyLineEdit *logedit_single_trap_light_16_edge_softness;
    QLabel *label_single_trap_light_16_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_16_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_16_anim_orbit_speed;
    MyLineEdit *logedit_single_trap_light_16_anim_pulsate_speed;
    MyLineEdit *logedit_single_trap_light_16_anim_pulsate_amount;
    QPushButton *pushButton_single_trap_light_16_place_surface;
    QPushButton *pushButton_single_trap_light_16_place_target;
    MyGroupBox *groupCheck_single_trap_light_17_enabled;
    QGridLayout *gridLayout_single_trap_light_17;
    QLabel *label_single_trap_light_17_shape;
    MyComboBox *comboBox_single_trap_light_17_shape;
    QLabel *label_single_trap_light_17_position;
    MyLineEdit *vect3_single_trap_light_17_position_x;
    MyLineEdit *vect3_single_trap_light_17_position_y;
    MyLineEdit *vect3_single_trap_light_17_position_z;
    QPushButton *pushButton_single_trap_light_17_place_camera;
    QLabel *label_single_trap_light_17_size;
    MyLineEdit *logedit_single_trap_light_17_size;
    QLabel *label_single_trap_light_17_size2;
    MyLineEdit *logedit_single_trap_light_17_size2;
    QLabel *label_single_trap_light_17_thickness;
    MyLineEdit *logedit_single_trap_light_17_thickness;
    QLabel *label_single_trap_light_17_rotation;
    MyDoubleSpinBox *spinboxd3_single_trap_light_17_rotation_x;
    MyDoubleSpinBox *spinboxd3_single_trap_light_17_rotation_y;
    MyDoubleSpinBox *spinboxd3_single_trap_light_17_rotation_z;
    QLabel *label_single_trap_light_17_intensity;
    MyLineEdit *logedit_single_trap_light_17_intensity;
    QLabel *label_single_trap_light_17_color;
    MyColorButton *colorButton_single_trap_light_17_color;
    QLabel *label_single_trap_light_17_gradient_color;
    MyColorButton *colorButton_single_trap_light_17_gradient_color;
    QLabel *label_single_trap_light_17_visibility;
    MyLineEdit *logedit_single_trap_light_17_visibility;
    QLabel *label_single_trap_light_17_max_distance;
    MyLineEdit *logedit_single_trap_light_17_max_distance;
    QLabel *label_single_trap_light_17_sharpening;
    MyLineEdit *logedit_single_trap_light_17_sharpening;
    QLabel *label_single_trap_light_17_blur;
    MyLineEdit *logedit_single_trap_light_17_blur;
    QLabel *label_single_trap_light_17_solid_intensity;
    MyLineEdit *logedit_single_trap_light_17_solid_intensity;
    QLabel *label_single_trap_light_17_softness;
    MyLineEdit *logedit_single_trap_light_17_softness;
    QLabel *label_single_trap_light_17_relative_size;
    MyLineEdit *logedit_single_trap_light_17_relative_size;
    MyCheckBox *checkBox_single_trap_light_17_pre_transformed;
    QLabel *label_single_trap_light_17_position_mode;
    MyComboBox *comboBox_single_trap_light_17_position_mode;
    QLabel *label_single_trap_light_17_coloring_mode;
    MyComboBox *comboBox_single_trap_light_17_coloring_mode;
    QLabel *label_single_trap_light_17_falloff_type;
    MyComboBox *comboBox_single_trap_light_17_falloff_type;
    QLabel *label_single_trap_light_17_edge_softness;
    MyLineEdit *logedit_single_trap_light_17_edge_softness;
    QLabel *label_single_trap_light_17_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_17_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_17_anim_orbit_speed;
    MyLineEdit *logedit_single_trap_light_17_anim_pulsate_speed;
    MyLineEdit *logedit_single_trap_light_17_anim_pulsate_amount;
    QPushButton *pushButton_single_trap_light_17_place_surface;
    QPushButton *pushButton_single_trap_light_17_place_target;
    MyGroupBox *groupCheck_single_trap_light_18_enabled;
    QGridLayout *gridLayout_single_trap_light_18;
    QLabel *label_single_trap_light_18_shape;
    MyComboBox *comboBox_single_trap_light_18_shape;
    QLabel *label_single_trap_light_18_position;
    MyLineEdit *vect3_single_trap_light_18_position_x;
    MyLineEdit *vect3_single_trap_light_18_position_y;
    MyLineEdit *vect3_single_trap_light_18_position_z;
    QPushButton *pushButton_single_trap_light_18_place_camera;
    QLabel *label_single_trap_light_18_size;
    MyLineEdit *logedit_single_trap_light_18_size;
    QLabel *label_single_trap_light_18_size2;
    MyLineEdit *logedit_single_trap_light_18_size2;
    QLabel *label_single_trap_light_18_thickness;
    MyLineEdit *logedit_single_trap_light_18_thickness;
    QLabel *label_single_trap_light_18_rotation;
    MyDoubleSpinBox *spinboxd3_single_trap_light_18_rotation_x;
    MyDoubleSpinBox *spinboxd3_single_trap_light_18_rotation_y;
    MyDoubleSpinBox *spinboxd3_single_trap_light_18_rotation_z;
    QLabel *label_single_trap_light_18_intensity;
    MyLineEdit *logedit_single_trap_light_18_intensity;
    QLabel *label_single_trap_light_18_color;
    MyColorButton *colorButton_single_trap_light_18_color;
    QLabel *label_single_trap_light_18_gradient_color;
    MyColorButton *colorButton_single_trap_light_18_gradient_color;
    QLabel *label_single_trap_light_18_visibility;
    MyLineEdit *logedit_single_trap_light_18_visibility;
    QLabel *label_single_trap_light_18_max_distance;
    MyLineEdit *logedit_single_trap_light_18_max_distance;
    QLabel *label_single_trap_light_18_sharpening;
    MyLineEdit *logedit_single_trap_light_18_sharpening;
    QLabel *label_single_trap_light_18_blur;
    MyLineEdit *logedit_single_trap_light_18_blur;
    QLabel *label_single_trap_light_18_solid_intensity;
    MyLineEdit *logedit_single_trap_light_18_solid_intensity;
    QLabel *label_single_trap_light_18_softness;
    MyLineEdit *logedit_single_trap_light_18_softness;
    QLabel *label_single_trap_light_18_relative_size;
    MyLineEdit *logedit_single_trap_light_18_relative_size;
    MyCheckBox *checkBox_single_trap_light_18_pre_transformed;
    QLabel *label_single_trap_light_18_position_mode;
    MyComboBox *comboBox_single_trap_light_18_position_mode;
    QLabel *label_single_trap_light_18_coloring_mode;
    MyComboBox *comboBox_single_trap_light_18_coloring_mode;
    QLabel *label_single_trap_light_18_falloff_type;
    MyComboBox *comboBox_single_trap_light_18_falloff_type;
    QLabel *label_single_trap_light_18_edge_softness;
    MyLineEdit *logedit_single_trap_light_18_edge_softness;
    QLabel *label_single_trap_light_18_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_18_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_18_anim_orbit_speed;
    MyLineEdit *logedit_single_trap_light_18_anim_pulsate_speed;
    MyLineEdit *logedit_single_trap_light_18_anim_pulsate_amount;
    QPushButton *pushButton_single_trap_light_18_place_surface;
    QPushButton *pushButton_single_trap_light_18_place_target;
    MyGroupBox *groupCheck_single_trap_light_19_enabled;
    QGridLayout *gridLayout_single_trap_light_19;
    QLabel *label_single_trap_light_19_shape;
    MyComboBox *comboBox_single_trap_light_19_shape;
    QLabel *label_single_trap_light_19_position;
    MyLineEdit *vect3_single_trap_light_19_position_x;
    MyLineEdit *vect3_single_trap_light_19_position_y;
    MyLineEdit *vect3_single_trap_light_19_position_z;
    QPushButton *pushButton_single_trap_light_19_place_camera;
    QLabel *label_single_trap_light_19_size;
    MyLineEdit *logedit_single_trap_light_19_size;
    QLabel *label_single_trap_light_19_size2;
    MyLineEdit *logedit_single_trap_light_19_size2;
    QLabel *label_single_trap_light_19_thickness;
    MyLineEdit *logedit_single_trap_light_19_thickness;
    QLabel *label_single_trap_light_19_rotation;
    MyDoubleSpinBox *spinboxd3_single_trap_light_19_rotation_x;
    MyDoubleSpinBox *spinboxd3_single_trap_light_19_rotation_y;
    MyDoubleSpinBox *spinboxd3_single_trap_light_19_rotation_z;
    QLabel *label_single_trap_light_19_intensity;
    MyLineEdit *logedit_single_trap_light_19_intensity;
    QLabel *label_single_trap_light_19_color;
    MyColorButton *colorButton_single_trap_light_19_color;
    QLabel *label_single_trap_light_19_gradient_color;
    MyColorButton *colorButton_single_trap_light_19_gradient_color;
    QLabel *label_single_trap_light_19_visibility;
    MyLineEdit *logedit_single_trap_light_19_visibility;
    QLabel *label_single_trap_light_19_max_distance;
    MyLineEdit *logedit_single_trap_light_19_max_distance;
    QLabel *label_single_trap_light_19_sharpening;
    MyLineEdit *logedit_single_trap_light_19_sharpening;
    QLabel *label_single_trap_light_19_blur;
    MyLineEdit *logedit_single_trap_light_19_blur;
    QLabel *label_single_trap_light_19_solid_intensity;
    MyLineEdit *logedit_single_trap_light_19_solid_intensity;
    QLabel *label_single_trap_light_19_softness;
    MyLineEdit *logedit_single_trap_light_19_softness;
    QLabel *label_single_trap_light_19_relative_size;
    MyLineEdit *logedit_single_trap_light_19_relative_size;
    MyCheckBox *checkBox_single_trap_light_19_pre_transformed;
    QLabel *label_single_trap_light_19_position_mode;
    MyComboBox *comboBox_single_trap_light_19_position_mode;
    QLabel *label_single_trap_light_19_coloring_mode;
    MyComboBox *comboBox_single_trap_light_19_coloring_mode;
    QLabel *label_single_trap_light_19_falloff_type;
    MyComboBox *comboBox_single_trap_light_19_falloff_type;
    QLabel *label_single_trap_light_19_edge_softness;
    MyLineEdit *logedit_single_trap_light_19_edge_softness;
    QLabel *label_single_trap_light_19_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_19_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_19_anim_orbit_speed;
    MyLineEdit *logedit_single_trap_light_19_anim_pulsate_speed;
    MyLineEdit *logedit_single_trap_light_19_anim_pulsate_amount;
    QPushButton *pushButton_single_trap_light_19_place_surface;
    QPushButton *pushButton_single_trap_light_19_place_target;
    MyGroupBox *groupCheck_single_trap_light_20_enabled;
    QGridLayout *gridLayout_single_trap_light_20;
    QLabel *label_single_trap_light_20_shape;
    MyComboBox *comboBox_single_trap_light_20_shape;
    QLabel *label_single_trap_light_20_position;
    MyLineEdit *vect3_single_trap_light_20_position_x;
    MyLineEdit *vect3_single_trap_light_20_position_y;
    MyLineEdit *vect3_single_trap_light_20_position_z;
    QPushButton *pushButton_single_trap_light_20_place_camera;
    QLabel *label_single_trap_light_20_size;
    MyLineEdit *logedit_single_trap_light_20_size;
    QLabel *label_single_trap_light_20_size2;
    MyLineEdit *logedit_single_trap_light_20_size2;
    QLabel *label_single_trap_light_20_thickness;
    MyLineEdit *logedit_single_trap_light_20_thickness;
    QLabel *label_single_trap_light_20_rotation;
    MyDoubleSpinBox *spinboxd3_single_trap_light_20_rotation_x;
    MyDoubleSpinBox *spinboxd3_single_trap_light_20_rotation_y;
    MyDoubleSpinBox *spinboxd3_single_trap_light_20_rotation_z;
    QLabel *label_single_trap_light_20_intensity;
    MyLineEdit *logedit_single_trap_light_20_intensity;
    QLabel *label_single_trap_light_20_color;
    MyColorButton *colorButton_single_trap_light_20_color;
    QLabel *label_single_trap_light_20_gradient_color;
    MyColorButton *colorButton_single_trap_light_20_gradient_color;
    QLabel *label_single_trap_light_20_visibility;
    MyLineEdit *logedit_single_trap_light_20_visibility;
    QLabel *label_single_trap_light_20_max_distance;
    MyLineEdit *logedit_single_trap_light_20_max_distance;
    QLabel *label_single_trap_light_20_sharpening;
    MyLineEdit *logedit_single_trap_light_20_sharpening;
    QLabel *label_single_trap_light_20_blur;
    MyLineEdit *logedit_single_trap_light_20_blur;
    QLabel *label_single_trap_light_20_solid_intensity;
    MyLineEdit *logedit_single_trap_light_20_solid_intensity;
    QLabel *label_single_trap_light_20_softness;
    MyLineEdit *logedit_single_trap_light_20_softness;
    QLabel *label_single_trap_light_20_relative_size;
    MyLineEdit *logedit_single_trap_light_20_relative_size;
    MyCheckBox *checkBox_single_trap_light_20_pre_transformed;
    QLabel *label_single_trap_light_20_position_mode;
    MyComboBox *comboBox_single_trap_light_20_position_mode;
    QLabel *label_single_trap_light_20_coloring_mode;
    MyComboBox *comboBox_single_trap_light_20_coloring_mode;
    QLabel *label_single_trap_light_20_falloff_type;
    MyComboBox *comboBox_single_trap_light_20_falloff_type;
    QLabel *label_single_trap_light_20_edge_softness;
    MyLineEdit *logedit_single_trap_light_20_edge_softness;
    QLabel *label_single_trap_light_20_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_20_anim_orbit_radius;
    MyLineEdit *logedit_single_trap_light_20_anim_orbit_speed;
    MyLineEdit *logedit_single_trap_light_20_anim_pulsate_speed;
    MyLineEdit *logedit_single_trap_light_20_anim_pulsate_amount;
    QPushButton *pushButton_single_trap_light_20_place_surface;
    QPushButton *pushButton_single_trap_light_20_place_target;
    QSpacerItem *verticalSpacer_single_trap;

    void setupUi(QWidget *cEffectsSingleTrapTab)
    {
        if (cEffectsSingleTrapTab->objectName().isEmpty())
            cEffectsSingleTrapTab->setObjectName(QString::fromUtf8("cEffectsSingleTrapTab"));
        verticalLayout_single_trap_tab = new QVBoxLayout(cEffectsSingleTrapTab);
        verticalLayout_single_trap_tab->setSpacing(2);
        verticalLayout_single_trap_tab->setObjectName(QString::fromUtf8("verticalLayout_single_trap_tab"));
        verticalLayout_single_trap_tab->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_single_trap_header = new QHBoxLayout();
        horizontalLayout_single_trap_header->setObjectName(QString::fromUtf8("horizontalLayout_single_trap_header"));
        pushButton_single_trap_load = new cButtonLoadSettingsFromWidget(cEffectsSingleTrapTab);
        pushButton_single_trap_load->setObjectName(QString::fromUtf8("pushButton_single_trap_load"));

        horizontalLayout_single_trap_header->addWidget(pushButton_single_trap_load);

        pushButton_single_trap_save = new cButtonSaveSettingsFromWidget(cEffectsSingleTrapTab);
        pushButton_single_trap_save->setObjectName(QString::fromUtf8("pushButton_single_trap_save"));

        horizontalLayout_single_trap_header->addWidget(pushButton_single_trap_save);

        horizontalSpacer_single_trap = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_single_trap_header->addItem(horizontalSpacer_single_trap);


        verticalLayout_single_trap_tab->addLayout(horizontalLayout_single_trap_header);

        groupCheck_single_trap_lights_enabled = new MyGroupBox(cEffectsSingleTrapTab);
        groupCheck_single_trap_lights_enabled->setObjectName(QString::fromUtf8("groupCheck_single_trap_lights_enabled"));
        groupCheck_single_trap_lights_enabled->setCheckable(true);
        verticalLayout_single_trap_master = new QVBoxLayout(groupCheck_single_trap_lights_enabled);
        verticalLayout_single_trap_master->setSpacing(2);
        verticalLayout_single_trap_master->setObjectName(QString::fromUtf8("verticalLayout_single_trap_master"));
        verticalLayout_single_trap_master->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_active_count = new QHBoxLayout();
        horizontalLayout_active_count->setObjectName(QString::fromUtf8("horizontalLayout_active_count"));
        label_single_trap_active_count = new QLabel(groupCheck_single_trap_lights_enabled);
        label_single_trap_active_count->setObjectName(QString::fromUtf8("label_single_trap_active_count"));

        horizontalLayout_active_count->addWidget(label_single_trap_active_count);

        spinboxInt_single_trap_lights_active_count = new MySpinBox(groupCheck_single_trap_lights_enabled);
        spinboxInt_single_trap_lights_active_count->setObjectName(QString::fromUtf8("spinboxInt_single_trap_lights_active_count"));

        horizontalLayout_active_count->addWidget(spinboxInt_single_trap_lights_active_count);

        horizontalSpacer_active_count = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_active_count->addItem(horizontalSpacer_active_count);


        verticalLayout_single_trap_master->addLayout(horizontalLayout_active_count);

        label_single_trap_independent_hint = new QLabel(groupCheck_single_trap_lights_enabled);
        label_single_trap_independent_hint->setObjectName(QString::fromUtf8("label_single_trap_independent_hint"));
        label_single_trap_independent_hint->setWordWrap(true);

        verticalLayout_single_trap_master->addWidget(label_single_trap_independent_hint);

        groupBox_single_trap_tuning = new QGroupBox(groupCheck_single_trap_lights_enabled);
        groupBox_single_trap_tuning->setObjectName(QString::fromUtf8("groupBox_single_trap_tuning"));
        horizontalLayout_single_trap_tuning = new QHBoxLayout(groupBox_single_trap_tuning);
        horizontalLayout_single_trap_tuning->setObjectName(QString::fromUtf8("horizontalLayout_single_trap_tuning"));
        label_single_trap_solo_layer = new QLabel(groupBox_single_trap_tuning);
        label_single_trap_solo_layer->setObjectName(QString::fromUtf8("label_single_trap_solo_layer"));

        horizontalLayout_single_trap_tuning->addWidget(label_single_trap_solo_layer);

        spinboxInt_single_trap_lights_solo_layer = new MySpinBox(groupBox_single_trap_tuning);
        spinboxInt_single_trap_lights_solo_layer->setObjectName(QString::fromUtf8("spinboxInt_single_trap_lights_solo_layer"));
        spinboxInt_single_trap_lights_solo_layer->setMinimum(0);
        spinboxInt_single_trap_lights_solo_layer->setMaximum(20);

        horizontalLayout_single_trap_tuning->addWidget(spinboxInt_single_trap_lights_solo_layer);

        label_single_trap_combine_mode = new QLabel(groupBox_single_trap_tuning);
        label_single_trap_combine_mode->setObjectName(QString::fromUtf8("label_single_trap_combine_mode"));

        horizontalLayout_single_trap_tuning->addWidget(label_single_trap_combine_mode);

        comboBox_single_trap_lights_combine_mode = new MyComboBox(groupBox_single_trap_tuning);
        comboBox_single_trap_lights_combine_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_lights_combine_mode"));

        horizontalLayout_single_trap_tuning->addWidget(comboBox_single_trap_lights_combine_mode);

        horizontalSpacer_single_trap_tuning = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_single_trap_tuning->addItem(horizontalSpacer_single_trap_tuning);


        verticalLayout_single_trap_master->addWidget(groupBox_single_trap_tuning);

        horizontalLayout_single_trap_copy = new QHBoxLayout();
        horizontalLayout_single_trap_copy->setObjectName(QString::fromUtf8("horizontalLayout_single_trap_copy"));
        label_single_trap_copy_from = new QLabel(groupCheck_single_trap_lights_enabled);
        label_single_trap_copy_from->setObjectName(QString::fromUtf8("label_single_trap_copy_from"));

        horizontalLayout_single_trap_copy->addWidget(label_single_trap_copy_from);

        spinboxInt_single_trap_copy_from = new MySpinBox(groupCheck_single_trap_lights_enabled);
        spinboxInt_single_trap_copy_from->setObjectName(QString::fromUtf8("spinboxInt_single_trap_copy_from"));
        spinboxInt_single_trap_copy_from->setMinimum(1);
        spinboxInt_single_trap_copy_from->setMaximum(20);
        spinboxInt_single_trap_copy_from->setValue(1);

        horizontalLayout_single_trap_copy->addWidget(spinboxInt_single_trap_copy_from);

        label_single_trap_copy_to = new QLabel(groupCheck_single_trap_lights_enabled);
        label_single_trap_copy_to->setObjectName(QString::fromUtf8("label_single_trap_copy_to"));

        horizontalLayout_single_trap_copy->addWidget(label_single_trap_copy_to);

        spinboxInt_single_trap_copy_to = new MySpinBox(groupCheck_single_trap_lights_enabled);
        spinboxInt_single_trap_copy_to->setObjectName(QString::fromUtf8("spinboxInt_single_trap_copy_to"));
        spinboxInt_single_trap_copy_to->setMinimum(1);
        spinboxInt_single_trap_copy_to->setMaximum(20);
        spinboxInt_single_trap_copy_to->setValue(2);

        horizontalLayout_single_trap_copy->addWidget(spinboxInt_single_trap_copy_to);

        pushButton_single_trap_copy = new QPushButton(groupCheck_single_trap_lights_enabled);
        pushButton_single_trap_copy->setObjectName(QString::fromUtf8("pushButton_single_trap_copy"));

        horizontalLayout_single_trap_copy->addWidget(pushButton_single_trap_copy);

        label_single_trap_randomize_layer = new QLabel(groupCheck_single_trap_lights_enabled);
        label_single_trap_randomize_layer->setObjectName(QString::fromUtf8("label_single_trap_randomize_layer"));

        horizontalLayout_single_trap_copy->addWidget(label_single_trap_randomize_layer);

        spinboxInt_single_trap_randomize_layer = new MySpinBox(groupCheck_single_trap_lights_enabled);
        spinboxInt_single_trap_randomize_layer->setObjectName(QString::fromUtf8("spinboxInt_single_trap_randomize_layer"));
        spinboxInt_single_trap_randomize_layer->setMinimum(1);
        spinboxInt_single_trap_randomize_layer->setMaximum(20);
        spinboxInt_single_trap_randomize_layer->setValue(1);

        horizontalLayout_single_trap_copy->addWidget(spinboxInt_single_trap_randomize_layer);

        pushButton_single_trap_randomize = new QPushButton(groupCheck_single_trap_lights_enabled);
        pushButton_single_trap_randomize->setObjectName(QString::fromUtf8("pushButton_single_trap_randomize"));

        horizontalLayout_single_trap_copy->addWidget(pushButton_single_trap_randomize);

        pushButton_single_trap_world_anchor = new QPushButton(groupCheck_single_trap_lights_enabled);
        pushButton_single_trap_world_anchor->setObjectName(QString::fromUtf8("pushButton_single_trap_world_anchor"));

        horizontalLayout_single_trap_copy->addWidget(pushButton_single_trap_world_anchor);

        pushButton_single_trap_randomize_all = new QPushButton(groupCheck_single_trap_lights_enabled);
        pushButton_single_trap_randomize_all->setObjectName(QString::fromUtf8("pushButton_single_trap_randomize_all"));

        horizontalLayout_single_trap_copy->addWidget(pushButton_single_trap_randomize_all);


        verticalLayout_single_trap_master->addLayout(horizontalLayout_single_trap_copy);

        horizontalLayout_single_trap_presets = new QHBoxLayout();
        horizontalLayout_single_trap_presets->setObjectName(QString::fromUtf8("horizontalLayout_single_trap_presets"));
        label_single_trap_preset = new QLabel(groupCheck_single_trap_lights_enabled);
        label_single_trap_preset->setObjectName(QString::fromUtf8("label_single_trap_preset"));

        horizontalLayout_single_trap_presets->addWidget(label_single_trap_preset);

        comboBox_single_trap_presets = new MyComboBox(groupCheck_single_trap_lights_enabled);
        comboBox_single_trap_presets->setObjectName(QString::fromUtf8("comboBox_single_trap_presets"));

        horizontalLayout_single_trap_presets->addWidget(comboBox_single_trap_presets);

        pushButton_single_trap_preset_refresh = new QPushButton(groupCheck_single_trap_lights_enabled);
        pushButton_single_trap_preset_refresh->setObjectName(QString::fromUtf8("pushButton_single_trap_preset_refresh"));

        horizontalLayout_single_trap_presets->addWidget(pushButton_single_trap_preset_refresh);

        pushButton_single_trap_preset_load = new QPushButton(groupCheck_single_trap_lights_enabled);
        pushButton_single_trap_preset_load->setObjectName(QString::fromUtf8("pushButton_single_trap_preset_load"));

        horizontalLayout_single_trap_presets->addWidget(pushButton_single_trap_preset_load);

        pushButton_single_trap_preset_save = new QPushButton(groupCheck_single_trap_lights_enabled);
        pushButton_single_trap_preset_save->setObjectName(QString::fromUtf8("pushButton_single_trap_preset_save"));

        horizontalLayout_single_trap_presets->addWidget(pushButton_single_trap_preset_save);

        pushButton_single_trap_reset_all = new QPushButton(groupCheck_single_trap_lights_enabled);
        pushButton_single_trap_reset_all->setObjectName(QString::fromUtf8("pushButton_single_trap_reset_all"));

        horizontalLayout_single_trap_presets->addWidget(pushButton_single_trap_reset_all);


        verticalLayout_single_trap_master->addLayout(horizontalLayout_single_trap_presets);

        scrollArea_single_trap_layers = new QScrollArea(groupCheck_single_trap_lights_enabled);
        scrollArea_single_trap_layers->setObjectName(QString::fromUtf8("scrollArea_single_trap_layers"));
        scrollArea_single_trap_layers->setWidgetResizable(true);
        scrollAreaWidgetContents_single_trap = new QWidget();
        scrollAreaWidgetContents_single_trap->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_single_trap"));
        scrollAreaWidgetContents_single_trap->setGeometry(QRect(0, 0, 380, 1200));
        verticalLayout_single_trap_layers = new QVBoxLayout(scrollAreaWidgetContents_single_trap);
        verticalLayout_single_trap_layers->setSpacing(2);
        verticalLayout_single_trap_layers->setObjectName(QString::fromUtf8("verticalLayout_single_trap_layers"));
        verticalLayout_single_trap_layers->setContentsMargins(2, 2, 2, 2);
        groupCheck_single_trap_light_1_enabled = new MyGroupBox(scrollAreaWidgetContents_single_trap);
        groupCheck_single_trap_light_1_enabled->setObjectName(QString::fromUtf8("groupCheck_single_trap_light_1_enabled"));
        groupCheck_single_trap_light_1_enabled->setCheckable(true);
        gridLayout_single_trap_light_1 = new QGridLayout(groupCheck_single_trap_light_1_enabled);
        gridLayout_single_trap_light_1->setSpacing(2);
        gridLayout_single_trap_light_1->setObjectName(QString::fromUtf8("gridLayout_single_trap_light_1"));
        label_single_trap_light_1_shape = new QLabel(groupCheck_single_trap_light_1_enabled);
        label_single_trap_light_1_shape->setObjectName(QString::fromUtf8("label_single_trap_light_1_shape"));

        gridLayout_single_trap_light_1->addWidget(label_single_trap_light_1_shape, 0, 0, 1, 1);

        comboBox_single_trap_light_1_shape = new MyComboBox(groupCheck_single_trap_light_1_enabled);
        comboBox_single_trap_light_1_shape->addItem(QString());
        comboBox_single_trap_light_1_shape->addItem(QString());
        comboBox_single_trap_light_1_shape->addItem(QString());
        comboBox_single_trap_light_1_shape->addItem(QString());
        comboBox_single_trap_light_1_shape->addItem(QString());
        comboBox_single_trap_light_1_shape->addItem(QString());
        comboBox_single_trap_light_1_shape->addItem(QString());
        comboBox_single_trap_light_1_shape->addItem(QString());
        comboBox_single_trap_light_1_shape->addItem(QString());
        comboBox_single_trap_light_1_shape->addItem(QString());
        comboBox_single_trap_light_1_shape->addItem(QString());
        comboBox_single_trap_light_1_shape->addItem(QString());
        comboBox_single_trap_light_1_shape->addItem(QString());
        comboBox_single_trap_light_1_shape->addItem(QString());
        comboBox_single_trap_light_1_shape->setObjectName(QString::fromUtf8("comboBox_single_trap_light_1_shape"));

        gridLayout_single_trap_light_1->addWidget(comboBox_single_trap_light_1_shape, 0, 1, 1, 2);

        label_single_trap_light_1_position = new QLabel(groupCheck_single_trap_light_1_enabled);
        label_single_trap_light_1_position->setObjectName(QString::fromUtf8("label_single_trap_light_1_position"));

        gridLayout_single_trap_light_1->addWidget(label_single_trap_light_1_position, 1, 0, 1, 1);

        vect3_single_trap_light_1_position_x = new MyLineEdit(groupCheck_single_trap_light_1_enabled);
        vect3_single_trap_light_1_position_x->setObjectName(QString::fromUtf8("vect3_single_trap_light_1_position_x"));

        gridLayout_single_trap_light_1->addWidget(vect3_single_trap_light_1_position_x, 1, 1, 1, 1);

        vect3_single_trap_light_1_position_y = new MyLineEdit(groupCheck_single_trap_light_1_enabled);
        vect3_single_trap_light_1_position_y->setObjectName(QString::fromUtf8("vect3_single_trap_light_1_position_y"));

        gridLayout_single_trap_light_1->addWidget(vect3_single_trap_light_1_position_y, 1, 2, 1, 1);

        vect3_single_trap_light_1_position_z = new MyLineEdit(groupCheck_single_trap_light_1_enabled);
        vect3_single_trap_light_1_position_z->setObjectName(QString::fromUtf8("vect3_single_trap_light_1_position_z"));

        gridLayout_single_trap_light_1->addWidget(vect3_single_trap_light_1_position_z, 1, 3, 1, 1);

        pushButton_single_trap_light_1_place_camera = new QPushButton(groupCheck_single_trap_light_1_enabled);
        pushButton_single_trap_light_1_place_camera->setObjectName(QString::fromUtf8("pushButton_single_trap_light_1_place_camera"));

        gridLayout_single_trap_light_1->addWidget(pushButton_single_trap_light_1_place_camera, 1, 4, 1, 1);

        label_single_trap_light_1_size = new QLabel(groupCheck_single_trap_light_1_enabled);
        label_single_trap_light_1_size->setObjectName(QString::fromUtf8("label_single_trap_light_1_size"));

        gridLayout_single_trap_light_1->addWidget(label_single_trap_light_1_size, 2, 0, 1, 1);

        logedit_single_trap_light_1_size = new MyLineEdit(groupCheck_single_trap_light_1_enabled);
        logedit_single_trap_light_1_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_1_size"));

        gridLayout_single_trap_light_1->addWidget(logedit_single_trap_light_1_size, 2, 1, 1, 2);

        label_single_trap_light_1_size2 = new QLabel(groupCheck_single_trap_light_1_enabled);
        label_single_trap_light_1_size2->setObjectName(QString::fromUtf8("label_single_trap_light_1_size2"));

        gridLayout_single_trap_light_1->addWidget(label_single_trap_light_1_size2, 2, 3, 1, 1);

        logedit_single_trap_light_1_size2 = new MyLineEdit(groupCheck_single_trap_light_1_enabled);
        logedit_single_trap_light_1_size2->setObjectName(QString::fromUtf8("logedit_single_trap_light_1_size2"));

        gridLayout_single_trap_light_1->addWidget(logedit_single_trap_light_1_size2, 2, 4, 1, 1);

        label_single_trap_light_1_thickness = new QLabel(groupCheck_single_trap_light_1_enabled);
        label_single_trap_light_1_thickness->setObjectName(QString::fromUtf8("label_single_trap_light_1_thickness"));

        gridLayout_single_trap_light_1->addWidget(label_single_trap_light_1_thickness, 3, 0, 1, 1);

        logedit_single_trap_light_1_thickness = new MyLineEdit(groupCheck_single_trap_light_1_enabled);
        logedit_single_trap_light_1_thickness->setObjectName(QString::fromUtf8("logedit_single_trap_light_1_thickness"));

        gridLayout_single_trap_light_1->addWidget(logedit_single_trap_light_1_thickness, 3, 1, 1, 2);

        label_single_trap_light_1_rotation = new QLabel(groupCheck_single_trap_light_1_enabled);
        label_single_trap_light_1_rotation->setObjectName(QString::fromUtf8("label_single_trap_light_1_rotation"));

        gridLayout_single_trap_light_1->addWidget(label_single_trap_light_1_rotation, 4, 0, 1, 1);

        spinboxd3_single_trap_light_1_rotation_x = new MyDoubleSpinBox(groupCheck_single_trap_light_1_enabled);
        spinboxd3_single_trap_light_1_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_1_rotation_x"));

        gridLayout_single_trap_light_1->addWidget(spinboxd3_single_trap_light_1_rotation_x, 4, 1, 1, 1);

        spinboxd3_single_trap_light_1_rotation_y = new MyDoubleSpinBox(groupCheck_single_trap_light_1_enabled);
        spinboxd3_single_trap_light_1_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_1_rotation_y"));

        gridLayout_single_trap_light_1->addWidget(spinboxd3_single_trap_light_1_rotation_y, 4, 2, 1, 1);

        spinboxd3_single_trap_light_1_rotation_z = new MyDoubleSpinBox(groupCheck_single_trap_light_1_enabled);
        spinboxd3_single_trap_light_1_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_1_rotation_z"));

        gridLayout_single_trap_light_1->addWidget(spinboxd3_single_trap_light_1_rotation_z, 4, 3, 1, 1);

        label_single_trap_light_1_intensity = new QLabel(groupCheck_single_trap_light_1_enabled);
        label_single_trap_light_1_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_1_intensity"));

        gridLayout_single_trap_light_1->addWidget(label_single_trap_light_1_intensity, 5, 0, 1, 1);

        logedit_single_trap_light_1_intensity = new MyLineEdit(groupCheck_single_trap_light_1_enabled);
        logedit_single_trap_light_1_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_1_intensity"));

        gridLayout_single_trap_light_1->addWidget(logedit_single_trap_light_1_intensity, 5, 1, 1, 2);

        label_single_trap_light_1_color = new QLabel(groupCheck_single_trap_light_1_enabled);
        label_single_trap_light_1_color->setObjectName(QString::fromUtf8("label_single_trap_light_1_color"));

        gridLayout_single_trap_light_1->addWidget(label_single_trap_light_1_color, 6, 0, 1, 1);

        colorButton_single_trap_light_1_color = new MyColorButton(groupCheck_single_trap_light_1_enabled);
        colorButton_single_trap_light_1_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_1_color"));

        gridLayout_single_trap_light_1->addWidget(colorButton_single_trap_light_1_color, 6, 1, 1, 1);

        label_single_trap_light_1_gradient_color = new QLabel(groupCheck_single_trap_light_1_enabled);
        label_single_trap_light_1_gradient_color->setObjectName(QString::fromUtf8("label_single_trap_light_1_gradient_color"));

        gridLayout_single_trap_light_1->addWidget(label_single_trap_light_1_gradient_color, 6, 2, 1, 1);

        colorButton_single_trap_light_1_gradient_color = new MyColorButton(groupCheck_single_trap_light_1_enabled);
        colorButton_single_trap_light_1_gradient_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_1_gradient_color"));

        gridLayout_single_trap_light_1->addWidget(colorButton_single_trap_light_1_gradient_color, 6, 3, 1, 2);

        label_single_trap_light_1_visibility = new QLabel(groupCheck_single_trap_light_1_enabled);
        label_single_trap_light_1_visibility->setObjectName(QString::fromUtf8("label_single_trap_light_1_visibility"));

        gridLayout_single_trap_light_1->addWidget(label_single_trap_light_1_visibility, 7, 0, 1, 1);

        logedit_single_trap_light_1_visibility = new MyLineEdit(groupCheck_single_trap_light_1_enabled);
        logedit_single_trap_light_1_visibility->setObjectName(QString::fromUtf8("logedit_single_trap_light_1_visibility"));

        gridLayout_single_trap_light_1->addWidget(logedit_single_trap_light_1_visibility, 7, 1, 1, 2);

        label_single_trap_light_1_max_distance = new QLabel(groupCheck_single_trap_light_1_enabled);
        label_single_trap_light_1_max_distance->setObjectName(QString::fromUtf8("label_single_trap_light_1_max_distance"));

        gridLayout_single_trap_light_1->addWidget(label_single_trap_light_1_max_distance, 7, 3, 1, 1);

        logedit_single_trap_light_1_max_distance = new MyLineEdit(groupCheck_single_trap_light_1_enabled);
        logedit_single_trap_light_1_max_distance->setObjectName(QString::fromUtf8("logedit_single_trap_light_1_max_distance"));

        gridLayout_single_trap_light_1->addWidget(logedit_single_trap_light_1_max_distance, 7, 4, 1, 1);

        label_single_trap_light_1_sharpening = new QLabel(groupCheck_single_trap_light_1_enabled);
        label_single_trap_light_1_sharpening->setObjectName(QString::fromUtf8("label_single_trap_light_1_sharpening"));

        gridLayout_single_trap_light_1->addWidget(label_single_trap_light_1_sharpening, 8, 0, 1, 1);

        logedit_single_trap_light_1_sharpening = new MyLineEdit(groupCheck_single_trap_light_1_enabled);
        logedit_single_trap_light_1_sharpening->setObjectName(QString::fromUtf8("logedit_single_trap_light_1_sharpening"));

        gridLayout_single_trap_light_1->addWidget(logedit_single_trap_light_1_sharpening, 8, 1, 1, 2);

        label_single_trap_light_1_blur = new QLabel(groupCheck_single_trap_light_1_enabled);
        label_single_trap_light_1_blur->setObjectName(QString::fromUtf8("label_single_trap_light_1_blur"));

        gridLayout_single_trap_light_1->addWidget(label_single_trap_light_1_blur, 8, 3, 1, 1);

        logedit_single_trap_light_1_blur = new MyLineEdit(groupCheck_single_trap_light_1_enabled);
        logedit_single_trap_light_1_blur->setObjectName(QString::fromUtf8("logedit_single_trap_light_1_blur"));

        gridLayout_single_trap_light_1->addWidget(logedit_single_trap_light_1_blur, 8, 4, 1, 1);

        label_single_trap_light_1_solid_intensity = new QLabel(groupCheck_single_trap_light_1_enabled);
        label_single_trap_light_1_solid_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_1_solid_intensity"));

        gridLayout_single_trap_light_1->addWidget(label_single_trap_light_1_solid_intensity, 9, 0, 1, 1);

        logedit_single_trap_light_1_solid_intensity = new MyLineEdit(groupCheck_single_trap_light_1_enabled);
        logedit_single_trap_light_1_solid_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_1_solid_intensity"));

        gridLayout_single_trap_light_1->addWidget(logedit_single_trap_light_1_solid_intensity, 9, 1, 1, 2);

        label_single_trap_light_1_softness = new QLabel(groupCheck_single_trap_light_1_enabled);
        label_single_trap_light_1_softness->setObjectName(QString::fromUtf8("label_single_trap_light_1_softness"));

        gridLayout_single_trap_light_1->addWidget(label_single_trap_light_1_softness, 9, 3, 1, 1);

        logedit_single_trap_light_1_softness = new MyLineEdit(groupCheck_single_trap_light_1_enabled);
        logedit_single_trap_light_1_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_1_softness"));

        gridLayout_single_trap_light_1->addWidget(logedit_single_trap_light_1_softness, 9, 4, 1, 1);

        label_single_trap_light_1_relative_size = new QLabel(groupCheck_single_trap_light_1_enabled);
        label_single_trap_light_1_relative_size->setObjectName(QString::fromUtf8("label_single_trap_light_1_relative_size"));

        gridLayout_single_trap_light_1->addWidget(label_single_trap_light_1_relative_size, 10, 0, 1, 1);

        logedit_single_trap_light_1_relative_size = new MyLineEdit(groupCheck_single_trap_light_1_enabled);
        logedit_single_trap_light_1_relative_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_1_relative_size"));

        gridLayout_single_trap_light_1->addWidget(logedit_single_trap_light_1_relative_size, 10, 1, 1, 2);

        checkBox_single_trap_light_1_pre_transformed = new MyCheckBox(groupCheck_single_trap_light_1_enabled);
        checkBox_single_trap_light_1_pre_transformed->setObjectName(QString::fromUtf8("checkBox_single_trap_light_1_pre_transformed"));

        gridLayout_single_trap_light_1->addWidget(checkBox_single_trap_light_1_pre_transformed, 11, 0, 1, 1);

        label_single_trap_light_1_position_mode = new QLabel(groupCheck_single_trap_light_1_enabled);
        label_single_trap_light_1_position_mode->setObjectName(QString::fromUtf8("label_single_trap_light_1_position_mode"));

        gridLayout_single_trap_light_1->addWidget(label_single_trap_light_1_position_mode, 12, 0, 1, 1);

        comboBox_single_trap_light_1_position_mode = new MyComboBox(groupCheck_single_trap_light_1_enabled);
        comboBox_single_trap_light_1_position_mode->addItem(QString());
        comboBox_single_trap_light_1_position_mode->addItem(QString());
        comboBox_single_trap_light_1_position_mode->addItem(QString());
        comboBox_single_trap_light_1_position_mode->addItem(QString());
        comboBox_single_trap_light_1_position_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_1_position_mode"));

        gridLayout_single_trap_light_1->addWidget(comboBox_single_trap_light_1_position_mode, 12, 1, 1, 2);

        label_single_trap_light_1_coloring_mode = new QLabel(groupCheck_single_trap_light_1_enabled);
        label_single_trap_light_1_coloring_mode->setObjectName(QString::fromUtf8("label_single_trap_light_1_coloring_mode"));

        gridLayout_single_trap_light_1->addWidget(label_single_trap_light_1_coloring_mode, 13, 0, 1, 1);

        comboBox_single_trap_light_1_coloring_mode = new MyComboBox(groupCheck_single_trap_light_1_enabled);
        comboBox_single_trap_light_1_coloring_mode->addItem(QString());
        comboBox_single_trap_light_1_coloring_mode->addItem(QString());
        comboBox_single_trap_light_1_coloring_mode->addItem(QString());
        comboBox_single_trap_light_1_coloring_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_1_coloring_mode"));

        gridLayout_single_trap_light_1->addWidget(comboBox_single_trap_light_1_coloring_mode, 13, 1, 1, 2);

        label_single_trap_light_1_falloff_type = new QLabel(groupCheck_single_trap_light_1_enabled);
        label_single_trap_light_1_falloff_type->setObjectName(QString::fromUtf8("label_single_trap_light_1_falloff_type"));

        gridLayout_single_trap_light_1->addWidget(label_single_trap_light_1_falloff_type, 14, 0, 1, 1);

        comboBox_single_trap_light_1_falloff_type = new MyComboBox(groupCheck_single_trap_light_1_enabled);
        comboBox_single_trap_light_1_falloff_type->addItem(QString());
        comboBox_single_trap_light_1_falloff_type->addItem(QString());
        comboBox_single_trap_light_1_falloff_type->addItem(QString());
        comboBox_single_trap_light_1_falloff_type->addItem(QString());
        comboBox_single_trap_light_1_falloff_type->addItem(QString());
        comboBox_single_trap_light_1_falloff_type->setObjectName(QString::fromUtf8("comboBox_single_trap_light_1_falloff_type"));

        gridLayout_single_trap_light_1->addWidget(comboBox_single_trap_light_1_falloff_type, 14, 1, 1, 2);

        label_single_trap_light_1_edge_softness = new QLabel(groupCheck_single_trap_light_1_enabled);
        label_single_trap_light_1_edge_softness->setObjectName(QString::fromUtf8("label_single_trap_light_1_edge_softness"));

        gridLayout_single_trap_light_1->addWidget(label_single_trap_light_1_edge_softness, 15, 0, 1, 1);

        logedit_single_trap_light_1_edge_softness = new MyLineEdit(groupCheck_single_trap_light_1_enabled);
        logedit_single_trap_light_1_edge_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_1_edge_softness"));

        gridLayout_single_trap_light_1->addWidget(logedit_single_trap_light_1_edge_softness, 15, 1, 1, 2);

        label_single_trap_light_1_anim_orbit_radius = new QLabel(groupCheck_single_trap_light_1_enabled);
        label_single_trap_light_1_anim_orbit_radius->setObjectName(QString::fromUtf8("label_single_trap_light_1_anim_orbit_radius"));

        gridLayout_single_trap_light_1->addWidget(label_single_trap_light_1_anim_orbit_radius, 16, 0, 1, 1);

        logedit_single_trap_light_1_anim_orbit_radius = new MyLineEdit(groupCheck_single_trap_light_1_enabled);
        logedit_single_trap_light_1_anim_orbit_radius->setObjectName(QString::fromUtf8("logedit_single_trap_light_1_anim_orbit_radius"));

        gridLayout_single_trap_light_1->addWidget(logedit_single_trap_light_1_anim_orbit_radius, 16, 1, 1, 1);

        logedit_single_trap_light_1_anim_orbit_speed = new MyLineEdit(groupCheck_single_trap_light_1_enabled);
        logedit_single_trap_light_1_anim_orbit_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_1_anim_orbit_speed"));

        gridLayout_single_trap_light_1->addWidget(logedit_single_trap_light_1_anim_orbit_speed, 16, 2, 1, 1);

        logedit_single_trap_light_1_anim_pulsate_speed = new MyLineEdit(groupCheck_single_trap_light_1_enabled);
        logedit_single_trap_light_1_anim_pulsate_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_1_anim_pulsate_speed"));

        gridLayout_single_trap_light_1->addWidget(logedit_single_trap_light_1_anim_pulsate_speed, 16, 3, 1, 1);

        logedit_single_trap_light_1_anim_pulsate_amount = new MyLineEdit(groupCheck_single_trap_light_1_enabled);
        logedit_single_trap_light_1_anim_pulsate_amount->setObjectName(QString::fromUtf8("logedit_single_trap_light_1_anim_pulsate_amount"));

        gridLayout_single_trap_light_1->addWidget(logedit_single_trap_light_1_anim_pulsate_amount, 16, 4, 1, 1);

        pushButton_single_trap_light_1_place_surface = new QPushButton(groupCheck_single_trap_light_1_enabled);
        pushButton_single_trap_light_1_place_surface->setObjectName(QString::fromUtf8("pushButton_single_trap_light_1_place_surface"));

        gridLayout_single_trap_light_1->addWidget(pushButton_single_trap_light_1_place_surface, 17, 0, 1, 5);

        pushButton_single_trap_light_1_place_target = new QPushButton(groupCheck_single_trap_light_1_enabled);
        pushButton_single_trap_light_1_place_target->setObjectName(QString::fromUtf8("pushButton_single_trap_light_1_place_target"));

        gridLayout_single_trap_light_1->addWidget(pushButton_single_trap_light_1_place_target, 18, 0, 1, 5);


        verticalLayout_single_trap_layers->addWidget(groupCheck_single_trap_light_1_enabled);

        groupCheck_single_trap_light_2_enabled = new MyGroupBox(scrollAreaWidgetContents_single_trap);
        groupCheck_single_trap_light_2_enabled->setObjectName(QString::fromUtf8("groupCheck_single_trap_light_2_enabled"));
        groupCheck_single_trap_light_2_enabled->setCheckable(true);
        gridLayout_single_trap_light_2 = new QGridLayout(groupCheck_single_trap_light_2_enabled);
        gridLayout_single_trap_light_2->setSpacing(2);
        gridLayout_single_trap_light_2->setObjectName(QString::fromUtf8("gridLayout_single_trap_light_2"));
        label_single_trap_light_2_shape = new QLabel(groupCheck_single_trap_light_2_enabled);
        label_single_trap_light_2_shape->setObjectName(QString::fromUtf8("label_single_trap_light_2_shape"));

        gridLayout_single_trap_light_2->addWidget(label_single_trap_light_2_shape, 0, 0, 1, 1);

        comboBox_single_trap_light_2_shape = new MyComboBox(groupCheck_single_trap_light_2_enabled);
        comboBox_single_trap_light_2_shape->addItem(QString());
        comboBox_single_trap_light_2_shape->addItem(QString());
        comboBox_single_trap_light_2_shape->addItem(QString());
        comboBox_single_trap_light_2_shape->addItem(QString());
        comboBox_single_trap_light_2_shape->addItem(QString());
        comboBox_single_trap_light_2_shape->addItem(QString());
        comboBox_single_trap_light_2_shape->addItem(QString());
        comboBox_single_trap_light_2_shape->addItem(QString());
        comboBox_single_trap_light_2_shape->addItem(QString());
        comboBox_single_trap_light_2_shape->addItem(QString());
        comboBox_single_trap_light_2_shape->addItem(QString());
        comboBox_single_trap_light_2_shape->addItem(QString());
        comboBox_single_trap_light_2_shape->addItem(QString());
        comboBox_single_trap_light_2_shape->addItem(QString());
        comboBox_single_trap_light_2_shape->setObjectName(QString::fromUtf8("comboBox_single_trap_light_2_shape"));

        gridLayout_single_trap_light_2->addWidget(comboBox_single_trap_light_2_shape, 0, 1, 1, 2);

        label_single_trap_light_2_position = new QLabel(groupCheck_single_trap_light_2_enabled);
        label_single_trap_light_2_position->setObjectName(QString::fromUtf8("label_single_trap_light_2_position"));

        gridLayout_single_trap_light_2->addWidget(label_single_trap_light_2_position, 1, 0, 1, 1);

        vect3_single_trap_light_2_position_x = new MyLineEdit(groupCheck_single_trap_light_2_enabled);
        vect3_single_trap_light_2_position_x->setObjectName(QString::fromUtf8("vect3_single_trap_light_2_position_x"));

        gridLayout_single_trap_light_2->addWidget(vect3_single_trap_light_2_position_x, 1, 1, 1, 1);

        vect3_single_trap_light_2_position_y = new MyLineEdit(groupCheck_single_trap_light_2_enabled);
        vect3_single_trap_light_2_position_y->setObjectName(QString::fromUtf8("vect3_single_trap_light_2_position_y"));

        gridLayout_single_trap_light_2->addWidget(vect3_single_trap_light_2_position_y, 1, 2, 1, 1);

        vect3_single_trap_light_2_position_z = new MyLineEdit(groupCheck_single_trap_light_2_enabled);
        vect3_single_trap_light_2_position_z->setObjectName(QString::fromUtf8("vect3_single_trap_light_2_position_z"));

        gridLayout_single_trap_light_2->addWidget(vect3_single_trap_light_2_position_z, 1, 3, 1, 1);

        pushButton_single_trap_light_2_place_camera = new QPushButton(groupCheck_single_trap_light_2_enabled);
        pushButton_single_trap_light_2_place_camera->setObjectName(QString::fromUtf8("pushButton_single_trap_light_2_place_camera"));

        gridLayout_single_trap_light_2->addWidget(pushButton_single_trap_light_2_place_camera, 1, 4, 1, 1);

        label_single_trap_light_2_size = new QLabel(groupCheck_single_trap_light_2_enabled);
        label_single_trap_light_2_size->setObjectName(QString::fromUtf8("label_single_trap_light_2_size"));

        gridLayout_single_trap_light_2->addWidget(label_single_trap_light_2_size, 2, 0, 1, 1);

        logedit_single_trap_light_2_size = new MyLineEdit(groupCheck_single_trap_light_2_enabled);
        logedit_single_trap_light_2_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_2_size"));

        gridLayout_single_trap_light_2->addWidget(logedit_single_trap_light_2_size, 2, 1, 1, 2);

        label_single_trap_light_2_size2 = new QLabel(groupCheck_single_trap_light_2_enabled);
        label_single_trap_light_2_size2->setObjectName(QString::fromUtf8("label_single_trap_light_2_size2"));

        gridLayout_single_trap_light_2->addWidget(label_single_trap_light_2_size2, 2, 3, 1, 1);

        logedit_single_trap_light_2_size2 = new MyLineEdit(groupCheck_single_trap_light_2_enabled);
        logedit_single_trap_light_2_size2->setObjectName(QString::fromUtf8("logedit_single_trap_light_2_size2"));

        gridLayout_single_trap_light_2->addWidget(logedit_single_trap_light_2_size2, 2, 4, 1, 1);

        label_single_trap_light_2_thickness = new QLabel(groupCheck_single_trap_light_2_enabled);
        label_single_trap_light_2_thickness->setObjectName(QString::fromUtf8("label_single_trap_light_2_thickness"));

        gridLayout_single_trap_light_2->addWidget(label_single_trap_light_2_thickness, 3, 0, 1, 1);

        logedit_single_trap_light_2_thickness = new MyLineEdit(groupCheck_single_trap_light_2_enabled);
        logedit_single_trap_light_2_thickness->setObjectName(QString::fromUtf8("logedit_single_trap_light_2_thickness"));

        gridLayout_single_trap_light_2->addWidget(logedit_single_trap_light_2_thickness, 3, 1, 1, 2);

        label_single_trap_light_2_rotation = new QLabel(groupCheck_single_trap_light_2_enabled);
        label_single_trap_light_2_rotation->setObjectName(QString::fromUtf8("label_single_trap_light_2_rotation"));

        gridLayout_single_trap_light_2->addWidget(label_single_trap_light_2_rotation, 4, 0, 1, 1);

        spinboxd3_single_trap_light_2_rotation_x = new MyDoubleSpinBox(groupCheck_single_trap_light_2_enabled);
        spinboxd3_single_trap_light_2_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_2_rotation_x"));

        gridLayout_single_trap_light_2->addWidget(spinboxd3_single_trap_light_2_rotation_x, 4, 1, 1, 1);

        spinboxd3_single_trap_light_2_rotation_y = new MyDoubleSpinBox(groupCheck_single_trap_light_2_enabled);
        spinboxd3_single_trap_light_2_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_2_rotation_y"));

        gridLayout_single_trap_light_2->addWidget(spinboxd3_single_trap_light_2_rotation_y, 4, 2, 1, 1);

        spinboxd3_single_trap_light_2_rotation_z = new MyDoubleSpinBox(groupCheck_single_trap_light_2_enabled);
        spinboxd3_single_trap_light_2_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_2_rotation_z"));

        gridLayout_single_trap_light_2->addWidget(spinboxd3_single_trap_light_2_rotation_z, 4, 3, 1, 1);

        label_single_trap_light_2_intensity = new QLabel(groupCheck_single_trap_light_2_enabled);
        label_single_trap_light_2_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_2_intensity"));

        gridLayout_single_trap_light_2->addWidget(label_single_trap_light_2_intensity, 5, 0, 1, 1);

        logedit_single_trap_light_2_intensity = new MyLineEdit(groupCheck_single_trap_light_2_enabled);
        logedit_single_trap_light_2_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_2_intensity"));

        gridLayout_single_trap_light_2->addWidget(logedit_single_trap_light_2_intensity, 5, 1, 1, 2);

        label_single_trap_light_2_color = new QLabel(groupCheck_single_trap_light_2_enabled);
        label_single_trap_light_2_color->setObjectName(QString::fromUtf8("label_single_trap_light_2_color"));

        gridLayout_single_trap_light_2->addWidget(label_single_trap_light_2_color, 6, 0, 1, 1);

        colorButton_single_trap_light_2_color = new MyColorButton(groupCheck_single_trap_light_2_enabled);
        colorButton_single_trap_light_2_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_2_color"));

        gridLayout_single_trap_light_2->addWidget(colorButton_single_trap_light_2_color, 6, 1, 1, 1);

        label_single_trap_light_2_gradient_color = new QLabel(groupCheck_single_trap_light_2_enabled);
        label_single_trap_light_2_gradient_color->setObjectName(QString::fromUtf8("label_single_trap_light_2_gradient_color"));

        gridLayout_single_trap_light_2->addWidget(label_single_trap_light_2_gradient_color, 6, 2, 1, 1);

        colorButton_single_trap_light_2_gradient_color = new MyColorButton(groupCheck_single_trap_light_2_enabled);
        colorButton_single_trap_light_2_gradient_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_2_gradient_color"));

        gridLayout_single_trap_light_2->addWidget(colorButton_single_trap_light_2_gradient_color, 6, 3, 1, 2);

        label_single_trap_light_2_visibility = new QLabel(groupCheck_single_trap_light_2_enabled);
        label_single_trap_light_2_visibility->setObjectName(QString::fromUtf8("label_single_trap_light_2_visibility"));

        gridLayout_single_trap_light_2->addWidget(label_single_trap_light_2_visibility, 7, 0, 1, 1);

        logedit_single_trap_light_2_visibility = new MyLineEdit(groupCheck_single_trap_light_2_enabled);
        logedit_single_trap_light_2_visibility->setObjectName(QString::fromUtf8("logedit_single_trap_light_2_visibility"));

        gridLayout_single_trap_light_2->addWidget(logedit_single_trap_light_2_visibility, 7, 1, 1, 2);

        label_single_trap_light_2_max_distance = new QLabel(groupCheck_single_trap_light_2_enabled);
        label_single_trap_light_2_max_distance->setObjectName(QString::fromUtf8("label_single_trap_light_2_max_distance"));

        gridLayout_single_trap_light_2->addWidget(label_single_trap_light_2_max_distance, 7, 3, 1, 1);

        logedit_single_trap_light_2_max_distance = new MyLineEdit(groupCheck_single_trap_light_2_enabled);
        logedit_single_trap_light_2_max_distance->setObjectName(QString::fromUtf8("logedit_single_trap_light_2_max_distance"));

        gridLayout_single_trap_light_2->addWidget(logedit_single_trap_light_2_max_distance, 7, 4, 1, 1);

        label_single_trap_light_2_sharpening = new QLabel(groupCheck_single_trap_light_2_enabled);
        label_single_trap_light_2_sharpening->setObjectName(QString::fromUtf8("label_single_trap_light_2_sharpening"));

        gridLayout_single_trap_light_2->addWidget(label_single_trap_light_2_sharpening, 8, 0, 1, 1);

        logedit_single_trap_light_2_sharpening = new MyLineEdit(groupCheck_single_trap_light_2_enabled);
        logedit_single_trap_light_2_sharpening->setObjectName(QString::fromUtf8("logedit_single_trap_light_2_sharpening"));

        gridLayout_single_trap_light_2->addWidget(logedit_single_trap_light_2_sharpening, 8, 1, 1, 2);

        label_single_trap_light_2_blur = new QLabel(groupCheck_single_trap_light_2_enabled);
        label_single_trap_light_2_blur->setObjectName(QString::fromUtf8("label_single_trap_light_2_blur"));

        gridLayout_single_trap_light_2->addWidget(label_single_trap_light_2_blur, 8, 3, 1, 1);

        logedit_single_trap_light_2_blur = new MyLineEdit(groupCheck_single_trap_light_2_enabled);
        logedit_single_trap_light_2_blur->setObjectName(QString::fromUtf8("logedit_single_trap_light_2_blur"));

        gridLayout_single_trap_light_2->addWidget(logedit_single_trap_light_2_blur, 8, 4, 1, 1);

        label_single_trap_light_2_solid_intensity = new QLabel(groupCheck_single_trap_light_2_enabled);
        label_single_trap_light_2_solid_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_2_solid_intensity"));

        gridLayout_single_trap_light_2->addWidget(label_single_trap_light_2_solid_intensity, 9, 0, 1, 1);

        logedit_single_trap_light_2_solid_intensity = new MyLineEdit(groupCheck_single_trap_light_2_enabled);
        logedit_single_trap_light_2_solid_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_2_solid_intensity"));

        gridLayout_single_trap_light_2->addWidget(logedit_single_trap_light_2_solid_intensity, 9, 1, 1, 2);

        label_single_trap_light_2_softness = new QLabel(groupCheck_single_trap_light_2_enabled);
        label_single_trap_light_2_softness->setObjectName(QString::fromUtf8("label_single_trap_light_2_softness"));

        gridLayout_single_trap_light_2->addWidget(label_single_trap_light_2_softness, 9, 3, 1, 1);

        logedit_single_trap_light_2_softness = new MyLineEdit(groupCheck_single_trap_light_2_enabled);
        logedit_single_trap_light_2_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_2_softness"));

        gridLayout_single_trap_light_2->addWidget(logedit_single_trap_light_2_softness, 9, 4, 1, 1);

        label_single_trap_light_2_relative_size = new QLabel(groupCheck_single_trap_light_2_enabled);
        label_single_trap_light_2_relative_size->setObjectName(QString::fromUtf8("label_single_trap_light_2_relative_size"));

        gridLayout_single_trap_light_2->addWidget(label_single_trap_light_2_relative_size, 10, 0, 1, 1);

        logedit_single_trap_light_2_relative_size = new MyLineEdit(groupCheck_single_trap_light_2_enabled);
        logedit_single_trap_light_2_relative_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_2_relative_size"));

        gridLayout_single_trap_light_2->addWidget(logedit_single_trap_light_2_relative_size, 10, 1, 1, 2);

        checkBox_single_trap_light_2_pre_transformed = new MyCheckBox(groupCheck_single_trap_light_2_enabled);
        checkBox_single_trap_light_2_pre_transformed->setObjectName(QString::fromUtf8("checkBox_single_trap_light_2_pre_transformed"));

        gridLayout_single_trap_light_2->addWidget(checkBox_single_trap_light_2_pre_transformed, 11, 0, 1, 1);

        label_single_trap_light_2_position_mode = new QLabel(groupCheck_single_trap_light_2_enabled);
        label_single_trap_light_2_position_mode->setObjectName(QString::fromUtf8("label_single_trap_light_2_position_mode"));

        gridLayout_single_trap_light_2->addWidget(label_single_trap_light_2_position_mode, 12, 0, 1, 1);

        comboBox_single_trap_light_2_position_mode = new MyComboBox(groupCheck_single_trap_light_2_enabled);
        comboBox_single_trap_light_2_position_mode->addItem(QString());
        comboBox_single_trap_light_2_position_mode->addItem(QString());
        comboBox_single_trap_light_2_position_mode->addItem(QString());
        comboBox_single_trap_light_2_position_mode->addItem(QString());
        comboBox_single_trap_light_2_position_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_2_position_mode"));

        gridLayout_single_trap_light_2->addWidget(comboBox_single_trap_light_2_position_mode, 12, 1, 1, 2);

        label_single_trap_light_2_coloring_mode = new QLabel(groupCheck_single_trap_light_2_enabled);
        label_single_trap_light_2_coloring_mode->setObjectName(QString::fromUtf8("label_single_trap_light_2_coloring_mode"));

        gridLayout_single_trap_light_2->addWidget(label_single_trap_light_2_coloring_mode, 13, 0, 1, 1);

        comboBox_single_trap_light_2_coloring_mode = new MyComboBox(groupCheck_single_trap_light_2_enabled);
        comboBox_single_trap_light_2_coloring_mode->addItem(QString());
        comboBox_single_trap_light_2_coloring_mode->addItem(QString());
        comboBox_single_trap_light_2_coloring_mode->addItem(QString());
        comboBox_single_trap_light_2_coloring_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_2_coloring_mode"));

        gridLayout_single_trap_light_2->addWidget(comboBox_single_trap_light_2_coloring_mode, 13, 1, 1, 2);

        label_single_trap_light_2_falloff_type = new QLabel(groupCheck_single_trap_light_2_enabled);
        label_single_trap_light_2_falloff_type->setObjectName(QString::fromUtf8("label_single_trap_light_2_falloff_type"));

        gridLayout_single_trap_light_2->addWidget(label_single_trap_light_2_falloff_type, 14, 0, 1, 1);

        comboBox_single_trap_light_2_falloff_type = new MyComboBox(groupCheck_single_trap_light_2_enabled);
        comboBox_single_trap_light_2_falloff_type->addItem(QString());
        comboBox_single_trap_light_2_falloff_type->addItem(QString());
        comboBox_single_trap_light_2_falloff_type->addItem(QString());
        comboBox_single_trap_light_2_falloff_type->addItem(QString());
        comboBox_single_trap_light_2_falloff_type->addItem(QString());
        comboBox_single_trap_light_2_falloff_type->setObjectName(QString::fromUtf8("comboBox_single_trap_light_2_falloff_type"));

        gridLayout_single_trap_light_2->addWidget(comboBox_single_trap_light_2_falloff_type, 14, 1, 1, 2);

        label_single_trap_light_2_edge_softness = new QLabel(groupCheck_single_trap_light_2_enabled);
        label_single_trap_light_2_edge_softness->setObjectName(QString::fromUtf8("label_single_trap_light_2_edge_softness"));

        gridLayout_single_trap_light_2->addWidget(label_single_trap_light_2_edge_softness, 15, 0, 1, 1);

        logedit_single_trap_light_2_edge_softness = new MyLineEdit(groupCheck_single_trap_light_2_enabled);
        logedit_single_trap_light_2_edge_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_2_edge_softness"));

        gridLayout_single_trap_light_2->addWidget(logedit_single_trap_light_2_edge_softness, 15, 1, 1, 2);

        label_single_trap_light_2_anim_orbit_radius = new QLabel(groupCheck_single_trap_light_2_enabled);
        label_single_trap_light_2_anim_orbit_radius->setObjectName(QString::fromUtf8("label_single_trap_light_2_anim_orbit_radius"));

        gridLayout_single_trap_light_2->addWidget(label_single_trap_light_2_anim_orbit_radius, 16, 0, 1, 1);

        logedit_single_trap_light_2_anim_orbit_radius = new MyLineEdit(groupCheck_single_trap_light_2_enabled);
        logedit_single_trap_light_2_anim_orbit_radius->setObjectName(QString::fromUtf8("logedit_single_trap_light_2_anim_orbit_radius"));

        gridLayout_single_trap_light_2->addWidget(logedit_single_trap_light_2_anim_orbit_radius, 16, 1, 1, 1);

        logedit_single_trap_light_2_anim_orbit_speed = new MyLineEdit(groupCheck_single_trap_light_2_enabled);
        logedit_single_trap_light_2_anim_orbit_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_2_anim_orbit_speed"));

        gridLayout_single_trap_light_2->addWidget(logedit_single_trap_light_2_anim_orbit_speed, 16, 2, 1, 1);

        logedit_single_trap_light_2_anim_pulsate_speed = new MyLineEdit(groupCheck_single_trap_light_2_enabled);
        logedit_single_trap_light_2_anim_pulsate_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_2_anim_pulsate_speed"));

        gridLayout_single_trap_light_2->addWidget(logedit_single_trap_light_2_anim_pulsate_speed, 16, 3, 1, 1);

        logedit_single_trap_light_2_anim_pulsate_amount = new MyLineEdit(groupCheck_single_trap_light_2_enabled);
        logedit_single_trap_light_2_anim_pulsate_amount->setObjectName(QString::fromUtf8("logedit_single_trap_light_2_anim_pulsate_amount"));

        gridLayout_single_trap_light_2->addWidget(logedit_single_trap_light_2_anim_pulsate_amount, 16, 4, 1, 1);

        pushButton_single_trap_light_2_place_surface = new QPushButton(groupCheck_single_trap_light_2_enabled);
        pushButton_single_trap_light_2_place_surface->setObjectName(QString::fromUtf8("pushButton_single_trap_light_2_place_surface"));

        gridLayout_single_trap_light_2->addWidget(pushButton_single_trap_light_2_place_surface, 17, 0, 1, 5);

        pushButton_single_trap_light_2_place_target = new QPushButton(groupCheck_single_trap_light_2_enabled);
        pushButton_single_trap_light_2_place_target->setObjectName(QString::fromUtf8("pushButton_single_trap_light_2_place_target"));

        gridLayout_single_trap_light_2->addWidget(pushButton_single_trap_light_2_place_target, 18, 0, 1, 5);


        verticalLayout_single_trap_layers->addWidget(groupCheck_single_trap_light_2_enabled);

        groupCheck_single_trap_light_3_enabled = new MyGroupBox(scrollAreaWidgetContents_single_trap);
        groupCheck_single_trap_light_3_enabled->setObjectName(QString::fromUtf8("groupCheck_single_trap_light_3_enabled"));
        groupCheck_single_trap_light_3_enabled->setCheckable(true);
        gridLayout_single_trap_light_3 = new QGridLayout(groupCheck_single_trap_light_3_enabled);
        gridLayout_single_trap_light_3->setSpacing(2);
        gridLayout_single_trap_light_3->setObjectName(QString::fromUtf8("gridLayout_single_trap_light_3"));
        label_single_trap_light_3_shape = new QLabel(groupCheck_single_trap_light_3_enabled);
        label_single_trap_light_3_shape->setObjectName(QString::fromUtf8("label_single_trap_light_3_shape"));

        gridLayout_single_trap_light_3->addWidget(label_single_trap_light_3_shape, 0, 0, 1, 1);

        comboBox_single_trap_light_3_shape = new MyComboBox(groupCheck_single_trap_light_3_enabled);
        comboBox_single_trap_light_3_shape->addItem(QString());
        comboBox_single_trap_light_3_shape->addItem(QString());
        comboBox_single_trap_light_3_shape->addItem(QString());
        comboBox_single_trap_light_3_shape->addItem(QString());
        comboBox_single_trap_light_3_shape->addItem(QString());
        comboBox_single_trap_light_3_shape->addItem(QString());
        comboBox_single_trap_light_3_shape->addItem(QString());
        comboBox_single_trap_light_3_shape->addItem(QString());
        comboBox_single_trap_light_3_shape->addItem(QString());
        comboBox_single_trap_light_3_shape->addItem(QString());
        comboBox_single_trap_light_3_shape->addItem(QString());
        comboBox_single_trap_light_3_shape->addItem(QString());
        comboBox_single_trap_light_3_shape->addItem(QString());
        comboBox_single_trap_light_3_shape->addItem(QString());
        comboBox_single_trap_light_3_shape->setObjectName(QString::fromUtf8("comboBox_single_trap_light_3_shape"));

        gridLayout_single_trap_light_3->addWidget(comboBox_single_trap_light_3_shape, 0, 1, 1, 2);

        label_single_trap_light_3_position = new QLabel(groupCheck_single_trap_light_3_enabled);
        label_single_trap_light_3_position->setObjectName(QString::fromUtf8("label_single_trap_light_3_position"));

        gridLayout_single_trap_light_3->addWidget(label_single_trap_light_3_position, 1, 0, 1, 1);

        vect3_single_trap_light_3_position_x = new MyLineEdit(groupCheck_single_trap_light_3_enabled);
        vect3_single_trap_light_3_position_x->setObjectName(QString::fromUtf8("vect3_single_trap_light_3_position_x"));

        gridLayout_single_trap_light_3->addWidget(vect3_single_trap_light_3_position_x, 1, 1, 1, 1);

        vect3_single_trap_light_3_position_y = new MyLineEdit(groupCheck_single_trap_light_3_enabled);
        vect3_single_trap_light_3_position_y->setObjectName(QString::fromUtf8("vect3_single_trap_light_3_position_y"));

        gridLayout_single_trap_light_3->addWidget(vect3_single_trap_light_3_position_y, 1, 2, 1, 1);

        vect3_single_trap_light_3_position_z = new MyLineEdit(groupCheck_single_trap_light_3_enabled);
        vect3_single_trap_light_3_position_z->setObjectName(QString::fromUtf8("vect3_single_trap_light_3_position_z"));

        gridLayout_single_trap_light_3->addWidget(vect3_single_trap_light_3_position_z, 1, 3, 1, 1);

        pushButton_single_trap_light_3_place_camera = new QPushButton(groupCheck_single_trap_light_3_enabled);
        pushButton_single_trap_light_3_place_camera->setObjectName(QString::fromUtf8("pushButton_single_trap_light_3_place_camera"));

        gridLayout_single_trap_light_3->addWidget(pushButton_single_trap_light_3_place_camera, 1, 4, 1, 1);

        label_single_trap_light_3_size = new QLabel(groupCheck_single_trap_light_3_enabled);
        label_single_trap_light_3_size->setObjectName(QString::fromUtf8("label_single_trap_light_3_size"));

        gridLayout_single_trap_light_3->addWidget(label_single_trap_light_3_size, 2, 0, 1, 1);

        logedit_single_trap_light_3_size = new MyLineEdit(groupCheck_single_trap_light_3_enabled);
        logedit_single_trap_light_3_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_3_size"));

        gridLayout_single_trap_light_3->addWidget(logedit_single_trap_light_3_size, 2, 1, 1, 2);

        label_single_trap_light_3_size2 = new QLabel(groupCheck_single_trap_light_3_enabled);
        label_single_trap_light_3_size2->setObjectName(QString::fromUtf8("label_single_trap_light_3_size2"));

        gridLayout_single_trap_light_3->addWidget(label_single_trap_light_3_size2, 2, 3, 1, 1);

        logedit_single_trap_light_3_size2 = new MyLineEdit(groupCheck_single_trap_light_3_enabled);
        logedit_single_trap_light_3_size2->setObjectName(QString::fromUtf8("logedit_single_trap_light_3_size2"));

        gridLayout_single_trap_light_3->addWidget(logedit_single_trap_light_3_size2, 2, 4, 1, 1);

        label_single_trap_light_3_thickness = new QLabel(groupCheck_single_trap_light_3_enabled);
        label_single_trap_light_3_thickness->setObjectName(QString::fromUtf8("label_single_trap_light_3_thickness"));

        gridLayout_single_trap_light_3->addWidget(label_single_trap_light_3_thickness, 3, 0, 1, 1);

        logedit_single_trap_light_3_thickness = new MyLineEdit(groupCheck_single_trap_light_3_enabled);
        logedit_single_trap_light_3_thickness->setObjectName(QString::fromUtf8("logedit_single_trap_light_3_thickness"));

        gridLayout_single_trap_light_3->addWidget(logedit_single_trap_light_3_thickness, 3, 1, 1, 2);

        label_single_trap_light_3_rotation = new QLabel(groupCheck_single_trap_light_3_enabled);
        label_single_trap_light_3_rotation->setObjectName(QString::fromUtf8("label_single_trap_light_3_rotation"));

        gridLayout_single_trap_light_3->addWidget(label_single_trap_light_3_rotation, 4, 0, 1, 1);

        spinboxd3_single_trap_light_3_rotation_x = new MyDoubleSpinBox(groupCheck_single_trap_light_3_enabled);
        spinboxd3_single_trap_light_3_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_3_rotation_x"));

        gridLayout_single_trap_light_3->addWidget(spinboxd3_single_trap_light_3_rotation_x, 4, 1, 1, 1);

        spinboxd3_single_trap_light_3_rotation_y = new MyDoubleSpinBox(groupCheck_single_trap_light_3_enabled);
        spinboxd3_single_trap_light_3_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_3_rotation_y"));

        gridLayout_single_trap_light_3->addWidget(spinboxd3_single_trap_light_3_rotation_y, 4, 2, 1, 1);

        spinboxd3_single_trap_light_3_rotation_z = new MyDoubleSpinBox(groupCheck_single_trap_light_3_enabled);
        spinboxd3_single_trap_light_3_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_3_rotation_z"));

        gridLayout_single_trap_light_3->addWidget(spinboxd3_single_trap_light_3_rotation_z, 4, 3, 1, 1);

        label_single_trap_light_3_intensity = new QLabel(groupCheck_single_trap_light_3_enabled);
        label_single_trap_light_3_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_3_intensity"));

        gridLayout_single_trap_light_3->addWidget(label_single_trap_light_3_intensity, 5, 0, 1, 1);

        logedit_single_trap_light_3_intensity = new MyLineEdit(groupCheck_single_trap_light_3_enabled);
        logedit_single_trap_light_3_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_3_intensity"));

        gridLayout_single_trap_light_3->addWidget(logedit_single_trap_light_3_intensity, 5, 1, 1, 2);

        label_single_trap_light_3_color = new QLabel(groupCheck_single_trap_light_3_enabled);
        label_single_trap_light_3_color->setObjectName(QString::fromUtf8("label_single_trap_light_3_color"));

        gridLayout_single_trap_light_3->addWidget(label_single_trap_light_3_color, 6, 0, 1, 1);

        colorButton_single_trap_light_3_color = new MyColorButton(groupCheck_single_trap_light_3_enabled);
        colorButton_single_trap_light_3_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_3_color"));

        gridLayout_single_trap_light_3->addWidget(colorButton_single_trap_light_3_color, 6, 1, 1, 1);

        label_single_trap_light_3_gradient_color = new QLabel(groupCheck_single_trap_light_3_enabled);
        label_single_trap_light_3_gradient_color->setObjectName(QString::fromUtf8("label_single_trap_light_3_gradient_color"));

        gridLayout_single_trap_light_3->addWidget(label_single_trap_light_3_gradient_color, 6, 2, 1, 1);

        colorButton_single_trap_light_3_gradient_color = new MyColorButton(groupCheck_single_trap_light_3_enabled);
        colorButton_single_trap_light_3_gradient_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_3_gradient_color"));

        gridLayout_single_trap_light_3->addWidget(colorButton_single_trap_light_3_gradient_color, 6, 3, 1, 2);

        label_single_trap_light_3_visibility = new QLabel(groupCheck_single_trap_light_3_enabled);
        label_single_trap_light_3_visibility->setObjectName(QString::fromUtf8("label_single_trap_light_3_visibility"));

        gridLayout_single_trap_light_3->addWidget(label_single_trap_light_3_visibility, 7, 0, 1, 1);

        logedit_single_trap_light_3_visibility = new MyLineEdit(groupCheck_single_trap_light_3_enabled);
        logedit_single_trap_light_3_visibility->setObjectName(QString::fromUtf8("logedit_single_trap_light_3_visibility"));

        gridLayout_single_trap_light_3->addWidget(logedit_single_trap_light_3_visibility, 7, 1, 1, 2);

        label_single_trap_light_3_max_distance = new QLabel(groupCheck_single_trap_light_3_enabled);
        label_single_trap_light_3_max_distance->setObjectName(QString::fromUtf8("label_single_trap_light_3_max_distance"));

        gridLayout_single_trap_light_3->addWidget(label_single_trap_light_3_max_distance, 7, 3, 1, 1);

        logedit_single_trap_light_3_max_distance = new MyLineEdit(groupCheck_single_trap_light_3_enabled);
        logedit_single_trap_light_3_max_distance->setObjectName(QString::fromUtf8("logedit_single_trap_light_3_max_distance"));

        gridLayout_single_trap_light_3->addWidget(logedit_single_trap_light_3_max_distance, 7, 4, 1, 1);

        label_single_trap_light_3_sharpening = new QLabel(groupCheck_single_trap_light_3_enabled);
        label_single_trap_light_3_sharpening->setObjectName(QString::fromUtf8("label_single_trap_light_3_sharpening"));

        gridLayout_single_trap_light_3->addWidget(label_single_trap_light_3_sharpening, 8, 0, 1, 1);

        logedit_single_trap_light_3_sharpening = new MyLineEdit(groupCheck_single_trap_light_3_enabled);
        logedit_single_trap_light_3_sharpening->setObjectName(QString::fromUtf8("logedit_single_trap_light_3_sharpening"));

        gridLayout_single_trap_light_3->addWidget(logedit_single_trap_light_3_sharpening, 8, 1, 1, 2);

        label_single_trap_light_3_blur = new QLabel(groupCheck_single_trap_light_3_enabled);
        label_single_trap_light_3_blur->setObjectName(QString::fromUtf8("label_single_trap_light_3_blur"));

        gridLayout_single_trap_light_3->addWidget(label_single_trap_light_3_blur, 8, 3, 1, 1);

        logedit_single_trap_light_3_blur = new MyLineEdit(groupCheck_single_trap_light_3_enabled);
        logedit_single_trap_light_3_blur->setObjectName(QString::fromUtf8("logedit_single_trap_light_3_blur"));

        gridLayout_single_trap_light_3->addWidget(logedit_single_trap_light_3_blur, 8, 4, 1, 1);

        label_single_trap_light_3_solid_intensity = new QLabel(groupCheck_single_trap_light_3_enabled);
        label_single_trap_light_3_solid_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_3_solid_intensity"));

        gridLayout_single_trap_light_3->addWidget(label_single_trap_light_3_solid_intensity, 9, 0, 1, 1);

        logedit_single_trap_light_3_solid_intensity = new MyLineEdit(groupCheck_single_trap_light_3_enabled);
        logedit_single_trap_light_3_solid_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_3_solid_intensity"));

        gridLayout_single_trap_light_3->addWidget(logedit_single_trap_light_3_solid_intensity, 9, 1, 1, 2);

        label_single_trap_light_3_softness = new QLabel(groupCheck_single_trap_light_3_enabled);
        label_single_trap_light_3_softness->setObjectName(QString::fromUtf8("label_single_trap_light_3_softness"));

        gridLayout_single_trap_light_3->addWidget(label_single_trap_light_3_softness, 9, 3, 1, 1);

        logedit_single_trap_light_3_softness = new MyLineEdit(groupCheck_single_trap_light_3_enabled);
        logedit_single_trap_light_3_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_3_softness"));

        gridLayout_single_trap_light_3->addWidget(logedit_single_trap_light_3_softness, 9, 4, 1, 1);

        label_single_trap_light_3_relative_size = new QLabel(groupCheck_single_trap_light_3_enabled);
        label_single_trap_light_3_relative_size->setObjectName(QString::fromUtf8("label_single_trap_light_3_relative_size"));

        gridLayout_single_trap_light_3->addWidget(label_single_trap_light_3_relative_size, 10, 0, 1, 1);

        logedit_single_trap_light_3_relative_size = new MyLineEdit(groupCheck_single_trap_light_3_enabled);
        logedit_single_trap_light_3_relative_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_3_relative_size"));

        gridLayout_single_trap_light_3->addWidget(logedit_single_trap_light_3_relative_size, 10, 1, 1, 2);

        checkBox_single_trap_light_3_pre_transformed = new MyCheckBox(groupCheck_single_trap_light_3_enabled);
        checkBox_single_trap_light_3_pre_transformed->setObjectName(QString::fromUtf8("checkBox_single_trap_light_3_pre_transformed"));

        gridLayout_single_trap_light_3->addWidget(checkBox_single_trap_light_3_pre_transformed, 11, 0, 1, 1);

        label_single_trap_light_3_position_mode = new QLabel(groupCheck_single_trap_light_3_enabled);
        label_single_trap_light_3_position_mode->setObjectName(QString::fromUtf8("label_single_trap_light_3_position_mode"));

        gridLayout_single_trap_light_3->addWidget(label_single_trap_light_3_position_mode, 12, 0, 1, 1);

        comboBox_single_trap_light_3_position_mode = new MyComboBox(groupCheck_single_trap_light_3_enabled);
        comboBox_single_trap_light_3_position_mode->addItem(QString());
        comboBox_single_trap_light_3_position_mode->addItem(QString());
        comboBox_single_trap_light_3_position_mode->addItem(QString());
        comboBox_single_trap_light_3_position_mode->addItem(QString());
        comboBox_single_trap_light_3_position_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_3_position_mode"));

        gridLayout_single_trap_light_3->addWidget(comboBox_single_trap_light_3_position_mode, 12, 1, 1, 2);

        label_single_trap_light_3_coloring_mode = new QLabel(groupCheck_single_trap_light_3_enabled);
        label_single_trap_light_3_coloring_mode->setObjectName(QString::fromUtf8("label_single_trap_light_3_coloring_mode"));

        gridLayout_single_trap_light_3->addWidget(label_single_trap_light_3_coloring_mode, 13, 0, 1, 1);

        comboBox_single_trap_light_3_coloring_mode = new MyComboBox(groupCheck_single_trap_light_3_enabled);
        comboBox_single_trap_light_3_coloring_mode->addItem(QString());
        comboBox_single_trap_light_3_coloring_mode->addItem(QString());
        comboBox_single_trap_light_3_coloring_mode->addItem(QString());
        comboBox_single_trap_light_3_coloring_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_3_coloring_mode"));

        gridLayout_single_trap_light_3->addWidget(comboBox_single_trap_light_3_coloring_mode, 13, 1, 1, 2);

        label_single_trap_light_3_falloff_type = new QLabel(groupCheck_single_trap_light_3_enabled);
        label_single_trap_light_3_falloff_type->setObjectName(QString::fromUtf8("label_single_trap_light_3_falloff_type"));

        gridLayout_single_trap_light_3->addWidget(label_single_trap_light_3_falloff_type, 14, 0, 1, 1);

        comboBox_single_trap_light_3_falloff_type = new MyComboBox(groupCheck_single_trap_light_3_enabled);
        comboBox_single_trap_light_3_falloff_type->addItem(QString());
        comboBox_single_trap_light_3_falloff_type->addItem(QString());
        comboBox_single_trap_light_3_falloff_type->addItem(QString());
        comboBox_single_trap_light_3_falloff_type->addItem(QString());
        comboBox_single_trap_light_3_falloff_type->addItem(QString());
        comboBox_single_trap_light_3_falloff_type->setObjectName(QString::fromUtf8("comboBox_single_trap_light_3_falloff_type"));

        gridLayout_single_trap_light_3->addWidget(comboBox_single_trap_light_3_falloff_type, 14, 1, 1, 2);

        label_single_trap_light_3_edge_softness = new QLabel(groupCheck_single_trap_light_3_enabled);
        label_single_trap_light_3_edge_softness->setObjectName(QString::fromUtf8("label_single_trap_light_3_edge_softness"));

        gridLayout_single_trap_light_3->addWidget(label_single_trap_light_3_edge_softness, 15, 0, 1, 1);

        logedit_single_trap_light_3_edge_softness = new MyLineEdit(groupCheck_single_trap_light_3_enabled);
        logedit_single_trap_light_3_edge_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_3_edge_softness"));

        gridLayout_single_trap_light_3->addWidget(logedit_single_trap_light_3_edge_softness, 15, 1, 1, 2);

        label_single_trap_light_3_anim_orbit_radius = new QLabel(groupCheck_single_trap_light_3_enabled);
        label_single_trap_light_3_anim_orbit_radius->setObjectName(QString::fromUtf8("label_single_trap_light_3_anim_orbit_radius"));

        gridLayout_single_trap_light_3->addWidget(label_single_trap_light_3_anim_orbit_radius, 16, 0, 1, 1);

        logedit_single_trap_light_3_anim_orbit_radius = new MyLineEdit(groupCheck_single_trap_light_3_enabled);
        logedit_single_trap_light_3_anim_orbit_radius->setObjectName(QString::fromUtf8("logedit_single_trap_light_3_anim_orbit_radius"));

        gridLayout_single_trap_light_3->addWidget(logedit_single_trap_light_3_anim_orbit_radius, 16, 1, 1, 1);

        logedit_single_trap_light_3_anim_orbit_speed = new MyLineEdit(groupCheck_single_trap_light_3_enabled);
        logedit_single_trap_light_3_anim_orbit_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_3_anim_orbit_speed"));

        gridLayout_single_trap_light_3->addWidget(logedit_single_trap_light_3_anim_orbit_speed, 16, 2, 1, 1);

        logedit_single_trap_light_3_anim_pulsate_speed = new MyLineEdit(groupCheck_single_trap_light_3_enabled);
        logedit_single_trap_light_3_anim_pulsate_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_3_anim_pulsate_speed"));

        gridLayout_single_trap_light_3->addWidget(logedit_single_trap_light_3_anim_pulsate_speed, 16, 3, 1, 1);

        logedit_single_trap_light_3_anim_pulsate_amount = new MyLineEdit(groupCheck_single_trap_light_3_enabled);
        logedit_single_trap_light_3_anim_pulsate_amount->setObjectName(QString::fromUtf8("logedit_single_trap_light_3_anim_pulsate_amount"));

        gridLayout_single_trap_light_3->addWidget(logedit_single_trap_light_3_anim_pulsate_amount, 16, 4, 1, 1);

        pushButton_single_trap_light_3_place_surface = new QPushButton(groupCheck_single_trap_light_3_enabled);
        pushButton_single_trap_light_3_place_surface->setObjectName(QString::fromUtf8("pushButton_single_trap_light_3_place_surface"));

        gridLayout_single_trap_light_3->addWidget(pushButton_single_trap_light_3_place_surface, 17, 0, 1, 5);

        pushButton_single_trap_light_3_place_target = new QPushButton(groupCheck_single_trap_light_3_enabled);
        pushButton_single_trap_light_3_place_target->setObjectName(QString::fromUtf8("pushButton_single_trap_light_3_place_target"));

        gridLayout_single_trap_light_3->addWidget(pushButton_single_trap_light_3_place_target, 18, 0, 1, 5);


        verticalLayout_single_trap_layers->addWidget(groupCheck_single_trap_light_3_enabled);

        groupCheck_single_trap_light_4_enabled = new MyGroupBox(scrollAreaWidgetContents_single_trap);
        groupCheck_single_trap_light_4_enabled->setObjectName(QString::fromUtf8("groupCheck_single_trap_light_4_enabled"));
        groupCheck_single_trap_light_4_enabled->setCheckable(true);
        gridLayout_single_trap_light_4 = new QGridLayout(groupCheck_single_trap_light_4_enabled);
        gridLayout_single_trap_light_4->setSpacing(2);
        gridLayout_single_trap_light_4->setObjectName(QString::fromUtf8("gridLayout_single_trap_light_4"));
        label_single_trap_light_4_shape = new QLabel(groupCheck_single_trap_light_4_enabled);
        label_single_trap_light_4_shape->setObjectName(QString::fromUtf8("label_single_trap_light_4_shape"));

        gridLayout_single_trap_light_4->addWidget(label_single_trap_light_4_shape, 0, 0, 1, 1);

        comboBox_single_trap_light_4_shape = new MyComboBox(groupCheck_single_trap_light_4_enabled);
        comboBox_single_trap_light_4_shape->addItem(QString());
        comboBox_single_trap_light_4_shape->addItem(QString());
        comboBox_single_trap_light_4_shape->addItem(QString());
        comboBox_single_trap_light_4_shape->addItem(QString());
        comboBox_single_trap_light_4_shape->addItem(QString());
        comboBox_single_trap_light_4_shape->addItem(QString());
        comboBox_single_trap_light_4_shape->addItem(QString());
        comboBox_single_trap_light_4_shape->addItem(QString());
        comboBox_single_trap_light_4_shape->addItem(QString());
        comboBox_single_trap_light_4_shape->addItem(QString());
        comboBox_single_trap_light_4_shape->addItem(QString());
        comboBox_single_trap_light_4_shape->addItem(QString());
        comboBox_single_trap_light_4_shape->addItem(QString());
        comboBox_single_trap_light_4_shape->addItem(QString());
        comboBox_single_trap_light_4_shape->setObjectName(QString::fromUtf8("comboBox_single_trap_light_4_shape"));

        gridLayout_single_trap_light_4->addWidget(comboBox_single_trap_light_4_shape, 0, 1, 1, 2);

        label_single_trap_light_4_position = new QLabel(groupCheck_single_trap_light_4_enabled);
        label_single_trap_light_4_position->setObjectName(QString::fromUtf8("label_single_trap_light_4_position"));

        gridLayout_single_trap_light_4->addWidget(label_single_trap_light_4_position, 1, 0, 1, 1);

        vect3_single_trap_light_4_position_x = new MyLineEdit(groupCheck_single_trap_light_4_enabled);
        vect3_single_trap_light_4_position_x->setObjectName(QString::fromUtf8("vect3_single_trap_light_4_position_x"));

        gridLayout_single_trap_light_4->addWidget(vect3_single_trap_light_4_position_x, 1, 1, 1, 1);

        vect3_single_trap_light_4_position_y = new MyLineEdit(groupCheck_single_trap_light_4_enabled);
        vect3_single_trap_light_4_position_y->setObjectName(QString::fromUtf8("vect3_single_trap_light_4_position_y"));

        gridLayout_single_trap_light_4->addWidget(vect3_single_trap_light_4_position_y, 1, 2, 1, 1);

        vect3_single_trap_light_4_position_z = new MyLineEdit(groupCheck_single_trap_light_4_enabled);
        vect3_single_trap_light_4_position_z->setObjectName(QString::fromUtf8("vect3_single_trap_light_4_position_z"));

        gridLayout_single_trap_light_4->addWidget(vect3_single_trap_light_4_position_z, 1, 3, 1, 1);

        pushButton_single_trap_light_4_place_camera = new QPushButton(groupCheck_single_trap_light_4_enabled);
        pushButton_single_trap_light_4_place_camera->setObjectName(QString::fromUtf8("pushButton_single_trap_light_4_place_camera"));

        gridLayout_single_trap_light_4->addWidget(pushButton_single_trap_light_4_place_camera, 1, 4, 1, 1);

        label_single_trap_light_4_size = new QLabel(groupCheck_single_trap_light_4_enabled);
        label_single_trap_light_4_size->setObjectName(QString::fromUtf8("label_single_trap_light_4_size"));

        gridLayout_single_trap_light_4->addWidget(label_single_trap_light_4_size, 2, 0, 1, 1);

        logedit_single_trap_light_4_size = new MyLineEdit(groupCheck_single_trap_light_4_enabled);
        logedit_single_trap_light_4_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_4_size"));

        gridLayout_single_trap_light_4->addWidget(logedit_single_trap_light_4_size, 2, 1, 1, 2);

        label_single_trap_light_4_size2 = new QLabel(groupCheck_single_trap_light_4_enabled);
        label_single_trap_light_4_size2->setObjectName(QString::fromUtf8("label_single_trap_light_4_size2"));

        gridLayout_single_trap_light_4->addWidget(label_single_trap_light_4_size2, 2, 3, 1, 1);

        logedit_single_trap_light_4_size2 = new MyLineEdit(groupCheck_single_trap_light_4_enabled);
        logedit_single_trap_light_4_size2->setObjectName(QString::fromUtf8("logedit_single_trap_light_4_size2"));

        gridLayout_single_trap_light_4->addWidget(logedit_single_trap_light_4_size2, 2, 4, 1, 1);

        label_single_trap_light_4_thickness = new QLabel(groupCheck_single_trap_light_4_enabled);
        label_single_trap_light_4_thickness->setObjectName(QString::fromUtf8("label_single_trap_light_4_thickness"));

        gridLayout_single_trap_light_4->addWidget(label_single_trap_light_4_thickness, 3, 0, 1, 1);

        logedit_single_trap_light_4_thickness = new MyLineEdit(groupCheck_single_trap_light_4_enabled);
        logedit_single_trap_light_4_thickness->setObjectName(QString::fromUtf8("logedit_single_trap_light_4_thickness"));

        gridLayout_single_trap_light_4->addWidget(logedit_single_trap_light_4_thickness, 3, 1, 1, 2);

        label_single_trap_light_4_rotation = new QLabel(groupCheck_single_trap_light_4_enabled);
        label_single_trap_light_4_rotation->setObjectName(QString::fromUtf8("label_single_trap_light_4_rotation"));

        gridLayout_single_trap_light_4->addWidget(label_single_trap_light_4_rotation, 4, 0, 1, 1);

        spinboxd3_single_trap_light_4_rotation_x = new MyDoubleSpinBox(groupCheck_single_trap_light_4_enabled);
        spinboxd3_single_trap_light_4_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_4_rotation_x"));

        gridLayout_single_trap_light_4->addWidget(spinboxd3_single_trap_light_4_rotation_x, 4, 1, 1, 1);

        spinboxd3_single_trap_light_4_rotation_y = new MyDoubleSpinBox(groupCheck_single_trap_light_4_enabled);
        spinboxd3_single_trap_light_4_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_4_rotation_y"));

        gridLayout_single_trap_light_4->addWidget(spinboxd3_single_trap_light_4_rotation_y, 4, 2, 1, 1);

        spinboxd3_single_trap_light_4_rotation_z = new MyDoubleSpinBox(groupCheck_single_trap_light_4_enabled);
        spinboxd3_single_trap_light_4_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_4_rotation_z"));

        gridLayout_single_trap_light_4->addWidget(spinboxd3_single_trap_light_4_rotation_z, 4, 3, 1, 1);

        label_single_trap_light_4_intensity = new QLabel(groupCheck_single_trap_light_4_enabled);
        label_single_trap_light_4_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_4_intensity"));

        gridLayout_single_trap_light_4->addWidget(label_single_trap_light_4_intensity, 5, 0, 1, 1);

        logedit_single_trap_light_4_intensity = new MyLineEdit(groupCheck_single_trap_light_4_enabled);
        logedit_single_trap_light_4_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_4_intensity"));

        gridLayout_single_trap_light_4->addWidget(logedit_single_trap_light_4_intensity, 5, 1, 1, 2);

        label_single_trap_light_4_color = new QLabel(groupCheck_single_trap_light_4_enabled);
        label_single_trap_light_4_color->setObjectName(QString::fromUtf8("label_single_trap_light_4_color"));

        gridLayout_single_trap_light_4->addWidget(label_single_trap_light_4_color, 6, 0, 1, 1);

        colorButton_single_trap_light_4_color = new MyColorButton(groupCheck_single_trap_light_4_enabled);
        colorButton_single_trap_light_4_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_4_color"));

        gridLayout_single_trap_light_4->addWidget(colorButton_single_trap_light_4_color, 6, 1, 1, 1);

        label_single_trap_light_4_gradient_color = new QLabel(groupCheck_single_trap_light_4_enabled);
        label_single_trap_light_4_gradient_color->setObjectName(QString::fromUtf8("label_single_trap_light_4_gradient_color"));

        gridLayout_single_trap_light_4->addWidget(label_single_trap_light_4_gradient_color, 6, 2, 1, 1);

        colorButton_single_trap_light_4_gradient_color = new MyColorButton(groupCheck_single_trap_light_4_enabled);
        colorButton_single_trap_light_4_gradient_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_4_gradient_color"));

        gridLayout_single_trap_light_4->addWidget(colorButton_single_trap_light_4_gradient_color, 6, 3, 1, 2);

        label_single_trap_light_4_visibility = new QLabel(groupCheck_single_trap_light_4_enabled);
        label_single_trap_light_4_visibility->setObjectName(QString::fromUtf8("label_single_trap_light_4_visibility"));

        gridLayout_single_trap_light_4->addWidget(label_single_trap_light_4_visibility, 7, 0, 1, 1);

        logedit_single_trap_light_4_visibility = new MyLineEdit(groupCheck_single_trap_light_4_enabled);
        logedit_single_trap_light_4_visibility->setObjectName(QString::fromUtf8("logedit_single_trap_light_4_visibility"));

        gridLayout_single_trap_light_4->addWidget(logedit_single_trap_light_4_visibility, 7, 1, 1, 2);

        label_single_trap_light_4_max_distance = new QLabel(groupCheck_single_trap_light_4_enabled);
        label_single_trap_light_4_max_distance->setObjectName(QString::fromUtf8("label_single_trap_light_4_max_distance"));

        gridLayout_single_trap_light_4->addWidget(label_single_trap_light_4_max_distance, 7, 3, 1, 1);

        logedit_single_trap_light_4_max_distance = new MyLineEdit(groupCheck_single_trap_light_4_enabled);
        logedit_single_trap_light_4_max_distance->setObjectName(QString::fromUtf8("logedit_single_trap_light_4_max_distance"));

        gridLayout_single_trap_light_4->addWidget(logedit_single_trap_light_4_max_distance, 7, 4, 1, 1);

        label_single_trap_light_4_sharpening = new QLabel(groupCheck_single_trap_light_4_enabled);
        label_single_trap_light_4_sharpening->setObjectName(QString::fromUtf8("label_single_trap_light_4_sharpening"));

        gridLayout_single_trap_light_4->addWidget(label_single_trap_light_4_sharpening, 8, 0, 1, 1);

        logedit_single_trap_light_4_sharpening = new MyLineEdit(groupCheck_single_trap_light_4_enabled);
        logedit_single_trap_light_4_sharpening->setObjectName(QString::fromUtf8("logedit_single_trap_light_4_sharpening"));

        gridLayout_single_trap_light_4->addWidget(logedit_single_trap_light_4_sharpening, 8, 1, 1, 2);

        label_single_trap_light_4_blur = new QLabel(groupCheck_single_trap_light_4_enabled);
        label_single_trap_light_4_blur->setObjectName(QString::fromUtf8("label_single_trap_light_4_blur"));

        gridLayout_single_trap_light_4->addWidget(label_single_trap_light_4_blur, 8, 3, 1, 1);

        logedit_single_trap_light_4_blur = new MyLineEdit(groupCheck_single_trap_light_4_enabled);
        logedit_single_trap_light_4_blur->setObjectName(QString::fromUtf8("logedit_single_trap_light_4_blur"));

        gridLayout_single_trap_light_4->addWidget(logedit_single_trap_light_4_blur, 8, 4, 1, 1);

        label_single_trap_light_4_solid_intensity = new QLabel(groupCheck_single_trap_light_4_enabled);
        label_single_trap_light_4_solid_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_4_solid_intensity"));

        gridLayout_single_trap_light_4->addWidget(label_single_trap_light_4_solid_intensity, 9, 0, 1, 1);

        logedit_single_trap_light_4_solid_intensity = new MyLineEdit(groupCheck_single_trap_light_4_enabled);
        logedit_single_trap_light_4_solid_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_4_solid_intensity"));

        gridLayout_single_trap_light_4->addWidget(logedit_single_trap_light_4_solid_intensity, 9, 1, 1, 2);

        label_single_trap_light_4_softness = new QLabel(groupCheck_single_trap_light_4_enabled);
        label_single_trap_light_4_softness->setObjectName(QString::fromUtf8("label_single_trap_light_4_softness"));

        gridLayout_single_trap_light_4->addWidget(label_single_trap_light_4_softness, 9, 3, 1, 1);

        logedit_single_trap_light_4_softness = new MyLineEdit(groupCheck_single_trap_light_4_enabled);
        logedit_single_trap_light_4_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_4_softness"));

        gridLayout_single_trap_light_4->addWidget(logedit_single_trap_light_4_softness, 9, 4, 1, 1);

        label_single_trap_light_4_relative_size = new QLabel(groupCheck_single_trap_light_4_enabled);
        label_single_trap_light_4_relative_size->setObjectName(QString::fromUtf8("label_single_trap_light_4_relative_size"));

        gridLayout_single_trap_light_4->addWidget(label_single_trap_light_4_relative_size, 10, 0, 1, 1);

        logedit_single_trap_light_4_relative_size = new MyLineEdit(groupCheck_single_trap_light_4_enabled);
        logedit_single_trap_light_4_relative_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_4_relative_size"));

        gridLayout_single_trap_light_4->addWidget(logedit_single_trap_light_4_relative_size, 10, 1, 1, 2);

        checkBox_single_trap_light_4_pre_transformed = new MyCheckBox(groupCheck_single_trap_light_4_enabled);
        checkBox_single_trap_light_4_pre_transformed->setObjectName(QString::fromUtf8("checkBox_single_trap_light_4_pre_transformed"));

        gridLayout_single_trap_light_4->addWidget(checkBox_single_trap_light_4_pre_transformed, 11, 0, 1, 1);

        label_single_trap_light_4_position_mode = new QLabel(groupCheck_single_trap_light_4_enabled);
        label_single_trap_light_4_position_mode->setObjectName(QString::fromUtf8("label_single_trap_light_4_position_mode"));

        gridLayout_single_trap_light_4->addWidget(label_single_trap_light_4_position_mode, 12, 0, 1, 1);

        comboBox_single_trap_light_4_position_mode = new MyComboBox(groupCheck_single_trap_light_4_enabled);
        comboBox_single_trap_light_4_position_mode->addItem(QString());
        comboBox_single_trap_light_4_position_mode->addItem(QString());
        comboBox_single_trap_light_4_position_mode->addItem(QString());
        comboBox_single_trap_light_4_position_mode->addItem(QString());
        comboBox_single_trap_light_4_position_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_4_position_mode"));

        gridLayout_single_trap_light_4->addWidget(comboBox_single_trap_light_4_position_mode, 12, 1, 1, 2);

        label_single_trap_light_4_coloring_mode = new QLabel(groupCheck_single_trap_light_4_enabled);
        label_single_trap_light_4_coloring_mode->setObjectName(QString::fromUtf8("label_single_trap_light_4_coloring_mode"));

        gridLayout_single_trap_light_4->addWidget(label_single_trap_light_4_coloring_mode, 13, 0, 1, 1);

        comboBox_single_trap_light_4_coloring_mode = new MyComboBox(groupCheck_single_trap_light_4_enabled);
        comboBox_single_trap_light_4_coloring_mode->addItem(QString());
        comboBox_single_trap_light_4_coloring_mode->addItem(QString());
        comboBox_single_trap_light_4_coloring_mode->addItem(QString());
        comboBox_single_trap_light_4_coloring_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_4_coloring_mode"));

        gridLayout_single_trap_light_4->addWidget(comboBox_single_trap_light_4_coloring_mode, 13, 1, 1, 2);

        label_single_trap_light_4_falloff_type = new QLabel(groupCheck_single_trap_light_4_enabled);
        label_single_trap_light_4_falloff_type->setObjectName(QString::fromUtf8("label_single_trap_light_4_falloff_type"));

        gridLayout_single_trap_light_4->addWidget(label_single_trap_light_4_falloff_type, 14, 0, 1, 1);

        comboBox_single_trap_light_4_falloff_type = new MyComboBox(groupCheck_single_trap_light_4_enabled);
        comboBox_single_trap_light_4_falloff_type->addItem(QString());
        comboBox_single_trap_light_4_falloff_type->addItem(QString());
        comboBox_single_trap_light_4_falloff_type->addItem(QString());
        comboBox_single_trap_light_4_falloff_type->addItem(QString());
        comboBox_single_trap_light_4_falloff_type->addItem(QString());
        comboBox_single_trap_light_4_falloff_type->setObjectName(QString::fromUtf8("comboBox_single_trap_light_4_falloff_type"));

        gridLayout_single_trap_light_4->addWidget(comboBox_single_trap_light_4_falloff_type, 14, 1, 1, 2);

        label_single_trap_light_4_edge_softness = new QLabel(groupCheck_single_trap_light_4_enabled);
        label_single_trap_light_4_edge_softness->setObjectName(QString::fromUtf8("label_single_trap_light_4_edge_softness"));

        gridLayout_single_trap_light_4->addWidget(label_single_trap_light_4_edge_softness, 15, 0, 1, 1);

        logedit_single_trap_light_4_edge_softness = new MyLineEdit(groupCheck_single_trap_light_4_enabled);
        logedit_single_trap_light_4_edge_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_4_edge_softness"));

        gridLayout_single_trap_light_4->addWidget(logedit_single_trap_light_4_edge_softness, 15, 1, 1, 2);

        label_single_trap_light_4_anim_orbit_radius = new QLabel(groupCheck_single_trap_light_4_enabled);
        label_single_trap_light_4_anim_orbit_radius->setObjectName(QString::fromUtf8("label_single_trap_light_4_anim_orbit_radius"));

        gridLayout_single_trap_light_4->addWidget(label_single_trap_light_4_anim_orbit_radius, 16, 0, 1, 1);

        logedit_single_trap_light_4_anim_orbit_radius = new MyLineEdit(groupCheck_single_trap_light_4_enabled);
        logedit_single_trap_light_4_anim_orbit_radius->setObjectName(QString::fromUtf8("logedit_single_trap_light_4_anim_orbit_radius"));

        gridLayout_single_trap_light_4->addWidget(logedit_single_trap_light_4_anim_orbit_radius, 16, 1, 1, 1);

        logedit_single_trap_light_4_anim_orbit_speed = new MyLineEdit(groupCheck_single_trap_light_4_enabled);
        logedit_single_trap_light_4_anim_orbit_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_4_anim_orbit_speed"));

        gridLayout_single_trap_light_4->addWidget(logedit_single_trap_light_4_anim_orbit_speed, 16, 2, 1, 1);

        logedit_single_trap_light_4_anim_pulsate_speed = new MyLineEdit(groupCheck_single_trap_light_4_enabled);
        logedit_single_trap_light_4_anim_pulsate_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_4_anim_pulsate_speed"));

        gridLayout_single_trap_light_4->addWidget(logedit_single_trap_light_4_anim_pulsate_speed, 16, 3, 1, 1);

        logedit_single_trap_light_4_anim_pulsate_amount = new MyLineEdit(groupCheck_single_trap_light_4_enabled);
        logedit_single_trap_light_4_anim_pulsate_amount->setObjectName(QString::fromUtf8("logedit_single_trap_light_4_anim_pulsate_amount"));

        gridLayout_single_trap_light_4->addWidget(logedit_single_trap_light_4_anim_pulsate_amount, 16, 4, 1, 1);

        pushButton_single_trap_light_4_place_surface = new QPushButton(groupCheck_single_trap_light_4_enabled);
        pushButton_single_trap_light_4_place_surface->setObjectName(QString::fromUtf8("pushButton_single_trap_light_4_place_surface"));

        gridLayout_single_trap_light_4->addWidget(pushButton_single_trap_light_4_place_surface, 17, 0, 1, 5);

        pushButton_single_trap_light_4_place_target = new QPushButton(groupCheck_single_trap_light_4_enabled);
        pushButton_single_trap_light_4_place_target->setObjectName(QString::fromUtf8("pushButton_single_trap_light_4_place_target"));

        gridLayout_single_trap_light_4->addWidget(pushButton_single_trap_light_4_place_target, 18, 0, 1, 5);


        verticalLayout_single_trap_layers->addWidget(groupCheck_single_trap_light_4_enabled);

        groupCheck_single_trap_light_5_enabled = new MyGroupBox(scrollAreaWidgetContents_single_trap);
        groupCheck_single_trap_light_5_enabled->setObjectName(QString::fromUtf8("groupCheck_single_trap_light_5_enabled"));
        groupCheck_single_trap_light_5_enabled->setCheckable(true);
        gridLayout_single_trap_light_5 = new QGridLayout(groupCheck_single_trap_light_5_enabled);
        gridLayout_single_trap_light_5->setSpacing(2);
        gridLayout_single_trap_light_5->setObjectName(QString::fromUtf8("gridLayout_single_trap_light_5"));
        label_single_trap_light_5_shape = new QLabel(groupCheck_single_trap_light_5_enabled);
        label_single_trap_light_5_shape->setObjectName(QString::fromUtf8("label_single_trap_light_5_shape"));

        gridLayout_single_trap_light_5->addWidget(label_single_trap_light_5_shape, 0, 0, 1, 1);

        comboBox_single_trap_light_5_shape = new MyComboBox(groupCheck_single_trap_light_5_enabled);
        comboBox_single_trap_light_5_shape->addItem(QString());
        comboBox_single_trap_light_5_shape->addItem(QString());
        comboBox_single_trap_light_5_shape->addItem(QString());
        comboBox_single_trap_light_5_shape->addItem(QString());
        comboBox_single_trap_light_5_shape->addItem(QString());
        comboBox_single_trap_light_5_shape->addItem(QString());
        comboBox_single_trap_light_5_shape->addItem(QString());
        comboBox_single_trap_light_5_shape->addItem(QString());
        comboBox_single_trap_light_5_shape->addItem(QString());
        comboBox_single_trap_light_5_shape->addItem(QString());
        comboBox_single_trap_light_5_shape->addItem(QString());
        comboBox_single_trap_light_5_shape->addItem(QString());
        comboBox_single_trap_light_5_shape->addItem(QString());
        comboBox_single_trap_light_5_shape->addItem(QString());
        comboBox_single_trap_light_5_shape->setObjectName(QString::fromUtf8("comboBox_single_trap_light_5_shape"));

        gridLayout_single_trap_light_5->addWidget(comboBox_single_trap_light_5_shape, 0, 1, 1, 2);

        label_single_trap_light_5_position = new QLabel(groupCheck_single_trap_light_5_enabled);
        label_single_trap_light_5_position->setObjectName(QString::fromUtf8("label_single_trap_light_5_position"));

        gridLayout_single_trap_light_5->addWidget(label_single_trap_light_5_position, 1, 0, 1, 1);

        vect3_single_trap_light_5_position_x = new MyLineEdit(groupCheck_single_trap_light_5_enabled);
        vect3_single_trap_light_5_position_x->setObjectName(QString::fromUtf8("vect3_single_trap_light_5_position_x"));

        gridLayout_single_trap_light_5->addWidget(vect3_single_trap_light_5_position_x, 1, 1, 1, 1);

        vect3_single_trap_light_5_position_y = new MyLineEdit(groupCheck_single_trap_light_5_enabled);
        vect3_single_trap_light_5_position_y->setObjectName(QString::fromUtf8("vect3_single_trap_light_5_position_y"));

        gridLayout_single_trap_light_5->addWidget(vect3_single_trap_light_5_position_y, 1, 2, 1, 1);

        vect3_single_trap_light_5_position_z = new MyLineEdit(groupCheck_single_trap_light_5_enabled);
        vect3_single_trap_light_5_position_z->setObjectName(QString::fromUtf8("vect3_single_trap_light_5_position_z"));

        gridLayout_single_trap_light_5->addWidget(vect3_single_trap_light_5_position_z, 1, 3, 1, 1);

        pushButton_single_trap_light_5_place_camera = new QPushButton(groupCheck_single_trap_light_5_enabled);
        pushButton_single_trap_light_5_place_camera->setObjectName(QString::fromUtf8("pushButton_single_trap_light_5_place_camera"));

        gridLayout_single_trap_light_5->addWidget(pushButton_single_trap_light_5_place_camera, 1, 4, 1, 1);

        label_single_trap_light_5_size = new QLabel(groupCheck_single_trap_light_5_enabled);
        label_single_trap_light_5_size->setObjectName(QString::fromUtf8("label_single_trap_light_5_size"));

        gridLayout_single_trap_light_5->addWidget(label_single_trap_light_5_size, 2, 0, 1, 1);

        logedit_single_trap_light_5_size = new MyLineEdit(groupCheck_single_trap_light_5_enabled);
        logedit_single_trap_light_5_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_5_size"));

        gridLayout_single_trap_light_5->addWidget(logedit_single_trap_light_5_size, 2, 1, 1, 2);

        label_single_trap_light_5_size2 = new QLabel(groupCheck_single_trap_light_5_enabled);
        label_single_trap_light_5_size2->setObjectName(QString::fromUtf8("label_single_trap_light_5_size2"));

        gridLayout_single_trap_light_5->addWidget(label_single_trap_light_5_size2, 2, 3, 1, 1);

        logedit_single_trap_light_5_size2 = new MyLineEdit(groupCheck_single_trap_light_5_enabled);
        logedit_single_trap_light_5_size2->setObjectName(QString::fromUtf8("logedit_single_trap_light_5_size2"));

        gridLayout_single_trap_light_5->addWidget(logedit_single_trap_light_5_size2, 2, 4, 1, 1);

        label_single_trap_light_5_thickness = new QLabel(groupCheck_single_trap_light_5_enabled);
        label_single_trap_light_5_thickness->setObjectName(QString::fromUtf8("label_single_trap_light_5_thickness"));

        gridLayout_single_trap_light_5->addWidget(label_single_trap_light_5_thickness, 3, 0, 1, 1);

        logedit_single_trap_light_5_thickness = new MyLineEdit(groupCheck_single_trap_light_5_enabled);
        logedit_single_trap_light_5_thickness->setObjectName(QString::fromUtf8("logedit_single_trap_light_5_thickness"));

        gridLayout_single_trap_light_5->addWidget(logedit_single_trap_light_5_thickness, 3, 1, 1, 2);

        label_single_trap_light_5_rotation = new QLabel(groupCheck_single_trap_light_5_enabled);
        label_single_trap_light_5_rotation->setObjectName(QString::fromUtf8("label_single_trap_light_5_rotation"));

        gridLayout_single_trap_light_5->addWidget(label_single_trap_light_5_rotation, 4, 0, 1, 1);

        spinboxd3_single_trap_light_5_rotation_x = new MyDoubleSpinBox(groupCheck_single_trap_light_5_enabled);
        spinboxd3_single_trap_light_5_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_5_rotation_x"));

        gridLayout_single_trap_light_5->addWidget(spinboxd3_single_trap_light_5_rotation_x, 4, 1, 1, 1);

        spinboxd3_single_trap_light_5_rotation_y = new MyDoubleSpinBox(groupCheck_single_trap_light_5_enabled);
        spinboxd3_single_trap_light_5_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_5_rotation_y"));

        gridLayout_single_trap_light_5->addWidget(spinboxd3_single_trap_light_5_rotation_y, 4, 2, 1, 1);

        spinboxd3_single_trap_light_5_rotation_z = new MyDoubleSpinBox(groupCheck_single_trap_light_5_enabled);
        spinboxd3_single_trap_light_5_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_5_rotation_z"));

        gridLayout_single_trap_light_5->addWidget(spinboxd3_single_trap_light_5_rotation_z, 4, 3, 1, 1);

        label_single_trap_light_5_intensity = new QLabel(groupCheck_single_trap_light_5_enabled);
        label_single_trap_light_5_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_5_intensity"));

        gridLayout_single_trap_light_5->addWidget(label_single_trap_light_5_intensity, 5, 0, 1, 1);

        logedit_single_trap_light_5_intensity = new MyLineEdit(groupCheck_single_trap_light_5_enabled);
        logedit_single_trap_light_5_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_5_intensity"));

        gridLayout_single_trap_light_5->addWidget(logedit_single_trap_light_5_intensity, 5, 1, 1, 2);

        label_single_trap_light_5_color = new QLabel(groupCheck_single_trap_light_5_enabled);
        label_single_trap_light_5_color->setObjectName(QString::fromUtf8("label_single_trap_light_5_color"));

        gridLayout_single_trap_light_5->addWidget(label_single_trap_light_5_color, 6, 0, 1, 1);

        colorButton_single_trap_light_5_color = new MyColorButton(groupCheck_single_trap_light_5_enabled);
        colorButton_single_trap_light_5_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_5_color"));

        gridLayout_single_trap_light_5->addWidget(colorButton_single_trap_light_5_color, 6, 1, 1, 1);

        label_single_trap_light_5_gradient_color = new QLabel(groupCheck_single_trap_light_5_enabled);
        label_single_trap_light_5_gradient_color->setObjectName(QString::fromUtf8("label_single_trap_light_5_gradient_color"));

        gridLayout_single_trap_light_5->addWidget(label_single_trap_light_5_gradient_color, 6, 2, 1, 1);

        colorButton_single_trap_light_5_gradient_color = new MyColorButton(groupCheck_single_trap_light_5_enabled);
        colorButton_single_trap_light_5_gradient_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_5_gradient_color"));

        gridLayout_single_trap_light_5->addWidget(colorButton_single_trap_light_5_gradient_color, 6, 3, 1, 2);

        label_single_trap_light_5_visibility = new QLabel(groupCheck_single_trap_light_5_enabled);
        label_single_trap_light_5_visibility->setObjectName(QString::fromUtf8("label_single_trap_light_5_visibility"));

        gridLayout_single_trap_light_5->addWidget(label_single_trap_light_5_visibility, 7, 0, 1, 1);

        logedit_single_trap_light_5_visibility = new MyLineEdit(groupCheck_single_trap_light_5_enabled);
        logedit_single_trap_light_5_visibility->setObjectName(QString::fromUtf8("logedit_single_trap_light_5_visibility"));

        gridLayout_single_trap_light_5->addWidget(logedit_single_trap_light_5_visibility, 7, 1, 1, 2);

        label_single_trap_light_5_max_distance = new QLabel(groupCheck_single_trap_light_5_enabled);
        label_single_trap_light_5_max_distance->setObjectName(QString::fromUtf8("label_single_trap_light_5_max_distance"));

        gridLayout_single_trap_light_5->addWidget(label_single_trap_light_5_max_distance, 7, 3, 1, 1);

        logedit_single_trap_light_5_max_distance = new MyLineEdit(groupCheck_single_trap_light_5_enabled);
        logedit_single_trap_light_5_max_distance->setObjectName(QString::fromUtf8("logedit_single_trap_light_5_max_distance"));

        gridLayout_single_trap_light_5->addWidget(logedit_single_trap_light_5_max_distance, 7, 4, 1, 1);

        label_single_trap_light_5_sharpening = new QLabel(groupCheck_single_trap_light_5_enabled);
        label_single_trap_light_5_sharpening->setObjectName(QString::fromUtf8("label_single_trap_light_5_sharpening"));

        gridLayout_single_trap_light_5->addWidget(label_single_trap_light_5_sharpening, 8, 0, 1, 1);

        logedit_single_trap_light_5_sharpening = new MyLineEdit(groupCheck_single_trap_light_5_enabled);
        logedit_single_trap_light_5_sharpening->setObjectName(QString::fromUtf8("logedit_single_trap_light_5_sharpening"));

        gridLayout_single_trap_light_5->addWidget(logedit_single_trap_light_5_sharpening, 8, 1, 1, 2);

        label_single_trap_light_5_blur = new QLabel(groupCheck_single_trap_light_5_enabled);
        label_single_trap_light_5_blur->setObjectName(QString::fromUtf8("label_single_trap_light_5_blur"));

        gridLayout_single_trap_light_5->addWidget(label_single_trap_light_5_blur, 8, 3, 1, 1);

        logedit_single_trap_light_5_blur = new MyLineEdit(groupCheck_single_trap_light_5_enabled);
        logedit_single_trap_light_5_blur->setObjectName(QString::fromUtf8("logedit_single_trap_light_5_blur"));

        gridLayout_single_trap_light_5->addWidget(logedit_single_trap_light_5_blur, 8, 4, 1, 1);

        label_single_trap_light_5_solid_intensity = new QLabel(groupCheck_single_trap_light_5_enabled);
        label_single_trap_light_5_solid_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_5_solid_intensity"));

        gridLayout_single_trap_light_5->addWidget(label_single_trap_light_5_solid_intensity, 9, 0, 1, 1);

        logedit_single_trap_light_5_solid_intensity = new MyLineEdit(groupCheck_single_trap_light_5_enabled);
        logedit_single_trap_light_5_solid_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_5_solid_intensity"));

        gridLayout_single_trap_light_5->addWidget(logedit_single_trap_light_5_solid_intensity, 9, 1, 1, 2);

        label_single_trap_light_5_softness = new QLabel(groupCheck_single_trap_light_5_enabled);
        label_single_trap_light_5_softness->setObjectName(QString::fromUtf8("label_single_trap_light_5_softness"));

        gridLayout_single_trap_light_5->addWidget(label_single_trap_light_5_softness, 9, 3, 1, 1);

        logedit_single_trap_light_5_softness = new MyLineEdit(groupCheck_single_trap_light_5_enabled);
        logedit_single_trap_light_5_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_5_softness"));

        gridLayout_single_trap_light_5->addWidget(logedit_single_trap_light_5_softness, 9, 4, 1, 1);

        label_single_trap_light_5_relative_size = new QLabel(groupCheck_single_trap_light_5_enabled);
        label_single_trap_light_5_relative_size->setObjectName(QString::fromUtf8("label_single_trap_light_5_relative_size"));

        gridLayout_single_trap_light_5->addWidget(label_single_trap_light_5_relative_size, 10, 0, 1, 1);

        logedit_single_trap_light_5_relative_size = new MyLineEdit(groupCheck_single_trap_light_5_enabled);
        logedit_single_trap_light_5_relative_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_5_relative_size"));

        gridLayout_single_trap_light_5->addWidget(logedit_single_trap_light_5_relative_size, 10, 1, 1, 2);

        checkBox_single_trap_light_5_pre_transformed = new MyCheckBox(groupCheck_single_trap_light_5_enabled);
        checkBox_single_trap_light_5_pre_transformed->setObjectName(QString::fromUtf8("checkBox_single_trap_light_5_pre_transformed"));

        gridLayout_single_trap_light_5->addWidget(checkBox_single_trap_light_5_pre_transformed, 11, 0, 1, 1);

        label_single_trap_light_5_position_mode = new QLabel(groupCheck_single_trap_light_5_enabled);
        label_single_trap_light_5_position_mode->setObjectName(QString::fromUtf8("label_single_trap_light_5_position_mode"));

        gridLayout_single_trap_light_5->addWidget(label_single_trap_light_5_position_mode, 12, 0, 1, 1);

        comboBox_single_trap_light_5_position_mode = new MyComboBox(groupCheck_single_trap_light_5_enabled);
        comboBox_single_trap_light_5_position_mode->addItem(QString());
        comboBox_single_trap_light_5_position_mode->addItem(QString());
        comboBox_single_trap_light_5_position_mode->addItem(QString());
        comboBox_single_trap_light_5_position_mode->addItem(QString());
        comboBox_single_trap_light_5_position_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_5_position_mode"));

        gridLayout_single_trap_light_5->addWidget(comboBox_single_trap_light_5_position_mode, 12, 1, 1, 2);

        label_single_trap_light_5_coloring_mode = new QLabel(groupCheck_single_trap_light_5_enabled);
        label_single_trap_light_5_coloring_mode->setObjectName(QString::fromUtf8("label_single_trap_light_5_coloring_mode"));

        gridLayout_single_trap_light_5->addWidget(label_single_trap_light_5_coloring_mode, 13, 0, 1, 1);

        comboBox_single_trap_light_5_coloring_mode = new MyComboBox(groupCheck_single_trap_light_5_enabled);
        comboBox_single_trap_light_5_coloring_mode->addItem(QString());
        comboBox_single_trap_light_5_coloring_mode->addItem(QString());
        comboBox_single_trap_light_5_coloring_mode->addItem(QString());
        comboBox_single_trap_light_5_coloring_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_5_coloring_mode"));

        gridLayout_single_trap_light_5->addWidget(comboBox_single_trap_light_5_coloring_mode, 13, 1, 1, 2);

        label_single_trap_light_5_falloff_type = new QLabel(groupCheck_single_trap_light_5_enabled);
        label_single_trap_light_5_falloff_type->setObjectName(QString::fromUtf8("label_single_trap_light_5_falloff_type"));

        gridLayout_single_trap_light_5->addWidget(label_single_trap_light_5_falloff_type, 14, 0, 1, 1);

        comboBox_single_trap_light_5_falloff_type = new MyComboBox(groupCheck_single_trap_light_5_enabled);
        comboBox_single_trap_light_5_falloff_type->addItem(QString());
        comboBox_single_trap_light_5_falloff_type->addItem(QString());
        comboBox_single_trap_light_5_falloff_type->addItem(QString());
        comboBox_single_trap_light_5_falloff_type->addItem(QString());
        comboBox_single_trap_light_5_falloff_type->addItem(QString());
        comboBox_single_trap_light_5_falloff_type->setObjectName(QString::fromUtf8("comboBox_single_trap_light_5_falloff_type"));

        gridLayout_single_trap_light_5->addWidget(comboBox_single_trap_light_5_falloff_type, 14, 1, 1, 2);

        label_single_trap_light_5_edge_softness = new QLabel(groupCheck_single_trap_light_5_enabled);
        label_single_trap_light_5_edge_softness->setObjectName(QString::fromUtf8("label_single_trap_light_5_edge_softness"));

        gridLayout_single_trap_light_5->addWidget(label_single_trap_light_5_edge_softness, 15, 0, 1, 1);

        logedit_single_trap_light_5_edge_softness = new MyLineEdit(groupCheck_single_trap_light_5_enabled);
        logedit_single_trap_light_5_edge_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_5_edge_softness"));

        gridLayout_single_trap_light_5->addWidget(logedit_single_trap_light_5_edge_softness, 15, 1, 1, 2);

        label_single_trap_light_5_anim_orbit_radius = new QLabel(groupCheck_single_trap_light_5_enabled);
        label_single_trap_light_5_anim_orbit_radius->setObjectName(QString::fromUtf8("label_single_trap_light_5_anim_orbit_radius"));

        gridLayout_single_trap_light_5->addWidget(label_single_trap_light_5_anim_orbit_radius, 16, 0, 1, 1);

        logedit_single_trap_light_5_anim_orbit_radius = new MyLineEdit(groupCheck_single_trap_light_5_enabled);
        logedit_single_trap_light_5_anim_orbit_radius->setObjectName(QString::fromUtf8("logedit_single_trap_light_5_anim_orbit_radius"));

        gridLayout_single_trap_light_5->addWidget(logedit_single_trap_light_5_anim_orbit_radius, 16, 1, 1, 1);

        logedit_single_trap_light_5_anim_orbit_speed = new MyLineEdit(groupCheck_single_trap_light_5_enabled);
        logedit_single_trap_light_5_anim_orbit_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_5_anim_orbit_speed"));

        gridLayout_single_trap_light_5->addWidget(logedit_single_trap_light_5_anim_orbit_speed, 16, 2, 1, 1);

        logedit_single_trap_light_5_anim_pulsate_speed = new MyLineEdit(groupCheck_single_trap_light_5_enabled);
        logedit_single_trap_light_5_anim_pulsate_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_5_anim_pulsate_speed"));

        gridLayout_single_trap_light_5->addWidget(logedit_single_trap_light_5_anim_pulsate_speed, 16, 3, 1, 1);

        logedit_single_trap_light_5_anim_pulsate_amount = new MyLineEdit(groupCheck_single_trap_light_5_enabled);
        logedit_single_trap_light_5_anim_pulsate_amount->setObjectName(QString::fromUtf8("logedit_single_trap_light_5_anim_pulsate_amount"));

        gridLayout_single_trap_light_5->addWidget(logedit_single_trap_light_5_anim_pulsate_amount, 16, 4, 1, 1);

        pushButton_single_trap_light_5_place_surface = new QPushButton(groupCheck_single_trap_light_5_enabled);
        pushButton_single_trap_light_5_place_surface->setObjectName(QString::fromUtf8("pushButton_single_trap_light_5_place_surface"));

        gridLayout_single_trap_light_5->addWidget(pushButton_single_trap_light_5_place_surface, 17, 0, 1, 5);

        pushButton_single_trap_light_5_place_target = new QPushButton(groupCheck_single_trap_light_5_enabled);
        pushButton_single_trap_light_5_place_target->setObjectName(QString::fromUtf8("pushButton_single_trap_light_5_place_target"));

        gridLayout_single_trap_light_5->addWidget(pushButton_single_trap_light_5_place_target, 18, 0, 1, 5);


        verticalLayout_single_trap_layers->addWidget(groupCheck_single_trap_light_5_enabled);

        groupCheck_single_trap_light_6_enabled = new MyGroupBox(scrollAreaWidgetContents_single_trap);
        groupCheck_single_trap_light_6_enabled->setObjectName(QString::fromUtf8("groupCheck_single_trap_light_6_enabled"));
        groupCheck_single_trap_light_6_enabled->setCheckable(true);
        gridLayout_single_trap_light_6 = new QGridLayout(groupCheck_single_trap_light_6_enabled);
        gridLayout_single_trap_light_6->setSpacing(2);
        gridLayout_single_trap_light_6->setObjectName(QString::fromUtf8("gridLayout_single_trap_light_6"));
        label_single_trap_light_6_shape = new QLabel(groupCheck_single_trap_light_6_enabled);
        label_single_trap_light_6_shape->setObjectName(QString::fromUtf8("label_single_trap_light_6_shape"));

        gridLayout_single_trap_light_6->addWidget(label_single_trap_light_6_shape, 0, 0, 1, 1);

        comboBox_single_trap_light_6_shape = new MyComboBox(groupCheck_single_trap_light_6_enabled);
        comboBox_single_trap_light_6_shape->addItem(QString());
        comboBox_single_trap_light_6_shape->addItem(QString());
        comboBox_single_trap_light_6_shape->addItem(QString());
        comboBox_single_trap_light_6_shape->addItem(QString());
        comboBox_single_trap_light_6_shape->addItem(QString());
        comboBox_single_trap_light_6_shape->addItem(QString());
        comboBox_single_trap_light_6_shape->addItem(QString());
        comboBox_single_trap_light_6_shape->addItem(QString());
        comboBox_single_trap_light_6_shape->addItem(QString());
        comboBox_single_trap_light_6_shape->addItem(QString());
        comboBox_single_trap_light_6_shape->addItem(QString());
        comboBox_single_trap_light_6_shape->addItem(QString());
        comboBox_single_trap_light_6_shape->addItem(QString());
        comboBox_single_trap_light_6_shape->addItem(QString());
        comboBox_single_trap_light_6_shape->setObjectName(QString::fromUtf8("comboBox_single_trap_light_6_shape"));

        gridLayout_single_trap_light_6->addWidget(comboBox_single_trap_light_6_shape, 0, 1, 1, 2);

        label_single_trap_light_6_position = new QLabel(groupCheck_single_trap_light_6_enabled);
        label_single_trap_light_6_position->setObjectName(QString::fromUtf8("label_single_trap_light_6_position"));

        gridLayout_single_trap_light_6->addWidget(label_single_trap_light_6_position, 1, 0, 1, 1);

        vect3_single_trap_light_6_position_x = new MyLineEdit(groupCheck_single_trap_light_6_enabled);
        vect3_single_trap_light_6_position_x->setObjectName(QString::fromUtf8("vect3_single_trap_light_6_position_x"));

        gridLayout_single_trap_light_6->addWidget(vect3_single_trap_light_6_position_x, 1, 1, 1, 1);

        vect3_single_trap_light_6_position_y = new MyLineEdit(groupCheck_single_trap_light_6_enabled);
        vect3_single_trap_light_6_position_y->setObjectName(QString::fromUtf8("vect3_single_trap_light_6_position_y"));

        gridLayout_single_trap_light_6->addWidget(vect3_single_trap_light_6_position_y, 1, 2, 1, 1);

        vect3_single_trap_light_6_position_z = new MyLineEdit(groupCheck_single_trap_light_6_enabled);
        vect3_single_trap_light_6_position_z->setObjectName(QString::fromUtf8("vect3_single_trap_light_6_position_z"));

        gridLayout_single_trap_light_6->addWidget(vect3_single_trap_light_6_position_z, 1, 3, 1, 1);

        pushButton_single_trap_light_6_place_camera = new QPushButton(groupCheck_single_trap_light_6_enabled);
        pushButton_single_trap_light_6_place_camera->setObjectName(QString::fromUtf8("pushButton_single_trap_light_6_place_camera"));

        gridLayout_single_trap_light_6->addWidget(pushButton_single_trap_light_6_place_camera, 1, 4, 1, 1);

        label_single_trap_light_6_size = new QLabel(groupCheck_single_trap_light_6_enabled);
        label_single_trap_light_6_size->setObjectName(QString::fromUtf8("label_single_trap_light_6_size"));

        gridLayout_single_trap_light_6->addWidget(label_single_trap_light_6_size, 2, 0, 1, 1);

        logedit_single_trap_light_6_size = new MyLineEdit(groupCheck_single_trap_light_6_enabled);
        logedit_single_trap_light_6_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_6_size"));

        gridLayout_single_trap_light_6->addWidget(logedit_single_trap_light_6_size, 2, 1, 1, 2);

        label_single_trap_light_6_size2 = new QLabel(groupCheck_single_trap_light_6_enabled);
        label_single_trap_light_6_size2->setObjectName(QString::fromUtf8("label_single_trap_light_6_size2"));

        gridLayout_single_trap_light_6->addWidget(label_single_trap_light_6_size2, 2, 3, 1, 1);

        logedit_single_trap_light_6_size2 = new MyLineEdit(groupCheck_single_trap_light_6_enabled);
        logedit_single_trap_light_6_size2->setObjectName(QString::fromUtf8("logedit_single_trap_light_6_size2"));

        gridLayout_single_trap_light_6->addWidget(logedit_single_trap_light_6_size2, 2, 4, 1, 1);

        label_single_trap_light_6_thickness = new QLabel(groupCheck_single_trap_light_6_enabled);
        label_single_trap_light_6_thickness->setObjectName(QString::fromUtf8("label_single_trap_light_6_thickness"));

        gridLayout_single_trap_light_6->addWidget(label_single_trap_light_6_thickness, 3, 0, 1, 1);

        logedit_single_trap_light_6_thickness = new MyLineEdit(groupCheck_single_trap_light_6_enabled);
        logedit_single_trap_light_6_thickness->setObjectName(QString::fromUtf8("logedit_single_trap_light_6_thickness"));

        gridLayout_single_trap_light_6->addWidget(logedit_single_trap_light_6_thickness, 3, 1, 1, 2);

        label_single_trap_light_6_rotation = new QLabel(groupCheck_single_trap_light_6_enabled);
        label_single_trap_light_6_rotation->setObjectName(QString::fromUtf8("label_single_trap_light_6_rotation"));

        gridLayout_single_trap_light_6->addWidget(label_single_trap_light_6_rotation, 4, 0, 1, 1);

        spinboxd3_single_trap_light_6_rotation_x = new MyDoubleSpinBox(groupCheck_single_trap_light_6_enabled);
        spinboxd3_single_trap_light_6_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_6_rotation_x"));

        gridLayout_single_trap_light_6->addWidget(spinboxd3_single_trap_light_6_rotation_x, 4, 1, 1, 1);

        spinboxd3_single_trap_light_6_rotation_y = new MyDoubleSpinBox(groupCheck_single_trap_light_6_enabled);
        spinboxd3_single_trap_light_6_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_6_rotation_y"));

        gridLayout_single_trap_light_6->addWidget(spinboxd3_single_trap_light_6_rotation_y, 4, 2, 1, 1);

        spinboxd3_single_trap_light_6_rotation_z = new MyDoubleSpinBox(groupCheck_single_trap_light_6_enabled);
        spinboxd3_single_trap_light_6_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_6_rotation_z"));

        gridLayout_single_trap_light_6->addWidget(spinboxd3_single_trap_light_6_rotation_z, 4, 3, 1, 1);

        label_single_trap_light_6_intensity = new QLabel(groupCheck_single_trap_light_6_enabled);
        label_single_trap_light_6_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_6_intensity"));

        gridLayout_single_trap_light_6->addWidget(label_single_trap_light_6_intensity, 5, 0, 1, 1);

        logedit_single_trap_light_6_intensity = new MyLineEdit(groupCheck_single_trap_light_6_enabled);
        logedit_single_trap_light_6_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_6_intensity"));

        gridLayout_single_trap_light_6->addWidget(logedit_single_trap_light_6_intensity, 5, 1, 1, 2);

        label_single_trap_light_6_color = new QLabel(groupCheck_single_trap_light_6_enabled);
        label_single_trap_light_6_color->setObjectName(QString::fromUtf8("label_single_trap_light_6_color"));

        gridLayout_single_trap_light_6->addWidget(label_single_trap_light_6_color, 6, 0, 1, 1);

        colorButton_single_trap_light_6_color = new MyColorButton(groupCheck_single_trap_light_6_enabled);
        colorButton_single_trap_light_6_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_6_color"));

        gridLayout_single_trap_light_6->addWidget(colorButton_single_trap_light_6_color, 6, 1, 1, 1);

        label_single_trap_light_6_gradient_color = new QLabel(groupCheck_single_trap_light_6_enabled);
        label_single_trap_light_6_gradient_color->setObjectName(QString::fromUtf8("label_single_trap_light_6_gradient_color"));

        gridLayout_single_trap_light_6->addWidget(label_single_trap_light_6_gradient_color, 6, 2, 1, 1);

        colorButton_single_trap_light_6_gradient_color = new MyColorButton(groupCheck_single_trap_light_6_enabled);
        colorButton_single_trap_light_6_gradient_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_6_gradient_color"));

        gridLayout_single_trap_light_6->addWidget(colorButton_single_trap_light_6_gradient_color, 6, 3, 1, 2);

        label_single_trap_light_6_visibility = new QLabel(groupCheck_single_trap_light_6_enabled);
        label_single_trap_light_6_visibility->setObjectName(QString::fromUtf8("label_single_trap_light_6_visibility"));

        gridLayout_single_trap_light_6->addWidget(label_single_trap_light_6_visibility, 7, 0, 1, 1);

        logedit_single_trap_light_6_visibility = new MyLineEdit(groupCheck_single_trap_light_6_enabled);
        logedit_single_trap_light_6_visibility->setObjectName(QString::fromUtf8("logedit_single_trap_light_6_visibility"));

        gridLayout_single_trap_light_6->addWidget(logedit_single_trap_light_6_visibility, 7, 1, 1, 2);

        label_single_trap_light_6_max_distance = new QLabel(groupCheck_single_trap_light_6_enabled);
        label_single_trap_light_6_max_distance->setObjectName(QString::fromUtf8("label_single_trap_light_6_max_distance"));

        gridLayout_single_trap_light_6->addWidget(label_single_trap_light_6_max_distance, 7, 3, 1, 1);

        logedit_single_trap_light_6_max_distance = new MyLineEdit(groupCheck_single_trap_light_6_enabled);
        logedit_single_trap_light_6_max_distance->setObjectName(QString::fromUtf8("logedit_single_trap_light_6_max_distance"));

        gridLayout_single_trap_light_6->addWidget(logedit_single_trap_light_6_max_distance, 7, 4, 1, 1);

        label_single_trap_light_6_sharpening = new QLabel(groupCheck_single_trap_light_6_enabled);
        label_single_trap_light_6_sharpening->setObjectName(QString::fromUtf8("label_single_trap_light_6_sharpening"));

        gridLayout_single_trap_light_6->addWidget(label_single_trap_light_6_sharpening, 8, 0, 1, 1);

        logedit_single_trap_light_6_sharpening = new MyLineEdit(groupCheck_single_trap_light_6_enabled);
        logedit_single_trap_light_6_sharpening->setObjectName(QString::fromUtf8("logedit_single_trap_light_6_sharpening"));

        gridLayout_single_trap_light_6->addWidget(logedit_single_trap_light_6_sharpening, 8, 1, 1, 2);

        label_single_trap_light_6_blur = new QLabel(groupCheck_single_trap_light_6_enabled);
        label_single_trap_light_6_blur->setObjectName(QString::fromUtf8("label_single_trap_light_6_blur"));

        gridLayout_single_trap_light_6->addWidget(label_single_trap_light_6_blur, 8, 3, 1, 1);

        logedit_single_trap_light_6_blur = new MyLineEdit(groupCheck_single_trap_light_6_enabled);
        logedit_single_trap_light_6_blur->setObjectName(QString::fromUtf8("logedit_single_trap_light_6_blur"));

        gridLayout_single_trap_light_6->addWidget(logedit_single_trap_light_6_blur, 8, 4, 1, 1);

        label_single_trap_light_6_solid_intensity = new QLabel(groupCheck_single_trap_light_6_enabled);
        label_single_trap_light_6_solid_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_6_solid_intensity"));

        gridLayout_single_trap_light_6->addWidget(label_single_trap_light_6_solid_intensity, 9, 0, 1, 1);

        logedit_single_trap_light_6_solid_intensity = new MyLineEdit(groupCheck_single_trap_light_6_enabled);
        logedit_single_trap_light_6_solid_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_6_solid_intensity"));

        gridLayout_single_trap_light_6->addWidget(logedit_single_trap_light_6_solid_intensity, 9, 1, 1, 2);

        label_single_trap_light_6_softness = new QLabel(groupCheck_single_trap_light_6_enabled);
        label_single_trap_light_6_softness->setObjectName(QString::fromUtf8("label_single_trap_light_6_softness"));

        gridLayout_single_trap_light_6->addWidget(label_single_trap_light_6_softness, 9, 3, 1, 1);

        logedit_single_trap_light_6_softness = new MyLineEdit(groupCheck_single_trap_light_6_enabled);
        logedit_single_trap_light_6_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_6_softness"));

        gridLayout_single_trap_light_6->addWidget(logedit_single_trap_light_6_softness, 9, 4, 1, 1);

        label_single_trap_light_6_relative_size = new QLabel(groupCheck_single_trap_light_6_enabled);
        label_single_trap_light_6_relative_size->setObjectName(QString::fromUtf8("label_single_trap_light_6_relative_size"));

        gridLayout_single_trap_light_6->addWidget(label_single_trap_light_6_relative_size, 10, 0, 1, 1);

        logedit_single_trap_light_6_relative_size = new MyLineEdit(groupCheck_single_trap_light_6_enabled);
        logedit_single_trap_light_6_relative_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_6_relative_size"));

        gridLayout_single_trap_light_6->addWidget(logedit_single_trap_light_6_relative_size, 10, 1, 1, 2);

        checkBox_single_trap_light_6_pre_transformed = new MyCheckBox(groupCheck_single_trap_light_6_enabled);
        checkBox_single_trap_light_6_pre_transformed->setObjectName(QString::fromUtf8("checkBox_single_trap_light_6_pre_transformed"));

        gridLayout_single_trap_light_6->addWidget(checkBox_single_trap_light_6_pre_transformed, 11, 0, 1, 1);

        label_single_trap_light_6_position_mode = new QLabel(groupCheck_single_trap_light_6_enabled);
        label_single_trap_light_6_position_mode->setObjectName(QString::fromUtf8("label_single_trap_light_6_position_mode"));

        gridLayout_single_trap_light_6->addWidget(label_single_trap_light_6_position_mode, 12, 0, 1, 1);

        comboBox_single_trap_light_6_position_mode = new MyComboBox(groupCheck_single_trap_light_6_enabled);
        comboBox_single_trap_light_6_position_mode->addItem(QString());
        comboBox_single_trap_light_6_position_mode->addItem(QString());
        comboBox_single_trap_light_6_position_mode->addItem(QString());
        comboBox_single_trap_light_6_position_mode->addItem(QString());
        comboBox_single_trap_light_6_position_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_6_position_mode"));

        gridLayout_single_trap_light_6->addWidget(comboBox_single_trap_light_6_position_mode, 12, 1, 1, 2);

        label_single_trap_light_6_coloring_mode = new QLabel(groupCheck_single_trap_light_6_enabled);
        label_single_trap_light_6_coloring_mode->setObjectName(QString::fromUtf8("label_single_trap_light_6_coloring_mode"));

        gridLayout_single_trap_light_6->addWidget(label_single_trap_light_6_coloring_mode, 13, 0, 1, 1);

        comboBox_single_trap_light_6_coloring_mode = new MyComboBox(groupCheck_single_trap_light_6_enabled);
        comboBox_single_trap_light_6_coloring_mode->addItem(QString());
        comboBox_single_trap_light_6_coloring_mode->addItem(QString());
        comboBox_single_trap_light_6_coloring_mode->addItem(QString());
        comboBox_single_trap_light_6_coloring_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_6_coloring_mode"));

        gridLayout_single_trap_light_6->addWidget(comboBox_single_trap_light_6_coloring_mode, 13, 1, 1, 2);

        label_single_trap_light_6_falloff_type = new QLabel(groupCheck_single_trap_light_6_enabled);
        label_single_trap_light_6_falloff_type->setObjectName(QString::fromUtf8("label_single_trap_light_6_falloff_type"));

        gridLayout_single_trap_light_6->addWidget(label_single_trap_light_6_falloff_type, 14, 0, 1, 1);

        comboBox_single_trap_light_6_falloff_type = new MyComboBox(groupCheck_single_trap_light_6_enabled);
        comboBox_single_trap_light_6_falloff_type->addItem(QString());
        comboBox_single_trap_light_6_falloff_type->addItem(QString());
        comboBox_single_trap_light_6_falloff_type->addItem(QString());
        comboBox_single_trap_light_6_falloff_type->addItem(QString());
        comboBox_single_trap_light_6_falloff_type->addItem(QString());
        comboBox_single_trap_light_6_falloff_type->setObjectName(QString::fromUtf8("comboBox_single_trap_light_6_falloff_type"));

        gridLayout_single_trap_light_6->addWidget(comboBox_single_trap_light_6_falloff_type, 14, 1, 1, 2);

        label_single_trap_light_6_edge_softness = new QLabel(groupCheck_single_trap_light_6_enabled);
        label_single_trap_light_6_edge_softness->setObjectName(QString::fromUtf8("label_single_trap_light_6_edge_softness"));

        gridLayout_single_trap_light_6->addWidget(label_single_trap_light_6_edge_softness, 15, 0, 1, 1);

        logedit_single_trap_light_6_edge_softness = new MyLineEdit(groupCheck_single_trap_light_6_enabled);
        logedit_single_trap_light_6_edge_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_6_edge_softness"));

        gridLayout_single_trap_light_6->addWidget(logedit_single_trap_light_6_edge_softness, 15, 1, 1, 2);

        label_single_trap_light_6_anim_orbit_radius = new QLabel(groupCheck_single_trap_light_6_enabled);
        label_single_trap_light_6_anim_orbit_radius->setObjectName(QString::fromUtf8("label_single_trap_light_6_anim_orbit_radius"));

        gridLayout_single_trap_light_6->addWidget(label_single_trap_light_6_anim_orbit_radius, 16, 0, 1, 1);

        logedit_single_trap_light_6_anim_orbit_radius = new MyLineEdit(groupCheck_single_trap_light_6_enabled);
        logedit_single_trap_light_6_anim_orbit_radius->setObjectName(QString::fromUtf8("logedit_single_trap_light_6_anim_orbit_radius"));

        gridLayout_single_trap_light_6->addWidget(logedit_single_trap_light_6_anim_orbit_radius, 16, 1, 1, 1);

        logedit_single_trap_light_6_anim_orbit_speed = new MyLineEdit(groupCheck_single_trap_light_6_enabled);
        logedit_single_trap_light_6_anim_orbit_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_6_anim_orbit_speed"));

        gridLayout_single_trap_light_6->addWidget(logedit_single_trap_light_6_anim_orbit_speed, 16, 2, 1, 1);

        logedit_single_trap_light_6_anim_pulsate_speed = new MyLineEdit(groupCheck_single_trap_light_6_enabled);
        logedit_single_trap_light_6_anim_pulsate_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_6_anim_pulsate_speed"));

        gridLayout_single_trap_light_6->addWidget(logedit_single_trap_light_6_anim_pulsate_speed, 16, 3, 1, 1);

        logedit_single_trap_light_6_anim_pulsate_amount = new MyLineEdit(groupCheck_single_trap_light_6_enabled);
        logedit_single_trap_light_6_anim_pulsate_amount->setObjectName(QString::fromUtf8("logedit_single_trap_light_6_anim_pulsate_amount"));

        gridLayout_single_trap_light_6->addWidget(logedit_single_trap_light_6_anim_pulsate_amount, 16, 4, 1, 1);

        pushButton_single_trap_light_6_place_surface = new QPushButton(groupCheck_single_trap_light_6_enabled);
        pushButton_single_trap_light_6_place_surface->setObjectName(QString::fromUtf8("pushButton_single_trap_light_6_place_surface"));

        gridLayout_single_trap_light_6->addWidget(pushButton_single_trap_light_6_place_surface, 17, 0, 1, 5);

        pushButton_single_trap_light_6_place_target = new QPushButton(groupCheck_single_trap_light_6_enabled);
        pushButton_single_trap_light_6_place_target->setObjectName(QString::fromUtf8("pushButton_single_trap_light_6_place_target"));

        gridLayout_single_trap_light_6->addWidget(pushButton_single_trap_light_6_place_target, 18, 0, 1, 5);


        verticalLayout_single_trap_layers->addWidget(groupCheck_single_trap_light_6_enabled);

        groupCheck_single_trap_light_7_enabled = new MyGroupBox(scrollAreaWidgetContents_single_trap);
        groupCheck_single_trap_light_7_enabled->setObjectName(QString::fromUtf8("groupCheck_single_trap_light_7_enabled"));
        groupCheck_single_trap_light_7_enabled->setCheckable(true);
        gridLayout_single_trap_light_7 = new QGridLayout(groupCheck_single_trap_light_7_enabled);
        gridLayout_single_trap_light_7->setSpacing(2);
        gridLayout_single_trap_light_7->setObjectName(QString::fromUtf8("gridLayout_single_trap_light_7"));
        label_single_trap_light_7_shape = new QLabel(groupCheck_single_trap_light_7_enabled);
        label_single_trap_light_7_shape->setObjectName(QString::fromUtf8("label_single_trap_light_7_shape"));

        gridLayout_single_trap_light_7->addWidget(label_single_trap_light_7_shape, 0, 0, 1, 1);

        comboBox_single_trap_light_7_shape = new MyComboBox(groupCheck_single_trap_light_7_enabled);
        comboBox_single_trap_light_7_shape->addItem(QString());
        comboBox_single_trap_light_7_shape->addItem(QString());
        comboBox_single_trap_light_7_shape->addItem(QString());
        comboBox_single_trap_light_7_shape->addItem(QString());
        comboBox_single_trap_light_7_shape->addItem(QString());
        comboBox_single_trap_light_7_shape->addItem(QString());
        comboBox_single_trap_light_7_shape->addItem(QString());
        comboBox_single_trap_light_7_shape->addItem(QString());
        comboBox_single_trap_light_7_shape->addItem(QString());
        comboBox_single_trap_light_7_shape->addItem(QString());
        comboBox_single_trap_light_7_shape->addItem(QString());
        comboBox_single_trap_light_7_shape->addItem(QString());
        comboBox_single_trap_light_7_shape->addItem(QString());
        comboBox_single_trap_light_7_shape->addItem(QString());
        comboBox_single_trap_light_7_shape->setObjectName(QString::fromUtf8("comboBox_single_trap_light_7_shape"));

        gridLayout_single_trap_light_7->addWidget(comboBox_single_trap_light_7_shape, 0, 1, 1, 2);

        label_single_trap_light_7_position = new QLabel(groupCheck_single_trap_light_7_enabled);
        label_single_trap_light_7_position->setObjectName(QString::fromUtf8("label_single_trap_light_7_position"));

        gridLayout_single_trap_light_7->addWidget(label_single_trap_light_7_position, 1, 0, 1, 1);

        vect3_single_trap_light_7_position_x = new MyLineEdit(groupCheck_single_trap_light_7_enabled);
        vect3_single_trap_light_7_position_x->setObjectName(QString::fromUtf8("vect3_single_trap_light_7_position_x"));

        gridLayout_single_trap_light_7->addWidget(vect3_single_trap_light_7_position_x, 1, 1, 1, 1);

        vect3_single_trap_light_7_position_y = new MyLineEdit(groupCheck_single_trap_light_7_enabled);
        vect3_single_trap_light_7_position_y->setObjectName(QString::fromUtf8("vect3_single_trap_light_7_position_y"));

        gridLayout_single_trap_light_7->addWidget(vect3_single_trap_light_7_position_y, 1, 2, 1, 1);

        vect3_single_trap_light_7_position_z = new MyLineEdit(groupCheck_single_trap_light_7_enabled);
        vect3_single_trap_light_7_position_z->setObjectName(QString::fromUtf8("vect3_single_trap_light_7_position_z"));

        gridLayout_single_trap_light_7->addWidget(vect3_single_trap_light_7_position_z, 1, 3, 1, 1);

        pushButton_single_trap_light_7_place_camera = new QPushButton(groupCheck_single_trap_light_7_enabled);
        pushButton_single_trap_light_7_place_camera->setObjectName(QString::fromUtf8("pushButton_single_trap_light_7_place_camera"));

        gridLayout_single_trap_light_7->addWidget(pushButton_single_trap_light_7_place_camera, 1, 4, 1, 1);

        label_single_trap_light_7_size = new QLabel(groupCheck_single_trap_light_7_enabled);
        label_single_trap_light_7_size->setObjectName(QString::fromUtf8("label_single_trap_light_7_size"));

        gridLayout_single_trap_light_7->addWidget(label_single_trap_light_7_size, 2, 0, 1, 1);

        logedit_single_trap_light_7_size = new MyLineEdit(groupCheck_single_trap_light_7_enabled);
        logedit_single_trap_light_7_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_7_size"));

        gridLayout_single_trap_light_7->addWidget(logedit_single_trap_light_7_size, 2, 1, 1, 2);

        label_single_trap_light_7_size2 = new QLabel(groupCheck_single_trap_light_7_enabled);
        label_single_trap_light_7_size2->setObjectName(QString::fromUtf8("label_single_trap_light_7_size2"));

        gridLayout_single_trap_light_7->addWidget(label_single_trap_light_7_size2, 2, 3, 1, 1);

        logedit_single_trap_light_7_size2 = new MyLineEdit(groupCheck_single_trap_light_7_enabled);
        logedit_single_trap_light_7_size2->setObjectName(QString::fromUtf8("logedit_single_trap_light_7_size2"));

        gridLayout_single_trap_light_7->addWidget(logedit_single_trap_light_7_size2, 2, 4, 1, 1);

        label_single_trap_light_7_thickness = new QLabel(groupCheck_single_trap_light_7_enabled);
        label_single_trap_light_7_thickness->setObjectName(QString::fromUtf8("label_single_trap_light_7_thickness"));

        gridLayout_single_trap_light_7->addWidget(label_single_trap_light_7_thickness, 3, 0, 1, 1);

        logedit_single_trap_light_7_thickness = new MyLineEdit(groupCheck_single_trap_light_7_enabled);
        logedit_single_trap_light_7_thickness->setObjectName(QString::fromUtf8("logedit_single_trap_light_7_thickness"));

        gridLayout_single_trap_light_7->addWidget(logedit_single_trap_light_7_thickness, 3, 1, 1, 2);

        label_single_trap_light_7_rotation = new QLabel(groupCheck_single_trap_light_7_enabled);
        label_single_trap_light_7_rotation->setObjectName(QString::fromUtf8("label_single_trap_light_7_rotation"));

        gridLayout_single_trap_light_7->addWidget(label_single_trap_light_7_rotation, 4, 0, 1, 1);

        spinboxd3_single_trap_light_7_rotation_x = new MyDoubleSpinBox(groupCheck_single_trap_light_7_enabled);
        spinboxd3_single_trap_light_7_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_7_rotation_x"));

        gridLayout_single_trap_light_7->addWidget(spinboxd3_single_trap_light_7_rotation_x, 4, 1, 1, 1);

        spinboxd3_single_trap_light_7_rotation_y = new MyDoubleSpinBox(groupCheck_single_trap_light_7_enabled);
        spinboxd3_single_trap_light_7_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_7_rotation_y"));

        gridLayout_single_trap_light_7->addWidget(spinboxd3_single_trap_light_7_rotation_y, 4, 2, 1, 1);

        spinboxd3_single_trap_light_7_rotation_z = new MyDoubleSpinBox(groupCheck_single_trap_light_7_enabled);
        spinboxd3_single_trap_light_7_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_7_rotation_z"));

        gridLayout_single_trap_light_7->addWidget(spinboxd3_single_trap_light_7_rotation_z, 4, 3, 1, 1);

        label_single_trap_light_7_intensity = new QLabel(groupCheck_single_trap_light_7_enabled);
        label_single_trap_light_7_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_7_intensity"));

        gridLayout_single_trap_light_7->addWidget(label_single_trap_light_7_intensity, 5, 0, 1, 1);

        logedit_single_trap_light_7_intensity = new MyLineEdit(groupCheck_single_trap_light_7_enabled);
        logedit_single_trap_light_7_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_7_intensity"));

        gridLayout_single_trap_light_7->addWidget(logedit_single_trap_light_7_intensity, 5, 1, 1, 2);

        label_single_trap_light_7_color = new QLabel(groupCheck_single_trap_light_7_enabled);
        label_single_trap_light_7_color->setObjectName(QString::fromUtf8("label_single_trap_light_7_color"));

        gridLayout_single_trap_light_7->addWidget(label_single_trap_light_7_color, 6, 0, 1, 1);

        colorButton_single_trap_light_7_color = new MyColorButton(groupCheck_single_trap_light_7_enabled);
        colorButton_single_trap_light_7_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_7_color"));

        gridLayout_single_trap_light_7->addWidget(colorButton_single_trap_light_7_color, 6, 1, 1, 1);

        label_single_trap_light_7_gradient_color = new QLabel(groupCheck_single_trap_light_7_enabled);
        label_single_trap_light_7_gradient_color->setObjectName(QString::fromUtf8("label_single_trap_light_7_gradient_color"));

        gridLayout_single_trap_light_7->addWidget(label_single_trap_light_7_gradient_color, 6, 2, 1, 1);

        colorButton_single_trap_light_7_gradient_color = new MyColorButton(groupCheck_single_trap_light_7_enabled);
        colorButton_single_trap_light_7_gradient_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_7_gradient_color"));

        gridLayout_single_trap_light_7->addWidget(colorButton_single_trap_light_7_gradient_color, 6, 3, 1, 2);

        label_single_trap_light_7_visibility = new QLabel(groupCheck_single_trap_light_7_enabled);
        label_single_trap_light_7_visibility->setObjectName(QString::fromUtf8("label_single_trap_light_7_visibility"));

        gridLayout_single_trap_light_7->addWidget(label_single_trap_light_7_visibility, 7, 0, 1, 1);

        logedit_single_trap_light_7_visibility = new MyLineEdit(groupCheck_single_trap_light_7_enabled);
        logedit_single_trap_light_7_visibility->setObjectName(QString::fromUtf8("logedit_single_trap_light_7_visibility"));

        gridLayout_single_trap_light_7->addWidget(logedit_single_trap_light_7_visibility, 7, 1, 1, 2);

        label_single_trap_light_7_max_distance = new QLabel(groupCheck_single_trap_light_7_enabled);
        label_single_trap_light_7_max_distance->setObjectName(QString::fromUtf8("label_single_trap_light_7_max_distance"));

        gridLayout_single_trap_light_7->addWidget(label_single_trap_light_7_max_distance, 7, 3, 1, 1);

        logedit_single_trap_light_7_max_distance = new MyLineEdit(groupCheck_single_trap_light_7_enabled);
        logedit_single_trap_light_7_max_distance->setObjectName(QString::fromUtf8("logedit_single_trap_light_7_max_distance"));

        gridLayout_single_trap_light_7->addWidget(logedit_single_trap_light_7_max_distance, 7, 4, 1, 1);

        label_single_trap_light_7_sharpening = new QLabel(groupCheck_single_trap_light_7_enabled);
        label_single_trap_light_7_sharpening->setObjectName(QString::fromUtf8("label_single_trap_light_7_sharpening"));

        gridLayout_single_trap_light_7->addWidget(label_single_trap_light_7_sharpening, 8, 0, 1, 1);

        logedit_single_trap_light_7_sharpening = new MyLineEdit(groupCheck_single_trap_light_7_enabled);
        logedit_single_trap_light_7_sharpening->setObjectName(QString::fromUtf8("logedit_single_trap_light_7_sharpening"));

        gridLayout_single_trap_light_7->addWidget(logedit_single_trap_light_7_sharpening, 8, 1, 1, 2);

        label_single_trap_light_7_blur = new QLabel(groupCheck_single_trap_light_7_enabled);
        label_single_trap_light_7_blur->setObjectName(QString::fromUtf8("label_single_trap_light_7_blur"));

        gridLayout_single_trap_light_7->addWidget(label_single_trap_light_7_blur, 8, 3, 1, 1);

        logedit_single_trap_light_7_blur = new MyLineEdit(groupCheck_single_trap_light_7_enabled);
        logedit_single_trap_light_7_blur->setObjectName(QString::fromUtf8("logedit_single_trap_light_7_blur"));

        gridLayout_single_trap_light_7->addWidget(logedit_single_trap_light_7_blur, 8, 4, 1, 1);

        label_single_trap_light_7_solid_intensity = new QLabel(groupCheck_single_trap_light_7_enabled);
        label_single_trap_light_7_solid_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_7_solid_intensity"));

        gridLayout_single_trap_light_7->addWidget(label_single_trap_light_7_solid_intensity, 9, 0, 1, 1);

        logedit_single_trap_light_7_solid_intensity = new MyLineEdit(groupCheck_single_trap_light_7_enabled);
        logedit_single_trap_light_7_solid_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_7_solid_intensity"));

        gridLayout_single_trap_light_7->addWidget(logedit_single_trap_light_7_solid_intensity, 9, 1, 1, 2);

        label_single_trap_light_7_softness = new QLabel(groupCheck_single_trap_light_7_enabled);
        label_single_trap_light_7_softness->setObjectName(QString::fromUtf8("label_single_trap_light_7_softness"));

        gridLayout_single_trap_light_7->addWidget(label_single_trap_light_7_softness, 9, 3, 1, 1);

        logedit_single_trap_light_7_softness = new MyLineEdit(groupCheck_single_trap_light_7_enabled);
        logedit_single_trap_light_7_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_7_softness"));

        gridLayout_single_trap_light_7->addWidget(logedit_single_trap_light_7_softness, 9, 4, 1, 1);

        label_single_trap_light_7_relative_size = new QLabel(groupCheck_single_trap_light_7_enabled);
        label_single_trap_light_7_relative_size->setObjectName(QString::fromUtf8("label_single_trap_light_7_relative_size"));

        gridLayout_single_trap_light_7->addWidget(label_single_trap_light_7_relative_size, 10, 0, 1, 1);

        logedit_single_trap_light_7_relative_size = new MyLineEdit(groupCheck_single_trap_light_7_enabled);
        logedit_single_trap_light_7_relative_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_7_relative_size"));

        gridLayout_single_trap_light_7->addWidget(logedit_single_trap_light_7_relative_size, 10, 1, 1, 2);

        checkBox_single_trap_light_7_pre_transformed = new MyCheckBox(groupCheck_single_trap_light_7_enabled);
        checkBox_single_trap_light_7_pre_transformed->setObjectName(QString::fromUtf8("checkBox_single_trap_light_7_pre_transformed"));

        gridLayout_single_trap_light_7->addWidget(checkBox_single_trap_light_7_pre_transformed, 11, 0, 1, 1);

        label_single_trap_light_7_position_mode = new QLabel(groupCheck_single_trap_light_7_enabled);
        label_single_trap_light_7_position_mode->setObjectName(QString::fromUtf8("label_single_trap_light_7_position_mode"));

        gridLayout_single_trap_light_7->addWidget(label_single_trap_light_7_position_mode, 12, 0, 1, 1);

        comboBox_single_trap_light_7_position_mode = new MyComboBox(groupCheck_single_trap_light_7_enabled);
        comboBox_single_trap_light_7_position_mode->addItem(QString());
        comboBox_single_trap_light_7_position_mode->addItem(QString());
        comboBox_single_trap_light_7_position_mode->addItem(QString());
        comboBox_single_trap_light_7_position_mode->addItem(QString());
        comboBox_single_trap_light_7_position_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_7_position_mode"));

        gridLayout_single_trap_light_7->addWidget(comboBox_single_trap_light_7_position_mode, 12, 1, 1, 2);

        label_single_trap_light_7_coloring_mode = new QLabel(groupCheck_single_trap_light_7_enabled);
        label_single_trap_light_7_coloring_mode->setObjectName(QString::fromUtf8("label_single_trap_light_7_coloring_mode"));

        gridLayout_single_trap_light_7->addWidget(label_single_trap_light_7_coloring_mode, 13, 0, 1, 1);

        comboBox_single_trap_light_7_coloring_mode = new MyComboBox(groupCheck_single_trap_light_7_enabled);
        comboBox_single_trap_light_7_coloring_mode->addItem(QString());
        comboBox_single_trap_light_7_coloring_mode->addItem(QString());
        comboBox_single_trap_light_7_coloring_mode->addItem(QString());
        comboBox_single_trap_light_7_coloring_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_7_coloring_mode"));

        gridLayout_single_trap_light_7->addWidget(comboBox_single_trap_light_7_coloring_mode, 13, 1, 1, 2);

        label_single_trap_light_7_falloff_type = new QLabel(groupCheck_single_trap_light_7_enabled);
        label_single_trap_light_7_falloff_type->setObjectName(QString::fromUtf8("label_single_trap_light_7_falloff_type"));

        gridLayout_single_trap_light_7->addWidget(label_single_trap_light_7_falloff_type, 14, 0, 1, 1);

        comboBox_single_trap_light_7_falloff_type = new MyComboBox(groupCheck_single_trap_light_7_enabled);
        comboBox_single_trap_light_7_falloff_type->addItem(QString());
        comboBox_single_trap_light_7_falloff_type->addItem(QString());
        comboBox_single_trap_light_7_falloff_type->addItem(QString());
        comboBox_single_trap_light_7_falloff_type->addItem(QString());
        comboBox_single_trap_light_7_falloff_type->addItem(QString());
        comboBox_single_trap_light_7_falloff_type->setObjectName(QString::fromUtf8("comboBox_single_trap_light_7_falloff_type"));

        gridLayout_single_trap_light_7->addWidget(comboBox_single_trap_light_7_falloff_type, 14, 1, 1, 2);

        label_single_trap_light_7_edge_softness = new QLabel(groupCheck_single_trap_light_7_enabled);
        label_single_trap_light_7_edge_softness->setObjectName(QString::fromUtf8("label_single_trap_light_7_edge_softness"));

        gridLayout_single_trap_light_7->addWidget(label_single_trap_light_7_edge_softness, 15, 0, 1, 1);

        logedit_single_trap_light_7_edge_softness = new MyLineEdit(groupCheck_single_trap_light_7_enabled);
        logedit_single_trap_light_7_edge_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_7_edge_softness"));

        gridLayout_single_trap_light_7->addWidget(logedit_single_trap_light_7_edge_softness, 15, 1, 1, 2);

        label_single_trap_light_7_anim_orbit_radius = new QLabel(groupCheck_single_trap_light_7_enabled);
        label_single_trap_light_7_anim_orbit_radius->setObjectName(QString::fromUtf8("label_single_trap_light_7_anim_orbit_radius"));

        gridLayout_single_trap_light_7->addWidget(label_single_trap_light_7_anim_orbit_radius, 16, 0, 1, 1);

        logedit_single_trap_light_7_anim_orbit_radius = new MyLineEdit(groupCheck_single_trap_light_7_enabled);
        logedit_single_trap_light_7_anim_orbit_radius->setObjectName(QString::fromUtf8("logedit_single_trap_light_7_anim_orbit_radius"));

        gridLayout_single_trap_light_7->addWidget(logedit_single_trap_light_7_anim_orbit_radius, 16, 1, 1, 1);

        logedit_single_trap_light_7_anim_orbit_speed = new MyLineEdit(groupCheck_single_trap_light_7_enabled);
        logedit_single_trap_light_7_anim_orbit_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_7_anim_orbit_speed"));

        gridLayout_single_trap_light_7->addWidget(logedit_single_trap_light_7_anim_orbit_speed, 16, 2, 1, 1);

        logedit_single_trap_light_7_anim_pulsate_speed = new MyLineEdit(groupCheck_single_trap_light_7_enabled);
        logedit_single_trap_light_7_anim_pulsate_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_7_anim_pulsate_speed"));

        gridLayout_single_trap_light_7->addWidget(logedit_single_trap_light_7_anim_pulsate_speed, 16, 3, 1, 1);

        logedit_single_trap_light_7_anim_pulsate_amount = new MyLineEdit(groupCheck_single_trap_light_7_enabled);
        logedit_single_trap_light_7_anim_pulsate_amount->setObjectName(QString::fromUtf8("logedit_single_trap_light_7_anim_pulsate_amount"));

        gridLayout_single_trap_light_7->addWidget(logedit_single_trap_light_7_anim_pulsate_amount, 16, 4, 1, 1);

        pushButton_single_trap_light_7_place_surface = new QPushButton(groupCheck_single_trap_light_7_enabled);
        pushButton_single_trap_light_7_place_surface->setObjectName(QString::fromUtf8("pushButton_single_trap_light_7_place_surface"));

        gridLayout_single_trap_light_7->addWidget(pushButton_single_trap_light_7_place_surface, 17, 0, 1, 5);

        pushButton_single_trap_light_7_place_target = new QPushButton(groupCheck_single_trap_light_7_enabled);
        pushButton_single_trap_light_7_place_target->setObjectName(QString::fromUtf8("pushButton_single_trap_light_7_place_target"));

        gridLayout_single_trap_light_7->addWidget(pushButton_single_trap_light_7_place_target, 18, 0, 1, 5);


        verticalLayout_single_trap_layers->addWidget(groupCheck_single_trap_light_7_enabled);

        groupCheck_single_trap_light_8_enabled = new MyGroupBox(scrollAreaWidgetContents_single_trap);
        groupCheck_single_trap_light_8_enabled->setObjectName(QString::fromUtf8("groupCheck_single_trap_light_8_enabled"));
        groupCheck_single_trap_light_8_enabled->setCheckable(true);
        gridLayout_single_trap_light_8 = new QGridLayout(groupCheck_single_trap_light_8_enabled);
        gridLayout_single_trap_light_8->setSpacing(2);
        gridLayout_single_trap_light_8->setObjectName(QString::fromUtf8("gridLayout_single_trap_light_8"));
        label_single_trap_light_8_shape = new QLabel(groupCheck_single_trap_light_8_enabled);
        label_single_trap_light_8_shape->setObjectName(QString::fromUtf8("label_single_trap_light_8_shape"));

        gridLayout_single_trap_light_8->addWidget(label_single_trap_light_8_shape, 0, 0, 1, 1);

        comboBox_single_trap_light_8_shape = new MyComboBox(groupCheck_single_trap_light_8_enabled);
        comboBox_single_trap_light_8_shape->addItem(QString());
        comboBox_single_trap_light_8_shape->addItem(QString());
        comboBox_single_trap_light_8_shape->addItem(QString());
        comboBox_single_trap_light_8_shape->addItem(QString());
        comboBox_single_trap_light_8_shape->addItem(QString());
        comboBox_single_trap_light_8_shape->addItem(QString());
        comboBox_single_trap_light_8_shape->addItem(QString());
        comboBox_single_trap_light_8_shape->addItem(QString());
        comboBox_single_trap_light_8_shape->addItem(QString());
        comboBox_single_trap_light_8_shape->addItem(QString());
        comboBox_single_trap_light_8_shape->addItem(QString());
        comboBox_single_trap_light_8_shape->addItem(QString());
        comboBox_single_trap_light_8_shape->addItem(QString());
        comboBox_single_trap_light_8_shape->addItem(QString());
        comboBox_single_trap_light_8_shape->setObjectName(QString::fromUtf8("comboBox_single_trap_light_8_shape"));

        gridLayout_single_trap_light_8->addWidget(comboBox_single_trap_light_8_shape, 0, 1, 1, 2);

        label_single_trap_light_8_position = new QLabel(groupCheck_single_trap_light_8_enabled);
        label_single_trap_light_8_position->setObjectName(QString::fromUtf8("label_single_trap_light_8_position"));

        gridLayout_single_trap_light_8->addWidget(label_single_trap_light_8_position, 1, 0, 1, 1);

        vect3_single_trap_light_8_position_x = new MyLineEdit(groupCheck_single_trap_light_8_enabled);
        vect3_single_trap_light_8_position_x->setObjectName(QString::fromUtf8("vect3_single_trap_light_8_position_x"));

        gridLayout_single_trap_light_8->addWidget(vect3_single_trap_light_8_position_x, 1, 1, 1, 1);

        vect3_single_trap_light_8_position_y = new MyLineEdit(groupCheck_single_trap_light_8_enabled);
        vect3_single_trap_light_8_position_y->setObjectName(QString::fromUtf8("vect3_single_trap_light_8_position_y"));

        gridLayout_single_trap_light_8->addWidget(vect3_single_trap_light_8_position_y, 1, 2, 1, 1);

        vect3_single_trap_light_8_position_z = new MyLineEdit(groupCheck_single_trap_light_8_enabled);
        vect3_single_trap_light_8_position_z->setObjectName(QString::fromUtf8("vect3_single_trap_light_8_position_z"));

        gridLayout_single_trap_light_8->addWidget(vect3_single_trap_light_8_position_z, 1, 3, 1, 1);

        pushButton_single_trap_light_8_place_camera = new QPushButton(groupCheck_single_trap_light_8_enabled);
        pushButton_single_trap_light_8_place_camera->setObjectName(QString::fromUtf8("pushButton_single_trap_light_8_place_camera"));

        gridLayout_single_trap_light_8->addWidget(pushButton_single_trap_light_8_place_camera, 1, 4, 1, 1);

        label_single_trap_light_8_size = new QLabel(groupCheck_single_trap_light_8_enabled);
        label_single_trap_light_8_size->setObjectName(QString::fromUtf8("label_single_trap_light_8_size"));

        gridLayout_single_trap_light_8->addWidget(label_single_trap_light_8_size, 2, 0, 1, 1);

        logedit_single_trap_light_8_size = new MyLineEdit(groupCheck_single_trap_light_8_enabled);
        logedit_single_trap_light_8_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_8_size"));

        gridLayout_single_trap_light_8->addWidget(logedit_single_trap_light_8_size, 2, 1, 1, 2);

        label_single_trap_light_8_size2 = new QLabel(groupCheck_single_trap_light_8_enabled);
        label_single_trap_light_8_size2->setObjectName(QString::fromUtf8("label_single_trap_light_8_size2"));

        gridLayout_single_trap_light_8->addWidget(label_single_trap_light_8_size2, 2, 3, 1, 1);

        logedit_single_trap_light_8_size2 = new MyLineEdit(groupCheck_single_trap_light_8_enabled);
        logedit_single_trap_light_8_size2->setObjectName(QString::fromUtf8("logedit_single_trap_light_8_size2"));

        gridLayout_single_trap_light_8->addWidget(logedit_single_trap_light_8_size2, 2, 4, 1, 1);

        label_single_trap_light_8_thickness = new QLabel(groupCheck_single_trap_light_8_enabled);
        label_single_trap_light_8_thickness->setObjectName(QString::fromUtf8("label_single_trap_light_8_thickness"));

        gridLayout_single_trap_light_8->addWidget(label_single_trap_light_8_thickness, 3, 0, 1, 1);

        logedit_single_trap_light_8_thickness = new MyLineEdit(groupCheck_single_trap_light_8_enabled);
        logedit_single_trap_light_8_thickness->setObjectName(QString::fromUtf8("logedit_single_trap_light_8_thickness"));

        gridLayout_single_trap_light_8->addWidget(logedit_single_trap_light_8_thickness, 3, 1, 1, 2);

        label_single_trap_light_8_rotation = new QLabel(groupCheck_single_trap_light_8_enabled);
        label_single_trap_light_8_rotation->setObjectName(QString::fromUtf8("label_single_trap_light_8_rotation"));

        gridLayout_single_trap_light_8->addWidget(label_single_trap_light_8_rotation, 4, 0, 1, 1);

        spinboxd3_single_trap_light_8_rotation_x = new MyDoubleSpinBox(groupCheck_single_trap_light_8_enabled);
        spinboxd3_single_trap_light_8_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_8_rotation_x"));

        gridLayout_single_trap_light_8->addWidget(spinboxd3_single_trap_light_8_rotation_x, 4, 1, 1, 1);

        spinboxd3_single_trap_light_8_rotation_y = new MyDoubleSpinBox(groupCheck_single_trap_light_8_enabled);
        spinboxd3_single_trap_light_8_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_8_rotation_y"));

        gridLayout_single_trap_light_8->addWidget(spinboxd3_single_trap_light_8_rotation_y, 4, 2, 1, 1);

        spinboxd3_single_trap_light_8_rotation_z = new MyDoubleSpinBox(groupCheck_single_trap_light_8_enabled);
        spinboxd3_single_trap_light_8_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_8_rotation_z"));

        gridLayout_single_trap_light_8->addWidget(spinboxd3_single_trap_light_8_rotation_z, 4, 3, 1, 1);

        label_single_trap_light_8_intensity = new QLabel(groupCheck_single_trap_light_8_enabled);
        label_single_trap_light_8_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_8_intensity"));

        gridLayout_single_trap_light_8->addWidget(label_single_trap_light_8_intensity, 5, 0, 1, 1);

        logedit_single_trap_light_8_intensity = new MyLineEdit(groupCheck_single_trap_light_8_enabled);
        logedit_single_trap_light_8_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_8_intensity"));

        gridLayout_single_trap_light_8->addWidget(logedit_single_trap_light_8_intensity, 5, 1, 1, 2);

        label_single_trap_light_8_color = new QLabel(groupCheck_single_trap_light_8_enabled);
        label_single_trap_light_8_color->setObjectName(QString::fromUtf8("label_single_trap_light_8_color"));

        gridLayout_single_trap_light_8->addWidget(label_single_trap_light_8_color, 6, 0, 1, 1);

        colorButton_single_trap_light_8_color = new MyColorButton(groupCheck_single_trap_light_8_enabled);
        colorButton_single_trap_light_8_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_8_color"));

        gridLayout_single_trap_light_8->addWidget(colorButton_single_trap_light_8_color, 6, 1, 1, 1);

        label_single_trap_light_8_gradient_color = new QLabel(groupCheck_single_trap_light_8_enabled);
        label_single_trap_light_8_gradient_color->setObjectName(QString::fromUtf8("label_single_trap_light_8_gradient_color"));

        gridLayout_single_trap_light_8->addWidget(label_single_trap_light_8_gradient_color, 6, 2, 1, 1);

        colorButton_single_trap_light_8_gradient_color = new MyColorButton(groupCheck_single_trap_light_8_enabled);
        colorButton_single_trap_light_8_gradient_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_8_gradient_color"));

        gridLayout_single_trap_light_8->addWidget(colorButton_single_trap_light_8_gradient_color, 6, 3, 1, 2);

        label_single_trap_light_8_visibility = new QLabel(groupCheck_single_trap_light_8_enabled);
        label_single_trap_light_8_visibility->setObjectName(QString::fromUtf8("label_single_trap_light_8_visibility"));

        gridLayout_single_trap_light_8->addWidget(label_single_trap_light_8_visibility, 7, 0, 1, 1);

        logedit_single_trap_light_8_visibility = new MyLineEdit(groupCheck_single_trap_light_8_enabled);
        logedit_single_trap_light_8_visibility->setObjectName(QString::fromUtf8("logedit_single_trap_light_8_visibility"));

        gridLayout_single_trap_light_8->addWidget(logedit_single_trap_light_8_visibility, 7, 1, 1, 2);

        label_single_trap_light_8_max_distance = new QLabel(groupCheck_single_trap_light_8_enabled);
        label_single_trap_light_8_max_distance->setObjectName(QString::fromUtf8("label_single_trap_light_8_max_distance"));

        gridLayout_single_trap_light_8->addWidget(label_single_trap_light_8_max_distance, 7, 3, 1, 1);

        logedit_single_trap_light_8_max_distance = new MyLineEdit(groupCheck_single_trap_light_8_enabled);
        logedit_single_trap_light_8_max_distance->setObjectName(QString::fromUtf8("logedit_single_trap_light_8_max_distance"));

        gridLayout_single_trap_light_8->addWidget(logedit_single_trap_light_8_max_distance, 7, 4, 1, 1);

        label_single_trap_light_8_sharpening = new QLabel(groupCheck_single_trap_light_8_enabled);
        label_single_trap_light_8_sharpening->setObjectName(QString::fromUtf8("label_single_trap_light_8_sharpening"));

        gridLayout_single_trap_light_8->addWidget(label_single_trap_light_8_sharpening, 8, 0, 1, 1);

        logedit_single_trap_light_8_sharpening = new MyLineEdit(groupCheck_single_trap_light_8_enabled);
        logedit_single_trap_light_8_sharpening->setObjectName(QString::fromUtf8("logedit_single_trap_light_8_sharpening"));

        gridLayout_single_trap_light_8->addWidget(logedit_single_trap_light_8_sharpening, 8, 1, 1, 2);

        label_single_trap_light_8_blur = new QLabel(groupCheck_single_trap_light_8_enabled);
        label_single_trap_light_8_blur->setObjectName(QString::fromUtf8("label_single_trap_light_8_blur"));

        gridLayout_single_trap_light_8->addWidget(label_single_trap_light_8_blur, 8, 3, 1, 1);

        logedit_single_trap_light_8_blur = new MyLineEdit(groupCheck_single_trap_light_8_enabled);
        logedit_single_trap_light_8_blur->setObjectName(QString::fromUtf8("logedit_single_trap_light_8_blur"));

        gridLayout_single_trap_light_8->addWidget(logedit_single_trap_light_8_blur, 8, 4, 1, 1);

        label_single_trap_light_8_solid_intensity = new QLabel(groupCheck_single_trap_light_8_enabled);
        label_single_trap_light_8_solid_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_8_solid_intensity"));

        gridLayout_single_trap_light_8->addWidget(label_single_trap_light_8_solid_intensity, 9, 0, 1, 1);

        logedit_single_trap_light_8_solid_intensity = new MyLineEdit(groupCheck_single_trap_light_8_enabled);
        logedit_single_trap_light_8_solid_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_8_solid_intensity"));

        gridLayout_single_trap_light_8->addWidget(logedit_single_trap_light_8_solid_intensity, 9, 1, 1, 2);

        label_single_trap_light_8_softness = new QLabel(groupCheck_single_trap_light_8_enabled);
        label_single_trap_light_8_softness->setObjectName(QString::fromUtf8("label_single_trap_light_8_softness"));

        gridLayout_single_trap_light_8->addWidget(label_single_trap_light_8_softness, 9, 3, 1, 1);

        logedit_single_trap_light_8_softness = new MyLineEdit(groupCheck_single_trap_light_8_enabled);
        logedit_single_trap_light_8_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_8_softness"));

        gridLayout_single_trap_light_8->addWidget(logedit_single_trap_light_8_softness, 9, 4, 1, 1);

        label_single_trap_light_8_relative_size = new QLabel(groupCheck_single_trap_light_8_enabled);
        label_single_trap_light_8_relative_size->setObjectName(QString::fromUtf8("label_single_trap_light_8_relative_size"));

        gridLayout_single_trap_light_8->addWidget(label_single_trap_light_8_relative_size, 10, 0, 1, 1);

        logedit_single_trap_light_8_relative_size = new MyLineEdit(groupCheck_single_trap_light_8_enabled);
        logedit_single_trap_light_8_relative_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_8_relative_size"));

        gridLayout_single_trap_light_8->addWidget(logedit_single_trap_light_8_relative_size, 10, 1, 1, 2);

        checkBox_single_trap_light_8_pre_transformed = new MyCheckBox(groupCheck_single_trap_light_8_enabled);
        checkBox_single_trap_light_8_pre_transformed->setObjectName(QString::fromUtf8("checkBox_single_trap_light_8_pre_transformed"));

        gridLayout_single_trap_light_8->addWidget(checkBox_single_trap_light_8_pre_transformed, 11, 0, 1, 1);

        label_single_trap_light_8_position_mode = new QLabel(groupCheck_single_trap_light_8_enabled);
        label_single_trap_light_8_position_mode->setObjectName(QString::fromUtf8("label_single_trap_light_8_position_mode"));

        gridLayout_single_trap_light_8->addWidget(label_single_trap_light_8_position_mode, 12, 0, 1, 1);

        comboBox_single_trap_light_8_position_mode = new MyComboBox(groupCheck_single_trap_light_8_enabled);
        comboBox_single_trap_light_8_position_mode->addItem(QString());
        comboBox_single_trap_light_8_position_mode->addItem(QString());
        comboBox_single_trap_light_8_position_mode->addItem(QString());
        comboBox_single_trap_light_8_position_mode->addItem(QString());
        comboBox_single_trap_light_8_position_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_8_position_mode"));

        gridLayout_single_trap_light_8->addWidget(comboBox_single_trap_light_8_position_mode, 12, 1, 1, 2);

        label_single_trap_light_8_coloring_mode = new QLabel(groupCheck_single_trap_light_8_enabled);
        label_single_trap_light_8_coloring_mode->setObjectName(QString::fromUtf8("label_single_trap_light_8_coloring_mode"));

        gridLayout_single_trap_light_8->addWidget(label_single_trap_light_8_coloring_mode, 13, 0, 1, 1);

        comboBox_single_trap_light_8_coloring_mode = new MyComboBox(groupCheck_single_trap_light_8_enabled);
        comboBox_single_trap_light_8_coloring_mode->addItem(QString());
        comboBox_single_trap_light_8_coloring_mode->addItem(QString());
        comboBox_single_trap_light_8_coloring_mode->addItem(QString());
        comboBox_single_trap_light_8_coloring_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_8_coloring_mode"));

        gridLayout_single_trap_light_8->addWidget(comboBox_single_trap_light_8_coloring_mode, 13, 1, 1, 2);

        label_single_trap_light_8_falloff_type = new QLabel(groupCheck_single_trap_light_8_enabled);
        label_single_trap_light_8_falloff_type->setObjectName(QString::fromUtf8("label_single_trap_light_8_falloff_type"));

        gridLayout_single_trap_light_8->addWidget(label_single_trap_light_8_falloff_type, 14, 0, 1, 1);

        comboBox_single_trap_light_8_falloff_type = new MyComboBox(groupCheck_single_trap_light_8_enabled);
        comboBox_single_trap_light_8_falloff_type->addItem(QString());
        comboBox_single_trap_light_8_falloff_type->addItem(QString());
        comboBox_single_trap_light_8_falloff_type->addItem(QString());
        comboBox_single_trap_light_8_falloff_type->addItem(QString());
        comboBox_single_trap_light_8_falloff_type->addItem(QString());
        comboBox_single_trap_light_8_falloff_type->setObjectName(QString::fromUtf8("comboBox_single_trap_light_8_falloff_type"));

        gridLayout_single_trap_light_8->addWidget(comboBox_single_trap_light_8_falloff_type, 14, 1, 1, 2);

        label_single_trap_light_8_edge_softness = new QLabel(groupCheck_single_trap_light_8_enabled);
        label_single_trap_light_8_edge_softness->setObjectName(QString::fromUtf8("label_single_trap_light_8_edge_softness"));

        gridLayout_single_trap_light_8->addWidget(label_single_trap_light_8_edge_softness, 15, 0, 1, 1);

        logedit_single_trap_light_8_edge_softness = new MyLineEdit(groupCheck_single_trap_light_8_enabled);
        logedit_single_trap_light_8_edge_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_8_edge_softness"));

        gridLayout_single_trap_light_8->addWidget(logedit_single_trap_light_8_edge_softness, 15, 1, 1, 2);

        label_single_trap_light_8_anim_orbit_radius = new QLabel(groupCheck_single_trap_light_8_enabled);
        label_single_trap_light_8_anim_orbit_radius->setObjectName(QString::fromUtf8("label_single_trap_light_8_anim_orbit_radius"));

        gridLayout_single_trap_light_8->addWidget(label_single_trap_light_8_anim_orbit_radius, 16, 0, 1, 1);

        logedit_single_trap_light_8_anim_orbit_radius = new MyLineEdit(groupCheck_single_trap_light_8_enabled);
        logedit_single_trap_light_8_anim_orbit_radius->setObjectName(QString::fromUtf8("logedit_single_trap_light_8_anim_orbit_radius"));

        gridLayout_single_trap_light_8->addWidget(logedit_single_trap_light_8_anim_orbit_radius, 16, 1, 1, 1);

        logedit_single_trap_light_8_anim_orbit_speed = new MyLineEdit(groupCheck_single_trap_light_8_enabled);
        logedit_single_trap_light_8_anim_orbit_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_8_anim_orbit_speed"));

        gridLayout_single_trap_light_8->addWidget(logedit_single_trap_light_8_anim_orbit_speed, 16, 2, 1, 1);

        logedit_single_trap_light_8_anim_pulsate_speed = new MyLineEdit(groupCheck_single_trap_light_8_enabled);
        logedit_single_trap_light_8_anim_pulsate_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_8_anim_pulsate_speed"));

        gridLayout_single_trap_light_8->addWidget(logedit_single_trap_light_8_anim_pulsate_speed, 16, 3, 1, 1);

        logedit_single_trap_light_8_anim_pulsate_amount = new MyLineEdit(groupCheck_single_trap_light_8_enabled);
        logedit_single_trap_light_8_anim_pulsate_amount->setObjectName(QString::fromUtf8("logedit_single_trap_light_8_anim_pulsate_amount"));

        gridLayout_single_trap_light_8->addWidget(logedit_single_trap_light_8_anim_pulsate_amount, 16, 4, 1, 1);

        pushButton_single_trap_light_8_place_surface = new QPushButton(groupCheck_single_trap_light_8_enabled);
        pushButton_single_trap_light_8_place_surface->setObjectName(QString::fromUtf8("pushButton_single_trap_light_8_place_surface"));

        gridLayout_single_trap_light_8->addWidget(pushButton_single_trap_light_8_place_surface, 17, 0, 1, 5);

        pushButton_single_trap_light_8_place_target = new QPushButton(groupCheck_single_trap_light_8_enabled);
        pushButton_single_trap_light_8_place_target->setObjectName(QString::fromUtf8("pushButton_single_trap_light_8_place_target"));

        gridLayout_single_trap_light_8->addWidget(pushButton_single_trap_light_8_place_target, 18, 0, 1, 5);


        verticalLayout_single_trap_layers->addWidget(groupCheck_single_trap_light_8_enabled);

        groupCheck_single_trap_light_9_enabled = new MyGroupBox(scrollAreaWidgetContents_single_trap);
        groupCheck_single_trap_light_9_enabled->setObjectName(QString::fromUtf8("groupCheck_single_trap_light_9_enabled"));
        groupCheck_single_trap_light_9_enabled->setCheckable(true);
        gridLayout_single_trap_light_9 = new QGridLayout(groupCheck_single_trap_light_9_enabled);
        gridLayout_single_trap_light_9->setSpacing(2);
        gridLayout_single_trap_light_9->setObjectName(QString::fromUtf8("gridLayout_single_trap_light_9"));
        label_single_trap_light_9_shape = new QLabel(groupCheck_single_trap_light_9_enabled);
        label_single_trap_light_9_shape->setObjectName(QString::fromUtf8("label_single_trap_light_9_shape"));

        gridLayout_single_trap_light_9->addWidget(label_single_trap_light_9_shape, 0, 0, 1, 1);

        comboBox_single_trap_light_9_shape = new MyComboBox(groupCheck_single_trap_light_9_enabled);
        comboBox_single_trap_light_9_shape->addItem(QString());
        comboBox_single_trap_light_9_shape->addItem(QString());
        comboBox_single_trap_light_9_shape->addItem(QString());
        comboBox_single_trap_light_9_shape->addItem(QString());
        comboBox_single_trap_light_9_shape->addItem(QString());
        comboBox_single_trap_light_9_shape->addItem(QString());
        comboBox_single_trap_light_9_shape->addItem(QString());
        comboBox_single_trap_light_9_shape->addItem(QString());
        comboBox_single_trap_light_9_shape->addItem(QString());
        comboBox_single_trap_light_9_shape->addItem(QString());
        comboBox_single_trap_light_9_shape->addItem(QString());
        comboBox_single_trap_light_9_shape->addItem(QString());
        comboBox_single_trap_light_9_shape->addItem(QString());
        comboBox_single_trap_light_9_shape->addItem(QString());
        comboBox_single_trap_light_9_shape->setObjectName(QString::fromUtf8("comboBox_single_trap_light_9_shape"));

        gridLayout_single_trap_light_9->addWidget(comboBox_single_trap_light_9_shape, 0, 1, 1, 2);

        label_single_trap_light_9_position = new QLabel(groupCheck_single_trap_light_9_enabled);
        label_single_trap_light_9_position->setObjectName(QString::fromUtf8("label_single_trap_light_9_position"));

        gridLayout_single_trap_light_9->addWidget(label_single_trap_light_9_position, 1, 0, 1, 1);

        vect3_single_trap_light_9_position_x = new MyLineEdit(groupCheck_single_trap_light_9_enabled);
        vect3_single_trap_light_9_position_x->setObjectName(QString::fromUtf8("vect3_single_trap_light_9_position_x"));

        gridLayout_single_trap_light_9->addWidget(vect3_single_trap_light_9_position_x, 1, 1, 1, 1);

        vect3_single_trap_light_9_position_y = new MyLineEdit(groupCheck_single_trap_light_9_enabled);
        vect3_single_trap_light_9_position_y->setObjectName(QString::fromUtf8("vect3_single_trap_light_9_position_y"));

        gridLayout_single_trap_light_9->addWidget(vect3_single_trap_light_9_position_y, 1, 2, 1, 1);

        vect3_single_trap_light_9_position_z = new MyLineEdit(groupCheck_single_trap_light_9_enabled);
        vect3_single_trap_light_9_position_z->setObjectName(QString::fromUtf8("vect3_single_trap_light_9_position_z"));

        gridLayout_single_trap_light_9->addWidget(vect3_single_trap_light_9_position_z, 1, 3, 1, 1);

        pushButton_single_trap_light_9_place_camera = new QPushButton(groupCheck_single_trap_light_9_enabled);
        pushButton_single_trap_light_9_place_camera->setObjectName(QString::fromUtf8("pushButton_single_trap_light_9_place_camera"));

        gridLayout_single_trap_light_9->addWidget(pushButton_single_trap_light_9_place_camera, 1, 4, 1, 1);

        label_single_trap_light_9_size = new QLabel(groupCheck_single_trap_light_9_enabled);
        label_single_trap_light_9_size->setObjectName(QString::fromUtf8("label_single_trap_light_9_size"));

        gridLayout_single_trap_light_9->addWidget(label_single_trap_light_9_size, 2, 0, 1, 1);

        logedit_single_trap_light_9_size = new MyLineEdit(groupCheck_single_trap_light_9_enabled);
        logedit_single_trap_light_9_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_9_size"));

        gridLayout_single_trap_light_9->addWidget(logedit_single_trap_light_9_size, 2, 1, 1, 2);

        label_single_trap_light_9_size2 = new QLabel(groupCheck_single_trap_light_9_enabled);
        label_single_trap_light_9_size2->setObjectName(QString::fromUtf8("label_single_trap_light_9_size2"));

        gridLayout_single_trap_light_9->addWidget(label_single_trap_light_9_size2, 2, 3, 1, 1);

        logedit_single_trap_light_9_size2 = new MyLineEdit(groupCheck_single_trap_light_9_enabled);
        logedit_single_trap_light_9_size2->setObjectName(QString::fromUtf8("logedit_single_trap_light_9_size2"));

        gridLayout_single_trap_light_9->addWidget(logedit_single_trap_light_9_size2, 2, 4, 1, 1);

        label_single_trap_light_9_thickness = new QLabel(groupCheck_single_trap_light_9_enabled);
        label_single_trap_light_9_thickness->setObjectName(QString::fromUtf8("label_single_trap_light_9_thickness"));

        gridLayout_single_trap_light_9->addWidget(label_single_trap_light_9_thickness, 3, 0, 1, 1);

        logedit_single_trap_light_9_thickness = new MyLineEdit(groupCheck_single_trap_light_9_enabled);
        logedit_single_trap_light_9_thickness->setObjectName(QString::fromUtf8("logedit_single_trap_light_9_thickness"));

        gridLayout_single_trap_light_9->addWidget(logedit_single_trap_light_9_thickness, 3, 1, 1, 2);

        label_single_trap_light_9_rotation = new QLabel(groupCheck_single_trap_light_9_enabled);
        label_single_trap_light_9_rotation->setObjectName(QString::fromUtf8("label_single_trap_light_9_rotation"));

        gridLayout_single_trap_light_9->addWidget(label_single_trap_light_9_rotation, 4, 0, 1, 1);

        spinboxd3_single_trap_light_9_rotation_x = new MyDoubleSpinBox(groupCheck_single_trap_light_9_enabled);
        spinboxd3_single_trap_light_9_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_9_rotation_x"));

        gridLayout_single_trap_light_9->addWidget(spinboxd3_single_trap_light_9_rotation_x, 4, 1, 1, 1);

        spinboxd3_single_trap_light_9_rotation_y = new MyDoubleSpinBox(groupCheck_single_trap_light_9_enabled);
        spinboxd3_single_trap_light_9_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_9_rotation_y"));

        gridLayout_single_trap_light_9->addWidget(spinboxd3_single_trap_light_9_rotation_y, 4, 2, 1, 1);

        spinboxd3_single_trap_light_9_rotation_z = new MyDoubleSpinBox(groupCheck_single_trap_light_9_enabled);
        spinboxd3_single_trap_light_9_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_9_rotation_z"));

        gridLayout_single_trap_light_9->addWidget(spinboxd3_single_trap_light_9_rotation_z, 4, 3, 1, 1);

        label_single_trap_light_9_intensity = new QLabel(groupCheck_single_trap_light_9_enabled);
        label_single_trap_light_9_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_9_intensity"));

        gridLayout_single_trap_light_9->addWidget(label_single_trap_light_9_intensity, 5, 0, 1, 1);

        logedit_single_trap_light_9_intensity = new MyLineEdit(groupCheck_single_trap_light_9_enabled);
        logedit_single_trap_light_9_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_9_intensity"));

        gridLayout_single_trap_light_9->addWidget(logedit_single_trap_light_9_intensity, 5, 1, 1, 2);

        label_single_trap_light_9_color = new QLabel(groupCheck_single_trap_light_9_enabled);
        label_single_trap_light_9_color->setObjectName(QString::fromUtf8("label_single_trap_light_9_color"));

        gridLayout_single_trap_light_9->addWidget(label_single_trap_light_9_color, 6, 0, 1, 1);

        colorButton_single_trap_light_9_color = new MyColorButton(groupCheck_single_trap_light_9_enabled);
        colorButton_single_trap_light_9_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_9_color"));

        gridLayout_single_trap_light_9->addWidget(colorButton_single_trap_light_9_color, 6, 1, 1, 1);

        label_single_trap_light_9_gradient_color = new QLabel(groupCheck_single_trap_light_9_enabled);
        label_single_trap_light_9_gradient_color->setObjectName(QString::fromUtf8("label_single_trap_light_9_gradient_color"));

        gridLayout_single_trap_light_9->addWidget(label_single_trap_light_9_gradient_color, 6, 2, 1, 1);

        colorButton_single_trap_light_9_gradient_color = new MyColorButton(groupCheck_single_trap_light_9_enabled);
        colorButton_single_trap_light_9_gradient_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_9_gradient_color"));

        gridLayout_single_trap_light_9->addWidget(colorButton_single_trap_light_9_gradient_color, 6, 3, 1, 2);

        label_single_trap_light_9_visibility = new QLabel(groupCheck_single_trap_light_9_enabled);
        label_single_trap_light_9_visibility->setObjectName(QString::fromUtf8("label_single_trap_light_9_visibility"));

        gridLayout_single_trap_light_9->addWidget(label_single_trap_light_9_visibility, 7, 0, 1, 1);

        logedit_single_trap_light_9_visibility = new MyLineEdit(groupCheck_single_trap_light_9_enabled);
        logedit_single_trap_light_9_visibility->setObjectName(QString::fromUtf8("logedit_single_trap_light_9_visibility"));

        gridLayout_single_trap_light_9->addWidget(logedit_single_trap_light_9_visibility, 7, 1, 1, 2);

        label_single_trap_light_9_max_distance = new QLabel(groupCheck_single_trap_light_9_enabled);
        label_single_trap_light_9_max_distance->setObjectName(QString::fromUtf8("label_single_trap_light_9_max_distance"));

        gridLayout_single_trap_light_9->addWidget(label_single_trap_light_9_max_distance, 7, 3, 1, 1);

        logedit_single_trap_light_9_max_distance = new MyLineEdit(groupCheck_single_trap_light_9_enabled);
        logedit_single_trap_light_9_max_distance->setObjectName(QString::fromUtf8("logedit_single_trap_light_9_max_distance"));

        gridLayout_single_trap_light_9->addWidget(logedit_single_trap_light_9_max_distance, 7, 4, 1, 1);

        label_single_trap_light_9_sharpening = new QLabel(groupCheck_single_trap_light_9_enabled);
        label_single_trap_light_9_sharpening->setObjectName(QString::fromUtf8("label_single_trap_light_9_sharpening"));

        gridLayout_single_trap_light_9->addWidget(label_single_trap_light_9_sharpening, 8, 0, 1, 1);

        logedit_single_trap_light_9_sharpening = new MyLineEdit(groupCheck_single_trap_light_9_enabled);
        logedit_single_trap_light_9_sharpening->setObjectName(QString::fromUtf8("logedit_single_trap_light_9_sharpening"));

        gridLayout_single_trap_light_9->addWidget(logedit_single_trap_light_9_sharpening, 8, 1, 1, 2);

        label_single_trap_light_9_blur = new QLabel(groupCheck_single_trap_light_9_enabled);
        label_single_trap_light_9_blur->setObjectName(QString::fromUtf8("label_single_trap_light_9_blur"));

        gridLayout_single_trap_light_9->addWidget(label_single_trap_light_9_blur, 8, 3, 1, 1);

        logedit_single_trap_light_9_blur = new MyLineEdit(groupCheck_single_trap_light_9_enabled);
        logedit_single_trap_light_9_blur->setObjectName(QString::fromUtf8("logedit_single_trap_light_9_blur"));

        gridLayout_single_trap_light_9->addWidget(logedit_single_trap_light_9_blur, 8, 4, 1, 1);

        label_single_trap_light_9_solid_intensity = new QLabel(groupCheck_single_trap_light_9_enabled);
        label_single_trap_light_9_solid_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_9_solid_intensity"));

        gridLayout_single_trap_light_9->addWidget(label_single_trap_light_9_solid_intensity, 9, 0, 1, 1);

        logedit_single_trap_light_9_solid_intensity = new MyLineEdit(groupCheck_single_trap_light_9_enabled);
        logedit_single_trap_light_9_solid_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_9_solid_intensity"));

        gridLayout_single_trap_light_9->addWidget(logedit_single_trap_light_9_solid_intensity, 9, 1, 1, 2);

        label_single_trap_light_9_softness = new QLabel(groupCheck_single_trap_light_9_enabled);
        label_single_trap_light_9_softness->setObjectName(QString::fromUtf8("label_single_trap_light_9_softness"));

        gridLayout_single_trap_light_9->addWidget(label_single_trap_light_9_softness, 9, 3, 1, 1);

        logedit_single_trap_light_9_softness = new MyLineEdit(groupCheck_single_trap_light_9_enabled);
        logedit_single_trap_light_9_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_9_softness"));

        gridLayout_single_trap_light_9->addWidget(logedit_single_trap_light_9_softness, 9, 4, 1, 1);

        label_single_trap_light_9_relative_size = new QLabel(groupCheck_single_trap_light_9_enabled);
        label_single_trap_light_9_relative_size->setObjectName(QString::fromUtf8("label_single_trap_light_9_relative_size"));

        gridLayout_single_trap_light_9->addWidget(label_single_trap_light_9_relative_size, 10, 0, 1, 1);

        logedit_single_trap_light_9_relative_size = new MyLineEdit(groupCheck_single_trap_light_9_enabled);
        logedit_single_trap_light_9_relative_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_9_relative_size"));

        gridLayout_single_trap_light_9->addWidget(logedit_single_trap_light_9_relative_size, 10, 1, 1, 2);

        checkBox_single_trap_light_9_pre_transformed = new MyCheckBox(groupCheck_single_trap_light_9_enabled);
        checkBox_single_trap_light_9_pre_transformed->setObjectName(QString::fromUtf8("checkBox_single_trap_light_9_pre_transformed"));

        gridLayout_single_trap_light_9->addWidget(checkBox_single_trap_light_9_pre_transformed, 11, 0, 1, 1);

        label_single_trap_light_9_position_mode = new QLabel(groupCheck_single_trap_light_9_enabled);
        label_single_trap_light_9_position_mode->setObjectName(QString::fromUtf8("label_single_trap_light_9_position_mode"));

        gridLayout_single_trap_light_9->addWidget(label_single_trap_light_9_position_mode, 12, 0, 1, 1);

        comboBox_single_trap_light_9_position_mode = new MyComboBox(groupCheck_single_trap_light_9_enabled);
        comboBox_single_trap_light_9_position_mode->addItem(QString());
        comboBox_single_trap_light_9_position_mode->addItem(QString());
        comboBox_single_trap_light_9_position_mode->addItem(QString());
        comboBox_single_trap_light_9_position_mode->addItem(QString());
        comboBox_single_trap_light_9_position_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_9_position_mode"));

        gridLayout_single_trap_light_9->addWidget(comboBox_single_trap_light_9_position_mode, 12, 1, 1, 2);

        label_single_trap_light_9_coloring_mode = new QLabel(groupCheck_single_trap_light_9_enabled);
        label_single_trap_light_9_coloring_mode->setObjectName(QString::fromUtf8("label_single_trap_light_9_coloring_mode"));

        gridLayout_single_trap_light_9->addWidget(label_single_trap_light_9_coloring_mode, 13, 0, 1, 1);

        comboBox_single_trap_light_9_coloring_mode = new MyComboBox(groupCheck_single_trap_light_9_enabled);
        comboBox_single_trap_light_9_coloring_mode->addItem(QString());
        comboBox_single_trap_light_9_coloring_mode->addItem(QString());
        comboBox_single_trap_light_9_coloring_mode->addItem(QString());
        comboBox_single_trap_light_9_coloring_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_9_coloring_mode"));

        gridLayout_single_trap_light_9->addWidget(comboBox_single_trap_light_9_coloring_mode, 13, 1, 1, 2);

        label_single_trap_light_9_falloff_type = new QLabel(groupCheck_single_trap_light_9_enabled);
        label_single_trap_light_9_falloff_type->setObjectName(QString::fromUtf8("label_single_trap_light_9_falloff_type"));

        gridLayout_single_trap_light_9->addWidget(label_single_trap_light_9_falloff_type, 14, 0, 1, 1);

        comboBox_single_trap_light_9_falloff_type = new MyComboBox(groupCheck_single_trap_light_9_enabled);
        comboBox_single_trap_light_9_falloff_type->addItem(QString());
        comboBox_single_trap_light_9_falloff_type->addItem(QString());
        comboBox_single_trap_light_9_falloff_type->addItem(QString());
        comboBox_single_trap_light_9_falloff_type->addItem(QString());
        comboBox_single_trap_light_9_falloff_type->addItem(QString());
        comboBox_single_trap_light_9_falloff_type->setObjectName(QString::fromUtf8("comboBox_single_trap_light_9_falloff_type"));

        gridLayout_single_trap_light_9->addWidget(comboBox_single_trap_light_9_falloff_type, 14, 1, 1, 2);

        label_single_trap_light_9_edge_softness = new QLabel(groupCheck_single_trap_light_9_enabled);
        label_single_trap_light_9_edge_softness->setObjectName(QString::fromUtf8("label_single_trap_light_9_edge_softness"));

        gridLayout_single_trap_light_9->addWidget(label_single_trap_light_9_edge_softness, 15, 0, 1, 1);

        logedit_single_trap_light_9_edge_softness = new MyLineEdit(groupCheck_single_trap_light_9_enabled);
        logedit_single_trap_light_9_edge_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_9_edge_softness"));

        gridLayout_single_trap_light_9->addWidget(logedit_single_trap_light_9_edge_softness, 15, 1, 1, 2);

        label_single_trap_light_9_anim_orbit_radius = new QLabel(groupCheck_single_trap_light_9_enabled);
        label_single_trap_light_9_anim_orbit_radius->setObjectName(QString::fromUtf8("label_single_trap_light_9_anim_orbit_radius"));

        gridLayout_single_trap_light_9->addWidget(label_single_trap_light_9_anim_orbit_radius, 16, 0, 1, 1);

        logedit_single_trap_light_9_anim_orbit_radius = new MyLineEdit(groupCheck_single_trap_light_9_enabled);
        logedit_single_trap_light_9_anim_orbit_radius->setObjectName(QString::fromUtf8("logedit_single_trap_light_9_anim_orbit_radius"));

        gridLayout_single_trap_light_9->addWidget(logedit_single_trap_light_9_anim_orbit_radius, 16, 1, 1, 1);

        logedit_single_trap_light_9_anim_orbit_speed = new MyLineEdit(groupCheck_single_trap_light_9_enabled);
        logedit_single_trap_light_9_anim_orbit_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_9_anim_orbit_speed"));

        gridLayout_single_trap_light_9->addWidget(logedit_single_trap_light_9_anim_orbit_speed, 16, 2, 1, 1);

        logedit_single_trap_light_9_anim_pulsate_speed = new MyLineEdit(groupCheck_single_trap_light_9_enabled);
        logedit_single_trap_light_9_anim_pulsate_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_9_anim_pulsate_speed"));

        gridLayout_single_trap_light_9->addWidget(logedit_single_trap_light_9_anim_pulsate_speed, 16, 3, 1, 1);

        logedit_single_trap_light_9_anim_pulsate_amount = new MyLineEdit(groupCheck_single_trap_light_9_enabled);
        logedit_single_trap_light_9_anim_pulsate_amount->setObjectName(QString::fromUtf8("logedit_single_trap_light_9_anim_pulsate_amount"));

        gridLayout_single_trap_light_9->addWidget(logedit_single_trap_light_9_anim_pulsate_amount, 16, 4, 1, 1);

        pushButton_single_trap_light_9_place_surface = new QPushButton(groupCheck_single_trap_light_9_enabled);
        pushButton_single_trap_light_9_place_surface->setObjectName(QString::fromUtf8("pushButton_single_trap_light_9_place_surface"));

        gridLayout_single_trap_light_9->addWidget(pushButton_single_trap_light_9_place_surface, 17, 0, 1, 5);

        pushButton_single_trap_light_9_place_target = new QPushButton(groupCheck_single_trap_light_9_enabled);
        pushButton_single_trap_light_9_place_target->setObjectName(QString::fromUtf8("pushButton_single_trap_light_9_place_target"));

        gridLayout_single_trap_light_9->addWidget(pushButton_single_trap_light_9_place_target, 18, 0, 1, 5);


        verticalLayout_single_trap_layers->addWidget(groupCheck_single_trap_light_9_enabled);

        groupCheck_single_trap_light_10_enabled = new MyGroupBox(scrollAreaWidgetContents_single_trap);
        groupCheck_single_trap_light_10_enabled->setObjectName(QString::fromUtf8("groupCheck_single_trap_light_10_enabled"));
        groupCheck_single_trap_light_10_enabled->setCheckable(true);
        gridLayout_single_trap_light_10 = new QGridLayout(groupCheck_single_trap_light_10_enabled);
        gridLayout_single_trap_light_10->setSpacing(2);
        gridLayout_single_trap_light_10->setObjectName(QString::fromUtf8("gridLayout_single_trap_light_10"));
        label_single_trap_light_10_shape = new QLabel(groupCheck_single_trap_light_10_enabled);
        label_single_trap_light_10_shape->setObjectName(QString::fromUtf8("label_single_trap_light_10_shape"));

        gridLayout_single_trap_light_10->addWidget(label_single_trap_light_10_shape, 0, 0, 1, 1);

        comboBox_single_trap_light_10_shape = new MyComboBox(groupCheck_single_trap_light_10_enabled);
        comboBox_single_trap_light_10_shape->addItem(QString());
        comboBox_single_trap_light_10_shape->addItem(QString());
        comboBox_single_trap_light_10_shape->addItem(QString());
        comboBox_single_trap_light_10_shape->addItem(QString());
        comboBox_single_trap_light_10_shape->addItem(QString());
        comboBox_single_trap_light_10_shape->addItem(QString());
        comboBox_single_trap_light_10_shape->addItem(QString());
        comboBox_single_trap_light_10_shape->addItem(QString());
        comboBox_single_trap_light_10_shape->addItem(QString());
        comboBox_single_trap_light_10_shape->addItem(QString());
        comboBox_single_trap_light_10_shape->addItem(QString());
        comboBox_single_trap_light_10_shape->addItem(QString());
        comboBox_single_trap_light_10_shape->addItem(QString());
        comboBox_single_trap_light_10_shape->addItem(QString());
        comboBox_single_trap_light_10_shape->setObjectName(QString::fromUtf8("comboBox_single_trap_light_10_shape"));

        gridLayout_single_trap_light_10->addWidget(comboBox_single_trap_light_10_shape, 0, 1, 1, 2);

        label_single_trap_light_10_position = new QLabel(groupCheck_single_trap_light_10_enabled);
        label_single_trap_light_10_position->setObjectName(QString::fromUtf8("label_single_trap_light_10_position"));

        gridLayout_single_trap_light_10->addWidget(label_single_trap_light_10_position, 1, 0, 1, 1);

        vect3_single_trap_light_10_position_x = new MyLineEdit(groupCheck_single_trap_light_10_enabled);
        vect3_single_trap_light_10_position_x->setObjectName(QString::fromUtf8("vect3_single_trap_light_10_position_x"));

        gridLayout_single_trap_light_10->addWidget(vect3_single_trap_light_10_position_x, 1, 1, 1, 1);

        vect3_single_trap_light_10_position_y = new MyLineEdit(groupCheck_single_trap_light_10_enabled);
        vect3_single_trap_light_10_position_y->setObjectName(QString::fromUtf8("vect3_single_trap_light_10_position_y"));

        gridLayout_single_trap_light_10->addWidget(vect3_single_trap_light_10_position_y, 1, 2, 1, 1);

        vect3_single_trap_light_10_position_z = new MyLineEdit(groupCheck_single_trap_light_10_enabled);
        vect3_single_trap_light_10_position_z->setObjectName(QString::fromUtf8("vect3_single_trap_light_10_position_z"));

        gridLayout_single_trap_light_10->addWidget(vect3_single_trap_light_10_position_z, 1, 3, 1, 1);

        pushButton_single_trap_light_10_place_camera = new QPushButton(groupCheck_single_trap_light_10_enabled);
        pushButton_single_trap_light_10_place_camera->setObjectName(QString::fromUtf8("pushButton_single_trap_light_10_place_camera"));

        gridLayout_single_trap_light_10->addWidget(pushButton_single_trap_light_10_place_camera, 1, 4, 1, 1);

        label_single_trap_light_10_size = new QLabel(groupCheck_single_trap_light_10_enabled);
        label_single_trap_light_10_size->setObjectName(QString::fromUtf8("label_single_trap_light_10_size"));

        gridLayout_single_trap_light_10->addWidget(label_single_trap_light_10_size, 2, 0, 1, 1);

        logedit_single_trap_light_10_size = new MyLineEdit(groupCheck_single_trap_light_10_enabled);
        logedit_single_trap_light_10_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_10_size"));

        gridLayout_single_trap_light_10->addWidget(logedit_single_trap_light_10_size, 2, 1, 1, 2);

        label_single_trap_light_10_size2 = new QLabel(groupCheck_single_trap_light_10_enabled);
        label_single_trap_light_10_size2->setObjectName(QString::fromUtf8("label_single_trap_light_10_size2"));

        gridLayout_single_trap_light_10->addWidget(label_single_trap_light_10_size2, 2, 3, 1, 1);

        logedit_single_trap_light_10_size2 = new MyLineEdit(groupCheck_single_trap_light_10_enabled);
        logedit_single_trap_light_10_size2->setObjectName(QString::fromUtf8("logedit_single_trap_light_10_size2"));

        gridLayout_single_trap_light_10->addWidget(logedit_single_trap_light_10_size2, 2, 4, 1, 1);

        label_single_trap_light_10_thickness = new QLabel(groupCheck_single_trap_light_10_enabled);
        label_single_trap_light_10_thickness->setObjectName(QString::fromUtf8("label_single_trap_light_10_thickness"));

        gridLayout_single_trap_light_10->addWidget(label_single_trap_light_10_thickness, 3, 0, 1, 1);

        logedit_single_trap_light_10_thickness = new MyLineEdit(groupCheck_single_trap_light_10_enabled);
        logedit_single_trap_light_10_thickness->setObjectName(QString::fromUtf8("logedit_single_trap_light_10_thickness"));

        gridLayout_single_trap_light_10->addWidget(logedit_single_trap_light_10_thickness, 3, 1, 1, 2);

        label_single_trap_light_10_rotation = new QLabel(groupCheck_single_trap_light_10_enabled);
        label_single_trap_light_10_rotation->setObjectName(QString::fromUtf8("label_single_trap_light_10_rotation"));

        gridLayout_single_trap_light_10->addWidget(label_single_trap_light_10_rotation, 4, 0, 1, 1);

        spinboxd3_single_trap_light_10_rotation_x = new MyDoubleSpinBox(groupCheck_single_trap_light_10_enabled);
        spinboxd3_single_trap_light_10_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_10_rotation_x"));

        gridLayout_single_trap_light_10->addWidget(spinboxd3_single_trap_light_10_rotation_x, 4, 1, 1, 1);

        spinboxd3_single_trap_light_10_rotation_y = new MyDoubleSpinBox(groupCheck_single_trap_light_10_enabled);
        spinboxd3_single_trap_light_10_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_10_rotation_y"));

        gridLayout_single_trap_light_10->addWidget(spinboxd3_single_trap_light_10_rotation_y, 4, 2, 1, 1);

        spinboxd3_single_trap_light_10_rotation_z = new MyDoubleSpinBox(groupCheck_single_trap_light_10_enabled);
        spinboxd3_single_trap_light_10_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_10_rotation_z"));

        gridLayout_single_trap_light_10->addWidget(spinboxd3_single_trap_light_10_rotation_z, 4, 3, 1, 1);

        label_single_trap_light_10_intensity = new QLabel(groupCheck_single_trap_light_10_enabled);
        label_single_trap_light_10_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_10_intensity"));

        gridLayout_single_trap_light_10->addWidget(label_single_trap_light_10_intensity, 5, 0, 1, 1);

        logedit_single_trap_light_10_intensity = new MyLineEdit(groupCheck_single_trap_light_10_enabled);
        logedit_single_trap_light_10_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_10_intensity"));

        gridLayout_single_trap_light_10->addWidget(logedit_single_trap_light_10_intensity, 5, 1, 1, 2);

        label_single_trap_light_10_color = new QLabel(groupCheck_single_trap_light_10_enabled);
        label_single_trap_light_10_color->setObjectName(QString::fromUtf8("label_single_trap_light_10_color"));

        gridLayout_single_trap_light_10->addWidget(label_single_trap_light_10_color, 6, 0, 1, 1);

        colorButton_single_trap_light_10_color = new MyColorButton(groupCheck_single_trap_light_10_enabled);
        colorButton_single_trap_light_10_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_10_color"));

        gridLayout_single_trap_light_10->addWidget(colorButton_single_trap_light_10_color, 6, 1, 1, 1);

        label_single_trap_light_10_gradient_color = new QLabel(groupCheck_single_trap_light_10_enabled);
        label_single_trap_light_10_gradient_color->setObjectName(QString::fromUtf8("label_single_trap_light_10_gradient_color"));

        gridLayout_single_trap_light_10->addWidget(label_single_trap_light_10_gradient_color, 6, 2, 1, 1);

        colorButton_single_trap_light_10_gradient_color = new MyColorButton(groupCheck_single_trap_light_10_enabled);
        colorButton_single_trap_light_10_gradient_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_10_gradient_color"));

        gridLayout_single_trap_light_10->addWidget(colorButton_single_trap_light_10_gradient_color, 6, 3, 1, 2);

        label_single_trap_light_10_visibility = new QLabel(groupCheck_single_trap_light_10_enabled);
        label_single_trap_light_10_visibility->setObjectName(QString::fromUtf8("label_single_trap_light_10_visibility"));

        gridLayout_single_trap_light_10->addWidget(label_single_trap_light_10_visibility, 7, 0, 1, 1);

        logedit_single_trap_light_10_visibility = new MyLineEdit(groupCheck_single_trap_light_10_enabled);
        logedit_single_trap_light_10_visibility->setObjectName(QString::fromUtf8("logedit_single_trap_light_10_visibility"));

        gridLayout_single_trap_light_10->addWidget(logedit_single_trap_light_10_visibility, 7, 1, 1, 2);

        label_single_trap_light_10_max_distance = new QLabel(groupCheck_single_trap_light_10_enabled);
        label_single_trap_light_10_max_distance->setObjectName(QString::fromUtf8("label_single_trap_light_10_max_distance"));

        gridLayout_single_trap_light_10->addWidget(label_single_trap_light_10_max_distance, 7, 3, 1, 1);

        logedit_single_trap_light_10_max_distance = new MyLineEdit(groupCheck_single_trap_light_10_enabled);
        logedit_single_trap_light_10_max_distance->setObjectName(QString::fromUtf8("logedit_single_trap_light_10_max_distance"));

        gridLayout_single_trap_light_10->addWidget(logedit_single_trap_light_10_max_distance, 7, 4, 1, 1);

        label_single_trap_light_10_sharpening = new QLabel(groupCheck_single_trap_light_10_enabled);
        label_single_trap_light_10_sharpening->setObjectName(QString::fromUtf8("label_single_trap_light_10_sharpening"));

        gridLayout_single_trap_light_10->addWidget(label_single_trap_light_10_sharpening, 8, 0, 1, 1);

        logedit_single_trap_light_10_sharpening = new MyLineEdit(groupCheck_single_trap_light_10_enabled);
        logedit_single_trap_light_10_sharpening->setObjectName(QString::fromUtf8("logedit_single_trap_light_10_sharpening"));

        gridLayout_single_trap_light_10->addWidget(logedit_single_trap_light_10_sharpening, 8, 1, 1, 2);

        label_single_trap_light_10_blur = new QLabel(groupCheck_single_trap_light_10_enabled);
        label_single_trap_light_10_blur->setObjectName(QString::fromUtf8("label_single_trap_light_10_blur"));

        gridLayout_single_trap_light_10->addWidget(label_single_trap_light_10_blur, 8, 3, 1, 1);

        logedit_single_trap_light_10_blur = new MyLineEdit(groupCheck_single_trap_light_10_enabled);
        logedit_single_trap_light_10_blur->setObjectName(QString::fromUtf8("logedit_single_trap_light_10_blur"));

        gridLayout_single_trap_light_10->addWidget(logedit_single_trap_light_10_blur, 8, 4, 1, 1);

        label_single_trap_light_10_solid_intensity = new QLabel(groupCheck_single_trap_light_10_enabled);
        label_single_trap_light_10_solid_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_10_solid_intensity"));

        gridLayout_single_trap_light_10->addWidget(label_single_trap_light_10_solid_intensity, 9, 0, 1, 1);

        logedit_single_trap_light_10_solid_intensity = new MyLineEdit(groupCheck_single_trap_light_10_enabled);
        logedit_single_trap_light_10_solid_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_10_solid_intensity"));

        gridLayout_single_trap_light_10->addWidget(logedit_single_trap_light_10_solid_intensity, 9, 1, 1, 2);

        label_single_trap_light_10_softness = new QLabel(groupCheck_single_trap_light_10_enabled);
        label_single_trap_light_10_softness->setObjectName(QString::fromUtf8("label_single_trap_light_10_softness"));

        gridLayout_single_trap_light_10->addWidget(label_single_trap_light_10_softness, 9, 3, 1, 1);

        logedit_single_trap_light_10_softness = new MyLineEdit(groupCheck_single_trap_light_10_enabled);
        logedit_single_trap_light_10_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_10_softness"));

        gridLayout_single_trap_light_10->addWidget(logedit_single_trap_light_10_softness, 9, 4, 1, 1);

        label_single_trap_light_10_relative_size = new QLabel(groupCheck_single_trap_light_10_enabled);
        label_single_trap_light_10_relative_size->setObjectName(QString::fromUtf8("label_single_trap_light_10_relative_size"));

        gridLayout_single_trap_light_10->addWidget(label_single_trap_light_10_relative_size, 10, 0, 1, 1);

        logedit_single_trap_light_10_relative_size = new MyLineEdit(groupCheck_single_trap_light_10_enabled);
        logedit_single_trap_light_10_relative_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_10_relative_size"));

        gridLayout_single_trap_light_10->addWidget(logedit_single_trap_light_10_relative_size, 10, 1, 1, 2);

        checkBox_single_trap_light_10_pre_transformed = new MyCheckBox(groupCheck_single_trap_light_10_enabled);
        checkBox_single_trap_light_10_pre_transformed->setObjectName(QString::fromUtf8("checkBox_single_trap_light_10_pre_transformed"));

        gridLayout_single_trap_light_10->addWidget(checkBox_single_trap_light_10_pre_transformed, 11, 0, 1, 1);

        label_single_trap_light_10_position_mode = new QLabel(groupCheck_single_trap_light_10_enabled);
        label_single_trap_light_10_position_mode->setObjectName(QString::fromUtf8("label_single_trap_light_10_position_mode"));

        gridLayout_single_trap_light_10->addWidget(label_single_trap_light_10_position_mode, 12, 0, 1, 1);

        comboBox_single_trap_light_10_position_mode = new MyComboBox(groupCheck_single_trap_light_10_enabled);
        comboBox_single_trap_light_10_position_mode->addItem(QString());
        comboBox_single_trap_light_10_position_mode->addItem(QString());
        comboBox_single_trap_light_10_position_mode->addItem(QString());
        comboBox_single_trap_light_10_position_mode->addItem(QString());
        comboBox_single_trap_light_10_position_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_10_position_mode"));

        gridLayout_single_trap_light_10->addWidget(comboBox_single_trap_light_10_position_mode, 12, 1, 1, 2);

        label_single_trap_light_10_coloring_mode = new QLabel(groupCheck_single_trap_light_10_enabled);
        label_single_trap_light_10_coloring_mode->setObjectName(QString::fromUtf8("label_single_trap_light_10_coloring_mode"));

        gridLayout_single_trap_light_10->addWidget(label_single_trap_light_10_coloring_mode, 13, 0, 1, 1);

        comboBox_single_trap_light_10_coloring_mode = new MyComboBox(groupCheck_single_trap_light_10_enabled);
        comboBox_single_trap_light_10_coloring_mode->addItem(QString());
        comboBox_single_trap_light_10_coloring_mode->addItem(QString());
        comboBox_single_trap_light_10_coloring_mode->addItem(QString());
        comboBox_single_trap_light_10_coloring_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_10_coloring_mode"));

        gridLayout_single_trap_light_10->addWidget(comboBox_single_trap_light_10_coloring_mode, 13, 1, 1, 2);

        label_single_trap_light_10_falloff_type = new QLabel(groupCheck_single_trap_light_10_enabled);
        label_single_trap_light_10_falloff_type->setObjectName(QString::fromUtf8("label_single_trap_light_10_falloff_type"));

        gridLayout_single_trap_light_10->addWidget(label_single_trap_light_10_falloff_type, 14, 0, 1, 1);

        comboBox_single_trap_light_10_falloff_type = new MyComboBox(groupCheck_single_trap_light_10_enabled);
        comboBox_single_trap_light_10_falloff_type->addItem(QString());
        comboBox_single_trap_light_10_falloff_type->addItem(QString());
        comboBox_single_trap_light_10_falloff_type->addItem(QString());
        comboBox_single_trap_light_10_falloff_type->addItem(QString());
        comboBox_single_trap_light_10_falloff_type->addItem(QString());
        comboBox_single_trap_light_10_falloff_type->setObjectName(QString::fromUtf8("comboBox_single_trap_light_10_falloff_type"));

        gridLayout_single_trap_light_10->addWidget(comboBox_single_trap_light_10_falloff_type, 14, 1, 1, 2);

        label_single_trap_light_10_edge_softness = new QLabel(groupCheck_single_trap_light_10_enabled);
        label_single_trap_light_10_edge_softness->setObjectName(QString::fromUtf8("label_single_trap_light_10_edge_softness"));

        gridLayout_single_trap_light_10->addWidget(label_single_trap_light_10_edge_softness, 15, 0, 1, 1);

        logedit_single_trap_light_10_edge_softness = new MyLineEdit(groupCheck_single_trap_light_10_enabled);
        logedit_single_trap_light_10_edge_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_10_edge_softness"));

        gridLayout_single_trap_light_10->addWidget(logedit_single_trap_light_10_edge_softness, 15, 1, 1, 2);

        label_single_trap_light_10_anim_orbit_radius = new QLabel(groupCheck_single_trap_light_10_enabled);
        label_single_trap_light_10_anim_orbit_radius->setObjectName(QString::fromUtf8("label_single_trap_light_10_anim_orbit_radius"));

        gridLayout_single_trap_light_10->addWidget(label_single_trap_light_10_anim_orbit_radius, 16, 0, 1, 1);

        logedit_single_trap_light_10_anim_orbit_radius = new MyLineEdit(groupCheck_single_trap_light_10_enabled);
        logedit_single_trap_light_10_anim_orbit_radius->setObjectName(QString::fromUtf8("logedit_single_trap_light_10_anim_orbit_radius"));

        gridLayout_single_trap_light_10->addWidget(logedit_single_trap_light_10_anim_orbit_radius, 16, 1, 1, 1);

        logedit_single_trap_light_10_anim_orbit_speed = new MyLineEdit(groupCheck_single_trap_light_10_enabled);
        logedit_single_trap_light_10_anim_orbit_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_10_anim_orbit_speed"));

        gridLayout_single_trap_light_10->addWidget(logedit_single_trap_light_10_anim_orbit_speed, 16, 2, 1, 1);

        logedit_single_trap_light_10_anim_pulsate_speed = new MyLineEdit(groupCheck_single_trap_light_10_enabled);
        logedit_single_trap_light_10_anim_pulsate_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_10_anim_pulsate_speed"));

        gridLayout_single_trap_light_10->addWidget(logedit_single_trap_light_10_anim_pulsate_speed, 16, 3, 1, 1);

        logedit_single_trap_light_10_anim_pulsate_amount = new MyLineEdit(groupCheck_single_trap_light_10_enabled);
        logedit_single_trap_light_10_anim_pulsate_amount->setObjectName(QString::fromUtf8("logedit_single_trap_light_10_anim_pulsate_amount"));

        gridLayout_single_trap_light_10->addWidget(logedit_single_trap_light_10_anim_pulsate_amount, 16, 4, 1, 1);

        pushButton_single_trap_light_10_place_surface = new QPushButton(groupCheck_single_trap_light_10_enabled);
        pushButton_single_trap_light_10_place_surface->setObjectName(QString::fromUtf8("pushButton_single_trap_light_10_place_surface"));

        gridLayout_single_trap_light_10->addWidget(pushButton_single_trap_light_10_place_surface, 17, 0, 1, 5);

        pushButton_single_trap_light_10_place_target = new QPushButton(groupCheck_single_trap_light_10_enabled);
        pushButton_single_trap_light_10_place_target->setObjectName(QString::fromUtf8("pushButton_single_trap_light_10_place_target"));

        gridLayout_single_trap_light_10->addWidget(pushButton_single_trap_light_10_place_target, 18, 0, 1, 5);


        verticalLayout_single_trap_layers->addWidget(groupCheck_single_trap_light_10_enabled);

        groupCheck_single_trap_light_11_enabled = new MyGroupBox(scrollAreaWidgetContents_single_trap);
        groupCheck_single_trap_light_11_enabled->setObjectName(QString::fromUtf8("groupCheck_single_trap_light_11_enabled"));
        groupCheck_single_trap_light_11_enabled->setCheckable(true);
        gridLayout_single_trap_light_11 = new QGridLayout(groupCheck_single_trap_light_11_enabled);
        gridLayout_single_trap_light_11->setSpacing(2);
        gridLayout_single_trap_light_11->setObjectName(QString::fromUtf8("gridLayout_single_trap_light_11"));
        label_single_trap_light_11_shape = new QLabel(groupCheck_single_trap_light_11_enabled);
        label_single_trap_light_11_shape->setObjectName(QString::fromUtf8("label_single_trap_light_11_shape"));

        gridLayout_single_trap_light_11->addWidget(label_single_trap_light_11_shape, 0, 0, 1, 1);

        comboBox_single_trap_light_11_shape = new MyComboBox(groupCheck_single_trap_light_11_enabled);
        comboBox_single_trap_light_11_shape->addItem(QString());
        comboBox_single_trap_light_11_shape->addItem(QString());
        comboBox_single_trap_light_11_shape->addItem(QString());
        comboBox_single_trap_light_11_shape->addItem(QString());
        comboBox_single_trap_light_11_shape->addItem(QString());
        comboBox_single_trap_light_11_shape->addItem(QString());
        comboBox_single_trap_light_11_shape->addItem(QString());
        comboBox_single_trap_light_11_shape->addItem(QString());
        comboBox_single_trap_light_11_shape->addItem(QString());
        comboBox_single_trap_light_11_shape->addItem(QString());
        comboBox_single_trap_light_11_shape->addItem(QString());
        comboBox_single_trap_light_11_shape->addItem(QString());
        comboBox_single_trap_light_11_shape->addItem(QString());
        comboBox_single_trap_light_11_shape->addItem(QString());
        comboBox_single_trap_light_11_shape->setObjectName(QString::fromUtf8("comboBox_single_trap_light_11_shape"));

        gridLayout_single_trap_light_11->addWidget(comboBox_single_trap_light_11_shape, 0, 1, 1, 2);

        label_single_trap_light_11_position = new QLabel(groupCheck_single_trap_light_11_enabled);
        label_single_trap_light_11_position->setObjectName(QString::fromUtf8("label_single_trap_light_11_position"));

        gridLayout_single_trap_light_11->addWidget(label_single_trap_light_11_position, 1, 0, 1, 1);

        vect3_single_trap_light_11_position_x = new MyLineEdit(groupCheck_single_trap_light_11_enabled);
        vect3_single_trap_light_11_position_x->setObjectName(QString::fromUtf8("vect3_single_trap_light_11_position_x"));

        gridLayout_single_trap_light_11->addWidget(vect3_single_trap_light_11_position_x, 1, 1, 1, 1);

        vect3_single_trap_light_11_position_y = new MyLineEdit(groupCheck_single_trap_light_11_enabled);
        vect3_single_trap_light_11_position_y->setObjectName(QString::fromUtf8("vect3_single_trap_light_11_position_y"));

        gridLayout_single_trap_light_11->addWidget(vect3_single_trap_light_11_position_y, 1, 2, 1, 1);

        vect3_single_trap_light_11_position_z = new MyLineEdit(groupCheck_single_trap_light_11_enabled);
        vect3_single_trap_light_11_position_z->setObjectName(QString::fromUtf8("vect3_single_trap_light_11_position_z"));

        gridLayout_single_trap_light_11->addWidget(vect3_single_trap_light_11_position_z, 1, 3, 1, 1);

        pushButton_single_trap_light_11_place_camera = new QPushButton(groupCheck_single_trap_light_11_enabled);
        pushButton_single_trap_light_11_place_camera->setObjectName(QString::fromUtf8("pushButton_single_trap_light_11_place_camera"));

        gridLayout_single_trap_light_11->addWidget(pushButton_single_trap_light_11_place_camera, 1, 4, 1, 1);

        label_single_trap_light_11_size = new QLabel(groupCheck_single_trap_light_11_enabled);
        label_single_trap_light_11_size->setObjectName(QString::fromUtf8("label_single_trap_light_11_size"));

        gridLayout_single_trap_light_11->addWidget(label_single_trap_light_11_size, 2, 0, 1, 1);

        logedit_single_trap_light_11_size = new MyLineEdit(groupCheck_single_trap_light_11_enabled);
        logedit_single_trap_light_11_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_11_size"));

        gridLayout_single_trap_light_11->addWidget(logedit_single_trap_light_11_size, 2, 1, 1, 2);

        label_single_trap_light_11_size2 = new QLabel(groupCheck_single_trap_light_11_enabled);
        label_single_trap_light_11_size2->setObjectName(QString::fromUtf8("label_single_trap_light_11_size2"));

        gridLayout_single_trap_light_11->addWidget(label_single_trap_light_11_size2, 2, 3, 1, 1);

        logedit_single_trap_light_11_size2 = new MyLineEdit(groupCheck_single_trap_light_11_enabled);
        logedit_single_trap_light_11_size2->setObjectName(QString::fromUtf8("logedit_single_trap_light_11_size2"));

        gridLayout_single_trap_light_11->addWidget(logedit_single_trap_light_11_size2, 2, 4, 1, 1);

        label_single_trap_light_11_thickness = new QLabel(groupCheck_single_trap_light_11_enabled);
        label_single_trap_light_11_thickness->setObjectName(QString::fromUtf8("label_single_trap_light_11_thickness"));

        gridLayout_single_trap_light_11->addWidget(label_single_trap_light_11_thickness, 3, 0, 1, 1);

        logedit_single_trap_light_11_thickness = new MyLineEdit(groupCheck_single_trap_light_11_enabled);
        logedit_single_trap_light_11_thickness->setObjectName(QString::fromUtf8("logedit_single_trap_light_11_thickness"));

        gridLayout_single_trap_light_11->addWidget(logedit_single_trap_light_11_thickness, 3, 1, 1, 2);

        label_single_trap_light_11_rotation = new QLabel(groupCheck_single_trap_light_11_enabled);
        label_single_trap_light_11_rotation->setObjectName(QString::fromUtf8("label_single_trap_light_11_rotation"));

        gridLayout_single_trap_light_11->addWidget(label_single_trap_light_11_rotation, 4, 0, 1, 1);

        spinboxd3_single_trap_light_11_rotation_x = new MyDoubleSpinBox(groupCheck_single_trap_light_11_enabled);
        spinboxd3_single_trap_light_11_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_11_rotation_x"));

        gridLayout_single_trap_light_11->addWidget(spinboxd3_single_trap_light_11_rotation_x, 4, 1, 1, 1);

        spinboxd3_single_trap_light_11_rotation_y = new MyDoubleSpinBox(groupCheck_single_trap_light_11_enabled);
        spinboxd3_single_trap_light_11_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_11_rotation_y"));

        gridLayout_single_trap_light_11->addWidget(spinboxd3_single_trap_light_11_rotation_y, 4, 2, 1, 1);

        spinboxd3_single_trap_light_11_rotation_z = new MyDoubleSpinBox(groupCheck_single_trap_light_11_enabled);
        spinboxd3_single_trap_light_11_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_11_rotation_z"));

        gridLayout_single_trap_light_11->addWidget(spinboxd3_single_trap_light_11_rotation_z, 4, 3, 1, 1);

        label_single_trap_light_11_intensity = new QLabel(groupCheck_single_trap_light_11_enabled);
        label_single_trap_light_11_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_11_intensity"));

        gridLayout_single_trap_light_11->addWidget(label_single_trap_light_11_intensity, 5, 0, 1, 1);

        logedit_single_trap_light_11_intensity = new MyLineEdit(groupCheck_single_trap_light_11_enabled);
        logedit_single_trap_light_11_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_11_intensity"));

        gridLayout_single_trap_light_11->addWidget(logedit_single_trap_light_11_intensity, 5, 1, 1, 2);

        label_single_trap_light_11_color = new QLabel(groupCheck_single_trap_light_11_enabled);
        label_single_trap_light_11_color->setObjectName(QString::fromUtf8("label_single_trap_light_11_color"));

        gridLayout_single_trap_light_11->addWidget(label_single_trap_light_11_color, 6, 0, 1, 1);

        colorButton_single_trap_light_11_color = new MyColorButton(groupCheck_single_trap_light_11_enabled);
        colorButton_single_trap_light_11_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_11_color"));

        gridLayout_single_trap_light_11->addWidget(colorButton_single_trap_light_11_color, 6, 1, 1, 1);

        label_single_trap_light_11_gradient_color = new QLabel(groupCheck_single_trap_light_11_enabled);
        label_single_trap_light_11_gradient_color->setObjectName(QString::fromUtf8("label_single_trap_light_11_gradient_color"));

        gridLayout_single_trap_light_11->addWidget(label_single_trap_light_11_gradient_color, 6, 2, 1, 1);

        colorButton_single_trap_light_11_gradient_color = new MyColorButton(groupCheck_single_trap_light_11_enabled);
        colorButton_single_trap_light_11_gradient_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_11_gradient_color"));

        gridLayout_single_trap_light_11->addWidget(colorButton_single_trap_light_11_gradient_color, 6, 3, 1, 2);

        label_single_trap_light_11_visibility = new QLabel(groupCheck_single_trap_light_11_enabled);
        label_single_trap_light_11_visibility->setObjectName(QString::fromUtf8("label_single_trap_light_11_visibility"));

        gridLayout_single_trap_light_11->addWidget(label_single_trap_light_11_visibility, 7, 0, 1, 1);

        logedit_single_trap_light_11_visibility = new MyLineEdit(groupCheck_single_trap_light_11_enabled);
        logedit_single_trap_light_11_visibility->setObjectName(QString::fromUtf8("logedit_single_trap_light_11_visibility"));

        gridLayout_single_trap_light_11->addWidget(logedit_single_trap_light_11_visibility, 7, 1, 1, 2);

        label_single_trap_light_11_max_distance = new QLabel(groupCheck_single_trap_light_11_enabled);
        label_single_trap_light_11_max_distance->setObjectName(QString::fromUtf8("label_single_trap_light_11_max_distance"));

        gridLayout_single_trap_light_11->addWidget(label_single_trap_light_11_max_distance, 7, 3, 1, 1);

        logedit_single_trap_light_11_max_distance = new MyLineEdit(groupCheck_single_trap_light_11_enabled);
        logedit_single_trap_light_11_max_distance->setObjectName(QString::fromUtf8("logedit_single_trap_light_11_max_distance"));

        gridLayout_single_trap_light_11->addWidget(logedit_single_trap_light_11_max_distance, 7, 4, 1, 1);

        label_single_trap_light_11_sharpening = new QLabel(groupCheck_single_trap_light_11_enabled);
        label_single_trap_light_11_sharpening->setObjectName(QString::fromUtf8("label_single_trap_light_11_sharpening"));

        gridLayout_single_trap_light_11->addWidget(label_single_trap_light_11_sharpening, 8, 0, 1, 1);

        logedit_single_trap_light_11_sharpening = new MyLineEdit(groupCheck_single_trap_light_11_enabled);
        logedit_single_trap_light_11_sharpening->setObjectName(QString::fromUtf8("logedit_single_trap_light_11_sharpening"));

        gridLayout_single_trap_light_11->addWidget(logedit_single_trap_light_11_sharpening, 8, 1, 1, 2);

        label_single_trap_light_11_blur = new QLabel(groupCheck_single_trap_light_11_enabled);
        label_single_trap_light_11_blur->setObjectName(QString::fromUtf8("label_single_trap_light_11_blur"));

        gridLayout_single_trap_light_11->addWidget(label_single_trap_light_11_blur, 8, 3, 1, 1);

        logedit_single_trap_light_11_blur = new MyLineEdit(groupCheck_single_trap_light_11_enabled);
        logedit_single_trap_light_11_blur->setObjectName(QString::fromUtf8("logedit_single_trap_light_11_blur"));

        gridLayout_single_trap_light_11->addWidget(logedit_single_trap_light_11_blur, 8, 4, 1, 1);

        label_single_trap_light_11_solid_intensity = new QLabel(groupCheck_single_trap_light_11_enabled);
        label_single_trap_light_11_solid_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_11_solid_intensity"));

        gridLayout_single_trap_light_11->addWidget(label_single_trap_light_11_solid_intensity, 9, 0, 1, 1);

        logedit_single_trap_light_11_solid_intensity = new MyLineEdit(groupCheck_single_trap_light_11_enabled);
        logedit_single_trap_light_11_solid_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_11_solid_intensity"));

        gridLayout_single_trap_light_11->addWidget(logedit_single_trap_light_11_solid_intensity, 9, 1, 1, 2);

        label_single_trap_light_11_softness = new QLabel(groupCheck_single_trap_light_11_enabled);
        label_single_trap_light_11_softness->setObjectName(QString::fromUtf8("label_single_trap_light_11_softness"));

        gridLayout_single_trap_light_11->addWidget(label_single_trap_light_11_softness, 9, 3, 1, 1);

        logedit_single_trap_light_11_softness = new MyLineEdit(groupCheck_single_trap_light_11_enabled);
        logedit_single_trap_light_11_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_11_softness"));

        gridLayout_single_trap_light_11->addWidget(logedit_single_trap_light_11_softness, 9, 4, 1, 1);

        label_single_trap_light_11_relative_size = new QLabel(groupCheck_single_trap_light_11_enabled);
        label_single_trap_light_11_relative_size->setObjectName(QString::fromUtf8("label_single_trap_light_11_relative_size"));

        gridLayout_single_trap_light_11->addWidget(label_single_trap_light_11_relative_size, 10, 0, 1, 1);

        logedit_single_trap_light_11_relative_size = new MyLineEdit(groupCheck_single_trap_light_11_enabled);
        logedit_single_trap_light_11_relative_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_11_relative_size"));

        gridLayout_single_trap_light_11->addWidget(logedit_single_trap_light_11_relative_size, 10, 1, 1, 2);

        checkBox_single_trap_light_11_pre_transformed = new MyCheckBox(groupCheck_single_trap_light_11_enabled);
        checkBox_single_trap_light_11_pre_transformed->setObjectName(QString::fromUtf8("checkBox_single_trap_light_11_pre_transformed"));

        gridLayout_single_trap_light_11->addWidget(checkBox_single_trap_light_11_pre_transformed, 11, 0, 1, 1);

        label_single_trap_light_11_position_mode = new QLabel(groupCheck_single_trap_light_11_enabled);
        label_single_trap_light_11_position_mode->setObjectName(QString::fromUtf8("label_single_trap_light_11_position_mode"));

        gridLayout_single_trap_light_11->addWidget(label_single_trap_light_11_position_mode, 12, 0, 1, 1);

        comboBox_single_trap_light_11_position_mode = new MyComboBox(groupCheck_single_trap_light_11_enabled);
        comboBox_single_trap_light_11_position_mode->addItem(QString());
        comboBox_single_trap_light_11_position_mode->addItem(QString());
        comboBox_single_trap_light_11_position_mode->addItem(QString());
        comboBox_single_trap_light_11_position_mode->addItem(QString());
        comboBox_single_trap_light_11_position_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_11_position_mode"));

        gridLayout_single_trap_light_11->addWidget(comboBox_single_trap_light_11_position_mode, 12, 1, 1, 2);

        label_single_trap_light_11_coloring_mode = new QLabel(groupCheck_single_trap_light_11_enabled);
        label_single_trap_light_11_coloring_mode->setObjectName(QString::fromUtf8("label_single_trap_light_11_coloring_mode"));

        gridLayout_single_trap_light_11->addWidget(label_single_trap_light_11_coloring_mode, 13, 0, 1, 1);

        comboBox_single_trap_light_11_coloring_mode = new MyComboBox(groupCheck_single_trap_light_11_enabled);
        comboBox_single_trap_light_11_coloring_mode->addItem(QString());
        comboBox_single_trap_light_11_coloring_mode->addItem(QString());
        comboBox_single_trap_light_11_coloring_mode->addItem(QString());
        comboBox_single_trap_light_11_coloring_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_11_coloring_mode"));

        gridLayout_single_trap_light_11->addWidget(comboBox_single_trap_light_11_coloring_mode, 13, 1, 1, 2);

        label_single_trap_light_11_falloff_type = new QLabel(groupCheck_single_trap_light_11_enabled);
        label_single_trap_light_11_falloff_type->setObjectName(QString::fromUtf8("label_single_trap_light_11_falloff_type"));

        gridLayout_single_trap_light_11->addWidget(label_single_trap_light_11_falloff_type, 14, 0, 1, 1);

        comboBox_single_trap_light_11_falloff_type = new MyComboBox(groupCheck_single_trap_light_11_enabled);
        comboBox_single_trap_light_11_falloff_type->addItem(QString());
        comboBox_single_trap_light_11_falloff_type->addItem(QString());
        comboBox_single_trap_light_11_falloff_type->addItem(QString());
        comboBox_single_trap_light_11_falloff_type->addItem(QString());
        comboBox_single_trap_light_11_falloff_type->addItem(QString());
        comboBox_single_trap_light_11_falloff_type->setObjectName(QString::fromUtf8("comboBox_single_trap_light_11_falloff_type"));

        gridLayout_single_trap_light_11->addWidget(comboBox_single_trap_light_11_falloff_type, 14, 1, 1, 2);

        label_single_trap_light_11_edge_softness = new QLabel(groupCheck_single_trap_light_11_enabled);
        label_single_trap_light_11_edge_softness->setObjectName(QString::fromUtf8("label_single_trap_light_11_edge_softness"));

        gridLayout_single_trap_light_11->addWidget(label_single_trap_light_11_edge_softness, 15, 0, 1, 1);

        logedit_single_trap_light_11_edge_softness = new MyLineEdit(groupCheck_single_trap_light_11_enabled);
        logedit_single_trap_light_11_edge_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_11_edge_softness"));

        gridLayout_single_trap_light_11->addWidget(logedit_single_trap_light_11_edge_softness, 15, 1, 1, 2);

        label_single_trap_light_11_anim_orbit_radius = new QLabel(groupCheck_single_trap_light_11_enabled);
        label_single_trap_light_11_anim_orbit_radius->setObjectName(QString::fromUtf8("label_single_trap_light_11_anim_orbit_radius"));

        gridLayout_single_trap_light_11->addWidget(label_single_trap_light_11_anim_orbit_radius, 16, 0, 1, 1);

        logedit_single_trap_light_11_anim_orbit_radius = new MyLineEdit(groupCheck_single_trap_light_11_enabled);
        logedit_single_trap_light_11_anim_orbit_radius->setObjectName(QString::fromUtf8("logedit_single_trap_light_11_anim_orbit_radius"));

        gridLayout_single_trap_light_11->addWidget(logedit_single_trap_light_11_anim_orbit_radius, 16, 1, 1, 1);

        logedit_single_trap_light_11_anim_orbit_speed = new MyLineEdit(groupCheck_single_trap_light_11_enabled);
        logedit_single_trap_light_11_anim_orbit_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_11_anim_orbit_speed"));

        gridLayout_single_trap_light_11->addWidget(logedit_single_trap_light_11_anim_orbit_speed, 16, 2, 1, 1);

        logedit_single_trap_light_11_anim_pulsate_speed = new MyLineEdit(groupCheck_single_trap_light_11_enabled);
        logedit_single_trap_light_11_anim_pulsate_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_11_anim_pulsate_speed"));

        gridLayout_single_trap_light_11->addWidget(logedit_single_trap_light_11_anim_pulsate_speed, 16, 3, 1, 1);

        logedit_single_trap_light_11_anim_pulsate_amount = new MyLineEdit(groupCheck_single_trap_light_11_enabled);
        logedit_single_trap_light_11_anim_pulsate_amount->setObjectName(QString::fromUtf8("logedit_single_trap_light_11_anim_pulsate_amount"));

        gridLayout_single_trap_light_11->addWidget(logedit_single_trap_light_11_anim_pulsate_amount, 16, 4, 1, 1);

        pushButton_single_trap_light_11_place_surface = new QPushButton(groupCheck_single_trap_light_11_enabled);
        pushButton_single_trap_light_11_place_surface->setObjectName(QString::fromUtf8("pushButton_single_trap_light_11_place_surface"));

        gridLayout_single_trap_light_11->addWidget(pushButton_single_trap_light_11_place_surface, 17, 0, 1, 5);

        pushButton_single_trap_light_11_place_target = new QPushButton(groupCheck_single_trap_light_11_enabled);
        pushButton_single_trap_light_11_place_target->setObjectName(QString::fromUtf8("pushButton_single_trap_light_11_place_target"));

        gridLayout_single_trap_light_11->addWidget(pushButton_single_trap_light_11_place_target, 18, 0, 1, 5);


        verticalLayout_single_trap_layers->addWidget(groupCheck_single_trap_light_11_enabled);

        groupCheck_single_trap_light_12_enabled = new MyGroupBox(scrollAreaWidgetContents_single_trap);
        groupCheck_single_trap_light_12_enabled->setObjectName(QString::fromUtf8("groupCheck_single_trap_light_12_enabled"));
        groupCheck_single_trap_light_12_enabled->setCheckable(true);
        gridLayout_single_trap_light_12 = new QGridLayout(groupCheck_single_trap_light_12_enabled);
        gridLayout_single_trap_light_12->setSpacing(2);
        gridLayout_single_trap_light_12->setObjectName(QString::fromUtf8("gridLayout_single_trap_light_12"));
        label_single_trap_light_12_shape = new QLabel(groupCheck_single_trap_light_12_enabled);
        label_single_trap_light_12_shape->setObjectName(QString::fromUtf8("label_single_trap_light_12_shape"));

        gridLayout_single_trap_light_12->addWidget(label_single_trap_light_12_shape, 0, 0, 1, 1);

        comboBox_single_trap_light_12_shape = new MyComboBox(groupCheck_single_trap_light_12_enabled);
        comboBox_single_trap_light_12_shape->addItem(QString());
        comboBox_single_trap_light_12_shape->addItem(QString());
        comboBox_single_trap_light_12_shape->addItem(QString());
        comboBox_single_trap_light_12_shape->addItem(QString());
        comboBox_single_trap_light_12_shape->addItem(QString());
        comboBox_single_trap_light_12_shape->addItem(QString());
        comboBox_single_trap_light_12_shape->addItem(QString());
        comboBox_single_trap_light_12_shape->addItem(QString());
        comboBox_single_trap_light_12_shape->addItem(QString());
        comboBox_single_trap_light_12_shape->addItem(QString());
        comboBox_single_trap_light_12_shape->addItem(QString());
        comboBox_single_trap_light_12_shape->addItem(QString());
        comboBox_single_trap_light_12_shape->addItem(QString());
        comboBox_single_trap_light_12_shape->addItem(QString());
        comboBox_single_trap_light_12_shape->setObjectName(QString::fromUtf8("comboBox_single_trap_light_12_shape"));

        gridLayout_single_trap_light_12->addWidget(comboBox_single_trap_light_12_shape, 0, 1, 1, 2);

        label_single_trap_light_12_position = new QLabel(groupCheck_single_trap_light_12_enabled);
        label_single_trap_light_12_position->setObjectName(QString::fromUtf8("label_single_trap_light_12_position"));

        gridLayout_single_trap_light_12->addWidget(label_single_trap_light_12_position, 1, 0, 1, 1);

        vect3_single_trap_light_12_position_x = new MyLineEdit(groupCheck_single_trap_light_12_enabled);
        vect3_single_trap_light_12_position_x->setObjectName(QString::fromUtf8("vect3_single_trap_light_12_position_x"));

        gridLayout_single_trap_light_12->addWidget(vect3_single_trap_light_12_position_x, 1, 1, 1, 1);

        vect3_single_trap_light_12_position_y = new MyLineEdit(groupCheck_single_trap_light_12_enabled);
        vect3_single_trap_light_12_position_y->setObjectName(QString::fromUtf8("vect3_single_trap_light_12_position_y"));

        gridLayout_single_trap_light_12->addWidget(vect3_single_trap_light_12_position_y, 1, 2, 1, 1);

        vect3_single_trap_light_12_position_z = new MyLineEdit(groupCheck_single_trap_light_12_enabled);
        vect3_single_trap_light_12_position_z->setObjectName(QString::fromUtf8("vect3_single_trap_light_12_position_z"));

        gridLayout_single_trap_light_12->addWidget(vect3_single_trap_light_12_position_z, 1, 3, 1, 1);

        pushButton_single_trap_light_12_place_camera = new QPushButton(groupCheck_single_trap_light_12_enabled);
        pushButton_single_trap_light_12_place_camera->setObjectName(QString::fromUtf8("pushButton_single_trap_light_12_place_camera"));

        gridLayout_single_trap_light_12->addWidget(pushButton_single_trap_light_12_place_camera, 1, 4, 1, 1);

        label_single_trap_light_12_size = new QLabel(groupCheck_single_trap_light_12_enabled);
        label_single_trap_light_12_size->setObjectName(QString::fromUtf8("label_single_trap_light_12_size"));

        gridLayout_single_trap_light_12->addWidget(label_single_trap_light_12_size, 2, 0, 1, 1);

        logedit_single_trap_light_12_size = new MyLineEdit(groupCheck_single_trap_light_12_enabled);
        logedit_single_trap_light_12_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_12_size"));

        gridLayout_single_trap_light_12->addWidget(logedit_single_trap_light_12_size, 2, 1, 1, 2);

        label_single_trap_light_12_size2 = new QLabel(groupCheck_single_trap_light_12_enabled);
        label_single_trap_light_12_size2->setObjectName(QString::fromUtf8("label_single_trap_light_12_size2"));

        gridLayout_single_trap_light_12->addWidget(label_single_trap_light_12_size2, 2, 3, 1, 1);

        logedit_single_trap_light_12_size2 = new MyLineEdit(groupCheck_single_trap_light_12_enabled);
        logedit_single_trap_light_12_size2->setObjectName(QString::fromUtf8("logedit_single_trap_light_12_size2"));

        gridLayout_single_trap_light_12->addWidget(logedit_single_trap_light_12_size2, 2, 4, 1, 1);

        label_single_trap_light_12_thickness = new QLabel(groupCheck_single_trap_light_12_enabled);
        label_single_trap_light_12_thickness->setObjectName(QString::fromUtf8("label_single_trap_light_12_thickness"));

        gridLayout_single_trap_light_12->addWidget(label_single_trap_light_12_thickness, 3, 0, 1, 1);

        logedit_single_trap_light_12_thickness = new MyLineEdit(groupCheck_single_trap_light_12_enabled);
        logedit_single_trap_light_12_thickness->setObjectName(QString::fromUtf8("logedit_single_trap_light_12_thickness"));

        gridLayout_single_trap_light_12->addWidget(logedit_single_trap_light_12_thickness, 3, 1, 1, 2);

        label_single_trap_light_12_rotation = new QLabel(groupCheck_single_trap_light_12_enabled);
        label_single_trap_light_12_rotation->setObjectName(QString::fromUtf8("label_single_trap_light_12_rotation"));

        gridLayout_single_trap_light_12->addWidget(label_single_trap_light_12_rotation, 4, 0, 1, 1);

        spinboxd3_single_trap_light_12_rotation_x = new MyDoubleSpinBox(groupCheck_single_trap_light_12_enabled);
        spinboxd3_single_trap_light_12_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_12_rotation_x"));

        gridLayout_single_trap_light_12->addWidget(spinboxd3_single_trap_light_12_rotation_x, 4, 1, 1, 1);

        spinboxd3_single_trap_light_12_rotation_y = new MyDoubleSpinBox(groupCheck_single_trap_light_12_enabled);
        spinboxd3_single_trap_light_12_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_12_rotation_y"));

        gridLayout_single_trap_light_12->addWidget(spinboxd3_single_trap_light_12_rotation_y, 4, 2, 1, 1);

        spinboxd3_single_trap_light_12_rotation_z = new MyDoubleSpinBox(groupCheck_single_trap_light_12_enabled);
        spinboxd3_single_trap_light_12_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_12_rotation_z"));

        gridLayout_single_trap_light_12->addWidget(spinboxd3_single_trap_light_12_rotation_z, 4, 3, 1, 1);

        label_single_trap_light_12_intensity = new QLabel(groupCheck_single_trap_light_12_enabled);
        label_single_trap_light_12_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_12_intensity"));

        gridLayout_single_trap_light_12->addWidget(label_single_trap_light_12_intensity, 5, 0, 1, 1);

        logedit_single_trap_light_12_intensity = new MyLineEdit(groupCheck_single_trap_light_12_enabled);
        logedit_single_trap_light_12_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_12_intensity"));

        gridLayout_single_trap_light_12->addWidget(logedit_single_trap_light_12_intensity, 5, 1, 1, 2);

        label_single_trap_light_12_color = new QLabel(groupCheck_single_trap_light_12_enabled);
        label_single_trap_light_12_color->setObjectName(QString::fromUtf8("label_single_trap_light_12_color"));

        gridLayout_single_trap_light_12->addWidget(label_single_trap_light_12_color, 6, 0, 1, 1);

        colorButton_single_trap_light_12_color = new MyColorButton(groupCheck_single_trap_light_12_enabled);
        colorButton_single_trap_light_12_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_12_color"));

        gridLayout_single_trap_light_12->addWidget(colorButton_single_trap_light_12_color, 6, 1, 1, 1);

        label_single_trap_light_12_gradient_color = new QLabel(groupCheck_single_trap_light_12_enabled);
        label_single_trap_light_12_gradient_color->setObjectName(QString::fromUtf8("label_single_trap_light_12_gradient_color"));

        gridLayout_single_trap_light_12->addWidget(label_single_trap_light_12_gradient_color, 6, 2, 1, 1);

        colorButton_single_trap_light_12_gradient_color = new MyColorButton(groupCheck_single_trap_light_12_enabled);
        colorButton_single_trap_light_12_gradient_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_12_gradient_color"));

        gridLayout_single_trap_light_12->addWidget(colorButton_single_trap_light_12_gradient_color, 6, 3, 1, 2);

        label_single_trap_light_12_visibility = new QLabel(groupCheck_single_trap_light_12_enabled);
        label_single_trap_light_12_visibility->setObjectName(QString::fromUtf8("label_single_trap_light_12_visibility"));

        gridLayout_single_trap_light_12->addWidget(label_single_trap_light_12_visibility, 7, 0, 1, 1);

        logedit_single_trap_light_12_visibility = new MyLineEdit(groupCheck_single_trap_light_12_enabled);
        logedit_single_trap_light_12_visibility->setObjectName(QString::fromUtf8("logedit_single_trap_light_12_visibility"));

        gridLayout_single_trap_light_12->addWidget(logedit_single_trap_light_12_visibility, 7, 1, 1, 2);

        label_single_trap_light_12_max_distance = new QLabel(groupCheck_single_trap_light_12_enabled);
        label_single_trap_light_12_max_distance->setObjectName(QString::fromUtf8("label_single_trap_light_12_max_distance"));

        gridLayout_single_trap_light_12->addWidget(label_single_trap_light_12_max_distance, 7, 3, 1, 1);

        logedit_single_trap_light_12_max_distance = new MyLineEdit(groupCheck_single_trap_light_12_enabled);
        logedit_single_trap_light_12_max_distance->setObjectName(QString::fromUtf8("logedit_single_trap_light_12_max_distance"));

        gridLayout_single_trap_light_12->addWidget(logedit_single_trap_light_12_max_distance, 7, 4, 1, 1);

        label_single_trap_light_12_sharpening = new QLabel(groupCheck_single_trap_light_12_enabled);
        label_single_trap_light_12_sharpening->setObjectName(QString::fromUtf8("label_single_trap_light_12_sharpening"));

        gridLayout_single_trap_light_12->addWidget(label_single_trap_light_12_sharpening, 8, 0, 1, 1);

        logedit_single_trap_light_12_sharpening = new MyLineEdit(groupCheck_single_trap_light_12_enabled);
        logedit_single_trap_light_12_sharpening->setObjectName(QString::fromUtf8("logedit_single_trap_light_12_sharpening"));

        gridLayout_single_trap_light_12->addWidget(logedit_single_trap_light_12_sharpening, 8, 1, 1, 2);

        label_single_trap_light_12_blur = new QLabel(groupCheck_single_trap_light_12_enabled);
        label_single_trap_light_12_blur->setObjectName(QString::fromUtf8("label_single_trap_light_12_blur"));

        gridLayout_single_trap_light_12->addWidget(label_single_trap_light_12_blur, 8, 3, 1, 1);

        logedit_single_trap_light_12_blur = new MyLineEdit(groupCheck_single_trap_light_12_enabled);
        logedit_single_trap_light_12_blur->setObjectName(QString::fromUtf8("logedit_single_trap_light_12_blur"));

        gridLayout_single_trap_light_12->addWidget(logedit_single_trap_light_12_blur, 8, 4, 1, 1);

        label_single_trap_light_12_solid_intensity = new QLabel(groupCheck_single_trap_light_12_enabled);
        label_single_trap_light_12_solid_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_12_solid_intensity"));

        gridLayout_single_trap_light_12->addWidget(label_single_trap_light_12_solid_intensity, 9, 0, 1, 1);

        logedit_single_trap_light_12_solid_intensity = new MyLineEdit(groupCheck_single_trap_light_12_enabled);
        logedit_single_trap_light_12_solid_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_12_solid_intensity"));

        gridLayout_single_trap_light_12->addWidget(logedit_single_trap_light_12_solid_intensity, 9, 1, 1, 2);

        label_single_trap_light_12_softness = new QLabel(groupCheck_single_trap_light_12_enabled);
        label_single_trap_light_12_softness->setObjectName(QString::fromUtf8("label_single_trap_light_12_softness"));

        gridLayout_single_trap_light_12->addWidget(label_single_trap_light_12_softness, 9, 3, 1, 1);

        logedit_single_trap_light_12_softness = new MyLineEdit(groupCheck_single_trap_light_12_enabled);
        logedit_single_trap_light_12_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_12_softness"));

        gridLayout_single_trap_light_12->addWidget(logedit_single_trap_light_12_softness, 9, 4, 1, 1);

        label_single_trap_light_12_relative_size = new QLabel(groupCheck_single_trap_light_12_enabled);
        label_single_trap_light_12_relative_size->setObjectName(QString::fromUtf8("label_single_trap_light_12_relative_size"));

        gridLayout_single_trap_light_12->addWidget(label_single_trap_light_12_relative_size, 10, 0, 1, 1);

        logedit_single_trap_light_12_relative_size = new MyLineEdit(groupCheck_single_trap_light_12_enabled);
        logedit_single_trap_light_12_relative_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_12_relative_size"));

        gridLayout_single_trap_light_12->addWidget(logedit_single_trap_light_12_relative_size, 10, 1, 1, 2);

        checkBox_single_trap_light_12_pre_transformed = new MyCheckBox(groupCheck_single_trap_light_12_enabled);
        checkBox_single_trap_light_12_pre_transformed->setObjectName(QString::fromUtf8("checkBox_single_trap_light_12_pre_transformed"));

        gridLayout_single_trap_light_12->addWidget(checkBox_single_trap_light_12_pre_transformed, 11, 0, 1, 1);

        label_single_trap_light_12_position_mode = new QLabel(groupCheck_single_trap_light_12_enabled);
        label_single_trap_light_12_position_mode->setObjectName(QString::fromUtf8("label_single_trap_light_12_position_mode"));

        gridLayout_single_trap_light_12->addWidget(label_single_trap_light_12_position_mode, 12, 0, 1, 1);

        comboBox_single_trap_light_12_position_mode = new MyComboBox(groupCheck_single_trap_light_12_enabled);
        comboBox_single_trap_light_12_position_mode->addItem(QString());
        comboBox_single_trap_light_12_position_mode->addItem(QString());
        comboBox_single_trap_light_12_position_mode->addItem(QString());
        comboBox_single_trap_light_12_position_mode->addItem(QString());
        comboBox_single_trap_light_12_position_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_12_position_mode"));

        gridLayout_single_trap_light_12->addWidget(comboBox_single_trap_light_12_position_mode, 12, 1, 1, 2);

        label_single_trap_light_12_coloring_mode = new QLabel(groupCheck_single_trap_light_12_enabled);
        label_single_trap_light_12_coloring_mode->setObjectName(QString::fromUtf8("label_single_trap_light_12_coloring_mode"));

        gridLayout_single_trap_light_12->addWidget(label_single_trap_light_12_coloring_mode, 13, 0, 1, 1);

        comboBox_single_trap_light_12_coloring_mode = new MyComboBox(groupCheck_single_trap_light_12_enabled);
        comboBox_single_trap_light_12_coloring_mode->addItem(QString());
        comboBox_single_trap_light_12_coloring_mode->addItem(QString());
        comboBox_single_trap_light_12_coloring_mode->addItem(QString());
        comboBox_single_trap_light_12_coloring_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_12_coloring_mode"));

        gridLayout_single_trap_light_12->addWidget(comboBox_single_trap_light_12_coloring_mode, 13, 1, 1, 2);

        label_single_trap_light_12_falloff_type = new QLabel(groupCheck_single_trap_light_12_enabled);
        label_single_trap_light_12_falloff_type->setObjectName(QString::fromUtf8("label_single_trap_light_12_falloff_type"));

        gridLayout_single_trap_light_12->addWidget(label_single_trap_light_12_falloff_type, 14, 0, 1, 1);

        comboBox_single_trap_light_12_falloff_type = new MyComboBox(groupCheck_single_trap_light_12_enabled);
        comboBox_single_trap_light_12_falloff_type->addItem(QString());
        comboBox_single_trap_light_12_falloff_type->addItem(QString());
        comboBox_single_trap_light_12_falloff_type->addItem(QString());
        comboBox_single_trap_light_12_falloff_type->addItem(QString());
        comboBox_single_trap_light_12_falloff_type->addItem(QString());
        comboBox_single_trap_light_12_falloff_type->setObjectName(QString::fromUtf8("comboBox_single_trap_light_12_falloff_type"));

        gridLayout_single_trap_light_12->addWidget(comboBox_single_trap_light_12_falloff_type, 14, 1, 1, 2);

        label_single_trap_light_12_edge_softness = new QLabel(groupCheck_single_trap_light_12_enabled);
        label_single_trap_light_12_edge_softness->setObjectName(QString::fromUtf8("label_single_trap_light_12_edge_softness"));

        gridLayout_single_trap_light_12->addWidget(label_single_trap_light_12_edge_softness, 15, 0, 1, 1);

        logedit_single_trap_light_12_edge_softness = new MyLineEdit(groupCheck_single_trap_light_12_enabled);
        logedit_single_trap_light_12_edge_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_12_edge_softness"));

        gridLayout_single_trap_light_12->addWidget(logedit_single_trap_light_12_edge_softness, 15, 1, 1, 2);

        label_single_trap_light_12_anim_orbit_radius = new QLabel(groupCheck_single_trap_light_12_enabled);
        label_single_trap_light_12_anim_orbit_radius->setObjectName(QString::fromUtf8("label_single_trap_light_12_anim_orbit_radius"));

        gridLayout_single_trap_light_12->addWidget(label_single_trap_light_12_anim_orbit_radius, 16, 0, 1, 1);

        logedit_single_trap_light_12_anim_orbit_radius = new MyLineEdit(groupCheck_single_trap_light_12_enabled);
        logedit_single_trap_light_12_anim_orbit_radius->setObjectName(QString::fromUtf8("logedit_single_trap_light_12_anim_orbit_radius"));

        gridLayout_single_trap_light_12->addWidget(logedit_single_trap_light_12_anim_orbit_radius, 16, 1, 1, 1);

        logedit_single_trap_light_12_anim_orbit_speed = new MyLineEdit(groupCheck_single_trap_light_12_enabled);
        logedit_single_trap_light_12_anim_orbit_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_12_anim_orbit_speed"));

        gridLayout_single_trap_light_12->addWidget(logedit_single_trap_light_12_anim_orbit_speed, 16, 2, 1, 1);

        logedit_single_trap_light_12_anim_pulsate_speed = new MyLineEdit(groupCheck_single_trap_light_12_enabled);
        logedit_single_trap_light_12_anim_pulsate_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_12_anim_pulsate_speed"));

        gridLayout_single_trap_light_12->addWidget(logedit_single_trap_light_12_anim_pulsate_speed, 16, 3, 1, 1);

        logedit_single_trap_light_12_anim_pulsate_amount = new MyLineEdit(groupCheck_single_trap_light_12_enabled);
        logedit_single_trap_light_12_anim_pulsate_amount->setObjectName(QString::fromUtf8("logedit_single_trap_light_12_anim_pulsate_amount"));

        gridLayout_single_trap_light_12->addWidget(logedit_single_trap_light_12_anim_pulsate_amount, 16, 4, 1, 1);

        pushButton_single_trap_light_12_place_surface = new QPushButton(groupCheck_single_trap_light_12_enabled);
        pushButton_single_trap_light_12_place_surface->setObjectName(QString::fromUtf8("pushButton_single_trap_light_12_place_surface"));

        gridLayout_single_trap_light_12->addWidget(pushButton_single_trap_light_12_place_surface, 17, 0, 1, 5);

        pushButton_single_trap_light_12_place_target = new QPushButton(groupCheck_single_trap_light_12_enabled);
        pushButton_single_trap_light_12_place_target->setObjectName(QString::fromUtf8("pushButton_single_trap_light_12_place_target"));

        gridLayout_single_trap_light_12->addWidget(pushButton_single_trap_light_12_place_target, 18, 0, 1, 5);


        verticalLayout_single_trap_layers->addWidget(groupCheck_single_trap_light_12_enabled);

        groupCheck_single_trap_light_13_enabled = new MyGroupBox(scrollAreaWidgetContents_single_trap);
        groupCheck_single_trap_light_13_enabled->setObjectName(QString::fromUtf8("groupCheck_single_trap_light_13_enabled"));
        groupCheck_single_trap_light_13_enabled->setCheckable(true);
        gridLayout_single_trap_light_13 = new QGridLayout(groupCheck_single_trap_light_13_enabled);
        gridLayout_single_trap_light_13->setSpacing(2);
        gridLayout_single_trap_light_13->setObjectName(QString::fromUtf8("gridLayout_single_trap_light_13"));
        label_single_trap_light_13_shape = new QLabel(groupCheck_single_trap_light_13_enabled);
        label_single_trap_light_13_shape->setObjectName(QString::fromUtf8("label_single_trap_light_13_shape"));

        gridLayout_single_trap_light_13->addWidget(label_single_trap_light_13_shape, 0, 0, 1, 1);

        comboBox_single_trap_light_13_shape = new MyComboBox(groupCheck_single_trap_light_13_enabled);
        comboBox_single_trap_light_13_shape->addItem(QString());
        comboBox_single_trap_light_13_shape->addItem(QString());
        comboBox_single_trap_light_13_shape->addItem(QString());
        comboBox_single_trap_light_13_shape->addItem(QString());
        comboBox_single_trap_light_13_shape->addItem(QString());
        comboBox_single_trap_light_13_shape->addItem(QString());
        comboBox_single_trap_light_13_shape->addItem(QString());
        comboBox_single_trap_light_13_shape->addItem(QString());
        comboBox_single_trap_light_13_shape->addItem(QString());
        comboBox_single_trap_light_13_shape->addItem(QString());
        comboBox_single_trap_light_13_shape->addItem(QString());
        comboBox_single_trap_light_13_shape->addItem(QString());
        comboBox_single_trap_light_13_shape->addItem(QString());
        comboBox_single_trap_light_13_shape->addItem(QString());
        comboBox_single_trap_light_13_shape->setObjectName(QString::fromUtf8("comboBox_single_trap_light_13_shape"));

        gridLayout_single_trap_light_13->addWidget(comboBox_single_trap_light_13_shape, 0, 1, 1, 2);

        label_single_trap_light_13_position = new QLabel(groupCheck_single_trap_light_13_enabled);
        label_single_trap_light_13_position->setObjectName(QString::fromUtf8("label_single_trap_light_13_position"));

        gridLayout_single_trap_light_13->addWidget(label_single_trap_light_13_position, 1, 0, 1, 1);

        vect3_single_trap_light_13_position_x = new MyLineEdit(groupCheck_single_trap_light_13_enabled);
        vect3_single_trap_light_13_position_x->setObjectName(QString::fromUtf8("vect3_single_trap_light_13_position_x"));

        gridLayout_single_trap_light_13->addWidget(vect3_single_trap_light_13_position_x, 1, 1, 1, 1);

        vect3_single_trap_light_13_position_y = new MyLineEdit(groupCheck_single_trap_light_13_enabled);
        vect3_single_trap_light_13_position_y->setObjectName(QString::fromUtf8("vect3_single_trap_light_13_position_y"));

        gridLayout_single_trap_light_13->addWidget(vect3_single_trap_light_13_position_y, 1, 2, 1, 1);

        vect3_single_trap_light_13_position_z = new MyLineEdit(groupCheck_single_trap_light_13_enabled);
        vect3_single_trap_light_13_position_z->setObjectName(QString::fromUtf8("vect3_single_trap_light_13_position_z"));

        gridLayout_single_trap_light_13->addWidget(vect3_single_trap_light_13_position_z, 1, 3, 1, 1);

        pushButton_single_trap_light_13_place_camera = new QPushButton(groupCheck_single_trap_light_13_enabled);
        pushButton_single_trap_light_13_place_camera->setObjectName(QString::fromUtf8("pushButton_single_trap_light_13_place_camera"));

        gridLayout_single_trap_light_13->addWidget(pushButton_single_trap_light_13_place_camera, 1, 4, 1, 1);

        label_single_trap_light_13_size = new QLabel(groupCheck_single_trap_light_13_enabled);
        label_single_trap_light_13_size->setObjectName(QString::fromUtf8("label_single_trap_light_13_size"));

        gridLayout_single_trap_light_13->addWidget(label_single_trap_light_13_size, 2, 0, 1, 1);

        logedit_single_trap_light_13_size = new MyLineEdit(groupCheck_single_trap_light_13_enabled);
        logedit_single_trap_light_13_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_13_size"));

        gridLayout_single_trap_light_13->addWidget(logedit_single_trap_light_13_size, 2, 1, 1, 2);

        label_single_trap_light_13_size2 = new QLabel(groupCheck_single_trap_light_13_enabled);
        label_single_trap_light_13_size2->setObjectName(QString::fromUtf8("label_single_trap_light_13_size2"));

        gridLayout_single_trap_light_13->addWidget(label_single_trap_light_13_size2, 2, 3, 1, 1);

        logedit_single_trap_light_13_size2 = new MyLineEdit(groupCheck_single_trap_light_13_enabled);
        logedit_single_trap_light_13_size2->setObjectName(QString::fromUtf8("logedit_single_trap_light_13_size2"));

        gridLayout_single_trap_light_13->addWidget(logedit_single_trap_light_13_size2, 2, 4, 1, 1);

        label_single_trap_light_13_thickness = new QLabel(groupCheck_single_trap_light_13_enabled);
        label_single_trap_light_13_thickness->setObjectName(QString::fromUtf8("label_single_trap_light_13_thickness"));

        gridLayout_single_trap_light_13->addWidget(label_single_trap_light_13_thickness, 3, 0, 1, 1);

        logedit_single_trap_light_13_thickness = new MyLineEdit(groupCheck_single_trap_light_13_enabled);
        logedit_single_trap_light_13_thickness->setObjectName(QString::fromUtf8("logedit_single_trap_light_13_thickness"));

        gridLayout_single_trap_light_13->addWidget(logedit_single_trap_light_13_thickness, 3, 1, 1, 2);

        label_single_trap_light_13_rotation = new QLabel(groupCheck_single_trap_light_13_enabled);
        label_single_trap_light_13_rotation->setObjectName(QString::fromUtf8("label_single_trap_light_13_rotation"));

        gridLayout_single_trap_light_13->addWidget(label_single_trap_light_13_rotation, 4, 0, 1, 1);

        spinboxd3_single_trap_light_13_rotation_x = new MyDoubleSpinBox(groupCheck_single_trap_light_13_enabled);
        spinboxd3_single_trap_light_13_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_13_rotation_x"));

        gridLayout_single_trap_light_13->addWidget(spinboxd3_single_trap_light_13_rotation_x, 4, 1, 1, 1);

        spinboxd3_single_trap_light_13_rotation_y = new MyDoubleSpinBox(groupCheck_single_trap_light_13_enabled);
        spinboxd3_single_trap_light_13_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_13_rotation_y"));

        gridLayout_single_trap_light_13->addWidget(spinboxd3_single_trap_light_13_rotation_y, 4, 2, 1, 1);

        spinboxd3_single_trap_light_13_rotation_z = new MyDoubleSpinBox(groupCheck_single_trap_light_13_enabled);
        spinboxd3_single_trap_light_13_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_13_rotation_z"));

        gridLayout_single_trap_light_13->addWidget(spinboxd3_single_trap_light_13_rotation_z, 4, 3, 1, 1);

        label_single_trap_light_13_intensity = new QLabel(groupCheck_single_trap_light_13_enabled);
        label_single_trap_light_13_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_13_intensity"));

        gridLayout_single_trap_light_13->addWidget(label_single_trap_light_13_intensity, 5, 0, 1, 1);

        logedit_single_trap_light_13_intensity = new MyLineEdit(groupCheck_single_trap_light_13_enabled);
        logedit_single_trap_light_13_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_13_intensity"));

        gridLayout_single_trap_light_13->addWidget(logedit_single_trap_light_13_intensity, 5, 1, 1, 2);

        label_single_trap_light_13_color = new QLabel(groupCheck_single_trap_light_13_enabled);
        label_single_trap_light_13_color->setObjectName(QString::fromUtf8("label_single_trap_light_13_color"));

        gridLayout_single_trap_light_13->addWidget(label_single_trap_light_13_color, 6, 0, 1, 1);

        colorButton_single_trap_light_13_color = new MyColorButton(groupCheck_single_trap_light_13_enabled);
        colorButton_single_trap_light_13_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_13_color"));

        gridLayout_single_trap_light_13->addWidget(colorButton_single_trap_light_13_color, 6, 1, 1, 1);

        label_single_trap_light_13_gradient_color = new QLabel(groupCheck_single_trap_light_13_enabled);
        label_single_trap_light_13_gradient_color->setObjectName(QString::fromUtf8("label_single_trap_light_13_gradient_color"));

        gridLayout_single_trap_light_13->addWidget(label_single_trap_light_13_gradient_color, 6, 2, 1, 1);

        colorButton_single_trap_light_13_gradient_color = new MyColorButton(groupCheck_single_trap_light_13_enabled);
        colorButton_single_trap_light_13_gradient_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_13_gradient_color"));

        gridLayout_single_trap_light_13->addWidget(colorButton_single_trap_light_13_gradient_color, 6, 3, 1, 2);

        label_single_trap_light_13_visibility = new QLabel(groupCheck_single_trap_light_13_enabled);
        label_single_trap_light_13_visibility->setObjectName(QString::fromUtf8("label_single_trap_light_13_visibility"));

        gridLayout_single_trap_light_13->addWidget(label_single_trap_light_13_visibility, 7, 0, 1, 1);

        logedit_single_trap_light_13_visibility = new MyLineEdit(groupCheck_single_trap_light_13_enabled);
        logedit_single_trap_light_13_visibility->setObjectName(QString::fromUtf8("logedit_single_trap_light_13_visibility"));

        gridLayout_single_trap_light_13->addWidget(logedit_single_trap_light_13_visibility, 7, 1, 1, 2);

        label_single_trap_light_13_max_distance = new QLabel(groupCheck_single_trap_light_13_enabled);
        label_single_trap_light_13_max_distance->setObjectName(QString::fromUtf8("label_single_trap_light_13_max_distance"));

        gridLayout_single_trap_light_13->addWidget(label_single_trap_light_13_max_distance, 7, 3, 1, 1);

        logedit_single_trap_light_13_max_distance = new MyLineEdit(groupCheck_single_trap_light_13_enabled);
        logedit_single_trap_light_13_max_distance->setObjectName(QString::fromUtf8("logedit_single_trap_light_13_max_distance"));

        gridLayout_single_trap_light_13->addWidget(logedit_single_trap_light_13_max_distance, 7, 4, 1, 1);

        label_single_trap_light_13_sharpening = new QLabel(groupCheck_single_trap_light_13_enabled);
        label_single_trap_light_13_sharpening->setObjectName(QString::fromUtf8("label_single_trap_light_13_sharpening"));

        gridLayout_single_trap_light_13->addWidget(label_single_trap_light_13_sharpening, 8, 0, 1, 1);

        logedit_single_trap_light_13_sharpening = new MyLineEdit(groupCheck_single_trap_light_13_enabled);
        logedit_single_trap_light_13_sharpening->setObjectName(QString::fromUtf8("logedit_single_trap_light_13_sharpening"));

        gridLayout_single_trap_light_13->addWidget(logedit_single_trap_light_13_sharpening, 8, 1, 1, 2);

        label_single_trap_light_13_blur = new QLabel(groupCheck_single_trap_light_13_enabled);
        label_single_trap_light_13_blur->setObjectName(QString::fromUtf8("label_single_trap_light_13_blur"));

        gridLayout_single_trap_light_13->addWidget(label_single_trap_light_13_blur, 8, 3, 1, 1);

        logedit_single_trap_light_13_blur = new MyLineEdit(groupCheck_single_trap_light_13_enabled);
        logedit_single_trap_light_13_blur->setObjectName(QString::fromUtf8("logedit_single_trap_light_13_blur"));

        gridLayout_single_trap_light_13->addWidget(logedit_single_trap_light_13_blur, 8, 4, 1, 1);

        label_single_trap_light_13_solid_intensity = new QLabel(groupCheck_single_trap_light_13_enabled);
        label_single_trap_light_13_solid_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_13_solid_intensity"));

        gridLayout_single_trap_light_13->addWidget(label_single_trap_light_13_solid_intensity, 9, 0, 1, 1);

        logedit_single_trap_light_13_solid_intensity = new MyLineEdit(groupCheck_single_trap_light_13_enabled);
        logedit_single_trap_light_13_solid_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_13_solid_intensity"));

        gridLayout_single_trap_light_13->addWidget(logedit_single_trap_light_13_solid_intensity, 9, 1, 1, 2);

        label_single_trap_light_13_softness = new QLabel(groupCheck_single_trap_light_13_enabled);
        label_single_trap_light_13_softness->setObjectName(QString::fromUtf8("label_single_trap_light_13_softness"));

        gridLayout_single_trap_light_13->addWidget(label_single_trap_light_13_softness, 9, 3, 1, 1);

        logedit_single_trap_light_13_softness = new MyLineEdit(groupCheck_single_trap_light_13_enabled);
        logedit_single_trap_light_13_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_13_softness"));

        gridLayout_single_trap_light_13->addWidget(logedit_single_trap_light_13_softness, 9, 4, 1, 1);

        label_single_trap_light_13_relative_size = new QLabel(groupCheck_single_trap_light_13_enabled);
        label_single_trap_light_13_relative_size->setObjectName(QString::fromUtf8("label_single_trap_light_13_relative_size"));

        gridLayout_single_trap_light_13->addWidget(label_single_trap_light_13_relative_size, 10, 0, 1, 1);

        logedit_single_trap_light_13_relative_size = new MyLineEdit(groupCheck_single_trap_light_13_enabled);
        logedit_single_trap_light_13_relative_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_13_relative_size"));

        gridLayout_single_trap_light_13->addWidget(logedit_single_trap_light_13_relative_size, 10, 1, 1, 2);

        checkBox_single_trap_light_13_pre_transformed = new MyCheckBox(groupCheck_single_trap_light_13_enabled);
        checkBox_single_trap_light_13_pre_transformed->setObjectName(QString::fromUtf8("checkBox_single_trap_light_13_pre_transformed"));

        gridLayout_single_trap_light_13->addWidget(checkBox_single_trap_light_13_pre_transformed, 11, 0, 1, 1);

        label_single_trap_light_13_position_mode = new QLabel(groupCheck_single_trap_light_13_enabled);
        label_single_trap_light_13_position_mode->setObjectName(QString::fromUtf8("label_single_trap_light_13_position_mode"));

        gridLayout_single_trap_light_13->addWidget(label_single_trap_light_13_position_mode, 12, 0, 1, 1);

        comboBox_single_trap_light_13_position_mode = new MyComboBox(groupCheck_single_trap_light_13_enabled);
        comboBox_single_trap_light_13_position_mode->addItem(QString());
        comboBox_single_trap_light_13_position_mode->addItem(QString());
        comboBox_single_trap_light_13_position_mode->addItem(QString());
        comboBox_single_trap_light_13_position_mode->addItem(QString());
        comboBox_single_trap_light_13_position_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_13_position_mode"));

        gridLayout_single_trap_light_13->addWidget(comboBox_single_trap_light_13_position_mode, 12, 1, 1, 2);

        label_single_trap_light_13_coloring_mode = new QLabel(groupCheck_single_trap_light_13_enabled);
        label_single_trap_light_13_coloring_mode->setObjectName(QString::fromUtf8("label_single_trap_light_13_coloring_mode"));

        gridLayout_single_trap_light_13->addWidget(label_single_trap_light_13_coloring_mode, 13, 0, 1, 1);

        comboBox_single_trap_light_13_coloring_mode = new MyComboBox(groupCheck_single_trap_light_13_enabled);
        comboBox_single_trap_light_13_coloring_mode->addItem(QString());
        comboBox_single_trap_light_13_coloring_mode->addItem(QString());
        comboBox_single_trap_light_13_coloring_mode->addItem(QString());
        comboBox_single_trap_light_13_coloring_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_13_coloring_mode"));

        gridLayout_single_trap_light_13->addWidget(comboBox_single_trap_light_13_coloring_mode, 13, 1, 1, 2);

        label_single_trap_light_13_falloff_type = new QLabel(groupCheck_single_trap_light_13_enabled);
        label_single_trap_light_13_falloff_type->setObjectName(QString::fromUtf8("label_single_trap_light_13_falloff_type"));

        gridLayout_single_trap_light_13->addWidget(label_single_trap_light_13_falloff_type, 14, 0, 1, 1);

        comboBox_single_trap_light_13_falloff_type = new MyComboBox(groupCheck_single_trap_light_13_enabled);
        comboBox_single_trap_light_13_falloff_type->addItem(QString());
        comboBox_single_trap_light_13_falloff_type->addItem(QString());
        comboBox_single_trap_light_13_falloff_type->addItem(QString());
        comboBox_single_trap_light_13_falloff_type->addItem(QString());
        comboBox_single_trap_light_13_falloff_type->addItem(QString());
        comboBox_single_trap_light_13_falloff_type->setObjectName(QString::fromUtf8("comboBox_single_trap_light_13_falloff_type"));

        gridLayout_single_trap_light_13->addWidget(comboBox_single_trap_light_13_falloff_type, 14, 1, 1, 2);

        label_single_trap_light_13_edge_softness = new QLabel(groupCheck_single_trap_light_13_enabled);
        label_single_trap_light_13_edge_softness->setObjectName(QString::fromUtf8("label_single_trap_light_13_edge_softness"));

        gridLayout_single_trap_light_13->addWidget(label_single_trap_light_13_edge_softness, 15, 0, 1, 1);

        logedit_single_trap_light_13_edge_softness = new MyLineEdit(groupCheck_single_trap_light_13_enabled);
        logedit_single_trap_light_13_edge_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_13_edge_softness"));

        gridLayout_single_trap_light_13->addWidget(logedit_single_trap_light_13_edge_softness, 15, 1, 1, 2);

        label_single_trap_light_13_anim_orbit_radius = new QLabel(groupCheck_single_trap_light_13_enabled);
        label_single_trap_light_13_anim_orbit_radius->setObjectName(QString::fromUtf8("label_single_trap_light_13_anim_orbit_radius"));

        gridLayout_single_trap_light_13->addWidget(label_single_trap_light_13_anim_orbit_radius, 16, 0, 1, 1);

        logedit_single_trap_light_13_anim_orbit_radius = new MyLineEdit(groupCheck_single_trap_light_13_enabled);
        logedit_single_trap_light_13_anim_orbit_radius->setObjectName(QString::fromUtf8("logedit_single_trap_light_13_anim_orbit_radius"));

        gridLayout_single_trap_light_13->addWidget(logedit_single_trap_light_13_anim_orbit_radius, 16, 1, 1, 1);

        logedit_single_trap_light_13_anim_orbit_speed = new MyLineEdit(groupCheck_single_trap_light_13_enabled);
        logedit_single_trap_light_13_anim_orbit_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_13_anim_orbit_speed"));

        gridLayout_single_trap_light_13->addWidget(logedit_single_trap_light_13_anim_orbit_speed, 16, 2, 1, 1);

        logedit_single_trap_light_13_anim_pulsate_speed = new MyLineEdit(groupCheck_single_trap_light_13_enabled);
        logedit_single_trap_light_13_anim_pulsate_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_13_anim_pulsate_speed"));

        gridLayout_single_trap_light_13->addWidget(logedit_single_trap_light_13_anim_pulsate_speed, 16, 3, 1, 1);

        logedit_single_trap_light_13_anim_pulsate_amount = new MyLineEdit(groupCheck_single_trap_light_13_enabled);
        logedit_single_trap_light_13_anim_pulsate_amount->setObjectName(QString::fromUtf8("logedit_single_trap_light_13_anim_pulsate_amount"));

        gridLayout_single_trap_light_13->addWidget(logedit_single_trap_light_13_anim_pulsate_amount, 16, 4, 1, 1);

        pushButton_single_trap_light_13_place_surface = new QPushButton(groupCheck_single_trap_light_13_enabled);
        pushButton_single_trap_light_13_place_surface->setObjectName(QString::fromUtf8("pushButton_single_trap_light_13_place_surface"));

        gridLayout_single_trap_light_13->addWidget(pushButton_single_trap_light_13_place_surface, 17, 0, 1, 5);

        pushButton_single_trap_light_13_place_target = new QPushButton(groupCheck_single_trap_light_13_enabled);
        pushButton_single_trap_light_13_place_target->setObjectName(QString::fromUtf8("pushButton_single_trap_light_13_place_target"));

        gridLayout_single_trap_light_13->addWidget(pushButton_single_trap_light_13_place_target, 18, 0, 1, 5);


        verticalLayout_single_trap_layers->addWidget(groupCheck_single_trap_light_13_enabled);

        groupCheck_single_trap_light_14_enabled = new MyGroupBox(scrollAreaWidgetContents_single_trap);
        groupCheck_single_trap_light_14_enabled->setObjectName(QString::fromUtf8("groupCheck_single_trap_light_14_enabled"));
        groupCheck_single_trap_light_14_enabled->setCheckable(true);
        gridLayout_single_trap_light_14 = new QGridLayout(groupCheck_single_trap_light_14_enabled);
        gridLayout_single_trap_light_14->setSpacing(2);
        gridLayout_single_trap_light_14->setObjectName(QString::fromUtf8("gridLayout_single_trap_light_14"));
        label_single_trap_light_14_shape = new QLabel(groupCheck_single_trap_light_14_enabled);
        label_single_trap_light_14_shape->setObjectName(QString::fromUtf8("label_single_trap_light_14_shape"));

        gridLayout_single_trap_light_14->addWidget(label_single_trap_light_14_shape, 0, 0, 1, 1);

        comboBox_single_trap_light_14_shape = new MyComboBox(groupCheck_single_trap_light_14_enabled);
        comboBox_single_trap_light_14_shape->addItem(QString());
        comboBox_single_trap_light_14_shape->addItem(QString());
        comboBox_single_trap_light_14_shape->addItem(QString());
        comboBox_single_trap_light_14_shape->addItem(QString());
        comboBox_single_trap_light_14_shape->addItem(QString());
        comboBox_single_trap_light_14_shape->addItem(QString());
        comboBox_single_trap_light_14_shape->addItem(QString());
        comboBox_single_trap_light_14_shape->addItem(QString());
        comboBox_single_trap_light_14_shape->addItem(QString());
        comboBox_single_trap_light_14_shape->addItem(QString());
        comboBox_single_trap_light_14_shape->addItem(QString());
        comboBox_single_trap_light_14_shape->addItem(QString());
        comboBox_single_trap_light_14_shape->addItem(QString());
        comboBox_single_trap_light_14_shape->addItem(QString());
        comboBox_single_trap_light_14_shape->setObjectName(QString::fromUtf8("comboBox_single_trap_light_14_shape"));

        gridLayout_single_trap_light_14->addWidget(comboBox_single_trap_light_14_shape, 0, 1, 1, 2);

        label_single_trap_light_14_position = new QLabel(groupCheck_single_trap_light_14_enabled);
        label_single_trap_light_14_position->setObjectName(QString::fromUtf8("label_single_trap_light_14_position"));

        gridLayout_single_trap_light_14->addWidget(label_single_trap_light_14_position, 1, 0, 1, 1);

        vect3_single_trap_light_14_position_x = new MyLineEdit(groupCheck_single_trap_light_14_enabled);
        vect3_single_trap_light_14_position_x->setObjectName(QString::fromUtf8("vect3_single_trap_light_14_position_x"));

        gridLayout_single_trap_light_14->addWidget(vect3_single_trap_light_14_position_x, 1, 1, 1, 1);

        vect3_single_trap_light_14_position_y = new MyLineEdit(groupCheck_single_trap_light_14_enabled);
        vect3_single_trap_light_14_position_y->setObjectName(QString::fromUtf8("vect3_single_trap_light_14_position_y"));

        gridLayout_single_trap_light_14->addWidget(vect3_single_trap_light_14_position_y, 1, 2, 1, 1);

        vect3_single_trap_light_14_position_z = new MyLineEdit(groupCheck_single_trap_light_14_enabled);
        vect3_single_trap_light_14_position_z->setObjectName(QString::fromUtf8("vect3_single_trap_light_14_position_z"));

        gridLayout_single_trap_light_14->addWidget(vect3_single_trap_light_14_position_z, 1, 3, 1, 1);

        pushButton_single_trap_light_14_place_camera = new QPushButton(groupCheck_single_trap_light_14_enabled);
        pushButton_single_trap_light_14_place_camera->setObjectName(QString::fromUtf8("pushButton_single_trap_light_14_place_camera"));

        gridLayout_single_trap_light_14->addWidget(pushButton_single_trap_light_14_place_camera, 1, 4, 1, 1);

        label_single_trap_light_14_size = new QLabel(groupCheck_single_trap_light_14_enabled);
        label_single_trap_light_14_size->setObjectName(QString::fromUtf8("label_single_trap_light_14_size"));

        gridLayout_single_trap_light_14->addWidget(label_single_trap_light_14_size, 2, 0, 1, 1);

        logedit_single_trap_light_14_size = new MyLineEdit(groupCheck_single_trap_light_14_enabled);
        logedit_single_trap_light_14_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_14_size"));

        gridLayout_single_trap_light_14->addWidget(logedit_single_trap_light_14_size, 2, 1, 1, 2);

        label_single_trap_light_14_size2 = new QLabel(groupCheck_single_trap_light_14_enabled);
        label_single_trap_light_14_size2->setObjectName(QString::fromUtf8("label_single_trap_light_14_size2"));

        gridLayout_single_trap_light_14->addWidget(label_single_trap_light_14_size2, 2, 3, 1, 1);

        logedit_single_trap_light_14_size2 = new MyLineEdit(groupCheck_single_trap_light_14_enabled);
        logedit_single_trap_light_14_size2->setObjectName(QString::fromUtf8("logedit_single_trap_light_14_size2"));

        gridLayout_single_trap_light_14->addWidget(logedit_single_trap_light_14_size2, 2, 4, 1, 1);

        label_single_trap_light_14_thickness = new QLabel(groupCheck_single_trap_light_14_enabled);
        label_single_trap_light_14_thickness->setObjectName(QString::fromUtf8("label_single_trap_light_14_thickness"));

        gridLayout_single_trap_light_14->addWidget(label_single_trap_light_14_thickness, 3, 0, 1, 1);

        logedit_single_trap_light_14_thickness = new MyLineEdit(groupCheck_single_trap_light_14_enabled);
        logedit_single_trap_light_14_thickness->setObjectName(QString::fromUtf8("logedit_single_trap_light_14_thickness"));

        gridLayout_single_trap_light_14->addWidget(logedit_single_trap_light_14_thickness, 3, 1, 1, 2);

        label_single_trap_light_14_rotation = new QLabel(groupCheck_single_trap_light_14_enabled);
        label_single_trap_light_14_rotation->setObjectName(QString::fromUtf8("label_single_trap_light_14_rotation"));

        gridLayout_single_trap_light_14->addWidget(label_single_trap_light_14_rotation, 4, 0, 1, 1);

        spinboxd3_single_trap_light_14_rotation_x = new MyDoubleSpinBox(groupCheck_single_trap_light_14_enabled);
        spinboxd3_single_trap_light_14_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_14_rotation_x"));

        gridLayout_single_trap_light_14->addWidget(spinboxd3_single_trap_light_14_rotation_x, 4, 1, 1, 1);

        spinboxd3_single_trap_light_14_rotation_y = new MyDoubleSpinBox(groupCheck_single_trap_light_14_enabled);
        spinboxd3_single_trap_light_14_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_14_rotation_y"));

        gridLayout_single_trap_light_14->addWidget(spinboxd3_single_trap_light_14_rotation_y, 4, 2, 1, 1);

        spinboxd3_single_trap_light_14_rotation_z = new MyDoubleSpinBox(groupCheck_single_trap_light_14_enabled);
        spinboxd3_single_trap_light_14_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_14_rotation_z"));

        gridLayout_single_trap_light_14->addWidget(spinboxd3_single_trap_light_14_rotation_z, 4, 3, 1, 1);

        label_single_trap_light_14_intensity = new QLabel(groupCheck_single_trap_light_14_enabled);
        label_single_trap_light_14_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_14_intensity"));

        gridLayout_single_trap_light_14->addWidget(label_single_trap_light_14_intensity, 5, 0, 1, 1);

        logedit_single_trap_light_14_intensity = new MyLineEdit(groupCheck_single_trap_light_14_enabled);
        logedit_single_trap_light_14_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_14_intensity"));

        gridLayout_single_trap_light_14->addWidget(logedit_single_trap_light_14_intensity, 5, 1, 1, 2);

        label_single_trap_light_14_color = new QLabel(groupCheck_single_trap_light_14_enabled);
        label_single_trap_light_14_color->setObjectName(QString::fromUtf8("label_single_trap_light_14_color"));

        gridLayout_single_trap_light_14->addWidget(label_single_trap_light_14_color, 6, 0, 1, 1);

        colorButton_single_trap_light_14_color = new MyColorButton(groupCheck_single_trap_light_14_enabled);
        colorButton_single_trap_light_14_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_14_color"));

        gridLayout_single_trap_light_14->addWidget(colorButton_single_trap_light_14_color, 6, 1, 1, 1);

        label_single_trap_light_14_gradient_color = new QLabel(groupCheck_single_trap_light_14_enabled);
        label_single_trap_light_14_gradient_color->setObjectName(QString::fromUtf8("label_single_trap_light_14_gradient_color"));

        gridLayout_single_trap_light_14->addWidget(label_single_trap_light_14_gradient_color, 6, 2, 1, 1);

        colorButton_single_trap_light_14_gradient_color = new MyColorButton(groupCheck_single_trap_light_14_enabled);
        colorButton_single_trap_light_14_gradient_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_14_gradient_color"));

        gridLayout_single_trap_light_14->addWidget(colorButton_single_trap_light_14_gradient_color, 6, 3, 1, 2);

        label_single_trap_light_14_visibility = new QLabel(groupCheck_single_trap_light_14_enabled);
        label_single_trap_light_14_visibility->setObjectName(QString::fromUtf8("label_single_trap_light_14_visibility"));

        gridLayout_single_trap_light_14->addWidget(label_single_trap_light_14_visibility, 7, 0, 1, 1);

        logedit_single_trap_light_14_visibility = new MyLineEdit(groupCheck_single_trap_light_14_enabled);
        logedit_single_trap_light_14_visibility->setObjectName(QString::fromUtf8("logedit_single_trap_light_14_visibility"));

        gridLayout_single_trap_light_14->addWidget(logedit_single_trap_light_14_visibility, 7, 1, 1, 2);

        label_single_trap_light_14_max_distance = new QLabel(groupCheck_single_trap_light_14_enabled);
        label_single_trap_light_14_max_distance->setObjectName(QString::fromUtf8("label_single_trap_light_14_max_distance"));

        gridLayout_single_trap_light_14->addWidget(label_single_trap_light_14_max_distance, 7, 3, 1, 1);

        logedit_single_trap_light_14_max_distance = new MyLineEdit(groupCheck_single_trap_light_14_enabled);
        logedit_single_trap_light_14_max_distance->setObjectName(QString::fromUtf8("logedit_single_trap_light_14_max_distance"));

        gridLayout_single_trap_light_14->addWidget(logedit_single_trap_light_14_max_distance, 7, 4, 1, 1);

        label_single_trap_light_14_sharpening = new QLabel(groupCheck_single_trap_light_14_enabled);
        label_single_trap_light_14_sharpening->setObjectName(QString::fromUtf8("label_single_trap_light_14_sharpening"));

        gridLayout_single_trap_light_14->addWidget(label_single_trap_light_14_sharpening, 8, 0, 1, 1);

        logedit_single_trap_light_14_sharpening = new MyLineEdit(groupCheck_single_trap_light_14_enabled);
        logedit_single_trap_light_14_sharpening->setObjectName(QString::fromUtf8("logedit_single_trap_light_14_sharpening"));

        gridLayout_single_trap_light_14->addWidget(logedit_single_trap_light_14_sharpening, 8, 1, 1, 2);

        label_single_trap_light_14_blur = new QLabel(groupCheck_single_trap_light_14_enabled);
        label_single_trap_light_14_blur->setObjectName(QString::fromUtf8("label_single_trap_light_14_blur"));

        gridLayout_single_trap_light_14->addWidget(label_single_trap_light_14_blur, 8, 3, 1, 1);

        logedit_single_trap_light_14_blur = new MyLineEdit(groupCheck_single_trap_light_14_enabled);
        logedit_single_trap_light_14_blur->setObjectName(QString::fromUtf8("logedit_single_trap_light_14_blur"));

        gridLayout_single_trap_light_14->addWidget(logedit_single_trap_light_14_blur, 8, 4, 1, 1);

        label_single_trap_light_14_solid_intensity = new QLabel(groupCheck_single_trap_light_14_enabled);
        label_single_trap_light_14_solid_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_14_solid_intensity"));

        gridLayout_single_trap_light_14->addWidget(label_single_trap_light_14_solid_intensity, 9, 0, 1, 1);

        logedit_single_trap_light_14_solid_intensity = new MyLineEdit(groupCheck_single_trap_light_14_enabled);
        logedit_single_trap_light_14_solid_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_14_solid_intensity"));

        gridLayout_single_trap_light_14->addWidget(logedit_single_trap_light_14_solid_intensity, 9, 1, 1, 2);

        label_single_trap_light_14_softness = new QLabel(groupCheck_single_trap_light_14_enabled);
        label_single_trap_light_14_softness->setObjectName(QString::fromUtf8("label_single_trap_light_14_softness"));

        gridLayout_single_trap_light_14->addWidget(label_single_trap_light_14_softness, 9, 3, 1, 1);

        logedit_single_trap_light_14_softness = new MyLineEdit(groupCheck_single_trap_light_14_enabled);
        logedit_single_trap_light_14_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_14_softness"));

        gridLayout_single_trap_light_14->addWidget(logedit_single_trap_light_14_softness, 9, 4, 1, 1);

        label_single_trap_light_14_relative_size = new QLabel(groupCheck_single_trap_light_14_enabled);
        label_single_trap_light_14_relative_size->setObjectName(QString::fromUtf8("label_single_trap_light_14_relative_size"));

        gridLayout_single_trap_light_14->addWidget(label_single_trap_light_14_relative_size, 10, 0, 1, 1);

        logedit_single_trap_light_14_relative_size = new MyLineEdit(groupCheck_single_trap_light_14_enabled);
        logedit_single_trap_light_14_relative_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_14_relative_size"));

        gridLayout_single_trap_light_14->addWidget(logedit_single_trap_light_14_relative_size, 10, 1, 1, 2);

        checkBox_single_trap_light_14_pre_transformed = new MyCheckBox(groupCheck_single_trap_light_14_enabled);
        checkBox_single_trap_light_14_pre_transformed->setObjectName(QString::fromUtf8("checkBox_single_trap_light_14_pre_transformed"));

        gridLayout_single_trap_light_14->addWidget(checkBox_single_trap_light_14_pre_transformed, 11, 0, 1, 1);

        label_single_trap_light_14_position_mode = new QLabel(groupCheck_single_trap_light_14_enabled);
        label_single_trap_light_14_position_mode->setObjectName(QString::fromUtf8("label_single_trap_light_14_position_mode"));

        gridLayout_single_trap_light_14->addWidget(label_single_trap_light_14_position_mode, 12, 0, 1, 1);

        comboBox_single_trap_light_14_position_mode = new MyComboBox(groupCheck_single_trap_light_14_enabled);
        comboBox_single_trap_light_14_position_mode->addItem(QString());
        comboBox_single_trap_light_14_position_mode->addItem(QString());
        comboBox_single_trap_light_14_position_mode->addItem(QString());
        comboBox_single_trap_light_14_position_mode->addItem(QString());
        comboBox_single_trap_light_14_position_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_14_position_mode"));

        gridLayout_single_trap_light_14->addWidget(comboBox_single_trap_light_14_position_mode, 12, 1, 1, 2);

        label_single_trap_light_14_coloring_mode = new QLabel(groupCheck_single_trap_light_14_enabled);
        label_single_trap_light_14_coloring_mode->setObjectName(QString::fromUtf8("label_single_trap_light_14_coloring_mode"));

        gridLayout_single_trap_light_14->addWidget(label_single_trap_light_14_coloring_mode, 13, 0, 1, 1);

        comboBox_single_trap_light_14_coloring_mode = new MyComboBox(groupCheck_single_trap_light_14_enabled);
        comboBox_single_trap_light_14_coloring_mode->addItem(QString());
        comboBox_single_trap_light_14_coloring_mode->addItem(QString());
        comboBox_single_trap_light_14_coloring_mode->addItem(QString());
        comboBox_single_trap_light_14_coloring_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_14_coloring_mode"));

        gridLayout_single_trap_light_14->addWidget(comboBox_single_trap_light_14_coloring_mode, 13, 1, 1, 2);

        label_single_trap_light_14_falloff_type = new QLabel(groupCheck_single_trap_light_14_enabled);
        label_single_trap_light_14_falloff_type->setObjectName(QString::fromUtf8("label_single_trap_light_14_falloff_type"));

        gridLayout_single_trap_light_14->addWidget(label_single_trap_light_14_falloff_type, 14, 0, 1, 1);

        comboBox_single_trap_light_14_falloff_type = new MyComboBox(groupCheck_single_trap_light_14_enabled);
        comboBox_single_trap_light_14_falloff_type->addItem(QString());
        comboBox_single_trap_light_14_falloff_type->addItem(QString());
        comboBox_single_trap_light_14_falloff_type->addItem(QString());
        comboBox_single_trap_light_14_falloff_type->addItem(QString());
        comboBox_single_trap_light_14_falloff_type->addItem(QString());
        comboBox_single_trap_light_14_falloff_type->setObjectName(QString::fromUtf8("comboBox_single_trap_light_14_falloff_type"));

        gridLayout_single_trap_light_14->addWidget(comboBox_single_trap_light_14_falloff_type, 14, 1, 1, 2);

        label_single_trap_light_14_edge_softness = new QLabel(groupCheck_single_trap_light_14_enabled);
        label_single_trap_light_14_edge_softness->setObjectName(QString::fromUtf8("label_single_trap_light_14_edge_softness"));

        gridLayout_single_trap_light_14->addWidget(label_single_trap_light_14_edge_softness, 15, 0, 1, 1);

        logedit_single_trap_light_14_edge_softness = new MyLineEdit(groupCheck_single_trap_light_14_enabled);
        logedit_single_trap_light_14_edge_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_14_edge_softness"));

        gridLayout_single_trap_light_14->addWidget(logedit_single_trap_light_14_edge_softness, 15, 1, 1, 2);

        label_single_trap_light_14_anim_orbit_radius = new QLabel(groupCheck_single_trap_light_14_enabled);
        label_single_trap_light_14_anim_orbit_radius->setObjectName(QString::fromUtf8("label_single_trap_light_14_anim_orbit_radius"));

        gridLayout_single_trap_light_14->addWidget(label_single_trap_light_14_anim_orbit_radius, 16, 0, 1, 1);

        logedit_single_trap_light_14_anim_orbit_radius = new MyLineEdit(groupCheck_single_trap_light_14_enabled);
        logedit_single_trap_light_14_anim_orbit_radius->setObjectName(QString::fromUtf8("logedit_single_trap_light_14_anim_orbit_radius"));

        gridLayout_single_trap_light_14->addWidget(logedit_single_trap_light_14_anim_orbit_radius, 16, 1, 1, 1);

        logedit_single_trap_light_14_anim_orbit_speed = new MyLineEdit(groupCheck_single_trap_light_14_enabled);
        logedit_single_trap_light_14_anim_orbit_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_14_anim_orbit_speed"));

        gridLayout_single_trap_light_14->addWidget(logedit_single_trap_light_14_anim_orbit_speed, 16, 2, 1, 1);

        logedit_single_trap_light_14_anim_pulsate_speed = new MyLineEdit(groupCheck_single_trap_light_14_enabled);
        logedit_single_trap_light_14_anim_pulsate_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_14_anim_pulsate_speed"));

        gridLayout_single_trap_light_14->addWidget(logedit_single_trap_light_14_anim_pulsate_speed, 16, 3, 1, 1);

        logedit_single_trap_light_14_anim_pulsate_amount = new MyLineEdit(groupCheck_single_trap_light_14_enabled);
        logedit_single_trap_light_14_anim_pulsate_amount->setObjectName(QString::fromUtf8("logedit_single_trap_light_14_anim_pulsate_amount"));

        gridLayout_single_trap_light_14->addWidget(logedit_single_trap_light_14_anim_pulsate_amount, 16, 4, 1, 1);

        pushButton_single_trap_light_14_place_surface = new QPushButton(groupCheck_single_trap_light_14_enabled);
        pushButton_single_trap_light_14_place_surface->setObjectName(QString::fromUtf8("pushButton_single_trap_light_14_place_surface"));

        gridLayout_single_trap_light_14->addWidget(pushButton_single_trap_light_14_place_surface, 17, 0, 1, 5);

        pushButton_single_trap_light_14_place_target = new QPushButton(groupCheck_single_trap_light_14_enabled);
        pushButton_single_trap_light_14_place_target->setObjectName(QString::fromUtf8("pushButton_single_trap_light_14_place_target"));

        gridLayout_single_trap_light_14->addWidget(pushButton_single_trap_light_14_place_target, 18, 0, 1, 5);


        verticalLayout_single_trap_layers->addWidget(groupCheck_single_trap_light_14_enabled);

        groupCheck_single_trap_light_15_enabled = new MyGroupBox(scrollAreaWidgetContents_single_trap);
        groupCheck_single_trap_light_15_enabled->setObjectName(QString::fromUtf8("groupCheck_single_trap_light_15_enabled"));
        groupCheck_single_trap_light_15_enabled->setCheckable(true);
        gridLayout_single_trap_light_15 = new QGridLayout(groupCheck_single_trap_light_15_enabled);
        gridLayout_single_trap_light_15->setSpacing(2);
        gridLayout_single_trap_light_15->setObjectName(QString::fromUtf8("gridLayout_single_trap_light_15"));
        label_single_trap_light_15_shape = new QLabel(groupCheck_single_trap_light_15_enabled);
        label_single_trap_light_15_shape->setObjectName(QString::fromUtf8("label_single_trap_light_15_shape"));

        gridLayout_single_trap_light_15->addWidget(label_single_trap_light_15_shape, 0, 0, 1, 1);

        comboBox_single_trap_light_15_shape = new MyComboBox(groupCheck_single_trap_light_15_enabled);
        comboBox_single_trap_light_15_shape->addItem(QString());
        comboBox_single_trap_light_15_shape->addItem(QString());
        comboBox_single_trap_light_15_shape->addItem(QString());
        comboBox_single_trap_light_15_shape->addItem(QString());
        comboBox_single_trap_light_15_shape->addItem(QString());
        comboBox_single_trap_light_15_shape->addItem(QString());
        comboBox_single_trap_light_15_shape->addItem(QString());
        comboBox_single_trap_light_15_shape->addItem(QString());
        comboBox_single_trap_light_15_shape->addItem(QString());
        comboBox_single_trap_light_15_shape->addItem(QString());
        comboBox_single_trap_light_15_shape->addItem(QString());
        comboBox_single_trap_light_15_shape->addItem(QString());
        comboBox_single_trap_light_15_shape->addItem(QString());
        comboBox_single_trap_light_15_shape->addItem(QString());
        comboBox_single_trap_light_15_shape->setObjectName(QString::fromUtf8("comboBox_single_trap_light_15_shape"));

        gridLayout_single_trap_light_15->addWidget(comboBox_single_trap_light_15_shape, 0, 1, 1, 2);

        label_single_trap_light_15_position = new QLabel(groupCheck_single_trap_light_15_enabled);
        label_single_trap_light_15_position->setObjectName(QString::fromUtf8("label_single_trap_light_15_position"));

        gridLayout_single_trap_light_15->addWidget(label_single_trap_light_15_position, 1, 0, 1, 1);

        vect3_single_trap_light_15_position_x = new MyLineEdit(groupCheck_single_trap_light_15_enabled);
        vect3_single_trap_light_15_position_x->setObjectName(QString::fromUtf8("vect3_single_trap_light_15_position_x"));

        gridLayout_single_trap_light_15->addWidget(vect3_single_trap_light_15_position_x, 1, 1, 1, 1);

        vect3_single_trap_light_15_position_y = new MyLineEdit(groupCheck_single_trap_light_15_enabled);
        vect3_single_trap_light_15_position_y->setObjectName(QString::fromUtf8("vect3_single_trap_light_15_position_y"));

        gridLayout_single_trap_light_15->addWidget(vect3_single_trap_light_15_position_y, 1, 2, 1, 1);

        vect3_single_trap_light_15_position_z = new MyLineEdit(groupCheck_single_trap_light_15_enabled);
        vect3_single_trap_light_15_position_z->setObjectName(QString::fromUtf8("vect3_single_trap_light_15_position_z"));

        gridLayout_single_trap_light_15->addWidget(vect3_single_trap_light_15_position_z, 1, 3, 1, 1);

        pushButton_single_trap_light_15_place_camera = new QPushButton(groupCheck_single_trap_light_15_enabled);
        pushButton_single_trap_light_15_place_camera->setObjectName(QString::fromUtf8("pushButton_single_trap_light_15_place_camera"));

        gridLayout_single_trap_light_15->addWidget(pushButton_single_trap_light_15_place_camera, 1, 4, 1, 1);

        label_single_trap_light_15_size = new QLabel(groupCheck_single_trap_light_15_enabled);
        label_single_trap_light_15_size->setObjectName(QString::fromUtf8("label_single_trap_light_15_size"));

        gridLayout_single_trap_light_15->addWidget(label_single_trap_light_15_size, 2, 0, 1, 1);

        logedit_single_trap_light_15_size = new MyLineEdit(groupCheck_single_trap_light_15_enabled);
        logedit_single_trap_light_15_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_15_size"));

        gridLayout_single_trap_light_15->addWidget(logedit_single_trap_light_15_size, 2, 1, 1, 2);

        label_single_trap_light_15_size2 = new QLabel(groupCheck_single_trap_light_15_enabled);
        label_single_trap_light_15_size2->setObjectName(QString::fromUtf8("label_single_trap_light_15_size2"));

        gridLayout_single_trap_light_15->addWidget(label_single_trap_light_15_size2, 2, 3, 1, 1);

        logedit_single_trap_light_15_size2 = new MyLineEdit(groupCheck_single_trap_light_15_enabled);
        logedit_single_trap_light_15_size2->setObjectName(QString::fromUtf8("logedit_single_trap_light_15_size2"));

        gridLayout_single_trap_light_15->addWidget(logedit_single_trap_light_15_size2, 2, 4, 1, 1);

        label_single_trap_light_15_thickness = new QLabel(groupCheck_single_trap_light_15_enabled);
        label_single_trap_light_15_thickness->setObjectName(QString::fromUtf8("label_single_trap_light_15_thickness"));

        gridLayout_single_trap_light_15->addWidget(label_single_trap_light_15_thickness, 3, 0, 1, 1);

        logedit_single_trap_light_15_thickness = new MyLineEdit(groupCheck_single_trap_light_15_enabled);
        logedit_single_trap_light_15_thickness->setObjectName(QString::fromUtf8("logedit_single_trap_light_15_thickness"));

        gridLayout_single_trap_light_15->addWidget(logedit_single_trap_light_15_thickness, 3, 1, 1, 2);

        label_single_trap_light_15_rotation = new QLabel(groupCheck_single_trap_light_15_enabled);
        label_single_trap_light_15_rotation->setObjectName(QString::fromUtf8("label_single_trap_light_15_rotation"));

        gridLayout_single_trap_light_15->addWidget(label_single_trap_light_15_rotation, 4, 0, 1, 1);

        spinboxd3_single_trap_light_15_rotation_x = new MyDoubleSpinBox(groupCheck_single_trap_light_15_enabled);
        spinboxd3_single_trap_light_15_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_15_rotation_x"));

        gridLayout_single_trap_light_15->addWidget(spinboxd3_single_trap_light_15_rotation_x, 4, 1, 1, 1);

        spinboxd3_single_trap_light_15_rotation_y = new MyDoubleSpinBox(groupCheck_single_trap_light_15_enabled);
        spinboxd3_single_trap_light_15_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_15_rotation_y"));

        gridLayout_single_trap_light_15->addWidget(spinboxd3_single_trap_light_15_rotation_y, 4, 2, 1, 1);

        spinboxd3_single_trap_light_15_rotation_z = new MyDoubleSpinBox(groupCheck_single_trap_light_15_enabled);
        spinboxd3_single_trap_light_15_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_15_rotation_z"));

        gridLayout_single_trap_light_15->addWidget(spinboxd3_single_trap_light_15_rotation_z, 4, 3, 1, 1);

        label_single_trap_light_15_intensity = new QLabel(groupCheck_single_trap_light_15_enabled);
        label_single_trap_light_15_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_15_intensity"));

        gridLayout_single_trap_light_15->addWidget(label_single_trap_light_15_intensity, 5, 0, 1, 1);

        logedit_single_trap_light_15_intensity = new MyLineEdit(groupCheck_single_trap_light_15_enabled);
        logedit_single_trap_light_15_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_15_intensity"));

        gridLayout_single_trap_light_15->addWidget(logedit_single_trap_light_15_intensity, 5, 1, 1, 2);

        label_single_trap_light_15_color = new QLabel(groupCheck_single_trap_light_15_enabled);
        label_single_trap_light_15_color->setObjectName(QString::fromUtf8("label_single_trap_light_15_color"));

        gridLayout_single_trap_light_15->addWidget(label_single_trap_light_15_color, 6, 0, 1, 1);

        colorButton_single_trap_light_15_color = new MyColorButton(groupCheck_single_trap_light_15_enabled);
        colorButton_single_trap_light_15_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_15_color"));

        gridLayout_single_trap_light_15->addWidget(colorButton_single_trap_light_15_color, 6, 1, 1, 1);

        label_single_trap_light_15_gradient_color = new QLabel(groupCheck_single_trap_light_15_enabled);
        label_single_trap_light_15_gradient_color->setObjectName(QString::fromUtf8("label_single_trap_light_15_gradient_color"));

        gridLayout_single_trap_light_15->addWidget(label_single_trap_light_15_gradient_color, 6, 2, 1, 1);

        colorButton_single_trap_light_15_gradient_color = new MyColorButton(groupCheck_single_trap_light_15_enabled);
        colorButton_single_trap_light_15_gradient_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_15_gradient_color"));

        gridLayout_single_trap_light_15->addWidget(colorButton_single_trap_light_15_gradient_color, 6, 3, 1, 2);

        label_single_trap_light_15_visibility = new QLabel(groupCheck_single_trap_light_15_enabled);
        label_single_trap_light_15_visibility->setObjectName(QString::fromUtf8("label_single_trap_light_15_visibility"));

        gridLayout_single_trap_light_15->addWidget(label_single_trap_light_15_visibility, 7, 0, 1, 1);

        logedit_single_trap_light_15_visibility = new MyLineEdit(groupCheck_single_trap_light_15_enabled);
        logedit_single_trap_light_15_visibility->setObjectName(QString::fromUtf8("logedit_single_trap_light_15_visibility"));

        gridLayout_single_trap_light_15->addWidget(logedit_single_trap_light_15_visibility, 7, 1, 1, 2);

        label_single_trap_light_15_max_distance = new QLabel(groupCheck_single_trap_light_15_enabled);
        label_single_trap_light_15_max_distance->setObjectName(QString::fromUtf8("label_single_trap_light_15_max_distance"));

        gridLayout_single_trap_light_15->addWidget(label_single_trap_light_15_max_distance, 7, 3, 1, 1);

        logedit_single_trap_light_15_max_distance = new MyLineEdit(groupCheck_single_trap_light_15_enabled);
        logedit_single_trap_light_15_max_distance->setObjectName(QString::fromUtf8("logedit_single_trap_light_15_max_distance"));

        gridLayout_single_trap_light_15->addWidget(logedit_single_trap_light_15_max_distance, 7, 4, 1, 1);

        label_single_trap_light_15_sharpening = new QLabel(groupCheck_single_trap_light_15_enabled);
        label_single_trap_light_15_sharpening->setObjectName(QString::fromUtf8("label_single_trap_light_15_sharpening"));

        gridLayout_single_trap_light_15->addWidget(label_single_trap_light_15_sharpening, 8, 0, 1, 1);

        logedit_single_trap_light_15_sharpening = new MyLineEdit(groupCheck_single_trap_light_15_enabled);
        logedit_single_trap_light_15_sharpening->setObjectName(QString::fromUtf8("logedit_single_trap_light_15_sharpening"));

        gridLayout_single_trap_light_15->addWidget(logedit_single_trap_light_15_sharpening, 8, 1, 1, 2);

        label_single_trap_light_15_blur = new QLabel(groupCheck_single_trap_light_15_enabled);
        label_single_trap_light_15_blur->setObjectName(QString::fromUtf8("label_single_trap_light_15_blur"));

        gridLayout_single_trap_light_15->addWidget(label_single_trap_light_15_blur, 8, 3, 1, 1);

        logedit_single_trap_light_15_blur = new MyLineEdit(groupCheck_single_trap_light_15_enabled);
        logedit_single_trap_light_15_blur->setObjectName(QString::fromUtf8("logedit_single_trap_light_15_blur"));

        gridLayout_single_trap_light_15->addWidget(logedit_single_trap_light_15_blur, 8, 4, 1, 1);

        label_single_trap_light_15_solid_intensity = new QLabel(groupCheck_single_trap_light_15_enabled);
        label_single_trap_light_15_solid_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_15_solid_intensity"));

        gridLayout_single_trap_light_15->addWidget(label_single_trap_light_15_solid_intensity, 9, 0, 1, 1);

        logedit_single_trap_light_15_solid_intensity = new MyLineEdit(groupCheck_single_trap_light_15_enabled);
        logedit_single_trap_light_15_solid_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_15_solid_intensity"));

        gridLayout_single_trap_light_15->addWidget(logedit_single_trap_light_15_solid_intensity, 9, 1, 1, 2);

        label_single_trap_light_15_softness = new QLabel(groupCheck_single_trap_light_15_enabled);
        label_single_trap_light_15_softness->setObjectName(QString::fromUtf8("label_single_trap_light_15_softness"));

        gridLayout_single_trap_light_15->addWidget(label_single_trap_light_15_softness, 9, 3, 1, 1);

        logedit_single_trap_light_15_softness = new MyLineEdit(groupCheck_single_trap_light_15_enabled);
        logedit_single_trap_light_15_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_15_softness"));

        gridLayout_single_trap_light_15->addWidget(logedit_single_trap_light_15_softness, 9, 4, 1, 1);

        label_single_trap_light_15_relative_size = new QLabel(groupCheck_single_trap_light_15_enabled);
        label_single_trap_light_15_relative_size->setObjectName(QString::fromUtf8("label_single_trap_light_15_relative_size"));

        gridLayout_single_trap_light_15->addWidget(label_single_trap_light_15_relative_size, 10, 0, 1, 1);

        logedit_single_trap_light_15_relative_size = new MyLineEdit(groupCheck_single_trap_light_15_enabled);
        logedit_single_trap_light_15_relative_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_15_relative_size"));

        gridLayout_single_trap_light_15->addWidget(logedit_single_trap_light_15_relative_size, 10, 1, 1, 2);

        checkBox_single_trap_light_15_pre_transformed = new MyCheckBox(groupCheck_single_trap_light_15_enabled);
        checkBox_single_trap_light_15_pre_transformed->setObjectName(QString::fromUtf8("checkBox_single_trap_light_15_pre_transformed"));

        gridLayout_single_trap_light_15->addWidget(checkBox_single_trap_light_15_pre_transformed, 11, 0, 1, 1);

        label_single_trap_light_15_position_mode = new QLabel(groupCheck_single_trap_light_15_enabled);
        label_single_trap_light_15_position_mode->setObjectName(QString::fromUtf8("label_single_trap_light_15_position_mode"));

        gridLayout_single_trap_light_15->addWidget(label_single_trap_light_15_position_mode, 12, 0, 1, 1);

        comboBox_single_trap_light_15_position_mode = new MyComboBox(groupCheck_single_trap_light_15_enabled);
        comboBox_single_trap_light_15_position_mode->addItem(QString());
        comboBox_single_trap_light_15_position_mode->addItem(QString());
        comboBox_single_trap_light_15_position_mode->addItem(QString());
        comboBox_single_trap_light_15_position_mode->addItem(QString());
        comboBox_single_trap_light_15_position_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_15_position_mode"));

        gridLayout_single_trap_light_15->addWidget(comboBox_single_trap_light_15_position_mode, 12, 1, 1, 2);

        label_single_trap_light_15_coloring_mode = new QLabel(groupCheck_single_trap_light_15_enabled);
        label_single_trap_light_15_coloring_mode->setObjectName(QString::fromUtf8("label_single_trap_light_15_coloring_mode"));

        gridLayout_single_trap_light_15->addWidget(label_single_trap_light_15_coloring_mode, 13, 0, 1, 1);

        comboBox_single_trap_light_15_coloring_mode = new MyComboBox(groupCheck_single_trap_light_15_enabled);
        comboBox_single_trap_light_15_coloring_mode->addItem(QString());
        comboBox_single_trap_light_15_coloring_mode->addItem(QString());
        comboBox_single_trap_light_15_coloring_mode->addItem(QString());
        comboBox_single_trap_light_15_coloring_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_15_coloring_mode"));

        gridLayout_single_trap_light_15->addWidget(comboBox_single_trap_light_15_coloring_mode, 13, 1, 1, 2);

        label_single_trap_light_15_falloff_type = new QLabel(groupCheck_single_trap_light_15_enabled);
        label_single_trap_light_15_falloff_type->setObjectName(QString::fromUtf8("label_single_trap_light_15_falloff_type"));

        gridLayout_single_trap_light_15->addWidget(label_single_trap_light_15_falloff_type, 14, 0, 1, 1);

        comboBox_single_trap_light_15_falloff_type = new MyComboBox(groupCheck_single_trap_light_15_enabled);
        comboBox_single_trap_light_15_falloff_type->addItem(QString());
        comboBox_single_trap_light_15_falloff_type->addItem(QString());
        comboBox_single_trap_light_15_falloff_type->addItem(QString());
        comboBox_single_trap_light_15_falloff_type->addItem(QString());
        comboBox_single_trap_light_15_falloff_type->addItem(QString());
        comboBox_single_trap_light_15_falloff_type->setObjectName(QString::fromUtf8("comboBox_single_trap_light_15_falloff_type"));

        gridLayout_single_trap_light_15->addWidget(comboBox_single_trap_light_15_falloff_type, 14, 1, 1, 2);

        label_single_trap_light_15_edge_softness = new QLabel(groupCheck_single_trap_light_15_enabled);
        label_single_trap_light_15_edge_softness->setObjectName(QString::fromUtf8("label_single_trap_light_15_edge_softness"));

        gridLayout_single_trap_light_15->addWidget(label_single_trap_light_15_edge_softness, 15, 0, 1, 1);

        logedit_single_trap_light_15_edge_softness = new MyLineEdit(groupCheck_single_trap_light_15_enabled);
        logedit_single_trap_light_15_edge_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_15_edge_softness"));

        gridLayout_single_trap_light_15->addWidget(logedit_single_trap_light_15_edge_softness, 15, 1, 1, 2);

        label_single_trap_light_15_anim_orbit_radius = new QLabel(groupCheck_single_trap_light_15_enabled);
        label_single_trap_light_15_anim_orbit_radius->setObjectName(QString::fromUtf8("label_single_trap_light_15_anim_orbit_radius"));

        gridLayout_single_trap_light_15->addWidget(label_single_trap_light_15_anim_orbit_radius, 16, 0, 1, 1);

        logedit_single_trap_light_15_anim_orbit_radius = new MyLineEdit(groupCheck_single_trap_light_15_enabled);
        logedit_single_trap_light_15_anim_orbit_radius->setObjectName(QString::fromUtf8("logedit_single_trap_light_15_anim_orbit_radius"));

        gridLayout_single_trap_light_15->addWidget(logedit_single_trap_light_15_anim_orbit_radius, 16, 1, 1, 1);

        logedit_single_trap_light_15_anim_orbit_speed = new MyLineEdit(groupCheck_single_trap_light_15_enabled);
        logedit_single_trap_light_15_anim_orbit_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_15_anim_orbit_speed"));

        gridLayout_single_trap_light_15->addWidget(logedit_single_trap_light_15_anim_orbit_speed, 16, 2, 1, 1);

        logedit_single_trap_light_15_anim_pulsate_speed = new MyLineEdit(groupCheck_single_trap_light_15_enabled);
        logedit_single_trap_light_15_anim_pulsate_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_15_anim_pulsate_speed"));

        gridLayout_single_trap_light_15->addWidget(logedit_single_trap_light_15_anim_pulsate_speed, 16, 3, 1, 1);

        logedit_single_trap_light_15_anim_pulsate_amount = new MyLineEdit(groupCheck_single_trap_light_15_enabled);
        logedit_single_trap_light_15_anim_pulsate_amount->setObjectName(QString::fromUtf8("logedit_single_trap_light_15_anim_pulsate_amount"));

        gridLayout_single_trap_light_15->addWidget(logedit_single_trap_light_15_anim_pulsate_amount, 16, 4, 1, 1);

        pushButton_single_trap_light_15_place_surface = new QPushButton(groupCheck_single_trap_light_15_enabled);
        pushButton_single_trap_light_15_place_surface->setObjectName(QString::fromUtf8("pushButton_single_trap_light_15_place_surface"));

        gridLayout_single_trap_light_15->addWidget(pushButton_single_trap_light_15_place_surface, 17, 0, 1, 5);

        pushButton_single_trap_light_15_place_target = new QPushButton(groupCheck_single_trap_light_15_enabled);
        pushButton_single_trap_light_15_place_target->setObjectName(QString::fromUtf8("pushButton_single_trap_light_15_place_target"));

        gridLayout_single_trap_light_15->addWidget(pushButton_single_trap_light_15_place_target, 18, 0, 1, 5);


        verticalLayout_single_trap_layers->addWidget(groupCheck_single_trap_light_15_enabled);

        groupCheck_single_trap_light_16_enabled = new MyGroupBox(scrollAreaWidgetContents_single_trap);
        groupCheck_single_trap_light_16_enabled->setObjectName(QString::fromUtf8("groupCheck_single_trap_light_16_enabled"));
        groupCheck_single_trap_light_16_enabled->setCheckable(true);
        gridLayout_single_trap_light_16 = new QGridLayout(groupCheck_single_trap_light_16_enabled);
        gridLayout_single_trap_light_16->setSpacing(2);
        gridLayout_single_trap_light_16->setObjectName(QString::fromUtf8("gridLayout_single_trap_light_16"));
        label_single_trap_light_16_shape = new QLabel(groupCheck_single_trap_light_16_enabled);
        label_single_trap_light_16_shape->setObjectName(QString::fromUtf8("label_single_trap_light_16_shape"));

        gridLayout_single_trap_light_16->addWidget(label_single_trap_light_16_shape, 0, 0, 1, 1);

        comboBox_single_trap_light_16_shape = new MyComboBox(groupCheck_single_trap_light_16_enabled);
        comboBox_single_trap_light_16_shape->addItem(QString());
        comboBox_single_trap_light_16_shape->addItem(QString());
        comboBox_single_trap_light_16_shape->addItem(QString());
        comboBox_single_trap_light_16_shape->addItem(QString());
        comboBox_single_trap_light_16_shape->addItem(QString());
        comboBox_single_trap_light_16_shape->addItem(QString());
        comboBox_single_trap_light_16_shape->addItem(QString());
        comboBox_single_trap_light_16_shape->addItem(QString());
        comboBox_single_trap_light_16_shape->addItem(QString());
        comboBox_single_trap_light_16_shape->addItem(QString());
        comboBox_single_trap_light_16_shape->addItem(QString());
        comboBox_single_trap_light_16_shape->addItem(QString());
        comboBox_single_trap_light_16_shape->addItem(QString());
        comboBox_single_trap_light_16_shape->addItem(QString());
        comboBox_single_trap_light_16_shape->setObjectName(QString::fromUtf8("comboBox_single_trap_light_16_shape"));

        gridLayout_single_trap_light_16->addWidget(comboBox_single_trap_light_16_shape, 0, 1, 1, 2);

        label_single_trap_light_16_position = new QLabel(groupCheck_single_trap_light_16_enabled);
        label_single_trap_light_16_position->setObjectName(QString::fromUtf8("label_single_trap_light_16_position"));

        gridLayout_single_trap_light_16->addWidget(label_single_trap_light_16_position, 1, 0, 1, 1);

        vect3_single_trap_light_16_position_x = new MyLineEdit(groupCheck_single_trap_light_16_enabled);
        vect3_single_trap_light_16_position_x->setObjectName(QString::fromUtf8("vect3_single_trap_light_16_position_x"));

        gridLayout_single_trap_light_16->addWidget(vect3_single_trap_light_16_position_x, 1, 1, 1, 1);

        vect3_single_trap_light_16_position_y = new MyLineEdit(groupCheck_single_trap_light_16_enabled);
        vect3_single_trap_light_16_position_y->setObjectName(QString::fromUtf8("vect3_single_trap_light_16_position_y"));

        gridLayout_single_trap_light_16->addWidget(vect3_single_trap_light_16_position_y, 1, 2, 1, 1);

        vect3_single_trap_light_16_position_z = new MyLineEdit(groupCheck_single_trap_light_16_enabled);
        vect3_single_trap_light_16_position_z->setObjectName(QString::fromUtf8("vect3_single_trap_light_16_position_z"));

        gridLayout_single_trap_light_16->addWidget(vect3_single_trap_light_16_position_z, 1, 3, 1, 1);

        pushButton_single_trap_light_16_place_camera = new QPushButton(groupCheck_single_trap_light_16_enabled);
        pushButton_single_trap_light_16_place_camera->setObjectName(QString::fromUtf8("pushButton_single_trap_light_16_place_camera"));

        gridLayout_single_trap_light_16->addWidget(pushButton_single_trap_light_16_place_camera, 1, 4, 1, 1);

        label_single_trap_light_16_size = new QLabel(groupCheck_single_trap_light_16_enabled);
        label_single_trap_light_16_size->setObjectName(QString::fromUtf8("label_single_trap_light_16_size"));

        gridLayout_single_trap_light_16->addWidget(label_single_trap_light_16_size, 2, 0, 1, 1);

        logedit_single_trap_light_16_size = new MyLineEdit(groupCheck_single_trap_light_16_enabled);
        logedit_single_trap_light_16_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_16_size"));

        gridLayout_single_trap_light_16->addWidget(logedit_single_trap_light_16_size, 2, 1, 1, 2);

        label_single_trap_light_16_size2 = new QLabel(groupCheck_single_trap_light_16_enabled);
        label_single_trap_light_16_size2->setObjectName(QString::fromUtf8("label_single_trap_light_16_size2"));

        gridLayout_single_trap_light_16->addWidget(label_single_trap_light_16_size2, 2, 3, 1, 1);

        logedit_single_trap_light_16_size2 = new MyLineEdit(groupCheck_single_trap_light_16_enabled);
        logedit_single_trap_light_16_size2->setObjectName(QString::fromUtf8("logedit_single_trap_light_16_size2"));

        gridLayout_single_trap_light_16->addWidget(logedit_single_trap_light_16_size2, 2, 4, 1, 1);

        label_single_trap_light_16_thickness = new QLabel(groupCheck_single_trap_light_16_enabled);
        label_single_trap_light_16_thickness->setObjectName(QString::fromUtf8("label_single_trap_light_16_thickness"));

        gridLayout_single_trap_light_16->addWidget(label_single_trap_light_16_thickness, 3, 0, 1, 1);

        logedit_single_trap_light_16_thickness = new MyLineEdit(groupCheck_single_trap_light_16_enabled);
        logedit_single_trap_light_16_thickness->setObjectName(QString::fromUtf8("logedit_single_trap_light_16_thickness"));

        gridLayout_single_trap_light_16->addWidget(logedit_single_trap_light_16_thickness, 3, 1, 1, 2);

        label_single_trap_light_16_rotation = new QLabel(groupCheck_single_trap_light_16_enabled);
        label_single_trap_light_16_rotation->setObjectName(QString::fromUtf8("label_single_trap_light_16_rotation"));

        gridLayout_single_trap_light_16->addWidget(label_single_trap_light_16_rotation, 4, 0, 1, 1);

        spinboxd3_single_trap_light_16_rotation_x = new MyDoubleSpinBox(groupCheck_single_trap_light_16_enabled);
        spinboxd3_single_trap_light_16_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_16_rotation_x"));

        gridLayout_single_trap_light_16->addWidget(spinboxd3_single_trap_light_16_rotation_x, 4, 1, 1, 1);

        spinboxd3_single_trap_light_16_rotation_y = new MyDoubleSpinBox(groupCheck_single_trap_light_16_enabled);
        spinboxd3_single_trap_light_16_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_16_rotation_y"));

        gridLayout_single_trap_light_16->addWidget(spinboxd3_single_trap_light_16_rotation_y, 4, 2, 1, 1);

        spinboxd3_single_trap_light_16_rotation_z = new MyDoubleSpinBox(groupCheck_single_trap_light_16_enabled);
        spinboxd3_single_trap_light_16_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_16_rotation_z"));

        gridLayout_single_trap_light_16->addWidget(spinboxd3_single_trap_light_16_rotation_z, 4, 3, 1, 1);

        label_single_trap_light_16_intensity = new QLabel(groupCheck_single_trap_light_16_enabled);
        label_single_trap_light_16_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_16_intensity"));

        gridLayout_single_trap_light_16->addWidget(label_single_trap_light_16_intensity, 5, 0, 1, 1);

        logedit_single_trap_light_16_intensity = new MyLineEdit(groupCheck_single_trap_light_16_enabled);
        logedit_single_trap_light_16_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_16_intensity"));

        gridLayout_single_trap_light_16->addWidget(logedit_single_trap_light_16_intensity, 5, 1, 1, 2);

        label_single_trap_light_16_color = new QLabel(groupCheck_single_trap_light_16_enabled);
        label_single_trap_light_16_color->setObjectName(QString::fromUtf8("label_single_trap_light_16_color"));

        gridLayout_single_trap_light_16->addWidget(label_single_trap_light_16_color, 6, 0, 1, 1);

        colorButton_single_trap_light_16_color = new MyColorButton(groupCheck_single_trap_light_16_enabled);
        colorButton_single_trap_light_16_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_16_color"));

        gridLayout_single_trap_light_16->addWidget(colorButton_single_trap_light_16_color, 6, 1, 1, 1);

        label_single_trap_light_16_gradient_color = new QLabel(groupCheck_single_trap_light_16_enabled);
        label_single_trap_light_16_gradient_color->setObjectName(QString::fromUtf8("label_single_trap_light_16_gradient_color"));

        gridLayout_single_trap_light_16->addWidget(label_single_trap_light_16_gradient_color, 6, 2, 1, 1);

        colorButton_single_trap_light_16_gradient_color = new MyColorButton(groupCheck_single_trap_light_16_enabled);
        colorButton_single_trap_light_16_gradient_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_16_gradient_color"));

        gridLayout_single_trap_light_16->addWidget(colorButton_single_trap_light_16_gradient_color, 6, 3, 1, 2);

        label_single_trap_light_16_visibility = new QLabel(groupCheck_single_trap_light_16_enabled);
        label_single_trap_light_16_visibility->setObjectName(QString::fromUtf8("label_single_trap_light_16_visibility"));

        gridLayout_single_trap_light_16->addWidget(label_single_trap_light_16_visibility, 7, 0, 1, 1);

        logedit_single_trap_light_16_visibility = new MyLineEdit(groupCheck_single_trap_light_16_enabled);
        logedit_single_trap_light_16_visibility->setObjectName(QString::fromUtf8("logedit_single_trap_light_16_visibility"));

        gridLayout_single_trap_light_16->addWidget(logedit_single_trap_light_16_visibility, 7, 1, 1, 2);

        label_single_trap_light_16_max_distance = new QLabel(groupCheck_single_trap_light_16_enabled);
        label_single_trap_light_16_max_distance->setObjectName(QString::fromUtf8("label_single_trap_light_16_max_distance"));

        gridLayout_single_trap_light_16->addWidget(label_single_trap_light_16_max_distance, 7, 3, 1, 1);

        logedit_single_trap_light_16_max_distance = new MyLineEdit(groupCheck_single_trap_light_16_enabled);
        logedit_single_trap_light_16_max_distance->setObjectName(QString::fromUtf8("logedit_single_trap_light_16_max_distance"));

        gridLayout_single_trap_light_16->addWidget(logedit_single_trap_light_16_max_distance, 7, 4, 1, 1);

        label_single_trap_light_16_sharpening = new QLabel(groupCheck_single_trap_light_16_enabled);
        label_single_trap_light_16_sharpening->setObjectName(QString::fromUtf8("label_single_trap_light_16_sharpening"));

        gridLayout_single_trap_light_16->addWidget(label_single_trap_light_16_sharpening, 8, 0, 1, 1);

        logedit_single_trap_light_16_sharpening = new MyLineEdit(groupCheck_single_trap_light_16_enabled);
        logedit_single_trap_light_16_sharpening->setObjectName(QString::fromUtf8("logedit_single_trap_light_16_sharpening"));

        gridLayout_single_trap_light_16->addWidget(logedit_single_trap_light_16_sharpening, 8, 1, 1, 2);

        label_single_trap_light_16_blur = new QLabel(groupCheck_single_trap_light_16_enabled);
        label_single_trap_light_16_blur->setObjectName(QString::fromUtf8("label_single_trap_light_16_blur"));

        gridLayout_single_trap_light_16->addWidget(label_single_trap_light_16_blur, 8, 3, 1, 1);

        logedit_single_trap_light_16_blur = new MyLineEdit(groupCheck_single_trap_light_16_enabled);
        logedit_single_trap_light_16_blur->setObjectName(QString::fromUtf8("logedit_single_trap_light_16_blur"));

        gridLayout_single_trap_light_16->addWidget(logedit_single_trap_light_16_blur, 8, 4, 1, 1);

        label_single_trap_light_16_solid_intensity = new QLabel(groupCheck_single_trap_light_16_enabled);
        label_single_trap_light_16_solid_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_16_solid_intensity"));

        gridLayout_single_trap_light_16->addWidget(label_single_trap_light_16_solid_intensity, 9, 0, 1, 1);

        logedit_single_trap_light_16_solid_intensity = new MyLineEdit(groupCheck_single_trap_light_16_enabled);
        logedit_single_trap_light_16_solid_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_16_solid_intensity"));

        gridLayout_single_trap_light_16->addWidget(logedit_single_trap_light_16_solid_intensity, 9, 1, 1, 2);

        label_single_trap_light_16_softness = new QLabel(groupCheck_single_trap_light_16_enabled);
        label_single_trap_light_16_softness->setObjectName(QString::fromUtf8("label_single_trap_light_16_softness"));

        gridLayout_single_trap_light_16->addWidget(label_single_trap_light_16_softness, 9, 3, 1, 1);

        logedit_single_trap_light_16_softness = new MyLineEdit(groupCheck_single_trap_light_16_enabled);
        logedit_single_trap_light_16_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_16_softness"));

        gridLayout_single_trap_light_16->addWidget(logedit_single_trap_light_16_softness, 9, 4, 1, 1);

        label_single_trap_light_16_relative_size = new QLabel(groupCheck_single_trap_light_16_enabled);
        label_single_trap_light_16_relative_size->setObjectName(QString::fromUtf8("label_single_trap_light_16_relative_size"));

        gridLayout_single_trap_light_16->addWidget(label_single_trap_light_16_relative_size, 10, 0, 1, 1);

        logedit_single_trap_light_16_relative_size = new MyLineEdit(groupCheck_single_trap_light_16_enabled);
        logedit_single_trap_light_16_relative_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_16_relative_size"));

        gridLayout_single_trap_light_16->addWidget(logedit_single_trap_light_16_relative_size, 10, 1, 1, 2);

        checkBox_single_trap_light_16_pre_transformed = new MyCheckBox(groupCheck_single_trap_light_16_enabled);
        checkBox_single_trap_light_16_pre_transformed->setObjectName(QString::fromUtf8("checkBox_single_trap_light_16_pre_transformed"));

        gridLayout_single_trap_light_16->addWidget(checkBox_single_trap_light_16_pre_transformed, 11, 0, 1, 1);

        label_single_trap_light_16_position_mode = new QLabel(groupCheck_single_trap_light_16_enabled);
        label_single_trap_light_16_position_mode->setObjectName(QString::fromUtf8("label_single_trap_light_16_position_mode"));

        gridLayout_single_trap_light_16->addWidget(label_single_trap_light_16_position_mode, 12, 0, 1, 1);

        comboBox_single_trap_light_16_position_mode = new MyComboBox(groupCheck_single_trap_light_16_enabled);
        comboBox_single_trap_light_16_position_mode->addItem(QString());
        comboBox_single_trap_light_16_position_mode->addItem(QString());
        comboBox_single_trap_light_16_position_mode->addItem(QString());
        comboBox_single_trap_light_16_position_mode->addItem(QString());
        comboBox_single_trap_light_16_position_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_16_position_mode"));

        gridLayout_single_trap_light_16->addWidget(comboBox_single_trap_light_16_position_mode, 12, 1, 1, 2);

        label_single_trap_light_16_coloring_mode = new QLabel(groupCheck_single_trap_light_16_enabled);
        label_single_trap_light_16_coloring_mode->setObjectName(QString::fromUtf8("label_single_trap_light_16_coloring_mode"));

        gridLayout_single_trap_light_16->addWidget(label_single_trap_light_16_coloring_mode, 13, 0, 1, 1);

        comboBox_single_trap_light_16_coloring_mode = new MyComboBox(groupCheck_single_trap_light_16_enabled);
        comboBox_single_trap_light_16_coloring_mode->addItem(QString());
        comboBox_single_trap_light_16_coloring_mode->addItem(QString());
        comboBox_single_trap_light_16_coloring_mode->addItem(QString());
        comboBox_single_trap_light_16_coloring_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_16_coloring_mode"));

        gridLayout_single_trap_light_16->addWidget(comboBox_single_trap_light_16_coloring_mode, 13, 1, 1, 2);

        label_single_trap_light_16_falloff_type = new QLabel(groupCheck_single_trap_light_16_enabled);
        label_single_trap_light_16_falloff_type->setObjectName(QString::fromUtf8("label_single_trap_light_16_falloff_type"));

        gridLayout_single_trap_light_16->addWidget(label_single_trap_light_16_falloff_type, 14, 0, 1, 1);

        comboBox_single_trap_light_16_falloff_type = new MyComboBox(groupCheck_single_trap_light_16_enabled);
        comboBox_single_trap_light_16_falloff_type->addItem(QString());
        comboBox_single_trap_light_16_falloff_type->addItem(QString());
        comboBox_single_trap_light_16_falloff_type->addItem(QString());
        comboBox_single_trap_light_16_falloff_type->addItem(QString());
        comboBox_single_trap_light_16_falloff_type->addItem(QString());
        comboBox_single_trap_light_16_falloff_type->setObjectName(QString::fromUtf8("comboBox_single_trap_light_16_falloff_type"));

        gridLayout_single_trap_light_16->addWidget(comboBox_single_trap_light_16_falloff_type, 14, 1, 1, 2);

        label_single_trap_light_16_edge_softness = new QLabel(groupCheck_single_trap_light_16_enabled);
        label_single_trap_light_16_edge_softness->setObjectName(QString::fromUtf8("label_single_trap_light_16_edge_softness"));

        gridLayout_single_trap_light_16->addWidget(label_single_trap_light_16_edge_softness, 15, 0, 1, 1);

        logedit_single_trap_light_16_edge_softness = new MyLineEdit(groupCheck_single_trap_light_16_enabled);
        logedit_single_trap_light_16_edge_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_16_edge_softness"));

        gridLayout_single_trap_light_16->addWidget(logedit_single_trap_light_16_edge_softness, 15, 1, 1, 2);

        label_single_trap_light_16_anim_orbit_radius = new QLabel(groupCheck_single_trap_light_16_enabled);
        label_single_trap_light_16_anim_orbit_radius->setObjectName(QString::fromUtf8("label_single_trap_light_16_anim_orbit_radius"));

        gridLayout_single_trap_light_16->addWidget(label_single_trap_light_16_anim_orbit_radius, 16, 0, 1, 1);

        logedit_single_trap_light_16_anim_orbit_radius = new MyLineEdit(groupCheck_single_trap_light_16_enabled);
        logedit_single_trap_light_16_anim_orbit_radius->setObjectName(QString::fromUtf8("logedit_single_trap_light_16_anim_orbit_radius"));

        gridLayout_single_trap_light_16->addWidget(logedit_single_trap_light_16_anim_orbit_radius, 16, 1, 1, 1);

        logedit_single_trap_light_16_anim_orbit_speed = new MyLineEdit(groupCheck_single_trap_light_16_enabled);
        logedit_single_trap_light_16_anim_orbit_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_16_anim_orbit_speed"));

        gridLayout_single_trap_light_16->addWidget(logedit_single_trap_light_16_anim_orbit_speed, 16, 2, 1, 1);

        logedit_single_trap_light_16_anim_pulsate_speed = new MyLineEdit(groupCheck_single_trap_light_16_enabled);
        logedit_single_trap_light_16_anim_pulsate_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_16_anim_pulsate_speed"));

        gridLayout_single_trap_light_16->addWidget(logedit_single_trap_light_16_anim_pulsate_speed, 16, 3, 1, 1);

        logedit_single_trap_light_16_anim_pulsate_amount = new MyLineEdit(groupCheck_single_trap_light_16_enabled);
        logedit_single_trap_light_16_anim_pulsate_amount->setObjectName(QString::fromUtf8("logedit_single_trap_light_16_anim_pulsate_amount"));

        gridLayout_single_trap_light_16->addWidget(logedit_single_trap_light_16_anim_pulsate_amount, 16, 4, 1, 1);

        pushButton_single_trap_light_16_place_surface = new QPushButton(groupCheck_single_trap_light_16_enabled);
        pushButton_single_trap_light_16_place_surface->setObjectName(QString::fromUtf8("pushButton_single_trap_light_16_place_surface"));

        gridLayout_single_trap_light_16->addWidget(pushButton_single_trap_light_16_place_surface, 17, 0, 1, 5);

        pushButton_single_trap_light_16_place_target = new QPushButton(groupCheck_single_trap_light_16_enabled);
        pushButton_single_trap_light_16_place_target->setObjectName(QString::fromUtf8("pushButton_single_trap_light_16_place_target"));

        gridLayout_single_trap_light_16->addWidget(pushButton_single_trap_light_16_place_target, 18, 0, 1, 5);


        verticalLayout_single_trap_layers->addWidget(groupCheck_single_trap_light_16_enabled);

        groupCheck_single_trap_light_17_enabled = new MyGroupBox(scrollAreaWidgetContents_single_trap);
        groupCheck_single_trap_light_17_enabled->setObjectName(QString::fromUtf8("groupCheck_single_trap_light_17_enabled"));
        groupCheck_single_trap_light_17_enabled->setCheckable(true);
        gridLayout_single_trap_light_17 = new QGridLayout(groupCheck_single_trap_light_17_enabled);
        gridLayout_single_trap_light_17->setSpacing(2);
        gridLayout_single_trap_light_17->setObjectName(QString::fromUtf8("gridLayout_single_trap_light_17"));
        label_single_trap_light_17_shape = new QLabel(groupCheck_single_trap_light_17_enabled);
        label_single_trap_light_17_shape->setObjectName(QString::fromUtf8("label_single_trap_light_17_shape"));

        gridLayout_single_trap_light_17->addWidget(label_single_trap_light_17_shape, 0, 0, 1, 1);

        comboBox_single_trap_light_17_shape = new MyComboBox(groupCheck_single_trap_light_17_enabled);
        comboBox_single_trap_light_17_shape->addItem(QString());
        comboBox_single_trap_light_17_shape->addItem(QString());
        comboBox_single_trap_light_17_shape->addItem(QString());
        comboBox_single_trap_light_17_shape->addItem(QString());
        comboBox_single_trap_light_17_shape->addItem(QString());
        comboBox_single_trap_light_17_shape->addItem(QString());
        comboBox_single_trap_light_17_shape->addItem(QString());
        comboBox_single_trap_light_17_shape->addItem(QString());
        comboBox_single_trap_light_17_shape->addItem(QString());
        comboBox_single_trap_light_17_shape->addItem(QString());
        comboBox_single_trap_light_17_shape->addItem(QString());
        comboBox_single_trap_light_17_shape->addItem(QString());
        comboBox_single_trap_light_17_shape->addItem(QString());
        comboBox_single_trap_light_17_shape->addItem(QString());
        comboBox_single_trap_light_17_shape->setObjectName(QString::fromUtf8("comboBox_single_trap_light_17_shape"));

        gridLayout_single_trap_light_17->addWidget(comboBox_single_trap_light_17_shape, 0, 1, 1, 2);

        label_single_trap_light_17_position = new QLabel(groupCheck_single_trap_light_17_enabled);
        label_single_trap_light_17_position->setObjectName(QString::fromUtf8("label_single_trap_light_17_position"));

        gridLayout_single_trap_light_17->addWidget(label_single_trap_light_17_position, 1, 0, 1, 1);

        vect3_single_trap_light_17_position_x = new MyLineEdit(groupCheck_single_trap_light_17_enabled);
        vect3_single_trap_light_17_position_x->setObjectName(QString::fromUtf8("vect3_single_trap_light_17_position_x"));

        gridLayout_single_trap_light_17->addWidget(vect3_single_trap_light_17_position_x, 1, 1, 1, 1);

        vect3_single_trap_light_17_position_y = new MyLineEdit(groupCheck_single_trap_light_17_enabled);
        vect3_single_trap_light_17_position_y->setObjectName(QString::fromUtf8("vect3_single_trap_light_17_position_y"));

        gridLayout_single_trap_light_17->addWidget(vect3_single_trap_light_17_position_y, 1, 2, 1, 1);

        vect3_single_trap_light_17_position_z = new MyLineEdit(groupCheck_single_trap_light_17_enabled);
        vect3_single_trap_light_17_position_z->setObjectName(QString::fromUtf8("vect3_single_trap_light_17_position_z"));

        gridLayout_single_trap_light_17->addWidget(vect3_single_trap_light_17_position_z, 1, 3, 1, 1);

        pushButton_single_trap_light_17_place_camera = new QPushButton(groupCheck_single_trap_light_17_enabled);
        pushButton_single_trap_light_17_place_camera->setObjectName(QString::fromUtf8("pushButton_single_trap_light_17_place_camera"));

        gridLayout_single_trap_light_17->addWidget(pushButton_single_trap_light_17_place_camera, 1, 4, 1, 1);

        label_single_trap_light_17_size = new QLabel(groupCheck_single_trap_light_17_enabled);
        label_single_trap_light_17_size->setObjectName(QString::fromUtf8("label_single_trap_light_17_size"));

        gridLayout_single_trap_light_17->addWidget(label_single_trap_light_17_size, 2, 0, 1, 1);

        logedit_single_trap_light_17_size = new MyLineEdit(groupCheck_single_trap_light_17_enabled);
        logedit_single_trap_light_17_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_17_size"));

        gridLayout_single_trap_light_17->addWidget(logedit_single_trap_light_17_size, 2, 1, 1, 2);

        label_single_trap_light_17_size2 = new QLabel(groupCheck_single_trap_light_17_enabled);
        label_single_trap_light_17_size2->setObjectName(QString::fromUtf8("label_single_trap_light_17_size2"));

        gridLayout_single_trap_light_17->addWidget(label_single_trap_light_17_size2, 2, 3, 1, 1);

        logedit_single_trap_light_17_size2 = new MyLineEdit(groupCheck_single_trap_light_17_enabled);
        logedit_single_trap_light_17_size2->setObjectName(QString::fromUtf8("logedit_single_trap_light_17_size2"));

        gridLayout_single_trap_light_17->addWidget(logedit_single_trap_light_17_size2, 2, 4, 1, 1);

        label_single_trap_light_17_thickness = new QLabel(groupCheck_single_trap_light_17_enabled);
        label_single_trap_light_17_thickness->setObjectName(QString::fromUtf8("label_single_trap_light_17_thickness"));

        gridLayout_single_trap_light_17->addWidget(label_single_trap_light_17_thickness, 3, 0, 1, 1);

        logedit_single_trap_light_17_thickness = new MyLineEdit(groupCheck_single_trap_light_17_enabled);
        logedit_single_trap_light_17_thickness->setObjectName(QString::fromUtf8("logedit_single_trap_light_17_thickness"));

        gridLayout_single_trap_light_17->addWidget(logedit_single_trap_light_17_thickness, 3, 1, 1, 2);

        label_single_trap_light_17_rotation = new QLabel(groupCheck_single_trap_light_17_enabled);
        label_single_trap_light_17_rotation->setObjectName(QString::fromUtf8("label_single_trap_light_17_rotation"));

        gridLayout_single_trap_light_17->addWidget(label_single_trap_light_17_rotation, 4, 0, 1, 1);

        spinboxd3_single_trap_light_17_rotation_x = new MyDoubleSpinBox(groupCheck_single_trap_light_17_enabled);
        spinboxd3_single_trap_light_17_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_17_rotation_x"));

        gridLayout_single_trap_light_17->addWidget(spinboxd3_single_trap_light_17_rotation_x, 4, 1, 1, 1);

        spinboxd3_single_trap_light_17_rotation_y = new MyDoubleSpinBox(groupCheck_single_trap_light_17_enabled);
        spinboxd3_single_trap_light_17_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_17_rotation_y"));

        gridLayout_single_trap_light_17->addWidget(spinboxd3_single_trap_light_17_rotation_y, 4, 2, 1, 1);

        spinboxd3_single_trap_light_17_rotation_z = new MyDoubleSpinBox(groupCheck_single_trap_light_17_enabled);
        spinboxd3_single_trap_light_17_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_17_rotation_z"));

        gridLayout_single_trap_light_17->addWidget(spinboxd3_single_trap_light_17_rotation_z, 4, 3, 1, 1);

        label_single_trap_light_17_intensity = new QLabel(groupCheck_single_trap_light_17_enabled);
        label_single_trap_light_17_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_17_intensity"));

        gridLayout_single_trap_light_17->addWidget(label_single_trap_light_17_intensity, 5, 0, 1, 1);

        logedit_single_trap_light_17_intensity = new MyLineEdit(groupCheck_single_trap_light_17_enabled);
        logedit_single_trap_light_17_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_17_intensity"));

        gridLayout_single_trap_light_17->addWidget(logedit_single_trap_light_17_intensity, 5, 1, 1, 2);

        label_single_trap_light_17_color = new QLabel(groupCheck_single_trap_light_17_enabled);
        label_single_trap_light_17_color->setObjectName(QString::fromUtf8("label_single_trap_light_17_color"));

        gridLayout_single_trap_light_17->addWidget(label_single_trap_light_17_color, 6, 0, 1, 1);

        colorButton_single_trap_light_17_color = new MyColorButton(groupCheck_single_trap_light_17_enabled);
        colorButton_single_trap_light_17_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_17_color"));

        gridLayout_single_trap_light_17->addWidget(colorButton_single_trap_light_17_color, 6, 1, 1, 1);

        label_single_trap_light_17_gradient_color = new QLabel(groupCheck_single_trap_light_17_enabled);
        label_single_trap_light_17_gradient_color->setObjectName(QString::fromUtf8("label_single_trap_light_17_gradient_color"));

        gridLayout_single_trap_light_17->addWidget(label_single_trap_light_17_gradient_color, 6, 2, 1, 1);

        colorButton_single_trap_light_17_gradient_color = new MyColorButton(groupCheck_single_trap_light_17_enabled);
        colorButton_single_trap_light_17_gradient_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_17_gradient_color"));

        gridLayout_single_trap_light_17->addWidget(colorButton_single_trap_light_17_gradient_color, 6, 3, 1, 2);

        label_single_trap_light_17_visibility = new QLabel(groupCheck_single_trap_light_17_enabled);
        label_single_trap_light_17_visibility->setObjectName(QString::fromUtf8("label_single_trap_light_17_visibility"));

        gridLayout_single_trap_light_17->addWidget(label_single_trap_light_17_visibility, 7, 0, 1, 1);

        logedit_single_trap_light_17_visibility = new MyLineEdit(groupCheck_single_trap_light_17_enabled);
        logedit_single_trap_light_17_visibility->setObjectName(QString::fromUtf8("logedit_single_trap_light_17_visibility"));

        gridLayout_single_trap_light_17->addWidget(logedit_single_trap_light_17_visibility, 7, 1, 1, 2);

        label_single_trap_light_17_max_distance = new QLabel(groupCheck_single_trap_light_17_enabled);
        label_single_trap_light_17_max_distance->setObjectName(QString::fromUtf8("label_single_trap_light_17_max_distance"));

        gridLayout_single_trap_light_17->addWidget(label_single_trap_light_17_max_distance, 7, 3, 1, 1);

        logedit_single_trap_light_17_max_distance = new MyLineEdit(groupCheck_single_trap_light_17_enabled);
        logedit_single_trap_light_17_max_distance->setObjectName(QString::fromUtf8("logedit_single_trap_light_17_max_distance"));

        gridLayout_single_trap_light_17->addWidget(logedit_single_trap_light_17_max_distance, 7, 4, 1, 1);

        label_single_trap_light_17_sharpening = new QLabel(groupCheck_single_trap_light_17_enabled);
        label_single_trap_light_17_sharpening->setObjectName(QString::fromUtf8("label_single_trap_light_17_sharpening"));

        gridLayout_single_trap_light_17->addWidget(label_single_trap_light_17_sharpening, 8, 0, 1, 1);

        logedit_single_trap_light_17_sharpening = new MyLineEdit(groupCheck_single_trap_light_17_enabled);
        logedit_single_trap_light_17_sharpening->setObjectName(QString::fromUtf8("logedit_single_trap_light_17_sharpening"));

        gridLayout_single_trap_light_17->addWidget(logedit_single_trap_light_17_sharpening, 8, 1, 1, 2);

        label_single_trap_light_17_blur = new QLabel(groupCheck_single_trap_light_17_enabled);
        label_single_trap_light_17_blur->setObjectName(QString::fromUtf8("label_single_trap_light_17_blur"));

        gridLayout_single_trap_light_17->addWidget(label_single_trap_light_17_blur, 8, 3, 1, 1);

        logedit_single_trap_light_17_blur = new MyLineEdit(groupCheck_single_trap_light_17_enabled);
        logedit_single_trap_light_17_blur->setObjectName(QString::fromUtf8("logedit_single_trap_light_17_blur"));

        gridLayout_single_trap_light_17->addWidget(logedit_single_trap_light_17_blur, 8, 4, 1, 1);

        label_single_trap_light_17_solid_intensity = new QLabel(groupCheck_single_trap_light_17_enabled);
        label_single_trap_light_17_solid_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_17_solid_intensity"));

        gridLayout_single_trap_light_17->addWidget(label_single_trap_light_17_solid_intensity, 9, 0, 1, 1);

        logedit_single_trap_light_17_solid_intensity = new MyLineEdit(groupCheck_single_trap_light_17_enabled);
        logedit_single_trap_light_17_solid_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_17_solid_intensity"));

        gridLayout_single_trap_light_17->addWidget(logedit_single_trap_light_17_solid_intensity, 9, 1, 1, 2);

        label_single_trap_light_17_softness = new QLabel(groupCheck_single_trap_light_17_enabled);
        label_single_trap_light_17_softness->setObjectName(QString::fromUtf8("label_single_trap_light_17_softness"));

        gridLayout_single_trap_light_17->addWidget(label_single_trap_light_17_softness, 9, 3, 1, 1);

        logedit_single_trap_light_17_softness = new MyLineEdit(groupCheck_single_trap_light_17_enabled);
        logedit_single_trap_light_17_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_17_softness"));

        gridLayout_single_trap_light_17->addWidget(logedit_single_trap_light_17_softness, 9, 4, 1, 1);

        label_single_trap_light_17_relative_size = new QLabel(groupCheck_single_trap_light_17_enabled);
        label_single_trap_light_17_relative_size->setObjectName(QString::fromUtf8("label_single_trap_light_17_relative_size"));

        gridLayout_single_trap_light_17->addWidget(label_single_trap_light_17_relative_size, 10, 0, 1, 1);

        logedit_single_trap_light_17_relative_size = new MyLineEdit(groupCheck_single_trap_light_17_enabled);
        logedit_single_trap_light_17_relative_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_17_relative_size"));

        gridLayout_single_trap_light_17->addWidget(logedit_single_trap_light_17_relative_size, 10, 1, 1, 2);

        checkBox_single_trap_light_17_pre_transformed = new MyCheckBox(groupCheck_single_trap_light_17_enabled);
        checkBox_single_trap_light_17_pre_transformed->setObjectName(QString::fromUtf8("checkBox_single_trap_light_17_pre_transformed"));

        gridLayout_single_trap_light_17->addWidget(checkBox_single_trap_light_17_pre_transformed, 11, 0, 1, 1);

        label_single_trap_light_17_position_mode = new QLabel(groupCheck_single_trap_light_17_enabled);
        label_single_trap_light_17_position_mode->setObjectName(QString::fromUtf8("label_single_trap_light_17_position_mode"));

        gridLayout_single_trap_light_17->addWidget(label_single_trap_light_17_position_mode, 12, 0, 1, 1);

        comboBox_single_trap_light_17_position_mode = new MyComboBox(groupCheck_single_trap_light_17_enabled);
        comboBox_single_trap_light_17_position_mode->addItem(QString());
        comboBox_single_trap_light_17_position_mode->addItem(QString());
        comboBox_single_trap_light_17_position_mode->addItem(QString());
        comboBox_single_trap_light_17_position_mode->addItem(QString());
        comboBox_single_trap_light_17_position_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_17_position_mode"));

        gridLayout_single_trap_light_17->addWidget(comboBox_single_trap_light_17_position_mode, 12, 1, 1, 2);

        label_single_trap_light_17_coloring_mode = new QLabel(groupCheck_single_trap_light_17_enabled);
        label_single_trap_light_17_coloring_mode->setObjectName(QString::fromUtf8("label_single_trap_light_17_coloring_mode"));

        gridLayout_single_trap_light_17->addWidget(label_single_trap_light_17_coloring_mode, 13, 0, 1, 1);

        comboBox_single_trap_light_17_coloring_mode = new MyComboBox(groupCheck_single_trap_light_17_enabled);
        comboBox_single_trap_light_17_coloring_mode->addItem(QString());
        comboBox_single_trap_light_17_coloring_mode->addItem(QString());
        comboBox_single_trap_light_17_coloring_mode->addItem(QString());
        comboBox_single_trap_light_17_coloring_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_17_coloring_mode"));

        gridLayout_single_trap_light_17->addWidget(comboBox_single_trap_light_17_coloring_mode, 13, 1, 1, 2);

        label_single_trap_light_17_falloff_type = new QLabel(groupCheck_single_trap_light_17_enabled);
        label_single_trap_light_17_falloff_type->setObjectName(QString::fromUtf8("label_single_trap_light_17_falloff_type"));

        gridLayout_single_trap_light_17->addWidget(label_single_trap_light_17_falloff_type, 14, 0, 1, 1);

        comboBox_single_trap_light_17_falloff_type = new MyComboBox(groupCheck_single_trap_light_17_enabled);
        comboBox_single_trap_light_17_falloff_type->addItem(QString());
        comboBox_single_trap_light_17_falloff_type->addItem(QString());
        comboBox_single_trap_light_17_falloff_type->addItem(QString());
        comboBox_single_trap_light_17_falloff_type->addItem(QString());
        comboBox_single_trap_light_17_falloff_type->addItem(QString());
        comboBox_single_trap_light_17_falloff_type->setObjectName(QString::fromUtf8("comboBox_single_trap_light_17_falloff_type"));

        gridLayout_single_trap_light_17->addWidget(comboBox_single_trap_light_17_falloff_type, 14, 1, 1, 2);

        label_single_trap_light_17_edge_softness = new QLabel(groupCheck_single_trap_light_17_enabled);
        label_single_trap_light_17_edge_softness->setObjectName(QString::fromUtf8("label_single_trap_light_17_edge_softness"));

        gridLayout_single_trap_light_17->addWidget(label_single_trap_light_17_edge_softness, 15, 0, 1, 1);

        logedit_single_trap_light_17_edge_softness = new MyLineEdit(groupCheck_single_trap_light_17_enabled);
        logedit_single_trap_light_17_edge_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_17_edge_softness"));

        gridLayout_single_trap_light_17->addWidget(logedit_single_trap_light_17_edge_softness, 15, 1, 1, 2);

        label_single_trap_light_17_anim_orbit_radius = new QLabel(groupCheck_single_trap_light_17_enabled);
        label_single_trap_light_17_anim_orbit_radius->setObjectName(QString::fromUtf8("label_single_trap_light_17_anim_orbit_radius"));

        gridLayout_single_trap_light_17->addWidget(label_single_trap_light_17_anim_orbit_radius, 16, 0, 1, 1);

        logedit_single_trap_light_17_anim_orbit_radius = new MyLineEdit(groupCheck_single_trap_light_17_enabled);
        logedit_single_trap_light_17_anim_orbit_radius->setObjectName(QString::fromUtf8("logedit_single_trap_light_17_anim_orbit_radius"));

        gridLayout_single_trap_light_17->addWidget(logedit_single_trap_light_17_anim_orbit_radius, 16, 1, 1, 1);

        logedit_single_trap_light_17_anim_orbit_speed = new MyLineEdit(groupCheck_single_trap_light_17_enabled);
        logedit_single_trap_light_17_anim_orbit_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_17_anim_orbit_speed"));

        gridLayout_single_trap_light_17->addWidget(logedit_single_trap_light_17_anim_orbit_speed, 16, 2, 1, 1);

        logedit_single_trap_light_17_anim_pulsate_speed = new MyLineEdit(groupCheck_single_trap_light_17_enabled);
        logedit_single_trap_light_17_anim_pulsate_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_17_anim_pulsate_speed"));

        gridLayout_single_trap_light_17->addWidget(logedit_single_trap_light_17_anim_pulsate_speed, 16, 3, 1, 1);

        logedit_single_trap_light_17_anim_pulsate_amount = new MyLineEdit(groupCheck_single_trap_light_17_enabled);
        logedit_single_trap_light_17_anim_pulsate_amount->setObjectName(QString::fromUtf8("logedit_single_trap_light_17_anim_pulsate_amount"));

        gridLayout_single_trap_light_17->addWidget(logedit_single_trap_light_17_anim_pulsate_amount, 16, 4, 1, 1);

        pushButton_single_trap_light_17_place_surface = new QPushButton(groupCheck_single_trap_light_17_enabled);
        pushButton_single_trap_light_17_place_surface->setObjectName(QString::fromUtf8("pushButton_single_trap_light_17_place_surface"));

        gridLayout_single_trap_light_17->addWidget(pushButton_single_trap_light_17_place_surface, 17, 0, 1, 5);

        pushButton_single_trap_light_17_place_target = new QPushButton(groupCheck_single_trap_light_17_enabled);
        pushButton_single_trap_light_17_place_target->setObjectName(QString::fromUtf8("pushButton_single_trap_light_17_place_target"));

        gridLayout_single_trap_light_17->addWidget(pushButton_single_trap_light_17_place_target, 18, 0, 1, 5);


        verticalLayout_single_trap_layers->addWidget(groupCheck_single_trap_light_17_enabled);

        groupCheck_single_trap_light_18_enabled = new MyGroupBox(scrollAreaWidgetContents_single_trap);
        groupCheck_single_trap_light_18_enabled->setObjectName(QString::fromUtf8("groupCheck_single_trap_light_18_enabled"));
        groupCheck_single_trap_light_18_enabled->setCheckable(true);
        gridLayout_single_trap_light_18 = new QGridLayout(groupCheck_single_trap_light_18_enabled);
        gridLayout_single_trap_light_18->setSpacing(2);
        gridLayout_single_trap_light_18->setObjectName(QString::fromUtf8("gridLayout_single_trap_light_18"));
        label_single_trap_light_18_shape = new QLabel(groupCheck_single_trap_light_18_enabled);
        label_single_trap_light_18_shape->setObjectName(QString::fromUtf8("label_single_trap_light_18_shape"));

        gridLayout_single_trap_light_18->addWidget(label_single_trap_light_18_shape, 0, 0, 1, 1);

        comboBox_single_trap_light_18_shape = new MyComboBox(groupCheck_single_trap_light_18_enabled);
        comboBox_single_trap_light_18_shape->addItem(QString());
        comboBox_single_trap_light_18_shape->addItem(QString());
        comboBox_single_trap_light_18_shape->addItem(QString());
        comboBox_single_trap_light_18_shape->addItem(QString());
        comboBox_single_trap_light_18_shape->addItem(QString());
        comboBox_single_trap_light_18_shape->addItem(QString());
        comboBox_single_trap_light_18_shape->addItem(QString());
        comboBox_single_trap_light_18_shape->addItem(QString());
        comboBox_single_trap_light_18_shape->addItem(QString());
        comboBox_single_trap_light_18_shape->addItem(QString());
        comboBox_single_trap_light_18_shape->addItem(QString());
        comboBox_single_trap_light_18_shape->addItem(QString());
        comboBox_single_trap_light_18_shape->addItem(QString());
        comboBox_single_trap_light_18_shape->addItem(QString());
        comboBox_single_trap_light_18_shape->setObjectName(QString::fromUtf8("comboBox_single_trap_light_18_shape"));

        gridLayout_single_trap_light_18->addWidget(comboBox_single_trap_light_18_shape, 0, 1, 1, 2);

        label_single_trap_light_18_position = new QLabel(groupCheck_single_trap_light_18_enabled);
        label_single_trap_light_18_position->setObjectName(QString::fromUtf8("label_single_trap_light_18_position"));

        gridLayout_single_trap_light_18->addWidget(label_single_trap_light_18_position, 1, 0, 1, 1);

        vect3_single_trap_light_18_position_x = new MyLineEdit(groupCheck_single_trap_light_18_enabled);
        vect3_single_trap_light_18_position_x->setObjectName(QString::fromUtf8("vect3_single_trap_light_18_position_x"));

        gridLayout_single_trap_light_18->addWidget(vect3_single_trap_light_18_position_x, 1, 1, 1, 1);

        vect3_single_trap_light_18_position_y = new MyLineEdit(groupCheck_single_trap_light_18_enabled);
        vect3_single_trap_light_18_position_y->setObjectName(QString::fromUtf8("vect3_single_trap_light_18_position_y"));

        gridLayout_single_trap_light_18->addWidget(vect3_single_trap_light_18_position_y, 1, 2, 1, 1);

        vect3_single_trap_light_18_position_z = new MyLineEdit(groupCheck_single_trap_light_18_enabled);
        vect3_single_trap_light_18_position_z->setObjectName(QString::fromUtf8("vect3_single_trap_light_18_position_z"));

        gridLayout_single_trap_light_18->addWidget(vect3_single_trap_light_18_position_z, 1, 3, 1, 1);

        pushButton_single_trap_light_18_place_camera = new QPushButton(groupCheck_single_trap_light_18_enabled);
        pushButton_single_trap_light_18_place_camera->setObjectName(QString::fromUtf8("pushButton_single_trap_light_18_place_camera"));

        gridLayout_single_trap_light_18->addWidget(pushButton_single_trap_light_18_place_camera, 1, 4, 1, 1);

        label_single_trap_light_18_size = new QLabel(groupCheck_single_trap_light_18_enabled);
        label_single_trap_light_18_size->setObjectName(QString::fromUtf8("label_single_trap_light_18_size"));

        gridLayout_single_trap_light_18->addWidget(label_single_trap_light_18_size, 2, 0, 1, 1);

        logedit_single_trap_light_18_size = new MyLineEdit(groupCheck_single_trap_light_18_enabled);
        logedit_single_trap_light_18_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_18_size"));

        gridLayout_single_trap_light_18->addWidget(logedit_single_trap_light_18_size, 2, 1, 1, 2);

        label_single_trap_light_18_size2 = new QLabel(groupCheck_single_trap_light_18_enabled);
        label_single_trap_light_18_size2->setObjectName(QString::fromUtf8("label_single_trap_light_18_size2"));

        gridLayout_single_trap_light_18->addWidget(label_single_trap_light_18_size2, 2, 3, 1, 1);

        logedit_single_trap_light_18_size2 = new MyLineEdit(groupCheck_single_trap_light_18_enabled);
        logedit_single_trap_light_18_size2->setObjectName(QString::fromUtf8("logedit_single_trap_light_18_size2"));

        gridLayout_single_trap_light_18->addWidget(logedit_single_trap_light_18_size2, 2, 4, 1, 1);

        label_single_trap_light_18_thickness = new QLabel(groupCheck_single_trap_light_18_enabled);
        label_single_trap_light_18_thickness->setObjectName(QString::fromUtf8("label_single_trap_light_18_thickness"));

        gridLayout_single_trap_light_18->addWidget(label_single_trap_light_18_thickness, 3, 0, 1, 1);

        logedit_single_trap_light_18_thickness = new MyLineEdit(groupCheck_single_trap_light_18_enabled);
        logedit_single_trap_light_18_thickness->setObjectName(QString::fromUtf8("logedit_single_trap_light_18_thickness"));

        gridLayout_single_trap_light_18->addWidget(logedit_single_trap_light_18_thickness, 3, 1, 1, 2);

        label_single_trap_light_18_rotation = new QLabel(groupCheck_single_trap_light_18_enabled);
        label_single_trap_light_18_rotation->setObjectName(QString::fromUtf8("label_single_trap_light_18_rotation"));

        gridLayout_single_trap_light_18->addWidget(label_single_trap_light_18_rotation, 4, 0, 1, 1);

        spinboxd3_single_trap_light_18_rotation_x = new MyDoubleSpinBox(groupCheck_single_trap_light_18_enabled);
        spinboxd3_single_trap_light_18_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_18_rotation_x"));

        gridLayout_single_trap_light_18->addWidget(spinboxd3_single_trap_light_18_rotation_x, 4, 1, 1, 1);

        spinboxd3_single_trap_light_18_rotation_y = new MyDoubleSpinBox(groupCheck_single_trap_light_18_enabled);
        spinboxd3_single_trap_light_18_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_18_rotation_y"));

        gridLayout_single_trap_light_18->addWidget(spinboxd3_single_trap_light_18_rotation_y, 4, 2, 1, 1);

        spinboxd3_single_trap_light_18_rotation_z = new MyDoubleSpinBox(groupCheck_single_trap_light_18_enabled);
        spinboxd3_single_trap_light_18_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_18_rotation_z"));

        gridLayout_single_trap_light_18->addWidget(spinboxd3_single_trap_light_18_rotation_z, 4, 3, 1, 1);

        label_single_trap_light_18_intensity = new QLabel(groupCheck_single_trap_light_18_enabled);
        label_single_trap_light_18_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_18_intensity"));

        gridLayout_single_trap_light_18->addWidget(label_single_trap_light_18_intensity, 5, 0, 1, 1);

        logedit_single_trap_light_18_intensity = new MyLineEdit(groupCheck_single_trap_light_18_enabled);
        logedit_single_trap_light_18_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_18_intensity"));

        gridLayout_single_trap_light_18->addWidget(logedit_single_trap_light_18_intensity, 5, 1, 1, 2);

        label_single_trap_light_18_color = new QLabel(groupCheck_single_trap_light_18_enabled);
        label_single_trap_light_18_color->setObjectName(QString::fromUtf8("label_single_trap_light_18_color"));

        gridLayout_single_trap_light_18->addWidget(label_single_trap_light_18_color, 6, 0, 1, 1);

        colorButton_single_trap_light_18_color = new MyColorButton(groupCheck_single_trap_light_18_enabled);
        colorButton_single_trap_light_18_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_18_color"));

        gridLayout_single_trap_light_18->addWidget(colorButton_single_trap_light_18_color, 6, 1, 1, 1);

        label_single_trap_light_18_gradient_color = new QLabel(groupCheck_single_trap_light_18_enabled);
        label_single_trap_light_18_gradient_color->setObjectName(QString::fromUtf8("label_single_trap_light_18_gradient_color"));

        gridLayout_single_trap_light_18->addWidget(label_single_trap_light_18_gradient_color, 6, 2, 1, 1);

        colorButton_single_trap_light_18_gradient_color = new MyColorButton(groupCheck_single_trap_light_18_enabled);
        colorButton_single_trap_light_18_gradient_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_18_gradient_color"));

        gridLayout_single_trap_light_18->addWidget(colorButton_single_trap_light_18_gradient_color, 6, 3, 1, 2);

        label_single_trap_light_18_visibility = new QLabel(groupCheck_single_trap_light_18_enabled);
        label_single_trap_light_18_visibility->setObjectName(QString::fromUtf8("label_single_trap_light_18_visibility"));

        gridLayout_single_trap_light_18->addWidget(label_single_trap_light_18_visibility, 7, 0, 1, 1);

        logedit_single_trap_light_18_visibility = new MyLineEdit(groupCheck_single_trap_light_18_enabled);
        logedit_single_trap_light_18_visibility->setObjectName(QString::fromUtf8("logedit_single_trap_light_18_visibility"));

        gridLayout_single_trap_light_18->addWidget(logedit_single_trap_light_18_visibility, 7, 1, 1, 2);

        label_single_trap_light_18_max_distance = new QLabel(groupCheck_single_trap_light_18_enabled);
        label_single_trap_light_18_max_distance->setObjectName(QString::fromUtf8("label_single_trap_light_18_max_distance"));

        gridLayout_single_trap_light_18->addWidget(label_single_trap_light_18_max_distance, 7, 3, 1, 1);

        logedit_single_trap_light_18_max_distance = new MyLineEdit(groupCheck_single_trap_light_18_enabled);
        logedit_single_trap_light_18_max_distance->setObjectName(QString::fromUtf8("logedit_single_trap_light_18_max_distance"));

        gridLayout_single_trap_light_18->addWidget(logedit_single_trap_light_18_max_distance, 7, 4, 1, 1);

        label_single_trap_light_18_sharpening = new QLabel(groupCheck_single_trap_light_18_enabled);
        label_single_trap_light_18_sharpening->setObjectName(QString::fromUtf8("label_single_trap_light_18_sharpening"));

        gridLayout_single_trap_light_18->addWidget(label_single_trap_light_18_sharpening, 8, 0, 1, 1);

        logedit_single_trap_light_18_sharpening = new MyLineEdit(groupCheck_single_trap_light_18_enabled);
        logedit_single_trap_light_18_sharpening->setObjectName(QString::fromUtf8("logedit_single_trap_light_18_sharpening"));

        gridLayout_single_trap_light_18->addWidget(logedit_single_trap_light_18_sharpening, 8, 1, 1, 2);

        label_single_trap_light_18_blur = new QLabel(groupCheck_single_trap_light_18_enabled);
        label_single_trap_light_18_blur->setObjectName(QString::fromUtf8("label_single_trap_light_18_blur"));

        gridLayout_single_trap_light_18->addWidget(label_single_trap_light_18_blur, 8, 3, 1, 1);

        logedit_single_trap_light_18_blur = new MyLineEdit(groupCheck_single_trap_light_18_enabled);
        logedit_single_trap_light_18_blur->setObjectName(QString::fromUtf8("logedit_single_trap_light_18_blur"));

        gridLayout_single_trap_light_18->addWidget(logedit_single_trap_light_18_blur, 8, 4, 1, 1);

        label_single_trap_light_18_solid_intensity = new QLabel(groupCheck_single_trap_light_18_enabled);
        label_single_trap_light_18_solid_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_18_solid_intensity"));

        gridLayout_single_trap_light_18->addWidget(label_single_trap_light_18_solid_intensity, 9, 0, 1, 1);

        logedit_single_trap_light_18_solid_intensity = new MyLineEdit(groupCheck_single_trap_light_18_enabled);
        logedit_single_trap_light_18_solid_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_18_solid_intensity"));

        gridLayout_single_trap_light_18->addWidget(logedit_single_trap_light_18_solid_intensity, 9, 1, 1, 2);

        label_single_trap_light_18_softness = new QLabel(groupCheck_single_trap_light_18_enabled);
        label_single_trap_light_18_softness->setObjectName(QString::fromUtf8("label_single_trap_light_18_softness"));

        gridLayout_single_trap_light_18->addWidget(label_single_trap_light_18_softness, 9, 3, 1, 1);

        logedit_single_trap_light_18_softness = new MyLineEdit(groupCheck_single_trap_light_18_enabled);
        logedit_single_trap_light_18_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_18_softness"));

        gridLayout_single_trap_light_18->addWidget(logedit_single_trap_light_18_softness, 9, 4, 1, 1);

        label_single_trap_light_18_relative_size = new QLabel(groupCheck_single_trap_light_18_enabled);
        label_single_trap_light_18_relative_size->setObjectName(QString::fromUtf8("label_single_trap_light_18_relative_size"));

        gridLayout_single_trap_light_18->addWidget(label_single_trap_light_18_relative_size, 10, 0, 1, 1);

        logedit_single_trap_light_18_relative_size = new MyLineEdit(groupCheck_single_trap_light_18_enabled);
        logedit_single_trap_light_18_relative_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_18_relative_size"));

        gridLayout_single_trap_light_18->addWidget(logedit_single_trap_light_18_relative_size, 10, 1, 1, 2);

        checkBox_single_trap_light_18_pre_transformed = new MyCheckBox(groupCheck_single_trap_light_18_enabled);
        checkBox_single_trap_light_18_pre_transformed->setObjectName(QString::fromUtf8("checkBox_single_trap_light_18_pre_transformed"));

        gridLayout_single_trap_light_18->addWidget(checkBox_single_trap_light_18_pre_transformed, 11, 0, 1, 1);

        label_single_trap_light_18_position_mode = new QLabel(groupCheck_single_trap_light_18_enabled);
        label_single_trap_light_18_position_mode->setObjectName(QString::fromUtf8("label_single_trap_light_18_position_mode"));

        gridLayout_single_trap_light_18->addWidget(label_single_trap_light_18_position_mode, 12, 0, 1, 1);

        comboBox_single_trap_light_18_position_mode = new MyComboBox(groupCheck_single_trap_light_18_enabled);
        comboBox_single_trap_light_18_position_mode->addItem(QString());
        comboBox_single_trap_light_18_position_mode->addItem(QString());
        comboBox_single_trap_light_18_position_mode->addItem(QString());
        comboBox_single_trap_light_18_position_mode->addItem(QString());
        comboBox_single_trap_light_18_position_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_18_position_mode"));

        gridLayout_single_trap_light_18->addWidget(comboBox_single_trap_light_18_position_mode, 12, 1, 1, 2);

        label_single_trap_light_18_coloring_mode = new QLabel(groupCheck_single_trap_light_18_enabled);
        label_single_trap_light_18_coloring_mode->setObjectName(QString::fromUtf8("label_single_trap_light_18_coloring_mode"));

        gridLayout_single_trap_light_18->addWidget(label_single_trap_light_18_coloring_mode, 13, 0, 1, 1);

        comboBox_single_trap_light_18_coloring_mode = new MyComboBox(groupCheck_single_trap_light_18_enabled);
        comboBox_single_trap_light_18_coloring_mode->addItem(QString());
        comboBox_single_trap_light_18_coloring_mode->addItem(QString());
        comboBox_single_trap_light_18_coloring_mode->addItem(QString());
        comboBox_single_trap_light_18_coloring_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_18_coloring_mode"));

        gridLayout_single_trap_light_18->addWidget(comboBox_single_trap_light_18_coloring_mode, 13, 1, 1, 2);

        label_single_trap_light_18_falloff_type = new QLabel(groupCheck_single_trap_light_18_enabled);
        label_single_trap_light_18_falloff_type->setObjectName(QString::fromUtf8("label_single_trap_light_18_falloff_type"));

        gridLayout_single_trap_light_18->addWidget(label_single_trap_light_18_falloff_type, 14, 0, 1, 1);

        comboBox_single_trap_light_18_falloff_type = new MyComboBox(groupCheck_single_trap_light_18_enabled);
        comboBox_single_trap_light_18_falloff_type->addItem(QString());
        comboBox_single_trap_light_18_falloff_type->addItem(QString());
        comboBox_single_trap_light_18_falloff_type->addItem(QString());
        comboBox_single_trap_light_18_falloff_type->addItem(QString());
        comboBox_single_trap_light_18_falloff_type->addItem(QString());
        comboBox_single_trap_light_18_falloff_type->setObjectName(QString::fromUtf8("comboBox_single_trap_light_18_falloff_type"));

        gridLayout_single_trap_light_18->addWidget(comboBox_single_trap_light_18_falloff_type, 14, 1, 1, 2);

        label_single_trap_light_18_edge_softness = new QLabel(groupCheck_single_trap_light_18_enabled);
        label_single_trap_light_18_edge_softness->setObjectName(QString::fromUtf8("label_single_trap_light_18_edge_softness"));

        gridLayout_single_trap_light_18->addWidget(label_single_trap_light_18_edge_softness, 15, 0, 1, 1);

        logedit_single_trap_light_18_edge_softness = new MyLineEdit(groupCheck_single_trap_light_18_enabled);
        logedit_single_trap_light_18_edge_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_18_edge_softness"));

        gridLayout_single_trap_light_18->addWidget(logedit_single_trap_light_18_edge_softness, 15, 1, 1, 2);

        label_single_trap_light_18_anim_orbit_radius = new QLabel(groupCheck_single_trap_light_18_enabled);
        label_single_trap_light_18_anim_orbit_radius->setObjectName(QString::fromUtf8("label_single_trap_light_18_anim_orbit_radius"));

        gridLayout_single_trap_light_18->addWidget(label_single_trap_light_18_anim_orbit_radius, 16, 0, 1, 1);

        logedit_single_trap_light_18_anim_orbit_radius = new MyLineEdit(groupCheck_single_trap_light_18_enabled);
        logedit_single_trap_light_18_anim_orbit_radius->setObjectName(QString::fromUtf8("logedit_single_trap_light_18_anim_orbit_radius"));

        gridLayout_single_trap_light_18->addWidget(logedit_single_trap_light_18_anim_orbit_radius, 16, 1, 1, 1);

        logedit_single_trap_light_18_anim_orbit_speed = new MyLineEdit(groupCheck_single_trap_light_18_enabled);
        logedit_single_trap_light_18_anim_orbit_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_18_anim_orbit_speed"));

        gridLayout_single_trap_light_18->addWidget(logedit_single_trap_light_18_anim_orbit_speed, 16, 2, 1, 1);

        logedit_single_trap_light_18_anim_pulsate_speed = new MyLineEdit(groupCheck_single_trap_light_18_enabled);
        logedit_single_trap_light_18_anim_pulsate_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_18_anim_pulsate_speed"));

        gridLayout_single_trap_light_18->addWidget(logedit_single_trap_light_18_anim_pulsate_speed, 16, 3, 1, 1);

        logedit_single_trap_light_18_anim_pulsate_amount = new MyLineEdit(groupCheck_single_trap_light_18_enabled);
        logedit_single_trap_light_18_anim_pulsate_amount->setObjectName(QString::fromUtf8("logedit_single_trap_light_18_anim_pulsate_amount"));

        gridLayout_single_trap_light_18->addWidget(logedit_single_trap_light_18_anim_pulsate_amount, 16, 4, 1, 1);

        pushButton_single_trap_light_18_place_surface = new QPushButton(groupCheck_single_trap_light_18_enabled);
        pushButton_single_trap_light_18_place_surface->setObjectName(QString::fromUtf8("pushButton_single_trap_light_18_place_surface"));

        gridLayout_single_trap_light_18->addWidget(pushButton_single_trap_light_18_place_surface, 17, 0, 1, 5);

        pushButton_single_trap_light_18_place_target = new QPushButton(groupCheck_single_trap_light_18_enabled);
        pushButton_single_trap_light_18_place_target->setObjectName(QString::fromUtf8("pushButton_single_trap_light_18_place_target"));

        gridLayout_single_trap_light_18->addWidget(pushButton_single_trap_light_18_place_target, 18, 0, 1, 5);


        verticalLayout_single_trap_layers->addWidget(groupCheck_single_trap_light_18_enabled);

        groupCheck_single_trap_light_19_enabled = new MyGroupBox(scrollAreaWidgetContents_single_trap);
        groupCheck_single_trap_light_19_enabled->setObjectName(QString::fromUtf8("groupCheck_single_trap_light_19_enabled"));
        groupCheck_single_trap_light_19_enabled->setCheckable(true);
        gridLayout_single_trap_light_19 = new QGridLayout(groupCheck_single_trap_light_19_enabled);
        gridLayout_single_trap_light_19->setSpacing(2);
        gridLayout_single_trap_light_19->setObjectName(QString::fromUtf8("gridLayout_single_trap_light_19"));
        label_single_trap_light_19_shape = new QLabel(groupCheck_single_trap_light_19_enabled);
        label_single_trap_light_19_shape->setObjectName(QString::fromUtf8("label_single_trap_light_19_shape"));

        gridLayout_single_trap_light_19->addWidget(label_single_trap_light_19_shape, 0, 0, 1, 1);

        comboBox_single_trap_light_19_shape = new MyComboBox(groupCheck_single_trap_light_19_enabled);
        comboBox_single_trap_light_19_shape->addItem(QString());
        comboBox_single_trap_light_19_shape->addItem(QString());
        comboBox_single_trap_light_19_shape->addItem(QString());
        comboBox_single_trap_light_19_shape->addItem(QString());
        comboBox_single_trap_light_19_shape->addItem(QString());
        comboBox_single_trap_light_19_shape->addItem(QString());
        comboBox_single_trap_light_19_shape->addItem(QString());
        comboBox_single_trap_light_19_shape->addItem(QString());
        comboBox_single_trap_light_19_shape->addItem(QString());
        comboBox_single_trap_light_19_shape->addItem(QString());
        comboBox_single_trap_light_19_shape->addItem(QString());
        comboBox_single_trap_light_19_shape->addItem(QString());
        comboBox_single_trap_light_19_shape->addItem(QString());
        comboBox_single_trap_light_19_shape->addItem(QString());
        comboBox_single_trap_light_19_shape->setObjectName(QString::fromUtf8("comboBox_single_trap_light_19_shape"));

        gridLayout_single_trap_light_19->addWidget(comboBox_single_trap_light_19_shape, 0, 1, 1, 2);

        label_single_trap_light_19_position = new QLabel(groupCheck_single_trap_light_19_enabled);
        label_single_trap_light_19_position->setObjectName(QString::fromUtf8("label_single_trap_light_19_position"));

        gridLayout_single_trap_light_19->addWidget(label_single_trap_light_19_position, 1, 0, 1, 1);

        vect3_single_trap_light_19_position_x = new MyLineEdit(groupCheck_single_trap_light_19_enabled);
        vect3_single_trap_light_19_position_x->setObjectName(QString::fromUtf8("vect3_single_trap_light_19_position_x"));

        gridLayout_single_trap_light_19->addWidget(vect3_single_trap_light_19_position_x, 1, 1, 1, 1);

        vect3_single_trap_light_19_position_y = new MyLineEdit(groupCheck_single_trap_light_19_enabled);
        vect3_single_trap_light_19_position_y->setObjectName(QString::fromUtf8("vect3_single_trap_light_19_position_y"));

        gridLayout_single_trap_light_19->addWidget(vect3_single_trap_light_19_position_y, 1, 2, 1, 1);

        vect3_single_trap_light_19_position_z = new MyLineEdit(groupCheck_single_trap_light_19_enabled);
        vect3_single_trap_light_19_position_z->setObjectName(QString::fromUtf8("vect3_single_trap_light_19_position_z"));

        gridLayout_single_trap_light_19->addWidget(vect3_single_trap_light_19_position_z, 1, 3, 1, 1);

        pushButton_single_trap_light_19_place_camera = new QPushButton(groupCheck_single_trap_light_19_enabled);
        pushButton_single_trap_light_19_place_camera->setObjectName(QString::fromUtf8("pushButton_single_trap_light_19_place_camera"));

        gridLayout_single_trap_light_19->addWidget(pushButton_single_trap_light_19_place_camera, 1, 4, 1, 1);

        label_single_trap_light_19_size = new QLabel(groupCheck_single_trap_light_19_enabled);
        label_single_trap_light_19_size->setObjectName(QString::fromUtf8("label_single_trap_light_19_size"));

        gridLayout_single_trap_light_19->addWidget(label_single_trap_light_19_size, 2, 0, 1, 1);

        logedit_single_trap_light_19_size = new MyLineEdit(groupCheck_single_trap_light_19_enabled);
        logedit_single_trap_light_19_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_19_size"));

        gridLayout_single_trap_light_19->addWidget(logedit_single_trap_light_19_size, 2, 1, 1, 2);

        label_single_trap_light_19_size2 = new QLabel(groupCheck_single_trap_light_19_enabled);
        label_single_trap_light_19_size2->setObjectName(QString::fromUtf8("label_single_trap_light_19_size2"));

        gridLayout_single_trap_light_19->addWidget(label_single_trap_light_19_size2, 2, 3, 1, 1);

        logedit_single_trap_light_19_size2 = new MyLineEdit(groupCheck_single_trap_light_19_enabled);
        logedit_single_trap_light_19_size2->setObjectName(QString::fromUtf8("logedit_single_trap_light_19_size2"));

        gridLayout_single_trap_light_19->addWidget(logedit_single_trap_light_19_size2, 2, 4, 1, 1);

        label_single_trap_light_19_thickness = new QLabel(groupCheck_single_trap_light_19_enabled);
        label_single_trap_light_19_thickness->setObjectName(QString::fromUtf8("label_single_trap_light_19_thickness"));

        gridLayout_single_trap_light_19->addWidget(label_single_trap_light_19_thickness, 3, 0, 1, 1);

        logedit_single_trap_light_19_thickness = new MyLineEdit(groupCheck_single_trap_light_19_enabled);
        logedit_single_trap_light_19_thickness->setObjectName(QString::fromUtf8("logedit_single_trap_light_19_thickness"));

        gridLayout_single_trap_light_19->addWidget(logedit_single_trap_light_19_thickness, 3, 1, 1, 2);

        label_single_trap_light_19_rotation = new QLabel(groupCheck_single_trap_light_19_enabled);
        label_single_trap_light_19_rotation->setObjectName(QString::fromUtf8("label_single_trap_light_19_rotation"));

        gridLayout_single_trap_light_19->addWidget(label_single_trap_light_19_rotation, 4, 0, 1, 1);

        spinboxd3_single_trap_light_19_rotation_x = new MyDoubleSpinBox(groupCheck_single_trap_light_19_enabled);
        spinboxd3_single_trap_light_19_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_19_rotation_x"));

        gridLayout_single_trap_light_19->addWidget(spinboxd3_single_trap_light_19_rotation_x, 4, 1, 1, 1);

        spinboxd3_single_trap_light_19_rotation_y = new MyDoubleSpinBox(groupCheck_single_trap_light_19_enabled);
        spinboxd3_single_trap_light_19_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_19_rotation_y"));

        gridLayout_single_trap_light_19->addWidget(spinboxd3_single_trap_light_19_rotation_y, 4, 2, 1, 1);

        spinboxd3_single_trap_light_19_rotation_z = new MyDoubleSpinBox(groupCheck_single_trap_light_19_enabled);
        spinboxd3_single_trap_light_19_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_19_rotation_z"));

        gridLayout_single_trap_light_19->addWidget(spinboxd3_single_trap_light_19_rotation_z, 4, 3, 1, 1);

        label_single_trap_light_19_intensity = new QLabel(groupCheck_single_trap_light_19_enabled);
        label_single_trap_light_19_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_19_intensity"));

        gridLayout_single_trap_light_19->addWidget(label_single_trap_light_19_intensity, 5, 0, 1, 1);

        logedit_single_trap_light_19_intensity = new MyLineEdit(groupCheck_single_trap_light_19_enabled);
        logedit_single_trap_light_19_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_19_intensity"));

        gridLayout_single_trap_light_19->addWidget(logedit_single_trap_light_19_intensity, 5, 1, 1, 2);

        label_single_trap_light_19_color = new QLabel(groupCheck_single_trap_light_19_enabled);
        label_single_trap_light_19_color->setObjectName(QString::fromUtf8("label_single_trap_light_19_color"));

        gridLayout_single_trap_light_19->addWidget(label_single_trap_light_19_color, 6, 0, 1, 1);

        colorButton_single_trap_light_19_color = new MyColorButton(groupCheck_single_trap_light_19_enabled);
        colorButton_single_trap_light_19_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_19_color"));

        gridLayout_single_trap_light_19->addWidget(colorButton_single_trap_light_19_color, 6, 1, 1, 1);

        label_single_trap_light_19_gradient_color = new QLabel(groupCheck_single_trap_light_19_enabled);
        label_single_trap_light_19_gradient_color->setObjectName(QString::fromUtf8("label_single_trap_light_19_gradient_color"));

        gridLayout_single_trap_light_19->addWidget(label_single_trap_light_19_gradient_color, 6, 2, 1, 1);

        colorButton_single_trap_light_19_gradient_color = new MyColorButton(groupCheck_single_trap_light_19_enabled);
        colorButton_single_trap_light_19_gradient_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_19_gradient_color"));

        gridLayout_single_trap_light_19->addWidget(colorButton_single_trap_light_19_gradient_color, 6, 3, 1, 2);

        label_single_trap_light_19_visibility = new QLabel(groupCheck_single_trap_light_19_enabled);
        label_single_trap_light_19_visibility->setObjectName(QString::fromUtf8("label_single_trap_light_19_visibility"));

        gridLayout_single_trap_light_19->addWidget(label_single_trap_light_19_visibility, 7, 0, 1, 1);

        logedit_single_trap_light_19_visibility = new MyLineEdit(groupCheck_single_trap_light_19_enabled);
        logedit_single_trap_light_19_visibility->setObjectName(QString::fromUtf8("logedit_single_trap_light_19_visibility"));

        gridLayout_single_trap_light_19->addWidget(logedit_single_trap_light_19_visibility, 7, 1, 1, 2);

        label_single_trap_light_19_max_distance = new QLabel(groupCheck_single_trap_light_19_enabled);
        label_single_trap_light_19_max_distance->setObjectName(QString::fromUtf8("label_single_trap_light_19_max_distance"));

        gridLayout_single_trap_light_19->addWidget(label_single_trap_light_19_max_distance, 7, 3, 1, 1);

        logedit_single_trap_light_19_max_distance = new MyLineEdit(groupCheck_single_trap_light_19_enabled);
        logedit_single_trap_light_19_max_distance->setObjectName(QString::fromUtf8("logedit_single_trap_light_19_max_distance"));

        gridLayout_single_trap_light_19->addWidget(logedit_single_trap_light_19_max_distance, 7, 4, 1, 1);

        label_single_trap_light_19_sharpening = new QLabel(groupCheck_single_trap_light_19_enabled);
        label_single_trap_light_19_sharpening->setObjectName(QString::fromUtf8("label_single_trap_light_19_sharpening"));

        gridLayout_single_trap_light_19->addWidget(label_single_trap_light_19_sharpening, 8, 0, 1, 1);

        logedit_single_trap_light_19_sharpening = new MyLineEdit(groupCheck_single_trap_light_19_enabled);
        logedit_single_trap_light_19_sharpening->setObjectName(QString::fromUtf8("logedit_single_trap_light_19_sharpening"));

        gridLayout_single_trap_light_19->addWidget(logedit_single_trap_light_19_sharpening, 8, 1, 1, 2);

        label_single_trap_light_19_blur = new QLabel(groupCheck_single_trap_light_19_enabled);
        label_single_trap_light_19_blur->setObjectName(QString::fromUtf8("label_single_trap_light_19_blur"));

        gridLayout_single_trap_light_19->addWidget(label_single_trap_light_19_blur, 8, 3, 1, 1);

        logedit_single_trap_light_19_blur = new MyLineEdit(groupCheck_single_trap_light_19_enabled);
        logedit_single_trap_light_19_blur->setObjectName(QString::fromUtf8("logedit_single_trap_light_19_blur"));

        gridLayout_single_trap_light_19->addWidget(logedit_single_trap_light_19_blur, 8, 4, 1, 1);

        label_single_trap_light_19_solid_intensity = new QLabel(groupCheck_single_trap_light_19_enabled);
        label_single_trap_light_19_solid_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_19_solid_intensity"));

        gridLayout_single_trap_light_19->addWidget(label_single_trap_light_19_solid_intensity, 9, 0, 1, 1);

        logedit_single_trap_light_19_solid_intensity = new MyLineEdit(groupCheck_single_trap_light_19_enabled);
        logedit_single_trap_light_19_solid_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_19_solid_intensity"));

        gridLayout_single_trap_light_19->addWidget(logedit_single_trap_light_19_solid_intensity, 9, 1, 1, 2);

        label_single_trap_light_19_softness = new QLabel(groupCheck_single_trap_light_19_enabled);
        label_single_trap_light_19_softness->setObjectName(QString::fromUtf8("label_single_trap_light_19_softness"));

        gridLayout_single_trap_light_19->addWidget(label_single_trap_light_19_softness, 9, 3, 1, 1);

        logedit_single_trap_light_19_softness = new MyLineEdit(groupCheck_single_trap_light_19_enabled);
        logedit_single_trap_light_19_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_19_softness"));

        gridLayout_single_trap_light_19->addWidget(logedit_single_trap_light_19_softness, 9, 4, 1, 1);

        label_single_trap_light_19_relative_size = new QLabel(groupCheck_single_trap_light_19_enabled);
        label_single_trap_light_19_relative_size->setObjectName(QString::fromUtf8("label_single_trap_light_19_relative_size"));

        gridLayout_single_trap_light_19->addWidget(label_single_trap_light_19_relative_size, 10, 0, 1, 1);

        logedit_single_trap_light_19_relative_size = new MyLineEdit(groupCheck_single_trap_light_19_enabled);
        logedit_single_trap_light_19_relative_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_19_relative_size"));

        gridLayout_single_trap_light_19->addWidget(logedit_single_trap_light_19_relative_size, 10, 1, 1, 2);

        checkBox_single_trap_light_19_pre_transformed = new MyCheckBox(groupCheck_single_trap_light_19_enabled);
        checkBox_single_trap_light_19_pre_transformed->setObjectName(QString::fromUtf8("checkBox_single_trap_light_19_pre_transformed"));

        gridLayout_single_trap_light_19->addWidget(checkBox_single_trap_light_19_pre_transformed, 11, 0, 1, 1);

        label_single_trap_light_19_position_mode = new QLabel(groupCheck_single_trap_light_19_enabled);
        label_single_trap_light_19_position_mode->setObjectName(QString::fromUtf8("label_single_trap_light_19_position_mode"));

        gridLayout_single_trap_light_19->addWidget(label_single_trap_light_19_position_mode, 12, 0, 1, 1);

        comboBox_single_trap_light_19_position_mode = new MyComboBox(groupCheck_single_trap_light_19_enabled);
        comboBox_single_trap_light_19_position_mode->addItem(QString());
        comboBox_single_trap_light_19_position_mode->addItem(QString());
        comboBox_single_trap_light_19_position_mode->addItem(QString());
        comboBox_single_trap_light_19_position_mode->addItem(QString());
        comboBox_single_trap_light_19_position_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_19_position_mode"));

        gridLayout_single_trap_light_19->addWidget(comboBox_single_trap_light_19_position_mode, 12, 1, 1, 2);

        label_single_trap_light_19_coloring_mode = new QLabel(groupCheck_single_trap_light_19_enabled);
        label_single_trap_light_19_coloring_mode->setObjectName(QString::fromUtf8("label_single_trap_light_19_coloring_mode"));

        gridLayout_single_trap_light_19->addWidget(label_single_trap_light_19_coloring_mode, 13, 0, 1, 1);

        comboBox_single_trap_light_19_coloring_mode = new MyComboBox(groupCheck_single_trap_light_19_enabled);
        comboBox_single_trap_light_19_coloring_mode->addItem(QString());
        comboBox_single_trap_light_19_coloring_mode->addItem(QString());
        comboBox_single_trap_light_19_coloring_mode->addItem(QString());
        comboBox_single_trap_light_19_coloring_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_19_coloring_mode"));

        gridLayout_single_trap_light_19->addWidget(comboBox_single_trap_light_19_coloring_mode, 13, 1, 1, 2);

        label_single_trap_light_19_falloff_type = new QLabel(groupCheck_single_trap_light_19_enabled);
        label_single_trap_light_19_falloff_type->setObjectName(QString::fromUtf8("label_single_trap_light_19_falloff_type"));

        gridLayout_single_trap_light_19->addWidget(label_single_trap_light_19_falloff_type, 14, 0, 1, 1);

        comboBox_single_trap_light_19_falloff_type = new MyComboBox(groupCheck_single_trap_light_19_enabled);
        comboBox_single_trap_light_19_falloff_type->addItem(QString());
        comboBox_single_trap_light_19_falloff_type->addItem(QString());
        comboBox_single_trap_light_19_falloff_type->addItem(QString());
        comboBox_single_trap_light_19_falloff_type->addItem(QString());
        comboBox_single_trap_light_19_falloff_type->addItem(QString());
        comboBox_single_trap_light_19_falloff_type->setObjectName(QString::fromUtf8("comboBox_single_trap_light_19_falloff_type"));

        gridLayout_single_trap_light_19->addWidget(comboBox_single_trap_light_19_falloff_type, 14, 1, 1, 2);

        label_single_trap_light_19_edge_softness = new QLabel(groupCheck_single_trap_light_19_enabled);
        label_single_trap_light_19_edge_softness->setObjectName(QString::fromUtf8("label_single_trap_light_19_edge_softness"));

        gridLayout_single_trap_light_19->addWidget(label_single_trap_light_19_edge_softness, 15, 0, 1, 1);

        logedit_single_trap_light_19_edge_softness = new MyLineEdit(groupCheck_single_trap_light_19_enabled);
        logedit_single_trap_light_19_edge_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_19_edge_softness"));

        gridLayout_single_trap_light_19->addWidget(logedit_single_trap_light_19_edge_softness, 15, 1, 1, 2);

        label_single_trap_light_19_anim_orbit_radius = new QLabel(groupCheck_single_trap_light_19_enabled);
        label_single_trap_light_19_anim_orbit_radius->setObjectName(QString::fromUtf8("label_single_trap_light_19_anim_orbit_radius"));

        gridLayout_single_trap_light_19->addWidget(label_single_trap_light_19_anim_orbit_radius, 16, 0, 1, 1);

        logedit_single_trap_light_19_anim_orbit_radius = new MyLineEdit(groupCheck_single_trap_light_19_enabled);
        logedit_single_trap_light_19_anim_orbit_radius->setObjectName(QString::fromUtf8("logedit_single_trap_light_19_anim_orbit_radius"));

        gridLayout_single_trap_light_19->addWidget(logedit_single_trap_light_19_anim_orbit_radius, 16, 1, 1, 1);

        logedit_single_trap_light_19_anim_orbit_speed = new MyLineEdit(groupCheck_single_trap_light_19_enabled);
        logedit_single_trap_light_19_anim_orbit_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_19_anim_orbit_speed"));

        gridLayout_single_trap_light_19->addWidget(logedit_single_trap_light_19_anim_orbit_speed, 16, 2, 1, 1);

        logedit_single_trap_light_19_anim_pulsate_speed = new MyLineEdit(groupCheck_single_trap_light_19_enabled);
        logedit_single_trap_light_19_anim_pulsate_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_19_anim_pulsate_speed"));

        gridLayout_single_trap_light_19->addWidget(logedit_single_trap_light_19_anim_pulsate_speed, 16, 3, 1, 1);

        logedit_single_trap_light_19_anim_pulsate_amount = new MyLineEdit(groupCheck_single_trap_light_19_enabled);
        logedit_single_trap_light_19_anim_pulsate_amount->setObjectName(QString::fromUtf8("logedit_single_trap_light_19_anim_pulsate_amount"));

        gridLayout_single_trap_light_19->addWidget(logedit_single_trap_light_19_anim_pulsate_amount, 16, 4, 1, 1);

        pushButton_single_trap_light_19_place_surface = new QPushButton(groupCheck_single_trap_light_19_enabled);
        pushButton_single_trap_light_19_place_surface->setObjectName(QString::fromUtf8("pushButton_single_trap_light_19_place_surface"));

        gridLayout_single_trap_light_19->addWidget(pushButton_single_trap_light_19_place_surface, 17, 0, 1, 5);

        pushButton_single_trap_light_19_place_target = new QPushButton(groupCheck_single_trap_light_19_enabled);
        pushButton_single_trap_light_19_place_target->setObjectName(QString::fromUtf8("pushButton_single_trap_light_19_place_target"));

        gridLayout_single_trap_light_19->addWidget(pushButton_single_trap_light_19_place_target, 18, 0, 1, 5);


        verticalLayout_single_trap_layers->addWidget(groupCheck_single_trap_light_19_enabled);

        groupCheck_single_trap_light_20_enabled = new MyGroupBox(scrollAreaWidgetContents_single_trap);
        groupCheck_single_trap_light_20_enabled->setObjectName(QString::fromUtf8("groupCheck_single_trap_light_20_enabled"));
        groupCheck_single_trap_light_20_enabled->setCheckable(true);
        gridLayout_single_trap_light_20 = new QGridLayout(groupCheck_single_trap_light_20_enabled);
        gridLayout_single_trap_light_20->setSpacing(2);
        gridLayout_single_trap_light_20->setObjectName(QString::fromUtf8("gridLayout_single_trap_light_20"));
        label_single_trap_light_20_shape = new QLabel(groupCheck_single_trap_light_20_enabled);
        label_single_trap_light_20_shape->setObjectName(QString::fromUtf8("label_single_trap_light_20_shape"));

        gridLayout_single_trap_light_20->addWidget(label_single_trap_light_20_shape, 0, 0, 1, 1);

        comboBox_single_trap_light_20_shape = new MyComboBox(groupCheck_single_trap_light_20_enabled);
        comboBox_single_trap_light_20_shape->addItem(QString());
        comboBox_single_trap_light_20_shape->addItem(QString());
        comboBox_single_trap_light_20_shape->addItem(QString());
        comboBox_single_trap_light_20_shape->addItem(QString());
        comboBox_single_trap_light_20_shape->addItem(QString());
        comboBox_single_trap_light_20_shape->addItem(QString());
        comboBox_single_trap_light_20_shape->addItem(QString());
        comboBox_single_trap_light_20_shape->addItem(QString());
        comboBox_single_trap_light_20_shape->addItem(QString());
        comboBox_single_trap_light_20_shape->addItem(QString());
        comboBox_single_trap_light_20_shape->addItem(QString());
        comboBox_single_trap_light_20_shape->addItem(QString());
        comboBox_single_trap_light_20_shape->addItem(QString());
        comboBox_single_trap_light_20_shape->addItem(QString());
        comboBox_single_trap_light_20_shape->setObjectName(QString::fromUtf8("comboBox_single_trap_light_20_shape"));

        gridLayout_single_trap_light_20->addWidget(comboBox_single_trap_light_20_shape, 0, 1, 1, 2);

        label_single_trap_light_20_position = new QLabel(groupCheck_single_trap_light_20_enabled);
        label_single_trap_light_20_position->setObjectName(QString::fromUtf8("label_single_trap_light_20_position"));

        gridLayout_single_trap_light_20->addWidget(label_single_trap_light_20_position, 1, 0, 1, 1);

        vect3_single_trap_light_20_position_x = new MyLineEdit(groupCheck_single_trap_light_20_enabled);
        vect3_single_trap_light_20_position_x->setObjectName(QString::fromUtf8("vect3_single_trap_light_20_position_x"));

        gridLayout_single_trap_light_20->addWidget(vect3_single_trap_light_20_position_x, 1, 1, 1, 1);

        vect3_single_trap_light_20_position_y = new MyLineEdit(groupCheck_single_trap_light_20_enabled);
        vect3_single_trap_light_20_position_y->setObjectName(QString::fromUtf8("vect3_single_trap_light_20_position_y"));

        gridLayout_single_trap_light_20->addWidget(vect3_single_trap_light_20_position_y, 1, 2, 1, 1);

        vect3_single_trap_light_20_position_z = new MyLineEdit(groupCheck_single_trap_light_20_enabled);
        vect3_single_trap_light_20_position_z->setObjectName(QString::fromUtf8("vect3_single_trap_light_20_position_z"));

        gridLayout_single_trap_light_20->addWidget(vect3_single_trap_light_20_position_z, 1, 3, 1, 1);

        pushButton_single_trap_light_20_place_camera = new QPushButton(groupCheck_single_trap_light_20_enabled);
        pushButton_single_trap_light_20_place_camera->setObjectName(QString::fromUtf8("pushButton_single_trap_light_20_place_camera"));

        gridLayout_single_trap_light_20->addWidget(pushButton_single_trap_light_20_place_camera, 1, 4, 1, 1);

        label_single_trap_light_20_size = new QLabel(groupCheck_single_trap_light_20_enabled);
        label_single_trap_light_20_size->setObjectName(QString::fromUtf8("label_single_trap_light_20_size"));

        gridLayout_single_trap_light_20->addWidget(label_single_trap_light_20_size, 2, 0, 1, 1);

        logedit_single_trap_light_20_size = new MyLineEdit(groupCheck_single_trap_light_20_enabled);
        logedit_single_trap_light_20_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_20_size"));

        gridLayout_single_trap_light_20->addWidget(logedit_single_trap_light_20_size, 2, 1, 1, 2);

        label_single_trap_light_20_size2 = new QLabel(groupCheck_single_trap_light_20_enabled);
        label_single_trap_light_20_size2->setObjectName(QString::fromUtf8("label_single_trap_light_20_size2"));

        gridLayout_single_trap_light_20->addWidget(label_single_trap_light_20_size2, 2, 3, 1, 1);

        logedit_single_trap_light_20_size2 = new MyLineEdit(groupCheck_single_trap_light_20_enabled);
        logedit_single_trap_light_20_size2->setObjectName(QString::fromUtf8("logedit_single_trap_light_20_size2"));

        gridLayout_single_trap_light_20->addWidget(logedit_single_trap_light_20_size2, 2, 4, 1, 1);

        label_single_trap_light_20_thickness = new QLabel(groupCheck_single_trap_light_20_enabled);
        label_single_trap_light_20_thickness->setObjectName(QString::fromUtf8("label_single_trap_light_20_thickness"));

        gridLayout_single_trap_light_20->addWidget(label_single_trap_light_20_thickness, 3, 0, 1, 1);

        logedit_single_trap_light_20_thickness = new MyLineEdit(groupCheck_single_trap_light_20_enabled);
        logedit_single_trap_light_20_thickness->setObjectName(QString::fromUtf8("logedit_single_trap_light_20_thickness"));

        gridLayout_single_trap_light_20->addWidget(logedit_single_trap_light_20_thickness, 3, 1, 1, 2);

        label_single_trap_light_20_rotation = new QLabel(groupCheck_single_trap_light_20_enabled);
        label_single_trap_light_20_rotation->setObjectName(QString::fromUtf8("label_single_trap_light_20_rotation"));

        gridLayout_single_trap_light_20->addWidget(label_single_trap_light_20_rotation, 4, 0, 1, 1);

        spinboxd3_single_trap_light_20_rotation_x = new MyDoubleSpinBox(groupCheck_single_trap_light_20_enabled);
        spinboxd3_single_trap_light_20_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_20_rotation_x"));

        gridLayout_single_trap_light_20->addWidget(spinboxd3_single_trap_light_20_rotation_x, 4, 1, 1, 1);

        spinboxd3_single_trap_light_20_rotation_y = new MyDoubleSpinBox(groupCheck_single_trap_light_20_enabled);
        spinboxd3_single_trap_light_20_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_20_rotation_y"));

        gridLayout_single_trap_light_20->addWidget(spinboxd3_single_trap_light_20_rotation_y, 4, 2, 1, 1);

        spinboxd3_single_trap_light_20_rotation_z = new MyDoubleSpinBox(groupCheck_single_trap_light_20_enabled);
        spinboxd3_single_trap_light_20_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_single_trap_light_20_rotation_z"));

        gridLayout_single_trap_light_20->addWidget(spinboxd3_single_trap_light_20_rotation_z, 4, 3, 1, 1);

        label_single_trap_light_20_intensity = new QLabel(groupCheck_single_trap_light_20_enabled);
        label_single_trap_light_20_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_20_intensity"));

        gridLayout_single_trap_light_20->addWidget(label_single_trap_light_20_intensity, 5, 0, 1, 1);

        logedit_single_trap_light_20_intensity = new MyLineEdit(groupCheck_single_trap_light_20_enabled);
        logedit_single_trap_light_20_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_20_intensity"));

        gridLayout_single_trap_light_20->addWidget(logedit_single_trap_light_20_intensity, 5, 1, 1, 2);

        label_single_trap_light_20_color = new QLabel(groupCheck_single_trap_light_20_enabled);
        label_single_trap_light_20_color->setObjectName(QString::fromUtf8("label_single_trap_light_20_color"));

        gridLayout_single_trap_light_20->addWidget(label_single_trap_light_20_color, 6, 0, 1, 1);

        colorButton_single_trap_light_20_color = new MyColorButton(groupCheck_single_trap_light_20_enabled);
        colorButton_single_trap_light_20_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_20_color"));

        gridLayout_single_trap_light_20->addWidget(colorButton_single_trap_light_20_color, 6, 1, 1, 1);

        label_single_trap_light_20_gradient_color = new QLabel(groupCheck_single_trap_light_20_enabled);
        label_single_trap_light_20_gradient_color->setObjectName(QString::fromUtf8("label_single_trap_light_20_gradient_color"));

        gridLayout_single_trap_light_20->addWidget(label_single_trap_light_20_gradient_color, 6, 2, 1, 1);

        colorButton_single_trap_light_20_gradient_color = new MyColorButton(groupCheck_single_trap_light_20_enabled);
        colorButton_single_trap_light_20_gradient_color->setObjectName(QString::fromUtf8("colorButton_single_trap_light_20_gradient_color"));

        gridLayout_single_trap_light_20->addWidget(colorButton_single_trap_light_20_gradient_color, 6, 3, 1, 2);

        label_single_trap_light_20_visibility = new QLabel(groupCheck_single_trap_light_20_enabled);
        label_single_trap_light_20_visibility->setObjectName(QString::fromUtf8("label_single_trap_light_20_visibility"));

        gridLayout_single_trap_light_20->addWidget(label_single_trap_light_20_visibility, 7, 0, 1, 1);

        logedit_single_trap_light_20_visibility = new MyLineEdit(groupCheck_single_trap_light_20_enabled);
        logedit_single_trap_light_20_visibility->setObjectName(QString::fromUtf8("logedit_single_trap_light_20_visibility"));

        gridLayout_single_trap_light_20->addWidget(logedit_single_trap_light_20_visibility, 7, 1, 1, 2);

        label_single_trap_light_20_max_distance = new QLabel(groupCheck_single_trap_light_20_enabled);
        label_single_trap_light_20_max_distance->setObjectName(QString::fromUtf8("label_single_trap_light_20_max_distance"));

        gridLayout_single_trap_light_20->addWidget(label_single_trap_light_20_max_distance, 7, 3, 1, 1);

        logedit_single_trap_light_20_max_distance = new MyLineEdit(groupCheck_single_trap_light_20_enabled);
        logedit_single_trap_light_20_max_distance->setObjectName(QString::fromUtf8("logedit_single_trap_light_20_max_distance"));

        gridLayout_single_trap_light_20->addWidget(logedit_single_trap_light_20_max_distance, 7, 4, 1, 1);

        label_single_trap_light_20_sharpening = new QLabel(groupCheck_single_trap_light_20_enabled);
        label_single_trap_light_20_sharpening->setObjectName(QString::fromUtf8("label_single_trap_light_20_sharpening"));

        gridLayout_single_trap_light_20->addWidget(label_single_trap_light_20_sharpening, 8, 0, 1, 1);

        logedit_single_trap_light_20_sharpening = new MyLineEdit(groupCheck_single_trap_light_20_enabled);
        logedit_single_trap_light_20_sharpening->setObjectName(QString::fromUtf8("logedit_single_trap_light_20_sharpening"));

        gridLayout_single_trap_light_20->addWidget(logedit_single_trap_light_20_sharpening, 8, 1, 1, 2);

        label_single_trap_light_20_blur = new QLabel(groupCheck_single_trap_light_20_enabled);
        label_single_trap_light_20_blur->setObjectName(QString::fromUtf8("label_single_trap_light_20_blur"));

        gridLayout_single_trap_light_20->addWidget(label_single_trap_light_20_blur, 8, 3, 1, 1);

        logedit_single_trap_light_20_blur = new MyLineEdit(groupCheck_single_trap_light_20_enabled);
        logedit_single_trap_light_20_blur->setObjectName(QString::fromUtf8("logedit_single_trap_light_20_blur"));

        gridLayout_single_trap_light_20->addWidget(logedit_single_trap_light_20_blur, 8, 4, 1, 1);

        label_single_trap_light_20_solid_intensity = new QLabel(groupCheck_single_trap_light_20_enabled);
        label_single_trap_light_20_solid_intensity->setObjectName(QString::fromUtf8("label_single_trap_light_20_solid_intensity"));

        gridLayout_single_trap_light_20->addWidget(label_single_trap_light_20_solid_intensity, 9, 0, 1, 1);

        logedit_single_trap_light_20_solid_intensity = new MyLineEdit(groupCheck_single_trap_light_20_enabled);
        logedit_single_trap_light_20_solid_intensity->setObjectName(QString::fromUtf8("logedit_single_trap_light_20_solid_intensity"));

        gridLayout_single_trap_light_20->addWidget(logedit_single_trap_light_20_solid_intensity, 9, 1, 1, 2);

        label_single_trap_light_20_softness = new QLabel(groupCheck_single_trap_light_20_enabled);
        label_single_trap_light_20_softness->setObjectName(QString::fromUtf8("label_single_trap_light_20_softness"));

        gridLayout_single_trap_light_20->addWidget(label_single_trap_light_20_softness, 9, 3, 1, 1);

        logedit_single_trap_light_20_softness = new MyLineEdit(groupCheck_single_trap_light_20_enabled);
        logedit_single_trap_light_20_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_20_softness"));

        gridLayout_single_trap_light_20->addWidget(logedit_single_trap_light_20_softness, 9, 4, 1, 1);

        label_single_trap_light_20_relative_size = new QLabel(groupCheck_single_trap_light_20_enabled);
        label_single_trap_light_20_relative_size->setObjectName(QString::fromUtf8("label_single_trap_light_20_relative_size"));

        gridLayout_single_trap_light_20->addWidget(label_single_trap_light_20_relative_size, 10, 0, 1, 1);

        logedit_single_trap_light_20_relative_size = new MyLineEdit(groupCheck_single_trap_light_20_enabled);
        logedit_single_trap_light_20_relative_size->setObjectName(QString::fromUtf8("logedit_single_trap_light_20_relative_size"));

        gridLayout_single_trap_light_20->addWidget(logedit_single_trap_light_20_relative_size, 10, 1, 1, 2);

        checkBox_single_trap_light_20_pre_transformed = new MyCheckBox(groupCheck_single_trap_light_20_enabled);
        checkBox_single_trap_light_20_pre_transformed->setObjectName(QString::fromUtf8("checkBox_single_trap_light_20_pre_transformed"));

        gridLayout_single_trap_light_20->addWidget(checkBox_single_trap_light_20_pre_transformed, 11, 0, 1, 1);

        label_single_trap_light_20_position_mode = new QLabel(groupCheck_single_trap_light_20_enabled);
        label_single_trap_light_20_position_mode->setObjectName(QString::fromUtf8("label_single_trap_light_20_position_mode"));

        gridLayout_single_trap_light_20->addWidget(label_single_trap_light_20_position_mode, 12, 0, 1, 1);

        comboBox_single_trap_light_20_position_mode = new MyComboBox(groupCheck_single_trap_light_20_enabled);
        comboBox_single_trap_light_20_position_mode->addItem(QString());
        comboBox_single_trap_light_20_position_mode->addItem(QString());
        comboBox_single_trap_light_20_position_mode->addItem(QString());
        comboBox_single_trap_light_20_position_mode->addItem(QString());
        comboBox_single_trap_light_20_position_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_20_position_mode"));

        gridLayout_single_trap_light_20->addWidget(comboBox_single_trap_light_20_position_mode, 12, 1, 1, 2);

        label_single_trap_light_20_coloring_mode = new QLabel(groupCheck_single_trap_light_20_enabled);
        label_single_trap_light_20_coloring_mode->setObjectName(QString::fromUtf8("label_single_trap_light_20_coloring_mode"));

        gridLayout_single_trap_light_20->addWidget(label_single_trap_light_20_coloring_mode, 13, 0, 1, 1);

        comboBox_single_trap_light_20_coloring_mode = new MyComboBox(groupCheck_single_trap_light_20_enabled);
        comboBox_single_trap_light_20_coloring_mode->addItem(QString());
        comboBox_single_trap_light_20_coloring_mode->addItem(QString());
        comboBox_single_trap_light_20_coloring_mode->addItem(QString());
        comboBox_single_trap_light_20_coloring_mode->setObjectName(QString::fromUtf8("comboBox_single_trap_light_20_coloring_mode"));

        gridLayout_single_trap_light_20->addWidget(comboBox_single_trap_light_20_coloring_mode, 13, 1, 1, 2);

        label_single_trap_light_20_falloff_type = new QLabel(groupCheck_single_trap_light_20_enabled);
        label_single_trap_light_20_falloff_type->setObjectName(QString::fromUtf8("label_single_trap_light_20_falloff_type"));

        gridLayout_single_trap_light_20->addWidget(label_single_trap_light_20_falloff_type, 14, 0, 1, 1);

        comboBox_single_trap_light_20_falloff_type = new MyComboBox(groupCheck_single_trap_light_20_enabled);
        comboBox_single_trap_light_20_falloff_type->addItem(QString());
        comboBox_single_trap_light_20_falloff_type->addItem(QString());
        comboBox_single_trap_light_20_falloff_type->addItem(QString());
        comboBox_single_trap_light_20_falloff_type->addItem(QString());
        comboBox_single_trap_light_20_falloff_type->addItem(QString());
        comboBox_single_trap_light_20_falloff_type->setObjectName(QString::fromUtf8("comboBox_single_trap_light_20_falloff_type"));

        gridLayout_single_trap_light_20->addWidget(comboBox_single_trap_light_20_falloff_type, 14, 1, 1, 2);

        label_single_trap_light_20_edge_softness = new QLabel(groupCheck_single_trap_light_20_enabled);
        label_single_trap_light_20_edge_softness->setObjectName(QString::fromUtf8("label_single_trap_light_20_edge_softness"));

        gridLayout_single_trap_light_20->addWidget(label_single_trap_light_20_edge_softness, 15, 0, 1, 1);

        logedit_single_trap_light_20_edge_softness = new MyLineEdit(groupCheck_single_trap_light_20_enabled);
        logedit_single_trap_light_20_edge_softness->setObjectName(QString::fromUtf8("logedit_single_trap_light_20_edge_softness"));

        gridLayout_single_trap_light_20->addWidget(logedit_single_trap_light_20_edge_softness, 15, 1, 1, 2);

        label_single_trap_light_20_anim_orbit_radius = new QLabel(groupCheck_single_trap_light_20_enabled);
        label_single_trap_light_20_anim_orbit_radius->setObjectName(QString::fromUtf8("label_single_trap_light_20_anim_orbit_radius"));

        gridLayout_single_trap_light_20->addWidget(label_single_trap_light_20_anim_orbit_radius, 16, 0, 1, 1);

        logedit_single_trap_light_20_anim_orbit_radius = new MyLineEdit(groupCheck_single_trap_light_20_enabled);
        logedit_single_trap_light_20_anim_orbit_radius->setObjectName(QString::fromUtf8("logedit_single_trap_light_20_anim_orbit_radius"));

        gridLayout_single_trap_light_20->addWidget(logedit_single_trap_light_20_anim_orbit_radius, 16, 1, 1, 1);

        logedit_single_trap_light_20_anim_orbit_speed = new MyLineEdit(groupCheck_single_trap_light_20_enabled);
        logedit_single_trap_light_20_anim_orbit_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_20_anim_orbit_speed"));

        gridLayout_single_trap_light_20->addWidget(logedit_single_trap_light_20_anim_orbit_speed, 16, 2, 1, 1);

        logedit_single_trap_light_20_anim_pulsate_speed = new MyLineEdit(groupCheck_single_trap_light_20_enabled);
        logedit_single_trap_light_20_anim_pulsate_speed->setObjectName(QString::fromUtf8("logedit_single_trap_light_20_anim_pulsate_speed"));

        gridLayout_single_trap_light_20->addWidget(logedit_single_trap_light_20_anim_pulsate_speed, 16, 3, 1, 1);

        logedit_single_trap_light_20_anim_pulsate_amount = new MyLineEdit(groupCheck_single_trap_light_20_enabled);
        logedit_single_trap_light_20_anim_pulsate_amount->setObjectName(QString::fromUtf8("logedit_single_trap_light_20_anim_pulsate_amount"));

        gridLayout_single_trap_light_20->addWidget(logedit_single_trap_light_20_anim_pulsate_amount, 16, 4, 1, 1);

        pushButton_single_trap_light_20_place_surface = new QPushButton(groupCheck_single_trap_light_20_enabled);
        pushButton_single_trap_light_20_place_surface->setObjectName(QString::fromUtf8("pushButton_single_trap_light_20_place_surface"));

        gridLayout_single_trap_light_20->addWidget(pushButton_single_trap_light_20_place_surface, 17, 0, 1, 5);

        pushButton_single_trap_light_20_place_target = new QPushButton(groupCheck_single_trap_light_20_enabled);
        pushButton_single_trap_light_20_place_target->setObjectName(QString::fromUtf8("pushButton_single_trap_light_20_place_target"));

        gridLayout_single_trap_light_20->addWidget(pushButton_single_trap_light_20_place_target, 18, 0, 1, 5);


        verticalLayout_single_trap_layers->addWidget(groupCheck_single_trap_light_20_enabled);

        verticalSpacer_single_trap = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_single_trap_layers->addItem(verticalSpacer_single_trap);

        scrollArea_single_trap_layers->setWidget(scrollAreaWidgetContents_single_trap);

        verticalLayout_single_trap_master->addWidget(scrollArea_single_trap_layers);


        verticalLayout_single_trap_tab->addWidget(groupCheck_single_trap_lights_enabled);


        retranslateUi(cEffectsSingleTrapTab);

        QMetaObject::connectSlotsByName(cEffectsSingleTrapTab);
    } // setupUi

    void retranslateUi(QWidget *cEffectsSingleTrapTab)
    {
        pushButton_single_trap_load->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Laden", nullptr));
        pushButton_single_trap_save->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Opslaan", nullptr));
        groupCheck_single_trap_lights_enabled->setTitle(QCoreApplication::translate("cEffectsSingleTrapTab", "Ruimtelijke lampen \342\200\224 elke lamp heeft eigen positie en vorm (geen gekoppelde \302\253multi-trap\302\273)", nullptr));
        label_single_trap_active_count->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Max. actieve lampen:", nullptr));
#if QT_CONFIG(tooltip)
        label_single_trap_active_count->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Alleen lampen 1\342\200\246N worden berekend. Hogere nummers worden genegeerd; zet dit op minstens het hoogste lampnummer dat je gebruikt.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_single_trap_independent_hint->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Elke lamp staat los: vul bij \302\253Lamp 1\302\273 je bol (positie + randzachtheid), bij \302\253Lamp 2\302\273 je lijn (andere positie, groter = dikkere lijn, draai X/Y/Z = richting). Alleen \302\253Combineren\302\273 en \302\253Solo\302\273 be\303\257nvloeden hoe lampen in het beeld mengen \342\200\224 niet waar ze staan.", nullptr));
        groupBox_single_trap_tuning->setTitle(QCoreApplication::translate("cEffectsSingleTrapTab", "Beeld mengen (alleen samenvoeging)", nullptr));
#if QT_CONFIG(tooltip)
        groupBox_single_trap_tuning->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Solo: alleen \303\251\303\251n lamp tonen. Combineren: optellen of max per kanaal. Dit verandert niet de 3D-posities van de lampen.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_single_trap_solo_layer->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Solo lamp (0 = alle):", nullptr));
        label_single_trap_combine_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Combineren:", nullptr));
        label_single_trap_copy_from->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kopieer van:", nullptr));
        label_single_trap_copy_to->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "naar:", nullptr));
        pushButton_single_trap_copy->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kopieer", nullptr));
        label_single_trap_randomize_layer->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Doellamp #:", nullptr));
#if QT_CONFIG(tooltip)
        label_single_trap_randomize_layer->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Lampnummer voor \302\253Willekeurig\302\273 en \302\253Wereld-anker\302\273 (los van kopi\303\253ren van/tot).", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_single_trap_randomize->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Willekeurig Laag", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_randomize->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Willekeurige instellingen voor de laag gekozen bij \"Doellamp #\"", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_single_trap_world_anchor->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Wereld-anker", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_world_anchor->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Zet voor \302\253Doellamp #\302\273: absolute wereldpositie (positiemodus), geen pre-transform, relatieve schaal 1 \342\200\224 co\303\266rdinaten zijn het midden van de vorm. Daarna kun je X,Y,Z nauwkeurig invullen.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_single_trap_randomize_all->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Willekeurig Alle", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_randomize_all->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Willekeurige instellingen voor alle 20 lagen", nullptr));
#endif // QT_CONFIG(tooltip)
        label_single_trap_preset->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Preset:", nullptr));
        pushButton_single_trap_preset_refresh->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Ververs", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_preset_refresh->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Herlaad de lijst met presets uit de map", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_single_trap_preset_load->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Laden", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_preset_load->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Laad de geselecteerde preset", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_single_trap_preset_save->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Opslaan", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_preset_save->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Sla huidige Single Trap Lights instellingen op als preset", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_single_trap_reset_all->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Reset Alles", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_reset_all->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Zet alle lagen uit en terug naar standaardwaarden", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_single_trap_light_1_enabled->setTitle(QCoreApplication::translate("cEffectsSingleTrapTab", "Lamp 1 (eigen positie)", nullptr));
        label_single_trap_light_1_shape->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vorm:", nullptr));
        comboBox_single_trap_light_1_shape->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Punt", nullptr));
        comboBox_single_trap_light_1_shape->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Lijn", nullptr));
        comboBox_single_trap_light_1_shape->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Cirkel", nullptr));
        comboBox_single_trap_light_1_shape->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Vierkant", nullptr));
        comboBox_single_trap_light_1_shape->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Bol", nullptr));
        comboBox_single_trap_light_1_shape->setItemText(5, QCoreApplication::translate("cEffectsSingleTrapTab", "Kubus", nullptr));
        comboBox_single_trap_light_1_shape->setItemText(6, QCoreApplication::translate("cEffectsSingleTrapTab", "Torus", nullptr));
        comboBox_single_trap_light_1_shape->setItemText(7, QCoreApplication::translate("cEffectsSingleTrapTab", "Capsule", nullptr));
        comboBox_single_trap_light_1_shape->setItemText(8, QCoreApplication::translate("cEffectsSingleTrapTab", "Ring", nullptr));
        comboBox_single_trap_light_1_shape->setItemText(9, QCoreApplication::translate("cEffectsSingleTrapTab", "Ellips", nullptr));
        comboBox_single_trap_light_1_shape->setItemText(10, QCoreApplication::translate("cEffectsSingleTrapTab", "Kruis", nullptr));
        comboBox_single_trap_light_1_shape->setItemText(11, QCoreApplication::translate("cEffectsSingleTrapTab", "Cilinder", nullptr));
        comboBox_single_trap_light_1_shape->setItemText(12, QCoreApplication::translate("cEffectsSingleTrapTab", "Vlak", nullptr));
        comboBox_single_trap_light_1_shape->setItemText(13, QCoreApplication::translate("cEffectsSingleTrapTab", "Schijf", nullptr));

        label_single_trap_light_1_position->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Positie:", nullptr));
        pushButton_single_trap_light_1_place_camera->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats bij Camera", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_light_1_place_camera->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats licht op huidige camera positie", nullptr));
#endif // QT_CONFIG(tooltip)
        label_single_trap_light_1_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte:", nullptr));
        label_single_trap_light_1_size2->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte2:", nullptr));
        label_single_trap_light_1_thickness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Gloed:", nullptr));
        label_single_trap_light_1_rotation->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rotatie:", nullptr));
        label_single_trap_light_1_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Intensiteit:", nullptr));
        label_single_trap_light_1_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleur:", nullptr));
        colorButton_single_trap_light_1_color->setText(QString());
        label_single_trap_light_1_gradient_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grad:", nullptr));
        colorButton_single_trap_light_1_gradient_color->setText(QString());
        label_single_trap_light_1_visibility->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zichtbaarheid:", nullptr));
        label_single_trap_light_1_max_distance->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Max Afstand:", nullptr));
        label_single_trap_light_1_sharpening->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Scherpte:", nullptr));
        label_single_trap_light_1_blur->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vervaging:", nullptr));
        label_single_trap_light_1_solid_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Soliditeit:", nullptr));
        label_single_trap_light_1_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zachtheid:", nullptr));
        label_single_trap_light_1_relative_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Relatieve grootte:", nullptr));
        checkBox_single_trap_light_1_pre_transformed->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Voor-getransformeerd", nullptr));
        label_single_trap_light_1_position_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Pos Modus:", nullptr));
        comboBox_single_trap_light_1_position_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Absoluut", nullptr));
        comboBox_single_trap_light_1_position_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan camera", nullptr));
        comboBox_single_trap_light_1_position_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan fractal midden", nullptr));
        comboBox_single_trap_light_1_position_mode->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan doel", nullptr));

        label_single_trap_light_1_coloring_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleuring:", nullptr));
        comboBox_single_trap_light_1_coloring_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Massief", nullptr));
        comboBox_single_trap_light_1_coloring_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Afstand gebaseerd", nullptr));
        comboBox_single_trap_light_1_coloring_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit val gebaseerd", nullptr));

        label_single_trap_light_1_falloff_type->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Afval:", nullptr));
        comboBox_single_trap_light_1_falloff_type->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Gaussiaans", nullptr));
        comboBox_single_trap_light_1_falloff_type->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Omgekeerd kwadraat", nullptr));
        comboBox_single_trap_light_1_falloff_type->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Lineair", nullptr));
        comboBox_single_trap_light_1_falloff_type->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Exponentieel", nullptr));
        comboBox_single_trap_light_1_falloff_type->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Smoothstep", nullptr));

        label_single_trap_light_1_edge_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rand zachtheid:", nullptr));
        label_single_trap_light_1_anim_orbit_radius->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_1_anim_orbit_radius->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit radius", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_1_anim_orbit_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_1_anim_pulsate_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_1_anim_pulsate_amount->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate amount", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_single_trap_light_1_place_surface->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Oppervlak", nullptr));
        pushButton_single_trap_light_1_place_target->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Doel", nullptr));
        groupCheck_single_trap_light_2_enabled->setTitle(QCoreApplication::translate("cEffectsSingleTrapTab", "Lamp 2 (eigen positie)", nullptr));
        label_single_trap_light_2_shape->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vorm:", nullptr));
        comboBox_single_trap_light_2_shape->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Punt", nullptr));
        comboBox_single_trap_light_2_shape->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Lijn", nullptr));
        comboBox_single_trap_light_2_shape->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Cirkel", nullptr));
        comboBox_single_trap_light_2_shape->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Vierkant", nullptr));
        comboBox_single_trap_light_2_shape->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Bol", nullptr));
        comboBox_single_trap_light_2_shape->setItemText(5, QCoreApplication::translate("cEffectsSingleTrapTab", "Kubus", nullptr));
        comboBox_single_trap_light_2_shape->setItemText(6, QCoreApplication::translate("cEffectsSingleTrapTab", "Torus", nullptr));
        comboBox_single_trap_light_2_shape->setItemText(7, QCoreApplication::translate("cEffectsSingleTrapTab", "Capsule", nullptr));
        comboBox_single_trap_light_2_shape->setItemText(8, QCoreApplication::translate("cEffectsSingleTrapTab", "Ring", nullptr));
        comboBox_single_trap_light_2_shape->setItemText(9, QCoreApplication::translate("cEffectsSingleTrapTab", "Ellips", nullptr));
        comboBox_single_trap_light_2_shape->setItemText(10, QCoreApplication::translate("cEffectsSingleTrapTab", "Kruis", nullptr));
        comboBox_single_trap_light_2_shape->setItemText(11, QCoreApplication::translate("cEffectsSingleTrapTab", "Cilinder", nullptr));
        comboBox_single_trap_light_2_shape->setItemText(12, QCoreApplication::translate("cEffectsSingleTrapTab", "Vlak", nullptr));
        comboBox_single_trap_light_2_shape->setItemText(13, QCoreApplication::translate("cEffectsSingleTrapTab", "Schijf", nullptr));

        label_single_trap_light_2_position->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Positie:", nullptr));
        pushButton_single_trap_light_2_place_camera->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats bij Camera", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_light_2_place_camera->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats licht op huidige camera positie", nullptr));
#endif // QT_CONFIG(tooltip)
        label_single_trap_light_2_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte:", nullptr));
        label_single_trap_light_2_size2->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte2:", nullptr));
        label_single_trap_light_2_thickness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Gloed:", nullptr));
        label_single_trap_light_2_rotation->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rotatie:", nullptr));
        label_single_trap_light_2_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Intensiteit:", nullptr));
        label_single_trap_light_2_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleur:", nullptr));
        colorButton_single_trap_light_2_color->setText(QString());
        label_single_trap_light_2_gradient_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grad:", nullptr));
        colorButton_single_trap_light_2_gradient_color->setText(QString());
        label_single_trap_light_2_visibility->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zichtbaarheid:", nullptr));
        label_single_trap_light_2_max_distance->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Max Afstand:", nullptr));
        label_single_trap_light_2_sharpening->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Scherpte:", nullptr));
        label_single_trap_light_2_blur->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vervaging:", nullptr));
        label_single_trap_light_2_solid_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Soliditeit:", nullptr));
        label_single_trap_light_2_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zachtheid:", nullptr));
        label_single_trap_light_2_relative_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Relatieve grootte:", nullptr));
        checkBox_single_trap_light_2_pre_transformed->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Voor-getransformeerd", nullptr));
        label_single_trap_light_2_position_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Pos Modus:", nullptr));
        comboBox_single_trap_light_2_position_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Absoluut", nullptr));
        comboBox_single_trap_light_2_position_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan camera", nullptr));
        comboBox_single_trap_light_2_position_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan fractal midden", nullptr));
        comboBox_single_trap_light_2_position_mode->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan doel", nullptr));

        label_single_trap_light_2_coloring_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleuring:", nullptr));
        comboBox_single_trap_light_2_coloring_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Massief", nullptr));
        comboBox_single_trap_light_2_coloring_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Afstand gebaseerd", nullptr));
        comboBox_single_trap_light_2_coloring_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit val gebaseerd", nullptr));

        label_single_trap_light_2_falloff_type->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Afval:", nullptr));
        comboBox_single_trap_light_2_falloff_type->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Gaussiaans", nullptr));
        comboBox_single_trap_light_2_falloff_type->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Omgekeerd kwadraat", nullptr));
        comboBox_single_trap_light_2_falloff_type->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Lineair", nullptr));
        comboBox_single_trap_light_2_falloff_type->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Exponentieel", nullptr));
        comboBox_single_trap_light_2_falloff_type->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Smoothstep", nullptr));

        label_single_trap_light_2_edge_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rand zachtheid:", nullptr));
        label_single_trap_light_2_anim_orbit_radius->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_2_anim_orbit_radius->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit radius", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_2_anim_orbit_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_2_anim_pulsate_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_2_anim_pulsate_amount->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate amount", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_single_trap_light_2_place_surface->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Oppervlak", nullptr));
        pushButton_single_trap_light_2_place_target->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Doel", nullptr));
        groupCheck_single_trap_light_3_enabled->setTitle(QCoreApplication::translate("cEffectsSingleTrapTab", "Lamp 3 (eigen positie)", nullptr));
        label_single_trap_light_3_shape->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vorm:", nullptr));
        comboBox_single_trap_light_3_shape->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Punt", nullptr));
        comboBox_single_trap_light_3_shape->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Lijn", nullptr));
        comboBox_single_trap_light_3_shape->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Cirkel", nullptr));
        comboBox_single_trap_light_3_shape->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Vierkant", nullptr));
        comboBox_single_trap_light_3_shape->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Bol", nullptr));
        comboBox_single_trap_light_3_shape->setItemText(5, QCoreApplication::translate("cEffectsSingleTrapTab", "Kubus", nullptr));
        comboBox_single_trap_light_3_shape->setItemText(6, QCoreApplication::translate("cEffectsSingleTrapTab", "Torus", nullptr));
        comboBox_single_trap_light_3_shape->setItemText(7, QCoreApplication::translate("cEffectsSingleTrapTab", "Capsule", nullptr));
        comboBox_single_trap_light_3_shape->setItemText(8, QCoreApplication::translate("cEffectsSingleTrapTab", "Ring", nullptr));
        comboBox_single_trap_light_3_shape->setItemText(9, QCoreApplication::translate("cEffectsSingleTrapTab", "Ellips", nullptr));
        comboBox_single_trap_light_3_shape->setItemText(10, QCoreApplication::translate("cEffectsSingleTrapTab", "Kruis", nullptr));
        comboBox_single_trap_light_3_shape->setItemText(11, QCoreApplication::translate("cEffectsSingleTrapTab", "Cilinder", nullptr));
        comboBox_single_trap_light_3_shape->setItemText(12, QCoreApplication::translate("cEffectsSingleTrapTab", "Vlak", nullptr));
        comboBox_single_trap_light_3_shape->setItemText(13, QCoreApplication::translate("cEffectsSingleTrapTab", "Schijf", nullptr));

        label_single_trap_light_3_position->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Positie:", nullptr));
        pushButton_single_trap_light_3_place_camera->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats bij Camera", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_light_3_place_camera->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats licht op huidige camera positie", nullptr));
#endif // QT_CONFIG(tooltip)
        label_single_trap_light_3_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte:", nullptr));
        label_single_trap_light_3_size2->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte2:", nullptr));
        label_single_trap_light_3_thickness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Gloed:", nullptr));
        label_single_trap_light_3_rotation->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rotatie:", nullptr));
        label_single_trap_light_3_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Intensiteit:", nullptr));
        label_single_trap_light_3_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleur:", nullptr));
        colorButton_single_trap_light_3_color->setText(QString());
        label_single_trap_light_3_gradient_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grad:", nullptr));
        colorButton_single_trap_light_3_gradient_color->setText(QString());
        label_single_trap_light_3_visibility->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zichtbaarheid:", nullptr));
        label_single_trap_light_3_max_distance->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Max Afstand:", nullptr));
        label_single_trap_light_3_sharpening->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Scherpte:", nullptr));
        label_single_trap_light_3_blur->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vervaging:", nullptr));
        label_single_trap_light_3_solid_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Soliditeit:", nullptr));
        label_single_trap_light_3_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zachtheid:", nullptr));
        label_single_trap_light_3_relative_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Relatieve grootte:", nullptr));
        checkBox_single_trap_light_3_pre_transformed->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Voor-getransformeerd", nullptr));
        label_single_trap_light_3_position_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Pos Modus:", nullptr));
        comboBox_single_trap_light_3_position_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Absoluut", nullptr));
        comboBox_single_trap_light_3_position_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan camera", nullptr));
        comboBox_single_trap_light_3_position_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan fractal midden", nullptr));
        comboBox_single_trap_light_3_position_mode->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan doel", nullptr));

        label_single_trap_light_3_coloring_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleuring:", nullptr));
        comboBox_single_trap_light_3_coloring_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Massief", nullptr));
        comboBox_single_trap_light_3_coloring_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Afstand gebaseerd", nullptr));
        comboBox_single_trap_light_3_coloring_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit val gebaseerd", nullptr));

        label_single_trap_light_3_falloff_type->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Afval:", nullptr));
        comboBox_single_trap_light_3_falloff_type->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Gaussiaans", nullptr));
        comboBox_single_trap_light_3_falloff_type->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Omgekeerd kwadraat", nullptr));
        comboBox_single_trap_light_3_falloff_type->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Lineair", nullptr));
        comboBox_single_trap_light_3_falloff_type->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Exponentieel", nullptr));
        comboBox_single_trap_light_3_falloff_type->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Smoothstep", nullptr));

        label_single_trap_light_3_edge_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rand zachtheid:", nullptr));
        label_single_trap_light_3_anim_orbit_radius->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_3_anim_orbit_radius->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit radius", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_3_anim_orbit_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_3_anim_pulsate_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_3_anim_pulsate_amount->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate amount", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_single_trap_light_3_place_surface->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Oppervlak", nullptr));
        pushButton_single_trap_light_3_place_target->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Doel", nullptr));
        groupCheck_single_trap_light_4_enabled->setTitle(QCoreApplication::translate("cEffectsSingleTrapTab", "Lamp 4 (eigen positie)", nullptr));
        label_single_trap_light_4_shape->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vorm:", nullptr));
        comboBox_single_trap_light_4_shape->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Punt", nullptr));
        comboBox_single_trap_light_4_shape->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Lijn", nullptr));
        comboBox_single_trap_light_4_shape->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Cirkel", nullptr));
        comboBox_single_trap_light_4_shape->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Vierkant", nullptr));
        comboBox_single_trap_light_4_shape->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Bol", nullptr));
        comboBox_single_trap_light_4_shape->setItemText(5, QCoreApplication::translate("cEffectsSingleTrapTab", "Kubus", nullptr));
        comboBox_single_trap_light_4_shape->setItemText(6, QCoreApplication::translate("cEffectsSingleTrapTab", "Torus", nullptr));
        comboBox_single_trap_light_4_shape->setItemText(7, QCoreApplication::translate("cEffectsSingleTrapTab", "Capsule", nullptr));
        comboBox_single_trap_light_4_shape->setItemText(8, QCoreApplication::translate("cEffectsSingleTrapTab", "Ring", nullptr));
        comboBox_single_trap_light_4_shape->setItemText(9, QCoreApplication::translate("cEffectsSingleTrapTab", "Ellips", nullptr));
        comboBox_single_trap_light_4_shape->setItemText(10, QCoreApplication::translate("cEffectsSingleTrapTab", "Kruis", nullptr));
        comboBox_single_trap_light_4_shape->setItemText(11, QCoreApplication::translate("cEffectsSingleTrapTab", "Cilinder", nullptr));
        comboBox_single_trap_light_4_shape->setItemText(12, QCoreApplication::translate("cEffectsSingleTrapTab", "Vlak", nullptr));
        comboBox_single_trap_light_4_shape->setItemText(13, QCoreApplication::translate("cEffectsSingleTrapTab", "Schijf", nullptr));

        label_single_trap_light_4_position->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Positie:", nullptr));
        pushButton_single_trap_light_4_place_camera->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats bij Camera", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_light_4_place_camera->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats licht op huidige camera positie", nullptr));
#endif // QT_CONFIG(tooltip)
        label_single_trap_light_4_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte:", nullptr));
        label_single_trap_light_4_size2->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte2:", nullptr));
        label_single_trap_light_4_thickness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Gloed:", nullptr));
        label_single_trap_light_4_rotation->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rotatie:", nullptr));
        label_single_trap_light_4_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Intensiteit:", nullptr));
        label_single_trap_light_4_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleur:", nullptr));
        colorButton_single_trap_light_4_color->setText(QString());
        label_single_trap_light_4_gradient_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grad:", nullptr));
        colorButton_single_trap_light_4_gradient_color->setText(QString());
        label_single_trap_light_4_visibility->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zichtbaarheid:", nullptr));
        label_single_trap_light_4_max_distance->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Max Afstand:", nullptr));
        label_single_trap_light_4_sharpening->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Scherpte:", nullptr));
        label_single_trap_light_4_blur->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vervaging:", nullptr));
        label_single_trap_light_4_solid_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Soliditeit:", nullptr));
        label_single_trap_light_4_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zachtheid:", nullptr));
        label_single_trap_light_4_relative_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Relatieve grootte:", nullptr));
        checkBox_single_trap_light_4_pre_transformed->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Voor-getransformeerd", nullptr));
        label_single_trap_light_4_position_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Pos Modus:", nullptr));
        comboBox_single_trap_light_4_position_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Absoluut", nullptr));
        comboBox_single_trap_light_4_position_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan camera", nullptr));
        comboBox_single_trap_light_4_position_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan fractal midden", nullptr));
        comboBox_single_trap_light_4_position_mode->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan doel", nullptr));

        label_single_trap_light_4_coloring_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleuring:", nullptr));
        comboBox_single_trap_light_4_coloring_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Massief", nullptr));
        comboBox_single_trap_light_4_coloring_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Afstand gebaseerd", nullptr));
        comboBox_single_trap_light_4_coloring_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit val gebaseerd", nullptr));

        label_single_trap_light_4_falloff_type->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Afval:", nullptr));
        comboBox_single_trap_light_4_falloff_type->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Gaussiaans", nullptr));
        comboBox_single_trap_light_4_falloff_type->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Omgekeerd kwadraat", nullptr));
        comboBox_single_trap_light_4_falloff_type->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Lineair", nullptr));
        comboBox_single_trap_light_4_falloff_type->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Exponentieel", nullptr));
        comboBox_single_trap_light_4_falloff_type->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Smoothstep", nullptr));

        label_single_trap_light_4_edge_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rand zachtheid:", nullptr));
        label_single_trap_light_4_anim_orbit_radius->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_4_anim_orbit_radius->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit radius", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_4_anim_orbit_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_4_anim_pulsate_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_4_anim_pulsate_amount->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate amount", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_single_trap_light_4_place_surface->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Oppervlak", nullptr));
        pushButton_single_trap_light_4_place_target->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Doel", nullptr));
        groupCheck_single_trap_light_5_enabled->setTitle(QCoreApplication::translate("cEffectsSingleTrapTab", "Lamp 5 (eigen positie)", nullptr));
        label_single_trap_light_5_shape->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vorm:", nullptr));
        comboBox_single_trap_light_5_shape->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Punt", nullptr));
        comboBox_single_trap_light_5_shape->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Lijn", nullptr));
        comboBox_single_trap_light_5_shape->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Cirkel", nullptr));
        comboBox_single_trap_light_5_shape->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Vierkant", nullptr));
        comboBox_single_trap_light_5_shape->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Bol", nullptr));
        comboBox_single_trap_light_5_shape->setItemText(5, QCoreApplication::translate("cEffectsSingleTrapTab", "Kubus", nullptr));
        comboBox_single_trap_light_5_shape->setItemText(6, QCoreApplication::translate("cEffectsSingleTrapTab", "Torus", nullptr));
        comboBox_single_trap_light_5_shape->setItemText(7, QCoreApplication::translate("cEffectsSingleTrapTab", "Capsule", nullptr));
        comboBox_single_trap_light_5_shape->setItemText(8, QCoreApplication::translate("cEffectsSingleTrapTab", "Ring", nullptr));
        comboBox_single_trap_light_5_shape->setItemText(9, QCoreApplication::translate("cEffectsSingleTrapTab", "Ellips", nullptr));
        comboBox_single_trap_light_5_shape->setItemText(10, QCoreApplication::translate("cEffectsSingleTrapTab", "Kruis", nullptr));
        comboBox_single_trap_light_5_shape->setItemText(11, QCoreApplication::translate("cEffectsSingleTrapTab", "Cilinder", nullptr));
        comboBox_single_trap_light_5_shape->setItemText(12, QCoreApplication::translate("cEffectsSingleTrapTab", "Vlak", nullptr));
        comboBox_single_trap_light_5_shape->setItemText(13, QCoreApplication::translate("cEffectsSingleTrapTab", "Schijf", nullptr));

        label_single_trap_light_5_position->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Positie:", nullptr));
        pushButton_single_trap_light_5_place_camera->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats bij Camera", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_light_5_place_camera->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats licht op huidige camera positie", nullptr));
#endif // QT_CONFIG(tooltip)
        label_single_trap_light_5_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte:", nullptr));
        label_single_trap_light_5_size2->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte2:", nullptr));
        label_single_trap_light_5_thickness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Gloed:", nullptr));
        label_single_trap_light_5_rotation->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rotatie:", nullptr));
        label_single_trap_light_5_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Intensiteit:", nullptr));
        label_single_trap_light_5_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleur:", nullptr));
        colorButton_single_trap_light_5_color->setText(QString());
        label_single_trap_light_5_gradient_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grad:", nullptr));
        colorButton_single_trap_light_5_gradient_color->setText(QString());
        label_single_trap_light_5_visibility->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zichtbaarheid:", nullptr));
        label_single_trap_light_5_max_distance->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Max Afstand:", nullptr));
        label_single_trap_light_5_sharpening->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Scherpte:", nullptr));
        label_single_trap_light_5_blur->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vervaging:", nullptr));
        label_single_trap_light_5_solid_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Soliditeit:", nullptr));
        label_single_trap_light_5_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zachtheid:", nullptr));
        label_single_trap_light_5_relative_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Relatieve grootte:", nullptr));
        checkBox_single_trap_light_5_pre_transformed->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Voor-getransformeerd", nullptr));
        label_single_trap_light_5_position_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Pos Modus:", nullptr));
        comboBox_single_trap_light_5_position_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Absoluut", nullptr));
        comboBox_single_trap_light_5_position_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan camera", nullptr));
        comboBox_single_trap_light_5_position_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan fractal midden", nullptr));
        comboBox_single_trap_light_5_position_mode->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan doel", nullptr));

        label_single_trap_light_5_coloring_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleuring:", nullptr));
        comboBox_single_trap_light_5_coloring_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Massief", nullptr));
        comboBox_single_trap_light_5_coloring_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Afstand gebaseerd", nullptr));
        comboBox_single_trap_light_5_coloring_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit val gebaseerd", nullptr));

        label_single_trap_light_5_falloff_type->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Afval:", nullptr));
        comboBox_single_trap_light_5_falloff_type->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Gaussiaans", nullptr));
        comboBox_single_trap_light_5_falloff_type->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Omgekeerd kwadraat", nullptr));
        comboBox_single_trap_light_5_falloff_type->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Lineair", nullptr));
        comboBox_single_trap_light_5_falloff_type->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Exponentieel", nullptr));
        comboBox_single_trap_light_5_falloff_type->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Smoothstep", nullptr));

        label_single_trap_light_5_edge_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rand zachtheid:", nullptr));
        label_single_trap_light_5_anim_orbit_radius->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_5_anim_orbit_radius->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit radius", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_5_anim_orbit_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_5_anim_pulsate_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_5_anim_pulsate_amount->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate amount", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_single_trap_light_5_place_surface->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Oppervlak", nullptr));
        pushButton_single_trap_light_5_place_target->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Doel", nullptr));
        groupCheck_single_trap_light_6_enabled->setTitle(QCoreApplication::translate("cEffectsSingleTrapTab", "Lamp 6 (eigen positie)", nullptr));
        label_single_trap_light_6_shape->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vorm:", nullptr));
        comboBox_single_trap_light_6_shape->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Punt", nullptr));
        comboBox_single_trap_light_6_shape->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Lijn", nullptr));
        comboBox_single_trap_light_6_shape->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Cirkel", nullptr));
        comboBox_single_trap_light_6_shape->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Vierkant", nullptr));
        comboBox_single_trap_light_6_shape->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Bol", nullptr));
        comboBox_single_trap_light_6_shape->setItemText(5, QCoreApplication::translate("cEffectsSingleTrapTab", "Kubus", nullptr));
        comboBox_single_trap_light_6_shape->setItemText(6, QCoreApplication::translate("cEffectsSingleTrapTab", "Torus", nullptr));
        comboBox_single_trap_light_6_shape->setItemText(7, QCoreApplication::translate("cEffectsSingleTrapTab", "Capsule", nullptr));
        comboBox_single_trap_light_6_shape->setItemText(8, QCoreApplication::translate("cEffectsSingleTrapTab", "Ring", nullptr));
        comboBox_single_trap_light_6_shape->setItemText(9, QCoreApplication::translate("cEffectsSingleTrapTab", "Ellips", nullptr));
        comboBox_single_trap_light_6_shape->setItemText(10, QCoreApplication::translate("cEffectsSingleTrapTab", "Kruis", nullptr));
        comboBox_single_trap_light_6_shape->setItemText(11, QCoreApplication::translate("cEffectsSingleTrapTab", "Cilinder", nullptr));
        comboBox_single_trap_light_6_shape->setItemText(12, QCoreApplication::translate("cEffectsSingleTrapTab", "Vlak", nullptr));
        comboBox_single_trap_light_6_shape->setItemText(13, QCoreApplication::translate("cEffectsSingleTrapTab", "Schijf", nullptr));

        label_single_trap_light_6_position->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Positie:", nullptr));
        pushButton_single_trap_light_6_place_camera->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats bij Camera", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_light_6_place_camera->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats licht op huidige camera positie", nullptr));
#endif // QT_CONFIG(tooltip)
        label_single_trap_light_6_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte:", nullptr));
        label_single_trap_light_6_size2->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte2:", nullptr));
        label_single_trap_light_6_thickness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Gloed:", nullptr));
        label_single_trap_light_6_rotation->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rotatie:", nullptr));
        label_single_trap_light_6_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Intensiteit:", nullptr));
        label_single_trap_light_6_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleur:", nullptr));
        colorButton_single_trap_light_6_color->setText(QString());
        label_single_trap_light_6_gradient_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grad:", nullptr));
        colorButton_single_trap_light_6_gradient_color->setText(QString());
        label_single_trap_light_6_visibility->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zichtbaarheid:", nullptr));
        label_single_trap_light_6_max_distance->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Max Afstand:", nullptr));
        label_single_trap_light_6_sharpening->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Scherpte:", nullptr));
        label_single_trap_light_6_blur->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vervaging:", nullptr));
        label_single_trap_light_6_solid_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Soliditeit:", nullptr));
        label_single_trap_light_6_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zachtheid:", nullptr));
        label_single_trap_light_6_relative_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Relatieve grootte:", nullptr));
        checkBox_single_trap_light_6_pre_transformed->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Voor-getransformeerd", nullptr));
        label_single_trap_light_6_position_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Pos Modus:", nullptr));
        comboBox_single_trap_light_6_position_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Absoluut", nullptr));
        comboBox_single_trap_light_6_position_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan camera", nullptr));
        comboBox_single_trap_light_6_position_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan fractal midden", nullptr));
        comboBox_single_trap_light_6_position_mode->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan doel", nullptr));

        label_single_trap_light_6_coloring_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleuring:", nullptr));
        comboBox_single_trap_light_6_coloring_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Massief", nullptr));
        comboBox_single_trap_light_6_coloring_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Afstand gebaseerd", nullptr));
        comboBox_single_trap_light_6_coloring_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit val gebaseerd", nullptr));

        label_single_trap_light_6_falloff_type->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Afval:", nullptr));
        comboBox_single_trap_light_6_falloff_type->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Gaussiaans", nullptr));
        comboBox_single_trap_light_6_falloff_type->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Omgekeerd kwadraat", nullptr));
        comboBox_single_trap_light_6_falloff_type->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Lineair", nullptr));
        comboBox_single_trap_light_6_falloff_type->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Exponentieel", nullptr));
        comboBox_single_trap_light_6_falloff_type->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Smoothstep", nullptr));

        label_single_trap_light_6_edge_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rand zachtheid:", nullptr));
        label_single_trap_light_6_anim_orbit_radius->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_6_anim_orbit_radius->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit radius", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_6_anim_orbit_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_6_anim_pulsate_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_6_anim_pulsate_amount->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate amount", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_single_trap_light_6_place_surface->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Oppervlak", nullptr));
        pushButton_single_trap_light_6_place_target->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Doel", nullptr));
        groupCheck_single_trap_light_7_enabled->setTitle(QCoreApplication::translate("cEffectsSingleTrapTab", "Lamp 7 (eigen positie)", nullptr));
        label_single_trap_light_7_shape->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vorm:", nullptr));
        comboBox_single_trap_light_7_shape->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Punt", nullptr));
        comboBox_single_trap_light_7_shape->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Lijn", nullptr));
        comboBox_single_trap_light_7_shape->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Cirkel", nullptr));
        comboBox_single_trap_light_7_shape->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Vierkant", nullptr));
        comboBox_single_trap_light_7_shape->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Bol", nullptr));
        comboBox_single_trap_light_7_shape->setItemText(5, QCoreApplication::translate("cEffectsSingleTrapTab", "Kubus", nullptr));
        comboBox_single_trap_light_7_shape->setItemText(6, QCoreApplication::translate("cEffectsSingleTrapTab", "Torus", nullptr));
        comboBox_single_trap_light_7_shape->setItemText(7, QCoreApplication::translate("cEffectsSingleTrapTab", "Capsule", nullptr));
        comboBox_single_trap_light_7_shape->setItemText(8, QCoreApplication::translate("cEffectsSingleTrapTab", "Ring", nullptr));
        comboBox_single_trap_light_7_shape->setItemText(9, QCoreApplication::translate("cEffectsSingleTrapTab", "Ellips", nullptr));
        comboBox_single_trap_light_7_shape->setItemText(10, QCoreApplication::translate("cEffectsSingleTrapTab", "Kruis", nullptr));
        comboBox_single_trap_light_7_shape->setItemText(11, QCoreApplication::translate("cEffectsSingleTrapTab", "Cilinder", nullptr));
        comboBox_single_trap_light_7_shape->setItemText(12, QCoreApplication::translate("cEffectsSingleTrapTab", "Vlak", nullptr));
        comboBox_single_trap_light_7_shape->setItemText(13, QCoreApplication::translate("cEffectsSingleTrapTab", "Schijf", nullptr));

        label_single_trap_light_7_position->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Positie:", nullptr));
        pushButton_single_trap_light_7_place_camera->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats bij Camera", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_light_7_place_camera->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats licht op huidige camera positie", nullptr));
#endif // QT_CONFIG(tooltip)
        label_single_trap_light_7_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte:", nullptr));
        label_single_trap_light_7_size2->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte2:", nullptr));
        label_single_trap_light_7_thickness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Gloed:", nullptr));
        label_single_trap_light_7_rotation->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rotatie:", nullptr));
        label_single_trap_light_7_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Intensiteit:", nullptr));
        label_single_trap_light_7_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleur:", nullptr));
        colorButton_single_trap_light_7_color->setText(QString());
        label_single_trap_light_7_gradient_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grad:", nullptr));
        colorButton_single_trap_light_7_gradient_color->setText(QString());
        label_single_trap_light_7_visibility->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zichtbaarheid:", nullptr));
        label_single_trap_light_7_max_distance->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Max Afstand:", nullptr));
        label_single_trap_light_7_sharpening->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Scherpte:", nullptr));
        label_single_trap_light_7_blur->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vervaging:", nullptr));
        label_single_trap_light_7_solid_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Soliditeit:", nullptr));
        label_single_trap_light_7_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zachtheid:", nullptr));
        label_single_trap_light_7_relative_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Relatieve grootte:", nullptr));
        checkBox_single_trap_light_7_pre_transformed->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Voor-getransformeerd", nullptr));
        label_single_trap_light_7_position_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Pos Modus:", nullptr));
        comboBox_single_trap_light_7_position_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Absoluut", nullptr));
        comboBox_single_trap_light_7_position_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan camera", nullptr));
        comboBox_single_trap_light_7_position_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan fractal midden", nullptr));
        comboBox_single_trap_light_7_position_mode->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan doel", nullptr));

        label_single_trap_light_7_coloring_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleuring:", nullptr));
        comboBox_single_trap_light_7_coloring_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Massief", nullptr));
        comboBox_single_trap_light_7_coloring_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Afstand gebaseerd", nullptr));
        comboBox_single_trap_light_7_coloring_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit val gebaseerd", nullptr));

        label_single_trap_light_7_falloff_type->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Afval:", nullptr));
        comboBox_single_trap_light_7_falloff_type->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Gaussiaans", nullptr));
        comboBox_single_trap_light_7_falloff_type->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Omgekeerd kwadraat", nullptr));
        comboBox_single_trap_light_7_falloff_type->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Lineair", nullptr));
        comboBox_single_trap_light_7_falloff_type->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Exponentieel", nullptr));
        comboBox_single_trap_light_7_falloff_type->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Smoothstep", nullptr));

        label_single_trap_light_7_edge_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rand zachtheid:", nullptr));
        label_single_trap_light_7_anim_orbit_radius->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_7_anim_orbit_radius->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit radius", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_7_anim_orbit_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_7_anim_pulsate_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_7_anim_pulsate_amount->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate amount", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_single_trap_light_7_place_surface->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Oppervlak", nullptr));
        pushButton_single_trap_light_7_place_target->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Doel", nullptr));
        groupCheck_single_trap_light_8_enabled->setTitle(QCoreApplication::translate("cEffectsSingleTrapTab", "Lamp 8 (eigen positie)", nullptr));
        label_single_trap_light_8_shape->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vorm:", nullptr));
        comboBox_single_trap_light_8_shape->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Punt", nullptr));
        comboBox_single_trap_light_8_shape->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Lijn", nullptr));
        comboBox_single_trap_light_8_shape->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Cirkel", nullptr));
        comboBox_single_trap_light_8_shape->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Vierkant", nullptr));
        comboBox_single_trap_light_8_shape->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Bol", nullptr));
        comboBox_single_trap_light_8_shape->setItemText(5, QCoreApplication::translate("cEffectsSingleTrapTab", "Kubus", nullptr));
        comboBox_single_trap_light_8_shape->setItemText(6, QCoreApplication::translate("cEffectsSingleTrapTab", "Torus", nullptr));
        comboBox_single_trap_light_8_shape->setItemText(7, QCoreApplication::translate("cEffectsSingleTrapTab", "Capsule", nullptr));
        comboBox_single_trap_light_8_shape->setItemText(8, QCoreApplication::translate("cEffectsSingleTrapTab", "Ring", nullptr));
        comboBox_single_trap_light_8_shape->setItemText(9, QCoreApplication::translate("cEffectsSingleTrapTab", "Ellips", nullptr));
        comboBox_single_trap_light_8_shape->setItemText(10, QCoreApplication::translate("cEffectsSingleTrapTab", "Kruis", nullptr));
        comboBox_single_trap_light_8_shape->setItemText(11, QCoreApplication::translate("cEffectsSingleTrapTab", "Cilinder", nullptr));
        comboBox_single_trap_light_8_shape->setItemText(12, QCoreApplication::translate("cEffectsSingleTrapTab", "Vlak", nullptr));
        comboBox_single_trap_light_8_shape->setItemText(13, QCoreApplication::translate("cEffectsSingleTrapTab", "Schijf", nullptr));

        label_single_trap_light_8_position->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Positie:", nullptr));
        pushButton_single_trap_light_8_place_camera->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats bij Camera", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_light_8_place_camera->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats licht op huidige camera positie", nullptr));
#endif // QT_CONFIG(tooltip)
        label_single_trap_light_8_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte:", nullptr));
        label_single_trap_light_8_size2->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte2:", nullptr));
        label_single_trap_light_8_thickness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Gloed:", nullptr));
        label_single_trap_light_8_rotation->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rotatie:", nullptr));
        label_single_trap_light_8_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Intensiteit:", nullptr));
        label_single_trap_light_8_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleur:", nullptr));
        colorButton_single_trap_light_8_color->setText(QString());
        label_single_trap_light_8_gradient_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grad:", nullptr));
        colorButton_single_trap_light_8_gradient_color->setText(QString());
        label_single_trap_light_8_visibility->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zichtbaarheid:", nullptr));
        label_single_trap_light_8_max_distance->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Max Afstand:", nullptr));
        label_single_trap_light_8_sharpening->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Scherpte:", nullptr));
        label_single_trap_light_8_blur->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vervaging:", nullptr));
        label_single_trap_light_8_solid_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Soliditeit:", nullptr));
        label_single_trap_light_8_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zachtheid:", nullptr));
        label_single_trap_light_8_relative_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Relatieve grootte:", nullptr));
        checkBox_single_trap_light_8_pre_transformed->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Voor-getransformeerd", nullptr));
        label_single_trap_light_8_position_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Pos Modus:", nullptr));
        comboBox_single_trap_light_8_position_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Absoluut", nullptr));
        comboBox_single_trap_light_8_position_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan camera", nullptr));
        comboBox_single_trap_light_8_position_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan fractal midden", nullptr));
        comboBox_single_trap_light_8_position_mode->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan doel", nullptr));

        label_single_trap_light_8_coloring_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleuring:", nullptr));
        comboBox_single_trap_light_8_coloring_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Massief", nullptr));
        comboBox_single_trap_light_8_coloring_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Afstand gebaseerd", nullptr));
        comboBox_single_trap_light_8_coloring_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit val gebaseerd", nullptr));

        label_single_trap_light_8_falloff_type->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Afval:", nullptr));
        comboBox_single_trap_light_8_falloff_type->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Gaussiaans", nullptr));
        comboBox_single_trap_light_8_falloff_type->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Omgekeerd kwadraat", nullptr));
        comboBox_single_trap_light_8_falloff_type->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Lineair", nullptr));
        comboBox_single_trap_light_8_falloff_type->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Exponentieel", nullptr));
        comboBox_single_trap_light_8_falloff_type->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Smoothstep", nullptr));

        label_single_trap_light_8_edge_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rand zachtheid:", nullptr));
        label_single_trap_light_8_anim_orbit_radius->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_8_anim_orbit_radius->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit radius", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_8_anim_orbit_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_8_anim_pulsate_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_8_anim_pulsate_amount->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate amount", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_single_trap_light_8_place_surface->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Oppervlak", nullptr));
        pushButton_single_trap_light_8_place_target->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Doel", nullptr));
        groupCheck_single_trap_light_9_enabled->setTitle(QCoreApplication::translate("cEffectsSingleTrapTab", "Lamp 9 (eigen positie)", nullptr));
        label_single_trap_light_9_shape->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vorm:", nullptr));
        comboBox_single_trap_light_9_shape->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Punt", nullptr));
        comboBox_single_trap_light_9_shape->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Lijn", nullptr));
        comboBox_single_trap_light_9_shape->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Cirkel", nullptr));
        comboBox_single_trap_light_9_shape->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Vierkant", nullptr));
        comboBox_single_trap_light_9_shape->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Bol", nullptr));
        comboBox_single_trap_light_9_shape->setItemText(5, QCoreApplication::translate("cEffectsSingleTrapTab", "Kubus", nullptr));
        comboBox_single_trap_light_9_shape->setItemText(6, QCoreApplication::translate("cEffectsSingleTrapTab", "Torus", nullptr));
        comboBox_single_trap_light_9_shape->setItemText(7, QCoreApplication::translate("cEffectsSingleTrapTab", "Capsule", nullptr));
        comboBox_single_trap_light_9_shape->setItemText(8, QCoreApplication::translate("cEffectsSingleTrapTab", "Ring", nullptr));
        comboBox_single_trap_light_9_shape->setItemText(9, QCoreApplication::translate("cEffectsSingleTrapTab", "Ellips", nullptr));
        comboBox_single_trap_light_9_shape->setItemText(10, QCoreApplication::translate("cEffectsSingleTrapTab", "Kruis", nullptr));
        comboBox_single_trap_light_9_shape->setItemText(11, QCoreApplication::translate("cEffectsSingleTrapTab", "Cilinder", nullptr));
        comboBox_single_trap_light_9_shape->setItemText(12, QCoreApplication::translate("cEffectsSingleTrapTab", "Vlak", nullptr));
        comboBox_single_trap_light_9_shape->setItemText(13, QCoreApplication::translate("cEffectsSingleTrapTab", "Schijf", nullptr));

        label_single_trap_light_9_position->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Positie:", nullptr));
        pushButton_single_trap_light_9_place_camera->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats bij Camera", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_light_9_place_camera->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats licht op huidige camera positie", nullptr));
#endif // QT_CONFIG(tooltip)
        label_single_trap_light_9_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte:", nullptr));
        label_single_trap_light_9_size2->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte2:", nullptr));
        label_single_trap_light_9_thickness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Gloed:", nullptr));
        label_single_trap_light_9_rotation->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rotatie:", nullptr));
        label_single_trap_light_9_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Intensiteit:", nullptr));
        label_single_trap_light_9_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleur:", nullptr));
        colorButton_single_trap_light_9_color->setText(QString());
        label_single_trap_light_9_gradient_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grad:", nullptr));
        colorButton_single_trap_light_9_gradient_color->setText(QString());
        label_single_trap_light_9_visibility->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zichtbaarheid:", nullptr));
        label_single_trap_light_9_max_distance->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Max Afstand:", nullptr));
        label_single_trap_light_9_sharpening->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Scherpte:", nullptr));
        label_single_trap_light_9_blur->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vervaging:", nullptr));
        label_single_trap_light_9_solid_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Soliditeit:", nullptr));
        label_single_trap_light_9_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zachtheid:", nullptr));
        label_single_trap_light_9_relative_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Relatieve grootte:", nullptr));
        checkBox_single_trap_light_9_pre_transformed->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Voor-getransformeerd", nullptr));
        label_single_trap_light_9_position_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Pos Modus:", nullptr));
        comboBox_single_trap_light_9_position_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Absoluut", nullptr));
        comboBox_single_trap_light_9_position_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan camera", nullptr));
        comboBox_single_trap_light_9_position_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan fractal midden", nullptr));
        comboBox_single_trap_light_9_position_mode->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan doel", nullptr));

        label_single_trap_light_9_coloring_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleuring:", nullptr));
        comboBox_single_trap_light_9_coloring_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Massief", nullptr));
        comboBox_single_trap_light_9_coloring_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Afstand gebaseerd", nullptr));
        comboBox_single_trap_light_9_coloring_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit val gebaseerd", nullptr));

        label_single_trap_light_9_falloff_type->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Afval:", nullptr));
        comboBox_single_trap_light_9_falloff_type->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Gaussiaans", nullptr));
        comboBox_single_trap_light_9_falloff_type->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Omgekeerd kwadraat", nullptr));
        comboBox_single_trap_light_9_falloff_type->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Lineair", nullptr));
        comboBox_single_trap_light_9_falloff_type->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Exponentieel", nullptr));
        comboBox_single_trap_light_9_falloff_type->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Smoothstep", nullptr));

        label_single_trap_light_9_edge_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rand zachtheid:", nullptr));
        label_single_trap_light_9_anim_orbit_radius->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_9_anim_orbit_radius->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit radius", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_9_anim_orbit_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_9_anim_pulsate_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_9_anim_pulsate_amount->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate amount", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_single_trap_light_9_place_surface->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Oppervlak", nullptr));
        pushButton_single_trap_light_9_place_target->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Doel", nullptr));
        groupCheck_single_trap_light_10_enabled->setTitle(QCoreApplication::translate("cEffectsSingleTrapTab", "Lamp 10 (eigen positie)", nullptr));
        label_single_trap_light_10_shape->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vorm:", nullptr));
        comboBox_single_trap_light_10_shape->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Punt", nullptr));
        comboBox_single_trap_light_10_shape->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Lijn", nullptr));
        comboBox_single_trap_light_10_shape->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Cirkel", nullptr));
        comboBox_single_trap_light_10_shape->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Vierkant", nullptr));
        comboBox_single_trap_light_10_shape->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Bol", nullptr));
        comboBox_single_trap_light_10_shape->setItemText(5, QCoreApplication::translate("cEffectsSingleTrapTab", "Kubus", nullptr));
        comboBox_single_trap_light_10_shape->setItemText(6, QCoreApplication::translate("cEffectsSingleTrapTab", "Torus", nullptr));
        comboBox_single_trap_light_10_shape->setItemText(7, QCoreApplication::translate("cEffectsSingleTrapTab", "Capsule", nullptr));
        comboBox_single_trap_light_10_shape->setItemText(8, QCoreApplication::translate("cEffectsSingleTrapTab", "Ring", nullptr));
        comboBox_single_trap_light_10_shape->setItemText(9, QCoreApplication::translate("cEffectsSingleTrapTab", "Ellips", nullptr));
        comboBox_single_trap_light_10_shape->setItemText(10, QCoreApplication::translate("cEffectsSingleTrapTab", "Kruis", nullptr));
        comboBox_single_trap_light_10_shape->setItemText(11, QCoreApplication::translate("cEffectsSingleTrapTab", "Cilinder", nullptr));
        comboBox_single_trap_light_10_shape->setItemText(12, QCoreApplication::translate("cEffectsSingleTrapTab", "Vlak", nullptr));
        comboBox_single_trap_light_10_shape->setItemText(13, QCoreApplication::translate("cEffectsSingleTrapTab", "Schijf", nullptr));

        label_single_trap_light_10_position->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Positie:", nullptr));
        pushButton_single_trap_light_10_place_camera->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats bij Camera", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_light_10_place_camera->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats licht op huidige camera positie", nullptr));
#endif // QT_CONFIG(tooltip)
        label_single_trap_light_10_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte:", nullptr));
        label_single_trap_light_10_size2->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte2:", nullptr));
        label_single_trap_light_10_thickness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Gloed:", nullptr));
        label_single_trap_light_10_rotation->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rotatie:", nullptr));
        label_single_trap_light_10_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Intensiteit:", nullptr));
        label_single_trap_light_10_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleur:", nullptr));
        colorButton_single_trap_light_10_color->setText(QString());
        label_single_trap_light_10_gradient_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grad:", nullptr));
        colorButton_single_trap_light_10_gradient_color->setText(QString());
        label_single_trap_light_10_visibility->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zichtbaarheid:", nullptr));
        label_single_trap_light_10_max_distance->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Max Afstand:", nullptr));
        label_single_trap_light_10_sharpening->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Scherpte:", nullptr));
        label_single_trap_light_10_blur->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vervaging:", nullptr));
        label_single_trap_light_10_solid_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Soliditeit:", nullptr));
        label_single_trap_light_10_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zachtheid:", nullptr));
        label_single_trap_light_10_relative_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Relatieve grootte:", nullptr));
        checkBox_single_trap_light_10_pre_transformed->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Voor-getransformeerd", nullptr));
        label_single_trap_light_10_position_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Pos Modus:", nullptr));
        comboBox_single_trap_light_10_position_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Absoluut", nullptr));
        comboBox_single_trap_light_10_position_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan camera", nullptr));
        comboBox_single_trap_light_10_position_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan fractal midden", nullptr));
        comboBox_single_trap_light_10_position_mode->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan doel", nullptr));

        label_single_trap_light_10_coloring_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleuring:", nullptr));
        comboBox_single_trap_light_10_coloring_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Massief", nullptr));
        comboBox_single_trap_light_10_coloring_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Afstand gebaseerd", nullptr));
        comboBox_single_trap_light_10_coloring_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit val gebaseerd", nullptr));

        label_single_trap_light_10_falloff_type->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Afval:", nullptr));
        comboBox_single_trap_light_10_falloff_type->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Gaussiaans", nullptr));
        comboBox_single_trap_light_10_falloff_type->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Omgekeerd kwadraat", nullptr));
        comboBox_single_trap_light_10_falloff_type->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Lineair", nullptr));
        comboBox_single_trap_light_10_falloff_type->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Exponentieel", nullptr));
        comboBox_single_trap_light_10_falloff_type->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Smoothstep", nullptr));

        label_single_trap_light_10_edge_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rand zachtheid:", nullptr));
        label_single_trap_light_10_anim_orbit_radius->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_10_anim_orbit_radius->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit radius", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_10_anim_orbit_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_10_anim_pulsate_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_10_anim_pulsate_amount->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate amount", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_single_trap_light_10_place_surface->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Oppervlak", nullptr));
        pushButton_single_trap_light_10_place_target->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Doel", nullptr));
        groupCheck_single_trap_light_11_enabled->setTitle(QCoreApplication::translate("cEffectsSingleTrapTab", "Lamp 11 (eigen positie)", nullptr));
        label_single_trap_light_11_shape->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vorm:", nullptr));
        comboBox_single_trap_light_11_shape->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Punt", nullptr));
        comboBox_single_trap_light_11_shape->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Lijn", nullptr));
        comboBox_single_trap_light_11_shape->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Cirkel", nullptr));
        comboBox_single_trap_light_11_shape->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Vierkant", nullptr));
        comboBox_single_trap_light_11_shape->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Bol", nullptr));
        comboBox_single_trap_light_11_shape->setItemText(5, QCoreApplication::translate("cEffectsSingleTrapTab", "Kubus", nullptr));
        comboBox_single_trap_light_11_shape->setItemText(6, QCoreApplication::translate("cEffectsSingleTrapTab", "Torus", nullptr));
        comboBox_single_trap_light_11_shape->setItemText(7, QCoreApplication::translate("cEffectsSingleTrapTab", "Capsule", nullptr));
        comboBox_single_trap_light_11_shape->setItemText(8, QCoreApplication::translate("cEffectsSingleTrapTab", "Ring", nullptr));
        comboBox_single_trap_light_11_shape->setItemText(9, QCoreApplication::translate("cEffectsSingleTrapTab", "Ellips", nullptr));
        comboBox_single_trap_light_11_shape->setItemText(10, QCoreApplication::translate("cEffectsSingleTrapTab", "Kruis", nullptr));
        comboBox_single_trap_light_11_shape->setItemText(11, QCoreApplication::translate("cEffectsSingleTrapTab", "Cilinder", nullptr));
        comboBox_single_trap_light_11_shape->setItemText(12, QCoreApplication::translate("cEffectsSingleTrapTab", "Vlak", nullptr));
        comboBox_single_trap_light_11_shape->setItemText(13, QCoreApplication::translate("cEffectsSingleTrapTab", "Schijf", nullptr));

        label_single_trap_light_11_position->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Positie:", nullptr));
        pushButton_single_trap_light_11_place_camera->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats bij Camera", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_light_11_place_camera->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats licht op huidige camera positie", nullptr));
#endif // QT_CONFIG(tooltip)
        label_single_trap_light_11_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte:", nullptr));
        label_single_trap_light_11_size2->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte2:", nullptr));
        label_single_trap_light_11_thickness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Gloed:", nullptr));
        label_single_trap_light_11_rotation->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rotatie:", nullptr));
        label_single_trap_light_11_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Intensiteit:", nullptr));
        label_single_trap_light_11_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleur:", nullptr));
        colorButton_single_trap_light_11_color->setText(QString());
        label_single_trap_light_11_gradient_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grad:", nullptr));
        colorButton_single_trap_light_11_gradient_color->setText(QString());
        label_single_trap_light_11_visibility->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zichtbaarheid:", nullptr));
        label_single_trap_light_11_max_distance->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Max Afstand:", nullptr));
        label_single_trap_light_11_sharpening->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Scherpte:", nullptr));
        label_single_trap_light_11_blur->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vervaging:", nullptr));
        label_single_trap_light_11_solid_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Soliditeit:", nullptr));
        label_single_trap_light_11_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zachtheid:", nullptr));
        label_single_trap_light_11_relative_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Relatieve grootte:", nullptr));
        checkBox_single_trap_light_11_pre_transformed->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Voor-getransformeerd", nullptr));
        label_single_trap_light_11_position_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Pos Modus:", nullptr));
        comboBox_single_trap_light_11_position_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Absoluut", nullptr));
        comboBox_single_trap_light_11_position_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan camera", nullptr));
        comboBox_single_trap_light_11_position_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan fractal midden", nullptr));
        comboBox_single_trap_light_11_position_mode->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan doel", nullptr));

        label_single_trap_light_11_coloring_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleuring:", nullptr));
        comboBox_single_trap_light_11_coloring_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Massief", nullptr));
        comboBox_single_trap_light_11_coloring_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Afstand gebaseerd", nullptr));
        comboBox_single_trap_light_11_coloring_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit val gebaseerd", nullptr));

        label_single_trap_light_11_falloff_type->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Afval:", nullptr));
        comboBox_single_trap_light_11_falloff_type->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Gaussiaans", nullptr));
        comboBox_single_trap_light_11_falloff_type->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Omgekeerd kwadraat", nullptr));
        comboBox_single_trap_light_11_falloff_type->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Lineair", nullptr));
        comboBox_single_trap_light_11_falloff_type->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Exponentieel", nullptr));
        comboBox_single_trap_light_11_falloff_type->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Smoothstep", nullptr));

        label_single_trap_light_11_edge_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rand zachtheid:", nullptr));
        label_single_trap_light_11_anim_orbit_radius->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_11_anim_orbit_radius->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit radius", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_11_anim_orbit_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_11_anim_pulsate_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_11_anim_pulsate_amount->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate amount", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_single_trap_light_11_place_surface->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Oppervlak", nullptr));
        pushButton_single_trap_light_11_place_target->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Doel", nullptr));
        groupCheck_single_trap_light_12_enabled->setTitle(QCoreApplication::translate("cEffectsSingleTrapTab", "Lamp 12 (eigen positie)", nullptr));
        label_single_trap_light_12_shape->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vorm:", nullptr));
        comboBox_single_trap_light_12_shape->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Punt", nullptr));
        comboBox_single_trap_light_12_shape->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Lijn", nullptr));
        comboBox_single_trap_light_12_shape->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Cirkel", nullptr));
        comboBox_single_trap_light_12_shape->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Vierkant", nullptr));
        comboBox_single_trap_light_12_shape->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Bol", nullptr));
        comboBox_single_trap_light_12_shape->setItemText(5, QCoreApplication::translate("cEffectsSingleTrapTab", "Kubus", nullptr));
        comboBox_single_trap_light_12_shape->setItemText(6, QCoreApplication::translate("cEffectsSingleTrapTab", "Torus", nullptr));
        comboBox_single_trap_light_12_shape->setItemText(7, QCoreApplication::translate("cEffectsSingleTrapTab", "Capsule", nullptr));
        comboBox_single_trap_light_12_shape->setItemText(8, QCoreApplication::translate("cEffectsSingleTrapTab", "Ring", nullptr));
        comboBox_single_trap_light_12_shape->setItemText(9, QCoreApplication::translate("cEffectsSingleTrapTab", "Ellips", nullptr));
        comboBox_single_trap_light_12_shape->setItemText(10, QCoreApplication::translate("cEffectsSingleTrapTab", "Kruis", nullptr));
        comboBox_single_trap_light_12_shape->setItemText(11, QCoreApplication::translate("cEffectsSingleTrapTab", "Cilinder", nullptr));
        comboBox_single_trap_light_12_shape->setItemText(12, QCoreApplication::translate("cEffectsSingleTrapTab", "Vlak", nullptr));
        comboBox_single_trap_light_12_shape->setItemText(13, QCoreApplication::translate("cEffectsSingleTrapTab", "Schijf", nullptr));

        label_single_trap_light_12_position->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Positie:", nullptr));
        pushButton_single_trap_light_12_place_camera->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats bij Camera", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_light_12_place_camera->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats licht op huidige camera positie", nullptr));
#endif // QT_CONFIG(tooltip)
        label_single_trap_light_12_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte:", nullptr));
        label_single_trap_light_12_size2->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte2:", nullptr));
        label_single_trap_light_12_thickness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Gloed:", nullptr));
        label_single_trap_light_12_rotation->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rotatie:", nullptr));
        label_single_trap_light_12_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Intensiteit:", nullptr));
        label_single_trap_light_12_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleur:", nullptr));
        colorButton_single_trap_light_12_color->setText(QString());
        label_single_trap_light_12_gradient_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grad:", nullptr));
        colorButton_single_trap_light_12_gradient_color->setText(QString());
        label_single_trap_light_12_visibility->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zichtbaarheid:", nullptr));
        label_single_trap_light_12_max_distance->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Max Afstand:", nullptr));
        label_single_trap_light_12_sharpening->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Scherpte:", nullptr));
        label_single_trap_light_12_blur->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vervaging:", nullptr));
        label_single_trap_light_12_solid_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Soliditeit:", nullptr));
        label_single_trap_light_12_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zachtheid:", nullptr));
        label_single_trap_light_12_relative_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Relatieve grootte:", nullptr));
        checkBox_single_trap_light_12_pre_transformed->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Voor-getransformeerd", nullptr));
        label_single_trap_light_12_position_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Pos Modus:", nullptr));
        comboBox_single_trap_light_12_position_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Absoluut", nullptr));
        comboBox_single_trap_light_12_position_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan camera", nullptr));
        comboBox_single_trap_light_12_position_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan fractal midden", nullptr));
        comboBox_single_trap_light_12_position_mode->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan doel", nullptr));

        label_single_trap_light_12_coloring_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleuring:", nullptr));
        comboBox_single_trap_light_12_coloring_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Massief", nullptr));
        comboBox_single_trap_light_12_coloring_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Afstand gebaseerd", nullptr));
        comboBox_single_trap_light_12_coloring_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit val gebaseerd", nullptr));

        label_single_trap_light_12_falloff_type->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Afval:", nullptr));
        comboBox_single_trap_light_12_falloff_type->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Gaussiaans", nullptr));
        comboBox_single_trap_light_12_falloff_type->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Omgekeerd kwadraat", nullptr));
        comboBox_single_trap_light_12_falloff_type->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Lineair", nullptr));
        comboBox_single_trap_light_12_falloff_type->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Exponentieel", nullptr));
        comboBox_single_trap_light_12_falloff_type->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Smoothstep", nullptr));

        label_single_trap_light_12_edge_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rand zachtheid:", nullptr));
        label_single_trap_light_12_anim_orbit_radius->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_12_anim_orbit_radius->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit radius", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_12_anim_orbit_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_12_anim_pulsate_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_12_anim_pulsate_amount->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate amount", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_single_trap_light_12_place_surface->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Oppervlak", nullptr));
        pushButton_single_trap_light_12_place_target->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Doel", nullptr));
        groupCheck_single_trap_light_13_enabled->setTitle(QCoreApplication::translate("cEffectsSingleTrapTab", "Lamp 13 (eigen positie)", nullptr));
        label_single_trap_light_13_shape->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vorm:", nullptr));
        comboBox_single_trap_light_13_shape->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Punt", nullptr));
        comboBox_single_trap_light_13_shape->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Lijn", nullptr));
        comboBox_single_trap_light_13_shape->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Cirkel", nullptr));
        comboBox_single_trap_light_13_shape->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Vierkant", nullptr));
        comboBox_single_trap_light_13_shape->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Bol", nullptr));
        comboBox_single_trap_light_13_shape->setItemText(5, QCoreApplication::translate("cEffectsSingleTrapTab", "Kubus", nullptr));
        comboBox_single_trap_light_13_shape->setItemText(6, QCoreApplication::translate("cEffectsSingleTrapTab", "Torus", nullptr));
        comboBox_single_trap_light_13_shape->setItemText(7, QCoreApplication::translate("cEffectsSingleTrapTab", "Capsule", nullptr));
        comboBox_single_trap_light_13_shape->setItemText(8, QCoreApplication::translate("cEffectsSingleTrapTab", "Ring", nullptr));
        comboBox_single_trap_light_13_shape->setItemText(9, QCoreApplication::translate("cEffectsSingleTrapTab", "Ellips", nullptr));
        comboBox_single_trap_light_13_shape->setItemText(10, QCoreApplication::translate("cEffectsSingleTrapTab", "Kruis", nullptr));
        comboBox_single_trap_light_13_shape->setItemText(11, QCoreApplication::translate("cEffectsSingleTrapTab", "Cilinder", nullptr));
        comboBox_single_trap_light_13_shape->setItemText(12, QCoreApplication::translate("cEffectsSingleTrapTab", "Vlak", nullptr));
        comboBox_single_trap_light_13_shape->setItemText(13, QCoreApplication::translate("cEffectsSingleTrapTab", "Schijf", nullptr));

        label_single_trap_light_13_position->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Positie:", nullptr));
        pushButton_single_trap_light_13_place_camera->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats bij Camera", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_light_13_place_camera->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats licht op huidige camera positie", nullptr));
#endif // QT_CONFIG(tooltip)
        label_single_trap_light_13_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte:", nullptr));
        label_single_trap_light_13_size2->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte2:", nullptr));
        label_single_trap_light_13_thickness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Gloed:", nullptr));
        label_single_trap_light_13_rotation->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rotatie:", nullptr));
        label_single_trap_light_13_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Intensiteit:", nullptr));
        label_single_trap_light_13_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleur:", nullptr));
        colorButton_single_trap_light_13_color->setText(QString());
        label_single_trap_light_13_gradient_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grad:", nullptr));
        colorButton_single_trap_light_13_gradient_color->setText(QString());
        label_single_trap_light_13_visibility->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zichtbaarheid:", nullptr));
        label_single_trap_light_13_max_distance->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Max Afstand:", nullptr));
        label_single_trap_light_13_sharpening->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Scherpte:", nullptr));
        label_single_trap_light_13_blur->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vervaging:", nullptr));
        label_single_trap_light_13_solid_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Soliditeit:", nullptr));
        label_single_trap_light_13_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zachtheid:", nullptr));
        label_single_trap_light_13_relative_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Relatieve grootte:", nullptr));
        checkBox_single_trap_light_13_pre_transformed->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Voor-getransformeerd", nullptr));
        label_single_trap_light_13_position_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Pos Modus:", nullptr));
        comboBox_single_trap_light_13_position_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Absoluut", nullptr));
        comboBox_single_trap_light_13_position_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan camera", nullptr));
        comboBox_single_trap_light_13_position_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan fractal midden", nullptr));
        comboBox_single_trap_light_13_position_mode->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan doel", nullptr));

        label_single_trap_light_13_coloring_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleuring:", nullptr));
        comboBox_single_trap_light_13_coloring_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Massief", nullptr));
        comboBox_single_trap_light_13_coloring_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Afstand gebaseerd", nullptr));
        comboBox_single_trap_light_13_coloring_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit val gebaseerd", nullptr));

        label_single_trap_light_13_falloff_type->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Afval:", nullptr));
        comboBox_single_trap_light_13_falloff_type->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Gaussiaans", nullptr));
        comboBox_single_trap_light_13_falloff_type->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Omgekeerd kwadraat", nullptr));
        comboBox_single_trap_light_13_falloff_type->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Lineair", nullptr));
        comboBox_single_trap_light_13_falloff_type->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Exponentieel", nullptr));
        comboBox_single_trap_light_13_falloff_type->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Smoothstep", nullptr));

        label_single_trap_light_13_edge_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rand zachtheid:", nullptr));
        label_single_trap_light_13_anim_orbit_radius->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_13_anim_orbit_radius->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit radius", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_13_anim_orbit_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_13_anim_pulsate_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_13_anim_pulsate_amount->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate amount", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_single_trap_light_13_place_surface->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Oppervlak", nullptr));
        pushButton_single_trap_light_13_place_target->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Doel", nullptr));
        groupCheck_single_trap_light_14_enabled->setTitle(QCoreApplication::translate("cEffectsSingleTrapTab", "Lamp 14 (eigen positie)", nullptr));
        label_single_trap_light_14_shape->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vorm:", nullptr));
        comboBox_single_trap_light_14_shape->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Punt", nullptr));
        comboBox_single_trap_light_14_shape->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Lijn", nullptr));
        comboBox_single_trap_light_14_shape->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Cirkel", nullptr));
        comboBox_single_trap_light_14_shape->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Vierkant", nullptr));
        comboBox_single_trap_light_14_shape->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Bol", nullptr));
        comboBox_single_trap_light_14_shape->setItemText(5, QCoreApplication::translate("cEffectsSingleTrapTab", "Kubus", nullptr));
        comboBox_single_trap_light_14_shape->setItemText(6, QCoreApplication::translate("cEffectsSingleTrapTab", "Torus", nullptr));
        comboBox_single_trap_light_14_shape->setItemText(7, QCoreApplication::translate("cEffectsSingleTrapTab", "Capsule", nullptr));
        comboBox_single_trap_light_14_shape->setItemText(8, QCoreApplication::translate("cEffectsSingleTrapTab", "Ring", nullptr));
        comboBox_single_trap_light_14_shape->setItemText(9, QCoreApplication::translate("cEffectsSingleTrapTab", "Ellips", nullptr));
        comboBox_single_trap_light_14_shape->setItemText(10, QCoreApplication::translate("cEffectsSingleTrapTab", "Kruis", nullptr));
        comboBox_single_trap_light_14_shape->setItemText(11, QCoreApplication::translate("cEffectsSingleTrapTab", "Cilinder", nullptr));
        comboBox_single_trap_light_14_shape->setItemText(12, QCoreApplication::translate("cEffectsSingleTrapTab", "Vlak", nullptr));
        comboBox_single_trap_light_14_shape->setItemText(13, QCoreApplication::translate("cEffectsSingleTrapTab", "Schijf", nullptr));

        label_single_trap_light_14_position->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Positie:", nullptr));
        pushButton_single_trap_light_14_place_camera->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats bij Camera", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_light_14_place_camera->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats licht op huidige camera positie", nullptr));
#endif // QT_CONFIG(tooltip)
        label_single_trap_light_14_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte:", nullptr));
        label_single_trap_light_14_size2->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte2:", nullptr));
        label_single_trap_light_14_thickness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Gloed:", nullptr));
        label_single_trap_light_14_rotation->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rotatie:", nullptr));
        label_single_trap_light_14_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Intensiteit:", nullptr));
        label_single_trap_light_14_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleur:", nullptr));
        colorButton_single_trap_light_14_color->setText(QString());
        label_single_trap_light_14_gradient_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grad:", nullptr));
        colorButton_single_trap_light_14_gradient_color->setText(QString());
        label_single_trap_light_14_visibility->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zichtbaarheid:", nullptr));
        label_single_trap_light_14_max_distance->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Max Afstand:", nullptr));
        label_single_trap_light_14_sharpening->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Scherpte:", nullptr));
        label_single_trap_light_14_blur->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vervaging:", nullptr));
        label_single_trap_light_14_solid_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Soliditeit:", nullptr));
        label_single_trap_light_14_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zachtheid:", nullptr));
        label_single_trap_light_14_relative_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Relatieve grootte:", nullptr));
        checkBox_single_trap_light_14_pre_transformed->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Voor-getransformeerd", nullptr));
        label_single_trap_light_14_position_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Pos Modus:", nullptr));
        comboBox_single_trap_light_14_position_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Absoluut", nullptr));
        comboBox_single_trap_light_14_position_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan camera", nullptr));
        comboBox_single_trap_light_14_position_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan fractal midden", nullptr));
        comboBox_single_trap_light_14_position_mode->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan doel", nullptr));

        label_single_trap_light_14_coloring_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleuring:", nullptr));
        comboBox_single_trap_light_14_coloring_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Massief", nullptr));
        comboBox_single_trap_light_14_coloring_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Afstand gebaseerd", nullptr));
        comboBox_single_trap_light_14_coloring_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit val gebaseerd", nullptr));

        label_single_trap_light_14_falloff_type->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Afval:", nullptr));
        comboBox_single_trap_light_14_falloff_type->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Gaussiaans", nullptr));
        comboBox_single_trap_light_14_falloff_type->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Omgekeerd kwadraat", nullptr));
        comboBox_single_trap_light_14_falloff_type->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Lineair", nullptr));
        comboBox_single_trap_light_14_falloff_type->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Exponentieel", nullptr));
        comboBox_single_trap_light_14_falloff_type->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Smoothstep", nullptr));

        label_single_trap_light_14_edge_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rand zachtheid:", nullptr));
        label_single_trap_light_14_anim_orbit_radius->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_14_anim_orbit_radius->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit radius", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_14_anim_orbit_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_14_anim_pulsate_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_14_anim_pulsate_amount->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate amount", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_single_trap_light_14_place_surface->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Oppervlak", nullptr));
        pushButton_single_trap_light_14_place_target->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Doel", nullptr));
        groupCheck_single_trap_light_15_enabled->setTitle(QCoreApplication::translate("cEffectsSingleTrapTab", "Lamp 15 (eigen positie)", nullptr));
        label_single_trap_light_15_shape->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vorm:", nullptr));
        comboBox_single_trap_light_15_shape->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Punt", nullptr));
        comboBox_single_trap_light_15_shape->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Lijn", nullptr));
        comboBox_single_trap_light_15_shape->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Cirkel", nullptr));
        comboBox_single_trap_light_15_shape->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Vierkant", nullptr));
        comboBox_single_trap_light_15_shape->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Bol", nullptr));
        comboBox_single_trap_light_15_shape->setItemText(5, QCoreApplication::translate("cEffectsSingleTrapTab", "Kubus", nullptr));
        comboBox_single_trap_light_15_shape->setItemText(6, QCoreApplication::translate("cEffectsSingleTrapTab", "Torus", nullptr));
        comboBox_single_trap_light_15_shape->setItemText(7, QCoreApplication::translate("cEffectsSingleTrapTab", "Capsule", nullptr));
        comboBox_single_trap_light_15_shape->setItemText(8, QCoreApplication::translate("cEffectsSingleTrapTab", "Ring", nullptr));
        comboBox_single_trap_light_15_shape->setItemText(9, QCoreApplication::translate("cEffectsSingleTrapTab", "Ellips", nullptr));
        comboBox_single_trap_light_15_shape->setItemText(10, QCoreApplication::translate("cEffectsSingleTrapTab", "Kruis", nullptr));
        comboBox_single_trap_light_15_shape->setItemText(11, QCoreApplication::translate("cEffectsSingleTrapTab", "Cilinder", nullptr));
        comboBox_single_trap_light_15_shape->setItemText(12, QCoreApplication::translate("cEffectsSingleTrapTab", "Vlak", nullptr));
        comboBox_single_trap_light_15_shape->setItemText(13, QCoreApplication::translate("cEffectsSingleTrapTab", "Schijf", nullptr));

        label_single_trap_light_15_position->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Positie:", nullptr));
        pushButton_single_trap_light_15_place_camera->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats bij Camera", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_light_15_place_camera->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats licht op huidige camera positie", nullptr));
#endif // QT_CONFIG(tooltip)
        label_single_trap_light_15_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte:", nullptr));
        label_single_trap_light_15_size2->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte2:", nullptr));
        label_single_trap_light_15_thickness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Gloed:", nullptr));
        label_single_trap_light_15_rotation->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rotatie:", nullptr));
        label_single_trap_light_15_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Intensiteit:", nullptr));
        label_single_trap_light_15_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleur:", nullptr));
        colorButton_single_trap_light_15_color->setText(QString());
        label_single_trap_light_15_gradient_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grad:", nullptr));
        colorButton_single_trap_light_15_gradient_color->setText(QString());
        label_single_trap_light_15_visibility->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zichtbaarheid:", nullptr));
        label_single_trap_light_15_max_distance->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Max Afstand:", nullptr));
        label_single_trap_light_15_sharpening->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Scherpte:", nullptr));
        label_single_trap_light_15_blur->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vervaging:", nullptr));
        label_single_trap_light_15_solid_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Soliditeit:", nullptr));
        label_single_trap_light_15_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zachtheid:", nullptr));
        label_single_trap_light_15_relative_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Relatieve grootte:", nullptr));
        checkBox_single_trap_light_15_pre_transformed->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Voor-getransformeerd", nullptr));
        label_single_trap_light_15_position_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Pos Modus:", nullptr));
        comboBox_single_trap_light_15_position_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Absoluut", nullptr));
        comboBox_single_trap_light_15_position_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan camera", nullptr));
        comboBox_single_trap_light_15_position_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan fractal midden", nullptr));
        comboBox_single_trap_light_15_position_mode->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan doel", nullptr));

        label_single_trap_light_15_coloring_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleuring:", nullptr));
        comboBox_single_trap_light_15_coloring_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Massief", nullptr));
        comboBox_single_trap_light_15_coloring_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Afstand gebaseerd", nullptr));
        comboBox_single_trap_light_15_coloring_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit val gebaseerd", nullptr));

        label_single_trap_light_15_falloff_type->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Afval:", nullptr));
        comboBox_single_trap_light_15_falloff_type->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Gaussiaans", nullptr));
        comboBox_single_trap_light_15_falloff_type->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Omgekeerd kwadraat", nullptr));
        comboBox_single_trap_light_15_falloff_type->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Lineair", nullptr));
        comboBox_single_trap_light_15_falloff_type->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Exponentieel", nullptr));
        comboBox_single_trap_light_15_falloff_type->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Smoothstep", nullptr));

        label_single_trap_light_15_edge_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rand zachtheid:", nullptr));
        label_single_trap_light_15_anim_orbit_radius->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_15_anim_orbit_radius->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit radius", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_15_anim_orbit_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_15_anim_pulsate_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_15_anim_pulsate_amount->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate amount", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_single_trap_light_15_place_surface->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Oppervlak", nullptr));
        pushButton_single_trap_light_15_place_target->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Doel", nullptr));
        groupCheck_single_trap_light_16_enabled->setTitle(QCoreApplication::translate("cEffectsSingleTrapTab", "Lamp 16 (eigen positie)", nullptr));
        label_single_trap_light_16_shape->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vorm:", nullptr));
        comboBox_single_trap_light_16_shape->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Punt", nullptr));
        comboBox_single_trap_light_16_shape->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Lijn", nullptr));
        comboBox_single_trap_light_16_shape->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Cirkel", nullptr));
        comboBox_single_trap_light_16_shape->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Vierkant", nullptr));
        comboBox_single_trap_light_16_shape->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Bol", nullptr));
        comboBox_single_trap_light_16_shape->setItemText(5, QCoreApplication::translate("cEffectsSingleTrapTab", "Kubus", nullptr));
        comboBox_single_trap_light_16_shape->setItemText(6, QCoreApplication::translate("cEffectsSingleTrapTab", "Torus", nullptr));
        comboBox_single_trap_light_16_shape->setItemText(7, QCoreApplication::translate("cEffectsSingleTrapTab", "Capsule", nullptr));
        comboBox_single_trap_light_16_shape->setItemText(8, QCoreApplication::translate("cEffectsSingleTrapTab", "Ring", nullptr));
        comboBox_single_trap_light_16_shape->setItemText(9, QCoreApplication::translate("cEffectsSingleTrapTab", "Ellips", nullptr));
        comboBox_single_trap_light_16_shape->setItemText(10, QCoreApplication::translate("cEffectsSingleTrapTab", "Kruis", nullptr));
        comboBox_single_trap_light_16_shape->setItemText(11, QCoreApplication::translate("cEffectsSingleTrapTab", "Cilinder", nullptr));
        comboBox_single_trap_light_16_shape->setItemText(12, QCoreApplication::translate("cEffectsSingleTrapTab", "Vlak", nullptr));
        comboBox_single_trap_light_16_shape->setItemText(13, QCoreApplication::translate("cEffectsSingleTrapTab", "Schijf", nullptr));

        label_single_trap_light_16_position->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Positie:", nullptr));
        pushButton_single_trap_light_16_place_camera->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats bij Camera", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_light_16_place_camera->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats licht op huidige camera positie", nullptr));
#endif // QT_CONFIG(tooltip)
        label_single_trap_light_16_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte:", nullptr));
        label_single_trap_light_16_size2->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte2:", nullptr));
        label_single_trap_light_16_thickness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Gloed:", nullptr));
        label_single_trap_light_16_rotation->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rotatie:", nullptr));
        label_single_trap_light_16_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Intensiteit:", nullptr));
        label_single_trap_light_16_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleur:", nullptr));
        colorButton_single_trap_light_16_color->setText(QString());
        label_single_trap_light_16_gradient_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grad:", nullptr));
        colorButton_single_trap_light_16_gradient_color->setText(QString());
        label_single_trap_light_16_visibility->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zichtbaarheid:", nullptr));
        label_single_trap_light_16_max_distance->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Max Afstand:", nullptr));
        label_single_trap_light_16_sharpening->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Scherpte:", nullptr));
        label_single_trap_light_16_blur->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vervaging:", nullptr));
        label_single_trap_light_16_solid_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Soliditeit:", nullptr));
        label_single_trap_light_16_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zachtheid:", nullptr));
        label_single_trap_light_16_relative_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Relatieve grootte:", nullptr));
        checkBox_single_trap_light_16_pre_transformed->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Voor-getransformeerd", nullptr));
        label_single_trap_light_16_position_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Pos Modus:", nullptr));
        comboBox_single_trap_light_16_position_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Absoluut", nullptr));
        comboBox_single_trap_light_16_position_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan camera", nullptr));
        comboBox_single_trap_light_16_position_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan fractal midden", nullptr));
        comboBox_single_trap_light_16_position_mode->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan doel", nullptr));

        label_single_trap_light_16_coloring_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleuring:", nullptr));
        comboBox_single_trap_light_16_coloring_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Massief", nullptr));
        comboBox_single_trap_light_16_coloring_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Afstand gebaseerd", nullptr));
        comboBox_single_trap_light_16_coloring_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit val gebaseerd", nullptr));

        label_single_trap_light_16_falloff_type->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Afval:", nullptr));
        comboBox_single_trap_light_16_falloff_type->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Gaussiaans", nullptr));
        comboBox_single_trap_light_16_falloff_type->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Omgekeerd kwadraat", nullptr));
        comboBox_single_trap_light_16_falloff_type->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Lineair", nullptr));
        comboBox_single_trap_light_16_falloff_type->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Exponentieel", nullptr));
        comboBox_single_trap_light_16_falloff_type->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Smoothstep", nullptr));

        label_single_trap_light_16_edge_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rand zachtheid:", nullptr));
        label_single_trap_light_16_anim_orbit_radius->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_16_anim_orbit_radius->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit radius", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_16_anim_orbit_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_16_anim_pulsate_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_16_anim_pulsate_amount->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate amount", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_single_trap_light_16_place_surface->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Oppervlak", nullptr));
        pushButton_single_trap_light_16_place_target->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Doel", nullptr));
        groupCheck_single_trap_light_17_enabled->setTitle(QCoreApplication::translate("cEffectsSingleTrapTab", "Lamp 17 (eigen positie)", nullptr));
        label_single_trap_light_17_shape->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vorm:", nullptr));
        comboBox_single_trap_light_17_shape->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Punt", nullptr));
        comboBox_single_trap_light_17_shape->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Lijn", nullptr));
        comboBox_single_trap_light_17_shape->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Cirkel", nullptr));
        comboBox_single_trap_light_17_shape->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Vierkant", nullptr));
        comboBox_single_trap_light_17_shape->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Bol", nullptr));
        comboBox_single_trap_light_17_shape->setItemText(5, QCoreApplication::translate("cEffectsSingleTrapTab", "Kubus", nullptr));
        comboBox_single_trap_light_17_shape->setItemText(6, QCoreApplication::translate("cEffectsSingleTrapTab", "Torus", nullptr));
        comboBox_single_trap_light_17_shape->setItemText(7, QCoreApplication::translate("cEffectsSingleTrapTab", "Capsule", nullptr));
        comboBox_single_trap_light_17_shape->setItemText(8, QCoreApplication::translate("cEffectsSingleTrapTab", "Ring", nullptr));
        comboBox_single_trap_light_17_shape->setItemText(9, QCoreApplication::translate("cEffectsSingleTrapTab", "Ellips", nullptr));
        comboBox_single_trap_light_17_shape->setItemText(10, QCoreApplication::translate("cEffectsSingleTrapTab", "Kruis", nullptr));
        comboBox_single_trap_light_17_shape->setItemText(11, QCoreApplication::translate("cEffectsSingleTrapTab", "Cilinder", nullptr));
        comboBox_single_trap_light_17_shape->setItemText(12, QCoreApplication::translate("cEffectsSingleTrapTab", "Vlak", nullptr));
        comboBox_single_trap_light_17_shape->setItemText(13, QCoreApplication::translate("cEffectsSingleTrapTab", "Schijf", nullptr));

        label_single_trap_light_17_position->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Positie:", nullptr));
        pushButton_single_trap_light_17_place_camera->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats bij Camera", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_light_17_place_camera->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats licht op huidige camera positie", nullptr));
#endif // QT_CONFIG(tooltip)
        label_single_trap_light_17_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte:", nullptr));
        label_single_trap_light_17_size2->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte2:", nullptr));
        label_single_trap_light_17_thickness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Gloed:", nullptr));
        label_single_trap_light_17_rotation->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rotatie:", nullptr));
        label_single_trap_light_17_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Intensiteit:", nullptr));
        label_single_trap_light_17_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleur:", nullptr));
        colorButton_single_trap_light_17_color->setText(QString());
        label_single_trap_light_17_gradient_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grad:", nullptr));
        colorButton_single_trap_light_17_gradient_color->setText(QString());
        label_single_trap_light_17_visibility->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zichtbaarheid:", nullptr));
        label_single_trap_light_17_max_distance->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Max Afstand:", nullptr));
        label_single_trap_light_17_sharpening->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Scherpte:", nullptr));
        label_single_trap_light_17_blur->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vervaging:", nullptr));
        label_single_trap_light_17_solid_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Soliditeit:", nullptr));
        label_single_trap_light_17_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zachtheid:", nullptr));
        label_single_trap_light_17_relative_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Relatieve grootte:", nullptr));
        checkBox_single_trap_light_17_pre_transformed->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Voor-getransformeerd", nullptr));
        label_single_trap_light_17_position_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Pos Modus:", nullptr));
        comboBox_single_trap_light_17_position_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Absoluut", nullptr));
        comboBox_single_trap_light_17_position_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan camera", nullptr));
        comboBox_single_trap_light_17_position_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan fractal midden", nullptr));
        comboBox_single_trap_light_17_position_mode->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan doel", nullptr));

        label_single_trap_light_17_coloring_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleuring:", nullptr));
        comboBox_single_trap_light_17_coloring_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Massief", nullptr));
        comboBox_single_trap_light_17_coloring_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Afstand gebaseerd", nullptr));
        comboBox_single_trap_light_17_coloring_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit val gebaseerd", nullptr));

        label_single_trap_light_17_falloff_type->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Afval:", nullptr));
        comboBox_single_trap_light_17_falloff_type->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Gaussiaans", nullptr));
        comboBox_single_trap_light_17_falloff_type->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Omgekeerd kwadraat", nullptr));
        comboBox_single_trap_light_17_falloff_type->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Lineair", nullptr));
        comboBox_single_trap_light_17_falloff_type->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Exponentieel", nullptr));
        comboBox_single_trap_light_17_falloff_type->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Smoothstep", nullptr));

        label_single_trap_light_17_edge_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rand zachtheid:", nullptr));
        label_single_trap_light_17_anim_orbit_radius->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_17_anim_orbit_radius->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit radius", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_17_anim_orbit_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_17_anim_pulsate_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_17_anim_pulsate_amount->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate amount", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_single_trap_light_17_place_surface->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Oppervlak", nullptr));
        pushButton_single_trap_light_17_place_target->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Doel", nullptr));
        groupCheck_single_trap_light_18_enabled->setTitle(QCoreApplication::translate("cEffectsSingleTrapTab", "Lamp 18 (eigen positie)", nullptr));
        label_single_trap_light_18_shape->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vorm:", nullptr));
        comboBox_single_trap_light_18_shape->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Punt", nullptr));
        comboBox_single_trap_light_18_shape->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Lijn", nullptr));
        comboBox_single_trap_light_18_shape->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Cirkel", nullptr));
        comboBox_single_trap_light_18_shape->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Vierkant", nullptr));
        comboBox_single_trap_light_18_shape->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Bol", nullptr));
        comboBox_single_trap_light_18_shape->setItemText(5, QCoreApplication::translate("cEffectsSingleTrapTab", "Kubus", nullptr));
        comboBox_single_trap_light_18_shape->setItemText(6, QCoreApplication::translate("cEffectsSingleTrapTab", "Torus", nullptr));
        comboBox_single_trap_light_18_shape->setItemText(7, QCoreApplication::translate("cEffectsSingleTrapTab", "Capsule", nullptr));
        comboBox_single_trap_light_18_shape->setItemText(8, QCoreApplication::translate("cEffectsSingleTrapTab", "Ring", nullptr));
        comboBox_single_trap_light_18_shape->setItemText(9, QCoreApplication::translate("cEffectsSingleTrapTab", "Ellips", nullptr));
        comboBox_single_trap_light_18_shape->setItemText(10, QCoreApplication::translate("cEffectsSingleTrapTab", "Kruis", nullptr));
        comboBox_single_trap_light_18_shape->setItemText(11, QCoreApplication::translate("cEffectsSingleTrapTab", "Cilinder", nullptr));
        comboBox_single_trap_light_18_shape->setItemText(12, QCoreApplication::translate("cEffectsSingleTrapTab", "Vlak", nullptr));
        comboBox_single_trap_light_18_shape->setItemText(13, QCoreApplication::translate("cEffectsSingleTrapTab", "Schijf", nullptr));

        label_single_trap_light_18_position->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Positie:", nullptr));
        pushButton_single_trap_light_18_place_camera->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats bij Camera", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_light_18_place_camera->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats licht op huidige camera positie", nullptr));
#endif // QT_CONFIG(tooltip)
        label_single_trap_light_18_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte:", nullptr));
        label_single_trap_light_18_size2->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte2:", nullptr));
        label_single_trap_light_18_thickness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Gloed:", nullptr));
        label_single_trap_light_18_rotation->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rotatie:", nullptr));
        label_single_trap_light_18_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Intensiteit:", nullptr));
        label_single_trap_light_18_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleur:", nullptr));
        colorButton_single_trap_light_18_color->setText(QString());
        label_single_trap_light_18_gradient_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grad:", nullptr));
        colorButton_single_trap_light_18_gradient_color->setText(QString());
        label_single_trap_light_18_visibility->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zichtbaarheid:", nullptr));
        label_single_trap_light_18_max_distance->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Max Afstand:", nullptr));
        label_single_trap_light_18_sharpening->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Scherpte:", nullptr));
        label_single_trap_light_18_blur->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vervaging:", nullptr));
        label_single_trap_light_18_solid_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Soliditeit:", nullptr));
        label_single_trap_light_18_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zachtheid:", nullptr));
        label_single_trap_light_18_relative_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Relatieve grootte:", nullptr));
        checkBox_single_trap_light_18_pre_transformed->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Voor-getransformeerd", nullptr));
        label_single_trap_light_18_position_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Pos Modus:", nullptr));
        comboBox_single_trap_light_18_position_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Absoluut", nullptr));
        comboBox_single_trap_light_18_position_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan camera", nullptr));
        comboBox_single_trap_light_18_position_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan fractal midden", nullptr));
        comboBox_single_trap_light_18_position_mode->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan doel", nullptr));

        label_single_trap_light_18_coloring_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleuring:", nullptr));
        comboBox_single_trap_light_18_coloring_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Massief", nullptr));
        comboBox_single_trap_light_18_coloring_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Afstand gebaseerd", nullptr));
        comboBox_single_trap_light_18_coloring_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit val gebaseerd", nullptr));

        label_single_trap_light_18_falloff_type->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Afval:", nullptr));
        comboBox_single_trap_light_18_falloff_type->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Gaussiaans", nullptr));
        comboBox_single_trap_light_18_falloff_type->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Omgekeerd kwadraat", nullptr));
        comboBox_single_trap_light_18_falloff_type->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Lineair", nullptr));
        comboBox_single_trap_light_18_falloff_type->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Exponentieel", nullptr));
        comboBox_single_trap_light_18_falloff_type->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Smoothstep", nullptr));

        label_single_trap_light_18_edge_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rand zachtheid:", nullptr));
        label_single_trap_light_18_anim_orbit_radius->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_18_anim_orbit_radius->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit radius", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_18_anim_orbit_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_18_anim_pulsate_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_18_anim_pulsate_amount->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate amount", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_single_trap_light_18_place_surface->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Oppervlak", nullptr));
        pushButton_single_trap_light_18_place_target->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Doel", nullptr));
        groupCheck_single_trap_light_19_enabled->setTitle(QCoreApplication::translate("cEffectsSingleTrapTab", "Lamp 19 (eigen positie)", nullptr));
        label_single_trap_light_19_shape->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vorm:", nullptr));
        comboBox_single_trap_light_19_shape->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Punt", nullptr));
        comboBox_single_trap_light_19_shape->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Lijn", nullptr));
        comboBox_single_trap_light_19_shape->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Cirkel", nullptr));
        comboBox_single_trap_light_19_shape->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Vierkant", nullptr));
        comboBox_single_trap_light_19_shape->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Bol", nullptr));
        comboBox_single_trap_light_19_shape->setItemText(5, QCoreApplication::translate("cEffectsSingleTrapTab", "Kubus", nullptr));
        comboBox_single_trap_light_19_shape->setItemText(6, QCoreApplication::translate("cEffectsSingleTrapTab", "Torus", nullptr));
        comboBox_single_trap_light_19_shape->setItemText(7, QCoreApplication::translate("cEffectsSingleTrapTab", "Capsule", nullptr));
        comboBox_single_trap_light_19_shape->setItemText(8, QCoreApplication::translate("cEffectsSingleTrapTab", "Ring", nullptr));
        comboBox_single_trap_light_19_shape->setItemText(9, QCoreApplication::translate("cEffectsSingleTrapTab", "Ellips", nullptr));
        comboBox_single_trap_light_19_shape->setItemText(10, QCoreApplication::translate("cEffectsSingleTrapTab", "Kruis", nullptr));
        comboBox_single_trap_light_19_shape->setItemText(11, QCoreApplication::translate("cEffectsSingleTrapTab", "Cilinder", nullptr));
        comboBox_single_trap_light_19_shape->setItemText(12, QCoreApplication::translate("cEffectsSingleTrapTab", "Vlak", nullptr));
        comboBox_single_trap_light_19_shape->setItemText(13, QCoreApplication::translate("cEffectsSingleTrapTab", "Schijf", nullptr));

        label_single_trap_light_19_position->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Positie:", nullptr));
        pushButton_single_trap_light_19_place_camera->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats bij Camera", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_light_19_place_camera->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats licht op huidige camera positie", nullptr));
#endif // QT_CONFIG(tooltip)
        label_single_trap_light_19_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte:", nullptr));
        label_single_trap_light_19_size2->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte2:", nullptr));
        label_single_trap_light_19_thickness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Gloed:", nullptr));
        label_single_trap_light_19_rotation->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rotatie:", nullptr));
        label_single_trap_light_19_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Intensiteit:", nullptr));
        label_single_trap_light_19_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleur:", nullptr));
        colorButton_single_trap_light_19_color->setText(QString());
        label_single_trap_light_19_gradient_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grad:", nullptr));
        colorButton_single_trap_light_19_gradient_color->setText(QString());
        label_single_trap_light_19_visibility->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zichtbaarheid:", nullptr));
        label_single_trap_light_19_max_distance->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Max Afstand:", nullptr));
        label_single_trap_light_19_sharpening->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Scherpte:", nullptr));
        label_single_trap_light_19_blur->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vervaging:", nullptr));
        label_single_trap_light_19_solid_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Soliditeit:", nullptr));
        label_single_trap_light_19_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zachtheid:", nullptr));
        label_single_trap_light_19_relative_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Relatieve grootte:", nullptr));
        checkBox_single_trap_light_19_pre_transformed->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Voor-getransformeerd", nullptr));
        label_single_trap_light_19_position_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Pos Modus:", nullptr));
        comboBox_single_trap_light_19_position_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Absoluut", nullptr));
        comboBox_single_trap_light_19_position_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan camera", nullptr));
        comboBox_single_trap_light_19_position_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan fractal midden", nullptr));
        comboBox_single_trap_light_19_position_mode->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan doel", nullptr));

        label_single_trap_light_19_coloring_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleuring:", nullptr));
        comboBox_single_trap_light_19_coloring_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Massief", nullptr));
        comboBox_single_trap_light_19_coloring_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Afstand gebaseerd", nullptr));
        comboBox_single_trap_light_19_coloring_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit val gebaseerd", nullptr));

        label_single_trap_light_19_falloff_type->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Afval:", nullptr));
        comboBox_single_trap_light_19_falloff_type->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Gaussiaans", nullptr));
        comboBox_single_trap_light_19_falloff_type->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Omgekeerd kwadraat", nullptr));
        comboBox_single_trap_light_19_falloff_type->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Lineair", nullptr));
        comboBox_single_trap_light_19_falloff_type->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Exponentieel", nullptr));
        comboBox_single_trap_light_19_falloff_type->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Smoothstep", nullptr));

        label_single_trap_light_19_edge_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rand zachtheid:", nullptr));
        label_single_trap_light_19_anim_orbit_radius->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_19_anim_orbit_radius->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit radius", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_19_anim_orbit_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_19_anim_pulsate_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_19_anim_pulsate_amount->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate amount", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_single_trap_light_19_place_surface->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Oppervlak", nullptr));
        pushButton_single_trap_light_19_place_target->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Doel", nullptr));
        groupCheck_single_trap_light_20_enabled->setTitle(QCoreApplication::translate("cEffectsSingleTrapTab", "Lamp 20 (eigen positie)", nullptr));
        label_single_trap_light_20_shape->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vorm:", nullptr));
        comboBox_single_trap_light_20_shape->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Punt", nullptr));
        comboBox_single_trap_light_20_shape->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Lijn", nullptr));
        comboBox_single_trap_light_20_shape->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Cirkel", nullptr));
        comboBox_single_trap_light_20_shape->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Vierkant", nullptr));
        comboBox_single_trap_light_20_shape->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Bol", nullptr));
        comboBox_single_trap_light_20_shape->setItemText(5, QCoreApplication::translate("cEffectsSingleTrapTab", "Kubus", nullptr));
        comboBox_single_trap_light_20_shape->setItemText(6, QCoreApplication::translate("cEffectsSingleTrapTab", "Torus", nullptr));
        comboBox_single_trap_light_20_shape->setItemText(7, QCoreApplication::translate("cEffectsSingleTrapTab", "Capsule", nullptr));
        comboBox_single_trap_light_20_shape->setItemText(8, QCoreApplication::translate("cEffectsSingleTrapTab", "Ring", nullptr));
        comboBox_single_trap_light_20_shape->setItemText(9, QCoreApplication::translate("cEffectsSingleTrapTab", "Ellips", nullptr));
        comboBox_single_trap_light_20_shape->setItemText(10, QCoreApplication::translate("cEffectsSingleTrapTab", "Kruis", nullptr));
        comboBox_single_trap_light_20_shape->setItemText(11, QCoreApplication::translate("cEffectsSingleTrapTab", "Cilinder", nullptr));
        comboBox_single_trap_light_20_shape->setItemText(12, QCoreApplication::translate("cEffectsSingleTrapTab", "Vlak", nullptr));
        comboBox_single_trap_light_20_shape->setItemText(13, QCoreApplication::translate("cEffectsSingleTrapTab", "Schijf", nullptr));

        label_single_trap_light_20_position->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Positie:", nullptr));
        pushButton_single_trap_light_20_place_camera->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats bij Camera", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_single_trap_light_20_place_camera->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats licht op huidige camera positie", nullptr));
#endif // QT_CONFIG(tooltip)
        label_single_trap_light_20_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte:", nullptr));
        label_single_trap_light_20_size2->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grootte2:", nullptr));
        label_single_trap_light_20_thickness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Gloed:", nullptr));
        label_single_trap_light_20_rotation->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rotatie:", nullptr));
        label_single_trap_light_20_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Intensiteit:", nullptr));
        label_single_trap_light_20_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleur:", nullptr));
        colorButton_single_trap_light_20_color->setText(QString());
        label_single_trap_light_20_gradient_color->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Grad:", nullptr));
        colorButton_single_trap_light_20_gradient_color->setText(QString());
        label_single_trap_light_20_visibility->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zichtbaarheid:", nullptr));
        label_single_trap_light_20_max_distance->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Max Afstand:", nullptr));
        label_single_trap_light_20_sharpening->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Scherpte:", nullptr));
        label_single_trap_light_20_blur->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Vervaging:", nullptr));
        label_single_trap_light_20_solid_intensity->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Soliditeit:", nullptr));
        label_single_trap_light_20_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Zachtheid:", nullptr));
        label_single_trap_light_20_relative_size->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Relatieve grootte:", nullptr));
        checkBox_single_trap_light_20_pre_transformed->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Voor-getransformeerd", nullptr));
        label_single_trap_light_20_position_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Pos Modus:", nullptr));
        comboBox_single_trap_light_20_position_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Absoluut", nullptr));
        comboBox_single_trap_light_20_position_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan camera", nullptr));
        comboBox_single_trap_light_20_position_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan fractal midden", nullptr));
        comboBox_single_trap_light_20_position_mode->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Relatief aan doel", nullptr));

        label_single_trap_light_20_coloring_mode->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Kleuring:", nullptr));
        comboBox_single_trap_light_20_coloring_mode->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Massief", nullptr));
        comboBox_single_trap_light_20_coloring_mode->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Afstand gebaseerd", nullptr));
        comboBox_single_trap_light_20_coloring_mode->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit val gebaseerd", nullptr));

        label_single_trap_light_20_falloff_type->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Afval:", nullptr));
        comboBox_single_trap_light_20_falloff_type->setItemText(0, QCoreApplication::translate("cEffectsSingleTrapTab", "Gaussiaans", nullptr));
        comboBox_single_trap_light_20_falloff_type->setItemText(1, QCoreApplication::translate("cEffectsSingleTrapTab", "Omgekeerd kwadraat", nullptr));
        comboBox_single_trap_light_20_falloff_type->setItemText(2, QCoreApplication::translate("cEffectsSingleTrapTab", "Lineair", nullptr));
        comboBox_single_trap_light_20_falloff_type->setItemText(3, QCoreApplication::translate("cEffectsSingleTrapTab", "Exponentieel", nullptr));
        comboBox_single_trap_light_20_falloff_type->setItemText(4, QCoreApplication::translate("cEffectsSingleTrapTab", "Smoothstep", nullptr));

        label_single_trap_light_20_edge_softness->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Rand zachtheid:", nullptr));
        label_single_trap_light_20_anim_orbit_radius->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_20_anim_orbit_radius->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit radius", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_20_anim_orbit_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Orbit speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_20_anim_pulsate_speed->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_single_trap_light_20_anim_pulsate_amount->setToolTip(QCoreApplication::translate("cEffectsSingleTrapTab", "Pulsate amount", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_single_trap_light_20_place_surface->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Oppervlak", nullptr));
        pushButton_single_trap_light_20_place_target->setText(QCoreApplication::translate("cEffectsSingleTrapTab", "Plaats op Doel", nullptr));
        (void)cEffectsSingleTrapTab;
    } // retranslateUi

};

namespace Ui {
    class cEffectsSingleTrapTab: public Ui_cEffectsSingleTrapTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EFFECTS_SINGLE_TRAP_TAB_H
