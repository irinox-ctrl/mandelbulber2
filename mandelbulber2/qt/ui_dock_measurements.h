/********************************************************************************
** Form generated from reading UI file 'dock_measurements.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCK_MEASUREMENTS_H
#define UI_DOCK_MEASUREMENTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "my_line_edit.h"

QT_BEGIN_NAMESPACE

class Ui_cDockMeasurements
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_meas_get_point;
    QLabel *label;
    QFormLayout *formLayout_coordinates_10;
    QLabel *label_296;
    MyLineEdit *vect3_meas_point_x;
    QLabel *label_297;
    MyLineEdit *vect3_meas_point_y;
    QLabel *label_298;
    MyLineEdit *vect3_meas_point_z;
    QFormLayout *formLayout;
    QLabel *label_299;
    QLineEdit *edit_meas_distance_from_last;
    QLabel *label_345;
    QLineEdit *edit_meas_distance_from_camera;
    QLabel *label_2;
    QFormLayout *formLayout_coordinates_11;
    QLabel *label_300;
    MyLineEdit *vect3_meas_midpoint_x;
    QLabel *label_301;
    MyLineEdit *vect3_meas_midpoint_y;
    QLabel *label_302;
    MyLineEdit *vect3_meas_midpoint_z;
    QSpacerItem *verticalSpacer_23;

    void setupUi(QWidget *cDockMeasurements)
    {
        if (cDockMeasurements->objectName().isEmpty())
            cDockMeasurements->setObjectName(QString::fromUtf8("cDockMeasurements"));
        cDockMeasurements->resize(376, 389);
        verticalLayout = new QVBoxLayout(cDockMeasurements);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        pushButton_meas_get_point = new QPushButton(cDockMeasurements);
        pushButton_meas_get_point->setObjectName(QString::fromUtf8("pushButton_meas_get_point"));

        verticalLayout->addWidget(pushButton_meas_get_point);

        label = new QLabel(cDockMeasurements);
        label->setObjectName(QString::fromUtf8("label"));
        label->setWordWrap(true);

        verticalLayout->addWidget(label);

        formLayout_coordinates_10 = new QFormLayout();
        formLayout_coordinates_10->setObjectName(QString::fromUtf8("formLayout_coordinates_10"));
        formLayout_coordinates_10->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        formLayout_coordinates_10->setHorizontalSpacing(2);
        formLayout_coordinates_10->setVerticalSpacing(1);
        label_296 = new QLabel(cDockMeasurements);
        label_296->setObjectName(QString::fromUtf8("label_296"));

        formLayout_coordinates_10->setWidget(0, QFormLayout::LabelRole, label_296);

        vect3_meas_point_x = new MyLineEdit(cDockMeasurements);
        vect3_meas_point_x->setObjectName(QString::fromUtf8("vect3_meas_point_x"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(vect3_meas_point_x->sizePolicy().hasHeightForWidth());
        vect3_meas_point_x->setSizePolicy(sizePolicy);

        formLayout_coordinates_10->setWidget(0, QFormLayout::FieldRole, vect3_meas_point_x);

        label_297 = new QLabel(cDockMeasurements);
        label_297->setObjectName(QString::fromUtf8("label_297"));

        formLayout_coordinates_10->setWidget(1, QFormLayout::LabelRole, label_297);

        vect3_meas_point_y = new MyLineEdit(cDockMeasurements);
        vect3_meas_point_y->setObjectName(QString::fromUtf8("vect3_meas_point_y"));
        sizePolicy.setHeightForWidth(vect3_meas_point_y->sizePolicy().hasHeightForWidth());
        vect3_meas_point_y->setSizePolicy(sizePolicy);

        formLayout_coordinates_10->setWidget(1, QFormLayout::FieldRole, vect3_meas_point_y);

        label_298 = new QLabel(cDockMeasurements);
        label_298->setObjectName(QString::fromUtf8("label_298"));

        formLayout_coordinates_10->setWidget(2, QFormLayout::LabelRole, label_298);

        vect3_meas_point_z = new MyLineEdit(cDockMeasurements);
        vect3_meas_point_z->setObjectName(QString::fromUtf8("vect3_meas_point_z"));
        sizePolicy.setHeightForWidth(vect3_meas_point_z->sizePolicy().hasHeightForWidth());
        vect3_meas_point_z->setSizePolicy(sizePolicy);

        formLayout_coordinates_10->setWidget(2, QFormLayout::FieldRole, vect3_meas_point_z);


        verticalLayout->addLayout(formLayout_coordinates_10);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setLabelAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        formLayout->setHorizontalSpacing(2);
        formLayout->setVerticalSpacing(2);
        formLayout->setContentsMargins(-1, 0, -1, -1);
        label_299 = new QLabel(cDockMeasurements);
        label_299->setObjectName(QString::fromUtf8("label_299"));
        label_299->setWordWrap(true);

        formLayout->setWidget(0, QFormLayout::LabelRole, label_299);

        edit_meas_distance_from_last = new QLineEdit(cDockMeasurements);
        edit_meas_distance_from_last->setObjectName(QString::fromUtf8("edit_meas_distance_from_last"));
        sizePolicy.setHeightForWidth(edit_meas_distance_from_last->sizePolicy().hasHeightForWidth());
        edit_meas_distance_from_last->setSizePolicy(sizePolicy);
        edit_meas_distance_from_last->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::FieldRole, edit_meas_distance_from_last);

        label_345 = new QLabel(cDockMeasurements);
        label_345->setObjectName(QString::fromUtf8("label_345"));
        label_345->setWordWrap(true);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_345);

        edit_meas_distance_from_camera = new QLineEdit(cDockMeasurements);
        edit_meas_distance_from_camera->setObjectName(QString::fromUtf8("edit_meas_distance_from_camera"));
        sizePolicy.setHeightForWidth(edit_meas_distance_from_camera->sizePolicy().hasHeightForWidth());
        edit_meas_distance_from_camera->setSizePolicy(sizePolicy);
        edit_meas_distance_from_camera->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::FieldRole, edit_meas_distance_from_camera);


        verticalLayout->addLayout(formLayout);

        label_2 = new QLabel(cDockMeasurements);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setWordWrap(true);

        verticalLayout->addWidget(label_2);

        formLayout_coordinates_11 = new QFormLayout();
        formLayout_coordinates_11->setObjectName(QString::fromUtf8("formLayout_coordinates_11"));
        formLayout_coordinates_11->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        formLayout_coordinates_11->setHorizontalSpacing(2);
        formLayout_coordinates_11->setVerticalSpacing(1);
        label_300 = new QLabel(cDockMeasurements);
        label_300->setObjectName(QString::fromUtf8("label_300"));

        formLayout_coordinates_11->setWidget(0, QFormLayout::LabelRole, label_300);

        vect3_meas_midpoint_x = new MyLineEdit(cDockMeasurements);
        vect3_meas_midpoint_x->setObjectName(QString::fromUtf8("vect3_meas_midpoint_x"));
        sizePolicy.setHeightForWidth(vect3_meas_midpoint_x->sizePolicy().hasHeightForWidth());
        vect3_meas_midpoint_x->setSizePolicy(sizePolicy);

        formLayout_coordinates_11->setWidget(0, QFormLayout::FieldRole, vect3_meas_midpoint_x);

        label_301 = new QLabel(cDockMeasurements);
        label_301->setObjectName(QString::fromUtf8("label_301"));

        formLayout_coordinates_11->setWidget(1, QFormLayout::LabelRole, label_301);

        vect3_meas_midpoint_y = new MyLineEdit(cDockMeasurements);
        vect3_meas_midpoint_y->setObjectName(QString::fromUtf8("vect3_meas_midpoint_y"));
        sizePolicy.setHeightForWidth(vect3_meas_midpoint_y->sizePolicy().hasHeightForWidth());
        vect3_meas_midpoint_y->setSizePolicy(sizePolicy);

        formLayout_coordinates_11->setWidget(1, QFormLayout::FieldRole, vect3_meas_midpoint_y);

        label_302 = new QLabel(cDockMeasurements);
        label_302->setObjectName(QString::fromUtf8("label_302"));

        formLayout_coordinates_11->setWidget(2, QFormLayout::LabelRole, label_302);

        vect3_meas_midpoint_z = new MyLineEdit(cDockMeasurements);
        vect3_meas_midpoint_z->setObjectName(QString::fromUtf8("vect3_meas_midpoint_z"));
        sizePolicy.setHeightForWidth(vect3_meas_midpoint_z->sizePolicy().hasHeightForWidth());
        vect3_meas_midpoint_z->setSizePolicy(sizePolicy);

        formLayout_coordinates_11->setWidget(2, QFormLayout::FieldRole, vect3_meas_midpoint_z);


        verticalLayout->addLayout(formLayout_coordinates_11);

        verticalSpacer_23 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_23);


        retranslateUi(cDockMeasurements);

        QMetaObject::connectSlotsByName(cDockMeasurements);
    } // setupUi

    void retranslateUi(QWidget *cDockMeasurements)
    {
        cDockMeasurements->setWindowTitle(QCoreApplication::translate("cDockMeasurements", "Form", nullptr));
        pushButton_meas_get_point->setText(QCoreApplication::translate("cDockMeasurements", "Get point by mouse pointer", nullptr));
        label->setText(QCoreApplication::translate("cDockMeasurements", "Last picked point", nullptr));
        label_296->setText(QCoreApplication::translate("cDockMeasurements", "x:", nullptr));
        label_297->setText(QCoreApplication::translate("cDockMeasurements", "y:", nullptr));
        label_298->setText(QCoreApplication::translate("cDockMeasurements", "z:", nullptr));
        label_299->setText(QCoreApplication::translate("cDockMeasurements", "Distance from last point:", nullptr));
        label_345->setText(QCoreApplication::translate("cDockMeasurements", "Distance from camera:", nullptr));
        label_2->setText(QCoreApplication::translate("cDockMeasurements", "Midpoint of last two picked points", nullptr));
        label_300->setText(QCoreApplication::translate("cDockMeasurements", "x:", nullptr));
        label_301->setText(QCoreApplication::translate("cDockMeasurements", "y:", nullptr));
        label_302->setText(QCoreApplication::translate("cDockMeasurements", "z:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cDockMeasurements: public Ui_cDockMeasurements {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCK_MEASUREMENTS_H
