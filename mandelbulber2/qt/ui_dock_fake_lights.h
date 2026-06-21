/********************************************************************************
** Form generated from reading UI file 'dock_fake_lights.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCK_FAKE_LIGHTS_H
#define UI_DOCK_FAKE_LIGHTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <fake_lights_panel.h>
#include "my_check_box.h"
#include "my_color_button.h"
#include "my_combo_box.h"
#include "my_double_spin_box.h"
#include "my_group_box.h"
#include "my_line_edit.h"
#include "my_spin_box.h"

QT_BEGIN_NAMESPACE

class Ui_cDockFakeLights
{
public:
    QVBoxLayout *verticalLayout_fake_lights_root;
    cFakeLightsPanel *widget_fake_lights_panel;

    void setupUi(QWidget *cDockFakeLights)
    {
        if (cDockFakeLights->objectName().isEmpty())
            cDockFakeLights->setObjectName(QString::fromUtf8("cDockFakeLights"));
        cDockFakeLights->resize(480, 900);
        verticalLayout_fake_lights_root = new QVBoxLayout(cDockFakeLights);
        verticalLayout_fake_lights_root->setSpacing(2);
        verticalLayout_fake_lights_root->setObjectName(QString::fromUtf8("verticalLayout_fake_lights_root"));
        verticalLayout_fake_lights_root->setContentsMargins(2, 2, 2, 2);
        widget_fake_lights_panel = new cFakeLightsPanel(cDockFakeLights);
        widget_fake_lights_panel->setObjectName(QString::fromUtf8("widget_fake_lights_panel"));

        verticalLayout_fake_lights_root->addWidget(widget_fake_lights_panel);


        retranslateUi(cDockFakeLights);

        QMetaObject::connectSlotsByName(cDockFakeLights);
    } // setupUi

    void retranslateUi(QWidget *cDockFakeLights)
    {
        cDockFakeLights->setWindowTitle(QCoreApplication::translate("cDockFakeLights", "Fake Lights", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cDockFakeLights: public Ui_cDockFakeLights {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCK_FAKE_LIGHTS_H
