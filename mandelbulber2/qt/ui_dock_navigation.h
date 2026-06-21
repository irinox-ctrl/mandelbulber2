/********************************************************************************
** Form generated from reading UI file 'dock_navigation.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCK_NAVIGATION_H
#define UI_DOCK_NAVIGATION_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "buton_load_settings_from_widget.h"
#include "buton_reset_settings_from_widget.h"
#include "buton_save_settings_from_widget.h"
#include "my_check_box.h"
#include "my_combo_box.h"
#include "my_double_spin_box.h"
#include "my_line_edit.h"

QT_BEGIN_NAMESPACE

class Ui_cDockNavigation
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_26;
    QPushButton *pushButton_redo;
    QPushButton *pushButton_undo;
    QPushButton *pushButton_openNavigator;
    QPushButton *pushButton_stop;
    QPushButton *pushButton_render;
    QHBoxLayout *layout_quick_views;
    QPushButton *pushButton_view_home;
    QPushButton *pushButton_view_top;
    QPushButton *pushButton_view_front;
    QPushButton *pushButton_view_right;
    QGroupBox *groupBox_bookmarks;
    QVBoxLayout *layout_bookmarks;
    QListWidget *listWidget_bookmarks;
    QHBoxLayout *layout_bookmark_buttons;
    QPushButton *pushButton_bookmark_save;
    QPushButton *pushButton_bookmark_recall;
    QPushButton *pushButton_bookmark_delete;
    QHBoxLayout *layout_bookmark_io;
    QPushButton *pushButton_bookmark_export;
    QPushButton *pushButton_bookmark_import;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QComboBox *comboBox_temporary_scale;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_opencl_mode;
    MyComboBox *comboBox_opencl_mode;
    MyCheckBox *checkBox_auto_refresh;
    QHBoxLayout *horizontalLayout_3;
    cButtonLoadSettingsFromWidget *pushButton_local_load_2;
    cButtonSaveSettingsFromWidget *pushButton_local_save_2;
    cButtonResetSettingsFromWidget *pushButton_local_reset_2;
    QSpacerItem *horizontalSpacer_5;
    QScrollArea *scrollArea_navi;
    QWidget *scrollAreaWidgetContents_5;
    QVBoxLayout *verticalLayout_coordinates;
    QVBoxLayout *vl_side_functions;
    QGroupBox *groupBox_coordinates;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_cameraPosition;
    QFormLayout *formLayout;
    QLabel *label_18;
    MyLineEdit *vect3_camera_x;
    QLabel *label_19;
    MyLineEdit *vect3_camera_y;
    QLabel *label_20;
    MyLineEdit *vect3_camera_z;
    QHBoxLayout *layout_camera_copypaste;
    QPushButton *pushButton_copy_camera;
    QPushButton *pushButton_paste_camera;
    QGroupBox *groupBox_targetPosition;
    QFormLayout *formLayout_2;
    QLabel *label_121;
    MyLineEdit *vect3_target_x;
    QLabel *label_122;
    MyLineEdit *vect3_target_y;
    QLabel *label_123;
    MyLineEdit *vect3_target_z;
    QHBoxLayout *layout_target_copypaste;
    QPushButton *pushButton_copy_target;
    QPushButton *pushButton_paste_target;
    QPushButton *pushButton_reset_view;
    MyComboBox *comboBox_camera_movement_mode;
    QGridLayout *gridLayout_24;
    QLabel *label_124;
    MyLineEdit *logedit_camera_distance_to_target;
    QGridLayout *gridLayout_arrows;
    QToolButton *bu_move_forward;
    QToolButton *bu_move_backward;
    QToolButton *bu_move_left;
    QToolButton *bu_move_up;
    QToolButton *bu_move_down;
    QToolButton *bu_move_right;
    QFrame *single_camera_movement_step_de;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label_9;
    MyLineEdit *logedit_camera_movement_step;
    MyComboBox *comboBox_camera_absolute_distance_mode;
    QGroupBox *groupBox_rotation;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_2;
    QToolButton *bu_rotate_roll_left;
    QToolButton *bu_rotate_up;
    QToolButton *bu_rotate_roll_right;
    QToolButton *bu_rotate_left;
    QToolButton *bu_rotate_down;
    QToolButton *bu_rotate_right;
    QFrame *single_camera_movement_step_de_3;
    QVBoxLayout *verticalLayout_57;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_125;
    MyDoubleSpinBox *spinbox_camera_rotation_step;
    MyComboBox *comboBox_camera_rotation_mode;
    MyComboBox *comboBox_camera_straight_rotation;
    QFrame *vect3_view_angle;
    QVBoxLayout *verticalLayout_13;
    QFormLayout *formLayout_coordinates;
    QLabel *label_15;
    MyLineEdit *vect3_camera_rotation_x;
    QLabel *label_16;
    MyLineEdit *vect3_camera_rotation_y;
    QLabel *label_17;
    MyLineEdit *vect3_camera_rotation_z;
    QGroupBox *groupBox_11;
    QVBoxLayout *verticalLayout_117;
    QGridLayout *gridLayout_72;
    MyDoubleSpinBox *spinboxd_sweet_spot_horizontal_angle;
    MyDoubleSpinBox *spinboxd_sweet_spot_vertical_angle;
    QLabel *label_293;
    QLabel *label_294;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *cDockNavigation)
    {
        if (cDockNavigation->objectName().isEmpty())
            cDockNavigation->setObjectName(QString::fromUtf8("cDockNavigation"));
        cDockNavigation->resize(294, 1001);
        verticalLayout = new QVBoxLayout(cDockNavigation);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        gridLayout_26 = new QGridLayout();
        gridLayout_26->setSpacing(2);
        gridLayout_26->setObjectName(QString::fromUtf8("gridLayout_26"));
        gridLayout_26->setContentsMargins(-1, 0, -1, -1);
        pushButton_redo = new QPushButton(cDockNavigation);
        pushButton_redo->setObjectName(QString::fromUtf8("pushButton_redo"));
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("edit-redo");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8(":/system/icons/edit-redo.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_redo->setIcon(icon);

        gridLayout_26->addWidget(pushButton_redo, 1, 1, 1, 1);

        pushButton_undo = new QPushButton(cDockNavigation);
        pushButton_undo->setObjectName(QString::fromUtf8("pushButton_undo"));
        QIcon icon1;
        iconThemeName = QString::fromUtf8("edit-undo");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8(":/system/icons/edit-undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_undo->setIcon(icon1);

        gridLayout_26->addWidget(pushButton_undo, 1, 0, 1, 1);

        pushButton_openNavigator = new QPushButton(cDockNavigation);
        pushButton_openNavigator->setObjectName(QString::fromUtf8("pushButton_openNavigator"));

        gridLayout_26->addWidget(pushButton_openNavigator, 2, 0, 1, 2);

        pushButton_stop = new QPushButton(cDockNavigation);
        pushButton_stop->setObjectName(QString::fromUtf8("pushButton_stop"));
        QIcon icon2;
        iconThemeName = QString::fromUtf8("process-stop");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QString::fromUtf8(":/system/icons/process-stop.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_stop->setIcon(icon2);

        gridLayout_26->addWidget(pushButton_stop, 0, 1, 1, 1);

        pushButton_render = new QPushButton(cDockNavigation);
        pushButton_render->setObjectName(QString::fromUtf8("pushButton_render"));
        QIcon icon3;
        iconThemeName = QString::fromUtf8("applications-graphics");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon3 = QIcon::fromTheme(iconThemeName);
        } else {
            icon3.addFile(QString::fromUtf8(":/system/icons/applications-graphics.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_render->setIcon(icon3);

        gridLayout_26->addWidget(pushButton_render, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_26);

        layout_quick_views = new QHBoxLayout();
        layout_quick_views->setSpacing(2);
        layout_quick_views->setObjectName(QString::fromUtf8("layout_quick_views"));
        pushButton_view_home = new QPushButton(cDockNavigation);
        pushButton_view_home->setObjectName(QString::fromUtf8("pushButton_view_home"));
        pushButton_view_home->setMaximumSize(QSize(16777215, 28));

        layout_quick_views->addWidget(pushButton_view_home);

        pushButton_view_top = new QPushButton(cDockNavigation);
        pushButton_view_top->setObjectName(QString::fromUtf8("pushButton_view_top"));
        pushButton_view_top->setMaximumSize(QSize(16777215, 28));

        layout_quick_views->addWidget(pushButton_view_top);

        pushButton_view_front = new QPushButton(cDockNavigation);
        pushButton_view_front->setObjectName(QString::fromUtf8("pushButton_view_front"));
        pushButton_view_front->setMaximumSize(QSize(16777215, 28));

        layout_quick_views->addWidget(pushButton_view_front);

        pushButton_view_right = new QPushButton(cDockNavigation);
        pushButton_view_right->setObjectName(QString::fromUtf8("pushButton_view_right"));
        pushButton_view_right->setMaximumSize(QSize(16777215, 28));

        layout_quick_views->addWidget(pushButton_view_right);


        verticalLayout->addLayout(layout_quick_views);

        groupBox_bookmarks = new QGroupBox(cDockNavigation);
        groupBox_bookmarks->setObjectName(QString::fromUtf8("groupBox_bookmarks"));
        layout_bookmarks = new QVBoxLayout(groupBox_bookmarks);
        layout_bookmarks->setSpacing(2);
        layout_bookmarks->setObjectName(QString::fromUtf8("layout_bookmarks"));
        listWidget_bookmarks = new QListWidget(groupBox_bookmarks);
        listWidget_bookmarks->setObjectName(QString::fromUtf8("listWidget_bookmarks"));
        listWidget_bookmarks->setMaximumSize(QSize(16777215, 120));

        layout_bookmarks->addWidget(listWidget_bookmarks);

        layout_bookmark_buttons = new QHBoxLayout();
        layout_bookmark_buttons->setSpacing(2);
        layout_bookmark_buttons->setObjectName(QString::fromUtf8("layout_bookmark_buttons"));
        pushButton_bookmark_save = new QPushButton(groupBox_bookmarks);
        pushButton_bookmark_save->setObjectName(QString::fromUtf8("pushButton_bookmark_save"));
        pushButton_bookmark_save->setMaximumSize(QSize(16777215, 24));

        layout_bookmark_buttons->addWidget(pushButton_bookmark_save);

        pushButton_bookmark_recall = new QPushButton(groupBox_bookmarks);
        pushButton_bookmark_recall->setObjectName(QString::fromUtf8("pushButton_bookmark_recall"));
        pushButton_bookmark_recall->setMaximumSize(QSize(16777215, 24));

        layout_bookmark_buttons->addWidget(pushButton_bookmark_recall);

        pushButton_bookmark_delete = new QPushButton(groupBox_bookmarks);
        pushButton_bookmark_delete->setObjectName(QString::fromUtf8("pushButton_bookmark_delete"));
        pushButton_bookmark_delete->setMaximumSize(QSize(16777215, 24));

        layout_bookmark_buttons->addWidget(pushButton_bookmark_delete);


        layout_bookmarks->addLayout(layout_bookmark_buttons);

        layout_bookmark_io = new QHBoxLayout();
        layout_bookmark_io->setSpacing(2);
        layout_bookmark_io->setObjectName(QString::fromUtf8("layout_bookmark_io"));
        pushButton_bookmark_export = new QPushButton(groupBox_bookmarks);
        pushButton_bookmark_export->setObjectName(QString::fromUtf8("pushButton_bookmark_export"));
        pushButton_bookmark_export->setMaximumSize(QSize(16777215, 24));

        layout_bookmark_io->addWidget(pushButton_bookmark_export);

        pushButton_bookmark_import = new QPushButton(groupBox_bookmarks);
        pushButton_bookmark_import->setObjectName(QString::fromUtf8("pushButton_bookmark_import"));
        pushButton_bookmark_import->setMaximumSize(QSize(16777215, 24));

        layout_bookmark_io->addWidget(pushButton_bookmark_import);


        layout_bookmarks->addLayout(layout_bookmark_io);


        verticalLayout->addWidget(groupBox_bookmarks);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label = new QLabel(cDockNavigation);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_5->addWidget(label);

        comboBox_temporary_scale = new QComboBox(cDockNavigation);
        comboBox_temporary_scale->addItem(QString());
        comboBox_temporary_scale->addItem(QString());
        comboBox_temporary_scale->addItem(QString());
        comboBox_temporary_scale->addItem(QString());
        comboBox_temporary_scale->addItem(QString());
        comboBox_temporary_scale->addItem(QString());
        comboBox_temporary_scale->addItem(QString());
        comboBox_temporary_scale->setObjectName(QString::fromUtf8("comboBox_temporary_scale"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(3);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox_temporary_scale->sizePolicy().hasHeightForWidth());
        comboBox_temporary_scale->setSizePolicy(sizePolicy);
        comboBox_temporary_scale->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);
        comboBox_temporary_scale->setMinimumContentsLength(3);

        horizontalLayout_5->addWidget(comboBox_temporary_scale);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, -1, -1);
        label_opencl_mode = new QLabel(cDockNavigation);
        label_opencl_mode->setObjectName(QString::fromUtf8("label_opencl_mode"));

        horizontalLayout_2->addWidget(label_opencl_mode);

        comboBox_opencl_mode = new MyComboBox(cDockNavigation);
        comboBox_opencl_mode->addItem(QString());
        comboBox_opencl_mode->addItem(QString());
        comboBox_opencl_mode->addItem(QString());
        comboBox_opencl_mode->addItem(QString());
        comboBox_opencl_mode->setObjectName(QString::fromUtf8("comboBox_opencl_mode"));

        horizontalLayout_2->addWidget(comboBox_opencl_mode);

        horizontalLayout_2->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_2);

        checkBox_auto_refresh = new MyCheckBox(cDockNavigation);
        checkBox_auto_refresh->setObjectName(QString::fromUtf8("checkBox_auto_refresh"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(checkBox_auto_refresh->sizePolicy().hasHeightForWidth());
        checkBox_auto_refresh->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(checkBox_auto_refresh);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton_local_load_2 = new cButtonLoadSettingsFromWidget(cDockNavigation);
        pushButton_local_load_2->setObjectName(QString::fromUtf8("pushButton_local_load_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_local_load_2->sizePolicy().hasHeightForWidth());
        pushButton_local_load_2->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(pushButton_local_load_2);

        pushButton_local_save_2 = new cButtonSaveSettingsFromWidget(cDockNavigation);
        pushButton_local_save_2->setObjectName(QString::fromUtf8("pushButton_local_save_2"));
        sizePolicy2.setHeightForWidth(pushButton_local_save_2->sizePolicy().hasHeightForWidth());
        pushButton_local_save_2->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(pushButton_local_save_2);

        pushButton_local_reset_2 = new cButtonResetSettingsFromWidget(cDockNavigation);
        pushButton_local_reset_2->setObjectName(QString::fromUtf8("pushButton_local_reset_2"));
        sizePolicy2.setHeightForWidth(pushButton_local_reset_2->sizePolicy().hasHeightForWidth());
        pushButton_local_reset_2->setSizePolicy(sizePolicy2);

        horizontalLayout_3->addWidget(pushButton_local_reset_2);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_3);

        scrollArea_navi = new QScrollArea(cDockNavigation);
        scrollArea_navi->setObjectName(QString::fromUtf8("scrollArea_navi"));
        scrollArea_navi->setWidgetResizable(true);
        scrollAreaWidgetContents_5 = new QWidget();
        scrollAreaWidgetContents_5->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_5"));
        scrollAreaWidgetContents_5->setGeometry(QRect(0, 0, 288, 817));
        QSizePolicy sizePolicy3(QSizePolicy::Ignored, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(scrollAreaWidgetContents_5->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents_5->setSizePolicy(sizePolicy3);
        verticalLayout_coordinates = new QVBoxLayout(scrollAreaWidgetContents_5);
        verticalLayout_coordinates->setSpacing(2);
        verticalLayout_coordinates->setObjectName(QString::fromUtf8("verticalLayout_coordinates"));
        verticalLayout_coordinates->setContentsMargins(0, 0, 0, 2);
        vl_side_functions = new QVBoxLayout();
        vl_side_functions->setSpacing(1);
        vl_side_functions->setObjectName(QString::fromUtf8("vl_side_functions"));
        groupBox_coordinates = new QGroupBox(scrollAreaWidgetContents_5);
        groupBox_coordinates->setObjectName(QString::fromUtf8("groupBox_coordinates"));
        verticalLayout_2 = new QVBoxLayout(groupBox_coordinates);
        verticalLayout_2->setSpacing(1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(2, 2, 2, 2);
        groupBox_cameraPosition = new QGroupBox(groupBox_coordinates);
        groupBox_cameraPosition->setObjectName(QString::fromUtf8("groupBox_cameraPosition"));
        formLayout = new QFormLayout(groupBox_cameraPosition);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(2, 2, 2, 2);
        label_18 = new QLabel(groupBox_cameraPosition);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_18);

        vect3_camera_x = new MyLineEdit(groupBox_cameraPosition);
        vect3_camera_x->setObjectName(QString::fromUtf8("vect3_camera_x"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(vect3_camera_x->sizePolicy().hasHeightForWidth());
        vect3_camera_x->setSizePolicy(sizePolicy4);

        formLayout->setWidget(0, QFormLayout::FieldRole, vect3_camera_x);

        label_19 = new QLabel(groupBox_cameraPosition);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_19);

        vect3_camera_y = new MyLineEdit(groupBox_cameraPosition);
        vect3_camera_y->setObjectName(QString::fromUtf8("vect3_camera_y"));
        sizePolicy4.setHeightForWidth(vect3_camera_y->sizePolicy().hasHeightForWidth());
        vect3_camera_y->setSizePolicy(sizePolicy4);

        formLayout->setWidget(1, QFormLayout::FieldRole, vect3_camera_y);

        label_20 = new QLabel(groupBox_cameraPosition);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_20);

        vect3_camera_z = new MyLineEdit(groupBox_cameraPosition);
        vect3_camera_z->setObjectName(QString::fromUtf8("vect3_camera_z"));
        sizePolicy4.setHeightForWidth(vect3_camera_z->sizePolicy().hasHeightForWidth());
        vect3_camera_z->setSizePolicy(sizePolicy4);

        formLayout->setWidget(2, QFormLayout::FieldRole, vect3_camera_z);


        verticalLayout_2->addWidget(groupBox_cameraPosition);

        layout_camera_copypaste = new QHBoxLayout();
        layout_camera_copypaste->setSpacing(2);
        layout_camera_copypaste->setObjectName(QString::fromUtf8("layout_camera_copypaste"));
        pushButton_copy_camera = new QPushButton(groupBox_coordinates);
        pushButton_copy_camera->setObjectName(QString::fromUtf8("pushButton_copy_camera"));
        pushButton_copy_camera->setMaximumSize(QSize(16777215, 24));

        layout_camera_copypaste->addWidget(pushButton_copy_camera);

        pushButton_paste_camera = new QPushButton(groupBox_coordinates);
        pushButton_paste_camera->setObjectName(QString::fromUtf8("pushButton_paste_camera"));
        pushButton_paste_camera->setMaximumSize(QSize(16777215, 24));

        layout_camera_copypaste->addWidget(pushButton_paste_camera);


        verticalLayout_2->addLayout(layout_camera_copypaste);

        groupBox_targetPosition = new QGroupBox(groupBox_coordinates);
        groupBox_targetPosition->setObjectName(QString::fromUtf8("groupBox_targetPosition"));
        formLayout_2 = new QFormLayout(groupBox_targetPosition);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setContentsMargins(2, 2, 2, 2);
        label_121 = new QLabel(groupBox_targetPosition);
        label_121->setObjectName(QString::fromUtf8("label_121"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_121);

        vect3_target_x = new MyLineEdit(groupBox_targetPosition);
        vect3_target_x->setObjectName(QString::fromUtf8("vect3_target_x"));
        sizePolicy4.setHeightForWidth(vect3_target_x->sizePolicy().hasHeightForWidth());
        vect3_target_x->setSizePolicy(sizePolicy4);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, vect3_target_x);

        label_122 = new QLabel(groupBox_targetPosition);
        label_122->setObjectName(QString::fromUtf8("label_122"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_122);

        vect3_target_y = new MyLineEdit(groupBox_targetPosition);
        vect3_target_y->setObjectName(QString::fromUtf8("vect3_target_y"));
        sizePolicy4.setHeightForWidth(vect3_target_y->sizePolicy().hasHeightForWidth());
        vect3_target_y->setSizePolicy(sizePolicy4);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, vect3_target_y);

        label_123 = new QLabel(groupBox_targetPosition);
        label_123->setObjectName(QString::fromUtf8("label_123"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_123);

        vect3_target_z = new MyLineEdit(groupBox_targetPosition);
        vect3_target_z->setObjectName(QString::fromUtf8("vect3_target_z"));
        sizePolicy4.setHeightForWidth(vect3_target_z->sizePolicy().hasHeightForWidth());
        vect3_target_z->setSizePolicy(sizePolicy4);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, vect3_target_z);


        verticalLayout_2->addWidget(groupBox_targetPosition);

        layout_target_copypaste = new QHBoxLayout();
        layout_target_copypaste->setSpacing(2);
        layout_target_copypaste->setObjectName(QString::fromUtf8("layout_target_copypaste"));
        pushButton_copy_target = new QPushButton(groupBox_coordinates);
        pushButton_copy_target->setObjectName(QString::fromUtf8("pushButton_copy_target"));
        pushButton_copy_target->setMaximumSize(QSize(16777215, 24));

        layout_target_copypaste->addWidget(pushButton_copy_target);

        pushButton_paste_target = new QPushButton(groupBox_coordinates);
        pushButton_paste_target->setObjectName(QString::fromUtf8("pushButton_paste_target"));
        pushButton_paste_target->setMaximumSize(QSize(16777215, 24));

        layout_target_copypaste->addWidget(pushButton_paste_target);


        verticalLayout_2->addLayout(layout_target_copypaste);

        pushButton_reset_view = new QPushButton(groupBox_coordinates);
        pushButton_reset_view->setObjectName(QString::fromUtf8("pushButton_reset_view"));
        sizePolicy1.setHeightForWidth(pushButton_reset_view->sizePolicy().hasHeightForWidth());
        pushButton_reset_view->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(pushButton_reset_view);

        comboBox_camera_movement_mode = new MyComboBox(groupBox_coordinates);
        comboBox_camera_movement_mode->addItem(QString());
        comboBox_camera_movement_mode->addItem(QString());
        comboBox_camera_movement_mode->addItem(QString());
        comboBox_camera_movement_mode->setObjectName(QString::fromUtf8("comboBox_camera_movement_mode"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(comboBox_camera_movement_mode->sizePolicy().hasHeightForWidth());
        comboBox_camera_movement_mode->setSizePolicy(sizePolicy5);

        verticalLayout_2->addWidget(comboBox_camera_movement_mode);

        gridLayout_24 = new QGridLayout();
        gridLayout_24->setSpacing(2);
        gridLayout_24->setObjectName(QString::fromUtf8("gridLayout_24"));
        gridLayout_24->setContentsMargins(0, 0, -1, -1);
        label_124 = new QLabel(groupBox_coordinates);
        label_124->setObjectName(QString::fromUtf8("label_124"));

        gridLayout_24->addWidget(label_124, 0, 0, 1, 1);

        logedit_camera_distance_to_target = new MyLineEdit(groupBox_coordinates);
        logedit_camera_distance_to_target->setObjectName(QString::fromUtf8("logedit_camera_distance_to_target"));
        sizePolicy4.setHeightForWidth(logedit_camera_distance_to_target->sizePolicy().hasHeightForWidth());
        logedit_camera_distance_to_target->setSizePolicy(sizePolicy4);
        logedit_camera_distance_to_target->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_24->addWidget(logedit_camera_distance_to_target, 0, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout_24);

        gridLayout_arrows = new QGridLayout();
        gridLayout_arrows->setSpacing(1);
        gridLayout_arrows->setObjectName(QString::fromUtf8("gridLayout_arrows"));
        bu_move_forward = new QToolButton(groupBox_coordinates);
        bu_move_forward->setObjectName(QString::fromUtf8("bu_move_forward"));
        sizePolicy2.setHeightForWidth(bu_move_forward->sizePolicy().hasHeightForWidth());
        bu_move_forward->setSizePolicy(sizePolicy2);
        QIcon icon4;
        iconThemeName = QString::fromUtf8("arrow-up-double");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon4 = QIcon::fromTheme(iconThemeName);
        } else {
            icon4.addFile(QString::fromUtf8(":/navigation/icons/arrow-up-double.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        bu_move_forward->setIcon(icon4);
        bu_move_forward->setIconSize(QSize(32, 32));

        gridLayout_arrows->addWidget(bu_move_forward, 1, 0, 1, 1);

        bu_move_backward = new QToolButton(groupBox_coordinates);
        bu_move_backward->setObjectName(QString::fromUtf8("bu_move_backward"));
        sizePolicy2.setHeightForWidth(bu_move_backward->sizePolicy().hasHeightForWidth());
        bu_move_backward->setSizePolicy(sizePolicy2);
        QIcon icon5;
        iconThemeName = QString::fromUtf8("arrow-down-double");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon5 = QIcon::fromTheme(iconThemeName);
        } else {
            icon5.addFile(QString::fromUtf8(":/navigation/icons/arrow-down-double.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        bu_move_backward->setIcon(icon5);
        bu_move_backward->setIconSize(QSize(32, 32));

        gridLayout_arrows->addWidget(bu_move_backward, 2, 0, 1, 1);

        bu_move_left = new QToolButton(groupBox_coordinates);
        bu_move_left->setObjectName(QString::fromUtf8("bu_move_left"));
        sizePolicy2.setHeightForWidth(bu_move_left->sizePolicy().hasHeightForWidth());
        bu_move_left->setSizePolicy(sizePolicy2);
        QIcon icon6;
        iconThemeName = QString::fromUtf8("go-previous");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon6 = QIcon::fromTheme(iconThemeName);
        } else {
            icon6.addFile(QString::fromUtf8(":/navigation/icons/go-previous.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        bu_move_left->setIcon(icon6);
        bu_move_left->setIconSize(QSize(32, 32));

        gridLayout_arrows->addWidget(bu_move_left, 2, 1, 1, 1);

        bu_move_up = new QToolButton(groupBox_coordinates);
        bu_move_up->setObjectName(QString::fromUtf8("bu_move_up"));
        sizePolicy2.setHeightForWidth(bu_move_up->sizePolicy().hasHeightForWidth());
        bu_move_up->setSizePolicy(sizePolicy2);
        QIcon icon7;
        iconThemeName = QString::fromUtf8("go-up");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon7 = QIcon::fromTheme(iconThemeName);
        } else {
            icon7.addFile(QString::fromUtf8(":/navigation/icons/go-up.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        bu_move_up->setIcon(icon7);
        bu_move_up->setIconSize(QSize(32, 32));

        gridLayout_arrows->addWidget(bu_move_up, 1, 2, 1, 1);

        bu_move_down = new QToolButton(groupBox_coordinates);
        bu_move_down->setObjectName(QString::fromUtf8("bu_move_down"));
        sizePolicy2.setHeightForWidth(bu_move_down->sizePolicy().hasHeightForWidth());
        bu_move_down->setSizePolicy(sizePolicy2);
        QIcon icon8;
        iconThemeName = QString::fromUtf8("go-down");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon8 = QIcon::fromTheme(iconThemeName);
        } else {
            icon8.addFile(QString::fromUtf8(":/navigation/icons/go-down.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        bu_move_down->setIcon(icon8);
        bu_move_down->setIconSize(QSize(32, 32));

        gridLayout_arrows->addWidget(bu_move_down, 2, 2, 1, 1);

        bu_move_right = new QToolButton(groupBox_coordinates);
        bu_move_right->setObjectName(QString::fromUtf8("bu_move_right"));
        sizePolicy2.setHeightForWidth(bu_move_right->sizePolicy().hasHeightForWidth());
        bu_move_right->setSizePolicy(sizePolicy2);
        QIcon icon9;
        iconThemeName = QString::fromUtf8("go-next");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon9 = QIcon::fromTheme(iconThemeName);
        } else {
            icon9.addFile(QString::fromUtf8(":/navigation/icons/go-next.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        bu_move_right->setIcon(icon9);
        bu_move_right->setIconSize(QSize(32, 32));

        gridLayout_arrows->addWidget(bu_move_right, 2, 3, 1, 1);


        verticalLayout_2->addLayout(gridLayout_arrows);

        single_camera_movement_step_de = new QFrame(groupBox_coordinates);
        single_camera_movement_step_de->setObjectName(QString::fromUtf8("single_camera_movement_step_de"));
        single_camera_movement_step_de->setFrameShape(QFrame::StyledPanel);
        single_camera_movement_step_de->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(single_camera_movement_step_de);
        verticalLayout_4->setSpacing(2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(2, 2, 2, 2);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_9 = new QLabel(single_camera_movement_step_de);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout->addWidget(label_9);

        logedit_camera_movement_step = new MyLineEdit(single_camera_movement_step_de);
        logedit_camera_movement_step->setObjectName(QString::fromUtf8("logedit_camera_movement_step"));
        sizePolicy4.setHeightForWidth(logedit_camera_movement_step->sizePolicy().hasHeightForWidth());
        logedit_camera_movement_step->setSizePolicy(sizePolicy4);

        horizontalLayout->addWidget(logedit_camera_movement_step);


        verticalLayout_4->addLayout(horizontalLayout);


        verticalLayout_2->addWidget(single_camera_movement_step_de);

        comboBox_camera_absolute_distance_mode = new MyComboBox(groupBox_coordinates);
        comboBox_camera_absolute_distance_mode->addItem(QString());
        comboBox_camera_absolute_distance_mode->addItem(QString());
        comboBox_camera_absolute_distance_mode->setObjectName(QString::fromUtf8("comboBox_camera_absolute_distance_mode"));
        sizePolicy5.setHeightForWidth(comboBox_camera_absolute_distance_mode->sizePolicy().hasHeightForWidth());
        comboBox_camera_absolute_distance_mode->setSizePolicy(sizePolicy5);

        verticalLayout_2->addWidget(comboBox_camera_absolute_distance_mode);


        vl_side_functions->addWidget(groupBox_coordinates);

        groupBox_rotation = new QGroupBox(scrollAreaWidgetContents_5);
        groupBox_rotation->setObjectName(QString::fromUtf8("groupBox_rotation"));
        verticalLayout_3 = new QVBoxLayout(groupBox_rotation);
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(2, 2, 2, 2);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(1);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        bu_rotate_roll_left = new QToolButton(groupBox_rotation);
        bu_rotate_roll_left->setObjectName(QString::fromUtf8("bu_rotate_roll_left"));
        sizePolicy2.setHeightForWidth(bu_rotate_roll_left->sizePolicy().hasHeightForWidth());
        bu_rotate_roll_left->setSizePolicy(sizePolicy2);
        bu_rotate_roll_left->setMinimumSize(QSize(0, 0));
        QIcon icon10;
        iconThemeName = QString::fromUtf8("object-rotate-left");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon10 = QIcon::fromTheme(iconThemeName);
        } else {
            icon10.addFile(QString::fromUtf8(":/navigation/icons/object-rotate-left.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        bu_rotate_roll_left->setIcon(icon10);
        bu_rotate_roll_left->setIconSize(QSize(32, 32));

        gridLayout_2->addWidget(bu_rotate_roll_left, 2, 1, 1, 1);

        bu_rotate_up = new QToolButton(groupBox_rotation);
        bu_rotate_up->setObjectName(QString::fromUtf8("bu_rotate_up"));
        sizePolicy2.setHeightForWidth(bu_rotate_up->sizePolicy().hasHeightForWidth());
        bu_rotate_up->setSizePolicy(sizePolicy2);
        bu_rotate_up->setMinimumSize(QSize(0, 0));
        bu_rotate_up->setIcon(icon7);
        bu_rotate_up->setIconSize(QSize(32, 32));

        gridLayout_2->addWidget(bu_rotate_up, 2, 2, 1, 1);

        bu_rotate_roll_right = new QToolButton(groupBox_rotation);
        bu_rotate_roll_right->setObjectName(QString::fromUtf8("bu_rotate_roll_right"));
        sizePolicy2.setHeightForWidth(bu_rotate_roll_right->sizePolicy().hasHeightForWidth());
        bu_rotate_roll_right->setSizePolicy(sizePolicy2);
        bu_rotate_roll_right->setMinimumSize(QSize(0, 0));
        QIcon icon11;
        iconThemeName = QString::fromUtf8("object-rotate-right");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon11 = QIcon::fromTheme(iconThemeName);
        } else {
            icon11.addFile(QString::fromUtf8(":/navigation/icons/object-rotate-right.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        bu_rotate_roll_right->setIcon(icon11);
        bu_rotate_roll_right->setIconSize(QSize(32, 32));

        gridLayout_2->addWidget(bu_rotate_roll_right, 2, 3, 1, 1);

        bu_rotate_left = new QToolButton(groupBox_rotation);
        bu_rotate_left->setObjectName(QString::fromUtf8("bu_rotate_left"));
        sizePolicy2.setHeightForWidth(bu_rotate_left->sizePolicy().hasHeightForWidth());
        bu_rotate_left->setSizePolicy(sizePolicy2);
        bu_rotate_left->setMinimumSize(QSize(0, 0));
        bu_rotate_left->setIcon(icon6);
        bu_rotate_left->setIconSize(QSize(32, 32));

        gridLayout_2->addWidget(bu_rotate_left, 3, 1, 1, 1);

        bu_rotate_down = new QToolButton(groupBox_rotation);
        bu_rotate_down->setObjectName(QString::fromUtf8("bu_rotate_down"));
        sizePolicy2.setHeightForWidth(bu_rotate_down->sizePolicy().hasHeightForWidth());
        bu_rotate_down->setSizePolicy(sizePolicy2);
        bu_rotate_down->setMinimumSize(QSize(0, 0));
        bu_rotate_down->setIcon(icon8);
        bu_rotate_down->setIconSize(QSize(32, 32));

        gridLayout_2->addWidget(bu_rotate_down, 3, 2, 1, 1);

        bu_rotate_right = new QToolButton(groupBox_rotation);
        bu_rotate_right->setObjectName(QString::fromUtf8("bu_rotate_right"));
        sizePolicy2.setHeightForWidth(bu_rotate_right->sizePolicy().hasHeightForWidth());
        bu_rotate_right->setSizePolicy(sizePolicy2);
        bu_rotate_right->setMinimumSize(QSize(0, 0));
        bu_rotate_right->setIcon(icon9);
        bu_rotate_right->setIconSize(QSize(32, 32));

        gridLayout_2->addWidget(bu_rotate_right, 3, 3, 1, 1);


        verticalLayout_3->addLayout(gridLayout_2);

        single_camera_movement_step_de_3 = new QFrame(groupBox_rotation);
        single_camera_movement_step_de_3->setObjectName(QString::fromUtf8("single_camera_movement_step_de_3"));
        single_camera_movement_step_de_3->setFrameShape(QFrame::StyledPanel);
        single_camera_movement_step_de_3->setFrameShadow(QFrame::Raised);
        verticalLayout_57 = new QVBoxLayout(single_camera_movement_step_de_3);
        verticalLayout_57->setSpacing(2);
        verticalLayout_57->setObjectName(QString::fromUtf8("verticalLayout_57"));
        verticalLayout_57->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(2);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_125 = new QLabel(single_camera_movement_step_de_3);
        label_125->setObjectName(QString::fromUtf8("label_125"));

        horizontalLayout_11->addWidget(label_125);

        spinbox_camera_rotation_step = new MyDoubleSpinBox(single_camera_movement_step_de_3);
        spinbox_camera_rotation_step->setObjectName(QString::fromUtf8("spinbox_camera_rotation_step"));
        sizePolicy1.setHeightForWidth(spinbox_camera_rotation_step->sizePolicy().hasHeightForWidth());
        spinbox_camera_rotation_step->setSizePolicy(sizePolicy1);
        spinbox_camera_rotation_step->setDecimals(2);
        spinbox_camera_rotation_step->setMinimum(0.100000000000000);
        spinbox_camera_rotation_step->setMaximum(90.000000000000000);
        spinbox_camera_rotation_step->setSingleStep(1.000000000000000);
        spinbox_camera_rotation_step->setValue(15.000000000000000);

        horizontalLayout_11->addWidget(spinbox_camera_rotation_step);


        verticalLayout_57->addLayout(horizontalLayout_11);


        verticalLayout_3->addWidget(single_camera_movement_step_de_3);

        comboBox_camera_rotation_mode = new MyComboBox(groupBox_rotation);
        comboBox_camera_rotation_mode->addItem(QString());
        comboBox_camera_rotation_mode->addItem(QString());
        comboBox_camera_rotation_mode->setObjectName(QString::fromUtf8("comboBox_camera_rotation_mode"));
        sizePolicy5.setHeightForWidth(comboBox_camera_rotation_mode->sizePolicy().hasHeightForWidth());
        comboBox_camera_rotation_mode->setSizePolicy(sizePolicy5);

        verticalLayout_3->addWidget(comboBox_camera_rotation_mode);

        comboBox_camera_straight_rotation = new MyComboBox(groupBox_rotation);
        comboBox_camera_straight_rotation->addItem(QString());
        comboBox_camera_straight_rotation->addItem(QString());
        comboBox_camera_straight_rotation->setObjectName(QString::fromUtf8("comboBox_camera_straight_rotation"));
        sizePolicy5.setHeightForWidth(comboBox_camera_straight_rotation->sizePolicy().hasHeightForWidth());
        comboBox_camera_straight_rotation->setSizePolicy(sizePolicy5);

        verticalLayout_3->addWidget(comboBox_camera_straight_rotation);

        vect3_view_angle = new QFrame(groupBox_rotation);
        vect3_view_angle->setObjectName(QString::fromUtf8("vect3_view_angle"));
        vect3_view_angle->setFrameShape(QFrame::StyledPanel);
        vect3_view_angle->setFrameShadow(QFrame::Raised);
        verticalLayout_13 = new QVBoxLayout(vect3_view_angle);
        verticalLayout_13->setSpacing(2);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(2, 2, 2, 2);
        formLayout_coordinates = new QFormLayout();
        formLayout_coordinates->setObjectName(QString::fromUtf8("formLayout_coordinates"));
        formLayout_coordinates->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
        formLayout_coordinates->setHorizontalSpacing(2);
        formLayout_coordinates->setVerticalSpacing(1);
        label_15 = new QLabel(vect3_view_angle);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        formLayout_coordinates->setWidget(0, QFormLayout::LabelRole, label_15);

        vect3_camera_rotation_x = new MyLineEdit(vect3_view_angle);
        vect3_camera_rotation_x->setObjectName(QString::fromUtf8("vect3_camera_rotation_x"));
        sizePolicy4.setHeightForWidth(vect3_camera_rotation_x->sizePolicy().hasHeightForWidth());
        vect3_camera_rotation_x->setSizePolicy(sizePolicy4);

        formLayout_coordinates->setWidget(0, QFormLayout::FieldRole, vect3_camera_rotation_x);

        label_16 = new QLabel(vect3_view_angle);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        formLayout_coordinates->setWidget(1, QFormLayout::LabelRole, label_16);

        vect3_camera_rotation_y = new MyLineEdit(vect3_view_angle);
        vect3_camera_rotation_y->setObjectName(QString::fromUtf8("vect3_camera_rotation_y"));
        sizePolicy4.setHeightForWidth(vect3_camera_rotation_y->sizePolicy().hasHeightForWidth());
        vect3_camera_rotation_y->setSizePolicy(sizePolicy4);

        formLayout_coordinates->setWidget(1, QFormLayout::FieldRole, vect3_camera_rotation_y);

        label_17 = new QLabel(vect3_view_angle);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        formLayout_coordinates->setWidget(2, QFormLayout::LabelRole, label_17);

        vect3_camera_rotation_z = new MyLineEdit(vect3_view_angle);
        vect3_camera_rotation_z->setObjectName(QString::fromUtf8("vect3_camera_rotation_z"));
        sizePolicy4.setHeightForWidth(vect3_camera_rotation_z->sizePolicy().hasHeightForWidth());
        vect3_camera_rotation_z->setSizePolicy(sizePolicy4);

        formLayout_coordinates->setWidget(2, QFormLayout::FieldRole, vect3_camera_rotation_z);


        verticalLayout_13->addLayout(formLayout_coordinates);


        verticalLayout_3->addWidget(vect3_view_angle);


        vl_side_functions->addWidget(groupBox_rotation);

        groupBox_11 = new QGroupBox(scrollAreaWidgetContents_5);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        verticalLayout_117 = new QVBoxLayout(groupBox_11);
        verticalLayout_117->setSpacing(2);
        verticalLayout_117->setObjectName(QString::fromUtf8("verticalLayout_117"));
        verticalLayout_117->setContentsMargins(2, 2, 2, 2);
        gridLayout_72 = new QGridLayout();
        gridLayout_72->setSpacing(2);
        gridLayout_72->setObjectName(QString::fromUtf8("gridLayout_72"));
        gridLayout_72->setContentsMargins(-1, 0, -1, -1);
        spinboxd_sweet_spot_horizontal_angle = new MyDoubleSpinBox(groupBox_11);
        spinboxd_sweet_spot_horizontal_angle->setObjectName(QString::fromUtf8("spinboxd_sweet_spot_horizontal_angle"));
        sizePolicy1.setHeightForWidth(spinboxd_sweet_spot_horizontal_angle->sizePolicy().hasHeightForWidth());
        spinboxd_sweet_spot_horizontal_angle->setSizePolicy(sizePolicy1);
        spinboxd_sweet_spot_horizontal_angle->setDecimals(2);
        spinboxd_sweet_spot_horizontal_angle->setMinimum(-180.000000000000000);
        spinboxd_sweet_spot_horizontal_angle->setMaximum(180.000000000000000);
        spinboxd_sweet_spot_horizontal_angle->setSingleStep(1.000000000000000);

        gridLayout_72->addWidget(spinboxd_sweet_spot_horizontal_angle, 1, 0, 1, 1);

        spinboxd_sweet_spot_vertical_angle = new MyDoubleSpinBox(groupBox_11);
        spinboxd_sweet_spot_vertical_angle->setObjectName(QString::fromUtf8("spinboxd_sweet_spot_vertical_angle"));
        sizePolicy1.setHeightForWidth(spinboxd_sweet_spot_vertical_angle->sizePolicy().hasHeightForWidth());
        spinboxd_sweet_spot_vertical_angle->setSizePolicy(sizePolicy1);
        spinboxd_sweet_spot_vertical_angle->setDecimals(2);
        spinboxd_sweet_spot_vertical_angle->setMinimum(-90.000000000000000);
        spinboxd_sweet_spot_vertical_angle->setMaximum(90.000000000000000);
        spinboxd_sweet_spot_vertical_angle->setSingleStep(1.000000000000000);

        gridLayout_72->addWidget(spinboxd_sweet_spot_vertical_angle, 1, 1, 1, 1);

        label_293 = new QLabel(groupBox_11);
        label_293->setObjectName(QString::fromUtf8("label_293"));
        label_293->setAlignment(Qt::AlignCenter);

        gridLayout_72->addWidget(label_293, 0, 0, 1, 1);

        label_294 = new QLabel(groupBox_11);
        label_294->setObjectName(QString::fromUtf8("label_294"));
        label_294->setAlignment(Qt::AlignCenter);

        gridLayout_72->addWidget(label_294, 0, 1, 1, 1);


        verticalLayout_117->addLayout(gridLayout_72);


        vl_side_functions->addWidget(groupBox_11);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vl_side_functions->addItem(verticalSpacer_2);


        verticalLayout_coordinates->addLayout(vl_side_functions);

        scrollArea_navi->setWidget(scrollAreaWidgetContents_5);

        verticalLayout->addWidget(scrollArea_navi);

        QWidget::setTabOrder(pushButton_render, pushButton_stop);
        QWidget::setTabOrder(pushButton_stop, pushButton_undo);
        QWidget::setTabOrder(pushButton_undo, pushButton_redo);
        QWidget::setTabOrder(pushButton_redo, checkBox_auto_refresh);
        QWidget::setTabOrder(checkBox_auto_refresh, scrollArea_navi);
        QWidget::setTabOrder(scrollArea_navi, pushButton_reset_view);
        QWidget::setTabOrder(pushButton_reset_view, comboBox_camera_movement_mode);
        QWidget::setTabOrder(comboBox_camera_movement_mode, logedit_camera_distance_to_target);
        QWidget::setTabOrder(logedit_camera_distance_to_target, bu_move_forward);
        QWidget::setTabOrder(bu_move_forward, bu_move_backward);
        QWidget::setTabOrder(bu_move_backward, bu_move_up);
        QWidget::setTabOrder(bu_move_up, bu_move_left);
        QWidget::setTabOrder(bu_move_left, bu_move_down);
        QWidget::setTabOrder(bu_move_down, bu_move_right);
        QWidget::setTabOrder(bu_move_right, logedit_camera_movement_step);
        QWidget::setTabOrder(logedit_camera_movement_step, comboBox_camera_absolute_distance_mode);
        QWidget::setTabOrder(comboBox_camera_absolute_distance_mode, bu_rotate_roll_left);
        QWidget::setTabOrder(bu_rotate_roll_left, bu_rotate_up);
        QWidget::setTabOrder(bu_rotate_up, bu_rotate_roll_right);
        QWidget::setTabOrder(bu_rotate_roll_right, bu_rotate_left);
        QWidget::setTabOrder(bu_rotate_left, bu_rotate_down);
        QWidget::setTabOrder(bu_rotate_down, bu_rotate_right);
        QWidget::setTabOrder(bu_rotate_right, spinbox_camera_rotation_step);
        QWidget::setTabOrder(spinbox_camera_rotation_step, comboBox_camera_rotation_mode);
        QWidget::setTabOrder(comboBox_camera_rotation_mode, comboBox_camera_straight_rotation);
        QWidget::setTabOrder(comboBox_camera_straight_rotation, vect3_camera_rotation_y);
        QWidget::setTabOrder(vect3_camera_rotation_y, vect3_camera_rotation_x);
        QWidget::setTabOrder(vect3_camera_rotation_x, vect3_camera_rotation_z);
        QWidget::setTabOrder(vect3_camera_rotation_z, spinboxd_sweet_spot_horizontal_angle);
        QWidget::setTabOrder(spinboxd_sweet_spot_horizontal_angle, spinboxd_sweet_spot_vertical_angle);

        retranslateUi(cDockNavigation);

        QMetaObject::connectSlotsByName(cDockNavigation);
    } // setupUi

    void retranslateUi(QWidget *cDockNavigation)
    {
        cDockNavigation->setWindowTitle(QCoreApplication::translate("cDockNavigation", "Form", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_redo->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Redo last revoked change of settings and start rendering of image</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_redo->setText(QCoreApplication::translate("cDockNavigation", "REDO", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_undo->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Discard last change of settings and start rendering of image</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_undo->setText(QCoreApplication::translate("cDockNavigation", "UNDO", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_openNavigator->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body> <p>Open a new Navigator window initialized with the current scene and camera for interactive navigation and view selection.</p> <p>Notes: - You can open multiple Navigator windows. - Close the Navigator when finished to free resources.</p> </body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_openNavigator->setText(QCoreApplication::translate("cDockNavigation", "Open new navigator", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_stop->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Terminate rendering</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_stop->setText(QCoreApplication::translate("cDockNavigation", "STOP", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_render->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Start rendering of image based on actual settings</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_render->setText(QCoreApplication::translate("cDockNavigation", "RENDER", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_view_home->setToolTip(QCoreApplication::translate("cDockNavigation", "Default perspective view", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_view_home->setText(QCoreApplication::translate("cDockNavigation", "Home", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_view_top->setToolTip(QCoreApplication::translate("cDockNavigation", "Top-down view (looking down Z axis)", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_view_top->setText(QCoreApplication::translate("cDockNavigation", "Top", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_view_front->setToolTip(QCoreApplication::translate("cDockNavigation", "Front view (looking along Y axis)", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_view_front->setText(QCoreApplication::translate("cDockNavigation", "Front", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_view_right->setToolTip(QCoreApplication::translate("cDockNavigation", "Right side view (looking along X axis)", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_view_right->setText(QCoreApplication::translate("cDockNavigation", "Right", nullptr));
        groupBox_bookmarks->setTitle(QCoreApplication::translate("cDockNavigation", "Bookmarks", nullptr));
#if QT_CONFIG(tooltip)
        listWidget_bookmarks->setToolTip(QCoreApplication::translate("cDockNavigation", "Saved camera positions \342\200\224 double-click to recall", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_bookmark_save->setText(QCoreApplication::translate("cDockNavigation", "Save", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_bookmark_save->setToolTip(QCoreApplication::translate("cDockNavigation", "Save current camera position as bookmark", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_bookmark_recall->setText(QCoreApplication::translate("cDockNavigation", "Recall", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_bookmark_recall->setToolTip(QCoreApplication::translate("cDockNavigation", "Go to selected bookmark position", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_bookmark_delete->setText(QCoreApplication::translate("cDockNavigation", "Delete", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_bookmark_delete->setToolTip(QCoreApplication::translate("cDockNavigation", "Delete selected bookmark", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_bookmark_export->setText(QCoreApplication::translate("cDockNavigation", "Export", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_bookmark_export->setToolTip(QCoreApplication::translate("cDockNavigation", "Export all bookmarks to JSON file", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_bookmark_import->setText(QCoreApplication::translate("cDockNavigation", "Import", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_bookmark_import->setToolTip(QCoreApplication::translate("cDockNavigation", "Import bookmarks from JSON file", nullptr));
#endif // QT_CONFIG(tooltip)
        label->setText(QCoreApplication::translate("cDockNavigation", "Temporary scale:", nullptr));
        comboBox_temporary_scale->setItemText(0, QCoreApplication::translate("cDockNavigation", "1", nullptr));
        comboBox_temporary_scale->setItemText(1, QCoreApplication::translate("cDockNavigation", "1/2", nullptr));
        comboBox_temporary_scale->setItemText(2, QCoreApplication::translate("cDockNavigation", "1/4", nullptr));
        comboBox_temporary_scale->setItemText(3, QCoreApplication::translate("cDockNavigation", "1/8", nullptr));
        comboBox_temporary_scale->setItemText(4, QCoreApplication::translate("cDockNavigation", "1/16", nullptr));
        comboBox_temporary_scale->setItemText(5, QCoreApplication::translate("cDockNavigation", "1/32", nullptr));
        comboBox_temporary_scale->setItemText(6, QCoreApplication::translate("cDockNavigation", "1/64", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_temporary_scale->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body> <p>Temporarily downscale rendering resolution for faster previews.</p> <p>Options: - 1 = full resolution (no downscale). - 1/2, 1/4, \342\200\246 1/64 = render with width and height divided by 2, 4, \342\200\246 64 (roughly N\302\262 speedup).</p> <p>Notes: - Affects only temporary/preview renders; image_width/height and saved outputs are unchanged. - Useful during navigation and Auto refresh; set back to 1 for final quality renders.</p> </body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_opencl_mode->setText(QCoreApplication::translate("cDockNavigation", "OpenCL mode:", nullptr));
        comboBox_opencl_mode->setItemText(0, QCoreApplication::translate("cDockNavigation", "no OpenCL", nullptr));
        comboBox_opencl_mode->setItemText(1, QCoreApplication::translate("cDockNavigation", "fast", nullptr));
        comboBox_opencl_mode->setItemText(2, QCoreApplication::translate("cDockNavigation", "medium", nullptr));
        comboBox_opencl_mode->setItemText(3, QCoreApplication::translate("cDockNavigation", "full", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_opencl_mode->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Modes for OpenCL computation (GPU support):</p><p><span style=\" font-weight:600;\">no OpenCL</span> - use only CPU</p><p><span style=\" font-weight:600;\">fast</span> - very fast rendering on GPU. Fractal has visible shape, but colors and effects are not calculated. It is very good mode for fast camera navigation and looking for interesting fractal shapes in auto-refresh mode.</p><p><span style=\" font-weight:600;\">medium</span> - medium rendering speed on GPU. There is calculated color of the fractal, light sources with shadows are used. There is used only first defined material. Reflections and volumetric effects are not calculated.</p><p><span style=\" font-weight:600;\">full</span> - the most accurate and the the slowest rendering. Uses more GPU resources. All effects are calculated .</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBox_auto_refresh->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Automatically re-render the image when any setting changes.</p><p>Behavior: - Checks for changes at a fixed interval and starts a new render only if parameters changed. </p><p>Tips: - The interval is set in Preferences \342\206\222 Image auto-refresh period. - For faster previews, combine with Temporary scale (e.g., 1/4, 1/8); set back to 1 for final renders. - May increase CPU/GPU usage; turn off for manual control.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_auto_refresh->setText(QCoreApplication::translate("cDockNavigation", "Auto-refresh", nullptr));
        pushButton_local_load_2->setText(QCoreApplication::translate("cDockNavigation", "Load", nullptr));
        pushButton_local_save_2->setText(QCoreApplication::translate("cDockNavigation", "Save", nullptr));
        pushButton_local_reset_2->setText(QCoreApplication::translate("cDockNavigation", "Reset", nullptr));
#if QT_CONFIG(tooltip)
        groupBox_coordinates->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>These parameters and gauges controls position of camera and point where the camera is looking at (target)</p><p><br/></p><p><img src=\":/tooltips/tooltips_images/Camera target.png\"/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_coordinates->setTitle(QCoreApplication::translate("cDockNavigation", "Coordinates:", nullptr));
#if QT_CONFIG(tooltip)
        groupBox_cameraPosition->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body> <p>Camera world coordinates (position of the viewpoint).</p> <p>Set X, Y, Z to move the camera. You can also use the navigation buttons or mouse controls to update these values interactively.</p> <p>Notes: - Works together with Target and Rotation to define the view. - With Auto refresh enabled the image re-renders after changes; otherwise click Render.</p> </body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_cameraPosition->setTitle(QCoreApplication::translate("cDockNavigation", "Camera", nullptr));
        label_18->setText(QCoreApplication::translate("cDockNavigation", "x:", nullptr));
        label_19->setText(QCoreApplication::translate("cDockNavigation", "y:", nullptr));
        label_20->setText(QCoreApplication::translate("cDockNavigation", "z:", nullptr));
        pushButton_copy_camera->setText(QCoreApplication::translate("cDockNavigation", "Copy Camera", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_copy_camera->setToolTip(QCoreApplication::translate("cDockNavigation", "Copy camera XYZ to clipboard", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_paste_camera->setText(QCoreApplication::translate("cDockNavigation", "Paste Camera", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_paste_camera->setToolTip(QCoreApplication::translate("cDockNavigation", "Paste XYZ from clipboard to camera position", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        groupBox_targetPosition->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body> <p>World coordinates of the target (the point the camera looks at).</p> <p>Set X, Y, Z to aim the camera without moving its position. Adjusting the target changes the view direction; the camera\342\200\223target distance updates accordingly.</p> <p>Tips: - Combine with Camera and Rotation for precise framing. - Use navigation buttons in \342\200\234Move target\342\200\235 mode to shift the target interactively. - With Auto refresh enabled the image re-renders after changes; otherwise click Render.</p> </body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_targetPosition->setTitle(QCoreApplication::translate("cDockNavigation", "Target", nullptr));
        label_121->setText(QCoreApplication::translate("cDockNavigation", "x:", nullptr));
        label_122->setText(QCoreApplication::translate("cDockNavigation", "y:", nullptr));
        label_123->setText(QCoreApplication::translate("cDockNavigation", "z:", nullptr));
        pushButton_copy_target->setText(QCoreApplication::translate("cDockNavigation", "Copy Target", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_copy_target->setToolTip(QCoreApplication::translate("cDockNavigation", "Copy target XYZ to clipboard", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_paste_target->setText(QCoreApplication::translate("cDockNavigation", "Paste Target", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_paste_target->setToolTip(QCoreApplication::translate("cDockNavigation", "Paste XYZ from clipboard to target position", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        pushButton_reset_view->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Set camera far from the fractal. It keeps actual camera angle.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_reset_view->setText(QCoreApplication::translate("cDockNavigation", "Reset view", nullptr));
        comboBox_camera_movement_mode->setItemText(0, QCoreApplication::translate("cDockNavigation", "Move camera and target", nullptr));
        comboBox_camera_movement_mode->setItemText(1, QCoreApplication::translate("cDockNavigation", "Move camera", nullptr));
        comboBox_camera_movement_mode->setItemText(2, QCoreApplication::translate("cDockNavigation", "Move target", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_camera_movement_mode->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Selection of camera / target movement mode</p><p><span style=\" font-style:italic;\">Move camera and target</span> - moves camera and target by the same distance</p><p><img src=\":/tooltips/tooltips_images/move camera and target.png\"/></p><p><span style=\" font-style:italic;\">Move camera</span> - moves only camera. Target stays in the same place. Camera rotates to look at stationary target.</p><p><img src=\":/tooltips/tooltips_images/move only camera.png\"/></p><p><br/>Move target - moves only target. Camera stays in the same place. Camera rotates to look at moving target.</p><p><img src=\":/tooltips/tooltips_images/move only target.png\"/></p><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_124->setText(QCoreApplication::translate("cDockNavigation", "Camera distance\n"
"to target:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_camera_distance_to_target->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Controls distance between camera and target</p><p>In<span style=\" font-style:italic;\"> Move camera and target</span> and <span style=\" font-style:italic;\">Move camera</span> modes it moves camera closer/further from target.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        bu_move_forward->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Moves the camera or the target forward by distance set by <span style=\" font-style:italic;\">step</span> parameter</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        bu_move_forward->setText(QString());
#if QT_CONFIG(tooltip)
        bu_move_backward->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Moves the camera or the target backwards by distance set by <span style=\" font-style:italic;\">step</span> parameter</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        bu_move_backward->setText(QString());
#if QT_CONFIG(tooltip)
        bu_move_left->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Moves the camera or the target to the left by distance set by <span style=\" font-style:italic;\">step</span> parameter</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        bu_move_left->setText(QString());
#if QT_CONFIG(tooltip)
        bu_move_up->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Moves the camera or the target up by distance set by <span style=\" font-style:italic;\">step</span> parameter</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        bu_move_up->setText(QString());
#if QT_CONFIG(tooltip)
        bu_move_down->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Moves the camera or the target down by distance set by <span style=\" font-style:italic;\">step</span> parameter</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        bu_move_down->setText(QString());
#if QT_CONFIG(tooltip)
        bu_move_right->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Moves the camera or the target to the right by distance set by <span style=\" font-style:italic;\">step</span> parameter</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        bu_move_right->setText(QString());
        label_9->setText(QCoreApplication::translate("cDockNavigation", "step:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_camera_movement_step->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Step for camera or target movement.</p><p>It can be relative or absolute step.</p><p>If it is set relative then movement distance equals <span style=\" font-style:italic;\">step</span> multiplied by actual distance to the fractal surface.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_camera_absolute_distance_mode->setItemText(0, QCoreApplication::translate("cDockNavigation", "Relative step mode", nullptr));
        comboBox_camera_absolute_distance_mode->setItemText(1, QCoreApplication::translate("cDockNavigation", "Absolute step mode", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_camera_absolute_distance_mode->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Selection for movement step calculation.</p><p>If it is set relative then movement distance equals  <span style=\" font-style:italic;\">step</span> multiplied by actual distance to fractal surface. This is the preferred mode.</p><p>If it is set absolute then movement equals step set by <span style=\" font-style:italic;\">step</span> parameter. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        groupBox_rotation->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Controls for camera rotation in three different axes</p><p><img src=\":/tooltips/tooltips_images/Yaw_Pich_Roll.png\"/></p><p>image source: &quot;<a href=\"http://commons.wikimedia.org/wiki/File:Yaw_Axis_Corrected.svg#/media/File:Yaw_Axis_Corrected.svg\"><span style=\" text-decoration: underline; color:#ae6326;\">Yaw Axis Corrected</span></a>&quot; by <a href=\"//commons.wikimedia.org/wiki/File:Yaw_Axis.svg\"><span style=\" text-decoration: underline; color:#ae6326;\">Yaw_Axis.svg</span></a>: <a href=\"//commons.wikimedia.org/wiki/User:Auawise\"><span style=\" text-decoration: underline; color:#ae6326;\">Auawise</span></a>derivative work: <a href=\"//commons.wikimedia.org/w/index.php?title=User:Jrvz&amp;action=edit&amp;redlink=1\"><span style=\" text-decoration: underline; color:#ae6326;\">Jrvz</span></a> (<a href=\"//commons.wikimedia.org/w/index.php?title=User_talk:Jrvz&amp;action=edit&amp;redlink=1\"><span style=\" text-decoration: underline; color:#ae6326;\">talk</span></a>) - <a href="
                        "\"//commons.wikimedia.org/wiki/File:Yaw_Axis.svg\"><span style=\" text-decoration: underline; color:#ae6326;\">Yaw_Axis.svg</span></a>. Licensed under <a href=\"http://creativecommons.org/licenses/by-sa/3.0\"><span style=\" text-decoration: underline; color:#ae6326;\">CC BY-SA 3.0</span></a> via <a href=\"//commons.wikimedia.org/wiki/\"><span style=\" text-decoration: underline; color:#ae6326;\">Wikimedia Commons</span></a>.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_rotation->setTitle(QCoreApplication::translate("cDockNavigation", "Camera rotation:", nullptr));
#if QT_CONFIG(tooltip)
        bu_rotate_roll_left->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Roll left</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        bu_rotate_roll_left->setText(QString());
#if QT_CONFIG(tooltip)
        bu_rotate_up->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Pitch up</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        bu_rotate_up->setText(QString());
#if QT_CONFIG(tooltip)
        bu_rotate_roll_right->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Roll right</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        bu_rotate_roll_right->setText(QString());
#if QT_CONFIG(tooltip)
        bu_rotate_left->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Yaw left</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        bu_rotate_left->setText(QString());
#if QT_CONFIG(tooltip)
        bu_rotate_down->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Pitch down</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        bu_rotate_down->setText(QString());
#if QT_CONFIG(tooltip)
        bu_rotate_right->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Yaw right</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        bu_rotate_right->setText(QString());
        label_125->setText(QCoreApplication::translate("cDockNavigation", "rotation step:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_camera_rotation_step->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Step of rotation in degrees</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_camera_rotation_step->setPrefix(QString());
        spinbox_camera_rotation_step->setSuffix(QString());
        comboBox_camera_rotation_mode->setItemText(0, QCoreApplication::translate("cDockNavigation", "Rotate camera", nullptr));
        comboBox_camera_rotation_mode->setItemText(1, QCoreApplication::translate("cDockNavigation", "Rotate around target", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_camera_rotation_mode->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Modes of camera rotation</p><p><span style=\" font-style:italic;\">Rotate camera</span> - rotates the camera by moving the target around the camera</p><p><img src=\":/tooltips/tooltips_images/rotate target around camera.png\"/></p><p>Rotate around target - rotates the camera by moving camera around the target</p><p><img src=\":/tooltips/tooltips_images/rotate camera around target.png\"/></p><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_camera_straight_rotation->setItemText(0, QCoreApplication::translate("cDockNavigation", "Fixed roll angle", nullptr));
        comboBox_camera_straight_rotation->setItemText(1, QCoreApplication::translate("cDockNavigation", "Straight rotation", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_camera_straight_rotation->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Selection for rotation modes</p><p>Fixed roll angle - rotates camera using world axes. This mode does not change the roll angle but can be difficult to predict when camera is upside down or almost in vertical orientation.</p><p>Straight rotation - rotates camera using actual camera axes. This mode rotates camera in a more intuitive way.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_15->setText(QCoreApplication::translate("cDockNavigation", "yaw:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_camera_rotation_x->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Rotation of camera around yaw axis (left &lt;-&gt; right)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_16->setText(QCoreApplication::translate("cDockNavigation", "pitch:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_camera_rotation_y->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Rotation of camera around pitch axis (up &lt;-&gt; down)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_17->setText(QCoreApplication::translate("cDockNavigation", "roll:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_camera_rotation_z->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Rotation of camera around roll axis (rotates image left &lt;-&gt; right)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        groupBox_11->setToolTip(QCoreApplication::translate("cDockNavigation", "<html><head/><body><p>Sweet spot position used especially for fulldome images or animations.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_11->setTitle(QCoreApplication::translate("cDockNavigation", "Sweet spot angle:", nullptr));
        spinboxd_sweet_spot_horizontal_angle->setPrefix(QString());
        spinboxd_sweet_spot_horizontal_angle->setSuffix(QString());
        spinboxd_sweet_spot_vertical_angle->setPrefix(QString());
        spinboxd_sweet_spot_vertical_angle->setSuffix(QString());
        label_293->setText(QCoreApplication::translate("cDockNavigation", "horizontal:", nullptr));
        label_294->setText(QCoreApplication::translate("cDockNavigation", "vertical:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cDockNavigation: public Ui_cDockNavigation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCK_NAVIGATION_H
