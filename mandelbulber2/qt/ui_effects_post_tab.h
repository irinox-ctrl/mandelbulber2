/********************************************************************************
** Form generated from reading UI file 'effects_post_tab.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EFFECTS_POST_TAB_H
#define UI_EFFECTS_POST_TAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "buton_load_settings_from_widget.h"
#include "buton_random_settings_from_widget.h"
#include "buton_reset_settings_from_widget.h"
#include "buton_save_settings_from_widget.h"
#include "my_check_box.h"
#include "my_double_spin_box.h"
#include "my_group_box.h"

QT_BEGIN_NAMESPACE

class Ui_cEffectsPostTab
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_15;
    cButtonLoadSettingsFromWidget *pushButton_local_load_7;
    cButtonSaveSettingsFromWidget *pushButton_local_save_7;
    cButtonResetSettingsFromWidget *pushButton_local_reset_7;
    cButtonRandomSettingsFromWidget *pushButton_local_randomize_6;
    QSpacerItem *horizontalSpacer_8;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton_post_effects_update;
    MyGroupBox *groupCheck_hdr_blur_enabled;
    QVBoxLayout *verticalLayout_74;
    QGridLayout *gridLayout_36;
    MyDoubleSpinBox *spinbox_hdr_blur_radius;
    QLabel *label_137;
    QLabel *label_352;
    MyDoubleSpinBox *spinbox_hdr_blur_intensity;
    MyGroupBox *groupCheck_post_chromatic_aberration_enabled;
    QVBoxLayout *verticalLayout_76;
    QGridLayout *gridLayout_37;
    QLabel *label_353;
    MyDoubleSpinBox *spinbox_post_chromatic_aberration_intensity;
    MyDoubleSpinBox *spinbox_post_chromatic_aberration_radius;
    QLabel *label_139;
    MyCheckBox *checkBox_post_chromatic_aberration_reverse;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *cEffectsPostTab)
    {
        if (cEffectsPostTab->objectName().isEmpty())
            cEffectsPostTab->setObjectName(QString::fromUtf8("cEffectsPostTab"));
        verticalLayout_2 = new QVBoxLayout(cEffectsPostTab);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(2, -1, 2, 2);
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        pushButton_local_load_7 = new cButtonLoadSettingsFromWidget(cEffectsPostTab);
        pushButton_local_load_7->setObjectName(QString::fromUtf8("pushButton_local_load_7"));

        horizontalLayout_15->addWidget(pushButton_local_load_7);

        pushButton_local_save_7 = new cButtonSaveSettingsFromWidget(cEffectsPostTab);
        pushButton_local_save_7->setObjectName(QString::fromUtf8("pushButton_local_save_7"));

        horizontalLayout_15->addWidget(pushButton_local_save_7);

        pushButton_local_reset_7 = new cButtonResetSettingsFromWidget(cEffectsPostTab);
        pushButton_local_reset_7->setObjectName(QString::fromUtf8("pushButton_local_reset_7"));

        horizontalLayout_15->addWidget(pushButton_local_reset_7);

        pushButton_local_randomize_6 = new cButtonRandomSettingsFromWidget(cEffectsPostTab);
        pushButton_local_randomize_6->setObjectName(QString::fromUtf8("pushButton_local_randomize_6"));

        horizontalLayout_15->addWidget(pushButton_local_randomize_6);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_8);


        verticalLayout_2->addLayout(horizontalLayout_15);

        scrollArea = new QScrollArea(cEffectsPostTab);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 442, 1050));
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(2, 2, 2, 2);
        pushButton_post_effects_update = new QPushButton(scrollAreaWidgetContents);
        pushButton_post_effects_update->setObjectName(QString::fromUtf8("pushButton_post_effects_update"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_post_effects_update->sizePolicy().hasHeightForWidth());
        pushButton_post_effects_update->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(pushButton_post_effects_update);

        groupCheck_hdr_blur_enabled = new MyGroupBox(scrollAreaWidgetContents);
        groupCheck_hdr_blur_enabled->setObjectName(QString::fromUtf8("groupCheck_hdr_blur_enabled"));
        groupCheck_hdr_blur_enabled->setCheckable(true);
        verticalLayout_74 = new QVBoxLayout(groupCheck_hdr_blur_enabled);
        verticalLayout_74->setSpacing(2);
        verticalLayout_74->setObjectName(QString::fromUtf8("verticalLayout_74"));
        verticalLayout_74->setContentsMargins(2, 2, 2, 2);
        gridLayout_36 = new QGridLayout();
        gridLayout_36->setSpacing(2);
        gridLayout_36->setObjectName(QString::fromUtf8("gridLayout_36"));
        spinbox_hdr_blur_radius = new MyDoubleSpinBox(groupCheck_hdr_blur_enabled);
        spinbox_hdr_blur_radius->setObjectName(QString::fromUtf8("spinbox_hdr_blur_radius"));
        sizePolicy.setHeightForWidth(spinbox_hdr_blur_radius->sizePolicy().hasHeightForWidth());
        spinbox_hdr_blur_radius->setSizePolicy(sizePolicy);
        spinbox_hdr_blur_radius->setDecimals(3);
        spinbox_hdr_blur_radius->setMinimum(0.001000000000000);
        spinbox_hdr_blur_radius->setMaximum(1000.000000000000000);
        spinbox_hdr_blur_radius->setSingleStep(1.000000000000000);
        spinbox_hdr_blur_radius->setValue(1.000000000000000);

        gridLayout_36->addWidget(spinbox_hdr_blur_radius, 0, 1, 1, 1);

        label_137 = new QLabel(groupCheck_hdr_blur_enabled);
        label_137->setObjectName(QString::fromUtf8("label_137"));

        gridLayout_36->addWidget(label_137, 0, 0, 1, 1);

        label_352 = new QLabel(groupCheck_hdr_blur_enabled);
        label_352->setObjectName(QString::fromUtf8("label_352"));

        gridLayout_36->addWidget(label_352, 1, 0, 1, 1);

        spinbox_hdr_blur_intensity = new MyDoubleSpinBox(groupCheck_hdr_blur_enabled);
        spinbox_hdr_blur_intensity->setObjectName(QString::fromUtf8("spinbox_hdr_blur_intensity"));
        sizePolicy.setHeightForWidth(spinbox_hdr_blur_intensity->sizePolicy().hasHeightForWidth());
        spinbox_hdr_blur_intensity->setSizePolicy(sizePolicy);
        spinbox_hdr_blur_intensity->setDecimals(4);
        spinbox_hdr_blur_intensity->setMinimum(0.000000000000000);
        spinbox_hdr_blur_intensity->setMaximum(100.000000000000000);
        spinbox_hdr_blur_intensity->setSingleStep(0.010000000000000);
        spinbox_hdr_blur_intensity->setValue(0.100000000000000);

        gridLayout_36->addWidget(spinbox_hdr_blur_intensity, 1, 1, 1, 1);


        verticalLayout_74->addLayout(gridLayout_36);


        verticalLayout_3->addWidget(groupCheck_hdr_blur_enabled);

        groupCheck_post_chromatic_aberration_enabled = new MyGroupBox(scrollAreaWidgetContents);
        groupCheck_post_chromatic_aberration_enabled->setObjectName(QString::fromUtf8("groupCheck_post_chromatic_aberration_enabled"));
        groupCheck_post_chromatic_aberration_enabled->setCheckable(true);
        verticalLayout_76 = new QVBoxLayout(groupCheck_post_chromatic_aberration_enabled);
        verticalLayout_76->setSpacing(2);
        verticalLayout_76->setObjectName(QString::fromUtf8("verticalLayout_76"));
        verticalLayout_76->setContentsMargins(2, 2, 2, 2);
        gridLayout_37 = new QGridLayout();
        gridLayout_37->setSpacing(2);
        gridLayout_37->setObjectName(QString::fromUtf8("gridLayout_37"));
        label_353 = new QLabel(groupCheck_post_chromatic_aberration_enabled);
        label_353->setObjectName(QString::fromUtf8("label_353"));

        gridLayout_37->addWidget(label_353, 1, 0, 1, 1);

        spinbox_post_chromatic_aberration_intensity = new MyDoubleSpinBox(groupCheck_post_chromatic_aberration_enabled);
        spinbox_post_chromatic_aberration_intensity->setObjectName(QString::fromUtf8("spinbox_post_chromatic_aberration_intensity"));
        sizePolicy.setHeightForWidth(spinbox_post_chromatic_aberration_intensity->sizePolicy().hasHeightForWidth());
        spinbox_post_chromatic_aberration_intensity->setSizePolicy(sizePolicy);
        spinbox_post_chromatic_aberration_intensity->setDecimals(3);
        spinbox_post_chromatic_aberration_intensity->setMinimum(0.000000000000000);
        spinbox_post_chromatic_aberration_intensity->setMaximum(100.000000000000000);
        spinbox_post_chromatic_aberration_intensity->setSingleStep(0.010000000000000);
        spinbox_post_chromatic_aberration_intensity->setValue(1.000000000000000);

        gridLayout_37->addWidget(spinbox_post_chromatic_aberration_intensity, 1, 1, 1, 1);

        spinbox_post_chromatic_aberration_radius = new MyDoubleSpinBox(groupCheck_post_chromatic_aberration_enabled);
        spinbox_post_chromatic_aberration_radius->setObjectName(QString::fromUtf8("spinbox_post_chromatic_aberration_radius"));
        sizePolicy.setHeightForWidth(spinbox_post_chromatic_aberration_radius->sizePolicy().hasHeightForWidth());
        spinbox_post_chromatic_aberration_radius->setSizePolicy(sizePolicy);
        spinbox_post_chromatic_aberration_radius->setDecimals(3);
        spinbox_post_chromatic_aberration_radius->setMinimum(0.000000000000000);
        spinbox_post_chromatic_aberration_radius->setMaximum(1000.000000000000000);
        spinbox_post_chromatic_aberration_radius->setSingleStep(0.100000000000000);
        spinbox_post_chromatic_aberration_radius->setValue(1.000000000000000);

        gridLayout_37->addWidget(spinbox_post_chromatic_aberration_radius, 0, 1, 1, 1);

        label_139 = new QLabel(groupCheck_post_chromatic_aberration_enabled);
        label_139->setObjectName(QString::fromUtf8("label_139"));

        gridLayout_37->addWidget(label_139, 0, 0, 1, 1);

        checkBox_post_chromatic_aberration_reverse = new MyCheckBox(groupCheck_post_chromatic_aberration_enabled);
        checkBox_post_chromatic_aberration_reverse->setObjectName(QString::fromUtf8("checkBox_post_chromatic_aberration_reverse"));
        sizePolicy.setHeightForWidth(checkBox_post_chromatic_aberration_reverse->sizePolicy().hasHeightForWidth());
        checkBox_post_chromatic_aberration_reverse->setSizePolicy(sizePolicy);

        gridLayout_37->addWidget(checkBox_post_chromatic_aberration_reverse, 2, 0, 1, 2);


        verticalLayout_76->addLayout(gridLayout_37);


        verticalLayout_3->addWidget(groupCheck_post_chromatic_aberration_enabled);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);


        retranslateUi(cEffectsPostTab);

        QMetaObject::connectSlotsByName(cEffectsPostTab);
    } // setupUi

    void retranslateUi(QWidget *cEffectsPostTab)
    {
        pushButton_local_load_7->setText(QCoreApplication::translate("cEffectsPostTab", "Laden", nullptr));
        pushButton_local_save_7->setText(QCoreApplication::translate("cEffectsPostTab", "Opslaan", nullptr));
        pushButton_local_reset_7->setText(QCoreApplication::translate("cEffectsPostTab", "Reset", nullptr));
        pushButton_local_randomize_6->setText(QCoreApplication::translate("cEffectsPostTab", "Randomize", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_post_effects_update->setToolTip(QCoreApplication::translate("cEffectsPostTab", "<html><head/><body><p>Update image after changes of DOF settings. Can be updated even after image rendering.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_post_effects_update->setText(QCoreApplication::translate("cEffectsPostTab", "Update image", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_hdr_blur_enabled->setToolTip(QCoreApplication::translate("cEffectsPostTab", "<html><head/><body><p>Enable the HDR Blur post effect (bloom-like glow on bright areas).</p><p>This applies a weighted blur in HDR space after rendering. Controls below: - Radius: overall spread of the blur (image-size relative). - Intensity: strength/threshold of the blur contribution.</p><p>Notes: - Operates on HDR image data; does not change lighting or exposure. - Uses OpenCL if available, otherwise CPU. - Larger Radius increases render time.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_hdr_blur_enabled->setTitle(QCoreApplication::translate("cEffectsPostTab", "HDR Bl&ur", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_hdr_blur_radius->setToolTip(QCoreApplication::translate("cEffectsPostTab", "<html><head/><body><p>Sets the radius (spread) of the HDR Blur bloom.</p><p>The blur size is relative to image dimensions. Approximate pixel radius = radius \303\227 (image width + image height) \303\227 0.001.</p><p>Larger values give a wider, softer glow; smaller values keep highlights tight. Bigger radius increases processing time. Works with Intensity to control strength.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_hdr_blur_radius->setPrefix(QString());
        spinbox_hdr_blur_radius->setSuffix(QString());
        label_137->setText(QCoreApplication::translate("cEffectsPostTab", "Blur radius:", nullptr));
        label_352->setText(QCoreApplication::translate("cEffectsPostTab", "Intensiteit:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_hdr_blur_intensity->setToolTip(QCoreApplication::translate("cEffectsPostTab", "<html><head/><body><p>Copilot said: </p><p>Controls the strength/threshold of the HDR Blur </p><p>Controls the strength/threshold of the HDR Blur contribution.</p><p>Lower values produce a stronger, brighter bloom; higher values dampen the effect. Works together with Radius (spread) but does not change blur size.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_hdr_blur_intensity->setPrefix(QString());
        spinbox_hdr_blur_intensity->setSuffix(QString());
#if QT_CONFIG(tooltip)
        groupCheck_post_chromatic_aberration_enabled->setToolTip(QCoreApplication::translate("cEffectsPostTab", "<html><head/><body><p>Enable the Chromatic Aberration post effect (RGB channel separation).</p><p>This simulates lens dispersion by shifting color channels radially from the image center.</p><p>Controls inside: - Radius: overall spread of the separation (relative to image size). - Aberration intensity: strength of the channel offset. - Reverse: flip direction (outward vs inward shift).</p><p>Notes: - Post-processing only; does not affect lighting or geometry. - Uses OpenCL if available.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_post_chromatic_aberration_enabled->setTitle(QCoreApplication::translate("cEffectsPostTab", "Chromatic aberration", nullptr));
        label_353->setText(QCoreApplication::translate("cEffectsPostTab", "Aberration intensity:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_post_chromatic_aberration_intensity->setToolTip(QCoreApplication::translate("cEffectsPostTab", "<html><head/><body><p>Controls the strength of RGB channel separation (color fringing) in Chromatic Aberration.</p><p>Higher values increase the offset between color channels and widen the visible fringes, especially toward the image edges. Lower values keep the effect subtle. Works together with Radius (spread) and does not change direction (use Reverse to flip).</p><p>Notes: - Stronger intensity can increase processing time. - Post-processing only; does not affect lighting or geometry.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_post_chromatic_aberration_intensity->setPrefix(QString());
        spinbox_post_chromatic_aberration_intensity->setSuffix(QString());
#if QT_CONFIG(tooltip)
        spinbox_post_chromatic_aberration_radius->setToolTip(QCoreApplication::translate("cEffectsPostTab", "<html><head/><body><p>Sets the base radius (spread) of Chromatic Aberration.</p><p>The effective spread is relative to image size and grows with distance from the image center, producing wider color fringing toward the edges. Increase for more pronounced, wider separation; decrease to keep fringes tight.</p><p>Notes: - Works with Aberration intensity (strength); does not change direction (see Reverse). - Larger values increase processing time.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_post_chromatic_aberration_radius->setPrefix(QString());
        spinbox_post_chromatic_aberration_radius->setSuffix(QString());
        label_139->setText(QCoreApplication::translate("cEffectsPostTab", "Blur radius:", nullptr));
        checkBox_post_chromatic_aberration_reverse->setText(QCoreApplication::translate("cEffectsPostTab", "Reverse color order", nullptr));
        (void)cEffectsPostTab;
    } // retranslateUi

};

namespace Ui {
    class cEffectsPostTab: public Ui_cEffectsPostTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EFFECTS_POST_TAB_H
