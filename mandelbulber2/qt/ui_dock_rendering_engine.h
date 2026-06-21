/********************************************************************************
** Form generated from reading UI file 'dock_rendering_engine.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCK_RENDERING_ENGINE_H
#define UI_DOCK_RENDERING_ENGINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <rendering_fractal_shape_tab.h>
#include <rendering_limits_tab.h>
#include <rendering_nebula_tab.h>
#include <rendering_netrender_tab.h>
#include "buton_load_settings_from_widget.h"
#include "buton_reset_settings_from_widget.h"
#include "buton_save_settings_from_widget.h"
#include "gradient_edit_widget.h"
#include "my_check_box.h"
#include "my_combo_box.h"
#include "my_double_spin_box.h"
#include "my_group_box.h"
#include "my_line_edit.h"
#include "my_spin_box.h"

QT_BEGIN_NAMESPACE

class Ui_cDockRenderingEngine
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    cButtonLoadSettingsFromWidget *pushButton_local_load_2;
    cButtonSaveSettingsFromWidget *pushButton_local_save_2;
    cButtonResetSettingsFromWidget *pushButton_local_reset_2;
    QSpacerItem *horizontalSpacer_2;
    QTabWidget *tabWidget;
    cRenderingFractalShapeTab *tabFractalShape;
    cRenderingNebulaTab *tabNebula;
    cRenderingLimitsTab *tabLimits;
    cRenderingNetrenderTab *tabNetRender;

    void setupUi(QWidget *cDockRenderingEngine)
    {
        if (cDockRenderingEngine->objectName().isEmpty())
            cDockRenderingEngine->setObjectName(QString::fromUtf8("cDockRenderingEngine"));
        cDockRenderingEngine->resize(455, 1126);
        verticalLayout = new QVBoxLayout(cDockRenderingEngine);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_local_load_2 = new cButtonLoadSettingsFromWidget(cDockRenderingEngine);
        pushButton_local_load_2->setObjectName(QString::fromUtf8("pushButton_local_load_2"));

        horizontalLayout_2->addWidget(pushButton_local_load_2);

        pushButton_local_save_2 = new cButtonSaveSettingsFromWidget(cDockRenderingEngine);
        pushButton_local_save_2->setObjectName(QString::fromUtf8("pushButton_local_save_2"));

        horizontalLayout_2->addWidget(pushButton_local_save_2);

        pushButton_local_reset_2 = new cButtonResetSettingsFromWidget(cDockRenderingEngine);
        pushButton_local_reset_2->setObjectName(QString::fromUtf8("pushButton_local_reset_2"));

        horizontalLayout_2->addWidget(pushButton_local_reset_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        tabWidget = new QTabWidget(cDockRenderingEngine);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabPosition(QTabWidget::West);
        tabFractalShape = new cRenderingFractalShapeTab();
        tabFractalShape->setObjectName(QString::fromUtf8("tabFractalShape"));
        tabWidget->addTab(tabFractalShape, QString());
        tabNebula = new cRenderingNebulaTab();
        tabNebula->setObjectName(QString::fromUtf8("tabNebula"));
        tabWidget->addTab(tabNebula, QString());
        tabLimits = new cRenderingLimitsTab();
        tabLimits->setObjectName(QString::fromUtf8("tabLimits"));
        tabWidget->addTab(tabLimits, QString());
        tabNetRender = new cRenderingNetrenderTab();
        tabNetRender->setObjectName(QString::fromUtf8("tabNetRender"));
        tabWidget->addTab(tabNetRender, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(cDockRenderingEngine);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(cDockRenderingEngine);
    } // setupUi

    void retranslateUi(QWidget *cDockRenderingEngine)
    {
        cDockRenderingEngine->setWindowTitle(QCoreApplication::translate("cDockRenderingEngine", "Form", nullptr));
        pushButton_local_load_2->setText(QCoreApplication::translate("cDockRenderingEngine", "Load", nullptr));
        pushButton_local_save_2->setText(QCoreApplication::translate("cDockRenderingEngine", "Save", nullptr));
        pushButton_local_reset_2->setText(QCoreApplication::translate("cDockRenderingEngine", "Reset", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabFractalShape), QCoreApplication::translate("cDockRenderingEngine", "Fractal shape calculation", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabNebula), QCoreApplication::translate("cDockRenderingEngine", "Nebula", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabLimits), QCoreApplication::translate("cDockRenderingEngine", "Limits", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabNetRender), QCoreApplication::translate("cDockRenderingEngine", "Net render", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cDockRenderingEngine: public Ui_cDockRenderingEngine {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCK_RENDERING_ENGINE_H
