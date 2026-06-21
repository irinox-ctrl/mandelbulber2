/********************************************************************************
** Form generated from reading UI file 'settings_cleaner.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_CLEANER_H
#define UI_SETTINGS_CLEANER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include "thumbnail_widget.h"

QT_BEGIN_NAMESPACE

class Ui_cSettingsCleaner
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QGridLayout *gridLayout;
    cThumbnailWidget *previewwidget_cleaned;
    cThumbnailWidget *previewwidget_actual;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_parameterName;
    QProgressBar *progressBar;
    QPushButton *pushButton_stop;
    QLabel *label_3;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_cancel;

    void setupUi(QDialog *cSettingsCleaner)
    {
        if (cSettingsCleaner->objectName().isEmpty())
            cSettingsCleaner->setObjectName(QString::fromUtf8("cSettingsCleaner"));
        cSettingsCleaner->resize(727, 660);
        cSettingsCleaner->setSizeGripEnabled(false);
        cSettingsCleaner->setModal(false);
        verticalLayout_2 = new QVBoxLayout(cSettingsCleaner);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_4 = new QLabel(cSettingsCleaner);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setWordWrap(true);

        verticalLayout_2->addWidget(label_4);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        previewwidget_cleaned = new cThumbnailWidget(cSettingsCleaner);
        previewwidget_cleaned->setObjectName(QString::fromUtf8("previewwidget_cleaned"));
        previewwidget_cleaned->setMinimumSize(QSize(16, 16));

        gridLayout->addWidget(previewwidget_cleaned, 1, 1, 1, 1);

        previewwidget_actual = new cThumbnailWidget(cSettingsCleaner);
        previewwidget_actual->setObjectName(QString::fromUtf8("previewwidget_actual"));
        previewwidget_actual->setMinimumSize(QSize(16, 16));

        gridLayout->addWidget(previewwidget_actual, 1, 0, 1, 1);

        label = new QLabel(cSettingsCleaner);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(cSettingsCleaner);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        gridLayout->setRowStretch(1, 1);

        verticalLayout_2->addLayout(gridLayout);

        label_parameterName = new QLabel(cSettingsCleaner);
        label_parameterName->setObjectName(QString::fromUtf8("label_parameterName"));

        verticalLayout_2->addWidget(label_parameterName);

        progressBar = new QProgressBar(cSettingsCleaner);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMaximum(1000);
        progressBar->setValue(0);

        verticalLayout_2->addWidget(progressBar);

        pushButton_stop = new QPushButton(cSettingsCleaner);
        pushButton_stop->setObjectName(QString::fromUtf8("pushButton_stop"));

        verticalLayout_2->addWidget(pushButton_stop);

        label_3 = new QLabel(cSettingsCleaner);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        listWidget = new QListWidget(cSettingsCleaner);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout_2->addWidget(listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_ok = new QPushButton(cSettingsCleaner);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));

        horizontalLayout->addWidget(pushButton_ok);

        pushButton_cancel = new QPushButton(cSettingsCleaner);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));

        horizontalLayout->addWidget(pushButton_cancel);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout_2->setStretch(6, 1);

        retranslateUi(cSettingsCleaner);

        QMetaObject::connectSlotsByName(cSettingsCleaner);
    } // setupUi

    void retranslateUi(QDialog *cSettingsCleaner)
    {
        cSettingsCleaner->setWindowTitle(QCoreApplication::translate("cSettingsCleaner", "Settings cleaner", nullptr));
        label_4->setText(QCoreApplication::translate("cSettingsCleaner", "This tool looks for parameters which can be defaulted without impact on image appearance.", nullptr));
        label->setText(QCoreApplication::translate("cSettingsCleaner", "Original settings", nullptr));
        label_2->setText(QCoreApplication::translate("cSettingsCleaner", "Cleaned settings", nullptr));
        label_parameterName->setText(QCoreApplication::translate("cSettingsCleaner", "Trying parameter: ", nullptr));
        pushButton_stop->setText(QCoreApplication::translate("cSettingsCleaner", "Stop", nullptr));
        label_3->setText(QCoreApplication::translate("cSettingsCleaner", "List of cleaned parameters:\n"
"(double click to remove from list)", nullptr));
        pushButton_ok->setText(QCoreApplication::translate("cSettingsCleaner", "OK", nullptr));
        pushButton_cancel->setText(QCoreApplication::translate("cSettingsCleaner", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cSettingsCleaner: public Ui_cSettingsCleaner {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_CLEANER_H
