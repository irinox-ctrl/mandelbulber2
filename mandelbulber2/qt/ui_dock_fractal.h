/********************************************************************************
** Form generated from reading UI file 'dock_fractal.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCK_FRACTAL_H
#define UI_DOCK_FRACTAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <fractal_common_tab.h>
#include <fractal_description_tab.h>
#include <fractal_formulas_tab.h>
#include <fractal_hybrid_tab.h>
#include <fractal_primitives_tab.h>
#include "buton_load_settings_from_widget.h"
#include "buton_random_settings_from_widget.h"
#include "buton_reset_settings_from_widget.h"
#include "buton_save_settings_from_widget.h"
#include "drone_explorer_widget.h"
#include "julia_heatmap_widget.h"
#include "material_selector.h"
#include "my_check_box.h"
#include "my_combo_box.h"
#include "my_double_spin_box.h"
#include "my_group_box.h"
#include "my_line_edit.h"
#include "my_spin_box.h"
#include "my_tab_widget.h"
#include "objects_tree_widget.h"
#include "primitives_manager.h"
#include "tab_fractal.h"
#include "thumbnail_widget.h"

QT_BEGIN_NAMESPACE

class Ui_cDockFractal
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget_fractal;
    cFractalFormulasTab *tabWidget_fractal_formulas;
    cFractalCommonTab *tabWidget_fractal_common;
    cFractalHybridTab *tabWidget_fractal_hybrid;
    cFractalPrimitivesTab *tab_primitives;
    cFractalDescriptionTab *tab_description;

    void setupUi(QWidget *cDockFractal)
    {
        if (cDockFractal->objectName().isEmpty())
            cDockFractal->setObjectName(QString::fromUtf8("cDockFractal"));
        cDockFractal->resize(506, 896);
        verticalLayout = new QVBoxLayout(cDockFractal);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        tabWidget_fractal = new QTabWidget(cDockFractal);
        tabWidget_fractal->setObjectName(QString::fromUtf8("tabWidget_fractal"));
        tabWidget_fractal->setTabPosition(QTabWidget::West);
        tabWidget_fractal->setDocumentMode(false);
        tabWidget_fractal->setMovable(true);
        tabWidget_fractal_formulas = new cFractalFormulasTab();
        tabWidget_fractal_formulas->setObjectName(QString::fromUtf8("tabWidget_fractal_formulas"));
        tabWidget_fractal->addTab(tabWidget_fractal_formulas, QString());
        tabWidget_fractal_common = new cFractalCommonTab();
        tabWidget_fractal_common->setObjectName(QString::fromUtf8("tabWidget_fractal_common"));
        tabWidget_fractal->addTab(tabWidget_fractal_common, QString());
        tabWidget_fractal_hybrid = new cFractalHybridTab();
        tabWidget_fractal_hybrid->setObjectName(QString::fromUtf8("tabWidget_fractal_hybrid"));
        tabWidget_fractal->addTab(tabWidget_fractal_hybrid, QString());
        tab_primitives = new cFractalPrimitivesTab();
        tab_primitives->setObjectName(QString::fromUtf8("tab_primitives"));
        tabWidget_fractal->addTab(tab_primitives, QString());
        tab_description = new cFractalDescriptionTab();
        tab_description->setObjectName(QString::fromUtf8("tab_description"));
        tabWidget_fractal->addTab(tab_description, QString());

        verticalLayout->addWidget(tabWidget_fractal);


        retranslateUi(cDockFractal);

        tabWidget_fractal->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(cDockFractal);
    } // setupUi

    void retranslateUi(QWidget *cDockFractal)
    {
        cDockFractal->setWindowTitle(QCoreApplication::translate("cDockFractal", "Form", nullptr));
        tabWidget_fractal->setTabText(tabWidget_fractal->indexOf(tabWidget_fractal_formulas), QCoreApplication::translate("cDockFractal", "Fractals", nullptr));
        tabWidget_fractal->setTabText(tabWidget_fractal->indexOf(tabWidget_fractal_common), QCoreApplication::translate("cDockFractal", "Global parameters", nullptr));
        tabWidget_fractal->setTabText(tabWidget_fractal->indexOf(tabWidget_fractal_hybrid), QCoreApplication::translate("cDockFractal", "Hybrid", nullptr));
        tabWidget_fractal->setTabText(tabWidget_fractal->indexOf(tab_primitives), QCoreApplication::translate("cDockFractal", "Primitives", nullptr));
        tabWidget_fractal->setTabText(tabWidget_fractal->indexOf(tab_description), QCoreApplication::translate("cDockFractal", "Description", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cDockFractal: public Ui_cDockFractal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCK_FRACTAL_H
