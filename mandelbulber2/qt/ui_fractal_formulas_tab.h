/********************************************************************************
** Form generated from reading UI file 'fractal_formulas_tab.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRACTAL_FORMULAS_TAB_H
#define UI_FRACTAL_FORMULAS_TAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
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
#include "my_tab_widget.h"
#include "tab_fractal.h"

QT_BEGIN_NAMESPACE

class Ui_cFractalFormulasTab
{
public:
    QVBoxLayout *verticalLayout_21;
    QHBoxLayout *horizontalLayout_2;
    cButtonLoadSettingsFromWidget *pushButton_local_load_2;
    cButtonSaveSettingsFromWidget *pushButton_local_save_2;
    cButtonResetSettingsFromWidget *pushButton_local_reset_2;
    cButtonRandomSettingsFromWidget *pushButton_local_randomize;
    QPushButton *pushButton_local_navi;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_fractals_remark_julia;
    MyTabWidget *tabWidget_fractals;
    QWidget *tab_fractal_formula_1;
    QVBoxLayout *verticalLayout_49;
    QScrollArea *scrollArea_fractal_1;
    QWidget *scrollAreaWidgetContents_fractal_1;
    QVBoxLayout *verticalLayoutScroll_fractal_1;
    cTabFractal *widgetTabFractal_1;
    QLabel *label_fractals_remark_hybrid;
    QWidget *tab_fractal_formula_2;
    QVBoxLayout *verticalLayout_50;
    QScrollArea *scrollArea_fractal_2;
    QWidget *scrollAreaWidgetContents_fractal_2;
    QVBoxLayout *verticalLayoutScroll_fractal_3;
    cTabFractal *widgetTabFractal_2;
    QWidget *tab_fractal_formula_3;
    QVBoxLayout *verticalLayout_51;
    QScrollArea *scrollArea_fractal_3;
    QWidget *scrollAreaWidgetContents_fractal_3;
    QVBoxLayout *verticalLayoutScroll_fractal_4;
    cTabFractal *widgetTabFractal_3;
    QWidget *tab_fractal_formula_4;
    QVBoxLayout *verticalLayout_52;
    QScrollArea *scrollArea_fractal_4;
    QWidget *scrollAreaWidgetContents_fractal_4;
    QVBoxLayout *verticalLayoutScroll_fractal_5;
    cTabFractal *widgetTabFractal_4;
    QWidget *tab_fractal_formula_5;
    QVBoxLayout *verticalLayout_97;
    QScrollArea *scrollArea_fractal_5;
    QWidget *scrollAreaWidgetContents_fractal_5;
    QVBoxLayout *verticalLayoutScroll_fractal_6;
    cTabFractal *widgetTabFractal_5;
    QWidget *tab_fractal_formula_6;
    QVBoxLayout *verticalLayout_101;
    QScrollArea *scrollArea_fractal_6;
    QWidget *scrollAreaWidgetContents_fractal_6;
    QVBoxLayout *verticalLayoutScroll_fractal_7;
    cTabFractal *widgetTabFractal_6;
    QWidget *tab_fractal_formula_7;
    QVBoxLayout *verticalLayout_105;
    QScrollArea *scrollArea_fractal_7;
    QWidget *scrollAreaWidgetContents_fractal_7;
    QVBoxLayout *verticalLayoutScroll_fractal_8;
    cTabFractal *widgetTabFractal_7;
    QWidget *tab_fractal_formula_8;
    QVBoxLayout *verticalLayout_109;
    QScrollArea *scrollArea_fractal_8;
    QWidget *scrollAreaWidgetContents_fractal_8;
    QVBoxLayout *verticalLayoutScroll_fractal_9;
    cTabFractal *widgetTabFractal_8;
    QWidget *tab_fractal_formula_9;
    QVBoxLayout *verticalLayout_113;
    QScrollArea *scrollArea_fractal_9;
    QWidget *scrollAreaWidgetContents_fractal_9;
    QVBoxLayout *verticalLayoutScroll_fractal_10;
    cTabFractal *widgetTabFractal_9;

    void setupUi(QWidget *cFractalFormulasTab)
    {
        if (cFractalFormulasTab->objectName().isEmpty())
            cFractalFormulasTab->setObjectName(QString::fromUtf8("cFractalFormulasTab"));
        verticalLayout_21 = new QVBoxLayout(cFractalFormulasTab);
        verticalLayout_21->setSpacing(2);
        verticalLayout_21->setObjectName(QString::fromUtf8("verticalLayout_21"));
        verticalLayout_21->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_local_load_2 = new cButtonLoadSettingsFromWidget(cFractalFormulasTab);
        pushButton_local_load_2->setObjectName(QString::fromUtf8("pushButton_local_load_2"));

        horizontalLayout_2->addWidget(pushButton_local_load_2);

        pushButton_local_save_2 = new cButtonSaveSettingsFromWidget(cFractalFormulasTab);
        pushButton_local_save_2->setObjectName(QString::fromUtf8("pushButton_local_save_2"));

        horizontalLayout_2->addWidget(pushButton_local_save_2);

        pushButton_local_reset_2 = new cButtonResetSettingsFromWidget(cFractalFormulasTab);
        pushButton_local_reset_2->setObjectName(QString::fromUtf8("pushButton_local_reset_2"));

        horizontalLayout_2->addWidget(pushButton_local_reset_2);

        pushButton_local_randomize = new cButtonRandomSettingsFromWidget(cFractalFormulasTab);
        pushButton_local_randomize->setObjectName(QString::fromUtf8("pushButton_local_randomize"));

        horizontalLayout_2->addWidget(pushButton_local_randomize);

        pushButton_local_navi = new QPushButton(cFractalFormulasTab);
        pushButton_local_navi->setObjectName(QString::fromUtf8("pushButton_local_navi"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_local_navi->sizePolicy().hasHeightForWidth());
        pushButton_local_navi->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(pushButton_local_navi);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_21->addLayout(horizontalLayout_2);

        label_fractals_remark_julia = new QLabel(cFractalFormulasTab);
        label_fractals_remark_julia->setObjectName(QString::fromUtf8("label_fractals_remark_julia"));
        label_fractals_remark_julia->setWordWrap(true);

        verticalLayout_21->addWidget(label_fractals_remark_julia);

        tabWidget_fractals = new MyTabWidget(cFractalFormulasTab);
        tabWidget_fractals->setObjectName(QString::fromUtf8("tabWidget_fractals"));
        tab_fractal_formula_1 = new QWidget();
        tab_fractal_formula_1->setObjectName(QString::fromUtf8("tab_fractal_formula_1"));
        verticalLayout_49 = new QVBoxLayout(tab_fractal_formula_1);
        verticalLayout_49->setSpacing(2);
        verticalLayout_49->setObjectName(QString::fromUtf8("verticalLayout_49"));
        verticalLayout_49->setContentsMargins(2, 2, 2, 2);
        scrollArea_fractal_1 = new QScrollArea(tab_fractal_formula_1);
        scrollArea_fractal_1->setObjectName(QString::fromUtf8("scrollArea_fractal_1"));
        scrollArea_fractal_1->setWidgetResizable(true);
        scrollAreaWidgetContents_fractal_1 = new QWidget();
        scrollAreaWidgetContents_fractal_1->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_fractal_1"));
        scrollAreaWidgetContents_fractal_1->setGeometry(QRect(0, 0, 453, 785));
        verticalLayoutScroll_fractal_1 = new QVBoxLayout(scrollAreaWidgetContents_fractal_1);
        verticalLayoutScroll_fractal_1->setSpacing(2);
        verticalLayoutScroll_fractal_1->setObjectName(QString::fromUtf8("verticalLayoutScroll_fractal_1"));
        verticalLayoutScroll_fractal_1->setContentsMargins(2, 2, 2, 2);
        widgetTabFractal_1 = new cTabFractal(scrollAreaWidgetContents_fractal_1);
        widgetTabFractal_1->setObjectName(QString::fromUtf8("widgetTabFractal_1"));

        verticalLayoutScroll_fractal_1->addWidget(widgetTabFractal_1);

        label_fractals_remark_hybrid = new QLabel(scrollAreaWidgetContents_fractal_1);
        label_fractals_remark_hybrid->setObjectName(QString::fromUtf8("label_fractals_remark_hybrid"));
        label_fractals_remark_hybrid->setWordWrap(true);

        verticalLayoutScroll_fractal_1->addWidget(label_fractals_remark_hybrid);

        verticalLayoutScroll_fractal_1->setStretch(0, 1);
        scrollArea_fractal_1->setWidget(scrollAreaWidgetContents_fractal_1);

        verticalLayout_49->addWidget(scrollArea_fractal_1);

        tabWidget_fractals->addTab(tab_fractal_formula_1, QString());
        tab_fractal_formula_2 = new QWidget();
        tab_fractal_formula_2->setObjectName(QString::fromUtf8("tab_fractal_formula_2"));
        verticalLayout_50 = new QVBoxLayout(tab_fractal_formula_2);
        verticalLayout_50->setSpacing(2);
        verticalLayout_50->setObjectName(QString::fromUtf8("verticalLayout_50"));
        verticalLayout_50->setContentsMargins(2, 2, 2, 2);
        scrollArea_fractal_2 = new QScrollArea(tab_fractal_formula_2);
        scrollArea_fractal_2->setObjectName(QString::fromUtf8("scrollArea_fractal_2"));
        scrollArea_fractal_2->setWidgetResizable(true);
        scrollAreaWidgetContents_fractal_2 = new QWidget();
        scrollAreaWidgetContents_fractal_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_fractal_2"));
        scrollAreaWidgetContents_fractal_2->setGeometry(QRect(0, 0, 96, 26));
        verticalLayoutScroll_fractal_3 = new QVBoxLayout(scrollAreaWidgetContents_fractal_2);
        verticalLayoutScroll_fractal_3->setSpacing(2);
        verticalLayoutScroll_fractal_3->setObjectName(QString::fromUtf8("verticalLayoutScroll_fractal_3"));
        verticalLayoutScroll_fractal_3->setContentsMargins(2, 2, 2, 2);
        widgetTabFractal_2 = new cTabFractal(scrollAreaWidgetContents_fractal_2);
        widgetTabFractal_2->setObjectName(QString::fromUtf8("widgetTabFractal_2"));

        verticalLayoutScroll_fractal_3->addWidget(widgetTabFractal_2);

        scrollArea_fractal_2->setWidget(scrollAreaWidgetContents_fractal_2);

        verticalLayout_50->addWidget(scrollArea_fractal_2);

        tabWidget_fractals->addTab(tab_fractal_formula_2, QString());
        tab_fractal_formula_3 = new QWidget();
        tab_fractal_formula_3->setObjectName(QString::fromUtf8("tab_fractal_formula_3"));
        verticalLayout_51 = new QVBoxLayout(tab_fractal_formula_3);
        verticalLayout_51->setSpacing(2);
        verticalLayout_51->setObjectName(QString::fromUtf8("verticalLayout_51"));
        verticalLayout_51->setContentsMargins(2, 2, 2, 2);
        scrollArea_fractal_3 = new QScrollArea(tab_fractal_formula_3);
        scrollArea_fractal_3->setObjectName(QString::fromUtf8("scrollArea_fractal_3"));
        scrollArea_fractal_3->setWidgetResizable(true);
        scrollAreaWidgetContents_fractal_3 = new QWidget();
        scrollAreaWidgetContents_fractal_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_fractal_3"));
        scrollAreaWidgetContents_fractal_3->setGeometry(QRect(0, 0, 96, 26));
        verticalLayoutScroll_fractal_4 = new QVBoxLayout(scrollAreaWidgetContents_fractal_3);
        verticalLayoutScroll_fractal_4->setSpacing(2);
        verticalLayoutScroll_fractal_4->setObjectName(QString::fromUtf8("verticalLayoutScroll_fractal_4"));
        verticalLayoutScroll_fractal_4->setContentsMargins(2, 2, 2, 2);
        widgetTabFractal_3 = new cTabFractal(scrollAreaWidgetContents_fractal_3);
        widgetTabFractal_3->setObjectName(QString::fromUtf8("widgetTabFractal_3"));

        verticalLayoutScroll_fractal_4->addWidget(widgetTabFractal_3);

        scrollArea_fractal_3->setWidget(scrollAreaWidgetContents_fractal_3);

        verticalLayout_51->addWidget(scrollArea_fractal_3);

        tabWidget_fractals->addTab(tab_fractal_formula_3, QString());
        tab_fractal_formula_4 = new QWidget();
        tab_fractal_formula_4->setObjectName(QString::fromUtf8("tab_fractal_formula_4"));
        verticalLayout_52 = new QVBoxLayout(tab_fractal_formula_4);
        verticalLayout_52->setSpacing(2);
        verticalLayout_52->setObjectName(QString::fromUtf8("verticalLayout_52"));
        verticalLayout_52->setContentsMargins(2, 2, 2, 2);
        scrollArea_fractal_4 = new QScrollArea(tab_fractal_formula_4);
        scrollArea_fractal_4->setObjectName(QString::fromUtf8("scrollArea_fractal_4"));
        scrollArea_fractal_4->setWidgetResizable(true);
        scrollAreaWidgetContents_fractal_4 = new QWidget();
        scrollAreaWidgetContents_fractal_4->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_fractal_4"));
        scrollAreaWidgetContents_fractal_4->setGeometry(QRect(0, 0, 96, 26));
        verticalLayoutScroll_fractal_5 = new QVBoxLayout(scrollAreaWidgetContents_fractal_4);
        verticalLayoutScroll_fractal_5->setSpacing(2);
        verticalLayoutScroll_fractal_5->setObjectName(QString::fromUtf8("verticalLayoutScroll_fractal_5"));
        verticalLayoutScroll_fractal_5->setContentsMargins(2, 2, 2, 2);
        widgetTabFractal_4 = new cTabFractal(scrollAreaWidgetContents_fractal_4);
        widgetTabFractal_4->setObjectName(QString::fromUtf8("widgetTabFractal_4"));

        verticalLayoutScroll_fractal_5->addWidget(widgetTabFractal_4);

        scrollArea_fractal_4->setWidget(scrollAreaWidgetContents_fractal_4);

        verticalLayout_52->addWidget(scrollArea_fractal_4);

        tabWidget_fractals->addTab(tab_fractal_formula_4, QString());
        tab_fractal_formula_5 = new QWidget();
        tab_fractal_formula_5->setObjectName(QString::fromUtf8("tab_fractal_formula_5"));
        verticalLayout_97 = new QVBoxLayout(tab_fractal_formula_5);
        verticalLayout_97->setSpacing(2);
        verticalLayout_97->setObjectName(QString::fromUtf8("verticalLayout_97"));
        verticalLayout_97->setContentsMargins(2, 2, 2, 2);
        scrollArea_fractal_5 = new QScrollArea(tab_fractal_formula_5);
        scrollArea_fractal_5->setObjectName(QString::fromUtf8("scrollArea_fractal_5"));
        scrollArea_fractal_5->setWidgetResizable(true);
        scrollAreaWidgetContents_fractal_5 = new QWidget();
        scrollAreaWidgetContents_fractal_5->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_fractal_5"));
        scrollAreaWidgetContents_fractal_5->setGeometry(QRect(0, 0, 96, 26));
        verticalLayoutScroll_fractal_6 = new QVBoxLayout(scrollAreaWidgetContents_fractal_5);
        verticalLayoutScroll_fractal_6->setSpacing(2);
        verticalLayoutScroll_fractal_6->setObjectName(QString::fromUtf8("verticalLayoutScroll_fractal_6"));
        verticalLayoutScroll_fractal_6->setContentsMargins(2, 2, 2, 2);
        widgetTabFractal_5 = new cTabFractal(scrollAreaWidgetContents_fractal_5);
        widgetTabFractal_5->setObjectName(QString::fromUtf8("widgetTabFractal_5"));

        verticalLayoutScroll_fractal_6->addWidget(widgetTabFractal_5);

        scrollArea_fractal_5->setWidget(scrollAreaWidgetContents_fractal_5);

        verticalLayout_97->addWidget(scrollArea_fractal_5);

        tabWidget_fractals->addTab(tab_fractal_formula_5, QString());
        tab_fractal_formula_6 = new QWidget();
        tab_fractal_formula_6->setObjectName(QString::fromUtf8("tab_fractal_formula_6"));
        verticalLayout_101 = new QVBoxLayout(tab_fractal_formula_6);
        verticalLayout_101->setSpacing(2);
        verticalLayout_101->setObjectName(QString::fromUtf8("verticalLayout_101"));
        verticalLayout_101->setContentsMargins(2, 2, 2, 2);
        scrollArea_fractal_6 = new QScrollArea(tab_fractal_formula_6);
        scrollArea_fractal_6->setObjectName(QString::fromUtf8("scrollArea_fractal_6"));
        scrollArea_fractal_6->setWidgetResizable(true);
        scrollAreaWidgetContents_fractal_6 = new QWidget();
        scrollAreaWidgetContents_fractal_6->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_fractal_6"));
        scrollAreaWidgetContents_fractal_6->setGeometry(QRect(0, 0, 96, 26));
        verticalLayoutScroll_fractal_7 = new QVBoxLayout(scrollAreaWidgetContents_fractal_6);
        verticalLayoutScroll_fractal_7->setSpacing(2);
        verticalLayoutScroll_fractal_7->setObjectName(QString::fromUtf8("verticalLayoutScroll_fractal_7"));
        verticalLayoutScroll_fractal_7->setContentsMargins(2, 2, 2, 2);
        widgetTabFractal_6 = new cTabFractal(scrollAreaWidgetContents_fractal_6);
        widgetTabFractal_6->setObjectName(QString::fromUtf8("widgetTabFractal_6"));

        verticalLayoutScroll_fractal_7->addWidget(widgetTabFractal_6);

        scrollArea_fractal_6->setWidget(scrollAreaWidgetContents_fractal_6);

        verticalLayout_101->addWidget(scrollArea_fractal_6);

        tabWidget_fractals->addTab(tab_fractal_formula_6, QString());
        tab_fractal_formula_7 = new QWidget();
        tab_fractal_formula_7->setObjectName(QString::fromUtf8("tab_fractal_formula_7"));
        verticalLayout_105 = new QVBoxLayout(tab_fractal_formula_7);
        verticalLayout_105->setSpacing(2);
        verticalLayout_105->setObjectName(QString::fromUtf8("verticalLayout_105"));
        verticalLayout_105->setContentsMargins(2, 2, 2, 2);
        scrollArea_fractal_7 = new QScrollArea(tab_fractal_formula_7);
        scrollArea_fractal_7->setObjectName(QString::fromUtf8("scrollArea_fractal_7"));
        scrollArea_fractal_7->setWidgetResizable(true);
        scrollAreaWidgetContents_fractal_7 = new QWidget();
        scrollAreaWidgetContents_fractal_7->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_fractal_7"));
        scrollAreaWidgetContents_fractal_7->setGeometry(QRect(0, 0, 96, 26));
        verticalLayoutScroll_fractal_8 = new QVBoxLayout(scrollAreaWidgetContents_fractal_7);
        verticalLayoutScroll_fractal_8->setSpacing(2);
        verticalLayoutScroll_fractal_8->setObjectName(QString::fromUtf8("verticalLayoutScroll_fractal_8"));
        verticalLayoutScroll_fractal_8->setContentsMargins(2, 2, 2, 2);
        widgetTabFractal_7 = new cTabFractal(scrollAreaWidgetContents_fractal_7);
        widgetTabFractal_7->setObjectName(QString::fromUtf8("widgetTabFractal_7"));

        verticalLayoutScroll_fractal_8->addWidget(widgetTabFractal_7);

        scrollArea_fractal_7->setWidget(scrollAreaWidgetContents_fractal_7);

        verticalLayout_105->addWidget(scrollArea_fractal_7);

        tabWidget_fractals->addTab(tab_fractal_formula_7, QString());
        tab_fractal_formula_8 = new QWidget();
        tab_fractal_formula_8->setObjectName(QString::fromUtf8("tab_fractal_formula_8"));
        verticalLayout_109 = new QVBoxLayout(tab_fractal_formula_8);
        verticalLayout_109->setSpacing(2);
        verticalLayout_109->setObjectName(QString::fromUtf8("verticalLayout_109"));
        verticalLayout_109->setContentsMargins(2, 2, 2, 2);
        scrollArea_fractal_8 = new QScrollArea(tab_fractal_formula_8);
        scrollArea_fractal_8->setObjectName(QString::fromUtf8("scrollArea_fractal_8"));
        scrollArea_fractal_8->setWidgetResizable(true);
        scrollAreaWidgetContents_fractal_8 = new QWidget();
        scrollAreaWidgetContents_fractal_8->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_fractal_8"));
        scrollAreaWidgetContents_fractal_8->setGeometry(QRect(0, 0, 96, 26));
        verticalLayoutScroll_fractal_9 = new QVBoxLayout(scrollAreaWidgetContents_fractal_8);
        verticalLayoutScroll_fractal_9->setSpacing(2);
        verticalLayoutScroll_fractal_9->setObjectName(QString::fromUtf8("verticalLayoutScroll_fractal_9"));
        verticalLayoutScroll_fractal_9->setContentsMargins(2, 2, 2, 2);
        widgetTabFractal_8 = new cTabFractal(scrollAreaWidgetContents_fractal_8);
        widgetTabFractal_8->setObjectName(QString::fromUtf8("widgetTabFractal_8"));

        verticalLayoutScroll_fractal_9->addWidget(widgetTabFractal_8);

        scrollArea_fractal_8->setWidget(scrollAreaWidgetContents_fractal_8);

        verticalLayout_109->addWidget(scrollArea_fractal_8);

        tabWidget_fractals->addTab(tab_fractal_formula_8, QString());
        tab_fractal_formula_9 = new QWidget();
        tab_fractal_formula_9->setObjectName(QString::fromUtf8("tab_fractal_formula_9"));
        verticalLayout_113 = new QVBoxLayout(tab_fractal_formula_9);
        verticalLayout_113->setSpacing(2);
        verticalLayout_113->setObjectName(QString::fromUtf8("verticalLayout_113"));
        verticalLayout_113->setContentsMargins(2, 2, 2, 2);
        scrollArea_fractal_9 = new QScrollArea(tab_fractal_formula_9);
        scrollArea_fractal_9->setObjectName(QString::fromUtf8("scrollArea_fractal_9"));
        scrollArea_fractal_9->setWidgetResizable(true);
        scrollAreaWidgetContents_fractal_9 = new QWidget();
        scrollAreaWidgetContents_fractal_9->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_fractal_9"));
        scrollAreaWidgetContents_fractal_9->setGeometry(QRect(0, 0, 96, 26));
        verticalLayoutScroll_fractal_10 = new QVBoxLayout(scrollAreaWidgetContents_fractal_9);
        verticalLayoutScroll_fractal_10->setSpacing(2);
        verticalLayoutScroll_fractal_10->setObjectName(QString::fromUtf8("verticalLayoutScroll_fractal_10"));
        verticalLayoutScroll_fractal_10->setContentsMargins(2, 2, 2, 2);
        widgetTabFractal_9 = new cTabFractal(scrollAreaWidgetContents_fractal_9);
        widgetTabFractal_9->setObjectName(QString::fromUtf8("widgetTabFractal_9"));

        verticalLayoutScroll_fractal_10->addWidget(widgetTabFractal_9);

        scrollArea_fractal_9->setWidget(scrollAreaWidgetContents_fractal_9);

        verticalLayout_113->addWidget(scrollArea_fractal_9);

        tabWidget_fractals->addTab(tab_fractal_formula_9, QString());

        verticalLayout_21->addWidget(tabWidget_fractals);


        retranslateUi(cFractalFormulasTab);

        tabWidget_fractals->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(cFractalFormulasTab);
    } // setupUi

    void retranslateUi(QWidget *cFractalFormulasTab)
    {
        pushButton_local_load_2->setText(QCoreApplication::translate("cFractalFormulasTab", "Load", nullptr));
        pushButton_local_save_2->setText(QCoreApplication::translate("cFractalFormulasTab", "Save", nullptr));
        pushButton_local_reset_2->setText(QCoreApplication::translate("cFractalFormulasTab", "Reset", nullptr));
        pushButton_local_randomize->setText(QCoreApplication::translate("cFractalFormulasTab", "Randomize", nullptr));
        pushButton_local_navi->setText(QCoreApplication::translate("cFractalFormulasTab", "Navi", nullptr));
        label_fractals_remark_julia->setText(QCoreApplication::translate("cFractalFormulasTab", "Remark: Julia mode is enabled", nullptr));
#if QT_CONFIG(tooltip)
        tabWidget_fractals->setToolTip(QCoreApplication::translate("cFractalFormulasTab", "<html><head/><body><p>Selection for fractal formula. Fractal formula defines shape of fractal.</p><p>Algorithm (code) for selected formula is visible in Information box.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_fractals_remark_hybrid->setText(QCoreApplication::translate("cFractalFormulasTab", "Remark: to unlock more fractal tabs, enable \"hybrid fractals\" or \"boolean operators\"", nullptr));
        tabWidget_fractals->setTabText(tabWidget_fractals->indexOf(tab_fractal_formula_1), QCoreApplication::translate("cFractalFormulasTab", "Page", nullptr));
        tabWidget_fractals->setTabText(tabWidget_fractals->indexOf(tab_fractal_formula_2), QCoreApplication::translate("cFractalFormulasTab", "Page", nullptr));
        tabWidget_fractals->setTabText(tabWidget_fractals->indexOf(tab_fractal_formula_3), QCoreApplication::translate("cFractalFormulasTab", "Page", nullptr));
        tabWidget_fractals->setTabText(tabWidget_fractals->indexOf(tab_fractal_formula_4), QCoreApplication::translate("cFractalFormulasTab", "Page", nullptr));
        tabWidget_fractals->setTabText(tabWidget_fractals->indexOf(tab_fractal_formula_5), QCoreApplication::translate("cFractalFormulasTab", "Page", nullptr));
        tabWidget_fractals->setTabText(tabWidget_fractals->indexOf(tab_fractal_formula_6), QCoreApplication::translate("cFractalFormulasTab", "Page", nullptr));
        tabWidget_fractals->setTabText(tabWidget_fractals->indexOf(tab_fractal_formula_7), QCoreApplication::translate("cFractalFormulasTab", "Page", nullptr));
        tabWidget_fractals->setTabText(tabWidget_fractals->indexOf(tab_fractal_formula_8), QCoreApplication::translate("cFractalFormulasTab", "Page", nullptr));
        tabWidget_fractals->setTabText(tabWidget_fractals->indexOf(tab_fractal_formula_9), QCoreApplication::translate("cFractalFormulasTab", "Page", nullptr));
        (void)cFractalFormulasTab;
    } // retranslateUi

};

namespace Ui {
    class cFractalFormulasTab: public Ui_cFractalFormulasTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRACTAL_FORMULAS_TAB_H
