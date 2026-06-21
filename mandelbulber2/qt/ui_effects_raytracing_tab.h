/********************************************************************************
** Form generated from reading UI file 'effects_raytracing_tab.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EFFECTS_RAYTRACING_TAB_H
#define UI_EFFECTS_RAYTRACING_TAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "buton_load_settings_from_widget.h"
#include "buton_random_settings_from_widget.h"
#include "buton_reset_settings_from_widget.h"
#include "buton_save_settings_from_widget.h"
#include "file_select_widget.h"
#include "my_check_box.h"
#include "my_color_button.h"
#include "my_combo_box.h"
#include "my_double_spin_box.h"
#include "my_group_box.h"
#include "my_line_edit.h"
#include "my_spin_box.h"

QT_BEGIN_NAMESPACE

class Ui_cEffectsRaytracingTab
{
public:
    QVBoxLayout *verticalLayout_64;
    QHBoxLayout *horizontalLayout_2;
    cButtonLoadSettingsFromWidget *pushButton_local_load_2;
    cButtonSaveSettingsFromWidget *pushButton_local_save_2;
    cButtonResetSettingsFromWidget *pushButton_local_reset_2;
    cButtonRandomSettingsFromWidget *pushButton_local_randomize_2;
    QSpacerItem *horizontalSpacer_2;
    QScrollArea *scrollArea_7;
    QWidget *scrollAreaWidgetContents_8;
    QVBoxLayout *verticalLayout_34;
    MyGroupBox *groupCheck_raytraced_reflections;
    QVBoxLayout *verticalLayout_72;
    QGridLayout *gridLayout_9;
    MySpinBox *spinboxInt_reflections_max;
    QLabel *label_62;
    MyGroupBox *groupCheck_DOF_enabled;
    QVBoxLayout *verticalLayout_73;
    QGridLayout *gridLayout_35;
    QLabel *label_131;
    QLabel *label_136;
    MyLineEdit *logedit_DOF_focus;
    MyDoubleSpinBox *spinbox_DOF_radius;
    QLabel *label_349;
    MySpinBox *spinboxInt_DOF_number_of_passes;
    QLabel *label_350;
    MyDoubleSpinBox *spinbox_DOF_blur_opacity;
    QLabel *label_138;
    MyDoubleSpinBox *spinbox_DOF_max_radius;
    QLabel *label_dof_autofocus;
    MyCheckBox *checkBox_DOF_auto_focus;
    QLabel *label_dof_autofocus_mode;
    MyComboBox *comboBox_DOF_auto_focus_mode;
    QLabel *label_dof_blur_kernel;
    MyComboBox *comboBox_DOF_blur_kernel;
    QLabel *label_auto_dof_focus_bias;
    MyDoubleSpinBox *spinbox_auto_dof_focus_bias;
    QLabel *label_auto_dof_radius_scale;
    MyDoubleSpinBox *spinbox_auto_dof_radius_scale;
    QLabel *label_auto_dof_max_radius_scale;
    MyDoubleSpinBox *spinbox_auto_dof_max_radius_scale;
    QLabel *label_auto_dof_blur_opacity_scale;
    MyDoubleSpinBox *spinbox_auto_dof_blur_opacity_scale;
    QPushButton *pushButton_DOF_update;
    QPushButton *pushButton_DOF_set_focus;
    MyGroupBox *groupCheck_DOF_monte_carlo;
    QVBoxLayout *verticalLayout_152;
    QGridLayout *gridLayout_97;
    QLabel *label_358;
    QLabel *label_359;
    QLabel *label_average_DOF_samples;
    MyLineEdit *logedit_DOF_max_noise;
    QLabel *label_average_DOF_noise;
    MySpinBox *spinboxInt_DOF_min_samples;
    QLabel *label_360;
    MySpinBox *spinboxInt_DOF_samples;
    QLabel *label_masked_pixels;
    QLabel *label_tiles_done;
    MyCheckBox *checkBox_MC_pixel_level_optimization;
    QHBoxLayout *horizontalLayout_progressive_adaptive_threshold;
    QLabel *label_progressive_adaptive_threshold;
    QSlider *slider_progressive_adaptive_threshold;
    MyDoubleSpinBox *spinbox_progressive_adaptive_threshold;
    QCheckBox *checkB_MCShowNoiseLevels;
    MyGroupBox *groupCheck_MC_denoiser_enable;
    QGridLayout *gridLayout_4;
    MyComboBox *comboBox_MC_denoiser_strength;
    QLabel *label_6;
    MyCheckBox *checkBox_MC_denoiser_preserve_geometry;
    MyCheckBox *checkBox_DOF_MC_global_illumination;
    QGridLayout *gridLayout_18;
    MyLineEdit *logedit_MC_GI_radiance_limit;
    QLabel *label_361;
    MyCheckBox *checkBox_MC_GI_use_reflectance;
    MyCheckBox *checkBox_MC_global_illumination_volumetric;
    MyCheckBox *checkBox_MC_fog_illumination;
    MyCheckBox *checkBox_MC_soft_shadows_enable;
    MyGroupBox *groupCheck_DOF_MC_CA_enable;
    QVBoxLayout *verticalLayout_75;
    QGridLayout *gridLayout_11;
    MyLineEdit *logedit_DOF_MC_CA_dispersion_gain;
    QLabel *label_69;
    QLabel *label_70;
    MyLineEdit *logedit_DOF_MC_CA_camera_dispersion;
    MyGroupBox *groupCheck_ambient_occlusion_enabled;
    QVBoxLayout *verticalLayout_69;
    QGridLayout *gridLayout_33;
    QLabel *label_103;
    QLabel *label_127;
    MySpinBox *spinboxInt_ambient_occlusion_quality;
    MyDoubleSpinBox *spinbox_ambient_occlusion_fast_tune;
    QLabel *label_132;
    QLabel *label_68;
    MyDoubleSpinBox *spinbox_ambient_occlusion;
    MyComboBox *comboBox_ambient_occlusion_mode;
    MyColorButton *colorButton_ambient_occlusion_color;
    QLabel *label_71;
    MyCheckBox *checkBox_SSAO_random_mode;
    QFrame *frame_lightmap_texture;
    QVBoxLayout *verticalLayout_138;
    QLabel *label_171;
    QGridLayout *gridLayout_74;
    FileSelectWidget *text_file_lightmap;
    QGridLayout *gridLayout_23;
    QLabel *label_236;
    QLabel *label_235;
    QLabel *label_234;
    QLabel *label_237;
    MyDoubleSpinBox *spinboxd3_ao_light_map_rotation_x;
    MyDoubleSpinBox *spinboxd3_ao_light_map_rotation_y;
    MyDoubleSpinBox *spinboxd3_ao_light_map_rotation_z;
    MyGroupBox *groupCheck_env_mapping_enable;
    QVBoxLayout *verticalLayout_119;
    QLabel *label_5;
    QGridLayout *gridLayout_73;
    QLabel *label_170;
    FileSelectWidget *text_file_envmap;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *cEffectsRaytracingTab)
    {
        if (cEffectsRaytracingTab->objectName().isEmpty())
            cEffectsRaytracingTab->setObjectName(QString::fromUtf8("cEffectsRaytracingTab"));
        verticalLayout_64 = new QVBoxLayout(cEffectsRaytracingTab);
        verticalLayout_64->setSpacing(2);
        verticalLayout_64->setObjectName(QString::fromUtf8("verticalLayout_64"));
        verticalLayout_64->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_local_load_2 = new cButtonLoadSettingsFromWidget(cEffectsRaytracingTab);
        pushButton_local_load_2->setObjectName(QString::fromUtf8("pushButton_local_load_2"));

        horizontalLayout_2->addWidget(pushButton_local_load_2);

        pushButton_local_save_2 = new cButtonSaveSettingsFromWidget(cEffectsRaytracingTab);
        pushButton_local_save_2->setObjectName(QString::fromUtf8("pushButton_local_save_2"));

        horizontalLayout_2->addWidget(pushButton_local_save_2);

        pushButton_local_reset_2 = new cButtonResetSettingsFromWidget(cEffectsRaytracingTab);
        pushButton_local_reset_2->setObjectName(QString::fromUtf8("pushButton_local_reset_2"));

        horizontalLayout_2->addWidget(pushButton_local_reset_2);

        pushButton_local_randomize_2 = new cButtonRandomSettingsFromWidget(cEffectsRaytracingTab);
        pushButton_local_randomize_2->setObjectName(QString::fromUtf8("pushButton_local_randomize_2"));

        horizontalLayout_2->addWidget(pushButton_local_randomize_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_64->addLayout(horizontalLayout_2);

        scrollArea_7 = new QScrollArea(cEffectsRaytracingTab);
        scrollArea_7->setObjectName(QString::fromUtf8("scrollArea_7"));
        scrollArea_7->setWidgetResizable(true);
        scrollAreaWidgetContents_8 = new QWidget();
        scrollAreaWidgetContents_8->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_8"));
        scrollAreaWidgetContents_8->setGeometry(QRect(0, -168, 421, 1501));
        verticalLayout_34 = new QVBoxLayout(scrollAreaWidgetContents_8);
        verticalLayout_34->setSpacing(2);
        verticalLayout_34->setObjectName(QString::fromUtf8("verticalLayout_34"));
        verticalLayout_34->setContentsMargins(2, 2, 2, 2);
        groupCheck_raytraced_reflections = new MyGroupBox(scrollAreaWidgetContents_8);
        groupCheck_raytraced_reflections->setObjectName(QString::fromUtf8("groupCheck_raytraced_reflections"));
        groupCheck_raytraced_reflections->setCheckable(true);
        verticalLayout_72 = new QVBoxLayout(groupCheck_raytraced_reflections);
        verticalLayout_72->setSpacing(2);
        verticalLayout_72->setObjectName(QString::fromUtf8("verticalLayout_72"));
        verticalLayout_72->setContentsMargins(2, 2, 2, 2);
        gridLayout_9 = new QGridLayout();
        gridLayout_9->setSpacing(2);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        spinboxInt_reflections_max = new MySpinBox(groupCheck_raytraced_reflections);
        spinboxInt_reflections_max->setObjectName(QString::fromUtf8("spinboxInt_reflections_max"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(spinboxInt_reflections_max->sizePolicy().hasHeightForWidth());
        spinboxInt_reflections_max->setSizePolicy(sizePolicy);
        spinboxInt_reflections_max->setMaximum(1000);

        gridLayout_9->addWidget(spinboxInt_reflections_max, 0, 1, 1, 1);

        label_62 = new QLabel(groupCheck_raytraced_reflections);
        label_62->setObjectName(QString::fromUtf8("label_62"));

        gridLayout_9->addWidget(label_62, 0, 0, 1, 1);


        verticalLayout_72->addLayout(gridLayout_9);


        verticalLayout_34->addWidget(groupCheck_raytraced_reflections);

        groupCheck_DOF_enabled = new MyGroupBox(scrollAreaWidgetContents_8);
        groupCheck_DOF_enabled->setObjectName(QString::fromUtf8("groupCheck_DOF_enabled"));
        groupCheck_DOF_enabled->setCheckable(true);
        verticalLayout_73 = new QVBoxLayout(groupCheck_DOF_enabled);
        verticalLayout_73->setSpacing(2);
        verticalLayout_73->setObjectName(QString::fromUtf8("verticalLayout_73"));
        verticalLayout_73->setContentsMargins(2, 2, 2, 2);
        gridLayout_35 = new QGridLayout();
        gridLayout_35->setSpacing(2);
        gridLayout_35->setObjectName(QString::fromUtf8("gridLayout_35"));
        label_131 = new QLabel(groupCheck_DOF_enabled);
        label_131->setObjectName(QString::fromUtf8("label_131"));

        gridLayout_35->addWidget(label_131, 0, 0, 1, 1);

        label_136 = new QLabel(groupCheck_DOF_enabled);
        label_136->setObjectName(QString::fromUtf8("label_136"));

        gridLayout_35->addWidget(label_136, 1, 0, 1, 1);

        logedit_DOF_focus = new MyLineEdit(groupCheck_DOF_enabled);
        logedit_DOF_focus->setObjectName(QString::fromUtf8("logedit_DOF_focus"));

        gridLayout_35->addWidget(logedit_DOF_focus, 0, 1, 1, 1);

        spinbox_DOF_radius = new MyDoubleSpinBox(groupCheck_DOF_enabled);
        spinbox_DOF_radius->setObjectName(QString::fromUtf8("spinbox_DOF_radius"));
        sizePolicy.setHeightForWidth(spinbox_DOF_radius->sizePolicy().hasHeightForWidth());
        spinbox_DOF_radius->setSizePolicy(sizePolicy);
        spinbox_DOF_radius->setDecimals(2);
        spinbox_DOF_radius->setMinimum(0.010000000000000);
        spinbox_DOF_radius->setMaximum(5000.000000000000000);
        spinbox_DOF_radius->setSingleStep(1.000000000000000);
        spinbox_DOF_radius->setValue(1.000000000000000);

        gridLayout_35->addWidget(spinbox_DOF_radius, 1, 1, 1, 1);

        label_349 = new QLabel(groupCheck_DOF_enabled);
        label_349->setObjectName(QString::fromUtf8("label_349"));

        gridLayout_35->addWidget(label_349, 3, 0, 1, 1);

        spinboxInt_DOF_number_of_passes = new MySpinBox(groupCheck_DOF_enabled);
        spinboxInt_DOF_number_of_passes->setObjectName(QString::fromUtf8("spinboxInt_DOF_number_of_passes"));
        sizePolicy.setHeightForWidth(spinboxInt_DOF_number_of_passes->sizePolicy().hasHeightForWidth());
        spinboxInt_DOF_number_of_passes->setSizePolicy(sizePolicy);
        spinboxInt_DOF_number_of_passes->setMinimum(1);
        spinboxInt_DOF_number_of_passes->setMaximum(10);

        gridLayout_35->addWidget(spinboxInt_DOF_number_of_passes, 3, 1, 1, 1);

        label_350 = new QLabel(groupCheck_DOF_enabled);
        label_350->setObjectName(QString::fromUtf8("label_350"));

        gridLayout_35->addWidget(label_350, 4, 0, 1, 1);

        spinbox_DOF_blur_opacity = new MyDoubleSpinBox(groupCheck_DOF_enabled);
        spinbox_DOF_blur_opacity->setObjectName(QString::fromUtf8("spinbox_DOF_blur_opacity"));
        sizePolicy.setHeightForWidth(spinbox_DOF_blur_opacity->sizePolicy().hasHeightForWidth());
        spinbox_DOF_blur_opacity->setSizePolicy(sizePolicy);
        spinbox_DOF_blur_opacity->setDecimals(2);
        spinbox_DOF_blur_opacity->setMinimum(0.010000000000000);
        spinbox_DOF_blur_opacity->setMaximum(100.000000000000000);
        spinbox_DOF_blur_opacity->setSingleStep(0.100000000000000);
        spinbox_DOF_blur_opacity->setValue(0.100000000000000);

        gridLayout_35->addWidget(spinbox_DOF_blur_opacity, 4, 1, 1, 1);

        label_138 = new QLabel(groupCheck_DOF_enabled);
        label_138->setObjectName(QString::fromUtf8("label_138"));

        gridLayout_35->addWidget(label_138, 2, 0, 1, 1);

        spinbox_DOF_max_radius = new MyDoubleSpinBox(groupCheck_DOF_enabled);
        spinbox_DOF_max_radius->setObjectName(QString::fromUtf8("spinbox_DOF_max_radius"));
        sizePolicy.setHeightForWidth(spinbox_DOF_max_radius->sizePolicy().hasHeightForWidth());
        spinbox_DOF_max_radius->setSizePolicy(sizePolicy);
        spinbox_DOF_max_radius->setDecimals(2);
        spinbox_DOF_max_radius->setMinimum(0.010000000000000);
        spinbox_DOF_max_radius->setMaximum(5000.000000000000000);
        spinbox_DOF_max_radius->setSingleStep(1.000000000000000);
        spinbox_DOF_max_radius->setValue(1.000000000000000);

        gridLayout_35->addWidget(spinbox_DOF_max_radius, 2, 1, 1, 1);

        label_dof_autofocus = new QLabel(groupCheck_DOF_enabled);
        label_dof_autofocus->setObjectName(QString::fromUtf8("label_dof_autofocus"));

        gridLayout_35->addWidget(label_dof_autofocus, 5, 0, 1, 1);

        checkBox_DOF_auto_focus = new MyCheckBox(groupCheck_DOF_enabled);
        checkBox_DOF_auto_focus->setObjectName(QString::fromUtf8("checkBox_DOF_auto_focus"));
        sizePolicy.setHeightForWidth(checkBox_DOF_auto_focus->sizePolicy().hasHeightForWidth());
        checkBox_DOF_auto_focus->setSizePolicy(sizePolicy);

        gridLayout_35->addWidget(checkBox_DOF_auto_focus, 5, 1, 1, 1);

        label_dof_autofocus_mode = new QLabel(groupCheck_DOF_enabled);
        label_dof_autofocus_mode->setObjectName(QString::fromUtf8("label_dof_autofocus_mode"));

        gridLayout_35->addWidget(label_dof_autofocus_mode, 6, 0, 1, 1);

        comboBox_DOF_auto_focus_mode = new MyComboBox(groupCheck_DOF_enabled);
        comboBox_DOF_auto_focus_mode->addItem(QString());
        comboBox_DOF_auto_focus_mode->addItem(QString());
        comboBox_DOF_auto_focus_mode->addItem(QString());
        comboBox_DOF_auto_focus_mode->addItem(QString());
        comboBox_DOF_auto_focus_mode->setObjectName(QString::fromUtf8("comboBox_DOF_auto_focus_mode"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox_DOF_auto_focus_mode->sizePolicy().hasHeightForWidth());
        comboBox_DOF_auto_focus_mode->setSizePolicy(sizePolicy1);

        gridLayout_35->addWidget(comboBox_DOF_auto_focus_mode, 6, 1, 1, 1);

        label_dof_blur_kernel = new QLabel(groupCheck_DOF_enabled);
        label_dof_blur_kernel->setObjectName(QString::fromUtf8("label_dof_blur_kernel"));

        gridLayout_35->addWidget(label_dof_blur_kernel, 7, 0, 1, 1);

        comboBox_DOF_blur_kernel = new MyComboBox(groupCheck_DOF_enabled);
        comboBox_DOF_blur_kernel->addItem(QString());
        comboBox_DOF_blur_kernel->addItem(QString());
        comboBox_DOF_blur_kernel->addItem(QString());
        comboBox_DOF_blur_kernel->addItem(QString());
        comboBox_DOF_blur_kernel->addItem(QString());
        comboBox_DOF_blur_kernel->addItem(QString());
        comboBox_DOF_blur_kernel->setObjectName(QString::fromUtf8("comboBox_DOF_blur_kernel"));
        sizePolicy1.setHeightForWidth(comboBox_DOF_blur_kernel->sizePolicy().hasHeightForWidth());
        comboBox_DOF_blur_kernel->setSizePolicy(sizePolicy1);

        gridLayout_35->addWidget(comboBox_DOF_blur_kernel, 7, 1, 1, 1);

        label_auto_dof_focus_bias = new QLabel(groupCheck_DOF_enabled);
        label_auto_dof_focus_bias->setObjectName(QString::fromUtf8("label_auto_dof_focus_bias"));

        gridLayout_35->addWidget(label_auto_dof_focus_bias, 8, 0, 1, 1);

        spinbox_auto_dof_focus_bias = new MyDoubleSpinBox(groupCheck_DOF_enabled);
        spinbox_auto_dof_focus_bias->setObjectName(QString::fromUtf8("spinbox_auto_dof_focus_bias"));
        sizePolicy.setHeightForWidth(spinbox_auto_dof_focus_bias->sizePolicy().hasHeightForWidth());
        spinbox_auto_dof_focus_bias->setSizePolicy(sizePolicy);
        spinbox_auto_dof_focus_bias->setDecimals(1);
        spinbox_auto_dof_focus_bias->setMinimum(-100.000000000000000);
        spinbox_auto_dof_focus_bias->setMaximum(100.000000000000000);
        spinbox_auto_dof_focus_bias->setSingleStep(5.000000000000000);

        gridLayout_35->addWidget(spinbox_auto_dof_focus_bias, 8, 1, 1, 1);

        label_auto_dof_radius_scale = new QLabel(groupCheck_DOF_enabled);
        label_auto_dof_radius_scale->setObjectName(QString::fromUtf8("label_auto_dof_radius_scale"));

        gridLayout_35->addWidget(label_auto_dof_radius_scale, 9, 0, 1, 1);

        spinbox_auto_dof_radius_scale = new MyDoubleSpinBox(groupCheck_DOF_enabled);
        spinbox_auto_dof_radius_scale->setObjectName(QString::fromUtf8("spinbox_auto_dof_radius_scale"));
        sizePolicy.setHeightForWidth(spinbox_auto_dof_radius_scale->sizePolicy().hasHeightForWidth());
        spinbox_auto_dof_radius_scale->setSizePolicy(sizePolicy);
        spinbox_auto_dof_radius_scale->setDecimals(2);
        spinbox_auto_dof_radius_scale->setMinimum(0.100000000000000);
        spinbox_auto_dof_radius_scale->setMaximum(5.000000000000000);
        spinbox_auto_dof_radius_scale->setSingleStep(0.100000000000000);
        spinbox_auto_dof_radius_scale->setValue(1.000000000000000);

        gridLayout_35->addWidget(spinbox_auto_dof_radius_scale, 9, 1, 1, 1);

        label_auto_dof_max_radius_scale = new QLabel(groupCheck_DOF_enabled);
        label_auto_dof_max_radius_scale->setObjectName(QString::fromUtf8("label_auto_dof_max_radius_scale"));

        gridLayout_35->addWidget(label_auto_dof_max_radius_scale, 10, 0, 1, 1);

        spinbox_auto_dof_max_radius_scale = new MyDoubleSpinBox(groupCheck_DOF_enabled);
        spinbox_auto_dof_max_radius_scale->setObjectName(QString::fromUtf8("spinbox_auto_dof_max_radius_scale"));
        sizePolicy.setHeightForWidth(spinbox_auto_dof_max_radius_scale->sizePolicy().hasHeightForWidth());
        spinbox_auto_dof_max_radius_scale->setSizePolicy(sizePolicy);
        spinbox_auto_dof_max_radius_scale->setDecimals(2);
        spinbox_auto_dof_max_radius_scale->setMinimum(0.100000000000000);
        spinbox_auto_dof_max_radius_scale->setMaximum(5.000000000000000);
        spinbox_auto_dof_max_radius_scale->setSingleStep(0.100000000000000);
        spinbox_auto_dof_max_radius_scale->setValue(1.000000000000000);

        gridLayout_35->addWidget(spinbox_auto_dof_max_radius_scale, 10, 1, 1, 1);

        label_auto_dof_blur_opacity_scale = new QLabel(groupCheck_DOF_enabled);
        label_auto_dof_blur_opacity_scale->setObjectName(QString::fromUtf8("label_auto_dof_blur_opacity_scale"));

        gridLayout_35->addWidget(label_auto_dof_blur_opacity_scale, 11, 0, 1, 1);

        spinbox_auto_dof_blur_opacity_scale = new MyDoubleSpinBox(groupCheck_DOF_enabled);
        spinbox_auto_dof_blur_opacity_scale->setObjectName(QString::fromUtf8("spinbox_auto_dof_blur_opacity_scale"));
        sizePolicy.setHeightForWidth(spinbox_auto_dof_blur_opacity_scale->sizePolicy().hasHeightForWidth());
        spinbox_auto_dof_blur_opacity_scale->setSizePolicy(sizePolicy);
        spinbox_auto_dof_blur_opacity_scale->setDecimals(2);
        spinbox_auto_dof_blur_opacity_scale->setMinimum(0.100000000000000);
        spinbox_auto_dof_blur_opacity_scale->setMaximum(5.000000000000000);
        spinbox_auto_dof_blur_opacity_scale->setSingleStep(0.100000000000000);
        spinbox_auto_dof_blur_opacity_scale->setValue(1.000000000000000);

        gridLayout_35->addWidget(spinbox_auto_dof_blur_opacity_scale, 11, 1, 1, 1);


        verticalLayout_73->addLayout(gridLayout_35);

        pushButton_DOF_update = new QPushButton(groupCheck_DOF_enabled);
        pushButton_DOF_update->setObjectName(QString::fromUtf8("pushButton_DOF_update"));
        sizePolicy.setHeightForWidth(pushButton_DOF_update->sizePolicy().hasHeightForWidth());
        pushButton_DOF_update->setSizePolicy(sizePolicy);

        verticalLayout_73->addWidget(pushButton_DOF_update);

        pushButton_DOF_set_focus = new QPushButton(groupCheck_DOF_enabled);
        pushButton_DOF_set_focus->setObjectName(QString::fromUtf8("pushButton_DOF_set_focus"));
        sizePolicy.setHeightForWidth(pushButton_DOF_set_focus->sizePolicy().hasHeightForWidth());
        pushButton_DOF_set_focus->setSizePolicy(sizePolicy);

        verticalLayout_73->addWidget(pushButton_DOF_set_focus);


        verticalLayout_34->addWidget(groupCheck_DOF_enabled);

        groupCheck_DOF_monte_carlo = new MyGroupBox(scrollAreaWidgetContents_8);
        groupCheck_DOF_monte_carlo->setObjectName(QString::fromUtf8("groupCheck_DOF_monte_carlo"));
        groupCheck_DOF_monte_carlo->setCheckable(true);
        verticalLayout_152 = new QVBoxLayout(groupCheck_DOF_monte_carlo);
        verticalLayout_152->setSpacing(2);
        verticalLayout_152->setObjectName(QString::fromUtf8("verticalLayout_152"));
        verticalLayout_152->setContentsMargins(2, 2, 2, 2);
        gridLayout_97 = new QGridLayout();
        gridLayout_97->setSpacing(2);
        gridLayout_97->setObjectName(QString::fromUtf8("gridLayout_97"));
        label_358 = new QLabel(groupCheck_DOF_monte_carlo);
        label_358->setObjectName(QString::fromUtf8("label_358"));

        gridLayout_97->addWidget(label_358, 0, 0, 1, 1);

        label_359 = new QLabel(groupCheck_DOF_monte_carlo);
        label_359->setObjectName(QString::fromUtf8("label_359"));

        gridLayout_97->addWidget(label_359, 1, 0, 1, 1);

        label_average_DOF_samples = new QLabel(groupCheck_DOF_monte_carlo);
        label_average_DOF_samples->setObjectName(QString::fromUtf8("label_average_DOF_samples"));

        gridLayout_97->addWidget(label_average_DOF_samples, 3, 0, 1, 2);

        logedit_DOF_max_noise = new MyLineEdit(groupCheck_DOF_monte_carlo);
        logedit_DOF_max_noise->setObjectName(QString::fromUtf8("logedit_DOF_max_noise"));

        gridLayout_97->addWidget(logedit_DOF_max_noise, 2, 1, 1, 1);

        label_average_DOF_noise = new QLabel(groupCheck_DOF_monte_carlo);
        label_average_DOF_noise->setObjectName(QString::fromUtf8("label_average_DOF_noise"));

        gridLayout_97->addWidget(label_average_DOF_noise, 4, 0, 1, 2);

        spinboxInt_DOF_min_samples = new MySpinBox(groupCheck_DOF_monte_carlo);
        spinboxInt_DOF_min_samples->setObjectName(QString::fromUtf8("spinboxInt_DOF_min_samples"));
        sizePolicy.setHeightForWidth(spinboxInt_DOF_min_samples->sizePolicy().hasHeightForWidth());
        spinboxInt_DOF_min_samples->setSizePolicy(sizePolicy);
        spinboxInt_DOF_min_samples->setMaximum(10000);

        gridLayout_97->addWidget(spinboxInt_DOF_min_samples, 1, 1, 1, 1);

        label_360 = new QLabel(groupCheck_DOF_monte_carlo);
        label_360->setObjectName(QString::fromUtf8("label_360"));

        gridLayout_97->addWidget(label_360, 2, 0, 1, 1);

        spinboxInt_DOF_samples = new MySpinBox(groupCheck_DOF_monte_carlo);
        spinboxInt_DOF_samples->setObjectName(QString::fromUtf8("spinboxInt_DOF_samples"));
        sizePolicy.setHeightForWidth(spinboxInt_DOF_samples->sizePolicy().hasHeightForWidth());
        spinboxInt_DOF_samples->setSizePolicy(sizePolicy);
        spinboxInt_DOF_samples->setMaximum(10000);

        gridLayout_97->addWidget(spinboxInt_DOF_samples, 0, 1, 1, 1);

        label_masked_pixels = new QLabel(groupCheck_DOF_monte_carlo);
        label_masked_pixels->setObjectName(QString::fromUtf8("label_masked_pixels"));

        gridLayout_97->addWidget(label_masked_pixels, 5, 0, 1, 2);

        label_tiles_done = new QLabel(groupCheck_DOF_monte_carlo);
        label_tiles_done->setObjectName(QString::fromUtf8("label_tiles_done"));

        gridLayout_97->addWidget(label_tiles_done, 6, 0, 1, 2);


        verticalLayout_152->addLayout(gridLayout_97);

        checkBox_MC_pixel_level_optimization = new MyCheckBox(groupCheck_DOF_monte_carlo);
        checkBox_MC_pixel_level_optimization->setObjectName(QString::fromUtf8("checkBox_MC_pixel_level_optimization"));
        sizePolicy.setHeightForWidth(checkBox_MC_pixel_level_optimization->sizePolicy().hasHeightForWidth());
        checkBox_MC_pixel_level_optimization->setSizePolicy(sizePolicy);

        verticalLayout_152->addWidget(checkBox_MC_pixel_level_optimization);

        horizontalLayout_progressive_adaptive_threshold = new QHBoxLayout();
        horizontalLayout_progressive_adaptive_threshold->setSpacing(4);
        horizontalLayout_progressive_adaptive_threshold->setObjectName(QString::fromUtf8("horizontalLayout_progressive_adaptive_threshold"));
        label_progressive_adaptive_threshold = new QLabel(groupCheck_DOF_monte_carlo);
        label_progressive_adaptive_threshold->setObjectName(QString::fromUtf8("label_progressive_adaptive_threshold"));

        horizontalLayout_progressive_adaptive_threshold->addWidget(label_progressive_adaptive_threshold);

        slider_progressive_adaptive_threshold = new QSlider(groupCheck_DOF_monte_carlo);
        slider_progressive_adaptive_threshold->setObjectName(QString::fromUtf8("slider_progressive_adaptive_threshold"));
        slider_progressive_adaptive_threshold->setMinimum(1);
        slider_progressive_adaptive_threshold->setMaximum(1000);
        slider_progressive_adaptive_threshold->setValue(50);
        slider_progressive_adaptive_threshold->setOrientation(Qt::Horizontal);

        horizontalLayout_progressive_adaptive_threshold->addWidget(slider_progressive_adaptive_threshold);

        spinbox_progressive_adaptive_threshold = new MyDoubleSpinBox(groupCheck_DOF_monte_carlo);
        spinbox_progressive_adaptive_threshold->setObjectName(QString::fromUtf8("spinbox_progressive_adaptive_threshold"));
        spinbox_progressive_adaptive_threshold->setDecimals(3);
        spinbox_progressive_adaptive_threshold->setMinimum(0.001000000000000);
        spinbox_progressive_adaptive_threshold->setMaximum(1.000000000000000);
        spinbox_progressive_adaptive_threshold->setSingleStep(0.010000000000000);
        spinbox_progressive_adaptive_threshold->setValue(0.050000000000000);

        horizontalLayout_progressive_adaptive_threshold->addWidget(spinbox_progressive_adaptive_threshold);


        verticalLayout_152->addLayout(horizontalLayout_progressive_adaptive_threshold);

        checkB_MCShowNoiseLevels = new QCheckBox(groupCheck_DOF_monte_carlo);
        checkB_MCShowNoiseLevels->setObjectName(QString::fromUtf8("checkB_MCShowNoiseLevels"));
        checkB_MCShowNoiseLevels->setEnabled(true);
        checkB_MCShowNoiseLevels->setChecked(false);

        verticalLayout_152->addWidget(checkB_MCShowNoiseLevels);

        groupCheck_MC_denoiser_enable = new MyGroupBox(groupCheck_DOF_monte_carlo);
        groupCheck_MC_denoiser_enable->setObjectName(QString::fromUtf8("groupCheck_MC_denoiser_enable"));
        groupCheck_MC_denoiser_enable->setCheckable(true);
        gridLayout_4 = new QGridLayout(groupCheck_MC_denoiser_enable);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(2, 2, 2, 2);
        comboBox_MC_denoiser_strength = new MyComboBox(groupCheck_MC_denoiser_enable);
        comboBox_MC_denoiser_strength->addItem(QString());
        comboBox_MC_denoiser_strength->addItem(QString());
        comboBox_MC_denoiser_strength->addItem(QString());
        comboBox_MC_denoiser_strength->addItem(QString());
        comboBox_MC_denoiser_strength->setObjectName(QString::fromUtf8("comboBox_MC_denoiser_strength"));
        sizePolicy1.setHeightForWidth(comboBox_MC_denoiser_strength->sizePolicy().hasHeightForWidth());
        comboBox_MC_denoiser_strength->setSizePolicy(sizePolicy1);

        gridLayout_4->addWidget(comboBox_MC_denoiser_strength, 0, 1, 1, 1);

        label_6 = new QLabel(groupCheck_MC_denoiser_enable);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_4->addWidget(label_6, 0, 0, 1, 1);

        checkBox_MC_denoiser_preserve_geometry = new MyCheckBox(groupCheck_MC_denoiser_enable);
        checkBox_MC_denoiser_preserve_geometry->setObjectName(QString::fromUtf8("checkBox_MC_denoiser_preserve_geometry"));
        sizePolicy.setHeightForWidth(checkBox_MC_denoiser_preserve_geometry->sizePolicy().hasHeightForWidth());
        checkBox_MC_denoiser_preserve_geometry->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(checkBox_MC_denoiser_preserve_geometry, 1, 0, 1, 2);

        gridLayout_4->setColumnStretch(1, 1);

        verticalLayout_152->addWidget(groupCheck_MC_denoiser_enable);

        checkBox_DOF_MC_global_illumination = new MyCheckBox(groupCheck_DOF_monte_carlo);
        checkBox_DOF_MC_global_illumination->setObjectName(QString::fromUtf8("checkBox_DOF_MC_global_illumination"));
        sizePolicy.setHeightForWidth(checkBox_DOF_MC_global_illumination->sizePolicy().hasHeightForWidth());
        checkBox_DOF_MC_global_illumination->setSizePolicy(sizePolicy);

        verticalLayout_152->addWidget(checkBox_DOF_MC_global_illumination);

        gridLayout_18 = new QGridLayout();
        gridLayout_18->setSpacing(2);
        gridLayout_18->setObjectName(QString::fromUtf8("gridLayout_18"));
        logedit_MC_GI_radiance_limit = new MyLineEdit(groupCheck_DOF_monte_carlo);
        logedit_MC_GI_radiance_limit->setObjectName(QString::fromUtf8("logedit_MC_GI_radiance_limit"));

        gridLayout_18->addWidget(logedit_MC_GI_radiance_limit, 0, 1, 1, 1);

        label_361 = new QLabel(groupCheck_DOF_monte_carlo);
        label_361->setObjectName(QString::fromUtf8("label_361"));

        gridLayout_18->addWidget(label_361, 0, 0, 1, 1);


        verticalLayout_152->addLayout(gridLayout_18);

        checkBox_MC_GI_use_reflectance = new MyCheckBox(groupCheck_DOF_monte_carlo);
        checkBox_MC_GI_use_reflectance->setObjectName(QString::fromUtf8("checkBox_MC_GI_use_reflectance"));
        sizePolicy.setHeightForWidth(checkBox_MC_GI_use_reflectance->sizePolicy().hasHeightForWidth());
        checkBox_MC_GI_use_reflectance->setSizePolicy(sizePolicy);

        verticalLayout_152->addWidget(checkBox_MC_GI_use_reflectance);

        checkBox_MC_global_illumination_volumetric = new MyCheckBox(groupCheck_DOF_monte_carlo);
        checkBox_MC_global_illumination_volumetric->setObjectName(QString::fromUtf8("checkBox_MC_global_illumination_volumetric"));
        checkBox_MC_global_illumination_volumetric->setEnabled(false);
        sizePolicy.setHeightForWidth(checkBox_MC_global_illumination_volumetric->sizePolicy().hasHeightForWidth());
        checkBox_MC_global_illumination_volumetric->setSizePolicy(sizePolicy);

        verticalLayout_152->addWidget(checkBox_MC_global_illumination_volumetric);

        checkBox_MC_fog_illumination = new MyCheckBox(groupCheck_DOF_monte_carlo);
        checkBox_MC_fog_illumination->setObjectName(QString::fromUtf8("checkBox_MC_fog_illumination"));
        checkBox_MC_fog_illumination->setEnabled(false);
        sizePolicy.setHeightForWidth(checkBox_MC_fog_illumination->sizePolicy().hasHeightForWidth());
        checkBox_MC_fog_illumination->setSizePolicy(sizePolicy);

        verticalLayout_152->addWidget(checkBox_MC_fog_illumination);

        checkBox_MC_soft_shadows_enable = new MyCheckBox(groupCheck_DOF_monte_carlo);
        checkBox_MC_soft_shadows_enable->setObjectName(QString::fromUtf8("checkBox_MC_soft_shadows_enable"));
        sizePolicy.setHeightForWidth(checkBox_MC_soft_shadows_enable->sizePolicy().hasHeightForWidth());
        checkBox_MC_soft_shadows_enable->setSizePolicy(sizePolicy);

        verticalLayout_152->addWidget(checkBox_MC_soft_shadows_enable);

        groupCheck_DOF_MC_CA_enable = new MyGroupBox(groupCheck_DOF_monte_carlo);
        groupCheck_DOF_MC_CA_enable->setObjectName(QString::fromUtf8("groupCheck_DOF_MC_CA_enable"));
        groupCheck_DOF_MC_CA_enable->setCheckable(true);
        verticalLayout_75 = new QVBoxLayout(groupCheck_DOF_MC_CA_enable);
        verticalLayout_75->setSpacing(2);
        verticalLayout_75->setObjectName(QString::fromUtf8("verticalLayout_75"));
        verticalLayout_75->setContentsMargins(2, 2, 2, 2);
        gridLayout_11 = new QGridLayout();
        gridLayout_11->setSpacing(2);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        logedit_DOF_MC_CA_dispersion_gain = new MyLineEdit(groupCheck_DOF_MC_CA_enable);
        logedit_DOF_MC_CA_dispersion_gain->setObjectName(QString::fromUtf8("logedit_DOF_MC_CA_dispersion_gain"));

        gridLayout_11->addWidget(logedit_DOF_MC_CA_dispersion_gain, 0, 1, 1, 1);

        label_69 = new QLabel(groupCheck_DOF_MC_CA_enable);
        label_69->setObjectName(QString::fromUtf8("label_69"));
        label_69->setWordWrap(true);

        gridLayout_11->addWidget(label_69, 0, 0, 1, 1);

        label_70 = new QLabel(groupCheck_DOF_MC_CA_enable);
        label_70->setObjectName(QString::fromUtf8("label_70"));
        label_70->setWordWrap(true);

        gridLayout_11->addWidget(label_70, 1, 0, 1, 1);

        logedit_DOF_MC_CA_camera_dispersion = new MyLineEdit(groupCheck_DOF_MC_CA_enable);
        logedit_DOF_MC_CA_camera_dispersion->setObjectName(QString::fromUtf8("logedit_DOF_MC_CA_camera_dispersion"));

        gridLayout_11->addWidget(logedit_DOF_MC_CA_camera_dispersion, 1, 1, 1, 1);


        verticalLayout_75->addLayout(gridLayout_11);


        verticalLayout_152->addWidget(groupCheck_DOF_MC_CA_enable);


        verticalLayout_34->addWidget(groupCheck_DOF_monte_carlo);

        groupCheck_ambient_occlusion_enabled = new MyGroupBox(scrollAreaWidgetContents_8);
        groupCheck_ambient_occlusion_enabled->setObjectName(QString::fromUtf8("groupCheck_ambient_occlusion_enabled"));
        groupCheck_ambient_occlusion_enabled->setCheckable(true);
        verticalLayout_69 = new QVBoxLayout(groupCheck_ambient_occlusion_enabled);
        verticalLayout_69->setSpacing(2);
        verticalLayout_69->setObjectName(QString::fromUtf8("verticalLayout_69"));
        verticalLayout_69->setContentsMargins(2, 2, 2, 2);
        gridLayout_33 = new QGridLayout();
        gridLayout_33->setSpacing(2);
        gridLayout_33->setObjectName(QString::fromUtf8("gridLayout_33"));
        label_103 = new QLabel(groupCheck_ambient_occlusion_enabled);
        label_103->setObjectName(QString::fromUtf8("label_103"));

        gridLayout_33->addWidget(label_103, 2, 0, 1, 1);

        label_127 = new QLabel(groupCheck_ambient_occlusion_enabled);
        label_127->setObjectName(QString::fromUtf8("label_127"));

        gridLayout_33->addWidget(label_127, 4, 0, 1, 1);

        spinboxInt_ambient_occlusion_quality = new MySpinBox(groupCheck_ambient_occlusion_enabled);
        spinboxInt_ambient_occlusion_quality->setObjectName(QString::fromUtf8("spinboxInt_ambient_occlusion_quality"));
        sizePolicy.setHeightForWidth(spinboxInt_ambient_occlusion_quality->sizePolicy().hasHeightForWidth());
        spinboxInt_ambient_occlusion_quality->setSizePolicy(sizePolicy);
        spinboxInt_ambient_occlusion_quality->setMaximum(30);

        gridLayout_33->addWidget(spinboxInt_ambient_occlusion_quality, 2, 2, 1, 1);

        spinbox_ambient_occlusion_fast_tune = new MyDoubleSpinBox(groupCheck_ambient_occlusion_enabled);
        spinbox_ambient_occlusion_fast_tune->setObjectName(QString::fromUtf8("spinbox_ambient_occlusion_fast_tune"));
        sizePolicy.setHeightForWidth(spinbox_ambient_occlusion_fast_tune->sizePolicy().hasHeightForWidth());
        spinbox_ambient_occlusion_fast_tune->setSizePolicy(sizePolicy);
        spinbox_ambient_occlusion_fast_tune->setDecimals(2);
        spinbox_ambient_occlusion_fast_tune->setMinimum(0.010000000000000);
        spinbox_ambient_occlusion_fast_tune->setMaximum(10.000000000000000);
        spinbox_ambient_occlusion_fast_tune->setSingleStep(0.100000000000000);

        gridLayout_33->addWidget(spinbox_ambient_occlusion_fast_tune, 3, 2, 1, 1);

        label_132 = new QLabel(groupCheck_ambient_occlusion_enabled);
        label_132->setObjectName(QString::fromUtf8("label_132"));

        gridLayout_33->addWidget(label_132, 3, 0, 1, 1);

        label_68 = new QLabel(groupCheck_ambient_occlusion_enabled);
        label_68->setObjectName(QString::fromUtf8("label_68"));

        gridLayout_33->addWidget(label_68, 0, 0, 1, 1);

        spinbox_ambient_occlusion = new MyDoubleSpinBox(groupCheck_ambient_occlusion_enabled);
        spinbox_ambient_occlusion->setObjectName(QString::fromUtf8("spinbox_ambient_occlusion"));
        sizePolicy.setHeightForWidth(spinbox_ambient_occlusion->sizePolicy().hasHeightForWidth());
        spinbox_ambient_occlusion->setSizePolicy(sizePolicy);
        spinbox_ambient_occlusion->setDecimals(2);
        spinbox_ambient_occlusion->setMaximum(1000.000000000000000);
        spinbox_ambient_occlusion->setSingleStep(0.100000000000000);

        gridLayout_33->addWidget(spinbox_ambient_occlusion, 0, 2, 1, 1);

        comboBox_ambient_occlusion_mode = new MyComboBox(groupCheck_ambient_occlusion_enabled);
        comboBox_ambient_occlusion_mode->addItem(QString());
        comboBox_ambient_occlusion_mode->addItem(QString());
        comboBox_ambient_occlusion_mode->addItem(QString());
        comboBox_ambient_occlusion_mode->setObjectName(QString::fromUtf8("comboBox_ambient_occlusion_mode"));
        sizePolicy1.setHeightForWidth(comboBox_ambient_occlusion_mode->sizePolicy().hasHeightForWidth());
        comboBox_ambient_occlusion_mode->setSizePolicy(sizePolicy1);

        gridLayout_33->addWidget(comboBox_ambient_occlusion_mode, 4, 2, 1, 1);

        colorButton_ambient_occlusion_color = new MyColorButton(groupCheck_ambient_occlusion_enabled);
        colorButton_ambient_occlusion_color->setObjectName(QString::fromUtf8("colorButton_ambient_occlusion_color"));
        colorButton_ambient_occlusion_color->setMinimumSize(QSize(0, 0));

        gridLayout_33->addWidget(colorButton_ambient_occlusion_color, 1, 2, 1, 1);

        label_71 = new QLabel(groupCheck_ambient_occlusion_enabled);
        label_71->setObjectName(QString::fromUtf8("label_71"));

        gridLayout_33->addWidget(label_71, 1, 0, 1, 1);


        verticalLayout_69->addLayout(gridLayout_33);

        checkBox_SSAO_random_mode = new MyCheckBox(groupCheck_ambient_occlusion_enabled);
        checkBox_SSAO_random_mode->setObjectName(QString::fromUtf8("checkBox_SSAO_random_mode"));
        sizePolicy.setHeightForWidth(checkBox_SSAO_random_mode->sizePolicy().hasHeightForWidth());
        checkBox_SSAO_random_mode->setSizePolicy(sizePolicy);

        verticalLayout_69->addWidget(checkBox_SSAO_random_mode);

        frame_lightmap_texture = new QFrame(groupCheck_ambient_occlusion_enabled);
        frame_lightmap_texture->setObjectName(QString::fromUtf8("frame_lightmap_texture"));
        frame_lightmap_texture->setEnabled(false);
        frame_lightmap_texture->setFrameShape(QFrame::StyledPanel);
        frame_lightmap_texture->setFrameShadow(QFrame::Raised);
        verticalLayout_138 = new QVBoxLayout(frame_lightmap_texture);
        verticalLayout_138->setSpacing(2);
        verticalLayout_138->setObjectName(QString::fromUtf8("verticalLayout_138"));
        verticalLayout_138->setContentsMargins(2, 2, 2, 2);
        label_171 = new QLabel(frame_lightmap_texture);
        label_171->setObjectName(QString::fromUtf8("label_171"));

        verticalLayout_138->addWidget(label_171);

        gridLayout_74 = new QGridLayout();
        gridLayout_74->setSpacing(2);
        gridLayout_74->setObjectName(QString::fromUtf8("gridLayout_74"));
        text_file_lightmap = new FileSelectWidget(frame_lightmap_texture);
        text_file_lightmap->setObjectName(QString::fromUtf8("text_file_lightmap"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(text_file_lightmap->sizePolicy().hasHeightForWidth());
        text_file_lightmap->setSizePolicy(sizePolicy2);

        gridLayout_74->addWidget(text_file_lightmap, 0, 1, 1, 2);


        verticalLayout_138->addLayout(gridLayout_74);

        gridLayout_23 = new QGridLayout();
        gridLayout_23->setSpacing(2);
        gridLayout_23->setObjectName(QString::fromUtf8("gridLayout_23"));
        label_236 = new QLabel(frame_lightmap_texture);
        label_236->setObjectName(QString::fromUtf8("label_236"));
        label_236->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_23->addWidget(label_236, 1, 1, 1, 1);

        label_235 = new QLabel(frame_lightmap_texture);
        label_235->setObjectName(QString::fromUtf8("label_235"));
        label_235->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_23->addWidget(label_235, 0, 1, 1, 1);

        label_234 = new QLabel(frame_lightmap_texture);
        label_234->setObjectName(QString::fromUtf8("label_234"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_234->sizePolicy().hasHeightForWidth());
        label_234->setSizePolicy(sizePolicy3);

        gridLayout_23->addWidget(label_234, 0, 0, 3, 1);

        label_237 = new QLabel(frame_lightmap_texture);
        label_237->setObjectName(QString::fromUtf8("label_237"));
        label_237->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_23->addWidget(label_237, 2, 1, 1, 1);

        spinboxd3_ao_light_map_rotation_x = new MyDoubleSpinBox(frame_lightmap_texture);
        spinboxd3_ao_light_map_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_ao_light_map_rotation_x"));
        sizePolicy.setHeightForWidth(spinboxd3_ao_light_map_rotation_x->sizePolicy().hasHeightForWidth());
        spinboxd3_ao_light_map_rotation_x->setSizePolicy(sizePolicy);
        spinboxd3_ao_light_map_rotation_x->setAccelerated(true);
        spinboxd3_ao_light_map_rotation_x->setDecimals(2);
        spinboxd3_ao_light_map_rotation_x->setMinimum(-180.000000000000000);
        spinboxd3_ao_light_map_rotation_x->setMaximum(180.000000000000000);
        spinboxd3_ao_light_map_rotation_x->setSingleStep(1.000000000000000);

        gridLayout_23->addWidget(spinboxd3_ao_light_map_rotation_x, 0, 2, 1, 1);

        spinboxd3_ao_light_map_rotation_y = new MyDoubleSpinBox(frame_lightmap_texture);
        spinboxd3_ao_light_map_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_ao_light_map_rotation_y"));
        sizePolicy.setHeightForWidth(spinboxd3_ao_light_map_rotation_y->sizePolicy().hasHeightForWidth());
        spinboxd3_ao_light_map_rotation_y->setSizePolicy(sizePolicy);
        spinboxd3_ao_light_map_rotation_y->setAccelerated(true);
        spinboxd3_ao_light_map_rotation_y->setDecimals(2);
        spinboxd3_ao_light_map_rotation_y->setMinimum(-180.000000000000000);
        spinboxd3_ao_light_map_rotation_y->setMaximum(180.000000000000000);
        spinboxd3_ao_light_map_rotation_y->setSingleStep(1.000000000000000);

        gridLayout_23->addWidget(spinboxd3_ao_light_map_rotation_y, 1, 2, 1, 1);

        spinboxd3_ao_light_map_rotation_z = new MyDoubleSpinBox(frame_lightmap_texture);
        spinboxd3_ao_light_map_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_ao_light_map_rotation_z"));
        sizePolicy.setHeightForWidth(spinboxd3_ao_light_map_rotation_z->sizePolicy().hasHeightForWidth());
        spinboxd3_ao_light_map_rotation_z->setSizePolicy(sizePolicy);
        spinboxd3_ao_light_map_rotation_z->setAccelerated(true);
        spinboxd3_ao_light_map_rotation_z->setDecimals(2);
        spinboxd3_ao_light_map_rotation_z->setMinimum(-180.000000000000000);
        spinboxd3_ao_light_map_rotation_z->setMaximum(180.000000000000000);
        spinboxd3_ao_light_map_rotation_z->setSingleStep(1.000000000000000);

        gridLayout_23->addWidget(spinboxd3_ao_light_map_rotation_z, 2, 2, 1, 1);


        verticalLayout_138->addLayout(gridLayout_23);


        verticalLayout_69->addWidget(frame_lightmap_texture);


        verticalLayout_34->addWidget(groupCheck_ambient_occlusion_enabled);

        groupCheck_env_mapping_enable = new MyGroupBox(scrollAreaWidgetContents_8);
        groupCheck_env_mapping_enable->setObjectName(QString::fromUtf8("groupCheck_env_mapping_enable"));
        groupCheck_env_mapping_enable->setCheckable(true);
        verticalLayout_119 = new QVBoxLayout(groupCheck_env_mapping_enable);
        verticalLayout_119->setSpacing(2);
        verticalLayout_119->setObjectName(QString::fromUtf8("verticalLayout_119"));
        verticalLayout_119->setContentsMargins(2, 2, 2, 2);
        label_5 = new QLabel(groupCheck_env_mapping_enable);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setWordWrap(true);

        verticalLayout_119->addWidget(label_5);

        gridLayout_73 = new QGridLayout();
        gridLayout_73->setSpacing(2);
        gridLayout_73->setObjectName(QString::fromUtf8("gridLayout_73"));
        label_170 = new QLabel(groupCheck_env_mapping_enable);
        label_170->setObjectName(QString::fromUtf8("label_170"));

        gridLayout_73->addWidget(label_170, 0, 0, 1, 1);

        text_file_envmap = new FileSelectWidget(groupCheck_env_mapping_enable);
        text_file_envmap->setObjectName(QString::fromUtf8("text_file_envmap"));
        sizePolicy2.setHeightForWidth(text_file_envmap->sizePolicy().hasHeightForWidth());
        text_file_envmap->setSizePolicy(sizePolicy2);

        gridLayout_73->addWidget(text_file_envmap, 0, 1, 1, 2);


        verticalLayout_119->addLayout(gridLayout_73);


        verticalLayout_34->addWidget(groupCheck_env_mapping_enable);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_34->addItem(verticalSpacer_2);

        scrollArea_7->setWidget(scrollAreaWidgetContents_8);

        verticalLayout_64->addWidget(scrollArea_7);


        retranslateUi(cEffectsRaytracingTab);

        QMetaObject::connectSlotsByName(cEffectsRaytracingTab);
    } // setupUi

    void retranslateUi(QWidget *cEffectsRaytracingTab)
    {
        pushButton_local_load_2->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Laden", nullptr));
        pushButton_local_save_2->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Opslaan", nullptr));
        pushButton_local_reset_2->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Reset", nullptr));
        pushButton_local_randomize_2->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Randomize", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_raytraced_reflections->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Activate calculation of ray-traced reflections and transparency. Reflectance can be set by <span style=\" font-style:italic;\">Material/Reflection. </span>Transparency settings are in the same tab as reflection.<br/>Also enable with Monte Carlo global illumination.</p><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_raytraced_reflections->setTitle(QCoreApplication::translate("cEffectsRaytracingTab", "Ray-&traced reflections and transparency", nullptr));
#if QT_CONFIG(tooltip)
        spinboxInt_reflections_max->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Maximum number of ray bounces which are calculated for a given pixel.</p><p>This value affects reflections, refraction and MC Global Illumination </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_62->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Reflections depth:", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_DOF_enabled->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Depth of field is the effect in which objects within some range of distances in a scene appear in focus, and objects nearer or farther than this range appear out of focus.</p><p>note: using DOF prevents one-pass anaglyph rendering, unless Monte carlo algorithm mode is selected.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_DOF_enabled->setTitle(QCoreApplication::translate("cEffectsRaytracingTab", "Depth of field", nullptr));
        label_131->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Focus distance:", nullptr));
        label_136->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Radius:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_DOF_focus->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>It's the distance where objects appear in focus.</p><p>Distance can be set bu using button <span style=\" font-style:italic;\">Set focus distance by mouse</span></p><p><br/></p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>low focus distance</p></td><td><p>high focus distance</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/image - DOF - focus close.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - DOF - focus far.jpg\"/></p></td></tr></table></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinbox_DOF_radius->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Intensity of DOF effect (average radius of blur)</p><p><br/></p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>radius = 10</p></td><td><p>radius = 50</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/image - DOF - radius 10.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - DOF - radius 50.jpg\"/></p></td></tr></table></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_DOF_radius->setPrefix(QString());
        spinbox_DOF_radius->setSuffix(QString());
        label_349->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Number of passes:", nullptr));
#if QT_CONFIG(tooltip)
        spinboxInt_DOF_number_of_passes->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Number of passes of rendering DOF effect. One pass is enough for most of cases. But for more realistic blur it can be increased (e.g to 4) and blur opacity should be accordingly decreased (e.g. to 1.0)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_350->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Blur opacity:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_DOF_blur_opacity->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Opacity of blur effect used during second phase of rendering the DOF effect. 4.0 is correct for most of cases. But for more realistic blur the number of passes can be increased (e.g to 4) and blur opacity should be accordingly decreased (e.g. to 1.0)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_DOF_blur_opacity->setPrefix(QString());
        spinbox_DOF_blur_opacity->setSuffix(QString());
        label_138->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Maximum blur radius:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_DOF_max_radius->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Maximum radius of generated blur. Lower value can speed up rendering but effect will be less realistic.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_DOF_max_radius->setPrefix(QString());
        spinbox_DOF_max_radius->setSuffix(QString());
        label_dof_autofocus->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Auto focus:", nullptr));
        checkBox_DOF_auto_focus->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Enable auto focus", nullptr));
        label_dof_autofocus_mode->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Auto focus mode:", nullptr));
        comboBox_DOF_auto_focus_mode->setItemText(0, QCoreApplication::translate("cEffectsRaytracingTab", "Mediaan depth", nullptr));
        comboBox_DOF_auto_focus_mode->setItemText(1, QCoreApplication::translate("cEffectsRaytracingTab", "Gemiddelde depth", nullptr));
        comboBox_DOF_auto_focus_mode->setItemText(2, QCoreApplication::translate("cEffectsRaytracingTab", "Histogram piek", nullptr));
        comboBox_DOF_auto_focus_mode->setItemText(3, QCoreApplication::translate("cEffectsRaytracingTab", "Dichtste object", nullptr));

        label_dof_blur_kernel->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Blur type:", nullptr));
        comboBox_DOF_blur_kernel->setItemText(0, QCoreApplication::translate("cEffectsRaytracingTab", "Lens", nullptr));
        comboBox_DOF_blur_kernel->setItemText(1, QCoreApplication::translate("cEffectsRaytracingTab", "Verticaal", nullptr));
        comboBox_DOF_blur_kernel->setItemText(2, QCoreApplication::translate("cEffectsRaytracingTab", "Horizontaal", nullptr));
        comboBox_DOF_blur_kernel->setItemText(3, QCoreApplication::translate("cEffectsRaytracingTab", "Motion", nullptr));
        comboBox_DOF_blur_kernel->setItemText(4, QCoreApplication::translate("cEffectsRaytracingTab", "Gauss", nullptr));
        comboBox_DOF_blur_kernel->setItemText(5, QCoreApplication::translate("cEffectsRaytracingTab", "Radiaal", nullptr));

        label_auto_dof_focus_bias->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Focus bias (%):", nullptr));
#if QT_CONFIG(tooltip)
        label_auto_dof_focus_bias->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Adjusts auto-focus distance. Negative = closer, positive = farther.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_auto_dof_radius_scale->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Auto radius scale:", nullptr));
#if QT_CONFIG(tooltip)
        label_auto_dof_radius_scale->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Multiplier for auto-computed blur radius. Higher = more blur.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_auto_dof_max_radius_scale->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Auto max radius scale:", nullptr));
        label_auto_dof_blur_opacity_scale->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Auto blur opacity scale:", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_DOF_update->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Update image after changes of DOF settings. Can be updated even after image rendering.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_DOF_update->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Update image", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_DOF_set_focus->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Auto-focus: analyze z-buffer and set optimal focus distance at image center.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_DOF_set_focus->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Auto-focus (center)", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_DOF_monte_carlo->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Enables Monte Carlo algorithms for rendering the depth of field (DOF), global illumination, ambient occlusion (with multiple rays) and soft shadows effects. This mode is extremely slow for rendering, but gives a very realistic appearance of effects.</p><p>In addition Monte Carlo algorithm provides high quality adaptive anti-aliasing.</p><p>Every pixed (or tile) of the image is rendered multiple times with randomly changed parameters. Every repeat reduces noise. Sampling of each pixel (or tile) is stopped when noise is reduced to defined level (defined by &quot;Max noise level&quot; parameter&quot;) or when maximum number of repeats is reached (defined by &quot;Max number of samples&quot;). </p><p>Remark: This effect cannot work properly when screen space ambient occlusion is enabled. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_DOF_monte_carlo->setTitle(QCoreApplication::translate("cEffectsRaytracingTab", "&Monte Carlo algorithm", nullptr));
        label_358->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Max number of samples\n"
"per pixel:", nullptr));
        label_359->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Min number of samples\n"
"per pixel:", nullptr));
#if QT_CONFIG(tooltip)
        label_average_DOF_samples->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Average number of MC samples that have been calculated  for each image pixel.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_average_DOF_samples->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Average number of MC samples:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_DOF_max_noise->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Limit of noise level for each image pixel. Every pixel is calculated multiple times until estimated noise reaches maximum noise level percentage.</p><p>A lower value reduces visible noise on the final image, but increases rendering time. Decreasing the maximum noise level by half, increases the rendering time by 4.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        label_average_DOF_noise->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Estimated average noise caused by Monte Carlo effects.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_average_DOF_noise->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Average noise:", nullptr));
#if QT_CONFIG(tooltip)
        spinboxInt_DOF_min_samples->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Minimum number of MC samples calculated for each image pixel. Increasing this parameter can reduce visible noise, ( by improving calculation of noise level estimation).</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_360->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Max noise level\n"
"(percentage)", nullptr));
#if QT_CONFIG(tooltip)
        spinboxInt_DOF_samples->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Number of MC samples calculated for each image pixel. Higher values reduce the noise on the image but increase the rendering time. </p><p>For instance if the number of samples is 100, then the rendering will take 100 times longer compared to the effect disabled.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        label_masked_pixels->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Estimated average noise caused by Monte Carlo effects.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_masked_pixels->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Masked pixels:", nullptr));
#if QT_CONFIG(tooltip)
        label_tiles_done->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Estimated average noise caused by Monte Carlo effects.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_tiles_done->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Tiles done:", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_MC_pixel_level_optimization->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Enables additonal optimization of MC rendering. The noise level is calculated separatelly for each pixel. If noise level is enough low, then the pixel is no longer calculated.</p><p>If the image is very noisy and there is low value of <span style=\" font-style:italic;\">Min number of samples</span>, then enabling this option can cause dark random pixels left on the image.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_MC_pixel_level_optimization->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Enable pixel level optimization", nullptr));
#if QT_CONFIG(tooltip)
        label_progressive_adaptive_threshold->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "Color variance threshold for adaptive pixel subdivision during progressive / MC rendering. Lower values refine more pixels (higher quality, slower).", nullptr));
#endif // QT_CONFIG(tooltip)
        label_progressive_adaptive_threshold->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Adaptive threshold:", nullptr));
#if QT_CONFIG(tooltip)
        slider_progressive_adaptive_threshold->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "Variance threshold for adaptive sampling (0.001\342\200\2231.0).", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinbox_progressive_adaptive_threshold->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "Used when pixel level optimization or adaptive antialiasing is enabled.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkB_MCShowNoiseLevels->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Show detailed noise levels durining rendering", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_MC_denoiser_enable->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "Enable the Monte Carlo denoiser to reduce noise in rendered images. This post-processing step smooths out grainy patterns caused by limited sampling, resulting in cleaner and more visually appealing results, especially at lower sample counts.", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_MC_denoiser_enable->setTitle(QCoreApplication::translate("cEffectsRaytracingTab", "Denoiser", nullptr));
        comboBox_MC_denoiser_strength->setItemText(0, QCoreApplication::translate("cEffectsRaytracingTab", "Light", nullptr));
        comboBox_MC_denoiser_strength->setItemText(1, QCoreApplication::translate("cEffectsRaytracingTab", "Medium", nullptr));
        comboBox_MC_denoiser_strength->setItemText(2, QCoreApplication::translate("cEffectsRaytracingTab", "Strong", nullptr));
        comboBox_MC_denoiser_strength->setItemText(3, QCoreApplication::translate("cEffectsRaytracingTab", "Extreme", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_MC_denoiser_strength->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Sets the strength of the Monte Carlo denoiser for noise reduction in rendered images:</p><p>Light: Minimal denoising with the smallest blur radius. Preserves the most detail but leaves some noise.</p><p>Medium: Balanced setting with moderate blur. Reduces noise while retaining most image details.</p><p>Strong: Aggressive denoising with a larger blur radius. Produces smoother images but may blur fine details.</p><p>Extreme: Maximum denoising with the largest blur. Greatly reduces noise but can noticeably smooth out textures and edges.</p><p>Choose a strength based on your preference for image smoothness versus detail preservation.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_6->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Strength", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_MC_denoiser_preserve_geometry->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Preserve geometry and edges during denoising. </p><p>When enabled, the denoiser uses depth and surface normal information to keep object boundaries and fine details sharp, reducing unwanted blurring of shapes. </p><p>Note: In scenes with strong depth of field (DOF), enabling this option may lead to unnatural appearance near blurred edges.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_MC_denoiser_preserve_geometry->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Preserve geometry", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_DOF_MC_global_illumination->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Enables calculation of realistic global illumination using Monte Carlo algorithm. </p><p>Number of light bounces is defined by the &quot;reflections depth&quot; parameter at the top of tab.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_DOF_MC_global_illumination->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Calculate MC global illumination", nullptr));
#if QT_CONFIG(tooltip)
        logedit_MC_GI_radiance_limit->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Limit for intensity of bounced light. Lower value reduces noise caused by very bright spots on HDR background textures.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_361->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Radiance limit for GI", nullptr));
        checkBox_MC_GI_use_reflectance->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Use reflectance for GI", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_MC_global_illumination_volumetric->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Enable global illumination for volumetric effects such as fog and clouds. </p><p>When checked, indirect lighting will account for light scattering inside volumes, resulting in more realistic illumination for scenes with participating media. </p><p>This may increase rendering time.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_MC_global_illumination_volumetric->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Global illumination by volumetric effects", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_MC_fog_illumination->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Enable global illumination for volumetric fog. </p><p>When checked, indirect lighting (from global illumination) will contribute to the brightness and realism of fog and other volumetric effects, allowing light to scatter and bounce inside fog. </p><p>This results in more realistic lighting but may increase render time.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_MC_fog_illumination->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Illumination of fog", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_MC_soft_shadows_enable->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Enables calculation of realistic soft shadows using Monte Carlo algorithm.</p><p>Soft shadow cone for main light source is defined by <span style=\" font-style:italic;\">Soft shadow code angle</span> (<span style=\" font-style:italic;\">Lights</span> tab)</p><p>Soft shadow cone for auxiliary lights is defined by C<span style=\" font-style:italic;\">ustom lights options</span> / <span style=\" font-style:italic;\">Size.</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_MC_soft_shadows_enable->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Calculate MC soft shadows", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_DOF_MC_CA_enable->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Enables rendering of chromatic aberration. This effect simulates the way an actual lens refracts light slightly differently based on wavelength.</p><p>It will give a \"rainbow\" type effect that gets stronger closer to the edges of the image. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_DOF_MC_CA_enable->setTitle(QCoreApplication::translate("cEffectsRaytracingTab", "Calculate chromatic aberration", nullptr));
#if QT_CONFIG(tooltip)
        logedit_DOF_MC_CA_dispersion_gain->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Higher value makes dispersion of refracted light more vsible on transparent objects.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_69->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Dispersion gain of light refraction:", nullptr));
        label_70->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Camera lenses dispersion:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_DOF_MC_CA_camera_dispersion->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Higher value makes simulated dispersion of camera lenses more visible.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        groupCheck_ambient_occlusion_enabled->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Settings for scattered light effect</p><p>Types of ambient occlusion effect:</p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>Screen Space Ambient Occlusion (SSAO)</p></td><td><p>Multiple rays</p></td><td><p>Fast</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/image - shader - ambient occlusion 1.0.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - shader - ambient occlusion high quality.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - shader - ambient occlusion fast mode.jpg\"/></p></td></tr></table><p><br/></p><p><span style=\" font-weight:600;\">SSAO</span> - relatively fast post-effect based on z-Buffer<br/>note: using SSAO prevents one-pass anaglyph rendering</p><p><span style=\" font-weight:600;\">Multiple rays</span> - based on calculation of rays in different directions. It uses texture to create colored light map. This effect sl"
                        "ows down rendering.</p><p><span style=\" font-weight:600;\">Fast</span> - simple and fast method to calculate scattered light effect. This the least accurate effect.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_ambient_occlusion_enabled->setTitle(QCoreApplication::translate("cEffectsRaytracingTab", "Ambient occl&usion", nullptr));
        label_103->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Quality:", nullptr));
        label_127->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Type:", nullptr));
#if QT_CONFIG(tooltip)
        spinboxInt_ambient_occlusion_quality->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Quality of ambient occlusion effect. Higher quality increases rendering time.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinbox_ambient_occlusion_fast_tune->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>This parameter controls brightness of fast ambient occlusion effect.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_ambient_occlusion_fast_tune->setPrefix(QString());
        spinbox_ambient_occlusion_fast_tune->setSuffix(QString());
        label_132->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Fast AO tune:", nullptr));
        label_68->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Intensiteit:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_ambient_occlusion->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Intensity of scattered light</p><p>example of effect:</p><p><img src=\":/tooltips/tooltips_images/image - shader - ambient occlusion 1.0.jpg\"/><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_ambient_occlusion->setPrefix(QString());
        spinbox_ambient_occlusion->setSuffix(QString());
        comboBox_ambient_occlusion_mode->setItemText(0, QCoreApplication::translate("cEffectsRaytracingTab", "Fast", nullptr));
        comboBox_ambient_occlusion_mode->setItemText(1, QCoreApplication::translate("cEffectsRaytracingTab", "Multiple rays with light map", nullptr));
        comboBox_ambient_occlusion_mode->setItemText(2, QCoreApplication::translate("cEffectsRaytracingTab", "Screen space", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_ambient_occlusion_mode->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Selection of method to calculate ambient occlusion effect.<br/>Do not use SSAO method with Monte Carlo option.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        colorButton_ambient_occlusion_color->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Color of light source</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_ambient_occlusion_color->setProperty("text", QVariant(QCoreApplication::translate("cEffectsRaytracingTab", "PushButton", nullptr)));
        label_71->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Kleur:", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_SSAO_random_mode->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Enables random directions of ray vectors</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_SSAO_random_mode->setText(QCoreApplication::translate("cEffectsRaytracingTab", "SSAO random mode", nullptr));
        label_171->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Light map texture:", nullptr));
#if QT_CONFIG(tooltip)
        text_file_lightmap->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>File-path to light map image. For ambient occlusion effect based on multiple rays</p><p>To use animated textures (image sequences), replace numbers by '%' symbol. Example: If sequence of images is as showed below: <br/>texture0001.jpg<br/>texture0002.jpg<br/>etc</p><p>Then use following file name: texture%%%%.jpg<br/>This tells the program to treat this as not a single image but as a sequence of images with 4 digit index.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_236->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Beta:", nullptr));
        label_235->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Alpha:", nullptr));
        label_234->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Rotatie:", nullptr));
        label_237->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Gamma:", nullptr));
        spinboxd3_ao_light_map_rotation_x->setPrefix(QString());
        spinboxd3_ao_light_map_rotation_x->setSuffix(QString());
        spinboxd3_ao_light_map_rotation_y->setPrefix(QString());
        spinboxd3_ao_light_map_rotation_y->setSuffix(QString());
        spinboxd3_ao_light_map_rotation_z->setPrefix(QString());
        spinboxd3_ao_light_map_rotation_z->setSuffix(QString());
#if QT_CONFIG(tooltip)
        groupCheck_env_mapping_enable->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>Environment mapping is an image-based lighting technique for approximating the appearance of a reflective surface by means of a precomputed texture image. The texture is used to store the image of the distant environment surrounding the rendered object.</p><p>To adjust effect intensity use <span style=\" font-style:italic;\">reflection</span> slider</p><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_env_mapping_enable->setTitle(QCoreApplication::translate("cEffectsRaytracingTab", "Environment mappin&g", nullptr));
        label_5->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Remark: It is simple reflections mapping.\n"
"To do mapping of radiance use HDRI texture as a background texture.", nullptr));
        label_170->setText(QCoreApplication::translate("cEffectsRaytracingTab", "Texture path:", nullptr));
#if QT_CONFIG(tooltip)
        text_file_envmap->setToolTip(QCoreApplication::translate("cEffectsRaytracingTab", "<html><head/><body><p>File-path to reflection map image .</p><p>To use animated textures (image sequences), replace numbers by '%' symbol. Example: If sequence of images is as showed below: <br/>texture0001.jpg<br/>texture0002.jpg<br/>etc</p><p>Then use following file name: texture%%%%.jpg<br/>This tells the program to treat this as not a single image but as a sequence of images with 4 digit index.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        (void)cEffectsRaytracingTab;
    } // retranslateUi

};

namespace Ui {
    class cEffectsRaytracingTab: public Ui_cEffectsRaytracingTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EFFECTS_RAYTRACING_TAB_H
