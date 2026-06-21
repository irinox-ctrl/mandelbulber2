/********************************************************************************
** Form generated from reading UI file 'effects_volumetric_tab.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EFFECTS_VOLUMETRIC_TAB_H
#define UI_EFFECTS_VOLUMETRIC_TAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "buton_load_settings_from_widget.h"
#include "buton_random_settings_from_widget.h"
#include "buton_reset_settings_from_widget.h"
#include "buton_save_settings_from_widget.h"
#include "my_check_box.h"
#include "my_color_button.h"
#include "my_combo_box.h"
#include "my_double_spin_box.h"
#include "my_group_box.h"
#include "my_line_edit.h"
#include "my_spin_box.h"

QT_BEGIN_NAMESPACE

class Ui_cEffectsVolumetricTab
{
public:
    QVBoxLayout *verticalLayout_65;
    QHBoxLayout *horizontalLayout_11;
    cButtonLoadSettingsFromWidget *pushButton_local_load_3;
    cButtonSaveSettingsFromWidget *pushButton_local_save_3;
    cButtonResetSettingsFromWidget *pushButton_local_reset_3;
    cButtonRandomSettingsFromWidget *pushButton_local_randomize_3;
    QSpacerItem *horizontalSpacer_3;
    QScrollArea *scrollArea_8;
    QWidget *scrollAreaWidgetContents_9;
    QVBoxLayout *verticalLayout_35;
    QGridLayout *gridLayout_2;
    MyLineEdit *logedit_volumetric_light_DE_Factor;
    QLabel *label_custom_step_multiplier;
    MyGroupBox *groupCheck_basic_fog_enabled;
    QVBoxLayout *verticalLayout_30;
    QGridLayout *gridLayout_10;
    MyLineEdit *logedit_basic_fog_visibility;
    MyComboBox *comboBox_basic_fog_primitive;
    QLabel *label_63;
    QLabel *label_64;
    QLabel *label_72;
    MyColorButton *colorButton_basic_fog_color;
    MyCheckBox *checkBox_basic_fog_cast_shadows;
    QPushButton *pushButton_set_fog_by_mouse;
    MyGroupBox *groupCheck_glow_enabled;
    QVBoxLayout *verticalLayout_28;
    QGridLayout *gridLayout_14;
    QLabel *label_88;
    QLabel *label_89;
    MyLineEdit *logedit_glow_intensity;
    QLabel *label_87;
    MyColorButton *colorButton_glow_color_1;
    MyColorButton *colorButton_glow_color_2;
    MyGroupBox *groupCheck_volumetric_fog_enabled;
    QVBoxLayout *verticalLayout_33;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *button_calculateFog;
    QToolButton *toolButton_fog_distance_double;
    QToolButton *toolButton_fog_distance_half;
    QHBoxLayout *horizontalLayout_volumetricFogMode;
    QLabel *label_volumetric_fog_mode;
    QComboBox *comboBox_volumetric_fog_mode;
    MyCheckBox *checkBox_voxel_fog_cache_enabled;
    QHBoxLayout *horizontalLayout_voxel_fog_cache_resolution;
    QLabel *label_voxel_fog_cache_resolution;
    QSlider *sliderInt_voxel_fog_cache_resolution;
    MySpinBox *spinboxInt_voxel_fog_cache_resolution;
    QGridLayout *gridLayout_13;
    QLabel *label_75;
    MyColorButton *colorButton_fog_color_2;
    QLabel *label_100;
    MyLineEdit *logedit_volumetric_fog_density;
    QLabel *label_66;
    QLabel *label_65;
    MyLineEdit *logedit_volumetric_fog_colour_2_distance;
    QLabel *label_78;
    MyCheckBox *checkBox_distance_fog_shadows;
    MyLineEdit *logedit_volumetric_fog_colour_1_distance;
    QLabel *label_79;
    MyLineEdit *logedit_volumetric_fog_distance_factor;
    QLabel *label_67;
    MyColorButton *colorButton_fog_color_1;
    QLabel *label_76;
    QLabel *label_77;
    MyLineEdit *logedit_volumetric_fog_distance_from_surface;
    MyComboBox *comboBox_distance_fog_primitive;
    MyColorButton *colorButton_fog_color_3;
    MyGroupBox *groupCheck_iteration_fog_enable;
    QVBoxLayout *verticalLayout_27;
    QGridLayout *gridLayout_8;
    QLabel *label_86;
    MyDoubleSpinBox *spinbox_iteration_fog_opacity_trim;
    MyDoubleSpinBox *spinbox_iteration_fog_color_1_maxiter;
    QLabel *label_85;
    QLabel *label_80;
    MyDoubleSpinBox *spinbox_iteration_fog_opacity_trim_high;
    QLabel *label_101;
    QLabel *label_81;
    MyDoubleSpinBox *spinbox_iteration_fog_brightness_boost;
    MyColorButton *colorButton_iteration_fog_color_1;
    MyCheckBox *checkBox_iteration_fog_shadows;
    MyColorButton *colorButton_iteration_fog_color_2;
    MyDoubleSpinBox *spinbox_iteration_fog_color_2_maxiter;
    QLabel *label_83;
    QLabel *label_82;
    MyColorButton *colorButton_iteration_fog_color_3;
    QLabel *label_99;
    MyLineEdit *logedit_iteration_fog_opacity;
    QLabel *label_84;
    QLabel *label_74;
    MyComboBox *comboBox_iteration_fog_primitive;
    QPushButton *pushButton_autoFog_iteration;
    QHBoxLayout *horizontalLayout_autoFogScale;
    QLabel *label_autoFogOpacityScale;
    MyDoubleSpinBox *spinbox_auto_fog_opacity_scale;
    QHBoxLayout *horizontalLayout_autoFogTrimBias;
    QLabel *label_autoFogTrimBias;
    MyDoubleSpinBox *spinbox_auto_fog_trim_bias;
    QHBoxLayout *horizontalLayout_autoFogTrimHighBias;
    QLabel *label_autoFogTrimHighBias;
    MyDoubleSpinBox *spinbox_auto_fog_trim_high_bias;
    QHBoxLayout *horizontalLayout_autoFogColorSpread;
    QLabel *label_autoFogColorSpread;
    MyDoubleSpinBox *spinbox_auto_fog_color_spread;
    QHBoxLayout *horizontalLayout_autoFogBoostScale;
    QLabel *label_autoFogBoostScale;
    MyDoubleSpinBox *spinbox_auto_fog_boost_scale;
    MyGroupBox *groupCheck_clouds_enable;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_cloudsPreset;
    QLabel *label_clouds_preset;
    QComboBox *comboBox_clouds_preset;
    QPushButton *pushButton_clouds_apply_preset;
    QGridLayout *gridLayout_19;
    QLabel *label_124;
    MySpinBox *spinboxInt_clouds_noise_iterations;
    QLabel *label_110;
    MyDoubleSpinBox *spinbox_clouds_density;
    QLabel *label_114;
    MyLineEdit *logedit_clouds_period;
    QLabel *label_113;
    MySpinBox *spinboxInt_clouds_random_seed;
    MyDoubleSpinBox *spinbox_clouds_ambient_light;
    QLabel *label_144;
    MyLineEdit *logedit_clouds_lights_boost;
    MyColorButton *colorButton_clouds_color;
    QPushButton *pushButton_clouds_randomize;
    QLabel *label_112;
    QLabel *label_111;
    MyLineEdit *logedit_clouds_opacity;
    QLabel *label_143;
    MyCheckBox *checkBox_clouds_cast_shadows;
    QLabel *label_clouds_density_gamma;
    MyDoubleSpinBox *spinbox_clouds_density_gamma;
    QLabel *label_clouds_softness;
    MyDoubleSpinBox *spinbox_clouds_softness;
    MyCheckBox *checkBox_clouds_adaptive_detail;
    MyGroupBox *groupCheck_clouds_sharp_edges;
    QFormLayout *formLayout_2;
    QLabel *label_142;
    MyDoubleSpinBox *spinbox_clouds_sharpness;
    QGridLayout *gridLayout_6;
    MyLineEdit *vect3_clouds_speed_y;
    QLabel *label_140;
    QLabel *label_141;
    MyLineEdit *vect3_clouds_speed_x;
    QLabel *label_135;
    MyLineEdit *vect3_clouds_speed_z;
    QLabel *label_133;
    QGridLayout *gridLayout_12;
    QLabel *label_145;
    MyComboBox *comboBox_clouds_primitive;
    MyGroupBox *groupCheck_clouds_plane_shape;
    QVBoxLayout *verticalLayout_7;
    QGridLayout *gridLayout_20;
    QLabel *label_121;
    MyDoubleSpinBox *spinboxd3_clouds_rotation_z;
    QLabel *label_116;
    MyLineEdit *vect3_clouds_center_z;
    QLabel *label_120;
    QLabel *label_119;
    QLabel *label_122;
    QLabel *label_118;
    QLabel *label_115;
    MyLineEdit *vect3_clouds_center_x;
    MyDoubleSpinBox *spinboxd3_clouds_rotation_y;
    QLabel *label_123;
    MyDoubleSpinBox *spinboxd3_clouds_rotation_x;
    QLabel *label_117;
    MyLineEdit *vect3_clouds_center_y;
    MyLineEdit *logedit_clouds_height;
    MyGroupBox *groupCheck_clouds_distance_mode;
    QVBoxLayout *verticalLayout_13;
    QGridLayout *gridLayout_21;
    QLabel *label_125;
    MyLineEdit *logedit_clouds_distance;
    QLabel *label_126;
    MyLineEdit *logedit_clouds_distance_layer;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_14;
    QGridLayout *gridLayout_22;
    MyLineEdit *logedit_clouds_DE_approaching;
    QLabel *label_128;
    MyLineEdit *logedit_clouds_detail_accuracy;
    QLabel *label_129;
    QLabel *label_130;
    MyLineEdit *logedit_clouds_DE_multiplier;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QWidget *cEffectsVolumetricTab)
    {
        if (cEffectsVolumetricTab->objectName().isEmpty())
            cEffectsVolumetricTab->setObjectName(QString::fromUtf8("cEffectsVolumetricTab"));
        verticalLayout_65 = new QVBoxLayout(cEffectsVolumetricTab);
        verticalLayout_65->setSpacing(2);
        verticalLayout_65->setObjectName(QString::fromUtf8("verticalLayout_65"));
        verticalLayout_65->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        pushButton_local_load_3 = new cButtonLoadSettingsFromWidget(cEffectsVolumetricTab);
        pushButton_local_load_3->setObjectName(QString::fromUtf8("pushButton_local_load_3"));

        horizontalLayout_11->addWidget(pushButton_local_load_3);

        pushButton_local_save_3 = new cButtonSaveSettingsFromWidget(cEffectsVolumetricTab);
        pushButton_local_save_3->setObjectName(QString::fromUtf8("pushButton_local_save_3"));

        horizontalLayout_11->addWidget(pushButton_local_save_3);

        pushButton_local_reset_3 = new cButtonResetSettingsFromWidget(cEffectsVolumetricTab);
        pushButton_local_reset_3->setObjectName(QString::fromUtf8("pushButton_local_reset_3"));

        horizontalLayout_11->addWidget(pushButton_local_reset_3);

        pushButton_local_randomize_3 = new cButtonRandomSettingsFromWidget(cEffectsVolumetricTab);
        pushButton_local_randomize_3->setObjectName(QString::fromUtf8("pushButton_local_randomize_3"));

        horizontalLayout_11->addWidget(pushButton_local_randomize_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_3);


        verticalLayout_65->addLayout(horizontalLayout_11);

        scrollArea_8 = new QScrollArea(cEffectsVolumetricTab);
        scrollArea_8->setObjectName(QString::fromUtf8("scrollArea_8"));
        scrollArea_8->setWidgetResizable(true);
        scrollAreaWidgetContents_9 = new QWidget();
        scrollAreaWidgetContents_9->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_9"));
        scrollAreaWidgetContents_9->setGeometry(QRect(0, 0, 421, 2227));
        verticalLayout_35 = new QVBoxLayout(scrollAreaWidgetContents_9);
        verticalLayout_35->setSpacing(2);
        verticalLayout_35->setObjectName(QString::fromUtf8("verticalLayout_35"));
        verticalLayout_35->setContentsMargins(2, 2, 2, 2);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(-1, 0, -1, -1);
        logedit_volumetric_light_DE_Factor = new MyLineEdit(scrollAreaWidgetContents_9);
        logedit_volumetric_light_DE_Factor->setObjectName(QString::fromUtf8("logedit_volumetric_light_DE_Factor"));

        gridLayout_2->addWidget(logedit_volumetric_light_DE_Factor, 0, 1, 1, 1);

        label_custom_step_multiplier = new QLabel(scrollAreaWidgetContents_9);
        label_custom_step_multiplier->setObjectName(QString::fromUtf8("label_custom_step_multiplier"));

        gridLayout_2->addWidget(label_custom_step_multiplier, 0, 0, 1, 1);


        verticalLayout_35->addLayout(gridLayout_2);

        groupCheck_basic_fog_enabled = new MyGroupBox(scrollAreaWidgetContents_9);
        groupCheck_basic_fog_enabled->setObjectName(QString::fromUtf8("groupCheck_basic_fog_enabled"));
        groupCheck_basic_fog_enabled->setCheckable(true);
        verticalLayout_30 = new QVBoxLayout(groupCheck_basic_fog_enabled);
        verticalLayout_30->setSpacing(2);
        verticalLayout_30->setObjectName(QString::fromUtf8("verticalLayout_30"));
        verticalLayout_30->setContentsMargins(2, 2, 2, 2);
        gridLayout_10 = new QGridLayout();
        gridLayout_10->setSpacing(2);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        logedit_basic_fog_visibility = new MyLineEdit(groupCheck_basic_fog_enabled);
        logedit_basic_fog_visibility->setObjectName(QString::fromUtf8("logedit_basic_fog_visibility"));
        logedit_basic_fog_visibility->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_10->addWidget(logedit_basic_fog_visibility, 0, 1, 1, 1);

        comboBox_basic_fog_primitive = new MyComboBox(groupCheck_basic_fog_enabled);
        comboBox_basic_fog_primitive->addItem(QString());
        comboBox_basic_fog_primitive->setObjectName(QString::fromUtf8("comboBox_basic_fog_primitive"));

        gridLayout_10->addWidget(comboBox_basic_fog_primitive, 3, 1, 1, 1);

        label_63 = new QLabel(groupCheck_basic_fog_enabled);
        label_63->setObjectName(QString::fromUtf8("label_63"));

        gridLayout_10->addWidget(label_63, 0, 0, 1, 1);

        label_64 = new QLabel(groupCheck_basic_fog_enabled);
        label_64->setObjectName(QString::fromUtf8("label_64"));

        gridLayout_10->addWidget(label_64, 1, 0, 1, 1);

        label_72 = new QLabel(groupCheck_basic_fog_enabled);
        label_72->setObjectName(QString::fromUtf8("label_72"));

        gridLayout_10->addWidget(label_72, 3, 0, 1, 1);

        colorButton_basic_fog_color = new MyColorButton(groupCheck_basic_fog_enabled);
        colorButton_basic_fog_color->setObjectName(QString::fromUtf8("colorButton_basic_fog_color"));

        gridLayout_10->addWidget(colorButton_basic_fog_color, 1, 1, 1, 1);

        checkBox_basic_fog_cast_shadows = new MyCheckBox(groupCheck_basic_fog_enabled);
        checkBox_basic_fog_cast_shadows->setObjectName(QString::fromUtf8("checkBox_basic_fog_cast_shadows"));

        gridLayout_10->addWidget(checkBox_basic_fog_cast_shadows, 2, 0, 1, 2);


        verticalLayout_30->addLayout(gridLayout_10);

        pushButton_set_fog_by_mouse = new QPushButton(groupCheck_basic_fog_enabled);
        pushButton_set_fog_by_mouse->setObjectName(QString::fromUtf8("pushButton_set_fog_by_mouse"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_set_fog_by_mouse->sizePolicy().hasHeightForWidth());
        pushButton_set_fog_by_mouse->setSizePolicy(sizePolicy);

        verticalLayout_30->addWidget(pushButton_set_fog_by_mouse);


        verticalLayout_35->addWidget(groupCheck_basic_fog_enabled);

        groupCheck_glow_enabled = new MyGroupBox(scrollAreaWidgetContents_9);
        groupCheck_glow_enabled->setObjectName(QString::fromUtf8("groupCheck_glow_enabled"));
        groupCheck_glow_enabled->setCheckable(true);
        verticalLayout_28 = new QVBoxLayout(groupCheck_glow_enabled);
        verticalLayout_28->setSpacing(2);
        verticalLayout_28->setObjectName(QString::fromUtf8("verticalLayout_28"));
        verticalLayout_28->setContentsMargins(2, 2, 2, 2);
        gridLayout_14 = new QGridLayout();
        gridLayout_14->setSpacing(2);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        label_88 = new QLabel(groupCheck_glow_enabled);
        label_88->setObjectName(QString::fromUtf8("label_88"));

        gridLayout_14->addWidget(label_88, 1, 0, 1, 1);

        label_89 = new QLabel(groupCheck_glow_enabled);
        label_89->setObjectName(QString::fromUtf8("label_89"));

        gridLayout_14->addWidget(label_89, 2, 0, 1, 1);

        logedit_glow_intensity = new MyLineEdit(groupCheck_glow_enabled);
        logedit_glow_intensity->setObjectName(QString::fromUtf8("logedit_glow_intensity"));

        gridLayout_14->addWidget(logedit_glow_intensity, 0, 1, 1, 1);

        label_87 = new QLabel(groupCheck_glow_enabled);
        label_87->setObjectName(QString::fromUtf8("label_87"));

        gridLayout_14->addWidget(label_87, 0, 0, 1, 1);

        colorButton_glow_color_1 = new MyColorButton(groupCheck_glow_enabled);
        colorButton_glow_color_1->setObjectName(QString::fromUtf8("colorButton_glow_color_1"));

        gridLayout_14->addWidget(colorButton_glow_color_1, 1, 1, 1, 1);

        colorButton_glow_color_2 = new MyColorButton(groupCheck_glow_enabled);
        colorButton_glow_color_2->setObjectName(QString::fromUtf8("colorButton_glow_color_2"));

        gridLayout_14->addWidget(colorButton_glow_color_2, 2, 1, 1, 1);


        verticalLayout_28->addLayout(gridLayout_14);


        verticalLayout_35->addWidget(groupCheck_glow_enabled);

        groupCheck_volumetric_fog_enabled = new MyGroupBox(scrollAreaWidgetContents_9);
        groupCheck_volumetric_fog_enabled->setObjectName(QString::fromUtf8("groupCheck_volumetric_fog_enabled"));
        groupCheck_volumetric_fog_enabled->setCheckable(true);
        verticalLayout_33 = new QVBoxLayout(groupCheck_volumetric_fog_enabled);
        verticalLayout_33->setSpacing(2);
        verticalLayout_33->setObjectName(QString::fromUtf8("verticalLayout_33"));
        verticalLayout_33->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(2);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        button_calculateFog = new QPushButton(groupCheck_volumetric_fog_enabled);
        button_calculateFog->setObjectName(QString::fromUtf8("button_calculateFog"));
        sizePolicy.setHeightForWidth(button_calculateFog->sizePolicy().hasHeightForWidth());
        button_calculateFog->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(button_calculateFog);

        toolButton_fog_distance_double = new QToolButton(groupCheck_volumetric_fog_enabled);
        toolButton_fog_distance_double->setObjectName(QString::fromUtf8("toolButton_fog_distance_double"));

        horizontalLayout_4->addWidget(toolButton_fog_distance_double);

        toolButton_fog_distance_half = new QToolButton(groupCheck_volumetric_fog_enabled);
        toolButton_fog_distance_half->setObjectName(QString::fromUtf8("toolButton_fog_distance_half"));

        horizontalLayout_4->addWidget(toolButton_fog_distance_half);


        verticalLayout_33->addLayout(horizontalLayout_4);

        horizontalLayout_volumetricFogMode = new QHBoxLayout();
        horizontalLayout_volumetricFogMode->setSpacing(4);
        horizontalLayout_volumetricFogMode->setObjectName(QString::fromUtf8("horizontalLayout_volumetricFogMode"));
        label_volumetric_fog_mode = new QLabel(groupCheck_volumetric_fog_enabled);
        label_volumetric_fog_mode->setObjectName(QString::fromUtf8("label_volumetric_fog_mode"));

        horizontalLayout_volumetricFogMode->addWidget(label_volumetric_fog_mode);

        comboBox_volumetric_fog_mode = new QComboBox(groupCheck_volumetric_fog_enabled);
        comboBox_volumetric_fog_mode->addItem(QString());
        comboBox_volumetric_fog_mode->addItem(QString());
        comboBox_volumetric_fog_mode->addItem(QString());
        comboBox_volumetric_fog_mode->addItem(QString());
        comboBox_volumetric_fog_mode->addItem(QString());
        comboBox_volumetric_fog_mode->setObjectName(QString::fromUtf8("comboBox_volumetric_fog_mode"));

        horizontalLayout_volumetricFogMode->addWidget(comboBox_volumetric_fog_mode);


        verticalLayout_33->addLayout(horizontalLayout_volumetricFogMode);

        checkBox_voxel_fog_cache_enabled = new MyCheckBox(groupCheck_volumetric_fog_enabled);
        checkBox_voxel_fog_cache_enabled->setObjectName(QString::fromUtf8("checkBox_voxel_fog_cache_enabled"));

        verticalLayout_33->addWidget(checkBox_voxel_fog_cache_enabled);

        horizontalLayout_voxel_fog_cache_resolution = new QHBoxLayout();
        horizontalLayout_voxel_fog_cache_resolution->setSpacing(4);
        horizontalLayout_voxel_fog_cache_resolution->setObjectName(QString::fromUtf8("horizontalLayout_voxel_fog_cache_resolution"));
        label_voxel_fog_cache_resolution = new QLabel(groupCheck_volumetric_fog_enabled);
        label_voxel_fog_cache_resolution->setObjectName(QString::fromUtf8("label_voxel_fog_cache_resolution"));

        horizontalLayout_voxel_fog_cache_resolution->addWidget(label_voxel_fog_cache_resolution);

        sliderInt_voxel_fog_cache_resolution = new QSlider(groupCheck_volumetric_fog_enabled);
        sliderInt_voxel_fog_cache_resolution->setObjectName(QString::fromUtf8("sliderInt_voxel_fog_cache_resolution"));
        sliderInt_voxel_fog_cache_resolution->setMinimum(16);
        sliderInt_voxel_fog_cache_resolution->setMaximum(64);
        sliderInt_voxel_fog_cache_resolution->setValue(32);
        sliderInt_voxel_fog_cache_resolution->setOrientation(Qt::Horizontal);

        horizontalLayout_voxel_fog_cache_resolution->addWidget(sliderInt_voxel_fog_cache_resolution);

        spinboxInt_voxel_fog_cache_resolution = new MySpinBox(groupCheck_volumetric_fog_enabled);
        spinboxInt_voxel_fog_cache_resolution->setObjectName(QString::fromUtf8("spinboxInt_voxel_fog_cache_resolution"));
        spinboxInt_voxel_fog_cache_resolution->setMinimum(16);
        spinboxInt_voxel_fog_cache_resolution->setMaximum(64);
        spinboxInt_voxel_fog_cache_resolution->setValue(32);

        horizontalLayout_voxel_fog_cache_resolution->addWidget(spinboxInt_voxel_fog_cache_resolution);


        verticalLayout_33->addLayout(horizontalLayout_voxel_fog_cache_resolution);

        gridLayout_13 = new QGridLayout();
        gridLayout_13->setSpacing(2);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        label_75 = new QLabel(groupCheck_volumetric_fog_enabled);
        label_75->setObjectName(QString::fromUtf8("label_75"));

        gridLayout_13->addWidget(label_75, 7, 0, 1, 1);

        colorButton_fog_color_2 = new MyColorButton(groupCheck_volumetric_fog_enabled);
        colorButton_fog_color_2->setObjectName(QString::fromUtf8("colorButton_fog_color_2"));

        gridLayout_13->addWidget(colorButton_fog_color_2, 9, 1, 1, 1);

        label_100 = new QLabel(groupCheck_volumetric_fog_enabled);
        label_100->setObjectName(QString::fromUtf8("label_100"));
        label_100->setWordWrap(true);

        gridLayout_13->addWidget(label_100, 5, 0, 1, 1);

        logedit_volumetric_fog_density = new MyLineEdit(groupCheck_volumetric_fog_enabled);
        logedit_volumetric_fog_density->setObjectName(QString::fromUtf8("logedit_volumetric_fog_density"));

        gridLayout_13->addWidget(logedit_volumetric_fog_density, 1, 1, 1, 1);

        label_66 = new QLabel(groupCheck_volumetric_fog_enabled);
        label_66->setObjectName(QString::fromUtf8("label_66"));

        gridLayout_13->addWidget(label_66, 8, 0, 1, 1);

        label_65 = new QLabel(groupCheck_volumetric_fog_enabled);
        label_65->setObjectName(QString::fromUtf8("label_65"));

        gridLayout_13->addWidget(label_65, 1, 0, 1, 1);

        logedit_volumetric_fog_colour_2_distance = new MyLineEdit(groupCheck_volumetric_fog_enabled);
        logedit_volumetric_fog_colour_2_distance->setObjectName(QString::fromUtf8("logedit_volumetric_fog_colour_2_distance"));

        gridLayout_13->addWidget(logedit_volumetric_fog_colour_2_distance, 3, 1, 1, 1);

        label_78 = new QLabel(groupCheck_volumetric_fog_enabled);
        label_78->setObjectName(QString::fromUtf8("label_78"));

        gridLayout_13->addWidget(label_78, 9, 0, 1, 1);

        checkBox_distance_fog_shadows = new MyCheckBox(groupCheck_volumetric_fog_enabled);
        checkBox_distance_fog_shadows->setObjectName(QString::fromUtf8("checkBox_distance_fog_shadows"));
        sizePolicy.setHeightForWidth(checkBox_distance_fog_shadows->sizePolicy().hasHeightForWidth());
        checkBox_distance_fog_shadows->setSizePolicy(sizePolicy);

        gridLayout_13->addWidget(checkBox_distance_fog_shadows, 6, 0, 1, 2);

        logedit_volumetric_fog_colour_1_distance = new MyLineEdit(groupCheck_volumetric_fog_enabled);
        logedit_volumetric_fog_colour_1_distance->setObjectName(QString::fromUtf8("logedit_volumetric_fog_colour_1_distance"));

        gridLayout_13->addWidget(logedit_volumetric_fog_colour_1_distance, 2, 1, 1, 1);

        label_79 = new QLabel(groupCheck_volumetric_fog_enabled);
        label_79->setObjectName(QString::fromUtf8("label_79"));

        gridLayout_13->addWidget(label_79, 10, 0, 1, 1);

        logedit_volumetric_fog_distance_factor = new MyLineEdit(groupCheck_volumetric_fog_enabled);
        logedit_volumetric_fog_distance_factor->setObjectName(QString::fromUtf8("logedit_volumetric_fog_distance_factor"));

        gridLayout_13->addWidget(logedit_volumetric_fog_distance_factor, 4, 1, 1, 1);

        label_67 = new QLabel(groupCheck_volumetric_fog_enabled);
        label_67->setObjectName(QString::fromUtf8("label_67"));

        gridLayout_13->addWidget(label_67, 2, 0, 1, 1);

        colorButton_fog_color_1 = new MyColorButton(groupCheck_volumetric_fog_enabled);
        colorButton_fog_color_1->setObjectName(QString::fromUtf8("colorButton_fog_color_1"));

        gridLayout_13->addWidget(colorButton_fog_color_1, 8, 1, 1, 1);

        label_76 = new QLabel(groupCheck_volumetric_fog_enabled);
        label_76->setObjectName(QString::fromUtf8("label_76"));

        gridLayout_13->addWidget(label_76, 3, 0, 1, 1);

        label_77 = new QLabel(groupCheck_volumetric_fog_enabled);
        label_77->setObjectName(QString::fromUtf8("label_77"));

        gridLayout_13->addWidget(label_77, 4, 0, 1, 1);

        logedit_volumetric_fog_distance_from_surface = new MyLineEdit(groupCheck_volumetric_fog_enabled);
        logedit_volumetric_fog_distance_from_surface->setObjectName(QString::fromUtf8("logedit_volumetric_fog_distance_from_surface"));

        gridLayout_13->addWidget(logedit_volumetric_fog_distance_from_surface, 5, 1, 1, 1);

        comboBox_distance_fog_primitive = new MyComboBox(groupCheck_volumetric_fog_enabled);
        comboBox_distance_fog_primitive->addItem(QString());
        comboBox_distance_fog_primitive->setObjectName(QString::fromUtf8("comboBox_distance_fog_primitive"));

        gridLayout_13->addWidget(comboBox_distance_fog_primitive, 7, 1, 1, 1);

        colorButton_fog_color_3 = new MyColorButton(groupCheck_volumetric_fog_enabled);
        colorButton_fog_color_3->setObjectName(QString::fromUtf8("colorButton_fog_color_3"));

        gridLayout_13->addWidget(colorButton_fog_color_3, 10, 1, 1, 1);


        verticalLayout_33->addLayout(gridLayout_13);


        verticalLayout_35->addWidget(groupCheck_volumetric_fog_enabled);

        groupCheck_iteration_fog_enable = new MyGroupBox(scrollAreaWidgetContents_9);
        groupCheck_iteration_fog_enable->setObjectName(QString::fromUtf8("groupCheck_iteration_fog_enable"));
        groupCheck_iteration_fog_enable->setCheckable(true);
        verticalLayout_27 = new QVBoxLayout(groupCheck_iteration_fog_enable);
        verticalLayout_27->setSpacing(2);
        verticalLayout_27->setObjectName(QString::fromUtf8("verticalLayout_27"));
        verticalLayout_27->setContentsMargins(2, 2, 2, 2);
        gridLayout_8 = new QGridLayout();
        gridLayout_8->setSpacing(2);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        label_86 = new QLabel(groupCheck_iteration_fog_enable);
        label_86->setObjectName(QString::fromUtf8("label_86"));

        gridLayout_8->addWidget(label_86, 7, 0, 1, 1);

        spinbox_iteration_fog_opacity_trim = new MyDoubleSpinBox(groupCheck_iteration_fog_enable);
        spinbox_iteration_fog_opacity_trim->setObjectName(QString::fromUtf8("spinbox_iteration_fog_opacity_trim"));
        sizePolicy.setHeightForWidth(spinbox_iteration_fog_opacity_trim->sizePolicy().hasHeightForWidth());
        spinbox_iteration_fog_opacity_trim->setSizePolicy(sizePolicy);
        spinbox_iteration_fog_opacity_trim->setDecimals(2);
        spinbox_iteration_fog_opacity_trim->setMaximum(1000.000000000000000);
        spinbox_iteration_fog_opacity_trim->setSingleStep(1.000000000000000);

        gridLayout_8->addWidget(spinbox_iteration_fog_opacity_trim, 1, 1, 1, 1);

        spinbox_iteration_fog_color_1_maxiter = new MyDoubleSpinBox(groupCheck_iteration_fog_enable);
        spinbox_iteration_fog_color_1_maxiter->setObjectName(QString::fromUtf8("spinbox_iteration_fog_color_1_maxiter"));
        sizePolicy.setHeightForWidth(spinbox_iteration_fog_color_1_maxiter->sizePolicy().hasHeightForWidth());
        spinbox_iteration_fog_color_1_maxiter->setSizePolicy(sizePolicy);
        spinbox_iteration_fog_color_1_maxiter->setDecimals(2);
        spinbox_iteration_fog_color_1_maxiter->setMaximum(1000.000000000000000);
        spinbox_iteration_fog_color_1_maxiter->setSingleStep(1.000000000000000);

        gridLayout_8->addWidget(spinbox_iteration_fog_color_1_maxiter, 3, 1, 1, 1);

        label_85 = new QLabel(groupCheck_iteration_fog_enable);
        label_85->setObjectName(QString::fromUtf8("label_85"));

        gridLayout_8->addWidget(label_85, 6, 0, 1, 1);

        label_80 = new QLabel(groupCheck_iteration_fog_enable);
        label_80->setObjectName(QString::fromUtf8("label_80"));

        gridLayout_8->addWidget(label_80, 0, 0, 1, 1);

        spinbox_iteration_fog_opacity_trim_high = new MyDoubleSpinBox(groupCheck_iteration_fog_enable);
        spinbox_iteration_fog_opacity_trim_high->setObjectName(QString::fromUtf8("spinbox_iteration_fog_opacity_trim_high"));
        sizePolicy.setHeightForWidth(spinbox_iteration_fog_opacity_trim_high->sizePolicy().hasHeightForWidth());
        spinbox_iteration_fog_opacity_trim_high->setSizePolicy(sizePolicy);
        spinbox_iteration_fog_opacity_trim_high->setDecimals(2);
        spinbox_iteration_fog_opacity_trim_high->setMaximum(1000.000000000000000);
        spinbox_iteration_fog_opacity_trim_high->setSingleStep(1.000000000000000);

        gridLayout_8->addWidget(spinbox_iteration_fog_opacity_trim_high, 2, 1, 1, 1);

        label_101 = new QLabel(groupCheck_iteration_fog_enable);
        label_101->setObjectName(QString::fromUtf8("label_101"));

        gridLayout_8->addWidget(label_101, 2, 0, 1, 1);

        label_81 = new QLabel(groupCheck_iteration_fog_enable);
        label_81->setObjectName(QString::fromUtf8("label_81"));

        gridLayout_8->addWidget(label_81, 1, 0, 1, 1);

        spinbox_iteration_fog_brightness_boost = new MyDoubleSpinBox(groupCheck_iteration_fog_enable);
        spinbox_iteration_fog_brightness_boost->setObjectName(QString::fromUtf8("spinbox_iteration_fog_brightness_boost"));
        sizePolicy.setHeightForWidth(spinbox_iteration_fog_brightness_boost->sizePolicy().hasHeightForWidth());
        spinbox_iteration_fog_brightness_boost->setSizePolicy(sizePolicy);
        spinbox_iteration_fog_brightness_boost->setDecimals(2);
        spinbox_iteration_fog_brightness_boost->setMaximum(1000000.000000000000000);
        spinbox_iteration_fog_brightness_boost->setSingleStep(10.000000000000000);

        gridLayout_8->addWidget(spinbox_iteration_fog_brightness_boost, 10, 1, 1, 1);

        colorButton_iteration_fog_color_1 = new MyColorButton(groupCheck_iteration_fog_enable);
        colorButton_iteration_fog_color_1->setObjectName(QString::fromUtf8("colorButton_iteration_fog_color_1"));

        gridLayout_8->addWidget(colorButton_iteration_fog_color_1, 5, 1, 1, 1);

        checkBox_iteration_fog_shadows = new MyCheckBox(groupCheck_iteration_fog_enable);
        checkBox_iteration_fog_shadows->setObjectName(QString::fromUtf8("checkBox_iteration_fog_shadows"));
        sizePolicy.setHeightForWidth(checkBox_iteration_fog_shadows->sizePolicy().hasHeightForWidth());
        checkBox_iteration_fog_shadows->setSizePolicy(sizePolicy);

        gridLayout_8->addWidget(checkBox_iteration_fog_shadows, 8, 0, 1, 2);

        colorButton_iteration_fog_color_2 = new MyColorButton(groupCheck_iteration_fog_enable);
        colorButton_iteration_fog_color_2->setObjectName(QString::fromUtf8("colorButton_iteration_fog_color_2"));

        gridLayout_8->addWidget(colorButton_iteration_fog_color_2, 6, 1, 1, 1);

        spinbox_iteration_fog_color_2_maxiter = new MyDoubleSpinBox(groupCheck_iteration_fog_enable);
        spinbox_iteration_fog_color_2_maxiter->setObjectName(QString::fromUtf8("spinbox_iteration_fog_color_2_maxiter"));
        sizePolicy.setHeightForWidth(spinbox_iteration_fog_color_2_maxiter->sizePolicy().hasHeightForWidth());
        spinbox_iteration_fog_color_2_maxiter->setSizePolicy(sizePolicy);
        spinbox_iteration_fog_color_2_maxiter->setDecimals(2);
        spinbox_iteration_fog_color_2_maxiter->setMaximum(1000.000000000000000);
        spinbox_iteration_fog_color_2_maxiter->setSingleStep(1.000000000000000);

        gridLayout_8->addWidget(spinbox_iteration_fog_color_2_maxiter, 4, 1, 1, 1);

        label_83 = new QLabel(groupCheck_iteration_fog_enable);
        label_83->setObjectName(QString::fromUtf8("label_83"));

        gridLayout_8->addWidget(label_83, 4, 0, 1, 1);

        label_82 = new QLabel(groupCheck_iteration_fog_enable);
        label_82->setObjectName(QString::fromUtf8("label_82"));

        gridLayout_8->addWidget(label_82, 3, 0, 1, 1);

        colorButton_iteration_fog_color_3 = new MyColorButton(groupCheck_iteration_fog_enable);
        colorButton_iteration_fog_color_3->setObjectName(QString::fromUtf8("colorButton_iteration_fog_color_3"));

        gridLayout_8->addWidget(colorButton_iteration_fog_color_3, 7, 1, 1, 1);

        label_99 = new QLabel(groupCheck_iteration_fog_enable);
        label_99->setObjectName(QString::fromUtf8("label_99"));
        label_99->setWordWrap(true);

        gridLayout_8->addWidget(label_99, 10, 0, 1, 1);

        logedit_iteration_fog_opacity = new MyLineEdit(groupCheck_iteration_fog_enable);
        logedit_iteration_fog_opacity->setObjectName(QString::fromUtf8("logedit_iteration_fog_opacity"));

        gridLayout_8->addWidget(logedit_iteration_fog_opacity, 0, 1, 1, 1);

        label_84 = new QLabel(groupCheck_iteration_fog_enable);
        label_84->setObjectName(QString::fromUtf8("label_84"));

        gridLayout_8->addWidget(label_84, 5, 0, 1, 1);

        label_74 = new QLabel(groupCheck_iteration_fog_enable);
        label_74->setObjectName(QString::fromUtf8("label_74"));

        gridLayout_8->addWidget(label_74, 9, 0, 1, 1);

        comboBox_iteration_fog_primitive = new MyComboBox(groupCheck_iteration_fog_enable);
        comboBox_iteration_fog_primitive->addItem(QString());
        comboBox_iteration_fog_primitive->setObjectName(QString::fromUtf8("comboBox_iteration_fog_primitive"));

        gridLayout_8->addWidget(comboBox_iteration_fog_primitive, 9, 1, 1, 1);


        verticalLayout_27->addLayout(gridLayout_8);

        pushButton_autoFog_iteration = new QPushButton(groupCheck_iteration_fog_enable);
        pushButton_autoFog_iteration->setObjectName(QString::fromUtf8("pushButton_autoFog_iteration"));

        verticalLayout_27->addWidget(pushButton_autoFog_iteration);

        horizontalLayout_autoFogScale = new QHBoxLayout();
        horizontalLayout_autoFogScale->setObjectName(QString::fromUtf8("horizontalLayout_autoFogScale"));
        label_autoFogOpacityScale = new QLabel(groupCheck_iteration_fog_enable);
        label_autoFogOpacityScale->setObjectName(QString::fromUtf8("label_autoFogOpacityScale"));

        horizontalLayout_autoFogScale->addWidget(label_autoFogOpacityScale);

        spinbox_auto_fog_opacity_scale = new MyDoubleSpinBox(groupCheck_iteration_fog_enable);
        spinbox_auto_fog_opacity_scale->setObjectName(QString::fromUtf8("spinbox_auto_fog_opacity_scale"));
        sizePolicy.setHeightForWidth(spinbox_auto_fog_opacity_scale->sizePolicy().hasHeightForWidth());
        spinbox_auto_fog_opacity_scale->setSizePolicy(sizePolicy);
        spinbox_auto_fog_opacity_scale->setDecimals(2);
        spinbox_auto_fog_opacity_scale->setMinimum(0.010000000000000);
        spinbox_auto_fog_opacity_scale->setMaximum(1000.000000000000000);
        spinbox_auto_fog_opacity_scale->setSingleStep(0.100000000000000);
        spinbox_auto_fog_opacity_scale->setValue(1.000000000000000);

        horizontalLayout_autoFogScale->addWidget(spinbox_auto_fog_opacity_scale);


        verticalLayout_27->addLayout(horizontalLayout_autoFogScale);

        horizontalLayout_autoFogTrimBias = new QHBoxLayout();
        horizontalLayout_autoFogTrimBias->setObjectName(QString::fromUtf8("horizontalLayout_autoFogTrimBias"));
        label_autoFogTrimBias = new QLabel(groupCheck_iteration_fog_enable);
        label_autoFogTrimBias->setObjectName(QString::fromUtf8("label_autoFogTrimBias"));

        horizontalLayout_autoFogTrimBias->addWidget(label_autoFogTrimBias);

        spinbox_auto_fog_trim_bias = new MyDoubleSpinBox(groupCheck_iteration_fog_enable);
        spinbox_auto_fog_trim_bias->setObjectName(QString::fromUtf8("spinbox_auto_fog_trim_bias"));
        sizePolicy.setHeightForWidth(spinbox_auto_fog_trim_bias->sizePolicy().hasHeightForWidth());
        spinbox_auto_fog_trim_bias->setSizePolicy(sizePolicy);
        spinbox_auto_fog_trim_bias->setDecimals(1);
        spinbox_auto_fog_trim_bias->setMinimum(-500.000000000000000);
        spinbox_auto_fog_trim_bias->setMaximum(500.000000000000000);
        spinbox_auto_fog_trim_bias->setSingleStep(0.500000000000000);
        spinbox_auto_fog_trim_bias->setValue(0.000000000000000);

        horizontalLayout_autoFogTrimBias->addWidget(spinbox_auto_fog_trim_bias);


        verticalLayout_27->addLayout(horizontalLayout_autoFogTrimBias);

        horizontalLayout_autoFogTrimHighBias = new QHBoxLayout();
        horizontalLayout_autoFogTrimHighBias->setObjectName(QString::fromUtf8("horizontalLayout_autoFogTrimHighBias"));
        label_autoFogTrimHighBias = new QLabel(groupCheck_iteration_fog_enable);
        label_autoFogTrimHighBias->setObjectName(QString::fromUtf8("label_autoFogTrimHighBias"));

        horizontalLayout_autoFogTrimHighBias->addWidget(label_autoFogTrimHighBias);

        spinbox_auto_fog_trim_high_bias = new MyDoubleSpinBox(groupCheck_iteration_fog_enable);
        spinbox_auto_fog_trim_high_bias->setObjectName(QString::fromUtf8("spinbox_auto_fog_trim_high_bias"));
        sizePolicy.setHeightForWidth(spinbox_auto_fog_trim_high_bias->sizePolicy().hasHeightForWidth());
        spinbox_auto_fog_trim_high_bias->setSizePolicy(sizePolicy);
        spinbox_auto_fog_trim_high_bias->setDecimals(1);
        spinbox_auto_fog_trim_high_bias->setMinimum(-2000.000000000000000);
        spinbox_auto_fog_trim_high_bias->setMaximum(2000.000000000000000);
        spinbox_auto_fog_trim_high_bias->setSingleStep(1.000000000000000);
        spinbox_auto_fog_trim_high_bias->setValue(0.000000000000000);

        horizontalLayout_autoFogTrimHighBias->addWidget(spinbox_auto_fog_trim_high_bias);


        verticalLayout_27->addLayout(horizontalLayout_autoFogTrimHighBias);

        horizontalLayout_autoFogColorSpread = new QHBoxLayout();
        horizontalLayout_autoFogColorSpread->setObjectName(QString::fromUtf8("horizontalLayout_autoFogColorSpread"));
        label_autoFogColorSpread = new QLabel(groupCheck_iteration_fog_enable);
        label_autoFogColorSpread->setObjectName(QString::fromUtf8("label_autoFogColorSpread"));

        horizontalLayout_autoFogColorSpread->addWidget(label_autoFogColorSpread);

        spinbox_auto_fog_color_spread = new MyDoubleSpinBox(groupCheck_iteration_fog_enable);
        spinbox_auto_fog_color_spread->setObjectName(QString::fromUtf8("spinbox_auto_fog_color_spread"));
        sizePolicy.setHeightForWidth(spinbox_auto_fog_color_spread->sizePolicy().hasHeightForWidth());
        spinbox_auto_fog_color_spread->setSizePolicy(sizePolicy);
        spinbox_auto_fog_color_spread->setDecimals(2);
        spinbox_auto_fog_color_spread->setMinimum(0.100000000000000);
        spinbox_auto_fog_color_spread->setMaximum(2.000000000000000);
        spinbox_auto_fog_color_spread->setSingleStep(0.100000000000000);
        spinbox_auto_fog_color_spread->setValue(1.000000000000000);

        horizontalLayout_autoFogColorSpread->addWidget(spinbox_auto_fog_color_spread);


        verticalLayout_27->addLayout(horizontalLayout_autoFogColorSpread);

        horizontalLayout_autoFogBoostScale = new QHBoxLayout();
        horizontalLayout_autoFogBoostScale->setObjectName(QString::fromUtf8("horizontalLayout_autoFogBoostScale"));
        label_autoFogBoostScale = new QLabel(groupCheck_iteration_fog_enable);
        label_autoFogBoostScale->setObjectName(QString::fromUtf8("label_autoFogBoostScale"));

        horizontalLayout_autoFogBoostScale->addWidget(label_autoFogBoostScale);

        spinbox_auto_fog_boost_scale = new MyDoubleSpinBox(groupCheck_iteration_fog_enable);
        spinbox_auto_fog_boost_scale->setObjectName(QString::fromUtf8("spinbox_auto_fog_boost_scale"));
        sizePolicy.setHeightForWidth(spinbox_auto_fog_boost_scale->sizePolicy().hasHeightForWidth());
        spinbox_auto_fog_boost_scale->setSizePolicy(sizePolicy);
        spinbox_auto_fog_boost_scale->setDecimals(2);
        spinbox_auto_fog_boost_scale->setMinimum(0.000000000000000);
        spinbox_auto_fog_boost_scale->setMaximum(3.000000000000000);
        spinbox_auto_fog_boost_scale->setSingleStep(0.100000000000000);
        spinbox_auto_fog_boost_scale->setValue(1.000000000000000);

        horizontalLayout_autoFogBoostScale->addWidget(spinbox_auto_fog_boost_scale);


        verticalLayout_27->addLayout(horizontalLayout_autoFogBoostScale);


        verticalLayout_35->addWidget(groupCheck_iteration_fog_enable);

        groupCheck_clouds_enable = new MyGroupBox(scrollAreaWidgetContents_9);
        groupCheck_clouds_enable->setObjectName(QString::fromUtf8("groupCheck_clouds_enable"));
        groupCheck_clouds_enable->setCheckable(true);
        verticalLayout_6 = new QVBoxLayout(groupCheck_clouds_enable);
        verticalLayout_6->setSpacing(2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_cloudsPreset = new QHBoxLayout();
        horizontalLayout_cloudsPreset->setObjectName(QString::fromUtf8("horizontalLayout_cloudsPreset"));
        label_clouds_preset = new QLabel(groupCheck_clouds_enable);
        label_clouds_preset->setObjectName(QString::fromUtf8("label_clouds_preset"));

        horizontalLayout_cloudsPreset->addWidget(label_clouds_preset);

        comboBox_clouds_preset = new QComboBox(groupCheck_clouds_enable);
        comboBox_clouds_preset->addItem(QString());
        comboBox_clouds_preset->addItem(QString());
        comboBox_clouds_preset->addItem(QString());
        comboBox_clouds_preset->addItem(QString());
        comboBox_clouds_preset->setObjectName(QString::fromUtf8("comboBox_clouds_preset"));

        horizontalLayout_cloudsPreset->addWidget(comboBox_clouds_preset);

        pushButton_clouds_apply_preset = new QPushButton(groupCheck_clouds_enable);
        pushButton_clouds_apply_preset->setObjectName(QString::fromUtf8("pushButton_clouds_apply_preset"));

        horizontalLayout_cloudsPreset->addWidget(pushButton_clouds_apply_preset);


        verticalLayout_6->addLayout(horizontalLayout_cloudsPreset);

        gridLayout_19 = new QGridLayout();
        gridLayout_19->setSpacing(2);
        gridLayout_19->setObjectName(QString::fromUtf8("gridLayout_19"));
        gridLayout_19->setContentsMargins(-1, -1, -1, 2);
        label_124 = new QLabel(groupCheck_clouds_enable);
        label_124->setObjectName(QString::fromUtf8("label_124"));

        gridLayout_19->addWidget(label_124, 0, 0, 1, 1);

        spinboxInt_clouds_noise_iterations = new MySpinBox(groupCheck_clouds_enable);
        spinboxInt_clouds_noise_iterations->setObjectName(QString::fromUtf8("spinboxInt_clouds_noise_iterations"));
        sizePolicy.setHeightForWidth(spinboxInt_clouds_noise_iterations->sizePolicy().hasHeightForWidth());
        spinboxInt_clouds_noise_iterations->setSizePolicy(sizePolicy);
        spinboxInt_clouds_noise_iterations->setMinimum(1);
        spinboxInt_clouds_noise_iterations->setMaximum(100);

        gridLayout_19->addWidget(spinboxInt_clouds_noise_iterations, 1, 1, 1, 1);

        label_110 = new QLabel(groupCheck_clouds_enable);
        label_110->setObjectName(QString::fromUtf8("label_110"));

        gridLayout_19->addWidget(label_110, 1, 0, 1, 1);

        spinbox_clouds_density = new MyDoubleSpinBox(groupCheck_clouds_enable);
        spinbox_clouds_density->setObjectName(QString::fromUtf8("spinbox_clouds_density"));
        sizePolicy.setHeightForWidth(spinbox_clouds_density->sizePolicy().hasHeightForWidth());
        spinbox_clouds_density->setSizePolicy(sizePolicy);
        spinbox_clouds_density->setDecimals(3);
        spinbox_clouds_density->setMaximum(1.000000000000000);
        spinbox_clouds_density->setSingleStep(0.001000000000000);

        gridLayout_19->addWidget(spinbox_clouds_density, 5, 1, 1, 1);

        label_114 = new QLabel(groupCheck_clouds_enable);
        label_114->setObjectName(QString::fromUtf8("label_114"));

        gridLayout_19->addWidget(label_114, 6, 0, 1, 1);

        logedit_clouds_period = new MyLineEdit(groupCheck_clouds_enable);
        logedit_clouds_period->setObjectName(QString::fromUtf8("logedit_clouds_period"));

        gridLayout_19->addWidget(logedit_clouds_period, 6, 1, 1, 1);

        label_113 = new QLabel(groupCheck_clouds_enable);
        label_113->setObjectName(QString::fromUtf8("label_113"));

        gridLayout_19->addWidget(label_113, 5, 0, 1, 1);

        spinboxInt_clouds_random_seed = new MySpinBox(groupCheck_clouds_enable);
        spinboxInt_clouds_random_seed->setObjectName(QString::fromUtf8("spinboxInt_clouds_random_seed"));
        sizePolicy.setHeightForWidth(spinboxInt_clouds_random_seed->sizePolicy().hasHeightForWidth());
        spinboxInt_clouds_random_seed->setSizePolicy(sizePolicy);
        spinboxInt_clouds_random_seed->setMaximum(100000);

        gridLayout_19->addWidget(spinboxInt_clouds_random_seed, 2, 1, 1, 1);

        spinbox_clouds_ambient_light = new MyDoubleSpinBox(groupCheck_clouds_enable);
        spinbox_clouds_ambient_light->setObjectName(QString::fromUtf8("spinbox_clouds_ambient_light"));
        sizePolicy.setHeightForWidth(spinbox_clouds_ambient_light->sizePolicy().hasHeightForWidth());
        spinbox_clouds_ambient_light->setSizePolicy(sizePolicy);
        spinbox_clouds_ambient_light->setDecimals(3);
        spinbox_clouds_ambient_light->setMaximum(1.000000000000000);
        spinbox_clouds_ambient_light->setSingleStep(0.010000000000000);

        gridLayout_19->addWidget(spinbox_clouds_ambient_light, 7, 1, 1, 1);

        label_144 = new QLabel(groupCheck_clouds_enable);
        label_144->setObjectName(QString::fromUtf8("label_144"));
        label_144->setWordWrap(true);

        gridLayout_19->addWidget(label_144, 8, 0, 1, 1);

        logedit_clouds_lights_boost = new MyLineEdit(groupCheck_clouds_enable);
        logedit_clouds_lights_boost->setObjectName(QString::fromUtf8("logedit_clouds_lights_boost"));

        gridLayout_19->addWidget(logedit_clouds_lights_boost, 8, 1, 1, 1);

        colorButton_clouds_color = new MyColorButton(groupCheck_clouds_enable);
        colorButton_clouds_color->setObjectName(QString::fromUtf8("colorButton_clouds_color"));

        gridLayout_19->addWidget(colorButton_clouds_color, 0, 1, 1, 1);

        pushButton_clouds_randomize = new QPushButton(groupCheck_clouds_enable);
        pushButton_clouds_randomize->setObjectName(QString::fromUtf8("pushButton_clouds_randomize"));

        gridLayout_19->addWidget(pushButton_clouds_randomize, 3, 0, 1, 2);

        label_112 = new QLabel(groupCheck_clouds_enable);
        label_112->setObjectName(QString::fromUtf8("label_112"));

        gridLayout_19->addWidget(label_112, 4, 0, 1, 1);

        label_111 = new QLabel(groupCheck_clouds_enable);
        label_111->setObjectName(QString::fromUtf8("label_111"));

        gridLayout_19->addWidget(label_111, 2, 0, 1, 1);

        logedit_clouds_opacity = new MyLineEdit(groupCheck_clouds_enable);
        logedit_clouds_opacity->setObjectName(QString::fromUtf8("logedit_clouds_opacity"));

        gridLayout_19->addWidget(logedit_clouds_opacity, 4, 1, 1, 1);

        label_143 = new QLabel(groupCheck_clouds_enable);
        label_143->setObjectName(QString::fromUtf8("label_143"));

        gridLayout_19->addWidget(label_143, 7, 0, 1, 1);

        checkBox_clouds_cast_shadows = new MyCheckBox(groupCheck_clouds_enable);
        checkBox_clouds_cast_shadows->setObjectName(QString::fromUtf8("checkBox_clouds_cast_shadows"));
        sizePolicy.setHeightForWidth(checkBox_clouds_cast_shadows->sizePolicy().hasHeightForWidth());
        checkBox_clouds_cast_shadows->setSizePolicy(sizePolicy);

        gridLayout_19->addWidget(checkBox_clouds_cast_shadows, 9, 0, 1, 2);

        label_clouds_density_gamma = new QLabel(groupCheck_clouds_enable);
        label_clouds_density_gamma->setObjectName(QString::fromUtf8("label_clouds_density_gamma"));

        gridLayout_19->addWidget(label_clouds_density_gamma, 10, 0, 1, 1);

        spinbox_clouds_density_gamma = new MyDoubleSpinBox(groupCheck_clouds_enable);
        spinbox_clouds_density_gamma->setObjectName(QString::fromUtf8("spinbox_clouds_density_gamma"));
        spinbox_clouds_density_gamma->setDecimals(2);
        spinbox_clouds_density_gamma->setMinimum(0.300000000000000);
        spinbox_clouds_density_gamma->setMaximum(3.000000000000000);
        spinbox_clouds_density_gamma->setSingleStep(0.100000000000000);
        spinbox_clouds_density_gamma->setValue(1.000000000000000);

        gridLayout_19->addWidget(spinbox_clouds_density_gamma, 10, 1, 1, 1);

        label_clouds_softness = new QLabel(groupCheck_clouds_enable);
        label_clouds_softness->setObjectName(QString::fromUtf8("label_clouds_softness"));

        gridLayout_19->addWidget(label_clouds_softness, 11, 0, 1, 1);

        spinbox_clouds_softness = new MyDoubleSpinBox(groupCheck_clouds_enable);
        spinbox_clouds_softness->setObjectName(QString::fromUtf8("spinbox_clouds_softness"));
        spinbox_clouds_softness->setDecimals(2);
        spinbox_clouds_softness->setMinimum(0.050000000000000);
        spinbox_clouds_softness->setMaximum(1.000000000000000);
        spinbox_clouds_softness->setSingleStep(0.050000000000000);
        spinbox_clouds_softness->setValue(0.400000000000000);

        gridLayout_19->addWidget(spinbox_clouds_softness, 11, 1, 1, 1);

        checkBox_clouds_adaptive_detail = new MyCheckBox(groupCheck_clouds_enable);
        checkBox_clouds_adaptive_detail->setObjectName(QString::fromUtf8("checkBox_clouds_adaptive_detail"));
        checkBox_clouds_adaptive_detail->setChecked(true);

        gridLayout_19->addWidget(checkBox_clouds_adaptive_detail, 12, 0, 1, 2);


        verticalLayout_6->addLayout(gridLayout_19);

        groupCheck_clouds_sharp_edges = new MyGroupBox(groupCheck_clouds_enable);
        groupCheck_clouds_sharp_edges->setObjectName(QString::fromUtf8("groupCheck_clouds_sharp_edges"));
        groupCheck_clouds_sharp_edges->setCheckable(true);
        formLayout_2 = new QFormLayout(groupCheck_clouds_sharp_edges);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setHorizontalSpacing(2);
        formLayout_2->setVerticalSpacing(2);
        formLayout_2->setContentsMargins(2, 2, 2, 2);
        label_142 = new QLabel(groupCheck_clouds_sharp_edges);
        label_142->setObjectName(QString::fromUtf8("label_142"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_142);

        spinbox_clouds_sharpness = new MyDoubleSpinBox(groupCheck_clouds_sharp_edges);
        spinbox_clouds_sharpness->setObjectName(QString::fromUtf8("spinbox_clouds_sharpness"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(spinbox_clouds_sharpness->sizePolicy().hasHeightForWidth());
        spinbox_clouds_sharpness->setSizePolicy(sizePolicy1);
        spinbox_clouds_sharpness->setDecimals(1);
        spinbox_clouds_sharpness->setMinimum(1.000000000000000);
        spinbox_clouds_sharpness->setMaximum(1000000.000000000000000);
        spinbox_clouds_sharpness->setSingleStep(1.000000000000000);
        spinbox_clouds_sharpness->setValue(20.000000000000000);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, spinbox_clouds_sharpness);


        verticalLayout_6->addWidget(groupCheck_clouds_sharp_edges);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(2);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        vect3_clouds_speed_y = new MyLineEdit(groupCheck_clouds_enable);
        vect3_clouds_speed_y->setObjectName(QString::fromUtf8("vect3_clouds_speed_y"));

        gridLayout_6->addWidget(vect3_clouds_speed_y, 1, 3, 1, 1);

        label_140 = new QLabel(groupCheck_clouds_enable);
        label_140->setObjectName(QString::fromUtf8("label_140"));
        label_140->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_140, 1, 2, 1, 1);

        label_141 = new QLabel(groupCheck_clouds_enable);
        label_141->setObjectName(QString::fromUtf8("label_141"));
        label_141->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_141, 2, 2, 1, 1);

        vect3_clouds_speed_x = new MyLineEdit(groupCheck_clouds_enable);
        vect3_clouds_speed_x->setObjectName(QString::fromUtf8("vect3_clouds_speed_x"));

        gridLayout_6->addWidget(vect3_clouds_speed_x, 0, 3, 1, 1);

        label_135 = new QLabel(groupCheck_clouds_enable);
        label_135->setObjectName(QString::fromUtf8("label_135"));
        label_135->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_6->addWidget(label_135, 0, 2, 1, 1);

        vect3_clouds_speed_z = new MyLineEdit(groupCheck_clouds_enable);
        vect3_clouds_speed_z->setObjectName(QString::fromUtf8("vect3_clouds_speed_z"));

        gridLayout_6->addWidget(vect3_clouds_speed_z, 2, 3, 1, 1);

        label_133 = new QLabel(groupCheck_clouds_enable);
        label_133->setObjectName(QString::fromUtf8("label_133"));

        gridLayout_6->addWidget(label_133, 1, 1, 1, 1);


        verticalLayout_6->addLayout(gridLayout_6);

        gridLayout_12 = new QGridLayout();
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        gridLayout_12->setContentsMargins(-1, 10, -1, -1);
        label_145 = new QLabel(groupCheck_clouds_enable);
        label_145->setObjectName(QString::fromUtf8("label_145"));

        gridLayout_12->addWidget(label_145, 0, 0, 1, 1);

        comboBox_clouds_primitive = new MyComboBox(groupCheck_clouds_enable);
        comboBox_clouds_primitive->addItem(QString());
        comboBox_clouds_primitive->setObjectName(QString::fromUtf8("comboBox_clouds_primitive"));

        gridLayout_12->addWidget(comboBox_clouds_primitive, 0, 1, 1, 1);


        verticalLayout_6->addLayout(gridLayout_12);

        groupCheck_clouds_plane_shape = new MyGroupBox(groupCheck_clouds_enable);
        groupCheck_clouds_plane_shape->setObjectName(QString::fromUtf8("groupCheck_clouds_plane_shape"));
        groupCheck_clouds_plane_shape->setCheckable(true);
        verticalLayout_7 = new QVBoxLayout(groupCheck_clouds_plane_shape);
        verticalLayout_7->setSpacing(2);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(2, 2, 2, 2);
        gridLayout_20 = new QGridLayout();
        gridLayout_20->setSpacing(2);
        gridLayout_20->setObjectName(QString::fromUtf8("gridLayout_20"));
        label_121 = new QLabel(groupCheck_clouds_plane_shape);
        label_121->setObjectName(QString::fromUtf8("label_121"));
        label_121->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_20->addWidget(label_121, 4, 1, 1, 1);

        spinboxd3_clouds_rotation_z = new MyDoubleSpinBox(groupCheck_clouds_plane_shape);
        spinboxd3_clouds_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_clouds_rotation_z"));
        sizePolicy.setHeightForWidth(spinboxd3_clouds_rotation_z->sizePolicy().hasHeightForWidth());
        spinboxd3_clouds_rotation_z->setSizePolicy(sizePolicy);
        spinboxd3_clouds_rotation_z->setAccelerated(true);
        spinboxd3_clouds_rotation_z->setDecimals(2);
        spinboxd3_clouds_rotation_z->setMinimum(-180.000000000000000);
        spinboxd3_clouds_rotation_z->setMaximum(180.000000000000000);
        spinboxd3_clouds_rotation_z->setSingleStep(1.000000000000000);

        gridLayout_20->addWidget(spinboxd3_clouds_rotation_z, 6, 2, 1, 1);

        label_116 = new QLabel(groupCheck_clouds_plane_shape);
        label_116->setObjectName(QString::fromUtf8("label_116"));

        gridLayout_20->addWidget(label_116, 1, 0, 3, 1);

        vect3_clouds_center_z = new MyLineEdit(groupCheck_clouds_plane_shape);
        vect3_clouds_center_z->setObjectName(QString::fromUtf8("vect3_clouds_center_z"));

        gridLayout_20->addWidget(vect3_clouds_center_z, 3, 2, 1, 1);

        label_120 = new QLabel(groupCheck_clouds_plane_shape);
        label_120->setObjectName(QString::fromUtf8("label_120"));

        gridLayout_20->addWidget(label_120, 4, 0, 3, 1);

        label_119 = new QLabel(groupCheck_clouds_plane_shape);
        label_119->setObjectName(QString::fromUtf8("label_119"));
        label_119->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_20->addWidget(label_119, 3, 1, 1, 1);

        label_122 = new QLabel(groupCheck_clouds_plane_shape);
        label_122->setObjectName(QString::fromUtf8("label_122"));
        label_122->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_20->addWidget(label_122, 5, 1, 1, 1);

        label_118 = new QLabel(groupCheck_clouds_plane_shape);
        label_118->setObjectName(QString::fromUtf8("label_118"));
        label_118->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_20->addWidget(label_118, 2, 1, 1, 1);

        label_115 = new QLabel(groupCheck_clouds_plane_shape);
        label_115->setObjectName(QString::fromUtf8("label_115"));

        gridLayout_20->addWidget(label_115, 0, 0, 1, 1);

        vect3_clouds_center_x = new MyLineEdit(groupCheck_clouds_plane_shape);
        vect3_clouds_center_x->setObjectName(QString::fromUtf8("vect3_clouds_center_x"));

        gridLayout_20->addWidget(vect3_clouds_center_x, 1, 2, 1, 1);

        spinboxd3_clouds_rotation_y = new MyDoubleSpinBox(groupCheck_clouds_plane_shape);
        spinboxd3_clouds_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_clouds_rotation_y"));
        sizePolicy.setHeightForWidth(spinboxd3_clouds_rotation_y->sizePolicy().hasHeightForWidth());
        spinboxd3_clouds_rotation_y->setSizePolicy(sizePolicy);
        spinboxd3_clouds_rotation_y->setAccelerated(true);
        spinboxd3_clouds_rotation_y->setDecimals(2);
        spinboxd3_clouds_rotation_y->setMinimum(-180.000000000000000);
        spinboxd3_clouds_rotation_y->setMaximum(180.000000000000000);
        spinboxd3_clouds_rotation_y->setSingleStep(1.000000000000000);

        gridLayout_20->addWidget(spinboxd3_clouds_rotation_y, 5, 2, 1, 1);

        label_123 = new QLabel(groupCheck_clouds_plane_shape);
        label_123->setObjectName(QString::fromUtf8("label_123"));
        label_123->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_20->addWidget(label_123, 6, 1, 1, 1);

        spinboxd3_clouds_rotation_x = new MyDoubleSpinBox(groupCheck_clouds_plane_shape);
        spinboxd3_clouds_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_clouds_rotation_x"));
        sizePolicy.setHeightForWidth(spinboxd3_clouds_rotation_x->sizePolicy().hasHeightForWidth());
        spinboxd3_clouds_rotation_x->setSizePolicy(sizePolicy);
        spinboxd3_clouds_rotation_x->setAccelerated(true);
        spinboxd3_clouds_rotation_x->setDecimals(2);
        spinboxd3_clouds_rotation_x->setMinimum(-180.000000000000000);
        spinboxd3_clouds_rotation_x->setMaximum(180.000000000000000);
        spinboxd3_clouds_rotation_x->setSingleStep(1.000000000000000);

        gridLayout_20->addWidget(spinboxd3_clouds_rotation_x, 4, 2, 1, 1);

        label_117 = new QLabel(groupCheck_clouds_plane_shape);
        label_117->setObjectName(QString::fromUtf8("label_117"));
        label_117->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_20->addWidget(label_117, 1, 1, 1, 1);

        vect3_clouds_center_y = new MyLineEdit(groupCheck_clouds_plane_shape);
        vect3_clouds_center_y->setObjectName(QString::fromUtf8("vect3_clouds_center_y"));

        gridLayout_20->addWidget(vect3_clouds_center_y, 2, 2, 1, 1);

        logedit_clouds_height = new MyLineEdit(groupCheck_clouds_plane_shape);
        logedit_clouds_height->setObjectName(QString::fromUtf8("logedit_clouds_height"));

        gridLayout_20->addWidget(logedit_clouds_height, 0, 2, 1, 1);


        verticalLayout_7->addLayout(gridLayout_20);


        verticalLayout_6->addWidget(groupCheck_clouds_plane_shape);

        groupCheck_clouds_distance_mode = new MyGroupBox(groupCheck_clouds_enable);
        groupCheck_clouds_distance_mode->setObjectName(QString::fromUtf8("groupCheck_clouds_distance_mode"));
        groupCheck_clouds_distance_mode->setCheckable(true);
        verticalLayout_13 = new QVBoxLayout(groupCheck_clouds_distance_mode);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(2, 2, 2, 2);
        gridLayout_21 = new QGridLayout();
        gridLayout_21->setSpacing(2);
        gridLayout_21->setObjectName(QString::fromUtf8("gridLayout_21"));
        label_125 = new QLabel(groupCheck_clouds_distance_mode);
        label_125->setObjectName(QString::fromUtf8("label_125"));

        gridLayout_21->addWidget(label_125, 0, 0, 1, 1);

        logedit_clouds_distance = new MyLineEdit(groupCheck_clouds_distance_mode);
        logedit_clouds_distance->setObjectName(QString::fromUtf8("logedit_clouds_distance"));

        gridLayout_21->addWidget(logedit_clouds_distance, 0, 1, 1, 1);

        label_126 = new QLabel(groupCheck_clouds_distance_mode);
        label_126->setObjectName(QString::fromUtf8("label_126"));

        gridLayout_21->addWidget(label_126, 1, 0, 1, 1);

        logedit_clouds_distance_layer = new MyLineEdit(groupCheck_clouds_distance_mode);
        logedit_clouds_distance_layer->setObjectName(QString::fromUtf8("logedit_clouds_distance_layer"));

        gridLayout_21->addWidget(logedit_clouds_distance_layer, 1, 1, 1, 1);


        verticalLayout_13->addLayout(gridLayout_21);


        verticalLayout_6->addWidget(groupCheck_clouds_distance_mode);

        groupBox = new QGroupBox(groupCheck_clouds_enable);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_14 = new QVBoxLayout(groupBox);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(2, 2, 2, 2);
        gridLayout_22 = new QGridLayout();
        gridLayout_22->setSpacing(2);
        gridLayout_22->setObjectName(QString::fromUtf8("gridLayout_22"));
        logedit_clouds_DE_approaching = new MyLineEdit(groupBox);
        logedit_clouds_DE_approaching->setObjectName(QString::fromUtf8("logedit_clouds_DE_approaching"));

        gridLayout_22->addWidget(logedit_clouds_DE_approaching, 1, 1, 1, 1);

        label_128 = new QLabel(groupBox);
        label_128->setObjectName(QString::fromUtf8("label_128"));

        gridLayout_22->addWidget(label_128, 0, 0, 1, 1);

        logedit_clouds_detail_accuracy = new MyLineEdit(groupBox);
        logedit_clouds_detail_accuracy->setObjectName(QString::fromUtf8("logedit_clouds_detail_accuracy"));

        gridLayout_22->addWidget(logedit_clouds_detail_accuracy, 0, 1, 1, 1);

        label_129 = new QLabel(groupBox);
        label_129->setObjectName(QString::fromUtf8("label_129"));

        gridLayout_22->addWidget(label_129, 1, 0, 1, 1);

        label_130 = new QLabel(groupBox);
        label_130->setObjectName(QString::fromUtf8("label_130"));

        gridLayout_22->addWidget(label_130, 2, 0, 1, 1);

        logedit_clouds_DE_multiplier = new MyLineEdit(groupBox);
        logedit_clouds_DE_multiplier->setObjectName(QString::fromUtf8("logedit_clouds_DE_multiplier"));

        gridLayout_22->addWidget(logedit_clouds_DE_multiplier, 2, 1, 1, 1);


        verticalLayout_14->addLayout(gridLayout_22);


        verticalLayout_6->addWidget(groupBox);


        verticalLayout_35->addWidget(groupCheck_clouds_enable);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_35->addItem(verticalSpacer_4);

        scrollArea_8->setWidget(scrollAreaWidgetContents_9);

        verticalLayout_65->addWidget(scrollArea_8);


        retranslateUi(cEffectsVolumetricTab);

        QMetaObject::connectSlotsByName(cEffectsVolumetricTab);
    } // setupUi

    void retranslateUi(QWidget *cEffectsVolumetricTab)
    {
        pushButton_local_load_3->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Laden", nullptr));
        pushButton_local_save_3->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Opslaan", nullptr));
        pushButton_local_reset_3->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Reset", nullptr));
        pushButton_local_randomize_3->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Randomize", nullptr));
#if QT_CONFIG(tooltip)
        logedit_volumetric_light_DE_Factor->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>This value controls the quality of the volumetric light effect.  The step for volumetric light is calculated in each iteration as: </p><p>step = DE * DE_FACTOR[global] * DE_FACTOR[volumetric].</p><p>A higher value gives a faster render but of poorer quality.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_custom_step_multiplier->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Custom DE Step multiplier\n"
"for volumetric effects:", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_basic_fog_enabled->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Uniform fog with constant density throughout space.</p><p>In the <b>Full OpenCL</b> engine, enabling/disabling basic fog is instant (runtime toggle, no kernel recompile).</p><p>Example:</p><p><img src=\":/tooltips/tooltips_images/image - shader - fog.jpeg\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_basic_fog_enabled->setTitle(QCoreApplication::translate("cEffectsVolumetricTab", "Basic fog", nullptr));
#if QT_CONFIG(tooltip)
        logedit_basic_fog_visibility->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Visibility distance of fog. Visibility can be set by using '<span style=\" font-style:italic;\">Set visibility distance by mouse'</span> button</p><p>Lower values produce denser fog,</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_basic_fog_primitive->setItemText(0, QCoreApplication::translate("cEffectsVolumetricTab", "None", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_basic_fog_primitive->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Selects the geometric primitive used to define the spatial boundaries of basic fog. The chosen shape (such as box, sphere, or other available primitives) determines where in the scene the basic fog effect will be applied, allowing for precise control over the fog\342\200\231s location and extent.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_63->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Visibility distance:", nullptr));
        label_64->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Kleur:", nullptr));
        label_72->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Shape from primitive:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_basic_fog_color->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Color of fog effect</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_basic_fog_color->setProperty("text", QVariant(QCoreApplication::translate("cEffectsVolumetricTab", "PushButton", nullptr)));
#if QT_CONFIG(tooltip)
        checkBox_basic_fog_cast_shadows->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Enables full shadow interaction for basic fog. </p><p>When activated, basic fog volumes will both cast shadows onto scene geometry and receive shadows from other objects and light sources. </p><p>This affects how light propagates through the fog, allowing occlusion effects and shadowed regions within and behind fog areas. </p><p>The result is a more physically accurate and visually integrated rendering of fog, though enabling this may increase computational complexity and rendering time due to additional light and shadow sampling.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_basic_fog_cast_shadows->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Cast / receive shadows", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_set_fog_by_mouse->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Sets visibility distance using mouse pointer. Point the object which should be the farthest visible.</p><p>After using it don't forget to change <span style=\" font-style:italic;\">Navigation</span> / <span style=\" font-style:italic;\">Mouse click function</span> to continue work with the camera.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_set_fog_by_mouse->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Set visibility distance by mouse", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_glow_enabled->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Glow effect based on ray-marching step count</p><p>Example:</p><p><img src=\":/tooltips/tooltips_images/image - shader - glow.jpeg\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_glow_enabled->setTitle(QCoreApplication::translate("cEffectsVolumetricTab", "&Glow", nullptr));
        label_88->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Color #1:", nullptr));
        label_89->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Color #2:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_glow_intensity->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Intensity of effect</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_87->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Intensiteit:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_glow_color_1->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Color of dark areas</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_glow_color_1->setProperty("text", QVariant(QCoreApplication::translate("cEffectsVolumetricTab", "PushButton", nullptr)));
#if QT_CONFIG(tooltip)
        colorButton_glow_color_2->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Color of bright areas</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_glow_color_2->setProperty("text", QVariant(QCoreApplication::translate("cEffectsVolumetricTab", "PushButton", nullptr)));
#if QT_CONFIG(tooltip)
        groupCheck_volumetric_fog_enabled->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Fog density depends on distance from the fractal surface.</p><p><b>Note:</b> enabling volumetric fog in OpenCL compiles extra shader code and may trigger a kernel rebuild.</p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>High distance values</p></td><td><p>Low distance values</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/image - shader - distance glow.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - shader - distance glow 2.jpeg\"/></p></td></tr></table></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_volumetric_fog_enabled->setTitle(QCoreApplication::translate("cEffectsVolumetricTab", "Fog based on dis&tance", nullptr));
#if QT_CONFIG(tooltip)
        button_calculateFog->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Calculates optimal settings for fog effect.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        button_calculateFog->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Optimal distances calculation", nullptr));
        toolButton_fog_distance_double->setText(QCoreApplication::translate("cEffectsVolumetricTab", "x2", nullptr));
        toolButton_fog_distance_half->setText(QCoreApplication::translate("cEffectsVolumetricTab", "\303\2672", nullptr));
        label_volumetric_fog_mode->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Fog falloff mode:", nullptr));
#if QT_CONFIG(tooltip)
        label_volumetric_fog_mode->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Controls how volumetric fog density varies in space. Surface shell wraps the fractal (default). Other modes use ray depth, world height, camera distance, or a hybrid blend.", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_volumetric_fog_mode->setItemText(0, QCoreApplication::translate("cEffectsVolumetricTab", "Surface shell", nullptr));
        comboBox_volumetric_fog_mode->setItemText(1, QCoreApplication::translate("cEffectsVolumetricTab", "Exponential depth", nullptr));
        comboBox_volumetric_fog_mode->setItemText(2, QCoreApplication::translate("cEffectsVolumetricTab", "Height fog", nullptr));
        comboBox_volumetric_fog_mode->setItemText(3, QCoreApplication::translate("cEffectsVolumetricTab", "Camera distance", nullptr));
        comboBox_volumetric_fog_mode->setItemText(4, QCoreApplication::translate("cEffectsVolumetricTab", "Hybrid shell + depth", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_volumetric_fog_mode->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Surface shell = Lorentzian around DE surface. Exponential depth = uniform haze along the view ray. Height fog = denser below a Y threshold. Camera distance = fog increases with distance from camera. Hybrid = 50/50 shell + depth.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBox_voxel_fog_cache_enabled->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Precomputes a coarse 3D light cache for volumetric fog. Reduces per-step light marching cost in scenes with many lights (approximate, no volumetric shadows).", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_voxel_fog_cache_enabled->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Enable voxel fog light cache", nullptr));
        label_voxel_fog_cache_resolution->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Cache resolution:", nullptr));
        label_75->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Shape from primitive:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fog_color_2->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Color of fog which is used between distance #1  and distance #2</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fog_color_2->setProperty("text", QVariant(QCoreApplication::translate("cEffectsVolumetricTab", "PushButton", nullptr)));
        label_100->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Distance from fractal surface:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_volumetric_fog_density->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Density of fog. Higher values produce denser fog. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_66->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Color #1:", nullptr));
        label_65->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Density:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_volumetric_fog_colour_2_distance->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Maximum fog distance of color #2 from the fractal surface, and minimum fog distance for color #3.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_78->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Color #2:", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_distance_fog_shadows->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Enables full shadow interaction for basic fog. </p><p>When activated, basic fog volumes will both cast shadows onto scene geometry and receive shadows from other objects and light sources. </p><p>This affects how light propagates through the fog, allowing occlusion effects and shadowed regions within and behind fog areas. </p><p>The result is a more physically accurate and visually integrated rendering of fog, though enabling this may increase computational complexity and rendering time due to additional light and shadow sampling.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_distance_fog_shadows->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Cast/receive shadows", nullptr));
#if QT_CONFIG(tooltip)
        logedit_volumetric_fog_colour_1_distance->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Maximum fog distance of color #1 from the fractal surface, and minimum fog distance for color #2.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_79->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Color #3:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_volumetric_fog_distance_factor->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Adjusts the density of fog based on  the  distance from the fractal surface. Higher values produces fog which reaches further from the fractal surface.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_67->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Distance of color #1:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_fog_color_1->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Color of fog which is used from fractal surface to distance #1</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fog_color_1->setProperty("text", QVariant(QCoreApplication::translate("cEffectsVolumetricTab", "PushButton", nullptr)));
        label_76->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Distance of color #2:", nullptr));
        label_77->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Fog distance factor:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_volumetric_fog_distance_from_surface->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Adjusts the density of fog based on  the  distance from the fractal surface. Higher values produces fog which reaches further from the fractal surface.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_distance_fog_primitive->setItemText(0, QCoreApplication::translate("cEffectsVolumetricTab", "None", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_distance_fog_primitive->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Selects the geometric primitive used to define the spatial boundaries of basic fog. The chosen shape (such as box, sphere, or other available primitives) determines where in the scene the basic fog effect will be applied, allowing for precise control over the fog\342\200\231s location and extent.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        colorButton_fog_color_3->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Color of fog which is used farther than distance #2</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fog_color_3->setProperty("text", QVariant(QCoreApplication::translate("cEffectsVolumetricTab", "PushButton", nullptr)));
#if QT_CONFIG(tooltip)
        groupCheck_iteration_fog_enable->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Fog density depends on fractal iteration count \342\200\224 denser near high-iteration regions. Receives and casts shadows.</p><p>In the <b>Full OpenCL</b> engine, toggling iteration fog is instant (runtime toggle). Use <i>Auto Detect</i> or Render Settings \342\206\222 Auto Iteration Fog for one-click tuning.</p><p>Example with lights:<br/><img src=\":/tooltips/tooltips_images/image - shader - iterfog - lights.jpeg\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_iteration_fog_enable->setTitle(QCoreApplication::translate("cEffectsVolumetricTab", "Fog based on iteration co&unt", nullptr));
        label_86->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Color #3:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_iteration_fog_opacity_trim->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>There is no fog in volume where iteration count is lower than this value. When this parameter is high then fog is only just by fractal surface.</p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>trim = 4</p></td><td><p>trim = 6</p></td><td><p>trim = 8</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/image - shader - iterfog - 4 - 16000.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - shader - iterfog - 6 - 30000.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - shader - iterfog - 8 - 40000.jpg\"/></p></td></tr></table></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_iteration_fog_opacity_trim->setPrefix(QString());
        spinbox_iteration_fog_opacity_trim->setSuffix(QString());
#if QT_CONFIG(tooltip)
        spinbox_iteration_fog_color_1_maxiter->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Color #1 is used for iteration count lower than this value</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_iteration_fog_color_1_maxiter->setPrefix(QString());
        spinbox_iteration_fog_color_1_maxiter->setSuffix(QString());
        label_85->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Color #2:", nullptr));
        label_80->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Opacity:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_iteration_fog_opacity_trim_high->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>There is no fog in volume where iteration count is lower than this value. When this parameter is high then fog is only just by fractal surface.</p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>trim = 4</p></td><td><p>trim = 6</p></td><td><p>trim = 8</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/image - shader - iterfog - 4 - 16000.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - shader - iterfog - 6 - 30000.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - shader - iterfog - 8 - 40000.jpg\"/></p></td></tr></table></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_iteration_fog_opacity_trim_high->setPrefix(QString());
        spinbox_iteration_fog_opacity_trim_high->setSuffix(QString());
        label_101->setText(QCoreApplication::translate("cEffectsVolumetricTab", "High iterations trim:", nullptr));
        label_81->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Low iterations trim:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_iteration_fog_brightness_boost->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>This parameter can be used to increase brightness of fog illuminated by auxiliary light sources.</p><p>In Mandelbulber version &lt;= 2.12 this value was hardcoded and default value was 100. </p><p>When brightness boost is 1.0 then there is correct proportion of illuminating fractal surface and fog.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_iteration_fog_brightness_boost->setPrefix(QString());
        spinbox_iteration_fog_brightness_boost->setSuffix(QString());
#if QT_CONFIG(tooltip)
        colorButton_iteration_fog_color_1->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Color #1 of fog effect</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_iteration_fog_color_1->setProperty("text", QVariant(QCoreApplication::translate("cEffectsVolumetricTab", "PushButton", nullptr)));
#if QT_CONFIG(tooltip)
        checkBox_iteration_fog_shadows->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Enables full shadow interaction for basic fog. </p><p>When activated, basic fog volumes will both cast shadows onto scene geometry and receive shadows from other objects and light sources. </p><p>This affects how light propagates through the fog, allowing occlusion effects and shadowed regions within and behind fog areas. </p><p>The result is a more physically accurate and visually integrated rendering of fog, though enabling this may increase computational complexity and rendering time due to additional light and shadow sampling.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_iteration_fog_shadows->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Cast/receive shadows", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_iteration_fog_color_2->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Color #2 of fog effect</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_iteration_fog_color_2->setProperty("text", QVariant(QCoreApplication::translate("cEffectsVolumetricTab", "PushButton", nullptr)));
#if QT_CONFIG(tooltip)
        spinbox_iteration_fog_color_2_maxiter->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Color #2 is used for iteration count lower than this value. </p><p>Color #3 is used for iteration count greater than this value.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_iteration_fog_color_2_maxiter->setPrefix(QString());
        spinbox_iteration_fog_color_2_maxiter->setSuffix(QString());
        label_83->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Max iter. for color#2:", nullptr));
        label_82->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Max iter. for color#1:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_iteration_fog_color_3->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Color #3 of fog effect</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_iteration_fog_color_3->setProperty("text", QVariant(QCoreApplication::translate("cEffectsVolumetricTab", "PushButton", nullptr)));
        label_99->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Brightness boost.\n"
"Set 100 to keep compatibility with version <=2.12", nullptr));
#if QT_CONFIG(tooltip)
        logedit_iteration_fog_opacity->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Opacity of fog. Higher value gives denser fog.<br/></p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>opacity = 1000</p></td><td><p>opacity = 4000</p></td><td><p>opacity = 16000</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/image - shader - iterfog - 4 - 1000.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - shader - iterfog - 4 - 4000.jpg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - shader - iterfog - 4 - 16000.jpg\"/></p></td></tr></table></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_84->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Color #1:", nullptr));
        label_74->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Shape from primitive:", nullptr));
        comboBox_iteration_fog_primitive->setItemText(0, QCoreApplication::translate("cEffectsVolumetricTab", "None", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_iteration_fog_primitive->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Selects the geometric primitive used to define the spatial boundaries of basic fog. The chosen shape (such as box, sphere, or other available primitives) determines where in the scene the basic fog effect will be applied, allowing for precise control over the fog\342\200\231s location and extent.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        pushButton_autoFog_iteration->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Probe the current view and calculate optimal iteration fog parameters (trim, opacity, color thresholds). Uses fractal-type detection and percentile statistics. Adjust bias spinboxes below to fine-tune results.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_autoFog_iteration->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Auto Detect Iteration Fog", nullptr));
        label_autoFogOpacityScale->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Auto-fog opacity scale:", nullptr));
#if QT_CONFIG(tooltip)
        label_autoFogOpacityScale->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Global multiplier applied to auto-calculated fog opacity. 1.0 = use probe result as-is.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinbox_auto_fog_opacity_scale->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Multiplier for auto-calculated fog opacity. Default 1.0 = use calculated value. Increase if fog is too faint, decrease if too dense.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_autoFogTrimBias->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Trim bias:", nullptr));
#if QT_CONFIG(tooltip)
        label_autoFogTrimBias->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Added to auto-calculated lower trim. Negative = fog starts at lower iterations; positive = tighter around the surface.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinbox_auto_fog_trim_bias->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Offset for auto-calculated trim. Negative = show more low-iteration fog. Positive = cut off more low iterations. Default 0.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_autoFogTrimHighBias->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Trim high bias:", nullptr));
#if QT_CONFIG(tooltip)
        label_autoFogTrimHighBias->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Added to auto-calculated upper trim. Controls where high-iteration fog saturates.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinbox_auto_fog_trim_high_bias->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Offset for auto-calculated trim high. Negative = softer fall-off. Positive = harder fall-off at high iterations. Default 0.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_autoFogColorSpread->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Color spread:", nullptr));
#if QT_CONFIG(tooltip)
        label_autoFogColorSpread->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Scales the spacing between iteration-fog color thresholds after auto-tuning.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinbox_auto_fog_color_spread->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Multiplier for color maxiter spread. <1 = colors closer together, >1 = colors more spread out. Default 1.0.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_autoFogBoostScale->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Boost scale:", nullptr));
#if QT_CONFIG(tooltip)
        label_autoFogBoostScale->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Scales the auto-calculated fog brightness boost applied to lit fog regions.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinbox_auto_fog_boost_scale->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Multiplier for auto-calculated brightness boost. Default 1.0 = use calculated value. Increase for brighter fog, decrease for subtler fog.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        groupCheck_clouds_enable->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Procedural volumetric clouds along view rays, with per-light illumination and optional shadows. <b>Note:</b> enabling clouds in OpenCL compiles extra shader code and may trigger a kernel recompile. Use presets for safer starting values; tune density gamma and softness for edge quality.", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_clouds_enable->setTitle(QCoreApplication::translate("cEffectsVolumetricTab", "Clouds", nullptr));
        label_clouds_preset->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Preset:", nullptr));
#if QT_CONFIG(tooltip)
        label_clouds_preset->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Starting styles: Soft Mist (light haze), Volumetric Clouds (balanced), Hard Fractal Smoke (sharp edges), Nebula Dust (sparse colored wisps).", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_clouds_preset->setItemText(0, QCoreApplication::translate("cEffectsVolumetricTab", "Soft Mist", nullptr));
        comboBox_clouds_preset->setItemText(1, QCoreApplication::translate("cEffectsVolumetricTab", "Volumetric Clouds", nullptr));
        comboBox_clouds_preset->setItemText(2, QCoreApplication::translate("cEffectsVolumetricTab", "Hard Fractal Smoke", nullptr));
        comboBox_clouds_preset->setItemText(3, QCoreApplication::translate("cEffectsVolumetricTab", "Nebula Dust", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_clouds_preset->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Cloud style presets with tuned opacity, sharpness, gamma, and softness. Select a style and click Apply \342\200\224 does not change your random seed.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        pushButton_clouds_apply_preset->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Apply the selected cloud preset to opacity, sharpness, density gamma, softness, and related parameters.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_clouds_apply_preset->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Apply", nullptr));
        label_124->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Color", nullptr));
#if QT_CONFIG(tooltip)
        spinboxInt_clouds_noise_iterations->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Number of noise octaves used to generate cloud density. </p><p>Higher values add finer, more turbulent detail and richer structure, but increase computation time due to additional noise sampling. Typical useful range: 5\342\200\22312. Adjust together with Cloud Period and Detail Accuracy; higher iterations with a small period produce very high-frequency features. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_110->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Noise iterations:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_clouds_density->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Base density/coverage of the volumetric cloud field (0\342\200\2231). Higher values produce thicker, more continuous clouds; lower values yield sparse, broken clouds. </p><p>Tune together with Cloud Opacity (overall strength), Period (scale), and Noise Iterations (detail). Typical range: 0.15\342\200\2230.60; 0 = clear, 1 = near-solid overcast.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_clouds_density->setPrefix(QString());
        spinbox_clouds_density->setSuffix(QString());
        label_114->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Period:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_clouds_period->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Spatial scale of the procedural cloud noise (period, in scene units). Larger values yield bigger, smoother cloud structures; smaller values create finer, more turbulent detail. </p><p>Interacts with Noise Iterations and Detail Accuracy; very small periods may increase render time and require higher Detail Accuracy to avoid aliasing.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_113->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Density:", nullptr));
#if QT_CONFIG(tooltip)
        spinboxInt_clouds_random_seed->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Random seed for the procedural noise field driving clouds. Changing it generates a different (statistically equivalent) cloud layout/phase without altering density, scale (period), or octave structure. Keep constant for deterministic, reproducible renders and animations; vary to explore alternative compositions. Integer value, typically 0\342\200\2231,000,000.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinbox_clouds_ambient_light->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Ambient light contribution for clouds (0\342\200\2231). </p><p>Blends uniform ambient illumination into cloud lighting: </p><p>0 = only direct lights with full shadow contrast; </p><p>1 = fully ambient, very soft/flat shadows. </p><p>Increase to brighten interiors and soften shadows; decrease for crisper shading. </p><p>Does not affect opacity. </p><p>Typical range: 0.05\342\200\2230.30.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_clouds_ambient_light->setPrefix(QString());
        spinbox_clouds_ambient_light->setSuffix(QString());
        label_144->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Visible light and trap light boost:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_clouds_lights_boost->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Boosts intensity of visible light beams and orbit\342\200\221trap \342\200\234fake lights\342\200\235 inside clouds. Scales their contribution with cloud density/opacity: higher values make light shafts brighter and more pronounced, especially in dense regions. </p><p>Does not affect direct/ambient light or cloud opacity. </p><p>0 = no boost. Typical range 0\342\200\2232; use higher for strong god\342\200\221ray effects (may increase noise).</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_clouds_color->setProperty("text", QVariant(QCoreApplication::translate("cEffectsVolumetricTab", "PushButton", nullptr)));
#if QT_CONFIG(tooltip)
        pushButton_clouds_randomize->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Generates a new random seed for the procedural cloud noise, changing the cloud pattern without altering density, period, or noise iterations. </p><p>Click repeatedly to explore variations; keep the chosen seed fixed for reproducible renders and animations.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_clouds_randomize->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Randomize", nullptr));
        label_112->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Opacity:", nullptr));
        label_111->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Random seed:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_clouds_opacity->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Global multiplier for volumetric cloud opacity. Typical range 0.5\342\200\2235. Default 2.0. Lower = more transparent clouds.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_143->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Ambient light:", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_clouds_cast_shadows->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Enable cloud shadowing. When checked, clouds receive and cast shadows from scene lights, giving more realistic occlusion and higher contrast; this is slower. When unchecked, faster shading without shadows. Tip: raise Clouds Ambient Light to soften shadows; use Lights Boost to emphasize light shafts.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_clouds_cast_shadows->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Receive shadows", nullptr));
        label_clouds_density_gamma->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Density gamma:", nullptr));
#if QT_CONFIG(tooltip)
        label_clouds_density_gamma->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Remaps cloud density before opacity. <1 = more low-density wisps; >1 = punchier cores. Default 1.0.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinbox_clouds_density_gamma->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Power curve on cloud density (0.3\342\200\2233.0). Lower = softer, more transparent clouds; higher = denser, more contrasty volumes.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_clouds_softness->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Density softness:", nullptr));
#if QT_CONFIG(tooltip)
        label_clouds_softness->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Smoothstep blend between empty space and full density. Higher = softer cloud edges; lower = harder transitions.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinbox_clouds_softness->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Edge softness for cloud density (0.05\342\200\2231.0). Works with density gamma to control how gradual cloud boundaries appear.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_clouds_adaptive_detail->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Adaptive cloud stepping", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_clouds_adaptive_detail->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Varies ray step size with local cloud density \342\200\224 larger steps in empty regions, smaller steps inside clouds. Faster with similar visual quality; disable for maximum uniformity at higher cost.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        groupCheck_clouds_sharp_edges->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Enable hard\342\200\221edged clouds by sharpening the density threshold. When on, use Sharpness to control edge steepness: higher values produce crisper, thinner transitions; lower values keep edges softer. </p><p>Great for dramatic silhouettes and pronounced shadows. </p><p>May increase noise/aliasing\342\200\224raise Clouds Noise Iterations or Detail Accuracy if needed.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_clouds_sharp_edges->setTitle(QCoreApplication::translate("cEffectsVolumetricTab", "Sharp edges", nullptr));
        label_142->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Sharpness:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_clouds_sharpness->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Edge steepness for Sharp edges clouds. Higher values sharpen the density threshold (crisper, thinner cloud contours); lower values keep transitions soft. </p><p>Very high values may introduce aliasing/noise\342\200\224consider increasing Clouds Noise Iterations or Clouds Detail Accuracy.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_clouds_sharpness->setPrefix(QString());
        spinbox_clouds_sharpness->setSuffix(QString());
        label_140->setText(QCoreApplication::translate("cEffectsVolumetricTab", "y", nullptr));
        label_141->setText(QCoreApplication::translate("cEffectsVolumetricTab", "z", nullptr));
#if QT_CONFIG(tooltip)
        vect3_clouds_speed_x->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>X-axis drift speed of the clouds. Controls how fast the noise field moves along +X over time (animation). </p><p>Positive = moves toward +X, negative = toward \342\210\222X; 0 = no motion. </p><p>Effective speed scales with Clouds Period. </p><p>Use small values (e.g., \302\2610.001 to \302\2610.05). </p><p>Combine with Y/Z for wind direction.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_135->setText(QCoreApplication::translate("cEffectsVolumetricTab", "x", nullptr));
        label_133->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Clouds movement speed:", nullptr));
        label_145->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Shape from primitive:", nullptr));
        comboBox_clouds_primitive->setItemText(0, QCoreApplication::translate("cEffectsVolumetricTab", "None", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_clouds_primitive->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Selects the geometric primitive used to define the spatial boundaries of basic fog. The chosen shape (such as box, sphere, or other available primitives) determines where in the scene the basic fog effect will be applied, allowing for precise control over the fog\342\200\231s location and extent.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        groupCheck_clouds_plane_shape->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "<html><head/><body><p>Enable planar cloud layer. Constrains clouds to a band around a rotated plane with a soft vertical falloff. </p><p>Use Height to set layer thickness, and Center/Rotation to position and tilt the layer. </p><p>Useful for horizon-like cloud sheets and can speed up rendering by limiting the cloud volume.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_clouds_plane_shape->setTitle(QCoreApplication::translate("cEffectsVolumetricTab", "Plane shape", nullptr));
        label_121->setText(QCoreApplication::translate("cEffectsVolumetricTab", "alpha", nullptr));
        spinboxd3_clouds_rotation_z->setPrefix(QString());
        spinboxd3_clouds_rotation_z->setSuffix(QString());
        label_116->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Clouds center:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_clouds_center_z->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Vertical position (Z axis) of the center of the clouds volume relative to the fractal.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_120->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Geometry rotation:", nullptr));
        label_119->setText(QCoreApplication::translate("cEffectsVolumetricTab", "z", nullptr));
        label_122->setText(QCoreApplication::translate("cEffectsVolumetricTab", "beta", nullptr));
        label_118->setText(QCoreApplication::translate("cEffectsVolumetricTab", "y", nullptr));
        label_115->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Clouds layer height:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_clouds_center_x->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Vertical position (X axis) of the center of the clouds volume relative to the fractal.", nullptr));
#endif // QT_CONFIG(tooltip)
        spinboxd3_clouds_rotation_y->setPrefix(QString());
        spinboxd3_clouds_rotation_y->setSuffix(QString());
        label_123->setText(QCoreApplication::translate("cEffectsVolumetricTab", "gamma", nullptr));
        spinboxd3_clouds_rotation_x->setPrefix(QString());
        spinboxd3_clouds_rotation_x->setSuffix(QString());
        label_117->setText(QCoreApplication::translate("cEffectsVolumetricTab", "x", nullptr));
#if QT_CONFIG(tooltip)
        vect3_clouds_center_y->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Vertical position (Y axis) of the center of the clouds volume relative to the fractal.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_clouds_height->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Height above the fractal base at which the main cloud layer appears.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        groupCheck_clouds_distance_mode->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Generate clouds which are within specified distance from the fractal.", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_clouds_distance_mode->setTitle(QCoreApplication::translate("cEffectsVolumetricTab", "Clouds at distance from fractal", nullptr));
        label_125->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Distance from fractal", nullptr));
#if QT_CONFIG(tooltip)
        logedit_clouds_distance->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Distance from the fractal surface to the start of the clouds volume.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_126->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Clouds layer height", nullptr));
#if QT_CONFIG(tooltip)
        logedit_clouds_distance_layer->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Vertical thickness of the clouds layer, controlling how deep clouds extend from their base.", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox->setTitle(QCoreApplication::translate("cEffectsVolumetricTab", "Accuracy control", nullptr));
#if QT_CONFIG(tooltip)
        logedit_clouds_DE_approaching->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Step size for distance estimation when approaching the clouds; lower values increase accuracy but reduce performance.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_128->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Details accuracy", nullptr));
#if QT_CONFIG(tooltip)
        logedit_clouds_detail_accuracy->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Controls the rendering accuracy for fine details in the clouds; higher values improve detail but increase render time.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_129->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Approaching DE multiplier", nullptr));
        label_130->setText(QCoreApplication::translate("cEffectsVolumetricTab", "Clouds DE multiplier", nullptr));
#if QT_CONFIG(tooltip)
        logedit_clouds_DE_multiplier->setToolTip(QCoreApplication::translate("cEffectsVolumetricTab", "Multiplier for the distance estimation step size in clouds rendering. Increasing this value can speed up rendering but may reduce accuracy and detail in cloud boundaries. Lower values provide more precise results at the cost of performance.", nullptr));
#endif // QT_CONFIG(tooltip)
        (void)cEffectsVolumetricTab;
    } // retranslateUi

};

namespace Ui {
    class cEffectsVolumetricTab: public Ui_cEffectsVolumetricTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EFFECTS_VOLUMETRIC_TAB_H
