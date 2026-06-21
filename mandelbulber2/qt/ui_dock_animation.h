/********************************************************************************
** Form generated from reading UI file 'dock_animation.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCK_ANIMATION_H
#define UI_DOCK_ANIMATION_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "animation_value_chart_widget.h"
#include "my_check_box.h"
#include "my_combo_box.h"
#include "my_double_spin_box.h"
#include "my_line_edit.h"
#include "my_spin_box.h"
#include "my_table_widget_anim.hpp"
#include "my_table_widget_keyframes.hpp"

QT_BEGIN_NAMESPACE

class Ui_cDockAnimation
{
public:
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidgetFlightKeyframe;
    QWidget *tab_flight_animation;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout_flight_animtion;
    QGridLayout *gridLayout_39;
    QPushButton *pushButton_render_flight;
    QPushButton *pushButton_record_flight;
    QPushButton *pushButton_delete_all_images;
    QPushButton *pushButton_show_animation;
    QPushButton *pushButton_continue_recording;
    QPushButton *pushButton_flight_refresh_table;
    QPushButton *pushButton_flight_to_keyframe_export;
    QScrollArea *scrollArea_flight_animation_parameters;
    QWidget *scrollAreaWidgetContents_flightAnimationParameters;
    QVBoxLayout *verticalLayout_79;
    QGridLayout *gridLayout_38;
    QLabel *label_path_for_images;
    QLabel *label_image_type;
    QLabel *label_147;
    QLabel *label_146;
    MyLineEdit *text_anim_flight_dir;
    MyComboBox *comboBox_flight_speed_control;
    QLabel *label_148;
    QPushButton *button_selectAnimFlightImageDir;
    QLabel *label_151;
    QLabel *label_153;
    MyCheckBox *checkBox_flight_show_thumbnails;
    QLabel *label_152;
    MyCheckBox *checkBox_flight_add_speeds;
    MyComboBox *comboBox_flight_animation_image_type;
    QLabel *label_218;
    QLabel *label_220;
    MyLineEdit *logedit_flight_speed;
    MyDoubleSpinBox *spinbox_flight_inertia;
    MyDoubleSpinBox *spinbox_flight_rotation_speed;
    MyDoubleSpinBox *spinbox_flight_roll_speed;
    MySpinBox *spinboxInt_flight_first_to_render;
    MySpinBox *spinboxInt_flight_last_to_render;
    MyDoubleSpinBox *spinbox_flight_sec_per_frame;
    QSpacerItem *verticalSpacer_11;
    QVBoxLayout *verticalLayout_table;
    MyTableWidgetAnim *tableWidget_flightAnimation;
    QWidget *tab_keyframe_animation;
    QHBoxLayout *horizontalLayout_15;
    QVBoxLayout *verticalLayout_flight_animtion_2;
    QGridLayout *gridLayout_keyframe_animation_parameters;
    QPushButton *pushButton_insert_keyframe;
    QPushButton *pushButton_delete_keyframe;
    QPushButton *pushButton_add_keyframe;
    QPushButton *pushButton_show_keyframe_animation;
    QPushButton *pushButton_render_keyframe_animation;
    QPushButton *pushButton_modify_keyframe;
    QPushButton *pushButton_keyframe_to_flight_export;
    QPushButton *pushButton_delete_all_keyframe_images;
    QPushButton *pushButton_refresh_keyframe_table;
    QPushButton *pushButton_check_for_collisions;
    QPushButton *pushButton_randomize;
    QPushButton *pushButton_add_all_parameters;
    QScrollArea *scrollArea_keyframe_animation_parameters;
    QWidget *scrollAreaWidgetContents_keyframeAnimationParameters;
    QVBoxLayout *verticalLayout_92;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_camera_distance_from_keyframe;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_52;
    QLabel *label_177;
    MySpinBox *spinboxInt_frames_per_keyframe;
    MyDoubleSpinBox *spinbox_keyframe_frames_per_second;
    QLabel *label_217;
    MySpinBox *spinboxInt_keyframe_last_to_render;
    QLabel *label_222;
    QLabel *label_219;
    MyComboBox *comboBox_keyframe_animation_image_type;
    QPushButton *button_selectAnimKeyframeImageDir;
    QLabel *label_150;
    MySpinBox *spinboxInt_keyframe_first_to_render;
    QLabel *label_213;
    MyLineEdit *text_anim_keyframe_dir;
    QPushButton *pushButton_set_frames_per_keyframe_to_all;
    MyCheckBox *checkBox_keyframe_animation_loop;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    MyCheckBox *checkBox_keyframe_auto_validate;
    QGridLayout *gridLayout;
    MyLineEdit *logedit_keyframe_collision_thresh;
    QLabel *label_221;
    QPushButton *pushButton_set_constant_target_distance;
    MyLineEdit *logedit_keyframe_constant_target_distance;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    MyCheckBox *checkBox_show_keyframe_thumbnails;
    MyCheckBox *checkBox_show_camera_path;
    MyCheckBox *checkBox_show_target_path;
    MyCheckBox *checkBox_show_light_path_1;
    MyCheckBox *checkBox_show_light_path_2;
    MyCheckBox *checkBox_show_light_path_3;
    MyCheckBox *checkBox_show_light_path_4;
    QSpacerItem *verticalSpacer_13;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *toolButton_previousFrame;
    QToolButton *toolButton_next_frame;
    QLabel *label_actualFrame;
    QSlider *horizontalSlider_actualFrame;
    QHBoxLayout *horizontalLayout_3;
    QGridLayout *gridLayout_2;
    QToolButton *toolButton_chartZoomIn;
    QToolButton *toolButton_chartZoomOut;
    cAnimationValueChartWidget *widgetValueChart;
    MyTableWidgetKeyframes *tableWidget_keyframe_animation;

    void setupUi(QWidget *cDockAnimation)
    {
        if (cDockAnimation->objectName().isEmpty())
            cDockAnimation->setObjectName(QString::fromUtf8("cDockAnimation"));
        cDockAnimation->resize(1443, 806);
        horizontalLayout = new QHBoxLayout(cDockAnimation);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        tabWidgetFlightKeyframe = new QTabWidget(cDockAnimation);
        tabWidgetFlightKeyframe->setObjectName(QString::fromUtf8("tabWidgetFlightKeyframe"));
        tab_flight_animation = new QWidget();
        tab_flight_animation->setObjectName(QString::fromUtf8("tab_flight_animation"));
        horizontalLayout_12 = new QHBoxLayout(tab_flight_animation);
        horizontalLayout_12->setSpacing(2);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(2, 2, 2, 2);
        verticalLayout_flight_animtion = new QVBoxLayout();
        verticalLayout_flight_animtion->setSpacing(2);
        verticalLayout_flight_animtion->setObjectName(QString::fromUtf8("verticalLayout_flight_animtion"));
        gridLayout_39 = new QGridLayout();
        gridLayout_39->setSpacing(2);
        gridLayout_39->setObjectName(QString::fromUtf8("gridLayout_39"));
        gridLayout_39->setContentsMargins(0, 0, 0, 0);
        pushButton_render_flight = new QPushButton(tab_flight_animation);
        pushButton_render_flight->setObjectName(QString::fromUtf8("pushButton_render_flight"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_render_flight->sizePolicy().hasHeightForWidth());
        pushButton_render_flight->setSizePolicy(sizePolicy);
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("video-x-generic");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8(":/system/icons/video-x-generic.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_render_flight->setIcon(icon);

        gridLayout_39->addWidget(pushButton_render_flight, 0, 0, 1, 1);

        pushButton_record_flight = new QPushButton(tab_flight_animation);
        pushButton_record_flight->setObjectName(QString::fromUtf8("pushButton_record_flight"));
        sizePolicy.setHeightForWidth(pushButton_record_flight->sizePolicy().hasHeightForWidth());
        pushButton_record_flight->setSizePolicy(sizePolicy);
        QIcon icon1;
        iconThemeName = QString::fromUtf8("media-record");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8(":/system/icons/media-record.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_record_flight->setIcon(icon1);

        gridLayout_39->addWidget(pushButton_record_flight, 0, 1, 1, 1);

        pushButton_delete_all_images = new QPushButton(tab_flight_animation);
        pushButton_delete_all_images->setObjectName(QString::fromUtf8("pushButton_delete_all_images"));
        sizePolicy.setHeightForWidth(pushButton_delete_all_images->sizePolicy().hasHeightForWidth());
        pushButton_delete_all_images->setSizePolicy(sizePolicy);
        QIcon icon2;
        iconThemeName = QString::fromUtf8("edit-delete");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QString::fromUtf8(":/system/icons/edit-delete.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_delete_all_images->setIcon(icon2);

        gridLayout_39->addWidget(pushButton_delete_all_images, 1, 1, 1, 1);

        pushButton_show_animation = new QPushButton(tab_flight_animation);
        pushButton_show_animation->setObjectName(QString::fromUtf8("pushButton_show_animation"));
        sizePolicy.setHeightForWidth(pushButton_show_animation->sizePolicy().hasHeightForWidth());
        pushButton_show_animation->setSizePolicy(sizePolicy);
        QIcon icon3;
        iconThemeName = QString::fromUtf8("media-playback-start");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon3 = QIcon::fromTheme(iconThemeName);
        } else {
            icon3.addFile(QString::fromUtf8(":/system/icons/media-playback-start.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_show_animation->setIcon(icon3);

        gridLayout_39->addWidget(pushButton_show_animation, 1, 0, 1, 1);

        pushButton_continue_recording = new QPushButton(tab_flight_animation);
        pushButton_continue_recording->setObjectName(QString::fromUtf8("pushButton_continue_recording"));
        sizePolicy.setHeightForWidth(pushButton_continue_recording->sizePolicy().hasHeightForWidth());
        pushButton_continue_recording->setSizePolicy(sizePolicy);
        pushButton_continue_recording->setIcon(icon1);

        gridLayout_39->addWidget(pushButton_continue_recording, 0, 2, 1, 1);

        pushButton_flight_refresh_table = new QPushButton(tab_flight_animation);
        pushButton_flight_refresh_table->setObjectName(QString::fromUtf8("pushButton_flight_refresh_table"));
        sizePolicy.setHeightForWidth(pushButton_flight_refresh_table->sizePolicy().hasHeightForWidth());
        pushButton_flight_refresh_table->setSizePolicy(sizePolicy);
        QIcon icon4;
        iconThemeName = QString::fromUtf8("view-refresh");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon4 = QIcon::fromTheme(iconThemeName);
        } else {
            icon4.addFile(QString::fromUtf8(":/system/icons/view-refresh.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_flight_refresh_table->setIcon(icon4);

        gridLayout_39->addWidget(pushButton_flight_refresh_table, 1, 2, 1, 1);

        pushButton_flight_to_keyframe_export = new QPushButton(tab_flight_animation);
        pushButton_flight_to_keyframe_export->setObjectName(QString::fromUtf8("pushButton_flight_to_keyframe_export"));
        sizePolicy.setHeightForWidth(pushButton_flight_to_keyframe_export->sizePolicy().hasHeightForWidth());
        pushButton_flight_to_keyframe_export->setSizePolicy(sizePolicy);

        gridLayout_39->addWidget(pushButton_flight_to_keyframe_export, 2, 0, 1, 1);


        verticalLayout_flight_animtion->addLayout(gridLayout_39);

        scrollArea_flight_animation_parameters = new QScrollArea(tab_flight_animation);
        scrollArea_flight_animation_parameters->setObjectName(QString::fromUtf8("scrollArea_flight_animation_parameters"));
        scrollArea_flight_animation_parameters->setWidgetResizable(true);
        scrollAreaWidgetContents_flightAnimationParameters = new QWidget();
        scrollAreaWidgetContents_flightAnimationParameters->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_flightAnimationParameters"));
        scrollAreaWidgetContents_flightAnimationParameters->setGeometry(QRect(0, 0, 477, 682));
        verticalLayout_79 = new QVBoxLayout(scrollAreaWidgetContents_flightAnimationParameters);
        verticalLayout_79->setObjectName(QString::fromUtf8("verticalLayout_79"));
        verticalLayout_79->setContentsMargins(2, 2, 2, 2);
        gridLayout_38 = new QGridLayout();
        gridLayout_38->setSpacing(2);
        gridLayout_38->setObjectName(QString::fromUtf8("gridLayout_38"));
        label_path_for_images = new QLabel(scrollAreaWidgetContents_flightAnimationParameters);
        label_path_for_images->setObjectName(QString::fromUtf8("label_path_for_images"));

        gridLayout_38->addWidget(label_path_for_images, 6, 0, 1, 1);

        label_image_type = new QLabel(scrollAreaWidgetContents_flightAnimationParameters);
        label_image_type->setObjectName(QString::fromUtf8("label_image_type"));

        gridLayout_38->addWidget(label_image_type, 7, 0, 1, 1);

        label_147 = new QLabel(scrollAreaWidgetContents_flightAnimationParameters);
        label_147->setObjectName(QString::fromUtf8("label_147"));

        gridLayout_38->addWidget(label_147, 1, 0, 1, 1);

        label_146 = new QLabel(scrollAreaWidgetContents_flightAnimationParameters);
        label_146->setObjectName(QString::fromUtf8("label_146"));

        gridLayout_38->addWidget(label_146, 0, 0, 1, 1);

        text_anim_flight_dir = new MyLineEdit(scrollAreaWidgetContents_flightAnimationParameters);
        text_anim_flight_dir->setObjectName(QString::fromUtf8("text_anim_flight_dir"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(text_anim_flight_dir->sizePolicy().hasHeightForWidth());
        text_anim_flight_dir->setSizePolicy(sizePolicy1);

        gridLayout_38->addWidget(text_anim_flight_dir, 6, 1, 1, 1);

        comboBox_flight_speed_control = new MyComboBox(scrollAreaWidgetContents_flightAnimationParameters);
        comboBox_flight_speed_control->addItem(QString());
        comboBox_flight_speed_control->addItem(QString());
        comboBox_flight_speed_control->setObjectName(QString::fromUtf8("comboBox_flight_speed_control"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(comboBox_flight_speed_control->sizePolicy().hasHeightForWidth());
        comboBox_flight_speed_control->setSizePolicy(sizePolicy2);

        gridLayout_38->addWidget(comboBox_flight_speed_control, 4, 1, 1, 2);

        label_148 = new QLabel(scrollAreaWidgetContents_flightAnimationParameters);
        label_148->setObjectName(QString::fromUtf8("label_148"));

        gridLayout_38->addWidget(label_148, 4, 0, 1, 1);

        button_selectAnimFlightImageDir = new QPushButton(scrollAreaWidgetContents_flightAnimationParameters);
        button_selectAnimFlightImageDir->setObjectName(QString::fromUtf8("button_selectAnimFlightImageDir"));
        sizePolicy.setHeightForWidth(button_selectAnimFlightImageDir->sizePolicy().hasHeightForWidth());
        button_selectAnimFlightImageDir->setSizePolicy(sizePolicy);

        gridLayout_38->addWidget(button_selectAnimFlightImageDir, 6, 2, 1, 1);

        label_151 = new QLabel(scrollAreaWidgetContents_flightAnimationParameters);
        label_151->setObjectName(QString::fromUtf8("label_151"));

        gridLayout_38->addWidget(label_151, 5, 0, 1, 1);

        label_153 = new QLabel(scrollAreaWidgetContents_flightAnimationParameters);
        label_153->setObjectName(QString::fromUtf8("label_153"));

        gridLayout_38->addWidget(label_153, 3, 0, 1, 1);

        checkBox_flight_show_thumbnails = new MyCheckBox(scrollAreaWidgetContents_flightAnimationParameters);
        checkBox_flight_show_thumbnails->setObjectName(QString::fromUtf8("checkBox_flight_show_thumbnails"));
        sizePolicy.setHeightForWidth(checkBox_flight_show_thumbnails->sizePolicy().hasHeightForWidth());
        checkBox_flight_show_thumbnails->setSizePolicy(sizePolicy);

        gridLayout_38->addWidget(checkBox_flight_show_thumbnails, 10, 0, 1, 3);

        label_152 = new QLabel(scrollAreaWidgetContents_flightAnimationParameters);
        label_152->setObjectName(QString::fromUtf8("label_152"));

        gridLayout_38->addWidget(label_152, 2, 0, 1, 1);

        checkBox_flight_add_speeds = new MyCheckBox(scrollAreaWidgetContents_flightAnimationParameters);
        checkBox_flight_add_speeds->setObjectName(QString::fromUtf8("checkBox_flight_add_speeds"));
        sizePolicy.setHeightForWidth(checkBox_flight_add_speeds->sizePolicy().hasHeightForWidth());
        checkBox_flight_add_speeds->setSizePolicy(sizePolicy);

        gridLayout_38->addWidget(checkBox_flight_add_speeds, 11, 0, 1, 3);

        comboBox_flight_animation_image_type = new MyComboBox(scrollAreaWidgetContents_flightAnimationParameters);
        comboBox_flight_animation_image_type->addItem(QString());
        comboBox_flight_animation_image_type->addItem(QString());
        comboBox_flight_animation_image_type->addItem(QString());
        comboBox_flight_animation_image_type->addItem(QString());
        comboBox_flight_animation_image_type->setObjectName(QString::fromUtf8("comboBox_flight_animation_image_type"));
        sizePolicy2.setHeightForWidth(comboBox_flight_animation_image_type->sizePolicy().hasHeightForWidth());
        comboBox_flight_animation_image_type->setSizePolicy(sizePolicy2);

        gridLayout_38->addWidget(comboBox_flight_animation_image_type, 7, 1, 1, 2);

        label_218 = new QLabel(scrollAreaWidgetContents_flightAnimationParameters);
        label_218->setObjectName(QString::fromUtf8("label_218"));

        gridLayout_38->addWidget(label_218, 8, 0, 1, 1);

        label_220 = new QLabel(scrollAreaWidgetContents_flightAnimationParameters);
        label_220->setObjectName(QString::fromUtf8("label_220"));

        gridLayout_38->addWidget(label_220, 9, 0, 1, 1);

        logedit_flight_speed = new MyLineEdit(scrollAreaWidgetContents_flightAnimationParameters);
        logedit_flight_speed->setObjectName(QString::fromUtf8("logedit_flight_speed"));
        sizePolicy1.setHeightForWidth(logedit_flight_speed->sizePolicy().hasHeightForWidth());
        logedit_flight_speed->setSizePolicy(sizePolicy1);

        gridLayout_38->addWidget(logedit_flight_speed, 0, 1, 1, 2);

        spinbox_flight_inertia = new MyDoubleSpinBox(scrollAreaWidgetContents_flightAnimationParameters);
        spinbox_flight_inertia->setObjectName(QString::fromUtf8("spinbox_flight_inertia"));
        sizePolicy.setHeightForWidth(spinbox_flight_inertia->sizePolicy().hasHeightForWidth());
        spinbox_flight_inertia->setSizePolicy(sizePolicy);
        spinbox_flight_inertia->setDecimals(2);
        spinbox_flight_inertia->setMaximum(1000.000000000000000);
        spinbox_flight_inertia->setSingleStep(0.100000000000000);

        gridLayout_38->addWidget(spinbox_flight_inertia, 1, 1, 1, 2);

        spinbox_flight_rotation_speed = new MyDoubleSpinBox(scrollAreaWidgetContents_flightAnimationParameters);
        spinbox_flight_rotation_speed->setObjectName(QString::fromUtf8("spinbox_flight_rotation_speed"));
        sizePolicy.setHeightForWidth(spinbox_flight_rotation_speed->sizePolicy().hasHeightForWidth());
        spinbox_flight_rotation_speed->setSizePolicy(sizePolicy);
        spinbox_flight_rotation_speed->setDecimals(2);
        spinbox_flight_rotation_speed->setMaximum(1000.000000000000000);
        spinbox_flight_rotation_speed->setSingleStep(0.100000000000000);

        gridLayout_38->addWidget(spinbox_flight_rotation_speed, 2, 1, 1, 2);

        spinbox_flight_roll_speed = new MyDoubleSpinBox(scrollAreaWidgetContents_flightAnimationParameters);
        spinbox_flight_roll_speed->setObjectName(QString::fromUtf8("spinbox_flight_roll_speed"));
        sizePolicy.setHeightForWidth(spinbox_flight_roll_speed->sizePolicy().hasHeightForWidth());
        spinbox_flight_roll_speed->setSizePolicy(sizePolicy);
        spinbox_flight_roll_speed->setDecimals(2);
        spinbox_flight_roll_speed->setMaximum(1000.000000000000000);
        spinbox_flight_roll_speed->setSingleStep(0.100000000000000);

        gridLayout_38->addWidget(spinbox_flight_roll_speed, 3, 1, 1, 2);

        spinboxInt_flight_first_to_render = new MySpinBox(scrollAreaWidgetContents_flightAnimationParameters);
        spinboxInt_flight_first_to_render->setObjectName(QString::fromUtf8("spinboxInt_flight_first_to_render"));
        sizePolicy.setHeightForWidth(spinboxInt_flight_first_to_render->sizePolicy().hasHeightForWidth());
        spinboxInt_flight_first_to_render->setSizePolicy(sizePolicy);
        spinboxInt_flight_first_to_render->setMinimum(0);
        spinboxInt_flight_first_to_render->setMaximum(99999);
        spinboxInt_flight_first_to_render->setSingleStep(1);
        spinboxInt_flight_first_to_render->setValue(0);

        gridLayout_38->addWidget(spinboxInt_flight_first_to_render, 8, 1, 1, 2);

        spinboxInt_flight_last_to_render = new MySpinBox(scrollAreaWidgetContents_flightAnimationParameters);
        spinboxInt_flight_last_to_render->setObjectName(QString::fromUtf8("spinboxInt_flight_last_to_render"));
        sizePolicy.setHeightForWidth(spinboxInt_flight_last_to_render->sizePolicy().hasHeightForWidth());
        spinboxInt_flight_last_to_render->setSizePolicy(sizePolicy);
        spinboxInt_flight_last_to_render->setMinimum(0);
        spinboxInt_flight_last_to_render->setMaximum(99999);
        spinboxInt_flight_last_to_render->setSingleStep(1);
        spinboxInt_flight_last_to_render->setValue(0);

        gridLayout_38->addWidget(spinboxInt_flight_last_to_render, 9, 1, 1, 2);

        spinbox_flight_sec_per_frame = new MyDoubleSpinBox(scrollAreaWidgetContents_flightAnimationParameters);
        spinbox_flight_sec_per_frame->setObjectName(QString::fromUtf8("spinbox_flight_sec_per_frame"));
        sizePolicy.setHeightForWidth(spinbox_flight_sec_per_frame->sizePolicy().hasHeightForWidth());
        spinbox_flight_sec_per_frame->setSizePolicy(sizePolicy);
        spinbox_flight_sec_per_frame->setDecimals(2);
        spinbox_flight_sec_per_frame->setMinimum(0.010000000000000);
        spinbox_flight_sec_per_frame->setMaximum(100.000000000000000);
        spinbox_flight_sec_per_frame->setSingleStep(0.100000000000000);

        gridLayout_38->addWidget(spinbox_flight_sec_per_frame, 5, 1, 1, 2);


        verticalLayout_79->addLayout(gridLayout_38);

        verticalSpacer_11 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_79->addItem(verticalSpacer_11);

        scrollArea_flight_animation_parameters->setWidget(scrollAreaWidgetContents_flightAnimationParameters);

        verticalLayout_flight_animtion->addWidget(scrollArea_flight_animation_parameters);


        horizontalLayout_12->addLayout(verticalLayout_flight_animtion);

        verticalLayout_table = new QVBoxLayout();
        verticalLayout_table->setSpacing(2);
        verticalLayout_table->setObjectName(QString::fromUtf8("verticalLayout_table"));
        tableWidget_flightAnimation = new MyTableWidgetAnim(tab_flight_animation);
        tableWidget_flightAnimation->setObjectName(QString::fromUtf8("tableWidget_flightAnimation"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(3);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(tableWidget_flightAnimation->sizePolicy().hasHeightForWidth());
        tableWidget_flightAnimation->setSizePolicy(sizePolicy3);
        tableWidget_flightAnimation->verticalHeader()->setDefaultSectionSize(22);

        verticalLayout_table->addWidget(tableWidget_flightAnimation);


        horizontalLayout_12->addLayout(verticalLayout_table);

        horizontalLayout_12->setStretch(1, 3);
        tabWidgetFlightKeyframe->addTab(tab_flight_animation, QString());
        tab_keyframe_animation = new QWidget();
        tab_keyframe_animation->setObjectName(QString::fromUtf8("tab_keyframe_animation"));
        horizontalLayout_15 = new QHBoxLayout(tab_keyframe_animation);
        horizontalLayout_15->setSpacing(2);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        horizontalLayout_15->setContentsMargins(2, 2, 2, 2);
        verticalLayout_flight_animtion_2 = new QVBoxLayout();
        verticalLayout_flight_animtion_2->setSpacing(2);
        verticalLayout_flight_animtion_2->setObjectName(QString::fromUtf8("verticalLayout_flight_animtion_2"));
        gridLayout_keyframe_animation_parameters = new QGridLayout();
        gridLayout_keyframe_animation_parameters->setSpacing(2);
        gridLayout_keyframe_animation_parameters->setObjectName(QString::fromUtf8("gridLayout_keyframe_animation_parameters"));
        gridLayout_keyframe_animation_parameters->setContentsMargins(0, 0, 0, 0);
        pushButton_insert_keyframe = new QPushButton(tab_keyframe_animation);
        pushButton_insert_keyframe->setObjectName(QString::fromUtf8("pushButton_insert_keyframe"));
        sizePolicy.setHeightForWidth(pushButton_insert_keyframe->sizePolicy().hasHeightForWidth());
        pushButton_insert_keyframe->setSizePolicy(sizePolicy);
        pushButton_insert_keyframe->setIcon(icon1);

        gridLayout_keyframe_animation_parameters->addWidget(pushButton_insert_keyframe, 1, 1, 1, 1);

        pushButton_delete_keyframe = new QPushButton(tab_keyframe_animation);
        pushButton_delete_keyframe->setObjectName(QString::fromUtf8("pushButton_delete_keyframe"));
        sizePolicy.setHeightForWidth(pushButton_delete_keyframe->sizePolicy().hasHeightForWidth());
        pushButton_delete_keyframe->setSizePolicy(sizePolicy);
        pushButton_delete_keyframe->setIcon(icon1);

        gridLayout_keyframe_animation_parameters->addWidget(pushButton_delete_keyframe, 1, 3, 1, 1);

        pushButton_add_keyframe = new QPushButton(tab_keyframe_animation);
        pushButton_add_keyframe->setObjectName(QString::fromUtf8("pushButton_add_keyframe"));
        sizePolicy.setHeightForWidth(pushButton_add_keyframe->sizePolicy().hasHeightForWidth());
        pushButton_add_keyframe->setSizePolicy(sizePolicy);
        pushButton_add_keyframe->setIcon(icon1);

        gridLayout_keyframe_animation_parameters->addWidget(pushButton_add_keyframe, 1, 2, 1, 1);

        pushButton_show_keyframe_animation = new QPushButton(tab_keyframe_animation);
        pushButton_show_keyframe_animation->setObjectName(QString::fromUtf8("pushButton_show_keyframe_animation"));
        sizePolicy.setHeightForWidth(pushButton_show_keyframe_animation->sizePolicy().hasHeightForWidth());
        pushButton_show_keyframe_animation->setSizePolicy(sizePolicy);
        pushButton_show_keyframe_animation->setIcon(icon3);

        gridLayout_keyframe_animation_parameters->addWidget(pushButton_show_keyframe_animation, 3, 1, 1, 1);

        pushButton_render_keyframe_animation = new QPushButton(tab_keyframe_animation);
        pushButton_render_keyframe_animation->setObjectName(QString::fromUtf8("pushButton_render_keyframe_animation"));
        sizePolicy.setHeightForWidth(pushButton_render_keyframe_animation->sizePolicy().hasHeightForWidth());
        pushButton_render_keyframe_animation->setSizePolicy(sizePolicy);
        pushButton_render_keyframe_animation->setIcon(icon);

        gridLayout_keyframe_animation_parameters->addWidget(pushButton_render_keyframe_animation, 0, 1, 1, 1);

        pushButton_modify_keyframe = new QPushButton(tab_keyframe_animation);
        pushButton_modify_keyframe->setObjectName(QString::fromUtf8("pushButton_modify_keyframe"));
        sizePolicy.setHeightForWidth(pushButton_modify_keyframe->sizePolicy().hasHeightForWidth());
        pushButton_modify_keyframe->setSizePolicy(sizePolicy);
        pushButton_modify_keyframe->setIcon(icon1);

        gridLayout_keyframe_animation_parameters->addWidget(pushButton_modify_keyframe, 2, 1, 1, 1);

        pushButton_keyframe_to_flight_export = new QPushButton(tab_keyframe_animation);
        pushButton_keyframe_to_flight_export->setObjectName(QString::fromUtf8("pushButton_keyframe_to_flight_export"));
        sizePolicy.setHeightForWidth(pushButton_keyframe_to_flight_export->sizePolicy().hasHeightForWidth());
        pushButton_keyframe_to_flight_export->setSizePolicy(sizePolicy);

        gridLayout_keyframe_animation_parameters->addWidget(pushButton_keyframe_to_flight_export, 3, 3, 1, 1);

        pushButton_delete_all_keyframe_images = new QPushButton(tab_keyframe_animation);
        pushButton_delete_all_keyframe_images->setObjectName(QString::fromUtf8("pushButton_delete_all_keyframe_images"));
        sizePolicy.setHeightForWidth(pushButton_delete_all_keyframe_images->sizePolicy().hasHeightForWidth());
        pushButton_delete_all_keyframe_images->setSizePolicy(sizePolicy);
        pushButton_delete_all_keyframe_images->setIcon(icon2);

        gridLayout_keyframe_animation_parameters->addWidget(pushButton_delete_all_keyframe_images, 3, 2, 1, 1);

        pushButton_refresh_keyframe_table = new QPushButton(tab_keyframe_animation);
        pushButton_refresh_keyframe_table->setObjectName(QString::fromUtf8("pushButton_refresh_keyframe_table"));
        sizePolicy.setHeightForWidth(pushButton_refresh_keyframe_table->sizePolicy().hasHeightForWidth());
        pushButton_refresh_keyframe_table->setSizePolicy(sizePolicy);
        pushButton_refresh_keyframe_table->setIcon(icon4);

        gridLayout_keyframe_animation_parameters->addWidget(pushButton_refresh_keyframe_table, 0, 3, 1, 1);

        pushButton_check_for_collisions = new QPushButton(tab_keyframe_animation);
        pushButton_check_for_collisions->setObjectName(QString::fromUtf8("pushButton_check_for_collisions"));
        sizePolicy.setHeightForWidth(pushButton_check_for_collisions->sizePolicy().hasHeightForWidth());
        pushButton_check_for_collisions->setSizePolicy(sizePolicy);
        QIcon icon5;
        iconThemeName = QString::fromUtf8("dialog-ok-apply");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon5 = QIcon::fromTheme(iconThemeName);
        } else {
            icon5.addFile(QString::fromUtf8(":/system/icons/video-x-generic.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_check_for_collisions->setIcon(icon5);

        gridLayout_keyframe_animation_parameters->addWidget(pushButton_check_for_collisions, 0, 2, 1, 1);

        pushButton_randomize = new QPushButton(tab_keyframe_animation);
        pushButton_randomize->setObjectName(QString::fromUtf8("pushButton_randomize"));
        sizePolicy.setHeightForWidth(pushButton_randomize->sizePolicy().hasHeightForWidth());
        pushButton_randomize->setSizePolicy(sizePolicy);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/gradient/icons/dice_colors.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_randomize->setIcon(icon6);

        gridLayout_keyframe_animation_parameters->addWidget(pushButton_randomize, 2, 2, 1, 1);

        pushButton_add_all_parameters = new QPushButton(tab_keyframe_animation);
        pushButton_add_all_parameters->setObjectName(QString::fromUtf8("pushButton_add_all_parameters"));
        sizePolicy.setHeightForWidth(pushButton_add_all_parameters->sizePolicy().hasHeightForWidth());
        pushButton_add_all_parameters->setSizePolicy(sizePolicy);

        gridLayout_keyframe_animation_parameters->addWidget(pushButton_add_all_parameters, 2, 3, 1, 1);


        verticalLayout_flight_animtion_2->addLayout(gridLayout_keyframe_animation_parameters);

        scrollArea_keyframe_animation_parameters = new QScrollArea(tab_keyframe_animation);
        scrollArea_keyframe_animation_parameters->setObjectName(QString::fromUtf8("scrollArea_keyframe_animation_parameters"));
        scrollArea_keyframe_animation_parameters->setWidgetResizable(true);
        scrollAreaWidgetContents_keyframeAnimationParameters = new QWidget();
        scrollAreaWidgetContents_keyframeAnimationParameters->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_keyframeAnimationParameters"));
        scrollAreaWidgetContents_keyframeAnimationParameters->setGeometry(QRect(0, 0, 407, 656));
        verticalLayout_92 = new QVBoxLayout(scrollAreaWidgetContents_keyframeAnimationParameters);
        verticalLayout_92->setObjectName(QString::fromUtf8("verticalLayout_92"));
        verticalLayout_92->setContentsMargins(2, 2, 2, 2);
        groupBox_4 = new QGroupBox(scrollAreaWidgetContents_keyframeAnimationParameters);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout_4 = new QVBoxLayout(groupBox_4);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(2, 2, 2, 2);
        label_camera_distance_from_keyframe = new QLabel(groupBox_4);
        label_camera_distance_from_keyframe->setObjectName(QString::fromUtf8("label_camera_distance_from_keyframe"));
        label_camera_distance_from_keyframe->setWordWrap(true);

        verticalLayout_4->addWidget(label_camera_distance_from_keyframe);


        verticalLayout_92->addWidget(groupBox_4);

        groupBox = new QGroupBox(scrollAreaWidgetContents_keyframeAnimationParameters);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        gridLayout_52 = new QGridLayout();
        gridLayout_52->setSpacing(2);
        gridLayout_52->setObjectName(QString::fromUtf8("gridLayout_52"));
        label_177 = new QLabel(groupBox);
        label_177->setObjectName(QString::fromUtf8("label_177"));

        gridLayout_52->addWidget(label_177, 2, 0, 1, 1);

        spinboxInt_frames_per_keyframe = new MySpinBox(groupBox);
        spinboxInt_frames_per_keyframe->setObjectName(QString::fromUtf8("spinboxInt_frames_per_keyframe"));
        sizePolicy.setHeightForWidth(spinboxInt_frames_per_keyframe->sizePolicy().hasHeightForWidth());
        spinboxInt_frames_per_keyframe->setSizePolicy(sizePolicy);
        spinboxInt_frames_per_keyframe->setMinimum(1);
        spinboxInt_frames_per_keyframe->setMaximum(10000);

        gridLayout_52->addWidget(spinboxInt_frames_per_keyframe, 0, 1, 1, 1);

        spinbox_keyframe_frames_per_second = new MyDoubleSpinBox(groupBox);
        spinbox_keyframe_frames_per_second->setObjectName(QString::fromUtf8("spinbox_keyframe_frames_per_second"));
        sizePolicy.setHeightForWidth(spinbox_keyframe_frames_per_second->sizePolicy().hasHeightForWidth());
        spinbox_keyframe_frames_per_second->setSizePolicy(sizePolicy);
        spinbox_keyframe_frames_per_second->setDecimals(4);
        spinbox_keyframe_frames_per_second->setMaximum(18000.000000000000000);
        spinbox_keyframe_frames_per_second->setSingleStep(0.100000000000000);

        gridLayout_52->addWidget(spinbox_keyframe_frames_per_second, 1, 1, 1, 2);

        label_217 = new QLabel(groupBox);
        label_217->setObjectName(QString::fromUtf8("label_217"));

        gridLayout_52->addWidget(label_217, 5, 0, 1, 1);

        spinboxInt_keyframe_last_to_render = new MySpinBox(groupBox);
        spinboxInt_keyframe_last_to_render->setObjectName(QString::fromUtf8("spinboxInt_keyframe_last_to_render"));
        sizePolicy.setHeightForWidth(spinboxInt_keyframe_last_to_render->sizePolicy().hasHeightForWidth());
        spinboxInt_keyframe_last_to_render->setSizePolicy(sizePolicy);
        spinboxInt_keyframe_last_to_render->setMinimum(0);
        spinboxInt_keyframe_last_to_render->setMaximum(99999);
        spinboxInt_keyframe_last_to_render->setSingleStep(1);

        gridLayout_52->addWidget(spinboxInt_keyframe_last_to_render, 5, 1, 1, 2);

        label_222 = new QLabel(groupBox);
        label_222->setObjectName(QString::fromUtf8("label_222"));

        gridLayout_52->addWidget(label_222, 1, 0, 1, 1);

        label_219 = new QLabel(groupBox);
        label_219->setObjectName(QString::fromUtf8("label_219"));

        gridLayout_52->addWidget(label_219, 0, 0, 1, 1);

        comboBox_keyframe_animation_image_type = new MyComboBox(groupBox);
        comboBox_keyframe_animation_image_type->addItem(QString());
        comboBox_keyframe_animation_image_type->addItem(QString());
        comboBox_keyframe_animation_image_type->addItem(QString());
        comboBox_keyframe_animation_image_type->addItem(QString());
        comboBox_keyframe_animation_image_type->setObjectName(QString::fromUtf8("comboBox_keyframe_animation_image_type"));
        sizePolicy2.setHeightForWidth(comboBox_keyframe_animation_image_type->sizePolicy().hasHeightForWidth());
        comboBox_keyframe_animation_image_type->setSizePolicy(sizePolicy2);

        gridLayout_52->addWidget(comboBox_keyframe_animation_image_type, 3, 1, 1, 2);

        button_selectAnimKeyframeImageDir = new QPushButton(groupBox);
        button_selectAnimKeyframeImageDir->setObjectName(QString::fromUtf8("button_selectAnimKeyframeImageDir"));
        sizePolicy.setHeightForWidth(button_selectAnimKeyframeImageDir->sizePolicy().hasHeightForWidth());
        button_selectAnimKeyframeImageDir->setSizePolicy(sizePolicy);

        gridLayout_52->addWidget(button_selectAnimKeyframeImageDir, 2, 2, 1, 1);

        label_150 = new QLabel(groupBox);
        label_150->setObjectName(QString::fromUtf8("label_150"));

        gridLayout_52->addWidget(label_150, 3, 0, 1, 1);

        spinboxInt_keyframe_first_to_render = new MySpinBox(groupBox);
        spinboxInt_keyframe_first_to_render->setObjectName(QString::fromUtf8("spinboxInt_keyframe_first_to_render"));
        sizePolicy.setHeightForWidth(spinboxInt_keyframe_first_to_render->sizePolicy().hasHeightForWidth());
        spinboxInt_keyframe_first_to_render->setSizePolicy(sizePolicy);
        spinboxInt_keyframe_first_to_render->setMinimum(0);
        spinboxInt_keyframe_first_to_render->setMaximum(99999);
        spinboxInt_keyframe_first_to_render->setSingleStep(1);
        spinboxInt_keyframe_first_to_render->setValue(0);

        gridLayout_52->addWidget(spinboxInt_keyframe_first_to_render, 4, 1, 1, 2);

        label_213 = new QLabel(groupBox);
        label_213->setObjectName(QString::fromUtf8("label_213"));

        gridLayout_52->addWidget(label_213, 4, 0, 1, 1);

        text_anim_keyframe_dir = new MyLineEdit(groupBox);
        text_anim_keyframe_dir->setObjectName(QString::fromUtf8("text_anim_keyframe_dir"));
        sizePolicy1.setHeightForWidth(text_anim_keyframe_dir->sizePolicy().hasHeightForWidth());
        text_anim_keyframe_dir->setSizePolicy(sizePolicy1);

        gridLayout_52->addWidget(text_anim_keyframe_dir, 2, 1, 1, 1);

        pushButton_set_frames_per_keyframe_to_all = new QPushButton(groupBox);
        pushButton_set_frames_per_keyframe_to_all->setObjectName(QString::fromUtf8("pushButton_set_frames_per_keyframe_to_all"));

        gridLayout_52->addWidget(pushButton_set_frames_per_keyframe_to_all, 0, 2, 1, 1);

        checkBox_keyframe_animation_loop = new MyCheckBox(groupBox);
        checkBox_keyframe_animation_loop->setObjectName(QString::fromUtf8("checkBox_keyframe_animation_loop"));
        sizePolicy.setHeightForWidth(checkBox_keyframe_animation_loop->sizePolicy().hasHeightForWidth());
        checkBox_keyframe_animation_loop->setSizePolicy(sizePolicy);

        gridLayout_52->addWidget(checkBox_keyframe_animation_loop, 6, 0, 1, 3);


        verticalLayout->addLayout(gridLayout_52);


        verticalLayout_92->addWidget(groupBox);

        groupBox_2 = new QGroupBox(scrollAreaWidgetContents_keyframeAnimationParameters);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(2, 2, 2, 2);
        checkBox_keyframe_auto_validate = new MyCheckBox(groupBox_2);
        checkBox_keyframe_auto_validate->setObjectName(QString::fromUtf8("checkBox_keyframe_auto_validate"));
        sizePolicy.setHeightForWidth(checkBox_keyframe_auto_validate->sizePolicy().hasHeightForWidth());
        checkBox_keyframe_auto_validate->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(checkBox_keyframe_auto_validate);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        logedit_keyframe_collision_thresh = new MyLineEdit(groupBox_2);
        logedit_keyframe_collision_thresh->setObjectName(QString::fromUtf8("logedit_keyframe_collision_thresh"));
        sizePolicy1.setHeightForWidth(logedit_keyframe_collision_thresh->sizePolicy().hasHeightForWidth());
        logedit_keyframe_collision_thresh->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(logedit_keyframe_collision_thresh, 0, 1, 1, 1);

        label_221 = new QLabel(groupBox_2);
        label_221->setObjectName(QString::fromUtf8("label_221"));

        gridLayout->addWidget(label_221, 0, 0, 1, 1);

        pushButton_set_constant_target_distance = new QPushButton(groupBox_2);
        pushButton_set_constant_target_distance->setObjectName(QString::fromUtf8("pushButton_set_constant_target_distance"));
        sizePolicy.setHeightForWidth(pushButton_set_constant_target_distance->sizePolicy().hasHeightForWidth());
        pushButton_set_constant_target_distance->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_set_constant_target_distance, 1, 0, 1, 1);

        logedit_keyframe_constant_target_distance = new MyLineEdit(groupBox_2);
        logedit_keyframe_constant_target_distance->setObjectName(QString::fromUtf8("logedit_keyframe_constant_target_distance"));
        sizePolicy1.setHeightForWidth(logedit_keyframe_constant_target_distance->sizePolicy().hasHeightForWidth());
        logedit_keyframe_constant_target_distance->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(logedit_keyframe_constant_target_distance, 1, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout);


        verticalLayout_92->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(scrollAreaWidgetContents_keyframeAnimationParameters);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(2, 2, 2, 2);
        checkBox_show_keyframe_thumbnails = new MyCheckBox(groupBox_3);
        checkBox_show_keyframe_thumbnails->setObjectName(QString::fromUtf8("checkBox_show_keyframe_thumbnails"));
        sizePolicy.setHeightForWidth(checkBox_show_keyframe_thumbnails->sizePolicy().hasHeightForWidth());
        checkBox_show_keyframe_thumbnails->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(checkBox_show_keyframe_thumbnails);

        checkBox_show_camera_path = new MyCheckBox(groupBox_3);
        checkBox_show_camera_path->setObjectName(QString::fromUtf8("checkBox_show_camera_path"));
        sizePolicy.setHeightForWidth(checkBox_show_camera_path->sizePolicy().hasHeightForWidth());
        checkBox_show_camera_path->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(checkBox_show_camera_path);

        checkBox_show_target_path = new MyCheckBox(groupBox_3);
        checkBox_show_target_path->setObjectName(QString::fromUtf8("checkBox_show_target_path"));
        sizePolicy.setHeightForWidth(checkBox_show_target_path->sizePolicy().hasHeightForWidth());
        checkBox_show_target_path->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(checkBox_show_target_path);

        checkBox_show_light_path_1 = new MyCheckBox(groupBox_3);
        checkBox_show_light_path_1->setObjectName(QString::fromUtf8("checkBox_show_light_path_1"));
        sizePolicy.setHeightForWidth(checkBox_show_light_path_1->sizePolicy().hasHeightForWidth());
        checkBox_show_light_path_1->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(checkBox_show_light_path_1);

        checkBox_show_light_path_2 = new MyCheckBox(groupBox_3);
        checkBox_show_light_path_2->setObjectName(QString::fromUtf8("checkBox_show_light_path_2"));
        sizePolicy.setHeightForWidth(checkBox_show_light_path_2->sizePolicy().hasHeightForWidth());
        checkBox_show_light_path_2->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(checkBox_show_light_path_2);

        checkBox_show_light_path_3 = new MyCheckBox(groupBox_3);
        checkBox_show_light_path_3->setObjectName(QString::fromUtf8("checkBox_show_light_path_3"));
        sizePolicy.setHeightForWidth(checkBox_show_light_path_3->sizePolicy().hasHeightForWidth());
        checkBox_show_light_path_3->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(checkBox_show_light_path_3);

        checkBox_show_light_path_4 = new MyCheckBox(groupBox_3);
        checkBox_show_light_path_4->setObjectName(QString::fromUtf8("checkBox_show_light_path_4"));
        sizePolicy.setHeightForWidth(checkBox_show_light_path_4->sizePolicy().hasHeightForWidth());
        checkBox_show_light_path_4->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(checkBox_show_light_path_4);


        verticalLayout_92->addWidget(groupBox_3);

        verticalSpacer_13 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_92->addItem(verticalSpacer_13);

        scrollArea_keyframe_animation_parameters->setWidget(scrollAreaWidgetContents_keyframeAnimationParameters);

        verticalLayout_flight_animtion_2->addWidget(scrollArea_keyframe_animation_parameters);


        horizontalLayout_15->addLayout(verticalLayout_flight_animtion_2);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        toolButton_previousFrame = new QToolButton(tab_keyframe_animation);
        toolButton_previousFrame->setObjectName(QString::fromUtf8("toolButton_previousFrame"));
        QIcon icon7;
        iconThemeName = QString::fromUtf8("arrow-left");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon7 = QIcon::fromTheme(iconThemeName);
        } else {
            icon7.addFile(QString::fromUtf8(":/navigation/icons/go-previous.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        toolButton_previousFrame->setIcon(icon7);

        horizontalLayout_2->addWidget(toolButton_previousFrame);

        toolButton_next_frame = new QToolButton(tab_keyframe_animation);
        toolButton_next_frame->setObjectName(QString::fromUtf8("toolButton_next_frame"));
        QIcon icon8;
        iconThemeName = QString::fromUtf8("arrow-right");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon8 = QIcon::fromTheme(iconThemeName);
        } else {
            icon8.addFile(QString::fromUtf8(":/navigation/icons/go-next.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        toolButton_next_frame->setIcon(icon8);

        horizontalLayout_2->addWidget(toolButton_next_frame);

        label_actualFrame = new QLabel(tab_keyframe_animation);
        label_actualFrame->setObjectName(QString::fromUtf8("label_actualFrame"));

        horizontalLayout_2->addWidget(label_actualFrame);

        horizontalSlider_actualFrame = new QSlider(tab_keyframe_animation);
        horizontalSlider_actualFrame->setObjectName(QString::fromUtf8("horizontalSlider_actualFrame"));
        horizontalSlider_actualFrame->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider_actualFrame);


        verticalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(2);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, -1, -1);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        toolButton_chartZoomIn = new QToolButton(tab_keyframe_animation);
        toolButton_chartZoomIn->setObjectName(QString::fromUtf8("toolButton_chartZoomIn"));
        QIcon icon9(QIcon::fromTheme(QString::fromUtf8("zoom-in")));
        toolButton_chartZoomIn->setIcon(icon9);

        gridLayout_2->addWidget(toolButton_chartZoomIn, 0, 0, 1, 1);

        toolButton_chartZoomOut = new QToolButton(tab_keyframe_animation);
        toolButton_chartZoomOut->setObjectName(QString::fromUtf8("toolButton_chartZoomOut"));
        QIcon icon10(QIcon::fromTheme(QString::fromUtf8("zoom-out")));
        toolButton_chartZoomOut->setIcon(icon10);

        gridLayout_2->addWidget(toolButton_chartZoomOut, 0, 1, 1, 1);


        horizontalLayout_3->addLayout(gridLayout_2);

        widgetValueChart = new cAnimationValueChartWidget(tab_keyframe_animation);
        widgetValueChart->setObjectName(QString::fromUtf8("widgetValueChart"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(64);
        sizePolicy4.setHeightForWidth(widgetValueChart->sizePolicy().hasHeightForWidth());
        widgetValueChart->setSizePolicy(sizePolicy4);

        horizontalLayout_3->addWidget(widgetValueChart);

        horizontalLayout_3->setStretch(1, 1);

        verticalLayout_5->addLayout(horizontalLayout_3);

        tableWidget_keyframe_animation = new MyTableWidgetKeyframes(tab_keyframe_animation);
        tableWidget_keyframe_animation->setObjectName(QString::fromUtf8("tableWidget_keyframe_animation"));
        sizePolicy3.setHeightForWidth(tableWidget_keyframe_animation->sizePolicy().hasHeightForWidth());
        tableWidget_keyframe_animation->setSizePolicy(sizePolicy3);
        tableWidget_keyframe_animation->verticalHeader()->setDefaultSectionSize(22);

        verticalLayout_5->addWidget(tableWidget_keyframe_animation);


        horizontalLayout_15->addLayout(verticalLayout_5);

        horizontalLayout_15->setStretch(1, 1);
        tabWidgetFlightKeyframe->addTab(tab_keyframe_animation, QString());

        horizontalLayout->addWidget(tabWidgetFlightKeyframe);

        QWidget::setTabOrder(pushButton_render_flight, pushButton_record_flight);
        QWidget::setTabOrder(pushButton_record_flight, pushButton_continue_recording);
        QWidget::setTabOrder(pushButton_continue_recording, pushButton_show_animation);
        QWidget::setTabOrder(pushButton_show_animation, pushButton_delete_all_images);
        QWidget::setTabOrder(pushButton_delete_all_images, pushButton_flight_refresh_table);
        QWidget::setTabOrder(pushButton_flight_refresh_table, pushButton_flight_to_keyframe_export);
        QWidget::setTabOrder(pushButton_flight_to_keyframe_export, scrollArea_flight_animation_parameters);
        QWidget::setTabOrder(scrollArea_flight_animation_parameters, spinbox_flight_inertia);
        QWidget::setTabOrder(spinbox_flight_inertia, spinbox_flight_rotation_speed);
        QWidget::setTabOrder(spinbox_flight_rotation_speed, spinbox_flight_roll_speed);
        QWidget::setTabOrder(spinbox_flight_roll_speed, comboBox_flight_speed_control);
        QWidget::setTabOrder(comboBox_flight_speed_control, spinbox_flight_sec_per_frame);
        QWidget::setTabOrder(spinbox_flight_sec_per_frame, text_anim_flight_dir);
        QWidget::setTabOrder(text_anim_flight_dir, button_selectAnimFlightImageDir);
        QWidget::setTabOrder(button_selectAnimFlightImageDir, comboBox_flight_animation_image_type);
        QWidget::setTabOrder(comboBox_flight_animation_image_type, spinboxInt_flight_first_to_render);
        QWidget::setTabOrder(spinboxInt_flight_first_to_render, spinboxInt_flight_last_to_render);
        QWidget::setTabOrder(spinboxInt_flight_last_to_render, checkBox_flight_show_thumbnails);
        QWidget::setTabOrder(checkBox_flight_show_thumbnails, checkBox_flight_add_speeds);
        QWidget::setTabOrder(checkBox_flight_add_speeds, pushButton_render_keyframe_animation);
        QWidget::setTabOrder(pushButton_render_keyframe_animation, pushButton_check_for_collisions);
        QWidget::setTabOrder(pushButton_check_for_collisions, pushButton_refresh_keyframe_table);
        QWidget::setTabOrder(pushButton_refresh_keyframe_table, tableWidget_flightAnimation);
        QWidget::setTabOrder(tableWidget_flightAnimation, pushButton_insert_keyframe);
        QWidget::setTabOrder(pushButton_insert_keyframe, pushButton_add_keyframe);
        QWidget::setTabOrder(pushButton_add_keyframe, pushButton_delete_keyframe);
        QWidget::setTabOrder(pushButton_delete_keyframe, pushButton_modify_keyframe);
        QWidget::setTabOrder(pushButton_modify_keyframe, pushButton_show_keyframe_animation);
        QWidget::setTabOrder(pushButton_show_keyframe_animation, pushButton_delete_all_keyframe_images);
        QWidget::setTabOrder(pushButton_delete_all_keyframe_images, pushButton_keyframe_to_flight_export);
        QWidget::setTabOrder(pushButton_keyframe_to_flight_export, scrollArea_keyframe_animation_parameters);
        QWidget::setTabOrder(scrollArea_keyframe_animation_parameters, spinboxInt_frames_per_keyframe);
        QWidget::setTabOrder(spinboxInt_frames_per_keyframe, text_anim_keyframe_dir);
        QWidget::setTabOrder(text_anim_keyframe_dir, button_selectAnimKeyframeImageDir);
        QWidget::setTabOrder(button_selectAnimKeyframeImageDir, comboBox_keyframe_animation_image_type);
        QWidget::setTabOrder(comboBox_keyframe_animation_image_type, spinboxInt_keyframe_first_to_render);
        QWidget::setTabOrder(spinboxInt_keyframe_first_to_render, spinboxInt_keyframe_last_to_render);

        retranslateUi(cDockAnimation);

        tabWidgetFlightKeyframe->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(cDockAnimation);
    } // setupUi

    void retranslateUi(QWidget *cDockAnimation)
    {
        cDockAnimation->setWindowTitle(QCoreApplication::translate("cDockAnimation", "Form", nullptr));
#if QT_CONFIG(tooltip)
        tab_flight_animation->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>In record flight mode, the camera is operated like in a flight simulator game. Flight path is recorded. It recommended to use low image resolution for better recording performance. </p><p>Render animation button starts rendering of the recorded flight path. For final rendering you can select higher image resolution.</p><p>To add a parameter, right click on the selected parameter's edit field and select from context menu <span style=\" font-style:italic;\">Add to flight animation</span></p><p>You can modify frame parameters directly in the animation table or by editing parameters in fractal or effects edit fields (double click keyframe preview or right click on a keyframe, and choose <span style=\" font-style:italic;\">Render this keyframe</span> , this updates parameters in window, then modify parameters and click <span style=\" font-style:italic;\">Modify keyframe</span> to get modified parameters into table)</p><p>You can click on <span style=\" font-style:italic;\">Export to keyframes<"
                        "/span> to continue editing animation in <span style=\" font-style:italic;\">Keyframe animation</span> editor</p><p>Animation is stored in a settings file in CSV format, therefore it is possible to edit animation with external tools (e.g spreadsheet editor or text editor).</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        pushButton_render_flight->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Starts rendering of previously recorded flight path</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_render_flight->setText(QCoreApplication::translate("cDockAnimation", "Render flight animation", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_record_flight->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Starts recording flight path. </p><p>It is recommended to decrease image resolution for better rendering performance.</p><p>The mouse pointer is used as the controller. <br/>Move the mouse pointer to change flight direction.<br/>Left mouse button increases flight speed. Right mouse button decreases speed.<br/>Arrow keys moves camera up, down, left and right (move sidewards)<br/>Z and X keys rotate the camera (roll)<br/>Spacebar pauses flight path recording . </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_record_flight->setText(QCoreApplication::translate("cDockAnimation", "Record flight path", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_delete_all_images->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Deletes all already rendered image frames in selected folder (<span style=\" font-style:italic;\">Path for images</span>). </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_delete_all_images->setText(QCoreApplication::translate("cDockAnimation", "Delete all images", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_show_animation->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Plays rendered animation.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_show_animation->setText(QCoreApplication::translate("cDockAnimation", "Show Animation", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_continue_recording->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Continues recording previously stopped rendering. The flight will start from the last point from the table, and will be continued with the latest direction and speed.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_continue_recording->setText(QCoreApplication::translate("cDockAnimation", "Continue recording", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_flight_refresh_table->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Refreshes animation table and keyframe previews.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_flight_refresh_table->setText(QCoreApplication::translate("cDockAnimation", "Refresh table", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_flight_to_keyframe_export->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Exports flight path to keyframe animation.  <span style=\" font-style:italic;\">Keyframe animation/frames per keyframe</span> parameter is used to determine how many frames will be exported as new keyframes. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_flight_to_keyframe_export->setText(QCoreApplication::translate("cDockAnimation", "Export to Keyframes", nullptr));
        label_path_for_images->setText(QCoreApplication::translate("cDockAnimation", "path for images:", nullptr));
        label_image_type->setText(QCoreApplication::translate("cDockAnimation", "image type:", nullptr));
        label_147->setText(QCoreApplication::translate("cDockAnimation", "inertia:", nullptr));
        label_146->setText(QCoreApplication::translate("cDockAnimation", "speed:", nullptr));
#if QT_CONFIG(tooltip)
        text_anim_flight_dir->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Path to stored rendered animation frames.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        comboBox_flight_speed_control->setItemText(0, QCoreApplication::translate("cDockAnimation", "Relative to distance", nullptr));
        comboBox_flight_speed_control->setItemText(1, QCoreApplication::translate("cDockAnimation", "Constant", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_flight_speed_control->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Determines how camera speed will be calculated.</p><p>In <span style=\" font-style:italic;\">Relative to distance</span> mode, camera speed will decrease when camera is nearer to the fractal surface. This mode will help you to not collide with the fractal. In this mode you can still control speed by <span style=\" font-style:italic;\">speed</span> parameter and by mouse buttons.</p><p>In Constant mode, the camera speed is only controlled by <span style=\" font-style:italic;\">speed</span> parameter and mouse buttons</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_148->setText(QCoreApplication::translate("cDockAnimation", "speed control:", nullptr));
        button_selectAnimFlightImageDir->setText(QCoreApplication::translate("cDockAnimation", "Select folder", nullptr));
        label_151->setText(QCoreApplication::translate("cDockAnimation", "seconds per frame:", nullptr));
        label_153->setText(QCoreApplication::translate("cDockAnimation", "roll speed:", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_flight_show_thumbnails->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Enables rendering of keyframe previews in animation table.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_flight_show_thumbnails->setText(QCoreApplication::translate("cDockAnimation", "Show thumbnails", nullptr));
        label_152->setText(QCoreApplication::translate("cDockAnimation", "rotation speed:", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_flight_add_speeds->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Enable this parameter  if you want to record a flight path in parts. It allows the program to continue recording the flight with the same speed.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_flight_add_speeds->setText(QCoreApplication::translate("cDockAnimation", "Add flight and rotation speed to parameters\n"
"(needed to continue recording animation)", nullptr));
        comboBox_flight_animation_image_type->setItemText(0, QCoreApplication::translate("cDockAnimation", "PNG", nullptr));
        comboBox_flight_animation_image_type->setItemText(1, QCoreApplication::translate("cDockAnimation", "JPG", nullptr));
        comboBox_flight_animation_image_type->setItemText(2, QCoreApplication::translate("cDockAnimation", "EXR", nullptr));
        comboBox_flight_animation_image_type->setItemText(3, QCoreApplication::translate("cDockAnimation", "TIFF", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_flight_animation_image_type->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Selection for image format for animation frames.</p><p>For more image format settings go to to <span style=\" font-style:italic;\">File/Program Preferences</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_218->setText(QCoreApplication::translate("cDockAnimation", "first frame to render:", nullptr));
        label_220->setText(QCoreApplication::translate("cDockAnimation", "last frame to render:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_flight_speed->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Controls flight speed. </p><p>If you click left mouse button, speed will be increased</p><p>If you click right mouse button, speed will be decreased</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinbox_flight_inertia->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Inertia of camera. </p><p>Higher inertia makes flight more smooth but more difficult to change speed or direction.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_flight_inertia->setPrefix(QString());
        spinbox_flight_inertia->setSuffix(QString());
#if QT_CONFIG(tooltip)
        spinbox_flight_rotation_speed->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Rotation speed of camera</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_flight_rotation_speed->setPrefix(QString());
        spinbox_flight_rotation_speed->setSuffix(QString());
#if QT_CONFIG(tooltip)
        spinbox_flight_roll_speed->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Roll speed of camera</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_flight_roll_speed->setPrefix(QString());
        spinbox_flight_roll_speed->setSuffix(QString());
#if QT_CONFIG(tooltip)
        spinboxInt_flight_first_to_render->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Limits range of frames to render</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinboxInt_flight_last_to_render->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Limits range of frames to render</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinbox_flight_sec_per_frame->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>This parameters controls frame rate during flight path recording. Higher values give slower rendering but are more detailed.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_flight_sec_per_frame->setPrefix(QString());
        spinbox_flight_sec_per_frame->setSuffix(QString());
        tabWidgetFlightKeyframe->setTabText(tabWidgetFlightKeyframe->indexOf(tab_flight_animation), QCoreApplication::translate("cDockAnimation", "Flight animation (every frame)", nullptr));
#if QT_CONFIG(tooltip)
        tab_keyframe_animation->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>This feature is for rendering animations by interpolating between keyframes.</p><p>You can create multiple keyframes, each with different parameters (i.e.camera, fractal and environment parameters values). Intermediate frames will be calculated during rendering of the animation. </p><p>To add a keyframe to the animation table, click <span style=\" font-style:italic;\">Add keyframe</span>. </p><p>To add a parameter, right click on the selected parameter's edit field and select from context menu <span style=\" font-style:italic;\">Add to keyframe animation</span></p><p>Build an animation by adding, inserting and deleting keyframes. Modify parameters directly in the animation table, or in fractal or effects edit fields (double click keyframe preview or right click on a keyframe, and choose <span style=\" font-style:italic;\">Render this keyframe</span> , this updates parameters in window, then modify parameters and click <span style=\" font-style:italic;\">Modify keyframe</span> to refresh a"
                        "nimation table.)</p><p>Each parameter can have assigned different type of interpolation (right click on animation parameter name.)</p><p>Animation is stored in a settings file in CSV format, therefore it is possible to edit animation with external tools (e.g spreadsheet editor or text editor).</p><p>Animation can be exported to Flight Animation, where it is possible to edit each frame.</p><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        pushButton_insert_keyframe->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Insert keyframe before selected keyframe</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_insert_keyframe->setText(QCoreApplication::translate("cDockAnimation", "Insert keyframe", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_delete_keyframe->setToolTip(QCoreApplication::translate("cDockAnimation", "Delete selected keyframe", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_delete_keyframe->setText(QCoreApplication::translate("cDockAnimation", "Delete keyframe", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_add_keyframe->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Add keyframe at the end</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_add_keyframe->setText(QCoreApplication::translate("cDockAnimation", "Add keyframe", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_show_keyframe_animation->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Play rendered animation</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_show_keyframe_animation->setText(QCoreApplication::translate("cDockAnimation", "Show Animation", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_render_keyframe_animation->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Starts rendering of animation</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_render_keyframe_animation->setText(QCoreApplication::translate("cDockAnimation", "Render animation", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_modify_keyframe->setToolTip(QCoreApplication::translate("cDockAnimation", "Modify selected keyframe", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_modify_keyframe->setText(QCoreApplication::translate("cDockAnimation", "Modify keyframe", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_keyframe_to_flight_export->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Export all keyframes to <span style=\" font-style:italic;\">Flight animation</span>. All keyframes will be interpolated. </p><p>This feature will allow editing of each animation frame separately in Flight animation editor (or external CSV editor) </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_keyframe_to_flight_export->setText(QCoreApplication::translate("cDockAnimation", "Export to Flight", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_delete_all_keyframe_images->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Delete all rendered frames in animation folder ( selected by <span style=\" font-style:italic;\">path for images)</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_delete_all_keyframe_images->setText(QCoreApplication::translate("cDockAnimation", "Delete all images", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_refresh_keyframe_table->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Refreshes animation table and keyframe previews.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_refresh_keyframe_table->setText(QCoreApplication::translate("cDockAnimation", "Refresh table", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_check_for_collisions->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Checks if there is no collision between camera and fractal at all interpolated frames.</p><p>Collision is defined as event where distance of camera to fractal object is lower than <span style=\" font-style:italic;\">collision distance</span> parameter</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_check_for_collisions->setText(QCoreApplication::translate("cDockAnimation", "Validate", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_randomize->setToolTip(QCoreApplication::translate("cDockAnimation", "Modify selected keyframe", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_randomize->setText(QCoreApplication::translate("cDockAnimation", "Randomize", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_add_all_parameters->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Add all parameters with non-default value to the animation</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_add_all_parameters->setText(QCoreApplication::translate("cDockAnimation", "Add all parameters", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("cDockAnimation", "Information", nullptr));
        label_camera_distance_from_keyframe->setText(QCoreApplication::translate("cDockAnimation", "Camera distance from selected keyframe: ", nullptr));
        groupBox->setTitle(QCoreApplication::translate("cDockAnimation", "Animation parameters", nullptr));
        label_177->setText(QCoreApplication::translate("cDockAnimation", "path for images:", nullptr));
#if QT_CONFIG(tooltip)
        spinboxInt_frames_per_keyframe->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>It sets how many frames will be interpolated for each keyframe. </p><p>Total number of animation frames is 'number of keyframes' multiplied by 'frames per keyframe' </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_keyframe_frames_per_second->setPrefix(QString());
        spinbox_keyframe_frames_per_second->setSuffix(QString());
        label_217->setText(QCoreApplication::translate("cDockAnimation", "last frame to render:", nullptr));
#if QT_CONFIG(tooltip)
        spinboxInt_keyframe_last_to_render->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Limits range of frames to render</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_222->setText(QCoreApplication::translate("cDockAnimation", "frames per second:", nullptr));
        label_219->setText(QCoreApplication::translate("cDockAnimation", "frames per keyframe:", nullptr));
        comboBox_keyframe_animation_image_type->setItemText(0, QCoreApplication::translate("cDockAnimation", "PNG", nullptr));
        comboBox_keyframe_animation_image_type->setItemText(1, QCoreApplication::translate("cDockAnimation", "JPG", nullptr));
        comboBox_keyframe_animation_image_type->setItemText(2, QCoreApplication::translate("cDockAnimation", "EXR", nullptr));
        comboBox_keyframe_animation_image_type->setItemText(3, QCoreApplication::translate("cDockAnimation", "TIFF", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_keyframe_animation_image_type->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Selection for image format for animation frames.</p><p>For more image format settings go to to <span style=\" font-style:italic;\">File/Program Preferences</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        button_selectAnimKeyframeImageDir->setText(QCoreApplication::translate("cDockAnimation", "Select folder", nullptr));
        label_150->setText(QCoreApplication::translate("cDockAnimation", "image type:", nullptr));
#if QT_CONFIG(tooltip)
        spinboxInt_keyframe_first_to_render->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Limits range of frames to render</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_213->setText(QCoreApplication::translate("cDockAnimation", "first frame to render:", nullptr));
#if QT_CONFIG(tooltip)
        text_anim_keyframe_dir->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Path to stored rendered animation frames.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_set_frames_per_keyframe_to_all->setText(QCoreApplication::translate("cDockAnimation", "Set in all", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_keyframe_animation_loop->setToolTip(QCoreApplication::translate("cDockAnimation", "Interpolates first and last frames to make a loop", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_keyframe_animation_loop->setText(QCoreApplication::translate("cDockAnimation", "Loop", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("cDockAnimation", "Validation and cleaning up", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_keyframe_auto_validate->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Enable checking for collisions before starting rendering of animation.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_keyframe_auto_validate->setText(QCoreApplication::translate("cDockAnimation", "Validate before render", nullptr));
#if QT_CONFIG(tooltip)
        logedit_keyframe_collision_thresh->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Minimum distance between camera and fractal which is allowed during <span style=\" font-style:italic;\">Validate</span> function (collision detection)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_221->setText(QCoreApplication::translate("cDockAnimation", "collision distance:", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_set_constant_target_distance->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Sets the same distance between camera target and camera for all keyframes. It doesn't modify camera position and rotation, so it doesn't modify camera movement path. It makes camera rotation smooth through entire animation.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_set_constant_target_distance->setText(QCoreApplication::translate("cDockAnimation", "Set the same\n"
"camera target\n"
"distance for all\n"
"keyframes", nullptr));
#if QT_CONFIG(tooltip)
        logedit_keyframe_constant_target_distance->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Sets the same distance between camera target and camera for all keyframes. It doesn't modify camera position and rotation, so it doesn't modify camera movement path. It makes camera rotation smooth through entire animation.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_3->setTitle(QCoreApplication::translate("cDockAnimation", "Display settings", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_show_keyframe_thumbnails->setToolTip(QCoreApplication::translate("cDockAnimation", "<html><head/><body><p>Enables rendering of keyframe previews in the animation table.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_show_keyframe_thumbnails->setText(QCoreApplication::translate("cDockAnimation", "Show keyframe preview thumbnails", nullptr));
        checkBox_show_camera_path->setText(QCoreApplication::translate("cDockAnimation", "Show camera path", nullptr));
        checkBox_show_target_path->setText(QCoreApplication::translate("cDockAnimation", "Show target path", nullptr));
        checkBox_show_light_path_1->setText(QCoreApplication::translate("cDockAnimation", "Show light #1 path", nullptr));
        checkBox_show_light_path_2->setText(QCoreApplication::translate("cDockAnimation", "Show light #2 path", nullptr));
        checkBox_show_light_path_3->setText(QCoreApplication::translate("cDockAnimation", "Show light #3 path", nullptr));
        checkBox_show_light_path_4->setText(QCoreApplication::translate("cDockAnimation", "Show light #4 path", nullptr));
        toolButton_previousFrame->setText(QCoreApplication::translate("cDockAnimation", "...", nullptr));
        toolButton_next_frame->setText(QCoreApplication::translate("cDockAnimation", "...", nullptr));
        label_actualFrame->setText(QCoreApplication::translate("cDockAnimation", "0", nullptr));
        toolButton_chartZoomIn->setText(QCoreApplication::translate("cDockAnimation", "+", nullptr));
        toolButton_chartZoomOut->setText(QCoreApplication::translate("cDockAnimation", "\342\200\222", nullptr));
        tabWidgetFlightKeyframe->setTabText(tabWidgetFlightKeyframe->indexOf(tab_keyframe_animation), QCoreApplication::translate("cDockAnimation", "Keyframe animation (only keyframes)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cDockAnimation: public Ui_cDockAnimation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCK_ANIMATION_H
