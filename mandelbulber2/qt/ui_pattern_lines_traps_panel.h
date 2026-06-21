/********************************************************************************
** Form generated from reading UI file 'pattern_lines_traps_panel.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATTERN_LINES_TRAPS_PANEL_H
#define UI_PATTERN_LINES_TRAPS_PANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
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

class Ui_cPatternLinesTrapsPanel
{
public:
    QVBoxLayout *verticalLayout_pattern_traps_panel_root;
    QScrollArea *scrollArea_pattern_line_traps_top;
    QWidget *scrollAreaWidgetContents_pattern_traps_top;
    QVBoxLayout *verticalLayout_pattern_traps_dock_top;
    QGroupBox *groupBox_pattern_line_traps;
    QVBoxLayout *verticalLayout_pattern_line_traps_outer;
    MyCheckBox *checkBox_pattern_line_traps_enabled;
    MyCheckBox *checkBox_pattern_line_traps_overlay_visible;
    QHBoxLayout *horizontalLayout_pattern_batch;
    QPushButton *pushButton_pattern_line_traps_enable_all;
    QPushButton *pushButton_pattern_line_traps_disable_all;
    QPushButton *pushButton_pattern_line_traps_solo_selected;
    QSpacerItem *horizontalSpacer_pattern_batch;
    QHBoxLayout *horizontalLayout_pattern_global;
    QLabel *label_pattern_line_traps_combine_mode;
    MyComboBox *comboBox_pattern_line_traps_combine_mode;
    QLabel *label_pattern_line_traps_coloring_mode;
    MyComboBox *comboBox_pattern_line_traps_coloring_mode;
    QSpacerItem *horizontalSpacer_pattern_global;
    QHBoxLayout *horizontalLayout_pattern_color_tune;
    QLabel *label_pattern_line_traps_coloring_speed;
    MyLineEdit *logedit_pattern_line_traps_coloring_speed;
    QLabel *label_pattern_line_traps_palette_offset;
    MyLineEdit *logedit_pattern_line_traps_palette_offset;
    QSpacerItem *horizontalSpacer_pattern_color_tune;
    QHBoxLayout *horizontalLayout_pattern_global_overrides;
    QLabel *label_pattern_line_traps_global_intensity;
    MyLineEdit *logedit_pattern_line_traps_global_intensity;
    QLabel *label_pattern_line_traps_global_max_distance;
    MyLineEdit *logedit_pattern_line_traps_global_max_distance;
    QLabel *label_pattern_line_traps_global_scale;
    MyLineEdit *logedit_pattern_line_traps_global_scale;
    QLabel *label_pattern_line_traps_global_relative_thickness;
    MyLineEdit *logedit_pattern_line_traps_global_relative_thickness;
    QSpacerItem *horizontalSpacer_pattern_global_overrides;
    QGroupBox *groupBox_pattern_line_trap_workflow;
    QVBoxLayout *verticalLayout_pattern_line_trap_workflow;
    QHBoxLayout *horizontalLayout_pattern_solo;
    QLabel *label_pattern_line_trap_solo_layer;
    MySpinBox *spinboxInt_pattern_line_trap_solo_layer;
    QSpacerItem *horizontalSpacer_pattern_solo;
    QHBoxLayout *horizontalLayout_pattern_presets;
    QLabel *label_pattern_line_trap_presets;
    QComboBox *comboBox_pattern_line_trap_presets;
    QPushButton *pushButton_pattern_line_trap_preset_refresh;
    QPushButton *pushButton_pattern_line_trap_preset_load;
    QPushButton *pushButton_pattern_line_trap_preset_save;
    QHBoxLayout *horizontalLayout_pattern_copy;
    QLabel *label_pattern_line_trap_copy;
    QSpinBox *spinbox_pattern_line_trap_copy_from;
    QLabel *label_pattern_line_trap_copy_arrow;
    QSpinBox *spinbox_pattern_line_trap_copy_to;
    QPushButton *pushButton_pattern_line_trap_copy_layer;
    QGroupBox *groupBox_pattern_line_exact_placement;
    QVBoxLayout *verticalLayout_pattern_line_exact;
    QLabel *label_pattern_line_exact_intro;
    QHBoxLayout *horizontalLayout_pattern_line_precision;
    QLabel *label_pattern_line_precision_mode;
    QComboBox *comboBox_pattern_line_precision_mode;
    QHBoxLayout *horizontalLayout_pattern_line_exact;
    QLabel *label_pattern_line_exact_layer;
    QSpinBox *spinbox_pattern_line_exact_layer;
    QPushButton *pushButton_pattern_line_exact_activate;
    QGroupBox *groupBox_pattern_line_placement_offset_xyz;
    QGridLayout *gridLayout_pattern_line_placement_offset;
    QLabel *label_pattern_line_pl_offset_x;
    MyLineEdit *vect3_aux_light_manual_placement_offset_x;
    QLabel *label_pattern_line_pl_offset_y;
    MyLineEdit *vect3_aux_light_manual_placement_offset_y;
    QLabel *label_pattern_line_pl_offset_z;
    MyLineEdit *vect3_aux_light_manual_placement_offset_z;
    QLabel *label_pattern_line_exact_footer;
    QLabel *label_pattern_line_traps_hint;
    QPushButton *pushButton_pattern_line_traps_quick_test;
    MyGroupBox *groupCheck_pattern_line_trap_1_enabled;
    QGridLayout *gridLayout_pattern_line_1;
    QLabel *label_pattern_line_1_pos;
    MyLineEdit *vect3_pattern_line_trap_1_position_x;
    MyLineEdit *vect3_pattern_line_trap_1_position_y;
    MyLineEdit *vect3_pattern_line_trap_1_position_z;
    QLabel *label_pattern_line_1_rot;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_1_rotation_x;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_1_rotation_y;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_1_rotation_z;
    QLabel *label_pattern_line_1_radius;
    MyLineEdit *logedit_pattern_line_trap_1_radius;
    MyLineEdit *logedit_pattern_line_trap_1_thickness;
    MyLineEdit *logedit_pattern_line_trap_1_edge_softness;
    MyLineEdit *logedit_pattern_line_trap_1_max_distance;
    QLabel *label_pattern_line_1_scale;
    MyLineEdit *logedit_pattern_line_trap_1_scale;
    MyLineEdit *logedit_pattern_line_trap_1_relative_thickness;
    QLabel *label_pattern_line_1_int;
    MyLineEdit *logedit_pattern_line_trap_1_intensity;
    MyColorButton *colorButton_pattern_line_trap_1_color;
    MyColorButton *colorButton_pattern_line_trap_1_color_2;
    MyColorButton *colorButton_pattern_line_trap_1_color_3;
    QLabel *label_pattern_line_1_shape;
    MyComboBox *comboBox_pattern_line_trap_1_shape;
    QLabel *label_pattern_line_1_shape_aux;
    MyLineEdit *logedit_pattern_line_trap_1_shape_aux;
    QLabel *label_pattern_line_1_sharp_seg;
    MyLineEdit *logedit_pattern_line_trap_1_falloff_sharpness;
    MyLineEdit *logedit_pattern_line_trap_1_segment_half_length;
    QLabel *label_pattern_line_1_glow;
    MyLineEdit *logedit_pattern_line_trap_1_glow_spread;
    MyComboBox *comboBox_pattern_line_trap_1_falloff_profile;
    QLabel *label_pattern_line_1_side;
    MyComboBox *comboBox_pattern_line_trap_1_edge_side;
    QPushButton *pushButton_pattern_line_trap_1_place_surface;
    QPushButton *pushButton_pattern_line_trap_1_place_target;
    MyGroupBox *groupCheck_pattern_line_trap_2_enabled;
    QGridLayout *gridLayout_pattern_line_2;
    QLabel *label_pattern_line_2_pos;
    MyLineEdit *vect3_pattern_line_trap_2_position_x;
    MyLineEdit *vect3_pattern_line_trap_2_position_y;
    MyLineEdit *vect3_pattern_line_trap_2_position_z;
    QLabel *label_pattern_line_2_rot;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_2_rotation_x;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_2_rotation_y;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_2_rotation_z;
    QLabel *label_pattern_line_2_radius;
    MyLineEdit *logedit_pattern_line_trap_2_radius;
    MyLineEdit *logedit_pattern_line_trap_2_thickness;
    MyLineEdit *logedit_pattern_line_trap_2_edge_softness;
    MyLineEdit *logedit_pattern_line_trap_2_max_distance;
    QLabel *label_pattern_line_2_scale;
    MyLineEdit *logedit_pattern_line_trap_2_scale;
    MyLineEdit *logedit_pattern_line_trap_2_relative_thickness;
    QLabel *label_pattern_line_2_int;
    MyLineEdit *logedit_pattern_line_trap_2_intensity;
    MyColorButton *colorButton_pattern_line_trap_2_color;
    MyColorButton *colorButton_pattern_line_trap_2_color_2;
    MyColorButton *colorButton_pattern_line_trap_2_color_3;
    QLabel *label_pattern_line_2_shape;
    MyComboBox *comboBox_pattern_line_trap_2_shape;
    QLabel *label_pattern_line_2_shape_aux;
    MyLineEdit *logedit_pattern_line_trap_2_shape_aux;
    QLabel *label_pattern_line_2_sharp_seg;
    MyLineEdit *logedit_pattern_line_trap_2_falloff_sharpness;
    MyLineEdit *logedit_pattern_line_trap_2_segment_half_length;
    QLabel *label_pattern_line_2_glow;
    MyLineEdit *logedit_pattern_line_trap_2_glow_spread;
    MyComboBox *comboBox_pattern_line_trap_2_falloff_profile;
    QLabel *label_pattern_line_2_side;
    MyComboBox *comboBox_pattern_line_trap_2_edge_side;
    QPushButton *pushButton_pattern_line_trap_2_place_surface;
    QPushButton *pushButton_pattern_line_trap_2_place_target;
    MyGroupBox *groupCheck_pattern_line_trap_3_enabled;
    QGridLayout *gridLayout_pattern_line_3;
    QLabel *label_pattern_line_3_pos;
    MyLineEdit *vect3_pattern_line_trap_3_position_x;
    MyLineEdit *vect3_pattern_line_trap_3_position_y;
    MyLineEdit *vect3_pattern_line_trap_3_position_z;
    QLabel *label_pattern_line_3_rot;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_3_rotation_x;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_3_rotation_y;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_3_rotation_z;
    QLabel *label_pattern_line_3_radius;
    MyLineEdit *logedit_pattern_line_trap_3_radius;
    MyLineEdit *logedit_pattern_line_trap_3_thickness;
    MyLineEdit *logedit_pattern_line_trap_3_edge_softness;
    MyLineEdit *logedit_pattern_line_trap_3_max_distance;
    QLabel *label_pattern_line_3_scale;
    MyLineEdit *logedit_pattern_line_trap_3_scale;
    MyLineEdit *logedit_pattern_line_trap_3_relative_thickness;
    QLabel *label_pattern_line_3_int;
    MyLineEdit *logedit_pattern_line_trap_3_intensity;
    MyColorButton *colorButton_pattern_line_trap_3_color;
    MyColorButton *colorButton_pattern_line_trap_3_color_2;
    MyColorButton *colorButton_pattern_line_trap_3_color_3;
    QLabel *label_pattern_line_3_shape;
    MyComboBox *comboBox_pattern_line_trap_3_shape;
    QLabel *label_pattern_line_3_shape_aux;
    MyLineEdit *logedit_pattern_line_trap_3_shape_aux;
    QLabel *label_pattern_line_3_sharp_seg;
    MyLineEdit *logedit_pattern_line_trap_3_falloff_sharpness;
    MyLineEdit *logedit_pattern_line_trap_3_segment_half_length;
    QLabel *label_pattern_line_3_glow;
    MyLineEdit *logedit_pattern_line_trap_3_glow_spread;
    MyComboBox *comboBox_pattern_line_trap_3_falloff_profile;
    QLabel *label_pattern_line_3_side;
    MyComboBox *comboBox_pattern_line_trap_3_edge_side;
    QPushButton *pushButton_pattern_line_trap_3_place_surface;
    QPushButton *pushButton_pattern_line_trap_3_place_target;
    MyGroupBox *groupCheck_pattern_line_trap_4_enabled;
    QGridLayout *gridLayout_pattern_line_4;
    QLabel *label_pattern_line_4_pos;
    MyLineEdit *vect3_pattern_line_trap_4_position_x;
    MyLineEdit *vect3_pattern_line_trap_4_position_y;
    MyLineEdit *vect3_pattern_line_trap_4_position_z;
    QLabel *label_pattern_line_4_rot;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_4_rotation_x;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_4_rotation_y;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_4_rotation_z;
    QLabel *label_pattern_line_4_radius;
    MyLineEdit *logedit_pattern_line_trap_4_radius;
    MyLineEdit *logedit_pattern_line_trap_4_thickness;
    MyLineEdit *logedit_pattern_line_trap_4_edge_softness;
    MyLineEdit *logedit_pattern_line_trap_4_max_distance;
    QLabel *label_pattern_line_4_scale;
    MyLineEdit *logedit_pattern_line_trap_4_scale;
    MyLineEdit *logedit_pattern_line_trap_4_relative_thickness;
    QLabel *label_pattern_line_4_int;
    MyLineEdit *logedit_pattern_line_trap_4_intensity;
    MyColorButton *colorButton_pattern_line_trap_4_color;
    MyColorButton *colorButton_pattern_line_trap_4_color_2;
    MyColorButton *colorButton_pattern_line_trap_4_color_3;
    QLabel *label_pattern_line_4_shape;
    MyComboBox *comboBox_pattern_line_trap_4_shape;
    QLabel *label_pattern_line_4_shape_aux;
    MyLineEdit *logedit_pattern_line_trap_4_shape_aux;
    QLabel *label_pattern_line_4_sharp_seg;
    MyLineEdit *logedit_pattern_line_trap_4_falloff_sharpness;
    MyLineEdit *logedit_pattern_line_trap_4_segment_half_length;
    QLabel *label_pattern_line_4_glow;
    MyLineEdit *logedit_pattern_line_trap_4_glow_spread;
    MyComboBox *comboBox_pattern_line_trap_4_falloff_profile;
    QLabel *label_pattern_line_4_side;
    MyComboBox *comboBox_pattern_line_trap_4_edge_side;
    QPushButton *pushButton_pattern_line_trap_4_place_surface;
    QPushButton *pushButton_pattern_line_trap_4_place_target;
    MyGroupBox *groupCheck_pattern_line_trap_5_enabled;
    QGridLayout *gridLayout_pattern_line_5;
    QLabel *label_pattern_line_5_pos;
    MyLineEdit *vect3_pattern_line_trap_5_position_x;
    MyLineEdit *vect3_pattern_line_trap_5_position_y;
    MyLineEdit *vect3_pattern_line_trap_5_position_z;
    QLabel *label_pattern_line_5_rot;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_5_rotation_x;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_5_rotation_y;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_5_rotation_z;
    QLabel *label_pattern_line_5_radius;
    MyLineEdit *logedit_pattern_line_trap_5_radius;
    MyLineEdit *logedit_pattern_line_trap_5_thickness;
    MyLineEdit *logedit_pattern_line_trap_5_edge_softness;
    MyLineEdit *logedit_pattern_line_trap_5_max_distance;
    QLabel *label_pattern_line_5_scale;
    MyLineEdit *logedit_pattern_line_trap_5_scale;
    MyLineEdit *logedit_pattern_line_trap_5_relative_thickness;
    QLabel *label_pattern_line_5_int;
    MyLineEdit *logedit_pattern_line_trap_5_intensity;
    MyColorButton *colorButton_pattern_line_trap_5_color;
    MyColorButton *colorButton_pattern_line_trap_5_color_2;
    MyColorButton *colorButton_pattern_line_trap_5_color_3;
    QLabel *label_pattern_line_5_shape;
    MyComboBox *comboBox_pattern_line_trap_5_shape;
    QLabel *label_pattern_line_5_shape_aux;
    MyLineEdit *logedit_pattern_line_trap_5_shape_aux;
    QLabel *label_pattern_line_5_sharp_seg;
    MyLineEdit *logedit_pattern_line_trap_5_falloff_sharpness;
    MyLineEdit *logedit_pattern_line_trap_5_segment_half_length;
    QLabel *label_pattern_line_5_glow;
    MyLineEdit *logedit_pattern_line_trap_5_glow_spread;
    MyComboBox *comboBox_pattern_line_trap_5_falloff_profile;
    QLabel *label_pattern_line_5_side;
    MyComboBox *comboBox_pattern_line_trap_5_edge_side;
    QPushButton *pushButton_pattern_line_trap_5_place_surface;
    QPushButton *pushButton_pattern_line_trap_5_place_target;
    MyGroupBox *groupCheck_pattern_line_trap_6_enabled;
    QGridLayout *gridLayout_pattern_line_6;
    QLabel *label_pattern_line_6_pos;
    MyLineEdit *vect3_pattern_line_trap_6_position_x;
    MyLineEdit *vect3_pattern_line_trap_6_position_y;
    MyLineEdit *vect3_pattern_line_trap_6_position_z;
    QLabel *label_pattern_line_6_rot;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_6_rotation_x;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_6_rotation_y;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_6_rotation_z;
    QLabel *label_pattern_line_6_radius;
    MyLineEdit *logedit_pattern_line_trap_6_radius;
    MyLineEdit *logedit_pattern_line_trap_6_thickness;
    MyLineEdit *logedit_pattern_line_trap_6_edge_softness;
    MyLineEdit *logedit_pattern_line_trap_6_max_distance;
    QLabel *label_pattern_line_6_scale;
    MyLineEdit *logedit_pattern_line_trap_6_scale;
    MyLineEdit *logedit_pattern_line_trap_6_relative_thickness;
    QLabel *label_pattern_line_6_int;
    MyLineEdit *logedit_pattern_line_trap_6_intensity;
    MyColorButton *colorButton_pattern_line_trap_6_color;
    MyColorButton *colorButton_pattern_line_trap_6_color_2;
    MyColorButton *colorButton_pattern_line_trap_6_color_3;
    QLabel *label_pattern_line_6_shape;
    MyComboBox *comboBox_pattern_line_trap_6_shape;
    QLabel *label_pattern_line_6_shape_aux;
    MyLineEdit *logedit_pattern_line_trap_6_shape_aux;
    QLabel *label_pattern_line_6_sharp_seg;
    MyLineEdit *logedit_pattern_line_trap_6_falloff_sharpness;
    MyLineEdit *logedit_pattern_line_trap_6_segment_half_length;
    QLabel *label_pattern_line_6_glow;
    MyLineEdit *logedit_pattern_line_trap_6_glow_spread;
    MyComboBox *comboBox_pattern_line_trap_6_falloff_profile;
    QLabel *label_pattern_line_6_side;
    MyComboBox *comboBox_pattern_line_trap_6_edge_side;
    QPushButton *pushButton_pattern_line_trap_6_place_surface;
    QPushButton *pushButton_pattern_line_trap_6_place_target;
    MyGroupBox *groupCheck_pattern_line_trap_7_enabled;
    QGridLayout *gridLayout_pattern_line_7;
    QLabel *label_pattern_line_7_pos;
    MyLineEdit *vect3_pattern_line_trap_7_position_x;
    MyLineEdit *vect3_pattern_line_trap_7_position_y;
    MyLineEdit *vect3_pattern_line_trap_7_position_z;
    QLabel *label_pattern_line_7_rot;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_7_rotation_x;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_7_rotation_y;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_7_rotation_z;
    QLabel *label_pattern_line_7_radius;
    MyLineEdit *logedit_pattern_line_trap_7_radius;
    MyLineEdit *logedit_pattern_line_trap_7_thickness;
    MyLineEdit *logedit_pattern_line_trap_7_edge_softness;
    MyLineEdit *logedit_pattern_line_trap_7_max_distance;
    QLabel *label_pattern_line_7_scale;
    MyLineEdit *logedit_pattern_line_trap_7_scale;
    MyLineEdit *logedit_pattern_line_trap_7_relative_thickness;
    QLabel *label_pattern_line_7_int;
    MyLineEdit *logedit_pattern_line_trap_7_intensity;
    MyColorButton *colorButton_pattern_line_trap_7_color;
    MyColorButton *colorButton_pattern_line_trap_7_color_2;
    MyColorButton *colorButton_pattern_line_trap_7_color_3;
    QLabel *label_pattern_line_7_shape;
    MyComboBox *comboBox_pattern_line_trap_7_shape;
    QLabel *label_pattern_line_7_shape_aux;
    MyLineEdit *logedit_pattern_line_trap_7_shape_aux;
    QLabel *label_pattern_line_7_sharp_seg;
    MyLineEdit *logedit_pattern_line_trap_7_falloff_sharpness;
    MyLineEdit *logedit_pattern_line_trap_7_segment_half_length;
    QLabel *label_pattern_line_7_glow;
    MyLineEdit *logedit_pattern_line_trap_7_glow_spread;
    MyComboBox *comboBox_pattern_line_trap_7_falloff_profile;
    QLabel *label_pattern_line_7_side;
    MyComboBox *comboBox_pattern_line_trap_7_edge_side;
    QPushButton *pushButton_pattern_line_trap_7_place_surface;
    QPushButton *pushButton_pattern_line_trap_7_place_target;
    MyGroupBox *groupCheck_pattern_line_trap_8_enabled;
    QGridLayout *gridLayout_pattern_line_8;
    QLabel *label_pattern_line_8_pos;
    MyLineEdit *vect3_pattern_line_trap_8_position_x;
    MyLineEdit *vect3_pattern_line_trap_8_position_y;
    MyLineEdit *vect3_pattern_line_trap_8_position_z;
    QLabel *label_pattern_line_8_rot;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_8_rotation_x;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_8_rotation_y;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_8_rotation_z;
    QLabel *label_pattern_line_8_radius;
    MyLineEdit *logedit_pattern_line_trap_8_radius;
    MyLineEdit *logedit_pattern_line_trap_8_thickness;
    MyLineEdit *logedit_pattern_line_trap_8_edge_softness;
    MyLineEdit *logedit_pattern_line_trap_8_max_distance;
    QLabel *label_pattern_line_8_scale;
    MyLineEdit *logedit_pattern_line_trap_8_scale;
    MyLineEdit *logedit_pattern_line_trap_8_relative_thickness;
    QLabel *label_pattern_line_8_int;
    MyLineEdit *logedit_pattern_line_trap_8_intensity;
    MyColorButton *colorButton_pattern_line_trap_8_color;
    MyColorButton *colorButton_pattern_line_trap_8_color_2;
    MyColorButton *colorButton_pattern_line_trap_8_color_3;
    QLabel *label_pattern_line_8_shape;
    MyComboBox *comboBox_pattern_line_trap_8_shape;
    QLabel *label_pattern_line_8_shape_aux;
    MyLineEdit *logedit_pattern_line_trap_8_shape_aux;
    QLabel *label_pattern_line_8_sharp_seg;
    MyLineEdit *logedit_pattern_line_trap_8_falloff_sharpness;
    MyLineEdit *logedit_pattern_line_trap_8_segment_half_length;
    QLabel *label_pattern_line_8_glow;
    MyLineEdit *logedit_pattern_line_trap_8_glow_spread;
    MyComboBox *comboBox_pattern_line_trap_8_falloff_profile;
    QLabel *label_pattern_line_8_side;
    MyComboBox *comboBox_pattern_line_trap_8_edge_side;
    QPushButton *pushButton_pattern_line_trap_8_place_surface;
    QPushButton *pushButton_pattern_line_trap_8_place_target;
    MyGroupBox *groupCheck_pattern_line_trap_9_enabled;
    QGridLayout *gridLayout_pattern_line_9;
    QLabel *label_pattern_line_9_pos;
    MyLineEdit *vect3_pattern_line_trap_9_position_x;
    MyLineEdit *vect3_pattern_line_trap_9_position_y;
    MyLineEdit *vect3_pattern_line_trap_9_position_z;
    QLabel *label_pattern_line_9_rot;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_9_rotation_x;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_9_rotation_y;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_9_rotation_z;
    QLabel *label_pattern_line_9_radius;
    MyLineEdit *logedit_pattern_line_trap_9_radius;
    MyLineEdit *logedit_pattern_line_trap_9_thickness;
    MyLineEdit *logedit_pattern_line_trap_9_edge_softness;
    MyLineEdit *logedit_pattern_line_trap_9_max_distance;
    QLabel *label_pattern_line_9_scale;
    MyLineEdit *logedit_pattern_line_trap_9_scale;
    MyLineEdit *logedit_pattern_line_trap_9_relative_thickness;
    QLabel *label_pattern_line_9_int;
    MyLineEdit *logedit_pattern_line_trap_9_intensity;
    MyColorButton *colorButton_pattern_line_trap_9_color;
    MyColorButton *colorButton_pattern_line_trap_9_color_2;
    MyColorButton *colorButton_pattern_line_trap_9_color_3;
    QLabel *label_pattern_line_9_shape;
    MyComboBox *comboBox_pattern_line_trap_9_shape;
    QLabel *label_pattern_line_9_shape_aux;
    MyLineEdit *logedit_pattern_line_trap_9_shape_aux;
    QLabel *label_pattern_line_9_sharp_seg;
    MyLineEdit *logedit_pattern_line_trap_9_falloff_sharpness;
    MyLineEdit *logedit_pattern_line_trap_9_segment_half_length;
    QLabel *label_pattern_line_9_glow;
    MyLineEdit *logedit_pattern_line_trap_9_glow_spread;
    MyComboBox *comboBox_pattern_line_trap_9_falloff_profile;
    QLabel *label_pattern_line_9_side;
    MyComboBox *comboBox_pattern_line_trap_9_edge_side;
    QPushButton *pushButton_pattern_line_trap_9_place_surface;
    QPushButton *pushButton_pattern_line_trap_9_place_target;
    MyGroupBox *groupCheck_pattern_line_trap_10_enabled;
    QGridLayout *gridLayout_pattern_line_10;
    QLabel *label_pattern_line_10_pos;
    MyLineEdit *vect3_pattern_line_trap_10_position_x;
    MyLineEdit *vect3_pattern_line_trap_10_position_y;
    MyLineEdit *vect3_pattern_line_trap_10_position_z;
    QLabel *label_pattern_line_10_rot;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_10_rotation_x;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_10_rotation_y;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_10_rotation_z;
    QLabel *label_pattern_line_10_radius;
    MyLineEdit *logedit_pattern_line_trap_10_radius;
    MyLineEdit *logedit_pattern_line_trap_10_thickness;
    MyLineEdit *logedit_pattern_line_trap_10_edge_softness;
    MyLineEdit *logedit_pattern_line_trap_10_max_distance;
    QLabel *label_pattern_line_10_scale;
    MyLineEdit *logedit_pattern_line_trap_10_scale;
    MyLineEdit *logedit_pattern_line_trap_10_relative_thickness;
    QLabel *label_pattern_line_10_int;
    MyLineEdit *logedit_pattern_line_trap_10_intensity;
    MyColorButton *colorButton_pattern_line_trap_10_color;
    MyColorButton *colorButton_pattern_line_trap_10_color_2;
    MyColorButton *colorButton_pattern_line_trap_10_color_3;
    QLabel *label_pattern_line_10_shape;
    MyComboBox *comboBox_pattern_line_trap_10_shape;
    QLabel *label_pattern_line_10_shape_aux;
    MyLineEdit *logedit_pattern_line_trap_10_shape_aux;
    QLabel *label_pattern_line_10_sharp_seg;
    MyLineEdit *logedit_pattern_line_trap_10_falloff_sharpness;
    MyLineEdit *logedit_pattern_line_trap_10_segment_half_length;
    QLabel *label_pattern_line_10_glow;
    MyLineEdit *logedit_pattern_line_trap_10_glow_spread;
    MyComboBox *comboBox_pattern_line_trap_10_falloff_profile;
    QLabel *label_pattern_line_10_side;
    MyComboBox *comboBox_pattern_line_trap_10_edge_side;
    QPushButton *pushButton_pattern_line_trap_10_place_surface;
    QPushButton *pushButton_pattern_line_trap_10_place_target;
    MyGroupBox *groupCheck_pattern_line_trap_11_enabled;
    QGridLayout *gridLayout_pattern_line_11;
    QLabel *label_pattern_line_11_pos;
    MyLineEdit *vect3_pattern_line_trap_11_position_x;
    MyLineEdit *vect3_pattern_line_trap_11_position_y;
    MyLineEdit *vect3_pattern_line_trap_11_position_z;
    QLabel *label_pattern_line_11_rot;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_11_rotation_x;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_11_rotation_y;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_11_rotation_z;
    QLabel *label_pattern_line_11_radius;
    MyLineEdit *logedit_pattern_line_trap_11_radius;
    MyLineEdit *logedit_pattern_line_trap_11_thickness;
    MyLineEdit *logedit_pattern_line_trap_11_edge_softness;
    MyLineEdit *logedit_pattern_line_trap_11_max_distance;
    QLabel *label_pattern_line_11_scale;
    MyLineEdit *logedit_pattern_line_trap_11_scale;
    MyLineEdit *logedit_pattern_line_trap_11_relative_thickness;
    QLabel *label_pattern_line_11_int;
    MyLineEdit *logedit_pattern_line_trap_11_intensity;
    MyColorButton *colorButton_pattern_line_trap_11_color;
    MyColorButton *colorButton_pattern_line_trap_11_color_2;
    MyColorButton *colorButton_pattern_line_trap_11_color_3;
    QLabel *label_pattern_line_11_shape;
    MyComboBox *comboBox_pattern_line_trap_11_shape;
    QLabel *label_pattern_line_11_shape_aux;
    MyLineEdit *logedit_pattern_line_trap_11_shape_aux;
    QLabel *label_pattern_line_11_sharp_seg;
    MyLineEdit *logedit_pattern_line_trap_11_falloff_sharpness;
    MyLineEdit *logedit_pattern_line_trap_11_segment_half_length;
    QLabel *label_pattern_line_11_glow;
    MyLineEdit *logedit_pattern_line_trap_11_glow_spread;
    MyComboBox *comboBox_pattern_line_trap_11_falloff_profile;
    QLabel *label_pattern_line_11_side;
    MyComboBox *comboBox_pattern_line_trap_11_edge_side;
    QPushButton *pushButton_pattern_line_trap_11_place_surface;
    QPushButton *pushButton_pattern_line_trap_11_place_target;
    MyGroupBox *groupCheck_pattern_line_trap_12_enabled;
    QGridLayout *gridLayout_pattern_line_12;
    QLabel *label_pattern_line_12_pos;
    MyLineEdit *vect3_pattern_line_trap_12_position_x;
    MyLineEdit *vect3_pattern_line_trap_12_position_y;
    MyLineEdit *vect3_pattern_line_trap_12_position_z;
    QLabel *label_pattern_line_12_rot;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_12_rotation_x;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_12_rotation_y;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_12_rotation_z;
    QLabel *label_pattern_line_12_radius;
    MyLineEdit *logedit_pattern_line_trap_12_radius;
    MyLineEdit *logedit_pattern_line_trap_12_thickness;
    MyLineEdit *logedit_pattern_line_trap_12_edge_softness;
    MyLineEdit *logedit_pattern_line_trap_12_max_distance;
    QLabel *label_pattern_line_12_scale;
    MyLineEdit *logedit_pattern_line_trap_12_scale;
    MyLineEdit *logedit_pattern_line_trap_12_relative_thickness;
    QLabel *label_pattern_line_12_int;
    MyLineEdit *logedit_pattern_line_trap_12_intensity;
    MyColorButton *colorButton_pattern_line_trap_12_color;
    MyColorButton *colorButton_pattern_line_trap_12_color_2;
    MyColorButton *colorButton_pattern_line_trap_12_color_3;
    QLabel *label_pattern_line_12_shape;
    MyComboBox *comboBox_pattern_line_trap_12_shape;
    QLabel *label_pattern_line_12_shape_aux;
    MyLineEdit *logedit_pattern_line_trap_12_shape_aux;
    QLabel *label_pattern_line_12_sharp_seg;
    MyLineEdit *logedit_pattern_line_trap_12_falloff_sharpness;
    MyLineEdit *logedit_pattern_line_trap_12_segment_half_length;
    QLabel *label_pattern_line_12_glow;
    MyLineEdit *logedit_pattern_line_trap_12_glow_spread;
    MyComboBox *comboBox_pattern_line_trap_12_falloff_profile;
    QLabel *label_pattern_line_12_side;
    MyComboBox *comboBox_pattern_line_trap_12_edge_side;
    QPushButton *pushButton_pattern_line_trap_12_place_surface;
    QPushButton *pushButton_pattern_line_trap_12_place_target;
    MyGroupBox *groupCheck_pattern_line_trap_13_enabled;
    QGridLayout *gridLayout_pattern_line_13;
    QLabel *label_pattern_line_13_pos;
    MyLineEdit *vect3_pattern_line_trap_13_position_x;
    MyLineEdit *vect3_pattern_line_trap_13_position_y;
    MyLineEdit *vect3_pattern_line_trap_13_position_z;
    QLabel *label_pattern_line_13_rot;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_13_rotation_x;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_13_rotation_y;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_13_rotation_z;
    QLabel *label_pattern_line_13_radius;
    MyLineEdit *logedit_pattern_line_trap_13_radius;
    MyLineEdit *logedit_pattern_line_trap_13_thickness;
    MyLineEdit *logedit_pattern_line_trap_13_edge_softness;
    MyLineEdit *logedit_pattern_line_trap_13_max_distance;
    QLabel *label_pattern_line_13_scale;
    MyLineEdit *logedit_pattern_line_trap_13_scale;
    MyLineEdit *logedit_pattern_line_trap_13_relative_thickness;
    QLabel *label_pattern_line_13_int;
    MyLineEdit *logedit_pattern_line_trap_13_intensity;
    MyColorButton *colorButton_pattern_line_trap_13_color;
    MyColorButton *colorButton_pattern_line_trap_13_color_2;
    MyColorButton *colorButton_pattern_line_trap_13_color_3;
    QLabel *label_pattern_line_13_shape;
    MyComboBox *comboBox_pattern_line_trap_13_shape;
    QLabel *label_pattern_line_13_shape_aux;
    MyLineEdit *logedit_pattern_line_trap_13_shape_aux;
    QLabel *label_pattern_line_13_sharp_seg;
    MyLineEdit *logedit_pattern_line_trap_13_falloff_sharpness;
    MyLineEdit *logedit_pattern_line_trap_13_segment_half_length;
    QLabel *label_pattern_line_13_glow;
    MyLineEdit *logedit_pattern_line_trap_13_glow_spread;
    MyComboBox *comboBox_pattern_line_trap_13_falloff_profile;
    QLabel *label_pattern_line_13_side;
    MyComboBox *comboBox_pattern_line_trap_13_edge_side;
    QPushButton *pushButton_pattern_line_trap_13_place_surface;
    QPushButton *pushButton_pattern_line_trap_13_place_target;
    MyGroupBox *groupCheck_pattern_line_trap_14_enabled;
    QGridLayout *gridLayout_pattern_line_14;
    QLabel *label_pattern_line_14_pos;
    MyLineEdit *vect3_pattern_line_trap_14_position_x;
    MyLineEdit *vect3_pattern_line_trap_14_position_y;
    MyLineEdit *vect3_pattern_line_trap_14_position_z;
    QLabel *label_pattern_line_14_rot;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_14_rotation_x;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_14_rotation_y;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_14_rotation_z;
    QLabel *label_pattern_line_14_radius;
    MyLineEdit *logedit_pattern_line_trap_14_radius;
    MyLineEdit *logedit_pattern_line_trap_14_thickness;
    MyLineEdit *logedit_pattern_line_trap_14_edge_softness;
    MyLineEdit *logedit_pattern_line_trap_14_max_distance;
    QLabel *label_pattern_line_14_scale;
    MyLineEdit *logedit_pattern_line_trap_14_scale;
    MyLineEdit *logedit_pattern_line_trap_14_relative_thickness;
    QLabel *label_pattern_line_14_int;
    MyLineEdit *logedit_pattern_line_trap_14_intensity;
    MyColorButton *colorButton_pattern_line_trap_14_color;
    MyColorButton *colorButton_pattern_line_trap_14_color_2;
    MyColorButton *colorButton_pattern_line_trap_14_color_3;
    QLabel *label_pattern_line_14_shape;
    MyComboBox *comboBox_pattern_line_trap_14_shape;
    QLabel *label_pattern_line_14_shape_aux;
    MyLineEdit *logedit_pattern_line_trap_14_shape_aux;
    QLabel *label_pattern_line_14_sharp_seg;
    MyLineEdit *logedit_pattern_line_trap_14_falloff_sharpness;
    MyLineEdit *logedit_pattern_line_trap_14_segment_half_length;
    QLabel *label_pattern_line_14_glow;
    MyLineEdit *logedit_pattern_line_trap_14_glow_spread;
    MyComboBox *comboBox_pattern_line_trap_14_falloff_profile;
    QLabel *label_pattern_line_14_side;
    MyComboBox *comboBox_pattern_line_trap_14_edge_side;
    QPushButton *pushButton_pattern_line_trap_14_place_surface;
    QPushButton *pushButton_pattern_line_trap_14_place_target;
    MyGroupBox *groupCheck_pattern_line_trap_15_enabled;
    QGridLayout *gridLayout_pattern_line_15;
    QLabel *label_pattern_line_15_pos;
    MyLineEdit *vect3_pattern_line_trap_15_position_x;
    MyLineEdit *vect3_pattern_line_trap_15_position_y;
    MyLineEdit *vect3_pattern_line_trap_15_position_z;
    QLabel *label_pattern_line_15_rot;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_15_rotation_x;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_15_rotation_y;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_15_rotation_z;
    QLabel *label_pattern_line_15_radius;
    MyLineEdit *logedit_pattern_line_trap_15_radius;
    MyLineEdit *logedit_pattern_line_trap_15_thickness;
    MyLineEdit *logedit_pattern_line_trap_15_edge_softness;
    MyLineEdit *logedit_pattern_line_trap_15_max_distance;
    QLabel *label_pattern_line_15_scale;
    MyLineEdit *logedit_pattern_line_trap_15_scale;
    MyLineEdit *logedit_pattern_line_trap_15_relative_thickness;
    QLabel *label_pattern_line_15_int;
    MyLineEdit *logedit_pattern_line_trap_15_intensity;
    MyColorButton *colorButton_pattern_line_trap_15_color;
    MyColorButton *colorButton_pattern_line_trap_15_color_2;
    MyColorButton *colorButton_pattern_line_trap_15_color_3;
    QLabel *label_pattern_line_15_shape;
    MyComboBox *comboBox_pattern_line_trap_15_shape;
    QLabel *label_pattern_line_15_shape_aux;
    MyLineEdit *logedit_pattern_line_trap_15_shape_aux;
    QLabel *label_pattern_line_15_sharp_seg;
    MyLineEdit *logedit_pattern_line_trap_15_falloff_sharpness;
    MyLineEdit *logedit_pattern_line_trap_15_segment_half_length;
    QLabel *label_pattern_line_15_glow;
    MyLineEdit *logedit_pattern_line_trap_15_glow_spread;
    MyComboBox *comboBox_pattern_line_trap_15_falloff_profile;
    QLabel *label_pattern_line_15_side;
    MyComboBox *comboBox_pattern_line_trap_15_edge_side;
    QPushButton *pushButton_pattern_line_trap_15_place_surface;
    QPushButton *pushButton_pattern_line_trap_15_place_target;
    MyGroupBox *groupCheck_pattern_line_trap_16_enabled;
    QGridLayout *gridLayout_pattern_line_16;
    QLabel *label_pattern_line_16_pos;
    MyLineEdit *vect3_pattern_line_trap_16_position_x;
    MyLineEdit *vect3_pattern_line_trap_16_position_y;
    MyLineEdit *vect3_pattern_line_trap_16_position_z;
    QLabel *label_pattern_line_16_rot;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_16_rotation_x;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_16_rotation_y;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_16_rotation_z;
    QLabel *label_pattern_line_16_radius;
    MyLineEdit *logedit_pattern_line_trap_16_radius;
    MyLineEdit *logedit_pattern_line_trap_16_thickness;
    MyLineEdit *logedit_pattern_line_trap_16_edge_softness;
    MyLineEdit *logedit_pattern_line_trap_16_max_distance;
    QLabel *label_pattern_line_16_scale;
    MyLineEdit *logedit_pattern_line_trap_16_scale;
    MyLineEdit *logedit_pattern_line_trap_16_relative_thickness;
    QLabel *label_pattern_line_16_int;
    MyLineEdit *logedit_pattern_line_trap_16_intensity;
    MyColorButton *colorButton_pattern_line_trap_16_color;
    MyColorButton *colorButton_pattern_line_trap_16_color_2;
    MyColorButton *colorButton_pattern_line_trap_16_color_3;
    QLabel *label_pattern_line_16_shape;
    MyComboBox *comboBox_pattern_line_trap_16_shape;
    QLabel *label_pattern_line_16_shape_aux;
    MyLineEdit *logedit_pattern_line_trap_16_shape_aux;
    QLabel *label_pattern_line_16_sharp_seg;
    MyLineEdit *logedit_pattern_line_trap_16_falloff_sharpness;
    MyLineEdit *logedit_pattern_line_trap_16_segment_half_length;
    QLabel *label_pattern_line_16_glow;
    MyLineEdit *logedit_pattern_line_trap_16_glow_spread;
    MyComboBox *comboBox_pattern_line_trap_16_falloff_profile;
    QLabel *label_pattern_line_16_side;
    MyComboBox *comboBox_pattern_line_trap_16_edge_side;
    QPushButton *pushButton_pattern_line_trap_16_place_surface;
    QPushButton *pushButton_pattern_line_trap_16_place_target;
    MyGroupBox *groupCheck_pattern_line_trap_17_enabled;
    QGridLayout *gridLayout_pattern_line_17;
    QLabel *label_pattern_line_17_pos;
    MyLineEdit *vect3_pattern_line_trap_17_position_x;
    MyLineEdit *vect3_pattern_line_trap_17_position_y;
    MyLineEdit *vect3_pattern_line_trap_17_position_z;
    QLabel *label_pattern_line_17_rot;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_17_rotation_x;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_17_rotation_y;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_17_rotation_z;
    QLabel *label_pattern_line_17_radius;
    MyLineEdit *logedit_pattern_line_trap_17_radius;
    MyLineEdit *logedit_pattern_line_trap_17_thickness;
    MyLineEdit *logedit_pattern_line_trap_17_edge_softness;
    MyLineEdit *logedit_pattern_line_trap_17_max_distance;
    QLabel *label_pattern_line_17_scale;
    MyLineEdit *logedit_pattern_line_trap_17_scale;
    MyLineEdit *logedit_pattern_line_trap_17_relative_thickness;
    QLabel *label_pattern_line_17_int;
    MyLineEdit *logedit_pattern_line_trap_17_intensity;
    MyColorButton *colorButton_pattern_line_trap_17_color;
    MyColorButton *colorButton_pattern_line_trap_17_color_2;
    MyColorButton *colorButton_pattern_line_trap_17_color_3;
    QLabel *label_pattern_line_17_shape;
    MyComboBox *comboBox_pattern_line_trap_17_shape;
    QLabel *label_pattern_line_17_shape_aux;
    MyLineEdit *logedit_pattern_line_trap_17_shape_aux;
    QLabel *label_pattern_line_17_sharp_seg;
    MyLineEdit *logedit_pattern_line_trap_17_falloff_sharpness;
    MyLineEdit *logedit_pattern_line_trap_17_segment_half_length;
    QLabel *label_pattern_line_17_glow;
    MyLineEdit *logedit_pattern_line_trap_17_glow_spread;
    MyComboBox *comboBox_pattern_line_trap_17_falloff_profile;
    QLabel *label_pattern_line_17_side;
    MyComboBox *comboBox_pattern_line_trap_17_edge_side;
    QPushButton *pushButton_pattern_line_trap_17_place_surface;
    QPushButton *pushButton_pattern_line_trap_17_place_target;
    MyGroupBox *groupCheck_pattern_line_trap_18_enabled;
    QGridLayout *gridLayout_pattern_line_18;
    QLabel *label_pattern_line_18_pos;
    MyLineEdit *vect3_pattern_line_trap_18_position_x;
    MyLineEdit *vect3_pattern_line_trap_18_position_y;
    MyLineEdit *vect3_pattern_line_trap_18_position_z;
    QLabel *label_pattern_line_18_rot;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_18_rotation_x;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_18_rotation_y;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_18_rotation_z;
    QLabel *label_pattern_line_18_radius;
    MyLineEdit *logedit_pattern_line_trap_18_radius;
    MyLineEdit *logedit_pattern_line_trap_18_thickness;
    MyLineEdit *logedit_pattern_line_trap_18_edge_softness;
    MyLineEdit *logedit_pattern_line_trap_18_max_distance;
    QLabel *label_pattern_line_18_scale;
    MyLineEdit *logedit_pattern_line_trap_18_scale;
    MyLineEdit *logedit_pattern_line_trap_18_relative_thickness;
    QLabel *label_pattern_line_18_int;
    MyLineEdit *logedit_pattern_line_trap_18_intensity;
    MyColorButton *colorButton_pattern_line_trap_18_color;
    MyColorButton *colorButton_pattern_line_trap_18_color_2;
    MyColorButton *colorButton_pattern_line_trap_18_color_3;
    QLabel *label_pattern_line_18_shape;
    MyComboBox *comboBox_pattern_line_trap_18_shape;
    QLabel *label_pattern_line_18_shape_aux;
    MyLineEdit *logedit_pattern_line_trap_18_shape_aux;
    QLabel *label_pattern_line_18_sharp_seg;
    MyLineEdit *logedit_pattern_line_trap_18_falloff_sharpness;
    MyLineEdit *logedit_pattern_line_trap_18_segment_half_length;
    QLabel *label_pattern_line_18_glow;
    MyLineEdit *logedit_pattern_line_trap_18_glow_spread;
    MyComboBox *comboBox_pattern_line_trap_18_falloff_profile;
    QLabel *label_pattern_line_18_side;
    MyComboBox *comboBox_pattern_line_trap_18_edge_side;
    QPushButton *pushButton_pattern_line_trap_18_place_surface;
    QPushButton *pushButton_pattern_line_trap_18_place_target;
    MyGroupBox *groupCheck_pattern_line_trap_19_enabled;
    QGridLayout *gridLayout_pattern_line_19;
    QLabel *label_pattern_line_19_pos;
    MyLineEdit *vect3_pattern_line_trap_19_position_x;
    MyLineEdit *vect3_pattern_line_trap_19_position_y;
    MyLineEdit *vect3_pattern_line_trap_19_position_z;
    QLabel *label_pattern_line_19_rot;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_19_rotation_x;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_19_rotation_y;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_19_rotation_z;
    QLabel *label_pattern_line_19_radius;
    MyLineEdit *logedit_pattern_line_trap_19_radius;
    MyLineEdit *logedit_pattern_line_trap_19_thickness;
    MyLineEdit *logedit_pattern_line_trap_19_edge_softness;
    MyLineEdit *logedit_pattern_line_trap_19_max_distance;
    QLabel *label_pattern_line_19_scale;
    MyLineEdit *logedit_pattern_line_trap_19_scale;
    MyLineEdit *logedit_pattern_line_trap_19_relative_thickness;
    QLabel *label_pattern_line_19_int;
    MyLineEdit *logedit_pattern_line_trap_19_intensity;
    MyColorButton *colorButton_pattern_line_trap_19_color;
    MyColorButton *colorButton_pattern_line_trap_19_color_2;
    MyColorButton *colorButton_pattern_line_trap_19_color_3;
    QLabel *label_pattern_line_19_shape;
    MyComboBox *comboBox_pattern_line_trap_19_shape;
    QLabel *label_pattern_line_19_shape_aux;
    MyLineEdit *logedit_pattern_line_trap_19_shape_aux;
    QLabel *label_pattern_line_19_sharp_seg;
    MyLineEdit *logedit_pattern_line_trap_19_falloff_sharpness;
    MyLineEdit *logedit_pattern_line_trap_19_segment_half_length;
    QLabel *label_pattern_line_19_glow;
    MyLineEdit *logedit_pattern_line_trap_19_glow_spread;
    MyComboBox *comboBox_pattern_line_trap_19_falloff_profile;
    QLabel *label_pattern_line_19_side;
    MyComboBox *comboBox_pattern_line_trap_19_edge_side;
    QPushButton *pushButton_pattern_line_trap_19_place_surface;
    QPushButton *pushButton_pattern_line_trap_19_place_target;
    MyGroupBox *groupCheck_pattern_line_trap_20_enabled;
    QGridLayout *gridLayout_pattern_line_20;
    QLabel *label_pattern_line_20_pos;
    MyLineEdit *vect3_pattern_line_trap_20_position_x;
    MyLineEdit *vect3_pattern_line_trap_20_position_y;
    MyLineEdit *vect3_pattern_line_trap_20_position_z;
    QLabel *label_pattern_line_20_rot;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_20_rotation_x;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_20_rotation_y;
    MyDoubleSpinBox *spinboxd3_pattern_line_trap_20_rotation_z;
    QLabel *label_pattern_line_20_radius;
    MyLineEdit *logedit_pattern_line_trap_20_radius;
    MyLineEdit *logedit_pattern_line_trap_20_thickness;
    MyLineEdit *logedit_pattern_line_trap_20_edge_softness;
    MyLineEdit *logedit_pattern_line_trap_20_max_distance;
    QLabel *label_pattern_line_20_scale;
    MyLineEdit *logedit_pattern_line_trap_20_scale;
    MyLineEdit *logedit_pattern_line_trap_20_relative_thickness;
    QLabel *label_pattern_line_20_int;
    MyLineEdit *logedit_pattern_line_trap_20_intensity;
    MyColorButton *colorButton_pattern_line_trap_20_color;
    MyColorButton *colorButton_pattern_line_trap_20_color_2;
    MyColorButton *colorButton_pattern_line_trap_20_color_3;
    QLabel *label_pattern_line_20_shape;
    MyComboBox *comboBox_pattern_line_trap_20_shape;
    QLabel *label_pattern_line_20_shape_aux;
    MyLineEdit *logedit_pattern_line_trap_20_shape_aux;
    QLabel *label_pattern_line_20_sharp_seg;
    MyLineEdit *logedit_pattern_line_trap_20_falloff_sharpness;
    MyLineEdit *logedit_pattern_line_trap_20_segment_half_length;
    QLabel *label_pattern_line_20_glow;
    MyLineEdit *logedit_pattern_line_trap_20_glow_spread;
    MyComboBox *comboBox_pattern_line_trap_20_falloff_profile;
    QLabel *label_pattern_line_20_side;
    MyComboBox *comboBox_pattern_line_trap_20_edge_side;
    QPushButton *pushButton_pattern_line_trap_20_place_surface;
    QPushButton *pushButton_pattern_line_trap_20_place_target;

    void setupUi(QWidget *cPatternLinesTrapsPanel)
    {
        if (cPatternLinesTrapsPanel->objectName().isEmpty())
            cPatternLinesTrapsPanel->setObjectName(QString::fromUtf8("cPatternLinesTrapsPanel"));
        verticalLayout_pattern_traps_panel_root = new QVBoxLayout(cPatternLinesTrapsPanel);
        verticalLayout_pattern_traps_panel_root->setObjectName(QString::fromUtf8("verticalLayout_pattern_traps_panel_root"));
        verticalLayout_pattern_traps_panel_root->setContentsMargins(0, 0, 0, 0);
        scrollArea_pattern_line_traps_top = new QScrollArea(cPatternLinesTrapsPanel);
        scrollArea_pattern_line_traps_top->setObjectName(QString::fromUtf8("scrollArea_pattern_line_traps_top"));
        scrollArea_pattern_line_traps_top->setWidgetResizable(true);
        scrollArea_pattern_line_traps_top->setFrameShape(QFrame::NoFrame);
        scrollArea_pattern_line_traps_top->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollAreaWidgetContents_pattern_traps_top = new QWidget();
        scrollAreaWidgetContents_pattern_traps_top->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_pattern_traps_top"));
        scrollAreaWidgetContents_pattern_traps_top->setGeometry(QRect(0, 0, 460, 4800));
        verticalLayout_pattern_traps_dock_top = new QVBoxLayout(scrollAreaWidgetContents_pattern_traps_top);
        verticalLayout_pattern_traps_dock_top->setSpacing(2);
        verticalLayout_pattern_traps_dock_top->setObjectName(QString::fromUtf8("verticalLayout_pattern_traps_dock_top"));
        verticalLayout_pattern_traps_dock_top->setContentsMargins(2, 2, 2, 2);
        groupBox_pattern_line_traps = new QGroupBox(scrollAreaWidgetContents_pattern_traps_top);
        groupBox_pattern_line_traps->setObjectName(QString::fromUtf8("groupBox_pattern_line_traps"));
        verticalLayout_pattern_line_traps_outer = new QVBoxLayout(groupBox_pattern_line_traps);
        verticalLayout_pattern_line_traps_outer->setObjectName(QString::fromUtf8("verticalLayout_pattern_line_traps_outer"));
        checkBox_pattern_line_traps_enabled = new MyCheckBox(groupBox_pattern_line_traps);
        checkBox_pattern_line_traps_enabled->setObjectName(QString::fromUtf8("checkBox_pattern_line_traps_enabled"));

        verticalLayout_pattern_line_traps_outer->addWidget(checkBox_pattern_line_traps_enabled);

        checkBox_pattern_line_traps_overlay_visible = new MyCheckBox(groupBox_pattern_line_traps);
        checkBox_pattern_line_traps_overlay_visible->setObjectName(QString::fromUtf8("checkBox_pattern_line_traps_overlay_visible"));
        checkBox_pattern_line_traps_overlay_visible->setChecked(true);

        verticalLayout_pattern_line_traps_outer->addWidget(checkBox_pattern_line_traps_overlay_visible);

        horizontalLayout_pattern_batch = new QHBoxLayout();
        horizontalLayout_pattern_batch->setObjectName(QString::fromUtf8("horizontalLayout_pattern_batch"));
        pushButton_pattern_line_traps_enable_all = new QPushButton(groupBox_pattern_line_traps);
        pushButton_pattern_line_traps_enable_all->setObjectName(QString::fromUtf8("pushButton_pattern_line_traps_enable_all"));

        horizontalLayout_pattern_batch->addWidget(pushButton_pattern_line_traps_enable_all);

        pushButton_pattern_line_traps_disable_all = new QPushButton(groupBox_pattern_line_traps);
        pushButton_pattern_line_traps_disable_all->setObjectName(QString::fromUtf8("pushButton_pattern_line_traps_disable_all"));

        horizontalLayout_pattern_batch->addWidget(pushButton_pattern_line_traps_disable_all);

        pushButton_pattern_line_traps_solo_selected = new QPushButton(groupBox_pattern_line_traps);
        pushButton_pattern_line_traps_solo_selected->setObjectName(QString::fromUtf8("pushButton_pattern_line_traps_solo_selected"));

        horizontalLayout_pattern_batch->addWidget(pushButton_pattern_line_traps_solo_selected);

        horizontalSpacer_pattern_batch = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_pattern_batch->addItem(horizontalSpacer_pattern_batch);


        verticalLayout_pattern_line_traps_outer->addLayout(horizontalLayout_pattern_batch);

        horizontalLayout_pattern_global = new QHBoxLayout();
        horizontalLayout_pattern_global->setObjectName(QString::fromUtf8("horizontalLayout_pattern_global"));
        label_pattern_line_traps_combine_mode = new QLabel(groupBox_pattern_line_traps);
        label_pattern_line_traps_combine_mode->setObjectName(QString::fromUtf8("label_pattern_line_traps_combine_mode"));

        horizontalLayout_pattern_global->addWidget(label_pattern_line_traps_combine_mode);

        comboBox_pattern_line_traps_combine_mode = new MyComboBox(groupBox_pattern_line_traps);
        comboBox_pattern_line_traps_combine_mode->addItem(QString());
        comboBox_pattern_line_traps_combine_mode->addItem(QString());
        comboBox_pattern_line_traps_combine_mode->setObjectName(QString::fromUtf8("comboBox_pattern_line_traps_combine_mode"));

        horizontalLayout_pattern_global->addWidget(comboBox_pattern_line_traps_combine_mode);

        label_pattern_line_traps_coloring_mode = new QLabel(groupBox_pattern_line_traps);
        label_pattern_line_traps_coloring_mode->setObjectName(QString::fromUtf8("label_pattern_line_traps_coloring_mode"));

        horizontalLayout_pattern_global->addWidget(label_pattern_line_traps_coloring_mode);

        comboBox_pattern_line_traps_coloring_mode = new MyComboBox(groupBox_pattern_line_traps);
        comboBox_pattern_line_traps_coloring_mode->addItem(QString());
        comboBox_pattern_line_traps_coloring_mode->addItem(QString());
        comboBox_pattern_line_traps_coloring_mode->addItem(QString());
        comboBox_pattern_line_traps_coloring_mode->setObjectName(QString::fromUtf8("comboBox_pattern_line_traps_coloring_mode"));

        horizontalLayout_pattern_global->addWidget(comboBox_pattern_line_traps_coloring_mode);

        horizontalSpacer_pattern_global = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_pattern_global->addItem(horizontalSpacer_pattern_global);


        verticalLayout_pattern_line_traps_outer->addLayout(horizontalLayout_pattern_global);

        horizontalLayout_pattern_color_tune = new QHBoxLayout();
        horizontalLayout_pattern_color_tune->setObjectName(QString::fromUtf8("horizontalLayout_pattern_color_tune"));
        label_pattern_line_traps_coloring_speed = new QLabel(groupBox_pattern_line_traps);
        label_pattern_line_traps_coloring_speed->setObjectName(QString::fromUtf8("label_pattern_line_traps_coloring_speed"));

        horizontalLayout_pattern_color_tune->addWidget(label_pattern_line_traps_coloring_speed);

        logedit_pattern_line_traps_coloring_speed = new MyLineEdit(groupBox_pattern_line_traps);
        logedit_pattern_line_traps_coloring_speed->setObjectName(QString::fromUtf8("logedit_pattern_line_traps_coloring_speed"));

        horizontalLayout_pattern_color_tune->addWidget(logedit_pattern_line_traps_coloring_speed);

        label_pattern_line_traps_palette_offset = new QLabel(groupBox_pattern_line_traps);
        label_pattern_line_traps_palette_offset->setObjectName(QString::fromUtf8("label_pattern_line_traps_palette_offset"));

        horizontalLayout_pattern_color_tune->addWidget(label_pattern_line_traps_palette_offset);

        logedit_pattern_line_traps_palette_offset = new MyLineEdit(groupBox_pattern_line_traps);
        logedit_pattern_line_traps_palette_offset->setObjectName(QString::fromUtf8("logedit_pattern_line_traps_palette_offset"));

        horizontalLayout_pattern_color_tune->addWidget(logedit_pattern_line_traps_palette_offset);

        horizontalSpacer_pattern_color_tune = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_pattern_color_tune->addItem(horizontalSpacer_pattern_color_tune);


        verticalLayout_pattern_line_traps_outer->addLayout(horizontalLayout_pattern_color_tune);

        horizontalLayout_pattern_global_overrides = new QHBoxLayout();
        horizontalLayout_pattern_global_overrides->setObjectName(QString::fromUtf8("horizontalLayout_pattern_global_overrides"));
        label_pattern_line_traps_global_intensity = new QLabel(groupBox_pattern_line_traps);
        label_pattern_line_traps_global_intensity->setObjectName(QString::fromUtf8("label_pattern_line_traps_global_intensity"));

        horizontalLayout_pattern_global_overrides->addWidget(label_pattern_line_traps_global_intensity);

        logedit_pattern_line_traps_global_intensity = new MyLineEdit(groupBox_pattern_line_traps);
        logedit_pattern_line_traps_global_intensity->setObjectName(QString::fromUtf8("logedit_pattern_line_traps_global_intensity"));

        horizontalLayout_pattern_global_overrides->addWidget(logedit_pattern_line_traps_global_intensity);

        label_pattern_line_traps_global_max_distance = new QLabel(groupBox_pattern_line_traps);
        label_pattern_line_traps_global_max_distance->setObjectName(QString::fromUtf8("label_pattern_line_traps_global_max_distance"));

        horizontalLayout_pattern_global_overrides->addWidget(label_pattern_line_traps_global_max_distance);

        logedit_pattern_line_traps_global_max_distance = new MyLineEdit(groupBox_pattern_line_traps);
        logedit_pattern_line_traps_global_max_distance->setObjectName(QString::fromUtf8("logedit_pattern_line_traps_global_max_distance"));

        horizontalLayout_pattern_global_overrides->addWidget(logedit_pattern_line_traps_global_max_distance);

        label_pattern_line_traps_global_scale = new QLabel(groupBox_pattern_line_traps);
        label_pattern_line_traps_global_scale->setObjectName(QString::fromUtf8("label_pattern_line_traps_global_scale"));

        horizontalLayout_pattern_global_overrides->addWidget(label_pattern_line_traps_global_scale);

        logedit_pattern_line_traps_global_scale = new MyLineEdit(groupBox_pattern_line_traps);
        logedit_pattern_line_traps_global_scale->setObjectName(QString::fromUtf8("logedit_pattern_line_traps_global_scale"));

        horizontalLayout_pattern_global_overrides->addWidget(logedit_pattern_line_traps_global_scale);

        label_pattern_line_traps_global_relative_thickness = new QLabel(groupBox_pattern_line_traps);
        label_pattern_line_traps_global_relative_thickness->setObjectName(QString::fromUtf8("label_pattern_line_traps_global_relative_thickness"));

        horizontalLayout_pattern_global_overrides->addWidget(label_pattern_line_traps_global_relative_thickness);

        logedit_pattern_line_traps_global_relative_thickness = new MyLineEdit(groupBox_pattern_line_traps);
        logedit_pattern_line_traps_global_relative_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_traps_global_relative_thickness"));

        horizontalLayout_pattern_global_overrides->addWidget(logedit_pattern_line_traps_global_relative_thickness);

        horizontalSpacer_pattern_global_overrides = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_pattern_global_overrides->addItem(horizontalSpacer_pattern_global_overrides);


        verticalLayout_pattern_line_traps_outer->addLayout(horizontalLayout_pattern_global_overrides);

        groupBox_pattern_line_trap_workflow = new QGroupBox(groupBox_pattern_line_traps);
        groupBox_pattern_line_trap_workflow->setObjectName(QString::fromUtf8("groupBox_pattern_line_trap_workflow"));
        verticalLayout_pattern_line_trap_workflow = new QVBoxLayout(groupBox_pattern_line_trap_workflow);
        verticalLayout_pattern_line_trap_workflow->setSpacing(2);
        verticalLayout_pattern_line_trap_workflow->setObjectName(QString::fromUtf8("verticalLayout_pattern_line_trap_workflow"));
        horizontalLayout_pattern_solo = new QHBoxLayout();
        horizontalLayout_pattern_solo->setObjectName(QString::fromUtf8("horizontalLayout_pattern_solo"));
        label_pattern_line_trap_solo_layer = new QLabel(groupBox_pattern_line_trap_workflow);
        label_pattern_line_trap_solo_layer->setObjectName(QString::fromUtf8("label_pattern_line_trap_solo_layer"));

        horizontalLayout_pattern_solo->addWidget(label_pattern_line_trap_solo_layer);

        spinboxInt_pattern_line_trap_solo_layer = new MySpinBox(groupBox_pattern_line_trap_workflow);
        spinboxInt_pattern_line_trap_solo_layer->setObjectName(QString::fromUtf8("spinboxInt_pattern_line_trap_solo_layer"));

        horizontalLayout_pattern_solo->addWidget(spinboxInt_pattern_line_trap_solo_layer);

        horizontalSpacer_pattern_solo = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_pattern_solo->addItem(horizontalSpacer_pattern_solo);


        verticalLayout_pattern_line_trap_workflow->addLayout(horizontalLayout_pattern_solo);

        horizontalLayout_pattern_presets = new QHBoxLayout();
        horizontalLayout_pattern_presets->setObjectName(QString::fromUtf8("horizontalLayout_pattern_presets"));
        label_pattern_line_trap_presets = new QLabel(groupBox_pattern_line_trap_workflow);
        label_pattern_line_trap_presets->setObjectName(QString::fromUtf8("label_pattern_line_trap_presets"));

        horizontalLayout_pattern_presets->addWidget(label_pattern_line_trap_presets);

        comboBox_pattern_line_trap_presets = new QComboBox(groupBox_pattern_line_trap_workflow);
        comboBox_pattern_line_trap_presets->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_presets"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox_pattern_line_trap_presets->sizePolicy().hasHeightForWidth());
        comboBox_pattern_line_trap_presets->setSizePolicy(sizePolicy);

        horizontalLayout_pattern_presets->addWidget(comboBox_pattern_line_trap_presets);

        pushButton_pattern_line_trap_preset_refresh = new QPushButton(groupBox_pattern_line_trap_workflow);
        pushButton_pattern_line_trap_preset_refresh->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_preset_refresh"));

        horizontalLayout_pattern_presets->addWidget(pushButton_pattern_line_trap_preset_refresh);

        pushButton_pattern_line_trap_preset_load = new QPushButton(groupBox_pattern_line_trap_workflow);
        pushButton_pattern_line_trap_preset_load->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_preset_load"));

        horizontalLayout_pattern_presets->addWidget(pushButton_pattern_line_trap_preset_load);

        pushButton_pattern_line_trap_preset_save = new QPushButton(groupBox_pattern_line_trap_workflow);
        pushButton_pattern_line_trap_preset_save->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_preset_save"));

        horizontalLayout_pattern_presets->addWidget(pushButton_pattern_line_trap_preset_save);


        verticalLayout_pattern_line_trap_workflow->addLayout(horizontalLayout_pattern_presets);

        horizontalLayout_pattern_copy = new QHBoxLayout();
        horizontalLayout_pattern_copy->setObjectName(QString::fromUtf8("horizontalLayout_pattern_copy"));
        label_pattern_line_trap_copy = new QLabel(groupBox_pattern_line_trap_workflow);
        label_pattern_line_trap_copy->setObjectName(QString::fromUtf8("label_pattern_line_trap_copy"));

        horizontalLayout_pattern_copy->addWidget(label_pattern_line_trap_copy);

        spinbox_pattern_line_trap_copy_from = new QSpinBox(groupBox_pattern_line_trap_workflow);
        spinbox_pattern_line_trap_copy_from->setObjectName(QString::fromUtf8("spinbox_pattern_line_trap_copy_from"));
        spinbox_pattern_line_trap_copy_from->setMinimum(1);
        spinbox_pattern_line_trap_copy_from->setMaximum(20);
        spinbox_pattern_line_trap_copy_from->setValue(1);

        horizontalLayout_pattern_copy->addWidget(spinbox_pattern_line_trap_copy_from);

        label_pattern_line_trap_copy_arrow = new QLabel(groupBox_pattern_line_trap_workflow);
        label_pattern_line_trap_copy_arrow->setObjectName(QString::fromUtf8("label_pattern_line_trap_copy_arrow"));

        horizontalLayout_pattern_copy->addWidget(label_pattern_line_trap_copy_arrow);

        spinbox_pattern_line_trap_copy_to = new QSpinBox(groupBox_pattern_line_trap_workflow);
        spinbox_pattern_line_trap_copy_to->setObjectName(QString::fromUtf8("spinbox_pattern_line_trap_copy_to"));
        spinbox_pattern_line_trap_copy_to->setMinimum(1);
        spinbox_pattern_line_trap_copy_to->setMaximum(20);
        spinbox_pattern_line_trap_copy_to->setValue(2);

        horizontalLayout_pattern_copy->addWidget(spinbox_pattern_line_trap_copy_to);

        pushButton_pattern_line_trap_copy_layer = new QPushButton(groupBox_pattern_line_trap_workflow);
        pushButton_pattern_line_trap_copy_layer->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_copy_layer"));

        horizontalLayout_pattern_copy->addWidget(pushButton_pattern_line_trap_copy_layer);


        verticalLayout_pattern_line_trap_workflow->addLayout(horizontalLayout_pattern_copy);


        verticalLayout_pattern_line_traps_outer->addWidget(groupBox_pattern_line_trap_workflow);

        groupBox_pattern_line_exact_placement = new QGroupBox(groupBox_pattern_line_traps);
        groupBox_pattern_line_exact_placement->setObjectName(QString::fromUtf8("groupBox_pattern_line_exact_placement"));
        verticalLayout_pattern_line_exact = new QVBoxLayout(groupBox_pattern_line_exact_placement);
        verticalLayout_pattern_line_exact->setSpacing(6);
        verticalLayout_pattern_line_exact->setObjectName(QString::fromUtf8("verticalLayout_pattern_line_exact"));
        label_pattern_line_exact_intro = new QLabel(groupBox_pattern_line_exact_placement);
        label_pattern_line_exact_intro->setObjectName(QString::fromUtf8("label_pattern_line_exact_intro"));
        label_pattern_line_exact_intro->setWordWrap(true);

        verticalLayout_pattern_line_exact->addWidget(label_pattern_line_exact_intro);

        horizontalLayout_pattern_line_precision = new QHBoxLayout();
        horizontalLayout_pattern_line_precision->setObjectName(QString::fromUtf8("horizontalLayout_pattern_line_precision"));
        label_pattern_line_precision_mode = new QLabel(groupBox_pattern_line_exact_placement);
        label_pattern_line_precision_mode->setObjectName(QString::fromUtf8("label_pattern_line_precision_mode"));

        horizontalLayout_pattern_line_precision->addWidget(label_pattern_line_precision_mode);

        comboBox_pattern_line_precision_mode = new QComboBox(groupBox_pattern_line_exact_placement);
        comboBox_pattern_line_precision_mode->addItem(QString());
        comboBox_pattern_line_precision_mode->addItem(QString());
        comboBox_pattern_line_precision_mode->setObjectName(QString::fromUtf8("comboBox_pattern_line_precision_mode"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox_pattern_line_precision_mode->sizePolicy().hasHeightForWidth());
        comboBox_pattern_line_precision_mode->setSizePolicy(sizePolicy1);

        horizontalLayout_pattern_line_precision->addWidget(comboBox_pattern_line_precision_mode);


        verticalLayout_pattern_line_exact->addLayout(horizontalLayout_pattern_line_precision);

        horizontalLayout_pattern_line_exact = new QHBoxLayout();
        horizontalLayout_pattern_line_exact->setObjectName(QString::fromUtf8("horizontalLayout_pattern_line_exact"));
        label_pattern_line_exact_layer = new QLabel(groupBox_pattern_line_exact_placement);
        label_pattern_line_exact_layer->setObjectName(QString::fromUtf8("label_pattern_line_exact_layer"));

        horizontalLayout_pattern_line_exact->addWidget(label_pattern_line_exact_layer);

        spinbox_pattern_line_exact_layer = new QSpinBox(groupBox_pattern_line_exact_placement);
        spinbox_pattern_line_exact_layer->setObjectName(QString::fromUtf8("spinbox_pattern_line_exact_layer"));
        spinbox_pattern_line_exact_layer->setMinimum(1);
        spinbox_pattern_line_exact_layer->setMaximum(20);
        spinbox_pattern_line_exact_layer->setValue(1);

        horizontalLayout_pattern_line_exact->addWidget(spinbox_pattern_line_exact_layer);

        pushButton_pattern_line_exact_activate = new QPushButton(groupBox_pattern_line_exact_placement);
        pushButton_pattern_line_exact_activate->setObjectName(QString::fromUtf8("pushButton_pattern_line_exact_activate"));
        pushButton_pattern_line_exact_activate->setCheckable(true);
        sizePolicy1.setHeightForWidth(pushButton_pattern_line_exact_activate->sizePolicy().hasHeightForWidth());
        pushButton_pattern_line_exact_activate->setSizePolicy(sizePolicy1);

        horizontalLayout_pattern_line_exact->addWidget(pushButton_pattern_line_exact_activate);


        verticalLayout_pattern_line_exact->addLayout(horizontalLayout_pattern_line_exact);

        groupBox_pattern_line_placement_offset_xyz = new QGroupBox(groupBox_pattern_line_exact_placement);
        groupBox_pattern_line_placement_offset_xyz->setObjectName(QString::fromUtf8("groupBox_pattern_line_placement_offset_xyz"));
        gridLayout_pattern_line_placement_offset = new QGridLayout(groupBox_pattern_line_placement_offset_xyz);
        gridLayout_pattern_line_placement_offset->setSpacing(4);
        gridLayout_pattern_line_placement_offset->setObjectName(QString::fromUtf8("gridLayout_pattern_line_placement_offset"));
        label_pattern_line_pl_offset_x = new QLabel(groupBox_pattern_line_placement_offset_xyz);
        label_pattern_line_pl_offset_x->setObjectName(QString::fromUtf8("label_pattern_line_pl_offset_x"));
        label_pattern_line_pl_offset_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_pattern_line_placement_offset->addWidget(label_pattern_line_pl_offset_x, 0, 0, 1, 1);

        vect3_aux_light_manual_placement_offset_x = new MyLineEdit(groupBox_pattern_line_placement_offset_xyz);
        vect3_aux_light_manual_placement_offset_x->setObjectName(QString::fromUtf8("vect3_aux_light_manual_placement_offset_x"));
        sizePolicy.setHeightForWidth(vect3_aux_light_manual_placement_offset_x->sizePolicy().hasHeightForWidth());
        vect3_aux_light_manual_placement_offset_x->setSizePolicy(sizePolicy);
        vect3_aux_light_manual_placement_offset_x->setMinimumSize(QSize(80, 22));

        gridLayout_pattern_line_placement_offset->addWidget(vect3_aux_light_manual_placement_offset_x, 0, 1, 1, 1);

        label_pattern_line_pl_offset_y = new QLabel(groupBox_pattern_line_placement_offset_xyz);
        label_pattern_line_pl_offset_y->setObjectName(QString::fromUtf8("label_pattern_line_pl_offset_y"));
        label_pattern_line_pl_offset_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_pattern_line_placement_offset->addWidget(label_pattern_line_pl_offset_y, 1, 0, 1, 1);

        vect3_aux_light_manual_placement_offset_y = new MyLineEdit(groupBox_pattern_line_placement_offset_xyz);
        vect3_aux_light_manual_placement_offset_y->setObjectName(QString::fromUtf8("vect3_aux_light_manual_placement_offset_y"));
        sizePolicy.setHeightForWidth(vect3_aux_light_manual_placement_offset_y->sizePolicy().hasHeightForWidth());
        vect3_aux_light_manual_placement_offset_y->setSizePolicy(sizePolicy);
        vect3_aux_light_manual_placement_offset_y->setMinimumSize(QSize(80, 22));

        gridLayout_pattern_line_placement_offset->addWidget(vect3_aux_light_manual_placement_offset_y, 1, 1, 1, 1);

        label_pattern_line_pl_offset_z = new QLabel(groupBox_pattern_line_placement_offset_xyz);
        label_pattern_line_pl_offset_z->setObjectName(QString::fromUtf8("label_pattern_line_pl_offset_z"));
        label_pattern_line_pl_offset_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_pattern_line_placement_offset->addWidget(label_pattern_line_pl_offset_z, 2, 0, 1, 1);

        vect3_aux_light_manual_placement_offset_z = new MyLineEdit(groupBox_pattern_line_placement_offset_xyz);
        vect3_aux_light_manual_placement_offset_z->setObjectName(QString::fromUtf8("vect3_aux_light_manual_placement_offset_z"));
        sizePolicy.setHeightForWidth(vect3_aux_light_manual_placement_offset_z->sizePolicy().hasHeightForWidth());
        vect3_aux_light_manual_placement_offset_z->setSizePolicy(sizePolicy);
        vect3_aux_light_manual_placement_offset_z->setMinimumSize(QSize(80, 22));

        gridLayout_pattern_line_placement_offset->addWidget(vect3_aux_light_manual_placement_offset_z, 2, 1, 1, 1);


        verticalLayout_pattern_line_exact->addWidget(groupBox_pattern_line_placement_offset_xyz);

        label_pattern_line_exact_footer = new QLabel(groupBox_pattern_line_exact_placement);
        label_pattern_line_exact_footer->setObjectName(QString::fromUtf8("label_pattern_line_exact_footer"));
        label_pattern_line_exact_footer->setWordWrap(true);
        label_pattern_line_exact_footer->setStyleSheet(QString::fromUtf8("color: palette(shadow);"));

        verticalLayout_pattern_line_exact->addWidget(label_pattern_line_exact_footer);


        verticalLayout_pattern_line_traps_outer->addWidget(groupBox_pattern_line_exact_placement);

        label_pattern_line_traps_hint = new QLabel(groupBox_pattern_line_traps);
        label_pattern_line_traps_hint->setObjectName(QString::fromUtf8("label_pattern_line_traps_hint"));
        label_pattern_line_traps_hint->setWordWrap(true);

        verticalLayout_pattern_line_traps_outer->addWidget(label_pattern_line_traps_hint);

        pushButton_pattern_line_traps_quick_test = new QPushButton(groupBox_pattern_line_traps);
        pushButton_pattern_line_traps_quick_test->setObjectName(QString::fromUtf8("pushButton_pattern_line_traps_quick_test"));

        verticalLayout_pattern_line_traps_outer->addWidget(pushButton_pattern_line_traps_quick_test);

        groupCheck_pattern_line_trap_1_enabled = new MyGroupBox(groupBox_pattern_line_traps);
        groupCheck_pattern_line_trap_1_enabled->setObjectName(QString::fromUtf8("groupCheck_pattern_line_trap_1_enabled"));
        groupCheck_pattern_line_trap_1_enabled->setCheckable(true);
        gridLayout_pattern_line_1 = new QGridLayout(groupCheck_pattern_line_trap_1_enabled);
        gridLayout_pattern_line_1->setSpacing(2);
        gridLayout_pattern_line_1->setObjectName(QString::fromUtf8("gridLayout_pattern_line_1"));
        label_pattern_line_1_pos = new QLabel(groupCheck_pattern_line_trap_1_enabled);
        label_pattern_line_1_pos->setObjectName(QString::fromUtf8("label_pattern_line_1_pos"));

        gridLayout_pattern_line_1->addWidget(label_pattern_line_1_pos, 0, 0, 1, 1);

        vect3_pattern_line_trap_1_position_x = new MyLineEdit(groupCheck_pattern_line_trap_1_enabled);
        vect3_pattern_line_trap_1_position_x->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_1_position_x"));

        gridLayout_pattern_line_1->addWidget(vect3_pattern_line_trap_1_position_x, 0, 1, 1, 1);

        vect3_pattern_line_trap_1_position_y = new MyLineEdit(groupCheck_pattern_line_trap_1_enabled);
        vect3_pattern_line_trap_1_position_y->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_1_position_y"));

        gridLayout_pattern_line_1->addWidget(vect3_pattern_line_trap_1_position_y, 0, 2, 1, 1);

        vect3_pattern_line_trap_1_position_z = new MyLineEdit(groupCheck_pattern_line_trap_1_enabled);
        vect3_pattern_line_trap_1_position_z->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_1_position_z"));

        gridLayout_pattern_line_1->addWidget(vect3_pattern_line_trap_1_position_z, 0, 3, 1, 1);

        label_pattern_line_1_rot = new QLabel(groupCheck_pattern_line_trap_1_enabled);
        label_pattern_line_1_rot->setObjectName(QString::fromUtf8("label_pattern_line_1_rot"));

        gridLayout_pattern_line_1->addWidget(label_pattern_line_1_rot, 1, 0, 1, 1);

        spinboxd3_pattern_line_trap_1_rotation_x = new MyDoubleSpinBox(groupCheck_pattern_line_trap_1_enabled);
        spinboxd3_pattern_line_trap_1_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_1_rotation_x"));

        gridLayout_pattern_line_1->addWidget(spinboxd3_pattern_line_trap_1_rotation_x, 1, 1, 1, 1);

        spinboxd3_pattern_line_trap_1_rotation_y = new MyDoubleSpinBox(groupCheck_pattern_line_trap_1_enabled);
        spinboxd3_pattern_line_trap_1_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_1_rotation_y"));

        gridLayout_pattern_line_1->addWidget(spinboxd3_pattern_line_trap_1_rotation_y, 1, 2, 1, 1);

        spinboxd3_pattern_line_trap_1_rotation_z = new MyDoubleSpinBox(groupCheck_pattern_line_trap_1_enabled);
        spinboxd3_pattern_line_trap_1_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_1_rotation_z"));

        gridLayout_pattern_line_1->addWidget(spinboxd3_pattern_line_trap_1_rotation_z, 1, 3, 1, 1);

        label_pattern_line_1_radius = new QLabel(groupCheck_pattern_line_trap_1_enabled);
        label_pattern_line_1_radius->setObjectName(QString::fromUtf8("label_pattern_line_1_radius"));

        gridLayout_pattern_line_1->addWidget(label_pattern_line_1_radius, 2, 0, 1, 1);

        logedit_pattern_line_trap_1_radius = new MyLineEdit(groupCheck_pattern_line_trap_1_enabled);
        logedit_pattern_line_trap_1_radius->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_1_radius"));

        gridLayout_pattern_line_1->addWidget(logedit_pattern_line_trap_1_radius, 2, 1, 1, 1);

        logedit_pattern_line_trap_1_thickness = new MyLineEdit(groupCheck_pattern_line_trap_1_enabled);
        logedit_pattern_line_trap_1_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_1_thickness"));

        gridLayout_pattern_line_1->addWidget(logedit_pattern_line_trap_1_thickness, 2, 2, 1, 1);

        logedit_pattern_line_trap_1_edge_softness = new MyLineEdit(groupCheck_pattern_line_trap_1_enabled);
        logedit_pattern_line_trap_1_edge_softness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_1_edge_softness"));

        gridLayout_pattern_line_1->addWidget(logedit_pattern_line_trap_1_edge_softness, 2, 3, 1, 1);

        logedit_pattern_line_trap_1_max_distance = new MyLineEdit(groupCheck_pattern_line_trap_1_enabled);
        logedit_pattern_line_trap_1_max_distance->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_1_max_distance"));

        gridLayout_pattern_line_1->addWidget(logedit_pattern_line_trap_1_max_distance, 2, 4, 1, 1);

        label_pattern_line_1_scale = new QLabel(groupCheck_pattern_line_trap_1_enabled);
        label_pattern_line_1_scale->setObjectName(QString::fromUtf8("label_pattern_line_1_scale"));

        gridLayout_pattern_line_1->addWidget(label_pattern_line_1_scale, 3, 0, 1, 1);

        logedit_pattern_line_trap_1_scale = new MyLineEdit(groupCheck_pattern_line_trap_1_enabled);
        logedit_pattern_line_trap_1_scale->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_1_scale"));

        gridLayout_pattern_line_1->addWidget(logedit_pattern_line_trap_1_scale, 3, 1, 1, 1);

        logedit_pattern_line_trap_1_relative_thickness = new MyLineEdit(groupCheck_pattern_line_trap_1_enabled);
        logedit_pattern_line_trap_1_relative_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_1_relative_thickness"));

        gridLayout_pattern_line_1->addWidget(logedit_pattern_line_trap_1_relative_thickness, 3, 2, 1, 1);

        label_pattern_line_1_int = new QLabel(groupCheck_pattern_line_trap_1_enabled);
        label_pattern_line_1_int->setObjectName(QString::fromUtf8("label_pattern_line_1_int"));

        gridLayout_pattern_line_1->addWidget(label_pattern_line_1_int, 4, 0, 1, 1);

        logedit_pattern_line_trap_1_intensity = new MyLineEdit(groupCheck_pattern_line_trap_1_enabled);
        logedit_pattern_line_trap_1_intensity->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_1_intensity"));

        gridLayout_pattern_line_1->addWidget(logedit_pattern_line_trap_1_intensity, 4, 1, 1, 1);

        colorButton_pattern_line_trap_1_color = new MyColorButton(groupCheck_pattern_line_trap_1_enabled);
        colorButton_pattern_line_trap_1_color->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_1_color"));

        gridLayout_pattern_line_1->addWidget(colorButton_pattern_line_trap_1_color, 4, 2, 1, 1);

        colorButton_pattern_line_trap_1_color_2 = new MyColorButton(groupCheck_pattern_line_trap_1_enabled);
        colorButton_pattern_line_trap_1_color_2->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_1_color_2"));

        gridLayout_pattern_line_1->addWidget(colorButton_pattern_line_trap_1_color_2, 4, 3, 1, 1);

        colorButton_pattern_line_trap_1_color_3 = new MyColorButton(groupCheck_pattern_line_trap_1_enabled);
        colorButton_pattern_line_trap_1_color_3->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_1_color_3"));

        gridLayout_pattern_line_1->addWidget(colorButton_pattern_line_trap_1_color_3, 4, 4, 1, 1);

        label_pattern_line_1_shape = new QLabel(groupCheck_pattern_line_trap_1_enabled);
        label_pattern_line_1_shape->setObjectName(QString::fromUtf8("label_pattern_line_1_shape"));

        gridLayout_pattern_line_1->addWidget(label_pattern_line_1_shape, 5, 0, 1, 1);

        comboBox_pattern_line_trap_1_shape = new MyComboBox(groupCheck_pattern_line_trap_1_enabled);
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->addItem(QString());
        comboBox_pattern_line_trap_1_shape->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_1_shape"));

        gridLayout_pattern_line_1->addWidget(comboBox_pattern_line_trap_1_shape, 5, 1, 1, 4);

        label_pattern_line_1_shape_aux = new QLabel(groupCheck_pattern_line_trap_1_enabled);
        label_pattern_line_1_shape_aux->setObjectName(QString::fromUtf8("label_pattern_line_1_shape_aux"));

        gridLayout_pattern_line_1->addWidget(label_pattern_line_1_shape_aux, 6, 0, 1, 1);

        logedit_pattern_line_trap_1_shape_aux = new MyLineEdit(groupCheck_pattern_line_trap_1_enabled);
        logedit_pattern_line_trap_1_shape_aux->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_1_shape_aux"));

        gridLayout_pattern_line_1->addWidget(logedit_pattern_line_trap_1_shape_aux, 6, 1, 1, 2);

        label_pattern_line_1_sharp_seg = new QLabel(groupCheck_pattern_line_trap_1_enabled);
        label_pattern_line_1_sharp_seg->setObjectName(QString::fromUtf8("label_pattern_line_1_sharp_seg"));

        gridLayout_pattern_line_1->addWidget(label_pattern_line_1_sharp_seg, 7, 0, 1, 1);

        logedit_pattern_line_trap_1_falloff_sharpness = new MyLineEdit(groupCheck_pattern_line_trap_1_enabled);
        logedit_pattern_line_trap_1_falloff_sharpness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_1_falloff_sharpness"));

        gridLayout_pattern_line_1->addWidget(logedit_pattern_line_trap_1_falloff_sharpness, 7, 1, 1, 1);

        logedit_pattern_line_trap_1_segment_half_length = new MyLineEdit(groupCheck_pattern_line_trap_1_enabled);
        logedit_pattern_line_trap_1_segment_half_length->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_1_segment_half_length"));

        gridLayout_pattern_line_1->addWidget(logedit_pattern_line_trap_1_segment_half_length, 7, 2, 1, 1);

        label_pattern_line_1_glow = new QLabel(groupCheck_pattern_line_trap_1_enabled);
        label_pattern_line_1_glow->setObjectName(QString::fromUtf8("label_pattern_line_1_glow"));

        gridLayout_pattern_line_1->addWidget(label_pattern_line_1_glow, 8, 0, 1, 1);

        logedit_pattern_line_trap_1_glow_spread = new MyLineEdit(groupCheck_pattern_line_trap_1_enabled);
        logedit_pattern_line_trap_1_glow_spread->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_1_glow_spread"));

        gridLayout_pattern_line_1->addWidget(logedit_pattern_line_trap_1_glow_spread, 8, 1, 1, 1);

        comboBox_pattern_line_trap_1_falloff_profile = new MyComboBox(groupCheck_pattern_line_trap_1_enabled);
        comboBox_pattern_line_trap_1_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_1_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_1_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_1_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_1_falloff_profile->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_1_falloff_profile"));

        gridLayout_pattern_line_1->addWidget(comboBox_pattern_line_trap_1_falloff_profile, 8, 2, 1, 3);

        label_pattern_line_1_side = new QLabel(groupCheck_pattern_line_trap_1_enabled);
        label_pattern_line_1_side->setObjectName(QString::fromUtf8("label_pattern_line_1_side"));

        gridLayout_pattern_line_1->addWidget(label_pattern_line_1_side, 9, 0, 1, 1);

        comboBox_pattern_line_trap_1_edge_side = new MyComboBox(groupCheck_pattern_line_trap_1_enabled);
        comboBox_pattern_line_trap_1_edge_side->addItem(QString());
        comboBox_pattern_line_trap_1_edge_side->addItem(QString());
        comboBox_pattern_line_trap_1_edge_side->addItem(QString());
        comboBox_pattern_line_trap_1_edge_side->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_1_edge_side"));

        gridLayout_pattern_line_1->addWidget(comboBox_pattern_line_trap_1_edge_side, 9, 1, 1, 4);

        pushButton_pattern_line_trap_1_place_surface = new QPushButton(groupCheck_pattern_line_trap_1_enabled);
        pushButton_pattern_line_trap_1_place_surface->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_1_place_surface"));

        gridLayout_pattern_line_1->addWidget(pushButton_pattern_line_trap_1_place_surface, 10, 0, 1, 5);

        pushButton_pattern_line_trap_1_place_target = new QPushButton(groupCheck_pattern_line_trap_1_enabled);
        pushButton_pattern_line_trap_1_place_target->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_1_place_target"));

        gridLayout_pattern_line_1->addWidget(pushButton_pattern_line_trap_1_place_target, 11, 0, 1, 5);


        verticalLayout_pattern_line_traps_outer->addWidget(groupCheck_pattern_line_trap_1_enabled);

        groupCheck_pattern_line_trap_2_enabled = new MyGroupBox(groupBox_pattern_line_traps);
        groupCheck_pattern_line_trap_2_enabled->setObjectName(QString::fromUtf8("groupCheck_pattern_line_trap_2_enabled"));
        groupCheck_pattern_line_trap_2_enabled->setCheckable(true);
        gridLayout_pattern_line_2 = new QGridLayout(groupCheck_pattern_line_trap_2_enabled);
        gridLayout_pattern_line_2->setSpacing(2);
        gridLayout_pattern_line_2->setObjectName(QString::fromUtf8("gridLayout_pattern_line_2"));
        label_pattern_line_2_pos = new QLabel(groupCheck_pattern_line_trap_2_enabled);
        label_pattern_line_2_pos->setObjectName(QString::fromUtf8("label_pattern_line_2_pos"));

        gridLayout_pattern_line_2->addWidget(label_pattern_line_2_pos, 0, 0, 1, 1);

        vect3_pattern_line_trap_2_position_x = new MyLineEdit(groupCheck_pattern_line_trap_2_enabled);
        vect3_pattern_line_trap_2_position_x->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_2_position_x"));

        gridLayout_pattern_line_2->addWidget(vect3_pattern_line_trap_2_position_x, 0, 1, 1, 1);

        vect3_pattern_line_trap_2_position_y = new MyLineEdit(groupCheck_pattern_line_trap_2_enabled);
        vect3_pattern_line_trap_2_position_y->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_2_position_y"));

        gridLayout_pattern_line_2->addWidget(vect3_pattern_line_trap_2_position_y, 0, 2, 1, 1);

        vect3_pattern_line_trap_2_position_z = new MyLineEdit(groupCheck_pattern_line_trap_2_enabled);
        vect3_pattern_line_trap_2_position_z->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_2_position_z"));

        gridLayout_pattern_line_2->addWidget(vect3_pattern_line_trap_2_position_z, 0, 3, 1, 1);

        label_pattern_line_2_rot = new QLabel(groupCheck_pattern_line_trap_2_enabled);
        label_pattern_line_2_rot->setObjectName(QString::fromUtf8("label_pattern_line_2_rot"));

        gridLayout_pattern_line_2->addWidget(label_pattern_line_2_rot, 1, 0, 1, 1);

        spinboxd3_pattern_line_trap_2_rotation_x = new MyDoubleSpinBox(groupCheck_pattern_line_trap_2_enabled);
        spinboxd3_pattern_line_trap_2_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_2_rotation_x"));

        gridLayout_pattern_line_2->addWidget(spinboxd3_pattern_line_trap_2_rotation_x, 1, 1, 1, 1);

        spinboxd3_pattern_line_trap_2_rotation_y = new MyDoubleSpinBox(groupCheck_pattern_line_trap_2_enabled);
        spinboxd3_pattern_line_trap_2_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_2_rotation_y"));

        gridLayout_pattern_line_2->addWidget(spinboxd3_pattern_line_trap_2_rotation_y, 1, 2, 1, 1);

        spinboxd3_pattern_line_trap_2_rotation_z = new MyDoubleSpinBox(groupCheck_pattern_line_trap_2_enabled);
        spinboxd3_pattern_line_trap_2_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_2_rotation_z"));

        gridLayout_pattern_line_2->addWidget(spinboxd3_pattern_line_trap_2_rotation_z, 1, 3, 1, 1);

        label_pattern_line_2_radius = new QLabel(groupCheck_pattern_line_trap_2_enabled);
        label_pattern_line_2_radius->setObjectName(QString::fromUtf8("label_pattern_line_2_radius"));

        gridLayout_pattern_line_2->addWidget(label_pattern_line_2_radius, 2, 0, 1, 1);

        logedit_pattern_line_trap_2_radius = new MyLineEdit(groupCheck_pattern_line_trap_2_enabled);
        logedit_pattern_line_trap_2_radius->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_2_radius"));

        gridLayout_pattern_line_2->addWidget(logedit_pattern_line_trap_2_radius, 2, 1, 1, 1);

        logedit_pattern_line_trap_2_thickness = new MyLineEdit(groupCheck_pattern_line_trap_2_enabled);
        logedit_pattern_line_trap_2_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_2_thickness"));

        gridLayout_pattern_line_2->addWidget(logedit_pattern_line_trap_2_thickness, 2, 2, 1, 1);

        logedit_pattern_line_trap_2_edge_softness = new MyLineEdit(groupCheck_pattern_line_trap_2_enabled);
        logedit_pattern_line_trap_2_edge_softness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_2_edge_softness"));

        gridLayout_pattern_line_2->addWidget(logedit_pattern_line_trap_2_edge_softness, 2, 3, 1, 1);

        logedit_pattern_line_trap_2_max_distance = new MyLineEdit(groupCheck_pattern_line_trap_2_enabled);
        logedit_pattern_line_trap_2_max_distance->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_2_max_distance"));

        gridLayout_pattern_line_2->addWidget(logedit_pattern_line_trap_2_max_distance, 2, 4, 1, 1);

        label_pattern_line_2_scale = new QLabel(groupCheck_pattern_line_trap_2_enabled);
        label_pattern_line_2_scale->setObjectName(QString::fromUtf8("label_pattern_line_2_scale"));

        gridLayout_pattern_line_2->addWidget(label_pattern_line_2_scale, 3, 0, 1, 1);

        logedit_pattern_line_trap_2_scale = new MyLineEdit(groupCheck_pattern_line_trap_2_enabled);
        logedit_pattern_line_trap_2_scale->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_2_scale"));

        gridLayout_pattern_line_2->addWidget(logedit_pattern_line_trap_2_scale, 3, 1, 1, 1);

        logedit_pattern_line_trap_2_relative_thickness = new MyLineEdit(groupCheck_pattern_line_trap_2_enabled);
        logedit_pattern_line_trap_2_relative_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_2_relative_thickness"));

        gridLayout_pattern_line_2->addWidget(logedit_pattern_line_trap_2_relative_thickness, 3, 2, 1, 1);

        label_pattern_line_2_int = new QLabel(groupCheck_pattern_line_trap_2_enabled);
        label_pattern_line_2_int->setObjectName(QString::fromUtf8("label_pattern_line_2_int"));

        gridLayout_pattern_line_2->addWidget(label_pattern_line_2_int, 4, 0, 1, 1);

        logedit_pattern_line_trap_2_intensity = new MyLineEdit(groupCheck_pattern_line_trap_2_enabled);
        logedit_pattern_line_trap_2_intensity->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_2_intensity"));

        gridLayout_pattern_line_2->addWidget(logedit_pattern_line_trap_2_intensity, 4, 1, 1, 1);

        colorButton_pattern_line_trap_2_color = new MyColorButton(groupCheck_pattern_line_trap_2_enabled);
        colorButton_pattern_line_trap_2_color->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_2_color"));

        gridLayout_pattern_line_2->addWidget(colorButton_pattern_line_trap_2_color, 4, 2, 1, 1);

        colorButton_pattern_line_trap_2_color_2 = new MyColorButton(groupCheck_pattern_line_trap_2_enabled);
        colorButton_pattern_line_trap_2_color_2->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_2_color_2"));

        gridLayout_pattern_line_2->addWidget(colorButton_pattern_line_trap_2_color_2, 4, 3, 1, 1);

        colorButton_pattern_line_trap_2_color_3 = new MyColorButton(groupCheck_pattern_line_trap_2_enabled);
        colorButton_pattern_line_trap_2_color_3->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_2_color_3"));

        gridLayout_pattern_line_2->addWidget(colorButton_pattern_line_trap_2_color_3, 4, 4, 1, 1);

        label_pattern_line_2_shape = new QLabel(groupCheck_pattern_line_trap_2_enabled);
        label_pattern_line_2_shape->setObjectName(QString::fromUtf8("label_pattern_line_2_shape"));

        gridLayout_pattern_line_2->addWidget(label_pattern_line_2_shape, 5, 0, 1, 1);

        comboBox_pattern_line_trap_2_shape = new MyComboBox(groupCheck_pattern_line_trap_2_enabled);
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->addItem(QString());
        comboBox_pattern_line_trap_2_shape->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_2_shape"));

        gridLayout_pattern_line_2->addWidget(comboBox_pattern_line_trap_2_shape, 5, 1, 1, 4);

        label_pattern_line_2_shape_aux = new QLabel(groupCheck_pattern_line_trap_2_enabled);
        label_pattern_line_2_shape_aux->setObjectName(QString::fromUtf8("label_pattern_line_2_shape_aux"));

        gridLayout_pattern_line_2->addWidget(label_pattern_line_2_shape_aux, 6, 0, 1, 1);

        logedit_pattern_line_trap_2_shape_aux = new MyLineEdit(groupCheck_pattern_line_trap_2_enabled);
        logedit_pattern_line_trap_2_shape_aux->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_2_shape_aux"));

        gridLayout_pattern_line_2->addWidget(logedit_pattern_line_trap_2_shape_aux, 6, 1, 1, 2);

        label_pattern_line_2_sharp_seg = new QLabel(groupCheck_pattern_line_trap_2_enabled);
        label_pattern_line_2_sharp_seg->setObjectName(QString::fromUtf8("label_pattern_line_2_sharp_seg"));

        gridLayout_pattern_line_2->addWidget(label_pattern_line_2_sharp_seg, 7, 0, 1, 1);

        logedit_pattern_line_trap_2_falloff_sharpness = new MyLineEdit(groupCheck_pattern_line_trap_2_enabled);
        logedit_pattern_line_trap_2_falloff_sharpness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_2_falloff_sharpness"));

        gridLayout_pattern_line_2->addWidget(logedit_pattern_line_trap_2_falloff_sharpness, 7, 1, 1, 1);

        logedit_pattern_line_trap_2_segment_half_length = new MyLineEdit(groupCheck_pattern_line_trap_2_enabled);
        logedit_pattern_line_trap_2_segment_half_length->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_2_segment_half_length"));

        gridLayout_pattern_line_2->addWidget(logedit_pattern_line_trap_2_segment_half_length, 7, 2, 1, 1);

        label_pattern_line_2_glow = new QLabel(groupCheck_pattern_line_trap_2_enabled);
        label_pattern_line_2_glow->setObjectName(QString::fromUtf8("label_pattern_line_2_glow"));

        gridLayout_pattern_line_2->addWidget(label_pattern_line_2_glow, 8, 0, 1, 1);

        logedit_pattern_line_trap_2_glow_spread = new MyLineEdit(groupCheck_pattern_line_trap_2_enabled);
        logedit_pattern_line_trap_2_glow_spread->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_2_glow_spread"));

        gridLayout_pattern_line_2->addWidget(logedit_pattern_line_trap_2_glow_spread, 8, 1, 1, 1);

        comboBox_pattern_line_trap_2_falloff_profile = new MyComboBox(groupCheck_pattern_line_trap_2_enabled);
        comboBox_pattern_line_trap_2_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_2_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_2_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_2_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_2_falloff_profile->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_2_falloff_profile"));

        gridLayout_pattern_line_2->addWidget(comboBox_pattern_line_trap_2_falloff_profile, 8, 2, 1, 3);

        label_pattern_line_2_side = new QLabel(groupCheck_pattern_line_trap_2_enabled);
        label_pattern_line_2_side->setObjectName(QString::fromUtf8("label_pattern_line_2_side"));

        gridLayout_pattern_line_2->addWidget(label_pattern_line_2_side, 9, 0, 1, 1);

        comboBox_pattern_line_trap_2_edge_side = new MyComboBox(groupCheck_pattern_line_trap_2_enabled);
        comboBox_pattern_line_trap_2_edge_side->addItem(QString());
        comboBox_pattern_line_trap_2_edge_side->addItem(QString());
        comboBox_pattern_line_trap_2_edge_side->addItem(QString());
        comboBox_pattern_line_trap_2_edge_side->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_2_edge_side"));

        gridLayout_pattern_line_2->addWidget(comboBox_pattern_line_trap_2_edge_side, 9, 1, 1, 4);

        pushButton_pattern_line_trap_2_place_surface = new QPushButton(groupCheck_pattern_line_trap_2_enabled);
        pushButton_pattern_line_trap_2_place_surface->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_2_place_surface"));

        gridLayout_pattern_line_2->addWidget(pushButton_pattern_line_trap_2_place_surface, 10, 0, 1, 5);

        pushButton_pattern_line_trap_2_place_target = new QPushButton(groupCheck_pattern_line_trap_2_enabled);
        pushButton_pattern_line_trap_2_place_target->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_2_place_target"));

        gridLayout_pattern_line_2->addWidget(pushButton_pattern_line_trap_2_place_target, 11, 0, 1, 5);


        verticalLayout_pattern_line_traps_outer->addWidget(groupCheck_pattern_line_trap_2_enabled);

        groupCheck_pattern_line_trap_3_enabled = new MyGroupBox(groupBox_pattern_line_traps);
        groupCheck_pattern_line_trap_3_enabled->setObjectName(QString::fromUtf8("groupCheck_pattern_line_trap_3_enabled"));
        groupCheck_pattern_line_trap_3_enabled->setCheckable(true);
        gridLayout_pattern_line_3 = new QGridLayout(groupCheck_pattern_line_trap_3_enabled);
        gridLayout_pattern_line_3->setSpacing(2);
        gridLayout_pattern_line_3->setObjectName(QString::fromUtf8("gridLayout_pattern_line_3"));
        label_pattern_line_3_pos = new QLabel(groupCheck_pattern_line_trap_3_enabled);
        label_pattern_line_3_pos->setObjectName(QString::fromUtf8("label_pattern_line_3_pos"));

        gridLayout_pattern_line_3->addWidget(label_pattern_line_3_pos, 0, 0, 1, 1);

        vect3_pattern_line_trap_3_position_x = new MyLineEdit(groupCheck_pattern_line_trap_3_enabled);
        vect3_pattern_line_trap_3_position_x->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_3_position_x"));

        gridLayout_pattern_line_3->addWidget(vect3_pattern_line_trap_3_position_x, 0, 1, 1, 1);

        vect3_pattern_line_trap_3_position_y = new MyLineEdit(groupCheck_pattern_line_trap_3_enabled);
        vect3_pattern_line_trap_3_position_y->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_3_position_y"));

        gridLayout_pattern_line_3->addWidget(vect3_pattern_line_trap_3_position_y, 0, 2, 1, 1);

        vect3_pattern_line_trap_3_position_z = new MyLineEdit(groupCheck_pattern_line_trap_3_enabled);
        vect3_pattern_line_trap_3_position_z->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_3_position_z"));

        gridLayout_pattern_line_3->addWidget(vect3_pattern_line_trap_3_position_z, 0, 3, 1, 1);

        label_pattern_line_3_rot = new QLabel(groupCheck_pattern_line_trap_3_enabled);
        label_pattern_line_3_rot->setObjectName(QString::fromUtf8("label_pattern_line_3_rot"));

        gridLayout_pattern_line_3->addWidget(label_pattern_line_3_rot, 1, 0, 1, 1);

        spinboxd3_pattern_line_trap_3_rotation_x = new MyDoubleSpinBox(groupCheck_pattern_line_trap_3_enabled);
        spinboxd3_pattern_line_trap_3_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_3_rotation_x"));

        gridLayout_pattern_line_3->addWidget(spinboxd3_pattern_line_trap_3_rotation_x, 1, 1, 1, 1);

        spinboxd3_pattern_line_trap_3_rotation_y = new MyDoubleSpinBox(groupCheck_pattern_line_trap_3_enabled);
        spinboxd3_pattern_line_trap_3_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_3_rotation_y"));

        gridLayout_pattern_line_3->addWidget(spinboxd3_pattern_line_trap_3_rotation_y, 1, 2, 1, 1);

        spinboxd3_pattern_line_trap_3_rotation_z = new MyDoubleSpinBox(groupCheck_pattern_line_trap_3_enabled);
        spinboxd3_pattern_line_trap_3_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_3_rotation_z"));

        gridLayout_pattern_line_3->addWidget(spinboxd3_pattern_line_trap_3_rotation_z, 1, 3, 1, 1);

        label_pattern_line_3_radius = new QLabel(groupCheck_pattern_line_trap_3_enabled);
        label_pattern_line_3_radius->setObjectName(QString::fromUtf8("label_pattern_line_3_radius"));

        gridLayout_pattern_line_3->addWidget(label_pattern_line_3_radius, 2, 0, 1, 1);

        logedit_pattern_line_trap_3_radius = new MyLineEdit(groupCheck_pattern_line_trap_3_enabled);
        logedit_pattern_line_trap_3_radius->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_3_radius"));

        gridLayout_pattern_line_3->addWidget(logedit_pattern_line_trap_3_radius, 2, 1, 1, 1);

        logedit_pattern_line_trap_3_thickness = new MyLineEdit(groupCheck_pattern_line_trap_3_enabled);
        logedit_pattern_line_trap_3_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_3_thickness"));

        gridLayout_pattern_line_3->addWidget(logedit_pattern_line_trap_3_thickness, 2, 2, 1, 1);

        logedit_pattern_line_trap_3_edge_softness = new MyLineEdit(groupCheck_pattern_line_trap_3_enabled);
        logedit_pattern_line_trap_3_edge_softness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_3_edge_softness"));

        gridLayout_pattern_line_3->addWidget(logedit_pattern_line_trap_3_edge_softness, 2, 3, 1, 1);

        logedit_pattern_line_trap_3_max_distance = new MyLineEdit(groupCheck_pattern_line_trap_3_enabled);
        logedit_pattern_line_trap_3_max_distance->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_3_max_distance"));

        gridLayout_pattern_line_3->addWidget(logedit_pattern_line_trap_3_max_distance, 2, 4, 1, 1);

        label_pattern_line_3_scale = new QLabel(groupCheck_pattern_line_trap_3_enabled);
        label_pattern_line_3_scale->setObjectName(QString::fromUtf8("label_pattern_line_3_scale"));

        gridLayout_pattern_line_3->addWidget(label_pattern_line_3_scale, 3, 0, 1, 1);

        logedit_pattern_line_trap_3_scale = new MyLineEdit(groupCheck_pattern_line_trap_3_enabled);
        logedit_pattern_line_trap_3_scale->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_3_scale"));

        gridLayout_pattern_line_3->addWidget(logedit_pattern_line_trap_3_scale, 3, 1, 1, 1);

        logedit_pattern_line_trap_3_relative_thickness = new MyLineEdit(groupCheck_pattern_line_trap_3_enabled);
        logedit_pattern_line_trap_3_relative_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_3_relative_thickness"));

        gridLayout_pattern_line_3->addWidget(logedit_pattern_line_trap_3_relative_thickness, 3, 2, 1, 1);

        label_pattern_line_3_int = new QLabel(groupCheck_pattern_line_trap_3_enabled);
        label_pattern_line_3_int->setObjectName(QString::fromUtf8("label_pattern_line_3_int"));

        gridLayout_pattern_line_3->addWidget(label_pattern_line_3_int, 4, 0, 1, 1);

        logedit_pattern_line_trap_3_intensity = new MyLineEdit(groupCheck_pattern_line_trap_3_enabled);
        logedit_pattern_line_trap_3_intensity->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_3_intensity"));

        gridLayout_pattern_line_3->addWidget(logedit_pattern_line_trap_3_intensity, 4, 1, 1, 1);

        colorButton_pattern_line_trap_3_color = new MyColorButton(groupCheck_pattern_line_trap_3_enabled);
        colorButton_pattern_line_trap_3_color->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_3_color"));

        gridLayout_pattern_line_3->addWidget(colorButton_pattern_line_trap_3_color, 4, 2, 1, 1);

        colorButton_pattern_line_trap_3_color_2 = new MyColorButton(groupCheck_pattern_line_trap_3_enabled);
        colorButton_pattern_line_trap_3_color_2->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_3_color_2"));

        gridLayout_pattern_line_3->addWidget(colorButton_pattern_line_trap_3_color_2, 4, 3, 1, 1);

        colorButton_pattern_line_trap_3_color_3 = new MyColorButton(groupCheck_pattern_line_trap_3_enabled);
        colorButton_pattern_line_trap_3_color_3->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_3_color_3"));

        gridLayout_pattern_line_3->addWidget(colorButton_pattern_line_trap_3_color_3, 4, 4, 1, 1);

        label_pattern_line_3_shape = new QLabel(groupCheck_pattern_line_trap_3_enabled);
        label_pattern_line_3_shape->setObjectName(QString::fromUtf8("label_pattern_line_3_shape"));

        gridLayout_pattern_line_3->addWidget(label_pattern_line_3_shape, 5, 0, 1, 1);

        comboBox_pattern_line_trap_3_shape = new MyComboBox(groupCheck_pattern_line_trap_3_enabled);
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->addItem(QString());
        comboBox_pattern_line_trap_3_shape->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_3_shape"));

        gridLayout_pattern_line_3->addWidget(comboBox_pattern_line_trap_3_shape, 5, 1, 1, 4);

        label_pattern_line_3_shape_aux = new QLabel(groupCheck_pattern_line_trap_3_enabled);
        label_pattern_line_3_shape_aux->setObjectName(QString::fromUtf8("label_pattern_line_3_shape_aux"));

        gridLayout_pattern_line_3->addWidget(label_pattern_line_3_shape_aux, 6, 0, 1, 1);

        logedit_pattern_line_trap_3_shape_aux = new MyLineEdit(groupCheck_pattern_line_trap_3_enabled);
        logedit_pattern_line_trap_3_shape_aux->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_3_shape_aux"));

        gridLayout_pattern_line_3->addWidget(logedit_pattern_line_trap_3_shape_aux, 6, 1, 1, 2);

        label_pattern_line_3_sharp_seg = new QLabel(groupCheck_pattern_line_trap_3_enabled);
        label_pattern_line_3_sharp_seg->setObjectName(QString::fromUtf8("label_pattern_line_3_sharp_seg"));

        gridLayout_pattern_line_3->addWidget(label_pattern_line_3_sharp_seg, 7, 0, 1, 1);

        logedit_pattern_line_trap_3_falloff_sharpness = new MyLineEdit(groupCheck_pattern_line_trap_3_enabled);
        logedit_pattern_line_trap_3_falloff_sharpness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_3_falloff_sharpness"));

        gridLayout_pattern_line_3->addWidget(logedit_pattern_line_trap_3_falloff_sharpness, 7, 1, 1, 1);

        logedit_pattern_line_trap_3_segment_half_length = new MyLineEdit(groupCheck_pattern_line_trap_3_enabled);
        logedit_pattern_line_trap_3_segment_half_length->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_3_segment_half_length"));

        gridLayout_pattern_line_3->addWidget(logedit_pattern_line_trap_3_segment_half_length, 7, 2, 1, 1);

        label_pattern_line_3_glow = new QLabel(groupCheck_pattern_line_trap_3_enabled);
        label_pattern_line_3_glow->setObjectName(QString::fromUtf8("label_pattern_line_3_glow"));

        gridLayout_pattern_line_3->addWidget(label_pattern_line_3_glow, 8, 0, 1, 1);

        logedit_pattern_line_trap_3_glow_spread = new MyLineEdit(groupCheck_pattern_line_trap_3_enabled);
        logedit_pattern_line_trap_3_glow_spread->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_3_glow_spread"));

        gridLayout_pattern_line_3->addWidget(logedit_pattern_line_trap_3_glow_spread, 8, 1, 1, 1);

        comboBox_pattern_line_trap_3_falloff_profile = new MyComboBox(groupCheck_pattern_line_trap_3_enabled);
        comboBox_pattern_line_trap_3_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_3_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_3_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_3_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_3_falloff_profile->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_3_falloff_profile"));

        gridLayout_pattern_line_3->addWidget(comboBox_pattern_line_trap_3_falloff_profile, 8, 2, 1, 3);

        label_pattern_line_3_side = new QLabel(groupCheck_pattern_line_trap_3_enabled);
        label_pattern_line_3_side->setObjectName(QString::fromUtf8("label_pattern_line_3_side"));

        gridLayout_pattern_line_3->addWidget(label_pattern_line_3_side, 9, 0, 1, 1);

        comboBox_pattern_line_trap_3_edge_side = new MyComboBox(groupCheck_pattern_line_trap_3_enabled);
        comboBox_pattern_line_trap_3_edge_side->addItem(QString());
        comboBox_pattern_line_trap_3_edge_side->addItem(QString());
        comboBox_pattern_line_trap_3_edge_side->addItem(QString());
        comboBox_pattern_line_trap_3_edge_side->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_3_edge_side"));

        gridLayout_pattern_line_3->addWidget(comboBox_pattern_line_trap_3_edge_side, 9, 1, 1, 4);

        pushButton_pattern_line_trap_3_place_surface = new QPushButton(groupCheck_pattern_line_trap_3_enabled);
        pushButton_pattern_line_trap_3_place_surface->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_3_place_surface"));

        gridLayout_pattern_line_3->addWidget(pushButton_pattern_line_trap_3_place_surface, 10, 0, 1, 5);

        pushButton_pattern_line_trap_3_place_target = new QPushButton(groupCheck_pattern_line_trap_3_enabled);
        pushButton_pattern_line_trap_3_place_target->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_3_place_target"));

        gridLayout_pattern_line_3->addWidget(pushButton_pattern_line_trap_3_place_target, 11, 0, 1, 5);


        verticalLayout_pattern_line_traps_outer->addWidget(groupCheck_pattern_line_trap_3_enabled);

        groupCheck_pattern_line_trap_4_enabled = new MyGroupBox(groupBox_pattern_line_traps);
        groupCheck_pattern_line_trap_4_enabled->setObjectName(QString::fromUtf8("groupCheck_pattern_line_trap_4_enabled"));
        groupCheck_pattern_line_trap_4_enabled->setCheckable(true);
        gridLayout_pattern_line_4 = new QGridLayout(groupCheck_pattern_line_trap_4_enabled);
        gridLayout_pattern_line_4->setSpacing(2);
        gridLayout_pattern_line_4->setObjectName(QString::fromUtf8("gridLayout_pattern_line_4"));
        label_pattern_line_4_pos = new QLabel(groupCheck_pattern_line_trap_4_enabled);
        label_pattern_line_4_pos->setObjectName(QString::fromUtf8("label_pattern_line_4_pos"));

        gridLayout_pattern_line_4->addWidget(label_pattern_line_4_pos, 0, 0, 1, 1);

        vect3_pattern_line_trap_4_position_x = new MyLineEdit(groupCheck_pattern_line_trap_4_enabled);
        vect3_pattern_line_trap_4_position_x->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_4_position_x"));

        gridLayout_pattern_line_4->addWidget(vect3_pattern_line_trap_4_position_x, 0, 1, 1, 1);

        vect3_pattern_line_trap_4_position_y = new MyLineEdit(groupCheck_pattern_line_trap_4_enabled);
        vect3_pattern_line_trap_4_position_y->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_4_position_y"));

        gridLayout_pattern_line_4->addWidget(vect3_pattern_line_trap_4_position_y, 0, 2, 1, 1);

        vect3_pattern_line_trap_4_position_z = new MyLineEdit(groupCheck_pattern_line_trap_4_enabled);
        vect3_pattern_line_trap_4_position_z->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_4_position_z"));

        gridLayout_pattern_line_4->addWidget(vect3_pattern_line_trap_4_position_z, 0, 3, 1, 1);

        label_pattern_line_4_rot = new QLabel(groupCheck_pattern_line_trap_4_enabled);
        label_pattern_line_4_rot->setObjectName(QString::fromUtf8("label_pattern_line_4_rot"));

        gridLayout_pattern_line_4->addWidget(label_pattern_line_4_rot, 1, 0, 1, 1);

        spinboxd3_pattern_line_trap_4_rotation_x = new MyDoubleSpinBox(groupCheck_pattern_line_trap_4_enabled);
        spinboxd3_pattern_line_trap_4_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_4_rotation_x"));

        gridLayout_pattern_line_4->addWidget(spinboxd3_pattern_line_trap_4_rotation_x, 1, 1, 1, 1);

        spinboxd3_pattern_line_trap_4_rotation_y = new MyDoubleSpinBox(groupCheck_pattern_line_trap_4_enabled);
        spinboxd3_pattern_line_trap_4_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_4_rotation_y"));

        gridLayout_pattern_line_4->addWidget(spinboxd3_pattern_line_trap_4_rotation_y, 1, 2, 1, 1);

        spinboxd3_pattern_line_trap_4_rotation_z = new MyDoubleSpinBox(groupCheck_pattern_line_trap_4_enabled);
        spinboxd3_pattern_line_trap_4_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_4_rotation_z"));

        gridLayout_pattern_line_4->addWidget(spinboxd3_pattern_line_trap_4_rotation_z, 1, 3, 1, 1);

        label_pattern_line_4_radius = new QLabel(groupCheck_pattern_line_trap_4_enabled);
        label_pattern_line_4_radius->setObjectName(QString::fromUtf8("label_pattern_line_4_radius"));

        gridLayout_pattern_line_4->addWidget(label_pattern_line_4_radius, 2, 0, 1, 1);

        logedit_pattern_line_trap_4_radius = new MyLineEdit(groupCheck_pattern_line_trap_4_enabled);
        logedit_pattern_line_trap_4_radius->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_4_radius"));

        gridLayout_pattern_line_4->addWidget(logedit_pattern_line_trap_4_radius, 2, 1, 1, 1);

        logedit_pattern_line_trap_4_thickness = new MyLineEdit(groupCheck_pattern_line_trap_4_enabled);
        logedit_pattern_line_trap_4_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_4_thickness"));

        gridLayout_pattern_line_4->addWidget(logedit_pattern_line_trap_4_thickness, 2, 2, 1, 1);

        logedit_pattern_line_trap_4_edge_softness = new MyLineEdit(groupCheck_pattern_line_trap_4_enabled);
        logedit_pattern_line_trap_4_edge_softness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_4_edge_softness"));

        gridLayout_pattern_line_4->addWidget(logedit_pattern_line_trap_4_edge_softness, 2, 3, 1, 1);

        logedit_pattern_line_trap_4_max_distance = new MyLineEdit(groupCheck_pattern_line_trap_4_enabled);
        logedit_pattern_line_trap_4_max_distance->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_4_max_distance"));

        gridLayout_pattern_line_4->addWidget(logedit_pattern_line_trap_4_max_distance, 2, 4, 1, 1);

        label_pattern_line_4_scale = new QLabel(groupCheck_pattern_line_trap_4_enabled);
        label_pattern_line_4_scale->setObjectName(QString::fromUtf8("label_pattern_line_4_scale"));

        gridLayout_pattern_line_4->addWidget(label_pattern_line_4_scale, 3, 0, 1, 1);

        logedit_pattern_line_trap_4_scale = new MyLineEdit(groupCheck_pattern_line_trap_4_enabled);
        logedit_pattern_line_trap_4_scale->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_4_scale"));

        gridLayout_pattern_line_4->addWidget(logedit_pattern_line_trap_4_scale, 3, 1, 1, 1);

        logedit_pattern_line_trap_4_relative_thickness = new MyLineEdit(groupCheck_pattern_line_trap_4_enabled);
        logedit_pattern_line_trap_4_relative_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_4_relative_thickness"));

        gridLayout_pattern_line_4->addWidget(logedit_pattern_line_trap_4_relative_thickness, 3, 2, 1, 1);

        label_pattern_line_4_int = new QLabel(groupCheck_pattern_line_trap_4_enabled);
        label_pattern_line_4_int->setObjectName(QString::fromUtf8("label_pattern_line_4_int"));

        gridLayout_pattern_line_4->addWidget(label_pattern_line_4_int, 4, 0, 1, 1);

        logedit_pattern_line_trap_4_intensity = new MyLineEdit(groupCheck_pattern_line_trap_4_enabled);
        logedit_pattern_line_trap_4_intensity->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_4_intensity"));

        gridLayout_pattern_line_4->addWidget(logedit_pattern_line_trap_4_intensity, 4, 1, 1, 1);

        colorButton_pattern_line_trap_4_color = new MyColorButton(groupCheck_pattern_line_trap_4_enabled);
        colorButton_pattern_line_trap_4_color->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_4_color"));

        gridLayout_pattern_line_4->addWidget(colorButton_pattern_line_trap_4_color, 4, 2, 1, 1);

        colorButton_pattern_line_trap_4_color_2 = new MyColorButton(groupCheck_pattern_line_trap_4_enabled);
        colorButton_pattern_line_trap_4_color_2->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_4_color_2"));

        gridLayout_pattern_line_4->addWidget(colorButton_pattern_line_trap_4_color_2, 4, 3, 1, 1);

        colorButton_pattern_line_trap_4_color_3 = new MyColorButton(groupCheck_pattern_line_trap_4_enabled);
        colorButton_pattern_line_trap_4_color_3->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_4_color_3"));

        gridLayout_pattern_line_4->addWidget(colorButton_pattern_line_trap_4_color_3, 4, 4, 1, 1);

        label_pattern_line_4_shape = new QLabel(groupCheck_pattern_line_trap_4_enabled);
        label_pattern_line_4_shape->setObjectName(QString::fromUtf8("label_pattern_line_4_shape"));

        gridLayout_pattern_line_4->addWidget(label_pattern_line_4_shape, 5, 0, 1, 1);

        comboBox_pattern_line_trap_4_shape = new MyComboBox(groupCheck_pattern_line_trap_4_enabled);
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->addItem(QString());
        comboBox_pattern_line_trap_4_shape->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_4_shape"));

        gridLayout_pattern_line_4->addWidget(comboBox_pattern_line_trap_4_shape, 5, 1, 1, 4);

        label_pattern_line_4_shape_aux = new QLabel(groupCheck_pattern_line_trap_4_enabled);
        label_pattern_line_4_shape_aux->setObjectName(QString::fromUtf8("label_pattern_line_4_shape_aux"));

        gridLayout_pattern_line_4->addWidget(label_pattern_line_4_shape_aux, 6, 0, 1, 1);

        logedit_pattern_line_trap_4_shape_aux = new MyLineEdit(groupCheck_pattern_line_trap_4_enabled);
        logedit_pattern_line_trap_4_shape_aux->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_4_shape_aux"));

        gridLayout_pattern_line_4->addWidget(logedit_pattern_line_trap_4_shape_aux, 6, 1, 1, 2);

        label_pattern_line_4_sharp_seg = new QLabel(groupCheck_pattern_line_trap_4_enabled);
        label_pattern_line_4_sharp_seg->setObjectName(QString::fromUtf8("label_pattern_line_4_sharp_seg"));

        gridLayout_pattern_line_4->addWidget(label_pattern_line_4_sharp_seg, 7, 0, 1, 1);

        logedit_pattern_line_trap_4_falloff_sharpness = new MyLineEdit(groupCheck_pattern_line_trap_4_enabled);
        logedit_pattern_line_trap_4_falloff_sharpness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_4_falloff_sharpness"));

        gridLayout_pattern_line_4->addWidget(logedit_pattern_line_trap_4_falloff_sharpness, 7, 1, 1, 1);

        logedit_pattern_line_trap_4_segment_half_length = new MyLineEdit(groupCheck_pattern_line_trap_4_enabled);
        logedit_pattern_line_trap_4_segment_half_length->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_4_segment_half_length"));

        gridLayout_pattern_line_4->addWidget(logedit_pattern_line_trap_4_segment_half_length, 7, 2, 1, 1);

        label_pattern_line_4_glow = new QLabel(groupCheck_pattern_line_trap_4_enabled);
        label_pattern_line_4_glow->setObjectName(QString::fromUtf8("label_pattern_line_4_glow"));

        gridLayout_pattern_line_4->addWidget(label_pattern_line_4_glow, 8, 0, 1, 1);

        logedit_pattern_line_trap_4_glow_spread = new MyLineEdit(groupCheck_pattern_line_trap_4_enabled);
        logedit_pattern_line_trap_4_glow_spread->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_4_glow_spread"));

        gridLayout_pattern_line_4->addWidget(logedit_pattern_line_trap_4_glow_spread, 8, 1, 1, 1);

        comboBox_pattern_line_trap_4_falloff_profile = new MyComboBox(groupCheck_pattern_line_trap_4_enabled);
        comboBox_pattern_line_trap_4_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_4_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_4_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_4_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_4_falloff_profile->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_4_falloff_profile"));

        gridLayout_pattern_line_4->addWidget(comboBox_pattern_line_trap_4_falloff_profile, 8, 2, 1, 3);

        label_pattern_line_4_side = new QLabel(groupCheck_pattern_line_trap_4_enabled);
        label_pattern_line_4_side->setObjectName(QString::fromUtf8("label_pattern_line_4_side"));

        gridLayout_pattern_line_4->addWidget(label_pattern_line_4_side, 9, 0, 1, 1);

        comboBox_pattern_line_trap_4_edge_side = new MyComboBox(groupCheck_pattern_line_trap_4_enabled);
        comboBox_pattern_line_trap_4_edge_side->addItem(QString());
        comboBox_pattern_line_trap_4_edge_side->addItem(QString());
        comboBox_pattern_line_trap_4_edge_side->addItem(QString());
        comboBox_pattern_line_trap_4_edge_side->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_4_edge_side"));

        gridLayout_pattern_line_4->addWidget(comboBox_pattern_line_trap_4_edge_side, 9, 1, 1, 4);

        pushButton_pattern_line_trap_4_place_surface = new QPushButton(groupCheck_pattern_line_trap_4_enabled);
        pushButton_pattern_line_trap_4_place_surface->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_4_place_surface"));

        gridLayout_pattern_line_4->addWidget(pushButton_pattern_line_trap_4_place_surface, 10, 0, 1, 5);

        pushButton_pattern_line_trap_4_place_target = new QPushButton(groupCheck_pattern_line_trap_4_enabled);
        pushButton_pattern_line_trap_4_place_target->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_4_place_target"));

        gridLayout_pattern_line_4->addWidget(pushButton_pattern_line_trap_4_place_target, 11, 0, 1, 5);


        verticalLayout_pattern_line_traps_outer->addWidget(groupCheck_pattern_line_trap_4_enabled);

        groupCheck_pattern_line_trap_5_enabled = new MyGroupBox(groupBox_pattern_line_traps);
        groupCheck_pattern_line_trap_5_enabled->setObjectName(QString::fromUtf8("groupCheck_pattern_line_trap_5_enabled"));
        groupCheck_pattern_line_trap_5_enabled->setCheckable(true);
        gridLayout_pattern_line_5 = new QGridLayout(groupCheck_pattern_line_trap_5_enabled);
        gridLayout_pattern_line_5->setSpacing(2);
        gridLayout_pattern_line_5->setObjectName(QString::fromUtf8("gridLayout_pattern_line_5"));
        label_pattern_line_5_pos = new QLabel(groupCheck_pattern_line_trap_5_enabled);
        label_pattern_line_5_pos->setObjectName(QString::fromUtf8("label_pattern_line_5_pos"));

        gridLayout_pattern_line_5->addWidget(label_pattern_line_5_pos, 0, 0, 1, 1);

        vect3_pattern_line_trap_5_position_x = new MyLineEdit(groupCheck_pattern_line_trap_5_enabled);
        vect3_pattern_line_trap_5_position_x->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_5_position_x"));

        gridLayout_pattern_line_5->addWidget(vect3_pattern_line_trap_5_position_x, 0, 1, 1, 1);

        vect3_pattern_line_trap_5_position_y = new MyLineEdit(groupCheck_pattern_line_trap_5_enabled);
        vect3_pattern_line_trap_5_position_y->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_5_position_y"));

        gridLayout_pattern_line_5->addWidget(vect3_pattern_line_trap_5_position_y, 0, 2, 1, 1);

        vect3_pattern_line_trap_5_position_z = new MyLineEdit(groupCheck_pattern_line_trap_5_enabled);
        vect3_pattern_line_trap_5_position_z->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_5_position_z"));

        gridLayout_pattern_line_5->addWidget(vect3_pattern_line_trap_5_position_z, 0, 3, 1, 1);

        label_pattern_line_5_rot = new QLabel(groupCheck_pattern_line_trap_5_enabled);
        label_pattern_line_5_rot->setObjectName(QString::fromUtf8("label_pattern_line_5_rot"));

        gridLayout_pattern_line_5->addWidget(label_pattern_line_5_rot, 1, 0, 1, 1);

        spinboxd3_pattern_line_trap_5_rotation_x = new MyDoubleSpinBox(groupCheck_pattern_line_trap_5_enabled);
        spinboxd3_pattern_line_trap_5_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_5_rotation_x"));

        gridLayout_pattern_line_5->addWidget(spinboxd3_pattern_line_trap_5_rotation_x, 1, 1, 1, 1);

        spinboxd3_pattern_line_trap_5_rotation_y = new MyDoubleSpinBox(groupCheck_pattern_line_trap_5_enabled);
        spinboxd3_pattern_line_trap_5_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_5_rotation_y"));

        gridLayout_pattern_line_5->addWidget(spinboxd3_pattern_line_trap_5_rotation_y, 1, 2, 1, 1);

        spinboxd3_pattern_line_trap_5_rotation_z = new MyDoubleSpinBox(groupCheck_pattern_line_trap_5_enabled);
        spinboxd3_pattern_line_trap_5_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_5_rotation_z"));

        gridLayout_pattern_line_5->addWidget(spinboxd3_pattern_line_trap_5_rotation_z, 1, 3, 1, 1);

        label_pattern_line_5_radius = new QLabel(groupCheck_pattern_line_trap_5_enabled);
        label_pattern_line_5_radius->setObjectName(QString::fromUtf8("label_pattern_line_5_radius"));

        gridLayout_pattern_line_5->addWidget(label_pattern_line_5_radius, 2, 0, 1, 1);

        logedit_pattern_line_trap_5_radius = new MyLineEdit(groupCheck_pattern_line_trap_5_enabled);
        logedit_pattern_line_trap_5_radius->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_5_radius"));

        gridLayout_pattern_line_5->addWidget(logedit_pattern_line_trap_5_radius, 2, 1, 1, 1);

        logedit_pattern_line_trap_5_thickness = new MyLineEdit(groupCheck_pattern_line_trap_5_enabled);
        logedit_pattern_line_trap_5_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_5_thickness"));

        gridLayout_pattern_line_5->addWidget(logedit_pattern_line_trap_5_thickness, 2, 2, 1, 1);

        logedit_pattern_line_trap_5_edge_softness = new MyLineEdit(groupCheck_pattern_line_trap_5_enabled);
        logedit_pattern_line_trap_5_edge_softness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_5_edge_softness"));

        gridLayout_pattern_line_5->addWidget(logedit_pattern_line_trap_5_edge_softness, 2, 3, 1, 1);

        logedit_pattern_line_trap_5_max_distance = new MyLineEdit(groupCheck_pattern_line_trap_5_enabled);
        logedit_pattern_line_trap_5_max_distance->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_5_max_distance"));

        gridLayout_pattern_line_5->addWidget(logedit_pattern_line_trap_5_max_distance, 2, 4, 1, 1);

        label_pattern_line_5_scale = new QLabel(groupCheck_pattern_line_trap_5_enabled);
        label_pattern_line_5_scale->setObjectName(QString::fromUtf8("label_pattern_line_5_scale"));

        gridLayout_pattern_line_5->addWidget(label_pattern_line_5_scale, 3, 0, 1, 1);

        logedit_pattern_line_trap_5_scale = new MyLineEdit(groupCheck_pattern_line_trap_5_enabled);
        logedit_pattern_line_trap_5_scale->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_5_scale"));

        gridLayout_pattern_line_5->addWidget(logedit_pattern_line_trap_5_scale, 3, 1, 1, 1);

        logedit_pattern_line_trap_5_relative_thickness = new MyLineEdit(groupCheck_pattern_line_trap_5_enabled);
        logedit_pattern_line_trap_5_relative_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_5_relative_thickness"));

        gridLayout_pattern_line_5->addWidget(logedit_pattern_line_trap_5_relative_thickness, 3, 2, 1, 1);

        label_pattern_line_5_int = new QLabel(groupCheck_pattern_line_trap_5_enabled);
        label_pattern_line_5_int->setObjectName(QString::fromUtf8("label_pattern_line_5_int"));

        gridLayout_pattern_line_5->addWidget(label_pattern_line_5_int, 4, 0, 1, 1);

        logedit_pattern_line_trap_5_intensity = new MyLineEdit(groupCheck_pattern_line_trap_5_enabled);
        logedit_pattern_line_trap_5_intensity->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_5_intensity"));

        gridLayout_pattern_line_5->addWidget(logedit_pattern_line_trap_5_intensity, 4, 1, 1, 1);

        colorButton_pattern_line_trap_5_color = new MyColorButton(groupCheck_pattern_line_trap_5_enabled);
        colorButton_pattern_line_trap_5_color->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_5_color"));

        gridLayout_pattern_line_5->addWidget(colorButton_pattern_line_trap_5_color, 4, 2, 1, 1);

        colorButton_pattern_line_trap_5_color_2 = new MyColorButton(groupCheck_pattern_line_trap_5_enabled);
        colorButton_pattern_line_trap_5_color_2->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_5_color_2"));

        gridLayout_pattern_line_5->addWidget(colorButton_pattern_line_trap_5_color_2, 4, 3, 1, 1);

        colorButton_pattern_line_trap_5_color_3 = new MyColorButton(groupCheck_pattern_line_trap_5_enabled);
        colorButton_pattern_line_trap_5_color_3->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_5_color_3"));

        gridLayout_pattern_line_5->addWidget(colorButton_pattern_line_trap_5_color_3, 4, 4, 1, 1);

        label_pattern_line_5_shape = new QLabel(groupCheck_pattern_line_trap_5_enabled);
        label_pattern_line_5_shape->setObjectName(QString::fromUtf8("label_pattern_line_5_shape"));

        gridLayout_pattern_line_5->addWidget(label_pattern_line_5_shape, 5, 0, 1, 1);

        comboBox_pattern_line_trap_5_shape = new MyComboBox(groupCheck_pattern_line_trap_5_enabled);
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->addItem(QString());
        comboBox_pattern_line_trap_5_shape->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_5_shape"));

        gridLayout_pattern_line_5->addWidget(comboBox_pattern_line_trap_5_shape, 5, 1, 1, 4);

        label_pattern_line_5_shape_aux = new QLabel(groupCheck_pattern_line_trap_5_enabled);
        label_pattern_line_5_shape_aux->setObjectName(QString::fromUtf8("label_pattern_line_5_shape_aux"));

        gridLayout_pattern_line_5->addWidget(label_pattern_line_5_shape_aux, 6, 0, 1, 1);

        logedit_pattern_line_trap_5_shape_aux = new MyLineEdit(groupCheck_pattern_line_trap_5_enabled);
        logedit_pattern_line_trap_5_shape_aux->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_5_shape_aux"));

        gridLayout_pattern_line_5->addWidget(logedit_pattern_line_trap_5_shape_aux, 6, 1, 1, 2);

        label_pattern_line_5_sharp_seg = new QLabel(groupCheck_pattern_line_trap_5_enabled);
        label_pattern_line_5_sharp_seg->setObjectName(QString::fromUtf8("label_pattern_line_5_sharp_seg"));

        gridLayout_pattern_line_5->addWidget(label_pattern_line_5_sharp_seg, 7, 0, 1, 1);

        logedit_pattern_line_trap_5_falloff_sharpness = new MyLineEdit(groupCheck_pattern_line_trap_5_enabled);
        logedit_pattern_line_trap_5_falloff_sharpness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_5_falloff_sharpness"));

        gridLayout_pattern_line_5->addWidget(logedit_pattern_line_trap_5_falloff_sharpness, 7, 1, 1, 1);

        logedit_pattern_line_trap_5_segment_half_length = new MyLineEdit(groupCheck_pattern_line_trap_5_enabled);
        logedit_pattern_line_trap_5_segment_half_length->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_5_segment_half_length"));

        gridLayout_pattern_line_5->addWidget(logedit_pattern_line_trap_5_segment_half_length, 7, 2, 1, 1);

        label_pattern_line_5_glow = new QLabel(groupCheck_pattern_line_trap_5_enabled);
        label_pattern_line_5_glow->setObjectName(QString::fromUtf8("label_pattern_line_5_glow"));

        gridLayout_pattern_line_5->addWidget(label_pattern_line_5_glow, 8, 0, 1, 1);

        logedit_pattern_line_trap_5_glow_spread = new MyLineEdit(groupCheck_pattern_line_trap_5_enabled);
        logedit_pattern_line_trap_5_glow_spread->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_5_glow_spread"));

        gridLayout_pattern_line_5->addWidget(logedit_pattern_line_trap_5_glow_spread, 8, 1, 1, 1);

        comboBox_pattern_line_trap_5_falloff_profile = new MyComboBox(groupCheck_pattern_line_trap_5_enabled);
        comboBox_pattern_line_trap_5_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_5_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_5_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_5_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_5_falloff_profile->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_5_falloff_profile"));

        gridLayout_pattern_line_5->addWidget(comboBox_pattern_line_trap_5_falloff_profile, 8, 2, 1, 3);

        label_pattern_line_5_side = new QLabel(groupCheck_pattern_line_trap_5_enabled);
        label_pattern_line_5_side->setObjectName(QString::fromUtf8("label_pattern_line_5_side"));

        gridLayout_pattern_line_5->addWidget(label_pattern_line_5_side, 9, 0, 1, 1);

        comboBox_pattern_line_trap_5_edge_side = new MyComboBox(groupCheck_pattern_line_trap_5_enabled);
        comboBox_pattern_line_trap_5_edge_side->addItem(QString());
        comboBox_pattern_line_trap_5_edge_side->addItem(QString());
        comboBox_pattern_line_trap_5_edge_side->addItem(QString());
        comboBox_pattern_line_trap_5_edge_side->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_5_edge_side"));

        gridLayout_pattern_line_5->addWidget(comboBox_pattern_line_trap_5_edge_side, 9, 1, 1, 4);

        pushButton_pattern_line_trap_5_place_surface = new QPushButton(groupCheck_pattern_line_trap_5_enabled);
        pushButton_pattern_line_trap_5_place_surface->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_5_place_surface"));

        gridLayout_pattern_line_5->addWidget(pushButton_pattern_line_trap_5_place_surface, 10, 0, 1, 5);

        pushButton_pattern_line_trap_5_place_target = new QPushButton(groupCheck_pattern_line_trap_5_enabled);
        pushButton_pattern_line_trap_5_place_target->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_5_place_target"));

        gridLayout_pattern_line_5->addWidget(pushButton_pattern_line_trap_5_place_target, 11, 0, 1, 5);


        verticalLayout_pattern_line_traps_outer->addWidget(groupCheck_pattern_line_trap_5_enabled);

        groupCheck_pattern_line_trap_6_enabled = new MyGroupBox(groupBox_pattern_line_traps);
        groupCheck_pattern_line_trap_6_enabled->setObjectName(QString::fromUtf8("groupCheck_pattern_line_trap_6_enabled"));
        groupCheck_pattern_line_trap_6_enabled->setCheckable(true);
        gridLayout_pattern_line_6 = new QGridLayout(groupCheck_pattern_line_trap_6_enabled);
        gridLayout_pattern_line_6->setSpacing(2);
        gridLayout_pattern_line_6->setObjectName(QString::fromUtf8("gridLayout_pattern_line_6"));
        label_pattern_line_6_pos = new QLabel(groupCheck_pattern_line_trap_6_enabled);
        label_pattern_line_6_pos->setObjectName(QString::fromUtf8("label_pattern_line_6_pos"));

        gridLayout_pattern_line_6->addWidget(label_pattern_line_6_pos, 0, 0, 1, 1);

        vect3_pattern_line_trap_6_position_x = new MyLineEdit(groupCheck_pattern_line_trap_6_enabled);
        vect3_pattern_line_trap_6_position_x->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_6_position_x"));

        gridLayout_pattern_line_6->addWidget(vect3_pattern_line_trap_6_position_x, 0, 1, 1, 1);

        vect3_pattern_line_trap_6_position_y = new MyLineEdit(groupCheck_pattern_line_trap_6_enabled);
        vect3_pattern_line_trap_6_position_y->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_6_position_y"));

        gridLayout_pattern_line_6->addWidget(vect3_pattern_line_trap_6_position_y, 0, 2, 1, 1);

        vect3_pattern_line_trap_6_position_z = new MyLineEdit(groupCheck_pattern_line_trap_6_enabled);
        vect3_pattern_line_trap_6_position_z->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_6_position_z"));

        gridLayout_pattern_line_6->addWidget(vect3_pattern_line_trap_6_position_z, 0, 3, 1, 1);

        label_pattern_line_6_rot = new QLabel(groupCheck_pattern_line_trap_6_enabled);
        label_pattern_line_6_rot->setObjectName(QString::fromUtf8("label_pattern_line_6_rot"));

        gridLayout_pattern_line_6->addWidget(label_pattern_line_6_rot, 1, 0, 1, 1);

        spinboxd3_pattern_line_trap_6_rotation_x = new MyDoubleSpinBox(groupCheck_pattern_line_trap_6_enabled);
        spinboxd3_pattern_line_trap_6_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_6_rotation_x"));

        gridLayout_pattern_line_6->addWidget(spinboxd3_pattern_line_trap_6_rotation_x, 1, 1, 1, 1);

        spinboxd3_pattern_line_trap_6_rotation_y = new MyDoubleSpinBox(groupCheck_pattern_line_trap_6_enabled);
        spinboxd3_pattern_line_trap_6_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_6_rotation_y"));

        gridLayout_pattern_line_6->addWidget(spinboxd3_pattern_line_trap_6_rotation_y, 1, 2, 1, 1);

        spinboxd3_pattern_line_trap_6_rotation_z = new MyDoubleSpinBox(groupCheck_pattern_line_trap_6_enabled);
        spinboxd3_pattern_line_trap_6_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_6_rotation_z"));

        gridLayout_pattern_line_6->addWidget(spinboxd3_pattern_line_trap_6_rotation_z, 1, 3, 1, 1);

        label_pattern_line_6_radius = new QLabel(groupCheck_pattern_line_trap_6_enabled);
        label_pattern_line_6_radius->setObjectName(QString::fromUtf8("label_pattern_line_6_radius"));

        gridLayout_pattern_line_6->addWidget(label_pattern_line_6_radius, 2, 0, 1, 1);

        logedit_pattern_line_trap_6_radius = new MyLineEdit(groupCheck_pattern_line_trap_6_enabled);
        logedit_pattern_line_trap_6_radius->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_6_radius"));

        gridLayout_pattern_line_6->addWidget(logedit_pattern_line_trap_6_radius, 2, 1, 1, 1);

        logedit_pattern_line_trap_6_thickness = new MyLineEdit(groupCheck_pattern_line_trap_6_enabled);
        logedit_pattern_line_trap_6_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_6_thickness"));

        gridLayout_pattern_line_6->addWidget(logedit_pattern_line_trap_6_thickness, 2, 2, 1, 1);

        logedit_pattern_line_trap_6_edge_softness = new MyLineEdit(groupCheck_pattern_line_trap_6_enabled);
        logedit_pattern_line_trap_6_edge_softness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_6_edge_softness"));

        gridLayout_pattern_line_6->addWidget(logedit_pattern_line_trap_6_edge_softness, 2, 3, 1, 1);

        logedit_pattern_line_trap_6_max_distance = new MyLineEdit(groupCheck_pattern_line_trap_6_enabled);
        logedit_pattern_line_trap_6_max_distance->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_6_max_distance"));

        gridLayout_pattern_line_6->addWidget(logedit_pattern_line_trap_6_max_distance, 2, 4, 1, 1);

        label_pattern_line_6_scale = new QLabel(groupCheck_pattern_line_trap_6_enabled);
        label_pattern_line_6_scale->setObjectName(QString::fromUtf8("label_pattern_line_6_scale"));

        gridLayout_pattern_line_6->addWidget(label_pattern_line_6_scale, 3, 0, 1, 1);

        logedit_pattern_line_trap_6_scale = new MyLineEdit(groupCheck_pattern_line_trap_6_enabled);
        logedit_pattern_line_trap_6_scale->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_6_scale"));

        gridLayout_pattern_line_6->addWidget(logedit_pattern_line_trap_6_scale, 3, 1, 1, 1);

        logedit_pattern_line_trap_6_relative_thickness = new MyLineEdit(groupCheck_pattern_line_trap_6_enabled);
        logedit_pattern_line_trap_6_relative_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_6_relative_thickness"));

        gridLayout_pattern_line_6->addWidget(logedit_pattern_line_trap_6_relative_thickness, 3, 2, 1, 1);

        label_pattern_line_6_int = new QLabel(groupCheck_pattern_line_trap_6_enabled);
        label_pattern_line_6_int->setObjectName(QString::fromUtf8("label_pattern_line_6_int"));

        gridLayout_pattern_line_6->addWidget(label_pattern_line_6_int, 4, 0, 1, 1);

        logedit_pattern_line_trap_6_intensity = new MyLineEdit(groupCheck_pattern_line_trap_6_enabled);
        logedit_pattern_line_trap_6_intensity->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_6_intensity"));

        gridLayout_pattern_line_6->addWidget(logedit_pattern_line_trap_6_intensity, 4, 1, 1, 1);

        colorButton_pattern_line_trap_6_color = new MyColorButton(groupCheck_pattern_line_trap_6_enabled);
        colorButton_pattern_line_trap_6_color->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_6_color"));

        gridLayout_pattern_line_6->addWidget(colorButton_pattern_line_trap_6_color, 4, 2, 1, 1);

        colorButton_pattern_line_trap_6_color_2 = new MyColorButton(groupCheck_pattern_line_trap_6_enabled);
        colorButton_pattern_line_trap_6_color_2->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_6_color_2"));

        gridLayout_pattern_line_6->addWidget(colorButton_pattern_line_trap_6_color_2, 4, 3, 1, 1);

        colorButton_pattern_line_trap_6_color_3 = new MyColorButton(groupCheck_pattern_line_trap_6_enabled);
        colorButton_pattern_line_trap_6_color_3->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_6_color_3"));

        gridLayout_pattern_line_6->addWidget(colorButton_pattern_line_trap_6_color_3, 4, 4, 1, 1);

        label_pattern_line_6_shape = new QLabel(groupCheck_pattern_line_trap_6_enabled);
        label_pattern_line_6_shape->setObjectName(QString::fromUtf8("label_pattern_line_6_shape"));

        gridLayout_pattern_line_6->addWidget(label_pattern_line_6_shape, 5, 0, 1, 1);

        comboBox_pattern_line_trap_6_shape = new MyComboBox(groupCheck_pattern_line_trap_6_enabled);
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->addItem(QString());
        comboBox_pattern_line_trap_6_shape->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_6_shape"));

        gridLayout_pattern_line_6->addWidget(comboBox_pattern_line_trap_6_shape, 5, 1, 1, 4);

        label_pattern_line_6_shape_aux = new QLabel(groupCheck_pattern_line_trap_6_enabled);
        label_pattern_line_6_shape_aux->setObjectName(QString::fromUtf8("label_pattern_line_6_shape_aux"));

        gridLayout_pattern_line_6->addWidget(label_pattern_line_6_shape_aux, 6, 0, 1, 1);

        logedit_pattern_line_trap_6_shape_aux = new MyLineEdit(groupCheck_pattern_line_trap_6_enabled);
        logedit_pattern_line_trap_6_shape_aux->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_6_shape_aux"));

        gridLayout_pattern_line_6->addWidget(logedit_pattern_line_trap_6_shape_aux, 6, 1, 1, 2);

        label_pattern_line_6_sharp_seg = new QLabel(groupCheck_pattern_line_trap_6_enabled);
        label_pattern_line_6_sharp_seg->setObjectName(QString::fromUtf8("label_pattern_line_6_sharp_seg"));

        gridLayout_pattern_line_6->addWidget(label_pattern_line_6_sharp_seg, 7, 0, 1, 1);

        logedit_pattern_line_trap_6_falloff_sharpness = new MyLineEdit(groupCheck_pattern_line_trap_6_enabled);
        logedit_pattern_line_trap_6_falloff_sharpness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_6_falloff_sharpness"));

        gridLayout_pattern_line_6->addWidget(logedit_pattern_line_trap_6_falloff_sharpness, 7, 1, 1, 1);

        logedit_pattern_line_trap_6_segment_half_length = new MyLineEdit(groupCheck_pattern_line_trap_6_enabled);
        logedit_pattern_line_trap_6_segment_half_length->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_6_segment_half_length"));

        gridLayout_pattern_line_6->addWidget(logedit_pattern_line_trap_6_segment_half_length, 7, 2, 1, 1);

        label_pattern_line_6_glow = new QLabel(groupCheck_pattern_line_trap_6_enabled);
        label_pattern_line_6_glow->setObjectName(QString::fromUtf8("label_pattern_line_6_glow"));

        gridLayout_pattern_line_6->addWidget(label_pattern_line_6_glow, 8, 0, 1, 1);

        logedit_pattern_line_trap_6_glow_spread = new MyLineEdit(groupCheck_pattern_line_trap_6_enabled);
        logedit_pattern_line_trap_6_glow_spread->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_6_glow_spread"));

        gridLayout_pattern_line_6->addWidget(logedit_pattern_line_trap_6_glow_spread, 8, 1, 1, 1);

        comboBox_pattern_line_trap_6_falloff_profile = new MyComboBox(groupCheck_pattern_line_trap_6_enabled);
        comboBox_pattern_line_trap_6_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_6_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_6_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_6_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_6_falloff_profile->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_6_falloff_profile"));

        gridLayout_pattern_line_6->addWidget(comboBox_pattern_line_trap_6_falloff_profile, 8, 2, 1, 3);

        label_pattern_line_6_side = new QLabel(groupCheck_pattern_line_trap_6_enabled);
        label_pattern_line_6_side->setObjectName(QString::fromUtf8("label_pattern_line_6_side"));

        gridLayout_pattern_line_6->addWidget(label_pattern_line_6_side, 9, 0, 1, 1);

        comboBox_pattern_line_trap_6_edge_side = new MyComboBox(groupCheck_pattern_line_trap_6_enabled);
        comboBox_pattern_line_trap_6_edge_side->addItem(QString());
        comboBox_pattern_line_trap_6_edge_side->addItem(QString());
        comboBox_pattern_line_trap_6_edge_side->addItem(QString());
        comboBox_pattern_line_trap_6_edge_side->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_6_edge_side"));

        gridLayout_pattern_line_6->addWidget(comboBox_pattern_line_trap_6_edge_side, 9, 1, 1, 4);

        pushButton_pattern_line_trap_6_place_surface = new QPushButton(groupCheck_pattern_line_trap_6_enabled);
        pushButton_pattern_line_trap_6_place_surface->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_6_place_surface"));

        gridLayout_pattern_line_6->addWidget(pushButton_pattern_line_trap_6_place_surface, 10, 0, 1, 5);

        pushButton_pattern_line_trap_6_place_target = new QPushButton(groupCheck_pattern_line_trap_6_enabled);
        pushButton_pattern_line_trap_6_place_target->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_6_place_target"));

        gridLayout_pattern_line_6->addWidget(pushButton_pattern_line_trap_6_place_target, 11, 0, 1, 5);


        verticalLayout_pattern_line_traps_outer->addWidget(groupCheck_pattern_line_trap_6_enabled);

        groupCheck_pattern_line_trap_7_enabled = new MyGroupBox(groupBox_pattern_line_traps);
        groupCheck_pattern_line_trap_7_enabled->setObjectName(QString::fromUtf8("groupCheck_pattern_line_trap_7_enabled"));
        groupCheck_pattern_line_trap_7_enabled->setCheckable(true);
        gridLayout_pattern_line_7 = new QGridLayout(groupCheck_pattern_line_trap_7_enabled);
        gridLayout_pattern_line_7->setSpacing(2);
        gridLayout_pattern_line_7->setObjectName(QString::fromUtf8("gridLayout_pattern_line_7"));
        label_pattern_line_7_pos = new QLabel(groupCheck_pattern_line_trap_7_enabled);
        label_pattern_line_7_pos->setObjectName(QString::fromUtf8("label_pattern_line_7_pos"));

        gridLayout_pattern_line_7->addWidget(label_pattern_line_7_pos, 0, 0, 1, 1);

        vect3_pattern_line_trap_7_position_x = new MyLineEdit(groupCheck_pattern_line_trap_7_enabled);
        vect3_pattern_line_trap_7_position_x->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_7_position_x"));

        gridLayout_pattern_line_7->addWidget(vect3_pattern_line_trap_7_position_x, 0, 1, 1, 1);

        vect3_pattern_line_trap_7_position_y = new MyLineEdit(groupCheck_pattern_line_trap_7_enabled);
        vect3_pattern_line_trap_7_position_y->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_7_position_y"));

        gridLayout_pattern_line_7->addWidget(vect3_pattern_line_trap_7_position_y, 0, 2, 1, 1);

        vect3_pattern_line_trap_7_position_z = new MyLineEdit(groupCheck_pattern_line_trap_7_enabled);
        vect3_pattern_line_trap_7_position_z->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_7_position_z"));

        gridLayout_pattern_line_7->addWidget(vect3_pattern_line_trap_7_position_z, 0, 3, 1, 1);

        label_pattern_line_7_rot = new QLabel(groupCheck_pattern_line_trap_7_enabled);
        label_pattern_line_7_rot->setObjectName(QString::fromUtf8("label_pattern_line_7_rot"));

        gridLayout_pattern_line_7->addWidget(label_pattern_line_7_rot, 1, 0, 1, 1);

        spinboxd3_pattern_line_trap_7_rotation_x = new MyDoubleSpinBox(groupCheck_pattern_line_trap_7_enabled);
        spinboxd3_pattern_line_trap_7_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_7_rotation_x"));

        gridLayout_pattern_line_7->addWidget(spinboxd3_pattern_line_trap_7_rotation_x, 1, 1, 1, 1);

        spinboxd3_pattern_line_trap_7_rotation_y = new MyDoubleSpinBox(groupCheck_pattern_line_trap_7_enabled);
        spinboxd3_pattern_line_trap_7_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_7_rotation_y"));

        gridLayout_pattern_line_7->addWidget(spinboxd3_pattern_line_trap_7_rotation_y, 1, 2, 1, 1);

        spinboxd3_pattern_line_trap_7_rotation_z = new MyDoubleSpinBox(groupCheck_pattern_line_trap_7_enabled);
        spinboxd3_pattern_line_trap_7_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_7_rotation_z"));

        gridLayout_pattern_line_7->addWidget(spinboxd3_pattern_line_trap_7_rotation_z, 1, 3, 1, 1);

        label_pattern_line_7_radius = new QLabel(groupCheck_pattern_line_trap_7_enabled);
        label_pattern_line_7_radius->setObjectName(QString::fromUtf8("label_pattern_line_7_radius"));

        gridLayout_pattern_line_7->addWidget(label_pattern_line_7_radius, 2, 0, 1, 1);

        logedit_pattern_line_trap_7_radius = new MyLineEdit(groupCheck_pattern_line_trap_7_enabled);
        logedit_pattern_line_trap_7_radius->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_7_radius"));

        gridLayout_pattern_line_7->addWidget(logedit_pattern_line_trap_7_radius, 2, 1, 1, 1);

        logedit_pattern_line_trap_7_thickness = new MyLineEdit(groupCheck_pattern_line_trap_7_enabled);
        logedit_pattern_line_trap_7_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_7_thickness"));

        gridLayout_pattern_line_7->addWidget(logedit_pattern_line_trap_7_thickness, 2, 2, 1, 1);

        logedit_pattern_line_trap_7_edge_softness = new MyLineEdit(groupCheck_pattern_line_trap_7_enabled);
        logedit_pattern_line_trap_7_edge_softness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_7_edge_softness"));

        gridLayout_pattern_line_7->addWidget(logedit_pattern_line_trap_7_edge_softness, 2, 3, 1, 1);

        logedit_pattern_line_trap_7_max_distance = new MyLineEdit(groupCheck_pattern_line_trap_7_enabled);
        logedit_pattern_line_trap_7_max_distance->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_7_max_distance"));

        gridLayout_pattern_line_7->addWidget(logedit_pattern_line_trap_7_max_distance, 2, 4, 1, 1);

        label_pattern_line_7_scale = new QLabel(groupCheck_pattern_line_trap_7_enabled);
        label_pattern_line_7_scale->setObjectName(QString::fromUtf8("label_pattern_line_7_scale"));

        gridLayout_pattern_line_7->addWidget(label_pattern_line_7_scale, 3, 0, 1, 1);

        logedit_pattern_line_trap_7_scale = new MyLineEdit(groupCheck_pattern_line_trap_7_enabled);
        logedit_pattern_line_trap_7_scale->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_7_scale"));

        gridLayout_pattern_line_7->addWidget(logedit_pattern_line_trap_7_scale, 3, 1, 1, 1);

        logedit_pattern_line_trap_7_relative_thickness = new MyLineEdit(groupCheck_pattern_line_trap_7_enabled);
        logedit_pattern_line_trap_7_relative_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_7_relative_thickness"));

        gridLayout_pattern_line_7->addWidget(logedit_pattern_line_trap_7_relative_thickness, 3, 2, 1, 1);

        label_pattern_line_7_int = new QLabel(groupCheck_pattern_line_trap_7_enabled);
        label_pattern_line_7_int->setObjectName(QString::fromUtf8("label_pattern_line_7_int"));

        gridLayout_pattern_line_7->addWidget(label_pattern_line_7_int, 4, 0, 1, 1);

        logedit_pattern_line_trap_7_intensity = new MyLineEdit(groupCheck_pattern_line_trap_7_enabled);
        logedit_pattern_line_trap_7_intensity->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_7_intensity"));

        gridLayout_pattern_line_7->addWidget(logedit_pattern_line_trap_7_intensity, 4, 1, 1, 1);

        colorButton_pattern_line_trap_7_color = new MyColorButton(groupCheck_pattern_line_trap_7_enabled);
        colorButton_pattern_line_trap_7_color->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_7_color"));

        gridLayout_pattern_line_7->addWidget(colorButton_pattern_line_trap_7_color, 4, 2, 1, 1);

        colorButton_pattern_line_trap_7_color_2 = new MyColorButton(groupCheck_pattern_line_trap_7_enabled);
        colorButton_pattern_line_trap_7_color_2->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_7_color_2"));

        gridLayout_pattern_line_7->addWidget(colorButton_pattern_line_trap_7_color_2, 4, 3, 1, 1);

        colorButton_pattern_line_trap_7_color_3 = new MyColorButton(groupCheck_pattern_line_trap_7_enabled);
        colorButton_pattern_line_trap_7_color_3->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_7_color_3"));

        gridLayout_pattern_line_7->addWidget(colorButton_pattern_line_trap_7_color_3, 4, 4, 1, 1);

        label_pattern_line_7_shape = new QLabel(groupCheck_pattern_line_trap_7_enabled);
        label_pattern_line_7_shape->setObjectName(QString::fromUtf8("label_pattern_line_7_shape"));

        gridLayout_pattern_line_7->addWidget(label_pattern_line_7_shape, 5, 0, 1, 1);

        comboBox_pattern_line_trap_7_shape = new MyComboBox(groupCheck_pattern_line_trap_7_enabled);
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->addItem(QString());
        comboBox_pattern_line_trap_7_shape->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_7_shape"));

        gridLayout_pattern_line_7->addWidget(comboBox_pattern_line_trap_7_shape, 5, 1, 1, 4);

        label_pattern_line_7_shape_aux = new QLabel(groupCheck_pattern_line_trap_7_enabled);
        label_pattern_line_7_shape_aux->setObjectName(QString::fromUtf8("label_pattern_line_7_shape_aux"));

        gridLayout_pattern_line_7->addWidget(label_pattern_line_7_shape_aux, 6, 0, 1, 1);

        logedit_pattern_line_trap_7_shape_aux = new MyLineEdit(groupCheck_pattern_line_trap_7_enabled);
        logedit_pattern_line_trap_7_shape_aux->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_7_shape_aux"));

        gridLayout_pattern_line_7->addWidget(logedit_pattern_line_trap_7_shape_aux, 6, 1, 1, 2);

        label_pattern_line_7_sharp_seg = new QLabel(groupCheck_pattern_line_trap_7_enabled);
        label_pattern_line_7_sharp_seg->setObjectName(QString::fromUtf8("label_pattern_line_7_sharp_seg"));

        gridLayout_pattern_line_7->addWidget(label_pattern_line_7_sharp_seg, 7, 0, 1, 1);

        logedit_pattern_line_trap_7_falloff_sharpness = new MyLineEdit(groupCheck_pattern_line_trap_7_enabled);
        logedit_pattern_line_trap_7_falloff_sharpness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_7_falloff_sharpness"));

        gridLayout_pattern_line_7->addWidget(logedit_pattern_line_trap_7_falloff_sharpness, 7, 1, 1, 1);

        logedit_pattern_line_trap_7_segment_half_length = new MyLineEdit(groupCheck_pattern_line_trap_7_enabled);
        logedit_pattern_line_trap_7_segment_half_length->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_7_segment_half_length"));

        gridLayout_pattern_line_7->addWidget(logedit_pattern_line_trap_7_segment_half_length, 7, 2, 1, 1);

        label_pattern_line_7_glow = new QLabel(groupCheck_pattern_line_trap_7_enabled);
        label_pattern_line_7_glow->setObjectName(QString::fromUtf8("label_pattern_line_7_glow"));

        gridLayout_pattern_line_7->addWidget(label_pattern_line_7_glow, 8, 0, 1, 1);

        logedit_pattern_line_trap_7_glow_spread = new MyLineEdit(groupCheck_pattern_line_trap_7_enabled);
        logedit_pattern_line_trap_7_glow_spread->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_7_glow_spread"));

        gridLayout_pattern_line_7->addWidget(logedit_pattern_line_trap_7_glow_spread, 8, 1, 1, 1);

        comboBox_pattern_line_trap_7_falloff_profile = new MyComboBox(groupCheck_pattern_line_trap_7_enabled);
        comboBox_pattern_line_trap_7_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_7_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_7_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_7_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_7_falloff_profile->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_7_falloff_profile"));

        gridLayout_pattern_line_7->addWidget(comboBox_pattern_line_trap_7_falloff_profile, 8, 2, 1, 3);

        label_pattern_line_7_side = new QLabel(groupCheck_pattern_line_trap_7_enabled);
        label_pattern_line_7_side->setObjectName(QString::fromUtf8("label_pattern_line_7_side"));

        gridLayout_pattern_line_7->addWidget(label_pattern_line_7_side, 9, 0, 1, 1);

        comboBox_pattern_line_trap_7_edge_side = new MyComboBox(groupCheck_pattern_line_trap_7_enabled);
        comboBox_pattern_line_trap_7_edge_side->addItem(QString());
        comboBox_pattern_line_trap_7_edge_side->addItem(QString());
        comboBox_pattern_line_trap_7_edge_side->addItem(QString());
        comboBox_pattern_line_trap_7_edge_side->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_7_edge_side"));

        gridLayout_pattern_line_7->addWidget(comboBox_pattern_line_trap_7_edge_side, 9, 1, 1, 4);

        pushButton_pattern_line_trap_7_place_surface = new QPushButton(groupCheck_pattern_line_trap_7_enabled);
        pushButton_pattern_line_trap_7_place_surface->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_7_place_surface"));

        gridLayout_pattern_line_7->addWidget(pushButton_pattern_line_trap_7_place_surface, 10, 0, 1, 5);

        pushButton_pattern_line_trap_7_place_target = new QPushButton(groupCheck_pattern_line_trap_7_enabled);
        pushButton_pattern_line_trap_7_place_target->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_7_place_target"));

        gridLayout_pattern_line_7->addWidget(pushButton_pattern_line_trap_7_place_target, 11, 0, 1, 5);


        verticalLayout_pattern_line_traps_outer->addWidget(groupCheck_pattern_line_trap_7_enabled);

        groupCheck_pattern_line_trap_8_enabled = new MyGroupBox(groupBox_pattern_line_traps);
        groupCheck_pattern_line_trap_8_enabled->setObjectName(QString::fromUtf8("groupCheck_pattern_line_trap_8_enabled"));
        groupCheck_pattern_line_trap_8_enabled->setCheckable(true);
        gridLayout_pattern_line_8 = new QGridLayout(groupCheck_pattern_line_trap_8_enabled);
        gridLayout_pattern_line_8->setSpacing(2);
        gridLayout_pattern_line_8->setObjectName(QString::fromUtf8("gridLayout_pattern_line_8"));
        label_pattern_line_8_pos = new QLabel(groupCheck_pattern_line_trap_8_enabled);
        label_pattern_line_8_pos->setObjectName(QString::fromUtf8("label_pattern_line_8_pos"));

        gridLayout_pattern_line_8->addWidget(label_pattern_line_8_pos, 0, 0, 1, 1);

        vect3_pattern_line_trap_8_position_x = new MyLineEdit(groupCheck_pattern_line_trap_8_enabled);
        vect3_pattern_line_trap_8_position_x->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_8_position_x"));

        gridLayout_pattern_line_8->addWidget(vect3_pattern_line_trap_8_position_x, 0, 1, 1, 1);

        vect3_pattern_line_trap_8_position_y = new MyLineEdit(groupCheck_pattern_line_trap_8_enabled);
        vect3_pattern_line_trap_8_position_y->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_8_position_y"));

        gridLayout_pattern_line_8->addWidget(vect3_pattern_line_trap_8_position_y, 0, 2, 1, 1);

        vect3_pattern_line_trap_8_position_z = new MyLineEdit(groupCheck_pattern_line_trap_8_enabled);
        vect3_pattern_line_trap_8_position_z->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_8_position_z"));

        gridLayout_pattern_line_8->addWidget(vect3_pattern_line_trap_8_position_z, 0, 3, 1, 1);

        label_pattern_line_8_rot = new QLabel(groupCheck_pattern_line_trap_8_enabled);
        label_pattern_line_8_rot->setObjectName(QString::fromUtf8("label_pattern_line_8_rot"));

        gridLayout_pattern_line_8->addWidget(label_pattern_line_8_rot, 1, 0, 1, 1);

        spinboxd3_pattern_line_trap_8_rotation_x = new MyDoubleSpinBox(groupCheck_pattern_line_trap_8_enabled);
        spinboxd3_pattern_line_trap_8_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_8_rotation_x"));

        gridLayout_pattern_line_8->addWidget(spinboxd3_pattern_line_trap_8_rotation_x, 1, 1, 1, 1);

        spinboxd3_pattern_line_trap_8_rotation_y = new MyDoubleSpinBox(groupCheck_pattern_line_trap_8_enabled);
        spinboxd3_pattern_line_trap_8_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_8_rotation_y"));

        gridLayout_pattern_line_8->addWidget(spinboxd3_pattern_line_trap_8_rotation_y, 1, 2, 1, 1);

        spinboxd3_pattern_line_trap_8_rotation_z = new MyDoubleSpinBox(groupCheck_pattern_line_trap_8_enabled);
        spinboxd3_pattern_line_trap_8_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_8_rotation_z"));

        gridLayout_pattern_line_8->addWidget(spinboxd3_pattern_line_trap_8_rotation_z, 1, 3, 1, 1);

        label_pattern_line_8_radius = new QLabel(groupCheck_pattern_line_trap_8_enabled);
        label_pattern_line_8_radius->setObjectName(QString::fromUtf8("label_pattern_line_8_radius"));

        gridLayout_pattern_line_8->addWidget(label_pattern_line_8_radius, 2, 0, 1, 1);

        logedit_pattern_line_trap_8_radius = new MyLineEdit(groupCheck_pattern_line_trap_8_enabled);
        logedit_pattern_line_trap_8_radius->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_8_radius"));

        gridLayout_pattern_line_8->addWidget(logedit_pattern_line_trap_8_radius, 2, 1, 1, 1);

        logedit_pattern_line_trap_8_thickness = new MyLineEdit(groupCheck_pattern_line_trap_8_enabled);
        logedit_pattern_line_trap_8_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_8_thickness"));

        gridLayout_pattern_line_8->addWidget(logedit_pattern_line_trap_8_thickness, 2, 2, 1, 1);

        logedit_pattern_line_trap_8_edge_softness = new MyLineEdit(groupCheck_pattern_line_trap_8_enabled);
        logedit_pattern_line_trap_8_edge_softness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_8_edge_softness"));

        gridLayout_pattern_line_8->addWidget(logedit_pattern_line_trap_8_edge_softness, 2, 3, 1, 1);

        logedit_pattern_line_trap_8_max_distance = new MyLineEdit(groupCheck_pattern_line_trap_8_enabled);
        logedit_pattern_line_trap_8_max_distance->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_8_max_distance"));

        gridLayout_pattern_line_8->addWidget(logedit_pattern_line_trap_8_max_distance, 2, 4, 1, 1);

        label_pattern_line_8_scale = new QLabel(groupCheck_pattern_line_trap_8_enabled);
        label_pattern_line_8_scale->setObjectName(QString::fromUtf8("label_pattern_line_8_scale"));

        gridLayout_pattern_line_8->addWidget(label_pattern_line_8_scale, 3, 0, 1, 1);

        logedit_pattern_line_trap_8_scale = new MyLineEdit(groupCheck_pattern_line_trap_8_enabled);
        logedit_pattern_line_trap_8_scale->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_8_scale"));

        gridLayout_pattern_line_8->addWidget(logedit_pattern_line_trap_8_scale, 3, 1, 1, 1);

        logedit_pattern_line_trap_8_relative_thickness = new MyLineEdit(groupCheck_pattern_line_trap_8_enabled);
        logedit_pattern_line_trap_8_relative_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_8_relative_thickness"));

        gridLayout_pattern_line_8->addWidget(logedit_pattern_line_trap_8_relative_thickness, 3, 2, 1, 1);

        label_pattern_line_8_int = new QLabel(groupCheck_pattern_line_trap_8_enabled);
        label_pattern_line_8_int->setObjectName(QString::fromUtf8("label_pattern_line_8_int"));

        gridLayout_pattern_line_8->addWidget(label_pattern_line_8_int, 4, 0, 1, 1);

        logedit_pattern_line_trap_8_intensity = new MyLineEdit(groupCheck_pattern_line_trap_8_enabled);
        logedit_pattern_line_trap_8_intensity->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_8_intensity"));

        gridLayout_pattern_line_8->addWidget(logedit_pattern_line_trap_8_intensity, 4, 1, 1, 1);

        colorButton_pattern_line_trap_8_color = new MyColorButton(groupCheck_pattern_line_trap_8_enabled);
        colorButton_pattern_line_trap_8_color->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_8_color"));

        gridLayout_pattern_line_8->addWidget(colorButton_pattern_line_trap_8_color, 4, 2, 1, 1);

        colorButton_pattern_line_trap_8_color_2 = new MyColorButton(groupCheck_pattern_line_trap_8_enabled);
        colorButton_pattern_line_trap_8_color_2->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_8_color_2"));

        gridLayout_pattern_line_8->addWidget(colorButton_pattern_line_trap_8_color_2, 4, 3, 1, 1);

        colorButton_pattern_line_trap_8_color_3 = new MyColorButton(groupCheck_pattern_line_trap_8_enabled);
        colorButton_pattern_line_trap_8_color_3->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_8_color_3"));

        gridLayout_pattern_line_8->addWidget(colorButton_pattern_line_trap_8_color_3, 4, 4, 1, 1);

        label_pattern_line_8_shape = new QLabel(groupCheck_pattern_line_trap_8_enabled);
        label_pattern_line_8_shape->setObjectName(QString::fromUtf8("label_pattern_line_8_shape"));

        gridLayout_pattern_line_8->addWidget(label_pattern_line_8_shape, 5, 0, 1, 1);

        comboBox_pattern_line_trap_8_shape = new MyComboBox(groupCheck_pattern_line_trap_8_enabled);
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->addItem(QString());
        comboBox_pattern_line_trap_8_shape->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_8_shape"));

        gridLayout_pattern_line_8->addWidget(comboBox_pattern_line_trap_8_shape, 5, 1, 1, 4);

        label_pattern_line_8_shape_aux = new QLabel(groupCheck_pattern_line_trap_8_enabled);
        label_pattern_line_8_shape_aux->setObjectName(QString::fromUtf8("label_pattern_line_8_shape_aux"));

        gridLayout_pattern_line_8->addWidget(label_pattern_line_8_shape_aux, 6, 0, 1, 1);

        logedit_pattern_line_trap_8_shape_aux = new MyLineEdit(groupCheck_pattern_line_trap_8_enabled);
        logedit_pattern_line_trap_8_shape_aux->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_8_shape_aux"));

        gridLayout_pattern_line_8->addWidget(logedit_pattern_line_trap_8_shape_aux, 6, 1, 1, 2);

        label_pattern_line_8_sharp_seg = new QLabel(groupCheck_pattern_line_trap_8_enabled);
        label_pattern_line_8_sharp_seg->setObjectName(QString::fromUtf8("label_pattern_line_8_sharp_seg"));

        gridLayout_pattern_line_8->addWidget(label_pattern_line_8_sharp_seg, 7, 0, 1, 1);

        logedit_pattern_line_trap_8_falloff_sharpness = new MyLineEdit(groupCheck_pattern_line_trap_8_enabled);
        logedit_pattern_line_trap_8_falloff_sharpness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_8_falloff_sharpness"));

        gridLayout_pattern_line_8->addWidget(logedit_pattern_line_trap_8_falloff_sharpness, 7, 1, 1, 1);

        logedit_pattern_line_trap_8_segment_half_length = new MyLineEdit(groupCheck_pattern_line_trap_8_enabled);
        logedit_pattern_line_trap_8_segment_half_length->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_8_segment_half_length"));

        gridLayout_pattern_line_8->addWidget(logedit_pattern_line_trap_8_segment_half_length, 7, 2, 1, 1);

        label_pattern_line_8_glow = new QLabel(groupCheck_pattern_line_trap_8_enabled);
        label_pattern_line_8_glow->setObjectName(QString::fromUtf8("label_pattern_line_8_glow"));

        gridLayout_pattern_line_8->addWidget(label_pattern_line_8_glow, 8, 0, 1, 1);

        logedit_pattern_line_trap_8_glow_spread = new MyLineEdit(groupCheck_pattern_line_trap_8_enabled);
        logedit_pattern_line_trap_8_glow_spread->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_8_glow_spread"));

        gridLayout_pattern_line_8->addWidget(logedit_pattern_line_trap_8_glow_spread, 8, 1, 1, 1);

        comboBox_pattern_line_trap_8_falloff_profile = new MyComboBox(groupCheck_pattern_line_trap_8_enabled);
        comboBox_pattern_line_trap_8_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_8_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_8_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_8_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_8_falloff_profile->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_8_falloff_profile"));

        gridLayout_pattern_line_8->addWidget(comboBox_pattern_line_trap_8_falloff_profile, 8, 2, 1, 3);

        label_pattern_line_8_side = new QLabel(groupCheck_pattern_line_trap_8_enabled);
        label_pattern_line_8_side->setObjectName(QString::fromUtf8("label_pattern_line_8_side"));

        gridLayout_pattern_line_8->addWidget(label_pattern_line_8_side, 9, 0, 1, 1);

        comboBox_pattern_line_trap_8_edge_side = new MyComboBox(groupCheck_pattern_line_trap_8_enabled);
        comboBox_pattern_line_trap_8_edge_side->addItem(QString());
        comboBox_pattern_line_trap_8_edge_side->addItem(QString());
        comboBox_pattern_line_trap_8_edge_side->addItem(QString());
        comboBox_pattern_line_trap_8_edge_side->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_8_edge_side"));

        gridLayout_pattern_line_8->addWidget(comboBox_pattern_line_trap_8_edge_side, 9, 1, 1, 4);

        pushButton_pattern_line_trap_8_place_surface = new QPushButton(groupCheck_pattern_line_trap_8_enabled);
        pushButton_pattern_line_trap_8_place_surface->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_8_place_surface"));

        gridLayout_pattern_line_8->addWidget(pushButton_pattern_line_trap_8_place_surface, 10, 0, 1, 5);

        pushButton_pattern_line_trap_8_place_target = new QPushButton(groupCheck_pattern_line_trap_8_enabled);
        pushButton_pattern_line_trap_8_place_target->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_8_place_target"));

        gridLayout_pattern_line_8->addWidget(pushButton_pattern_line_trap_8_place_target, 11, 0, 1, 5);


        verticalLayout_pattern_line_traps_outer->addWidget(groupCheck_pattern_line_trap_8_enabled);

        groupCheck_pattern_line_trap_9_enabled = new MyGroupBox(groupBox_pattern_line_traps);
        groupCheck_pattern_line_trap_9_enabled->setObjectName(QString::fromUtf8("groupCheck_pattern_line_trap_9_enabled"));
        groupCheck_pattern_line_trap_9_enabled->setCheckable(true);
        gridLayout_pattern_line_9 = new QGridLayout(groupCheck_pattern_line_trap_9_enabled);
        gridLayout_pattern_line_9->setSpacing(2);
        gridLayout_pattern_line_9->setObjectName(QString::fromUtf8("gridLayout_pattern_line_9"));
        label_pattern_line_9_pos = new QLabel(groupCheck_pattern_line_trap_9_enabled);
        label_pattern_line_9_pos->setObjectName(QString::fromUtf8("label_pattern_line_9_pos"));

        gridLayout_pattern_line_9->addWidget(label_pattern_line_9_pos, 0, 0, 1, 1);

        vect3_pattern_line_trap_9_position_x = new MyLineEdit(groupCheck_pattern_line_trap_9_enabled);
        vect3_pattern_line_trap_9_position_x->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_9_position_x"));

        gridLayout_pattern_line_9->addWidget(vect3_pattern_line_trap_9_position_x, 0, 1, 1, 1);

        vect3_pattern_line_trap_9_position_y = new MyLineEdit(groupCheck_pattern_line_trap_9_enabled);
        vect3_pattern_line_trap_9_position_y->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_9_position_y"));

        gridLayout_pattern_line_9->addWidget(vect3_pattern_line_trap_9_position_y, 0, 2, 1, 1);

        vect3_pattern_line_trap_9_position_z = new MyLineEdit(groupCheck_pattern_line_trap_9_enabled);
        vect3_pattern_line_trap_9_position_z->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_9_position_z"));

        gridLayout_pattern_line_9->addWidget(vect3_pattern_line_trap_9_position_z, 0, 3, 1, 1);

        label_pattern_line_9_rot = new QLabel(groupCheck_pattern_line_trap_9_enabled);
        label_pattern_line_9_rot->setObjectName(QString::fromUtf8("label_pattern_line_9_rot"));

        gridLayout_pattern_line_9->addWidget(label_pattern_line_9_rot, 1, 0, 1, 1);

        spinboxd3_pattern_line_trap_9_rotation_x = new MyDoubleSpinBox(groupCheck_pattern_line_trap_9_enabled);
        spinboxd3_pattern_line_trap_9_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_9_rotation_x"));

        gridLayout_pattern_line_9->addWidget(spinboxd3_pattern_line_trap_9_rotation_x, 1, 1, 1, 1);

        spinboxd3_pattern_line_trap_9_rotation_y = new MyDoubleSpinBox(groupCheck_pattern_line_trap_9_enabled);
        spinboxd3_pattern_line_trap_9_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_9_rotation_y"));

        gridLayout_pattern_line_9->addWidget(spinboxd3_pattern_line_trap_9_rotation_y, 1, 2, 1, 1);

        spinboxd3_pattern_line_trap_9_rotation_z = new MyDoubleSpinBox(groupCheck_pattern_line_trap_9_enabled);
        spinboxd3_pattern_line_trap_9_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_9_rotation_z"));

        gridLayout_pattern_line_9->addWidget(spinboxd3_pattern_line_trap_9_rotation_z, 1, 3, 1, 1);

        label_pattern_line_9_radius = new QLabel(groupCheck_pattern_line_trap_9_enabled);
        label_pattern_line_9_radius->setObjectName(QString::fromUtf8("label_pattern_line_9_radius"));

        gridLayout_pattern_line_9->addWidget(label_pattern_line_9_radius, 2, 0, 1, 1);

        logedit_pattern_line_trap_9_radius = new MyLineEdit(groupCheck_pattern_line_trap_9_enabled);
        logedit_pattern_line_trap_9_radius->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_9_radius"));

        gridLayout_pattern_line_9->addWidget(logedit_pattern_line_trap_9_radius, 2, 1, 1, 1);

        logedit_pattern_line_trap_9_thickness = new MyLineEdit(groupCheck_pattern_line_trap_9_enabled);
        logedit_pattern_line_trap_9_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_9_thickness"));

        gridLayout_pattern_line_9->addWidget(logedit_pattern_line_trap_9_thickness, 2, 2, 1, 1);

        logedit_pattern_line_trap_9_edge_softness = new MyLineEdit(groupCheck_pattern_line_trap_9_enabled);
        logedit_pattern_line_trap_9_edge_softness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_9_edge_softness"));

        gridLayout_pattern_line_9->addWidget(logedit_pattern_line_trap_9_edge_softness, 2, 3, 1, 1);

        logedit_pattern_line_trap_9_max_distance = new MyLineEdit(groupCheck_pattern_line_trap_9_enabled);
        logedit_pattern_line_trap_9_max_distance->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_9_max_distance"));

        gridLayout_pattern_line_9->addWidget(logedit_pattern_line_trap_9_max_distance, 2, 4, 1, 1);

        label_pattern_line_9_scale = new QLabel(groupCheck_pattern_line_trap_9_enabled);
        label_pattern_line_9_scale->setObjectName(QString::fromUtf8("label_pattern_line_9_scale"));

        gridLayout_pattern_line_9->addWidget(label_pattern_line_9_scale, 3, 0, 1, 1);

        logedit_pattern_line_trap_9_scale = new MyLineEdit(groupCheck_pattern_line_trap_9_enabled);
        logedit_pattern_line_trap_9_scale->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_9_scale"));

        gridLayout_pattern_line_9->addWidget(logedit_pattern_line_trap_9_scale, 3, 1, 1, 1);

        logedit_pattern_line_trap_9_relative_thickness = new MyLineEdit(groupCheck_pattern_line_trap_9_enabled);
        logedit_pattern_line_trap_9_relative_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_9_relative_thickness"));

        gridLayout_pattern_line_9->addWidget(logedit_pattern_line_trap_9_relative_thickness, 3, 2, 1, 1);

        label_pattern_line_9_int = new QLabel(groupCheck_pattern_line_trap_9_enabled);
        label_pattern_line_9_int->setObjectName(QString::fromUtf8("label_pattern_line_9_int"));

        gridLayout_pattern_line_9->addWidget(label_pattern_line_9_int, 4, 0, 1, 1);

        logedit_pattern_line_trap_9_intensity = new MyLineEdit(groupCheck_pattern_line_trap_9_enabled);
        logedit_pattern_line_trap_9_intensity->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_9_intensity"));

        gridLayout_pattern_line_9->addWidget(logedit_pattern_line_trap_9_intensity, 4, 1, 1, 1);

        colorButton_pattern_line_trap_9_color = new MyColorButton(groupCheck_pattern_line_trap_9_enabled);
        colorButton_pattern_line_trap_9_color->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_9_color"));

        gridLayout_pattern_line_9->addWidget(colorButton_pattern_line_trap_9_color, 4, 2, 1, 1);

        colorButton_pattern_line_trap_9_color_2 = new MyColorButton(groupCheck_pattern_line_trap_9_enabled);
        colorButton_pattern_line_trap_9_color_2->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_9_color_2"));

        gridLayout_pattern_line_9->addWidget(colorButton_pattern_line_trap_9_color_2, 4, 3, 1, 1);

        colorButton_pattern_line_trap_9_color_3 = new MyColorButton(groupCheck_pattern_line_trap_9_enabled);
        colorButton_pattern_line_trap_9_color_3->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_9_color_3"));

        gridLayout_pattern_line_9->addWidget(colorButton_pattern_line_trap_9_color_3, 4, 4, 1, 1);

        label_pattern_line_9_shape = new QLabel(groupCheck_pattern_line_trap_9_enabled);
        label_pattern_line_9_shape->setObjectName(QString::fromUtf8("label_pattern_line_9_shape"));

        gridLayout_pattern_line_9->addWidget(label_pattern_line_9_shape, 5, 0, 1, 1);

        comboBox_pattern_line_trap_9_shape = new MyComboBox(groupCheck_pattern_line_trap_9_enabled);
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->addItem(QString());
        comboBox_pattern_line_trap_9_shape->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_9_shape"));

        gridLayout_pattern_line_9->addWidget(comboBox_pattern_line_trap_9_shape, 5, 1, 1, 4);

        label_pattern_line_9_shape_aux = new QLabel(groupCheck_pattern_line_trap_9_enabled);
        label_pattern_line_9_shape_aux->setObjectName(QString::fromUtf8("label_pattern_line_9_shape_aux"));

        gridLayout_pattern_line_9->addWidget(label_pattern_line_9_shape_aux, 6, 0, 1, 1);

        logedit_pattern_line_trap_9_shape_aux = new MyLineEdit(groupCheck_pattern_line_trap_9_enabled);
        logedit_pattern_line_trap_9_shape_aux->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_9_shape_aux"));

        gridLayout_pattern_line_9->addWidget(logedit_pattern_line_trap_9_shape_aux, 6, 1, 1, 2);

        label_pattern_line_9_sharp_seg = new QLabel(groupCheck_pattern_line_trap_9_enabled);
        label_pattern_line_9_sharp_seg->setObjectName(QString::fromUtf8("label_pattern_line_9_sharp_seg"));

        gridLayout_pattern_line_9->addWidget(label_pattern_line_9_sharp_seg, 7, 0, 1, 1);

        logedit_pattern_line_trap_9_falloff_sharpness = new MyLineEdit(groupCheck_pattern_line_trap_9_enabled);
        logedit_pattern_line_trap_9_falloff_sharpness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_9_falloff_sharpness"));

        gridLayout_pattern_line_9->addWidget(logedit_pattern_line_trap_9_falloff_sharpness, 7, 1, 1, 1);

        logedit_pattern_line_trap_9_segment_half_length = new MyLineEdit(groupCheck_pattern_line_trap_9_enabled);
        logedit_pattern_line_trap_9_segment_half_length->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_9_segment_half_length"));

        gridLayout_pattern_line_9->addWidget(logedit_pattern_line_trap_9_segment_half_length, 7, 2, 1, 1);

        label_pattern_line_9_glow = new QLabel(groupCheck_pattern_line_trap_9_enabled);
        label_pattern_line_9_glow->setObjectName(QString::fromUtf8("label_pattern_line_9_glow"));

        gridLayout_pattern_line_9->addWidget(label_pattern_line_9_glow, 8, 0, 1, 1);

        logedit_pattern_line_trap_9_glow_spread = new MyLineEdit(groupCheck_pattern_line_trap_9_enabled);
        logedit_pattern_line_trap_9_glow_spread->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_9_glow_spread"));

        gridLayout_pattern_line_9->addWidget(logedit_pattern_line_trap_9_glow_spread, 8, 1, 1, 1);

        comboBox_pattern_line_trap_9_falloff_profile = new MyComboBox(groupCheck_pattern_line_trap_9_enabled);
        comboBox_pattern_line_trap_9_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_9_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_9_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_9_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_9_falloff_profile->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_9_falloff_profile"));

        gridLayout_pattern_line_9->addWidget(comboBox_pattern_line_trap_9_falloff_profile, 8, 2, 1, 3);

        label_pattern_line_9_side = new QLabel(groupCheck_pattern_line_trap_9_enabled);
        label_pattern_line_9_side->setObjectName(QString::fromUtf8("label_pattern_line_9_side"));

        gridLayout_pattern_line_9->addWidget(label_pattern_line_9_side, 9, 0, 1, 1);

        comboBox_pattern_line_trap_9_edge_side = new MyComboBox(groupCheck_pattern_line_trap_9_enabled);
        comboBox_pattern_line_trap_9_edge_side->addItem(QString());
        comboBox_pattern_line_trap_9_edge_side->addItem(QString());
        comboBox_pattern_line_trap_9_edge_side->addItem(QString());
        comboBox_pattern_line_trap_9_edge_side->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_9_edge_side"));

        gridLayout_pattern_line_9->addWidget(comboBox_pattern_line_trap_9_edge_side, 9, 1, 1, 4);

        pushButton_pattern_line_trap_9_place_surface = new QPushButton(groupCheck_pattern_line_trap_9_enabled);
        pushButton_pattern_line_trap_9_place_surface->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_9_place_surface"));

        gridLayout_pattern_line_9->addWidget(pushButton_pattern_line_trap_9_place_surface, 10, 0, 1, 5);

        pushButton_pattern_line_trap_9_place_target = new QPushButton(groupCheck_pattern_line_trap_9_enabled);
        pushButton_pattern_line_trap_9_place_target->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_9_place_target"));

        gridLayout_pattern_line_9->addWidget(pushButton_pattern_line_trap_9_place_target, 11, 0, 1, 5);


        verticalLayout_pattern_line_traps_outer->addWidget(groupCheck_pattern_line_trap_9_enabled);

        groupCheck_pattern_line_trap_10_enabled = new MyGroupBox(groupBox_pattern_line_traps);
        groupCheck_pattern_line_trap_10_enabled->setObjectName(QString::fromUtf8("groupCheck_pattern_line_trap_10_enabled"));
        groupCheck_pattern_line_trap_10_enabled->setCheckable(true);
        gridLayout_pattern_line_10 = new QGridLayout(groupCheck_pattern_line_trap_10_enabled);
        gridLayout_pattern_line_10->setSpacing(2);
        gridLayout_pattern_line_10->setObjectName(QString::fromUtf8("gridLayout_pattern_line_10"));
        label_pattern_line_10_pos = new QLabel(groupCheck_pattern_line_trap_10_enabled);
        label_pattern_line_10_pos->setObjectName(QString::fromUtf8("label_pattern_line_10_pos"));

        gridLayout_pattern_line_10->addWidget(label_pattern_line_10_pos, 0, 0, 1, 1);

        vect3_pattern_line_trap_10_position_x = new MyLineEdit(groupCheck_pattern_line_trap_10_enabled);
        vect3_pattern_line_trap_10_position_x->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_10_position_x"));

        gridLayout_pattern_line_10->addWidget(vect3_pattern_line_trap_10_position_x, 0, 1, 1, 1);

        vect3_pattern_line_trap_10_position_y = new MyLineEdit(groupCheck_pattern_line_trap_10_enabled);
        vect3_pattern_line_trap_10_position_y->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_10_position_y"));

        gridLayout_pattern_line_10->addWidget(vect3_pattern_line_trap_10_position_y, 0, 2, 1, 1);

        vect3_pattern_line_trap_10_position_z = new MyLineEdit(groupCheck_pattern_line_trap_10_enabled);
        vect3_pattern_line_trap_10_position_z->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_10_position_z"));

        gridLayout_pattern_line_10->addWidget(vect3_pattern_line_trap_10_position_z, 0, 3, 1, 1);

        label_pattern_line_10_rot = new QLabel(groupCheck_pattern_line_trap_10_enabled);
        label_pattern_line_10_rot->setObjectName(QString::fromUtf8("label_pattern_line_10_rot"));

        gridLayout_pattern_line_10->addWidget(label_pattern_line_10_rot, 1, 0, 1, 1);

        spinboxd3_pattern_line_trap_10_rotation_x = new MyDoubleSpinBox(groupCheck_pattern_line_trap_10_enabled);
        spinboxd3_pattern_line_trap_10_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_10_rotation_x"));

        gridLayout_pattern_line_10->addWidget(spinboxd3_pattern_line_trap_10_rotation_x, 1, 1, 1, 1);

        spinboxd3_pattern_line_trap_10_rotation_y = new MyDoubleSpinBox(groupCheck_pattern_line_trap_10_enabled);
        spinboxd3_pattern_line_trap_10_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_10_rotation_y"));

        gridLayout_pattern_line_10->addWidget(spinboxd3_pattern_line_trap_10_rotation_y, 1, 2, 1, 1);

        spinboxd3_pattern_line_trap_10_rotation_z = new MyDoubleSpinBox(groupCheck_pattern_line_trap_10_enabled);
        spinboxd3_pattern_line_trap_10_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_10_rotation_z"));

        gridLayout_pattern_line_10->addWidget(spinboxd3_pattern_line_trap_10_rotation_z, 1, 3, 1, 1);

        label_pattern_line_10_radius = new QLabel(groupCheck_pattern_line_trap_10_enabled);
        label_pattern_line_10_radius->setObjectName(QString::fromUtf8("label_pattern_line_10_radius"));

        gridLayout_pattern_line_10->addWidget(label_pattern_line_10_radius, 2, 0, 1, 1);

        logedit_pattern_line_trap_10_radius = new MyLineEdit(groupCheck_pattern_line_trap_10_enabled);
        logedit_pattern_line_trap_10_radius->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_10_radius"));

        gridLayout_pattern_line_10->addWidget(logedit_pattern_line_trap_10_radius, 2, 1, 1, 1);

        logedit_pattern_line_trap_10_thickness = new MyLineEdit(groupCheck_pattern_line_trap_10_enabled);
        logedit_pattern_line_trap_10_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_10_thickness"));

        gridLayout_pattern_line_10->addWidget(logedit_pattern_line_trap_10_thickness, 2, 2, 1, 1);

        logedit_pattern_line_trap_10_edge_softness = new MyLineEdit(groupCheck_pattern_line_trap_10_enabled);
        logedit_pattern_line_trap_10_edge_softness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_10_edge_softness"));

        gridLayout_pattern_line_10->addWidget(logedit_pattern_line_trap_10_edge_softness, 2, 3, 1, 1);

        logedit_pattern_line_trap_10_max_distance = new MyLineEdit(groupCheck_pattern_line_trap_10_enabled);
        logedit_pattern_line_trap_10_max_distance->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_10_max_distance"));

        gridLayout_pattern_line_10->addWidget(logedit_pattern_line_trap_10_max_distance, 2, 4, 1, 1);

        label_pattern_line_10_scale = new QLabel(groupCheck_pattern_line_trap_10_enabled);
        label_pattern_line_10_scale->setObjectName(QString::fromUtf8("label_pattern_line_10_scale"));

        gridLayout_pattern_line_10->addWidget(label_pattern_line_10_scale, 3, 0, 1, 1);

        logedit_pattern_line_trap_10_scale = new MyLineEdit(groupCheck_pattern_line_trap_10_enabled);
        logedit_pattern_line_trap_10_scale->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_10_scale"));

        gridLayout_pattern_line_10->addWidget(logedit_pattern_line_trap_10_scale, 3, 1, 1, 1);

        logedit_pattern_line_trap_10_relative_thickness = new MyLineEdit(groupCheck_pattern_line_trap_10_enabled);
        logedit_pattern_line_trap_10_relative_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_10_relative_thickness"));

        gridLayout_pattern_line_10->addWidget(logedit_pattern_line_trap_10_relative_thickness, 3, 2, 1, 1);

        label_pattern_line_10_int = new QLabel(groupCheck_pattern_line_trap_10_enabled);
        label_pattern_line_10_int->setObjectName(QString::fromUtf8("label_pattern_line_10_int"));

        gridLayout_pattern_line_10->addWidget(label_pattern_line_10_int, 4, 0, 1, 1);

        logedit_pattern_line_trap_10_intensity = new MyLineEdit(groupCheck_pattern_line_trap_10_enabled);
        logedit_pattern_line_trap_10_intensity->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_10_intensity"));

        gridLayout_pattern_line_10->addWidget(logedit_pattern_line_trap_10_intensity, 4, 1, 1, 1);

        colorButton_pattern_line_trap_10_color = new MyColorButton(groupCheck_pattern_line_trap_10_enabled);
        colorButton_pattern_line_trap_10_color->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_10_color"));

        gridLayout_pattern_line_10->addWidget(colorButton_pattern_line_trap_10_color, 4, 2, 1, 1);

        colorButton_pattern_line_trap_10_color_2 = new MyColorButton(groupCheck_pattern_line_trap_10_enabled);
        colorButton_pattern_line_trap_10_color_2->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_10_color_2"));

        gridLayout_pattern_line_10->addWidget(colorButton_pattern_line_trap_10_color_2, 4, 3, 1, 1);

        colorButton_pattern_line_trap_10_color_3 = new MyColorButton(groupCheck_pattern_line_trap_10_enabled);
        colorButton_pattern_line_trap_10_color_3->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_10_color_3"));

        gridLayout_pattern_line_10->addWidget(colorButton_pattern_line_trap_10_color_3, 4, 4, 1, 1);

        label_pattern_line_10_shape = new QLabel(groupCheck_pattern_line_trap_10_enabled);
        label_pattern_line_10_shape->setObjectName(QString::fromUtf8("label_pattern_line_10_shape"));

        gridLayout_pattern_line_10->addWidget(label_pattern_line_10_shape, 5, 0, 1, 1);

        comboBox_pattern_line_trap_10_shape = new MyComboBox(groupCheck_pattern_line_trap_10_enabled);
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->addItem(QString());
        comboBox_pattern_line_trap_10_shape->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_10_shape"));

        gridLayout_pattern_line_10->addWidget(comboBox_pattern_line_trap_10_shape, 5, 1, 1, 4);

        label_pattern_line_10_shape_aux = new QLabel(groupCheck_pattern_line_trap_10_enabled);
        label_pattern_line_10_shape_aux->setObjectName(QString::fromUtf8("label_pattern_line_10_shape_aux"));

        gridLayout_pattern_line_10->addWidget(label_pattern_line_10_shape_aux, 6, 0, 1, 1);

        logedit_pattern_line_trap_10_shape_aux = new MyLineEdit(groupCheck_pattern_line_trap_10_enabled);
        logedit_pattern_line_trap_10_shape_aux->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_10_shape_aux"));

        gridLayout_pattern_line_10->addWidget(logedit_pattern_line_trap_10_shape_aux, 6, 1, 1, 2);

        label_pattern_line_10_sharp_seg = new QLabel(groupCheck_pattern_line_trap_10_enabled);
        label_pattern_line_10_sharp_seg->setObjectName(QString::fromUtf8("label_pattern_line_10_sharp_seg"));

        gridLayout_pattern_line_10->addWidget(label_pattern_line_10_sharp_seg, 7, 0, 1, 1);

        logedit_pattern_line_trap_10_falloff_sharpness = new MyLineEdit(groupCheck_pattern_line_trap_10_enabled);
        logedit_pattern_line_trap_10_falloff_sharpness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_10_falloff_sharpness"));

        gridLayout_pattern_line_10->addWidget(logedit_pattern_line_trap_10_falloff_sharpness, 7, 1, 1, 1);

        logedit_pattern_line_trap_10_segment_half_length = new MyLineEdit(groupCheck_pattern_line_trap_10_enabled);
        logedit_pattern_line_trap_10_segment_half_length->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_10_segment_half_length"));

        gridLayout_pattern_line_10->addWidget(logedit_pattern_line_trap_10_segment_half_length, 7, 2, 1, 1);

        label_pattern_line_10_glow = new QLabel(groupCheck_pattern_line_trap_10_enabled);
        label_pattern_line_10_glow->setObjectName(QString::fromUtf8("label_pattern_line_10_glow"));

        gridLayout_pattern_line_10->addWidget(label_pattern_line_10_glow, 8, 0, 1, 1);

        logedit_pattern_line_trap_10_glow_spread = new MyLineEdit(groupCheck_pattern_line_trap_10_enabled);
        logedit_pattern_line_trap_10_glow_spread->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_10_glow_spread"));

        gridLayout_pattern_line_10->addWidget(logedit_pattern_line_trap_10_glow_spread, 8, 1, 1, 1);

        comboBox_pattern_line_trap_10_falloff_profile = new MyComboBox(groupCheck_pattern_line_trap_10_enabled);
        comboBox_pattern_line_trap_10_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_10_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_10_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_10_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_10_falloff_profile->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_10_falloff_profile"));

        gridLayout_pattern_line_10->addWidget(comboBox_pattern_line_trap_10_falloff_profile, 8, 2, 1, 3);

        label_pattern_line_10_side = new QLabel(groupCheck_pattern_line_trap_10_enabled);
        label_pattern_line_10_side->setObjectName(QString::fromUtf8("label_pattern_line_10_side"));

        gridLayout_pattern_line_10->addWidget(label_pattern_line_10_side, 9, 0, 1, 1);

        comboBox_pattern_line_trap_10_edge_side = new MyComboBox(groupCheck_pattern_line_trap_10_enabled);
        comboBox_pattern_line_trap_10_edge_side->addItem(QString());
        comboBox_pattern_line_trap_10_edge_side->addItem(QString());
        comboBox_pattern_line_trap_10_edge_side->addItem(QString());
        comboBox_pattern_line_trap_10_edge_side->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_10_edge_side"));

        gridLayout_pattern_line_10->addWidget(comboBox_pattern_line_trap_10_edge_side, 9, 1, 1, 4);

        pushButton_pattern_line_trap_10_place_surface = new QPushButton(groupCheck_pattern_line_trap_10_enabled);
        pushButton_pattern_line_trap_10_place_surface->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_10_place_surface"));

        gridLayout_pattern_line_10->addWidget(pushButton_pattern_line_trap_10_place_surface, 10, 0, 1, 5);

        pushButton_pattern_line_trap_10_place_target = new QPushButton(groupCheck_pattern_line_trap_10_enabled);
        pushButton_pattern_line_trap_10_place_target->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_10_place_target"));

        gridLayout_pattern_line_10->addWidget(pushButton_pattern_line_trap_10_place_target, 11, 0, 1, 5);


        verticalLayout_pattern_line_traps_outer->addWidget(groupCheck_pattern_line_trap_10_enabled);

        groupCheck_pattern_line_trap_11_enabled = new MyGroupBox(groupBox_pattern_line_traps);
        groupCheck_pattern_line_trap_11_enabled->setObjectName(QString::fromUtf8("groupCheck_pattern_line_trap_11_enabled"));
        groupCheck_pattern_line_trap_11_enabled->setCheckable(true);
        gridLayout_pattern_line_11 = new QGridLayout(groupCheck_pattern_line_trap_11_enabled);
        gridLayout_pattern_line_11->setSpacing(2);
        gridLayout_pattern_line_11->setObjectName(QString::fromUtf8("gridLayout_pattern_line_11"));
        label_pattern_line_11_pos = new QLabel(groupCheck_pattern_line_trap_11_enabled);
        label_pattern_line_11_pos->setObjectName(QString::fromUtf8("label_pattern_line_11_pos"));

        gridLayout_pattern_line_11->addWidget(label_pattern_line_11_pos, 0, 0, 1, 1);

        vect3_pattern_line_trap_11_position_x = new MyLineEdit(groupCheck_pattern_line_trap_11_enabled);
        vect3_pattern_line_trap_11_position_x->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_11_position_x"));

        gridLayout_pattern_line_11->addWidget(vect3_pattern_line_trap_11_position_x, 0, 1, 1, 1);

        vect3_pattern_line_trap_11_position_y = new MyLineEdit(groupCheck_pattern_line_trap_11_enabled);
        vect3_pattern_line_trap_11_position_y->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_11_position_y"));

        gridLayout_pattern_line_11->addWidget(vect3_pattern_line_trap_11_position_y, 0, 2, 1, 1);

        vect3_pattern_line_trap_11_position_z = new MyLineEdit(groupCheck_pattern_line_trap_11_enabled);
        vect3_pattern_line_trap_11_position_z->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_11_position_z"));

        gridLayout_pattern_line_11->addWidget(vect3_pattern_line_trap_11_position_z, 0, 3, 1, 1);

        label_pattern_line_11_rot = new QLabel(groupCheck_pattern_line_trap_11_enabled);
        label_pattern_line_11_rot->setObjectName(QString::fromUtf8("label_pattern_line_11_rot"));

        gridLayout_pattern_line_11->addWidget(label_pattern_line_11_rot, 1, 0, 1, 1);

        spinboxd3_pattern_line_trap_11_rotation_x = new MyDoubleSpinBox(groupCheck_pattern_line_trap_11_enabled);
        spinboxd3_pattern_line_trap_11_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_11_rotation_x"));

        gridLayout_pattern_line_11->addWidget(spinboxd3_pattern_line_trap_11_rotation_x, 1, 1, 1, 1);

        spinboxd3_pattern_line_trap_11_rotation_y = new MyDoubleSpinBox(groupCheck_pattern_line_trap_11_enabled);
        spinboxd3_pattern_line_trap_11_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_11_rotation_y"));

        gridLayout_pattern_line_11->addWidget(spinboxd3_pattern_line_trap_11_rotation_y, 1, 2, 1, 1);

        spinboxd3_pattern_line_trap_11_rotation_z = new MyDoubleSpinBox(groupCheck_pattern_line_trap_11_enabled);
        spinboxd3_pattern_line_trap_11_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_11_rotation_z"));

        gridLayout_pattern_line_11->addWidget(spinboxd3_pattern_line_trap_11_rotation_z, 1, 3, 1, 1);

        label_pattern_line_11_radius = new QLabel(groupCheck_pattern_line_trap_11_enabled);
        label_pattern_line_11_radius->setObjectName(QString::fromUtf8("label_pattern_line_11_radius"));

        gridLayout_pattern_line_11->addWidget(label_pattern_line_11_radius, 2, 0, 1, 1);

        logedit_pattern_line_trap_11_radius = new MyLineEdit(groupCheck_pattern_line_trap_11_enabled);
        logedit_pattern_line_trap_11_radius->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_11_radius"));

        gridLayout_pattern_line_11->addWidget(logedit_pattern_line_trap_11_radius, 2, 1, 1, 1);

        logedit_pattern_line_trap_11_thickness = new MyLineEdit(groupCheck_pattern_line_trap_11_enabled);
        logedit_pattern_line_trap_11_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_11_thickness"));

        gridLayout_pattern_line_11->addWidget(logedit_pattern_line_trap_11_thickness, 2, 2, 1, 1);

        logedit_pattern_line_trap_11_edge_softness = new MyLineEdit(groupCheck_pattern_line_trap_11_enabled);
        logedit_pattern_line_trap_11_edge_softness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_11_edge_softness"));

        gridLayout_pattern_line_11->addWidget(logedit_pattern_line_trap_11_edge_softness, 2, 3, 1, 1);

        logedit_pattern_line_trap_11_max_distance = new MyLineEdit(groupCheck_pattern_line_trap_11_enabled);
        logedit_pattern_line_trap_11_max_distance->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_11_max_distance"));

        gridLayout_pattern_line_11->addWidget(logedit_pattern_line_trap_11_max_distance, 2, 4, 1, 1);

        label_pattern_line_11_scale = new QLabel(groupCheck_pattern_line_trap_11_enabled);
        label_pattern_line_11_scale->setObjectName(QString::fromUtf8("label_pattern_line_11_scale"));

        gridLayout_pattern_line_11->addWidget(label_pattern_line_11_scale, 3, 0, 1, 1);

        logedit_pattern_line_trap_11_scale = new MyLineEdit(groupCheck_pattern_line_trap_11_enabled);
        logedit_pattern_line_trap_11_scale->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_11_scale"));

        gridLayout_pattern_line_11->addWidget(logedit_pattern_line_trap_11_scale, 3, 1, 1, 1);

        logedit_pattern_line_trap_11_relative_thickness = new MyLineEdit(groupCheck_pattern_line_trap_11_enabled);
        logedit_pattern_line_trap_11_relative_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_11_relative_thickness"));

        gridLayout_pattern_line_11->addWidget(logedit_pattern_line_trap_11_relative_thickness, 3, 2, 1, 1);

        label_pattern_line_11_int = new QLabel(groupCheck_pattern_line_trap_11_enabled);
        label_pattern_line_11_int->setObjectName(QString::fromUtf8("label_pattern_line_11_int"));

        gridLayout_pattern_line_11->addWidget(label_pattern_line_11_int, 4, 0, 1, 1);

        logedit_pattern_line_trap_11_intensity = new MyLineEdit(groupCheck_pattern_line_trap_11_enabled);
        logedit_pattern_line_trap_11_intensity->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_11_intensity"));

        gridLayout_pattern_line_11->addWidget(logedit_pattern_line_trap_11_intensity, 4, 1, 1, 1);

        colorButton_pattern_line_trap_11_color = new MyColorButton(groupCheck_pattern_line_trap_11_enabled);
        colorButton_pattern_line_trap_11_color->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_11_color"));

        gridLayout_pattern_line_11->addWidget(colorButton_pattern_line_trap_11_color, 4, 2, 1, 1);

        colorButton_pattern_line_trap_11_color_2 = new MyColorButton(groupCheck_pattern_line_trap_11_enabled);
        colorButton_pattern_line_trap_11_color_2->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_11_color_2"));

        gridLayout_pattern_line_11->addWidget(colorButton_pattern_line_trap_11_color_2, 4, 3, 1, 1);

        colorButton_pattern_line_trap_11_color_3 = new MyColorButton(groupCheck_pattern_line_trap_11_enabled);
        colorButton_pattern_line_trap_11_color_3->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_11_color_3"));

        gridLayout_pattern_line_11->addWidget(colorButton_pattern_line_trap_11_color_3, 4, 4, 1, 1);

        label_pattern_line_11_shape = new QLabel(groupCheck_pattern_line_trap_11_enabled);
        label_pattern_line_11_shape->setObjectName(QString::fromUtf8("label_pattern_line_11_shape"));

        gridLayout_pattern_line_11->addWidget(label_pattern_line_11_shape, 5, 0, 1, 1);

        comboBox_pattern_line_trap_11_shape = new MyComboBox(groupCheck_pattern_line_trap_11_enabled);
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->addItem(QString());
        comboBox_pattern_line_trap_11_shape->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_11_shape"));

        gridLayout_pattern_line_11->addWidget(comboBox_pattern_line_trap_11_shape, 5, 1, 1, 4);

        label_pattern_line_11_shape_aux = new QLabel(groupCheck_pattern_line_trap_11_enabled);
        label_pattern_line_11_shape_aux->setObjectName(QString::fromUtf8("label_pattern_line_11_shape_aux"));

        gridLayout_pattern_line_11->addWidget(label_pattern_line_11_shape_aux, 6, 0, 1, 1);

        logedit_pattern_line_trap_11_shape_aux = new MyLineEdit(groupCheck_pattern_line_trap_11_enabled);
        logedit_pattern_line_trap_11_shape_aux->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_11_shape_aux"));

        gridLayout_pattern_line_11->addWidget(logedit_pattern_line_trap_11_shape_aux, 6, 1, 1, 2);

        label_pattern_line_11_sharp_seg = new QLabel(groupCheck_pattern_line_trap_11_enabled);
        label_pattern_line_11_sharp_seg->setObjectName(QString::fromUtf8("label_pattern_line_11_sharp_seg"));

        gridLayout_pattern_line_11->addWidget(label_pattern_line_11_sharp_seg, 7, 0, 1, 1);

        logedit_pattern_line_trap_11_falloff_sharpness = new MyLineEdit(groupCheck_pattern_line_trap_11_enabled);
        logedit_pattern_line_trap_11_falloff_sharpness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_11_falloff_sharpness"));

        gridLayout_pattern_line_11->addWidget(logedit_pattern_line_trap_11_falloff_sharpness, 7, 1, 1, 1);

        logedit_pattern_line_trap_11_segment_half_length = new MyLineEdit(groupCheck_pattern_line_trap_11_enabled);
        logedit_pattern_line_trap_11_segment_half_length->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_11_segment_half_length"));

        gridLayout_pattern_line_11->addWidget(logedit_pattern_line_trap_11_segment_half_length, 7, 2, 1, 1);

        label_pattern_line_11_glow = new QLabel(groupCheck_pattern_line_trap_11_enabled);
        label_pattern_line_11_glow->setObjectName(QString::fromUtf8("label_pattern_line_11_glow"));

        gridLayout_pattern_line_11->addWidget(label_pattern_line_11_glow, 8, 0, 1, 1);

        logedit_pattern_line_trap_11_glow_spread = new MyLineEdit(groupCheck_pattern_line_trap_11_enabled);
        logedit_pattern_line_trap_11_glow_spread->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_11_glow_spread"));

        gridLayout_pattern_line_11->addWidget(logedit_pattern_line_trap_11_glow_spread, 8, 1, 1, 1);

        comboBox_pattern_line_trap_11_falloff_profile = new MyComboBox(groupCheck_pattern_line_trap_11_enabled);
        comboBox_pattern_line_trap_11_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_11_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_11_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_11_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_11_falloff_profile->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_11_falloff_profile"));

        gridLayout_pattern_line_11->addWidget(comboBox_pattern_line_trap_11_falloff_profile, 8, 2, 1, 3);

        label_pattern_line_11_side = new QLabel(groupCheck_pattern_line_trap_11_enabled);
        label_pattern_line_11_side->setObjectName(QString::fromUtf8("label_pattern_line_11_side"));

        gridLayout_pattern_line_11->addWidget(label_pattern_line_11_side, 9, 0, 1, 1);

        comboBox_pattern_line_trap_11_edge_side = new MyComboBox(groupCheck_pattern_line_trap_11_enabled);
        comboBox_pattern_line_trap_11_edge_side->addItem(QString());
        comboBox_pattern_line_trap_11_edge_side->addItem(QString());
        comboBox_pattern_line_trap_11_edge_side->addItem(QString());
        comboBox_pattern_line_trap_11_edge_side->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_11_edge_side"));

        gridLayout_pattern_line_11->addWidget(comboBox_pattern_line_trap_11_edge_side, 9, 1, 1, 4);

        pushButton_pattern_line_trap_11_place_surface = new QPushButton(groupCheck_pattern_line_trap_11_enabled);
        pushButton_pattern_line_trap_11_place_surface->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_11_place_surface"));

        gridLayout_pattern_line_11->addWidget(pushButton_pattern_line_trap_11_place_surface, 10, 0, 1, 5);

        pushButton_pattern_line_trap_11_place_target = new QPushButton(groupCheck_pattern_line_trap_11_enabled);
        pushButton_pattern_line_trap_11_place_target->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_11_place_target"));

        gridLayout_pattern_line_11->addWidget(pushButton_pattern_line_trap_11_place_target, 11, 0, 1, 5);


        verticalLayout_pattern_line_traps_outer->addWidget(groupCheck_pattern_line_trap_11_enabled);

        groupCheck_pattern_line_trap_12_enabled = new MyGroupBox(groupBox_pattern_line_traps);
        groupCheck_pattern_line_trap_12_enabled->setObjectName(QString::fromUtf8("groupCheck_pattern_line_trap_12_enabled"));
        groupCheck_pattern_line_trap_12_enabled->setCheckable(true);
        gridLayout_pattern_line_12 = new QGridLayout(groupCheck_pattern_line_trap_12_enabled);
        gridLayout_pattern_line_12->setSpacing(2);
        gridLayout_pattern_line_12->setObjectName(QString::fromUtf8("gridLayout_pattern_line_12"));
        label_pattern_line_12_pos = new QLabel(groupCheck_pattern_line_trap_12_enabled);
        label_pattern_line_12_pos->setObjectName(QString::fromUtf8("label_pattern_line_12_pos"));

        gridLayout_pattern_line_12->addWidget(label_pattern_line_12_pos, 0, 0, 1, 1);

        vect3_pattern_line_trap_12_position_x = new MyLineEdit(groupCheck_pattern_line_trap_12_enabled);
        vect3_pattern_line_trap_12_position_x->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_12_position_x"));

        gridLayout_pattern_line_12->addWidget(vect3_pattern_line_trap_12_position_x, 0, 1, 1, 1);

        vect3_pattern_line_trap_12_position_y = new MyLineEdit(groupCheck_pattern_line_trap_12_enabled);
        vect3_pattern_line_trap_12_position_y->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_12_position_y"));

        gridLayout_pattern_line_12->addWidget(vect3_pattern_line_trap_12_position_y, 0, 2, 1, 1);

        vect3_pattern_line_trap_12_position_z = new MyLineEdit(groupCheck_pattern_line_trap_12_enabled);
        vect3_pattern_line_trap_12_position_z->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_12_position_z"));

        gridLayout_pattern_line_12->addWidget(vect3_pattern_line_trap_12_position_z, 0, 3, 1, 1);

        label_pattern_line_12_rot = new QLabel(groupCheck_pattern_line_trap_12_enabled);
        label_pattern_line_12_rot->setObjectName(QString::fromUtf8("label_pattern_line_12_rot"));

        gridLayout_pattern_line_12->addWidget(label_pattern_line_12_rot, 1, 0, 1, 1);

        spinboxd3_pattern_line_trap_12_rotation_x = new MyDoubleSpinBox(groupCheck_pattern_line_trap_12_enabled);
        spinboxd3_pattern_line_trap_12_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_12_rotation_x"));

        gridLayout_pattern_line_12->addWidget(spinboxd3_pattern_line_trap_12_rotation_x, 1, 1, 1, 1);

        spinboxd3_pattern_line_trap_12_rotation_y = new MyDoubleSpinBox(groupCheck_pattern_line_trap_12_enabled);
        spinboxd3_pattern_line_trap_12_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_12_rotation_y"));

        gridLayout_pattern_line_12->addWidget(spinboxd3_pattern_line_trap_12_rotation_y, 1, 2, 1, 1);

        spinboxd3_pattern_line_trap_12_rotation_z = new MyDoubleSpinBox(groupCheck_pattern_line_trap_12_enabled);
        spinboxd3_pattern_line_trap_12_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_12_rotation_z"));

        gridLayout_pattern_line_12->addWidget(spinboxd3_pattern_line_trap_12_rotation_z, 1, 3, 1, 1);

        label_pattern_line_12_radius = new QLabel(groupCheck_pattern_line_trap_12_enabled);
        label_pattern_line_12_radius->setObjectName(QString::fromUtf8("label_pattern_line_12_radius"));

        gridLayout_pattern_line_12->addWidget(label_pattern_line_12_radius, 2, 0, 1, 1);

        logedit_pattern_line_trap_12_radius = new MyLineEdit(groupCheck_pattern_line_trap_12_enabled);
        logedit_pattern_line_trap_12_radius->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_12_radius"));

        gridLayout_pattern_line_12->addWidget(logedit_pattern_line_trap_12_radius, 2, 1, 1, 1);

        logedit_pattern_line_trap_12_thickness = new MyLineEdit(groupCheck_pattern_line_trap_12_enabled);
        logedit_pattern_line_trap_12_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_12_thickness"));

        gridLayout_pattern_line_12->addWidget(logedit_pattern_line_trap_12_thickness, 2, 2, 1, 1);

        logedit_pattern_line_trap_12_edge_softness = new MyLineEdit(groupCheck_pattern_line_trap_12_enabled);
        logedit_pattern_line_trap_12_edge_softness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_12_edge_softness"));

        gridLayout_pattern_line_12->addWidget(logedit_pattern_line_trap_12_edge_softness, 2, 3, 1, 1);

        logedit_pattern_line_trap_12_max_distance = new MyLineEdit(groupCheck_pattern_line_trap_12_enabled);
        logedit_pattern_line_trap_12_max_distance->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_12_max_distance"));

        gridLayout_pattern_line_12->addWidget(logedit_pattern_line_trap_12_max_distance, 2, 4, 1, 1);

        label_pattern_line_12_scale = new QLabel(groupCheck_pattern_line_trap_12_enabled);
        label_pattern_line_12_scale->setObjectName(QString::fromUtf8("label_pattern_line_12_scale"));

        gridLayout_pattern_line_12->addWidget(label_pattern_line_12_scale, 3, 0, 1, 1);

        logedit_pattern_line_trap_12_scale = new MyLineEdit(groupCheck_pattern_line_trap_12_enabled);
        logedit_pattern_line_trap_12_scale->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_12_scale"));

        gridLayout_pattern_line_12->addWidget(logedit_pattern_line_trap_12_scale, 3, 1, 1, 1);

        logedit_pattern_line_trap_12_relative_thickness = new MyLineEdit(groupCheck_pattern_line_trap_12_enabled);
        logedit_pattern_line_trap_12_relative_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_12_relative_thickness"));

        gridLayout_pattern_line_12->addWidget(logedit_pattern_line_trap_12_relative_thickness, 3, 2, 1, 1);

        label_pattern_line_12_int = new QLabel(groupCheck_pattern_line_trap_12_enabled);
        label_pattern_line_12_int->setObjectName(QString::fromUtf8("label_pattern_line_12_int"));

        gridLayout_pattern_line_12->addWidget(label_pattern_line_12_int, 4, 0, 1, 1);

        logedit_pattern_line_trap_12_intensity = new MyLineEdit(groupCheck_pattern_line_trap_12_enabled);
        logedit_pattern_line_trap_12_intensity->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_12_intensity"));

        gridLayout_pattern_line_12->addWidget(logedit_pattern_line_trap_12_intensity, 4, 1, 1, 1);

        colorButton_pattern_line_trap_12_color = new MyColorButton(groupCheck_pattern_line_trap_12_enabled);
        colorButton_pattern_line_trap_12_color->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_12_color"));

        gridLayout_pattern_line_12->addWidget(colorButton_pattern_line_trap_12_color, 4, 2, 1, 1);

        colorButton_pattern_line_trap_12_color_2 = new MyColorButton(groupCheck_pattern_line_trap_12_enabled);
        colorButton_pattern_line_trap_12_color_2->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_12_color_2"));

        gridLayout_pattern_line_12->addWidget(colorButton_pattern_line_trap_12_color_2, 4, 3, 1, 1);

        colorButton_pattern_line_trap_12_color_3 = new MyColorButton(groupCheck_pattern_line_trap_12_enabled);
        colorButton_pattern_line_trap_12_color_3->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_12_color_3"));

        gridLayout_pattern_line_12->addWidget(colorButton_pattern_line_trap_12_color_3, 4, 4, 1, 1);

        label_pattern_line_12_shape = new QLabel(groupCheck_pattern_line_trap_12_enabled);
        label_pattern_line_12_shape->setObjectName(QString::fromUtf8("label_pattern_line_12_shape"));

        gridLayout_pattern_line_12->addWidget(label_pattern_line_12_shape, 5, 0, 1, 1);

        comboBox_pattern_line_trap_12_shape = new MyComboBox(groupCheck_pattern_line_trap_12_enabled);
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->addItem(QString());
        comboBox_pattern_line_trap_12_shape->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_12_shape"));

        gridLayout_pattern_line_12->addWidget(comboBox_pattern_line_trap_12_shape, 5, 1, 1, 4);

        label_pattern_line_12_shape_aux = new QLabel(groupCheck_pattern_line_trap_12_enabled);
        label_pattern_line_12_shape_aux->setObjectName(QString::fromUtf8("label_pattern_line_12_shape_aux"));

        gridLayout_pattern_line_12->addWidget(label_pattern_line_12_shape_aux, 6, 0, 1, 1);

        logedit_pattern_line_trap_12_shape_aux = new MyLineEdit(groupCheck_pattern_line_trap_12_enabled);
        logedit_pattern_line_trap_12_shape_aux->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_12_shape_aux"));

        gridLayout_pattern_line_12->addWidget(logedit_pattern_line_trap_12_shape_aux, 6, 1, 1, 2);

        label_pattern_line_12_sharp_seg = new QLabel(groupCheck_pattern_line_trap_12_enabled);
        label_pattern_line_12_sharp_seg->setObjectName(QString::fromUtf8("label_pattern_line_12_sharp_seg"));

        gridLayout_pattern_line_12->addWidget(label_pattern_line_12_sharp_seg, 7, 0, 1, 1);

        logedit_pattern_line_trap_12_falloff_sharpness = new MyLineEdit(groupCheck_pattern_line_trap_12_enabled);
        logedit_pattern_line_trap_12_falloff_sharpness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_12_falloff_sharpness"));

        gridLayout_pattern_line_12->addWidget(logedit_pattern_line_trap_12_falloff_sharpness, 7, 1, 1, 1);

        logedit_pattern_line_trap_12_segment_half_length = new MyLineEdit(groupCheck_pattern_line_trap_12_enabled);
        logedit_pattern_line_trap_12_segment_half_length->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_12_segment_half_length"));

        gridLayout_pattern_line_12->addWidget(logedit_pattern_line_trap_12_segment_half_length, 7, 2, 1, 1);

        label_pattern_line_12_glow = new QLabel(groupCheck_pattern_line_trap_12_enabled);
        label_pattern_line_12_glow->setObjectName(QString::fromUtf8("label_pattern_line_12_glow"));

        gridLayout_pattern_line_12->addWidget(label_pattern_line_12_glow, 8, 0, 1, 1);

        logedit_pattern_line_trap_12_glow_spread = new MyLineEdit(groupCheck_pattern_line_trap_12_enabled);
        logedit_pattern_line_trap_12_glow_spread->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_12_glow_spread"));

        gridLayout_pattern_line_12->addWidget(logedit_pattern_line_trap_12_glow_spread, 8, 1, 1, 1);

        comboBox_pattern_line_trap_12_falloff_profile = new MyComboBox(groupCheck_pattern_line_trap_12_enabled);
        comboBox_pattern_line_trap_12_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_12_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_12_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_12_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_12_falloff_profile->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_12_falloff_profile"));

        gridLayout_pattern_line_12->addWidget(comboBox_pattern_line_trap_12_falloff_profile, 8, 2, 1, 3);

        label_pattern_line_12_side = new QLabel(groupCheck_pattern_line_trap_12_enabled);
        label_pattern_line_12_side->setObjectName(QString::fromUtf8("label_pattern_line_12_side"));

        gridLayout_pattern_line_12->addWidget(label_pattern_line_12_side, 9, 0, 1, 1);

        comboBox_pattern_line_trap_12_edge_side = new MyComboBox(groupCheck_pattern_line_trap_12_enabled);
        comboBox_pattern_line_trap_12_edge_side->addItem(QString());
        comboBox_pattern_line_trap_12_edge_side->addItem(QString());
        comboBox_pattern_line_trap_12_edge_side->addItem(QString());
        comboBox_pattern_line_trap_12_edge_side->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_12_edge_side"));

        gridLayout_pattern_line_12->addWidget(comboBox_pattern_line_trap_12_edge_side, 9, 1, 1, 4);

        pushButton_pattern_line_trap_12_place_surface = new QPushButton(groupCheck_pattern_line_trap_12_enabled);
        pushButton_pattern_line_trap_12_place_surface->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_12_place_surface"));

        gridLayout_pattern_line_12->addWidget(pushButton_pattern_line_trap_12_place_surface, 10, 0, 1, 5);

        pushButton_pattern_line_trap_12_place_target = new QPushButton(groupCheck_pattern_line_trap_12_enabled);
        pushButton_pattern_line_trap_12_place_target->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_12_place_target"));

        gridLayout_pattern_line_12->addWidget(pushButton_pattern_line_trap_12_place_target, 11, 0, 1, 5);


        verticalLayout_pattern_line_traps_outer->addWidget(groupCheck_pattern_line_trap_12_enabled);

        groupCheck_pattern_line_trap_13_enabled = new MyGroupBox(groupBox_pattern_line_traps);
        groupCheck_pattern_line_trap_13_enabled->setObjectName(QString::fromUtf8("groupCheck_pattern_line_trap_13_enabled"));
        groupCheck_pattern_line_trap_13_enabled->setCheckable(true);
        gridLayout_pattern_line_13 = new QGridLayout(groupCheck_pattern_line_trap_13_enabled);
        gridLayout_pattern_line_13->setSpacing(2);
        gridLayout_pattern_line_13->setObjectName(QString::fromUtf8("gridLayout_pattern_line_13"));
        label_pattern_line_13_pos = new QLabel(groupCheck_pattern_line_trap_13_enabled);
        label_pattern_line_13_pos->setObjectName(QString::fromUtf8("label_pattern_line_13_pos"));

        gridLayout_pattern_line_13->addWidget(label_pattern_line_13_pos, 0, 0, 1, 1);

        vect3_pattern_line_trap_13_position_x = new MyLineEdit(groupCheck_pattern_line_trap_13_enabled);
        vect3_pattern_line_trap_13_position_x->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_13_position_x"));

        gridLayout_pattern_line_13->addWidget(vect3_pattern_line_trap_13_position_x, 0, 1, 1, 1);

        vect3_pattern_line_trap_13_position_y = new MyLineEdit(groupCheck_pattern_line_trap_13_enabled);
        vect3_pattern_line_trap_13_position_y->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_13_position_y"));

        gridLayout_pattern_line_13->addWidget(vect3_pattern_line_trap_13_position_y, 0, 2, 1, 1);

        vect3_pattern_line_trap_13_position_z = new MyLineEdit(groupCheck_pattern_line_trap_13_enabled);
        vect3_pattern_line_trap_13_position_z->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_13_position_z"));

        gridLayout_pattern_line_13->addWidget(vect3_pattern_line_trap_13_position_z, 0, 3, 1, 1);

        label_pattern_line_13_rot = new QLabel(groupCheck_pattern_line_trap_13_enabled);
        label_pattern_line_13_rot->setObjectName(QString::fromUtf8("label_pattern_line_13_rot"));

        gridLayout_pattern_line_13->addWidget(label_pattern_line_13_rot, 1, 0, 1, 1);

        spinboxd3_pattern_line_trap_13_rotation_x = new MyDoubleSpinBox(groupCheck_pattern_line_trap_13_enabled);
        spinboxd3_pattern_line_trap_13_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_13_rotation_x"));

        gridLayout_pattern_line_13->addWidget(spinboxd3_pattern_line_trap_13_rotation_x, 1, 1, 1, 1);

        spinboxd3_pattern_line_trap_13_rotation_y = new MyDoubleSpinBox(groupCheck_pattern_line_trap_13_enabled);
        spinboxd3_pattern_line_trap_13_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_13_rotation_y"));

        gridLayout_pattern_line_13->addWidget(spinboxd3_pattern_line_trap_13_rotation_y, 1, 2, 1, 1);

        spinboxd3_pattern_line_trap_13_rotation_z = new MyDoubleSpinBox(groupCheck_pattern_line_trap_13_enabled);
        spinboxd3_pattern_line_trap_13_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_13_rotation_z"));

        gridLayout_pattern_line_13->addWidget(spinboxd3_pattern_line_trap_13_rotation_z, 1, 3, 1, 1);

        label_pattern_line_13_radius = new QLabel(groupCheck_pattern_line_trap_13_enabled);
        label_pattern_line_13_radius->setObjectName(QString::fromUtf8("label_pattern_line_13_radius"));

        gridLayout_pattern_line_13->addWidget(label_pattern_line_13_radius, 2, 0, 1, 1);

        logedit_pattern_line_trap_13_radius = new MyLineEdit(groupCheck_pattern_line_trap_13_enabled);
        logedit_pattern_line_trap_13_radius->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_13_radius"));

        gridLayout_pattern_line_13->addWidget(logedit_pattern_line_trap_13_radius, 2, 1, 1, 1);

        logedit_pattern_line_trap_13_thickness = new MyLineEdit(groupCheck_pattern_line_trap_13_enabled);
        logedit_pattern_line_trap_13_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_13_thickness"));

        gridLayout_pattern_line_13->addWidget(logedit_pattern_line_trap_13_thickness, 2, 2, 1, 1);

        logedit_pattern_line_trap_13_edge_softness = new MyLineEdit(groupCheck_pattern_line_trap_13_enabled);
        logedit_pattern_line_trap_13_edge_softness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_13_edge_softness"));

        gridLayout_pattern_line_13->addWidget(logedit_pattern_line_trap_13_edge_softness, 2, 3, 1, 1);

        logedit_pattern_line_trap_13_max_distance = new MyLineEdit(groupCheck_pattern_line_trap_13_enabled);
        logedit_pattern_line_trap_13_max_distance->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_13_max_distance"));

        gridLayout_pattern_line_13->addWidget(logedit_pattern_line_trap_13_max_distance, 2, 4, 1, 1);

        label_pattern_line_13_scale = new QLabel(groupCheck_pattern_line_trap_13_enabled);
        label_pattern_line_13_scale->setObjectName(QString::fromUtf8("label_pattern_line_13_scale"));

        gridLayout_pattern_line_13->addWidget(label_pattern_line_13_scale, 3, 0, 1, 1);

        logedit_pattern_line_trap_13_scale = new MyLineEdit(groupCheck_pattern_line_trap_13_enabled);
        logedit_pattern_line_trap_13_scale->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_13_scale"));

        gridLayout_pattern_line_13->addWidget(logedit_pattern_line_trap_13_scale, 3, 1, 1, 1);

        logedit_pattern_line_trap_13_relative_thickness = new MyLineEdit(groupCheck_pattern_line_trap_13_enabled);
        logedit_pattern_line_trap_13_relative_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_13_relative_thickness"));

        gridLayout_pattern_line_13->addWidget(logedit_pattern_line_trap_13_relative_thickness, 3, 2, 1, 1);

        label_pattern_line_13_int = new QLabel(groupCheck_pattern_line_trap_13_enabled);
        label_pattern_line_13_int->setObjectName(QString::fromUtf8("label_pattern_line_13_int"));

        gridLayout_pattern_line_13->addWidget(label_pattern_line_13_int, 4, 0, 1, 1);

        logedit_pattern_line_trap_13_intensity = new MyLineEdit(groupCheck_pattern_line_trap_13_enabled);
        logedit_pattern_line_trap_13_intensity->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_13_intensity"));

        gridLayout_pattern_line_13->addWidget(logedit_pattern_line_trap_13_intensity, 4, 1, 1, 1);

        colorButton_pattern_line_trap_13_color = new MyColorButton(groupCheck_pattern_line_trap_13_enabled);
        colorButton_pattern_line_trap_13_color->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_13_color"));

        gridLayout_pattern_line_13->addWidget(colorButton_pattern_line_trap_13_color, 4, 2, 1, 1);

        colorButton_pattern_line_trap_13_color_2 = new MyColorButton(groupCheck_pattern_line_trap_13_enabled);
        colorButton_pattern_line_trap_13_color_2->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_13_color_2"));

        gridLayout_pattern_line_13->addWidget(colorButton_pattern_line_trap_13_color_2, 4, 3, 1, 1);

        colorButton_pattern_line_trap_13_color_3 = new MyColorButton(groupCheck_pattern_line_trap_13_enabled);
        colorButton_pattern_line_trap_13_color_3->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_13_color_3"));

        gridLayout_pattern_line_13->addWidget(colorButton_pattern_line_trap_13_color_3, 4, 4, 1, 1);

        label_pattern_line_13_shape = new QLabel(groupCheck_pattern_line_trap_13_enabled);
        label_pattern_line_13_shape->setObjectName(QString::fromUtf8("label_pattern_line_13_shape"));

        gridLayout_pattern_line_13->addWidget(label_pattern_line_13_shape, 5, 0, 1, 1);

        comboBox_pattern_line_trap_13_shape = new MyComboBox(groupCheck_pattern_line_trap_13_enabled);
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->addItem(QString());
        comboBox_pattern_line_trap_13_shape->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_13_shape"));

        gridLayout_pattern_line_13->addWidget(comboBox_pattern_line_trap_13_shape, 5, 1, 1, 4);

        label_pattern_line_13_shape_aux = new QLabel(groupCheck_pattern_line_trap_13_enabled);
        label_pattern_line_13_shape_aux->setObjectName(QString::fromUtf8("label_pattern_line_13_shape_aux"));

        gridLayout_pattern_line_13->addWidget(label_pattern_line_13_shape_aux, 6, 0, 1, 1);

        logedit_pattern_line_trap_13_shape_aux = new MyLineEdit(groupCheck_pattern_line_trap_13_enabled);
        logedit_pattern_line_trap_13_shape_aux->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_13_shape_aux"));

        gridLayout_pattern_line_13->addWidget(logedit_pattern_line_trap_13_shape_aux, 6, 1, 1, 2);

        label_pattern_line_13_sharp_seg = new QLabel(groupCheck_pattern_line_trap_13_enabled);
        label_pattern_line_13_sharp_seg->setObjectName(QString::fromUtf8("label_pattern_line_13_sharp_seg"));

        gridLayout_pattern_line_13->addWidget(label_pattern_line_13_sharp_seg, 7, 0, 1, 1);

        logedit_pattern_line_trap_13_falloff_sharpness = new MyLineEdit(groupCheck_pattern_line_trap_13_enabled);
        logedit_pattern_line_trap_13_falloff_sharpness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_13_falloff_sharpness"));

        gridLayout_pattern_line_13->addWidget(logedit_pattern_line_trap_13_falloff_sharpness, 7, 1, 1, 1);

        logedit_pattern_line_trap_13_segment_half_length = new MyLineEdit(groupCheck_pattern_line_trap_13_enabled);
        logedit_pattern_line_trap_13_segment_half_length->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_13_segment_half_length"));

        gridLayout_pattern_line_13->addWidget(logedit_pattern_line_trap_13_segment_half_length, 7, 2, 1, 1);

        label_pattern_line_13_glow = new QLabel(groupCheck_pattern_line_trap_13_enabled);
        label_pattern_line_13_glow->setObjectName(QString::fromUtf8("label_pattern_line_13_glow"));

        gridLayout_pattern_line_13->addWidget(label_pattern_line_13_glow, 8, 0, 1, 1);

        logedit_pattern_line_trap_13_glow_spread = new MyLineEdit(groupCheck_pattern_line_trap_13_enabled);
        logedit_pattern_line_trap_13_glow_spread->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_13_glow_spread"));

        gridLayout_pattern_line_13->addWidget(logedit_pattern_line_trap_13_glow_spread, 8, 1, 1, 1);

        comboBox_pattern_line_trap_13_falloff_profile = new MyComboBox(groupCheck_pattern_line_trap_13_enabled);
        comboBox_pattern_line_trap_13_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_13_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_13_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_13_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_13_falloff_profile->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_13_falloff_profile"));

        gridLayout_pattern_line_13->addWidget(comboBox_pattern_line_trap_13_falloff_profile, 8, 2, 1, 3);

        label_pattern_line_13_side = new QLabel(groupCheck_pattern_line_trap_13_enabled);
        label_pattern_line_13_side->setObjectName(QString::fromUtf8("label_pattern_line_13_side"));

        gridLayout_pattern_line_13->addWidget(label_pattern_line_13_side, 9, 0, 1, 1);

        comboBox_pattern_line_trap_13_edge_side = new MyComboBox(groupCheck_pattern_line_trap_13_enabled);
        comboBox_pattern_line_trap_13_edge_side->addItem(QString());
        comboBox_pattern_line_trap_13_edge_side->addItem(QString());
        comboBox_pattern_line_trap_13_edge_side->addItem(QString());
        comboBox_pattern_line_trap_13_edge_side->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_13_edge_side"));

        gridLayout_pattern_line_13->addWidget(comboBox_pattern_line_trap_13_edge_side, 9, 1, 1, 4);

        pushButton_pattern_line_trap_13_place_surface = new QPushButton(groupCheck_pattern_line_trap_13_enabled);
        pushButton_pattern_line_trap_13_place_surface->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_13_place_surface"));

        gridLayout_pattern_line_13->addWidget(pushButton_pattern_line_trap_13_place_surface, 10, 0, 1, 5);

        pushButton_pattern_line_trap_13_place_target = new QPushButton(groupCheck_pattern_line_trap_13_enabled);
        pushButton_pattern_line_trap_13_place_target->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_13_place_target"));

        gridLayout_pattern_line_13->addWidget(pushButton_pattern_line_trap_13_place_target, 11, 0, 1, 5);


        verticalLayout_pattern_line_traps_outer->addWidget(groupCheck_pattern_line_trap_13_enabled);

        groupCheck_pattern_line_trap_14_enabled = new MyGroupBox(groupBox_pattern_line_traps);
        groupCheck_pattern_line_trap_14_enabled->setObjectName(QString::fromUtf8("groupCheck_pattern_line_trap_14_enabled"));
        groupCheck_pattern_line_trap_14_enabled->setCheckable(true);
        gridLayout_pattern_line_14 = new QGridLayout(groupCheck_pattern_line_trap_14_enabled);
        gridLayout_pattern_line_14->setSpacing(2);
        gridLayout_pattern_line_14->setObjectName(QString::fromUtf8("gridLayout_pattern_line_14"));
        label_pattern_line_14_pos = new QLabel(groupCheck_pattern_line_trap_14_enabled);
        label_pattern_line_14_pos->setObjectName(QString::fromUtf8("label_pattern_line_14_pos"));

        gridLayout_pattern_line_14->addWidget(label_pattern_line_14_pos, 0, 0, 1, 1);

        vect3_pattern_line_trap_14_position_x = new MyLineEdit(groupCheck_pattern_line_trap_14_enabled);
        vect3_pattern_line_trap_14_position_x->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_14_position_x"));

        gridLayout_pattern_line_14->addWidget(vect3_pattern_line_trap_14_position_x, 0, 1, 1, 1);

        vect3_pattern_line_trap_14_position_y = new MyLineEdit(groupCheck_pattern_line_trap_14_enabled);
        vect3_pattern_line_trap_14_position_y->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_14_position_y"));

        gridLayout_pattern_line_14->addWidget(vect3_pattern_line_trap_14_position_y, 0, 2, 1, 1);

        vect3_pattern_line_trap_14_position_z = new MyLineEdit(groupCheck_pattern_line_trap_14_enabled);
        vect3_pattern_line_trap_14_position_z->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_14_position_z"));

        gridLayout_pattern_line_14->addWidget(vect3_pattern_line_trap_14_position_z, 0, 3, 1, 1);

        label_pattern_line_14_rot = new QLabel(groupCheck_pattern_line_trap_14_enabled);
        label_pattern_line_14_rot->setObjectName(QString::fromUtf8("label_pattern_line_14_rot"));

        gridLayout_pattern_line_14->addWidget(label_pattern_line_14_rot, 1, 0, 1, 1);

        spinboxd3_pattern_line_trap_14_rotation_x = new MyDoubleSpinBox(groupCheck_pattern_line_trap_14_enabled);
        spinboxd3_pattern_line_trap_14_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_14_rotation_x"));

        gridLayout_pattern_line_14->addWidget(spinboxd3_pattern_line_trap_14_rotation_x, 1, 1, 1, 1);

        spinboxd3_pattern_line_trap_14_rotation_y = new MyDoubleSpinBox(groupCheck_pattern_line_trap_14_enabled);
        spinboxd3_pattern_line_trap_14_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_14_rotation_y"));

        gridLayout_pattern_line_14->addWidget(spinboxd3_pattern_line_trap_14_rotation_y, 1, 2, 1, 1);

        spinboxd3_pattern_line_trap_14_rotation_z = new MyDoubleSpinBox(groupCheck_pattern_line_trap_14_enabled);
        spinboxd3_pattern_line_trap_14_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_14_rotation_z"));

        gridLayout_pattern_line_14->addWidget(spinboxd3_pattern_line_trap_14_rotation_z, 1, 3, 1, 1);

        label_pattern_line_14_radius = new QLabel(groupCheck_pattern_line_trap_14_enabled);
        label_pattern_line_14_radius->setObjectName(QString::fromUtf8("label_pattern_line_14_radius"));

        gridLayout_pattern_line_14->addWidget(label_pattern_line_14_radius, 2, 0, 1, 1);

        logedit_pattern_line_trap_14_radius = new MyLineEdit(groupCheck_pattern_line_trap_14_enabled);
        logedit_pattern_line_trap_14_radius->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_14_radius"));

        gridLayout_pattern_line_14->addWidget(logedit_pattern_line_trap_14_radius, 2, 1, 1, 1);

        logedit_pattern_line_trap_14_thickness = new MyLineEdit(groupCheck_pattern_line_trap_14_enabled);
        logedit_pattern_line_trap_14_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_14_thickness"));

        gridLayout_pattern_line_14->addWidget(logedit_pattern_line_trap_14_thickness, 2, 2, 1, 1);

        logedit_pattern_line_trap_14_edge_softness = new MyLineEdit(groupCheck_pattern_line_trap_14_enabled);
        logedit_pattern_line_trap_14_edge_softness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_14_edge_softness"));

        gridLayout_pattern_line_14->addWidget(logedit_pattern_line_trap_14_edge_softness, 2, 3, 1, 1);

        logedit_pattern_line_trap_14_max_distance = new MyLineEdit(groupCheck_pattern_line_trap_14_enabled);
        logedit_pattern_line_trap_14_max_distance->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_14_max_distance"));

        gridLayout_pattern_line_14->addWidget(logedit_pattern_line_trap_14_max_distance, 2, 4, 1, 1);

        label_pattern_line_14_scale = new QLabel(groupCheck_pattern_line_trap_14_enabled);
        label_pattern_line_14_scale->setObjectName(QString::fromUtf8("label_pattern_line_14_scale"));

        gridLayout_pattern_line_14->addWidget(label_pattern_line_14_scale, 3, 0, 1, 1);

        logedit_pattern_line_trap_14_scale = new MyLineEdit(groupCheck_pattern_line_trap_14_enabled);
        logedit_pattern_line_trap_14_scale->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_14_scale"));

        gridLayout_pattern_line_14->addWidget(logedit_pattern_line_trap_14_scale, 3, 1, 1, 1);

        logedit_pattern_line_trap_14_relative_thickness = new MyLineEdit(groupCheck_pattern_line_trap_14_enabled);
        logedit_pattern_line_trap_14_relative_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_14_relative_thickness"));

        gridLayout_pattern_line_14->addWidget(logedit_pattern_line_trap_14_relative_thickness, 3, 2, 1, 1);

        label_pattern_line_14_int = new QLabel(groupCheck_pattern_line_trap_14_enabled);
        label_pattern_line_14_int->setObjectName(QString::fromUtf8("label_pattern_line_14_int"));

        gridLayout_pattern_line_14->addWidget(label_pattern_line_14_int, 4, 0, 1, 1);

        logedit_pattern_line_trap_14_intensity = new MyLineEdit(groupCheck_pattern_line_trap_14_enabled);
        logedit_pattern_line_trap_14_intensity->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_14_intensity"));

        gridLayout_pattern_line_14->addWidget(logedit_pattern_line_trap_14_intensity, 4, 1, 1, 1);

        colorButton_pattern_line_trap_14_color = new MyColorButton(groupCheck_pattern_line_trap_14_enabled);
        colorButton_pattern_line_trap_14_color->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_14_color"));

        gridLayout_pattern_line_14->addWidget(colorButton_pattern_line_trap_14_color, 4, 2, 1, 1);

        colorButton_pattern_line_trap_14_color_2 = new MyColorButton(groupCheck_pattern_line_trap_14_enabled);
        colorButton_pattern_line_trap_14_color_2->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_14_color_2"));

        gridLayout_pattern_line_14->addWidget(colorButton_pattern_line_trap_14_color_2, 4, 3, 1, 1);

        colorButton_pattern_line_trap_14_color_3 = new MyColorButton(groupCheck_pattern_line_trap_14_enabled);
        colorButton_pattern_line_trap_14_color_3->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_14_color_3"));

        gridLayout_pattern_line_14->addWidget(colorButton_pattern_line_trap_14_color_3, 4, 4, 1, 1);

        label_pattern_line_14_shape = new QLabel(groupCheck_pattern_line_trap_14_enabled);
        label_pattern_line_14_shape->setObjectName(QString::fromUtf8("label_pattern_line_14_shape"));

        gridLayout_pattern_line_14->addWidget(label_pattern_line_14_shape, 5, 0, 1, 1);

        comboBox_pattern_line_trap_14_shape = new MyComboBox(groupCheck_pattern_line_trap_14_enabled);
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->addItem(QString());
        comboBox_pattern_line_trap_14_shape->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_14_shape"));

        gridLayout_pattern_line_14->addWidget(comboBox_pattern_line_trap_14_shape, 5, 1, 1, 4);

        label_pattern_line_14_shape_aux = new QLabel(groupCheck_pattern_line_trap_14_enabled);
        label_pattern_line_14_shape_aux->setObjectName(QString::fromUtf8("label_pattern_line_14_shape_aux"));

        gridLayout_pattern_line_14->addWidget(label_pattern_line_14_shape_aux, 6, 0, 1, 1);

        logedit_pattern_line_trap_14_shape_aux = new MyLineEdit(groupCheck_pattern_line_trap_14_enabled);
        logedit_pattern_line_trap_14_shape_aux->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_14_shape_aux"));

        gridLayout_pattern_line_14->addWidget(logedit_pattern_line_trap_14_shape_aux, 6, 1, 1, 2);

        label_pattern_line_14_sharp_seg = new QLabel(groupCheck_pattern_line_trap_14_enabled);
        label_pattern_line_14_sharp_seg->setObjectName(QString::fromUtf8("label_pattern_line_14_sharp_seg"));

        gridLayout_pattern_line_14->addWidget(label_pattern_line_14_sharp_seg, 7, 0, 1, 1);

        logedit_pattern_line_trap_14_falloff_sharpness = new MyLineEdit(groupCheck_pattern_line_trap_14_enabled);
        logedit_pattern_line_trap_14_falloff_sharpness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_14_falloff_sharpness"));

        gridLayout_pattern_line_14->addWidget(logedit_pattern_line_trap_14_falloff_sharpness, 7, 1, 1, 1);

        logedit_pattern_line_trap_14_segment_half_length = new MyLineEdit(groupCheck_pattern_line_trap_14_enabled);
        logedit_pattern_line_trap_14_segment_half_length->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_14_segment_half_length"));

        gridLayout_pattern_line_14->addWidget(logedit_pattern_line_trap_14_segment_half_length, 7, 2, 1, 1);

        label_pattern_line_14_glow = new QLabel(groupCheck_pattern_line_trap_14_enabled);
        label_pattern_line_14_glow->setObjectName(QString::fromUtf8("label_pattern_line_14_glow"));

        gridLayout_pattern_line_14->addWidget(label_pattern_line_14_glow, 8, 0, 1, 1);

        logedit_pattern_line_trap_14_glow_spread = new MyLineEdit(groupCheck_pattern_line_trap_14_enabled);
        logedit_pattern_line_trap_14_glow_spread->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_14_glow_spread"));

        gridLayout_pattern_line_14->addWidget(logedit_pattern_line_trap_14_glow_spread, 8, 1, 1, 1);

        comboBox_pattern_line_trap_14_falloff_profile = new MyComboBox(groupCheck_pattern_line_trap_14_enabled);
        comboBox_pattern_line_trap_14_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_14_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_14_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_14_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_14_falloff_profile->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_14_falloff_profile"));

        gridLayout_pattern_line_14->addWidget(comboBox_pattern_line_trap_14_falloff_profile, 8, 2, 1, 3);

        label_pattern_line_14_side = new QLabel(groupCheck_pattern_line_trap_14_enabled);
        label_pattern_line_14_side->setObjectName(QString::fromUtf8("label_pattern_line_14_side"));

        gridLayout_pattern_line_14->addWidget(label_pattern_line_14_side, 9, 0, 1, 1);

        comboBox_pattern_line_trap_14_edge_side = new MyComboBox(groupCheck_pattern_line_trap_14_enabled);
        comboBox_pattern_line_trap_14_edge_side->addItem(QString());
        comboBox_pattern_line_trap_14_edge_side->addItem(QString());
        comboBox_pattern_line_trap_14_edge_side->addItem(QString());
        comboBox_pattern_line_trap_14_edge_side->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_14_edge_side"));

        gridLayout_pattern_line_14->addWidget(comboBox_pattern_line_trap_14_edge_side, 9, 1, 1, 4);

        pushButton_pattern_line_trap_14_place_surface = new QPushButton(groupCheck_pattern_line_trap_14_enabled);
        pushButton_pattern_line_trap_14_place_surface->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_14_place_surface"));

        gridLayout_pattern_line_14->addWidget(pushButton_pattern_line_trap_14_place_surface, 10, 0, 1, 5);

        pushButton_pattern_line_trap_14_place_target = new QPushButton(groupCheck_pattern_line_trap_14_enabled);
        pushButton_pattern_line_trap_14_place_target->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_14_place_target"));

        gridLayout_pattern_line_14->addWidget(pushButton_pattern_line_trap_14_place_target, 11, 0, 1, 5);


        verticalLayout_pattern_line_traps_outer->addWidget(groupCheck_pattern_line_trap_14_enabled);

        groupCheck_pattern_line_trap_15_enabled = new MyGroupBox(groupBox_pattern_line_traps);
        groupCheck_pattern_line_trap_15_enabled->setObjectName(QString::fromUtf8("groupCheck_pattern_line_trap_15_enabled"));
        groupCheck_pattern_line_trap_15_enabled->setCheckable(true);
        gridLayout_pattern_line_15 = new QGridLayout(groupCheck_pattern_line_trap_15_enabled);
        gridLayout_pattern_line_15->setSpacing(2);
        gridLayout_pattern_line_15->setObjectName(QString::fromUtf8("gridLayout_pattern_line_15"));
        label_pattern_line_15_pos = new QLabel(groupCheck_pattern_line_trap_15_enabled);
        label_pattern_line_15_pos->setObjectName(QString::fromUtf8("label_pattern_line_15_pos"));

        gridLayout_pattern_line_15->addWidget(label_pattern_line_15_pos, 0, 0, 1, 1);

        vect3_pattern_line_trap_15_position_x = new MyLineEdit(groupCheck_pattern_line_trap_15_enabled);
        vect3_pattern_line_trap_15_position_x->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_15_position_x"));

        gridLayout_pattern_line_15->addWidget(vect3_pattern_line_trap_15_position_x, 0, 1, 1, 1);

        vect3_pattern_line_trap_15_position_y = new MyLineEdit(groupCheck_pattern_line_trap_15_enabled);
        vect3_pattern_line_trap_15_position_y->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_15_position_y"));

        gridLayout_pattern_line_15->addWidget(vect3_pattern_line_trap_15_position_y, 0, 2, 1, 1);

        vect3_pattern_line_trap_15_position_z = new MyLineEdit(groupCheck_pattern_line_trap_15_enabled);
        vect3_pattern_line_trap_15_position_z->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_15_position_z"));

        gridLayout_pattern_line_15->addWidget(vect3_pattern_line_trap_15_position_z, 0, 3, 1, 1);

        label_pattern_line_15_rot = new QLabel(groupCheck_pattern_line_trap_15_enabled);
        label_pattern_line_15_rot->setObjectName(QString::fromUtf8("label_pattern_line_15_rot"));

        gridLayout_pattern_line_15->addWidget(label_pattern_line_15_rot, 1, 0, 1, 1);

        spinboxd3_pattern_line_trap_15_rotation_x = new MyDoubleSpinBox(groupCheck_pattern_line_trap_15_enabled);
        spinboxd3_pattern_line_trap_15_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_15_rotation_x"));

        gridLayout_pattern_line_15->addWidget(spinboxd3_pattern_line_trap_15_rotation_x, 1, 1, 1, 1);

        spinboxd3_pattern_line_trap_15_rotation_y = new MyDoubleSpinBox(groupCheck_pattern_line_trap_15_enabled);
        spinboxd3_pattern_line_trap_15_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_15_rotation_y"));

        gridLayout_pattern_line_15->addWidget(spinboxd3_pattern_line_trap_15_rotation_y, 1, 2, 1, 1);

        spinboxd3_pattern_line_trap_15_rotation_z = new MyDoubleSpinBox(groupCheck_pattern_line_trap_15_enabled);
        spinboxd3_pattern_line_trap_15_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_15_rotation_z"));

        gridLayout_pattern_line_15->addWidget(spinboxd3_pattern_line_trap_15_rotation_z, 1, 3, 1, 1);

        label_pattern_line_15_radius = new QLabel(groupCheck_pattern_line_trap_15_enabled);
        label_pattern_line_15_radius->setObjectName(QString::fromUtf8("label_pattern_line_15_radius"));

        gridLayout_pattern_line_15->addWidget(label_pattern_line_15_radius, 2, 0, 1, 1);

        logedit_pattern_line_trap_15_radius = new MyLineEdit(groupCheck_pattern_line_trap_15_enabled);
        logedit_pattern_line_trap_15_radius->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_15_radius"));

        gridLayout_pattern_line_15->addWidget(logedit_pattern_line_trap_15_radius, 2, 1, 1, 1);

        logedit_pattern_line_trap_15_thickness = new MyLineEdit(groupCheck_pattern_line_trap_15_enabled);
        logedit_pattern_line_trap_15_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_15_thickness"));

        gridLayout_pattern_line_15->addWidget(logedit_pattern_line_trap_15_thickness, 2, 2, 1, 1);

        logedit_pattern_line_trap_15_edge_softness = new MyLineEdit(groupCheck_pattern_line_trap_15_enabled);
        logedit_pattern_line_trap_15_edge_softness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_15_edge_softness"));

        gridLayout_pattern_line_15->addWidget(logedit_pattern_line_trap_15_edge_softness, 2, 3, 1, 1);

        logedit_pattern_line_trap_15_max_distance = new MyLineEdit(groupCheck_pattern_line_trap_15_enabled);
        logedit_pattern_line_trap_15_max_distance->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_15_max_distance"));

        gridLayout_pattern_line_15->addWidget(logedit_pattern_line_trap_15_max_distance, 2, 4, 1, 1);

        label_pattern_line_15_scale = new QLabel(groupCheck_pattern_line_trap_15_enabled);
        label_pattern_line_15_scale->setObjectName(QString::fromUtf8("label_pattern_line_15_scale"));

        gridLayout_pattern_line_15->addWidget(label_pattern_line_15_scale, 3, 0, 1, 1);

        logedit_pattern_line_trap_15_scale = new MyLineEdit(groupCheck_pattern_line_trap_15_enabled);
        logedit_pattern_line_trap_15_scale->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_15_scale"));

        gridLayout_pattern_line_15->addWidget(logedit_pattern_line_trap_15_scale, 3, 1, 1, 1);

        logedit_pattern_line_trap_15_relative_thickness = new MyLineEdit(groupCheck_pattern_line_trap_15_enabled);
        logedit_pattern_line_trap_15_relative_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_15_relative_thickness"));

        gridLayout_pattern_line_15->addWidget(logedit_pattern_line_trap_15_relative_thickness, 3, 2, 1, 1);

        label_pattern_line_15_int = new QLabel(groupCheck_pattern_line_trap_15_enabled);
        label_pattern_line_15_int->setObjectName(QString::fromUtf8("label_pattern_line_15_int"));

        gridLayout_pattern_line_15->addWidget(label_pattern_line_15_int, 4, 0, 1, 1);

        logedit_pattern_line_trap_15_intensity = new MyLineEdit(groupCheck_pattern_line_trap_15_enabled);
        logedit_pattern_line_trap_15_intensity->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_15_intensity"));

        gridLayout_pattern_line_15->addWidget(logedit_pattern_line_trap_15_intensity, 4, 1, 1, 1);

        colorButton_pattern_line_trap_15_color = new MyColorButton(groupCheck_pattern_line_trap_15_enabled);
        colorButton_pattern_line_trap_15_color->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_15_color"));

        gridLayout_pattern_line_15->addWidget(colorButton_pattern_line_trap_15_color, 4, 2, 1, 1);

        colorButton_pattern_line_trap_15_color_2 = new MyColorButton(groupCheck_pattern_line_trap_15_enabled);
        colorButton_pattern_line_trap_15_color_2->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_15_color_2"));

        gridLayout_pattern_line_15->addWidget(colorButton_pattern_line_trap_15_color_2, 4, 3, 1, 1);

        colorButton_pattern_line_trap_15_color_3 = new MyColorButton(groupCheck_pattern_line_trap_15_enabled);
        colorButton_pattern_line_trap_15_color_3->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_15_color_3"));

        gridLayout_pattern_line_15->addWidget(colorButton_pattern_line_trap_15_color_3, 4, 4, 1, 1);

        label_pattern_line_15_shape = new QLabel(groupCheck_pattern_line_trap_15_enabled);
        label_pattern_line_15_shape->setObjectName(QString::fromUtf8("label_pattern_line_15_shape"));

        gridLayout_pattern_line_15->addWidget(label_pattern_line_15_shape, 5, 0, 1, 1);

        comboBox_pattern_line_trap_15_shape = new MyComboBox(groupCheck_pattern_line_trap_15_enabled);
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->addItem(QString());
        comboBox_pattern_line_trap_15_shape->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_15_shape"));

        gridLayout_pattern_line_15->addWidget(comboBox_pattern_line_trap_15_shape, 5, 1, 1, 4);

        label_pattern_line_15_shape_aux = new QLabel(groupCheck_pattern_line_trap_15_enabled);
        label_pattern_line_15_shape_aux->setObjectName(QString::fromUtf8("label_pattern_line_15_shape_aux"));

        gridLayout_pattern_line_15->addWidget(label_pattern_line_15_shape_aux, 6, 0, 1, 1);

        logedit_pattern_line_trap_15_shape_aux = new MyLineEdit(groupCheck_pattern_line_trap_15_enabled);
        logedit_pattern_line_trap_15_shape_aux->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_15_shape_aux"));

        gridLayout_pattern_line_15->addWidget(logedit_pattern_line_trap_15_shape_aux, 6, 1, 1, 2);

        label_pattern_line_15_sharp_seg = new QLabel(groupCheck_pattern_line_trap_15_enabled);
        label_pattern_line_15_sharp_seg->setObjectName(QString::fromUtf8("label_pattern_line_15_sharp_seg"));

        gridLayout_pattern_line_15->addWidget(label_pattern_line_15_sharp_seg, 7, 0, 1, 1);

        logedit_pattern_line_trap_15_falloff_sharpness = new MyLineEdit(groupCheck_pattern_line_trap_15_enabled);
        logedit_pattern_line_trap_15_falloff_sharpness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_15_falloff_sharpness"));

        gridLayout_pattern_line_15->addWidget(logedit_pattern_line_trap_15_falloff_sharpness, 7, 1, 1, 1);

        logedit_pattern_line_trap_15_segment_half_length = new MyLineEdit(groupCheck_pattern_line_trap_15_enabled);
        logedit_pattern_line_trap_15_segment_half_length->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_15_segment_half_length"));

        gridLayout_pattern_line_15->addWidget(logedit_pattern_line_trap_15_segment_half_length, 7, 2, 1, 1);

        label_pattern_line_15_glow = new QLabel(groupCheck_pattern_line_trap_15_enabled);
        label_pattern_line_15_glow->setObjectName(QString::fromUtf8("label_pattern_line_15_glow"));

        gridLayout_pattern_line_15->addWidget(label_pattern_line_15_glow, 8, 0, 1, 1);

        logedit_pattern_line_trap_15_glow_spread = new MyLineEdit(groupCheck_pattern_line_trap_15_enabled);
        logedit_pattern_line_trap_15_glow_spread->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_15_glow_spread"));

        gridLayout_pattern_line_15->addWidget(logedit_pattern_line_trap_15_glow_spread, 8, 1, 1, 1);

        comboBox_pattern_line_trap_15_falloff_profile = new MyComboBox(groupCheck_pattern_line_trap_15_enabled);
        comboBox_pattern_line_trap_15_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_15_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_15_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_15_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_15_falloff_profile->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_15_falloff_profile"));

        gridLayout_pattern_line_15->addWidget(comboBox_pattern_line_trap_15_falloff_profile, 8, 2, 1, 3);

        label_pattern_line_15_side = new QLabel(groupCheck_pattern_line_trap_15_enabled);
        label_pattern_line_15_side->setObjectName(QString::fromUtf8("label_pattern_line_15_side"));

        gridLayout_pattern_line_15->addWidget(label_pattern_line_15_side, 9, 0, 1, 1);

        comboBox_pattern_line_trap_15_edge_side = new MyComboBox(groupCheck_pattern_line_trap_15_enabled);
        comboBox_pattern_line_trap_15_edge_side->addItem(QString());
        comboBox_pattern_line_trap_15_edge_side->addItem(QString());
        comboBox_pattern_line_trap_15_edge_side->addItem(QString());
        comboBox_pattern_line_trap_15_edge_side->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_15_edge_side"));

        gridLayout_pattern_line_15->addWidget(comboBox_pattern_line_trap_15_edge_side, 9, 1, 1, 4);

        pushButton_pattern_line_trap_15_place_surface = new QPushButton(groupCheck_pattern_line_trap_15_enabled);
        pushButton_pattern_line_trap_15_place_surface->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_15_place_surface"));

        gridLayout_pattern_line_15->addWidget(pushButton_pattern_line_trap_15_place_surface, 10, 0, 1, 5);

        pushButton_pattern_line_trap_15_place_target = new QPushButton(groupCheck_pattern_line_trap_15_enabled);
        pushButton_pattern_line_trap_15_place_target->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_15_place_target"));

        gridLayout_pattern_line_15->addWidget(pushButton_pattern_line_trap_15_place_target, 11, 0, 1, 5);


        verticalLayout_pattern_line_traps_outer->addWidget(groupCheck_pattern_line_trap_15_enabled);

        groupCheck_pattern_line_trap_16_enabled = new MyGroupBox(groupBox_pattern_line_traps);
        groupCheck_pattern_line_trap_16_enabled->setObjectName(QString::fromUtf8("groupCheck_pattern_line_trap_16_enabled"));
        groupCheck_pattern_line_trap_16_enabled->setCheckable(true);
        gridLayout_pattern_line_16 = new QGridLayout(groupCheck_pattern_line_trap_16_enabled);
        gridLayout_pattern_line_16->setSpacing(2);
        gridLayout_pattern_line_16->setObjectName(QString::fromUtf8("gridLayout_pattern_line_16"));
        label_pattern_line_16_pos = new QLabel(groupCheck_pattern_line_trap_16_enabled);
        label_pattern_line_16_pos->setObjectName(QString::fromUtf8("label_pattern_line_16_pos"));

        gridLayout_pattern_line_16->addWidget(label_pattern_line_16_pos, 0, 0, 1, 1);

        vect3_pattern_line_trap_16_position_x = new MyLineEdit(groupCheck_pattern_line_trap_16_enabled);
        vect3_pattern_line_trap_16_position_x->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_16_position_x"));

        gridLayout_pattern_line_16->addWidget(vect3_pattern_line_trap_16_position_x, 0, 1, 1, 1);

        vect3_pattern_line_trap_16_position_y = new MyLineEdit(groupCheck_pattern_line_trap_16_enabled);
        vect3_pattern_line_trap_16_position_y->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_16_position_y"));

        gridLayout_pattern_line_16->addWidget(vect3_pattern_line_trap_16_position_y, 0, 2, 1, 1);

        vect3_pattern_line_trap_16_position_z = new MyLineEdit(groupCheck_pattern_line_trap_16_enabled);
        vect3_pattern_line_trap_16_position_z->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_16_position_z"));

        gridLayout_pattern_line_16->addWidget(vect3_pattern_line_trap_16_position_z, 0, 3, 1, 1);

        label_pattern_line_16_rot = new QLabel(groupCheck_pattern_line_trap_16_enabled);
        label_pattern_line_16_rot->setObjectName(QString::fromUtf8("label_pattern_line_16_rot"));

        gridLayout_pattern_line_16->addWidget(label_pattern_line_16_rot, 1, 0, 1, 1);

        spinboxd3_pattern_line_trap_16_rotation_x = new MyDoubleSpinBox(groupCheck_pattern_line_trap_16_enabled);
        spinboxd3_pattern_line_trap_16_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_16_rotation_x"));

        gridLayout_pattern_line_16->addWidget(spinboxd3_pattern_line_trap_16_rotation_x, 1, 1, 1, 1);

        spinboxd3_pattern_line_trap_16_rotation_y = new MyDoubleSpinBox(groupCheck_pattern_line_trap_16_enabled);
        spinboxd3_pattern_line_trap_16_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_16_rotation_y"));

        gridLayout_pattern_line_16->addWidget(spinboxd3_pattern_line_trap_16_rotation_y, 1, 2, 1, 1);

        spinboxd3_pattern_line_trap_16_rotation_z = new MyDoubleSpinBox(groupCheck_pattern_line_trap_16_enabled);
        spinboxd3_pattern_line_trap_16_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_16_rotation_z"));

        gridLayout_pattern_line_16->addWidget(spinboxd3_pattern_line_trap_16_rotation_z, 1, 3, 1, 1);

        label_pattern_line_16_radius = new QLabel(groupCheck_pattern_line_trap_16_enabled);
        label_pattern_line_16_radius->setObjectName(QString::fromUtf8("label_pattern_line_16_radius"));

        gridLayout_pattern_line_16->addWidget(label_pattern_line_16_radius, 2, 0, 1, 1);

        logedit_pattern_line_trap_16_radius = new MyLineEdit(groupCheck_pattern_line_trap_16_enabled);
        logedit_pattern_line_trap_16_radius->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_16_radius"));

        gridLayout_pattern_line_16->addWidget(logedit_pattern_line_trap_16_radius, 2, 1, 1, 1);

        logedit_pattern_line_trap_16_thickness = new MyLineEdit(groupCheck_pattern_line_trap_16_enabled);
        logedit_pattern_line_trap_16_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_16_thickness"));

        gridLayout_pattern_line_16->addWidget(logedit_pattern_line_trap_16_thickness, 2, 2, 1, 1);

        logedit_pattern_line_trap_16_edge_softness = new MyLineEdit(groupCheck_pattern_line_trap_16_enabled);
        logedit_pattern_line_trap_16_edge_softness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_16_edge_softness"));

        gridLayout_pattern_line_16->addWidget(logedit_pattern_line_trap_16_edge_softness, 2, 3, 1, 1);

        logedit_pattern_line_trap_16_max_distance = new MyLineEdit(groupCheck_pattern_line_trap_16_enabled);
        logedit_pattern_line_trap_16_max_distance->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_16_max_distance"));

        gridLayout_pattern_line_16->addWidget(logedit_pattern_line_trap_16_max_distance, 2, 4, 1, 1);

        label_pattern_line_16_scale = new QLabel(groupCheck_pattern_line_trap_16_enabled);
        label_pattern_line_16_scale->setObjectName(QString::fromUtf8("label_pattern_line_16_scale"));

        gridLayout_pattern_line_16->addWidget(label_pattern_line_16_scale, 3, 0, 1, 1);

        logedit_pattern_line_trap_16_scale = new MyLineEdit(groupCheck_pattern_line_trap_16_enabled);
        logedit_pattern_line_trap_16_scale->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_16_scale"));

        gridLayout_pattern_line_16->addWidget(logedit_pattern_line_trap_16_scale, 3, 1, 1, 1);

        logedit_pattern_line_trap_16_relative_thickness = new MyLineEdit(groupCheck_pattern_line_trap_16_enabled);
        logedit_pattern_line_trap_16_relative_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_16_relative_thickness"));

        gridLayout_pattern_line_16->addWidget(logedit_pattern_line_trap_16_relative_thickness, 3, 2, 1, 1);

        label_pattern_line_16_int = new QLabel(groupCheck_pattern_line_trap_16_enabled);
        label_pattern_line_16_int->setObjectName(QString::fromUtf8("label_pattern_line_16_int"));

        gridLayout_pattern_line_16->addWidget(label_pattern_line_16_int, 4, 0, 1, 1);

        logedit_pattern_line_trap_16_intensity = new MyLineEdit(groupCheck_pattern_line_trap_16_enabled);
        logedit_pattern_line_trap_16_intensity->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_16_intensity"));

        gridLayout_pattern_line_16->addWidget(logedit_pattern_line_trap_16_intensity, 4, 1, 1, 1);

        colorButton_pattern_line_trap_16_color = new MyColorButton(groupCheck_pattern_line_trap_16_enabled);
        colorButton_pattern_line_trap_16_color->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_16_color"));

        gridLayout_pattern_line_16->addWidget(colorButton_pattern_line_trap_16_color, 4, 2, 1, 1);

        colorButton_pattern_line_trap_16_color_2 = new MyColorButton(groupCheck_pattern_line_trap_16_enabled);
        colorButton_pattern_line_trap_16_color_2->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_16_color_2"));

        gridLayout_pattern_line_16->addWidget(colorButton_pattern_line_trap_16_color_2, 4, 3, 1, 1);

        colorButton_pattern_line_trap_16_color_3 = new MyColorButton(groupCheck_pattern_line_trap_16_enabled);
        colorButton_pattern_line_trap_16_color_3->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_16_color_3"));

        gridLayout_pattern_line_16->addWidget(colorButton_pattern_line_trap_16_color_3, 4, 4, 1, 1);

        label_pattern_line_16_shape = new QLabel(groupCheck_pattern_line_trap_16_enabled);
        label_pattern_line_16_shape->setObjectName(QString::fromUtf8("label_pattern_line_16_shape"));

        gridLayout_pattern_line_16->addWidget(label_pattern_line_16_shape, 5, 0, 1, 1);

        comboBox_pattern_line_trap_16_shape = new MyComboBox(groupCheck_pattern_line_trap_16_enabled);
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->addItem(QString());
        comboBox_pattern_line_trap_16_shape->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_16_shape"));

        gridLayout_pattern_line_16->addWidget(comboBox_pattern_line_trap_16_shape, 5, 1, 1, 4);

        label_pattern_line_16_shape_aux = new QLabel(groupCheck_pattern_line_trap_16_enabled);
        label_pattern_line_16_shape_aux->setObjectName(QString::fromUtf8("label_pattern_line_16_shape_aux"));

        gridLayout_pattern_line_16->addWidget(label_pattern_line_16_shape_aux, 6, 0, 1, 1);

        logedit_pattern_line_trap_16_shape_aux = new MyLineEdit(groupCheck_pattern_line_trap_16_enabled);
        logedit_pattern_line_trap_16_shape_aux->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_16_shape_aux"));

        gridLayout_pattern_line_16->addWidget(logedit_pattern_line_trap_16_shape_aux, 6, 1, 1, 2);

        label_pattern_line_16_sharp_seg = new QLabel(groupCheck_pattern_line_trap_16_enabled);
        label_pattern_line_16_sharp_seg->setObjectName(QString::fromUtf8("label_pattern_line_16_sharp_seg"));

        gridLayout_pattern_line_16->addWidget(label_pattern_line_16_sharp_seg, 7, 0, 1, 1);

        logedit_pattern_line_trap_16_falloff_sharpness = new MyLineEdit(groupCheck_pattern_line_trap_16_enabled);
        logedit_pattern_line_trap_16_falloff_sharpness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_16_falloff_sharpness"));

        gridLayout_pattern_line_16->addWidget(logedit_pattern_line_trap_16_falloff_sharpness, 7, 1, 1, 1);

        logedit_pattern_line_trap_16_segment_half_length = new MyLineEdit(groupCheck_pattern_line_trap_16_enabled);
        logedit_pattern_line_trap_16_segment_half_length->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_16_segment_half_length"));

        gridLayout_pattern_line_16->addWidget(logedit_pattern_line_trap_16_segment_half_length, 7, 2, 1, 1);

        label_pattern_line_16_glow = new QLabel(groupCheck_pattern_line_trap_16_enabled);
        label_pattern_line_16_glow->setObjectName(QString::fromUtf8("label_pattern_line_16_glow"));

        gridLayout_pattern_line_16->addWidget(label_pattern_line_16_glow, 8, 0, 1, 1);

        logedit_pattern_line_trap_16_glow_spread = new MyLineEdit(groupCheck_pattern_line_trap_16_enabled);
        logedit_pattern_line_trap_16_glow_spread->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_16_glow_spread"));

        gridLayout_pattern_line_16->addWidget(logedit_pattern_line_trap_16_glow_spread, 8, 1, 1, 1);

        comboBox_pattern_line_trap_16_falloff_profile = new MyComboBox(groupCheck_pattern_line_trap_16_enabled);
        comboBox_pattern_line_trap_16_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_16_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_16_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_16_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_16_falloff_profile->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_16_falloff_profile"));

        gridLayout_pattern_line_16->addWidget(comboBox_pattern_line_trap_16_falloff_profile, 8, 2, 1, 3);

        label_pattern_line_16_side = new QLabel(groupCheck_pattern_line_trap_16_enabled);
        label_pattern_line_16_side->setObjectName(QString::fromUtf8("label_pattern_line_16_side"));

        gridLayout_pattern_line_16->addWidget(label_pattern_line_16_side, 9, 0, 1, 1);

        comboBox_pattern_line_trap_16_edge_side = new MyComboBox(groupCheck_pattern_line_trap_16_enabled);
        comboBox_pattern_line_trap_16_edge_side->addItem(QString());
        comboBox_pattern_line_trap_16_edge_side->addItem(QString());
        comboBox_pattern_line_trap_16_edge_side->addItem(QString());
        comboBox_pattern_line_trap_16_edge_side->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_16_edge_side"));

        gridLayout_pattern_line_16->addWidget(comboBox_pattern_line_trap_16_edge_side, 9, 1, 1, 4);

        pushButton_pattern_line_trap_16_place_surface = new QPushButton(groupCheck_pattern_line_trap_16_enabled);
        pushButton_pattern_line_trap_16_place_surface->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_16_place_surface"));

        gridLayout_pattern_line_16->addWidget(pushButton_pattern_line_trap_16_place_surface, 10, 0, 1, 5);

        pushButton_pattern_line_trap_16_place_target = new QPushButton(groupCheck_pattern_line_trap_16_enabled);
        pushButton_pattern_line_trap_16_place_target->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_16_place_target"));

        gridLayout_pattern_line_16->addWidget(pushButton_pattern_line_trap_16_place_target, 11, 0, 1, 5);


        verticalLayout_pattern_line_traps_outer->addWidget(groupCheck_pattern_line_trap_16_enabled);

        groupCheck_pattern_line_trap_17_enabled = new MyGroupBox(groupBox_pattern_line_traps);
        groupCheck_pattern_line_trap_17_enabled->setObjectName(QString::fromUtf8("groupCheck_pattern_line_trap_17_enabled"));
        groupCheck_pattern_line_trap_17_enabled->setCheckable(true);
        gridLayout_pattern_line_17 = new QGridLayout(groupCheck_pattern_line_trap_17_enabled);
        gridLayout_pattern_line_17->setSpacing(2);
        gridLayout_pattern_line_17->setObjectName(QString::fromUtf8("gridLayout_pattern_line_17"));
        label_pattern_line_17_pos = new QLabel(groupCheck_pattern_line_trap_17_enabled);
        label_pattern_line_17_pos->setObjectName(QString::fromUtf8("label_pattern_line_17_pos"));

        gridLayout_pattern_line_17->addWidget(label_pattern_line_17_pos, 0, 0, 1, 1);

        vect3_pattern_line_trap_17_position_x = new MyLineEdit(groupCheck_pattern_line_trap_17_enabled);
        vect3_pattern_line_trap_17_position_x->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_17_position_x"));

        gridLayout_pattern_line_17->addWidget(vect3_pattern_line_trap_17_position_x, 0, 1, 1, 1);

        vect3_pattern_line_trap_17_position_y = new MyLineEdit(groupCheck_pattern_line_trap_17_enabled);
        vect3_pattern_line_trap_17_position_y->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_17_position_y"));

        gridLayout_pattern_line_17->addWidget(vect3_pattern_line_trap_17_position_y, 0, 2, 1, 1);

        vect3_pattern_line_trap_17_position_z = new MyLineEdit(groupCheck_pattern_line_trap_17_enabled);
        vect3_pattern_line_trap_17_position_z->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_17_position_z"));

        gridLayout_pattern_line_17->addWidget(vect3_pattern_line_trap_17_position_z, 0, 3, 1, 1);

        label_pattern_line_17_rot = new QLabel(groupCheck_pattern_line_trap_17_enabled);
        label_pattern_line_17_rot->setObjectName(QString::fromUtf8("label_pattern_line_17_rot"));

        gridLayout_pattern_line_17->addWidget(label_pattern_line_17_rot, 1, 0, 1, 1);

        spinboxd3_pattern_line_trap_17_rotation_x = new MyDoubleSpinBox(groupCheck_pattern_line_trap_17_enabled);
        spinboxd3_pattern_line_trap_17_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_17_rotation_x"));

        gridLayout_pattern_line_17->addWidget(spinboxd3_pattern_line_trap_17_rotation_x, 1, 1, 1, 1);

        spinboxd3_pattern_line_trap_17_rotation_y = new MyDoubleSpinBox(groupCheck_pattern_line_trap_17_enabled);
        spinboxd3_pattern_line_trap_17_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_17_rotation_y"));

        gridLayout_pattern_line_17->addWidget(spinboxd3_pattern_line_trap_17_rotation_y, 1, 2, 1, 1);

        spinboxd3_pattern_line_trap_17_rotation_z = new MyDoubleSpinBox(groupCheck_pattern_line_trap_17_enabled);
        spinboxd3_pattern_line_trap_17_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_17_rotation_z"));

        gridLayout_pattern_line_17->addWidget(spinboxd3_pattern_line_trap_17_rotation_z, 1, 3, 1, 1);

        label_pattern_line_17_radius = new QLabel(groupCheck_pattern_line_trap_17_enabled);
        label_pattern_line_17_radius->setObjectName(QString::fromUtf8("label_pattern_line_17_radius"));

        gridLayout_pattern_line_17->addWidget(label_pattern_line_17_radius, 2, 0, 1, 1);

        logedit_pattern_line_trap_17_radius = new MyLineEdit(groupCheck_pattern_line_trap_17_enabled);
        logedit_pattern_line_trap_17_radius->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_17_radius"));

        gridLayout_pattern_line_17->addWidget(logedit_pattern_line_trap_17_radius, 2, 1, 1, 1);

        logedit_pattern_line_trap_17_thickness = new MyLineEdit(groupCheck_pattern_line_trap_17_enabled);
        logedit_pattern_line_trap_17_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_17_thickness"));

        gridLayout_pattern_line_17->addWidget(logedit_pattern_line_trap_17_thickness, 2, 2, 1, 1);

        logedit_pattern_line_trap_17_edge_softness = new MyLineEdit(groupCheck_pattern_line_trap_17_enabled);
        logedit_pattern_line_trap_17_edge_softness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_17_edge_softness"));

        gridLayout_pattern_line_17->addWidget(logedit_pattern_line_trap_17_edge_softness, 2, 3, 1, 1);

        logedit_pattern_line_trap_17_max_distance = new MyLineEdit(groupCheck_pattern_line_trap_17_enabled);
        logedit_pattern_line_trap_17_max_distance->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_17_max_distance"));

        gridLayout_pattern_line_17->addWidget(logedit_pattern_line_trap_17_max_distance, 2, 4, 1, 1);

        label_pattern_line_17_scale = new QLabel(groupCheck_pattern_line_trap_17_enabled);
        label_pattern_line_17_scale->setObjectName(QString::fromUtf8("label_pattern_line_17_scale"));

        gridLayout_pattern_line_17->addWidget(label_pattern_line_17_scale, 3, 0, 1, 1);

        logedit_pattern_line_trap_17_scale = new MyLineEdit(groupCheck_pattern_line_trap_17_enabled);
        logedit_pattern_line_trap_17_scale->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_17_scale"));

        gridLayout_pattern_line_17->addWidget(logedit_pattern_line_trap_17_scale, 3, 1, 1, 1);

        logedit_pattern_line_trap_17_relative_thickness = new MyLineEdit(groupCheck_pattern_line_trap_17_enabled);
        logedit_pattern_line_trap_17_relative_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_17_relative_thickness"));

        gridLayout_pattern_line_17->addWidget(logedit_pattern_line_trap_17_relative_thickness, 3, 2, 1, 1);

        label_pattern_line_17_int = new QLabel(groupCheck_pattern_line_trap_17_enabled);
        label_pattern_line_17_int->setObjectName(QString::fromUtf8("label_pattern_line_17_int"));

        gridLayout_pattern_line_17->addWidget(label_pattern_line_17_int, 4, 0, 1, 1);

        logedit_pattern_line_trap_17_intensity = new MyLineEdit(groupCheck_pattern_line_trap_17_enabled);
        logedit_pattern_line_trap_17_intensity->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_17_intensity"));

        gridLayout_pattern_line_17->addWidget(logedit_pattern_line_trap_17_intensity, 4, 1, 1, 1);

        colorButton_pattern_line_trap_17_color = new MyColorButton(groupCheck_pattern_line_trap_17_enabled);
        colorButton_pattern_line_trap_17_color->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_17_color"));

        gridLayout_pattern_line_17->addWidget(colorButton_pattern_line_trap_17_color, 4, 2, 1, 1);

        colorButton_pattern_line_trap_17_color_2 = new MyColorButton(groupCheck_pattern_line_trap_17_enabled);
        colorButton_pattern_line_trap_17_color_2->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_17_color_2"));

        gridLayout_pattern_line_17->addWidget(colorButton_pattern_line_trap_17_color_2, 4, 3, 1, 1);

        colorButton_pattern_line_trap_17_color_3 = new MyColorButton(groupCheck_pattern_line_trap_17_enabled);
        colorButton_pattern_line_trap_17_color_3->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_17_color_3"));

        gridLayout_pattern_line_17->addWidget(colorButton_pattern_line_trap_17_color_3, 4, 4, 1, 1);

        label_pattern_line_17_shape = new QLabel(groupCheck_pattern_line_trap_17_enabled);
        label_pattern_line_17_shape->setObjectName(QString::fromUtf8("label_pattern_line_17_shape"));

        gridLayout_pattern_line_17->addWidget(label_pattern_line_17_shape, 5, 0, 1, 1);

        comboBox_pattern_line_trap_17_shape = new MyComboBox(groupCheck_pattern_line_trap_17_enabled);
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->addItem(QString());
        comboBox_pattern_line_trap_17_shape->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_17_shape"));

        gridLayout_pattern_line_17->addWidget(comboBox_pattern_line_trap_17_shape, 5, 1, 1, 4);

        label_pattern_line_17_shape_aux = new QLabel(groupCheck_pattern_line_trap_17_enabled);
        label_pattern_line_17_shape_aux->setObjectName(QString::fromUtf8("label_pattern_line_17_shape_aux"));

        gridLayout_pattern_line_17->addWidget(label_pattern_line_17_shape_aux, 6, 0, 1, 1);

        logedit_pattern_line_trap_17_shape_aux = new MyLineEdit(groupCheck_pattern_line_trap_17_enabled);
        logedit_pattern_line_trap_17_shape_aux->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_17_shape_aux"));

        gridLayout_pattern_line_17->addWidget(logedit_pattern_line_trap_17_shape_aux, 6, 1, 1, 2);

        label_pattern_line_17_sharp_seg = new QLabel(groupCheck_pattern_line_trap_17_enabled);
        label_pattern_line_17_sharp_seg->setObjectName(QString::fromUtf8("label_pattern_line_17_sharp_seg"));

        gridLayout_pattern_line_17->addWidget(label_pattern_line_17_sharp_seg, 7, 0, 1, 1);

        logedit_pattern_line_trap_17_falloff_sharpness = new MyLineEdit(groupCheck_pattern_line_trap_17_enabled);
        logedit_pattern_line_trap_17_falloff_sharpness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_17_falloff_sharpness"));

        gridLayout_pattern_line_17->addWidget(logedit_pattern_line_trap_17_falloff_sharpness, 7, 1, 1, 1);

        logedit_pattern_line_trap_17_segment_half_length = new MyLineEdit(groupCheck_pattern_line_trap_17_enabled);
        logedit_pattern_line_trap_17_segment_half_length->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_17_segment_half_length"));

        gridLayout_pattern_line_17->addWidget(logedit_pattern_line_trap_17_segment_half_length, 7, 2, 1, 1);

        label_pattern_line_17_glow = new QLabel(groupCheck_pattern_line_trap_17_enabled);
        label_pattern_line_17_glow->setObjectName(QString::fromUtf8("label_pattern_line_17_glow"));

        gridLayout_pattern_line_17->addWidget(label_pattern_line_17_glow, 8, 0, 1, 1);

        logedit_pattern_line_trap_17_glow_spread = new MyLineEdit(groupCheck_pattern_line_trap_17_enabled);
        logedit_pattern_line_trap_17_glow_spread->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_17_glow_spread"));

        gridLayout_pattern_line_17->addWidget(logedit_pattern_line_trap_17_glow_spread, 8, 1, 1, 1);

        comboBox_pattern_line_trap_17_falloff_profile = new MyComboBox(groupCheck_pattern_line_trap_17_enabled);
        comboBox_pattern_line_trap_17_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_17_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_17_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_17_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_17_falloff_profile->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_17_falloff_profile"));

        gridLayout_pattern_line_17->addWidget(comboBox_pattern_line_trap_17_falloff_profile, 8, 2, 1, 3);

        label_pattern_line_17_side = new QLabel(groupCheck_pattern_line_trap_17_enabled);
        label_pattern_line_17_side->setObjectName(QString::fromUtf8("label_pattern_line_17_side"));

        gridLayout_pattern_line_17->addWidget(label_pattern_line_17_side, 9, 0, 1, 1);

        comboBox_pattern_line_trap_17_edge_side = new MyComboBox(groupCheck_pattern_line_trap_17_enabled);
        comboBox_pattern_line_trap_17_edge_side->addItem(QString());
        comboBox_pattern_line_trap_17_edge_side->addItem(QString());
        comboBox_pattern_line_trap_17_edge_side->addItem(QString());
        comboBox_pattern_line_trap_17_edge_side->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_17_edge_side"));

        gridLayout_pattern_line_17->addWidget(comboBox_pattern_line_trap_17_edge_side, 9, 1, 1, 4);

        pushButton_pattern_line_trap_17_place_surface = new QPushButton(groupCheck_pattern_line_trap_17_enabled);
        pushButton_pattern_line_trap_17_place_surface->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_17_place_surface"));

        gridLayout_pattern_line_17->addWidget(pushButton_pattern_line_trap_17_place_surface, 10, 0, 1, 5);

        pushButton_pattern_line_trap_17_place_target = new QPushButton(groupCheck_pattern_line_trap_17_enabled);
        pushButton_pattern_line_trap_17_place_target->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_17_place_target"));

        gridLayout_pattern_line_17->addWidget(pushButton_pattern_line_trap_17_place_target, 11, 0, 1, 5);


        verticalLayout_pattern_line_traps_outer->addWidget(groupCheck_pattern_line_trap_17_enabled);

        groupCheck_pattern_line_trap_18_enabled = new MyGroupBox(groupBox_pattern_line_traps);
        groupCheck_pattern_line_trap_18_enabled->setObjectName(QString::fromUtf8("groupCheck_pattern_line_trap_18_enabled"));
        groupCheck_pattern_line_trap_18_enabled->setCheckable(true);
        gridLayout_pattern_line_18 = new QGridLayout(groupCheck_pattern_line_trap_18_enabled);
        gridLayout_pattern_line_18->setSpacing(2);
        gridLayout_pattern_line_18->setObjectName(QString::fromUtf8("gridLayout_pattern_line_18"));
        label_pattern_line_18_pos = new QLabel(groupCheck_pattern_line_trap_18_enabled);
        label_pattern_line_18_pos->setObjectName(QString::fromUtf8("label_pattern_line_18_pos"));

        gridLayout_pattern_line_18->addWidget(label_pattern_line_18_pos, 0, 0, 1, 1);

        vect3_pattern_line_trap_18_position_x = new MyLineEdit(groupCheck_pattern_line_trap_18_enabled);
        vect3_pattern_line_trap_18_position_x->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_18_position_x"));

        gridLayout_pattern_line_18->addWidget(vect3_pattern_line_trap_18_position_x, 0, 1, 1, 1);

        vect3_pattern_line_trap_18_position_y = new MyLineEdit(groupCheck_pattern_line_trap_18_enabled);
        vect3_pattern_line_trap_18_position_y->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_18_position_y"));

        gridLayout_pattern_line_18->addWidget(vect3_pattern_line_trap_18_position_y, 0, 2, 1, 1);

        vect3_pattern_line_trap_18_position_z = new MyLineEdit(groupCheck_pattern_line_trap_18_enabled);
        vect3_pattern_line_trap_18_position_z->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_18_position_z"));

        gridLayout_pattern_line_18->addWidget(vect3_pattern_line_trap_18_position_z, 0, 3, 1, 1);

        label_pattern_line_18_rot = new QLabel(groupCheck_pattern_line_trap_18_enabled);
        label_pattern_line_18_rot->setObjectName(QString::fromUtf8("label_pattern_line_18_rot"));

        gridLayout_pattern_line_18->addWidget(label_pattern_line_18_rot, 1, 0, 1, 1);

        spinboxd3_pattern_line_trap_18_rotation_x = new MyDoubleSpinBox(groupCheck_pattern_line_trap_18_enabled);
        spinboxd3_pattern_line_trap_18_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_18_rotation_x"));

        gridLayout_pattern_line_18->addWidget(spinboxd3_pattern_line_trap_18_rotation_x, 1, 1, 1, 1);

        spinboxd3_pattern_line_trap_18_rotation_y = new MyDoubleSpinBox(groupCheck_pattern_line_trap_18_enabled);
        spinboxd3_pattern_line_trap_18_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_18_rotation_y"));

        gridLayout_pattern_line_18->addWidget(spinboxd3_pattern_line_trap_18_rotation_y, 1, 2, 1, 1);

        spinboxd3_pattern_line_trap_18_rotation_z = new MyDoubleSpinBox(groupCheck_pattern_line_trap_18_enabled);
        spinboxd3_pattern_line_trap_18_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_18_rotation_z"));

        gridLayout_pattern_line_18->addWidget(spinboxd3_pattern_line_trap_18_rotation_z, 1, 3, 1, 1);

        label_pattern_line_18_radius = new QLabel(groupCheck_pattern_line_trap_18_enabled);
        label_pattern_line_18_radius->setObjectName(QString::fromUtf8("label_pattern_line_18_radius"));

        gridLayout_pattern_line_18->addWidget(label_pattern_line_18_radius, 2, 0, 1, 1);

        logedit_pattern_line_trap_18_radius = new MyLineEdit(groupCheck_pattern_line_trap_18_enabled);
        logedit_pattern_line_trap_18_radius->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_18_radius"));

        gridLayout_pattern_line_18->addWidget(logedit_pattern_line_trap_18_radius, 2, 1, 1, 1);

        logedit_pattern_line_trap_18_thickness = new MyLineEdit(groupCheck_pattern_line_trap_18_enabled);
        logedit_pattern_line_trap_18_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_18_thickness"));

        gridLayout_pattern_line_18->addWidget(logedit_pattern_line_trap_18_thickness, 2, 2, 1, 1);

        logedit_pattern_line_trap_18_edge_softness = new MyLineEdit(groupCheck_pattern_line_trap_18_enabled);
        logedit_pattern_line_trap_18_edge_softness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_18_edge_softness"));

        gridLayout_pattern_line_18->addWidget(logedit_pattern_line_trap_18_edge_softness, 2, 3, 1, 1);

        logedit_pattern_line_trap_18_max_distance = new MyLineEdit(groupCheck_pattern_line_trap_18_enabled);
        logedit_pattern_line_trap_18_max_distance->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_18_max_distance"));

        gridLayout_pattern_line_18->addWidget(logedit_pattern_line_trap_18_max_distance, 2, 4, 1, 1);

        label_pattern_line_18_scale = new QLabel(groupCheck_pattern_line_trap_18_enabled);
        label_pattern_line_18_scale->setObjectName(QString::fromUtf8("label_pattern_line_18_scale"));

        gridLayout_pattern_line_18->addWidget(label_pattern_line_18_scale, 3, 0, 1, 1);

        logedit_pattern_line_trap_18_scale = new MyLineEdit(groupCheck_pattern_line_trap_18_enabled);
        logedit_pattern_line_trap_18_scale->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_18_scale"));

        gridLayout_pattern_line_18->addWidget(logedit_pattern_line_trap_18_scale, 3, 1, 1, 1);

        logedit_pattern_line_trap_18_relative_thickness = new MyLineEdit(groupCheck_pattern_line_trap_18_enabled);
        logedit_pattern_line_trap_18_relative_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_18_relative_thickness"));

        gridLayout_pattern_line_18->addWidget(logedit_pattern_line_trap_18_relative_thickness, 3, 2, 1, 1);

        label_pattern_line_18_int = new QLabel(groupCheck_pattern_line_trap_18_enabled);
        label_pattern_line_18_int->setObjectName(QString::fromUtf8("label_pattern_line_18_int"));

        gridLayout_pattern_line_18->addWidget(label_pattern_line_18_int, 4, 0, 1, 1);

        logedit_pattern_line_trap_18_intensity = new MyLineEdit(groupCheck_pattern_line_trap_18_enabled);
        logedit_pattern_line_trap_18_intensity->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_18_intensity"));

        gridLayout_pattern_line_18->addWidget(logedit_pattern_line_trap_18_intensity, 4, 1, 1, 1);

        colorButton_pattern_line_trap_18_color = new MyColorButton(groupCheck_pattern_line_trap_18_enabled);
        colorButton_pattern_line_trap_18_color->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_18_color"));

        gridLayout_pattern_line_18->addWidget(colorButton_pattern_line_trap_18_color, 4, 2, 1, 1);

        colorButton_pattern_line_trap_18_color_2 = new MyColorButton(groupCheck_pattern_line_trap_18_enabled);
        colorButton_pattern_line_trap_18_color_2->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_18_color_2"));

        gridLayout_pattern_line_18->addWidget(colorButton_pattern_line_trap_18_color_2, 4, 3, 1, 1);

        colorButton_pattern_line_trap_18_color_3 = new MyColorButton(groupCheck_pattern_line_trap_18_enabled);
        colorButton_pattern_line_trap_18_color_3->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_18_color_3"));

        gridLayout_pattern_line_18->addWidget(colorButton_pattern_line_trap_18_color_3, 4, 4, 1, 1);

        label_pattern_line_18_shape = new QLabel(groupCheck_pattern_line_trap_18_enabled);
        label_pattern_line_18_shape->setObjectName(QString::fromUtf8("label_pattern_line_18_shape"));

        gridLayout_pattern_line_18->addWidget(label_pattern_line_18_shape, 5, 0, 1, 1);

        comboBox_pattern_line_trap_18_shape = new MyComboBox(groupCheck_pattern_line_trap_18_enabled);
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->addItem(QString());
        comboBox_pattern_line_trap_18_shape->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_18_shape"));

        gridLayout_pattern_line_18->addWidget(comboBox_pattern_line_trap_18_shape, 5, 1, 1, 4);

        label_pattern_line_18_shape_aux = new QLabel(groupCheck_pattern_line_trap_18_enabled);
        label_pattern_line_18_shape_aux->setObjectName(QString::fromUtf8("label_pattern_line_18_shape_aux"));

        gridLayout_pattern_line_18->addWidget(label_pattern_line_18_shape_aux, 6, 0, 1, 1);

        logedit_pattern_line_trap_18_shape_aux = new MyLineEdit(groupCheck_pattern_line_trap_18_enabled);
        logedit_pattern_line_trap_18_shape_aux->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_18_shape_aux"));

        gridLayout_pattern_line_18->addWidget(logedit_pattern_line_trap_18_shape_aux, 6, 1, 1, 2);

        label_pattern_line_18_sharp_seg = new QLabel(groupCheck_pattern_line_trap_18_enabled);
        label_pattern_line_18_sharp_seg->setObjectName(QString::fromUtf8("label_pattern_line_18_sharp_seg"));

        gridLayout_pattern_line_18->addWidget(label_pattern_line_18_sharp_seg, 7, 0, 1, 1);

        logedit_pattern_line_trap_18_falloff_sharpness = new MyLineEdit(groupCheck_pattern_line_trap_18_enabled);
        logedit_pattern_line_trap_18_falloff_sharpness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_18_falloff_sharpness"));

        gridLayout_pattern_line_18->addWidget(logedit_pattern_line_trap_18_falloff_sharpness, 7, 1, 1, 1);

        logedit_pattern_line_trap_18_segment_half_length = new MyLineEdit(groupCheck_pattern_line_trap_18_enabled);
        logedit_pattern_line_trap_18_segment_half_length->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_18_segment_half_length"));

        gridLayout_pattern_line_18->addWidget(logedit_pattern_line_trap_18_segment_half_length, 7, 2, 1, 1);

        label_pattern_line_18_glow = new QLabel(groupCheck_pattern_line_trap_18_enabled);
        label_pattern_line_18_glow->setObjectName(QString::fromUtf8("label_pattern_line_18_glow"));

        gridLayout_pattern_line_18->addWidget(label_pattern_line_18_glow, 8, 0, 1, 1);

        logedit_pattern_line_trap_18_glow_spread = new MyLineEdit(groupCheck_pattern_line_trap_18_enabled);
        logedit_pattern_line_trap_18_glow_spread->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_18_glow_spread"));

        gridLayout_pattern_line_18->addWidget(logedit_pattern_line_trap_18_glow_spread, 8, 1, 1, 1);

        comboBox_pattern_line_trap_18_falloff_profile = new MyComboBox(groupCheck_pattern_line_trap_18_enabled);
        comboBox_pattern_line_trap_18_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_18_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_18_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_18_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_18_falloff_profile->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_18_falloff_profile"));

        gridLayout_pattern_line_18->addWidget(comboBox_pattern_line_trap_18_falloff_profile, 8, 2, 1, 3);

        label_pattern_line_18_side = new QLabel(groupCheck_pattern_line_trap_18_enabled);
        label_pattern_line_18_side->setObjectName(QString::fromUtf8("label_pattern_line_18_side"));

        gridLayout_pattern_line_18->addWidget(label_pattern_line_18_side, 9, 0, 1, 1);

        comboBox_pattern_line_trap_18_edge_side = new MyComboBox(groupCheck_pattern_line_trap_18_enabled);
        comboBox_pattern_line_trap_18_edge_side->addItem(QString());
        comboBox_pattern_line_trap_18_edge_side->addItem(QString());
        comboBox_pattern_line_trap_18_edge_side->addItem(QString());
        comboBox_pattern_line_trap_18_edge_side->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_18_edge_side"));

        gridLayout_pattern_line_18->addWidget(comboBox_pattern_line_trap_18_edge_side, 9, 1, 1, 4);

        pushButton_pattern_line_trap_18_place_surface = new QPushButton(groupCheck_pattern_line_trap_18_enabled);
        pushButton_pattern_line_trap_18_place_surface->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_18_place_surface"));

        gridLayout_pattern_line_18->addWidget(pushButton_pattern_line_trap_18_place_surface, 10, 0, 1, 5);

        pushButton_pattern_line_trap_18_place_target = new QPushButton(groupCheck_pattern_line_trap_18_enabled);
        pushButton_pattern_line_trap_18_place_target->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_18_place_target"));

        gridLayout_pattern_line_18->addWidget(pushButton_pattern_line_trap_18_place_target, 11, 0, 1, 5);


        verticalLayout_pattern_line_traps_outer->addWidget(groupCheck_pattern_line_trap_18_enabled);

        groupCheck_pattern_line_trap_19_enabled = new MyGroupBox(groupBox_pattern_line_traps);
        groupCheck_pattern_line_trap_19_enabled->setObjectName(QString::fromUtf8("groupCheck_pattern_line_trap_19_enabled"));
        groupCheck_pattern_line_trap_19_enabled->setCheckable(true);
        gridLayout_pattern_line_19 = new QGridLayout(groupCheck_pattern_line_trap_19_enabled);
        gridLayout_pattern_line_19->setSpacing(2);
        gridLayout_pattern_line_19->setObjectName(QString::fromUtf8("gridLayout_pattern_line_19"));
        label_pattern_line_19_pos = new QLabel(groupCheck_pattern_line_trap_19_enabled);
        label_pattern_line_19_pos->setObjectName(QString::fromUtf8("label_pattern_line_19_pos"));

        gridLayout_pattern_line_19->addWidget(label_pattern_line_19_pos, 0, 0, 1, 1);

        vect3_pattern_line_trap_19_position_x = new MyLineEdit(groupCheck_pattern_line_trap_19_enabled);
        vect3_pattern_line_trap_19_position_x->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_19_position_x"));

        gridLayout_pattern_line_19->addWidget(vect3_pattern_line_trap_19_position_x, 0, 1, 1, 1);

        vect3_pattern_line_trap_19_position_y = new MyLineEdit(groupCheck_pattern_line_trap_19_enabled);
        vect3_pattern_line_trap_19_position_y->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_19_position_y"));

        gridLayout_pattern_line_19->addWidget(vect3_pattern_line_trap_19_position_y, 0, 2, 1, 1);

        vect3_pattern_line_trap_19_position_z = new MyLineEdit(groupCheck_pattern_line_trap_19_enabled);
        vect3_pattern_line_trap_19_position_z->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_19_position_z"));

        gridLayout_pattern_line_19->addWidget(vect3_pattern_line_trap_19_position_z, 0, 3, 1, 1);

        label_pattern_line_19_rot = new QLabel(groupCheck_pattern_line_trap_19_enabled);
        label_pattern_line_19_rot->setObjectName(QString::fromUtf8("label_pattern_line_19_rot"));

        gridLayout_pattern_line_19->addWidget(label_pattern_line_19_rot, 1, 0, 1, 1);

        spinboxd3_pattern_line_trap_19_rotation_x = new MyDoubleSpinBox(groupCheck_pattern_line_trap_19_enabled);
        spinboxd3_pattern_line_trap_19_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_19_rotation_x"));

        gridLayout_pattern_line_19->addWidget(spinboxd3_pattern_line_trap_19_rotation_x, 1, 1, 1, 1);

        spinboxd3_pattern_line_trap_19_rotation_y = new MyDoubleSpinBox(groupCheck_pattern_line_trap_19_enabled);
        spinboxd3_pattern_line_trap_19_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_19_rotation_y"));

        gridLayout_pattern_line_19->addWidget(spinboxd3_pattern_line_trap_19_rotation_y, 1, 2, 1, 1);

        spinboxd3_pattern_line_trap_19_rotation_z = new MyDoubleSpinBox(groupCheck_pattern_line_trap_19_enabled);
        spinboxd3_pattern_line_trap_19_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_19_rotation_z"));

        gridLayout_pattern_line_19->addWidget(spinboxd3_pattern_line_trap_19_rotation_z, 1, 3, 1, 1);

        label_pattern_line_19_radius = new QLabel(groupCheck_pattern_line_trap_19_enabled);
        label_pattern_line_19_radius->setObjectName(QString::fromUtf8("label_pattern_line_19_radius"));

        gridLayout_pattern_line_19->addWidget(label_pattern_line_19_radius, 2, 0, 1, 1);

        logedit_pattern_line_trap_19_radius = new MyLineEdit(groupCheck_pattern_line_trap_19_enabled);
        logedit_pattern_line_trap_19_radius->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_19_radius"));

        gridLayout_pattern_line_19->addWidget(logedit_pattern_line_trap_19_radius, 2, 1, 1, 1);

        logedit_pattern_line_trap_19_thickness = new MyLineEdit(groupCheck_pattern_line_trap_19_enabled);
        logedit_pattern_line_trap_19_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_19_thickness"));

        gridLayout_pattern_line_19->addWidget(logedit_pattern_line_trap_19_thickness, 2, 2, 1, 1);

        logedit_pattern_line_trap_19_edge_softness = new MyLineEdit(groupCheck_pattern_line_trap_19_enabled);
        logedit_pattern_line_trap_19_edge_softness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_19_edge_softness"));

        gridLayout_pattern_line_19->addWidget(logedit_pattern_line_trap_19_edge_softness, 2, 3, 1, 1);

        logedit_pattern_line_trap_19_max_distance = new MyLineEdit(groupCheck_pattern_line_trap_19_enabled);
        logedit_pattern_line_trap_19_max_distance->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_19_max_distance"));

        gridLayout_pattern_line_19->addWidget(logedit_pattern_line_trap_19_max_distance, 2, 4, 1, 1);

        label_pattern_line_19_scale = new QLabel(groupCheck_pattern_line_trap_19_enabled);
        label_pattern_line_19_scale->setObjectName(QString::fromUtf8("label_pattern_line_19_scale"));

        gridLayout_pattern_line_19->addWidget(label_pattern_line_19_scale, 3, 0, 1, 1);

        logedit_pattern_line_trap_19_scale = new MyLineEdit(groupCheck_pattern_line_trap_19_enabled);
        logedit_pattern_line_trap_19_scale->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_19_scale"));

        gridLayout_pattern_line_19->addWidget(logedit_pattern_line_trap_19_scale, 3, 1, 1, 1);

        logedit_pattern_line_trap_19_relative_thickness = new MyLineEdit(groupCheck_pattern_line_trap_19_enabled);
        logedit_pattern_line_trap_19_relative_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_19_relative_thickness"));

        gridLayout_pattern_line_19->addWidget(logedit_pattern_line_trap_19_relative_thickness, 3, 2, 1, 1);

        label_pattern_line_19_int = new QLabel(groupCheck_pattern_line_trap_19_enabled);
        label_pattern_line_19_int->setObjectName(QString::fromUtf8("label_pattern_line_19_int"));

        gridLayout_pattern_line_19->addWidget(label_pattern_line_19_int, 4, 0, 1, 1);

        logedit_pattern_line_trap_19_intensity = new MyLineEdit(groupCheck_pattern_line_trap_19_enabled);
        logedit_pattern_line_trap_19_intensity->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_19_intensity"));

        gridLayout_pattern_line_19->addWidget(logedit_pattern_line_trap_19_intensity, 4, 1, 1, 1);

        colorButton_pattern_line_trap_19_color = new MyColorButton(groupCheck_pattern_line_trap_19_enabled);
        colorButton_pattern_line_trap_19_color->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_19_color"));

        gridLayout_pattern_line_19->addWidget(colorButton_pattern_line_trap_19_color, 4, 2, 1, 1);

        colorButton_pattern_line_trap_19_color_2 = new MyColorButton(groupCheck_pattern_line_trap_19_enabled);
        colorButton_pattern_line_trap_19_color_2->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_19_color_2"));

        gridLayout_pattern_line_19->addWidget(colorButton_pattern_line_trap_19_color_2, 4, 3, 1, 1);

        colorButton_pattern_line_trap_19_color_3 = new MyColorButton(groupCheck_pattern_line_trap_19_enabled);
        colorButton_pattern_line_trap_19_color_3->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_19_color_3"));

        gridLayout_pattern_line_19->addWidget(colorButton_pattern_line_trap_19_color_3, 4, 4, 1, 1);

        label_pattern_line_19_shape = new QLabel(groupCheck_pattern_line_trap_19_enabled);
        label_pattern_line_19_shape->setObjectName(QString::fromUtf8("label_pattern_line_19_shape"));

        gridLayout_pattern_line_19->addWidget(label_pattern_line_19_shape, 5, 0, 1, 1);

        comboBox_pattern_line_trap_19_shape = new MyComboBox(groupCheck_pattern_line_trap_19_enabled);
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->addItem(QString());
        comboBox_pattern_line_trap_19_shape->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_19_shape"));

        gridLayout_pattern_line_19->addWidget(comboBox_pattern_line_trap_19_shape, 5, 1, 1, 4);

        label_pattern_line_19_shape_aux = new QLabel(groupCheck_pattern_line_trap_19_enabled);
        label_pattern_line_19_shape_aux->setObjectName(QString::fromUtf8("label_pattern_line_19_shape_aux"));

        gridLayout_pattern_line_19->addWidget(label_pattern_line_19_shape_aux, 6, 0, 1, 1);

        logedit_pattern_line_trap_19_shape_aux = new MyLineEdit(groupCheck_pattern_line_trap_19_enabled);
        logedit_pattern_line_trap_19_shape_aux->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_19_shape_aux"));

        gridLayout_pattern_line_19->addWidget(logedit_pattern_line_trap_19_shape_aux, 6, 1, 1, 2);

        label_pattern_line_19_sharp_seg = new QLabel(groupCheck_pattern_line_trap_19_enabled);
        label_pattern_line_19_sharp_seg->setObjectName(QString::fromUtf8("label_pattern_line_19_sharp_seg"));

        gridLayout_pattern_line_19->addWidget(label_pattern_line_19_sharp_seg, 7, 0, 1, 1);

        logedit_pattern_line_trap_19_falloff_sharpness = new MyLineEdit(groupCheck_pattern_line_trap_19_enabled);
        logedit_pattern_line_trap_19_falloff_sharpness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_19_falloff_sharpness"));

        gridLayout_pattern_line_19->addWidget(logedit_pattern_line_trap_19_falloff_sharpness, 7, 1, 1, 1);

        logedit_pattern_line_trap_19_segment_half_length = new MyLineEdit(groupCheck_pattern_line_trap_19_enabled);
        logedit_pattern_line_trap_19_segment_half_length->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_19_segment_half_length"));

        gridLayout_pattern_line_19->addWidget(logedit_pattern_line_trap_19_segment_half_length, 7, 2, 1, 1);

        label_pattern_line_19_glow = new QLabel(groupCheck_pattern_line_trap_19_enabled);
        label_pattern_line_19_glow->setObjectName(QString::fromUtf8("label_pattern_line_19_glow"));

        gridLayout_pattern_line_19->addWidget(label_pattern_line_19_glow, 8, 0, 1, 1);

        logedit_pattern_line_trap_19_glow_spread = new MyLineEdit(groupCheck_pattern_line_trap_19_enabled);
        logedit_pattern_line_trap_19_glow_spread->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_19_glow_spread"));

        gridLayout_pattern_line_19->addWidget(logedit_pattern_line_trap_19_glow_spread, 8, 1, 1, 1);

        comboBox_pattern_line_trap_19_falloff_profile = new MyComboBox(groupCheck_pattern_line_trap_19_enabled);
        comboBox_pattern_line_trap_19_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_19_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_19_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_19_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_19_falloff_profile->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_19_falloff_profile"));

        gridLayout_pattern_line_19->addWidget(comboBox_pattern_line_trap_19_falloff_profile, 8, 2, 1, 3);

        label_pattern_line_19_side = new QLabel(groupCheck_pattern_line_trap_19_enabled);
        label_pattern_line_19_side->setObjectName(QString::fromUtf8("label_pattern_line_19_side"));

        gridLayout_pattern_line_19->addWidget(label_pattern_line_19_side, 9, 0, 1, 1);

        comboBox_pattern_line_trap_19_edge_side = new MyComboBox(groupCheck_pattern_line_trap_19_enabled);
        comboBox_pattern_line_trap_19_edge_side->addItem(QString());
        comboBox_pattern_line_trap_19_edge_side->addItem(QString());
        comboBox_pattern_line_trap_19_edge_side->addItem(QString());
        comboBox_pattern_line_trap_19_edge_side->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_19_edge_side"));

        gridLayout_pattern_line_19->addWidget(comboBox_pattern_line_trap_19_edge_side, 9, 1, 1, 4);

        pushButton_pattern_line_trap_19_place_surface = new QPushButton(groupCheck_pattern_line_trap_19_enabled);
        pushButton_pattern_line_trap_19_place_surface->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_19_place_surface"));

        gridLayout_pattern_line_19->addWidget(pushButton_pattern_line_trap_19_place_surface, 10, 0, 1, 5);

        pushButton_pattern_line_trap_19_place_target = new QPushButton(groupCheck_pattern_line_trap_19_enabled);
        pushButton_pattern_line_trap_19_place_target->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_19_place_target"));

        gridLayout_pattern_line_19->addWidget(pushButton_pattern_line_trap_19_place_target, 11, 0, 1, 5);


        verticalLayout_pattern_line_traps_outer->addWidget(groupCheck_pattern_line_trap_19_enabled);

        groupCheck_pattern_line_trap_20_enabled = new MyGroupBox(groupBox_pattern_line_traps);
        groupCheck_pattern_line_trap_20_enabled->setObjectName(QString::fromUtf8("groupCheck_pattern_line_trap_20_enabled"));
        groupCheck_pattern_line_trap_20_enabled->setCheckable(true);
        gridLayout_pattern_line_20 = new QGridLayout(groupCheck_pattern_line_trap_20_enabled);
        gridLayout_pattern_line_20->setSpacing(2);
        gridLayout_pattern_line_20->setObjectName(QString::fromUtf8("gridLayout_pattern_line_20"));
        label_pattern_line_20_pos = new QLabel(groupCheck_pattern_line_trap_20_enabled);
        label_pattern_line_20_pos->setObjectName(QString::fromUtf8("label_pattern_line_20_pos"));

        gridLayout_pattern_line_20->addWidget(label_pattern_line_20_pos, 0, 0, 1, 1);

        vect3_pattern_line_trap_20_position_x = new MyLineEdit(groupCheck_pattern_line_trap_20_enabled);
        vect3_pattern_line_trap_20_position_x->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_20_position_x"));

        gridLayout_pattern_line_20->addWidget(vect3_pattern_line_trap_20_position_x, 0, 1, 1, 1);

        vect3_pattern_line_trap_20_position_y = new MyLineEdit(groupCheck_pattern_line_trap_20_enabled);
        vect3_pattern_line_trap_20_position_y->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_20_position_y"));

        gridLayout_pattern_line_20->addWidget(vect3_pattern_line_trap_20_position_y, 0, 2, 1, 1);

        vect3_pattern_line_trap_20_position_z = new MyLineEdit(groupCheck_pattern_line_trap_20_enabled);
        vect3_pattern_line_trap_20_position_z->setObjectName(QString::fromUtf8("vect3_pattern_line_trap_20_position_z"));

        gridLayout_pattern_line_20->addWidget(vect3_pattern_line_trap_20_position_z, 0, 3, 1, 1);

        label_pattern_line_20_rot = new QLabel(groupCheck_pattern_line_trap_20_enabled);
        label_pattern_line_20_rot->setObjectName(QString::fromUtf8("label_pattern_line_20_rot"));

        gridLayout_pattern_line_20->addWidget(label_pattern_line_20_rot, 1, 0, 1, 1);

        spinboxd3_pattern_line_trap_20_rotation_x = new MyDoubleSpinBox(groupCheck_pattern_line_trap_20_enabled);
        spinboxd3_pattern_line_trap_20_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_20_rotation_x"));

        gridLayout_pattern_line_20->addWidget(spinboxd3_pattern_line_trap_20_rotation_x, 1, 1, 1, 1);

        spinboxd3_pattern_line_trap_20_rotation_y = new MyDoubleSpinBox(groupCheck_pattern_line_trap_20_enabled);
        spinboxd3_pattern_line_trap_20_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_20_rotation_y"));

        gridLayout_pattern_line_20->addWidget(spinboxd3_pattern_line_trap_20_rotation_y, 1, 2, 1, 1);

        spinboxd3_pattern_line_trap_20_rotation_z = new MyDoubleSpinBox(groupCheck_pattern_line_trap_20_enabled);
        spinboxd3_pattern_line_trap_20_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_pattern_line_trap_20_rotation_z"));

        gridLayout_pattern_line_20->addWidget(spinboxd3_pattern_line_trap_20_rotation_z, 1, 3, 1, 1);

        label_pattern_line_20_radius = new QLabel(groupCheck_pattern_line_trap_20_enabled);
        label_pattern_line_20_radius->setObjectName(QString::fromUtf8("label_pattern_line_20_radius"));

        gridLayout_pattern_line_20->addWidget(label_pattern_line_20_radius, 2, 0, 1, 1);

        logedit_pattern_line_trap_20_radius = new MyLineEdit(groupCheck_pattern_line_trap_20_enabled);
        logedit_pattern_line_trap_20_radius->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_20_radius"));

        gridLayout_pattern_line_20->addWidget(logedit_pattern_line_trap_20_radius, 2, 1, 1, 1);

        logedit_pattern_line_trap_20_thickness = new MyLineEdit(groupCheck_pattern_line_trap_20_enabled);
        logedit_pattern_line_trap_20_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_20_thickness"));

        gridLayout_pattern_line_20->addWidget(logedit_pattern_line_trap_20_thickness, 2, 2, 1, 1);

        logedit_pattern_line_trap_20_edge_softness = new MyLineEdit(groupCheck_pattern_line_trap_20_enabled);
        logedit_pattern_line_trap_20_edge_softness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_20_edge_softness"));

        gridLayout_pattern_line_20->addWidget(logedit_pattern_line_trap_20_edge_softness, 2, 3, 1, 1);

        logedit_pattern_line_trap_20_max_distance = new MyLineEdit(groupCheck_pattern_line_trap_20_enabled);
        logedit_pattern_line_trap_20_max_distance->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_20_max_distance"));

        gridLayout_pattern_line_20->addWidget(logedit_pattern_line_trap_20_max_distance, 2, 4, 1, 1);

        label_pattern_line_20_scale = new QLabel(groupCheck_pattern_line_trap_20_enabled);
        label_pattern_line_20_scale->setObjectName(QString::fromUtf8("label_pattern_line_20_scale"));

        gridLayout_pattern_line_20->addWidget(label_pattern_line_20_scale, 3, 0, 1, 1);

        logedit_pattern_line_trap_20_scale = new MyLineEdit(groupCheck_pattern_line_trap_20_enabled);
        logedit_pattern_line_trap_20_scale->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_20_scale"));

        gridLayout_pattern_line_20->addWidget(logedit_pattern_line_trap_20_scale, 3, 1, 1, 1);

        logedit_pattern_line_trap_20_relative_thickness = new MyLineEdit(groupCheck_pattern_line_trap_20_enabled);
        logedit_pattern_line_trap_20_relative_thickness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_20_relative_thickness"));

        gridLayout_pattern_line_20->addWidget(logedit_pattern_line_trap_20_relative_thickness, 3, 2, 1, 1);

        label_pattern_line_20_int = new QLabel(groupCheck_pattern_line_trap_20_enabled);
        label_pattern_line_20_int->setObjectName(QString::fromUtf8("label_pattern_line_20_int"));

        gridLayout_pattern_line_20->addWidget(label_pattern_line_20_int, 4, 0, 1, 1);

        logedit_pattern_line_trap_20_intensity = new MyLineEdit(groupCheck_pattern_line_trap_20_enabled);
        logedit_pattern_line_trap_20_intensity->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_20_intensity"));

        gridLayout_pattern_line_20->addWidget(logedit_pattern_line_trap_20_intensity, 4, 1, 1, 1);

        colorButton_pattern_line_trap_20_color = new MyColorButton(groupCheck_pattern_line_trap_20_enabled);
        colorButton_pattern_line_trap_20_color->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_20_color"));

        gridLayout_pattern_line_20->addWidget(colorButton_pattern_line_trap_20_color, 4, 2, 1, 1);

        colorButton_pattern_line_trap_20_color_2 = new MyColorButton(groupCheck_pattern_line_trap_20_enabled);
        colorButton_pattern_line_trap_20_color_2->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_20_color_2"));

        gridLayout_pattern_line_20->addWidget(colorButton_pattern_line_trap_20_color_2, 4, 3, 1, 1);

        colorButton_pattern_line_trap_20_color_3 = new MyColorButton(groupCheck_pattern_line_trap_20_enabled);
        colorButton_pattern_line_trap_20_color_3->setObjectName(QString::fromUtf8("colorButton_pattern_line_trap_20_color_3"));

        gridLayout_pattern_line_20->addWidget(colorButton_pattern_line_trap_20_color_3, 4, 4, 1, 1);

        label_pattern_line_20_shape = new QLabel(groupCheck_pattern_line_trap_20_enabled);
        label_pattern_line_20_shape->setObjectName(QString::fromUtf8("label_pattern_line_20_shape"));

        gridLayout_pattern_line_20->addWidget(label_pattern_line_20_shape, 5, 0, 1, 1);

        comboBox_pattern_line_trap_20_shape = new MyComboBox(groupCheck_pattern_line_trap_20_enabled);
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->addItem(QString());
        comboBox_pattern_line_trap_20_shape->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_20_shape"));

        gridLayout_pattern_line_20->addWidget(comboBox_pattern_line_trap_20_shape, 5, 1, 1, 4);

        label_pattern_line_20_shape_aux = new QLabel(groupCheck_pattern_line_trap_20_enabled);
        label_pattern_line_20_shape_aux->setObjectName(QString::fromUtf8("label_pattern_line_20_shape_aux"));

        gridLayout_pattern_line_20->addWidget(label_pattern_line_20_shape_aux, 6, 0, 1, 1);

        logedit_pattern_line_trap_20_shape_aux = new MyLineEdit(groupCheck_pattern_line_trap_20_enabled);
        logedit_pattern_line_trap_20_shape_aux->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_20_shape_aux"));

        gridLayout_pattern_line_20->addWidget(logedit_pattern_line_trap_20_shape_aux, 6, 1, 1, 2);

        label_pattern_line_20_sharp_seg = new QLabel(groupCheck_pattern_line_trap_20_enabled);
        label_pattern_line_20_sharp_seg->setObjectName(QString::fromUtf8("label_pattern_line_20_sharp_seg"));

        gridLayout_pattern_line_20->addWidget(label_pattern_line_20_sharp_seg, 7, 0, 1, 1);

        logedit_pattern_line_trap_20_falloff_sharpness = new MyLineEdit(groupCheck_pattern_line_trap_20_enabled);
        logedit_pattern_line_trap_20_falloff_sharpness->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_20_falloff_sharpness"));

        gridLayout_pattern_line_20->addWidget(logedit_pattern_line_trap_20_falloff_sharpness, 7, 1, 1, 1);

        logedit_pattern_line_trap_20_segment_half_length = new MyLineEdit(groupCheck_pattern_line_trap_20_enabled);
        logedit_pattern_line_trap_20_segment_half_length->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_20_segment_half_length"));

        gridLayout_pattern_line_20->addWidget(logedit_pattern_line_trap_20_segment_half_length, 7, 2, 1, 1);

        label_pattern_line_20_glow = new QLabel(groupCheck_pattern_line_trap_20_enabled);
        label_pattern_line_20_glow->setObjectName(QString::fromUtf8("label_pattern_line_20_glow"));

        gridLayout_pattern_line_20->addWidget(label_pattern_line_20_glow, 8, 0, 1, 1);

        logedit_pattern_line_trap_20_glow_spread = new MyLineEdit(groupCheck_pattern_line_trap_20_enabled);
        logedit_pattern_line_trap_20_glow_spread->setObjectName(QString::fromUtf8("logedit_pattern_line_trap_20_glow_spread"));

        gridLayout_pattern_line_20->addWidget(logedit_pattern_line_trap_20_glow_spread, 8, 1, 1, 1);

        comboBox_pattern_line_trap_20_falloff_profile = new MyComboBox(groupCheck_pattern_line_trap_20_enabled);
        comboBox_pattern_line_trap_20_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_20_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_20_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_20_falloff_profile->addItem(QString());
        comboBox_pattern_line_trap_20_falloff_profile->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_20_falloff_profile"));

        gridLayout_pattern_line_20->addWidget(comboBox_pattern_line_trap_20_falloff_profile, 8, 2, 1, 3);

        label_pattern_line_20_side = new QLabel(groupCheck_pattern_line_trap_20_enabled);
        label_pattern_line_20_side->setObjectName(QString::fromUtf8("label_pattern_line_20_side"));

        gridLayout_pattern_line_20->addWidget(label_pattern_line_20_side, 9, 0, 1, 1);

        comboBox_pattern_line_trap_20_edge_side = new MyComboBox(groupCheck_pattern_line_trap_20_enabled);
        comboBox_pattern_line_trap_20_edge_side->addItem(QString());
        comboBox_pattern_line_trap_20_edge_side->addItem(QString());
        comboBox_pattern_line_trap_20_edge_side->addItem(QString());
        comboBox_pattern_line_trap_20_edge_side->setObjectName(QString::fromUtf8("comboBox_pattern_line_trap_20_edge_side"));

        gridLayout_pattern_line_20->addWidget(comboBox_pattern_line_trap_20_edge_side, 9, 1, 1, 4);

        pushButton_pattern_line_trap_20_place_surface = new QPushButton(groupCheck_pattern_line_trap_20_enabled);
        pushButton_pattern_line_trap_20_place_surface->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_20_place_surface"));

        gridLayout_pattern_line_20->addWidget(pushButton_pattern_line_trap_20_place_surface, 10, 0, 1, 5);

        pushButton_pattern_line_trap_20_place_target = new QPushButton(groupCheck_pattern_line_trap_20_enabled);
        pushButton_pattern_line_trap_20_place_target->setObjectName(QString::fromUtf8("pushButton_pattern_line_trap_20_place_target"));

        gridLayout_pattern_line_20->addWidget(pushButton_pattern_line_trap_20_place_target, 11, 0, 1, 5);


        verticalLayout_pattern_line_traps_outer->addWidget(groupCheck_pattern_line_trap_20_enabled);


        verticalLayout_pattern_traps_dock_top->addWidget(groupBox_pattern_line_traps);

        scrollArea_pattern_line_traps_top->setWidget(scrollAreaWidgetContents_pattern_traps_top);

        verticalLayout_pattern_traps_panel_root->addWidget(scrollArea_pattern_line_traps_top);


        retranslateUi(cPatternLinesTrapsPanel);

        comboBox_pattern_line_precision_mode->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(cPatternLinesTrapsPanel);
    } // setupUi

    void retranslateUi(QWidget *cPatternLinesTrapsPanel)
    {
#if QT_CONFIG(tooltip)
        groupBox_pattern_line_traps->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Accents als gloeiende lijnen in de wereld: positioneer per laag, kies profielvorm, stel in hoe hard en breed de gloed is. Werkstroom: (1) Zet boven de master aan; (2) per laag: positie/rotatie, straal, dikte, schaal, profiel + eventueel profiel extra; (3) solo alleen ter debug; (4) opslaan/laden met presets. CPU en OpenCL volgen dezelfde 50 vormen.", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_pattern_line_traps->setTitle(QCoreApplication::translate("cPatternLinesTrapsPanel", "Patroon-lijnen (20 lagen, wereldruimte)", nullptr));
        checkBox_pattern_line_traps_enabled->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Patroon-lijnen aanzetten (master)", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_pattern_line_traps_enabled->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schakelt alle patroon-lijnen in de shader. Uit = geen effect; per laag apart aan/uit.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_pattern_line_traps_overlay_visible->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Overlay tonen in render (preview)", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_pattern_line_traps_overlay_visible->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Tekent lijn en middenpunt van elke actieve patroonlijn als overlay op de render, zodat u ze kunt zien voordat het beeld klaar is.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_pattern_line_traps_enable_all->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Alles aan", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_pattern_line_traps_enable_all->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Zet alle 20 lagen aan (master blijft ongewijzigd).", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_pattern_line_traps_disable_all->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Alles uit", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_pattern_line_traps_disable_all->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Zet alle 20 lagen uit.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_pattern_line_traps_solo_selected->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Solo geselecteerd", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_pattern_line_traps_solo_selected->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Zet alle lagen uit behalve de geselecteerde (spinbox Exacte laag).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_traps_combine_mode->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Combineren", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_traps_combine_mode->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Hoe meerdere lagen samengaan: optellen (additief) of maximum per kleurkanaal.", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_traps_combine_mode->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Optellen (additief)", nullptr));
        comboBox_pattern_line_traps_combine_mode->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Maximum per kanaal", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_pattern_line_traps_combine_mode->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Optellen: lagen tellen op (meer gloed). Maximum: sterkste per R/G/B (harde overgangen).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_traps_coloring_mode->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Kleuring", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_traps_coloring_mode->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Waar de gradient-t (0\342\200\2231) vandaan komt: geometrische muurafstand, fractal orbit-trap (colorIndex), of aantal iteraties.", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_traps_coloring_mode->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Geometrisch (muurafstand)", nullptr));
        comboBox_pattern_line_traps_coloring_mode->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Orbit-trap (kleurindex)", nullptr));
        comboBox_pattern_line_traps_coloring_mode->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Iteraties (aantal)", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_pattern_line_traps_coloring_mode->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Geometrisch: verloopt over de muurafstand. Orbit-trap: gebruikt fractal colorIndex. Iteraties: gebruikt aantal iteraties / N.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_traps_coloring_speed->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Kleur-snelheid", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_traps_coloring_speed->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Hoe snel de palette-kleur verloopt over de orbit-trap of iteraties. 1 = standaard; hoger = meer kleurvariatie.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_pattern_line_traps_coloring_speed->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Multiplicator op de orbit-trap/iteratie-waarde voor de palette-positie.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_traps_palette_offset->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Palette-offset", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_traps_palette_offset->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Verschuiving van de palette-start (0\342\200\2231). Handig om de basiskleur te verplaatsen zonder snelheid te wijzigen.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_pattern_line_traps_palette_offset->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Faseverschuiving van de palette; 0 = begin, 0.5 = midden, etc.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_traps_global_intensity->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Globale intensiteit", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_traps_global_intensity->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Master multiplier voor de gloed-intensiteit van ALLE lagen. 1.0 = ongewijzigd; 0.5 = half zo fel; 2.0 = dubbel zo fel.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_pattern_line_traps_global_intensity->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Master multiplier voor alle lagen tegelijk.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_traps_global_max_distance->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Globale max. afstand", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_traps_global_max_distance->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Als > 0, beperkt de gloed-afstand van ALLE lagen tot deze waarde. 0 = per laag eigen waarde gebruiken.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_pattern_line_traps_global_max_distance->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "0 = uit (per-laag waarde); >0 = cap voor alle lagen.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_traps_global_scale->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Globale schaal", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_traps_global_scale->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Uniforme schaal voor alle profielen. 1.0 = ongewijzigd; >1 = dikker; <1 = dunner.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_pattern_line_traps_global_scale->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Vermenigvuldigt de straal van alle lagen.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_traps_global_relative_thickness->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Globale rel. dikte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_traps_global_relative_thickness->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Master multiplier voor de gloedband-dikte van ALLE lagen. 1.0 = ongewijzigd; hoger = bredere band.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_pattern_line_traps_global_relative_thickness->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Vermenigvuldigt de effectieve banddikte van alle lagen.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        groupBox_pattern_line_trap_workflow->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Presets: bewaar/laad alleen de patroonlijnparameters (liefst naammatig in je bestandenmap). Solo: 0 = alle lagen, 1\342\200\22320 = isoleer die laag. Kopi\303\253ren: snel de instellingen van ene laag naar de andere (handig voor 2\342\200\2233 varianten).", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_pattern_line_trap_workflow->setTitle(QCoreApplication::translate("cPatternLinesTrapsPanel", "Preset, solo, kopi\303\253ren", nullptr));
        label_pattern_line_trap_solo_layer->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Solo laag (0 = uit)", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_trap_solo_layer->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "0: alle actieve lagen in de render. 1\342\200\22320: toon uitsluitend die ene lijn (snellere feedback bij tunen van \303\251\303\251n profiel).", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinboxInt_pattern_line_trap_solo_layer->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "0 = alle lagen; anders enkel geselecteerde laag (1\342\200\22320).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_trap_presets->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Preset", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_trap_presets->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Opgeslagen combinaties van alle patroonlijn-velden. Vernieuwen leest de map; Laden past toe; Save As vraagt een naam en slaat direct op.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_pattern_line_trap_preset_refresh->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Vernieuwen", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_pattern_line_trap_preset_refresh->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scant de preset-map opnieuw en vult de keuzelijst; gebruik na het toevoegen van handmatige .ini/.json bestanden.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_pattern_line_trap_preset_load->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Laden", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_pattern_line_trap_preset_load->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Laat de geselecteerde preset in alle patroonlijn-velden (inclusief alle 20 lagen) gelden.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_pattern_line_trap_preset_save->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Save As\342\200\246", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_pattern_line_trap_preset_save->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Sla huidige patroonlijn-instellingen op als preset. Je typt alleen een naam; de preset wordt direct in de preset-map bewaard.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_trap_copy->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Kopieer laag", nullptr));
        label_pattern_line_trap_copy_arrow->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "\342\206\222", nullptr));
        pushButton_pattern_line_trap_copy_layer->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Kopi\303\253ren", nullptr));
        groupBox_pattern_line_exact_placement->setTitle(QCoreApplication::translate("cPatternLinesTrapsPanel", "Exacte plaatsing (camera + Z-buffer)", nullptr));
#if QT_CONFIG(tooltip)
        groupBox_pattern_line_exact_placement->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Zelfde methode als \302\253Place light\302\273 in Mandelbulber: diepte uit de render, viewvector met FOV en camerarotatie, optioneel een stukje v\303\263\303\263r/achter het oppervlak. Vereist een afgerende preview of beeld (Z-buffer).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_exact_intro->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Kies de laag en zet de groene knop op AAN. Oppervlak: klik in de render, of zonder muis: focus op het beeld, dan Enter of Spatie = midden beeld, [ en ] = offset, of: ingedrukt houden en verticaal slepen in het beeld (offset verandert direct). (t.o.v. oppervlak, zelfde idee als Alt+wiel in Effects). Zet de knop uit of een andere muisactie om te stoppen.", nullptr));
        label_pattern_line_precision_mode->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaatsing", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_precision_mode->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Offset/effect: zoals voorheen (~10% scene vanaf camera, zachte verschuiving). Nauwkeurig: midden van het pixel + bilineaire Z, handmatige afstand 0 \342\200\224 dichter op waar u klikt.", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_precision_mode->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Offset / effect (zoals eerder)", nullptr));
        comboBox_pattern_line_precision_mode->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Nauwkeurig (midden pixel + Z)", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_pattern_line_precision_mode->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Offset/effect: zoals voorheen. Nauwkeurig: subpixel-ray + Z voor strakkere plaatsing op de klik.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_exact_layer->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Laag", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_pattern_line_exact_layer->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Welke patroonlijn (1\342\200\22320) krijgt de nieuwe positie bij de volgende klik in het beeld.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_pattern_line_exact_activate->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Exacte klik-plaatsing (AAN / UIT)", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_pattern_line_exact_activate->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "AAN: zelfde pipeline als hulplicht, groene knop. Klik in de render, of Enter/Spatie = midden; [ en ] of verticaal slepen in het beeld = offset. UIT: \302\253geen\302\273 of knop. Offset: Effects, Alt+scroll, of [ ]. (Hulplicht: Alt+sleep wijzigt offset, sleep zonder Alt verplaatst het licht.)", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_pattern_line_placement_offset_xyz->setTitle(QCoreApplication::translate("cPatternLinesTrapsPanel", "Extra positie X / Y / Z (wereld)", nullptr));
#if QT_CONFIG(tooltip)
        groupBox_pattern_line_placement_offset_xyz->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Verschuiving in wereldruimte die na de klik-positie (en na de handmatige z-afstand uit Effects) wordt opgeteld. Hetzelfde als in Effects \342\200\224 Light placement options.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_pl_offset_x->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "X", nullptr));
#if QT_CONFIG(tooltip)
        vect3_aux_light_manual_placement_offset_x->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Extra X in wereldco\303\266rdinaten (zelfde parameter als in Effects/dock hulplicht).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_pl_offset_y->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Y", nullptr));
#if QT_CONFIG(tooltip)
        vect3_aux_light_manual_placement_offset_y->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Extra Y in wereldco\303\266rdinaten.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_pl_offset_z->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Z", nullptr));
#if QT_CONFIG(tooltip)
        vect3_aux_light_manual_placement_offset_z->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Extra Z in wereldco\303\266rdinaten.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_exact_footer->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Offset t.o.v. het oppervlak: handmatige afstand (Effects \342\200\224 Light placement) en eventueel X/Y/Z hierboven. Toetsen [ en ] of verticaal slepen op het beeld. Hulplicht: Alt+sleep = afstand. Achter de fractal: zelfde \302\253place behind\302\273 als bij lichten. Knoppen \302\253op oppervlak / doelpunt\302\273 hieronder: snelle middenas \342\200\224 voor testen.", nullptr));
        label_pattern_line_traps_hint->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "As langs lokale X. Positie = midden/ankerpunt; rotatie draait het YZ-profiel. Straal: typische afmeting van de vorm in de dwarssectie. Dikte + relatieve dikte: hoe smal de lichtband; lagere Dikte = dunnere lijn. Schaal: vergroot/verkleint het hele YZ-profiel. Profiel: kies \303\251\303\251n van 50 vormen (0\342\200\22349); Profiel extra: per vorm (ovaal, ring, tandwiel, fraktalen, \342\200\246). Gloed: Scherpe rand / spreiding + falloff-profiel; Zichtbare kant = omtrek, alleen buiten, of alleen binnen. Fractal-afstand (Mandelbrot, Julia, multibrot, tricorn, Julia\302\263, \342\200\246): speel met Straal en Profiel extra (iteraties, c, varianten). Lijn/poly (Koch, draak, Hilbert, Levy, Lissajous, H-boom, \342\200\246): vaak fijn: lagere Dikte, iets hogere Schaal, en beperk eventueel het segment. Hover over de velden in elke laag voor korte tooltips.", nullptr));
        pushButton_pattern_line_traps_quick_test->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Snel test: patroon aan, L1 zichtbaar op doelpunt", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_pattern_line_traps_quick_test->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Zet sterke standaardwaarden en leg lijn 1 nabij het camera-doelpunt.", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_pattern_line_trap_1_enabled->setTitle(QCoreApplication::translate("cPatternLinesTrapsPanel", "Lijn 1", nullptr));
        label_pattern_line_1_pos->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Positie", nullptr));
        label_pattern_line_1_rot->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Rot \302\260", nullptr));
        label_pattern_line_1_radius->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal / dikte / rand / max", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_1_radius->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal = profielgrootte. Dikte = schaal van de SDF-band. Rand = afronding hoeken. Max = afstand-limiet voor de gloed (0 = uit in praktijk volgens instelling).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_1_scale->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal / rel. dikte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_1_scale->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal: uniform het dwarsprofiel (YZ). Relatieve dikte: factor op de gloedband t.o.v. Dikte (1 = standaard).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_1_int->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Intensiteit / 3 kleuren", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_1_int->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gradient langs de gloed: kern (kleur 1) \342\206\222 midden (2) \342\206\222 rand (3). Zelfde RGB = effen.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_1_shape->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_1_shape->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Dwarsdoorsnede loodrecht op de as (lokale X).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_1_shape->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Buis (rond)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lint (vlak)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ruit", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(4, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(5, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zeshoek", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(6, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(7, QCoreApplication::translate("cPatternLinesTrapsPanel", "Achthoek", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(8, QCoreApplication::translate("cPatternLinesTrapsPanel", "Squircle", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(9, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(10, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vijfhoek", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(11, QCoreApplication::translate("cPatternLinesTrapsPanel", "Rechthoek", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(12, QCoreApplication::translate("cPatternLinesTrapsPanel", "Capsule", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(13, QCoreApplication::translate("cPatternLinesTrapsPanel", "Driehoek", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(14, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-5 (roos)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(15, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tienhoek", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(16, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=3", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(17, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=6", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(18, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sikkel", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(19, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(20, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(21, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski driehoek", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(22, QCoreApplication::translate("cPatternLinesTrapsPanel", "Koch (1 iter)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(23, QCoreApplication::translate("cPatternLinesTrapsPanel", "Mandelbrot (afstand)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(24, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia (afstand)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(25, QCoreApplication::translate("cPatternLinesTrapsPanel", "Burning ship", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(26, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cantor-achtig", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(27, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pythagoras boom", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(28, QCoreApplication::translate("cPatternLinesTrapsPanel", "Draak (polylijn)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(29, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hilbert (orde 1)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(30, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vicsek (5 blokken)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(31, QCoreApplication::translate("cPatternLinesTrapsPanel", "Griekse kruis", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(32, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(33, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\264 (afstand)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(34, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tricorn (afstand)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(35, QCoreApplication::translate("cPatternLinesTrapsPanel", "3-ary boom (Y)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(36, QCoreApplication::translate("cPatternLinesTrapsPanel", "Peano-achtig (8\303\227)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(37, QCoreApplication::translate("cPatternLinesTrapsPanel", "Levy C (1 iter)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(38, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-Cantor", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(39, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gouden L-vorm", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(40, QCoreApplication::translate("cPatternLinesTrapsPanel", "3 cirkels (Apollonius)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(41, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lissajous 2:3", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(42, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(43, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\265 (afstand)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(44, QCoreApplication::translate("cPatternLinesTrapsPanel", "H-boom (1 iter)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(45, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt (2 niv.)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(46, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zes-lob rimpel", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(47, QCoreApplication::translate("cPatternLinesTrapsPanel", "Binaire boom (2 niv.)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(48, QCoreApplication::translate("cPatternLinesTrapsPanel", "Fermat-spiraal", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(49, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dubbel kruis", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(50, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hendecagon (11-hoek)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(51, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dodecagon (12-hoek)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(52, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tetradecagon (14-hoek)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(53, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hexadecagon (16-hoek)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(54, QCoreApplication::translate("cPatternLinesTrapsPanel", "Icosagon (20-hoek)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(55, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-6 (hexagram)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(56, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-7", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(57, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-8", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(58, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-9", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(59, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-10", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(60, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-12", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(61, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-16", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(62, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-3", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(63, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-4", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(64, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-6", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(65, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-7", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(66, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-8", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(67, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-10", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(68, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-12", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(69, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-16", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(70, QCoreApplication::translate("cPatternLinesTrapsPanel", "Heptagon (7-hoek)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(71, QCoreApplication::translate("cPatternLinesTrapsPanel", "Enneagon (9-hoek)", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(72, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-6", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(73, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-8", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(74, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-10", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(75, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-12", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(76, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-16", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(77, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-20", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(78, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hart", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(79, QCoreApplication::translate("cPatternLinesTrapsPanel", "Infinity", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(80, QCoreApplication::translate("cPatternLinesTrapsPanel", "Druppel", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(81, QCoreApplication::translate("cPatternLinesTrapsPanel", "Oog", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(82, QCoreApplication::translate("cPatternLinesTrapsPanel", "Maan", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(83, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pijl", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(84, QCoreApplication::translate("cPatternLinesTrapsPanel", "Bliksem", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(85, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sinus-golf", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(86, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zaagtand", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(87, QCoreApplication::translate("cPatternLinesTrapsPanel", "Block-golf", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(88, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 60\302\260", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(89, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 90\302\260", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(90, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 120\302\260", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(91, QCoreApplication::translate("cPatternLinesTrapsPanel", "Halve cirkel", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(92, QCoreApplication::translate("cPatternLinesTrapsPanel", "Taartpunt", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(93, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis met bol", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(94, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-kruis", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(95, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant met kruis", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(96, QCoreApplication::translate("cPatternLinesTrapsPanel", "Target", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(97, QCoreApplication::translate("cPatternLinesTrapsPanel", "Genestelde vierkanten", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(98, QCoreApplication::translate("cPatternLinesTrapsPanel", "Meander", nullptr));
        comboBox_pattern_line_trap_1_shape->setItemText(99, QCoreApplication::translate("cPatternLinesTrapsPanel", "Spiraal", nullptr));

        label_pattern_line_1_shape_aux->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel extra", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_1_shape_aux->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal: Z-straal t.o.v. Y (1 = cirkel). Ring: halve dikte van de buis.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_1_sharp_seg->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte / lengte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_1_sharp_seg->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte: sterkere piek (hoger = smallere gloed). Lengte: halve lijnlengte langs X (0 = oneindig). Zie ook \302\253Gloed / rand\302\273.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_1_glow->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloed / rand", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_1_glow->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloedbreedte: hoger = zachtere, bredere rand. Falloff: Gauss, smoothstep, lineair, exponentieel \342\200\224 bepaalt hoe snel het uitsterft (los van de 3-kleur-gradient).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_1_falloff_profile->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gauss (zacht)", nullptr));
        comboBox_pattern_line_trap_1_falloff_profile->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Strak (smooth)", nullptr));
        comboBox_pattern_line_trap_1_falloff_profile->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hard (lineair)", nullptr));
        comboBox_pattern_line_trap_1_falloff_profile->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Exponentieel", nullptr));

        label_pattern_line_1_side->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Zichtbare kant", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_1_side->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek: gloed aan beide zijden van de vorm (klassiek). Alleen buiten of binnen: \303\251\303\251n zijde van het oppervlak \342\200\224 handig om alleen de silhouet-rand te tonen.", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_1_edge_side->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek (beide)", nullptr));
        comboBox_pattern_line_trap_1_edge_side->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen buiten", nullptr));
        comboBox_pattern_line_trap_1_edge_side->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen binnen", nullptr));

        pushButton_pattern_line_trap_1_place_surface->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op oppervlak (zichtlijn)", nullptr));
        pushButton_pattern_line_trap_1_place_target->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op doelpunt", nullptr));
        groupCheck_pattern_line_trap_2_enabled->setTitle(QCoreApplication::translate("cPatternLinesTrapsPanel", "Lijn 2", nullptr));
        label_pattern_line_2_pos->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Positie", nullptr));
        label_pattern_line_2_rot->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Rot \302\260", nullptr));
        label_pattern_line_2_radius->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal / dikte / rand / max", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_2_radius->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal = profielgrootte. Dikte = schaal van de SDF-band. Rand = afronding hoeken. Max = afstand-limiet voor de gloed (0 = uit in praktijk volgens instelling).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_2_scale->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal / rel. dikte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_2_scale->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal: uniform het dwarsprofiel (YZ). Relatieve dikte: factor op de gloedband t.o.v. Dikte (1 = standaard).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_2_int->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Intensiteit / 3 kleuren", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_2_int->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gradient langs de gloed: kern (kleur 1) \342\206\222 midden (2) \342\206\222 rand (3). Zelfde RGB = effen.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_2_shape->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_2_shape->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Dwarsdoorsnede loodrecht op de as (lokale X).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_2_shape->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Buis (rond)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lint (vlak)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ruit", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(4, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(5, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zeshoek", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(6, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(7, QCoreApplication::translate("cPatternLinesTrapsPanel", "Achthoek", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(8, QCoreApplication::translate("cPatternLinesTrapsPanel", "Squircle", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(9, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(10, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vijfhoek", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(11, QCoreApplication::translate("cPatternLinesTrapsPanel", "Rechthoek", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(12, QCoreApplication::translate("cPatternLinesTrapsPanel", "Capsule", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(13, QCoreApplication::translate("cPatternLinesTrapsPanel", "Driehoek", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(14, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-5 (roos)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(15, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tienhoek", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(16, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=3", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(17, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=6", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(18, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sikkel", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(19, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(20, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(21, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski driehoek", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(22, QCoreApplication::translate("cPatternLinesTrapsPanel", "Koch (1 iter)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(23, QCoreApplication::translate("cPatternLinesTrapsPanel", "Mandelbrot (afstand)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(24, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia (afstand)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(25, QCoreApplication::translate("cPatternLinesTrapsPanel", "Burning ship", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(26, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cantor-achtig", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(27, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pythagoras boom", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(28, QCoreApplication::translate("cPatternLinesTrapsPanel", "Draak (polylijn)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(29, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hilbert (orde 1)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(30, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vicsek (5 blokken)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(31, QCoreApplication::translate("cPatternLinesTrapsPanel", "Griekse kruis", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(32, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(33, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\264 (afstand)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(34, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tricorn (afstand)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(35, QCoreApplication::translate("cPatternLinesTrapsPanel", "3-ary boom (Y)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(36, QCoreApplication::translate("cPatternLinesTrapsPanel", "Peano-achtig (8\303\227)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(37, QCoreApplication::translate("cPatternLinesTrapsPanel", "Levy C (1 iter)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(38, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-Cantor", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(39, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gouden L-vorm", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(40, QCoreApplication::translate("cPatternLinesTrapsPanel", "3 cirkels (Apollonius)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(41, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lissajous 2:3", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(42, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(43, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\265 (afstand)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(44, QCoreApplication::translate("cPatternLinesTrapsPanel", "H-boom (1 iter)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(45, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt (2 niv.)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(46, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zes-lob rimpel", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(47, QCoreApplication::translate("cPatternLinesTrapsPanel", "Binaire boom (2 niv.)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(48, QCoreApplication::translate("cPatternLinesTrapsPanel", "Fermat-spiraal", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(49, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dubbel kruis", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(50, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hendecagon (11-hoek)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(51, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dodecagon (12-hoek)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(52, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tetradecagon (14-hoek)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(53, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hexadecagon (16-hoek)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(54, QCoreApplication::translate("cPatternLinesTrapsPanel", "Icosagon (20-hoek)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(55, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-6 (hexagram)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(56, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-7", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(57, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-8", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(58, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-9", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(59, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-10", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(60, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-12", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(61, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-16", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(62, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-3", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(63, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-4", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(64, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-6", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(65, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-7", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(66, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-8", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(67, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-10", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(68, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-12", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(69, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-16", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(70, QCoreApplication::translate("cPatternLinesTrapsPanel", "Heptagon (7-hoek)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(71, QCoreApplication::translate("cPatternLinesTrapsPanel", "Enneagon (9-hoek)", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(72, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-6", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(73, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-8", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(74, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-10", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(75, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-12", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(76, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-16", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(77, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-20", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(78, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hart", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(79, QCoreApplication::translate("cPatternLinesTrapsPanel", "Infinity", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(80, QCoreApplication::translate("cPatternLinesTrapsPanel", "Druppel", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(81, QCoreApplication::translate("cPatternLinesTrapsPanel", "Oog", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(82, QCoreApplication::translate("cPatternLinesTrapsPanel", "Maan", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(83, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pijl", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(84, QCoreApplication::translate("cPatternLinesTrapsPanel", "Bliksem", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(85, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sinus-golf", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(86, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zaagtand", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(87, QCoreApplication::translate("cPatternLinesTrapsPanel", "Block-golf", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(88, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 60\302\260", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(89, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 90\302\260", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(90, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 120\302\260", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(91, QCoreApplication::translate("cPatternLinesTrapsPanel", "Halve cirkel", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(92, QCoreApplication::translate("cPatternLinesTrapsPanel", "Taartpunt", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(93, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis met bol", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(94, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-kruis", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(95, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant met kruis", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(96, QCoreApplication::translate("cPatternLinesTrapsPanel", "Target", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(97, QCoreApplication::translate("cPatternLinesTrapsPanel", "Genestelde vierkanten", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(98, QCoreApplication::translate("cPatternLinesTrapsPanel", "Meander", nullptr));
        comboBox_pattern_line_trap_2_shape->setItemText(99, QCoreApplication::translate("cPatternLinesTrapsPanel", "Spiraal", nullptr));

        label_pattern_line_2_shape_aux->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel extra", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_2_shape_aux->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal: Z-straal t.o.v. Y (1 = cirkel). Ring: halve dikte van de buis.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_2_sharp_seg->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte / lengte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_2_sharp_seg->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte: sterkere piek (hoger = smallere gloed). Lengte: halve lijnlengte langs X (0 = oneindig). Zie ook \302\253Gloed / rand\302\273.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_2_glow->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloed / rand", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_2_glow->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloedbreedte: hoger = zachtere, bredere rand. Falloff: Gauss, smoothstep, lineair, exponentieel \342\200\224 bepaalt hoe snel het uitsterft (los van de 3-kleur-gradient).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_2_falloff_profile->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gauss (zacht)", nullptr));
        comboBox_pattern_line_trap_2_falloff_profile->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Strak (smooth)", nullptr));
        comboBox_pattern_line_trap_2_falloff_profile->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hard (lineair)", nullptr));
        comboBox_pattern_line_trap_2_falloff_profile->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Exponentieel", nullptr));

        label_pattern_line_2_side->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Zichtbare kant", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_2_side->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek: gloed aan beide zijden van de vorm (klassiek). Alleen buiten of binnen: \303\251\303\251n zijde van het oppervlak \342\200\224 handig om alleen de silhouet-rand te tonen.", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_2_edge_side->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek (beide)", nullptr));
        comboBox_pattern_line_trap_2_edge_side->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen buiten", nullptr));
        comboBox_pattern_line_trap_2_edge_side->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen binnen", nullptr));

        pushButton_pattern_line_trap_2_place_surface->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op oppervlak (zichtlijn)", nullptr));
        pushButton_pattern_line_trap_2_place_target->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op doelpunt", nullptr));
        groupCheck_pattern_line_trap_3_enabled->setTitle(QCoreApplication::translate("cPatternLinesTrapsPanel", "Lijn 3", nullptr));
        label_pattern_line_3_pos->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Positie", nullptr));
        label_pattern_line_3_rot->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Rot \302\260", nullptr));
        label_pattern_line_3_radius->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal / dikte / rand / max", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_3_radius->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal = profielgrootte. Dikte = schaal van de SDF-band. Rand = afronding hoeken. Max = afstand-limiet voor de gloed (0 = uit in praktijk volgens instelling).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_3_scale->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal / rel. dikte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_3_scale->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal: uniform het dwarsprofiel (YZ). Relatieve dikte: factor op de gloedband t.o.v. Dikte (1 = standaard).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_3_int->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Intensiteit / 3 kleuren", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_3_int->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gradient langs de gloed: kern (kleur 1) \342\206\222 midden (2) \342\206\222 rand (3). Zelfde RGB = effen.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_3_shape->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_3_shape->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Dwarsdoorsnede loodrecht op de as (lokale X).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_3_shape->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Buis (rond)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lint (vlak)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ruit", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(4, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(5, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zeshoek", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(6, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(7, QCoreApplication::translate("cPatternLinesTrapsPanel", "Achthoek", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(8, QCoreApplication::translate("cPatternLinesTrapsPanel", "Squircle", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(9, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(10, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vijfhoek", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(11, QCoreApplication::translate("cPatternLinesTrapsPanel", "Rechthoek", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(12, QCoreApplication::translate("cPatternLinesTrapsPanel", "Capsule", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(13, QCoreApplication::translate("cPatternLinesTrapsPanel", "Driehoek", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(14, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-5 (roos)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(15, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tienhoek", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(16, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=3", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(17, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=6", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(18, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sikkel", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(19, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(20, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(21, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski driehoek", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(22, QCoreApplication::translate("cPatternLinesTrapsPanel", "Koch (1 iter)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(23, QCoreApplication::translate("cPatternLinesTrapsPanel", "Mandelbrot (afstand)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(24, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia (afstand)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(25, QCoreApplication::translate("cPatternLinesTrapsPanel", "Burning ship", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(26, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cantor-achtig", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(27, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pythagoras boom", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(28, QCoreApplication::translate("cPatternLinesTrapsPanel", "Draak (polylijn)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(29, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hilbert (orde 1)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(30, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vicsek (5 blokken)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(31, QCoreApplication::translate("cPatternLinesTrapsPanel", "Griekse kruis", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(32, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(33, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\264 (afstand)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(34, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tricorn (afstand)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(35, QCoreApplication::translate("cPatternLinesTrapsPanel", "3-ary boom (Y)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(36, QCoreApplication::translate("cPatternLinesTrapsPanel", "Peano-achtig (8\303\227)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(37, QCoreApplication::translate("cPatternLinesTrapsPanel", "Levy C (1 iter)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(38, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-Cantor", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(39, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gouden L-vorm", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(40, QCoreApplication::translate("cPatternLinesTrapsPanel", "3 cirkels (Apollonius)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(41, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lissajous 2:3", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(42, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(43, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\265 (afstand)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(44, QCoreApplication::translate("cPatternLinesTrapsPanel", "H-boom (1 iter)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(45, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt (2 niv.)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(46, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zes-lob rimpel", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(47, QCoreApplication::translate("cPatternLinesTrapsPanel", "Binaire boom (2 niv.)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(48, QCoreApplication::translate("cPatternLinesTrapsPanel", "Fermat-spiraal", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(49, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dubbel kruis", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(50, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hendecagon (11-hoek)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(51, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dodecagon (12-hoek)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(52, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tetradecagon (14-hoek)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(53, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hexadecagon (16-hoek)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(54, QCoreApplication::translate("cPatternLinesTrapsPanel", "Icosagon (20-hoek)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(55, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-6 (hexagram)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(56, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-7", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(57, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-8", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(58, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-9", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(59, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-10", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(60, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-12", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(61, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-16", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(62, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-3", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(63, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-4", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(64, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-6", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(65, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-7", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(66, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-8", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(67, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-10", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(68, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-12", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(69, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-16", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(70, QCoreApplication::translate("cPatternLinesTrapsPanel", "Heptagon (7-hoek)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(71, QCoreApplication::translate("cPatternLinesTrapsPanel", "Enneagon (9-hoek)", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(72, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-6", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(73, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-8", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(74, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-10", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(75, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-12", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(76, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-16", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(77, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-20", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(78, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hart", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(79, QCoreApplication::translate("cPatternLinesTrapsPanel", "Infinity", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(80, QCoreApplication::translate("cPatternLinesTrapsPanel", "Druppel", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(81, QCoreApplication::translate("cPatternLinesTrapsPanel", "Oog", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(82, QCoreApplication::translate("cPatternLinesTrapsPanel", "Maan", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(83, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pijl", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(84, QCoreApplication::translate("cPatternLinesTrapsPanel", "Bliksem", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(85, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sinus-golf", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(86, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zaagtand", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(87, QCoreApplication::translate("cPatternLinesTrapsPanel", "Block-golf", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(88, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 60\302\260", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(89, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 90\302\260", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(90, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 120\302\260", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(91, QCoreApplication::translate("cPatternLinesTrapsPanel", "Halve cirkel", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(92, QCoreApplication::translate("cPatternLinesTrapsPanel", "Taartpunt", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(93, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis met bol", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(94, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-kruis", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(95, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant met kruis", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(96, QCoreApplication::translate("cPatternLinesTrapsPanel", "Target", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(97, QCoreApplication::translate("cPatternLinesTrapsPanel", "Genestelde vierkanten", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(98, QCoreApplication::translate("cPatternLinesTrapsPanel", "Meander", nullptr));
        comboBox_pattern_line_trap_3_shape->setItemText(99, QCoreApplication::translate("cPatternLinesTrapsPanel", "Spiraal", nullptr));

        label_pattern_line_3_shape_aux->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel extra", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_3_shape_aux->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal: Z-straal t.o.v. Y (1 = cirkel). Ring: halve dikte van de buis.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_3_sharp_seg->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte / lengte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_3_sharp_seg->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte: sterkere piek (hoger = smallere gloed). Lengte: halve lijnlengte langs X (0 = oneindig). Zie ook \302\253Gloed / rand\302\273.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_3_glow->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloed / rand", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_3_glow->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloedbreedte: hoger = zachtere, bredere rand. Falloff: Gauss, smoothstep, lineair, exponentieel \342\200\224 bepaalt hoe snel het uitsterft (los van de 3-kleur-gradient).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_3_falloff_profile->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gauss (zacht)", nullptr));
        comboBox_pattern_line_trap_3_falloff_profile->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Strak (smooth)", nullptr));
        comboBox_pattern_line_trap_3_falloff_profile->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hard (lineair)", nullptr));
        comboBox_pattern_line_trap_3_falloff_profile->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Exponentieel", nullptr));

        label_pattern_line_3_side->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Zichtbare kant", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_3_side->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek: gloed aan beide zijden van de vorm (klassiek). Alleen buiten of binnen: \303\251\303\251n zijde van het oppervlak \342\200\224 handig om alleen de silhouet-rand te tonen.", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_3_edge_side->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek (beide)", nullptr));
        comboBox_pattern_line_trap_3_edge_side->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen buiten", nullptr));
        comboBox_pattern_line_trap_3_edge_side->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen binnen", nullptr));

        pushButton_pattern_line_trap_3_place_surface->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op oppervlak (zichtlijn)", nullptr));
        pushButton_pattern_line_trap_3_place_target->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op doelpunt", nullptr));
        groupCheck_pattern_line_trap_4_enabled->setTitle(QCoreApplication::translate("cPatternLinesTrapsPanel", "Lijn 4", nullptr));
        label_pattern_line_4_pos->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Positie", nullptr));
        label_pattern_line_4_rot->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Rot \302\260", nullptr));
        label_pattern_line_4_radius->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal / dikte / rand / max", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_4_radius->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal = profielgrootte. Dikte = schaal van de SDF-band. Rand = afronding hoeken. Max = afstand-limiet voor de gloed (0 = uit in praktijk volgens instelling).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_4_scale->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal / rel. dikte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_4_scale->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal: uniform het dwarsprofiel (YZ). Relatieve dikte: factor op de gloedband t.o.v. Dikte (1 = standaard).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_4_int->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Intensiteit / 3 kleuren", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_4_int->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gradient langs de gloed: kern (kleur 1) \342\206\222 midden (2) \342\206\222 rand (3). Zelfde RGB = effen.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_4_shape->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_4_shape->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Dwarsdoorsnede loodrecht op de as (lokale X).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_4_shape->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Buis (rond)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lint (vlak)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ruit", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(4, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(5, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zeshoek", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(6, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(7, QCoreApplication::translate("cPatternLinesTrapsPanel", "Achthoek", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(8, QCoreApplication::translate("cPatternLinesTrapsPanel", "Squircle", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(9, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(10, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vijfhoek", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(11, QCoreApplication::translate("cPatternLinesTrapsPanel", "Rechthoek", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(12, QCoreApplication::translate("cPatternLinesTrapsPanel", "Capsule", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(13, QCoreApplication::translate("cPatternLinesTrapsPanel", "Driehoek", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(14, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-5 (roos)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(15, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tienhoek", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(16, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=3", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(17, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=6", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(18, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sikkel", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(19, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(20, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(21, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski driehoek", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(22, QCoreApplication::translate("cPatternLinesTrapsPanel", "Koch (1 iter)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(23, QCoreApplication::translate("cPatternLinesTrapsPanel", "Mandelbrot (afstand)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(24, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia (afstand)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(25, QCoreApplication::translate("cPatternLinesTrapsPanel", "Burning ship", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(26, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cantor-achtig", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(27, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pythagoras boom", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(28, QCoreApplication::translate("cPatternLinesTrapsPanel", "Draak (polylijn)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(29, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hilbert (orde 1)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(30, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vicsek (5 blokken)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(31, QCoreApplication::translate("cPatternLinesTrapsPanel", "Griekse kruis", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(32, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(33, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\264 (afstand)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(34, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tricorn (afstand)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(35, QCoreApplication::translate("cPatternLinesTrapsPanel", "3-ary boom (Y)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(36, QCoreApplication::translate("cPatternLinesTrapsPanel", "Peano-achtig (8\303\227)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(37, QCoreApplication::translate("cPatternLinesTrapsPanel", "Levy C (1 iter)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(38, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-Cantor", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(39, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gouden L-vorm", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(40, QCoreApplication::translate("cPatternLinesTrapsPanel", "3 cirkels (Apollonius)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(41, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lissajous 2:3", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(42, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(43, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\265 (afstand)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(44, QCoreApplication::translate("cPatternLinesTrapsPanel", "H-boom (1 iter)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(45, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt (2 niv.)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(46, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zes-lob rimpel", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(47, QCoreApplication::translate("cPatternLinesTrapsPanel", "Binaire boom (2 niv.)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(48, QCoreApplication::translate("cPatternLinesTrapsPanel", "Fermat-spiraal", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(49, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dubbel kruis", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(50, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hendecagon (11-hoek)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(51, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dodecagon (12-hoek)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(52, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tetradecagon (14-hoek)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(53, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hexadecagon (16-hoek)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(54, QCoreApplication::translate("cPatternLinesTrapsPanel", "Icosagon (20-hoek)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(55, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-6 (hexagram)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(56, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-7", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(57, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-8", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(58, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-9", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(59, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-10", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(60, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-12", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(61, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-16", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(62, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-3", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(63, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-4", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(64, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-6", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(65, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-7", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(66, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-8", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(67, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-10", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(68, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-12", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(69, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-16", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(70, QCoreApplication::translate("cPatternLinesTrapsPanel", "Heptagon (7-hoek)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(71, QCoreApplication::translate("cPatternLinesTrapsPanel", "Enneagon (9-hoek)", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(72, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-6", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(73, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-8", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(74, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-10", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(75, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-12", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(76, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-16", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(77, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-20", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(78, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hart", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(79, QCoreApplication::translate("cPatternLinesTrapsPanel", "Infinity", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(80, QCoreApplication::translate("cPatternLinesTrapsPanel", "Druppel", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(81, QCoreApplication::translate("cPatternLinesTrapsPanel", "Oog", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(82, QCoreApplication::translate("cPatternLinesTrapsPanel", "Maan", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(83, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pijl", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(84, QCoreApplication::translate("cPatternLinesTrapsPanel", "Bliksem", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(85, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sinus-golf", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(86, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zaagtand", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(87, QCoreApplication::translate("cPatternLinesTrapsPanel", "Block-golf", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(88, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 60\302\260", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(89, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 90\302\260", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(90, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 120\302\260", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(91, QCoreApplication::translate("cPatternLinesTrapsPanel", "Halve cirkel", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(92, QCoreApplication::translate("cPatternLinesTrapsPanel", "Taartpunt", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(93, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis met bol", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(94, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-kruis", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(95, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant met kruis", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(96, QCoreApplication::translate("cPatternLinesTrapsPanel", "Target", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(97, QCoreApplication::translate("cPatternLinesTrapsPanel", "Genestelde vierkanten", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(98, QCoreApplication::translate("cPatternLinesTrapsPanel", "Meander", nullptr));
        comboBox_pattern_line_trap_4_shape->setItemText(99, QCoreApplication::translate("cPatternLinesTrapsPanel", "Spiraal", nullptr));

        label_pattern_line_4_shape_aux->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel extra", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_4_shape_aux->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal: Z-straal t.o.v. Y (1 = cirkel). Ring: halve dikte van de buis.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_4_sharp_seg->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte / lengte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_4_sharp_seg->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte: sterkere piek (hoger = smallere gloed). Lengte: halve lijnlengte langs X (0 = oneindig). Zie ook \302\253Gloed / rand\302\273.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_4_glow->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloed / rand", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_4_glow->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloedbreedte: hoger = zachtere, bredere rand. Falloff: Gauss, smoothstep, lineair, exponentieel \342\200\224 bepaalt hoe snel het uitsterft (los van de 3-kleur-gradient).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_4_falloff_profile->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gauss (zacht)", nullptr));
        comboBox_pattern_line_trap_4_falloff_profile->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Strak (smooth)", nullptr));
        comboBox_pattern_line_trap_4_falloff_profile->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hard (lineair)", nullptr));
        comboBox_pattern_line_trap_4_falloff_profile->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Exponentieel", nullptr));

        label_pattern_line_4_side->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Zichtbare kant", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_4_side->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek: gloed aan beide zijden van de vorm (klassiek). Alleen buiten of binnen: \303\251\303\251n zijde van het oppervlak \342\200\224 handig om alleen de silhouet-rand te tonen.", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_4_edge_side->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek (beide)", nullptr));
        comboBox_pattern_line_trap_4_edge_side->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen buiten", nullptr));
        comboBox_pattern_line_trap_4_edge_side->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen binnen", nullptr));

        pushButton_pattern_line_trap_4_place_surface->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op oppervlak (zichtlijn)", nullptr));
        pushButton_pattern_line_trap_4_place_target->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op doelpunt", nullptr));
        groupCheck_pattern_line_trap_5_enabled->setTitle(QCoreApplication::translate("cPatternLinesTrapsPanel", "Lijn 5", nullptr));
        label_pattern_line_5_pos->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Positie", nullptr));
        label_pattern_line_5_rot->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Rot \302\260", nullptr));
        label_pattern_line_5_radius->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal / dikte / rand / max", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_5_radius->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal = profielgrootte. Dikte = schaal van de SDF-band. Rand = afronding hoeken. Max = afstand-limiet voor de gloed (0 = uit in praktijk volgens instelling).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_5_scale->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal / rel. dikte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_5_scale->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal: uniform het dwarsprofiel (YZ). Relatieve dikte: factor op de gloedband t.o.v. Dikte (1 = standaard).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_5_int->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Intensiteit / 3 kleuren", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_5_int->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gradient langs de gloed: kern (kleur 1) \342\206\222 midden (2) \342\206\222 rand (3). Zelfde RGB = effen.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_5_shape->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_5_shape->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Dwarsdoorsnede loodrecht op de as (lokale X).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_5_shape->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Buis (rond)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lint (vlak)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ruit", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(4, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(5, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zeshoek", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(6, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(7, QCoreApplication::translate("cPatternLinesTrapsPanel", "Achthoek", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(8, QCoreApplication::translate("cPatternLinesTrapsPanel", "Squircle", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(9, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(10, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vijfhoek", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(11, QCoreApplication::translate("cPatternLinesTrapsPanel", "Rechthoek", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(12, QCoreApplication::translate("cPatternLinesTrapsPanel", "Capsule", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(13, QCoreApplication::translate("cPatternLinesTrapsPanel", "Driehoek", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(14, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-5 (roos)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(15, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tienhoek", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(16, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=3", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(17, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=6", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(18, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sikkel", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(19, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(20, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(21, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski driehoek", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(22, QCoreApplication::translate("cPatternLinesTrapsPanel", "Koch (1 iter)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(23, QCoreApplication::translate("cPatternLinesTrapsPanel", "Mandelbrot (afstand)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(24, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia (afstand)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(25, QCoreApplication::translate("cPatternLinesTrapsPanel", "Burning ship", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(26, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cantor-achtig", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(27, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pythagoras boom", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(28, QCoreApplication::translate("cPatternLinesTrapsPanel", "Draak (polylijn)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(29, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hilbert (orde 1)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(30, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vicsek (5 blokken)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(31, QCoreApplication::translate("cPatternLinesTrapsPanel", "Griekse kruis", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(32, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(33, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\264 (afstand)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(34, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tricorn (afstand)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(35, QCoreApplication::translate("cPatternLinesTrapsPanel", "3-ary boom (Y)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(36, QCoreApplication::translate("cPatternLinesTrapsPanel", "Peano-achtig (8\303\227)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(37, QCoreApplication::translate("cPatternLinesTrapsPanel", "Levy C (1 iter)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(38, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-Cantor", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(39, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gouden L-vorm", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(40, QCoreApplication::translate("cPatternLinesTrapsPanel", "3 cirkels (Apollonius)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(41, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lissajous 2:3", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(42, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(43, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\265 (afstand)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(44, QCoreApplication::translate("cPatternLinesTrapsPanel", "H-boom (1 iter)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(45, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt (2 niv.)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(46, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zes-lob rimpel", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(47, QCoreApplication::translate("cPatternLinesTrapsPanel", "Binaire boom (2 niv.)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(48, QCoreApplication::translate("cPatternLinesTrapsPanel", "Fermat-spiraal", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(49, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dubbel kruis", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(50, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hendecagon (11-hoek)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(51, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dodecagon (12-hoek)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(52, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tetradecagon (14-hoek)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(53, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hexadecagon (16-hoek)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(54, QCoreApplication::translate("cPatternLinesTrapsPanel", "Icosagon (20-hoek)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(55, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-6 (hexagram)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(56, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-7", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(57, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-8", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(58, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-9", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(59, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-10", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(60, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-12", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(61, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-16", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(62, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-3", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(63, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-4", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(64, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-6", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(65, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-7", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(66, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-8", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(67, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-10", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(68, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-12", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(69, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-16", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(70, QCoreApplication::translate("cPatternLinesTrapsPanel", "Heptagon (7-hoek)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(71, QCoreApplication::translate("cPatternLinesTrapsPanel", "Enneagon (9-hoek)", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(72, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-6", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(73, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-8", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(74, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-10", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(75, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-12", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(76, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-16", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(77, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-20", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(78, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hart", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(79, QCoreApplication::translate("cPatternLinesTrapsPanel", "Infinity", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(80, QCoreApplication::translate("cPatternLinesTrapsPanel", "Druppel", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(81, QCoreApplication::translate("cPatternLinesTrapsPanel", "Oog", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(82, QCoreApplication::translate("cPatternLinesTrapsPanel", "Maan", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(83, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pijl", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(84, QCoreApplication::translate("cPatternLinesTrapsPanel", "Bliksem", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(85, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sinus-golf", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(86, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zaagtand", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(87, QCoreApplication::translate("cPatternLinesTrapsPanel", "Block-golf", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(88, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 60\302\260", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(89, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 90\302\260", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(90, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 120\302\260", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(91, QCoreApplication::translate("cPatternLinesTrapsPanel", "Halve cirkel", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(92, QCoreApplication::translate("cPatternLinesTrapsPanel", "Taartpunt", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(93, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis met bol", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(94, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-kruis", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(95, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant met kruis", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(96, QCoreApplication::translate("cPatternLinesTrapsPanel", "Target", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(97, QCoreApplication::translate("cPatternLinesTrapsPanel", "Genestelde vierkanten", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(98, QCoreApplication::translate("cPatternLinesTrapsPanel", "Meander", nullptr));
        comboBox_pattern_line_trap_5_shape->setItemText(99, QCoreApplication::translate("cPatternLinesTrapsPanel", "Spiraal", nullptr));

        label_pattern_line_5_shape_aux->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel extra", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_5_shape_aux->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal: Z-straal t.o.v. Y (1 = cirkel). Ring: halve dikte van de buis.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_5_sharp_seg->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte / lengte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_5_sharp_seg->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte: sterkere piek (hoger = smallere gloed). Lengte: halve lijnlengte langs X (0 = oneindig). Zie ook \302\253Gloed / rand\302\273.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_5_glow->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloed / rand", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_5_glow->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloedbreedte: hoger = zachtere, bredere rand. Falloff: Gauss, smoothstep, lineair, exponentieel \342\200\224 bepaalt hoe snel het uitsterft (los van de 3-kleur-gradient).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_5_falloff_profile->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gauss (zacht)", nullptr));
        comboBox_pattern_line_trap_5_falloff_profile->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Strak (smooth)", nullptr));
        comboBox_pattern_line_trap_5_falloff_profile->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hard (lineair)", nullptr));
        comboBox_pattern_line_trap_5_falloff_profile->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Exponentieel", nullptr));

        label_pattern_line_5_side->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Zichtbare kant", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_5_side->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek: gloed aan beide zijden van de vorm (klassiek). Alleen buiten of binnen: \303\251\303\251n zijde van het oppervlak \342\200\224 handig om alleen de silhouet-rand te tonen.", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_5_edge_side->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek (beide)", nullptr));
        comboBox_pattern_line_trap_5_edge_side->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen buiten", nullptr));
        comboBox_pattern_line_trap_5_edge_side->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen binnen", nullptr));

        pushButton_pattern_line_trap_5_place_surface->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op oppervlak (zichtlijn)", nullptr));
        pushButton_pattern_line_trap_5_place_target->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op doelpunt", nullptr));
        groupCheck_pattern_line_trap_6_enabled->setTitle(QCoreApplication::translate("cPatternLinesTrapsPanel", "Lijn 6", nullptr));
        label_pattern_line_6_pos->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Positie", nullptr));
        label_pattern_line_6_rot->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Rot \302\260", nullptr));
        label_pattern_line_6_radius->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal / dikte / rand / max", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_6_radius->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal = profielgrootte. Dikte = schaal van de SDF-band. Rand = afronding hoeken. Max = afstand-limiet voor de gloed (0 = uit in praktijk volgens instelling).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_6_scale->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal / rel. dikte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_6_scale->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal: uniform het dwarsprofiel (YZ). Relatieve dikte: factor op de gloedband t.o.v. Dikte (1 = standaard).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_6_int->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Intensiteit / 3 kleuren", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_6_int->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gradient langs de gloed: kern (kleur 1) \342\206\222 midden (2) \342\206\222 rand (3). Zelfde RGB = effen.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_6_shape->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_6_shape->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Dwarsdoorsnede loodrecht op de as (lokale X).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_6_shape->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Buis (rond)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lint (vlak)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ruit", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(4, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(5, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zeshoek", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(6, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(7, QCoreApplication::translate("cPatternLinesTrapsPanel", "Achthoek", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(8, QCoreApplication::translate("cPatternLinesTrapsPanel", "Squircle", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(9, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(10, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vijfhoek", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(11, QCoreApplication::translate("cPatternLinesTrapsPanel", "Rechthoek", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(12, QCoreApplication::translate("cPatternLinesTrapsPanel", "Capsule", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(13, QCoreApplication::translate("cPatternLinesTrapsPanel", "Driehoek", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(14, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-5 (roos)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(15, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tienhoek", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(16, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=3", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(17, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=6", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(18, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sikkel", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(19, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(20, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(21, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski driehoek", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(22, QCoreApplication::translate("cPatternLinesTrapsPanel", "Koch (1 iter)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(23, QCoreApplication::translate("cPatternLinesTrapsPanel", "Mandelbrot (afstand)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(24, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia (afstand)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(25, QCoreApplication::translate("cPatternLinesTrapsPanel", "Burning ship", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(26, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cantor-achtig", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(27, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pythagoras boom", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(28, QCoreApplication::translate("cPatternLinesTrapsPanel", "Draak (polylijn)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(29, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hilbert (orde 1)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(30, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vicsek (5 blokken)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(31, QCoreApplication::translate("cPatternLinesTrapsPanel", "Griekse kruis", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(32, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(33, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\264 (afstand)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(34, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tricorn (afstand)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(35, QCoreApplication::translate("cPatternLinesTrapsPanel", "3-ary boom (Y)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(36, QCoreApplication::translate("cPatternLinesTrapsPanel", "Peano-achtig (8\303\227)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(37, QCoreApplication::translate("cPatternLinesTrapsPanel", "Levy C (1 iter)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(38, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-Cantor", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(39, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gouden L-vorm", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(40, QCoreApplication::translate("cPatternLinesTrapsPanel", "3 cirkels (Apollonius)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(41, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lissajous 2:3", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(42, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(43, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\265 (afstand)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(44, QCoreApplication::translate("cPatternLinesTrapsPanel", "H-boom (1 iter)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(45, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt (2 niv.)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(46, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zes-lob rimpel", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(47, QCoreApplication::translate("cPatternLinesTrapsPanel", "Binaire boom (2 niv.)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(48, QCoreApplication::translate("cPatternLinesTrapsPanel", "Fermat-spiraal", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(49, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dubbel kruis", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(50, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hendecagon (11-hoek)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(51, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dodecagon (12-hoek)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(52, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tetradecagon (14-hoek)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(53, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hexadecagon (16-hoek)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(54, QCoreApplication::translate("cPatternLinesTrapsPanel", "Icosagon (20-hoek)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(55, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-6 (hexagram)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(56, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-7", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(57, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-8", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(58, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-9", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(59, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-10", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(60, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-12", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(61, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-16", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(62, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-3", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(63, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-4", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(64, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-6", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(65, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-7", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(66, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-8", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(67, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-10", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(68, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-12", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(69, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-16", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(70, QCoreApplication::translate("cPatternLinesTrapsPanel", "Heptagon (7-hoek)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(71, QCoreApplication::translate("cPatternLinesTrapsPanel", "Enneagon (9-hoek)", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(72, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-6", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(73, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-8", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(74, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-10", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(75, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-12", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(76, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-16", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(77, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-20", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(78, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hart", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(79, QCoreApplication::translate("cPatternLinesTrapsPanel", "Infinity", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(80, QCoreApplication::translate("cPatternLinesTrapsPanel", "Druppel", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(81, QCoreApplication::translate("cPatternLinesTrapsPanel", "Oog", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(82, QCoreApplication::translate("cPatternLinesTrapsPanel", "Maan", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(83, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pijl", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(84, QCoreApplication::translate("cPatternLinesTrapsPanel", "Bliksem", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(85, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sinus-golf", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(86, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zaagtand", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(87, QCoreApplication::translate("cPatternLinesTrapsPanel", "Block-golf", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(88, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 60\302\260", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(89, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 90\302\260", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(90, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 120\302\260", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(91, QCoreApplication::translate("cPatternLinesTrapsPanel", "Halve cirkel", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(92, QCoreApplication::translate("cPatternLinesTrapsPanel", "Taartpunt", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(93, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis met bol", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(94, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-kruis", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(95, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant met kruis", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(96, QCoreApplication::translate("cPatternLinesTrapsPanel", "Target", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(97, QCoreApplication::translate("cPatternLinesTrapsPanel", "Genestelde vierkanten", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(98, QCoreApplication::translate("cPatternLinesTrapsPanel", "Meander", nullptr));
        comboBox_pattern_line_trap_6_shape->setItemText(99, QCoreApplication::translate("cPatternLinesTrapsPanel", "Spiraal", nullptr));

        label_pattern_line_6_shape_aux->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel extra", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_6_shape_aux->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal: Z-straal t.o.v. Y (1 = cirkel). Ring: halve dikte van de buis.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_6_sharp_seg->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte / lengte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_6_sharp_seg->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte: sterkere piek (hoger = smallere gloed). Lengte: halve lijnlengte langs X (0 = oneindig). Zie ook \302\253Gloed / rand\302\273.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_6_glow->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloed / rand", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_6_glow->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloedbreedte: hoger = zachtere, bredere rand. Falloff: Gauss, smoothstep, lineair, exponentieel \342\200\224 bepaalt hoe snel het uitsterft (los van de 3-kleur-gradient).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_6_falloff_profile->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gauss (zacht)", nullptr));
        comboBox_pattern_line_trap_6_falloff_profile->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Strak (smooth)", nullptr));
        comboBox_pattern_line_trap_6_falloff_profile->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hard (lineair)", nullptr));
        comboBox_pattern_line_trap_6_falloff_profile->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Exponentieel", nullptr));

        label_pattern_line_6_side->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Zichtbare kant", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_6_side->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek: gloed aan beide zijden van de vorm (klassiek). Alleen buiten of binnen: \303\251\303\251n zijde van het oppervlak \342\200\224 handig om alleen de silhouet-rand te tonen.", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_6_edge_side->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek (beide)", nullptr));
        comboBox_pattern_line_trap_6_edge_side->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen buiten", nullptr));
        comboBox_pattern_line_trap_6_edge_side->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen binnen", nullptr));

        pushButton_pattern_line_trap_6_place_surface->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op oppervlak (zichtlijn)", nullptr));
        pushButton_pattern_line_trap_6_place_target->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op doelpunt", nullptr));
        groupCheck_pattern_line_trap_7_enabled->setTitle(QCoreApplication::translate("cPatternLinesTrapsPanel", "Lijn 7", nullptr));
        label_pattern_line_7_pos->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Positie", nullptr));
        label_pattern_line_7_rot->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Rot \302\260", nullptr));
        label_pattern_line_7_radius->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal / dikte / rand / max", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_7_radius->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal = profielgrootte. Dikte = schaal van de SDF-band. Rand = afronding hoeken. Max = afstand-limiet voor de gloed (0 = uit in praktijk volgens instelling).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_7_scale->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal / rel. dikte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_7_scale->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal: uniform het dwarsprofiel (YZ). Relatieve dikte: factor op de gloedband t.o.v. Dikte (1 = standaard).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_7_int->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Intensiteit / 3 kleuren", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_7_int->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gradient langs de gloed: kern (kleur 1) \342\206\222 midden (2) \342\206\222 rand (3). Zelfde RGB = effen.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_7_shape->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_7_shape->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Dwarsdoorsnede loodrecht op de as (lokale X).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_7_shape->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Buis (rond)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lint (vlak)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ruit", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(4, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(5, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zeshoek", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(6, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(7, QCoreApplication::translate("cPatternLinesTrapsPanel", "Achthoek", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(8, QCoreApplication::translate("cPatternLinesTrapsPanel", "Squircle", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(9, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(10, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vijfhoek", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(11, QCoreApplication::translate("cPatternLinesTrapsPanel", "Rechthoek", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(12, QCoreApplication::translate("cPatternLinesTrapsPanel", "Capsule", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(13, QCoreApplication::translate("cPatternLinesTrapsPanel", "Driehoek", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(14, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-5 (roos)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(15, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tienhoek", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(16, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=3", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(17, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=6", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(18, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sikkel", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(19, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(20, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(21, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski driehoek", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(22, QCoreApplication::translate("cPatternLinesTrapsPanel", "Koch (1 iter)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(23, QCoreApplication::translate("cPatternLinesTrapsPanel", "Mandelbrot (afstand)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(24, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia (afstand)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(25, QCoreApplication::translate("cPatternLinesTrapsPanel", "Burning ship", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(26, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cantor-achtig", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(27, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pythagoras boom", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(28, QCoreApplication::translate("cPatternLinesTrapsPanel", "Draak (polylijn)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(29, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hilbert (orde 1)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(30, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vicsek (5 blokken)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(31, QCoreApplication::translate("cPatternLinesTrapsPanel", "Griekse kruis", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(32, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(33, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\264 (afstand)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(34, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tricorn (afstand)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(35, QCoreApplication::translate("cPatternLinesTrapsPanel", "3-ary boom (Y)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(36, QCoreApplication::translate("cPatternLinesTrapsPanel", "Peano-achtig (8\303\227)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(37, QCoreApplication::translate("cPatternLinesTrapsPanel", "Levy C (1 iter)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(38, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-Cantor", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(39, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gouden L-vorm", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(40, QCoreApplication::translate("cPatternLinesTrapsPanel", "3 cirkels (Apollonius)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(41, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lissajous 2:3", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(42, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(43, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\265 (afstand)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(44, QCoreApplication::translate("cPatternLinesTrapsPanel", "H-boom (1 iter)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(45, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt (2 niv.)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(46, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zes-lob rimpel", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(47, QCoreApplication::translate("cPatternLinesTrapsPanel", "Binaire boom (2 niv.)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(48, QCoreApplication::translate("cPatternLinesTrapsPanel", "Fermat-spiraal", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(49, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dubbel kruis", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(50, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hendecagon (11-hoek)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(51, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dodecagon (12-hoek)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(52, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tetradecagon (14-hoek)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(53, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hexadecagon (16-hoek)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(54, QCoreApplication::translate("cPatternLinesTrapsPanel", "Icosagon (20-hoek)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(55, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-6 (hexagram)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(56, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-7", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(57, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-8", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(58, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-9", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(59, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-10", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(60, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-12", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(61, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-16", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(62, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-3", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(63, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-4", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(64, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-6", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(65, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-7", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(66, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-8", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(67, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-10", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(68, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-12", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(69, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-16", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(70, QCoreApplication::translate("cPatternLinesTrapsPanel", "Heptagon (7-hoek)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(71, QCoreApplication::translate("cPatternLinesTrapsPanel", "Enneagon (9-hoek)", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(72, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-6", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(73, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-8", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(74, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-10", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(75, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-12", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(76, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-16", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(77, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-20", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(78, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hart", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(79, QCoreApplication::translate("cPatternLinesTrapsPanel", "Infinity", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(80, QCoreApplication::translate("cPatternLinesTrapsPanel", "Druppel", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(81, QCoreApplication::translate("cPatternLinesTrapsPanel", "Oog", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(82, QCoreApplication::translate("cPatternLinesTrapsPanel", "Maan", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(83, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pijl", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(84, QCoreApplication::translate("cPatternLinesTrapsPanel", "Bliksem", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(85, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sinus-golf", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(86, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zaagtand", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(87, QCoreApplication::translate("cPatternLinesTrapsPanel", "Block-golf", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(88, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 60\302\260", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(89, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 90\302\260", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(90, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 120\302\260", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(91, QCoreApplication::translate("cPatternLinesTrapsPanel", "Halve cirkel", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(92, QCoreApplication::translate("cPatternLinesTrapsPanel", "Taartpunt", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(93, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis met bol", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(94, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-kruis", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(95, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant met kruis", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(96, QCoreApplication::translate("cPatternLinesTrapsPanel", "Target", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(97, QCoreApplication::translate("cPatternLinesTrapsPanel", "Genestelde vierkanten", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(98, QCoreApplication::translate("cPatternLinesTrapsPanel", "Meander", nullptr));
        comboBox_pattern_line_trap_7_shape->setItemText(99, QCoreApplication::translate("cPatternLinesTrapsPanel", "Spiraal", nullptr));

        label_pattern_line_7_shape_aux->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel extra", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_7_shape_aux->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal: Z-straal t.o.v. Y (1 = cirkel). Ring: halve dikte van de buis.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_7_sharp_seg->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte / lengte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_7_sharp_seg->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte: sterkere piek (hoger = smallere gloed). Lengte: halve lijnlengte langs X (0 = oneindig). Zie ook \302\253Gloed / rand\302\273.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_7_glow->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloed / rand", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_7_glow->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloedbreedte: hoger = zachtere, bredere rand. Falloff: Gauss, smoothstep, lineair, exponentieel \342\200\224 bepaalt hoe snel het uitsterft (los van de 3-kleur-gradient).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_7_falloff_profile->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gauss (zacht)", nullptr));
        comboBox_pattern_line_trap_7_falloff_profile->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Strak (smooth)", nullptr));
        comboBox_pattern_line_trap_7_falloff_profile->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hard (lineair)", nullptr));
        comboBox_pattern_line_trap_7_falloff_profile->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Exponentieel", nullptr));

        label_pattern_line_7_side->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Zichtbare kant", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_7_side->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek: gloed aan beide zijden van de vorm (klassiek). Alleen buiten of binnen: \303\251\303\251n zijde van het oppervlak \342\200\224 handig om alleen de silhouet-rand te tonen.", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_7_edge_side->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek (beide)", nullptr));
        comboBox_pattern_line_trap_7_edge_side->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen buiten", nullptr));
        comboBox_pattern_line_trap_7_edge_side->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen binnen", nullptr));

        pushButton_pattern_line_trap_7_place_surface->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op oppervlak (zichtlijn)", nullptr));
        pushButton_pattern_line_trap_7_place_target->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op doelpunt", nullptr));
        groupCheck_pattern_line_trap_8_enabled->setTitle(QCoreApplication::translate("cPatternLinesTrapsPanel", "Lijn 8", nullptr));
        label_pattern_line_8_pos->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Positie", nullptr));
        label_pattern_line_8_rot->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Rot \302\260", nullptr));
        label_pattern_line_8_radius->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal / dikte / rand / max", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_8_radius->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal = profielgrootte. Dikte = schaal van de SDF-band. Rand = afronding hoeken. Max = afstand-limiet voor de gloed (0 = uit in praktijk volgens instelling).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_8_scale->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal / rel. dikte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_8_scale->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal: uniform het dwarsprofiel (YZ). Relatieve dikte: factor op de gloedband t.o.v. Dikte (1 = standaard).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_8_int->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Intensiteit / 3 kleuren", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_8_int->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gradient langs de gloed: kern (kleur 1) \342\206\222 midden (2) \342\206\222 rand (3). Zelfde RGB = effen.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_8_shape->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_8_shape->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Dwarsdoorsnede loodrecht op de as (lokale X).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_8_shape->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Buis (rond)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lint (vlak)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ruit", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(4, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(5, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zeshoek", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(6, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(7, QCoreApplication::translate("cPatternLinesTrapsPanel", "Achthoek", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(8, QCoreApplication::translate("cPatternLinesTrapsPanel", "Squircle", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(9, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(10, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vijfhoek", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(11, QCoreApplication::translate("cPatternLinesTrapsPanel", "Rechthoek", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(12, QCoreApplication::translate("cPatternLinesTrapsPanel", "Capsule", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(13, QCoreApplication::translate("cPatternLinesTrapsPanel", "Driehoek", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(14, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-5 (roos)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(15, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tienhoek", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(16, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=3", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(17, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=6", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(18, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sikkel", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(19, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(20, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(21, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski driehoek", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(22, QCoreApplication::translate("cPatternLinesTrapsPanel", "Koch (1 iter)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(23, QCoreApplication::translate("cPatternLinesTrapsPanel", "Mandelbrot (afstand)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(24, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia (afstand)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(25, QCoreApplication::translate("cPatternLinesTrapsPanel", "Burning ship", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(26, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cantor-achtig", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(27, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pythagoras boom", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(28, QCoreApplication::translate("cPatternLinesTrapsPanel", "Draak (polylijn)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(29, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hilbert (orde 1)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(30, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vicsek (5 blokken)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(31, QCoreApplication::translate("cPatternLinesTrapsPanel", "Griekse kruis", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(32, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(33, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\264 (afstand)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(34, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tricorn (afstand)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(35, QCoreApplication::translate("cPatternLinesTrapsPanel", "3-ary boom (Y)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(36, QCoreApplication::translate("cPatternLinesTrapsPanel", "Peano-achtig (8\303\227)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(37, QCoreApplication::translate("cPatternLinesTrapsPanel", "Levy C (1 iter)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(38, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-Cantor", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(39, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gouden L-vorm", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(40, QCoreApplication::translate("cPatternLinesTrapsPanel", "3 cirkels (Apollonius)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(41, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lissajous 2:3", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(42, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(43, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\265 (afstand)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(44, QCoreApplication::translate("cPatternLinesTrapsPanel", "H-boom (1 iter)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(45, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt (2 niv.)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(46, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zes-lob rimpel", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(47, QCoreApplication::translate("cPatternLinesTrapsPanel", "Binaire boom (2 niv.)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(48, QCoreApplication::translate("cPatternLinesTrapsPanel", "Fermat-spiraal", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(49, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dubbel kruis", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(50, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hendecagon (11-hoek)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(51, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dodecagon (12-hoek)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(52, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tetradecagon (14-hoek)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(53, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hexadecagon (16-hoek)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(54, QCoreApplication::translate("cPatternLinesTrapsPanel", "Icosagon (20-hoek)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(55, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-6 (hexagram)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(56, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-7", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(57, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-8", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(58, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-9", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(59, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-10", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(60, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-12", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(61, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-16", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(62, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-3", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(63, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-4", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(64, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-6", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(65, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-7", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(66, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-8", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(67, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-10", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(68, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-12", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(69, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-16", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(70, QCoreApplication::translate("cPatternLinesTrapsPanel", "Heptagon (7-hoek)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(71, QCoreApplication::translate("cPatternLinesTrapsPanel", "Enneagon (9-hoek)", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(72, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-6", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(73, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-8", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(74, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-10", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(75, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-12", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(76, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-16", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(77, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-20", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(78, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hart", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(79, QCoreApplication::translate("cPatternLinesTrapsPanel", "Infinity", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(80, QCoreApplication::translate("cPatternLinesTrapsPanel", "Druppel", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(81, QCoreApplication::translate("cPatternLinesTrapsPanel", "Oog", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(82, QCoreApplication::translate("cPatternLinesTrapsPanel", "Maan", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(83, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pijl", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(84, QCoreApplication::translate("cPatternLinesTrapsPanel", "Bliksem", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(85, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sinus-golf", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(86, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zaagtand", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(87, QCoreApplication::translate("cPatternLinesTrapsPanel", "Block-golf", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(88, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 60\302\260", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(89, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 90\302\260", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(90, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 120\302\260", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(91, QCoreApplication::translate("cPatternLinesTrapsPanel", "Halve cirkel", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(92, QCoreApplication::translate("cPatternLinesTrapsPanel", "Taartpunt", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(93, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis met bol", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(94, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-kruis", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(95, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant met kruis", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(96, QCoreApplication::translate("cPatternLinesTrapsPanel", "Target", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(97, QCoreApplication::translate("cPatternLinesTrapsPanel", "Genestelde vierkanten", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(98, QCoreApplication::translate("cPatternLinesTrapsPanel", "Meander", nullptr));
        comboBox_pattern_line_trap_8_shape->setItemText(99, QCoreApplication::translate("cPatternLinesTrapsPanel", "Spiraal", nullptr));

        label_pattern_line_8_shape_aux->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel extra", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_8_shape_aux->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal: Z-straal t.o.v. Y (1 = cirkel). Ring: halve dikte van de buis.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_8_sharp_seg->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte / lengte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_8_sharp_seg->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte: sterkere piek (hoger = smallere gloed). Lengte: halve lijnlengte langs X (0 = oneindig). Zie ook \302\253Gloed / rand\302\273.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_8_glow->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloed / rand", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_8_glow->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloedbreedte: hoger = zachtere, bredere rand. Falloff: Gauss, smoothstep, lineair, exponentieel \342\200\224 bepaalt hoe snel het uitsterft (los van de 3-kleur-gradient).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_8_falloff_profile->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gauss (zacht)", nullptr));
        comboBox_pattern_line_trap_8_falloff_profile->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Strak (smooth)", nullptr));
        comboBox_pattern_line_trap_8_falloff_profile->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hard (lineair)", nullptr));
        comboBox_pattern_line_trap_8_falloff_profile->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Exponentieel", nullptr));

        label_pattern_line_8_side->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Zichtbare kant", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_8_side->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek: gloed aan beide zijden van de vorm (klassiek). Alleen buiten of binnen: \303\251\303\251n zijde van het oppervlak \342\200\224 handig om alleen de silhouet-rand te tonen.", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_8_edge_side->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek (beide)", nullptr));
        comboBox_pattern_line_trap_8_edge_side->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen buiten", nullptr));
        comboBox_pattern_line_trap_8_edge_side->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen binnen", nullptr));

        pushButton_pattern_line_trap_8_place_surface->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op oppervlak (zichtlijn)", nullptr));
        pushButton_pattern_line_trap_8_place_target->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op doelpunt", nullptr));
        groupCheck_pattern_line_trap_9_enabled->setTitle(QCoreApplication::translate("cPatternLinesTrapsPanel", "Lijn 9", nullptr));
        label_pattern_line_9_pos->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Positie", nullptr));
        label_pattern_line_9_rot->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Rot \302\260", nullptr));
        label_pattern_line_9_radius->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal / dikte / rand / max", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_9_radius->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal = profielgrootte. Dikte = schaal van de SDF-band. Rand = afronding hoeken. Max = afstand-limiet voor de gloed (0 = uit in praktijk volgens instelling).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_9_scale->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal / rel. dikte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_9_scale->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal: uniform het dwarsprofiel (YZ). Relatieve dikte: factor op de gloedband t.o.v. Dikte (1 = standaard).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_9_int->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Intensiteit / 3 kleuren", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_9_int->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gradient langs de gloed: kern (kleur 1) \342\206\222 midden (2) \342\206\222 rand (3). Zelfde RGB = effen.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_9_shape->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_9_shape->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Dwarsdoorsnede loodrecht op de as (lokale X).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_9_shape->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Buis (rond)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lint (vlak)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ruit", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(4, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(5, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zeshoek", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(6, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(7, QCoreApplication::translate("cPatternLinesTrapsPanel", "Achthoek", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(8, QCoreApplication::translate("cPatternLinesTrapsPanel", "Squircle", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(9, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(10, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vijfhoek", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(11, QCoreApplication::translate("cPatternLinesTrapsPanel", "Rechthoek", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(12, QCoreApplication::translate("cPatternLinesTrapsPanel", "Capsule", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(13, QCoreApplication::translate("cPatternLinesTrapsPanel", "Driehoek", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(14, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-5 (roos)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(15, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tienhoek", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(16, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=3", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(17, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=6", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(18, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sikkel", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(19, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(20, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(21, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski driehoek", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(22, QCoreApplication::translate("cPatternLinesTrapsPanel", "Koch (1 iter)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(23, QCoreApplication::translate("cPatternLinesTrapsPanel", "Mandelbrot (afstand)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(24, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia (afstand)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(25, QCoreApplication::translate("cPatternLinesTrapsPanel", "Burning ship", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(26, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cantor-achtig", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(27, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pythagoras boom", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(28, QCoreApplication::translate("cPatternLinesTrapsPanel", "Draak (polylijn)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(29, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hilbert (orde 1)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(30, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vicsek (5 blokken)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(31, QCoreApplication::translate("cPatternLinesTrapsPanel", "Griekse kruis", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(32, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(33, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\264 (afstand)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(34, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tricorn (afstand)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(35, QCoreApplication::translate("cPatternLinesTrapsPanel", "3-ary boom (Y)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(36, QCoreApplication::translate("cPatternLinesTrapsPanel", "Peano-achtig (8\303\227)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(37, QCoreApplication::translate("cPatternLinesTrapsPanel", "Levy C (1 iter)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(38, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-Cantor", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(39, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gouden L-vorm", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(40, QCoreApplication::translate("cPatternLinesTrapsPanel", "3 cirkels (Apollonius)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(41, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lissajous 2:3", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(42, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(43, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\265 (afstand)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(44, QCoreApplication::translate("cPatternLinesTrapsPanel", "H-boom (1 iter)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(45, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt (2 niv.)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(46, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zes-lob rimpel", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(47, QCoreApplication::translate("cPatternLinesTrapsPanel", "Binaire boom (2 niv.)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(48, QCoreApplication::translate("cPatternLinesTrapsPanel", "Fermat-spiraal", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(49, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dubbel kruis", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(50, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hendecagon (11-hoek)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(51, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dodecagon (12-hoek)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(52, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tetradecagon (14-hoek)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(53, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hexadecagon (16-hoek)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(54, QCoreApplication::translate("cPatternLinesTrapsPanel", "Icosagon (20-hoek)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(55, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-6 (hexagram)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(56, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-7", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(57, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-8", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(58, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-9", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(59, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-10", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(60, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-12", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(61, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-16", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(62, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-3", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(63, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-4", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(64, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-6", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(65, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-7", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(66, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-8", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(67, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-10", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(68, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-12", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(69, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-16", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(70, QCoreApplication::translate("cPatternLinesTrapsPanel", "Heptagon (7-hoek)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(71, QCoreApplication::translate("cPatternLinesTrapsPanel", "Enneagon (9-hoek)", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(72, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-6", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(73, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-8", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(74, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-10", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(75, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-12", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(76, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-16", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(77, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-20", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(78, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hart", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(79, QCoreApplication::translate("cPatternLinesTrapsPanel", "Infinity", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(80, QCoreApplication::translate("cPatternLinesTrapsPanel", "Druppel", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(81, QCoreApplication::translate("cPatternLinesTrapsPanel", "Oog", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(82, QCoreApplication::translate("cPatternLinesTrapsPanel", "Maan", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(83, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pijl", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(84, QCoreApplication::translate("cPatternLinesTrapsPanel", "Bliksem", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(85, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sinus-golf", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(86, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zaagtand", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(87, QCoreApplication::translate("cPatternLinesTrapsPanel", "Block-golf", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(88, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 60\302\260", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(89, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 90\302\260", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(90, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 120\302\260", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(91, QCoreApplication::translate("cPatternLinesTrapsPanel", "Halve cirkel", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(92, QCoreApplication::translate("cPatternLinesTrapsPanel", "Taartpunt", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(93, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis met bol", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(94, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-kruis", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(95, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant met kruis", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(96, QCoreApplication::translate("cPatternLinesTrapsPanel", "Target", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(97, QCoreApplication::translate("cPatternLinesTrapsPanel", "Genestelde vierkanten", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(98, QCoreApplication::translate("cPatternLinesTrapsPanel", "Meander", nullptr));
        comboBox_pattern_line_trap_9_shape->setItemText(99, QCoreApplication::translate("cPatternLinesTrapsPanel", "Spiraal", nullptr));

        label_pattern_line_9_shape_aux->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel extra", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_9_shape_aux->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal: Z-straal t.o.v. Y (1 = cirkel). Ring: halve dikte van de buis.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_9_sharp_seg->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte / lengte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_9_sharp_seg->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte: sterkere piek (hoger = smallere gloed). Lengte: halve lijnlengte langs X (0 = oneindig). Zie ook \302\253Gloed / rand\302\273.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_9_glow->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloed / rand", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_9_glow->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloedbreedte: hoger = zachtere, bredere rand. Falloff: Gauss, smoothstep, lineair, exponentieel \342\200\224 bepaalt hoe snel het uitsterft (los van de 3-kleur-gradient).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_9_falloff_profile->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gauss (zacht)", nullptr));
        comboBox_pattern_line_trap_9_falloff_profile->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Strak (smooth)", nullptr));
        comboBox_pattern_line_trap_9_falloff_profile->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hard (lineair)", nullptr));
        comboBox_pattern_line_trap_9_falloff_profile->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Exponentieel", nullptr));

        label_pattern_line_9_side->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Zichtbare kant", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_9_side->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek: gloed aan beide zijden van de vorm (klassiek). Alleen buiten of binnen: \303\251\303\251n zijde van het oppervlak \342\200\224 handig om alleen de silhouet-rand te tonen.", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_9_edge_side->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek (beide)", nullptr));
        comboBox_pattern_line_trap_9_edge_side->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen buiten", nullptr));
        comboBox_pattern_line_trap_9_edge_side->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen binnen", nullptr));

        pushButton_pattern_line_trap_9_place_surface->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op oppervlak (zichtlijn)", nullptr));
        pushButton_pattern_line_trap_9_place_target->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op doelpunt", nullptr));
        groupCheck_pattern_line_trap_10_enabled->setTitle(QCoreApplication::translate("cPatternLinesTrapsPanel", "Lijn 10", nullptr));
        label_pattern_line_10_pos->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Positie", nullptr));
        label_pattern_line_10_rot->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Rot \302\260", nullptr));
        label_pattern_line_10_radius->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal / dikte / rand / max", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_10_radius->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal = profielgrootte. Dikte = schaal van de SDF-band. Rand = afronding hoeken. Max = afstand-limiet voor de gloed (0 = uit in praktijk volgens instelling).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_10_scale->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal / rel. dikte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_10_scale->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal: uniform het dwarsprofiel (YZ). Relatieve dikte: factor op de gloedband t.o.v. Dikte (1 = standaard).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_10_int->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Intensiteit / 3 kleuren", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_10_int->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gradient langs de gloed: kern (kleur 1) \342\206\222 midden (2) \342\206\222 rand (3). Zelfde RGB = effen.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_10_shape->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_10_shape->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Dwarsdoorsnede loodrecht op de as (lokale X).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_10_shape->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Buis (rond)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lint (vlak)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ruit", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(4, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(5, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zeshoek", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(6, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(7, QCoreApplication::translate("cPatternLinesTrapsPanel", "Achthoek", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(8, QCoreApplication::translate("cPatternLinesTrapsPanel", "Squircle", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(9, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(10, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vijfhoek", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(11, QCoreApplication::translate("cPatternLinesTrapsPanel", "Rechthoek", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(12, QCoreApplication::translate("cPatternLinesTrapsPanel", "Capsule", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(13, QCoreApplication::translate("cPatternLinesTrapsPanel", "Driehoek", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(14, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-5 (roos)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(15, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tienhoek", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(16, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=3", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(17, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=6", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(18, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sikkel", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(19, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(20, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(21, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski driehoek", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(22, QCoreApplication::translate("cPatternLinesTrapsPanel", "Koch (1 iter)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(23, QCoreApplication::translate("cPatternLinesTrapsPanel", "Mandelbrot (afstand)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(24, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia (afstand)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(25, QCoreApplication::translate("cPatternLinesTrapsPanel", "Burning ship", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(26, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cantor-achtig", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(27, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pythagoras boom", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(28, QCoreApplication::translate("cPatternLinesTrapsPanel", "Draak (polylijn)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(29, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hilbert (orde 1)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(30, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vicsek (5 blokken)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(31, QCoreApplication::translate("cPatternLinesTrapsPanel", "Griekse kruis", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(32, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(33, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\264 (afstand)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(34, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tricorn (afstand)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(35, QCoreApplication::translate("cPatternLinesTrapsPanel", "3-ary boom (Y)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(36, QCoreApplication::translate("cPatternLinesTrapsPanel", "Peano-achtig (8\303\227)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(37, QCoreApplication::translate("cPatternLinesTrapsPanel", "Levy C (1 iter)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(38, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-Cantor", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(39, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gouden L-vorm", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(40, QCoreApplication::translate("cPatternLinesTrapsPanel", "3 cirkels (Apollonius)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(41, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lissajous 2:3", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(42, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(43, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\265 (afstand)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(44, QCoreApplication::translate("cPatternLinesTrapsPanel", "H-boom (1 iter)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(45, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt (2 niv.)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(46, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zes-lob rimpel", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(47, QCoreApplication::translate("cPatternLinesTrapsPanel", "Binaire boom (2 niv.)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(48, QCoreApplication::translate("cPatternLinesTrapsPanel", "Fermat-spiraal", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(49, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dubbel kruis", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(50, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hendecagon (11-hoek)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(51, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dodecagon (12-hoek)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(52, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tetradecagon (14-hoek)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(53, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hexadecagon (16-hoek)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(54, QCoreApplication::translate("cPatternLinesTrapsPanel", "Icosagon (20-hoek)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(55, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-6 (hexagram)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(56, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-7", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(57, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-8", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(58, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-9", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(59, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-10", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(60, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-12", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(61, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-16", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(62, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-3", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(63, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-4", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(64, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-6", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(65, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-7", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(66, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-8", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(67, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-10", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(68, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-12", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(69, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-16", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(70, QCoreApplication::translate("cPatternLinesTrapsPanel", "Heptagon (7-hoek)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(71, QCoreApplication::translate("cPatternLinesTrapsPanel", "Enneagon (9-hoek)", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(72, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-6", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(73, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-8", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(74, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-10", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(75, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-12", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(76, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-16", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(77, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-20", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(78, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hart", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(79, QCoreApplication::translate("cPatternLinesTrapsPanel", "Infinity", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(80, QCoreApplication::translate("cPatternLinesTrapsPanel", "Druppel", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(81, QCoreApplication::translate("cPatternLinesTrapsPanel", "Oog", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(82, QCoreApplication::translate("cPatternLinesTrapsPanel", "Maan", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(83, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pijl", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(84, QCoreApplication::translate("cPatternLinesTrapsPanel", "Bliksem", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(85, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sinus-golf", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(86, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zaagtand", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(87, QCoreApplication::translate("cPatternLinesTrapsPanel", "Block-golf", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(88, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 60\302\260", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(89, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 90\302\260", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(90, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 120\302\260", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(91, QCoreApplication::translate("cPatternLinesTrapsPanel", "Halve cirkel", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(92, QCoreApplication::translate("cPatternLinesTrapsPanel", "Taartpunt", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(93, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis met bol", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(94, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-kruis", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(95, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant met kruis", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(96, QCoreApplication::translate("cPatternLinesTrapsPanel", "Target", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(97, QCoreApplication::translate("cPatternLinesTrapsPanel", "Genestelde vierkanten", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(98, QCoreApplication::translate("cPatternLinesTrapsPanel", "Meander", nullptr));
        comboBox_pattern_line_trap_10_shape->setItemText(99, QCoreApplication::translate("cPatternLinesTrapsPanel", "Spiraal", nullptr));

        label_pattern_line_10_shape_aux->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel extra", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_10_shape_aux->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal: Z-straal t.o.v. Y (1 = cirkel). Ring: halve dikte van de buis.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_10_sharp_seg->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte / lengte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_10_sharp_seg->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte: sterkere piek (hoger = smallere gloed). Lengte: halve lijnlengte langs X (0 = oneindig). Zie ook \302\253Gloed / rand\302\273.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_10_glow->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloed / rand", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_10_glow->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloedbreedte: hoger = zachtere, bredere rand. Falloff: Gauss, smoothstep, lineair, exponentieel \342\200\224 bepaalt hoe snel het uitsterft (los van de 3-kleur-gradient).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_10_falloff_profile->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gauss (zacht)", nullptr));
        comboBox_pattern_line_trap_10_falloff_profile->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Strak (smooth)", nullptr));
        comboBox_pattern_line_trap_10_falloff_profile->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hard (lineair)", nullptr));
        comboBox_pattern_line_trap_10_falloff_profile->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Exponentieel", nullptr));

        label_pattern_line_10_side->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Zichtbare kant", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_10_side->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek: gloed aan beide zijden van de vorm (klassiek). Alleen buiten of binnen: \303\251\303\251n zijde van het oppervlak \342\200\224 handig om alleen de silhouet-rand te tonen.", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_10_edge_side->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek (beide)", nullptr));
        comboBox_pattern_line_trap_10_edge_side->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen buiten", nullptr));
        comboBox_pattern_line_trap_10_edge_side->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen binnen", nullptr));

        pushButton_pattern_line_trap_10_place_surface->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op oppervlak (zichtlijn)", nullptr));
        pushButton_pattern_line_trap_10_place_target->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op doelpunt", nullptr));
        groupCheck_pattern_line_trap_11_enabled->setTitle(QCoreApplication::translate("cPatternLinesTrapsPanel", "Lijn 11", nullptr));
        label_pattern_line_11_pos->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Positie", nullptr));
        label_pattern_line_11_rot->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Rot \302\260", nullptr));
        label_pattern_line_11_radius->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal / dikte / rand / max", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_11_radius->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal = profielgrootte. Dikte = schaal van de SDF-band. Rand = afronding hoeken. Max = afstand-limiet voor de gloed (0 = uit in praktijk volgens instelling).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_11_scale->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal / rel. dikte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_11_scale->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal: uniform het dwarsprofiel (YZ). Relatieve dikte: factor op de gloedband t.o.v. Dikte (1 = standaard).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_11_int->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Intensiteit / 3 kleuren", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_11_int->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gradient langs de gloed: kern (kleur 1) \342\206\222 midden (2) \342\206\222 rand (3). Zelfde RGB = effen.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_11_shape->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_11_shape->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Dwarsdoorsnede loodrecht op de as (lokale X).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_11_shape->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Buis (rond)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lint (vlak)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ruit", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(4, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(5, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zeshoek", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(6, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(7, QCoreApplication::translate("cPatternLinesTrapsPanel", "Achthoek", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(8, QCoreApplication::translate("cPatternLinesTrapsPanel", "Squircle", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(9, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(10, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vijfhoek", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(11, QCoreApplication::translate("cPatternLinesTrapsPanel", "Rechthoek", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(12, QCoreApplication::translate("cPatternLinesTrapsPanel", "Capsule", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(13, QCoreApplication::translate("cPatternLinesTrapsPanel", "Driehoek", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(14, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-5 (roos)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(15, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tienhoek", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(16, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=3", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(17, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=6", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(18, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sikkel", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(19, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(20, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(21, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski driehoek", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(22, QCoreApplication::translate("cPatternLinesTrapsPanel", "Koch (1 iter)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(23, QCoreApplication::translate("cPatternLinesTrapsPanel", "Mandelbrot (afstand)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(24, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia (afstand)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(25, QCoreApplication::translate("cPatternLinesTrapsPanel", "Burning ship", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(26, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cantor-achtig", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(27, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pythagoras boom", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(28, QCoreApplication::translate("cPatternLinesTrapsPanel", "Draak (polylijn)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(29, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hilbert (orde 1)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(30, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vicsek (5 blokken)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(31, QCoreApplication::translate("cPatternLinesTrapsPanel", "Griekse kruis", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(32, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(33, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\264 (afstand)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(34, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tricorn (afstand)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(35, QCoreApplication::translate("cPatternLinesTrapsPanel", "3-ary boom (Y)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(36, QCoreApplication::translate("cPatternLinesTrapsPanel", "Peano-achtig (8\303\227)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(37, QCoreApplication::translate("cPatternLinesTrapsPanel", "Levy C (1 iter)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(38, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-Cantor", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(39, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gouden L-vorm", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(40, QCoreApplication::translate("cPatternLinesTrapsPanel", "3 cirkels (Apollonius)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(41, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lissajous 2:3", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(42, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(43, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\265 (afstand)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(44, QCoreApplication::translate("cPatternLinesTrapsPanel", "H-boom (1 iter)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(45, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt (2 niv.)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(46, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zes-lob rimpel", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(47, QCoreApplication::translate("cPatternLinesTrapsPanel", "Binaire boom (2 niv.)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(48, QCoreApplication::translate("cPatternLinesTrapsPanel", "Fermat-spiraal", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(49, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dubbel kruis", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(50, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hendecagon (11-hoek)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(51, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dodecagon (12-hoek)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(52, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tetradecagon (14-hoek)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(53, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hexadecagon (16-hoek)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(54, QCoreApplication::translate("cPatternLinesTrapsPanel", "Icosagon (20-hoek)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(55, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-6 (hexagram)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(56, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-7", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(57, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-8", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(58, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-9", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(59, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-10", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(60, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-12", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(61, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-16", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(62, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-3", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(63, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-4", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(64, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-6", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(65, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-7", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(66, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-8", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(67, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-10", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(68, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-12", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(69, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-16", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(70, QCoreApplication::translate("cPatternLinesTrapsPanel", "Heptagon (7-hoek)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(71, QCoreApplication::translate("cPatternLinesTrapsPanel", "Enneagon (9-hoek)", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(72, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-6", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(73, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-8", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(74, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-10", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(75, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-12", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(76, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-16", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(77, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-20", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(78, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hart", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(79, QCoreApplication::translate("cPatternLinesTrapsPanel", "Infinity", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(80, QCoreApplication::translate("cPatternLinesTrapsPanel", "Druppel", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(81, QCoreApplication::translate("cPatternLinesTrapsPanel", "Oog", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(82, QCoreApplication::translate("cPatternLinesTrapsPanel", "Maan", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(83, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pijl", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(84, QCoreApplication::translate("cPatternLinesTrapsPanel", "Bliksem", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(85, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sinus-golf", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(86, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zaagtand", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(87, QCoreApplication::translate("cPatternLinesTrapsPanel", "Block-golf", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(88, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 60\302\260", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(89, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 90\302\260", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(90, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 120\302\260", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(91, QCoreApplication::translate("cPatternLinesTrapsPanel", "Halve cirkel", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(92, QCoreApplication::translate("cPatternLinesTrapsPanel", "Taartpunt", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(93, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis met bol", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(94, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-kruis", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(95, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant met kruis", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(96, QCoreApplication::translate("cPatternLinesTrapsPanel", "Target", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(97, QCoreApplication::translate("cPatternLinesTrapsPanel", "Genestelde vierkanten", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(98, QCoreApplication::translate("cPatternLinesTrapsPanel", "Meander", nullptr));
        comboBox_pattern_line_trap_11_shape->setItemText(99, QCoreApplication::translate("cPatternLinesTrapsPanel", "Spiraal", nullptr));

        label_pattern_line_11_shape_aux->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel extra", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_11_shape_aux->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal: Z-straal t.o.v. Y (1 = cirkel). Ring: halve dikte van de buis.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_11_sharp_seg->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte / lengte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_11_sharp_seg->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte: sterkere piek (hoger = smallere gloed). Lengte: halve lijnlengte langs X (0 = oneindig). Zie ook \302\253Gloed / rand\302\273.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_11_glow->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloed / rand", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_11_glow->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloedbreedte: hoger = zachtere, bredere rand. Falloff: Gauss, smoothstep, lineair, exponentieel \342\200\224 bepaalt hoe snel het uitsterft (los van de 3-kleur-gradient).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_11_falloff_profile->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gauss (zacht)", nullptr));
        comboBox_pattern_line_trap_11_falloff_profile->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Strak (smooth)", nullptr));
        comboBox_pattern_line_trap_11_falloff_profile->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hard (lineair)", nullptr));
        comboBox_pattern_line_trap_11_falloff_profile->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Exponentieel", nullptr));

        label_pattern_line_11_side->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Zichtbare kant", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_11_side->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek: gloed aan beide zijden van de vorm (klassiek). Alleen buiten of binnen: \303\251\303\251n zijde van het oppervlak \342\200\224 handig om alleen de silhouet-rand te tonen.", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_11_edge_side->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek (beide)", nullptr));
        comboBox_pattern_line_trap_11_edge_side->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen buiten", nullptr));
        comboBox_pattern_line_trap_11_edge_side->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen binnen", nullptr));

        pushButton_pattern_line_trap_11_place_surface->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op oppervlak (zichtlijn)", nullptr));
        pushButton_pattern_line_trap_11_place_target->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op doelpunt", nullptr));
        groupCheck_pattern_line_trap_12_enabled->setTitle(QCoreApplication::translate("cPatternLinesTrapsPanel", "Lijn 12", nullptr));
        label_pattern_line_12_pos->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Positie", nullptr));
        label_pattern_line_12_rot->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Rot \302\260", nullptr));
        label_pattern_line_12_radius->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal / dikte / rand / max", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_12_radius->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal = profielgrootte. Dikte = schaal van de SDF-band. Rand = afronding hoeken. Max = afstand-limiet voor de gloed (0 = uit in praktijk volgens instelling).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_12_scale->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal / rel. dikte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_12_scale->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal: uniform het dwarsprofiel (YZ). Relatieve dikte: factor op de gloedband t.o.v. Dikte (1 = standaard).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_12_int->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Intensiteit / 3 kleuren", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_12_int->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gradient langs de gloed: kern (kleur 1) \342\206\222 midden (2) \342\206\222 rand (3). Zelfde RGB = effen.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_12_shape->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_12_shape->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Dwarsdoorsnede loodrecht op de as (lokale X).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_12_shape->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Buis (rond)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lint (vlak)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ruit", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(4, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(5, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zeshoek", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(6, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(7, QCoreApplication::translate("cPatternLinesTrapsPanel", "Achthoek", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(8, QCoreApplication::translate("cPatternLinesTrapsPanel", "Squircle", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(9, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(10, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vijfhoek", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(11, QCoreApplication::translate("cPatternLinesTrapsPanel", "Rechthoek", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(12, QCoreApplication::translate("cPatternLinesTrapsPanel", "Capsule", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(13, QCoreApplication::translate("cPatternLinesTrapsPanel", "Driehoek", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(14, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-5 (roos)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(15, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tienhoek", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(16, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=3", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(17, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=6", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(18, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sikkel", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(19, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(20, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(21, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski driehoek", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(22, QCoreApplication::translate("cPatternLinesTrapsPanel", "Koch (1 iter)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(23, QCoreApplication::translate("cPatternLinesTrapsPanel", "Mandelbrot (afstand)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(24, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia (afstand)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(25, QCoreApplication::translate("cPatternLinesTrapsPanel", "Burning ship", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(26, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cantor-achtig", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(27, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pythagoras boom", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(28, QCoreApplication::translate("cPatternLinesTrapsPanel", "Draak (polylijn)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(29, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hilbert (orde 1)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(30, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vicsek (5 blokken)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(31, QCoreApplication::translate("cPatternLinesTrapsPanel", "Griekse kruis", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(32, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(33, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\264 (afstand)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(34, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tricorn (afstand)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(35, QCoreApplication::translate("cPatternLinesTrapsPanel", "3-ary boom (Y)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(36, QCoreApplication::translate("cPatternLinesTrapsPanel", "Peano-achtig (8\303\227)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(37, QCoreApplication::translate("cPatternLinesTrapsPanel", "Levy C (1 iter)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(38, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-Cantor", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(39, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gouden L-vorm", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(40, QCoreApplication::translate("cPatternLinesTrapsPanel", "3 cirkels (Apollonius)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(41, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lissajous 2:3", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(42, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(43, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\265 (afstand)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(44, QCoreApplication::translate("cPatternLinesTrapsPanel", "H-boom (1 iter)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(45, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt (2 niv.)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(46, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zes-lob rimpel", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(47, QCoreApplication::translate("cPatternLinesTrapsPanel", "Binaire boom (2 niv.)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(48, QCoreApplication::translate("cPatternLinesTrapsPanel", "Fermat-spiraal", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(49, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dubbel kruis", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(50, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hendecagon (11-hoek)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(51, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dodecagon (12-hoek)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(52, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tetradecagon (14-hoek)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(53, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hexadecagon (16-hoek)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(54, QCoreApplication::translate("cPatternLinesTrapsPanel", "Icosagon (20-hoek)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(55, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-6 (hexagram)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(56, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-7", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(57, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-8", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(58, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-9", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(59, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-10", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(60, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-12", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(61, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-16", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(62, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-3", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(63, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-4", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(64, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-6", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(65, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-7", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(66, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-8", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(67, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-10", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(68, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-12", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(69, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-16", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(70, QCoreApplication::translate("cPatternLinesTrapsPanel", "Heptagon (7-hoek)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(71, QCoreApplication::translate("cPatternLinesTrapsPanel", "Enneagon (9-hoek)", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(72, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-6", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(73, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-8", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(74, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-10", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(75, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-12", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(76, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-16", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(77, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-20", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(78, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hart", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(79, QCoreApplication::translate("cPatternLinesTrapsPanel", "Infinity", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(80, QCoreApplication::translate("cPatternLinesTrapsPanel", "Druppel", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(81, QCoreApplication::translate("cPatternLinesTrapsPanel", "Oog", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(82, QCoreApplication::translate("cPatternLinesTrapsPanel", "Maan", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(83, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pijl", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(84, QCoreApplication::translate("cPatternLinesTrapsPanel", "Bliksem", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(85, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sinus-golf", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(86, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zaagtand", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(87, QCoreApplication::translate("cPatternLinesTrapsPanel", "Block-golf", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(88, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 60\302\260", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(89, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 90\302\260", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(90, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 120\302\260", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(91, QCoreApplication::translate("cPatternLinesTrapsPanel", "Halve cirkel", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(92, QCoreApplication::translate("cPatternLinesTrapsPanel", "Taartpunt", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(93, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis met bol", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(94, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-kruis", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(95, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant met kruis", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(96, QCoreApplication::translate("cPatternLinesTrapsPanel", "Target", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(97, QCoreApplication::translate("cPatternLinesTrapsPanel", "Genestelde vierkanten", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(98, QCoreApplication::translate("cPatternLinesTrapsPanel", "Meander", nullptr));
        comboBox_pattern_line_trap_12_shape->setItemText(99, QCoreApplication::translate("cPatternLinesTrapsPanel", "Spiraal", nullptr));

        label_pattern_line_12_shape_aux->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel extra", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_12_shape_aux->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal: Z-straal t.o.v. Y (1 = cirkel). Ring: halve dikte van de buis.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_12_sharp_seg->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte / lengte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_12_sharp_seg->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte: sterkere piek (hoger = smallere gloed). Lengte: halve lijnlengte langs X (0 = oneindig). Zie ook \302\253Gloed / rand\302\273.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_12_glow->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloed / rand", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_12_glow->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloedbreedte: hoger = zachtere, bredere rand. Falloff: Gauss, smoothstep, lineair, exponentieel \342\200\224 bepaalt hoe snel het uitsterft (los van de 3-kleur-gradient).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_12_falloff_profile->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gauss (zacht)", nullptr));
        comboBox_pattern_line_trap_12_falloff_profile->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Strak (smooth)", nullptr));
        comboBox_pattern_line_trap_12_falloff_profile->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hard (lineair)", nullptr));
        comboBox_pattern_line_trap_12_falloff_profile->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Exponentieel", nullptr));

        label_pattern_line_12_side->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Zichtbare kant", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_12_side->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek: gloed aan beide zijden van de vorm (klassiek). Alleen buiten of binnen: \303\251\303\251n zijde van het oppervlak \342\200\224 handig om alleen de silhouet-rand te tonen.", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_12_edge_side->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek (beide)", nullptr));
        comboBox_pattern_line_trap_12_edge_side->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen buiten", nullptr));
        comboBox_pattern_line_trap_12_edge_side->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen binnen", nullptr));

        pushButton_pattern_line_trap_12_place_surface->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op oppervlak (zichtlijn)", nullptr));
        pushButton_pattern_line_trap_12_place_target->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op doelpunt", nullptr));
        groupCheck_pattern_line_trap_13_enabled->setTitle(QCoreApplication::translate("cPatternLinesTrapsPanel", "Lijn 13", nullptr));
        label_pattern_line_13_pos->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Positie", nullptr));
        label_pattern_line_13_rot->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Rot \302\260", nullptr));
        label_pattern_line_13_radius->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal / dikte / rand / max", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_13_radius->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal = profielgrootte. Dikte = schaal van de SDF-band. Rand = afronding hoeken. Max = afstand-limiet voor de gloed (0 = uit in praktijk volgens instelling).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_13_scale->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal / rel. dikte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_13_scale->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal: uniform het dwarsprofiel (YZ). Relatieve dikte: factor op de gloedband t.o.v. Dikte (1 = standaard).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_13_int->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Intensiteit / 3 kleuren", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_13_int->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gradient langs de gloed: kern (kleur 1) \342\206\222 midden (2) \342\206\222 rand (3). Zelfde RGB = effen.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_13_shape->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_13_shape->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Dwarsdoorsnede loodrecht op de as (lokale X).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_13_shape->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Buis (rond)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lint (vlak)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ruit", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(4, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(5, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zeshoek", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(6, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(7, QCoreApplication::translate("cPatternLinesTrapsPanel", "Achthoek", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(8, QCoreApplication::translate("cPatternLinesTrapsPanel", "Squircle", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(9, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(10, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vijfhoek", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(11, QCoreApplication::translate("cPatternLinesTrapsPanel", "Rechthoek", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(12, QCoreApplication::translate("cPatternLinesTrapsPanel", "Capsule", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(13, QCoreApplication::translate("cPatternLinesTrapsPanel", "Driehoek", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(14, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-5 (roos)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(15, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tienhoek", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(16, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=3", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(17, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=6", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(18, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sikkel", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(19, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(20, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(21, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski driehoek", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(22, QCoreApplication::translate("cPatternLinesTrapsPanel", "Koch (1 iter)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(23, QCoreApplication::translate("cPatternLinesTrapsPanel", "Mandelbrot (afstand)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(24, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia (afstand)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(25, QCoreApplication::translate("cPatternLinesTrapsPanel", "Burning ship", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(26, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cantor-achtig", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(27, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pythagoras boom", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(28, QCoreApplication::translate("cPatternLinesTrapsPanel", "Draak (polylijn)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(29, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hilbert (orde 1)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(30, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vicsek (5 blokken)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(31, QCoreApplication::translate("cPatternLinesTrapsPanel", "Griekse kruis", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(32, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(33, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\264 (afstand)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(34, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tricorn (afstand)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(35, QCoreApplication::translate("cPatternLinesTrapsPanel", "3-ary boom (Y)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(36, QCoreApplication::translate("cPatternLinesTrapsPanel", "Peano-achtig (8\303\227)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(37, QCoreApplication::translate("cPatternLinesTrapsPanel", "Levy C (1 iter)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(38, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-Cantor", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(39, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gouden L-vorm", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(40, QCoreApplication::translate("cPatternLinesTrapsPanel", "3 cirkels (Apollonius)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(41, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lissajous 2:3", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(42, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(43, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\265 (afstand)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(44, QCoreApplication::translate("cPatternLinesTrapsPanel", "H-boom (1 iter)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(45, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt (2 niv.)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(46, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zes-lob rimpel", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(47, QCoreApplication::translate("cPatternLinesTrapsPanel", "Binaire boom (2 niv.)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(48, QCoreApplication::translate("cPatternLinesTrapsPanel", "Fermat-spiraal", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(49, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dubbel kruis", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(50, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hendecagon (11-hoek)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(51, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dodecagon (12-hoek)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(52, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tetradecagon (14-hoek)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(53, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hexadecagon (16-hoek)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(54, QCoreApplication::translate("cPatternLinesTrapsPanel", "Icosagon (20-hoek)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(55, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-6 (hexagram)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(56, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-7", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(57, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-8", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(58, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-9", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(59, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-10", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(60, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-12", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(61, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-16", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(62, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-3", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(63, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-4", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(64, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-6", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(65, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-7", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(66, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-8", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(67, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-10", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(68, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-12", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(69, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-16", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(70, QCoreApplication::translate("cPatternLinesTrapsPanel", "Heptagon (7-hoek)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(71, QCoreApplication::translate("cPatternLinesTrapsPanel", "Enneagon (9-hoek)", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(72, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-6", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(73, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-8", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(74, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-10", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(75, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-12", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(76, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-16", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(77, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-20", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(78, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hart", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(79, QCoreApplication::translate("cPatternLinesTrapsPanel", "Infinity", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(80, QCoreApplication::translate("cPatternLinesTrapsPanel", "Druppel", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(81, QCoreApplication::translate("cPatternLinesTrapsPanel", "Oog", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(82, QCoreApplication::translate("cPatternLinesTrapsPanel", "Maan", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(83, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pijl", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(84, QCoreApplication::translate("cPatternLinesTrapsPanel", "Bliksem", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(85, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sinus-golf", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(86, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zaagtand", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(87, QCoreApplication::translate("cPatternLinesTrapsPanel", "Block-golf", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(88, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 60\302\260", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(89, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 90\302\260", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(90, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 120\302\260", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(91, QCoreApplication::translate("cPatternLinesTrapsPanel", "Halve cirkel", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(92, QCoreApplication::translate("cPatternLinesTrapsPanel", "Taartpunt", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(93, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis met bol", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(94, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-kruis", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(95, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant met kruis", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(96, QCoreApplication::translate("cPatternLinesTrapsPanel", "Target", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(97, QCoreApplication::translate("cPatternLinesTrapsPanel", "Genestelde vierkanten", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(98, QCoreApplication::translate("cPatternLinesTrapsPanel", "Meander", nullptr));
        comboBox_pattern_line_trap_13_shape->setItemText(99, QCoreApplication::translate("cPatternLinesTrapsPanel", "Spiraal", nullptr));

        label_pattern_line_13_shape_aux->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel extra", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_13_shape_aux->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal: Z-straal t.o.v. Y (1 = cirkel). Ring: halve dikte van de buis.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_13_sharp_seg->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte / lengte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_13_sharp_seg->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte: sterkere piek (hoger = smallere gloed). Lengte: halve lijnlengte langs X (0 = oneindig). Zie ook \302\253Gloed / rand\302\273.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_13_glow->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloed / rand", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_13_glow->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloedbreedte: hoger = zachtere, bredere rand. Falloff: Gauss, smoothstep, lineair, exponentieel \342\200\224 bepaalt hoe snel het uitsterft (los van de 3-kleur-gradient).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_13_falloff_profile->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gauss (zacht)", nullptr));
        comboBox_pattern_line_trap_13_falloff_profile->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Strak (smooth)", nullptr));
        comboBox_pattern_line_trap_13_falloff_profile->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hard (lineair)", nullptr));
        comboBox_pattern_line_trap_13_falloff_profile->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Exponentieel", nullptr));

        label_pattern_line_13_side->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Zichtbare kant", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_13_side->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek: gloed aan beide zijden van de vorm (klassiek). Alleen buiten of binnen: \303\251\303\251n zijde van het oppervlak \342\200\224 handig om alleen de silhouet-rand te tonen.", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_13_edge_side->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek (beide)", nullptr));
        comboBox_pattern_line_trap_13_edge_side->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen buiten", nullptr));
        comboBox_pattern_line_trap_13_edge_side->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen binnen", nullptr));

        pushButton_pattern_line_trap_13_place_surface->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op oppervlak (zichtlijn)", nullptr));
        pushButton_pattern_line_trap_13_place_target->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op doelpunt", nullptr));
        groupCheck_pattern_line_trap_14_enabled->setTitle(QCoreApplication::translate("cPatternLinesTrapsPanel", "Lijn 14", nullptr));
        label_pattern_line_14_pos->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Positie", nullptr));
        label_pattern_line_14_rot->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Rot \302\260", nullptr));
        label_pattern_line_14_radius->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal / dikte / rand / max", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_14_radius->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal = profielgrootte. Dikte = schaal van de SDF-band. Rand = afronding hoeken. Max = afstand-limiet voor de gloed (0 = uit in praktijk volgens instelling).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_14_scale->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal / rel. dikte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_14_scale->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal: uniform het dwarsprofiel (YZ). Relatieve dikte: factor op de gloedband t.o.v. Dikte (1 = standaard).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_14_int->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Intensiteit / 3 kleuren", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_14_int->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gradient langs de gloed: kern (kleur 1) \342\206\222 midden (2) \342\206\222 rand (3). Zelfde RGB = effen.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_14_shape->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_14_shape->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Dwarsdoorsnede loodrecht op de as (lokale X).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_14_shape->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Buis (rond)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lint (vlak)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ruit", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(4, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(5, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zeshoek", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(6, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(7, QCoreApplication::translate("cPatternLinesTrapsPanel", "Achthoek", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(8, QCoreApplication::translate("cPatternLinesTrapsPanel", "Squircle", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(9, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(10, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vijfhoek", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(11, QCoreApplication::translate("cPatternLinesTrapsPanel", "Rechthoek", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(12, QCoreApplication::translate("cPatternLinesTrapsPanel", "Capsule", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(13, QCoreApplication::translate("cPatternLinesTrapsPanel", "Driehoek", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(14, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-5 (roos)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(15, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tienhoek", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(16, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=3", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(17, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=6", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(18, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sikkel", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(19, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(20, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(21, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski driehoek", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(22, QCoreApplication::translate("cPatternLinesTrapsPanel", "Koch (1 iter)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(23, QCoreApplication::translate("cPatternLinesTrapsPanel", "Mandelbrot (afstand)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(24, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia (afstand)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(25, QCoreApplication::translate("cPatternLinesTrapsPanel", "Burning ship", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(26, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cantor-achtig", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(27, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pythagoras boom", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(28, QCoreApplication::translate("cPatternLinesTrapsPanel", "Draak (polylijn)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(29, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hilbert (orde 1)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(30, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vicsek (5 blokken)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(31, QCoreApplication::translate("cPatternLinesTrapsPanel", "Griekse kruis", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(32, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(33, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\264 (afstand)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(34, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tricorn (afstand)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(35, QCoreApplication::translate("cPatternLinesTrapsPanel", "3-ary boom (Y)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(36, QCoreApplication::translate("cPatternLinesTrapsPanel", "Peano-achtig (8\303\227)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(37, QCoreApplication::translate("cPatternLinesTrapsPanel", "Levy C (1 iter)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(38, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-Cantor", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(39, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gouden L-vorm", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(40, QCoreApplication::translate("cPatternLinesTrapsPanel", "3 cirkels (Apollonius)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(41, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lissajous 2:3", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(42, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(43, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\265 (afstand)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(44, QCoreApplication::translate("cPatternLinesTrapsPanel", "H-boom (1 iter)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(45, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt (2 niv.)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(46, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zes-lob rimpel", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(47, QCoreApplication::translate("cPatternLinesTrapsPanel", "Binaire boom (2 niv.)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(48, QCoreApplication::translate("cPatternLinesTrapsPanel", "Fermat-spiraal", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(49, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dubbel kruis", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(50, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hendecagon (11-hoek)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(51, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dodecagon (12-hoek)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(52, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tetradecagon (14-hoek)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(53, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hexadecagon (16-hoek)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(54, QCoreApplication::translate("cPatternLinesTrapsPanel", "Icosagon (20-hoek)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(55, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-6 (hexagram)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(56, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-7", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(57, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-8", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(58, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-9", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(59, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-10", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(60, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-12", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(61, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-16", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(62, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-3", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(63, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-4", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(64, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-6", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(65, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-7", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(66, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-8", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(67, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-10", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(68, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-12", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(69, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-16", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(70, QCoreApplication::translate("cPatternLinesTrapsPanel", "Heptagon (7-hoek)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(71, QCoreApplication::translate("cPatternLinesTrapsPanel", "Enneagon (9-hoek)", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(72, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-6", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(73, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-8", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(74, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-10", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(75, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-12", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(76, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-16", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(77, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-20", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(78, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hart", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(79, QCoreApplication::translate("cPatternLinesTrapsPanel", "Infinity", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(80, QCoreApplication::translate("cPatternLinesTrapsPanel", "Druppel", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(81, QCoreApplication::translate("cPatternLinesTrapsPanel", "Oog", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(82, QCoreApplication::translate("cPatternLinesTrapsPanel", "Maan", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(83, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pijl", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(84, QCoreApplication::translate("cPatternLinesTrapsPanel", "Bliksem", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(85, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sinus-golf", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(86, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zaagtand", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(87, QCoreApplication::translate("cPatternLinesTrapsPanel", "Block-golf", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(88, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 60\302\260", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(89, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 90\302\260", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(90, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 120\302\260", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(91, QCoreApplication::translate("cPatternLinesTrapsPanel", "Halve cirkel", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(92, QCoreApplication::translate("cPatternLinesTrapsPanel", "Taartpunt", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(93, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis met bol", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(94, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-kruis", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(95, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant met kruis", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(96, QCoreApplication::translate("cPatternLinesTrapsPanel", "Target", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(97, QCoreApplication::translate("cPatternLinesTrapsPanel", "Genestelde vierkanten", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(98, QCoreApplication::translate("cPatternLinesTrapsPanel", "Meander", nullptr));
        comboBox_pattern_line_trap_14_shape->setItemText(99, QCoreApplication::translate("cPatternLinesTrapsPanel", "Spiraal", nullptr));

        label_pattern_line_14_shape_aux->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel extra", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_14_shape_aux->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal: Z-straal t.o.v. Y (1 = cirkel). Ring: halve dikte van de buis.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_14_sharp_seg->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte / lengte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_14_sharp_seg->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte: sterkere piek (hoger = smallere gloed). Lengte: halve lijnlengte langs X (0 = oneindig). Zie ook \302\253Gloed / rand\302\273.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_14_glow->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloed / rand", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_14_glow->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloedbreedte: hoger = zachtere, bredere rand. Falloff: Gauss, smoothstep, lineair, exponentieel \342\200\224 bepaalt hoe snel het uitsterft (los van de 3-kleur-gradient).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_14_falloff_profile->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gauss (zacht)", nullptr));
        comboBox_pattern_line_trap_14_falloff_profile->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Strak (smooth)", nullptr));
        comboBox_pattern_line_trap_14_falloff_profile->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hard (lineair)", nullptr));
        comboBox_pattern_line_trap_14_falloff_profile->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Exponentieel", nullptr));

        label_pattern_line_14_side->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Zichtbare kant", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_14_side->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek: gloed aan beide zijden van de vorm (klassiek). Alleen buiten of binnen: \303\251\303\251n zijde van het oppervlak \342\200\224 handig om alleen de silhouet-rand te tonen.", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_14_edge_side->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek (beide)", nullptr));
        comboBox_pattern_line_trap_14_edge_side->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen buiten", nullptr));
        comboBox_pattern_line_trap_14_edge_side->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen binnen", nullptr));

        pushButton_pattern_line_trap_14_place_surface->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op oppervlak (zichtlijn)", nullptr));
        pushButton_pattern_line_trap_14_place_target->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op doelpunt", nullptr));
        groupCheck_pattern_line_trap_15_enabled->setTitle(QCoreApplication::translate("cPatternLinesTrapsPanel", "Lijn 15", nullptr));
        label_pattern_line_15_pos->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Positie", nullptr));
        label_pattern_line_15_rot->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Rot \302\260", nullptr));
        label_pattern_line_15_radius->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal / dikte / rand / max", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_15_radius->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal = profielgrootte. Dikte = schaal van de SDF-band. Rand = afronding hoeken. Max = afstand-limiet voor de gloed (0 = uit in praktijk volgens instelling).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_15_scale->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal / rel. dikte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_15_scale->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal: uniform het dwarsprofiel (YZ). Relatieve dikte: factor op de gloedband t.o.v. Dikte (1 = standaard).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_15_int->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Intensiteit / 3 kleuren", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_15_int->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gradient langs de gloed: kern (kleur 1) \342\206\222 midden (2) \342\206\222 rand (3). Zelfde RGB = effen.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_15_shape->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_15_shape->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Dwarsdoorsnede loodrecht op de as (lokale X).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_15_shape->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Buis (rond)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lint (vlak)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ruit", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(4, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(5, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zeshoek", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(6, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(7, QCoreApplication::translate("cPatternLinesTrapsPanel", "Achthoek", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(8, QCoreApplication::translate("cPatternLinesTrapsPanel", "Squircle", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(9, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(10, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vijfhoek", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(11, QCoreApplication::translate("cPatternLinesTrapsPanel", "Rechthoek", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(12, QCoreApplication::translate("cPatternLinesTrapsPanel", "Capsule", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(13, QCoreApplication::translate("cPatternLinesTrapsPanel", "Driehoek", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(14, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-5 (roos)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(15, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tienhoek", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(16, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=3", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(17, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=6", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(18, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sikkel", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(19, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(20, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(21, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski driehoek", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(22, QCoreApplication::translate("cPatternLinesTrapsPanel", "Koch (1 iter)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(23, QCoreApplication::translate("cPatternLinesTrapsPanel", "Mandelbrot (afstand)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(24, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia (afstand)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(25, QCoreApplication::translate("cPatternLinesTrapsPanel", "Burning ship", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(26, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cantor-achtig", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(27, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pythagoras boom", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(28, QCoreApplication::translate("cPatternLinesTrapsPanel", "Draak (polylijn)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(29, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hilbert (orde 1)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(30, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vicsek (5 blokken)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(31, QCoreApplication::translate("cPatternLinesTrapsPanel", "Griekse kruis", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(32, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(33, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\264 (afstand)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(34, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tricorn (afstand)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(35, QCoreApplication::translate("cPatternLinesTrapsPanel", "3-ary boom (Y)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(36, QCoreApplication::translate("cPatternLinesTrapsPanel", "Peano-achtig (8\303\227)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(37, QCoreApplication::translate("cPatternLinesTrapsPanel", "Levy C (1 iter)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(38, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-Cantor", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(39, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gouden L-vorm", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(40, QCoreApplication::translate("cPatternLinesTrapsPanel", "3 cirkels (Apollonius)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(41, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lissajous 2:3", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(42, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(43, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\265 (afstand)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(44, QCoreApplication::translate("cPatternLinesTrapsPanel", "H-boom (1 iter)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(45, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt (2 niv.)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(46, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zes-lob rimpel", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(47, QCoreApplication::translate("cPatternLinesTrapsPanel", "Binaire boom (2 niv.)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(48, QCoreApplication::translate("cPatternLinesTrapsPanel", "Fermat-spiraal", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(49, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dubbel kruis", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(50, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hendecagon (11-hoek)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(51, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dodecagon (12-hoek)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(52, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tetradecagon (14-hoek)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(53, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hexadecagon (16-hoek)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(54, QCoreApplication::translate("cPatternLinesTrapsPanel", "Icosagon (20-hoek)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(55, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-6 (hexagram)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(56, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-7", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(57, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-8", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(58, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-9", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(59, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-10", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(60, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-12", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(61, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-16", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(62, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-3", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(63, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-4", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(64, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-6", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(65, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-7", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(66, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-8", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(67, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-10", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(68, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-12", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(69, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-16", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(70, QCoreApplication::translate("cPatternLinesTrapsPanel", "Heptagon (7-hoek)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(71, QCoreApplication::translate("cPatternLinesTrapsPanel", "Enneagon (9-hoek)", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(72, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-6", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(73, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-8", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(74, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-10", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(75, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-12", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(76, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-16", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(77, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-20", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(78, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hart", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(79, QCoreApplication::translate("cPatternLinesTrapsPanel", "Infinity", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(80, QCoreApplication::translate("cPatternLinesTrapsPanel", "Druppel", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(81, QCoreApplication::translate("cPatternLinesTrapsPanel", "Oog", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(82, QCoreApplication::translate("cPatternLinesTrapsPanel", "Maan", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(83, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pijl", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(84, QCoreApplication::translate("cPatternLinesTrapsPanel", "Bliksem", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(85, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sinus-golf", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(86, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zaagtand", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(87, QCoreApplication::translate("cPatternLinesTrapsPanel", "Block-golf", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(88, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 60\302\260", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(89, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 90\302\260", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(90, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 120\302\260", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(91, QCoreApplication::translate("cPatternLinesTrapsPanel", "Halve cirkel", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(92, QCoreApplication::translate("cPatternLinesTrapsPanel", "Taartpunt", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(93, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis met bol", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(94, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-kruis", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(95, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant met kruis", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(96, QCoreApplication::translate("cPatternLinesTrapsPanel", "Target", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(97, QCoreApplication::translate("cPatternLinesTrapsPanel", "Genestelde vierkanten", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(98, QCoreApplication::translate("cPatternLinesTrapsPanel", "Meander", nullptr));
        comboBox_pattern_line_trap_15_shape->setItemText(99, QCoreApplication::translate("cPatternLinesTrapsPanel", "Spiraal", nullptr));

        label_pattern_line_15_shape_aux->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel extra", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_15_shape_aux->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal: Z-straal t.o.v. Y (1 = cirkel). Ring: halve dikte van de buis.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_15_sharp_seg->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte / lengte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_15_sharp_seg->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte: sterkere piek (hoger = smallere gloed). Lengte: halve lijnlengte langs X (0 = oneindig). Zie ook \302\253Gloed / rand\302\273.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_15_glow->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloed / rand", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_15_glow->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloedbreedte: hoger = zachtere, bredere rand. Falloff: Gauss, smoothstep, lineair, exponentieel \342\200\224 bepaalt hoe snel het uitsterft (los van de 3-kleur-gradient).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_15_falloff_profile->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gauss (zacht)", nullptr));
        comboBox_pattern_line_trap_15_falloff_profile->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Strak (smooth)", nullptr));
        comboBox_pattern_line_trap_15_falloff_profile->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hard (lineair)", nullptr));
        comboBox_pattern_line_trap_15_falloff_profile->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Exponentieel", nullptr));

        label_pattern_line_15_side->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Zichtbare kant", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_15_side->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek: gloed aan beide zijden van de vorm (klassiek). Alleen buiten of binnen: \303\251\303\251n zijde van het oppervlak \342\200\224 handig om alleen de silhouet-rand te tonen.", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_15_edge_side->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek (beide)", nullptr));
        comboBox_pattern_line_trap_15_edge_side->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen buiten", nullptr));
        comboBox_pattern_line_trap_15_edge_side->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen binnen", nullptr));

        pushButton_pattern_line_trap_15_place_surface->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op oppervlak (zichtlijn)", nullptr));
        pushButton_pattern_line_trap_15_place_target->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op doelpunt", nullptr));
        groupCheck_pattern_line_trap_16_enabled->setTitle(QCoreApplication::translate("cPatternLinesTrapsPanel", "Lijn 16", nullptr));
        label_pattern_line_16_pos->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Positie", nullptr));
        label_pattern_line_16_rot->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Rot \302\260", nullptr));
        label_pattern_line_16_radius->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal / dikte / rand / max", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_16_radius->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal = profielgrootte. Dikte = schaal van de SDF-band. Rand = afronding hoeken. Max = afstand-limiet voor de gloed (0 = uit in praktijk volgens instelling).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_16_scale->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal / rel. dikte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_16_scale->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal: uniform het dwarsprofiel (YZ). Relatieve dikte: factor op de gloedband t.o.v. Dikte (1 = standaard).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_16_int->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Intensiteit / 3 kleuren", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_16_int->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gradient langs de gloed: kern (kleur 1) \342\206\222 midden (2) \342\206\222 rand (3). Zelfde RGB = effen.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_16_shape->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_16_shape->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Dwarsdoorsnede loodrecht op de as (lokale X).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_16_shape->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Buis (rond)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lint (vlak)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ruit", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(4, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(5, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zeshoek", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(6, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(7, QCoreApplication::translate("cPatternLinesTrapsPanel", "Achthoek", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(8, QCoreApplication::translate("cPatternLinesTrapsPanel", "Squircle", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(9, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(10, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vijfhoek", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(11, QCoreApplication::translate("cPatternLinesTrapsPanel", "Rechthoek", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(12, QCoreApplication::translate("cPatternLinesTrapsPanel", "Capsule", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(13, QCoreApplication::translate("cPatternLinesTrapsPanel", "Driehoek", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(14, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-5 (roos)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(15, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tienhoek", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(16, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=3", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(17, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=6", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(18, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sikkel", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(19, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(20, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(21, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski driehoek", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(22, QCoreApplication::translate("cPatternLinesTrapsPanel", "Koch (1 iter)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(23, QCoreApplication::translate("cPatternLinesTrapsPanel", "Mandelbrot (afstand)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(24, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia (afstand)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(25, QCoreApplication::translate("cPatternLinesTrapsPanel", "Burning ship", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(26, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cantor-achtig", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(27, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pythagoras boom", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(28, QCoreApplication::translate("cPatternLinesTrapsPanel", "Draak (polylijn)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(29, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hilbert (orde 1)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(30, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vicsek (5 blokken)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(31, QCoreApplication::translate("cPatternLinesTrapsPanel", "Griekse kruis", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(32, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(33, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\264 (afstand)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(34, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tricorn (afstand)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(35, QCoreApplication::translate("cPatternLinesTrapsPanel", "3-ary boom (Y)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(36, QCoreApplication::translate("cPatternLinesTrapsPanel", "Peano-achtig (8\303\227)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(37, QCoreApplication::translate("cPatternLinesTrapsPanel", "Levy C (1 iter)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(38, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-Cantor", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(39, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gouden L-vorm", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(40, QCoreApplication::translate("cPatternLinesTrapsPanel", "3 cirkels (Apollonius)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(41, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lissajous 2:3", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(42, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(43, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\265 (afstand)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(44, QCoreApplication::translate("cPatternLinesTrapsPanel", "H-boom (1 iter)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(45, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt (2 niv.)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(46, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zes-lob rimpel", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(47, QCoreApplication::translate("cPatternLinesTrapsPanel", "Binaire boom (2 niv.)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(48, QCoreApplication::translate("cPatternLinesTrapsPanel", "Fermat-spiraal", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(49, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dubbel kruis", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(50, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hendecagon (11-hoek)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(51, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dodecagon (12-hoek)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(52, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tetradecagon (14-hoek)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(53, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hexadecagon (16-hoek)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(54, QCoreApplication::translate("cPatternLinesTrapsPanel", "Icosagon (20-hoek)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(55, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-6 (hexagram)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(56, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-7", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(57, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-8", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(58, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-9", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(59, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-10", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(60, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-12", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(61, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-16", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(62, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-3", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(63, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-4", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(64, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-6", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(65, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-7", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(66, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-8", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(67, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-10", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(68, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-12", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(69, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-16", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(70, QCoreApplication::translate("cPatternLinesTrapsPanel", "Heptagon (7-hoek)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(71, QCoreApplication::translate("cPatternLinesTrapsPanel", "Enneagon (9-hoek)", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(72, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-6", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(73, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-8", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(74, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-10", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(75, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-12", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(76, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-16", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(77, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-20", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(78, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hart", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(79, QCoreApplication::translate("cPatternLinesTrapsPanel", "Infinity", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(80, QCoreApplication::translate("cPatternLinesTrapsPanel", "Druppel", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(81, QCoreApplication::translate("cPatternLinesTrapsPanel", "Oog", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(82, QCoreApplication::translate("cPatternLinesTrapsPanel", "Maan", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(83, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pijl", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(84, QCoreApplication::translate("cPatternLinesTrapsPanel", "Bliksem", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(85, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sinus-golf", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(86, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zaagtand", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(87, QCoreApplication::translate("cPatternLinesTrapsPanel", "Block-golf", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(88, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 60\302\260", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(89, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 90\302\260", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(90, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 120\302\260", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(91, QCoreApplication::translate("cPatternLinesTrapsPanel", "Halve cirkel", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(92, QCoreApplication::translate("cPatternLinesTrapsPanel", "Taartpunt", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(93, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis met bol", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(94, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-kruis", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(95, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant met kruis", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(96, QCoreApplication::translate("cPatternLinesTrapsPanel", "Target", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(97, QCoreApplication::translate("cPatternLinesTrapsPanel", "Genestelde vierkanten", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(98, QCoreApplication::translate("cPatternLinesTrapsPanel", "Meander", nullptr));
        comboBox_pattern_line_trap_16_shape->setItemText(99, QCoreApplication::translate("cPatternLinesTrapsPanel", "Spiraal", nullptr));

        label_pattern_line_16_shape_aux->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel extra", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_16_shape_aux->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal: Z-straal t.o.v. Y (1 = cirkel). Ring: halve dikte van de buis.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_16_sharp_seg->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte / lengte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_16_sharp_seg->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte: sterkere piek (hoger = smallere gloed). Lengte: halve lijnlengte langs X (0 = oneindig). Zie ook \302\253Gloed / rand\302\273.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_16_glow->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloed / rand", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_16_glow->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloedbreedte: hoger = zachtere, bredere rand. Falloff: Gauss, smoothstep, lineair, exponentieel \342\200\224 bepaalt hoe snel het uitsterft (los van de 3-kleur-gradient).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_16_falloff_profile->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gauss (zacht)", nullptr));
        comboBox_pattern_line_trap_16_falloff_profile->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Strak (smooth)", nullptr));
        comboBox_pattern_line_trap_16_falloff_profile->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hard (lineair)", nullptr));
        comboBox_pattern_line_trap_16_falloff_profile->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Exponentieel", nullptr));

        label_pattern_line_16_side->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Zichtbare kant", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_16_side->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek: gloed aan beide zijden van de vorm (klassiek). Alleen buiten of binnen: \303\251\303\251n zijde van het oppervlak \342\200\224 handig om alleen de silhouet-rand te tonen.", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_16_edge_side->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek (beide)", nullptr));
        comboBox_pattern_line_trap_16_edge_side->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen buiten", nullptr));
        comboBox_pattern_line_trap_16_edge_side->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen binnen", nullptr));

        pushButton_pattern_line_trap_16_place_surface->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op oppervlak (zichtlijn)", nullptr));
        pushButton_pattern_line_trap_16_place_target->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op doelpunt", nullptr));
        groupCheck_pattern_line_trap_17_enabled->setTitle(QCoreApplication::translate("cPatternLinesTrapsPanel", "Lijn 17", nullptr));
        label_pattern_line_17_pos->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Positie", nullptr));
        label_pattern_line_17_rot->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Rot \302\260", nullptr));
        label_pattern_line_17_radius->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal / dikte / rand / max", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_17_radius->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal = profielgrootte. Dikte = schaal van de SDF-band. Rand = afronding hoeken. Max = afstand-limiet voor de gloed (0 = uit in praktijk volgens instelling).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_17_scale->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal / rel. dikte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_17_scale->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal: uniform het dwarsprofiel (YZ). Relatieve dikte: factor op de gloedband t.o.v. Dikte (1 = standaard).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_17_int->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Intensiteit / 3 kleuren", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_17_int->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gradient langs de gloed: kern (kleur 1) \342\206\222 midden (2) \342\206\222 rand (3). Zelfde RGB = effen.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_17_shape->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_17_shape->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Dwarsdoorsnede loodrecht op de as (lokale X).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_17_shape->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Buis (rond)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lint (vlak)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ruit", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(4, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(5, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zeshoek", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(6, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(7, QCoreApplication::translate("cPatternLinesTrapsPanel", "Achthoek", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(8, QCoreApplication::translate("cPatternLinesTrapsPanel", "Squircle", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(9, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(10, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vijfhoek", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(11, QCoreApplication::translate("cPatternLinesTrapsPanel", "Rechthoek", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(12, QCoreApplication::translate("cPatternLinesTrapsPanel", "Capsule", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(13, QCoreApplication::translate("cPatternLinesTrapsPanel", "Driehoek", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(14, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-5 (roos)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(15, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tienhoek", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(16, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=3", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(17, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=6", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(18, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sikkel", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(19, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(20, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(21, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski driehoek", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(22, QCoreApplication::translate("cPatternLinesTrapsPanel", "Koch (1 iter)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(23, QCoreApplication::translate("cPatternLinesTrapsPanel", "Mandelbrot (afstand)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(24, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia (afstand)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(25, QCoreApplication::translate("cPatternLinesTrapsPanel", "Burning ship", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(26, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cantor-achtig", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(27, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pythagoras boom", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(28, QCoreApplication::translate("cPatternLinesTrapsPanel", "Draak (polylijn)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(29, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hilbert (orde 1)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(30, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vicsek (5 blokken)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(31, QCoreApplication::translate("cPatternLinesTrapsPanel", "Griekse kruis", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(32, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(33, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\264 (afstand)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(34, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tricorn (afstand)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(35, QCoreApplication::translate("cPatternLinesTrapsPanel", "3-ary boom (Y)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(36, QCoreApplication::translate("cPatternLinesTrapsPanel", "Peano-achtig (8\303\227)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(37, QCoreApplication::translate("cPatternLinesTrapsPanel", "Levy C (1 iter)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(38, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-Cantor", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(39, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gouden L-vorm", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(40, QCoreApplication::translate("cPatternLinesTrapsPanel", "3 cirkels (Apollonius)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(41, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lissajous 2:3", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(42, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(43, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\265 (afstand)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(44, QCoreApplication::translate("cPatternLinesTrapsPanel", "H-boom (1 iter)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(45, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt (2 niv.)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(46, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zes-lob rimpel", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(47, QCoreApplication::translate("cPatternLinesTrapsPanel", "Binaire boom (2 niv.)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(48, QCoreApplication::translate("cPatternLinesTrapsPanel", "Fermat-spiraal", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(49, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dubbel kruis", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(50, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hendecagon (11-hoek)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(51, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dodecagon (12-hoek)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(52, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tetradecagon (14-hoek)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(53, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hexadecagon (16-hoek)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(54, QCoreApplication::translate("cPatternLinesTrapsPanel", "Icosagon (20-hoek)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(55, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-6 (hexagram)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(56, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-7", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(57, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-8", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(58, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-9", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(59, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-10", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(60, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-12", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(61, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-16", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(62, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-3", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(63, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-4", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(64, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-6", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(65, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-7", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(66, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-8", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(67, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-10", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(68, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-12", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(69, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-16", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(70, QCoreApplication::translate("cPatternLinesTrapsPanel", "Heptagon (7-hoek)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(71, QCoreApplication::translate("cPatternLinesTrapsPanel", "Enneagon (9-hoek)", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(72, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-6", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(73, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-8", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(74, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-10", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(75, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-12", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(76, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-16", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(77, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-20", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(78, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hart", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(79, QCoreApplication::translate("cPatternLinesTrapsPanel", "Infinity", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(80, QCoreApplication::translate("cPatternLinesTrapsPanel", "Druppel", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(81, QCoreApplication::translate("cPatternLinesTrapsPanel", "Oog", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(82, QCoreApplication::translate("cPatternLinesTrapsPanel", "Maan", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(83, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pijl", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(84, QCoreApplication::translate("cPatternLinesTrapsPanel", "Bliksem", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(85, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sinus-golf", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(86, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zaagtand", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(87, QCoreApplication::translate("cPatternLinesTrapsPanel", "Block-golf", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(88, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 60\302\260", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(89, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 90\302\260", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(90, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 120\302\260", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(91, QCoreApplication::translate("cPatternLinesTrapsPanel", "Halve cirkel", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(92, QCoreApplication::translate("cPatternLinesTrapsPanel", "Taartpunt", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(93, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis met bol", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(94, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-kruis", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(95, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant met kruis", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(96, QCoreApplication::translate("cPatternLinesTrapsPanel", "Target", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(97, QCoreApplication::translate("cPatternLinesTrapsPanel", "Genestelde vierkanten", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(98, QCoreApplication::translate("cPatternLinesTrapsPanel", "Meander", nullptr));
        comboBox_pattern_line_trap_17_shape->setItemText(99, QCoreApplication::translate("cPatternLinesTrapsPanel", "Spiraal", nullptr));

        label_pattern_line_17_shape_aux->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel extra", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_17_shape_aux->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal: Z-straal t.o.v. Y (1 = cirkel). Ring: halve dikte van de buis.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_17_sharp_seg->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte / lengte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_17_sharp_seg->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte: sterkere piek (hoger = smallere gloed). Lengte: halve lijnlengte langs X (0 = oneindig). Zie ook \302\253Gloed / rand\302\273.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_17_glow->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloed / rand", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_17_glow->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloedbreedte: hoger = zachtere, bredere rand. Falloff: Gauss, smoothstep, lineair, exponentieel \342\200\224 bepaalt hoe snel het uitsterft (los van de 3-kleur-gradient).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_17_falloff_profile->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gauss (zacht)", nullptr));
        comboBox_pattern_line_trap_17_falloff_profile->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Strak (smooth)", nullptr));
        comboBox_pattern_line_trap_17_falloff_profile->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hard (lineair)", nullptr));
        comboBox_pattern_line_trap_17_falloff_profile->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Exponentieel", nullptr));

        label_pattern_line_17_side->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Zichtbare kant", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_17_side->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek: gloed aan beide zijden van de vorm (klassiek). Alleen buiten of binnen: \303\251\303\251n zijde van het oppervlak \342\200\224 handig om alleen de silhouet-rand te tonen.", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_17_edge_side->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek (beide)", nullptr));
        comboBox_pattern_line_trap_17_edge_side->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen buiten", nullptr));
        comboBox_pattern_line_trap_17_edge_side->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen binnen", nullptr));

        pushButton_pattern_line_trap_17_place_surface->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op oppervlak (zichtlijn)", nullptr));
        pushButton_pattern_line_trap_17_place_target->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op doelpunt", nullptr));
        groupCheck_pattern_line_trap_18_enabled->setTitle(QCoreApplication::translate("cPatternLinesTrapsPanel", "Lijn 18", nullptr));
        label_pattern_line_18_pos->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Positie", nullptr));
        label_pattern_line_18_rot->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Rot \302\260", nullptr));
        label_pattern_line_18_radius->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal / dikte / rand / max", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_18_radius->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal = profielgrootte. Dikte = schaal van de SDF-band. Rand = afronding hoeken. Max = afstand-limiet voor de gloed (0 = uit in praktijk volgens instelling).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_18_scale->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal / rel. dikte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_18_scale->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal: uniform het dwarsprofiel (YZ). Relatieve dikte: factor op de gloedband t.o.v. Dikte (1 = standaard).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_18_int->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Intensiteit / 3 kleuren", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_18_int->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gradient langs de gloed: kern (kleur 1) \342\206\222 midden (2) \342\206\222 rand (3). Zelfde RGB = effen.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_18_shape->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_18_shape->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Dwarsdoorsnede loodrecht op de as (lokale X).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_18_shape->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Buis (rond)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lint (vlak)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ruit", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(4, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(5, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zeshoek", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(6, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(7, QCoreApplication::translate("cPatternLinesTrapsPanel", "Achthoek", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(8, QCoreApplication::translate("cPatternLinesTrapsPanel", "Squircle", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(9, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(10, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vijfhoek", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(11, QCoreApplication::translate("cPatternLinesTrapsPanel", "Rechthoek", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(12, QCoreApplication::translate("cPatternLinesTrapsPanel", "Capsule", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(13, QCoreApplication::translate("cPatternLinesTrapsPanel", "Driehoek", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(14, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-5 (roos)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(15, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tienhoek", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(16, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=3", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(17, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=6", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(18, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sikkel", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(19, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(20, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(21, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski driehoek", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(22, QCoreApplication::translate("cPatternLinesTrapsPanel", "Koch (1 iter)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(23, QCoreApplication::translate("cPatternLinesTrapsPanel", "Mandelbrot (afstand)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(24, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia (afstand)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(25, QCoreApplication::translate("cPatternLinesTrapsPanel", "Burning ship", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(26, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cantor-achtig", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(27, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pythagoras boom", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(28, QCoreApplication::translate("cPatternLinesTrapsPanel", "Draak (polylijn)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(29, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hilbert (orde 1)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(30, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vicsek (5 blokken)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(31, QCoreApplication::translate("cPatternLinesTrapsPanel", "Griekse kruis", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(32, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(33, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\264 (afstand)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(34, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tricorn (afstand)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(35, QCoreApplication::translate("cPatternLinesTrapsPanel", "3-ary boom (Y)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(36, QCoreApplication::translate("cPatternLinesTrapsPanel", "Peano-achtig (8\303\227)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(37, QCoreApplication::translate("cPatternLinesTrapsPanel", "Levy C (1 iter)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(38, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-Cantor", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(39, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gouden L-vorm", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(40, QCoreApplication::translate("cPatternLinesTrapsPanel", "3 cirkels (Apollonius)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(41, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lissajous 2:3", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(42, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(43, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\265 (afstand)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(44, QCoreApplication::translate("cPatternLinesTrapsPanel", "H-boom (1 iter)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(45, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt (2 niv.)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(46, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zes-lob rimpel", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(47, QCoreApplication::translate("cPatternLinesTrapsPanel", "Binaire boom (2 niv.)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(48, QCoreApplication::translate("cPatternLinesTrapsPanel", "Fermat-spiraal", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(49, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dubbel kruis", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(50, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hendecagon (11-hoek)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(51, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dodecagon (12-hoek)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(52, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tetradecagon (14-hoek)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(53, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hexadecagon (16-hoek)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(54, QCoreApplication::translate("cPatternLinesTrapsPanel", "Icosagon (20-hoek)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(55, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-6 (hexagram)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(56, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-7", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(57, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-8", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(58, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-9", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(59, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-10", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(60, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-12", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(61, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-16", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(62, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-3", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(63, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-4", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(64, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-6", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(65, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-7", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(66, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-8", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(67, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-10", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(68, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-12", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(69, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-16", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(70, QCoreApplication::translate("cPatternLinesTrapsPanel", "Heptagon (7-hoek)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(71, QCoreApplication::translate("cPatternLinesTrapsPanel", "Enneagon (9-hoek)", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(72, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-6", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(73, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-8", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(74, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-10", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(75, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-12", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(76, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-16", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(77, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-20", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(78, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hart", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(79, QCoreApplication::translate("cPatternLinesTrapsPanel", "Infinity", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(80, QCoreApplication::translate("cPatternLinesTrapsPanel", "Druppel", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(81, QCoreApplication::translate("cPatternLinesTrapsPanel", "Oog", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(82, QCoreApplication::translate("cPatternLinesTrapsPanel", "Maan", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(83, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pijl", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(84, QCoreApplication::translate("cPatternLinesTrapsPanel", "Bliksem", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(85, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sinus-golf", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(86, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zaagtand", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(87, QCoreApplication::translate("cPatternLinesTrapsPanel", "Block-golf", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(88, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 60\302\260", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(89, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 90\302\260", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(90, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 120\302\260", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(91, QCoreApplication::translate("cPatternLinesTrapsPanel", "Halve cirkel", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(92, QCoreApplication::translate("cPatternLinesTrapsPanel", "Taartpunt", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(93, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis met bol", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(94, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-kruis", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(95, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant met kruis", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(96, QCoreApplication::translate("cPatternLinesTrapsPanel", "Target", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(97, QCoreApplication::translate("cPatternLinesTrapsPanel", "Genestelde vierkanten", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(98, QCoreApplication::translate("cPatternLinesTrapsPanel", "Meander", nullptr));
        comboBox_pattern_line_trap_18_shape->setItemText(99, QCoreApplication::translate("cPatternLinesTrapsPanel", "Spiraal", nullptr));

        label_pattern_line_18_shape_aux->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel extra", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_18_shape_aux->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal: Z-straal t.o.v. Y (1 = cirkel). Ring: halve dikte van de buis.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_18_sharp_seg->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte / lengte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_18_sharp_seg->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte: sterkere piek (hoger = smallere gloed). Lengte: halve lijnlengte langs X (0 = oneindig). Zie ook \302\253Gloed / rand\302\273.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_18_glow->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloed / rand", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_18_glow->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloedbreedte: hoger = zachtere, bredere rand. Falloff: Gauss, smoothstep, lineair, exponentieel \342\200\224 bepaalt hoe snel het uitsterft (los van de 3-kleur-gradient).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_18_falloff_profile->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gauss (zacht)", nullptr));
        comboBox_pattern_line_trap_18_falloff_profile->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Strak (smooth)", nullptr));
        comboBox_pattern_line_trap_18_falloff_profile->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hard (lineair)", nullptr));
        comboBox_pattern_line_trap_18_falloff_profile->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Exponentieel", nullptr));

        label_pattern_line_18_side->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Zichtbare kant", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_18_side->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek: gloed aan beide zijden van de vorm (klassiek). Alleen buiten of binnen: \303\251\303\251n zijde van het oppervlak \342\200\224 handig om alleen de silhouet-rand te tonen.", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_18_edge_side->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek (beide)", nullptr));
        comboBox_pattern_line_trap_18_edge_side->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen buiten", nullptr));
        comboBox_pattern_line_trap_18_edge_side->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen binnen", nullptr));

        pushButton_pattern_line_trap_18_place_surface->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op oppervlak (zichtlijn)", nullptr));
        pushButton_pattern_line_trap_18_place_target->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op doelpunt", nullptr));
        groupCheck_pattern_line_trap_19_enabled->setTitle(QCoreApplication::translate("cPatternLinesTrapsPanel", "Lijn 19", nullptr));
        label_pattern_line_19_pos->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Positie", nullptr));
        label_pattern_line_19_rot->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Rot \302\260", nullptr));
        label_pattern_line_19_radius->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal / dikte / rand / max", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_19_radius->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal = profielgrootte. Dikte = schaal van de SDF-band. Rand = afronding hoeken. Max = afstand-limiet voor de gloed (0 = uit in praktijk volgens instelling).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_19_scale->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal / rel. dikte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_19_scale->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal: uniform het dwarsprofiel (YZ). Relatieve dikte: factor op de gloedband t.o.v. Dikte (1 = standaard).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_19_int->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Intensiteit / 3 kleuren", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_19_int->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gradient langs de gloed: kern (kleur 1) \342\206\222 midden (2) \342\206\222 rand (3). Zelfde RGB = effen.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_19_shape->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_19_shape->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Dwarsdoorsnede loodrecht op de as (lokale X).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_19_shape->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Buis (rond)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lint (vlak)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ruit", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(4, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(5, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zeshoek", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(6, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(7, QCoreApplication::translate("cPatternLinesTrapsPanel", "Achthoek", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(8, QCoreApplication::translate("cPatternLinesTrapsPanel", "Squircle", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(9, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(10, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vijfhoek", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(11, QCoreApplication::translate("cPatternLinesTrapsPanel", "Rechthoek", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(12, QCoreApplication::translate("cPatternLinesTrapsPanel", "Capsule", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(13, QCoreApplication::translate("cPatternLinesTrapsPanel", "Driehoek", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(14, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-5 (roos)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(15, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tienhoek", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(16, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=3", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(17, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=6", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(18, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sikkel", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(19, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(20, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(21, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski driehoek", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(22, QCoreApplication::translate("cPatternLinesTrapsPanel", "Koch (1 iter)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(23, QCoreApplication::translate("cPatternLinesTrapsPanel", "Mandelbrot (afstand)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(24, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia (afstand)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(25, QCoreApplication::translate("cPatternLinesTrapsPanel", "Burning ship", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(26, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cantor-achtig", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(27, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pythagoras boom", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(28, QCoreApplication::translate("cPatternLinesTrapsPanel", "Draak (polylijn)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(29, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hilbert (orde 1)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(30, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vicsek (5 blokken)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(31, QCoreApplication::translate("cPatternLinesTrapsPanel", "Griekse kruis", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(32, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(33, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\264 (afstand)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(34, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tricorn (afstand)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(35, QCoreApplication::translate("cPatternLinesTrapsPanel", "3-ary boom (Y)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(36, QCoreApplication::translate("cPatternLinesTrapsPanel", "Peano-achtig (8\303\227)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(37, QCoreApplication::translate("cPatternLinesTrapsPanel", "Levy C (1 iter)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(38, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-Cantor", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(39, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gouden L-vorm", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(40, QCoreApplication::translate("cPatternLinesTrapsPanel", "3 cirkels (Apollonius)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(41, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lissajous 2:3", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(42, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(43, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\265 (afstand)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(44, QCoreApplication::translate("cPatternLinesTrapsPanel", "H-boom (1 iter)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(45, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt (2 niv.)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(46, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zes-lob rimpel", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(47, QCoreApplication::translate("cPatternLinesTrapsPanel", "Binaire boom (2 niv.)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(48, QCoreApplication::translate("cPatternLinesTrapsPanel", "Fermat-spiraal", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(49, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dubbel kruis", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(50, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hendecagon (11-hoek)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(51, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dodecagon (12-hoek)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(52, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tetradecagon (14-hoek)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(53, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hexadecagon (16-hoek)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(54, QCoreApplication::translate("cPatternLinesTrapsPanel", "Icosagon (20-hoek)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(55, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-6 (hexagram)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(56, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-7", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(57, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-8", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(58, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-9", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(59, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-10", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(60, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-12", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(61, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-16", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(62, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-3", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(63, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-4", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(64, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-6", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(65, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-7", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(66, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-8", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(67, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-10", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(68, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-12", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(69, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-16", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(70, QCoreApplication::translate("cPatternLinesTrapsPanel", "Heptagon (7-hoek)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(71, QCoreApplication::translate("cPatternLinesTrapsPanel", "Enneagon (9-hoek)", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(72, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-6", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(73, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-8", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(74, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-10", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(75, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-12", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(76, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-16", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(77, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-20", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(78, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hart", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(79, QCoreApplication::translate("cPatternLinesTrapsPanel", "Infinity", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(80, QCoreApplication::translate("cPatternLinesTrapsPanel", "Druppel", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(81, QCoreApplication::translate("cPatternLinesTrapsPanel", "Oog", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(82, QCoreApplication::translate("cPatternLinesTrapsPanel", "Maan", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(83, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pijl", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(84, QCoreApplication::translate("cPatternLinesTrapsPanel", "Bliksem", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(85, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sinus-golf", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(86, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zaagtand", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(87, QCoreApplication::translate("cPatternLinesTrapsPanel", "Block-golf", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(88, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 60\302\260", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(89, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 90\302\260", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(90, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 120\302\260", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(91, QCoreApplication::translate("cPatternLinesTrapsPanel", "Halve cirkel", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(92, QCoreApplication::translate("cPatternLinesTrapsPanel", "Taartpunt", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(93, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis met bol", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(94, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-kruis", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(95, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant met kruis", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(96, QCoreApplication::translate("cPatternLinesTrapsPanel", "Target", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(97, QCoreApplication::translate("cPatternLinesTrapsPanel", "Genestelde vierkanten", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(98, QCoreApplication::translate("cPatternLinesTrapsPanel", "Meander", nullptr));
        comboBox_pattern_line_trap_19_shape->setItemText(99, QCoreApplication::translate("cPatternLinesTrapsPanel", "Spiraal", nullptr));

        label_pattern_line_19_shape_aux->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel extra", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_19_shape_aux->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal: Z-straal t.o.v. Y (1 = cirkel). Ring: halve dikte van de buis.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_19_sharp_seg->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte / lengte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_19_sharp_seg->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte: sterkere piek (hoger = smallere gloed). Lengte: halve lijnlengte langs X (0 = oneindig). Zie ook \302\253Gloed / rand\302\273.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_19_glow->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloed / rand", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_19_glow->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloedbreedte: hoger = zachtere, bredere rand. Falloff: Gauss, smoothstep, lineair, exponentieel \342\200\224 bepaalt hoe snel het uitsterft (los van de 3-kleur-gradient).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_19_falloff_profile->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gauss (zacht)", nullptr));
        comboBox_pattern_line_trap_19_falloff_profile->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Strak (smooth)", nullptr));
        comboBox_pattern_line_trap_19_falloff_profile->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hard (lineair)", nullptr));
        comboBox_pattern_line_trap_19_falloff_profile->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Exponentieel", nullptr));

        label_pattern_line_19_side->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Zichtbare kant", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_19_side->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek: gloed aan beide zijden van de vorm (klassiek). Alleen buiten of binnen: \303\251\303\251n zijde van het oppervlak \342\200\224 handig om alleen de silhouet-rand te tonen.", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_19_edge_side->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek (beide)", nullptr));
        comboBox_pattern_line_trap_19_edge_side->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen buiten", nullptr));
        comboBox_pattern_line_trap_19_edge_side->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen binnen", nullptr));

        pushButton_pattern_line_trap_19_place_surface->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op oppervlak (zichtlijn)", nullptr));
        pushButton_pattern_line_trap_19_place_target->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op doelpunt", nullptr));
        groupCheck_pattern_line_trap_20_enabled->setTitle(QCoreApplication::translate("cPatternLinesTrapsPanel", "Lijn 20", nullptr));
        label_pattern_line_20_pos->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Positie", nullptr));
        label_pattern_line_20_rot->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Rot \302\260", nullptr));
        label_pattern_line_20_radius->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal / dikte / rand / max", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_20_radius->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Straal = profielgrootte. Dikte = schaal van de SDF-band. Rand = afronding hoeken. Max = afstand-limiet voor de gloed (0 = uit in praktijk volgens instelling).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_20_scale->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal / rel. dikte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_20_scale->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Schaal: uniform het dwarsprofiel (YZ). Relatieve dikte: factor op de gloedband t.o.v. Dikte (1 = standaard).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_20_int->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Intensiteit / 3 kleuren", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_20_int->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gradient langs de gloed: kern (kleur 1) \342\206\222 midden (2) \342\206\222 rand (3). Zelfde RGB = effen.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_20_shape->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_20_shape->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Dwarsdoorsnede loodrecht op de as (lokale X).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_20_shape->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Buis (rond)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lint (vlak)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ruit", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(4, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(5, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zeshoek", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(6, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(7, QCoreApplication::translate("cPatternLinesTrapsPanel", "Achthoek", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(8, QCoreApplication::translate("cPatternLinesTrapsPanel", "Squircle", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(9, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(10, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vijfhoek", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(11, QCoreApplication::translate("cPatternLinesTrapsPanel", "Rechthoek", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(12, QCoreApplication::translate("cPatternLinesTrapsPanel", "Capsule", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(13, QCoreApplication::translate("cPatternLinesTrapsPanel", "Driehoek", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(14, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-5 (roos)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(15, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tienhoek", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(16, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=3", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(17, QCoreApplication::translate("cPatternLinesTrapsPanel", "Superellips n=6", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(18, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sikkel", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(19, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(20, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(21, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski driehoek", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(22, QCoreApplication::translate("cPatternLinesTrapsPanel", "Koch (1 iter)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(23, QCoreApplication::translate("cPatternLinesTrapsPanel", "Mandelbrot (afstand)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(24, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia (afstand)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(25, QCoreApplication::translate("cPatternLinesTrapsPanel", "Burning ship", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(26, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cantor-achtig", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(27, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pythagoras boom", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(28, QCoreApplication::translate("cPatternLinesTrapsPanel", "Draak (polylijn)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(29, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hilbert (orde 1)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(30, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vicsek (5 blokken)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(31, QCoreApplication::translate("cPatternLinesTrapsPanel", "Griekse kruis", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(32, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(33, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\264 (afstand)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(34, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tricorn (afstand)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(35, QCoreApplication::translate("cPatternLinesTrapsPanel", "3-ary boom (Y)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(36, QCoreApplication::translate("cPatternLinesTrapsPanel", "Peano-achtig (8\303\227)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(37, QCoreApplication::translate("cPatternLinesTrapsPanel", "Levy C (1 iter)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(38, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-Cantor", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(39, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gouden L-vorm", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(40, QCoreApplication::translate("cPatternLinesTrapsPanel", "3 cirkels (Apollonius)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(41, QCoreApplication::translate("cPatternLinesTrapsPanel", "Lissajous 2:3", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(42, QCoreApplication::translate("cPatternLinesTrapsPanel", "Julia\302\263 (afstand)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(43, QCoreApplication::translate("cPatternLinesTrapsPanel", "Multibrot\342\201\265 (afstand)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(44, QCoreApplication::translate("cPatternLinesTrapsPanel", "H-boom (1 iter)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(45, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sierpinski tapijt (2 niv.)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(46, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zes-lob rimpel", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(47, QCoreApplication::translate("cPatternLinesTrapsPanel", "Binaire boom (2 niv.)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(48, QCoreApplication::translate("cPatternLinesTrapsPanel", "Fermat-spiraal", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(49, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dubbel kruis", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(50, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hendecagon (11-hoek)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(51, QCoreApplication::translate("cPatternLinesTrapsPanel", "Dodecagon (12-hoek)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(52, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tetradecagon (14-hoek)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(53, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hexadecagon (16-hoek)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(54, QCoreApplication::translate("cPatternLinesTrapsPanel", "Icosagon (20-hoek)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(55, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-6 (hexagram)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(56, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-7", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(57, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-8", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(58, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-9", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(59, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-10", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(60, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-12", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(61, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ster-16", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(62, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-3", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(63, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-4", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(64, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-6", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(65, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-7", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(66, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-8", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(67, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-10", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(68, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-12", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(69, QCoreApplication::translate("cPatternLinesTrapsPanel", "Roos-16", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(70, QCoreApplication::translate("cPatternLinesTrapsPanel", "Heptagon (7-hoek)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(71, QCoreApplication::translate("cPatternLinesTrapsPanel", "Enneagon (9-hoek)", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(72, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-6", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(73, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-8", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(74, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-10", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(75, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-12", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(76, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-16", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(77, QCoreApplication::translate("cPatternLinesTrapsPanel", "Tandwiel-20", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(78, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hart", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(79, QCoreApplication::translate("cPatternLinesTrapsPanel", "Infinity", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(80, QCoreApplication::translate("cPatternLinesTrapsPanel", "Druppel", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(81, QCoreApplication::translate("cPatternLinesTrapsPanel", "Oog", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(82, QCoreApplication::translate("cPatternLinesTrapsPanel", "Maan", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(83, QCoreApplication::translate("cPatternLinesTrapsPanel", "Pijl", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(84, QCoreApplication::translate("cPatternLinesTrapsPanel", "Bliksem", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(85, QCoreApplication::translate("cPatternLinesTrapsPanel", "Sinus-golf", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(86, QCoreApplication::translate("cPatternLinesTrapsPanel", "Zaagtand", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(87, QCoreApplication::translate("cPatternLinesTrapsPanel", "Block-golf", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(88, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 60\302\260", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(89, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 90\302\260", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(90, QCoreApplication::translate("cPatternLinesTrapsPanel", "Cirkel-sektor 120\302\260", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(91, QCoreApplication::translate("cPatternLinesTrapsPanel", "Halve cirkel", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(92, QCoreApplication::translate("cPatternLinesTrapsPanel", "Taartpunt", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(93, QCoreApplication::translate("cPatternLinesTrapsPanel", "Kruis met bol", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(94, QCoreApplication::translate("cPatternLinesTrapsPanel", "Ring-kruis", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(95, QCoreApplication::translate("cPatternLinesTrapsPanel", "Vierkant met kruis", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(96, QCoreApplication::translate("cPatternLinesTrapsPanel", "Target", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(97, QCoreApplication::translate("cPatternLinesTrapsPanel", "Genestelde vierkanten", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(98, QCoreApplication::translate("cPatternLinesTrapsPanel", "Meander", nullptr));
        comboBox_pattern_line_trap_20_shape->setItemText(99, QCoreApplication::translate("cPatternLinesTrapsPanel", "Spiraal", nullptr));

        label_pattern_line_20_shape_aux->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Profiel extra", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_20_shape_aux->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Ovaal: Z-straal t.o.v. Y (1 = cirkel). Ring: halve dikte van de buis.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_20_sharp_seg->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte / lengte", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_20_sharp_seg->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Scherpte: sterkere piek (hoger = smallere gloed). Lengte: halve lijnlengte langs X (0 = oneindig). Zie ook \302\253Gloed / rand\302\273.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_pattern_line_20_glow->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloed / rand", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_20_glow->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Gloedbreedte: hoger = zachtere, bredere rand. Falloff: Gauss, smoothstep, lineair, exponentieel \342\200\224 bepaalt hoe snel het uitsterft (los van de 3-kleur-gradient).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_20_falloff_profile->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Gauss (zacht)", nullptr));
        comboBox_pattern_line_trap_20_falloff_profile->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Strak (smooth)", nullptr));
        comboBox_pattern_line_trap_20_falloff_profile->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Hard (lineair)", nullptr));
        comboBox_pattern_line_trap_20_falloff_profile->setItemText(3, QCoreApplication::translate("cPatternLinesTrapsPanel", "Exponentieel", nullptr));

        label_pattern_line_20_side->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Zichtbare kant", nullptr));
#if QT_CONFIG(tooltip)
        label_pattern_line_20_side->setToolTip(QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek: gloed aan beide zijden van de vorm (klassiek). Alleen buiten of binnen: \303\251\303\251n zijde van het oppervlak \342\200\224 handig om alleen de silhouet-rand te tonen.", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_pattern_line_trap_20_edge_side->setItemText(0, QCoreApplication::translate("cPatternLinesTrapsPanel", "Omtrek (beide)", nullptr));
        comboBox_pattern_line_trap_20_edge_side->setItemText(1, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen buiten", nullptr));
        comboBox_pattern_line_trap_20_edge_side->setItemText(2, QCoreApplication::translate("cPatternLinesTrapsPanel", "Alleen binnen", nullptr));

        pushButton_pattern_line_trap_20_place_surface->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op oppervlak (zichtlijn)", nullptr));
        pushButton_pattern_line_trap_20_place_target->setText(QCoreApplication::translate("cPatternLinesTrapsPanel", "Plaats op doelpunt", nullptr));
        (void)cPatternLinesTrapsPanel;
    } // retranslateUi

};

namespace Ui {
    class cPatternLinesTrapsPanel: public Ui_cPatternLinesTrapsPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATTERN_LINES_TRAPS_PANEL_H
