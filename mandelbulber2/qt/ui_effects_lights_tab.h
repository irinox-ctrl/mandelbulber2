/********************************************************************************
** Form generated from reading UI file 'effects_lights_tab.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EFFECTS_LIGHTS_TAB_H
#define UI_EFFECTS_LIGHTS_TAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
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
#include "light_sources_manager.h"
#include "my_check_box.h"
#include "my_color_button.h"
#include "my_combo_box.h"
#include "my_double_spin_box.h"
#include "my_group_box.h"
#include "my_line_edit.h"
#include "my_spin_box.h"

QT_BEGIN_NAMESPACE

class Ui_cEffectsLightsTab
{
public:
    QVBoxLayout *verticalLayout_67;
    QHBoxLayout *horizontalLayout_14;
    cButtonLoadSettingsFromWidget *pushButton_local_load_6;
    cButtonSaveSettingsFromWidget *pushButton_local_save_6;
    cButtonResetSettingsFromWidget *pushButton_local_reset_6;
    cButtonRandomSettingsFromWidget *pushButton_local_randomize_5;
    QSpacerItem *horizontalSpacer_7;
    QScrollArea *scrollArea_10;
    QWidget *scrollAreaWidgetContents_11;
    QVBoxLayout *verticalLayout_41;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_12;
    QGridLayout *gridLayout;
    MyLineEdit *logedit_all_lights_intensity;
    MyLineEdit *logedit_all_lights_size;
    MyColorButton *colorButton_fill_light_color;
    QLabel *label_2;
    QLabel *label_4;
    MyLineEdit *logedit_rayleigh_scattering_blue;
    MyLineEdit *logedit_all_lights_visibility;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_7;
    QLabel *label_13;
    MyLineEdit *logedit_rayleigh_scattering_red;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_17;
    QGridLayout *gridLayout_5;
    MyLineEdit *logedit_aux_light_manual_placement_dist;
    MyCheckBox *checkBox_aux_light_place_behind;
    QLabel *label_134;
    cLightSourcesManager *widget_light_sources_manager;
    MyGroupBox *groupCheck_random_lights_group;
    QVBoxLayout *verticalLayout_random_lights;
    QGridLayout *gridLayout_random_lights;
    QLabel *label_random_lights_intensity_3;
    QLabel *label_random_lights_center_of_distribution;
    MyLineEdit *logedit_random_lights_intensity;
    MyLineEdit *logedit_random_lights_max_distance_from_fractal;
    QLabel *label_random_lights_intensity;
    QLabel *label_random_lights_max_distance_from_fractal;
    QLabel *label_random_lights_intensity_5;
    MyLineEdit *vect3_random_lights_distribution_center_y;
    QLabel *label_random_lights_first_color;
    QLabel *label_random_lights_intensity_2;
    QLabel *label_random_lights_intensity_4;
    QLabel *label_random_lights_random_seed;
    MyComboBox *comboBox_random_lights_coloring_type;
    MySpinBox *spinboxInt_random_lights_number;
    MySpinBox *spinboxInt_random_lights_random_seed;
    QLabel *label_distribution_y;
    MyCheckBox *checkBox_random_lights_cast_shadows;
    QLabel *label_distribution_z;
    QLabel *label_random_lights_number;
    QPushButton *pushButton_place_random_lights_by_mouse;
    QLabel *label_random_lights_second_color;
    MyLineEdit *logedit_random_lights_distribution_radius;
    MyLineEdit *vect3_random_lights_distribution_center_x;
    QLabel *label_random_lights_distribution_radius;
    MyLineEdit *vect3_random_lights_distribution_center_z;
    QLabel *label_distribution_x;
    MyLineEdit *logedit_random_lights_soft_shadow_cone;
    MyCheckBox *checkBox_random_lights_penetrating;
    MyLineEdit *logedit_random_lights_size;
    MyLineEdit *logedit_random_lights_visibility;
    MyColorButton *colorButton_random_lights_color_2;
    MyColorButton *colorButton_random_lights_color;
    MyGroupBox *groupCheck_glow_sphere_1_enabled;
    QVBoxLayout *verticalLayout_glow_sphere;
    QGridLayout *gridLayout_glow_sphere;
    QLabel *label_glow_position_x;
    MyLineEdit *vect3_glow_sphere_1_position_x;
    QLabel *label_glow_position_y;
    MyLineEdit *vect3_glow_sphere_1_position_y;
    QLabel *label_glow_position_z;
    MyLineEdit *vect3_glow_sphere_1_position_z;
    QLabel *label_glow_radius;
    MyDoubleSpinBox *spinboxd_glow_sphere_1_radius;
    QLabel *label_glow_color;
    MyColorButton *colorButton_glow_sphere_1_color;
    QLabel *label_glow_intensity;
    MyDoubleSpinBox *spinboxd_glow_sphere_1_intensity;
    QSpacerItem *verticalSpacer_6;

    void setupUi(QWidget *cEffectsLightsTab)
    {
        if (cEffectsLightsTab->objectName().isEmpty())
            cEffectsLightsTab->setObjectName(QString::fromUtf8("cEffectsLightsTab"));
        verticalLayout_67 = new QVBoxLayout(cEffectsLightsTab);
        verticalLayout_67->setSpacing(2);
        verticalLayout_67->setObjectName(QString::fromUtf8("verticalLayout_67"));
        verticalLayout_67->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        pushButton_local_load_6 = new cButtonLoadSettingsFromWidget(cEffectsLightsTab);
        pushButton_local_load_6->setObjectName(QString::fromUtf8("pushButton_local_load_6"));

        horizontalLayout_14->addWidget(pushButton_local_load_6);

        pushButton_local_save_6 = new cButtonSaveSettingsFromWidget(cEffectsLightsTab);
        pushButton_local_save_6->setObjectName(QString::fromUtf8("pushButton_local_save_6"));

        horizontalLayout_14->addWidget(pushButton_local_save_6);

        pushButton_local_reset_6 = new cButtonResetSettingsFromWidget(cEffectsLightsTab);
        pushButton_local_reset_6->setObjectName(QString::fromUtf8("pushButton_local_reset_6"));

        horizontalLayout_14->addWidget(pushButton_local_reset_6);

        pushButton_local_randomize_5 = new cButtonRandomSettingsFromWidget(cEffectsLightsTab);
        pushButton_local_randomize_5->setObjectName(QString::fromUtf8("pushButton_local_randomize_5"));

        horizontalLayout_14->addWidget(pushButton_local_randomize_5);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_7);


        verticalLayout_67->addLayout(horizontalLayout_14);

        scrollArea_10 = new QScrollArea(cEffectsLightsTab);
        scrollArea_10->setObjectName(QString::fromUtf8("scrollArea_10"));
        scrollArea_10->setWidgetResizable(true);
        scrollAreaWidgetContents_11 = new QWidget();
        scrollAreaWidgetContents_11->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_11"));
        scrollAreaWidgetContents_11->setGeometry(QRect(0, 0, 422, 1651));
        verticalLayout_41 = new QVBoxLayout(scrollAreaWidgetContents_11);
        verticalLayout_41->setSpacing(2);
        verticalLayout_41->setObjectName(QString::fromUtf8("verticalLayout_41"));
        verticalLayout_41->setContentsMargins(2, 2, 2, 2);
        groupBox_7 = new QGroupBox(scrollAreaWidgetContents_11);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        verticalLayout_12 = new QVBoxLayout(groupBox_7);
        verticalLayout_12->setSpacing(2);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(2, 2, 2, 2);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(-1, 0, -1, -1);
        logedit_all_lights_intensity = new MyLineEdit(groupBox_7);
        logedit_all_lights_intensity->setObjectName(QString::fromUtf8("logedit_all_lights_intensity"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(logedit_all_lights_intensity->sizePolicy().hasHeightForWidth());
        logedit_all_lights_intensity->setSizePolicy(sizePolicy);

        gridLayout->addWidget(logedit_all_lights_intensity, 1, 1, 1, 1);

        logedit_all_lights_size = new MyLineEdit(groupBox_7);
        logedit_all_lights_size->setObjectName(QString::fromUtf8("logedit_all_lights_size"));
        sizePolicy.setHeightForWidth(logedit_all_lights_size->sizePolicy().hasHeightForWidth());
        logedit_all_lights_size->setSizePolicy(sizePolicy);

        gridLayout->addWidget(logedit_all_lights_size, 3, 1, 1, 1);

        colorButton_fill_light_color = new MyColorButton(groupBox_7);
        colorButton_fill_light_color->setObjectName(QString::fromUtf8("colorButton_fill_light_color"));

        gridLayout->addWidget(colorButton_fill_light_color, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox_7);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_4 = new QLabel(groupBox_7);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        logedit_rayleigh_scattering_blue = new MyLineEdit(groupBox_7);
        logedit_rayleigh_scattering_blue->setObjectName(QString::fromUtf8("logedit_rayleigh_scattering_blue"));
        sizePolicy.setHeightForWidth(logedit_rayleigh_scattering_blue->sizePolicy().hasHeightForWidth());
        logedit_rayleigh_scattering_blue->setSizePolicy(sizePolicy);

        gridLayout->addWidget(logedit_rayleigh_scattering_blue, 4, 1, 1, 1);

        logedit_all_lights_visibility = new MyLineEdit(groupBox_7);
        logedit_all_lights_visibility->setObjectName(QString::fromUtf8("logedit_all_lights_visibility"));
        sizePolicy.setHeightForWidth(logedit_all_lights_visibility->sizePolicy().hasHeightForWidth());
        logedit_all_lights_visibility->setSizePolicy(sizePolicy);

        gridLayout->addWidget(logedit_all_lights_visibility, 2, 1, 1, 1);

        label_3 = new QLabel(groupBox_7);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label = new QLabel(groupBox_7);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_7 = new QLabel(groupBox_7);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 4, 0, 1, 1);

        label_13 = new QLabel(groupBox_7);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout->addWidget(label_13, 5, 0, 1, 1);

        logedit_rayleigh_scattering_red = new MyLineEdit(groupBox_7);
        logedit_rayleigh_scattering_red->setObjectName(QString::fromUtf8("logedit_rayleigh_scattering_red"));
        sizePolicy.setHeightForWidth(logedit_rayleigh_scattering_red->sizePolicy().hasHeightForWidth());
        logedit_rayleigh_scattering_red->setSizePolicy(sizePolicy);

        gridLayout->addWidget(logedit_rayleigh_scattering_red, 5, 1, 1, 1);


        verticalLayout_12->addLayout(gridLayout);


        verticalLayout_41->addWidget(groupBox_7);

        groupBox_8 = new QGroupBox(scrollAreaWidgetContents_11);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        verticalLayout_17 = new QVBoxLayout(groupBox_8);
        verticalLayout_17->setSpacing(2);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        verticalLayout_17->setContentsMargins(2, 2, 2, 2);
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(2);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        logedit_aux_light_manual_placement_dist = new MyLineEdit(groupBox_8);
        logedit_aux_light_manual_placement_dist->setObjectName(QString::fromUtf8("logedit_aux_light_manual_placement_dist"));

        gridLayout_5->addWidget(logedit_aux_light_manual_placement_dist, 1, 1, 1, 1);

        checkBox_aux_light_place_behind = new MyCheckBox(groupBox_8);
        checkBox_aux_light_place_behind->setObjectName(QString::fromUtf8("checkBox_aux_light_place_behind"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(checkBox_aux_light_place_behind->sizePolicy().hasHeightForWidth());
        checkBox_aux_light_place_behind->setSizePolicy(sizePolicy1);

        gridLayout_5->addWidget(checkBox_aux_light_place_behind, 2, 0, 1, 2);

        label_134 = new QLabel(groupBox_8);
        label_134->setObjectName(QString::fromUtf8("label_134"));

        gridLayout_5->addWidget(label_134, 1, 0, 1, 1);


        verticalLayout_17->addLayout(gridLayout_5);


        verticalLayout_41->addWidget(groupBox_8);

        widget_light_sources_manager = new cLightSourcesManager(scrollAreaWidgetContents_11);
        widget_light_sources_manager->setObjectName(QString::fromUtf8("widget_light_sources_manager"));

        verticalLayout_41->addWidget(widget_light_sources_manager);

        groupCheck_random_lights_group = new MyGroupBox(scrollAreaWidgetContents_11);
        groupCheck_random_lights_group->setObjectName(QString::fromUtf8("groupCheck_random_lights_group"));
        groupCheck_random_lights_group->setCheckable(true);
        verticalLayout_random_lights = new QVBoxLayout(groupCheck_random_lights_group);
        verticalLayout_random_lights->setSpacing(2);
        verticalLayout_random_lights->setObjectName(QString::fromUtf8("verticalLayout_random_lights"));
        verticalLayout_random_lights->setContentsMargins(2, 2, 2, 2);
        gridLayout_random_lights = new QGridLayout();
        gridLayout_random_lights->setSpacing(2);
        gridLayout_random_lights->setObjectName(QString::fromUtf8("gridLayout_random_lights"));
        label_random_lights_intensity_3 = new QLabel(groupCheck_random_lights_group);
        label_random_lights_intensity_3->setObjectName(QString::fromUtf8("label_random_lights_intensity_3"));

        gridLayout_random_lights->addWidget(label_random_lights_intensity_3, 10, 0, 1, 1);

        label_random_lights_center_of_distribution = new QLabel(groupCheck_random_lights_group);
        label_random_lights_center_of_distribution->setObjectName(QString::fromUtf8("label_random_lights_center_of_distribution"));

        gridLayout_random_lights->addWidget(label_random_lights_center_of_distribution, 4, 0, 1, 1);

        logedit_random_lights_intensity = new MyLineEdit(groupCheck_random_lights_group);
        logedit_random_lights_intensity->setObjectName(QString::fromUtf8("logedit_random_lights_intensity"));

        gridLayout_random_lights->addWidget(logedit_random_lights_intensity, 8, 2, 1, 1);

        logedit_random_lights_max_distance_from_fractal = new MyLineEdit(groupCheck_random_lights_group);
        logedit_random_lights_max_distance_from_fractal->setObjectName(QString::fromUtf8("logedit_random_lights_max_distance_from_fractal"));

        gridLayout_random_lights->addWidget(logedit_random_lights_max_distance_from_fractal, 2, 2, 1, 1);

        label_random_lights_intensity = new QLabel(groupCheck_random_lights_group);
        label_random_lights_intensity->setObjectName(QString::fromUtf8("label_random_lights_intensity"));

        gridLayout_random_lights->addWidget(label_random_lights_intensity, 8, 0, 1, 1);

        label_random_lights_max_distance_from_fractal = new QLabel(groupCheck_random_lights_group);
        label_random_lights_max_distance_from_fractal->setObjectName(QString::fromUtf8("label_random_lights_max_distance_from_fractal"));

        gridLayout_random_lights->addWidget(label_random_lights_max_distance_from_fractal, 2, 0, 1, 1);

        label_random_lights_intensity_5 = new QLabel(groupCheck_random_lights_group);
        label_random_lights_intensity_5->setObjectName(QString::fromUtf8("label_random_lights_intensity_5"));

        gridLayout_random_lights->addWidget(label_random_lights_intensity_5, 14, 0, 1, 1);

        vect3_random_lights_distribution_center_y = new MyLineEdit(groupCheck_random_lights_group);
        vect3_random_lights_distribution_center_y->setObjectName(QString::fromUtf8("vect3_random_lights_distribution_center_y"));
        sizePolicy1.setHeightForWidth(vect3_random_lights_distribution_center_y->sizePolicy().hasHeightForWidth());
        vect3_random_lights_distribution_center_y->setSizePolicy(sizePolicy1);

        gridLayout_random_lights->addWidget(vect3_random_lights_distribution_center_y, 5, 2, 1, 1);

        label_random_lights_first_color = new QLabel(groupCheck_random_lights_group);
        label_random_lights_first_color->setObjectName(QString::fromUtf8("label_random_lights_first_color"));

        gridLayout_random_lights->addWidget(label_random_lights_first_color, 15, 0, 1, 1);

        label_random_lights_intensity_2 = new QLabel(groupCheck_random_lights_group);
        label_random_lights_intensity_2->setObjectName(QString::fromUtf8("label_random_lights_intensity_2"));

        gridLayout_random_lights->addWidget(label_random_lights_intensity_2, 9, 0, 1, 1);

        label_random_lights_intensity_4 = new QLabel(groupCheck_random_lights_group);
        label_random_lights_intensity_4->setObjectName(QString::fromUtf8("label_random_lights_intensity_4"));

        gridLayout_random_lights->addWidget(label_random_lights_intensity_4, 11, 0, 1, 1);

        label_random_lights_random_seed = new QLabel(groupCheck_random_lights_group);
        label_random_lights_random_seed->setObjectName(QString::fromUtf8("label_random_lights_random_seed"));

        gridLayout_random_lights->addWidget(label_random_lights_random_seed, 1, 0, 1, 1);

        comboBox_random_lights_coloring_type = new MyComboBox(groupCheck_random_lights_group);
        comboBox_random_lights_coloring_type->addItem(QString());
        comboBox_random_lights_coloring_type->addItem(QString());
        comboBox_random_lights_coloring_type->addItem(QString());
        comboBox_random_lights_coloring_type->addItem(QString());
        comboBox_random_lights_coloring_type->setObjectName(QString::fromUtf8("comboBox_random_lights_coloring_type"));

        gridLayout_random_lights->addWidget(comboBox_random_lights_coloring_type, 14, 2, 1, 1);

        spinboxInt_random_lights_number = new MySpinBox(groupCheck_random_lights_group);
        spinboxInt_random_lights_number->setObjectName(QString::fromUtf8("spinboxInt_random_lights_number"));
        sizePolicy1.setHeightForWidth(spinboxInt_random_lights_number->sizePolicy().hasHeightForWidth());
        spinboxInt_random_lights_number->setSizePolicy(sizePolicy1);
        spinboxInt_random_lights_number->setMaximum(999999);

        gridLayout_random_lights->addWidget(spinboxInt_random_lights_number, 0, 1, 1, 2);

        spinboxInt_random_lights_random_seed = new MySpinBox(groupCheck_random_lights_group);
        spinboxInt_random_lights_random_seed->setObjectName(QString::fromUtf8("spinboxInt_random_lights_random_seed"));
        sizePolicy1.setHeightForWidth(spinboxInt_random_lights_random_seed->sizePolicy().hasHeightForWidth());
        spinboxInt_random_lights_random_seed->setSizePolicy(sizePolicy1);
        spinboxInt_random_lights_random_seed->setMaximum(999999);

        gridLayout_random_lights->addWidget(spinboxInt_random_lights_random_seed, 1, 1, 1, 2);

        label_distribution_y = new QLabel(groupCheck_random_lights_group);
        label_distribution_y->setObjectName(QString::fromUtf8("label_distribution_y"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_distribution_y->sizePolicy().hasHeightForWidth());
        label_distribution_y->setSizePolicy(sizePolicy2);

        gridLayout_random_lights->addWidget(label_distribution_y, 5, 1, 1, 1);

        checkBox_random_lights_cast_shadows = new MyCheckBox(groupCheck_random_lights_group);
        checkBox_random_lights_cast_shadows->setObjectName(QString::fromUtf8("checkBox_random_lights_cast_shadows"));
        sizePolicy1.setHeightForWidth(checkBox_random_lights_cast_shadows->sizePolicy().hasHeightForWidth());
        checkBox_random_lights_cast_shadows->setSizePolicy(sizePolicy1);

        gridLayout_random_lights->addWidget(checkBox_random_lights_cast_shadows, 12, 0, 1, 3);

        label_distribution_z = new QLabel(groupCheck_random_lights_group);
        label_distribution_z->setObjectName(QString::fromUtf8("label_distribution_z"));
        sizePolicy2.setHeightForWidth(label_distribution_z->sizePolicy().hasHeightForWidth());
        label_distribution_z->setSizePolicy(sizePolicy2);

        gridLayout_random_lights->addWidget(label_distribution_z, 6, 1, 1, 1);

        label_random_lights_number = new QLabel(groupCheck_random_lights_group);
        label_random_lights_number->setObjectName(QString::fromUtf8("label_random_lights_number"));

        gridLayout_random_lights->addWidget(label_random_lights_number, 0, 0, 1, 1);

        pushButton_place_random_lights_by_mouse = new QPushButton(groupCheck_random_lights_group);
        pushButton_place_random_lights_by_mouse->setObjectName(QString::fromUtf8("pushButton_place_random_lights_by_mouse"));
        sizePolicy1.setHeightForWidth(pushButton_place_random_lights_by_mouse->sizePolicy().hasHeightForWidth());
        pushButton_place_random_lights_by_mouse->setSizePolicy(sizePolicy1);

        gridLayout_random_lights->addWidget(pushButton_place_random_lights_by_mouse, 7, 0, 1, 3);

        label_random_lights_second_color = new QLabel(groupCheck_random_lights_group);
        label_random_lights_second_color->setObjectName(QString::fromUtf8("label_random_lights_second_color"));

        gridLayout_random_lights->addWidget(label_random_lights_second_color, 16, 0, 1, 1);

        logedit_random_lights_distribution_radius = new MyLineEdit(groupCheck_random_lights_group);
        logedit_random_lights_distribution_radius->setObjectName(QString::fromUtf8("logedit_random_lights_distribution_radius"));

        gridLayout_random_lights->addWidget(logedit_random_lights_distribution_radius, 3, 2, 1, 1);

        vect3_random_lights_distribution_center_x = new MyLineEdit(groupCheck_random_lights_group);
        vect3_random_lights_distribution_center_x->setObjectName(QString::fromUtf8("vect3_random_lights_distribution_center_x"));
        sizePolicy1.setHeightForWidth(vect3_random_lights_distribution_center_x->sizePolicy().hasHeightForWidth());
        vect3_random_lights_distribution_center_x->setSizePolicy(sizePolicy1);

        gridLayout_random_lights->addWidget(vect3_random_lights_distribution_center_x, 4, 2, 1, 1);

        label_random_lights_distribution_radius = new QLabel(groupCheck_random_lights_group);
        label_random_lights_distribution_radius->setObjectName(QString::fromUtf8("label_random_lights_distribution_radius"));

        gridLayout_random_lights->addWidget(label_random_lights_distribution_radius, 3, 0, 1, 1);

        vect3_random_lights_distribution_center_z = new MyLineEdit(groupCheck_random_lights_group);
        vect3_random_lights_distribution_center_z->setObjectName(QString::fromUtf8("vect3_random_lights_distribution_center_z"));
        sizePolicy1.setHeightForWidth(vect3_random_lights_distribution_center_z->sizePolicy().hasHeightForWidth());
        vect3_random_lights_distribution_center_z->setSizePolicy(sizePolicy1);

        gridLayout_random_lights->addWidget(vect3_random_lights_distribution_center_z, 6, 2, 1, 1);

        label_distribution_x = new QLabel(groupCheck_random_lights_group);
        label_distribution_x->setObjectName(QString::fromUtf8("label_distribution_x"));
        sizePolicy2.setHeightForWidth(label_distribution_x->sizePolicy().hasHeightForWidth());
        label_distribution_x->setSizePolicy(sizePolicy2);

        gridLayout_random_lights->addWidget(label_distribution_x, 4, 1, 1, 1);

        logedit_random_lights_soft_shadow_cone = new MyLineEdit(groupCheck_random_lights_group);
        logedit_random_lights_soft_shadow_cone->setObjectName(QString::fromUtf8("logedit_random_lights_soft_shadow_cone"));

        gridLayout_random_lights->addWidget(logedit_random_lights_soft_shadow_cone, 11, 2, 1, 1);

        checkBox_random_lights_penetrating = new MyCheckBox(groupCheck_random_lights_group);
        checkBox_random_lights_penetrating->setObjectName(QString::fromUtf8("checkBox_random_lights_penetrating"));
        sizePolicy1.setHeightForWidth(checkBox_random_lights_penetrating->sizePolicy().hasHeightForWidth());
        checkBox_random_lights_penetrating->setSizePolicy(sizePolicy1);

        gridLayout_random_lights->addWidget(checkBox_random_lights_penetrating, 13, 0, 1, 3);

        logedit_random_lights_size = new MyLineEdit(groupCheck_random_lights_group);
        logedit_random_lights_size->setObjectName(QString::fromUtf8("logedit_random_lights_size"));

        gridLayout_random_lights->addWidget(logedit_random_lights_size, 9, 2, 1, 1);

        logedit_random_lights_visibility = new MyLineEdit(groupCheck_random_lights_group);
        logedit_random_lights_visibility->setObjectName(QString::fromUtf8("logedit_random_lights_visibility"));

        gridLayout_random_lights->addWidget(logedit_random_lights_visibility, 10, 2, 1, 1);

        colorButton_random_lights_color_2 = new MyColorButton(groupCheck_random_lights_group);
        colorButton_random_lights_color_2->setObjectName(QString::fromUtf8("colorButton_random_lights_color_2"));

        gridLayout_random_lights->addWidget(colorButton_random_lights_color_2, 16, 2, 1, 1);

        colorButton_random_lights_color = new MyColorButton(groupCheck_random_lights_group);
        colorButton_random_lights_color->setObjectName(QString::fromUtf8("colorButton_random_lights_color"));

        gridLayout_random_lights->addWidget(colorButton_random_lights_color, 15, 2, 1, 1);


        verticalLayout_random_lights->addLayout(gridLayout_random_lights);


        verticalLayout_41->addWidget(groupCheck_random_lights_group);

        groupCheck_glow_sphere_1_enabled = new MyGroupBox(scrollAreaWidgetContents_11);
        groupCheck_glow_sphere_1_enabled->setObjectName(QString::fromUtf8("groupCheck_glow_sphere_1_enabled"));
        groupCheck_glow_sphere_1_enabled->setCheckable(true);
        verticalLayout_glow_sphere = new QVBoxLayout(groupCheck_glow_sphere_1_enabled);
        verticalLayout_glow_sphere->setSpacing(2);
        verticalLayout_glow_sphere->setObjectName(QString::fromUtf8("verticalLayout_glow_sphere"));
        verticalLayout_glow_sphere->setContentsMargins(2, 2, 2, 2);
        gridLayout_glow_sphere = new QGridLayout();
        gridLayout_glow_sphere->setSpacing(2);
        gridLayout_glow_sphere->setObjectName(QString::fromUtf8("gridLayout_glow_sphere"));
        label_glow_position_x = new QLabel(groupCheck_glow_sphere_1_enabled);
        label_glow_position_x->setObjectName(QString::fromUtf8("label_glow_position_x"));

        gridLayout_glow_sphere->addWidget(label_glow_position_x, 0, 0, 1, 1);

        vect3_glow_sphere_1_position_x = new MyLineEdit(groupCheck_glow_sphere_1_enabled);
        vect3_glow_sphere_1_position_x->setObjectName(QString::fromUtf8("vect3_glow_sphere_1_position_x"));

        gridLayout_glow_sphere->addWidget(vect3_glow_sphere_1_position_x, 0, 1, 1, 2);

        label_glow_position_y = new QLabel(groupCheck_glow_sphere_1_enabled);
        label_glow_position_y->setObjectName(QString::fromUtf8("label_glow_position_y"));

        gridLayout_glow_sphere->addWidget(label_glow_position_y, 1, 0, 1, 1);

        vect3_glow_sphere_1_position_y = new MyLineEdit(groupCheck_glow_sphere_1_enabled);
        vect3_glow_sphere_1_position_y->setObjectName(QString::fromUtf8("vect3_glow_sphere_1_position_y"));

        gridLayout_glow_sphere->addWidget(vect3_glow_sphere_1_position_y, 1, 1, 1, 2);

        label_glow_position_z = new QLabel(groupCheck_glow_sphere_1_enabled);
        label_glow_position_z->setObjectName(QString::fromUtf8("label_glow_position_z"));

        gridLayout_glow_sphere->addWidget(label_glow_position_z, 2, 0, 1, 1);

        vect3_glow_sphere_1_position_z = new MyLineEdit(groupCheck_glow_sphere_1_enabled);
        vect3_glow_sphere_1_position_z->setObjectName(QString::fromUtf8("vect3_glow_sphere_1_position_z"));

        gridLayout_glow_sphere->addWidget(vect3_glow_sphere_1_position_z, 2, 1, 1, 2);

        label_glow_radius = new QLabel(groupCheck_glow_sphere_1_enabled);
        label_glow_radius->setObjectName(QString::fromUtf8("label_glow_radius"));

        gridLayout_glow_sphere->addWidget(label_glow_radius, 3, 0, 1, 1);

        spinboxd_glow_sphere_1_radius = new MyDoubleSpinBox(groupCheck_glow_sphere_1_enabled);
        spinboxd_glow_sphere_1_radius->setObjectName(QString::fromUtf8("spinboxd_glow_sphere_1_radius"));

        gridLayout_glow_sphere->addWidget(spinboxd_glow_sphere_1_radius, 3, 1, 1, 2);

        label_glow_color = new QLabel(groupCheck_glow_sphere_1_enabled);
        label_glow_color->setObjectName(QString::fromUtf8("label_glow_color"));

        gridLayout_glow_sphere->addWidget(label_glow_color, 4, 0, 1, 1);

        colorButton_glow_sphere_1_color = new MyColorButton(groupCheck_glow_sphere_1_enabled);
        colorButton_glow_sphere_1_color->setObjectName(QString::fromUtf8("colorButton_glow_sphere_1_color"));

        gridLayout_glow_sphere->addWidget(colorButton_glow_sphere_1_color, 4, 1, 1, 2);

        label_glow_intensity = new QLabel(groupCheck_glow_sphere_1_enabled);
        label_glow_intensity->setObjectName(QString::fromUtf8("label_glow_intensity"));

        gridLayout_glow_sphere->addWidget(label_glow_intensity, 5, 0, 1, 1);

        spinboxd_glow_sphere_1_intensity = new MyDoubleSpinBox(groupCheck_glow_sphere_1_enabled);
        spinboxd_glow_sphere_1_intensity->setObjectName(QString::fromUtf8("spinboxd_glow_sphere_1_intensity"));

        gridLayout_glow_sphere->addWidget(spinboxd_glow_sphere_1_intensity, 5, 1, 1, 2);


        verticalLayout_glow_sphere->addLayout(gridLayout_glow_sphere);


        verticalLayout_41->addWidget(groupCheck_glow_sphere_1_enabled);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_41->addItem(verticalSpacer_6);

        scrollArea_10->setWidget(scrollAreaWidgetContents_11);

        verticalLayout_67->addWidget(scrollArea_10);


        retranslateUi(cEffectsLightsTab);

        QMetaObject::connectSlotsByName(cEffectsLightsTab);
    } // setupUi

    void retranslateUi(QWidget *cEffectsLightsTab)
    {
        pushButton_local_load_6->setText(QCoreApplication::translate("cEffectsLightsTab", "Laden", nullptr));
        pushButton_local_save_6->setText(QCoreApplication::translate("cEffectsLightsTab", "Opslaan", nullptr));
        pushButton_local_reset_6->setText(QCoreApplication::translate("cEffectsLightsTab", "Reset", nullptr));
        pushButton_local_randomize_5->setText(QCoreApplication::translate("cEffectsLightsTab", "Randomize", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("cEffectsLightsTab", "Common light options", nullptr));
#if QT_CONFIG(tooltip)
        logedit_all_lights_intensity->setToolTip(QCoreApplication::translate("cEffectsLightsTab", "<html><head/><body><p>Global intensity multiplier for all lights (Light #1\342\200\246#N). Multiplies each light\342\200\231s Intensity value: 1.0 = no change, 0 = lights off, &gt;1 brightens, &lt;1 dims. </p><p>Useful for balancing overall lighting without editing each light.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_all_lights_size->setToolTip(QCoreApplication::translate("cEffectsLightsTab", "<html><head/><body><p>Global size multiplier for all lights\342\200\231 visible glow/halo. Multiplies each light\342\200\231s Size value: 1.0 = no change; &gt;1 enlarges halos, &lt;1 shrinks them. </p><p>Also scales the apparent angular size for directional lights.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        colorButton_fill_light_color->setToolTip(QCoreApplication::translate("cEffectsLightsTab", "<html><head/><body><p>Color of light source</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_fill_light_color->setProperty("text", QVariant(QCoreApplication::translate("cEffectsLightsTab", "PushButton", nullptr)));
        label_2->setText(QCoreApplication::translate("cEffectsLightsTab", "All lights intensity", nullptr));
        label_4->setText(QCoreApplication::translate("cEffectsLightsTab", "All lights size", nullptr));
#if QT_CONFIG(tooltip)
        logedit_rayleigh_scattering_blue->setToolTip(QCoreApplication::translate("cEffectsLightsTab", "<html><head/><body><p>Strength of blue Rayleigh scattering for volumetric effects (atmosphere). </p><p>Higher values add a blue, angle\342\200\221dependent tint around lights (\342\210\235 1 + cos\302\262\316\270). Set to 0 to disable. </p><p>Use with Rayleigh scattering red to balance the effect.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_all_lights_visibility->setToolTip(QCoreApplication::translate("cEffectsLightsTab", "<html><head/><body><p>Global multiplier for all lights\342\200\231 Visibility (the visible glow/illuminated fog around lights). </p><p>Multiplies each light\342\200\231s Visibility value: 1.0 = no change, 0 = hide visible lights, &gt;1 increases glow.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_3->setText(QCoreApplication::translate("cEffectsLightsTab", "All lights visibility", nullptr));
        label->setText(QCoreApplication::translate("cEffectsLightsTab", "Fill light color:", nullptr));
        label_7->setText(QCoreApplication::translate("cEffectsLightsTab", "Rayleigh scattering blue:", nullptr));
        label_13->setText(QCoreApplication::translate("cEffectsLightsTab", "Rayleigh scattering red:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_rayleigh_scattering_red->setToolTip(QCoreApplication::translate("cEffectsLightsTab", "<html><head/><body><p>Strength of red Mie scattering for volumetric effects (atmosphere). Increases warm, forward\342\200\221scattering glow when looking toward the light direction (stronger near beams/god\342\200\221rays). </p><p>1.0 = noticeable effect; 0 = off. </p><p>Use together with Rayleigh scattering blue to balance overall color.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_8->setTitle(QCoreApplication::translate("cEffectsLightsTab", "Light placement options", nullptr));
#if QT_CONFIG(tooltip)
        logedit_aux_light_manual_placement_dist->setToolTip(QCoreApplication::translate("cEffectsLightsTab", "<html><head/><body><p>Controls distance from the fractal surface where the light will be placed with mouse pointer. When it's zero, the light will be set on fractal surface. A higher value moves the light towards the camera.</p><p>Mouse wheel + Alt, or vertical click-drag in the main render: with pattern line placement, drag changes offset live; with Place light, hold Alt and drag to change offset (without Alt, drag moves the light).</p><p>Extra X/Y/Z world offset: Pattern Lines \342\206\222 \302\253Extra positie X / Y / Z (wereld)\302\273.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBox_aux_light_place_behind->setToolTip(QCoreApplication::translate("cEffectsLightsTab", "<html><head/><body> <p>When placing a light with the mouse, position it <b>behind</b> the clicked surface (traced through the fractal). When disabled, the light is placed <b>in front</b> of the surface at the manual placement distance.</p> <p>Use to hide the emitter behind geometry while keeping its illumination/visible glow. Applies to the \342\200\234Place light\342\200\235 mouse action.</p> </body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_aux_light_place_behind->setText(QCoreApplication::translate("cEffectsLightsTab", "Place light behind the object", nullptr));
        label_134->setText(QCoreApplication::translate("cEffectsLightsTab", "Placement distance\n"
"(by mouse):", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_random_lights_group->setToolTip(QCoreApplication::translate("cEffectsLightsTab", "<html><head/><body><p><img src=\":/tooltips/tooltips_images/random lights placement.png\"/></p><p><span style=\" font-weight:600;\">Random seed: </span>random seed for lights distribution </p><p><span style=\" font-weight:600;\">Maximum distance from the fractal: </span>random lights are placed within this distance from the fractal surface </p><p><span style=\" font-weight:600;\">Centre of distribution X, Y, Z: </span>the centre point for random light distribution. To set this point by mouse pointer, select &quot;Set position of centre for random lights&quot; in Mouse click function combo box in Mandelbulber Render Window </p><p><span style=\" font-weight:600;\">Distribution radius of lights: </span>maximum distance from Centre of distribution where lights can be placed. The random lights appear in the region that matches the condition of being both within this radius and also within the maximum distance from fractal surface.</p><p>If this radius is too small to generate random lights, then the program will au"
                        "tomatically increase this radius. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_random_lights_group->setTitle(QCoreApplication::translate("cEffectsLightsTab", "Random li&ghts options", nullptr));
        label_random_lights_intensity_3->setText(QCoreApplication::translate("cEffectsLightsTab", "Zichtbaarheid:", nullptr));
        label_random_lights_center_of_distribution->setText(QCoreApplication::translate("cEffectsLightsTab", "Center of distribution:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_random_lights_intensity->setToolTip(QCoreApplication::translate("cEffectsLightsTab", "<html><head/><body><p>Per\342\200\221light brightness for auto\342\200\221generated random lights.</p><p>Does not depend on \342\200\234Number of random lights\342\200\235 \342\200\224 adding more lights does not auto\342\200\221scale intensity. Increase for brighter illumination; very high values can cause overexposure. Adjust together with Visibility and Size for desired look.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_random_lights_max_distance_from_fractal->setToolTip(QCoreApplication::translate("cEffectsLightsTab", "<html><head/><body><p>Maximum distance from the fractal surface used when placing auto-generated random lights. Only positions within this distance from the surface are accepted.</p><p>Lower values keep lights close to the surface; higher values allow them to float farther out. Very small values may slow placement or yield few/no lights. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_random_lights_intensity->setText(QCoreApplication::translate("cEffectsLightsTab", "Intensiteit:", nullptr));
        label_random_lights_max_distance_from_fractal->setText(QCoreApplication::translate("cEffectsLightsTab", "Maximum distance\n"
"from fractal:", nullptr));
        label_random_lights_intensity_5->setText(QCoreApplication::translate("cEffectsLightsTab", "Coloring type:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_random_lights_distribution_center_y->setToolTip(QCoreApplication::translate("cEffectsLightsTab", "<html><head/><body><p>Center point (X/Y/Z) for placing auto-generated random lights. Lights are distributed around this point within the Distribution radius.</p><p>Use \342\200\234Place random light center\342\200\235 to pick it with the mouse. Works together with \342\200\234Maximum distance from fractal\342\200\235 to keep lights near the surface.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_random_lights_first_color->setText(QCoreApplication::translate("cEffectsLightsTab", "First color:", nullptr));
        label_random_lights_intensity_2->setText(QCoreApplication::translate("cEffectsLightsTab", "Grootte:", nullptr));
        label_random_lights_intensity_4->setText(QCoreApplication::translate("cEffectsLightsTab", "Soft shadow cone:", nullptr));
        label_random_lights_random_seed->setText(QCoreApplication::translate("cEffectsLightsTab", "Random Seed:", nullptr));
        comboBox_random_lights_coloring_type->setItemText(0, QCoreApplication::translate("cEffectsLightsTab", "Random colors", nullptr));
        comboBox_random_lights_coloring_type->setItemText(1, QCoreApplication::translate("cEffectsLightsTab", "Single color", nullptr));
        comboBox_random_lights_coloring_type->setItemText(2, QCoreApplication::translate("cEffectsLightsTab", "Two colors", nullptr));
        comboBox_random_lights_coloring_type->setItemText(3, QCoreApplication::translate("cEffectsLightsTab", "Two colors based on distance", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_random_lights_coloring_type->setToolTip(QCoreApplication::translate("cEffectsLightsTab", "<html><head/><body><p>Choose how auto\342\200\221generated random lights are colored.</p><p><span style=\" font-style:italic;\">Random colors</span> \342\200\224 each light gets a random color.</p><p><span style=\" font-style:italic;\">Single color</span> \342\200\224 all lights use the First color.</p><p><span style=\" font-style:italic;\">Two colors</span> \342\200\224 each light randomly uses the First or Second color.</p><p><span style=\" font-style:italic;\">Two colors based on distance</span> \342\200\224 color blends between First and Second color based on the light\342\200\231s distance to the fractal surface (closer \342\206\222 First, farther \342\206\222 Second).</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinboxInt_random_lights_number->setToolTip(QCoreApplication::translate("cEffectsLightsTab", "<html><head/><body><p>Number of auto-generated random lights. </p><p>Lights are placed around the Center of distribution within the Distribution radius, constrained by Maximum distance from fractal, and initialized using the Random seed. </p><p>Higher values may slow rendering and clutter the scene.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinboxInt_random_lights_random_seed->setToolTip(QCoreApplication::translate("cEffectsLightsTab", "<html><head/><body><p>Random seed for generating auto-created lights. With the same seed and settings, the random lights\342\200\231 positions/colors are reproducible; change it to get a different arrangement.</p><p>Integer 0\342\200\223999999. Does not change the number of lights, only their randomized outcome.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_distribution_y->setText(QCoreApplication::translate("cEffectsLightsTab", "y:", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_random_lights_cast_shadows->setToolTip(QCoreApplication::translate("cEffectsLightsTab", "<html><head/><body><p>Enable shadow casting for auto\342\200\221generated random lights.</p><p>When on, these lights occlude geometry and produce shadows. Turn off to use them as non\342\200\221shadowing fill lights and speed up rendering. For soft, blurry shadows, also enable \342\200\234Calculate MC soft shadows\342\200\235 and adjust \342\200\234Soft shadow cone\342\200\235. Otherwise shadows are hard.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_random_lights_cast_shadows->setText(QCoreApplication::translate("cEffectsLightsTab", "Cast shadows", nullptr));
        label_distribution_z->setText(QCoreApplication::translate("cEffectsLightsTab", "z:", nullptr));
        label_random_lights_number->setText(QCoreApplication::translate("cEffectsLightsTab", "Number of random\n"
"lights:", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_place_random_lights_by_mouse->setToolTip(QCoreApplication::translate("cEffectsLightsTab", "<html><head/><body><p>Pick the center for auto-generated random lights by clicking in the image.</p><p>Sets the mouse mode to \342\200\234Place random light center\342\200\235. On click, it also auto-sets Distribution radius to 50% and Maximum distance from fractal to 10% of the distance from the chosen center to the camera.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_place_random_lights_by_mouse->setText(QCoreApplication::translate("cEffectsLightsTab", "Place random light center by mouse", nullptr));
        label_random_lights_second_color->setText(QCoreApplication::translate("cEffectsLightsTab", "Second color:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_random_lights_distribution_radius->setToolTip(QCoreApplication::translate("cEffectsLightsTab", "<html><head/><body><p>Radius of the area around the Center of distribution where auto-generated random lights are placed (\302\261radius along X/Y/Z).</p><p>Increase to spread lights wider; decrease to cluster them near the center. Works with \342\200\234Maximum distance from fractal\342\200\235 to keep lights near the surface. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        vect3_random_lights_distribution_center_x->setToolTip(QCoreApplication::translate("cEffectsLightsTab", "<html><head/><body><p>Center point (X/Y/Z) for placing auto-generated random lights. Lights are distributed around this point within the Distribution radius.</p><p>Use \342\200\234Place random light center\342\200\235 to pick it with the mouse. Works together with \342\200\234Maximum distance from fractal\342\200\235 to keep lights near the surface.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_random_lights_distribution_radius->setText(QCoreApplication::translate("cEffectsLightsTab", "Distribution radius\n"
"of lights:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_random_lights_distribution_center_z->setToolTip(QCoreApplication::translate("cEffectsLightsTab", "<html><head/><body><p>Center point (X/Y/Z) for placing auto-generated random lights. Lights are distributed around this point within the Distribution radius.</p><p>Use \342\200\234Place random light center\342\200\235 to pick it with the mouse. Works together with \342\200\234Maximum distance from fractal\342\200\235 to keep lights near the surface.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_distribution_x->setText(QCoreApplication::translate("cEffectsLightsTab", "x:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_random_lights_soft_shadow_cone->setToolTip(QCoreApplication::translate("cEffectsLightsTab", "<html><head/><body><p>Soft shadow cone angle for auto\342\200\221generated random lights (degrees).</p><p>Sets the angular radius used by Monte Carlo soft\342\200\221shadow sampling. 0 = hard, crisp shadows; higher values produce softer, blurrier shadows.</p><p>Effective when \342\200\234Cast shadows\342\200\235 is on, and \342\200\234Calculate MC soft shadows\342\200\235 is enabled.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBox_random_lights_penetrating->setToolTip(QCoreApplication::translate("cEffectsLightsTab", "<html><head/><body><p>Allow auto\342\200\221generated random lights to penetrate geometry.</p><p>When enabled, these lights are partally blocked by objects and can illuminate through walls or inside cavities\342\200\224useful as fill lights. For realistic, blocked lighting and shadows, turn this off.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_random_lights_penetrating->setText(QCoreApplication::translate("cEffectsLightsTab", "Penetrating", nullptr));
#if QT_CONFIG(tooltip)
        logedit_random_lights_size->setToolTip(QCoreApplication::translate("cEffectsLightsTab", "<html><head/><body><p>Emitter size (radius) of each auto\342\200\221generated random light.</p><p>Larger values behave more like area lights, producing softer shadows and broader highlights; smaller values approach point lights with sharper shadows. Very large sizes can flatten contrast.</p><p>Effective when \342\200\234Random lights group\342\200\235 is enabled. Default: 0.1.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_random_lights_visibility->setToolTip(QCoreApplication::translate("cEffectsLightsTab", "<html><head/><body><p>Brightness of the visible light source (glow/halo) for each auto\342\200\221generated random light.</p><p>Affects only how strongly the emitter itself is drawn on screen; it does not change scene illumination (use \342\200\234Intensity\342\200\235 for that). Works together with \342\200\234Size\342\200\235 to define the halo\342\200\231s radius. Not used for directional lights.</p><p>Higher values make brighter, more noticeable bulbs.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_random_lights_color_2->setProperty("text", QVariant(QCoreApplication::translate("cEffectsLightsTab", "PushButton", nullptr)));
        colorButton_random_lights_color->setProperty("text", QVariant(QCoreApplication::translate("cEffectsLightsTab", "PushButton", nullptr)));
        groupCheck_glow_sphere_1_enabled->setTitle(QCoreApplication::translate("cEffectsLightsTab", "Glow Sphere", nullptr));
        label_glow_position_x->setText(QCoreApplication::translate("cEffectsLightsTab", "Position X", nullptr));
        label_glow_position_y->setText(QCoreApplication::translate("cEffectsLightsTab", "Position Y", nullptr));
        label_glow_position_z->setText(QCoreApplication::translate("cEffectsLightsTab", "Position Z", nullptr));
        label_glow_radius->setText(QCoreApplication::translate("cEffectsLightsTab", "Radius:", nullptr));
        label_glow_color->setText(QCoreApplication::translate("cEffectsLightsTab", "Kleur:", nullptr));
        colorButton_glow_sphere_1_color->setText(QString());
        label_glow_intensity->setText(QCoreApplication::translate("cEffectsLightsTab", "Intensiteit:", nullptr));
        (void)cEffectsLightsTab;
    } // retranslateUi

};

namespace Ui {
    class cEffectsLightsTab: public Ui_cEffectsLightsTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EFFECTS_LIGHTS_TAB_H
