/********************************************************************************
** Form generated from reading UI file 'light_sources_manager.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIGHT_SOURCES_MANAGER_H
#define UI_LIGHT_SOURCES_MANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "my_check_box.h"
#include "my_tab_widget_with_checkboxes.h"

QT_BEGIN_NAMESPACE

class Ui_cLightSourcesManager
{
public:
    QVBoxLayout *verticalLayout;
    MyCheckBox *checkBox_show_wireframe_lights;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_newLight;
    QPushButton *pushButton_duplicateLight;
    QPushButton *pushButton_deleteLight;
    QPushButton *pushButton_placeLight;
    QPushButton *pushButton_snapToSurface;
    MyTabWidgetWithCheckboxes *tabWidget_lightSources;

    void setupUi(QWidget *cLightSourcesManager)
    {
        if (cLightSourcesManager->objectName().isEmpty())
            cLightSourcesManager->setObjectName(QString::fromUtf8("cLightSourcesManager"));
        cLightSourcesManager->resize(352, 440);
        verticalLayout = new QVBoxLayout(cLightSourcesManager);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        checkBox_show_wireframe_lights = new MyCheckBox(cLightSourcesManager);
        checkBox_show_wireframe_lights->setObjectName(QString::fromUtf8("checkBox_show_wireframe_lights"));

        verticalLayout->addWidget(checkBox_show_wireframe_lights);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_newLight = new QPushButton(cLightSourcesManager);
        pushButton_newLight->setObjectName(QString::fromUtf8("pushButton_newLight"));

        horizontalLayout->addWidget(pushButton_newLight);

        pushButton_duplicateLight = new QPushButton(cLightSourcesManager);
        pushButton_duplicateLight->setObjectName(QString::fromUtf8("pushButton_duplicateLight"));

        horizontalLayout->addWidget(pushButton_duplicateLight);

        pushButton_deleteLight = new QPushButton(cLightSourcesManager);
        pushButton_deleteLight->setObjectName(QString::fromUtf8("pushButton_deleteLight"));

        horizontalLayout->addWidget(pushButton_deleteLight);

        pushButton_placeLight = new QPushButton(cLightSourcesManager);
        pushButton_placeLight->setObjectName(QString::fromUtf8("pushButton_placeLight"));

        horizontalLayout->addWidget(pushButton_placeLight);

        pushButton_snapToSurface = new QPushButton(cLightSourcesManager);
        pushButton_snapToSurface->setObjectName(QString::fromUtf8("pushButton_snapToSurface"));

        horizontalLayout->addWidget(pushButton_snapToSurface);


        verticalLayout->addLayout(horizontalLayout);

        tabWidget_lightSources = new MyTabWidgetWithCheckboxes(cLightSourcesManager);
        tabWidget_lightSources->setObjectName(QString::fromUtf8("tabWidget_lightSources"));

        verticalLayout->addWidget(tabWidget_lightSources);


        retranslateUi(cLightSourcesManager);

        tabWidget_lightSources->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(cLightSourcesManager);
    } // setupUi

    void retranslateUi(QWidget *cLightSourcesManager)
    {
        cLightSourcesManager->setWindowTitle(QCoreApplication::translate("cLightSourcesManager", "Form", nullptr));
        checkBox_show_wireframe_lights->setText(QCoreApplication::translate("cLightSourcesManager", "Show wire-frame preview of lights", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_newLight->setToolTip(QCoreApplication::translate("cLightSourcesManager", "<html><head/><body><p>Add a new light source to the scene. This new light will appear as a new tab below. There is no limit to the number of light sources.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_newLight->setText(QCoreApplication::translate("cLightSourcesManager", "New\n"
"light", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_duplicateLight->setToolTip(QCoreApplication::translate("cLightSourcesManager", "<html><head/><body><p>Duplicate the selected light source. All parameters will be copied to the new one.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_duplicateLight->setText(QCoreApplication::translate("cLightSourcesManager", "Duplicate\n"
"light", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_deleteLight->setToolTip(QCoreApplication::translate("cLightSourcesManager", "<html><head/><body><p>Delete the selected light source.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_deleteLight->setText(QCoreApplication::translate("cLightSourcesManager", "Delete\n"
"light", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_placeLight->setToolTip(QCoreApplication::translate("cLightSourcesManager", "<html><head/><body><p>Place a light source using the mouse pointer.</p><p>Light position (for selected light tab) can be manipulated in following ways:</p><p>- mouse click on the image places light in front of selected point (offset by placement distance.) Placement distance from the selected point can be adjusted using mouse wheel + alt key.</p><p>- move light by dragging the mouse pointer while holding left mouse button. Moves light while maintaining placement distance</p><p>- rotating mouse wheel while holding control key moves light forward/backward</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_placeLight->setText(QCoreApplication::translate("cLightSourcesManager", "Place/move\n"
"light", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_snapToSurface->setToolTip(QCoreApplication::translate("cLightSourcesManager", "<html><head/><body><p>Snap selected light to the fractal surface in the camera view direction.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_snapToSurface->setText(QCoreApplication::translate("cLightSourcesManager", "Snap to\n"
"surface", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cLightSourcesManager: public Ui_cLightSourcesManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIGHT_SOURCES_MANAGER_H
