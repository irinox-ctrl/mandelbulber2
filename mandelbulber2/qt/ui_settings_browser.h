/********************************************************************************
** Form generated from reading UI file 'settings_browser.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_BROWSER_H
#define UI_SETTINGS_BROWSER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cSettingsBrowser
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_folder;
    QPushButton *pushButton_parent_folder;
    QPushButton *pushButton_select_folder;
    QComboBox *comboBoxOpenCLMode;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *comboBox_filterBy;
    QLabel *label;
    QLineEdit *lineEdit_filterText;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_load;
    QPushButton *pushButton_cancel;

    void setupUi(QDialog *cSettingsBrowser)
    {
        if (cSettingsBrowser->objectName().isEmpty())
            cSettingsBrowser->setObjectName(QString::fromUtf8("cSettingsBrowser"));
        cSettingsBrowser->resize(1231, 884);
        verticalLayout = new QVBoxLayout(cSettingsBrowser);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit_folder = new QLineEdit(cSettingsBrowser);
        lineEdit_folder->setObjectName(QString::fromUtf8("lineEdit_folder"));

        horizontalLayout->addWidget(lineEdit_folder);

        pushButton_parent_folder = new QPushButton(cSettingsBrowser);
        pushButton_parent_folder->setObjectName(QString::fromUtf8("pushButton_parent_folder"));
        pushButton_parent_folder->setFocusPolicy(Qt::ClickFocus);
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("go-previous");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8(":/navigation/icons/go-previous.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_parent_folder->setIcon(icon);

        horizontalLayout->addWidget(pushButton_parent_folder);

        pushButton_select_folder = new QPushButton(cSettingsBrowser);
        pushButton_select_folder->setObjectName(QString::fromUtf8("pushButton_select_folder"));
        pushButton_select_folder->setFocusPolicy(Qt::ClickFocus);
        QIcon icon1;
        iconThemeName = QString::fromUtf8("folder");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8(":/system/icons/folder.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_select_folder->setIcon(icon1);

        horizontalLayout->addWidget(pushButton_select_folder);

        comboBoxOpenCLMode = new QComboBox(cSettingsBrowser);
        comboBoxOpenCLMode->addItem(QString());
        comboBoxOpenCLMode->addItem(QString());
        comboBoxOpenCLMode->addItem(QString());
        comboBoxOpenCLMode->addItem(QString());
        comboBoxOpenCLMode->addItem(QString());
        comboBoxOpenCLMode->setObjectName(QString::fromUtf8("comboBoxOpenCLMode"));
        comboBoxOpenCLMode->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout->addWidget(comboBoxOpenCLMode);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 10, -1, -1);
        comboBox_filterBy = new QComboBox(cSettingsBrowser);
        comboBox_filterBy->addItem(QString());
        comboBox_filterBy->addItem(QString());
        comboBox_filterBy->addItem(QString());
        comboBox_filterBy->setObjectName(QString::fromUtf8("comboBox_filterBy"));
        comboBox_filterBy->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_3->addWidget(comboBox_filterBy);

        label = new QLabel(cSettingsBrowser);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        lineEdit_filterText = new QLineEdit(cSettingsBrowser);
        lineEdit_filterText->setObjectName(QString::fromUtf8("lineEdit_filterText"));

        horizontalLayout_3->addWidget(lineEdit_filterText);


        verticalLayout->addLayout(horizontalLayout_3);

        scrollArea = new QScrollArea(cSettingsBrowser);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1215, 760));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tableWidget = new QTableWidget(scrollAreaWidgetContents);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout_2->addWidget(tableWidget);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_load = new QPushButton(cSettingsBrowser);
        pushButton_load->setObjectName(QString::fromUtf8("pushButton_load"));

        horizontalLayout_2->addWidget(pushButton_load);

        pushButton_cancel = new QPushButton(cSettingsBrowser);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));

        horizontalLayout_2->addWidget(pushButton_cancel);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(cSettingsBrowser);

        QMetaObject::connectSlotsByName(cSettingsBrowser);
    } // setupUi

    void retranslateUi(QDialog *cSettingsBrowser)
    {
        cSettingsBrowser->setWindowTitle(QCoreApplication::translate("cSettingsBrowser", "Dialog", nullptr));
        pushButton_parent_folder->setText(QString());
        pushButton_select_folder->setText(QString());
        comboBoxOpenCLMode->setItemText(0, QCoreApplication::translate("cSettingsBrowser", "Don't use OpenCL", nullptr));
        comboBoxOpenCLMode->setItemText(1, QCoreApplication::translate("cSettingsBrowser", "Use OpenCL for MC", nullptr));
        comboBoxOpenCLMode->setItemText(2, QCoreApplication::translate("cSettingsBrowser", "Use OpenCL for MC, HQ", nullptr));
        comboBoxOpenCLMode->setItemText(3, QCoreApplication::translate("cSettingsBrowser", "Use OpenCL for all", nullptr));
        comboBoxOpenCLMode->setItemText(4, QCoreApplication::translate("cSettingsBrowser", "Use OpenCL for all, HQ", nullptr));

        comboBox_filterBy->setItemText(0, QCoreApplication::translate("cSettingsBrowser", "Filter by Name", nullptr));
        comboBox_filterBy->setItemText(1, QCoreApplication::translate("cSettingsBrowser", "Filter by Fractal", nullptr));
        comboBox_filterBy->setItemText(2, QCoreApplication::translate("cSettingsBrowser", "Filter by Effect", nullptr));

        label->setText(QCoreApplication::translate("cSettingsBrowser", "Filter:", nullptr));
        pushButton_load->setText(QCoreApplication::translate("cSettingsBrowser", "Load settings", nullptr));
        pushButton_cancel->setText(QCoreApplication::translate("cSettingsBrowser", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cSettingsBrowser: public Ui_cSettingsBrowser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_BROWSER_H
