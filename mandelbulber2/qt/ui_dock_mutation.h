/********************************************************************************
** Form generated from reading UI file 'dock_mutation.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCK_MUTATION_H
#define UI_DOCK_MUTATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cDockMutation
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget_mutations;

    void setupUi(QWidget *cDockMutation)
    {
        if (cDockMutation->objectName().isEmpty())
            cDockMutation->setObjectName(QString::fromUtf8("cDockMutation"));
        cDockMutation->resize(440, 800);
        verticalLayout = new QVBoxLayout(cDockMutation);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        tabWidget_mutations = new QTabWidget(cDockMutation);
        tabWidget_mutations->setObjectName(QString::fromUtf8("tabWidget_mutations"));
        tabWidget_mutations->setTabPosition(QTabWidget::North);

        verticalLayout->addWidget(tabWidget_mutations);


        retranslateUi(cDockMutation);

        tabWidget_mutations->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(cDockMutation);
    } // setupUi

    void retranslateUi(QWidget *cDockMutation)
    {
        cDockMutation->setWindowTitle(QCoreApplication::translate("cDockMutation", "Mutation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cDockMutation: public Ui_cDockMutation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCK_MUTATION_H
