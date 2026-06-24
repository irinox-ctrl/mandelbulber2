/********************************************************************************
** Form generated from reading UI file 'mutation_systems_panel.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MUTATION_SYSTEMS_PANEL_H
#define UI_MUTATION_SYSTEMS_PANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <mutation_systems_group1.h>
#include <mutation_systems_group2.h>
#include <mutation_systems_group3.h>

QT_BEGIN_NAMESPACE

class Ui_cMutationSystemsPanel
{
public:
    QVBoxLayout *verticalLayout_mutation_systems;
    cMutationSystemsGroup1 *widget_mutation_systems_group1;
    cMutationSystemsGroup2 *widget_mutation_systems_group2;
    cMutationSystemsGroup3 *widget_mutation_systems_group3;

    void setupUi(QWidget *cMutationSystemsPanel)
    {
        if (cMutationSystemsPanel->objectName().isEmpty())
            cMutationSystemsPanel->setObjectName(QString::fromUtf8("cMutationSystemsPanel"));
        verticalLayout_mutation_systems = new QVBoxLayout(cMutationSystemsPanel);
        verticalLayout_mutation_systems->setSpacing(2);
        verticalLayout_mutation_systems->setObjectName(QString::fromUtf8("verticalLayout_mutation_systems"));
        verticalLayout_mutation_systems->setContentsMargins(0, 0, 0, 0);
        widget_mutation_systems_group1 = new cMutationSystemsGroup1(cMutationSystemsPanel);
        widget_mutation_systems_group1->setObjectName(QString::fromUtf8("widget_mutation_systems_group1"));

        verticalLayout_mutation_systems->addWidget(widget_mutation_systems_group1);

        widget_mutation_systems_group2 = new cMutationSystemsGroup2(cMutationSystemsPanel);
        widget_mutation_systems_group2->setObjectName(QString::fromUtf8("widget_mutation_systems_group2"));

        verticalLayout_mutation_systems->addWidget(widget_mutation_systems_group2);

        widget_mutation_systems_group3 = new cMutationSystemsGroup3(cMutationSystemsPanel);
        widget_mutation_systems_group3->setObjectName(QString::fromUtf8("widget_mutation_systems_group3"));

        verticalLayout_mutation_systems->addWidget(widget_mutation_systems_group3);


        retranslateUi(cMutationSystemsPanel);

        QMetaObject::connectSlotsByName(cMutationSystemsPanel);
    } // setupUi

    void retranslateUi(QWidget *cMutationSystemsPanel)
    {
        (void)cMutationSystemsPanel;
    } // retranslateUi

};

namespace Ui {
    class cMutationSystemsPanel: public Ui_cMutationSystemsPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MUTATION_SYSTEMS_PANEL_H
