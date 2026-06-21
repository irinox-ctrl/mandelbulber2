/********************************************************************************
** Form generated from reading UI file 'dock_effects.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCK_EFFECTS_H
#define UI_DOCK_EFFECTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <effects_background_tab.h>
#include <effects_lights_tab.h>
#include <effects_post_tab.h>
#include <effects_raytracing_tab.h>
#include <effects_single_trap_tab.h>
#include <effects_volumetric_tab.h>
#include "buton_load_settings_from_widget.h"
#include "buton_random_settings_from_widget.h"
#include "buton_reset_settings_from_widget.h"
#include "buton_save_settings_from_widget.h"
#include "file_select_widget.h"
#include "light_sources_manager.h"
#include "my_check_box.h"
#include "my_color_button.h"
#include "my_combo_box.h"
#include "my_double_spin_box.h"
#include "my_group_box.h"
#include "my_line_edit.h"
#include "my_spin_box.h"

QT_BEGIN_NAMESPACE

class Ui_cDockEffects
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    cButtonLoadSettingsFromWidget *pushButton_local_load;
    cButtonSaveSettingsFromWidget *pushButton_local_save;
    cButtonResetSettingsFromWidget *pushButton_local_reset;
    cButtonRandomSettingsFromWidget *pushButton_local_randomize_7;
    QPushButton *pushButton_local_navi;
    QSpacerItem *horizontalSpacer;
    QTabWidget *tabWidget_effects;
    cEffectsRaytracingTab *tab_raytracing;
    cEffectsVolumetricTab *tab_volumetric;
    cEffectsBackgroundTab *tab_background;
    cEffectsLightsTab *tab_lights;
    cEffectsSingleTrapTab *tab_single_trap_lights;
    cEffectsPostTab *tab_postEffects;

    void setupUi(QWidget *cDockEffects)
    {
        if (cDockEffects->objectName().isEmpty())
            cDockEffects->setObjectName(QString::fromUtf8("cDockEffects"));
        cDockEffects->resize(489, 1156);
        verticalLayout = new QVBoxLayout(cDockEffects);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_local_load = new cButtonLoadSettingsFromWidget(cDockEffects);
        pushButton_local_load->setObjectName(QString::fromUtf8("pushButton_local_load"));

        horizontalLayout->addWidget(pushButton_local_load);

        pushButton_local_save = new cButtonSaveSettingsFromWidget(cDockEffects);
        pushButton_local_save->setObjectName(QString::fromUtf8("pushButton_local_save"));

        horizontalLayout->addWidget(pushButton_local_save);

        pushButton_local_reset = new cButtonResetSettingsFromWidget(cDockEffects);
        pushButton_local_reset->setObjectName(QString::fromUtf8("pushButton_local_reset"));

        horizontalLayout->addWidget(pushButton_local_reset);

        pushButton_local_randomize_7 = new cButtonRandomSettingsFromWidget(cDockEffects);
        pushButton_local_randomize_7->setObjectName(QString::fromUtf8("pushButton_local_randomize_7"));

        horizontalLayout->addWidget(pushButton_local_randomize_7);

        pushButton_local_navi = new QPushButton(cDockEffects);
        pushButton_local_navi->setObjectName(QString::fromUtf8("pushButton_local_navi"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_local_navi->sizePolicy().hasHeightForWidth());
        pushButton_local_navi->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(pushButton_local_navi);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        tabWidget_effects = new QTabWidget(cDockEffects);
        tabWidget_effects->setObjectName(QString::fromUtf8("tabWidget_effects"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget_effects->sizePolicy().hasHeightForWidth());
        tabWidget_effects->setSizePolicy(sizePolicy1);
        tabWidget_effects->setTabPosition(QTabWidget::West);
        tabWidget_effects->setUsesScrollButtons(true);
        tabWidget_effects->setMovable(true);
        tab_raytracing = new cEffectsRaytracingTab();
        tab_raytracing->setObjectName(QString::fromUtf8("tab_raytracing"));
        tabWidget_effects->addTab(tab_raytracing, QString());
        tab_volumetric = new cEffectsVolumetricTab();
        tab_volumetric->setObjectName(QString::fromUtf8("tab_volumetric"));
        tabWidget_effects->addTab(tab_volumetric, QString());
        tab_background = new cEffectsBackgroundTab();
        tab_background->setObjectName(QString::fromUtf8("tab_background"));
        tabWidget_effects->addTab(tab_background, QString());
        tab_lights = new cEffectsLightsTab();
        tab_lights->setObjectName(QString::fromUtf8("tab_lights"));
        tabWidget_effects->addTab(tab_lights, QString());
        tab_single_trap_lights = new cEffectsSingleTrapTab();
        tab_single_trap_lights->setObjectName(QString::fromUtf8("tab_single_trap_lights"));
        tabWidget_effects->addTab(tab_single_trap_lights, QString());
        tab_postEffects = new cEffectsPostTab();
        tab_postEffects->setObjectName(QString::fromUtf8("tab_postEffects"));
        tabWidget_effects->addTab(tab_postEffects, QString());

        verticalLayout->addWidget(tabWidget_effects);

        verticalLayout->setStretch(1, 1);

        retranslateUi(cDockEffects);

        tabWidget_effects->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(cDockEffects);
    } // setupUi

    void retranslateUi(QWidget *cDockEffects)
    {
        cDockEffects->setWindowTitle(QCoreApplication::translate("cDockEffects", "Form", nullptr));
        pushButton_local_load->setText(QCoreApplication::translate("cDockEffects", "Laden", nullptr));
        pushButton_local_save->setText(QCoreApplication::translate("cDockEffects", "Opslaan", nullptr));
        pushButton_local_reset->setText(QCoreApplication::translate("cDockEffects", "Reset", nullptr));
        pushButton_local_randomize_7->setText(QCoreApplication::translate("cDockEffects", "Randomize", nullptr));
        pushButton_local_navi->setText(QCoreApplication::translate("cDockEffects", "Navi", nullptr));
#if QT_CONFIG(tooltip)
        tabWidget_effects->setToolTip(QCoreApplication::translate("cDockEffects", "<html><head/><body><p>Flip the direction of Chromatic Aberration (RGB channel offset).</p><p>When enabled, the color fringing shifts in the opposite radial direction: - Off: channels shift outward from the image center. - On: channels shift inward toward the center. This also swaps the apparent order of the colored fringes.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        tabWidget_effects->setTabText(tabWidget_effects->indexOf(tab_raytracing), QCoreApplication::translate("cDockEffects", "Ray-tracing", nullptr));
        tabWidget_effects->setTabText(tabWidget_effects->indexOf(tab_volumetric), QCoreApplication::translate("cDockEffects", "Volumetric", nullptr));
        tabWidget_effects->setTabText(tabWidget_effects->indexOf(tab_background), QCoreApplication::translate("cDockEffects", "Background", nullptr));
        tabWidget_effects->setTabText(tabWidget_effects->indexOf(tab_lights), QCoreApplication::translate("cDockEffects", "Lights", nullptr));
        tabWidget_effects->setTabText(tabWidget_effects->indexOf(tab_single_trap_lights), QCoreApplication::translate("cDockEffects", "Ruimtelijk licht", nullptr));
        tabWidget_effects->setTabText(tabWidget_effects->indexOf(tab_postEffects), QCoreApplication::translate("cDockEffects", "Post effects", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cDockEffects: public Ui_cDockEffects {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCK_EFFECTS_H
