/********************************************************************************
** Form generated from reading UI file 'dock_image_adjustments.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCK_IMAGE_ADJUSTMENTS_H
#define UI_DOCK_IMAGE_ADJUSTMENTS_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "buton_load_settings_from_widget.h"
#include "buton_reset_settings_from_widget.h"
#include "buton_save_settings_from_widget.h"
#include "my_check_box.h"
#include "my_combo_box.h"
#include "my_double_spin_box.h"
#include "my_group_box.h"
#include "my_line_edit.h"
#include "my_spin_box.h"

QT_BEGIN_NAMESPACE

class Ui_cDockImageAdjustments
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    cButtonLoadSettingsFromWidget *pushButton_local_load_2;
    cButtonSaveSettingsFromWidget *pushButton_local_save_2;
    cButtonResetSettingsFromWidget *pushButton_local_reset_2;
    QSpacerItem *horizontalSpacer_5;
    QGroupBox *groupBox_imageResolution;
    QVBoxLayout *verticalLayout_40;
    QGridLayout *gridLayout_18;
    QHBoxLayout *horizontalLayout_increase_decrease;
    QToolButton *pushButton_imagesize_increase;
    QToolButton *pushButton_imagesize_decrease;
    MySpinBox *spinboxInt_image_width;
    QLabel *label_101;
    MySpinBox *spinboxInt_image_height;
    QLabel *label_102;
    QLabel *label_100;
    MyComboBox *comboBox_image_proportion;
    MyGroupBox *groupCheck_antialiasing_enabled;
    QVBoxLayout *verticalLayout_148;
    QGridLayout *gridLayout_12;
    QLabel *label_antialiasingNumberOfSamples;
    MySpinBox *spinboxInt_antialiasing_size;
    MyComboBox *comboBox_antialiasing_ocl_depth;
    QLabel *label_antialiasing_depth;
    MyCheckBox *checkBox_antialiasing_adaptive;
    MyCheckBox *checkBox_connect_detail_level;
    QGroupBox *groupBox_presets;
    QVBoxLayout *verticalLayout_71;
    QGridLayout *gridLayout_32;
    QToolButton *toolButton_resolution_preset_1;
    QToolButton *toolButton_resolution_preset_2;
    QToolButton *toolButton_resolution_preset_9;
    QToolButton *toolButton_resolution_preset_3;
    QToolButton *toolButton_resolution_preset_4;
    QToolButton *toolButton_resolution_preset_5;
    QToolButton *toolButton_resolution_preset_6;
    QToolButton *toolButton_resolution_preset_7;
    QToolButton *toolButton_resolution_preset_8;
    MyGroupBox *groupCheck_stereo_enabled;
    QVBoxLayout *verticalLayout_147;
    QGridLayout *gridLayout_11;
    QLabel *label_69;
    MyComboBox *comboBox_stereo_mode;
    QLabel *label_70;
    MyCheckBox *checkBox_stereo_swap_eyes;
    QLabel *label_71;
    MyLineEdit *logedit_stereo_eye_distance;
    MyDoubleSpinBox *spinbox_stereo_infinite_correction;
    QPushButton *pushButton_optimal_distance_between_eyes;
    QGroupBox *groupBox_12;
    QVBoxLayout *verticalLayout_146;
    QGridLayout *gridLayout_34;
    QPushButton *pushButton_quality_preset_normal;
    QPushButton *pushButton_quality_preset_low;
    QPushButton *pushButton_quality_preset_high;
    QPushButton *pushButton_quality_preset_very_low;
    QGroupBox *groupBox_ImageAdjustments;
    QVBoxLayout *verticalLayout_20;
    QGridLayout *gridLayout;
    MyDoubleSpinBox *spinbox_contrast;
    MyDoubleSpinBox *spinbox_gamma;
    MyDoubleSpinBox *spinbox_brightness;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_45;
    QLabel *label_46;
    MyDoubleSpinBox *spinbox_saturation;
    MyCheckBox *checkBox_hdr;
    QPushButton *pushButton_apply_image_changes;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_58;
    QGridLayout *gridLayout_25;
    QLabel *label_54;
    MyLineEdit *logedit_fov;
    QLabel *label_126;
    MyComboBox *comboBox_perspective_type;
    MyCheckBox *checkBox_legacy_coordinate_system;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *cDockImageAdjustments)
    {
        if (cDockImageAdjustments->objectName().isEmpty())
            cDockImageAdjustments->setObjectName(QString::fromUtf8("cDockImageAdjustments"));
        cDockImageAdjustments->resize(338, 1257);
        verticalLayout = new QVBoxLayout(cDockImageAdjustments);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_local_load_2 = new cButtonLoadSettingsFromWidget(cDockImageAdjustments);
        pushButton_local_load_2->setObjectName(QString::fromUtf8("pushButton_local_load_2"));

        horizontalLayout_2->addWidget(pushButton_local_load_2);

        pushButton_local_save_2 = new cButtonSaveSettingsFromWidget(cDockImageAdjustments);
        pushButton_local_save_2->setObjectName(QString::fromUtf8("pushButton_local_save_2"));

        horizontalLayout_2->addWidget(pushButton_local_save_2);

        pushButton_local_reset_2 = new cButtonResetSettingsFromWidget(cDockImageAdjustments);
        pushButton_local_reset_2->setObjectName(QString::fromUtf8("pushButton_local_reset_2"));

        horizontalLayout_2->addWidget(pushButton_local_reset_2);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_2);

        groupBox_imageResolution = new QGroupBox(cDockImageAdjustments);
        groupBox_imageResolution->setObjectName(QString::fromUtf8("groupBox_imageResolution"));
        verticalLayout_40 = new QVBoxLayout(groupBox_imageResolution);
        verticalLayout_40->setSpacing(2);
        verticalLayout_40->setObjectName(QString::fromUtf8("verticalLayout_40"));
        verticalLayout_40->setContentsMargins(2, 2, 2, 2);
        gridLayout_18 = new QGridLayout();
        gridLayout_18->setSpacing(2);
        gridLayout_18->setObjectName(QString::fromUtf8("gridLayout_18"));
        horizontalLayout_increase_decrease = new QHBoxLayout();
        horizontalLayout_increase_decrease->setObjectName(QString::fromUtf8("horizontalLayout_increase_decrease"));
        pushButton_imagesize_increase = new QToolButton(groupBox_imageResolution);
        pushButton_imagesize_increase->setObjectName(QString::fromUtf8("pushButton_imagesize_increase"));

        horizontalLayout_increase_decrease->addWidget(pushButton_imagesize_increase);

        pushButton_imagesize_decrease = new QToolButton(groupBox_imageResolution);
        pushButton_imagesize_decrease->setObjectName(QString::fromUtf8("pushButton_imagesize_decrease"));

        horizontalLayout_increase_decrease->addWidget(pushButton_imagesize_decrease);


        gridLayout_18->addLayout(horizontalLayout_increase_decrease, 2, 2, 1, 1);

        spinboxInt_image_width = new MySpinBox(groupBox_imageResolution);
        spinboxInt_image_width->setObjectName(QString::fromUtf8("spinboxInt_image_width"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(spinboxInt_image_width->sizePolicy().hasHeightForWidth());
        spinboxInt_image_width->setSizePolicy(sizePolicy);
        spinboxInt_image_width->setMinimum(32);
        spinboxInt_image_width->setMaximum(65535);
        spinboxInt_image_width->setSingleStep(8);

        gridLayout_18->addWidget(spinboxInt_image_width, 0, 1, 1, 2);

        label_101 = new QLabel(groupBox_imageResolution);
        label_101->setObjectName(QString::fromUtf8("label_101"));

        gridLayout_18->addWidget(label_101, 1, 0, 1, 1);

        spinboxInt_image_height = new MySpinBox(groupBox_imageResolution);
        spinboxInt_image_height->setObjectName(QString::fromUtf8("spinboxInt_image_height"));
        sizePolicy.setHeightForWidth(spinboxInt_image_height->sizePolicy().hasHeightForWidth());
        spinboxInt_image_height->setSizePolicy(sizePolicy);
        spinboxInt_image_height->setMinimum(32);
        spinboxInt_image_height->setMaximum(65535);
        spinboxInt_image_height->setSingleStep(8);

        gridLayout_18->addWidget(spinboxInt_image_height, 1, 1, 1, 2);

        label_102 = new QLabel(groupBox_imageResolution);
        label_102->setObjectName(QString::fromUtf8("label_102"));

        gridLayout_18->addWidget(label_102, 2, 0, 1, 1);

        label_100 = new QLabel(groupBox_imageResolution);
        label_100->setObjectName(QString::fromUtf8("label_100"));

        gridLayout_18->addWidget(label_100, 0, 0, 1, 1);

        comboBox_image_proportion = new MyComboBox(groupBox_imageResolution);
        comboBox_image_proportion->addItem(QString());
        comboBox_image_proportion->addItem(QString());
        comboBox_image_proportion->addItem(QString());
        comboBox_image_proportion->addItem(QString());
        comboBox_image_proportion->addItem(QString());
        comboBox_image_proportion->addItem(QString());
        comboBox_image_proportion->addItem(QString());
        comboBox_image_proportion->setObjectName(QString::fromUtf8("comboBox_image_proportion"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox_image_proportion->sizePolicy().hasHeightForWidth());
        comboBox_image_proportion->setSizePolicy(sizePolicy1);

        gridLayout_18->addWidget(comboBox_image_proportion, 2, 1, 1, 1);


        verticalLayout_40->addLayout(gridLayout_18);

        groupCheck_antialiasing_enabled = new MyGroupBox(groupBox_imageResolution);
        groupCheck_antialiasing_enabled->setObjectName(QString::fromUtf8("groupCheck_antialiasing_enabled"));
        groupCheck_antialiasing_enabled->setCheckable(true);
        verticalLayout_148 = new QVBoxLayout(groupCheck_antialiasing_enabled);
        verticalLayout_148->setSpacing(2);
        verticalLayout_148->setObjectName(QString::fromUtf8("verticalLayout_148"));
        verticalLayout_148->setContentsMargins(2, 2, 2, 2);
        gridLayout_12 = new QGridLayout();
        gridLayout_12->setSpacing(2);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        label_antialiasingNumberOfSamples = new QLabel(groupCheck_antialiasing_enabled);
        label_antialiasingNumberOfSamples->setObjectName(QString::fromUtf8("label_antialiasingNumberOfSamples"));

        gridLayout_12->addWidget(label_antialiasingNumberOfSamples, 0, 0, 1, 1);

        spinboxInt_antialiasing_size = new MySpinBox(groupCheck_antialiasing_enabled);
        spinboxInt_antialiasing_size->setObjectName(QString::fromUtf8("spinboxInt_antialiasing_size"));
        sizePolicy.setHeightForWidth(spinboxInt_antialiasing_size->sizePolicy().hasHeightForWidth());
        spinboxInt_antialiasing_size->setSizePolicy(sizePolicy);
        spinboxInt_antialiasing_size->setMinimum(1);
        spinboxInt_antialiasing_size->setMaximum(10);
        spinboxInt_antialiasing_size->setSingleStep(1);

        gridLayout_12->addWidget(spinboxInt_antialiasing_size, 0, 1, 1, 1);

        comboBox_antialiasing_ocl_depth = new MyComboBox(groupCheck_antialiasing_enabled);
        comboBox_antialiasing_ocl_depth->addItem(QString());
        comboBox_antialiasing_ocl_depth->addItem(QString());
        comboBox_antialiasing_ocl_depth->addItem(QString());
        comboBox_antialiasing_ocl_depth->addItem(QString());
        comboBox_antialiasing_ocl_depth->addItem(QString());
        comboBox_antialiasing_ocl_depth->addItem(QString());
        comboBox_antialiasing_ocl_depth->setObjectName(QString::fromUtf8("comboBox_antialiasing_ocl_depth"));
        sizePolicy1.setHeightForWidth(comboBox_antialiasing_ocl_depth->sizePolicy().hasHeightForWidth());
        comboBox_antialiasing_ocl_depth->setSizePolicy(sizePolicy1);

        gridLayout_12->addWidget(comboBox_antialiasing_ocl_depth, 1, 1, 1, 1);

        label_antialiasing_depth = new QLabel(groupCheck_antialiasing_enabled);
        label_antialiasing_depth->setObjectName(QString::fromUtf8("label_antialiasing_depth"));
        label_antialiasing_depth->setEnabled(true);
        label_antialiasing_depth->setWordWrap(true);

        gridLayout_12->addWidget(label_antialiasing_depth, 1, 0, 1, 1);

        checkBox_antialiasing_adaptive = new MyCheckBox(groupCheck_antialiasing_enabled);
        checkBox_antialiasing_adaptive->setObjectName(QString::fromUtf8("checkBox_antialiasing_adaptive"));

        gridLayout_12->addWidget(checkBox_antialiasing_adaptive, 2, 0, 1, 2);


        verticalLayout_148->addLayout(gridLayout_12);


        verticalLayout_40->addWidget(groupCheck_antialiasing_enabled);

        checkBox_connect_detail_level = new MyCheckBox(groupBox_imageResolution);
        checkBox_connect_detail_level->setObjectName(QString::fromUtf8("checkBox_connect_detail_level"));

        verticalLayout_40->addWidget(checkBox_connect_detail_level);

        groupBox_presets = new QGroupBox(groupBox_imageResolution);
        groupBox_presets->setObjectName(QString::fromUtf8("groupBox_presets"));
        verticalLayout_71 = new QVBoxLayout(groupBox_presets);
        verticalLayout_71->setSpacing(2);
        verticalLayout_71->setObjectName(QString::fromUtf8("verticalLayout_71"));
        verticalLayout_71->setContentsMargins(2, 2, 2, 2);
        gridLayout_32 = new QGridLayout();
        gridLayout_32->setSpacing(2);
        gridLayout_32->setObjectName(QString::fromUtf8("gridLayout_32"));
        gridLayout_32->setContentsMargins(-1, 0, -1, -1);
        toolButton_resolution_preset_1 = new QToolButton(groupBox_presets);
        toolButton_resolution_preset_1->setObjectName(QString::fromUtf8("toolButton_resolution_preset_1"));
        sizePolicy.setHeightForWidth(toolButton_resolution_preset_1->sizePolicy().hasHeightForWidth());
        toolButton_resolution_preset_1->setSizePolicy(sizePolicy);

        gridLayout_32->addWidget(toolButton_resolution_preset_1, 0, 0, 1, 1);

        toolButton_resolution_preset_2 = new QToolButton(groupBox_presets);
        toolButton_resolution_preset_2->setObjectName(QString::fromUtf8("toolButton_resolution_preset_2"));
        sizePolicy.setHeightForWidth(toolButton_resolution_preset_2->sizePolicy().hasHeightForWidth());
        toolButton_resolution_preset_2->setSizePolicy(sizePolicy);

        gridLayout_32->addWidget(toolButton_resolution_preset_2, 0, 1, 1, 1);

        toolButton_resolution_preset_9 = new QToolButton(groupBox_presets);
        toolButton_resolution_preset_9->setObjectName(QString::fromUtf8("toolButton_resolution_preset_9"));
        sizePolicy.setHeightForWidth(toolButton_resolution_preset_9->sizePolicy().hasHeightForWidth());
        toolButton_resolution_preset_9->setSizePolicy(sizePolicy);

        gridLayout_32->addWidget(toolButton_resolution_preset_9, 2, 2, 1, 1);

        toolButton_resolution_preset_3 = new QToolButton(groupBox_presets);
        toolButton_resolution_preset_3->setObjectName(QString::fromUtf8("toolButton_resolution_preset_3"));
        sizePolicy.setHeightForWidth(toolButton_resolution_preset_3->sizePolicy().hasHeightForWidth());
        toolButton_resolution_preset_3->setSizePolicy(sizePolicy);

        gridLayout_32->addWidget(toolButton_resolution_preset_3, 0, 2, 1, 1);

        toolButton_resolution_preset_4 = new QToolButton(groupBox_presets);
        toolButton_resolution_preset_4->setObjectName(QString::fromUtf8("toolButton_resolution_preset_4"));
        sizePolicy.setHeightForWidth(toolButton_resolution_preset_4->sizePolicy().hasHeightForWidth());
        toolButton_resolution_preset_4->setSizePolicy(sizePolicy);

        gridLayout_32->addWidget(toolButton_resolution_preset_4, 1, 0, 1, 1);

        toolButton_resolution_preset_5 = new QToolButton(groupBox_presets);
        toolButton_resolution_preset_5->setObjectName(QString::fromUtf8("toolButton_resolution_preset_5"));
        sizePolicy.setHeightForWidth(toolButton_resolution_preset_5->sizePolicy().hasHeightForWidth());
        toolButton_resolution_preset_5->setSizePolicy(sizePolicy);

        gridLayout_32->addWidget(toolButton_resolution_preset_5, 1, 1, 1, 1);

        toolButton_resolution_preset_6 = new QToolButton(groupBox_presets);
        toolButton_resolution_preset_6->setObjectName(QString::fromUtf8("toolButton_resolution_preset_6"));
        sizePolicy.setHeightForWidth(toolButton_resolution_preset_6->sizePolicy().hasHeightForWidth());
        toolButton_resolution_preset_6->setSizePolicy(sizePolicy);

        gridLayout_32->addWidget(toolButton_resolution_preset_6, 1, 2, 1, 1);

        toolButton_resolution_preset_7 = new QToolButton(groupBox_presets);
        toolButton_resolution_preset_7->setObjectName(QString::fromUtf8("toolButton_resolution_preset_7"));
        sizePolicy.setHeightForWidth(toolButton_resolution_preset_7->sizePolicy().hasHeightForWidth());
        toolButton_resolution_preset_7->setSizePolicy(sizePolicy);

        gridLayout_32->addWidget(toolButton_resolution_preset_7, 2, 0, 1, 1);

        toolButton_resolution_preset_8 = new QToolButton(groupBox_presets);
        toolButton_resolution_preset_8->setObjectName(QString::fromUtf8("toolButton_resolution_preset_8"));
        sizePolicy.setHeightForWidth(toolButton_resolution_preset_8->sizePolicy().hasHeightForWidth());
        toolButton_resolution_preset_8->setSizePolicy(sizePolicy);

        gridLayout_32->addWidget(toolButton_resolution_preset_8, 2, 1, 1, 1);


        verticalLayout_71->addLayout(gridLayout_32);


        verticalLayout_40->addWidget(groupBox_presets);


        verticalLayout->addWidget(groupBox_imageResolution);

        groupCheck_stereo_enabled = new MyGroupBox(cDockImageAdjustments);
        groupCheck_stereo_enabled->setObjectName(QString::fromUtf8("groupCheck_stereo_enabled"));
        groupCheck_stereo_enabled->setCheckable(true);
        verticalLayout_147 = new QVBoxLayout(groupCheck_stereo_enabled);
        verticalLayout_147->setSpacing(2);
        verticalLayout_147->setObjectName(QString::fromUtf8("verticalLayout_147"));
        verticalLayout_147->setContentsMargins(2, 2, 2, 2);
        gridLayout_11 = new QGridLayout();
        gridLayout_11->setSpacing(2);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        label_69 = new QLabel(groupCheck_stereo_enabled);
        label_69->setObjectName(QString::fromUtf8("label_69"));

        gridLayout_11->addWidget(label_69, 1, 0, 1, 1);

        comboBox_stereo_mode = new MyComboBox(groupCheck_stereo_enabled);
        comboBox_stereo_mode->addItem(QString());
        comboBox_stereo_mode->addItem(QString());
        comboBox_stereo_mode->addItem(QString());
        comboBox_stereo_mode->setObjectName(QString::fromUtf8("comboBox_stereo_mode"));

        gridLayout_11->addWidget(comboBox_stereo_mode, 0, 1, 1, 2);

        label_70 = new QLabel(groupCheck_stereo_enabled);
        label_70->setObjectName(QString::fromUtf8("label_70"));

        gridLayout_11->addWidget(label_70, 0, 0, 1, 1);

        checkBox_stereo_swap_eyes = new MyCheckBox(groupCheck_stereo_enabled);
        checkBox_stereo_swap_eyes->setObjectName(QString::fromUtf8("checkBox_stereo_swap_eyes"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(checkBox_stereo_swap_eyes->sizePolicy().hasHeightForWidth());
        checkBox_stereo_swap_eyes->setSizePolicy(sizePolicy2);

        gridLayout_11->addWidget(checkBox_stereo_swap_eyes, 3, 0, 1, 3);

        label_71 = new QLabel(groupCheck_stereo_enabled);
        label_71->setObjectName(QString::fromUtf8("label_71"));

        gridLayout_11->addWidget(label_71, 2, 0, 1, 1);

        logedit_stereo_eye_distance = new MyLineEdit(groupCheck_stereo_enabled);
        logedit_stereo_eye_distance->setObjectName(QString::fromUtf8("logedit_stereo_eye_distance"));

        gridLayout_11->addWidget(logedit_stereo_eye_distance, 1, 1, 1, 2);

        spinbox_stereo_infinite_correction = new MyDoubleSpinBox(groupCheck_stereo_enabled);
        spinbox_stereo_infinite_correction->setObjectName(QString::fromUtf8("spinbox_stereo_infinite_correction"));
        sizePolicy2.setHeightForWidth(spinbox_stereo_infinite_correction->sizePolicy().hasHeightForWidth());
        spinbox_stereo_infinite_correction->setSizePolicy(sizePolicy2);
        spinbox_stereo_infinite_correction->setDecimals(4);
        spinbox_stereo_infinite_correction->setMinimum(0.000000000000000);
        spinbox_stereo_infinite_correction->setMaximum(10.000000000000000);
        spinbox_stereo_infinite_correction->setSingleStep(0.010000000000000);
        spinbox_stereo_infinite_correction->setValue(0.000000000000000);

        gridLayout_11->addWidget(spinbox_stereo_infinite_correction, 2, 1, 1, 2);


        verticalLayout_147->addLayout(gridLayout_11);

        pushButton_optimal_distance_between_eyes = new QPushButton(groupCheck_stereo_enabled);
        pushButton_optimal_distance_between_eyes->setObjectName(QString::fromUtf8("pushButton_optimal_distance_between_eyes"));

        verticalLayout_147->addWidget(pushButton_optimal_distance_between_eyes);


        verticalLayout->addWidget(groupCheck_stereo_enabled);

        groupBox_12 = new QGroupBox(cDockImageAdjustments);
        groupBox_12->setObjectName(QString::fromUtf8("groupBox_12"));
        verticalLayout_146 = new QVBoxLayout(groupBox_12);
        verticalLayout_146->setSpacing(2);
        verticalLayout_146->setObjectName(QString::fromUtf8("verticalLayout_146"));
        verticalLayout_146->setContentsMargins(2, 2, 2, 2);
        gridLayout_34 = new QGridLayout();
        gridLayout_34->setSpacing(2);
        gridLayout_34->setObjectName(QString::fromUtf8("gridLayout_34"));
        gridLayout_34->setContentsMargins(-1, 0, -1, -1);
        pushButton_quality_preset_normal = new QPushButton(groupBox_12);
        pushButton_quality_preset_normal->setObjectName(QString::fromUtf8("pushButton_quality_preset_normal"));
        sizePolicy.setHeightForWidth(pushButton_quality_preset_normal->sizePolicy().hasHeightForWidth());
        pushButton_quality_preset_normal->setSizePolicy(sizePolicy);

        gridLayout_34->addWidget(pushButton_quality_preset_normal, 1, 0, 1, 1);

        pushButton_quality_preset_low = new QPushButton(groupBox_12);
        pushButton_quality_preset_low->setObjectName(QString::fromUtf8("pushButton_quality_preset_low"));
        sizePolicy.setHeightForWidth(pushButton_quality_preset_low->sizePolicy().hasHeightForWidth());
        pushButton_quality_preset_low->setSizePolicy(sizePolicy);

        gridLayout_34->addWidget(pushButton_quality_preset_low, 0, 1, 1, 1);

        pushButton_quality_preset_high = new QPushButton(groupBox_12);
        pushButton_quality_preset_high->setObjectName(QString::fromUtf8("pushButton_quality_preset_high"));
        sizePolicy.setHeightForWidth(pushButton_quality_preset_high->sizePolicy().hasHeightForWidth());
        pushButton_quality_preset_high->setSizePolicy(sizePolicy);

        gridLayout_34->addWidget(pushButton_quality_preset_high, 1, 1, 1, 1);

        pushButton_quality_preset_very_low = new QPushButton(groupBox_12);
        pushButton_quality_preset_very_low->setObjectName(QString::fromUtf8("pushButton_quality_preset_very_low"));
        sizePolicy.setHeightForWidth(pushButton_quality_preset_very_low->sizePolicy().hasHeightForWidth());
        pushButton_quality_preset_very_low->setSizePolicy(sizePolicy);

        gridLayout_34->addWidget(pushButton_quality_preset_very_low, 0, 0, 1, 1);


        verticalLayout_146->addLayout(gridLayout_34);


        verticalLayout->addWidget(groupBox_12);

        groupBox_ImageAdjustments = new QGroupBox(cDockImageAdjustments);
        groupBox_ImageAdjustments->setObjectName(QString::fromUtf8("groupBox_ImageAdjustments"));
        verticalLayout_20 = new QVBoxLayout(groupBox_ImageAdjustments);
        verticalLayout_20->setSpacing(2);
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));
        verticalLayout_20->setContentsMargins(2, 2, 2, 2);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        spinbox_contrast = new MyDoubleSpinBox(groupBox_ImageAdjustments);
        spinbox_contrast->setObjectName(QString::fromUtf8("spinbox_contrast"));
        sizePolicy.setHeightForWidth(spinbox_contrast->sizePolicy().hasHeightForWidth());
        spinbox_contrast->setSizePolicy(sizePolicy);
        spinbox_contrast->setDecimals(2);
        spinbox_contrast->setMaximum(1000.000000000000000);
        spinbox_contrast->setSingleStep(0.100000000000000);

        gridLayout->addWidget(spinbox_contrast, 1, 1, 1, 1);

        spinbox_gamma = new MyDoubleSpinBox(groupBox_ImageAdjustments);
        spinbox_gamma->setObjectName(QString::fromUtf8("spinbox_gamma"));
        sizePolicy.setHeightForWidth(spinbox_gamma->sizePolicy().hasHeightForWidth());
        spinbox_gamma->setSizePolicy(sizePolicy);
        spinbox_gamma->setDecimals(2);
        spinbox_gamma->setMaximum(1000.000000000000000);
        spinbox_gamma->setSingleStep(0.100000000000000);

        gridLayout->addWidget(spinbox_gamma, 2, 1, 1, 1);

        spinbox_brightness = new MyDoubleSpinBox(groupBox_ImageAdjustments);
        spinbox_brightness->setObjectName(QString::fromUtf8("spinbox_brightness"));
        sizePolicy.setHeightForWidth(spinbox_brightness->sizePolicy().hasHeightForWidth());
        spinbox_brightness->setSizePolicy(sizePolicy);
        spinbox_brightness->setDecimals(2);
        spinbox_brightness->setMaximum(1000.000000000000000);
        spinbox_brightness->setSingleStep(0.100000000000000);

        gridLayout->addWidget(spinbox_brightness, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox_ImageAdjustments);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        label_3 = new QLabel(groupBox_ImageAdjustments);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        label_45 = new QLabel(groupBox_ImageAdjustments);
        label_45->setObjectName(QString::fromUtf8("label_45"));

        gridLayout->addWidget(label_45, 1, 0, 1, 1);

        label_46 = new QLabel(groupBox_ImageAdjustments);
        label_46->setObjectName(QString::fromUtf8("label_46"));

        gridLayout->addWidget(label_46, 3, 0, 1, 1);

        spinbox_saturation = new MyDoubleSpinBox(groupBox_ImageAdjustments);
        spinbox_saturation->setObjectName(QString::fromUtf8("spinbox_saturation"));
        sizePolicy.setHeightForWidth(spinbox_saturation->sizePolicy().hasHeightForWidth());
        spinbox_saturation->setSizePolicy(sizePolicy);
        spinbox_saturation->setDecimals(2);
        spinbox_saturation->setMaximum(1000.000000000000000);
        spinbox_saturation->setSingleStep(0.100000000000000);

        gridLayout->addWidget(spinbox_saturation, 3, 1, 1, 1);

        gridLayout->setColumnStretch(1, 1);

        verticalLayout_20->addLayout(gridLayout);

        checkBox_hdr = new MyCheckBox(groupBox_ImageAdjustments);
        checkBox_hdr->setObjectName(QString::fromUtf8("checkBox_hdr"));

        verticalLayout_20->addWidget(checkBox_hdr);

        pushButton_apply_image_changes = new QPushButton(groupBox_ImageAdjustments);
        pushButton_apply_image_changes->setObjectName(QString::fromUtf8("pushButton_apply_image_changes"));
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("dialog-ok-apply");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8("../git/.designer/backup"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_apply_image_changes->setIcon(icon);

        verticalLayout_20->addWidget(pushButton_apply_image_changes);


        verticalLayout->addWidget(groupBox_ImageAdjustments);

        groupBox_5 = new QGroupBox(cDockImageAdjustments);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        verticalLayout_58 = new QVBoxLayout(groupBox_5);
        verticalLayout_58->setObjectName(QString::fromUtf8("verticalLayout_58"));
        verticalLayout_58->setContentsMargins(2, 2, 2, 2);
        gridLayout_25 = new QGridLayout();
        gridLayout_25->setSpacing(2);
        gridLayout_25->setObjectName(QString::fromUtf8("gridLayout_25"));
        label_54 = new QLabel(groupBox_5);
        label_54->setObjectName(QString::fromUtf8("label_54"));
        label_54->setWordWrap(true);

        gridLayout_25->addWidget(label_54, 0, 0, 1, 1);

        logedit_fov = new MyLineEdit(groupBox_5);
        logedit_fov->setObjectName(QString::fromUtf8("logedit_fov"));

        gridLayout_25->addWidget(logedit_fov, 0, 1, 1, 1);

        label_126 = new QLabel(groupBox_5);
        label_126->setObjectName(QString::fromUtf8("label_126"));

        gridLayout_25->addWidget(label_126, 1, 0, 1, 1);

        comboBox_perspective_type = new MyComboBox(groupBox_5);
        comboBox_perspective_type->addItem(QString());
        comboBox_perspective_type->addItem(QString());
        comboBox_perspective_type->addItem(QString());
        comboBox_perspective_type->addItem(QString());
        comboBox_perspective_type->setObjectName(QString::fromUtf8("comboBox_perspective_type"));
        sizePolicy1.setHeightForWidth(comboBox_perspective_type->sizePolicy().hasHeightForWidth());
        comboBox_perspective_type->setSizePolicy(sizePolicy1);

        gridLayout_25->addWidget(comboBox_perspective_type, 1, 1, 1, 2);


        verticalLayout_58->addLayout(gridLayout_25);

        checkBox_legacy_coordinate_system = new MyCheckBox(groupBox_5);
        checkBox_legacy_coordinate_system->setObjectName(QString::fromUtf8("checkBox_legacy_coordinate_system"));

        verticalLayout_58->addWidget(checkBox_legacy_coordinate_system);


        verticalLayout->addWidget(groupBox_5);

        verticalSpacer_3 = new QSpacerItem(8, 8, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        QWidget::setTabOrder(spinboxInt_image_width, spinboxInt_image_height);
        QWidget::setTabOrder(spinboxInt_image_height, comboBox_image_proportion);
        QWidget::setTabOrder(comboBox_image_proportion, pushButton_imagesize_increase);
        QWidget::setTabOrder(pushButton_imagesize_increase, pushButton_imagesize_decrease);
        QWidget::setTabOrder(pushButton_imagesize_decrease, checkBox_connect_detail_level);
        QWidget::setTabOrder(checkBox_connect_detail_level, toolButton_resolution_preset_1);
        QWidget::setTabOrder(toolButton_resolution_preset_1, toolButton_resolution_preset_2);
        QWidget::setTabOrder(toolButton_resolution_preset_2, toolButton_resolution_preset_3);
        QWidget::setTabOrder(toolButton_resolution_preset_3, toolButton_resolution_preset_4);
        QWidget::setTabOrder(toolButton_resolution_preset_4, toolButton_resolution_preset_5);
        QWidget::setTabOrder(toolButton_resolution_preset_5, toolButton_resolution_preset_6);
        QWidget::setTabOrder(toolButton_resolution_preset_6, toolButton_resolution_preset_7);
        QWidget::setTabOrder(toolButton_resolution_preset_7, toolButton_resolution_preset_8);
        QWidget::setTabOrder(toolButton_resolution_preset_8, toolButton_resolution_preset_9);
        QWidget::setTabOrder(toolButton_resolution_preset_9, groupCheck_stereo_enabled);
        QWidget::setTabOrder(groupCheck_stereo_enabled, comboBox_stereo_mode);
        QWidget::setTabOrder(comboBox_stereo_mode, spinbox_stereo_infinite_correction);
        QWidget::setTabOrder(spinbox_stereo_infinite_correction, checkBox_stereo_swap_eyes);
        QWidget::setTabOrder(checkBox_stereo_swap_eyes, pushButton_quality_preset_very_low);
        QWidget::setTabOrder(pushButton_quality_preset_very_low, pushButton_quality_preset_low);
        QWidget::setTabOrder(pushButton_quality_preset_low, pushButton_quality_preset_normal);
        QWidget::setTabOrder(pushButton_quality_preset_normal, pushButton_quality_preset_high);
        QWidget::setTabOrder(pushButton_quality_preset_high, spinbox_brightness);
        QWidget::setTabOrder(spinbox_brightness, spinbox_contrast);
        QWidget::setTabOrder(spinbox_contrast, spinbox_gamma);
        QWidget::setTabOrder(spinbox_gamma, checkBox_hdr);
        QWidget::setTabOrder(checkBox_hdr, pushButton_apply_image_changes);
        QWidget::setTabOrder(pushButton_apply_image_changes, comboBox_perspective_type);
        QWidget::setTabOrder(comboBox_perspective_type, checkBox_legacy_coordinate_system);

        retranslateUi(cDockImageAdjustments);

        QMetaObject::connectSlotsByName(cDockImageAdjustments);
    } // setupUi

    void retranslateUi(QWidget *cDockImageAdjustments)
    {
        cDockImageAdjustments->setWindowTitle(QCoreApplication::translate("cDockImageAdjustments", "Form", nullptr));
        pushButton_local_load_2->setText(QCoreApplication::translate("cDockImageAdjustments", "Load", nullptr));
        pushButton_local_save_2->setText(QCoreApplication::translate("cDockImageAdjustments", "Save", nullptr));
        pushButton_local_reset_2->setText(QCoreApplication::translate("cDockImageAdjustments", "Reset", nullptr));
        groupBox_imageResolution->setTitle(QCoreApplication::translate("cDockImageAdjustments", "Image resolution", nullptr));
        pushButton_imagesize_increase->setText(QCoreApplication::translate("cDockImageAdjustments", "\303\2272", nullptr));
        pushButton_imagesize_decrease->setText(QCoreApplication::translate("cDockImageAdjustments", "\303\2672", nullptr));
#if QT_CONFIG(tooltip)
        spinboxInt_image_width->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body><p>Width of rendered image in pixel</p><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_101->setText(QCoreApplication::translate("cDockImageAdjustments", "Image height:", nullptr));
#if QT_CONFIG(tooltip)
        spinboxInt_image_height->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body><p>Height of rendered image in pixel</p><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_102->setText(QCoreApplication::translate("cDockImageAdjustments", "Image proportion:", nullptr));
        label_100->setText(QCoreApplication::translate("cDockImageAdjustments", "Image width:", nullptr));
        comboBox_image_proportion->setItemText(0, QCoreApplication::translate("cDockImageAdjustments", "Free", nullptr));
        comboBox_image_proportion->setItemText(1, QCoreApplication::translate("cDockImageAdjustments", "1:1", nullptr));
        comboBox_image_proportion->setItemText(2, QCoreApplication::translate("cDockImageAdjustments", "4:3", nullptr));
        comboBox_image_proportion->setItemText(3, QCoreApplication::translate("cDockImageAdjustments", "3:2", nullptr));
        comboBox_image_proportion->setItemText(4, QCoreApplication::translate("cDockImageAdjustments", "16:9", nullptr));
        comboBox_image_proportion->setItemText(5, QCoreApplication::translate("cDockImageAdjustments", "16:10", nullptr));
        comboBox_image_proportion->setItemText(6, QCoreApplication::translate("cDockImageAdjustments", "2:1", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_image_proportion->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body><p>Force image proportion</p><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        groupCheck_antialiasing_enabled->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body> <p>Enable anti-aliasing (supersampling) to reduce jagged edges and shimmering.</p> <p>How it works: - Renders multiple subpixel samples per pixel and averages them. - \342\200\234Number of samples (n \303\227 n)\342\200\235 sets the subpixel grid; total samples per pixel = n\302\262 (e.g., 2 \303\227 2 = 4 samples).</p> <p>Notes: - Improves edge smoothness and animation stability (less flicker). - Increases render time approximately proportional to n\302\262. - Uncheck to disable anti-aliasing entirely.</p> </body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_antialiasing_enabled->setTitle(QCoreApplication::translate("cDockImageAdjustments", "Anti-aliasin&g", nullptr));
        label_antialiasingNumberOfSamples->setText(QCoreApplication::translate("cDockImageAdjustments", "Number of samples (n x n):", nullptr));
#if QT_CONFIG(tooltip)
        spinboxInt_antialiasing_size->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body> <p>Set the anti-aliasing sample grid size (n).</p> <p>Each pixel is sampled on an n \303\227 n subpixel grid and averaged; total samples per pixel = n\302\262.</p> <p>Notes: - 1 = no supersampling (fastest). - Higher n reduces jagged edges and shimmering but increases render time roughly by n\302\262. - Takes effect only when Anti-aliasing is enabled.</p> </body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_antialiasing_ocl_depth->setItemText(0, QCoreApplication::translate("cDockImageAdjustments", "5", nullptr));
        comboBox_antialiasing_ocl_depth->setItemText(1, QCoreApplication::translate("cDockImageAdjustments", "9", nullptr));
        comboBox_antialiasing_ocl_depth->setItemText(2, QCoreApplication::translate("cDockImageAdjustments", "45", nullptr));
        comboBox_antialiasing_ocl_depth->setItemText(3, QCoreApplication::translate("cDockImageAdjustments", "81", nullptr));
        comboBox_antialiasing_ocl_depth->setItemText(4, QCoreApplication::translate("cDockImageAdjustments", "405", nullptr));
        comboBox_antialiasing_ocl_depth->setItemText(5, QCoreApplication::translate("cDockImageAdjustments", "729", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_antialiasing_ocl_depth->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body> <p>Select the total number of OpenCL anti-aliasing samples per pixel.</p> <p>Use in OpenCL anti-aliasing mode only. Higher values reduce jaggies and shimmering but increase render time roughly proportionally.</p> <p>Options (samples/pixel): 5, 9, 45, 81, 405, 729.</p> <p>Notes: - Effective only when OpenCL AA is enabled; the regular \342\200\234n \303\227 n\342\200\235 grid is ignored in this mode. - With \342\200\234Adaptive (faster)\342\200\235 enabled, fewer samples may be used in low-detail areas.</p> </body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_antialiasing_depth->setText(QCoreApplication::translate("cDockImageAdjustments", "Number of samples (OpenCL mode):", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_antialiasing_adaptive->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body><p>Adaptive anti-aliasing (OpenCL): vary samples per pixel based on image detail to speed up rendering.</p><p>Behavior: - Uses fewer samples in flat/low-contrast areas; uses up to the selected maximum near edges and fine detail. - Usually faster with minimal quality loss, but may increase noise or flicker in animations.</p><p>Notes: - Effective only in OpenCL anti-aliasing mode; ignored in regular n \303\227 n CPU AA. - \342\200\234Number of samples (OpenCL mode)\342\200\235 sets the maximum samples per pixel.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_antialiasing_adaptive->setText(QCoreApplication::translate("cDockImageAdjustments", "Adaptive (faster)", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_connect_detail_level->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body><p>When this option is enabled, the fractal appearance is maintained at all resolutions. </p><p>The fractal detail level will be automatically adjusted to match any change of image resolution. </p><p>For instance, if the resolution is doubled then the detail level will be reduced by half.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_connect_detail_level->setText(QCoreApplication::translate("cDockImageAdjustments", "Connect fractal detail level with image resolution", nullptr));
#if QT_CONFIG(tooltip)
        groupBox_presets->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body><p>Presets for rendered image size</p><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_presets->setTitle(QCoreApplication::translate("cDockImageAdjustments", "Presets", nullptr));
        toolButton_resolution_preset_1->setText(QString());
        toolButton_resolution_preset_2->setText(QString());
        toolButton_resolution_preset_9->setText(QString());
        toolButton_resolution_preset_3->setText(QString());
        toolButton_resolution_preset_4->setText(QString());
        toolButton_resolution_preset_5->setText(QString());
        toolButton_resolution_preset_6->setText(QString());
        toolButton_resolution_preset_7->setText(QString());
        toolButton_resolution_preset_8->setText(QString());
#if QT_CONFIG(tooltip)
        groupCheck_stereo_enabled->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body><p>Enables rendering of stereoscopic images and animations for viewing with 3D glasses.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_stereo_enabled->setTitle(QCoreApplication::translate("cDockImageAdjustments", "S&tereoscopic rendering", nullptr));
        label_69->setText(QCoreApplication::translate("cDockImageAdjustments", "Distance between eyes", nullptr));
        comboBox_stereo_mode->setItemText(0, QCoreApplication::translate("cDockImageAdjustments", "Left - right", nullptr));
        comboBox_stereo_mode->setItemText(1, QCoreApplication::translate("cDockImageAdjustments", "Top - bottom", nullptr));
        comboBox_stereo_mode->setItemText(2, QCoreApplication::translate("cDockImageAdjustments", "Anaglyph - red/cyan", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_stereo_mode->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body><p>Defines how stereoscopic image will be rendered.</p><p>Left-right - View for left eye will be rendered on the left side of the image. View for right eye will be on the right side.</p><p>Top-bottom - View for left eye will be rendered on the top half of the image. View for right eye will be on the bottom half of the image.</p><p>Anaglyph red/cyan - Image will be rendered as an anaglyph dedicated for red/cyan 3D glasses. Using this option it is possible to edit the fractal with 3D view directly in the application window using regular display.  Cheap 3D glasses are all that is required. For fractal exploration it is recommended to not use SSAO ambient occlusion, because it is rendered in 2 passes (try to use &quot;Fast&quot; ambient occlusion).</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_70->setText(QCoreApplication::translate("cDockImageAdjustments", "Mode:", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_stereo_swap_eyes->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body><p>Swaps left and right eye on rendered image.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_stereo_swap_eyes->setText(QCoreApplication::translate("cDockImageAdjustments", "Swap eyes", nullptr));
        label_71->setText(QCoreApplication::translate("cDockImageAdjustments", "Infinite distance correction", nullptr));
#if QT_CONFIG(tooltip)
        logedit_stereo_eye_distance->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body><p>The distance between two virtual eyes. Higher values make the 3D effect more intense. </p><p>The optimal distance between eyes is about 1%-5% of the distance to the viewed object. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinbox_stereo_infinite_correction->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body><p>Adjusts the appearance of the 3D effect for the furthest objects (or background). If the value of this parameter is higher then the background objects will appear further away. </p><p>As an example, the optimal value of this parameter for a 24 inch display could be about 0.4. For bigger display this value should be lower. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_stereo_infinite_correction->setPrefix(QString());
        spinbox_stereo_infinite_correction->setSuffix(QString());
        pushButton_optimal_distance_between_eyes->setText(QCoreApplication::translate("cDockImageAdjustments", "Calculate optimal distance\n"
"between eyes", nullptr));
        groupBox_12->setTitle(QCoreApplication::translate("cDockImageAdjustments", "Image quality presets", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_quality_preset_normal->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body><p>Normal quality preset.</p><p>Ambient occlusion is turned on in Screen Space Ambient Occlusion (SSAO) mode.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_quality_preset_normal->setText(QCoreApplication::translate("cDockImageAdjustments", "Normal", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_quality_preset_low->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body><p>A fast preset but with low quality.</p><p>Ambient occlusion is turned off.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_quality_preset_low->setText(QCoreApplication::translate("cDockImageAdjustments", "Low\n"
"(no ambient occlusion)", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_quality_preset_high->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body><p>The highest quality preset and the slowest.</p><p>Ambient occlusion is turned on in Multiple Rays mode. Raymarching step is decreased to 0.2 to reduce fractal calculation errors.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_quality_preset_high->setText(QCoreApplication::translate("cDockImageAdjustments", " High\n"
"(HQ ambient occlusion\n"
"accurate raymarching)", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_quality_preset_very_low->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body><p>This is the fastest preset but with the lowest quality.</p><p>Shadows, ambient occlusion and raytraced reflections are turned off. Detail level is decreased to 0.5.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_quality_preset_very_low->setText(QCoreApplication::translate("cDockImageAdjustments", "Very low\n"
"(no shadows\n"
"no ambient occlusion)", nullptr));
#if QT_CONFIG(tooltip)
        groupBox_ImageAdjustments->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body><p>Adjustments for image colors. Can be changed after rendering</p><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_ImageAdjustments->setTitle(QCoreApplication::translate("cDockImageAdjustments", "Picture", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_contrast->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body><p>Contrast of image</p><p>Use <span style=\" font-style:italic;\">apply changes</span> button to update image</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_contrast->setPrefix(QString());
        spinbox_contrast->setSuffix(QString());
#if QT_CONFIG(tooltip)
        spinbox_gamma->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body><p>Gamma of image</p><p>Use <span style=\" font-style:italic;\">apply changes</span> button to update image</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_gamma->setPrefix(QString());
        spinbox_gamma->setSuffix(QString());
#if QT_CONFIG(tooltip)
        spinbox_brightness->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body><p>Brightness of image</p><p>Use <span style=\" font-style:italic;\">apply changes</span> button to update image<br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_brightness->setPrefix(QString());
        spinbox_brightness->setSuffix(QString());
        label_4->setText(QCoreApplication::translate("cDockImageAdjustments", "Gamma:", nullptr));
        label_3->setText(QCoreApplication::translate("cDockImageAdjustments", "Brightness:", nullptr));
        label_45->setText(QCoreApplication::translate("cDockImageAdjustments", "Contrast:", nullptr));
        label_46->setText(QCoreApplication::translate("cDockImageAdjustments", "Saturation", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_saturation->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body><p>Gamma of image</p><p>Use <span style=\" font-style:italic;\">apply changes</span> button to update image</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_saturation->setPrefix(QString());
        spinbox_saturation->setSuffix(QString());
#if QT_CONFIG(tooltip)
        checkBox_hdr->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body> <p>Enable High Dynamic Range (HDR) tone mapping to preserve highlight and shadow detail.</p> <p>What it does: - Compresses very bright pixels to prevent clipping/oversaturation. - Improves perceived contrast while retaining details.</p> <p>Notes: - Post-effect on the rendered image; it doesn\342\200\231t change scene lighting. - Works together with Brightness/Contrast/Gamma and Saturation controls.</p> <p>Use <span style=\" font-style:italic;\">Apply changes</span> to update the image.</p> </body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_hdr->setText(QCoreApplication::translate("cDockImageAdjustments", "High Dynamic Range (HDR)", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_apply_image_changes->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body><p>Apply changes of image colors</p><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_apply_image_changes->setText(QCoreApplication::translate("cDockImageAdjustments", "Apply changes", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("cDockImageAdjustments", "Camera", nullptr));
        label_54->setText(QCoreApplication::translate("cDockImageAdjustments", "Field of view (degrees):", nullptr));
#if QT_CONFIG(tooltip)
        logedit_fov->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body><p>Field of view of camera. Higher value gives wider view.</p><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_126->setText(QCoreApplication::translate("cDockImageAdjustments", "Perspective type:", nullptr));
        comboBox_perspective_type->setItemText(0, QCoreApplication::translate("cDockImageAdjustments", "Three-point perspective", nullptr));
        comboBox_perspective_type->setItemText(1, QCoreApplication::translate("cDockImageAdjustments", "Fish eye", nullptr));
        comboBox_perspective_type->setItemText(2, QCoreApplication::translate("cDockImageAdjustments", "Equirectangular", nullptr));
        comboBox_perspective_type->setItemText(3, QCoreApplication::translate("cDockImageAdjustments", "Fulldome", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_perspective_type->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body><p>Type of perspective projection.</p><p>- Three-point perspective  projection, has two vanishing points on the horizon line and one on zenith or nadir</p><p>- Fish eye - simulates fish eye camera. <span style=\" font-style:italic;\">Field of view</span> = 1.0 corresponds to 180 degree</p><p>- Equirectangular - is dedicated to render 360 degree panoramas. Image proportion should be set to 2:1 and <span style=\" font-style:italic;\">Field of view</span> = 1.0</p><p>- Fulldome - is dedicated to render images for displaying in fulldome.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBox_legacy_coordinate_system->setToolTip(QCoreApplication::translate("cDockImageAdjustments", "<html><head/><body><p>For compatibility of coordinate system with old Mandelbulber v. 1.21 .fract files</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_legacy_coordinate_system->setText(QCoreApplication::translate("cDockImageAdjustments", "Coordinate system like in Mandelbulber v1.21", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cDockImageAdjustments: public Ui_cDockImageAdjustments {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCK_IMAGE_ADJUSTMENTS_H
