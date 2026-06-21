/********************************************************************************
** Form generated from reading UI file 'material_editor_panel.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATERIAL_EDITOR_PANEL_H
#define UI_MATERIAL_EDITOR_PANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "file_select_widget.h"
#include "gradient_edit_widget.h"
#include "my_check_box.h"
#include "my_color_button.h"
#include "my_combo_box.h"
#include "my_double_spin_box.h"
#include "my_group_box.h"
#include "my_line_edit.h"
#include "my_spin_box.h"

QT_BEGIN_NAMESPACE

class Ui_cMaterialEditorPanel
{
public:
    QVBoxLayout *verticalLayout_material_editor_panel_root;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_3;
    QVBoxLayout *verticalLayout_2;
    MyGroupBox *groupCheck_use_colors_from_palette;
    QVBoxLayout *verticalLayout_70;
    MyGroupBox *groupCheck_surface_gradient_enable;
    QVBoxLayout *verticalLayout_14;
    cGradientEditWidget *colorpalette_surface_color_gradient;
    QHBoxLayout *horizontalLayout_surface_blend;
    QLabel *label_surface_blend_mode;
    MyComboBox *comboBox_surface_gradient_blend_mode;
    MyCheckBox *checkBox_surface_gradient_mask_enable;
    QLabel *label_surface_gradient_opacity;
    MyDoubleSpinBox *spinbox_surface_gradient_opacity;
    QSpacerItem *horizontalSpacer_surface_blend;
    MyGroupBox *groupCheck_specular_gradient_enable;
    QVBoxLayout *verticalLayout_15;
    cGradientEditWidget *colorpalette_specular_gradient;
    QHBoxLayout *horizontalLayout_specular_opacity;
    MyCheckBox *checkBox_specular_gradient_mask_enable;
    QLabel *label_specular_gradient_opacity;
    MyDoubleSpinBox *spinbox_specular_gradient_opacity;
    QSpacerItem *horizontalSpacer_specular_opacity;
    MyGroupBox *groupCheck_diffuse_gradient_enable;
    QVBoxLayout *verticalLayout_16;
    cGradientEditWidget *colorpalette_diffuse_gradient;
    QHBoxLayout *horizontalLayout_diffuse_opacity;
    MyCheckBox *checkBox_diffuse_gradient_mask_enable;
    QLabel *label_diffuse_gradient_opacity;
    MyDoubleSpinBox *spinbox_diffuse_gradient_opacity;
    QSpacerItem *horizontalSpacer_diffuse_opacity;
    MyGroupBox *groupCheck_luminosity_gradient_enable;
    QVBoxLayout *verticalLayout_17;
    cGradientEditWidget *colorpalette_luminosity_gradient;
    QHBoxLayout *horizontalLayout_luminosity_opacity;
    MyCheckBox *checkBox_luminosity_gradient_mask_enable;
    QLabel *label_luminosity_gradient_opacity;
    MyDoubleSpinBox *spinbox_luminosity_gradient_opacity;
    QSpacerItem *horizontalSpacer_luminosity_opacity;
    MyGroupBox *groupCheck_roughness_gradient_enable;
    QVBoxLayout *verticalLayout_18;
    cGradientEditWidget *colorpalette_roughness_gradient;
    QHBoxLayout *horizontalLayout_roughness_opacity;
    MyCheckBox *checkBox_roughness_gradient_mask_enable;
    QLabel *label_roughness_gradient_opacity;
    MyDoubleSpinBox *spinbox_roughness_gradient_opacity;
    QSpacerItem *horizontalSpacer_roughness_opacity;
    MyGroupBox *groupCheck_reflectance_gradient_enable;
    QVBoxLayout *verticalLayout_19;
    cGradientEditWidget *colorpalette_reflectance_gradient;
    QHBoxLayout *horizontalLayout_reflectance_opacity;
    MyCheckBox *checkBox_reflectance_gradient_mask_enable;
    QLabel *label_reflectance_gradient_opacity;
    MyDoubleSpinBox *spinbox_reflectance_gradient_opacity;
    QSpacerItem *horizontalSpacer_reflectance_opacity;
    MyGroupBox *groupCheck_transparency_gradient_enable;
    QVBoxLayout *verticalLayout_20;
    cGradientEditWidget *colorpalette_transparency_gradient;
    QHBoxLayout *horizontalLayout_transparency_opacity;
    MyCheckBox *checkBox_transparency_gradient_mask_enable;
    QLabel *label_transparency_gradient_opacity;
    MyDoubleSpinBox *spinbox_transparency_gradient_opacity;
    QSpacerItem *horizontalSpacer_transparency_opacity;
    QGroupBox *groupBox_gradient_processing;
    QGridLayout *gridLayout_gradient_processing;
    QLabel *label_gradient_scale;
    MyDoubleSpinBox *spinbox_gradient_scale;
    QLabel *label_gradient_offset;
    MyDoubleSpinBox *spinbox_gradient_offset;
    QLabel *label_gradient_repeat_mode;
    MyComboBox *comboBox_gradient_repeat_mode;
    QLabel *label_gradient_brightness;
    MyDoubleSpinBox *spinbox_gradient_brightness;
    QLabel *label_gradient_contrast;
    MyDoubleSpinBox *spinbox_gradient_contrast;
    QLabel *label_gradient_saturation;
    MyDoubleSpinBox *spinbox_gradient_saturation;
    QLabel *label_gradient_gamma;
    MyDoubleSpinBox *spinbox_gradient_gamma;
    QLabel *label_gradient_color_space;
    MyComboBox *comboBox_gradient_color_space;
    QLabel *label_gradient_noise_amount;
    MyDoubleSpinBox *spinbox_gradient_noise_amount;
    QGridLayout *gridLayout_34;
    QLabel *label_133;
    QLabel *label_357;
    QLabel *label_fractal_coloring_circle_radius;
    MyLineEdit *vect4_fractal_coloring_line_direction_x;
    QFrame *line_4;
    MyLineEdit *vect4_fractal_coloring_line_direction_z;
    QLabel *label_fractal_coloring_line_direction_x;
    QLabel *label_fractal_coloring_line_direction_z;
    MyDoubleSpinBox *spinbox_coloring_speed;
    MyDoubleSpinBox *spinbox_fractal_coloring_sphere_radius;
    MyComboBox *comboBox_fractal_coloring_algorithm;
    QLabel *label_fractal_coloring_line_direction_y;
    QLabel *label_354;
    MyLineEdit *vect4_fractal_coloring_line_direction_y;
    MyDoubleSpinBox *spinbox_coloring_palette_offset;
    QLabel *label_fractal_coloring_line_direction_z_2;
    MyLineEdit *vect4_fractal_coloring_line_direction_w;
    QLabel *label_fractal_coloring_line_direction;
    MyCheckBox *checkBox_fractal_coloring_color_4D_enabled_false;
    MyCheckBox *checkBox_fractal_coloring_color_preV215_false;
    MyGroupBox *groupCheck_fractal_coloring_extra_color_options_false;
    QVBoxLayout *verticalLayout_49;
    QGridLayout *gridLayout;
    QLabel *label_63;
    QGridLayout *gridLayout_32;
    QLabel *label_88;
    MyDoubleSpinBox *spinbox_fractal_coloring_rad_div_de_scale1;
    QLabel *label_89;
    MyDoubleSpinBox *spinbox_fractal_coloring_aux_color_scale1;
    MyDoubleSpinBox *spinbox_fractal_coloring_orbit_trap_scale1;
    QLabel *label_90;
    MyGroupBox *groupCheck_fractal_coloring_extra_color_enabled_false;
    QVBoxLayout *verticalLayout_29;
    QGridLayout *gridLayout_28;
    QLabel *label_64;
    MyDoubleSpinBox *spinbox_fractal_coloring_initial_color_value;
    MyGroupBox *groupCheck_fractal_coloring_init_cond_enabled_false;
    QVBoxLayout *verticalLayout_33;
    QGridLayout *gridLayout_17;
    MyCheckBox *checkBox_fractal_coloring_ic_rad_enabled_false;
    QLabel *label_45;
    QLabel *label_46;
    QLabel *label_43;
    QLabel *label_44;
    MyDoubleSpinBox *spinbox_fractal_coloring_ic_rad_weight;
    MyDoubleSpinBox *spinbox3_fractal_coloring_xyzC_111_z;
    MyCheckBox *checkBox_fractal_coloring_ic_xyz_enabled_false;
    MyDoubleSpinBox *spinbox3_fractal_coloring_xyzC_111_y;
    MyDoubleSpinBox *spinbox3_fractal_coloring_xyzC_111_x;
    MyCheckBox *checkBox_fractal_coloring_ic_fabs_enabled_false;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    MyGroupBox *groupCheck_fractal_coloring_orbit_trap_true;
    QVBoxLayout *verticalLayout_42;
    QLabel *label_78;
    QLabel *label_81;
    QGridLayout *gridLayout_23;
    QLabel *label_62;
    MyDoubleSpinBox *spinbox_fractal_coloring_orbit_trap_weight;
    MyGroupBox *groupCheck_fractal_coloring_aux_color_false;
    QVBoxLayout *verticalLayout_43;
    QLabel *label_83;
    QGridLayout *gridLayout_24;
    QLabel *label_58;
    MyDoubleSpinBox *spinbox_fractal_coloring_aux_color_weight;
    QLabel *label_59;
    MyDoubleSpinBox *spinbox_fractal_coloring_aux_color_hybrid_weight;
    MyGroupBox *groupCheck_fractal_coloring_rad_enabled_false;
    QVBoxLayout *verticalLayout_35;
    MyCheckBox *checkBox_fractal_coloring_rad_div_1e13_false;
    MyCheckBox *checkBox_fractal_coloring_rad_squared_enabled_false;
    QGridLayout *gridLayout_18;
    MyDoubleSpinBox *spinbox_fractal_coloring_rad_weight;
    QLabel *label_52;
    MyGroupBox *groupCheck_fractal_coloring_rad_div_de_enabled_false;
    QVBoxLayout *verticalLayout_36;
    QLabel *label_84;
    MyCheckBox *checkBox_fractal_coloring_rad_div_de_1e13_false;
    MyCheckBox *checkBox_fractal_coloring_rad_div_de_squared_false;
    QGridLayout *gridLayout_19;
    MyDoubleSpinBox *spinbox_fractal_coloring_rad_div_de_weight;
    QLabel *label_53;
    MyGroupBox *groupCheck_fractal_coloring_xyz_bias_enabled_false;
    QVBoxLayout *verticalLayout_32;
    MyCheckBox *checkBox_fractal_coloring_xyz_div_1e13_false;
    QGridLayout *gridLayout_16;
    MyCheckBox *checkBox_fractal_coloring_xyz_x_sqrd_enabled_false;
    MyCheckBox *checkBox_fractal_coloring_xyz_z_sqrd_enabled_false;
    QLabel *label_40;
    MyDoubleSpinBox *spinbox3_fractal_coloring_xyz_000_y;
    MyDoubleSpinBox *spinbox_fractal_coloring_xyz_iter_scale;
    MyCheckBox *checkBox_fractal_coloring_xyz_y_sqrd_enabled_false;
    QLabel *label_35;
    QLabel *label_38;
    MyDoubleSpinBox *spinbox3_fractal_coloring_xyz_000_x;
    QLabel *label_39;
    MyDoubleSpinBox *spinbox3_fractal_coloring_xyz_000_z;
    QLabel *label_36;
    MyCheckBox *checkBox_fractal_coloring_xyz_fabs_enabled_false;
    MyGroupBox *groupCheck_fractal_coloring_iter_group_enabled_false;
    QVBoxLayout *verticalLayout_37;
    QGridLayout *gridLayout_20;
    MyCheckBox *checkBox_fractal_coloring_iter_add_scale_enabled_true;
    MyDoubleSpinBox *spinbox_fractal_coloring_iter_add_scale;
    MyCheckBox *checkBox_fractal_coloring_iter_scale_enabled_false;
    MySpinBox *spinboxInt_fractal_coloring_i_start_value;
    MyDoubleSpinBox *spinbox_fractal_coloring_iter_scale;
    QLabel *label_42;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_7;
    MyGroupBox *groupCheck_fractal_coloring_global_palette_false;
    QVBoxLayout *verticalLayout_41;
    MyGroupBox *groupCheck_fractal_coloring_add_enabled_false;
    QVBoxLayout *verticalLayout_38;
    QGridLayout *gridLayout_11;
    MyDoubleSpinBox *spinbox_fractal_coloring_add_spread;
    QLabel *label_68;
    QLabel *label_76;
    MyDoubleSpinBox *spinbox_fractal_coloring_add_start_value;
    QLabel *label_77;
    MyDoubleSpinBox *spinbox_fractal_coloring_add_max;
    MyGroupBox *groupCheck_fractal_coloring_parab_enabled_false;
    QVBoxLayout *verticalLayout_40;
    QGridLayout *gridLayout_15;
    QLabel *label_79;
    QLabel *label_80;
    MyDoubleSpinBox *spinbox_fractal_coloring_parab_start_value;
    MyDoubleSpinBox *spinbox_fractal_coloring_parab_scale;
    MyGroupBox *groupCheck_fractal_coloring_cos_enabled_false;
    QVBoxLayout *verticalLayout_34;
    QGridLayout *gridLayout_5;
    MyDoubleSpinBox *spinbox_fractal_coloring_cos_add;
    QLabel *label_48;
    QLabel *label_47;
    MyDoubleSpinBox *spinbox_fractal_coloring_cos_start_value;
    QLabel *label_51;
    MyDoubleSpinBox *spinbox_fractal_coloring_cos_period;
    QGridLayout *gridLayout_22;
    MyGroupBox *groupCheck_fractal_coloring_round_enabled_false;
    QVBoxLayout *verticalLayout_39;
    QGridLayout *gridLayout_21;
    MyDoubleSpinBox *spinbox_fractal_coloring_round_scale;
    QLabel *label_57;
    QGridLayout *gridLayout_6;
    QLabel *label_34;
    MyDoubleSpinBox *spinbox_fractal_coloring_min_color_value;
    QLabel *label_37;
    MyDoubleSpinBox *spinbox_fractal_coloring_max_color_value;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_6;
    QGridLayout *gridLayout_8;
    MyColorButton *colorButton_surface_color;
    QLabel *label_56;
    MyGroupBox *groupCheck_use_color_texture;
    QVBoxLayout *verticalLayout_141;
    QGridLayout *gridLayout_95;
    QLabel *label_378;
    QLabel *label_377;
    FileSelectWidget *text_file_color_texture;
    MyDoubleSpinBox *spinbox_color_texture_intensity;
    MyGroupBox *groupCheck_perlin_noise_color_enable;
    QGridLayout *gridLayout_29;
    MyDoubleSpinBox *spinbox_perlin_noise_color_intensity;
    QLabel *label_41;
    MyCheckBox *checkBox_perlin_noise_color_invert;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_2;
    QGridLayout *gridLayout_7;
    QLabel *label_55;
    MyDoubleSpinBox *spinbox_shading;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_9;
    QGridLayout *gridLayout_25;
    QLabel *label_72;
    MyColorButton *colorButton_specular_color;
    MyGroupBox *groupCheck_specular_plastic_enable;
    QVBoxLayout *verticalLayout_146;
    QGridLayout *gridLayout_9;
    MyDoubleSpinBox *spinbox_specular_width;
    MyDoubleSpinBox *spinbox_specular;
    QLabel *label_69;
    QLabel *label_71;
    MyGroupBox *groupCheck_metallic;
    QVBoxLayout *verticalLayout_147;
    QGridLayout *gridLayout_26;
    QLabel *label_85;
    QLabel *label_86;
    MyDoubleSpinBox *spinbox_specular_metallic;
    MyDoubleSpinBox *spinbox_specular_metallic_width;
    QLabel *label_87;
    MyDoubleSpinBox *spinbox_specular_metallic_roughness;
    MyGroupBox *groupCheck_rough_surface;
    QVBoxLayout *verticalLayout_148;
    QGridLayout *gridLayout_27;
    QLabel *label_93;
    MyDoubleSpinBox *spinbox_surface_roughness;
    MyGroupBox *groupCheck_use_roughness_texture;
    QVBoxLayout *verticalLayout_149;
    QGridLayout *gridLayout_101;
    QLabel *label_395;
    QLabel *label_396;
    FileSelectWidget *text_file_roughness_texture;
    MyDoubleSpinBox *spinbox_roughness_texture_intensity;
    MyGroupBox *groupCheck_iridescence_enabled;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *label_75;
    MyDoubleSpinBox *spinbox_iridescence_intensity;
    QLabel *label_82;
    MyDoubleSpinBox *spinbox_iridescence_subsurface_thickness;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_10;
    QGridLayout *gridLayout_10;
    QLabel *label_73;
    MyDoubleSpinBox *spinbox_luminosity;
    QLabel *label_74;
    MyColorButton *colorButton_luminosity_color;
    QLabel *label_94;
    MyDoubleSpinBox *spinbox_luminosity_emissive;
    MyGroupBox *groupCheck_use_luminosity_texture;
    QVBoxLayout *verticalLayout_142;
    QGridLayout *gridLayout_96;
    QLabel *label_379;
    QLabel *label_380;
    FileSelectWidget *text_file_luminosity_texture;
    MyDoubleSpinBox *spinbox_luminosity_texture_intensity;
    MyGroupBox *groupCheck_perlin_noise_luminosity_enable;
    QGridLayout *gridLayout_30;
    MyDoubleSpinBox *spinbox_perlin_noise_luminosity_intensity;
    QLabel *label_49;
    MyCheckBox *checkBox_perlin_noise_luminosity_invert;
    QGroupBox *groupBox_9;
    QVBoxLayout *verticalLayout_11;
    MyCheckBox *checkBox_fresnel_reflectance;
    QGridLayout *gridLayout_12;
    QLabel *label_352;
    MyDoubleSpinBox *spinbox_transparency_index_of_refraction;
    QGroupBox *groupBox_10;
    QVBoxLayout *verticalLayout_12;
    QGridLayout *gridLayout_13;
    MyColorButton *colorButton_reflections_color;
    QLabel *label_70;
    MyDoubleSpinBox *spinbox_reflectance;
    QLabel *label_91;
    MyGroupBox *groupCheck_use_reflectance_texture;
    QVBoxLayout *verticalLayout_150;
    QGridLayout *gridLayout_102;
    QLabel *label_397;
    QLabel *label_398;
    FileSelectWidget *text_file_reflectance_texture;
    MyDoubleSpinBox *spinbox_reflectance_texture_intensity;
    MyGroupBox *groupCheck_perlin_noise_reflectance_enable;
    QGridLayout *gridLayout_33;
    MyDoubleSpinBox *spinbox_perlin_noise_reflectance_intensity;
    QLabel *label_54;
    MyCheckBox *checkBox_perlin_noise_reflectance_invert;
    QGroupBox *groupBox_11;
    QVBoxLayout *verticalLayout_13;
    QGridLayout *gridLayout_14;
    QLabel *label_295;
    MyCheckBox *checkBox_inside_coloring;
    MyColorButton *colorButton_transparency_interior_color;
    MyLineEdit *logedit_transparency_of_interior;
    QLabel *label_92;
    MyDoubleSpinBox *spinbox_transparency_of_surface;
    MyColorButton *colorButton_transparency_color;
    QLabel *label_351;
    QLabel *label_353;
    MyCheckBox *checkBox_subsurface_scattering;
    MyGroupBox *groupCheck_use_transparency_texture;
    QVBoxLayout *verticalLayout_151;
    QGridLayout *gridLayout_103;
    MyDoubleSpinBox *spinbox_transparency_texture_intensity;
    QLabel *label_399;
    QLabel *label_400;
    FileSelectWidget *text_file_transparency_texture;
    MyDoubleSpinBox *spinbox_transparency_texture_intensity_vol;
    QLabel *label_401;
    MyGroupBox *groupCheck_use_transparency_alpha_texture;
    QVBoxLayout *verticalLayout_153;
    QGridLayout *gridLayout_105;
    FileSelectWidget *text_file_transparency_alpha_texture;
    QLabel *label_404;
    QLabel *label_403;
    MyDoubleSpinBox *spinbox_transparency_alpha_texture_intensity;
    QLabel *label_405;
    MyDoubleSpinBox *spinbox_transparency_alpha_texture_intensity_vol;
    MyGroupBox *groupCheck_perlin_noise_transparency_color_enable;
    QGridLayout *gridLayout_35;
    MyDoubleSpinBox *spinbox_perlin_noise_transparency_color_intensity;
    MyCheckBox *checkBox_perlin_noise_transparency_color_invert;
    QLabel *label_60;
    QLabel *label_65;
    MyDoubleSpinBox *spinbox_perlin_noise_transparency_color_intensity_vol;
    MyGroupBox *groupCheck_perlin_noise_transparency_alpha_enable;
    QGridLayout *gridLayout_36;
    QLabel *label_61;
    MyCheckBox *checkBox_perlin_noise_transparency_alpha_invert;
    MyDoubleSpinBox *spinbox_perlin_noise_transparency_alpha_intensity;
    QLabel *label_66;
    MyDoubleSpinBox *spinbox_perlin_noise_transparency_alpha_intensity_vol;
    QLabel *label_5;
    MyGroupBox *groupCheck_use_diffusion_texture;
    QVBoxLayout *verticalLayout_144;
    QGridLayout *gridLayout_98;
    QLabel *label_383;
    QLabel *label_384;
    FileSelectWidget *text_file_diffusion_texture;
    MyDoubleSpinBox *spinbox_diffusion_texture_intensity;
    MyGroupBox *groupCheck_use_normal_map_texture;
    QVBoxLayout *verticalLayout_145;
    QGridLayout *gridLayout_100;
    QLabel *label_394;
    QLabel *label_393;
    MyLineEdit *logedit_normal_map_texture_height;
    FileSelectWidget *text_file_normal_map_texture;
    MyCheckBox *checkBox_normal_map_texture_from_bumpmap;
    MyCheckBox *checkBox_normal_map_texture_invert_green;
    MyGroupBox *groupCheck_use_displacement_texture;
    QVBoxLayout *verticalLayout_143;
    QGridLayout *gridLayout_97;
    QLabel *label_381;
    QLabel *label_382;
    FileSelectWidget *text_file_displacement_texture;
    MyLineEdit *logedit_displacement_texture_height;
    MyGroupBox *groupCheck_perlin_noise_displacement_enable;
    QGridLayout *gridLayout_31;
    QLabel *label_50;
    MyCheckBox *checkBox_perlin_noise_displacement_invert;
    MyLineEdit *logedit_perlin_noise_displacement_intensity;
    QGroupBox *groupBox_texture_options;
    QVBoxLayout *verticalLayout_31;
    MyGroupBox *groupCheck_texture_fractalize;
    QVBoxLayout *verticalLayout_5;
    QLabel *label;
    QGridLayout *gridLayout_3;
    QLabel *label_4;
    QLabel *label_3;
    MyLineEdit *logedit_texture_fractalize_cube_size;
    MySpinBox *spinboxInt_texture_fractalize_start_iteration;
    QLabel *label_fractalize_shape;
    MyComboBox *comboBox_texture_fractalize_shape;
    QGridLayout *gridLayout_99;
    QLabel *label_374;
    QLabel *label_386;
    QLabel *label_376;
    QLabel *label_375;
    QLabel *label_372;
    QLabel *label_388;
    QLabel *label_390;
    MyComboBox *comboBox_texture_mapping_type;
    QLabel *label_373;
    QLabel *label_387;
    QLabel *label_389;
    QLabel *label_391;
    QLabel *label_392;
    MyDoubleSpinBox *spinbox3_texture_center_x;
    MyDoubleSpinBox *spinbox3_texture_center_y;
    MyDoubleSpinBox *spinbox3_texture_center_z;
    MyLineEdit *logvect3_texture_scale_x;
    MyLineEdit *logvect3_texture_scale_y;
    MyLineEdit *logvect3_texture_scale_z;
    MyDoubleSpinBox *spinboxd3_texture_rotation_x;
    MyDoubleSpinBox *spinboxd3_texture_rotation_y;
    MyDoubleSpinBox *spinboxd3_texture_rotation_z;
    QLabel *label_385;
    MyGroupBox *groupCheck_perlin_noise_enable;
    QVBoxLayout *verticalLayout_21;
    QGridLayout *gridLayout_4;
    QLabel *label_402;
    MyLineEdit *vect3_perlin_noise_period_x;
    MyCheckBox *checkBox_perlin_noise_abs;
    MyLineEdit *vect3_perlin_noise_position_offset_y;
    QLabel *label_115;
    QLabel *label_6;
    MyDoubleSpinBox *spinboxd3_perlin_noise_rotation_x;
    MyDoubleSpinBox *spinbox_perlin_noise_value_offset;
    QLabel *label_137;
    QLabel *label_408;
    QLabel *label_136;
    MyLineEdit *vect3_perlin_noise_period_y;
    QLabel *label_7;
    QLabel *label_406;
    MySpinBox *spinboxInt_perlin_noise_iterations;
    QLabel *label_407;
    MyLineEdit *vect3_perlin_noise_position_offset_z;
    MyDoubleSpinBox *spinboxd3_perlin_noise_rotation_y;
    MyLineEdit *vect3_perlin_noise_period_z;
    QLabel *label_135;
    MyLineEdit *vect3_perlin_noise_position_offset_x;
    MyDoubleSpinBox *spinboxd3_perlin_noise_rotation_z;
    QLabel *label_409;
    QFrame *line_13;

    void setupUi(QWidget *cMaterialEditorPanel)
    {
        if (cMaterialEditorPanel->objectName().isEmpty())
            cMaterialEditorPanel->setObjectName(QString::fromUtf8("cMaterialEditorPanel"));
        verticalLayout_material_editor_panel_root = new QVBoxLayout(cMaterialEditorPanel);
        verticalLayout_material_editor_panel_root->setObjectName(QString::fromUtf8("verticalLayout_material_editor_panel_root"));
        verticalLayout_material_editor_panel_root->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(cMaterialEditorPanel);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, -4350, 471, 5463));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents_3);
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(2, 2, 2, 2);
        groupCheck_use_colors_from_palette = new MyGroupBox(scrollAreaWidgetContents_3);
        groupCheck_use_colors_from_palette->setObjectName(QString::fromUtf8("groupCheck_use_colors_from_palette"));
        groupCheck_use_colors_from_palette->setCheckable(true);
        verticalLayout_70 = new QVBoxLayout(groupCheck_use_colors_from_palette);
        verticalLayout_70->setSpacing(2);
        verticalLayout_70->setObjectName(QString::fromUtf8("verticalLayout_70"));
        verticalLayout_70->setContentsMargins(2, 2, 2, 2);
        groupCheck_surface_gradient_enable = new MyGroupBox(groupCheck_use_colors_from_palette);
        groupCheck_surface_gradient_enable->setObjectName(QString::fromUtf8("groupCheck_surface_gradient_enable"));
        groupCheck_surface_gradient_enable->setCheckable(true);
        verticalLayout_14 = new QVBoxLayout(groupCheck_surface_gradient_enable);
        verticalLayout_14->setSpacing(2);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(2, 2, 2, 2);
        colorpalette_surface_color_gradient = new cGradientEditWidget(groupCheck_surface_gradient_enable);
        colorpalette_surface_color_gradient->setObjectName(QString::fromUtf8("colorpalette_surface_color_gradient"));

        verticalLayout_14->addWidget(colorpalette_surface_color_gradient);

        horizontalLayout_surface_blend = new QHBoxLayout();
        horizontalLayout_surface_blend->setObjectName(QString::fromUtf8("horizontalLayout_surface_blend"));
        label_surface_blend_mode = new QLabel(groupCheck_surface_gradient_enable);
        label_surface_blend_mode->setObjectName(QString::fromUtf8("label_surface_blend_mode"));

        horizontalLayout_surface_blend->addWidget(label_surface_blend_mode);

        comboBox_surface_gradient_blend_mode = new MyComboBox(groupCheck_surface_gradient_enable);
        comboBox_surface_gradient_blend_mode->addItem(QString());
        comboBox_surface_gradient_blend_mode->addItem(QString());
        comboBox_surface_gradient_blend_mode->addItem(QString());
        comboBox_surface_gradient_blend_mode->addItem(QString());
        comboBox_surface_gradient_blend_mode->addItem(QString());
        comboBox_surface_gradient_blend_mode->addItem(QString());
        comboBox_surface_gradient_blend_mode->setObjectName(QString::fromUtf8("comboBox_surface_gradient_blend_mode"));

        horizontalLayout_surface_blend->addWidget(comboBox_surface_gradient_blend_mode);

        checkBox_surface_gradient_mask_enable = new MyCheckBox(groupCheck_surface_gradient_enable);
        checkBox_surface_gradient_mask_enable->setObjectName(QString::fromUtf8("checkBox_surface_gradient_mask_enable"));

        horizontalLayout_surface_blend->addWidget(checkBox_surface_gradient_mask_enable);

        label_surface_gradient_opacity = new QLabel(groupCheck_surface_gradient_enable);
        label_surface_gradient_opacity->setObjectName(QString::fromUtf8("label_surface_gradient_opacity"));

        horizontalLayout_surface_blend->addWidget(label_surface_gradient_opacity);

        spinbox_surface_gradient_opacity = new MyDoubleSpinBox(groupCheck_surface_gradient_enable);
        spinbox_surface_gradient_opacity->setObjectName(QString::fromUtf8("spinbox_surface_gradient_opacity"));

        horizontalLayout_surface_blend->addWidget(spinbox_surface_gradient_opacity);

        horizontalSpacer_surface_blend = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_surface_blend->addItem(horizontalSpacer_surface_blend);


        verticalLayout_14->addLayout(horizontalLayout_surface_blend);


        verticalLayout_70->addWidget(groupCheck_surface_gradient_enable);

        groupCheck_specular_gradient_enable = new MyGroupBox(groupCheck_use_colors_from_palette);
        groupCheck_specular_gradient_enable->setObjectName(QString::fromUtf8("groupCheck_specular_gradient_enable"));
        groupCheck_specular_gradient_enable->setCheckable(true);
        verticalLayout_15 = new QVBoxLayout(groupCheck_specular_gradient_enable);
        verticalLayout_15->setSpacing(2);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        verticalLayout_15->setContentsMargins(2, 2, 2, 2);
        colorpalette_specular_gradient = new cGradientEditWidget(groupCheck_specular_gradient_enable);
        colorpalette_specular_gradient->setObjectName(QString::fromUtf8("colorpalette_specular_gradient"));

        verticalLayout_15->addWidget(colorpalette_specular_gradient);

        horizontalLayout_specular_opacity = new QHBoxLayout();
        horizontalLayout_specular_opacity->setObjectName(QString::fromUtf8("horizontalLayout_specular_opacity"));
        checkBox_specular_gradient_mask_enable = new MyCheckBox(groupCheck_specular_gradient_enable);
        checkBox_specular_gradient_mask_enable->setObjectName(QString::fromUtf8("checkBox_specular_gradient_mask_enable"));

        horizontalLayout_specular_opacity->addWidget(checkBox_specular_gradient_mask_enable);

        label_specular_gradient_opacity = new QLabel(groupCheck_specular_gradient_enable);
        label_specular_gradient_opacity->setObjectName(QString::fromUtf8("label_specular_gradient_opacity"));

        horizontalLayout_specular_opacity->addWidget(label_specular_gradient_opacity);

        spinbox_specular_gradient_opacity = new MyDoubleSpinBox(groupCheck_specular_gradient_enable);
        spinbox_specular_gradient_opacity->setObjectName(QString::fromUtf8("spinbox_specular_gradient_opacity"));

        horizontalLayout_specular_opacity->addWidget(spinbox_specular_gradient_opacity);

        horizontalSpacer_specular_opacity = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_specular_opacity->addItem(horizontalSpacer_specular_opacity);


        verticalLayout_15->addLayout(horizontalLayout_specular_opacity);


        verticalLayout_70->addWidget(groupCheck_specular_gradient_enable);

        groupCheck_diffuse_gradient_enable = new MyGroupBox(groupCheck_use_colors_from_palette);
        groupCheck_diffuse_gradient_enable->setObjectName(QString::fromUtf8("groupCheck_diffuse_gradient_enable"));
        groupCheck_diffuse_gradient_enable->setCheckable(true);
        verticalLayout_16 = new QVBoxLayout(groupCheck_diffuse_gradient_enable);
        verticalLayout_16->setSpacing(2);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        verticalLayout_16->setContentsMargins(2, 2, 2, 2);
        colorpalette_diffuse_gradient = new cGradientEditWidget(groupCheck_diffuse_gradient_enable);
        colorpalette_diffuse_gradient->setObjectName(QString::fromUtf8("colorpalette_diffuse_gradient"));

        verticalLayout_16->addWidget(colorpalette_diffuse_gradient);

        horizontalLayout_diffuse_opacity = new QHBoxLayout();
        horizontalLayout_diffuse_opacity->setObjectName(QString::fromUtf8("horizontalLayout_diffuse_opacity"));
        checkBox_diffuse_gradient_mask_enable = new MyCheckBox(groupCheck_diffuse_gradient_enable);
        checkBox_diffuse_gradient_mask_enable->setObjectName(QString::fromUtf8("checkBox_diffuse_gradient_mask_enable"));

        horizontalLayout_diffuse_opacity->addWidget(checkBox_diffuse_gradient_mask_enable);

        label_diffuse_gradient_opacity = new QLabel(groupCheck_diffuse_gradient_enable);
        label_diffuse_gradient_opacity->setObjectName(QString::fromUtf8("label_diffuse_gradient_opacity"));

        horizontalLayout_diffuse_opacity->addWidget(label_diffuse_gradient_opacity);

        spinbox_diffuse_gradient_opacity = new MyDoubleSpinBox(groupCheck_diffuse_gradient_enable);
        spinbox_diffuse_gradient_opacity->setObjectName(QString::fromUtf8("spinbox_diffuse_gradient_opacity"));

        horizontalLayout_diffuse_opacity->addWidget(spinbox_diffuse_gradient_opacity);

        horizontalSpacer_diffuse_opacity = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_diffuse_opacity->addItem(horizontalSpacer_diffuse_opacity);


        verticalLayout_16->addLayout(horizontalLayout_diffuse_opacity);


        verticalLayout_70->addWidget(groupCheck_diffuse_gradient_enable);

        groupCheck_luminosity_gradient_enable = new MyGroupBox(groupCheck_use_colors_from_palette);
        groupCheck_luminosity_gradient_enable->setObjectName(QString::fromUtf8("groupCheck_luminosity_gradient_enable"));
        groupCheck_luminosity_gradient_enable->setCheckable(true);
        verticalLayout_17 = new QVBoxLayout(groupCheck_luminosity_gradient_enable);
        verticalLayout_17->setSpacing(2);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        verticalLayout_17->setContentsMargins(2, 2, 2, 2);
        colorpalette_luminosity_gradient = new cGradientEditWidget(groupCheck_luminosity_gradient_enable);
        colorpalette_luminosity_gradient->setObjectName(QString::fromUtf8("colorpalette_luminosity_gradient"));

        verticalLayout_17->addWidget(colorpalette_luminosity_gradient);

        horizontalLayout_luminosity_opacity = new QHBoxLayout();
        horizontalLayout_luminosity_opacity->setObjectName(QString::fromUtf8("horizontalLayout_luminosity_opacity"));
        checkBox_luminosity_gradient_mask_enable = new MyCheckBox(groupCheck_luminosity_gradient_enable);
        checkBox_luminosity_gradient_mask_enable->setObjectName(QString::fromUtf8("checkBox_luminosity_gradient_mask_enable"));

        horizontalLayout_luminosity_opacity->addWidget(checkBox_luminosity_gradient_mask_enable);

        label_luminosity_gradient_opacity = new QLabel(groupCheck_luminosity_gradient_enable);
        label_luminosity_gradient_opacity->setObjectName(QString::fromUtf8("label_luminosity_gradient_opacity"));

        horizontalLayout_luminosity_opacity->addWidget(label_luminosity_gradient_opacity);

        spinbox_luminosity_gradient_opacity = new MyDoubleSpinBox(groupCheck_luminosity_gradient_enable);
        spinbox_luminosity_gradient_opacity->setObjectName(QString::fromUtf8("spinbox_luminosity_gradient_opacity"));

        horizontalLayout_luminosity_opacity->addWidget(spinbox_luminosity_gradient_opacity);

        horizontalSpacer_luminosity_opacity = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_luminosity_opacity->addItem(horizontalSpacer_luminosity_opacity);


        verticalLayout_17->addLayout(horizontalLayout_luminosity_opacity);


        verticalLayout_70->addWidget(groupCheck_luminosity_gradient_enable);

        groupCheck_roughness_gradient_enable = new MyGroupBox(groupCheck_use_colors_from_palette);
        groupCheck_roughness_gradient_enable->setObjectName(QString::fromUtf8("groupCheck_roughness_gradient_enable"));
        groupCheck_roughness_gradient_enable->setCheckable(true);
        verticalLayout_18 = new QVBoxLayout(groupCheck_roughness_gradient_enable);
        verticalLayout_18->setSpacing(2);
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        verticalLayout_18->setContentsMargins(2, 2, 2, 2);
        colorpalette_roughness_gradient = new cGradientEditWidget(groupCheck_roughness_gradient_enable);
        colorpalette_roughness_gradient->setObjectName(QString::fromUtf8("colorpalette_roughness_gradient"));

        verticalLayout_18->addWidget(colorpalette_roughness_gradient);

        horizontalLayout_roughness_opacity = new QHBoxLayout();
        horizontalLayout_roughness_opacity->setObjectName(QString::fromUtf8("horizontalLayout_roughness_opacity"));
        checkBox_roughness_gradient_mask_enable = new MyCheckBox(groupCheck_roughness_gradient_enable);
        checkBox_roughness_gradient_mask_enable->setObjectName(QString::fromUtf8("checkBox_roughness_gradient_mask_enable"));

        horizontalLayout_roughness_opacity->addWidget(checkBox_roughness_gradient_mask_enable);

        label_roughness_gradient_opacity = new QLabel(groupCheck_roughness_gradient_enable);
        label_roughness_gradient_opacity->setObjectName(QString::fromUtf8("label_roughness_gradient_opacity"));

        horizontalLayout_roughness_opacity->addWidget(label_roughness_gradient_opacity);

        spinbox_roughness_gradient_opacity = new MyDoubleSpinBox(groupCheck_roughness_gradient_enable);
        spinbox_roughness_gradient_opacity->setObjectName(QString::fromUtf8("spinbox_roughness_gradient_opacity"));

        horizontalLayout_roughness_opacity->addWidget(spinbox_roughness_gradient_opacity);

        horizontalSpacer_roughness_opacity = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_roughness_opacity->addItem(horizontalSpacer_roughness_opacity);


        verticalLayout_18->addLayout(horizontalLayout_roughness_opacity);


        verticalLayout_70->addWidget(groupCheck_roughness_gradient_enable);

        groupCheck_reflectance_gradient_enable = new MyGroupBox(groupCheck_use_colors_from_palette);
        groupCheck_reflectance_gradient_enable->setObjectName(QString::fromUtf8("groupCheck_reflectance_gradient_enable"));
        groupCheck_reflectance_gradient_enable->setCheckable(true);
        verticalLayout_19 = new QVBoxLayout(groupCheck_reflectance_gradient_enable);
        verticalLayout_19->setSpacing(2);
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        verticalLayout_19->setContentsMargins(2, 2, 2, 2);
        colorpalette_reflectance_gradient = new cGradientEditWidget(groupCheck_reflectance_gradient_enable);
        colorpalette_reflectance_gradient->setObjectName(QString::fromUtf8("colorpalette_reflectance_gradient"));

        verticalLayout_19->addWidget(colorpalette_reflectance_gradient);

        horizontalLayout_reflectance_opacity = new QHBoxLayout();
        horizontalLayout_reflectance_opacity->setObjectName(QString::fromUtf8("horizontalLayout_reflectance_opacity"));
        checkBox_reflectance_gradient_mask_enable = new MyCheckBox(groupCheck_reflectance_gradient_enable);
        checkBox_reflectance_gradient_mask_enable->setObjectName(QString::fromUtf8("checkBox_reflectance_gradient_mask_enable"));

        horizontalLayout_reflectance_opacity->addWidget(checkBox_reflectance_gradient_mask_enable);

        label_reflectance_gradient_opacity = new QLabel(groupCheck_reflectance_gradient_enable);
        label_reflectance_gradient_opacity->setObjectName(QString::fromUtf8("label_reflectance_gradient_opacity"));

        horizontalLayout_reflectance_opacity->addWidget(label_reflectance_gradient_opacity);

        spinbox_reflectance_gradient_opacity = new MyDoubleSpinBox(groupCheck_reflectance_gradient_enable);
        spinbox_reflectance_gradient_opacity->setObjectName(QString::fromUtf8("spinbox_reflectance_gradient_opacity"));

        horizontalLayout_reflectance_opacity->addWidget(spinbox_reflectance_gradient_opacity);

        horizontalSpacer_reflectance_opacity = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_reflectance_opacity->addItem(horizontalSpacer_reflectance_opacity);


        verticalLayout_19->addLayout(horizontalLayout_reflectance_opacity);


        verticalLayout_70->addWidget(groupCheck_reflectance_gradient_enable);

        groupCheck_transparency_gradient_enable = new MyGroupBox(groupCheck_use_colors_from_palette);
        groupCheck_transparency_gradient_enable->setObjectName(QString::fromUtf8("groupCheck_transparency_gradient_enable"));
        groupCheck_transparency_gradient_enable->setCheckable(true);
        verticalLayout_20 = new QVBoxLayout(groupCheck_transparency_gradient_enable);
        verticalLayout_20->setSpacing(2);
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));
        verticalLayout_20->setContentsMargins(2, 2, 2, 2);
        colorpalette_transparency_gradient = new cGradientEditWidget(groupCheck_transparency_gradient_enable);
        colorpalette_transparency_gradient->setObjectName(QString::fromUtf8("colorpalette_transparency_gradient"));

        verticalLayout_20->addWidget(colorpalette_transparency_gradient);

        horizontalLayout_transparency_opacity = new QHBoxLayout();
        horizontalLayout_transparency_opacity->setObjectName(QString::fromUtf8("horizontalLayout_transparency_opacity"));
        checkBox_transparency_gradient_mask_enable = new MyCheckBox(groupCheck_transparency_gradient_enable);
        checkBox_transparency_gradient_mask_enable->setObjectName(QString::fromUtf8("checkBox_transparency_gradient_mask_enable"));

        horizontalLayout_transparency_opacity->addWidget(checkBox_transparency_gradient_mask_enable);

        label_transparency_gradient_opacity = new QLabel(groupCheck_transparency_gradient_enable);
        label_transparency_gradient_opacity->setObjectName(QString::fromUtf8("label_transparency_gradient_opacity"));

        horizontalLayout_transparency_opacity->addWidget(label_transparency_gradient_opacity);

        spinbox_transparency_gradient_opacity = new MyDoubleSpinBox(groupCheck_transparency_gradient_enable);
        spinbox_transparency_gradient_opacity->setObjectName(QString::fromUtf8("spinbox_transparency_gradient_opacity"));

        horizontalLayout_transparency_opacity->addWidget(spinbox_transparency_gradient_opacity);

        horizontalSpacer_transparency_opacity = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_transparency_opacity->addItem(horizontalSpacer_transparency_opacity);


        verticalLayout_20->addLayout(horizontalLayout_transparency_opacity);


        verticalLayout_70->addWidget(groupCheck_transparency_gradient_enable);

        groupBox_gradient_processing = new QGroupBox(groupCheck_use_colors_from_palette);
        groupBox_gradient_processing->setObjectName(QString::fromUtf8("groupBox_gradient_processing"));
        gridLayout_gradient_processing = new QGridLayout(groupBox_gradient_processing);
        gridLayout_gradient_processing->setSpacing(2);
        gridLayout_gradient_processing->setObjectName(QString::fromUtf8("gridLayout_gradient_processing"));
        gridLayout_gradient_processing->setContentsMargins(2, 2, 2, 2);
        label_gradient_scale = new QLabel(groupBox_gradient_processing);
        label_gradient_scale->setObjectName(QString::fromUtf8("label_gradient_scale"));

        gridLayout_gradient_processing->addWidget(label_gradient_scale, 0, 0, 1, 1);

        spinbox_gradient_scale = new MyDoubleSpinBox(groupBox_gradient_processing);
        spinbox_gradient_scale->setObjectName(QString::fromUtf8("spinbox_gradient_scale"));

        gridLayout_gradient_processing->addWidget(spinbox_gradient_scale, 0, 1, 1, 1);

        label_gradient_offset = new QLabel(groupBox_gradient_processing);
        label_gradient_offset->setObjectName(QString::fromUtf8("label_gradient_offset"));

        gridLayout_gradient_processing->addWidget(label_gradient_offset, 0, 2, 1, 1);

        spinbox_gradient_offset = new MyDoubleSpinBox(groupBox_gradient_processing);
        spinbox_gradient_offset->setObjectName(QString::fromUtf8("spinbox_gradient_offset"));

        gridLayout_gradient_processing->addWidget(spinbox_gradient_offset, 0, 3, 1, 1);

        label_gradient_repeat_mode = new QLabel(groupBox_gradient_processing);
        label_gradient_repeat_mode->setObjectName(QString::fromUtf8("label_gradient_repeat_mode"));

        gridLayout_gradient_processing->addWidget(label_gradient_repeat_mode, 0, 4, 1, 1);

        comboBox_gradient_repeat_mode = new MyComboBox(groupBox_gradient_processing);
        comboBox_gradient_repeat_mode->addItem(QString());
        comboBox_gradient_repeat_mode->addItem(QString());
        comboBox_gradient_repeat_mode->addItem(QString());
        comboBox_gradient_repeat_mode->addItem(QString());
        comboBox_gradient_repeat_mode->addItem(QString());
        comboBox_gradient_repeat_mode->setObjectName(QString::fromUtf8("comboBox_gradient_repeat_mode"));

        gridLayout_gradient_processing->addWidget(comboBox_gradient_repeat_mode, 0, 5, 1, 1);

        label_gradient_brightness = new QLabel(groupBox_gradient_processing);
        label_gradient_brightness->setObjectName(QString::fromUtf8("label_gradient_brightness"));

        gridLayout_gradient_processing->addWidget(label_gradient_brightness, 1, 0, 1, 1);

        spinbox_gradient_brightness = new MyDoubleSpinBox(groupBox_gradient_processing);
        spinbox_gradient_brightness->setObjectName(QString::fromUtf8("spinbox_gradient_brightness"));

        gridLayout_gradient_processing->addWidget(spinbox_gradient_brightness, 1, 1, 1, 1);

        label_gradient_contrast = new QLabel(groupBox_gradient_processing);
        label_gradient_contrast->setObjectName(QString::fromUtf8("label_gradient_contrast"));

        gridLayout_gradient_processing->addWidget(label_gradient_contrast, 1, 2, 1, 1);

        spinbox_gradient_contrast = new MyDoubleSpinBox(groupBox_gradient_processing);
        spinbox_gradient_contrast->setObjectName(QString::fromUtf8("spinbox_gradient_contrast"));

        gridLayout_gradient_processing->addWidget(spinbox_gradient_contrast, 1, 3, 1, 1);

        label_gradient_saturation = new QLabel(groupBox_gradient_processing);
        label_gradient_saturation->setObjectName(QString::fromUtf8("label_gradient_saturation"));

        gridLayout_gradient_processing->addWidget(label_gradient_saturation, 1, 4, 1, 1);

        spinbox_gradient_saturation = new MyDoubleSpinBox(groupBox_gradient_processing);
        spinbox_gradient_saturation->setObjectName(QString::fromUtf8("spinbox_gradient_saturation"));

        gridLayout_gradient_processing->addWidget(spinbox_gradient_saturation, 1, 5, 1, 1);

        label_gradient_gamma = new QLabel(groupBox_gradient_processing);
        label_gradient_gamma->setObjectName(QString::fromUtf8("label_gradient_gamma"));

        gridLayout_gradient_processing->addWidget(label_gradient_gamma, 2, 0, 1, 1);

        spinbox_gradient_gamma = new MyDoubleSpinBox(groupBox_gradient_processing);
        spinbox_gradient_gamma->setObjectName(QString::fromUtf8("spinbox_gradient_gamma"));

        gridLayout_gradient_processing->addWidget(spinbox_gradient_gamma, 2, 1, 1, 1);

        label_gradient_color_space = new QLabel(groupBox_gradient_processing);
        label_gradient_color_space->setObjectName(QString::fromUtf8("label_gradient_color_space"));

        gridLayout_gradient_processing->addWidget(label_gradient_color_space, 2, 2, 1, 1);

        comboBox_gradient_color_space = new MyComboBox(groupBox_gradient_processing);
        comboBox_gradient_color_space->addItem(QString());
        comboBox_gradient_color_space->addItem(QString());
        comboBox_gradient_color_space->setObjectName(QString::fromUtf8("comboBox_gradient_color_space"));

        gridLayout_gradient_processing->addWidget(comboBox_gradient_color_space, 2, 3, 1, 1);

        label_gradient_noise_amount = new QLabel(groupBox_gradient_processing);
        label_gradient_noise_amount->setObjectName(QString::fromUtf8("label_gradient_noise_amount"));

        gridLayout_gradient_processing->addWidget(label_gradient_noise_amount, 2, 4, 1, 1);

        spinbox_gradient_noise_amount = new MyDoubleSpinBox(groupBox_gradient_processing);
        spinbox_gradient_noise_amount->setObjectName(QString::fromUtf8("spinbox_gradient_noise_amount"));

        gridLayout_gradient_processing->addWidget(spinbox_gradient_noise_amount, 2, 5, 1, 1);


        verticalLayout_70->addWidget(groupBox_gradient_processing);

        gridLayout_34 = new QGridLayout();
        gridLayout_34->setSpacing(2);
        gridLayout_34->setObjectName(QString::fromUtf8("gridLayout_34"));
        label_133 = new QLabel(groupCheck_use_colors_from_palette);
        label_133->setObjectName(QString::fromUtf8("label_133"));

        gridLayout_34->addWidget(label_133, 1, 0, 1, 1);

        label_357 = new QLabel(groupCheck_use_colors_from_palette);
        label_357->setObjectName(QString::fromUtf8("label_357"));

        gridLayout_34->addWidget(label_357, 0, 0, 1, 1);

        label_fractal_coloring_circle_radius = new QLabel(groupCheck_use_colors_from_palette);
        label_fractal_coloring_circle_radius->setObjectName(QString::fromUtf8("label_fractal_coloring_circle_radius"));

        gridLayout_34->addWidget(label_fractal_coloring_circle_radius, 4, 0, 1, 1);

        vect4_fractal_coloring_line_direction_x = new MyLineEdit(groupCheck_use_colors_from_palette);
        vect4_fractal_coloring_line_direction_x->setObjectName(QString::fromUtf8("vect4_fractal_coloring_line_direction_x"));
        vect4_fractal_coloring_line_direction_x->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(vect4_fractal_coloring_line_direction_x->sizePolicy().hasHeightForWidth());
        vect4_fractal_coloring_line_direction_x->setSizePolicy(sizePolicy);

        gridLayout_34->addWidget(vect4_fractal_coloring_line_direction_x, 5, 2, 1, 1);

        line_4 = new QFrame(groupCheck_use_colors_from_palette);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout_34->addWidget(line_4, 2, 0, 1, 3);

        vect4_fractal_coloring_line_direction_z = new MyLineEdit(groupCheck_use_colors_from_palette);
        vect4_fractal_coloring_line_direction_z->setObjectName(QString::fromUtf8("vect4_fractal_coloring_line_direction_z"));
        vect4_fractal_coloring_line_direction_z->setEnabled(false);
        sizePolicy.setHeightForWidth(vect4_fractal_coloring_line_direction_z->sizePolicy().hasHeightForWidth());
        vect4_fractal_coloring_line_direction_z->setSizePolicy(sizePolicy);

        gridLayout_34->addWidget(vect4_fractal_coloring_line_direction_z, 7, 2, 1, 1);

        label_fractal_coloring_line_direction_x = new QLabel(groupCheck_use_colors_from_palette);
        label_fractal_coloring_line_direction_x->setObjectName(QString::fromUtf8("label_fractal_coloring_line_direction_x"));
        label_fractal_coloring_line_direction_x->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_34->addWidget(label_fractal_coloring_line_direction_x, 5, 1, 1, 1);

        label_fractal_coloring_line_direction_z = new QLabel(groupCheck_use_colors_from_palette);
        label_fractal_coloring_line_direction_z->setObjectName(QString::fromUtf8("label_fractal_coloring_line_direction_z"));
        label_fractal_coloring_line_direction_z->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_34->addWidget(label_fractal_coloring_line_direction_z, 7, 1, 1, 1);

        spinbox_coloring_speed = new MyDoubleSpinBox(groupCheck_use_colors_from_palette);
        spinbox_coloring_speed->setObjectName(QString::fromUtf8("spinbox_coloring_speed"));
        sizePolicy.setHeightForWidth(spinbox_coloring_speed->sizePolicy().hasHeightForWidth());
        spinbox_coloring_speed->setSizePolicy(sizePolicy);
        spinbox_coloring_speed->setAccelerated(false);
        spinbox_coloring_speed->setDecimals(4);
        spinbox_coloring_speed->setMinimum(0.000000000000000);
        spinbox_coloring_speed->setMaximum(100000.000000000000000);
        spinbox_coloring_speed->setSingleStep(0.010000000000000);
        spinbox_coloring_speed->setValue(0.000000000000000);

        gridLayout_34->addWidget(spinbox_coloring_speed, 1, 1, 1, 2);

        spinbox_fractal_coloring_sphere_radius = new MyDoubleSpinBox(groupCheck_use_colors_from_palette);
        spinbox_fractal_coloring_sphere_radius->setObjectName(QString::fromUtf8("spinbox_fractal_coloring_sphere_radius"));
        spinbox_fractal_coloring_sphere_radius->setEnabled(false);
        sizePolicy.setHeightForWidth(spinbox_fractal_coloring_sphere_radius->sizePolicy().hasHeightForWidth());
        spinbox_fractal_coloring_sphere_radius->setSizePolicy(sizePolicy);
        spinbox_fractal_coloring_sphere_radius->setAccelerated(false);
        spinbox_fractal_coloring_sphere_radius->setDecimals(4);
        spinbox_fractal_coloring_sphere_radius->setMinimum(0.000000000000000);
        spinbox_fractal_coloring_sphere_radius->setMaximum(1000.000000000000000);
        spinbox_fractal_coloring_sphere_radius->setSingleStep(0.010000000000000);
        spinbox_fractal_coloring_sphere_radius->setValue(0.000000000000000);

        gridLayout_34->addWidget(spinbox_fractal_coloring_sphere_radius, 4, 1, 1, 2);

        comboBox_fractal_coloring_algorithm = new MyComboBox(groupCheck_use_colors_from_palette);
        comboBox_fractal_coloring_algorithm->addItem(QString());
        comboBox_fractal_coloring_algorithm->addItem(QString());
        comboBox_fractal_coloring_algorithm->addItem(QString());
        comboBox_fractal_coloring_algorithm->addItem(QString());
        comboBox_fractal_coloring_algorithm->addItem(QString());
        comboBox_fractal_coloring_algorithm->addItem(QString());
        comboBox_fractal_coloring_algorithm->addItem(QString());
        comboBox_fractal_coloring_algorithm->setObjectName(QString::fromUtf8("comboBox_fractal_coloring_algorithm"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox_fractal_coloring_algorithm->sizePolicy().hasHeightForWidth());
        comboBox_fractal_coloring_algorithm->setSizePolicy(sizePolicy1);

        gridLayout_34->addWidget(comboBox_fractal_coloring_algorithm, 3, 1, 1, 2);

        label_fractal_coloring_line_direction_y = new QLabel(groupCheck_use_colors_from_palette);
        label_fractal_coloring_line_direction_y->setObjectName(QString::fromUtf8("label_fractal_coloring_line_direction_y"));
        label_fractal_coloring_line_direction_y->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_34->addWidget(label_fractal_coloring_line_direction_y, 6, 1, 1, 1);

        label_354 = new QLabel(groupCheck_use_colors_from_palette);
        label_354->setObjectName(QString::fromUtf8("label_354"));

        gridLayout_34->addWidget(label_354, 3, 0, 1, 1);

        vect4_fractal_coloring_line_direction_y = new MyLineEdit(groupCheck_use_colors_from_palette);
        vect4_fractal_coloring_line_direction_y->setObjectName(QString::fromUtf8("vect4_fractal_coloring_line_direction_y"));
        vect4_fractal_coloring_line_direction_y->setEnabled(false);
        sizePolicy.setHeightForWidth(vect4_fractal_coloring_line_direction_y->sizePolicy().hasHeightForWidth());
        vect4_fractal_coloring_line_direction_y->setSizePolicy(sizePolicy);

        gridLayout_34->addWidget(vect4_fractal_coloring_line_direction_y, 6, 2, 1, 1);

        spinbox_coloring_palette_offset = new MyDoubleSpinBox(groupCheck_use_colors_from_palette);
        spinbox_coloring_palette_offset->setObjectName(QString::fromUtf8("spinbox_coloring_palette_offset"));
        sizePolicy.setHeightForWidth(spinbox_coloring_palette_offset->sizePolicy().hasHeightForWidth());
        spinbox_coloring_palette_offset->setSizePolicy(sizePolicy);
        spinbox_coloring_palette_offset->setAccelerated(false);
        spinbox_coloring_palette_offset->setDecimals(5);
        spinbox_coloring_palette_offset->setMinimum(0.000000000000000);
        spinbox_coloring_palette_offset->setMaximum(100.000000000000000);
        spinbox_coloring_palette_offset->setSingleStep(0.010000000000000);
        spinbox_coloring_palette_offset->setValue(0.000000000000000);

        gridLayout_34->addWidget(spinbox_coloring_palette_offset, 0, 1, 1, 2);

        label_fractal_coloring_line_direction_z_2 = new QLabel(groupCheck_use_colors_from_palette);
        label_fractal_coloring_line_direction_z_2->setObjectName(QString::fromUtf8("label_fractal_coloring_line_direction_z_2"));
        label_fractal_coloring_line_direction_z_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_34->addWidget(label_fractal_coloring_line_direction_z_2, 8, 1, 1, 1);

        vect4_fractal_coloring_line_direction_w = new MyLineEdit(groupCheck_use_colors_from_palette);
        vect4_fractal_coloring_line_direction_w->setObjectName(QString::fromUtf8("vect4_fractal_coloring_line_direction_w"));
        vect4_fractal_coloring_line_direction_w->setEnabled(false);
        sizePolicy.setHeightForWidth(vect4_fractal_coloring_line_direction_w->sizePolicy().hasHeightForWidth());
        vect4_fractal_coloring_line_direction_w->setSizePolicy(sizePolicy);

        gridLayout_34->addWidget(vect4_fractal_coloring_line_direction_w, 8, 2, 1, 1);

        label_fractal_coloring_line_direction = new QLabel(groupCheck_use_colors_from_palette);
        label_fractal_coloring_line_direction->setObjectName(QString::fromUtf8("label_fractal_coloring_line_direction"));

        gridLayout_34->addWidget(label_fractal_coloring_line_direction, 5, 0, 4, 1);


        verticalLayout_70->addLayout(gridLayout_34);

        checkBox_fractal_coloring_color_4D_enabled_false = new MyCheckBox(groupCheck_use_colors_from_palette);
        checkBox_fractal_coloring_color_4D_enabled_false->setObjectName(QString::fromUtf8("checkBox_fractal_coloring_color_4D_enabled_false"));
        checkBox_fractal_coloring_color_4D_enabled_false->setText(QString::fromUtf8("4D orbit trap color"));

        verticalLayout_70->addWidget(checkBox_fractal_coloring_color_4D_enabled_false);

        checkBox_fractal_coloring_color_preV215_false = new MyCheckBox(groupCheck_use_colors_from_palette);
        checkBox_fractal_coloring_color_preV215_false->setObjectName(QString::fromUtf8("checkBox_fractal_coloring_color_preV215_false"));
        checkBox_fractal_coloring_color_preV215_false->setText(QString::fromUtf8("pre V2.15 orbit trap color"));

        verticalLayout_70->addWidget(checkBox_fractal_coloring_color_preV215_false);

        groupCheck_fractal_coloring_extra_color_options_false = new MyGroupBox(groupCheck_use_colors_from_palette);
        groupCheck_fractal_coloring_extra_color_options_false->setObjectName(QString::fromUtf8("groupCheck_fractal_coloring_extra_color_options_false"));
        groupCheck_fractal_coloring_extra_color_options_false->setCheckable(true);
        verticalLayout_49 = new QVBoxLayout(groupCheck_fractal_coloring_extra_color_options_false);
        verticalLayout_49->setSpacing(2);
        verticalLayout_49->setObjectName(QString::fromUtf8("verticalLayout_49"));
        verticalLayout_49->setContentsMargins(2, 2, 2, 2);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_63 = new QLabel(groupCheck_fractal_coloring_extra_color_options_false);
        label_63->setObjectName(QString::fromUtf8("label_63"));

        gridLayout->addWidget(label_63, 2, 0, 1, 1);


        verticalLayout_49->addLayout(gridLayout);

        gridLayout_32 = new QGridLayout();
        gridLayout_32->setObjectName(QString::fromUtf8("gridLayout_32"));
        gridLayout_32->setContentsMargins(-1, 0, -1, -1);
        label_88 = new QLabel(groupCheck_fractal_coloring_extra_color_options_false);
        label_88->setObjectName(QString::fromUtf8("label_88"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_88->setFont(font);

        gridLayout_32->addWidget(label_88, 2, 0, 1, 1);

        spinbox_fractal_coloring_rad_div_de_scale1 = new MyDoubleSpinBox(groupCheck_fractal_coloring_extra_color_options_false);
        spinbox_fractal_coloring_rad_div_de_scale1->setObjectName(QString::fromUtf8("spinbox_fractal_coloring_rad_div_de_scale1"));
        sizePolicy.setHeightForWidth(spinbox_fractal_coloring_rad_div_de_scale1->sizePolicy().hasHeightForWidth());
        spinbox_fractal_coloring_rad_div_de_scale1->setSizePolicy(sizePolicy);
        spinbox_fractal_coloring_rad_div_de_scale1->setDecimals(6);
        spinbox_fractal_coloring_rad_div_de_scale1->setMinimum(0.000000000000000);
        spinbox_fractal_coloring_rad_div_de_scale1->setMaximum(9999.999900000000707);
        spinbox_fractal_coloring_rad_div_de_scale1->setSingleStep(0.100000000000000);

        gridLayout_32->addWidget(spinbox_fractal_coloring_rad_div_de_scale1, 2, 1, 1, 1);

        label_89 = new QLabel(groupCheck_fractal_coloring_extra_color_options_false);
        label_89->setObjectName(QString::fromUtf8("label_89"));
        label_89->setFont(font);

        gridLayout_32->addWidget(label_89, 1, 0, 1, 1);

        spinbox_fractal_coloring_aux_color_scale1 = new MyDoubleSpinBox(groupCheck_fractal_coloring_extra_color_options_false);
        spinbox_fractal_coloring_aux_color_scale1->setObjectName(QString::fromUtf8("spinbox_fractal_coloring_aux_color_scale1"));
        sizePolicy.setHeightForWidth(spinbox_fractal_coloring_aux_color_scale1->sizePolicy().hasHeightForWidth());
        spinbox_fractal_coloring_aux_color_scale1->setSizePolicy(sizePolicy);
        spinbox_fractal_coloring_aux_color_scale1->setDecimals(6);
        spinbox_fractal_coloring_aux_color_scale1->setMinimum(0.000000000000000);
        spinbox_fractal_coloring_aux_color_scale1->setMaximum(9999.999900000000707);
        spinbox_fractal_coloring_aux_color_scale1->setSingleStep(0.100000000000000);

        gridLayout_32->addWidget(spinbox_fractal_coloring_aux_color_scale1, 1, 1, 1, 1);

        spinbox_fractal_coloring_orbit_trap_scale1 = new MyDoubleSpinBox(groupCheck_fractal_coloring_extra_color_options_false);
        spinbox_fractal_coloring_orbit_trap_scale1->setObjectName(QString::fromUtf8("spinbox_fractal_coloring_orbit_trap_scale1"));
        sizePolicy.setHeightForWidth(spinbox_fractal_coloring_orbit_trap_scale1->sizePolicy().hasHeightForWidth());
        spinbox_fractal_coloring_orbit_trap_scale1->setSizePolicy(sizePolicy);
        spinbox_fractal_coloring_orbit_trap_scale1->setDecimals(6);
        spinbox_fractal_coloring_orbit_trap_scale1->setMinimum(0.000000000000000);
        spinbox_fractal_coloring_orbit_trap_scale1->setMaximum(9999.999900000000707);
        spinbox_fractal_coloring_orbit_trap_scale1->setSingleStep(0.100000000000000);

        gridLayout_32->addWidget(spinbox_fractal_coloring_orbit_trap_scale1, 0, 1, 1, 1);

        label_90 = new QLabel(groupCheck_fractal_coloring_extra_color_options_false);
        label_90->setObjectName(QString::fromUtf8("label_90"));
        label_90->setFont(font);

        gridLayout_32->addWidget(label_90, 0, 0, 1, 1);

        gridLayout_32->setColumnStretch(1, 1);

        verticalLayout_49->addLayout(gridLayout_32);


        verticalLayout_70->addWidget(groupCheck_fractal_coloring_extra_color_options_false);

        groupCheck_fractal_coloring_extra_color_enabled_false = new MyGroupBox(groupCheck_use_colors_from_palette);
        groupCheck_fractal_coloring_extra_color_enabled_false->setObjectName(QString::fromUtf8("groupCheck_fractal_coloring_extra_color_enabled_false"));
        groupCheck_fractal_coloring_extra_color_enabled_false->setCheckable(true);
        verticalLayout_29 = new QVBoxLayout(groupCheck_fractal_coloring_extra_color_enabled_false);
        verticalLayout_29->setSpacing(2);
        verticalLayout_29->setObjectName(QString::fromUtf8("verticalLayout_29"));
        verticalLayout_29->setContentsMargins(2, 2, 2, 2);
        gridLayout_28 = new QGridLayout();
        gridLayout_28->setSpacing(2);
        gridLayout_28->setObjectName(QString::fromUtf8("gridLayout_28"));
        label_64 = new QLabel(groupCheck_fractal_coloring_extra_color_enabled_false);
        label_64->setObjectName(QString::fromUtf8("label_64"));
        label_64->setFont(font);

        gridLayout_28->addWidget(label_64, 1, 0, 1, 1);

        spinbox_fractal_coloring_initial_color_value = new MyDoubleSpinBox(groupCheck_fractal_coloring_extra_color_enabled_false);
        spinbox_fractal_coloring_initial_color_value->setObjectName(QString::fromUtf8("spinbox_fractal_coloring_initial_color_value"));
        sizePolicy.setHeightForWidth(spinbox_fractal_coloring_initial_color_value->sizePolicy().hasHeightForWidth());
        spinbox_fractal_coloring_initial_color_value->setSizePolicy(sizePolicy);
        spinbox_fractal_coloring_initial_color_value->setAccelerated(false);
        spinbox_fractal_coloring_initial_color_value->setDecimals(6);
        spinbox_fractal_coloring_initial_color_value->setMinimum(-9999.999900000000707);
        spinbox_fractal_coloring_initial_color_value->setMaximum(9999.999900000000707);
        spinbox_fractal_coloring_initial_color_value->setSingleStep(0.100000000000000);

        gridLayout_28->addWidget(spinbox_fractal_coloring_initial_color_value, 1, 1, 1, 1);

        gridLayout_28->setColumnStretch(1, 1);

        verticalLayout_29->addLayout(gridLayout_28);

        groupCheck_fractal_coloring_init_cond_enabled_false = new MyGroupBox(groupCheck_fractal_coloring_extra_color_enabled_false);
        groupCheck_fractal_coloring_init_cond_enabled_false->setObjectName(QString::fromUtf8("groupCheck_fractal_coloring_init_cond_enabled_false"));
        groupCheck_fractal_coloring_init_cond_enabled_false->setCheckable(true);
        verticalLayout_33 = new QVBoxLayout(groupCheck_fractal_coloring_init_cond_enabled_false);
        verticalLayout_33->setSpacing(2);
        verticalLayout_33->setObjectName(QString::fromUtf8("verticalLayout_33"));
        verticalLayout_33->setContentsMargins(2, 6, 2, 2);
        gridLayout_17 = new QGridLayout();
        gridLayout_17->setSpacing(2);
        gridLayout_17->setObjectName(QString::fromUtf8("gridLayout_17"));
        checkBox_fractal_coloring_ic_rad_enabled_false = new MyCheckBox(groupCheck_fractal_coloring_init_cond_enabled_false);
        checkBox_fractal_coloring_ic_rad_enabled_false->setObjectName(QString::fromUtf8("checkBox_fractal_coloring_ic_rad_enabled_false"));
        checkBox_fractal_coloring_ic_rad_enabled_false->setText(QString::fromUtf8(" c_radius"));

        gridLayout_17->addWidget(checkBox_fractal_coloring_ic_rad_enabled_false, 0, 1, 1, 3);

        label_45 = new QLabel(groupCheck_fractal_coloring_init_cond_enabled_false);
        label_45->setObjectName(QString::fromUtf8("label_45"));

        gridLayout_17->addWidget(label_45, 1, 1, 1, 1);

        label_46 = new QLabel(groupCheck_fractal_coloring_init_cond_enabled_false);
        label_46->setObjectName(QString::fromUtf8("label_46"));

        gridLayout_17->addWidget(label_46, 5, 1, 1, 1);

        label_43 = new QLabel(groupCheck_fractal_coloring_init_cond_enabled_false);
        label_43->setObjectName(QString::fromUtf8("label_43"));

        gridLayout_17->addWidget(label_43, 3, 1, 1, 1);

        label_44 = new QLabel(groupCheck_fractal_coloring_init_cond_enabled_false);
        label_44->setObjectName(QString::fromUtf8("label_44"));

        gridLayout_17->addWidget(label_44, 4, 1, 1, 1);

        spinbox_fractal_coloring_ic_rad_weight = new MyDoubleSpinBox(groupCheck_fractal_coloring_init_cond_enabled_false);
        spinbox_fractal_coloring_ic_rad_weight->setObjectName(QString::fromUtf8("spinbox_fractal_coloring_ic_rad_weight"));
        sizePolicy.setHeightForWidth(spinbox_fractal_coloring_ic_rad_weight->sizePolicy().hasHeightForWidth());
        spinbox_fractal_coloring_ic_rad_weight->setSizePolicy(sizePolicy);
        spinbox_fractal_coloring_ic_rad_weight->setDecimals(6);
        spinbox_fractal_coloring_ic_rad_weight->setMinimum(-9999.999900000000707);
        spinbox_fractal_coloring_ic_rad_weight->setMaximum(9999.999900000000707);
        spinbox_fractal_coloring_ic_rad_weight->setSingleStep(0.100000000000000);

        gridLayout_17->addWidget(spinbox_fractal_coloring_ic_rad_weight, 1, 2, 1, 2);

        spinbox3_fractal_coloring_xyzC_111_z = new MyDoubleSpinBox(groupCheck_fractal_coloring_init_cond_enabled_false);
        spinbox3_fractal_coloring_xyzC_111_z->setObjectName(QString::fromUtf8("spinbox3_fractal_coloring_xyzC_111_z"));
        sizePolicy.setHeightForWidth(spinbox3_fractal_coloring_xyzC_111_z->sizePolicy().hasHeightForWidth());
        spinbox3_fractal_coloring_xyzC_111_z->setSizePolicy(sizePolicy);
        spinbox3_fractal_coloring_xyzC_111_z->setDecimals(6);
        spinbox3_fractal_coloring_xyzC_111_z->setMinimum(-9999.999900000000707);
        spinbox3_fractal_coloring_xyzC_111_z->setMaximum(9999.999900000000707);
        spinbox3_fractal_coloring_xyzC_111_z->setSingleStep(0.100000000000000);

        gridLayout_17->addWidget(spinbox3_fractal_coloring_xyzC_111_z, 5, 2, 1, 2);

        checkBox_fractal_coloring_ic_xyz_enabled_false = new MyCheckBox(groupCheck_fractal_coloring_init_cond_enabled_false);
        checkBox_fractal_coloring_ic_xyz_enabled_false->setObjectName(QString::fromUtf8("checkBox_fractal_coloring_ic_xyz_enabled_false"));
        checkBox_fractal_coloring_ic_xyz_enabled_false->setText(QString::fromUtf8(" c_xyz"));

        gridLayout_17->addWidget(checkBox_fractal_coloring_ic_xyz_enabled_false, 2, 1, 1, 3);

        spinbox3_fractal_coloring_xyzC_111_y = new MyDoubleSpinBox(groupCheck_fractal_coloring_init_cond_enabled_false);
        spinbox3_fractal_coloring_xyzC_111_y->setObjectName(QString::fromUtf8("spinbox3_fractal_coloring_xyzC_111_y"));
        sizePolicy.setHeightForWidth(spinbox3_fractal_coloring_xyzC_111_y->sizePolicy().hasHeightForWidth());
        spinbox3_fractal_coloring_xyzC_111_y->setSizePolicy(sizePolicy);
        spinbox3_fractal_coloring_xyzC_111_y->setDecimals(6);
        spinbox3_fractal_coloring_xyzC_111_y->setMinimum(-9999.999900000000707);
        spinbox3_fractal_coloring_xyzC_111_y->setMaximum(9999.999900000000707);
        spinbox3_fractal_coloring_xyzC_111_y->setSingleStep(0.100000000000000);

        gridLayout_17->addWidget(spinbox3_fractal_coloring_xyzC_111_y, 4, 2, 1, 2);

        spinbox3_fractal_coloring_xyzC_111_x = new MyDoubleSpinBox(groupCheck_fractal_coloring_init_cond_enabled_false);
        spinbox3_fractal_coloring_xyzC_111_x->setObjectName(QString::fromUtf8("spinbox3_fractal_coloring_xyzC_111_x"));
        sizePolicy.setHeightForWidth(spinbox3_fractal_coloring_xyzC_111_x->sizePolicy().hasHeightForWidth());
        spinbox3_fractal_coloring_xyzC_111_x->setSizePolicy(sizePolicy);
        spinbox3_fractal_coloring_xyzC_111_x->setDecimals(6);
        spinbox3_fractal_coloring_xyzC_111_x->setMinimum(-9999.999900000000707);
        spinbox3_fractal_coloring_xyzC_111_x->setMaximum(9999.999900000000707);
        spinbox3_fractal_coloring_xyzC_111_x->setSingleStep(0.100000000000000);

        gridLayout_17->addWidget(spinbox3_fractal_coloring_xyzC_111_x, 3, 2, 1, 2);


        verticalLayout_33->addLayout(gridLayout_17);

        checkBox_fractal_coloring_ic_fabs_enabled_false = new MyCheckBox(groupCheck_fractal_coloring_init_cond_enabled_false);
        checkBox_fractal_coloring_ic_fabs_enabled_false->setObjectName(QString::fromUtf8("checkBox_fractal_coloring_ic_fabs_enabled_false"));
        checkBox_fractal_coloring_ic_fabs_enabled_false->setText(QString::fromUtf8("disable abs(). May need to increase initial colorValue."));

        verticalLayout_33->addWidget(checkBox_fractal_coloring_ic_fabs_enabled_false);


        verticalLayout_29->addWidget(groupCheck_fractal_coloring_init_cond_enabled_false);

        groupBox_2 = new QGroupBox(groupCheck_fractal_coloring_extra_color_enabled_false);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(2, 2, 2, 2);
        groupCheck_fractal_coloring_orbit_trap_true = new MyGroupBox(groupBox_2);
        groupCheck_fractal_coloring_orbit_trap_true->setObjectName(QString::fromUtf8("groupCheck_fractal_coloring_orbit_trap_true"));
        groupCheck_fractal_coloring_orbit_trap_true->setEnabled(true);
        groupCheck_fractal_coloring_orbit_trap_true->setCheckable(true);
        verticalLayout_42 = new QVBoxLayout(groupCheck_fractal_coloring_orbit_trap_true);
        verticalLayout_42->setSpacing(2);
        verticalLayout_42->setObjectName(QString::fromUtf8("verticalLayout_42"));
        verticalLayout_42->setContentsMargins(2, 6, 2, 2);
        label_78 = new QLabel(groupCheck_fractal_coloring_orbit_trap_true);
        label_78->setObjectName(QString::fromUtf8("label_78"));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        label_78->setFont(font1);

        verticalLayout_42->addWidget(label_78);

        label_81 = new QLabel(groupCheck_fractal_coloring_orbit_trap_true);
        label_81->setObjectName(QString::fromUtf8("label_81"));
        label_81->setFont(font1);

        verticalLayout_42->addWidget(label_81);

        gridLayout_23 = new QGridLayout();
        gridLayout_23->setSpacing(2);
        gridLayout_23->setObjectName(QString::fromUtf8("gridLayout_23"));
        label_62 = new QLabel(groupCheck_fractal_coloring_orbit_trap_true);
        label_62->setObjectName(QString::fromUtf8("label_62"));
        label_62->setFont(font);

        gridLayout_23->addWidget(label_62, 1, 0, 1, 1);

        spinbox_fractal_coloring_orbit_trap_weight = new MyDoubleSpinBox(groupCheck_fractal_coloring_orbit_trap_true);
        spinbox_fractal_coloring_orbit_trap_weight->setObjectName(QString::fromUtf8("spinbox_fractal_coloring_orbit_trap_weight"));
        sizePolicy.setHeightForWidth(spinbox_fractal_coloring_orbit_trap_weight->sizePolicy().hasHeightForWidth());
        spinbox_fractal_coloring_orbit_trap_weight->setSizePolicy(sizePolicy);
        spinbox_fractal_coloring_orbit_trap_weight->setAccelerated(false);
        spinbox_fractal_coloring_orbit_trap_weight->setDecimals(6);
        spinbox_fractal_coloring_orbit_trap_weight->setMinimum(-9999.999900000000707);
        spinbox_fractal_coloring_orbit_trap_weight->setMaximum(9999.999900000000707);
        spinbox_fractal_coloring_orbit_trap_weight->setSingleStep(0.100000000000000);

        gridLayout_23->addWidget(spinbox_fractal_coloring_orbit_trap_weight, 1, 1, 1, 1);

        gridLayout_23->setColumnStretch(1, 1);

        verticalLayout_42->addLayout(gridLayout_23);


        verticalLayout_4->addWidget(groupCheck_fractal_coloring_orbit_trap_true);

        groupCheck_fractal_coloring_aux_color_false = new MyGroupBox(groupBox_2);
        groupCheck_fractal_coloring_aux_color_false->setObjectName(QString::fromUtf8("groupCheck_fractal_coloring_aux_color_false"));
        groupCheck_fractal_coloring_aux_color_false->setCheckable(true);
        verticalLayout_43 = new QVBoxLayout(groupCheck_fractal_coloring_aux_color_false);
        verticalLayout_43->setSpacing(2);
        verticalLayout_43->setObjectName(QString::fromUtf8("verticalLayout_43"));
        verticalLayout_43->setContentsMargins(2, 6, 2, 2);
        label_83 = new QLabel(groupCheck_fractal_coloring_aux_color_false);
        label_83->setObjectName(QString::fromUtf8("label_83"));
        label_83->setFont(font1);

        verticalLayout_43->addWidget(label_83);

        gridLayout_24 = new QGridLayout();
        gridLayout_24->setSpacing(2);
        gridLayout_24->setObjectName(QString::fromUtf8("gridLayout_24"));
        label_58 = new QLabel(groupCheck_fractal_coloring_aux_color_false);
        label_58->setObjectName(QString::fromUtf8("label_58"));
        label_58->setFont(font1);

        gridLayout_24->addWidget(label_58, 0, 0, 1, 1);

        spinbox_fractal_coloring_aux_color_weight = new MyDoubleSpinBox(groupCheck_fractal_coloring_aux_color_false);
        spinbox_fractal_coloring_aux_color_weight->setObjectName(QString::fromUtf8("spinbox_fractal_coloring_aux_color_weight"));
        sizePolicy.setHeightForWidth(spinbox_fractal_coloring_aux_color_weight->sizePolicy().hasHeightForWidth());
        spinbox_fractal_coloring_aux_color_weight->setSizePolicy(sizePolicy);
        spinbox_fractal_coloring_aux_color_weight->setDecimals(6);
        spinbox_fractal_coloring_aux_color_weight->setMinimum(-9999.999900000000707);
        spinbox_fractal_coloring_aux_color_weight->setMaximum(9999.999900000000707);
        spinbox_fractal_coloring_aux_color_weight->setSingleStep(0.100000000000000);

        gridLayout_24->addWidget(spinbox_fractal_coloring_aux_color_weight, 0, 1, 1, 1);

        label_59 = new QLabel(groupCheck_fractal_coloring_aux_color_false);
        label_59->setObjectName(QString::fromUtf8("label_59"));
        label_59->setFont(font1);

        gridLayout_24->addWidget(label_59, 1, 0, 1, 1);

        spinbox_fractal_coloring_aux_color_hybrid_weight = new MyDoubleSpinBox(groupCheck_fractal_coloring_aux_color_false);
        spinbox_fractal_coloring_aux_color_hybrid_weight->setObjectName(QString::fromUtf8("spinbox_fractal_coloring_aux_color_hybrid_weight"));
        sizePolicy.setHeightForWidth(spinbox_fractal_coloring_aux_color_hybrid_weight->sizePolicy().hasHeightForWidth());
        spinbox_fractal_coloring_aux_color_hybrid_weight->setSizePolicy(sizePolicy);
        spinbox_fractal_coloring_aux_color_hybrid_weight->setDecimals(6);
        spinbox_fractal_coloring_aux_color_hybrid_weight->setMinimum(-9999.999900000000707);
        spinbox_fractal_coloring_aux_color_hybrid_weight->setMaximum(9999.999900000000707);
        spinbox_fractal_coloring_aux_color_hybrid_weight->setSingleStep(0.100000000000000);

        gridLayout_24->addWidget(spinbox_fractal_coloring_aux_color_hybrid_weight, 1, 1, 1, 1);

        gridLayout_24->setColumnStretch(1, 1);

        verticalLayout_43->addLayout(gridLayout_24);


        verticalLayout_4->addWidget(groupCheck_fractal_coloring_aux_color_false);

        groupCheck_fractal_coloring_rad_enabled_false = new MyGroupBox(groupBox_2);
        groupCheck_fractal_coloring_rad_enabled_false->setObjectName(QString::fromUtf8("groupCheck_fractal_coloring_rad_enabled_false"));
        groupCheck_fractal_coloring_rad_enabled_false->setCheckable(true);
        verticalLayout_35 = new QVBoxLayout(groupCheck_fractal_coloring_rad_enabled_false);
        verticalLayout_35->setSpacing(2);
        verticalLayout_35->setObjectName(QString::fromUtf8("verticalLayout_35"));
        verticalLayout_35->setContentsMargins(2, 6, 2, 2);
        checkBox_fractal_coloring_rad_div_1e13_false = new MyCheckBox(groupCheck_fractal_coloring_rad_enabled_false);
        checkBox_fractal_coloring_rad_div_1e13_false->setObjectName(QString::fromUtf8("checkBox_fractal_coloring_rad_div_1e13_false"));
        checkBox_fractal_coloring_rad_div_1e13_false->setText(QString::fromUtf8("radius / 1e13"));

        verticalLayout_35->addWidget(checkBox_fractal_coloring_rad_div_1e13_false);

        checkBox_fractal_coloring_rad_squared_enabled_false = new MyCheckBox(groupCheck_fractal_coloring_rad_enabled_false);
        checkBox_fractal_coloring_rad_squared_enabled_false->setObjectName(QString::fromUtf8("checkBox_fractal_coloring_rad_squared_enabled_false"));
        checkBox_fractal_coloring_rad_squared_enabled_false->setText(QString::fromUtf8("radius squared"));

        verticalLayout_35->addWidget(checkBox_fractal_coloring_rad_squared_enabled_false);

        gridLayout_18 = new QGridLayout();
        gridLayout_18->setSpacing(2);
        gridLayout_18->setObjectName(QString::fromUtf8("gridLayout_18"));
        spinbox_fractal_coloring_rad_weight = new MyDoubleSpinBox(groupCheck_fractal_coloring_rad_enabled_false);
        spinbox_fractal_coloring_rad_weight->setObjectName(QString::fromUtf8("spinbox_fractal_coloring_rad_weight"));
        sizePolicy.setHeightForWidth(spinbox_fractal_coloring_rad_weight->sizePolicy().hasHeightForWidth());
        spinbox_fractal_coloring_rad_weight->setSizePolicy(sizePolicy);
        spinbox_fractal_coloring_rad_weight->setDecimals(6);
        spinbox_fractal_coloring_rad_weight->setMinimum(-99999.999899999995250);
        spinbox_fractal_coloring_rad_weight->setMaximum(99999.999899999995250);
        spinbox_fractal_coloring_rad_weight->setSingleStep(0.100000000000000);

        gridLayout_18->addWidget(spinbox_fractal_coloring_rad_weight, 1, 1, 1, 1);

        label_52 = new QLabel(groupCheck_fractal_coloring_rad_enabled_false);
        label_52->setObjectName(QString::fromUtf8("label_52"));

        gridLayout_18->addWidget(label_52, 1, 0, 1, 1);

        gridLayout_18->setColumnStretch(1, 1);

        verticalLayout_35->addLayout(gridLayout_18);


        verticalLayout_4->addWidget(groupCheck_fractal_coloring_rad_enabled_false);

        groupCheck_fractal_coloring_rad_div_de_enabled_false = new MyGroupBox(groupBox_2);
        groupCheck_fractal_coloring_rad_div_de_enabled_false->setObjectName(QString::fromUtf8("groupCheck_fractal_coloring_rad_div_de_enabled_false"));
        groupCheck_fractal_coloring_rad_div_de_enabled_false->setCheckable(true);
        verticalLayout_36 = new QVBoxLayout(groupCheck_fractal_coloring_rad_div_de_enabled_false);
        verticalLayout_36->setSpacing(2);
        verticalLayout_36->setObjectName(QString::fromUtf8("verticalLayout_36"));
        verticalLayout_36->setContentsMargins(2, 6, 2, 2);
        label_84 = new QLabel(groupCheck_fractal_coloring_rad_div_de_enabled_false);
        label_84->setObjectName(QString::fromUtf8("label_84"));
        label_84->setFont(font1);

        verticalLayout_36->addWidget(label_84);

        checkBox_fractal_coloring_rad_div_de_1e13_false = new MyCheckBox(groupCheck_fractal_coloring_rad_div_de_enabled_false);
        checkBox_fractal_coloring_rad_div_de_1e13_false->setObjectName(QString::fromUtf8("checkBox_fractal_coloring_rad_div_de_1e13_false"));
        checkBox_fractal_coloring_rad_div_de_1e13_false->setText(QString::fromUtf8("radius / 1e13"));

        verticalLayout_36->addWidget(checkBox_fractal_coloring_rad_div_de_1e13_false);

        checkBox_fractal_coloring_rad_div_de_squared_false = new MyCheckBox(groupCheck_fractal_coloring_rad_div_de_enabled_false);
        checkBox_fractal_coloring_rad_div_de_squared_false->setObjectName(QString::fromUtf8("checkBox_fractal_coloring_rad_div_de_squared_false"));
        checkBox_fractal_coloring_rad_div_de_squared_false->setText(QString::fromUtf8("radius squared"));

        verticalLayout_36->addWidget(checkBox_fractal_coloring_rad_div_de_squared_false);

        gridLayout_19 = new QGridLayout();
        gridLayout_19->setSpacing(2);
        gridLayout_19->setObjectName(QString::fromUtf8("gridLayout_19"));
        spinbox_fractal_coloring_rad_div_de_weight = new MyDoubleSpinBox(groupCheck_fractal_coloring_rad_div_de_enabled_false);
        spinbox_fractal_coloring_rad_div_de_weight->setObjectName(QString::fromUtf8("spinbox_fractal_coloring_rad_div_de_weight"));
        sizePolicy.setHeightForWidth(spinbox_fractal_coloring_rad_div_de_weight->sizePolicy().hasHeightForWidth());
        spinbox_fractal_coloring_rad_div_de_weight->setSizePolicy(sizePolicy);
        spinbox_fractal_coloring_rad_div_de_weight->setDecimals(6);
        spinbox_fractal_coloring_rad_div_de_weight->setMinimum(-99999.999899999995250);
        spinbox_fractal_coloring_rad_div_de_weight->setMaximum(99999.999899999995250);
        spinbox_fractal_coloring_rad_div_de_weight->setSingleStep(0.100000000000000);

        gridLayout_19->addWidget(spinbox_fractal_coloring_rad_div_de_weight, 1, 1, 1, 1);

        label_53 = new QLabel(groupCheck_fractal_coloring_rad_div_de_enabled_false);
        label_53->setObjectName(QString::fromUtf8("label_53"));

        gridLayout_19->addWidget(label_53, 1, 0, 1, 1);

        gridLayout_19->setColumnStretch(1, 1);

        verticalLayout_36->addLayout(gridLayout_19);


        verticalLayout_4->addWidget(groupCheck_fractal_coloring_rad_div_de_enabled_false);

        groupCheck_fractal_coloring_xyz_bias_enabled_false = new MyGroupBox(groupBox_2);
        groupCheck_fractal_coloring_xyz_bias_enabled_false->setObjectName(QString::fromUtf8("groupCheck_fractal_coloring_xyz_bias_enabled_false"));
        groupCheck_fractal_coloring_xyz_bias_enabled_false->setCheckable(true);
        verticalLayout_32 = new QVBoxLayout(groupCheck_fractal_coloring_xyz_bias_enabled_false);
        verticalLayout_32->setSpacing(2);
        verticalLayout_32->setObjectName(QString::fromUtf8("verticalLayout_32"));
        verticalLayout_32->setContentsMargins(2, 2, 2, 2);
        checkBox_fractal_coloring_xyz_div_1e13_false = new MyCheckBox(groupCheck_fractal_coloring_xyz_bias_enabled_false);
        checkBox_fractal_coloring_xyz_div_1e13_false->setObjectName(QString::fromUtf8("checkBox_fractal_coloring_xyz_div_1e13_false"));
        checkBox_fractal_coloring_xyz_div_1e13_false->setText(QString::fromUtf8("xyz / 1e13"));

        verticalLayout_32->addWidget(checkBox_fractal_coloring_xyz_div_1e13_false);

        gridLayout_16 = new QGridLayout();
        gridLayout_16->setSpacing(2);
        gridLayout_16->setObjectName(QString::fromUtf8("gridLayout_16"));
        checkBox_fractal_coloring_xyz_x_sqrd_enabled_false = new MyCheckBox(groupCheck_fractal_coloring_xyz_bias_enabled_false);
        checkBox_fractal_coloring_xyz_x_sqrd_enabled_false->setObjectName(QString::fromUtf8("checkBox_fractal_coloring_xyz_x_sqrd_enabled_false"));
        checkBox_fractal_coloring_xyz_x_sqrd_enabled_false->setText(QString::fromUtf8(""));

        gridLayout_16->addWidget(checkBox_fractal_coloring_xyz_x_sqrd_enabled_false, 1, 2, 1, 1);

        checkBox_fractal_coloring_xyz_z_sqrd_enabled_false = new MyCheckBox(groupCheck_fractal_coloring_xyz_bias_enabled_false);
        checkBox_fractal_coloring_xyz_z_sqrd_enabled_false->setObjectName(QString::fromUtf8("checkBox_fractal_coloring_xyz_z_sqrd_enabled_false"));
        checkBox_fractal_coloring_xyz_z_sqrd_enabled_false->setText(QString::fromUtf8(""));

        gridLayout_16->addWidget(checkBox_fractal_coloring_xyz_z_sqrd_enabled_false, 3, 2, 1, 1);

        label_40 = new QLabel(groupCheck_fractal_coloring_xyz_bias_enabled_false);
        label_40->setObjectName(QString::fromUtf8("label_40"));

        gridLayout_16->addWidget(label_40, 3, 0, 1, 1);

        spinbox3_fractal_coloring_xyz_000_y = new MyDoubleSpinBox(groupCheck_fractal_coloring_xyz_bias_enabled_false);
        spinbox3_fractal_coloring_xyz_000_y->setObjectName(QString::fromUtf8("spinbox3_fractal_coloring_xyz_000_y"));
        sizePolicy.setHeightForWidth(spinbox3_fractal_coloring_xyz_000_y->sizePolicy().hasHeightForWidth());
        spinbox3_fractal_coloring_xyz_000_y->setSizePolicy(sizePolicy);
        spinbox3_fractal_coloring_xyz_000_y->setDecimals(6);
        spinbox3_fractal_coloring_xyz_000_y->setMinimum(-9999.999900000000707);
        spinbox3_fractal_coloring_xyz_000_y->setMaximum(9999.999900000000707);
        spinbox3_fractal_coloring_xyz_000_y->setSingleStep(0.100000000000000);

        gridLayout_16->addWidget(spinbox3_fractal_coloring_xyz_000_y, 2, 1, 1, 1);

        spinbox_fractal_coloring_xyz_iter_scale = new MyDoubleSpinBox(groupCheck_fractal_coloring_xyz_bias_enabled_false);
        spinbox_fractal_coloring_xyz_iter_scale->setObjectName(QString::fromUtf8("spinbox_fractal_coloring_xyz_iter_scale"));
        sizePolicy.setHeightForWidth(spinbox_fractal_coloring_xyz_iter_scale->sizePolicy().hasHeightForWidth());
        spinbox_fractal_coloring_xyz_iter_scale->setSizePolicy(sizePolicy);
        spinbox_fractal_coloring_xyz_iter_scale->setDecimals(6);
        spinbox_fractal_coloring_xyz_iter_scale->setMinimum(-9999.999900000000707);
        spinbox_fractal_coloring_xyz_iter_scale->setMaximum(9999.999900000000707);
        spinbox_fractal_coloring_xyz_iter_scale->setSingleStep(0.100000000000000);

        gridLayout_16->addWidget(spinbox_fractal_coloring_xyz_iter_scale, 0, 1, 1, 1);

        checkBox_fractal_coloring_xyz_y_sqrd_enabled_false = new MyCheckBox(groupCheck_fractal_coloring_xyz_bias_enabled_false);
        checkBox_fractal_coloring_xyz_y_sqrd_enabled_false->setObjectName(QString::fromUtf8("checkBox_fractal_coloring_xyz_y_sqrd_enabled_false"));
        checkBox_fractal_coloring_xyz_y_sqrd_enabled_false->setText(QString::fromUtf8(""));

        gridLayout_16->addWidget(checkBox_fractal_coloring_xyz_y_sqrd_enabled_false, 2, 2, 1, 1);

        label_35 = new QLabel(groupCheck_fractal_coloring_xyz_bias_enabled_false);
        label_35->setObjectName(QString::fromUtf8("label_35"));

        gridLayout_16->addWidget(label_35, 0, 0, 1, 1);

        label_38 = new QLabel(groupCheck_fractal_coloring_xyz_bias_enabled_false);
        label_38->setObjectName(QString::fromUtf8("label_38"));

        gridLayout_16->addWidget(label_38, 2, 0, 1, 1);

        spinbox3_fractal_coloring_xyz_000_x = new MyDoubleSpinBox(groupCheck_fractal_coloring_xyz_bias_enabled_false);
        spinbox3_fractal_coloring_xyz_000_x->setObjectName(QString::fromUtf8("spinbox3_fractal_coloring_xyz_000_x"));
        sizePolicy.setHeightForWidth(spinbox3_fractal_coloring_xyz_000_x->sizePolicy().hasHeightForWidth());
        spinbox3_fractal_coloring_xyz_000_x->setSizePolicy(sizePolicy);
        spinbox3_fractal_coloring_xyz_000_x->setDecimals(6);
        spinbox3_fractal_coloring_xyz_000_x->setMinimum(-9999.999900000000707);
        spinbox3_fractal_coloring_xyz_000_x->setMaximum(9999.999900000000707);
        spinbox3_fractal_coloring_xyz_000_x->setSingleStep(0.100000000000000);

        gridLayout_16->addWidget(spinbox3_fractal_coloring_xyz_000_x, 1, 1, 1, 1);

        label_39 = new QLabel(groupCheck_fractal_coloring_xyz_bias_enabled_false);
        label_39->setObjectName(QString::fromUtf8("label_39"));

        gridLayout_16->addWidget(label_39, 0, 2, 1, 1);

        spinbox3_fractal_coloring_xyz_000_z = new MyDoubleSpinBox(groupCheck_fractal_coloring_xyz_bias_enabled_false);
        spinbox3_fractal_coloring_xyz_000_z->setObjectName(QString::fromUtf8("spinbox3_fractal_coloring_xyz_000_z"));
        sizePolicy.setHeightForWidth(spinbox3_fractal_coloring_xyz_000_z->sizePolicy().hasHeightForWidth());
        spinbox3_fractal_coloring_xyz_000_z->setSizePolicy(sizePolicy);
        spinbox3_fractal_coloring_xyz_000_z->setDecimals(6);
        spinbox3_fractal_coloring_xyz_000_z->setMinimum(-9999.999900000000707);
        spinbox3_fractal_coloring_xyz_000_z->setMaximum(9999.999900000000707);
        spinbox3_fractal_coloring_xyz_000_z->setSingleStep(0.100000000000000);

        gridLayout_16->addWidget(spinbox3_fractal_coloring_xyz_000_z, 3, 1, 1, 1);

        label_36 = new QLabel(groupCheck_fractal_coloring_xyz_bias_enabled_false);
        label_36->setObjectName(QString::fromUtf8("label_36"));

        gridLayout_16->addWidget(label_36, 1, 0, 1, 1);

        gridLayout_16->setColumnStretch(1, 1);

        verticalLayout_32->addLayout(gridLayout_16);

        checkBox_fractal_coloring_xyz_fabs_enabled_false = new MyCheckBox(groupCheck_fractal_coloring_xyz_bias_enabled_false);
        checkBox_fractal_coloring_xyz_fabs_enabled_false->setObjectName(QString::fromUtf8("checkBox_fractal_coloring_xyz_fabs_enabled_false"));
        checkBox_fractal_coloring_xyz_fabs_enabled_false->setText(QString::fromUtf8("disable abs(). May need to increase initial colorValue."));

        verticalLayout_32->addWidget(checkBox_fractal_coloring_xyz_fabs_enabled_false);


        verticalLayout_4->addWidget(groupCheck_fractal_coloring_xyz_bias_enabled_false);

        groupCheck_fractal_coloring_iter_group_enabled_false = new MyGroupBox(groupBox_2);
        groupCheck_fractal_coloring_iter_group_enabled_false->setObjectName(QString::fromUtf8("groupCheck_fractal_coloring_iter_group_enabled_false"));
        groupCheck_fractal_coloring_iter_group_enabled_false->setCheckable(true);
        verticalLayout_37 = new QVBoxLayout(groupCheck_fractal_coloring_iter_group_enabled_false);
        verticalLayout_37->setSpacing(2);
        verticalLayout_37->setObjectName(QString::fromUtf8("verticalLayout_37"));
        verticalLayout_37->setContentsMargins(2, 2, 2, 2);
        gridLayout_20 = new QGridLayout();
        gridLayout_20->setSpacing(2);
        gridLayout_20->setObjectName(QString::fromUtf8("gridLayout_20"));
        checkBox_fractal_coloring_iter_add_scale_enabled_true = new MyCheckBox(groupCheck_fractal_coloring_iter_group_enabled_false);
        checkBox_fractal_coloring_iter_add_scale_enabled_true->setObjectName(QString::fromUtf8("checkBox_fractal_coloring_iter_add_scale_enabled_true"));
        checkBox_fractal_coloring_iter_add_scale_enabled_true->setText(QString::fromUtf8("addition value:"));

        gridLayout_20->addWidget(checkBox_fractal_coloring_iter_add_scale_enabled_true, 1, 0, 1, 1);

        spinbox_fractal_coloring_iter_add_scale = new MyDoubleSpinBox(groupCheck_fractal_coloring_iter_group_enabled_false);
        spinbox_fractal_coloring_iter_add_scale->setObjectName(QString::fromUtf8("spinbox_fractal_coloring_iter_add_scale"));
        sizePolicy.setHeightForWidth(spinbox_fractal_coloring_iter_add_scale->sizePolicy().hasHeightForWidth());
        spinbox_fractal_coloring_iter_add_scale->setSizePolicy(sizePolicy);
        spinbox_fractal_coloring_iter_add_scale->setDecimals(6);
        spinbox_fractal_coloring_iter_add_scale->setMinimum(-9999.999900000000707);
        spinbox_fractal_coloring_iter_add_scale->setMaximum(9999.999900000000707);
        spinbox_fractal_coloring_iter_add_scale->setSingleStep(0.100000000000000);

        gridLayout_20->addWidget(spinbox_fractal_coloring_iter_add_scale, 1, 1, 1, 1);

        checkBox_fractal_coloring_iter_scale_enabled_false = new MyCheckBox(groupCheck_fractal_coloring_iter_group_enabled_false);
        checkBox_fractal_coloring_iter_scale_enabled_false->setObjectName(QString::fromUtf8("checkBox_fractal_coloring_iter_scale_enabled_false"));
        checkBox_fractal_coloring_iter_scale_enabled_false->setText(QString::fromUtf8(" scale (needs an input value):"));

        gridLayout_20->addWidget(checkBox_fractal_coloring_iter_scale_enabled_false, 2, 0, 1, 1);

        spinboxInt_fractal_coloring_i_start_value = new MySpinBox(groupCheck_fractal_coloring_iter_group_enabled_false);
        spinboxInt_fractal_coloring_i_start_value->setObjectName(QString::fromUtf8("spinboxInt_fractal_coloring_i_start_value"));
        sizePolicy.setHeightForWidth(spinboxInt_fractal_coloring_i_start_value->sizePolicy().hasHeightForWidth());
        spinboxInt_fractal_coloring_i_start_value->setSizePolicy(sizePolicy);
        spinboxInt_fractal_coloring_i_start_value->setMaximum(999);

        gridLayout_20->addWidget(spinboxInt_fractal_coloring_i_start_value, 0, 1, 1, 1);

        spinbox_fractal_coloring_iter_scale = new MyDoubleSpinBox(groupCheck_fractal_coloring_iter_group_enabled_false);
        spinbox_fractal_coloring_iter_scale->setObjectName(QString::fromUtf8("spinbox_fractal_coloring_iter_scale"));
        sizePolicy.setHeightForWidth(spinbox_fractal_coloring_iter_scale->sizePolicy().hasHeightForWidth());
        spinbox_fractal_coloring_iter_scale->setSizePolicy(sizePolicy);
        spinbox_fractal_coloring_iter_scale->setDecimals(6);
        spinbox_fractal_coloring_iter_scale->setMinimum(-9999.999900000000707);
        spinbox_fractal_coloring_iter_scale->setMaximum(9999.999900000000707);
        spinbox_fractal_coloring_iter_scale->setSingleStep(0.100000000000000);

        gridLayout_20->addWidget(spinbox_fractal_coloring_iter_scale, 2, 1, 1, 1);

        label_42 = new QLabel(groupCheck_fractal_coloring_iter_group_enabled_false);
        label_42->setObjectName(QString::fromUtf8("label_42"));

        gridLayout_20->addWidget(label_42, 0, 0, 1, 1);

        gridLayout_20->setColumnStretch(1, 1);

        verticalLayout_37->addLayout(gridLayout_20);


        verticalLayout_4->addWidget(groupCheck_fractal_coloring_iter_group_enabled_false);


        verticalLayout_29->addWidget(groupBox_2);

        groupBox_5 = new QGroupBox(groupCheck_fractal_coloring_extra_color_enabled_false);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        verticalLayout_7 = new QVBoxLayout(groupBox_5);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(2, 2, 2, 2);
        groupCheck_fractal_coloring_global_palette_false = new MyGroupBox(groupBox_5);
        groupCheck_fractal_coloring_global_palette_false->setObjectName(QString::fromUtf8("groupCheck_fractal_coloring_global_palette_false"));
        groupCheck_fractal_coloring_global_palette_false->setCheckable(true);
        verticalLayout_41 = new QVBoxLayout(groupCheck_fractal_coloring_global_palette_false);
        verticalLayout_41->setSpacing(2);
        verticalLayout_41->setObjectName(QString::fromUtf8("verticalLayout_41"));
        verticalLayout_41->setContentsMargins(2, 2, 2, 2);
        groupCheck_fractal_coloring_add_enabled_false = new MyGroupBox(groupCheck_fractal_coloring_global_palette_false);
        groupCheck_fractal_coloring_add_enabled_false->setObjectName(QString::fromUtf8("groupCheck_fractal_coloring_add_enabled_false"));
        groupCheck_fractal_coloring_add_enabled_false->setCheckable(true);
        verticalLayout_38 = new QVBoxLayout(groupCheck_fractal_coloring_add_enabled_false);
        verticalLayout_38->setSpacing(2);
        verticalLayout_38->setObjectName(QString::fromUtf8("verticalLayout_38"));
        verticalLayout_38->setContentsMargins(2, 2, 2, 2);
        gridLayout_11 = new QGridLayout();
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        gridLayout_11->setContentsMargins(-1, 0, -1, -1);
        spinbox_fractal_coloring_add_spread = new MyDoubleSpinBox(groupCheck_fractal_coloring_add_enabled_false);
        spinbox_fractal_coloring_add_spread->setObjectName(QString::fromUtf8("spinbox_fractal_coloring_add_spread"));
        sizePolicy.setHeightForWidth(spinbox_fractal_coloring_add_spread->sizePolicy().hasHeightForWidth());
        spinbox_fractal_coloring_add_spread->setSizePolicy(sizePolicy);
        spinbox_fractal_coloring_add_spread->setDecimals(2);
        spinbox_fractal_coloring_add_spread->setMinimum(0.000000000000000);
        spinbox_fractal_coloring_add_spread->setMaximum(999999.989999999990687);
        spinbox_fractal_coloring_add_spread->setSingleStep(0.100000000000000);

        gridLayout_11->addWidget(spinbox_fractal_coloring_add_spread, 1, 1, 1, 1);

        label_68 = new QLabel(groupCheck_fractal_coloring_add_enabled_false);
        label_68->setObjectName(QString::fromUtf8("label_68"));

        gridLayout_11->addWidget(label_68, 1, 0, 1, 1);

        label_76 = new QLabel(groupCheck_fractal_coloring_add_enabled_false);
        label_76->setObjectName(QString::fromUtf8("label_76"));

        gridLayout_11->addWidget(label_76, 0, 0, 1, 1);

        spinbox_fractal_coloring_add_start_value = new MyDoubleSpinBox(groupCheck_fractal_coloring_add_enabled_false);
        spinbox_fractal_coloring_add_start_value->setObjectName(QString::fromUtf8("spinbox_fractal_coloring_add_start_value"));
        sizePolicy.setHeightForWidth(spinbox_fractal_coloring_add_start_value->sizePolicy().hasHeightForWidth());
        spinbox_fractal_coloring_add_start_value->setSizePolicy(sizePolicy);
        spinbox_fractal_coloring_add_start_value->setDecimals(2);
        spinbox_fractal_coloring_add_start_value->setMinimum(0.000000000000000);
        spinbox_fractal_coloring_add_start_value->setMaximum(999999.989999999990687);
        spinbox_fractal_coloring_add_start_value->setSingleStep(1.000000000000000);

        gridLayout_11->addWidget(spinbox_fractal_coloring_add_start_value, 2, 1, 1, 1);

        label_77 = new QLabel(groupCheck_fractal_coloring_add_enabled_false);
        label_77->setObjectName(QString::fromUtf8("label_77"));

        gridLayout_11->addWidget(label_77, 2, 0, 1, 1);

        spinbox_fractal_coloring_add_max = new MyDoubleSpinBox(groupCheck_fractal_coloring_add_enabled_false);
        spinbox_fractal_coloring_add_max->setObjectName(QString::fromUtf8("spinbox_fractal_coloring_add_max"));
        sizePolicy.setHeightForWidth(spinbox_fractal_coloring_add_max->sizePolicy().hasHeightForWidth());
        spinbox_fractal_coloring_add_max->setSizePolicy(sizePolicy);
        spinbox_fractal_coloring_add_max->setDecimals(6);
        spinbox_fractal_coloring_add_max->setMinimum(-9999.999998999999661);
        spinbox_fractal_coloring_add_max->setMaximum(9999.999998999999661);
        spinbox_fractal_coloring_add_max->setSingleStep(0.100000000000000);

        gridLayout_11->addWidget(spinbox_fractal_coloring_add_max, 0, 1, 1, 1);

        gridLayout_11->setColumnStretch(1, 1);

        verticalLayout_38->addLayout(gridLayout_11);


        verticalLayout_41->addWidget(groupCheck_fractal_coloring_add_enabled_false);

        groupCheck_fractal_coloring_parab_enabled_false = new MyGroupBox(groupCheck_fractal_coloring_global_palette_false);
        groupCheck_fractal_coloring_parab_enabled_false->setObjectName(QString::fromUtf8("groupCheck_fractal_coloring_parab_enabled_false"));
        groupCheck_fractal_coloring_parab_enabled_false->setCheckable(true);
        verticalLayout_40 = new QVBoxLayout(groupCheck_fractal_coloring_parab_enabled_false);
        verticalLayout_40->setSpacing(2);
        verticalLayout_40->setObjectName(QString::fromUtf8("verticalLayout_40"));
        verticalLayout_40->setContentsMargins(2, 2, 2, 2);
        gridLayout_15 = new QGridLayout();
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        gridLayout_15->setContentsMargins(-1, 0, -1, -1);
        label_79 = new QLabel(groupCheck_fractal_coloring_parab_enabled_false);
        label_79->setObjectName(QString::fromUtf8("label_79"));

        gridLayout_15->addWidget(label_79, 0, 0, 1, 1);

        label_80 = new QLabel(groupCheck_fractal_coloring_parab_enabled_false);
        label_80->setObjectName(QString::fromUtf8("label_80"));

        gridLayout_15->addWidget(label_80, 1, 0, 1, 1);

        spinbox_fractal_coloring_parab_start_value = new MyDoubleSpinBox(groupCheck_fractal_coloring_parab_enabled_false);
        spinbox_fractal_coloring_parab_start_value->setObjectName(QString::fromUtf8("spinbox_fractal_coloring_parab_start_value"));
        sizePolicy.setHeightForWidth(spinbox_fractal_coloring_parab_start_value->sizePolicy().hasHeightForWidth());
        spinbox_fractal_coloring_parab_start_value->setSizePolicy(sizePolicy);
        spinbox_fractal_coloring_parab_start_value->setDecimals(2);
        spinbox_fractal_coloring_parab_start_value->setMinimum(0.000000000000000);
        spinbox_fractal_coloring_parab_start_value->setMaximum(999999.989999999990687);
        spinbox_fractal_coloring_parab_start_value->setSingleStep(0.100000000000000);

        gridLayout_15->addWidget(spinbox_fractal_coloring_parab_start_value, 1, 1, 1, 1);

        spinbox_fractal_coloring_parab_scale = new MyDoubleSpinBox(groupCheck_fractal_coloring_parab_enabled_false);
        spinbox_fractal_coloring_parab_scale->setObjectName(QString::fromUtf8("spinbox_fractal_coloring_parab_scale"));
        sizePolicy.setHeightForWidth(spinbox_fractal_coloring_parab_scale->sizePolicy().hasHeightForWidth());
        spinbox_fractal_coloring_parab_scale->setSizePolicy(sizePolicy);
        spinbox_fractal_coloring_parab_scale->setDecimals(6);
        spinbox_fractal_coloring_parab_scale->setMinimum(-999.990000000000009);
        spinbox_fractal_coloring_parab_scale->setMaximum(999.990000000000009);
        spinbox_fractal_coloring_parab_scale->setSingleStep(0.100000000000000);

        gridLayout_15->addWidget(spinbox_fractal_coloring_parab_scale, 0, 1, 1, 1);

        gridLayout_15->setColumnStretch(1, 1);

        verticalLayout_40->addLayout(gridLayout_15);


        verticalLayout_41->addWidget(groupCheck_fractal_coloring_parab_enabled_false);

        groupCheck_fractal_coloring_cos_enabled_false = new MyGroupBox(groupCheck_fractal_coloring_global_palette_false);
        groupCheck_fractal_coloring_cos_enabled_false->setObjectName(QString::fromUtf8("groupCheck_fractal_coloring_cos_enabled_false"));
        groupCheck_fractal_coloring_cos_enabled_false->setCheckable(true);
        verticalLayout_34 = new QVBoxLayout(groupCheck_fractal_coloring_cos_enabled_false);
        verticalLayout_34->setSpacing(2);
        verticalLayout_34->setObjectName(QString::fromUtf8("verticalLayout_34"));
        verticalLayout_34->setContentsMargins(2, 2, 2, 2);
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(-1, 0, -1, -1);
        spinbox_fractal_coloring_cos_add = new MyDoubleSpinBox(groupCheck_fractal_coloring_cos_enabled_false);
        spinbox_fractal_coloring_cos_add->setObjectName(QString::fromUtf8("spinbox_fractal_coloring_cos_add"));
        sizePolicy.setHeightForWidth(spinbox_fractal_coloring_cos_add->sizePolicy().hasHeightForWidth());
        spinbox_fractal_coloring_cos_add->setSizePolicy(sizePolicy);
        spinbox_fractal_coloring_cos_add->setDecimals(6);
        spinbox_fractal_coloring_cos_add->setMinimum(-9999.999900000000707);
        spinbox_fractal_coloring_cos_add->setMaximum(9999.999900000000707);
        spinbox_fractal_coloring_cos_add->setSingleStep(0.100000000000000);

        gridLayout_5->addWidget(spinbox_fractal_coloring_cos_add, 1, 1, 1, 1);

        label_48 = new QLabel(groupCheck_fractal_coloring_cos_enabled_false);
        label_48->setObjectName(QString::fromUtf8("label_48"));

        gridLayout_5->addWidget(label_48, 1, 0, 1, 1);

        label_47 = new QLabel(groupCheck_fractal_coloring_cos_enabled_false);
        label_47->setObjectName(QString::fromUtf8("label_47"));

        gridLayout_5->addWidget(label_47, 0, 0, 1, 1);

        spinbox_fractal_coloring_cos_start_value = new MyDoubleSpinBox(groupCheck_fractal_coloring_cos_enabled_false);
        spinbox_fractal_coloring_cos_start_value->setObjectName(QString::fromUtf8("spinbox_fractal_coloring_cos_start_value"));
        sizePolicy.setHeightForWidth(spinbox_fractal_coloring_cos_start_value->sizePolicy().hasHeightForWidth());
        spinbox_fractal_coloring_cos_start_value->setSizePolicy(sizePolicy);
        spinbox_fractal_coloring_cos_start_value->setDecimals(2);
        spinbox_fractal_coloring_cos_start_value->setMinimum(0.000000000000000);
        spinbox_fractal_coloring_cos_start_value->setMaximum(999999.989999999990687);
        spinbox_fractal_coloring_cos_start_value->setSingleStep(1.000000000000000);

        gridLayout_5->addWidget(spinbox_fractal_coloring_cos_start_value, 2, 1, 1, 1);

        label_51 = new QLabel(groupCheck_fractal_coloring_cos_enabled_false);
        label_51->setObjectName(QString::fromUtf8("label_51"));

        gridLayout_5->addWidget(label_51, 2, 0, 1, 1);

        spinbox_fractal_coloring_cos_period = new MyDoubleSpinBox(groupCheck_fractal_coloring_cos_enabled_false);
        spinbox_fractal_coloring_cos_period->setObjectName(QString::fromUtf8("spinbox_fractal_coloring_cos_period"));
        sizePolicy.setHeightForWidth(spinbox_fractal_coloring_cos_period->sizePolicy().hasHeightForWidth());
        spinbox_fractal_coloring_cos_period->setSizePolicy(sizePolicy);
        spinbox_fractal_coloring_cos_period->setDecimals(6);
        spinbox_fractal_coloring_cos_period->setMinimum(0.000000000000000);
        spinbox_fractal_coloring_cos_period->setMaximum(9999.999900000000707);
        spinbox_fractal_coloring_cos_period->setSingleStep(0.100000000000000);

        gridLayout_5->addWidget(spinbox_fractal_coloring_cos_period, 0, 1, 1, 1);

        gridLayout_5->setColumnStretch(1, 1);

        verticalLayout_34->addLayout(gridLayout_5);


        verticalLayout_41->addWidget(groupCheck_fractal_coloring_cos_enabled_false);

        gridLayout_22 = new QGridLayout();
        gridLayout_22->setObjectName(QString::fromUtf8("gridLayout_22"));
        gridLayout_22->setContentsMargins(-1, 0, -1, -1);
        groupCheck_fractal_coloring_round_enabled_false = new MyGroupBox(groupCheck_fractal_coloring_global_palette_false);
        groupCheck_fractal_coloring_round_enabled_false->setObjectName(QString::fromUtf8("groupCheck_fractal_coloring_round_enabled_false"));
        groupCheck_fractal_coloring_round_enabled_false->setCheckable(true);
        verticalLayout_39 = new QVBoxLayout(groupCheck_fractal_coloring_round_enabled_false);
        verticalLayout_39->setSpacing(2);
        verticalLayout_39->setObjectName(QString::fromUtf8("verticalLayout_39"));
        verticalLayout_39->setContentsMargins(2, 2, 2, 2);
        gridLayout_21 = new QGridLayout();
        gridLayout_21->setObjectName(QString::fromUtf8("gridLayout_21"));
        gridLayout_21->setContentsMargins(-1, 0, -1, -1);
        spinbox_fractal_coloring_round_scale = new MyDoubleSpinBox(groupCheck_fractal_coloring_round_enabled_false);
        spinbox_fractal_coloring_round_scale->setObjectName(QString::fromUtf8("spinbox_fractal_coloring_round_scale"));
        sizePolicy.setHeightForWidth(spinbox_fractal_coloring_round_scale->sizePolicy().hasHeightForWidth());
        spinbox_fractal_coloring_round_scale->setSizePolicy(sizePolicy);
        spinbox_fractal_coloring_round_scale->setDecimals(2);
        spinbox_fractal_coloring_round_scale->setMinimum(0.000000000000000);
        spinbox_fractal_coloring_round_scale->setMaximum(99999999.000000000000000);
        spinbox_fractal_coloring_round_scale->setSingleStep(0.100000000000000);

        gridLayout_21->addWidget(spinbox_fractal_coloring_round_scale, 0, 1, 1, 1);

        label_57 = new QLabel(groupCheck_fractal_coloring_round_enabled_false);
        label_57->setObjectName(QString::fromUtf8("label_57"));

        gridLayout_21->addWidget(label_57, 0, 0, 1, 1);

        gridLayout_21->setColumnStretch(1, 1);

        verticalLayout_39->addLayout(gridLayout_21);


        gridLayout_22->addWidget(groupCheck_fractal_coloring_round_enabled_false, 0, 0, 1, 1);


        verticalLayout_41->addLayout(gridLayout_22);


        verticalLayout_7->addWidget(groupCheck_fractal_coloring_global_palette_false);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_34 = new QLabel(groupBox_5);
        label_34->setObjectName(QString::fromUtf8("label_34"));

        gridLayout_6->addWidget(label_34, 0, 0, 1, 1);

        spinbox_fractal_coloring_min_color_value = new MyDoubleSpinBox(groupBox_5);
        spinbox_fractal_coloring_min_color_value->setObjectName(QString::fromUtf8("spinbox_fractal_coloring_min_color_value"));
        sizePolicy.setHeightForWidth(spinbox_fractal_coloring_min_color_value->sizePolicy().hasHeightForWidth());
        spinbox_fractal_coloring_min_color_value->setSizePolicy(sizePolicy);
        spinbox_fractal_coloring_min_color_value->setDecimals(2);
        spinbox_fractal_coloring_min_color_value->setMinimum(0.000000000000000);
        spinbox_fractal_coloring_min_color_value->setMaximum(99999999.000000000000000);
        spinbox_fractal_coloring_min_color_value->setSingleStep(1.000000000000000);

        gridLayout_6->addWidget(spinbox_fractal_coloring_min_color_value, 0, 1, 1, 1);

        label_37 = new QLabel(groupBox_5);
        label_37->setObjectName(QString::fromUtf8("label_37"));

        gridLayout_6->addWidget(label_37, 1, 0, 1, 1);

        spinbox_fractal_coloring_max_color_value = new MyDoubleSpinBox(groupBox_5);
        spinbox_fractal_coloring_max_color_value->setObjectName(QString::fromUtf8("spinbox_fractal_coloring_max_color_value"));
        sizePolicy.setHeightForWidth(spinbox_fractal_coloring_max_color_value->sizePolicy().hasHeightForWidth());
        spinbox_fractal_coloring_max_color_value->setSizePolicy(sizePolicy);
        spinbox_fractal_coloring_max_color_value->setDecimals(2);
        spinbox_fractal_coloring_max_color_value->setMinimum(0.000000000000000);
        spinbox_fractal_coloring_max_color_value->setMaximum(99999999.000000000000000);
        spinbox_fractal_coloring_max_color_value->setSingleStep(1.000000000000000);

        gridLayout_6->addWidget(spinbox_fractal_coloring_max_color_value, 1, 1, 1, 1);

        gridLayout_6->setColumnStretch(1, 1);

        verticalLayout_7->addLayout(gridLayout_6);


        verticalLayout_29->addWidget(groupBox_5);


        verticalLayout_70->addWidget(groupCheck_fractal_coloring_extra_color_enabled_false);


        verticalLayout_2->addWidget(groupCheck_use_colors_from_palette);

        groupBox = new QGroupBox(scrollAreaWidgetContents_3);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_6 = new QVBoxLayout(groupBox);
        verticalLayout_6->setSpacing(2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(2, 2, 2, 2);
        gridLayout_8 = new QGridLayout();
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_8->setContentsMargins(-1, 0, -1, -1);
        colorButton_surface_color = new MyColorButton(groupBox);
        colorButton_surface_color->setObjectName(QString::fromUtf8("colorButton_surface_color"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(colorButton_surface_color->sizePolicy().hasHeightForWidth());
        colorButton_surface_color->setSizePolicy(sizePolicy2);

        gridLayout_8->addWidget(colorButton_surface_color, 0, 1, 1, 1);

        label_56 = new QLabel(groupBox);
        label_56->setObjectName(QString::fromUtf8("label_56"));

        gridLayout_8->addWidget(label_56, 0, 0, 1, 1);


        verticalLayout_6->addLayout(gridLayout_8);

        groupCheck_use_color_texture = new MyGroupBox(groupBox);
        groupCheck_use_color_texture->setObjectName(QString::fromUtf8("groupCheck_use_color_texture"));
        groupCheck_use_color_texture->setCheckable(true);
        verticalLayout_141 = new QVBoxLayout(groupCheck_use_color_texture);
        verticalLayout_141->setSpacing(2);
        verticalLayout_141->setObjectName(QString::fromUtf8("verticalLayout_141"));
        verticalLayout_141->setContentsMargins(2, 2, 2, 2);
        gridLayout_95 = new QGridLayout();
        gridLayout_95->setSpacing(2);
        gridLayout_95->setObjectName(QString::fromUtf8("gridLayout_95"));
        label_378 = new QLabel(groupCheck_use_color_texture);
        label_378->setObjectName(QString::fromUtf8("label_378"));

        gridLayout_95->addWidget(label_378, 1, 0, 1, 1);

        label_377 = new QLabel(groupCheck_use_color_texture);
        label_377->setObjectName(QString::fromUtf8("label_377"));

        gridLayout_95->addWidget(label_377, 0, 0, 1, 1);

        text_file_color_texture = new FileSelectWidget(groupCheck_use_color_texture);
        text_file_color_texture->setObjectName(QString::fromUtf8("text_file_color_texture"));
        sizePolicy2.setHeightForWidth(text_file_color_texture->sizePolicy().hasHeightForWidth());
        text_file_color_texture->setSizePolicy(sizePolicy2);

        gridLayout_95->addWidget(text_file_color_texture, 0, 1, 1, 2);

        spinbox_color_texture_intensity = new MyDoubleSpinBox(groupCheck_use_color_texture);
        spinbox_color_texture_intensity->setObjectName(QString::fromUtf8("spinbox_color_texture_intensity"));
        sizePolicy.setHeightForWidth(spinbox_color_texture_intensity->sizePolicy().hasHeightForWidth());
        spinbox_color_texture_intensity->setSizePolicy(sizePolicy);
        spinbox_color_texture_intensity->setDecimals(2);
        spinbox_color_texture_intensity->setMaximum(1000.000000000000000);
        spinbox_color_texture_intensity->setSingleStep(0.100000000000000);

        gridLayout_95->addWidget(spinbox_color_texture_intensity, 1, 2, 1, 1);

        gridLayout_95->setColumnStretch(2, 1);

        verticalLayout_141->addLayout(gridLayout_95);


        verticalLayout_6->addWidget(groupCheck_use_color_texture);

        groupCheck_perlin_noise_color_enable = new MyGroupBox(groupBox);
        groupCheck_perlin_noise_color_enable->setObjectName(QString::fromUtf8("groupCheck_perlin_noise_color_enable"));
        groupCheck_perlin_noise_color_enable->setCheckable(true);
        groupCheck_perlin_noise_color_enable->setChecked(true);
        gridLayout_29 = new QGridLayout(groupCheck_perlin_noise_color_enable);
        gridLayout_29->setSpacing(2);
        gridLayout_29->setObjectName(QString::fromUtf8("gridLayout_29"));
        gridLayout_29->setContentsMargins(2, 2, 2, 2);
        spinbox_perlin_noise_color_intensity = new MyDoubleSpinBox(groupCheck_perlin_noise_color_enable);
        spinbox_perlin_noise_color_intensity->setObjectName(QString::fromUtf8("spinbox_perlin_noise_color_intensity"));
        sizePolicy.setHeightForWidth(spinbox_perlin_noise_color_intensity->sizePolicy().hasHeightForWidth());
        spinbox_perlin_noise_color_intensity->setSizePolicy(sizePolicy);
        spinbox_perlin_noise_color_intensity->setDecimals(2);
        spinbox_perlin_noise_color_intensity->setMinimum(0.000000000000000);
        spinbox_perlin_noise_color_intensity->setMaximum(1000.000000000000000);
        spinbox_perlin_noise_color_intensity->setSingleStep(0.100000000000000);

        gridLayout_29->addWidget(spinbox_perlin_noise_color_intensity, 0, 1, 1, 1);

        label_41 = new QLabel(groupCheck_perlin_noise_color_enable);
        label_41->setObjectName(QString::fromUtf8("label_41"));

        gridLayout_29->addWidget(label_41, 0, 0, 1, 1);

        checkBox_perlin_noise_color_invert = new MyCheckBox(groupCheck_perlin_noise_color_enable);
        checkBox_perlin_noise_color_invert->setObjectName(QString::fromUtf8("checkBox_perlin_noise_color_invert"));

        gridLayout_29->addWidget(checkBox_perlin_noise_color_invert, 1, 0, 1, 2);

        gridLayout_29->setColumnStretch(1, 1);

        verticalLayout_6->addWidget(groupCheck_perlin_noise_color_enable);


        verticalLayout_2->addWidget(groupBox);

        groupBox_6 = new QGroupBox(scrollAreaWidgetContents_3);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        verticalLayout_8 = new QVBoxLayout(groupBox_6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(2, 2, 2, 2);
        label_2 = new QLabel(groupBox_6);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_8->addWidget(label_2);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label_55 = new QLabel(groupBox_6);
        label_55->setObjectName(QString::fromUtf8("label_55"));

        gridLayout_7->addWidget(label_55, 0, 0, 1, 1);

        spinbox_shading = new MyDoubleSpinBox(groupBox_6);
        spinbox_shading->setObjectName(QString::fromUtf8("spinbox_shading"));
        sizePolicy.setHeightForWidth(spinbox_shading->sizePolicy().hasHeightForWidth());
        spinbox_shading->setSizePolicy(sizePolicy);
        spinbox_shading->setDecimals(2);
        spinbox_shading->setMaximum(1000.000000000000000);
        spinbox_shading->setSingleStep(0.100000000000000);

        gridLayout_7->addWidget(spinbox_shading, 0, 1, 1, 1);

        gridLayout_7->setColumnStretch(1, 1);

        verticalLayout_8->addLayout(gridLayout_7);


        verticalLayout_2->addWidget(groupBox_6);

        groupBox_7 = new QGroupBox(scrollAreaWidgetContents_3);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        verticalLayout_9 = new QVBoxLayout(groupBox_7);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(2, 2, 2, 2);
        gridLayout_25 = new QGridLayout();
        gridLayout_25->setObjectName(QString::fromUtf8("gridLayout_25"));
        label_72 = new QLabel(groupBox_7);
        label_72->setObjectName(QString::fromUtf8("label_72"));

        gridLayout_25->addWidget(label_72, 0, 0, 1, 1);

        colorButton_specular_color = new MyColorButton(groupBox_7);
        colorButton_specular_color->setObjectName(QString::fromUtf8("colorButton_specular_color"));
        sizePolicy2.setHeightForWidth(colorButton_specular_color->sizePolicy().hasHeightForWidth());
        colorButton_specular_color->setSizePolicy(sizePolicy2);

        gridLayout_25->addWidget(colorButton_specular_color, 0, 1, 1, 1);


        verticalLayout_9->addLayout(gridLayout_25);

        groupCheck_specular_plastic_enable = new MyGroupBox(groupBox_7);
        groupCheck_specular_plastic_enable->setObjectName(QString::fromUtf8("groupCheck_specular_plastic_enable"));
        groupCheck_specular_plastic_enable->setCheckable(true);
        verticalLayout_146 = new QVBoxLayout(groupCheck_specular_plastic_enable);
        verticalLayout_146->setSpacing(2);
        verticalLayout_146->setObjectName(QString::fromUtf8("verticalLayout_146"));
        verticalLayout_146->setContentsMargins(2, 2, 2, 2);
        gridLayout_9 = new QGridLayout();
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        gridLayout_9->setVerticalSpacing(2);
        spinbox_specular_width = new MyDoubleSpinBox(groupCheck_specular_plastic_enable);
        spinbox_specular_width->setObjectName(QString::fromUtf8("spinbox_specular_width"));
        sizePolicy.setHeightForWidth(spinbox_specular_width->sizePolicy().hasHeightForWidth());
        spinbox_specular_width->setSizePolicy(sizePolicy);
        spinbox_specular_width->setDecimals(3);
        spinbox_specular_width->setMinimum(0.001000000000000);
        spinbox_specular_width->setMaximum(30.000000000000000);
        spinbox_specular_width->setSingleStep(0.010000000000000);

        gridLayout_9->addWidget(spinbox_specular_width, 1, 1, 1, 1);

        spinbox_specular = new MyDoubleSpinBox(groupCheck_specular_plastic_enable);
        spinbox_specular->setObjectName(QString::fromUtf8("spinbox_specular"));
        sizePolicy.setHeightForWidth(spinbox_specular->sizePolicy().hasHeightForWidth());
        spinbox_specular->setSizePolicy(sizePolicy);
        spinbox_specular->setDecimals(2);
        spinbox_specular->setMaximum(1000.000000000000000);
        spinbox_specular->setSingleStep(0.100000000000000);

        gridLayout_9->addWidget(spinbox_specular, 0, 1, 1, 1);

        label_69 = new QLabel(groupCheck_specular_plastic_enable);
        label_69->setObjectName(QString::fromUtf8("label_69"));
        label_69->setWordWrap(true);

        gridLayout_9->addWidget(label_69, 0, 0, 1, 1);

        label_71 = new QLabel(groupCheck_specular_plastic_enable);
        label_71->setObjectName(QString::fromUtf8("label_71"));
        label_71->setWordWrap(true);

        gridLayout_9->addWidget(label_71, 1, 0, 1, 1);


        verticalLayout_146->addLayout(gridLayout_9);


        verticalLayout_9->addWidget(groupCheck_specular_plastic_enable);

        groupCheck_metallic = new MyGroupBox(groupBox_7);
        groupCheck_metallic->setObjectName(QString::fromUtf8("groupCheck_metallic"));
        groupCheck_metallic->setCheckable(true);
        verticalLayout_147 = new QVBoxLayout(groupCheck_metallic);
        verticalLayout_147->setSpacing(2);
        verticalLayout_147->setObjectName(QString::fromUtf8("verticalLayout_147"));
        verticalLayout_147->setContentsMargins(2, 2, 2, 2);
        gridLayout_26 = new QGridLayout();
        gridLayout_26->setObjectName(QString::fromUtf8("gridLayout_26"));
        gridLayout_26->setVerticalSpacing(2);
        label_85 = new QLabel(groupCheck_metallic);
        label_85->setObjectName(QString::fromUtf8("label_85"));
        label_85->setWordWrap(true);

        gridLayout_26->addWidget(label_85, 0, 0, 1, 1);

        label_86 = new QLabel(groupCheck_metallic);
        label_86->setObjectName(QString::fromUtf8("label_86"));
        label_86->setWordWrap(true);

        gridLayout_26->addWidget(label_86, 1, 0, 1, 1);

        spinbox_specular_metallic = new MyDoubleSpinBox(groupCheck_metallic);
        spinbox_specular_metallic->setObjectName(QString::fromUtf8("spinbox_specular_metallic"));
        sizePolicy.setHeightForWidth(spinbox_specular_metallic->sizePolicy().hasHeightForWidth());
        spinbox_specular_metallic->setSizePolicy(sizePolicy);
        spinbox_specular_metallic->setDecimals(2);
        spinbox_specular_metallic->setMaximum(1000.000000000000000);
        spinbox_specular_metallic->setSingleStep(0.100000000000000);

        gridLayout_26->addWidget(spinbox_specular_metallic, 0, 1, 1, 1);

        spinbox_specular_metallic_width = new MyDoubleSpinBox(groupCheck_metallic);
        spinbox_specular_metallic_width->setObjectName(QString::fromUtf8("spinbox_specular_metallic_width"));
        sizePolicy.setHeightForWidth(spinbox_specular_metallic_width->sizePolicy().hasHeightForWidth());
        spinbox_specular_metallic_width->setSizePolicy(sizePolicy);
        spinbox_specular_metallic_width->setDecimals(3);
        spinbox_specular_metallic_width->setMinimum(0.001000000000000);
        spinbox_specular_metallic_width->setMaximum(30.000000000000000);
        spinbox_specular_metallic_width->setSingleStep(0.010000000000000);

        gridLayout_26->addWidget(spinbox_specular_metallic_width, 1, 1, 1, 1);

        label_87 = new QLabel(groupCheck_metallic);
        label_87->setObjectName(QString::fromUtf8("label_87"));
        label_87->setWordWrap(true);

        gridLayout_26->addWidget(label_87, 2, 0, 1, 1);

        spinbox_specular_metallic_roughness = new MyDoubleSpinBox(groupCheck_metallic);
        spinbox_specular_metallic_roughness->setObjectName(QString::fromUtf8("spinbox_specular_metallic_roughness"));
        sizePolicy.setHeightForWidth(spinbox_specular_metallic_roughness->sizePolicy().hasHeightForWidth());
        spinbox_specular_metallic_roughness->setSizePolicy(sizePolicy);
        spinbox_specular_metallic_roughness->setDecimals(2);
        spinbox_specular_metallic_roughness->setMinimum(0.000000000000000);
        spinbox_specular_metallic_roughness->setMaximum(100.000000000000000);
        spinbox_specular_metallic_roughness->setSingleStep(0.010000000000000);

        gridLayout_26->addWidget(spinbox_specular_metallic_roughness, 2, 1, 1, 1);


        verticalLayout_147->addLayout(gridLayout_26);


        verticalLayout_9->addWidget(groupCheck_metallic);


        verticalLayout_2->addWidget(groupBox_7);

        groupCheck_rough_surface = new MyGroupBox(scrollAreaWidgetContents_3);
        groupCheck_rough_surface->setObjectName(QString::fromUtf8("groupCheck_rough_surface"));
        groupCheck_rough_surface->setCheckable(true);
        verticalLayout_148 = new QVBoxLayout(groupCheck_rough_surface);
        verticalLayout_148->setSpacing(2);
        verticalLayout_148->setObjectName(QString::fromUtf8("verticalLayout_148"));
        verticalLayout_148->setContentsMargins(2, 2, 2, 2);
        gridLayout_27 = new QGridLayout();
        gridLayout_27->setObjectName(QString::fromUtf8("gridLayout_27"));
        gridLayout_27->setVerticalSpacing(2);
        label_93 = new QLabel(groupCheck_rough_surface);
        label_93->setObjectName(QString::fromUtf8("label_93"));
        label_93->setWordWrap(true);

        gridLayout_27->addWidget(label_93, 0, 0, 1, 1);

        spinbox_surface_roughness = new MyDoubleSpinBox(groupCheck_rough_surface);
        spinbox_surface_roughness->setObjectName(QString::fromUtf8("spinbox_surface_roughness"));
        sizePolicy.setHeightForWidth(spinbox_surface_roughness->sizePolicy().hasHeightForWidth());
        spinbox_surface_roughness->setSizePolicy(sizePolicy);
        spinbox_surface_roughness->setDecimals(4);
        spinbox_surface_roughness->setMaximum(1.000000000000000);
        spinbox_surface_roughness->setSingleStep(0.001000000000000);

        gridLayout_27->addWidget(spinbox_surface_roughness, 0, 1, 1, 1);


        verticalLayout_148->addLayout(gridLayout_27);

        groupCheck_use_roughness_texture = new MyGroupBox(groupCheck_rough_surface);
        groupCheck_use_roughness_texture->setObjectName(QString::fromUtf8("groupCheck_use_roughness_texture"));
        groupCheck_use_roughness_texture->setCheckable(true);
        verticalLayout_149 = new QVBoxLayout(groupCheck_use_roughness_texture);
        verticalLayout_149->setSpacing(2);
        verticalLayout_149->setObjectName(QString::fromUtf8("verticalLayout_149"));
        verticalLayout_149->setContentsMargins(2, 2, 2, 2);
        gridLayout_101 = new QGridLayout();
        gridLayout_101->setSpacing(2);
        gridLayout_101->setObjectName(QString::fromUtf8("gridLayout_101"));
        label_395 = new QLabel(groupCheck_use_roughness_texture);
        label_395->setObjectName(QString::fromUtf8("label_395"));

        gridLayout_101->addWidget(label_395, 1, 0, 1, 1);

        label_396 = new QLabel(groupCheck_use_roughness_texture);
        label_396->setObjectName(QString::fromUtf8("label_396"));

        gridLayout_101->addWidget(label_396, 0, 0, 1, 1);

        text_file_roughness_texture = new FileSelectWidget(groupCheck_use_roughness_texture);
        text_file_roughness_texture->setObjectName(QString::fromUtf8("text_file_roughness_texture"));
        sizePolicy2.setHeightForWidth(text_file_roughness_texture->sizePolicy().hasHeightForWidth());
        text_file_roughness_texture->setSizePolicy(sizePolicy2);

        gridLayout_101->addWidget(text_file_roughness_texture, 0, 1, 1, 2);

        spinbox_roughness_texture_intensity = new MyDoubleSpinBox(groupCheck_use_roughness_texture);
        spinbox_roughness_texture_intensity->setObjectName(QString::fromUtf8("spinbox_roughness_texture_intensity"));
        sizePolicy.setHeightForWidth(spinbox_roughness_texture_intensity->sizePolicy().hasHeightForWidth());
        spinbox_roughness_texture_intensity->setSizePolicy(sizePolicy);
        spinbox_roughness_texture_intensity->setDecimals(2);
        spinbox_roughness_texture_intensity->setMaximum(1000.000000000000000);
        spinbox_roughness_texture_intensity->setSingleStep(0.100000000000000);

        gridLayout_101->addWidget(spinbox_roughness_texture_intensity, 1, 2, 1, 1);

        gridLayout_101->setColumnStretch(2, 1);

        verticalLayout_149->addLayout(gridLayout_101);


        verticalLayout_148->addWidget(groupCheck_use_roughness_texture);


        verticalLayout_2->addWidget(groupCheck_rough_surface);

        groupCheck_iridescence_enabled = new MyGroupBox(scrollAreaWidgetContents_3);
        groupCheck_iridescence_enabled->setObjectName(QString::fromUtf8("groupCheck_iridescence_enabled"));
        groupCheck_iridescence_enabled->setCheckable(true);
        verticalLayout_3 = new QVBoxLayout(groupCheck_iridescence_enabled);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(2, 2, 2, 2);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setVerticalSpacing(2);
        label_75 = new QLabel(groupCheck_iridescence_enabled);
        label_75->setObjectName(QString::fromUtf8("label_75"));

        gridLayout_2->addWidget(label_75, 0, 0, 1, 1);

        spinbox_iridescence_intensity = new MyDoubleSpinBox(groupCheck_iridescence_enabled);
        spinbox_iridescence_intensity->setObjectName(QString::fromUtf8("spinbox_iridescence_intensity"));
        sizePolicy.setHeightForWidth(spinbox_iridescence_intensity->sizePolicy().hasHeightForWidth());
        spinbox_iridescence_intensity->setSizePolicy(sizePolicy);
        spinbox_iridescence_intensity->setDecimals(2);
        spinbox_iridescence_intensity->setMinimum(0.000000000000000);
        spinbox_iridescence_intensity->setMaximum(99999999.000000000000000);
        spinbox_iridescence_intensity->setSingleStep(1.000000000000000);

        gridLayout_2->addWidget(spinbox_iridescence_intensity, 0, 1, 1, 1);

        label_82 = new QLabel(groupCheck_iridescence_enabled);
        label_82->setObjectName(QString::fromUtf8("label_82"));
        label_82->setWordWrap(true);

        gridLayout_2->addWidget(label_82, 1, 0, 1, 1);

        spinbox_iridescence_subsurface_thickness = new MyDoubleSpinBox(groupCheck_iridescence_enabled);
        spinbox_iridescence_subsurface_thickness->setObjectName(QString::fromUtf8("spinbox_iridescence_subsurface_thickness"));
        sizePolicy.setHeightForWidth(spinbox_iridescence_subsurface_thickness->sizePolicy().hasHeightForWidth());
        spinbox_iridescence_subsurface_thickness->setSizePolicy(sizePolicy);
        spinbox_iridescence_subsurface_thickness->setDecimals(5);
        spinbox_iridescence_subsurface_thickness->setMinimum(0.000000000000000);
        spinbox_iridescence_subsurface_thickness->setMaximum(99999999.000000000000000);
        spinbox_iridescence_subsurface_thickness->setSingleStep(1.000000000000000);

        gridLayout_2->addWidget(spinbox_iridescence_subsurface_thickness, 1, 1, 1, 1);

        gridLayout_2->setColumnStretch(1, 1);

        verticalLayout_3->addLayout(gridLayout_2);


        verticalLayout_2->addWidget(groupCheck_iridescence_enabled);

        groupBox_8 = new QGroupBox(scrollAreaWidgetContents_3);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        verticalLayout_10 = new QVBoxLayout(groupBox_8);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(2, 2, 2, 2);
        gridLayout_10 = new QGridLayout();
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        label_73 = new QLabel(groupBox_8);
        label_73->setObjectName(QString::fromUtf8("label_73"));

        gridLayout_10->addWidget(label_73, 0, 0, 1, 1);

        spinbox_luminosity = new MyDoubleSpinBox(groupBox_8);
        spinbox_luminosity->setObjectName(QString::fromUtf8("spinbox_luminosity"));
        sizePolicy.setHeightForWidth(spinbox_luminosity->sizePolicy().hasHeightForWidth());
        spinbox_luminosity->setSizePolicy(sizePolicy);
        spinbox_luminosity->setDecimals(2);
        spinbox_luminosity->setMaximum(1000.000000000000000);
        spinbox_luminosity->setSingleStep(0.100000000000000);

        gridLayout_10->addWidget(spinbox_luminosity, 0, 1, 1, 1);

        label_74 = new QLabel(groupBox_8);
        label_74->setObjectName(QString::fromUtf8("label_74"));

        gridLayout_10->addWidget(label_74, 2, 0, 1, 1);

        colorButton_luminosity_color = new MyColorButton(groupBox_8);
        colorButton_luminosity_color->setObjectName(QString::fromUtf8("colorButton_luminosity_color"));
        sizePolicy2.setHeightForWidth(colorButton_luminosity_color->sizePolicy().hasHeightForWidth());
        colorButton_luminosity_color->setSizePolicy(sizePolicy2);

        gridLayout_10->addWidget(colorButton_luminosity_color, 2, 1, 1, 1);

        label_94 = new QLabel(groupBox_8);
        label_94->setObjectName(QString::fromUtf8("label_94"));

        gridLayout_10->addWidget(label_94, 1, 0, 1, 1);

        spinbox_luminosity_emissive = new MyDoubleSpinBox(groupBox_8);
        spinbox_luminosity_emissive->setObjectName(QString::fromUtf8("spinbox_luminosity_emissive"));
        sizePolicy.setHeightForWidth(spinbox_luminosity_emissive->sizePolicy().hasHeightForWidth());
        spinbox_luminosity_emissive->setSizePolicy(sizePolicy);
        spinbox_luminosity_emissive->setDecimals(2);
        spinbox_luminosity_emissive->setMaximum(1000.000000000000000);
        spinbox_luminosity_emissive->setSingleStep(0.100000000000000);

        gridLayout_10->addWidget(spinbox_luminosity_emissive, 1, 1, 1, 1);


        verticalLayout_10->addLayout(gridLayout_10);

        groupCheck_use_luminosity_texture = new MyGroupBox(groupBox_8);
        groupCheck_use_luminosity_texture->setObjectName(QString::fromUtf8("groupCheck_use_luminosity_texture"));
        groupCheck_use_luminosity_texture->setCheckable(true);
        verticalLayout_142 = new QVBoxLayout(groupCheck_use_luminosity_texture);
        verticalLayout_142->setSpacing(2);
        verticalLayout_142->setObjectName(QString::fromUtf8("verticalLayout_142"));
        verticalLayout_142->setContentsMargins(2, 2, 2, 2);
        gridLayout_96 = new QGridLayout();
        gridLayout_96->setSpacing(2);
        gridLayout_96->setObjectName(QString::fromUtf8("gridLayout_96"));
        label_379 = new QLabel(groupCheck_use_luminosity_texture);
        label_379->setObjectName(QString::fromUtf8("label_379"));

        gridLayout_96->addWidget(label_379, 1, 0, 1, 1);

        label_380 = new QLabel(groupCheck_use_luminosity_texture);
        label_380->setObjectName(QString::fromUtf8("label_380"));

        gridLayout_96->addWidget(label_380, 0, 0, 1, 1);

        text_file_luminosity_texture = new FileSelectWidget(groupCheck_use_luminosity_texture);
        text_file_luminosity_texture->setObjectName(QString::fromUtf8("text_file_luminosity_texture"));
        sizePolicy2.setHeightForWidth(text_file_luminosity_texture->sizePolicy().hasHeightForWidth());
        text_file_luminosity_texture->setSizePolicy(sizePolicy2);

        gridLayout_96->addWidget(text_file_luminosity_texture, 0, 1, 1, 2);

        spinbox_luminosity_texture_intensity = new MyDoubleSpinBox(groupCheck_use_luminosity_texture);
        spinbox_luminosity_texture_intensity->setObjectName(QString::fromUtf8("spinbox_luminosity_texture_intensity"));
        sizePolicy.setHeightForWidth(spinbox_luminosity_texture_intensity->sizePolicy().hasHeightForWidth());
        spinbox_luminosity_texture_intensity->setSizePolicy(sizePolicy);
        spinbox_luminosity_texture_intensity->setDecimals(2);
        spinbox_luminosity_texture_intensity->setMaximum(1000.000000000000000);
        spinbox_luminosity_texture_intensity->setSingleStep(0.100000000000000);

        gridLayout_96->addWidget(spinbox_luminosity_texture_intensity, 1, 2, 1, 1);

        gridLayout_96->setColumnStretch(2, 1);

        verticalLayout_142->addLayout(gridLayout_96);


        verticalLayout_10->addWidget(groupCheck_use_luminosity_texture);

        groupCheck_perlin_noise_luminosity_enable = new MyGroupBox(groupBox_8);
        groupCheck_perlin_noise_luminosity_enable->setObjectName(QString::fromUtf8("groupCheck_perlin_noise_luminosity_enable"));
        groupCheck_perlin_noise_luminosity_enable->setCheckable(true);
        groupCheck_perlin_noise_luminosity_enable->setChecked(true);
        gridLayout_30 = new QGridLayout(groupCheck_perlin_noise_luminosity_enable);
        gridLayout_30->setSpacing(2);
        gridLayout_30->setObjectName(QString::fromUtf8("gridLayout_30"));
        gridLayout_30->setContentsMargins(2, 2, 2, 2);
        spinbox_perlin_noise_luminosity_intensity = new MyDoubleSpinBox(groupCheck_perlin_noise_luminosity_enable);
        spinbox_perlin_noise_luminosity_intensity->setObjectName(QString::fromUtf8("spinbox_perlin_noise_luminosity_intensity"));
        sizePolicy.setHeightForWidth(spinbox_perlin_noise_luminosity_intensity->sizePolicy().hasHeightForWidth());
        spinbox_perlin_noise_luminosity_intensity->setSizePolicy(sizePolicy);
        spinbox_perlin_noise_luminosity_intensity->setDecimals(2);
        spinbox_perlin_noise_luminosity_intensity->setMinimum(0.000000000000000);
        spinbox_perlin_noise_luminosity_intensity->setMaximum(1000.000000000000000);
        spinbox_perlin_noise_luminosity_intensity->setSingleStep(0.100000000000000);

        gridLayout_30->addWidget(spinbox_perlin_noise_luminosity_intensity, 0, 1, 1, 1);

        label_49 = new QLabel(groupCheck_perlin_noise_luminosity_enable);
        label_49->setObjectName(QString::fromUtf8("label_49"));

        gridLayout_30->addWidget(label_49, 0, 0, 1, 1);

        checkBox_perlin_noise_luminosity_invert = new MyCheckBox(groupCheck_perlin_noise_luminosity_enable);
        checkBox_perlin_noise_luminosity_invert->setObjectName(QString::fromUtf8("checkBox_perlin_noise_luminosity_invert"));

        gridLayout_30->addWidget(checkBox_perlin_noise_luminosity_invert, 1, 0, 1, 2);

        gridLayout_30->setColumnStretch(1, 1);

        verticalLayout_10->addWidget(groupCheck_perlin_noise_luminosity_enable);


        verticalLayout_2->addWidget(groupBox_8);

        groupBox_9 = new QGroupBox(scrollAreaWidgetContents_3);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        verticalLayout_11 = new QVBoxLayout(groupBox_9);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(2, 2, 2, 2);
        checkBox_fresnel_reflectance = new MyCheckBox(groupBox_9);
        checkBox_fresnel_reflectance->setObjectName(QString::fromUtf8("checkBox_fresnel_reflectance"));
        sizePolicy.setHeightForWidth(checkBox_fresnel_reflectance->sizePolicy().hasHeightForWidth());
        checkBox_fresnel_reflectance->setSizePolicy(sizePolicy);

        verticalLayout_11->addWidget(checkBox_fresnel_reflectance);

        gridLayout_12 = new QGridLayout();
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        label_352 = new QLabel(groupBox_9);
        label_352->setObjectName(QString::fromUtf8("label_352"));

        gridLayout_12->addWidget(label_352, 0, 0, 1, 1);

        spinbox_transparency_index_of_refraction = new MyDoubleSpinBox(groupBox_9);
        spinbox_transparency_index_of_refraction->setObjectName(QString::fromUtf8("spinbox_transparency_index_of_refraction"));
        sizePolicy.setHeightForWidth(spinbox_transparency_index_of_refraction->sizePolicy().hasHeightForWidth());
        spinbox_transparency_index_of_refraction->setSizePolicy(sizePolicy);
        spinbox_transparency_index_of_refraction->setDecimals(2);
        spinbox_transparency_index_of_refraction->setMaximum(10.000000000000000);
        spinbox_transparency_index_of_refraction->setSingleStep(0.100000000000000);

        gridLayout_12->addWidget(spinbox_transparency_index_of_refraction, 0, 1, 1, 1);

        gridLayout_12->setColumnStretch(1, 1);

        verticalLayout_11->addLayout(gridLayout_12);

        groupBox_10 = new QGroupBox(groupBox_9);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        verticalLayout_12 = new QVBoxLayout(groupBox_10);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(2, 2, 2, 2);
        gridLayout_13 = new QGridLayout();
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        colorButton_reflections_color = new MyColorButton(groupBox_10);
        colorButton_reflections_color->setObjectName(QString::fromUtf8("colorButton_reflections_color"));
        sizePolicy2.setHeightForWidth(colorButton_reflections_color->sizePolicy().hasHeightForWidth());
        colorButton_reflections_color->setSizePolicy(sizePolicy2);

        gridLayout_13->addWidget(colorButton_reflections_color, 1, 1, 1, 1);

        label_70 = new QLabel(groupBox_10);
        label_70->setObjectName(QString::fromUtf8("label_70"));

        gridLayout_13->addWidget(label_70, 0, 0, 1, 1);

        spinbox_reflectance = new MyDoubleSpinBox(groupBox_10);
        spinbox_reflectance->setObjectName(QString::fromUtf8("spinbox_reflectance"));
        sizePolicy.setHeightForWidth(spinbox_reflectance->sizePolicy().hasHeightForWidth());
        spinbox_reflectance->setSizePolicy(sizePolicy);
        spinbox_reflectance->setDecimals(2);
        spinbox_reflectance->setMaximum(1000.000000000000000);
        spinbox_reflectance->setSingleStep(0.100000000000000);

        gridLayout_13->addWidget(spinbox_reflectance, 0, 1, 1, 1);

        label_91 = new QLabel(groupBox_10);
        label_91->setObjectName(QString::fromUtf8("label_91"));

        gridLayout_13->addWidget(label_91, 1, 0, 1, 1);


        verticalLayout_12->addLayout(gridLayout_13);

        groupCheck_use_reflectance_texture = new MyGroupBox(groupBox_10);
        groupCheck_use_reflectance_texture->setObjectName(QString::fromUtf8("groupCheck_use_reflectance_texture"));
        groupCheck_use_reflectance_texture->setCheckable(true);
        verticalLayout_150 = new QVBoxLayout(groupCheck_use_reflectance_texture);
        verticalLayout_150->setSpacing(2);
        verticalLayout_150->setObjectName(QString::fromUtf8("verticalLayout_150"));
        verticalLayout_150->setContentsMargins(2, 2, 2, 2);
        gridLayout_102 = new QGridLayout();
        gridLayout_102->setSpacing(2);
        gridLayout_102->setObjectName(QString::fromUtf8("gridLayout_102"));
        label_397 = new QLabel(groupCheck_use_reflectance_texture);
        label_397->setObjectName(QString::fromUtf8("label_397"));

        gridLayout_102->addWidget(label_397, 1, 0, 1, 1);

        label_398 = new QLabel(groupCheck_use_reflectance_texture);
        label_398->setObjectName(QString::fromUtf8("label_398"));

        gridLayout_102->addWidget(label_398, 0, 0, 1, 1);

        text_file_reflectance_texture = new FileSelectWidget(groupCheck_use_reflectance_texture);
        text_file_reflectance_texture->setObjectName(QString::fromUtf8("text_file_reflectance_texture"));
        sizePolicy2.setHeightForWidth(text_file_reflectance_texture->sizePolicy().hasHeightForWidth());
        text_file_reflectance_texture->setSizePolicy(sizePolicy2);

        gridLayout_102->addWidget(text_file_reflectance_texture, 0, 1, 1, 2);

        spinbox_reflectance_texture_intensity = new MyDoubleSpinBox(groupCheck_use_reflectance_texture);
        spinbox_reflectance_texture_intensity->setObjectName(QString::fromUtf8("spinbox_reflectance_texture_intensity"));
        sizePolicy.setHeightForWidth(spinbox_reflectance_texture_intensity->sizePolicy().hasHeightForWidth());
        spinbox_reflectance_texture_intensity->setSizePolicy(sizePolicy);
        spinbox_reflectance_texture_intensity->setDecimals(2);
        spinbox_reflectance_texture_intensity->setMaximum(1000.000000000000000);
        spinbox_reflectance_texture_intensity->setSingleStep(0.100000000000000);

        gridLayout_102->addWidget(spinbox_reflectance_texture_intensity, 1, 2, 1, 1);

        gridLayout_102->setColumnStretch(2, 1);

        verticalLayout_150->addLayout(gridLayout_102);


        verticalLayout_12->addWidget(groupCheck_use_reflectance_texture);

        groupCheck_perlin_noise_reflectance_enable = new MyGroupBox(groupBox_10);
        groupCheck_perlin_noise_reflectance_enable->setObjectName(QString::fromUtf8("groupCheck_perlin_noise_reflectance_enable"));
        groupCheck_perlin_noise_reflectance_enable->setCheckable(true);
        groupCheck_perlin_noise_reflectance_enable->setChecked(true);
        gridLayout_33 = new QGridLayout(groupCheck_perlin_noise_reflectance_enable);
        gridLayout_33->setSpacing(2);
        gridLayout_33->setObjectName(QString::fromUtf8("gridLayout_33"));
        gridLayout_33->setContentsMargins(2, 2, 2, 2);
        spinbox_perlin_noise_reflectance_intensity = new MyDoubleSpinBox(groupCheck_perlin_noise_reflectance_enable);
        spinbox_perlin_noise_reflectance_intensity->setObjectName(QString::fromUtf8("spinbox_perlin_noise_reflectance_intensity"));
        sizePolicy.setHeightForWidth(spinbox_perlin_noise_reflectance_intensity->sizePolicy().hasHeightForWidth());
        spinbox_perlin_noise_reflectance_intensity->setSizePolicy(sizePolicy);
        spinbox_perlin_noise_reflectance_intensity->setDecimals(2);
        spinbox_perlin_noise_reflectance_intensity->setMinimum(0.000000000000000);
        spinbox_perlin_noise_reflectance_intensity->setMaximum(1000.000000000000000);
        spinbox_perlin_noise_reflectance_intensity->setSingleStep(0.100000000000000);

        gridLayout_33->addWidget(spinbox_perlin_noise_reflectance_intensity, 0, 1, 1, 1);

        label_54 = new QLabel(groupCheck_perlin_noise_reflectance_enable);
        label_54->setObjectName(QString::fromUtf8("label_54"));

        gridLayout_33->addWidget(label_54, 0, 0, 1, 1);

        checkBox_perlin_noise_reflectance_invert = new MyCheckBox(groupCheck_perlin_noise_reflectance_enable);
        checkBox_perlin_noise_reflectance_invert->setObjectName(QString::fromUtf8("checkBox_perlin_noise_reflectance_invert"));

        gridLayout_33->addWidget(checkBox_perlin_noise_reflectance_invert, 1, 0, 1, 2);

        gridLayout_33->setColumnStretch(1, 1);

        verticalLayout_12->addWidget(groupCheck_perlin_noise_reflectance_enable);


        verticalLayout_11->addWidget(groupBox_10);

        groupBox_11 = new QGroupBox(groupBox_9);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        verticalLayout_13 = new QVBoxLayout(groupBox_11);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(2, 2, 2, 2);
        gridLayout_14 = new QGridLayout();
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        gridLayout_14->setVerticalSpacing(2);
        label_295 = new QLabel(groupBox_11);
        label_295->setObjectName(QString::fromUtf8("label_295"));

        gridLayout_14->addWidget(label_295, 0, 0, 1, 1);

        checkBox_inside_coloring = new MyCheckBox(groupBox_11);
        checkBox_inside_coloring->setObjectName(QString::fromUtf8("checkBox_inside_coloring"));
        sizePolicy.setHeightForWidth(checkBox_inside_coloring->sizePolicy().hasHeightForWidth());
        checkBox_inside_coloring->setSizePolicy(sizePolicy);

        gridLayout_14->addWidget(checkBox_inside_coloring, 4, 0, 1, 2);

        colorButton_transparency_interior_color = new MyColorButton(groupBox_11);
        colorButton_transparency_interior_color->setObjectName(QString::fromUtf8("colorButton_transparency_interior_color"));

        gridLayout_14->addWidget(colorButton_transparency_interior_color, 3, 1, 1, 1);

        logedit_transparency_of_interior = new MyLineEdit(groupBox_11);
        logedit_transparency_of_interior->setObjectName(QString::fromUtf8("logedit_transparency_of_interior"));

        gridLayout_14->addWidget(logedit_transparency_of_interior, 2, 1, 1, 1);

        label_92 = new QLabel(groupBox_11);
        label_92->setObjectName(QString::fromUtf8("label_92"));

        gridLayout_14->addWidget(label_92, 1, 0, 1, 1);

        spinbox_transparency_of_surface = new MyDoubleSpinBox(groupBox_11);
        spinbox_transparency_of_surface->setObjectName(QString::fromUtf8("spinbox_transparency_of_surface"));
        sizePolicy.setHeightForWidth(spinbox_transparency_of_surface->sizePolicy().hasHeightForWidth());
        spinbox_transparency_of_surface->setSizePolicy(sizePolicy);
        spinbox_transparency_of_surface->setDecimals(2);
        spinbox_transparency_of_surface->setMaximum(1.000000000000000);
        spinbox_transparency_of_surface->setSingleStep(0.100000000000000);

        gridLayout_14->addWidget(spinbox_transparency_of_surface, 0, 1, 1, 1);

        colorButton_transparency_color = new MyColorButton(groupBox_11);
        colorButton_transparency_color->setObjectName(QString::fromUtf8("colorButton_transparency_color"));
        sizePolicy2.setHeightForWidth(colorButton_transparency_color->sizePolicy().hasHeightForWidth());
        colorButton_transparency_color->setSizePolicy(sizePolicy2);

        gridLayout_14->addWidget(colorButton_transparency_color, 1, 1, 1, 1);

        label_351 = new QLabel(groupBox_11);
        label_351->setObjectName(QString::fromUtf8("label_351"));

        gridLayout_14->addWidget(label_351, 2, 0, 1, 1);

        label_353 = new QLabel(groupBox_11);
        label_353->setObjectName(QString::fromUtf8("label_353"));

        gridLayout_14->addWidget(label_353, 3, 0, 1, 1);

        checkBox_subsurface_scattering = new MyCheckBox(groupBox_11);
        checkBox_subsurface_scattering->setObjectName(QString::fromUtf8("checkBox_subsurface_scattering"));
        sizePolicy.setHeightForWidth(checkBox_subsurface_scattering->sizePolicy().hasHeightForWidth());
        checkBox_subsurface_scattering->setSizePolicy(sizePolicy);

        gridLayout_14->addWidget(checkBox_subsurface_scattering, 5, 0, 1, 1);


        verticalLayout_13->addLayout(gridLayout_14);

        groupCheck_use_transparency_texture = new MyGroupBox(groupBox_11);
        groupCheck_use_transparency_texture->setObjectName(QString::fromUtf8("groupCheck_use_transparency_texture"));
        groupCheck_use_transparency_texture->setCheckable(true);
        verticalLayout_151 = new QVBoxLayout(groupCheck_use_transparency_texture);
        verticalLayout_151->setSpacing(2);
        verticalLayout_151->setObjectName(QString::fromUtf8("verticalLayout_151"));
        verticalLayout_151->setContentsMargins(2, 2, 2, 2);
        gridLayout_103 = new QGridLayout();
        gridLayout_103->setSpacing(2);
        gridLayout_103->setObjectName(QString::fromUtf8("gridLayout_103"));
        spinbox_transparency_texture_intensity = new MyDoubleSpinBox(groupCheck_use_transparency_texture);
        spinbox_transparency_texture_intensity->setObjectName(QString::fromUtf8("spinbox_transparency_texture_intensity"));
        sizePolicy.setHeightForWidth(spinbox_transparency_texture_intensity->sizePolicy().hasHeightForWidth());
        spinbox_transparency_texture_intensity->setSizePolicy(sizePolicy);
        spinbox_transparency_texture_intensity->setDecimals(2);
        spinbox_transparency_texture_intensity->setMaximum(1000.000000000000000);
        spinbox_transparency_texture_intensity->setSingleStep(0.100000000000000);

        gridLayout_103->addWidget(spinbox_transparency_texture_intensity, 1, 2, 1, 1);

        label_399 = new QLabel(groupCheck_use_transparency_texture);
        label_399->setObjectName(QString::fromUtf8("label_399"));

        gridLayout_103->addWidget(label_399, 1, 0, 1, 1);

        label_400 = new QLabel(groupCheck_use_transparency_texture);
        label_400->setObjectName(QString::fromUtf8("label_400"));

        gridLayout_103->addWidget(label_400, 0, 0, 1, 1);

        text_file_transparency_texture = new FileSelectWidget(groupCheck_use_transparency_texture);
        text_file_transparency_texture->setObjectName(QString::fromUtf8("text_file_transparency_texture"));
        sizePolicy2.setHeightForWidth(text_file_transparency_texture->sizePolicy().hasHeightForWidth());
        text_file_transparency_texture->setSizePolicy(sizePolicy2);

        gridLayout_103->addWidget(text_file_transparency_texture, 0, 1, 1, 2);

        spinbox_transparency_texture_intensity_vol = new MyDoubleSpinBox(groupCheck_use_transparency_texture);
        spinbox_transparency_texture_intensity_vol->setObjectName(QString::fromUtf8("spinbox_transparency_texture_intensity_vol"));
        sizePolicy.setHeightForWidth(spinbox_transparency_texture_intensity_vol->sizePolicy().hasHeightForWidth());
        spinbox_transparency_texture_intensity_vol->setSizePolicy(sizePolicy);
        spinbox_transparency_texture_intensity_vol->setDecimals(2);
        spinbox_transparency_texture_intensity_vol->setMaximum(1000.000000000000000);
        spinbox_transparency_texture_intensity_vol->setSingleStep(0.100000000000000);

        gridLayout_103->addWidget(spinbox_transparency_texture_intensity_vol, 2, 2, 1, 1);

        label_401 = new QLabel(groupCheck_use_transparency_texture);
        label_401->setObjectName(QString::fromUtf8("label_401"));

        gridLayout_103->addWidget(label_401, 2, 0, 1, 1);

        gridLayout_103->setColumnStretch(2, 1);

        verticalLayout_151->addLayout(gridLayout_103);


        verticalLayout_13->addWidget(groupCheck_use_transparency_texture);

        groupCheck_use_transparency_alpha_texture = new MyGroupBox(groupBox_11);
        groupCheck_use_transparency_alpha_texture->setObjectName(QString::fromUtf8("groupCheck_use_transparency_alpha_texture"));
        groupCheck_use_transparency_alpha_texture->setCheckable(true);
        verticalLayout_153 = new QVBoxLayout(groupCheck_use_transparency_alpha_texture);
        verticalLayout_153->setSpacing(2);
        verticalLayout_153->setObjectName(QString::fromUtf8("verticalLayout_153"));
        verticalLayout_153->setContentsMargins(2, 2, 2, 2);
        gridLayout_105 = new QGridLayout();
        gridLayout_105->setSpacing(2);
        gridLayout_105->setObjectName(QString::fromUtf8("gridLayout_105"));
        text_file_transparency_alpha_texture = new FileSelectWidget(groupCheck_use_transparency_alpha_texture);
        text_file_transparency_alpha_texture->setObjectName(QString::fromUtf8("text_file_transparency_alpha_texture"));
        sizePolicy2.setHeightForWidth(text_file_transparency_alpha_texture->sizePolicy().hasHeightForWidth());
        text_file_transparency_alpha_texture->setSizePolicy(sizePolicy2);

        gridLayout_105->addWidget(text_file_transparency_alpha_texture, 0, 1, 1, 2);

        label_404 = new QLabel(groupCheck_use_transparency_alpha_texture);
        label_404->setObjectName(QString::fromUtf8("label_404"));

        gridLayout_105->addWidget(label_404, 0, 0, 1, 1);

        label_403 = new QLabel(groupCheck_use_transparency_alpha_texture);
        label_403->setObjectName(QString::fromUtf8("label_403"));

        gridLayout_105->addWidget(label_403, 1, 0, 1, 1);

        spinbox_transparency_alpha_texture_intensity = new MyDoubleSpinBox(groupCheck_use_transparency_alpha_texture);
        spinbox_transparency_alpha_texture_intensity->setObjectName(QString::fromUtf8("spinbox_transparency_alpha_texture_intensity"));
        sizePolicy.setHeightForWidth(spinbox_transparency_alpha_texture_intensity->sizePolicy().hasHeightForWidth());
        spinbox_transparency_alpha_texture_intensity->setSizePolicy(sizePolicy);
        spinbox_transparency_alpha_texture_intensity->setDecimals(2);
        spinbox_transparency_alpha_texture_intensity->setMaximum(1000.000000000000000);
        spinbox_transparency_alpha_texture_intensity->setSingleStep(0.100000000000000);

        gridLayout_105->addWidget(spinbox_transparency_alpha_texture_intensity, 1, 2, 1, 1);

        label_405 = new QLabel(groupCheck_use_transparency_alpha_texture);
        label_405->setObjectName(QString::fromUtf8("label_405"));

        gridLayout_105->addWidget(label_405, 2, 0, 1, 1);

        spinbox_transparency_alpha_texture_intensity_vol = new MyDoubleSpinBox(groupCheck_use_transparency_alpha_texture);
        spinbox_transparency_alpha_texture_intensity_vol->setObjectName(QString::fromUtf8("spinbox_transparency_alpha_texture_intensity_vol"));
        sizePolicy.setHeightForWidth(spinbox_transparency_alpha_texture_intensity_vol->sizePolicy().hasHeightForWidth());
        spinbox_transparency_alpha_texture_intensity_vol->setSizePolicy(sizePolicy);
        spinbox_transparency_alpha_texture_intensity_vol->setDecimals(2);
        spinbox_transparency_alpha_texture_intensity_vol->setMaximum(1000.000000000000000);
        spinbox_transparency_alpha_texture_intensity_vol->setSingleStep(0.100000000000000);

        gridLayout_105->addWidget(spinbox_transparency_alpha_texture_intensity_vol, 2, 2, 1, 1);

        gridLayout_105->setColumnStretch(2, 1);

        verticalLayout_153->addLayout(gridLayout_105);


        verticalLayout_13->addWidget(groupCheck_use_transparency_alpha_texture);

        groupCheck_perlin_noise_transparency_color_enable = new MyGroupBox(groupBox_11);
        groupCheck_perlin_noise_transparency_color_enable->setObjectName(QString::fromUtf8("groupCheck_perlin_noise_transparency_color_enable"));
        groupCheck_perlin_noise_transparency_color_enable->setCheckable(true);
        groupCheck_perlin_noise_transparency_color_enable->setChecked(true);
        gridLayout_35 = new QGridLayout(groupCheck_perlin_noise_transparency_color_enable);
        gridLayout_35->setSpacing(2);
        gridLayout_35->setObjectName(QString::fromUtf8("gridLayout_35"));
        gridLayout_35->setContentsMargins(2, 2, 2, 2);
        spinbox_perlin_noise_transparency_color_intensity = new MyDoubleSpinBox(groupCheck_perlin_noise_transparency_color_enable);
        spinbox_perlin_noise_transparency_color_intensity->setObjectName(QString::fromUtf8("spinbox_perlin_noise_transparency_color_intensity"));
        sizePolicy.setHeightForWidth(spinbox_perlin_noise_transparency_color_intensity->sizePolicy().hasHeightForWidth());
        spinbox_perlin_noise_transparency_color_intensity->setSizePolicy(sizePolicy);
        spinbox_perlin_noise_transparency_color_intensity->setDecimals(2);
        spinbox_perlin_noise_transparency_color_intensity->setMinimum(0.000000000000000);
        spinbox_perlin_noise_transparency_color_intensity->setMaximum(1000.000000000000000);
        spinbox_perlin_noise_transparency_color_intensity->setSingleStep(0.100000000000000);

        gridLayout_35->addWidget(spinbox_perlin_noise_transparency_color_intensity, 0, 1, 1, 1);

        checkBox_perlin_noise_transparency_color_invert = new MyCheckBox(groupCheck_perlin_noise_transparency_color_enable);
        checkBox_perlin_noise_transparency_color_invert->setObjectName(QString::fromUtf8("checkBox_perlin_noise_transparency_color_invert"));

        gridLayout_35->addWidget(checkBox_perlin_noise_transparency_color_invert, 2, 0, 1, 2);

        label_60 = new QLabel(groupCheck_perlin_noise_transparency_color_enable);
        label_60->setObjectName(QString::fromUtf8("label_60"));

        gridLayout_35->addWidget(label_60, 0, 0, 1, 1);

        label_65 = new QLabel(groupCheck_perlin_noise_transparency_color_enable);
        label_65->setObjectName(QString::fromUtf8("label_65"));

        gridLayout_35->addWidget(label_65, 1, 0, 1, 1);

        spinbox_perlin_noise_transparency_color_intensity_vol = new MyDoubleSpinBox(groupCheck_perlin_noise_transparency_color_enable);
        spinbox_perlin_noise_transparency_color_intensity_vol->setObjectName(QString::fromUtf8("spinbox_perlin_noise_transparency_color_intensity_vol"));
        sizePolicy.setHeightForWidth(spinbox_perlin_noise_transparency_color_intensity_vol->sizePolicy().hasHeightForWidth());
        spinbox_perlin_noise_transparency_color_intensity_vol->setSizePolicy(sizePolicy);
        spinbox_perlin_noise_transparency_color_intensity_vol->setDecimals(2);
        spinbox_perlin_noise_transparency_color_intensity_vol->setMinimum(0.000000000000000);
        spinbox_perlin_noise_transparency_color_intensity_vol->setMaximum(1000.000000000000000);
        spinbox_perlin_noise_transparency_color_intensity_vol->setSingleStep(0.100000000000000);

        gridLayout_35->addWidget(spinbox_perlin_noise_transparency_color_intensity_vol, 1, 1, 1, 1);

        gridLayout_35->setColumnStretch(1, 1);

        verticalLayout_13->addWidget(groupCheck_perlin_noise_transparency_color_enable);

        groupCheck_perlin_noise_transparency_alpha_enable = new MyGroupBox(groupBox_11);
        groupCheck_perlin_noise_transparency_alpha_enable->setObjectName(QString::fromUtf8("groupCheck_perlin_noise_transparency_alpha_enable"));
        groupCheck_perlin_noise_transparency_alpha_enable->setCheckable(true);
        groupCheck_perlin_noise_transparency_alpha_enable->setChecked(true);
        gridLayout_36 = new QGridLayout(groupCheck_perlin_noise_transparency_alpha_enable);
        gridLayout_36->setSpacing(2);
        gridLayout_36->setObjectName(QString::fromUtf8("gridLayout_36"));
        gridLayout_36->setContentsMargins(2, 2, 2, 2);
        label_61 = new QLabel(groupCheck_perlin_noise_transparency_alpha_enable);
        label_61->setObjectName(QString::fromUtf8("label_61"));

        gridLayout_36->addWidget(label_61, 0, 0, 1, 1);

        checkBox_perlin_noise_transparency_alpha_invert = new MyCheckBox(groupCheck_perlin_noise_transparency_alpha_enable);
        checkBox_perlin_noise_transparency_alpha_invert->setObjectName(QString::fromUtf8("checkBox_perlin_noise_transparency_alpha_invert"));

        gridLayout_36->addWidget(checkBox_perlin_noise_transparency_alpha_invert, 2, 0, 1, 2);

        spinbox_perlin_noise_transparency_alpha_intensity = new MyDoubleSpinBox(groupCheck_perlin_noise_transparency_alpha_enable);
        spinbox_perlin_noise_transparency_alpha_intensity->setObjectName(QString::fromUtf8("spinbox_perlin_noise_transparency_alpha_intensity"));
        sizePolicy.setHeightForWidth(spinbox_perlin_noise_transparency_alpha_intensity->sizePolicy().hasHeightForWidth());
        spinbox_perlin_noise_transparency_alpha_intensity->setSizePolicy(sizePolicy);
        spinbox_perlin_noise_transparency_alpha_intensity->setDecimals(2);
        spinbox_perlin_noise_transparency_alpha_intensity->setMinimum(0.000000000000000);
        spinbox_perlin_noise_transparency_alpha_intensity->setMaximum(1000.000000000000000);
        spinbox_perlin_noise_transparency_alpha_intensity->setSingleStep(0.100000000000000);

        gridLayout_36->addWidget(spinbox_perlin_noise_transparency_alpha_intensity, 0, 1, 1, 1);

        label_66 = new QLabel(groupCheck_perlin_noise_transparency_alpha_enable);
        label_66->setObjectName(QString::fromUtf8("label_66"));

        gridLayout_36->addWidget(label_66, 1, 0, 1, 1);

        spinbox_perlin_noise_transparency_alpha_intensity_vol = new MyDoubleSpinBox(groupCheck_perlin_noise_transparency_alpha_enable);
        spinbox_perlin_noise_transparency_alpha_intensity_vol->setObjectName(QString::fromUtf8("spinbox_perlin_noise_transparency_alpha_intensity_vol"));
        sizePolicy.setHeightForWidth(spinbox_perlin_noise_transparency_alpha_intensity_vol->sizePolicy().hasHeightForWidth());
        spinbox_perlin_noise_transparency_alpha_intensity_vol->setSizePolicy(sizePolicy);
        spinbox_perlin_noise_transparency_alpha_intensity_vol->setDecimals(2);
        spinbox_perlin_noise_transparency_alpha_intensity_vol->setMinimum(0.000000000000000);
        spinbox_perlin_noise_transparency_alpha_intensity_vol->setMaximum(1000.000000000000000);
        spinbox_perlin_noise_transparency_alpha_intensity_vol->setSingleStep(0.100000000000000);

        gridLayout_36->addWidget(spinbox_perlin_noise_transparency_alpha_intensity_vol, 1, 1, 1, 1);

        gridLayout_36->setColumnStretch(1, 1);

        verticalLayout_13->addWidget(groupCheck_perlin_noise_transparency_alpha_enable);

        label_5 = new QLabel(groupBox_11);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setWordWrap(true);

        verticalLayout_13->addWidget(label_5);


        verticalLayout_11->addWidget(groupBox_11);


        verticalLayout_2->addWidget(groupBox_9);

        groupCheck_use_diffusion_texture = new MyGroupBox(scrollAreaWidgetContents_3);
        groupCheck_use_diffusion_texture->setObjectName(QString::fromUtf8("groupCheck_use_diffusion_texture"));
        groupCheck_use_diffusion_texture->setCheckable(true);
        verticalLayout_144 = new QVBoxLayout(groupCheck_use_diffusion_texture);
        verticalLayout_144->setSpacing(2);
        verticalLayout_144->setObjectName(QString::fromUtf8("verticalLayout_144"));
        verticalLayout_144->setContentsMargins(2, 2, 2, 2);
        gridLayout_98 = new QGridLayout();
        gridLayout_98->setSpacing(2);
        gridLayout_98->setObjectName(QString::fromUtf8("gridLayout_98"));
        label_383 = new QLabel(groupCheck_use_diffusion_texture);
        label_383->setObjectName(QString::fromUtf8("label_383"));

        gridLayout_98->addWidget(label_383, 1, 0, 1, 1);

        label_384 = new QLabel(groupCheck_use_diffusion_texture);
        label_384->setObjectName(QString::fromUtf8("label_384"));

        gridLayout_98->addWidget(label_384, 0, 0, 1, 1);

        text_file_diffusion_texture = new FileSelectWidget(groupCheck_use_diffusion_texture);
        text_file_diffusion_texture->setObjectName(QString::fromUtf8("text_file_diffusion_texture"));
        sizePolicy2.setHeightForWidth(text_file_diffusion_texture->sizePolicy().hasHeightForWidth());
        text_file_diffusion_texture->setSizePolicy(sizePolicy2);

        gridLayout_98->addWidget(text_file_diffusion_texture, 0, 1, 1, 2);

        spinbox_diffusion_texture_intensity = new MyDoubleSpinBox(groupCheck_use_diffusion_texture);
        spinbox_diffusion_texture_intensity->setObjectName(QString::fromUtf8("spinbox_diffusion_texture_intensity"));
        sizePolicy.setHeightForWidth(spinbox_diffusion_texture_intensity->sizePolicy().hasHeightForWidth());
        spinbox_diffusion_texture_intensity->setSizePolicy(sizePolicy);
        spinbox_diffusion_texture_intensity->setDecimals(2);
        spinbox_diffusion_texture_intensity->setMaximum(1.000000000000000);
        spinbox_diffusion_texture_intensity->setSingleStep(0.100000000000000);

        gridLayout_98->addWidget(spinbox_diffusion_texture_intensity, 1, 2, 1, 1);

        gridLayout_98->setColumnStretch(2, 1);

        verticalLayout_144->addLayout(gridLayout_98);


        verticalLayout_2->addWidget(groupCheck_use_diffusion_texture);

        groupCheck_use_normal_map_texture = new MyGroupBox(scrollAreaWidgetContents_3);
        groupCheck_use_normal_map_texture->setObjectName(QString::fromUtf8("groupCheck_use_normal_map_texture"));
        groupCheck_use_normal_map_texture->setCheckable(true);
        verticalLayout_145 = new QVBoxLayout(groupCheck_use_normal_map_texture);
        verticalLayout_145->setSpacing(2);
        verticalLayout_145->setObjectName(QString::fromUtf8("verticalLayout_145"));
        verticalLayout_145->setContentsMargins(2, 2, 2, 2);
        gridLayout_100 = new QGridLayout();
        gridLayout_100->setSpacing(2);
        gridLayout_100->setObjectName(QString::fromUtf8("gridLayout_100"));
        label_394 = new QLabel(groupCheck_use_normal_map_texture);
        label_394->setObjectName(QString::fromUtf8("label_394"));

        gridLayout_100->addWidget(label_394, 0, 0, 1, 1);

        label_393 = new QLabel(groupCheck_use_normal_map_texture);
        label_393->setObjectName(QString::fromUtf8("label_393"));

        gridLayout_100->addWidget(label_393, 3, 0, 1, 1);

        logedit_normal_map_texture_height = new MyLineEdit(groupCheck_use_normal_map_texture);
        logedit_normal_map_texture_height->setObjectName(QString::fromUtf8("logedit_normal_map_texture_height"));

        gridLayout_100->addWidget(logedit_normal_map_texture_height, 3, 2, 1, 1);

        text_file_normal_map_texture = new FileSelectWidget(groupCheck_use_normal_map_texture);
        text_file_normal_map_texture->setObjectName(QString::fromUtf8("text_file_normal_map_texture"));
        sizePolicy2.setHeightForWidth(text_file_normal_map_texture->sizePolicy().hasHeightForWidth());
        text_file_normal_map_texture->setSizePolicy(sizePolicy2);

        gridLayout_100->addWidget(text_file_normal_map_texture, 0, 1, 1, 2);

        checkBox_normal_map_texture_from_bumpmap = new MyCheckBox(groupCheck_use_normal_map_texture);
        checkBox_normal_map_texture_from_bumpmap->setObjectName(QString::fromUtf8("checkBox_normal_map_texture_from_bumpmap"));

        gridLayout_100->addWidget(checkBox_normal_map_texture_from_bumpmap, 1, 0, 1, 3);

        checkBox_normal_map_texture_invert_green = new MyCheckBox(groupCheck_use_normal_map_texture);
        checkBox_normal_map_texture_invert_green->setObjectName(QString::fromUtf8("checkBox_normal_map_texture_invert_green"));

        gridLayout_100->addWidget(checkBox_normal_map_texture_invert_green, 2, 0, 1, 3);


        verticalLayout_145->addLayout(gridLayout_100);


        verticalLayout_2->addWidget(groupCheck_use_normal_map_texture);

        groupCheck_use_displacement_texture = new MyGroupBox(scrollAreaWidgetContents_3);
        groupCheck_use_displacement_texture->setObjectName(QString::fromUtf8("groupCheck_use_displacement_texture"));
        groupCheck_use_displacement_texture->setCheckable(true);
        verticalLayout_143 = new QVBoxLayout(groupCheck_use_displacement_texture);
        verticalLayout_143->setSpacing(2);
        verticalLayout_143->setObjectName(QString::fromUtf8("verticalLayout_143"));
        verticalLayout_143->setContentsMargins(2, 2, 2, 2);
        gridLayout_97 = new QGridLayout();
        gridLayout_97->setSpacing(2);
        gridLayout_97->setObjectName(QString::fromUtf8("gridLayout_97"));
        label_381 = new QLabel(groupCheck_use_displacement_texture);
        label_381->setObjectName(QString::fromUtf8("label_381"));

        gridLayout_97->addWidget(label_381, 1, 0, 1, 1);

        label_382 = new QLabel(groupCheck_use_displacement_texture);
        label_382->setObjectName(QString::fromUtf8("label_382"));

        gridLayout_97->addWidget(label_382, 0, 0, 1, 1);

        text_file_displacement_texture = new FileSelectWidget(groupCheck_use_displacement_texture);
        text_file_displacement_texture->setObjectName(QString::fromUtf8("text_file_displacement_texture"));
        sizePolicy2.setHeightForWidth(text_file_displacement_texture->sizePolicy().hasHeightForWidth());
        text_file_displacement_texture->setSizePolicy(sizePolicy2);

        gridLayout_97->addWidget(text_file_displacement_texture, 0, 1, 1, 2);

        logedit_displacement_texture_height = new MyLineEdit(groupCheck_use_displacement_texture);
        logedit_displacement_texture_height->setObjectName(QString::fromUtf8("logedit_displacement_texture_height"));

        gridLayout_97->addWidget(logedit_displacement_texture_height, 1, 2, 1, 1);

        gridLayout_97->setColumnStretch(2, 1);

        verticalLayout_143->addLayout(gridLayout_97);


        verticalLayout_2->addWidget(groupCheck_use_displacement_texture);

        groupCheck_perlin_noise_displacement_enable = new MyGroupBox(scrollAreaWidgetContents_3);
        groupCheck_perlin_noise_displacement_enable->setObjectName(QString::fromUtf8("groupCheck_perlin_noise_displacement_enable"));
        groupCheck_perlin_noise_displacement_enable->setCheckable(true);
        groupCheck_perlin_noise_displacement_enable->setChecked(true);
        gridLayout_31 = new QGridLayout(groupCheck_perlin_noise_displacement_enable);
        gridLayout_31->setSpacing(2);
        gridLayout_31->setObjectName(QString::fromUtf8("gridLayout_31"));
        gridLayout_31->setContentsMargins(2, 2, 2, 2);
        label_50 = new QLabel(groupCheck_perlin_noise_displacement_enable);
        label_50->setObjectName(QString::fromUtf8("label_50"));

        gridLayout_31->addWidget(label_50, 0, 0, 1, 1);

        checkBox_perlin_noise_displacement_invert = new MyCheckBox(groupCheck_perlin_noise_displacement_enable);
        checkBox_perlin_noise_displacement_invert->setObjectName(QString::fromUtf8("checkBox_perlin_noise_displacement_invert"));

        gridLayout_31->addWidget(checkBox_perlin_noise_displacement_invert, 1, 0, 1, 3);

        logedit_perlin_noise_displacement_intensity = new MyLineEdit(groupCheck_perlin_noise_displacement_enable);
        logedit_perlin_noise_displacement_intensity->setObjectName(QString::fromUtf8("logedit_perlin_noise_displacement_intensity"));

        gridLayout_31->addWidget(logedit_perlin_noise_displacement_intensity, 0, 1, 1, 1);

        gridLayout_31->setColumnStretch(1, 1);

        verticalLayout_2->addWidget(groupCheck_perlin_noise_displacement_enable);

        groupBox_texture_options = new QGroupBox(scrollAreaWidgetContents_3);
        groupBox_texture_options->setObjectName(QString::fromUtf8("groupBox_texture_options"));
        verticalLayout_31 = new QVBoxLayout(groupBox_texture_options);
        verticalLayout_31->setSpacing(2);
        verticalLayout_31->setObjectName(QString::fromUtf8("verticalLayout_31"));
        verticalLayout_31->setContentsMargins(2, 2, 2, 2);
        groupCheck_texture_fractalize = new MyGroupBox(groupBox_texture_options);
        groupCheck_texture_fractalize->setObjectName(QString::fromUtf8("groupCheck_texture_fractalize"));
        groupCheck_texture_fractalize->setCheckable(true);
        verticalLayout_5 = new QVBoxLayout(groupCheck_texture_fractalize);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(2, 2, 2, -1);
        label = new QLabel(groupCheck_texture_fractalize);
        label->setObjectName(QString::fromUtf8("label"));
        label->setWordWrap(true);

        verticalLayout_5->addWidget(label);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_4 = new QLabel(groupCheck_texture_fractalize);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setWordWrap(true);

        gridLayout_3->addWidget(label_4, 1, 0, 1, 1);

        label_3 = new QLabel(groupCheck_texture_fractalize);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 0, 0, 1, 1);

        logedit_texture_fractalize_cube_size = new MyLineEdit(groupCheck_texture_fractalize);
        logedit_texture_fractalize_cube_size->setObjectName(QString::fromUtf8("logedit_texture_fractalize_cube_size"));

        gridLayout_3->addWidget(logedit_texture_fractalize_cube_size, 0, 1, 1, 1);

        spinboxInt_texture_fractalize_start_iteration = new MySpinBox(groupCheck_texture_fractalize);
        spinboxInt_texture_fractalize_start_iteration->setObjectName(QString::fromUtf8("spinboxInt_texture_fractalize_start_iteration"));
        sizePolicy.setHeightForWidth(spinboxInt_texture_fractalize_start_iteration->sizePolicy().hasHeightForWidth());
        spinboxInt_texture_fractalize_start_iteration->setSizePolicy(sizePolicy);
        spinboxInt_texture_fractalize_start_iteration->setMaximum(999);

        gridLayout_3->addWidget(spinboxInt_texture_fractalize_start_iteration, 1, 1, 1, 1);

        label_fractalize_shape = new QLabel(groupCheck_texture_fractalize);
        label_fractalize_shape->setObjectName(QString::fromUtf8("label_fractalize_shape"));

        gridLayout_3->addWidget(label_fractalize_shape, 2, 0, 1, 1);

        comboBox_texture_fractalize_shape = new MyComboBox(groupCheck_texture_fractalize);
        comboBox_texture_fractalize_shape->addItem(QString());
        comboBox_texture_fractalize_shape->addItem(QString());
        comboBox_texture_fractalize_shape->addItem(QString());
        comboBox_texture_fractalize_shape->addItem(QString());
        comboBox_texture_fractalize_shape->addItem(QString());
        comboBox_texture_fractalize_shape->addItem(QString());
        comboBox_texture_fractalize_shape->addItem(QString());
        comboBox_texture_fractalize_shape->addItem(QString());
        comboBox_texture_fractalize_shape->setObjectName(QString::fromUtf8("comboBox_texture_fractalize_shape"));

        gridLayout_3->addWidget(comboBox_texture_fractalize_shape, 2, 1, 1, 1);


        verticalLayout_5->addLayout(gridLayout_3);


        verticalLayout_31->addWidget(groupCheck_texture_fractalize);

        gridLayout_99 = new QGridLayout();
        gridLayout_99->setSpacing(2);
        gridLayout_99->setObjectName(QString::fromUtf8("gridLayout_99"));
        label_374 = new QLabel(groupBox_texture_options);
        label_374->setObjectName(QString::fromUtf8("label_374"));
        sizePolicy1.setHeightForWidth(label_374->sizePolicy().hasHeightForWidth());
        label_374->setSizePolicy(sizePolicy1);
        label_374->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_99->addWidget(label_374, 3, 1, 1, 1);

        label_386 = new QLabel(groupBox_texture_options);
        label_386->setObjectName(QString::fromUtf8("label_386"));

        gridLayout_99->addWidget(label_386, 0, 0, 1, 1);

        label_376 = new QLabel(groupBox_texture_options);
        label_376->setObjectName(QString::fromUtf8("label_376"));
        sizePolicy1.setHeightForWidth(label_376->sizePolicy().hasHeightForWidth());
        label_376->setSizePolicy(sizePolicy1);
        label_376->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_99->addWidget(label_376, 5, 1, 1, 1);

        label_375 = new QLabel(groupBox_texture_options);
        label_375->setObjectName(QString::fromUtf8("label_375"));
        sizePolicy1.setHeightForWidth(label_375->sizePolicy().hasHeightForWidth());
        label_375->setSizePolicy(sizePolicy1);
        label_375->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_99->addWidget(label_375, 4, 1, 1, 1);

        label_372 = new QLabel(groupBox_texture_options);
        label_372->setObjectName(QString::fromUtf8("label_372"));
        sizePolicy1.setHeightForWidth(label_372->sizePolicy().hasHeightForWidth());
        label_372->setSizePolicy(sizePolicy1);
        label_372->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_99->addWidget(label_372, 1, 1, 1, 1);

        label_388 = new QLabel(groupBox_texture_options);
        label_388->setObjectName(QString::fromUtf8("label_388"));

        gridLayout_99->addWidget(label_388, 4, 0, 3, 1);

        label_390 = new QLabel(groupBox_texture_options);
        label_390->setObjectName(QString::fromUtf8("label_390"));
        sizePolicy1.setHeightForWidth(label_390->sizePolicy().hasHeightForWidth());
        label_390->setSizePolicy(sizePolicy1);
        label_390->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_99->addWidget(label_390, 7, 1, 1, 1);

        comboBox_texture_mapping_type = new MyComboBox(groupBox_texture_options);
        comboBox_texture_mapping_type->addItem(QString());
        comboBox_texture_mapping_type->addItem(QString());
        comboBox_texture_mapping_type->addItem(QString());
        comboBox_texture_mapping_type->addItem(QString());
        comboBox_texture_mapping_type->addItem(QString());
        comboBox_texture_mapping_type->addItem(QString());
        comboBox_texture_mapping_type->addItem(QString());
        comboBox_texture_mapping_type->addItem(QString());
        comboBox_texture_mapping_type->addItem(QString());
        comboBox_texture_mapping_type->addItem(QString());
        comboBox_texture_mapping_type->addItem(QString());
        comboBox_texture_mapping_type->setObjectName(QString::fromUtf8("comboBox_texture_mapping_type"));
        sizePolicy1.setHeightForWidth(comboBox_texture_mapping_type->sizePolicy().hasHeightForWidth());
        comboBox_texture_mapping_type->setSizePolicy(sizePolicy1);

        gridLayout_99->addWidget(comboBox_texture_mapping_type, 0, 1, 1, 3);

        label_373 = new QLabel(groupBox_texture_options);
        label_373->setObjectName(QString::fromUtf8("label_373"));
        sizePolicy1.setHeightForWidth(label_373->sizePolicy().hasHeightForWidth());
        label_373->setSizePolicy(sizePolicy1);
        label_373->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_99->addWidget(label_373, 2, 1, 1, 1);

        label_387 = new QLabel(groupBox_texture_options);
        label_387->setObjectName(QString::fromUtf8("label_387"));
        sizePolicy1.setHeightForWidth(label_387->sizePolicy().hasHeightForWidth());
        label_387->setSizePolicy(sizePolicy1);
        label_387->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_99->addWidget(label_387, 6, 1, 1, 1);

        label_389 = new QLabel(groupBox_texture_options);
        label_389->setObjectName(QString::fromUtf8("label_389"));

        gridLayout_99->addWidget(label_389, 7, 0, 3, 1);

        label_391 = new QLabel(groupBox_texture_options);
        label_391->setObjectName(QString::fromUtf8("label_391"));
        sizePolicy1.setHeightForWidth(label_391->sizePolicy().hasHeightForWidth());
        label_391->setSizePolicy(sizePolicy1);
        label_391->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_99->addWidget(label_391, 8, 1, 1, 1);

        label_392 = new QLabel(groupBox_texture_options);
        label_392->setObjectName(QString::fromUtf8("label_392"));
        sizePolicy1.setHeightForWidth(label_392->sizePolicy().hasHeightForWidth());
        label_392->setSizePolicy(sizePolicy1);
        label_392->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_99->addWidget(label_392, 9, 1, 1, 1);

        spinbox3_texture_center_x = new MyDoubleSpinBox(groupBox_texture_options);
        spinbox3_texture_center_x->setObjectName(QString::fromUtf8("spinbox3_texture_center_x"));
        sizePolicy.setHeightForWidth(spinbox3_texture_center_x->sizePolicy().hasHeightForWidth());
        spinbox3_texture_center_x->setSizePolicy(sizePolicy);
        spinbox3_texture_center_x->setDecimals(5);
        spinbox3_texture_center_x->setMinimum(-100.000000000000000);
        spinbox3_texture_center_x->setMaximum(100.000000000000000);
        spinbox3_texture_center_x->setSingleStep(0.100000000000000);

        gridLayout_99->addWidget(spinbox3_texture_center_x, 1, 2, 1, 2);

        spinbox3_texture_center_y = new MyDoubleSpinBox(groupBox_texture_options);
        spinbox3_texture_center_y->setObjectName(QString::fromUtf8("spinbox3_texture_center_y"));
        sizePolicy.setHeightForWidth(spinbox3_texture_center_y->sizePolicy().hasHeightForWidth());
        spinbox3_texture_center_y->setSizePolicy(sizePolicy);
        spinbox3_texture_center_y->setDecimals(5);
        spinbox3_texture_center_y->setMinimum(-100.000000000000000);
        spinbox3_texture_center_y->setMaximum(100.000000000000000);
        spinbox3_texture_center_y->setSingleStep(0.100000000000000);

        gridLayout_99->addWidget(spinbox3_texture_center_y, 2, 2, 1, 2);

        spinbox3_texture_center_z = new MyDoubleSpinBox(groupBox_texture_options);
        spinbox3_texture_center_z->setObjectName(QString::fromUtf8("spinbox3_texture_center_z"));
        sizePolicy.setHeightForWidth(spinbox3_texture_center_z->sizePolicy().hasHeightForWidth());
        spinbox3_texture_center_z->setSizePolicy(sizePolicy);
        spinbox3_texture_center_z->setDecimals(5);
        spinbox3_texture_center_z->setMinimum(-100.000000000000000);
        spinbox3_texture_center_z->setMaximum(100.000000000000000);
        spinbox3_texture_center_z->setSingleStep(0.100000000000000);

        gridLayout_99->addWidget(spinbox3_texture_center_z, 3, 2, 1, 2);

        logvect3_texture_scale_x = new MyLineEdit(groupBox_texture_options);
        logvect3_texture_scale_x->setObjectName(QString::fromUtf8("logvect3_texture_scale_x"));

        gridLayout_99->addWidget(logvect3_texture_scale_x, 4, 2, 1, 2);

        logvect3_texture_scale_y = new MyLineEdit(groupBox_texture_options);
        logvect3_texture_scale_y->setObjectName(QString::fromUtf8("logvect3_texture_scale_y"));

        gridLayout_99->addWidget(logvect3_texture_scale_y, 5, 2, 1, 2);

        logvect3_texture_scale_z = new MyLineEdit(groupBox_texture_options);
        logvect3_texture_scale_z->setObjectName(QString::fromUtf8("logvect3_texture_scale_z"));

        gridLayout_99->addWidget(logvect3_texture_scale_z, 6, 2, 1, 2);

        spinboxd3_texture_rotation_x = new MyDoubleSpinBox(groupBox_texture_options);
        spinboxd3_texture_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_texture_rotation_x"));
        sizePolicy.setHeightForWidth(spinboxd3_texture_rotation_x->sizePolicy().hasHeightForWidth());
        spinboxd3_texture_rotation_x->setSizePolicy(sizePolicy);
        spinboxd3_texture_rotation_x->setDecimals(4);
        spinboxd3_texture_rotation_x->setMinimum(-180.000000000000000);
        spinboxd3_texture_rotation_x->setMaximum(180.000000000000000);
        spinboxd3_texture_rotation_x->setSingleStep(1.000000000000000);

        gridLayout_99->addWidget(spinboxd3_texture_rotation_x, 7, 2, 1, 2);

        spinboxd3_texture_rotation_y = new MyDoubleSpinBox(groupBox_texture_options);
        spinboxd3_texture_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_texture_rotation_y"));
        sizePolicy.setHeightForWidth(spinboxd3_texture_rotation_y->sizePolicy().hasHeightForWidth());
        spinboxd3_texture_rotation_y->setSizePolicy(sizePolicy);
        spinboxd3_texture_rotation_y->setDecimals(4);
        spinboxd3_texture_rotation_y->setMinimum(-180.000000000000000);
        spinboxd3_texture_rotation_y->setMaximum(180.000000000000000);
        spinboxd3_texture_rotation_y->setSingleStep(1.000000000000000);

        gridLayout_99->addWidget(spinboxd3_texture_rotation_y, 8, 2, 1, 2);

        spinboxd3_texture_rotation_z = new MyDoubleSpinBox(groupBox_texture_options);
        spinboxd3_texture_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_texture_rotation_z"));
        sizePolicy.setHeightForWidth(spinboxd3_texture_rotation_z->sizePolicy().hasHeightForWidth());
        spinboxd3_texture_rotation_z->setSizePolicy(sizePolicy);
        spinboxd3_texture_rotation_z->setDecimals(4);
        spinboxd3_texture_rotation_z->setMinimum(-180.000000000000000);
        spinboxd3_texture_rotation_z->setMaximum(180.000000000000000);
        spinboxd3_texture_rotation_z->setSingleStep(1.000000000000000);

        gridLayout_99->addWidget(spinboxd3_texture_rotation_z, 9, 2, 1, 2);

        label_385 = new QLabel(groupBox_texture_options);
        label_385->setObjectName(QString::fromUtf8("label_385"));

        gridLayout_99->addWidget(label_385, 1, 0, 3, 1);

        gridLayout_99->setColumnStretch(3, 1);

        verticalLayout_31->addLayout(gridLayout_99);


        verticalLayout_2->addWidget(groupBox_texture_options);

        groupCheck_perlin_noise_enable = new MyGroupBox(scrollAreaWidgetContents_3);
        groupCheck_perlin_noise_enable->setObjectName(QString::fromUtf8("groupCheck_perlin_noise_enable"));
        groupCheck_perlin_noise_enable->setCheckable(true);
        verticalLayout_21 = new QVBoxLayout(groupCheck_perlin_noise_enable);
        verticalLayout_21->setSpacing(2);
        verticalLayout_21->setObjectName(QString::fromUtf8("verticalLayout_21"));
        verticalLayout_21->setContentsMargins(2, 2, 2, 2);
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_402 = new QLabel(groupCheck_perlin_noise_enable);
        label_402->setObjectName(QString::fromUtf8("label_402"));

        gridLayout_4->addWidget(label_402, 4, 0, 3, 1);

        vect3_perlin_noise_period_x = new MyLineEdit(groupCheck_perlin_noise_enable);
        vect3_perlin_noise_period_x->setObjectName(QString::fromUtf8("vect3_perlin_noise_period_x"));

        gridLayout_4->addWidget(vect3_perlin_noise_period_x, 1, 2, 1, 1);

        checkBox_perlin_noise_abs = new MyCheckBox(groupCheck_perlin_noise_enable);
        checkBox_perlin_noise_abs->setObjectName(QString::fromUtf8("checkBox_perlin_noise_abs"));
        sizePolicy.setHeightForWidth(checkBox_perlin_noise_abs->sizePolicy().hasHeightForWidth());
        checkBox_perlin_noise_abs->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(checkBox_perlin_noise_abs, 11, 0, 1, 3);

        vect3_perlin_noise_position_offset_y = new MyLineEdit(groupCheck_perlin_noise_enable);
        vect3_perlin_noise_position_offset_y->setObjectName(QString::fromUtf8("vect3_perlin_noise_position_offset_y"));

        gridLayout_4->addWidget(vect3_perlin_noise_position_offset_y, 5, 2, 1, 1);

        label_115 = new QLabel(groupCheck_perlin_noise_enable);
        label_115->setObjectName(QString::fromUtf8("label_115"));

        gridLayout_4->addWidget(label_115, 1, 0, 3, 1);

        label_6 = new QLabel(groupCheck_perlin_noise_enable);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_4->addWidget(label_6, 0, 0, 1, 1);

        spinboxd3_perlin_noise_rotation_x = new MyDoubleSpinBox(groupCheck_perlin_noise_enable);
        spinboxd3_perlin_noise_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_perlin_noise_rotation_x"));
        sizePolicy.setHeightForWidth(spinboxd3_perlin_noise_rotation_x->sizePolicy().hasHeightForWidth());
        spinboxd3_perlin_noise_rotation_x->setSizePolicy(sizePolicy);
        spinboxd3_perlin_noise_rotation_x->setDecimals(4);
        spinboxd3_perlin_noise_rotation_x->setMinimum(-180.000000000000000);
        spinboxd3_perlin_noise_rotation_x->setMaximum(180.000000000000000);
        spinboxd3_perlin_noise_rotation_x->setSingleStep(1.000000000000000);

        gridLayout_4->addWidget(spinboxd3_perlin_noise_rotation_x, 7, 2, 1, 1);

        spinbox_perlin_noise_value_offset = new MyDoubleSpinBox(groupCheck_perlin_noise_enable);
        spinbox_perlin_noise_value_offset->setObjectName(QString::fromUtf8("spinbox_perlin_noise_value_offset"));
        sizePolicy.setHeightForWidth(spinbox_perlin_noise_value_offset->sizePolicy().hasHeightForWidth());
        spinbox_perlin_noise_value_offset->setSizePolicy(sizePolicy);
        spinbox_perlin_noise_value_offset->setDecimals(6);
        spinbox_perlin_noise_value_offset->setMinimum(-1.000000000000000);
        spinbox_perlin_noise_value_offset->setMaximum(1.000000000000000);
        spinbox_perlin_noise_value_offset->setSingleStep(0.100000000000000);

        gridLayout_4->addWidget(spinbox_perlin_noise_value_offset, 10, 2, 1, 1);

        label_137 = new QLabel(groupCheck_perlin_noise_enable);
        label_137->setObjectName(QString::fromUtf8("label_137"));
        label_137->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_137, 3, 1, 1, 1);

        label_408 = new QLabel(groupCheck_perlin_noise_enable);
        label_408->setObjectName(QString::fromUtf8("label_408"));
        sizePolicy1.setHeightForWidth(label_408->sizePolicy().hasHeightForWidth());
        label_408->setSizePolicy(sizePolicy1);
        label_408->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_408, 6, 1, 1, 1);

        label_136 = new QLabel(groupCheck_perlin_noise_enable);
        label_136->setObjectName(QString::fromUtf8("label_136"));
        label_136->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_136, 2, 1, 1, 1);

        vect3_perlin_noise_period_y = new MyLineEdit(groupCheck_perlin_noise_enable);
        vect3_perlin_noise_period_y->setObjectName(QString::fromUtf8("vect3_perlin_noise_period_y"));

        gridLayout_4->addWidget(vect3_perlin_noise_period_y, 2, 2, 1, 1);

        label_7 = new QLabel(groupCheck_perlin_noise_enable);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_4->addWidget(label_7, 10, 0, 1, 1);

        label_406 = new QLabel(groupCheck_perlin_noise_enable);
        label_406->setObjectName(QString::fromUtf8("label_406"));
        sizePolicy1.setHeightForWidth(label_406->sizePolicy().hasHeightForWidth());
        label_406->setSizePolicy(sizePolicy1);
        label_406->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_406, 4, 1, 1, 1);

        spinboxInt_perlin_noise_iterations = new MySpinBox(groupCheck_perlin_noise_enable);
        spinboxInt_perlin_noise_iterations->setObjectName(QString::fromUtf8("spinboxInt_perlin_noise_iterations"));
        sizePolicy.setHeightForWidth(spinboxInt_perlin_noise_iterations->sizePolicy().hasHeightForWidth());
        spinboxInt_perlin_noise_iterations->setSizePolicy(sizePolicy);
        spinboxInt_perlin_noise_iterations->setMinimum(1);
        spinboxInt_perlin_noise_iterations->setMaximum(100);

        gridLayout_4->addWidget(spinboxInt_perlin_noise_iterations, 0, 2, 1, 1);

        label_407 = new QLabel(groupCheck_perlin_noise_enable);
        label_407->setObjectName(QString::fromUtf8("label_407"));
        sizePolicy1.setHeightForWidth(label_407->sizePolicy().hasHeightForWidth());
        label_407->setSizePolicy(sizePolicy1);
        label_407->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_407, 5, 1, 1, 1);

        vect3_perlin_noise_position_offset_z = new MyLineEdit(groupCheck_perlin_noise_enable);
        vect3_perlin_noise_position_offset_z->setObjectName(QString::fromUtf8("vect3_perlin_noise_position_offset_z"));

        gridLayout_4->addWidget(vect3_perlin_noise_position_offset_z, 6, 2, 1, 1);

        spinboxd3_perlin_noise_rotation_y = new MyDoubleSpinBox(groupCheck_perlin_noise_enable);
        spinboxd3_perlin_noise_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_perlin_noise_rotation_y"));
        sizePolicy.setHeightForWidth(spinboxd3_perlin_noise_rotation_y->sizePolicy().hasHeightForWidth());
        spinboxd3_perlin_noise_rotation_y->setSizePolicy(sizePolicy);
        spinboxd3_perlin_noise_rotation_y->setDecimals(4);
        spinboxd3_perlin_noise_rotation_y->setMinimum(-180.000000000000000);
        spinboxd3_perlin_noise_rotation_y->setMaximum(180.000000000000000);
        spinboxd3_perlin_noise_rotation_y->setSingleStep(1.000000000000000);

        gridLayout_4->addWidget(spinboxd3_perlin_noise_rotation_y, 8, 2, 1, 1);

        vect3_perlin_noise_period_z = new MyLineEdit(groupCheck_perlin_noise_enable);
        vect3_perlin_noise_period_z->setObjectName(QString::fromUtf8("vect3_perlin_noise_period_z"));

        gridLayout_4->addWidget(vect3_perlin_noise_period_z, 3, 2, 1, 1);

        label_135 = new QLabel(groupCheck_perlin_noise_enable);
        label_135->setObjectName(QString::fromUtf8("label_135"));
        label_135->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_135, 1, 1, 1, 1);

        vect3_perlin_noise_position_offset_x = new MyLineEdit(groupCheck_perlin_noise_enable);
        vect3_perlin_noise_position_offset_x->setObjectName(QString::fromUtf8("vect3_perlin_noise_position_offset_x"));

        gridLayout_4->addWidget(vect3_perlin_noise_position_offset_x, 4, 2, 1, 1);

        spinboxd3_perlin_noise_rotation_z = new MyDoubleSpinBox(groupCheck_perlin_noise_enable);
        spinboxd3_perlin_noise_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_perlin_noise_rotation_z"));
        sizePolicy.setHeightForWidth(spinboxd3_perlin_noise_rotation_z->sizePolicy().hasHeightForWidth());
        spinboxd3_perlin_noise_rotation_z->setSizePolicy(sizePolicy);
        spinboxd3_perlin_noise_rotation_z->setDecimals(4);
        spinboxd3_perlin_noise_rotation_z->setMinimum(-180.000000000000000);
        spinboxd3_perlin_noise_rotation_z->setMaximum(180.000000000000000);
        spinboxd3_perlin_noise_rotation_z->setSingleStep(1.000000000000000);

        gridLayout_4->addWidget(spinboxd3_perlin_noise_rotation_z, 9, 2, 1, 1);

        label_409 = new QLabel(groupCheck_perlin_noise_enable);
        label_409->setObjectName(QString::fromUtf8("label_409"));

        gridLayout_4->addWidget(label_409, 7, 0, 3, 1);


        verticalLayout_21->addLayout(gridLayout_4);


        verticalLayout_2->addWidget(groupCheck_perlin_noise_enable);

        line_13 = new QFrame(scrollAreaWidgetContents_3);
        line_13->setObjectName(QString::fromUtf8("line_13"));
        line_13->setFrameShape(QFrame::HLine);
        line_13->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_13);

        scrollArea->setWidget(scrollAreaWidgetContents_3);

        verticalLayout_material_editor_panel_root->addWidget(scrollArea);

        QWidget::setTabOrder(scrollArea, spinbox_coloring_palette_offset);
        QWidget::setTabOrder(spinbox_coloring_palette_offset, spinbox_coloring_speed);
        QWidget::setTabOrder(spinbox_coloring_speed, comboBox_fractal_coloring_algorithm);
        QWidget::setTabOrder(comboBox_fractal_coloring_algorithm, spinbox_fractal_coloring_sphere_radius);
        QWidget::setTabOrder(spinbox_fractal_coloring_sphere_radius, vect4_fractal_coloring_line_direction_x);
        QWidget::setTabOrder(vect4_fractal_coloring_line_direction_x, vect4_fractal_coloring_line_direction_y);
        QWidget::setTabOrder(vect4_fractal_coloring_line_direction_y, vect4_fractal_coloring_line_direction_z);
        QWidget::setTabOrder(vect4_fractal_coloring_line_direction_z, spinbox_color_texture_intensity);
        QWidget::setTabOrder(spinbox_color_texture_intensity, spinbox_luminosity_texture_intensity);
        QWidget::setTabOrder(spinbox_luminosity_texture_intensity, spinbox_diffusion_texture_intensity);
        QWidget::setTabOrder(spinbox_diffusion_texture_intensity, checkBox_normal_map_texture_from_bumpmap);
        QWidget::setTabOrder(checkBox_normal_map_texture_from_bumpmap, checkBox_normal_map_texture_invert_green);
        QWidget::setTabOrder(checkBox_normal_map_texture_invert_green, logedit_normal_map_texture_height);
        QWidget::setTabOrder(logedit_normal_map_texture_height, logedit_displacement_texture_height);
        QWidget::setTabOrder(logedit_displacement_texture_height, comboBox_texture_mapping_type);
        QWidget::setTabOrder(comboBox_texture_mapping_type, spinbox3_texture_center_x);
        QWidget::setTabOrder(spinbox3_texture_center_x, spinbox3_texture_center_y);
        QWidget::setTabOrder(spinbox3_texture_center_y, spinbox3_texture_center_z);
        QWidget::setTabOrder(spinbox3_texture_center_z, logvect3_texture_scale_x);
        QWidget::setTabOrder(logvect3_texture_scale_x, logvect3_texture_scale_y);
        QWidget::setTabOrder(logvect3_texture_scale_y, logvect3_texture_scale_z);
        QWidget::setTabOrder(logvect3_texture_scale_z, spinboxd3_texture_rotation_x);
        QWidget::setTabOrder(spinboxd3_texture_rotation_x, spinboxd3_texture_rotation_y);
        QWidget::setTabOrder(spinboxd3_texture_rotation_y, spinboxd3_texture_rotation_z);

        retranslateUi(cMaterialEditorPanel);
        QObject::connect(checkBox_fractal_coloring_iter_add_scale_enabled_true, SIGNAL(toggled(bool)), spinbox_fractal_coloring_iter_add_scale, SLOT(setEnabled(bool)));
        QObject::connect(checkBox_fractal_coloring_iter_scale_enabled_false, SIGNAL(toggled(bool)), spinbox_fractal_coloring_iter_scale, SLOT(setEnabled(bool)));
        QObject::connect(groupCheck_fractal_coloring_extra_color_enabled_false, SIGNAL(toggled(bool)), groupCheck_fractal_coloring_extra_color_options_false, SLOT(setDisabled(bool)));

        QMetaObject::connectSlotsByName(cMaterialEditorPanel);
    } // setupUi

    void retranslateUi(QWidget *cMaterialEditorPanel)
    {
#if QT_CONFIG(tooltip)
        groupCheck_use_colors_from_palette->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Enables coloring of fractal surface using mathematical algorithms and a color palette. </p><p>This option works only for fractal objects, (not for primitive objects.)</p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>palette off</p></td><td><p>palette on</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/image - resolution 1.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - shader - colouring enabled.jpg\"/></p></td></tr></table></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_use_colors_from_palette->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "&Use colors from gradients", nullptr));
        groupCheck_surface_gradient_enable->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Surface color", nullptr));
#if QT_CONFIG(tooltip)
        colorpalette_surface_color_gradient->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Gradient which defines the colors of the fractal surface.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_surface_blend_mode->setText(QCoreApplication::translate("cMaterialEditorPanel", "Blend mode:", nullptr));
        comboBox_surface_gradient_blend_mode->setItemText(0, QCoreApplication::translate("cMaterialEditorPanel", "Normal", nullptr));
        comboBox_surface_gradient_blend_mode->setItemText(1, QCoreApplication::translate("cMaterialEditorPanel", "Multiply", nullptr));
        comboBox_surface_gradient_blend_mode->setItemText(2, QCoreApplication::translate("cMaterialEditorPanel", "Screen", nullptr));
        comboBox_surface_gradient_blend_mode->setItemText(3, QCoreApplication::translate("cMaterialEditorPanel", "Overlay", nullptr));
        comboBox_surface_gradient_blend_mode->setItemText(4, QCoreApplication::translate("cMaterialEditorPanel", "Soft Light", nullptr));
        comboBox_surface_gradient_blend_mode->setItemText(5, QCoreApplication::translate("cMaterialEditorPanel", "Hard Light", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_surface_gradient_blend_mode->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Blend mode for surface gradient with base material color.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBox_surface_gradient_mask_enable->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Enable opacity stops from gradient to control per-point transparency", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_surface_gradient_mask_enable->setText(QCoreApplication::translate("cMaterialEditorPanel", "Use opacity", nullptr));
        label_surface_gradient_opacity->setText(QCoreApplication::translate("cMaterialEditorPanel", "Strength:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_surface_gradient_opacity->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Master gradient strength (0.0 = no effect, 1.0 = full gradient). Multiplied by opacity stops when enabled.", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_specular_gradient_enable->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Specular highlights", nullptr));
#if QT_CONFIG(tooltip)
        colorpalette_specular_gradient->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Gradient which defines the colors of the specular highlights.</p><p>Brighter colors increase the highlights intensity. A black color creates no highlights.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBox_specular_gradient_mask_enable->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Enable opacity stops from gradient to control per-point transparency", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_specular_gradient_mask_enable->setText(QCoreApplication::translate("cMaterialEditorPanel", "Use opacity", nullptr));
        label_specular_gradient_opacity->setText(QCoreApplication::translate("cMaterialEditorPanel", "Strength:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_specular_gradient_opacity->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Master gradient strength (0.0 = no effect, 1.0 = full gradient)", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_diffuse_gradient_enable->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Diffuse (brighter -> higher glossiness)", nullptr));
#if QT_CONFIG(tooltip)
        colorpalette_diffuse_gradient->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Gradient which defines the intensity and width of specular highlights.</p><p>A higher value produces a more glossy surface, e.g. brighter highlights of a smaller width.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBox_diffuse_gradient_mask_enable->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Enable opacity stops from gradient to control per-point transparency", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_diffuse_gradient_mask_enable->setText(QCoreApplication::translate("cMaterialEditorPanel", "Use opacity", nullptr));
        label_diffuse_gradient_opacity->setText(QCoreApplication::translate("cMaterialEditorPanel", "Strength:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_diffuse_gradient_opacity->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Master gradient strength (0.0 = no effect, 1.0 = full gradient)", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_luminosity_gradient_enable->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Luminosity", nullptr));
#if QT_CONFIG(tooltip)
        colorpalette_luminosity_gradient->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Gradient which defines the luminosity of the fractal.</p><p>Higher brighness of gradient colors provides a higher luminosity.</p><p>This effect works only when the luminosity value is greater than zero.</p><p>To illuminate other objects by this gradient, <span style=\" font-style:italic;\">Monte Carlo Algorithm</span> / <span style=\" font-style:italic;\">Calculate MC Global Illumination </span>must be enabled.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBox_luminosity_gradient_mask_enable->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Enable opacity stops from gradient to control per-point transparency", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_luminosity_gradient_mask_enable->setText(QCoreApplication::translate("cMaterialEditorPanel", "Use opacity", nullptr));
        label_luminosity_gradient_opacity->setText(QCoreApplication::translate("cMaterialEditorPanel", "Strength:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_luminosity_gradient_opacity->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Master gradient strength (0.0 = no effect, 1.0 = full gradient)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        groupCheck_roughness_gradient_enable->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_roughness_gradient_enable->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Roughness (brighter -> higher roughness)", nullptr));
#if QT_CONFIG(tooltip)
        colorpalette_roughness_gradient->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Gradient which defines the roughness of the fractal surface.</p><p>A higher value provides higher roughness. A black color makes a smooth surface.</p><p>This gradient works only when &quot;Rough surface&quot; is enabled.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBox_roughness_gradient_mask_enable->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Enable opacity stops from gradient to control per-point transparency", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_roughness_gradient_mask_enable->setText(QCoreApplication::translate("cMaterialEditorPanel", "Use opacity", nullptr));
        label_roughness_gradient_opacity->setText(QCoreApplication::translate("cMaterialEditorPanel", "Strength:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_roughness_gradient_opacity->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Master gradient strength (0.0 = no effect, 1.0 = full gradient)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        groupCheck_reflectance_gradient_enable->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        groupCheck_reflectance_gradient_enable->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Reflectance", nullptr));
#if QT_CONFIG(tooltip)
        colorpalette_reflectance_gradient->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Gradient which defines the reflected light colors.</p><p>Brighter colors increase reflectance. A black color creates no reflections.</p><p>This gradient works only when <span style=\" font-style:italic;\">reflectance</span> is greater than zero.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBox_reflectance_gradient_mask_enable->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Enable opacity stops from gradient to control per-point transparency", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_reflectance_gradient_mask_enable->setText(QCoreApplication::translate("cMaterialEditorPanel", "Use opacity", nullptr));
        label_reflectance_gradient_opacity->setText(QCoreApplication::translate("cMaterialEditorPanel", "Strength:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_reflectance_gradient_opacity->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Master gradient strength (0.0 = no effect, 1.0 = full gradient)", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_transparency_gradient_enable->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Transparency", nullptr));
#if QT_CONFIG(tooltip)
        colorpalette_transparency_gradient->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Gradient which defines the transparency colors of the fractal.</p><p>Brighter colors increase transparency. A black color creates no transparency.</p><p>This gradient works only if <span style=\" font-style:italic;\">transparency of surface</span> is greater than zero.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBox_transparency_gradient_mask_enable->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Enable opacity stops from gradient to control per-point transparency", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_transparency_gradient_mask_enable->setText(QCoreApplication::translate("cMaterialEditorPanel", "Use opacity", nullptr));
        label_transparency_gradient_opacity->setText(QCoreApplication::translate("cMaterialEditorPanel", "Strength:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_transparency_gradient_opacity->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Master gradient strength (0.0 = no effect, 1.0 = full gradient)", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_gradient_processing->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Gradient Processing", nullptr));
        label_gradient_scale->setText(QCoreApplication::translate("cMaterialEditorPanel", "Scale:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_gradient_scale->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Scales the gradient position (1.0 = normal, 2.0 = compressed, 0.5 = stretched)", nullptr));
#endif // QT_CONFIG(tooltip)
        label_gradient_offset->setText(QCoreApplication::translate("cMaterialEditorPanel", "Offset:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_gradient_offset->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Shifts the gradient position", nullptr));
#endif // QT_CONFIG(tooltip)
        label_gradient_repeat_mode->setText(QCoreApplication::translate("cMaterialEditorPanel", "Repeat:", nullptr));
        comboBox_gradient_repeat_mode->setItemText(0, QCoreApplication::translate("cMaterialEditorPanel", "Clamp", nullptr));
        comboBox_gradient_repeat_mode->setItemText(1, QCoreApplication::translate("cMaterialEditorPanel", "Repeat", nullptr));
        comboBox_gradient_repeat_mode->setItemText(2, QCoreApplication::translate("cMaterialEditorPanel", "Mirror", nullptr));
        comboBox_gradient_repeat_mode->setItemText(3, QCoreApplication::translate("cMaterialEditorPanel", "Mirror Once", nullptr));
        comboBox_gradient_repeat_mode->setItemText(4, QCoreApplication::translate("cMaterialEditorPanel", "Extend", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_gradient_repeat_mode->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "How the gradient repeats outside [0,1] range", nullptr));
#endif // QT_CONFIG(tooltip)
        label_gradient_brightness->setText(QCoreApplication::translate("cMaterialEditorPanel", "Brightness:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_gradient_brightness->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Multiplies gradient color brightness", nullptr));
#endif // QT_CONFIG(tooltip)
        label_gradient_contrast->setText(QCoreApplication::translate("cMaterialEditorPanel", "Contrast:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_gradient_contrast->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Adjusts gradient color contrast", nullptr));
#endif // QT_CONFIG(tooltip)
        label_gradient_saturation->setText(QCoreApplication::translate("cMaterialEditorPanel", "Saturation:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_gradient_saturation->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Adjusts gradient color saturation (1.0 = normal, 0.0 = grayscale)", nullptr));
#endif // QT_CONFIG(tooltip)
        label_gradient_gamma->setText(QCoreApplication::translate("cMaterialEditorPanel", "Gamma:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_gradient_gamma->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Gamma correction for gradient colors (1.0 = no change)", nullptr));
#endif // QT_CONFIG(tooltip)
        label_gradient_color_space->setText(QCoreApplication::translate("cMaterialEditorPanel", "Color space:", nullptr));
        comboBox_gradient_color_space->setItemText(0, QCoreApplication::translate("cMaterialEditorPanel", "sRGB", nullptr));
        comboBox_gradient_color_space->setItemText(1, QCoreApplication::translate("cMaterialEditorPanel", "Linear RGB", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_gradient_color_space->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Interpolation color space for gradients", nullptr));
#endif // QT_CONFIG(tooltip)
        label_gradient_noise_amount->setText(QCoreApplication::translate("cMaterialEditorPanel", "Noise:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_gradient_noise_amount->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Adds noise dithering to reduce color banding", nullptr));
#endif // QT_CONFIG(tooltip)
        label_133->setText(QCoreApplication::translate("cMaterialEditorPanel", "Color speed:", nullptr));
        label_357->setText(QCoreApplication::translate("cMaterialEditorPanel", "Palette offset:", nullptr));
        label_fractal_coloring_circle_radius->setText(QCoreApplication::translate("cMaterialEditorPanel", "Orbit trap\n"
"   sphere radius:", nullptr));
#if QT_CONFIG(tooltip)
        vect4_fractal_coloring_line_direction_x->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Direction vector of the line used in the orbit trap coloring algorithm</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        vect4_fractal_coloring_line_direction_z->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Direction vector of line in orbit trap algorithm for coloring</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_fractal_coloring_line_direction_x->setText(QCoreApplication::translate("cMaterialEditorPanel", "x:", nullptr));
        label_fractal_coloring_line_direction_z->setText(QCoreApplication::translate("cMaterialEditorPanel", "z:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_coloring_speed->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Color palette speed sets the frequency of color changing</p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>speed 0.3</p></td><td><p>speed 1.0</p></td><td><p>speed 5.0</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/image - shader - colour speed 0.3.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - shader - colouring enabled.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - shader - colour speed 5.jpg\"/></p></td></tr></table></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_coloring_speed->setPrefix(QString());
        spinbox_coloring_speed->setSuffix(QString());
#if QT_CONFIG(tooltip)
        spinbox_fractal_coloring_sphere_radius->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Radius of the sphere used in the orbit trap coloring algorithm </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_fractal_coloring_sphere_radius->setPrefix(QString());
        spinbox_fractal_coloring_sphere_radius->setSuffix(QString());
        comboBox_fractal_coloring_algorithm->setItemText(0, QCoreApplication::translate("cMaterialEditorPanel", "Standard", nullptr));
        comboBox_fractal_coloring_algorithm->setItemText(1, QCoreApplication::translate("cMaterialEditorPanel", "orbit trap: z.Dot(point)", nullptr));
        comboBox_fractal_coloring_algorithm->setItemText(2, QCoreApplication::translate("cMaterialEditorPanel", "orbit trap: Sphere", nullptr));
        comboBox_fractal_coloring_algorithm->setItemText(3, QCoreApplication::translate("cMaterialEditorPanel", "orbit trap: Cross", nullptr));
        comboBox_fractal_coloring_algorithm->setItemText(4, QCoreApplication::translate("cMaterialEditorPanel", "orbit trap: Line", nullptr));
        comboBox_fractal_coloring_algorithm->setItemText(5, QCoreApplication::translate("cMaterialEditorPanel", "orbit trap: Cylinder", nullptr));
        comboBox_fractal_coloring_algorithm->setItemText(6, QCoreApplication::translate("cMaterialEditorPanel", "orbit trap: Torus", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_fractal_coloring_algorithm->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Selection between different coloring algorithms based on an orbit trap calculation, (distance of point from orbit trap.)</p><p>- Standard: orbit trap defined as a point at the origin.  The value is the value at the <span style=\" text-decoration: underline;\">end</span> of orbit trap iterations</p><p>The rest of the algorithms use the minimum value recorded <span style=\" text-decoration: underline;\">during</span> the orbit trap iterations.</p><p>- orbit trap: z.Dot(point): orbit trap defined as the starting coordinates of the point being iterated</p><p>- orbit trap: Sphere: orbit trap defined as a sphere surface</p><p>- orbit trap: Cross: orbit trap defined as a cross</p><p>- orbit trap: Line: orbit trap defined as a line in set direction</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_fractal_coloring_line_direction_y->setText(QCoreApplication::translate("cMaterialEditorPanel", "y:", nullptr));
        label_354->setText(QCoreApplication::translate("cMaterialEditorPanel", "Coloring algorithm:", nullptr));
#if QT_CONFIG(tooltip)
        vect4_fractal_coloring_line_direction_y->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Direction vector of line in orbit trap algorithm for coloring</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinbox_coloring_palette_offset->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Offset applied to the fractal coloring palette. Shifts the color mapping along the palette, allowing fine-tuning of color distribution on the fractal surface. Used in combination with coloring speed and gradients.", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_coloring_palette_offset->setPrefix(QString());
        spinbox_coloring_palette_offset->setSuffix(QString());
        label_fractal_coloring_line_direction_z_2->setText(QCoreApplication::translate("cMaterialEditorPanel", "w:", nullptr));
#if QT_CONFIG(tooltip)
        vect4_fractal_coloring_line_direction_w->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Direction vector of line in orbit trap algorithm for coloring</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_fractal_coloring_line_direction->setText(QCoreApplication::translate("cMaterialEditorPanel", "Orbit trap line\n"
"   direction vector:", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_fractal_coloring_color_preV215_false->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>For backwards compatibity.  If enabled, OpenCL and Non-OpenCL modes will sometimes render different coloring.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_extra_color_options_false->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Can be used for controlling the relative size of the three color components in the Hybrid Mode.</p><p>These controls can also be used for pre-V2.15 backwards compatibility</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_extra_color_options_false->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Extra Hybrid Mode Co&lor Options", nullptr));
        label_63->setText(QCoreApplication::translate("cMaterialEditorPanel", "Hybrid Mode Color", nullptr));
        label_88->setText(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p><span style=\" font-weight:400;\">radDivDe scale:</span></p></body></html>", nullptr));
        spinbox_fractal_coloring_rad_div_de_scale1->setPrefix(QString());
        spinbox_fractal_coloring_rad_div_de_scale1->setSuffix(QString());
        label_89->setText(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p><span style=\" font-weight:400;\">aux.color scale:</span></p></body></html>", nullptr));
        spinbox_fractal_coloring_aux_color_scale1->setPrefix(QString());
        spinbox_fractal_coloring_aux_color_scale1->setSuffix(QString());
        spinbox_fractal_coloring_orbit_trap_scale1->setPrefix(QString());
        spinbox_fractal_coloring_orbit_trap_scale1->setSuffix(QString());
        label_90->setText(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p><span style=\" font-weight:400;\">orbit trap scale:</span></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_extra_color_enabled_false->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>At Default Color_Speed the distance between two colors is 256. With these functions this distance = 1.0, e.g. a radius of 1.0 is one color step from the color at the origin. Similarly an addition of 1.0 = 256, cos period 1 =256.</p><p><br/>At the end of these functions, the colorValue is then multiplied by * 256.</p><p>Settings vary widely depending on such factors as fractal type &amp; size, location and number of iterations.</p><p>Adjusting the color speed may be required.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_extra_color_enabled_false->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "C&olor by numbers", nullptr));
        label_64->setText(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p><span style=\" font-weight:400;\">initial colorValue:</span></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fractal_coloring_initial_color_value->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        spinbox_fractal_coloring_initial_color_value->setPrefix(QString());
        spinbox_fractal_coloring_initial_color_value->setSuffix(QString());
#if QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_init_cond_enabled_false->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>&quot;c&quot; (aux.c) is the original coordinates of the point being iterated. These &quot;c&quot; functions, color the point domain before the fractal is iterated, e.g. assigning an Initial ColorValue (default,  all = 0.0.)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_init_cond_enabled_false->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "co&lorValue Initial Conditions Components", nullptr));
        label_45->setText(QCoreApplication::translate("cMaterialEditorPanel", "c radius * scale:", nullptr));
        label_46->setText(QCoreApplication::translate("cMaterialEditorPanel", "c.z * scale:", nullptr));
        label_43->setText(QCoreApplication::translate("cMaterialEditorPanel", "c.x * scale:", nullptr));
        label_44->setText(QCoreApplication::translate("cMaterialEditorPanel", "c.y * scale:", nullptr));
        spinbox_fractal_coloring_ic_rad_weight->setPrefix(QString());
        spinbox_fractal_coloring_ic_rad_weight->setSuffix(QString());
        spinbox3_fractal_coloring_xyzC_111_z->setPrefix(QString());
        spinbox3_fractal_coloring_xyzC_111_z->setSuffix(QString());
        spinbox3_fractal_coloring_xyzC_111_y->setPrefix(QString());
        spinbox3_fractal_coloring_xyzC_111_y->setSuffix(QString());
        spinbox3_fractal_coloring_xyzC_111_x->setPrefix(QString());
        spinbox3_fractal_coloring_xyzC_111_x->setSuffix(QString());
        groupBox_2->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Fractal Color Components", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_orbit_trap_true->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>OrbitTrap weight  scales the colorValue input from the chosen Coloring Algorithm above (orbit traps). This allows blending of this input with other functions.</p><p>Initial minimumR is a separate limit set in the code  to control the size of this colorValue.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_orbit_trap_true->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Orbit trap com&ponent", nullptr));
        label_78->setText(QCoreApplication::translate("cMaterialEditorPanel", "weight of 19.5 = old default (minimumR * 5000)", nullptr));
        label_81->setText(QCoreApplication::translate("cMaterialEditorPanel", "weight of 3.9 = old hybrid default (minimumR * 1000)", nullptr));
        label_62->setText(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p><span style=\" font-weight:400;\">orbit trap weight:</span></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fractal_coloring_orbit_trap_weight->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        spinbox_fractal_coloring_orbit_trap_weight->setPrefix(QString());
        spinbox_fractal_coloring_orbit_trap_weight->setSuffix(QString());
#if QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_aux_color_false->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>These components collect and update data with every iteration. </p><p>aux.color is what collects theXYZplane and radius components, as in the original Mandelbox UI: Coloring Parameters.</p><p>aux.colorHybrid is the input from some experimental color Transforms.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_aux_color_false->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "a&uxillary color components", nullptr));
        label_83->setText(QCoreApplication::translate("cMaterialEditorPanel", "weight of 0.39 =  old hybrid default (aux.color * 100)", nullptr));
        label_58->setText(QCoreApplication::translate("cMaterialEditorPanel", "aux. color weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fractal_coloring_aux_color_weight->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Use with fractals that have aux.color components. aux.color must be enabled on the formula UI.</p><p>These functions update a running colorValue total, every iteration (may result in localized cuts in the color)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_fractal_coloring_aux_color_weight->setPrefix(QString());
        spinbox_fractal_coloring_aux_color_weight->setSuffix(QString());
        label_59->setText(QCoreApplication::translate("cMaterialEditorPanel", "aux. color hybrid weight:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fractal_coloring_aux_color_hybrid_weight->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>For BETA transforms: trans_hybrid_color &amp; trans_hybrid_color2.</p><p>Parameter controls weight of aux.colorHybrid values.</p><p>Assume these functions may not be backwards compatible in later releases.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_fractal_coloring_aux_color_hybrid_weight->setPrefix(QString());
        spinbox_fractal_coloring_aux_color_hybrid_weight->setSuffix(QString());
#if QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_rad_enabled_false->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>ColorValue is derived from the radius of the point at termination.</p><p>Radius derived changes in colorValue are often inside the fractal. Can use with pseudoKleinian type structures.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_rad_enabled_false->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "rad&ius components", nullptr));
        spinbox_fractal_coloring_rad_weight->setPrefix(QString());
        spinbox_fractal_coloring_rad_weight->setSuffix(QString());
        label_52->setText(QCoreApplication::translate("cMaterialEditorPanel", "radius  * scale:", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_rad_div_de_enabled_false->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>ColorValue is derived from the radius of the point divided by the DE value, at termination.</p><p>Radius derived changes in colorValue are often inside the fractal. Can use with pseudoKleinian type structures.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_rad_div_de_enabled_false->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "rad&ius / DE components", nullptr));
        label_84->setText(QCoreApplication::translate("cMaterialEditorPanel", "scale of 19.5 = old hybrid default ( r  * 5000) / DE )", nullptr));
        spinbox_fractal_coloring_rad_div_de_weight->setPrefix(QString());
        spinbox_fractal_coloring_rad_div_de_weight->setSuffix(QString());
        label_53->setText(QCoreApplication::translate("cMaterialEditorPanel", "radius  / DE  * scale", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_xyz_bias_enabled_false->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>ColorValue is derived from the coordinates of the point at termination</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_xyz_bias_enabled_false->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "xyz &bias", nullptr));
        label_40->setText(QCoreApplication::translate("cMaterialEditorPanel", "z.z * scale:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox3_fractal_coloring_xyz_000_y->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>color_y  = z.y   *  scale_y ;</p><p><br/></p><p>colorValue = color_x + color_y + color_z;</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox3_fractal_coloring_xyz_000_y->setPrefix(QString());
        spinbox3_fractal_coloring_xyz_000_y->setSuffix(QString());
#if QT_CONFIG(tooltip)
        spinbox_fractal_coloring_xyz_iter_scale->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>colorValue *= (1.0 + ( i * scale));</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_fractal_coloring_xyz_iter_scale->setPrefix(QString());
        spinbox_fractal_coloring_xyz_iter_scale->setSuffix(QString());
        label_35->setText(QCoreApplication::translate("cMaterialEditorPanel", "iter scale :", nullptr));
        label_38->setText(QCoreApplication::translate("cMaterialEditorPanel", "z.y * scale:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox3_fractal_coloring_xyz_000_x->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>color_x  = z.x   *  scale_x ;</p><p><br/></p><p>colorValue = color_x + color_y + color_z;</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox3_fractal_coloring_xyz_000_x->setPrefix(QString());
        spinbox3_fractal_coloring_xyz_000_x->setSuffix(QString());
        label_39->setText(QCoreApplication::translate("cMaterialEditorPanel", "sqrd", nullptr));
#if QT_CONFIG(tooltip)
        spinbox3_fractal_coloring_xyz_000_z->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>color_z  = z.z   *  scale_z ;</p><p><br/></p><p>colorValue = color_x + color_y + color_z;</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox3_fractal_coloring_xyz_000_z->setPrefix(QString());
        spinbox3_fractal_coloring_xyz_000_z->setSuffix(QString());
        label_36->setText(QCoreApplication::translate("cMaterialEditorPanel", "z.x * scale:", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_iter_group_enabled_false->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>As these functions are simply iteration based, they will produce sharp changes in color based on the iteration count at termination.</p><p>Adjusting the color speed may be required, depending on the size of the fractal and location.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_iter_group_enabled_false->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "color&Value iteration components", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fractal_coloring_iter_add_scale->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>colorValue += addValue * ( i - startIter);</p><p>An addValue of 1.0 equals one whole color step along the palette, at default color speed of 1.0.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_fractal_coloring_iter_add_scale->setPrefix(QString());
        spinbox_fractal_coloring_iter_add_scale->setSuffix(QString());
#if QT_CONFIG(tooltip)
        spinbox_fractal_coloring_iter_scale->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>colorValue *=  1.0 +   ( scale * ( i  -  startIter));</p><p>This function will not work on its own, it always needs some other component supplying a range of colorValues.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_fractal_coloring_iter_scale->setPrefix(QString());
        spinbox_fractal_coloring_iter_scale->setSuffix(QString());
        label_42->setText(QCoreApplication::translate("cMaterialEditorPanel", "start function at iteration:", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Final ColorValue Controls", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_global_palette_false->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>These options deform the Final ColorValues derived from the previous functions.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_global_palette_false->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Palette deformin&g options", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_add_enabled_false->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Function produces an addition to the ColorValues based on its current value.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_add_enabled_false->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "addition curv&e function", nullptr));
        spinbox_fractal_coloring_add_spread->setPrefix(QString());
        spinbox_fractal_coloring_add_spread->setSuffix(QString());
        label_68->setText(QCoreApplication::translate("cMaterialEditorPanel", "spread factor:", nullptr));
        label_76->setText(QCoreApplication::translate("cMaterialEditorPanel", "maximum add:", nullptr));
        spinbox_fractal_coloring_add_start_value->setPrefix(QString());
        spinbox_fractal_coloring_add_start_value->setSuffix(QString());
        label_77->setText(QCoreApplication::translate("cMaterialEditorPanel", "start value:", nullptr));
        spinbox_fractal_coloring_add_max->setPrefix(QString());
        spinbox_fractal_coloring_add_max->setSuffix(QString());
#if QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_parab_enabled_false->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Function produces an addition to the ColorValues based on its current value.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_parab_enabled_false->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "paraboli&c function", nullptr));
        label_79->setText(QCoreApplication::translate("cMaterialEditorPanel", "parab scale:", nullptr));
        label_80->setText(QCoreApplication::translate("cMaterialEditorPanel", "start value:", nullptr));
        spinbox_fractal_coloring_parab_start_value->setPrefix(QString());
        spinbox_fractal_coloring_parab_start_value->setSuffix(QString());
        spinbox_fractal_coloring_parab_scale->setPrefix(QString());
        spinbox_fractal_coloring_parab_scale->setSuffix(QString());
#if QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_cos_enabled_false->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Function produces an addition to the ColorValues based on its current value.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_cos_enabled_false->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "t&rig function", nullptr));
        spinbox_fractal_coloring_cos_add->setPrefix(QString());
        spinbox_fractal_coloring_cos_add->setSuffix(QString());
        label_48->setText(QCoreApplication::translate("cMaterialEditorPanel", "cosine add:", nullptr));
        label_47->setText(QCoreApplication::translate("cMaterialEditorPanel", "cosine period:", nullptr));
        spinbox_fractal_coloring_cos_start_value->setPrefix(QString());
        spinbox_fractal_coloring_cos_start_value->setSuffix(QString());
        label_51->setText(QCoreApplication::translate("cMaterialEditorPanel", "start value:", nullptr));
        spinbox_fractal_coloring_cos_period->setPrefix(QString());
        spinbox_fractal_coloring_cos_period->setSuffix(QString());
#if QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_round_enabled_false->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Function rounds adjacent colorValues to produces solid color bands (i.e. no transitions between colors.)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_fractal_coloring_round_enabled_false->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "roun&d", nullptr));
        spinbox_fractal_coloring_round_scale->setPrefix(QString());
        spinbox_fractal_coloring_round_scale->setSuffix(QString());
        label_57->setText(QCoreApplication::translate("cMaterialEditorPanel", "round scale", nullptr));
        label_34->setText(QCoreApplication::translate("cMaterialEditorPanel", "min colorValue", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fractal_coloring_min_color_value->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Limit of minimum colorValue (units are still 1.0 = 256 colorValue units).</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_fractal_coloring_min_color_value->setPrefix(QString());
        spinbox_fractal_coloring_min_color_value->setSuffix(QString());
        label_37->setText(QCoreApplication::translate("cMaterialEditorPanel", "max colorValue", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_fractal_coloring_max_color_value->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Limit of maximum colorValue (units are still 1.0 = 256 colorValue units).</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_fractal_coloring_max_color_value->setPrefix(QString());
        spinbox_fractal_coloring_max_color_value->setSuffix(QString());
        groupBox->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Surface color", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_surface_color->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Color of the object's surface . This color is used when 'Use colors from palette' is disabled or when the material is to be applied to a non-fractal object.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_surface_color->setProperty("text", QVariant(QCoreApplication::translate("cMaterialEditorPanel", "PushButton", nullptr)));
        label_56->setText(QCoreApplication::translate("cMaterialEditorPanel", "Single color:", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_use_color_texture->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Use image file as color texture.</p><p>Color texture is mixed with 'Single Color' (if palette is off) or 'Palette' (if palette is on). </p><p>example:</p><p><img src=\":/tooltips/tooltips_images/material - color texture.jpg\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_use_color_texture->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Use color texture from an &image", nullptr));
        label_378->setText(QCoreApplication::translate("cMaterialEditorPanel", "Texture intensity:", nullptr));
        label_377->setText(QCoreApplication::translate("cMaterialEditorPanel", "Texture path:", nullptr));
#if QT_CONFIG(tooltip)
        text_file_color_texture->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Path to image with color texture</p><p>To use animated textures (image sequences), replace numbers by '%' symbol. Example: If sequence of images is as showed below: <br/>texture0001.jpg<br/>texture0002.jpg<br/>etc</p><p>Then use following file name: texture%%%%.jpg<br/>This tells the program to treat this as not a single image but as a sequence of images with 4 digit index.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinbox_color_texture_intensity->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Adjusts the influence of the loaded color texture on the material's surface color. A value of 0 uses only the base color; a value of 1 uses only the texture. Intermediate values blend between the two.", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_color_texture_intensity->setPrefix(QString());
        spinbox_color_texture_intensity->setSuffix(QString());
        groupCheck_perlin_noise_color_enable->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Use perlin noise for color", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_perlin_noise_color_intensity->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Contrast of color texture</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_perlin_noise_color_intensity->setPrefix(QString());
        spinbox_perlin_noise_color_intensity->setSuffix(QString());
        label_41->setText(QCoreApplication::translate("cMaterialEditorPanel", "intensity", nullptr));
        checkBox_perlin_noise_color_invert->setText(QCoreApplication::translate("cMaterialEditorPanel", "invert", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Shading", nullptr));
        label_2->setText(QCoreApplication::translate("cMaterialEditorPanel", "(effect of angle of incidence of light)", nullptr));
        label_55->setText(QCoreApplication::translate("cMaterialEditorPanel", "Shading:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_shading->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>angle of incidence effects intensity</p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>shading 0.0</p></td><td><p>shading 1.0 </p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/image - shader - shading 0.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - shader - shading 1.jpg\"/></p></td></tr></table></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_shading->setPrefix(QString());
        spinbox_shading->setSuffix(QString());
        groupBox_7->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Specular highlight", nullptr));
        label_72->setText(QCoreApplication::translate("cMaterialEditorPanel", "Specular highlight color:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_specular_color->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Color of specular highlights</p><p>example:</p><p><img src=\":/tooltips/tooltips_images/material - specular highlight color.jpg\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_specular_color->setProperty("text", QVariant(QCoreApplication::translate("cMaterialEditorPanel", "PushButton", nullptr)));
#if QT_CONFIG(tooltip)
        groupCheck_specular_plastic_enable->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Plastic specular reflection has color defined by <span style=\" font-style:italic;\">Specular highlight color</span> and depends on light source color. Surface color doesn't affect specular reflection color.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_specular_plastic_enable->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Plastic specular reflection", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_specular_width->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Size of specular highlights<br/></p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>width 0.1</p></td><td><p>width 1.0</p></td><td><p>width 5.0</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/material - specular highlight width 0.1.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/material - specular highlight width 1.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/material - specular highlight width 5.jpg\"/></p></td></tr></table></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_specular_width->setPrefix(QString());
        spinbox_specular_width->setSuffix(QString());
#if QT_CONFIG(tooltip)
        spinbox_specular->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Intensity of specular highlights</p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>brightness 0</p></td><td><p>brightness 5 </p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/image - shader - specularity 0.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - shader - specularity 5.jpg\"/></p></td></tr></table></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_specular->setPrefix(QString());
        spinbox_specular->setSuffix(QString());
        label_69->setText(QCoreApplication::translate("cMaterialEditorPanel", "Specular highlight brightness:", nullptr));
        label_71->setText(QCoreApplication::translate("cMaterialEditorPanel", "Specular highlight width:", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_metallic->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Metallic specular reflection has color defined by <span style=\" font-style:italic;\">Specular highlight color</span> and depends on light source color and surface color.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_metallic->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Metallic specular reflection", nullptr));
        label_85->setText(QCoreApplication::translate("cMaterialEditorPanel", "Specular highlight brightness:", nullptr));
        label_86->setText(QCoreApplication::translate("cMaterialEditorPanel", "Specular highlight width:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_specular_metallic->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Intensity of metallic specular highlights</p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>brightness 0</p></td><td><p>brightness 5</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/image - shader - specularity 0.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - shader - specular metallic 5.jpg\"/></p></td></tr></table></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_specular_metallic->setPrefix(QString());
        spinbox_specular_metallic->setSuffix(QString());
#if QT_CONFIG(tooltip)
        spinbox_specular_metallic_width->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Width of metallic specular highlights </p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>width 0.2</p></td><td><p>width 2</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/image - shader - specular metallic width 02.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - shader - specular metallic width 2.jpg\"/></p></td></tr></table></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_specular_metallic_width->setPrefix(QString());
        spinbox_specular_metallic_width->setSuffix(QString());
        label_87->setText(QCoreApplication::translate("cMaterialEditorPanel", "Roughness", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_specular_metallic_roughness->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Roughness of metallic specular highlights </p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>roughness 0</p></td><td><p>roughness 5</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/image - shader - specular metallic 5.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - shader - specular metallic roughness 10.jpg\"/></p></td></tr></table><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_specular_metallic_roughness->setPrefix(QString());
        spinbox_specular_metallic_roughness->setSuffix(QString());
#if QT_CONFIG(tooltip)
        groupCheck_rough_surface->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Makes surface rough. This effect works well with enabled Monte Carlo algorithms.</p><p><img src=\":/tooltips/tooltips_images/material - roughness 0,05.jpg\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_rough_surface->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Rough surface", nullptr));
        label_93->setText(QCoreApplication::translate("cMaterialEditorPanel", "Roughness:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_surface_roughness->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Roughness of object surface</p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>roughness 0</p></td><td><p>roughness 0.05</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/material - roughness 0.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/material - roughness 0,05.jpg\"/></p></td></tr></table></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_surface_roughness->setPrefix(QString());
        spinbox_surface_roughness->setSuffix(QString());
        groupCheck_use_roughness_texture->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Use roughness map texture", nullptr));
        label_395->setText(QCoreApplication::translate("cMaterialEditorPanel", "Texture intensity:", nullptr));
        label_396->setText(QCoreApplication::translate("cMaterialEditorPanel", "Texture path:", nullptr));
        spinbox_roughness_texture_intensity->setPrefix(QString());
        spinbox_roughness_texture_intensity->setSuffix(QString());
#if QT_CONFIG(tooltip)
        groupCheck_iridescence_enabled->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Iridescence makes gradual changes of surface colour as the angle of view or the angle of illumination changes. </p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>Iridescence disabled</p></td><td><p>Ididescence enabled</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/material - iridescence off.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/material - iridescence on.jpg\"/></p></td></tr></table></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_iridescence_enabled->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Iridescence", nullptr));
        label_75->setText(QCoreApplication::translate("cMaterialEditorPanel", "Intensity:", nullptr));
        spinbox_iridescence_intensity->setPrefix(QString());
        spinbox_iridescence_intensity->setSuffix(QString());
        label_82->setText(QCoreApplication::translate("cMaterialEditorPanel", "Subsurface relative thickness", nullptr));
        spinbox_iridescence_subsurface_thickness->setPrefix(QString());
        spinbox_iridescence_subsurface_thickness->setSuffix(QString());
        groupBox_8->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Luminosity", nullptr));
        label_73->setText(QCoreApplication::translate("cMaterialEditorPanel", "Luminosity:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_luminosity->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Intensity of the luminosity of the selected color.</p><p>Note: luminosity effect illuminates near objects only when Global Illumination is enabled.</p><p>Example of luminosity effect:</p><p><img src=\":/tooltips/tooltips_images/material - luminosity.jpg\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_luminosity->setPrefix(QString());
        spinbox_luminosity->setSuffix(QString());
        label_74->setText(QCoreApplication::translate("cMaterialEditorPanel", "Luminosity color:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_luminosity_color->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Color of the luminosity effect.</p><p>Note: luminosity effect does not illuminate near objects.</p><p>Example of luminosity effect:</p><p><img src=\":/tooltips/tooltips_images/material - luminosity.jpg\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_luminosity_color->setProperty("text", QVariant(QCoreApplication::translate("cMaterialEditorPanel", "PushButton", nullptr)));
        label_94->setText(QCoreApplication::translate("cMaterialEditorPanel", "Emission multiplier:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_luminosity_emissive->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Multiplier of luminosity intensity wich controls amount of emited light in global illumination effect,</p><p>Note: luminosity effect illuminates near objects only when Global Illumination is enabled.</p><p>Example of luminosity effect:</p><p><img src=\":/tooltips/tooltips_images/material - luminosity.jpg\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_luminosity_emissive->setPrefix(QString());
        spinbox_luminosity_emissive->setSuffix(QString());
#if QT_CONFIG(tooltip)
        groupCheck_use_luminosity_texture->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Use an image as a texture for luminosity effect.</p><p>Example:</p><p><img src=\":/tooltips/tooltips_images/material - luminosity texture.jpg\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_use_luminosity_texture->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Use luminosity te&xture", nullptr));
        label_379->setText(QCoreApplication::translate("cMaterialEditorPanel", "Texture intensity:", nullptr));
        label_380->setText(QCoreApplication::translate("cMaterialEditorPanel", "Texture path:", nullptr));
#if QT_CONFIG(tooltip)
        text_file_luminosity_texture->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Path to image with luminosity texture</p><p>To use animated textures (image sequences), replace numbers by '%' symbol. Example: If sequence of images is as showed below: <br/>texture0001.jpg<br/>texture0002.jpg<br/>etc</p><p>Then use following file name: texture%%%%.jpg<br/>This tells the program to treat this as not a single image but as a sequence of images with 4 digit index.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinbox_luminosity_texture_intensity->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Controls how much the luminosity texture affects the material's self-illumination. Higher values increase the contribution of the texture to the final luminosity.", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_luminosity_texture_intensity->setPrefix(QString());
        spinbox_luminosity_texture_intensity->setSuffix(QString());
        groupCheck_perlin_noise_luminosity_enable->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Use perlin noise for luminosity", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_perlin_noise_luminosity_intensity->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Contrast of color texture</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_perlin_noise_luminosity_intensity->setPrefix(QString());
        spinbox_perlin_noise_luminosity_intensity->setSuffix(QString());
        label_49->setText(QCoreApplication::translate("cMaterialEditorPanel", "intensity", nullptr));
        checkBox_perlin_noise_luminosity_invert->setText(QCoreApplication::translate("cMaterialEditorPanel", "invert", nullptr));
        groupBox_9->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Reflections and refraction", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_fresnel_reflectance->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>If enabled the reflectance is calculated from Fresnel's equations.  Reflectance is dependant on the angle of incidence of the ray.</p><p>To apply this effect, enable ray-traced reflections in <span style=\" font-style:italic;\">Raytracing</span> tab</p><p><br/></p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>Fresnel's equations off</p></td><td><p>Fresnel's equations on</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/material - reflectance fresnel off.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/material - reflectance fresnel.jpg\"/></p></td></tr></table></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_fresnel_reflectance->setText(QCoreApplication::translate("cMaterialEditorPanel", "Fresnel's equations for reflectance", nullptr));
        label_352->setText(QCoreApplication::translate("cMaterialEditorPanel", "Index of refraction:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_transparency_index_of_refraction->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Index of refraction of the material. It has influence on transparent objects and on non-transparent reflective objects. It affects the calculation in Fresnel's equations. </p><p>To apply this effect, enable ray-traced reflections in <span style=\" font-style:italic;\">Raytracing</span> tab</p><p>Example values: vacuum 1.0; glass.1.5; water 1.35; diamond 2.41<br/></p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>index of refraction 1.0 (gas or vacuum)</p></td><td><p>index of refraction 1.5 (glass)</p></td><td><p>index of refraction 2.0</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/material - transparency index of refraction 1.0.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/material - transparency index of refraction 1.5.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/material - transparency index of refraction 2.0.jpg\"/></p></td></tr></table></b"
                        "ody></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_transparency_index_of_refraction->setPrefix(QString());
        spinbox_transparency_index_of_refraction->setSuffix(QString());
        groupBox_10->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Reflections", nullptr));
        colorButton_reflections_color->setProperty("text", QVariant(QCoreApplication::translate("cMaterialEditorPanel", "PushButton", nullptr)));
        label_70->setText(QCoreApplication::translate("cMaterialEditorPanel", "Reflectance:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_reflectance->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Intensity of light reflection effect</p><p>To apply this effect, enable ray-traced reflections in <span style=\" font-style:italic;\">Raytracing</span> tab or environment mapping<br/></p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>reflectance 0.5</p></td><td><p>reflectance 0.8</p></td><td><p>reflectance 1.0 (perfect reflection)</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/material - reflectance 0.5.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/material - reflectance 0.8.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/material - reflectance 1.0.jpg\"/></p></td></tr></table></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_reflectance->setPrefix(QString());
        spinbox_reflectance->setSuffix(QString());
        label_91->setText(QCoreApplication::translate("cMaterialEditorPanel", "Color of reflections:", nullptr));
        groupCheck_use_reflectance_texture->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Use reflectance map texture", nullptr));
        label_397->setText(QCoreApplication::translate("cMaterialEditorPanel", "Texture intensity:", nullptr));
        label_398->setText(QCoreApplication::translate("cMaterialEditorPanel", "Texture path:", nullptr));
        spinbox_reflectance_texture_intensity->setPrefix(QString());
        spinbox_reflectance_texture_intensity->setSuffix(QString());
        groupCheck_perlin_noise_reflectance_enable->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Use perlin noise for reflectance", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_perlin_noise_reflectance_intensity->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Contrast of color texture</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_perlin_noise_reflectance_intensity->setPrefix(QString());
        spinbox_perlin_noise_reflectance_intensity->setSuffix(QString());
        label_54->setText(QCoreApplication::translate("cMaterialEditorPanel", "intensity", nullptr));
        checkBox_perlin_noise_reflectance_invert->setText(QCoreApplication::translate("cMaterialEditorPanel", "invert", nullptr));
        groupBox_11->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Transparency", nullptr));
        label_295->setText(QCoreApplication::translate("cMaterialEditorPanel", "Transparency of surface:", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_inside_coloring->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Apply color gradient to the volume of the object (if transparency of volume is lower than 1)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_inside_coloring->setText(QCoreApplication::translate("cMaterialEditorPanel", "Use color gradient for interior", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_transparency_interior_color->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Color of interior of transparent objects.</p><p>To apply this effect, enable ray-traced reflections in <span style=\" font-style:italic;\">Raytracing</span> tab</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_transparency_interior_color->setProperty("text", QVariant(QCoreApplication::translate("cMaterialEditorPanel", "PushButton", nullptr)));
#if QT_CONFIG(tooltip)
        logedit_transparency_of_interior->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Transparency of the fractal interior. Thicker parts of the object will appear less transparent than thinner parts.</p><p>To apply this effect, enable ray-traced reflections in <span style=\" font-style:italic;\">Raytracing</span> tab</p><p>Examples for yellow color of volume</p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>transparency 0.5</p></td><td><p>transparency 0.8</p></td><td><p>transparency 1.0</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/material - transparency of volume 0.5.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/material - transparency of volume 0.8.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/material - transparency of surface 1.0.jpg\"/></p></td></tr></table></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_92->setText(QCoreApplication::translate("cMaterialEditorPanel", "Color of transparency:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_transparency_of_surface->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Transparency of fractal surface. </p><p>This effect simulates glass or other refractive materials. For fast rendering, it is recommended to decrease the 'maximum number of iterations' to as low a value as will still produce acceptable  image quality ( e.g. maybe about 20 iterations).</p><p>To apply this effect, enable ray-traced reflections in <span style=\" font-style:italic;\">Raytracing</span> tab </p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>transparency 0.5</p></td><td><p>transparency 0.8</p></td><td><p>transparency 1.0</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/material - transparency of surface 0.5.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/material - transparency of surface 0.8.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/material - transparency of surface 1.0.jpg\"/></p></td></tr></table></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_transparency_of_surface->setPrefix(QString());
        spinbox_transparency_of_surface->setSuffix(QString());
        colorButton_transparency_color->setProperty("text", QVariant(QCoreApplication::translate("cMaterialEditorPanel", "PushButton", nullptr)));
        label_351->setText(QCoreApplication::translate("cMaterialEditorPanel", "Transparency of volume:", nullptr));
        label_353->setText(QCoreApplication::translate("cMaterialEditorPanel", "Color of volume:", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_subsurface_scattering->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Scatters the light inside the object. It involves calculation of shadows through the volume of the object.</p><p>Because the effect is slow for calculation, it is recomended to decrease Maximum number of fractal iterations to a level which does not change the appearance of the objects.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_subsurface_scattering->setText(QCoreApplication::translate("cMaterialEditorPanel", "Subsurface scattering", nullptr));
        groupCheck_use_transparency_texture->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Use transparency color map texture", nullptr));
        spinbox_transparency_texture_intensity->setPrefix(QString());
        spinbox_transparency_texture_intensity->setSuffix(QString());
        label_399->setText(QCoreApplication::translate("cMaterialEditorPanel", "Texture intensity on surface:", nullptr));
        label_400->setText(QCoreApplication::translate("cMaterialEditorPanel", "Texture path:", nullptr));
        spinbox_transparency_texture_intensity_vol->setPrefix(QString());
        spinbox_transparency_texture_intensity_vol->setSuffix(QString());
        label_401->setText(QCoreApplication::translate("cMaterialEditorPanel", "Texture intensity in volume:", nullptr));
        groupCheck_use_transparency_alpha_texture->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Use transparency texture (alpha)", nullptr));
        label_404->setText(QCoreApplication::translate("cMaterialEditorPanel", "Texture path:", nullptr));
        label_403->setText(QCoreApplication::translate("cMaterialEditorPanel", "Texture intensity on surface:", nullptr));
        spinbox_transparency_alpha_texture_intensity->setPrefix(QString());
        spinbox_transparency_alpha_texture_intensity->setSuffix(QString());
        label_405->setText(QCoreApplication::translate("cMaterialEditorPanel", "Texture intensity in volume:", nullptr));
        spinbox_transparency_alpha_texture_intensity_vol->setPrefix(QString());
        spinbox_transparency_alpha_texture_intensity_vol->setSuffix(QString());
        groupCheck_perlin_noise_transparency_color_enable->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Use perlin noise for transparency color", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_perlin_noise_transparency_color_intensity->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Contrast of color texture</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_perlin_noise_transparency_color_intensity->setPrefix(QString());
        spinbox_perlin_noise_transparency_color_intensity->setSuffix(QString());
        checkBox_perlin_noise_transparency_color_invert->setText(QCoreApplication::translate("cMaterialEditorPanel", "invert", nullptr));
        label_60->setText(QCoreApplication::translate("cMaterialEditorPanel", "intensity on surface", nullptr));
        label_65->setText(QCoreApplication::translate("cMaterialEditorPanel", "intensity in volume", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_perlin_noise_transparency_color_intensity_vol->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Contrast of color texture</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_perlin_noise_transparency_color_intensity_vol->setPrefix(QString());
        spinbox_perlin_noise_transparency_color_intensity_vol->setSuffix(QString());
        groupCheck_perlin_noise_transparency_alpha_enable->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Use perlin noise for alpha", nullptr));
        label_61->setText(QCoreApplication::translate("cMaterialEditorPanel", "intensity on surface", nullptr));
        checkBox_perlin_noise_transparency_alpha_invert->setText(QCoreApplication::translate("cMaterialEditorPanel", "invert", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_perlin_noise_transparency_alpha_intensity->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Contrast of color texture</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_perlin_noise_transparency_alpha_intensity->setPrefix(QString());
        spinbox_perlin_noise_transparency_alpha_intensity->setSuffix(QString());
        label_66->setText(QCoreApplication::translate("cMaterialEditorPanel", "intensity in volume", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_perlin_noise_transparency_alpha_intensity_vol->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Contrast of color texture</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_perlin_noise_transparency_alpha_intensity_vol->setPrefix(QString());
        spinbox_perlin_noise_transparency_alpha_intensity_vol->setSuffix(QString());
        label_5->setText(QCoreApplication::translate("cMaterialEditorPanel", "Note: reduce Maximum number of fractal iterations to the level which will not cause changes to the objects shape. It will significantly speed up calculations.", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_use_diffusion_texture->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Diffusion texture controls the amount and color of the reflected light. It also controls the intensity and width of the specular reflections.</p><p>Areas with brighter colors will reflect more light, the specular reflection will be brighter and the size of the specular reflections will be smaller (i.e. simulates polished surface.)</p><p>Dark areas will not reflect light, and the specular reflections will be dark and wide (i.e. simulates a rough surface). </p><p>Example:</p><p><img src=\":/tooltips/tooltips_images/material - diffusion texture.jpg\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_use_diffusion_texture->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Use diffusion &texture", nullptr));
        label_383->setText(QCoreApplication::translate("cMaterialEditorPanel", "Texture intensity:", nullptr));
        label_384->setText(QCoreApplication::translate("cMaterialEditorPanel", "Texture path:", nullptr));
#if QT_CONFIG(tooltip)
        text_file_diffusion_texture->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Path to the image to be used for diffusion texture</p><p>To use animated textures (image sequences), replace numbers by '%' symbol. Example: If sequence of images is as showed below: <br/>texture0001.jpg<br/>texture0002.jpg<br/>etc</p><p>Then use following file name: texture%%%%.jpg<br/>This tells the program to treat this as not a single image but as a sequence of images with 4 digit index.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinbox_diffusion_texture_intensity->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Brightness of diffusion texture. Higher value will simulate more polished surface.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_diffusion_texture_intensity->setPrefix(QString());
        spinbox_diffusion_texture_intensity->setSuffix(QString());
#if QT_CONFIG(tooltip)
        groupCheck_use_normal_map_texture->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Normal mapping is a technique used for faking the lighting of bumps and dents \342\200\223 an implementation of bump mapping. Normal map texture changes locally the direction of the surface normal vector, (i.e. <span style=\" text-decoration: underline;\">simulates</span> local changes of the surface angle). It causes changes to the way that the light is reflected or diffused. Normal maps do not deform the object surface, but just give the appearance of deformation.</p><p>Normal map textures uses color components to define the direction of the deflection of a normal vector. Red represents X axis, green represents Y axis and blue represents Z axis. </p><p>Normal maps can be derived from height maps (bumpmaps)<br/></p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>Example normal map texture:</p></td><td><p>Example height map</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/norma"
                        "l_map_texture.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/displacement_texture.jpg\"/></p></td></tr></table><p>Example object with normal map texture:</p><p><img src=\":/tooltips/tooltips_images/material - normal map texture.jpg\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_use_normal_map_texture->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Use normal &map texture", nullptr));
        label_394->setText(QCoreApplication::translate("cMaterialEditorPanel", "Texture path:", nullptr));
        label_393->setText(QCoreApplication::translate("cMaterialEditorPanel", "Intensity:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_normal_map_texture_height->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Intensity of bumps.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        text_file_normal_map_texture->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Path to the image to be used as the normal map texture</p><p>To use animated textures (image sequences), replace numbers by '%' symbol. Example: If sequence of images is as showed below: <br/>texture0001.jpg<br/>texture0002.jpg<br/>etc</p><p>Then use following file name: texture%%%%.jpg<br/>This tells the program to treat this as not a single image but as a sequence of images with 4 digit index.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBox_normal_map_texture_from_bumpmap->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Enables the use of greyscale heightmaps as bump maps, like on the image below. The bump map is internally converted to a normal map. </p><p><img src=\":/tooltips/tooltips_images/displacement_texture.jpg\"/></p><p>This texture can give the following result:</p><p><img src=\":/tooltips/tooltips_images/material - normal map texture from bumpmap.jpg\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_normal_map_texture_from_bumpmap->setText(QCoreApplication::translate("cMaterialEditorPanel", "Normal map derived from greyscale bump map", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_normal_map_texture_invert_green->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>There are two standards of normal maps. The difference between them is in the direction of the Y component of the normal vector. Visually when the Y component is swapped then the green component of the texture is inverted.</p><p><br/></p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>standard</p></td><td><p>inverted</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/normal_map_texture.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/normal_map_texture_g_inv.jpg\"/></p></td></tr></table><p>To recognize which standard it is, check how the colors are located on the convex part of the texture.</p><p>Standard:   top left corner - green,  bottom right- red</p><p>Inverted:    bottom left corner - green,  right top - red</p><p>If you use inverted texture, then this check box should be ticked.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_normal_map_texture_invert_green->setText(QCoreApplication::translate("cMaterialEditorPanel", "Invert green (Y+ / Y-)", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_use_displacement_texture->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Displacement map technique uses texture to cause an effect where the actual geometric position of points over the textured surface are displaced. It gives the surfaces a greater sense of depth and detail, permitting self-shadowing. In contrast to normal mapping, it deforms object surface.</p><p>Example displacement map texture (in most cases it can be the same as for bump maps). Brighter pixels will give bigger embossing of surface.</p><p><img src=\":/tooltips/tooltips_images/displacement_texture.jpg\"/></p><p>Example result:</p><p><img src=\":/tooltips/tooltips_images/material - displacement map.jpg\"/></p><p>Note: displacement map does not work with cubic mapping of texture.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_use_displacement_texture->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Use displacement &map texture", nullptr));
        label_381->setText(QCoreApplication::translate("cMaterialEditorPanel", "Displacement height:", nullptr));
        label_382->setText(QCoreApplication::translate("cMaterialEditorPanel", "Texture path:", nullptr));
#if QT_CONFIG(tooltip)
        text_file_displacement_texture->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Path to image with displacement map texture</p><p>To use animated textures (image sequences), replace numbers by '%' symbol. Example: If sequence of images is as showed below: <br/>texture0001.jpg<br/>texture0002.jpg<br/>etc</p><p>Then use following file name: texture%%%%.jpg<br/>This tells the program to treat this as not a single image but as a sequence of images with 4 digit index.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_displacement_texture_height->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Height of displacement. Height is in the same units as object sizes.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_perlin_noise_displacement_enable->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Use perlin noise for displacement", nullptr));
        label_50->setText(QCoreApplication::translate("cMaterialEditorPanel", "intensity", nullptr));
        checkBox_perlin_noise_displacement_invert->setText(QCoreApplication::translate("cMaterialEditorPanel", "invert", nullptr));
#if QT_CONFIG(tooltip)
        logedit_perlin_noise_displacement_intensity->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Height of displacement. Height is in the same units as object sizes.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_texture_options->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Texture mapping", nullptr));
        groupCheck_texture_fractalize->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Fractalize texture", nullptr));
        label->setText(QCoreApplication::translate("cMaterialEditorPanel", "Map texture to fractal shape using algorithm basing on orbit traps", nullptr));
        label_4->setText(QCoreApplication::translate("cMaterialEditorPanel", "start orbit trap at iteration:", nullptr));
        label_3->setText(QCoreApplication::translate("cMaterialEditorPanel", "Orbit trap cube size", nullptr));
        label_fractalize_shape->setText(QCoreApplication::translate("cMaterialEditorPanel", "Orbit trap shape:", nullptr));
        comboBox_texture_fractalize_shape->setItemText(0, QCoreApplication::translate("cMaterialEditorPanel", "Cube", nullptr));
        comboBox_texture_fractalize_shape->setItemText(1, QCoreApplication::translate("cMaterialEditorPanel", "Sphere", nullptr));
        comboBox_texture_fractalize_shape->setItemText(2, QCoreApplication::translate("cMaterialEditorPanel", "Cross", nullptr));
        comboBox_texture_fractalize_shape->setItemText(3, QCoreApplication::translate("cMaterialEditorPanel", "Line", nullptr));
        comboBox_texture_fractalize_shape->setItemText(4, QCoreApplication::translate("cMaterialEditorPanel", "Plane", nullptr));
        comboBox_texture_fractalize_shape->setItemText(5, QCoreApplication::translate("cMaterialEditorPanel", "Cylinder", nullptr));
        comboBox_texture_fractalize_shape->setItemText(6, QCoreApplication::translate("cMaterialEditorPanel", "Torus", nullptr));
        comboBox_texture_fractalize_shape->setItemText(7, QCoreApplication::translate("cMaterialEditorPanel", "Spiral", nullptr));

        label_374->setText(QCoreApplication::translate("cMaterialEditorPanel", "z:", nullptr));
        label_386->setText(QCoreApplication::translate("cMaterialEditorPanel", "Mapping type:", nullptr));
        label_376->setText(QCoreApplication::translate("cMaterialEditorPanel", "y:", nullptr));
        label_375->setText(QCoreApplication::translate("cMaterialEditorPanel", "x:", nullptr));
        label_372->setText(QCoreApplication::translate("cMaterialEditorPanel", "x:", nullptr));
        label_388->setText(QCoreApplication::translate("cMaterialEditorPanel", "Texture scale:\n"
"   (relative to\n"
"   object size)", nullptr));
        label_390->setText(QCoreApplication::translate("cMaterialEditorPanel", "alpha:", nullptr));
        comboBox_texture_mapping_type->setItemText(0, QCoreApplication::translate("cMaterialEditorPanel", "Spherical", nullptr));
        comboBox_texture_mapping_type->setItemText(1, QCoreApplication::translate("cMaterialEditorPanel", "Cubic", nullptr));
        comboBox_texture_mapping_type->setItemText(2, QCoreApplication::translate("cMaterialEditorPanel", "Cylindrical", nullptr));
        comboBox_texture_mapping_type->setItemText(3, QCoreApplication::translate("cMaterialEditorPanel", "Planar", nullptr));
        comboBox_texture_mapping_type->setItemText(4, QCoreApplication::translate("cMaterialEditorPanel", "Triplanar", nullptr));
        comboBox_texture_mapping_type->setItemText(5, QCoreApplication::translate("cMaterialEditorPanel", "Equirectangular", nullptr));
        comboBox_texture_mapping_type->setItemText(6, QCoreApplication::translate("cMaterialEditorPanel", "Triplanar Stochastic", nullptr));
        comboBox_texture_mapping_type->setItemText(7, QCoreApplication::translate("cMaterialEditorPanel", "Cylindrical Fractal", nullptr));
        comboBox_texture_mapping_type->setItemText(8, QCoreApplication::translate("cMaterialEditorPanel", "Spherical Fractal", nullptr));
        comboBox_texture_mapping_type->setItemText(9, QCoreApplication::translate("cMaterialEditorPanel", "Octa", nullptr));
        comboBox_texture_mapping_type->setItemText(10, QCoreApplication::translate("cMaterialEditorPanel", "Camera", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_texture_mapping_type->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Geometry of texture mapping<br/></p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>Planar - texture is mapped as a 2D plane</p></td><td><p>Spherical - texture is mapped as a sphere around the object center</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/material - planar mapping.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/material - spherical mapping.jpg\"/></p></td></tr></table><p><br/></p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>Cylindrical - texture is mapped as a cylinder around the object axis</p></td><td><p>Cubic - texture is mapped in accordance with the surface direction of a cube.<br/>Note: this mapping cannot be used with a displacement map </p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/material - cylindrical mapping.jpg\"/></p>"
                        "</td><td><p><img src=\":/tooltips/tooltips_images/material - cubic mapping.jpg\"/></p></td></tr></table></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_373->setText(QCoreApplication::translate("cMaterialEditorPanel", "y:", nullptr));
        label_387->setText(QCoreApplication::translate("cMaterialEditorPanel", "z:", nullptr));
        label_389->setText(QCoreApplication::translate("cMaterialEditorPanel", "Texture\n"
"   rotation:", nullptr));
        label_391->setText(QCoreApplication::translate("cMaterialEditorPanel", "beta:", nullptr));
        label_392->setText(QCoreApplication::translate("cMaterialEditorPanel", "gamma:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox3_texture_center_x->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Position of the center of the texture. Position is relative to the texture size.</p><p>Note: size of texture is always 1 x 1 x 1.</p><p>Example of changed texture center [0.3, 0.3, 0.0] </p><p><img src=\":/tooltips/tooltips_images/material - cubic mapping - center 0.3 0.3 0.0.jpg\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox3_texture_center_x->setPrefix(QString());
        spinbox3_texture_center_x->setSuffix(QString());
#if QT_CONFIG(tooltip)
        spinbox3_texture_center_y->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Position of center of the texture. Position is relative to object size.</p><p>Note: object size of fractal object is always 1 x 1 x 1.</p><p>Example of changed texture center [0.3, 0.3, 0.0] </p><p><img src=\":/tooltips/tooltips_images/material - cubic mapping - center 0.3 0.3 0.0.jpg\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox3_texture_center_y->setPrefix(QString());
        spinbox3_texture_center_y->setSuffix(QString());
#if QT_CONFIG(tooltip)
        spinbox3_texture_center_z->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Position of center of the texture. Position is relative to object size.</p><p>Note: object size of fractal object is always 1 x 1 x 1.</p><p>Example of changed texture center [0.3, 0.3, 0.0] </p><p><img src=\":/tooltips/tooltips_images/material - cubic mapping - center 0.3 0.3 0.0.jpg\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox3_texture_center_z->setPrefix(QString());
        spinbox3_texture_center_z->setSuffix(QString());
#if QT_CONFIG(tooltip)
        logvect3_texture_scale_x->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Size of the texture. Size is relative to object size.</p><p>Note: object size of fractal object is always 1 x 1 x 1.</p><p>Example of changed texture scale [0.3, 0.3, 0.3] </p><p><img src=\":/tooltips/tooltips_images/material - cubic mapping - scaled down.jpg\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logvect3_texture_scale_y->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Size of the texture. Size is relative to object size.</p><p>Note: object size of fractal object is always 1 x 1 x 1.</p><p>Example of changed texture scale [0.3, 0.3, 0.3] </p><p><img src=\":/tooltips/tooltips_images/material - cubic mapping - scaled down.jpg\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logvect3_texture_scale_z->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Size of the texture. Size is relative to object size.</p><p>Note: object size of fractal object is always 1 x 1 x 1.</p><p>Example of changed texture scale [0.3, 0.3, 0.3] </p><p><img src=\":/tooltips/tooltips_images/material - cubic mapping - scaled down.jpg\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinboxd3_texture_rotation_x->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Rotation of the texture relative to the object orientation.</p><p>Example of rotated texture</p><p><img src=\":/tooltips/tooltips_images/material - planar mapping - rotated.jpg\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinboxd3_texture_rotation_x->setPrefix(QString());
        spinboxd3_texture_rotation_x->setSuffix(QString());
#if QT_CONFIG(tooltip)
        spinboxd3_texture_rotation_y->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Rotation of the texture relative to the object orientation.</p><p>Example of rotated texture</p><p><img src=\":/tooltips/tooltips_images/material - planar mapping - rotated.jpg\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinboxd3_texture_rotation_y->setPrefix(QString());
        spinboxd3_texture_rotation_y->setSuffix(QString());
#if QT_CONFIG(tooltip)
        spinboxd3_texture_rotation_z->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "<html><head/><body><p>Rotation of the texture relative to the object orientation.</p><p>Example of rotated texture</p><p><img src=\":/tooltips/tooltips_images/material - planar mapping - rotated.jpg\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinboxd3_texture_rotation_z->setPrefix(QString());
        spinboxd3_texture_rotation_z->setSuffix(QString());
        label_385->setText(QCoreApplication::translate("cMaterialEditorPanel", "Texture center:\n"
"   (relative to\n"
"   object size)", nullptr));
        groupCheck_perlin_noise_enable->setTitle(QCoreApplication::translate("cMaterialEditorPanel", "Perlin noise", nullptr));
        label_402->setText(QCoreApplication::translate("cMaterialEditorPanel", "Noise position\n"
"   offset:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_perlin_noise_period_x->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Defines the period (scale) of the Perlin noise along each axis. Larger values create broader, slower variations; smaller values create finer details.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBox_perlin_noise_abs->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "f enabled, uses the absolute value of the Perlin noise, resulting in a mirrored, always-positive pattern for certain effects.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_perlin_noise_abs->setText(QCoreApplication::translate("cMaterialEditorPanel", "abs() function", nullptr));
#if QT_CONFIG(tooltip)
        vect3_perlin_noise_position_offset_y->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Offsets the Perlin noise pattern in 3D space, allowing you to shift the noise effect without changing its scale or orientation.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_115->setText(QCoreApplication::translate("cMaterialEditorPanel", "Noise period:", nullptr));
        label_6->setText(QCoreApplication::translate("cMaterialEditorPanel", "Noise iterations", nullptr));
#if QT_CONFIG(tooltip)
        spinboxd3_perlin_noise_rotation_x->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Rotates the Perlin noise pattern around the respective axis, affecting the orientation of noise features.", nullptr));
#endif // QT_CONFIG(tooltip)
        spinboxd3_perlin_noise_rotation_x->setPrefix(QString());
        spinboxd3_perlin_noise_rotation_x->setSuffix(QString());
#if QT_CONFIG(tooltip)
        spinbox_perlin_noise_value_offset->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Adds a constant offset to the Perlin noise value before applying it, useful for biasing the effect or controlling thresholds.", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_perlin_noise_value_offset->setPrefix(QString());
        spinbox_perlin_noise_value_offset->setSuffix(QString());
        label_137->setText(QCoreApplication::translate("cMaterialEditorPanel", "z:", nullptr));
        label_408->setText(QCoreApplication::translate("cMaterialEditorPanel", "z:", nullptr));
        label_136->setText(QCoreApplication::translate("cMaterialEditorPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_perlin_noise_period_y->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Defines the period (scale) of the Perlin noise along each axis. Larger values create broader, slower variations; smaller values create finer details.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_7->setText(QCoreApplication::translate("cMaterialEditorPanel", "Value offset", nullptr));
        label_406->setText(QCoreApplication::translate("cMaterialEditorPanel", "x:", nullptr));
#if QT_CONFIG(tooltip)
        spinboxInt_perlin_noise_iterations->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Sets the number of octaves (layers) for Perlin noise, increasing the complexity and detail of the noise pattern.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_407->setText(QCoreApplication::translate("cMaterialEditorPanel", "y:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_perlin_noise_position_offset_z->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Offsets the Perlin noise pattern in 3D space, allowing you to shift the noise effect without changing its scale or orientation.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinboxd3_perlin_noise_rotation_y->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Rotates the Perlin noise pattern around the respective axis, affecting the orientation of noise features.", nullptr));
#endif // QT_CONFIG(tooltip)
        spinboxd3_perlin_noise_rotation_y->setPrefix(QString());
        spinboxd3_perlin_noise_rotation_y->setSuffix(QString());
#if QT_CONFIG(tooltip)
        vect3_perlin_noise_period_z->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Defines the period (scale) of the Perlin noise along each axis. Larger values create broader, slower variations; smaller values create finer details.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_135->setText(QCoreApplication::translate("cMaterialEditorPanel", "x:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_perlin_noise_position_offset_x->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Offsets the Perlin noise pattern in 3D space, allowing you to shift the noise effect without changing its scale or orientation.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinboxd3_perlin_noise_rotation_z->setToolTip(QCoreApplication::translate("cMaterialEditorPanel", "Rotates the Perlin noise pattern around the respective axis, affecting the orientation of noise features.", nullptr));
#endif // QT_CONFIG(tooltip)
        spinboxd3_perlin_noise_rotation_z->setPrefix(QString());
        spinboxd3_perlin_noise_rotation_z->setSuffix(QString());
        label_409->setText(QCoreApplication::translate("cMaterialEditorPanel", "Noise\n"
"   rotation:", nullptr));
        (void)cMaterialEditorPanel;
    } // retranslateUi

};

namespace Ui {
    class cMaterialEditorPanel: public Ui_cMaterialEditorPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATERIAL_EDITOR_PANEL_H
