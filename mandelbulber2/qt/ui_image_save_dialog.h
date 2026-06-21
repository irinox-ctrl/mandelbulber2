/********************************************************************************
** Form generated from reading UI file 'image_save_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGE_SAVE_DIALOG_H
#define UI_IMAGE_SAVE_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "my_check_box.h"
#include "my_combo_box.h"
#include "my_group_box.h"
#include "my_line_edit.h"
#include "my_spin_box.h"

QT_BEGIN_NAMESPACE

class Ui_cImageSaveDialog
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea_image;
    QWidget *scrollAreaWidgetContents_image;
    QVBoxLayout *verticalLayout_image;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_12;
    QGridLayout *gridLayout_4;
    QLabel *label_10;
    QLabel *label_8;
    QLabel *label_9;
    MyCheckBox *checkBox_color_enabled;
    MyComboBox *comboBox_color_quality;
    MyLineEdit *text_color_postfix;
    MyCheckBox *checkBox_alpha_enabled;
    MyComboBox *comboBox_alpha_quality;
    MyLineEdit *text_alpha_postfix;
    MyCheckBox *checkBox_zbuffer_enabled;
    MyComboBox *comboBox_zbuffer_quality;
    MyLineEdit *text_zbuffer_postfix;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_3;
    MyCheckBox *checkBox_zbuffer_invert;
    MyCheckBox *checkBox_zbuffer_logarithmic;
    MyGroupBox *groupCheck_zbuffer_constant_range;
    QGridLayout *gridLayout_5;
    QLabel *label_2;
    QLabel *label;
    MyLineEdit *logedit_zbuffer_min_depth;
    MyLineEdit *logedit_zbuffer_max_depth;
    QVBoxLayout *verticalLayout_10;
    MyGroupBox *groupCheck_optional_image_channels_enabled;
    QGridLayout *gridLayout_optional_image_channels;
    MyLineEdit *text_diffuse_postfix;
    MyLineEdit *text_world_postfix;
    QLabel *label_image_quality_optional;
    MyCheckBox *checkBox_gi_channel_enabled;
    QLabel *label_image_postfix_optional;
    MyLineEdit *text_normalWorld_postfix;
    MyComboBox *comboBox_shadow_channel_quality;
    MyCheckBox *checkBox_diffuse_enabled;
    MyCheckBox *checkBox_normalWorld_enabled;
    MyCheckBox *checkBox_specular_enabled;
    MyLineEdit *text_shadow_channel_postfix;
    MyCheckBox *checkBox_world_enabled;
    QLabel *label_image_channel_optional;
    MyLineEdit *text_normal_postfix;
    MyComboBox *comboBox_world_quality;
    MyCheckBox *checkBox_shadow_channel_enabled;
    MyComboBox *comboBox_specular_quality;
    MyLineEdit *text_gi_channel_postfix;
    MyCheckBox *checkBox_normal_enabled;
    MyComboBox *comboBox_gi_channel_quality;
    MyLineEdit *text_specular_postfix;
    MyComboBox *comboBox_normal_quality;
    QLabel *label_rerender_required_info;
    MyComboBox *comboBox_diffuse_quality;
    MyComboBox *comboBox_normalWorld_quality;
    MyCheckBox *checkBox_not_denoised_channel_enabled;
    MyComboBox *comboBox_not_denoised_channel_quality;
    MyLineEdit *text_not_denoised_channel_postfix;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout_2;
    MyCheckBox *checkBox_append_alpha_png;
    MySpinBox *spinboxInt_jpeg_quality;
    QLabel *label_5;
    MyCheckBox *checkBox_linear_colorspace;
    MyCheckBox *checkBox_save_channels_in_separate_folders;
    MyCheckBox *checkBox_stereoscopic_in_separate_files;
    QCheckBox *checkBox_save_settings_with_image;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *cImageSaveDialog)
    {
        if (cImageSaveDialog->objectName().isEmpty())
            cImageSaveDialog->setObjectName(QString::fromUtf8("cImageSaveDialog"));
        cImageSaveDialog->resize(423, 793);
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("image-x-generic");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8(":/system/icons/image-x-generic.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        cImageSaveDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(cImageSaveDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea_image = new QScrollArea(cImageSaveDialog);
        scrollArea_image->setObjectName(QString::fromUtf8("scrollArea_image"));
        scrollArea_image->setWidgetResizable(true);
        scrollAreaWidgetContents_image = new QWidget();
        scrollAreaWidgetContents_image->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_image"));
        scrollAreaWidgetContents_image->setGeometry(QRect(0, 0, 389, 780));
        verticalLayout_image = new QVBoxLayout(scrollAreaWidgetContents_image);
        verticalLayout_image->setSpacing(2);
        verticalLayout_image->setObjectName(QString::fromUtf8("verticalLayout_image"));
        verticalLayout_image->setContentsMargins(2, 2, 2, 2);
        groupBox_4 = new QGroupBox(scrollAreaWidgetContents_image);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout_6 = new QVBoxLayout(groupBox_4);
        verticalLayout_6->setSpacing(2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(2, 2, 2, 2);
        label_12 = new QLabel(groupBox_4);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        verticalLayout_6->addWidget(label_12);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_4->addWidget(label_10, 0, 0, 1, 1);

        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_4->addWidget(label_8, 0, 1, 1, 1);

        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_4->addWidget(label_9, 0, 2, 1, 1);

        checkBox_color_enabled = new MyCheckBox(groupBox_4);
        checkBox_color_enabled->setObjectName(QString::fromUtf8("checkBox_color_enabled"));
        checkBox_color_enabled->setChecked(true);

        gridLayout_4->addWidget(checkBox_color_enabled, 1, 0, 1, 1);

        comboBox_color_quality = new MyComboBox(groupBox_4);
        comboBox_color_quality->addItem(QString());
        comboBox_color_quality->addItem(QString());
        comboBox_color_quality->addItem(QString());
        comboBox_color_quality->setObjectName(QString::fromUtf8("comboBox_color_quality"));

        gridLayout_4->addWidget(comboBox_color_quality, 1, 1, 1, 1);

        text_color_postfix = new MyLineEdit(groupBox_4);
        text_color_postfix->setObjectName(QString::fromUtf8("text_color_postfix"));

        gridLayout_4->addWidget(text_color_postfix, 1, 2, 1, 1);

        checkBox_alpha_enabled = new MyCheckBox(groupBox_4);
        checkBox_alpha_enabled->setObjectName(QString::fromUtf8("checkBox_alpha_enabled"));

        gridLayout_4->addWidget(checkBox_alpha_enabled, 2, 0, 1, 1);

        comboBox_alpha_quality = new MyComboBox(groupBox_4);
        comboBox_alpha_quality->addItem(QString());
        comboBox_alpha_quality->addItem(QString());
        comboBox_alpha_quality->addItem(QString());
        comboBox_alpha_quality->setObjectName(QString::fromUtf8("comboBox_alpha_quality"));

        gridLayout_4->addWidget(comboBox_alpha_quality, 2, 1, 1, 1);

        text_alpha_postfix = new MyLineEdit(groupBox_4);
        text_alpha_postfix->setObjectName(QString::fromUtf8("text_alpha_postfix"));

        gridLayout_4->addWidget(text_alpha_postfix, 2, 2, 1, 1);

        checkBox_zbuffer_enabled = new MyCheckBox(groupBox_4);
        checkBox_zbuffer_enabled->setObjectName(QString::fromUtf8("checkBox_zbuffer_enabled"));

        gridLayout_4->addWidget(checkBox_zbuffer_enabled, 3, 0, 1, 1);

        comboBox_zbuffer_quality = new MyComboBox(groupBox_4);
        comboBox_zbuffer_quality->addItem(QString());
        comboBox_zbuffer_quality->addItem(QString());
        comboBox_zbuffer_quality->addItem(QString());
        comboBox_zbuffer_quality->setObjectName(QString::fromUtf8("comboBox_zbuffer_quality"));

        gridLayout_4->addWidget(comboBox_zbuffer_quality, 3, 1, 1, 1);

        text_zbuffer_postfix = new MyLineEdit(groupBox_4);
        text_zbuffer_postfix->setObjectName(QString::fromUtf8("text_zbuffer_postfix"));

        gridLayout_4->addWidget(text_zbuffer_postfix, 3, 2, 1, 1);


        verticalLayout_6->addLayout(gridLayout_4);


        verticalLayout_image->addWidget(groupBox_4);

        groupBox = new QGroupBox(scrollAreaWidgetContents_image);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_3 = new QGridLayout(groupBox);
        gridLayout_3->setSpacing(2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(2, 2, 2, 2);
        checkBox_zbuffer_invert = new MyCheckBox(groupBox);
        checkBox_zbuffer_invert->setObjectName(QString::fromUtf8("checkBox_zbuffer_invert"));

        gridLayout_3->addWidget(checkBox_zbuffer_invert, 0, 0, 1, 1);

        checkBox_zbuffer_logarithmic = new MyCheckBox(groupBox);
        checkBox_zbuffer_logarithmic->setObjectName(QString::fromUtf8("checkBox_zbuffer_logarithmic"));

        gridLayout_3->addWidget(checkBox_zbuffer_logarithmic, 1, 0, 1, 1);

        groupCheck_zbuffer_constant_range = new MyGroupBox(groupBox);
        groupCheck_zbuffer_constant_range->setObjectName(QString::fromUtf8("groupCheck_zbuffer_constant_range"));
        groupCheck_zbuffer_constant_range->setCheckable(true);
        gridLayout_5 = new QGridLayout(groupCheck_zbuffer_constant_range);
        gridLayout_5->setSpacing(2);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(2, 2, 2, 2);
        label_2 = new QLabel(groupCheck_zbuffer_constant_range);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_5->addWidget(label_2, 1, 0, 1, 1);

        label = new QLabel(groupCheck_zbuffer_constant_range);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_5->addWidget(label, 0, 0, 1, 1);

        logedit_zbuffer_min_depth = new MyLineEdit(groupCheck_zbuffer_constant_range);
        logedit_zbuffer_min_depth->setObjectName(QString::fromUtf8("logedit_zbuffer_min_depth"));

        gridLayout_5->addWidget(logedit_zbuffer_min_depth, 0, 1, 1, 1);

        logedit_zbuffer_max_depth = new MyLineEdit(groupCheck_zbuffer_constant_range);
        logedit_zbuffer_max_depth->setObjectName(QString::fromUtf8("logedit_zbuffer_max_depth"));

        gridLayout_5->addWidget(logedit_zbuffer_max_depth, 1, 1, 1, 1);


        gridLayout_3->addWidget(groupCheck_zbuffer_constant_range, 2, 0, 1, 1);


        verticalLayout_image->addWidget(groupBox);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        groupCheck_optional_image_channels_enabled = new MyGroupBox(scrollAreaWidgetContents_image);
        groupCheck_optional_image_channels_enabled->setObjectName(QString::fromUtf8("groupCheck_optional_image_channels_enabled"));
        groupCheck_optional_image_channels_enabled->setCheckable(true);
        gridLayout_optional_image_channels = new QGridLayout(groupCheck_optional_image_channels_enabled);
        gridLayout_optional_image_channels->setSpacing(2);
        gridLayout_optional_image_channels->setObjectName(QString::fromUtf8("gridLayout_optional_image_channels"));
        text_diffuse_postfix = new MyLineEdit(groupCheck_optional_image_channels_enabled);
        text_diffuse_postfix->setObjectName(QString::fromUtf8("text_diffuse_postfix"));

        gridLayout_optional_image_channels->addWidget(text_diffuse_postfix, 5, 2, 1, 1);

        text_world_postfix = new MyLineEdit(groupCheck_optional_image_channels_enabled);
        text_world_postfix->setObjectName(QString::fromUtf8("text_world_postfix"));

        gridLayout_optional_image_channels->addWidget(text_world_postfix, 4, 2, 1, 1);

        label_image_quality_optional = new QLabel(groupCheck_optional_image_channels_enabled);
        label_image_quality_optional->setObjectName(QString::fromUtf8("label_image_quality_optional"));

        gridLayout_optional_image_channels->addWidget(label_image_quality_optional, 1, 1, 1, 1);

        checkBox_gi_channel_enabled = new MyCheckBox(groupCheck_optional_image_channels_enabled);
        checkBox_gi_channel_enabled->setObjectName(QString::fromUtf8("checkBox_gi_channel_enabled"));

        gridLayout_optional_image_channels->addWidget(checkBox_gi_channel_enabled, 8, 0, 1, 1);

        label_image_postfix_optional = new QLabel(groupCheck_optional_image_channels_enabled);
        label_image_postfix_optional->setObjectName(QString::fromUtf8("label_image_postfix_optional"));

        gridLayout_optional_image_channels->addWidget(label_image_postfix_optional, 1, 2, 1, 1);

        text_normalWorld_postfix = new MyLineEdit(groupCheck_optional_image_channels_enabled);
        text_normalWorld_postfix->setObjectName(QString::fromUtf8("text_normalWorld_postfix"));

        gridLayout_optional_image_channels->addWidget(text_normalWorld_postfix, 6, 2, 1, 1);

        comboBox_shadow_channel_quality = new MyComboBox(groupCheck_optional_image_channels_enabled);
        comboBox_shadow_channel_quality->addItem(QString());
        comboBox_shadow_channel_quality->addItem(QString());
        comboBox_shadow_channel_quality->addItem(QString());
        comboBox_shadow_channel_quality->setObjectName(QString::fromUtf8("comboBox_shadow_channel_quality"));

        gridLayout_optional_image_channels->addWidget(comboBox_shadow_channel_quality, 7, 1, 1, 1);

        checkBox_diffuse_enabled = new MyCheckBox(groupCheck_optional_image_channels_enabled);
        checkBox_diffuse_enabled->setObjectName(QString::fromUtf8("checkBox_diffuse_enabled"));

        gridLayout_optional_image_channels->addWidget(checkBox_diffuse_enabled, 5, 0, 1, 1);

        checkBox_normalWorld_enabled = new MyCheckBox(groupCheck_optional_image_channels_enabled);
        checkBox_normalWorld_enabled->setObjectName(QString::fromUtf8("checkBox_normalWorld_enabled"));

        gridLayout_optional_image_channels->addWidget(checkBox_normalWorld_enabled, 6, 0, 1, 1);

        checkBox_specular_enabled = new MyCheckBox(groupCheck_optional_image_channels_enabled);
        checkBox_specular_enabled->setObjectName(QString::fromUtf8("checkBox_specular_enabled"));

        gridLayout_optional_image_channels->addWidget(checkBox_specular_enabled, 3, 0, 1, 1);

        text_shadow_channel_postfix = new MyLineEdit(groupCheck_optional_image_channels_enabled);
        text_shadow_channel_postfix->setObjectName(QString::fromUtf8("text_shadow_channel_postfix"));

        gridLayout_optional_image_channels->addWidget(text_shadow_channel_postfix, 7, 2, 1, 1);

        checkBox_world_enabled = new MyCheckBox(groupCheck_optional_image_channels_enabled);
        checkBox_world_enabled->setObjectName(QString::fromUtf8("checkBox_world_enabled"));

        gridLayout_optional_image_channels->addWidget(checkBox_world_enabled, 4, 0, 1, 1);

        label_image_channel_optional = new QLabel(groupCheck_optional_image_channels_enabled);
        label_image_channel_optional->setObjectName(QString::fromUtf8("label_image_channel_optional"));

        gridLayout_optional_image_channels->addWidget(label_image_channel_optional, 1, 0, 1, 1);

        text_normal_postfix = new MyLineEdit(groupCheck_optional_image_channels_enabled);
        text_normal_postfix->setObjectName(QString::fromUtf8("text_normal_postfix"));

        gridLayout_optional_image_channels->addWidget(text_normal_postfix, 2, 2, 1, 1);

        comboBox_world_quality = new MyComboBox(groupCheck_optional_image_channels_enabled);
        comboBox_world_quality->addItem(QString());
        comboBox_world_quality->addItem(QString());
        comboBox_world_quality->addItem(QString());
        comboBox_world_quality->setObjectName(QString::fromUtf8("comboBox_world_quality"));

        gridLayout_optional_image_channels->addWidget(comboBox_world_quality, 4, 1, 1, 1);

        checkBox_shadow_channel_enabled = new MyCheckBox(groupCheck_optional_image_channels_enabled);
        checkBox_shadow_channel_enabled->setObjectName(QString::fromUtf8("checkBox_shadow_channel_enabled"));

        gridLayout_optional_image_channels->addWidget(checkBox_shadow_channel_enabled, 7, 0, 1, 1);

        comboBox_specular_quality = new MyComboBox(groupCheck_optional_image_channels_enabled);
        comboBox_specular_quality->addItem(QString());
        comboBox_specular_quality->addItem(QString());
        comboBox_specular_quality->addItem(QString());
        comboBox_specular_quality->setObjectName(QString::fromUtf8("comboBox_specular_quality"));

        gridLayout_optional_image_channels->addWidget(comboBox_specular_quality, 3, 1, 1, 1);

        text_gi_channel_postfix = new MyLineEdit(groupCheck_optional_image_channels_enabled);
        text_gi_channel_postfix->setObjectName(QString::fromUtf8("text_gi_channel_postfix"));

        gridLayout_optional_image_channels->addWidget(text_gi_channel_postfix, 8, 2, 1, 1);

        checkBox_normal_enabled = new MyCheckBox(groupCheck_optional_image_channels_enabled);
        checkBox_normal_enabled->setObjectName(QString::fromUtf8("checkBox_normal_enabled"));

        gridLayout_optional_image_channels->addWidget(checkBox_normal_enabled, 2, 0, 1, 1);

        comboBox_gi_channel_quality = new MyComboBox(groupCheck_optional_image_channels_enabled);
        comboBox_gi_channel_quality->addItem(QString());
        comboBox_gi_channel_quality->addItem(QString());
        comboBox_gi_channel_quality->addItem(QString());
        comboBox_gi_channel_quality->setObjectName(QString::fromUtf8("comboBox_gi_channel_quality"));

        gridLayout_optional_image_channels->addWidget(comboBox_gi_channel_quality, 8, 1, 1, 1);

        text_specular_postfix = new MyLineEdit(groupCheck_optional_image_channels_enabled);
        text_specular_postfix->setObjectName(QString::fromUtf8("text_specular_postfix"));

        gridLayout_optional_image_channels->addWidget(text_specular_postfix, 3, 2, 1, 1);

        comboBox_normal_quality = new MyComboBox(groupCheck_optional_image_channels_enabled);
        comboBox_normal_quality->addItem(QString());
        comboBox_normal_quality->addItem(QString());
        comboBox_normal_quality->addItem(QString());
        comboBox_normal_quality->setObjectName(QString::fromUtf8("comboBox_normal_quality"));

        gridLayout_optional_image_channels->addWidget(comboBox_normal_quality, 2, 1, 1, 1);

        label_rerender_required_info = new QLabel(groupCheck_optional_image_channels_enabled);
        label_rerender_required_info->setObjectName(QString::fromUtf8("label_rerender_required_info"));

        gridLayout_optional_image_channels->addWidget(label_rerender_required_info, 0, 0, 1, 3);

        comboBox_diffuse_quality = new MyComboBox(groupCheck_optional_image_channels_enabled);
        comboBox_diffuse_quality->addItem(QString());
        comboBox_diffuse_quality->addItem(QString());
        comboBox_diffuse_quality->addItem(QString());
        comboBox_diffuse_quality->setObjectName(QString::fromUtf8("comboBox_diffuse_quality"));

        gridLayout_optional_image_channels->addWidget(comboBox_diffuse_quality, 5, 1, 1, 1);

        comboBox_normalWorld_quality = new MyComboBox(groupCheck_optional_image_channels_enabled);
        comboBox_normalWorld_quality->addItem(QString());
        comboBox_normalWorld_quality->addItem(QString());
        comboBox_normalWorld_quality->addItem(QString());
        comboBox_normalWorld_quality->setObjectName(QString::fromUtf8("comboBox_normalWorld_quality"));

        gridLayout_optional_image_channels->addWidget(comboBox_normalWorld_quality, 6, 1, 1, 1);

        checkBox_not_denoised_channel_enabled = new MyCheckBox(groupCheck_optional_image_channels_enabled);
        checkBox_not_denoised_channel_enabled->setObjectName(QString::fromUtf8("checkBox_not_denoised_channel_enabled"));

        gridLayout_optional_image_channels->addWidget(checkBox_not_denoised_channel_enabled, 9, 0, 1, 1);

        comboBox_not_denoised_channel_quality = new MyComboBox(groupCheck_optional_image_channels_enabled);
        comboBox_not_denoised_channel_quality->addItem(QString());
        comboBox_not_denoised_channel_quality->addItem(QString());
        comboBox_not_denoised_channel_quality->addItem(QString());
        comboBox_not_denoised_channel_quality->setObjectName(QString::fromUtf8("comboBox_not_denoised_channel_quality"));

        gridLayout_optional_image_channels->addWidget(comboBox_not_denoised_channel_quality, 9, 1, 1, 1);

        text_not_denoised_channel_postfix = new MyLineEdit(groupCheck_optional_image_channels_enabled);
        text_not_denoised_channel_postfix->setObjectName(QString::fromUtf8("text_not_denoised_channel_postfix"));

        gridLayout_optional_image_channels->addWidget(text_not_denoised_channel_postfix, 9, 2, 1, 1);


        verticalLayout_10->addWidget(groupCheck_optional_image_channels_enabled);


        verticalLayout_image->addLayout(verticalLayout_10);

        groupBox_2 = new QGroupBox(scrollAreaWidgetContents_image);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setSpacing(2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(2, 2, 2, 2);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        checkBox_append_alpha_png = new MyCheckBox(groupBox_2);
        checkBox_append_alpha_png->setObjectName(QString::fromUtf8("checkBox_append_alpha_png"));

        gridLayout_2->addWidget(checkBox_append_alpha_png, 2, 0, 1, 2);

        spinboxInt_jpeg_quality = new MySpinBox(groupBox_2);
        spinboxInt_jpeg_quality->setObjectName(QString::fromUtf8("spinboxInt_jpeg_quality"));
        spinboxInt_jpeg_quality->setMinimum(1);
        spinboxInt_jpeg_quality->setMaximum(100);

        gridLayout_2->addWidget(spinboxInt_jpeg_quality, 0, 1, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 0, 0, 1, 1);

        checkBox_linear_colorspace = new MyCheckBox(groupBox_2);
        checkBox_linear_colorspace->setObjectName(QString::fromUtf8("checkBox_linear_colorspace"));

        gridLayout_2->addWidget(checkBox_linear_colorspace, 4, 0, 1, 2);

        checkBox_save_channels_in_separate_folders = new MyCheckBox(groupBox_2);
        checkBox_save_channels_in_separate_folders->setObjectName(QString::fromUtf8("checkBox_save_channels_in_separate_folders"));

        gridLayout_2->addWidget(checkBox_save_channels_in_separate_folders, 3, 0, 1, 2);

        checkBox_stereoscopic_in_separate_files = new MyCheckBox(groupBox_2);
        checkBox_stereoscopic_in_separate_files->setObjectName(QString::fromUtf8("checkBox_stereoscopic_in_separate_files"));

        gridLayout_2->addWidget(checkBox_stereoscopic_in_separate_files, 5, 0, 1, 2);

        checkBox_save_settings_with_image = new QCheckBox(groupBox_2);
        checkBox_save_settings_with_image->setObjectName(QString::fromUtf8("checkBox_save_settings_with_image"));

        gridLayout_2->addWidget(checkBox_save_settings_with_image, 1, 0, 1, 1);


        verticalLayout_4->addLayout(gridLayout_2);


        verticalLayout_image->addWidget(groupBox_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_image->addItem(verticalSpacer_2);

        scrollArea_image->setWidget(scrollAreaWidgetContents_image);

        verticalLayout->addWidget(scrollArea_image);


        retranslateUi(cImageSaveDialog);

        QMetaObject::connectSlotsByName(cImageSaveDialog);
    } // setupUi

    void retranslateUi(QWidget *cImageSaveDialog)
    {
        cImageSaveDialog->setWindowTitle(QCoreApplication::translate("cImageSaveDialog", "Save Image", nullptr));
#if QT_CONFIG(tooltip)
        groupBox_4->setToolTip(QCoreApplication::translate("cImageSaveDialog", "<html><head/><body><p><span style=\" font-weight:600;\">JPG</span></p><p>The quality value will be ignored, since JPG only supports 8 bit precision.</p><p>Every image channel will be saved as a separate file with appended postfix.</p><p><span style=\" font-weight:600;\">PNG</span></p><p>The quality value can be 8 bit or 16 bit (32 bit will result in 16 bit precision).</p><p>Every image channel will be saved as a separate file. </p><p>Only exception can be alpha channel:</p><p>If both Color and Alpha channel are selected and &quot;Append alpha to image (only PNG and TIFF)&quot;, then color + alpha will be saved to a RGBA image with quality and postfix of color row.</p><p><span style=\" font-weight:600;\">TIFF</span></p><p>The quality value can be 8 bit, 16 bit or 32 bit.</p><p>Every image channel will be saved as a separate file. </p><p>Only exception can be alpha channel:</p><p>If both Color and Alpha channel are selected and &quot;Append alpha to image (only PNG and TIFF)&quot;, then color + alpha will be sav"
                        "ed to a RGBA image with quality and postfix of color row.</p><p><span style=\" font-weight:600;\">EXR</span></p><p>The quality value can be 16 bit or 32 bit (8 bit will result in 16 bit precision).</p><p>The postfix will be ignored since all image channels will be saved to one file.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_4->setTitle(QCoreApplication::translate("cImageSaveDialog", "Image Settings", nullptr));
        label_12->setText(QCoreApplication::translate("cImageSaveDialog", "These settings affect \"Save as JPG/PNG/EXR/TIFF\" actions\n"
" and saving animation frames.", nullptr));
        label_10->setText(QCoreApplication::translate("cImageSaveDialog", "Image Channel", nullptr));
        label_8->setText(QCoreApplication::translate("cImageSaveDialog", "Quality", nullptr));
        label_9->setText(QCoreApplication::translate("cImageSaveDialog", "Postfix", nullptr));
        checkBox_color_enabled->setText(QCoreApplication::translate("cImageSaveDialog", "Color", nullptr));
        comboBox_color_quality->setItemText(0, QCoreApplication::translate("cImageSaveDialog", "8 bit", nullptr));
        comboBox_color_quality->setItemText(1, QCoreApplication::translate("cImageSaveDialog", "16 bit", nullptr));
        comboBox_color_quality->setItemText(2, QCoreApplication::translate("cImageSaveDialog", "32 bit", nullptr));

        text_color_postfix->setText(QString());
        checkBox_alpha_enabled->setText(QCoreApplication::translate("cImageSaveDialog", "Alpha", nullptr));
        comboBox_alpha_quality->setItemText(0, QCoreApplication::translate("cImageSaveDialog", "8 bit", nullptr));
        comboBox_alpha_quality->setItemText(1, QCoreApplication::translate("cImageSaveDialog", "16 bit", nullptr));
        comboBox_alpha_quality->setItemText(2, QCoreApplication::translate("cImageSaveDialog", "32 bit", nullptr));

        text_alpha_postfix->setText(QString());
        checkBox_zbuffer_enabled->setText(QCoreApplication::translate("cImageSaveDialog", "Z Buffer", nullptr));
        comboBox_zbuffer_quality->setItemText(0, QCoreApplication::translate("cImageSaveDialog", "8 bit", nullptr));
        comboBox_zbuffer_quality->setItemText(1, QCoreApplication::translate("cImageSaveDialog", "16 bit", nullptr));
        comboBox_zbuffer_quality->setItemText(2, QCoreApplication::translate("cImageSaveDialog", "32 bit", nullptr));

        text_zbuffer_postfix->setText(QString());
        groupBox->setTitle(QCoreApplication::translate("cImageSaveDialog", "Z-buffer options", nullptr));
        checkBox_zbuffer_invert->setText(QCoreApplication::translate("cImageSaveDialog", "Invert z-buffer", nullptr));
        checkBox_zbuffer_logarithmic->setText(QCoreApplication::translate("cImageSaveDialog", "Logarithmic scale", nullptr));
        groupCheck_zbuffer_constant_range->setTitle(QCoreApplication::translate("cImageSaveDialog", "Use contant depth range", nullptr));
        label_2->setText(QCoreApplication::translate("cImageSaveDialog", "maximum z-depth", nullptr));
        label->setText(QCoreApplication::translate("cImageSaveDialog", "minimum z-depth", nullptr));
        groupCheck_optional_image_channels_enabled->setTitle(QCoreApplication::translate("cImageSaveDialog", "Optional Image Channels", nullptr));
        text_diffuse_postfix->setText(QString());
        text_world_postfix->setText(QString());
        label_image_quality_optional->setText(QCoreApplication::translate("cImageSaveDialog", "Quality", nullptr));
        checkBox_gi_channel_enabled->setText(QCoreApplication::translate("cImageSaveDialog", "Global illumination", nullptr));
        label_image_postfix_optional->setText(QCoreApplication::translate("cImageSaveDialog", "Postfix", nullptr));
        text_normalWorld_postfix->setText(QString());
        comboBox_shadow_channel_quality->setItemText(0, QCoreApplication::translate("cImageSaveDialog", "8 bit", nullptr));
        comboBox_shadow_channel_quality->setItemText(1, QCoreApplication::translate("cImageSaveDialog", "16 bit", nullptr));
        comboBox_shadow_channel_quality->setItemText(2, QCoreApplication::translate("cImageSaveDialog", "32 bit", nullptr));

        checkBox_diffuse_enabled->setText(QCoreApplication::translate("cImageSaveDialog", "Diffuse", nullptr));
        checkBox_normalWorld_enabled->setText(QCoreApplication::translate("cImageSaveDialog", "World Normal", nullptr));
        checkBox_specular_enabled->setText(QCoreApplication::translate("cImageSaveDialog", "Specular", nullptr));
        text_shadow_channel_postfix->setText(QString());
        checkBox_world_enabled->setText(QCoreApplication::translate("cImageSaveDialog", "World", nullptr));
        label_image_channel_optional->setText(QCoreApplication::translate("cImageSaveDialog", "Image Channel", nullptr));
        text_normal_postfix->setText(QString());
        comboBox_world_quality->setItemText(0, QCoreApplication::translate("cImageSaveDialog", "8 bit", nullptr));
        comboBox_world_quality->setItemText(1, QCoreApplication::translate("cImageSaveDialog", "16 bit", nullptr));
        comboBox_world_quality->setItemText(2, QCoreApplication::translate("cImageSaveDialog", "32 bit", nullptr));

        checkBox_shadow_channel_enabled->setText(QCoreApplication::translate("cImageSaveDialog", "Shadows", nullptr));
        comboBox_specular_quality->setItemText(0, QCoreApplication::translate("cImageSaveDialog", "8 bit", nullptr));
        comboBox_specular_quality->setItemText(1, QCoreApplication::translate("cImageSaveDialog", "16 bit", nullptr));
        comboBox_specular_quality->setItemText(2, QCoreApplication::translate("cImageSaveDialog", "32 bit", nullptr));

        text_gi_channel_postfix->setText(QString());
        checkBox_normal_enabled->setText(QCoreApplication::translate("cImageSaveDialog", "Surface Normal", nullptr));
        comboBox_gi_channel_quality->setItemText(0, QCoreApplication::translate("cImageSaveDialog", "8 bit", nullptr));
        comboBox_gi_channel_quality->setItemText(1, QCoreApplication::translate("cImageSaveDialog", "16 bit", nullptr));
        comboBox_gi_channel_quality->setItemText(2, QCoreApplication::translate("cImageSaveDialog", "32 bit", nullptr));

        text_specular_postfix->setText(QString());
        comboBox_normal_quality->setItemText(0, QCoreApplication::translate("cImageSaveDialog", "8 bit", nullptr));
        comboBox_normal_quality->setItemText(1, QCoreApplication::translate("cImageSaveDialog", "16 bit", nullptr));
        comboBox_normal_quality->setItemText(2, QCoreApplication::translate("cImageSaveDialog", "32 bit", nullptr));

        label_rerender_required_info->setText(QCoreApplication::translate("cImageSaveDialog", "Following channels are only rendered on demand\n"
"and will only be present after enabling and re-render.", nullptr));
        comboBox_diffuse_quality->setItemText(0, QCoreApplication::translate("cImageSaveDialog", "8 bit", nullptr));
        comboBox_diffuse_quality->setItemText(1, QCoreApplication::translate("cImageSaveDialog", "16 bit", nullptr));
        comboBox_diffuse_quality->setItemText(2, QCoreApplication::translate("cImageSaveDialog", "32 bit", nullptr));

        comboBox_normalWorld_quality->setItemText(0, QCoreApplication::translate("cImageSaveDialog", "8 bit", nullptr));
        comboBox_normalWorld_quality->setItemText(1, QCoreApplication::translate("cImageSaveDialog", "16 bit", nullptr));
        comboBox_normalWorld_quality->setItemText(2, QCoreApplication::translate("cImageSaveDialog", "32 bit", nullptr));

        checkBox_not_denoised_channel_enabled->setText(QCoreApplication::translate("cImageSaveDialog", "Not denoised", nullptr));
        comboBox_not_denoised_channel_quality->setItemText(0, QCoreApplication::translate("cImageSaveDialog", "8 bit", nullptr));
        comboBox_not_denoised_channel_quality->setItemText(1, QCoreApplication::translate("cImageSaveDialog", "16 bit", nullptr));
        comboBox_not_denoised_channel_quality->setItemText(2, QCoreApplication::translate("cImageSaveDialog", "32 bit", nullptr));

        text_not_denoised_channel_postfix->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("cImageSaveDialog", "Misc Image Settings", nullptr));
        checkBox_append_alpha_png->setText(QCoreApplication::translate("cImageSaveDialog", "Append alpha to image (only PNG and TIFF)", nullptr));
        label_5->setText(QCoreApplication::translate("cImageSaveDialog", "JPEG quality:", nullptr));
        checkBox_linear_colorspace->setText(QCoreApplication::translate("cImageSaveDialog", "Use linear colorspace (only EXR)", nullptr));
        checkBox_save_channels_in_separate_folders->setText(QCoreApplication::translate("cImageSaveDialog", "Save each channel in separate folder", nullptr));
        checkBox_stereoscopic_in_separate_files->setText(QCoreApplication::translate("cImageSaveDialog", "Save stereoscopic left and right images in separate files\n"
"(stereoscopic mode has to be \"left-right\")", nullptr));
        checkBox_save_settings_with_image->setText(QCoreApplication::translate("cImageSaveDialog", "Save fractal settings together with the image", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cImageSaveDialog: public Ui_cImageSaveDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGE_SAVE_DIALOG_H
