/********************************************************************************
** Form generated from reading UI file 'objects_tree_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJECTS_TREE_WIDGET_H
#define UI_OBJECTS_TREE_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cObjectsTreeWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_add;
    QPushButton *pushButton_delete;
    QPushButton *pushButton_refresh;
    QTreeWidget *treeWidget_objects;

    void setupUi(QWidget *cObjectsTreeWidget)
    {
        if (cObjectsTreeWidget->objectName().isEmpty())
            cObjectsTreeWidget->setObjectName(QString::fromUtf8("cObjectsTreeWidget"));
        cObjectsTreeWidget->resize(757, 665);
        verticalLayout = new QVBoxLayout(cObjectsTreeWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_add = new QPushButton(cObjectsTreeWidget);
        pushButton_add->setObjectName(QString::fromUtf8("pushButton_add"));

        horizontalLayout->addWidget(pushButton_add);

        pushButton_delete = new QPushButton(cObjectsTreeWidget);
        pushButton_delete->setObjectName(QString::fromUtf8("pushButton_delete"));

        horizontalLayout->addWidget(pushButton_delete);

        pushButton_refresh = new QPushButton(cObjectsTreeWidget);
        pushButton_refresh->setObjectName(QString::fromUtf8("pushButton_refresh"));

        horizontalLayout->addWidget(pushButton_refresh);


        verticalLayout->addLayout(horizontalLayout);

        treeWidget_objects = new QTreeWidget(cObjectsTreeWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget_objects->setHeaderItem(__qtreewidgetitem);
        treeWidget_objects->setObjectName(QString::fromUtf8("treeWidget_objects"));

        verticalLayout->addWidget(treeWidget_objects);


        retranslateUi(cObjectsTreeWidget);

        QMetaObject::connectSlotsByName(cObjectsTreeWidget);
    } // setupUi

    void retranslateUi(QWidget *cObjectsTreeWidget)
    {
        cObjectsTreeWidget->setWindowTitle(QCoreApplication::translate("cObjectsTreeWidget", "Form", nullptr));
        pushButton_add->setText(QCoreApplication::translate("cObjectsTreeWidget", "Add", nullptr));
        pushButton_delete->setText(QCoreApplication::translate("cObjectsTreeWidget", "Delete", nullptr));
        pushButton_refresh->setText(QCoreApplication::translate("cObjectsTreeWidget", "Refresh", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cObjectsTreeWidget: public Ui_cObjectsTreeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJECTS_TREE_WIDGET_H
