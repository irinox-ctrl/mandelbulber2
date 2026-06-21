/********************************************************************************
** Form generated from reading UI file 'material_manager_view.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATERIAL_MANAGER_VIEW_H
#define UI_MATERIAL_MANAGER_VIEW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cMaterialManagerView
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_newMaterial;
    QPushButton *pushButton_deleteMaterial;
    QPushButton *pushButton_editMaterial;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_LoadMaterial;
    QPushButton *pushButton_SaveMaterial;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *cMaterialManagerView)
    {
        if (cMaterialManagerView->objectName().isEmpty())
            cMaterialManagerView->setObjectName(QString::fromUtf8("cMaterialManagerView"));
        cMaterialManagerView->resize(742, 327);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cMaterialManagerView->sizePolicy().hasHeightForWidth());
        cMaterialManagerView->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(cMaterialManagerView);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_newMaterial = new QPushButton(cMaterialManagerView);
        pushButton_newMaterial->setObjectName(QString::fromUtf8("pushButton_newMaterial"));
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("list-add");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8(":/system/icons/list-add.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_newMaterial->setIcon(icon);

        horizontalLayout->addWidget(pushButton_newMaterial);

        pushButton_deleteMaterial = new QPushButton(cMaterialManagerView);
        pushButton_deleteMaterial->setObjectName(QString::fromUtf8("pushButton_deleteMaterial"));
        QIcon icon1;
        iconThemeName = QString::fromUtf8("process-stop");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8(":/system/icons/process-stop.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_deleteMaterial->setIcon(icon1);

        horizontalLayout->addWidget(pushButton_deleteMaterial);

        pushButton_editMaterial = new QPushButton(cMaterialManagerView);
        pushButton_editMaterial->setObjectName(QString::fromUtf8("pushButton_editMaterial"));
        QIcon icon2;
        iconThemeName = QString::fromUtf8("applications-graphics");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QString::fromUtf8(":/system/icons/applications-graphics.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_editMaterial->setIcon(icon2);

        horizontalLayout->addWidget(pushButton_editMaterial);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton_LoadMaterial = new QPushButton(cMaterialManagerView);
        pushButton_LoadMaterial->setObjectName(QString::fromUtf8("pushButton_LoadMaterial"));
        QIcon icon3;
        iconThemeName = QString::fromUtf8("document-open");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon3 = QIcon::fromTheme(iconThemeName);
        } else {
            icon3.addFile(QString::fromUtf8(":/system/icons/document-open.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_LoadMaterial->setIcon(icon3);

        horizontalLayout_3->addWidget(pushButton_LoadMaterial);

        pushButton_SaveMaterial = new QPushButton(cMaterialManagerView);
        pushButton_SaveMaterial->setObjectName(QString::fromUtf8("pushButton_SaveMaterial"));
        QIcon icon4;
        iconThemeName = QString::fromUtf8("document-save-as");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon4 = QIcon::fromTheme(iconThemeName);
        } else {
            icon4.addFile(QString::fromUtf8(":/system/icons/document-save-as.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_SaveMaterial->setIcon(icon4);

        horizontalLayout_3->addWidget(pushButton_SaveMaterial);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(cMaterialManagerView);

        QMetaObject::connectSlotsByName(cMaterialManagerView);
    } // setupUi

    void retranslateUi(QWidget *cMaterialManagerView)
    {
        cMaterialManagerView->setWindowTitle(QCoreApplication::translate("cMaterialManagerView", "Form", nullptr));
        pushButton_newMaterial->setText(QCoreApplication::translate("cMaterialManagerView", "New material", nullptr));
        pushButton_deleteMaterial->setText(QCoreApplication::translate("cMaterialManagerView", "Delete material", nullptr));
        pushButton_editMaterial->setText(QCoreApplication::translate("cMaterialManagerView", "Edit material", nullptr));
        pushButton_LoadMaterial->setText(QCoreApplication::translate("cMaterialManagerView", "Load materials...", nullptr));
        pushButton_SaveMaterial->setText(QCoreApplication::translate("cMaterialManagerView", "Save material as....", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cMaterialManagerView: public Ui_cMaterialManagerView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATERIAL_MANAGER_VIEW_H
