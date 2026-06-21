/********************************************************************************
** Form generated from reading UI file 'dock_gamepad.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCK_GAMEPAD_H
#define UI_DOCK_GAMEPAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cDockGamepad
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupCheck_gamepad_enabled;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout_gamepad_device;
    QLabel *label_149;
    QComboBox *comboBox_gamepad_device;
    QLabel *label_gamepad_no_device;
    QGroupBox *groupBox_movement_velocity;
    QVBoxLayout *verticalLayout_movement_velocity;
    QGridLayout *gridLayout_gamepad_vel;
    QLabel *label_gamepad_x;
    QLabel *label_gamepad_y;
    QLabel *label_gamepad_z;
    QSlider *sl_gamepad_movement_x;
    QSlider *sl_gamepad_movement_y;
    QSlider *sl_gamepad_movement_z;
    QGroupBox *groupBox_angle_velocity;
    QVBoxLayout *verticalLayout_angle_velocity;
    QGridLayout *gridLayout_gamepad_angle;
    QLabel *label_gamepad_yaw;
    QLabel *label_gamepad_pitch;
    QLabel *label_gamepad_roll;
    QSlider *sl_gamepad_angle_yaw;
    QSlider *sl_gamepad_angle_pitch;
    QSlider *sl_gamepad_angle_roll;
    QLabel *label_gamepad_v1_info;

    void setupUi(QWidget *cDockGamepad)
    {
        if (cDockGamepad->objectName().isEmpty())
            cDockGamepad->setObjectName(QString::fromUtf8("cDockGamepad"));
        cDockGamepad->resize(289, 458);
        verticalLayout = new QVBoxLayout(cDockGamepad);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupCheck_gamepad_enabled = new QGroupBox(cDockGamepad);
        groupCheck_gamepad_enabled->setObjectName(QString::fromUtf8("groupCheck_gamepad_enabled"));
        groupCheck_gamepad_enabled->setCheckable(true);
        groupCheck_gamepad_enabled->setChecked(false);
        verticalLayout_2 = new QVBoxLayout(groupCheck_gamepad_enabled);
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(2, 2, 2, 2);
        gridLayout_gamepad_device = new QGridLayout();
        gridLayout_gamepad_device->setObjectName(QString::fromUtf8("gridLayout_gamepad_device"));
        gridLayout_gamepad_device->setHorizontalSpacing(2);
        gridLayout_gamepad_device->setContentsMargins(-1, 0, -1, -1);
        label_149 = new QLabel(groupCheck_gamepad_enabled);
        label_149->setObjectName(QString::fromUtf8("label_149"));

        gridLayout_gamepad_device->addWidget(label_149, 1, 0, 1, 1);

        comboBox_gamepad_device = new QComboBox(groupCheck_gamepad_enabled);
        comboBox_gamepad_device->setObjectName(QString::fromUtf8("comboBox_gamepad_device"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox_gamepad_device->sizePolicy().hasHeightForWidth());
        comboBox_gamepad_device->setSizePolicy(sizePolicy);

        gridLayout_gamepad_device->addWidget(comboBox_gamepad_device, 1, 1, 1, 1);

        label_gamepad_no_device = new QLabel(groupCheck_gamepad_enabled);
        label_gamepad_no_device->setObjectName(QString::fromUtf8("label_gamepad_no_device"));

        gridLayout_gamepad_device->addWidget(label_gamepad_no_device, 0, 0, 1, 2);


        verticalLayout_2->addLayout(gridLayout_gamepad_device);

        groupBox_movement_velocity = new QGroupBox(groupCheck_gamepad_enabled);
        groupBox_movement_velocity->setObjectName(QString::fromUtf8("groupBox_movement_velocity"));
        verticalLayout_movement_velocity = new QVBoxLayout(groupBox_movement_velocity);
        verticalLayout_movement_velocity->setSpacing(1);
        verticalLayout_movement_velocity->setObjectName(QString::fromUtf8("verticalLayout_movement_velocity"));
        verticalLayout_movement_velocity->setContentsMargins(2, 2, 2, 2);
        gridLayout_gamepad_vel = new QGridLayout();
        gridLayout_gamepad_vel->setObjectName(QString::fromUtf8("gridLayout_gamepad_vel"));
        gridLayout_gamepad_vel->setContentsMargins(0, 0, -1, -1);
        label_gamepad_x = new QLabel(groupBox_movement_velocity);
        label_gamepad_x->setObjectName(QString::fromUtf8("label_gamepad_x"));

        gridLayout_gamepad_vel->addWidget(label_gamepad_x, 0, 0, 1, 1);

        label_gamepad_y = new QLabel(groupBox_movement_velocity);
        label_gamepad_y->setObjectName(QString::fromUtf8("label_gamepad_y"));

        gridLayout_gamepad_vel->addWidget(label_gamepad_y, 0, 1, 1, 1);

        label_gamepad_z = new QLabel(groupBox_movement_velocity);
        label_gamepad_z->setObjectName(QString::fromUtf8("label_gamepad_z"));

        gridLayout_gamepad_vel->addWidget(label_gamepad_z, 0, 2, 1, 1);

        sl_gamepad_movement_x = new QSlider(groupBox_movement_velocity);
        sl_gamepad_movement_x->setObjectName(QString::fromUtf8("sl_gamepad_movement_x"));
        sl_gamepad_movement_x->setEnabled(false);
        sl_gamepad_movement_x->setMinimum(-100);
        sl_gamepad_movement_x->setMaximum(100);
        sl_gamepad_movement_x->setPageStep(10);
        sl_gamepad_movement_x->setOrientation(Qt::Vertical);
        sl_gamepad_movement_x->setTickPosition(QSlider::TicksBothSides);
        sl_gamepad_movement_x->setTickInterval(10);

        gridLayout_gamepad_vel->addWidget(sl_gamepad_movement_x, 1, 0, 1, 1);

        sl_gamepad_movement_y = new QSlider(groupBox_movement_velocity);
        sl_gamepad_movement_y->setObjectName(QString::fromUtf8("sl_gamepad_movement_y"));
        sl_gamepad_movement_y->setEnabled(false);
        sl_gamepad_movement_y->setMinimum(-100);
        sl_gamepad_movement_y->setMaximum(100);
        sl_gamepad_movement_y->setPageStep(10);
        sl_gamepad_movement_y->setOrientation(Qt::Vertical);
        sl_gamepad_movement_y->setTickPosition(QSlider::TicksBothSides);
        sl_gamepad_movement_y->setTickInterval(10);

        gridLayout_gamepad_vel->addWidget(sl_gamepad_movement_y, 1, 1, 1, 1);

        sl_gamepad_movement_z = new QSlider(groupBox_movement_velocity);
        sl_gamepad_movement_z->setObjectName(QString::fromUtf8("sl_gamepad_movement_z"));
        sl_gamepad_movement_z->setEnabled(false);
        sl_gamepad_movement_z->setMinimum(-100);
        sl_gamepad_movement_z->setMaximum(100);
        sl_gamepad_movement_z->setPageStep(10);
        sl_gamepad_movement_z->setOrientation(Qt::Vertical);
        sl_gamepad_movement_z->setTickPosition(QSlider::TicksBothSides);
        sl_gamepad_movement_z->setTickInterval(10);

        gridLayout_gamepad_vel->addWidget(sl_gamepad_movement_z, 1, 2, 1, 1);


        verticalLayout_movement_velocity->addLayout(gridLayout_gamepad_vel);

        groupBox_angle_velocity = new QGroupBox(groupBox_movement_velocity);
        groupBox_angle_velocity->setObjectName(QString::fromUtf8("groupBox_angle_velocity"));
        verticalLayout_angle_velocity = new QVBoxLayout(groupBox_angle_velocity);
        verticalLayout_angle_velocity->setSpacing(1);
        verticalLayout_angle_velocity->setObjectName(QString::fromUtf8("verticalLayout_angle_velocity"));
        verticalLayout_angle_velocity->setContentsMargins(2, 2, 2, 2);

        verticalLayout_movement_velocity->addWidget(groupBox_angle_velocity);

        gridLayout_gamepad_angle = new QGridLayout();
        gridLayout_gamepad_angle->setObjectName(QString::fromUtf8("gridLayout_gamepad_angle"));
        gridLayout_gamepad_angle->setContentsMargins(0, 0, -1, -1);
        label_gamepad_yaw = new QLabel(groupBox_movement_velocity);
        label_gamepad_yaw->setObjectName(QString::fromUtf8("label_gamepad_yaw"));

        gridLayout_gamepad_angle->addWidget(label_gamepad_yaw, 0, 0, 1, 1);

        label_gamepad_pitch = new QLabel(groupBox_movement_velocity);
        label_gamepad_pitch->setObjectName(QString::fromUtf8("label_gamepad_pitch"));

        gridLayout_gamepad_angle->addWidget(label_gamepad_pitch, 0, 1, 1, 1);

        label_gamepad_roll = new QLabel(groupBox_movement_velocity);
        label_gamepad_roll->setObjectName(QString::fromUtf8("label_gamepad_roll"));

        gridLayout_gamepad_angle->addWidget(label_gamepad_roll, 0, 2, 1, 1);

        sl_gamepad_angle_yaw = new QSlider(groupBox_movement_velocity);
        sl_gamepad_angle_yaw->setObjectName(QString::fromUtf8("sl_gamepad_angle_yaw"));
        sl_gamepad_angle_yaw->setEnabled(false);
        sl_gamepad_angle_yaw->setMinimum(-100);
        sl_gamepad_angle_yaw->setMaximum(100);
        sl_gamepad_angle_yaw->setPageStep(10);
        sl_gamepad_angle_yaw->setOrientation(Qt::Vertical);
        sl_gamepad_angle_yaw->setTickPosition(QSlider::TicksBothSides);
        sl_gamepad_angle_yaw->setTickInterval(10);

        gridLayout_gamepad_angle->addWidget(sl_gamepad_angle_yaw, 1, 0, 1, 1);

        sl_gamepad_angle_pitch = new QSlider(groupBox_movement_velocity);
        sl_gamepad_angle_pitch->setObjectName(QString::fromUtf8("sl_gamepad_angle_pitch"));
        sl_gamepad_angle_pitch->setEnabled(false);
        sl_gamepad_angle_pitch->setMinimum(-100);
        sl_gamepad_angle_pitch->setMaximum(100);
        sl_gamepad_angle_pitch->setPageStep(10);
        sl_gamepad_angle_pitch->setOrientation(Qt::Vertical);
        sl_gamepad_angle_pitch->setTickPosition(QSlider::TicksBothSides);
        sl_gamepad_angle_pitch->setTickInterval(10);

        gridLayout_gamepad_angle->addWidget(sl_gamepad_angle_pitch, 1, 1, 1, 1);

        sl_gamepad_angle_roll = new QSlider(groupBox_movement_velocity);
        sl_gamepad_angle_roll->setObjectName(QString::fromUtf8("sl_gamepad_angle_roll"));
        sl_gamepad_angle_roll->setEnabled(false);
        sl_gamepad_angle_roll->setMinimum(-100);
        sl_gamepad_angle_roll->setMaximum(100);
        sl_gamepad_angle_roll->setPageStep(10);
        sl_gamepad_angle_roll->setOrientation(Qt::Vertical);
        sl_gamepad_angle_roll->setTickPosition(QSlider::TicksBothSides);
        sl_gamepad_angle_roll->setTickInterval(10);

        gridLayout_gamepad_angle->addWidget(sl_gamepad_angle_roll, 1, 2, 1, 1);


        verticalLayout_movement_velocity->addLayout(gridLayout_gamepad_angle);


        verticalLayout_2->addWidget(groupBox_movement_velocity);

        label_gamepad_v1_info = new QLabel(groupCheck_gamepad_enabled);
        label_gamepad_v1_info->setObjectName(QString::fromUtf8("label_gamepad_v1_info"));

        verticalLayout_2->addWidget(label_gamepad_v1_info);


        verticalLayout->addWidget(groupCheck_gamepad_enabled);


        retranslateUi(cDockGamepad);

        QMetaObject::connectSlotsByName(cDockGamepad);
    } // setupUi

    void retranslateUi(QWidget *cDockGamepad)
    {
        cDockGamepad->setWindowTitle(QCoreApplication::translate("cDockGamepad", "Form", nullptr));
        groupCheck_gamepad_enabled->setTitle(QCoreApplication::translate("cDockGamepad", "&Gamepad activate", nullptr));
        label_149->setText(QCoreApplication::translate("cDockGamepad", "Gamepad device:", nullptr));
        label_gamepad_no_device->setText(QCoreApplication::translate("cDockGamepad", "no device attached", nullptr));
        groupBox_movement_velocity->setTitle(QCoreApplication::translate("cDockGamepad", "movement velocity", nullptr));
        label_gamepad_x->setText(QCoreApplication::translate("cDockGamepad", "x:", nullptr));
        label_gamepad_y->setText(QCoreApplication::translate("cDockGamepad", "y:", nullptr));
        label_gamepad_z->setText(QCoreApplication::translate("cDockGamepad", "z:", nullptr));
        groupBox_angle_velocity->setTitle(QCoreApplication::translate("cDockGamepad", "angle velocity", nullptr));
        label_gamepad_yaw->setText(QCoreApplication::translate("cDockGamepad", "yaw:", nullptr));
        label_gamepad_pitch->setText(QCoreApplication::translate("cDockGamepad", "pitch:", nullptr));
        label_gamepad_roll->setText(QCoreApplication::translate("cDockGamepad", "roll:", nullptr));
        label_gamepad_v1_info->setText(QCoreApplication::translate("cDockGamepad", "(does not work properly with v1 coordinates)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cDockGamepad: public Ui_cDockGamepad {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCK_GAMEPAD_H
