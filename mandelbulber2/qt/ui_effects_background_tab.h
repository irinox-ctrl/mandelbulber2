/********************************************************************************
** Form generated from reading UI file 'effects_background_tab.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EFFECTS_BACKGROUND_TAB_H
#define UI_EFFECTS_BACKGROUND_TAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "buton_load_settings_from_widget.h"
#include "buton_random_settings_from_widget.h"
#include "buton_reset_settings_from_widget.h"
#include "buton_save_settings_from_widget.h"
#include "file_select_widget.h"
#include "my_color_button.h"
#include "my_combo_box.h"
#include "my_double_spin_box.h"
#include "my_group_box.h"

QT_BEGIN_NAMESPACE

class Ui_cEffectsBackgroundTab
{
public:
    QVBoxLayout *verticalLayout_66;
    QHBoxLayout *horizontalLayout_13;
    cButtonLoadSettingsFromWidget *pushButton_local_load_5;
    cButtonSaveSettingsFromWidget *pushButton_local_save_5;
    cButtonResetSettingsFromWidget *pushButton_local_reset_5;
    cButtonRandomSettingsFromWidget *pushButton_local_randomize_4;
    QSpacerItem *horizontalSpacer_6;
    QScrollArea *scrollArea_9;
    QWidget *scrollAreaWidgetContents_10;
    QVBoxLayout *verticalLayout_36;
    QGroupBox *groupBox_14;
    QVBoxLayout *verticalLayout_37;
    QGridLayout *gridLayout_15;
    MyColorButton *colorButton_background_color_1;
    QLabel *label_57;
    MyGroupBox *groupCheck_background_3_colors_enable;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout_3;
    MyColorButton *colorButton_background_color_3;
    QLabel *label_58;
    QLabel *label_59;
    MyColorButton *colorButton_background_color_2;
    QGridLayout *gridLayout_7;
    QLabel *label_223;
    MyDoubleSpinBox *spinbox_background_brightness;
    QLabel *label_227;
    MyDoubleSpinBox *spinbox_background_gamma;
    MyGroupBox *groupCheck_textured_background;
    QVBoxLayout *verticalLayout_38;
    QGridLayout *gridLayout_16;
    QLabel *label_90;
    QLabel *label_224;
    MyComboBox *comboBox_textured_background_map_type;
    QLabel *label_228;
    FileSelectWidget *text_file_background;
    MyDoubleSpinBox *spinbox_background_texture_offset_x;
    QLabel *label_232;
    QLabel *label_229;
    QLabel *label_230;
    MyDoubleSpinBox *spinbox_background_texture_offset_y;
    QLabel *label_226;
    QLabel *label_231;
    MyDoubleSpinBox *spinboxd3_background_rotation_x;
    QLabel *label_225;
    QLabel *label_61;
    MyDoubleSpinBox *spinbox_background_v_scale;
    MyDoubleSpinBox *spinboxd3_background_rotation_z;
    MyDoubleSpinBox *spinbox_background_h_scale;
    MyDoubleSpinBox *spinboxd3_background_rotation_y;
    QLabel *label_233;
    QSpacerItem *verticalSpacer_5;

    void setupUi(QWidget *cEffectsBackgroundTab)
    {
        if (cEffectsBackgroundTab->objectName().isEmpty())
            cEffectsBackgroundTab->setObjectName(QString::fromUtf8("cEffectsBackgroundTab"));
        verticalLayout_66 = new QVBoxLayout(cEffectsBackgroundTab);
        verticalLayout_66->setSpacing(2);
        verticalLayout_66->setObjectName(QString::fromUtf8("verticalLayout_66"));
        verticalLayout_66->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        pushButton_local_load_5 = new cButtonLoadSettingsFromWidget(cEffectsBackgroundTab);
        pushButton_local_load_5->setObjectName(QString::fromUtf8("pushButton_local_load_5"));

        horizontalLayout_13->addWidget(pushButton_local_load_5);

        pushButton_local_save_5 = new cButtonSaveSettingsFromWidget(cEffectsBackgroundTab);
        pushButton_local_save_5->setObjectName(QString::fromUtf8("pushButton_local_save_5"));

        horizontalLayout_13->addWidget(pushButton_local_save_5);

        pushButton_local_reset_5 = new cButtonResetSettingsFromWidget(cEffectsBackgroundTab);
        pushButton_local_reset_5->setObjectName(QString::fromUtf8("pushButton_local_reset_5"));

        horizontalLayout_13->addWidget(pushButton_local_reset_5);

        pushButton_local_randomize_4 = new cButtonRandomSettingsFromWidget(cEffectsBackgroundTab);
        pushButton_local_randomize_4->setObjectName(QString::fromUtf8("pushButton_local_randomize_4"));

        horizontalLayout_13->addWidget(pushButton_local_randomize_4);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_6);


        verticalLayout_66->addLayout(horizontalLayout_13);

        scrollArea_9 = new QScrollArea(cEffectsBackgroundTab);
        scrollArea_9->setObjectName(QString::fromUtf8("scrollArea_9"));
        scrollArea_9->setWidgetResizable(true);
        scrollAreaWidgetContents_10 = new QWidget();
        scrollAreaWidgetContents_10->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_10"));
        scrollAreaWidgetContents_10->setGeometry(QRect(0, 0, 442, 1058));
        verticalLayout_36 = new QVBoxLayout(scrollAreaWidgetContents_10);
        verticalLayout_36->setSpacing(2);
        verticalLayout_36->setObjectName(QString::fromUtf8("verticalLayout_36"));
        verticalLayout_36->setContentsMargins(2, 2, 2, 2);
        groupBox_14 = new QGroupBox(scrollAreaWidgetContents_10);
        groupBox_14->setObjectName(QString::fromUtf8("groupBox_14"));
        verticalLayout_37 = new QVBoxLayout(groupBox_14);
        verticalLayout_37->setSpacing(2);
        verticalLayout_37->setObjectName(QString::fromUtf8("verticalLayout_37"));
        verticalLayout_37->setContentsMargins(2, 2, 2, 2);
        gridLayout_15 = new QGridLayout();
        gridLayout_15->setSpacing(2);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        colorButton_background_color_1 = new MyColorButton(groupBox_14);
        colorButton_background_color_1->setObjectName(QString::fromUtf8("colorButton_background_color_1"));

        gridLayout_15->addWidget(colorButton_background_color_1, 0, 1, 1, 1);

        label_57 = new QLabel(groupBox_14);
        label_57->setObjectName(QString::fromUtf8("label_57"));

        gridLayout_15->addWidget(label_57, 0, 0, 1, 1);


        verticalLayout_37->addLayout(gridLayout_15);

        groupCheck_background_3_colors_enable = new MyGroupBox(groupBox_14);
        groupCheck_background_3_colors_enable->setObjectName(QString::fromUtf8("groupCheck_background_3_colors_enable"));
        groupCheck_background_3_colors_enable->setCheckable(true);
        verticalLayout_4 = new QVBoxLayout(groupCheck_background_3_colors_enable);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(2, 2, 2, 2);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        colorButton_background_color_3 = new MyColorButton(groupCheck_background_3_colors_enable);
        colorButton_background_color_3->setObjectName(QString::fromUtf8("colorButton_background_color_3"));

        gridLayout_3->addWidget(colorButton_background_color_3, 1, 1, 1, 1);

        label_58 = new QLabel(groupCheck_background_3_colors_enable);
        label_58->setObjectName(QString::fromUtf8("label_58"));

        gridLayout_3->addWidget(label_58, 0, 0, 1, 1);

        label_59 = new QLabel(groupCheck_background_3_colors_enable);
        label_59->setObjectName(QString::fromUtf8("label_59"));

        gridLayout_3->addWidget(label_59, 1, 0, 1, 1);

        colorButton_background_color_2 = new MyColorButton(groupCheck_background_3_colors_enable);
        colorButton_background_color_2->setObjectName(QString::fromUtf8("colorButton_background_color_2"));

        gridLayout_3->addWidget(colorButton_background_color_2, 0, 1, 1, 1);


        verticalLayout_4->addLayout(gridLayout_3);


        verticalLayout_37->addWidget(groupCheck_background_3_colors_enable);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        label_223 = new QLabel(groupBox_14);
        label_223->setObjectName(QString::fromUtf8("label_223"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_223->sizePolicy().hasHeightForWidth());
        label_223->setSizePolicy(sizePolicy);

        gridLayout_7->addWidget(label_223, 0, 0, 1, 1);

        spinbox_background_brightness = new MyDoubleSpinBox(groupBox_14);
        spinbox_background_brightness->setObjectName(QString::fromUtf8("spinbox_background_brightness"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(spinbox_background_brightness->sizePolicy().hasHeightForWidth());
        spinbox_background_brightness->setSizePolicy(sizePolicy1);
        spinbox_background_brightness->setDecimals(2);
        spinbox_background_brightness->setMaximum(1000.000000000000000);
        spinbox_background_brightness->setSingleStep(0.100000000000000);

        gridLayout_7->addWidget(spinbox_background_brightness, 0, 1, 1, 1);

        label_227 = new QLabel(groupBox_14);
        label_227->setObjectName(QString::fromUtf8("label_227"));
        sizePolicy.setHeightForWidth(label_227->sizePolicy().hasHeightForWidth());
        label_227->setSizePolicy(sizePolicy);

        gridLayout_7->addWidget(label_227, 1, 0, 1, 1);

        spinbox_background_gamma = new MyDoubleSpinBox(groupBox_14);
        spinbox_background_gamma->setObjectName(QString::fromUtf8("spinbox_background_gamma"));
        sizePolicy1.setHeightForWidth(spinbox_background_gamma->sizePolicy().hasHeightForWidth());
        spinbox_background_gamma->setSizePolicy(sizePolicy1);
        spinbox_background_gamma->setDecimals(2);
        spinbox_background_gamma->setMaximum(1000.000000000000000);
        spinbox_background_gamma->setSingleStep(0.100000000000000);

        gridLayout_7->addWidget(spinbox_background_gamma, 1, 1, 1, 1);


        verticalLayout_37->addLayout(gridLayout_7);


        verticalLayout_36->addWidget(groupBox_14);

        groupCheck_textured_background = new MyGroupBox(scrollAreaWidgetContents_10);
        groupCheck_textured_background->setObjectName(QString::fromUtf8("groupCheck_textured_background"));
        groupCheck_textured_background->setCheckable(true);
        verticalLayout_38 = new QVBoxLayout(groupCheck_textured_background);
        verticalLayout_38->setSpacing(2);
        verticalLayout_38->setObjectName(QString::fromUtf8("verticalLayout_38"));
        verticalLayout_38->setContentsMargins(2, 2, 2, 2);
        gridLayout_16 = new QGridLayout();
        gridLayout_16->setSpacing(2);
        gridLayout_16->setObjectName(QString::fromUtf8("gridLayout_16"));
        label_90 = new QLabel(groupCheck_textured_background);
        label_90->setObjectName(QString::fromUtf8("label_90"));
        sizePolicy.setHeightForWidth(label_90->sizePolicy().hasHeightForWidth());
        label_90->setSizePolicy(sizePolicy);

        gridLayout_16->addWidget(label_90, 1, 0, 1, 1);

        label_224 = new QLabel(groupCheck_textured_background);
        label_224->setObjectName(QString::fromUtf8("label_224"));
        sizePolicy.setHeightForWidth(label_224->sizePolicy().hasHeightForWidth());
        label_224->setSizePolicy(sizePolicy);

        gridLayout_16->addWidget(label_224, 3, 0, 1, 1);

        comboBox_textured_background_map_type = new MyComboBox(groupCheck_textured_background);
        comboBox_textured_background_map_type->addItem(QString());
        comboBox_textured_background_map_type->addItem(QString());
        comboBox_textured_background_map_type->addItem(QString());
        comboBox_textured_background_map_type->setObjectName(QString::fromUtf8("comboBox_textured_background_map_type"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(comboBox_textured_background_map_type->sizePolicy().hasHeightForWidth());
        comboBox_textured_background_map_type->setSizePolicy(sizePolicy2);

        gridLayout_16->addWidget(comboBox_textured_background_map_type, 1, 1, 1, 2);

        label_228 = new QLabel(groupCheck_textured_background);
        label_228->setObjectName(QString::fromUtf8("label_228"));
        label_228->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_16->addWidget(label_228, 7, 1, 1, 1);

        text_file_background = new FileSelectWidget(groupCheck_textured_background);
        text_file_background->setObjectName(QString::fromUtf8("text_file_background"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(text_file_background->sizePolicy().hasHeightForWidth());
        text_file_background->setSizePolicy(sizePolicy3);

        gridLayout_16->addWidget(text_file_background, 0, 1, 1, 2);

        spinbox_background_texture_offset_x = new MyDoubleSpinBox(groupCheck_textured_background);
        spinbox_background_texture_offset_x->setObjectName(QString::fromUtf8("spinbox_background_texture_offset_x"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(spinbox_background_texture_offset_x->sizePolicy().hasHeightForWidth());
        spinbox_background_texture_offset_x->setSizePolicy(sizePolicy4);
        spinbox_background_texture_offset_x->setDecimals(4);
        spinbox_background_texture_offset_x->setMinimum(-1000.000000000000000);
        spinbox_background_texture_offset_x->setMaximum(1000.000000000000000);
        spinbox_background_texture_offset_x->setSingleStep(0.001000000000000);

        gridLayout_16->addWidget(spinbox_background_texture_offset_x, 4, 2, 1, 1);

        label_232 = new QLabel(groupCheck_textured_background);
        label_232->setObjectName(QString::fromUtf8("label_232"));
        label_232->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_16->addWidget(label_232, 6, 1, 1, 1);

        label_229 = new QLabel(groupCheck_textured_background);
        label_229->setObjectName(QString::fromUtf8("label_229"));
        label_229->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_16->addWidget(label_229, 8, 1, 1, 1);

        label_230 = new QLabel(groupCheck_textured_background);
        label_230->setObjectName(QString::fromUtf8("label_230"));
        sizePolicy.setHeightForWidth(label_230->sizePolicy().hasHeightForWidth());
        label_230->setSizePolicy(sizePolicy);

        gridLayout_16->addWidget(label_230, 4, 0, 2, 1);

        spinbox_background_texture_offset_y = new MyDoubleSpinBox(groupCheck_textured_background);
        spinbox_background_texture_offset_y->setObjectName(QString::fromUtf8("spinbox_background_texture_offset_y"));
        sizePolicy4.setHeightForWidth(spinbox_background_texture_offset_y->sizePolicy().hasHeightForWidth());
        spinbox_background_texture_offset_y->setSizePolicy(sizePolicy4);
        spinbox_background_texture_offset_y->setDecimals(4);
        spinbox_background_texture_offset_y->setMinimum(-1000.000000000000000);
        spinbox_background_texture_offset_y->setMaximum(1000.000000000000000);
        spinbox_background_texture_offset_y->setSingleStep(0.001000000000000);

        gridLayout_16->addWidget(spinbox_background_texture_offset_y, 5, 2, 1, 1);

        label_226 = new QLabel(groupCheck_textured_background);
        label_226->setObjectName(QString::fromUtf8("label_226"));
        sizePolicy.setHeightForWidth(label_226->sizePolicy().hasHeightForWidth());
        label_226->setSizePolicy(sizePolicy);

        gridLayout_16->addWidget(label_226, 6, 0, 3, 1);

        label_231 = new QLabel(groupCheck_textured_background);
        label_231->setObjectName(QString::fromUtf8("label_231"));
        label_231->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_16->addWidget(label_231, 4, 1, 1, 1);

        spinboxd3_background_rotation_x = new MyDoubleSpinBox(groupCheck_textured_background);
        spinboxd3_background_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_background_rotation_x"));
        sizePolicy4.setHeightForWidth(spinboxd3_background_rotation_x->sizePolicy().hasHeightForWidth());
        spinboxd3_background_rotation_x->setSizePolicy(sizePolicy4);
        spinboxd3_background_rotation_x->setAccelerated(true);
        spinboxd3_background_rotation_x->setDecimals(2);
        spinboxd3_background_rotation_x->setMinimum(-180.000000000000000);
        spinboxd3_background_rotation_x->setMaximum(180.000000000000000);
        spinboxd3_background_rotation_x->setSingleStep(1.000000000000000);

        gridLayout_16->addWidget(spinboxd3_background_rotation_x, 6, 2, 1, 1);

        label_225 = new QLabel(groupCheck_textured_background);
        label_225->setObjectName(QString::fromUtf8("label_225"));
        sizePolicy.setHeightForWidth(label_225->sizePolicy().hasHeightForWidth());
        label_225->setSizePolicy(sizePolicy);

        gridLayout_16->addWidget(label_225, 2, 0, 1, 1);

        label_61 = new QLabel(groupCheck_textured_background);
        label_61->setObjectName(QString::fromUtf8("label_61"));
        sizePolicy.setHeightForWidth(label_61->sizePolicy().hasHeightForWidth());
        label_61->setSizePolicy(sizePolicy);

        gridLayout_16->addWidget(label_61, 0, 0, 1, 1);

        spinbox_background_v_scale = new MyDoubleSpinBox(groupCheck_textured_background);
        spinbox_background_v_scale->setObjectName(QString::fromUtf8("spinbox_background_v_scale"));
        sizePolicy4.setHeightForWidth(spinbox_background_v_scale->sizePolicy().hasHeightForWidth());
        spinbox_background_v_scale->setSizePolicy(sizePolicy4);
        spinbox_background_v_scale->setDecimals(3);
        spinbox_background_v_scale->setMaximum(10000.000000000000000);
        spinbox_background_v_scale->setSingleStep(0.010000000000000);

        gridLayout_16->addWidget(spinbox_background_v_scale, 3, 2, 1, 1);

        spinboxd3_background_rotation_z = new MyDoubleSpinBox(groupCheck_textured_background);
        spinboxd3_background_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_background_rotation_z"));
        sizePolicy4.setHeightForWidth(spinboxd3_background_rotation_z->sizePolicy().hasHeightForWidth());
        spinboxd3_background_rotation_z->setSizePolicy(sizePolicy4);
        spinboxd3_background_rotation_z->setAccelerated(true);
        spinboxd3_background_rotation_z->setDecimals(2);
        spinboxd3_background_rotation_z->setMinimum(-180.000000000000000);
        spinboxd3_background_rotation_z->setMaximum(180.000000000000000);
        spinboxd3_background_rotation_z->setSingleStep(1.000000000000000);

        gridLayout_16->addWidget(spinboxd3_background_rotation_z, 8, 2, 1, 1);

        spinbox_background_h_scale = new MyDoubleSpinBox(groupCheck_textured_background);
        spinbox_background_h_scale->setObjectName(QString::fromUtf8("spinbox_background_h_scale"));
        sizePolicy4.setHeightForWidth(spinbox_background_h_scale->sizePolicy().hasHeightForWidth());
        spinbox_background_h_scale->setSizePolicy(sizePolicy4);
        spinbox_background_h_scale->setDecimals(3);
        spinbox_background_h_scale->setMaximum(10000.000000000000000);
        spinbox_background_h_scale->setSingleStep(0.010000000000000);

        gridLayout_16->addWidget(spinbox_background_h_scale, 2, 2, 1, 1);

        spinboxd3_background_rotation_y = new MyDoubleSpinBox(groupCheck_textured_background);
        spinboxd3_background_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_background_rotation_y"));
        sizePolicy4.setHeightForWidth(spinboxd3_background_rotation_y->sizePolicy().hasHeightForWidth());
        spinboxd3_background_rotation_y->setSizePolicy(sizePolicy4);
        spinboxd3_background_rotation_y->setAccelerated(true);
        spinboxd3_background_rotation_y->setDecimals(2);
        spinboxd3_background_rotation_y->setMinimum(-180.000000000000000);
        spinboxd3_background_rotation_y->setMaximum(180.000000000000000);
        spinboxd3_background_rotation_y->setSingleStep(1.000000000000000);

        gridLayout_16->addWidget(spinboxd3_background_rotation_y, 7, 2, 1, 1);

        label_233 = new QLabel(groupCheck_textured_background);
        label_233->setObjectName(QString::fromUtf8("label_233"));
        label_233->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_16->addWidget(label_233, 5, 1, 1, 1);


        verticalLayout_38->addLayout(gridLayout_16);


        verticalLayout_36->addWidget(groupCheck_textured_background);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_36->addItem(verticalSpacer_5);

        scrollArea_9->setWidget(scrollAreaWidgetContents_10);

        verticalLayout_66->addWidget(scrollArea_9);


        retranslateUi(cEffectsBackgroundTab);

        QMetaObject::connectSlotsByName(cEffectsBackgroundTab);
    } // setupUi

    void retranslateUi(QWidget *cEffectsBackgroundTab)
    {
        pushButton_local_load_5->setText(QCoreApplication::translate("cEffectsBackgroundTab", "Laden", nullptr));
        pushButton_local_save_5->setText(QCoreApplication::translate("cEffectsBackgroundTab", "Opslaan", nullptr));
        pushButton_local_reset_5->setText(QCoreApplication::translate("cEffectsBackgroundTab", "Reset", nullptr));
        pushButton_local_randomize_4->setText(QCoreApplication::translate("cEffectsBackgroundTab", "Randomize", nullptr));
        groupBox_14->setTitle(QCoreApplication::translate("cEffectsBackgroundTab", "Colored background", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_background_color_1->setToolTip(QCoreApplication::translate("cEffectsBackgroundTab", "<html><head/><body><p>Color of background at zenith</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_background_color_1->setProperty("text", QVariant(QCoreApplication::translate("cEffectsBackgroundTab", "PushButton", nullptr)));
        label_57->setText(QCoreApplication::translate("cEffectsBackgroundTab", "Color #1:", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_background_3_colors_enable->setToolTip(QCoreApplication::translate("cEffectsBackgroundTab", "Enables colored gradient on background. When disabled only color #1 is used.", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_background_3_colors_enable->setTitle(QCoreApplication::translate("cEffectsBackgroundTab", "&3-color gradient", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_background_color_3->setToolTip(QCoreApplication::translate("cEffectsBackgroundTab", "<html><head/><body><p>Color of background at nadir</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_background_color_3->setProperty("text", QVariant(QCoreApplication::translate("cEffectsBackgroundTab", "PushButton", nullptr)));
        label_58->setText(QCoreApplication::translate("cEffectsBackgroundTab", "Color #2:", nullptr));
        label_59->setText(QCoreApplication::translate("cEffectsBackgroundTab", "Color #3:", nullptr));
#if QT_CONFIG(tooltip)
        colorButton_background_color_2->setToolTip(QCoreApplication::translate("cEffectsBackgroundTab", "<html><head/><body><p>Color of background at horizon</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_background_color_2->setProperty("text", QVariant(QCoreApplication::translate("cEffectsBackgroundTab", "PushButton", nullptr)));
        label_223->setText(QCoreApplication::translate("cEffectsBackgroundTab", "Brightness:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_background_brightness->setToolTip(QCoreApplication::translate("cEffectsBackgroundTab", "<html><head/><body><p>Brightness of background</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_background_brightness->setPrefix(QString());
        spinbox_background_brightness->setSuffix(QString());
        label_227->setText(QCoreApplication::translate("cEffectsBackgroundTab", "Gamma", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_background_gamma->setToolTip(QCoreApplication::translate("cEffectsBackgroundTab", "<html><head/><body><p>Gamma correction for the background (colors or texture), applied after Background brightness. </p><p>1.0 = no change; &gt;1 brightens midtones; &lt;1 darkens. </p><p>Affects only the background, not scene lighting or objects. </p><p>Typical range: ~0.8\342\200\2232.5.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_background_gamma->setPrefix(QString());
        spinbox_background_gamma->setSuffix(QString());
#if QT_CONFIG(tooltip)
        groupCheck_textured_background->setToolTip(QCoreApplication::translate("cEffectsBackgroundTab", "<html><head/><body><p>Enables covering of background sphere with selected image.</p><p>Example:</p><p><img src=\":/tooltips/tooltips_images/image - shader - backhround texture.jpg\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_textured_background->setTitle(QCoreApplication::translate("cEffectsBackgroundTab", "Text&ured background", nullptr));
        label_90->setText(QCoreApplication::translate("cEffectsBackgroundTab", "Map type:", nullptr));
        label_224->setText(QCoreApplication::translate("cEffectsBackgroundTab", "Vertical scale:", nullptr));
        comboBox_textured_background_map_type->setItemText(0, QCoreApplication::translate("cEffectsBackgroundTab", "Equirectangular", nullptr));
        comboBox_textured_background_map_type->setItemText(1, QCoreApplication::translate("cEffectsBackgroundTab", "Double hemisphere", nullptr));
        comboBox_textured_background_map_type->setItemText(2, QCoreApplication::translate("cEffectsBackgroundTab", "Flat", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_textured_background_map_type->setToolTip(QCoreApplication::translate("cEffectsBackgroundTab", "<html><head/><body><p>It determines, how texture will be mapped on background sphere</p><p><span style=\" font-weight:600;\">Equirectangular: <br/></span><span style=\" font-weight:400;\">Texture has to be created used equirectangular projection. It's the most popular format for textures dedicated for sphere mapping.<br/>Example:<br/></span><img src=\":/tooltips/tooltips_images/equirectangular_bkg.jpg\"/></p><p><span style=\" font-weight:600;\">Double hemisphere:</span></p><p>Texture has to be created as a pair of images of hemispheres. Mapping has to be the same as <span style=\" font-style:italic;\">Full dome projection</span> (or <span style=\" font-style:italic;\">Fish eye</span>)<br/>Example texture with indicated axes and directions:<br/><img src=\":/tooltips/tooltips_images/full_dome_bkg_axes.png\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_228->setText(QCoreApplication::translate("cEffectsBackgroundTab", "Beta:", nullptr));
#if QT_CONFIG(tooltip)
        text_file_background->setToolTip(QCoreApplication::translate("cEffectsBackgroundTab", "<html><head/><body><p>Path to the background image. Acceptable formats are BMP, GIF, JPG, PNG</p><p>To use animated textures (image sequences), replace numbers by '%' symbol. Example: If sequence of images is as showed below: <br/>texture0001.jpg<br/>texture0002.jpg<br/>etc</p><p>Then use following file name: texture%%%%.jpg<br/>This tells the program to treat this as not a single image but as a sequence of images with 4 digit index.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_background_texture_offset_x->setPrefix(QString());
        spinbox_background_texture_offset_x->setSuffix(QString());
        label_232->setText(QCoreApplication::translate("cEffectsBackgroundTab", "Alpha:", nullptr));
        label_229->setText(QCoreApplication::translate("cEffectsBackgroundTab", "Gamma:", nullptr));
        label_230->setText(QCoreApplication::translate("cEffectsBackgroundTab", "Texture offset:", nullptr));
        spinbox_background_texture_offset_y->setPrefix(QString());
        spinbox_background_texture_offset_y->setSuffix(QString());
        label_226->setText(QCoreApplication::translate("cEffectsBackgroundTab", "Rotatie:", nullptr));
        label_231->setText(QCoreApplication::translate("cEffectsBackgroundTab", "x:", nullptr));
        spinboxd3_background_rotation_x->setPrefix(QString());
        spinboxd3_background_rotation_x->setSuffix(QString());
        label_225->setText(QCoreApplication::translate("cEffectsBackgroundTab", "Horizontal scale:", nullptr));
        label_61->setText(QCoreApplication::translate("cEffectsBackgroundTab", "Texture path:", nullptr));
        spinbox_background_v_scale->setPrefix(QString());
        spinbox_background_v_scale->setSuffix(QString());
        spinboxd3_background_rotation_z->setPrefix(QString());
        spinboxd3_background_rotation_z->setSuffix(QString());
        spinbox_background_h_scale->setPrefix(QString());
        spinbox_background_h_scale->setSuffix(QString());
        spinboxd3_background_rotation_y->setPrefix(QString());
        spinboxd3_background_rotation_y->setSuffix(QString());
        label_233->setText(QCoreApplication::translate("cEffectsBackgroundTab", "y:", nullptr));
        (void)cEffectsBackgroundTab;
    } // retranslateUi

};

namespace Ui {
    class cEffectsBackgroundTab: public Ui_cEffectsBackgroundTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EFFECTS_BACKGROUND_TAB_H
