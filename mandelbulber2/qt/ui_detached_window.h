/********************************************************************************
** Form generated from reading UI file 'detached_window.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DETACHED_WINDOW_H
#define UI_DETACHED_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cDetachedWindow
{
public:
    QAction *actionReturn_to_main_window;
    QAction *actionFull_screen;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QMenuBar *menubar;
    QMenu *menuView;

    void setupUi(QMainWindow *cDetachedWindow)
    {
        if (cDetachedWindow->objectName().isEmpty())
            cDetachedWindow->setObjectName(QString::fromUtf8("cDetachedWindow"));
        cDetachedWindow->resize(800, 600);
        actionReturn_to_main_window = new QAction(cDetachedWindow);
        actionReturn_to_main_window->setObjectName(QString::fromUtf8("actionReturn_to_main_window"));
        actionFull_screen = new QAction(cDetachedWindow);
        actionFull_screen->setObjectName(QString::fromUtf8("actionFull_screen"));
        centralwidget = new QWidget(cDetachedWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        cDetachedWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(cDetachedWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        cDetachedWindow->setMenuBar(menubar);

        menubar->addAction(menuView->menuAction());
        menuView->addAction(actionReturn_to_main_window);
        menuView->addAction(actionFull_screen);

        retranslateUi(cDetachedWindow);

        QMetaObject::connectSlotsByName(cDetachedWindow);
    } // setupUi

    void retranslateUi(QMainWindow *cDetachedWindow)
    {
        cDetachedWindow->setWindowTitle(QCoreApplication::translate("cDetachedWindow", "Rendered image", nullptr));
        actionReturn_to_main_window->setText(QCoreApplication::translate("cDetachedWindow", "Attach to main window", nullptr));
        actionFull_screen->setText(QCoreApplication::translate("cDetachedWindow", "Toggle full screen", nullptr));
        menuView->setTitle(QCoreApplication::translate("cDetachedWindow", "&View", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cDetachedWindow: public Ui_cDetachedWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DETACHED_WINDOW_H
